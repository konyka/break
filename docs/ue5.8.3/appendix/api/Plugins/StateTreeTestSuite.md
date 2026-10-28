# Plugins / StateTreeTestSuite

- module root: `Plugins/Runtime/StateTree/Source/StateTreeTestSuite`
- headers: 4; symbols: 427
- symbol kinds: class=7, enum=4, enumerator=12, function=130, macro=1, member=139, namespace=7, prototype=39, struct=64, typedef=24
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AIModule, AITestSuite, Core, CoreUObject, Engine, GameplayTags, PropertyBindingUtils, PropertyBindingUtilsEditor, StateTreeEditorModule, StateTreeModule

### `Plugins/Runtime/StateTree/Source/StateTreeTestSuite/Private/StateTreeTest.h` (Private)


#### class `UStateTreeTestSchema`  
`class UStateTreeTestSchema : public UStateTreeSchema`  
_L10-39_
- reflection: `UCLASS(HideDropdown)`
- inherits: `UStateTreeSchema`
- L15 _public function_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const override`
- L19 _public function_ `virtual bool IsExternalItemAllowed(const UStruct& InStruct) const override`
- L23 _public function_ `virtual bool IsScheduledTickAllowed() const`
- L27 _public function_ `virtual EStateTreeStateSelectionRules GetStateSelectionRules() const`
- L31 _public function_ `void SetStateSelectionRules(EStateTreeStateSelectionRules Rules)`
- L38 _private member_ `EStateTreeStateSelectionRules DefaultRules = EStateTreeStateSelectionRules::Default;` — `UPROPERTY()`

#### class `UStateTreeTestSchema2`  
`class UStateTreeTestSchema2 : public UStateTreeSchema`  
_L42-45_
- reflection: `UCLASS(HideDropdown)`
- inherits: `UStateTreeSchema`

#### Free symbols / members of external scopes

- L47 _macro_ `#define IMPLEMENT_STATE_TREE_INSTANT_TEST(TestClass, PrettyName) \`

### `Plugins/Runtime/StateTree/Source/StateTreeTestSuite/Private/StateTreeTestTypes.h` (Private)


#### struct `FStateTreeTestLog`  
`struct FStateTreeTestLog`  
_L24-41_
- reflection: `USTRUCT()`
- desc: Test log that can be passed as external data.
- L35 _public member_ `TArray<FLogItem> Items;`
- L37 _public function_ `void Log(const FName& Name, const FString& Message)`

#### struct `FStateTreeTestLog::FLogItem`  
`struct FLogItem`  
_L28-34_
- L30 _public prototype_ `FLogItem() = default;`
- L31 _public function_ `FLogItem(const FName& InName, const FString& InMessage) : Name(InName), Message(InMessage)`
- L32 _public member_ `FName Name;`
- L33 _public member_ `FString Message;`

#### struct `FTestStateTreeExecutionContext`  
`struct FTestStateTreeExecutionContext : public FStateTreeExecutionContext`  
_L43-159_
- inherits: `FStateTreeExecutionContext`
- L45 _public function_ `FTestStateTreeExecutionContext(UObject& InOwner, const UStateTree& InStateTree, FStateTreeInstanceData& InInstanceData, const FOnCollectStateTreeExternalData& CollectExternalDataCallback = {}, const EStateTreeRecordTransitions RecordTransitions = EStateTreeRecordTransitions::No) : FTestStateTreeExecutionContext(&InOwner, &InStateTree, InInstanceData, CollectExternalDataCallback, RecordTransitions)`
- L50 _public function_ `FTestStateTreeExecutionContext(TNotNull<UObject*> InOwner, TNotNull<const UStateTree*> InStateTree, FStateTreeInstanceData& InInstanceData, const FOnCollectStateTreeExternalData& CollectExternalDataCallback = {}, const EStateTreeRecordTransitions RecordTransitions = EStateTreeRecordTransitions::No) : FStateTreeExecutionContext(InOwner, InStateTree, InInstanceData, CollectExternalDataCallback, RecordTransitions)`
- L72 _public member_ `FStateTreeTestLog Log;`
- L74 _public function_ `void LogClear()`
- L125 _public function_ `FLogOrder Expect(const FName& Name) const`
- L130 _public function_ `FLogOrder Expect(const FName& Name, const FStringView Message) const`
- L136 _public function_ `template <class ...Args> bool ExpectInActiveStates(const Args&... States)`

#### struct `FTestStateTreeExecutionContext::FLogOrder`  
`struct FLogOrder`  
_L79-123_
- L81 _public function_ `FLogOrder(const FTestStateTreeExecutionContext& InContext, const int32 InIndex) : Context(&InContext), Index(InIndex)`
- L85 _public function_ `FLogOrder Then(const FName& Name) const`
- L100 _public function_ `FLogOrder Then(const FName& Name, const FStringView Message) const`
- L115 _public function_ `operator bool() const`
- L121 _private member_ `const FTestStateTreeExecutionContext* Context;`
- L122 _private member_ `int32 Index = 0;`

#### enum `UE::StateTree::Test::ECppClassEnumByte`  
`enum class ECppClassEnumByte : uint8`  
_L164-169_
- reflection: `UENUM()`
- L166 _public enumerator_ `A = 0`
- L167 _public enumerator_ `B = 0x11`
- L168 _public enumerator_ `C = 0x22`

#### enum `UE::StateTree::Test::ECppClassEnumInt`  
`enum class ECppClassEnumInt : uint32`  
_L172-177_
- reflection: `UENUM()`
- L174 _public enumerator_ `A = 0`
- L175 _public enumerator_ `B = 0xF333F333`
- L176 _public enumerator_ `C = 0xF444F444`

