# Plugins / HTNPlanner

- module root: `Plugins/AI/HTNPlanner/Source/HTNPlanner`
- headers: 7; symbols: 191
- symbol kinds: class=3, enum=4, enumerator=14, function=52, macro=1, member=41, namespace=3, prototype=41, struct=14, typedef=12, variable=6
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, GameplayTags, GameplayTasks

### `Plugins/AI/HTNPlanner/Source/HTNPlanner/Public/AI/HTNBrainComponent.h` (Public)


#### class `UHTNBrainComponent`  
`class UHTNBrainComponent : public UBrainComponent`  
_L13-22_
- reflection: `UCLASS()`
- inherits: `UBrainComponent`
- L18 _public prototype_ `UHTNBrainComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L21 _protected member_ `FHTNPlanner Planner;`

### `Plugins/AI/HTNPlanner/Source/HTNPlanner/Public/Debug/GameplayDebuggerCategory_HTN.h` (Public)


#### class `FGameplayDebuggerCategory_HTN`  
`class FGameplayDebuggerCategory_HTN : public FGameplayDebuggerCategory`  
_L12-23_
- inherits: `FGameplayDebuggerCategory`
- L15 _public prototype_ `FGameplayDebuggerCategory_HTN();`
- L17 _public prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L18 _public prototype_ `virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;`
- L20 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`

### `Plugins/AI/HTNPlanner/Source/HTNPlanner/Public/Debug/HTNDebug.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace FHTNDebug`
- L12 _prototype_ `FString HTNWorldStateCheckToString(const EHTNWorldStateCheck Value);` (scope `FHTNDebug`)
- L13 _prototype_ `FString HTNWorldStateOperationToString(const EHTNWorldStateOperation Value);` (scope `FHTNDebug`)
- L15 _prototype_ `FString GetDescription(const FHTNCondition& Condition);` (scope `FHTNDebug`)
- L16 _prototype_ `FString GetDescription(const FHTNEffect& Effect);` (scope `FHTNDebug`)
- L17 _prototype_ `FString GetDescription(const FHTNDomain& Domain, const TArray<FHTNPolicy::FTaskID>& TaskIDs, const FString& Delimiter = TEXT(", "), const int32 CurrentTaskIndex = INDEX_NONE` (scope `FHTNDebug`)
- L19 _prototype_ `FName GetTaskName(const FHTNBuilder_Domain& DomainBuilder, const FHTNPolicy::FTaskID TaskID);` (scope `FHTNDebug`)
- L20 _prototype_ `FName GetTaskName(const FHTNDomain& Domain, const FHTNPolicy::FTaskID TaskID);` (scope `FHTNDebug`)

### `Plugins/AI/HTNPlanner/Source/HTNPlanner/Public/HTNBuilder.h` (Public)


#### struct `FHTNBuilder_PrimitiveTask`  
`struct FHTNBuilder_PrimitiveTask`  
_L8-27_
- L10 _public member_ `uint32 ActionID;`
- L11 _public member_ `uint32 Parameter;`
- L12 _public member_ `TArray<FHTNEffect> Effects;`
- L14 _public function_ `void SetOperator(const uint32 InActionID, const uint32 InParameter = 0)`
- L21 _public function_ `template<typename A, typename B=uint32> void SetOperator(const A InActionID, const B InParameter = B(0))`
- L26 _public function_ `void AddEffect(const FHTNEffect& Effect)`

#### struct `FHTNBuilder_Method`  
`struct FHTNBuilder_Method`  
_L29-47_
- L31 _public member_ `TArray<FHTNCondition> Conditions;`
- L32 _public member_ `TArray<FName> Tasks;`
- L34 _public function_ `FHTNBuilder_Method()`
- L36 _public function_ `explicit FHTNBuilder_Method(const FHTNCondition& InCondition)`
- L43 _public function_ `FHTNBuilder_Method(const TArray<FHTNCondition>& InConditions) : Conditions(InConditions)`
- L46 _public function_ `void AddTask(const FName& TaskName)`

#### struct `FHTNBuilder_CompositeTask`  
`struct FHTNBuilder_CompositeTask`  
_L49-67_
- L51 _public member_ `TArray<FHTNBuilder_Method> Methods;`
- L53 _public function_ `FHTNBuilder_Method& AddMethod()`
- L58 _public function_ `FHTNBuilder_Method& AddMethod(const FHTNCondition& Condition)`
- L63 _public function_ `FHTNBuilder_Method& AddMethod(const TArray<FHTNCondition>& Conditions)`

