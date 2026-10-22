# Runtime / TypedElementFramework

- module root: `Source/Runtime/TypedElementFramework`
- headers: 98; symbols: 3410
- symbol kinds: class=87, delegate=5, enum=44, enumerator=157, externvar=3, function=850, macro=98, member=414, namespace=214, prototype=1082, struct=253, typedef=182, union=3, variable=18
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/TypedElementFramework/Private/Elements/Framework/TypedElementListLibrary.h` (Private)


#### class `UTypedElementListLibrary`  
`class UTypedElementListLibrary : public UObject`  
_L12-233_
- reflection: `UCLASS()`
- inherits: `UObject`
- L21 _public function_ `static FScriptTypedElementListProxy CreateScriptElementList(UTypedElementRegistry* Registry)` — `UFUNCTION(BlueprintCallable, DisplayName="Create Element List", Category = "TypedElementFramework|Registry", meta=(ScriptMethod, ScriptName="CreateElementList"))` — Create an empty list of elements associated with the given registry.
- L31 _public function_ `static FScriptTypedElementListProxy Clone(const FScriptTypedElementListProxy ElementList)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Clone this list instance. @note Only copies elements; does not copy any bindings!
- L42 _public function_ `static FScriptTypedElementHandle GetElementHandleAt(const FScriptTypedElementListProxy ElementList, const int32 Index)` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Get the element handle at the given index. @note Use IsValidIndex to test for validity.
- L52 _public function_ `static UObject* GetElementInterface(const FScriptTypedElementListProxy ElementList, const FScriptTypedElementHandle& ElementHandle, const TSubclassOf<UInterface> BaseInterfaceType)` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Get the element interface from the given handle.
- L62 _public function_ `static bool HasElements(const FScriptTypedElementListProxy ElementList, const TSubclassOf<UInterface> BaseInterfaceType = {})` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Test whether there are elements in this list, optionally filtering to elements that implement the given interface.
- L72 _public function_ `static int32 CountElements(const FScriptTypedElementListProxy ElementList, const TSubclassOf<UInterface> BaseInterfaceType = {})` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Count the number of elements in this list, optionally filtering to elements that implement the given interface.
- L82 _public function_ `static bool HasElementsOfType(const FScriptTypedElementListProxy ElementList, const FName ElementTypeName)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Test whether there are elements in this list of the given type.
- L92 _public function_ `static int32 CountElementsOfType(const FScriptTypedElementListProxy ElementList, const FName ElementTypeName)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Count the number of elements in this list of the given type.
- L102 _public function_ `static TArray<FScriptTypedElementHandle> GetElementHandles(const FScriptTypedElementListProxy ElementList, const TSubclassOf<UInterface> BaseInterfaceType)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Get the handle of every element in this list, optionally filtering to elements that implement the given interface.
- L112 _public function_ `static bool IsValidIndex(const FScriptTypedElementListProxy ElementList, const int32 Index)` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Is the given index a valid entry within this element list?
- L122 _public function_ `static int32 Num(const FScriptTypedElementListProxy ElementList)` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Get the number of entries within this element list.
- L132 _public function_ `static void Shrink(FScriptTypedElementListProxy ElementList)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Shrink this element list storage to avoid slack.
- L144 _public function_ `static void Reserve(FScriptTypedElementListProxy ElementList, const int32 Size)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Pre-allocate enough memory in this element list to store the given number of entries.
- L156 _public function_ `static void Empty(FScriptTypedElementListProxy ElementList, const int32 Slack = 0)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Remove all entries from this element list, potentially leaving space allocated for the given number of entries.
- L168 _public function_ `static void Reset(FScriptTypedElementListProxy ElementList)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Remove all entries from this element list, preserving existing allocations.
- L180 _public function_ `static bool Contains(const FScriptTypedElementListProxy ElementList, const FScriptTypedElementHandle& ElementHandle)` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Does this element list contain an entry for the given element handle?
- L191 _public function_ `static bool Add(FScriptTypedElementListProxy ElementList, const FScriptTypedElementHandle& ElementHandle)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Add the given element handle to this element list, if it isn't already in the list. @return True if the element handle was added, false if it is already in the list.
- L201 _public function_ `static void Append(FScriptTypedElementListProxy ElementList, const TArray<FScriptTypedElementHandle>& ElementHandles)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Append the given element handles to this element list.
- L213 _public function_ `static void AppendList(FScriptTypedElementListProxy ElementList, const FScriptTypedElementListProxy OtherElementList)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Append the another element list to this element list.
- L228 _public function_ `static bool Remove(FScriptTypedElementListProxy ElementList, const FScriptTypedElementHandle& ElementHandle)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|List", meta=(ScriptMethod))` — Remove the given element handle from this element list, if it is in the list. @return True if the element handle was removed, false if it isn't in the list.

### `Source/Runtime/TypedElementFramework/Private/TypedElementFrameworkTests.h` (Private)


#### class `UTestTypedElementInterfaceA`  
`class UTestTypedElementInterfaceA : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ITestTypedElementInterfaceA`  
`class ITestTypedElementInterfaceA`  
_L19-33_
- desc: Test interfaces
- L24 _public function_ `virtual FText GetDisplayName(const FTypedElementHandle& InElementHandle)`
- L26 _public function_ `virtual bool SetDisplayName(const FTypedElementHandle& InElementHandle, FText InNewName, bool bNotify = true)`
- L29 _public function_ `virtual FText GetDisplayName(const FScriptTypedElementHandle& InElementHandle)` — `UFUNCTION(BlueprintCallable, Category = "TypedElementFramework|Testing")`
- L32 _public function_ `virtual bool SetDisplayName(const FScriptTypedElementHandle& InElementHandle, FText InNewName, bool bNotify = true)` — `UFUNCTION(BlueprintCallable, Category = "TypedElementFramework|Testing")`

#### class `UTestTypedElementInterfaceB`  
`class UTestTypedElementInterfaceB : public UInterface`  
_L36-39_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ITestTypedElementInterfaceB`  
`class ITestTypedElementInterfaceB`  
_L41-50_
- L46 _public function_ `virtual bool MarkAsTested(const FTypedElementHandle& InElementHandle)`
- L49 _public function_ `virtual bool MarkAsTested(const FScriptTypedElementHandle& InElementHandle)` — `UFUNCTION(BlueprintCallable, Category = "TypedElementFramework|Testing")`

#### class `UTestTypedElementInterfaceC`  
`class UTestTypedElementInterfaceC : public UInterface`  
_L53-56_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ITestTypedElementInterfaceC`  
`class ITestTypedElementInterfaceC`  
_L58-67_
- L63 _public function_ `virtual bool GetIsTested(const FTypedElementHandle& InElementHandle) const`
- L66 _public function_ `virtual bool GetIsTested(const FScriptTypedElementHandle& InElementHandle) const` — `UFUNCTION(BlueprintCallable, Category = "TypedElementFramework|Testing")`

#### struct `TTypedElement`  
`template <> struct TTypedElement<ITestTypedElementInterfaceA> : public TTypedElementBase<ITestTypedElementInterfaceA>`  
_L70-74_
- inherits: `TTypedElementBase<ITestTypedElementInterfaceA>`
- L72 _public function_ `FText GetDisplayName() const`
- L73 _public function_ `bool SetDisplayName(FText InNewName, bool bNotify = true) const`
- L79 _public function_ `bool MarkAsTested()`
- L85 _public function_ `bool GetIsTested() const`

#### struct `TTypedElement`  
`template <> struct TTypedElement<ITestTypedElementInterfaceB> : public TTypedElementBase<ITestTypedElementInterfaceB>`  
_L77-80_
- inherits: `TTypedElementBase<ITestTypedElementInterfaceB>`
- L72 _public function_ `FText GetDisplayName() const`
- L73 _public function_ `bool SetDisplayName(FText InNewName, bool bNotify = true) const`
- L79 _public function_ `bool MarkAsTested()`
- L85 _public function_ `bool GetIsTested() const`

#### struct `TTypedElement`  
`template <> struct TTypedElement<ITestTypedElementInterfaceC> : public TTypedElementBase<ITestTypedElementInterfaceC>`  
_L83-86_
- inherits: `TTypedElementBase<ITestTypedElementInterfaceC>`
- L72 _public function_ `FText GetDisplayName() const`
- L73 _public function_ `bool SetDisplayName(FText InNewName, bool bNotify = true) const`
- L79 _public function_ `bool MarkAsTested()`
- L85 _public function_ `bool GetIsTested() const`

#### struct `FTestTypedElementData`  
`struct FTestTypedElementData`  
_L91-96_
- desc: Test dummy type
- L93 _public prototype_ `UE_DECLARE_TYPED_ELEMENT_DATA_RTTI(FTestTypedElementData);`
- L95 _public member_ `FName InternalElementId;`

#### class `UTestTypedElementInterfaceA_ImplTyped`  
`class UTestTypedElementInterfaceA_ImplTyped : public UObject, public ITestTypedElementInterfaceA`  
_L99-106_
- reflection: `UCLASS()`
- inherits: `UObject,ITestTypedElementInterfaceA`
- L104 _public prototype_ `virtual FText GetDisplayName(const FTypedElementHandle& InElementHandle) override;`
- L105 _public prototype_ `virtual bool SetDisplayName(const FTypedElementHandle& InElementHandle, FText InNewName, bool bNotify) override;`

#### class `UTestTypedElementInterfaceA_ImplUntyped`  
`class UTestTypedElementInterfaceA_ImplUntyped : public UObject, public ITestTypedElementInterfaceA`  
_L112-119_
- reflection: `UCLASS()`
- inherits: `UObject,ITestTypedElementInterfaceA`
- desc: Test untyped
- L117 _public prototype_ `virtual FText GetDisplayName(const FTypedElementHandle& InElementHandle) override;`
- L118 _public prototype_ `virtual bool SetDisplayName(const FTypedElementHandle& InElementHandle, FText InNewName, bool bNotify) override;`

#### class `UTestTypedElementInterfaceBAndC_Typed`  
`class UTestTypedElementInterfaceBAndC_Typed : public UObject, public ITestTypedElementInterfaceB, public ITestTypedElementInterfaceC`  
_L125-132_
- reflection: `UCLASS()`
- inherits: `UObject,ITestTypedElementInterfaceB,ITestTypedElementInterfaceC`
- desc: Test to two implementation in one object
- L130 _public prototype_ `virtual bool MarkAsTested(const FTypedElementHandle& InElementHandle) override;`
- L131 _public prototype_ `virtual bool GetIsTested(const FTypedElementHandle& InElementHandle) const override;`

### `Source/Runtime/TypedElementFramework/Public/DataStorage/CommonTypes.h` (Public)


#### struct `FEditorDataStorageColumn`  
`struct FEditorDataStorageColumn`  
_L15-18_
- reflection: `USTRUCT()`
- desc: Base for the data structures for a column.

#### struct `FEditorDataStorageTag`  
`struct FEditorDataStorageTag`  
_L24-27_
- reflection: `USTRUCT()`
- desc: Base for the data structures that act as tags to rows. Tags should not have any data.

#### struct `UE::type_identity`  
`template<class T> struct type_identity`  
_L47-47_
- L47 _public typedef_ `template<class T> struct type_identity { using type = T; };`

#### class `UE::Editor::DataStorage::FValueTag`  
`class FValueTag`  
_L83-93_
- desc: Defines a dynamic type for a value tag Example: FValueTag ColorTagType(TEXT("Color")); FValueTag DirectionTagType(TEXT("Direction")); A value tag can take on different values for each type.  This is set up when a tag is added to a row.
- L86 _public prototype_ `explicit FValueTag(const FName& InName);`
- L88 _public prototype_ `const FName& GetName() const;`
- L89 _public prototype_ `bool operator==(const FValueTag& Other) const = default;`
- L92 _private member_ `FName Name;`

#### struct `UE::Editor::DataStorage::FDynamicColumnDescription`  
`struct FDynamicColumnDescription`  
_L98-105_
- L100 _public member_ `const UScriptStruct* TemplateType;`
- L101 _public member_ `FName Identifier;`
- L104 _public prototype_ `bool operator==(const FDynamicColumnDescription&) const = default;`

#### enum `UE::Editor::DataStorage::ETableType`  
`enum class ETableType : uint8`  
_L107-113_
- L109 _public enumerator_ `Invalid` — Not a valid table.
- L110 _public enumerator_ `Declared` — Table declared by user.
- L111 _public enumerator_ `Derivative` — Table declared by users, based on another table.
- L112 _public enumerator_ `Variant` — A dynamically generated variant of a declared or derivative table.

#### struct `UE::Editor::DataStorage::FTableInfoView`  
`struct FTableInfoView`  
_L125-140_
- desc: Short lived view into information about a table. Note: This struct is meant for short term usage only and becomes invalid the moment there's any change to a table.
- L128 _public member_ `TConstArrayView<TableHandle> Variants;` — List of all dynamically created variants of this table.
- L130 _public member_ `TConstArrayView<TableHandle> Derivatives;` — All declared tables that use this table as a template.
- L132 _public member_ `FName Name;` — The name of the table.
- L134 _public member_ `ETableType Type = ETableType::Invalid;` — The type of table.
- L139 _public member_ `TableHandle Parent = InvalidTableHandle;` — If this is a variant then the Parent represents the table used as the basis for the variant. If this is a derived table then the Parent represents the table that was passed in as the template for this table.

#### struct `UE::Editor::DataStorage::FTableRegistrationOptions`  
`struct FTableRegistrationOptions`  
_L142-159_
- L145 _public member_ `TableHandle SourceTable = InvalidTableHandle;` — If set, use the provided table as a source to copy from. Additional provided rows will be added to the copied layout.
- L158 _public member_ `int32 MemorySize = 0;` — Indicates the amount of memory a shard (a.k.a. chunk) of the table will take. Increasing this number means less memory fragmentation and longer continuous time spend in a query callback while smaller sizes will decrease wasted memory. Making this too large yields diminishing returns as cache efficiency will plateau while distribution across threads will suffer as there are less shards to distribute. Making this too small though will cause increased overhead in managing tables and the overhead of calling query callbacks will relatively increase. Consider leaving this to default and only update if profiling indicates a benefit. Benefits may include going larger for very large tables since distribution among processors will be high but the cost of table management will go down. Decrease for tables that on average only have a small number of entries to save on memory. Set to 0 will indicate to use a default size or the editor specified override. Any other value will override any default or user setting.

#### struct `UE::Editor::DataStorage::TVariantName`  
`template <int N> struct TVariantName`  
_L190-205_
- desc: Capture for variant names, e.g. for dynamic columns or hierarchies, so the name can be passed in as a template argument.
- L192 _public member_ `static constexpr int Size = N;`
- L193 _public member_ `char Name[N > 1 ? (N - 1) : 1];`
- L195 _public prototype_ `constexpr TVariantName() requires (N == 0) = default;`
- L196 _public function_ `constexpr TVariantName(const char (&InName)[N]) requires (N > 0)`
- L201 _public function_ `FName GetName() const`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L32 _namespace_ `namespace detail` (scope `UE`)
- L50 _typedef_ `template< class T > using type_identity_t = type_identity<T>::type;` (scope `UE`)
- L53 _function_ `template <class T> constexpr T MakeDefault()` (scope `UE`)
- L65 _namespace_ `namespace Editor` (scope `UE`)
- L65 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L67 _typedef_ `using FColumn = FEditorDataStorageColumn;` (scope `UE::Editor::DataStorage`)
- L68 _typedef_ `using FTag = FEditorDataStorageTag;` (scope `UE::Editor::DataStorage`)
- L119 _typedef_ `using FForeignKey = FMapKey;` (scope `UE::Editor::DataStorage`) — Foreign keys provide a mechanic to generate a key that unique identifies a given row so it can be referenced by external sources.
- L163 _typedef_ `using RowCreationCallbackRef = TFunctionRef<void(RowHandle Row)>;` (scope `UE::Editor::DataStorage`)
- L164 _typedef_ `using ColumnCreationCallbackRef = TFunctionRef<void(void* Column, const UScriptStruct& ColumnType)>;` (scope `UE::Editor::DataStorage`)
- L165 _typedef_ `using ColumnListCallbackRef = TFunctionRef<void(const UScriptStruct& ColumnType)>;` (scope `UE::Editor::DataStorage`)
- L166 _typedef_ `using ColumnListWithDataCallbackRef = TFunctionRef<void(void* Column, const UScriptStruct& ColumnType)>;` (scope `UE::Editor::DataStorage`)
- L167 _typedef_ `using ColumnCopyOrMoveCallback = void (*)(const UScriptStruct& ColumnType, void* Destination, void* Source);` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/DataStorage/Debug/Log.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEditorDataStorage, Log, All);`

### `Source/Runtime/TypedElementFramework/Public/DataStorage/Features.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L12 _externvar_ `const extern FName StorageFeatureName;` (scope `UE::Editor::DataStorage`)
- L13 _externvar_ `const extern FName CompatibilityFeatureName;` (scope `UE::Editor::DataStorage`)
- L14 _externvar_ `const extern FName UiFeatureName;` (scope `UE::Editor::DataStorage`)
- L16 _prototype_ `FSimpleMulticastDelegate& OnEditorDataStorageFeaturesEnabled();` (scope `UE::Editor::DataStorage`)
- L17 _prototype_ `bool AreEditorDataStorageFeaturesEnabled();` (scope `UE::Editor::DataStorage`)
- L20 _function_ `template<typename T> const T* GetDataStorageFeature(const FName InName)` (scope `UE::Editor::DataStorage`)
- L30 _function_ `template<typename T> T* GetMutableDataStorageFeature(const FName InName)` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/DataStorage/Handles.h` (Public)


#### struct `UE::Editor::DataStorage::FHierarchyHandle`  
`struct FHierarchyHandle`  
_L28-35_
- L30 _public member_ `uint64 Reserved = 0;`
- L31 _public function_ `bool operator==(FHierarchyHandle Other) const`

#### struct `FTedsRowHandle`  
`struct FTedsRowHandle`  
_L44-71_
- reflection: `USTRUCT()`
- desc: FTedsRowHandle is a strongly typed wrapper around UE::Editor::DataStorage::RowHandle and should only be used in cases where you need the extra info. E.g for reflection/UHT or for template specializing something that needs to know the semantics of the row handle. For all other cases, you should use the regular UE::Editor::DataStorage::RowHandle
- L49 _public member_ `uint64 RowHandle = UE::Editor::DataStorage::InvalidRowHandle;` — `UPROPERTY()`
- L51 _public function_ `operator UE::Editor::DataStorage::RowHandle () const`
- L56 _public function_ `FTedsRowHandle& operator=(UE::Editor::DataStorage::RowHandle InRowHandle)`
- L62 _public function_ `bool IsValid() const`

#### struct `FTedsTableHandle`  
`struct FTedsTableHandle`  
_L81-108_
- reflection: `USTRUCT()`
- desc: FTedsTableHandle is a strongly typed wrapper around UE::Editor::DataStorage::TableHandle and should only be used in cases where you need the extra info. E.g for reflection/UHT or for template specializing something that needs to know the semantics of the table handle. For all other cases, you should use the regular UE::Editor::DataStorage::TableHandle
- L86 _public member_ `uint64 TableHandle = UE::Editor::DataStorage::InvalidTableHandle;` — `UPROPERTY()`
- L88 _public function_ `operator UE::Editor::DataStorage::TableHandle() const`
- L93 _public function_ `FTedsTableHandle& operator=(UE::Editor::DataStorage::TableHandle InTableHandle)`
- L99 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L12 _typedef_ `using TableHandle = uint64;` (scope `UE::Editor::DataStorage`)
- L13 _variable_ `static constexpr TableHandle InvalidTableHandle = TNumericLimits<TableHandle>::Max();` (scope `UE::Editor::DataStorage`)
- L15 _typedef_ `using RowHandle = uint64;` (scope `UE::Editor::DataStorage`)
- L16 _variable_ `static constexpr RowHandle InvalidRowHandle = 0;` (scope `UE::Editor::DataStorage`)
- L18 _typedef_ `using QueryHandle = uint64;` (scope `UE::Editor::DataStorage`)
- L19 _variable_ `static constexpr QueryHandle InvalidQueryHandle = TNumericLimits<QueryHandle>::Max();` (scope `UE::Editor::DataStorage`)
- L25 _typedef_ `using RelationTypeHandle = uint64;` (scope `UE::Editor::DataStorage`) — Handle to a registered relation type. Relation types define how two rows can be connected (e.g., SubclassOf, ImplementsInterface).
- L26 _variable_ `static constexpr RelationTypeHandle InvalidRelationTypeHandle = TNumericLimits<RelationTypeHandle>::Max();` (scope `UE::Editor::DataStorage`)
- L67 _function_ `friend uint32 GetTypeHash(const FTedsRowHandle& Key)`
- L104 _function_ `friend uint32 GetTypeHash(const FTedsTableHandle& Key)`

### `Source/Runtime/TypedElementFramework/Public/DataStorage/MapKey.h` (Public)


#### struct `UE::Editor::DataStorage::FKeyIssue`  
`struct FKeyIssue`  
_L22-36_
- desc: If the key encountered a problem the type will be switched to FKeyIssue and the description contains an explanation of the problem.
- L24 _public prototype_ `FKeyIssue() = default;`
- L25 _public prototype_ `FKeyIssue(const FString::ElementType* Description);`
- L26 _public prototype_ `FKeyIssue(FString Description);`
- L27 _public prototype_ `FKeyIssue(FStringView Description);`
- L28 _public prototype_ `FKeyIssue(const FKeyIssueView& Description);`
- L30 _public prototype_ `bool operator==(const FKeyIssue& Rhs) const = default;`
- L31 _public prototype_ `bool operator!=(const FKeyIssue& Rhs) const = default;`
- L32 _public prototype_ `bool operator==(const FKeyIssueView& Rhs) const;`
- L33 _public prototype_ `bool operator!=(const FKeyIssueView& Rhs) const;`
- L35 _public member_ `FString Description;`

#### struct `UE::Editor::DataStorage::FKeyIssueView`  
`struct FKeyIssueView`  
_L38-50_
- L40 _public prototype_ `FKeyIssueView() = default;`
- L41 _public prototype_ `FKeyIssueView(FStringView Description);`
- L42 _public prototype_ `FKeyIssueView(const FKeyIssue& Description);`
- L44 _public prototype_ `bool operator==(const FKeyIssueView& Rhs) const = default;`
- L45 _public prototype_ `bool operator!=(const FKeyIssueView& Rhs) const = default;`
- L46 _public prototype_ `bool operator==(const FKeyIssue& Rhs) const;`
- L47 _public prototype_ `bool operator!=(const FKeyIssue& Rhs) const;`
- L49 _public member_ `FStringView Description;`

#### class `UE::Editor::DataStorage::FMapKey`  
`class FMapKey`  
_L52-97_
- L60 _public prototype_ `FMapKey() = default;`
- L62 _public prototype_ `FMapKey(const FMapKey& Key);`
- L63 _public prototype_ `FMapKey(FMapKey&& Rhs);`
- L64 _public prototype_ `explicit FMapKey(FKeyIssue Key);`
- L65 _public prototype_ `explicit FMapKey(const void* Key);`
- L66 _public prototype_ `explicit FMapKey(const UObject* Key);`
- L67 _public prototype_ `explicit FMapKey(int64 Key);`
- L68 _public prototype_ `explicit FMapKey(uint64 Key);`
- L69 _public prototype_ `explicit FMapKey(float Key);`
- L70 _public prototype_ `explicit FMapKey(double Key);`
- L71 _public prototype_ `explicit FMapKey(FString Key);`
- L72 _public prototype_ `explicit FMapKey(FName Key);`
- L73 _public prototype_ `explicit FMapKey(FSoftObjectPath Key);`
- L75 _public prototype_ `FMapKey& operator=(const FMapKey& Rhs);`
- L76 _public prototype_ `FMapKey& operator=(FMapKey&& Rhs);`
- L78 _public prototype_ `bool operator==(const FMapKey& Rhs) const;`
- L79 _public prototype_ `bool operator==(const FMapKeyView& Rhs) const;`
- L80 _public prototype_ `bool operator!=(const FMapKey& Rhs) const;`
- L81 _public prototype_ `bool operator!=(const FMapKeyView& Rhs) const;`
- L83 _public prototype_ `uint64 CalculateHash() const;`
- L84 _public prototype_ `bool IsSet() const;`
- L85 _public prototype_ `void Clear();`
- L86 _public prototype_ `FString ToString() const;`
- L89 _public function_ `template<typename T> bool IsType() const`
- L91 _public function_ `template<typename T> const T& GetAs() const`
- L94 _private typedef_ `using KeyType = TVariant<FEmptyVariantState, FKeyIssue, const void*, const UObject*, int64, uint64, float, double, FString, FName, TUniquePtr<FSoftObjectPath>>;`
- L96 _private member_ `KeyType Key;`

#### class `UE::Editor::DataStorage::FMapKeyView`  
`class FMapKeyView`  
_L99-141_
- L105 _public prototype_ `FMapKeyView() = default;`
- L106 _public prototype_ `FMapKeyView(const FMapKey& InKey);`
- L107 _public prototype_ `explicit FMapKeyView(const FKeyIssue& Key);`
- L108 _public prototype_ `explicit FMapKeyView(FKeyIssueView Key);`
- L109 _public prototype_ `explicit FMapKeyView(const void* Key);`
- L110 _public prototype_ `explicit FMapKeyView(const UObject* Key);`
- L111 _public prototype_ `explicit FMapKeyView(int64 Key);`
- L112 _public prototype_ `explicit FMapKeyView(uint64 Key);`
- L113 _public prototype_ `explicit FMapKeyView(float Key);`
- L114 _public prototype_ `explicit FMapKeyView(double Key);`
- L115 _public prototype_ `explicit FMapKeyView(const FString& Key);`
- L116 _public prototype_ `explicit FMapKeyView(FStringView Key);`
- L117 _public prototype_ `explicit FMapKeyView(const FName& Key);`
- L118 _public prototype_ `explicit FMapKeyView(const FSoftObjectPath& Key);`
- L120 _public prototype_ `FMapKeyView& operator=(const FMapKey& InKey);`
- L122 _public prototype_ `FMapKey CreateKey() const;`
- L124 _public prototype_ `bool operator==(const FMapKey& Rhs) const;`
- L125 _public prototype_ `bool operator==(const FMapKeyView& Rhs) const;`
- L126 _public prototype_ `bool operator!=(const FMapKey& Rhs) const;`
- L127 _public prototype_ `bool operator!=(const FMapKeyView& Rhs) const;`
- L129 _public prototype_ `uint64 CalculateHash() const;`
- L130 _public prototype_ `FString ToString() const;`
- L133 _public function_ `template<typename T> bool IsType() const`
- L135 _public function_ `template<typename T> const T& GetAs() const`
- L138 _private typedef_ `using KeyViewType = TVariant<FEmptyVariantState, FKeyIssueView, const void*, const UObject*, int64, uint64, float, double, FStringView, const FName*, const FSoftObjectPath*>;`
- L140 _private member_ `KeyViewType Key;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Source/Runtime/TypedElementFramework/Public/DataStorage/Queries/Conditions.h` (Public)


#### struct `UE::Editor::DataStorage::Queries::FColumnBase`  
`struct FColumnBase`  
_L18-29_
- L20 _public member_ `TWeakObjectPtr<const UScriptStruct> TypeInfo = nullptr;`
- L21 _public member_ `FName Identifier = NAME_None;`
- L24 _protected prototype_ `FColumnBase() = default;`
- L25 _protected function_ `explicit FColumnBase(TWeakObjectPtr<const UScriptStruct> ColumnTypeInfo, const FName& InIdentifier) : TypeInfo(ColumnTypeInfo) , Identifier(InIdentifier)`

#### struct `UE::Editor::DataStorage::Queries::TColumn`  
`template<typename T, TVariantName Id = TVariantName<0>()> struct TColumn final : public FColumnBase`  
_L32-36_
- inherits: `FColumnBase`
- L34 _public function_ `explicit TColumn() : FColumnBase(T::StaticStruct(), NAME_None)`
- L35 _public function_ `explicit TColumn(const FName& Identifier) : FColumnBase(T::StaticStruct(), Identifier)`
- L41 _public function_ `explicit TColumn() : FColumnBase(T::StaticStruct(), []() { static FName Name = Id.GetName(); return Name; }())`
- L42 _public function_ ``
- L51 _public function_ `explicit TColumn(TWeakObjectPtr<const UScriptStruct> ColumnTypeInfo) : FColumnBase(ColumnTypeInfo, NAME_None)`
- L52 _public function_ `explicit TColumn(TWeakObjectPtr<const UScriptStruct> ColumnTypeInfo, const FName& Identifier) : FColumnBase(ColumnTypeInfo, Identifier)`

#### struct `UE::Editor::DataStorage::Queries::TColumn`  
`template<typename T, TVariantName Id> requires (decltype(Id)::Size > 0) struct TColumn<T, Id> final : public FColumnBase`  
_L39-46_
- inherits: `FColumnBase`
- L34 _public function_ `explicit TColumn() : FColumnBase(T::StaticStruct(), NAME_None)`
- L35 _public function_ `explicit TColumn(const FName& Identifier) : FColumnBase(T::StaticStruct(), Identifier)`
- L41 _public function_ `explicit TColumn() : FColumnBase(T::StaticStruct(), []() { static FName Name = Id.GetName(); return Name; }())`
- L42 _public function_ ``
- L51 _public function_ `explicit TColumn(TWeakObjectPtr<const UScriptStruct> ColumnTypeInfo) : FColumnBase(ColumnTypeInfo, NAME_None)`
- L52 _public function_ `explicit TColumn(TWeakObjectPtr<const UScriptStruct> ColumnTypeInfo, const FName& Identifier) : FColumnBase(ColumnTypeInfo, Identifier)`

#### struct `UE::Editor::DataStorage::Queries::TColumn`  
`template<> struct TColumn<void> final : public FColumnBase`  
_L49-56_
- inherits: `FColumnBase`
- L34 _public function_ `explicit TColumn() : FColumnBase(T::StaticStruct(), NAME_None)`
- L35 _public function_ `explicit TColumn(const FName& Identifier) : FColumnBase(T::StaticStruct(), Identifier)`
- L41 _public function_ `explicit TColumn() : FColumnBase(T::StaticStruct(), []() { static FName Name = Id.GetName(); return Name; }())`
- L42 _public function_ ``
- L51 _public function_ `explicit TColumn(TWeakObjectPtr<const UScriptStruct> ColumnTypeInfo) : FColumnBase(ColumnTypeInfo, NAME_None)`
- L52 _public function_ `explicit TColumn(TWeakObjectPtr<const UScriptStruct> ColumnTypeInfo, const FName& Identifier) : FColumnBase(ColumnTypeInfo, Identifier)`

#### class `UE::Editor::DataStorage::Queries::IQueryConditionCompileContext`  
`class IQueryConditionCompileContext`  
_L66-71_
- desc: Compile Context used to resolve dynamic columns when FConditions are compiled
- L69 _public prototype_ `virtual ~IQueryConditionCompileContext() = default;`
- L70 _public prototype_ `virtual const UScriptStruct* GenerateDynamicColumn(const FDynamicColumnDescription&) const = 0;`

#### class `UE::Editor::DataStorage::Queries::FEditorStorageQueryConditionCompileContext`  
`class FEditorStorageQueryConditionCompileContext : public IQueryConditionCompileContext`  
_L76-84_
- inherits: `IQueryConditionCompileContext`
- desc: Specialized compile context that accepts an ICoreProvider
- L79 _public prototype_ `explicit FEditorStorageQueryConditionCompileContext(ICoreProvider* InDataStorage);`
- L80 _public prototype_ `virtual const UScriptStruct* GenerateDynamicColumn(const FDynamicColumnDescription& Description) const override;`
- L83 _private member_ `ICoreProvider* DataStorage;`

#### class `UE::Editor::DataStorage::Queries::FConditions`  
`class FConditions final`  
_L92-205_
- desc: Product of boolean combination of multiple columns. This can be used to verify if a collection of columns match the stored columns. NOTE: You must call Compile() before you call any members accessing the conditions
- L95 _public typedef_ `using ContainsCallback = TFunctionRef<bool(uint8_t ColumnIndex, TWeakObjectPtr<const UScriptStruct> Column)>;`
- L107 _public prototype_ `FConditions();`
- L110 _public prototype_ `FConditions(FColumnBase Column);` — Not marked as "explicit" to allow conversion from a column. This means that conditions with a single argument can be written in the same way as ones that use combinations.
- L113 _public prototype_ `FConditions& Compile(const IQueryConditionCompileContext& CompileContext);` — Compile must be called before using any functions that access the columns
- L116 _public prototype_ `bool IsCompiled() const;` — Check whether these query conditions have been compiled
- L119 _public prototype_ `void AppendToString(FString& Output) const;` — Convert the conditions into a string and append them to the provided string.
- L122 _public prototype_ `bool Verify(TConstArrayView<FColumnBase> AvailableColumns) const;` — Runs the provided list of columns through the conditions and returns true if a valid combination of columns is found.
- L127 _public prototype_ `bool Verify( TArray<TWeakObjectPtr<const UScriptStruct>>& MatchedColumns, TConstArrayView<FColumnBase> AvailableColumns, bool AvailableColumnsAreSorted = false) const;` — Runs the provided list of columns through the conditions and returns true if a valid combination of columns is found. This version returns a list of the columns that were used to match the condition.
- L132 _public prototype_ `bool Verify(TConstArrayView<TWeakObjectPtr<const UScriptStruct>> AvailableColumns, bool AvailableColumnsAreSorted = false) const;` — Runs the provided list of columns through the conditions and returns true if a valid combination of columns is found.
- L138 _public prototype_ `bool Verify( TArray<TWeakObjectPtr<const UScriptStruct>>& MatchedColumns, TConstArrayView<TWeakObjectPtr<const UScriptStruct>> AvailableColumns, bool AvailableColumnsAreSorted = false) const;` — Runs the provided list of columns through the conditions and returns true if a valid combination of columns is found. This version returns a list of the columns that were used to match the condition.
- L143 _public prototype_ `bool Verify(TSet<TWeakObjectPtr<const UScriptStruct>> AvailableColumns) const;` — Runs the provided list of columns through the conditions and returns true if a valid combination of columns is found.
- L145 _public prototype_ `bool Verify(ContainsCallback Callback) const;` — Runs through the list of query conditions and uses the callback to verify if a column is available.
- L148 _public prototype_ `uint8_t MinimumColumnMatchRequired() const;` — Returns the minimum number of columns needed for a successful match.
- L150 _public prototype_ `TConstArrayView<TWeakObjectPtr<const UScriptStruct>> GetColumns() const;` — Returns a list of all columns used. This can include duplicate columns.
- L152 _public prototype_ `bool IsEmpty() const;` — Whether or not there are any columns registered for operation.
- L154 _public prototype_ `bool UsesDynamicTemplates() const;` — Whether the conditions contain any columns that are dynamic templates.
- L158 _private prototype_ `template<typename AvailableColumnType, typename ProjectionFunction> bool VerifyWithDynamicColumn(TConstArrayView<AvailableColumnType> AvailableColumns, uint64& OutMatches, ProjectionFunction Projection) const;`
- L160 _private prototype_ `void AppendName(FString& Output, TWeakObjectPtr<const UScriptStruct> TypeInfo) const;`
- L162 _private prototype_ `bool EntersScopeNext(uint8_t Index) const;`
- L163 _private prototype_ `bool EntersScope(uint8_t Index) const;`
- L164 _private prototype_ `bool Contains(TWeakObjectPtr<const UScriptStruct> ColumnType, const TArray<FColumnBase>& AvailableColumns) const;`
- L166 _private prototype_ `bool VerifyBootstrap(ContainsCallback Contains) const;`
- L167 _private prototype_ `bool VerifyRange(uint8_t& TokenIndex, uint8_t& ColumnIndex, ContainsCallback Contains) const;`
- L169 _private prototype_ `void ConvertColumnBitToArray(TArray<TWeakObjectPtr<const UScriptStruct>>& MatchedColumns, uint64 ColumnBits) const;`
- L171 _private prototype_ `uint8_t MinimumColumnMatchRequiredRange(uint8_t& Front) const;`
- L173 _private prototype_ `static void AppendQuery(FConditions& Target, const FConditions& Source);`
- L175 _private member_ `static constexpr SIZE_T MaxColumnCount = 32;`
- L176 _private member_ `static constexpr SIZE_T MaxTokenCount = 64;`
- L191 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(EColumnFlags);`
- L193 _private typedef_ `using ColumnArray = TArray<TWeakObjectPtr<const UScriptStruct>, TInlineAllocator<MaxColumnCount>>;`
- L194 _private typedef_ `using TokenArray = TArray<Token, TInlineAllocator<MaxTokenCount>>;`
- L195 _private typedef_ `using IdentifierArray = TArray<FName, TInlineAllocator<MaxColumnCount>>;`
- L196 _private typedef_ `using ColumnFlagArray = TArray<EColumnFlags, TInlineAllocator<MaxColumnCount>>;`
- L198 _private member_ `ColumnArray Columns;`
- L199 _private member_ `ColumnFlagArray ColumnFlags;`
- L200 _private member_ `TokenArray Tokens;`
- L201 _private member_ `IdentifierArray Identifiers;`
- L202 _private member_ `uint8_t ColumnCount = 0;`
- L203 _private member_ `uint8_t TokenCount = 0;`
- L204 _private member_ `bool bIsCompiled = false;`

#### enum `UE::Editor::DataStorage::Queries::FConditions::Token`  
`enum class Token : uint8_t`  
_L178-185_
- L180 _public enumerator_ `None`
- L181 _public enumerator_ `And`
- L182 _public enumerator_ `Or`
- L183 _public enumerator_ `ScopeOpen`
- L184 _public enumerator_ `ScopeClose`

#### enum `UE::Editor::DataStorage::Queries::FConditions::EColumnFlags`  
`enum class EColumnFlags : uint8_t`  
_L187-190_
- L189 _public enumerator_ `DynamicColumnTemplate = 1 << 0`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L16 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L57 _prototype_ `TColumn(TWeakObjectPtr<const UScriptStruct>) -> TColumn<void>;` (scope `UE::Editor::DataStorage::Queries`)
- L58 _prototype_ `TColumn(TWeakObjectPtr<const UScriptStruct>, const FName&) -> TColumn<void>;` (scope `UE::Editor::DataStorage::Queries`)
- L207 _prototype_ `FConditions operator&&(const FConditions& Lhs, FColumnBase Rhs);` (scope `UE::Editor::DataStorage::Queries`)
- L208 _prototype_ `FConditions operator&&(const FConditions& Lhs, const FConditions& Rhs);` (scope `UE::Editor::DataStorage::Queries`)
- L209 _prototype_ `FConditions operator&&(FColumnBase Lhs, FColumnBase Rhs);` (scope `UE::Editor::DataStorage::Queries`)
- L210 _prototype_ `FConditions operator&&(FColumnBase Lhs, const FConditions& Rhs);` (scope `UE::Editor::DataStorage::Queries`)
- L212 _prototype_ `FConditions operator||(const FConditions& Lhs, FColumnBase Rhs);` (scope `UE::Editor::DataStorage::Queries`)
- L213 _prototype_ `FConditions operator||(const FConditions& Lhs, const FConditions& Rhs);` (scope `UE::Editor::DataStorage::Queries`)
- L214 _prototype_ `FConditions operator||(FColumnBase Lhs, FColumnBase Rhs);` (scope `UE::Editor::DataStorage::Queries`)
- L215 _prototype_ `FConditions operator||(FColumnBase Lhs, const FConditions& Rhs);` (scope `UE::Editor::DataStorage::Queries`)

### `Source/Runtime/TypedElementFramework/Public/DataStorage/Queries/Description.h` (Public)


#### struct `UE::Editor::DataStorage::FQueryDescription`  
`struct FQueryDescription final`  
_L31-216_
- L33 _public member_ `static constexpr int32 NumInlineSelections = 8;`
- L34 _public member_ `static constexpr int32 NumInlineConditions = 8;`
- L35 _public member_ `static constexpr int32 NumInlineDependencies = 2;`
- L36 _public member_ `static constexpr int32 NumInlineGroups = 2;`
- L173 _public member_ `FCallbackData Callback;`
- L178 _public member_ `TArray<TWeakObjectPtr<const UScriptStruct>, TInlineAllocator<NumInlineSelections>> SelectionTypes;`
- L179 _public member_ `TArray<EQueryAccessType, TInlineAllocator<NumInlineSelections>> SelectionAccessTypes;`
- L180 _public member_ `TArray<FColumnMetaData, TInlineAllocator<NumInlineSelections>> SelectionMetaData;`
- L182 _public member_ `TArray<EOperatorType, TInlineAllocator<NumInlineConditions>> ConditionTypes;`
- L183 _public member_ `TArray<FOperator, TInlineAllocator<NumInlineConditions>> ConditionOperators;`
- L185 _public member_ `TArray<FDynamicColumnDescription, TInlineAllocator<NumInlineSelections>> DynamicSelectionTypes;`
- L186 _public member_ `TArray<EQueryAccessType, TInlineAllocator<NumInlineSelections>> DynamicSelectionAccessTypes;`
- L187 _public member_ `TArray<FColumnMetaData::EFlags, TInlineAllocator<NumInlineSelections>> DynamicSelectionMetaData;`
- L189 _public member_ `TArray<EOperatorType, TInlineAllocator<NumInlineConditions>> DynamicConditionOperations;`
- L190 _public member_ `TArray<FDynamicColumnDescription, TInlineAllocator<NumInlineConditions>> DynamicConditionDescriptions;`
- L192 _public member_ `TArray<FValueTagData> ValueTags;`
- L194 _public member_ `TOptional<UE::Editor::DataStorage::Queries::FConditions> Conditions;`
- L196 _public member_ `TArray<TWeakObjectPtr<const UClass>, TInlineAllocator<NumInlineDependencies>> DependencyTypes;`
- L197 _public member_ `TArray<EQueryDependencyFlags, TInlineAllocator<NumInlineDependencies>> DependencyFlags;`
- L199 _public member_ `TArray<TWeakObjectPtr<UObject>, TInlineAllocator<NumInlineDependencies>> CachedDependencies;` — Cached instances of the dependencies. This will always match the count of the other Dependency*Types, but may contain null pointers.
- L200 _public member_ `TArray<QueryHandle> Subqueries;`
- L201 _public member_ `FMetaData MetaData;`
- L203 _public member_ `FName Hierarchy;`
- L206 _public member_ `TArray<FRelationCondition, TInlineAllocator<2>> RelationConditions;` — Relation conditions for filtering rows by relation participation
- L209 _public member_ `TArray<FHierarchyCondition, TInlineAllocator<1>> DescendantOfConditions;` — Descendant-of conditions for hierarchical filtering
- L212 _public member_ `TArray<FHierarchyCondition, TInlineAllocator<1>> AncestorOfConditions;` — Ancestor-of conditions for hierarchical filtering
- L214 _public member_ `EActionType Action;`
- L215 _public member_ `bool bShouldBatchModifications = false;`

#### enum `UE::Editor::DataStorage::FQueryDescription::EActionType`  
`enum class EActionType : uint8`  
_L38-45_
- L40 _public enumerator_ `None` — Do nothing.
- L41 _public enumerator_ `Select` — Selects a set of columns for further processing.
- L42 _public enumerator_ `Count` — Counts the number of entries that match the filter condition.
- L44 _public enumerator_ `Max` — Value indicating the maximum value in this enum. Not to be used as an enum value.

#### enum `UE::Editor::DataStorage::FQueryDescription::EOperatorType`  
`enum class EOperatorType : uint16`  
_L47-55_
- L49 _public enumerator_ `SimpleAll` — Unary: Type
- L50 _public enumerator_ `SimpleAny` — Unary: Type
- L51 _public enumerator_ `SimpleNone` — Unary: Type
- L52 _public enumerator_ `SimpleOptional` — Unary: Type
- L54 _public enumerator_ `Max` — Value indicating the maximum value in this enum. Not to be used as an enum value.

#### union `UE::Editor::DataStorage::FQueryDescription::FOperator`  
`union FOperator`  
_L57-60_
- L59 _public member_ `TWeakObjectPtr<const UScriptStruct> Type;`

#### struct `UE::Editor::DataStorage::FQueryDescription::FValueTagData`  
`struct FValueTagData`  
_L62-70_
- L65 _public member_ `FValueTag Tag;` — The Tag maps to a Mass ConstSharedFragment object
- L69 _public member_ `FName MatchValue;` — The MatchValue specifies the value that the fragment must have to be matched If MatchValue is NAME_None, then TEDS will match all values

#### enum `UE::Editor::DataStorage::FQueryDescription::ERelationRole`  
`enum class ERelationRole : uint8`  
_L75-81_
- desc: Specifies the role a row plays in a relation.
- L78 _public enumerator_ `Subject` — The "from" / "child" side of a relation
- L80 _public enumerator_ `Object` — The "to" / "parent" side of a relation

#### struct `UE::Editor::DataStorage::FQueryDescription::FRelationCondition`  
`struct FRelationCondition`  
_L87-97_
- desc: Condition for filtering rows by their participation in relations. If TargetRow is set, only matches relations with that specific counterpart.
- L90 _public member_ `RelationTypeHandle RelationType = InvalidRelationTypeHandle;` — The relation type to filter by
- L93 _public member_ `ERelationRole Role = ERelationRole::Subject;` — Whether we're looking for rows as subjects or objects of the relation
- L96 _public member_ `RowHandle TargetRow = InvalidRowHandle;` — Optional: If set, only match relations where the counterpart is this specific row

#### struct `UE::Editor::DataStorage::FQueryDescription::FHierarchyCondition`  
`struct FHierarchyCondition`  
_L103-113_
- desc: Condition for filtering rows by their position in a hierarchical relation. Used for IsDescendantOf/IsAncestorOf queries.
- L106 _public member_ `RelationTypeHandle RelationType = InvalidRelationTypeHandle;` — The hierarchical relation type to traverse
- L109 _public member_ `RowHandle ReferenceRow = InvalidRowHandle;` — The reference row to check ancestry/descendancy against
- L112 _public member_ `bool bIncludeSelf = false;` — Whether to include the reference row itself in the results

#### struct `UE::Editor::DataStorage::FQueryDescription::FRelationPredicate`  
`struct FRelationPredicate`  
_L119-139_
- desc: A single atomic relation predicate. Multiple predicates are AND-composed. Unifies the four existing condition types into one value type.
- L129 _public member_ `EType Type = EType::SubjectOf;`
- L130 _public member_ `RelationTypeHandle RelationType = InvalidRelationTypeHandle;`
- L135 _public member_ `RowHandle ReferenceRow = InvalidRowHandle;` — For SubjectOf/ObjectOf: the specific counterpart row, or InvalidRowHandle to match any. For DescendantOf: the ancestor to test against. For AncestorOf: the descendant to test against.
- L138 _public member_ `bool bIncludeSelf = false;` — For DescendantOf/AncestorOf: if true, the reference row itself also passes.

#### enum `UE::Editor::DataStorage::FQueryDescription::FRelationPredicate::EType`  
`enum class EType : uint8`  
_L121-127_
- L123 _public enumerator_ `SubjectOf` — Row must be a subject of the relation (optionally with a specific object)
- L124 _public enumerator_ `ObjectOf` — Row must be an object of the relation (optionally with a specific subject)
- L125 _public enumerator_ `DescendantOf` — Row must be a descendant of ReferenceRow in a hierarchical relation
- L126 _public enumerator_ `AncestorOf` — Row must be an ancestor of ReferenceRow in a hierarchical relation

#### struct `UE::Editor::DataStorage::FQueryDescription::FCallbackData`  
`struct FCallbackData`  
_L141-172_
- L148 _public prototype_ `FCallbackData() = default;`
- L149 _public prototype_ `FCallbackData(const FCallbackData&) = default;`
- L150 _public prototype_ `FCallbackData& operator=(const FCallbackData&) = default;`
- L151 _public prototype_ `FCallbackData(FCallbackData&&) = default;`
- L152 _public prototype_ `FCallbackData& operator=(FCallbackData&&) = default;`
- L156 _public member_ `TArray<FName, TInlineAllocator<NumInlineGroups>> BeforeGroups;`
- L157 _public member_ `TArray<FName, TInlineAllocator<NumInlineGroups>> AfterGroups;`
- L158 _public member_ `QueryCallback Function;`
- L159 _public member_ `FName Name;`
- L160 _public member_ `FName Group;`
- L162 _public member_ `FName ActivationName;` — If a name is set, it indicates the query callback will not be run unless explicitly activated with ActivateQueries.
- L163 _public member_ `const UScriptStruct* MonitoredType{ nullptr };`
- L164 _public member_ `EQueryCallbackType Type{ EQueryCallbackType::None };`
- L165 _public member_ `EQueryTickPhase Phase{ EQueryTickPhase::FrameEnd };`
- L166 _public member_ `bool Active = true;`
- L169 _public member_ `uint8 ActivationCount;` — `UE_DEPRECATED("5.7", "Activation counts are no longer supported.")`
- L171 _public member_ `EExecutionMode ExecutionMode = EExecutionMode::Default;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Editor` (scope `UE`)
- L21 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L26 _typedef_ `using QueryCallback = TFunction<void(const FQueryDescription&, IQueryContext&)>;` (scope `UE::Editor::DataStorage`)
- L27 _typedef_ `using QueryCallbackRef = TFunctionRef<void(const FQueryDescription&, IQueryContext&)>;` (scope `UE::Editor::DataStorage`)
- L28 _typedef_ `using DirectQueryCallback = TFunction<void(const FQueryDescription&, IDirectQueryContext&)>;` (scope `UE::Editor::DataStorage`)
- L29 _typedef_ `using DirectQueryCallbackRef = TFunctionRef<void(const FQueryDescription&, IDirectQueryContext&)>;` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/DataStorage/Queries/Types.h` (Public)


#### enum `UE::Editor::DataStorage::EQueryTickPhase`  
`enum class EQueryTickPhase : uint8`  
_L14-22_
- L16 _public enumerator_ `PrePhysics` — Queries are executed before physics simulation starts.
- L17 _public enumerator_ `DuringPhysics` — Queries that can be run in parallel with physics simulation work.
- L18 _public enumerator_ `PostPhysics` — Queries that need rigid body and cloth simulation to be completed before being executed.
- L19 _public enumerator_ `FrameEnd` — Catchall for queries demoted to the last possible moment.
- L21 _public enumerator_ `Max` — Value indicating the maximum value in this enum. Not to be used as an enum value.

#### enum `UE::Editor::DataStorage::EQueryTickGroups`  
`enum class EQueryTickGroups : uint8`  
_L24-54_
- L27 _public enumerator_ `Default` — The standard group to run work in.
- L30 _public enumerator_ `PreUpdate` — General group that prepares for updating.
- L33 _public enumerator_ `Update` — General group that's used for updating data.
- L36 _public enumerator_ `PostUpdate` — General group that completes for updating.
- L42 _public enumerator_ `SyncExternalToDataStorage` — The group for queries that need to sync data from external sources such as subsystems or the world into the Data Storage. These typically run early in a phase.
- L47 _public enumerator_ `SyncDataStorageToExternal` — The group for queries that need to sync data from the Data Storage to external sources such as subsystems or the world into. These typically run late in a phase.
- L51 _public enumerator_ `SyncWidgets` — Queries grouped under this name will sync data to/from widgets.
- L53 _public enumerator_ `Max` — Value indicating the maximum value in this enum. Not to be used as an enum value.

#### enum `UE::Editor::DataStorage::EQueryCallbackType`  
`enum class EQueryCallbackType : uint8`  
_L56-81_
- L59 _public enumerator_ `None` — No callback provided.
- L61 _public enumerator_ `Processor` — The query will be run every tick if at least one row matches.
- L63 _public enumerator_ `ObserveAdd` — The query will be run when a row is added that matches the query. The first recorded column will be actively monitored for changes.
- L65 _public enumerator_ `ObserveRemove` — The query will be run when a row is removed that matches the query. The first recorded column will be actively monitored for changes.
- L71 _public enumerator_ `PhasePreparation` — At the start of the assigned phase this query will run if there are any matches. These queries will have any deferred operations such as adding/removing rows/columns executed before the phase starts. This introduces sync points that hinder performance and are therefore recommended only for queries that save on work later in the phase such as repeated checks for validity.
- L78 _public enumerator_ `PhaseFinalization` — At the end of the assigned phase this query will run if there are any matches. These queries will have any deferred operations such as adding/removing rows/columns executed before the phase ends. This introduces sync points that hinder performance and are therefore recommended only cases where delaying deferred operations is not possible e.g. when tables are known to be referenced outside the update cycle.
- L80 _public enumerator_ `Max` — Value indicating the maximum value in this enum. Not to be used as an enum value.

#### enum `UE::Editor::DataStorage::EExecutionMode`  
`enum class EExecutionMode : uint8`  
_L83-89_
- L85 _public enumerator_ `Default` — Use the default for the query callback type or the group default.
- L86 _public enumerator_ `GameThread` — The query callback will be executed sequentially on the game thread.
- L87 _public enumerator_ `Threaded` — The entire query callback is called on a separate thread, while respecting dependencies.
- L88 _public enumerator_ `ThreadedChunks` — The query callback is called on a separate thread for each chunk. This can not be set if there are sub-queries.

#### enum `UE::Editor::DataStorage::EQueryAccessType`  
`enum class EQueryAccessType : uint8`  
_L91-101_
- L94 _public enumerator_ `ReadOnly` — Provide read-only access.
- L96 _public enumerator_ `OptionalReadOnly` — Provide read-only access, but do not include when finding matching tables.
- L98 _public enumerator_ `ReadWrite` — Provide read and write access.
- L100 _public enumerator_ `NUM` — /

#### enum `UE::Editor::DataStorage::EQueryDependencyFlags`  
`enum class EQueryDependencyFlags : uint8`  
_L103-112_
- L105 _public enumerator_ `None = 0`
- L107 _public enumerator_ `ReadOnly = 1 << 0` — If set the dependency is accessed as read-only. If not set the dependency requires Read/Write access.
- L109 _public enumerator_ `GameThreadBound = 1 << 1` — If set the dependency can only be used from the game thread, otherwise it can be accessed from any thread.
- L111 _public enumerator_ `AlwaysRefresh = 1 << 2` — If set the dependency will be re-fetched every iteration, otherwise only if not fetched before.

#### struct `UE::Editor::DataStorage::FQueryResult`  
`struct FQueryResult final`  
_L115-167_
- L139 _public prototype_ `FQueryResult() = default;`
- L140 _public function_ `FQueryResult(const FQueryResult& Other) : Count(Other.Count.load()) , Completed(Other.Completed)`
- L145 _public function_ `FQueryResult(FQueryResult&& Other) noexcept : Count(Other.Count.load()) , Completed(Other.Completed)`
- L150 _public function_ `FQueryResult& operator=(const FQueryResult& Other)`
- L157 _public function_ `FQueryResult& operator=(FQueryResult&& Other) noexcept`
- L165 _public member_ `std::atomic<uint32> Count{ 0 };` — The number of rows that were processed.
- L166 _public member_ `ECompletion Completed{ ECompletion::Unavailable };`

#### enum `UE::Editor::DataStorage::FQueryResult::ECompletion`  
`enum class ECompletion`  
_L117-137_
- L120 _public enumerator_ `Fully` — Query could be fully executed.
- L122 _public enumerator_ `Partially` — Only portions of the query were executed. This is caused by a problem that was encountered partway through processing.
- L127 _public enumerator_ `Unsupported` — The back-end doesn't support the particular query. This may be a limitation in how/where the query is run or because the query contains actions and/or operations that are not supported.
- L129 _public enumerator_ `Unavailable` — The provided query is no longer available.
- L134 _public enumerator_ `Incompatible` — The provided callback is not compatible with the query. This can be due to missing columns in the selection or the access to a column is more restricted than the callback requests.
- L136 _public enumerator_ `MissingDependency` — One or more dependencies declared on the query could not be retrieved.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L12 _typedef_ `using IndexHash = uint64;` (scope `UE::Editor::DataStorage`) — `UE_DEPRECATED(5.6, "Use FMapKey(View) with the new mapping functions.")`
- L113 _prototype_ `ENUM_CLASS_FLAGS(EQueryDependencyFlags);` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/DataStorage/Scope/EditorDataScope.h` (Public)


#### class `UE::Editor::DataStorage::Scope::FPushScopeGuard`  
`class FPushScopeGuard`  
_L68-89_
- desc: RAII guard that pushes a new scope row as the thread-local current context. On destruction, restores the previous context. Supports nesting.
- L71 _public function_ `explicit FPushScopeGuard(RowHandle NewContext) : PreviousScope(SetCurrentScope(NewContext))`
- L76 _public function_ `~FPushScopeGuard()`
- L82 _public prototype_ `FPushScopeGuard(const FPushScopeGuard&) = delete;` — Non-copyable, non-movable
- L83 _public prototype_ `FPushScopeGuard& operator=(const FPushScopeGuard&) = delete;`
- L84 _public prototype_ `FPushScopeGuard(FPushScopeGuard&&) = delete;`
- L85 _public prototype_ `FPushScopeGuard& operator=(FPushScopeGuard&&) = delete;`
- L88 _private member_ `RowHandle PreviousScope;`

#### Free symbols / members of external scopes

- L50 _namespace_ `namespace UE`
- L50 _namespace_ `namespace Editor` (scope `UE`)
- L50 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L50 _namespace_ `namespace Scope` (scope `UE::Editor::DataStorage`)
- L58 _prototype_ `RowHandle GetCurrentScope();` (scope `UE::Editor::DataStorage::Scope`) — Returns the thread-local current scope row handle. InvalidRowHandle if none set.
- L62 _prototype_ `RowHandle SetCurrentScope(RowHandle NewContext);` (scope `UE::Editor::DataStorage::Scope`) — Sets the thread-local current scope row handle. Returns the previous value. Prefer FPushScopeGuard for RAII usage.
- L101 _function_ `template<TColumnType T> const T* GetScopeData(ICoreProvider& Storage)` (scope `UE::Editor::DataStorage::Scope`) — Typed hierarchy-walking lookup using the thread-local current scope.
- L108 _function_ `template<TColumnType T> FScopeDataVersion GetScopeDataVersion(ICoreProvider& Storage)` (scope `UE::Editor::DataStorage::Scope`) — Hierarchy-walking version query using thread-local current scope.
- L115 _function_ `template<TColumnType T> FScopeDataVersion SetScopeData(ICoreProvider& Storage, T&& Data)` (scope `UE::Editor::DataStorage::Scope`) — Set scope data using thread-local current scope.
- L122 _function_ `template<TColumnType T> bool RemoveScopeData(ICoreProvider& Storage)` (scope `UE::Editor::DataStorage::Scope`) — Remove scope data using thread-local current scope.

### `Source/Runtime/TypedElementFramework/Public/DataStorage/Scope/EditorDataScopeColumns.h` (Public)


#### struct `FDataStorageScopeDataTag`  
`struct FDataStorageScopeDataTag : public FEditorDataStorageTag`  
_L13-16_
- reflection: `USTRUCT(meta = (DisplayName = "Data Storage Scope Data"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag applied to all scope rows created via AddScopeRow. Used to identify Editor Scope Tree rows in the TEDS debugger.

#### struct `FEditingVerseScope`  
`struct FEditingVerseScope : public FEditorDataStorageColumn`  
_L25-31_
- reflection: `USTRUCT(meta = (DisplayName = "Editing Verse Scope"))`
- inherits: `FEditorDataStorageColumn`
- desc: The VersePath of the asset/scope currently being edited by a tool. Published on scope rows by editors (Level Editor, Prefab Editor, etc.) so that downstream consumers can determine access-specifier visibility via FVersePathRegistry::CanAccess(ContextPath, TargetPath).
- L30 _public member_ `FString EditingScopeVersePath;` — `UPROPERTY()`

#### struct `FScopeRowSourceInfo`  
`struct FScopeRowSourceInfo : public FEditorDataStorageColumn`  
_L38-46_
- reflection: `USTRUCT(meta = (DisplayName = "Scope Row Source Info"))`
- inherits: `FEditorDataStorageColumn`
- desc: Captures the callstack at the point where a scope row was created via AddScopeRow. Used by the Scope Hierarchy debugger tab to show where each scope row originated.
- L42 _public member_ `static constexpr int32 MaxCallstackDepth = 64;`
- L44 _public member_ `uint64 Callstack[MaxCallstackDepth] = {};`
- L45 _public member_ `int32 CallstackDepth = 0;`

#### Free symbols / members of external scopes

- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace Editor` (scope `UE`)
- L48 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L50 _typedef_ `using FScopeDataTag = FDataStorageScopeDataTag;` (scope `UE::Editor::DataStorage`)
- L51 _typedef_ `using FEditingScopeColumn = FEditingVerseScope;` (scope `UE::Editor::DataStorage`)
- L52 _typedef_ `using FScopeSourceInfoColumn = FScopeRowSourceInfo;` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/DataStorage/Scope/EditorDataScopeTypes.h` (Public)


#### struct `UE::Editor::DataStorage::Scope::FScopeDataVersion`  
`struct FScopeDataVersion`  
_L19-35_
- desc: Represents a versioned snapshot of scope data for a specific column type on a row. Used for change detection: compare two FScopeDataVersion values to detect if scope data has changed (including removal). The version is opaque -- callers should only use operator==, operator!=, and IsValid().
- L21 _public prototype_ `FScopeDataVersion();`
- L23 _public prototype_ `bool operator==(const FScopeDataVersion& Other) const;`
- L24 _public prototype_ `bool operator!=(const FScopeDataVersion& Other) const;`
- L27 _public prototype_ `bool IsValid() const;` — Returns true if this version refers to a valid row (i.e., was obtained from a real operation).
- L30 _public prototype_ `static FScopeDataVersion Make(RowHandle InSourceRow, uint64 InVersion);` — Factory for internal use by ICoreProvider implementations.
- L33 _private member_ `RowHandle SourceRow = InvalidRowHandle;`
- L34 _private member_ `uint64 Version = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L9 _namespace_ `namespace Scope` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/DataStorage/Scope/EditorDataScopeVersion.h` (Public)


#### struct `FScopeDataVersionColumn`  
`struct FScopeDataVersionColumn : public FEditorDataStorageColumn`  
_L15-20_
- reflection: `USTRUCT(meta = (DisplayName = "ContextDataVersion"))`
- inherits: `FEditorDataStorageColumn`
- desc: Monotonic version counter for a scope row. Bumped on every SetScopeData or RemoveScopeData call targeting this row. Part of the scope table schema — every scope row has one automatically.
- L19 _public member_ `uint64 Version = 0;`

### `Source/Runtime/TypedElementFramework/Public/DataStorage/ScopedRowHandle.h` (Public)


#### class `UE::Editor::DataStorage::FScopedRow`  
`class FScopedRow`  
_L14-55_
- desc: RAII class that removes its row from storage when going out of scope.
- L17 _public function_ `FScopedRow(ICoreProvider* InStorage, RowHandle InRow) : Storage(InStorage) , Row(InRow)`
- L23 _public function_ `FScopedRow(FScopedRow&& Other) : Storage(std::exchange(Other.Storage, nullptr)) , Row(std::exchange(Other.Row, InvalidRowHandle))`
- L29 _public function_ `FScopedRow& operator=(FScopedRow&& Other)`
- L36 _public prototype_ `FScopedRow(const FScopedRow&) = delete;`
- L37 _public prototype_ `FScopedRow& operator=(const FScopedRow&) = delete;`
- L39 _public function_ `~FScopedRow()`
- L47 _public function_ `ICoreProvider* GetStorage() const`
- L48 _public function_ `RowHandle GetRow() const`
- L50 _public function_ `explicit operator RowHandle() const`
- L53 _private member_ `ICoreProvider* Storage;`
- L54 _private member_ `RowHandle Row;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/DecoratorWidgetColumns.h` (Public)


#### struct `FEditorDataStorageUiDecoratorWidgetFactoryTag`  
`struct FEditorDataStorageUiDecoratorWidgetFactoryTag : public FEditorDataStorageTag`  
_L13-16_
- reflection: `USTRUCT(meta = (DisplayName = "Decorator Widget Factory"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag used to uniquely identify widget factories for decorator widgets

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Editor` (scope `UE`)
- L18 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _namespace_ `namespace Ui` (scope `UE::Editor::DataStorage`)
- L20 _typedef_ `using FDecoratorWidgetFactoryTag = FEditorDataStorageUiDecoratorWidgetFactoryTag;` (scope `UE::Editor::DataStorage::Ui`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TedsRevisionControlColumns.h` (Public)


#### enum `ESCCModification`  
`enum class ESCCModification`  
_L24-32_
- reflection: `UENUM()`
- L26 _public enumerator_ `None`
- L27 _public enumerator_ `Conflicted`
- L28 _public enumerator_ `Modified`
- L29 _public enumerator_ `Added`
- L30 _public enumerator_ `Removed`
- L31 _public enumerator_ `NotInDepot`

#### struct `FSccStateColumn`  
`struct FSccStateColumn final : public FEditorDataStorageColumn`  
_L44-65_
- reflection: `USTRUCT(meta = (DisplayName = "Revision control state"))`
- inherits: `FEditorDataStorageColumn`
- desc: Aggregated revision control state for a package row. Modification == ESCCModification::None means the file is source-controlled and has no local change. IconStyleName / IconOverlayName / DisplayTooltip are populated authoritatively by the active source-control provider (in its UpdateEditorDataStorage) from FSourceControlState::GetIcon() and GetDisplayTooltip(). Consumers that only need to render the row should use those directly without reinterpreting the booleans below.
- L50 _public member_ `ESCCModification Modification = ESCCModification::None;` — modification axis
- L56 _public member_ `bool bIsExternallyLocked = false;` — state axis A file can be modified (modification) and bIsLocked and bIsNotCurrent The state is viewed as an additional bit flag on top of the modification
- L57 _public member_ `bool bIsLocked = false;`
- L58 _public member_ `bool bIsExternallyEdited = false;`
- L59 _public member_ `bool bIsNotCurrent = false;`
- L61 _public member_ `FName IconStyleSetName;`
- L62 _public member_ `FName IconStyleName;`
- L63 _public member_ `FName IconOverlayName;`
- L64 _public member_ `FText DisplayTooltip;`

#### struct `FSCCStatusUpdateRequiredTag`  
`struct FSCCStatusUpdateRequiredTag final : public FEditorDataStorageTag`  
_L69-72_
- reflection: `USTRUCT(meta = (DisplayName = "SCC status update required"))`
- inherits: `FEditorDataStorageTag`
- desc: tag used to trigger a file monitoring start

#### struct `FSCCStatusUpdateEndedTag`  
`struct FSCCStatusUpdateEndedTag final : public FEditorDataStorageTag`  
_L76-79_
- reflection: `USTRUCT(meta = (DisplayName = "SCC status update ended"))`
- inherits: `FEditorDataStorageTag`
- desc: tag used to trigger a file monitoring stop

#### struct `FSccStateDirtyTag`  
`struct FSccStateDirtyTag final : public FEditorDataStorageTag`  
_L83-86_
- reflection: `USTRUCT(meta = (DisplayName = "SCC state dirty"))`
- inherits: `FEditorDataStorageTag`
- desc: tag to indicate the Scc state has changed.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Editor` (scope `UE`)
- L18 _namespace_ `namespace RevisionControl` (scope `UE::Editor`)
- L20 _variable_ `inline static const FName MappingDomain = "So` (scope `UE::Editor::RevisionControl`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementCompatibilityColumns.h` (Public)


#### struct `FTypedElementUObjectColumn`  
`struct FTypedElementUObjectColumn final : public FEditorDataStorageColumn`  
_L19-27_
- reflection: `USTRUCT(meta = (DisplayName = "UObject reference"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column containing a non-owning reference to a UObject.
- L26 _public member_ `TWeakObjectPtr<UObject> Object;` — If the UObject is accessed during an OnRemove event that is triggered by the garbage collection, the UObject will already be marked as unreachable and regular functions to retrieve the UObject will return an nullptr. In these cases use the unreachable versions such as Get( bEvenIfPendingKill  true) or GetEvenIfUnreachable().

#### struct `FTypedElementUObjectIdColumn`  
`struct FTypedElementUObjectIdColumn final : public FEditorDataStorageColumn`  
_L33-41_
- reflection: `USTRUCT(meta = (DisplayName = "UObject ID"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column containing information to uniquely identify the UObject, e.g. for use by the garbage collection.
- L38 _public member_ `uint32 Id;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`
- L40 _public member_ `int32 SerialNumber;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

#### struct `FTypedElementExternalObjectColumn`  
`struct FTypedElementExternalObjectColumn final : public FEditorDataStorageColumn`  
_L49-54_
- reflection: `USTRUCT(meta = (DisplayName = "External object reference"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column containing a non-owning reference to an arbitrary object. It's strongly recommended to also add a FTypedElementScriptStructTypeInfoColumn to make sure the type can be safely recovered.
- L53 _public member_ `void* Object;`

#### struct `FTypedElementClassDefaultObjectTag`  
`struct FTypedElementClassDefaultObjectTag final : public FEditorDataStorageTag`  
_L61-64_
- reflection: `USTRUCT(meta = (DisplayName = "Class Default Object"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to identify a row with a Class Default Object (CDO). If there's a FTypedElementUObjectColumn, the stored object will be a CDO if this tag is present.

#### struct `FTypedElementActorTag`  
`struct FTypedElementActorTag final : public FEditorDataStorageTag`  
_L71-74_
- reflection: `USTRUCT(meta = (DisplayName = "Actor"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to identify a row with an actor. If there's a FTypedElementUObjectColumn, the stored object will be an actor if this tag is present.

#### struct `FTypedElementWorldColumn`  
`struct FTypedElementWorldColumn final : public FEditorDataStorageColumn`  
_L80-85_
- reflection: `USTRUCT(meta = (DisplayName = "World"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores a reference to the world.
- L84 _public member_ `TWeakObjectPtr<UWorld> World;`

#### struct `FEditorDataStorageWorldTag`  
`struct FEditorDataStorageWorldTag final : public FEditorDataStorageTag`  
_L92-95_
- reflection: `USTRUCT(meta = (DisplayName = "World Tag"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to identify a row with a UWorld. If there's a FTypedElementUObjectColumn, the stored object will be a UWorld if this tag is present.

#### struct `FTypedElementLevelColumn`  
`struct FTypedElementLevelColumn final : public FEditorDataStorageColumn`  
_L101-106_
- reflection: `USTRUCT(meta = (DisplayName = "Level"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores a reference to a level.
- L105 _public member_ `TWeakObjectPtr<ULevel> Level;`

#### struct `FEditorDataStorageLevelTag`  
`struct FEditorDataStorageLevelTag final : public FEditorDataStorageTag`  
_L113-116_
- reflection: `USTRUCT(meta = (DisplayName = "Level Tag"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to identify a row with a ULevel. If there's a FTypedElementUObjectColumn, the stored object will be a ULevel if this tag is present.

#### struct `FTypedElementPropertyBagPlaceholderTag`  
`struct FTypedElementPropertyBagPlaceholderTag final : public FEditorDataStorageTag`  
_L124-127_
- reflection: `USTRUCT(meta = (DisplayName = "Property bag placeholder"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to signal that a row represents a property bag "placeholder-typed" object reference. This object has an unknown base type and will generally be associated with a "property bag" containing any serialized data that was loaded for it as a set of "loose" properties.

#### struct `FTypedElementLoosePropertyTag`  
`struct FTypedElementLoosePropertyTag final : public FEditorDataStorageTag`  
_L133-136_
- reflection: `USTRUCT(meta = (DisplayName = "Loose property"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to signal that a row contains an object with at least one loose property associated with it.

#### struct `FTypedElementPropertyBagPlaceholderTypeInfoColumn`  
`struct FTypedElementPropertyBagPlaceholderTypeInfoColumn final : public FEditorDataStorageColumn`  
_L145-150_
- reflection: `USTRUCT(meta = (DisplayName = "Placeholder type info"))`
- inherits: `FEditorDataStorageColumn`
- desc: A column that stores an inferred base type for placeholder-typed object references. Note that this will not be the same as the placeholder object type (stored in the class type info column). This column can be used to query for a "base type" determined from the serialization context, for systems that need to look/behave differently based on an inferred base type context (e.g. UI).
- L149 _public member_ `TWeakObjectPtr<const UStruct> InferredBaseType;`

#### struct `FEditorDataStorageUObjectIdNameColumn`  
`struct FEditorDataStorageUObjectIdNameColumn final : public FEditorDataStorageColumn`  
_L156-162_
- reflection: `USTRUCT(meta = (DisplayName = "Name"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column containing the ID Name of the UObject.
- L161 _public member_ `FName IdName;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FEditorDataStoragePieObjectTag`  
`struct FEditorDataStoragePieObjectTag final : public FEditorDataStorageTag`  
_L168-171_
- reflection: `USTRUCT(meta = (DisplayName = "PIE Object"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag on a row that to denote this is a PIE specific row (e.g PIE actors, PIE folders)

#### struct `FEditorDataStorageGuidColumn`  
`struct FEditorDataStorageGuidColumn final : public FEditorDataStorageColumn`  
_L177-181_
- reflection: `USTRUCT(meta = (DisplayName = "Guid"))`
- inherits: `FEditorDataStorageColumn`
- desc: Tag on a row that stores the editor only guid of the row
- L180 _public member_ `FGuid Guid;`

#### Free symbols / members of external scopes

- L183 _namespace_ `namespace UE`
- L183 _namespace_ `namespace Editor` (scope `UE`)
- L183 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L185 _typedef_ `using FUObjectIdNameColumn = FEditorDataStorageUObjectIdNameColumn;` (scope `UE::Editor::DataStorage`)
- L186 _typedef_ `using FLevelColumn = FTypedElementLevelColumn;` (scope `UE::Editor::DataStorage`)
- L187 _typedef_ `using FLevelTag = FEditorDataStorageLevelTag;` (scope `UE::Editor::DataStorage`)
- L188 _typedef_ `using FWorldTag = FEditorDataStorageWorldTag;` (scope `UE::Editor::DataStorage`)
- L189 _typedef_ `using FPieObjectTag = FEditorDataStoragePieObjectTag;` (scope `UE::Editor::DataStorage`)
- L190 _typedef_ `using FGuidColumn = FEditorDataStorageGuidColumn;` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementFolderColumns.h` (Public)


#### struct `FFolderTag`  
`struct FFolderTag final : public FEditorDataStorageTag`  
_L13-16_
- reflection: `USTRUCT(meta = (DisplayName = "Folder"))`
- inherits: `FEditorDataStorageTag`
- desc: Column that signifies this row is for a folder

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementHandleColumn.h` (Public)


#### struct `FTedsTypedElementColumn`  
`struct FTedsTypedElementColumn : public FEditorDataStorageColumn`  
_L13-18_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: A column which contains a TypedElementHandle from the TypedElementFramework Prefer to use the namespaced alias when referencing in code - UE::Editor::DataStorage::Compatibility::FTypedElementColumn
- L17 _public member_ `FTypedElementHandle Handle;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Editor` (scope `UE`)
- L20 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L20 _namespace_ `namespace Compatibility` (scope `UE::Editor::DataStorage`)
- L22 _typedef_ `using FTypedElementColumn = FTedsTypedElementColumn;` (scope `UE::Editor::DataStorage::Compatibility`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementHiearchyColumns.h` (Public)


#### struct `FTableRowParentColumn`  
`struct FTableRowParentColumn final : public FEditorDataStorageColumn`  
_L16-21_
- reflection: `USTRUCT(meta = (DisplayName = "Parent"))`
- inherits: `FEditorDataStorageColumn`
- desc: A reference to the direct hierarchical parent of this row.
- L20 _public member_ `UE::Editor::DataStorage::RowHandle Parent;`

#### struct `FUnresolvedTableRowParentColumn`  
`struct FUnresolvedTableRowParentColumn final : public FEditorDataStorageColumn`  
_L28-33_
- reflection: `USTRUCT(meta = (DisplayName = "Parent (Unresolved)"))`
- inherits: `FEditorDataStorageColumn`
- desc: A reference to the direct hierarchical parent of this row which has not been resolved yet. The stored value will be used to attempt to find the indexed row. This column can not be used to find rows that are not indexed.
- L32 _public member_ `UE::Editor::DataStorage::FMapKey ParentIdKey;`

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementIconOverrideColumns.h` (Public)


#### struct `FTypedElementIconOverrideColumn`  
`struct FTypedElementIconOverrideColumn final : public FEditorDataStorageColumn`  
_L14-21_
- reflection: `USTRUCT(meta = (DisplayName = "Icon override"))`
- inherits: `FEditorDataStorageColumn`
- desc: When present this column overrides any icon that would normally be used to represent the row.
- L20 _public member_ `FName IconName;` — `UPROPERTY()` — Name of the replacement icon.

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementLabelColumns.h` (Public)


#### struct `FTypedElementLabelColumn`  
`struct FTypedElementLabelColumn final : public FEditorDataStorageColumn`  
_L15-21_
- reflection: `USTRUCT(meta = (DisplayName = "Label"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores a label.
- L20 _public member_ `FString Label;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FTypedElementLabelHashColumn`  
`struct FTypedElementLabelHashColumn final : public FEditorDataStorageColumn`  
_L28-34_
- reflection: `USTRUCT(meta = (DisplayName = "Label hash"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores the hash of a label. This is typically paired with FTypedElementLabelColumn, but kept separate in order to iterate quickly over all hash values.
- L33 _public member_ `uint64 LabelHash;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementMiscColumns.h` (Public)


#### struct `FTypedElementSyncBackToWorldTag`  
`struct FTypedElementSyncBackToWorldTag final : public FEditorDataStorageTag`  
_L17-20_
- reflection: `USTRUCT(meta = (DisplayName = "Sync back to world"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to indicate that there are one or more bits of information in the row that need to be copied out the Data Storage and into the original object. This tag will automatically be removed at the end of a tick.

#### struct `FTypedElementSyncFromWorldTag`  
`struct FTypedElementSyncFromWorldTag final : public FEditorDataStorageTag`  
_L29-32_
- reflection: `USTRUCT(meta = (DisplayName = "Sync from world"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to signal that data a processor copies out of the world must be synced to the data storage. Useful for when an Actor was recently spawned or reloaded in the world. Currently used if any property changes since there is no mechanism to selectively run queries for specific changed properties.

#### struct `FTypedElementSyncFromWorldInteractiveTag`  
`struct FTypedElementSyncFromWorldInteractiveTag final : public FEditorDataStorageTag`  
_L43-46_
- reflection: `USTRUCT(meta = (DisplayName = "Sync from world (interactive)"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to signal that data a processor copies out of the world must be synced to the data storage. Useful for when an Actor was recently spawned or reloaded in the world. This version is not automatically removed and intended for interactive operations that will take a few frames to complete such as dragging. Currently used if any property changes since there is no mechanism to selectively run queries for specific changed properties.

#### struct `FTypedElementRowReferenceColumn`  
`struct FTypedElementRowReferenceColumn final : public FEditorDataStorageColumn`  
_L52-57_
- reflection: `USTRUCT(meta = (DisplayName = "Row reference"))`
- inherits: `FEditorDataStorageColumn`
- desc: A general reference to another row.
- L56 _public member_ `UE::Editor::DataStorage::RowHandle Row;`

#### struct `FNameColumn`  
`struct UE_DEPRECATED(5.7, "Use of the FNameColumn has been deprecated, please create a new column for your purpose.") FNameColumn final : public FEditorDataStorageColumn`  
_L63-78_
- reflection: `USTRUCT(meta = (DisplayName = "Name"))`
- inherits: `FEditorDataStorageColumn`
- desc: A name for this row.
- L68 _public member_ `FName Name;` — `UPROPERTY(meta = (Searchable, DeprecatedProperty))`
- L71 _public prototype_ `FNameColumn() = default;`
- L72 _public prototype_ `~FNameColumn() = default;`
- L73 _public prototype_ `FNameColumn(const FNameColumn&) = default;`
- L74 _public prototype_ `FNameColumn(FNameColumn&&) = default;`
- L75 _public prototype_ `FNameColumn& operator=(const FNameColumn&) = default;`
- L76 _public prototype_ `FNameColumn& operator=(FNameColumn&&) = default;`

#### struct `FFavoriteTag`  
`struct FFavoriteTag final : public FEditorDataStorageTag`  
_L84-87_
- reflection: `USTRUCT(meta = (DisplayName = "Favorite"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag used to mark a row as "favorite" in TEDS - which can then be used to filter in table views.

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementOverrideColumns.h` (Public)


#### struct `FObjectOverrideColumn`  
`struct FObjectOverrideColumn final : public FEditorDataStorageColumn`  
_L12-17_
- reflection: `USTRUCT(meta = (DisplayName = "Override"))`
- inherits: `FEditorDataStorageColumn`
- desc: Whether the object has an override on the base
- L16 _public member_ `EOverriddenState OverriddenState;`

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementPackageColumns.h` (Public)


#### struct `FTypedElementPackageUnresolvedReference`  
`struct FTypedElementPackageUnresolvedReference final : public FEditorDataStorageColumn`  
_L27-32_
- reflection: `USTRUCT(meta = (DisplayName = "Unresolved package path reference"))`
- inherits: `FEditorDataStorageColumn`
- desc: A package reference column that has not yet been resolved to reference a package.
- L31 _public member_ `FString PathOnDisk;`

#### struct `FTypedElementPackageReference`  
`struct FTypedElementPackageReference final : public FEditorDataStorageColumn`  
_L38-43_
- reflection: `USTRUCT(meta = (DisplayName = "Package path reference"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that references a row in the table that provides package and source control information.
- L42 _public member_ `UE::Editor::DataStorage::RowHandle Row;`

#### struct `FTypedElementPackageUpdatedTag`  
`struct FTypedElementPackageUpdatedTag final : public FEditorDataStorageTag`  
_L49-52_
- reflection: `USTRUCT(meta = (DisplayName = "Package information has been updated"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag that indicates some related package information has been modified.

#### struct `FTypedElementPackagePathColumn`  
`struct FTypedElementPackagePathColumn final : public FEditorDataStorageColumn`  
_L58-64_
- reflection: `USTRUCT(meta = (DisplayName = "Package path"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores the path of a package.
- L63 _public member_ `FString Path;` — `UPROPERTY(meta = (Searchable))`

#### struct `FTypedElementPackageFilePathOnDiskColumn`  
`struct FTypedElementPackageFilePathOnDiskColumn final : public FEditorDataStorageColumn`  
_L70-76_
- reflection: `USTRUCT(meta = (DisplayName = "Package file path on disk"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores the fully normalized file path of a package as seen by the operating system.
- L75 _public member_ `FString FilePathOnDisk;` — `UPROPERTY(meta = (Searchable))`

#### struct `FTypedElementPackageLoadedPathColumn`  
`struct FTypedElementPackageLoadedPathColumn final : public FEditorDataStorageColumn`  
_L87-92_
- reflection: `USTRUCT(meta = (DisplayName = "Package loaded path"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores the full loading path to a package.
- L91 _public member_ `FPackagePath LoadedPath;`

#### struct `FTedsPackageDirtyTag`  
`struct FTedsPackageDirtyTag final : public FEditorDataStorageTag`  
_L98-101_
- reflection: `USTRUCT(meta = (DisplayName = "In Dirty Package"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to indicate that the data on the row is in a package that was marked unsaved/marked dirty

#### struct `FTedsPrimaryPackageObjectTag`  
`struct FTedsPrimaryPackageObjectTag final : public FEditorDataStorageTag`  
_L107-110_
- reflection: `USTRUCT(meta = (DisplayName = "Primary Package Object"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to indicate that the data on the row is the primary object in a package

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Editor` (scope `UE`)
- L17 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L19 _variable_ `inline static const FName PackageTableName = TEXT("Edi` (scope `UE::Editor::DataStorage`)
- L20 _variable_ `inline static const FName PackageHierarchyName = TEXT("Pac` (scope `UE::Editor::DataStorage`)
- L78 _function_ `inline uint32 GetTypeHash(const FTypedElementPackagePathColumn& InStruct)`

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementPivotOffsetColumns.h` (Public)


#### struct `FTypedElementPivotOffset`  
`struct FTypedElementPivotOffset final : public FEditorDataStorageColumn`  
_L10-16_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- L15 _public member_ `FVector Offset;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementSelectionColumns.h` (Public)


#### struct `FTypedElementSelectionColumn`  
`struct FTypedElementSelectionColumn final : public FEditorDataStorageColumn`  
_L14-21_
- reflection: `USTRUCT(meta = (DisplayName = "Selected"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column to represent that a row is selected
- L20 _public member_ `FName SelectionSet;` — `UPROPERTY()` — The selection set this row belongs to, empty = default selection set

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementSlateWidgetColumns.h` (Public)


#### struct `FTypedElementSlateWidgetReferenceColumn`  
`struct FTypedElementSlateWidgetReferenceColumn final : public FEditorDataStorageColumn`  
_L26-38_
- reflection: `USTRUCT(meta = (DisplayName = "Slate widget reference"))`
- inherits: `FEditorDataStorageColumn`
- desc: Stores a widget reference in the data storage. At the start of processing any columns that are not pointing to a valid widget will be removed. If the FTypedElementSlateWidgetDeletesRowTag is found then the entire row will be deleted.
- L31 _public member_ `TWeakPtr<SWidget> Widget;` — The actual internal widget
- L34 _public member_ `TWeakPtr<UE::Editor::DataStorage::ITedsWidget> TedsWidget;` — Reference to the container widget that holds the internal widget
- L37 _public member_ `TWeakPtr<FTypedElementWidgetConstructor> WidgetConstructor;` — Reference to the widget constructor that was used to create this widget (if applicable)

#### struct `FTypedElementSlateWidgetReferenceDeletesRowTag`  
`struct FTypedElementSlateWidgetReferenceDeletesRowTag final : public FEditorDataStorageTag`  
_L46-49_
- reflection: `USTRUCT(meta = (DisplayName = "Slate widget reference deletes row"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to indicate that the entire row needs to be deleted when the widget in FTypedElementSlateWidgetReferenceColumn is no longer valid, otherwise only the column will be removed.

#### struct `FDisplayNameColumn`  
`struct FDisplayNameColumn final : public FEditorDataStorageColumn`  
_L55-61_
- reflection: `USTRUCT(meta = (DisplayName = "Display Name"))`
- inherits: `FEditorDataStorageColumn`
- desc: A localized display name for this row.
- L60 _public member_ `FText DisplayName;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FDescriptionColumn`  
`struct FDescriptionColumn final : public FEditorDataStorageColumn`  
_L67-73_
- reflection: `USTRUCT(meta = (DisplayName = "Description"))`
- inherits: `FEditorDataStorageColumn`
- desc: A localized description for this row.
- L72 _public member_ `FText Description;` — `UPROPERTY(meta = (Searchable))`

#### struct `FHighlightTextColumn`  
`struct FHighlightTextColumn final : public FEditorDataStorageColumn`  
_L79-85_
- reflection: `USTRUCT(meta = (DisplayName = "Highlight Text"))`
- inherits: `FEditorDataStorageColumn`
- desc: A highlight text for this row.  Can be used by widget rows to set the corresponding HighlightText on a widget (e.g. STextBlock)
- L84 _public member_ `FText HighlightText;` — `UPROPERTY()`

#### struct `FSlateColorColumn`  
`struct FSlateColorColumn final : public FEditorDataStorageColumn`  
_L92-98_
- reflection: `USTRUCT(meta = (DisplayName = "Color"))`
- inherits: `FEditorDataStorageColumn`
- desc: A color for this row. Can be used by widget rows to determine widget color or non-widget rows to attach a logical color to their data (e.g asset colors)
- L97 _public member_ `FSlateColor Color = FSlateColor::UseForeground();` — `UPROPERTY()`

#### struct `FIsInEditingModeTag`  
`struct FIsInEditingModeTag final : public FEditorDataStorageTag`  
_L104-107_
- reflection: `USTRUCT(meta = (DisplayName = "Is Editing"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag added onto widget rows if they are currently in editing mode (e.g editable text boxes)

#### struct `FWidgetPurposeReferenceColumn`  
`struct FWidgetPurposeReferenceColumn final : public FEditorDataStorageColumn`  
_L113-118_
- reflection: `USTRUCT(meta = (DisplayName = "Widget Purpose Reference"))`
- inherits: `FEditorDataStorageColumn`
- desc: A reference to the widget purpose this widget was created for
- L117 _public member_ `UE::Editor::DataStorage::RowHandle PurposeRowHandle;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementTransformColumns.h` (Public)


#### struct `FTypedElementLocalTransformColumn`  
`struct FTypedElementLocalTransformColumn final : public FEditorDataStorageColumn`  
_L15-25_
- reflection: `USTRUCT(meta = (DisplayName = "Local Transform"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores a local transform.
- L24 _public member_ `FTransform Transform { NoInit };` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))` — Transform is not being initialized to avoid spending time on initialization when the Transform will be updated the first and following ticks afr it's creation. If this isn't initialized at the correct time, then the sync from source or the true initialization need to be moved to an earlier phase or group.

#### struct `FTypedElementLockTransformTag`  
`struct FTypedElementLockTransformTag final : public FEditorDataStorageTag`  
_L29-32_
- reflection: `USTRUCT(meta = (DisplayName = "Lock Transform"))`
- inherits: `FEditorDataStorageTag`

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementTypeInfoColumns.h` (Public)


#### struct `FTypedElementClassTypeInfoColumn`  
`struct FTypedElementClassTypeInfoColumn final : public FEditorDataStorageColumn`  
_L17-22_
- reflection: `USTRUCT(meta = (DisplayName = "Type"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores type information for classes.
- L21 _public member_ `TWeakObjectPtr<const UClass> TypeInfo;`

#### struct `FTypedElementScriptStructTypeInfoColumn`  
`struct FTypedElementScriptStructTypeInfoColumn final : public FEditorDataStorageColumn`  
_L28-33_
- reflection: `USTRUCT(meta = (DisplayName = "ScriptStruct type info"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores type information for structs.
- L32 _public member_ `TWeakObjectPtr<const UScriptStruct> TypeInfo;`

#### struct `FTypedElementTypeInfoDisplayOverrideColumn`  
`struct FTypedElementTypeInfoDisplayOverrideColumn final : public FEditorDataStorageColumn`  
_L41-46_
- reflection: `USTRUCT(meta = (DisplayName = "Type Display Override"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores a type display name that should override the main Class Type Info column Note: Can be used to display types that aren't a UClass or UStruct (i.e. folders)
- L45 _public member_ `FText TypeDisplayName;`

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementUIColumns.h` (Public)


#### struct `FHideRowFromUITag`  
`struct FHideRowFromUITag final : public FEditorDataStorageTag`  
_L14-17_
- reflection: `USTRUCT(meta = (DisplayName = "Hide row from UI"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to indicate that this row should not show up in any TEDS UI that displays rows (e.g table viewer)

#### struct `FExpandedInUITag`  
`struct FExpandedInUITag : public FEditorDataStorageTag`  
_L23-26_
- reflection: `USTRUCT(meta = (DisplayName = "Expanded item"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag on to indicate that this row should be expanded in the UI

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementValueCacheColumns.h` (Public)


#### struct `FTypedElementU32IntValueCacheColumn`  
`struct FTypedElementU32IntValueCacheColumn final : public FEditorDataStorageColumn`  
_L14-20_
- reflection: `USTRUCT(meta = (DisplayName = "Uint32 value cache"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that can be used to cache an unsigned 32-bit value in.
- L19 _public member_ `uint32 Value;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

#### struct `FTypedElementI32IntValueCacheColumn`  
`struct FTypedElementI32IntValueCacheColumn final : public FEditorDataStorageColumn`  
_L26-32_
- reflection: `USTRUCT(meta = (DisplayName = "Int32 value cache"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that can be used to cache a signed 32-bit value in.
- L31 _public member_ `int32 Value;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

#### struct `FTypedElementU64IntValueCacheColumn`  
`struct FTypedElementU64IntValueCacheColumn final : public FEditorDataStorageColumn`  
_L38-44_
- reflection: `USTRUCT(meta = (DisplayName = "Uint64 value cache"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that can be used to cache an unsigned 64-bit value in.
- L43 _public member_ `uint64 Value;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

#### struct `FTypedElementI64IntValueCacheColumn`  
`struct FTypedElementI64IntValueCacheColumn final : public FEditorDataStorageColumn`  
_L50-56_
- reflection: `USTRUCT(meta = (DisplayName = "Int64 value cache"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that can be used to cache a signed 64-bit value in.
- L55 _public member_ `int64 Value;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

#### struct `FTypedElementFloatValueCacheColumn`  
`struct FTypedElementFloatValueCacheColumn final : public FEditorDataStorageColumn`  
_L62-68_
- reflection: `USTRUCT(meta = (DisplayName = "float value cache"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that can be used to cache a 32-bit floating point value in.
- L67 _public member_ `float Value;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementViewportColumns.h` (Public)


#### struct `FTypedElementViewportOutlineColorColumn`  
`struct FTypedElementViewportOutlineColorColumn final : public FEditorDataStorageColumn`  
_L13-19_
- reflection: `USTRUCT(meta = (DisplayName = "Viewport Outline Color"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column to hold the color that the object is outlined with in the viewport
- L18 _public member_ `uint8 SelectionOutlineColorIndex = 0;` — `UPROPERTY(meta = (ClampMin = "0", ClampMax = "7"))`

#### struct `FTypedElementViewportOverlayColorColumn`  
`struct FTypedElementViewportOverlayColorColumn final : public FEditorDataStorageColumn`  
_L25-31_
- reflection: `USTRUCT(meta = (DisplayName = "Viewport Overlay Color"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column to hold the color that the object is overlaid with in the viewport
- L30 _public member_ `FColor OverlayColor = FColor(EForceInit::ForceInitToZero);` — `UPROPERTY()`

#### struct `FTypedElementViewportOverlayColorDirtyFlag`  
`struct FTypedElementViewportOverlayColorDirtyFlag final : public FEditorDataStorageTag`  
_L37-40_
- reflection: `USTRUCT(meta = (DisplayName = "Viewport Overlay Color Dirty Flag"))`
- inherits: `FEditorDataStorageTag`
- desc: Flag to mark current color dirty and trigger a rendering refresh

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementVisibilityColumns.h` (Public)


#### struct `FVisibleInEditorColumn`  
`struct FVisibleInEditorColumn final : public FEditorDataStorageColumn`  
_L18-25_
- reflection: `USTRUCT(meta = (DisplayName = "Visibility"))`
- inherits: `FEditorDataStorageColumn`
- desc: VisibleInEditor column that signifies whether or not this row's object should be visible in view ports
- L24 _public member_ `bool bIsVisibleInEditor = true;` — `UPROPERTY(meta = (Sortable))`

#### struct `FVisibilityChangedTag`  
`struct FVisibilityChangedTag final : public FEditorDataStorageTag`  
_L34-37_
- reflection: `USTRUCT(meta = (DisplayName = "Visibility Changed"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag added to rows for a frame when their visibility value changes. This tag is required to be added for any changes you make to the TEDS column to be propagated back to the world, and is then removed at the end of the frame.

#### class `UE::Editor::DataStorage::FVisibilityColumnChange`  
`class FVisibilityColumnChange : public FCommandChange`  
_L44-67_
- inherits: `FCommandChange`
- desc: Change object for undo/redo of TEDS visibility column modifications.
- L52 _public function_ `FVisibilityColumnChange(FRowHandleArray&& ChangedRowsIn, bool bVisibleOnApplyIn) : Rows(MoveTemp(ChangedRowsIn)) , bVisibleOnApply(bVisibleOnApplyIn)` — Note that ChangedRowsIn should only include rows whose visibilty state actually changed. Including rows whose visibility was already bVisibleOnApply before the transaction will cause undo to place the rows in unmatching state on undo.
- L57 _public prototype_ `void Apply(UObject* Object) override;`
- L58 _public prototype_ `void Revert(UObject* Object) override;`
- L59 _public function_ `FString ToString() const override`
- L65 _private member_ `FRowHandleArray Rows;`
- L66 _private member_ `bool bVisibleOnApply;`

#### Free symbols / members of external scopes

- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace Editor` (scope `UE`)
- L40 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/TypedElementWebColumns.h` (Public)


#### struct `FEditorDataStorageUrlColumn`  
`struct FEditorDataStorageUrlColumn final : public FEditorDataStorageColumn`  
_L14-20_
- reflection: `USTRUCT(meta = (DisplayName = "Url"))`
- inherits: `FEditorDataStorageColumn`
- desc: Information for retrieving a web page from the web.
- L19 _public member_ `FString UrlString;` — `UPROPERTY()`

#### struct `FEditorDataStorageWebImageColumn`  
`struct FEditorDataStorageWebImageColumn final : public FEditorDataStorageColumn`  
_L27-42_
- reflection: `USTRUCT(meta = (DisplayName = "WebImage", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageColumn`
- desc: Information for retrieving an image from the web. The width and height can optionally be set to non-zero indicating that the size should overwrite the size from the source image.
- L33 _public member_ `FString UrlString;` — `UPROPERTY()` — URL to the image in string form. Can be used with for instance with WebImage(Cache) to create a local image.
- L37 _public member_ `uint16 Width;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))` — If set, the target width for the image. A value of zero indicates that the width from the source image should be used.
- L41 _public member_ `uint16 Height;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))` — If set, the target height for the image. A value of zero indicates that the height from the source image should be used.

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace Editor` (scope `UE`)
- L44 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L46 _typedef_ `using FUrlColumn = FEditorDataStorageUrlColumn;` (scope `UE::Editor::DataStorage`)
- L47 _typedef_ `using FWebImageColumn = FEditorDataStorageWebImageColumn;` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Columns/WidgetPurposeColumns.h` (Public)


#### struct `FWidgetPurposeColumn`  
`struct FWidgetPurposeColumn : public FEditorDataStorageColumn`  
_L11-20_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column used to store the type of a widget purpose
- L16 _public member_ `UE::Editor::DataStorage::IUiProvider::EPurposeType PurposeType;` — The type of the purpose, used to determine how factories are registered for it
- L19 _public member_ `UE::Editor::DataStorage::IUiProvider::FPurposeID PurposeID;` — The unique ID of this purpose that can be used to reference it instead of the row handle

#### struct `FWidgetPurposeNameColumn`  
`struct FWidgetPurposeNameColumn : public FEditorDataStorageColumn`  
_L24-36_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column used to store the name of a widget purpose split into 3 parts (E.g "SceneOutliner.Cell.Large")
- L29 _public member_ `FName Namespace;` — `UPROPERTY(meta = (Searchable, Sortable))`
- L32 _public member_ `FName Name;` — `UPROPERTY(meta = (Searchable, Sortable))`
- L35 _public member_ `FName Frame;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FWidgetFactoryColumn`  
`struct FWidgetFactoryColumn : public FEditorDataStorageColumn`  
_L40-46_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column to store info about a widget factory
- L45 _public member_ `UE::Editor::DataStorage::RowHandle PurposeRowHandle;` — Row handle of the purpose the widget factory belongs to

#### struct `FWidgetFactoryConstructorTypeInfoColumn`  
`struct FWidgetFactoryConstructorTypeInfoColumn : public FEditorDataStorageColumn`  
_L50-55_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column used to store the widget constructor used by a widget factory by its TypeInfo
- L54 _public member_ `TWeakObjectPtr<const UScriptStruct> Constructor;`

#### struct `FWidgetConstructorNameColumn`  
`struct FWidgetConstructorNameColumn : public FEditorDataStorageColumn`  
_L59-65_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column used to store the name of the widget constructor
- L64 _public member_ `FName Name;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FWidgetFactoryConditionsColumn`  
`struct FWidgetFactoryConditionsColumn : public FEditorDataStorageColumn`  
_L71-76_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column used to store the query conditions used by a widget factory If the column is not present the factory doesn't match against any conditions (i.e is a general purpose factory)
- L75 _public member_ `UE::Editor::DataStorage::Queries::FConditions Conditions;`

#### struct `FWidgetFactoryConstructorColumn`  
`FWidgetFactoryConstructorColumn : public FEditorDataStorageColumn`  
_L82-96_
- reflection: `USTRUCT()`
- reflection: `UE_DEPRECATED(5.7, "Use of the FWidgetFactoryConstructorColumn has been deprecated, use FWidgetFactoryConstructorTypeInfoColumn to store the constructor by type instead.")`
- inherits: `FEditorDataStorageColumn`
- L86 _public member_ `TUniquePtr<FTypedElementWidgetConstructor> Constructor;`
- L89 _public prototype_ `FWidgetFactoryConstructorColumn() = default;`
- L90 _public prototype_ `~FWidgetFactoryConstructorColumn() = default;`
- L91 _public prototype_ `FWidgetFactoryConstructorColumn(const FWidgetFactoryConstructorColumn&) = delete;`
- L92 _public prototype_ `FWidgetFactoryConstructorColumn(FWidgetFactoryConstructorColumn&&) = default;`
- L93 _public prototype_ `FWidgetFactoryConstructorColumn& operator=(const FWidgetFactoryConstructorColumn&) = delete;`
- L94 _public prototype_ `FWidgetFactoryConstructorColumn& operator=(FWidgetFactoryConstructorColumn&&) = default;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FWidgetFactoryConstructorColumn> : public TStructOpsTypeTraitsBase2<FWidgetFactoryConstructorColumn>`  
_L100-106_
- inherits: `TStructOpsTypeTraitsBase2<FWidgetFactoryConstructorColumn>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L103-105_

#### Free symbols / members of external scopes

- L104 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon5d7665690103`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Common/EditorDataStorageFeatures.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/TypedElementFramework/Public/Elements/Common/TypedElementCommonTypes.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/TypedElementFramework/Public/Elements/Common/TypedElementDataStorageLog.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/TypedElementFramework/Public/Elements/Common/TypedElementHandles.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/TypedElementFramework/Public/Elements/Common/TypedElementMapKey.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/TypedElementFramework/Public/Elements/Common/TypedElementQueryConditions.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/TypedElementFramework/Public/Elements/Common/TypedElementQueryDescription.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/TypedElementFramework/Public/Elements/Common/TypedElementQueryTypes.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementAttributeBinding.h` (Public)


#### class `UE::Editor::DataStorage::FAttributeBinder`  
`class FAttributeBinder`  
_L24-308_
- desc: Builder class that can be used as a shorthand to bind data inside a TEDS row, column pair to a TAttribute so the attribute updates if the data in the column is changed. Usage Example: FAttributeBinder Binder(RowHandle); TAttribute<int> TestAttribute(Binder.BindData(&FTestColumnInt::TestInt))
- L29 _public prototype_ `FAttributeBinder(RowHandle InTargetRow);` — Create an attribute binder for a given row.
- L32 _public prototype_ `FAttributeBinder(RowHandle InTargetRow, ICoreProvider* InDataStorage);` — Create an attribute binder for a given row.
- L45 _public prototype_ `template <typename AttributeType, TDataColumnType ColumnType> TAttribute<AttributeType> BindData(AttributeType ColumnType::* InVariable, const AttributeType& InDefaultValue = AttributeType());` — Bind a specific data member inside a TEDS column to an attribute of the same type as the data @param InVariable The data member inside a column to be bound @param InDefaultValue The default value to be used when the column isn't present on a row Example: FAttributeBinder Binder(RowHandle); TAttribute<FString> TestAttribute(Binder.BindData(&FTypedElementLabelColumn::Label))
- L60 _public prototype_ `template <typename AttributeType, TDynamicColumnTemplate ColumnType> TAttribute<AttributeType> BindData(const FName& InIdentifier, AttributeType ColumnType::* InVariable, const AttributeType& InDefaultValue = AttributeType());` — Bind a specific data member inside a TEDS column to an attribute of the same type as the data @param InVariable The data member inside a column to be bound @param InDefaultValue The default value to be used when the column isn't present on a row @param InIdentifier The identifier for this dynamic column @return A TAttribute bound to the row, column pair specified Example: FAttributeBinder Binder(RowHandle); TAttribute<FString> TestAttribute(Binder.BindData(&FTypedElementLabelColumn::Label, FName("Id")))
- L81 _public prototype_ `template <typename AttributeType, typename DataType, TDataColumnType ColumnType> TAttribute<AttributeType> BindData(DataType ColumnType::* InVariable, TFunction<AttributeType(const DataType&)> InConverter, const DataType& InDefaultValue = DataType());` — Bind a specific data member inside a TEDS column to an attribute of a different type than the data by providing a conversion function NOTE: the default value is not the actual attribute type but rather the data type in the column and it gets passed to the conversion function @param InVariable The data member inside a column to be bound @param InConverter Conversion function to convert from DataType -> AttributeType @param InDefaultValue The default value to be used when the column isn't present on a row @return A TAttribute bound to the row, column pair specified Example: UE::Editor::DataStorage::FAttributeBinder Binder(RowHandle); TAttribute<FText> TestAttribute(Binder.BindData(&FTypedElementLabelColumn::Label), [](const FString& Data) { return FText::FromString(Data); } ));
- L103 _public prototype_ `template <typename AttributeType, typename DataType, TDynamicColumnTemplate ColumnType> TAttribute<AttributeType> BindData(const FName& InIdentifier, DataType ColumnType::* InVariable, TFunction<AttributeType(const DataType&)> InConverter, const DataType& InDefaultValue = DataType());` — Bind a specific data member inside a TEDS column to an attribute of a different type than the data by providing a conversion function NOTE: the default value is not the actual attribute type but rather the data type in the column and it gets passed to the conversion function @param InVariable The data member inside a column to be bound @param InConverter Conversion function to convert from DataType -> AttributeType @param InIdentifier The identifier for this column if it is a dynamic column @param InDefaultValue The default value to be used when the column isn't present on a row @return A TAttribute bound to the row, column pair specified Example: UE::Editor::DataStorage::FAttributeBinder Binder(RowHandle); TAttribute<FText> TestAttribute(Binder.BindData(&FTypedElementLabelColumn::Label), [](const FString& Data) { return FText::FromString(Data); } ));
- L114 _public prototype_ `template <typename DataType, TDataColumnType ColumnType, typename FunctionType> requires DataStorage::Private::AttributeBinderInvocable<FunctionType, DataType> auto BindData(DataType ColumnType::* InVariable, FunctionType&& InConverter, const DataType& InDefaultValue = DataType());` — Overload for the conversion binder to accept lambdas instead of TFunctions @param InVariable The data member inside a column to be bound @param InConverter Conversion function to convert from DataType -> AttributeType @param InDefaultValue The default value to be used when the column isn't present on a row\
- L127 _public prototype_ `template <typename DataType, TDynamicColumnTemplate ColumnType, typename FunctionType> requires DataStorage::Private::AttributeBinderInvocable<FunctionType, DataType> auto BindData(const FName& InIdentifier, DataType ColumnType::* InVariable, FunctionType&& InConverter, const DataType& InDefaultValue = DataType());` — Overload for the conversion binder to accept lambdas instead of TFunctions @param InVariable The data member inside a column to be bound @param InConverter Conversion function to convert from DataType -> AttributeType @param InDefaultValue The default value to be used when the column isn't present on a row\ @param InIdentifier The identifier for this column if it is a dynamic column, NAME_None if it is not a dynamic column @return A TAttribute bound to the row, column pair specified
- L143 _public prototype_ `template <typename AttributeType, TDataColumnType ColumnType> TAttribute<AttributeType> BindColumn(TFunction<AttributeType(const ColumnType&)> InConverter);` — Bind a whole TEDS column to a slate attribute (instead of a single member variable). This allows you to derive an attribute from multiple members of a TEDS column @param InConverter Conversion function to convert from ColumnType -> AttributeType @return A TAttribute bound to the row, column pair specified Example: const TAttribute TestIntAttribute(Binder.BindColumn<FTestColumnInt>([](const FTestColumnInt& Column) { return Column.TestInt1 + Column.TestInt2; }
- L152 _public prototype_ `template <TDataColumnType ColumnType, typename FunctionType> requires DataStorage::Private::AttributeBinderColumnInvocable<FunctionType, ColumnType> auto BindColumn(FunctionType&& InConverter);` — Overload for the BindColumn to accept lambdas instead of TFunctions @param InConverter Conversion function to convert from DataType -> AttributeType @return A TAttribute bound to the row, column pair specified
- L168 _public prototype_ `template <typename AttributeType, TColumnType... ColumnTypes> TAttribute<AttributeType> BindColumnsPresence(TFunction<AttributeType(const bool)> InConverter);` — Bind the presence of a TEDS tag or column to a slate attribute (instead of a single member variable). This allows you to derive an attribute from the presence of a tag on a row @param InConverter Conversion function to convert from a bool (aka bHasColumn) -> AttributeType @return A TAttribute bound to the row, column pair specified Example: const TAttribute TestHasIntAttribute(Binder.BindColumnsPresence<FTestHasIntTag>([](bool bHasColumn) { return bHasColumn ? Image1 : Image2; }));
- L177 _public prototype_ `template <TColumnType... ColumnTypes, typename FunctionType> requires DataStorage::Private::AttributeBinderColumnPresenceInvocable<FunctionType> auto BindColumnsPresence(FunctionType&& InConverter);` — Overload for the BindColumnPresence to accept lambdas instead of TFunctions @param InConverter Conversion function to convert from a bool (aka bHasColumn) -> AttributeType @return A TAttribute bound to the row, column pair specified
- L186 _public prototype_ `template <typename AttributeType> TAttribute<AttributeType> BindColumnsPresence(Queries::FConditions InConditions, TFunction<AttributeType(const bool)> InConverter);` — Overload for the BindColumnPresence to accept FConditions instead of TColumnTypes @param InConditions Conditions to check the row if it matches (can include dynamic columns) @param InConverter Conversion function to convert from a bool (aka bHasColumn) -> AttributeType @return A TAttribute bound to the row, column pair specified
- L196 _public prototype_ `template <typename FunctionType> requires DataStorage::Private::AttributeBinderColumnPresenceInvocable<FunctionType> auto BindColumnsPresence(Queries::FConditions InConditions, FunctionType&& InConverter);` — Overload for the BindColumnPresence(FConditions) to accept lambdas instead of TFunctions @param InConditions Conditions to check the row if it matches (can include dynamic columns) @param InConverter Conversion function to convert from a bool (aka bHasColumn) -> AttributeType @return A TAttribute bound to the row, column pair specified
- L213 _public prototype_ `template <typename AttributeType> TAttribute<AttributeType> BindColumnData(const TWeakObjectPtr<const UScriptStruct>& InColumnType, const TFunction<AttributeType(const TWeakObjectPtr<const UScriptStruct>&, const void*)>& InConverter);` — Bind a whole TEDS column to a slate attribute (instead of a single member variable) using the column's typeinfo. @param InColumnType The typeinfo of the column (e.g FTestIntColumn::StaticStruct) @param InConverter Conversion function to convert from const void* ColumnData -> AttributeType @return A TAttribute bound to the row, column pair specified Example: const TAttribute TestIntAttribute(Binder.BindColumnData(FTestColumnInt::StaticStruct(), [](const TWeakObjectPtr<const UScriptStruct>& ColumnType, const void* ColumnData) { return static_cast<const FTestColumnInt*>(ColumnData)->TestInt; }
- L223 _public prototype_ `template <typename FunctionType> requires DataStorage::Private::AttributeBinderColumnDataInvocable<FunctionType> auto BindColumnData(const TWeakObjectPtr<const UScriptStruct>& InColumnType, FunctionType&& InConverter);` — Overload for the BindColumnData to accept lambdas instead of TFunctions @param InConverter Conversion function to convert from const void* ColumnData -> AttributeType @return A TAttribute bound to the row, column pair specified
- L232 _public prototype_ `template <typename InRetValType, typename... ParamTypes, TDataColumnType ColumnType> TDelegate<InRetValType(ParamTypes...)> BindEvent(TDelegate<InRetValType(ParamTypes...)> ColumnType::* InVariable);` — Bind a delegate inside a TEDS column to a SLATE_EVENT macro on a widget @param InVariable The delegate inside the TEDS column @param InIdentifier The identifier for this column if it is a dynamic column, NAME_None if it is not a dynamic column @return A delegate that can be provided to an event on a slate widget
- L235 _public prototype_ `template <typename InRetValType, typename... ParamTypes, TDynamicColumnTemplate ColumnType> TDelegate<InRetValType(ParamTypes...)> BindEvent(const FName& InIdentifier, TDelegate<InRetValType(ParamTypes...)> ColumnType::* InVariable);`
- L239 _public prototype_ `template <typename InRetValType, typename... ParamTypes, TDataColumnType ColumnType> TDelegate<InRetValType(ParamTypes...)> BindEvent(TSharedPtr<TDelegate<InRetValType(ParamTypes...)>> ColumnType::* InVariable);` — BindEvent overrides for TSharedPtr<TDelegate> since raw delegates inside of columns are unsafe because they are not trivially relocatable
- L242 _public prototype_ `template <typename InRetValType, typename... ParamTypes, TDynamicColumnTemplate ColumnType> TDelegate<InRetValType(ParamTypes...)> BindEvent(const FName& InIdentifier, TSharedPtr<TDelegate<InRetValType(ParamTypes...)>> ColumnType::* InVariable);`
- L246 _public prototype_ `template <typename InRetValType, TDataColumnType ColumnType> TAttribute<InRetValType> BindEventAttribute( TSharedPtr<TDelegate<InRetValType()>> ColumnType::* InVariable, InRetValType DefaultValue = InRetValType{});` — Bind an event column to a Slate attribute directly instead of a TDelegate
- L251 _public prototype_ `template <typename InRetValType, TDynamicColumnTemplate ColumnType> TAttribute<InRetValType> BindEventAttribute( const FName& InIdentifier, TSharedPtr<TDelegate<InRetValType()>> ColumnType::* InVariable, InRetValType DefaultValue = InRetValType{});`
- L263 _public prototype_ `template <TDataColumnType ColumnType> TAttribute<FText> BindText(FString ColumnType::* InFStringVariable);` — Directly bind an FString member in a TEDS column to an FText attribute as a shortcut @param InFStringVariable The FString variable @param InIdentifier The identifier for this column if it is a dynamic column, NAME_None if it is not a dynamic column @return A delegate that can be provided to a text widget in Slate (e.g STextBlock)
- L266 _public prototype_ `template <TDynamicColumnTemplate ColumnType> TAttribute<FText> BindText(const FName& InIdentifier, FString ColumnType::* InFStringVariable);`
- L275 _public prototype_ `template <TDataColumnType ColumnType> TAttribute<FText> BindText(FName ColumnType::* InFNameVariable);` — Directly bind an FName member in a TEDS column to an FText attribute as a shortcut @param InFNameVariable The FName variable @param InIdentifier The identifier for this column if it is a dynamic column, NAME_None if it is not a dynamic column @return A delegate that can be provided to a text widget in Slate (e.g STextBlock)
- L278 _public prototype_ `template <TDynamicColumnTemplate ColumnType> TAttribute<FText> BindText(const FName& InIdentifier, FName ColumnType::* InFNameVariable);`
- L299 _public prototype_ `FTextAttributeFormatted BindTextFormat(FTextFormat Format) const;` — Composite a FText attribute using a format string and named arguments bound to TEDS columns. Arguments are passed in using the .Arg(...) function. Each argument starts with the name of the argument in the format string followed by one of the following options: - A column variable that's a string (FText, FString or FName). - A column variable with a converter to a string. - A direct value that's supported by FFormatArgumentValue (FText and numbers). The final parameter for an argument is an optional default that optionally takes a FFormatArgumentValue value. @param Format The format to use composite a string together. @return A delegate that can be provided to a text widget in Slate (e.g STextBlock) Example: TAttribute<FText> Attribute(Binder.BindTextFormat( LOCTEXT("Format", "{Label}: {Value1}, {Value2}, {Value3}, {Value4}") .Arg(TEXT("Label"), &FTypedElementLabelColumn::Label) .Arg(TEXT("Value1"), &FValueColumn::Integer, [](const int32& Value) { return FText::AsNumber(Value); }, 42) .Arg(TEXT("Value2"), &FTextColumn::Text, LOCTEXT("Default", "<no value>")) .Arg(TEXT("Value3"), 42)
- L304 _private member_ `RowHandle TargetRow;` — The target row for this binder
- L307 _private member_ `ICoreProvider* DataStorage;` — A ptr to the data storage for quick access

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementAttributeBinding.inl` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _function_ `template <typename AttributeType, TDataColumnType ColumnType> TAttribute<AttributeType> FAttributeBinder::BindData(AttributeType ColumnType::* InVariable, const AttributeType& InDefaultValue)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L28 _function_ `` (scope `UE::Editor::DataStorage::FAttributeBinder::BindData`)
- L41 _function_ `template <typename AttributeType, TDynamicColumnTemplate ColumnType> TAttribute<AttributeType> FAttributeBinder::BindData(const FName& InIdentifier, AttributeType ColumnType::* InVariable, const AttributeType& InDefaultValue)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L67 _function_ `template <typename AttributeType, typename DataType, TDataColumnType ColumnType> TAttribute<AttributeType> FAttributeBinder::BindData(DataType ColumnType::* InVariable, TFunction<AttributeType(const DataType&)> InConverter, const DataType& InDefaultValue)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L100 _function_ `template <typename AttributeType, typename DataType, TDynamicColumnTemplate ColumnType> TAttribute<AttributeType> FAttributeBinder::BindData(const FName& InIdentifier, DataType ColumnType::* InVariable, TFunction<AttributeType(const DataType&)> InConverter, const DataType& InDefaultValue)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L136 _function_ `template <typename DataType, TDataColumnType ColumnType, typename FunctionType> requires DataStorage::Private::AttributeBinderInvocable<FunctionType, DataType> auto FAttributeBinder::BindData(DataType ColumnType::* InVariable, FunctionType&& InConverter, const DataType& InDefaultValue)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L139 _typedef_ `using AttributeType = decltype(InConverter(std::declval<DataType>()));` (scope `UE::Editor::DataStorage::FAttributeBinder::BindData`) — Deduce the attribute type from the return value of the converter function
- L146 _function_ `template <typename DataType, TDynamicColumnTemplate ColumnType, typename FunctionType> requires DataStorage::Private::AttributeBinderInvocable<FunctionType, DataType> auto FAttributeBinder::BindData(const FName& InIdentifier, DataType ColumnType::* InVariable, FunctionType&& InConverter, const DataType& InDefaultValue)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L155 _function_ `template <typename AttributeType, TDataColumnType ColumnType> TAttribute<AttributeType> FAttributeBinder::BindColumn(TFunction<AttributeType(const ColumnType&)> InConverter)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L165 _function_ `` (scope `UE::Editor::DataStorage::FAttributeBinder::BindColumn`)
- L179 _function_ `template <TDataColumnType ColumnType, typename FunctionType> requires DataStorage::Private::AttributeBinderColumnInvocable<FunctionType, ColumnType> auto FAttributeBinder::BindColumn(FunctionType&& InConverter)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L182 _typedef_ `using AttributeType = decltype(InConverter(std::declval<const ColumnType&>()));` (scope `UE::Editor::DataStorage::FAttributeBinder::BindColumn`) — Deduce the attribute type from the return value of the converter function
- L188 _function_ `template <typename AttributeType, TColumnType... ColumnTypes> TAttribute<AttributeType> FAttributeBinder::BindColumnsPresence(TFunction<AttributeType(const bool)> InConverter)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L198 _function_ `` (scope `UE::Editor::DataStorage::FAttributeBinder::BindColumnsPresence`)
- L207 _function_ `template <TColumnType... ColumnTypes, typename FunctionType> requires DataStorage::Private::AttributeBinderColumnPresenceInvocable<FunctionType> auto FAttributeBinder::BindColumnsPresence(FunctionType&& InConverter)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L210 _typedef_ `using AttributeType = decltype(InConverter(std::declval<const bool>()));` (scope `UE::Editor::DataStorage::FAttributeBinder::BindColumnsPresence`) — Deduce the attribute type from the return value of the converter function
- L216 _function_ `template <typename AttributeType> TAttribute<AttributeType> FAttributeBinder::BindColumnsPresence(Queries::FConditions InConditions, TFunction<AttributeType(const bool)> InConverter)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L240 _function_ `template <typename FunctionType> requires DataStorage::Private::AttributeBinderColumnPresenceInvocable<FunctionType> auto FAttributeBinder::BindColumnsPresence(Queries::FConditions InConditions, FunctionType&& InConverter)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L249 _function_ `template <typename AttributeType> TAttribute<AttributeType> FAttributeBinder::BindColumnData(const TWeakObjectPtr<const UScriptStruct>& InColumnType, const TFunction<AttributeType(const TWeakObjectPtr<const UScriptStruct>&, const void*)>& InConverter)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L261 _function_ `` (scope `UE::Editor::DataStorage::FAttributeBinder::BindColumnData`)
- L275 _function_ `template <typename FunctionType> requires DataStorage::Private::AttributeBinderColumnDataInvocable<FunctionType> auto FAttributeBinder::BindColumnData(const TWeakObjectPtr<const UScriptStruct>& InColumnType, FunctionType&& InConverter)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L278 _typedef_ `using AttributeType = decltype(InConverter(std::declval<const TWeakObjectPtr<const UScriptStruct>&>(), std::declval<const void*>()));` (scope `UE::Editor::DataStorage::FAttributeBinder::BindColumnData`) — Deduce the attribute type from the return value of the converter function
- L285 _function_ `template <typename InRetValType, typename... ParamTypes, TDataColumnType ColumnType> TDelegate<InRetValType(ParamTypes...)> FAttributeBinder::BindEvent(TDelegate<InRetValType(ParamTypes...)> ColumnType::* InVariable)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L295 _function_ `` (scope `UE::Editor::DataStorage::FAttributeBinder::BindEvent`)
- L312 _function_ `template <typename InRetValType, typename... ParamTypes, TDynamicColumnTemplate ColumnType> TDelegate<InRetValType(ParamTypes...)> FAttributeBinder::BindEvent(const FName& InIdentifier, TDelegate<InRetValType(ParamTypes...)> ColumnType::* InVariable)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L339 _function_ `template <typename InRetValType, typename... ParamTypes, TDataColumnType ColumnType> TDelegate<InRetValType(ParamTypes...)> FAttributeBinder::BindEvent(TSharedPtr<TDelegate<InRetValType(ParamTypes...)>> ColumnType::* InVariable)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L362 _function_ `template <typename InRetValType, typename... ParamTypes, TDynamicColumnTemplate ColumnType> TDelegate<InRetValType(ParamTypes...)> FAttributeBinder::BindEvent(const FName& InIdentifier, TSharedPtr<TDelegate<InRetValType(ParamTypes...)>> ColumnType::* InVariable)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L385 _function_ `template <typename InRetValType, TDataColumnType ColumnType> TAttribute<InRetValType> FAttributeBinder::BindEventAttribute( TSharedPtr<TDelegate<InRetValType()>> ColumnType::* InVariable, InRetValType DefaultValue)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L396 _function_ `` (scope `UE::Editor::DataStorage::FAttributeBinder::BindEventAttribute`)
- L410 _function_ `template <typename InRetValType, TDynamicColumnTemplate ColumnType> TAttribute<InRetValType> FAttributeBinder::BindEventAttribute( const FName& InIdentifier, TSharedPtr<TDelegate<InRetValType()>> ColumnType::* InVariable, InRetValType DefaultValue)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L436 _function_ `template <TDataColumnType ColumnType> TAttribute<FText> FAttributeBinder::BindText(FString ColumnType::* InFStringVariable)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L439 _function_ `` (scope `UE::Editor::DataStorage::FAttributeBinder::BindText`)
- L445 _function_ `template <TDynamicColumnTemplate ColumnType> TAttribute<FText> FAttributeBinder::BindText(const FName& InIdentifier, FString ColumnType::* InFStringVariable)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L454 _function_ `template <TDataColumnType ColumnType> TAttribute<FText> FAttributeBinder::BindText(FName ColumnType::* InFNameVariable)` (scope `UE::Editor::DataStorage::FAttributeBinder`)
- L463 _function_ `template <TDynamicColumnTemplate ColumnType> TAttribute<FText> FAttributeBinder::BindText(const FName& InIdentifier, FName ColumnType::* InFNameVariable)` (scope `UE::Editor::DataStorage::FAttributeBinder`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementAttributeBindingProperty.h` (Public)


#### struct `UE::Editor::DataStorage::Private::TEmptyProperty`  
`template <typename PropertyType> struct TEmptyProperty final`  
_L50-54_
- L52 _public prototype_ `PropertyType* Get(void* Object) const;`
- L53 _public prototype_ `const PropertyType* Get(const void* Object) const;`
- L136 _function_ `template <typename PropertyType> PropertyType* TEmptyProperty<PropertyType>::Get(void* Object) const` — TEmptyProperty
- L143 _function_ `template <typename PropertyType> const PropertyType* TEmptyProperty<PropertyType>::Get(const void* Object) const`

#### struct `UE::Editor::DataStorage::Private::TDirectProperty`  
`template <typename PropertyType> struct TDirectProperty final`  
_L57-64_
- L60 _public member_ `size_t Offset;` — Offset to a particular data member inside the object
- L62 _public prototype_ `PropertyType* Get(void* Object) const;`
- L63 _public prototype_ `const PropertyType* Get(const void* Object) const;`
- L155 _function_ `template <typename PropertyType> PropertyType* TDirectProperty<PropertyType>::Get(void* Object) const`
- L161 _function_ `template <typename PropertyType> const PropertyType* TDirectProperty<PropertyType>::Get(const void* Object) const`

#### struct `UE::Editor::DataStorage::Private::TConvertibleProperty`  
`template <typename PropertyType> struct TConvertibleProperty final`  
_L68-78_
- desc: A property that goes through a conversion function before being accessed from the object
- L71 _public member_ `TFunction<PropertyType(const void*)> Converter;` — Conversion function
- L74 _public member_ `mutable PropertyType Cache;` — Cache to avoid a copy when returning if not necessary
- L76 _public prototype_ `PropertyType* Get(void* Object) const;`
- L77 _public prototype_ `const PropertyType* Get(const void* Object) const;`
- L172 _function_ `template <typename PropertyType> PropertyType* TConvertibleProperty<PropertyType>::Get(void* Object) const`
- L179 _function_ `template <typename PropertyType> const PropertyType* TConvertibleProperty<PropertyType>::Get(const void* Object) const`

#### class `UE::Editor::DataStorage::Private::TProperty`  
`template <typename PropertyType> class TProperty`  
_L87-130_
- L92 _public prototype_ `template <TDataColumnOrDynamicDataColumnTemplate ObjectType> void Bind(PropertyType ObjectType::* Variable);` — Bind this property directly
- L96 _public prototype_ `template <typename InputType, TDataColumnOrDynamicDataColumnTemplate ObjectType> void Bind(InputType ObjectType::* Variable, TFunction<PropertyType(const InputType&)> Converter);` — Bind this property using a conversion function
- L100 _public prototype_ `template <TDataColumnOrDynamicDataColumnTemplate ObjectType> PropertyType& Get(ObjectType& Object) const;` — Get the bound property for the specified object
- L104 _public prototype_ `template <TDataColumnOrDynamicDataColumnTemplate ObjectType> const PropertyType& Get(const ObjectType& Object) const;` — Get the bound property for the specified object
- L107 _public prototype_ `PropertyType& Get(void* Object, TWeakObjectPtr<const UScriptStruct> Type) const;` — Get the bound property for this specified object ptr by providing type information about the object
- L110 _public prototype_ `const PropertyType& Get(const void* Object, TWeakObjectPtr<const UScriptStruct> Type) const;` — Get the bound property for this specified object ptr by providing type information about the object
- L113 _public prototype_ `TWeakObjectPtr<const UScriptStruct> GetObjectTypeInfo() const;` — Returns the stored type information or null if no type was set.
- L116 _public prototype_ `bool IsBound() const;` — Whether or not this property has been bound.
- L120 _private typedef_ `using InternalPropertyType = TVariant< TEmptyProperty<PropertyType>, TDirectProperty<PropertyType>, TConvertibleProperty<PropertyType>>;` — Internally we could be storing a direct property or a convertible property
- L126 _private member_ `InternalPropertyType InternalProperty;` — The actual property
- L129 _private member_ `TWeakObjectPtr<const UScriptStruct> ObjectTypeInfo = nullptr;` — The type of the object we are bound to
- L192 _function_ `template <typename PropertyType> template <TDataColumnOrDynamicDataColumnTemplate ObjectType> void TProperty<PropertyType>::Bind(PropertyType ObjectType::* Variable)`
- L203 _function_ `template <typename PropertyType> template <typename InputType, TDataColumnOrDynamicDataColumnTemplate ObjectType> void TProperty<PropertyType>::Bind(InputType ObjectType::* Variable, TFunction<PropertyType(const InputType&)> Converter)`
- L217 _function_ `template <typename PropertyType> template <TDataColumnOrDynamicDataColumnTemplate ObjectType> PropertyType& TProperty<PropertyType>::Get(ObjectType& Object) const`
- L224 _function_ `template <typename PropertyType> template <TDataColumnOrDynamicDataColumnTemplate ObjectType> const PropertyType& TProperty<PropertyType>::Get(const ObjectType& Object) const`
- L230 _function_ `template <typename PropertyType> PropertyType& TProperty<PropertyType>::Get(void* Object, TWeakObjectPtr<const UScriptStruct> Type) const`
- L243 _function_ `template <typename PropertyType> const PropertyType& TProperty<PropertyType>::Get(const void* Object, TWeakObjectPtr<const UScriptStruct> Type) const`
- L256 _function_ `template <typename PropertyType> TWeakObjectPtr<const UScriptStruct> TProperty<PropertyType>::GetObjectTypeInfo() const`
- L262 _function_ `template <typename PropertyType> bool TProperty<PropertyType>::IsBound() const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage`)
- L33 _function_ `template <TColumnType ColumnType> ColumnType* GetColumn(ICoreProvider* DataStorage, RowHandle Row)` (scope `UE::Editor::DataStorage::Private`)
- L39 _function_ `template <TDynamicColumnTemplate ColumnType> ColumnType* GetColumn(ICoreProvider* DataStorage, RowHandle Row, const FName& InIdentifier)` (scope `UE::Editor::DataStorage::Private`)
- L207 _function_ `` (scope `UE::Editor::DataStorage::Private::TProperty::Bind`)
- L239 _function_ `return *Visit([Object](auto&& Prop) { return Prop.Get(Object); }, InternalProperty);` (scope `UE::Editor::DataStorage::Private::TProperty::Get`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementAttributeBindingText.h` (Public)


#### class `UE::Editor::DataStorage::FTextAttributeFormatted`  
`class FTextAttributeFormatted`  
_L19-69_
- L24 _public prototype_ `FTextAttributeFormatted& Arg(FString Name, FFormatArgumentValue Value);`
- L27 _public prototype_ `template <TDataColumnType ColumnType> FTextAttributeFormatted& Arg(FString Name, FText ColumnType::* Variable, FFormatArgumentValue Default = {}, FName ColumnIdentifier = NAME_None);`
- L31 _public prototype_ `template <TDataColumnType ColumnType> FTextAttributeFormatted& Arg(FString Name, FString ColumnType::* Variable, FFormatArgumentValue Default = {}, FName ColumnIdentifier = NAME_None);`
- L35 _public prototype_ `template <TDataColumnType ColumnType> FTextAttributeFormatted& Arg(FString Name, FName ColumnType::* Variable, FFormatArgumentValue Default = {}, FName ColumnIdentifier = NAME_None);`
- L39 _public prototype_ `template <typename DataType, TDataColumnType ColumnType> FTextAttributeFormatted& Arg( FString Name, DataType ColumnType::* Variable, const TFunction<FText(const DataType&)>& Converter, FFormatArgumentValue Default = {}, FName ColumnIdentifier = NAME_None);`
- L48 _public prototype_ `template <typename DataType, TDataColumnType ColumnType, typename FunctionType> requires DataStorage::Private::AttributeBinderInvocable<FunctionType, DataType> FTextAttributeFormatted& Arg(FString Name, DataType ColumnType::* Variable, FunctionType Converter, FFormatArgumentValue Default = {}, FName ColumnIdentifier = NAME_None);`
- L51 _public prototype_ `operator TAttribute<FText>();`
- L54 _private prototype_ `FTextAttributeFormatted(FTextFormat InFormat, RowHandle InTargetRow, ICoreProvider* InDataStorage);`
- L62 _private member_ `TMap<FString, FPropertyInfo> NamedProperties;`
- L63 _private member_ `FTextFormat Format;`
- L66 _private member_ `RowHandle TargetRow;` — The target row for this binder
- L68 _private member_ `ICoreProvider* DataStorage;` — A ptr to the data storage for quick access
- L72 _function_ `template <TDataColumnType ColumnType> FTextAttributeFormatted& FTextAttributeFormatted::Arg( FString Name, FText ColumnType::* Variable, FFormatArgumentValue Default, FName ColumnIdentifier)`
- L84 _function_ `template <TDataColumnType ColumnType> FTextAttributeFormatted& FTextAttributeFormatted::Arg( FString Name, FString ColumnType::* Variable, FFormatArgumentValue Default, FName ColumnIdentifier)`
- L91 _function_ `template <TDataColumnType ColumnType> FTextAttributeFormatted& FTextAttributeFormatted::Arg( FString Name, FName ColumnType::* Variable, FFormatArgumentValue Default, FName ColumnIdentifier)`
- L98 _function_ `template <typename DataType, TDataColumnType ColumnType> FTextAttributeFormatted& FTextAttributeFormatted::Arg( FString Name, DataType ColumnType::* Variable, const TFunction<FText(const DataType&)>& Converter, FFormatArgumentValue Default, FName ColumnIdentifier)`
- L115 _function_ `template <typename DataType, TDataColumnType ColumnType, typename FunctionType> requires DataStorage::Private::AttributeBinderInvocable<FunctionType, DataType> FTextAttributeFormatted& FTextAttributeFormatted::Arg( FString Name, DataType ColumnType::* Variable, FunctionType Converter, FFormatArgumentValue Default, FName ColumnIdentifier)`

#### struct `UE::Editor::DataStorage::FTextAttributeFormatted::FPropertyInfo`  
`struct FPropertyInfo`  
_L56-61_
- L58 _public member_ `DataStorage::Private::TProperty<FText> Property;`
- L59 _public member_ `FFormatArgumentValue Default;`
- L60 _public member_ `FName DynamicColumnIdentifier;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L87 _function_ `return Arg(MoveTemp(Name), Variable, [](const FString& Value) { return FText::FromString(Value); }, MoveTemp(Default), ColumnIdentifier);` (scope `UE::Editor::DataStorage::FTextAttributeFormatted::Arg`)
- L94 _function_ `return Arg(MoveTemp(Name), Variable, [](const FName& Value) { return FText::FromName(Value); }, MoveTemp(Default), ColumnIdentifier);` (scope `UE::Editor::DataStorage::FTextAttributeFormatted::Arg`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementColumnUtils.h` (Public)


#### struct `UE::Editor::DataStorage::ColumnUtils::Argument`  
`struct Argument`  
_L12-16_
- L14 _public member_ `FName Name;`
- L15 _public member_ `FString Value;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L10 _namespace_ `namespace ColumnUtils` (scope `UE::Editor::DataStorage`)
- L23 _prototype_ `void SetColumnValue( void* ColumnData, const UScriptStruct* ColumnType, FName ArgumentName, const FString& ArgumentValue);` (scope `UE::Editor::DataStorage::ColumnUtils`) — If found in the column, the variable under the provided name will be updated to the target value. The target variable must be convertable from string. Any incompatible or missing variables will be silently ignored.
- L30 _prototype_ `void SetColumnValues(void* ColumnData, const UScriptStruct* ColumnType, TConstArrayView<Argument> Arguments);` (scope `UE::Editor::DataStorage::ColumnUtils`) — If found in the column, the variables under the provided names will be updated to the target values. The target variables must be convertable from string. Any incompatible or missing variables will be silently ignored.
- L34 _function_ `template<typename ColumnType> void SetColumnValue(ColumnType& Column, FName ArgumentName, const FString& ArgumentValue)` (scope `UE::Editor::DataStorage::ColumnUtils`) — Utility function for SetColumnValue that automatically detects the type of the column.
- L41 _function_ `template<typename ColumnType> void SetColumnValues(ColumnType& Column, TConstArrayView<Argument> Arguments)` (scope `UE::Editor::DataStorage::ColumnUtils`) — Utility function for SetColumnValues that automatically detects the type of the column.
- L47 _prototype_ `bool IsDynamicTemplate(const UScriptStruct* InColumn);` (scope `UE::Editor::DataStorage::ColumnUtils`) — Utility function to check if a column type is a dynamic template.
- L50 _prototype_ `bool IsDerivedFromDynamicTemplate(const UScriptStruct* InColumn);` (scope `UE::Editor::DataStorage::ColumnUtils`) — Utility function to check if a column type is derived from a dynamic template.
- L53 _prototype_ `FName GetDynamicColumnIdentifier(const UScriptStruct* InColumn);` (scope `UE::Editor::DataStorage::ColumnUtils`) — Utility function to get the identifier for a dynamic column, NAME_None if invalid
- L57 _namespace_ `namespace TypedElement`
- L59 _namespace_ `namespace ColumnUtils` (scope `TypedElement`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementConcurrentRowHandleCollector.h` (Public)


#### enum `UE::Editor::DataStorage::EConcurrentRowHandleCollectorType`  
`enum class EConcurrentRowHandleCollectorType`  
_L10-14_
- L12 _public enumerator_ `Array` — Collects all row handles in random order. Is allowed to have duplicates.
- L13 _public enumerator_ `Set` — Collects only a unique instance of a row handles and orders them numerically.

#### class `UE::Editor::DataStorage::FConcurrentRowHandleCollector`  
`template<EConcurrentRowHandleCollectorType Type> class FConcurrentRowHandleCollector`  
_L31-69_
- desc: A lock-free utility class to collect rows from multiple threads at the same time. Two options are provided: - Array: Collects all provided row handles without order and can have duplicates. This is usually faster than a set. - Set: Merges the provided row handles in sorted order and removes duplicates. This is generally slower than an array. Each thread needs to first fill a local row handle array. That list is then passed on to the collector that will combine it with the final list collected from multiple threads. The cost of merging is spread across multiple threads, but as more list contribute some threads will have to merge larger lists than other threads causing an imbalance in thread runtime. The worse case will be the last thread as that will need to merge two arrays that are roughly both half the size of the final array. It's therefor recommended to run with "AutoBalanceParallelChunkProcessing".
- L34 _public prototype_ `~FConcurrentRowHandleCollector();`
- L55 _public prototype_ `void Append(FRowHandleArray&& LocalArray);` — Moves the provided array into the collected list by either appending (Array) or uniquely merging (Set). This function can be repeatedly collect from multiple threads at the same time. The approach for writing results back is a two step process. In the first step it tries to grab the temp local array that's shared by all threads. If that returns a nullptr it means there's no array yet or another thread has already claimed it, in which case a new array is created. If it does manage to get a hold of the array it merges its own local changes into it. In the next phase it tries to place the locally update version of the array back so other threads can add to it. If the shared array is a nullptr than it can move the local version into it, but if another thread has already set it, it needs to try to grab that version and merge the local copy into it. This local copy becomes the new target to place in the shared location. In practice there will be multiple merges collections present for the majority of processing and separate threads will merge them together into a single final collection over time. This does result in later threads having to merge increasingly large list, with one thread have to merge the final largest list. As a result this leads to threads starting fast but taking increasingly long to run. It's therefore recommended to run queries with `AutoBalanceParallelChunkProcessing`.
- L65 _public prototype_ `bool Collect(FRowHandleArray& AccumulatedCollection);` — Collect the final results and merge with the provided list. Returns true if additions were mode, otherwise false. This function should be called once from a single thread to collect the final list. This can be called if threads are still adding new values to the collector, in which case this will remove the row handles merged into "Result" and will merge the rest when this is called again.
- L68 _private member_ `std::atomic<FRowHandleArray*> WorkingSet = nullptr;`
- L74 _prototype_ `extern template FConcurrentRowHandleCollector<EConcurrentRowHandleCollectorType::Array>::~FConcurrentRowHandleCollector();`
- L75 _prototype_ `extern template void FConcurrentRowHandleCollector<EConcurrentRowHandleCollectorType::Array>::Append(FRowHandleArray&&);`
- L76 _prototype_ `extern template bool FConcurrentRowHandleCollector<EConcurrentRowHandleCollectorType::Array>::Collect(FRowHandleArray&);`
- L78 _prototype_ `extern template FConcurrentRowHandleCollector<EConcurrentRowHandleCollectorType::Set>::~FConcurrentRowHandleCollector();`
- L79 _prototype_ `extern template void FConcurrentRowHandleCollector<EConcurrentRowHandleCollectorType::Set>::Append(FRowHandleArray&&);`
- L80 _prototype_ `extern template bool FConcurrentRowHandleCollector<EConcurrentRowHandleCollectorType::Set>::Collect(FRowHandleArray&);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L71 _typedef_ `using FConcurrentRowHandleArrayCollector = FConcurrentRowHandleCollector<EConcurrentRowHandleCollectorType::Array>;` (scope `UE::Editor::DataStorage`)
- L72 _typedef_ `using FConcurrentRowHandleSetCollector = FConcurrentRowHandleCollector<EConcurrentRowHandleCollectorType::Set>;` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementCounter.h` (Public)


#### class `FTypedElementCounter`  
`class FTypedElementCounter`  
_L49-291_
- desc: Tracks various categories of counters for the typed elements (eg, the number of elements of a given type). The categories counted may be expanded by element types that implement the UTypedElementCounterInterface API.
- L52 _public typedef_ `using FCounterValue = int32;`
- L54 _public prototype_ `FTypedElementCounter() = default;`
- L55 _public prototype_ `explicit FTypedElementCounter(UTypedElementRegistry* InRegistry);`
- L57 _public prototype_ `FTypedElementCounter(const FTypedElementCounter&) = delete;`
- L58 _public prototype_ `FTypedElementCounter& operator=(const FTypedElementCounter&) = delete;`
- L60 _public prototype_ `FTypedElementCounter(FTypedElementCounter&&) = default;`
- L61 _public prototype_ `FTypedElementCounter& operator=(FTypedElementCounter&&) = default;`
- L66 _public prototype_ `void Initialize(UTypedElementRegistry* InRegistry);` — Explicitly initialize this instance, if it was previously default constructed.
- L71 _public prototype_ `void AddElement(const FTypedElementHandle& InElementHandle);` — Update the counter categories to include the given element.
- L76 _public prototype_ `void RemoveElement(const FTypedElementHandle& InElementHandle);` — Update the counter categories to remove the given element.
- L83 _public function_ `template <typename KeyType> void IncrementCounter(const FName InCategory, const KeyType& InKey)` — Increment the counter for the given category and key. @note For use by UTypedElementCounterInterface.
- L98 _public function_ `template <typename KeyType> void DecrementCounter(const FName InCategory, const KeyType& InKey)` — Decrement the counter for the given category and key. @note For use by UTypedElementCounterInterface.
- L110 _public function_ `template <typename KeyType> FCounterValue GetCounterValue(const FName InCategory, const KeyType& InKey) const` — Get the value of the counter for the given category and key, or zero if the category or key are unknown.
- L123 _public function_ `template <typename KeyType> void ForEachCounterValue(const FName InCategory, TFunctionRef<bool(const KeyType&, FCounterValue)> InCallback) const` — Enumerate the value of the counters for the given category.
- L135 _public function_ `template <typename KeyType> void ClearCounter(const FName InCategory, const KeyType& InKey)` — Clear the value of the counter for the given category and key.
- L146 _public prototype_ `void ClearCounters(const FName InCategory);` — Clear the value of the counters for the given category.
- L151 _public prototype_ `void ClearCounters();` — Clear all counters.
- L156 _public prototype_ `static FName GetElementTypeCategoryName();` — Get the category name used to count element types (by type ID).
- L285 _private member_ `TWeakObjectPtr<UTypedElementRegistry> Registry;` — Element registry this element counter is associated with.
- L290 _private member_ `TSortedMap<FName, TUniquePtr<ICounterCategory>, FDefaultAllocator, FNameFastLess> CounterCategories;` — Counter categories.

#### class `FTypedElementCounter::ICounterCategory`  
`class ICounterCategory`  
_L159-206_
- L162 _public prototype_ `virtual ~ICounterCategory() = default;`
- L165 _public function_ `template <typename KeyType> FCounterValue GetCounterValue(const KeyType& InKey) const`
- L171 _public function_ `template <typename KeyType> void ForEachCounterValue(TFunctionRef<bool(const KeyType&, FCounterValue)> InCallback) const`
- L177 _public function_ `template <typename KeyType> void IncrementCounter(const KeyType& InKey)`
- L183 _public function_ `template <typename KeyType> void DecrementCounter(const KeyType& InKey)`
- L189 _public function_ `template <typename KeyType> void ClearCounter(const KeyType& InKey)`
- L194 _public function_ `void ClearCounters()`
- L200 _protected prototype_ `virtual FCounterValue GetCounterValueImpl(const void* InKey, const FName InKeyTypeName) const = 0;`
- L201 _protected prototype_ `virtual void ForEachCounterValueImpl(const void* InCallback, const FName InKeyTypeName) const = 0;`
- L202 _protected prototype_ `virtual void IncrementCounterImpl(const void* InKey, const FName InKeyTypeName) = 0;`
- L203 _protected prototype_ `virtual void DecrementCounterImpl(const void* InKey, const FName InKeyTypeName) = 0;`
- L204 _protected prototype_ `virtual void ClearCounterImpl(const void* InKey, const FName InKeyTypeName) = 0;`
- L205 _protected prototype_ `virtual void ClearCountersImpl() = 0;`

#### class `FTypedElementCounter::TCounterCategory`  
`template <typename KeyType> class TCounterCategory : public ICounterCategory`  
_L209-280_
- inherits: `ICounterCategory`
- L212 _public function_ `TCounterCategory() : KeyTypeName(GetTypedElementCounterKeyName<KeyType>())`
- L218 _private function_ `virtual FCounterValue GetCounterValueImpl(const void* InKey, const FName InKeyTypeName) const override`
- L226 _private function_ `virtual void ForEachCounterValueImpl(const void* InCallback, const FName InKeyTypeName) const override`
- L240 _private function_ `virtual void IncrementCounterImpl(const void* InKey, const FName InKeyTypeName) override`
- L249 _private function_ `virtual void DecrementCounterImpl(const void* InKey, const FName InKeyTypeName) override`
- L264 _private function_ `virtual void ClearCounterImpl(const void* InKey, const FName InKeyTypeName) override`
- L272 _private function_ `virtual void ClearCountersImpl() override`
- L278 _private member_ `FName KeyTypeName;`
- L279 _private member_ `TMap<KeyType, FCounterValue> Counters;`

#### class `UTypedElementCounterInterface`  
`class UTypedElementCounterInterface : public UInterface`  
_L294-297_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ITypedElementCounterInterface`  
`class ITypedElementCounterInterface`  
_L299-313_
- L307 _public function_ `virtual void IncrementCountersForElement(const FTypedElementHandle& InElementHandle, FTypedElementCounter& InOutCounter)` — Increment additional counters for the given element.
- L312 _public function_ `virtual void DecrementCountersForElement(const FTypedElementHandle& InElementHandle, FTypedElementCounter& InOutCounter)` — Decrement additional counters for the given element.

#### struct `TTypedElement`  
`template <> struct TTypedElement<ITypedElementCounterInterface> : public TTypedElementBase<ITypedElementCounterInterface>`  
_L316-320_
- inherits: `TTypedElementBase<ITypedElementCounterInterface>`
- L318 _public function_ `void IncrementCountersForElement(FTypedElementCounter& InOutCounter) const`
- L319 _public function_ `void DecrementCountersForElement(FTypedElementCounter& InOutCounter) const`

#### Free symbols / members of external scopes

- L32 _function_ `template <typename KeyType> inline FName GetTypedElementCounterKeyName()`

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementData.h` (Public)


#### class `FTypedElementReference`  
`class FTypedElementReference`  
_L44-72_
- desc: Debugging information used to locate reference leaks.
- L47 _public function_ `FTypedElementReference()`
- L52 _public prototype_ `FTypedElementReference(const FTypedElementReference&) = default;`
- L53 _public prototype_ `FTypedElementReference& operator=(const FTypedElementReference&) = default;`
- L55 _public prototype_ `FTypedElementReference(FTypedElementReference&&) = default;`
- L56 _public prototype_ `FTypedElementReference& operator=(FTypedElementReference&&) = default;`
- L58 _public function_ `void LogReference() const`
- L70 _private member_ `uint64 Callstack[TypedHandleRefTrackingDepth + TypedHandleRefTrackingSkipCount];`
- L71 _private member_ `uint32 CallstackDepth = 0;`

#### class `FTypedElementReferences`  
`class FTypedElementReferences`  
_L77-150_
- desc: Debugging information used to locate reference leaks.
- L80 _public function_ `static TUniquePtr<FTypedElementReferences> Create()`
- L87 _public function_ `void Reset()`
- L94 _public function_ `FTypedElementReferenceId AddRef()`
- L100 _public function_ `void ReleaseRef(const FTypedElementReferenceId InReferenceId)`
- L109 _public function_ `void LogReferences() const`
- L128 _public function_ `void StoreDestructionRequestCallstack()`
- L145 _private prototype_ `static bool ReferenceTrackingEnabled();`
- L147 _private member_ `mutable FCriticalSection ReferencesCS;`
- L148 _private member_ `TSparseArray<FTypedElementReference> References;`
- L149 _private member_ `TUniquePtr<FTypedElementReference> DestructionRequestCallstack;`

#### class `FTypedElementInternalData`  
`class FTypedElementInternalData`  
_L156-321_
- desc: Base class for the internal payload data associated with elements.
- L159 _public prototype_ `FTypedElementInternalData() = default;`
- L161 _public prototype_ `FTypedElementInternalData(const FTypedElementInternalData&) = delete;`
- L162 _public prototype_ `FTypedElementInternalData& operator=(const FTypedElementInternalData&) = delete;`
- L164 _public prototype_ `FTypedElementInternalData(FTypedElementInternalData&& InOther) = delete;`
- L165 _public prototype_ `FTypedElementInternalData& operator=(FTypedElementInternalData&&) = delete;`
- L167 _public function_ `virtual ~FTypedElementInternalData()`
- L172 _public function_ `void Initialize(const FTypedHandleTypeId InTypeId, const FTypedHandleElementId InElementId)`
- L186 _public function_ `virtual void Reset()`
- L212 _public function_ `inline const FTypedElementId& GetId() const`
- L217 _public function_ `inline FTypedElementReferenceId AddRef(const bool bCanTrackReference) const`
- L241 _public function_ `inline void ReleaseRef(const FTypedElementReferenceId InReferenceId) const`
- L260 _public function_ `inline FTypedElementRefCount GetRefCount() const`
- L269 _public function_ `void StoreDestructionRequestCallstack() const`
- L279 _public function_ `void LogExternalReferencesOnDestruction() const`
- L303 _public function_ `virtual const void* GetUntypedData() const`
- L308 _public function_ `virtual FString GetDebugId() const`
- L314 _private member_ `FTypedElementId Id;`
- L316 _private member_ `mutable FTypedElementRefCount RefCount = 0;`
- L319 _private member_ `TUniquePtr<FTypedElementReferences> References;`

#### class `TTypedElementInternalData`  
`template <typename ElementDataType> class TTypedElementInternalData : public FTypedElementInternalData`  
_L327-361_
- inherits: `FTypedElementInternalData`
- desc: Internal payload data associated with typed elements.
- L330 _public function_ `virtual void Reset() override`
- L336 _public function_ `inline const ElementDataType& GetData() const`
- L341 _public function_ `inline ElementDataType& GetMutableData()`
- L346 _public function_ `virtual const void* GetUntypedData() const override`
- L351 _public function_ `virtual FString GetDebugId() const override`
- L360 _private member_ `ElementDataType Data;`

#### class `TTypedElementInternalData`  
`template <> class TTypedElementInternalData<void> : public FTypedElementInternalData`  
_L367-369_
- inherits: `FTypedElementInternalData`
- desc: Internal payload data associated with typeless elements.
- L330 _public function_ `virtual void Reset() override`
- L336 _public function_ `inline const ElementDataType& GetData() const`
- L341 _public function_ `inline ElementDataType& GetMutableData()`
- L346 _public function_ `virtual const void* GetUntypedData() const override`
- L351 _public function_ `virtual FString GetDebugId() const override`
- L360 _private member_ `ElementDataType Data;`

#### class `FScriptTypedElementInternalDataPtr`  
`class FScriptTypedElementInternalDataPtr`  
_L374-510_
- desc: Internal data that act as a ptr to a control block for the data represented by a ScriptTypedElementHandle
- L378 _public prototype_ `FScriptTypedElementInternalDataPtr() = default;`
- L380 _public function_ `~FScriptTypedElementInternalDataPtr()`
- L385 _public function_ `FScriptTypedElementInternalDataPtr(const FScriptTypedElementInternalDataPtr& Other) : ControlBlock(Other.ControlBlock)`
- L391 _public function_ `FScriptTypedElementInternalDataPtr(FScriptTypedElementInternalDataPtr&& Other) : ControlBlock(Other.ControlBlock)`
- L397 _public function_ `FScriptTypedElementInternalDataPtr& operator=(const FScriptTypedElementInternalDataPtr& Other)`
- L404 _public function_ `FScriptTypedElementInternalDataPtr& operator=(FScriptTypedElementInternalDataPtr&& Other)`
- L411 _public function_ `bool operator==(const FScriptTypedElementInternalDataPtr& Other) const`
- L416 _public function_ `bool operator!=(const FScriptTypedElementInternalDataPtr& Other) const`
- L421 _public function_ `bool IsSet() const`
- L426 _public function_ `void Release()`
- L432 _public function_ `inline const FTypedElementId& GetId() const`
- L445 _public function_ `inline FTypedElementInternalData* GetInternalData() const`
- L459 _protected function_ `void IncrementCount()`
- L467 _protected function_ `void DecrementCount()`
- L480 _protected function_ `FScriptTypedElementInternalDataPtr(FTypedElementInternalData& InternalData) : ControlBlock(new FScriptTypedElementInternalDataControlBlock(InternalData))`
- L509 _protected member_ `FScriptTypedElementInternalDataControlBlock* ControlBlock = nullptr;`

#### struct `FScriptTypedElementInternalDataPtr::FScriptTypedElementInternalDataControlBlock`  
`struct FScriptTypedElementInternalDataControlBlock`  
_L489-507_
- desc: Internal data that act as a weak reference count and a control block for the ScriptTypedElementHandle
- L491 _public function_ `FScriptTypedElementInternalDataControlBlock(FTypedElementInternalData& InData) : Data(&InData)`
- L496 _public prototype_ `FScriptTypedElementInternalDataControlBlock() = delete;`
- L499 _public prototype_ `FScriptTypedElementInternalDataControlBlock(const FScriptTypedElementInternalDataControlBlock&) = delete;` — The control block should never be copied/Moved
- L500 _public prototype_ `FScriptTypedElementInternalDataControlBlock(FScriptTypedElementInternalDataControlBlock&&) = delete;`
- L501 _public prototype_ `FScriptTypedElementInternalDataControlBlock& operator=(const FScriptTypedElementInternalDataControlBlock&) = delete;`
- L502 _public prototype_ `FScriptTypedElementInternalDataControlBlock& operator=(FScriptTypedElementInternalDataControlBlock&&) = delete;`
- L505 _public member_ `FTypedElementInternalData* Data = nullptr;`
- L506 _public member_ `FTypedElementRefCount WeakRefCount = 0;`

#### class `FScriptTypedElementInternalDataOwner`  
`class FScriptTypedElementInternalDataOwner : public FScriptTypedElementInternalDataPtr`  
_L512-530_
- inherits: `FScriptTypedElementInternalDataPtr`
- L516 _public function_ `FScriptTypedElementInternalDataOwner(FTypedElementInternalData& InInternalData) : FScriptTypedElementInternalDataPtr(InInternalData)`
- L524 _public function_ `~FScriptTypedElementInternalDataOwner()` — Tell all the weak reference that the data they point to is no longer valid

#### class `TTypedElementInternalDataStore`  
`template <typename ElementDataType> class TTypedElementInternalDataStore`  
_L537-619_
- desc: Data store implementation used by the element registry to manage internal data. @note This is the generic implementation that uses an array and manages the IDs itself.
- L542 _public function_ `TTypedElementInternalData<ElementDataType>& AddDataForElement(const FTypedHandleTypeId InTypeId, FTypedHandleElementId& InOutElementId)`
- L557 _public function_ `FScriptTypedElementInternalDataPtr GetInternalDataForScriptHandle(const FTypedHandleElementId InElementId)`
- L571 _public function_ `void DisableScriptHandlesForElement(const FTypedHandleElementId InElementId)`
- L577 _public function_ `void RemoveDataForElement(const FTypedHandleElementId InElementId, const FTypedElementInternalData* InExpectedDataPtr)`
- L590 _public function_ `const TTypedElementInternalData<ElementDataType>& GetDataForElement(const FTypedHandleElementId InElementId) const`
- L598 _public function_ `static inline void SetStaticDataTypeId(const FTypedHandleTypeId InTypeId)`
- L604 _public function_ `static inline FTypedHandleTypeId StaticDataTypeId()`
- L609 _public function_ `static inline FName StaticDataTypeName()`
- L615 _private member_ `mutable FTransactionallySafeRWLock InternalDataRW;`
- L616 _private member_ `TArray<int32> InternalDataFreeIndices;`
- L617 _private member_ `TChunkedArray<TTypedElementInternalData<ElementDataType>> InternalDataArray;`
- L618 _private member_ `TMap<FTypedHandleElementId, FScriptTypedElementInternalDataOwner> ScriptInternalDataMap;`
- L631 _public function_ `TTypedElementInternalData<void>& AddDataForElement(const FTypedHandleTypeId InTypeId, FTypedHandleElementId& InOutElementId)`
- L685 _public function_ `const TTypedElementInternalData<void>& GetDataForElement(const FTypedHandleElementId InElementId) const`
- L710 _private member_ `TChunkedArray<TTypedElementInternalData<void>> InternalDataArray;`
- L712 _private member_ `TMap<FTypedHandleElementId, int32> ElementIdToArrayIndex;`

#### class `TTypedElementInternalDataStore`  
`template <> class TTypedElementInternalDataStore<void>`  
_L626-714_
- desc: Data store implementation used by the element registry to manage internal data. @note This is the typeless implementation that uses external IDs, and exists only to track ref counts.
- L542 _public function_ `TTypedElementInternalData<ElementDataType>& AddDataForElement(const FTypedHandleTypeId InTypeId, FTypedHandleElementId& InOutElementId)`
- L557 _public function_ `FScriptTypedElementInternalDataPtr GetInternalDataForScriptHandle(const FTypedHandleElementId InElementId)`
- L571 _public function_ `void DisableScriptHandlesForElement(const FTypedHandleElementId InElementId)`
- L577 _public function_ `void RemoveDataForElement(const FTypedHandleElementId InElementId, const FTypedElementInternalData* InExpectedDataPtr)`
- L590 _public function_ `const TTypedElementInternalData<ElementDataType>& GetDataForElement(const FTypedHandleElementId InElementId) const`
- L598 _public function_ `static inline void SetStaticDataTypeId(const FTypedHandleTypeId InTypeId)`
- L604 _public function_ `static inline FTypedHandleTypeId StaticDataTypeId()`
- L609 _public function_ `static inline FName StaticDataTypeName()`
- L615 _private member_ `mutable FTransactionallySafeRWLock InternalDataRW;`
- L616 _private member_ `TArray<int32> InternalDataFreeIndices;`
- L617 _private member_ `TChunkedArray<TTypedElementInternalData<ElementDataType>> InternalDataArray;`
- L618 _private member_ `TMap<FTypedHandleElementId, FScriptTypedElementInternalDataOwner> ScriptInternalDataMap;`
- L631 _public function_ `TTypedElementInternalData<void>& AddDataForElement(const FTypedHandleTypeId InTypeId, FTypedHandleElementId& InOutElementId)`
- L685 _public function_ `const TTypedElementInternalData<void>& GetDataForElement(const FTypedHandleElementId InElementId) const`
- L710 _private member_ `TChunkedArray<TTypedElementInternalData<void>> InternalDataArray;`
- L712 _private member_ `TMap<FTypedHandleElementId, int32> ElementIdToArrayIndex;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_DECLARE_TYPED_ELEMENT_DATA_RTTI(ELEMENT_DATA_TYPE, ...) \` — Macro to declare the required RTTI data for types representing element data. @note Place this in the public section of your type declaration.
- L27 _macro_ `#define UE_DEFINE_TYPED_ELEMENT_DATA_RTTI(ELEMENT_DATA_TYPE) \` — Macro to define the required RTTI data for types representing element data. @note Place this in the cpp file for your type definition.
- L35 _function_ `template <typename ElementDataType> inline FString GetTypedElementDebugId(const ElementDataType& InElementData)` — Templated util to get the low-level debug ID for an element data instance. Specialize this to provide exta/custom data for your element data type.

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementDataStorageWidget.h` (Public)


#### class `UE::Editor::DataStorage::ITedsWidget`  
`class ITedsWidget`  
_L10-20_
- L13 _public prototype_ `virtual ~ITedsWidget() = default;`
- L15 _public prototype_ `virtual RowHandle GetRowHandle() const = 0;`
- L17 _public prototype_ `virtual void SetContent(const TSharedRef< SWidget >& InContent) = 0;`
- L19 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L25 _typedef_ `using STedsWidget UE_DEPRECATED(5.6, "Use the new ITedsWidget interface directly` — This is for backwards compatibility with the STedsWidget class in the global namespace that used to exist in this file but has been replaced by the ITedsWidget interface

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementHandle.h` (Public)


#### struct `FTypedElementHandle`  
`struct FTypedElementHandle`  
_L17-264_
- desc: A representation of an element that includes its handle data. This type is the most standard way that an element is passed through to interfaces, and also the type that is stored in element lists. C++ code may choose to use TTypedElement instead, which is a combination of an element handle and its associated element interface. @note Handles auto-release on destruction.
- L20 _public prototype_ `FTypedElementHandle() = default;`
- L22 _public function_ `FTypedElementHandle(const FTypedElementHandle& InOther)`
- L30 _public function_ `FTypedElementHandle& operator=(const FTypedElementHandle& InOther)`
- L44 _public function_ `FTypedElementHandle(FTypedElementHandle&& InOther) : DataPtr(InOther.DataPtr) #if UE_TYPED_ELEMENT_HAS_REFTRACKING , ReferenceId(InOther.ReferenceId) #endif`
- L57 _public function_ `FTypedElementHandle& operator=(FTypedElementHandle&& InOther)`
- L77 _public function_ `~FTypedElementHandle()`
- L82 _public function_ `inline explicit operator bool() const`
- L90 _public function_ `inline bool IsSet() const` — Has this handle been initialized to a valid element?
- L98 _public function_ `inline void Release()` — Release this handle and set it back to an empty state.
- L106 _public function_ `inline const FTypedElementId& GetId() const` — Get the ID that this element represents.
- L118 _public function_ `template <typename ElementDataType> inline bool IsDataOfType() const` — Test to see whether the data stored within this handle is of the given type. @note This is not typically something you'd want to query outside of data access within an interface implementation.
- L128 _public function_ `template <typename ElementDataType> const ElementDataType* GetData(const bool bSilent = false) const` — Attempt to access the data stored within this handle as the given type, returning null if it isn't possible and logging an access error for scripting. @note This is not typically something you'd want to use outside of data access within an interface implementation.
- L156 _public function_ `template <typename ElementDataType> inline const ElementDataType& GetDataChecked() const` — Attempt to access the data stored within this handle as the given type, asserting if it isn't possible. @note This is not typically something you'd want to use outside of data access within an interface implementation.
- L167 _public function_ `FTypedElementId AcquireId() const` — Acquire a copy of the ID that this element represents. @note This must be paired with a call to ReleaseId.
- L182 _public function_ `void ReleaseId(FTypedElementId& InOutElementId) const` — Release a copy of the ID that this element represents. @note This should have come from a call to AcquireId.
- L207 _public function_ `inline void Private_InitializeNoRef(const FTypedElementInternalData& InData)`
- L212 _public function_ `inline void Private_InitializeAddRef(const FTypedElementInternalData& InData)`
- L218 _public function_ `inline void Private_DestroyNoRef()`
- L226 _public function_ `inline void Private_DestroyReleaseRef()`
- L232 _public function_ `inline const FTypedElementInternalData* Private_GetInternalData() const`
- L238 _private function_ `inline void RegisterRef()`
- L249 _private function_ `inline void UnregisterRef()`
- L260 _private member_ `const FTypedElementInternalData* DataPtr = nullptr;`
- L262 _private member_ `FTypedElementReferenceId ReferenceId = INDEX_NONE;`

#### struct `TTypedElementBase`  
`template <typename BaseInterfaceType> struct TTypedElementBase : public FTypedElementHandle`  
_L270-387_
- inherits: `FTypedElementHandle`
- desc: Common implementation of TTypedElement that is inherited by all specializations.
- L273 _public prototype_ `TTypedElementBase() = default;`
- L275 _public prototype_ `TTypedElementBase(const TTypedElementBase&) = default;`
- L276 _public prototype_ `TTypedElementBase& operator=(const TTypedElementBase&) = default;`
- L278 _public function_ `TTypedElementBase(TTypedElementBase&& InOther) : FTypedElementHandle(MoveTemp(InOther)) , InterfacePtr(InOther.InterfacePtr)`
- L286 _public function_ `TTypedElementBase& operator=(TTypedElementBase&& InOther)`
- L299 _public function_ `~TTypedElementBase()`
- L304 _public function_ `inline explicit operator bool() const`
- L312 _public function_ `inline bool IsSet() const` — Has this element been initialized to a valid handle and interface?
- L321 _public function_ `inline void Release()` — Release this element and set it back to an empty state.
- L329 _public function_ `inline BaseInterfaceType* GetInterface() const` — Attempt to access the interface stored within this element, returning null if it isn't set.
- L338 _public function_ `template <typename U = BaseInterfaceType, std::enable_if_t<!std::is_void<U>::value>* = nullptr> inline U& GetInterfaceChecked() const` — Attempt to access the interface stored within this element, asserting if it isn't set.
- L361 _public function_ `inline void Private_InitializeNoRef(const FTypedElementInternalData& InData, BaseInterfaceType* InInterfacePtr)`
- L367 _public function_ `inline void Private_InitializeAddRef(const FTypedElementInternalData& InData, BaseInterfaceType* InInterfacePtr)`
- L373 _public function_ `inline void Private_DestroyNoRef()`
- L379 _public function_ `inline void Private_DestroyReleaseRef()`
- L386 _protected member_ `BaseInterfaceType* InterfacePtr = nullptr;`

#### struct `TTypedElement`  
`template <typename BaseInterfaceType> struct TTypedElement : public TTypedElementBase<BaseInterfaceType>`  
_L395-397_
- inherits: `TTypedElementBase<BaseInterfaceType>`
- desc: A combination of an element handle and its associated element interface. @note This should be specialized for top-level element interfaces to include their interface API. @note Elements auto-release on destruction.

#### struct `TTypedElementOwner`  
`template <typename ElementDataType> struct TTypedElementOwner`  
_L408-611_
- desc: A representation of the owner of an element that includes its mutable handle data. This type is returned when creating an element, and should be used to populate its internal payload data (if any). @note Owners do not auto-release on destruction, and must be manually destroyed via their owner element registry.
- L411 _public prototype_ `TTypedElementOwner() = default;`
- L413 _public prototype_ `TTypedElementOwner(const TTypedElementOwner&) = delete;`
- L414 _public prototype_ `TTypedElementOwner& operator=(const TTypedElementOwner&) = delete;`
- L416 _public function_ `TTypedElementOwner(TTypedElementOwner&& InOther) : DataPtr(InOther.DataPtr)`
- L423 _public function_ `TTypedElementOwner& operator=(TTypedElementOwner&& InOther)`
- L435 _public function_ `~TTypedElementOwner()`
- L440 _public function_ `inline explicit operator bool() const`
- L448 _public function_ `inline bool IsSet() const` — Has this owner been initialized to a valid element?
- L456 _public function_ `inline const FTypedElementId& GetId() const` — Get the ID that this element represents.
- L467 _public function_ `template <typename U = ElementDataType, std::enable_if_t<!std::is_void<U>::value>* = nullptr> inline U* GetData() const` — Attempt to access the mutable data stored within this owner, returning null if it isn't possible.
- L479 _public function_ `template <typename U = ElementDataType, std::enable_if_t<!std::is_void<U>::value>* = nullptr> inline U& GetDataChecked() const` — Attempt to access the mutable data stored within this owner, asserting if it isn't possible.
- L490 _public function_ `FTypedElementId AcquireId() const` — Acquire a copy of the ID that this element represents. @note This must be paired with a call to ReleaseId.
- L505 _public function_ `void ReleaseId(FTypedElementId& InOutElementId) const` — Release a copy of the ID that this element represents. @note This should have come from a call to AcquireId.
- L519 _public function_ `FTypedElementHandle AcquireHandle() const` — Acquire a copy of the handle that this element represents. @note This must be paired with a call to ReleaseHandle (or a call to Release on the handle instance).
- L533 _public function_ `void ReleaseHandle(FTypedElementHandle& InOutElementHandle) const` — Release a copy of the handle that this element represents. @note This should have come from a call to AcquireHandle.
- L554 _public function_ `inline void Private_InitializeNoRef(TTypedElementInternalData<ElementDataType>& InData)`
- L559 _public function_ `inline void Private_InitializeAddRef(TTypedElementInternalData<ElementDataType>& InData)`
- L565 _public function_ `inline void Private_DestroyNoRef()`
- L573 _public function_ `inline void Private_DestroyReleaseRef()`
- L579 _public function_ `inline const TTypedElementInternalData<ElementDataType>* Private_GetInternalData() const`
- L585 _private function_ `inline void RegisterRef()`
- L596 _private function_ `inline void UnregisterRef()`
- L607 _private member_ `TTypedElementInternalData<ElementDataType>* DataPtr = nullptr;`
- L609 _private member_ `FTypedElementReferenceId ReferenceId = INDEX_NONE;`

#### struct `FScriptTypedElementHandle`  
`struct FScriptTypedElementHandle`  
_L624-705_
- reflection: `USTRUCT(BlueprintType)`
- desc: Script exposure for the typed element handle struct type Act as a weak handle to simplify the scripting use of the typed element framework and making it safer to use by avoiding crash in case of a bad usage. This type is the standard way that an element is passed through to interfaces for a script (Blueprint or Python), and also the type that is stored in the script element lists. C++ code may choose to use TTypedElement instead, which is a combination of an element handle and its associated element interface. Note: This type shouldn't be used in the engine code as it come with a performance and memory overhead that we want to avoid when compare to the native handles (FTypedElementHandle).
- L629 _public prototype_ `FScriptTypedElementHandle() = default;`
- L631 _public function_ `FScriptTypedElementHandle(const FScriptTypedElementHandle& InOther) : InternalData(InOther.InternalData)`
- L636 _public function_ `FScriptTypedElementHandle(FScriptTypedElementHandle&& InOther) : InternalData(MoveTemp(InOther.InternalData))`
- L641 _public function_ `FScriptTypedElementHandle& operator=(const FScriptTypedElementHandle& InOther)`
- L647 _public function_ `FScriptTypedElementHandle& operator=(FScriptTypedElementHandle&& InOther)`
- L653 _public function_ `inline bool operator==(const FScriptTypedElementHandle& InOther) const`
- L658 _public function_ `inline bool operator!=(const FScriptTypedElementHandle& InOther) const`
- L663 _public function_ `inline explicit operator bool() const`
- L668 _public function_ `inline bool IsSet() const`
- L673 _public function_ `inline void Release()`
- L678 _public function_ `inline void Private_Initialize(FScriptTypedElementInternalDataPtr&& InInternalData)`
- L683 _public function_ `inline const FTypedElementId& GetId() const`
- L692 _public function_ `FTypedElementHandle GetTypedElementHandle() const` — Return typed element handle from the script typed element handle If this script handle is invalid it will return a invalid TypedElementHandle
- L704 _private member_ `FScriptTypedElementInternalDataPtr InternalData;`

#### class `UTypedElementHandleLibrary`  
`class UTypedElementHandleLibrary : public UObject`  
_L709-749_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Script exposure for FScriptTypedElementHandle.
- L718 _public function_ `static bool IsSet(const FScriptTypedElementHandle& ElementHandle)` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Handle", meta=(ScriptMethod, ScriptOperator="bool"))` — Has this handle been initialized to a valid element?
- L727 _public function_ `static void Release(UPARAM(ref) FScriptTypedElementHandle& ElementHandle)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|Handle", meta=(ScriptMethod))` — Release this handle and set it back to an empty state.
- L736 _public function_ `static bool Equal(const FScriptTypedElementHandle& LHS, const FScriptTypedElementHandle& RHS)` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Handle", meta=(DisplayName="Equal (TypedElementHandle)", CompactNodeTitle="==", Keywords="== equal", ScriptMethod, ScriptOperator="=="))` — Are these two handles equal?
- L745 _public function_ `static bool NotEqual(const FScriptTypedElementHandle& LHS, const FScriptTypedElementHandle& RHS)` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Handle", meta=(DisplayName="NotEqual (TypedElementHandle)", CompactNodeTitle="!=", Keywords="!= not equal", ScriptMethod, ScriptOperator="!="))` — Are these two handles not equal?

#### Free symbols / members of external scopes

- L192 _function_ `inline friend bool operator==(const FTypedElementHandle& InLHS, const FTypedElementHandle& InRHS)`
- L197 _function_ `inline friend bool operator!=(const FTypedElementHandle& InLHS, const FTypedElementHandle& InRHS)`
- L202 _function_ `friend inline uint32 GetTypeHash(const FTypedElementHandle& InElementHandle)`
- L345 _function_ `inline friend bool operator==(const TTypedElementBase& InLHS, const TTypedElementBase& InRHS)`
- L351 _function_ `inline friend bool operator!=(const TTypedElementBase& InLHS, const TTypedElementBase& InRHS)`
- L356 _function_ `friend inline uint32 GetTypeHash(const TTypedElementBase& InElement)`
- L400 _typedef_ `using FTypedElement = TTypedElement<void>;` — The typed element InterfacePtr will points toward the vtable of the interface
- L539 _function_ `inline friend bool operator==(const TTypedElementOwner& InLHS, const TTypedElementOwner& InRHS)`
- L544 _function_ `inline friend bool operator!=(const TTypedElementOwner& InLHS, const TTypedElementOwner& InRHS)`
- L549 _function_ `friend inline uint32 GetTypeHash(const TTypedElementOwner& InElementOwner)`
- L612 _typedef_ `using FTypedElementOwner = TTypedElementOwner<void>;`

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementId.h` (Public)


#### struct `FTypedElementId`  
`struct FTypedElementId`  
_L16-129_
- desc: The most minimal representation of an element - its ID! This type is not immediately useful on its own, but can be used to find an element from the element registry or an element list. @note This is ref-counted like handles themselves are, so as long as an ID is available, the handle will be too. @note IDs lack the information needed to auto-release on destruction, so must be manually released, either via the corresponding handle or their owner element registry.
- L19 _public function_ `FTypedElementId() : CombinedId(0)`
- L24 _public prototype_ `FTypedElementId(const FTypedElementId&) = delete;`
- L25 _public prototype_ `FTypedElementId& operator=(const FTypedElementId&) = delete;`
- L27 _public function_ `FTypedElementId(FTypedElementId&& InOther) : CombinedId(InOther.CombinedId)`
- L33 _public function_ `FTypedElementId& operator=(FTypedElementId&& InOther)`
- L44 _public function_ `~FTypedElementId()`
- L49 _public function_ `inline explicit operator bool() const`
- L57 _public function_ `inline bool IsSet() const` — Has this ID been initialized to a valid element?
- L65 _public function_ `inline FTypedHandleTypeId GetTypeId() const` — Access the type ID portion of this element ID.
- L73 _public function_ `inline FTypedHandleElementId GetElementId() const` — Access the element ID portion of this element ID.
- L83 _public function_ `inline FTypedHandleCombinedId GetCombinedId() const` — Access the combined value of this element ID. @note You typically don't want to store this directly as the element ID could be re-used. It is primarily useful as a secondary cache where something is keeping a reference to an element ID or element handle (eg, how FTypedElementList uses it internally).
- L104 _public function_ `inline void Private_InitializeNoRef(const FTypedHandleTypeId InTypeId, const FTypedHandleElementId InElementId)`
- L110 _public function_ `inline void Private_DestroyNoRef()`
- L116 _public member_ `static const FTypedElementId Unset;` — An unset element ID

#### union `FTypedElementId::(anonymous)`  
``  
_L120-128_

#### struct `FTypedElementId::__anone64c4820010a::(anonymous)`  
``  
_L122-126_

#### Free symbols / members of external scopes

- L88 _function_ `inline friend bool operator==(const FTypedElementId& InLHS, const FTypedElementId& InRHS)`
- L93 _function_ `inline friend bool operator!=(const FTypedElementId& InLHS, const FTypedElementId& InRHS)`
- L98 _function_ `friend inline uint32 GetTypeHash(const FTypedElementId& InElementId)`
- L124 _member_ `FTypedHandleCombinedId ElementId : TypedHandleElementIdBits;` (scope `FTypedElementId::__anone64c4820010a::__anone64c48200208`) — Note: These are arranged in this order to give CombinedId better hash distribution for GetTypeHash!
- L125 _member_ `FTypedHandleCombinedId TypeId : TypedHandleTypeIdBits;` (scope `FTypedElementId::__anone64c4820010a::__anone64c48200208`)
- L127 _member_ `FTypedHandleCombinedId CombinedId;` (scope `FTypedElementId::__anone64c4820010a`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementIndexHasher.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _prototype_ `IndexHash GenerateIndexHash(const T* Object);` (scope `UE::Editor::DataStorage`) — `UE_DEPRECATED(5.6, "Use FMapKey(View) with the new mapping functions.")`
- L22 _prototype_ `IndexHash GenerateIndexHash(const TWeakObjectPtr<T>& Object);` (scope `UE::Editor::DataStorage`) — `UE_DEPRECATED(5.6, "Use FMapKey(View) with the new mapping functions.")`
- L25 _prototype_ `IndexHash GenerateIndexHash(const TObjectPtr<T>& Object);` (scope `UE::Editor::DataStorage`) — `UE_DEPRECATED(5.6, "Use FMapKey(View) with the new mapping functions.")`
- L28 _prototype_ `IndexHash GenerateIndexHash(const TStrongObjectPtr<T>& Object);` (scope `UE::Editor::DataStorage`) — `UE_DEPRECATED(5.6, "Use FMapKey(View) with the new mapping functions.")`
- L31 _prototype_ `inline IndexHash GenerateIndexHash(const FString& Object);` (scope `UE::Editor::DataStorage`) — `UE_DEPRECATED(5.6, "Use FMapKey(View) with the new mapping functions.")`
- L33 _prototype_ `inline IndexHash GenerateIndexHash(FStringView Object);` (scope `UE::Editor::DataStorage`) — `UE_DEPRECATED(5.6, "Use FMapKey(View) with the new mapping functions.")`
- L35 _prototype_ `inline IndexHash GenerateIndexHash(FName Object);` (scope `UE::Editor::DataStorage`) — `UE_DEPRECATED(5.6, "Use FMapKey(View) with the new mapping functions.")`
- L37 _prototype_ `inline IndexHash GenerateIndexHash(const FSoftObjectPath& ObjectPath);` (scope `UE::Editor::DataStorage`) — `UE_DEPRECATED(5.6, "Use FMapKey(View) with the new mapping functions.")`

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementIndexHasher.inl` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L11 _function_ `template<typename T> IndexHash GenerateIndexHash(const T* Object)` (scope `UE::Editor::DataStorage`)
- L17 _function_ `template<typename T> IndexHash GenerateIndexHash(const TWeakObjectPtr<T>& Object)` (scope `UE::Editor::DataStorage`)
- L23 _function_ `template<typename T> IndexHash GenerateIndexHash(const TObjectPtr<T>& Object)` (scope `UE::Editor::DataStorage`)
- L29 _function_ `template<typename T> IndexHash GenerateIndexHash(const TStrongObjectPtr<T>& Object)` (scope `UE::Editor::DataStorage`)
- L34 _function_ `IndexHash GenerateIndexHash(const FString& Object)` (scope `UE::Editor::DataStorage`)
- L39 _function_ `IndexHash GenerateIndexHash(FStringView Object)` (scope `UE::Editor::DataStorage`)
- L44 _function_ `IndexHash GenerateIndexHash(FName Object)` (scope `UE::Editor::DataStorage`)
- L51 _function_ `IndexHash GenerateIndexHash(const FSoftObjectPath& ObjectPath)` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementLimits.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_TYPED_ELEMENT_HAS_REFCOUNTING (1)`
- L9 _macro_ `#define UE_TYPED_ELEMENT_HAS_REFTRACKING (UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT || WITH_EDITOR)`
- L10 _macro_ `#define UE_TYPED_ELEMENT_HAS_REFERENCING (UE_TYPED_ELEMENT_HAS_REFCOUNTING || UE_TYPED_ELEMENT_HAS_REFTRACKING)`
- L17 _variable_ `inline constexpr SIZE_T TypedHandleTypeIdBits = 8;` — Handle ID limits, as used by FTypedElementId. @note Limited to a combined 32-bits so that they can be used directly within render targets, though could be made 64-bits if the editor used 64-bit render targets (this would also require 64-bit container support in TTypedElementInternalDataStore).
- L18 _variable_ `inline constexpr SIZE_T TypedHandleElementIdBits = 24;`
- L20 _variable_ `inline constexpr SIZE_T TypedHandleTypeIdBytes = TypedHandleTypeIdBits >> 3;`
- L21 _variable_ `inline constexpr SIZE_T TypedHandleElementIdBytes = TypedHandleElementIdBits >> 3;`
- L23 _variable_ `inline constexpr SIZE_T TypedHandleMaxTypeId = ((SIZE_T)1 << TypedHandleTypeIdBits) - 1;`
- L24 _variable_ `inline constexpr SIZE_T TypedHandleMaxElementId = ((SIZE_T)1 << TypedHandleElementIdBits) - 1;`
- L26 _variable_ `inline constexpr SIZE_T TypedHandleRefTrackingSkipCount = 1;`
- L27 _variable_ `inline constexpr SIZE_T TypedHandleRefTrackingDepth = 31;`
- L29 _typedef_ `using FTypedHandleTypeId = uint8;`
- L30 _typedef_ `using FTypedHandleElementId = int32;`
- L31 _typedef_ `using FTypedHandleCombinedId = uint32;`
- L33 _typedef_ `using FTypedElementRefCount = int32;`
- L34 _typedef_ `using FTypedElementReferenceId = int32;`

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementList.h` (Public)


#### class `TTypedElementList`  
`template<class HandleType> class TTypedElementList final : public TSharedFromThis<TTypedElementList<HandleType>>`  
_L61-773_
- inherits: `TSharedFromThis<TTypedElementList<HandleType>>`
- desc: A list of element handles. Provides high-level access to groups of elements, including accessing elements that implement specific interfaces.
- L65 _public typedef_ `using FHandleType = HandleType;`
- L66 _public typedef_ `using TTypedElementListRef = TSharedRef<TTypedElementList>;`
- L67 _public typedef_ `using TTypedElementListConstRef = TSharedRef<const TTypedElementList>;`
- L70 _public prototype_ `~TTypedElementList();`
- L76 _public prototype_ `TTypedElementListRef Clone() const;` — Clone this list instance. @note Only copies elements; does not copy any bindings!
- L82 _public function_ `inline HandleType operator[](const int32 InIndex) const` — Get the element handle at the given index. @note Use IsValidIndex to test for validity.
- L91 _public function_ `inline HandleType GetElementHandleAt(const int32 InIndex) const` — Get the element handle at the given index. @note Use IsValidIndex to test for validity.
- L101 _public function_ `template <typename BaseInterfaceType> inline TTypedElement<BaseInterfaceType> GetElementAt(const int32 InIndex) const` — Get the element at the given index. @note Use IsValidIndex to test for validity.
- L111 _public function_ `template <typename BaseInterfaceType> inline void GetElementAt(const int32 InIndex, TTypedElement<BaseInterfaceType>& OutElement) const` — Get the element at the given index. @note Use IsValidIndex to test for validity.
- L120 _public function_ `template <typename BaseInterfaceType> inline TTypedElement<BaseInterfaceType> GetElement(const HandleType& InElementHandle) const` — Get the element from the given handle.
- L129 _public function_ `template <typename BaseInterfaceType> inline void GetElement(const HandleType& InElementHandle, TTypedElement<BaseInterfaceType>& OutElement) const` — Get the element from the given handle.
- L138 _public function_ `template <typename BaseInterfaceType> TTypedElement<BaseInterfaceType> GetTopElement() const` — Get the first element implementing the given interface.
- L157 _public function_ `template <typename BaseInterfaceType> TTypedElement<BaseInterfaceType> GetTopElement(TFunctionRef<bool (const TTypedElement<BaseInterfaceType>&)> Predicate) const` — Get the first element that implement the given interface and pass the predicate @Predicate A function that should return true when the element is desirable
- L178 _public function_ `template <typename BaseInterfaceType> TTypedElement<BaseInterfaceType> GetBottomElement() const` — Get the last element implementing the given interface.
- L197 _public function_ `template <typename BaseInterfaceType> TTypedElement<BaseInterfaceType> GetBottomElement(TFunctionRef<bool (const TTypedElement<BaseInterfaceType>&)> Predicate) const` — Get the last element that implement the given interface and pass the predicate. @Predicate A function that return should true when the element is desirable
- L219 _public function_ `template <typename BaseInterfaceType> BaseInterfaceType* GetElementInterface(const FTypedElementHandle& InElementHandle) const` — Get the element interface from the given handle.
- L227 _public prototype_ `UObject* GetElementInterface(const HandleType& InElementHandle, const TSubclassOf<UInterface>& InBaseInterfaceType) const;` — Get the element interface from the given handle.
- L232 _public prototype_ `bool HasElements(const TSubclassOf<UInterface>& InBaseInterfaceType = {}) const;` — Test whether there are elements in this list, optionally filtering to elements that implement the given interface.
- L237 _public prototype_ `int32 CountElements(const TSubclassOf<UInterface>& InBaseInterfaceType = {}) const;` — Count the number of elements in this list, optionally filtering to elements that implement the given interface.
- L242 _public prototype_ `bool HasElementsOfType(const FName InElementTypeName) const;` — Test whether there are elements in this list of the given type.
- L243 _public prototype_ `bool HasElementsOfType(const FTypedHandleTypeId InElementTypeId) const;`
- L248 _public prototype_ `int32 CountElementsOfType(const FName InElementTypeName) const;` — Count the number of elements in this list of the given type.
- L249 _public prototype_ `int32 CountElementsOfType(const FTypedHandleTypeId InElementTypeId) const;`
- L254 _public prototype_ `TArray<HandleType> GetElementHandles(const TSubclassOf<UInterface>& InBaseInterfaceType = {}) const;` — Get the handle of every element in this list, optionally filtering to elements that implement the given interface.
- L260 _public function_ `template <typename ArrayAllocator> void GetElementHandles(TArray<HandleType, ArrayAllocator>& OutArray, const TSubclassOf<UInterface>& InBaseInterfaceType = {}) const` — Get the handle of every element in this list, optionally filtering to elements that implement the given interface.
- L275 _public prototype_ `void ForEachElementHandle(TFunctionRef<bool(const HandleType&)> InCallback, const TSubclassOf<UInterface>& InBaseInterfaceType = {}) const;` — Enumerate the handle of every element in this list, optionally filtering to elements that implement the given interface. @note Return true from the callback to continue enumeration.
- L282 _public function_ `template <typename BaseInterfaceType> void ForEachElement(TFunctionRef<bool(const TTypedElement<BaseInterfaceType>&)> InCallback) const` — Enumerate the elements in this list that implement the given interface. @note Return true from the callback to continue enumeration.
- L298 _public function_ `inline bool IsValidIndex(const int32 InIndex) const` — Is the given index a valid entry within this element list?
- L306 _public function_ `inline int32 Num() const` — Get the number of entries within this element list.
- L314 _public function_ `inline void Shrink()` — Shrink this element list storage to avoid slack.
- L323 _public function_ `inline void Reserve(const int32 InSize)` — Pre-allocate enough memory in this element list to store the given number of entries.
- L332 _public function_ `inline void Empty(const int32 InSlack = 0)` — Remove all entries from this element list, potentially leaving space allocated for the given number of entries.
- L355 _public function_ `inline void Reset()` — Remove all entries from this element list, preserving existing allocations.
- L371 _public function_ `inline bool Contains(const FTypedElementId& InElementId) const` — Does this element list contain an entry for the given element ID?
- L379 _public function_ `inline bool Contains(const HandleType& InElementHandle) const` — Does this element list contain an entry for the given element handle?
- L388 _public function_ `template <typename ElementDataType> inline bool Contains(const TTypedElementOwner<ElementDataType>& InElementOwner)` — Does this element list contain an entry for the given element owner?
- L397 _public function_ `inline bool Add(const HandleType& InElementHandle)` — Add the given element handle to this element list, if it isn't already in the list. @return True if the element handle was added, false if it is already in the list.
- L406 _public function_ `inline bool Add(HandleType&& InElementHandle)` — Add the given element handle to this element list, if it isn't already in the list. @return True if the element handle was added, false if it is already in the list.
- L416 _public function_ `template <typename ElementDataType> inline bool Add(const TTypedElementOwner<ElementDataType>& InElementOwner)` — Add the given element owner to this element list, if it isn't already in the list. @return True if the element owner was added, false if it is already in the list.
- L424 _public function_ `void Append(const TTypedElementListConstRef& InElementList)` — Append another element list to this element list.
- L442 _public function_ `void Append(TArrayView<const HandleType> InElementHandles)` — Append the given element handles to this element list.
- L457 _public function_ `template <typename ElementDataType> inline void Append(const TArray<TTypedElementOwner<ElementDataType>>& InElementOwners)` — Append the given element owners to this element list.
- L466 _public function_ `template <typename ElementDataType> void Append(TArrayView<const TTypedElementOwner<ElementDataType>> InElementOwners)` — Append the given element owners to this element list.
- L481 _public function_ `inline bool Remove(const FTypedElementId& InElementId)` — Remove the given element ID from this element list, if it is in the list. @return True if the element ID was removed, false if it isn't in the list.
- L490 _public function_ `inline bool Remove(const HandleType& InElementHandle)` — Remove the given element handle from this element list, if it is in the list. @return True if the element handle was removed, false if it isn't in the list.
- L500 _public function_ `template <typename ElementDataType> inline bool Remove(const TTypedElementOwner<ElementDataType>& InElementOwner)` — Remove the given element owner from this element list, if it is in the list. @return True if the element owner was removed, false if it isn't in the list.
- L509 _public function_ `inline int32 RemoveAll(TFunctionRef<bool(const HandleType&)> InPredicate)` — Remove any element handles that match the given predicate from this element list. @return The number of element handles removed.
- L519 _public function_ `template <typename BaseInterfaceType> int32 RemoveAll(TFunctionRef<bool(const TTypedElement<BaseInterfaceType>&)> InPredicate)` — Remove any elements that match the given predicate from this element list. @return The number of elements removed.
- L532 _public function_ `const FTypedElementCounter& GetCounter() const` — Get the counter for the elements within the list.
- L541 _public prototype_ `DECLARE_EVENT_OneParam(TTypedElementList, FOnPreChange, const TTypedElementList& );` — Access the delegate that is invoked whenever this element list is potentially about to change. @note This may be called even if no actual change happens, so may be called multiple times without a corresponding OnChanged notification.
- L542 _public function_ `FOnPreChange& OnPreChange()`
- L551 _public prototype_ `DECLARE_EVENT_OneParam(TTypedElementList, FOnChanged, const TTypedElementList& );` — Access the delegate that is invoked whenever this element list has been changed. @note This is called automatically at the end of each frame, but can also be manually invoked by NotifyPendingChanges.
- L552 _public function_ `FOnChanged& OnChanged()`
- L561 _public prototype_ `bool NotifyPendingChanges();` — Invoke the delegate called whenever this element list has been changed. @return true if a change notification was emitted
- L675 _public prototype_ `FScopedClearNewPendingChange GetScopedClearNewPendingChange();` — Get a scoped object that when destroyed it clear a pending change notification without emitting the notification if it happened during its lifecycle.
- L681 _public prototype_ `FLegacySync& Legacy_GetSync();` — Access the interface to allow external systems (such as USelection) to receive immediate sync notifications as an element list is changed. This exists purely as a bridging mechanism and shouldn't be relied on for new code. It is lazily created as needed.
- L687 _public prototype_ `FLegacySync* Legacy_GetSyncPtr() const;` — Access the interface to allow external systems (such as USelection) to receive immediate sync notifications as an element list is changed. This exists purely as a bridging mechanism and shouldn't be relied on for new code. This will return null if no legacy sync has been created for this instance.
- L692 _public prototype_ `static TTypedElementListRef Private_CreateElementList(UTypedElementRegistry* InRegistry);` — Internal function used by the element registry to create an element list instance.
- L694 _public function_ `UTypedElementRegistry* GetRegistry() const`
- L721 _private prototype_ `explicit TTypedElementList(UTypedElementRegistry* InRegistry);`
- L723 _private prototype_ `bool AddElementImpl(HandleType&& InElementHandle);`
- L724 _private prototype_ `bool RemoveElementImpl(const FTypedElementId& InElementId);`
- L725 _private prototype_ `int32 RemoveAllElementsImpl(TFunctionRef<bool(const HandleType&)> InPredicate);`
- L726 _private prototype_ `bool ContainsElementImpl(const FTypedElementId& InElementId) const;`
- L728 _private prototype_ `void NoteListMayChange();`
- L729 _private prototype_ `void NoteListChanged(const EChangeType InChangeType, const HandleType& InElementHandle = HandleType());`
- L734 _private member_ `TWeakObjectPtr<UTypedElementRegistry> Registry;` — Element registry this element list is associated with.
- L740 _private member_ `TSet<FTypedHandleCombinedId> ElementCombinedIds;` — Set of combined ID values that are currently present in this element list. Used to perform optimized querying of which elements are in this list, and to avoid adding duplicate entries.
- L746 _private member_ `TArray<HandleType> ElementHandles;` — Array of element handles present in this element list. These are stored in the same order that they are added, and the set above can be used to optimize certain queries.
- L751 _private member_ `FTypedElementCounter ElementCounts;` — Tracks various categories of counters for the elements within the list (eg, the number of elements of a given type).
- L756 _private member_ `FOnPreChange OnPreChangeDelegate;` — Delegate that is invoked whenever this element list is potentially about to change.
- L761 _private member_ `FOnChanged OnChangedDelegate;` — Delegate that is invoked whenever this element list has been changed.
- L766 _private member_ `bool bHasPendingNotify = false;` — Whether there are pending changes for OnChangedDelegate to notify for.
- L772 _private member_ `TUniquePtr<FLegacySync> LegacySync;` — Interface to allow external systems (such as USelection) to receive immediate sync notifications as an element list is changed. This exists purely as a bridging mechanism and shouldn't be relied on for new code. It is lazily created as needed.

#### struct `TTypedElementList::FScopedClearNewPendingChange`  
`struct FScopedClearNewPendingChange`  
_L567-582_
- desc: A utility struct that help to cancel any new pending notification that happened in a scope. Note: it won't cancel a notification if there is a legacy batch operation ongoing
- L569 _public prototype_ `FScopedClearNewPendingChange() = default;`
- L570 _public prototype_ `FScopedClearNewPendingChange(TTypedElementList& InTypeElementList);`
- L572 _public prototype_ `FScopedClearNewPendingChange(const FScopedClearNewPendingChange&) = delete;`
- L573 _public prototype_ `FScopedClearNewPendingChange& operator=(const FScopedClearNewPendingChange&) = delete;`
- L575 _public prototype_ `FScopedClearNewPendingChange(FScopedClearNewPendingChange&& Other);`
- L576 _public prototype_ `FScopedClearNewPendingChange& operator=(FScopedClearNewPendingChange&& Other);`
- L578 _public prototype_ `~FScopedClearNewPendingChange();`
- L581 _private member_ `TTypedElementList* TypedElementList = nullptr;`

#### class `TTypedElementList::FLegacySync`  
`class FLegacySync`  
_L588-646_
- desc: Interface to allow external systems (such as USelection) to receive immediate sync notifications as an element list is changed. This exists purely as a bridging mechanism and shouldn't be relied on for new code. It is lazily created as needed.
- L626 _public prototype_ `FLegacySync(const TTypedElementList& InElementList);`
- L628 _public prototype_ `void Private_EmitSyncEvent(const ESyncType InSyncType, const HandleType& InElementHandle = HandleType());`
- L630 _public prototype_ `DECLARE_EVENT_FourParams(FLegacySync, FOnSyncEvent, const TTypedElementList& , ESyncType , const HandleType& , bool );`
- L631 _public prototype_ `FOnSyncEvent& OnSyncEvent();`
- L633 _public prototype_ `bool IsRunningBatchOperation() const;`
- L634 _public prototype_ `void BeginBatchOperation();`
- L635 _public prototype_ `void EndBatchOperation(const bool InNotify = true);`
- L636 _public prototype_ `bool IsBatchOperationDirty() const;`
- L637 _public prototype_ `void ForceBatchOperationDirty();`
- L640 _private member_ `const TTypedElementList& ElementList;`
- L642 _private member_ `FOnSyncEvent OnSyncEventDelegate;`
- L644 _private member_ `int32 NumOpenBatchOperations = 0;`
- L645 _private member_ `bool bBatchOperationIsDirty = false;`

#### enum `TTypedElementList::FLegacySync::ESyncType`  
`enum class ESyncType : uint8`  
_L591-624_
- L597 _public enumerator_ `Added` — An element was added to the element list. The ElementHandle argument will be set to the element that was added.
- L603 _public enumerator_ `Removed` — An element was removed from the element list. The ElementHandle argument will be set to the element that was removed.
- L609 _public enumerator_ `Modified` — The element list was modified in an unknown way. The ElementHandle argument will be unset.
- L615 _public enumerator_ `Cleared` — The element list was cleared. The ElementHandle argument will be unset.
- L623 _public enumerator_ `BatchComplete` — The element list was modified as part of a batch or bulk operation. The ElementHandle argument will be unset. @note A batch operation will emit internal (bIsWithinBatchOperation=true) Added, Removed, Modified and Cleared updates during the batch, so if you respond to those internal updates you may choose to ignore this one. Otherwise you should treat it the same as Modified.

#### class `TTypedElementList::FLegacySyncScopedBatch`  
`class FLegacySyncScopedBatch`  
_L652-670_
- desc: Helper to batch immediate sync notifications for legacy code. Does nothing if no legacy sync has been created for the given instance.
- L655 _public prototype_ `explicit FLegacySyncScopedBatch(const TTypedElementList& InElementList, const bool InNotify = true);`
- L656 _public prototype_ `~FLegacySyncScopedBatch();`
- L658 _public prototype_ `FLegacySyncScopedBatch(const FLegacySyncScopedBatch&) = delete;`
- L659 _public prototype_ `FLegacySyncScopedBatch& operator=(const FLegacySyncScopedBatch&) = delete;`
- L661 _public prototype_ `FLegacySyncScopedBatch(FLegacySyncScopedBatch&&) = delete;`
- L662 _public prototype_ `FLegacySyncScopedBatch& operator=(FLegacySyncScopedBatch&&) = delete;`
- L664 _public prototype_ `bool IsDirty() const;`
- L665 _public prototype_ `void ForceDirty();`
- L668 _private member_ `FLegacySync* ElementListLegacySync = nullptr;`
- L669 _private member_ `bool bNotify = true;`

#### enum `TTypedElementList::EChangeType`  
`enum class EChangeType : uint8`  
_L700-719_
- L706 _public enumerator_ `Added` — An element was added to the element list. The ElementHandle argument will be set to the element that was added.
- L712 _public enumerator_ `Removed` — An element was removed from the element list. The ElementHandle argument will be set to the element that was removed.
- L718 _public enumerator_ `Cleared` — The element list was cleared. The ElementHandle argument will be unset.

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace TypedElementList_Private`
- L34 _prototype_ `void GetElementImpl(const UTypedElementRegistry* InRegistry, const FTypedElementHandle& InElementHandle, const TSubclassOf<UInterface>& InBaseInterfaceType, FTypedElement& OutElement);` (scope `TypedElementList_Private`)
- L36 _prototype_ `void GetElementImpl(const UTypedElementRegistry* InRegistry, const FScriptTypedElementHandle& InElementHandle, const TSubclassOf<UInterface>& InBaseInterfaceType, FTypedElement& OutElement);` (scope `TypedElementList_Private`)
- L39 _function_ `template <typename BaseInterfaceType, class HandleType> inline void GetElement(const UTypedElementRegistry* InRegistry, const HandleType& InElementHandle, TTypedElement<BaseInterfaceType>& OutElement)` (scope `TypedElementList_Private`)
- L46 _function_ `template <typename BaseInterfaceType, class HandleType> inline TTypedElement<BaseInterfaceType> GetElement(const UTypedElementRegistry* InRegistry, const HandleType& InElementHandle)` (scope `TypedElementList_Private`)
- L265 _function_ `` (scope `TTypedElementList::GetElementHandles`)
- L432 _function_ `` (scope `TTypedElementList::Append`)
- L523 _function_ `` (scope `TTypedElementList::RemoveAll`)
- L541 _delegate_ `DECLARE_EVENT_OneParam(TTypedElementList, FOnPreChange, const TTypedElementList& );` — Access the delegate that is invoked whenever this element list is potentially about to change. @note This may be called even if no actual change happens, so may be called multiple times without a corresponding OnChanged notification.
- L551 _delegate_ `DECLARE_EVENT_OneParam(TTypedElementList, FOnChanged, const TTypedElementList& );` — Access the delegate that is invoked whenever this element list has been changed. @note This is called automatically at the end of each frame, but can also be manually invoked by NotifyPendingChanges.
- L630 _delegate_ `DECLARE_EVENT_FourParams(FLegacySync, FOnSyncEvent, const TTypedElementList& , ESyncType , const HandleType& , bool );`
- L776 _namespace_ `namespace UE`
- L776 _namespace_ `namespace TypedElementFramework` (scope `UE`)
- L782 _prototype_ `FTypedElementListPtr ConvertToNativeTypedElementList(const FScriptTypedElementListConstPtr& ScriptList);` (scope `UE::TypedElementFramework`) — Functions to convert a script list to a native one @note Only copies elements; does not copy any bindings!
- L788 _prototype_ `FScriptTypedElementListPtr ConvertToScriptTypedElementList(const FTypedElementListConstPtr& NativeList);` (scope `UE::TypedElementFramework`) — Functions to convert a script list to a native one @note Only copies elements; does not copy any bindings!

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementListFwd.h` (Public)


#### Free symbols / members of external scopes

- L14 _typedef_ `using FTypedElementList = TTypedElementList<FTypedElementHandle>;` — Native typed element list.
- L16 _typedef_ `using FTypedElementListPtr = TSharedPtr<FTypedElementList>;`
- L17 _typedef_ `using FTypedElementListRef = TSharedRef<FTypedElementList>;`
- L19 _typedef_ `using FTypedElementListConstPtr = TSharedPtr<const FTypedElementList>;`
- L20 _typedef_ `using FTypedElementListConstRef = TSharedRef<const FTypedElementList>;`
- L26 _typedef_ `using FScriptTypedElementList = TTypedElementList<FScriptTypedElementHandle>;` — Script typed element list. It should only be use for the script exposure apis since the script handles does have a performance overhead over the normal handles.
- L28 _typedef_ `using FScriptTypedElementListPtr = TSharedPtr<FScriptTypedElementList>;`
- L29 _typedef_ `using FScriptTypedElementListRef = TSharedRef<FScriptTypedElementList>;`
- L31 _typedef_ `using FScriptTypedElementListConstPtr = TSharedPtr<const FScriptTypedElementList>;`
- L32 _typedef_ `using FScriptTypedElementListConstRef = TSharedRef<const FScriptTypedElementList>;`

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementListProxy.h` (Public)


#### struct `FScriptTypedElementListProxy`  
`struct FScriptTypedElementListProxy`  
_L17-46_
- reflection: `USTRUCT(BlueprintType, DisplayName="Typed Element List", meta=(ScriptName="TypedElementList"))`
- desc: A list of script element handles (proxy to a FScriptTypedElementList instance). Provides high-level access to groups of elements, including accessing elements that implement specific interfaces. Note: the script list proxy use should be avoided when not using it for the script exposure apis. The weak model for the handles come with an additional cost to the runtime performance and the memory usage.
- L22 _public prototype_ `FScriptTypedElementListProxy() = default;`
- L24 _public function_ `FScriptTypedElementListProxy(FScriptTypedElementListRef InElementList) : ElementList(MoveTemp(InElementList))`
- L29 _public function_ `FScriptTypedElementListProxy(FScriptTypedElementListConstRef InElementList) : ElementList(ConstCastSharedRef<FScriptTypedElementList>(InElementList))`
- L34 _public function_ `FScriptTypedElementListPtr GetElementList()`
- L39 _public function_ `FScriptTypedElementListConstPtr GetElementList() const`
- L45 _private member_ `FScriptTypedElementListPtr ElementList;`

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementMetaData.h` (Public)


#### class `UE::Editor::DataStorage::FMetaDataEntryView`  
`class FMetaDataEntryView final`  
_L29-50_
- desc: Short lived view of single entry in the meta data container.
- L32 _public prototype_ `FMetaDataEntryView();`
- L33 _public prototype_ `explicit FMetaDataEntryView(const MetaDataType& MetaData);`
- L34 _public prototype_ `explicit FMetaDataEntryView(const FString& MetaDataString);`
- L37 _public prototype_ `template<typename T> explicit FMetaDataEntryView(T&& MetaDataValue);` — Explicit constructor. The provided type must match exactly to one of the available stored types.
- L40 _public prototype_ `bool IsSet() const;` — Returns true if set to a value, otherwise false.
- L43 _public prototype_ `template<typename T> bool IsType() const;` — Checks if the stored value matches the requested type.
- L46 _public prototype_ `template<typename T> const T* TryGetExact() const;` — Returns the value if the requested type matches exactly with the stored type, otherwise returns a nullptr.
- L49 _private member_ `MetaDataTypeView DataView;`

#### class `UE::Editor::DataStorage::FMetaDataBase`  
`class FMetaDataBase`  
_L55-77_
- desc: Base class to store meta data for use within the Typed Elements Data Storage.
- L59 _public prototype_ `template<typename T> bool AddImmutableData(FName Name, T&& Value);`
- L61 _public prototype_ `template<typename T> void AddOrSetMutableData(FName Name, T&& Value);`
- L63 _public prototype_ `virtual FMetaDataEntryView Find(FName Name) const;`
- L65 _public prototype_ `virtual void Shrink();`
- L67 _public prototype_ `virtual bool IsEmpty() const;`
- L70 _protected prototype_ `FMetaDataBase() = default;`
- L71 _protected prototype_ `virtual ~FMetaDataBase() = default;`
- L74 _protected member_ `TMap<FName, MetaDataType> ImmutableData;` — Data that can be added once but can't be changed afterwards. Values here always take priority over other values.
- L76 _protected member_ `TMap<FName, MetaDataType> MutableData;` — Data that can be added and can have their value updated afterwards.

#### class `UE::Editor::DataStorage::FMetaData`  
`class FMetaData final : public FMetaDataBase`  
_L80-80_
- inherits: `FMetaDataBase`
- desc: General storage for meta data for the Typed Elements Data Storage.

#### class `UE::Editor::DataStorage::FColumnMetaData`  
`class FColumnMetaData final : public FMetaDataBase`  
_L85-108_
- inherits: `FMetaDataBase`
- desc: Meta data that's specifically associated with a single column.
- L94 _public prototype_ `FColumnMetaData() = default;`
- L95 _public prototype_ `FColumnMetaData(const UScriptStruct* InColumnType, EFlags InFlags);`
- L97 _public prototype_ `FMetaDataEntryView Find(FName Name) const override;`
- L99 _public prototype_ `const UScriptStruct* GetColumnType() const;`
- L101 _public prototype_ `bool IsEmpty() const override;`
- L105 _private member_ `const UScriptStruct* ColumnType{ nullptr };` — If set, properties on the column will also be included if a value isn't found in the (im)mutable data map.
- L107 _private member_ `EFlags Flags = EFlags::None;` — Flags indicating the behavior of the column

#### enum `UE::Editor::DataStorage::FColumnMetaData::EFlags`  
`enum class EFlags`  
_L88-92_
- L90 _public enumerator_ `None = 0`
- L91 _public enumerator_ `IsMutable = 1 << 0`

#### class `UE::Editor::DataStorage::FMetaDataView`  
`class FMetaDataView`  
_L113-134_
- desc: Short lived view of a meta data container.
- L116 _public prototype_ `virtual ~FMetaDataView() = default;`
- L118 _public prototype_ `virtual FMetaDataEntryView FindGeneric(FName AttributeName) const;`
- L119 _public prototype_ `virtual FMetaDataEntryView FindForColumn( TWeakObjectPtr<const UScriptStruct> Column, FName AttributeName) const;`
- L122 _public prototype_ `template<typename Column> FMetaDataEntryView FindForColumn(FName AttributeName) const;`
- L125 _public prototype_ `FMetaDataEntryView FindForColumnOrGeneric( TWeakObjectPtr<const UScriptStruct> Column, FName AttributeName) const;` — First tries FindForColumn and if unsuccessful, calls FindGeneric.
- L128 _public prototype_ `template<typename Column> FMetaDataEntryView FindForColumnOrGeneric(FName AttributeName) const;`
- L130 _public prototype_ `FMetaDataEntryView FindForColumnsOrGeneric( const TConstArrayView<TWeakObjectPtr<const UScriptStruct>> Columns, FName AttributeName) const;` — Tries FindForColumn for each given column in order until successful, otherwise calls FindGeneric.
- L133 _public prototype_ `template<typename... Columns> FMetaDataEntryView FindForColumnsOrGeneric(FName AttributeName) const;`

#### class `UE::Editor::DataStorage::FQueryMetaDataView`  
`class FQueryMetaDataView final : public FMetaDataView`  
_L139-152_
- inherits: `FMetaDataView`
- desc: Short lived view of a meta data container that wraps a query.
- L142 _public prototype_ `~FQueryMetaDataView() override = default;`
- L144 _public prototype_ `explicit FQueryMetaDataView(const FQueryDescription& InQuery);`
- L146 _public prototype_ `FMetaDataEntryView FindGeneric(FName AttributeName) const override;`
- L147 _public prototype_ `FMetaDataEntryView FindForColumn( TWeakObjectPtr<const UScriptStruct> Column, FName AttributeName) const override;`
- L151 _private member_ `const FQueryDescription& Query;`

#### class `UE::Editor::DataStorage::FColumnsMetaDataView`  
`class FColumnsMetaDataView final : public FMetaDataView`  
_L157-170_
- inherits: `FMetaDataView`
- desc: Short lived view of a meta data container that wraps a list of columns.
- L160 _public prototype_ `~FColumnsMetaDataView() override = default;`
- L162 _public prototype_ `explicit FColumnsMetaDataView(TConstArrayView<TWeakObjectPtr<const UScriptStruct>> InColumns);`
- L163 _public prototype_ `explicit FColumnsMetaDataView(TConstArrayView<TSharedPtr<FColumnMetaData>> InColumnsMetaData);`
- L164 _public prototype_ `FMetaDataEntryView FindForColumn( TWeakObjectPtr<const UScriptStruct> Column, FName AttributeName) const override;`
- L168 _private member_ `TConstArrayView<TWeakObjectPtr<const UScriptStruct>> Columns;`
- L169 _private member_ `TConstArrayView<TSharedPtr<FColumnMetaData>> ColumnsMetaData;`

#### class `UE::Editor::DataStorage::FGenericMetaDataView`  
`class FGenericMetaDataView final : public FMetaDataView`  
_L175-185_
- inherits: `FMetaDataView`
- desc: Short lived view of a meta data container that wraps generic meta data.
- L178 _public prototype_ `~FGenericMetaDataView() override = default;`
- L180 _public prototype_ `explicit FGenericMetaDataView(const FMetaData& InMetaData);`
- L181 _public prototype_ `FMetaDataEntryView FindGeneric(FName AttributeName) const override;`
- L184 _private member_ `const FMetaData& MetaData;`

#### class `UE::Editor::DataStorage::FForwardingMetaDataView`  
`class FForwardingMetaDataView final : public FMetaDataView`  
_L190-202_
- inherits: `FMetaDataView`
- desc: Short lived view of a meta data container that wraps around another meta data view so they can be chained.
- L193 _public prototype_ `~FForwardingMetaDataView() override = default;`
- L195 _public prototype_ `explicit FForwardingMetaDataView(const FMetaDataView& InView);`
- L196 _public prototype_ `FMetaDataEntryView FindGeneric(FName AttributeName) const override;`
- L197 _public prototype_ `FMetaDataEntryView FindForColumn( TWeakObjectPtr<const UScriptStruct> Column, FName AttributeName) const override;`
- L201 _private member_ `const FMetaDataView& View;`

#### class `UE::Editor::DataStorage::FComboMetaDataView`  
`template<typename... ViewTypes> class FComboMetaDataView final : public FMetaDataView`  
_L208-221_
- inherits: `FMetaDataView`
- desc: Short lived view of a meta data container.
- L211 _public prototype_ `FComboMetaDataView(const ViewTypes&... InViews);`
- L212 _public prototype_ `FComboMetaDataView(ViewTypes&&... InViews);`
- L215 _public prototype_ `template<typename NextViewType> FComboMetaDataView<ViewTypes..., NextViewType> Next(NextViewType&& NextView);`
- L217 _public prototype_ `FMetaDataEntryView FindGeneric(FName AttributeName) const override;`
- L218 _public prototype_ `FMetaDataEntryView FindForColumn(TWeakObjectPtr<const UScriptStruct> Column, FName AttributeName) const;`
- L220 _public member_ `TTuple<ViewTypes...> Views;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L20 _variable_ `inline static const FName IsEditableName("IsE` (scope `UE::Editor::DataStorage`)
- L21 _variable_ `inline static const FName IsConstName("IsC` (scope `UE::Editor::DataStorage`)
- L23 _typedef_ `using MetaDataType = TVariant<bool, uint64, int64, double, FString>;` (scope `UE::Editor::DataStorage`)
- L24 _typedef_ `using MetaDataTypeView = TVariant<FEmptyVariantState, bool, uint64, int64, double, const FString*>;` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementMetaData.inl` (Public)


#### Free symbols / members of external scopes

- L3 _namespace_ `namespace UE`
- L3 _namespace_ `namespace Editor` (scope `UE`)
- L3 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L5 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage`)
- L8 _function_ `template<typename TContainer, typename T> void AddDataToContainer(TContainer& Container, FName Name, T Value)` (scope `UE::Editor::DataStorage::Private`)
- L10 _typedef_ `using BaseType = std::remove_const_t<std::remove_reference_t<T>>;` (scope `UE::Editor::DataStorage::Private::AddDataToContainer`)
- L46 _function_ `ENUM_CLASS_FLAGS(FColumnMetaData::EFlags) template<typename T> bool FMetaDataBase::AddImmutableData(FName Name, T&& Value)` (scope `UE::Editor::DataStorage`)
- L63 _function_ `template<typename T> void FMetaDataBase::AddOrSetMutableData(FName Name, T&& Value)` (scope `UE::Editor::DataStorage::FMetaDataBase`)
- L75 _function_ `template<typename T> FMetaDataEntryView::FMetaDataEntryView(T&& MetaDataValue) : DataView(TInPlaceType<T>(), Forward<T>(MetaDataValue))` (scope `UE::Editor::DataStorage::FMetaDataEntryView`)
- L80 _function_ `template<typename T> bool FMetaDataEntryView::IsType() const` (scope `UE::Editor::DataStorage::FMetaDataEntryView`)
- L86 _function_ `template<typename T> const T* FMetaDataEntryView::TryGetExact() const` (scope `UE::Editor::DataStorage::FMetaDataEntryView`)
- L102 _function_ `template<typename Column> FMetaDataEntryView FMetaDataView::FindForColumn(FName AttributeName) const` (scope `UE::Editor::DataStorage::FMetaDataView`)
- L108 _function_ `template<typename Column> FMetaDataEntryView FMetaDataView::FindForColumnOrGeneric(FName AttributeName) const` (scope `UE::Editor::DataStorage::FMetaDataView`)
- L114 _function_ `template<typename... Columns> FMetaDataEntryView FMetaDataView::FindForColumnsOrGeneric(FName AttributeName) const` (scope `UE::Editor::DataStorage::FMetaDataView`)
- L127 _function_ `template<typename... ViewTypes> FComboMetaDataView<ViewTypes...>::FComboMetaDataView(const ViewTypes&... InViews) : Views(InViews...)` (scope `UE::Editor::DataStorage::FComboMetaDataView`)
- L133 _function_ `template<typename... ViewTypes> FComboMetaDataView<ViewTypes...>::FComboMetaDataView(ViewTypes&&... InViews) : Views(Forward<ViewTypes>(InViews)...)` (scope `UE::Editor::DataStorage::FComboMetaDataView`)
- L140 _function_ `template<typename... ViewTypes> template<typename NextViewType> FComboMetaDataView<ViewTypes..., NextViewType> FComboMetaDataView<ViewTypes...>::Next(NextViewType&& NextView)` (scope `UE::Editor::DataStorage::FComboMetaDataView`)
- L143 _function_ `` (scope `UE::Editor::DataStorage::FComboMetaDataView::Next`)
- L149 _function_ `template<typename... ViewTypes> FMetaDataEntryView FComboMetaDataView<ViewTypes...>::FindGeneric(FName AttributeName) const` (scope `UE::Editor::DataStorage::FComboMetaDataView`)
- L152 _function_ `` (scope `UE::Editor::DataStorage::FComboMetaDataView::FindGeneric`)
- L155 _function_ `` (scope `UE::Editor::DataStorage::FComboMetaDataView::FindGeneric::__anon3823744f0202`)
- L165 _function_ `template<typename... ViewTypes> FMetaDataEntryView FComboMetaDataView<ViewTypes...>::FindForColumn(TWeakObjectPtr<const UScriptStruct> Column, FName AttributeName) const` (scope `UE::Editor::DataStorage::FComboMetaDataView`)
- L168 _function_ `` (scope `UE::Editor::DataStorage::FComboMetaDataView::FindForColumn`)
- L171 _function_ `` (scope `UE::Editor::DataStorage::FComboMetaDataView::FindForColumn::__anon3823744f0402`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementOwnerStore.h` (Public)


#### struct `TTypedElementOwnerScopedAccessImpl`  
`template <typename ElementOwnerType> struct TTypedElementOwnerScopedAccessImpl`  
_L16-87_
- desc: Type to keep a lock on the TTypedElementOwnerStore for the duration of time that a TTypedElementOwner is being externally referenced. This avoids invalid memory access if the map is reallocated.
- L19 _public function_ `explicit TTypedElementOwnerScopedAccessImpl(FTransactionallySafeCriticalSection* InSynchObject) : SynchObject(InSynchObject)`
- L26 _public function_ `~TTypedElementOwnerScopedAccessImpl()`
- L34 _public prototype_ `TTypedElementOwnerScopedAccessImpl(const TTypedElementOwnerScopedAccessImpl&) = delete;`
- L35 _public prototype_ `TTypedElementOwnerScopedAccessImpl& operator=(const TTypedElementOwnerScopedAccessImpl&) = delete;`
- L37 _public function_ `TTypedElementOwnerScopedAccessImpl(TTypedElementOwnerScopedAccessImpl&& InOther) : SynchObject(InOther.SynchObject) , ElementOwner(InOther.ElementOwner)`
- L45 _public prototype_ `TTypedElementOwnerScopedAccessImpl& operator=(TTypedElementOwnerScopedAccessImpl&&) = delete;`
- L47 _public function_ `inline explicit operator bool() const`
- L52 _public function_ `inline bool IsSet() const`
- L57 _public function_ `inline ElementOwnerType& operator*() const`
- L63 _public function_ `inline ElementOwnerType* operator->() const`
- L69 _public function_ `void Private_SetElementOwner(ElementOwnerType* InElementOwner)`
- L85 _private member_ `FTransactionallySafeCriticalSection* SynchObject = nullptr;`
- L86 _private member_ `ElementOwnerType* ElementOwner = nullptr;`

#### struct `TTypedElementOwnerStore`  
`template <typename ElementDataType, typename KeyDataType = const void*> struct TTypedElementOwnerStore`  
_L111-219_
- desc: A store of element owners tied to their corresponding owner instance. This can be used to track element owners for an instance without having to add new data to the type itself.
- L116 _public prototype_ `TTypedElementOwnerStore() = default;`
- L118 _public function_ `~TTypedElementOwnerStore()`
- L128 _public function_ `TTypedElementOwnerScopedAccess<ElementDataType> RegisterElementOwner(const KeyDataType& InKey, TTypedElementOwner<ElementDataType>&& InElementOwner)` — Register the given element owner, transferring ownership of the owner instance to this store. @note This will lock the store for writes until the scoped access struct is no longer being used. @note This must be paired with a call to UnregisterElementOwner.
- L141 _public function_ `TTypedElementOwner<ElementDataType> UnregisterElementOwner(const KeyDataType& InKey)` — Unregister the given element owner, transferring ownership of the owner instance back to the caller. @note The returned owner may be unset if the key was not registered.
- L154 _public function_ `void UnregisterElementOwners(TFunctionRef<bool(const TTypedElementOwner<ElementDataType>&)> InShouldUnregisterElement, TFunctionRef<void(TTypedElementOwner<ElementDataType>&&)> InOnUnregisterElement)` — Unregister any given element owners that match the given predicate, transferring ownership of the owner instance to the given callback.
- L171 _public function_ `TTypedElementOwnerScopedAccess<ElementDataType> FindOrRegisterElementOwner(const KeyDataType& InKey, TFunctionRef<TTypedElementOwner<ElementDataType>()> InCreateElement)` — Find the given element owner, or call the register callback to attempt to create one if none is found. @note This must be paired with a call to UnregisterElementOwner if a new element owner is created.
- L189 _public function_ `TTypedElementOwnerScopedAccess<ElementDataType> FindElementOwner(const KeyDataType& InKey) const` — Provide const access to the given element owner. @note This will lock the store for writes until the scoped access struct is no longer being used. The returned struct may be unset if the key was not registered.
- L200 _public function_ `TTypedElementOwnerScopedMutableAccess<ElementDataType> FindMutableElementOwner(const KeyDataType& InKey)` — Provide mutable access to the given element owner. @note This will lock the store for writes until the scoped access struct is no longer being used. The returned struct may be unset if the key was not registered.
- L210 _public function_ `bool ContainsElementOwner(const KeyDataType& InKey) const` — Test to see whether the store has an entry for the given element owner.
- L217 _private member_ `TMap<KeyDataType, TTypedElementOwner<ElementDataType>> ElementOwnerMap;`
- L218 _private member_ `mutable FTransactionallySafeCriticalSection ElementOwnerMapCS;`

#### Free symbols / members of external scopes

- L90 _typedef_ `template <typename ElementDataType> using TTypedElementOwnerScopedAccess = TTypedElementOwnerScopedAccessImpl<const TTypedElementOwner<ElementDataType>>;`
- L93 _typedef_ `template <typename ElementDataType> using TTypedElementOwnerScopedMutableAccess = TTypedElementOwnerScopedAccessImpl<TTypedElementOwner<ElementDataType>>;`
- L96 _function_ `template <typename KeyDataType> inline FString GetTypedElementOwnerStoreKeyDebugString(const KeyDataType& InKey)`
- L101 _function_ `inline FString GetTypedElementOwnerStoreKeyDebugString(const UObject* InKey)`

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryBuilder.h` (Public)


#### enum `UE::Editor::DataStorage::Queries::EOptional`  
`enum class EOptional`  
_L114-118_
- L116 _public enumerator_ `No`
- L117 _public enumerator_ `Yes`

#### class `UE::Editor::DataStorage::Queries::FDependency`  
`class FDependency final`  
_L120-145_
- L128 _public prototype_ `template<typename... TargetTypes> FDependency& ReadOnly();`
- L129 _public prototype_ `FDependency& ReadOnly(const UClass* Target);`
- L130 _public prototype_ `FDependency& ReadOnly(TConstArrayView<const UClass*> Targets);`
- L132 _public prototype_ `template<typename... TargetTypes> FDependency& ReadWrite();`
- L133 _public prototype_ `FDependency& ReadWrite(const UClass* Target);`
- L134 _public prototype_ `FDependency& ReadWrite(TConstArrayView<const UClass*> Targets);`
- L136 _public prototype_ `FDependency& SubQuery(QueryHandle Handle);`
- L137 _public prototype_ `FDependency& SubQuery(TConstArrayView<QueryHandle> Handles);`
- L139 _public prototype_ `FQueryDescription&& Compile();`
- L142 _private prototype_ `explicit FDependency(FQueryDescription* Query);`
- L144 _private member_ `FQueryDescription* Query;`

#### struct `UE::Editor::DataStorage::Queries::FQueryExpression`  
`struct FQueryExpression`  
_L176-182_
- desc: Composite query expression holding both column conditions (evaluated at archetype selection time via SetArchetypeMatchOverride) and relation predicates (evaluated per-entity after chunk selection). Column and relation conditions are AND-composed with each other.
- L179 _public member_ `TOptional<FConditions> ColumnConditions;` — Column conditions. Evaluated at archetype level. Absent when only relation predicates are combined.
- L181 _public member_ `TArray<FQueryDescription::FRelationPredicate, TInlineAllocator<2>> RelationAtoms;` — Relation predicates AND-composed with each other and with ColumnConditions.

#### class `UE::Editor::DataStorage::Queries::FSimpleQuery`  
`class FSimpleQuery final`  
_L197-330_
- L203 _public prototype_ `FDependency DependsOn();`
- L204 _public prototype_ `FQueryDescription&& Compile();`
- L207 _public prototype_ `template<TColumnType... TargetTypes> FSimpleQuery& All();`
- L208 _public prototype_ `FSimpleQuery& All(const UScriptStruct* Target);`
- L209 _public prototype_ `FSimpleQuery& All(TConstArrayView<const UScriptStruct*> Targets);`
- L212 _public prototype_ `template<TColumnType... TargetTypes> FSimpleQuery& Any();`
- L213 _public prototype_ `FSimpleQuery& Any(const UScriptStruct* Target);`
- L214 _public prototype_ `FSimpleQuery& Any(TConstArrayView<const UScriptStruct*> Targets);`
- L217 _public prototype_ `FSimpleQuery& Any(const FDynamicColumnDescription& Description);` — Dynamic Column Support
- L219 _public prototype_ `template<TDynamicColumnTemplate T> FSimpleQuery& Any(const FName&);`
- L223 _public prototype_ `template<TValueTagType> FSimpleQuery& Any(const FName&) = delete;` — ValueTags not yet supported for Any
- L225 _public prototype_ `template<TValueTagType> FSimpleQuery& Any(const FName&, const FName&) = delete;`
- L228 _public prototype_ `template<TColumnType... TargetTypes> FSimpleQuery& None();`
- L230 _public prototype_ `FSimpleQuery& None(const UScriptStruct* Target);`
- L231 _public prototype_ `FSimpleQuery& None(TConstArrayView<const UScriptStruct*> Targets);`
- L235 _public prototype_ `template<TValueTagType> FSimpleQuery& None(const FName& Tag) = delete;` — ValueTags not yet supported for None
- L237 _public prototype_ `template<TValueTagType> FSimpleQuery& None(const FName& Tag, const FName& Value) = delete;`
- L240 _public prototype_ `FSimpleQuery& None(const FDynamicColumnDescription& Description);` — Dynamic Column Support
- L242 _public prototype_ `template<TDynamicColumnTemplate T> FSimpleQuery& None(const FName&);`
- L247 _public prototype_ `FSimpleQuery& All(const FValueTag& Tag);` — Adds a filter to the query which must match a given ValueTag.  The value of the ValueTag will not be checked.
- L250 _public prototype_ `FSimpleQuery& All(const FValueTag& Tag, const FName& Value);` — Adds a filter to the query which must match a given ValueTag.  The value of the ValueTag must also match. Note: The query can only match a single value.  Multiple value queries are not supported at this time.
- L252 _public prototype_ `FSimpleQuery& All(const UEnum& Enum);`
- L253 _public prototype_ `FSimpleQuery& All(const UEnum& Enum, int64 Value);`
- L256 _public prototype_ `FSimpleQuery& All(const FDynamicColumnDescription& Description);` — Dynamic Column support
- L258 _public prototype_ `template<TDynamicColumnTemplate T> FSimpleQuery& All(const FName&);`
- L262 _public prototype_ `template<TValueTagType> FSimpleQuery& All(const FName& Tag);` — Adds a filter to the query which must match a given ValueTag.  The value of the DynamicTag will not be checked.
- L266 _public prototype_ `template<TValueTagType> FSimpleQuery& All(const FName& Tag, const FName& Value);` — Adds a filter to the query which must match a given ValueTag.  The value of the DynamicTag must also match. Note: The query can only match a single value.  Multiple value queries are not supported at this time.
- L269 _public prototype_ `template<TEnumType EnumT> FSimpleQuery& All();`
- L272 _public prototype_ `template<TEnumType EnumT> FSimpleQuery& All(EnumT EnumValue);`
- L275 _public prototype_ `template<auto Value, TEnumType EnumT = decltype(Value)> FSimpleQuery& All();`
- L285 _public prototype_ `FSimpleQuery& IsSubjectOf(RelationTypeHandle RelationType);` — Filter to rows that are subjects in relations of the given type. E.g., IsSubjectOf(SubclassOfType) finds all rows that inherit from something.
- L291 _public prototype_ `FSimpleQuery& IsSubjectOf(RelationTypeHandle RelationType, RowHandle Object);` — Filter to rows that are subjects in relations of the given type where the object is the specified row. E.g., IsSubjectOf(SubclassOfType, UObject) finds direct subclasses of UObject.
- L297 _public prototype_ `FSimpleQuery& IsObjectOf(RelationTypeHandle RelationType);` — Filter to rows that are objects in relations of the given type. E.g., IsObjectOf(SubclassOfType) finds all rows that have something inheriting from them.
- L303 _public prototype_ `FSimpleQuery& IsObjectOf(RelationTypeHandle RelationType, RowHandle Subject);` — Filter to rows that are objects in relations of the given type where the subject is the specified row. E.g., IsObjectOf(SubclassOfType, UDerivedClass) finds UDerivedClass's parent.
- L316 _public prototype_ `FSimpleQuery& IsDescendantOf(RelationTypeHandle RelationType, RowHandle Ancestor, bool bIncludeSelf = false);` — Filter to rows that are descendants of the specified ancestor in the given hierarchical relation. Uses interval encoding for O(1) evaluation per row. @param RelationType Must be a hierarchical relation type (HierarchyMode != EHierarchyMode::Disabled) @param Ancestor The ancestor row to test against @param bIncludeSelf If true, the ancestor itself will also match
- L324 _public prototype_ `FSimpleQuery& IsAncestorOf(RelationTypeHandle RelationType, RowHandle Descendant, bool bIncludeSelf = false);` — Filter to rows that are ancestors of the specified descendant in the given hierarchical relation. @param RelationType Must be a hierarchical relation type (HierarchyMode != EHierarchyMode::Disabled) @param Descendant The descendant row to test against @param bIncludeSelf If true, the descendant itself will also match
- L327 _private prototype_ `explicit FSimpleQuery(FQueryDescription* Query);`
- L329 _private member_ `FQueryDescription* Query;`

#### struct `UE::Editor::DataStorage::Queries::FQueryCallbackType`  
`struct FQueryCallbackType`  
_L332-332_

#### struct `UE::Editor::DataStorage::Queries::FProcessor`  
`struct FProcessor final : public FQueryCallbackType`  
_L334-352_
- inherits: `FQueryCallbackType`
- L336 _public prototype_ `FProcessor(EQueryTickPhase Phase, FName Group);`
- L337 _public prototype_ `FProcessor& SetPhase(EQueryTickPhase NewPhase);`
- L338 _public prototype_ `FProcessor& SetGroup(FName GroupName);`
- L339 _public prototype_ `FProcessor& SetBeforeGroup(FName GroupName);`
- L340 _public prototype_ `FProcessor& SetAfterGroup(FName GroupName);`
- L341 _public prototype_ `FProcessor& SetExecutionMode(EExecutionMode Mode);`
- L342 _public prototype_ `FProcessor& MakeActivatable(FName Name);`
- L343 _public prototype_ `FProcessor& BatchModifications(bool bBatch);`
- L345 _public member_ `EQueryTickPhase Phase;`
- L346 _public member_ `FName Group;`
- L347 _public member_ `FName BeforeGroup;`
- L348 _public member_ `FName AfterGroup;`
- L349 _public member_ `FName ActivationName;`
- L350 _public member_ `EExecutionMode ExecutionMode = EExecutionMode::Default;`
- L351 _public member_ `bool bBatchModifications = false;`

#### struct `UE::Editor::DataStorage::Queries::FObserver`  
`struct FObserver final : public FQueryCallbackType`  
_L354-380_
- inherits: `FQueryCallbackType`
- L362 _public prototype_ `FObserver(EEvent MonitorForEvent, const UScriptStruct* MonitoredColumn);`
- L365 _public prototype_ `template<TColumnType ColumnType> static FObserver OnAdd();`
- L367 _public prototype_ `template<TColumnType ColumnType> static FObserver OnRemove();`
- L369 _public prototype_ `FObserver& SetEvent(EEvent MonitorForEvent);`
- L370 _public prototype_ `FObserver& SetMonitoredColumn(const UScriptStruct* MonitoredColumn);`
- L372 _public prototype_ `template<TColumnType ColumnType> FObserver& SetMonitoredColumn();`
- L373 _public prototype_ `FObserver& SetExecutionMode(EExecutionMode Mode);`
- L374 _public prototype_ `FObserver& MakeActivatable(FName Name);`
- L376 _public member_ `const UScriptStruct* Monitor;`
- L377 _public member_ `EEvent Event;`
- L378 _public member_ `FName ActivationName;`
- L379 _public member_ `EExecutionMode ExecutionMode = EExecutionMode::Default;`

#### enum `UE::Editor::DataStorage::Queries::FObserver::EEvent`  
`enum class EEvent : uint8`  
_L356-360_
- L358 _public enumerator_ `Add`
- L359 _public enumerator_ `Remove`

#### struct `UE::Editor::DataStorage::Queries::FPhaseAmble`  
`struct FPhaseAmble final : public FQueryCallbackType`  
_L382-400_
- inherits: `FQueryCallbackType`
- L390 _public prototype_ `FPhaseAmble(ELocation InLocation, EQueryTickPhase InPhase);`
- L391 _public prototype_ `FPhaseAmble& SetLocation(ELocation NewLocation);`
- L392 _public prototype_ `FPhaseAmble& SetPhase(EQueryTickPhase NewPhase);`
- L393 _public prototype_ `FPhaseAmble& SetExecutionMode(EExecutionMode Mode);`
- L394 _public prototype_ `FPhaseAmble& MakeActivatable(FName Name);`
- L396 _public member_ `EQueryTickPhase Phase;`
- L397 _public member_ `ELocation Location;`
- L398 _public member_ `FName ActivationName;`
- L399 _public member_ `EExecutionMode ExecutionMode = EExecutionMode::Default;`

#### enum `UE::Editor::DataStorage::Queries::FPhaseAmble::ELocation`  
`enum class ELocation : uint8`  
_L384-388_
- L386 _public enumerator_ `Preamble`
- L387 _public enumerator_ `Postamble`

#### struct `UE::Editor::DataStorage::Queries::FQueryContextForwarder`  
`struct FQueryContextForwarder : public IQueryContext`  
_L404-445_
- inherits: `IQueryContext`
- desc: Because this is a thin wrapper called from within a query callback, it's better to inline fully so all function pre/postambles can be optimized away.
- L406 _public prototype_ `inline FQueryContextForwarder( const FQueryDescription& InDescription, IQueryContext& InParentContext);`
- L409 _public prototype_ `inline ~FQueryContextForwarder() = default;`
- L411 _public prototype_ `inline const void* GetColumn(const UScriptStruct* ColumnType) const override;`
- L412 _public prototype_ `inline void* GetMutableColumn(const UScriptStruct* ColumnType) override;`
- L413 _public prototype_ `inline void GetColumns(TArrayView<char*> RetrievedAddresses, TConstArrayView<TWeakObjectPtr<const UScriptStruct>> ColumnTypes, TConstArrayView<EQueryAccessType> AccessTypes) override;`
- L415 _public prototype_ `inline void GetColumnsUnguarded(int32 TypeCount, char** RetrievedAddresses, const TWeakObjectPtr<const UScriptStruct>* ColumnTypes, const EQueryAccessType* AccessTypes) override;`
- L418 _public prototype_ `inline bool HasColumn(const UScriptStruct* ColumnType) const override;`
- L420 _public prototype_ `inline UObject* GetMutableDependency(const UClass* DependencyClass) override;`
- L421 _public prototype_ `inline const UObject* GetDependency(const UClass* DependencyClass) override;`
- L422 _public prototype_ `inline void GetDependencies(TArrayView<UObject*> RetrievedAddresses, TConstArrayView<TWeakObjectPtr<const UClass>> SubsystemTypes, TConstArrayView<EQueryAccessType> AccessTypes) override;`
- L425 _public prototype_ `inline uint32 GetRowCount() const override;`
- L426 _public prototype_ `inline TConstArrayView<RowHandle> GetRowHandles() const override;`
- L427 _public prototype_ `inline void RemoveRow(RowHandle Row) override;`
- L428 _public prototype_ `inline void RemoveRows(TConstArrayView<RowHandle> Rows) override;`
- L430 _public prototype_ `inline void AddColumns(RowHandle Row, TConstArrayView<const UScriptStruct*> ColumnTypes) override;`
- L431 _public prototype_ `inline void AddColumns(TConstArrayView<RowHandle> Rows, TConstArrayView<const UScriptStruct*> ColumnTypes) override;`
- L432 _public prototype_ `inline void RemoveColumns(RowHandle Row, TConstArrayView<const UScriptStruct*> ColumnTypes) override;`
- L433 _public prototype_ `inline void RemoveColumns(TConstArrayView<RowHandle> Rows, TConstArrayView<const UScriptStruct*> ColumnTypes) override;`
- L435 _public prototype_ `inline void PushCommand(void(* CommandFunction)(void*), void* CommandData) override;`
- L437 _public prototype_ `inline FQueryResult RunQuery(QueryHandle Query) override;`
- L438 _public prototype_ `inline FQueryResult RunSubquery(int32 SubqueryIndex) override;`
- L439 _public prototype_ `inline FQueryResult RunSubquery(int32 SubqueryIndex, SubqueryCallbackRef Callback) override;`
- L440 _public prototype_ `inline FQueryResult RunSubquery(int32 SubqueryIndex, RowHandle Row, SubqueryCallbackRef Callback) override;`
- L443 _public member_ `IQueryContext& ParentContext;`
- L444 _public member_ `const FQueryDescription& Description;`

#### struct `UE::Editor::DataStorage::Queries::FCachedQueryContext`  
`template<typename... Dependencies> struct FCachedQueryContext final : public FQueryContextForwarder`  
_L448-460_
- inherits: `FQueryContextForwarder`
- L450 _public prototype_ `explicit FCachedQueryContext( const FQueryDescription& InDescription, IQueryContext& InParentContext);`
- L454 _public prototype_ `static void Register(FQueryDescription& Query);`
- L457 _public prototype_ `template<typename Dependency> Dependency& GetCachedMutableDependency();`
- L459 _public prototype_ `template<typename Dependency> const Dependency& GetCachedDependency() const;`

#### class `UE::Editor::DataStorage::Queries::FQueryConditionQuery`  
`class FQueryConditionQuery`  
_L462-474_
- L468 _public prototype_ `FDependency DependsOn();`
- L469 _public prototype_ `FQueryDescription&& Compile();`
- L471 _private prototype_ `explicit FQueryConditionQuery(FQueryDescription* Query);`
- L473 _private member_ `FQueryDescription* Query;`

#### class `UE::Editor::DataStorage::Queries::Select`  
`class Select final`  
_L477-541_
- desc: Explicitly not following the naming convention in order to present this as a query that can be read as such.
- L480 _public prototype_ `Select();`
- L484 _public prototype_ `template<typename CallbackType, typename Function> Select(FName Name, const CallbackType& Type, Function&& Callback);` — Select the columns to operate one, giving read - only or read / write access.
- L487 _public prototype_ `template<typename CallbackType, typename Class, typename Function> Select(FName Name, const CallbackType& Type, Class* Instance, Function&& Callback);` — Select the columns to operate one, giving read - only or read / write access.
- L491 _public prototype_ `template<TDataColumnType... TargetTypes> Select& ReadOnly();` — Request read-only access to the listed columns.
- L493 _public prototype_ `Select& ReadOnly(const UScriptStruct* Target);` — Request read-only access to the listed columns.
- L495 _public prototype_ `Select& ReadOnly(TConstArrayView<const UScriptStruct*> Targets);` — Request read-only access to the listed columns.
- L496 _public prototype_ `Select& ReadOnly(const FDynamicColumnDescription& Description);`
- L502 _public prototype_ `template<TDataColumnType... TargetTypes> Select& ReadOnly(EOptional Optional);` — Request read-only access to the listed columns. If optional is true read access will be given if the column is in the table but it will not be used for finding matching tables. Columns bound with optional can not be bound to a query callback argument.
- L507 _public prototype_ `Select& ReadOnly(const UScriptStruct* Target, EOptional Optional);` — Request read-only access to the listed columns. If optional is true read access will be given if the column is in the table but it will not be used for finding matching tables. Columns bound with optional can not be bound to a query callback argument.
- L512 _public prototype_ `Select& ReadOnly(TConstArrayView<const UScriptStruct*> Targets, EOptional Optional);` — Request read-only access to the listed columns. If optional is true read access will be given if the column is in the table but it will not be used for finding matching tables. Columns bound with optional can not be bound to a query callback argument.
- L514 _public prototype_ `template<TDynamicColumnTemplate Target> Select& ReadOnly(const FName& Identifier);`
- L516 _public prototype_ `template<TDynamicColumnTemplate Target> Select& ReadOnly();`
- L519 _public prototype_ `template<TDataColumnType... TargetTypes> Select& ReadWrite();` — Request read and write access to the listed columns.
- L521 _public prototype_ `Select& ReadWrite(const UScriptStruct* Target);` — Request read and write access to the listed columns.
- L523 _public prototype_ `Select& ReadWrite(TConstArrayView<const UScriptStruct*> Targets);` — Request read and write access to the listed columns.
- L524 _public prototype_ `Select& ReadWrite(const FDynamicColumnDescription& Description);`
- L526 _public prototype_ `template<TDynamicColumnTemplate Target> Select& ReadWrite(const FName& Identifier);`
- L528 _public prototype_ `template<TDynamicColumnTemplate Target> Select& ReadWrite();`
- L531 _public prototype_ `FQueryConditionQuery Where(Queries::FConditions Condition);` — Query Condition API
- L532 _public prototype_ `FQueryConditionQuery Where(Queries::FQueryExpression Expression);`
- L534 _public prototype_ `FQueryDescription&& Compile();`
- L535 _public prototype_ `FSimpleQuery Where();`
- L536 _public prototype_ `FDependency DependsOn();`
- L537 _public prototype_ `Select& AccessesHierarchy(const FName& HierarchyName);`
- L540 _private member_ `FQueryDescription Query;`

#### class `UE::Editor::DataStorage::Queries::Count`  
`class Count final`  
_L544-554_
- desc: Explicitly not following the naming convention in order to keep readability consistent. It now reads like a query sentence.
- L547 _public prototype_ `Count();`
- L549 _public prototype_ `FSimpleQuery Where();`
- L550 _public prototype_ `FDependency DependsOn();`
- L553 _private member_ `FQueryDescription Query;`

#### Free symbols / members of external scopes

- L107 _namespace_ `namespace UE`
- L107 _namespace_ `namespace Editor` (scope `UE`)
- L107 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L107 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L109 _prototype_ `const UScriptStruct* Type(FTopLevelAssetPath Name);` (scope `UE::Editor::DataStorage::Queries`)
- L110 _prototype_ `const UScriptStruct* TypeOptional(FTopLevelAssetPath Name);` (scope `UE::Editor::DataStorage::Queries`)
- L111 _prototype_ `const UScriptStruct* operator""_Type(const char* Name, std::size_t NameSize);` (scope `UE::Editor::DataStorage::Queries`)
- L112 _prototype_ `const UScriptStruct* operator""_TypeOptional(const char* Name, std::size_t NameSize);` (scope `UE::Editor::DataStorage::Queries`)
- L151 _prototype_ `FQueryDescription::FRelationPredicate IsSubjectOf(RelationTypeHandle RelationType);` (scope `UE::Editor::DataStorage::Queries`)
- L152 _prototype_ `FQueryDescription::FRelationPredicate IsSubjectOf(RelationTypeHandle RelationType, RowHandle Object);` (scope `UE::Editor::DataStorage::Queries`)
- L153 _prototype_ `FQueryDescription::FRelationPredicate IsObjectOf(RelationTypeHandle RelationType);` (scope `UE::Editor::DataStorage::Queries`)
- L154 _prototype_ `FQueryDescription::FRelationPredicate IsObjectOf(RelationTypeHandle RelationType, RowHandle Subject);` (scope `UE::Editor::DataStorage::Queries`)
- L155 _prototype_ `FQueryDescription::FRelationPredicate IsDescendantOf(RelationTypeHandle RelationType, RowHandle Ancestor, bool bIncludeSelf = false);` (scope `UE::Editor::DataStorage::Queries`)
- L156 _prototype_ `FQueryDescription::FRelationPredicate IsAncestorOf(RelationTypeHandle RelationType, RowHandle Descendant, bool bIncludeSelf = false);` (scope `UE::Editor::DataStorage::Queries`)
- L185 _prototype_ `FQueryExpression operator&&(FColumnBase Lhs, const FQueryDescription::FRelationPredicate& Rhs);` (scope `UE::Editor::DataStorage::Queries`) — ---- Produce FQueryExpression: column atom + relation predicate ----
- L186 _prototype_ `FQueryExpression operator&&(const FQueryDescription::FRelationPredicate& Lhs, FColumnBase Rhs);` (scope `UE::Editor::DataStorage::Queries`)
- L188 _prototype_ `FQueryExpression operator&&(const FConditions& Lhs, const FQueryDescription::FRelationPredicate& Rhs);` (scope `UE::Editor::DataStorage::Queries`) — ---- Produce FQueryExpression: FConditions + relation predicate ----
- L189 _prototype_ `FQueryExpression operator&&(const FQueryDescription::FRelationPredicate& Lhs, const FConditions& Rhs);` (scope `UE::Editor::DataStorage::Queries`)
- L191 _prototype_ `FQueryExpression operator&&(const FQueryDescription::FRelationPredicate& Lhs, const FQueryDescription::FRelationPredicate& Rhs);` (scope `UE::Editor::DataStorage::Queries`) — ---- Produce FQueryExpression: relation predicate + relation predicate ----
- L193 _prototype_ `FQueryExpression operator&&(FQueryExpression Lhs, const FQueryDescription::FRelationPredicate& Rhs);` (scope `UE::Editor::DataStorage::Queries`) — ---- Extend an existing FQueryExpression ----
- L194 _prototype_ `FQueryExpression operator&&(FQueryExpression Lhs, FColumnBase Rhs);` (scope `UE::Editor::DataStorage::Queries`)
- L195 _prototype_ `FQueryExpression operator&&(FQueryExpression Lhs, const FConditions& Rhs);` (scope `UE::Editor::DataStorage::Queries`)
- L557 _prototype_ `template<typename Function> AUTORTFM_INFER DirectQueryCallback CreateDirectQueryCallbackBinding(Function&& Callback);` (scope `UE::Editor::DataStorage::Queries`)
- L559 _prototype_ `template<typename Function> AUTORTFM_INFER SubqueryCallback CreateSubqueryCallbackBinding(Function&& Callback);` (scope `UE::Editor::DataStorage::Queries`)
- L563 _prototype_ `bool MergeQueries(FQueryDescription& Destination, const FQueryDescription& Source, FText* OutErrorMessage = nullptr);` (scope `UE::Editor::DataStorage::Queries`) — Merge the two input queries by copying the source query into the destination query. If the merge is not possible the original data will be preserved and an optional error message can be requested

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryBuilder.inl` (Public)


#### struct `UE::Editor::DataStorage::Queries::Private::FFunctionColumnInfo`  
`template<SourceQueryContext SourceContext, bool ValidateColumns, typename... ColumnTypes> struct FFunctionColumnInfo`  
_L389-452_
- L391 _public member_ `std::tuple<BaseColumnType<ColumnTypes>*...> Columns;`
- L392 _public member_ `static constexpr bool bArePointerColumns = AreAllColumnsPointers<ColumnTypes...>();`
- L395 _public function_ `template<typename Column> bool CheckValidity(const FQueryDescription& Description)`
- L433 _public function_ `FFunctionColumnInfo(const FQueryDescription& Description, SourceContext& Context)`
- L457 _public function_ `FFunctionColumnInfo(const FQueryDescription&, SourceContext&)`
- L458 _public member_ `static constexpr bool bArePointerColumns = false;`

#### struct `UE::Editor::DataStorage::Queries::Private::FFunctionColumnInfo`  
`template<SourceQueryContext SourceContext, bool ValidateColumns> struct FFunctionColumnInfo<SourceContext, ValidateColumns>`  
_L455-459_
- L391 _public member_ `std::tuple<BaseColumnType<ColumnTypes>*...> Columns;`
- L392 _public member_ `static constexpr bool bArePointerColumns = AreAllColumnsPointers<ColumnTypes...>();`
- L395 _public function_ `template<typename Column> bool CheckValidity(const FQueryDescription& Description)`
- L433 _public function_ `FFunctionColumnInfo(const FQueryDescription& Description, SourceContext& Context)`
- L457 _public function_ `FFunctionColumnInfo(const FQueryDescription&, SourceContext&)`
- L458 _public member_ `static constexpr bool bArePointerColumns = false;`

#### struct `UE::Editor::DataStorage::Queries::Private::FContextInfo`  
`template<SourceQueryContext SourceType, typename TargetType> requires IsCompatibleTargetContextType<SourceType, TargetType> struct FContextInfo`  
_L463-471_
- L465 _public typedef_ `using BaseContextType = std::remove_reference_t<TargetType>;`
- L466 _public member_ `BaseContextType ContextWrapper;`
- L468 _public function_ `FContextInfo(const FQueryDescription& Description, SourceType& Context) : ContextWrapper(Description, Context)`
- L476 _public member_ `const SourceType& ContextWrapper;`
- L478 _public function_ `FContextInfo(const FQueryDescription& Description, SourceType& Context) : ContextWrapper(Context)`
- L486 _public member_ `SourceType& ContextWrapper;`

#### struct `UE::Editor::DataStorage::Queries::Private::FContextInfo`  
`template<SourceQueryContext SourceType> struct FContextInfo<SourceType, const SourceType&>`  
_L474-481_
- L465 _public typedef_ `using BaseContextType = std::remove_reference_t<TargetType>;`
- L466 _public member_ `BaseContextType ContextWrapper;`
- L468 _public function_ `FContextInfo(const FQueryDescription& Description, SourceType& Context) : ContextWrapper(Description, Context)`
- L476 _public member_ `const SourceType& ContextWrapper;`
- L478 _public function_ `FContextInfo(const FQueryDescription& Description, SourceType& Context) : ContextWrapper(Context)`
- L486 _public member_ `SourceType& ContextWrapper;`

#### struct `UE::Editor::DataStorage::Queries::Private::FContextInfo`  
`template<SourceQueryContext SourceType> struct FContextInfo<SourceType, SourceType&>`  
_L484-491_
- L465 _public typedef_ `using BaseContextType = std::remove_reference_t<TargetType>;`
- L466 _public member_ `BaseContextType ContextWrapper;`
- L468 _public function_ `FContextInfo(const FQueryDescription& Description, SourceType& Context) : ContextWrapper(Description, Context)`
- L476 _public member_ `const SourceType& ContextWrapper;`
- L478 _public function_ `FContextInfo(const FQueryDescription& Description, SourceType& Context) : ContextWrapper(Context)`
- L486 _public member_ `SourceType& ContextWrapper;`

#### struct `UE::Editor::DataStorage::Queries::Private::FContextRowHandleColumnsFunction`  
`template<SourceQueryContext SourceContext, bool ValidateColumns, typename TargetContext, typename RowHandleType, typename... Args> requires IsCompatibleTargetContextType<SourceContext, TargetContext> struct FContextRowHandleColumnsFunction : public FFunctionColumnInfo<SourceContext, ValidateColumns, Args...> , public FContextInfo<SourceContext, TargetContext>`  
_L495-552_
- inherits: `FFunctionColumnInfo<SourceContext,ValidateColumns,Args...>,FContextInfo<SourceContext,TargetContext>`
- L499 _public typedef_ `using SuperColumn = FFunctionColumnInfo<SourceContext, ValidateColumns, Args...>;`
- L500 _public typedef_ `using SuperContext = FContextInfo<SourceContext, TargetContext>;`
- L502 _public function_ `FContextRowHandleColumnsFunction(const FQueryDescription& Description, SourceContext& Context) : SuperColumn(Description, Context) , SuperContext(Description, Context)`
- L508 _public function_ `template<typename CallerType> AUTORTFM_INFER void Call(SourceContext& Context, const CallerType& Caller)`

#### struct `UE::Editor::DataStorage::Queries::Private::FContextColumnsFunction`  
`template<SourceQueryContext SourceContext, bool ValidateColumns, typename TargetContext, typename... Args> requires IsCompatibleTargetContextType<SourceContext, TargetContext> struct FContextColumnsFunction : public FFunctionColumnInfo<SourceContext, ValidateColumns, Args...> , public FContextInfo<SourceContext, TargetContext>`  
_L556-600_
- inherits: `FFunctionColumnInfo<SourceContext,ValidateColumns,Args...>,FContextInfo<SourceContext,TargetContext>`
- L560 _public typedef_ `using SuperColumn = FFunctionColumnInfo<SourceContext, ValidateColumns, Args...>;`
- L561 _public typedef_ `using SuperContext = FContextInfo<SourceContext, TargetContext>;`
- L563 _public function_ `FContextColumnsFunction(const FQueryDescription& Description, SourceContext& Context) : SuperColumn(Description, Context) , SuperContext(Description, Context)`
- L569 _public function_ `template<typename CallerType> void Call(SourceContext& Context, const CallerType& Caller)`

#### struct `UE::Editor::DataStorage::Queries::Private::FRowHandleColumnsFunction`  
`template<SourceQueryContext SourceContext, bool ValidateColumns, typename RowHandleType, typename... Columns> struct FRowHandleColumnsFunction : public FFunctionColumnInfo<SourceContext, ValidateColumns, Columns...>`  
_L603-648_
- inherits: `FFunctionColumnInfo<SourceContext,ValidateColumns,Columns...>`
- L605 _public typedef_ `using Super = FFunctionColumnInfo<SourceContext, ValidateColumns, Columns...>;`
- L607 _public function_ `FRowHandleColumnsFunction(const FQueryDescription& Description, SourceContext& Context) : Super(Description, Context)`
- L612 _public function_ `template<typename CallerType> void Call(SourceContext& Context, const CallerType& Caller)`

#### struct `UE::Editor::DataStorage::Queries::Private::FColumnsFunction`  
`template<SourceQueryContext SourceContext, bool ValidateColumns, typename... Args> struct FColumnsFunction : public FFunctionColumnInfo<SourceContext, ValidateColumns, Args...>`  
_L651-695_
- inherits: `FFunctionColumnInfo<SourceContext,ValidateColumns,Args...>`
- L653 _public typedef_ `using Super = FFunctionColumnInfo<SourceContext, ValidateColumns, Args...>;`
- L655 _public function_ `FColumnsFunction(const FQueryDescription& Description, SourceContext& Context) : Super(Description, Context)`
- L660 _public function_ `template<typename CallerType> void Call(SourceContext& Context, const CallerType& Caller)`

#### struct `UE::Editor::DataStorage::Queries::Private::FFunctionInfoHelper`  
`template<SourceQueryContext SourceContext, bool ValidateColumns, typename... Args> struct FFunctionInfoHelper`  
_L698-701_
- L700 _public typedef_ `using BaseClass = FColumnsFunction<SourceContext, ValidateColumns, Args...>;`
- L707 _public typedef_ `using BaseClass = FContextColumnsFunction<SourceContext, ValidateColumns, Arg0, Args...>;`
- L714 _public typedef_ `using BaseClass = FRowHandleColumnsFunction<SourceContext, ValidateColumns, Arg0, Args...>;`
- L721 _public typedef_ `using BaseClass = FContextRowHandleColumnsFunction<SourceContext, ValidateColumns, Arg0, Arg1, Args...>;`

#### struct `UE::Editor::DataStorage::Queries::Private::FFunctionInfoHelper`  
`template<SourceQueryContext SourceContext, bool ValidateColumns, typename Arg0, typename... Args> requires IsCompatibleTargetContextType<SourceContext, Arg0> struct FFunctionInfoHelper<SourceContext, ValidateColumns, Arg0, Args...>`  
_L705-708_
- L700 _public typedef_ `using BaseClass = FColumnsFunction<SourceContext, ValidateColumns, Args...>;`
- L707 _public typedef_ `using BaseClass = FContextColumnsFunction<SourceContext, ValidateColumns, Arg0, Args...>;`
- L714 _public typedef_ `using BaseClass = FRowHandleColumnsFunction<SourceContext, ValidateColumns, Arg0, Args...>;`
- L721 _public typedef_ `using BaseClass = FContextRowHandleColumnsFunction<SourceContext, ValidateColumns, Arg0, Arg1, Args...>;`

#### struct `UE::Editor::DataStorage::Queries::Private::FFunctionInfoHelper`  
`template<SourceQueryContext SourceContext, bool ValidateColumns, typename Arg0, typename... Args> requires IsRowHandleType<Arg0> struct FFunctionInfoHelper<SourceContext, ValidateColumns, Arg0, Args...>`  
_L712-715_
- L700 _public typedef_ `using BaseClass = FColumnsFunction<SourceContext, ValidateColumns, Args...>;`
- L707 _public typedef_ `using BaseClass = FContextColumnsFunction<SourceContext, ValidateColumns, Arg0, Args...>;`
- L714 _public typedef_ `using BaseClass = FRowHandleColumnsFunction<SourceContext, ValidateColumns, Arg0, Args...>;`
- L721 _public typedef_ `using BaseClass = FContextRowHandleColumnsFunction<SourceContext, ValidateColumns, Arg0, Arg1, Args...>;`

#### struct `UE::Editor::DataStorage::Queries::Private::FFunctionInfoHelper`  
`template<SourceQueryContext SourceContext, bool ValidateColumns, typename Arg0, typename Arg1, typename... Args> requires IsCompatibleTargetContextType<SourceContext, Arg0> && IsRowHandleType<Arg1> struct FFunctionInfoHelper<SourceContext, ValidateColumns, Arg0, Arg1, Args...>`  
_L719-722_
- L700 _public typedef_ `using BaseClass = FColumnsFunction<SourceContext, ValidateColumns, Args...>;`
- L707 _public typedef_ `using BaseClass = FContextColumnsFunction<SourceContext, ValidateColumns, Arg0, Args...>;`
- L714 _public typedef_ `using BaseClass = FRowHandleColumnsFunction<SourceContext, ValidateColumns, Arg0, Args...>;`
- L721 _public typedef_ `using BaseClass = FContextRowHandleColumnsFunction<SourceContext, ValidateColumns, Arg0, Arg1, Args...>;`

#### struct `UE::Editor::DataStorage::Queries::Private::FFunctionInfo`  
`template<SourceQueryContext SourceContext, bool ValidateColumns, typename... Args> struct FFunctionInfo final : public FFunctionInfoHelper<SourceContext, ValidateColumns, Args...>::BaseClass`  
_L725-732_
- inherits: `FFunctionInfoHelper<SourceContext,ValidateColumns,Args...>::BaseClass`
- L727 _public typedef_ `using Super = typename FFunctionInfoHelper<SourceContext, ValidateColumns, Args...>::BaseClass;`
- L729 _public function_ `FFunctionInfo(const FQueryDescription& Description, SourceContext& Context) : Super(Description, Context)`

#### struct `UE::Editor::DataStorage::Queries::Private::RegisterFunctionArgumentsHelper`  
`template<SourceQueryContext SourceContext, typename... Args> struct RegisterFunctionArgumentsHelper`  
_L860-866_
- L862 _public function_ `void Register(FQueryDescription&, Select& Target)`
- L871 _public function_ `static void Register(FQueryDescription&, Select&)`
- L877 _public function_ `static void Register(FQueryDescription& Query, Select& Target)`

#### struct `UE::Editor::DataStorage::Queries::Private::RegisterFunctionArgumentsHelper`  
`template<SourceQueryContext SourceContext> struct RegisterFunctionArgumentsHelper<SourceContext>`  
_L869-872_
- L862 _public function_ `void Register(FQueryDescription&, Select& Target)`
- L871 _public function_ `static void Register(FQueryDescription&, Select&)`
- L877 _public function_ `static void Register(FQueryDescription& Query, Select& Target)`

#### struct `UE::Editor::DataStorage::Queries::Private::RegisterFunctionArgumentsHelper`  
`template<SourceQueryContext SourceContext, typename Arg0> struct RegisterFunctionArgumentsHelper<SourceContext, Arg0>`  
_L875-889_
- L862 _public function_ `void Register(FQueryDescription&, Select& Target)`
- L871 _public function_ `static void Register(FQueryDescription&, Select&)`
- L877 _public function_ `static void Register(FQueryDescription& Query, Select& Target)`

#### struct `UE::Editor::DataStorage::Queries::Private::RegisterFunctionArgumentsHelper`  
`template<SourceQueryContext SourceContext, typename Arg0, typename Arg1, typename... Args> struct RegisterFunctionArgumentsHelper<SourceContext, Arg0, Arg1, Args...>`  
_L892-914_
- L862 _public function_ `void Register(FQueryDescription&, Select& Target)`
- L871 _public function_ `static void Register(FQueryDescription&, Select&)`
- L877 _public function_ `static void Register(FQueryDescription& Query, Select& Target)`

#### struct `UE::Editor::DataStorage::Queries::Private::IsValidSelectFunctionSignatureImpl2`  
`template<SourceQueryContext SourceContext, typename... Args> struct IsValidSelectFunctionSignatureImpl2`  
_L941-947_
- L943 _public member_ `constexpr static bool HasValidColumnTypes = (IsValidColumnType<Args>() && ...);`
- L946 _public member_ `constexpr static bool Value = HasValidColumnTypes;`
- L952 _public member_ `constexpr static bool Arg0IsContext = IsCompatibleTargetContextType<SourceContext, Arg0>;`
- L953 _public member_ `constexpr static bool Arg0IsRowHandle = IsRowHandleType<Arg0>;`
- L954 _public member_ `constexpr static bool Arg0IsArgument = IsValidColumnType<Arg0>();`
- L955 _public member_ `constexpr static bool Arg0IsValidRowHandle = Arg0IsRowHandle && IsRowTypeCompatibleWithColumns<Arg0, Args...>();`
- L956 _public member_ `constexpr static bool Arg0IsValid = (Arg0IsContext || Arg0IsValidRowHandle || Arg0IsArgument);`
- L966 _public member_ `constexpr static bool Value = Arg0IsValid && HasValidColumnTypes;`
- L983 _public member_ `constexpr static bool Arg1IsRowHandle = IsRowHandleType<Arg1>;`
- L984 _public member_ `constexpr static bool Arg1IsArgument = IsValidColumnType<Arg1>();`
- L985 _public member_ `constexpr static bool Arg1IsValidRowHandle = Arg1IsRowHandle && IsRowTypeCompatibleWithColumns<Arg1, Args...>();`
- L986 _public member_ `constexpr static bool Arg1IsValid = (Arg1IsValidRowHandle || Arg1IsArgument);`
- L996 _public member_ `constexpr static bool Value = Arg0IsValid && Arg1IsValid && HasValidColumnTypes;`
- L1002 _public member_ `constexpr static bool Value = false;`

#### struct `UE::Editor::DataStorage::Queries::Private::IsValidSelectFunctionSignatureImpl2`  
`template<SourceQueryContext SourceContext, typename Arg0, typename... Args> struct IsValidSelectFunctionSignatureImpl2<SourceContext, Arg0, Args...>`  
_L950-967_
- L943 _public member_ `constexpr static bool HasValidColumnTypes = (IsValidColumnType<Args>() && ...);`
- L946 _public member_ `constexpr static bool Value = HasValidColumnTypes;`
- L952 _public member_ `constexpr static bool Arg0IsContext = IsCompatibleTargetContextType<SourceContext, Arg0>;`
- L953 _public member_ `constexpr static bool Arg0IsRowHandle = IsRowHandleType<Arg0>;`
- L954 _public member_ `constexpr static bool Arg0IsArgument = IsValidColumnType<Arg0>();`
- L955 _public member_ `constexpr static bool Arg0IsValidRowHandle = Arg0IsRowHandle && IsRowTypeCompatibleWithColumns<Arg0, Args...>();`
- L956 _public member_ `constexpr static bool Arg0IsValid = (Arg0IsContext || Arg0IsValidRowHandle || Arg0IsArgument);`
- L966 _public member_ `constexpr static bool Value = Arg0IsValid && HasValidColumnTypes;`
- L983 _public member_ `constexpr static bool Arg1IsRowHandle = IsRowHandleType<Arg1>;`
- L984 _public member_ `constexpr static bool Arg1IsArgument = IsValidColumnType<Arg1>();`
- L985 _public member_ `constexpr static bool Arg1IsValidRowHandle = Arg1IsRowHandle && IsRowTypeCompatibleWithColumns<Arg1, Args...>();`
- L986 _public member_ `constexpr static bool Arg1IsValid = (Arg1IsValidRowHandle || Arg1IsArgument);`
- L996 _public member_ `constexpr static bool Value = Arg0IsValid && Arg1IsValid && HasValidColumnTypes;`
- L1002 _public member_ `constexpr static bool Value = false;`

#### struct `UE::Editor::DataStorage::Queries::Private::IsValidSelectFunctionSignatureImpl2`  
`template<SourceQueryContext SourceContext, typename Arg0, typename Arg1, typename... Args> struct IsValidSelectFunctionSignatureImpl2<SourceContext, Arg0, Arg1, Args...>`  
_L970-997_
- L943 _public member_ `constexpr static bool HasValidColumnTypes = (IsValidColumnType<Args>() && ...);`
- L946 _public member_ `constexpr static bool Value = HasValidColumnTypes;`
- L952 _public member_ `constexpr static bool Arg0IsContext = IsCompatibleTargetContextType<SourceContext, Arg0>;`
- L953 _public member_ `constexpr static bool Arg0IsRowHandle = IsRowHandleType<Arg0>;`
- L954 _public member_ `constexpr static bool Arg0IsArgument = IsValidColumnType<Arg0>();`
- L955 _public member_ `constexpr static bool Arg0IsValidRowHandle = Arg0IsRowHandle && IsRowTypeCompatibleWithColumns<Arg0, Args...>();`
- L956 _public member_ `constexpr static bool Arg0IsValid = (Arg0IsContext || Arg0IsValidRowHandle || Arg0IsArgument);`
- L966 _public member_ `constexpr static bool Value = Arg0IsValid && HasValidColumnTypes;`
- L983 _public member_ `constexpr static bool Arg1IsRowHandle = IsRowHandleType<Arg1>;`
- L984 _public member_ `constexpr static bool Arg1IsArgument = IsValidColumnType<Arg1>();`
- L985 _public member_ `constexpr static bool Arg1IsValidRowHandle = Arg1IsRowHandle && IsRowTypeCompatibleWithColumns<Arg1, Args...>();`
- L986 _public member_ `constexpr static bool Arg1IsValid = (Arg1IsValidRowHandle || Arg1IsArgument);`
- L996 _public member_ `constexpr static bool Value = Arg0IsValid && Arg1IsValid && HasValidColumnTypes;`
- L1002 _public member_ `constexpr static bool Value = false;`

#### struct `UE::Editor::DataStorage::Queries::Private::IsValidSelectFunctionSignatureImpl2`  
`template<SourceQueryContext SourceContext> struct IsValidSelectFunctionSignatureImpl2<SourceContext>`  
_L1000-1003_
- L943 _public member_ `constexpr static bool HasValidColumnTypes = (IsValidColumnType<Args>() && ...);`
- L946 _public member_ `constexpr static bool Value = HasValidColumnTypes;`
- L952 _public member_ `constexpr static bool Arg0IsContext = IsCompatibleTargetContextType<SourceContext, Arg0>;`
- L953 _public member_ `constexpr static bool Arg0IsRowHandle = IsRowHandleType<Arg0>;`
- L954 _public member_ `constexpr static bool Arg0IsArgument = IsValidColumnType<Arg0>();`
- L955 _public member_ `constexpr static bool Arg0IsValidRowHandle = Arg0IsRowHandle && IsRowTypeCompatibleWithColumns<Arg0, Args...>();`
- L956 _public member_ `constexpr static bool Arg0IsValid = (Arg0IsContext || Arg0IsValidRowHandle || Arg0IsArgument);`
- L966 _public member_ `constexpr static bool Value = Arg0IsValid && HasValidColumnTypes;`
- L983 _public member_ `constexpr static bool Arg1IsRowHandle = IsRowHandleType<Arg1>;`
- L984 _public member_ `constexpr static bool Arg1IsArgument = IsValidColumnType<Arg1>();`
- L985 _public member_ `constexpr static bool Arg1IsValidRowHandle = Arg1IsRowHandle && IsRowTypeCompatibleWithColumns<Arg1, Args...>();`
- L986 _public member_ `constexpr static bool Arg1IsValid = (Arg1IsValidRowHandle || Arg1IsArgument);`
- L996 _public member_ `constexpr static bool Value = Arg0IsValid && Arg1IsValid && HasValidColumnTypes;`
- L1002 _public member_ `constexpr static bool Value = false;`

#### struct `UE::Editor::DataStorage::Queries::Private::IsValidSelectFunctionSignatureImpl`  
`template<SourceQueryContext SourceContext, typename T> struct IsValidSelectFunctionSignatureImpl`  
_L1006-1009_
- L1008 _public member_ `constexpr static bool Value = false;`
- L1014 _public member_ `constexpr static bool Value = IsValidSelectFunctionSignatureImpl2<SourceContext, Args...>::Value;`

#### struct `UE::Editor::DataStorage::Queries::Private::IsValidSelectFunctionSignatureImpl`  
`template<SourceQueryContext SourceContext, typename... Args> struct IsValidSelectFunctionSignatureImpl<SourceContext, void (*)(Args...)>`  
_L1012-1015_
- L1008 _public member_ `constexpr static bool Value = false;`
- L1014 _public member_ `constexpr static bool Value = IsValidSelectFunctionSignatureImpl2<SourceContext, Args...>::Value;`

#### struct `UE::Editor::DataStorage::Queries::Private::IsValidSelectFunctionSignatureImpl`  
`template<SourceQueryContext SourceContext, typename Class, typename... Args> struct IsValidSelectFunctionSignatureImpl<SourceContext, void (Class::*)(Args...)>`  
_L1018-1021_
- L1008 _public member_ `constexpr static bool Value = false;`
- L1014 _public member_ `constexpr static bool Value = IsValidSelectFunctionSignatureImpl2<SourceContext, Args...>::Value;`

#### struct `UE::Editor::DataStorage::Queries::Private::IsValidSelectFunctionSignatureImpl`  
`template<SourceQueryContext SourceContext, typename Class, typename... Args> struct IsValidSelectFunctionSignatureImpl<SourceContext, void (Class::*)(Args...) const>`  
_L1024-1027_
- L1008 _public member_ `constexpr static bool Value = false;`
- L1014 _public member_ `constexpr static bool Value = IsValidSelectFunctionSignatureImpl2<SourceContext, Args...>::Value;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L14 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L18 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage::Queries`)
- L23 _function_ `template<typename Target, typename ArgsCurrent, typename... ArgsRemainder> constexpr uint32 GetVarArgIndex()` (scope `UE::Editor::DataStorage::Queries::Private`) — This assumes that the types are unique, but for queries this should be true and otherwise both results would point to the first found index.
- L36 _function_ `template<typename Type> constexpr EQueryAccessType GetAccessType()` (scope `UE::Editor::DataStorage::Queries::Private`)
- L38 _typedef_ `using BaseType = typename std::remove_reference_t<Type>;` (scope `UE::Editor::DataStorage::Queries::Private::GetAccessType`)
- L50 _function_ `template<typename Type> constexpr EQueryDependencyFlags GetDependencyFlags()` (scope `UE::Editor::DataStorage::Queries::Private`)
- L52 _typedef_ `using BaseType = typename std::remove_reference_t<Type>;` (scope `UE::Editor::DataStorage::Queries::Private::GetDependencyFlags`)
- L53 _typedef_ `using SubsystemTraits = TTypedElementSubsystemTraits<std::remove_const_t<BaseType>>;` (scope `UE::Editor::DataStorage::Queries::Private::GetDependencyFlags`)
- L78 _function_ `template<typename... TargetTypes> FDependency& FDependency::ReadOnly()` (scope `UE::Editor::DataStorage::Queries::FDependency`)
- L85 _function_ `template<typename... TargetTypes> FDependency& FDependency::ReadWrite()` (scope `UE::Editor::DataStorage::Queries::FDependency`)
- L97 _function_ `template<TColumnType ColumnType> FObserver FObserver::OnAdd()` (scope `UE::Editor::DataStorage::Queries::FObserver`)
- L103 _function_ `template<TColumnType ColumnType> FObserver FObserver::OnRemove()` (scope `UE::Editor::DataStorage::Queries::FObserver`)
- L109 _function_ `template<TColumnType ColumnType> FObserver& FObserver::SetMonitoredColumn()` (scope `UE::Editor::DataStorage::Queries::FObserver`)
- L119 _function_ `FQueryContextForwarder::FQueryContextForwarder( const FQueryDescription& InDescription, IQueryContext& InParentContext) : ParentContext(InParentContext) , Description(InDescription)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L126 _function_ `const void* FQueryContextForwarder::GetColumn(const UScriptStruct* ColumnType) const` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L131 _function_ `void* FQueryContextForwarder::GetMutableColumn(const UScriptStruct* ColumnType)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L136 _function_ `void FQueryContextForwarder::GetColumns(TArrayView<char*> RetrievedAddresses, TConstArrayView<TWeakObjectPtr<const UScriptStruct>> ColumnTypes, TConstArrayView<EQueryAccessType> AccessTypes)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L142 _function_ `void FQueryContextForwarder::GetColumnsUnguarded(int32 TypeCount, char** RetrievedAddresses, const TWeakObjectPtr<const UScriptStruct>* ColumnTypes, const EQueryAccessType* AccessTypes)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L148 _function_ `bool FQueryContextForwarder::HasColumn(const UScriptStruct* ColumnType) const` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L153 _function_ `UObject* FQueryContextForwarder::GetMutableDependency(const UClass* DependencyClass)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L158 _function_ `const UObject* FQueryContextForwarder::GetDependency(const UClass* DependencyClass)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L163 _function_ `void FQueryContextForwarder::GetDependencies(TArrayView<UObject*> RetrievedAddresses, TConstArrayView<TWeakObjectPtr<const UClass>> DependencyTypes, TConstArrayView<EQueryAccessType> AccessTypes)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L169 _function_ `uint32 FQueryContextForwarder::GetRowCount() const` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L174 _function_ `TConstArrayView<RowHandle> FQueryContextForwarder::GetRowHandles() const` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L179 _function_ `void FQueryContextForwarder::RemoveRow(RowHandle Row)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L184 _function_ `void FQueryContextForwarder::RemoveRows(TConstArrayView<RowHandle> Rows)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L189 _function_ `void FQueryContextForwarder::AddColumns(RowHandle Row, TConstArrayView<const UScriptStruct*> ColumnTypes)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L194 _function_ `void FQueryContextForwarder::AddColumns(TConstArrayView<RowHandle> Rows, TConstArrayView<const UScriptStruct*> ColumnTypes)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L199 _function_ `void FQueryContextForwarder::RemoveColumns(RowHandle Row, TConstArrayView<const UScriptStruct*> ColumnTypes)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L204 _function_ `void FQueryContextForwarder::RemoveColumns(TConstArrayView<RowHandle> Rows, TConstArrayView<const UScriptStruct*> ColumnTypes)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L209 _function_ `FQueryResult FQueryContextForwarder::RunQuery(QueryHandle Query)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L214 _function_ `FQueryResult FQueryContextForwarder::RunSubquery(int32 SubqueryIndex)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L219 _function_ `FQueryResult FQueryContextForwarder::RunSubquery(int32 SubqueryIndex, SubqueryCallbackRef Callback)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L225 _function_ `FQueryResult FQueryContextForwarder::RunSubquery(int32 SubqueryIndex, RowHandle Row, SubqueryCallbackRef Callback)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L231 _function_ `void FQueryContextForwarder::PushCommand(void(* CommandFunction)(void*), void* CommandData)` (scope `UE::Editor::DataStorage::Queries::FQueryContextForwarder`)
- L241 _function_ `template<typename... Dependencies> FCachedQueryContext<Dependencies...>::FCachedQueryContext( const FQueryDescription& InDescription, IQueryContext& InParentContext) : FQueryContextForwarder(InDescription, InParentContext)` (scope `UE::Editor::DataStorage::Queries::FCachedQueryContext`)
- L248 _function_ `template<typename... Dependencies> void FCachedQueryContext<Dependencies...>::Register(FQueryDescription& Query)` (scope `UE::Editor::DataStorage::Queries::FCachedQueryContext`)
- L261 _function_ `template<typename... Dependencies> template<typename Dependency> Dependency& FCachedQueryContext<Dependencies...>::GetCachedMutableDependency()` (scope `UE::Editor::DataStorage::Queries::FCachedQueryContext`)
- L271 _function_ `template<typename... Dependencies> template<typename Dependency> const Dependency& FCachedQueryContext<Dependencies...>::GetCachedDependency() const` (scope `UE::Editor::DataStorage::Queries::FCachedQueryContext`)
- L290 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage::Queries`)
- L313 _function_ `template<typename... Columns> constexpr bool AreAllColumnsReferences()` (scope `UE::Editor::DataStorage::Queries::Private`)
- L326 _function_ `template<typename... Columns> constexpr bool AreAllColumnsPointers()` (scope `UE::Editor::DataStorage::Queries::Private`)
- L339 _typedef_ `template<typename Column> using BaseColumnType = std::remove_pointer_t<std::remove_reference_t<Column>>;` (scope `UE::Editor::DataStorage::Queries::Private`)
- L342 _typedef_ `template<typename Column> using UndecoratedColumnType = std::remove_cv_t<BaseColumnType<Column>>;` (scope `UE::Editor::DataStorage::Queries::Private`)
- L345 _function_ `template<typename Column> constexpr bool IsValidColumnType()` (scope `UE::Editor::DataStorage::Queries::Private`)
- L350 _typedef_ `using BaseType = typename std::remove_const_t<std::remove_reference_t<Column>>;` (scope `UE::Editor::DataStorage::Queries::Private::IsValidColumnType`)
- L355 _typedef_ `using BaseType = typename std::remove_const_t<std::remove_pointer_t<Column>>;` (scope `UE::Editor::DataStorage::Queries::Private::IsValidColumnType`)
- L365 _function_ `template<typename Column> const UScriptStruct* GetColumnType()` (scope `UE::Editor::DataStorage::Queries::Private`)
- L374 _function_ `template<typename RowType, typename... Columns> constexpr bool IsRowTypeCompatibleWithColumns()` (scope `UE::Editor::DataStorage::Queries::Private`)
- L400 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::FFunctionColumnInfo::CheckValidity`)
- L447 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::FFunctionColumnInfo::FFunctionColumnInfo`)
- L577 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::FContextColumnsFunction::Call`)
- L620 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::FRowHandleColumnsFunction::Call`)
- L668 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::FColumnsFunction::Call`)
- L735 _function_ `template<SourceQueryContext SourceContext, bool ValidateColumns, typename... Args> void BindQueryFunction(QueryCallback& Function, void (*Callback)(Args...))` (scope `UE::Editor::DataStorage::Queries::Private`)
- L739 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::BindQueryFunction`)
- L745 _function_ `template<SourceQueryContext SourceContext, bool ValidateColumns, typename Class, typename... Args> void BindQueryFunction(QueryCallback& Function, Class* Target, void (Class::*Callback)(Args...))` (scope `UE::Editor::DataStorage::Queries::Private`)
- L755 _function_ `template<SourceQueryContext SourceContext, bool ValidateColumns, typename Class, typename... Args> void BindQueryFunction(QueryCallback& Function, Class* Target, void (Class::*Callback)(Args...) const)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L765 _function_ `template<SourceQueryContext SourceContext, bool ValidateColumns, typename Functor, typename Class, typename... Args> void BindQueryFunction_Expand(QueryCallback& Function, Functor&& CallbackObject, void (Class::*Callback)(Args...) const)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L769 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::BindQueryFunction_Expand`)
- L785 _function_ `template<SourceQueryContext SourceContext, bool ValidateColumns, typename Functor> void BindQueryFunction(QueryCallback& Function, Functor&& Callback)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L795 _function_ `template<bool ValidateColumns, SourceQueryContext SourceContext, typename... Args> AUTORTFM_INFER void CallQueryFunction(const FQueryDescription& Description, SourceContext& Context, QueryCallback& Function, void (*Callback)(Args...))` (scope `UE::Editor::DataStorage::Queries::Private`)
- L802 _function_ `template<bool ValidateColumns, SourceQueryContext SourceContext, typename Class, typename... Args> AUTORTFM_INFER void CallQueryFunction(const FQueryDescription& Description, SourceContext& Context, Class* Target, void (Class::* Callback)(Args...))` (scope `UE::Editor::DataStorage::Queries::Private`)
- L816 _function_ `template<bool ValidateColumns, SourceQueryContext SourceContext, typename Functor, typename Class, typename... Args> AUTORTFM_INFER void CallQueryFunction_Expand(const FQueryDescription& Description, SourceContext& Context, const Functor& CallbackObject, void (Class::* Callback)(Args...) const)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L830 _function_ `template<bool ValidateColumns, SourceQueryContext SourceContext, typename Functor> AUTORTFM_INFER void CallQueryFunction(const FQueryDescription& Description, SourceContext& Context, const Functor& Callback)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L838 _function_ `template<typename Arg> void AddColumnToSelect(Select& Target)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L850 _function_ `template<typename ContextType> void RegisterDependencies(FQueryDescription& Query)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L852 _typedef_ `using BaseType = typename TRemoveReference<ContextType>::Type;` (scope `UE::Editor::DataStorage::Queries::Private::RegisterDependencies`)
- L917 _function_ `template<SourceQueryContext SourceContext, typename... Args> void RegisterFunctionArguments(FQueryDescription& Query, Select& Target, void (*)(Args...))` (scope `UE::Editor::DataStorage::Queries::Private`)
- L923 _function_ `template<SourceQueryContext SourceContext, typename Class, typename... Args> void RegisterFunctionArguments(FQueryDescription& Query, Select& Target, void (Class::*)(Args...))` (scope `UE::Editor::DataStorage::Queries::Private`)
- L929 _function_ `template<SourceQueryContext SourceContext, typename Class, typename... Args> void RegisterFunctionArguments(FQueryDescription& Query, Select& Target, void (Class::*)(Args...) const)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L935 _function_ `template<SourceQueryContext SourceContext, typename Functor> void RegisterFunctionArguments(FQueryDescription& Query, Select& Target, Functor)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L1029 _function_ `template<SourceQueryContext SourceContext, typename T> constexpr bool IsValidSelectFunctionSignature()` (scope `UE::Editor::DataStorage::Queries::Private`)
- L1041 _function_ `inline void PrepareForQueryBinding(FQueryDescription& Query, const FProcessor& Processor)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L1061 _function_ `inline void PrepareForQueryBinding(FQueryDescription& Query, const FObserver& Observer)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L1078 _function_ `inline void PrepareForQueryBinding(FQueryDescription& Query, const FPhaseAmble& PhaseAmble)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L1096 _function_ `template<typename CallbackType, typename Function> void PrepareForQueryBinding(Select& Target, FQueryDescription& Query, FName Name, const CallbackType& Type, Function Callback)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L1120 _function_ `template<typename CallbackType, typename Function> Select::Select(FName Name, const CallbackType& Type, Function&& Callback) : Select()` (scope `UE::Editor::DataStorage::Queries::Select`)
- L1129 _function_ `template<typename CallbackType, typename Class, typename Function> Select::Select(FName Name, const CallbackType& Type, Class* Instance, Function&& Callback) : Select()` (scope `UE::Editor::DataStorage::Queries::Select`)
- L1138 _function_ `template<TDataColumnType... TargetTypes> Select& Select::ReadOnly()` (scope `UE::Editor::DataStorage::Queries::Select`)
- L1145 _function_ `template<TDataColumnType... TargetTypes> Select& Select::ReadOnly(EOptional Optional)` (scope `UE::Editor::DataStorage::Queries::Select`)
- L1152 _function_ `template<TDynamicColumnTemplate Target> Select& Select::ReadOnly(const FName& Identifier)` (scope `UE::Editor::DataStorage::Queries::Select`)
- L1163 _function_ `template<TDataColumnType... TargetTypes> Select& Select::ReadWrite()` (scope `UE::Editor::DataStorage::Queries::Select`)
- L1170 _function_ `template<TDynamicColumnTemplate Target> Select& Select::ReadWrite(const FName& Identifier)` (scope `UE::Editor::DataStorage::Queries::Select`)
- L1185 _function_ `template<TColumnType... TargetTypes> FSimpleQuery& FSimpleQuery::All()` (scope `UE::Editor::DataStorage::Queries::FSimpleQuery`)
- L1192 _function_ `template<TColumnType... TargetTypes> FSimpleQuery& FSimpleQuery::Any()` (scope `UE::Editor::DataStorage::Queries::FSimpleQuery`)
- L1199 _function_ `template <TDynamicColumnTemplate DynamicColumnTemplate> FSimpleQuery& FSimpleQuery::Any(const FName& Identifier)` (scope `UE::Editor::DataStorage::Queries::FSimpleQuery`)
- L1209 _function_ `template<TColumnType... TargetTypes> FSimpleQuery& FSimpleQuery::None()` (scope `UE::Editor::DataStorage::Queries::FSimpleQuery`)
- L1216 _function_ `template<TValueTagType> FSimpleQuery& FSimpleQuery::All(const FName& Tag)` (scope `UE::Editor::DataStorage::Queries::FSimpleQuery`)
- L1222 _function_ `template<TValueTagType> FSimpleQuery& FSimpleQuery::All(const FName& Tag, const FName& Value)` (scope `UE::Editor::DataStorage::Queries::FSimpleQuery`)
- L1228 _function_ `template <TDynamicColumnTemplate DynamicColumnTemplate> FSimpleQuery& FSimpleQuery::None(const FName& Identifier)` (scope `UE::Editor::DataStorage::Queries::FSimpleQuery`)
- L1238 _function_ `template <TDynamicColumnTemplate DynamicColumnTemplate> FSimpleQuery& FSimpleQuery::All(const FName& Identifier)` (scope `UE::Editor::DataStorage::Queries::FSimpleQuery`)
- L1248 _function_ `template <TEnumType EnumT> FSimpleQuery& FSimpleQuery::All()` (scope `UE::Editor::DataStorage::Queries::FSimpleQuery`)
- L1254 _function_ `template <TEnumType EnumT> FSimpleQuery& FSimpleQuery::All(EnumT EnumValue)` (scope `UE::Editor::DataStorage::Queries::FSimpleQuery`)
- L1260 _function_ `template<auto Value, TEnumType EnumT = decltype(Value)> FSimpleQuery& All()` (scope `UE::Editor::DataStorage::Queries`)
- L1269 _function_ `template<typename Function> DirectQueryCallback CreateDirectQueryCallbackBinding(Function&& Callback)` (scope `UE::Editor::DataStorage::Queries`) — External query bindings
- L1287 _function_ `` (scope `UE::Editor::DataStorage::Queries::CreateDirectQueryCallbackBinding`)
- L1294 _function_ `template<typename Function> SubqueryCallback CreateSubqueryCallbackBinding(Function&& Callback)` (scope `UE::Editor::DataStorage::Queries`)
- L1312 _function_ `` (scope `UE::Editor::DataStorage::Queries::CreateSubqueryCallbackBinding`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryCapabilities.h` (Public)


#### enum `UE::Editor::DataStorage::Queries::EContextCapabilityFlags`  
`enum class EContextCapabilityFlags`  
_L22-26_
- L24 _public enumerator_ `SupportsSingle = 1 << 0`
- L25 _public enumerator_ `SupportsBatch = 1 << 1`

#### struct `UE::Editor::DataStorage::Queries::IContextCapability`  
`struct IContextCapability`  
_L36-39_
- desc: Class fragments used to composite a context. A query context is created by combining various context capabilities together. Users can request a query context being created with one or more of these capabilities and based on the requested capabilities they get connected with an implementation. Each capability represents a subset of functionality of TEDS such as access to column data, creating new rows or access to subqueries.
- L38 _public prototype_ `virtual ~IContextCapability() = default;`

#### struct `UE::Editor::DataStorage::Queries::ImplementsContextCapability`  
`template<ContextCapability Capability> struct ImplementsContextCapability`  
_L45-49_
- L47 _public member_ `static constexpr int32 Id = Capability::Id;`
- L48 _public member_ `inline static FName Name = Capability::Name;`

#### struct `UE::Editor::DataStorage::Queries::FCapabilityCompatibilityCheck`  
`template<typename Implementation, typename Capability> struct FCapabilityCompatibilityCheck`  
_L83-85_

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Editor` (scope `UE`)
- L20 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L20 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L60 _prototype_ `template<typename Return, FunctionType Function> TQueryFunction<Return> BuildQueryFunction(Function&& Callback);` (scope `UE::Editor::DataStorage::Queries`) — forward declaration
- L63 _prototype_ `template<typename Return, FunctionType Function> TConstQueryFunction<Return> BuildConstQueryFunction(Function&& Callback);` (scope `UE::Editor::DataStorage::Queries`) — forward declaration
- L68 _prototype_ `template <typename T> constexpr T& VarType(T& Value);` (scope `UE::Editor::DataStorage::Queries`)
- L71 _prototype_ `template <typename T> constexpr const T& VarType(const T& Value);` (scope `UE::Editor::DataStorage::Queries`)
- L74 _prototype_ `template <typename T> constexpr T&& VarType(T&& Value);` (scope `UE::Editor::DataStorage::Queries`)
- L76 _macro_ `#define ArgType(Type, Name) Type`
- L77 _macro_ `#define ArgName(Type, Name) Name`
- L78 _macro_ `#define ArgTypeName(Type, Name) Type Name`
- L87 _macro_ `#define CapabilityStart(InCapability, InFlags) \`
- L96 _macro_ `#define Function0(Capability, Return, Function) \`
- L101 _macro_ `#define Function1(Capability, Return, Function, Arg1) \`
- L106 _macro_ `#define Function2(Capability, Return, Function, Arg1, Arg2) \`
- L113 _macro_ `#define Function3(Capability, Return, Function, Arg1, Arg2, Arg3) \`
- L121 _macro_ `#define Function4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4) \`
- L131 _macro_ `#define ConstFunction0(Capability, Return, Function) \`
- L136 _macro_ `#define ConstFunction1(Capability, Return, Function, Arg1) \`
- L141 _macro_ `#define ConstFunction2(Capability, Return, Function, Arg1, Arg2) \`
- L148 _macro_ `#define ConstFunction3(Capability, Return, Function, Arg1, Arg2, Arg3) \`
- L156 _macro_ `#define ConstFunction4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4) \`
- L166 _macro_ `#define CapabilityEnd(InCapability) \`
- L170 _macro_ `#define DeprecatedFunction(Version, Msg)`
- L193 _variable_ `static constexpr int32 CapabilityBaseId = __COUNTER__;` (scope `UE::Editor::DataStorage::Queries`) — Assign a unique id to each capability, starting at 0. Since __COUNTER__ is a preprocessor defined macro other headers are free to use it as well, leading to the starting address not being 0, hence recording the first occurrence and subtracting it from the ids.
- L195 _macro_ `#define WithWrappers 1`
- L206 _macro_ `#define Function0(Capability, Return, Function) virtual Return Function() = 0;`
- L207 _macro_ `#define Function1(Capability, Return, Function, Arg1) virtual Return Function(ArgTypeName Arg1 ) = 0;`
- L208 _macro_ `#define Function2(Capability, Return, Function, Arg1, Arg2) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 ) = 0;`
- L209 _macro_ `#define Function3(Capability, Return, Function, Arg1, Arg2, Arg3) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 ) = 0;`
- L210 _macro_ `#define Function4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 , ArgTypeName Arg4 ) = 0;`
- L212 _macro_ `#define ConstFunction0(Capability, Return, Function) virtual Return Function() const = 0;`
- L213 _macro_ `#define ConstFunction1(Capability, Return, Function, Arg1) virtual Return Function(ArgTypeName Arg1 ) const = 0;`
- L214 _macro_ `#define ConstFunction2(Capability, Return, Function, Arg1, Arg2) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 ) const = 0;`
- L215 _macro_ `#define ConstFunction3(Capability, Return, Function, Arg1, Arg2, Arg3) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 ) const = 0;`
- L216 _macro_ `#define ConstFunction4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 , ArgTypeName Arg4 ) const = 0;`
- L218 _macro_ `#define DeprecatedFunction(Version, Msg) UE_DEPRECATED(Version, Msg)`

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryCapabilities.inl` (Public)


#### Free symbols / members of external scopes

- L41 _function_ `template<TColumnType... ColumnTypes> bool TableHasColumns(TableHandle Table) const` — Returns true if the table contains the requested columns, otherwise false.
- L53 _function_ `ConstFunction0(CurrentTableInfo, TableHandle, GetCurrentTable) ConstFunction1(CurrentTableInfo, bool, CurrentTableHasColumns, (TConstArrayView<const UScriptStruct*>, Columns)) ConstFunction0(CurrentTableInfo, const UScriptStruct*, GetTagForCurrentTable) #if defined(WithWrappers) template<TColumnType... ColumnTypes> bool CurrentTableHasColumns() const` — Returns the handle to the table that's currently being used in the context.
- L97 _function_ `template<TColumnType... ColumnTypes> TableHandle RegisterTable(const FName& TableName)` — Register a table by name.
- L104 _function_ `template<TColumnType... ColumnTypes> TableHandle RegisterTable(const FName& TableName, const FTableRegistrationOptions& Options)` — Register a table by name with additional configuration options.
- L114 _function_ `template<FunctionType Function> void RegisterTableForeignKey(TableHandle Table, const FName& Domain, Function&& Callback)` — Register a function that's used to generate a foreign key for a particular row. Foreign keys create a unique identifier that represents the row for a specific domain.
- L120 _function_ `inline TableHandle RegisterTable(TableHandle SourceTable, TConstArrayView<const UScriptStruct*> ColumnList, const FName& TableName)` — `UE_DEPRECATED(5.8, "Use the version of 'RegisterTable' that takes a 'FTableRegistrationOptions'.")`
- L127 _function_ `TableHandle RegisterTable(TableHandle SourceTable, const FName& TableName)` — `UE_DEPRECATED(5.8, "Use the version of 'RegisterTable' that takes a 'FTableRegistrationOptions'.")`
- L138 _function_ `CapabilityStart(SingleRowInfo, EContextCapabilityFlags::SupportsSingle) DeprecatedFunction(5.8, "Use CurrentTableHasColumns instead. Make sure to add CurrentTableInfo to the query's context capabilities.") ConstFunction1(SingleRowInfo, bool, CurrentRowHasColumns, (TConstArrayView<const UScriptStruct*>, Columns)) ConstFunction0(SingleRowInfo, RowHandle, GetCurrentRow) #if defined(WithWrappers) template<TColumnType... ColumnTypes> DeprecatedFunction(5.8, "Use CurrentTableHasColumns instead. Make sure to add CurrentTableInfo to the query's context capabilities.") bool CurrentRowHasColumns() const` — Capability to provide information about the currently active row.
- L167 _function_ `CapabilityStart(RowBatchInfo, EContextCapabilityFlags::SupportsBatch) ConstFunction0(RowBatchInfo, uint32, GetBatchRowCount) ConstFunction0(RowBatchInfo, FRowHandleArrayView, GetBatchRowHandles) DeprecatedFunction(5.8, "Use CurrentTableHasColumns instead. Make sure to add CurrentTableInfo to the query's context capabilities.") ConstFunction1(RowBatchInfo, bool, CurrentBatchTableHasColumns, (TConstArrayView<const UScriptStruct*>, Columns)) ConstFunction1(RowBatchInfo, const void*, GetColumnBatchAddress, (const UScriptStruct*, ColumnType)) Function1(RowBatchInfo, void*, GetMutableColumnBatchAddress, (const UScriptStruct*, ColumnType)) #if defined(WithWrappers) template<TColumnType... ColumnTypes> DeprecatedFunction(5.8, "Use CurrentTableHasColumns instead. Make sure to add CurrentTableInfo to the query's context capabilities.") bool CurrentBatchTableHasColumns() const` — Capability to provide information about the currently active batch.
- L201 _function_ `template<typename CallbackType, typename... Args> void ForEachRow(CallbackType&& Callback, TBatch<Args>... Batches) const` — Utility function to iterate over each individual cell in the rows in this batch for the requested columns. Example: ForEachRow([](RowHandle Row, const ColumnA&, const ColumnB&), ArgA, ArgB); where ArgA is a TBatch<ColumnA> or TConstBatch<ColumnA> (a.k.a. TBatch<const ColumnA>) and ArgB is a TBatch<ColumnB> or TConstBatch<ColumnB> (a.k.a. TBatch<const ColumnB>) argument in the query callback function.
- L207 _function_ `` (scope `ForEachRow`)
- L220 _function_ `template<typename CallbackType, typename... Args> void ForEachRow(CallbackType&& Callback, TBatch<Args>... Batches)` — Utility function to iterate over each individual cell in the rows in this batch for the requested columns. Example: ForEachRow([](RowHandle Row, ColumnA&, const ColumnB&), ArgA, ArgB); where ArgA is a TBatch<ColumnA> and ArgB is a TConstBatch<ColumnB> (a.k.a. TBatch<const ColumnB>) or TBatch<ColumnB> argument in the query callback function.
- L257 _function_ `template<TDynamicColumnTemplate DynamicColumnTemplateType> const UScriptStruct* FindDynamicColumnType(const FName& Identifier) const` — Finds the type information for a dynamic column. If the dynamic column has not been generated, then return nullptr The DynamicColumnTemplateType may be a type derived from either FColumn or FTag, anything else will result in a compile error.
- L268 _function_ `template<TDynamicColumnTemplate DynamicColumnTemplateType, TVariantName Identifier> const UScriptStruct* FindDynamicColumnType() const` — Finds the type information for a dynamic column. If the dynamic column has not been generated, then return nullptr The DynamicColumnTemplateType may be a type derived from either FColumn or FTag, anything else will result in a compile error.
- L272 _function_ `` (scope `FindDynamicColumnType`)
- L284 _function_ `template<TColumnDescType ColumnType> const UScriptStruct* FindDynamicColumnType(const ColumnType& Column) const` — Finds the type information for a dynamic column. If the dynamic column has not been generated, then return nullptr The ColumnType can be any TColumn but TColumns without a name or dynamic column type will return a nullptr.
- L296 _function_ `template<TDynamicColumnTemplate DynamicColumnTemplateType> void ForEachDynamicColumnType(TFunctionRef<void(const UScriptStruct& Type)> Callback) const` — Executes the given callback for each known dynamic column that derives from the base template provided. The DynamicColumnTemplateType may be a type derived from either FColumn or FTag, anything else will result in a compile error.
- L302 _function_ `const UScriptStruct* FindDynamicColumnType(const FDynamicColumnDescription& Description) const` — `UE_DEPRECATED(5.8, "Please one of the new versions of FindDynamicColumnType.")`
- L308 _function_ `const UScriptStruct* FindDynamicColumn(const FDynamicColumnDescription& Description) const` — `UE_DEPRECATED(5.8, "Please one of the new versions of FindDynamicColumnType.")`

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryCapabilityForwarder.h` (Public)


#### struct `UE::Editor::DataStorage::Queries::Private::FQueryContext`  
`struct FQueryContext`  
_L16-16_

#### struct `UE::Editor::DataStorage::Queries::Private::FConstQueryContext`  
`struct FConstQueryContext`  
_L17-17_

#### struct `UE::Editor::DataStorage::Queries::Private::TForwarder`  
`template<bool bIsConst, typename... Capabilities> struct TForwarder`  
_L19-24_
- L32 _public prototype_ `TForwarder() = default;`
- L33 _public function_ `explicit TForwarder(IContextContract& Contract) : Contract(&Contract)`
- L34 _public function_ `explicit TForwarder(const IContextContract& Contract) requires (bIsConst) : Contract(&Contract)`
- L37 _protected member_ `std::conditional_t<bIsConst, const IContextContract*, IContextContract*> Contract = nullptr;`

#### struct `UE::Editor::DataStorage::Queries::Private::TForwarder`  
`template<bool bIsConst, typename Base, typename...Capabilities> struct TForwarder<bIsConst, Base, Capabilities...> : Base, TForwarder<bIsConst, Capabilities...>`  
_L27-27_
- inherits: `Base,TForwarder<bIsConst,Capabilities...>`
- L32 _public prototype_ `TForwarder() = default;`
- L33 _public function_ `explicit TForwarder(IContextContract& Contract) : Contract(&Contract)`
- L34 _public function_ `explicit TForwarder(const IContextContract& Contract) requires (bIsConst) : Contract(&Contract)`
- L37 _protected member_ `std::conditional_t<bIsConst, const IContextContract*, IContextContract*> Contract = nullptr;`

#### struct `UE::Editor::DataStorage::Queries::Private::TForwarder`  
`template<bool bIsConst> struct TForwarder<bIsConst> : std::conditional_t<bIsConst, FConstQueryContext, FQueryContext>`  
_L30-38_
- inherits: `std::conditional_t<bIsConst,FConstQueryContext,FQueryContext>`
- L32 _public prototype_ `TForwarder() = default;`
- L33 _public function_ `explicit TForwarder(IContextContract& Contract) : Contract(&Contract)`
- L34 _public function_ `explicit TForwarder(const IContextContract& Contract) requires (bIsConst) : Contract(&Contract)`
- L37 _protected member_ `std::conditional_t<bIsConst, const IContextContract*, IContextContract*> Contract = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L10 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L10 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage::Queries`)
- L40 _macro_ `#define CapabilityStart(Capability, Flags) \`
- L48 _macro_ `#define ArgTypeName(Type, Name) Type Name`
- L49 _macro_ `#define ArgName(Type, Name) Name`
- L50 _macro_ `#define ForwardArg(Type, Name) Forward< Type >( Name )`
- L52 _macro_ `#define Function0(Capability, Return, Function) Return Function() requires (!bIsConst) \`
- L54 _macro_ `#define Function1(Capability, Return, Function, Arg1) Return Function(ArgTypeName Arg1 ) requires (!bIsConst) \`
- L56 _macro_ `#define Function2(Capability, Return, Function, Arg1, Arg2) Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 ) requires (!bIsConst) \`
- L58 _macro_ `#define Function3(Capability, Return, Function, Arg1, Arg2, Arg3) Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 ) requires (!bIsConst) \`
- L60 _macro_ `#define Function4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4) Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 , ArgTypeName Arg4 ) requires (!bIsConst) \`
- L63 _macro_ `#define ConstFunction0(Capability, Return, Function) Return Function() const \`
- L65 _macro_ `#define ConstFunction1(Capability, Return, Function, Arg1) Return Function(ArgTypeName Arg1 ) const \`
- L67 _macro_ `#define ConstFunction2(Capability, Return, Function, Arg1, Arg2) Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 ) const \`
- L69 _macro_ `#define ConstFunction3(Capability, Return, Function, Arg1, Arg2, Arg3) Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 ) const \`
- L71 _macro_ `#define ConstFunction4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4) Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 , ArgTypeName Arg4 ) const \`
- L74 _macro_ `#define CapabilityEnd(Capability) \`
- L77 _macro_ `#define DeprecatedFunction(Version, Msg) UE_DEPRECATED(Version, Msg)`
- L79 _macro_ `#define WithWrappers 1`

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryContext.h` (Public)


#### struct `UE::Editor::DataStorage::Queries::TCapabilityStore`  
`template<ContextCapability... Capabilities> struct TCapabilityStore : Capabilities...`  
_L14-18_
- inherits: `Capabilities...`
- L16 _public member_ `static constexpr bool bIsSingle = (EnumHasAnyFlags(Capabilities::Flags, EContextCapabilityFlags::SupportsSingle) && ...);`
- L17 _public member_ `static constexpr bool bIsBatch = (EnumHasAnyFlags(Capabilities::Flags, EContextCapabilityFlags::SupportsBatch) && ...);`

#### struct `UE::Editor::DataStorage::Queries::TQueryContext`  
`template<ContextCapability... CapabilityTypes> struct TQueryContext final : Private::TForwarder<false, CapabilityTypes...>`  
_L28-43_
- inherits: `Private::TForwarder<false,CapabilityTypes...>`
- desc: Template to composite a query context using context capabilities. Any query callback that requires interacting with the editor data storage requires a context to get access. Each context capability provides access to a different kind of functionality. Some of the capabilities are mutually exclusive and not all places that accept a query callback support the same capabilities. It's therefore recommended to only include the capabilities that are needed by the query callback to improve re-usability or use a predefined query context if the query callback doesn't need to be reused.
- L30 _public typedef_ `using Capabilities = TCapabilityStore<CapabilityTypes...>;`
- L41 _public prototype_ `TQueryContext() = default;`
- L42 _public prototype_ `TQueryContext(IContextContract& Contract);`
- L114 _function_ `template<ContextCapability... CapabilityTypes> TQueryContext<CapabilityTypes...>::TQueryContext(IContextContract& Contract) : Private::TForwarder<false, CapabilityTypes...>(Contract)`

#### struct `UE::Editor::DataStorage::Queries::TConstQueryContext`  
`template<ContextCapability... CapabilityTypes> struct TConstQueryContext final : Private::TForwarder<true, CapabilityTypes...>`  
_L53-65_
- inherits: `Private::TForwarder<true,CapabilityTypes...>`
- desc: Template to composite a query context using context capabilities. Any query callback that requires interacting with the editor data storage requires a context to get access. Each context capability provides access to a different kind of functionality. Some of the capabilities are mutually exclusive and not all places that accept a query callback support the same capabilities. It's therefore recommended to only include the capabilities that are needed by the query callback to improve re-usability or use a predefined query context if the query callback doesn't need to be reused.
- L55 _public typedef_ `using Capabilities = TCapabilityStore<CapabilityTypes...>;`
- L63 _public prototype_ `TConstQueryContext() = default;`
- L64 _public prototype_ `TConstQueryContext(const IContextContract& Contract);`
- L124 _function_ `template<ContextCapability... CapabilityTypes> TConstQueryContext<CapabilityTypes...>::TConstQueryContext(const IContextContract& Contract) : Private::TForwarder<true, CapabilityTypes...>(Contract)`

#### struct `UE::Editor::DataStorage::Queries::TForwardingQueryContext`  
`template<ContextCapability... CapabilityTypes> struct TForwardingQueryContext final : Private::TForwarder<false, CapabilityTypes...>`  
_L68-83_
- inherits: `Private::TForwarder<false,CapabilityTypes...>`
- L70 _public typedef_ `using Capabilities = TCapabilityStore<CapabilityTypes...>;`
- L75 _public prototype_ `TForwardingQueryContext() = default;`
- L76 _public prototype_ `TForwardingQueryContext(IContextContract& Contract);`
- L79 _public prototype_ `template<ContextCapability... InCapabilityTypes> TForwardingQueryContext(TQueryContext<InCapabilityTypes...> QueryContext);`
- L81 _public prototype_ `operator IContextContract& ();`
- L82 _public prototype_ `operator const IContextContract& () const;`
- L134 _function_ `template<ContextCapability... CapabilityTypes> TForwardingQueryContext<CapabilityTypes...>::TForwardingQueryContext(IContextContract& Contract) : Private::TForwarder<false, CapabilityTypes...>(Contract)`
- L141 _function_ `template<ContextCapability... CapabilityTypes> template<ContextCapability... InCapabilityTypes> TForwardingQueryContext<CapabilityTypes...>::TForwardingQueryContext(TQueryContext<InCapabilityTypes...> QueryContext) : Private::TForwarder<false, CapabilityTypes...>(*QueryContext.Contract)`
- L150 _function_ `template<ContextCapability... CapabilityTypes> TForwardingQueryContext<CapabilityTypes...>::operator IContextContract& ()`
- L156 _function_ `template<ContextCapability... CapabilityTypes> TForwardingQueryContext<CapabilityTypes...>::operator const IContextContract& () const`

#### struct `UE::Editor::DataStorage::Queries::TForwardingConstQueryContext`  
`template<ContextCapability... CapabilityTypes> struct TForwardingConstQueryContext final : Private::TForwarder<true, CapabilityTypes...>`  
_L86-102_
- inherits: `Private::TForwarder<true,CapabilityTypes...>`
- L88 _public typedef_ `using Capabilities = TCapabilityStore<CapabilityTypes...>;`
- L93 _public prototype_ `TForwardingConstQueryContext() = default;`
- L94 _public prototype_ `TForwardingConstQueryContext(const IContextContract& Contract);`
- L97 _public prototype_ `template<ContextCapability... InCapabilityTypes> TForwardingConstQueryContext(TQueryContext<InCapabilityTypes...> QueryContext);`
- L99 _public prototype_ `template<ContextCapability... InCapabilityTypes> TForwardingConstQueryContext(TConstQueryContext<InCapabilityTypes...> QueryContext);`
- L101 _public prototype_ `operator const IContextContract& () const;`
- L166 _function_ `template<ContextCapability... CapabilityTypes> TForwardingConstQueryContext<CapabilityTypes...>::TForwardingConstQueryContext(const IContextContract& Contract) : Private::TForwarder<true, CapabilityTypes...>(Contract)`
- L173 _function_ `template<ContextCapability... CapabilityTypes> template<ContextCapability... InCapabilityTypes> TForwardingConstQueryContext<CapabilityTypes...>::TForwardingConstQueryContext(TQueryContext<InCapabilityTypes...> QueryContext) : Private::TForwarder<true, CapabilityTypes...>(*QueryContext.Contract)`
- L183 _function_ `template<ContextCapability... CapabilityTypes> template<ContextCapability... InCapabilityTypes> TForwardingConstQueryContext<CapabilityTypes...>::TForwardingConstQueryContext(TConstQueryContext<InCapabilityTypes...> QueryContext) : Private::TForwarder<true, CapabilityTypes...>(*QueryContext.Contract)`
- L192 _function_ `template<ContextCapability... CapabilityTypes> TForwardingConstQueryContext<CapabilityTypes...>::operator const IContextContract& () const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L9 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryContextImplementation.h` (Public)


#### class `UE::Editor::DataStorage::Queries::TQueryContextImpl`  
`template<bool bIsConst, typename EnvironmentType, typename... ImplementationTypes> class TQueryContextImpl final : public IContextContract`  
_L44-70_
- inherits: `IContextContract`
- desc: Base used for context implementations. This will verify if a context is correctly implemented. Classes that implement capabilities should use this template to automatically satisfy the requirements of a query contract. Any missing functionality in a capability implementation will be reported as a compilation failure. This template will satisfy the IContextContract, but will implement placeholder functions for the functions of capabilities that are not supported.
- L47 _public prototype_ `explicit TQueryContextImpl(EnvironmentType& Environment);`
- L49 _public prototype_ `virtual ~TQueryContextImpl() override = default;`
- L55 _public prototype_ `static constexpr uint64 GetCapabilityMask();`
- L57 _public prototype_ `template<ContextCapability RequestedCapability> static constexpr bool SupportsCapability();`
- L58 _public prototype_ `static bool SupportsCapability(const FName& Capability);`
- L59 _public prototype_ `static constexpr bool SupportsCapability(int32 CapabilityId);`
- L60 _public prototype_ `static constexpr bool SupportsCapabilities(uint64 CapabilityMask);`
- L62 _public prototype_ `static void StaticReportCompatibility(uint64 CapabilityMask);`
- L63 _public prototype_ `static TConstArrayView<FName> StaticGetSupportedCapabilities();`
- L65 _public prototype_ `virtual constexpr bool CheckCompatibility(uint64 CapabilityMask) const override;`
- L66 _public prototype_ `virtual void ReportCompatibility(uint64 CapabilityMask) const override;`
- L67 _public prototype_ `virtual TConstArrayView<FName> GetSupportedCapabilities() const override;`
- L69 _public member_ `std::conditional_t<bIsConst, const EnvironmentType&, EnvironmentType&> Environment;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define ArgTypeName(Type, Name) Type Name`
- L14 _macro_ `#define CapabilityStart(Capability, Flags)`
- L16 _macro_ `#define Function0(Capability, Return, Function) virtual Return Function() override;`
- L17 _macro_ `#define Function1(Capability, Return, Function, Arg1) virtual Return Function(ArgTypeName Arg1 ) override;`
- L18 _macro_ `#define Function2(Capability, Return, Function, Arg1, Arg2) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 ) override;`
- L19 _macro_ `#define Function3(Capability, Return, Function, Arg1, Arg2, Arg3) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 ) override;`
- L20 _macro_ `#define Function4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 , ArgTypeName Arg4 ) override;`
- L22 _macro_ `#define ConstFunction0(Capability, Return, Function) virtual Return Function() const override;`
- L23 _macro_ `#define ConstFunction1(Capability, Return, Function, Arg1) virtual Return Function(ArgTypeName Arg1 ) const override;`
- L24 _macro_ `#define ConstFunction2(Capability, Return, Function, Arg1, Arg2) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 ) const override;`
- L25 _macro_ `#define ConstFunction3(Capability, Return, Function, Arg1, Arg2, Arg3) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 ) const override;`
- L26 _macro_ `#define ConstFunction4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 , ArgTypeName Arg4 ) const override;`
- L28 _macro_ `#define CapabilityEnd(Capability)`
- L30 _macro_ `#define DeprecatedFunction(Version, Msg) UE_DEPRECATED(Version, Msg)`
- L32 _macro_ `#define WithWrappers 1`
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace Editor` (scope `UE`)
- L34 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L34 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryContextImplementation.inl` (Public)


#### struct `UE::Editor::DataStorage::Queries::Private::FindImplementationType`  
`template<ContextCapability RequestedCapability, typename... ImplementationTypes> struct FindImplementationType`  
_L13-16_
- L15 _public typedef_ `using Type = void;`
- L20 _public typedef_ `using Type = std::conditional_t< std::is_base_of_v<ImplementsContextCapability<RequestedCapability>, ImplementationType>, ImplementationType, typename FindImplementationType<RequestedCapability, ImplementationTypes...>::Type >;`

#### struct `UE::Editor::DataStorage::Queries::Private::FindImplementationType`  
`template<ContextCapability RequestedCapability, typename ImplementationType, typename... ImplementationTypes> struct FindImplementationType<RequestedCapability, ImplementationType, ImplementationTypes...>`  
_L19-25_
- L15 _public typedef_ `using Type = void;`
- L20 _public typedef_ `using Type = std::conditional_t< std::is_base_of_v<ImplementsContextCapability<RequestedCapability>, ImplementationType>, ImplementationType, typename FindImplementationType<RequestedCapability, ImplementationTypes...>::Type >;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L8 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L10 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage::Queries`)
- L28 _typedef_ `template<ContextCapability RequestedCapability, typename... ImplementationTypes> using ImplementationType = typename FindImplementationType<RequestedCapability, ImplementationTypes...>::Type;` (scope `UE::Editor::DataStorage::Queries::Private`)
- L32 _function_ `template<bool bIsConst, typename EnvironmentType, typename... ImplementationTypes> TQueryContextImpl<bIsConst, EnvironmentType, ImplementationTypes...>::TQueryContextImpl(EnvironmentType& Environment) : Environment(Environment)` (scope `UE::Editor::DataStorage::Queries::TQueryContextImpl`)
- L38 _function_ `template<bool bIsConst, typename EnvironmentType, typename... ImplementationTypes> constexpr uint64 TQueryContextImpl<bIsConst, EnvironmentType, ImplementationTypes...>::GetCapabilityMask()` (scope `UE::Editor::DataStorage::Queries::TQueryContextImpl`)
- L45 _function_ `template<bool bIsConst, typename EnvironmentType, typename... ImplementationTypes> template<ContextCapability RequestedCapability> constexpr bool TQueryContextImpl<bIsConst, EnvironmentType, ImplementationTypes...>::SupportsCapability()` (scope `UE::Editor::DataStorage::Queries::TQueryContextImpl`)
- L51 _function_ `template<bool bIsConst, typename EnvironmentType, typename... ImplementationTypes> bool TQueryContextImpl<bIsConst, EnvironmentType, ImplementationTypes...>::SupportsCapability(const FName& Capability)` (scope `UE::Editor::DataStorage::Queries::TQueryContextImpl`)
- L57 _function_ `template<bool bIsConst, typename EnvironmentType, typename... ImplementationTypes> constexpr bool TQueryContextImpl<bIsConst, EnvironmentType, ImplementationTypes...>::SupportsCapability(int32 CapabilityId)` (scope `UE::Editor::DataStorage::Queries::TQueryContextImpl`)
- L63 _function_ `template<bool bIsConst, typename EnvironmentType, typename... ImplementationTypes> constexpr bool TQueryContextImpl<bIsConst, EnvironmentType, ImplementationTypes...>::SupportsCapabilities(uint64 CapabilityMask)` (scope `UE::Editor::DataStorage::Queries::TQueryContextImpl`)
- L73 _macro_ `#define ExpandArgPack(...) __VA_ARGS__` — Use a macro for this since it's impossible to do with a template since the function pointer that would be needed might not exist. The macro also has the added benefit that it can print the function name for better reporting. CheckArgs and CallArgs are both parenthesized argument packs. CheckArgs uses lvalue argument names for the requires() expression while CallArgs uses Forward<> for the actual call. Keeping them separate incorrect evaluated requires() as false when Forward<T> produces an rvalue for types that are not move-constructible (e.g. TFunctionRef).
- L74 _macro_ `#define PrependCommaIfNeeded(...) __VA_OPT__(,) __VA_ARGS__`
- L75 _macro_ `#define CallFunction(ConstFunction, Capability, ReturnValue, FunctionName, CheckArgs, CallArgs) \`
- L103 _macro_ `#define ArgTypeName(Type, Name) Type Name`
- L104 _macro_ `#define ArgName(Type, Name) Name`
- L105 _macro_ `#define ForwardArg(Type, Name) Forward< Type >( Name )`
- L107 _macro_ `#define FunctionCommon(ReturnType) \`
- L111 _macro_ `#define CapabilityStart(Capability, Flags)`
- L113 _macro_ `#define Function0(Capability, Return, Function) \`
- L118 _macro_ `#define Function1(Capability, Return, Function, Arg1) \`
- L123 _macro_ `#define Function2(Capability, Return, Function, Arg1, Arg2) \`
- L128 _macro_ `#define Function3(Capability, Return, Function, Arg1, Arg2, Arg3) \`
- L133 _macro_ `#define Function4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4) \`
- L139 _macro_ `#define ConstFunction0(Capability, Return, Function) \`
- L144 _macro_ `#define ConstFunction1(Capability, Return, Function, Arg1) \`
- L149 _macro_ `#define ConstFunction2(Capability, Return, Function, Arg1, Arg2) \`
- L154 _macro_ `#define ConstFunction3(Capability, Return, Function, Arg1, Arg2, Arg3) \`
- L159 _macro_ `#define ConstFunction4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4) \`
- L165 _macro_ `#define CapabilityEnd(Capability)`
- L167 _macro_ `#define DeprecatedFunction(Version, Msg)`
- L196 _function_ `template<bool bIsConst, typename EnvironmentType, typename... ImplementationTypes> void TQueryContextImpl<bIsConst, EnvironmentType, ImplementationTypes...>::StaticReportCompatibility(uint64 CapabilityMask)` (scope `UE::Editor::DataStorage::Queries::TQueryContextImpl`)
- L225 _function_ `template<bool bIsConst, typename EnvironmentType, typename... ImplementationTypes> TConstArrayView<FName> TQueryContextImpl<bIsConst, EnvironmentType, ImplementationTypes...>::StaticGetSupportedCapabilities()` (scope `UE::Editor::DataStorage::Queries::TQueryContextImpl`)
- L235 _function_ `template<bool bIsConst, typename EnvironmentType, typename... ImplementationTypes> constexpr bool TQueryContextImpl<bIsConst, EnvironmentType, ImplementationTypes...>::CheckCompatibility(uint64 CapabilityMask) const` (scope `UE::Editor::DataStorage::Queries::TQueryContextImpl`)
- L241 _function_ `template<bool bIsConst, typename EnvironmentType, typename... ImplementationTypes> void TQueryContextImpl<bIsConst, EnvironmentType, ImplementationTypes...>::ReportCompatibility(uint64 CapabilityMask) const` (scope `UE::Editor::DataStorage::Queries::TQueryContextImpl`)
- L247 _function_ `template<bool bIsConst, typename EnvironmentType, typename... ImplementationTypes> TConstArrayView<FName> TQueryContextImpl<bIsConst, EnvironmentType, ImplementationTypes...>::GetSupportedCapabilities() const` (scope `UE::Editor::DataStorage::Queries::TQueryContextImpl`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryContract.h` (Public)


#### struct `UE::Editor::DataStorage::Queries::Private::IContextContractCombinerImpl`  
`template<template<typename> typename Base, template<typename> typename... Bases> struct IContextContractCombinerImpl : Base<IContextContractCombinerImpl<Bases>...>`  
_L13-16_
- inherits: `Base<IContextContractCombinerImpl<Bases>...>`
- L15 _public prototype_ `virtual ~IContextContractCombinerImpl() override = default;`

#### struct `UE::Editor::DataStorage::Queries::Private::IContextContractCombinerImpl`  
`template<template<typename> typename Base> struct IContextContractCombinerImpl<Base> : Base<IContextCapability>`  
_L19-22_
- inherits: `Base<IContextCapability>`
- L15 _public prototype_ `virtual ~IContextContractCombinerImpl() override = default;`

#### struct `UE::Editor::DataStorage::Queries::Private::IContextContractCombiner`  
`template<template<typename> typename... Bases> struct IContextContractCombiner : IContextContractCombinerImpl<Bases>...`  
_L25-141_
- inherits: `IContextContractCombinerImpl<Bases>...`
- L27 _public prototype_ `virtual ~IContextContractCombiner() override = default;`
- L33 _private function_ `template<typename Implementation, template<typename> typename Base> static bool ImplementsCapability(const FName& Capability)` — Work around for MSVC struggling to correctly expand fold expressions when providing the implementation for a template with templated types.
- L41 _private function_ `template<typename Implementation, template<typename> typename Base> constexpr static bool ImplementsCapability(int32 CapabilityId)`
- L49 _public function_ `static FName GetCapabilityName(int32 CapabilityId)`
- L57 _public function_ `template<typename Implementation, ContextCapability RequestedCapability> constexpr static bool SupportsCapability()`
- L63 _public function_ `template<typename Implementation> static bool SupportsCapability(const FName& Capability)`
- L69 _public function_ `template<typename Implementation> constexpr static bool SupportsCapability(int32 CapabilityId)`
- L75 _public function_ `template<typename Implementation> constexpr static int32 CountSupportedCapabilities()`
- L81 _public function_ `template<typename Implementation> static TConstArrayView<FName> GetSupportedCapabilityNameList()`
- L105 _public function_ `template<typename Implementation> static TConstArrayView<int32> GetSupportedCapabilityIdList()`
- L129 _public function_ `template<typename Implementation> static constexpr uint64 GetSupportedCapabilityMask()`

#### struct `UE::Editor::DataStorage::Queries::Private::IPreContextContractCombiner`  
`template<typename, template<typename> typename... Bases> struct IPreContextContractCombiner : IContextContractCombiner<Bases...>`  
_L145-148_
- inherits: `IContextContractCombiner<Bases...>`
- desc: Used to remove the first template argument as that's a placeholder to allow the X-macros to work with the template.
- L147 _public prototype_ `virtual ~IPreContextContractCombiner() override = default;`

#### struct `UE::Editor::DataStorage::Queries::IContextContract`  
`struct IContextContract : Private::IPreContextContractCombiner<int #include "Elements/Framework/TypedElementQueryCapabilities.inl" >`  
_L174-197_
- inherits: `Private::IPreContextContractCombiner<int>`
- desc: Contract between context and implementation to be able to communicate. The contract contains all functions for all capabilities that are available. Based on the supported capabilities an implementation may opt to only partially implement the contract, with the remaining functions asserting. On the opposite side a context may restrict what functions on the contract can be called based on the requested capabilities. Through the query function the capabilities on both sides are kept aligned, resulting in no function on the contract being callable if they're not implemented.
- L178 _public prototype_ `virtual ~IContextContract() override = default;`
- L180 _public prototype_ `virtual bool constexpr CheckCompatibility(uint64 CapabilityMask) const = 0;`
- L182 _public function_ `template<ContextCapability... Capabilities> constexpr bool CheckCompatibility() const`
- L188 _public prototype_ `virtual void ReportCompatibility(uint64 CapabilityMask) const = 0;`
- L190 _public function_ `template<ContextCapability... Capabilities> void ReportCompatibility() const`
- L196 _public prototype_ `virtual TConstArrayView<FName> GetSupportedCapabilities() const = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L8 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L10 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage::Queries`)
- L84 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::IContextContractCombiner::GetSupportedCapabilityNameList`)
- L92 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::IContextContractCombiner::GetSupportedCapabilityNameList::__anon801e2b270102`)
- L108 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::IContextContractCombiner::GetSupportedCapabilityIdList`)
- L116 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::IContextContractCombiner::GetSupportedCapabilityIdList::__anon801e2b270302`)
- L133 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::IContextContractCombiner::GetSupportedCapabilityMask`)
- L151 _macro_ `#define Function0(Capability, Return, Function)`
- L152 _macro_ `#define Function1(Capability, Return, Function, Arg1)`
- L153 _macro_ `#define Function2(Capability, Return, Function, Arg1, Arg2)`
- L154 _macro_ `#define Function3(Capability, Return, Function, Arg1, Arg2, Arg3)`
- L155 _macro_ `#define Function4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4)`
- L156 _macro_ `#define ConstFunction0(Capability, Return, Function)`
- L157 _macro_ `#define ConstFunction1(Capability, Return, Function, Arg1)`
- L158 _macro_ `#define ConstFunction2(Capability, Return, Function, Arg1, Arg2)`
- L159 _macro_ `#define ConstFunction3(Capability, Return, Function, Arg1, Arg2, Arg3)`
- L160 _macro_ `#define ConstFunction4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4)`
- L162 _macro_ `#define DeprecatedFunction(Version, Msg)`
- L163 _macro_ `#define CapabilityStart(Capability, Flags) , I##Capability`
- L164 _macro_ `#define CapabilityEnd(Capability)`

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryFunctionArgumentTypes.h` (Public)


#### enum `UE::Editor::DataStorage::Queries::EFlowControl`  
`enum class EFlowControl`  
_L32-36_
- desc: Optional argument that allows controlling the flow of the query callback. This can be used to early out if for example a searched for value is found or if the number of processed rows has reached a predetermined limit.
- L34 _public enumerator_ `Continue`
- L35 _public enumerator_ `Break` — Continue,   Continue processing with the next row/batch.

#### struct `UE::Editor::DataStorage::Queries::TResult`  
`template<typename ResultType> struct TResult`  
_L46-49_
- desc: Functions that return anything other than void need to provide an interface to collect results into. It'll be up to the implementation to determine what to do with the results, such as track each registered value or accumulate all results together. Query Callback functions that operate in single mode can return the result type from the function and the result will automatically be added. Query Callback functions that work in batch mode require having a TResult<...>& argument where results are written to.
- L48 _public prototype_ `virtual void Add(RowHandle Row, ResultType ResultValue) = 0;`

#### struct `UE::Editor::DataStorage::Queries::TResult`  
`template<> struct TResult<void>`  
_L50-50_
- desc: Used as a placeholder for internal use.
- L48 _public prototype_ `virtual void Add(RowHandle Row, ResultType ResultValue) = 0;`

#### class `UE::Editor::DataStorage::Queries::TBatch`  
`template<typename T> class TBatch`  
_L59-80_
- desc: Storage for batch of objects used in a query. Batches provide the following guarantees: - Contiguous in memory up to the number of entries in the batch. - All values apply to the same table.
- L65 _public prototype_ `TBatch() = default;`
- L68 _public function_ `TArrayView<T> GetView(int32 BatchSize)` — Provides direct access to the stored objects.
- L71 _public function_ `T* GetData()` — Returns a pointer to the stored column.
- L73 _public function_ `const T* GetData() const` — Returns a pointer to the stored column.
- L76 _private function_ `TBatch(T* Values) : Values(Values)`
- L77 _private function_ `TBatch& operator=(T* InValues)`
- L79 _private member_ `T* Values = nullptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L8 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L21 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage::Queries`)
- L83 _typedef_ `template<typename T> using TConstBatch = TBatch<const T>;` (scope `UE::Editor::DataStorage::Queries`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryFunctionArguments.h` (Public)


#### enum `UE::Editor::DataStorage::Queries::Private::EArgumentFlags`  
`enum class EArgumentFlags`  
_L23-35_
- L25 _public enumerator_ `IsConst = 1 << 0` — Indicates the data is immutable.
- L26 _public enumerator_ `IsMutable = 1 << 1` — Indicates that the data can change.
- L27 _public enumerator_ `SingleArgument = 1 << 2` — The argument can be used when a single row is being processed.
- L28 _public enumerator_ `BatchArgument = 1 << 3` — The argument can be used when a batch of rows is being processed.
- L30 _public enumerator_ `Type_Result = 1 << 4` — The argument is used to pass back results.
- L31 _public enumerator_ `Type_Context = 1 << 5` — The argument contains contextual information about the current row or batch.
- L32 _public enumerator_ `Type_RowHandle = 1 << 6` — The argument stores a row handle.
- L33 _public enumerator_ `Type_Column = 1 << 7` — The argument stores a column, including data columns and tag columns.
- L34 _public enumerator_ `Type_FlowControl = 1 << 8` — The argument can be used to control the next iteration step, including stopping work.

#### struct `UE::Editor::DataStorage::Queries::Private::TPointerForwarder`  
`template<typename T> struct TPointerForwarder`  
_L40-50_
- desc: Wrapper around a pointer to act as a reference.
- L42 _public prototype_ `TPointerForwarder() = default;`
- L43 _public function_ `TPointerForwarder(T* Value) : Value(Value)`
- L44 _public function_ `TPointerForwarder& operator=(T* InValue)`
- L46 _public function_ `operator T& () const`
- L47 _public function_ `void Increment()`
- L49 _public member_ `T* Value = nullptr;`

#### struct `UE::Editor::DataStorage::Queries::Private::TArgument`  
`template<typename T> struct TArgument`  
_L54-57_
- desc: Base descriptor for query callback function arguments. Not directly usable and requires specializations.
- L63 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags(0);`
- L64 _public typedef_ `using BaseType = void;`
- L65 _public typedef_ `using ArgumentType = void;`
- L66 _public typedef_ `using ColumnType = void;`
- L67 _public typedef_ `using PointerCastType = void;`
- L90 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_Result;`
- L92 _public typedef_ `using BaseType = typename ResultTypeInfo<FoundationalType<T>>::BaseType;`
- L93 _public typedef_ `using ArgumentType = TPointerForwarder<FoundationalType<T>>;`
- L95 _public typedef_ `using PointerCastType = void*;`
- L104 _public typedef_ `using BaseType = FoundationalType<T>;`
- L105 _public typedef_ `using ContextCapabilities = BaseType::Capabilities;`
- L107 _public member_ `constexpr static EArgumentFlags Flags = (ContextCapabilities::bIsSingle ? EArgumentFlags::SingleArgument : EArgumentFlags(0)) | (ContextCapabilities::bIsBatch ? EArgumentFlags::BatchArgument : EArgumentFlags(0)) | (std::is_base_of_v<FConstQueryContext, BaseType> ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Context;`
- L112 _public typedef_ `using ArgumentType = BaseType;` — Take by value because the context is a forwarder that only stores a single pointer.
- L124 _public member_ `static constexpr bool bIsConst = std::is_const_v<UnreferencedType<T>>;`
- L126 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L131 _public typedef_ `using ArgumentType = TPointerForwarder<UnreferencedType<T>>;`
- L132 _public typedef_ `using ColumnType = BaseType;`
- L133 _public typedef_ `using PointerCastType = std::conditional_t<bIsConst, const BaseType*, BaseType*>;`
- L142 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::BatchArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L146 _public typedef_ `using BaseType = T;`
- L147 _public typedef_ `using ArgumentType = TBatch<T>;`
- L159 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_FlowControl;`
- L162 _public typedef_ `using ArgumentType = TPointerForwarder<BaseType>;`
- L164 _public typedef_ `using PointerCastType = BaseType*;`

#### struct `UE::Editor::DataStorage::Queries::Private::TArgument`  
`template<> struct TArgument<void>`  
_L61-68_
- desc: Void type (used as a placeholder)
- L63 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags(0);`
- L64 _public typedef_ `using BaseType = void;`
- L65 _public typedef_ `using ArgumentType = void;`
- L66 _public typedef_ `using ColumnType = void;`
- L67 _public typedef_ `using PointerCastType = void;`
- L90 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_Result;`
- L92 _public typedef_ `using BaseType = typename ResultTypeInfo<FoundationalType<T>>::BaseType;`
- L93 _public typedef_ `using ArgumentType = TPointerForwarder<FoundationalType<T>>;`
- L95 _public typedef_ `using PointerCastType = void*;`
- L104 _public typedef_ `using BaseType = FoundationalType<T>;`
- L105 _public typedef_ `using ContextCapabilities = BaseType::Capabilities;`
- L107 _public member_ `constexpr static EArgumentFlags Flags = (ContextCapabilities::bIsSingle ? EArgumentFlags::SingleArgument : EArgumentFlags(0)) | (ContextCapabilities::bIsBatch ? EArgumentFlags::BatchArgument : EArgumentFlags(0)) | (std::is_base_of_v<FConstQueryContext, BaseType> ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Context;`
- L112 _public typedef_ `using ArgumentType = BaseType;` — Take by value because the context is a forwarder that only stores a single pointer.
- L124 _public member_ `static constexpr bool bIsConst = std::is_const_v<UnreferencedType<T>>;`
- L126 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L131 _public typedef_ `using ArgumentType = TPointerForwarder<UnreferencedType<T>>;`
- L132 _public typedef_ `using ColumnType = BaseType;`
- L133 _public typedef_ `using PointerCastType = std::conditional_t<bIsConst, const BaseType*, BaseType*>;`
- L142 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::BatchArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L146 _public typedef_ `using BaseType = T;`
- L147 _public typedef_ `using ArgumentType = TBatch<T>;`
- L159 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_FlowControl;`
- L162 _public typedef_ `using ArgumentType = TPointerForwarder<BaseType>;`
- L164 _public typedef_ `using PointerCastType = BaseType*;`

#### struct `UE::Editor::DataStorage::Queries::Private::ResultTypeInfo`  
`template<typename T> struct ResultTypeInfo`  
_L72-76_
- desc: Result type
- L74 _public member_ `static constexpr bool bIsValid = false;`
- L75 _public typedef_ `using BaseType = void;`
- L80 _public member_ `static constexpr bool bIsValid = true;`
- L81 _public typedef_ `using BaseType = T;`

#### struct `UE::Editor::DataStorage::Queries::Private::ResultTypeInfo`  
`template<typename T> struct ResultTypeInfo<TResult<T>>`  
_L78-82_
- L74 _public member_ `static constexpr bool bIsValid = false;`
- L75 _public typedef_ `using BaseType = void;`
- L80 _public member_ `static constexpr bool bIsValid = true;`
- L81 _public typedef_ `using BaseType = T;`

#### struct `UE::Editor::DataStorage::Queries::Private::TArgument`  
`template<typename T> requires ResultTypeInfo<FoundationalType<T>>::bIsValid struct TArgument<T>`  
_L85-96_
- L63 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags(0);`
- L64 _public typedef_ `using BaseType = void;`
- L65 _public typedef_ `using ArgumentType = void;`
- L66 _public typedef_ `using ColumnType = void;`
- L67 _public typedef_ `using PointerCastType = void;`
- L90 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_Result;`
- L92 _public typedef_ `using BaseType = typename ResultTypeInfo<FoundationalType<T>>::BaseType;`
- L93 _public typedef_ `using ArgumentType = TPointerForwarder<FoundationalType<T>>;`
- L95 _public typedef_ `using PointerCastType = void*;`
- L104 _public typedef_ `using BaseType = FoundationalType<T>;`
- L105 _public typedef_ `using ContextCapabilities = BaseType::Capabilities;`
- L107 _public member_ `constexpr static EArgumentFlags Flags = (ContextCapabilities::bIsSingle ? EArgumentFlags::SingleArgument : EArgumentFlags(0)) | (ContextCapabilities::bIsBatch ? EArgumentFlags::BatchArgument : EArgumentFlags(0)) | (std::is_base_of_v<FConstQueryContext, BaseType> ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Context;`
- L112 _public typedef_ `using ArgumentType = BaseType;` — Take by value because the context is a forwarder that only stores a single pointer.
- L124 _public member_ `static constexpr bool bIsConst = std::is_const_v<UnreferencedType<T>>;`
- L126 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L131 _public typedef_ `using ArgumentType = TPointerForwarder<UnreferencedType<T>>;`
- L132 _public typedef_ `using ColumnType = BaseType;`
- L133 _public typedef_ `using PointerCastType = std::conditional_t<bIsConst, const BaseType*, BaseType*>;`
- L142 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::BatchArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L146 _public typedef_ `using BaseType = T;`
- L147 _public typedef_ `using ArgumentType = TBatch<T>;`
- L159 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_FlowControl;`
- L162 _public typedef_ `using ArgumentType = TPointerForwarder<BaseType>;`
- L164 _public typedef_ `using PointerCastType = BaseType*;`

#### struct `UE::Editor::DataStorage::Queries::Private::TArgument`  
`template<typename T> requires ContextType<FoundationalType<T>> struct TArgument<T>`  
_L100-115_
- desc: Context type
- L63 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags(0);`
- L64 _public typedef_ `using BaseType = void;`
- L65 _public typedef_ `using ArgumentType = void;`
- L66 _public typedef_ `using ColumnType = void;`
- L67 _public typedef_ `using PointerCastType = void;`
- L90 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_Result;`
- L92 _public typedef_ `using BaseType = typename ResultTypeInfo<FoundationalType<T>>::BaseType;`
- L93 _public typedef_ `using ArgumentType = TPointerForwarder<FoundationalType<T>>;`
- L95 _public typedef_ `using PointerCastType = void*;`
- L104 _public typedef_ `using BaseType = FoundationalType<T>;`
- L105 _public typedef_ `using ContextCapabilities = BaseType::Capabilities;`
- L107 _public member_ `constexpr static EArgumentFlags Flags = (ContextCapabilities::bIsSingle ? EArgumentFlags::SingleArgument : EArgumentFlags(0)) | (ContextCapabilities::bIsBatch ? EArgumentFlags::BatchArgument : EArgumentFlags(0)) | (std::is_base_of_v<FConstQueryContext, BaseType> ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Context;`
- L112 _public typedef_ `using ArgumentType = BaseType;` — Take by value because the context is a forwarder that only stores a single pointer.
- L124 _public member_ `static constexpr bool bIsConst = std::is_const_v<UnreferencedType<T>>;`
- L126 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L131 _public typedef_ `using ArgumentType = TPointerForwarder<UnreferencedType<T>>;`
- L132 _public typedef_ `using ColumnType = BaseType;`
- L133 _public typedef_ `using PointerCastType = std::conditional_t<bIsConst, const BaseType*, BaseType*>;`
- L142 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::BatchArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L146 _public typedef_ `using BaseType = T;`
- L147 _public typedef_ `using ArgumentType = TBatch<T>;`
- L159 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_FlowControl;`
- L162 _public typedef_ `using ArgumentType = TPointerForwarder<BaseType>;`
- L164 _public typedef_ `using PointerCastType = BaseType*;`

#### struct `UE::Editor::DataStorage::Queries::Private::TArgument`  
`template<typename T> requires TColumnType<FoundationalType<T>> struct TArgument<T>`  
_L119-134_
- desc: Column reference types
- L63 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags(0);`
- L64 _public typedef_ `using BaseType = void;`
- L65 _public typedef_ `using ArgumentType = void;`
- L66 _public typedef_ `using ColumnType = void;`
- L67 _public typedef_ `using PointerCastType = void;`
- L90 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_Result;`
- L92 _public typedef_ `using BaseType = typename ResultTypeInfo<FoundationalType<T>>::BaseType;`
- L93 _public typedef_ `using ArgumentType = TPointerForwarder<FoundationalType<T>>;`
- L95 _public typedef_ `using PointerCastType = void*;`
- L104 _public typedef_ `using BaseType = FoundationalType<T>;`
- L105 _public typedef_ `using ContextCapabilities = BaseType::Capabilities;`
- L107 _public member_ `constexpr static EArgumentFlags Flags = (ContextCapabilities::bIsSingle ? EArgumentFlags::SingleArgument : EArgumentFlags(0)) | (ContextCapabilities::bIsBatch ? EArgumentFlags::BatchArgument : EArgumentFlags(0)) | (std::is_base_of_v<FConstQueryContext, BaseType> ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Context;`
- L112 _public typedef_ `using ArgumentType = BaseType;` — Take by value because the context is a forwarder that only stores a single pointer.
- L124 _public member_ `static constexpr bool bIsConst = std::is_const_v<UnreferencedType<T>>;`
- L126 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L131 _public typedef_ `using ArgumentType = TPointerForwarder<UnreferencedType<T>>;`
- L132 _public typedef_ `using ColumnType = BaseType;`
- L133 _public typedef_ `using PointerCastType = std::conditional_t<bIsConst, const BaseType*, BaseType*>;`
- L142 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::BatchArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L146 _public typedef_ `using BaseType = T;`
- L147 _public typedef_ `using ArgumentType = TBatch<T>;`
- L159 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_FlowControl;`
- L162 _public typedef_ `using ArgumentType = TPointerForwarder<BaseType>;`
- L164 _public typedef_ `using PointerCastType = BaseType*;`

#### struct `UE::Editor::DataStorage::Queries::Private::TArgument`  
`template<typename T> requires TColumnType<T> struct TArgument<TBatch<T>>`  
_L138-150_
- desc: Column batch types
- L63 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags(0);`
- L64 _public typedef_ `using BaseType = void;`
- L65 _public typedef_ `using ArgumentType = void;`
- L66 _public typedef_ `using ColumnType = void;`
- L67 _public typedef_ `using PointerCastType = void;`
- L90 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_Result;`
- L92 _public typedef_ `using BaseType = typename ResultTypeInfo<FoundationalType<T>>::BaseType;`
- L93 _public typedef_ `using ArgumentType = TPointerForwarder<FoundationalType<T>>;`
- L95 _public typedef_ `using PointerCastType = void*;`
- L104 _public typedef_ `using BaseType = FoundationalType<T>;`
- L105 _public typedef_ `using ContextCapabilities = BaseType::Capabilities;`
- L107 _public member_ `constexpr static EArgumentFlags Flags = (ContextCapabilities::bIsSingle ? EArgumentFlags::SingleArgument : EArgumentFlags(0)) | (ContextCapabilities::bIsBatch ? EArgumentFlags::BatchArgument : EArgumentFlags(0)) | (std::is_base_of_v<FConstQueryContext, BaseType> ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Context;`
- L112 _public typedef_ `using ArgumentType = BaseType;` — Take by value because the context is a forwarder that only stores a single pointer.
- L124 _public member_ `static constexpr bool bIsConst = std::is_const_v<UnreferencedType<T>>;`
- L126 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L131 _public typedef_ `using ArgumentType = TPointerForwarder<UnreferencedType<T>>;`
- L132 _public typedef_ `using ColumnType = BaseType;`
- L133 _public typedef_ `using PointerCastType = std::conditional_t<bIsConst, const BaseType*, BaseType*>;`
- L142 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::BatchArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L146 _public typedef_ `using BaseType = T;`
- L147 _public typedef_ `using ArgumentType = TBatch<T>;`
- L159 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_FlowControl;`
- L162 _public typedef_ `using ArgumentType = TPointerForwarder<BaseType>;`
- L164 _public typedef_ `using PointerCastType = BaseType*;`

#### struct `UE::Editor::DataStorage::Queries::Private::TArgument`  
`template<typename T> requires std::is_same_v<FoundationalType<T>, EFlowControl> struct TArgument<T>`  
_L154-165_
- desc: Flow control
- L63 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags(0);`
- L64 _public typedef_ `using BaseType = void;`
- L65 _public typedef_ `using ArgumentType = void;`
- L66 _public typedef_ `using ColumnType = void;`
- L67 _public typedef_ `using PointerCastType = void;`
- L90 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_Result;`
- L92 _public typedef_ `using BaseType = typename ResultTypeInfo<FoundationalType<T>>::BaseType;`
- L93 _public typedef_ `using ArgumentType = TPointerForwarder<FoundationalType<T>>;`
- L95 _public typedef_ `using PointerCastType = void*;`
- L104 _public typedef_ `using BaseType = FoundationalType<T>;`
- L105 _public typedef_ `using ContextCapabilities = BaseType::Capabilities;`
- L107 _public member_ `constexpr static EArgumentFlags Flags = (ContextCapabilities::bIsSingle ? EArgumentFlags::SingleArgument : EArgumentFlags(0)) | (ContextCapabilities::bIsBatch ? EArgumentFlags::BatchArgument : EArgumentFlags(0)) | (std::is_base_of_v<FConstQueryContext, BaseType> ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Context;`
- L112 _public typedef_ `using ArgumentType = BaseType;` — Take by value because the context is a forwarder that only stores a single pointer.
- L124 _public member_ `static constexpr bool bIsConst = std::is_const_v<UnreferencedType<T>>;`
- L126 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L131 _public typedef_ `using ArgumentType = TPointerForwarder<UnreferencedType<T>>;`
- L132 _public typedef_ `using ColumnType = BaseType;`
- L133 _public typedef_ `using PointerCastType = std::conditional_t<bIsConst, const BaseType*, BaseType*>;`
- L142 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::BatchArgument | (bIsConst ? EArgumentFlags::IsConst : EArgumentFlags::IsMutable) | EArgumentFlags::Type_Column;`
- L146 _public typedef_ `using BaseType = T;`
- L147 _public typedef_ `using ArgumentType = TBatch<T>;`
- L159 _public member_ `constexpr static EArgumentFlags Flags = EArgumentFlags::SingleArgument | EArgumentFlags::BatchArgument | EArgumentFlags::IsMutable | EArgumentFlags::Type_FlowControl;`
- L162 _public typedef_ `using ArgumentType = TPointerForwarder<BaseType>;`
- L164 _public typedef_ `using PointerCastType = BaseType*;`

#### struct `UE::Editor::DataStorage::Queries::Private::TIndexToArgInfoImpl`  
`template<int32 Index, typename... Args> struct TIndexToArgInfoImpl`  
_L168-168_
- L182 _public typedef_ `using Type = TArgument<void>;`

#### struct `UE::Editor::DataStorage::Queries::Private::TIndexToArgInfoImpl`  
`template<int32 Index, typename Front, typename... Args> struct TIndexToArgInfoImpl<Index, Front, Args...>`  
_L171-177_
- L182 _public typedef_ `using Type = TArgument<void>;`

#### struct `UE::Editor::DataStorage::Queries::Private::TIndexToArgInfoImpl`  
`template<int32 Index> struct TIndexToArgInfoImpl<Index>`  
_L180-183_
- desc: Empty argument list.
- L182 _public typedef_ `using Type = TArgument<void>;`

#### struct `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`  
`template<typename... Args> struct TArgumentInfo`  
_L189-248_
- L193 _private prototype_ `template<EArgumentFlags TypeFlag> constexpr static int32 FirstIndexOfType();`
- L196 _private prototype_ `template<EArgumentFlags Flags> constexpr static int32 CountFlags();`
- L199 _private prototype_ `template<int32 Index, EArgumentFlags Flags> constexpr static bool HasFlags();`
- L202 _private prototype_ `template<EArgumentFlags Flags> static TConstArrayView<const UScriptStruct*> ListColumns();`
- L205 _public member_ `static constexpr bool bIsSingle = (EnumHasAnyFlags(TArgument<Args>::Flags, EArgumentFlags::SingleArgument) && ...);`
- L206 _public member_ `static constexpr bool bIsBatch = (EnumHasAnyFlags(TArgument<Args>::Flags, EArgumentFlags::BatchArgument) && ...);`
- L210 _public typedef_ `using ArgumentList = TTuple<typename TArgument<Args>::ArgumentType...>;`
- L212 _public member_ `constexpr static int32 ResultIndex = FirstIndexOfType<EArgumentFlags::Type_Result>();`
- L213 _public typedef_ `using ResultType = typename TIndexToArgInfo<ResultIndex, Args...>::BaseType;`
- L215 _public prototype_ `template<typename T> static void SetResult(ArgumentList& Arguments, TResult<T>& Result);`
- L216 _public prototype_ `constexpr static int32 CountResults();`
- L218 _public member_ `constexpr static int32 ContextIndex = FirstIndexOfType<EArgumentFlags::Type_Context>();`
- L219 _public typedef_ `using ContextType = typename TIndexToArgInfo<ContextIndex, Args...>::BaseType;`
- L220 _public prototype_ `static void SetContext(ArgumentList& Arguments, IContextContract& Contract);`
- L221 _public prototype_ `static void SetContext(ArgumentList& Arguments, const IContextContract& Contract);`
- L222 _public prototype_ `constexpr static bool IsContextConst();`
- L223 _public prototype_ `constexpr static int32 CountContexts();`
- L225 _public member_ `constexpr static int32 FlowIndex = FirstIndexOfType<EArgumentFlags::Type_FlowControl>();`
- L226 _public prototype_ `static void SetFlowControl(ArgumentList& Arguments, EFlowControl& FlowControl);`
- L227 _public prototype_ `constexpr static int32 CountFlowControls();`
- L229 _public prototype_ `constexpr static int32 CountConstColumns();`
- L230 _public prototype_ `constexpr static int32 CountMutableColumns();`
- L231 _public prototype_ `static TConstArrayView<const UScriptStruct*> ListConstColumns();`
- L232 _public prototype_ `static TConstArrayView<const UScriptStruct*> ListMutableColumns();`
- L233 _public prototype_ `static void SetConstColumns(ArgumentList& Arguments, TConstArrayView<const void*> Columns);`
- L234 _public prototype_ `static void SetMutableColumns(ArgumentList& Arguments, TConstArrayView<void*> Columns);`
- L235 _public prototype_ `static void IncrementColumns(ArgumentList& Arguments);`
- L239 _private prototype_ `template<int32 Index, typename T> static void SetResultUnguarded(ArgumentList& Arguments, TResult<T>& Result);`
- L241 _private prototype_ `template<int32 Index> static void SetContextUnguarded(ArgumentList& Arguments, IContextContract& Contract);`
- L243 _private prototype_ `template<int32 Index> static void SetContextUnguarded(ArgumentList& Arguments, const IContextContract& Contract);`
- L245 _private prototype_ `template<int32 Index> static void SetFlowControlUnguarded(ArgumentList& Arguments, EFlowControl& FlowControl);`
- L247 _private prototype_ `template<typename ArgumentType> static void IncrementColumnUnguarded(ArgumentList& Arguments);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L15 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage::Queries`)
- L18 _typedef_ `template<typename T> using UnreferencedType = std::remove_reference_t<std::remove_pointer_t<T>>;` (scope `UE::Editor::DataStorage::Queries::Private`)
- L20 _typedef_ `template<typename T> using FoundationalType = std::remove_cv_t<UnreferencedType<T>>;` (scope `UE::Editor::DataStorage::Queries::Private`)
- L186 _typedef_ `template<int32 Index, typename... Args> using TIndexToArgInfo = typename TIndexToArgInfoImpl<Index, Args...>::Type;` (scope `UE::Editor::DataStorage::Queries::Private`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryFunctionArguments.inl` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Editor` (scope `UE`)
- L6 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L6 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L6 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage::Queries`)
- L9 _function_ `template<EArgumentFlags TypeFlag, int32 Index> constexpr int32 FirstIndexOfTypeImpl()` (scope `UE::Editor::DataStorage::Queries::Private`)
- L15 _function_ `template<EArgumentFlags TypeFlag, int32 Index, typename Arg, typename... Args> constexpr int32 FirstIndexOfTypeImpl()` (scope `UE::Editor::DataStorage::Queries::Private`)
- L29 _function_ `template<typename... Args> template<EArgumentFlags TypeFlag> constexpr int32 TArgumentInfo<Args...>::FirstIndexOfType()` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L43 _function_ `template<typename... Args> template<EArgumentFlags Flags> constexpr int32 TArgumentInfo<Args...>::CountFlags()` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L50 _function_ `template<typename... Args> template<int32 Index, EArgumentFlags Flags> constexpr bool TArgumentInfo<Args...>::HasFlags()` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L52 _typedef_ `using NthArg = typename TTupleElement<Index, TTuple<Args...>>::Type;` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo::HasFlags`)
- L58 _function_ `template<typename... Args> template<typename T> void TArgumentInfo<Args...>::SetResult(ArgumentList& Arguments, TResult<T>& Result)` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L67 _function_ `template<typename... Args> constexpr int32 TArgumentInfo<Args...>::CountResults()` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L73 _function_ `template<typename... Args> void TArgumentInfo<Args...>::SetContext(ArgumentList& Arguments, IContextContract& Contract)` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L82 _function_ `template<typename... Args> void TArgumentInfo<Args...>::SetContext(ArgumentList& Arguments, const IContextContract& Contract)` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L91 _function_ `template<typename... Args> constexpr bool TArgumentInfo<Args...>::IsContextConst()` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L104 _function_ `template<typename... Args> constexpr int32 TArgumentInfo<Args...>::CountContexts()` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L110 _function_ `template<typename... Args> void TArgumentInfo<Args...>::SetFlowControl(ArgumentList& Arguments, EFlowControl& FlowControl)` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L119 _function_ `template<typename... Args> constexpr int32 TArgumentInfo<Args...>::CountFlowControls()` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L125 _function_ `template<typename... Args> constexpr int32 TArgumentInfo<Args...>::CountConstColumns()` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L131 _function_ `template<typename... Args> constexpr int32 TArgumentInfo<Args...>::CountMutableColumns()` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L138 _function_ `template<typename... Args> template<EArgumentFlags Flags> TConstArrayView<const UScriptStruct*> TArgumentInfo<Args...>::ListColumns()` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L145 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo::ListColumns`)
- L150 _function_ `` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo::ListColumns::__anonc6ed47000102`)
- L169 _function_ `template<typename... Args> TConstArrayView<const UScriptStruct*> TArgumentInfo<Args...>::ListConstColumns()` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L175 _function_ `template<typename... Args> TConstArrayView<const UScriptStruct*> TArgumentInfo<Args...>::ListMutableColumns()` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L181 _function_ `template<typename... Args> void TArgumentInfo<Args...>::SetConstColumns(ArgumentList& Arguments, TConstArrayView<const void*> Columns)` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L184 _function_ `([&]{ using ArgumentType = TArgument<Args>; if constexpr (EnumHasAllFlags(ArgumentType::Flags, EArgumentFlags::IsConst | EArgumentFlags::Type_Column)) { Arguments.template Get<typename ArgumentType::ArgumentType>() = static_cast<typename ArgumentType::PointerCastType>(*ColumnIt++); } }(), ...);` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo::SetConstColumns`)
- L185 _typedef_ `using ArgumentType = TArgument<Args>;` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo::SetConstColumns::__anonc6ed47000302`)
- L194 _function_ `template<typename... Args> void TArgumentInfo<Args...>::SetMutableColumns(ArgumentList& Arguments, TConstArrayView<void*> Columns)` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L197 _function_ `([&]{ using ArgumentType = TArgument<Args>; if constexpr (EnumHasAllFlags(ArgumentType::Flags, EArgumentFlags::IsMutable | EArgumentFlags::Type_Column)) { Arguments.template Get<typename ArgumentType::ArgumentType>() = static_cast<typename ArgumentType::PointerCastType>(*ColumnIt++); } }(), ...);` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo::SetMutableColumns`)
- L198 _typedef_ `using ArgumentType = TArgument<Args>;` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo::SetMutableColumns::__anonc6ed47000402`)
- L207 _function_ `template<typename... Args> void TArgumentInfo<Args...>::IncrementColumns(ArgumentList& Arguments)` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L209 _function_ `([&] { using ArgumentType = TArgument<Args>; if constexpr (EnumHasAllFlags(ArgumentType::Flags, EArgumentFlags::SingleArgument | EArgumentFlags::Type_Column)) { IncrementColumnUnguarded<typename ArgumentType::ArgumentType>(Arguments); } }(), ...);` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo::IncrementColumns`)
- L210 _typedef_ `using ArgumentType = TArgument<Args>;` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo::IncrementColumns::__anonc6ed47000502`)
- L220 _function_ `template<typename... Args> template<int32 Index, typename T> void TArgumentInfo<Args...>::SetResultUnguarded(ArgumentList& Arguments, TResult<T>& Result)` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L229 _function_ `template<typename... Args> template<int32 Index> void TArgumentInfo<Args...>::SetContextUnguarded(ArgumentList& Arguments, IContextContract& Contract)` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L236 _function_ `template<typename... Args> template<int32 Index> void TArgumentInfo<Args...>::SetContextUnguarded(ArgumentList& Arguments, const IContextContract& Contract)` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L243 _function_ `template<typename... Args> template<int32 Index> void TArgumentInfo<Args...>::SetFlowControlUnguarded(ArgumentList& Arguments, EFlowControl& FlowControl)` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)
- L250 _function_ `template<typename... Args> template<typename ArgumentType> void TArgumentInfo<Args...>::IncrementColumnUnguarded(ArgumentList& Arguments)` (scope `UE::Editor::DataStorage::Queries::Private::TArgumentInfo`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryFunctions.h` (Public)


#### struct `UE::Editor::DataStorage::Queries::IQueryFunctionResponse`  
`struct IQueryFunctionResponse`  
_L20-30_
- L22 _public prototype_ `virtual ~IQueryFunctionResponse() = default;`
- L24 _public prototype_ `virtual FRowHandleArrayView GetBatchRows() const = 0;`
- L25 _public prototype_ `virtual void GetConstColumns(TArrayView<const void*> ColumnsData, TConstArrayView<const UScriptStruct*> ColumnTypes) const = 0;`
- L27 _public prototype_ `virtual void GetMutableColumns(TArrayView<void*> ColumnsData, TConstArrayView<const UScriptStruct*> ColumnTypes) = 0;` — Not used in const queries.
- L29 _public prototype_ `virtual void SetCurrentRow(RowHandle Row) = 0;` — Only called when a batch is broken up in individual rows for the current active call.

#### enum `UE::Editor::DataStorage::Queries::EFunctionCallConfig`  
`enum class EFunctionCallConfig`  
_L32-43_
- L34 _public enumerator_ `None = 0`
- L36 _public enumerator_ `VerifyCapabilityCompatibility = 1 << 0` — Verifies if the function is compatible with the provided context.
- L38 _public enumerator_ `ReportCapabilityCompatibility = 1 << 1` — If the function is not compatible with the provided context it will assert. Requires `VerifyCapabilityCompatibility`.
- L40 _public enumerator_ `VerifyColumns = 1 << 2` — If not all columns could be retrieved, return the default value for the return type, if applicable, and don't call the function.
- L42 _public enumerator_ `ContinueOnIncompleteRow = 1 << 3` — Continues to evaluate all input when Verify Columns fails. Requires `VerifyColumns`.

#### class `UE::Editor::DataStorage::Queries::TQueryFunctionBase`  
`template<typename ReturnType, bool bIsConst> class TQueryFunctionBase`  
_L48-69_
- desc: Storage for a function that can be used as part of a query.
- L51 _public typedef_ `using ContractType = std::conditional_t<bIsConst, const IContextContract&, IContextContract&>;`
- L52 _public typedef_ `using FunctionResponseType = IQueryFunctionResponse&;`
- L53 _public typedef_ `using FunctionSpecializationCallback = std::conditional_t<bIsConst, bool(*)(FunctionResponseType Response, TArrayView<const void*> ConstColumns), bool(*)(FunctionResponseType Response, TArrayView<const void*> ConstColumns, TArrayView<void*> MutableColumns)>;`
- L57 _public typedef_ `using WrapperFunctionType = TFunction<EFlowControl(TResult<ReturnType>& Result, ContractType Contract, FunctionResponseType Response, FunctionSpecializationCallback Specialization, EFlowControl IncompleteRowFlowControl)>;`
- L60 _public member_ `TConstArrayView<const UScriptStruct*> ConstColumnTypes;`
- L61 _public member_ `TConstArrayView<const UScriptStruct*> MutableColumnTypes;`
- L62 _public member_ `WrapperFunctionType Function;`
- L63 _public member_ `uint64 CapabilityMask = 0;`
- L64 _public member_ `bool bIsSingleRowProcessor = false;`
- L68 _protected prototype_ `template<EFunctionCallConfig Config> EFlowControl CallInternal(TResult<ReturnType>& Result, ContractType Contract, FunctionResponseType Response) const;`

#### class `UE::Editor::DataStorage::Queries::TQueryFunction`  
`template<typename ReturnType> class TQueryFunction final : public TQueryFunctionBase<ReturnType, false>`  
_L72-87_
- inherits: `TQueryFunctionBase<ReturnType,false>`
- L78 _public function_ `template<EFunctionCallConfig Config> EFlowControl Call(TResult<ReturnType>& Result, IContextContract& Contract, FunctionResponseType Response) const`
- L83 _public function_ `EFlowControl Call(TResult<ReturnType>& Result, IContextContract& Contract, FunctionResponseType Response) const`
- L96 _public function_ `template<EFunctionCallConfig Config> EFlowControl Call(IContextContract& Contract, FunctionResponseType Response) const`
- L102 _public function_ `EFlowControl Call(IContextContract& Contract, FunctionResponseType Response) const`

#### class `UE::Editor::DataStorage::Queries::TQueryFunction`  
`template<> class TQueryFunction<void> final : public TQueryFunctionBase<void, false>`  
_L90-106_
- inherits: `TQueryFunctionBase<void,false>`
- L78 _public function_ `template<EFunctionCallConfig Config> EFlowControl Call(TResult<ReturnType>& Result, IContextContract& Contract, FunctionResponseType Response) const`
- L83 _public function_ `EFlowControl Call(TResult<ReturnType>& Result, IContextContract& Contract, FunctionResponseType Response) const`
- L96 _public function_ `template<EFunctionCallConfig Config> EFlowControl Call(IContextContract& Contract, FunctionResponseType Response) const`
- L102 _public function_ `EFlowControl Call(IContextContract& Contract, FunctionResponseType Response) const`

#### class `UE::Editor::DataStorage::Queries::TConstQueryFunction`  
`template<typename ReturnType> class TConstQueryFunction final : public TQueryFunctionBase<ReturnType, true>`  
_L109-124_
- inherits: `TQueryFunctionBase<ReturnType,true>`
- L115 _public function_ `template<EFunctionCallConfig Config> EFlowControl Call(TResult<ReturnType>& Result, const IContextContract& Contract, FunctionResponseType Response) const`
- L120 _public function_ `EFlowControl Call(TResult<ReturnType>& Result, const IContextContract& Contract, FunctionResponseType Response) const`
- L133 _public function_ `template<EFunctionCallConfig Config> EFlowControl Call(const IContextContract& Contract, FunctionResponseType Response) const`
- L139 _public function_ `EFlowControl Call(const IContextContract& Contract, FunctionResponseType Response) const`

#### class `UE::Editor::DataStorage::Queries::TConstQueryFunction`  
`template<> class TConstQueryFunction<void> final : public TQueryFunctionBase<void, true>`  
_L127-143_
- inherits: `TQueryFunctionBase<void,true>`
- L115 _public function_ `template<EFunctionCallConfig Config> EFlowControl Call(TResult<ReturnType>& Result, const IContextContract& Contract, FunctionResponseType Response) const`
- L120 _public function_ `EFlowControl Call(TResult<ReturnType>& Result, const IContextContract& Contract, FunctionResponseType Response) const`
- L133 _public function_ `template<EFunctionCallConfig Config> EFlowControl Call(const IContextContract& Contract, FunctionResponseType Response) const`
- L139 _public function_ `EFlowControl Call(const IContextContract& Contract, FunctionResponseType Response) const`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L16 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L44 _prototype_ `ENUM_CLASS_FLAGS(EFunctionCallConfig);` (scope `UE::Editor::DataStorage::Queries`)
- L146 _prototype_ `template<typename Return, FunctionType Function> TQueryFunction<Return> BuildQueryFunction(Function&& Callback);` (scope `UE::Editor::DataStorage::Queries`)
- L149 _prototype_ `template<typename Return, FunctionType Function> TConstQueryFunction<Return> BuildConstQueryFunction(Function&& Callback);` (scope `UE::Editor::DataStorage::Queries`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementQueryFunctions.inl` (Public)


#### struct `UE::Editor::DataStorage::Queries::Private::TFunctionInfoImpl`  
`template<typename T> struct TFunctionInfoImpl`  
_L19-25_
- L21 _public typedef_ `using ArgumentInfo = TArgumentInfo<>;`
- L23 _public member_ `static constexpr bool bIsValidQueryFunction = false;`
- L24 _public typedef_ `using ReturnType = void;`
- L30 _public typedef_ `using ArgumentInfo = TArgumentInfo<Args...>;`
- L32 _public member_ `static constexpr bool bIsValidQueryFunction = true;`
- L33 _public typedef_ `using ReturnType = Return;`

#### struct `UE::Editor::DataStorage::Queries::Private::TFunctionInfoImpl`  
`template<typename Return, typename... Args> struct TFunctionInfoImpl<Return(*)(Args...)>`  
_L28-34_
- L21 _public typedef_ `using ArgumentInfo = TArgumentInfo<>;`
- L23 _public member_ `static constexpr bool bIsValidQueryFunction = false;`
- L24 _public typedef_ `using ReturnType = void;`
- L30 _public typedef_ `using ArgumentInfo = TArgumentInfo<Args...>;`
- L32 _public member_ `static constexpr bool bIsValidQueryFunction = true;`
- L33 _public typedef_ `using ReturnType = Return;`

#### struct `UE::Editor::DataStorage::Queries::Private::TFunctionInfoImpl`  
`template<typename Class, typename Return, typename... Args> struct TFunctionInfoImpl<Return(Class::*)(Args...)>`  
_L37-43_
- L21 _public typedef_ `using ArgumentInfo = TArgumentInfo<>;`
- L23 _public member_ `static constexpr bool bIsValidQueryFunction = false;`
- L24 _public typedef_ `using ReturnType = void;`
- L30 _public typedef_ `using ArgumentInfo = TArgumentInfo<Args...>;`
- L32 _public member_ `static constexpr bool bIsValidQueryFunction = true;`
- L33 _public typedef_ `using ReturnType = Return;`

#### struct `UE::Editor::DataStorage::Queries::Private::TFunctionInfoImpl`  
`template<typename Class, typename Return, typename... Args> struct TFunctionInfoImpl<Return(Class::*)(Args...) const>`  
_L46-52_
- L21 _public typedef_ `using ArgumentInfo = TArgumentInfo<>;`
- L23 _public member_ `static constexpr bool bIsValidQueryFunction = false;`
- L24 _public typedef_ `using ReturnType = void;`
- L30 _public typedef_ `using ArgumentInfo = TArgumentInfo<Args...>;`
- L32 _public member_ `static constexpr bool bIsValidQueryFunction = true;`
- L33 _public typedef_ `using ReturnType = Return;`

#### struct `UE::Editor::DataStorage::Queries::Private::TFunctionInfoSelection`  
`template<bool IsFunctor, typename FunctionType> struct TFunctionInfoSelection`  
_L55-55_
- L60 _public typedef_ `using Type = TFunctionInfoImpl<decltype(&FunctionType::operator())>;`
- L66 _public typedef_ `using Type = TFunctionInfoImpl<FunctionType>;`

#### struct `UE::Editor::DataStorage::Queries::Private::TFunctionInfoSelection`  
`template<typename FunctionType> struct TFunctionInfoSelection<true, FunctionType>`  
_L58-61_
- L60 _public typedef_ `using Type = TFunctionInfoImpl<decltype(&FunctionType::operator())>;`
- L66 _public typedef_ `using Type = TFunctionInfoImpl<FunctionType>;`

#### struct `UE::Editor::DataStorage::Queries::Private::TFunctionInfoSelection`  
`template<typename FunctionType> struct TFunctionInfoSelection<false, FunctionType>`  
_L64-67_
- L60 _public typedef_ `using Type = TFunctionInfoImpl<decltype(&FunctionType::operator())>;`
- L66 _public typedef_ `using Type = TFunctionInfoImpl<FunctionType>;`

#### struct `UE::Editor::DataStorage::Queries::Private::TFunctionInfo`  
`template<typename FunctionType> struct TFunctionInfo`  
_L70-166_
- L72 _public typedef_ `using Base = TFunctionInfoSelection<FunctorType<FunctionType>, FunctionType>::Type;`
- L74 _public typedef_ `using ReturnType = typename Base::ReturnType;`
- L75 _public typedef_ `using ArgumentInfo = typename Base::ArgumentInfo;`
- L76 _public typedef_ `using ContextType = typename ArgumentInfo::ContextType;`
- L78 _public member_ `static constexpr bool bIsValidQueryFunction = Base::bIsValidQueryFunction && (ArgumentInfo::bIsSingle || ArgumentInfo::bIsBatch);`
- L81 _public member_ `static constexpr bool bIsSingleRowProcessor = ArgumentInfo::bIsSingle;`
- L84 _public function_ `template<typename RequestedReturnType, bool bIsConst> static constexpr void StaticValidation()`
- L137 _public function_ `template<typename RequestedReturnType> static constexpr void SetupResult(TQueryFunction<RequestedReturnType>& Result)`
- L153 _public function_ `template<typename RequestedReturnType> static constexpr void SetupResult(TConstQueryFunction<RequestedReturnType>& Result)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L12 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L14 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage::Queries`)
- L169 _function_ `template<bool bIsConst, typename FunctionInfo, typename ArgumentInfo, typename ReturnType, typename FunctionType> EFlowControl CallBody( TResult<ReturnType>& QueryResult, typename TQueryFunctionBase<ReturnType, bIsConst>::ContractType Contract, typename TQueryFunctionBase<ReturnType, bIsConst>::FunctionResponseType Response, typename TQueryFunctionBase<ReturnType, bIsConst>::FunctionSpecializationCallback Specialization, FunctionType&& Callback, EFlowControl IncompleteRowFlowControl)` (scope `UE::Editor::DataStorage::Queries::Private`)
- L177 _typedef_ `using ArgumentList = typename ArgumentInfo::ArgumentList;` (scope `UE::Editor::DataStorage::Queries::Private::CallBody`)
- L262 _function_ `template<typename ReturnType, bool bIsConst> template<EFunctionCallConfig Config> EFlowControl TQueryFunctionBase<ReturnType, bIsConst>::CallInternal(TResult<ReturnType>& Result, ContractType Contract, FunctionResponseType Response) const` (scope `UE::Editor::DataStorage::Queries::TQueryFunctionBase`)
- L281 _function_ `` (scope `UE::Editor::DataStorage::Queries::TQueryFunctionBase::CallInternal`)
- L325 _function_ `template<typename Return, FunctionType Function> TQueryFunction<Return> BuildQueryFunction(Function&& Callback)` (scope `UE::Editor::DataStorage::Queries`)
- L327 _typedef_ `using FunctionInfo = Private::TFunctionInfo<Function>;` (scope `UE::Editor::DataStorage::Queries::BuildQueryFunction`)
- L328 _typedef_ `using ArgumentInfo = typename FunctionInfo::ArgumentInfo;` (scope `UE::Editor::DataStorage::Queries::BuildQueryFunction`)
- L341 _function_ `` (scope `UE::Editor::DataStorage::Queries::BuildQueryFunction`)
- L348 _function_ `template<typename Return, FunctionType Function> TConstQueryFunction<Return> BuildConstQueryFunction(Function&& Callback)` (scope `UE::Editor::DataStorage::Queries`)
- L350 _typedef_ `using FunctionInfo = Private::TFunctionInfo<Function>;` (scope `UE::Editor::DataStorage::Queries::BuildConstQueryFunction`)
- L351 _typedef_ `using ArgumentInfo = typename FunctionInfo::ArgumentInfo;` (scope `UE::Editor::DataStorage::Queries::BuildConstQueryFunction`)
- L364 _function_ `` (scope `UE::Editor::DataStorage::Queries::BuildConstQueryFunction`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementRegistry.h` (Public)


#### class `UTypedElementRegistry`  
`class UTypedElementRegistry : public UObject`  
_L54-684_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: Registry of element types and their associated interfaces, along with the elements that represent their instances.
- L59 _public prototype_ `UTypedElementRegistry();`
- L62 _public prototype_ `virtual void FinishDestroy() override;`
- L63 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L68 _public prototype_ `static void Private_InitializeInstance();` — Initialize the singleton instance of the registry used in most cases.
- L73 _public prototype_ `static void Private_ShutdownInstance();` — Shutdown the singleton instance of the registry used in most cases.
- L79 _public prototype_ `static UTypedElementRegistry* GetInstance();` — `UFUNCTION(BlueprintPure, DisplayName="Get Default Typed Element Registry", Category = "TypedElementFramework|Registry", meta=(ScriptName="GetDefaultTypedElementRegistry"))` — Get the singleton instance of the registry used in most cases.
- L84 _public typedef_ `using FOnElementReplaced_Payload = TArrayView<const TTuple<FTypedElementHandle, FTypedElementHandle>>;` — Event fired when references to one element should be replaced with a reference to a different element.
- L85 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnElementReplaced, FOnElementReplaced_Payload );`
- L86 _public function_ `FOnElementReplaced& OnElementReplaced()`
- L94 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnElementUpdated, TArrayView<const FTypedElementHandle> );` — Event fired when an element has been internally updated and data cached from it should be refreshed.
- L95 _public function_ `FOnElementUpdated& OnElementUpdated()`
- L104 _public function_ `FSimpleMulticastDelegate& OnProcessingDeferredElementsToDestroy()` — Event fired prior to processing any elements that were previously marked for deferred destruction. @see ProcessDeferredElementsToDestroy.
- L113 _public function_ `inline FTypedHandleTypeId GetRegisteredElementTypeId(const FName InElementTypeName) const` — Get the element type ID for the associated element type name, if any. @return The element type ID, or 0 if the given name wasn't registered.
- L123 _public function_ `inline FName GetRegisteredElementTypeName(const FTypedHandleTypeId InElementTypeId) const` — Get the element type name for the associated element type ID, if any. @return The element type name, or None if the given ID wasn't registered.
- L133 _public function_ `inline void RegisterElementType(const FName InElementTypeName, bool bSupportScriptHandles)` — Register an element type that doesn't require any additional payload data. @param bSupportScriptHandles Does this element type support script handles. If true the elements of this type can only be destroyed from the game thread
- L150 _public function_ `template <typename ElementDataType, bool bSupportScriptHandles> inline void RegisterElementType(const FName InElementTypeName)` — Register an element type that has additional payload data. Note if bSupportScriptHandles is true, elements of this type should only be destroyed from the game thread
- L159 _public function_ `template <typename BaseInterfaceType> inline void RegisterElementInterface(const FName InElementTypeName, UObject* InElementInterface, const bool InAllowOverride = false)` — Register that an element interface is supported for the given type, which must have previously been registered via RegisterElementType.
- L169 _public function_ `template <typename BaseInterfaceType> inline BaseInterfaceType* GetElementInterface(const FTypedHandleTypeId InElementTypeId) const` — Get the element interface supported by the given type, or null if there is no support for this interface.
- L178 _public function_ `template <typename BaseInterfaceType> inline BaseInterfaceType* GetElementInterface(const FTypedElementHandle& InElementHandle) const` — Get the element interface supported by the given handle, or null if there is no support for this interface.
- L186 _public function_ `inline UObject* GetElementInterface(const FTypedElementHandle& InElementHandle, const TSubclassOf<UInterface> InBaseInterfaceType) const` — Get the element interface supported by the given handle, or null if there is no support for this interface.
- L195 _public function_ `inline UObject* GetElementInterface(const FScriptTypedElementHandle& InElementHandle, const TSubclassOf<UInterface> InBaseInterfaceType) const` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Registry")` — Get the element interface supported by the given handle, or null if there is no support for this interface or if the handle is invalid.
- L204 _public function_ `inline FTypedElementOwner CreateElement(const FName InElementTypeName, const FTypedHandleElementId InElementId)` — Create an element that doesn't require any additional payload data. @note The associated handle ID should be something that can externally be used to uniquely identify this element, until DestroyElementHandle is called on this handle.
- L214 _public function_ `template <typename ElementDataType> inline TTypedElementOwner<ElementDataType> CreateElement(const FName InElementTypeName)` — Create an element that has additional payload data. @note Allocation of the payload data and the associated handle ID are managed internally, and the data will remain valid until DestroyElementHandle is called on this handle.
- L223 _public function_ `inline void DestroyElement(FTypedElementOwner& InOutElementOwner)` — Destroy an element. @note Destruction is deferred until the next call to ProcessDeferredElementsToDestroy.
- L233 _public function_ `template <typename ElementDataType> inline void DestroyElement(TTypedElementOwner<ElementDataType>& InOutElementOwner)` — Destroy an element. @note Destruction is deferred until the next call to ProcessDeferredElementsToDestroy.
- L243 _public prototype_ `void ProcessDeferredElementsToDestroy();` — Process any elements that were previously marked for deferred destruction. @note This is automatically called at the end of each frame, but may also be called manually. @note This is automatically called post-GC, unless auto-GC destruction has been disabled (@see FDisableElementDestructionOnGC).
- L248 _public prototype_ `void ReleaseElementId(FTypedElementId& InOutElementId);` — Release an element ID that was previously acquired from an existing handle.
- L253 _public prototype_ `FTypedElementHandle GetElementHandle(const FTypedElementId& InElementId) const;` — Get an element handle from its minimal ID.
- L258 _public function_ `inline FTypedElement GetElement(const FTypedElementId& InElementId, const TSubclassOf<UInterface>& InBaseInterfaceType) const` — Get an element that implements the given interface from its minimal ID.
- L269 _public function_ `template <typename BaseInterfaceType> inline TTypedElement<BaseInterfaceType> GetElement(const FTypedElementId& InElementId) const` — Get an element that implements the given interface from its minimal ID.
- L279 _public function_ `inline FTypedElement GetElement(const FTypedElementHandle& InElementHandle, const TSubclassOf<UInterface>& InBaseInterfaceType) const` — Get an element that implements the given interface from its handle.
- L290 _public function_ `template <typename BaseInterfaceType> inline TTypedElement<BaseInterfaceType> GetElement(const FTypedElementHandle& InElementHandle) const` — Get an element that implements the given interface from its handle.
- L300 _public function_ `inline FTypedElementListRef CreateElementList()` — Create an empty list of elements associated with this registry.
- L308 _public function_ `inline FScriptTypedElementListRef CreateScriptElementList()` — Create an empty list of script elements associated with this registry.
- L316 _public prototype_ `FTypedElementListRef CreateElementList(TArrayView<const FTypedElementId> InElementIds);` — Create an empty list of elements associated with this registry, populated from the given minimal IDs that are valid.
- L321 _public prototype_ `FTypedElementListRef CreateElementList(TArrayView<const FTypedElementHandle> InElementHandles);` — Create an empty list of elements associated with this registry, populated from the given handles that are valid.
- L327 _public function_ `template <typename ElementDataType> inline FTypedElementListRef CreateElementList(const TArray<TTypedElementOwner<ElementDataType>>& InElementOwners)` — Create an empty list of elements associated with this registry, populated from the given owners that are valid.
- L336 _public function_ `template <typename ElementDataType> FTypedElementListRef CreateElementList(TArrayView<const TTypedElementOwner<ElementDataType>> InElementOwners)` — Create an empty list of elements associated with this registry, populated from the given owners that are valid.
- L347 _public prototype_ `FString RegistredElementTypesAndInterfacesToString() const;` — Extract a string that contains name of the type elements registered. For each type it also says what interface are registered and the path of the class that implement them
- L352 _public function_ `inline FScriptTypedElementHandle CreateScriptHandle(const FTypedElementId& InElementId)` — Create a script handle. This should only be use for the script exposure apis.
- L371 _public function_ `void Private_OnElementListCreated(FTypedElementList* InElementList)`
- L377 _public function_ `void Private_OnElementListDestroyed(FTypedElementList* InElementList)`
- L384 _public function_ `void Private_OnElementListCreated(FScriptTypedElementList* InElementList)`
- L390 _public function_ `void Private_OnElementListDestroyed(FScriptTypedElementList* InElementList)`
- L397 _public function_ `inline void Private_GetElementImpl(const FTypedElementHandle& InElementHandle, const TSubclassOf<UInterface>& InBaseInterfaceType, FTypedElement& OutElement) const` — Note: Access for FTypedElementList
- L528 _private prototype_ `void RegisterElementTypeImpl(const FName InElementTypeName, TUniquePtr<FRegisteredElementType>&& InRegisteredElementType);`
- L529 _private prototype_ `void RegisterElementInterfaceImpl(const FName InElementTypeName, UObject* InElementInterface, const TSubclassOf<UInterface>& InBaseInterfaceType, const bool InAllowOverride);`
- L530 _private prototype_ `UObject* GetElementInterfaceImpl(const FTypedHandleTypeId InElementTypeId, const TSubclassOf<UInterface>& InBaseInterfaceType) const;`
- L533 _private function_ `template <typename ElementDataType> TTypedElementOwner<ElementDataType> CreateElementImpl(const FName InElementTypeName, const FTypedHandleElementId InElementId)`
- L550 _private function_ `template <typename ElementDataType> void DestroyElementImpl(TTypedElementOwner<ElementDataType>& InOutElementOwner)`
- L560 _private function_ `template <typename BaseInterfaceType> void GetElementImpl(const FTypedElementId& InElementId, const TSubclassOf<UInterface>& InBaseInterfaceType, TTypedElement<BaseInterfaceType>& OutElement) const`
- L585 _private function_ `template <typename BaseInterfaceType> void GetElementImpl(const FTypedElementHandle& InElementHandle, const TSubclassOf<UInterface>& InBaseInterfaceType, TTypedElement<BaseInterfaceType>& OutElement) const`
- L615 _private function_ `void AddRegisteredElementType(TUniquePtr<FRegisteredElementType>&& InRegisteredElementType)`
- L630 _private function_ `FRegisteredElementType* GetRegisteredElementTypeFromId(const FTypedHandleTypeId InTypeId) const`
- L639 _private function_ `FRegisteredElementType* GetRegisteredElementTypeFromName(const FName& InTypeName) const`
- L651 _private prototype_ `void NotifyElementListPendingChanges();`
- L653 _private prototype_ `void OnBeginFrame();`
- L654 _private prototype_ `void OnEndFrame();`
- L655 _private prototype_ `void OnPostGarbageCollect();`
- L657 _private function_ `inline void IncrementDisableElementDestructionOnGCCount()`
- L663 _private function_ `inline void DecrementDisableElementDestructionOnGCCount()`
- L669 _private member_ `mutable FTransactionallySafeRWLock RegisteredElementTypesRW;`
- L670 _private member_ `TUniquePtr<FRegisteredElementType> RegisteredElementTypes[TypedHandleMaxTypeId - 1];`
- L671 _private member_ `TSortedMap<FName, FTypedHandleTypeId, FDefaultAllocator, FNameFastLess> RegisteredElementTypesNameToId;`
- L673 _private member_ `mutable FCriticalSection ActiveElementListsCS;`
- L674 _private member_ `TSet<FTypedElementList*> ActiveElementLists;`
- L676 _private member_ `TSet<FScriptTypedElementList*> ActiveScriptElementLists;`
- L678 _private member_ `uint8 DisableElementDestructionOnGCCount = 0;`
- L679 _private member_ `bool bIsWithinFrame = false;`
- L681 _private member_ `FOnElementReplaced OnElementReplacedDelegate;`
- L682 _private member_ `FOnElementUpdated OnElementUpdatedDelegate;`
- L683 _private member_ `FSimpleMulticastDelegate OnProcessingDeferredElementsToDestroyDelegate;`

#### struct `UTypedElementRegistry::FDisableElementDestructionOnGC`  
`struct FDisableElementDestructionOnGC`  
_L403-426_
- desc: Struct to disable auto-GC reference collection within a scope
- L406 _public function_ `explicit FDisableElementDestructionOnGC(UTypedElementRegistry* InRegistry) : Registry(InRegistry)`
- L413 _public function_ `~FDisableElementDestructionOnGC()`
- L418 _public prototype_ `FDisableElementDestructionOnGC(const FDisableElementDestructionOnGC&) = delete;`
- L419 _public prototype_ `FDisableElementDestructionOnGC& operator=(const FDisableElementDestructionOnGC&) = delete;`
- L421 _public prototype_ `FDisableElementDestructionOnGC(FDisableElementDestructionOnGC&&) = delete;`
- L422 _public prototype_ `FDisableElementDestructionOnGC& operator=(FDisableElementDestructionOnGC&&) = delete;`
- L425 _private member_ `UTypedElementRegistry* Registry = nullptr;`

#### struct `UTypedElementRegistry::FRegisteredElementType`  
`struct FRegisteredElementType`  
_L429-446_
- L431 _public prototype_ `virtual ~FRegisteredElementType() = default;`
- L433 _public prototype_ `virtual FTypedElementInternalData& AddDataForElement(FTypedHandleElementId& InOutElementId) = 0;`
- L434 _public prototype_ `virtual void RemoveDataForElement(const FTypedHandleElementId InElementId, const FTypedElementInternalData* InExpectedDataPtr, const bool bDefer) = 0;`
- L435 _public prototype_ `virtual const FTypedElementInternalData& GetDataForElement(const FTypedHandleElementId InElementId) const = 0;`
- L436 _public prototype_ `virtual FScriptTypedElementInternalDataPtr GetDataForScriptElement(const FTypedHandleElementId InElementId) = 0;`
- L437 _public prototype_ `virtual void ProcessDeferredElementsToRemove() = 0;`
- L438 _public prototype_ `virtual void SetDataTypeId(const FTypedHandleTypeId InTypeId) = 0;`
- L439 _public prototype_ `virtual FTypedHandleTypeId GetDataTypeId() const = 0;`
- L440 _public prototype_ `virtual FName GetDataTypeName() const = 0;`
- L442 _public member_ `FTypedHandleTypeId TypeId = 0;`
- L443 _public member_ `FName TypeName;`
- L445 _public member_ `TSortedMap<FName, TObjectPtr<UObject>, FDefaultAllocator, FNameFastLess> Interfaces;`

#### struct `UTypedElementRegistry::TRegisteredElementType`  
`template <typename ElementDataType, bool bSupportScriptHandles> struct TRegisteredElementType : public FRegisteredElementType`  
_L449-526_
- inherits: `FRegisteredElementType`
- L451 _public prototype_ `virtual ~TRegisteredElementType() = default;`
- L453 _public function_ `virtual FTypedElementInternalData& AddDataForElement(FTypedHandleElementId& InOutElementId) override`
- L458 _public function_ `virtual void RemoveDataForElement(const FTypedHandleElementId InElementId, const FTypedElementInternalData* InExpectedDataPtr, const bool bDefer) override`
- L479 _public function_ `virtual FScriptTypedElementInternalDataPtr GetDataForScriptElement(const FTypedHandleElementId InElementId) override`
- L491 _public function_ `virtual const FTypedElementInternalData& GetDataForElement(const FTypedHandleElementId InElementId) const override`
- L496 _public function_ `virtual void ProcessDeferredElementsToRemove() override`
- L506 _public function_ `virtual void SetDataTypeId(const FTypedHandleTypeId InTypeId) override`
- L511 _public function_ `virtual FTypedHandleTypeId GetDataTypeId() const override`
- L516 _public function_ `virtual FName GetDataTypeName() const override`
- L521 _public member_ `TTypedElementInternalDataStore<ElementDataType> HandleDataStore;`
- L523 _public typedef_ `using FDeferredElementToRemove = TTuple<FTypedHandleElementId, const FTypedElementInternalData*>;`
- L524 _public member_ `FCriticalSection DeferredElementsToRemoveCS;`
- L525 _public member_ `TArray<FDeferredElementToRemove> DeferredElementsToRemove;`

#### Free symbols / members of external scopes

- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnElementReplaced, FOnElementReplaced_Payload );`
- L94 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnElementUpdated, TArrayView<const FTypedElementHandle> );` — Event fired when an element has been internally updated and data cached from it should be refreshed.

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementRowHandleArray.h` (Public)


#### class `UE::Editor::DataStorage::FRowHandleArray`  
`class FRowHandleArray`  
_L15-151_
- desc: Array dedicated to handling row handles. This provides various unique and optimized functionality that makes working with a large number row handles easier and more efficient.
- L18 _public typedef_ `using EFlags = FRowHandleArrayView::EFlags;`
- L20 _public prototype_ `FRowHandleArray() = default;`
- L21 _public prototype_ `explicit FRowHandleArray(FRowHandleArrayView InRows);`
- L24 _public prototype_ `int32 Num() const;` — Returns the number of rows stored.
- L30 _public prototype_ `void Reserve(int32 Count);` — Reserve space for additional row handles. This allocates memory but doesn't add new row handles. If the requested count is less than the current count then nothing happens.
- L33 _public prototype_ `void Shrink();` — Reduces the amount of memory used by the array to exactly fit the current number or elements.
- L41 _public prototype_ `void Add(RowHandle Row, EFlags Guarantee = EFlags::None);` — Appends the provided row handle at the end of the array. This may result in the array becoming unsorted and/or no longer unique. If Guarantee is set to IsUnique the user takes responsibility to guaranteed that the new row is not already present. If array is sorted, the IsUnique hint is ignored and the array will determine if the values are unique. The IsSorted guarantee is always ignored. If the arrays was already not unique setting the Guarantee flags has no effect.
- L49 _public prototype_ `void Append(TConstArrayView<RowHandle> AdditionalRows, EFlags Guarantee = EFlags::None);` — Append the provided list of rows to the end of the array. If Guarantee is set to IsSorted and/or IsUnique the user guarantees that the provided row handle array view is sorted by row handle and/or only contains unique values. In this case this function will try to append the additional rows and maintain the sorted status and if applicable the uniqueness state, otherwise the array will be marked as unsorted and no longer unique.
- L56 _public prototype_ `void Append(FRowHandleArrayView AdditionalRows);` — Append the provided list of rows to the end of the array. If the current array and the additional rows are both sorted then this function will try to append the additional rows and maintain the sorted status and if applicable the uniqueness state, otherwise the array will be marked as unsorted and no longer unique.
- L63 _public prototype_ `void Remove(RowHandle Row);` — Removes the provided row. If the array is sorted, a binary search will be used to find the row, but requires moving all subsequent rows down. If the array is not sorted a linear search is required but the last row will be moved into the removed location for quicker removal.
- L69 _public prototype_ `void Remove(TConstArrayView<RowHandle> RowsToRemove);` — Removes the provided list of rows. If the array is sorted, a binary search will be used to find the row, but requires moving all subsequent rows down. If the array is not sorted a linear search is required but the last row will be moved into the removed location for quicker removals.
- L76 _public prototype_ `void Remove(FRowHandleArrayView RowsToRemove);` — Removes the provided list of rows. If the array is sorted, a binary search will be used to find the row, but requires moving all subsequent rows down. If the array is not sorted a linear search is required but the last row will be moved into the removed location for quicker removals. If both the array and list of rows to remove are sorted than an optimized version can run that quickly finds the first row to remove and then removes the other rows as it's moving the remainder down.
- L82 _public prototype_ `bool Contains(RowHandle Row) const;` — Checks if the provided row is stored in this array. If the array is sorted a faster binary search is used, otherwise a linear search is required.
- L88 _public prototype_ `void Reset(int32 NewSize = 0);` — Removes all row handles, but keeps the allocated memory around. If the provided size is larger than the number of rows that fit in the container then extra memory will be allocated so there's enough space for the new number of rows.
- L94 _public prototype_ `void Empty(int32 Slack = 0);` — Removes all row handles and releases all allocated memory. If the provided slack size is not zero then memory is reserved for at least the provided number of rows.
- L97 _public prototype_ `void Sort();` — Sorts the row handles in numerical order from lowest to highest.
- L102 _public prototype_ `void Sort(TArrayView<RowHandle> ScratchBuffer);` — Sorts the row handles in numerical order from lowest to highest. This version is faster as it doesn't need to allocate a temporary intermediate array. ScratchBuffer has to be at least as large as the number of rows in the array.
- L105 _public prototype_ `void MakeUnique();` — Goes through the array and removes any duplicate entries. If the array isn't sorted it will be sorted first.
- L110 _public prototype_ `void ReduceToDuplicates();` — Goes through the array and only keeps a single instance of any value that appears twice or more. If the array isn't sorted it will be sorted first. After this function completes the array only contains unique values.
- L113 _public prototype_ `void SortedMerge(FRowHandleArrayView AddedRows);` — Merges the provided array into the array while remaining sorted. The provided array is expected to be sorted.
- L115 _public prototype_ `void SortedMerge(const FRowHandleArray& AddedRows);` — Merges the provided array into the array while remaining sorted. The provided array is expected to be sorted.
- L117 _public prototype_ `void SortedMerge(FRowHandleArray&& AddedRows);` — Merges the provided array into the array while remaining sorted.
- L124 _public prototype_ `void InvertOrder();` — Reverses the order in which the rows are stored, making the first element the last and vice versa. If the array was marked as sorted it will no longer be considered sorted. Another call to InvertOrder will not restore the sorted state.
- L127 _public prototype_ `FRowHandleArrayView GetRows() const;` — Constructs a view of the array to provide access to its rows.
- L134 _public prototype_ `TArrayView<RowHandle> GetMutableRows(EFlags Guarantee = EFlags::None);` — Returns a mutable view of the array of rows. This will invalidate sorted and uniqueness status of the array. If Guarantee is set to IsSorted and/or IsUnique the user takes responsibility to guaranteed that the rows remain sorted in numeric order and/or all values remain unique after the new rows are modified. If the arrays was already not sorted and/or not unique setting the Guarantee flags has no effect.
- L136 _public prototype_ `bool IsSorted() const;` — Whether or not the contained rows are numerically ordered from smallest to largest.
- L138 _public prototype_ `bool IsUnique() const;` — Whether or all rows in the view only appear once.
- L140 _public prototype_ `bool IsEmpty() const;` — Whether or not there are any values in the view.
- L142 _public prototype_ `bool IsSame(const FRowHandleArray& Other) const;` — Whether or not the two arrays contain the same values.
- L145 _private prototype_ `void SortedMergeInternal(FRowHandleArrayView AddedRows);`
- L146 _private prototype_ `int32 Find(RowHandle Row) const;`
- L148 _private member_ `TArray<RowHandle> Rows;`
- L149 _private member_ `bool bIsSorted = true;`
- L150 _private member_ `bool bIsUnique = true;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementRowHandleArrayView.h` (Public)


#### class `UE::Editor::DataStorage::FRowHandleArrayView`  
`class FRowHandleArrayView`  
_L19-88_
- desc: Provides a view of a list of row handles. Note that this view is more restrictive than typical array views. For instance, an typical array view would remain valid after changing values the array, but will invalidate FRowHandleArrayView as the value may not be unique and/or cause the array to no longer be sorted.
- L29 _public prototype_ `FRowHandleArrayView() = default;`
- L30 _public prototype_ `FRowHandleArrayView(const RowHandle* Rows UE_LIFETIMEBOUND, int32 RowCount, EFlags Flags);`
- L31 _public prototype_ `FRowHandleArrayView(TConstArrayView<RowHandle> Rows, EFlags Flags);`
- L32 _public prototype_ `FRowHandleArrayView(std::initializer_list<RowHandle> Rows UE_LIFETIMEBOUND, EFlags Flags);`
- L38 _public prototype_ `const RowHandle* begin() const;` — Returns a pointer to the first row in the view. This function is primarily used for compatibility to C++ features and libraries.
- L43 _public prototype_ `const RowHandle* end() const;` — Returns a pointer the address after the last row in the view. This function is primarily used for compatibility to C++ features and libraries.
- L46 _public prototype_ `RowHandle operator[](uint32 Index) const;` — Retrieves the row handle at the provided index or asserts if the index is out of bounds.
- L48 _public prototype_ `const RowHandle* GetData() const;` — Returns the address of row handles in memory.
- L53 _public prototype_ `const RowHandle& First() const;` — If the view is not empty, this return the last row handle in the view. Calling this function on an empty view will cause an assert.
- L58 _public prototype_ `const RowHandle& Last() const;` — If the view is not empty, this return the last row handle in the view. Calling this function on an empty view will cause an assert.
- L60 _public prototype_ `int32 Num() const;` — The number of rows this view shows.
- L65 _public prototype_ `int32 NumBytes() const;` — Returns the total number of bytes that are in use by rows. This is may not be the total amount of memory in use by the container this view maps to.
- L68 _public prototype_ `operator TConstArrayView<RowHandle>() const;` — Conversion operator to allow the view to be transparently used in places where a immutable array view of row handles is required.
- L71 _public prototype_ `bool IsSorted() const;` — Whether or not the contained rows are numerically ordered from smallest to largest.
- L73 _public prototype_ `bool IsUnique() const;` — Whether or all rows in the view only appear once.
- L75 _public prototype_ `bool IsEmpty() const;` — Whether or not there are any values in the view.
- L81 _public prototype_ `bool Contains(RowHandle Row) const;` — Whether or not the view contains the provided row. If the view is sorted a much binary search can be used for a much faster search otherwise a slower linear search is done.
- L84 _private member_ `const RowHandle* Rows = nullptr;`
- L85 _private member_ `int32 RowCount = 0;`
- L86 _private member_ `bool bIsSorted = false;`
- L87 _private member_ `bool bIsUnique = false;`

#### enum `UE::Editor::DataStorage::FRowHandleArrayView::EFlags`  
`enum class EFlags`  
_L22-27_
- L24 _public enumerator_ `None = 0`
- L25 _public enumerator_ `IsSorted = 1 << 0` — The view is sorted by row handle.
- L26 _public enumerator_ `IsUnique = 1 << 1` — Every value in the view is guaranteed to appear only once.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L90 _prototype_ `ENUM_CLASS_FLAGS(FRowHandleArrayView::EFlags);` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementSearcher.h` (Public)


#### class `UE::Editor::DataStorage::FColumnSearcherInterface`  
`class FColumnSearcherInterface`  
_L20-26_
- desc: Interface to provide searching of rows by column.
- L23 _public prototype_ `virtual ~FColumnSearcherInterface() = default;`
- L25 _public prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, RowHandle Row) const = 0;`

#### class `UE::Editor::DataStorage::TColumnSearcherInterface`  
`template<typename ColumnType> class TColumnSearcherInterface : public FColumnSearcherInterface`  
_L29-38_
- inherits: `FColumnSearcherInterface`
- L32 _public prototype_ `virtual ~TColumnSearcherInterface() override = default;`
- L34 _public prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, RowHandle Row) const override final;`
- L37 _protected prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, const ColumnType& Column) const = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementSearcher.inl` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L10 _function_ `template<typename ColumnType> void TColumnSearcherInterface<ColumnType>::GetSearchableString( FString& SearchableString, const ICoreProvider& Storage, RowHandle Row) const` (scope `UE::Editor::DataStorage::TColumnSearcherInterface`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementSorter.h` (Public)


#### struct `UE::Editor::DataStorage::FPrefixInfo`  
`struct FPrefixInfo`  
_L22-26_
- L24 _public member_ `uint64 Prefix = TNumericLimits<uint64>::Max();`
- L25 _public member_ `bool bHasRemainingBytes = false;`

#### class `UE::Editor::DataStorage::FColumnSorterInterface`  
`class FColumnSorterInterface`  
_L29-91_
- desc: Interface to provide sorting of rows by column.
- L32 _public prototype_ `virtual ~FColumnSorterInterface() = default;`
- L72 _public prototype_ `virtual ESortType GetSortType() const = 0;` — Returns the type of sorting required for this column.
- L75 _public prototype_ `virtual FText GetShortName() const = 0;` — If set, this can be used.
- L81 _public prototype_ `virtual int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const = 0;` — Compare the content of the left row to the right row and return a negative number if left is smaller than right, zero if left and right are equal and a positive number if right is larger than left.
- L90 _public prototype_ `virtual FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const = 0;` — The numeric prefix for the column. For numeric values this typically the number itself. For strings it's typically the next 8 characters or 4 wide characters starting at the provided byte index. The utility function can `CreateSortPrefix` be used to help create a prefix from one or more variables. Note that using a prefix is limited to only one value that has a variable length (e.g. strings) and has to be the last value to be sorted.

#### enum `UE::Editor::DataStorage::FColumnSorterInterface::ESortType`  
`enum class ESortType : uint8`  
_L34-69_
- L40 _public enumerator_ `FixedSize64` — Supports sort algorithms that sort by only using a single (packed) value of 64 bits. Algorithms supporting this option will only use `SortPrefix` and will only call this once per row.
- L46 _public enumerator_ `FixedSizeOnly` — Supports sort algorithms that sort by only using one or more fixed sized values like integers or floats. Algorithms supporting this option will only use `SortPrefix` and assume only fixed sized values are used. Including values with variable size such as strings will lead to suboptimal performance.
- L54 _public enumerator_ `ComparativeSort` — Supports sort algorithms that sort using a comparative function. Algorithms supporting this option will only use the `Compare` function to sort. Comparative sorting requires more reads from columns than fixed sized sorting or hybrid sorting an is also more susceptible to frame spikes when distributed over multiple frames and/or threads. It does however provide greater flexibility when requiring complex comparisons such as ones requiring multiple strings.
- L65 _public enumerator_ `HybridSort` — Supports sort algorithms that sort using both a prefix and a comparative function. Algorithms supporting this option will use both the `SortPrefix` and `Compare` functions to sort. Typically rows are grouped into buckets based on their prefix and when a bucket is small enough a compare may be used to sort the bucket. A hybrid approach is typically faster for larger numbers of rows as is reduces the amount of times columns have to be read. It also reduces or removes the need for a compare which can be beneficial if the compare is expensive. Lastly it typically also allows for more even work distribution over frames/threads, reducing the risk of spikes. However it does come at an increased peak memory usage and limits the number of variable sized variables to one, which also have to be the last variable in the chain.
- L68 _public enumerator_ `Max` — Indicates the final value, cannot be used as input.

#### class `UE::Editor::DataStorage::TColumnSorterInterface`  
`template<FColumnSorterInterface::ESortType SortType, typename ColumnType> class TColumnSorterInterface : public FColumnSorterInterface`  
_L94-97_
- inherits: `FColumnSorterInterface`
- L103 _public prototype_ `virtual ~TColumnSorterInterface() override = default;`
- L105 _public prototype_ `int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override final;`
- L106 _public prototype_ `FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override final;`
- L107 _public prototype_ `ESortType GetSortType() const override final;`
- L110 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const ColumnType& Column, uint32 ByteIndex) const = 0;`
- L138 _protected prototype_ `virtual int32 Compare(const ColumnType& Left, const ColumnType& Right) const = 0;`

#### class `UE::Editor::DataStorage::TColumnSorterInterface`  
`template<typename ColumnType> class TColumnSorterInterface<FColumnSorterInterface::ESortType::FixedSize64, ColumnType> : public FColumnSorterInterface`  
_L100-111_
- inherits: `FColumnSorterInterface`
- L103 _public prototype_ `virtual ~TColumnSorterInterface() override = default;`
- L105 _public prototype_ `int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override final;`
- L106 _public prototype_ `FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override final;`
- L107 _public prototype_ `ESortType GetSortType() const override final;`
- L110 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const ColumnType& Column, uint32 ByteIndex) const = 0;`
- L138 _protected prototype_ `virtual int32 Compare(const ColumnType& Left, const ColumnType& Right) const = 0;`

#### class `UE::Editor::DataStorage::TColumnSorterInterface`  
`template<typename ColumnType> class TColumnSorterInterface<FColumnSorterInterface::ESortType::FixedSizeOnly, ColumnType> : public FColumnSorterInterface`  
_L114-125_
- inherits: `FColumnSorterInterface`
- L103 _public prototype_ `virtual ~TColumnSorterInterface() override = default;`
- L105 _public prototype_ `int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override final;`
- L106 _public prototype_ `FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override final;`
- L107 _public prototype_ `ESortType GetSortType() const override final;`
- L110 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const ColumnType& Column, uint32 ByteIndex) const = 0;`
- L138 _protected prototype_ `virtual int32 Compare(const ColumnType& Left, const ColumnType& Right) const = 0;`

#### class `UE::Editor::DataStorage::TColumnSorterInterface`  
`template<typename ColumnType> class TColumnSorterInterface<FColumnSorterInterface::ESortType::ComparativeSort, ColumnType> : public FColumnSorterInterface`  
_L128-139_
- inherits: `FColumnSorterInterface`
- L103 _public prototype_ `virtual ~TColumnSorterInterface() override = default;`
- L105 _public prototype_ `int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override final;`
- L106 _public prototype_ `FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override final;`
- L107 _public prototype_ `ESortType GetSortType() const override final;`
- L110 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const ColumnType& Column, uint32 ByteIndex) const = 0;`
- L138 _protected prototype_ `virtual int32 Compare(const ColumnType& Left, const ColumnType& Right) const = 0;`

#### class `UE::Editor::DataStorage::TColumnSorterInterface`  
`template<typename ColumnType> class TColumnSorterInterface<FColumnSorterInterface::ESortType::HybridSort, ColumnType> : public FColumnSorterInterface`  
_L142-154_
- inherits: `FColumnSorterInterface`
- L103 _public prototype_ `virtual ~TColumnSorterInterface() override = default;`
- L105 _public prototype_ `int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override final;`
- L106 _public prototype_ `FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override final;`
- L107 _public prototype_ `ESortType GetSortType() const override final;`
- L110 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const ColumnType& Column, uint32 ByteIndex) const = 0;`
- L138 _protected prototype_ `virtual int32 Compare(const ColumnType& Left, const ColumnType& Right) const = 0;`

#### struct `UE::Editor::DataStorage::Private::TSortStringViewType`  
`template <typename T> struct TSortStringViewType : std::false_type`  
_L162-162_
- inherits: `std::false_type`

#### struct `UE::Editor::DataStorage::Private::TSortStringViewType`  
`template <typename T> struct TSortStringViewType<TStringView<T>> : std::true_type`  
_L165-165_
- inherits: `std::true_type`

#### struct `UE::Editor::DataStorage::FSortCaseSensitive`  
`struct FSortCaseSensitive`  
_L193-193_

#### struct `UE::Editor::DataStorage::FSortCaseInsensitive`  
`struct FSortCaseInsensitive`  
_L194-194_

#### struct `UE::Editor::DataStorage::TSortStringView`  
`template<SortCase Casing, Private::SortStringViewValue StringView> struct TSortStringView`  
_L199-228_
- L201 _public typedef_ `using StringViewType = StringView;`
- L202 _public member_ `static constexpr bool bIsCaseSensitive = std::is_same_v<Casing, FSortCaseSensitive>;`
- L203 _public member_ `static constexpr ESearchCase::Type SearchCase = bIsCaseSensitive ? ESearchCase::CaseSensitive : ESearchCase::IgnoreCase;`
- L205 _public prototype_ `TSortStringView() = default;`
- L208 _public function_ `template<Private::SortStringViewCopyableType ViewType> TSortStringView(const ViewType& InView) : View(InView)`
- L210 _public function_ `template<Private::SortStringViewCopyableType ViewType> TSortStringView& operator=(const ViewType& InView)`
- L212 _public function_ `TSortStringView(const FText& Text) : View(Text.ToString())`
- L213 _public function_ `TSortStringView& operator=(const FText& Text)`
- L216 _public function_ `template<SortCase TargetCasing, Private::SortStringViewCopyableType ViewType> TSortStringView(TargetCasing, const ViewType& String) : View(String)`
- L218 _public function_ `template<SortCase TargetCasing> TSortStringView(TargetCasing, const FText& Text) : View(Text.ToString())`
- L220 _public function_ `bool operator==(const TSortStringView& Rhs) const`
- L221 _public function_ `bool operator!=(const TSortStringView& Rhs) const`
- L222 _public function_ `bool operator< (const TSortStringView& Rhs) const`
- L223 _public function_ `bool operator<=(const TSortStringView& Rhs) const`
- L224 _public function_ `bool operator> (const TSortStringView& Rhs) const`
- L225 _public function_ `bool operator>=(const TSortStringView& Rhs) const`
- L227 _public member_ `StringView View;`

#### enum `UE::Editor::DataStorage::ENameSortBy`  
`enum class ENameSortBy : bool`  
_L235-235_
- L235 _public enumerator_ `enum class ENameSortBy : bool { Id, String }; enum class ESortByNameFlags { Default = 0, WithNone = 1 << 0, RemoveLeadingSlash = 1 << 1, };`
- L235 _public enumerator_ `enum class ENameSortBy : bool { Id, String }; enum class ESortByNameFlags { Default = 0, WithNone = 1 << 0, RemoveLeadingSlash = 1 << 1, };`

#### enum `UE::Editor::DataStorage::ESortByNameFlags`  
`enum class ESortByNameFlags`  
_L237-242_
- L239 _public enumerator_ `Default = 0`
- L240 _public enumerator_ `WithNone = 1 << 0`
- L241 _public enumerator_ `RemoveLeadingSlash = 1 << 1` — WithNone = 1 << 0,   If an empty name is found, use the string "None" to represent it.

#### struct `UE::Editor::DataStorage::TSortByName`  
`template<ESortByNameFlags InFlags = ESortByNameFlags::Default> struct TSortByName`  
_L247-247_
- desc: Sort FNames by their name. If an empty name is provided it will be treated as an empty string.
- L247 _public member_ `template<ESortByNameFlags InFlags = ESortByNameFlags::Default> struct TSortByName { static const ESortByNameFlags Flags = InFlags; };` — Sort FNames by their name. If an empty name is provided it will be treated as an empty string.

#### struct `UE::Editor::DataStorage::FSortById`  
`struct FSortById`  
_L249-249_
- desc: Sort FNames by their id.

#### struct `UE::Editor::DataStorage::IsSortByName`  
`template<typename> struct IsSortByName : std::false_type`  
_L252-252_
- inherits: `std::false_type`

#### struct `UE::Editor::DataStorage::IsSortByName`  
`template<ESortByNameFlags Flags> struct IsSortByName<TSortByName<Flags>> : std::true_type`  
_L254-254_
- inherits: `std::true_type`

#### struct `UE::Editor::DataStorage::TSortNameView`  
`template<SortBy By> struct TSortNameView`  
_L260-293_
- L262 _public member_ `constexpr static bool bIsById = std::is_same_v<By, FSortById>;`
- L263 _public typedef_ `using CompareType = std::conditional_t<bIsById, int32, FString>;`
- L264 _public member_ `constexpr static bool bIsFixedSize = bIsById;`
- L266 _public prototype_ `TSortNameView() = default;`
- L267 _public function_ `explicit TSortNameView(const FName& Name) : View(&Name)`
- L268 _public prototype_ `TSortNameView& operator=(const FName& Name);`
- L271 _public function_ `template<SortBy TargetBy> TSortNameView(TargetBy, const FName& Name) : View(&Name)`
- L273 _public prototype_ `uint32 GetByteSize() const;`
- L274 _public prototype_ `constexpr static uint32 GetElementSize();`
- L275 _public prototype_ `FPrefixInfo CalculatePrefix(int32 CurrentIndex, int32 ByteIndex) const;`
- L277 _public prototype_ `int32 Compare(const FName& Rhs) const;`
- L278 _public prototype_ `int32 Compare(const TSortNameView& Rhs) const;`
- L279 _public prototype_ `bool operator==(const TSortNameView& Rhs) const;`
- L280 _public prototype_ `bool operator!=(const TSortNameView& Rhs) const;`
- L281 _public prototype_ `bool operator< (const TSortNameView& Rhs) const;`
- L282 _public prototype_ `bool operator<=(const TSortNameView& Rhs) const;`
- L283 _public prototype_ `bool operator> (const TSortNameView& Rhs) const;`
- L284 _public prototype_ `bool operator>=(const TSortNameView& Rhs) const;`
- L286 _public member_ `const FName* View = nullptr;`
- L287 _public member_ `mutable CompareType Cache = {};`
- L288 _public member_ `mutable bool bIsCached = false;`
- L291 _private prototype_ `int32 Compare(const FName& Lhs, const FName& Rhs) const;`
- L292 _private prototype_ `void CacheCompareType() const;`

#### struct `UE::Editor::DataStorage::TSortTypeInfo`  
`template<typename ValueType> struct TSortTypeInfo`  
_L318-326_
- L321 _public member_ `static constexpr bool bIsSupportedType = false;` — Used to short-circuit several calls to minimize noise in the error output of the compiler.
- L331 _public member_ `static constexpr bool bIsSupportedType = true;`
- L332 _public member_ `static constexpr bool bIsFixedSize = true;`
- L333 _public function_ `constexpr static uint32 GetByteSize(NumericType Value)`
- L334 _public function_ `constexpr static uint32 GetElementSize()`
- L335 _public function_ `constexpr static FPrefixInfo CalculatePrefix(int32 CurrentIndex, int32 ByteIndex, NumericType Value)`
- L351 _public member_ `static constexpr bool bIsFixedSize = false;`
- L352 _public prototype_ `constexpr static uint32 GetByteSize(TSortStringView<Casing, T> Value);`
- L353 _public prototype_ `constexpr static uint32 GetElementSize();`
- L354 _public prototype_ `constexpr static FPrefixInfo CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortStringView<Casing, T> Value);`
- L370 _public member_ `static constexpr bool bIsFixedSize = TSortNameView<By>::bIsFixedSize;`
- L371 _public function_ `static uint32 GetByteSize(const TSortNameView<By>& Value)`
- L373 _public function_ `static FPrefixInfo CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortNameView<By> Value)`

#### struct `UE::Editor::DataStorage::TSortTypeInfo`  
`template<Private::SortNumericValue NumericType> struct TSortTypeInfo<NumericType>`  
_L329-345_
- L321 _public member_ `static constexpr bool bIsSupportedType = false;` — Used to short-circuit several calls to minimize noise in the error output of the compiler.
- L331 _public member_ `static constexpr bool bIsSupportedType = true;`
- L332 _public member_ `static constexpr bool bIsFixedSize = true;`
- L333 _public function_ `constexpr static uint32 GetByteSize(NumericType Value)`
- L334 _public function_ `constexpr static uint32 GetElementSize()`
- L335 _public function_ `constexpr static FPrefixInfo CalculatePrefix(int32 CurrentIndex, int32 ByteIndex, NumericType Value)`
- L351 _public member_ `static constexpr bool bIsFixedSize = false;`
- L352 _public prototype_ `constexpr static uint32 GetByteSize(TSortStringView<Casing, T> Value);`
- L353 _public prototype_ `constexpr static uint32 GetElementSize();`
- L354 _public prototype_ `constexpr static FPrefixInfo CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortStringView<Casing, T> Value);`
- L370 _public member_ `static constexpr bool bIsFixedSize = TSortNameView<By>::bIsFixedSize;`
- L371 _public function_ `static uint32 GetByteSize(const TSortNameView<By>& Value)`
- L373 _public function_ `static FPrefixInfo CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortNameView<By> Value)`

#### struct `UE::Editor::DataStorage::TSortTypeInfo`  
`template<SortCase Casing, typename T> struct TSortTypeInfo<TSortStringView<Casing, T>>`  
_L348-356_
- L321 _public member_ `static constexpr bool bIsSupportedType = false;` — Used to short-circuit several calls to minimize noise in the error output of the compiler.
- L331 _public member_ `static constexpr bool bIsSupportedType = true;`
- L332 _public member_ `static constexpr bool bIsFixedSize = true;`
- L333 _public function_ `constexpr static uint32 GetByteSize(NumericType Value)`
- L334 _public function_ `constexpr static uint32 GetElementSize()`
- L335 _public function_ `constexpr static FPrefixInfo CalculatePrefix(int32 CurrentIndex, int32 ByteIndex, NumericType Value)`
- L351 _public member_ `static constexpr bool bIsFixedSize = false;`
- L352 _public prototype_ `constexpr static uint32 GetByteSize(TSortStringView<Casing, T> Value);`
- L353 _public prototype_ `constexpr static uint32 GetElementSize();`
- L354 _public prototype_ `constexpr static FPrefixInfo CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortStringView<Casing, T> Value);`
- L370 _public member_ `static constexpr bool bIsFixedSize = TSortNameView<By>::bIsFixedSize;`
- L371 _public function_ `static uint32 GetByteSize(const TSortNameView<By>& Value)`
- L373 _public function_ `static FPrefixInfo CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortNameView<By> Value)`

#### struct `UE::Editor::DataStorage::TSortTypeInfo`  
`template<typename StringType> requires Private::SortStringVariantType<StringType> struct TSortTypeInfo<StringType>`  
_L359-364_
- L321 _public member_ `static constexpr bool bIsSupportedType = false;` — Used to short-circuit several calls to minimize noise in the error output of the compiler.
- L331 _public member_ `static constexpr bool bIsSupportedType = true;`
- L332 _public member_ `static constexpr bool bIsFixedSize = true;`
- L333 _public function_ `constexpr static uint32 GetByteSize(NumericType Value)`
- L334 _public function_ `constexpr static uint32 GetElementSize()`
- L335 _public function_ `constexpr static FPrefixInfo CalculatePrefix(int32 CurrentIndex, int32 ByteIndex, NumericType Value)`
- L351 _public member_ `static constexpr bool bIsFixedSize = false;`
- L352 _public prototype_ `constexpr static uint32 GetByteSize(TSortStringView<Casing, T> Value);`
- L353 _public prototype_ `constexpr static uint32 GetElementSize();`
- L354 _public prototype_ `constexpr static FPrefixInfo CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortStringView<Casing, T> Value);`
- L370 _public member_ `static constexpr bool bIsFixedSize = TSortNameView<By>::bIsFixedSize;`
- L371 _public function_ `static uint32 GetByteSize(const TSortNameView<By>& Value)`
- L373 _public function_ `static FPrefixInfo CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortNameView<By> Value)`

#### struct `UE::Editor::DataStorage::TSortTypeInfo`  
`template<SortBy By> struct TSortTypeInfo<TSortNameView<By>>`  
_L367-375_
- L321 _public member_ `static constexpr bool bIsSupportedType = false;` — Used to short-circuit several calls to minimize noise in the error output of the compiler.
- L331 _public member_ `static constexpr bool bIsSupportedType = true;`
- L332 _public member_ `static constexpr bool bIsFixedSize = true;`
- L333 _public function_ `constexpr static uint32 GetByteSize(NumericType Value)`
- L334 _public function_ `constexpr static uint32 GetElementSize()`
- L335 _public function_ `constexpr static FPrefixInfo CalculatePrefix(int32 CurrentIndex, int32 ByteIndex, NumericType Value)`
- L351 _public member_ `static constexpr bool bIsFixedSize = false;`
- L352 _public prototype_ `constexpr static uint32 GetByteSize(TSortStringView<Casing, T> Value);`
- L353 _public prototype_ `constexpr static uint32 GetElementSize();`
- L354 _public prototype_ `constexpr static FPrefixInfo CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortStringView<Casing, T> Value);`
- L370 _public member_ `static constexpr bool bIsFixedSize = TSortNameView<By>::bIsFixedSize;`
- L371 _public function_ `static uint32 GetByteSize(const TSortNameView<By>& Value)`
- L373 _public function_ `static FPrefixInfo CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortNameView<By> Value)`

#### struct `UE::Editor::DataStorage::TSortTypeInfo`  
`template<Private::NameValue NameType> struct TSortTypeInfo<NameType>`  
_L379-384_
- desc: Not a direct specialization, but done through requirements to prevent the compiler from evaluating the static_assert when it's not instanced.
- L321 _public member_ `static constexpr bool bIsSupportedType = false;` — Used to short-circuit several calls to minimize noise in the error output of the compiler.
- L331 _public member_ `static constexpr bool bIsSupportedType = true;`
- L332 _public member_ `static constexpr bool bIsFixedSize = true;`
- L333 _public function_ `constexpr static uint32 GetByteSize(NumericType Value)`
- L334 _public function_ `constexpr static uint32 GetElementSize()`
- L335 _public function_ `constexpr static FPrefixInfo CalculatePrefix(int32 CurrentIndex, int32 ByteIndex, NumericType Value)`
- L351 _public member_ `static constexpr bool bIsFixedSize = false;`
- L352 _public prototype_ `constexpr static uint32 GetByteSize(TSortStringView<Casing, T> Value);`
- L353 _public prototype_ `constexpr static uint32 GetElementSize();`
- L354 _public prototype_ `constexpr static FPrefixInfo CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortStringView<Casing, T> Value);`
- L370 _public member_ `static constexpr bool bIsFixedSize = TSortNameView<By>::bIsFixedSize;`
- L371 _public function_ `static uint32 GetByteSize(const TSortNameView<By>& Value)`
- L373 _public function_ `static FPrefixInfo CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortNameView<By> Value)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L156 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage`)
- L231 _prototype_ `template<SortCase Casing, Private::SortStringViewCopyableType View> TSortStringView(Casing, const View&) -> TSortStringView<Casing, TStringView<typename View::ElementType>>;` (scope `UE::Editor::DataStorage`)
- L233 _prototype_ `template<SortCase Casing> TSortStringView(Casing, const FText&) -> TSortStringView<Casing, FStringView>;` (scope `UE::Editor::DataStorage`)
- L296 _prototype_ `template<SortBy By> TSortNameView(By, const FName&) -> TSortNameView<By>;` (scope `UE::Editor::DataStorage`)
- L299 _prototype_ `template<typename... ValueTypes> FPrefixInfo CreateSortPrefix(uint32 ByteIndex, ValueTypes&&... Values);` (scope `UE::Editor::DataStorage`)
- L308 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage`)
- L311 _prototype_ `template<typename T> constexpr uint64 MoveToLocation(int32 ByteIndex, T Value);` (scope `UE::Editor::DataStorage::Private`)
- L314 _prototype_ `template<typename Numeric> constexpr auto Rebase(Numeric Value);` (scope `UE::Editor::DataStorage::Private`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementSorter.inl` (Public)


#### union `UE::Editor::DataStorage::Private::Rebase::(anonymous)`  
`union`  
_L144-144_

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Editor` (scope `UE`)
- L6 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _function_ `template<typename ColumnType> int32 TColumnSorterInterface<FColumnSorterInterface::ESortType::FixedSize64, ColumnType > ::Compare( const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const` (scope `UE::Editor::DataStorage::TColumnSorterInterface::ESortType::FixedSize64`)
- L20 _function_ `template<typename ColumnType> FPrefixInfo TColumnSorterInterface<FColumnSorterInterface::ESortType::FixedSize64, ColumnType>::CalculatePrefix( const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const` (scope `UE::Editor::DataStorage::TColumnSorterInterface::ESortType::FixedSize64`)
- L28 _function_ `template<typename ColumnType> FColumnSorterInterface::ESortType TColumnSorterInterface<FColumnSorterInterface::ESortType::FixedSize64, ColumnType>::GetSortType() const` (scope `UE::Editor::DataStorage::TColumnSorterInterface::ESortType::FixedSize64`)
- L40 _function_ `template<typename ColumnType> int32 TColumnSorterInterface<FColumnSorterInterface::ESortType::FixedSizeOnly, ColumnType > ::Compare( const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const` (scope `UE::Editor::DataStorage::TColumnSorterInterface::ESortType::FixedSizeOnly`)
- L47 _function_ `template<typename ColumnType> FPrefixInfo TColumnSorterInterface<FColumnSorterInterface::ESortType::FixedSizeOnly, ColumnType>::CalculatePrefix( const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const` (scope `UE::Editor::DataStorage::TColumnSorterInterface::ESortType::FixedSizeOnly`)
- L55 _function_ `template<typename ColumnType> FColumnSorterInterface::ESortType TColumnSorterInterface<FColumnSorterInterface::ESortType::FixedSizeOnly, ColumnType>::GetSortType() const` (scope `UE::Editor::DataStorage::TColumnSorterInterface::ESortType::FixedSizeOnly`)
- L67 _function_ `template<typename ColumnType> int32 TColumnSorterInterface<FColumnSorterInterface::ESortType::ComparativeSort, ColumnType > ::Compare( const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const` (scope `UE::Editor::DataStorage::TColumnSorterInterface::ESortType::ComparativeSort`)
- L79 _function_ `template<typename ColumnType> FPrefixInfo TColumnSorterInterface<FColumnSorterInterface::ESortType::ComparativeSort, ColumnType>::CalculatePrefix( const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const` (scope `UE::Editor::DataStorage::TColumnSorterInterface::ESortType::ComparativeSort`)
- L86 _function_ `template<typename ColumnType> FColumnSorterInterface::ESortType TColumnSorterInterface<FColumnSorterInterface::ESortType::ComparativeSort, ColumnType>::GetSortType() const` (scope `UE::Editor::DataStorage::TColumnSorterInterface::ESortType::ComparativeSort`)
- L97 _function_ `template<typename ColumnType> int32 TColumnSorterInterface<FColumnSorterInterface::ESortType::HybridSort, ColumnType>::Compare( const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const` (scope `UE::Editor::DataStorage::TColumnSorterInterface::ESortType::HybridSort`)
- L109 _function_ `template<typename ColumnType> FPrefixInfo TColumnSorterInterface<FColumnSorterInterface::ESortType::HybridSort, ColumnType>::CalculatePrefix( const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const` (scope `UE::Editor::DataStorage::TColumnSorterInterface::ESortType::HybridSort`)
- L117 _function_ `template<typename ColumnType> FColumnSorterInterface::ESortType TColumnSorterInterface<FColumnSorterInterface::ESortType::HybridSort, ColumnType>::GetSortType() const` (scope `UE::Editor::DataStorage::TColumnSorterInterface::ESortType::HybridSort`)
- L122 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage`)
- L125 _function_ `template<typename T> constexpr uint64 MoveToLocation(int32 ByteIndex, T Value)` (scope `UE::Editor::DataStorage::Private`)
- L135 _function_ `template<typename Numeric> constexpr auto Rebase(Numeric Value)` (scope `UE::Editor::DataStorage::Private`)
- L141 _typedef_ `using SignedInt = std::conditional_t<sizeof(Numeric) == sizeof(double), int64, int32>;` (scope `UE::Editor::DataStorage::Private::Rebase`)
- L142 _typedef_ `using UnsignedInt = std::make_unsigned_t<SignedInt>;` (scope `UE::Editor::DataStorage::Private::Rebase`)
- L144 _member_ `union { Numeric F; UnsignedInt U; } Converter;` (scope `UE::Editor::DataStorage::Private::Rebase::__anonea66c2ed010a`)
- L144 _member_ `union { Numeric F; UnsignedInt U; } Converter;` (scope `UE::Editor::DataStorage::Private::Rebase::__anonea66c2ed010a`)
- L152 _typedef_ `using Unsigned = std::make_unsigned_t<Numeric>;` (scope `UE::Editor::DataStorage::Private::Rebase`)
- L165 _function_ `template<bool bCaseSensitive, typename CharType> CharType ToUpper(CharType Input)` (scope `UE::Editor::DataStorage::Private`)
- L178 _function_ `template<typename ValueType> void CalculatePrefix(FPrefixInfo& Result, int32 CurrentIndex, int32 ByteIndex, const ValueType& Value)` (scope `UE::Editor::DataStorage::Private`)
- L211 _function_ `template<typename ValueType, typename... ValueTypes> void CalculatePrefix(FPrefixInfo& Result, int32 CurrentIndex, int32 ByteIndex, const ValueType& Value, ValueTypes&&... Values)` (scope `UE::Editor::DataStorage::Private`)
- L247 _function_ `template<SortBy By> TSortNameView<By>& TSortNameView<By>::operator=(const FName& Name)` (scope `UE::Editor::DataStorage::TSortNameView`)
- L255 _function_ `template<SortBy By> uint32 TSortNameView<By>::GetByteSize() const` (scope `UE::Editor::DataStorage::TSortNameView`)
- L269 _function_ `template<SortBy By> constexpr uint32 TSortNameView<By>::GetElementSize()` (scope `UE::Editor::DataStorage::TSortNameView`)
- L282 _function_ `template<SortBy By> FPrefixInfo TSortNameView<By>::CalculatePrefix(int32 CurrentIndex, int32 ByteIndex) const` (scope `UE::Editor::DataStorage::TSortNameView`)
- L291 _typedef_ `using StringView = TStringView<typename CompareType::ElementType>;` (scope `UE::Editor::DataStorage::TSortNameView::CalculatePrefix`)
- L292 _typedef_ `using SortStringView = TSortStringView<FSortCaseInsensitive, StringView>;` (scope `UE::Editor::DataStorage::TSortNameView::CalculatePrefix`)
- L298 _function_ `template<SortBy By> int32 TSortNameView<By>::Compare(const FName& Lhs, const FName& Rhs) const` (scope `UE::Editor::DataStorage::TSortNameView`)
- L307 _function_ `` (scope `UE::Editor::DataStorage::TSortNameView::Compare`)
- L338 _function_ `template<SortBy By> int32 TSortNameView<By>::Compare(const FName& Rhs) const` (scope `UE::Editor::DataStorage::TSortNameView`)
- L344 _function_ `template<SortBy By> int32 TSortNameView<By>::Compare(const TSortNameView& Rhs) const` (scope `UE::Editor::DataStorage::TSortNameView`)
- L352 _function_ `template<SortBy By> bool TSortNameView<By>::operator==(const TSortNameView& Rhs) const` (scope `UE::Editor::DataStorage::TSortNameView`)
- L358 _function_ `template<SortBy By> bool TSortNameView<By>::operator!=(const TSortNameView& Rhs) const` (scope `UE::Editor::DataStorage::TSortNameView`)
- L364 _function_ `template<SortBy By> bool TSortNameView<By>::operator< (const TSortNameView& Rhs) const` (scope `UE::Editor::DataStorage::TSortNameView`)
- L370 _function_ `template<SortBy By> bool TSortNameView<By>::operator<=(const TSortNameView& Rhs) const` (scope `UE::Editor::DataStorage::TSortNameView`)
- L376 _function_ `template<SortBy By> bool TSortNameView<By>::operator> (const TSortNameView& Rhs) const` (scope `UE::Editor::DataStorage::TSortNameView`)
- L382 _function_ `template<SortBy By> bool TSortNameView<By>::operator>=(const TSortNameView& Rhs) const` (scope `UE::Editor::DataStorage::TSortNameView`)
- L388 _function_ `template<SortBy By> void TSortNameView<By>::CacheCompareType() const` (scope `UE::Editor::DataStorage::TSortNameView`)
- L425 _function_ `template<SortCase Casing, typename T> constexpr uint32 TSortTypeInfo<TSortStringView<Casing, T>>::GetByteSize(TSortStringView<Casing, T> Value)` (scope `UE::Editor::DataStorage::TSortTypeInfo`)
- L431 _function_ `template<SortCase Casing, typename T> constexpr uint32 TSortTypeInfo<TSortStringView<Casing, T>>::GetElementSize()` (scope `UE::Editor::DataStorage::TSortTypeInfo`)
- L437 _function_ `template<SortCase Casing, typename T> constexpr FPrefixInfo TSortTypeInfo<TSortStringView<Casing, T>>::CalculatePrefix( int32 CurrentIndex, int32 ByteIndex, TSortStringView<Casing, T> Value)` (scope `UE::Editor::DataStorage::TSortTypeInfo`)
- L502 _function_ `template<typename... ValueTypes> FPrefixInfo CreateSortPrefix(uint32 ByteIndex, ValueTypes&&... Values)` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Framework/TypedElementUtil.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace TypedElementUtil`
- L22 _prototype_ `void BatchElementsByType(FTypedElementListConstRef InElementsToBatch, TMap<FTypedHandleTypeId, TArray<FTypedElementHandle>>& OutElementsByType);` (scope `TypedElementUtil`) — Batch the given elements by their type.
- L23 _prototype_ `void BatchElementsByType(TArrayView<const FTypedElementHandle> InElementsToBatch, TMap<FTypedHandleTypeId, TArray<FTypedElementHandle>>& OutElementsByType);` (scope `TypedElementUtil`)
- L25 _prototype_ `TArray<FScriptTypedElementHandle> ConvertToScriptElementArray(const TArray<FTypedElementHandle>& InNativeHandles, UTypedElementRegistry* Registry);` (scope `TypedElementUtil`)
- L26 _prototype_ `TArray<FTypedElementHandle> ConvertToNativeElementArray(const TArray<FScriptTypedElementHandle>& InScriptHandles);` (scope `TypedElementUtil`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Interfaces/Capabilities/TypedElementUiStyleOverrideCapability.h` (Public)


#### class `PRAGMA_DISABLE_DEPRECATION_WARNINGS`  
`PRAGMA_DISABLE_DEPRECATION_WARNINGS : public ITypedElementUiCapability PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L15-27_
- inherits: `ITypedElementUiCapabilityPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L21 _public prototype_ `SLATE_METADATA_TYPE(ITypedElementUiStyleOverrideCapability, ITypedElementUiCapability) PRAGMA_ENABLE_DEPRECATION_WARNINGS ~ITypedElementUiStyleOverrideCapability() override = default;`
- L26 _public prototype_ `virtual void SetForegroundColor(const TAttribute<FSlateColor>& InColorAndOpacity) = 0;`
- L37 _public function_ `explicit TTypedElementUiStyleOverrideCapability(WidgetType& InWidget) : Widget(InWidget)`
- L39 _public function_ `virtual void SetForegroundColor(const TAttribute<FSlateColor>& InColorAndOpacity) override`
- L45 _private member_ `WidgetType& Widget;`

#### class `PRAGMA_DISABLE_DEPRECATION_WARNINGS`  
`PRAGMA_DISABLE_DEPRECATION_WARNINGS : public ITypedElementUiStyleOverrideCapability PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L32-46_
- inherits: `ITypedElementUiStyleOverrideCapabilityPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L21 _public prototype_ `SLATE_METADATA_TYPE(ITypedElementUiStyleOverrideCapability, ITypedElementUiCapability) PRAGMA_ENABLE_DEPRECATION_WARNINGS ~ITypedElementUiStyleOverrideCapability() override = default;`
- L26 _public prototype_ `virtual void SetForegroundColor(const TAttribute<FSlateColor>& InColorAndOpacity) = 0;`
- L37 _public function_ `explicit TTypedElementUiStyleOverrideCapability(WidgetType& InWidget) : Widget(InWidget)`
- L39 _public function_ `virtual void SetForegroundColor(const TAttribute<FSlateColor>& InColorAndOpacity) override`
- L45 _private member_ `WidgetType& Widget;`

### `Source/Runtime/TypedElementFramework/Public/Elements/Interfaces/Capabilities/TypedElementUiTextCapability.h` (Public)


#### class `PRAGMA_DISABLE_DEPRECATION_WARNINGS`  
`PRAGMA_DISABLE_DEPRECATION_WARNINGS : public ITypedElementUiCapability PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L14-28_
- inherits: `ITypedElementUiCapabilityPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L20 _public prototype_ `SLATE_METADATA_TYPE(ITypedElementUiTextCapability, ITypedElementUiCapability) PRAGMA_ENABLE_DEPRECATION_WARNINGS ~ITypedElementUiTextCapability() override = default;`
- L25 _public prototype_ `virtual void SetText(const TAttribute<FText>& Text) = 0;`
- L27 _public prototype_ `virtual void SetHighlightText(const TAttribute<FText>& Text) = 0;`
- L38 _public function_ `explicit TTypedElementUiTextCapability(WidgetType& InWidget) : Widget(InWidget)`
- L40 _public function_ `void SetText(const TAttribute<FText>& Text) override`
- L45 _public function_ `void SetHighlightText(const TAttribute<FText>& Text) override`
- L51 _private member_ `WidgetType& Widget;`

#### class `PRAGMA_DISABLE_DEPRECATION_WARNINGS`  
`PRAGMA_DISABLE_DEPRECATION_WARNINGS : public ITypedElementUiTextCapability PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L33-52_
- inherits: `ITypedElementUiTextCapabilityPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L20 _public prototype_ `SLATE_METADATA_TYPE(ITypedElementUiTextCapability, ITypedElementUiCapability) PRAGMA_ENABLE_DEPRECATION_WARNINGS ~ITypedElementUiTextCapability() override = default;`
- L25 _public prototype_ `virtual void SetText(const TAttribute<FText>& Text) = 0;`
- L27 _public prototype_ `virtual void SetHighlightText(const TAttribute<FText>& Text) = 0;`
- L38 _public function_ `explicit TTypedElementUiTextCapability(WidgetType& InWidget) : Widget(InWidget)`
- L40 _public function_ `void SetText(const TAttribute<FText>& Text) override`
- L45 _public function_ `void SetHighlightText(const TAttribute<FText>& Text) override`
- L51 _private member_ `WidgetType& Widget;`

### `Source/Runtime/TypedElementFramework/Public/Elements/Interfaces/Capabilities/TypedElementUiTooltipCapability.h` (Public)


#### class `PRAGMA_DISABLE_DEPRECATION_WARNINGS`  
`PRAGMA_DISABLE_DEPRECATION_WARNINGS : public ITypedElementUiCapability PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L15-33_
- inherits: `ITypedElementUiCapabilityPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L21 _public prototype_ `SLATE_METADATA_TYPE(ITypedElementUiTooltipCapability, ITypedElementUiCapability) PRAGMA_ENABLE_DEPRECATION_WARNINGS ~ITypedElementUiTooltipCapability() override = default;`
- L26 _public prototype_ `virtual void SetToolTipText(const TAttribute<FText>& ToolTipText) = 0;`
- L27 _public prototype_ `virtual void SetToolTipText(const FText& ToolTipText) = 0;`
- L28 _public prototype_ `virtual void SetToolTip(const TAttribute<TSharedPtr<IToolTip>>& ToolTip) = 0;`
- L29 _public prototype_ `virtual TSharedPtr<IToolTip> GetToolTip() = 0;`
- L31 _public prototype_ `virtual void EnableToolTipForceField(const bool bEnableForceField) = 0;`
- L32 _public prototype_ `virtual bool HasToolTipForceField() const = 0;`
- L43 _public function_ `explicit TTypedElementUiTooltipCapability(WidgetType& InWidget) : Widget(InWidget)`
- L45 _public function_ `void SetToolTipText(const TAttribute<FText>& ToolTipText) override`
- L50 _public function_ `void SetToolTipText(const FText& ToolTipText) override`
- L55 _public function_ `void SetToolTip(const TAttribute<TSharedPtr<IToolTip>>& ToolTip) override`
- L60 _public function_ `TSharedPtr<IToolTip> GetToolTip() override`
- L65 _public function_ `void EnableToolTipForceField(const bool bEnableForceField) override`
- L70 _public function_ `bool HasToolTipForceField() const override`
- L76 _private member_ `WidgetType& Widget;`

#### class `PRAGMA_DISABLE_DEPRECATION_WARNINGS`  
`PRAGMA_DISABLE_DEPRECATION_WARNINGS : public ITypedElementUiTooltipCapability PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L38-77_
- inherits: `ITypedElementUiTooltipCapabilityPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L21 _public prototype_ `SLATE_METADATA_TYPE(ITypedElementUiTooltipCapability, ITypedElementUiCapability) PRAGMA_ENABLE_DEPRECATION_WARNINGS ~ITypedElementUiTooltipCapability() override = default;`
- L26 _public prototype_ `virtual void SetToolTipText(const TAttribute<FText>& ToolTipText) = 0;`
- L27 _public prototype_ `virtual void SetToolTipText(const FText& ToolTipText) = 0;`
- L28 _public prototype_ `virtual void SetToolTip(const TAttribute<TSharedPtr<IToolTip>>& ToolTip) = 0;`
- L29 _public prototype_ `virtual TSharedPtr<IToolTip> GetToolTip() = 0;`
- L31 _public prototype_ `virtual void EnableToolTipForceField(const bool bEnableForceField) = 0;`
- L32 _public prototype_ `virtual bool HasToolTipForceField() const = 0;`
- L43 _public function_ `explicit TTypedElementUiTooltipCapability(WidgetType& InWidget) : Widget(InWidget)`
- L45 _public function_ `void SetToolTipText(const TAttribute<FText>& ToolTipText) override`
- L50 _public function_ `void SetToolTipText(const FText& ToolTipText) override`
- L55 _public function_ `void SetToolTip(const TAttribute<TSharedPtr<IToolTip>>& ToolTip) override`
- L60 _public function_ `TSharedPtr<IToolTip> GetToolTip() override`
- L65 _public function_ `void EnableToolTipForceField(const bool bEnableForceField) override`
- L70 _public function_ `bool HasToolTipForceField() const override`
- L76 _private member_ `WidgetType& Widget;`

### `Source/Runtime/TypedElementFramework/Public/Elements/Interfaces/DecoratorWidgetConstructor.h` (Public)


#### struct `FTedsDecoratorWidgetConstructor`  
`struct FTedsDecoratorWidgetConstructor : public FTedsWidgetConstructorBase`  
_L20-50_
- reflection: `USTRUCT()`
- inherits: `FTedsWidgetConstructorBase`
- desc: Base class used to for decorator widgets in TEDS UI. A decorator widget is appended to regular TEDS UI widgets to provide additional functionality such as UI effects, context menus etc A decorator widget constructor can be registered against a specific purpose and column using IUiProvider. They will then be automatically added to any widgets where the widget row matches the purpose and column (both on creation and dynamically post creation)
- L25 _public prototype_ `explicit FTedsDecoratorWidgetConstructor(const UScriptStruct* InTypeInfo);`
- L26 _public function_ `explicit FTedsDecoratorWidgetConstructor(EForceInit) : FTedsWidgetConstructorBase(ForceInit)` — For compatibility and shouldn't be directly used.
- L28 _public prototype_ `virtual ~FTedsDecoratorWidgetConstructor() = default;`
- L39 _public prototype_ `virtual TSharedPtr<SWidget> CreateDecoratorWidget( TSharedPtr<SWidget> InChildWidget, UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle DataRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments);` — Construct a decorator widget that wraps InChildWidget @param InChildWidget The actual internal widget, it is expected that the decorator widget you create contains this widget as a child @param DataStorage Pointer to the TEDS interface @param DataStorageUi Pointer to the TEDS UI interface @param DataRow The row containing the actual data InChildWidget was created to observe (e.g Actor row) @param WidgetRow The row containing UI specific data about InChildWidget (e.g widget color) @param Arguments Any metadata arguments specified when requesting this decorator
- L49 _protected member_ `TWeakObjectPtr<const UScriptStruct> TypeInfo = nullptr;` — The constructor's typeinfo

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FTedsDecoratorWidgetConstructor> : public TStructOpsTypeTraitsBase2<FTedsDecoratorWidgetConstructor>`  
_L53-60_
- inherits: `TStructOpsTypeTraitsBase2<FTedsDecoratorWidgetConstructor>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L56-59_

#### Free symbols / members of external scopes

- L57 _enumerator_ `WithNoInitConstructor = true` (scope `TStructOpsTypeTraits::__anonadc7af660103`)
- L58 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anonadc7af660103`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Interfaces/TypedElementDataStorageCompatibilityInterface.h` (Public)


#### class `UE::Editor::DataStorage::ICompatibilityProvider`  
`class ICompatibilityProvider : public IModularFeature`  
_L24-130_
- inherits: `IModularFeature`
- desc: Interface to provide compatibility with existing systems that don't directly support the data storage.
- L28 _public typedef_ `using ObjectRegistrationFilter = TFunction<bool(const ICompatibilityProvider&, const UObject*)>;`
- L29 _public typedef_ `using ObjectToRowDealiaser = TFunction<RowHandle(const ICompatibilityProvider&, const UObject*)>;`
- L31 _public member_ `inline static const FName ObjectMappingDomain = "Ob`
- L46 _public prototype_ `template<typename ObjectType> RowHandle AddCompatibleObject(ObjectType&& Object);` — Adds a reference to an existing object to the data storage. The data storage does NOT take ownership of the object and the caller is responsible for managing the life cycle of the object. The address is only used for associating the object with a row and to setup the initial row data.
- L50 _public prototype_ `template<typename ObjectType> void RemoveCompatibleObject(ObjectType&& Object);` — Removes a previously registered object from the data storage.
- L53 _public prototype_ `template<typename ObjectType> RowHandle FindRowWithCompatibleObject(ObjectType&& Object) const;`
- L65 _public prototype_ `virtual void RegisterRegistrationFilter(ObjectRegistrationFilter Filter) = 0;` — Objects like actors are registered through the compatibility layer in bulk. This can lead to objects being added that cause conflicts with other data in the data storage. This callback offers the opportunity to inspect the objects that are being added and if they include an object that shouldn't be store it can filter them out.
- L72 _public prototype_ `virtual void RegisterDealiaserCallback(ObjectToRowDealiaser Dealiaser) = 0;` — Notifications and request can be made to the compatibility layer for objects that are stored but don't directly map to a row. An example is a UObject represented by a column. If the UObject gets updated there's no direct mapping to the row the column is stored in but the row still needs to be updated. For cases like this it's possible to store information to find the row that's being aliased.
- L78 _public prototype_ `virtual void RegisterTypeTableAssociation(TWeakObjectPtr<UStruct> TypeInfo, TableHandle Table) = 0;` — Allows a specific type to be associated with a table. Whenever a compatible object is added, the type information of that object will be used to find the closest match in the registered types and use the associated table. E.g. actors derive from uobjects so if the type information of an actor is registered the actor table will be used instead of the uobject table.
- L86 _public prototype_ `virtual RowHandle AddCompatibleObjectExplicit(UObject* Object) = 0;` — Adds a UObject to the data storage.
- L88 _public prototype_ `virtual RowHandle AddCompatibleObjectExplicit(void* Object, TWeakObjectPtr<const UScriptStruct> TypeInfo) = 0;` — Adds an FStruct to the data storage.
- L91 _public prototype_ `virtual void RemoveCompatibleObjectExplicit(UObject* Object) = 0;` — Removes a UObject from the data storage.
- L93 _public prototype_ `virtual void RemoveCompatibleObjectExplicit(void* Object) = 0;` — Removes an FStruct from the data storage.
- L96 _public prototype_ `virtual RowHandle FindRowWithCompatibleObjectExplicit(const UObject* Object) const = 0;` — Finds a previously stored UObject. If not found an invalid row handle will be returned.
- L98 _public prototype_ `virtual RowHandle FindRowWithCompatibleObjectExplicit(const void* Object) const = 0;` — Finds a previously stored FStruct. If not found an invalid row handle will be returned.
- L105 _public prototype_ `virtual bool SupportsExtension(FName Extension) const = 0;` — Check if a custom extension is supported. This can be used to check for in-development features, custom extensions, etc.
- L107 _public prototype_ `virtual void ListExtensions(TFunctionRef<void(FName)> Callback) const = 0;` — Provides a list of all extensions that are enabled.
- L127 _protected prototype_ `virtual void EnterImmediateMode(FObjectCompatibilityImmediateScope& Scope) = 0;`
- L129 _protected prototype_ `virtual void LeaveImmediateMode(FObjectCompatibilityImmediateScope& Scope) = 0;`
- L258 _function_ `template<typename ObjectType> RowHandle ICompatibilityProvider::AddCompatibleObject(ObjectType&& Object)`
- L274 _function_ `template<typename ObjectType> void ICompatibilityProvider::RemoveCompatibleObject(ObjectType&& Object)`
- L280 _function_ `template<typename ObjectType> RowHandle ICompatibilityProvider::FindRowWithCompatibleObject(ObjectType&& Object) const`

#### struct `UE::Editor::DataStorage::ICompatibilityProvider::FObjectCompatibilityImmediateScopeWriteAccess`  
`struct UE_INTERNAL FObjectCompatibilityImmediateScopeWriteAccess`  
_L114-125_
- L116 _public prototype_ `static void RegisterObject(FObjectCompatibilityImmediateScope& Scope, void* Object, const UScriptStruct* TypeInfo, RowHandle Row);`
- L118 _public prototype_ `static void SetPrevious(FObjectCompatibilityImmediateScope& Scope, FObjectCompatibilityImmediateScope* InPrevious);`
- L119 _public prototype_ `static FObjectCompatibilityImmediateScope* GetPrevious(const FObjectCompatibilityImmediateScope& Scope);`
- L121 _public prototype_ `static void ListUObjects(const FObjectCompatibilityImmediateScope& Scope, TFunctionRef<void(RowHandle, UObject*, const UClass*)> Callback);`
- L123 _public prototype_ `static void ListExternalObjects(const FObjectCompatibilityImmediateScope& Scope, TFunctionRef<void(RowHandle, void*, const UScriptStruct*)> Callback);`
- L193 _function_ `inline void ICompatibilityProvider::FObjectCompatibilityImmediateScopeWriteAccess::RegisterObject( FObjectCompatibilityImmediateScope& Scope, void* Object, const UScriptStruct* TypeInfo, RowHandle Row)`
- L206 _function_ `inline void ICompatibilityProvider::FObjectCompatibilityImmediateScopeWriteAccess::SetPrevious( FObjectCompatibilityImmediateScope& Scope, FObjectCompatibilityImmediateScope* InPrevious)`
- L213 _function_ `inline FObjectCompatibilityImmediateScope* ICompatibilityProvider::FObjectCompatibilityImmediateScopeWriteAccess::GetPrevious( const FObjectCompatibilityImmediateScope& Scope)`
- L219 _function_ `inline void ICompatibilityProvider::FObjectCompatibilityImmediateScopeWriteAccess::ListUObjects( const FObjectCompatibilityImmediateScope& Scope, TFunctionRef<void(RowHandle, UObject*, const UClass*)> Callback)`
- L231 _function_ `inline void ICompatibilityProvider::FObjectCompatibilityImmediateScopeWriteAccess::ListExternalObjects( const FObjectCompatibilityImmediateScope& Scope, TFunctionRef<void(RowHandle, void*, const UScriptStruct*)> Callback)`

#### class `UE::Editor::DataStorage::FObjectCompatibilityImmediateScope`  
`class UE_INTERNAL FObjectCompatibilityImmediateScope`  
_L145-167_
- desc: Scope object to tell TEDS Compatibility that any objects being registered on that thread with this scope should be immediately registered instead of queued up once this goes out of scope. Scopes can be nested and are able to provide the row handles to the objects that have been newly or previously registered. The scope is local to the calling thread so other threads will continue to queue registrations. The immediate mode limits how much batch and distributed registration TEDS Compatibility can do. Avoid using this scope when possible and prefer to limit the use to a small number of objects. This scope was introduced to aid the transition to the multi-threaded environment TEDS provides and as such this scope may be removed in the future. Warning: This scope is to aid the transition of existing single-threaded systems over to the editor data storage.
- L151 _public prototype_ `explicit FObjectCompatibilityImmediateScope(ICompatibilityProvider& InCompatibility);`
- L152 _public prototype_ `~FObjectCompatibilityImmediateScope();`
- L154 _public prototype_ `RowHandle FindObject(const void* Object) const;`
- L155 _public prototype_ `int32 GetObjectCount() const;`
- L164 _private member_ `TArray<ObjectInfoType> Objects;`
- L165 _private member_ `FObjectCompatibilityImmediateScope* Previous = nullptr;`
- L166 _private member_ `ICompatibilityProvider& Compatibility;`
- L175 _function_ `inline FObjectCompatibilityImmediateScope::FObjectCompatibilityImmediateScope(ICompatibilityProvider& InCompatibility) : Compatibility(InCompatibility)`
- L181 _function_ `inline FObjectCompatibilityImmediateScope::~FObjectCompatibilityImmediateScope()`
- L186 _function_ `inline RowHandle FObjectCompatibilityImmediateScope::FindObject(const void* Object) const`
- L191 _function_ `inline int32 FObjectCompatibilityImmediateScope::GetObjectCount() const`

#### struct `UE::Editor::DataStorage::FObjectCompatibilityImmediateScope::ObjectInfoType`  
`struct ObjectInfoType`  
_L158-163_
- L160 _public member_ `void* Address;`
- L161 _public member_ `const UScriptStruct* TypeInfo;` — If this is null, Address points to a UObject.
- L162 _public member_ `RowHandle Row;`

#### struct `UE::Editor::DataStorage::TTypedElementSubsystemTraits`  
`template<typename Subsystem> struct TTypedElementSubsystemTraits final`  
_L286-339_
- L310 _public function_ `static constexpr bool RequiresGameThread()`
- L325 _public function_ `static constexpr bool IsHotReloadable()`

#### struct `UE::Editor::DataStorage::TTypedElementSubsystemTraits::HasRequiresGameThreadVariable`  
`template<typename T, typename = void> struct HasRequiresGameThreadVariable`  
_L289-292_
- L291 _public member_ `static constexpr bool bAvailable = false;`
- L296 _public member_ `static constexpr bool bAvailable = true;`

#### struct `UE::Editor::DataStorage::TTypedElementSubsystemTraits::HasRequiresGameThreadVariable`  
`template<typename T> struct HasRequiresGameThreadVariable <T, decltype((void)T::bRequiresGameThread)>`  
_L294-297_
- L291 _public member_ `static constexpr bool bAvailable = false;`
- L296 _public member_ `static constexpr bool bAvailable = true;`

#### struct `UE::Editor::DataStorage::TTypedElementSubsystemTraits::HasIsHotReloadableVariable`  
`template<typename T, typename = void> struct HasIsHotReloadableVariable`  
_L300-303_
- L302 _public member_ `static constexpr bool bAvailable = false;`
- L307 _public member_ `static constexpr bool bAvailable = true;`

#### struct `UE::Editor::DataStorage::TTypedElementSubsystemTraits::HasIsHotReloadableVariable`  
`template<typename T> struct HasIsHotReloadableVariable <T, decltype((void)T::bIsHotReloadable)>`  
_L305-308_
- L302 _public member_ `static constexpr bool bAvailable = false;`
- L307 _public member_ `static constexpr bool bAvailable = true;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L188 _function_ `const ObjectInfoType* Result = Objects.FindByPredicate([Object](const ObjectInfoType& Info) { return Info.Address == Object; });` (scope `UE::Editor::DataStorage::FObjectCompatibilityImmediateScope::FindObject`)
- L245 _function_ `template<typename Type> Type* GetRawPointer(const TWeakObjectPtr<Type> Object)` (scope `UE::Editor::DataStorage`)
- L249 _function_ `template<typename Type> Type* GetRawPointer(const TObjectPtr<Type> Object)` (scope `UE::Editor::DataStorage`)
- L250 _function_ `template<typename Type> Type* GetRawPointer(const TStrongObjectPtr<Type> Object)` (scope `UE::Editor::DataStorage`)
- L252 _function_ `template<typename Type> Type* GetRawPointer(TNotNull<Type*> Object)` (scope `UE::Editor::DataStorage`)
- L254 _function_ `template<typename Type> Type* GetRawPointer(Type* Object)` (scope `UE::Editor::DataStorage`)
- L261 _typedef_ `using BaseType = std::remove_cv_t<std::remove_pointer_t<decltype(RawPointer)>>;` (scope `UE::Editor::DataStorage::ICompatibilityProvider::AddCompatibleObject`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Interfaces/TypedElementDataStorageFactory.h` (Public)


#### class `UEditorDataStorageFactory`  
`class UEditorDataStorageFactory : public UObject`  
_L19-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base class that can be used to register various elements, such as queries and widgets, with the Editor Data Storage.
- L24 _public prototype_ `~UEditorDataStorageFactory() override = default;`
- L30 _public function_ `virtual uint8 GetOrder() const` — Returns the order registration will be executed. Factories with a lower number will be executed before factories with a higher number.
- L35 _public function_ `virtual void PreRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage)` — All factories will have this called before any Register functions on any factories are called
- L40 _public function_ `virtual void PostRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage)` — All factories will have this called after every Register functions on all factories are called
- L42 _public function_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage)`
- L43 _public function_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::ICompatibilityProvider& DataStorageCompatibility)`
- L44 _public function_ `virtual void RegisterTickGroups(UE::Editor::DataStorage::ICoreProvider& DataStorage) const`
- L45 _public function_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage)`
- L47 _public function_ `virtual void RegisterHierarchies(UE::Editor::DataStorage::ICoreProvider& DataStorage)`
- L49 _public function_ `virtual void RegisterRegistrationFilters(UE::Editor::DataStorage::ICompatibilityProvider& DataStorageCompatibility) const`
- L50 _public function_ `virtual void RegisterDealiaser(UE::Editor::DataStorage::ICompatibilityProvider& DataStorageCompatibility) const`
- L52 _public function_ `virtual void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const`
- L53 _public function_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const`
- L61 _public function_ `virtual void RegisterPropertySearchers(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const` — Used to register searchers for a specific property type to be used in the default generated property searcher. The widget constructor can be used to provide a custom searcher if more complex searching logic is needed. Implementations of this function should mostly be calling `RegisterSearcherGeneratorForProperty` on the UI provider.
- L68 _public function_ `virtual void RegisterPropertySorters(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const` — Used to register sorters for a specific property type to be used in the default generated property sorter. The widget constructor can be used to provide a custom sorter if more complex sorting logic is needed. Implementations of this function should mostly be calling `RegisterSorterGeneratorForProperty` on the UI provider.
- L73 _public function_ `virtual void PreShutdown(UE::Editor::DataStorage::ICoreProvider& DataStorage)` — Called in reverse order before the DataStorage object is shut down

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Interfaces/TypedElementDataStorageInterface.h` (Public)


#### struct `UE::Editor::DataStorage::TTypedElementColumnTypeList`  
`template<TColumnType... Columns> struct TTypedElementColumnTypeList`  
_L49-54_
- desc: Convenience structure that can be used to pass a list of columns to functions that don't have an dedicate templated version that takes a column list directly, for instance when multiple column lists are used. Note that the returned array view is only available while this object is constructed, so care must be taken with functions that return a const array view.
- L51 _public member_ `const UScriptStruct* ColumnTypes[sizeof...(Columns)] = { Columns::StaticStruct()... };`
- L53 _public function_ `operator TConstArrayView<const UScriptStruct*>() const`

#### struct `UE::Editor::DataStorage::FHierarchyRegistrationParams`  
`struct FHierarchyRegistrationParams`  
_L56-77_
- L58 _public member_ `FName Name;`
- L63 _public member_ `bool bEnableParentChangedColumn = false;` — Optionally add a column to any row participating in the hierarchy if its parent changes (useful for change detection). This behaves similar to the sync tags and is removed at the end of the frame. For the Relations backend this maps to bEnableSubjectChangedColumn on the underlying relation type.
- L66 _public member_ `const UScriptStruct* ParentChangedColumn = nullptr;` — `UE_DEPRECATED(5.8, "Providing an explicit column has been deprecated, use the bool argument + ICoreProvider::GetParentChangedColumn()")`
- L76 _public member_ `EBackend Backend = EBackend::Legacy;`

#### enum `UE::Editor::DataStorage::FHierarchyRegistrationParams::EBackend`  
`enum class EBackend : uint8`  
_L69-75_
- desc: Selects which storage backend implements this hierarchy.
- L72 _public enumerator_ `Legacy` — Column-on-row storage (FTedsHierarchyRegistrar). Existing behavior.
- L74 _public enumerator_ `Relations` — Relation-row storage with interval encoding for O(1) descendant queries.

#### struct `UE::Editor::DataStorage::FTedsRelationRoleTraits`  
`struct FTedsRelationRoleTraits`  
_L82-103_
- desc: Configuration for a role (Subject or Object) in a relation type.
- L88 _public member_ `bool bExclusive = false;` — Whether only one entity can hold this role per relation. For hierarchies: Object (parent) is typically exclusive (one parent per child).
- L102 _public member_ `EDestructionPolicy DestructionPolicy = EDestructionPolicy::CleanUp;`

#### enum `UE::Editor::DataStorage::FTedsRelationRoleTraits::EDestructionPolicy`  
`enum class EDestructionPolicy : uint8`  
_L93-101_
- desc: Policy for what happens when the entity in this role is destroyed.
- L96 _public enumerator_ `CleanUp` — Just remove the relation row, leave other participant unchanged
- L98 _public enumerator_ `Cascade` — Destroy the entity in the other role (e.g., destroy child when parent is deleted)
- L100 _public enumerator_ `Orphan` — Leave the other participant without relation (orphan it)

#### enum `UE::Editor::DataStorage::EHierarchyMode`  
`enum class EHierarchyMode : uint8`  
_L106-115_
- desc: Controls how hierarchical queries (IsDescendantOf, etc.) are implemented for a relation type.
- L109 _public enumerator_ `Disabled` — Not a hierarchy. Hierarchical APIs are not available.
- L111 _public enumerator_ `WalkOnly` — IsDescendantOf walks the parent chain. Always correct, O(depth).
- L114 _public enumerator_ `IntervalEncoded` — IsDescendantOf uses interval encoding for O(1) checks. Falls back to walk when intervals are stale; intervals are automatically refreshed at frame end. Recommended for dynamic hierarchies.

#### struct `UE::Editor::DataStorage::FTedsRelationTraits`  
`struct FTedsRelationTraits`  
_L121-138_
- desc: Configuration for registering a new relation type. Relation types define how two rows can be connected.
- L124 _public member_ `FTedsRelationRoleTraits Subject;` — Configuration for the Subject role (the "from" / "child" side)
- L127 _public member_ `FTedsRelationRoleTraits Object;` — Configuration for the Object role (the "to" / "parent" side)
- L130 _public member_ `EHierarchyMode HierarchyMode = EHierarchyMode::Disabled;` — Selects how hierarchical descendant queries are implemented for this relation type.
- L137 _public member_ `int64 IntervalGap = 1000;` — Initial gap between interval values for new nodes. Larger gaps allow more insertions before rebalancing is needed. Only used when HierarchyMode is IntervalEncoded.

#### struct `UE::Editor::DataStorage::FRelationRegistrationParams`  
`struct FRelationRegistrationParams`  
_L143-165_
- desc: Parameters for registering a relation type.
- L146 _public member_ `FName Name;` — Unique name for this relation type
- L149 _public member_ `FTedsRelationTraits Traits;` — Relation type configuration
- L157 _public member_ `bool bEnableSubjectChangedColumn = false;` — When true, a tag column is stamped on the Subject row whenever a relation of this type is created or destroyed with that row as Subject. The column is removed at FrameEnd. Retrieve the column type via ICoreProvider::GetRelationSubjectChangedColumn. Use with FObserver::OnAdd or a FProcessor Where().All(col) for change detection.
- L164 _public member_ `bool bEnableObjectChangedColumn = false;` — When true, a tag column is stamped on the Object row whenever a relation of this type is created or destroyed with that row as Object. The column is removed at FrameEnd. Retrieve the column type via ICoreProvider::GetRelationObjectChangedColumn.

#### class `UE::Editor::DataStorage::ICoreProvider`  
`class ICoreProvider : public Queries::ITableInfo< Queries::ITableManagement< Queries::IDynamicColumnInfo< IModularFeature>>>`  
_L167-1026_
- inherits: `Queries::ITableInfo<Queries::ITableManagement<Queries::IDynamicColumnInfo<IModularFeature>>>`
- L182 _public prototype_ `virtual const UEditorDataStorageFactory* FindFactory(const UClass* FactoryType) const = 0;` — Finds a factory instance registered with TEDS
- L184 _public prototype_ `virtual UEditorDataStorageFactory* FindFactory(const UClass* FactoryType) = 0;`
- L188 _public prototype_ `template<typename FactoryT> const FactoryT* FindFactory() const;` — Convenience function for FindFactory
- L191 _public prototype_ `template<typename FactoryT> FactoryT* FindFactory();`
- L197 _public prototype_ `virtual RowHandle ReserveRow() = 0;` — Reserves a row to be assigned to a table at a later point. If the row is no longer needed before it's been assigned to a table, it should still be released with RemoveRow.
- L204 _public prototype_ `virtual void BatchReserveRows(int32 Count, TFunctionRef<void(RowHandle)> ReservationCallback) = 0;` — Reserve multiple rows at once to be assigned to a table at a later point. If multiple rows are needed, the batch version will generally have better performance. If a row is no longer needed before it's been assigned to a table, it should still be released with RemoveRow. The reservation callback will be called once per reserved row.
- L211 _public prototype_ `virtual void BatchReserveRows(TArrayView<RowHandle> ReservedRows) = 0;` — Reserve multiple rows at once to be assigned to a table at a later point. If multiple rows are needed, the batch version will generally have better performance. If a row is no longer needed before it's been assigned to a table, it should still be released with RemoveRow. The provided range will be have its values set to the reserved row handles.
- L214 _public prototype_ `virtual RowHandle AddRow(TableHandle Table) = 0;` — Adds a new row to the provided table.
- L219 _public prototype_ `virtual RowHandle AddRow(TableHandle Table, RowCreationCallbackRef OnCreated) = 0;` — Adds a new row to the provided table. Callers are expected to use the callback to initialize the row if needed.
- L221 _public prototype_ `virtual bool AddRow(RowHandle ReservedRow, TableHandle Table) = 0;` — Adds a new row to the provided table using a previously reserved row.
- L226 _public prototype_ `virtual bool AddRow(RowHandle ReservedRow, TableHandle Table, RowCreationCallbackRef OnCreated) = 0;` — Adds a new row to the provided table using a previously reserved row. Callers are expected to use the callback to initialize the row if needed.
- L232 _public prototype_ `virtual bool BatchAddRow(TableHandle Table, int32 Count, RowCreationCallbackRef OnCreated) = 0;` — Add multiple rows at once. For each new row the OnCreated callback is called. Callers are expected to use the callback to initialize the row if needed.
- L238 _public prototype_ `virtual bool BatchAddRow(TableHandle Table, TConstArrayView<RowHandle> ReservedHandles, RowCreationCallbackRef OnCreated) = 0;` — Add multiple rows at once. For each new row the OnCreated callback is called. Callers are expected to use the callback to initialize the row if needed. This version uses a set of previously reserved rows. Any row that can't be used will be released.
- L241 _public prototype_ `virtual void RemoveRow(RowHandle Row) = 0;` — Removes a previously reserved or added row. If the row handle is invalid or already removed, nothing happens
- L244 _public prototype_ `virtual void BatchRemoveRows(TConstArrayView<RowHandle> Rows) = 0;` — Removes multiple rows at one. If any of the rows are invalid or already removed, nothing happens.
- L251 _public prototype_ `virtual void RemoveAllRowsWithColumns(TConstArrayView<const UScriptStruct*> Columns) = 0;` — Removes all rows that have at least the provided columns. This can be used to for instance remove all rows with a specific type tag, such as removing all rows with an entity tag to remove all entities from the data storage.
- L259 _public prototype_ `template<TColumnType... Columns> void RemoveAllRowsWith();` — Removes all rows that have at least the provided columns as template arguments. This can be used to for instance remove all rows with a specific type tag, such as removing all rows with an entity tag to remove all entities from the data storage.
- L262 _public prototype_ `virtual bool IsRowAvailable(RowHandle Row) const = 0;` — Checks whether or not a row is in use. This is true even if the row has only been reserved.
- L264 _public prototype_ `virtual bool IsRowAssigned(RowHandle Row) const = 0;` — Checks whether or not a row has been reserved but not yet assigned to a table.
- L275 _public prototype_ `virtual void FilterRowsBy( FRowHandleArray& Result, FRowHandleArrayView Input, EFilterOptions Options, Queries::TConstQueryFunction<bool>& Filter) const = 0;` — Filters the provided rows using the query filter and stores the results in the provided list.
- L279 _public prototype_ `template<typename FilterFunction> void FilterRowsBy(FRowHandleArray& Result, FRowHandleArrayView Input, EFilterOptions Options, FilterFunction&& Filter) const;` — Filters the provided rows using the query filter and stores the results in the provided list.
- L286 _public prototype_ `virtual void AddColumn(RowHandle Row, const UScriptStruct* ColumnType) = 0;` — Adds a column to a row or does nothing if already added.
- L288 _public prototype_ `template<TColumnType ColumnType> void AddColumn(RowHandle Row);`
- L293 _public prototype_ `virtual void AddColumnData(RowHandle Row, const UScriptStruct* ColumnType, const ColumnCreationCallbackRef Initializer, ColumnCopyOrMoveCallback Relocator) = 0;` — Adds a new data column and initializes it. The relocator will be used to copy or move the column out of its temporary location into the final table if the addition needs to be deferred.
- L297 _public prototype_ `template<TDataColumnType ColumnType> void AddColumn(RowHandle Row, ColumnType&& Column);`
- L310 _public prototype_ `virtual void AddColumn(RowHandle Row, const FValueTag& Tag, const FName& Value) = 0;` — Adds a ValueTag with the given value to a row A row can have multiple ValueTags, but only one of each tag type. Example: AddColumn(Row, ValueTag(TEXT("Color"), TEXT("Red));     // Valid AddColumn(Row, ValueTag(TEXT("Direction"), TEXT("Up")); // Valid AddColumn(Row, ValueTag(TEXT("Color"), TEXT("Blue"));   // Will do nothing since there already exists a Color value tag Note: Current support for changing a value tag from one value to another requires that the tag is removed before a new one is added.  This will likely change in the future to transparently replace the tag to have consistent behaviour with other usages of AddColumn
- L313 _public prototype_ `template<typename T> void AddColumn(RowHandle Row, const FName& Tag) = delete;`
- L316 _public prototype_ `template<typename T> void AddColumn(RowHandle Row, const FName& Tag, const FName& Value) = delete;`
- L319 _public prototype_ `template<> void AddColumn<FValueTag>(RowHandle Row, const FName& Tag, const FName& Value);`
- L322 _public prototype_ `template<TEnumType EnumT> void AddColumn(RowHandle Row, EnumT Value);`
- L325 _public prototype_ `template<auto Value, TEnumType EnumT = decltype(Value)> void AddColumn(RowHandle Row);`
- L328 _public prototype_ `template<TDynamicColumnTemplate DynamicColumnTemplate> void AddColumn(RowHandle Row, const FName& Identifier);`
- L331 _public prototype_ `template<TDynamicColumnTemplate DynamicColumnTemplate> void AddColumn(RowHandle Row, const FName& Identifier, DynamicColumnTemplate&& TemplateInstance);`
- L337 _public prototype_ `virtual void AddColumns(RowHandle Row, TConstArrayView<const UScriptStruct*> Columns) = 0;` — Adds multiple columns from a row. This is typically more efficient than adding columns one at a time.
- L339 _public prototype_ `template<TColumnType... Columns> void AddColumns(RowHandle Row);`
- L342 _public prototype_ `virtual void RemoveColumn(RowHandle Row, const UScriptStruct* ColumnType) = 0;` — Removes a column from a row or does nothing if already removed.
- L344 _public prototype_ `template<TColumnType Column> void RemoveColumn(RowHandle Row);`
- L347 _public prototype_ `template<TEnumType EnumT> void RemoveColumn(RowHandle Row);`
- L353 _public prototype_ `virtual void RemoveColumn(RowHandle Row, const FValueTag& Tag) = 0;` — Removes a value tag from the given row If tag does not exist on row, operation will do nothing.
- L356 _public prototype_ `template<typename T> void RemoveColumn(RowHandle Row, const FName& Tag) = delete;`
- L359 _public prototype_ `template<TDynamicColumnTemplate DynamicColumnTemplateType> void RemoveColumn(RowHandle Row, const FName& Identifier);`
- L362 _public prototype_ `template<> void RemoveColumn<FValueTag>(RowHandle Row, const FName& Tag);`
- L368 _public prototype_ `virtual void RemoveColumns(RowHandle Row, TConstArrayView<const UScriptStruct*> Columns) = 0;` — Removes multiple columns from a row. This is typically more efficient than adding columns one at a time.
- L370 _public prototype_ `template<TColumnType... Columns> void RemoveColumns(RowHandle Row);`
- L377 _public prototype_ `virtual void AddRemoveColumns(RowHandle Row, TConstArrayView<const UScriptStruct*> ColumnsToAdd, TConstArrayView<const UScriptStruct*> ColumnsToRemove) = 0;` — Adds and removes the provided column types from the provided row. This is typically more efficient than individually adding and removing columns as well as being faster than adding and removing columns separately.
- L381 _public prototype_ `virtual void BatchAddRemoveColumns( TConstArrayView<RowHandle> Rows, TConstArrayView<const UScriptStruct*> ColumnsToAdd, TConstArrayView<const UScriptStruct*> ColumnsToRemove) = 0;` — Adds and removes the provided column types from the provided list of rows.
- L387 _public prototype_ `virtual void* GetColumnData(RowHandle Row, const UScriptStruct* ColumnType) = 0;` — Retrieves a pointer to the column of the given row or a nullptr if not found or if the column type is a tag.
- L388 _public prototype_ `virtual const void* GetColumnData(RowHandle Row, const UScriptStruct* ColumnType) const = 0;`
- L391 _public prototype_ `template<TDataColumnType ColumnType> ColumnType* GetColumn(RowHandle Row);` — Returns a pointer to the column of the given row or a nullptr if the type couldn't be found or the row doesn't exist.
- L393 _public prototype_ `template<TDataColumnType ColumnType> const ColumnType* GetColumn(RowHandle Row) const;`
- L396 _public prototype_ `template<TDynamicColumnTemplate ColumnTypeTemplate> ColumnTypeTemplate* GetColumn(RowHandle Row, const FName& Identifer);` — Gets a dynamic column identified by the ColumnTypeTemplate and Identifier
- L398 _public prototype_ `template<TDynamicColumnTemplate ColumnTypeTemplate> const ColumnTypeTemplate* GetColumn(RowHandle Row, const FName& Identifer) const;`
- L405 _public prototype_ `virtual bool HasColumns(RowHandle Row, TConstArrayView<const UScriptStruct*> ColumnTypes) const = 0;` — Determines if the provided row contains the collection of columns and tags. Note that for rows that haven't been assigned yet it's not possible to check if a column exists as the table to check for hasn't been assigned yet. In these cases a list of known additions will be checked as these will be added once the table is assigned.
- L406 _public prototype_ `virtual bool HasColumns(RowHandle Row, TConstArrayView<TWeakObjectPtr<const UScriptStruct>> ColumnTypes) const = 0;`
- L408 _public prototype_ `template<TColumnType... ColumnTypes> bool HasColumns(RowHandle Row) const;`
- L410 _public prototype_ `template<Queries::TColumnDescType... ColumnTypes> bool HasColumns(RowHandle Row, const ColumnTypes&... Columns) const;`
- L417 _public prototype_ `virtual void ListColumns(RowHandle Row, ColumnListCallbackRef Callback) const = 0;` — Lists the columns on a row. This includes data and tag columns. Note that for rows that haven't been assigned yet it's not possible to return the full list as no table has been assigned yet. In these cases a list of known additions will be returned as these will be added once the table is assigned.
- L425 _public prototype_ `virtual void ListColumns(RowHandle Row, ColumnListWithDataCallbackRef Callback) = 0;` — Lists the column type and data on a row. This includes data and tag columns. Not all columns may have data so the data pointer in the callback can be null. Note that for rows that haven't been assigned yet it's not possible to return the full list as no table has been assigned yet. In these cases a list of known additions will be returned.
- L428 _public prototype_ `virtual bool MatchesColumns(RowHandle Row, const Queries::FConditions& Conditions) const = 0;` — Determines if the columns in the row match the query conditions.
- L435 _public prototype_ `virtual const UScriptStruct* GenerateDynamicColumn(const FDynamicColumnDescription& Description) = 0;` — Generates a new dynamic column from a Template.  A dynamic column is uniquely identified using the given template and an Identifier This function is idempotent - multiple calls with the same parameters will result in subsequent calls returning the same type The TemplateType may be a typed derived from either FColumn or FTag
- L440 _public prototype_ `virtual void ForEachDynamicColumn(const UScriptStruct& Template, TFunctionRef<void(const UScriptStruct& Type)> Callback) const = 0;` — Executes the given callback for each known dynamic column that derives from the base template provided
- L446 _public prototype_ `template<TDynamicColumnTemplate DynamicColumnTemplateType> void ForEachDynamicColumn(TFunctionRef<void(const UScriptStruct& Type)> Callback) const;` — Executes the given callback for each known dynamic column that derives from the base template provided
- L451 _public prototype_ `virtual UE::Editor::DataStorage::FHierarchyHandle RegisterHierarchy(const UE::Editor::DataStorage::FHierarchyRegistrationParams& Params) = 0;`
- L452 _public prototype_ `virtual UE::Editor::DataStorage::FHierarchyHandle FindHierarchyByName(const FName& Name) const = 0;`
- L453 _public prototype_ `virtual bool IsValidHierarchyHandle(FHierarchyHandle) const = 0;`
- L456 _public prototype_ `virtual const UScriptStruct* GetChildTagType(FHierarchyHandle InHierarchyHandle) const = 0;` — Gets the tag type indicating the row is a child in this hierarchy and thus has a parent
- L458 _public prototype_ `virtual const UScriptStruct* GetParentTagType(FHierarchyHandle InHierarchyHandle) const = 0;` — Gets the tag type indicating the row is a parent in this hierarchy and thus has a child
- L462 _public prototype_ `virtual const UScriptStruct* GetHierarchyDataColumnType(FHierarchyHandle InHierarchyHandle) const = 0;` — Gets the column type storing the hierarchy data. Note that the format of this type is opaque and is used internally.  It is the caller's responsibility to provide at least Read access to this column type in query requirements in order to use the HierarchyAccessInterface on the row
- L465 _public prototype_ `virtual const UScriptStruct* GetParentChangedColumnType(FHierarchyHandle InHierarchyHandle) const = 0;` — Gets the column type that is added to a row for a frame when the parent changes (if specified in RegisterHierarchy)
- L470 _public prototype_ `virtual void ResolveHierarchy(FHierarchyHandle InHierarchyHandle) = 0;` — Try to resolve every row that has an Unresolved Parent for the given hierarchy (@see SetUnresolvedParent) Unresolved hierarchies are evaluated by a processor every frame to see if the parent is known, but this function can be manually called to immediately try to resolve all rows for a particular hierarchy
- L473 _public prototype_ `virtual void ListHierarchyNames(TFunctionRef<void(const FName& HierarchyName)> Callback) const = 0;` — List all the currently known hierarchies by name
- L479 _public prototype_ `virtual void SetParentRow( FHierarchyHandle InHierarchyHandle, RowHandle Target, RowHandle Parent) = 0;` — Establishes a parent relationship between the Target and the Parent
- L489 _public prototype_ `virtual void SetUnresolvedParent( FHierarchyHandle InHierarchyHandle, RowHandle Target, FMapKey ParentId, FName MappingDomain) = 0;` — Establishes a parent relationship between the Target row and a Parent that is not registered in TEDS yet. Every frame, TEDS will attempt to resolve the missing relation by looking up the parent using TEDS Mapping. An optional MaxFrameCount can be specified, which will be decremented every frame until the potential relationship is discarded
- L496 _public prototype_ `virtual RowHandle GetParentRow(FHierarchyHandle InHierarchyHandle, RowHandle Target) const = 0;` — Gets the parent of a target, if there is one
- L501 _public prototype_ `virtual TFunction<RowHandle(const void*, const UScriptStruct*)> CreateParentExtractionFunction(FHierarchyHandle InHierarchyHandle) const = 0;` — Returns a callable which will extract the parent row from the hierarchy's HierarchyDataColumn Note that the second parameter must be the same as what is returned by GetHierarchyDataColumn() and the first parameter should point to a struct of that type
- L503 _public prototype_ `virtual bool HasChildren(FHierarchyHandle InHierarchyHandle, RowHandle Row) const = 0;`
- L505 _public typedef_ `using FHierarchyIterationCallback = TFunction<void(const ICoreProvider& Context, RowHandle Owner, RowHandle Target)>;`
- L517 _public prototype_ `virtual void WalkDepthFirst( FHierarchyHandle InHierarchyHandle, RowHandle Row, FHierarchyIterationCallback VisitFn, ETraversalOrder TraversalOrder = ETraversalOrder::PreOrder) const = 0;` — Iterates depth first from the passed in Row, calling the VisitFn on each row The Row passed in will have VisitFn called on it
- L534 _public function_ `virtual bool IterateChildren( FHierarchyHandle InHierarchyHandle, RowHandle Row, TFunctionRef<bool(const ICoreProvider& Context, RowHandle Child)> VisitFn) const` — Iterates the immediate children of the given row without descending further down the hierarchy. @param InHierarchyHandle Hierarchy to use @param Row Parent row (not included in iteration) @param VisitFn Iteration function that is expected to return true if iteration should continue or false if it should be stopped early. @return true if iteration completed (including if there were no children) without any VisitFn call returning false. Returns false if VisitFn stopped iteration early or there was an error.
- L545 _public prototype_ `virtual void DebugPrintQueryCallbacks(FOutputDevice& Output) = 0;` — Outputs the registered query callbacks to the given output device for debugging purposes.
- L565 _public prototype_ `virtual RelationTypeHandle RegisterRelationType(const FRelationRegistrationParams& Params) = 0;` — Registers a new relation type with the given configuration. Returns InvalidRelationTypeHandle if registration fails (e.g., name already exists).
- L568 _public prototype_ `virtual RelationTypeHandle FindRelationType(const FName& Name) const = 0;` — Finds a previously registered relation type by name. Returns InvalidRelationTypeHandle if not found.
- L571 _public prototype_ `virtual bool IsValidRelationType(RelationTypeHandle Type) const = 0;` — Checks if a relation type handle is valid.
- L574 _public prototype_ `virtual const FTedsRelationTraits* GetRelationTypeTraits(RelationTypeHandle Type) const = 0;` — Gets the traits for a registered relation type. Returns nullptr if handle is invalid.
- L577 _public prototype_ `virtual void ListRelationTypes(TFunctionRef<void(RelationTypeHandle, const FName&)> Callback) const = 0;` — Lists all registered relation types by calling the callback for each.
- L584 _public prototype_ `virtual const UScriptStruct* GetRelationSubjectChangedColumn(RelationTypeHandle Type) const = 0;` — Returns the tag column type stamped on Subject rows when a relation of this type changes. Only non-null when the relation was registered with bEnableSubjectChangedColumn=true. Returns nullptr for an invalid handle or when the column was not enabled.
- L591 _public prototype_ `virtual const UScriptStruct* GetRelationObjectChangedColumn(RelationTypeHandle Type) const = 0;` — Returns the tag column type stamped on Object rows when a relation of this type changes. Only non-null when the relation was registered with bEnableObjectChangedColumn=true. Returns nullptr for an invalid handle or when the column was not enabled.
- L605 _public prototype_ `virtual RowHandle CreateRelation(RelationTypeHandle Type, RowHandle Subject, RowHandle Object) = 0;` — Creates a relation between two rows. Returns the handle of the newly created relation row, or InvalidRowHandle if creation fails. For hierarchical relations, this also: - Computes and stores depth, root, and interval values - Updates indexes for efficient queries
- L614 _public prototype_ `virtual void BatchCreateRelations( RelationTypeHandle Type, TConstArrayView<RowHandle> Subjects, TConstArrayView<RowHandle> Objects, TArray<RowHandle>* OutRelationRows = nullptr) = 0;` — Creates multiple relations at once (more efficient than individual calls). Subjects and Objects arrays must have the same length, or Objects can have length 1 (in which case all subjects relate to the same object). @param OutRelationRows Optional output array to receive the created relation row handles.
- L624 _public prototype_ `virtual bool DestroyRelation(RelationTypeHandle Type, RowHandle Subject, RowHandle Object) = 0;` — Destroys a specific relation between two rows. Returns true if a relation was found and destroyed.
- L629 _public prototype_ `virtual bool HasRelation(RelationTypeHandle Type, RowHandle Subject, RowHandle Object) const = 0;` — Checks if a specific relation exists between two rows.
- L632 _public prototype_ `virtual bool HasRelationObject(RelationTypeHandle Type, RowHandle Subject) const = 0;` — Returns true if Subject has at least one Object in this relation type.
- L635 _public prototype_ `virtual bool HasRelationSubject(RelationTypeHandle Type, RowHandle Object) const = 0;` — Returns true if Object has at least one Subject in this relation type.
- L645 _public prototype_ `virtual void GetRelationObjects( RelationTypeHandle Type, RowHandle Subject, TArray<RowHandle>& OutObjects) const = 0;` — Gets all Objects that the given Subject has relations to. For a "ChildOf" relation, this returns the parent(s) of the given row.
- L655 _public prototype_ `virtual RowHandle GetRelationObject(RelationTypeHandle Type, RowHandle Subject) const = 0;` — Gets the single Object for a given Subject. Use this for exclusive-object relations (bExclusiveObject=true), where a subject has at most one object. Returns InvalidRowHandle if the subject has no object in this relation.
- L661 _public prototype_ `virtual void GetRelationSubjects( RelationTypeHandle Type, RowHandle Object, TArray<RowHandle>& OutSubjects) const = 0;` — Gets all Subjects that have relations to the given Object. For a "ChildOf" relation, this returns the children of the given row.
- L671 _public prototype_ `virtual RowHandle GetRelationSubject(RelationTypeHandle Type, RowHandle Object) const = 0;` — Gets the single Subject for a given Object. Use this for exclusive-subject relations (bExclusiveSubject=true), where an object has at most one subject. Returns InvalidRowHandle if the object has no subject in this relation.
- L681 _public prototype_ `virtual bool IsDescendantOf( RelationTypeHandle Type, RowHandle Descendant, RowHandle Ancestor, bool bIncludeSelf = false) const = 0;` — Checks if Descendant is anywhere below Ancestor in the hierarchy. @param bIncludeSelf If true, returns true when Descendant == Ancestor.
- L692 _public function_ `inline bool IsAncestorOf( RelationTypeHandle Type, RowHandle Ancestor, RowHandle Descendant, bool bIncludeSelf = false) const` — Checks if Ancestor is anywhere above Descendant in the hierarchy. Equivalent to IsDescendantOf with arguments swapped. @param bIncludeSelf If true, returns true when Ancestor == Descendant.
- L705 _public prototype_ `virtual RowHandle GetHierarchyRoot(RelationTypeHandle Type, RowHandle Row) const = 0;` — Gets the root of the hierarchy containing this row. Returns the row itself if it has no parent (is a root).
- L711 _public prototype_ `virtual int32 GetHierarchyDepth(RelationTypeHandle Type, RowHandle Row) const = 0;` — Gets the depth of a row in the hierarchy. Roots return 0, their direct children return 1, etc.
- L714 _public prototype_ `virtual void GetDescendants( RelationTypeHandle Type, RowHandle Ancestor, TArray<RowHandle>& OutDescendants) const = 0;` — Gets all descendants of a row in the hierarchy.
- L722 _public prototype_ `virtual void GetAncestors( RelationTypeHandle Type, RowHandle Descendant, TArray<RowHandle>& OutAncestors) const = 0;` — Gets all ancestors of a row in the hierarchy (parent, grandparent, etc.).
- L728 _public typedef_ `using FRelationTraversalCallback = TFunctionRef<void(RowHandle Current, RowHandle Object, int32 Depth)>;` — Callback for TraverseDescendants. Receives the current row, its object, and depth relative to StartRow.
- L731 _public prototype_ `virtual void TraverseDescendants( RelationTypeHandle Type, RowHandle StartRow, FRelationTraversalCallback Callback, ETraversalOrder Order = ETraversalOrder::PreOrder, int32 MaxDepth = TNumericLimits<int32>::Max()) const = 0;` — Traverses descendants of StartRow depth-first, calling Callback for each.
- L744 _public prototype_ `virtual void ForEachRelationObject(RelationTypeHandle Type, RowHandle Subject, TFunctionRef<void(RowHandle Object)> Callback) const = 0;` — Calls Callback for each Object related to Subject.
- L748 _public prototype_ `virtual void ForEachRelationSubject(RelationTypeHandle Type, RowHandle Object, TFunctionRef<void(RowHandle Subject)> Callback) const = 0;` — Calls Callback for each Subject related to Object.
- L755 _public prototype_ `virtual void TraverseAncestors(RelationTypeHandle Type, RowHandle Descendant, TFunctionRef<bool(RowHandle Ancestor, int32 Depth)> Callback) const = 0;` — Walks ancestors (parent, grandparent, ...) calling Callback for each. Return false from Callback to stop early.
- L759 _public prototype_ `virtual int32 ComputeDescendantCount(RelationTypeHandle Type, RowHandle Ancestor) const = 0;` — Counts descendants by walking the subtree. Not cached.
- L762 _public prototype_ `virtual bool HasRelationSubjects(RelationTypeHandle Type, RowHandle Object) const = 0;` — Returns true if Object has at least one Subject in this relation type.
- L778 _public prototype_ `virtual QueryHandle RegisterQuery(FQueryDescription&& Query) = 0;` — Registers a query with the data storage. The description is processed into an internal format and may be changed. If no valid could be created an invalid query handle will be returned. It's recommended to use the Query Builder for a more convenient and safer construction of a query.
- L780 _public prototype_ `virtual void UnregisterQuery(QueryHandle Query) = 0;` — Removes a previous registered. If the query handle is invalid or the query has already been deleted nothing will happen.
- L782 _public prototype_ `virtual const FQueryDescription& GetQueryDescription(QueryHandle Query) const = 0;` — Returns the description of a previously registered query. If the query no longer exists an empty description will be returned.
- L787 _public prototype_ `virtual uint64 CalculateQueryTablesTopologyHash(QueryHandle Query) const = 0;` — Calculates a hash based on the topology revision id of the tables associated with the provided query. If this value changes it indicates that one or more tables has new rows added, had rows removed and/or rows have been reordered.
- L793 _public prototype_ `virtual FName GetQueryTickGroupName(EQueryTickGroups Group) const = 0;` — Tick groups for queries can be given any name and the Data Storage will figure out the order of execution based on found dependencies. However keeping processors within the same query group can help promote better performance through parallelization. Therefore a collection of common tick group names is provided to help create consistent tick group names.
- L795 _public prototype_ `virtual FQueryResult RunQuery(QueryHandle Query) = 0;` — Directly runs a query. If the query handle is invalid or has been deleted nothing will happen.
- L800 _public prototype_ `virtual FQueryResult RunQuery(QueryHandle Query, DirectQueryCallbackRef Callback) = 0;` — Directly runs a query. The callback will be called for batches of matching rows. During a single call to RunQuery the callback may be called multiple times. If the query handle is invalid or has been deleted nothing happens and the callback won't be called.
- L805 _public prototype_ `virtual FQueryResult RunQuery(QueryHandle Query, EDirectQueryExecutionFlags Flags, DirectQueryCallbackRef Callback) = 0;` — Directly runs a query. The callback will be called for batches of matching rows. During a single call to RunQuery the callback may be called multiple times. If the query handle is invalid or has been deleted nothing happens and the callback won't be called.
- L810 _public prototype_ `virtual FQueryResult RunQuery(QueryHandle Query, ERunQueryFlags Flags, const Queries::TQueryFunction<void>& Callback) = 0;` — Directly runs a query. The callback will be called for batches of matching rows. During a single call to RunQuery the callback may be called multiple times. If the query handle is invalid or has been deleted nothing happens and the callback won't be called.
- L815 _public prototype_ `virtual FQueryResult RunQuery(QueryHandle Query, ERunQueryFlags Flags, const Queries::TConstQueryFunction<void>& Callback) const = 0;` — Directly runs a query. The callback will be called for batches of matching rows. During a single call to RunQuery the callback may be called multiple times. If the query handle is invalid or has been deleted nothing happens and the callback won't be called.
- L821 _public prototype_ `template<FunctionType Function> FQueryResult RunQuery(QueryHandle Query, ERunQueryFlags Flags, Function&& Callback);` — Directly runs a query. The callback will be called for batches of matching rows. During a single call to RunQuery the callback may be called multiple times. If the query handle is invalid or has been deleted nothing happens and the callback won't be called.
- L827 _public prototype_ `template<typename ResultType, FunctionType Function> FQueryResult RunQuery(QueryHandle Query, ERunQueryFlags Flags, Queries::TResult<ResultType>& Result, Function&& Callback);` — Directly runs a query. The callback will be called for batches of matching rows. During a single call to RunQuery the callback may be called multiple times. If the query handle is invalid or has been deleted nothing happens and the callback won't be called.
- L833 _public prototype_ `template<FunctionType Function> FQueryResult RunQuery(QueryHandle Query, ERunQueryFlags Flags, Function&& Callback) const;` — Directly runs a query. The callback will be called for batches of matching rows. During a single call to RunQuery the callback may be called multiple times. If the query handle is invalid or has been deleted nothing happens and the callback won't be called.
- L839 _public prototype_ `template<typename ResultType, FunctionType Function> FQueryResult RunQuery(QueryHandle Query, ERunQueryFlags Flags, Queries::TResult<ResultType>& Result, Function&& Callback) const;` — Directly runs a query. The callback will be called for batches of matching rows. During a single call to RunQuery the callback may be called multiple times. If the query handle is invalid or has been deleted nothing happens and the callback won't be called.
- L845 _public prototype_ `virtual void ActivateQueries(FName ActivationName) = 0;` — Triggers all queries registered under the activation name to run for one update cycle. The activatable queries will be activated at start of the cycle and disabled at the end of the cycle and act like regular queries for that cycle. This includes not running if there are no columns to match against.
- L859 _public prototype_ `virtual RowHandle LookupMappedRow(const FName& Domain, const FMapKeyView& Key) const = 0;` — Retrieves the row for a mapped object. Returns an invalid row handle if the no row with the provided key was found in the provided domain.
- L864 _public prototype_ `virtual void MapRow(const FName& Domain, FMapKey Key, RowHandle Row) = 0;` — Registers a row under a key in the provided domain. The same row can be registered multiple, but an key can only be associated with a single row.
- L869 _public prototype_ `virtual void BatchMapRows(const FName& Domain, TArrayView<TPair<FMapKey, RowHandle>> MapRowPairs) = 0;` — Register multiple rows under their key in the provided domain. The same row can be registered multiple times, but the key can only be associated with a single row in the domain. During processing the keys will be moved out into the final location.
- L871 _public prototype_ `virtual void RemapRow(const FName& Domain, const FMapKeyView& OriginalKey, FMapKey NewKey) = 0;` — Updates the key of a row in the provided domain to a new value. Effectively this is the same as removing a key and adding a new one.
- L873 _public prototype_ `virtual void RemoveRowMapping(const FName& Domain, const FMapKeyView& Key) = 0;` — Removes a previously registered key in the provided domain from the mapping table or does nothing if the key no longer exists.
- L884 _public prototype_ `virtual FTypedElementOnDataStorageUpdate& OnUpdate() = 0;` — Called periodically when the storage is available. This provides an opportunity to do any repeated processing for the data storage.
- L889 _public prototype_ `virtual FTypedElementOnDataStorageUpdate& OnUpdateCompleted() = 0;` — Called periodically when the storage is available. This provides an opportunity clean up after processing and to get ready for the next batch up updates.
- L891 _public typedef_ `using FOnCooperativeUpdate = TFunction<void(FTimespan TimeAllowance)>;`
- L906 _public prototype_ `virtual void RegisterCooperativeUpdate(const FName& TaskName, ECooperativeTaskPriority Priority, FOnCooperativeUpdate Callback) = 0;` — Each tick TEDS will use the remaining time in a frame to execute task in the cooperative queue. A time slicer uses a cooperative threading model so once a task has been started it will not be interrupted and it's up to the registered function to try to stay within the provided time window. Tasks with a higher priority will on average be run more frequently, but other priority tasks will be given a chance to do work so guarantees are given that lower priority aren't starved out by higher priority tasks.
- L908 _public prototype_ `virtual void UnregisterCooperativeUpdate(const FName& TaskName) = 0;` — Removes a previously registered time sliced callback.
- L918 _public prototype_ `virtual bool IsAvailable() const = 0;` — Whether or not the data storage is available. The data storage is available most of the time, but can be unavailable for a brief time between being destroyed and a new one created.
- L921 _public prototype_ `virtual void* GetExternalSystemAddress(UClass* Target) = 0;` — Returns a pointer to the registered external system if found, otherwise null.
- L924 _public prototype_ `template<typename SystemType> SystemType* GetExternalSystem();` — Returns a pointer to the registered external system if found, otherwise null.
- L927 _public prototype_ `virtual bool SupportsExtension(FName Extension) const = 0;` — Check if a custom extension is supported. This can be used to check for in-development features, custom extensions, etc.
- L929 _public prototype_ `virtual void ListExtensions(TFunctionRef<void(FName)> Callback) const = 0;` — Provides a list of all extensions that are enabled.
- L942 _public prototype_ `virtual RowHandle AddScopeRow() = 0;` — Creates a new scope row with a default label.
- L944 _public prototype_ `virtual RowHandle AddScopeRow(FStringView Label) = 0;` — Creates a new scope row with the given label.
- L946 _public prototype_ `virtual RowHandle AddScopeRow(FStringView Label, RowHandle Parent) = 0;` — Creates a new scope row with the given label, parented to Parent.
- L948 _public prototype_ `virtual void RemoveScopeRow(RowHandle Row) = 0;` — Removes a scope row.
- L950 _public prototype_ `virtual void SetParentScope(RowHandle Child, RowHandle Parent) = 0;` — Sets the parent of Child to Parent in the scope hierarchy.
- L952 _public prototype_ `virtual RowHandle GetParentScope(RowHandle Row) = 0;` — Returns the parent scope row for the given row in the scope hierarchy.
- L957 _public prototype_ `virtual const void* GetScopeDataRaw(RowHandle Row, const UScriptStruct* ColumnType) = 0;` — Walks up the scope hierarchy from Row, returning the first non-null column data pointer for ColumnType. Returns nullptr if not found.
- L964 _public prototype_ `virtual Scope::FScopeDataVersion GetScopeDataVersion(RowHandle Row, const UScriptStruct* ColumnType) = 0;` — Walks up the scope hierarchy from Row, returning the version of the first row that holds ColumnType data. The version is a per-row counter incremented by any write to any column on that row — not a per-column version. Returns an invalid version if no row in the hierarchy holds ColumnType.
- L970 _public prototype_ `virtual Scope::FScopeDataVersion SetScopeData(RowHandle Row, const UScriptStruct* ColumnType, ColumnCreationCallbackRef Initializer, ColumnCopyOrMoveCallback Relocator) = 0;` — Sets (creates if absent) scope data on a specific row. The row's version counter is bumped (shared across all columns on this row). Returns the new version.
- L976 _public prototype_ `virtual bool RemoveScopeData(RowHandle Row, const UScriptStruct* ColumnType) = 0;` — Removes scope data from a specific row. The row's version counter is bumped. Returns true if the column was present and removed.
- L981 _public prototype_ `virtual TArray<const UScriptStruct*> GetAllVisibleScopeColumns(RowHandle Row) = 0;` — Returns all columns visible from a scope row by walking up the hierarchy. Closer rows shadow parents.
- L983 _public prototype_ `virtual RowHandle GetRootScope() const = 0;` — Returns the root scope row. InvalidRowHandle if not yet initialized.
- L985 _public prototype_ `virtual FHierarchyHandle GetScopeHierarchy() = 0;` — Returns the hierarchy handle for the editor scope hierarchy.
- L989 _public prototype_ `template<TColumnType T> const T* GetScopeData(RowHandle Row);` — Typed hierarchy-walking lookup from a specific row.
- L992 _public prototype_ `template<TColumnType T> Scope::FScopeDataVersion GetScopeDataVersion(RowHandle Row);` — Typed hierarchy-walking version query from a specific row.
- L995 _public prototype_ `template<TColumnType T> Scope::FScopeDataVersion SetScopeData(RowHandle Row, T&& Data);` — Template convenience: set scope data on a specific row.
- L998 _public prototype_ `template<TColumnType T> bool RemoveScopeData(RowHandle Row);` — Template convenience: remove scope data from a specific row.
- L1004 _public prototype_ `inline RowHandle FindIndexedRow(IndexHash Index) const;` — `UE_DEPRECATED(5.6, "Use 'LookUpMappedRow' instead and use the new FMapKey(View) instead of the explicit 'GenerateIndexHash'-functions.")` — @section Deprecated
- L1006 _public prototype_ `inline void IndexRow(IndexHash Index, RowHandle Row);` — `UE_DEPRECATED(5.6, "Use 'MapRow' instead and use the new FMapKey(View) instead of the explicit 'GenerateIndexHash'-functions.")`
- L1008 _public prototype_ `inline void BatchIndexRows(TConstArrayView<TPair<IndexHash, RowHandle>> IndexRowPairs);` — `UE_DEPRECATED(5.6, "Use 'BatchMapRows' instead and use the new FMapKey(View) instead of the explicit 'GenerateIndexHash'-functions.")`
- L1010 _public prototype_ `inline void Reindex(IndexHash OriginalIndex, IndexHash NewIndex);` — `UE_DEPRECATED(5.6, "Use 'RemapRow' instead and use the new FMapKey(View) instead of the explicit 'GenerateIndexHash'-functions.")`
- L1012 _public prototype_ `inline void RemoveIndex(IndexHash Index);` — `UE_DEPRECATED(5.6, "Use 'RemovedRowMapping' instead and use the new FMapKey(View) instead of the explicit 'GenerateIndexHash'-functions.")`
- L1014 _public prototype_ `inline void ReindexRow(IndexHash OriginalIndex, IndexHash NewIndex, RowHandle Row);` — `UE_DEPRECATED(5.6, "Use 'RemapRow' instead and use the new FMapKey(View) instead of the explicit 'GenerateIndexHash'-functions. The Row argument is no longer used.")`
- L1017 _public prototype_ `inline RowHandle LookupMappedRow(const FMapKeyView& Key) const;` — `UE_DEPRECATED(5.7, "Use the version of 'LookupMappedRow' that uses a domain.")`
- L1019 _public prototype_ `inline void MapRow(FMapKey Key, RowHandle Row);` — `UE_DEPRECATED(5.7, "Use the version of 'MapRow' that uses a domain.")`
- L1021 _public prototype_ `inline void BatchMapRows(TArrayView<TPair<FMapKey, RowHandle>> MapRowPairs);` — `UE_DEPRECATED(5.7, "Use the version of 'BatchMapRows' that uses a domain.")`
- L1023 _public prototype_ `inline void RemapRow(const FMapKeyView& OriginalKey, FMapKey NewKey);` — `UE_DEPRECATED(5.7, "Use the version of 'RemapRow' that uses a domain.")`
- L1025 _public prototype_ `inline void RemoveRowMapping(const FMapKeyView& Key);` — `UE_DEPRECATED(5.7, "Use the version of 'RemoveRowMapping' that uses a domain.")`
- L1039 _function_ `template <typename FactoryT> FactoryT* ICoreProvider::FindFactory()`
- L1045 _function_ `template<typename FilterFunction> void ICoreProvider::FilterRowsBy(FRowHandleArray& Result, FRowHandleArrayView Input, EFilterOptions Options, FilterFunction&& Filter) const`
- L1051 _function_ `template<TColumnType Column> void ICoreProvider::AddColumn(RowHandle Row)`
- L1057 _function_ `template<TColumnType Column> void ICoreProvider::RemoveColumn(RowHandle Row)`
- L1063 _function_ `template<TColumnType... Columns> void ICoreProvider::AddColumns(RowHandle Row)`
- L1069 _function_ `template <> inline void ICoreProvider::AddColumn<FValueTag>(RowHandle Row, const FName& Tag, const FName& Value)`
- L1075 _function_ `template <> inline void ICoreProvider::RemoveColumn<FValueTag>(RowHandle Row, const FName& Tag)`
- L1082 _function_ `template<TDynamicColumnTemplate DynamicColumnTemplate> void ICoreProvider::RemoveColumn(RowHandle Row, const FName& Identifier)`
- L1088 _function_ `template<TEnumType EnumT> void ICoreProvider::AddColumn(RowHandle Row, EnumT Value)`
- L1099 _function_ `template<TColumnType... Columns> void ICoreProvider::RemoveAllRowsWith()`
- L1105 _function_ `template<auto Value, TEnumType EnumT> void ICoreProvider::AddColumn(RowHandle Row)`
- L1111 _function_ `template <TDynamicColumnTemplate DynamicColumnTemplate> void ICoreProvider::AddColumn(RowHandle Row, const FName& Identifier)`
- L1123 _function_ `template <TDynamicColumnTemplate DynamicColumnTemplate> void ICoreProvider::AddColumn(RowHandle Row, const FName& Identifier, DynamicColumnTemplate&& TemplateInstance)`
- L1158 _function_ `template<TEnumType EnumT> void ICoreProvider::RemoveColumn(RowHandle Row)`
- L1165 _function_ `template<TColumnType... Columns> void ICoreProvider::RemoveColumns(RowHandle Row)`
- L1171 _function_ `template<TDataColumnType ColumnType> void ICoreProvider::AddColumn(RowHandle Row, ColumnType&& Column)`
- L1199 _function_ `template<TDataColumnType ColumnType> ColumnType* ICoreProvider::GetColumn(RowHandle Row)`
- L1205 _function_ `template<TDataColumnType ColumnType> const ColumnType* ICoreProvider::GetColumn(RowHandle Row) const`
- L1211 _function_ `template <TDynamicColumnTemplate DynamicColumnTemplate> DynamicColumnTemplate* ICoreProvider::GetColumn(RowHandle Row, const FName& Identifier)`
- L1227 _function_ `template <TDynamicColumnTemplate DynamicColumnTemplate> const DynamicColumnTemplate* ICoreProvider::GetColumn(RowHandle Row, const FName& Identifier) const`
- L1237 _function_ `template<TColumnType... ColumnType> bool ICoreProvider::HasColumns(RowHandle Row) const`
- L1243 _function_ `template<Queries::TColumnDescType... ColumnTypes> bool ICoreProvider::HasColumns(RowHandle Row, const ColumnTypes&... Columns) const`
- L1273 _function_ `template<typename SystemType> SystemType* ICoreProvider::GetExternalSystem()`
- L1278 _function_ `void ICoreProvider::ReindexRow( IndexHash OriginalIndex, IndexHash NewIndex, RowHandle Row)`
- L1284 _function_ `RowHandle ICoreProvider::FindIndexedRow(IndexHash Index) const`
- L1289 _function_ `void ICoreProvider::IndexRow(IndexHash Index, RowHandle Row)`
- L1294 _function_ `void ICoreProvider::BatchIndexRows(TConstArrayView<TPair<IndexHash, RowHandle>> IndexRowPairs)`
- L1302 _function_ `void ICoreProvider::Reindex(IndexHash OriginalIndex, IndexHash NewIndex)`
- L1307 _function_ `void ICoreProvider::RemoveIndex(IndexHash Index)`
- L1312 _function_ `RowHandle ICoreProvider::LookupMappedRow(const FMapKeyView& Key) const`
- L1317 _function_ `void ICoreProvider::MapRow(FMapKey Key, RowHandle Row)`
- L1322 _function_ `void ICoreProvider::BatchMapRows(TArrayView<TPair<FMapKey, RowHandle>> MapRowPairs)`
- L1327 _function_ `void ICoreProvider::RemapRow(const FMapKeyView& OriginalKey, FMapKey NewKey)`
- L1332 _function_ `void ICoreProvider::RemoveRowMapping(const FMapKeyView& Key)`
- L1338 _function_ `template<TDynamicColumnTemplate DynamicColumnTemplateType> void ICoreProvider::ForEachDynamicColumn(TFunctionRef<void(const UScriptStruct& Type)> Callback) const`
- L1344 _function_ `template<FunctionType Function> FQueryResult ICoreProvider::RunQuery(QueryHandle Query, ERunQueryFlags Flags, Function&& Callback)`
- L1350 _function_ `template<typename ResultType, FunctionType Function> FQueryResult ICoreProvider::RunQuery(QueryHandle Query, ERunQueryFlags Flags, Queries::TResult<ResultType>& Result, Function&& Callback)`
- L1356 _function_ `template<FunctionType Function> FQueryResult ICoreProvider::RunQuery(QueryHandle Query, ERunQueryFlags Flags, Function&& Callback) const`
- L1362 _function_ `template<typename ResultType, FunctionType Function> FQueryResult ICoreProvider::RunQuery(QueryHandle Query, ERunQueryFlags Flags, Queries::TResult<ResultType>& Result, Function&& Callback) const`
- L1370 _function_ `template<TColumnType T> const T* ICoreProvider::GetScopeData(RowHandle Row)`
- L1376 _function_ `template<TColumnType T> Scope::FScopeDataVersion ICoreProvider::GetScopeDataVersion(RowHandle Row)`
- L1382 _function_ `template<TColumnType T> Scope::FScopeDataVersion ICoreProvider::SetScopeData(RowHandle Row, T&& Data)`
- L1410 _function_ `template<TColumnType T> bool ICoreProvider::RemoveScopeData(RowHandle Row)`

#### enum `UE::Editor::DataStorage::ICoreProvider::EFilterOptions`  
`enum class EFilterOptions : uint8`  
_L266-272_
- L269 _public enumerator_ `Default = 0` — Only include rows in the result that have the required columns and pass the filter function
- L271 _public enumerator_ `InvertFilter = 1 << 0` — Invert the filter to return rows that did not pass the filter function

#### enum `UE::Editor::DataStorage::ICoreProvider::ETraversalOrder`  
`enum class ETraversalOrder : uint8`  
_L507-513_
- L510 _public enumerator_ `PreOrder` — Specifies that a pre-order traversal should be performed. In a pre-order traversal, rows are visited before their children.
- L512 _public enumerator_ `PostOrder` — Specifies that a post-order traversal should be performed. In a post-order traversal, rows are visited after their children.

#### enum `UE::Editor::DataStorage::ICoreProvider::ECooperativeTaskPriority`  
`enum class ECooperativeTaskPriority : uint8`  
_L893-898_
- desc: The higher the priority, the more frequently tasks get called. See RegisterCooperativeUpdate.
- L895 _public enumerator_ `High`
- L896 _public enumerator_ `Medium`
- L897 _public enumerator_ `Low`

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace Editor` (scope `UE`)
- L36 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L38 _typedef_ `using FTypedElementOnDataStorageCreation = FSimpleMulticastDelegate;` (scope `UE::Editor::DataStorage`)
- L39 _typedef_ `using FTypedElementOnDataStorageDestruction = FSimpleMulticastDelegate;` (scope `UE::Editor::DataStorage`)
- L40 _typedef_ `using FTypedElementOnDataStorageUpdate = FSimpleMulticastDelegate;` (scope `UE::Editor::DataStorage`)
- L1028 _function_ `ENUM_CLASS_FLAGS(ICoreProvider::EFilterOptions)` (scope `UE::Editor::DataStorage`)
- L1133 _function_ `` (scope `UE::Editor::DataStorage::ICoreProvider::AddColumn`)
- L1386 _function_ `` (scope `UE::Editor::DataStorage::ICoreProvider::SetScopeData`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Interfaces/TypedElementDataStorageUiInterface.h` (Public)


#### struct `FTedsWidgetConstructorBase`  
`struct FTedsWidgetConstructorBase`  
_L37-78_
- reflection: `USTRUCT()`
- desc: Base class for Widget Constructors in TEDS. Contains common functionality needed by the different types of widget constructors that TEDS UI supports.
- L43 _public prototype_ `explicit FTedsWidgetConstructorBase(const UScriptStruct* InTypeInfo);`
- L44 _public function_ `explicit FTedsWidgetConstructorBase(EForceInit)` — For compatibility and shouldn't be directly used.
- L45 _public prototype_ `virtual ~FTedsWidgetConstructorBase() = default;`
- L48 _public prototype_ `virtual bool Initialize(const UE::Editor::DataStorage::FMetaDataView& InArguments, TArray<TWeakObjectPtr<const UScriptStruct>> InMatchedColumnTypes, UE::Editor::DataStorage::RowHandle FactoryRowHandle);` — Initializes a new constructor based on the provided arguments.
- L52 _public prototype_ `virtual const UScriptStruct* GetTypeInfo() const;` — Retrieves the type information for the constructor type.
- L54 _public prototype_ `virtual const TArray<TWeakObjectPtr<const UScriptStruct>>& GetMatchedColumns() const;` — Retrieves the columns, if any, that were matched to this constructor when it was created.
- L57 _public prototype_ `virtual const UE::Editor::DataStorage::Queries::FConditions* GetQueryConditions(const UE::Editor::DataStorage::ICoreProvider* Storage) const;` — Retrieves the query conditions that need to match for this widget constructor to produce a widget.
- L60 _protected prototype_ `bool Initialize_Internal(const UE::Editor::DataStorage::FMetaDataView& InArguments, TArray<TWeakObjectPtr<const UScriptStruct>> InMatchedColumnTypes);`
- L65 _protected member_ `TArray<TWeakObjectPtr<const UScriptStruct>> MatchedColumnTypes;` — The columns this widget constructor matched against
- L68 _protected member_ `TMap<TWeakObjectPtr<const UScriptStruct>, FName> MatchedDynamicTemplates;` — If the constructor matched against any dynamic columns, map from the base template for the column -> FName identifier
- L71 _protected member_ `UE::Editor::DataStorage::RowHandle WidgetFactoryRow = UE::Editor::DataStorage::InvalidRowHandle;` — The row containing the widget factory this constructor was factories from
- L74 _protected member_ `const UE::Editor::DataStorage::Queries::FConditions* QueryConditions = nullptr;` — The query conditions required by this constructor
- L77 _protected member_ `const UScriptStruct* TypeInfo = nullptr;` — The constructor's typeinfo

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FTedsWidgetConstructorBase> : public TStructOpsTypeTraitsBase2<FTedsWidgetConstructorBase>`  
_L81-88_
- inherits: `TStructOpsTypeTraitsBase2<FTedsWidgetConstructorBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L84-87_

#### struct `FTypedElementWidgetConstructor`  
`struct FTypedElementWidgetConstructor : public FTedsWidgetConstructorBase`  
_L96-241_
- reflection: `USTRUCT()`
- inherits: `FTedsWidgetConstructorBase`
- desc: Base class used to construct TEDS UI widgets with. See below for the options to register a constructor with the Data Storage. In most cases you want to inherit from FSimpleWidgetConstructor instead which has a simpler pipeline to create widgets
- L101 _public prototype_ `explicit FTypedElementWidgetConstructor(const UScriptStruct* InTypeInfo);`
- L102 _public function_ `explicit FTypedElementWidgetConstructor(EForceInit) : FTedsWidgetConstructorBase(ForceInit)` — For compatibility and shouldn't be directly used.
- L104 _public prototype_ `virtual ~FTypedElementWidgetConstructor() override = default;`
- L107 _public prototype_ `virtual TConstArrayView<const UScriptStruct*> GetAdditionalColumnsList() const;` — Returns a list of additional columns the widget requires to be added to its rows.
- L118 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const;` — Returns an FText of the friendly name for the data the created widget represents. By default the associated column is used. If there are multiple columns associated with the constructor the default implementation will attempt to find the longest common starting string for all the columns. Individual widget constructors can override this function with a name specific to them. If no row is specified, it will default to an InvalidRowHandle, assuming that we are asking for a display name for the whole widget and not a specific instance.
- L129 _public prototype_ `virtual TSharedPtr<SWidget> ConstructFinalWidget( UE::Editor::DataStorage::RowHandle Row, UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments);` — Calls Construct() to create the internal widget, and then stores it in a container before returning. In most cases you want to call this to first create the initial TEDS widget, to ensure the internal widget is automatically created/destroyed if the row matches/unmatches the required columns. Construct() can be called later to (re)create the internal widget if ever required. @see Construct
- L142 _public prototype_ `virtual TSharedPtr<SWidget> Construct( UE::Editor::DataStorage::RowHandle Row, UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments);` — Constructs the widget according to the provided information. Information is collected by calling the below functions CreateWidget and AddColumns. It's recommended to overload those functions to build widgets according to a standard recipe and to reduce the amount of code needed. If a complexer situation is called for this function can also be directly overwritten. In most cases, you want to call ConstructFinalWidget to create the actual widget.
- L154 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments);` — Constructs a list of classes that are used to sort the rows with the column(s) associated with this widget constructor. If this widget constructor is used to create multiple widgets, for instance when used in a column of a grid view, these sorters can be used to order the rows in a logical order described by the sorter. A widget constructor can provide multiple constructors which will allow the same list of rows to be sorted in different orders.
- L164 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSearcherInterface>> ConstructColumnSearchers( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments);` — Constructs a list of classes that are used to convert the column data into a searchable string on the rows with the column(s) associated with this widget constructor. A widget constructor can provide multiple searching constructors which will allow the same list of rows to be searched in different ways.
- L172 _public prototype_ `UE::Editor::DataStorage::RowHandle GetWidgetFactoryRow() const;` — Helper function to get the row containing the widget factory this constructor was factoried from
- L185 _public prototype_ `virtual FString CreateWidgetDisplayName( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row) const final;` — `UE_DEPRECATED(5.6, "CreateWidgetDisplayName is deprecated, please use CreateWidgetDisplayNameText instead, which will return FText rather than an FString.")` — Returns a friendly name for the data the created widget represents. By default the associated column is used. If there are multiple columns associated with the constructor the default implementation will attempt to find the longest common starting string for all the columns. Individual widget constructors can override this function with a name specific to them.
- L194 _public prototype_ `virtual bool Initialize(const UE::Editor::DataStorage::FMetaDataView& InArguments, TArray<TWeakObjectPtr<const UScriptStruct>> InMatchedColumnTypes, const UE::Editor::DataStorage::Queries::FConditions& InQueryConditions);` — `UE_DEPRECATED(5.6, "Use Initialize that takes in the factory row handle instead")` — Initializes a new constructor based on the provided arguments..
- L199 _public prototype_ `virtual const UE::Editor::DataStorage::Queries::FConditions* GetQueryConditions() const final;` — `UE_DEPRECATED(5.6, "Use GetQueryConditions that takes in ICoreProvider* instead")` — Retrieves the query conditions that need to match for this widget constructor to produce a widget.
- L203 _protected prototype_ `virtual TSharedPtr<SWidget> CreateWidget(const UE::Editor::DataStorage::FMetaDataView& Arguments);` — Create a new instance of the target widget. This is a required function.
- L205 _protected prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments);` — Create a new instance of the target widget. This is a required function.
- L212 _protected prototype_ `virtual bool SetColumns(UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row);` — Set any values in columns if needed. The columns provided through GetAdditionalColumnsList() will have already been created.
- L215 _protected prototype_ `virtual FText DescribeColumnType(const UScriptStruct* ColumnType) const;` — Creates a (friendly) name for the provided column type.
- L221 _protected prototype_ `virtual bool FinalizeWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle Row, const TSharedPtr<SWidget>& Widget);` — Last opportunity to configure anything in the widget or the row. This step can be needed to initialize widgets with data stored in columns.
- L228 _protected prototype_ `void AddDefaultWidgetColumns(UE::Editor::DataStorage::RowHandle Row, UE::Editor::DataStorage::ICoreProvider* DataStorage) const;` — Add the default misc columns we want a widget row to have.
- L234 _protected prototype_ `UE::Editor::DataStorage::RowHandle GetTargetRow( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle WidgetRow) const;` — Helper function to get the actual target row with the data the widget is operating on (if applicable). Returns InvalidRowHandle if there is no target row
- L240 _protected prototype_ `void ForAllColumnTypes(TFunctionRef<void(TNotNull<const UScriptStruct*>)> Function) const;` — Helper function to perform a function on all column types for this widget (includes matched dynamic templates)

#### struct `FSimpleWidgetConstructor`  
`struct FSimpleWidgetConstructor : public FTypedElementWidgetConstructor`  
_L248-307_
- reflection: `USTRUCT()`
- inherits: `FTypedElementWidgetConstructor`
- desc: A simple widget constructor that cuts down on most of the boilerplate, in most cases you want to inherit from this to create your widget constructor Only requires you to override CreateWidget() to create the actual SWidget
- L253 _public prototype_ `explicit FSimpleWidgetConstructor(const UScriptStruct* InTypeInfo);` — Call this constructor with StaticStruct() on your derived class to pass in the type information
- L255 _public function_ `FSimpleWidgetConstructor() : Super(StaticStruct())` — For compatibility and shouldn't be directly used.
- L257 _public prototype_ `virtual ~FSimpleWidgetConstructor() override = default;`
- L269 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;` — Required function to create the actual widget instance. @param DataStorage A pointer to the TEDS data storage interface @param DataStorageUi A pointer to the TEDS data storage UI interface @param TargetRow The row for the actual data this widget is being created for (can be InvalidRowHandle if there is no target row attached to this widget) @param WidgetRow The row that contains information about the widget itself @param Arguments Any metadata arguments that were specified @return The actual widget instance
- L283 _public prototype_ `virtual bool SetColumns(UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle WidgetRow) override;` — Override this function to add any columns to the WidgetRow before CreateWidget is called @param DataStorage A pointer to the TEDS data storage interface @param WidgetRow The row that contains information about the widget itself @return Whether any columns were added
- L288 _protected prototype_ `virtual TSharedPtr<SWidget> CreateWidget(const UE::Editor::DataStorage::FMetaDataView& Arguments) override final;` — Old CreateWidget overload that exists for backwards compatibility, you should use the overload that provides the row instead
- L293 _protected prototype_ `virtual bool FinalizeWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle Row, const TSharedPtr<SWidget>& Widget) override final;` — Old function in the widget creation pipeline that isn't used anymore. All your logic should go in CreateWidget() itself
- L302 _protected prototype_ `virtual TSharedPtr<SWidget> Construct( UE::Editor::DataStorage::RowHandle WidgetRow, UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override final;` — Helper function to call SetColumns() and CreateWidget(), you should not need to override this for simple widget constructors

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FTypedElementWidgetConstructor> : public TStructOpsTypeTraitsBase2<FTypedElementWidgetConstructor>`  
_L310-317_
- inherits: `TStructOpsTypeTraitsBase2<FTypedElementWidgetConstructor>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L313-316_

#### class `UE::Editor::DataStorage::IUiProvider`  
`class IUiProvider : public IModularFeature`  
_L324-703_
- inherits: `IModularFeature`
- L327 _public member_ `inline static const FName PurposeMappingDomain = "Wi`
- L358 _public typedef_ `using FPurposeID = FMapKey;`
- L403 _public typedef_ `using FWidgetConstructorPtr = TSharedPtr<FTypedElementWidgetConstructor>;`
- L404 _public typedef_ `using WidgetCreatedCallback = TFunctionRef<void(const TSharedRef<SWidget>& NewWidget, UE::Editor::DataStorage::RowHandle Row)>;`
- L405 _public typedef_ `using WidgetConstructionCallback = TFunctionRef<bool(FWidgetConstructorPtr, TConstArrayView<TWeakObjectPtr<const UScriptStruct>>)>;`
- L406 _public typedef_ `using WidgetPurposeCallback = TFunctionRef<void(FName, EPurposeType, const FText&)>;`
- L407 _public typedef_ `using PropertySorterConstructorCallback = TFunction<TSharedPtr<const FColumnSorterInterface>(TWeakObjectPtr<const UScriptStruct> ColumnType, const FProperty& Property)>;`
- L409 _public typedef_ `using PropertySearcherConstructorCallback = TFunction<TSharedPtr<const FColumnSearcherInterface>(TWeakObjectPtr<const UScriptStruct> ColumnType, const FProperty& Property)>;`
- L428 _public prototype_ `virtual RowHandle RegisterWidgetPurpose(const FPurposeInfo& InPurposeInfo) = 0;` — Register a widget purpose. Widget purposes indicates how widgets can be used and categorizes/organizes the available widget factories. If the same purpose is registered multiple times, only the first will be recorded and later registrations will be ignored and the return value will be InvalidRowHandle. The purposes will be mapped to the TEDS Mapping Table using InPurposeInfo.GeneratePurposeID() which can be used to lookup the purpose row. @param InPurposeInfo Struct with init params for the purpose
- L436 _public prototype_ `virtual RowHandle RegisterWidgetPurpose(const FPurposeID& PurposeID, const FPurposeInfo& InPurposeInfo) = 0;` — Overload for RegisterWidgetPurpose that allows you to use a custom ID to map to the TEDS Mapping table for lookup @param PurposeID A unique ID for the purpose that can be used to look up the row handle later @param InPurposeInfo Struct with init params for the purpose
- L439 _public prototype_ `virtual RowHandle FindPurpose(const FPurposeID& PurposeID) const = 0;` — Find the row handle for a purpose by looking it up using the purpose ID
- L442 _public prototype_ `virtual void ListWidgetPurposes(const WidgetPurposeCallback& Callback) const = 0;` — Calls the provided callback for all known registered widget purposes.
- L446 _public prototype_ `virtual FPurposeID GetDefaultWidgetPurposeID() const = 0;` — Get the name of the default TEDS UI widget purpose used to register default widgets for different types of data (e.g FText -> STextBlock)
- L449 _public prototype_ `virtual FPurposeID GetGeneralWidgetPurposeID() const = 0;` — Get the name of the general TEDS UI purpose used to register general purpose widgets for columns
- L452 _public prototype_ `virtual FHierarchyHandle GetWidgetPurposeHierarchyHandle() const = 0;` — Get the hierarchy handle that stores widget purposes relationships
- L469 _public prototype_ `virtual bool RegisterWidgetFactory(RowHandle PurposeRow, const UScriptStruct* Constructor) = 0;` — Registers a widget factory that will be called when the purpose it's registered under is requested. This version registers a generic type. Construction using these are typically cheaper as they can avoid copying the Constructor and take up less memory. The downside is that they can't store additional configuration options. If the purpose has not been registered the factory will not be recorded and a warning will be printed. If registration is successful true will be returned otherwise false.
- L479 _public prototype_ `template<typename ConstructorType> bool RegisterWidgetFactory(RowHandle PurposeRow);` — Registers a widget factory that will be called when the purpose it's registered under is requested. This version registers a generic type. Construction using these are typically cheaper as they can avoid copying the Constructor and take up less memory. The downside is that they can't store additional configuration options. If the purpose has not been registered the factory will not be recorded and a warning will be printed. If registration is successful true will be returned otherwise false.
- L489 _public prototype_ `virtual bool RegisterWidgetFactory(RowHandle PurposeRow, const UScriptStruct* Constructor, Queries::FConditions Columns) = 0;` — Registers a widget factory that will be called when the purpose it's registered under is requested. This version registers a generic type. Construction using these are typically cheaper as they can avoid copying the Constructor and take up less memory. The downside is that they can't store additional configuration options. If the purpose has not been registered the factory will not be recorded and a warning will be printed. The provided columns will be used when matching the factory during widget construction. If registration is successful true will be returned otherwise false.
- L501 _public prototype_ `template<typename ConstructorType> bool RegisterWidgetFactory(RowHandle PurposeRow, Queries::FConditions Columns);` — Registers a widget factory that will be called when the purpose it's registered under is requested. This version registers a generic type. Construction using these are typically cheaper as they can avoid copying the Constructor and take up less memory. The downside is that they can't store additional configuration options. If the purpose has not been registered the factory will not be recorded and a warning will be printed. The provided columns will be used when matching the factory during widget construction. If registration is successful true will be returned otherwise false.
- L510 _public prototype_ `template<TColumnType ColumnType> bool RegisterDecoratorWidgetFactory(RowHandle PurposeRow, const UScriptStruct* Constructor);` — Registers a decorator widget factory against a specific column Decorator widgets are added onto TEDS UI widgets for the specified purpose when the widget row has the column/tag they are registered against. @see FTedsDecoratorWidgetConstructor
- L518 _public prototype_ `virtual bool RegisterDecoratorWidgetFactory(RowHandle PurposeRow, const UScriptStruct* Constructor, const UScriptStruct* Column) = 0;` — Registers a decorator widget factory against a specific column. Decorator widgets are added onto TEDS UI widgets for the specified purpose when the widget row has the column/tag they are registered against. @see FTedsDecoratorWidgetConstructor
- L528 _public prototype_ `virtual void CreateWidgetConstructors(RowHandle PurposeRow, const FMetaDataView& Arguments, const WidgetConstructionCallback& Callback) = 0;` — Creates widget constructors for the requested purpose. The provided arguments will be used to configure the constructor. Settings made this way will be applied to all widgets created from the constructor, if applicable. If no factories were found for the requested purpose, the purpose's parent chain will be traversed to try and find an ancestor purpose with factories
- L540 _public prototype_ `virtual void CreateWidgetConstructors(RowHandle PurposeRow, EMatchApproach MatchApproach, TArray<TWeakObjectPtr<const UScriptStruct>>& Columns, const FMetaDataView& Arguments, const WidgetConstructionCallback& Callback) = 0;` — Finds matching widget constructors for provided columns, preferring longer matches over shorter matches. The provided list of columns will be updated to contain all columns that couldn't be matched. The provided arguments will be used to configure the constructor. Settings made this way will be applied to all widgets created from the constructor, if applicable. If there are still columns remaining after matching against the requested purpose, the purpose's parent chain will be traversed to try and match the remaining columns
- L550 _public prototype_ `virtual void ConstructWidgets(RowHandle PurposeRow, const FMetaDataView& Arguments, const WidgetCreatedCallback& ConstructionCallback) = 0;` — Creates all the widgets registered under the provided purpose. This may be a large number of widgets for a wide name or exactly one when the exact name of the widget is registered. Arguments can be provided, but widgets are free to ignore them. If no factories were found for the requested purpose, the purpose's parent chain will be traversed to try and find an ancestor purpose with factories
- L558 _public prototype_ `virtual TSharedPtr<SWidget> ConstructWidget(RowHandle Row, FTypedElementWidgetConstructor& Constructor, const FMetaDataView& Arguments) = 0;` — Creates a single widget using the provided constructor. The provided row will be used to store the widget information on. If columns have already been added to the row, the constructor is free to use that to configure the widget. Arguments are used by the constructor to configure the widget.
- L566 _public prototype_ `virtual TSharedPtr<SWidget> ConstructInternalWidget(RowHandle Row, FTypedElementWidgetConstructor& Constructor, const FMetaDataView& Arguments) = 0;` — Creates a single widget using the provided constructor. Alternative to ConstructWidget that doesn't create the ContainerTedsWidget that wraps the actual widget. Only recommended for advanced use cases, in most situations you want to use ConstructWidget NOTE: This will include any decorator widgets that match with the given row
- L570 _public prototype_ `virtual TSharedPtr<ITedsWidget> CreateContainerTedsWidget(RowHandle UiRowHandle) const = 0;` — Create the container widget that every TEDS UI widget is stored in
- L573 _public prototype_ `virtual TableHandle GetWidgetTable() const = 0;` — Get the table where TEDS UI widgets are stored
- L586 _public prototype_ `virtual void GeneratePropertySearchers(TArray<TSharedPtr<const FColumnSearcherInterface>>& Results, TArrayView<TWeakObjectPtr<const UScriptStruct>> Columns) const = 0;` — Build searchers for the provided list of columns
- L590 _public prototype_ `virtual void RegisterSearcherGeneratorForProperty(const FFieldClass* PropertyType, PropertySearcherConstructorCallback PropertySearcherConstructor) = 0;` — Register a function to handle converting a property into a searcher.
- L595 _public prototype_ `template<PropertyClassType PropertyClass> void RegisterSearcherGeneratorForProperty(PropertySearcherConstructorCallback PropertySearcherConstructor);` — Register a function to handle converting a property into a searcher.
- L598 _public prototype_ `virtual void UnregisterSearcherGeneratorForProperty(const FFieldClass* PropertyType) = 0;` — Unregister a function to handle converting a property into a searcher.
- L602 _public prototype_ `template<PropertyClassType PropertyClass> void UnregisterSearcherGeneratorForProperty();` — Unregister a function to handle converting a property into a searcher.
- L615 _public prototype_ `virtual void GeneratePropertySorters(TArray<TSharedPtr<const FColumnSorterInterface>>& Results, TArrayView<TWeakObjectPtr<const UScriptStruct>> Columns) const = 0;` — Build sorters for the provided list of columns
- L619 _public prototype_ `virtual void RegisterSorterGeneratorForProperty(const FFieldClass* PropertyType, PropertySorterConstructorCallback PropertySorterConstructor) = 0;` — Register a function to handle converting a property into a sorter.
- L624 _public prototype_ `template<PropertyClassType PropertyClass> void RegisterSorterGeneratorForProperty(PropertySorterConstructorCallback PropertySorterConstructor);` — Register a function to handle converting a property into a sorter.
- L627 _public prototype_ `virtual void UnregisterSorterGeneratorForProperty(const FFieldClass* PropertyType) = 0;` — Unregister a function to handle converting a property into a sorter.
- L631 _public prototype_ `template<PropertyClassType PropertyClass> void UnregisterSorterGeneratorForProperty();` — Unregister a function to handle converting a property into a sorter.
- L638 _public prototype_ `virtual bool SupportsExtension(FName Extension) const = 0;` — Check if a custom extension is supported. This can be used to check for in-development features, custom extensions, etc.
- L640 _public prototype_ `virtual void ListExtensions(TFunctionRef<void(FName)> Callback) const = 0;` — Provides a list of all extensions that are enabled.
- L648 _public typedef_ `using WidgetConstructorCallback UE_DEPRECATED(5.8, "Use the new WidgetConstructionCallback alias instead") = TFunctionRef<bool(TUniquePtr<FTypedElementWidgetConstructor>, TConstArrayView<TWeakObjectPtr<const UScriptStruct>>)>;` — Old widget constructor callback that takes in a UniquePtr, all new code should use the new WidgetConstructionCallback instead
- L654 _public prototype_ `virtual void CreateWidgetConstructors(RowHandle PurposeRow, const FMetaDataView& Arguments, const WidgetConstructorCallback& Callback) = 0;` — `UE_DEPRECATED(5.8, "Use the overload that uses the new WidgetConstructionCallback instead")`
- L658 _public prototype_ `virtual void CreateWidgetConstructors(RowHandle PurposeRow, EMatchApproach MatchApproach, TArray<TWeakObjectPtr<const UScriptStruct>>& Columns, const FMetaDataView& Arguments, const WidgetConstructorCallback& Callback) = 0;` — `UE_DEPRECATED(5.8, "Use the overload that uses the new WidgetConstructionCallback instead")`
- L662 _public prototype_ `virtual bool RegisterWidgetFactory(RowHandle PurposeRow, TUniquePtr<FTypedElementWidgetConstructor>&& Constructor) = 0;` — `UE_DEPRECATED(5.7, "Registering Widget Factories by instance is not supported anymore, register them by type instead")`
- L665 _public prototype_ `virtual bool RegisterWidgetFactory(RowHandle PurposeRow, TUniquePtr<FTypedElementWidgetConstructor>&& Constructor, Queries::FConditions Columns) = 0;` — `UE_DEPRECATED(5.7, "Registering Widget Factories by instance is not supported anymore, register them by type instead")`
- L669 _public prototype_ `virtual void RegisterWidgetPurpose(FName Purpose, EPurposeType Type, FText Description) = 0;` — `UE_DEPRECATED(5.6, "Use the version that takes in an FPurposeInfo struct instead")`
- L672 _public prototype_ `virtual bool RegisterWidgetFactory(FName Purpose, const UScriptStruct* Constructor) = 0;` — `UE_DEPRECATED(5.6, "Use the version that takes in PurposeRowHandle instead. FindPurpose() to lookup row handle by PurposeID")`
- L676 _public prototype_ `bool RegisterWidgetFactory(FName Purpose);` — `UE_DEPRECATED(5.6, "Use the version that takes in PurposeRowHandle instead. FindPurpose() to lookup row handle by PurposeID")`
- L679 _public prototype_ `virtual bool RegisterWidgetFactory(FName Purpose, const UScriptStruct* Constructor, Queries::FConditions Columns) = 0;` — `UE_DEPRECATED(5.6, "Use the version that takes in PurposeRowHandle instead. FindPurpose() to lookup row handle by PurposeID")`
- L683 _public prototype_ `bool RegisterWidgetFactory(FName Purpose, Queries::FConditions Columns);` — `UE_DEPRECATED(5.6, "Use the version that takes in PurposeRowHandle instead. FindPurpose() to lookup row handle by PurposeID")`
- L686 _public prototype_ `virtual bool RegisterWidgetFactory(FName Purpose, TUniquePtr<FTypedElementWidgetConstructor>&& Constructor) = 0;` — `UE_DEPRECATED(5.6, "Use the version that takes in PurposeRowHandle instead. FindPurpose() to lookup row handle by PurposeID")`
- L689 _public prototype_ `virtual bool RegisterWidgetFactory(FName Purpose, TUniquePtr<FTypedElementWidgetConstructor>&& Constructor, Queries::FConditions Columns) = 0;` — `UE_DEPRECATED(5.6, "Use the version that takes in PurposeRowHandle instead. FindPurpose() to lookup row handle by PurposeID")`
- L693 _public prototype_ `virtual void CreateWidgetConstructors(FName Purpose, const FMetaDataView& Arguments, const WidgetConstructorCallback& Callback) = 0;` — `UE_DEPRECATED(5.6, "Use the version that takes in PurposeRowHandle instead. FindPurpose() to lookup row handle by PurposeID")`
- L696 _public prototype_ `virtual void CreateWidgetConstructors(FName Purpose, EMatchApproach MatchApproach, TArray<TWeakObjectPtr<const UScriptStruct>>& Columns, const FMetaDataView& Arguments, const WidgetConstructorCallback& Callback) = 0;` — `UE_DEPRECATED(5.6, "Use the version that takes in PurposeRowHandle instead. FindPurpose() to lookup row handle by PurposeID")`
- L700 _public prototype_ `virtual void ConstructWidgets(FName Purpose, const FMetaDataView& Arguments, const WidgetCreatedCallback& ConstructionCallback) = 0;` — `UE_DEPRECATED(5.6, "Use the version that takes in PurposeRowHandle instead. FindPurpose() to lookup row handle by PurposeID")`
- L713 _function_ `template<typename ConstructorType> bool IUiProvider::RegisterWidgetFactory(FName Purpose)`
- L721 _function_ `template<typename ConstructorType> bool IUiProvider::RegisterWidgetFactory(RowHandle PurposeRow)`
- L727 _function_ `template<typename ConstructorType> bool IUiProvider::RegisterWidgetFactory(FName Purpose, Queries::FConditions Columns)`
- L735 _function_ `template<typename ConstructorType> bool IUiProvider::RegisterWidgetFactory(RowHandle PurposeRow, Queries::FConditions Columns)`
- L741 _function_ `template<TColumnType ColumnType> bool IUiProvider::RegisterDecoratorWidgetFactory(RowHandle PurposeRow, const UScriptStruct* Constructor)`
- L747 _function_ `template<PropertyClassType PropertyClass> void IUiProvider::RegisterSearcherGeneratorForProperty(PropertySearcherConstructorCallback PropertySearcherConstructor)`
- L753 _function_ `template<PropertyClassType PropertyClass> void IUiProvider::UnregisterSearcherGeneratorForProperty()`
- L759 _function_ `template<PropertyClassType PropertyClass> void IUiProvider::RegisterSorterGeneratorForProperty(PropertySorterConstructorCallback PropertySorterConstructor)`
- L765 _function_ `template<PropertyClassType PropertyClass> void IUiProvider::UnregisterSorterGeneratorForProperty()`

#### enum `UE::Editor::DataStorage::IUiProvider::EPurposeType`  
`enum class EPurposeType : uint8`  
_L329-343_
- L332 _public enumerator_ `Generic` — General purpose name which allows multiple factory registrations.
- L337 _public enumerator_ `UniqueByName` — Only one factory can be registered with this purpose. If multiple factories are registered only the last factory will be stored.
- L342 _public enumerator_ `UniqueByNameAndColumn` — Only one factory can be registered with this purpose for a specific combination of columns. If multiple factories are registered only the last factory will be stored.

#### enum `UE::Editor::DataStorage::IUiProvider::EMatchApproach`  
`enum class EMatchApproach : uint8`  
_L345-356_
- L351 _public enumerator_ `LongestMatch` — Looks for the longest chain of columns matching widget factories. The matching columns are removed and the process is repeated until there are no more columns or no matches are found.
- L353 _public enumerator_ `ExactMatch` — A single widget factory is reduced which matches the requested columns exactly.
- L355 _public enumerator_ `SingleMatch` — Each column is matched to widget factory. Only widget factories that use a single column are used.

#### struct `UE::Editor::DataStorage::IUiProvider::FPurposeInfo`  
`struct FPurposeInfo`  
_L364-401_
- desc: Struct describing the default init params for a widget purpose. These can also be added to the purpose row post init using the columns in WidgetPurposeColumns.h
- L367 _public member_ `FName Namespace;` — The namespace the purpose belongs to (e.g "General", "SceneOutliner")
- L370 _public member_ `FName Name;` — The name of the purpose (e.g "RowLabel", "Cell")
- L373 _public member_ `FName Frame;` — An optional suffix for the purpose (e.g "Large", "Small", "Default")
- L376 _public member_ `EPurposeType Type;` — The purpose type
- L379 _public member_ `FText Description;` — A user facing description for the purpose
- L382 _public member_ `FPurposeID ParentPurposeID;` — The parent purpose. If valid, widget construction methods will go up the hierarchy if no widgets were found for a purpose
- L385 _public prototype_ `FPurposeInfo(const FName& InNamespace, const FName& InName, const FName& InFrame, EPurposeType InPurposeType = EPurposeType::UniqueByNameAndColumn, const FText& InDescription = FText::GetEmpty(), const FPurposeID& InParent = FPurposeID());` — Default constructor for FPurposeInfo, the members with a default value are optional when you only need an FPurposeInfo to look up FPurposeID
- L390 _public prototype_ `FPurposeInfo(const FName& InLegacyPurposeName, EPurposeType InPurposeType, const FText& InDescription, const FPurposeID& InParent = FPurposeID());` — Create an FPurposeInfo struct using a legacy purpose name to parse it as Namespace.Name.Frame (e.g "SceneOutliner.Cell.Large")
- L394 _public prototype_ `explicit FPurposeInfo(const FWidgetPurposeNameColumn& WidgetPurposeNameColumn);` — Create an FPurposeInfo struct using FWidgetPurposeNameColumn
- L397 _public prototype_ `FPurposeID GeneratePurposeID() const;` — Convert this PurposeInfo to a PurposeID that can be used to look up the purpose row
- L400 _public prototype_ `FName ToString() const;` — Convert this PurposeInfo to a human-readable name in the legacy format ("Namespace.Name.Frame")

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Editor` (scope `UE`)
- L23 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L85 _enumerator_ `WithNoInitConstructor = true` (scope `TStructOpsTypeTraits::__anon030dbac70103`)
- L86 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anon030dbac70103`)
- L314 _enumerator_ `WithNoInitConstructor = true` (scope `TStructOpsTypeTraits::__anon030dbac70203`)
- L315 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anon030dbac70203`)
- L319 _namespace_ `namespace UE`
- L319 _namespace_ `namespace Editor` (scope `UE`)
- L319 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L705 _typedef_ `using FWidgetConstructor = FTypedElementWidgetConstructor;` (scope `UE::Editor::DataStorage`)
- L706 _typedef_ `using FSimpleWidgetConstructor = FSimpleWidgetConstructor;` (scope `UE::Editor::DataStorage`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Interfaces/TypedElementQueryStorageInterfaces.h` (Public)


#### struct `UE::Editor::DataStorage::ICommonQueryContext`  
`struct ICommonQueryContext : public Queries::ITableInfo< Queries::IDynamicColumnInfo< Queries::IContextCapability>>`  
_L30-169_
- inherits: `Queries::ITableInfo<Queries::IDynamicColumnInfo<Queries::IContextCapability>>`
- desc: Base interface for any contexts provided to query callbacks.
- L35 _public prototype_ `virtual ~ICommonQueryContext() = default;`
- L38 _public prototype_ `virtual uint32 GetRowCount() const = 0;` — Returns the number rows in the batch.
- L43 _public prototype_ `virtual TConstArrayView<RowHandle> GetRowHandles() const = 0;` — Returns an immutable view that contains the row handles for all returned results. The returned size will be the same  as the value returned by GetRowCount().
- L46 _public prototype_ `virtual const void* GetColumn(const UScriptStruct* ColumnType) const = 0;` — Return the address of a immutable column matching the requested type or a nullptr if not found.
- L49 _public prototype_ `template<TDataColumnType Column> const Column* GetColumn() const;` — Return the address of a immutable column matching the requested type or a nullptr if not found.
- L51 _public prototype_ `template<TDynamicColumnTemplate TemplateType> const TemplateType* GetColumn(const FName& Identifier) const;`
- L53 _public prototype_ `virtual void* GetMutableColumn(const UScriptStruct* ColumnType) = 0;` — Return the address of a mutable column matching the requested type or a nullptr if not found.
- L56 _public prototype_ `template<typename Column> Column* GetMutableColumn();` — Return the address of a mutable column matching the requested type or a nullptr if not found.
- L58 _public prototype_ `template<TDynamicColumnTemplate TemplateType> TemplateType* GetMutableColumn(const FName& Identifier);`
- L64 _public prototype_ `virtual void GetColumns(TArrayView<char*> RetrievedAddresses, TConstArrayView<TWeakObjectPtr<const UScriptStruct>> ColumnTypes, TConstArrayView<EQueryAccessType> AccessTypes) = 0;` — Get a list of columns or nullptrs if the column type wasn't found. Mutable addresses are returned and it's up to the caller to not change immutable addresses.
- L71 _public prototype_ `virtual void GetColumnsUnguarded(int32 TypeCount, char** RetrievedAddresses, const TWeakObjectPtr<const UScriptStruct>* ColumnTypes, const EQueryAccessType* AccessTypes) = 0;` — Get a list of columns or nullptrs if the column type wasn't found. Mutable addresses are returned and it's up to the caller to not change immutable addresses. This version doesn't verify that the enough space is provided and it's up to the caller to guarantee the target addresses have enough space.
- L78 _public prototype_ `virtual bool HasColumn(const UScriptStruct* ColumnType) const = 0;` — Returns whether a column matches the requested type or not. This version only applies to the table that's currently set in the context. This version is faster of checking in the current row or table, but the version using a row is needed to check arbitrary rows.
- L85 _public prototype_ `template<typename Column> bool HasColumn() const;` — Returns whether a column matches the requested type or not. This version only applies to the table that's currently set in the context. This version is faster of checking in the current row or table, but the version using a row is needed to check arbitrary rows.
- L91 _public prototype_ `virtual bool HasColumn(RowHandle Row, const UScriptStruct* ColumnType) const = 0;` — Return whether a column matches the requested type or not. This can be used for arbitrary rows. If the row is in the table that's set in the context, for instance because it's the current row, then the version that doesn't take a row as an argument is recommended.
- L98 _public prototype_ `template<typename Column> bool HasColumn(RowHandle Row) const;` — Return whether a column matches the requested type or not. This can be used for arbitrary rows. If the row is in the table that's set in the context, for instance because it's the current row, then the version that doesn't take a row as an argument is recommended.
- L101 _public prototype_ `template<TDynamicColumnTemplate DynamicColumnTemplate> bool HasColumn(RowHandle Row, const FName& Identifier) const;`
- L104 _public prototype_ `virtual void SetParentRow( RowHandle Target, RowHandle Parent) = 0;` — Sets the Target's Parent if the query has a configured Hierarchy
- L113 _public prototype_ `virtual void SetUnresolvedParent( RowHandle Target, FMapKey ParentId, FName MappingDomain) = 0;` — Establishes a parent relationship between the Target row and a Parent that is not registered in TEDS yet. Every frame, TEDS will attempt to resolve the missing relation by looking up the parent using TEDS Mapping. An optional MaxFrameCount can be specified, which will be decremented every frame until the potential relationship is discarded
- L119 _public prototype_ `virtual RowHandle GetParentRow( RowHandle Target) const = 0;` — Gets the Target's Parent if the query has a configured Hierarchy
- L129 _public prototype_ `virtual void SetRelation( RelationTypeHandle Type, RowHandle Target, RowHandle NewObject) = 0;` — Defers a relation change until the end of the current chunk loop. Removes any existing relation of this type where Target is the Subject, then creates a new one with NewObject as the Object. Pass InvalidRowHandle for NewObject to remove the existing relation without creating a new one. Safe to call from within a processor callback — does not call ICoreProvider directly.
- L135 _public prototype_ `virtual float GetDeltaTimeSeconds() const = 0;` — Returns the amount of time now and the last update in seconds.
- L155 _public prototype_ `template<typename T> void PushCommand(T CommandContext);` — Creates a command that will run at the termination of an execution context. Intended to be used for cases where the query callback requires doing some work that needs to be serialized with respect to other callback invocations. Note that commands will be executed in order with respect to the thread that pushed them and will be executed on the query exection thread serially. Usage: Define a command struct with a mutable operator() overload struct FMyCommand { void operator()() { DoSomethingWithSideEffects(MyActor) }; TWeakObjectPtr<AActor> MyActor; }; Context.PushCommand(FMyCommand{ .MyActor = Actor });
- L157 _public prototype_ `virtual void PushCommand(void (*CommandFunction)(void* ), void* InCommandData) = 0;`
- L168 _protected prototype_ `virtual void* EmplaceObjectInScratch(const FEmplaceObjectParams& Params) = 0;` — Required as the interface doesn't have direct access to any temporary handling of memory in the backend.
- L464 _function_ `template<TDataColumnType Column> const Column* ICommonQueryContext::GetColumn() const`
- L470 _function_ `template <TDynamicColumnTemplate TemplateType> const TemplateType* ICommonQueryContext::GetColumn(const FName& Identifier) const`
- L477 _function_ `template<typename Column> Column* ICommonQueryContext::GetMutableColumn()`
- L483 _function_ `template <TDynamicColumnTemplate TemplateType> TemplateType* ICommonQueryContext::GetMutableColumn(const FName& Identifier)`
- L490 _function_ `template <typename Column> bool ICommonQueryContext::HasColumn() const`
- L496 _function_ `template <typename Column> bool ICommonQueryContext::HasColumn(RowHandle Row) const`
- L502 _function_ `template <TDynamicColumnTemplate DynamicColumnTemplate> bool ICommonQueryContext::HasColumn(RowHandle Row, const FName& Identifier) const`
- L661 _function_ `template <typename T> void ICommonQueryContext::PushCommand(T CommandContext)`

#### struct `UE::Editor::DataStorage::ICommonQueryContext::FEmplaceObjectParams`  
`struct FEmplaceObjectParams`  
_L159-166_
- L161 _public member_ `size_t ObjectSize;`
- L162 _public member_ `size_t Alignment;`
- L163 _public member_ `void (*Construct)(void*, void*);`
- L164 _public member_ `void(*Destroy)(void*);`
- L165 _public member_ `void* SourceObject;`

#### struct `UE::Editor::DataStorage::ICommonQueryWithEnvironmentContext`  
`struct ICommonQueryWithEnvironmentContext : public ICommonQueryContext`  
_L171-341_
- inherits: `ICommonQueryContext`
- L173 _public typedef_ `using ObjectCopyOrMove = void (*)(const UScriptStruct& TypeInfo, void* Destination, void* Source);`
- L187 _public prototype_ `template<typename DynamicColumnTemplate> const DynamicColumnTemplate* GetColumn(const FName& Identifier) const;` — Helper template that returns a const reference to the column array data for the range of rows being processed Returns nullptr if type not found or column not assigned to row @warning It is advised to only use this function in a query callback that handles multiple rows the returned reference will be to the first column in the table chunk, not necessarily the column corresponding to the row that the singular callback form is using.
- L197 _public prototype_ `template<typename DynamicColumnTemplate> DynamicColumnTemplate* GetMutableColumn(const FName& Identifier);` — Helper template that returns the reference to the column array data for the range of rows being processed Returns nullptr if type not found or column not assigned to row @warning It is advised to only use this function in a query callback that handles multiple rows the returned reference will be to the first column in the table chunk, not necessarily the column corresponding to the row that the singular callback form is using.
- L203 _public prototype_ `template<typename DynamicColumnTemplate> bool HasColumn(const FName& Identifier) const;` — Helper template to return whether a row has a given dynamic column.
- L209 _public prototype_ `template<typename DynamicColumnTemplate> bool HasColumn(RowHandle Row, const FName& Identifier) const;` — Helper template to return whether a row has a given dynamic column.
- L216 _public prototype_ `virtual uint64 GetUpdateCycleId() const = 0;` — Returns the id for the current update cycle. Every time TEDS goes through a cycle of running query callbacks, this is incremented by one. This guarantees that all query callbacks in the same run see the same cycle id. This can be useful in avoiding duplicated work.
- L219 _public prototype_ `virtual bool IsRowAvailable(RowHandle Row) const = 0;` — Checks whether or not a row is in use. This is true even if the row has only been reserved.
- L221 _public prototype_ `virtual bool IsRowAssigned(RowHandle Row) const = 0;` — Checks whether or not a row has been reserved but not yet assigned to a table.
- L228 _public prototype_ `virtual void ActivateQueries(FName ActivationName) = 0;` — Triggers all queries registered under the activation name to run for one update cycle. The activatable queries will be activated at start of the cycle and disabled at the end of the cycle and act like regular queries for that cycle. This includes not running if there are not columns to match against.
- L233 _public prototype_ `virtual RowHandle AddRow(TableHandle Table) = 0;` — Adds a row to the given table.
- L239 _public prototype_ `virtual void RemoveRow(RowHandle Row) = 0;` — Removes the row with the provided row handle. The removal will not be immediately done but delayed until the end of the tick group.
- L244 _public prototype_ `virtual void RemoveRows(TConstArrayView<RowHandle> Rows) = 0;` — Removes rows with the provided row handles. The removal will not be immediately done but delayed until the end of the tick group.
- L253 _public prototype_ `template<typename ColumnType> ColumnType& AddColumn(RowHandle Row, ColumnType&& Column);` — Adds the provided column to the requested row. Note: The addition of the column will not be immediately done. Instead it will be deferred until the end of the tick group. Changes made to the return column will still be applied when the column is added to the row.
- L262 _public prototype_ `template<typename ColumnTypeTemplate> ColumnTypeTemplate* AddColumn(RowHandle Row, const FName& Identifier);` — Helper template for adding a dynamic column to the requested row.  The resulting column will be default initialized. @tparam ColumnTypeTemplate The template layout of the column @param Row The row to add the column to @param Identifier Combined with the template type, the dynamic column is uniquely identified with this parameter @return An ephemeral reference to the data of the column.  The returned column will have been constructed.
- L271 _public prototype_ `template<typename ColumnTypeTemplate> ColumnTypeTemplate& AddColumn(RowHandle Row, const FName& Identifier, ColumnTypeTemplate&& Column);` — Helper template for adding a dynamic column to the requested row @tparam ColumnTypeTemplate The template layout of the column @param Row The row to add the column to @param Identifier Combined with the template type, the dynamic column is uniquely identified with this parameter @return An ephemeral reference to the data of the column.  The returned column will have been constructed.
- L277 _public prototype_ `template<typename... Columns> void AddColumns(RowHandle Row);` — Adds new empty columns to a row of the provided type. The addition will not be immediately done but delayed until the end of the tick group.
- L283 _public prototype_ `template<typename... Columns> void AddColumns(TConstArrayView<RowHandle> Rows);` — Adds new empty columns to the listed rows of the provided type. The addition will not be immediately done but delayed until the end of the tick group.
- L288 _public prototype_ `virtual void AddColumns(RowHandle Row, TConstArrayView<const UScriptStruct*> ColumnTypes) = 0;` — Adds new empty columns to a row of the provided type. The addition will not be immediately done but delayed until the end of the tick group.
- L293 _public prototype_ `virtual void AddColumns(TConstArrayView<RowHandle> Rows, TConstArrayView<const UScriptStruct*> ColumnTypes) = 0;` — Adds new empty columns to the listed rows of the provided type. The addition will not be immediately done but delayed until the end of the tick group.
- L295 _public prototype_ `virtual void AddColumns(TConstArrayView<RowHandle> Rows, TConstArrayView<FDynamicColumnDescription> DynamicColumnDescriptions) = 0;`
- L304 _public prototype_ `virtual void* AddColumnUninitialized(RowHandle Row, const UScriptStruct* ColumnType) = 0;` — Add a new uninitialized column of the provided type if one does not exist. Returns a staged column which is used to copy into the database at a later time via the UStructScript Copy operator at the end of the tick group. It is the caller's responsibility to ensure the staged column's constructor is called. The caller may modify other values in the column. This function can not be used to add a tag as tags do not contain any data.
- L313 _public prototype_ `virtual void* AddColumnUninitialized(RowHandle Row, const UScriptStruct* ObjectType, ObjectCopyOrMove Relocator) = 0;` — Add a new uninitialized column of the provided type if one does not exist. Returns a staged column which is used to copy/move into the database at a later time via the provided relocator at the end of the tick group. It is the caller's responsibility to ensure the staged column's constructor is called. The caller may modify other values in the column. This function can not be used to add a tag as tags do not contain any data.
- L315 _public prototype_ `virtual void* AddColumnUninitialized(RowHandle Row, const FDynamicColumnDescription& DynamicColumnDescription, ObjectCopyOrMove Relocator) = 0;`
- L316 _public prototype_ `virtual void* AddColumnUninitialized(RowHandle Row, const FDynamicColumnDescription& DynamicColumnDescription) = 0;`
- L324 _public prototype_ `template<typename... Columns> void RemoveColumns(RowHandle Row);` — Removes columns of the provided types from a row. The removal will not be immediately done but delayed until the end of the tick group.
- L330 _public prototype_ `template<typename... Columns> void RemoveColumns(TConstArrayView<RowHandle> Rows);` — Removes columns of the provided types from the listed rows. The removal will not be immediately done but delayed until the end of the tick group.
- L335 _public prototype_ `virtual void RemoveColumns(RowHandle Row, TConstArrayView<const UScriptStruct*> ColumnTypes) = 0;` — Removes columns of the provided types from a row. The removal will not be immediately done but delayed until the end of the tick group.
- L340 _public prototype_ `virtual void RemoveColumns(TConstArrayView<RowHandle> Rows, TConstArrayView<const UScriptStruct*> ColumnTypes) = 0;` — Removes columns of the provided types from the listed rows. The removal will not be immediately done but delayed until the end of the tick group.
- L509 _function_ `template <typename DynamicColumnTemplate> const DynamicColumnTemplate* ICommonQueryWithEnvironmentContext::GetColumn(const FName& Identifier) const`
- L522 _function_ `template <typename DynamicColumnTemplate> DynamicColumnTemplate* ICommonQueryWithEnvironmentContext::GetMutableColumn(const FName& Identifier)`
- L535 _function_ `template <typename DynamicColumnTemplate> bool ICommonQueryWithEnvironmentContext::HasColumn(const FName& Identifier) const`
- L547 _function_ `template <typename DynamicColumnTemplate> bool ICommonQueryWithEnvironmentContext::HasColumn(RowHandle Row, const FName& Identifier) const`
- L563 _function_ `template<typename ColumnType> ColumnType& ICommonQueryWithEnvironmentContext::AddColumn(RowHandle Row, ColumnType&& Column)`
- L585 _function_ `template <typename ColumnTypeTemplate> ColumnTypeTemplate* ICommonQueryWithEnvironmentContext::AddColumn(RowHandle Row, const FName& Identifier)`
- L610 _function_ `template <typename ColumnTypeTemplate> ColumnTypeTemplate& ICommonQueryWithEnvironmentContext::AddColumn(RowHandle Row, const FName& Identifier, ColumnTypeTemplate&& Column)`
- L637 _function_ `template<typename... Columns> void ICommonQueryWithEnvironmentContext::AddColumns(RowHandle Row)`
- L643 _function_ `template<typename... Columns> void ICommonQueryWithEnvironmentContext::AddColumns(TConstArrayView<RowHandle> Rows)`
- L649 _function_ `template<typename... Columns> void ICommonQueryWithEnvironmentContext::RemoveColumns(RowHandle Row)`
- L655 _function_ `template<typename... Columns> void ICommonQueryWithEnvironmentContext::RemoveColumns(TConstArrayView<RowHandle> Rows)`

#### enum `UE::Editor::DataStorage::EDirectQueryExecutionFlags`  
`enum class EDirectQueryExecutionFlags : uint32`  
_L343-357_
- L345 _public enumerator_ `Default = 0` — No settings, use the default behavior.
- L346 _public enumerator_ `ParallelizeChunks = 1 << 0` — If set, each chunk is processed on a separate thread.
- L352 _public enumerator_ `AutoBalanceParallelChunkProcessing = 1 << 1` — Requires ParallelizeChunks to be set. If set together with ParallelizeChunks, each chunk will be scheduled individually. This allows work to be better distributed among threads, but comes at additional scheduling cost. Add this flag if the processing time per chunk varies.
- L353 _public enumerator_ `IgnoreActiveState = 1 << 2` — If set, a direct call will not check activatable queries if they're set.
- L354 _public enumerator_ `AllowBoundQueries = 1 << 3` — Stops checking if queries are bound when set, otherwise bound queries will assert.
- L356 _public enumerator_ `IgnoreActivationCount UE_DEPRECATED("5.7", "Activation counts are no longer supported.") = IgnoreActiveState`

#### enum `UE::Editor::DataStorage::ERunQueryFlags`  
`enum class ERunQueryFlags : uint32`  
_L363-375_
- desc: For now this is an exact mirror of EDirectQueryExecutionFlags (except deprecated flags) in order to separate the old and the new query callbacks/context. Please keep both in sync, except for new entries, until the old query callbacks/context has been fully deprecated.
- L365 _public enumerator_ `Default = 0` — No settings, use the default behavior.
- L366 _public enumerator_ `ParallelizeChunks = 1 << 0` — If set, each chunk is processed on a separate thread.
- L372 _public enumerator_ `AutoBalanceParallelChunkProcessing = 1 << 1` — Requires ParallelizeChunks to be set. If set together with ParallelizeChunks, each chunk will be scheduled individually. This allows work to be better distributed among threads, but comes at additional scheduling cost. Add this flag if the processing time per chunk varies.
- L373 _public enumerator_ `IgnoreActiveState = 1 << 2` — If set, a direct call will not check activatable queries if they're set.
- L374 _public enumerator_ `AllowBoundQueries = 1 << 3` — Stops checking if queries are bound when set, otherwise bound queries will assert.

#### struct `UE::Editor::DataStorage::IDirectQueryContext`  
`struct IDirectQueryContext : public ICommonQueryContext`  
_L381-384_
- inherits: `ICommonQueryContext`
- desc: Interface to be provided to query callbacks that are directly called through RunQuery from outside a query callback.
- L383 _public prototype_ `virtual ~IDirectQueryContext() = default;`

#### struct `UE::Editor::DataStorage::ISubqueryContext`  
`struct ISubqueryContext : public ICommonQueryWithEnvironmentContext`  
_L389-392_
- inherits: `ICommonQueryWithEnvironmentContext`
- desc: Interface to be provided to query callbacks that are directly called through from a query callback.
- L391 _public prototype_ `virtual ~ISubqueryContext() = default;`

#### struct `UE::Editor::DataStorage::IQueryContext`  
`struct IQueryContext : public ICommonQueryWithEnvironmentContext`  
_L398-447_
- inherits: `ICommonQueryWithEnvironmentContext`
- desc: Interface to be provided to query callbacks running with the Data Storage. Note that at the time of writing only subclasses of Subsystem are supported as dependencies.
- L400 _public prototype_ `virtual ~IQueryContext() = default;`
- L403 _public prototype_ `virtual const UObject* GetDependency(const UClass* DependencyClass) = 0;` — Returns an immutable instance of the requested dependency or a nullptr if not found.
- L405 _public prototype_ `virtual UObject* GetMutableDependency(const UClass* DependencyClass) = 0;` — Returns a mutable instance of the requested dependency or a nullptr if not found.
- L411 _public prototype_ `virtual void GetDependencies(TArrayView<UObject*> RetrievedAddresses, TConstArrayView<TWeakObjectPtr<const UClass>> DependencyTypes, TConstArrayView<EQueryAccessType> AccessTypes) = 0;` — Returns a list of dependencies or nullptrs if a dependency wasn't found. Mutable versions are return and it's up to the caller to not change immutable dependencies.
- L415 _public prototype_ `virtual RowHandle LookupMappedRow(const FName& Domain, const FMapKeyView& Index) const = 0;` — Retrieves the row for a mapped object in the provided domain. Returns an invalid row handle if the key wasn't found.
- L422 _public prototype_ `virtual FQueryResult RunQuery(QueryHandle Query) = 0;` — Runs a previously created query. This version takes an arbitrary query, but is limited to running queries that do not directly access data from rows such as count queries. The returned result is a snap shot and values may change between phases.
- L427 _public prototype_ `virtual FQueryResult RunSubquery(int32 SubqueryIndex) = 0;` — Runs a subquery registered with the current query. The subquery index is in the order of registration with the query. Subqueries are executed as part of their parent query and are not scheduled separately.
- L432 _public prototype_ `virtual FQueryResult RunSubquery(int32 SubqueryIndex, SubqueryCallbackRef Callback) = 0;` — Runs the provided callback on a subquery registered with the current query. The subquery index is in the order of registration with the query. Subqueries are executed as part of their parent query and are not scheduled separately.
- L439 _public prototype_ `virtual FQueryResult RunSubquery(int32 SubqueryIndex, RowHandle Row, SubqueryCallbackRef Callback) = 0;` — Runs the provided callback on a subquery registered with the current query for the exact provided row. The subquery index is in the order of registration with the query. If the row handle is in a table that doesn't match the selected subquery the callback will not be called. Check the count in the returned results to determine if the callback was called or not. Subqueries are executed as part of their parent query and are not scheduled separately.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Editor` (scope `UE`)
- L19 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L24 _typedef_ `using SubqueryCallback = TFunction<void(const FQueryDescription&, ISubqueryContext&)>;` (scope `UE::Editor::DataStorage`)
- L25 _typedef_ `using SubqueryCallbackRef = TFunctionRef<void(const FQueryDescription&, ISubqueryContext&)>;` (scope `UE::Editor::DataStorage`)
- L358 _prototype_ `ENUM_CLASS_FLAGS(EDirectQueryExecutionFlags);` (scope `UE::Editor::DataStorage`)
- L376 _prototype_ `ENUM_CLASS_FLAGS(ERunQueryFlags);` (scope `UE::Editor::DataStorage`)
- L457 _namespace_ `namespace UE`
- L457 _namespace_ `namespace Editor` (scope `UE`)
- L457 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L571 _function_ `` (scope `UE::Editor::DataStorage::ICommonQueryWithEnvironmentContext::AddColumn`)
- L668 _function_ `` (scope `UE::Editor::DataStorage::ICommonQueryContext::PushCommand`)

### `Source/Runtime/TypedElementFramework/Public/Elements/Interfaces/TypedElementUiCapabilities.h` (Public)


#### class `ITypedElementUiCapability`  
`class UE_DEPRECATED(5.8, "Please store metadata in columns instead of using UI capabilities") ITypedElementUiCapability : public ISlateMetaData`  
_L12-18_
- inherits: `ISlateMetaData`
- desc: UI Capabilities are objects that can be stored as meta data on widgets created through TEDS UI and describe the functionality offered by the widget. This allows arbitrary widgets to describe themselves and allows users of TEDS UI to call into or register with the widget.
- L15 _public prototype_ `SLATE_METADATA_TYPE(ITypedElementUiCapability, ISlateMetaData) ~ITypedElementUiCapability() override = default;`

### `Source/Runtime/TypedElementFramework/Public/TedsRevisionControlStateHelper.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace RevisionControl` (scope `UE::Editor`)
- L21 _prototype_ `UE::Editor::DataStorage::RowHandle FindOrAddPackageRow( UE::Editor::DataStorage::ICoreProvider& DataStorage, const FString& InFilename);` (scope `UE::Editor::RevisionControl`) — Look up the package row for InFilename in the SourceControl mapping domain, creating one if it doesn't exist. Returns InvalidRowHandle if the package table hasn't been registered yet.
- L31 _prototype_ `void ApplySccStateUpdate( UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::RowHandle Row, const FSccStateColumn& NewState);` (scope `UE::Editor::RevisionControl`) — Write NewState to Row, always add FSCCStatusUpdateEndedTag, and activate UpdateSCCForActors so the viewport overlay refreshes. Callers build NewState from their provider-specific state (FPerforceSourceControlState / FSkeinSourceControlState) and hand it off.