#### enum `UE::StateTree::Test::ENamespaceEnumByte::Type`  
`enum Type : uint8`  
_L182-187_
- L184 _public enumerator_ `A = 0`
- L185 _public enumerator_ `B = 0x55`
- L186 _public enumerator_ `C = 0x66`

#### enum `UE::StateTree::Test::EEnumByte`  
`enum EEnumByte : uint8`  
_L191-196_
- reflection: `UENUM()`
- L193 _public enumerator_ `EEnumByte_A = 0`
- L194 _public enumerator_ `EEnumByte_B = 0x77`
- L195 _public enumerator_ `EEnumByte_C = 0x88`

#### struct `UE::StateTree::Test::FStructWithEnum`  
`struct FStructWithEnum`  
_L199-211_
- reflection: `USTRUCT()`
- L204 _public member_ `ECppClassEnumByte CppClassEnumByte = ECppClassEnumByte::A;` — `UPROPERTY()`
- L206 _public member_ `ECppClassEnumInt CppClassEnumInt = ECppClassEnumInt::A;` — `UPROPERTY()`
- L208 _public member_ `TEnumAsByte<ENamespaceEnumByte::Type> NamespaceEnumByte = ENamespaceEnumByte::A;` — `UPROPERTY()`
- L210 _public member_ `TEnumAsByte<EEnumByte> EnumByte = EEnumByte_A;` — `UPROPERTY()`

#### struct `UE::StateTree::Test::FStructWithEnumRef`  
`struct FStructWithEnumRef`  
_L214-226_
- reflection: `USTRUCT()`
- L219 _public member_ `TStateTreePropertyRef<ECppClassEnumByte> CppClassEnumByte;` — `UPROPERTY()`
- L221 _public member_ `TStateTreePropertyRef<ECppClassEnumInt> CppClassEnumInt;` — `UPROPERTY()`
- L223 _public member_ `TStateTreePropertyRef<TEnumAsByte<ENamespaceEnumByte::Type>> NamespaceEnumByte;` — `UPROPERTY()`
- L225 _public member_ `TStateTreePropertyRef<TEnumAsByte<EEnumByte>> EnumByte;` — `UPROPERTY()`

#### struct `FTestEval_AInstanceData`  
`struct FTestEval_AInstanceData`  
_L230-242_
- reflection: `USTRUCT()`
- L235 _public member_ `float FloatA = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L238 _public member_ `int32 IntA = 0;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L241 _public member_ `bool bBoolA = false;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FTestEval_A`  
`struct FTestEval_A : public FStateTreeEvaluatorBase`  
_L245-256_
- reflection: `USTRUCT()`
- inherits: `FStateTreeEvaluatorBase`
- L249 _public typedef_ `using FInstanceDataType = FTestEval_AInstanceData;`
- L251 _public prototype_ `FTestEval_A() = default;`
- L252 _public function_ `FTestEval_A(const FName InName)`
- L253 _public prototype_ `virtual ~FTestEval_A() override = default;`
- L255 _public function_ `virtual const UStruct* GetInstanceDataType() const override`

#### struct `FTestEval_Custom`  
`struct FTestEval_Custom : public FStateTreeEvaluatorBase`  
_L259-308_
- reflection: `USTRUCT()`
- inherits: `FStateTreeEvaluatorBase`
- L263 _public typedef_ `using FInstanceDataType = FTestEval_AInstanceData;`
- L265 _public prototype_ `FTestEval_Custom() = default;`
- L266 _public function_ `FTestEval_Custom(const FName InName)`
- L268 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L273 _public function_ `virtual void TreeStart(FStateTreeExecutionContext& Context) const override`
- L281 _public function_ `virtual void TreeStop(FStateTreeExecutionContext& Context) const override`
- L289 _public function_ `virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override`
- L297 _public function_ `virtual bool Link(FStateTreeLinker& Linker) override`
- L303 _public member_ `TStateTreeExternalDataHandle<FStateTreeTestLog> LogHandle;`
- L305 _public member_ `TFunction<void(FStateTreeExecutionContext&, const FTestEval_Custom*)> CustomEnterStateFunc;`
- L306 _public member_ `TFunction<void(FStateTreeExecutionContext&, const FTestEval_Custom*)> CustomExitStateFunc;`
- L307 _public member_ `TFunction<void(FStateTreeExecutionContext&, const FTestEval_Custom*)> CustomTickFunc;`

#### struct `FTestTask_BInstanceData`  
`struct FTestTask_BInstanceData`  
_L311-323_
- reflection: `USTRUCT()`
- L316 _public member_ `float FloatB = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L319 _public member_ `int32 IntB = 0;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L322 _public member_ `bool bBoolB = false;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FTestTask_B`  
`struct FTestTask_B : public FStateTreeTaskBase`  
_L326-352_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L330 _public typedef_ `using FInstanceDataType = FTestTask_BInstanceData;`
- L332 _public prototype_ `FTestTask_B() = default;`
- L333 _public function_ `FTestTask_B(const FName InName)`
- L334 _public prototype_ `virtual ~FTestTask_B() override = default;`
- L336 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L338 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L345 _public function_ `virtual bool Link(FStateTreeLinker& Linker) override`
- L351 _public member_ `TStateTreeExternalDataHandle<FStateTreeTestLog> LogHandle;`