#### struct `FHTNBuilder_Domain`  
`struct FHTNBuilder_Domain`  
_L69-98_
- desc: : public FHTNDomain
- L71 _public member_ `TSharedPtr<FHTNDomain> DomainInstance;`
- L73 _public prototype_ `FHTNBuilder_Domain();`
- L74 _public prototype_ `FHTNBuilder_Domain(const TSharedPtr<FHTNDomain>& InDomain);`
- L76 _public function_ `void SetRootName(const FName InRootName)`
- L77 _public prototype_ `FHTNBuilder_CompositeTask& AddCompositeTask(const FName& TaskName);`
- L78 _public prototype_ `FHTNBuilder_PrimitiveTask& AddPrimitiveTask(const FName& TaskName);`
- L80 _public prototype_ `FHTNBuilder_CompositeTask* FindCompositeTask(const FName& TaskName);`
- L81 _public prototype_ `FHTNBuilder_PrimitiveTask* FindPrimitiveTask(const FName& TaskName);`
- L83 _public function_ `FHTNBuilder_CompositeTask* GetRootAsCompositeTask()`
- L84 _public function_ `FHTNBuilder_PrimitiveTask* GetRootAsPrimitiveTask()`
- L89 _public prototype_ `bool Compile();` — Optimizes stored information. After the Domain is compiled it's impossible to extend it @return true if compilation was successful. False otherwise, look for warnings and errors in the log
- L91 _public prototype_ `void Decompile();` — Using DomainInstance information populate this domain builder instance
- L93 _public prototype_ `FString GetDebugDescription() const;`
- L95 _public member_ `FName RootTaskName;`
- L96 _public member_ `TMap<FName, FHTNBuilder_PrimitiveTask> PrimitiveTasks;`
- L97 _public member_ `TMap<FName, FHTNBuilder_CompositeTask> CompositeTasks;`

### `Plugins/AI/HTNPlanner/Source/HTNPlanner/Public/HTNDomain.h` (Public)


#### enum `EHTNWorldStateCheck`  
`enum class EHTNWorldStateCheck : uint8`  
_L35-46_
- reflection: `UENUM()`
- L37 _public enumerator_ `Less`
- L38 _public enumerator_ `LessOrEqual`
- L39 _public enumerator_ `Equal`
- L40 _public enumerator_ `NotEqual`
- L41 _public enumerator_ `GreaterOrEqual`
- L42 _public enumerator_ `Greater`
- L43 _public enumerator_ `IsTrue`
- L45 _public enumerator_ `MAX UMETA(Hidden)`

#### enum `EHTNWorldStateOperation`  
`enum class EHTNWorldStateOperation : uint8`  
_L49-56_
- reflection: `UENUM()`
- L51 _public enumerator_ `Set`
- L52 _public enumerator_ `Increase`
- L53 _public enumerator_ `Decrease`
- L55 _public enumerator_ `MAX UMETA(Hidden)`

#### struct `THTNWorldStateOperation`  
`template<typename TOperationEnum> struct THTNWorldStateOperation`  
_L59-105_
- L61 _public typedef_ `typedef TOperationEnum FOperationEnum;`
- L63 _public member_ `const FHTNPolicy::FWSOperationID Operation;`
- L64 _public member_ `const FHTNPolicy::FWSKey KeyLeftHand;`
- L65 _public member_ `FHTNPolicy::FWSKey KeyRightHand;`
- L66 _public member_ `FHTNPolicy::FWSValue Value;`
- L68 _public function_ `THTNWorldStateOperation(const FHTNPolicy::FWSKey InKeyLeftHand = FHTNPolicy::InvalidWSKey, const FHTNPolicy::FWSOperationID InOperation = FHTNPolicy::InvalidWSOperation) : Operation(FHTNPolicy::FWSOperationID(InOperation)), KeyLeftHand(InKeyLeftHand), KeyRightHand(FHTNPolicy::InvalidWSKey), Value(FHTNPolicy::DefaultValue)`
- L73 _public function_ `THTNWorldStateOperation(const FHTNPolicy::FWSKey InKeyLeftHand, const FOperationEnum InOperation) : THTNWorldStateOperation(InKeyLeftHand, FHTNPolicy::FWSOperationID(InOperation))`
- L79 _public function_ `template<typename TAlternativeKey> THTNWorldStateOperation(const TAlternativeKey InKeyLeftHand, const FOperationEnum InOperation = FOperationEnum::MAX) : THTNWorldStateOperation(FHTNPolicy::FWSKey(InKeyLeftHand), InOperation)`
- L84 _public function_ `THTNWorldStateOperation<TOperationEnum>& SetRHSAsWSKey(const FHTNPolicy::FWSKey InKeyRightHand)`
- L91 _public function_ `template<typename TAlternativeKey> THTNWorldStateOperation<TOperationEnum>& SetRHSAsWSKey(const TAlternativeKey InKeyRightHand)`
- L96 _public function_ `THTNWorldStateOperation<TOperationEnum>& SetRHSAsValue(const FHTNPolicy::FWSValue InValue)`
- L102 _public function_ `inline bool IsRHSAbsolute() const`
- L104 _public function_ `bool IsValid() const`

