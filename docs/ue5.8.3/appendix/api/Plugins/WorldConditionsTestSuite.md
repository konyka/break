# Plugins / WorldConditionsTestSuite

- module root: `Plugins/Runtime/WorldConditions/Source/WorldConditionsTestSuite`
- headers: 2; symbols: 53
- symbol kinds: class=5, function=24, member=15, prototype=3, struct=5, typedef=1
- PrivateDependencyModuleNames: EditorFramework, UnrealEd

### `Plugins/Runtime/WorldConditions/Source/WorldConditionsTestSuite/Public/WorldConditionTestTypes.h` (Public)


#### struct `FWorldConditionTestData`  
`struct FWorldConditionTestData`  
_L10-21_
- reflection: `USTRUCT()`
- L14 _public prototype_ `FWorldConditionTestData() = default;`
- L15 _public function_ `explicit FWorldConditionTestData(const int32 InValue) : Value(InValue)`
- L17 _public member_ `FSimpleMulticastDelegate ValueChanged;`
- L19 _public member_ `int32 Value = 0;`
- L20 _public member_ `int32 AccessCount = 0;`

#### class `UWorldConditionTestSchema`  
`class UWorldConditionTestSchema : public UWorldConditionSchema`  
_L24-47_
- reflection: `UCLASS()`
- inherits: `UWorldConditionSchema`
- L28 _public function_ `explicit UWorldConditionTestSchema(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L35 _public function_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const override`
- L40 _public function_ `FWorldConditionContextDataRef GetActorRef() const`
- L41 _public function_ `FWorldConditionContextDataRef GetValueRef() const`
- L45 _private member_ `FWorldConditionContextDataRef ActorRef;`
- L46 _private member_ `FWorldConditionContextDataRef ValueRef;`

#### class `UWorldConditionTestCachedSchema`  
`class UWorldConditionTestCachedSchema : public UWorldConditionSchema`  
_L51-71_
- reflection: `UCLASS()`
- inherits: `UWorldConditionSchema`
- L55 _public function_ `explicit UWorldConditionTestCachedSchema(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L61 _public function_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const override`
- L66 _public function_ `FWorldConditionContextDataRef GetValueRef() const`
- L70 _private member_ `FWorldConditionContextDataRef ValueRef;`

#### struct `FWorldConditionTest`  
`struct FWorldConditionTest : public FWorldConditionBase`  
_L74-128_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FWorldConditionBase`
- L78 _public prototype_ `FWorldConditionTest() = default;`
- L79 _public function_ `explicit FWorldConditionTest(const int32 InTestValue, const bool bInActivateResult = true) : TestValue(InTestValue), bActivateResult(bInActivateResult)`
- L81 _public function_ `virtual TObjectPtr<const UStruct>* GetRuntimeStateType() const override`
- L83 _public function_ `virtual bool Initialize(const UWorldConditionSchema& Schema) override`
- L95 _public function_ `virtual bool Activate(const FWorldConditionContext& Context) const override`
- L100 _public function_ `virtual FWorldConditionResult IsTrue(const FWorldConditionContext& Context) const override`
- L113 _public function_ `virtual void Deactivate(const FWorldConditionContext& Context) const override`
- L117 _public function_ `virtual FText GetDescription() const override`
- L124 _protected member_ `FWorldConditionContextDataRef ValueRef;`
- L126 _protected member_ `int32 TestValue = 0;`
- L127 _protected member_ `bool bActivateResult = true;`

#### struct `FWorldConditionTestState`  
`struct FWorldConditionTestState`  
_L132-137_
- reflection: `USTRUCT()`
- L136 _public member_ `FDelegateHandle DelegateHandle;`

#### struct `FWorldConditionTestCached`  
`struct FWorldConditionTestCached : public FWorldConditionBase`  
_L140-224_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FWorldConditionBase`
- L144 _public prototype_ `FWorldConditionTestCached() = default;`
- L145 _public function_ `explicit FWorldConditionTestCached(const int32 InTestValue) : TestValue(InTestValue)`
- L147 _public typedef_ `using FStateType = FWorldConditionTestState;`
- L149 _public function_ `virtual TObjectPtr<const UStruct>* GetRuntimeStateType() const override`
- L155 _public function_ `virtual bool Initialize(const UWorldConditionSchema& Schema) override`
- L169 _public function_ `virtual bool Activate(const FWorldConditionContext& Context) const override`
- L190 _public function_ `virtual FWorldConditionResult IsTrue(const FWorldConditionContext& Context) const override`
- L205 _public function_ `virtual void Deactivate(const FWorldConditionContext& Context) const override`
- L221 _protected member_ `FWorldConditionContextDataRef ValueRef;`
- L223 _protected member_ `int32 TestValue = 0;`

#### class `UWorldConditionOwnerClass`  
`class UWorldConditionOwnerClass : public UObject`  
_L227-235_
- reflection: `UCLASS(hidden)`
- inherits: `UObject`
- L234 _public member_ `FWorldConditionQueryDefinition Definition;` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### struct `FWorldConditionQueryDefinitionContainer`  
`struct FWorldConditionQueryDefinitionContainer`  
_L238-244_
- reflection: `USTRUCT()`
- L243 _public member_ `FWorldConditionQueryDefinition Definition;` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### class `UWorldConditionOwnerClassWithNestedStruct`  
`class UWorldConditionOwnerClassWithNestedStruct : public UObject`  
_L247-255_
- reflection: `UCLASS(hidden)`
- inherits: `UObject`
- L254 _public member_ `FWorldConditionQueryDefinitionContainer Container;` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### Free symbols / members of external scopes

- L178 _function_ `` (scope `FWorldConditionTestCached::Activate`)

### `Plugins/Runtime/WorldConditions/Source/WorldConditionsTestSuite/Public/WorldConditionsTestSuiteModule.h` (Public)


#### class `IWorldConditionsTestSuiteModule`  
`class IWorldConditionsTestSuiteModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IWorldConditionsTestSuiteModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