#### struct `FTestTask_PrintValueInstanceData`  
`struct FTestTask_PrintValueInstanceData`  
_L355-395_
- reflection: `USTRUCT()`
- L360 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L363 _public member_ `int32 OutputValue = 0;` — `UPROPERTY(EditAnywhere, Category = "Output")`
- L366 _public member_ `TArray<int32> ArrayValue;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L369 _public member_ `EStateTreeRunStatus EnterStateRunStatus = EStateTreeRunStatus::Running;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L372 _public member_ `EStateTreeRunStatus TickRunStatus = EStateTreeRunStatus::Running;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L374 _public function_ `FString GetArrayDescription() const`

#### struct `FTestTask_PrintValueExecutionRuntimeData`  
`struct FTestTask_PrintValueExecutionRuntimeData`  
_L398-404_
- reflection: `USTRUCT()`
- L403 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FTestTask_PrintValue`  
`struct FTestTask_PrintValue : public FStateTreeTaskBase`  
_L407-482_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L411 _public typedef_ `using FInstanceDataType = FTestTask_PrintValueInstanceData;`
- L412 _public typedef_ `using FExecutionRuntimeDataType = FTestTask_PrintValueExecutionRuntimeData;`
- L414 _public prototype_ `FTestTask_PrintValue() = default;`
- L415 _public function_ `FTestTask_PrintValue(const FName InName)`
- L416 _public prototype_ `virtual ~FTestTask_PrintValue() override = default;`
- L418 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L419 _public function_ `virtual const UStruct* GetExecutionRuntimeDataType() const override`
- L421 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L438 _public function_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L451 _public function_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override`
- L464 _public function_ `virtual void TriggerTransitions(FStateTreeExecutionContext& Context) const override`
- L472 _public function_ `virtual bool Link(FStateTreeLinker& Linker) override`
- L478 _public member_ `TStateTreeExternalDataHandle<FStateTreeTestLog> LogHandle;`
- L479 _public member_ `TFunction<void(FStateTreeExecutionContext&, const FTestTask_PrintValue*)> CustomEnterStateFunc;`
- L480 _public member_ `TFunction<void(FStateTreeExecutionContext&, const FTestTask_PrintValue*)> CustomExitStateFunc;`
- L481 _public member_ `TFunction<void(FStateTreeExecutionContext&, const FTestTask_PrintValue*)> CustomTickFunc;`

#### struct `FTestCondition_PrintValue`  
`struct FTestCondition_PrintValue : public FStateTreeConditionCommonBase`  
_L485-525_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeConditionCommonBase`
- L489 _public typedef_ `using FInstanceDataType = FTestTask_PrintValueInstanceData;`
- L490 _public typedef_ `using FExecutionRuntimeDataType = FTestTask_PrintValueExecutionRuntimeData;`
- L492 _public prototype_ `FTestCondition_PrintValue() = default;`
- L493 _public function_ `FTestCondition_PrintValue(const FName InName)`
- L497 _public function_ `virtual ~FTestCondition_PrintValue() override`
- L499 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L500 _public function_ `virtual const UStruct* GetExecutionRuntimeDataType() const override`
- L502 _public function_ `virtual bool Link(FStateTreeLinker& Linker) override`
- L508 _public function_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override`
- L523 _public member_ `TFunction<bool(FStateTreeExecutionContext&, const FTestCondition_PrintValue*)> CustomTestConditionFunc;`
- L524 _public member_ `TStateTreeExternalDataHandle<FStateTreeTestLog> LogHandle;`

#### struct `FTestTask_PrintAndResetValue`  
`struct FTestTask_PrintAndResetValue : public FTestTask_PrintValue`  
_L528-565_
- reflection: `USTRUCT()`
- inherits: `FTestTask_PrintValue`
- L534 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L543 _public function_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override`
- L552 _public function_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L561 _public member_ `int32 ResetValue = 0;` — `UPROPERTY()`
- L564 _public member_ `TArray<int32> ResetArrayValue;` — `UPROPERTY()`

#### struct `FTestTask_PrintValue_TransitionTick`  
`struct FTestTask_PrintValue_TransitionTick : public FTestTask_PrintValue`  
_L568-583_
- reflection: `USTRUCT()`
- inherits: `FTestTask_PrintValue`
- L572 _public function_ `FTestTask_PrintValue_TransitionTick()`
- L577 _public function_ `FTestTask_PrintValue_TransitionTick(const FName InName) : FTestTask_PrintValue(InName)`

#### struct `FTestTask_PrintValue_TransitionNoTick`  
`struct FTestTask_PrintValue_TransitionNoTick : public FTestTask_PrintValue`  
_L586-601_
- reflection: `USTRUCT()`
- inherits: `FTestTask_PrintValue`
- L590 _public function_ `FTestTask_PrintValue_TransitionNoTick()`
- L595 _public function_ `FTestTask_PrintValue_TransitionNoTick(const FName InName) : FTestTask_PrintValue(InName)`

#### struct `FTestTask_StopTreeInstanceData`  
`struct FTestTask_StopTreeInstanceData`  
_L604-607_
- reflection: `USTRUCT()`