#### struct `FHTNExecutableAction`  
`struct FHTNExecutableAction`  
_L121-137_
- L124 _public member_ `FHTNPolicy::FActionID ActionID;` — operation ID (Move, Attack, Use, ...)
- L126 _public member_ `FHTNPolicy::FActionParameter Parameter;` — operand ID (Enemy, Table, CoverLocation, ...)
- L128 _public function_ `FHTNExecutableAction() : ActionID(FHTNPolicy::InvalidActionID) , Parameter(0)`
- L133 _public function_ `bool operator==(const FHTNExecutableAction& Other) const`

#### struct `FHTNPrimitiveTask`  
`struct FHTNPrimitiveTask : public FHTNExecutableAction`  
_L139-149_
- inherits: `FHTNExecutableAction`
- L142 _public member_ `FHTNEffect* Effects;` — effect (applied to world state when this task is used)
- L143 _public member_ `uint8 EffectsCount;`
- L145 _public function_ `FHTNPrimitiveTask() : Effects(nullptr) , EffectsCount(0)`

#### struct `FHTNMethod`  
`struct FHTNMethod`  
_L151-164_
- L153 _public member_ `FHTNPolicy::FTaskID* Tasks;`
- L154 _public member_ `FHTNCondition* Conditions;`
- L155 _public member_ `uint8 TasksCount;`
- L156 _public member_ `uint8 ConditionsCount;`
- L158 _public function_ `FHTNMethod() : Tasks(nullptr) , Conditions(nullptr) , TasksCount(0) , ConditionsCount(0)`

#### struct `FHTNCompositeTask`  
`struct FHTNCompositeTask`  
_L166-177_
- L168 _public member_ `FHTNMethod* Methods;`
- L169 _public member_ `uint8 MethodsCount;`
- L171 _public function_ `FHTNCompositeTask() : Methods(nullptr) , MethodsCount(0)`
- L176 _public prototype_ `int32 FindSatisfiedMethod(const FHTNWorldState& WorldState, const int32 StartIndex = 0) const;`

#### struct `FHTNDomain`  
`struct FHTNDomain : public TSharedFromThis<FHTNDomain>`  
_L179-229_
- inherits: `TSharedFromThis<FHTNDomain>`
- L181 _public prototype_ `FHTNDomain();`
- L182 _public prototype_ `~FHTNDomain();`
- L186 _public prototype_ `FHTNPolicy::FTaskID FindTaskID(const FName& TaskName) const;`
- L187 _public function_ `inline bool IsPrimitiveTask(const FHTNPolicy::FTaskID TaskID) const`
- L191 _public function_ `inline bool IsCompositeTask(const FHTNPolicy::FTaskID TaskID) const`
- L196 _public function_ `const FHTNPrimitiveTask& GetPrimitiveTask(const FHTNPolicy::FTaskID TaskID) const`
- L201 _public function_ `const FHTNCompositeTask& GetCompositeTask(const FHTNPolicy::FTaskID TaskID) const`
- L207 _public prototype_ `FName GetTaskName(const FHTNPolicy::FTaskID TaskID) const;` — @note this information is available only if WITH_HTN_DEBUG
- L209 _public function_ `FHTNPolicy::FTaskID GetRootTaskID() const`
- L210 _public function_ `bool IsEmpty() const`
- L214 _protected prototype_ `void ReleaseRawData();`
- L216 _protected member_ `uint8* RawData = nullptr;`
- L217 _protected member_ `TMap<FName, FHTNPolicy::FTaskID> TaskNameMap;`
- L218 _protected member_ `FHTNPolicy::FTaskID FirstCompositeTaskID;`
- L222 _protected member_ `FHTNPolicy::FTaskID RootTaskID;` — Root task is the default task we start planning from
- L224 _protected member_ `TMap<FHTNPolicy::FTaskID, FName> TaskIDToName;`
- L227 _protected prototype_ `void Reset();`

