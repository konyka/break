# Plugins / WorldConditions

- module root: `Plugins/Runtime/WorldConditions/Source/WorldConditions`
- headers: 6; symbols: 267
- symbol kinds: class=2, enum=7, enumerator=20, function=96, macro=4, member=52, namespace=2, prototype=63, struct=20, variable=1

### `Plugins/Runtime/WorldConditions/Source/WorldConditions/Public/WorldConditionBase.h` (Public)


#### struct `FWorldConditionBase`  
`struct FWorldConditionBase`  
_L117-213_
- reflection: `USTRUCT(meta=(Hidden))`
- desc: Base struct for all World Conditions. World Conditions are used together with World Condition Query to create expressions of conditions whose result can be checked. The conditions can be based on globally accessible data (e.g. subsystems), or based on any of the context data accessible via FWorldConditionContext. The data that is available is defined for each use case using a UWorldConditionSchema. It also defines which conditions are available when creating a query in that use case. FWorldConditionContextDataRef allows to reference a specific context data. When added on a world condition as property, the UI allows to pick context data of specified type, and in code, pointer to the actual data can be accessed via the context. UPROPERTY(EditAnywhere, Category="Default", meta=(BaseStruct="/Script/ModuleFoo.StructBar")) FWorldConditionContextDataRef BarRef; FWorldConditionResult FWorldConditionFoo::IsTrue(const FWorldConditionContext& Context) const { if (FStructBar* Bar = Context.GetMutableContextDataPtr<FStructBar>(BarRef)) { } ... } Under the hood a reference is a name that needs to be turned into an index before use. This is done on Initialize(): bool FWorldConditionFoo::Initialize(const UWorldConditionSchema& Schema) { if (!Schema.ResolveContextDataRef<FStructBar>(BarRef)) { return false; } ... } To speed up query evaluation, the result of a World Condition can be cached by World Condition Query. A result can be cached, if the condition is based on globally accessible data,
- L121 _public function_ `FWorldConditionBase() : bIsStateObject(false) , bCanCacheResult(true) , bInvert(false)`
- L127 _public prototype_ `virtual ~FWorldConditionBase();`
- L130 _public function_ `virtual TObjectPtr<const UStruct>* GetRuntimeStateType() const` — @return The Instance data type of the condition.
- L133 _public prototype_ `virtual FText GetDescription() const;` — @return Description to be shown in the UI or any debug tool.
- L143 _public prototype_ `virtual bool Initialize(const UWorldConditionSchema& Schema);` — Initializes the condition to be used with a specific schema. This is called on PostLoad(), or during editing to make sure the data stays in sync with the schema. This is the place to resolve all the Context Data References, and set bCanCacheResult based on if the context data type. @param Schema The schema to initialize the condition for. @return True if init succeeded.
- L151 _public prototype_ `virtual bool Activate(const FWorldConditionContext& Context) const;` — Called to activate the condition. The state data for the conditions can be accessed via the Context. @param Context Context that stores the context data and state of the query. @return True if activation succeeded.
- L159 _public prototype_ `virtual FWorldConditionResult IsTrue(const FWorldConditionContext& Context) const;` — Called to check the condition state. The state data for the conditions can be accessed via the Context. @param Context Context that stores the context data and state of the query. @return The state of the condition.
- L166 _public prototype_ `virtual void Deactivate(const FWorldConditionContext& Context) const;` — Called to deactivate the condition. The state data for the conditions can be accessed via the Context. @param Context Context that stores the context data and state of the query.
- L169 _public function_ `uint16 GetStateDataOffset() const` — @return offset in state memory where the conditions state is stored.
- L172 _public function_ `uint8 GetConditionIndex() const` — @return condition index.
- L175 _public function_ `bool IsStateObject() const` — @return true if the state of the condition is UObject.
- L178 _public function_ `bool ShouldInvertResult() const` — @return true if conditions result should be inverted. Applied by the expression evaluator.
- L181 _public function_ `EWorldConditionOperator GetOperator() const` — @return operator to apply for this condition in the expression evaluation.
- L184 _public function_ `uint8 GetNextExpressionDepth() const` — @return expression depth used by the expression evaluator.
- L188 _protected member_ `uint16 StateDataOffset = 0;` — Used internally, Offset of the data in the State storage.
- L191 _protected member_ `uint8 ConditionIndex = 0;` — Used internally, Index of the condition in the definition and state storage.
- L194 _protected member_ `uint8 bIsStateObject : 1;` — Used Internally, true if the condition has Object state.
- L197 _protected member_ `uint8 bCanCacheResult : 1;` — Set to true if the result of the IsTrue() can be cached.
- L201 _protected member_ `uint8 bInvert : 1;` — `UPROPERTY()` — Controls whether the value of the expressions as calculated by IsTrue should be inverted. The inversion is handled by the expression evaluator.
- L205 _protected member_ `EWorldConditionOperator Operator = EWorldConditionOperator::And;` — `UPROPERTY()` — Operator describing how the results of the condition is combined with other conditions. Not used directly, but to set up condition item in query state.
- L209 _protected member_ `uint8 NextExpressionDepth = 0;` — `UPROPERTY()` — Depth controlling the parenthesis of the expression. Not used directly, but to set up condition item in query state.