#### struct `FTestTask_StopTree`  
`struct FTestTask_StopTree : public FStateTreeTaskBase`  
_L610-659_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L614 _public typedef_ `using FInstanceDataType = FTestTask_PrintValueInstanceData;`
- L616 _public prototype_ `FTestTask_StopTree() = default;`
- L617 _public function_ `explicit FTestTask_StopTree(const FName InName)`
- L618 _public prototype_ `virtual ~FTestTask_StopTree() override = default;`
- L620 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L622 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L631 _public function_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L639 _public function_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override`
- L648 _public function_ `virtual bool Link(FStateTreeLinker& Linker) override`
- L654 _public member_ `TStateTreeExternalDataHandle<FStateTreeTestLog> LogHandle;`
- L658 _public member_ `EStateTreeUpdatePhase Phase = EStateTreeUpdatePhase::Unset;` — `UPROPERTY()` — Indicates in which phase the call to Stop should be performed. Possible values are EnterStates, ExitStats and TickStateTree

#### struct `FTestTask_StandInstanceData`  
`struct FTestTask_StandInstanceData`  
_L662-671_
- reflection: `USTRUCT()`
- L667 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L670 _public member_ `int32 CurrentTick = 0;` — `UPROPERTY()`

#### struct `FTestTask_Stand`  
`struct FTestTask_Stand : public FStateTreeTaskBase`  
_L674-757_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L678 _public typedef_ `using FInstanceDataType = FTestTask_StandInstanceData;`
- L680 _public prototype_ `FTestTask_Stand() = default;`
- L681 _public function_ `FTestTask_Stand(const FName InName)`
- L682 _public prototype_ `virtual ~FTestTask_Stand() = default;`
- L684 _public function_ `virtual const UStruct* GetInstanceDataType() const`
- L686 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L701 _public function_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L722 _public function_ `virtual void StateCompleted(FStateTreeExecutionContext& Context, const EStateTreeRunStatus CompletionStatus, const FStateTreeActiveStates& CompletedActiveStates) const override`
- L728 _public function_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override`
- L741 _public function_ `virtual bool Link(FStateTreeLinker& Linker) override`
- L747 _public member_ `TStateTreeExternalDataHandle<FStateTreeTestLog> LogHandle;`
- L750 _public member_ `int32 TicksToCompletion = 1;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L753 _public member_ `EStateTreeRunStatus TickCompletionResult = EStateTreeRunStatus::Succeeded;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L756 _public member_ `EStateTreeRunStatus EnterStateResult = EStateTreeRunStatus::Running;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FTestTask_StandNoTick`  
`struct FTestTask_StandNoTick : public FTestTask_Stand`  
_L760-774_
- reflection: `USTRUCT()`
- inherits: `FTestTask_Stand`
- L764 _public function_ `FTestTask_StandNoTick()`
- L769 _public function_ `FTestTask_StandNoTick(const FName InName) : FTestTask_Stand(InName)`

#### struct `FTestTask_StandNoStateChangeOnReselect`  
`struct FTestTask_StandNoStateChangeOnReselect : public FTestTask_Stand`  
_L777-791_
- reflection: `USTRUCT()`
- inherits: `FTestTask_Stand`
- L781 _public function_ `FTestTask_StandNoStateChangeOnReselect()`
- L786 _public function_ `FTestTask_StandNoStateChangeOnReselect(const FName InName) : FTestTask_Stand(InName)`

#### struct `FTestTask_IntegersOutput_InstanceData`  
`struct FTestTask_IntegersOutput_InstanceData`  
_L794-804_
- reflection: `USTRUCT()`
- L799 _public member_ `int32 IntA = 0;` — `UPROPERTY(EditAnywhere, Category=Output)`
- L802 _public member_ `int32 IntB = 0;` — `UPROPERTY(EditAnywhere, Category=Output)`

#### struct `FTestTask_IntegersOutput`  
`struct FTestTask_IntegersOutput : public FStateTreeTaskBase`  
_L807-833_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L811 _public typedef_ `using FInstanceDataType = FTestTask_IntegersOutput_InstanceData;`
- L813 _public prototype_ `FTestTask_IntegersOutput() = default;`
- L815 _public function_ `explicit FTestTask_IntegersOutput(FName InName)`
- L820 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L822 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L832 _public member_ `TFunction<void(FStateTreeExecutionContext&, const FTestTask_IntegersOutput&)> CustomEnterStateFunc;`

#### struct `FTestTask_PropertyRefOnNodeAndInstance_InstanceData`  
`struct FTestTask_PropertyRefOnNodeAndInstance_InstanceData`  
_L836-842_
- reflection: `USTRUCT()`
- L841 _public member_ `FStateTreePropertyRef RefOnInstance;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (RefType = "int32", Optional))`

#### struct `FTestTask_PropertyRefOnNodeAndInstance`  
`struct FTestTask_PropertyRefOnNodeAndInstance : public FStateTreeTaskBase`  
_L845-873_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L849 _public typedef_ `using FInstanceDataType = FTestTask_PropertyRefOnNodeAndInstance_InstanceData;`
- L851 _public prototype_ `FTestTask_PropertyRefOnNodeAndInstance() = default;`
- L852 _public function_ `FTestTask_PropertyRefOnNodeAndInstance(FName InName)`
- L857 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L859 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L870 _public member_ `FStateTreePropertyRef RefOnNode;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (RefType = "int32", Optional))`
- L872 _public member_ `TFunction<void(FStateTreeExecutionContext&, const FTestTask_PropertyRefOnNodeAndInstance&)> CustomEnterStateFunc;`