#### struct `FHTNWorldState`  
`struct FHTNWorldState`  
_L231-276_
- L233 _public prototype_ `FHTNWorldState(const uint32 WorldStateSize = 128);`
- L234 _public prototype_ `~FHTNWorldState();`
- L236 _public prototype_ `void Reinit(const uint32 NewWorldStateSize = 128);`
- L238 _public prototype_ `bool CheckCondition(const FHTNCondition& Condition) const;`
- L239 _public function_ `inline bool CheckConditions(const FHTNCondition* Conditions, const int32 ConditionsCount) const`
- L251 _public prototype_ `void ApplyEffect(const FHTNEffect& Effect);`
- L252 _public function_ `inline void ApplyEffects(const FHTNEffect* Effects, const int32 EffectsCount)`
- L260 _public prototype_ `bool GetValue(const FHTNPolicy::FWSKey Key, FHTNPolicy::FWSValue& OutValue) const;`
- L261 _public function_ `FHTNPolicy::FWSValue GetValueUnsafe(const FHTNPolicy::FWSKey Key) const`
- L266 _public prototype_ `bool SetValue(const FHTNPolicy::FWSKey Key, const FHTNPolicy::FWSValue InValue);`
- L267 _public function_ `void SetValueUnsafe(const FHTNPolicy::FWSKey Key, const FHTNPolicy::FWSValue InValue)`
- L272 _public function_ `void Shrink()`
- L275 _protected member_ `TArray<FHTNPolicy::FWSValue> Values;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define WITH_HTN_DEBUG !(UE_BUILD_SHIPPING || UE_BUILD_TEST)`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHTNPlanner, Warning, All);`
- L17 _namespace_ `namespace FHTNPolicy`
- L19 _typedef_ `typedef uint16 FWSKey;` (scope `FHTNPolicy`)
- L20 _typedef_ `typedef int32 FWSValue;` (scope `FHTNPolicy`)
- L21 _typedef_ `typedef uint16 FTaskID;` (scope `FHTNPolicy`)
- L22 _typedef_ `typedef uint16 FMethodID;` (scope `FHTNPolicy`)
- L23 _typedef_ `typedef uint16 FActionID;` (scope `FHTNPolicy`)
- L24 _typedef_ `typedef int32 FActionParameter;` (scope `FHTNPolicy`)
- L25 _typedef_ `typedef uint8 FWSOperationID;` (scope `FHTNPolicy`)
- L26 _variable_ `const FWSValue DefaultValue = FWSValue(0);` (scope `FHTNPolicy`)
- L27 _variable_ `const FWSKey InvalidWSKey = MAX_uint16;` (scope `FHTNPolicy`)
- L28 _variable_ `const FTaskID InvalidTaskID = FTaskID(INDEX_NONE);` (scope `FHTNPolicy`)
- L29 _variable_ `const FMethodID InvalidMethodID = FMethodID(INDEX_NONE);` (scope `FHTNPolicy`)
- L30 _variable_ `const FActionID InvalidActionID = FActionID(MAX_uint16);` (scope `FHTNPolicy`)
- L31 _variable_ `const FWSOperationID InvalidWSOperation = FWSOperationID(MAX_uint8);` (scope `FHTNPolicy`)
- L107 _typedef_ `typedef THTNWorldStateOperation<EHTNWorldStateCheck> FHTNCondition;`
- L108 _typedef_ `typedef THTNWorldStateOperation<EHTNWorldStateOperation> FHTNEffect;`
- L110 _namespace_ `namespace FHTNWorldStateOperations`
- L112 _typedef_ `typedef bool(*FConditionFunctionPtr)(const FHTNPolicy::FWSValue*, const FHTNCondition& Condition);` (scope `FHTNWorldStateOperations`)
- L113 _typedef_ `typedef void(*FOperationFunctionPtr)(FHTNPolicy::FWSValue*, const FHTNEffect& Effect);` (scope `FHTNWorldStateOperations`)
- L116 _prototype_ `FHTNPolicy::FWSOperationID RegisterCustomCheckType(const FConditionFunctionPtr CustomConditionFunctionPtr, const FName& DebugName);` (scope `FHTNWorldStateOperations`) — @return check ID, use it while building your conditions with the HTN builders
- L118 _prototype_ `FHTNPolicy::FWSOperationID RegisterCustomOperationType(const FOperationFunctionPtr CustomOperationFunctionPtr, const FName& DebugName);` (scope `FHTNWorldStateOperations`) — @return check ID, use it while building your world state effects with the HTN builders

### `Plugins/AI/HTNPlanner/Source/HTNPlanner/Public/HTNPlanner.h` (Public)


#### struct `FHTNResult`  
`struct FHTNResult`  
_L8-19_
- L10 _public member_ `TArray<FHTNPolicy::FTaskID> TaskIDs;`
- L11 _public member_ `TArray<FHTNExecutableAction> ActionsSequence;`
- L13 _public function_ `void Reset()`
- L18 _public prototype_ `void Set(const FHTNDomain& Domain, const TArray<FHTNPolicy::FTaskID>& TasksSequence);`

#### struct `FHTNRestorePoint`  
`struct FHTNRestorePoint`  
_L21-42_
- L28 _public member_ `FHTNWorldState WorldState;`
- L29 _public member_ `TArray<FHTNPolicy::FTaskID> Plan;`
- L30 _public member_ `int32 NextMethod;`
- L31 _public member_ `FHTNPolicy::FTaskID ActiveTask;`
- L33 _public function_ `explicit FHTNRestorePoint(const FHTNWorldState& InWorldState = FHTNWorldState()) : WorldState(InWorldState), NextMethod(0), ActiveTask(FHTNPolicy::InvalidTaskID)`
- L39 _public function_ `FHTNRestorePoint(const FHTNRestorePoint& PreviousPoint, const FHTNPolicy::FTaskID CurrentTask, const int32 InNextMethod) : WorldState(PreviousPoint.WorldState), Plan(PreviousPoint.Plan), NextMethod(InNextMethod), ActiveTask(CurrentTask)`

#### enum `FHTNRestorePoint::(anonymous)`  
``  
_L24-26_

#### struct `FHTNPlanner`  
`struct FHTNPlanner`  
_L44-81_
- L51 _public prototype_ `FHTNPlanner();`
- L52 _public prototype_ `bool GeneratePlan(const FHTNDomain& Domain, const FHTNWorldState& InitialWorldState, FHTNResult& Result, const FName& StartTaskName = NAME_None);`
- L53 _public function_ `const FHTNWorldState& GetWorldState() const`
- L56 _protected function_ `FHTNWorldState& CurrentWorldState()`
- L57 _protected function_ `void RecordDecomposition(const FHTNPolicy::FTaskID CurrentTask, const int32 MethodIndex)`
- L58 _protected function_ `void RestoreDecomposition()`
- L59 _protected function_ `bool CanRollBack() const`
- L60 _protected function_ `int32 GetMethodIndex() const`
- L61 _protected function_ `FHTNPolicy::FTaskID GetActiveTask() const`
- L62 _protected function_ `const TArray<FHTNPolicy::FTaskID> GetPlan() const`
- L63 _protected function_ `void AddToPlan(const FHTNPolicy::FTaskID CurrentTask)`
- L65 _protected function_ `void Reset()`
- L72 _protected member_ `FHTNRestorePoint CurrentState;`
- L77 _protected member_ `TArray<FHTNRestorePoint> RestorePoints;` — The array where consecutive restore points are stored. Note that the elements of this array are never getting destroyed (no destructor call) as long as the FHTNPlanner instance is alive.
- L79 _protected member_ `int32 RestorePointsStored;` — Used for bookkeeping RestorePoints contents
- L80 _protected member_ `TArray<FHTNPolicy::FTaskID> TasksToProcess;`

#### enum `FHTNPlanner::(anonymous)`  
``  
_L47-49_

#### Free symbols / members of external scopes

- L25 _enumerator_ `InitialPlanSize = 5` (scope `FHTNRestorePoint::__anon1634b9d00103`) — used to preallocate Plan array
- L48 _enumerator_ `InitialResporePoints = 5` (scope `FHTNPlanner::__anon1634b9d00203`) — used to preallocate RestorePoints array

### `Plugins/AI/HTNPlanner/Source/HTNPlanner/Public/HTNPlannerModule.h` (Public)


#### class `IHTNPlannerModule`  
`class IHTNPlannerModule : public IModuleInterface`  
_L11-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L22 _public function_ `static inline IHTNPlannerModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