#### struct `FWorldConditionCommonBase`  
`struct FWorldConditionCommonBase : public FWorldConditionBase`  
_L220-223_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FWorldConditionBase`
- desc: Base struct for world conditions that do not need a specific context data to work (e.g. interfaces a subsystem).

#### struct `FWorldConditionCommonActorBase`  
`struct FWorldConditionCommonActorBase : public FWorldConditionBase`  
_L229-232_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FWorldConditionBase`
- desc: Base struct for world conditions that require just an AActor as a context data to work.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WORLDCONDITIONS_API`

### `Plugins/Runtime/WorldConditions/Source/WorldConditions/Public/WorldConditionContext.h` (Public)


#### struct `FWorldConditionContextData`  
`struct FWorldConditionContextData`  
_L56-194_
- desc: Container for World Condition context data for a specific schema.
- L58 _public prototype_ `FWorldConditionContextData() = default;`
- L61 _public prototype_ `FWorldConditionContextData(const FWorldConditionContextData& Other) = delete;` — FWorldConditionContextData should not be stored for longer durations.
- L62 _public prototype_ `FWorldConditionContextData(FWorldConditionContextData&& Other) = delete;`
- L63 _public prototype_ `FWorldConditionContextData& operator=(const FWorldConditionContextData& Other) = delete;`
- L64 _public prototype_ `FWorldConditionContextData& operator=(FWorldConditionContextData&& Other) = delete;`
- L66 _public function_ `explicit FWorldConditionContextData(const UWorldConditionSchema& InSchema)`
- L72 _public function_ `bool IsValid() const` — @return True if the context data is initialized with a schema.
- L75 _public function_ `bool IsSchemaChildOf(const UWorldConditionSchema* OtherSchema) const` — @return True if Schema and OtherSchema are valid pointers, and the schema for the context data is child of other context.
- L81 _public function_ `const UWorldConditionSchema* GetSchema() const` — @return the schema the context data is initialized for.
- L84 _public function_ `void SetSchema(const UWorldConditionSchema& InSchema)` — Sets schema for the context data and initializes data views.
- L95 _public function_ `bool SetContextData(const FWorldConditionContextDataRef& Ref, const FConstStructView StructView)` — Sets context data from a struct view at location specified by Ref.
- L109 _public function_ `template <typename T> typename TEnableIf<!TIsDerivedFrom<T, UObject>::IsDerived, bool>::Type SetContextData(const FWorldConditionContextDataRef& Ref, const T* Value)` — Sets context data Struct at location specified by Ref.
- L123 _public function_ `template <typename T> typename TEnableIf<TIsDerivedFrom<T, UObject>::IsDerived, bool>::Type SetContextData(const FWorldConditionContextDataRef& Ref, const T* Object)` — Sets context data Object at location specified by Ref.
- L137 _public function_ `template <typename T> typename TEnableIf<!TIsDerivedFrom<T, UObject>::IsDerived, bool>::Type SetContextData(const FName Name, const T* Value)` — Sets context data Struct at location specified by Name.
- L152 _public function_ `template <typename T> typename TEnableIf<TIsDerivedFrom<T, UObject>::IsDerived, bool>::Type SetContextData(const FName Name, const T* Object)` — Sets context data Object at location specified by Name.
- L166 _public function_ `EWorldConditionContextDataType GetContextDataType(const FWorldConditionContextDataRef& Ref) const` — @return Type of the referenced context data.
- L174 _public function_ `template <typename T> T* GetContextDataPtr(const FWorldConditionContextDataRef& Ref) const` — @return Pointer to referenced context data.
- L182 _public function_ `template <typename T> T* TryGetContextDataPtr(const FWorldConditionContextDataRef& Ref) const` — @return Pointer to referenced context data if the type is correct, else returns nullptr.
- L190 _protected member_ `const UWorldConditionSchema* Schema = nullptr;` — Pointer to schema used to initialize the context data.
- L193 _protected member_ `TArray<FWorldConditionDataView> Views;` — Views to context data.

#### struct `FWorldConditionContext`  
`struct FWorldConditionContext`  
_L200-305_
- desc: The World Condition context is used to activate, update, and deactivate a world condition. It ties together the context data, query definition, and query state, and allows data access for the query conditions.
- L202 _public function_ `explicit FWorldConditionContext(FWorldConditionQueryState& InQueryState, const FWorldConditionContextData& InContextData) : QueryState(InQueryState) , ContextData(InContextData)`
- L210 _public prototype_ `FWorldConditionContext(const FWorldConditionContext& Other) = delete;` — FWorldConditionContext should not be stored for longer durations.
- L211 _public prototype_ `FWorldConditionContext(FWorldConditionContext&& Other) = delete;`
- L212 _public prototype_ `FWorldConditionContext& operator=(const FWorldConditionContext& Other) = delete;`
- L213 _public prototype_ `FWorldConditionContext& operator=(FWorldConditionContext&& Other) = delete;`
- L216 _public function_ `const UObject* GetOwner() const` — @return Pointer to owner of the world conditions to be updated.
- L219 _public function_ `UWorld* GetWorld() const` — @return Pointer to world of the owner of the world conditions to be updated.
- L222 _public function_ `const UWorldConditionSchema* GetSchema() const` — @return Pointer to the schema of the context data passed to the conditions.
- L225 _public function_ `EWorldConditionContextDataType GetContextDataType(const FWorldConditionContextDataRef& Ref) const` — @return Type of the referenced context data.
- L232 _public function_ `template <typename T> T* GetContextDataPtr(const FWorldConditionContextDataRef& Ref) const` — @return Pointer to referenced context data.
- L242 _public function_ `template <typename ...T> TTuple<T*...> GetContextDataTuplePtr(const FWorldConditionContextDataRef& Ref) const` — Usage Example : auto [Actor, Position] = Context.GetContextDataTuplePtr<AActor, FVector>(Ref); @return a tuple of pointers of the given types to the property if possible, nullptr otherwise.
- L249 _public function_ `template <typename T> typename T::FStateType& GetState(const T& Condition) const` — @return Struct State data of the specific world condition.
- L257 _public function_ `template <typename T> typename T::UStateType& GetState(const T& Condition) const` — @return Object State data of the specific world condition.
- L264 _public function_ `FWorldConditionQueryState& GetQueryState() const` — @return Reference to the query state of update world condition query.
- L272 _public function_ `FWorldConditionResultInvalidationHandle GetInvalidationHandle(const FWorldConditionBase& Condition) const` — Returns handle that can be used to invalidate specific condition and recalculate the condition. The handle can be acquired via FWorldConditionContext or FWorldConditionQueryState and is guaranteed to be valid while the query is active. @return Invalidation handle.
- L281 _public prototype_ `bool Activate() const;` — Calls Activate() on the world conditions in the query. @return true of the activation succeeded, or false if failed. Failed queries will return false when IsTrue() is called.
- L289 _public prototype_ `bool IsTrue() const;` — Evaluates the result of the query. Intermediate results may be cached, and are stored in the query state. If a cached result is invalidated, or the query relies on dynamic context data, IsTrue() is called on the necessary conditions. @return the value of the query condition expression.
- L294 _public prototype_ `void Deactivate() const;` — Calls Deactivate() on the world conditions in the query.
- L298 _protected member_ `UWorld* World = nullptr;` — World of the QueryState.Owner.
- L301 _protected member_ `FWorldConditionQueryState& QueryState;` — Reference to the query state of the query to be updated.
- L304 _protected member_ `const FWorldConditionContextData& ContextData;` — Reference to the context data for the query to be updated.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WORLDCONDITIONS_API`