#### struct `FTestCondition_PropertyRefOnNodeAndInstance`  
`struct FTestCondition_PropertyRefOnNodeAndInstance : public FStateTreeConditionBase`  
_L876-904_
- reflection: `USTRUCT()`
- inherits: `FStateTreeConditionBase`
- L880 _public typedef_ `using FInstanceDataType = FTestTask_PropertyRefOnNodeAndInstance_InstanceData;`
- L882 _public prototype_ `FTestCondition_PropertyRefOnNodeAndInstance() = default;`
- L883 _public function_ `FTestCondition_PropertyRefOnNodeAndInstance(FName InName)`
- L888 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L890 _public function_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override`
- L901 _public member_ `FStateTreePropertyRef RefOnNode;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (RefType = "int32", Optional))`
- L903 _public member_ `TFunction<void(FStateTreeExecutionContext&, const FTestCondition_PropertyRefOnNodeAndInstance&)> CustomTestConditionFunc;`

#### struct `FStateTreeTestConditionInstanceData`  
`struct FStateTreeTestConditionInstanceData`  
_L907-915_
- reflection: `USTRUCT()`
- L912 _public member_ `int32 Count = 1;` — `UPROPERTY(EditAnywhere, Category = Parameters)`
- L914 _public member_ `static std::atomic<int32> GlobalCounter;`

#### struct `FStateTreeTestCondition`  
`struct FStateTreeTestCondition : public FStateTreeConditionCommonBase`  
_L918-943_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeConditionCommonBase`
- L922 _public typedef_ `using FInstanceDataType = FStateTreeTestConditionInstanceData;`
- L924 _public prototype_ `FStateTreeTestCondition() = default;`
- L926 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L927 _public function_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override`
- L942 _public member_ `bool bTestConditionResult = true;` — `UPROPERTY()`

#### struct `FStateTreeTestRunContext`  
`struct FStateTreeTestRunContext`  
_L945-948_
- L947 _public member_ `int32 Count = 0;`

#### struct `FStateTreeTest_PropertyStructA`  
`struct FStateTreeTest_PropertyStructA`  
_L952-958_
- reflection: `USTRUCT()`
- L957 _public member_ `int32 A = 0;` — `UPROPERTY(EditAnywhere, Category = "")`

#### struct `FStateTreeTest_PropertyStructB`  
`struct FStateTreeTest_PropertyStructB`  
_L961-978_
- reflection: `USTRUCT()`
- L965 _public function_ `FStateTreeTest_PropertyStructB()`
- L969 _public function_ `~FStateTreeTest_PropertyStructB()`
- L975 _public member_ `int32 B = 0;` — `UPROPERTY(EditAnywhere, Category = "")`
- L977 _public member_ `static inline int32 NumConstructed = 0;`

#### struct `FStateTreeTest_PropertyStructObjectPtr`  
`struct FStateTreeTest_PropertyStructObjectPtr`  
_L981-1002_
- reflection: `USTRUCT()`
- L986 _public member_ `TObjectPtr<UObject> A;` — `UPROPERTY(EditAnywhere, Category = "")`
- L989 _public member_ `TWeakObjectPtr<UObject> B;` — `UPROPERTY(EditAnywhere, Category = "")`
- L992 _public member_ `TSoftObjectPtr<UObject> C;` — `UPROPERTY(EditAnywhere, Category = "")`
- L995 _public member_ `TArray<TObjectPtr<UObject>> ArrayA;` — `UPROPERTY(EditAnywhere, Category = "")`
- L998 _public member_ `TArray<TWeakObjectPtr<UObject>> ArrayB;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1001 _public member_ `TArray<TSoftObjectPtr<UObject>> ArrayC;` — `UPROPERTY(EditAnywhere, Category = "")`

#### struct `FStateTreeTest_PropertyStruct`  
`struct FStateTreeTest_PropertyStruct`  
_L1005-1017_
- reflection: `USTRUCT()`
- L1010 _public member_ `int32 A = 0;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1013 _public member_ `int32 B = 0;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1016 _public member_ `FStateTreeTest_PropertyStructB StructB;` — `UPROPERTY(EditAnywhere, Category = "")`

#### class `UStateTreeTest_PropertyObjectInstanced`  
`class UStateTreeTest_PropertyObjectInstanced : public UObject`  
_L1020-1033_
- reflection: `UCLASS(HideDropdown)`
- inherits: `UObject`
- L1026 _public member_ `int32 A = 0;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1029 _public member_ `FInstancedStruct InstancedStruct;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1032 _public member_ `TArray<FGameplayTag> ArrayOfTags;` — `UPROPERTY(EditAnywhere, Category = "")`

#### class `UStateTreeTest_PropertyObjectInstancedWithB`  
`class UStateTreeTest_PropertyObjectInstancedWithB : public UStateTreeTest_PropertyObjectInstanced`  
_L1036-1043_
- reflection: `UCLASS(HideDropdown)`
- inherits: `UStateTreeTest_PropertyObjectInstanced`
- L1042 _public member_ `int32 B = 0;` — `UPROPERTY(EditAnywhere, Category = "")`

#### class `UStateTreeTest_PropertyObject`  
`class UStateTreeTest_PropertyObject : public UObject`  
_L1046-1071_
- reflection: `UCLASS(HideDropdown)`
- inherits: `UObject`
- L1052 _public member_ `TObjectPtr<UStateTreeTest_PropertyObjectInstanced> InstancedObject;` — `UPROPERTY(EditAnywhere, Instanced, Category = "")`
- L1055 _public member_ `TArray<TObjectPtr<UStateTreeTest_PropertyObjectInstanced>> ArrayOfInstancedObjects;` — `UPROPERTY(EditAnywhere, Instanced, Category = "")`
- L1058 _public member_ `TArray<int32> ArrayOfInts;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1061 _public member_ `FInstancedStruct InstancedStruct;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1064 _public member_ `TArray<FInstancedStruct> ArrayOfInstancedStructs;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1067 _public member_ `FStateTreeTest_PropertyStruct Struct;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1070 _public member_ `TArray<FStateTreeTest_PropertyStruct> ArrayOfStruct;` — `UPROPERTY(EditAnywhere, Category = "")`

#### class `UStateTreeTest_PropertyObject2`  
`class UStateTreeTest_PropertyObject2 : public UObject`  
_L1074-1078_
- reflection: `UCLASS(HideDropdown)`
- inherits: `UObject`

#### struct `FStateTreeTest_PropertyCopy`  
`struct FStateTreeTest_PropertyCopy`  
_L1081-1103_
- reflection: `USTRUCT()`
- L1086 _public member_ `FStateTreeTest_PropertyStruct Item;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1089 _public member_ `TArray<FStateTreeTest_PropertyStruct> Array;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1092 _public member_ `TArray<FStateTreeTest_PropertyStruct> FixedArray;` — `UPROPERTY(EditAnywhere, Category = "", EditFixedSize)`
- L1095 _public member_ `FStateTreeTest_PropertyStruct CArray[3];` — `UPROPERTY(EditAnywhere, Category = "")`
- L1098 _public member_ `TArray<float> ArrayOfFloat;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1101 _public member_ `TArray<double> ArrayOfDouble;` — `UPROPERTY(EditAnywhere, Category = "")`

#### struct `FStateTreeTest_PropertyRefSourceStruct`  
`struct FStateTreeTest_PropertyRefSourceStruct`  
_L1106-1118_
- reflection: `USTRUCT()`
- L1111 _public member_ `FStateTreeTest_PropertyStruct Item;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1114 _public member_ `FStateTreeTest_PropertyStruct OutputItem;` — `UPROPERTY(EditAnywhere, Category = "Output")`
- L1117 _public member_ `TArray<FStateTreeTest_PropertyStruct> Array;` — `UPROPERTY(EditAnywhere, Category = "")`

#### struct `FStateTreeTest_PropertyRefTargetStruct`  
`struct FStateTreeTest_PropertyRefTargetStruct`  
_L1121-1133_
- reflection: `USTRUCT()`
- L1126 _public member_ `FStateTreePropertyRef RefToStruct;` — `UPROPERTY(EditAnywhere, Category = "", meta = (RefType = "/Script/StateTreeTestSuite.StateTreeTest_PropertyStruct"))`
- L1129 _public member_ `FStateTreePropertyRef RefToInt;` — `UPROPERTY(EditAnywhere, Category = "", meta = (RefType = "Int32"))`
- L1132 _public member_ `FStateTreePropertyRef RefToStructArray;` — `UPROPERTY(EditAnywhere, Category = "", meta = (RefType = "/Script/StateTreeTestSuite.StateTreeTest_PropertyStruct", IsRefToArray))`

#### struct `FStateTreeTest_PropertyCopyObjects`  
`struct FStateTreeTest_PropertyCopyObjects`  
_L1136-1151_
- reflection: `USTRUCT()`
- L1141 _public member_ `TObjectPtr<UObject> Object;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1144 _public member_ `TSubclassOf<UObject> Class;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1147 _public member_ `TSoftObjectPtr<UObject> SoftObject;` — `UPROPERTY(EditAnywhere, Category = "")`
- L1150 _public member_ `TSoftClassPtr<UObject> SoftClass;` — `UPROPERTY(EditAnywhere, Category = "")`

#### struct `FTestPropertyFunction_InstanceData`  
`struct FTestPropertyFunction_InstanceData`  
_L1154-1163_
- reflection: `USTRUCT()`
- L1159 _public member_ `int32 Input = 0;` — `UPROPERTY()`
- L1162 _public member_ `int32 Result = 0;` — `UPROPERTY()`

#### struct `FTestPropertyFunction`  
`struct FTestPropertyFunction : public FStateTreePropertyFunctionBase`  
_L1167-1183_
- reflection: `USTRUCT()`
- inherits: `FStateTreePropertyFunctionBase`
- L1171 _public typedef_ `using FInstanceDataType = FTestPropertyFunction_InstanceData;`
- L1173 _public prototype_ `FTestPropertyFunction() = default;`
- L1174 _public function_ `FTestPropertyFunction(const FName InName)`
- L1176 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L1178 _public function_ `virtual void Execute(FStateTreeExecutionContext& Context) const override`

#### struct `FTestTask_PrintValue_StructRef_NoBindingUpdateInstanceData`  
`struct FTestTask_PrintValue_StructRef_NoBindingUpdateInstanceData : public FTestTask_PrintValueInstanceData`  
_L1186-1195_
- reflection: `USTRUCT()`
- inherits: `FTestTask_PrintValueInstanceData`
- L1191 _public member_ `FStateTreeTest_PropertyStruct PropertyStruct;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L1194 _public member_ `FStateTreeStructRef StructRef;` — `UPROPERTY(EditAnywhere, Category = "Parameter", meta = (BaseStruct = "/Script/StateTreeTestSuite.StateTreeTest_PropertyStruct"))`

#### struct `FTestTask_PrintValue_StructRef_NoBindingUpdate`  
`struct FTestTask_PrintValue_StructRef_NoBindingUpdate : public FTestTask_PrintValue`  
_L1198-1218_
- reflection: `USTRUCT()`
- inherits: `FTestTask_PrintValue`
- L1202 _public typedef_ `using FInstanceDataType = FTestTask_PrintValue_StructRef_NoBindingUpdateInstanceData;`
- L1204 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L1209 _public function_ `FTestTask_PrintValue_StructRef_NoBindingUpdate()`
- L1213 _public function_ `FTestTask_PrintValue_StructRef_NoBindingUpdate(const FName InName) : FTestTask_PrintValue(InName)`

#### struct `FStateTreeTestBooleanConditionInstanceData`  
`struct FStateTreeTestBooleanConditionInstanceData`  
_L1221-1227_
- reflection: `USTRUCT()`
- L1226 _public member_ `bool bSuccess = true;` — `UPROPERTY(EditAnywhere, Category = Parameters)`

#### struct `FStateTreeTestBooleanCondition`  
`struct FStateTreeTestBooleanCondition : public FStateTreeConditionCommonBase`  
_L1231-1255_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeConditionCommonBase`
- L1235 _public typedef_ `using FInstanceDataType = FStateTreeTestBooleanConditionInstanceData;`
- L1237 _public prototype_ `FStateTreeTestBooleanCondition() = default;`
- L1239 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L1240 _public function_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override`
- L1248 _public function_ `virtual bool Link(FStateTreeLinker& Linker) override`
- L1254 _public member_ `TStateTreeExternalDataHandle<FStateTreeTestLog> LogHandle;`

#### struct `FTestTask_BroadcastDelegate_InstanceData`  
`struct FTestTask_BroadcastDelegate_InstanceData`  
_L1258-1270_
- reflection: `USTRUCT()`
- L1263 _public member_ `FStateTreeDelegateDispatcher OnEnterDelegate;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L1266 _public member_ `FStateTreeDelegateDispatcher OnTickDelegate;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L1269 _public member_ `FStateTreeDelegateDispatcher OnExitDelegate;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FTestTask_BroadcastDelegate`  
`struct FTestTask_BroadcastDelegate : public FStateTreeTaskBase`  
_L1273-1312_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L1277 _public prototype_ `FTestTask_BroadcastDelegate() = default;`
- L1278 _public function_ `FTestTask_BroadcastDelegate(const FName InName)`
- L1280 _public typedef_ `using FInstanceDataType = FTestTask_BroadcastDelegate_InstanceData;`
- L1282 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L1287 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L1294 _public function_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override`
- L1301 _public function_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L1308 _public member_ `EStateTreeRunStatus EnterStateResult = EStateTreeRunStatus::Running;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L1311 _public member_ `EStateTreeRunStatus TickCompletionResult = EStateTreeRunStatus::Running;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FTestTask_ListenDelegate_InstanceData`  
`struct FTestTask_ListenDelegate_InstanceData`  
_L1315-1323_
- reflection: `USTRUCT()`
- L1320 _public member_ `FStateTreeDelegateListener Listener;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L1322 _public member_ `uint32 TriggersAmount = 0u;`