### `Plugins/Runtime/WorldConditions/Source/WorldConditions/Public/WorldConditionQuery.h` (Public)


#### struct `FWorldConditionEditable`  
`struct FWorldConditionEditable`  
_L40-96_
- reflection: `USTRUCT()`
- desc: Struct used to store a world condition in editor or to apply hotfixes. Used internally. Note that the Operator and ExpressionDepth are stored here separately from the World Condition to make sure they are not reset if the Condition is empty.
- L44 _public prototype_ `FWorldConditionEditable() = default;`
- L46 _public function_ `FWorldConditionEditable(const uint8 InExpressionDepth, const EWorldConditionOperator InOperator, const FConstStructView InCondition) : ExpressionDepth(InExpressionDepth) , Operator(InOperator) , Condition(InCondition)`
- L53 _public function_ `FWorldConditionEditable(const uint8 InExpressionDepth, const EWorldConditionOperator InOperator, const bool bInInvert, const FConstStructView InCondition) : ExpressionDepth(InExpressionDepth) , Operator(InOperator) , bInvert(bInInvert) , Condition(InCondition)`
- L61 _public function_ `void Reset()`
- L68 _public function_ `bool operator==(const FWorldConditionEditable& Other) const`
- L76 _public function_ `bool operator!=(const FWorldConditionEditable& Other) const`
- L83 _public member_ `uint8 ExpressionDepth = 0;` — `UPROPERTY(EditAnywhere, Category="Default")` — Expression depth controlling the parenthesis of the expression.
- L87 _public member_ `EWorldConditionOperator Operator = EWorldConditionOperator::And;` — `UPROPERTY(EditAnywhere, Category="Default")` — Operator describing how the results of the condition is combined with other conditions.
- L91 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category="Default")` — Controls whether the value of the expressions as calculated by IsTrue should be inverted.
- L95 _public member_ `FInstancedStruct Condition;` — `UPROPERTY(EditAnywhere, Category="Default")` — Instance of a world condition.

#### struct `FWorldConditionQuerySharedDefinition`  
`struct FWorldConditionQuerySharedDefinition`  
_L103-172_
- reflection: `USTRUCT()`
- desc: Class that describes a specific configuration of a world condition. Should not be used directly. It is shared between all query states initialized with a specific FWorldConditionQueryDefinition.
- L107 _public function_ `FWorldConditionQuerySharedDefinition() : bIsLinked(false)`
- L112 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L113 _public prototype_ `bool Identical(const FWorldConditionQuerySharedDefinition* Other, uint32 PortFlags) const;`
- L116 _public function_ `TSubclassOf<UWorldConditionSchema> GetSchemaClass() const` — @return the schema used for the definition.
- L122 _public function_ `const FInstancedStructContainer& GetConditions() const` — @return conditions in the definition.
- L128 _public function_ `int32 GetStateSize() const` — @return the amount of memory needed for the state (in bytes).
- L134 _public function_ `int32 GetStateMinAlignment() const` — @return the alignment of the memory needed for the state (in bytes).
- L140 _public function_ `bool IsLinked() const` — @return true if the shared definition is successfully linked.
- L148 _private prototype_ `bool Link(const UObject* Outer);` — Updates the state memory layout and initializes the conditions.
- L151 _private prototype_ `void Set(const TSubclassOf<UWorldConditionSchema> InSchema, const TArrayView<FConstStructView> InConditions);` — Sets the definition data.
- L152 _private prototype_ `void Set(const TSubclassOf<UWorldConditionSchema> InSchema, const TArrayView<FStructView> InConditions);`
- L156 _private member_ `FInstancedStructContainer Conditions;` — `UPROPERTY()` — All the conditions of the world conditions.
- L160 _private member_ `TSubclassOf<UWorldConditionSchema> SchemaClass;` — `UPROPERTY()` — Schema used to create the conditions.
- L163 _private member_ `int32 StateMinAlignment = 8;` — Min alignment of the state storage
- L166 _private member_ `int32 StateSize = 0;` — Size of the state storage
- L169 _private member_ `uint8 bIsLinked : 1;` — Flag indicating the last result of Link(), if true, the definition is ready to use.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FWorldConditionQuerySharedDefinition> : public TStructOpsTypeTraitsBase2<FWorldConditionQuerySharedDefinition>`  
_L175-182_
- inherits: `TStructOpsTypeTraitsBase2<FWorldConditionQuerySharedDefinition>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L178-181_

#### struct `FWorldConditionQueryDefinition`  
`struct FWorldConditionQueryDefinition`  
_L190-294_
- reflection: `USTRUCT(BlueprintType)`
- desc: Definition of a world condition. The mutable state of the world condition is stored in FWorldConditionQueryState. This allows to reuse the definitions and minimize the runtime memory needed to run queries.
- L195 _public prototype_ `void SetSchemaClass(const TSubclassOf<UWorldConditionSchema> InSchema);` — Sets the schema class that is used to create the conditions.
- L198 _public function_ `TSubclassOf<UWorldConditionSchema> GetSchemaClass() const` — @return the schema class of the definition.
- L204 _public prototype_ `bool IsValid() const;` — @return true of the definition has conditions and has been initialized.
- L242 _public prototype_ `bool Initialize(const UObject* Outer, EInitializationMode InitializationMode = EInitializationMode::Default);` — Initialized the condition from editable data. @param Outer Used in logging error messages, optional @param InitializationMode Indicates how the method will handle an empty list of Editable conditions @return true if initialization succeeded.
- L244 _public prototype_ `bool Serialize(FArchive& Ar);`
- L245 _public prototype_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText, FArchive* InSerializingArchive = nullptr);`
- L246 _public prototype_ `bool ExportTextItem(FString& ValueStr, FWorldConditionQueryDefinition const& DefaultValue, class UObject* Parent, int32 PortFlags, class UObject* ExportRootScope) const;`
- L247 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector) const;`
- L248 _public prototype_ `bool Identical(const FWorldConditionQueryDefinition* Other, uint32 PortFlags) const;`
- L252 _public prototype_ `bool Initialize(const UObject* Outer, const TSubclassOf<UWorldConditionSchema> InSchemaClass, const TConstArrayView<FWorldConditionEditable> InConditions);` — Initialized the condition with specific data.
- L255 _public function_ `void AddCondition(const FWorldConditionEditable& NewCondition)` — Adds a single condition to the definition. The condition will not be in use until Initialize() is called, and a state is initialized.
- L262 _public prototype_ `FText GetDescription() const;` — @returns description of the query expression.
- L264 _public function_ `FWorldConditionQuerySharedDefinition* GetSharedDefinition() const`
- L269 _public function_ `FSharedStruct GetSharedDefinitionStruct() const`
- L274 _public prototype_ `static bool TryRetargetingPathToConditions(FPropertyBindingPath& InOutPath);`
- L282 _private member_ `FSharedStruct SharedDefinition;` — `UPROPERTY(transient)` — The definition used to initialize and execute world conditions. Created from editable conditions during edit via Initialize().
- L286 _private member_ `TSubclassOf<UWorldConditionSchema> SchemaClass;` — `UPROPERTY()` — Schema of the definition, also stored in SharedDefinition.
- L293 _private member_ `TArray<FWorldConditionEditable> EditableConditions;` — `UPROPERTY(EditAnywhere, Category="Default", meta=(BaseStruct = "/Script/SmartObjectsModule.WorldCondition"))` — Conditions used while editing, converted in to Conditions via Initialize(). Those will be cleared for cooked builds but can still be used by hotfixes.

#### enum `FWorldConditionQueryDefinition::EInitializationMode`  
`enum class EInitializationMode : uint8`  
_L206-234_
- L211 _public enumerator_ `ResetSharedDefinitionOnEmptyConditions` — The Initialize function will create a SharedDefinition only if there are Editable conditions, otherwise it will be invalid.
- L216 _public enumerator_ `UseExistingSharedDefinitionOnEmptyConditions` — The Initialize function will preserve the existing SharedDefinition if there are no Editable conditions.
- L230 _public enumerator_ `Default = ResetSharedDefinitionOnEmptyConditions #else Default = UseExistingSharedDefinitionOnEmptyConditions #endif`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FWorldConditionQueryDefinition> : public TStructOpsTypeTraitsBase2<FWorldConditionQueryDefinition>`  
_L297-308_
- inherits: `TStructOpsTypeTraitsBase2<FWorldConditionQueryDefinition>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L300-307_

#### struct `FWorldConditionItem`  
`struct FWorldConditionItem`  
_L315-335_
- reflection: `USTRUCT()`
- desc: Item used to describe the structure of a world condition query for fast traversal of the expression.
- L319 _public prototype_ `FWorldConditionItem() = default;`
- L321 _public function_ `explicit FWorldConditionItem(const EWorldConditionOperator InOperator, const uint8 InNextExpressionDepth) : Operator(InOperator) , NextExpressionDepth(InNextExpressionDepth)`
- L328 _public member_ `EWorldConditionOperator Operator = EWorldConditionOperator::And;` — Operator describing how the results of the condition is combined with other conditions.
- L331 _public member_ `uint8 NextExpressionDepth = 0;` — Expression depth controlling the parenthesis of the expression.
- L334 _public member_ `EWorldConditionResultValue CachedResult = EWorldConditionResultValue::Invalid;` — Cached result of the condition.

#### struct `FWorldConditionStateObject`  
`struct FWorldConditionStateObject`  
_L341-347_
- reflection: `USTRUCT()`
- desc: Struct used to store the pointer to an UObject based condition state.
- L346 _public member_ `TObjectPtr<UObject> Object;` — `UPROPERTY()`

#### struct `FWorldConditionResultInvalidationHandle`  
`struct FWorldConditionResultInvalidationHandle`  
_L355-386_
- desc: Handle that can be used to invalidate the cached result of a condition (and query). The handle can be acquired via FWorldConditionContext or FWorldConditionQueryState and is guaranteed to be valid while the query is active.
- L357 _public prototype_ `FWorldConditionResultInvalidationHandle() = default;`
- L360 _public function_ `bool IsValid() const` — @return True if the handle is valid.
- L363 _public function_ `void Reset()` — Resets the handle.
- L372 _public prototype_ `void InvalidateResult() const;` — When called invalidates the result of the query and condition.
- L376 _protected function_ `explicit FWorldConditionResultInvalidationHandle(const TWeakPtr<uint8>& InStateMemory, const int32 InItemOffset) : WeakStateMemory(InStateMemory) , ItemOffset(InItemOffset)`
- L382 _protected member_ `TWeakPtr<uint8> WeakStateMemory = nullptr;`
- L383 _protected member_ `int32 ItemOffset = 0;`

#### struct `FWorldConditionQueryState`  
`struct FWorldConditionQueryState`  
_L397-568_
- reflection: `USTRUCT()`
- desc: Runtime state of a world conditions. The structure of the data for the state is defined in a query definition. The definition and conditions are stored in FWorldConditionQueryDefinition. This allows to reuse the definitions and minimize the runtime memory needed to run queries. Note: Any code embedding this struct is responsible for calling AddReferencedObjects().
- L401 _public function_ `FWorldConditionQueryState() : bIsInitialized(false) , bAreConditionsActivated(false)`
- L407 _public function_ `FWorldConditionQueryState(const FWorldConditionQueryState& Other) : FWorldConditionQueryState()`
- L413 _public function_ `FWorldConditionQueryState(FWorldConditionQueryState&& Other) : NumConditions(Other.NumConditions) , bIsInitialized(Other.bIsInitialized) , bAreConditionsActivated(Other.bAreConditionsActivated) , Memory(MoveTemp(Other.Memory)) , SharedDefinition(MoveTemp(Other.SharedDefinition)) , Owner(MoveTemp(Other.Owner))`
- L423 _public function_ `FWorldConditionQueryState& operator=(FWorldConditionQueryState&& Other)`
- L438 _public prototype_ `~FWorldConditionQueryState();`
- L440 _public function_ `FWorldConditionQueryState& operator=(const FWorldConditionQueryState& RHS)`
- L447 _public function_ `bool IsInitialized() const` — @return True if the state is properly initialized.
- L457 _public prototype_ `void Initialize(const UObject& Owner, const FWorldConditionQueryDefinition& QueryDefinition);` — Initialized the state for a specific query definition. @param Owner Owner of any objects created during Init(). @param QueryDefinition definition of the state to initialize.
- L463 _public prototype_ `void Free();` — Frees the allocated data and objects. The definition must be the same as used in init as it is used to traverse the structure in memory.
- L466 _public function_ `bool AreConditionsActivated() const` — @return True if the conditions were activated.
- L472 _public function_ `void SetConditionsActivated(const bool bConditionsActivated)` — Sets the status of the conditions for this state.
- L478 _public function_ `EWorldConditionResultValue GetCachedResult() const` — @return cached result stored in the state.
- L486 _public function_ `FWorldConditionItem& GetItem(const int32 Index) const` — @return Condition item at specific index
- L494 _public function_ `UObject* GetStateObject(const FWorldConditionBase& Condition) const` — @return Object describing the state of a specified condition.
- L505 _public function_ `FStructView GetStateStruct(const FWorldConditionBase& Condition) const` — @return struct describing the state of a specified condition.
- L517 _public function_ `int32 GetNumConditions() const` — @return The number of conditions in the state data.
- L520 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector);` — Adds referenced objects to the collector.
- L528 _public prototype_ `FWorldConditionResultInvalidationHandle GetInvalidationHandle(const FWorldConditionBase& Condition) const;` — Returns handle that can be used to invalidate specific condition and recalculate the condition. The handle can be acquired via FWorldConditionContext or FWorldConditionQueryState and is guaranteed to be valid while the query is active. @return Invalidation handle.
- L531 _public function_ `const UObject* GetOwner() const` — @return the owner the state was initialized with.
- L534 _public function_ `const FWorldConditionQuerySharedDefinition* GetSharedDefinition() const` — @return shared definition used to initialize the state, or nullptr if query is empty.
- L540 _public function_ `void SetCachedResult(const EWorldConditionResultValue InResult) const` — Sets the combined cached result of the query.
- L551 _public member_ `static constexpr int32 CachedResultOffset = 0;` — Offset in state memory where cached result is.
- L554 _public member_ `static constexpr int32 ItemsOffset = static_cast<int32>(Align(sizeof(EWorldConditionResultValue), alignof(FWorldConditionItem)));` — Offset in state memory where condition items are.
- L558 _private prototype_ `void InitializeInternal(const UObject* InOwner, const FSharedStruct InSharedDefinition);`
- L560 _private member_ `uint8 NumConditions = 0;`
- L561 _private member_ `uint8 bIsInitialized : 1;`
- L562 _private member_ `uint8 bAreConditionsActivated : 1;`
- L563 _private member_ `TSharedPtr<uint8> Memory = nullptr;`
- L564 _private member_ `FSharedStruct SharedDefinition;`
- L567 _private member_ `TObjectPtr<const UObject> Owner = nullptr;` — `UPROPERTY(Transient)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FWorldConditionQueryState> : public TStructOpsTypeTraitsBase2<FWorldConditionQueryState>`  
_L571-577_
- inherits: `TStructOpsTypeTraitsBase2<FWorldConditionQueryState>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L574-576_

#### struct `FWorldConditionQuery`  
`struct FWorldConditionQuery`  
_L584-629_
- reflection: `USTRUCT()`
- desc: General purpose World Condition Query that combines Query Definition and Query State in one.
- L589 _public prototype_ `bool IsActive() const;` — @return True if the query is activated.
- L597 _public prototype_ `bool Activate(const UObject& Owner, const FWorldConditionContextData& ContextData) const;` — Activates the world conditions in the query. @param Owner Owner of any objects created during Activate(). @param ContextData ContextData that matches the schema of the query. @return true of the activation succeeded, or false if failed. Failed queries will return false when IsTrue() is called.
- L605 _public prototype_ `bool IsTrue(const FWorldConditionContextData& ContextData) const;` — Returns the result of the query. Cached state is returned if it is available, if update is needed or the query has dynamic context data, IsTrue() is called on the necessary conditions. @param ContextData ContextData that matches the schema of the query. @return the value of the query condition expression.
- L611 _public prototype_ `void Deactivate(const FWorldConditionContextData& ContextData) const;` — Deactivates the world conditions in the query. @param ContextData ContextData that matches the schema of the query.
- L618 _public prototype_ `bool DebugInitialize(const UObject* Outer, const TSubclassOf<UWorldConditionSchema> InSchemaClass, const TConstArrayView<FWorldConditionEditable> InConditions);` — Initializes a query from array of conditions for testing. @return true of the query was created and initialized.
- L624 _protected member_ `FWorldConditionQueryDefinition QueryDefinition;` — `UPROPERTY(EditAnywhere, Category="Default")` — Defines the conditions to run on the query.
- L628 _protected member_ `mutable FWorldConditionQueryState QueryState;` — `UPROPERTY(Transient)` — Runtime state of the query.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API WORLDCONDITIONS_API`
- L179 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anone7b5fde50103`)
- L180 _enumerator_ `WithIdentical = true` (scope `TStructOpsTypeTraits::__anone7b5fde50103`)
- L301 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anone7b5fde50203`) — Ensures that the SharedDefinition gets copied too.
- L302 _enumerator_ `WithIdentical = true` (scope `TStructOpsTypeTraits::__anone7b5fde50203`)
- L303 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anone7b5fde50203`)
- L304 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anone7b5fde50203`)
- L305 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anone7b5fde50203`)
- L306 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anone7b5fde50203`)
- L575 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anone7b5fde50303`)

### `Plugins/Runtime/WorldConditions/Source/WorldConditions/Public/WorldConditionSchema.h` (Public)


#### class `UWorldConditionSchema`  
`class UWorldConditionSchema : public UObject`  
_L44-161_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L51 _public function_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const` — @return True if world condition of the specific type is allowed.
- L54 _public prototype_ `TConstArrayView<FWorldConditionContextDataDesc> GetContextDataDescs() const;` — @return All condition descriptors.
- L57 _public prototype_ `const FWorldConditionContextDataDesc* GetContextDataDescByName(const FName DataName, const TArray<const UStruct*>& Structs) const;` — @return Context data descriptor of specific name and types.
- L60 _public prototype_ `const FWorldConditionContextDataDesc* GetContextDataDescByRef(const FWorldConditionContextDataRef& Ref) const;` — @return Context data descriptor of specific name and type.
- L63 _public prototype_ `const FWorldConditionContextDataDesc& GetContextDataDescByIndex(const int32 Index) const;` — @return Context data descriptor of specified index.
- L66 _public prototype_ `EWorldConditionContextDataType GetContextDataTypeByRef(const FWorldConditionContextDataRef& Ref) const;` — @return Context data type based on reference.
- L69 _public prototype_ `EWorldConditionContextDataType GetContextDataTypeByIndex(const int32 Index) const;` — @return Context data type based on index.
- L72 _public prototype_ `FWorldConditionContextDataRef GetContextDataRefByName(const FName DataName, const UStruct* Struct) const;` — @return Context data reference of specific name and type.
- L75 _public prototype_ `int32 GetContextDataIndexByName(const FName DataName, const UStruct* Struct) const;` — @return Context data index by name.
- L84 _public function_ `template <typename Head, typename NextHead, typename... Tail> typename TEnableIf<TIsDerivedFrom<Head, UObject>::IsDerived, bool>::Type ResolveContextDataRef(FWorldConditionContextDataRef& Ref) const` — Resolves the index of the context data reference to an object data, based on the name in the reference and the types from the template. Usage example : Schema.ResolveContextDataRef<AActor, FVector>(SourceWorldConditionContextDataRef) @param Ref Reference to resolve. @return True if the reference was resolved.
- L103 _public function_ `template <typename Head> typename TEnableIf<TIsDerivedFrom<Head, UObject>::IsDerived, bool>::Type ResolveContextDataRef(FWorldConditionContextDataRef& Ref) const` — Resolves the index of the context data reference to an object data, based on the name in the reference and the type from the template. Usage example : Schema.ResolveContextDataRef<AActor>(SourceActorWorldConditionContextDataRef) @param Ref Reference to resolve. @return True if the reference was resolved.
- L123 _public function_ `template <typename Head, typename NextHead, typename... Tail> typename TEnableIf<!TIsDerivedFrom<Head, UObject>::IsDerived, bool>::Type ResolveContextDataRef(FWorldConditionContextDataRef& Ref) const` — Resolves the index of the context data reference to a Struct context data, based on the name in the reference and the types from the template. Usage example : Schema.ResolveContextDataRef<AActor, FVector>(SourceWorldConditionContextDataRef) @param Ref Reference to resolve. @return True if the reference was resolved.
- L141 _public function_ `template <typename Head> typename TEnableIf<!TIsDerivedFrom<Head, UObject>::IsDerived, bool>::Type ResolveContextDataRef(FWorldConditionContextDataRef& Ref) const` — Resolves the index of the context data reference to a Struct context data, based on the name in the reference and the type from the template. Usage example : Schema.ResolveContextDataRef<AActor>(SourceActorWorldConditionContextDataRef) @param Ref Reference to resolve. @return True if the reference was resolved.
- L156 _protected prototype_ `FWorldConditionContextDataRef AddContextDataDesc(const FName InName, const UStruct* InStruct, const EWorldConditionContextDataType InType);` — Adds a context data descriptor and returns reference to it.
- L160 _protected member_ `TArray<FWorldConditionContextDataDesc> ContextDataDescs;` — `UPROPERTY()` — All context data descriptors.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WORLDCONDITIONS_API`

### `Plugins/Runtime/WorldConditions/Source/WorldConditions/Public/WorldConditionTypes.h` (Public)


#### enum `EWorldConditionResultValue`  
`enum class EWorldConditionResultValue : uint8`  
_L12-20_
- reflection: `UENUM()`
- desc: Result of a world condition
- L15 _public enumerator_ `IsFalse = 0` — The result is false.
- L17 _public enumerator_ `IsTrue = 1` — The result is true.
- L19 _public enumerator_ `Invalid = 2` — The result needs to be recalculated.

#### struct `FWorldConditionResult`  
`struct FWorldConditionResult`  
_L27-45_
- reflection: `USTRUCT()`
- desc: Result of a world condition evaluation. Also contains additional information related to that result (e.g. if the result can be cached or not)
- L31 _public prototype_ `FWorldConditionResult() = default;`
- L32 _public function_ `FWorldConditionResult(const EWorldConditionResultValue Result, const bool bCanResultBeCached) : Value(Result) , bCanBeCached(bCanResultBeCached)`
- L40 _public member_ `EWorldConditionResultValue Value = EWorldConditionResultValue::Invalid;` — `UPROPERTY()` — Indicates the result of a condition evaluated for a given context.
- L44 _public member_ `bool bCanBeCached = false;` — `UPROPERTY()` — Indicates that a given result can be cached or not.

#### enum `EWorldConditionOperator`  
`enum class EWorldConditionOperator : uint8`  
_L49-57_
- reflection: `UENUM()`
- desc: Boolean operator between conditions in a expression.
- L52 _public enumerator_ `And` — Boolean And
- L54 _public enumerator_ `Or` — Boolean Or
- L56 _public enumerator_ `Copy UMETA(Hidden)` — Used internally, signifies that a right value is copied over left value.

#### enum `EWorldConditionContextDataType`  
`enum class EWorldConditionContextDataType : uint8`  
_L100-106_
- reflection: `UENUM()`
- desc: Describes the availability of a context data.
- L103 _public enumerator_ `Dynamic` — The context data might change on each call, must check for validity, and is only available on IsTrue().
- L105 _public enumerator_ `Persistent` — The context data is the same during the lifetime of the condition, must check for validity on Activate()/IsTrue(), might not be available on Deactivate().

#### struct `FWorldConditionContextDataDesc`  
`struct FWorldConditionContextDataDesc`  
_L114-157_
- reflection: `USTRUCT()`
- desc: Describes context data available for a world conditions. The descriptors are defined in UWorldConditionSchema, and context data is referred using FWorldConditionContextDataRef.
- L118 _public prototype_ `FWorldConditionContextDataDesc() = default;`
- L119 _public function_ `explicit FWorldConditionContextDataDesc(const FName InName, const UStruct* InStruct, const EWorldConditionContextDataType InType) : Struct(InStruct) , Name(InName) , Type(InType)`
- L126 _public function_ `bool MatchesType(const UStruct* TypeToMatch) const`
- L148 _public member_ `TObjectPtr<const UStruct> Struct;` — `UPROPERTY()` — Type of the context data, can be a struct or object.
- L152 _public member_ `FName Name;` — `UPROPERTY()` — Name of the context data, which is used together with the type struct to find specific data to use.
- L156 _public member_ `EWorldConditionContextDataType Type = EWorldConditionContextDataType::Dynamic;` — `UPROPERTY()` — Type of the context data, See EWorldConditionContextDataType.

#### struct `FWorldConditionContextDataRef`  
`struct FWorldConditionContextDataRef`  
_L165-198_
- reflection: `USTRUCT()`
- desc: Describes a reference to context data defined in UWorldConditionSchema. When placed as editable property on a World Condition, allows the user to define which context data to use, and allows quick access of that data via FWorldConditionContext.
- L170 _public member_ `static constexpr uint8 InvalidIndex = 0xff;` — Marker for invalid index value.
- L172 _public prototype_ `FWorldConditionContextDataRef() = default;`
- L174 _public function_ `explicit FWorldConditionContextDataRef(const FName InName, const uint8 InIndex = InvalidIndex) : Name(InName) , Index(InIndex)`
- L181 _public function_ `bool IsValid() const` — @return true if the data ref index is resolved.
- L184 _public function_ `uint8 GetIndex() const` — @return Referenced context data index.
- L187 _public function_ `FName GetName() const` — @return Name of the referenced data.
- L191 _protected member_ `FName Name;` — `UPROPERTY()`
- L194 _protected member_ `uint8 Index = InvalidIndex;` — `UPROPERTY()`

#### struct `FWorldConditionDataView`  
`struct FWorldConditionDataView`  
_L203-314_
- desc: View holding a pointer to context data struct or object.
- L205 _public prototype_ `FWorldConditionDataView() = default;`
- L207 _public function_ `explicit FWorldConditionDataView(const EWorldConditionContextDataType InType) : Type(InType)`
- L213 _public function_ `explicit FWorldConditionDataView(const UScriptStruct* InScriptStruct, const uint8* InMemory, const EWorldConditionContextDataType InType) : Struct(InScriptStruct) , Memory(InMemory) , Type(InType)` — `USTRUCT()`
- L223 _public function_ `explicit FWorldConditionDataView(const UObject* Object, const EWorldConditionContextDataType InType) : Struct(Object ? Object->GetClass() : nullptr) , Memory(reinterpret_cast<const uint8*>(Object)) , Type(InType)` — UOBJECT() constructor.
- L233 _public function_ `explicit FWorldConditionDataView(FConstStructView StructView, const EWorldConditionContextDataType InType) : Struct(StructView.GetScriptStruct()) , Memory(StructView.GetMemory()) , Type(InType)` — `USTRUCT()`
- L243 _public function_ `bool IsValid() const` — @return True if the view is set to valid data.
- L250 _public function_ `template <typename T> typename TEnableIf<TIsDerivedFrom<T, UObject>::IsDerived, T*>::Type GetPtr() const` — @return Pointer to object stored in the view.
- L260 _public function_ `template <typename T> typename TEnableIf<!TIsDerivedFrom<T, UObject>::IsDerived, T*>::Type GetPtr() const` — @return Pointer to struct stored in the view.
- L270 _public function_ `template <typename T> typename TEnableIf<TIsDerivedFrom<T, UObject>::IsDerived, T*>::Type TryGetPtr() const` — @return Pointer to object stored in the view if the type matches correctly, else returns nullptr.
- L284 _public function_ `template <typename T> typename TEnableIf<!TIsDerivedFrom<T, UObject>::IsDerived, T*>::Type TryGetPtr() const` — @return Pointer to struct stored in the view if the type matches correctly, else returns nullptr.
- L297 _public function_ `const UStruct* GetStruct() const` — @return Struct describing the data type.
- L300 _public function_ `const uint8* GetMemory() const` — @return Raw const pointer to the data.
- L303 _public function_ `EWorldConditionContextDataType GetType() const` — @return type of the context data.
- L307 _protected member_ `const UStruct* Struct = nullptr;` — UClass or UScriptStruct of the data.
- L310 _protected member_ `const uint8* Memory = nullptr;` — Memory pointing at the class or struct
- L313 _protected member_ `EWorldConditionContextDataType Type = EWorldConditionContextDataType::Dynamic;` — Type of the context data, copied from the descriptor.

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWorldCondition, Warning, All);`
- L59 _namespace_ `namespace UE`
- L59 _namespace_ `namespace WorldCondition` (scope `UE`)
- L62 _variable_ `constexpr int32 MaxExpressionDepth = 4;` (scope `UE::WorldCondition`) — Maximum depth of sub-expressions in an expression.
- L65 _function_ `inline EWorldConditionResultValue MergeResults(const EWorldConditionOperator Operator, const EWorldConditionResultValue InLeft, const EWorldConditionResultValue InRight)` (scope `UE::WorldCondition`) — Merges two condition results using specific operator.
- L76 _function_ `inline EWorldConditionResultValue Invert(const EWorldConditionResultValue InResult, const bool bInvert)` (scope `UE::WorldCondition`) — Inverts the result if bInvert is true. Invalid is kept intact.
- L85 _function_ `inline EWorldConditionResultValue FromOptional(const TOptional<bool>& InOptionalBool)` (scope `UE::WorldCondition`)

### `Plugins/Runtime/WorldConditions/Source/WorldConditions/Public/WorldConditionsModule.h` (Public)


#### class `IWorldConditionsModule`  
`class IWorldConditionsModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IWorldConditionsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