#### struct `FTestTask_ListenDelegate`  
`struct FTestTask_ListenDelegate : public FStateTreeTaskBase`  
_L1326-1373_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L1330 _public prototype_ `FTestTask_ListenDelegate() = default;`
- L1331 _public function_ `FTestTask_ListenDelegate(const FName InName)`
- L1333 _public typedef_ `using FInstanceDataType = FTestTask_ListenDelegate_InstanceData;`
- L1335 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L1340 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L1356 _public function_ `virtual bool Link(FStateTreeLinker& Linker) override`
- L1362 _public function_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L1371 _public member_ `bool bRemoveOnExit = true;`
- L1372 _public member_ `TStateTreeExternalDataHandle<FStateTreeTestLog> LogHandle;`

#### struct `FTestTask_RebroadcastDelegate_InstanceData`  
`struct FTestTask_RebroadcastDelegate_InstanceData`  
_L1376-1385_
- reflection: `USTRUCT()`
- L1381 _public member_ `FStateTreeDelegateListener Listener;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L1384 _public member_ `FStateTreeDelegateDispatcher Dispatcher;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FTestTask_RebroadcastDelegate`  
`struct FTestTask_RebroadcastDelegate : public FStateTreeTaskBase`  
_L1388-1419_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L1392 _public prototype_ `FTestTask_RebroadcastDelegate() = default;`
- L1393 _public function_ `FTestTask_RebroadcastDelegate(const FName InName)`
- L1395 _public typedef_ `using FInstanceDataType = FTestTask_RebroadcastDelegate_InstanceData;`
- L1397 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L1402 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L1414 _public function_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`

#### struct `FTestTask_CustomFuncOnDelegate_InstanceData`  
`struct FTestTask_CustomFuncOnDelegate_InstanceData`  
_L1422-1428_
- reflection: `USTRUCT()`
- L1427 _public member_ `FStateTreeDelegateListener Listener;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FTestTask_CustomFuncOnDelegate`  
`struct FTestTask_CustomFuncOnDelegate : public FStateTreeTaskBase`  
_L1431-1468_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L1435 _public prototype_ `FTestTask_CustomFuncOnDelegate() = default;`
- L1436 _public function_ `FTestTask_CustomFuncOnDelegate(const FName InName)`
- L1438 _public typedef_ `using FInstanceDataType = FTestTask_CustomFuncOnDelegate_InstanceData;`
- L1440 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L1445 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L1456 _public function_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L1465 _public member_ `TFunction<void(const FStateTreeWeakExecutionContext&, FStateTreeDelegateListener)> CustomFunc;`
- L1467 _public member_ `bool bRemoveOnExit = true;`

#### struct `FTestTask_DispatcherOnNodeAndInstance_InstanceData`  
`struct FTestTask_DispatcherOnNodeAndInstance_InstanceData`  
_L1471-1477_
- reflection: `USTRUCT()`
- L1476 _public member_ `FStateTreeDelegateDispatcher DispatcherOnInstance;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FTestTask_DispatcherOnNodeAndInstance`  
`struct FTestTask_DispatcherOnNodeAndInstance : public FStateTreeTaskBase`  
_L1480-1507_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L1484 _public typedef_ `using FInstanceDataType = FTestTask_DispatcherOnNodeAndInstance_InstanceData;`
- L1486 _public prototype_ `FTestTask_DispatcherOnNodeAndInstance() = default;`
- L1488 _public function_ `explicit FTestTask_DispatcherOnNodeAndInstance(FName InName)`
- L1493 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L1495 _public function_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override`
- L1506 _public member_ `FStateTreeDelegateDispatcher DispatcherOnNode;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FTestTask_ListenerOnNode_InstanceData`  
`struct FTestTask_ListenerOnNode_InstanceData`  
_L1510-1513_
- reflection: `USTRUCT()`

#### struct `FTestTask_ListenerOnNode`  
`struct FTestTask_ListenerOnNode : public FStateTreeTaskBase`  
_L1516-1546_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L1520 _public typedef_ `using FInstanceDataType = FTestTask_ListenerOnNode_InstanceData;`
- L1522 _public prototype_ `FTestTask_ListenerOnNode() = default;`
- L1524 _public function_ `explicit FTestTask_ListenerOnNode(FName InName)`
- L1529 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L1531 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L1543 _public member_ `FStateTreeDelegateListener ListenerOnNode;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L1545 _public member_ `TFunction<void(const FStateTreeWeakExecutionContext&)> CustomFunc;`

#### struct `FTestTask_ListenerOnInstance_InstanceData`  
`struct FTestTask_ListenerOnInstance_InstanceData`  
_L1549-1555_
- reflection: `USTRUCT()`
- L1554 _public member_ `FStateTreeDelegateListener ListenerOnInstance;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FTestTask_ListenerOnInstance`  
`struct FTestTask_ListenerOnInstance : public FStateTreeTaskBase`  
_L1558-1586_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L1562 _public typedef_ `using FInstanceDataType = FTestTask_ListenerOnInstance_InstanceData;`
- L1564 _public prototype_ `FTestTask_ListenerOnInstance() = default;`
- L1566 _public function_ `explicit FTestTask_ListenerOnInstance(FName InName)`
- L1571 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L1573 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L1585 _public member_ `TFunction<void(const FStateTreeWeakExecutionContext&)> CustomFunc;`

#### struct `FIntWrapper`  
`struct FIntWrapper`  
_L1590-1599_
- reflection: `USTRUCT()`
- desc: @todo: add tests for CArray type
- L1595 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L1598 _public prototype_ `bool operator==(const FIntWrapper& Other) const = default;`

#### struct `FTestTask_OutputBindingsTaskInstanceData`  
`struct FTestTask_OutputBindingsTaskInstanceData`  
_L1602-1629_
- reflection: `USTRUCT()`
- L1607 _public member_ `FIntWrapper InputIntWrapper;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L1610 _public member_ `TArray<FIntWrapper> InputIntWrapperArray;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L1613 _public member_ `int32 InputIntA = 0;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L1616 _public member_ `int32 InputIntB = 0;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L1619 _public member_ `uint8 OutputBool : 1 = false;` — `UPROPERTY(EditAnywhere, Category = Output)`
- L1622 _public member_ `int32 OutputInt = 0;` — `UPROPERTY(EditAnywhere, Category = Output)`
- L1625 _public member_ `FIntWrapper OutputIntWrapper;` — `UPROPERTY(EditAnywhere, Category = Output)`
- L1628 _public member_ `TArray<FIntWrapper> OutputIntWrapperArray;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FTestTask_OutputBindingsTask`  
`struct FTestTask_OutputBindingsTask : public FStateTreeTaskBase`  
_L1632-1684_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- L1636 _public typedef_ `using FInstanceDataType = FTestTask_OutputBindingsTaskInstanceData;`
- L1638 _public prototype_ `FTestTask_OutputBindingsTask() = default;`
- L1640 _public function_ `explicit FTestTask_OutputBindingsTask(FName InName)`
- L1645 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L1647 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L1657 _public function_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override`
- L1667 _public function_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override`
- L1675 _public member_ `TFunction<void(FTestTask_OutputBindingsTaskInstanceData&)> CustomEnterFunc;`
- L1676 _public member_ `TFunction<void(FTestTask_OutputBindingsTaskInstanceData&)> CustomTickFunc;`
- L1677 _public member_ `TFunction<void(FTestTask_OutputBindingsTaskInstanceData&)> CustomExitFunc;`
- L1680 _public member_ `uint8 bShouldFailEnter : 1 = false;` — `UPROPERTY()`
- L1683 _public member_ `uint8 bShouldFailTick : 1 = false;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L58 _function_ `` (scope `FTestStateTreeExecutionContext::FTestStateTreeExecutionContext`)
- L161 _namespace_ `namespace UE`
- L161 _namespace_ `namespace StateTree` (scope `UE`)
- L161 _namespace_ `namespace Test` (scope `UE::StateTree`)
- L180 _namespace_ `namespace ENamespaceEnumByte` (scope `UE::StateTree::Test`)
- L1164 _prototype_ `UE_STATETREE_ZEROED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA(FTestPropertyFunction_InstanceData);`
- L1228 _prototype_ `UE_STATETREE_CONSTRUCTED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA(FStateTreeTestBooleanConditionInstanceData);`
- L1345 _function_ `` (scope `FTestTask_ListenDelegate::EnterState`)
- L1407 _function_ `` (scope `FTestTask_RebroadcastDelegate::EnterState`)
- L1450 _function_ `` (scope `FTestTask_CustomFuncOnDelegate::EnterState`)
- L1535 _function_ `` (scope `FTestTask_ListenerOnNode::EnterState`)
- L1578 _function_ `` (scope `FTestTask_ListenerOnInstance::EnterState`)

### `Plugins/Runtime/StateTree/Source/StateTreeTestSuite/Public/StateTreeTestBase.h` (Public)


#### struct `UE::StateTree::Tests::FStateTreeTestBase`  
`struct FStateTreeTestBase : public FAITestBase`  
_L17-29_
- inherits: `FAITestBase`
- desc: Base class for StateTree test
- L20 _protected prototype_ `UStateTree& NewStateTree() const;`
- L21 _protected prototype_ `static FStateTreePropertyPathBinding MakeBinding(const FGuid& SourceID, const FStringView Source, const FGuid& TargetID, const FStringView Target, const bool bInIsOutputBinding = false);`
- L22 _protected prototype_ `static FGameplayTag GetTestTag1();`
- L23 _protected prototype_ `static FGameplayTag GetTestTag2();`
- L24 _protected prototype_ `static FGameplayTag GetTestTag3();`
- L25 _protected prototype_ `static FGameplayTag GetTestTag4();`
- L26 _protected prototype_ `static FGameplayTag GetTestTag5();`
- L27 _protected prototype_ `static FGameplayTag GetTestTag6();`
- L28 _protected prototype_ `FInstancedPropertyBag& GetRootPropertyBag(UStateTreeEditorData& EditorData) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace StateTree` (scope `UE`)
- L11 _namespace_ `namespace Tests` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeTestSuite/Public/StateTreeTestSuiteModule.h` (Public)


#### class `IStateTreeTestSuiteModule`  
`class IStateTreeTestSuiteModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IStateTreeTestSuiteModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
