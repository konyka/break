# Plugins / StateTreeModule

- module root: `Plugins/Runtime/StateTree/Source/StateTreeModule`
- headers: 70; symbols: 3811
- symbol kinds: class=22, delegate=34, enum=62, enumerator=318, externvar=60, function=704, macro=129, member=880, namespace=132, prototype=1133, struct=276, typedef=57, variable=4

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Internal/StateTreeDelegatesInternal.h` (Internal)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STATETREEMODULE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace StateTree` (scope `UE`)
- L16 _namespace_ `namespace Delegates` (scope `UE::StateTree`)
- L16 _namespace_ `namespace Private` (scope `UE::StateTree::Delegates`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStateTreeAssetLoaded, TNotNull<UStateTree*> );` — A StateTree asset loads.
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStateTreeAssetLoaded, TNotNull<UStateTree*> );` (scope `UE::StateTree::Delegates::Private`) — A StateTree asset loads.
- L20 _externvar_ `extern FOnStateTreeAssetLoaded OnStateTreeAssetLoaded;` (scope `UE::StateTree::Delegates::Private`)
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStateTreeEditorBindingUpdated, TNotNull<UStateTreeEditorData*> );`
- L22 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStateTreeEditorBindingUpdated, TNotNull<UStateTreeEditorData*> );` (scope `UE::StateTree::Delegates::Private`)
- L23 _externvar_ `extern FOnStateTreeEditorBindingUpdated OnStateTreeEditorBindingUpdated;` (scope `UE::StateTree::Delegates::Private`)
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCompileIfChanged, TNotNull<UStateTree*> );` — A callback for UStateTree::CompileIfChanged.
- L27 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCompileIfChanged, TNotNull<UStateTree*> );` (scope `UE::StateTree::Delegates::Private`) — A callback for UStateTree::CompileIfChanged.
- L28 _externvar_ `extern FOnCompileIfChanged OnCompileIfChanged;` (scope `UE::StateTree::Delegates::Private`)
- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStateTreeMarkedDirty, TNotNull<UStateTree*> );` — A callback for UStateTree::MarkAsModified to notify that a tree was marked dirty.
- L31 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStateTreeMarkedDirty, TNotNull<UStateTree*> );` (scope `UE::StateTree::Delegates::Private`) — A callback for UStateTree::MarkAsModified to notify that a tree was marked dirty.
- L32 _externvar_ `extern FOnStateTreeMarkedDirty OnStateTreeMarkedAsModified;` (scope `UE::StateTree::Delegates::Private`)
- L35 _typedef_ `using FOnStateTreeRequestAssetRegistryTags = TTSDelegate<void(TNotNull<const UStateTree*> , FAssetRegistryTagsContext& )>;` (scope `UE::StateTree::Delegates::Private`) — A callback for UStateTree::GetAssetRegistryTags.
- L36 _externvar_ `extern FOnStateTreeRequestAssetRegistryTags OnRequestAssetRegistryTags;` (scope `UE::StateTree::Delegates::Private`)
- L39 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAppendToClassSchema, FAppendToClassSchemaContext& );` — A callback for UStateTree::AppendToClassSchema.
- L39 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAppendToClassSchema, FAppendToClassSchemaContext& );` (scope `UE::StateTree::Delegates::Private`) — A callback for UStateTree::AppendToClassSchema.
- L40 _externvar_ `extern FOnAppendToClassSchema OnAppendToClassSchema;` (scope `UE::StateTree::Delegates::Private`)
- L43 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPreCookStateTreeAsset, TNotNull<UStateTree*> );` — The StateTree asset is going to get cooked.
- L43 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPreCookStateTreeAsset, TNotNull<UStateTree*> );` (scope `UE::StateTree::Delegates::Private`) — The StateTree asset is going to get cooked.
- L44 _externvar_ `extern FOnPreCookStateTreeAsset OnPreCookStateTreeAsset;` (scope `UE::StateTree::Delegates::Private`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Private/CrashReporter/StateTreeCrashReporterHandler.h` (Private)


#### struct `UE::StateTree::FCrashReporterHandler`  
`struct FCrashReporterHandler`  
_L24-28_
- desc: Additional crash context for StateTree. Will add extra information on the asset when crashing inside a StateTree callstack.
- L26 _public prototype_ `static void Register();`
- L27 _public prototype_ `static void Unregister();`

#### class `UE::StateTree::FCrashReporterScope`  
`class FCrashReporterScope`  
_L31-44_
- desc: Helper object allowing easy tracking of StateTree code in crash reporter.
- L34 _public prototype_ `explicit FCrashReporterScope(TNotNull<const UObject*> Owner, TNotNull<const UStateTree*> StateTree, FName Context);`
- L35 _public prototype_ `~FCrashReporterScope();`
- L37 _public prototype_ `FCrashReporterScope() = delete;`
- L38 _public prototype_ `FCrashReporterScope(const FCrashReporterScope&) = delete;`
- L39 _public prototype_ `FCrashReporterScope& operator=(const FCrashReporterScope&) = delete;`
- L42 _private member_ `bool bWasEnabled = false;`
- L43 _private member_ `uint32 ID = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_WITH_STATETREE_CRASHREPORTER WITH_ADDITIONAL_CRASH_CONTEXTS`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace StateTree` (scope `UE`)
- L51 _macro_ `#define UE_STATETREE_CRASH_REPORTER_SCOPE(InOwner, InStateTree, InContext) ::UE::StateTree::FCrashReporterScope ANONYMOUS_VARIABLE(AddCrashContext) {(InOwner), (InStateTree), (InContext)}`
- L53 _macro_ `#define UE_STATETREE_CRASH_REPORTER_SCOPE(InOwner, InStateTree, InContext)`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Private/Debugger/StateTreeRuntimeValidationInstanceData.h` (Private)


#### class `UE::StateTree::Debug::FRuntimeValidationInstanceData`  
`class FRuntimeValidationInstanceData`  
_L17-51_
- desc: For debugging purposes. Data used for runtime check.
- L20 _public prototype_ `FRuntimeValidationInstanceData() = default;`
- L21 _public prototype_ `~FRuntimeValidationInstanceData();`
- L23 _public prototype_ `void SetContext(TNotNull<const UObject*> InOwner, TNotNull<const UStateTree*> InStateTree, bool bInInstanceDataWriteAccessAcquired);`
- L25 _public prototype_ `void NodeEnterState(const FGuid& NodeID, FActiveFrameID FrameID);`
- L26 _public prototype_ `void NodeExitState(const FGuid& NodeID, FActiveFrameID FrameID);`
- L27 _public prototype_ `void NodeTick(const FGuid& NodeID, FActiveFrameID FrameID);`
- L30 _private prototype_ `void ValidateTreeNodes(TNotNull<const UStateTree*> NewStateTree) const;`
- L31 _private prototype_ `void ValidateInstanceData(TNotNull<const UStateTree*> NewStateTree);`
- L39 _private member_ `TArray<FNodeStatePair> NodeStates;`
- L40 _private member_ `TWeakObjectPtr<const UStateTree> StateTree;`
- L41 _private member_ `TWeakObjectPtr<const UObject> Owner;`
- L44 _private member_ `bool bInstanceDataWriteAccessAcquired = false;` — An ExecContext with write access to the Instance Storage data this is debugging on has been created
- L50 _private member_ `TOptional<bool> bMaintainNodeStates;` — The execution started with bRuntimeValidationEnterExitState set to true. It will keep maintaining the NodeStates array even if bRuntimeValidationEnterExitState is set to false afterward. The bRuntimeValidationEnterExitState can be reset to true after a fail, and we need to keep maintaining the array.

#### struct `UE::StateTree::Debug::FRuntimeValidationInstanceData::FNodeStatePair`  
`struct FNodeStatePair`  
_L34-38_
- L36 _public member_ `FGuid NodeID;`
- L37 _public member_ `FActiveFrameID FrameID;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace StateTree` (scope `UE`)
- L12 _namespace_ `namespace Debug` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Private/PropertyFunctions/StateTreeBooleanAlgebraPropertyFunctions.h` (Private)


#### struct `FStateTreeBooleanOperationPropertyFunctionInstanceData`  
`struct FStateTreeBooleanOperationPropertyFunctionInstanceData`  
_L13-25_
- reflection: `USTRUCT()`
- L18 _public member_ `bool bLeft = false;` — `UPROPERTY(EditAnywhere, Category = Param)`
- L21 _public member_ `bool bRight = false;` — `UPROPERTY(EditAnywhere, Category = Param)`
- L24 _public member_ `bool bResult = false;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FStateTreeBooleanAndPropertyFunction`  
`struct FStateTreeBooleanAndPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L31-44_
- reflection: `USTRUCT(meta=(DisplayName = "And", Category="Logic"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Performs 'And' operation on two booleans.
- L35 _public typedef_ `using FInstanceDataType = FStateTreeBooleanOperationPropertyFunctionInstanceData;`
- L37 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L39 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L42 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeBooleanOrPropertyFunction`  
`struct FStateTreeBooleanOrPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L50-63_
- reflection: `USTRUCT(meta=(DisplayName = "Or", Category="Logic"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Performs 'Or' operation on two booleans.
- L54 _public typedef_ `using FInstanceDataType = FStateTreeBooleanOperationPropertyFunctionInstanceData;`
- L56 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L58 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L61 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeBooleanXOrPropertyFunction`  
`struct FStateTreeBooleanXOrPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L69-82_
- reflection: `USTRUCT(meta=(DisplayName = "XOr", Category="Logic"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Performs 'Exclusive Or' operation on two booleans.
- L73 _public typedef_ `using FInstanceDataType = FStateTreeBooleanOperationPropertyFunctionInstanceData;`
- L75 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L77 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L80 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeBooleanNotOperationPropertyFunctionInstanceData`  
`struct FStateTreeBooleanNotOperationPropertyFunctionInstanceData`  
_L85-94_
- reflection: `USTRUCT()`
- L90 _public member_ `bool bInput = false;` — `UPROPERTY(EditAnywhere, Category = Param)`
- L93 _public member_ `bool bResult = false;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FStateTreeBooleanNotPropertyFunction`  
`struct FStateTreeBooleanNotPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L100-113_
- reflection: `USTRUCT(meta=(DisplayName = "Not", Category="Logic"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Performs 'Not' operation on a boolean.
- L104 _public typedef_ `using FInstanceDataType = FStateTreeBooleanNotOperationPropertyFunctionInstanceData;`
- L106 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L108 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L111 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Private/PropertyFunctions/StateTreeFloatPropertyFunctions.h` (Private)


#### struct `FStateTreeFloatCombinaisonPropertyFunctionInstanceData`  
`struct FStateTreeFloatCombinaisonPropertyFunctionInstanceData`  
_L13-25_
- reflection: `USTRUCT()`
- L18 _public member_ `float Left = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L21 _public member_ `float Right = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L24 _public member_ `float Result = 0.f;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FStateTreeAddFloatPropertyFunction`  
`struct FStateTreeAddFloatPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L31-44_
- reflection: `USTRUCT(meta=(DisplayName = "Add", Category = "Math|Float"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Add two floats.
- L35 _public typedef_ `using FInstanceDataType = FStateTreeFloatCombinaisonPropertyFunctionInstanceData;`
- L37 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L39 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L42 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeSubtractFloatPropertyFunction`  
`struct FStateTreeSubtractFloatPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L50-63_
- reflection: `USTRUCT(meta=(DisplayName = "Subtract", Category = "Math|Float"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Subtract right float from left float.
- L54 _public typedef_ `using FInstanceDataType = FStateTreeFloatCombinaisonPropertyFunctionInstanceData;`
- L56 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L58 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L61 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeMultiplyFloatPropertyFunction`  
`struct FStateTreeMultiplyFloatPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L69-82_
- reflection: `USTRUCT(meta=(DisplayName = "Multiply", Category = "Math|Float"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Multiply the two given float.
- L73 _public typedef_ `using FInstanceDataType = FStateTreeFloatCombinaisonPropertyFunctionInstanceData;`
- L75 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L77 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L80 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeDivideFloatPropertyFunction`  
`struct FStateTreeDivideFloatPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L88-101_
- reflection: `USTRUCT(meta=(DisplayName = "Divide", Category = "Math|Float"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Divide left float by right float.
- L92 _public typedef_ `using FInstanceDataType = FStateTreeFloatCombinaisonPropertyFunctionInstanceData;`
- L94 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L96 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L99 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeSingleFloatPropertyFunctionInstanceData`  
`struct FStateTreeSingleFloatPropertyFunctionInstanceData`  
_L104-113_
- reflection: `USTRUCT()`
- L109 _public member_ `float Input = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L112 _public member_ `float Result = 0.f;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FStateTreeInvertFloatPropertyFunction`  
`struct FStateTreeInvertFloatPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L119-132_
- reflection: `USTRUCT(meta=(DisplayName = "Invert", Category = "Math|Float"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Invert the given float.
- L123 _public typedef_ `using FInstanceDataType = FStateTreeSingleFloatPropertyFunctionInstanceData;`
- L125 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L127 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L130 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeAbsoluteFloatPropertyFunction`  
`struct FStateTreeAbsoluteFloatPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L138-151_
- reflection: `USTRUCT(meta=(DisplayName = "Absolute", Category = "Math|Float"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Gives the absolute value of the given float.
- L142 _public typedef_ `using FInstanceDataType = FStateTreeSingleFloatPropertyFunctionInstanceData;`
- L144 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L146 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L149 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Private/PropertyFunctions/StateTreeIntPropertyFunctions.h` (Private)


#### struct `FStateTreeIntCombinaisonPropertyFunctionInstanceData`  
`struct FStateTreeIntCombinaisonPropertyFunctionInstanceData`  
_L13-25_
- reflection: `USTRUCT()`
- L18 _public member_ `int32 Left = 0;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L21 _public member_ `int32 Right = 0;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L24 _public member_ `int32 Result = 0;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FStateTreeAddIntPropertyFunction`  
`struct FStateTreeAddIntPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L31-44_
- reflection: `USTRUCT(meta=(DisplayName = "Add", Category = "Math|Integer"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Add two ints.
- L35 _public typedef_ `using FInstanceDataType = FStateTreeIntCombinaisonPropertyFunctionInstanceData;`
- L37 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L39 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L42 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeSubtractIntPropertyFunction`  
`struct FStateTreeSubtractIntPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L50-63_
- reflection: `USTRUCT(meta=(DisplayName = "Subtract", Category = "Math|Integer"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Subtract right int from left int.
- L54 _public typedef_ `using FInstanceDataType = FStateTreeIntCombinaisonPropertyFunctionInstanceData;`
- L56 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L58 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L61 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeMultiplyIntPropertyFunction`  
`struct FStateTreeMultiplyIntPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L69-82_
- reflection: `USTRUCT(meta=(DisplayName = "Multiply", Category = "Math|Integer"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Multiply the two given ints.
- L73 _public typedef_ `using FInstanceDataType = FStateTreeIntCombinaisonPropertyFunctionInstanceData;`
- L75 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L77 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L80 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeDivideIntPropertyFunction`  
`struct FStateTreeDivideIntPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L88-101_
- reflection: `USTRUCT(meta=(DisplayName = "Divide", Category = "Math|Integer"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Divide left int by right int.
- L92 _public typedef_ `using FInstanceDataType = FStateTreeIntCombinaisonPropertyFunctionInstanceData;`
- L94 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L96 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L99 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeSingleIntPropertyFunctionInstanceData`  
`struct FStateTreeSingleIntPropertyFunctionInstanceData`  
_L104-113_
- reflection: `USTRUCT()`
- L109 _public member_ `int32 Input = 0;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L112 _public member_ `int32 Result = 0;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FStateTreeInvertIntPropertyFunction`  
`struct FStateTreeInvertIntPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L119-132_
- reflection: `USTRUCT(meta=(DisplayName = "Invert", Category = "Math|Integer"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Invert the given int.
- L123 _public typedef_ `using FInstanceDataType = FStateTreeSingleIntPropertyFunctionInstanceData;`
- L125 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L127 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L130 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### struct `FStateTreeAbsoluteIntPropertyFunction`  
`struct FStateTreeAbsoluteIntPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L138-151_
- reflection: `USTRUCT(meta=(DisplayName = "Absolute", Category = "Math|Integer"))`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Gives the absolute value of the given int.
- L142 _public typedef_ `using FInstanceDataType = FStateTreeSingleIntPropertyFunctionInstanceData;`
- L144 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L146 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L149 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Private/PropertyFunctions/StateTreeIntervalPropertyFunctions.h` (Private)


#### struct `FStateTreeMakeIntervalPropertyFunctionInstanceData`  
`struct FStateTreeMakeIntervalPropertyFunctionInstanceData`  
_L13-25_
- reflection: `USTRUCT()`
- L18 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L21 _public member_ `float Max = 1.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L24 _public member_ `FFloatInterval Result = FFloatInterval(0.f, 1.f);` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FStateTreeMakeIntervalPropertyFunction`  
`struct FStateTreeMakeIntervalPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L31-44_
- reflection: `USTRUCT(DisplayName = "Make Interval")`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Make an Interval from two floats.
- L35 _public typedef_ `using FInstanceDataType = FStateTreeMakeIntervalPropertyFunctionInstanceData;`
- L37 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L39 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L42 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Private/PropertyFunctions/StateTreeTransformPropertyFunctions.h` (Private)


#### struct `FStateTreeMakeTransformPropertyFunctionInstanceData`  
`struct FStateTreeMakeTransformPropertyFunctionInstanceData`  
_L13-25_
- reflection: `USTRUCT()`
- L18 _public member_ `FVector InTranslation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (DisplayName = "Translation"))`
- L21 _public member_ `FQuat InRotation = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (DisplayName = "Rotation"))`
- L24 _public member_ `FTransform OutTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = Output, meta = (DisplayName = "Transform"))`

#### struct `FStateTreeMakeTransformPropertyFunction`  
`struct FStateTreeMakeTransformPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L31-50_
- reflection: `USTRUCT(DisplayName = "Make Transform")`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Make a transform from translation and rotation.
- L35 _public typedef_ `using FInstanceDataType = FStateTreeMakeTransformPropertyFunctionInstanceData;`
- L37 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L42 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L45 _public function_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const override`

#### struct `FStateTreeBreakTransformPropertyFunctionInstanceData`  
`struct FStateTreeBreakTransformPropertyFunctionInstanceData`  
_L53-65_
- reflection: `USTRUCT()`
- L58 _public member_ `FTransform InTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (DisplayName = "Transform"))`
- L61 _public member_ `FVector OutTranslation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Output, meta = (DisplayName = "Translation"))`
- L64 _public member_ `FQuat OutRotation = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category = Output, meta = (DisplayName = "Rotation"))`

#### struct `FStateTreeBreakTransformPropertyFunction`  
`struct FStateTreeBreakTransformPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L71-90_
- reflection: `USTRUCT(DisplayName = "Break Transform")`
- inherits: `FStateTreePropertyFunctionCommonBase`
- desc: Break a transform into position and rotation.
- L75 _public typedef_ `using FInstanceDataType = FStateTreeBreakTransformPropertyFunctionInstanceData;`
- L77 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L82 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L85 _public function_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const override`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Private/StateTreeInstanceDataHelpers.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace StateTree` (scope `UE`)
- L7 _namespace_ `namespace InstanceData` (scope `UE::StateTree`)
- L7 _namespace_ `namespace Private` (scope `UE::StateTree::InstanceData`)
- L10 _prototype_ `[[nodiscard]] bool IsActiveInstanceHandleSourceValid( const FStateTreeInstanceStorage& Storage, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle& Handle);` (scope `UE::StateTree::InstanceData::Private`) — @return whether the handle is valid when it's an instance data type.
- L16 _prototype_ `[[nodiscard]] bool IsHandleSourceValid( const FStateTreeInstanceStorage& InstanceStorage, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle& Handle);` (scope `UE::StateTree::InstanceData::Private`) — @return whether the handle is valid relative to the given frame.
- L22 _prototype_ `[[nodiscard]] FStateTreeDataView GetTemporaryDataView( FStateTreeInstanceStorage& InstanceStorage, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle& Handle);` (scope `UE::StateTree::InstanceData::Private`) — @return data view of the specified handle in temporary instance.
- L28 _prototype_ `[[nodiscard]] bool AreAllInstancesValid(const FInstancedStructContainer& InstanceStructs);` (scope `UE::StateTree::InstanceData::Private`) — @return true if all instances are valid.
- L31 _prototype_ `[[nodiscard]] int32 GetAllocatedMemory(const FInstancedStructContainer& InstanceStructs);` (scope `UE::StateTree::InstanceData::Private`) — Returns number of bytes allocated for the array
- L34 _prototype_ `[[nodiscard]] TNotNull<UObject*> CopyNodeInstance(TNotNull<UObject*> Instance, TNotNull<UObject*> InOwner, bool bDuplicate);` (scope `UE::StateTree::InstanceData::Private`) — Duplicates object, and tries to covert old BP classes (REINST_*) to their newer version.
- L37 _prototype_ `void PostAppendToInstanceStructContainer(FInstancedStructContainer& InstanceStructs, TNotNull<UObject*> InOwner, bool bDuplicateWrappedObject, int32 StartIndex);` (scope `UE::StateTree::InstanceData::Private`) — None generic code for AppendToInstanceStructContainer. Called after AppendToInstanceStructContainer to move code to cpp.
- L41 _function_ `template<typename TOtherType> int32 AppendToInstanceStructContainer(FInstancedStructContainer& InstanceStructs, TNotNull<UObject*> InOwner, TConstArrayView<TOtherType> InStructs, bool bDuplicateWrappedObject)` (scope `UE::StateTree::InstanceData::Private`) — Appends new items to the instance, and moves existing data into the allocated instances.

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Private/StateTreeModuleImpl.h` (Private)


#### class `FStateTreeModule`  
`class FStateTreeModule : public IStateTreeModule`  
_L20-78_
- inherits: `IStateTreeModule`
- L23 _public prototype_ `FStateTreeModule();`
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _public prototype_ `virtual bool StartTraces(int32& OutTraceId) override;`
- L31 _public prototype_ `virtual bool IsTracing() const override;`
- L32 _public prototype_ `virtual void StopTraces() override;`
- L35 _public member_ `static FTSSimpleMulticastDelegate OnPreRuntimeValidationInstanceData;`
- L36 _public member_ `static FTSSimpleMulticastDelegate OnPostRuntimeValidationInstanceData;`
- L42 _private prototype_ `void HandlePreGC();`
- L43 _private prototype_ `void HandlePostGC();`
- L50 _private prototype_ `virtual UE::Trace::FStoreClient* GetStoreClient() override;` — Gets the store client.
- L52 _private member_ `TSharedPtr<TraceServices::IAnalysisService> TraceAnalysisService;`
- L53 _private member_ `TSharedPtr<TraceServices::IModuleService> TraceModuleService;`
- L56 _private member_ `TUniquePtr<UE::Trace::FStoreClient> StoreClient;` — The client used to connect to the trace store.
- L58 _private member_ `FStateTreeTraceModule StateTreeTraceModule;`
- L60 _private prototype_ `virtual TNotNull<const IStateTreeDebugInfoProvider*> GetDebugInfoProvider() override;`
- L61 _private prototype_ `virtual void SetDebugInfoProvider(TSharedPtr<IStateTreeDebugInfoProvider> InDebugInfoProvider) override;`
- L63 _private member_ `TSharedPtr<IStateTreeDebugInfoProvider> DebugInfoProvider;`
- L68 _private member_ `TArray<const FString> ChannelsToRestore;`
- L70 _private member_ `FAutoConsoleCommand StartDebuggerTracesCommand;`
- L71 _private member_ `FAutoConsoleCommand StopDebuggerTracesCommand;`
- L75 _private member_ `FDelegateHandle PreGCHandle;`
- L76 _private member_ `FDelegateHandle PostGCHandle;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace TraceServices`
- L16 _namespace_ `namespace TraceServices`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Trace` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Private/Tasks/StateTreeDebugTextTask.h` (Private)


#### struct `FStateTreeDebugTextTaskInstanceData`  
`struct FStateTreeDebugTextTaskInstanceData`  
_L14-27_
- reflection: `USTRUCT()`
- L19 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L23 _public member_ `TObjectPtr<AActor> ReferenceActor = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Input", meta=(Optional))` — Optional actor where to draw the text at.
- L26 _public member_ `FString BindableText;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeDebugTextTask`  
`struct FStateTreeDebugTextTask : public FStateTreeTaskCommonBase`  
_L33-77_
- reflection: `USTRUCT(meta = (DisplayName = "Debug Text Task"))`
- inherits: `FStateTreeTaskCommonBase`
- desc: Draws debug text on the HUD associated to the player controller.
- L37 _public typedef_ `using FInstanceDataType = FStateTreeDebugTextTaskInstanceData;`
- L39 _public prototype_ `FStateTreeDebugTextTask();`
- L41 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L43 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L44 _public prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L46 _public prototype_ `virtual void PostLoad(FStateTreeDataView InstanceDataView) override;`
- L47 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L48 _public function_ `virtual FName GetIconName() const override`
- L52 _public function_ `virtual FColor GetIconColor() const override`
- L59 _public member_ `FString Text;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L62 _public member_ `FColor TextColor = FColor::White;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L65 _public member_ `float FontScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Parameter", meta=(ClampMin = 0, UIMin = 0))`
- L68 _public member_ `FVector Offset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L72 _public member_ `bool bEnabled_DEPRECATED = true;` — `UPROPERTY()`
- L75 _public member_ `int32 DeprecatedVersion = 0;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Private/Tasks/StateTreeDelayTask.h` (Private)


#### struct `FStateTreeDelayTaskInstanceData`  
`struct FStateTreeDelayTaskInstanceData`  
_L14-35_
- reflection: `USTRUCT()`
- L20 _public member_ `float Duration = 1.f;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (EditCondition = "!bRunForever", ClampMin="0.0"))` — Delay before the task ends.
- L24 _public member_ `float RandomDeviation = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (EditCondition = "!bRunForever", ClampMin="0.0"))` — Adds random range to the Duration.
- L28 _public member_ `bool bRunForever = false;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — If true the task will run forever until a transition stops it.
- L31 _public member_ `float RemainingTime = 0.f;` — Internal countdown in seconds.
- L34 _public member_ `UE::StateTree::FScheduledTickHandle ScheduledTickHandle;` — The handle of the scheduled tick request.

#### struct `FStateTreeDelayTask`  
`struct FStateTreeDelayTask : public FStateTreeTaskCommonBase`  
_L41-66_
- reflection: `USTRUCT(meta = (DisplayName = "Delay Task"))`
- inherits: `FStateTreeTaskCommonBase`
- desc: Simple task to wait indefinitely or for a given time (in seconds) before succeeding.
- L45 _public typedef_ `using FInstanceDataType = FStateTreeDelayTaskInstanceData;`
- L47 _public prototype_ `FStateTreeDelayTask();`
- L49 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L51 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L52 _public prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L53 _public prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L56 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L57 _public function_ `virtual FName GetIconName() const override`
- L61 _public function_ `virtual FColor GetIconColor() const override`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Blueprint/StateTreeConditionBlueprintBase.h` (Public)


#### class `UStateTreeConditionBlueprintBase`  
`class UStateTreeConditionBlueprintBase : public UStateTreeNodeBlueprintBase`  
_L18-33_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UStateTreeNodeBlueprintBase`
- desc: Base class for Blueprint based Conditions.
- L22 _public prototype_ `UStateTreeConditionBlueprintBase(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `bool ReceiveTestCondition() const;` — `UFUNCTION(BlueprintImplementableEvent)`
- L28 _protected prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const;`
- L32 _protected member_ `uint8 bHasTestCondition : 1;`

#### struct `FStateTreeBlueprintConditionWrapper`  
`struct FStateTreeBlueprintConditionWrapper : public FStateTreeConditionBase`  
_L39-53_
- reflection: `USTRUCT()`
- inherits: `FStateTreeConditionBase`
- desc: Wrapper for Blueprint based Conditions.
- L43 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L44 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L46 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L47 _public prototype_ `virtual FName GetIconName() const override;`
- L48 _public prototype_ `virtual FColor GetIconColor() const override;`
- L52 _public member_ `TSubclassOf<UStateTreeConditionBlueprintBase> ConditionClass;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Blueprint/StateTreeConsiderationBlueprintBase.h` (Public)


#### class `UStateTreeConsiderationBlueprintBase`  
`class UStateTreeConsiderationBlueprintBase : public UStateTreeNodeBlueprintBase`  
_L18-34_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UStateTreeNodeBlueprintBase`
- desc: Base class for Blueprint based Considerations.
- L23 _public prototype_ `UStateTreeConsiderationBlueprintBase(const FObjectInitializer& ObjectInitializer);`
- L26 _public prototype_ `float ReceiveGetScore() const;` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "GetScore"))`
- L29 _protected prototype_ `virtual float GetScore(FStateTreeExecutionContext& Context) const;`
- L33 _protected member_ `uint8 bHasGetScore : 1;`

#### struct `FStateTreeBlueprintConsiderationWrapper`  
`struct FStateTreeBlueprintConsiderationWrapper : public FStateTreeConsiderationBase`  
_L40-61_
- reflection: `USTRUCT()`
- inherits: `FStateTreeConsiderationBase`
- desc: Wrapper for Blueprint based Considerations.
- L45 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L47 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L48 _public prototype_ `virtual FName GetIconName() const override;`
- L49 _public prototype_ `virtual FColor GetIconColor() const override;`
- L55 _protected prototype_ `virtual float GetScore(FStateTreeExecutionContext& Context) const override;`
- L60 _public member_ `TSubclassOf<UStateTreeConsiderationBlueprintBase> ConsiderationClass;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Blueprint/StateTreeEvaluatorBlueprintBase.h` (Public)


#### class `UStateTreeEvaluatorBlueprintBase`  
`class UStateTreeEvaluatorBlueprintBase : public UStateTreeNodeBlueprintBase`  
_L18-43_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UStateTreeNodeBlueprintBase`
- desc: Base class for Blueprint based evaluators.
- L22 _public prototype_ `UStateTreeEvaluatorBlueprintBase(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `void ReceiveTreeStart();` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "TreeStart"))`
- L28 _public prototype_ `void ReceiveTreeStop();` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "TreeStop"))`
- L31 _public prototype_ `void ReceiveTick(const float DeltaTime);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Tick"))`
- L34 _protected prototype_ `virtual void TreeStart(FStateTreeExecutionContext& Context);`
- L35 _protected prototype_ `virtual void TreeStop(FStateTreeExecutionContext& Context);`
- L36 _protected prototype_ `virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime);`
- L38 _protected member_ `uint8 bHasTreeStart : 1;`
- L39 _protected member_ `uint8 bHasTreeStop : 1;`
- L40 _protected member_ `uint8 bHasTick : 1;`

#### struct `FStateTreeBlueprintEvaluatorWrapper`  
`struct FStateTreeBlueprintEvaluatorWrapper : public FStateTreeEvaluatorBase`  
_L49-66_
- reflection: `USTRUCT()`
- inherits: `FStateTreeEvaluatorBase`
- desc: Wrapper for Blueprint based Evaluators.
- L53 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L55 _public prototype_ `virtual void TreeStart(FStateTreeExecutionContext& Context) const override;`
- L56 _public prototype_ `virtual void TreeStop(FStateTreeExecutionContext& Context) const override;`
- L57 _public prototype_ `virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L59 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L60 _public prototype_ `virtual FName GetIconName() const override;`
- L61 _public prototype_ `virtual FColor GetIconColor() const override;`
- L65 _public member_ `TSubclassOf<UStateTreeEvaluatorBlueprintBase> EvaluatorClass;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Blueprint/StateTreeNodeBlueprintBase.h` (Public)


#### enum `EStateTreeBlueprintPropertyCategory`  
`enum class EStateTreeBlueprintPropertyCategory : uint8`  
_L22-29_
- reflection: `UENUM()`
- L24 _public enumerator_ `NotSet`
- L25 _public enumerator_ `Input`
- L26 _public enumerator_ `Parameter`
- L27 _public enumerator_ `Output`
- L28 _public enumerator_ `ContextObject`

#### struct `FStateTreeBlueprintExternalDataHandle`  
`struct FStateTreeBlueprintExternalDataHandle`  
_L33-37_
- desc: Struct use to copy external data to the Blueprint item instance, resolved during StateTree linking.
- L35 _public member_ `const FProperty* Property = nullptr;`
- L36 _public member_ `FStateTreeExternalDataHandle Handle;`

#### class `UStateTreeNodeBlueprintBase`  
`class UStateTreeNodeBlueprintBase : public UObject`  
_L41-144_
- reflection: `UCLASS(MinimalAPI, Abstract, meta = (DisallowLevelActorReference = true))`
- inherits: `UObject`
- L48 _public prototype_ `void SendEvent(const FStateTreeEvent& Event);` — `UFUNCTION(BlueprintCallable, Category = "StateTree", meta = (HideSelfPin = "true", DisplayName = "StateTree Send Event"))` — Sends event to the StateTree.
- L52 _public prototype_ `void RequestTransition(const FStateTreeStateLink& TargetState, const EStateTreeTransitionPriority Priority = EStateTreeTransitionPriority::Normal);` — `UFUNCTION(BlueprintCallable, Category = "StateTree", meta = (HideSelfPin = "true", DisplayName = "StateTree Request Transition"))` — Request state transition.
- L56 _public prototype_ `void GetPropertyReference(const FStateTreeBlueprintPropertyRef& PropertyRef) const;` — `UFUNCTION(CustomThunk)` — Returns a reference to selected property in State Tree.
- L60 _public prototype_ `bool IsPropertyRefValid(const FStateTreeBlueprintPropertyRef& PropertyRef) const;` — `UFUNCTION()` — Returns true if reference to selected property in State Tree is accessible.
- L64 _public prototype_ `FText GetPropertyDescriptionByPropertyName(FName PropertyName) const;` — `UFUNCTION(BlueprintCallable, Category = "StateTree", meta=( BlueprintInternalUseOnly="true" ))` — @return text describing the property, either direct value or binding description. Used internally.
- L67 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`
- L69 _public function_ `FName GetIconName() const`
- L74 _public function_ `FColor GetIconColor() const`
- L84 _protected prototype_ `FText ReceiveGetDescription(EStateTreeNodeFormatting Formatting) const;` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Get Description"))` — Event to implement to get node description.
- L86 _protected prototype_ `virtual UWorld* GetWorld() const override;`
- L87 _protected prototype_ `AActor* GetOwnerActor(const FStateTreeExecutionContext& Context) const;`
- L90 _protected prototype_ `void SetCachedInstanceDataFromContext(const FStateTreeExecutionContext& Context) const;` — These methods are const as they set mutable variables and need to be called from a const method.
- L91 _protected prototype_ `void ClearCachedInstanceData() const;`
- L93 _protected function_ `FStateTreeWeakExecutionContext GetWeakExecutionContext() const`
- L101 _private prototype_ `void* GetMutablePtrToProperty(const FStateTreeBlueprintPropertyRef& PropertyRef, FProperty*& OutSourceProperty) const;`
- L104 _private member_ `mutable FStateTreeWeakExecutionContext WeakExecutionContext;` — Cached execution context while the node is active for async nodes.
- L110 _private member_ `mutable TWeakPtr<FStateTreeInstanceStorage> WeakInstanceStorage;` — Cached instance data while the node is active for async nodes.
- L115 _private member_ `mutable TObjectPtr<const UStateTree> CachedFrameStateTree = nullptr;` — `UPROPERTY()` — Cached State Tree of owning execution frame.
- L119 _private member_ `mutable FStateTreeStateHandle CachedFrameRootState;` — Cached root state of owning execution frame.
- L123 _private member_ `FText Description;` — `UPROPERTY(EditDefaultsOnly, Category="Description")` — Description of the node.
- L132 _private member_ `FName IconName;` — `UPROPERTY(EditDefaultsOnly, Category="Description")` — Name of the icon in format: StyleSetName | StyleName [ | SmallStyleName | StatusOverlayStyleName] SmallStyleName and StatusOverlayStyleName are optional. Example: "StateTreeEditorStyle|Node.Animation"
- L136 _private member_ `FColor IconColor = UE::StateTree::Colors::Grey;` — `UPROPERTY(EditDefaultsOnly, Category="Description")` — Color of the icon.
- L141 _private member_ `static FGuid CachedNodeID;` — Cached values used during editor to make some BP nodes simpler to use.
- L142 _private member_ `static const IStateTreeBindingLookup* CachedBindingLookup;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Blueprint/StateTreeTaskBlueprintBase.h` (Public)


#### class `UStateTreeTaskBlueprintBase`  
`class UStateTreeTaskBlueprintBase : public UStateTreeNodeBlueprintBase`  
_L21-168_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UStateTreeNodeBlueprintBase`
- desc: Base class for Blueprint based Tasks.
- L26 _public prototype_ `UStateTreeTaskBlueprintBase(const FObjectInitializer& ObjectInitializer);`
- L38 _public prototype_ `void ReceiveLatentEnterState(const FStateTreeTransitionResult& Transition);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "EnterState"))` — Called when a new state is entered and task is part of active states. Use FinishTask() to set the task execution completed. State completion is controlled by completed tasks. GameplayTasks and other latent actions should be generally triggered on EnterState. When using a GameplayTasks it's required to manually cancel active tasks on ExitState if the GameplayTask's lifetime is tied to the State Tree task. @param Transition Describes the states involved in the transition
- L45 _public prototype_ `void ReceiveExitState(const FStateTreeTransitionResult& Transition);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ExitState"))` — Called when a current state is exited and task is part of active states. @param Transition Describes the states involved in the transition
- L54 _public prototype_ `void ReceiveStateCompleted(const EStateTreeRunStatus CompletionStatus, const FStateTreeActiveStates CompletedActiveStates);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "StateCompleted"))` — Called right after a state has been completed, but before new state has been selected. StateCompleted is called in reverse order to allow to propagate state to other Tasks that are executed earlier in the tree. Note that StateCompleted is not called if conditional transition changes the state. @param CompletionStatus Describes the running status of the completed state (Succeeded/Failed). @param CompletedActiveStates Active states at the time of completion.
- L68 _public prototype_ `void ReceiveLatentTick(const float DeltaTime);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Tick"))` — Called during state tree tick when the task is on active state. Use FinishTask() to set the task execution completed. State completion is controlled by completed tasks. Triggering GameplayTasks and other latent action should generally be done on EnterState. Tick is called on each update (or event) and can cause huge amount of task added if the logic is not handled carefully. Tick should be generally be used for monitoring that require polling, or actions that require constant ticking. Note: The method is called only if bShouldCallTick or bShouldCallTickOnlyOnEvents is set. @param DeltaTime Time since last StateTree tick.
- L72 _public prototype_ `EStateTreeRunStatus ReceiveEnterState(const FStateTreeTransitionResult& Transition);` — `UE_DEPRECATED(all, "Use the new EnterState event without without return value instead. Task status is now controlled via FinishTask node, instead of a return value. Default status is running.")` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "EnterState (Deprecated)", DeprecatedFunction, DeprecationMessage="Use the new EnterState event without without return value instead. Task status is now controlled via FinishTask node, instead of a return value. Default status is running."))`
- L76 _public prototype_ `EStateTreeRunStatus ReceiveTick(const float DeltaTime);` — `UE_DEPRECATED(all, "Use the new Tick event without without return value instead. Task status is now controlled via FinishTask node, instead of a return value. Default status is running.")` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Tick (Deprecated)", DeprecatedFunction, DeprecationMessage="Use the new Tick event without without return value instead. Task status is now controlled via FinishTask node, instead of a return value. Default status is running."))`
- L79 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition);`
- L80 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition);`
- L82 _protected prototype_ `virtual void StateCompleted(FStateTreeExecutionContext& Context, const EStateTreeRunStatus CompletionStatus, const FStateTreeActiveStates& CompletedActiveStates);`
- L83 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime);`
- L87 _protected prototype_ `void FinishTask(const bool bSucceeded = true);` — `UFUNCTION(BlueprintCallable, Category = "StateTree", meta = (HideSelfPin = "true", DisplayName = "Finish Task"))` — Finish the task and sets it's status.
- L91 _protected prototype_ `void BroadcastDelegate(FStateTreeDelegateDispatcher Dispatcher);` — `UFUNCTION(BlueprintCallable, Category = "StateTree")` — Broadcasts the dispatcher. It will triggers bound callback (bound with BindDelegate) and bound transitions.
- L99 _protected prototype_ `void BindDelegate(const FStateTreeDelegateListener& Listener, const FStateTreeDynamicDelegate& Delegate);` — `UFUNCTION(BlueprintCallable, Category = "StateTree")` — Registers the callback to the listener. If the listener was previously registered, then unregister it first before registering it again with the new delegate callback. The listener is bound to a dispatcher in the editor.
- L103 _protected prototype_ `void UnbindDelegate(const FStateTreeDelegateListener& Listener);` — `UFUNCTION(BlueprintCallable, Category = "StateTree")` — Unregisters the callback bound to the listener.
- L109 _protected member_ `mutable FStateTreeWeakTaskRef WeakTaskRef;` — Cached task while the node is active for async execution.
- L114 _protected member_ `EStateTreeRunStatus RunStatus = EStateTreeRunStatus::Running;` — Run status when using latent EnterState and Tick
- L121 _protected member_ `uint8 bShouldStateChangeOnReselect : 1;` — `UPROPERTY(EditDefaultsOnly, Category="Default")` — If set to true, the task will receive EnterState/ExitState even if the state was previously active. Generally this should be true for action type tasks, like playing animation, and false on state like tasks like claiming a resource that is expected to be acquired on child states.
- L127 _protected member_ `uint8 bShouldCallTick : 1;` — If set to true, Tick() is called. Not ticking implies no property copy. Default true. Note: this is intentionally not a property, should be only set by C++ derived classes when the tick should not be called.
- L131 _protected member_ `uint8 bShouldCallTickOnlyOnEvents : 1;` — `UPROPERTY(EditDefaultsOnly, Category="Default")` — If set to true, Tick() is called. Default false.
- L135 _protected member_ `uint8 bShouldCopyBoundPropertiesOnTick : 1;` — `UPROPERTY(EditDefaultsOnly, Category="Default")` — If set to true, copy the values of bound properties before calling Tick(). Default true.
- L139 _protected member_ `uint8 bShouldCopyBoundPropertiesOnExitState : 1;` — `UPROPERTY(EditDefaultsOnly, Category="Default")` — If set to true, copy the values of bound properties before calling ExitState(). Default true.
- L148 _public member_ `uint8 bConsideredForCompletion : 1;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")` — True if the task is considered for completion. False if the task runs in the background without affecting the state completion.
- L152 _public member_ `uint8 bCanEditConsideredForCompletion : 1;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")` — True if the user can edit bConsideredForCompletion in the editor.
- L156 _protected member_ `uint8 bHasExitState : 1;`
- L157 _protected member_ `uint8 bHasStateCompleted : 1;`
- L158 _protected member_ `uint8 bHasLatentEnterState : 1;`
- L159 _protected member_ `uint8 bHasLatentTick : 1;`
- L161 _protected member_ `uint8 bHasEnterState_DEPRECATED : 1;` — `UE_DEPRECATED(all, "Use bHasLatentEnterState instead.")`
- L163 _protected member_ `uint8 bHasTick_DEPRECATED : 1;` — `UE_DEPRECATED(all, "Use bHasLatentTick instead.")`
- L165 _protected member_ `mutable uint8 bIsProcessingEnterStateOrTick : 1;`

#### struct `FStateTreeBlueprintTaskWrapper`  
`struct FStateTreeBlueprintTaskWrapper : public FStateTreeTaskBase`  
_L174-207_
- reflection: `USTRUCT()`
- inherits: `FStateTreeTaskBase`
- desc: Wrapper for Blueprint based Tasks.
- L178 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L183 _public prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L184 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L185 _public prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L186 _public prototype_ `virtual void StateCompleted(FStateTreeExecutionContext& Context, const EStateTreeRunStatus CompletionStatus, const FStateTreeActiveStates& CompletedActiveStates) const override;`
- L187 _public prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L189 _public prototype_ `virtual EDataValidationResult Compile(UE::StateTree::ICompileNodeContext& Context) override;`
- L190 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L191 _public prototype_ `virtual FName GetIconName() const override;`
- L192 _public prototype_ `virtual FColor GetIconColor() const override;`
- L196 _public member_ `TSubclassOf<UStateTreeTaskBlueprintBase> TaskClass;` — `UPROPERTY()`
- L199 _public member_ `uint8 TaskFlags = 0;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API STATETREEMODULE_API`
- L15 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FStateTreeDynamicDelegate);`
- L15 _prototype_ `DECLARE_DYNAMIC_DELEGATE(FStateTreeDynamicDelegate);`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Conditions/StateTreeCommonConditions.h` (Public)


#### struct `FStateTreeCompareIntConditionInstanceData`  
`struct FStateTreeCompareIntConditionInstanceData`  
_L19-28_
- reflection: `USTRUCT()`
- L24 _public member_ `int32 Left = 0;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L27 _public member_ `int32 Right = 0;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeCompareIntCondition`  
`struct FStateTreeCompareIntCondition : public FStateTreeConditionCommonBase`  
_L35-62_
- reflection: `USTRUCT(DisplayName = "Integer Compare")`
- inherits: `FStateTreeConditionCommonBase`
- desc: Condition comparing two integers.
- L39 _public typedef_ `using FInstanceDataType = FStateTreeCompareIntConditionInstanceData;`
- L41 _public prototype_ `FStateTreeCompareIntCondition() = default;`
- L42 _public function_ `explicit FStateTreeCompareIntCondition(const UE::StateTree::EComparisonOperator InOperator, const EStateTreeCompare InInverts = EStateTreeCompare::Default) : bInvert(InInverts == EStateTreeCompare::Invert) , Operator(InOperator)`
- L48 _public prototype_ `explicit FStateTreeCompareIntCondition(const EGenericAICheck InOperator, const EStateTreeCompare InInverts = EStateTreeCompare::Default);` — `UE_DEPRECATED(5.8, "Use EComparisonOperator instead.")`
- L50 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L51 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L53 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L57 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L61 _public member_ `UE::StateTree::EComparisonOperator Operator = UE::StateTree::EComparisonOperator::Equal;` — `UE_DEPRECATED_FORGAME(5.8, "The Operator type changed from EGenericAICheck to EComparisonOperator.")` — `UPROPERTY(EditAnywhere, Category = "Parameter", meta = (InvalidEnumValues = "IsTrue"))`

#### struct `FStateTreeCompareFloatConditionInstanceData`  
`struct FStateTreeCompareFloatConditionInstanceData`  
_L66-75_
- reflection: `USTRUCT()`
- L71 _public member_ `double Left = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L74 _public member_ `double Right = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeCompareFloatCondition`  
`struct FStateTreeCompareFloatCondition : public FStateTreeConditionCommonBase`  
_L82-109_
- reflection: `USTRUCT(DisplayName = "Float Compare")`
- inherits: `FStateTreeConditionCommonBase`
- desc: Condition comparing two floats.
- L86 _public typedef_ `using FInstanceDataType = FStateTreeCompareFloatConditionInstanceData;`
- L88 _public prototype_ `FStateTreeCompareFloatCondition() = default;`
- L89 _public function_ `explicit FStateTreeCompareFloatCondition(const UE::StateTree::EComparisonOperator InOperator, const EStateTreeCompare InInverts = EStateTreeCompare::Default) : bInvert(InInverts == EStateTreeCompare::Invert) , Operator(InOperator)`
- L95 _public prototype_ `explicit FStateTreeCompareFloatCondition(const EGenericAICheck InOperator, const EStateTreeCompare InInverts = EStateTreeCompare::Default);` — `UE_DEPRECATED(5.8, "Use EComparisonOperator instead.")`
- L97 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L98 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L100 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L104 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L108 _public member_ `UE::StateTree::EComparisonOperator Operator = UE::StateTree::EComparisonOperator::Equal;` — `UE_DEPRECATED_FORGAME(5.8, "The Operator type changed from EGenericAICheck to EComparisonOperator.")` — `UPROPERTY(EditAnywhere, Category = "Parameter", meta = (InvalidEnumValues = "IsTrue"))`

#### struct `FStateTreeCompareBoolConditionInstanceData`  
`struct FStateTreeCompareBoolConditionInstanceData`  
_L113-122_
- reflection: `USTRUCT()`
- L118 _public member_ `bool bLeft = false;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L121 _public member_ `bool bRight = false;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeCompareBoolCondition`  
`struct FStateTreeCompareBoolCondition : public FStateTreeConditionCommonBase`  
_L129-152_
- reflection: `USTRUCT(DisplayName = "Bool Compare")`
- inherits: `FStateTreeConditionCommonBase`
- desc: Condition comparing two booleans.
- L133 _public typedef_ `using FInstanceDataType = FStateTreeCompareBoolConditionInstanceData;`
- L135 _public prototype_ `FStateTreeCompareBoolCondition() = default;`
- L136 _public function_ `explicit FStateTreeCompareBoolCondition(const EStateTreeCompare InInverts) : bInvert(InInverts == EStateTreeCompare::Invert)`
- L140 _public function_ `FStateTreeCompareBoolCondition(const bool bInInverts) : bInvert(bInInverts)`
- L144 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L145 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L147 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L151 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeCompareEnumConditionInstanceData`  
`struct FStateTreeCompareEnumConditionInstanceData`  
_L156-165_
- reflection: `USTRUCT()`
- L161 _public member_ `FStateTreeAnyEnum Left;` — `UPROPERTY(EditAnywhere, Category = "Input", meta=(AllowAnyBinding))`
- L164 _public member_ `FStateTreeAnyEnum Right;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeCompareEnumCondition`  
`struct FStateTreeCompareEnumCondition : public FStateTreeConditionCommonBase`  
_L172-196_
- reflection: `USTRUCT(DisplayName = "Enum Compare")`
- inherits: `FStateTreeConditionCommonBase`
- desc: Condition comparing two enums.
- L176 _public typedef_ `using FInstanceDataType = FStateTreeCompareEnumConditionInstanceData;`
- L178 _public prototype_ `FStateTreeCompareEnumCondition() = default;`
- L179 _public function_ `explicit FStateTreeCompareEnumCondition(const EStateTreeCompare InInverts) : bInvert(InInverts == EStateTreeCompare::Invert)`
- L183 _public function_ `FStateTreeCompareEnumCondition(const bool bInInverts) : bInvert(bInInverts)`
- L187 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L188 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L190 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L191 _public prototype_ `virtual void OnBindingChanged(const FGuid& ID, FStateTreeDataView InstanceData, const FPropertyBindingPath& SourcePath, const FPropertyBindingPath& TargetPath, const IStateTreeBindingLookup& BindingLookup) override;`
- L195 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeCompareDistanceConditionInstanceData`  
`struct FStateTreeCompareDistanceConditionInstanceData`  
_L200-212_
- reflection: `USTRUCT()`
- L205 _public member_ `FVector Source;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L208 _public member_ `FVector Target;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L211 _public member_ `double Distance = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeCompareDistanceCondition`  
`struct FStateTreeCompareDistanceCondition : public FStateTreeConditionCommonBase`  
_L219-246_
- reflection: `USTRUCT(DisplayName = "Distance Compare")`
- inherits: `FStateTreeConditionCommonBase`
- desc: Condition comparing distance between two vectors.
- L223 _public typedef_ `using FInstanceDataType = FStateTreeCompareDistanceConditionInstanceData;`
- L225 _public prototype_ `FStateTreeCompareDistanceCondition() = default;`
- L226 _public function_ `explicit FStateTreeCompareDistanceCondition(const UE::StateTree::EComparisonOperator InOperator, const EStateTreeCompare InInverts = EStateTreeCompare::Default) : bInvert(InInverts == EStateTreeCompare::Invert) , Operator(InOperator)`
- L232 _public prototype_ `explicit FStateTreeCompareDistanceCondition(const EGenericAICheck InOperator, const EStateTreeCompare InInverts = EStateTreeCompare::Default);` — `UE_DEPRECATED(5.8, "Use EComparisonOperator instead.")`
- L234 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L235 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L237 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L241 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Condition")`
- L245 _public member_ `UE::StateTree::EComparisonOperator Operator = UE::StateTree::EComparisonOperator::Equal;` — `UE_DEPRECATED_FORGAME(5.8, "The Operator type changed from EGenericAICheck to EComparisonOperator.")` — `UPROPERTY(EditAnywhere, Category = "Condition", meta = (InvalidEnumValues = "IsTrue"))`

#### struct `FStateTreeCompareNameConditionInstanceData`  
`struct FStateTreeCompareNameConditionInstanceData`  
_L249-258_
- reflection: `USTRUCT()`
- L254 _public member_ `FName Left = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L257 _public member_ `FName Right = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeCompareNameCondition`  
`struct FStateTreeCompareNameCondition : public FStateTreeConditionCommonBase`  
_L265-288_
- reflection: `USTRUCT(DisplayName = "Name Compare")`
- inherits: `FStateTreeConditionCommonBase`
- desc: Condition comparing two FNames.
- L269 _public typedef_ `using FInstanceDataType = FStateTreeCompareNameConditionInstanceData;`
- L271 _public prototype_ `FStateTreeCompareNameCondition() = default;`
- L272 _public function_ `explicit FStateTreeCompareNameCondition(const EStateTreeCompare InInverts) : bInvert(InInverts == EStateTreeCompare::Invert)`
- L276 _public function_ `FStateTreeCompareNameCondition(const bool bInInverts) : bInvert(bInInverts)`
- L280 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L281 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L283 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L287 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeRandomConditionInstanceData`  
`struct FStateTreeRandomConditionInstanceData`  
_L292-297_
- reflection: `USTRUCT()`
- L296 _public member_ `float Threshold = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Parameter", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))`

#### struct `FStateTreeRandomCondition`  
`struct FStateTreeRandomCondition : public FStateTreeConditionCommonBase`  
_L304-317_
- reflection: `USTRUCT(DisplayName = "Random")`
- inherits: `FStateTreeConditionCommonBase`
- desc: Random condition
- L308 _public typedef_ `using FInstanceDataType = FStateTreeRandomConditionInstanceData;`
- L310 _public prototype_ `FStateTreeRandomCondition() = default;`
- L312 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L313 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L315 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API STATETREEMODULE_API`
- L29 _prototype_ `UE_STATETREE_ZEROED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA(FStateTreeCompareIntConditionInstanceData);`
- L76 _prototype_ `UE_STATETREE_ZEROED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA(FStateTreeCompareFloatConditionInstanceData);`
- L123 _prototype_ `UE_STATETREE_ZEROED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA(FStateTreeCompareBoolConditionInstanceData);`
- L166 _prototype_ `UE_STATETREE_CONSTRUCTED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA(FStateTreeCompareEnumConditionInstanceData);`
- L213 _prototype_ `UE_STATETREE_ZEROED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA(FStateTreeCompareDistanceConditionInstanceData);`
- L259 _prototype_ `UE_STATETREE_CONSTRUCTED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA(FStateTreeCompareNameConditionInstanceData);`
- L298 _prototype_ `UE_STATETREE_CONSTRUCTED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA(FStateTreeRandomConditionInstanceData);`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Conditions/StateTreeConditionHelpers.h` (Public)


#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API STATETREEMODULE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace StateTree` (scope `UE`)
- L15 _namespace_ `namespace Conditions` (scope `UE::StateTree`)
- L18 _function_ `template<typename T> bool CompareNumbers(const T Left, const T Right, const EComparisonOperator Operator)` (scope `UE::StateTree::Conditions`)
- L41 _prototype_ `extern EComparisonOperator GenericAICheckToComparisonOperator(EGenericAICheck Operator);` (scope `UE::StateTree::Conditions`) — `UE_DEPRECATED(5.8, "Use EComparisonOperator instead.")`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Conditions/StateTreeGameplayTagConditions.h` (Public)


#### struct `FGameplayTagSingleMatchConditionInstanceData`  
`struct FGameplayTagSingleMatchConditionInstanceData`  
_L11-22_
- reflection: `USTRUCT()`
- L17 _public member_ `FGameplayTag Left;` — `UPROPERTY(EditAnywhere, Category = Input)` — First tag to compare.
- L21 _public member_ `FGameplayTag Right;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Second tag to compare.

#### struct `FGameplayTagSingleMatchCondition`  
`struct FGameplayTagSingleMatchCondition : public FStateTreeConditionCommonBase`  
_L36-63_
- reflection: `USTRUCT(DisplayName="Matches Tag", Category="Gameplay Tags")`
- inherits: `FStateTreeConditionCommonBase`
- desc: MatchesTag condition Succeeds if the tag matches the specified tag. Condition can be used with multiple configurations: Does Tag "A.1" match Tag "A" ? exact match 'false' will SUCCEED exact match 'true' will FAIL Does Tag "A" match Tag "A.1" ? always returns false
- L40 _public typedef_ `using FInstanceDataType = FGameplayTagSingleMatchConditionInstanceData;`
- L42 _public prototype_ `FGameplayTagSingleMatchCondition() = default;`
- L44 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L45 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L47 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L48 _public function_ `virtual FName GetIconName() const override`
- L52 _public function_ `virtual FColor GetIconColor() const override`
- L59 _public member_ `bool bExactMatch = false;` — `UPROPERTY(EditAnywhere, Category = Condition)` — If true, the tag has to match exactly, if false then the tag may match its parent tags
- L62 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = Condition)`

#### struct `FGameplayTagMatchConditionInstanceData`  
`struct FGameplayTagMatchConditionInstanceData`  
_L67-78_
- reflection: `USTRUCT()`
- L73 _public member_ `FGameplayTagContainer TagContainer;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Container to check for the tag.
- L77 _public member_ `FGameplayTag Tag;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Tag to check for in the container.

#### struct `FGameplayTagMatchCondition`  
`struct FGameplayTagMatchCondition : public FStateTreeConditionCommonBase`  
_L90-117_
- reflection: `USTRUCT(DisplayName="Has Tag", Category="Gameplay Tags")`
- inherits: `FStateTreeConditionCommonBase`
- desc: HasTag condition Succeeds if the tag container has the specified tag. Condition can be used with multiple configurations: Does TagContainer {"A.1"} has Tag "A" ? exact match 'false' will SUCCEED exact match 'true' will FAIL
- L94 _public typedef_ `using FInstanceDataType = FGameplayTagMatchConditionInstanceData;`
- L96 _public prototype_ `FGameplayTagMatchCondition() = default;`
- L98 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L99 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L101 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L102 _public function_ `virtual FName GetIconName() const override`
- L106 _public function_ `virtual FColor GetIconColor() const override`
- L113 _public member_ `bool bExactMatch = false;` — `UPROPERTY(EditAnywhere, Category = Condition)` — If true, the tag has to be exactly present, if false then TagContainer will include its parent tags while matching
- L116 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = Condition)`

#### struct `FGameplayTagContainerMatchConditionInstanceData`  
`struct FGameplayTagContainerMatchConditionInstanceData`  
_L121-132_
- reflection: `USTRUCT()`
- L127 _public member_ `FGameplayTagContainer TagContainer;` — `UPROPERTY(EditAnywhere, Category = Input)` — Container to check if it matches any of the tags in the other container.
- L131 _public member_ `FGameplayTagContainer OtherContainer;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Container to check against.

#### struct `FGameplayTagContainerMatchCondition`  
`struct FGameplayTagContainerMatchCondition : public FStateTreeConditionCommonBase`  
_L161-191_
- reflection: `USTRUCT(DisplayName="Has Tags", Category="Gameplay Tags")`
- inherits: `FStateTreeConditionCommonBase`
- desc: HasAnyTags / HasAllTags condition Succeeds  if the specified tag container has ANY or ALL of the tags in the other container. Condition can be used with multiple configurations: Has ANY Tags: exact match 'false': TagContainer {"A.1"} has any of OtherContainer {"A","B"} will SUCCEED TagContainer {"A"} has any of OtherContainer {"A.1","B"} will FAIL exact match 'true': TagContainer {"A","B"} has any of OtherContainer {"A.1"} will FAIL If TagContainer is empty/invalid it will always fail. Has ALL Tags: exact match 'false': TagContainer {"A.1","B.1"} has all of OtherContainer {"A","B"} will SUCCEED TagContainer {"A","B"} has all of OtherContainer {"A.1","B.1"} will FAIL exact match 'true': TagContainer {"A.1","B.1"} has all of OtherContainer {"A","B"} will FAIL If TagContainer is empty/invalid it will always SUCCEED, because there were no failed checks.
- L165 _public typedef_ `using FInstanceDataType = FGameplayTagContainerMatchConditionInstanceData ;`
- L167 _public prototype_ `FGameplayTagContainerMatchCondition() = default;`
- L169 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L170 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L172 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L173 _public function_ `virtual FName GetIconName() const override`
- L177 _public function_ `virtual FColor GetIconColor() const override`
- L183 _public member_ `EGameplayContainerMatchType MatchType = EGameplayContainerMatchType::Any;` — `UPROPERTY(EditAnywhere, Category = Condition)`
- L187 _public member_ `bool bExactMatch = false;` — `UPROPERTY(EditAnywhere, Category = Condition)` — If true, the tag has to be exactly present, if false then TagContainer will include it's parent tags while matching
- L190 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = Condition)`

#### struct `FGameplayTagQueryConditionInstanceData`  
`struct FGameplayTagQueryConditionInstanceData`  
_L195-202_
- reflection: `USTRUCT()`
- L201 _public member_ `FGameplayTagContainer TagContainer;` — `UPROPERTY(EditAnywhere, Category = Input)` — Container that needs to match the query.

#### struct `FGameplayTagQueryCondition`  
`struct FGameplayTagQueryCondition : public FStateTreeConditionCommonBase`  
_L209-236_
- reflection: `USTRUCT(DisplayName="Does Container Match Tag Query", Category="Gameplay Tags")`
- inherits: `FStateTreeConditionCommonBase`
- desc: DoesContainerMatchTagQuery condition Succeeds if the specified tag container matches the given Tag Query.
- L213 _public typedef_ `using FInstanceDataType = FGameplayTagQueryConditionInstanceData;`
- L215 _public prototype_ `FGameplayTagQueryCondition() = default;`
- L217 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L218 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L220 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L221 _public function_ `virtual FName GetIconName() const override`
- L225 _public function_ `virtual FColor GetIconColor() const override`
- L232 _public member_ `FGameplayTagQuery TagQuery;` — `UPROPERTY(EditAnywhere, Category = Condition)` — Query to match against
- L235 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = Condition)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Conditions/StateTreeObjectConditions.h` (Public)


#### struct `FStateTreeObjectIsValidConditionInstanceData`  
`struct FStateTreeObjectIsValidConditionInstanceData`  
_L11-17_
- reflection: `USTRUCT()`
- L16 _public member_ `TObjectPtr<UObject> Object = nullptr;` — `UPROPERTY(EditAnywhere, Category = Input)`

#### struct `FStateTreeObjectIsValidCondition`  
`struct FStateTreeObjectIsValidCondition : public FStateTreeConditionCommonBase`  
_L23-46_
- reflection: `USTRUCT(DisplayName = "Object Is Valid", Category = "Object")`
- inherits: `FStateTreeConditionCommonBase`
- desc: Condition testing if specified object is valid.
- L27 _public typedef_ `using FInstanceDataType = FStateTreeObjectIsValidConditionInstanceData;`
- L29 _public prototype_ `FStateTreeObjectIsValidCondition() = default;`
- L30 _public function_ `explicit FStateTreeObjectIsValidCondition(const EStateTreeCompare InInverts) : bInvert(InInverts == EStateTreeCompare::Invert)`
- L34 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L38 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L41 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L45 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FStateTreeObjectEqualsConditionInstanceData`  
`struct FStateTreeObjectEqualsConditionInstanceData`  
_L50-59_
- reflection: `USTRUCT()`
- L55 _public member_ `TObjectPtr<UObject> Left = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L58 _public member_ `TObjectPtr<UObject> Right = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeObjectEqualsCondition`  
`struct FStateTreeObjectEqualsCondition : public FStateTreeConditionCommonBase`  
_L65-88_
- reflection: `USTRUCT(DisplayName = "Object Equals", Category = "Object")`
- inherits: `FStateTreeConditionCommonBase`
- desc: Condition testing if two object pointers point to the same object.
- L69 _public typedef_ `using FInstanceDataType = FStateTreeObjectEqualsConditionInstanceData;`
- L71 _public prototype_ `FStateTreeObjectEqualsCondition() = default;`
- L72 _public function_ `explicit FStateTreeObjectEqualsCondition(const EStateTreeCompare InInverts) : bInvert(InInverts == EStateTreeCompare::Invert)`
- L76 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L80 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L83 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L87 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeObjectIsChildOfClassConditionInstanceData`  
`struct FStateTreeObjectIsChildOfClassConditionInstanceData`  
_L92-101_
- reflection: `USTRUCT()`
- L97 _public member_ `TObjectPtr<UObject> Object = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L100 _public member_ `TObjectPtr<UClass> Class = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FStateTreeObjectIsChildOfClassCondition`  
`struct FStateTreeObjectIsChildOfClassCondition : public FStateTreeConditionCommonBase`  
_L107-130_
- reflection: `USTRUCT(DisplayName = "Object Class Is", Category = "Object")`
- inherits: `FStateTreeConditionCommonBase`
- desc: Condition testing if object is child of specified class.
- L111 _public typedef_ `using FInstanceDataType = FStateTreeObjectIsChildOfClassConditionInstanceData;`
- L113 _public prototype_ `FStateTreeObjectIsChildOfClassCondition() = default;`
- L114 _public function_ `explicit FStateTreeObjectIsChildOfClassCondition(const EStateTreeCompare InInverts) : bInvert(InInverts == EStateTreeCompare::Invert)`
- L118 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L122 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L125 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L129 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Considerations/StateTreeCommonConsiderations.h` (Public)


#### struct `FStateTreeConstantConsiderationInstanceData`  
`struct FStateTreeConstantConsiderationInstanceData`  
_L13-19_
- reflection: `USTRUCT()`
- L18 _public member_ `float Constant = 0.f;` — `UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 1, UIMin = 0, UIMax = 1), Category = "Default")`

#### struct `FStateTreeConstantConsideration`  
`struct FStateTreeConstantConsideration: public FStateTreeConsiderationCommonBase`  
_L25-42_
- reflection: `USTRUCT(DisplayName = "Constant")`
- inherits: `FStateTreeConsiderationCommonBase`
- desc: Consideration using a constant as its score.
- L29 _public typedef_ `using FInstanceDataType = FStateTreeConstantConsiderationInstanceData;`
- L32 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L34 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L40 _protected prototype_ `virtual float GetScore(FStateTreeExecutionContext& Context) const override;`

#### struct `FStateTreeConsiderationResponseCurve`  
`struct FStateTreeConsiderationResponseCurve`  
_L45-70_
- reflection: `USTRUCT()`
- L54 _public function_ `float Evaluate(float NormalizedInput) const` — Evaluate the output value from curve @param NormalizedInput the normalized input value to the response curve @return The output value. If the curve is not set, will simply return NormalizedInput.
- L69 _public member_ `FRuntimeFloatCurve CurveInfo;` — `UPROPERTY(EditAnywhere, Category = Default, DisplayName = "Curve")` — Curve used to output the final score for the Consideration.

#### struct `FStateTreeFloatInputConsiderationInstanceData`  
`struct FStateTreeFloatInputConsiderationInstanceData`  
_L73-82_
- reflection: `USTRUCT()`
- L78 _public member_ `float Input = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L81 _public member_ `FFloatInterval Interval = FFloatInterval(0.f, 1.f);` — `UPROPERTY(EditAnywhere, DisplayName = "InputRange", Category = "Parameter")`

#### struct `FStateTreeFloatInputConsideration`  
`struct FStateTreeFloatInputConsideration : public FStateTreeConsiderationCommonBase`  
_L88-109_
- reflection: `USTRUCT(DisplayName = "Float Input")`
- inherits: `FStateTreeConsiderationCommonBase`
- desc: Consideration using a Float as input to the response curve.
- L92 _public typedef_ `using FInstanceDataType = FStateTreeFloatInputConsiderationInstanceData;`
- L95 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L97 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L103 _protected prototype_ `virtual float GetScore(FStateTreeExecutionContext& Context) const override;`
- L108 _public member_ `FStateTreeConsiderationResponseCurve ResponseCurve;` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### struct `FStateTreeEnumValueScorePair`  
`struct FStateTreeEnumValueScorePair`  
_L112-136_
- reflection: `USTRUCT()`
- L116 _public function_ `bool operator==(const FStateTreeEnumValueScorePair& RHS) const`
- L121 _public function_ `bool operator!=(const FStateTreeEnumValueScorePair& RHS) const`
- L128 _public member_ `FName EnumName;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L132 _public member_ `int64 EnumValue = 0;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L135 _public member_ `float Score = 0.f;` — `UPROPERTY(EditAnywhere, Category = Default, meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 1.0, ClampMax = 1.0))`

#### struct `FStateTreeEnumValueScorePairs`  
`struct FStateTreeEnumValueScorePairs`  
_L139-163_
- reflection: `USTRUCT()`
- L145 _public member_ `TObjectPtr<const UEnum> Enum;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L149 _public member_ `TArray<FStateTreeEnumValueScorePair> Data;` — `UPROPERTY(EditAnywhere, Category = Default, DisplayName = EnumValueScorePairs)`
- L153 _public function_ `void Initialize(const UEnum* NewEnum)` — Initializes the class to specific enum.

#### struct `FStateTreeEnumInputConsiderationInstanceData`  
`struct FStateTreeEnumInputConsiderationInstanceData`  
_L166-172_
- reflection: `USTRUCT()`
- L171 _public member_ `FStateTreeAnyEnum Input;` — `UPROPERTY(EditAnywhere, Category = "Input", meta=(AllowAnyBinding))`

#### struct `FStateTreeEnumInputConsideration`  
`struct FStateTreeEnumInputConsideration : public FStateTreeConsiderationCommonBase`  
_L175-198_
- reflection: `USTRUCT(DisplayName = "Enum Input")`
- inherits: `FStateTreeConsiderationCommonBase`
- L179 _public typedef_ `using FInstanceDataType = FStateTreeEnumInputConsiderationInstanceData;`
- L182 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L184 _public prototype_ `virtual EDataValidationResult Compile(UE::StateTree::ICompileNodeContext& Context) override;`
- L185 _public prototype_ `virtual void OnBindingChanged(const FGuid& ID, FStateTreeDataView InstanceData, const FPropertyBindingPath& SourcePath, const FPropertyBindingPath& TargetPath, const IStateTreeBindingLookup& BindingLookup) override;`
- L187 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L193 _protected prototype_ `virtual float GetScore(FStateTreeExecutionContext& Context) const override;`
- L197 _protected member_ `FStateTreeEnumValueScorePairs EnumValueScorePairs;` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Debugger/IStateTreeTraceProvider.h` (Public)


#### class `IStateTreeTraceProvider`  
`class IStateTreeTraceProvider : public TraceServices::IProvider`  
_L15-53_
- inherits: `TraceServices::IProvider`
- L18 _public typedef_ `typedef TraceServices::ITimeline<FStateTreeTraceEventVariantType> FEventsTimeline;`
- L25 _public prototype_ `virtual TSharedPtr<const UE::StateTreeDebugger::FInstanceDescriptor> GetInstanceDescriptor(const FStateTreeInstanceDebugId InstanceId) const = 0;` — Return instance descriptor associated to the given instance id. @param InstanceId Id of a specific instance to get the descriptor for. @return Shared pointer to the descriptor if the specified instance was found.
- L31 _public prototype_ `virtual void GetInstances(TArray<const TSharedRef<const UE::StateTreeDebugger::FInstanceDescriptor>>& OutInstances) const = 0;` — Return all instances with events in the traces. @param OutInstances List of all instances with events in the traces regardless if they are active or not.
- L34 _public function_ `virtual void GetInstances(TArray<UE::StateTreeDebugger::FInstanceDescriptor>& OutInstances) const final` — `UE_DEPRECATED(5.7, "Use the version with TSharedRef array instead")`
- L44 _public prototype_ `virtual bool ReadTimelines(const FStateTreeInstanceDebugId InstanceId, TFunctionRef<void(const FStateTreeInstanceDebugId ProcessedInstanceId, const FEventsTimeline&)> Callback) const = 0;` — Execute given function receiving an event timeline for a given instance or all timelines if instance not specified. @param InstanceId Id of a specific instance to get the timeline for; could be an FStateTreeInstanceDebugId::Invalid to go through all timelines @param Callback Function called for timeline(s) matching the provided Id @return True if the specified instance was found for a given Id or at least one timeline was found when no specific Id is provided.
- L52 _public prototype_ `virtual bool ReadTimelines(const UStateTree& StateTree, TFunctionRef<void(const FStateTreeInstanceDebugId ProcessedInstanceId, const FEventsTimeline&)> Callback) const = 0;` — Execute given function receiving an event timeline for all timelines matching a given asset. @param StateTree Asset that must be used by the instance to be processed @param Callback Function called for timeline(s) matching the provided asset @return True if the specified instance was found for a given Id or at least one timeline was found when no specific Id is provided.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace StateTreeDebugger` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Debugger/StateTreeDebug.h` (Public)


#### struct `UE::StateTree::Debug::FNodeReference`  
`struct FNodeReference`  
_L90-95_
- L92 _public prototype_ `explicit FNodeReference(TNotNull<const UStateTree*> InStateTree, FStateTreeIndex16 InNodeIndex);`
- L93 _public member_ `TNotNull<const UStateTree*> StateTree;`
- L94 _public member_ `FStateTreeIndex16 Index;`

#### struct `UE::StateTree::Debug::FNodeDelegateArgs`  
`struct FNodeDelegateArgs`  
_L97-101_
- L99 _public member_ `FNodeReference Node;`
- L100 _public member_ `FGuid NodeId;`

#### struct `UE::StateTree::Debug::FEventSentDelegateArgs`  
`struct FEventSentDelegateArgs`  
_L103-109_
- L105 _public member_ `TNotNull<const UStateTree*> StateTree;`
- L106 _public member_ `FGameplayTag Tag;`
- L107 _public member_ `FConstStructView Payload;`
- L108 _public member_ `FName Origin;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_STATETREE_DEBUG_CONDITION_ENTER_STATE(InCtx, InStateTree, InNodeIndex) ::UE::StateTree::Debug::ConditionEnterState(*(InCtx), ::UE::StateTree::Debug::FNodeReference((InStateTree), FStateTreeIndex16(InNodeIndex)))`
- L18 _macro_ `#define UE_STATETREE_DEBUG_CONDITION_TEST_CONDITION(InCtx, InStateTree, InNodeIndex) ::UE::StateTree::Debug::ConditionTest(*(InCtx), ::UE::StateTree::Debug::FNodeReference((InStateTree), FStateTreeIndex16(InNodeIndex)))`
- L19 _macro_ `#define UE_STATETREE_DEBUG_CONDITION_EXIT_STATE(InCtx, InStateTree, InNodeIndex) ::UE::StateTree::Debug::ConditionExitState(*(InCtx), ::UE::StateTree::Debug::FNodeReference((InStateTree), FStateTreeIndex16(InNodeIndex)))`
- L21 _macro_ `#define UE_STATETREE_DEBUG_EVALUATOR_ENTER_TREE(InCtx, InStateTree, InNodeIndex) ::UE::StateTree::Debug::EvaluatorEnterTree(*(InCtx), ::UE::StateTree::Debug::FNodeReference((InStateTree), FStateTreeIndex16(InNodeIndex)))`
- L22 _macro_ `#define UE_STATETREE_DEBUG_EVALUATOR_TICK(InCtx, InStateTree, InNodeIndex) ::UE::StateTree::Debug::EvaluatorTick(*(InCtx), ::UE::StateTree::Debug::FNodeReference((InStateTree), FStateTreeIndex16(InNodeIndex)))`
- L23 _macro_ `#define UE_STATETREE_DEBUG_EVALUATOR_EXIT_TREE(InCtx, InStateTree, InNodeIndex) ::UE::StateTree::Debug::EvaluatorExitTree(*(InCtx), ::UE::StateTree::Debug::FNodeReference((InStateTree), FStateTreeIndex16(InNodeIndex)))`
- L25 _macro_ `#define UE_STATETREE_DEBUG_TASK_ENTER_STATE(InCtx, InStateTree, InNodeIndex) ::UE::StateTree::Debug::TaskEnterState(*(InCtx), ::UE::StateTree::Debug::FNodeReference((InStateTree), FStateTreeIndex16(InNodeIndex)))`
- L26 _macro_ `#define UE_STATETREE_DEBUG_TASK_TICK(InCtx, InStateTree, InNodeIndex) ::UE::StateTree::Debug::TaskTick(*(InCtx), ::UE::StateTree::Debug::FNodeReference((InStateTree), FStateTreeIndex16(InNodeIndex)))`
- L27 _macro_ `#define UE_STATETREE_DEBUG_TASK_EXIT_STATE(InCtx, InStateTree, InNodeIndex) ::UE::StateTree::Debug::TaskExitState(*(InCtx), ::UE::StateTree::Debug::FNodeReference((InStateTree), FStateTreeIndex16(InNodeIndex)))`
- L29 _macro_ `#define UE_STATETREE_DEBUG_STATE_UTILITY_EVALUATED(InCtx, InStateHandled, Score) ::UE::StateTree::Debug::StateUtilityEvaluated(*(InCtx), InStateHandled, Score)`
- L31 _macro_ `#define UE_STATETREE_DEBUG_SEND_EVENT(InCtx, InStateTree, InTag, InPayload, InOrigin) ::UE::StateTree::Debug::EventSent(*(InCtx), InStateTree, InTag, InPayload, InOrigin)`
- L32 _macro_ `#define UE_STATETREE_DEBUG_EVENT_CONSUMED(InExecutionContextPtr, Event) ::UE::StateTree::Debug::EventConsumed(*(InExecutionContextPtr), Event)`
- L34 _macro_ `#define UE_STATETREE_DEBUG_ENTER_PHASE(InCtx, InPhase) \`
- L38 _macro_ `#define UE_STATETREE_DEBUG_EXIT_PHASE(InCtx, InPhase) \`
- L42 _macro_ `#define UE_STATETREE_DEBUG_STATE_EVENT(InCtx, InStateHandle, InEventType) \`
- L46 _macro_ `#define UE_STATETREE_DEBUG_TRANSITION_EVENT(InCtx, InTransitionSource, InEventType) \`
- L50 _macro_ `#define UE_STATETREE_DEBUG_LOG_EVENT(InCtx, InLogVerbosity, InFormat, ...) TRACE_STATETREE_LOG_EVENT((InCtx), InLogVerbosity, InFormat, ##__VA_ARGS__)`
- L51 _macro_ `#define UE_STATETREE_DEBUG_CONDITION_EVENT(InCtx, InIndex, InDataView, InEventType) TRACE_STATETREE_CONDITION_EVENT((InCtx), FStateTreeIndex16(InIndex), (InDataView), (InEventType));`
- L52 _macro_ `#define UE_STATETREE_DEBUG_INSTANCE_EVENT(InCtx, InEventType) TRACE_STATETREE_INSTANCE_EVENT((InCtx), (InEventType));`
- L53 _macro_ `#define UE_STATETREE_DEBUG_INSTANCE_FRAME_EVENT(InCtx, InFrame) TRACE_STATETREE_INSTANCE_FRAME_EVENT((InCtx), (InFrame));`
- L54 _macro_ `#define UE_STATETREE_DEBUG_ACTIVE_STATES_EVENT(InCtx, InActiveFrames) TRACE_STATETREE_ACTIVE_STATES_EVENT((InCtx), InActiveFrames);`
- L55 _macro_ `#define UE_STATETREE_DEBUG_TASK_EVENT(InCtx, InIndex, InDataView, InEventType, InStatus) TRACE_STATETREE_TASK_EVENT((InCtx), FStateTreeIndex16(InIndex), (InDataView), (InEventType), (InStatus));`
- L56 _macro_ `#define UE_STATETREE_DEBUG_EVALUATOR_EVENT(InCtx, InIndex, InDataView, InEventType) TRACE_STATETREE_EVALUATOR_EVENT((InCtx), FStateTreeIndex16(InIndex), (InDataView), (InEventType));`
- L58 _macro_ `#define UE_STATETREE_ID_NAME UE_JOIN(InstanceId,__LINE__) \`
- L61 _macro_ `#define UE_STATETREE_DEBUG_SCOPED_PHASE(InCtx, InPhase) \` — Scope based macros captures the instance ID since it might not be accessible when exiting the scope
- L70 _macro_ `#define UE_STATETREE_DEBUG_SCOPED_STATE(InCtx, InStateHandle) \` — Scope based macros captures the instance ID since it might not be accessible when exiting the scope
- L79 _macro_ `#define UE_STATETREE_DEBUG_SCOPED_STATE_PHASE(InCtx, InStateHandle, InPhase) \` — Scope based macros captures the instance ID since it might not be accessible when exiting the scope
- L88 _namespace_ `namespace UE`
- L88 _namespace_ `namespace StateTree` (scope `UE`)
- L88 _namespace_ `namespace Debug` (scope `UE::StateTree`)
- L111 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FEventSentDelegate, const FStateTreeMinimalExecutionContext& ExecutionContext, const FEventSentDelegateArgs& EventSentArgs);`
- L111 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FEventSentDelegate, const FStateTreeMinimalExecutionContext& ExecutionContext, const FEventSentDelegateArgs& EventSentArgs);` (scope `UE::StateTree::Debug`)
- L112 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FEventConsumedDelegate, const FStateTreeExecutionContext& ExecutionContext, const FStateTreeSharedEvent& Event);`
- L112 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FEventConsumedDelegate, const FStateTreeExecutionContext& ExecutionContext, const FStateTreeSharedEvent& Event);` (scope `UE::StateTree::Debug`)
- L113 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FNodeDelegate, const FStateTreeExecutionContext&, FNodeDelegateArgs);`
- L113 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FNodeDelegate, const FStateTreeExecutionContext&, FNodeDelegateArgs);` (scope `UE::StateTree::Debug`)
- L114 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FPhaseDelegate, const FStateTreeExecutionContext&, EStateTreeUpdatePhase, FStateTreeStateHandle);`
- L114 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FPhaseDelegate, const FStateTreeExecutionContext&, EStateTreeUpdatePhase, FStateTreeStateHandle);` (scope `UE::StateTree::Debug`)
- L115 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FStateDelegate, const FStateTreeExecutionContext&, FStateTreeStateHandle, EStateTreeTraceEventType);`
- L115 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FStateDelegate, const FStateTreeExecutionContext&, FStateTreeStateHandle, EStateTreeTraceEventType);` (scope `UE::StateTree::Debug`)
- L116 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FTransitionDelegate, const FStateTreeExecutionContext&, const FStateTreeTransitionSource&, EStateTreeTraceEventType);`
- L116 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FTransitionDelegate, const FStateTreeExecutionContext&, const FStateTreeTransitionSource&, EStateTreeTraceEventType);` (scope `UE::StateTree::Debug`)
- L117 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FStateUtilityEvaluatedDelegate, const FStateTreeExecutionContext&, FStateTreeStateHandle, float);`
- L117 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FStateUtilityEvaluatedDelegate, const FStateTreeExecutionContext&, FStateTreeStateHandle, float);` (scope `UE::StateTree::Debug`)
- L119 _prototype_ `void ConditionEnterState(const FStateTreeExecutionContext& ExecutionContext, FNodeReference Node);` (scope `UE::StateTree::Debug`)
- L120 _prototype_ `void ConditionTest(const FStateTreeExecutionContext& ExecutionContext, FNodeReference Node);` (scope `UE::StateTree::Debug`)
- L121 _prototype_ `void ConditionExitState(const FStateTreeExecutionContext& ExecutionContext, FNodeReference Node);` (scope `UE::StateTree::Debug`)
- L123 _prototype_ `void EvaluatorEnterTree(const FStateTreeExecutionContext& ExecutionContext, FNodeReference Node);` (scope `UE::StateTree::Debug`)
- L124 _prototype_ `void EvaluatorTick(const FStateTreeExecutionContext& ExecutionContext, FNodeReference Node);` (scope `UE::StateTree::Debug`)
- L125 _prototype_ `void EvaluatorExitTree(const FStateTreeExecutionContext& ExecutionContext, FNodeReference Node);` (scope `UE::StateTree::Debug`)
- L127 _prototype_ `void TaskEnterState(const FStateTreeExecutionContext& ExecutionContext, FNodeReference Node);` (scope `UE::StateTree::Debug`)
- L128 _prototype_ `void TaskTick(const FStateTreeExecutionContext& ExecutionContext, FNodeReference Node);` (scope `UE::StateTree::Debug`)
- L129 _prototype_ `void TaskExitState(const FStateTreeExecutionContext& ExecutionContext, FNodeReference Node);` (scope `UE::StateTree::Debug`)
- L131 _prototype_ `void StateUtilityEvaluated(const FStateTreeExecutionContext& ExecutionContext, FStateTreeStateHandle StateHandle, float Score);` (scope `UE::StateTree::Debug`)
- L133 _prototype_ `void EventSent(const FStateTreeMinimalExecutionContext& ExecutionContext, TNotNull<const UStateTree*> StateTree, FGameplayTag Tag, FConstStructView Payload, FName Origin);` (scope `UE::StateTree::Debug`)
- L134 _prototype_ `void EventConsumed(const FStateTreeExecutionContext& ExecutionContext, const FStateTreeSharedEvent& Event);` (scope `UE::StateTree::Debug`)
- L136 _prototype_ `void EnterPhase(const FStateTreeExecutionContext& ExecutionContext, EStateTreeUpdatePhase Phase, FStateTreeStateHandle StateHandle);` (scope `UE::StateTree::Debug`)
- L137 _prototype_ `void ExitPhase(const FStateTreeExecutionContext& ExecutionContext, EStateTreeUpdatePhase Phase, FStateTreeStateHandle StateHandle);` (scope `UE::StateTree::Debug`)
- L139 _prototype_ `void StateEvent(const FStateTreeExecutionContext& ExecutionContext, FStateTreeStateHandle StateHandle, EStateTreeTraceEventType EventType);` (scope `UE::StateTree::Debug`)
- L141 _prototype_ `void TransitionEvent(const FStateTreeExecutionContext& ExecutionContext, const FStateTreeTransitionSource& TransitionSource, EStateTreeTraceEventType EventType);` (scope `UE::StateTree::Debug`)
- L148 _externvar_ `extern FNodeDelegate OnConditionEnterState_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for when a condition activates. @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L155 _externvar_ `extern FNodeDelegate OnTestCondition_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for before a condition is tested. @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L162 _externvar_ `extern FNodeDelegate OnConditionExitState_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for when a condition deactivates. @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L169 _externvar_ `extern FNodeDelegate OnEvaluatorEnterTree_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for when a evaluator activates. @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L176 _externvar_ `extern FNodeDelegate OnTickEvaluator_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for before an evaluator ticks. @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L183 _externvar_ `extern FNodeDelegate OnEvaluatorExitTree_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for when a evaluator deactivates. @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L190 _externvar_ `extern FNodeDelegate OnTaskEnterState_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for when a task activates. @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L197 _externvar_ `extern FNodeDelegate OnTickTask_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback executed before a task ticks. @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L204 _externvar_ `extern FNodeDelegate OnTaskExitState_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for when a task deactivates. @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L211 _externvar_ `extern FPhaseDelegate OnBeginUpdatePhase_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for when entering an update phase (global to the tree or specific to a state). @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L218 _externvar_ `extern FPhaseDelegate OnEndUpdatePhase_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for when exiting an update phase (global to the tree or specific to a state). @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L225 _externvar_ `extern FStateDelegate OnStateEvent_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback when an action related to a state is executing (e.g., entering, exiting, selecting, etc.). @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L232 _externvar_ `extern FTransitionDelegate OnTransitionEvent_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback when an action related to a transition is executing (e.g., requesting, evaluating, etc.). @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L239 _externvar_ `extern FEventSentDelegate OnEventSent_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for when an event is sent. @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L246 _externvar_ `extern FEventConsumedDelegate OnEventConsumed_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for when an event is consumed. @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L253 _externvar_ `extern FStateUtilityEvaluatedDelegate OnStateUtilityEvaluated_AnyThread;` (scope `UE::StateTree::Debug`) — Debugging callback for when an utility score is calculated for a state. @note The callback executes inside the StateTree logic. @note The StateTree can execute on any thread.
- L258 _macro_ `#define UE_STATETREE_DEBUG_CONDITION_ENTER_STATE(...)`
- L259 _macro_ `#define UE_STATETREE_DEBUG_CONDITION_TEST_CONDITION(...)`
- L260 _macro_ `#define UE_STATETREE_DEBUG_CONDITION_EXIT_STATE(...)`
- L262 _macro_ `#define UE_STATETREE_DEBUG_EVALUATOR_ENTER_TREE(...)`
- L263 _macro_ `#define UE_STATETREE_DEBUG_EVALUATOR_TICK(...)`
- L264 _macro_ `#define UE_STATETREE_DEBUG_EVALUATOR_EXIT_TREE(...)`
- L266 _macro_ `#define UE_STATETREE_DEBUG_TASK_ENTER_STATE(...)`
- L267 _macro_ `#define UE_STATETREE_DEBUG_TASK_TICK(...)`
- L268 _macro_ `#define UE_STATETREE_DEBUG_TASK_EXIT_STATE(...)`
- L270 _macro_ `#define UE_STATETREE_DEBUG_STATE_UTILITY_EVALUATED(...)`
- L272 _macro_ `#define UE_STATETREE_DEBUG_SEND_EVENT(...)`
- L273 _macro_ `#define UE_STATETREE_DEBUG_EVENT_CONSUMED(...)`
- L275 _macro_ `#define UE_STATETREE_DEBUG_ENTER_PHASE(...)`
- L276 _macro_ `#define UE_STATETREE_DEBUG_EXIT_PHASE(...)`
- L277 _macro_ `#define UE_STATETREE_DEBUG_STATE_EVENT(...)`
- L278 _macro_ `#define UE_STATETREE_DEBUG_TRANSITION_EVENT(...)`
- L279 _macro_ `#define UE_STATETREE_DEBUG_LOG_EVENT(...)`
- L280 _macro_ `#define UE_STATETREE_DEBUG_CONDITION_EVENT(...)`
- L281 _macro_ `#define UE_STATETREE_DEBUG_INSTANCE_EVENT(...)`
- L282 _macro_ `#define UE_STATETREE_DEBUG_INSTANCE_FRAME_EVENT(...)`
- L283 _macro_ `#define UE_STATETREE_DEBUG_ACTIVE_STATES_EVENT(...)`
- L284 _macro_ `#define UE_STATETREE_DEBUG_TASK_EVENT(...)`
- L285 _macro_ `#define UE_STATETREE_DEBUG_EVALUATOR_EVENT(...)`
- L287 _macro_ `#define UE_STATETREE_DEBUG_SCOPED_PHASE(...)`
- L288 _macro_ `#define UE_STATETREE_DEBUG_SCOPED_STATE(...)`
- L289 _macro_ `#define UE_STATETREE_DEBUG_SCOPED_STATE_PHASE(...)`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Debugger/StateTreeDebugger.h` (Public)


#### struct `UE::StateTreeDebugger::ITraceReader`  
`struct ITraceReader`  
_L32-39_
- L34 _public prototype_ `virtual ~ITraceReader() = default;`
- L35 _public prototype_ `virtual FInstanceEventCollection* GetOrCreateEventCollection(FStateTreeInstanceDebugId InstanceId) = 0;`
- L36 _public function_ `virtual void OnTraceEventProcessed(FStateTreeInstanceDebugId InstanceId, const FStateTreeTraceEventVariantType& Event)`

#### struct `UE::StateTreeDebugger::FTraceFilter`  
`struct FTraceFilter`  
_L41-55_
- L43 _public prototype_ `FTraceFilter() = delete;`
- L44 _public function_ `explicit FTraceFilter(const TNotNull<const UStateTree*>& Asset) : Asset(Asset)`
- L48 _public function_ `explicit FTraceFilter(const FStateTreeInstanceDebugId& Instance) : Instance(Instance)`
- L53 _public member_ `TObjectPtr<const UStateTree> Asset = nullptr;`
- L54 _public member_ `FStateTreeInstanceDebugId Instance;`

#### struct `FStateTreeDebugger`  
`struct FStateTreeDebugger : FTickableGameObject, UE::StateTreeDebugger::ITraceReader`  
_L82-544_
- inherits: `FTickableGameObject,UE::StateTreeDebugger::ITraceReader`
- L138 _public prototype_ `FStateTreeDebugger();`
- L141 _public function_ `const UStateTree* GetAsset() const`
- L146 _public function_ `void SetAsset(const UStateTree* Asset)`
- L153 _public prototype_ `void SyncToCurrentSessionDuration();` — Forces a single refresh to latest state. Useful when simulation is paused.
- L155 _public prototype_ `bool CanStepBackToPreviousStateWithEvents() const;`
- L156 _public prototype_ `void StepBackToPreviousStateWithEvents();`
- L158 _public prototype_ `bool CanStepForwardToNextStateWithEvents() const;`
- L159 _public prototype_ `void StepForwardToNextStateWithEvents();`
- L161 _public prototype_ `bool CanStepBackToPreviousStateChange() const;`
- L162 _public prototype_ `void StepBackToPreviousStateChange();`
- L164 _public prototype_ `bool CanStepForwardToNextStateChange() const;`
- L165 _public prototype_ `void StepForwardToNextStateChange();`
- L167 _public prototype_ `bool IsActiveInstance(double Time, FStateTreeInstanceDebugId InstanceId) const;`
- L169 _public prototype_ `FText GetInstanceName(FStateTreeInstanceDebugId InstanceId) const;`
- L170 _public prototype_ `FText GetInstanceDescription(FStateTreeInstanceDebugId InstanceId) const;`
- L172 _public prototype_ `void SelectInstance(const FStateTreeInstanceDebugId InstanceId);`
- L174 _public function_ `void ClearSelection()`
- L179 _public function_ `FStateTreeInstanceDebugId GetSelectedInstanceId() const`
- L184 _public prototype_ `TSharedPtr<const UE::StateTreeDebugger::FInstanceDescriptor> GetDescriptor(const FStateTreeInstanceDebugId InstanceId) const;`
- L185 _public function_ `TSharedPtr<const UE::StateTreeDebugger::FInstanceDescriptor> GetSelectedDescriptor() const`
- L191 _public function_ `const UE::StateTreeDebugger::FInstanceDescriptor* GetInstanceDescriptor(const FStateTreeInstanceDebugId InstanceId) const` — `UE_DEPRECATED(5.7, "Use GetDescriptor instead")`
- L196 _public function_ `const UE::StateTreeDebugger::FInstanceDescriptor* GetSelectedInstanceDescriptor() const` — `UE_DEPRECATED(5.7, "Use GetSelectedDescriptor instead")`
- L201 _public prototype_ `bool HasStateBreakpoint(FStateTreeStateHandle StateHandle, EStateTreeBreakpointType BreakpointType) const;`
- L202 _public prototype_ `bool HasTaskBreakpoint(FStateTreeIndex16 Index, EStateTreeBreakpointType BreakpointType) const;`
- L203 _public prototype_ `bool HasTransitionBreakpoint(FStateTreeIndex16 Index, EStateTreeBreakpointType BreakpointType) const;`
- L204 _public prototype_ `void SetStateBreakpoint(FStateTreeStateHandle StateHandle, EStateTreeBreakpointType BreakpointType);`
- L205 _public prototype_ `void SetTransitionBreakpoint(FStateTreeIndex16 SubIndex, EStateTreeBreakpointType BreakpointType);`
- L206 _public prototype_ `void SetTaskBreakpoint(FStateTreeIndex16 NodeIndex, EStateTreeBreakpointType BreakpointType);`
- L207 _public prototype_ `void ClearBreakpoint(FStateTreeIndex16 NodeIndex, EStateTreeBreakpointType BreakpointType);`
- L208 _public prototype_ `void ClearAllBreakpoints();`
- L210 _public function_ `int32 NumBreakpoints() const`
- L215 _public function_ `bool HasHitBreakpoint() const`
- L220 _public function_ `bool CanProcessBreakpoints() const`
- L225 _public prototype_ `static FText DescribeTrace(const FTraceDescriptor& TraceDescriptor);`
- L226 _public prototype_ `static FText DescribeInstance(const UE::StateTreeDebugger::FInstanceDescriptor& StateTreeInstanceDesc);`
- L234 _public prototype_ `const UE::StateTreeDebugger::FInstanceEventCollection& GetEventCollection(FStateTreeInstanceDebugId InstanceId) const;` — Finds and returns the event collection associated to a given instance Id. An invalid empty collection is returned if not found (IsValid needs to be called). @param InstanceId Id of the instance for which the event collection is returned. @return Event collection associated to the provided Id or an invalid one if not found.
- L237 _public prototype_ `void ResetEventCollections();` — Clears events from all instances.
- L240 _public function_ `double GetLastProcessedRecordedWorldTime() const` — Returns the world time associated to the last processed event.
- L246 _public function_ `double GetRecordingDuration() const` — `UE_DEPRECATED(5.7, "Use GetLastProcessedRecordedWorldTime instead")`
- L252 _public function_ `double GetAnalysisDuration() const` — Returns the duration of the analysis session. This is not related to the world simulation time.
- L258 _public function_ `double GetScrubTime() const` — Returns the time (based on the recording duration) associated to the selected frame.
- L263 _public prototype_ `void SetScrubTime(double ScrubTime);`
- L265 _public prototype_ `void GetLiveTraces(TArray<FTraceDescriptor>& OutTraceDescriptors) const;`
- L271 _public prototype_ `bool RequestAnalysisOfEditorSession();` — Queue a request to auto start an analysis session on the next available live trace. @return True if connection was successfully requested or was able to use active trace, false otherwise.
- L272 _public function_ `bool IsAnalyzingEditorSession() const`
- L279 _public function_ `bool WasAnalyzingEditorSession() const`
- L288 _public function_ `bool IsAnalysisSessionActive() const` — Indicates whether the analysis session was started and not stopped yet.
- L297 _public function_ `bool IsAnalysisSessionPaused() const` — Indicates that the debugger no longer processes new events from the analysis session until it gets resumed. This can be an external explicit request or after hitting a breakpoint.
- L302 _public prototype_ `const TraceServices::IAnalysisSession* GetAnalysisSession() const;`
- L310 _public prototype_ `bool RequestSessionAnalysis(const FTraceDescriptor& TraceDescriptor);` — Tries to start an analysis for a given trace descriptor. On success this method will execute the OnNewSession delegate. @param TraceDescriptor Descriptor of the trace that needs to be analyzed @return True if analysis was successfully started, false otherwise.
- L312 _public function_ `void PauseSessionAnalysis()`
- L317 _public function_ `void ResumeSessionAnalysis()`
- L323 _public prototype_ `void StopSessionAnalysis();`
- L325 _public function_ `FTraceDescriptor GetSelectedTraceDescriptor() const`
- L330 _public prototype_ `FText GetSelectedTraceDescription() const;`
- L333 _public prototype_ `void GetSessionInstances(TArray<UE::StateTreeDebugger::FInstanceDescriptor>& OutInstances) const;` — `UE_DEPRECATED(5.7, "Use GetSessionInstanceDescriptors instead")`
- L334 _public prototype_ `void GetSessionInstanceDescriptors(TArray<const TSharedRef<const UE::StateTreeDebugger::FInstanceDescriptor>>& OutInstances) const;`
- L336 _public member_ `FOnStateTreeDebuggerNewSession OnNewSession;`
- L337 _public member_ `FOnStateTreeDebuggerNewInstance OnNewInstance;`
- L341 _public member_ `FOnStateTreeDebuggerDebuggedInstanceSet OnSelectedInstanceCleared;` — `UE_DEPRECATED(5.7, "Delegate no longer used and will be removed")`
- L344 _public member_ `FOnStateTreeDebuggerScrubStateChanged OnScrubStateChanged;`
- L345 _public member_ `FOnStateTreeDebuggerBreakpointHit OnBreakpointHit;`
- L346 _public member_ `FOnStateTreeDebuggerActiveStatesChanges OnActiveStatesChanged;`
- L349 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L351 _protected function_ `virtual bool IsTickable() const override`
- L356 _protected function_ `virtual bool IsTickableWhenPaused() const override`
- L361 _protected function_ `virtual bool IsTickableInEditor() const override`
- L366 _protected function_ `virtual TStatId GetStatId() const override`
- L373 _private prototype_ `UE::StateTreeDebugger::FInstanceEventCollection* GetMutableEventCollection(const FStateTreeInstanceDebugId InstanceId);`
- L395 _private prototype_ `void UpdateAnalysisTransitionType(EAnalysisSourceType SourceType);`
- L397 _private prototype_ `void ReadTrace(double ScrubTime);`
- L398 _private prototype_ `void ReadTrace(uint64 FrameIndex);`
- L401 _private prototype_ `virtual UE::StateTreeDebugger::FInstanceEventCollection* GetOrCreateEventCollection(FStateTreeInstanceDebugId InstanceId) override;`
- L402 _private prototype_ `virtual void OnTraceEventProcessed(FStateTreeInstanceDebugId InstanceId, const FStateTreeTraceEventVariantType& Event) override;`
- L411 _private prototype_ `bool EvaluateBreakpoints(FStateTreeInstanceDebugId InstanceId, const FStateTreeTraceEventVariantType& Event);` — Tests event for given instance id against breakpoints. @param InstanceId Id of the statetree instance that produces the event. @param Event The event received from the instance. @return True if a breakpoint has been it, false otherwise.
- L413 _private prototype_ `void SendNotifications();`
- L415 _private prototype_ `void SetActiveStates(const FStateTreeTraceActiveStates& NewActiveStates);`
- L421 _private prototype_ `void RequestAnalysisOfLatestTrace();` — Request an analysis session on the latest next available live trace. This will replace the current analysis session if any.
- L429 _private prototype_ `bool TryStartNewLiveSessionAnalysis(float RetryPollingDuration);` — Looks for a new live traces to start an analysis session. On failure, if 'RetryPollingDuration is > 0', will retry connecting every frame for 'RetryPollingDuration' seconds @param RetryPollingDuration - On failure, how many seconds to retry connecting during FStateTreeDebugger::Tick @return True if the analysis was successfully started; false otherwise.
- L431 _private prototype_ `bool StartSessionAnalysis(const FTraceDescriptor& TraceDescriptor);`
- L433 _private prototype_ `void SetScrubStateCollection(const UE::StateTreeDebugger::FInstanceEventCollection* Collection);`
- L439 _private prototype_ `void RefreshActiveStates();` — Recompute index of the span that contains the active states change event and update the active states. This method handles unselected instances in which case it will reset the active states and set the span index to INDEX_NONE
- L441 _private prototype_ `UE::Trace::FStoreClient* GetStoreClient() const;`
- L443 _private prototype_ `void UpdateMetadata(FTraceDescriptor& TraceDescriptor) const;`
- L446 _private member_ `IStateTreeModule& StateTreeModule;` — Module used to access the store client and analysis sessions .
- L452 _private member_ `TWeakObjectPtr<const UStateTree> InstanceRootAsset;` — The StateTree asset associated to the selected instance. This can be different from 'StateTreeAsset' if the debugger is associated to a linked asset.
- L455 _private member_ `TWeakObjectPtr<const UStateTree> CurrentFrameStateTreeAsset;` — The StateTree asset associated to the last frame event processed by the debugger
- L458 _private member_ `TWeakObjectPtr<const UStateTree> StateTreeAsset;` — The StateTree asset associated to this debugger. All instances will be using this asset.
- L461 _private member_ `TSharedPtr<const TraceServices::IAnalysisSession> AnalysisSession;` — The trace analysis session.
- L464 _private member_ `FTraceDescriptor ActiveSessionTraceDescriptor;` — Descriptor of the currently selected session
- L467 _private member_ `TIndirectArray<UE::StateTreeDebugger::FInstanceEventCollection> EventCollections;` — Processed events for each instance.
- L470 _private member_ `FStateTreeInstanceDebugId SelectedInstanceId;` — Specific instance selected for more details
- L473 _private member_ `TArray<FStateTreeDebuggerBreakpoint> Breakpoints;` — List of breakpoints set. This is per asset and not specific to an instance.
- L476 _private member_ `FStateTreeTraceActiveStates ActiveStates;` — List of currently active states in the selected instance
- L482 _private member_ `int32 LastLiveSessionId = INDEX_NONE;` — When auto-connecting on next live session it is possible that a few frames are required for the tracing session to be accessible and connected to. This is to keep track of the previous last live session id so we can detect when the new one is available.
- L488 _private member_ `float RetryLoadNextLiveSessionTimer = 0.0f;` — When auto-connecting on next live session it is possible that a few frames are required for the tracing session to be accessible and connected to. This is to keep track of the time window where we will retry.
- L493 _private member_ `double LastProcessedRecordedWorldTime = 0;` — Most recent processed world time. This value is updated from received events so it might increase by large deltas.
- L496 _private member_ `double AnalysisDuration = 0;` — Duration of the analysis session. This is not related to the world simulation time.
- L499 _private member_ `double LastTraceReadTime = 0;` — Last time in the recording that we use to fetch events and we will use for the next read.
- L502 _private member_ `UE::StateTreeDebugger::FScrubState ScrubState;` — Combined information regarding current scrub time (e.g. frame index, event collection index, etc.)
- L505 _private member_ `FHitBreakpoint HitBreakpoint;` — Information stored when a breakpoint is hit while processing events and used to send notifications.
- L508 _private member_ `TArray<FStateTreeInstanceDebugId> NewInstances;` — List of new instances discovered by processing event in the analysis session.
- L511 _private member_ `bool bIsExternalSessionAnalysis = false;` — Indicates whether the analysis session is controlled by an external system, and we don't control its lifetime.
- L517 _private member_ `bool bSessionAnalysisActive = false;` — Indicates whether the analysis session is valid and active. This flag is required since once an analysis session is stopped there is nothing in its API to retrieve its status.
- L523 _private member_ `bool bSessionAnalysisPaused = false;` — Indicates that the debugger no longer process new events from the analysis session until it gets resumed. This can be an external explicit request or after hitting a breakpoint.
- L528 _private member_ `EAnalysisTransitionType AnalysisTransitionType = EAnalysisTransitionType::Unset;` — Indicates the last transition type between two consecutive analyses to manage track cleanup properly.
- L533 _private member_ `FDelegateHandle TracingStateChangedHandle;` — Delegate Handle bound to UE::StateTree::Delegates::OnTracingStateChanged
- L538 _private member_ `FDelegateHandle TraceAnalysisStateChangedHandle;` — Delegate Handle bound to UE::StateTree::Delegates::OnTraceAnalysisStateChanged
- L543 _private member_ `FDelegateHandle TracingTimelineScrubbedHandle;` — Delegate Handle bound to UE::StateTree::Delegates::OnTracingTimelineScrubbed

#### struct `FStateTreeDebugger::FTraceDescriptor`  
`struct FTraceDescriptor`  
_L84-110_
- L86 _public prototype_ `FTraceDescriptor() = default;`
- L87 _public function_ `FTraceDescriptor(const FString& Name, const uint32 Id) : Name(Name), TraceId(Id)`
- L91 _public function_ `bool operator==(const FTraceDescriptor& Other) const`
- L96 _public function_ `bool operator!=(const FTraceDescriptor& Other) const`
- L101 _public function_ `bool IsValid() const`
- L106 _public member_ `FString Name;`
- L107 _public member_ `uint32 TraceId = INDEX_NONE;`
- L109 _public member_ `TraceServices::FSessionInfo SessionInfo;`

#### struct `FStateTreeDebugger::FHitBreakpoint`  
`struct FHitBreakpoint`  
_L112-136_
- L114 _public function_ `bool IsSet() const`
- L118 _public function_ `void Reset()`
- L126 _public member_ `FStateTreeInstanceDebugId InstanceId = FStateTreeInstanceDebugId::Invalid;` — Indicates the instance for which the breakpoint has been hit
- L132 _public member_ `double Time = 0;` — Store the time at which the breakpoint was hit since we might have process more events before sending the notifications.
- L135 _public member_ `int32 Index = INDEX_NONE;` — Indicates the index of the breakpoint that has been hit

#### enum `FStateTreeDebugger::EAnalysisSourceType`  
`enum class EAnalysisSourceType : uint8`  
_L375-382_
- L378 _public enumerator_ `SelectedSession` — Analysis selected from available sessions
- L381 _public enumerator_ `EditorSession` — Analysis automatically started from Editor new recording

#### enum `FStateTreeDebugger::EAnalysisTransitionType`  
`enum class EAnalysisTransitionType : uint8`  
_L384-393_
- L386 _public enumerator_ `Unset`
- L387 _public enumerator_ `NoneToSelected`
- L388 _public enumerator_ `NoneToEditor`
- L389 _public enumerator_ `EditorToSelected`
- L390 _public enumerator_ `EditorToEditor`
- L391 _public enumerator_ `SelectedToSelected`
- L392 _public enumerator_ `SelectedToEditor`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API STATETREEMODULE_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Trace` (scope `UE`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace StateTreeDebugger` (scope `UE`)
- L57 _prototype_ `void ReadTrace( const TraceServices::IAnalysisSession& Session, const double ScrubTime, TNotNull<ITraceReader*> TraceReader, const FTraceFilter& Filter, double& OutLastTraceReadTime);` (scope `UE::StateTreeDebugger`)
- L64 _prototype_ `void ReadTrace( const TraceServices::IAnalysisSession& Session, const TraceServices::IFrameProvider& FrameProvider, const TraceServices::FFrame& Frame, TNotNull<ITraceReader*> TraceReader, const FTraceFilter& Filter, double& OutLastTraceReadTime);` (scope `UE::StateTreeDebugger`)
- L73 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStateTreeDebuggerScrubStateChanged, const UE::StateTreeDebugger::FScrubState& ScrubState);`
- L73 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStateTreeDebuggerScrubStateChanged, const UE::StateTreeDebugger::FScrubState& ScrubState);`
- L74 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnStateTreeDebuggerBreakpointHit, FStateTreeInstanceDebugId InstanceId, const FStateTreeDebuggerBreakpoint Breakpoint);`
- L74 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnStateTreeDebuggerBreakpointHit, FStateTreeInstanceDebugId InstanceId, const FStateTreeDebuggerBreakpoint Breakpoint);`
- L75 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStateTreeDebuggerActiveStatesChanges, const FStateTreeTraceActiveStates& ActiveStates);`
- L75 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStateTreeDebuggerActiveStatesChanges, const FStateTreeTraceActiveStates& ActiveStates);`
- L76 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStateTreeDebuggerNewInstance, FStateTreeInstanceDebugId InstanceId);`
- L76 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStateTreeDebuggerNewInstance, FStateTreeInstanceDebugId InstanceId);`
- L77 _delegate_ `DECLARE_DELEGATE(FOnStateTreeDebuggerNewSession);`
- L77 _prototype_ `DECLARE_DELEGATE(FOnStateTreeDebuggerNewSession);`
- L80 _delegate_ `DECLARE_DELEGATE(FOnStateTreeDebuggerDebuggedInstanceSet);`
- L80 _prototype_ `DECLARE_DELEGATE(FOnStateTreeDebuggerDebuggedInstanceSet);` — `UE_DEPRECATED(5.7, "Delegate type no longer used and will be removed")`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Debugger/StateTreeDebuggerTypes.h` (Public)


#### enum `EStateTreeBreakpointType`  
`enum class EStateTreeBreakpointType : uint8`  
_L18-24_
- reflection: `UENUM()`
- L20 _public enumerator_ `Unset`
- L21 _public enumerator_ `OnEnter`
- L22 _public enumerator_ `OnExit`
- L23 _public enumerator_ `OnTransition`

#### struct `UE::StateTreeDebugger::FFrameSpan`  
`struct FFrameSpan`  
_L38-59_
- desc: Struct indicating the index of the first event for a given trace recording frame.
- L40 _public prototype_ `FFrameSpan() = default;`
- L41 _public function_ `FFrameSpan(const TraceServices::FFrame& Frame, const double RecordingWorldTime, const int32 EventIdx) : Frame(Frame) , WorldTime(RecordingWorldTime) , EventIdx(EventIdx)`
- L48 _public function_ `double GetWorldTimeStart() const`
- L49 _public function_ `double GetWorldTimeEnd() const`
- L52 _public member_ `TraceServices::FFrame Frame;` — Frame index in the analysis session
- L55 _public member_ `double WorldTime = 0;` — World simulation time associated to that Frame index
- L58 _public member_ `int32 EventIdx = INDEX_NONE;` — Index of the first event for that Frame index

#### struct `UE::StateTreeDebugger::FInstanceDescriptor`  
`struct FInstanceDescriptor : TSharedFromThis<FInstanceDescriptor>`  
_L65-107_
- inherits: `TSharedFromThis<FInstanceDescriptor>`
- desc: Struct describing a state tree instance for a given StateTree asset
- L67 _public prototype_ `FInstanceDescriptor() = default;`
- L68 _public prototype_ `FInstanceDescriptor(const UStateTree* InStateTree, const FStateTreeInstanceDebugId InId, const FString& InName, const TRange<double>& InLifetime);`
- L70 _public prototype_ `bool IsValid() const;`
- L72 _public function_ `bool operator==(const FInstanceDescriptor& Other) const`
- L77 _public function_ `bool operator!=(const FInstanceDescriptor& Other) const`
- L83 _public function_ `bool IsInstanceActive() const` — Whether the associated instance is still active (i.e., not explicitly stopped by an execution context)
- L101 _public member_ `static constexpr double ActiveInstanceEndTime = std::numeric_limits<double>::max();`
- L102 _public member_ `TRange<double> Lifetime = TRange<double>(0);`
- L103 _public member_ `TWeakObjectPtr<const UStateTree> StateTree = nullptr;`
- L104 _public member_ `TArray<TWeakObjectPtr<const UStateTree>> LinkedStateTrees;`
- L105 _public member_ `FString Name;`
- L106 _public member_ `FStateTreeInstanceDebugId Id = FStateTreeInstanceDebugId::Invalid;`

#### struct `UE::StateTreeDebugger::FInstanceEventCollection`  
`struct FInstanceEventCollection`  
_L113-185_
- desc: Struct holding organized events associated to a given state tree instance.
- L115 _public prototype_ `FInstanceEventCollection() = default;`
- L116 _public function_ `explicit FInstanceEventCollection(const FStateTreeInstanceDebugId& InstanceId) : InstanceId(InstanceId)`
- L131 _public function_ `bool IsValid() const`
- L136 _public function_ `bool IsInvalid() const`
- L165 _public member_ `FStateTreeInstanceDebugId InstanceId;` — Id of the instance associated to the stored events.
- L168 _public member_ `TArray<FStateTreeTraceEventVariantType> Events;` — All events received for this instance.
- L171 _public member_ `TArray<FFrameSpan> FrameSpans;` — Spans for frames with events. Each span contains the frame information and the index of the first event for that frame.
- L174 _public member_ `TArray<FContiguousTraceInfo> ContiguousTracesData;` — This list is only used to merge events when dealing with multiple traces related to the same tree instance.
- L177 _public member_ `TArray<FActiveStatesChangePair> ActiveStatesChanges;` — Indices of span and event for frames with a change of activate states.
- L184 _public member_ `static const FInstanceEventCollection Invalid;` — Returns the event collection associated to the currently selected instance. An invalid empty collection is returned if there is no selected instance. (IsValid needs to be called). @return Event collection associated to the selected instance or an invalid one if not found.

#### struct `UE::StateTreeDebugger::FInstanceEventCollection::FActiveStatesChangePair`  
`struct FActiveStatesChangePair`  
_L141-151_
- L143 _public function_ `FActiveStatesChangePair(const int32 SpanIndex, const int32 EventIndex) : SpanIndex(SpanIndex) , EventIndex(EventIndex)`
- L149 _public member_ `int32 SpanIndex = INDEX_NONE;`
- L150 _public member_ `int32 EventIndex = INDEX_NONE;`

#### struct `UE::StateTreeDebugger::FInstanceEventCollection::FContiguousTraceInfo`  
`struct FContiguousTraceInfo`  
_L153-162_
- L155 _public function_ `explicit FContiguousTraceInfo(int32 LastSpanIndex) : LastSpanIndex(LastSpanIndex)`
- L161 _public member_ `int32 LastSpanIndex = INDEX_NONE;` — Indicates the index of the last spans of the trace and from which the frame index will be used to offset new events since their frames will restart at 0.

#### struct `UE::StateTreeDebugger::FScrubState`  
`struct FScrubState`  
_L187-326_
- L189 _public prototype_ `FScrubState() = default;`
- L190 _public function_ `explicit FScrubState(const FInstanceEventCollection* EventCollection) : EventCollection(EventCollection)`
- L195 _public function_ `explicit FScrubState(const TArray<FInstanceEventCollection>& EventCollections)` — `UE_DEPRECATED(5.7, "FScrubState will no longer support multiple collections.")`
- L200 _public function_ `int32 GetEventCollectionIndex() const` — `UE_DEPRECATED(5.7, "FScrubState will no longer support multiple collections.")`
- L206 _public function_ `void SetEventCollectionIndex(const int32 InEventCollectionIndex)` — `UE_DEPRECATED(5.7, "FScrubState will no longer support multiple collections.")`
- L211 _public prototype_ `void SetEventCollection(const FInstanceEventCollection* InEventCollection);` — Assigns a new collection and updates internal indices for current scrub time.
- L214 _public function_ `int32 GetFrameSpanIndex() const` — @return Index of the span for the currently selected frame; INDEX_NONE if there is no span for the current scrub time.
- L220 _public function_ `int32 GetActiveStatesIndex() const` — @return Index of the list of active states for the currently selected frame; INDEX_NONE if there is no active states for the current scrub time.
- L226 _public function_ `double GetScrubTime() const` — @return Current scrub time.
- L237 _public prototype_ `bool SetScrubTime(double NewScrubTime, bool bForceRefresh = false);` — Updates internal indices based on the new time. @param NewScrubTime The new scrub time to use to update all internal indices @param bForceRefresh Whether to force update of internal indices regardless if the current stored scrub time is the same as the provided one @return true if values were updated; false otherwise (i.e. no changes)
- L243 _public function_ `bool IsInBounds() const` — Indicates if the current scrub state points to a valid frame. @return True if the frame index is set
- L252 _public function_ `bool IsPointingToValidActiveStates() const` — Indicates if the current scrub state points to an active states entry in the event collection. @return True if the collection and active states indices are set
- L258 _public prototype_ `bool HasPreviousFrame() const;` — Indicates if there is a frame before with events.
- L265 _public prototype_ `double GotoPreviousFrame();` — Set scrubbing info using the previous frame with events. HasPreviousFrame must be used to validate that this method can be called otherwise some checks might fail. @return Adjusted scrub time
- L268 _public prototype_ `bool HasNextFrame() const;` — Indicates if there is a frame after with events.
- L275 _public prototype_ `double GotoNextFrame();` — Set scrubbing info using the next frame with events. HasPreviousFrame must be used to validate that this method can be called otherwise some checks might fail. @return Adjusted scrub time
- L278 _public prototype_ `bool HasPreviousActiveStates() const;` — Indicates if there is a frame before where the StateTree has a different list of active states.
- L285 _public prototype_ `double GotoPreviousActiveStates();` — Set scrubbing info using the previous frame where the StateTree has a different list of active states. HasPreviousActiveStates must be used to validate that this method can be called otherwise some checks might fail. @return Adjusted scrub time
- L288 _public prototype_ `bool HasNextActiveStates() const;` — Indicates if there is a frame after where the StateTree has a different list of active states.
- L295 _public prototype_ `double GotoNextActiveStates();` — Set scrubbing info using the next frame where the StateTree has a different list of active states. HasNextActiveStates must be used to validate that this method can be called otherwise some checks might fail. @return Adjusted scrub time
- L302 _public prototype_ `const FInstanceEventCollection& GetEventCollection() const;` — Returns the event collection associated. An invalid empty collection is returned if no collection was set (IsValid needs to be called). @return Event collection set or an invalid one if not set.
- L316 _private prototype_ `void SetFrameSpanIndex(int32 NewFrameSpanIndex);`
- L317 _private prototype_ `void SetActiveStatesIndex(int32 NewActiveStatesIndex);`
- L318 _private prototype_ `void UpdateActiveStatesIndex(int32 SpanIndex);`
- L320 _private member_ `const FInstanceEventCollection* EventCollection = nullptr;`
- L321 _private member_ `double ScrubTime = 0;`
- L322 _private member_ `uint64 TraceFrameIndex = INDEX_NONE;`
- L323 _private member_ `int32 FrameSpanIndex = INDEX_NONE;`
- L324 _private member_ `int32 ActiveStatesIndex = INDEX_NONE;`
- L325 _private member_ `EScrubTimeBoundState ScrubTimeBoundState = EScrubTimeBoundState::Unset;`

#### enum `UE::StateTreeDebugger::FScrubState::EScrubTimeBoundState`  
`enum class EScrubTimeBoundState : uint8`  
_L305-314_
- L307 _public enumerator_ `Unset`
- L309 _public enumerator_ `BeforeLowerBound` — There are events but current time is before the first frame.
- L311 _public enumerator_ `InBounds` — There are events and current time is within the frames received.
- L313 _public enumerator_ `AfterHigherBound` — There are events but current time is after the last frame.

#### struct `FStateTreeDebuggerBreakpoint`  
`struct FStateTreeDebuggerBreakpoint`  
_L330-369_
- L354 _public typedef_ `using FIdentifierVariantType = TVariant<FStateTreeStateHandle, FStateTreeTaskIndex, FStateTreeTransitionIndex>;`
- L356 _public prototype_ `FStateTreeDebuggerBreakpoint();`
- L357 _public prototype_ `explicit FStateTreeDebuggerBreakpoint(const FStateTreeStateHandle StateHandle, const EStateTreeBreakpointType BreakpointType);`
- L358 _public prototype_ `explicit FStateTreeDebuggerBreakpoint(const FStateTreeTaskIndex Index, const EStateTreeBreakpointType BreakpointType);`
- L359 _public prototype_ `explicit FStateTreeDebuggerBreakpoint(const FStateTreeTransitionIndex Index, const EStateTreeBreakpointType BreakpointType);`
- L361 _public prototype_ `bool IsMatchingEvent(const FStateTreeTraceEventVariantType& Event) const;`
- L363 _public member_ `FIdentifierVariantType ElementIdentifier;`
- L364 _public member_ `EStateTreeBreakpointType BreakpointType;`
- L365 _public member_ `EStateTreeTraceEventType EventType;`
- L368 _private prototype_ `static EStateTreeTraceEventType GetMatchingEventType(EStateTreeBreakpointType BreakpointType);`

#### struct `FStateTreeDebuggerBreakpoint::FStateTreeTaskIndex`  
`struct FStateTreeTaskIndex`  
_L333-342_
- desc: Wrapper structs to be able to use TVariant with more than one type based on FStateTreeIndex16 (can't use 'using')
- L335 _public prototype_ `FStateTreeTaskIndex() = default;`
- L336 _public function_ `explicit FStateTreeTaskIndex(const FStateTreeIndex16& Index) : Index(Index)`
- L341 _public member_ `FStateTreeIndex16 Index;`

#### struct `FStateTreeDebuggerBreakpoint::FStateTreeTransitionIndex`  
`struct FStateTreeTransitionIndex`  
_L344-352_
- L346 _public prototype_ `FStateTreeTransitionIndex() = default;`
- L347 _public function_ `explicit FStateTreeTransitionIndex(const FStateTreeIndex16& Index) : Index(Index)`
- L351 _public member_ `FStateTreeIndex16 Index;`

#### Free symbols / members of external scopes

- L28 _macro_ `#define UE_API STATETREEMODULE_API`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace StateTreeDebugger` (scope `UE`)
- L88 _function_ `friend FString LexToString(const FInstanceDescriptor& InstanceDesc)` (scope `UE::StateTreeDebugger`)
- L96 _function_ `friend uint32 GetTypeHash(const FInstanceDescriptor& Desc)` (scope `UE::StateTreeDebugger`)
- L121 _function_ `friend bool operator==(const FInstanceEventCollection& Lhs, const FInstanceEventCollection& RHS)` (scope `UE::StateTreeDebugger`)
- L126 _function_ `friend bool operator!=(const FInstanceEventCollection& Lhs, const FInstanceEventCollection& RHS)` (scope `UE::StateTreeDebugger`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Debugger/StateTreeRuntimeValidation.h` (Public)


#### struct `UE::StateTree::Debug::FRuntimeValidation`  
`struct FRuntimeValidation`  
_L27-44_
- desc: For debugging purposes, test the actions that are made on the StateTree instance.
- L30 _public prototype_ `FRuntimeValidation() = default;`
- L33 _public prototype_ `FRuntimeValidation(TNotNull<FRuntimeValidationInstanceData*> Instance);`
- L34 _public prototype_ `FRuntimeValidationInstanceData* GetInstanceData() const;`
- L38 _public prototype_ `void SetContext(TNotNull<const UObject*> Owner, TNotNull<const UStateTree*> StateTree, bool bInstanceDataWriteAccessAcquired) const;` — Set the Owner of the data
- L42 _private member_ `FRuntimeValidationInstanceData* RuntimeValidationData = nullptr;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace StateTree` (scope `UE`)
- L15 _namespace_ `namespace Debug` (scope `UE::StateTree`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace StateTree` (scope `UE`)
- L21 _namespace_ `namespace Debug` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Debugger/StateTreeTrace.h` (Public)


#### struct `UE::StateTreeTrace::FNodeCustomDebugData`  
`struct FNodeCustomDebugData`  
_L36-99_
- desc: Struct allowing StateTree nodes to add (or replace) a custom string to the trace event
- L45 _public prototype_ `FNodeCustomDebugData() = default;`
- L47 _public function_ `FNodeCustomDebugData(FStringView TraceDebuggerString, const EMergePolicy MergePolicy): TraceDebuggerString(TraceDebuggerString) , MergePolicy(MergePolicy)`
- L52 _public function_ `FNodeCustomDebugData(FNodeCustomDebugData&& Other) : TraceDebuggerString(MoveTemp(Other.TraceDebuggerString)) , MergePolicy(Other.MergePolicy)`
- L59 _public function_ `FNodeCustomDebugData& operator=(FNodeCustomDebugData&& Other)`
- L71 _public function_ `bool IsSet() const`
- L76 _public function_ `void Reset()`
- L82 _public function_ `bool ShouldOverrideDataView() const`
- L86 _public function_ `bool ShouldAppendToDataView() const`
- L91 _public function_ `FStringView GetTraceDebuggerString() const`
- L97 _private member_ `FString TraceDebuggerString;`
- L98 _private member_ `EMergePolicy MergePolicy = EMergePolicy::Unset;`

#### enum `UE::StateTreeTrace::FNodeCustomDebugData::EMergePolicy`  
`enum class EMergePolicy: uint8`  
_L38-43_
- L40 _public enumerator_ `Unset`
- L41 _public enumerator_ `Append`
- L42 _public enumerator_ `Override`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace ELogVerbosity`
- L30 _macro_ `#define UE_API STATETREEMODULE_API`
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace StateTreeTrace` (scope `UE`)
- L101 _prototype_ `void RegisterGlobalDelegates();` (scope `UE::StateTreeTrace`)
- L102 _prototype_ `void UnregisterGlobalDelegates();` (scope `UE::StateTreeTrace`)
- L103 _prototype_ `void OutputAssetDebugIdEvent(const UStateTree* StateTree, FStateTreeIndex16 AssetDebugId);` (scope `UE::StateTreeTrace`)
- L104 _prototype_ `void OutputPhaseScopeEvent(TNotNull<const FStateTreeReadOnlyExecutionContext*> Context, EStateTreeUpdatePhase Phase, EStateTreeTraceEventType EventType, FStateTreeStateHandle StateHandle);` (scope `UE::StateTreeTrace`)
- L105 _prototype_ `void OutputInstanceLifetimeEvent(TNotNull<const FStateTreeReadOnlyExecutionContext*> Context, EStateTreeTraceEventType EventType);` (scope `UE::StateTreeTrace`)
- L106 _prototype_ `void OutputInstanceAssetEvent(TNotNull<const FStateTreeReadOnlyExecutionContext*> Context, const UStateTree* StateTree);` (scope `UE::StateTreeTrace`)
- L107 _prototype_ `void OutputInstanceFrameEvent(TNotNull<const FStateTreeReadOnlyExecutionContext*> Context, const FStateTreeExecutionFrame* Frame);` (scope `UE::StateTreeTrace`)
- L108 _prototype_ `void OutputLogEventTrace(TNotNull<const FStateTreeReadOnlyExecutionContext*> Context, ELogVerbosity::Type Verbosity, const TCHAR* Fmt, ...);` (scope `UE::StateTreeTrace`)
- L109 _prototype_ `void OutputStateEventTrace(TNotNull<const FStateTreeReadOnlyExecutionContext*> Context, FStateTreeStateHandle StateHandle, EStateTreeTraceEventType EventType);` (scope `UE::StateTreeTrace`)
- L110 _prototype_ `void OutputTaskEventTrace(TNotNull<const FStateTreeReadOnlyExecutionContext*> Context, FStateTreeIndex16 TaskIdx, FStateTreeDataView DataView, EStateTreeTraceEventType EventType, EStateTreeRunStatus Status);` (scope `UE::StateTreeTrace`)
- L111 _prototype_ `void OutputEvaluatorEventTrace(TNotNull<const FStateTreeReadOnlyExecutionContext*> Context, FStateTreeIndex16 EvaluatorIdx, FStateTreeDataView DataView, EStateTreeTraceEventType EventType);` (scope `UE::StateTreeTrace`)
- L112 _prototype_ `void OutputConditionEventTrace(TNotNull<const FStateTreeReadOnlyExecutionContext*> Context, FStateTreeIndex16 ConditionIdx, FStateTreeDataView DataView, EStateTreeTraceEventType EventType);` (scope `UE::StateTreeTrace`)
- L113 _prototype_ `void OutputTransitionEventTrace(TNotNull<const FStateTreeReadOnlyExecutionContext*> Context, FStateTreeTransitionSource TransitionSource, EStateTreeTraceEventType EventType);` (scope `UE::StateTreeTrace`)
- L114 _prototype_ `void OutputActiveStatesEventTrace(TNotNull<const FStateTreeReadOnlyExecutionContext*> Context, TConstArrayView<FStateTreeExecutionFrame> ActiveFrames);` (scope `UE::StateTreeTrace`)
- L117 _prototype_ `FStateTreeIndex16 FindOrAddDebugIdForAsset(const UStateTree* StateTree);` (scope `UE::StateTreeTrace`) — `UE_DEPRECATED(5.6, "This method will no longer be exposed publicly.")`
- L119 _prototype_ `void OutputPhaseScopeEvent(FStateTreeInstanceDebugId InstanceId, EStateTreeUpdatePhase Phase, EStateTreeTraceEventType EventType, FStateTreeStateHandle StateHandle);` (scope `UE::StateTreeTrace`) — `UE_DEPRECATED(5.7, "Use the overload taking a pointer to the execution context instead.")`
- L121 _prototype_ `void OutputInstanceLifetimeEvent(FStateTreeInstanceDebugId InstanceId, const UStateTree* StateTree, const TCHAR* InstanceName, EStateTreeTraceEventType EventType);` (scope `UE::StateTreeTrace`) — `UE_DEPRECATED(5.7, "Use the overload taking a pointer to the execution context instead.")`
- L123 _prototype_ `void OutputInstanceAssetEvent(FStateTreeInstanceDebugId InstanceId, const UStateTree* StateTree);` (scope `UE::StateTreeTrace`) — `UE_DEPRECATED(5.7, "Use the overload taking a pointer to the execution context instead.")`
- L125 _prototype_ `void OutputInstanceFrameEvent(FStateTreeInstanceDebugId InstanceId, const FStateTreeExecutionFrame* Frame);` (scope `UE::StateTreeTrace`) — `UE_DEPRECATED(5.7, "Use the overload taking a pointer to the execution context instead.")`
- L127 _prototype_ `void OutputLogEventTrace(FStateTreeInstanceDebugId InstanceId, ELogVerbosity::Type Verbosity, const TCHAR* Fmt, ...);` (scope `UE::StateTreeTrace`) — `UE_DEPRECATED(5.7, "Use the overload taking a pointer to the execution context instead.")`
- L129 _prototype_ `void OutputStateEventTrace(FStateTreeInstanceDebugId InstanceId, FStateTreeStateHandle StateHandle, EStateTreeTraceEventType EventType);` (scope `UE::StateTreeTrace`) — `UE_DEPRECATED(5.7, "Use the overload taking a pointer to the execution context instead.")`
- L131 _prototype_ `void OutputTaskEventTrace(FStateTreeInstanceDebugId InstanceId, FNodeCustomDebugData&& DebugData, FStateTreeIndex16 TaskIdx, FStateTreeDataView DataView, EStateTreeTraceEventType EventType, EStateTreeRunStatus Status);` (scope `UE::StateTreeTrace`) — `UE_DEPRECATED(5.7, "Use the overload taking a pointer to the execution context instead.")`
- L133 _prototype_ `void OutputEvaluatorEventTrace(FStateTreeInstanceDebugId InstanceId, FNodeCustomDebugData&& DebugData, FStateTreeIndex16 EvaluatorIdx, FStateTreeDataView DataView, EStateTreeTraceEventType EventType);` (scope `UE::StateTreeTrace`) — `UE_DEPRECATED(5.7, "Use the overload taking a pointer to the execution context instead.")`
- L135 _prototype_ `void OutputConditionEventTrace(FStateTreeInstanceDebugId InstanceId, FNodeCustomDebugData&& DebugData, FStateTreeIndex16 ConditionIdx, FStateTreeDataView DataView, EStateTreeTraceEventType EventType);` (scope `UE::StateTreeTrace`) — `UE_DEPRECATED(5.7, "Use the overload taking a pointer to the execution context instead.")`
- L137 _prototype_ `void OutputTransitionEventTrace(FStateTreeInstanceDebugId InstanceId, FStateTreeTransitionSource TransitionSource, EStateTreeTraceEventType EventType);` (scope `UE::StateTreeTrace`) — `UE_DEPRECATED(5.7, "Use the overload taking a pointer to the execution context instead.")`
- L139 _prototype_ `void OutputActiveStatesEventTrace(FStateTreeInstanceDebugId InstanceId, TConstArrayView<FStateTreeExecutionFrame> ActiveFrames);` (scope `UE::StateTreeTrace`) — `UE_DEPRECATED(5.7, "Use the overload taking a pointer to the execution context instead.")`
- L143 _macro_ `#define TRACE_STATETREE_INSTANCE_EVENT(Context, EventType) \`
- L146 _macro_ `#define TRACE_STATETREE_INSTANCE_FRAME_EVENT(Context, Frame) \`
- L149 _macro_ `#define TRACE_STATETREE_PHASE_EVENT(Context, Phase, EventType, StateHandle) \`
- L152 _macro_ `#define TRACE_STATETREE_LOG_EVENT(Context, TraceVerbosity, Format, ...) \`
- L158 _macro_ `#define TRACE_STATETREE_STATE_EVENT(Context, StateHandle, EventType) \`
- L164 _macro_ `#define TRACE_STATETREE_TASK_EVENT(Context, TaskIdx, DataView, EventType, Status) \`
- L170 _macro_ `#define TRACE_STATETREE_EVALUATOR_EVENT(Context, EvaluatorIdx, DataView, EventType) \`
- L176 _macro_ `#define TRACE_STATETREE_CONDITION_EVENT(Context, ConditionIdx, DataView, EventType) \`
- L182 _macro_ `#define TRACE_STATETREE_TRANSITION_EVENT(Context, TransitionIdx, EventType) \`
- L188 _macro_ `#define TRACE_STATETREE_ACTIVE_STATES_EVENT(Context, ActivateFrames) \`
- L195 _macro_ `#define TRACE_STATETREE_INSTANCE_EVENT(...)`
- L196 _macro_ `#define TRACE_STATETREE_INSTANCE_FRAME_EVENT(...)`
- L197 _macro_ `#define TRACE_STATETREE_PHASE_EVENT(...)`
- L198 _macro_ `#define TRACE_STATETREE_LOG_EVENT(...)`
- L199 _macro_ `#define TRACE_STATETREE_STATE_EVENT(...)`
- L200 _macro_ `#define TRACE_STATETREE_TASK_EVENT(...)`
- L201 _macro_ `#define TRACE_STATETREE_EVALUATOR_EVENT(...)`
- L202 _macro_ `#define TRACE_STATETREE_CONDITION_EVENT(...)`
- L203 _macro_ `#define TRACE_STATETREE_TRANSITION_EVENT(...)`
- L204 _macro_ `#define TRACE_STATETREE_ACTIVE_STATES_EVENT(...)`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Debugger/StateTreeTraceAnalyzer.h` (Public)


#### class `FStateTreeTraceAnalyzer`  
`class FStateTreeTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L12-41_
- inherits: `UE::Trace::IAnalyzer`
- L15 _public prototype_ `FStateTreeTraceAnalyzer(TraceServices::IAnalysisSession& InSession, FStateTreeTraceProvider& InProvider);`
- L17 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L18 _public function_ `virtual void OnAnalysisEnd() override`
- L19 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L38 _private member_ `TraceServices::IAnalysisSession& Session;`
- L39 _private member_ `FStateTreeTraceProvider& Provider;`
- L40 _private member_ `double WorldTime = 0;`

#### enum `FStateTreeTraceAnalyzer::(anonymous)`  
``  
_L23-36_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L24 _enumerator_ `RouteId_WorldTimestamp` (scope `FStateTreeTraceAnalyzer::__anoncfbae41e0103`)
- L25 _enumerator_ `RouteId_AssetDebugId` (scope `FStateTreeTraceAnalyzer::__anoncfbae41e0103`)
- L26 _enumerator_ `RouteId_Instance` (scope `FStateTreeTraceAnalyzer::__anoncfbae41e0103`)
- L27 _enumerator_ `RouteId_InstanceFrame` (scope `FStateTreeTraceAnalyzer::__anoncfbae41e0103`)
- L28 _enumerator_ `RouteId_Phase` (scope `FStateTreeTraceAnalyzer::__anoncfbae41e0103`)
- L29 _enumerator_ `RouteId_LogMessage` (scope `FStateTreeTraceAnalyzer::__anoncfbae41e0103`)
- L30 _enumerator_ `RouteId_State` (scope `FStateTreeTraceAnalyzer::__anoncfbae41e0103`)
- L31 _enumerator_ `RouteId_Task` (scope `FStateTreeTraceAnalyzer::__anoncfbae41e0103`)
- L32 _enumerator_ `RouteId_Evaluator` (scope `FStateTreeTraceAnalyzer::__anoncfbae41e0103`)
- L33 _enumerator_ `RouteId_Transition` (scope `FStateTreeTraceAnalyzer::__anoncfbae41e0103`)
- L34 _enumerator_ `RouteId_Condition` (scope `FStateTreeTraceAnalyzer::__anoncfbae41e0103`)
- L35 _enumerator_ `RouteId_ActiveStates` (scope `FStateTreeTraceAnalyzer::__anoncfbae41e0103`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Debugger/StateTreeTraceModule.h` (Public)


#### class `FStateTreeTraceModule`  
`class FStateTreeTraceModule : public TraceServices::IModule`  
_L9-19_
- inherits: `TraceServices::IModule`
- L13 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L14 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L15 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L18 _private member_ `static FName ModuleName;`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Debugger/StateTreeTraceProvider.h` (Public)


#### class `FStateTreeTraceProvider`  
`class FStateTreeTraceProvider : public IStateTreeTraceProvider, public TraceServices::IEditableProvider`  
_L21-97_
- inherits: `IStateTreeTraceProvider,TraceServices::IEditableProvider`
- L24 _public member_ `static FName ProviderName;`
- L26 _public prototype_ `explicit FStateTreeTraceProvider(TraceServices::IAnalysisSession& InSession);`
- L29 _public function_ `virtual void BeginRead() const override`
- L33 _public function_ `virtual void EndRead() const override`
- L37 _public function_ `virtual void ReadAccessCheck() const override`
- L43 _public function_ `virtual void BeginEdit() const override`
- L47 _public function_ `virtual void EndEdit() const override`
- L51 _public function_ `virtual void EditAccessCheck() const override`
- L56 _public prototype_ `void AppendEvent(FStateTreeInstanceDebugId InInstanceId, double InTime, const FStateTreeTraceEventVariantType& InEvent);`
- L57 _public prototype_ `void AppendInstanceEvent( const FStateTreeIndex16 AssetDebugId, const FStateTreeInstanceDebugId InInstanceId, const TCHAR* InInstanceName, double InTime, double InWorldRecordingTime, EStateTreeTraceEventType InEventType);`
- L65 _public prototype_ `void AppendAssetDebugId(const UStateTree* InStateTree, const FStateTreeIndex16 AssetDebugId);`
- L66 _public prototype_ `bool GetAssetFromDebugId(const FStateTreeIndex16 AssetDebugId, TWeakObjectPtr<const UStateTree>& WeakStateTree) const;`
- L67 _public prototype_ `bool GetAssetFromInstanceId(const FStateTreeInstanceDebugId InstanceId, TWeakObjectPtr<const UStateTree>& WeakStateTree) const;`
- L71 _protected prototype_ `virtual TSharedPtr<const UE::StateTreeDebugger::FInstanceDescriptor> GetInstanceDescriptor(const FStateTreeInstanceDebugId InstanceId) const override;`
- L72 _protected prototype_ `virtual void GetInstances(TArray<const TSharedRef<const UE::StateTreeDebugger::FInstanceDescriptor>>& OutInstances) const override;`
- L73 _protected prototype_ `virtual bool ReadTimelines(const FStateTreeInstanceDebugId InstanceId, TFunctionRef<void(const FStateTreeInstanceDebugId ProcessedInstanceId, const FEventsTimeline&)> Callback) const override;`
- L74 _protected prototype_ `virtual bool ReadTimelines(const UStateTree& StateTree, TFunctionRef<void(const FStateTreeInstanceDebugId ProcessedInstanceId, const FEventsTimeline&)> Callback) const override;`
- L77 _private member_ `TraceServices::IAnalysisSession& Session;`
- L78 _private member_ `mutable TraceServices::FProviderLock Lock;`
- L80 _private member_ `TMap<FStateTreeInstanceDebugId, uint32> InstanceIdToDebuggerEntryTimelines;`
- L81 _private member_ `TArray<TSharedRef<UE::StateTreeDebugger::FInstanceDescriptor>> Descriptors;`
- L82 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FStateTreeTraceEventVariantType>>> EventsTimelines;`
- L96 _private member_ `TArray<FStateTreeDebugIdPair> StateTreeAssets;`

#### struct `FStateTreeTraceProvider::FStateTreeDebugIdPair`  
`struct FStateTreeDebugIdPair`  
_L84-94_
- L86 _public function_ `FStateTreeDebugIdPair(const TWeakObjectPtr<const UStateTree>& WeakStateTree, const FStateTreeIndex16 Id) : WeakStateTree(WeakStateTree) , Id(Id)`
- L92 _public member_ `TWeakObjectPtr<const UStateTree> WeakStateTree;`
- L93 _public member_ `FStateTreeIndex16 Id;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`
- L15 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GStateTreeProviderLockState;` (scope `TraceServices`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace StateTreeDebugger` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Debugger/StateTreeTraceTypes.h` (Public)


#### enum `EStateTreeTraceStatus`  
`enum class EStateTreeTraceStatus : uint8`  
_L16-22_
- reflection: `UENUM()`
- L18 _public enumerator_ `TracesStarted`
- L19 _public enumerator_ `StoppingTrace`
- L20 _public enumerator_ `TracesStopped`
- L21 _public enumerator_ `Cleared`

#### enum `EStateTreeTraceAnalysisStatus`  
`enum class EStateTreeTraceAnalysisStatus : uint8`  
_L25-30_
- reflection: `UENUM()`
- L27 _public enumerator_ `Started`
- L28 _public enumerator_ `Stopped`
- L29 _public enumerator_ `Cleared`

#### enum `EStateTreeTraceEventType`  
`enum class EStateTreeTraceEventType : uint8`  
_L33-57_
- reflection: `UENUM()`
- L35 _public enumerator_ `Unset`
- L36 _public enumerator_ `OnEntering UMETA(DisplayName = "Entering")`
- L37 _public enumerator_ `OnEntered UMETA(DisplayName = "Entered")`
- L38 _public enumerator_ `OnExiting UMETA(DisplayName = "Exiting")`
- L39 _public enumerator_ `OnExited UMETA(DisplayName = "Exited")`
- L40 _public enumerator_ `Push UMETA(DisplayName = "Push")`
- L41 _public enumerator_ `Pop UMETA(DisplayName = "Pop")`
- L42 _public enumerator_ `OnStateSelected UMETA(DisplayName = "Selected")`
- L43 _public enumerator_ `OnStateCompleted UMETA(DisplayName = "Completed")`
- L44 _public enumerator_ `OnTicking UMETA(DisplayName = "Tick")`
- L45 _public enumerator_ `OnTaskCompleted UMETA(DisplayName = "Completed")`
- L46 _public enumerator_ `OnTicked UMETA(DisplayName = "Ticked")`
- L47 _public enumerator_ `Passed UMETA(DisplayName = "Passed")`
- L48 _public enumerator_ `Failed UMETA(DisplayName = "Failed")`
- L49 _public enumerator_ `ForcedSuccess UMETA(DisplayName = "Forced Success")`
- L50 _public enumerator_ `ForcedFailure UMETA(DisplayName = "Forced Failure")`
- L51 _public enumerator_ `InternalForcedFailure UMETA(DisplayName = "Internal Forced Failure")`
- L52 _public enumerator_ `OnRequesting UMETA(DisplayName = "Requesting")`
- L53 _public enumerator_ `OnEvaluating UMETA(DisplayName = "Evaluating")`
- L54 _public enumerator_ `OnTransition UMETA(DisplayName = "Applying Transition")`
- L55 _public enumerator_ `OnTreeStarted UMETA(DisplayName = "Tree Started")`
- L56 _public enumerator_ `OnTreeStopped UMETA(DisplayName = "Tree Stopped")`

#### struct `FStateTreeTraceBaseEvent`  
`struct FStateTreeTraceBaseEvent`  
_L61-86_
- L63 _public function_ `explicit FStateTreeTraceBaseEvent(const double RecordingWorldTime, const EStateTreeTraceEventType EventType) : RecordingWorldTime(RecordingWorldTime) , EventType(EventType)`
- L69 _public function_ `static FString GetDataTypePath()`
- L74 _public function_ `static FString GetDataAsText()`
- L79 _public function_ `static FString GetDebugText()`
- L84 _public member_ `double RecordingWorldTime = 0;`
- L85 _public member_ `EStateTreeTraceEventType EventType;`

#### struct `FStateTreeTracePhaseEvent`  
`struct FStateTreeTracePhaseEvent : FStateTreeTraceBaseEvent`  
_L88-103_
- inherits: `FStateTreeTraceBaseEvent`
- L90 _public function_ `explicit FStateTreeTracePhaseEvent(const double RecordingWorldTime, const EStateTreeUpdatePhase Phase, const EStateTreeTraceEventType EventType, const FStateTreeStateHandle StateHandle) : FStateTreeTraceBaseEvent(RecordingWorldTime, EventType) , Phase(Phase) , StateHandle(StateHandle)`
- L97 _public prototype_ `FString ToFullString(const UStateTree& StateTree) const;`
- L98 _public prototype_ `FString GetValueString(const UStateTree& StateTree) const;`
- L99 _public prototype_ `FString GetTypeString(const UStateTree& StateTree) const;`
- L101 _public member_ `EStateTreeUpdatePhase Phase;`
- L102 _public member_ `FStateTreeStateHandle StateHandle;`

#### struct `FStateTreeTraceLogEvent`  
`struct FStateTreeTraceLogEvent : FStateTreeTraceBaseEvent`  
_L105-120_
- inherits: `FStateTreeTraceBaseEvent`
- L107 _public function_ `explicit FStateTreeTraceLogEvent(const double RecordingWorldTime, const ELogVerbosity::Type Verbosity, const FString& Message) : FStateTreeTraceBaseEvent(RecordingWorldTime, EStateTreeTraceEventType::Unset) , Verbosity(Verbosity) , Message(Message)`
- L114 _public prototype_ `FString ToFullString(const UStateTree& StateTree) const;`
- L115 _public prototype_ `FString GetValueString(const UStateTree& StateTree) const;`
- L116 _public prototype_ `FString GetTypeString(const UStateTree& StateTree) const;`
- L118 _public member_ `ELogVerbosity::Type Verbosity;`
- L119 _public member_ `FString Message;`

#### struct `FStateTreeTracePropertyEvent`  
`struct FStateTreeTracePropertyEvent : FStateTreeTraceLogEvent`  
_L122-137_
- inherits: `FStateTreeTraceLogEvent`
- L124 _public function_ `explicit FStateTreeTracePropertyEvent(const double RecordingWorldTime, const FString& Message) : FStateTreeTraceLogEvent(RecordingWorldTime, ELogVerbosity::Verbose, Message)`
- L129 _public function_ `explicit FStateTreeTracePropertyEvent(const double RecordingWorldTime, const ELogVerbosity::Type Verbosity, const FString& Message) : FStateTreeTraceLogEvent(RecordingWorldTime, Verbosity, Message)`
- L134 _public prototype_ `FString ToFullString(const UStateTree& StateTree) const;`
- L135 _public prototype_ `FString GetValueString(const UStateTree& StateTree) const;`
- L136 _public prototype_ `FString GetTypeString(const UStateTree& StateTree) const;`

#### struct `FStateTreeTraceTransitionEvent`  
`struct FStateTreeTraceTransitionEvent : FStateTreeTraceBaseEvent`  
_L139-152_
- inherits: `FStateTreeTraceBaseEvent`
- L141 _public function_ `explicit FStateTreeTraceTransitionEvent(const double RecordingWorldTime, const FStateTreeTransitionSource TransitionSource, const EStateTreeTraceEventType EventType) : FStateTreeTraceBaseEvent(RecordingWorldTime, EventType) , TransitionSource(TransitionSource)`
- L147 _public prototype_ `FString ToFullString(const UStateTree& StateTree) const;`
- L148 _public prototype_ `FString GetValueString(const UStateTree& StateTree) const;`
- L149 _public prototype_ `FString GetTypeString(const UStateTree& StateTree) const;`
- L151 _public member_ `FStateTreeTransitionSource TransitionSource;`

#### struct `FStateTreeTraceNodeEvent`  
`struct FStateTreeTraceNodeEvent : FStateTreeTraceBaseEvent`  
_L154-167_
- inherits: `FStateTreeTraceBaseEvent`
- L156 _public function_ `explicit FStateTreeTraceNodeEvent(const double RecordingWorldTime, const FStateTreeIndex16 Index, const EStateTreeTraceEventType EventType) : FStateTreeTraceBaseEvent(RecordingWorldTime, EventType) , Index(Index)`
- L162 _public prototype_ `FString ToFullString(const UStateTree& StateTree) const;`
- L163 _public prototype_ `FString GetValueString(const UStateTree& StateTree) const;`
- L164 _public prototype_ `FString GetTypeString(const UStateTree& StateTree) const;`
- L166 _public member_ `FStateTreeIndex16 Index;`

#### struct `FStateTreeTraceStateEvent`  
`struct FStateTreeTraceStateEvent : FStateTreeTraceNodeEvent`  
_L169-180_
- inherits: `FStateTreeTraceNodeEvent`
- L171 _public function_ `explicit FStateTreeTraceStateEvent(const double RecordingWorldTime, const FStateTreeIndex16 Index, const EStateTreeTraceEventType EventType) : FStateTreeTraceNodeEvent(RecordingWorldTime, Index, EventType)`
- L176 _public prototype_ `FString ToFullString(const UStateTree& StateTree) const;`
- L177 _public prototype_ `FString GetValueString(const UStateTree& StateTree) const;`
- L178 _public prototype_ `FString GetTypeString(const UStateTree& StateTree) const;`
- L179 _public prototype_ `FStateTreeStateHandle GetStateHandle() const;`

#### struct `FStateTreeTraceTaskEvent`  
`struct FStateTreeTraceTaskEvent : FStateTreeTraceNodeEvent`  
_L182-222_
- inherits: `FStateTreeTraceNodeEvent`
- L184 _public function_ `explicit FStateTreeTraceTaskEvent(const double RecordingWorldTime , const FStateTreeIndex16 Index , const EStateTreeTraceEventType EventType , const EStateTreeRunStatus Status , const FString& TypePath , const FString& InstanceDataAsText , const FString& DebugText) : FStateTreeTraceNodeEvent(RecordingWorldTime, Index, EventType) , TypePath(TypePath) , InstanceDataAsText(InstanceDataAsText) , DebugText(DebugText) , Status(Status)`
- L199 _public prototype_ `FString ToFullString(const UStateTree& StateTree) const;`
- L200 _public prototype_ `FString GetValueString(const UStateTree& StateTree) const;`
- L201 _public prototype_ `FString GetTypeString(const UStateTree& StateTree) const;`
- L203 _public function_ `FString GetDataTypePath() const`
- L208 _public function_ `FString GetDataAsText() const`
- L213 _public function_ `FString GetDebugText() const`
- L218 _public member_ `FString TypePath;`
- L219 _public member_ `FString InstanceDataAsText;`
- L220 _public member_ `FString DebugText;`
- L221 _public member_ `EStateTreeRunStatus Status;`

#### struct `FStateTreeTraceEvaluatorEvent`  
`struct FStateTreeTraceEvaluatorEvent : FStateTreeTraceNodeEvent`  
_L224-261_
- inherits: `FStateTreeTraceNodeEvent`
- L226 _public function_ `explicit FStateTreeTraceEvaluatorEvent(const double RecordingWorldTime , const FStateTreeIndex16 Index , const EStateTreeTraceEventType EventType , const FString& TypePath , const FString& InstanceDataAsText , const FString& DebugText) : FStateTreeTraceNodeEvent(RecordingWorldTime, Index, EventType) , TypePath(TypePath) , InstanceDataAsText(InstanceDataAsText) , DebugText(DebugText)`
- L239 _public prototype_ `FString ToFullString(const UStateTree& StateTree) const;`
- L240 _public prototype_ `FString GetValueString(const UStateTree& StateTree) const;`
- L241 _public prototype_ `FString GetTypeString(const UStateTree& StateTree) const;`
- L243 _public function_ `FString GetDataTypePath() const`
- L248 _public function_ `FString GetDataAsText() const`
- L253 _public function_ `FString GetDebugText() const`
- L258 _public member_ `FString TypePath;`
- L259 _public member_ `FString InstanceDataAsText;`
- L260 _public member_ `FString DebugText;`

#### struct `FStateTreeTraceConditionEvent`  
`struct FStateTreeTraceConditionEvent : FStateTreeTraceNodeEvent`  
_L263-300_
- inherits: `FStateTreeTraceNodeEvent`
- L265 _public function_ `explicit FStateTreeTraceConditionEvent(const double RecordingWorldTime , const FStateTreeIndex16 Index , const EStateTreeTraceEventType EventType , const FString& TypePath , const FString& InstanceDataAsText , const FString& DebugText) : FStateTreeTraceNodeEvent(RecordingWorldTime, Index, EventType) , TypePath(TypePath) , InstanceDataAsText(InstanceDataAsText) , DebugText(DebugText)`
- L278 _public prototype_ `FString ToFullString(const UStateTree& StateTree) const;`
- L279 _public prototype_ `FString GetValueString(const UStateTree& StateTree) const;`
- L280 _public prototype_ `FString GetTypeString(const UStateTree& StateTree) const;`
- L282 _public function_ `FString GetDataTypePath() const`
- L287 _public function_ `FString GetDataAsText() const`
- L292 _public function_ `FString GetDebugText() const`
- L297 _public member_ `FString TypePath;`
- L298 _public member_ `FString InstanceDataAsText;`
- L299 _public member_ `FString DebugText;`

#### struct `FStateTreeTraceActiveStates`  
`struct FStateTreeTraceActiveStates`  
_L302-315_
- L312 _public prototype_ `bool operator==(const FStateTreeTraceActiveStates& Other) const = default;`
- L314 _public member_ `TArray<FAssetActiveStates> PerAssetStates;`

#### struct `FStateTreeTraceActiveStates::FAssetActiveStates`  
`struct FAssetActiveStates`  
_L304-310_
- L306 _public prototype_ `bool operator==(const FAssetActiveStates& Other) const = default;`
- L308 _public member_ `TWeakObjectPtr<const UStateTree> WeakStateTree;`
- L309 _public member_ `TArray<FStateTreeStateHandle> ActiveStates;`

#### struct `FStateTreeTraceActiveStatesEvent`  
`struct FStateTreeTraceActiveStatesEvent : FStateTreeTraceBaseEvent`  
_L317-327_
- inherits: `FStateTreeTraceBaseEvent`
- L320 _public prototype_ `explicit FStateTreeTraceActiveStatesEvent(const double RecordingWorldTime);` — Intentionally implemented in source file to compile 'TArray<FStateTreeStateHandle>' using only forward declaration.
- L322 _public prototype_ `FString ToFullString(const UStateTree& StateTree) const;`
- L323 _public prototype_ `FString GetValueString(const UStateTree& StateTree) const;`
- L324 _public prototype_ `FString GetTypeString(const UStateTree& StateTree) const;`
- L326 _public member_ `FStateTreeTraceActiveStates ActiveStates;`

#### struct `FStateTreeTraceInstanceFrameEvent`  
`struct FStateTreeTraceInstanceFrameEvent : FStateTreeTraceBaseEvent`  
_L329-338_
- inherits: `FStateTreeTraceBaseEvent`
- L331 _public prototype_ `explicit FStateTreeTraceInstanceFrameEvent(const double RecordingWorldTime, const EStateTreeTraceEventType EventType, const UStateTree* StateTree);`
- L333 _public prototype_ `FString ToFullString(const UStateTree& StateTree) const;`
- L334 _public prototype_ `FString GetValueString(const UStateTree& StateTree) const;`
- L335 _public prototype_ `FString GetTypeString(const UStateTree& StateTree) const;`
- L337 _public member_ `TWeakObjectPtr<const UStateTree> WeakStateTree;`

#### Free symbols / members of external scopes

- L341 _typedef_ `using FStateTreeTraceEventVariantType = TVariant<FStateTreeTracePhaseEvent, FStateTreeTraceLogEvent, FStateTreeTracePropertyEvent, FStateTreeTraceNodeEvent, FStateTreeTraceStateEvent, FStateTreeTraceTaskEvent, FStateTreeTraceEvaluatorEvent, FStateTreeTraceTransitionEvent, FStateTreeTraceConditionEvent, FStateTreeTraceActiveStatesEvent, FStateTreeTraceInstanceFrameEvent>;` — Type aliases for statetree trace events

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/IStateTreeSchemaProvider.h` (Public)


#### class `UStateTreeSchemaProvider`  
`class UStateTreeSchemaProvider : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IStateTreeSchemaProvider`  
`class IStateTreeSchemaProvider`  
_L25-31_
- desc: Implementing this interface allows derived class to override the schema used to filter valid state trees for a FStateTreeReference. The state tree reference property needs to be marked with SchemaCanBeOverriden metatag. Ex: UPROPERTY(EditAnywhere, Category = AI, meta=(Schema="/Script/GameplayStateTreeModule.StateTreeComponentSchema", SchemaCanBeOverriden)) FStateTreeReference StateTreeRef;

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTree.h` (Public)


#### struct `FStateTreeCustomVersion`  
`FStateTreeCustomVersion`  
_L26-81_
- reflection: `UE_DEPRECATED(all, "Use a stream custom version. Data made with a custom version for feature do not merge between streams.")`
- L77 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L80 _private function_ `FStateTreeCustomVersion()`

#### enum `FStateTreeCustomVersion::Type`  
`enum Type`  
_L28-74_
- L31 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L33 _public enumerator_ `SharedInstanceData` — Separated conditions to shared instance data.
- L35 _public enumerator_ `GlobalEvaluators` — Moved evaluators to be global.
- L37 _public enumerator_ `InstanceDataArrays` — Moved instance data to arrays.
- L39 _public enumerator_ `IndexTypes` — Added index types.
- L41 _public enumerator_ `AddedEvents` — Added events.
- L43 _public enumerator_ `AddedFoo` — Testing mishap
- L45 _public enumerator_ `TransitionDelay` — Changed transition delay
- L47 _public enumerator_ `AddedExternalTransitions` — Added external transitions
- L49 _public enumerator_ `ChangedBindingsRepresentation` — Changed how bindings are represented
- L51 _public enumerator_ `AddedTransitionIds` — Added guid to transitions
- L53 _public enumerator_ `AddedDataHandlesIds` — Added data handles
- L55 _public enumerator_ `AddedLinkedAssetState` — Added linked asset state
- L57 _public enumerator_ `ChangedExternalDataAccess` — Change how external data is accessed
- L59 _public enumerator_ `OverridableParameters` — Added override option for parameters
- L61 _public enumerator_ `OverridableStateParameters` — Added override option for state parameters
- L63 _public enumerator_ `StoringGlobalParametersInInstanceStorage` — Added storing global parameters in instance storage
- L65 _public enumerator_ `AddedBindingToEvents` — Added binding to events
- L67 _public enumerator_ `AddedCheckingParentsPrerequisites` — Added checking parent states' prerequisites when activating child state directly.
- L69 _public enumerator_ `TickParameterBindings` — Added Tick Parameter Binding.
- L72 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L73 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### struct `FStateTreeMemoryUsage`  
`struct FStateTreeMemoryUsage`  
_L103-121_
- desc: Struct containing information about the StateTree runtime memory usage.
- L105 _public prototype_ `FStateTreeMemoryUsage() = default;`
- L106 _public function_ `FStateTreeMemoryUsage(const FString InName, const FStateTreeStateHandle InHandle = FStateTreeStateHandle::Invalid) : Name(InName) , Handle(InHandle)`
- L112 _public prototype_ `void AddUsage(FConstStructView View);`
- L113 _public prototype_ `void AddUsage(const UObject* Object);`
- L115 _public member_ `FString Name;`
- L116 _public member_ `FStateTreeStateHandle Handle;`
- L117 _public member_ `int32 NodeCount = 0;`
- L118 _public member_ `int32 EstimatedMemoryUsage = 0;`
- L119 _public member_ `int32 ChildNodeCount = 0;`
- L120 _public member_ `int32 EstimatedChildMemoryUsage = 0;`

#### class `UStateTree`  
`class UStateTree : public UDataAsset`  
_L133-687_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- desc: StateTree asset. Contains the StateTree definition in both editor and runtime (baked) formats.
- L139 _public function_ `const FStateTreeInstanceData& GetDefaultInstanceData() const` — @return Default instance data.
- L145 _public prototype_ `TSharedPtr<FStateTreeInstanceData> GetSharedInstanceData() const;` — @return Shared instance data.
- L148 _public function_ `int32 GetNumContextDataViews() const` — @return Number of context data views required for StateTree execution (Tree params, context data, External data).
- L154 _public function_ `const UE::StateTree::InstanceData::FInstanceContainer& GetDefaultEvaluationScopeInstanceData() const` — @return Default evaluation scope instance data.
- L160 _public function_ `const UE::StateTree::InstanceData::FInstanceContainer& GetDefaultExecutionRuntimeData() const` — @return Default execution runtime data.
- L166 _public function_ `TConstArrayView<FStateTreeExternalDataDesc> GetExternalDataDescs() const` — @return List of external data required by the state tree
- L172 _public function_ `TConstArrayView<FStateTreeExternalDataDesc> GetContextDataDescs() const` — @return List of context data enforced by the schema that must be provided through the execution context.
- L178 _public prototype_ `bool HasCompatibleContextData(const UStateTree& Other) const;` — @return true if the other StateTree has compatible context data.
- L181 _public prototype_ `bool HasCompatibleContextData(TNotNull<const UStateTree*> Other) const;` — @return true if the other StateTree has compatible context data.
- L184 _public function_ `const FInstancedPropertyBag& GetDefaultParameters() const` — @return List of default parameters of the state tree. Default parameter values can be overridden at runtime by the execution context.
- L193 _public prototype_ `[[nodiscard]] bool IsReadyToRun() const;` — @return true if the tree asset can be used at runtime. @note the asset can be in the compilation queue. This will make sure it is up to date.
- L196 _public function_ `const UStateTreeSchema* GetSchema() const` — @return schema that was used to compile the StateTree.
- L202 _public prototype_ `const FCompactStateTreeFrame* GetFrameFromHandle(const FStateTreeStateHandle StateHandle) const;` — @return Pointer to a frame or null if frame not found.
- L205 _public prototype_ `const FCompactStateTreeState* GetStateFromHandle(const FStateTreeStateHandle StateHandle) const;` — @return Pointer to a state or null if state not found
- L208 _public prototype_ `FStateTreeStateHandle GetStateHandleFromId(const FGuid Id) const;` — @return State handle matching a given Id; invalid handle if state not found.
- L228 _public prototype_ `FStateTreeStateHandle GetStateHandleFromGameplayTag(const FGameplayTag Tag, EStateGameplayTagQueryMethod QueryMethod) const;` — Get state handle by gameplay tag. States with same tag are searched in breadth first order. @param Tag Gameplay tags to query @param QueryMethod how to query tags @return State handle matching a given gameplay tag
- L231 _public prototype_ `FGuid GetStateIdFromHandle(const FStateTreeStateHandle Handle) const;` — @return ID of the state matching a given state handle; invalid Id if state not found.
- L234 _public prototype_ `FConstStructView GetNode(const int32 NodeIndex) const;` — @return Struct view of the node matching a given node index; invalid view if state not found.
- L237 _public function_ `const FInstancedStructContainer& GetNodes() const` — @return Struct views of all nodes
- L243 _public function_ `const uint16 GetGlobalEvaluatorsBegin() const` — @return index to first global evaluator in GetNodes
- L249 _public function_ `const uint16 GetGlobalEvaluatorsNum() const` — @return number of global evaluators.
- L255 _public function_ `const uint16 GetGlobalTasksBegin() const` — @return index to first global tasks in GetNodes
- L261 _public function_ `const uint16 GetGlobalTasksNum() const` — @return number of global tasks.
- L267 _public prototype_ `FStateTreeIndex16 GetNodeIndexFromId(const FGuid Id) const;` — @return Node index matching a given Id; invalid index if node not found.
- L270 _public prototype_ `FGuid GetNodeIdFromIndex(const FStateTreeIndex16 NodeIndex) const;` — @return Id of the node matching a given node index; invalid Id if node not found.
- L273 _public function_ `TConstArrayView<FCompactStateTreeState> GetStates() const` — @return View of all states.
- L279 _public prototype_ `const FCompactStateTransition* GetTransitionFromIndex(const FStateTreeIndex16 TransitionIndex) const;` — @return Pointer to the transition at a given index; null if not found.
- L282 _public prototype_ `FStateTreeIndex16 GetTransitionIndexFromId(const FGuid Id) const;` — @return Runtime transition index matching a given Id; invalid index if node not found.
- L285 _public prototype_ `FGuid GetTransitionIdFromIndex(const FStateTreeIndex16 Index) const;` — @return Id of the transition matching a given runtime transition index; invalid Id if transition not found.
- L288 _public function_ `const FStateTreePropertyBindings& GetPropertyBindings() const` — @return Property bindings
- L294 _public function_ `TConstArrayView<UStateTreeExtension*> GetExtensions() const` — @return View of all extensions.
- L300 _public function_ `TConstArrayView<UE::StateTree::FTaskCompletionDispatcher> GetTaskCompletionDispatchers() const` — @return View of all task completion dispatchers.
- L307 _public function_ `template<typename ExtensionType> const ExtensionType* GetExtension() const` — Find the first extension of the requested type.
- L314 _public prototype_ `const UStateTreeExtension* K2_GetExtension(TSubclassOf<UStateTreeExtension> ExtensionType) const;` — `UFUNCTION(BlueprintCallable, Category = "StateTree|Extension", Meta = (DisplayName="Get Extension", DeterminesOutputType = "ExtensionType"))` — Find the first extension of the requested type.
- L317 _public function_ `bool DoesRequestTickGlobalTasks(bool bHasEvents) const` — @return True if there is any global tasks need ticking.
- L323 _public function_ `bool ShouldTickGlobalTasks(bool bHasEvents) const` — @return True if there is any global tasks that ticks.
- L329 _public function_ `bool IsScheduledTickAllowed() const` — @return true if the tree can use the scheduled tick feature.
- L335 _public function_ `EStateTreeStateSelectionRules GetStateSelectionRules() const` — @return the rules used by the execution context for selecting states.
- L342 _public prototype_ `void ResetCompiled();` — Resets the compiled data to empty.
- L349 _public prototype_ `void MarkAsModified(bool bPubliclyModified);` — Mark the state tree dirty. It will require the StateTree to be compiled before it can be used. @param bPubliclyModified Whether to also mark the public dependency dirty. It will affect the other asset that references the StateTree asset.
- L352 _public prototype_ `[[nodiscard]] bool IsEditorDataDirty() const;` — @return whether the state tree asset is dirty and needs to be compiled.
- L355 _public prototype_ `void CompileIfChanged();` — Compile the state tree if the editor data as changed since the last compilation.
- L358 _public prototype_ `TArray<FStateTreeMemoryUsage> CalculateEstimatedMemoryUsage() const;` — Calculates runtime memory usage for different sections of the tree.
- L362 _public function_ `void OnPreBeginPIE(const bool bIsSimulating)` — Called when the editor is preparing to start a pie session.
- L367 _public member_ `static const int32 LatestCustomAssetSavedVersion;` — The expected result of GetAssetSavedVersion. If the values do not match, the UI will suggest saving the asset.
- L370 _public function_ `int32 GetAssetSavedVersion() const` — Custom asset version to notify the user when the package needs to be resaved.
- L378 _public prototype_ `[[nodiscard]] FString DebugInternalLayoutAsString() const;` — @return the internal content of the state tree compiled asset.
- L384 _public member_ `TObjectPtr<UObject> EditorData;` — `UPROPERTY()` — Edit time data for the StateTree, instance of UStateTreeEditorData
- L387 _public member_ `FDelegateHandle OnObjectsReinstancedHandle;` — `UE_DEPRECATED(5.7, "Use the compiler manager.")`
- L389 _public member_ `FDelegateHandle OnUserDefinedStructReinstancedHandle;` — `UE_DEPRECATED(5.7, "Use the compiler manager.")`
- L391 _public member_ `FDelegateHandle OnPreBeginPIEHandle;` — `UE_DEPRECATED(5.7, "Use the compiler manager.")`
- L396 _public member_ `uint32 LastCompiledEditorDataHash = 0;` — `UPROPERTY()` — Hash of the editor data from last compile. Also used to detect mismatching events from recorded traces.
- L404 _protected prototype_ `[[nodiscard]] bool Link();` — Resolves references between data in the StateTree. @return true if all references to internal and external data are resolved properly, false otherwise.
- L406 _protected prototype_ `virtual void PostLoad() override;`
- L409 _protected prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L410 _protected prototype_ `static void AppendToClassSchema(FAppendToClassSchemaContext& Context);`
- L412 _protected prototype_ `virtual void Serialize(FStructuredArchiveRecord Record) override;`
- L415 _protected prototype_ `virtual void BeginDestroy() override;`
- L416 _protected prototype_ `virtual void PostInitProperties() override;`
- L420 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext Context) override;`
- L421 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L422 _protected prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L423 _protected prototype_ `void BeginCacheForCookedPlatformData(const ITargetPlatform* TargetPlatform) override;`
- L425 _protected prototype_ `virtual void ThreadedPostLoadAssetRegistryTagsOverride(FPostLoadAssetRegistryTagsContext& Context) const override;`
- L427 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L430 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L437 _private prototype_ `void ResetLinked();` — Reset the data generated by Link(), this in turn will cause IsReadyToRun() to return false. Used during linking, or to invalidate the linked data when data version is old (requires recompile).
- L440 _private prototype_ `bool ValidateInstanceData();` — @return true if all the source instance data types match with the node's instance data types
- L443 _private prototype_ `void UpdateRuntimeFlags();` — Set StateTree's flag that can't be set when compiled.
- L445 _private prototype_ `bool PatchBindings();`
- L451 _private member_ `TObjectPtr<UStateTreeSchema> Schema = nullptr;` — `UPROPERTY(Instanced)` — Schema used to compile the StateTree.
- L455 _private member_ `TArray<FCompactStateTreeFrame> Frames;` — `UPROPERTY()` — Runtime frames
- L459 _private member_ `TArray<FCompactStateTreeState> States;` — `UPROPERTY()` — Runtime states, root state at index 0
- L463 _private member_ `TArray<FCompactStateTransition> Transitions;` — `UPROPERTY()` — Runtime transitions.
- L467 _private member_ `FInstancedStructContainer Nodes;` — `UPROPERTY()` — Evaluators, Tasks, Condition and Consideration nodes.
- L471 _private member_ `FStateTreeInstanceData DefaultInstanceData;` — `UPROPERTY()` — Default node instance data (e.g. evaluators, tasks).
- L475 _private member_ `UE::StateTree::InstanceData::FInstanceContainer DefaultEvaluationScopeInstanceData;` — `UPROPERTY()` — Default node instance data for evaluation scope (e.g. conditions, considerations, functions)
- L479 _private member_ `UE::StateTree::InstanceData::FInstanceContainer DefaultExecutionRuntimeData;` — `UPROPERTY()` — Default node execution runtime data for execution runtime (e.g. tasks, conditions, considerations, functions)
- L483 _private member_ `FStateTreeInstanceData SharedInstanceData;` — `UPROPERTY()` — Shared node instance data (e.g. conditions, considerations).
- L485 _private member_ `mutable FTransactionallySafeRWLock PerThreadSharedInstanceDataLock;`
- L486 _private member_ `mutable TArray<TSharedPtr<FStateTreeInstanceData>> PerThreadSharedInstanceData;`
- L490 _private member_ `TArray<FStateTreeExternalDataDesc> ContextDataDescs;` — `UPROPERTY()` — List of names external data enforced by the schema, created at compilation.
- L493 _private member_ `FStateTreePropertyBindings PropertyBindings;` — `UPROPERTY()`
- L495 _private typedef_ `using FMemoryRequirement = UE::StateTree::InstanceData::FEvaluationScopeInstanceContainer::FMemoryRequirement;`
- L497 _private member_ `TArray<FMemoryRequirement> PropertyFunctionEvaluationScopeMemoryRequirements;` — The amount of memory used by property binding copy info batch for property function.
- L501 _private member_ `TArray<UE::StateTree::FTaskCompletionDispatcher> TaskCompletionDispatchers;` — `UPROPERTY()` — Task completion dispatchers.
- L505 _private member_ `TArray<TObjectPtr<UStateTreeExtension>> Extensions;` — `UPROPERTY()` — The asset extensions. A place to add extra information for plugins.
- L509 _private member_ `TArray<FStateTreeStateIdToHandle> IDToStateMappings;` — `UPROPERTY()` — Mapping of state guid for the Editor and state handles, created at compilation.
- L513 _private member_ `TArray<FStateTreeNodeIdToIndex> IDToNodeMappings;` — `UPROPERTY()` — Mapping of node guid for the Editor and node index, created at compilation.
- L517 _private member_ `TArray<FStateTreeTransitionIdToIndex> IDToTransitionMappings;` — `UPROPERTY()` — Mapping of state transition identifiers and runtime compact transition index, created at compilation.
- L525 _private member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY()` — Parameters that could be used for bindings within the Tree. Default values are stored within the asset but StateTreeReference can be used to parameterized the tree. @see FStateTreeReference
- L530 _private member_ `TArray<FStateTreeExternalDataDesc> ExternalDataDescs;` — `UPROPERTY(Transient)` — List of external data required by the state tree, created during linking.
- L534 _private member_ `uint32 CompletionGlobalTasksMask = 0;` — `UPROPERTY()` — Mask used to test the global tasks completion.
- L538 _private member_ `uint16 NumContextData = 0;` — `UPROPERTY()` — Number of context data, include parameters and all context data.
- L542 _private member_ `uint16 NumGlobalInstanceData = 0;` — `UPROPERTY()` — Number of global instance data.
- L546 _private member_ `uint16 EvaluatorsBegin = 0;` — `UPROPERTY()` — Index of first evaluator in Nodes.
- L550 _private member_ `uint16 EvaluatorsNum = 0;` — `UPROPERTY()` — Number of evaluators.
- L554 _private member_ `uint16 GlobalTasksBegin = 0;` — `UPROPERTY()` — Index of first global task in Nodes.
- L558 _private member_ `uint16 GlobalTasksNum = 0;` — `UPROPERTY()` — Number of global tasks.
- L561 _private member_ `EStateTreeStateSelectionRules StateSelectionRules = EStateTreeStateSelectionRules::Default;` — The cached value of UStateTreeSchema::GetStateSelectionRules
- L565 _private member_ `EStateTreeTaskCompletionType CompletionGlobalTasksControl = EStateTreeTaskCompletionType::Any;` — `UPROPERTY()` — How the global tasks control the completion of the frame.
- L569 _private member_ `EStateTreeParameterDataType ParameterDataType = EStateTreeParameterDataType::GlobalParameterData;` — `UPROPERTY()` — The parameter data type used by the schema.
- L584 _private member_ `ECompileStatus CompileStatus = ECompileStatus::Link;` — The current state of the asset. The compilation could have failed or is pending (in the compiler queue). This is different from EditorDataDirtyStatus. The compilation/link could have failed but the data didn't change since the last compilation/link.
- L602 _private member_ `EDirtyStatus EditorDataDirtyStatus = EDirtyStatus::None;` — Whether the editor data dirtied since the last compilation. After a compilation (success or failure), the dirty status returns to none.
- L605 _private member_ `bool bCompilationPending = false;` — The asset compilation was requested. The asset is in the pending queue.
- L610 _private member_ `uint8 bHasGlobalTransitionTasks : 1 = false;` — `UPROPERTY()` — True if any global task is a transition task.
- L616 _private member_ `uint8 bHasGlobalTickTasks : 1 = false;` — True if any global task has bShouldCallTick. Not ticking implies no property copy.
- L623 _private member_ `uint8 bHasGlobalTickTasksOnlyOnEvents : 1 = false;` — True if any global task has bShouldCallTickOnlyOnEvents. No effect if bHasGlobalTickTasks is true. Not ticking implies no property copy.
- L626 _private member_ `uint8 bCachedRequestGlobalTick : 1 = false;` — True if any global tasks request a tick every frame.
- L632 _private member_ `uint8 bCachedRequestGlobalTickOnlyOnEvents : 1 = false;` — True if any global tasks request a tick every frame but only if there are events. No effect if bCachedRequestGlobalTick is true.
- L635 _private member_ `uint8 bScheduledTickAllowed : 1 = false;` — True when the scheduled tick is allowed by the schema.
- L639 _private member_ `TSet<FObjectKey> OutOfDateStructs;` — List of Struct that are out of date and waiting to be replaced with the new instance.
- L643 _private member_ `int32 CustomAssetSavedVersion = 0;` — `UPROPERTY()` — The custom version number the package was last saved with.
- L667 _private member_ `TArray<FDebugInstanceData> GCObjectDatas;`
- L668 _private member_ `FDelegateHandle PreGCHandle;`
- L669 _private member_ `FDelegateHandle PostGCHandle;`
- L671 _private prototype_ `void HandleRuntimeValidationPreGC();`
- L672 _private prototype_ `void HandleRuntimeValidationPostGC();`

#### enum `UStateTree::EStateGameplayTagQueryMethod`  
`enum class EStateGameplayTagQueryMethod`  
_L213-220_
- desc: Determines how we match a state gameplay tag
- L216 _public enumerator_ `Includes` — Foo matches both Foo and Foo.Bar. Foo.Bar does not match Foo.
- L219 _public enumerator_ `MatchesExact` — Foo only matches Foo. Foo does not match Foo.Bar. Foo.Bar does not match Foo

#### enum `UStateTree::ECompileStatus`  
`enum class ECompileStatus : uint8`  
_L571-577_
- L573 _public enumerator_ `Public` — The exported dependencies need to be compiled.
- L574 _public enumerator_ `Internal` — The public compiled and the internal dependencies need to be compiled.
- L575 _public enumerator_ `Link` — Compiled and not yet link.
- L576 _public enumerator_ `Executable` — Compiled and ready to use.

#### enum `UStateTree::EDirtyStatus`  
`enum class EDirtyStatus : uint8`  
_L587-597_
- L589 _public enumerator_ `Public` — Publicly produced dependencies changed since the last compilation.
- L590 _public enumerator_ `Internal` — Internal/Private nodes/properties changed since the last compilation.
- L594 _public enumerator_ `Link` — A new task is considered a modification. A property value changed on a task is considered a modification. A BP task that added a property is not considered a modification. It wouldn't affect the compilation result.
- L596 _public enumerator_ `None` — A BP task that removed a property and that property had a binding is not considered a modification.

#### struct `UStateTree::FDebugInstanceData`  
`struct FDebugInstanceData`  
_L649-666_
- L651 _public member_ `FWeakObjectPtr Object;`
- L652 _public member_ `int32 InstanceDataStructIndex = INDEX_NONE;`
- L653 _public member_ `int32 SharedInstanceDataIndex = INDEX_NONE;`
- L659 _public member_ `EContainer Container = EContainer::DefaultInstance;`
- L665 _public member_ `EObjectType Type = EObjectType::ObjectInstance;`

#### enum `UStateTree::FDebugInstanceData::EContainer`  
`enum class EContainer : uint8`  
_L654-658_
- L656 _public enumerator_ `DefaultInstance`
- L657 _public enumerator_ `SharedInstance`

#### enum `UStateTree::FDebugInstanceData::EObjectType`  
`enum class EObjectType : uint8`  
_L660-664_
- L662 _public enumerator_ `ObjectInstance`
- L663 _public enumerator_ `Struct`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API STATETREEMODULE_API`
- L86 _namespace_ `namespace UE`
- L86 _namespace_ `namespace StateTree` (scope `UE`)
- L86 _namespace_ `namespace Compiler` (scope `UE::StateTree`)
- L94 _prototype_ `extern void RenameObjectToTransientPackage(TNotNull<UObject*> ObjectToRename, FStringView Name = nullptr);` (scope `UE::StateTree::Compiler`) — Helper method to correctly rename a no longer needed object. @param ObjectToRename - Object to be renamed, will have flags updated & export invalidated @param Name - New name of the object. Null by default which means it will only get moved to transient outer.
- L97 _namespace_ `namespace UE`
- L97 _namespace_ `namespace StateTree` (scope `UE`)
- L97 _namespace_ `namespace Compiler` (scope `UE::StateTree`)
- L97 _namespace_ `namespace Private` (scope `UE::StateTree::Compiler`)
- L124 _namespace_ `namespace UE`
- L124 _namespace_ `namespace StateTree` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeAnyEnum.h` (Public)


#### struct `FStateTreeAnyEnum`  
`struct FStateTreeAnyEnum`  
_L11-39_
- reflection: `USTRUCT()`
- desc: Enum that can be any type in the UI. Helper class to deal with any enum in property binding.
- L15 _public function_ `bool operator==(const FStateTreeAnyEnum& RHS) const`
- L20 _public function_ `bool operator!=(const FStateTreeAnyEnum& RHS) const`
- L26 _public function_ `void Initialize(UEnum* NewEnum)` — Initializes the class and value to specific enum. The value is set to the first value of the enum or 0 if class is null
- L34 _public member_ `uint32 Value = 0;` — `UPROPERTY(EditAnywhere, Category = Enum)` — The enum integer value.
- L38 _public member_ `TObjectPtr<UEnum> Enum = nullptr;` — `UPROPERTY(EditAnywhere, Category = Enum)` — The enum class associated with this enum.

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeAsyncExecutionContext.h` (Public)


#### struct `UE::StateTree::Async::FActivePathInfo`  
`struct FActivePathInfo`  
_L29-42_
- L31 _public function_ `bool IsValid() const`
- L36 _public prototype_ `const FStateTreeNodeBase& GetNode() const;`
- L38 _public member_ `FStateTreeExecutionFrame* Frame = nullptr;`
- L39 _public member_ `FStateTreeExecutionFrame* ParentFrame = nullptr;`
- L40 _public member_ `FStateTreeStateHandle StateHandle;`
- L41 _public member_ `FStateTreeIndex16 NodeIndex;`

#### struct `TStateTreeStrongExecutionContext`  
`template<bool bWithWriteAccess> struct TStateTreeStrongExecutionContext`  
_L60-242_
- desc: Execution context to interact with the state tree instance data asynchronously. It should only be allocated on the stack. You are responsible for making it thread-safe if needed. ThreadSafeAsyncCallback.AddLambda( [MyTag, WeakContext = Context.MakeWeakExecutionContext()]() { TStateTreeStrongExecutionContext<true> StrongContext = WeakContext.CreateStrongContext(); if (StrongContext.SendEvent()) { ... } });
- L62 _public prototype_ `TStateTreeStrongExecutionContext() = default;`
- L63 _public prototype_ `explicit TStateTreeStrongExecutionContext(const FStateTreeWeakExecutionContext& WeakContext);`
- L64 _public prototype_ `~TStateTreeStrongExecutionContext();`
- L66 _public prototype_ `TStateTreeStrongExecutionContext(const TStateTreeStrongExecutionContext& Other) = delete;`
- L67 _public prototype_ `TStateTreeStrongExecutionContext& operator=(const TStateTreeStrongExecutionContext& Other) = delete;`
- L70 _public function_ `TStrongObjectPtr<UObject> GetOwner() const` — @return The owner of the context
- L76 _public function_ `TStrongObjectPtr<const UStateTree> GetStateTree() const` — @return the StateTree asset in use.
- L82 _public function_ `TSharedPtr<const FStateTreeInstanceStorage> GetStorage() const` — @return the Instance Storage.
- L88 _public function_ `TSharedPtr<const UE::StateTree::ExecutionContext::ITemporaryStorage> GetTemporaryStorage() const` — @return the Temporary Storage.
- L97 _public prototype_ `bool SendEvent(const FGameplayTag Tag, const FConstStructView Payload = FConstStructView(), const FName Origin = FName()) const requires bWithWriteAccess;` — Sends event for the StateTree. @return false if the context is not valid or the event could not be sent.
- L109 _public prototype_ `bool RequestTransition(FStateTreeStateHandle TargetState, EStateTreeTransitionPriority Priority = EStateTreeTransitionPriority::Normal, EStateTreeSelectionFallback Fallback = EStateTreeSelectionFallback::None) const requires bWithWriteAccess;` — Requests transition to a state. If called during transition processing (e.g. from FStateTreeTaskBase::TriggerTransitions()) the transition is attempted to be activated immediately (it can fail e.g. because of preconditions on a target state). If called outside the transition handling, the request is buffered and handled at the beginning of next transition processing. @param TargetState The state to transition to. @param Priority The priority of the transition. @param Fallback of the transition if it fails to select the target state. @return false if the context is not valid or doesn't have a valid frame anymore or the request failed.
- L116 _public prototype_ `bool BroadcastDelegate(const FStateTreeDelegateDispatcher& Dispatcher) const requires bWithWriteAccess;` — Broadcasts the delegate. It executes bound delegates immediately and triggers bound transitions (when transitions are evaluated). @return false if the context is not valid or doesn't have a valid frame anymore or the broadcast failed.
- L124 _public prototype_ `bool BindDelegate(const FStateTreeDelegateListener& Listener, FSimpleDelegate Delegate) const requires bWithWriteAccess;` — Registers the delegate to the listener. If the listener was previously registered, then unregister it first before registering it again with the new delegate callback. The listener is bound to a dispatcher in the editor. @return false if the context is not valid or doesn't have a valid frame anymore or the bind failed.
- L130 _public prototype_ `bool UnbindDelegate(const FStateTreeDelegateListener& Listener) const requires bWithWriteAccess;` — Unregisters the callback bound to the listener. @return false if the context is not valid or the unbind failed.
- L138 _public prototype_ `bool FinishTask(EStateTreeFinishTaskType FinishType) const requires bWithWriteAccess;` — Finishes a task. If called during tick processing, then the state completes immediately. If called outside of the tick processing, then the request is buffered and handled on the next tick. @return false if the context is not valid or doesn't have a valid frame anymore or finish task failed.
- L144 _public prototype_ `bool UpdateScheduledTickRequest(UE::StateTree::FScheduledTickHandle Handle, FStateTreeScheduledTick ScheduledTick) const requires bWithWriteAccess;` — Updates the scheduled tick of a previous request. @return false if the context is not valid.
- L151 _public function_ `template<typename T> std::conditional_t<bWithWriteAccess, T*, const T*> GetInstanceDataPtr() const&` — Get the Instance Data of recorded node. Only callable on lvalue because it would have lost the access track. @return nullptr if the frame or state containing the node is no longer active.
- L163 _public prototype_ `template<typename T> std::conditional_t<bWithWriteAccess, T*, const T*> GetInstanceDataPtr() const&& = delete;`
- L170 _public function_ `template<typename T> std::conditional_t<bWithWriteAccess, T*, const T*> GetExecutionRuntimeDataPtr() const&` — Get the Execution Runtime Data of recorded node. Only callable on lvalue because it would have lost the access track. @return nullptr if the frame or state containing the node is no longer active.
- L182 _public prototype_ `template<typename T> std::conditional_t<bWithWriteAccess, T*, const T*> GetExecutionRuntimeDataPtr() const&& = delete;`
- L191 _public prototype_ `bool CopyInputBindings() const requires bWithWriteAccess;` — Copies the input bindings for the recorded node. Propagates data FROM bound sources INTO the node's instance data (similar to what happens before Tick in normal execution). Binding sources requiring context or external data are not available in async context and are skipped (and returns false). Batches that include property functions cannot be evaluated without a full FStateTreeExecutionContext. @return true if all bindings are copied.
- L200 _public prototype_ `bool CopyOutputBindings() const requires bWithWriteAccess;` — Copies the output bindings for the recorded node. Propagates data FROM the node's instance data BACK to bound targets (similar to what happens after Tick in normal execution). Output binding batches never contain property functions, so this call is always async-safe. Binding targets requiring context or external data are skipped. @return true if all bindings are copied.
- L206 _public prototype_ `UE::StateTree::Async::FActivePathInfo GetActivePathInfo() const;` — Get the info of active frame, state and node this Context is based on @return an invalid FActivePathInfo if the frame or state containing the node is no longer active.
- L213 _public function_ `bool IsValid() const` — Checks if the context is valid. Validity: Pinned Members are valid AND (WeakContext is created outside the ExecContext loop OR the recorded frame and state are still active) @return false if the context is not valid.
- L220 _private function_ `bool IsValidInstanceStorage() const`
- L225 _private prototype_ `FStateTreeDataView GetInstanceDataPtrInternal() const;`
- L226 _private prototype_ `FStateTreeDataView GetExecutionRuntimeDataPtrInternal() const;`
- L227 _private prototype_ `bool CopyBindingBatchForAsync(const FStateTreeExecutionFrame* CurrentFrame, const FStateTreeDataView TargetView, const FStateTreeIndex16 BindingsBatch) const requires bWithWriteAccess;`
- L229 _private prototype_ `static void ScheduleNextTick(TNotNull<UObject*> Owner, TNotNull<const UStateTree*> RootStateTree, FStateTreeInstanceStorage& Storage, UE::StateTree::ETickReason Reason) requires bWithWriteAccess;`
- L231 _private member_ `TStrongObjectPtr<UObject> Owner;`
- L232 _private member_ `TStrongObjectPtr<const UStateTree> StateTree;`
- L233 _private member_ `TSharedPtr<FStateTreeInstanceStorage> Storage;`
- L234 _private member_ `TSharedPtr<UE::StateTree::ExecutionContext::ITemporaryStorage> TemporaryStorage;`
- L236 _private member_ `UE::StateTree::FActiveFrameID FrameID;`
- L237 _private member_ `UE::StateTree::FActiveStateID StateID;`
- L238 _private member_ `FStateTreeIndex16 NodeIndex;`
- L239 _private member_ `uint8 bAccessAcquired : 1 = false;`

#### struct `FStateTreeWeakExecutionContext`  
`struct FStateTreeWeakExecutionContext`  
_L262-370_
- desc: Execution context that can be saved/copied and used asynchronously. You are responsible for making it thread-safe if needed. The context is valid if the state (or global context) from which it was created is still active. The owner, state tree, and storage also need to be valid. ThreadSafeAsyncCallback.AddLambda( [MyTag, WeakContext = Context.MakeWeakExecutionContext]() { if (WeakContext.SendEvent(MyTag)) { ... } });
- L268 _public prototype_ `FStateTreeWeakExecutionContext() = default;`
- L269 _public prototype_ `explicit FStateTreeWeakExecutionContext(const FStateTreeExecutionContext& Context);`
- L273 _public function_ `TStrongObjectPtr<UObject> GetOwner() const` — @return The owner of the context
- L279 _public function_ `TStrongObjectPtr<const UStateTree> GetStateTree() const` — @return the StateTree asset in use.
- L284 _public function_ `[[nodiscard]] FStateTreeStrongReadOnlyExecutionContext MakeStrongReadOnlyExecutionContext() const`
- L289 _public function_ `[[nodiscard]] FStateTreeStrongExecutionContext MakeStrongExecutionContext() const`
- L298 _public prototype_ `bool SendEvent(const FGameplayTag Tag, const FConstStructView Payload = FConstStructView(), const FName Origin = FName()) const;` — Sends event for the StateTree. @return false if the context is not valid or the event could not be sent.
- L310 _public prototype_ `bool RequestTransition(FStateTreeStateHandle TargetState, EStateTreeTransitionPriority Priority = EStateTreeTransitionPriority::Normal, EStateTreeSelectionFallback Fallback = EStateTreeSelectionFallback::None) const;` — Requests transition to a state. If called during transition processing (e.g. from FStateTreeTaskBase::TriggerTransitions()) the transition is attempted to be activated immediately (it can fail e.g. because of preconditions on a target state). If called outside the transition handling, the request is buffered and handled at the beginning of next transition processing. @param TargetState The state to transition to. @param Priority The priority of the transition. @param Fallback of the transition if it fails to select the target state. @return false if the context is not valid or doesn't have a valid frame anymore or the request failed.
- L317 _public prototype_ `bool BroadcastDelegate(const FStateTreeDelegateDispatcher& Dispatcher) const;` — Broadcasts the delegate. It executes bound delegates immediately and triggers bound transitions (when transitions are evaluated). @return false if the context is not valid or doesn't have a valid frame anymore or the broadcast failed.
- L325 _public prototype_ `bool BindDelegate(const FStateTreeDelegateListener& Listener, FSimpleDelegate Delegate) const;` — Registers the delegate to the listener. If the listener was previously registered, then unregister it first before registering it again with the new delegate callback. The listener is bound to a dispatcher in the editor. @return false if the context is not valid or doesn't have a valid frame anymore or the bind failed.
- L329 _public prototype_ `bool BindDelegate(const FStateTreeWeakTaskRef& Task, const FStateTreeDelegateListener& Listener, FSimpleDelegate Delegate) const;` — `UE_DEPRECATED(5.6, "Use the version without FStateTreeWeakTaskRef")`
- L334 _public prototype_ `bool RemoveDelegateListener(const FStateTreeDelegateListener& Listener) const;` — Removes Delegate Listener.
- L340 _public prototype_ `bool UnbindDelegate(const FStateTreeDelegateListener& Listener) const;` — Unregisters the callback bound to the listener. @return false if the context is not valid or the unbind failed.
- L348 _public prototype_ `bool FinishTask(EStateTreeFinishTaskType FinishType) const;` — Finishes a task. If called during tick processing, then the state completes immediately. If called outside of the tick processing, then the request is buffered and handled on the next tick. @return false if the context is not valid or doesn't have a valid frame anymore or finish task failed.
- L352 _public prototype_ `bool FinishTask(const FStateTreeWeakTaskRef& Task, EStateTreeFinishTaskType FinishType) const;` — `UE_DEPRECATED(5.6, "Use the version without FStateTreeWeakTaskRef.")`
- L359 _public prototype_ `bool UpdateScheduledTickRequest(UE::StateTree::FScheduledTickHandle Handle, FStateTreeScheduledTick ScheduledTick) const;` — Updates the scheduled tick of a previous request. @return false if the context is not valid.
- L362 _private member_ `TWeakObjectPtr<UObject> Owner;`
- L363 _private member_ `TWeakObjectPtr<const UStateTree> StateTree;`
- L364 _private member_ `TWeakPtr<FStateTreeInstanceStorage> Storage;`
- L365 _private member_ `TWeakPtr<UE::StateTree::ExecutionContext::ITemporaryStorage> TemporaryStorage;`
- L367 _private member_ `UE::StateTree::FActiveFrameID FrameID;`
- L368 _private member_ `UE::StateTree::FActiveStateID StateID;`
- L369 _private member_ `FStateTreeIndex16 NodeIndex;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace StateTree` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace StateTree` (scope `UE`)
- L27 _namespace_ `namespace Async` (scope `UE::StateTree`)
- L244 _typedef_ `using FStateTreeStrongExecutionContext = TStateTreeStrongExecutionContext<true>;`
- L245 _typedef_ `using FStateTreeStrongReadOnlyExecutionContext = TStateTreeStrongExecutionContext<false>;`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeConditionBase.h` (Public)


#### enum `EStateTreeCompare`  
`enum class EStateTreeCompare : uint8`  
_L11-15_
- L13 _public enumerator_ `Default`
- L14 _public enumerator_ `Invert`

#### struct `FStateTreeConditionBase`  
`struct FStateTreeConditionBase : public FStateTreeNodeBase`  
_L21-75_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeNodeBase`
- desc: Base struct for all conditions.
- L26 _public function_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const` — @return True if the condition passes.
- L36 _public function_ `virtual void EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const` — Called when a new state is entered and task is part of active states. Note: The condition instance data is shared between all the uses a State Tree asset. You should not modify the instance data in this callback. @param Context Reference to current execution context. @param Transition Describes the states involved in the transition @return Succeed/Failed will end the state immediately and trigger to select new state, Running will carry on to tick the state.
- L45 _public function_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const` — Called when a current state is exited and task is part of active states. Note: The condition instance data is shared between all the uses a State Tree asset. You should not modify the instance data in this callback. @param Context Reference to current execution context. @param Transition Describes the states involved in the transition
- L56 _public function_ `virtual void StateCompleted(FStateTreeExecutionContext& Context, const EStateTreeRunStatus CompletionStatus, const FStateTreeActiveStates& CompletedActiveStates) const` — Called right after a state has been completed, but before new state has been selected. StateCompleted is called in reverse order to allow to propagate state to other Tasks that are executed earlier in the tree. Note that StateCompleted is not called if conditional transition changes the state. Note: The condition instance data is shared between all the uses a State Tree asset. You should not modify the instance data in this callback. @param Context Reference to current execution context. @param CompletionStatus Describes the running status of the completed state (Succeeded/Failed). @param CompletedActiveStates Active states at the time of completion.
- L59 _public member_ `EStateTreeExpressionOperand Operand = EStateTreeExpressionOperand::And;` — `UPROPERTY()`
- L62 _public member_ `int8 DeltaIndent = 0;` — `UPROPERTY()`
- L65 _public member_ `EStateTreeConditionEvaluationMode EvaluationMode = EStateTreeConditionEvaluationMode::Evaluated;` — `UPROPERTY()`
- L68 _public member_ `uint8 bHasShouldCallStateChangeEvents : 1 = false;` — If set to true, EnterState, ExitState, and StateCompleted are called on the condition.
- L74 _public member_ `uint8 bShouldStateChangeOnReselect : 1 = true;` — If set to true, the condition will receive EnterState/ExitState even if the state was previously active. Default value is true.

#### struct `FStateTreeConditionCommonBase`  
`struct FStateTreeConditionCommonBase : public FStateTreeConditionBase`  
_L82-85_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeConditionBase`
- desc: Base class (namespace) for all common Conditions that are generally applicable. This allows schemas to safely include all conditions child of this struct.

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeConsiderationBase.h` (Public)


#### struct `FStateTreeConsiderationBase`  
`struct FStateTreeConsiderationBase : public FStateTreeNodeBase`  
_L18-36_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeNodeBase`
- desc: This feature is experimental and the API is expected to change. Base struct for all utility considerations.
- L22 _public prototype_ `FStateTreeConsiderationBase();`
- L25 _public prototype_ `float GetNormalizedScore(FStateTreeExecutionContext& Context) const;`
- L28 _protected function_ `virtual float GetScore(FStateTreeExecutionContext& Context) const`
- L32 _public member_ `EStateTreeExpressionOperand Operand;` — `UPROPERTY()`
- L35 _public member_ `int8 DeltaIndent;` — `UPROPERTY()`

#### struct `FStateTreeConsiderationCommonBase`  
`struct FStateTreeConsiderationCommonBase : public FStateTreeConsiderationBase`  
_L43-46_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeConsiderationBase`
- desc: Base class (namespace) for all common Utility Considerations that are generally applicable. This allows schemas to safely include all considerations child of this struct.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeDelegate.h` (Public)


#### struct `FStateTreeDelegateDispatcher`  
`struct FStateTreeDelegateDispatcher`  
_L29-48_
- reflection: `USTRUCT(BlueprintType, meta = (NoBinding))`
- desc: StateTree's delegate dispatcher.
- L35 _public function_ `bool IsValid() const` — @return if dispatcher is valid.
- L40 _public prototype_ `bool operator==(const FStateTreeDelegateDispatcher&) const = default;`
- L41 _public prototype_ `bool operator!=(const FStateTreeDelegateDispatcher&) const = default;`
- L45 _private member_ `FGuid ID;` — `UPROPERTY()`

#### struct `FStateTreeDelegateListener`  
`struct FStateTreeDelegateListener`  
_L55-86_
- reflection: `USTRUCT(BlueprintType, meta = (NoPromoteToParameter))`
- desc: The receiver of a delegate binding. Can be bound in the editor to a delegate dispatcher.
- L61 _public function_ `FStateTreeDelegateDispatcher GetDispatcher() const` — @return the bound delegate.
- L67 _public function_ `bool IsValid() const` — @return if the listener is valid.
- L72 _public prototype_ `bool operator==(const FStateTreeDelegateListener&) const = default;`
- L73 _public prototype_ `bool operator!=(const FStateTreeDelegateListener&) const = default;`
- L79 _private member_ `FStateTreeDelegateDispatcher Dispatcher;` — `UPROPERTY()` — ID of the dispatcher that listener is or will be bound to.
- L83 _private member_ `int32 ID = 0;` — `UPROPERTY()` — The generated ID of the listener.

#### enum `UE::StateTree::ETaskCompletionCondition`  
`enum class ETaskCompletionCondition : uint8`  
_L96-101_
- reflection: `UENUM()`
- desc: Task completion event condition. Used to control when a task completion dispatcher is broadcast.
- L98 _public enumerator_ `Succeeds` — Broadcast only when task Succeeded
- L99 _public enumerator_ `Fails` — Broadcast only when task Failed (or Stopped for backward compatibility)
- L100 _public enumerator_ `Completes` — Broadcast on either Succeeded or Failed (or Stopped for backward compatibility)

#### struct `UE::StateTree::FTaskCompletionDispatcher`  
`struct FTaskCompletionDispatcher`  
_L108-127_
- reflection: `USTRUCT()`
- desc: Task completion dispatcher entry compiled into the state tree asset. Maps a task node to a dispatcher that is broadcast when the task completes.
- L115 _public member_ `FStateTreeDelegateDispatcher Dispatcher;` — `UPROPERTY()` — The dispatcher GUID to broadcast (auto-generated at compile time)
- L119 _public member_ `FStateTreeIndex16 TaskNodeIndex;` — `UPROPERTY()` — Index of the task node in UStateTree::Nodes[]
- L123 _public member_ `ETaskCompletionCondition Condition = ETaskCompletionCondition::Completes;` — `UPROPERTY()` — Condition for when to broadcast (Succeeds/Fails/Completes)
- L125 _public prototype_ `bool operator==(const UE::StateTree::FTaskCompletionDispatcher&) const = default;`
- L126 _public prototype_ `bool operator!=(const UE::StateTree::FTaskCompletionDispatcher&) const = default;`

#### Free symbols / members of external scopes

- L88 _namespace_ `namespace UE`
- L88 _namespace_ `namespace StateTree` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeDelegates.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STATETREEMODULE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace StateTree` (scope `UE`)
- L13 _namespace_ `namespace Delegates` (scope `UE::StateTree`)
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIdentifierChanged, const UStateTree& );` — Called when linkable name in a StateTree has changed.
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIdentifierChanged, const UStateTree& );` (scope `UE::StateTree::Delegates`) — Called when linkable name in a StateTree has changed.
- L20 _externvar_ `extern FOnIdentifierChanged OnIdentifierChanged;` (scope `UE::StateTree::Delegates`)
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSchemaChanged, const UStateTree& );` — Called when schema of the StateTree EditorData has changed. This is used to refresh the asset editor. Note that this is NOT called when updating the StateTree schema from the EditorData on successful compilation.
- L27 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSchemaChanged, const UStateTree& );` (scope `UE::StateTree::Delegates`) — Called when schema of the StateTree EditorData has changed. This is used to refresh the asset editor. Note that this is NOT called when updating the StateTree schema from the EditorData on successful compilation.
- L28 _externvar_ `extern FOnSchemaChanged OnSchemaChanged;` (scope `UE::StateTree::Delegates`)
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnParametersChanged, const UStateTree& );` — Called when parameters of the StateTree EditorData changed. This should mainly be used by the asset editor to maintain consistency in the UI for manipulations on the EditorData until the tree gets compiled.
- L35 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnParametersChanged, const UStateTree& );` (scope `UE::StateTree::Delegates`) — Called when parameters of the StateTree EditorData changed. This should mainly be used by the asset editor to maintain consistency in the UI for manipulations on the EditorData until the tree gets compiled.
- L36 _externvar_ `extern FOnParametersChanged OnParametersChanged;` (scope `UE::StateTree::Delegates`)
- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStateParametersChanged, const UStateTree& , const FGuid );` — Called when parameters of a StateTree State changed. This should mainly be used by the asset editor to maintain consistency in the UI for manipulations.
- L42 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStateParametersChanged, const UStateTree& , const FGuid );` (scope `UE::StateTree::Delegates`) — Called when parameters of a StateTree State changed. This should mainly be used by the asset editor to maintain consistency in the UI for manipulations.
- L43 _externvar_ `extern FOnStateParametersChanged OnStateParametersChanged;` (scope `UE::StateTree::Delegates`)
- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGlobalDataChanged, const UStateTree& );` — Called when Global Tasks or Evaluators of the StateTree EditorData changed. This should mainly be used by the asset editor to maintain consistency in the UI for manipulations on the EditorData.
- L49 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGlobalDataChanged, const UStateTree& );` (scope `UE::StateTree::Delegates`) — Called when Global Tasks or Evaluators of the StateTree EditorData changed. This should mainly be used by the asset editor to maintain consistency in the UI for manipulations on the EditorData.
- L50 _externvar_ `extern FOnGlobalDataChanged OnGlobalDataChanged;` (scope `UE::StateTree::Delegates`)
- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisualThemeChanged, const UStateTree& );` — Called when the theme colors change. This should mainly be used by the asset editor to maintain consistency in the UI for manipulations on the EditorData.
- L56 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisualThemeChanged, const UStateTree& );` (scope `UE::StateTree::Delegates`) — Called when the theme colors change. This should mainly be used by the asset editor to maintain consistency in the UI for manipulations on the EditorData.
- L57 _externvar_ `extern FOnVisualThemeChanged OnVisualThemeChanged;` (scope `UE::StateTree::Delegates`)
- L63 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBreakpointsChanged, const UStateTree& );` — Called when breakpoints of the StateTree EditorData changed. This should mainly be used by the asset editor to update the debugger.
- L63 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBreakpointsChanged, const UStateTree& );` (scope `UE::StateTree::Delegates`) — Called when breakpoints of the StateTree EditorData changed. This should mainly be used by the asset editor to update the debugger.
- L64 _externvar_ `extern FOnBreakpointsChanged OnBreakpointsChanged;` (scope `UE::StateTree::Delegates`)
- L67 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostCompile, const UStateTree& );` — Called when the state tree compiles.
- L67 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostCompile, const UStateTree& );` (scope `UE::StateTree::Delegates`) — Called when the state tree compiles.
- L68 _externvar_ `extern FOnPostCompile OnPostCompile;` (scope `UE::StateTree::Delegates`)
- L73 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnRequestCompile, UStateTree& );` — Request StateTree compilation.
- L73 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnRequestCompile, UStateTree& );` (scope `UE::StateTree::Delegates`) — Request StateTree compilation.
- L75 _externvar_ `extern FOnRequestCompile OnRequestCompile;` (scope `UE::StateTree::Delegates`) — `UE_DEPRECATED(5.8, "Use the UStateTreeEditingSubsystem to trigger a compilation.")`
- L79 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(uint32, FOnRequestEditorHash, const UStateTree& );` — Request the editor hash of the given state tree.
- L79 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(uint32, FOnRequestEditorHash, const UStateTree& );` (scope `UE::StateTree::Delegates`) — Request the editor hash of the given state tree.
- L80 _externvar_ `extern FOnRequestEditorHash OnRequestEditorHash;` (scope `UE::StateTree::Delegates`)
- L87 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTracingStateChanged, EStateTreeTraceStatus);` — Called by the StateTree module when StateTree traces are enabled/disabled.
- L87 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTracingStateChanged, EStateTreeTraceStatus);` (scope `UE::StateTree::Delegates`) — Called by the StateTree module when StateTree traces are enabled/disabled.
- L88 _externvar_ `extern FOnTracingStateChanged OnTracingStateChanged;` (scope `UE::StateTree::Delegates`)
- L95 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTraceAnalysisStateChanged, EStateTreeTraceAnalysisStatus);` — Called by the StateTree module when StateTree traces analysis is started/stopped.
- L95 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTraceAnalysisStateChanged, EStateTreeTraceAnalysisStatus);` (scope `UE::StateTree::Delegates`) — Called by the StateTree module when StateTree traces analysis is started/stopped.
- L96 _externvar_ `extern FOnTraceAnalysisStateChanged OnTraceAnalysisStateChanged;` (scope `UE::StateTree::Delegates`)
- L99 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTracingTimelineScrubbed, const double );` — Called by the StateTree module whenever tracing timeline is scrubbed on Rewind Debugger
- L99 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTracingTimelineScrubbed, const double );` (scope `UE::StateTree::Delegates`) — Called by the StateTree module whenever tracing timeline is scrubbed on Rewind Debugger
- L100 _externvar_ `extern FOnTracingTimelineScrubbed OnTracingTimelineScrubbed;` (scope `UE::StateTree::Delegates`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeEvaluationScopeInstanceContainer.h` (Public)


#### struct `UE::StateTree::InstanceData::FEvaluationScopeInstanceContainer`  
`struct FEvaluationScopeInstanceContainer`  
_L16-123_
- desc: Container of instance data for evaluation scope data. The memory is pre-allocated and only available for a short amount of time.
- L20 _public typedef_ `using FMemoryRequirement = UE::StateTree::InstanceData::FEvaluationScopeMemoryRequirement;` — The memory requirement for the container allocation.
- L40 _public prototype_ `FEvaluationScopeInstanceContainer() = default;`
- L41 _public prototype_ `explicit FEvaluationScopeInstanceContainer(TNotNull<void*> InMemory, const FMemoryRequirement& InRequirement);`
- L42 _public prototype_ `~FEvaluationScopeInstanceContainer();`
- L44 _public prototype_ `FEvaluationScopeInstanceContainer(const FEvaluationScopeInstanceContainer& Other) = delete;`
- L45 _public prototype_ `FEvaluationScopeInstanceContainer& operator=(const FEvaluationScopeInstanceContainer& Other) = delete;`
- L47 _public function_ `FEvaluationScopeInstanceContainer(FEvaluationScopeInstanceContainer&& Other)`
- L53 _public function_ `FEvaluationScopeInstanceContainer& operator=(FEvaluationScopeInstanceContainer&& Other)`
- L63 _public function_ `[[nodiscard]] int32 Num() const` — @return number of items in the storage.
- L69 _public function_ `[[nodiscard]] bool IsValidDataHandle(FStateTreeDataHandle DataHandle) const` — @return true if the index can be used to get data.
- L75 _public function_ `[[nodiscard]] FStructView GetDataView(FStateTreeDataHandle DataHandle)` — @return specified item of an added structure.
- L81 _public function_ `[[nodiscard]] FStructView* GetDataViewPtr(FStateTreeDataHandle DataHandle)` — @return specified item if the structure was added.
- L92 _public prototype_ `void Add(FStateTreeDataHandle DataHandle, FConstStructView Default);` — Add a structure to the current memory requirement. Takes into account the structure alignment. UObject are created in the transient package and returned.
- L95 _public prototype_ `void Reset();` — Resets the data to empty.
- L98 _public function_ `[[nodiscard]] int32 GetAllocatedMemory() const` — Returns number of bytes allocated for the array
- L110 _private prototype_ `FItem* Get(const FStateTreeDataHandle& Handle) const;`
- L113 _private prototype_ `void AddTableDebugTag();`
- L114 _private prototype_ `void AddStructDebugTag(int32 Index);`
- L115 _private prototype_ `void TestDebugTags() const;`
- L119 _private member_ `void* Memory = nullptr;` — Struct instances (Not transient, as we use FStateTreeInstanceData to store default values for instance data)
- L120 _private member_ `FMemoryRequirement MemoryRequirement;`
- L121 _private member_ `int32 NumberOfElements = 0;`
- L122 _private member_ `bool bStructsHaveDestructor = false;`

#### struct `UE::StateTree::InstanceData::FEvaluationScopeInstanceContainer::FMemoryRequirementBuilder`  
`struct FMemoryRequirementBuilder`  
_L23-37_
- desc: Builds the amount of memory required to store the provided structures.
- L26 _public prototype_ `FMemoryRequirementBuilder() = default;`
- L29 _public prototype_ `void Add(TNotNull<const UScriptStruct*> Struct);` — Add a structure to the current memory requirement. Takes into account the structure alignment.
- L32 _public prototype_ `[[nodiscard]] FMemoryRequirement Build();` — @return the requirement memory for all added structures.
- L35 _private member_ `FMemoryRequirement MemoryRequirement;`
- L36 _private member_ `int32 FirstStructAlignment = -1;`

#### struct `UE::StateTree::InstanceData::FEvaluationScopeInstanceContainer::FItem`  
`struct FItem`  
_L104-108_
- L106 _public member_ `FStructView Instance;`
- L107 _public member_ `FStateTreeDataHandle DataHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace StateTree` (scope `UE`)
- L10 _namespace_ `namespace InstanceData` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeEvaluatorBase.h` (Public)


#### struct `FStateTreeEvaluatorBase`  
`struct FStateTreeEvaluatorBase : public FStateTreeNodeBase`  
_L18-49_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeNodeBase`
- desc: Base struct of StateTree Evaluators. Evaluators calculate and expose data to be used for decision making in a StateTree.
- L26 _public function_ `virtual void TreeStart(FStateTreeExecutionContext& Context) const` — Called when StateTree is started. @param Context Reference to current execution context.
- L32 _public function_ `virtual void TreeStop(FStateTreeExecutionContext& Context) const` — Called when StateTree is stopped. @param Context Reference to current execution context.
- L39 _public function_ `virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const` — Called each frame to update the evaluator. @param Context Reference to current execution context. @param DeltaTime Time since last StateTree tick, or 0 if called during preselection.
- L42 _public prototype_ `virtual FString GetDebugInfo(const FStateTreeReadOnlyExecutionContext& Context) const;`
- L45 _public function_ `virtual void AppendDebugInfoString(FString& DebugString, const FStateTreeExecutionContext& Context) const final` — `UE_DEPRECATED(5.8, "Use the version with the FStateTreeReadOnlyExecutionContext.")`

#### struct `FStateTreeEvaluatorCommonBase`  
`struct FStateTreeEvaluatorCommonBase : public FStateTreeEvaluatorBase`  
_L56-59_
- reflection: `USTRUCT(Meta=(Hidden))`
- inherits: `FStateTreeEvaluatorBase`
- desc: Base class (namespace) for all common Evaluators that are generally applicable. This allows schemas to safely include all Evaluators child of this struct.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeEvents.h` (Public)


#### struct `UE::StateTree::Event::FEventsPendingForNextTransitionProcessingScope`  
`struct FEventsPendingForNextTransitionProcessingScope`  
_L21-30_
- desc: State Tree Events are cleared at end of each transition processing phase. (Inside TriggerTransitions()). When in scope, events sent will live through the current phase and cleared on the next transition processing phase. Used internally by TriggerTransitions and ParallelTree.
- L23 _public prototype_ `explicit FEventsPendingForNextTransitionProcessingScope(TNotNull<FStateTreeEventQueue*> EventQueue);`
- L25 _public prototype_ `~FEventsPendingForNextTransitionProcessingScope();`
- L27 _public member_ `TNotNull<FStateTreeEventQueue*> ScopedEventQueue;`
- L29 _public member_ `uint8 bSavedIsPendingForNextTransitionProcessingScope : 1 = false;`

#### enum `EStateTreeLoopEvents`  
`enum class EStateTreeLoopEvents : uint8`  
_L35-43_
- reflection: `UENUM()`
- desc: Enum used for flow control during event iteration.
- L38 _public enumerator_ `Next` — Continues to next event.
- L40 _public enumerator_ `Break` — Stops the event handling loop.
- L42 _public enumerator_ `Consume` — Consumes and removes the current event.

#### struct `FStateTreeEvent`  
`struct FStateTreeEvent`  
_L49-95_
- reflection: `USTRUCT(BlueprintType)`
- desc: StateTree event with payload.
- L53 _public prototype_ `FStateTreeEvent() = default;`
- L55 _public function_ `explicit FStateTreeEvent(const FGameplayTag InTag) : Tag(InTag)`
- L60 _public function_ `explicit FStateTreeEvent(const FGameplayTag InTag, const FConstStructView InPayload, const FName InOrigin) : Tag(InTag) , Payload(InPayload) , Origin(InOrigin)`
- L81 _public member_ `FGameplayTag Tag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta=(Categories="StateTreeEvent"))` — Tag describing the event
- L85 _public member_ `FInstancedStruct Payload;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")` — Optional payload for the event.
- L89 _public member_ `FName Origin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")` — Optional info to describe who sent the event.
- L92 _private member_ `uint8 bIsPendingForNextTransitionProcessing : 1 = false;`

#### struct `FStateTreeSharedEvent`  
`struct FStateTreeSharedEvent`  
_L101-161_
- reflection: `USTRUCT()`
- desc: A struct wrapping FStateTreeEvent in shared struct, used to make it easier to refer to the events during State Tree update.
- L105 _public prototype_ `FStateTreeSharedEvent() = default;`
- L107 _public function_ `explicit FStateTreeSharedEvent(const FGameplayTag InTag, const FConstStructView InPayload, const FName InOrigin) : Event(MakeShared<FStateTreeEvent>(InTag, InPayload, InOrigin))`
- L111 _public function_ `explicit FStateTreeSharedEvent(const FStateTreeEvent& InEvent) : Event(MakeShared<FStateTreeEvent>(InEvent))`
- L115 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector);`
- L117 _public function_ `const FStateTreeEvent* Get() const`
- L122 _public function_ `FStateTreeEvent* GetMutable()`
- L127 _public function_ `const FStateTreeEvent* operator->() const`
- L132 _public function_ `FStateTreeEvent* operator->()`
- L137 _public function_ `const FStateTreeEvent& operator*()`
- L143 _public function_ `FStateTreeEvent& operator*() const`
- L149 _public function_ `bool IsValid() const`
- L154 _public function_ `bool operator==(const FStateTreeSharedEvent& Other) const`
- L160 _protected member_ `TSharedPtr<FStateTreeEvent> Event;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FStateTreeSharedEvent> : public TStructOpsTypeTraitsBase2<FStateTreeSharedEvent>`  
_L164-170_
- inherits: `TStructOpsTypeTraitsBase2<FStateTreeSharedEvent>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L167-169_

#### struct `FStateTreeEventQueue`  
`struct FStateTreeEventQueue`  
_L176-261_
- reflection: `USTRUCT()`
- desc: Event queue buffering all the events to be processed by a State Tree.
- L181 _public member_ `static constexpr int32 MaxActiveEvents = 64;` — Maximum number of events that can be buffered.
- L184 _public function_ `TConstArrayView<FStateTreeSharedEvent> GetEventsView() const` — @return const view to all the events in the buffer.
- L190 _public function_ `TArrayView<FStateTreeSharedEvent> GetMutableEventsView()` — @return view to all the events in the buffer.
- L196 _public function_ `void Reset()` — Resets the events in the event queue
- L203 _public function_ `bool HasEvents() const` — @return true if the queue has any events.
- L216 _public prototype_ `bool SendEvent(const UObject* Owner, const FGameplayTag& Tag, const FConstStructView Payload = FConstStructView(), const FName Origin = FName());` — Buffers and event to be sent to the State Tree. @param Owner Optional pointer to an owner UObject that is used for logging errors. @param Tag tag identifying the event. @param Payload Optional reference to the payload struct. @param Origin Optional name identifying the origin of the event. @return true if successfully added the event to the events queue.
- L222 _public prototype_ `bool ConsumeEvent(const FStateTreeSharedEvent& Event);` — Consumes and removes the specified event from the event queue. @return true if successfully found and removed the event from the queue.
- L228 _public prototype_ `void ClearEventsForCurrentTransitionProcessingPhase();` — Clear all events in the queue that are not marked pending for next transition processing phase, And unmarks events that are pending for next transition processing since we are advancing to the next.
- L235 _public function_ `template<typename TFunc> void ForEachEvent(TFunc&& Function)` — Iterates over all events. @param Function a lambda which takes const FStateTreeSharedEvent& Event, and returns EStateTreeLoopEvents.
- L253 _protected function_ `TArray<FStateTreeSharedEvent>& GetEventsArray()` — Used by FStateTreeExecutionState to implement deprecated functionality.
- L256 _protected member_ `TArray<FStateTreeSharedEvent> SharedEvents;` — `UPROPERTY()`
- L258 _protected member_ `uint8 bNewlyAddedEventsShouldBePendingForNextTransitionProcessing : 1 = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API STATETREEMODULE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace StateTree` (scope `UE`)
- L14 _namespace_ `namespace Event` (scope `UE::StateTree`)
- L67 _function_ `friend inline uint32 GetTypeHash(const FStateTreeEvent& Event)`
- L168 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anonba11a1aa0103`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeExecutionContext.h` (Public)


#### struct `FStateTreeReadOnlyExecutionContext`  
`struct FStateTreeReadOnlyExecutionContext`  
_L72-217_
- desc: Read-only execution context to interact with the state tree instance data. Only const and read accesses are available. Multiple FStateTreeReadOnlyExecutionContext can coexist on different threads as long no other (minimal, weak, regular) execution context exists. The user is responsible for preventing invalid multi-threaded access.
- L75 _public prototype_ `explicit FStateTreeReadOnlyExecutionContext(TNotNull<UObject*> Owner, TNotNull<const UStateTree*> StateTree, FStateTreeInstanceData& InInstanceData);`
- L76 _public prototype_ `explicit FStateTreeReadOnlyExecutionContext(TNotNull<UObject*> Owner, TNotNull<const UStateTree*> StateTree, FStateTreeInstanceStorage& Storage);`
- L77 _public prototype_ `virtual ~FStateTreeReadOnlyExecutionContext();`
- L80 _private prototype_ `FStateTreeReadOnlyExecutionContext(const FStateTreeReadOnlyExecutionContext&) = delete;`
- L81 _private prototype_ `FStateTreeReadOnlyExecutionContext& operator=(const FStateTreeReadOnlyExecutionContext&) = delete;`
- L89 _public function_ `bool IsValid() const` — Indicates if the instance is valid and would be able to run the instance of the associated StateTree asset with a regular execution context. @return True if the StateTree asset assigned to the execution context is valid (i.e., not empty) and successfully initialized (i.e., linked and all bindings resolved).
- L95 _public function_ `TNotNull<UObject*> GetOwner() const` — @return The owner of the context
- L101 _public function_ `UWorld* GetWorld() const` — @return The world of the owner or nullptr if the owner is not set.
- L107 _public function_ `TNotNull<const UStateTree*> GetStateTree() const` — @return the StateTree asset in use by the instance. It is the root asset.
- L113 _public function_ `bool HasEventToProcess(const FGameplayTag Tag) const` — @return true if there is a pending event with specified tag.
- L123 _public function_ `const FCompactStateTreeState* GetStateFromHandle(const FStateTreeStateHandle StateHandle) const` — @return Pointer to a State or null if state not found
- L129 _public prototype_ `FStateTreeScheduledTick GetNextScheduledTick() const;` — @return the delta time for the next execution context tick.
- L132 _public prototype_ `EStateTreeRunStatus GetStateTreeRunStatus() const;` — @return the tree run status.
- L135 _public prototype_ `EStateTreeRunStatus GetLastTickStatus() const;` — @return the status of the last tick function
- L138 _public prototype_ `TConstArrayView<FStateTreeExecutionFrame> GetActiveFrames() const;` — @return reference to the list of currently active frames and states.
- L141 _public prototype_ `FString GetActiveStateName() const;` — @return the name of the active state.
- L144 _public prototype_ `TArray<FName> GetActiveStateNames() const;` — @return the names of all the active state.
- L148 _public prototype_ `FString GetDebugInfoString() const;` — @return Debug string describing the current state of the execution
- L152 _public prototype_ `int32 GetStateChangeCount() const;`
- L154 _public prototype_ `void DebugPrintInternalLayout();`
- L159 _public prototype_ `FStateTreeInstanceDebugId GetInstanceDebugId() const;` — A unique Id used by debugging tools to identify the instance.
- L162 _public function_ `FString GetInstanceDebugDescription() const` — @return Short description of the instance for debug/trace purposes
- L167 _public function_ `void SetOuterTraceId(const uint64 Id) const`
- L172 _public function_ `uint64 GetOuterTraceId() const`
- L177 _public function_ `void SetNodeCustomDebugTraceData(UE::StateTreeTrace::FNodeCustomDebugData&& DebugData) const`
- L185 _public function_ `UE::StateTreeTrace::FNodeCustomDebugData StealNodeCustomDebugTraceData() const`
- L202 _protected prototype_ `FString GetInstanceDescriptionInternal() const;` — @return Description used as prefix by STATETREE_LOG and STATETREE_CLOG, Owner name by default.
- L205 _protected member_ `UObject& Owner;` — Owner of the instance data.
- L208 _protected member_ `const UStateTree& RootStateTree;` — The StateTree asset the context is initialized for
- L211 _protected member_ `FStateTreeInstanceStorage& Storage;` — Data storage of the instance data.
- L214 _protected member_ `mutable UE::StateTreeTrace::FNodeCustomDebugData NodeCustomDebugTraceData;`
- L215 _protected member_ `mutable uint64 OuterTraceId = 0;`

#### struct `FStateTreeMinimalExecutionContext`  
`struct FStateTreeMinimalExecutionContext : public FStateTreeReadOnlyExecutionContext`  
_L224-272_
- inherits: `FStateTreeReadOnlyExecutionContext`
- desc: Minimal execution context to interact with the state tree instance data. A regular execution context requires the context data and external data to be valid to execute all possible operations. The minimal execution context doesn't requires those data but supports only a subset of operations.
- L228 _public prototype_ `explicit FStateTreeMinimalExecutionContext(UObject& Owner, const UStateTree& StateTree, FStateTreeInstanceData& InInstanceData);` — `UE_DEPRECATED(5.6, "Use FStateTreeMinimalExecutionContext with the not null pointer.")`
- L230 _public prototype_ `explicit FStateTreeMinimalExecutionContext(UObject& Owner, const UStateTree& StateTree, FStateTreeInstanceStorage& Storage);` — `UE_DEPRECATED(5.6, "Use FStateTreeMinimalExecutionContext with the not null pointer.")`
- L231 _public prototype_ `explicit FStateTreeMinimalExecutionContext(TNotNull<UObject*> Owner, TNotNull<const UStateTree*> StateTree, FStateTreeInstanceData& InInstanceData);`
- L232 _public prototype_ `explicit FStateTreeMinimalExecutionContext(TNotNull<UObject*> Owner, TNotNull<const UStateTree*> StateTree, FStateTreeInstanceStorage& Storage);`
- L233 _public prototype_ `virtual ~FStateTreeMinimalExecutionContext();`
- L236 _private prototype_ `FStateTreeMinimalExecutionContext(const FStateTreeMinimalExecutionContext&) = delete;`
- L237 _private prototype_ `FStateTreeMinimalExecutionContext& operator=(const FStateTreeMinimalExecutionContext&) = delete;`
- L247 _public prototype_ `UE::StateTree::FScheduledTickHandle AddScheduledTickRequest(FStateTreeScheduledTick ScheduledTick);` — Adds a scheduled tick request. The result of GetNextScheduledTick is affected by the request. This allows a specific task to control when the tree ticks. @note A request with a higher priority will supersede all other requests. ex: Task A request a custom time of 1FPS and Task B request a custom time of 2FPS. Both tasks will tick at 1FPS.
- L250 _public prototype_ `void UpdateScheduledTickRequest(UE::StateTree::FScheduledTickHandle Handle, FStateTreeScheduledTick ScheduledTick);` — Updates the scheduled tick of a previous request.
- L253 _public prototype_ `void RemoveScheduledTickRequest(UE::StateTree::FScheduledTickHandle Handle);` — Removes a scheduled tick request.
- L256 _public prototype_ `void SendEvent(const FGameplayTag Tag, const FConstStructView Payload = FConstStructView(), const FName Origin = FName());` — Sends event for the StateTree.
- L264 _protected prototype_ `FStateTreeExecutionExtension* GetMutableExecutionExtension() const;` — Get ExecutionExtension from InstanceStorage for less indirections The user is responsible for validity of the result, re-call the getter when needed @return ExecutionExtension from InstanceStorage. could be null if Extension hasn't been set or Instance Storage has been reset.
- L267 _protected prototype_ `void ScheduleNextTick(UE::StateTree::ETickReason Reason = UE::StateTree::ETickReason::None);` — Informs the owner when the instance of the tree must woke up from a scheduled tick sleep.
- L271 _protected member_ `bool bAllowedToScheduleNextTick = true;` — The context is processing the tree. We do not need to inform the owner that something changed.

#### struct `FStateTreeExecutionContext`  
`struct FStateTreeExecutionContext : public FStateTreeMinimalExecutionContext`  
_L329-1787_
- inherits: `FStateTreeMinimalExecutionContext`
- desc: StateTree Execution Context is a helper that is used to update StateTree instance data. The context is meant to be temporary, you should not store a context across multiple frames. The owner is used as the owner of the instantiated UObjects in the instance data and logging, it should have same or greater lifetime as the InstanceData. In common case you can use the constructor to initialize the context, and us a helper struct to set up the context data and external data getter: FStateTreeExecutionContext Context(*GetOwner(), *StateTreeRef.GetStateTree(), InstanceData); if (SetContextRequirements(Context)) { Context.Tick(DeltaTime); } bool UMyComponent::SetContextRequirements(FStateTreeExecutionContext& Context) { if (!Context.IsValid()) { return false; } // Setup context data Context.SetContextDataByName(...); ... Context.SetCollectExternalDataCallback(FOnCollectStateTreeExternalData::CreateUObject(this, &UMyComponent::CollectExternalData); return Context.AreContextDataViewsValid(); } bool UMyComponent::CollectExternalData(const FStateTreeExecutionContext& Context, const UStateTree* StateTree, TArrayView<const FStateTreeExternalDataDesc> ExternalDataDescs, TArrayView<FStateTreeDataView> OutDataViews) { ... for (int32 Index = 0; Index < ExternalDataDescs.Num(); Index++) { const FStateTreeExternalDataDesc& Desc = ExternalDataDescs[Index]; if (Desc.Struct->IsChildOf(UWorldSubsystem::StaticClass())) { UWorldSubsystem* Subsystem = World->GetSubsystemBase(Cast<UClass>(const_cast<USt
- L332 _public prototype_ `FStateTreeExecutionContext(UObject& InOwner, const UStateTree& InStateTree, FStateTreeInstanceData& InInstanceData, const FOnCollectStateTreeExternalData& CollectExternalDataCallback = {}, const EStateTreeRecordTransitions RecordTransitions = EStateTreeRecordTransitions::No);`
- L334 _public prototype_ `FStateTreeExecutionContext(const FStateTreeExecutionContext& InContextToCopy, const UStateTree& InStateTree, FStateTreeInstanceData& InInstanceData);` — Construct an execution context from a parent context and another tree. Useful to run a subtree from the parent context with the same schema.
- L335 _public prototype_ `FStateTreeExecutionContext(TNotNull<UObject*> Owner, TNotNull<const UStateTree*> StateTree, FStateTreeInstanceData& InInstanceData, const FOnCollectStateTreeExternalData& CollectExternalDataCallback = {}, const EStateTreeRecordTransitions RecordTransitions = EStateTreeRecordTransitions::No);`
- L337 _public prototype_ `FStateTreeExecutionContext(const FStateTreeExecutionContext& InContextToCopy, TNotNull<const UStateTree*> StateTree, FStateTreeInstanceData& InInstanceData);` — Construct an execution context from a parent context and another tree. Useful to run a subtree from the parent context with the same schema.
- L338 _public prototype_ `virtual ~FStateTreeExecutionContext();`
- L341 _private prototype_ `FStateTreeExecutionContext(const FStateTreeExecutionContext&) = delete;`
- L342 _private prototype_ `FStateTreeExecutionContext& operator=(const FStateTreeExecutionContext&) = delete;`
- L346 _public prototype_ `void SetCollectExternalDataCallback(const FOnCollectStateTreeExternalData& Callback);` — Sets callback used to collect external data views during State Tree execution.
- L353 _public prototype_ `void SetLinkedStateTreeOverrides(const FStateTreeReferenceOverrides* InLinkedStateTreeOverrides);` — Overrides for linked State Trees. This table is used to override State Tree references on linked states. If a linked state's tag is exact match of the tag specified on the table, the reference from the table is used instead.
- L359 _public prototype_ `void SetLinkedStateTreeOverrides(FStateTreeReferenceOverrides InLinkedStateTreeOverrides);` — Overrides for linked State Trees. This table is used to override State Tree references on linked states. If a linked state's tag is exact match of the tag specified on the table, the reference from the table is used instead.
- L362 _public prototype_ `const FStateTreeReference* GetLinkedStateTreeOverrideForTag(const FGameplayTag StateTag) const;` — @return the first state tree reference set by SetLinkedStateTreeOverrides that matches the StateTag. Or null if not found.
- L374 _public prototype_ `void SetExternalGlobalParameters(const FExternalGlobalParameters* Parameters);`
- L377 _public function_ `const FStateTreeInstanceData* GetInstanceData() const` — @return const references to the instance data in use
- L383 _public function_ `FStateTreeInstanceData* GetMutableInstanceData() const` — @return mutable references to the instance data in use
- L389 _public function_ `const FStateTreeEventQueue& GetEventQueue() const` — @return mutable references to the instance data in use.
- L395 _public function_ `FStateTreeEventQueue& GetMutableEventQueue() const` — @return mutable references to the instance data in use.
- L401 _public prototype_ `FStateTreeWeakExecutionContext MakeWeakExecutionContext() const;` — @return a weak context to interact with the state tree instance data that can be stored for later uses.
- L409 _public prototype_ `FStateTreeWeakTaskRef MakeWeakTaskRef(const FStateTreeTaskBase& Node) const;` — `UE_DEPRECATED(5.6, "FStateTreeWeakTaskRef is no longer used.")` — @return a weak reference for a task that can be stored for later uses. @note similar to GetInstanceData, the node needs to be the current processing node.
- L419 _public function_ `FStateTreeWeakTaskRef MakeWeakTaskRefFromInstanceData(const T& InInstanceData) const` — `UE_DEPRECATED(5.6, "FStateTreeWeakTaskRef is no longer used.")`
- L433 _public function_ `FStateTreeWeakTaskRef MakeWeakTaskRefFromInstanceDataPtr(const T* InInstanceData) const` — `UE_DEPRECATED(5.6, "FStateTreeWeakTaskRef is no longer used.")`
- L477 _public prototype_ `EStateTreeRunStatus Start();` — Start executing. @return Tree execution status after the start.
- L484 _public prototype_ `EStateTreeRunStatus Start(FConstStructView InitialGlobalParameters);` — Start executing. @param InitialGlobalParameters Optional override of parameters initial values @return Tree execution status after the start.
- L490 _public prototype_ `EStateTreeRunStatus Start(FStartParameters Parameter);` — Start executing. @return Tree execution status after the start.
- L493 _public prototype_ `EStateTreeRunStatus Start(const FInstancedPropertyBag* InitialGlobalParameters, int32 RandomSeed = -1);` — `UE_DEPRECATED(5.8, "Use the version with the FStartParameters")`
- L500 _public prototype_ `EStateTreeRunStatus Stop(const EStateTreeRunStatus CompletionStatus = EStateTreeRunStatus::Stopped);` — Stop executing if the tree is running. @param CompletionStatus Status (and terminal state) reported in the transition when the tree is stopped. @return Tree execution status at stop, can be CompletionStatus, or earlier status if the tree is not running.
- L507 _public prototype_ `EStateTreeRunStatus Tick(const float DeltaTime);` — Tick the state tree logic, updates the tasks and triggers transitions. @param DeltaTime time to advance the logic. @returns tree run status after the tick.
- L515 _public prototype_ `EStateTreeRunStatus TickUpdateTasks(const float DeltaTime);` — Tick the state tree logic partially, updates the tasks. For full update TickTriggerTransitions() should be called after. @param DeltaTime time to advance the logic. @returns tree run status after the partial tick.
- L522 _public prototype_ `EStateTreeRunStatus TickTriggerTransitions();` — Tick the state tree logic partially, triggers the transitions. For full update TickUpdateTasks() should be called before. @returns tree run status after the partial tick.
- L528 _public prototype_ `void BroadcastDelegate(const FStateTreeDelegateDispatcher& Dispatcher);` — Broadcasts the delegate. It executes bound delegates immediately and triggers bound transitions (when transitions are evaluated).
- L532 _public prototype_ `bool AddDelegateListener(const FStateTreeDelegateListener& Listener, FSimpleDelegate Delegate);` — Adds delegate listener.
- L539 _public prototype_ `void BindDelegate(const FStateTreeDelegateListener& Listener, FSimpleDelegate Delegate);` — Registers the delegate to the listener. If the listener was previously registered, then unregister it first before registering it again with the new delegate callback. The listener is bound to a dispatcher in the editor.
- L543 _public prototype_ `void RemoveDelegateListener(const FStateTreeDelegateListener& Listener);` — Removes delegate listener.
- L546 _public prototype_ `void UnbindDelegate(const FStateTreeDelegateListener& Listener);` — Unregisters the callback bound to the listener.
- L553 _public function_ `template<typename TFunc> typename TEnableIf<TIsInvocable<TFunc, FStateTreeSharedEvent>::Value, void>::Type ForEachEvent(TFunc&& Function) const` — Iterates over all events. @param Function a lambda which takes const FStateTreeSharedEvent& Event, and returns EStateTreeLoopEvents.
- L568 _public function_ `template<typename TFunc> typename TEnableIf<TIsInvocable<TFunc, FStateTreeEvent>::Value, void>::Type ForEachEvent(TFunc&& Function) const` — Iterates over all events. @param Function a lambda which takes const FStateTreeEvent& Event, and returns EStateTreeLoopEvents. Less preferable than FStateTreeSharedEvent version.
- L581 _public function_ `TArrayView<FStateTreeSharedEvent> GetMutableEventsToProcessView()` — @return events to process this tick.
- L587 _public function_ `TConstArrayView<FStateTreeSharedEvent> GetEventsToProcessView() const` — @return events to process this tick.
- L593 _public prototype_ `void ConsumeEvent(const FStateTreeSharedEvent& Event);` — Consumes and removes the specified event from the event queue.
- L595 _public function_ `FStateTreeIndex16 GetCurrentlyProcessedNodeIndex() const`
- L600 _public function_ `FStateTreeDataHandle GetCurrentlyProcessedNodeInstanceData() const`
- L607 _public function_ `FStateTreeDataHandle GetCurrentlyProcessedNode() const` — @return the currently processed node if applicable.
- L613 _public function_ `FStateTreeStateHandle GetCurrentlyProcessedState() const` — @return the currently processed state if applicable.
- L619 _public function_ `const FStateTreeExecutionFrame* GetCurrentlyProcessedFrame() const` — @return the currently processed execution frame if applicable.
- L625 _public function_ `const FStateTreeExecutionFrame* GetCurrentlyProcessedParentFrame() const` — @return the currently processed execution parent frame if applicable.
- L631 _public function_ `TSharedPtr<UE::StateTree::ExecutionContext::ITemporaryStorage> GetCurrentlyProcessedTemporaryStorage() const` — @return the currently processed temporary storage
- L637 _public function_ `TConstArrayView<FStateTreeExternalDataDesc> GetContextDataDescs() const` — @return Array view to named external data descriptors associated with this context. Note: Init() must be called before calling this method.
- L643 _public function_ `void SetContextData(const FStateTreeExternalDataHandle Handle, FStateTreeDataView DataView)` — Sets context data view value for specific item.
- L651 _public prototype_ `bool SetContextDataByName(const FName Name, FStateTreeDataView DataView);` — Sets the context data based on name (name is defined in the schema), returns true if data was found
- L654 _public prototype_ `FStateTreeDataView GetContextDataByName(const FName Name) const;` — @return the context data based on name (name is defined in the schema)
- L657 _public prototype_ `bool AreContextDataViewsValid() const;` — @return True if all context data pointers are set.
- L665 _public function_ `template <typename T> typename T::DataType& GetExternalData(const T Handle) const` — Returns reference to external data based on provided handle. The return type is deduced from the handle's template type. @param Handle Valid TStateTreeExternalDataHandle<> handle. @return reference to external data based on handle or null if data is not set.
- L680 _public function_ `template <typename T> typename T::DataType* GetExternalDataPtr(const T Handle) const` — Returns pointer to external data based on provided item handle. The return type is deduced from the handle's template type. @param Handle Valid TStateTreeExternalDataHandle<> handle. @return pointer to external data based on handle or null if item is not set or handle is invalid.
- L691 _public function_ `FStateTreeDataView GetExternalDataView(const FStateTreeExternalDataHandle Handle)`
- L704 _public function_ `template <typename T> T* GetInstanceDataPtr(const FStateTreeNodeBase& Node) const` — @returns pointer to the instance data of specified node.
- L712 _public function_ `template <typename T> T& GetInstanceData(const FStateTreeNodeBase& Node) const` — @returns reference to the instance data of specified node.
- L720 _public function_ `template <typename T> typename T::FInstanceDataType& GetInstanceData(const T& Node) const` — @returns reference to the instance data of specified node. Infers the instance data type from the node's FInstanceDataType.
- L729 _public function_ `template <typename T> T* GetExecutionRuntimeDataPtr(const FStateTreeNodeBase& Node) const` — @returns pointer to the execution runtime data of specified node.
- L737 _public function_ `template <typename T> T& GetExecutionRuntimeData(const FStateTreeNodeBase& Node) const` — @returns reference to the execution runtime data of specified node.
- L745 _public function_ `template <typename T> typename T::FExecutionRuntimeDataType& GetExecutionRuntimeData(const T& Node) const` — @returns reference to the execution runtime data of specified node. Infers the execution runtime data type from the node's FExecutionRuntimeDataType.
- L754 _public function_ `template <typename T> TStateTreeInstanceDataStructRef<typename T::FInstanceDataType> GetInstanceDataStructRef(const T& Node) const` — @returns reference to instance data struct that can be passed to lambdas. See TStateTreeInstanceDataStructRef for usage.
- L768 _public prototype_ `void RequestTransition(const FStateTreeTransitionRequest& Request);` — Requests transition to a state. If called during during transition processing (e.g. from FStateTreeTaskBase::TriggerTransitions()) the transition is attempted to be activate immediately (it can fail e.g. because of preconditions on a target state). If called outside the transition handling, the request is buffered and handled at the beginning of next transition processing. @param Request The state to transition to.
- L779 _public prototype_ `void RequestTransition(FStateTreeStateHandle TargetState, EStateTreeTransitionPriority Priority = EStateTreeTransitionPriority::Normal, EStateTreeSelectionFallback Fallback = EStateTreeSelectionFallback::None);` — Requests transition to a state. If called during during transition processing (e.g. from FStateTreeTaskBase::TriggerTransitions()) the transition is attempted to be activate immediately (it can fail e.g. because of preconditions on a target state). If called outside the transition handling, the request is buffered and handled at the beginning of next transition processing. @param TargetState The state to transition to. @param Priority The priority of the transition. @param Fallback of the transition if it fails to select the target state.
- L787 _public prototype_ `void FinishTask(const FStateTreeTaskBase& Task, EStateTreeFinishTaskType FinishType);` — Finishes a task. This fails if the Task is not currently the processed node. ie. Must be called from inside a FStateTreeTaskBase EnterState, ExitState, StateCompleted, Tick, TriggerTransitions. If called during tick processing, then the state completes immediately. If called outside of the tick processing, then the request is buffered and handled on the next tick.
- L796 _public prototype_ `void FinishTask(const UE::StateTree::FFinishedTask& Task, EStateTreeFinishTaskType FinishType);` — Finishes a task. If called during tick processing, then the state completes immediately. If called outside of the tick processing, then the request is buffered and handled on the next tick.
- L801 _public function_ `static FStateTreeDataView GetDataViewFromInstanceStorage(FStateTreeInstanceStorage& InstanceDataStorage, FStateTreeInstanceStorage* CurrentlyProcessedSharedInstanceStorage, const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle Handle)` — `UE_DEPRECATED(5.6, "Use UE::StateTree::InstanceData::GetDataView instead.")` — @return data view of the specified handle relative to given frame.
- L808 _public prototype_ `static const FStateTreeExecutionFrame* FindFrame(const UStateTree* StateTree, FStateTreeStateHandle RootState, TConstArrayView<FStateTreeExecutionFrame> Frames, const FStateTreeExecutionFrame*& OutParentFrame);` — `UE_DEPRECATED(5.8, "Use UE::StateTree::ExecutionContext::FindExecutionFrame instead.")` — Looks for a frame in provided list of frames.
- L811 _protected prototype_ `static FStateTreeExecutionFrame* FindMutableExecutionFrame(UE::StateTree::FActiveFrameID InFrameID, TArrayView<FStateTreeExecutionFrame> ActiveFrames, TArrayView<FStateTreeExecutionFrame> InTemporaryFrames);`
- L822 _public prototype_ `EStateTreeRunStatus ForceTransition(const FRecordedStateTreeTransitionResult& Transition);` — Forces transition to a state. It will skip all conditions. Primarily used for replication purposes so that a client state tree stays in sync with its server counterpart. It has to be a running instance. It will not work if you didn't call Start or if the execution previously failed. @param Recorded state transition to run on the state tree. @return The new run status for the state tree.
- L825 _public function_ `TConstArrayView<FRecordedStateTreeTransitionResult> GetRecordedTransitions() const` — Returns the recorded transitions for this context.
- L955 _protected prototype_ `virtual FString GetInstanceDescription() const final;` — @return Prefix that will be used by STATETREE_LOG and STATETREE_CLOG, Owner name by default.
- L958 _protected function_ `virtual void BeginDelayedTransition(const FStateTreeTransitionDelayedState& DelayedState)` — Callback when delayed transition is triggered. Contexts that are event based can use this to trigger a future event.
- L961 _protected prototype_ `void UpdateInstanceData(TConstArrayView<FStateTreeExecutionFrame> CurrentActiveFrames, TArrayView<FStateTreeExecutionFrame> NextActiveFrames);` — `UE_DEPRECATED(5.7, "Use the UpdateInstanceData with the FSelectStateResult argument.")`
- L964 _protected prototype_ `void UpdateInstanceData(const TSharedPtr<FSelectStateResult>& SelectStateResult);` — Allocate the instance data. Fixup the TemporarySelectedFrame with the correct data.
- L967 _protected prototype_ `EStateTreeRunStatus EnterState(FStateTreeTransitionResult& Transition);` — `UE_DEPRECATED(5.7, "Use the EnterState with the FSelectStateResult argument.")`
- L975 _protected prototype_ `EStateTreeRunStatus EnterState(const TSharedPtr<FSelectStateResult>& SelectStateResult, const FStateTreeTransitionResult& Transition);` — Handles logic for entering State. EnterState is called on new active Evaluators and Tasks that are part of the re-planned tree. Re-planned tree is from the transition target up to the leaf state. States that are parent to the transition target state and still active after the transition will remain intact. @return run status returned by the tasks.
- L978 _protected prototype_ `void ExitState(const FStateTreeTransitionResult& Transition);` — `UE_DEPRECATED(5.7, "Use the ExitState with the FSelectStateResult argument.")`
- L985 _protected prototype_ `void ExitState(const TSharedPtr<const FSelectStateResult>& SelectStateResult, const FStateTreeTransitionResult& Transition);` — Handles logic for exiting State. ExitState is called on current active Evaluators and Tasks that are part of the re-planned tree. Re-planned tree is from the transition target up to the leaf state. States that are parent to the transition target state and still active after the transition will remain intact.
- L990 _protected prototype_ `void RemoveAllDelegateListeners();` — Removes all delegate listeners.
- L995 _protected prototype_ `void StateCompleted();` — Handles logic for signaling State completed. StateCompleted is called on current active Evaluators and Tasks in reverse order (from leaf to root).
- L999 _private prototype_ `template<bool bOnActiveInstances> void TickGlobalEvaluatorsForFrameInternal(float DeltaTime, const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& Frame);`
- L1006 _protected prototype_ `void TickGlobalEvaluatorsForFrameOnActiveInstances(float DeltaTime, const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& Frame);` — Stop the frame's evaluators. Should be used only on active node instances, assumes valid data handles and does not consider temporary node instances.
- L1012 _protected prototype_ `void TickGlobalEvaluatorsForFrameWithValidation(float DeltaTime, const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& Frame);` — Tick the frame's evaluators. This version validates the data handles and looks up temporary instances.
- L1017 _protected prototype_ `EStateTreeRunStatus TickEvaluatorsAndGlobalTasks(float DeltaTime, bool bTickGlobalTasks = true);` — Tick evaluators and global tasks by delta time.
- L1022 _protected prototype_ `EStateTreeRunStatus TickEvaluatorsAndGlobalTasksForFrame(float DeltaTime, bool bTickGlobalTasks, int32 FrameIndex, const FStateTreeExecutionFrame* CurrentParentFrame, const TNotNull<FStateTreeExecutionFrame*> CurrentFrame);` — Tick the frame's evaluators and the frame's tasks.
- L1025 _protected prototype_ `TSharedPtr<FSelectStateResult> GetCurrentlyProcessedStateSelection() const;` — @return in progress transition or the latest requested transition.
- L1029 _private prototype_ `void MoveGlobalTemporariesToInstances(FStateTreeExecutionFrame& Frame);` — Move the temporary data for each evaluators and tasks to instance data.
- L1032 _private prototype_ `template<bool bOnActiveInstances, bool bMoveFromTemporary> EStateTreeRunStatus StartGlobalsForFrameInternal(const FStateTreeExecutionFrame* ParentFrame, FStateTreeExecutionFrame& Frame, FStateTreeTransitionResult& Transition);`
- L1039 _protected prototype_ `EStateTreeRunStatus StartGlobalsForFrameOnActiveInstances(const FStateTreeExecutionFrame* ParentFrame, FStateTreeExecutionFrame& Frame, FStateTreeTransitionResult& Transition);` — Start the frame's evaluators and the frame's tasks. Should be used only on active node instances, assumes valid data handles and does not consider temporary node instances.
- L1045 _protected prototype_ `EStateTreeRunStatus StartGlobalsForFrameWithValidation(const FStateTreeExecutionFrame* ParentFrame, FStateTreeExecutionFrame& Frame, FStateTreeTransitionResult& Transition);` — Start the frame's evaluators and the frame's tasks. This version validates the data handles and looks up temporary instances.
- L1048 _protected prototype_ `EStateTreeRunStatus StartEvaluatorsAndGlobalTasks(FStateTreeIndex16& OutLastInitializedTaskIndex);` — `UE_DEPRECATED(5.7, "Use StartEvaluatorsAndGlobalTasks without the OutLastInitializedTaskIndex argument")`
- L1054 _protected prototype_ `EStateTreeRunStatus StartEvaluatorsAndGlobalTasks();` — Starts active global evaluators and global tasks. @return run status returned by the global tasks.
- L1058 _private prototype_ `template<bool bOnActiveInstances> void StopGlobalsForFrameInternal(const FStateTreeExecutionFrame* ParentFrame, FStateTreeExecutionFrame& Frame, const FStateTreeTransitionResult& Transition);`
- L1065 _protected prototype_ `void StopGlobalsForFrameOnActiveInstances(const FStateTreeExecutionFrame* ParentFrame, FStateTreeExecutionFrame& Frame, const FStateTreeTransitionResult& Transition);` — Stop the frame's evaluators and the frame's tasks. Should be used only on active node instances, assumes valid data handles and does not consider temporary node instances.
- L1071 _protected prototype_ `void StopGlobalsForFrameWithValidation(const FStateTreeExecutionFrame* ParentFrame, FStateTreeExecutionFrame& Frame, const FStateTreeTransitionResult& Transition);` — Stop the frame's evaluators and the frame's tasks. This version validates the data handles and looks up temporary instances.
- L1074 _protected prototype_ `void StopEvaluatorsAndGlobalTasks(const EStateTreeRunStatus CompletionStatus, const FStateTreeIndex16 LastInitializedTaskIndex);` — `UE_DEPRECATED(5.7, "Use StopEvaluatorsAndGlobalTasks without LastInitializedTaskIndex")`
- L1079 _protected prototype_ `void StopEvaluatorsAndGlobalTasks(const EStateTreeRunStatus CompletionStatus);` — Stops active global evaluators and active global tasks.
- L1082 _protected prototype_ `void CallStopOnEvaluatorsAndGlobalTasks(const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& Frame, const FStateTreeTransitionResult& Transition, const FStateTreeIndex16 LastInitializedTaskIndex = FStateTreeIndex16());` — `UE_DEPRECATED(5.7, "Use StopGlobalsForFrameOnActiveInstances")`
- L1085 _protected prototype_ `EStateTreeRunStatus StartTemporaryEvaluatorsAndGlobalTasks(const FStateTreeExecutionFrame* CurrentParentFrame, FStateTreeExecutionFrame& CurrentFrame);` — Starts temporary instances of global evaluators and tasks for a given frame.
- L1088 _protected function_ `EStateTreeRunStatus StartTemporaryEvaluatorsAndGlobalTasks(const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame)` — `UE_DEPRECATED(5.6, "Use the non const version of StartTemporaryEvaluatorsAndGlobalTasks")`
- L1094 _protected prototype_ `void StopTemporaryEvaluatorsAndGlobalTasks(const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame);` — `UE_DEPRECATED(5.7, "Use the non const version of StopTemporaryEvaluatorsAndGlobalTasks")`
- L1097 _protected prototype_ `void StopTemporaryEvaluatorsAndGlobalTasks(const FStateTreeExecutionFrame* CurrentParentFrame, FStateTreeExecutionFrame& CurrentFrame, EStateTreeRunStatus StartResult);` — Stops temporary frame's evaluators and frame's tasks for the provided frame.
- L1103 _protected prototype_ `EStateTreeRunStatus TickTasks(const float DeltaTime);` — Ticks tasks of all active states starting from current state by delta time. @return Run status returned by the tasks.
- L1124 _protected prototype_ `FTickTaskResult TickTasks(const FTickTaskArguments& Args);` — Ticks tasks and updates the bindings for a specific state or frame.
- L1127 _protected prototype_ `EStateTreeRunStatus TickPrelude();` — Common functionality shared by the tick methods.
- L1128 _protected prototype_ `EStateTreeRunStatus TickPostlude();`
- L1131 _protected prototype_ `void TickUpdateTasksInternal(float DeltaTime);` — Handles task ticking part of the tick.
- L1134 _protected prototype_ `void TickTriggerTransitionsInternal();` — Handles transition triggering part of the tick.
- L1137 _protected prototype_ `void BroadcastTaskCompletionDispatchers(TNotNull<const UStateTree*> StateTree, int32 NodeIndex, UE::StateTree::ETaskCompletionStatus TaskStatus);` — Broadcasts task completion dispatchers when a task completes.
- L1140 _protected prototype_ `void BeginApplyTransition(const FStateTreeTransitionResult& InTransitionResult);` — Gives Execution Extension a chance to react.
- L1143 _protected typedef_ `using FMemoryRequirement = UE::StateTree::InstanceData::FEvaluationScopeInstanceContainer::FMemoryRequirement;`
- L1147 _private prototype_ `template<bool bOnActiveInstances> bool TestAllConditionsInternal(const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame, FStateTreeStateHandle CurrentStateHandle, const FMemoryRequirement& MemoryRequirement, const int32 ConditionsOffset, const int32 ConditionsNum, EStateTreeUpdatePhase Phase);`
- L1156 _private prototype_ `template<bool bOnActiveInstances, EConditionFunction ConditionFunction> void RunAllConditionsInternal(const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FCompactStateTreeState& CurrentState, const FStateTreeTransitionResult& CurrentTransition);`
- L1164 _protected prototype_ `bool TestAllConditionsOnActiveInstances(const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame, FStateTreeStateHandle CurrentStateHandle, const FMemoryRequirement& MemoryRequirement, const int32 ConditionsOffset, const int32 ConditionsNum, EStateTreeUpdatePhase Phase);` — Checks all conditions at given range. Should be used only on active node instances, assumes valid data handles and does not consider temporary node instances. @return True if all conditions pass.
- L1171 _protected prototype_ `bool TestAllConditionsWithValidation(const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame, FStateTreeStateHandle CurrentStateHandle, const FMemoryRequirement& MemoryRequirement, const int32 ConditionsOffset, const int32 ConditionsNum, EStateTreeUpdatePhase Phase);` — Checks all conditions at given range. This version validates the data handles and looks up temporary instances. @return True if all conditions pass.
- L1174 _protected prototype_ `bool TestAllConditions(const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const int32 ConditionsOffset, const int32 ConditionsNum);` — `UE_DEPRECATED(5.7, "Use TestAllConditionsWithValidation or TestAllConditionsOnActiveInstances. TestAllConditionsWithValidation can get the data from a temporary frame in state selection.")`
- L1180 _protected prototype_ `float EvaluateUtilityWithValidation(const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame, FStateTreeStateHandle StateHandle, const FMemoryRequirement& MemoryRequirement, const int32 ConsiderationsBegin, const int32 ConsiderationsNum, const float StateWeight);` — Calculate the final score of all considerations at given range. @return the final score
- L1183 _protected prototype_ `float EvaluateUtility(const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const int32 ConsiderationsOffset, const int32 ConsiderationsNum, const float StateWeight);` — `UE_DEPRECATED(5.7, "Use EvaluateUtilityWithValidation. It can get the data from a temporary frame in state selection.")`
- L1187 _private prototype_ `template<bool bOnActiveInstances> void EvaluatePropertyFunctionsInternal(const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame, FStateTreeIndex16 FuncsBegin, uint16 FuncsNum);`
- L1194 _protected prototype_ `void EvaluatePropertyFunctionsOnActiveInstances(const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame, FStateTreeIndex16 FuncsBegin, uint16 FuncsNum);` — Evaluate all function at given range. Should be used only on active node instances, assumes valid data handles and does not consider temporary node instances.
- L1200 _protected prototype_ `void EvaluatePropertyFunctionsWithValidation(const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame, FStateTreeIndex16 FuncsBegin, uint16 FuncsNum);` — Evaluate all function at given range. This version validates the data handles and looks up temporary instances.
- L1203 _protected prototype_ `bool RequestTransition( const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeStateHandle NextState, const EStateTreeTransitionPriority Priority, const FStateTreeSharedEvent* TransitionEvent = nullptr, const EStateTreeSelectionFallback Fallback = EStateTreeSelectionFallback::None);` — `UE_DEPRECATED(5.7, "Use the RequestTransitionInternal with the active state ID")`
- L1212 _protected prototype_ `void SetupNextTransition(const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeStateHandle NextState, const EStateTreeTransitionPriority Priority);` — `UE_DEPRECATED(5.7, "Use the SetupNextTransition with TransitionArguments")`
- L1224 _protected prototype_ `bool RequestTransitionInternal(const FStateTreeExecutionFrame& SourceFrame, UE::StateTree::FActiveStateID SourceStateID, UE::StateTree::ExecutionContext::FStateHandleContext TargetState, const FTransitionArguments& Args);` — Requests transition to a specified state.
- L1230 _protected prototype_ `void SetupNextTransition(const FStateTreeExecutionFrame& SourceFrame, UE::StateTree::FActiveStateID SourceStateID, UE::StateTree::ExecutionContext::FStateHandleContext TargetState, const FTransitionArguments& Args);` — Sets up NextTransition based on the provided parameters and the current execution status.
- L1252 _protected prototype_ `bool TriggerTransitions(const FTriggerTransitionsInternalArgs Args = FTriggerTransitionsInternalArgs());`
- L1256 _protected prototype_ `TOptional<FStateTreeTransitionResult> MakeTransitionResult(const FRecordedStateTreeTransitionResult& Transition) const;` — Create a new transition result from a recorded transition result. It will fail if the recorded transition is malformed.
- L1260 _protected prototype_ `FRecordedStateTreeTransitionResult MakeRecordedTransitionResult(const FStateTreeTransitionResult& Transition) const;` — Create a new recorded transition from a transition result.
- L1263 _protected prototype_ `FRecordedStateTreeTransitionResult MakeRecordedTransitionResult(const TSharedRef<FSelectStateResult>& Args, const FStateTreeTransitionResult& Transition) const;` — Create a new recorded transition from a select state result.
- L1268 _protected prototype_ `bool IsFinishedTaskValid(const UE::StateTree::FFinishedTask& Task) const;` — Confirms that the frame and state ID are valid and the task index is correct.
- L1277 _protected prototype_ `void UpdateCompletedStateList(bool bMarkTaskProcessed);` — Removes stale entries and fills the completed states list. The tree can be in a different state from when a finished task was added to the pending list and the finished task may not be valid. @param bMarkTaskProcessed when true, marks the tasks as processed. When false, only used the already marked tasks.
- L1280 _protected prototype_ `void UpdateCompletedStateList();` — `UE_DEPRECATED(5.6, "Replaced with FStateTreeTasksCompletionStatus")`
- L1285 _protected prototype_ `void MarkStateCompleted(UE::StateTree::FFinishedTask& FinisedTask);` — Adds the state to the completed list from a finished task.
- L1290 _protected prototype_ `EStateTreeRunStatus GetGlobalTasksCompletedStatesStatus() const;` — In the list of completed states, returns the run status when it's completed by a global task.
- L1293 _protected prototype_ `bool ForceTransitionInternal(const TArrayView<const UE::StateTree::ExecutionContext::FStateHandleContext> States, const TSharedRef<FSelectStateResult>& OutSelectionResult);` — Forces transition to a state. It will skip all conditions.
- L1297 _protected prototype_ `bool SelectState(const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeStateHandle NextState, FStateSelectionResult& OutSelectionResult, const FStateTreeSharedEvent* TransitionEvent = nullptr, const EStateTreeSelectionFallback Fallback = EStateTreeSelectionFallback::None);` — `UE_DEPRECATED(5.7, "Use the SelectState with the FSelectStateArguments argument.")`
- L1336 _protected prototype_ `bool SelectState(const FSelectStateArguments& SelectStateArgs, const TSharedRef<FSelectStateResult>& OutSelectionResult);` — Starting at the specified state, walking towards the leaf states. @param SelectStateArgs the arguments for SelectState. @param OutSelectionResult the result of the selection. @return True if succeeded to select new active states.
- L1340 _protected prototype_ `bool SelectStateInternal(const FStateTreeExecutionFrame* CurrentParentFrame, FStateTreeExecutionFrame& CurrentFrame, const FStateTreeExecutionFrame* CurrentFrameInActiveFrames, TConstArrayView<FStateTreeStateHandle> PathToNextState, FStateSelectionResult& OutSelectionResult, const FStateTreeSharedEvent* TransitionEvent = nullptr);` — `UE_DEPRECATED(5.7, "Use the SelectStateInternal with FSelectStateArguments argument.")`
- L1352 _protected prototype_ `bool SelectStateInternal( const FSelectStateArguments& Args, const FSelectStateInternalArguments& InternalArgs, const TSharedRef<FSelectStateResult>& OutSelectionResult);` — Used internally to do the recursive part of the SelectState().
- L1358 _protected prototype_ `TOptional<bool> SelectStateFromSourceInternal( const FSelectStateArguments& Args, const FSelectStateInternalArguments& InternalArgs, const TSharedRef<FSelectStateResult>& OutSelectionResult, const FStateTreeExecutionFrame& NextFrame, const FCompactStateTreeState& NextState, FStateTreeStateHandle NextStateHandle, bool bNewFrameCreated);` — Used internally to select state until we reach the transition source or the transition target.
- L1367 _protected prototype_ `bool SelectStateInternal_Linked( const FSelectStateArguments& Args, const FSelectStateInternalArguments& InternalArgs, const TSharedRef<FSelectStateResult>& OutSelectionResult, TNotNull<const UStateTree*> NextStateTree, const FCompactStateTreeState& NextState, bool bShouldCreateNewState );`
- L1376 _protected prototype_ `bool SelectStateInternal_LinkedAsset( const FSelectStateArguments& Args, const FSelectStateInternalArguments& InternalArgs, const TSharedRef<FSelectStateResult>& OutSelectionResult, TNotNull<const UStateTree*> NextStateTree, const FCompactStateTreeState& NextState, const UStateTree* NextLinkedStateAsset, bool bShouldCreateNewState);`
- L1385 _protected prototype_ `bool SelectStateInternal_TrySelectChildrenInOrder( const FSelectStateArguments& Args, const FSelectStateInternalArguments& InternalArgs, const TSharedRef<FSelectStateResult>& OutSelectionResult, TNotNull<const UStateTree*> NextStateTree, const FCompactStateTreeState& TargetState, const FStateTreeStateHandle TargetStateHandle);`
- L1393 _protected prototype_ `bool SelectStateInternal_TrySelectChildrenAtRandom( const FSelectStateArguments& Args, const FSelectStateInternalArguments& InternalArgs, const TSharedRef<FSelectStateResult>& OutSelectionResult, TNotNull<const UStateTree*> NextStateTree, const FCompactStateTreeState& TargetState, const FStateTreeStateHandle TargetStateHandle);`
- L1401 _protected prototype_ `bool SelectStateInternal_TrySelectChildrenWithHighestUtility( const FSelectStateArguments& Args, const FSelectStateInternalArguments& InternalArgs, const TSharedRef<FSelectStateResult>& OutSelectionResult, TNotNull<const UStateTree*> NextStateTree, const FCompactStateTreeState& TargetState, const FStateTreeStateHandle TargetStateHandle);`
- L1409 _protected prototype_ `bool SelectStateInternal_TrySelectChildrenAtRandomWeightedByUtility( const FSelectStateArguments& Args, const FSelectStateInternalArguments& InternalArgs, const TSharedRef<FSelectStateResult>& OutSelectionResult, TNotNull<const UStateTree*> NextStateTree, const FCompactStateTreeState& TargetState, const FStateTreeStateHandle TargetStateHandle);`
- L1417 _protected prototype_ `bool SelectStateInternal_TryFollowTransitions( const FSelectStateArguments& Args, const FSelectStateInternalArguments& InternalArgs, const TSharedRef<FSelectStateResult>& OutSelectionResult, TNotNull<const UStateTree*> NextStateTree, const FCompactStateTreeState& TargetState, const FStateTreeStateHandle TargetStateHandle);`
- L1426 _protected function_ `[[nodiscard]] FStateTreeExecutionState& GetExecState()` — @return StateTree execution state from the instance storage.
- L1432 _protected function_ `[[nodiscard]] const FStateTreeExecutionState& GetExecState() const` — @return const StateTree execution state from the instance storage.
- L1438 _protected prototype_ `void SetUpdatePhaseInExecutionState(FStateTreeExecutionState& ExecutionState, EStateTreeUpdatePhase UpdatePhase) const;` — Updates the update phase of the statetree execution state.
- L1441 _protected prototype_ `[[nodiscard]] FString GetStateStatusString(const FStateTreeExecutionState& ExecState) const;` — @return String describing state status for logging and debug.
- L1444 _protected prototype_ `[[nodiscard]] FString GetSafeStateName(const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeStateHandle State) const;` — @return String describing state name for logging and debug.
- L1447 _protected prototype_ `[[nodiscard]] FString GetSafeStateName(const UStateTree* StateTree, const FStateTreeStateHandle State) const;` — @return String describing state name for logging and debug.
- L1450 _protected prototype_ `[[nodiscard]] FString DebugGetStatePath(TConstArrayView<FStateTreeExecutionFrame> ActiveFrames, const FStateTreeExecutionFrame* CurrentFrame = nullptr, const int32 ActiveStateIndex = INDEX_NONE) const;` — @return String describing full path of an activate state for logging and debug.
- L1453 _protected prototype_ `[[nodiscard]] FString DebugGetEventsAsString() const;` — @return String describing all events that are currently being processed  for logging and debug.
- L1459 _protected prototype_ `FStateTreeDataView MoveTemporaryToInstance(const FStateTreeExecutionFrame& Frame, const FStateTreeIndex16 NodeIndex, const FStateTreeDataHandle Handle);` — Move the data from the temporary buffer to the allocated instance data relative to given frame. @return instanced data of the specified handle relative to given frame.
- L1462 _protected prototype_ `[[nodiscard]] FStateTreeDataView GetDataView(const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle Handle);` — @return data view of the specified handle relative to given frame.
- L1463 _protected prototype_ `[[nodiscard]] FStateTreeDataView GetDataView(const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FPropertyBindingCopyInfo& CopyInfo);`
- L1466 _protected prototype_ `[[nodiscard]] FStateTreeDataView GetExecutionRuntimeDataView() const;` — @return data view for the execution runtime view of the current node and frame.
- L1469 _protected prototype_ `[[nodiscard]] bool IsHandleSourceValid(const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle Handle) const;` — @return true if handle source is valid cified handle relative to given frame.
- L1470 _protected prototype_ `[[nodiscard]] bool IsHandleSourceValid(const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FPropertyBindingCopyInfo& CopyInfo) const;`
- L1473 _protected prototype_ `[[nodiscard]] FStateTreeDataView GetDataViewOrTemporary(const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle Handle);` — @return data view of the specified handle relative to the given frame, or tries to find a matching temporary instance.
- L1474 _protected prototype_ `[[nodiscard]] FStateTreeDataView GetDataViewOrTemporary(const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FPropertyBindingCopyInfo& CopyInfo);`
- L1477 _protected prototype_ `[[nodiscard]] FStateTreeDataView GetTemporaryDataView(const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle Handle);` — @return data view of the specified handle from temporary instance.
- L1483 _protected prototype_ `[[nodiscard]] FStateTreeDataView AddTemporaryInstance(const FStateTreeExecutionFrame& Frame, const FStateTreeIndex16 OwnerNodeIndex, const FStateTreeDataHandle DataHandle, FConstStructView NewInstanceData);` — Adds a temporary instance that can be located using frame and data handle later. @returns view to the newly added instance. If NewInstanceData is Object wrapper, the new object is returned.
- L1493 _protected prototype_ `void CopyAllBindingsOnActiveInstances(ECopyBindings CopyType);` — Copy the binding on all valid active instances.
- L1497 _private prototype_ `template<bool bOnActiveInstances> bool CopyBatchInternal(const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataView TargetView, const FStateTreeIndex16 BindingsBatch);`
- L1504 _protected prototype_ `bool CopyBatchOnActiveInstances(const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataView TargetView, const FStateTreeIndex16 BindingsBatch);` — Copies a batch of properties to the data in TargetView. Should be used only on active node instances, assumes valid data handles and does not consider temporary node instances.
- L1507 _protected prototype_ `bool CopyBatchWithValidation(const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataView TargetView, const FStateTreeIndex16 BindingsBatch);` — Copies a batch of properties to the data in TargetView. This version validates the data handles and looks up temporary instances.
- L1513 _protected prototype_ `bool CollectActiveExternalData();` — Collects external data for all StateTrees in active frames. @returns true if all external data are set successfully.
- L1519 _protected prototype_ `bool CollectActiveExternalData(const TArrayView<FStateTreeExecutionFrame> Frames);` — Collects external data for all StateTrees in active frames. @returns true if all external data are set successfully.
- L1525 _protected prototype_ `FStateTreeIndex16 CollectExternalData(const UStateTree* StateTree);` — Collects external data for specific State Tree asset. If the data is already collected, cached index is returned. @returns index in ContextAndExternalDataViews for the first external data.
- L1532 _protected prototype_ `bool SetGlobalParameters(FConstStructView Parameters);` — Stores copy of provided parameters as State Tree global parameters. @param Parameters parameters to copy @returns true if successfully set the parameters
- L1535 _protected prototype_ `bool SetGlobalParameters(const FInstancedPropertyBag& Parameters);` — `UE_DEPRECATED(5.8, "Use the version with a FConstStructView")`
- L1539 _protected prototype_ `void CaptureNewStateEvents(TConstArrayView<FStateTreeExecutionFrame> PrevFrames, TConstArrayView<FStateTreeExecutionFrame> NewFrames, TArrayView<FStateTreeFrameStateSelectionEvents> FramesStateSelectionEvents);` — `UE_DEPRECATED(5.7, "Use the CaptureNewStateEvents with the FSelectStateResult argument.")`
- L1545 _protected prototype_ `void CaptureNewStateEvents(const TSharedRef<const FSelectStateResult>& Args);` — Captures StateTree events used during the state selection.
- L1550 _protected prototype_ `FStateTreeWeakTaskRef MakeWeakTaskRefInternal() const;` — `UE_DEPRECATED(5.6, "FStateTreeWeakTaskRef is no longer used.")` — @return a weak reference for a task that can be stored for later uses.
- L1554 _protected member_ `FStateTreeInstanceData& InstanceData;` — Instance data used during current tick.
- L1558 _protected member_ `FStateTreeInstanceStorage* InstanceDataStorage = nullptr;` — Data storage of the instance data, cached for less indirections.
- L1561 _protected member_ `TSharedPtr<FStateTreeEventQueue> EventQueue;` — Events queue to use, cached for less indirections.
- L1566 _protected member_ `const FStateTreeReferenceOverrides* LinkedStateTreeOverrides = nullptr;` — Pointer to linked state tree overrides.
- L1569 _protected member_ `FStateTreeReferenceOverrides LinkedAssetStateTreeOverrides;` — Current linked state tree overrides.
- L1572 _protected member_ `TArray<FStateTreeDataView> ContextAndExternalDataViews;` — Data view of the context data.
- L1574 _protected member_ `FOnCollectStateTreeExternalData CollectExternalDataDelegate;`
- L1581 _protected member_ `TArray<FCollectedExternalDataCache> CollectedExternalCache;`
- L1582 _protected member_ `bool bActiveExternalDataCollected = false;`
- L1591 _protected member_ `static constexpr int32 ExpectedEvaluationScopeCacheLength = 4;`
- L1593 _protected member_ `TArray<FEvaluationScopeDataCache, TInlineAllocator<ExpectedEvaluationScopeCacheLength>> EvaluationScopeInstanceCaches;` — Data view of the evaluation scope instance data.
- L1595 _protected prototype_ `void PushEvaluationScopeInstanceContainer(UE::StateTree::InstanceData::FEvaluationScopeInstanceContainer& Container, const FStateTreeExecutionFrame& Frame);`
- L1596 _protected prototype_ `void PopEvaluationScopeInstanceContainer(UE::StateTree::InstanceData::FEvaluationScopeInstanceContainer& Container);`
- L1601 _protected member_ `TOptional<EStateTreeRunStatus> CompletedStateRunStatus;` — Run status set in FinishTask and that used after the task ticks.
- L1605 _protected member_ `FStateTreeTransitionResult NextTransition;` — Next transition, used by RequestTransition().
- L1609 _protected member_ `FStateTreeTransitionSource NextTransitionSource;` — Structure describing the origin of the state transition that caused the state change.
- L1612 _protected member_ `TOptional<int32> TriggerTransitionsFromFrameIndex;` — `UE_DEPRECATED(5.8, "No longer used.")`
- L1616 _protected member_ `TUniquePtr<FRequestTransitionResult> RequestedTransition;` — Current selected transition.
- L1619 _protected member_ `TArray<FStateTreeDelegateDispatcher> CurrentlyProcessedBroadcastedDelegates;` — Current broadcasted delegates we're processing.
- L1622 _protected member_ `const FStateTreeExecutionFrame* CurrentlyProcessedParentFrame = nullptr;` — Current frame we're processing.
- L1623 _protected member_ `const FStateTreeExecutionFrame* CurrentlyProcessedFrame = nullptr;`
- L1626 _protected member_ `FStateTreeInstanceStorage* CurrentlyProcessedSharedInstanceStorage = nullptr;` — Pointer to the shared instance data of the current frame we're processing.
- L1648 _protected member_ `const FStateSelectionResult* CurrentSelectionResult = nullptr;` — Current state selection result when performing recursive state selection, or nullptr if not applicable.
- L1653 _protected member_ `FStateTreeStateHandle CurrentlyProcessedState;` — Current state we're processing, or invalid if not applicable.
- L1677 _protected member_ `const FStateTreeEvent* CurrentlyProcessedTransitionEvent = nullptr;` — Current event we're processing in transition, or invalid if not applicable.
- L1703 _protected member_ `FSelectStateResult* CurrentlyProcessedStateSelectionResult = nullptr;` — Current select state result we're processing during the state selection, or invalid if not applicable. Used by the GetDataView when accessing event data. @note used only during selection and will always point to CurrentlyProcessedTemporaryStorage.
- L1706 _protected member_ `TSharedPtr<FSelectStateResult> CurrentlyProcessedTemporaryStorage;` — Current temporary storage for instance data, frames and state. Valid during the state selection, ExitState and EnterState.
- L1711 _protected member_ `FStateTreeFrameStateSelectionEvents* CurrentlyProcessedStateSelectionEvents = nullptr;` — `UE_DEPRECATED(5.7, "FStateTreeFrameStateSelectionEvents is now unused. Use CurrentlyProcessedStateSelectionResult")`
- L1737 _protected member_ `bool bAllowDirectTransitions = false;` — True if transitions are allowed to be requested directly instead of buffering.
- L1760 _protected member_ `const FStateTreeNodeBase* CurrentNode = nullptr;` — Currently processed nodes instance data. Ideally we would pass these to the nodes directly, but do not want to change the API currently.
- L1761 _protected member_ `int32 CurrentNodeIndex = FStateTreeIndex16::InvalidValue;`
- L1762 _protected member_ `FStateTreeDataHandle CurrentNodeDataHandle;`
- L1763 _protected member_ `FStateTreeDataView CurrentNodeInstanceData;`
- L1780 _protected member_ `bool bRecordTransitions = false;` — If true, the state tree context will create snapshots of transition events and capture them within RecordedTransitions for later use.
- L1783 _protected member_ `TArray<FRecordedStateTreeTransitionResult> RecordedTransitions;` — Captured snapshots for transition results that can be used to recreate transitions. This array is only populated if bRecordTransitions is true.
- L1786 _protected member_ `const FExternalGlobalParameters* ExternalGlobalParameters = nullptr;` — Memory mapping structure used for redirecting property-bag copies to external (raw) memory pointers

#### struct `FStateTreeExecutionContext::FExternalGlobalParameters`  
`struct FExternalGlobalParameters`  
_L365-373_
- desc: Structure to-be-populated and set for any StateTree using any EStateTreeDataSourceType::ExternalGlobalParameterData bindings
- L368 _public prototype_ `bool Add(const FPropertyBindingCopyInfo& Copy, uint8* InParameterMemory);` — Add memory mapping, this expects InParameterMemory to resolve correctly for the SourceLeafProperty and SourceIndirection
- L369 _public prototype_ `uint8* Find(const FPropertyBindingCopyInfo& Copy) const;`
- L370 _public prototype_ `void Reset();`
- L372 _private member_ `TMap<uint32, uint8*> Mappings;`

#### struct `FStateTreeExecutionContext::FStartParameters`  
`struct FStartParameters`  
_L440-471_
- L443 _public member_ `FConstStructView InitialGlobalParameters;` — Optional override of global parameters initial values.
- L446 _public member_ `TInstancedStruct<FStateTreeExecutionExtension> ExecutionExtension;` — Optional extension for the execution context.
- L449 _public member_ `const TSharedPtr<FStateTreeEventQueue> SharedEventQueue;` — Optional event queue from another instance data. Marks the event queue not owned.
- L452 _public member_ `TOptional<int32> RandomSeed;` — Optional override of initial seed for RandomStream. By default FPlatformTime::Cycles() will be used.
- L464 _public member_ `TOptional<FStateToSelectOverrideArgs> SelectStateOverrideArgs;` — Optional override of initial state to select. By default, root state will be selected.
- L469 _public member_ `const FInstancedPropertyBag* GlobalParameters = nullptr;` — Optional override of global parameters initial values.

#### struct `FStateTreeExecutionContext::FStartParameters::FStateToSelectOverrideArgs`  
`struct FStateToSelectOverrideArgs`  
_L454-461_
- L457 _public member_ `FGameplayTag StateTag;` — Optional override of tag of start state to select.
- L460 _public member_ `UStateTree::EStateGameplayTagQueryMethod TagQueryMethod = UStateTree::EStateGameplayTagQueryMethod::MatchesExact;` — Does the tag needs to match exactly when searching the state.

#### struct `FStateTreeExecutionContext::FSelectionEventWithID`  
`struct FSelectionEventWithID`  
_L832-836_
- desc: Event used during state selection. Identified by the ID of the active state that consumed it.
- L834 _public member_ `UE::StateTree::FActiveState State;`
- L835 _public member_ `FStateTreeSharedEvent Event;`

#### struct `FStateTreeExecutionContext::FSelectStateResult`  
`struct FSelectStateResult : public UE::StateTree::ExecutionContext::ITemporaryStorage`  
_L839-880_
- inherits: `UE::StateTree::ExecutionContext::ITemporaryStorage`
- desc: Describes a result of States Selection.
- L841 _public prototype_ `FSelectStateResult() = default;`
- L842 _public prototype_ `virtual ~FSelectStateResult() = default;`
- L845 _public member_ `TArray<UE::StateTree::FActiveState> SelectedStates;` — The active states selected. They are in order from the root to the leaf.
- L848 _public member_ `TArray<UE::StateTree::FActiveFrameID, TInlineAllocator<4>> SelectedFrames;` — The selected frame ID. The frame can be in the current active list or in the TemporaryFrames list.
- L854 _public member_ `TArray<FStateTreeExecutionFrame, TInlineAllocator<2>> TemporaryFrames;` — New execution frame created during the state selection. The active state list is empty and will be filled during EnterState()
- L857 _public member_ `TArray<FSelectionEventWithID, TInlineAllocator<2>> SelectionEvents;` — Events used during the state selection.
- L860 _public member_ `UE::StateTree::FActiveState TargetState;` — The requested target of the selection.
- L863 _public prototype_ `FStateTreeExecutionFrame& MakeAndAddTemporaryFrame(UE::StateTree::FActiveFrameID FrameID, const UE::StateTree::FExecutionFrameHandle& FrameHandle, bool bIsGlobalFrame);` — @return a new temporary frame
- L864 _public prototype_ `FStateTreeExecutionFrame& MakeAndAddTemporaryFrameWithNewRoot(UE::StateTree::FActiveFrameID FrameID, const UE::StateTree::FExecutionFrameHandle& FrameHandle, FStateTreeExecutionFrame& OtherFrame);`
- L867 _public function_ `FStateTreeExecutionFrame* FindTemporaryFrame(UE::StateTree::FActiveFrameID FrameID)` — @return a temporary frame by ID.
- L877 _public prototype_ `virtual FFrameAndParent GetExecutionFrame(UE::StateTree::FActiveFrameID ID) override;`
- L878 _public prototype_ `virtual UE::StateTree::FActiveState GetStateHandle(UE::StateTree::FActiveStateID ID) const override;`
- L879 _public prototype_ `virtual TConstArrayView<FStateTreeExecutionFrame> GetTemporaryFrames() const override;`

#### struct `FStateTreeExecutionContext::FStateSelectionResult`  
`FStateSelectionResult`  
_L885-942_
- reflection: `UE_DEPRECATED(5.7, "The selection result changed to include the state ID and frame ID")`
- L888 _public member_ `static constexpr int32 MaxExecutionFrames = 8;` — Max number of execution frames handled during state selection.
- L890 _public prototype_ `FStateSelectionResult() = default;`
- L891 _public function_ `explicit FStateSelectionResult(TConstArrayView<FStateTreeExecutionFrame> InFrames)`
- L897 _public function_ `bool IsFull() const`
- L902 _public function_ `void PushFrame(FStateTreeExecutionFrame Frame)`
- L908 _public function_ `void PopFrame()`
- L914 _public function_ `bool ContainsFrames() const`
- L919 _public function_ `int32 FramesNum() const`
- L924 _public function_ `TArrayView<FStateTreeExecutionFrame> GetSelectedFrames()`
- L929 _public function_ `TConstArrayView<FStateTreeExecutionFrame> GetSelectedFrames() const`
- L934 _public function_ `TArrayView<FStateTreeFrameStateSelectionEvents> GetFramesStateSelectionEvents()`
- L940 _protected member_ `TArray<FStateTreeExecutionFrame, TFixedAllocator<MaxExecutionFrames>> SelectedFrames;`
- L941 _protected member_ `TArray<FStateTreeFrameStateSelectionEvents, TFixedAllocator<MaxExecutionFrames>> FramesStateSelectionEvents;`

#### struct `FStateTreeExecutionContext::FRequestTransitionResult`  
`struct FRequestTransitionResult`  
_L946-951_
- desc: The result of the RequestTransition function.
- L948 _public member_ `TSharedPtr<FSelectStateResult> Selection;`
- L949 _public member_ `FStateTreeTransitionResult Transition;`
- L950 _public member_ `FStateTreeTransitionSource Source;`

#### struct `FStateTreeExecutionContext::FTickTaskResult`  
`struct FTickTaskResult`  
_L1105-1108_
- L1107 _public member_ `bool bShouldTickTasks = true;`

#### struct `FStateTreeExecutionContext::FTickTaskArguments`  
`struct FTickTaskArguments`  
_L1109-1122_
- L1111 _public prototype_ `FTickTaskArguments() = default;`
- L1112 _public member_ `float DeltaTime = 0.f;`
- L1113 _public member_ `int32 TasksBegin = 0;`
- L1114 _public member_ `int32 TasksNum = 0;`
- L1115 _public member_ `int32 Indent = 0;`
- L1116 _public member_ `const FStateTreeExecutionFrame* ParentFrame = nullptr;`
- L1117 _public member_ `FStateTreeExecutionFrame* Frame = nullptr;`
- L1118 _public member_ `UE::StateTree::FActiveStateID StateID;`
- L1119 _public member_ `UE::StateTree::FTasksCompletionStatus* TasksCompletionStatus = nullptr;`
- L1120 _public member_ `bool bIsGlobalTasks = false;`
- L1121 _public member_ `bool bShouldTickTasks = true;`

#### enum `FStateTreeExecutionContext::EConditionFunction`  
`enum class EConditionFunction`  
_L1149-1154_
- L1151 _public enumerator_ `EnterState`
- L1152 _public enumerator_ `ExitState`
- L1153 _public enumerator_ `StateCompleted`

#### struct `FStateTreeExecutionContext::FTransitionArguments`  
`struct FTransitionArguments`  
_L1215-1221_
- desc: Optional arguments for a transition request.
- L1217 _public member_ `EStateTreeTransitionPriority Priority = EStateTreeTransitionPriority::Normal;`
- L1218 _public member_ `FStateTreeSharedEvent TransitionEvent;`
- L1219 _public member_ `EStateTreeSelectionFallback Fallback = EStateTreeSelectionFallback::None;`
- L1220 _public member_ `EStateTreeStateSelectionRules SelectionRules = EStateTreeStateSelectionRules::None;`

#### struct `FStateTreeExecutionContext::FTriggerTransitionsInternalArgs`  
`struct FTriggerTransitionsInternalArgs`  
_L1247-1250_
- desc: Tick (if needed) event, delayed, delegate and, tick state completion transitions. Test the completed state transitions. @return if the transition is valid and should be entered.
- L1249 _public member_ `TOptional<int32> CompletedSubtreeParentFrameIndex;`

#### enum `FStateTreeExecutionContext::ESelectStateBehavior`  
`enum class ESelectStateBehavior : uint8`  
_L1301-1311_
- desc: The different type of selections.
- L1304 _public enumerator_ `StateTransition` — From a state transition. Normal rules apply.
- L1310 _public enumerator_ `Forced` — From a force transition. The state's selection behavior and condition will not be respected. The target is the final state.

#### struct `FStateTreeExecutionContext::FSelectStateArguments`  
`struct FSelectStateArguments`  
_L1312-1328_
- L1315 _public member_ `TArrayView<const UE::StateTree::FActiveState> ActiveStates;` — The current list of active states.
- L1317 _public member_ `UE::StateTree::FActiveState SourceState;` — The state that requested the transition.
- L1319 _public member_ `UE::StateTree::ExecutionContext::FStateHandleContext TargetState;` — The state that we want to select. Depending on the state's selection behavior, another state can be selected.
- L1321 _public member_ `FStateTreeSharedEvent TransitionEvent;` — Transition event used by transition to trigger the state selection.
- L1323 _public member_ `EStateTreeSelectionFallback Fallback = EStateTreeSelectionFallback::None;` — Fallback selection behavior to execute if it fails to select the desired state.
- L1325 _public member_ `ESelectStateBehavior Behavior = ESelectStateBehavior::StateTransition;` — The type of selection.
- L1327 _public member_ `EStateTreeStateSelectionRules SelectionRules = EStateTreeStateSelectionRules::None;` — Rule to Selection state rules.

#### struct `FStateTreeExecutionContext::FSelectStateInternalArguments`  
`struct FSelectStateInternalArguments`  
_L1343-1349_
- L1345 _public member_ `TArrayView<const UE::StateTree::FActiveState> MissingActiveStates;`
- L1346 _public member_ `UE::StateTree::FActiveFrameID MissingSourceFrameID;`
- L1347 _public member_ `TArrayView<const UE::StateTree::FActiveState> MissingSourceStates;`
- L1348 _public member_ `TArrayView<const UE::StateTree::ExecutionContext::FStateHandleContext> MissingStatesToReachTarget;`

#### enum `FStateTreeExecutionContext::ECopyBindings`  
`enum class ECopyBindings : uint8`  
_L1485-1490_
- L1487 _public enumerator_ `EnterState`
- L1488 _public enumerator_ `Tick`
- L1489 _public enumerator_ `ExitState`

#### struct `FStateTreeExecutionContext::FCollectedExternalDataCache`  
`struct FCollectedExternalDataCache`  
_L1576-1580_
- L1578 _public member_ `const UStateTree* StateTree = nullptr;`
- L1579 _public member_ `FStateTreeIndex16 BaseIndex;`

#### struct `FStateTreeExecutionContext::FEvaluationScopeDataCache`  
`struct FEvaluationScopeDataCache`  
_L1585-1589_
- desc: Holds the container. Multiple instances with the same state tree can occur in a recursive call.
- L1587 _public member_ `UE::StateTree::InstanceData::FEvaluationScopeInstanceContainer* Container;`
- L1588 _public member_ `TObjectKey<UStateTree> StateTree;`

#### struct `FStateTreeExecutionContext::FCurrentlyProcessedFrameScope`  
`struct FCurrentlyProcessedFrameScope`  
_L1629-1642_
- desc: Helper struct to track currently processed frame.
- L1631 _public prototype_ `FCurrentlyProcessedFrameScope(FStateTreeExecutionContext& InContext, const FStateTreeExecutionFrame* CurrentParentFrame, const FStateTreeExecutionFrame& CurrentFrame);`
- L1632 _public prototype_ `FCurrentlyProcessedFrameScope(const FCurrentlyProcessedFrameScope&) = delete;`
- L1633 _public prototype_ `FCurrentlyProcessedFrameScope& operator=(const FCurrentlyProcessedFrameScope&) = delete;`
- L1634 _public prototype_ `~FCurrentlyProcessedFrameScope();`
- L1637 _private member_ `FStateTreeExecutionContext& Context;`
- L1638 _private member_ `int32 SavedFrameIndex = 0;`
- L1639 _private member_ `FStateTreeInstanceStorage* SavedSharedInstanceDataStorage = nullptr;`
- L1640 _private member_ `const FStateTreeExecutionFrame* SavedFrame = nullptr;`
- L1641 _private member_ `const FStateTreeExecutionFrame* SavedParentFrame = nullptr;`

#### struct `FStateTreeExecutionContext::FCurrentlyProcessedStateScope`  
`struct FCurrentlyProcessedStateScope`  
_L1656-1674_
- desc: Helper struct to track currently processed state.
- L1658 _public function_ `FCurrentlyProcessedStateScope(FStateTreeExecutionContext& InContext, const FStateTreeStateHandle State) : Context(InContext)`
- L1664 _public prototype_ `FCurrentlyProcessedStateScope(const FCurrentlyProcessedStateScope&) = delete;`
- L1665 _public prototype_ `FCurrentlyProcessedStateScope& operator=(const FCurrentlyProcessedStateScope&) = delete;`
- L1666 _public function_ `~FCurrentlyProcessedStateScope()`
- L1672 _private member_ `FStateTreeExecutionContext& Context;`
- L1673 _private member_ `FStateTreeStateHandle SavedState = FStateTreeStateHandle::Invalid;`

#### struct `FStateTreeExecutionContext::FCurrentlyProcessedTransitionEventScope`  
`struct FCurrentlyProcessedTransitionEventScope`  
_L1680-1696_
- desc: Helper struct to track currently processed transition event.
- L1682 _public function_ `FCurrentlyProcessedTransitionEventScope(FStateTreeExecutionContext& InContext, const FStateTreeEvent* Event) : Context(InContext)`
- L1689 _public function_ `~FCurrentlyProcessedTransitionEventScope()`
- L1695 _private member_ `FStateTreeExecutionContext& Context;`

#### struct `FStateTreeExecutionContext::FCurrentFrameStateSelectionEventsScope`  
`FCurrentFrameStateSelectionEventsScope`  
_L1715-1732_
- reflection: `UE_DEPRECATED(5.7, "FStateTreeFrameStateSelectionEvents is now unused. Use CurrentlyProcessedStateSelectionResult")`
- L1717 _public function_ `FCurrentFrameStateSelectionEventsScope(FStateTreeExecutionContext& InContext, FStateTreeFrameStateSelectionEvents& InCurrentlyProcessedStateSelectionEvents) : Context(InContext)`
- L1724 _public function_ `~FCurrentFrameStateSelectionEventsScope()`
- L1730 _private member_ `FStateTreeExecutionContext& Context;`
- L1731 _private member_ `FStateTreeFrameStateSelectionEvents* SavedStateSelectionEvents = nullptr;`

#### struct `FStateTreeExecutionContext::FAllowDirectTransitionsScope`  
`struct FAllowDirectTransitionsScope`  
_L1740-1757_
- desc: Helper struct to track when it is allowed to request transitions.
- L1742 _public function_ `FAllowDirectTransitionsScope(FStateTreeExecutionContext& InContext) : Context(InContext)`
- L1749 _public function_ `~FAllowDirectTransitionsScope()`
- L1755 _private member_ `FStateTreeExecutionContext& Context;`
- L1756 _private member_ `bool bSavedAllowDirectTransitions = false;`

#### struct `FStateTreeExecutionContext::FNodeInstanceDataScope`  
`struct FNodeInstanceDataScope`  
_L1766-1777_
- desc: Helper struct to set current node data.
- L1768 _public prototype_ `FNodeInstanceDataScope(FStateTreeExecutionContext& InContext, const FStateTreeNodeBase* InNode, const int32 InNodeIndex, const FStateTreeDataHandle InNodeDataHandle, const FStateTreeDataView InNodeInstanceData);`
- L1769 _public prototype_ `~FNodeInstanceDataScope();`
- L1772 _private member_ `FStateTreeExecutionContext& Context;`
- L1773 _private member_ `const FStateTreeNodeBase* SavedNode = nullptr;`
- L1774 _private member_ `int32 SavedNodeIndex = FStateTreeIndex16::InvalidValue;`
- L1775 _private member_ `FStateTreeDataHandle SavedNodeDataHandle;`
- L1776 _private member_ `FStateTreeDataView SavedNodeInstanceData;`

#### struct `FConstStateTreeExecutionContextView`  
`struct FConstStateTreeExecutionContextView`  
_L1792-1815_
- desc: The const version of a StateTree Execution Context that prevents using the FStateTreeInstanceData with non-const member function.
- L1795 _public function_ `FConstStateTreeExecutionContextView(UObject& InOwner, const UStateTree& InStateTree, const FStateTreeInstanceData& InInstanceData) : ExecutionContext(InOwner, InStateTree, const_cast<FStateTreeInstanceData&>(InInstanceData))`
- L1799 _public function_ `operator const FStateTreeExecutionContext& ()`
- L1804 _public function_ `const FStateTreeExecutionContext& Get() const`
- L1810 _private prototype_ `FConstStateTreeExecutionContextView(const FConstStateTreeExecutionContextView&) = delete;`
- L1811 _private prototype_ `FConstStateTreeExecutionContextView& operator=(const FConstStateTreeExecutionContextView&) = delete;`
- L1814 _private member_ `FStateTreeExecutionContext ExecutionContext;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API STATETREEMODULE_API`
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace StateTree` (scope `UE`)
- L34 _namespace_ `namespace InstanceData` (scope `UE::StateTree`)
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace StateTree` (scope `UE`)
- L39 _namespace_ `namespace ExecutionContext` (scope `UE::StateTree`)
- L41 _prototype_ `bool MarkDelegateAsBroadcasted(FStateTreeDelegateDispatcher Dispatcher, const FStateTreeExecutionFrame& CurrentFrame, FStateTreeInstanceStorage& Storage);` (scope `UE::StateTree::ExecutionContext`)
- L42 _prototype_ `EStateTreeRunStatus GetPriorityRunStatus(EStateTreeRunStatus A, EStateTreeRunStatus B);` (scope `UE::StateTree::ExecutionContext`)
- L43 _prototype_ `UE::StateTree::ETaskCompletionStatus CastToTaskStatus(EStateTreeFinishTaskType FinishTask);` (scope `UE::StateTree::ExecutionContext`)
- L44 _prototype_ `EStateTreeRunStatus CastToRunStatus(EStateTreeFinishTaskType FinishTask);` (scope `UE::StateTree::ExecutionContext`)
- L45 _prototype_ `UE::StateTree::ETaskCompletionStatus CastToTaskStatus(EStateTreeRunStatus InStatus);` (scope `UE::StateTree::ExecutionContext`)
- L46 _prototype_ `EStateTreeRunStatus CastToRunStatus(UE::StateTree::ETaskCompletionStatus InStatus);` (scope `UE::StateTree::ExecutionContext`)
- L48 _typedef_ `using FTaskCompletionDelegateDispatcherContainer = TArray<FStateTreeDelegateDispatcher, TInlineAllocator<3>>;` (scope `UE::StateTree::ExecutionContext`)
- L50 _prototype_ `FTaskCompletionDelegateDispatcherContainer GetTaskCompletionDispatcher(TNotNull<const UStateTree*> StateTree, int32 NodeIndex, UE::StateTree::ETaskCompletionStatus TaskStatus);` (scope `UE::StateTree::ExecutionContext`) — Find the dispatcher for a task completion if one matches the task node and condition.
- L65 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FOnCollectStateTreeExternalData, const FStateTreeExecutionContext& , const UStateTree* , TArrayView<const FStateTreeExternalDataDesc> , TArrayView<FStateTreeDataView> );` — Delegate used by the execution context to collect external data views for a given StateTree asset. The caller is expected to iterate over the ExternalDataDescs array, find the matching external data, and store it in the OutDataViews at the same index: for (int32 Index = 0; Index < ExternalDataDescs.Num(); Index++) { const FStateTreeExternalDataDesc& Desc = ExternalDataDescs[Index]; // Find data requested by Desc OutDataViews[Index] = ...; }
- L65 _prototype_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FOnCollectStateTreeExternalData, const FStateTreeExecutionContext& , const UStateTree* , TArrayView<const FStateTreeExternalDataDesc> , TArrayView<FStateTreeDataView> );` — Delegate used by the execution context to collect external data views for a given StateTree asset. The caller is expected to iterate over the ExternalDataDescs array, find the matching external data, and store it in the OutDataViews at the same index: for (int32 Index = 0; Index < ExternalDataDescs.Num(); Index++) { const FStateTreeExternalDataDesc& Desc = ExternalDataDescs[Index]; // Find data requested by Desc OutDataViews[Index] = ...; }
- L116 _function_ `` (scope `FStateTreeReadOnlyExecutionContext::HasEventToProcess`)
- L575 _function_ `` (scope `FStateTreeExecutionContext::ForEachEvent`)
- L871 _function_ `` (scope `FStateTreeExecutionContext::FSelectStateResult::FindTemporaryFrame`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeExecutionContextTypes.h` (Public)


#### struct `UE::StateTree::ExecutionContext::FStateHandleContext`  
`struct FStateHandleContext`  
_L16-29_
- desc: Helper that combines the state handle and its tree asset.
- L18 _public prototype_ `FStateHandleContext() = default;`
- L19 _public function_ `FStateHandleContext(TNotNull<const UStateTree*> InStateTree, FStateTreeStateHandle InStateHandle) : StateTree(InStateTree) , StateHandle(InStateHandle)`
- L25 _public prototype_ `bool operator==(const FStateHandleContext&) const = default;`
- L27 _public member_ `const UStateTree* StateTree = nullptr;`
- L28 _public member_ `FStateTreeStateHandle StateHandle;`

#### struct `UE::StateTree::ExecutionContext::ITemporaryStorage`  
`struct ITemporaryStorage`  
_L32-45_
- desc: Interface of structure that can store temporary frames and states.
- L34 _public prototype_ `virtual ~ITemporaryStorage() = default;`
- L42 _public prototype_ `virtual FFrameAndParent GetExecutionFrame(UE::StateTree::FActiveFrameID ID) = 0;`
- L43 _public prototype_ `virtual UE::StateTree::FActiveState GetStateHandle(UE::StateTree::FActiveStateID ID) const = 0;`
- L44 _public prototype_ `virtual TConstArrayView<FStateTreeExecutionFrame> GetTemporaryFrames() const = 0;`

#### struct `UE::StateTree::ExecutionContext::ITemporaryStorage::FFrameAndParent`  
`struct FFrameAndParent`  
_L36-40_
- L38 _public member_ `FStateTreeExecutionFrame* Frame = nullptr;`
- L39 _public member_ `UE::StateTree::FActiveFrameID ParentFrameID;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATETREEMODULE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace StateTree` (scope `UE`)
- L13 _namespace_ `namespace ExecutionContext` (scope `UE::StateTree`)
- L47 _prototype_ `const FStateTreeExecutionFrame* FindExecutionFrame(FActiveFrameID InFrameID, TConstArrayView<FStateTreeExecutionFrame> InActiveFrames, TConstArrayView<FStateTreeExecutionFrame> InTemporaryFrames);` (scope `UE::StateTree::ExecutionContext`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeExecutionExtension.h` (Public)


#### struct `FStateTreeExecutionExtension`  
`struct FStateTreeExecutionExtension`  
_L23-81_
- reflection: `USTRUCT()`
- desc: Used by the execution context or a weak execution context to extend their functionalities.
- L45 _public prototype_ `virtual ~FStateTreeExecutionExtension() = default;`
- L48 _public function_ `virtual FString GetInstanceDescription(const FContextParameters& Context) const` — Prefix that will be used by STATETREE_LOG and STATETREE_CLOG, using Entity description.
- L62 _public function_ `virtual void ScheduleNextTick(const FContextParameters& Context, const FNextTickArguments& Args)` — Callback when the execution context request the tree to wakeup from a schedule tick sleep.
- L68 _public function_ `virtual void ScheduleNextTick(const FContextParameters& Context) final` — `UE_DEPRECATED(5.7, "Use ScheduleNextTick with the FNextTickArguments parameter.")`
- L71 _public function_ `virtual void OnLinkedStateTreeOverridesSet(const FContextParameters& Context, const FStateTreeReferenceOverrides& Overrides)` — Callback when the overrides are set to the execution context .
- L77 _public function_ `virtual void OnBeginApplyTransition(const FContextParameters& Context, const FStateTreeTransitionResult& TransitionResult)` — Callback before the execution context applies a transition.

#### struct `FStateTreeExecutionExtension::FContextParameters`  
`struct FContextParameters`  
_L27-43_
- L29 _public function_ `FContextParameters(UObject& Owner, const UStateTree& StateTree, FStateTreeInstanceStorage& InstanceData) : Owner(Owner) , StateTree(StateTree) , InstanceData(InstanceData)`
- L34 _public function_ `FContextParameters(TNotNull<UObject*> Owner, TNotNull<const UStateTree*> StateTree, FStateTreeInstanceStorage& InstanceData) : Owner(*Owner) , StateTree(*StateTree) , InstanceData(InstanceData)`
- L40 _public member_ `UObject& Owner;`
- L41 _public member_ `const UStateTree& StateTree;`
- L42 _public member_ `FStateTreeInstanceStorage& InstanceData;`

#### struct `FStateTreeExecutionExtension::FNextTickArguments`  
`struct FNextTickArguments`  
_L53-59_
- L55 _public prototype_ `FNextTickArguments();`
- L56 _public prototype_ `explicit FNextTickArguments(UE::StateTree::ETickReason Reason);`
- L58 _public member_ `UE::StateTree::ETickReason Reason;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STATETREEMODULE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace StateTree` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeExecutionRuntimeDataTypes.h` (Public)


#### struct `UE::StateTree::InstanceData::FExecutionRuntimeData`  
`struct FExecutionRuntimeData`  
_L18-27_
- reflection: `USTRUCT()`
- desc: Helper structure that holds the execution runtime instances.
- L23 _public member_ `TObjectKey<UStateTree> StateTree;` — The state tree of the instances.
- L26 _public member_ `UE::StateTree::InstanceData::FInstanceContainer Instances;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API STATETREEMODULE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace StateTree` (scope `UE`)
- L14 _namespace_ `namespace InstanceData` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeExecutionTypes.h` (Public)


#### enum `EStateTreeUpdatePhase`  
`enum class EStateTreeUpdatePhase : uint8`  
_L25-48_
- reflection: `UENUM()`
- desc: Enumeration for the different update phases. This is used as context information when tracing debug events.
- L27 _public enumerator_ `Unset = 0`
- L28 _public enumerator_ `StartTree UMETA(DisplayName = "Start Tree")`
- L29 _public enumerator_ `StopTree UMETA(DisplayName = "Stop Tree")`
- L30 _public enumerator_ `StartGlobalTasks UMETA(DisplayName = "Start Global Tasks & Evaluators")`
- L31 _public enumerator_ `StartGlobalTasksForSelection UMETA(DisplayName = "Start Global Tasks & Evaluators for selection")`
- L32 _public enumerator_ `StopGlobalTasks UMETA(DisplayName = "Stop Global Tasks & Evaluators")`
- L33 _public enumerator_ `StopGlobalTasksForSelection UMETA(DisplayName = "Stop Global Tasks & Evaluators for selection")`
- L34 _public enumerator_ `TickStateTree UMETA(DisplayName = "Tick State Tree")`
- L35 _public enumerator_ `ApplyTransitions UMETA(DisplayName = "Transition")`
- L36 _public enumerator_ `TickTransitions UMETA(DisplayName = "Tick Transitions")`
- L37 _public enumerator_ `TriggerTransitions UMETA(DisplayName = "Trigger Transitions")`
- L38 _public enumerator_ `TickingGlobalTasks UMETA(DisplayName = "Tick Global Tasks & Evaluators")`
- L39 _public enumerator_ `TickingTasks UMETA(DisplayName = "Tick Tasks")`
- L40 _public enumerator_ `TransitionConditions UMETA(DisplayName = "Transition conditions")`
- L41 _public enumerator_ `StateSelection UMETA(DisplayName = "Try Enter")`
- L42 _public enumerator_ `TrySelectBehavior UMETA(DisplayName = "Try Select Behavior")`
- L43 _public enumerator_ `EnterConditions UMETA(DisplayName = "Enter conditions")`
- L44 _public enumerator_ `EnterStates UMETA(DisplayName = "Enter States")`
- L45 _public enumerator_ `ExitStates UMETA(DisplayName = "Exit States")`
- L46 _public enumerator_ `StateCompleted UMETA(DisplayName = "State(s) Completed")`
- L47 _public enumerator_ `EvaluateUtility UMETA(DisplayName = "Evaluate Utility")`

#### enum `EStateTreeRunStatus`  
`enum class EStateTreeRunStatus : uint8`  
_L53-69_
- reflection: `UENUM(BlueprintType)`
- desc: Status describing current run status of a State Tree.
- L56 _public enumerator_ `Running` — Tree is still running.
- L59 _public enumerator_ `Stopped` — The State Tree was requested to stop without a particular success or failure state.
- L62 _public enumerator_ `Succeeded` — Tree execution has stopped on success.
- L65 _public enumerator_ `Failed` — Tree execution has stopped on failure.
- L68 _public enumerator_ `Unset` — Status not set.

#### enum `EStateTreeFinishTaskType`  
`enum class EStateTreeFinishTaskType : uint8`  
_L74-81_
- reflection: `UENUM()`
- desc: Status describing how a task finished.
- L77 _public enumerator_ `Failed` — The task execution failed.
- L80 _public enumerator_ `Succeeded` — The task execution succeed.

#### enum `EStateTreeStateChangeType`  
`enum class EStateTreeStateChangeType : uint8`  
_L86-96_
- reflection: `UENUM()`
- desc: State change type. Passed to EnterState() and ExitState() to indicate how the state change affects the state and Evaluator or Task is on.
- L89 _public enumerator_ `None` — Not an activation
- L92 _public enumerator_ `Changed` — The state became activated or deactivated.
- L95 _public enumerator_ `Sustained` — The state is parent of new active state and sustained previous active state.

#### enum `EStateTreeConditionEvaluationMode`  
`enum class EStateTreeConditionEvaluationMode : uint8`  
_L101-111_
- reflection: `UENUM()`
- desc: Defines how to assign the result of a condition to evaluate.
- L104 _public enumerator_ `Evaluated` — Condition is evaluated to set the result. This is the normal behavior.
- L107 _public enumerator_ `ForcedTrue` — Do not evaluate the condition and force result to 'true'.
- L110 _public enumerator_ `ForcedFalse` — Do not evaluate the condition and force result to 'false'.

#### struct `FStateTreeExternalDataHandle`  
`struct FStateTreeExternalDataHandle`  
_L119-137_
- reflection: `USTRUCT()`
- desc: Handle to access an external struct or object. Note: Use the templated version below.
- L124 _public prototype_ `FStateTreeExternalDataHandle() = default;`
- L125 _public prototype_ `FStateTreeExternalDataHandle(const FStateTreeExternalDataHandle& Other) = default;`
- L126 _public prototype_ `FStateTreeExternalDataHandle(FStateTreeExternalDataHandle&& Other) = default;`
- L127 _public prototype_ `FStateTreeExternalDataHandle& operator=(FStateTreeExternalDataHandle const& Other) = default;`
- L128 _public prototype_ `FStateTreeExternalDataHandle& operator=(FStateTreeExternalDataHandle&& Other) = default;`
- L131 _public member_ `static const FStateTreeExternalDataHandle Invalid;`
- L133 _public function_ `bool IsValid() const`
- L136 _public member_ `FStateTreeDataHandle DataHandle = FStateTreeDataHandle::Invalid;` — `UPROPERTY()`

#### struct `TStateTreeExternalDataHandle`  
`template<typename T, EStateTreeExternalDataRequirement Req = EStateTreeExternalDataRequirement::Required> struct TStateTreeExternalDataHandle : FStateTreeExternalDataHandle`  
_L165-169_
- inherits: `FStateTreeExternalDataHandle`
- desc: Handle to access an external struct or object. This reference handle can be used in StateTree tasks and evaluators to have quick access to external data. The type provided to the template is used by the linker and context to pass along the type. USTRUCT() struct FExampleTask : public FStateTreeTaskBase { ... bool Link(FStateTreeLinker& Linker) { Linker.LinkExternalData(ExampleSubsystemHandle); return true; } EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const EStateTreeStateChangeType ChangeType, const FStateTreeTransitionResult& Transition) { const UExampleSubsystem& ExampleSubsystem = Context.GetExternalData(ExampleSubsystemHandle); ... } TStateTreeExternalDataHandle<UExampleSubsystem> ExampleSubsystemHandle; }
- L167 _public typedef_ `typedef T DataType;`
- L168 _public member_ `static constexpr EStateTreeExternalDataRequirement DataRequirement = Req;`

#### struct `FStateTreeExternalDataDesc`  
`struct FStateTreeExternalDataDesc`  
_L177-241_
- reflection: `USTRUCT()`
- desc: Describes an external data. The data can point to a struct or object. The code that handles StateTree ticking is responsible for passing in the actually data, see FStateTreeExecutionContext.
- L181 _public prototype_ `FStateTreeExternalDataDesc() = default;`
- L182 _public function_ `FStateTreeExternalDataDesc(const UStruct* InStruct, const EStateTreeExternalDataRequirement InRequirement) : Struct(InStruct), Requirement(InRequirement)`
- L184 _public function_ `FStateTreeExternalDataDesc(const FName InName, const UStruct* InStruct, const FGuid InGuid) : Struct(InStruct) , Name(InName) #if WITH_EDITORONLY_DATA , ID(InGuid) #endif`
- L193 _public function_ `bool IsCompatibleWith(const FStateTreeDataView& DataView) const` — @return true if the DataView is compatible with the descriptor.
- L211 _public function_ `bool operator==(const FStateTreeExternalDataDesc& Other) const`
- L218 _public member_ `TObjectPtr<const UStruct> Struct = nullptr;` — `UPROPERTY()` — Class or struct of the external data.
- L226 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, Category = Common)` — Name of the external data. Used only for bindable external data (enforced by the schema). External data linked explicitly by the nodes (i.e. LinkExternalData) are identified only by their type since they are used for unique instance of a given type.
- L230 _public member_ `FStateTreeExternalDataHandle Handle;` — `UPROPERTY()` — Handle/Index to the StateTreeExecutionContext data views array
- L234 _public member_ `EStateTreeExternalDataRequirement Requirement = EStateTreeExternalDataRequirement::Required;` — `UPROPERTY()` — Describes if the data is required or not.
- L239 _public member_ `FGuid ID;` — `UPROPERTY()` — Unique identifier. Used only for bindable external data.

#### struct `FStateTreeTransitionRequest`  
`struct FStateTreeTransitionRequest`  
_L246-308_
- reflection: `USTRUCT(BlueprintType)`
- desc: Transition request
- L251 _public prototype_ `FStateTreeTransitionRequest() = default;`
- L253 _public function_ `explicit FStateTreeTransitionRequest(const FStateTreeStateLink& InStateLink) : TargetState(InStateLink.StateHandle) , Fallback(InStateLink.Fallback)`
- L259 _public function_ `explicit FStateTreeTransitionRequest( const FStateTreeStateHandle InTargetState, const EStateTreeTransitionPriority InPriority = EStateTreeTransitionPriority::Normal, const EStateTreeSelectionFallback InFallback = EStateTreeSelectionFallback::None) : TargetState(InTargetState) , Priority(InPriority) , Fallback(InFallback)`
- L269 _public prototype_ `FStateTreeTransitionRequest(const FStateTreeTransitionRequest&) = default;`
- L270 _public prototype_ `FStateTreeTransitionRequest(FStateTreeTransitionRequest&&) = default;`
- L271 _public prototype_ `FStateTreeTransitionRequest& operator=(const FStateTreeTransitionRequest&) = default;`
- L272 _public prototype_ `FStateTreeTransitionRequest& operator=(FStateTreeTransitionRequest&&) = default;`
- L277 _public member_ `FStateTreeStateHandle TargetState;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")` — Target state of the transition.
- L281 _public member_ `EStateTreeTransitionPriority Priority = EStateTreeTransitionPriority::Normal;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")` — Priority of the transition.
- L285 _public member_ `EStateTreeSelectionFallback Fallback = EStateTreeSelectionFallback::None;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")` — Fallback of the transition if it fails to select the target state
- L288 _public member_ `UE::StateTree::FActiveFrameID SourceFrameID;` — StateTree frame that was active when the transition was requested. Filled in by the StateTree execution context.
- L290 _public member_ `UE::StateTree::FActiveStateID SourceStateID;` — StateTree state that was active when the transition was requested. Filled in by the StateTree execution context.
- L296 _public member_ `TObjectPtr<const UStateTree> SourceStateTree = nullptr;` — `UPROPERTY()` — StateTree asset that was active when the transition was requested. Filled in by the StateTree execution context.
- L301 _public member_ `FStateTreeStateHandle SourceRootState = FStateTreeStateHandle::Invalid;` — `UPROPERTY()` — Root state the execution frame where the transition was requested. Filled in by the StateTree execution context.
- L306 _public member_ `FStateTreeStateHandle SourceState;` — `UPROPERTY()` — Source state of the transition. Filled in by the StateTree execution context.

#### struct `FStateTreeActiveStates`  
`struct FStateTreeActiveStates`  
_L315-583_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes an array of active states in a State Tree.
- L320 _public member_ `static constexpr uint8 MaxStates = 8;` — Max number of active states.
- L322 _public prototype_ `FStateTreeActiveStates() = default;`
- L325 _public function_ `explicit FStateTreeActiveStates(const FStateTreeStateHandle StateHandle)` — `UE_DEPRECATED(5.6, "Use the constructor with FActiveStateId.")`
- L329 _public function_ `explicit FStateTreeActiveStates(const FStateTreeStateHandle StateHandle, UE::StateTree::FActiveStateID StateID)`
- L335 _public function_ `void Reset()` — Resets the active state array to empty.
- L342 _public function_ `bool Push(const FStateTreeStateHandle StateHandle)` — Pushes new state at the back of the array and returns true if there was enough space.
- L348 _public function_ `bool Push(const FStateTreeStateHandle StateHandle, UE::StateTree::FActiveStateID StateID)` — Pushes new state at the back of the array and returns true if there was enough space.
- L364 _public function_ `bool PushFront(const FStateTreeStateHandle StateHandle)` — Pushes new state at the front of the array and returns true if there was enough space.
- L370 _public function_ `bool PushFront(const FStateTreeStateHandle StateHandle, UE::StateTree::FActiveStateID StateID)` — Pushes new state at the front of the array and returns true if there was enough space.
- L390 _public function_ `FStateTreeStateHandle Pop()` — Pops a state from the back of the array and returns the popped value, or invalid handle if the array was empty.
- L403 _public function_ `void SetNum(const int32 NewNum)` — Sets the number of states, new states are set to invalid state.
- L418 _public function_ `FStateTreeStateHandle FindStateHandle(UE::StateTree::FActiveStateID StateId) const` — Returns the corresponding state handle for the active state ID.
- L432 _public function_ `UE::StateTree::FActiveStateID FindStateID(FStateTreeStateHandle StateHandle) const` — Returns the corresponding state ID for the active state handle.
- L446 _public function_ `int32 IndexOfReverse(const FStateTreeStateHandle StateHandle) const` — Returns index of a state, searching in reverse order.
- L459 _public function_ `int32 IndexOfReverse(const UE::StateTree::FActiveStateID StateId) const` — Returns index of a state, searching in reverse order.
- L472 _public function_ `bool Contains(const FStateTreeStateHandle StateHandle) const` — Returns true of the array contains specified state.
- L485 _public function_ `bool Contains(const FStateTreeStateHandle StateHandle, const uint8 MaxNumStatesToCheck) const` — Returns true of the array contains specified state within MaxNumStatesToCheck states.
- L499 _public function_ `bool Contains(const UE::StateTree::FActiveStateID StateId) const` — Returns true if the state id is inside the container.
- L512 _public function_ `FStateTreeStateHandle Last() const` — Returns last state in the array, or invalid state if the array is empty.
- L518 _public function_ `int32 Num() const` — Returns number of states in the array.
- L524 _public function_ `bool IsValidIndex(const int32 Index) const` — Returns true if the index is within array bounds.
- L530 _public function_ `bool IsEmpty() const` — Returns true if the array is empty.
- L536 _public function_ `inline const FStateTreeStateHandle& operator[](const int32 Index) const` — Returns a specified state in the array.
- L543 _public function_ `inline FStateTreeStateHandle& operator[](const int32 Index)` — Returns mutable reference to a specified state in the array.
- L550 _public function_ `operator TArrayView<FStateTreeStateHandle>()` — Returns the active states from the States array.
- L556 _public function_ `operator TConstArrayView<FStateTreeStateHandle>() const` — Returns the active states from the States array.
- L562 _public function_ `FStateTreeStateHandle GetStateSafe(const int32 Index) const` — Returns a specified state in the array, or FStateTreeStateHandle::Invalid if Index is out of array bounds.
- L571 _public function_ `inline FStateTreeStateHandle* begin()` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L572 _public function_ `inline FStateTreeStateHandle* end ()`
- L573 _public function_ `inline const FStateTreeStateHandle* begin() const`
- L574 _public function_ `inline const FStateTreeStateHandle* end () const`
- L576 _public member_ `UE::StateTree::FActiveStateID StateIDs[MaxStates];`
- L579 _public member_ `FStateTreeStateHandle States[MaxStates];` — `UPROPERTY(VisibleDefaultsOnly, Category = Default)`
- L582 _public member_ `uint8 NumStates = 0;` — `UPROPERTY(VisibleDefaultsOnly, Category = Default)`

#### enum `EStateTreeTransitionSourceType`  
`enum class EStateTreeTransitionSourceType : uint8`  
_L587-593_
- reflection: `UENUM()`
- L589 _public enumerator_ `Unset`
- L590 _public enumerator_ `Asset`
- L591 _public enumerator_ `ExternalRequest`
- L592 _public enumerator_ `Internal`

#### struct `FStateTreeTransitionSource`  
`struct FStateTreeTransitionSource`  
_L599-654_
- reflection: `USTRUCT()`
- desc: Describes the origin of an applied transition.
- L603 _public prototype_ `FStateTreeTransitionSource() = default;`
- L606 _public function_ `explicit FStateTreeTransitionSource(const EStateTreeTransitionSourceType SourceType, const FStateTreeIndex16 TransitionIndex, const FStateTreeStateHandle TargetState, const EStateTreeTransitionPriority Priority) : FStateTreeTransitionSource(nullptr, SourceType, TransitionIndex, TargetState, Priority)` — `UE_DEPRECATED(5.6, "Use the version that requires a pointer to the StateTree asset.")`
- L612 _public function_ `explicit FStateTreeTransitionSource(const FStateTreeIndex16 TransitionIndex, const FStateTreeStateHandle TargetState, const EStateTreeTransitionPriority Priority) : FStateTreeTransitionSource(nullptr, EStateTreeTransitionSourceType::Asset, TransitionIndex, TargetState, Priority)` — `UE_DEPRECATED(5.6, "Use the version that requires a pointer to the StateTree asset.")`
- L618 _public function_ `explicit FStateTreeTransitionSource(const EStateTreeTransitionSourceType SourceType, const FStateTreeStateHandle TargetState, const EStateTreeTransitionPriority Priority) : FStateTreeTransitionSource(nullptr, SourceType, FStateTreeIndex16::Invalid, TargetState, Priority)` — `UE_DEPRECATED(5.6, "Use the version that requires a pointer to the StateTree asset.")`
- L623 _public prototype_ `explicit FStateTreeTransitionSource(const UStateTree* StateTree, const EStateTreeTransitionSourceType SourceType, const FStateTreeIndex16 TransitionIndex, const FStateTreeStateHandle TargetState, const EStateTreeTransitionPriority Priority);`
- L625 _public function_ `explicit FStateTreeTransitionSource(const UStateTree* StateTree, const FStateTreeIndex16 TransitionIndex, const FStateTreeStateHandle TargetState, const EStateTreeTransitionPriority Priority) : FStateTreeTransitionSource(StateTree, EStateTreeTransitionSourceType::Asset, TransitionIndex, TargetState, Priority)`
- L630 _public function_ `explicit FStateTreeTransitionSource(const UStateTree* StateTree, const EStateTreeTransitionSourceType SourceType, const FStateTreeStateHandle TargetState, const EStateTreeTransitionPriority Priority) : FStateTreeTransitionSource(StateTree, SourceType, FStateTreeIndex16::Invalid, TargetState, Priority)`
- L635 _public function_ `void Reset()`
- L641 _public member_ `TWeakObjectPtr<const UStateTree> Asset;` — The StateTree asset owning the transition and state.
- L644 _public member_ `EStateTreeTransitionSourceType SourceType = EStateTreeTransitionSourceType::Unset;` — Describes where the transition originated.
- L647 _public member_ `FStateTreeIndex16 TransitionIndex;` — Index of the transition if from predefined asset transitions, invalid otherwise
- L650 _public member_ `FStateTreeStateHandle TargetState = FStateTreeStateHandle::Invalid;` — Transition target state
- L653 _public member_ `EStateTreeTransitionPriority Priority = EStateTreeTransitionPriority::None;` — Priority of the transition that caused the state change.

#### struct `FStateTreeInstanceDebugId`  
`struct FStateTreeInstanceDebugId`  
_L658-705_
- L660 _public prototype_ `FStateTreeInstanceDebugId() = default;`
- L661 _public function_ `FStateTreeInstanceDebugId(const uint32 InstanceId, const uint32 SerialNumber) : Id(InstanceId) , SerialNumber(SerialNumber)`
- L666 _public function_ `explicit FStateTreeInstanceDebugId(const uint64 Id) : Id(static_cast<uint32>(Id >> 32)) , SerialNumber(static_cast<uint32>(Id))`
- L672 _public function_ `bool IsValid() const`
- L673 _public function_ `bool IsInvalid() const`
- L674 _public function_ `void Reset()`
- L676 _public function_ `bool operator==(const FStateTreeInstanceDebugId& Other) const`
- L681 _public function_ `bool operator!=(const FStateTreeInstanceDebugId& Other) const`
- L686 _public function_ `uint64 ToUint64() const`
- L701 _public member_ `static const FStateTreeInstanceDebugId Invalid;`
- L703 _public member_ `uint32 Id = INDEX_NONE;`
- L704 _public member_ `uint32 SerialNumber = INDEX_NONE;`

#### struct `FStateTreeTransitionDelayedState`  
`struct FStateTreeTransitionDelayedState`  
_L710-744_
- reflection: `USTRUCT()`
- desc: Describes current state of a delayed transition.
- L715 _public prototype_ `FStateTreeTransitionDelayedState() = default;`
- L716 _public prototype_ `FStateTreeTransitionDelayedState(const FStateTreeTransitionDelayedState&) = default;`
- L717 _public prototype_ `FStateTreeTransitionDelayedState(FStateTreeTransitionDelayedState&&) = default;`
- L718 _public prototype_ `FStateTreeTransitionDelayedState& operator=(const FStateTreeTransitionDelayedState&) = default;`
- L719 _public prototype_ `FStateTreeTransitionDelayedState& operator=(FStateTreeTransitionDelayedState&&) = default;`
- L723 _public member_ `UE::StateTree::FActiveStateID StateID;` — The state ID that triggers the transition.
- L727 _public member_ `TObjectPtr<const UStateTree> StateTree = nullptr;` — `UE_DEPRECATED(5.6, "StateTree is unused. Use StateID instead.")` — `UPROPERTY()`
- L730 _public member_ `FStateTreeSharedEvent CapturedEvent;` — `UPROPERTY()`
- L733 _public member_ `float TimeLeft = 0.0f;` — `UPROPERTY()`
- L736 _public member_ `uint32 CapturedEventHash = 0u;` — `UPROPERTY()`
- L740 _public member_ `FStateTreeStateHandle StateHandle;` — `UE_DEPRECATED(5.6, "StateHandle is unused. Use StateID instead.")` — `UPROPERTY()`
- L743 _public member_ `FStateTreeIndex16 TransitionIndex = FStateTreeIndex16::Invalid;` — `UPROPERTY()`

#### struct `UE::StateTree::FFinishedTask`  
`FFinishedTask`  
_L752-781_
- reflection: `UE_DEPRECATED(5.6, "Replaced with FStateTreeTasksCompletionStatus")`
- L763 _public prototype_ `FFinishedTask() = default;`
- L764 _public prototype_ `FFinishedTask(FActiveFrameID FrameID, FActiveStateID StateID, FStateTreeIndex16 TaskIndex, EStateTreeRunStatus RunStatus, EReasonType Reason, bool bTickProcessed);`
- L766 _public member_ `FActiveFrameID FrameID;` — Frame ID that identifies 1the active frame.
- L768 _public member_ `FActiveStateID StateID;` — State ID that contains the finished task.
- L770 _public member_ `FStateTreeIndex16 TaskIndex = FStateTreeIndex16::Invalid;` — Task that is finished and needs to be processed.
- L772 _public member_ `EStateTreeRunStatus RunStatus = EStateTreeRunStatus::Failed;` — The result of the finished task.
- L774 _public member_ `EReasonType Reason = EReasonType::GlobalTask;` — The reason of the finished task.
- L780 _public member_ `bool bTickProcessed = false;` — Set to true if the task is completed before or during the TickTasks. Used to identify tasks that were completed and had the chance to be processed by the algo. If not processed, they won't trigger the transition in this frame.

#### enum `UE::StateTree::FFinishedTask::EReasonType`  
`enum class EReasonType : uint8`  
_L754-762_
- L757 _public enumerator_ `GlobalTask` — A global task finished. The FrameID and TaskIndex are valid.
- L759 _public enumerator_ `StateTask` — A task inside a state finished. The FrameID, StateID and TaskIndex are valid.
- L761 _public enumerator_ `InternalTransition` — An internal transition finish the state. The FrameID and StateID are valid.

#### enum `UE::StateTree::ETickReason`  
`enum class ETickReason : uint8`  
_L785-808_
- reflection: `UENUM()`
- desc: Describes the reason behind StateTree ticking.
- L787 _public enumerator_ `None`
- L789 _public enumerator_ `ScheduledTickRequest` — A scheduled tick request is active.
- L791 _public enumerator_ `Forced` — The tick is forced. The schema doesn't support scheduling.
- L793 _public enumerator_ `StateCustomTickRate` — An active state requested a custom tick rate.
- L795 _public enumerator_ `TaskTicking` — A task in an active state request ticking.
- L797 _public enumerator_ `TransitionTicking` — A transition in an active state request ticking.
- L799 _public enumerator_ `TransitionRequest` — A transition request occurs via RequestTransition.
- L801 _public enumerator_ `Event` — An event need to be cleared.
- L803 _public enumerator_ `CompletedState` — A state completed async and transition didn't tick yet.
- L805 _public enumerator_ `DelayedTransition` — A active delayed transitions is pending.
- L807 _public enumerator_ `Delegate` — A broadcast delegate occurs via BroadcastDelegate, and a transition is listening to the delegate.

#### struct `FStateTreeScheduledTick`  
`struct FStateTreeScheduledTick`  
_L815-861_
- reflection: `USTRUCT()`
- desc: Information on how a state tree should tick next.
- L820 _public prototype_ `FStateTreeScheduledTick() = default;`
- L822 _public prototype_ `bool operator==(const FStateTreeScheduledTick&) const = default;`
- L823 _public prototype_ `bool operator!=(const FStateTreeScheduledTick&) const = default;`
- L826 _public prototype_ `static FStateTreeScheduledTick MakeSleep();` — Make a scheduled tick that returns Sleep.
- L828 _public prototype_ `static FStateTreeScheduledTick MakeEveryFrames(UE::StateTree::ETickReason Reason = UE::StateTree::ETickReason::None);` — Make a scheduled tick that returns EveryFrame.
- L830 _public prototype_ `static FStateTreeScheduledTick MakeNextFrame(UE::StateTree::ETickReason Reason = UE::StateTree::ETickReason::None);` — Make a scheduled tick that returns NextFrame.
- L832 _public prototype_ `static FStateTreeScheduledTick MakeCustomTickRate(float DeltaTime, UE::StateTree::ETickReason Reason = UE::StateTree::ETickReason::None);` — Make a scheduled tick that returns a tick rate. The value needs to be greater than zero.
- L836 _public prototype_ `bool ShouldSleep() const;` — @return true if it doesn't need to tick until an event/delegate/transition/... occurs.
- L838 _public prototype_ `bool ShouldTickEveryFrames() const;` — @return true if it the needs to tick every frame.
- L840 _public prototype_ `bool ShouldTickOnceNextFrame() const;` — @return true if it usually doesn't need to tick but it needs to tick once next frame.
- L842 _public prototype_ `bool HasCustomTickRate() const;` — @return true if it has a custom tick rate.
- L844 _public prototype_ `float GetTickRate() const;` — @return the delay in seconds between ticks.
- L847 _public function_ `UE::StateTree::ETickReason GetReason() const` — @return the reason why tick is required.
- L853 _private function_ `FStateTreeScheduledTick(float DeltaTime, UE::StateTree::ETickReason Reason) : NextDeltaTime(DeltaTime) , Reason(Reason)`
- L859 _private member_ `float NextDeltaTime = 0.0f;` — `UPROPERTY()`
- L860 _private member_ `UE::StateTree::ETickReason Reason = UE::StateTree::ETickReason::None;`

#### struct `UE::StateTree::FScheduledTickHandle`  
`struct FScheduledTickHandle`  
_L869-891_
- desc: ID of a scheduled tick request.
- L872 _public prototype_ `FScheduledTickHandle() = default;`
- L873 _public prototype_ `FScheduledTickHandle(const FScheduledTickHandle&) = default;`
- L875 _public prototype_ `static FScheduledTickHandle GenerateNewHandle();`
- L877 _public function_ `bool IsValid() const`
- L882 _public prototype_ `bool operator==(const FScheduledTickHandle& Other) const = default;`
- L883 _public prototype_ `bool operator!=(const FScheduledTickHandle& Other) const = default;`
- L886 _private function_ `explicit FScheduledTickHandle(uint32 InValue) : Value(InValue)`
- L890 _private member_ `uint32 Value = 0;`

#### struct `FStateTreeDelegateActiveListeners`  
`struct FStateTreeDelegateActiveListeners`  
_L896-939_
- desc: Describes added delegate listeners.
- L898 _public prototype_ `FStateTreeDelegateActiveListeners() = default;`
- L899 _public prototype_ `~FStateTreeDelegateActiveListeners();`
- L902 _public prototype_ `void Add(const FStateTreeDelegateListener& Listener, FSimpleDelegate Delegate, UE::StateTree::FActiveFrameID FrameID, UE::StateTree::FActiveStateID StateID, FStateTreeIndex16 OwningNodeIndex);` — Adds a delegate bound in the editor to the list. Safe to be called during broadcasting.
- L905 _public prototype_ `void Remove(const FStateTreeDelegateListener& Listener);` — Removes a delegate bound in the editor from the list. Safe to be called during broadcasting.
- L908 _public prototype_ `void RemoveAll(UE::StateTree::FActiveFrameID FrameID);` — Removes the listener by predicate.
- L911 _public prototype_ `void RemoveAll(UE::StateTree::FActiveStateID StateID);` — Removes the listener that match.
- L914 _public prototype_ `void BroadcastDelegate(const FStateTreeDelegateDispatcher& Dispatcher, const FStateTreeExecutionState& Exec);` — Broadcasts the listener by predicate.
- L917 _private prototype_ `void RemoveUnbounds();`
- L936 _private member_ `TArray<FActiveListener> Listeners;`
- L937 _private member_ `uint32 BroadcastingLockCount : 31 = 0;`
- L938 _private member_ `uint32 bContainsUnboundListeners : 1 = false;`

#### struct `FStateTreeDelegateActiveListeners::FActiveListener`  
`struct FActiveListener`  
_L919-934_
- L921 _public prototype_ `FActiveListener() = default;`
- L922 _public prototype_ `FActiveListener(const FStateTreeDelegateListener& Listener, FSimpleDelegate InDelegate, UE::StateTree::FActiveFrameID FrameID, UE::StateTree::FActiveStateID StateID, FStateTreeIndex16 OwningNodeIndex);`
- L924 _public function_ `bool IsValid() const`
- L929 _public member_ `FStateTreeDelegateListener Listener;`
- L930 _public member_ `FSimpleDelegate Delegate;`
- L931 _public member_ `UE::StateTree::FActiveFrameID FrameID;`
- L932 _public member_ `UE::StateTree::FActiveStateID StateID;`
- L933 _public member_ `FStateTreeIndex16 OwningNodeIndex = FStateTreeIndex16::Invalid;`

#### struct `UE::StateTree::FExecutionFrameHandle`  
`struct FExecutionFrameHandle`  
_L945-977_
- reflection: `USTRUCT()`
- desc: Helper that identifies an execution frame with the root state and its tree asset.
- L949 _public prototype_ `FExecutionFrameHandle() = default;`
- L950 _public function_ `FExecutionFrameHandle(TNotNull<const UStateTree*> InStateTree, FStateTreeStateHandle InRootState) : StateTree(InStateTree) , RootState(InRootState)`
- L956 _public function_ `bool IsValid() const`
- L961 _public function_ `const UStateTree* GetStateTree() const`
- L966 _public function_ `FStateTreeStateHandle GetRootState() const`
- L973 _private member_ `TObjectPtr<const UStateTree> StateTree;` — `UPROPERTY()`
- L976 _private member_ `FStateTreeStateHandle RootState;` — `UPROPERTY()`

#### struct `FStateTreeExecutionFrame`  
`struct FStateTreeExecutionFrame`  
_L982-1119_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes an active branch of a State Tree.
- L987 _public prototype_ `FStateTreeExecutionFrame() = default;`
- L988 _public prototype_ `FStateTreeExecutionFrame(const FStateTreeExecutionFrame&) = default;`
- L989 _public prototype_ `FStateTreeExecutionFrame(FStateTreeExecutionFrame&&) = default;`
- L990 _public prototype_ `FStateTreeExecutionFrame& operator=(const FStateTreeExecutionFrame&) = default;`
- L991 _public prototype_ `FStateTreeExecutionFrame& operator=(FStateTreeExecutionFrame&&) = default;`
- L993 _public prototype_ `FStateTreeExecutionFrame(const FRecordedStateTreeExecutionFrame& RecordedExecutionFrame);` — `UE_DEPRECATED(5.6, "The recorded frame doesn't have all the needed information to properly form an FStateTreeExecutionFrame.")`
- L997 _public function_ `bool IsSameFrame(const FStateTreeExecutionFrame& OtherFrame) const` — `UE_DEPRECATED(5.7, "Use the other version of IsSameRoot.")`
- L1003 _public function_ `bool HasSameRoot(const FStateTreeExecutionFrame& OtherFrame) const` — @return wherever the frame uses the state tree and root state.
- L1009 _public function_ `bool HasRoot(const UE::StateTree::FExecutionFrameHandle& FrameHandle) const` — @return wherever the frame uses the state tree and root state.
- L1015 _public function_ `bool HasRoot(TNotNull<const UStateTree*> InStateTree, FStateTreeStateHandle InRootState) const` — @return wherever the frame uses the state tree and root state.
- L1022 _public member_ `TObjectPtr<const UStateTree> StateTree = nullptr;` — `UPROPERTY()` — The State Tree used by the frame.
- L1026 _public member_ `FStateTreeTasksCompletionStatus ActiveTasksStatus;` — `UPROPERTY(Transient)` — Flag to track the completion of a global task or a task from a state in the ActiveStates.
- L1030 _public member_ `FStateTreeActiveStates ActiveStates;` — `UPROPERTY()` — Active states in this frame
- L1038 _public member_ `FStateTreeDataHandle StateParameterDataHandle = FStateTreeDataHandle::Invalid;` — `UPROPERTY()` — Handle to the root state parameter data. Exists in parent frame if this frame is entered by a linked state, Otherwise it exists in the current frame.
- L1046 _public member_ `FStateTreeDataHandle GlobalParameterDataHandle = FStateTreeDataHandle::Invalid;` — `UPROPERTY()` — Handle to the global parameter data, Exists in parent frame if it is a state parameter. Exists in root frame if it is the root global parameter.
- L1049 _public member_ `UE::StateTree::FActiveFrameID FrameID;` — Unique frame ID for this frame. Can be used to identify the frame.
- L1052 _public member_ `UE::StateTree::FActiveFrameID GlobalInstanceDataFrameID;` — current or parent frame ID that holds global instance data this frame can have access to.
- L1055 _public member_ `UE::StateTree::FActiveFrameID GlobalParameterDataFrameID;` — current or parent frame ID that holds global parameter data this frame can have access to.
- L1058 _public member_ `UE::StateTree::FActiveFrameID StateParameterDataFrameID;` — current or parent frame ID that holds root state parameter this frame can have access to.
- L1062 _public member_ `FStateTreeStateHandle RootState = FStateTreeStateHandle::Root;` — `UPROPERTY()` — The root state of the frame (e.g. Root state or a subtree).
- L1069 _public member_ `FStateTreeIndex16 ActiveNodeIndex = FStateTreeIndex16::Invalid;` — The evaluator or task node index that was "entered". Used during the Enter and Exit phase. A node can fail EnterState. Nodes after ActiveNodeIndex do not receive ExitState, because they didn't receive EnterState.
- L1073 _public member_ `FStateTreeIndex16 ExternalDataBaseIndex = FStateTreeIndex16::Invalid;` — `UPROPERTY()` — First index of the external data for this frame.
- L1077 _public member_ `FStateTreeIndex16 GlobalInstanceIndexBase = FStateTreeIndex16::Invalid;` — `UPROPERTY()` — Index within the instance data to the first global instance data (e.g. global tasks)
- L1085 _public member_ `FStateTreeIndex16 GlobalParameterIndexBase = FStateTreeIndex16::Invalid;` — `UPROPERTY()` — Index within the instance data that GlobalParameterDataHandle is relative to, if it is state parameter it lives within the parent frame Invalid means GlobalParameterDataHandle points to the root global parameter.
- L1093 _public member_ `FStateTreeIndex16 StateParameterIndexBase = FStateTreeIndex16::Invalid;` — `UPROPERTY()` — Index within the instance data that StateParameterDataHandle is relative to, It could be the current frame or parent frame's active instance index base, depending on if the current frame is a linked subtree. Always valid.
- L1097 _public member_ `FStateTreeIndex16 ActiveInstanceIndexBase = FStateTreeIndex16::Invalid;` — `UPROPERTY()` — Index within the instance data to the first active state's instance data (e.g. tasks)
- L1101 _public member_ `FStateTreeIndex16 ExecutionRuntimeIndexBase = FStateTreeIndex16::Invalid;` — `UPROPERTY()` — Index within the execution runtime data to the first execution runtime's instance data (e.g. tasks).
- L1105 _public member_ `uint8 bIsGlobalFrame : 1 = false;` — `UPROPERTY()` — If true, the global tasks of the State Tree should be handle in this frame.
- L1113 _public member_ `uint8 bHaveEntered : 1 = false;` — `UPROPERTY()` — If true, the global tasks/evaluator received the "EnterState". Can be sustained or added via a linked state. Only call StateEnter when the state didn't previously receive a state enter.
- L1117 _public member_ `uint8 NumCurrentlyActiveStates = 0;` — `UE_DEPRECATED(5.7, "States in ActiveStates are always valid.")`

#### struct `FStateTreeExecutionState`  
`struct FStateTreeExecutionState`  
_L1123-1289_
- reflection: `USTRUCT()`
- desc: Describes the execution state of the current State Tree instance.
- L1128 _public prototype_ `FStateTreeExecutionState() = default;`
- L1129 _public prototype_ `FStateTreeExecutionState(const FStateTreeExecutionState&) = default;`
- L1130 _public prototype_ `FStateTreeExecutionState(FStateTreeExecutionState&&) = default;`
- L1131 _public prototype_ `FStateTreeExecutionState& operator=(const FStateTreeExecutionState&) = default;`
- L1132 _public prototype_ `FStateTreeExecutionState& operator=(FStateTreeExecutionState&&) = default;`
- L1136 _public function_ `void Reset()`
- L1142 _public prototype_ `UE::StateTree::FActiveStatePath GetActiveStatePath() const;` — @return the unique path of all the active states of all the active execution frames.
- L1146 _public function_ `TArray<FStateTreeTransitionDelayedState, TInlineAllocator<8>> FindAndRemoveExpiredDelayedTransitions(const UStateTree* OwnerStateTree, const FStateTreeIndex16 TransitionIndex)` — Finds all delayed transition states for a specific transition and removes them. Returns their copies.
- L1164 _public prototype_ `const FStateTreeExecutionFrame* FindActiveFrame(UE::StateTree::FActiveFrameID FrameID) const;` — @return the active frame that matches the unique frame ID.
- L1167 _public prototype_ `FStateTreeExecutionFrame* FindActiveFrame(UE::StateTree::FActiveFrameID FrameID);` — @return the active frame that matches the unique frame ID.
- L1170 _public prototype_ `int32 IndexOfActiveFrame(UE::StateTree::FActiveFrameID FrameID) const;` — @return the active frame index that matches the unique frame ID.
- L1173 _public function_ `bool HasScheduledTickRequests() const` — @return whether it contains any scheduled tick requests.
- L1179 _public function_ `FStateTreeScheduledTick GetScheduledTickRequest() const` — @return the best/smallest scheduled tick request of all the requests.
- L1185 _public prototype_ `UE::StateTree::FScheduledTickHandle AddScheduledTickRequest(FStateTreeScheduledTick ScheduledTick);` — Adds a scheduled tick request.
- L1188 _public prototype_ `bool UpdateScheduledTickRequest(UE::StateTree::FScheduledTickHandle Handle, FStateTreeScheduledTick ScheduledTick);` — Updates the scheduled tick of a previous request.
- L1191 _public prototype_ `bool RemoveScheduledTickRequest(UE::StateTree::FScheduledTickHandle Handle);` — Removes a request.
- L1194 _private prototype_ `void CacheScheduledTickRequest();`
- L1199 _public member_ `TArray<FStateTreeExecutionFrame> ActiveFrames;` — `UPROPERTY()` — Currently active frames (and states)
- L1203 _public member_ `TArray<FStateTreeTransitionDelayedState> DelayedTransitions;` — `UPROPERTY()` — Pending delayed transitions.
- L1207 _public member_ `FRandomStream RandomStream;` — `UPROPERTY()` — Used by state tree random-based operations.
- L1210 _public member_ `FStateTreeDelegateActiveListeners DelegateActiveListeners;` — Active delegate listeners.
- L1219 _private member_ `TArray<FScheduledTickRequest> ScheduledTickRequests;`
- L1222 _private member_ `FStateTreeScheduledTick CachedScheduledTickRequest;` — The current computed value from ScheduledTickRequests. Only valid when ScheduledTickRequests is not empty.
- L1227 _public member_ `mutable FStateTreeInstanceDebugId InstanceDebugId;` — Id for the active instance used for debugging.
- L1232 _public member_ `TInstancedStruct<FStateTreeExecutionExtension> ExecutionExtension;` — `UPROPERTY(Transient)` — Optional extension for the execution context.
- L1236 _public member_ `EStateTreeRunStatus LastTickStatus = EStateTreeRunStatus::Failed;` — `UPROPERTY()` — Result of last TickTasks
- L1240 _public member_ `EStateTreeRunStatus TreeRunStatus = EStateTreeRunStatus::Unset;` — `UPROPERTY()` — Running status of the instance
- L1244 _public member_ `EStateTreeRunStatus RequestedStop = EStateTreeRunStatus::Unset;` — `UPROPERTY()` — Completion status stored if Stop was called during the Tick and needed to be deferred.
- L1248 _public member_ `EStateTreeUpdatePhase CurrentPhase = EStateTreeUpdatePhase::Unset;` — `UPROPERTY()` — Current update phase used to validate reentrant calls to the main entry points of the execution context (i.e. Start, Stop, Tick).
- L1252 _public member_ `uint16 StateChangeCount = 0;` — `UPROPERTY()` — Number of times a new state has been changed.
- L1256 _public member_ `bool bHasPendingCompletedState = false;` — `UPROPERTY()` — A task that completed a state or a global task that completed a global frame.
- L1262 _public member_ `TArray<UE::StateTree::FFinishedTask> FinishedTasks;` — Pending finished tasks that need processing.
- L1267 _public member_ `FStateTreeIndex16 CompletedFrameIndex = FStateTreeIndex16::Invalid;` — `UPROPERTY()` — Handle of the state that was first to report state completed (success or failure), used to trigger completion transitions.
- L1271 _public member_ `FStateTreeStateHandle CompletedStateHandle = FStateTreeStateHandle::Invalid;` — `UE_DEPRECATED(5.6, "Use FinishTask to completed a state.")` — `UPROPERTY()`
- L1274 _public member_ `FStateTreeExecutionContext* CurrentExecutionContext = nullptr;` — `UE_DEPRECATED(5.6, "CurrentExecutionContext is not needed anymore. Use FrameID and StateID.")`
- L1278 _public member_ `FStateTreeIndex16 EnterStateFailedFrameIndex = FStateTreeIndex16::Invalid;` — `UE_DEPRECATED(5.7, "Use FStateTreeExecutionFrame::ActiveNodeIndex instead.")` — `UPROPERTY()`
- L1282 _public member_ `FStateTreeIndex16 EnterStateFailedTaskIndex = FStateTreeIndex16::Invalid;` — `UE_DEPRECATED(5.7, "Use FStateTreeExecutionFrame::ActiveNodeIndex instead.")` — `UPROPERTY()`
- L1286 _public member_ `FStateTreeIndex16 LastExitedNodeIndex = FStateTreeIndex16::Invalid;` — `UE_DEPRECATED(5.7, "Use FStateTreeExecutionFrame::ActiveNodeIndex instead.")` — `UPROPERTY()`

#### struct `FStateTreeExecutionState::FScheduledTickRequest`  
`struct FScheduledTickRequest`  
_L1214-1218_
- desc: ScheduledTick
- L1216 _public member_ `UE::StateTree::FScheduledTickHandle Handle;`
- L1217 _public member_ `FStateTreeScheduledTick ScheduledTick;`

#### struct `FStateTreeFrameStateSelectionEvents`  
`FStateTreeFrameStateSelectionEvents`  
_L1294-1297_
- reflection: `UE_DEPRECATED(5.7, "Use the StateTreeExecutionContext.RequestTransitionResult.Selection.SelectionEvents instead.")`
- L1296 _public member_ `TStaticArray<FStateTreeSharedEvent, FStateTreeActiveStates::MaxStates> Events;`

#### struct `FStateTreeTransitionResult`  
`struct FStateTreeTransitionResult`  
_L1305-1379_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes a state tree transition. Source is the state where the transition started, Target describes the state where the transition pointed at, and Next describes the selected state. The reason Transition and Next are different is that Transition state can be a selector state, in which case the children will be visited until a leaf state is found, which will be the next state.
- L1310 _public prototype_ `FStateTreeTransitionResult() = default;`
- L1311 _public prototype_ `FStateTreeTransitionResult(const FStateTreeTransitionResult&) = default;`
- L1312 _public prototype_ `FStateTreeTransitionResult(FStateTreeTransitionResult&&) = default;`
- L1313 _public prototype_ `FStateTreeTransitionResult& operator=(const FStateTreeTransitionResult&) = default;`
- L1314 _public prototype_ `FStateTreeTransitionResult& operator=(FStateTreeTransitionResult&&) = default;`
- L1318 _public prototype_ `FStateTreeTransitionResult(const FRecordedStateTreeTransitionResult& RecordedTransition);` — `UE_DEPRECATED(5.6, "Use FStateTreeExecutionContext::MakeTransitionResult to crate a new transition.")`
- L1320 _public function_ `void Reset()`
- L1326 _public member_ `UE::StateTree::FActiveFrameID SourceFrameID;` — Frame that was active when the transition was requested.
- L1332 _public member_ `UE::StateTree::FActiveStateID SourceStateID;` — The state the transition was requested from. It can be invalid if the transition is requested outside the Tick.
- L1336 _public member_ `FStateTreeStateHandle TargetState = FStateTreeStateHandle::Invalid;` — `UPROPERTY(EditDefaultsOnly, Category = "Default", BlueprintReadOnly)` — Transition target state. It can be a completion state.
- L1340 _public member_ `FStateTreeStateHandle CurrentState = FStateTreeStateHandle::Invalid;` — `UPROPERTY(EditDefaultsOnly, Category = "Default", BlueprintReadOnly)` — The current state being executed. On enter/exit callbacks this is the state of the task.
- L1344 _public member_ `EStateTreeRunStatus CurrentRunStatus = EStateTreeRunStatus::Unset;` — `UPROPERTY(EditDefaultsOnly, Category = "Default", BlueprintReadOnly)` — Current Run status.
- L1348 _public member_ `EStateTreeStateChangeType ChangeType = EStateTreeStateChangeType::Changed;` — `UPROPERTY(EditDefaultsOnly, Category = "Default", BlueprintReadOnly)` — If the change type is Sustained, then the CurrentState was reselected, or if Changed then the state was just activated.
- L1352 _public member_ `EStateTreeTransitionPriority Priority = EStateTreeTransitionPriority::None;` — `UPROPERTY(EditDefaultsOnly, Category = "Default", BlueprintReadOnly)` — Priority of the transition that caused the state change.
- L1358 _public member_ `TArray<FStateTreeExecutionFrame> NextActiveFrames;` — `UPROPERTY(Category = "Default", BlueprintReadOnly, meta = (DeprecatedProperty))` — States selected as result of the transition.
- L1362 _public member_ `TArray<FStateTreeFrameStateSelectionEvents> NextActiveFrameEvents;` — Events used in state selection.
- L1367 _public member_ `TObjectPtr<const UStateTree> SourceStateTree = nullptr;` — `UPROPERTY(Category = "Default", BlueprintReadOnly, meta = (DeprecatedProperty))` — StateTree asset that was active when the transition was requested.
- L1372 _public member_ `FStateTreeStateHandle SourceRootState = FStateTreeStateHandle::Invalid;` — `UPROPERTY(Category = "Default", BlueprintReadOnly, meta = (DeprecatedProperty))` — Root state the execution frame where the transition was requested.
- L1377 _public member_ `FStateTreeStateHandle SourceState = FStateTreeStateHandle::Invalid;` — `UPROPERTY(Category = "Default", BlueprintReadOnly, meta=(DeprecatedProperty))` — Transition source state.

#### enum `EStateTreeRecordTransitions`  
`enum class EStateTreeRecordTransitions : uint8`  
_L1386-1390_
- reflection: `UENUM()`
- desc: Enumeration for the different transition recording types. This is used by the execution context to capture transition snapshots if set to record.
- L1388 _public enumerator_ `No`
- L1389 _public enumerator_ `Yes`

#### struct `FRecordedStateTreeExecutionFrame`  
`FRecordedStateTreeExecutionFrame`  
_L1399-1425_
- reflection: `UE_DEPRECATED(5.7, "FRecordedStateTreeExecutionFrame is not used anymore.")`
- L1403 _public prototype_ `FRecordedStateTreeExecutionFrame() = default;`
- L1405 _public prototype_ `FRecordedStateTreeExecutionFrame(const FStateTreeExecutionFrame& ExecutionFrame);` — `UE_DEPRECATED(5.6, "Use FStateTreeExecutionContext::MakeRecordedTransitionResult to create a new recorded transition.")`
- L1409 _public member_ `TObjectPtr<const UStateTree> StateTree = nullptr;` — `UPROPERTY()` — The State Tree used for ticking this frame.
- L1413 _public member_ `FStateTreeStateHandle RootState = FStateTreeStateHandle::Root;` — `UPROPERTY()` — The root state of the frame (e.g. Root state or a subtree).
- L1417 _public member_ `FStateTreeActiveStates ActiveStates;` — `UPROPERTY()` — Active states in this frame.
- L1421 _public member_ `uint8 bIsGlobalFrame : 1 = false;` — `UPROPERTY()` — If true, the global tasks of the State Tree should be handle in this frame.
- L1424 _public member_ `TStaticArray<uint8, FStateTreeActiveStates::MaxStates> EventIndices;` — Captured indices of the events we've recorded.

#### struct `FRecordedActiveState`  
`struct FRecordedActiveState`  
_L1429-1446_
- reflection: `USTRUCT()`
- desc: Captured state cached for recording purposes.
- L1433 _public prototype_ `FRecordedActiveState() = default;`
- L1437 _public member_ `TObjectPtr<const UStateTree> StateTree;` — `UPROPERTY()` — The state tree that owns the state handle.
- L1441 _public member_ `FStateTreeStateHandle State;` — `UPROPERTY()` — The active state.
- L1445 _public member_ `int32 EventIndex = INDEX_NONE;` — `UPROPERTY()` — Captured events from the transition that we've recorded

#### struct `FRecordedStateTreeTransitionResult`  
`struct FRecordedStateTreeTransitionResult`  
_L1454-1514_
- reflection: `USTRUCT()`
- desc: Captured state tree transition result that can be cached for recording purposes. when transitions are recorded through this structure, we can replicate them down to clients to keep our state tree in sync.
- L1459 _public prototype_ `FRecordedStateTreeTransitionResult() = default;`
- L1460 _public prototype_ `FRecordedStateTreeTransitionResult(const FRecordedStateTreeTransitionResult&) = default;`
- L1461 _public prototype_ `FRecordedStateTreeTransitionResult(FRecordedStateTreeTransitionResult&&) = default;`
- L1462 _public prototype_ `FRecordedStateTreeTransitionResult& operator=(const FRecordedStateTreeTransitionResult&) = default;`
- L1463 _public prototype_ `FRecordedStateTreeTransitionResult& operator=(FRecordedStateTreeTransitionResult&&) = default;`
- L1467 _public prototype_ `FRecordedStateTreeTransitionResult(const FStateTreeTransitionResult& Transition);` — `UE_DEPRECATED(5.6, "Use FStateTreeExecutionContext::MakeRecordedTransitionResult to create a new recorded transition.")`
- L1471 _public member_ `TArray<FRecordedActiveState> States;` — `UPROPERTY()` — The selected states.
- L1475 _public member_ `TArray<FStateTreeEvent> Events;` — `UPROPERTY()` — The selected states.
- L1479 _public member_ `EStateTreeTransitionPriority Priority = EStateTreeTransitionPriority::None;` — `UPROPERTY()` — Priority of the transition that caused the state change.
- L1486 _public member_ `TArray<FRecordedStateTreeExecutionFrame> NextActiveFrames;` — `UPROPERTY()` — States selected as result of the transition.
- L1491 _public member_ `TArray<FStateTreeEvent> NextActiveFrameEvents;` — `UPROPERTY()` — Captured events from the transition that we've recorded
- L1496 _public member_ `FStateTreeStateHandle SourceState = FStateTreeStateHandle::Invalid;` — `UPROPERTY()` — Transition source state.
- L1501 _public member_ `FStateTreeStateHandle TargetState = FStateTreeStateHandle::Invalid;` — `UPROPERTY()` — Transition target state.
- L1506 _public member_ `TObjectPtr<const UStateTree> SourceStateTree = nullptr;` — `UPROPERTY()` — StateTree asset that was active when the transition was requested.
- L1511 _public member_ `FStateTreeStateHandle SourceRootState = FStateTreeStateHandle::Invalid;` — `UPROPERTY()` — Root state the execution frame where the transition was requested.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API STATETREEMODULE_API`
- L691 _function_ `friend uint32 GetTypeHash(const FStateTreeInstanceDebugId InstanceDebugId)`
- L696 _function_ `friend FString LexToString(const FStateTreeInstanceDebugId InstanceDebugId)`
- L747 _namespace_ `namespace UE`
- L747 _namespace_ `namespace StateTree` (scope `UE`)
- L864 _namespace_ `namespace UE`
- L864 _namespace_ `namespace StateTree` (scope `UE`)
- L941 _namespace_ `namespace UE`
- L941 _namespace_ `namespace StateTree` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeExtension.h` (Public)


#### class `UStateTreeExtension`  
`class UStateTreeExtension : public UObject`  
_L15-31_
- reflection: `UCLASS(Abstract, DefaultToInstanced, Within=StateTree, MinimalAPI)`
- inherits: `UObject`
- desc: Extension for the state tree asset.
- L21 _public function_ `virtual bool Link(FStateTreeLinker& Linker)` — Resolves references to other StateTree data.
- L27 _protected function_ `UStateTree* GetStateTree() const`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeFunctionLibrary.h` (Public)


#### class `UStateTreeFunctionLibrary`  
`class UStateTreeFunctionLibrary : public UBlueprintFunctionLibrary`  
_L16-36_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UBlueprintFunctionLibrary`
- desc: A collection of blueprint functions for state tree.
- L22 _public prototype_ `static void SetStateTree(UPARAM(ref)FStateTreeReference& Reference, UStateTree* StateTree);` — `UFUNCTION(BlueprintCallable, Category = "StateTree|Reference")`
- L25 _public prototype_ `static FStateTreeReference MakeStateTreeReference(UStateTree* StateTree);` — `UFUNCTION(BlueprintCallable, DisplayName = "Make State Tree Reference", Category = "StateTree|Reference", meta = (Keywords = "construct build", NativeMakeFunc, BlueprintInternalUseOnly = "true"))`
- L28 _public prototype_ `static void K2_SetParametersProperty(UPARAM(ref)FStateTreeReference& Reference, FGuid PropertyID, UPARAM(ref) const int32& NewValue);` — `UFUNCTION(BlueprintCallable, CustomThunk, DisplayName = "Set Parameter Property", Category = "StateTree|Reference", meta = (BlueprintInternalUseOnly = "true", CustomStructureParam = "NewValue"))`
- L31 _public prototype_ `static void K2_GetParametersProperty(UPARAM(ref)const FStateTreeReference& Reference, FGuid PropertyID, int32& ReturnValue);` — `UFUNCTION(BlueprintCallable, CustomThunk, DisplayName = "Get Parameter Property", Category = "StateTree|Reference", meta = (BlueprintInternalUseOnly = "true", CustomStructureParam = "ReturnValue"))`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeIndexTypes.h` (Public)


#### struct `FStateTreeIndex16`  
`struct FStateTreeIndex16`  
_L12-84_
- reflection: `USTRUCT(BlueprintType)`
- desc: uint16 index that can be invalid.
- L16 _public member_ `static constexpr uint16 InvalidValue = MAX_uint16;`
- L17 _public member_ `static const FStateTreeIndex16 Invalid;`
- L25 _public function_ `static bool IsValidIndex(const int32 Index)` — @return true if the given index can be represented by the type.
- L30 _public prototype_ `FStateTreeIndex16() = default;`
- L36 _public function_ `explicit FStateTreeIndex16(const uint16 InIndex) : Value(InIndex)` — Construct from a uint16 index where MAX_uint16 is considered an invalid index (i.e FStateTreeIndex16::InvalidValue).
- L44 _public function_ `explicit FStateTreeIndex16(const int32 InIndex)` — Construct from a int32 index where INDEX_NONE is considered an invalid index and converted to FStateTreeIndex16::InvalidValue (i.e MAX_uint16).
- L53 _public function_ `explicit FStateTreeIndex16(const FPropertyBindingIndex16 InIndex) : Value(InIndex.Get())` — Construct from FPropertyBindingIndex16 to facilitate transition to FPropertyBindingIndex16 in bindings
- L62 _public function_ `operator FPropertyBindingIndex16() const` — Conversion to from FPropertyBindingIndex16 to facilitate transition to FPropertyBindingIndex16 in bindings (Intentionally not explicit for the initial refactoring) @todo make this explicit and update StateTree code to use FPropertyBindingIndex16
- L68 _public function_ `uint16 Get() const` — @return value of the index or FStateTreeIndex16::InvalidValue (i.e. MAX_uint16) if invalid.
- L71 _public function_ `int32 AsInt32() const` — @return the index value as int32, mapping invalid value to INDEX_NONE.
- L74 _public function_ `bool IsValid() const` — @return true if the index is valid.
- L76 _public function_ `bool operator==(const FStateTreeIndex16& RHS) const`
- L77 _public function_ `bool operator!=(const FStateTreeIndex16& RHS) const`
- L79 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L83 _protected member_ `uint16 Value = InvalidValue;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FStateTreeIndex16> : public TStructOpsTypeTraitsBase2<FStateTreeIndex16>`  
_L87-93_
- inherits: `TStructOpsTypeTraitsBase2<FStateTreeIndex16>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L90-92_

#### struct `FStateTreeIndex8`  
`struct FStateTreeIndex8`  
_L97-135_
- reflection: `USTRUCT(BlueprintType)`
- desc: uint8 index that can be invalid.
- L101 _public member_ `static constexpr uint8 InvalidValue = MAX_uint8;`
- L102 _public member_ `static const FStateTreeIndex8 Invalid;`
- L105 _public function_ `static bool IsValidIndex(const int32 Index)` — @return true if the given index can be represented by the type.
- L110 _public prototype_ `FStateTreeIndex8() = default;`
- L112 _public function_ `explicit FStateTreeIndex8(const int32 InIndex)`
- L119 _public function_ `uint8 Get() const` — @return value of the index.
- L122 _public function_ `int32 AsInt32() const` — @return the index value as int32, mapping invalid value to INDEX_NONE.
- L125 _public function_ `bool IsValid() const` — @return true if the index is valid.
- L127 _public function_ `bool operator==(const FStateTreeIndex8& RHS) const`
- L128 _public function_ `bool operator!=(const FStateTreeIndex8& RHS) const`
- L130 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L134 _protected member_ `uint8 Value = InvalidValue;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FStateTreeIndex8> : public TStructOpsTypeTraitsBase2<FStateTreeIndex8>`  
_L138-144_
- inherits: `TStructOpsTypeTraitsBase2<FStateTreeIndex8>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L141-143_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`
- L19 _function_ `friend inline uint32 GetTypeHash(const FStateTreeIndex16 Index)`
- L91 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon52f29d220103`)
- L142 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon52f29d220203`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeInstanceContainer.h` (Public)


#### struct `FStateTreeInstanceObjectWrapper`  
`struct FStateTreeInstanceObjectWrapper`  
_L13-24_
- reflection: `USTRUCT()`
- desc: Wrapper class to store an object amongst the structs.
- L17 _public prototype_ `FStateTreeInstanceObjectWrapper() = default;`
- L18 _public function_ `FStateTreeInstanceObjectWrapper(UObject* Object) : InstanceObject(Object)`
- L23 _public member_ `TObjectPtr<UObject> InstanceObject = nullptr;` — `UPROPERTY()`

#### struct `UE::StateTree::InstanceData::FInstanceContainer`  
`struct FInstanceContainer`  
_L30-137_
- reflection: `USTRUCT()`
- desc: Container of instance data.
- L34 _public prototype_ `FInstanceContainer() = default;`
- L44 _public prototype_ `void Init(TNotNull<UObject*> InOwner, const FInstanceContainer& InStructs, FAddArgs Args);` — Initializes the array with specified items.
- L46 _public prototype_ `void Init(TNotNull<UObject*> InOwner, TConstArrayView<FInstancedStruct> InStructs, FAddArgs Args);` — Initializes the array with specified items.
- L48 _public prototype_ `void Init(TNotNull<UObject*> InOwner, TConstArrayView<FConstStructView> InStructs, FAddArgs Args);` — Initializes the array with specified items.
- L50 _public prototype_ `int32 Append(TNotNull<UObject*> InOwner, const FInstanceContainer& InStructs, FAddArgs Args);` — Append the specified items to the array.
- L52 _public prototype_ `int32 Append(TNotNull<UObject*> InOwner, TConstArrayView<FInstancedStruct> InStructs, FAddArgs Args);` — Append the specified items to the array.
- L54 _public prototype_ `int32 Append(TNotNull<UObject*> InOwner, TConstArrayView<FConstStructView> InStructs, FAddArgs Args);` — Append the specified items to the array.
- L57 _public function_ `[[nodiscard]] int32 Num() const` — @return number of items in the storage.
- L63 _public function_ `[[nodiscard]] bool IsValidIndex(const int32 Index) const` — @return true if the index can be used to get data.
- L69 _public function_ `[[nodiscard]] bool IsObject(const int32 Index) const` — @return true if item at the specified index is object type.
- L75 _public function_ `[[nodiscard]] FConstStructView GetStruct(const int32 Index) const` — @return specified item as struct.
- L81 _public function_ `[[nodiscard]] FStructView GetMutableStruct(const int32 Index)` — @return specified item as mutable struct.
- L87 _public function_ `[[nodiscard]] const UObject* GetObject(const int32 Index) const` — @return specified item as object, will check() if the item is not an object.
- L94 _public function_ `[[nodiscard]] UObject* GetMutableObject(const int32 Index) const` — @return specified item as mutable Object, will check() if the item is not an object.
- L101 _public prototype_ `[[nodiscard]] bool AreAllInstancesValid() const;` — @return true if all instances are valid.
- L104 _public function_ `void Reset()` — Resets the data to empty.
- L110 _public prototype_ `[[nodiscard]] int32 GetAllocatedMemory() const;` — Returns the estimated memory allocated by the container.
- L112 _public typedef_ `using FIterator = FInstancedStructContainer::FIterator;`
- L113 _public typedef_ `using FConstIterator = FInstancedStructContainer::FConstIterator;`
- L116 _public function_ `FIterator begin()`
- L120 _public function_ `FIterator end()`
- L125 _public function_ `FConstIterator begin() const`
- L129 _public function_ `FConstIterator end() const`
- L136 _private member_ `FInstancedStructContainer InstanceStructs;` — `UPROPERTY()`

#### struct `UE::StateTree::InstanceData::FInstanceContainer::FAddArgs`  
`struct FAddArgs`  
_L37-41_
- L40 _public member_ `bool bDuplicateWrappedObject = true;` — Duplicate the object contained by object wrapper.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATETREEMODULE_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace StateTree` (scope `UE`)
- L26 _namespace_ `namespace InstanceData` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeInstanceData.h` (Public)


#### struct `FStateTreeTemporaryInstanceData`  
`struct FStateTreeTemporaryInstanceData`  
_L89-122_
- reflection: `USTRUCT()`
- desc: Holds temporary instance data created during state selection. The data is identified by Frame and DataHandle.
- L93 _public prototype_ `FStateTreeTemporaryInstanceData() = default;`
- L96 _public prototype_ `FStateTreeTemporaryInstanceData(const FStateTreeTemporaryInstanceData& Other) = default;`
- L97 _public prototype_ `FStateTreeTemporaryInstanceData(FStateTreeTemporaryInstanceData&& Other) = default;`
- L98 _public prototype_ `FStateTreeTemporaryInstanceData& operator=(FStateTreeTemporaryInstanceData const& Other) = default;`
- L99 _public prototype_ `FStateTreeTemporaryInstanceData& operator=(FStateTreeTemporaryInstanceData&& Other) = default;`
- L102 _public member_ `UE::StateTree::FActiveFrameID FrameID;`
- L105 _public member_ `FStateTreeDataHandle DataHandle = FStateTreeDataHandle::Invalid;` — `UPROPERTY()`
- L108 _public member_ `FStateTreeIndex16 OwnerNodeIndex = FStateTreeIndex16::Invalid;` — `UPROPERTY()`
- L111 _public member_ `FInstancedStruct Instance;` — `UPROPERTY()`
- L116 _public member_ `TObjectPtr<const UStateTree> StateTree = nullptr;` — `UE_DEPRECATED(5.6, "Use the frame id to identify the frame.")` — `UPROPERTY()`
- L120 _public member_ `FStateTreeStateHandle RootState = FStateTreeStateHandle::Invalid;` — `UE_DEPRECATED(5.6, "Use the frame id to identify the frame.")` — `UPROPERTY()`

#### struct `FStateTreeInstanceStorageCustomVersion`  
`struct FStateTreeInstanceStorageCustomVersion`  
_L125-144_
- L140 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L143 _private prototype_ `FStateTreeInstanceStorageCustomVersion() = default;`

#### enum `FStateTreeInstanceStorageCustomVersion::Type`  
`enum Type`  
_L127-137_
- L130 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L132 _public enumerator_ `AddedCustomSerialization` — Added custom serialization
- L135 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L136 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### struct `FStateTreeInstanceStorage`  
`struct FStateTreeInstanceStorage`  
_L159-447_
- reflection: `USTRUCT()`
- desc: Storage for the actual instance data.
- L163 _public prototype_ `FStateTreeInstanceStorage();`
- L164 _public prototype_ `FStateTreeInstanceStorage(const FStateTreeInstanceStorage& Other);`
- L165 _public prototype_ `FStateTreeInstanceStorage(FStateTreeInstanceStorage&& Other) noexcept;`
- L167 _public prototype_ `FStateTreeInstanceStorage& operator=(const FStateTreeInstanceStorage& Other);`
- L168 _public prototype_ `FStateTreeInstanceStorage& operator=(FStateTreeInstanceStorage&& Other) noexcept;`
- L171 _public function_ `FStateTreeEventQueue& GetMutableEventQueue()` — @return reference to the event queue.
- L177 _public function_ `const FStateTreeEventQueue& GetEventQueue() const` — @return reference to the event queue.
- L183 _public function_ `bool IsOwningEventQueue() const` — @return true if the storage owns the event queue.
- L189 _public function_ `const TSharedRef<FStateTreeEventQueue>& GetSharedMutableEventQueue()` — @return shared pointer to the event queue.
- L195 _public prototype_ `void SetSharedEventQueue(const TSharedRef<FStateTreeEventQueue>& InSharedEventQueue);` — Sets event queue from another storage. Marks the event queue not owned.
- L202 _public prototype_ `void AddTransitionRequest(const UObject* Owner, const FStateTreeTransitionRequest& Request);` — Buffers a transition request to be sent to the State Tree. @param Owner Optional pointer to an owner UObject that is used for logging errors. @param Request transition to request.
- L205 _public prototype_ `void MarkDelegateAsBroadcasted(const FStateTreeDelegateDispatcher& Dispatcher);` — Marks delegate as broadcasted. Use for transitions.
- L208 _public prototype_ `bool IsDelegateBroadcasted(const FStateTreeDelegateDispatcher& Dispatcher) const;` — @return true if a delegate was broadcasted.
- L211 _public prototype_ `void ResetBroadcastedDelegates();` — Resets the list of broadcasted delegates.
- L214 _public prototype_ `TArray<FStateTreeDelegateDispatcher> StealBroadcastedDelegates();` — Resets the list of broadcasted delegates and returns it's copy.
- L217 _public prototype_ `bool HasBroadcastedDelegates() const;` — @return true if there's any broadcasted delegates.
- L220 _public function_ `TConstArrayView<FStateTreeTransitionRequest> GetTransitionRequests() const` — @return currently pending transition requests.
- L226 _public prototype_ `void ResetTransitionRequests();` — Reset all pending transition requests.
- L229 _public prototype_ `bool AreAllInstancesValid() const;` — @return true if all instances are valid.
- L232 _public function_ `int32 Num() const` — @return number of items in the storage.
- L238 _public function_ `bool IsValidIndex(const int32 Index) const` — @return true if the index can be used to get data.
- L244 _public function_ `bool IsObject(const int32 Index) const` — @return true if item at the specified index is object type.
- L250 _public function_ `FConstStructView GetStruct(const int32 Index) const` — @return specified item as struct.
- L256 _public function_ `FStructView GetMutableStruct(const int32 Index)` — @return specified item as mutable struct.
- L262 _public function_ `const UObject* GetObject(const int32 Index) const` — @return specified item as object, will check() if the item is not an object.
- L269 _public function_ `UObject* GetMutableObject(const int32 Index) const` — @return specified item as mutable Object, will check() if the item is not an object.
- L276 _public function_ `const FStateTreeExecutionState& GetExecutionState() const` — @return reference to StateTree execution state.
- L282 _public function_ `FStateTreeExecutionState& GetMutableExecutionState()` — @return reference to StateTree execution state.
- L288 _public function_ `[[nodiscard]] const UE::StateTree::InstanceData::FInstanceContainer& GetExecutionRuntimeData() const` — @return the storage's execution runtime data for the state tree.
- L294 _public function_ `[[nodiscard]] UE::StateTree::InstanceData::FInstanceContainer& GetExecutionRuntimeData()` — @return the storage's execution runtime data for the state tree.
- L303 _public prototype_ `[[nodiscard]] int32 AddExecutionRuntimeData(TNotNull<UObject*> Owner, UE::StateTree::FExecutionFrameHandle FrameHandle);` — Add or reuse the execution runtime data for the state tree. Return the base index for the execution runtime data.
- L309 _public prototype_ `FStructView AddTemporaryInstance(UObject& InOwner, const FStateTreeExecutionFrame& Frame, const FStateTreeIndex16 OwnerNodeIndex, const FStateTreeDataHandle DataHandle, FConstStructView NewInstanceData);` — Adds temporary instance data associated with specified frame and data handle. @returns mutable struct view to the instance.
- L312 _public prototype_ `void RemoveTemporaryInstance(const UE::StateTree::FActiveFrameID FrameID, const FStateTreeIndex16 OwnerNodeIndex, const FStateTreeDataHandle DataHandle);` — Removes a temporary instance data associated with specified frame and data handle.
- L315 _public function_ `FStructView GetMutableTemporaryStruct(const FStateTreeExecutionFrame& Frame, const FStateTreeDataHandle DataHandle)` — `UE_DEPRECATED(5.7, "Use the version with FrameID instead.")`
- L318 _public prototype_ `FStructView GetMutableTemporaryStruct(UE::StateTree::FActiveFrameID FrameID, const FStateTreeDataHandle DataHandle);` — @returns mutable view to the specified instance data, or invalid view if not found.
- L321 _public function_ `UObject* GetMutableTemporaryObject(const FStateTreeExecutionFrame& Frame, const FStateTreeDataHandle DataHandle)` — `UE_DEPRECATED(5.7, "Use the version with FrameID instead.")`
- L324 _public prototype_ `UObject* GetMutableTemporaryObject(UE::StateTree::FActiveFrameID FrameID, const FStateTreeDataHandle DataHandle);` — @returns mutable pointer to the specified instance data object, or invalid view if not found. Will check() if called on non-object data.
- L327 _public prototype_ `void ResetTemporaryInstances();` — Empties the temporary instances.
- L330 _public function_ `TArrayView<FStateTreeTemporaryInstanceData> GetMutableTemporaryInstances()` — @return mutable array view to the temporary instances
- L336 _public prototype_ `void SetGlobalParameters(FConstStructView Parameters);` — Stores copy of provided parameters as State Tree global parameters.
- L339 _public prototype_ `void SetGlobalParameters(const FInstancedPropertyBag& Parameters);` — `UE_DEPRECATED(5.8, "Use the version with a FConstStructView")`
- L342 _public function_ `FConstStructView GetGlobalParameters() const` — @return view to global parameters.
- L348 _public function_ `FStructView GetMutableGlobalParameters()` — @return mutable view to global parameters.
- L354 _public prototype_ `uint32 GenerateUniqueId();` — @return a unique number used to make active frame id and active state id.
- L357 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector);` — Note, called by FStateTreeInstanceData.
- L360 _public prototype_ `void Reset();` — Resets the storage to initial state.
- L363 _public prototype_ `void AcquireReadAccess();` — Start the invalid multithreading read-only access detection.
- L366 _public prototype_ `void ReleaseReadAccess();` — Stop the multitheading read-only access detection.
- L369 _public prototype_ `void AcquireWriteAccess();` — Start the invalid multithreading write access detection.
- L372 _public prototype_ `void ReleaseWriteAccess();` — Stop the multitheading write access detection.
- L375 _public prototype_ `UE::StateTree::Debug::FRuntimeValidation GetRuntimeValidation() const;` — Get the data used at runtime to confirm the inner working of the StateTree.
- L389 _private member_ `FInstancedStructContainer InstanceStructs;` — `UPROPERTY()` — Struct for global and active instances. The buffer format is: for each frames Global parameters, if it's a global frame. Global node instances, if it's a global frame. (evaluator, global tasks) Active state parameters Active node instances (tasks) @note Not transient, as we use FStateTreeInstanceData to store default values for instance data.
- L393 _private member_ `FStateTreeExecutionState ExecutionState;` — `UPROPERTY(Transient)` — Execution state of the state tree instance.
- L400 _private member_ `UE::StateTree::InstanceData::FInstanceContainer ExecutionRuntimeData;` — `UPROPERTY(Transient)` — Struct for the execution runtime data. They stay alive until the owning execution context stops.
- L408 _private member_ `TArray<FExecutionRuntimeInfo, TInlineAllocator<1>> ExecutionRuntimeDataInfos;`
- L412 _private member_ `TArray<FStateTreeTemporaryInstanceData> TemporaryInstances;` — `UPROPERTY(Transient)` — Temporary instances
- L415 _private member_ `TSharedRef<FStateTreeEventQueue> EventQueue = MakeShared<FStateTreeEventQueue>();` — Events (Transient)
- L418 _private member_ `TArray<FStateTreeDelegateDispatcher> BroadcastedDelegates;` — Array of broadcasted delegates.
- L422 _private member_ `TArray<FStateTreeTransitionRequest> TransitionRequests;` — `UPROPERTY(Transient)` — Requested transitions
- L426 _private member_ `FInstancedStruct GlobalParameters;` — `UPROPERTY(Transient)` — Global parameters
- L430 _private member_ `uint32 UniqueIdGenerator = 0;` — `UPROPERTY(Transient)` — Unique id.
- L437 _private prototype_ `UE_MT_DECLARE_MRSW_RECURSIVE_ACCESS_DETECTOR(AccessDetector);` — Used to detect if we are using the instance data on multiple threads in a safe way. The instance data supports multiple reader threads or a single writer thread. The detector supports recursive access.
- L440 _private member_ `bool bIsOwningEventQueue = true;` — True if the storage owns the event queue.
- L443 _private member_ `TPimplPtr<UE::StateTree::Debug::FRuntimeValidationInstanceData> RuntimeValidationData;`

#### struct `FStateTreeInstanceStorage::FExecutionRuntimeInfo`  
`struct FExecutionRuntimeInfo`  
_L403-407_
- desc: Info to find the index where the execution runtime data starts for a specific state tree.
- L405 _public member_ `FObjectKey StateTree;`
- L406 _public member_ `int32 StartIndex = 0;`

#### struct `FStateTreeInstanceData`  
`struct FStateTreeInstanceData`  
_L458-646_
- reflection: `USTRUCT()`
- desc: StateTree instance data is used to store the runtime state of a StateTree. The layout of the data is described in a FStateTreeInstanceDataLayout. Note: If FStateTreeInstanceData is placed on an struct, you must call AddStructReferencedObjects() manually, as it is not automatically called recursively. Note: Serialization is supported only for FArchive::IsModifyingWeakAndStrongReferences(), that is replacing object references.
- L462 _public prototype_ `FStateTreeInstanceData();`
- L463 _public prototype_ `FStateTreeInstanceData(const FStateTreeInstanceData& Other);`
- L464 _public prototype_ `FStateTreeInstanceData(FStateTreeInstanceData&& Other) noexcept;`
- L466 _public prototype_ `FStateTreeInstanceData& operator=(const FStateTreeInstanceData& Other);`
- L467 _public prototype_ `FStateTreeInstanceData& operator=(FStateTreeInstanceData&& Other) noexcept;`
- L469 _public prototype_ `~FStateTreeInstanceData();`
- L479 _public prototype_ `void Init(UObject& InOwner, TConstArrayView<FInstancedStruct> InStructs, FAddArgs Args = FAddArgs::Default);` — Initializes the array with specified items.
- L480 _public prototype_ `void Init(UObject& InOwner, TConstArrayView<FConstStructView> InStructs, FAddArgs Args = FAddArgs::Default);`
- L483 _public prototype_ `void Append(UObject& InOwner, TConstArrayView<FInstancedStruct> InStructs, FAddArgs Args = FAddArgs::Default);` — Appends new items to the instance.
- L484 _public prototype_ `void Append(UObject& InOwner, TConstArrayView<FConstStructView> InStructs, FAddArgs Args = FAddArgs::Default);`
- L490 _public prototype_ `void Append(UObject& InOwner, TConstArrayView<FConstStructView> InStructs, TConstArrayView<FInstancedStruct*> InInstancesToMove, FAddArgs Args = FAddArgs::Default);` — Appends new items to the instance, and moves existing data into the allocated instances. If the struct is of type FStateTreeInstanceObjectWrapper then this will duplicate the UObject instance.
- L495 _public prototype_ `void Append(UObject& InOwner, TConstArrayView<FConstStructView> InStructs, TConstArrayView<TOptional<FInstancedStruct*>> InInstancesToMove, FAddArgs Args = FAddArgs::Default);` — Appends new items to the instance, and moves existing data into the allocated instances, if provided. If the struct is of type FStateTreeInstanceObjectWrapper then this will duplicate the UObject instance only if the InstanceToMove is set.
- L498 _public prototype_ `void ShrinkTo(const int32 Num);` — Shrinks the array sizes to specified lengths. Sizes must be small or equal than current size.
- L501 _public prototype_ `void CopyFrom(UObject& InOwner, const FStateTreeInstanceData& InOther);` — Shares the layout from another instance data, and copies the data over.
- L504 _public prototype_ `void Reset();` — Resets the data to empty.
- L507 _public function_ `int32 Num() const` — @return Number of items in the instance data.
- L513 _public function_ `bool IsValidIndex(const int32 Index) const` — @return true if the specified index is valid index into the instance data container.
- L519 _public function_ `bool IsObject(const int32 Index) const` — @return true if the data at specified index is object.
- L525 _public function_ `FStructView GetMutableStruct(const int32 Index)` — @return mutable view to the struct at specified index.
- L531 _public function_ `FConstStructView GetStruct(const int32 Index) const` — @return const view to the struct at specified index.
- L537 _public function_ `UObject* GetMutableObject(const int32 Index)` — @return pointer to an instance object
- L543 _public function_ `const UObject* GetObject(const int32 Index) const` — @return const pointer to an instance object
- L549 _public function_ `const FStateTreeExecutionState* GetExecutionState() const` — @return pointer to StateTree execution state, or null if the instance data is not initialized.
- L555 _public function_ `FStateTreeExecutionState* GetMutableExecutionState()` — @return mutable pointer to StateTree execution state, or null if the instance data is not initialized.
- L561 _public prototype_ `FStateTreeEventQueue& GetMutableEventQueue();` — @return reference to the event queue.
- L562 _public prototype_ `const FStateTreeEventQueue& GetEventQueue() const;`
- L563 _public prototype_ `const TSharedRef<FStateTreeEventQueue>& GetSharedMutableEventQueue();`
- L566 _public prototype_ `bool IsOwningEventQueue() const;` — @return true if the instance data owns its' event queue.
- L569 _public prototype_ `void SetSharedEventQueue(const TSharedRef<FStateTreeEventQueue>& InSharedEventQueue);` — Sets event queue from another instance data. Marks the event queue not owned.
- L576 _public prototype_ `void AddTransitionRequest(const UObject* Owner, const FStateTreeTransitionRequest& Request);` — Buffers a transition request to be sent to the State Tree. @param Owner Optional pointer to an owner UObject that is used for logging errors. @param Request transition to request.
- L579 _public prototype_ `TConstArrayView<FStateTreeTransitionRequest> GetTransitionRequests() const;` — @return currently pending transition requests.
- L582 _public prototype_ `void ResetTransitionRequests();` — Reset all pending transition requests.
- L585 _public prototype_ `bool AreAllInstancesValid() const;` — @return true if all instances are valid.
- L587 _public prototype_ `FStateTreeInstanceStorage& GetMutableStorage();`
- L588 _public prototype_ `const FStateTreeInstanceStorage& GetStorage() const;`
- L590 _public prototype_ `TWeakPtr<FStateTreeInstanceStorage> GetWeakMutableStorage();`
- L591 _public prototype_ `TWeakPtr<const FStateTreeInstanceStorage> GetWeakStorage() const;`
- L593 _public prototype_ `int32 GetEstimatedMemoryUsage() const;`
- L596 _public prototype_ `bool Identical(const FStateTreeInstanceData* Other, uint32 PortFlags) const;` — Type traits
- L597 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector);`
- L598 _public prototype_ `bool Serialize(FArchive& Ar);`
- L599 _public prototype_ `void GetPreloadDependencies(TArray<UObject*>& OutDeps);`
- L605 _public function_ `FStructView AddTemporaryInstance(UObject& InOwner, const FStateTreeExecutionFrame& Frame, const FStateTreeIndex16 OwnerNodeIndex, const FStateTreeDataHandle DataHandle, FConstStructView NewInstanceData)` — Adds temporary instance data associated with specified frame and data handle. @returns mutable struct view to the instance.
- L611 _public function_ `FStructView GetMutableTemporaryStruct(const FStateTreeExecutionFrame& Frame, const FStateTreeDataHandle DataHandle)` — @returns mutable view to the specified instance data, or invalid view if not found.
- L617 _public function_ `UObject* GetMutableTemporaryObject(const FStateTreeExecutionFrame& Frame, const FStateTreeDataHandle DataHandle)` — @returns mutable pointer to the specified instance data object, or invalid view if not found. Will check() if called on non-object data.
- L623 _public function_ `void ResetTemporaryInstances()` — Empties the temporary instances.
- L629 _public function_ `UE::StateTree::Debug::FRuntimeValidation GetRuntimeValidation() const` — Get the data used at runtime to confirm the inner working of the StateTree.
- L636 _protected member_ `TSharedRef<FStateTreeInstanceStorage> InstanceStorage = MakeShared<FStateTreeInstanceStorage>();` — Storage for the actual instance data, always stores FStateTreeInstanceStorage.
- L642 _protected member_ `TInstancedStruct<FStateTreeInstanceStorage> InstanceStorage_DEPRECATED;` — `UPROPERTY()`

#### struct `FStateTreeInstanceData::FAddArgs`  
`struct FAddArgs`  
_L471-476_
- L473 _public member_ `static FAddArgs Default;`
- L475 _public member_ `bool bDuplicateWrappedObject = true;` — Duplicate the object contained by object wrapper.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FStateTreeInstanceData> : public TStructOpsTypeTraitsBase2<FStateTreeInstanceData>`  
_L656-665_
- inherits: `TStructOpsTypeTraitsBase2<FStateTreeInstanceData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L659-664_

#### struct `TStateTreeInstanceDataStructRef`  
`template <typename T> struct TStateTreeInstanceDataStructRef`  
_L697-834_
- desc: Stores indexed reference to a instance data struct. The instance data structs may be relocated when the instance data composition changed. For that reason you cannot store pointers to the instance data. This is often needed for example when dealing with delegate lambda's. This helper struct stores data to be able to find the instance data in the instance data array. That way we can access the instance data even of the array changes, and the instance data moves in memory. Note that the reference is valid only during the lifetime of a task (between a call EnterState() and ExitState()). You generally do not use this directly, but via FStateTreeExecutionContext. EStateTreeRunStatus FTestTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const { FInstanceDataType& InstanceData = Context.GetInstanceData(*this); Context.GetWorld()->GetTimerManager().SetTimer( InstanceData.TimerHandle, [InstanceDataRef = Context.GetInstanceDataStructRef(*this)]() { if (FInstanceDataType* InstanceData = InstanceDataRef.GetPtr()) { ... } }, Delay, true); return EStateTreeRunStatus::Running; }
- L699 _public function_ `TStateTreeInstanceDataStructRef(TWeakPtr<FStateTreeInstanceStorage> InWeakStorage, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle InDataHandle) : WeakStorage(InWeakStorage) , FrameID(CurrentFrame.FrameID) , DataHandle(InDataHandle)`
- L711 _public function_ `TStateTreeInstanceDataStructRef(FStateTreeInstanceData& InInstanceData, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle InDataHandle) : TStateTreeInstanceDataStructRef(InInstanceData.GetWeakMutableStorage(), CurrentFrame, InDataHandle)`
- L717 _public prototype_ `TStateTreeInstanceDataStructRef(const TStateTreeInstanceDataStructRef& Other) = default;`
- L718 _public prototype_ `TStateTreeInstanceDataStructRef(TStateTreeInstanceDataStructRef&& Other) = default;`
- L719 _public prototype_ `TStateTreeInstanceDataStructRef& operator=(TStateTreeInstanceDataStructRef const& Other) = default;`
- L720 _public prototype_ `TStateTreeInstanceDataStructRef& operator=(TStateTreeInstanceDataStructRef&& Other) = default;`
- L723 _public function_ `bool IsValid() const`
- L728 _public function_ `T* GetPtr() const`
- L786 _protected function_ `FStateTreeDataView GetDataView(FStateTreeInstanceStorage& Storage, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle Handle) const`
- L804 _protected function_ `bool IsHandleSourceValid(FStateTreeInstanceStorage& Storage, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle Handle) const`
- L824 _protected member_ `TWeakPtr<FStateTreeInstanceStorage> WeakStorage = nullptr;`
- L825 _protected member_ `UE::StateTree::FActiveFrameID FrameID;`
- L826 _protected member_ `FStateTreeDataHandle DataHandle = FStateTreeDataHandle::Invalid;`
- L830 _protected member_ `TWeakObjectPtr<const UStateTree> WeakStateTree = nullptr;` — `UE_DEPRECATED(5.6, "Use the frame id to identify the frame.")`
- L832 _protected member_ `FStateTreeStateHandle RootState = FStateTreeStateHandle::Invalid;` — `UE_DEPRECATED(5.6, "Use the frame id to identify the frame.")`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API STATETREEMODULE_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace StateTree` (scope `UE`)
- L24 _namespace_ `namespace Debug` (scope `UE::StateTree`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace StateTree` (scope `UE`)
- L30 _namespace_ `namespace InstanceData` (scope `UE::StateTree`)
- L33 _prototype_ `[[nodiscard]] FStateTreeDataView GetDataView( FStateTreeInstanceStorage& InstanceStorage, FStateTreeInstanceStorage* SharedInstanceStorage, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle& Handle);` (scope `UE::StateTree::InstanceData`) — @return data view of the specified handle relative to the given frame.
- L40 _function_ `[[nodiscard]] inline FStateTreeDataView GetDataView( FStateTreeInstanceStorage& InstanceStorage, FStateTreeInstanceStorage* SharedInstanceStorage, const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle& Handle)` (scope `UE::StateTree::InstanceData`) — `UE_DEPRECATED(5.8, "Use the version without Parent Frame instead")`
- L51 _prototype_ `[[nodiscard]] FStateTreeDataView GetDataViewOrTemporary( FStateTreeInstanceStorage& InstanceStorage, FStateTreeInstanceStorage* SharedInstanceStorage, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle& Handle);` (scope `UE::StateTree::InstanceData`) — @return data view of the specified handle relative to the given frame, or tries to find a matching temporary instance.
- L58 _function_ `[[nodiscard]] inline FStateTreeDataView GetDataViewOrTemporary( FStateTreeInstanceStorage& InstanceStorage, FStateTreeInstanceStorage* SharedInstanceStorage, const FStateTreeExecutionFrame* ParentFrame, const FStateTreeExecutionFrame& CurrentFrame, const FStateTreeDataHandle& Handle)` (scope `UE::StateTree::InstanceData`) — `UE_DEPRECATED(5.8, "Use the version without Parent Frame instead")`
- L74 _prototype_ `bool DoesRequireExecutionContext(EStateTreeDataSourceType SourceType);` (scope `UE::StateTree::InstanceData`) — Check if a data source type requires FStateTreeExecutionContext to access. Sources that require execution context include context data, external data, and evaluation scope data. @param SourceType The data source type to check. @return true if the source requires a full FStateTreeExecutionContext to access.
- L81 _prototype_ `bool DoesRequireInstanceStorage(EStateTreeDataSourceType SourceType);` (scope `UE::StateTree::InstanceData`) — Check if a data source type can be access from the UE::StateTree::InstanceData::GetDataView function. @param SourceType The data source type to check. @return true if the source doesn't requires anything other than the provided arguments.
- L649 _namespace_ `namespace UE`
- L649 _namespace_ `namespace StateTree` (scope `UE`)
- L651 _prototype_ `void RegisterInstanceDataForLocalization();` (scope `UE::StateTree`)
- L660 _enumerator_ `WithIdentical = true` (scope `TStructOpsTypeTraits::__anon15ed62e40103`)
- L661 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon15ed62e40103`)
- L662 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon15ed62e40103`)
- L663 _enumerator_ `WithGetPreloadDependencies = true` (scope `TStructOpsTypeTraits::__anon15ed62e40103`)
- L756 _function_ `` (scope `TStateTreeInstanceDataStructRef::GetPtr`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeLinker.h` (Public)


#### enum `EStateTreeLinkerStatus`  
`enum class EStateTreeLinkerStatus : uint8`  
_L14-18_
- reflection: `UENUM()`
- L16 _public enumerator_ `Succeeded`
- L17 _public enumerator_ `Failed`

#### struct `FStateTreeLinker`  
`struct FStateTreeLinker`  
_L24-95_
- desc: The StateTree linker is used to resolved references to various StateTree data at load time. @see TStateTreeExternalDataHandle<> for example usage.
- L26 _public prototype_ `explicit FStateTreeLinker(TNotNull<const UStateTree*> InStateTree);`
- L29 _public function_ `explicit FStateTreeLinker(const UStateTreeSchema* InSchema) : Schema(InSchema)` — `UE_DEPRECATED(5.7, "Use the constructor with the StateTree pointer.")`
- L34 _public function_ `EStateTreeLinkerStatus GetStatus() const` — @returns the linking status.
- L40 _public function_ `const UStateTree* GetStateTree() const` — @returns the StateTree asset.
- L50 _public function_ `template <typename T> typename TEnableIf<TIsDerivedFrom<typename T::DataType, UObject>::IsDerived, void>::Type LinkExternalData(T& Handle)` — Links reference to an external UObject. @param Handle Reference to TStateTreeExternalDataHandle<> with UOBJECT type to link to.
- L60 _public function_ `template <typename T> typename TEnableIf<!TIsDerivedFrom<typename T::DataType, UObject>::IsDerived && !TIsIInterface<typename T::DataType>::Value, void>::Type LinkExternalData(T& Handle)` — Links reference to an external UStruct. @param Handle Reference to TStateTreeExternalDataHandle<> with USTRUCT type to link to.
- L70 _public function_ `template <typename T> typename TEnableIf<TIsIInterface<typename T::DataType>::Value, void>::Type LinkExternalData(T& Handle)` — Links reference to an external IInterface. @param Handle Reference to TStateTreeExternalDataHandle<> with IINTERFACE type to link to.
- L82 _public prototype_ `void LinkExternalData(FStateTreeExternalDataHandle& Handle, const UStruct* Struct, const EStateTreeExternalDataRequirement Requirement);` — Links reference to an external Object or Struct. This function should only be used when TStateTreeExternalDataHandle<> cannot be used, i.e. the Struct is based on some data. @param Handle Reference to link to. @param Struct Expected type of the Object or Struct to link to. @param Requirement Describes if the external data is expected to be required or optional.
- L85 _public function_ `const TArrayView<const FStateTreeExternalDataDesc> GetExternalDataDescs() const` — @return linked external data descriptors.
- L91 _protected member_ `TStrongObjectPtr<const UStateTree> StateTree;`
- L92 _protected member_ `TStrongObjectPtr<const UStateTreeSchema> Schema;`
- L93 _protected member_ `EStateTreeLinkerStatus Status = EStateTreeLinkerStatus::Succeeded;`
- L94 _protected member_ `TArray<FStateTreeExternalDataDesc> ExternalDataDescs;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeModule.h` (Public)


#### class `IStateTreeModule`  
`class IStateTreeModule : public IModuleInterface`  
_L22-88_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L33 _public function_ `static IStateTreeModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L43 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L56 _public prototype_ `virtual bool StartTraces(int32& OutTraceId) = 0;` — Creates new tracing connection if necessary and enables StateTree debugging related channels (frame + statetree). If traces are already active we keep track of all channels previously activated to restore them on stop. @param OutTraceId In case a connection is already active this indicates its id, 0 otherwise. @return True if a new trace connection was created, false otherwise (already active or not created) @note Even if it returns false this can still have enabled StateTree related channels, OutTraceId will indicate which trace to use and StopTraces should be called to restore to previous setup.
- L62 _public prototype_ `virtual void StopTraces() = 0;` — Stops the trace service if it was not already connected when StartTraces was called. Restores previously enabled channels if necessary.
- L68 _public prototype_ `virtual bool IsTracing() const = 0;` — Indicates if the statetree specific traces are active (explicitly started by StartTraces). @return True is StartTraces was called, false otherwise.
- L75 _public prototype_ `virtual TNotNull<const IStateTreeDebugInfoProvider*> GetDebugInfoProvider() = 0;` — Returns debug info provider. Creates on get if needed. @return ptr to debug info provider to query against.
- L81 _public prototype_ `virtual void SetDebugInfoProvider(TSharedPtr<IStateTreeDebugInfoProvider> InDebugInfoProvider) = 0;` — Sets debug info provider. @param ptr to debug info provider to query against.
- L86 _public prototype_ `virtual UE::Trace::FStoreClient* GetStoreClient() = 0;` — Gets the store client.

#### class `IStateTreeDebugInfoProvider`  
`class IStateTreeDebugInfoProvider`  
_L94-101_
- desc: Allows runtime to use editor data for debugging wben available & fallback to runtime only if needed.
- L97 _public prototype_ `virtual ~IStateTreeDebugInfoProvider() = default;`
- L100 _public prototype_ `virtual FText GetNodeDescription(TNotNull<const UStateTree*> StateTree, FStateTreeIndex16 NodeIndex) const = 0;` — Get text desc for the node

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Trace` (scope `UE`)
- L17 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeNodeBase.h` (Public)


#### struct `UE::StateTree::ICompileNodeContext`  
`struct ICompileNodeContext`  
_L29-35_
- L31 _public prototype_ `virtual ~ICompileNodeContext() = default;`
- L32 _public prototype_ `virtual void AddValidationError(const FText& Message) = 0;`
- L33 _public prototype_ `virtual FStateTreeDataView GetInstanceDataView() const = 0;`
- L34 _public prototype_ `virtual bool HasBindingForProperty(const FName PropertyName) const = 0;`

#### enum `EStateTreeNodeFormatting`  
`enum class EStateTreeNodeFormatting : uint8`  
_L47-57_
- reflection: `UENUM(BlueprintType)`
- desc: Enum describing in what format a text is expected to be returned. - Normal text should be used for values - Bold text should generally be used for actions, like name a of a task "<b>Play Animation</> {AnimName}". - Subdued should be generally used for secondary/structural information, like "{Left} <s>equals</> {Right}".
- L53 _public enumerator_ `RichText` — The returned text can contain following right text formatting (no nesting) - <b>Bold</> (bolder font is used) - <s>Subdued</> (normal font with lighter color)
- L56 _public enumerator_ `Text` — The text should be unformatted

#### struct `FStateTreeNodeBase`  
`struct FStateTreeNodeBase`  
_L63-233_
- reflection: `USTRUCT()`
- desc: Base struct of StateTree Conditions, Considerations, Evaluators, and Tasks.
- L68 _public prototype_ `FStateTreeNodeBase() = default;`
- L69 _public prototype_ `FStateTreeNodeBase(const FStateTreeNodeBase&) = default;`
- L70 _public prototype_ `FStateTreeNodeBase(FStateTreeNodeBase&&) = default;`
- L71 _public prototype_ `FStateTreeNodeBase& operator=(const FStateTreeNodeBase&) = default;`
- L72 _public prototype_ `FStateTreeNodeBase& operator=(FStateTreeNodeBase&&) = default;`
- L82 _public typedef_ `using FInstanceDataType = FNoInstanceDataType;` — The instance data type. The implementation node should set its type. The type should match GetInstanceDataType().
- L89 _public typedef_ `using FExecutionRuntimeDataType = FNoInstanceDataType;` — The execution runtime data type. Execution runtime is optional. If needed, the implementation node should set its type. The type should match GetExecutionRuntimeDataType().
- L91 _public prototype_ `virtual ~FStateTreeNodeBase() = default;`
- L94 _public function_ `virtual const UStruct* GetInstanceDataType() const` — @return Struct that represents the runtime data of the node.
- L105 _public function_ `virtual const UStruct* GetExecutionRuntimeDataType() const` — Execution runtime data is always valid between an FStateTreeExecutionContext::Start and FStateTreeExecutionContext::Stop. If the node is no longer active but the instance (FStateTreeInstanceData) is active, the data is still valid and will persist. @note Be careful about UObject reference, the objects are garbage collected like normal references. @return the struct that represents the persistent runtime data of the node.
- L116 _public function_ `[[nodiscard]] virtual bool Link(FStateTreeLinker& Linker)` — Called when the StateTree asset is linked. Allows to resolve references to other StateTree data. @see TStateTreeExternalDataHandle @param Linker Reference to the linker @return true if linking succeeded.
- L129 _public function_ `virtual EDataValidationResult Compile(UE::StateTree::ICompileNodeContext& CompileContext)` — Called during State Tree compilation, allows to modify and validate the node and instance data. The method is called with node and instance that is duplicated during compilation and used at runtime (it's different than the data used in editor). @param ValidationMessages Any messages to report during validation. Displayed as errors if the validation result is Invalid, else as warnings. @param CompileContext @return Validation result based on if the validation succeeded or not. Returning Invalid will fail compilation and messages will be displayed as errors.
- L142 _public function_ `virtual EDataValidationResult Compile(FStateTreeDataView InstanceDataView, TArray<FText>& ValidationMessages) final` — `UE_DEPRECATED(5.6, "Use the version with Binding infos instead")` — Called during State Tree compilation, allows to modify and validate the node and instance data. The method is called with node and instance that is duplicated during compilation and used at runtime (it's different than the data used in editor). @param InstanceDataView Pointer to the instance data. @param ValidationMessages Any messages to report during validation. Displayed as errors if the validation result is Invalid, else as warnings. @return Validation result based on if the validation succeeded or not. Returning Invalid will fail compilation and messages will be displayed as errors.
- L155 _public function_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const` — Returns description for the node, use in the UI. The UI description is selected as follows: - Node Name, if not empty - Description if not empty - Display name of the node struct @param ID ID of the item, can be used make property paths to this item. @param InstanceDataView View to the instance data, can be struct or class. @param BindingLookup Reference to binding lookup which can be used to reason about property paths. @param Formatting Requested formatting (whether rich or plain text should be returned).
- L166 _public function_ `virtual FName GetIconName() const` — @returns name of the icon in format: StyleSetName | StyleName [ | SmallStyleName | StatusOverlayStyleName] SmallStyleName and StatusOverlayStyleName are optional. Example: "StateTreeEditorStyle|Node.Animation"
- L172 _public function_ `virtual FColor GetIconColor() const` — @return the color to be used with the icon.
- L185 _public function_ `virtual void OnBindingChanged(const FGuid& ID, FStateTreeDataView InstanceDataView, const FPropertyBindingPath& SourcePath, const FPropertyBindingPath& TargetPath, const IStateTreeBindingLookup& BindingLookup)` — Called when binding of any of the properties in the node changes. @param ID ID of the item, can be used make property paths to this item. @param InstanceDataView view to the instance data, can be struct or class. @param SourcePath Source path of the new binding. @param TargetPath Target path of the new binding (the property in the condition). @param BindingLookup Reference to binding lookup which can be used to reason about property paths.
- L187 _public function_ `virtual void OnBindingChanged(const FGuid& ID, FStateTreeDataView InstanceDataView, const FStateTreePropertyPath& SourcePath, const FStateTreePropertyPath& TargetPath, const IStateTreeBindingLookup& BindingLookup) final` — `UE_DEPRECATED(5.6, "Use the version taking FPropertyBindingPath instead")`
- L194 _public function_ `virtual void PostEditNodeChangeChainProperty(const FPropertyChangedChainEvent& PropertyChangedEvent, FStateTreeDataView InstanceDataView)` — Called when a property of the node has been modified externally @param PropertyChangedEvent The event for the changed property. PropertyChain's active properties are set relative to node. @param InstanceData view to the instance data, can be struct or class.
- L201 _public function_ `virtual void PostEditInstanceDataChangeChainProperty(const FPropertyChangedChainEvent& PropertyChangedEvent, FStateTreeDataView InstanceDataView)` — Called when a property of node's instance data has been modified externally @param PropertyChangedEvent The event for the changed property. PropertyChain's active properties are set relative to instance data. @param InstanceData view to the instance data, can be struct or class.
- L208 _public function_ `virtual void PostLoad(FStateTreeDataView InstanceDataView)` — Called after the state tree asset that contains this node is loaded from disk. @param InstanceDataView view to the instance data, can be struct or class.
- L212 _public member_ `FName Name;` — `UPROPERTY(EditDefaultsOnly, Category = "", meta=(EditCondition = "false", EditConditionHides))` — Name of the node.
- L216 _public member_ `FStateTreeIndex16 BindingsBatch = FStateTreeIndex16::Invalid;` — `UPROPERTY()` — Property binding copy batch handle.
- L220 _public member_ `FStateTreeIndex16 OutputBindingsBatch = FStateTreeIndex16::Invalid;` — `UPROPERTY()` — Property output binding copy batch handle.
- L224 _public member_ `FStateTreeIndex16 InstanceTemplateIndex = FStateTreeIndex16::Invalid;` — `UPROPERTY()` — Index of template instance data for the node. Can point to Shared or Default instance data in StateTree depending on node type.
- L228 _public member_ `FStateTreeIndex16 ExecutionRuntimeTemplateIndex = FStateTreeIndex16::Invalid;` — `UPROPERTY()` — Index of template execution runtime data for the node.
- L232 _public member_ `FStateTreeDataHandle InstanceDataHandle = FStateTreeDataHandle::Invalid;` — `UPROPERTY()` — Data handle to access the instance data.

#### struct `FStateTreeNodeBase::FNoInstanceDataType`  
`struct FNoInstanceDataType`  
_L75-76_

#### Free symbols / members of external scopes

- L15 _macro_ `#define SET_NODE_CUSTOM_TRACE_TEXT(Context, MergePolicy, Format, ...) \`
- L23 _macro_ `#define SET_NODE_CUSTOM_TRACE_TEXT(...)`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace StateTree` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeNodeDescriptionHelpers.h` (Public)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace StateTree` (scope `UE`)
- L18 _namespace_ `namespace DescHelpers` (scope `UE::StateTree`)
- L23 _prototype_ `extern FText GetOperatorText(const EComparisonOperator Operator, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`) — @return description for a EComparisonOperator.
- L27 _prototype_ `extern FText GetOperatorText(const EGenericAICheck Operator, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`) — @return description for a EComparisonOperator.
- L30 _prototype_ `extern FText GetInvertText(bool bInvert, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`) — @return description for condition inversion (returns "Not" plus a space).
- L33 _prototype_ `extern FText GetBoolText(bool bValue, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`) — @return description of a boolean value.
- L36 _prototype_ `extern FText GetIntervalText(const FFloatInterval& Interval, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`) — @return description of a float interval.
- L39 _prototype_ `extern FText GetIntervalText(float Min, float Max, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`) — @return description of a float interval.
- L42 _prototype_ `extern FText GetIntervalText(const FText& MinValueText, const FText& MaxValueText, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`) — @return description of a float interval.
- L45 _prototype_ `extern FText GetGameplayTagContainerAsText(const FGameplayTagContainer& TagContainer, const int ApproxMaxLength = 60);` (scope `UE::StateTree::DescHelpers`) — @return description for a Gameplay Tag Container. If the length of container description is longer than ApproxMaxLength, the it truncated and ... as added to the end.
- L48 _prototype_ `extern FText GetGameplayTagQueryAsText(const FGameplayTagQuery& TagQuery, const int ApproxMaxLength = 120);` (scope `UE::StateTree::DescHelpers`) — @return description for a Gameplay Tag Query. If the query description is longer than ApproxMaxLength, the it truncated and ... as added to the end.
- L51 _prototype_ `extern FText GetExactMatchText(bool bExactMatch, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`) — @return description for exact match, used for Gameplay Tag matching functions (returns "Exactly" plus space).
- L54 _prototype_ `extern FText GetText(const FVector& Value, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`) — @return description of a vector value.
- L57 _prototype_ `extern FText GetText(float Value, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`) — @return description of a float value.
- L60 _prototype_ `extern FText GetText(int32 Value, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`) — @return description of an int value.
- L63 _prototype_ `extern FText GetText(const UObject* Value, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`) — @return description of a UObject value.
- L65 _prototype_ `extern FText GetMathOperationText(const FText& OperationText, const FText& LeftText, const FText& RightText, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`)
- L67 _prototype_ `extern FText GetSingleParamFunctionText(const FText& FunctionText, const FText& ParamText, EStateTreeNodeFormatting Formatting);` (scope `UE::StateTree::DescHelpers`)
- L77 _function_ `template <typename TInstanceDataType> FText GetDescriptionForMathOperation(FText OperationText, const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting)` (scope `UE::StateTree::DescHelpers`) — @return description in the form of (Left OperationText Right). Expect TInstanceDataType to have a member Left and Right whose types have an overloaded UE::StateTree::DescHelpers::GetText function.
- L100 _function_ `template <typename TInstanceDataType> FText GetDescriptionForSingleParameterFunc(FText OperationText, const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting)` (scope `UE::StateTree::DescHelpers`) — @return description in the form of OperationText(Input). Expect TInstanceDataType to have a member input whose type has an overloaded UE::StateTree::DescHelpers::GetText function.

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeNodeRef.h` (Public)


#### struct `FStateTreeStrongTaskRef`  
`struct UE_DEPRECATED(5.6, "FStateTreeStrongTaskRef is deprecated. We now use TaskIndex in WeakExecutionContext.") FStateTreeStrongTaskRef`  
_L15-45_
- desc: A reference to a task that can utilized in a async callback. Use FStateTreeWeakTaskRef to store the reference and Pin it to get the strong version. Similar to StrongPtr and WeakPtr.
- L17 _public prototype_ `explicit FStateTreeStrongTaskRef() = default;`
- L19 _public prototype_ `explicit FStateTreeStrongTaskRef(TStrongObjectPtr<const UStateTree> StateTree, const FStateTreeTaskBase* Task, FStateTreeIndex16 NodeIndex, FGuid NodeId);`
- L21 _public prototype_ `explicit FStateTreeStrongTaskRef(TStrongObjectPtr<const UStateTree> StateTree, const FStateTreeTaskBase* Task, FStateTreeIndex16 NodeIndex);`
- L24 _public prototype_ `const UStateTree* GetStateTree() const;`
- L25 _public prototype_ `const FStateTreeTaskBase* GetTask() const;`
- L26 _public function_ `FStateTreeIndex16 GetTaskIndex() const`
- L31 _public function_ `operator bool() const`
- L36 _public prototype_ `bool IsValid() const;`
- L39 _private member_ `TStrongObjectPtr<const UStateTree> StateTree;`
- L40 _private member_ `const FStateTreeTaskBase* Task = nullptr;`
- L41 _private member_ `FStateTreeIndex16 NodeIndex = FStateTreeIndex16::Invalid;`
- L43 _private member_ `FGuid NodeId;`

#### struct `FStateTreeWeakTaskRef`  
`struct UE_DEPRECATED(5.6, "FStateTreeWeakTaskRef is deprecated. We now use TaskIndex in WeakExecutionContext.") FStateTreeWeakTaskRef`  
_L51-71_
- desc: A reference to a task that can be retrieve. Similar to StrongPtr and WeakPtr.
- L53 _public prototype_ `explicit FStateTreeWeakTaskRef() = default;`
- L54 _public prototype_ `explicit FStateTreeWeakTaskRef(TNotNull<const UStateTree*> StateTree, FStateTreeIndex16 TaskIndex);`
- L57 _public prototype_ `FStateTreeStrongTaskRef Pin() const;`
- L60 _public function_ `void Release()`
- L66 _private member_ `TWeakObjectPtr<const UStateTree> StateTree;`
- L67 _private member_ `FStateTreeIndex16 NodeIndex = FStateTreeIndex16::Invalid;`
- L69 _private member_ `FGuid NodeId;`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreePropertyBindings.h` (Public)


#### enum `EStateTreeBindableStructSource`  
`enum class EStateTreeBindableStructSource : uint8`  
_L26-52_
- reflection: `UENUM()`
- L29 _public enumerator_ `Context` — Source is StateTree context object
- L31 _public enumerator_ `Parameter` — Source is StateTree parameter
- L33 _public enumerator_ `Evaluator` — Source is StateTree evaluator
- L35 _public enumerator_ `GlobalTask` — Source is StateTree global task
- L37 _public enumerator_ `StateParameter` — Source is State parameter
- L39 _public enumerator_ `Task` — Source is State task
- L41 _public enumerator_ `Condition` — Source is State condition
- L43 _public enumerator_ `Consideration` — Source is State utility consideration
- L45 _public enumerator_ `TransitionEvent` — Source is StateTree event used by transition
- L47 _public enumerator_ `StateEvent` — Source is StateTree event used by state selection
- L49 _public enumerator_ `PropertyFunction` — Source is Property Function
- L51 _public enumerator_ `Transition` — Source is Transition

#### struct `FStateTreeBindableStructDesc`  
`struct FStateTreeBindableStructDesc : public FPropertyBindingBindableStructDescriptor`  
_L65-101_
- reflection: `USTRUCT()`
- inherits: `FPropertyBindingBindableStructDescriptor`
- desc: Descriptor for a struct or class that can be a binding source or target. Each struct has unique identifier, which is used to distinguish them, and name that is mostly for debugging and UI.
- L69 _public prototype_ `FStateTreeBindableStructDesc() = default;`
- L72 _public function_ `FStateTreeBindableStructDesc(const FString& InStatePath, const FName InName, const UStruct* InStruct, const FStateTreeDataHandle InDataHandle, const EStateTreeBindableStructSource InDataSource, const FGuid InGuid) : FPropertyBindingBindableStructDescriptor(InName, InStruct, InGuid) , DataHandle(InDataHandle) , DataSource(InDataSource) , StatePath(InStatePath)`
- L80 _public function_ `virtual FString GetSection() const override`
- L86 _public prototype_ `virtual FString ToString() const override;`
- L90 _public member_ `FStateTreeDataHandle DataHandle = FStateTreeDataHandle::Invalid;` — `UPROPERTY()` — Runtime data the struct represents.
- L94 _public member_ `EStateTreeBindableStructSource DataSource = EStateTreeBindableStructSource::Context;` — `UPROPERTY()` — Type of the source.
- L99 _public member_ `FString StatePath;` — `UPROPERTY(Transient)` — In Editor path to State containing the data.

#### struct `FStateTreeEditorPropertyPath`  
`struct UE_DEPRECATED(all, "Use FPropertyBindingPath instead.") FStateTreeEditorPropertyPath`  
_L104-122_
- reflection: `USTRUCT()`
- L111 _public member_ `FGuid StructID;` — `UPROPERTY()` — Handle of the struct this property path is relative to.
- L115 _public member_ `TArray<FString> Path;` — `UPROPERTY()` — Property path segments
- L117 _public function_ `bool IsValid() const`

#### struct `FStateTreePropertyPathBinding`  
`struct FStateTreePropertyPathBinding : public FPropertyBindingBinding`  
_L128-240_
- reflection: `USTRUCT()`
- inherits: `FPropertyBindingBinding`
- desc: Representation of a property binding in StateTree
- L133 _public prototype_ `FStateTreePropertyPathBinding() = default;`
- L135 _public function_ `FStateTreePropertyPathBinding(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath, const bool bInIsOutputBinding) : FPropertyBindingBinding(InSourcePath, InTargetPath) , bIsOutputBinding(bInIsOutputBinding)`
- L142 _public function_ `FStateTreePropertyPathBinding(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath) : FStateTreePropertyPathBinding(InSourcePath, InTargetPath, false)` — `UE_DEPRECATED(5.7, "Use the version with bInIsOutputBinding instead.")`
- L147 _public function_ `FStateTreePropertyPathBinding(const FStateTreeDataHandle InSourceDataHandle, const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath, const bool bInIsOutputBinding) : FPropertyBindingBinding(InSourcePath, InTargetPath) , SourceDataHandle(InSourceDataHandle) , bIsOutputBinding(bInIsOutputBinding)`
- L155 _public function_ `FStateTreePropertyPathBinding(const FStateTreeDataHandle InSourceDataHandle, const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath) : FStateTreePropertyPathBinding(InSourceDataHandle, InSourcePath, InTargetPath, false)` — `UE_DEPRECATED(5.7, "Use the version with bInIsOutputBinding instead.")`
- L161 _public function_ `FStateTreePropertyPathBinding(FConstStructView InFunctionNodeStruct, const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath) : FPropertyBindingBinding(InFunctionNodeStruct, InSourcePath, InTargetPath)`
- L170 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L173 _public function_ `void SetSourceDataHandle(const FStateTreeDataHandle NewSourceDataHandle)`
- L178 _public function_ `FStateTreeDataHandle GetSourceDataHandle() const`
- L183 _public function_ `void SetIsOutputBinding(const bool bInIsOutputBinding)`
- L188 _public function_ `bool IsOutputBinding() const`
- L193 _public function_ `void SetCompletionBinding(const UE::StateTree::ETaskCompletionCondition Condition)`
- L198 _public function_ `TOptional<UE::StateTree::ETaskCompletionCondition> GetCompletionBinding() const`
- L203 _public function_ `bool IsTaskCompletionBinding() const`
- L209 _protected function_ `virtual FConstStructView GetSourceDataHandleStruct() const override`
- L217 _private member_ `FStateTreeDataHandle SourceDataHandle = FStateTreeDataHandle::Invalid;` — `UPROPERTY()` — Describes how to get the source data pointer for the binding.
- L221 _private member_ `bool bIsOutputBinding = false;` — `UPROPERTY()` — Whether this binding is reversed(i.e., copying from target to source).
- L229 _private member_ `TOptional<UE::StateTree::ETaskCompletionCondition> TaskCompletionCondition;` — `UPROPERTY()` — Whether this is a task completion binding. The SourcePath.StructID is set to the task node ID (template) The SourcePath.Segments is empty.
- L234 _private member_ `FStateTreeEditorPropertyPath SourcePath_DEPRECATED;` — `UPROPERTY()`
- L237 _private member_ `FStateTreeEditorPropertyPath TargetPath_DEPRECATED;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FStateTreePropertyPathBinding> : public TStructOpsTypeTraitsBase2<FStateTreePropertyPathBinding>`  
_L244-250_
- inherits: `TStructOpsTypeTraitsBase2<FStateTreePropertyPathBinding>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L247-249_

#### struct `FStateTreePropertyRefPath`  
`struct FStateTreePropertyRefPath`  
_L257-284_
- reflection: `USTRUCT()`
- desc: Representation of a property reference binding in StateTree.
- L261 _public prototype_ `FStateTreePropertyRefPath() = default;`
- L263 _public function_ `FStateTreePropertyRefPath(FStateTreeDataHandle InSourceDataHandle, const FPropertyBindingPath& InSourcePath) : SourcePropertyPath(InSourcePath) , SourceDataHandle(InSourceDataHandle)`
- L269 _public function_ `const FPropertyBindingPath& GetSourcePath() const`
- L271 _public function_ `FPropertyBindingPath& GetMutableSourcePath()`
- L273 _public function_ `void SetSourceDataHandle(const FStateTreeDataHandle NewSourceDataHandle)`
- L274 _public function_ `FStateTreeDataHandle GetSourceDataHandle() const`
- L279 _private member_ `FPropertyBindingPath SourcePropertyPath;` — `UPROPERTY()` — Source property path of the reference
- L283 _private member_ `FStateTreeDataHandle SourceDataHandle = FStateTreeDataHandle::Invalid;` — `UPROPERTY()` — Describes how to get the source data pointer

#### struct `FStateTreePropertyAccess`  
`struct FStateTreePropertyAccess`  
_L290-308_
- reflection: `USTRUCT()`
- desc: Describes access to referenced property.
- L296 _public member_ `FPropertyBindingPropertyIndirection SourceIndirection;` — `UPROPERTY()` — Source property access.
- L299 _public member_ `const FProperty* SourceLeafProperty = nullptr;` — Cached pointer to the leaf property of the access.
- L303 _public member_ `TObjectPtr<const UStruct> SourceStructType = nullptr;` — `UPROPERTY(Transient)` — Type of the source data, used for validation.
- L307 _public member_ `FStateTreeDataHandle SourceDataHandle = FStateTreeDataHandle::Invalid;` — `UPROPERTY()` — Describes how to get the source data pointer.

#### struct `FStateTreePropertyBindings`  
`struct FStateTreePropertyBindings : public FPropertyBindingBindingCollection`  
_L314-386_
- reflection: `USTRUCT()`
- inherits: `FPropertyBindingBindingCollection`
- desc: Runtime storage and execution of property bindings.
- L318 _public prototype_ `FStateTreePropertyBindings();`
- L323 _public prototype_ `virtual void OnReset() override;` — Clears all bindings.
- L328 _public prototype_ `const FStateTreePropertyAccess* GetPropertyAccess(const FStateTreePropertyRef& Reference) const;` — @return Referenced property access for provided PropertyRef.
- L337 _public prototype_ `template<class T> T* GetMutablePropertyPtr(FStateTreeDataView SourceView, const FStateTreePropertyAccess& PropertyAccess) const;` — Pointer to referenced property @param SourceView Data view to referenced property's owner. @param PropertyAccess Access to the property for which we want to obtain a pointer. @return Pointer to referenced property if it's type match, nullptr otherwise.
- L340 _public prototype_ `virtual int32 GetNumBindableStructDescriptors() const override;`
- L341 _public prototype_ `virtual const FPropertyBindingBindableStructDescriptor* GetBindableStructDescriptorFromHandle(FConstStructView InSourceHandleView) const override;`
- L342 _public prototype_ `virtual void VisitSourceStructDescriptorInternal(TFunctionRef<EVisitResult(const FPropertyBindingBindableStructDescriptor& Descriptor)> InFunction) const override;`
- L343 _public prototype_ `[[nodiscard]] virtual bool ResolveBindingCopyInfo(const FPropertyBindingBinding& InResolvedBinding, const FPropertyBindingPathIndirection& InBindingSourceLeafIndirection, const FPropertyBindingPathIndirection& InBindingTargetLeafIndirection, FPropertyBindingCopyInfo& OutCopyInfo) override;`
- L347 _protected prototype_ `const FPropertyBindingBindableStructDescriptor* GetBindableStructDescriptorFromHandle(FStateTreeDataHandle InSourceHandle) const;`
- L350 _protected prototype_ `[[nodiscard]] virtual bool OnResolvingPaths() override;`
- L352 _protected prototype_ `virtual int32 GetNumBindings() const override;`
- L353 _protected prototype_ `virtual void ForEachBinding(TFunctionRef<void(const FPropertyBindingBinding& Binding)> InFunction) const override;`
- L354 _protected prototype_ `virtual void ForEachBinding(const FPropertyBindingIndex16 InBegin, const FPropertyBindingIndex16 InEnd, const TFunctionRef<void(const FPropertyBindingBinding& Binding, const int32 BindingIndex)> InFunction) const override;`
- L355 _protected prototype_ `virtual void ForEachMutableBinding(TFunctionRef<void(FPropertyBindingBinding& Binding)> InFunction) override;`
- L356 _protected prototype_ `virtual void VisitBindings(TFunctionRef<EVisitResult(const FPropertyBindingBinding& Binding)> InFunction) const override;`
- L357 _protected prototype_ `virtual void VisitBindings(const FPropertyBindingIndex16 InBegin, const FPropertyBindingIndex16 InEnd, TFunctionRef<EVisitResult(const FPropertyBindingBinding& Binding, const int32 BindingIndex)> InFunction) const override;`
- L358 _protected prototype_ `virtual void VisitMutableBindings(TFunctionRef<EVisitResult(FPropertyBindingBinding& Binding)> InFunction) override;`
- L361 _protected prototype_ `virtual FPropertyBindingBinding* AddBindingInternal(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath) override;`
- L362 _protected prototype_ `virtual void RemoveBindingsInternal(TFunctionRef<bool(FPropertyBindingBinding&)> InPredicate) override;`
- L363 _protected prototype_ `virtual bool HasBindingInternal(TFunctionRef<bool(const FPropertyBindingBinding&)> InPredicate) const override;`
- L364 _protected prototype_ `virtual const FPropertyBindingBinding* FindBindingInternal(TFunctionRef<bool(const FPropertyBindingBinding&)> InPredicate) const override;`
- L370 _private member_ `TArray<FStateTreeBindableStructDesc> SourceStructs;` — `UPROPERTY()` — Array of expected source structs.
- L374 _private member_ `TArray<FStateTreePropertyPathBinding> PropertyPathBindings;` — `UPROPERTY()` — Array of property bindings, resolved into arrays of copies before use.
- L378 _private member_ `TArray<FStateTreePropertyRefPath> PropertyReferencePaths;` — `UPROPERTY()` — Array of referenced property paths
- L382 _private member_ `TArray<FStateTreePropertyAccess> PropertyAccesses;` — `UPROPERTY()` — Array of individually accessed properties
- L389 _function_ `template <class T> T* FStateTreePropertyBindings::GetMutablePropertyPtr(FStateTreeDataView SourceView, const FStateTreePropertyAccess& PropertyAccess) const`

#### struct `IStateTreeBindingLookup`  
`struct IStateTreeBindingLookup`  
_L404-419_
- desc: Helper interface to reason about bound properties. The implementation is in the editor plugin.
- L406 _public prototype_ `virtual ~IStateTreeBindingLookup() = default;`
- L409 _public prototype_ `virtual const FPropertyBindingPath* GetPropertyBindingSource(const FPropertyBindingPath& InTargetPath) const = 0;` — @return Source path for given target path, or null if binding does not exists.
- L412 _public prototype_ `virtual FText GetPropertyPathDisplayName(const FPropertyBindingPath& InPath, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const = 0;` — @return Display name given property path.
- L415 _public prototype_ `virtual const FProperty* GetPropertyPathLeafProperty(const FPropertyBindingPath& InPath) const = 0;` — @return Leaf property based on property path.
- L418 _public prototype_ `virtual FText GetBindingSourceDisplayName(const FPropertyBindingPath& InTargetPath, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const = 0;` — @return Display name of binding source, or empty if binding does not exists.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API STATETREEMODULE_API`
- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace StateTree` (scope `UE`)
- L57 _prototype_ `[[nodiscard]] bool AcceptTaskInstanceData(EStateTreeBindableStructSource Target);` (scope `UE::StateTree`) — Can that binding type accept a task instance data for a source.
- L248 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonab5a3fc80103`)
- L422 _namespace_ `namespace UE`
- L422 _namespace_ `namespace StateTree` (scope `UE`)
- L425 _prototype_ `extern FString GetDescAndPathAsString(const FStateTreeBindableStructDesc& Desc, const FPropertyBindingPath& Path);` (scope `UE::StateTree`) — @return desc and path as a display string.
- L433 _prototype_ `EStateTreePropertyUsage GetUsageFromMetaData(const FProperty* Property);` (scope `UE::StateTree`) — Returns property usage based on the Category metadata of given property. @param Property Handle to property where value is got from. @return found usage type, or EStateTreePropertyUsage::Invalid if not found.
- L436 _prototype_ `const FProperty* GetStructSingleOutputProperty(const UStruct& InStruct);` (scope `UE::StateTree`) — @return struct's property which is the only one marked as Output. Returns null otherwise.

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreePropertyFunctionBase.h` (Public)


#### struct `FStateTreePropertyFunctionBase`  
`struct FStateTreePropertyFunctionBase : public FStateTreeNodeBase`  
_L40-58_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeNodeBase`
- desc: Base struct for all property functions. PropertyFunction is a node which is executed just before evaluating owner's bindings. The property function's instance data is expected to have one property marked as output. This property is used to find which properties the function can be used for, and that property is hidden in the UI. It is expected that there's just one output property. Example: USTRUCT() struct FStateTreeBooleanOperationPropertyFunctionInstanceData { GENERATED_BODY() UPROPERTY(EditAnywhere, Category = Param) bool bLeft = false; UPROPERTY(EditAnywhere, Category = Param) bool bRight = false; // This property is used to find which properties the function can be used for. UPROPERTY(EditAnywhere, Category = Output) bool bResult = false; };
- L48 _public function_ `virtual void Execute(FStateTreeExecutionContext& Context) const` — Called right before evaluating bindings for the owning node. @param Context Reference to current execution context.
- L51 _public function_ `virtual FName GetIconName() const override`
- L56 _public prototype_ `virtual FColor GetIconColor() const override;`

#### struct `FStateTreePropertyFunctionCommonBase`  
`struct FStateTreePropertyFunctionCommonBase : public FStateTreePropertyFunctionBase`  
_L61-64_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreePropertyFunctionBase`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreePropertyRef.h` (Public)


#### struct `UE::StateTree::PropertyRefHelpers::Private::FResolvePropertyReferenceIndirectionsResult`  
`struct FResolvePropertyReferenceIndirectionsResult`  
_L20-25_
- L22 _public member_ `FStateTreeDataView SourceView;`
- L23 _public member_ `const FStateTreePropertyAccess* PropertyAccess = nullptr;`
- L24 _public member_ `const FStateTreePropertyBindings* PropertyBindings = nullptr;`

#### struct `FStateTreePropertyRef`  
`struct FStateTreePropertyRef`  
_L136-219_
- reflection: `USTRUCT()`
- desc: Property ref allows to get a pointer to selected property in StateTree. The expected type of the reference should be set in "RefType" meta specifier. PropertyRef is recommended to be used to avoid copying large struct. Otherwise, Output Binding offers a simpler workflow and designers can author the write-back inside Editor. Meta specifiers for the type: - RefType = "<type>" - Specifies a comma separated list of type of property to reference - Supported types are: bool, byte, int32, int64, float, double, Name, String, Text, UObject pointers, and structs - Structs and Objects must use full path name - If multiple types are specified, GetMutablePtrTuple can be used to access the correct type - IsRefToArray - If specified, the reference is to an TArray<RefType> - CanRefToArray - If specified, the reference can bind to a Reftype or TArray<RefType> - Optional - If specified, the reference can be left unbound, otherwise the compiler report error if the reference is not bound Example: // Reference to float UPROPERTY(EditAnywhere, meta = (RefType = "float")) FStateTreePropertyRef RefToFloat; // Reference to FTestStructBase UPROPERTY(EditAnywhere, meta = (RefType = "/Script/ModuleName.TestStructBase")) FStateTreePropertyRef RefToTest; // Reference to TArray<FTestStructBase> UPROPERTY(EditAnywhere, meta = (RefType = "/Script/ModuleName.TestStructBase", IsRefToArray)) FStateTreePropertyRef RefToArrayOfTests; // Reference to Vector, TArray<FVector>, AActor*, TArray<AActor*> UPROPERTY(Edit
- L140 _public prototype_ `FStateTreePropertyRef() = default;`
- L144 _public function_ `template <class T> T* GetMutablePtr(const FStateTreeExecutionContext& Context) const` — @return pointer to the property if possible, nullptr otherwise.
- L154 _public function_ `template<class T, bool bWithWriteAccess> std::conditional_t<bWithWriteAccess, T*, const T*> GetPtrFromStrongExecutionContext(const TStateTreeStrongExecutionContext<bWithWriteAccess>& Context)` — @return pointer to the property if possible, nullptr otherwise.
- L167 _public function_ `template <class... T> TTuple<T*...> GetMutablePtrTuple(const FStateTreeExecutionContext& Context) const` — @return a tuple of pointers of the given types to the property if possible, nullptr otherwise.
- L177 _public function_ `template <class... T, bool bWithWriteAccess> std::conditional_t<bWithWriteAccess, TTuple<T*...>, TTuple<const T*...>> GetPtrTupleFromStrongExecutionContext(const TStateTreeStrongExecutionContext<bWithWriteAccess>& Context) const` — @return a tuple of pointers of the given types to the property if possible, nullptr otherwise.
- L192 _public function_ `FStateTreeIndex16 GetRefAccessIndex() const` — Used internally. @return index to referenced property access
- L198 _public function_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot)`
- L216 _private member_ `FStateTreeIndex16 RefAccessIndex;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FStateTreePropertyRef> : public TStructOpsTypeTraitsBase2<FStateTreePropertyRef>`  
_L222-228_
- inherits: `TStructOpsTypeTraitsBase2<FStateTreePropertyRef>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L225-227_

#### struct `TStateTreePropertyRef`  
`template <class TRef> struct TStateTreePropertyRef`  
_L253-292_
- desc: TStateTreePropertyRef is a type-safe FStateTreePropertyRef wrapper against a single given type. @note When used as a property, this automatically defines PropertyRef property meta-data. Example: // Reference to float UPROPERTY(EditAnywhere) TStateTreePropertyRef<float> RefToFloat; // Reference to FTestStructBase UPROPERTY(EditAnywhere) TStateTreePropertyRef<FTestStructBase> RefToTest; // Reference to TArray<FTestStructBase> UPROPERTY(EditAnywhere) TStateTreePropertyRef<TArray<FTestStructBase>> RefToArrayOfTests; // Reference to FTestStructBase or TArray<FTestStructBase> UPROPERTY(EditAnywhere, meta = (CanRefToArray)) TStateTreePropertyRef<FTestStructBase> RefToSingleOrArrayOfTests;
- L256 _public function_ `TRef* GetMutablePtr(const FStateTreeExecutionContext& Context) const` — @return pointer to the property if possible, nullptr otherwise.
- L263 _public function_ `template<bool bWithWriteAccess> std::conditional_t<bWithWriteAccess, TRef*, const TRef*> GetPtrFromStrongExecutionContext(const TStateTreeStrongExecutionContext<bWithWriteAccess>& Context)` — @return pointer to the property if possible, nullptr otherwise.
- L269 _public function_ `TTuple<TRef*, TArray<TRef>*> GetMutablePtrTuple(const FStateTreeExecutionContext& Context) const` — @return a tuple of pointer to the property of the type or array of type, nullptr otherwise.
- L276 _public function_ `template <bool bWithWriteAccess> std::conditional_t<bWithWriteAccess, TTuple<TRef*, TArray<TRef>*>, TTuple<const TRef*, const TArray<TRef>*>> GetPtrTupleFromStrongExecutionContext(const TStateTreeStrongExecutionContext<bWithWriteAccess>& Context) const` — @return a tuple of pointers of the given types to the property if possible, nullptr otherwise.
- L285 _public function_ `FStateTreePropertyRef GetInternalPropertyRef() const` — Used internally. @return internal property ref
- L291 _private member_ `FStateTreePropertyRef PropertyRef;`

#### struct `FStateTreePropertyRefExternalHandle`  
`struct UE_DEPRECATED(5.8, "PropertyRefExternalHandle is deprecated. Use PropertyRef with ExecutionContext/StrongExecutionContext instead, which is a general async pattern for data access using Frame/StateID.") FStateTreePropertyRefExternalHandle`  
_L295-339_
- L297 _public function_ `FStateTreePropertyRefExternalHandle(FStateTreePropertyRef InPropertyRef, FStateTreeExecutionContext& InContext) : WeakInstanceStorage(InContext.GetMutableInstanceData()->GetWeakMutableStorage()) , WeakStateTree(InContext.GetCurrentlyProcessedFrame()->StateTree) , RootState(InContext.GetCurrentlyProcessedFrame()->RootState) , PropertyRef(InPropertyRef)`
- L307 _public function_ `template <class TRef> TRef* GetMutablePtr() const` — @return pointer to the property if possible, nullptr otherwise.
- L314 _public function_ `template <class... TRef> TTuple<TRef*...> GetMutablePtrTuple() const` — @return a tuple of pointers of the given types to the property if possible, nullptr otherwise.
- L335 _protected member_ `TWeakPtr<FStateTreeInstanceStorage> WeakInstanceStorage;`
- L336 _protected member_ `TWeakObjectPtr<const UStateTree> WeakStateTree = nullptr;`
- L337 _protected member_ `FStateTreeStateHandle RootState = FStateTreeStateHandle::Invalid;`
- L338 _protected member_ `FStateTreePropertyRef PropertyRef;`

#### struct `TStateTreePropertyRefExternalHandle`  
`template <class TRef> struct UE_DEPRECATED(5.8, "PropertyRefExternalHandle is deprecated. Use PropertyRef with ExecutionContext/StrongExecutionContext instead, which is a general async pattern for data access using Frame/StateID.") TStateTreePropertyRefExternalHandle : public FStateTreePropertyRefExternalHandle`  
_L342-365_
- inherits: `FStateTreePropertyRefExternalHandle`
- L345 _public function_ `TStateTreePropertyRefExternalHandle(TStateTreePropertyRef<TRef> InPropertyRef, FStateTreeExecutionContext& InContext) : FStateTreePropertyRefExternalHandle(InPropertyRef.GetInternalPropertyRef(), InContext)`
- L351 _public function_ `TRef* GetMutablePtr() const` — @return pointer to the property if possible, nullptr otherwise.
- L357 _public function_ `TTuple<TRef*, TArray<TRef>*> GetMutablePtrTuple() const` — @return a tuple of pointer to the property of the type or array of type, nullptr otherwise.

#### enum `EStateTreePropertyRefType`  
`enum class EStateTreePropertyRefType : uint8`  
_L369-387_
- reflection: `UENUM()`
- L371 _public enumerator_ `None`
- L372 _public enumerator_ `Bool`
- L373 _public enumerator_ `Byte`
- L374 _public enumerator_ `Int32`
- L375 _public enumerator_ `Int64`
- L376 _public enumerator_ `Float`
- L377 _public enumerator_ `Double`
- L378 _public enumerator_ `Name`
- L379 _public enumerator_ `String`
- L380 _public enumerator_ `Text`
- L381 _public enumerator_ `Enum`
- L382 _public enumerator_ `Struct`
- L383 _public enumerator_ `Object`
- L384 _public enumerator_ `SoftObject`
- L385 _public enumerator_ `Class`
- L386 _public enumerator_ `SoftClass`

#### struct `FStateTreeBlueprintPropertyRef`  
`struct FStateTreeBlueprintPropertyRef : public FStateTreePropertyRef`  
_L393-429_
- reflection: `USTRUCT(BlueprintType, DisplayName = "State Tree Property Ref")`
- inherits: `FStateTreePropertyRef`
- desc: FStateTreeBlueprintPropertyRef is a PropertyRef intended to be used in State Tree Blueprint nodes like tasks, conditions or evaluators, but also as a StateTree parameter.
- L397 _public prototype_ `FStateTreeBlueprintPropertyRef() = default;`
- L400 _public function_ `EStateTreePropertyRefType GetRefType() const` — Returns PropertyRef's type
- L403 _public function_ `bool IsRefToArray() const` — Returns true if referenced property is an array.
- L406 _public function_ `UObject* GetTypeObject() const` — Returns selected ScriptStruct, Class or Enum.
- L409 _public function_ `bool IsOptional() const` — Returns true if PropertyRef was marked as optional.
- L414 _private member_ `EStateTreePropertyRefType RefType = EStateTreePropertyRefType::None;` — `UPROPERTY(EditAnywhere, Category = "InternalType")` — Specifies the type of property to reference
- L418 _private member_ `uint8 bIsRefToArray : 1 = false;` — `UPROPERTY(EditAnywhere, Category = "InternalType")` — If specified, the reference is to an TArray<RefType>
- L422 _private member_ `uint8 bIsOptional : 1 = false;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — If specified, the reference can be left unbound, otherwise the State Tree compiler report error if the reference is not bound.
- L426 _private member_ `TObjectPtr<UObject> TypeObject = nullptr;` — `UPROPERTY(EditAnywhere, Category= "InternalType")` — Specifies the type of property to reference together with RefType, used for Enums, Structs, Objects and Classes.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API STATETREEMODULE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace StateTree` (scope `UE`)
- L16 _namespace_ `namespace PropertyRefHelpers` (scope `UE::StateTree`)
- L18 _namespace_ `namespace Private` (scope `UE::StateTree::PropertyRefHelpers`)
- L26 _prototype_ `TOptional<FResolvePropertyReferenceIndirectionsResult> ResolvePropertyReferenceIndirections( const FStateTreePropertyRef& InPropertyRef, FStateTreeInstanceStorage& InInstanceDataStorage, const ExecutionContext::ITemporaryStorage* InTemporaryStorage, const FStateTreeExecutionFrame& InExecutionFrame);` (scope `UE::StateTree::PropertyRefHelpers::Private`)
- L35 _function_ `T* GetMutablePtrToProperty(const FStateTreePropertyRef& PropertyRef, FStateTreeInstanceStorage& InstanceDataStorage, const FStateTreeExecutionFrame& ExecutionFrame, const FStateTreeExecutionFrame* ParentExecutionFrame, const FProperty** OutSourceProperty = nullptr)` (scope `UE::StateTree::PropertyRefHelpers`) — `UE_DEPRECATED(5.8, "Use the version with TemporaryStorage instead of ParentFrame")`
- L50 _function_ `template <class T> T* GetMutablePtrToProperty(const FStateTreePropertyRef& InPropertyRef, FStateTreeInstanceStorage& InInstanceDataStorage, const ExecutionContext::ITemporaryStorage* InTemporaryStorage, const FStateTreeExecutionFrame& InExecutionFrame, const FProperty** OutSourceProperty = nullptr)` (scope `UE::StateTree::PropertyRefHelpers`) — @param InPropertyRef Property's reference to get pointer to. @param InInstanceDataStorage Instance Data Storage. @param InTemporaryStorage Temporary Data Storage. @param InExecutionFrame Execution frame owning referenced property. @param OutSourceProperty On success, returns referenced property. @return Pointer to referenced property value if succeeded.
- L71 _function_ `TTuple<T*...> GetMutablePtrTupleToProperty(const FStateTreePropertyRef& PropertyRef, FStateTreeInstanceStorage& InstanceDataStorage, const FStateTreeExecutionFrame& ExecutionFrame, const FStateTreeExecutionFrame* ParentExecutionFrame)` (scope `UE::StateTree::PropertyRefHelpers`) — `UE_DEPRECATED(5.8, "Use the version with ITemporaryStorage instead of ParentFrame")`
- L85 _function_ `template <class... T> TTuple<T*...> GetMutablePtrTupleToProperty(const FStateTreePropertyRef& InPropertyRef, FStateTreeInstanceStorage& InInstanceDataStorage, const ExecutionContext::ITemporaryStorage* InTemporaryStorage, const FStateTreeExecutionFrame& InExecutionFrame)` (scope `UE::StateTree::PropertyRefHelpers`) — @param InPropertyRef Property's reference to get pointer to. @param InInstanceDataStorage Instance Data Storage @param InTemporaryStorage Temporary Data Storage @param InExecutionFrame Execution frame owning referenced property @return A tuple of pointer to referenced property if succeeded.
- L226 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon255435170103`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreePropertyRefHelpers.h` (Public)


#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<class T, class = void> struct Validator`  
_L105-106_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<> struct Validator<void>`  
_L109-112_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<> struct Validator<FBoolProperty::TCppType>`  
_L115-118_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<> struct Validator<FByteProperty::TCppType>`  
_L121-124_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<> struct Validator<FIntProperty::TCppType>`  
_L127-130_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<> struct Validator<FInt64Property::TCppType>`  
_L133-136_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<> struct Validator<FFloatProperty::TCppType>`  
_L139-142_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<> struct Validator<FDoubleProperty::TCppType>`  
_L145-148_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<> struct Validator<FNameProperty::TCppType>`  
_L151-154_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<> struct Validator<FStrProperty::TCppType>`  
_L157-160_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<> struct Validator<FTextProperty::TCppType>`  
_L163-166_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<class T> struct Validator<T, typename TEnableIf<TIsTArray_V<T>, void>::Type>`  
_L169-180_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<typename T> struct Validator<TEnumAsByte<T>>`  
_L183-189_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<class T> struct Validator<T, decltype(TBaseStructure<T>::Get, void())>`  
_L195-206_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<class T> struct Validator<T, typename TEnableIf<TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>::IsDerived>::Type>`  
_L212-223_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### struct `UE::StateTree::PropertyRefHelpers::Validator`  
`template<class T> struct Validator<T, typename TEnableIf<TIsEnum<T>::Value>::Type>`  
_L229-240_
- L111 _public function_ `static bool IsValid(const FProperty& Property)`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace StateTree` (scope `UE`)
- L23 _namespace_ `namespace PropertyRefHelpers` (scope `UE::StateTree`)
- L26 _externvar_ `extern const FName IsRefToArrayName;` (scope `UE::StateTree::PropertyRefHelpers`)
- L27 _externvar_ `extern const FName CanRefToArrayName;` (scope `UE::StateTree::PropertyRefHelpers`)
- L28 _externvar_ `extern const FName RefTypeName;` (scope `UE::StateTree::PropertyRefHelpers`)
- L36 _prototype_ `bool IsPropertyRefCompatibleWithProperty(const FProperty& RefProperty, const FProperty& SourceProperty, const void* PropertyRefAddress, const void* SourceAddress);` (scope `UE::StateTree::PropertyRefHelpers`) — @param RefProperty Property of PropertyRef type. @param SourceProperty Property to check its type compatibility. @param PropertyRefAddress Address of PropertyRef @param SourceAddress Address of checked property value. @return true if SourceProperty type is compatible with PropertyRef.
- L43 _prototype_ `bool IsPropertyAccessibleForPropertyRef(TConstArrayView<FPropertyBindingPathIndirection> SourcePropertyPathIndirections, FStateTreeBindableStructDesc SourceStruct);` (scope `UE::StateTree::PropertyRefHelpers`) — @param SourcePropertyPathIndirections Path indirections of the referenced property. @param SourceStruct Bindable owner of referenced property. @return true if property can be referenced by PropertyRef.
- L46 _prototype_ `bool IsPropertyAccessibleForPropertyRef(TConstArrayView<FStateTreePropertyPathIndirection> SourcePropertyPathIndirections, FStateTreeBindableStructDesc SourceStruct);` (scope `UE::StateTree::PropertyRefHelpers`) — `UE_DEPRECATED(5.6, "Use the overload taking FPropertyBindingPathIndirection instead")`
- L54 _prototype_ `bool IsPropertyAccessibleForPropertyRef(const FProperty& SourceProperty, TConstArrayView<FBindingChainElement> BindingChain, FStateTreeBindableStructDesc SourceStruct);` (scope `UE::StateTree::PropertyRefHelpers`) — @param SourceProperty Referenced property. @param BindingChain Binding chain to referenced property. @param SourceStruct Bindable owner of referenced property. @return true if property can be referenced by PropertyRef.
- L61 _prototype_ `bool IsPropertyRefMarkedAsOptional(const FProperty& RefProperty, const void* PropertyRefAddress);` (scope `UE::StateTree::PropertyRefHelpers`) — @param RefProperty Property of PropertyRef type. @param PropertyRefAddress Address of PropertyRef. @return true if PropertyRef is marked as optional.
- L67 _prototype_ `TArray<FEdGraphPinType, TInlineAllocator<1>> GetPropertyRefInternalTypesAsPins(const FProperty& RefProperty);` (scope `UE::StateTree::PropertyRefHelpers`) — @param RefProperty Property of PropertyRef type @return PinTypes for PropertyRef's internal types
- L74 _prototype_ `FEdGraphPinType GetPropertyRefInternalTypeAsPin(const FProperty& RefProperty, const void* PropertyRefAddress);` (scope `UE::StateTree::PropertyRefHelpers`) — @param RefProperty Property of PropertyRef type @param PropertyRefAddress Address of PropertyRef. @return PinType for PropertyRef's internal type
- L80 _prototype_ `FEdGraphPinType GetBlueprintPropertyRefInternalTypeAsPin(const FStateTreeBlueprintPropertyRef& InPropertyRef);` (scope `UE::StateTree::PropertyRefHelpers`) — @param InPropertyRef PropertyRef to get internal type from. @return PinType for Blueprint PropertyRef's internal type
- L88 _prototype_ `void GetBlueprintPropertyRefInternalTypeFromPin(const FEdGraphPinType& PinType, EStateTreePropertyRefType& OutRefType, bool& bOutIsArray, UObject*& OutObjectType);` (scope `UE::StateTree::PropertyRefHelpers`) — @param PinType Pin to get type from. @param OutRefType PropertyRef's referenced type. @param bOutIsArray True if PropertyRef references an array property. @param OutObjectType Referenced type's specific object.
- L95 _prototype_ `bool IsPropertyRef(const FProperty& Property);` (scope `UE::StateTree::PropertyRefHelpers`) — @param Property Property to check @return true if Property is a PropertyRef
- L102 _prototype_ `bool IsBlueprintPropertyRefCompatibleWithProperty(const FProperty& SourceProperty, const void* PropertyRefAddress);` (scope `UE::StateTree::PropertyRefHelpers`) — @param SourceProperty Property to check it's type compatibility. @param PropertyRefAddress Address of PropertyRef @return true if SourceProperty type is compatible with Blueprint PropertyRef.
- L192 _prototype_ `bool IsPropertyCompatibleWithStruct(const FProperty& Property, const class UScriptStruct& Struct);` (scope `UE::StateTree::PropertyRefHelpers`) — Checks if provided property is compatible with selected ScriptStruct.
- L209 _prototype_ `bool IsPropertyCompatibleWithClass(const FProperty& Property, const class UClass& Class);` (scope `UE::StateTree::PropertyRefHelpers`) — Checks if provided property is compatible with selected Class.
- L226 _prototype_ `bool IsPropertyCompatibleWithEnum(const FProperty& Property, const class UEnum& Enum);` (scope `UE::StateTree::PropertyRefHelpers`) — Checks if provided property is compatible with selected Enum.

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeReference.h` (Public)


#### struct `FStateTreeReference`  
`struct FStateTreeReference`  
_L17-112_
- reflection: `USTRUCT(BlueprintType, meta = (DisableSplitPin, HasNativeMake = "/Script/StateTreeModule.StateTreeFunctionLibrary.MakeStateTreeReference"))`
- desc: Struct to hold reference to a StateTree asset along with values to parameterized it.
- L22 _public function_ `bool IsValid() const` — @return true if the reference is set.
- L28 _public function_ `void SetStateTree(UStateTree* NewStateTree)` — Sets the StateTree asset and referenced parameters.
- L35 _public function_ `const UStateTree* GetStateTree() const` — @return const pointer to the referenced StateTree asset.
- L41 _public function_ `UStateTree* GetMutableStateTree()` — @return pointer to the referenced StateTree asset.
- L47 _public function_ `FConstStructView GetGlobalParameters() const` — @return the parameters for the referenced StateTree asset.
- L54 _public function_ `FStructView GetMutableGlobalParameters()` — @return the parameters for the referenced StateTree asset.
- L61 _public function_ `const FInstancedPropertyBag& GetParameters() const` — @return reference to the parameters for the referenced StateTree asset.
- L68 _public function_ `FInstancedPropertyBag& GetMutableParameters()` — @return reference to the parameters for the referenced StateTree asset.
- L77 _public prototype_ `void SyncParameters();` — Enforce self parameters to be compatible with those exposed by the selected StateTree asset.
- L83 _public prototype_ `bool RequiresParametersSync() const;` — Indicates if current parameters are compatible with those available in the selected StateTree asset. @return true when parameters requires to be synced to be compatible with those available in the selected StateTree asset, false otherwise.
- L86 _public prototype_ `void ConditionallySyncParameters() const;` — Sync parameters to match the asset if required.
- L89 _public function_ `bool IsPropertyOverridden(const FGuid PropertyID) const` — @return true if the property of specified ID is overridden.
- L95 _public prototype_ `void SetPropertyOverridden(const FGuid PropertyID, const bool bIsOverridden);` — Sets the override status of specified property by ID.
- L97 _public prototype_ `bool Serialize(FStructuredArchive::FSlot Slot);`
- L98 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L102 _protected member_ `TObjectPtr<UStateTree> StateTree = nullptr;` — `UPROPERTY(EditAnywhere, Category = "StateTree")`
- L105 _protected member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY(EditAnywhere, Category = "StateTree", meta = (FixedLayout))`
- L109 _protected member_ `TArray<FGuid> PropertyOverrides;` — `UPROPERTY(EditAnywhere, Category = "StateTree")` — Array of overridden properties. Non-overridden properties will inherit the values from the StateTree default parameters.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FStateTreeReference> : public TStructOpsTypeTraitsBase2<FStateTreeReference>`  
_L115-122_
- inherits: `TStructOpsTypeTraitsBase2<FStateTreeReference>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L118-121_

#### struct `FStateTreeReferenceOverrideItem`  
`struct FStateTreeReferenceOverrideItem`  
_L129-170_
- reflection: `USTRUCT()`
- desc: Item describing a state tree override for a state with a specific tag.
- L133 _public prototype_ `FStateTreeReferenceOverrideItem() = default;`
- L134 _public function_ `FStateTreeReferenceOverrideItem(const FGameplayTag InStateTag, const FStateTreeReference& InStateTreeReference) : StateTag(InStateTag) , StateTreeReference(InStateTreeReference)`
- L139 _public function_ `FStateTreeReferenceOverrideItem(const FGameplayTag InStateTag, FStateTreeReference&& InStateTreeReference) : StateTag(InStateTag) , StateTreeReference(MoveTemp(InStateTreeReference))`
- L145 _public function_ `FGameplayTag GetStateTag() const`
- L150 _public function_ `const FStateTreeReference& GetStateTreeReference() const`
- L163 _private member_ `FGameplayTag StateTag;` — `UPROPERTY(EditAnywhere, Category = "StateTree")` — Exact tag used to match against a tag on a linked State Tree state.
- L167 _private member_ `FStateTreeReference StateTreeReference;` — `UPROPERTY(EditAnywhere, Category = "StateTree", DisplayName = "State Tree", meta=(SchemaCanBeOverriden))` — State Tree and parameters to replace the linked state asset with.

#### struct `FStateTreeReferenceOverrides`  
`struct FStateTreeReferenceOverrides`  
_L177-255_
- reflection: `USTRUCT()`
- desc: Overrides for linked State Trees. This table is used to override State Tree references on linked states. If a linked state's tag is exact match of the tag specified on the table, the reference from the table is used instead.
- L182 _public function_ `void Reset()` — Removes all overrides.
- L188 _public function_ `void AddOverride(const FGameplayTag StateTag, const FStateTreeReference& StateTreeReference)` — Adds or replaces override for a selected tag.
- L206 _public function_ `void AddOverride(FStateTreeReferenceOverrideItem OverrideItem)` — Adds or replaces override for a selected tag.
- L224 _public function_ `bool RemoveOverride(const FGameplayTag StateTag)` — Returns true if removing an override succeeded.
- L240 _public function_ `TConstArrayView<FStateTreeReferenceOverrideItem> GetOverrideItems() const`
- L252 _private member_ `TArray<FStateTreeReferenceOverrideItem> OverrideItems;` — `UPROPERTY(EditAnywhere, Category = "StateTree")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATETREEMODULE_API`
- L119 _enumerator_ `WithStructuredSerializer = true` (scope `TStructOpsTypeTraits::__anon162d23a40103`)
- L120 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon162d23a40103`)
- L155 _function_ `friend uint32 GetTypeHash(const FStateTreeReferenceOverrideItem& Item)`
- L191 _function_ `` (scope `FStateTreeReferenceOverrides::AddOverride`)
- L227 _function_ `` (scope `FStateTreeReferenceOverrides::RemoveOverride`)
- L245 _function_ `friend uint32 GetTypeHash(const FStateTreeReferenceOverrides& Overrides)`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeSchema.h` (Public)


#### class `UStateTreeSchema`  
`class UStateTreeSchema : public UObject`  
_L29-139_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Schema describing which inputs, evaluators, and tasks a StateTree can contain. Each StateTree asset saves the schema class name in asset data tags, which can be used to limit which StatTree assets can be selected per use case, i.e.: UPROPERTY(EditDefaultsOnly, Category = AI, meta=(RequiredAssetDataTags="Schema=StateTreeSchema_SupaDupa")) UStateTree* StateTree;
- L36 _public function_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const` — @return True if specified struct is supported
- L42 _public function_ `virtual bool IsClassAllowed(const UClass* InScriptStruct) const` — @return True if specified class is supported
- L48 _public function_ `virtual bool IsExternalItemAllowed(const UStruct& InStruct) const` — @return True if specified struct/class is supported as external data
- L54 _public function_ `virtual bool IsScheduledTickAllowed() const` — @return True if the execution context can sleep or the next tick delayed.
- L60 _public function_ `virtual bool IsStateSelectionAllowed(EStateTreeStateSelectionBehavior InBehavior) const` — @return True if the state selection behavior is supported.
- L66 _public function_ `virtual bool IsStateTypeAllowed(EStateTreeStateType InStateType) const` — @return True if the state type is supported.
- L76 _public prototype_ `static bool IsChildOfBlueprintBase(const UClass* InClass);` — Helper function to check if a class is any of the Blueprint extendable item classes (Eval, Task, Condition). Can be used to quickly accept all of those classes in IsClassAllowed(). @return True if the class is a StateTree item Blueprint base class.
- L79 _public function_ `virtual TConstArrayView<FStateTreeExternalDataDesc> GetContextDataDescs() const` — @return List of context objects (UObjects or UScriptStructs) enforced by the schema. They must be provided at runtime through the execution context.
- L85 _public prototype_ `virtual EStateTreeParameterDataType GetGlobalParameterDataType() const;` — @return the global parameter type used by the schema.
- L88 _public prototype_ `virtual EStateTreeStateSelectionRules GetStateSelectionRules() const;` — @return the selection rules used by the schema.
- L91 _public function_ `virtual bool Link(FStateTreeLinker& Linker)` — Resolves schema references to other StateTree data.
- L98 _public function_ `virtual bool AllowEnterConditions() const` — @return True if enter conditions are allowed.
- L104 _public function_ `virtual bool AllowUtilityConsiderations() const` — @return True if utility considerations are allowed.
- L110 _public function_ `virtual bool AllowEvaluators() const` — @return True if evaluators are allowed.
- L116 _public function_ `virtual bool AllowMultipleTasks() const` — @return True if multiple tasks are allowed.
- L122 _public function_ `virtual bool AllowGlobalParameters() const` — @return True if global parameters for the State Tree are allowed.
- L128 _public function_ `virtual bool AllowTasksCompletion() const` — @return True if modifying the tasks completion is allowed. If not allowed, "any" will be used.
- L134 _public function_ `virtual bool AllowQueuedCompilation() const` — @return Whether the compilation of the state tree is allowed to be queued.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeSettings.h` (Public)


#### class `UStateTreeSettings`  
`class UStateTreeSettings : public UDeveloperSettings`  
_L12-26_
- reflection: `UCLASS(MinimalAPI, config = StateTree, defaultconfig, DisplayName = "StateTree")`
- inherits: `UDeveloperSettings`
- desc: Default StateTree settings
- L17 _public function_ `static UStateTreeSettings& Get()`
- L25 _public member_ `bool bAutoStartDebuggerTracesOnNonEditorTargets = false;` — `UPROPERTY(EditDefaultsOnly, Category = StateTree, config)` — Editor targets relies on PIE and StateTreeEditor to start/stop traces. This is to start traces automatically when launching Standalone, Client or Server builds. It's also possible to do it manually using 'statetree.startdebuggertraces' and 'statetree.stopdebuggertraces' in the console.

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeStatePath.h` (Public)


#### struct `UE::StateTree::FActiveFrameID`  
`struct FActiveFrameID`  
_L17-42_
- desc: A unique ID for FStateTreeExecutionFrame.
- L20 _private member_ `static constexpr uint32 InvalidValue = 0;`
- L23 _public member_ `static const FActiveFrameID Invalid;`
- L25 _public prototype_ `explicit FActiveFrameID() = default;`
- L26 _public function_ `explicit FActiveFrameID(uint32 NewID) : Value(NewID)`
- L32 _public prototype_ `[[nodiscard]] bool operator==(const FActiveFrameID&) const = default;`
- L33 _public prototype_ `[[nodiscard]] bool operator!=(const FActiveFrameID&) const = default;`
- L35 _public function_ `[[nodiscard]] bool IsValid() const`
- L41 _private member_ `uint32 Value = InvalidValue;`

#### struct `UE::StateTree::FActiveStateID`  
`struct FActiveStateID`  
_L45-70_
- desc: A unique ID for FStateTreeActiveStates state.
- L48 _private member_ `static constexpr uint32 InvalidValue = 0;`
- L51 _public member_ `static const FActiveStateID Invalid;`
- L53 _public prototype_ `explicit FActiveStateID() = default;`
- L54 _public function_ `explicit FActiveStateID(uint32 NewID) : Value(NewID)`
- L60 _public prototype_ `[[nodiscard]] bool operator==(const FActiveStateID&) const = default;`
- L61 _public prototype_ `[[nodiscard]] bool operator!=(const FActiveStateID&) const = default;`
- L63 _public function_ `[[nodiscard]] bool IsValid() const`
- L69 _private member_ `uint32 Value = InvalidValue;`

#### struct `UE::StateTree::FActiveState`  
`struct FActiveState`  
_L73-108_
- desc: A state entry in the state path.
- L75 _public prototype_ `FActiveState() = default;`
- L76 _public prototype_ `inline explicit FActiveState(FActiveFrameID InFrameID, FActiveStateID InStateID, FStateTreeStateHandle InHandle);`
- L78 _public prototype_ `[[nodiscard]] bool operator==(const FActiveState&) const = default;`
- L79 _public prototype_ `[[nodiscard]] bool operator!=(const FActiveState&) const = default;`
- L81 _public function_ `[[nodiscard]] bool IsValid() const`
- L86 _public function_ `[[nodiscard]] FActiveFrameID GetFrameID() const`
- L91 _public function_ `[[nodiscard]] FActiveStateID GetStateID() const`
- L96 _public function_ `[[nodiscard]] FStateTreeStateHandle GetStateHandle() const`
- L103 _private member_ `FActiveFrameID FrameID;` — The unique ID of the state for this instance.
- L105 _private member_ `FActiveStateID StateID;` — The unique ID of the state for this instance.
- L107 _private member_ `FStateTreeStateHandle StateHandle;` — The index of the state handle the state tree asset.
- L210 _function_ `FActiveState::FActiveState(FActiveFrameID InFrameID, FActiveStateID InStateID, FStateTreeStateHandle InHandle) : FrameID(InFrameID) , StateID(InStateID) , StateHandle(InHandle)` — Inlined functions

#### class `UE::StateTree::FActiveStatePath`  
`class FActiveStatePath`  
_L125-207_
- desc: Describe the state list used to get to a specific state. Since a state can be a subtree and can be linked to other states, the path to activate the subtree can be different. A state can enter, then exit, then reenter. It is considered the same state path but not the same unique state path. For a tree like RootA(0) StateA(1) StateB(2) LinkedStateA(3) StateC(4) LinkedStateA(5) SubTreeA(6) StateD(7) The path to get to StateD can be RootA.StateB.LinkedStateA.SubTreeA.StateD(0.2.3.6.7)
- L128 _public prototype_ `explicit FActiveStatePath() = default;`
- L129 _public prototype_ `explicit FActiveStatePath(TNotNull<const UStateTree*> InStateTree, const TArrayView<const FActiveState> InElements);`
- L130 _public prototype_ `explicit FActiveStatePath(TNotNull<const UStateTree*> InStateTree, TArray<FActiveState> InElements);`
- L133 _public function_ `[[nodiscard]] int32 Num() const` — @return the number of elements in the path.
- L139 _public function_ `[[nodiscard]] const TArrayView<const FActiveState> GetView() const` — @return a view of the states in the path.
- L145 _public prototype_ `[[nodiscard]] static bool Matches(const TArrayView<const FActiveState>& A, const TArrayView<const FActiveState>& B);` — @return true if both paths match exactly.
- L148 _public prototype_ `[[nodiscard]] bool Matches(const FActiveStatePath& Other) const;` — @return true if both paths match exactly.
- L151 _public prototype_ `[[nodiscard]] static bool Matches(const TArrayView<const FActiveState>& Path, FActiveState Other);` — @return true if the last element in the path matches.
- L154 _public prototype_ `[[nodiscard]] bool Matches(FActiveState Other) const;` — @return true if the last element in the path matches.
- L157 _public prototype_ `[[nodiscard]] static bool Matches(const TArrayView<const FActiveState>& Path, FActiveStateID Other);` — @return true if the last element in the path matches.
- L160 _public prototype_ `[[nodiscard]] bool Matches(FActiveStateID Other) const;` — @return true if the last element in the path matches.
- L163 _public prototype_ `[[nodiscard]] static const TArrayView<const FActiveState> Intersect(const TArrayView<const FActiveState>& A, const TArrayView<const FActiveState>& B);` — @return the elements that are in both paths.
- L166 _public prototype_ `[[nodiscard]] const TArrayView<const FActiveState> Intersect(const FActiveStatePath& Other) const;` — @return the path where the 2 paths intersect.
- L169 _public prototype_ `[[nodiscard]]static bool StartsWith(const TArrayView<const FActiveState>& Path, const TArrayView<const FActiveState>& B);` — @return true if the path starts with and contains the other path.
- L172 _public prototype_ `[[nodiscard]] bool StartsWith(const FActiveStatePath& Other) const;` — @return true if this path starts with and contains the other path.
- L175 _public prototype_ `[[nodiscard]] static bool Contains(const TArrayView<const FActiveState>& Path, FActiveState Other);` — @return true if the path contains anywhere the other element.
- L178 _public prototype_ `[[nodiscard]] bool Contains(FActiveState Other) const;` — @return true if this path contains anywhere the other element.
- L181 _public prototype_ `[[nodiscard]] static bool Contains(const TArrayView<const FActiveState>& Path, FActiveStateID Other);` — @return true if the path contains anywhere the other element.
- L184 _public prototype_ `[[nodiscard]] bool Contains(FActiveStateID Other) const;` — @return true if this path contains anywhere the other element.
- L187 _public prototype_ `[[nodiscard]] static int32 IndexOf(const TArrayView<const FActiveState>& Path, FActiveState Other);` — @return true the index of element inside the path.
- L190 _public prototype_ `[[nodiscard]]int32 IndexOf(FActiveState Other) const;` — @return true the index of element inside the path.
- L193 _public prototype_ `[[nodiscard]] static int32 IndexOf(const TArrayView<const FActiveState>& Path, FActiveStateID Other);` — @return true the index of element inside the path.
- L196 _public prototype_ `[[nodiscard]] int32 IndexOf(FActiveStateID Other) const;` — @return true the index of element inside the path.
- L199 _public prototype_ `[[nodiscard]] static TValueOrError<FString, void> Describe(TNotNull<const UStateTree*> StateTree, const TArrayView<const FActiveState>& Path);` — @return debugging information about the path.
- L202 _public prototype_ `[[nodiscard]] TValueOrError<FString, void> Describe() const;` — @return debugging information about the path.
- L205 _private member_ `TWeakObjectPtr<const UStateTree> StateTree;`
- L206 _private member_ `TArray<FActiveState> States;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATETREEMODULE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace StateTree` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeTaskBase.h` (Public)


#### struct `FStateTreeTaskBase`  
`struct FStateTreeTaskBase : public FStateTreeNodeBase`  
_L19-158_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeNodeBase`
- desc: Base struct for StateTree Tasks. Tasks are logic executed in an active state.
- L23 _public function_ `FStateTreeTaskBase() : bShouldStateChangeOnReselect(true) , bShouldCallTick(true) , bShouldCallTickOnlyOnEvents(false) , bShouldCopyBoundPropertiesOnTick(true) , bShouldCopyBoundPropertiesOnExitState(true) , bShouldAffectTransitions(false) , bConsideredForScheduling(true) , bTaskEnabled(true) , bHasTaskCompletionDelegateDispatcher(false) #if WITH_EDITORONLY_DATA , bConsideredForCompletion(true) , bCanEditConsideredForCompletion(true) #endif`
- L46 _public function_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const` — Called when a new state is entered and task is part of active states. @param Context Reference to current execution context. @param Transition Describes the states involved in the transition @return Succeed/Failed will end the state immediately and trigger to select new state, Running will carry on to tick the state.
- L56 _public function_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const` — Called when a current state is exited and task is part of active states. @param Context Reference to current execution context. @param Transition Describes the states involved in the transition
- L67 _public function_ `virtual void StateCompleted(FStateTreeExecutionContext& Context, const EStateTreeRunStatus CompletionStatus, const FStateTreeActiveStates& CompletedActiveStates) const` — Called right after a state has been completed, but before new state has been selected. StateCompleted is called in reverse order to allow to propagate state to other Tasks that are executed earlier in the tree. Note that StateCompleted is not called if conditional transition changes the state. @param Context Reference to current execution context. @param CompletionStatus Describes the running status of the completed state (Succeeded/Failed). @param CompletedActiveStates Active states at the time of completion.
- L78 _public function_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const` — Called during state tree tick when the task is on active state. Note: The method is called only if bShouldCallTick or bShouldCallTickOnlyOnEvents is set. @param Context Reference to current execution context. @param DeltaTime Time since last StateTree tick. @return Running status of the state: Running if still in progress, Succeeded if execution is done and succeeded, Failed if execution is done and failed.
- L88 _public function_ `virtual void TriggerTransitions(FStateTreeExecutionContext& Context) const` — Called when state tree triggers transitions. This method is called during transition handling, before state's tick and event transitions are handled. Note: the method is called only if bShouldAffectTransitions is set. @param Context Reference to current execution context.
- L93 _public function_ `virtual FName GetIconName() const override`
- L97 _public function_ `virtual FColor GetIconColor() const override`
- L104 _public prototype_ `virtual FString GetDebugInfo(const FStateTreeReadOnlyExecutionContext& Context) const;`
- L113 _public member_ `uint8 bShouldStateChangeOnReselect : 1;` — If set to true, the task will receive EnterState/ExitState even if the state was previously active. Generally this should be true for action type tasks, like playing animation, and false on state like tasks like claiming a resource that is expected to be acquired on child states. Default value is true.
- L116 _public member_ `uint8 bShouldCallTick : 1;` — If set to true, Tick() is called. Not ticking implies no property copy. Default true.
- L118 _public member_ `uint8 bShouldCallTickOnlyOnEvents : 1;` — If set to true, Tick() is called only when there are events. No effect if bShouldCallTick is true. Not ticking implies no property copy. Default false.
- L121 _public member_ `uint8 bShouldCopyBoundPropertiesOnTick : 1;` — If set to true, copy the values of bound properties before calling Tick(). Default true.
- L123 _public member_ `uint8 bShouldCopyBoundPropertiesOnExitState : 1;` — If set to true, copy the values of bound properties before calling ExitState(). Default true.
- L126 _public member_ `uint8 bShouldAffectTransitions : 1;` — If set to true, TriggerTransitions() is called during transition handling. Default false.
- L133 _public member_ `uint8 bConsideredForScheduling : 1;` — If set to true, the task is considered for scheduled tick. It will use these flags: bShouldCallTick, bShouldCallTickOnlyOnEvents, and bShouldAffectTransitions. It doesn't affect how the task ticks. Default true.
- L137 _public member_ `uint8 bTaskEnabled : 1;` — `UPROPERTY()` — True if the node is Enabled (i.e. not explicitly disabled in the asset).
- L141 _public member_ `uint8 bHasTaskCompletionDelegateDispatcher : 1;` — `UPROPERTY()` — True if the node is bound to a task completion delegate listener.
- L144 _public member_ `EStateTreeTransitionPriority TransitionHandlingPriority = EStateTreeTransitionPriority::Normal;` — `UPROPERTY()`
- L152 _public member_ `uint8 bConsideredForCompletion : 1;` — `UPROPERTY()` — True if the task is considered for completion. False if the task runs in the background without affecting the state completion.
- L156 _public member_ `uint8 bCanEditConsideredForCompletion : 1;` — `UPROPERTY()` — True if the user can edit bConsideredForCompletion in the editor.

#### struct `FStateTreeTaskCommonBase`  
`struct FStateTreeTaskCommonBase : public FStateTreeTaskBase`  
_L165-168_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeTaskBase`
- desc: Base class (namespace) for all common Tasks that are generally applicable. This allows schemas to safely include all conditions child of this struct.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATETREEMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeTasksStatus.h` (Public)


#### enum `EStateTreeTaskCompletionType`  
`enum class EStateTreeTaskCompletionType : uint8`  
_L16-22_
- reflection: `UENUM()`
- L19 _public enumerator_ `All` — All tasks need to complete for the group to completes.
- L21 _public enumerator_ `Any` — Any task completes the group.

#### enum `UE::StateTree::ETaskCompletionStatus`  
`enum class ETaskCompletionStatus : uint8`  
_L26-39_
- L29 _public enumerator_ `Running = 0` — The task is running.
- L34 _public enumerator_ `Stopped = 1` — The task stopped without a particular reason. (ie. Aborted). Use for backward compatibility. Prefer Succeeded and Failed.
- L36 _public enumerator_ `Succeeded = 2` — The task stopped with a success.
- L38 _public enumerator_ `Failed = 3` — The task stopped with a failure.

#### struct `UE::StateTree::TTasksCompletionStatus`  
`template<typename T> struct TTasksCompletionStatus`  
_L45-296_
- L48 _public member_ `static constexpr int32 MaxNumTasks = sizeof(T)*8;`
- L51 _public function_ `TTasksCompletionStatus(TNotNull<T*> InFirstCompletionBits, TNotNull<T*> InSecondCompletionBits, T InCompletionMask, int32 InBitIndex, EStateTreeTaskCompletionType InTaskControl) : FirstCompletionBits(InFirstCompletionBits) , SecondCompletionBits(InSecondCompletionBits) , CompletionMask(InCompletionMask) , BitIndex(InBitIndex) , TaskControl(InTaskControl)`
- L64 _public function_ `[[nodiscard]] ETaskCompletionStatus GetStatus(int32 StateTaskIndex) const` — @param StateTaskIndex The index of the task in the state. @return the status of a task.
- L77 _public function_ `[[nodiscard]] ETaskCompletionStatus GetCompletionStatus() const` — The completion status of all tasks or any task, in priority order. If any of the tasks fail, the completion status will be Failed regardless of any other tasks. In case the type is Any, it will return Succeeded before Stopped and before Running. @return the completion status of all tasks.
- L112 _public function_ `[[nodiscard]] bool IsConsideredForCompletion(int32 StateTaskIndex) const` — @param StateTaskIndex The index of the task in the state. @return true when the task is considered for GetCompletionStatus, HasAllCompleted, HasAnyCompleted, HasAnyFailed, IsCompleted
- L124 _public function_ `[[nodiscard]] bool IsRunning(int32 StateTaskIndex) const` — @param StateTaskIndex The index of the task in the state. @return true when the task status is running.
- L136 _public function_ `[[nodiscard]] bool HasFailed(int32 StateTaskIndex) const` — @param StateTaskIndex The index of the task in the state. @return true when the task status is failed.
- L145 _public function_ `[[nodiscard]] bool HasAllCompleted() const` — @return true when there's any failure or all tasks succeeded or stopped.
- L153 _public function_ `[[nodiscard]] bool HasAnyCompleted() const` — @return true when there's any failure or any tasks succeeded or stopped.
- L159 _public function_ `[[nodiscard]] bool HasAnyFailed() const` — @return true when there's any failure.
- L165 _public function_ `[[nodiscard]] bool IsCompleted() const` — @return true when there's any failure or respect the task control.
- L174 _public function_ `void SetStatus(int32 StateTaskIndex, ETaskCompletionStatus NewStatus)` — Set the status of a task. @param StateTaskIndex The index of the task in the state.
- L186 _public function_ `ETaskCompletionStatus SetStatusWithPriority(int32 StateTaskIndex, ETaskCompletionStatus NewStatus)` — Set the status of a task respecting the previous status value. The priority is Failed, Succeeded, Stopped, Running. @param StateTaskIndex The index of the task in the state.
- L212 _public function_ `FSetStatusResult SetTaskStatusWithPriority(int32 StateTaskIndex, ETaskCompletionStatus NewStatus)` — Set the status of a task respecting the previous status value and report if it changed. The priority is Failed, Succeeded, Stopped, Running. @param StateTaskIndex The index of the task in the state. @param NewStatus The new status to set. @return Result containing current status and whether it changed.
- L229 _public function_ `void SetCompletionStatus(ETaskCompletionStatus NewStatus)` — Set the status of all tasks in the completion mask.
- L245 _public function_ `void ResetStatus(int32 NumberOfTasksInTheCompletionMask)` — Set the status of all tasks to running.
- L268 _private function_ `uint8 GetStatusInternal(int32 Index) const`
- L276 _private function_ `void SetStatusInternal(int32 Index, ETaskCompletionStatus NewStatus)`
- L287 _private member_ `T* FirstCompletionBits;` — The first buffer. 00 is Running and 01 is Stopped.
- L289 _private member_ `T* SecondCompletionBits;` — The second buffer. 10 is Succeeded and 11 is Failed.
- L291 _private member_ `T CompletionMask;` — The mask that represents each task considered by the state/frame for completion.
- L293 _private member_ `int32 BitIndex;` — The offset, in bits, of the first task inside the mask.
- L295 _private member_ `EStateTreeTaskCompletionType TaskControl;` — How the mask is tested to complete the state/frame.

#### struct `UE::StateTree::TTasksCompletionStatus::FSetStatusResult`  
`struct FSetStatusResult`  
_L199-203_
- L201 _public member_ `ETaskCompletionStatus CurrentStatus = ETaskCompletionStatus::Running;`
- L202 _public member_ `bool bChanged = false;`

#### struct `FStateTreeTasksCompletionStatus`  
`struct FStateTreeTasksCompletionStatus`  
_L330-391_
- reflection: `USTRUCT()`
- desc: Container for task status for all the active states and global tasks. Each task needs 2 bits of information. The information is in 2 different int32. 1 bit per int32 instead of 2bits inside the same int32. The int32 are sequential: The first masks takes the 2 first int32 and (if needed) the second mask takes the 3rd and 4th int32. A state/global has at least 1 entry (2bits), even if there are no tasks on the state/global. It is to represent if the state completes (ex: when no tasks are ticked the state completes). The bits, from different states, are packed until there are too many to fit inside the same int32. When it can't be packed, all the bits from that overflow state are moved to the next int32. When possible (when the number of tasks is below 32), the buffer will be inlined. Otherwise, it will use dynamic memory. We allocate the worst case scenario when the frame is created. Ex: For the tree: (0)Global task: 8 tasks. (1)State Root: 6 tasks. (2)StateA: no task (it takes one bit). (3)StateB: 10 tasks. (4)State: 8 tasks, not enough space go to the next int32. (5)State: 1 task, takes one bit. The mask looks like: [------33333333333211111100000000|-----------------------544444444] The buffer will be 4 int32. The first 2 int32 are for the (0)Global task, (1)State Root, (2)State, (3)StateB The next 2 int32 are for the (4)State, (5)State The first bit of each buffer is combined to represent the ETaskCompletionStatus. Ex: (on int8 instead of int32 to be shorter in this descript
- L334 _public typedef_ `using FMaskType = uint32;`
- L335 _public member_ `static constexpr int32 MaxNumberOfTasksPerGroup = sizeof(FMaskType)*8;`
- L337 _public member_ `static constexpr int32 MaxTotalAmountOfTasks = MaxNumberOfTasksPerGroup + MaxNumberOfTasksPerGroup * 8;` — 32 global global tasks + 32 tasks per states for a max of 8 states(max 8 states per frame).
- L340 _public prototype_ `FStateTreeTasksCompletionStatus() = default;`
- L341 _public prototype_ `explicit FStateTreeTasksCompletionStatus(const FCompactStateTreeFrame& Frame);`
- L342 _public prototype_ `~FStateTreeTasksCompletionStatus();`
- L344 _public prototype_ `FStateTreeTasksCompletionStatus(const FStateTreeTasksCompletionStatus&);`
- L345 _public prototype_ `FStateTreeTasksCompletionStatus(FStateTreeTasksCompletionStatus&&);`
- L346 _public prototype_ `FStateTreeTasksCompletionStatus& operator=(const FStateTreeTasksCompletionStatus&);`
- L347 _public prototype_ `FStateTreeTasksCompletionStatus& operator=(FStateTreeTasksCompletionStatus&&);`
- L350 _public prototype_ `[[nodiscard]] UE::StateTree::FTasksCompletionStatus GetStatus(const FCompactStateTreeState& State);`
- L351 _public prototype_ `[[nodiscard]] UE::StateTree::FConstTasksCompletionStatus GetStatus(const FCompactStateTreeState& State) const;`
- L353 _public prototype_ `[[nodiscard]] UE::StateTree::FTasksCompletionStatus GetStatus(TNotNull<const UStateTree*> StateTree);`
- L354 _public prototype_ `[[nodiscard]] UE::StateTree::FConstTasksCompletionStatus GetStatus(TNotNull<const UStateTree*> StateTree) const;`
- L357 _public function_ `[[nodiscard]] bool IsValid() const` — @return true when the status is initialized correctly.
- L362 _public prototype_ `void Push(const FCompactStateTreeState& State);`
- L364 _public prototype_ `bool Serialize(FArchive& Ar);`
- L365 _public prototype_ `bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);`
- L368 _private member_ `static constexpr int32 MaxNumberOfTaskForInlineBuffer = sizeof(FMaskType*) * 8 / 2;`
- L370 _private function_ `inline bool UseInlineBuffer() const`
- L375 _private prototype_ `void MallocBufferIfNeeded();`
- L376 _private prototype_ `void CopyBuffer(const FStateTreeTasksCompletionStatus& Other);`
- L379 _private prototype_ `template<typename TTasksCompletionStatusType> inline TTasksCompletionStatusType GetStatusInternal(FMaskType Mask, uint8 BufferIndex, uint8 BitsOffset, EStateTreeTaskCompletionType Control);`
- L385 _private member_ `FMaskType* Buffer = nullptr;` — Dynamic or inlined container for a FMaskType. The actual memory used is double of BufferNum because each task has 2 bits of information.
- L390 _private member_ `uint8 BufferNum = 0;` — Number of requested FMaskType. If <= 1, it will use Buffer as an inlined buffer.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FStateTreeTasksCompletionStatus> : public TStructOpsTypeTraitsBase2<FStateTreeTasksCompletionStatus>`  
_L394-402_
- inherits: `TStructOpsTypeTraitsBase2<FStateTreeTasksCompletionStatus>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L397-401_

#### struct `TIsTriviallyRelocatable`  
`template <UE::CDerivedFrom<FStateTreeTasksCompletionStatus> T> struct TIsTriviallyRelocatable<T>`  
_L406-409_
- desc: FStateTreeTasksCompletionStatus is not trivially relocatable. Flag their use in containers and other contexts.
- L408 _public member_ `static inline constexpr bool Value = false;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace StateTree` (scope `UE`)
- L41 _variable_ `static constexpr int32 NumberOfTaskStatus = 4;` (scope `UE::StateTree`) — Number of entry in the ETaskCompletionStatus.
- L298 _typedef_ `using FTasksCompletionStatus = TTasksCompletionStatus<uint32>;` (scope `UE::StateTree`)
- L299 _typedef_ `using FConstTasksCompletionStatus = TTasksCompletionStatus<const uint32>;` (scope `UE::StateTree`)
- L398 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonb12efd3f0103`)
- L399 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonb12efd3f0103`)
- L400 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anonb12efd3f0103`)

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeTypes.h` (Public)


#### enum `UE::StateTree::EComparisonOperator`  
`enum class EComparisonOperator : uint8`  
_L60-68_
- reflection: `UENUM()`
- L62 _public enumerator_ `Less`
- L63 _public enumerator_ `LessOrEqual`
- L64 _public enumerator_ `Equal`
- L65 _public enumerator_ `NotEqual`
- L66 _public enumerator_ `GreaterOrEqual`
- L67 _public enumerator_ `Greater`

#### enum `EStateTreeTransitionType`  
`enum class EStateTreeTransitionType : uint8`  
_L76-106_
- reflection: `UENUM()`
- desc: Transitions behavior.
- L79 _public enumerator_ `None` — No transition will take place.
- L82 _public enumerator_ `Succeeded` — Stop State Tree or sub-tree and mark execution succeeded.
- L85 _public enumerator_ `Failed` — Stop State Tree or sub-tree and mark execution failed.
- L88 _public enumerator_ `GotoState` — Transition to the specified state.
- L91 _public enumerator_ `Parent` — Transition to the parent state.
- L94 _public enumerator_ `NextState` — Transition to the next sibling state.
- L97 _public enumerator_ `NextSelectableState` — Transition to the next selectable sibling state.
- L100 _public enumerator_ `NextParent` — Transition to the next sibling state of the parent state.
- L103 _public enumerator_ `NextSelectableParent` — Transition to the next selectable sibling state of the parent state.
- L105 _public enumerator_ `NotSet UE_DEPRECATED(all, "Use None instead.")`

#### enum `EStateTreeStateSelectionRules`  
`enum class EStateTreeStateSelectionRules : uint32`  
_L110-132_
- reflection: `UENUM()`
- desc: The rules used by the execution context for selecting states.
- L113 _public enumerator_ `None = 0` — Previous (UE 5.6) rules
- L119 _public enumerator_ `CompletedTransitionStatesCreateNewStates = 1 << 0` — If the transition source state or the transition target state (or any child states of the source or target) is completed, then the completed states are new (recreated if needed). When a new state is created, all the following states in the selection path are also new (recreated if needed). Without this rule, the state will remain active even if it's completed. The state might never trigger a complete transition.
- L124 _public enumerator_ `CompletedStateBeforeTransitionSourceFailsTransition = 1 << 1` — The transition will fail if there is a completed state before the transition source state. Without this rule, a transition that triggers on completion might take an extra tick to execute.
- L129 _public enumerator_ `ReselectedStateCreatesNewStates = 1 << 2` — When selecting a parent state(from a child), the target child states are new (recreated if needed). Without this rule, the "reselected" states are sustained.
- L131 _public enumerator_ `Default = CompletedTransitionStatesCreateNewStates | CompletedStateBeforeTransitionSourceFailsTransition`

#### enum `EStateTreeExpressionOperand`  
`enum class EStateTreeExpressionOperand : uint8`  
_L137-150_
- reflection: `UENUM()`
- desc: Operand in an expression
- L140 _public enumerator_ `Copy UMETA(Hidden)` — Copy result
- L143 _public enumerator_ `And` — Combine results with AND for Condition, Min(a, b) for Consideration
- L146 _public enumerator_ `Or` — Combine results with OR for Condition, Max(a, b) for Consideration
- L149 _public enumerator_ `Multiply` — Combine results with (a * b) for Consideration, not applicable for Condition

#### enum `EStateTreeStateType`  
`enum class EStateTreeStateType : uint8`  
_L153-169_
- reflection: `UENUM()`
- L156 _public enumerator_ `State` — A State containing tasks and child states.
- L159 _public enumerator_ `Group` — A State containing just child states.
- L162 _public enumerator_ `Linked` — A State that is linked to another state in the tree (the execution continues on the linked state).
- L165 _public enumerator_ `LinkedAsset` — A State that is linked to another StateTree asset (the execution continues on the Root state of the linked asset).
- L168 _public enumerator_ `Subtree` — A subtree that can be linked to.

#### enum `EStateTreeStateSelectionBehavior`  
`enum class EStateTreeStateSelectionBehavior : uint8`  
_L172-198_
- reflection: `UENUM()`
- L175 _public enumerator_ `None` — The State cannot be directly selected.
- L178 _public enumerator_ `TryEnterState UMETA(DisplayName = "Try Enter")` — When state is considered for selection, it is selected even if it has child states.
- L181 _public enumerator_ `TrySelectChildrenInOrder UMETA(DisplayName = "Try Select Children In Order")` — When state is considered for selection, try to select the first child state (in order they appear in the child list). If no child states are present, behaves like SelectState.
- L184 _public enumerator_ `TrySelectChildrenAtRandom UMETA(DisplayName = "Try Select Children At Random")` — When state is considered for selection, shuffle the order of child states and try to select the first one. If no child states are present, behaves like SelectState.
- L187 _public enumerator_ `TrySelectChildrenWithHighestUtility UMETA(DisplayName = "Try Select Children With Highest Utility")` — When state is considered for selection, try to select the child state with highest utility score. If there is a tie, it will try to select in order.
- L190 _public enumerator_ `TrySelectChildrenAtRandomWeightedByUtility UMETA(DisplayName = "Try Select Children At Random Weighted By Utility")` — When state is considered for selection, randomly pick one of its child states. The probability of selecting each child state is its normalized utility score
- L193 _public enumerator_ `TryFollowTransitions UMETA(DisplayName = "Try Follow Transitions")` — When state is considered for selection, try to trigger the transitions instead.
- L196 _public enumerator_ `TrySelectChildrenAtUniformRandom UE_DEPRECATED(all, "Use TrySelectChildrenAtRandom Instead") = TrySelectChildrenAtRandom UMETA(Hidden)` — Olds names that needs to be kept forever to ensure asset serialization to work correctly when UENUM() switched from serializing int to names.
- L197 _public enumerator_ `TrySelectChildrenBasedOnRelativeUtility UE_DEPRECATED(all, "Use TrySelectChildrenAtRandomWeightedByUtility Instead") = TrySelectChildrenAtRandomWeightedByUtility UMETA(Hidden)`

#### enum `EStateTreeTransitionTrigger`  
`enum class EStateTreeTransitionTrigger : uint8`  
_L218-241_
- reflection: `UENUM()`
- desc: Transitions trigger.
- L220 _public enumerator_ `None = 0 UMETA(Hidden)`
- L223 _public enumerator_ `OnStateCompleted = 0x1 | 0x2` — Try trigger transition when a state succeeded or failed.
- L226 _public enumerator_ `OnStateSucceeded = 0x1` — Try trigger transition when a state succeeded.
- L229 _public enumerator_ `OnStateFailed = 0x2` — Try trigger transition when a state failed.
- L232 _public enumerator_ `OnTick = 0x4` — Try trigger transition each State Tree tick.
- L235 _public enumerator_ `OnEvent = 0x8` — Try trigger transition on specific State Tree event.
- L238 _public enumerator_ `OnDelegate = 0x10` — Try trigger transition on specific State Tree delegate.
- L240 _public enumerator_ `MAX`

#### enum `EStateTreeTransitionPriority`  
`enum class EStateTreeTransitionPriority : uint8`  
_L247-265_
- reflection: `UENUM(BlueprintType)`
- desc: Transition priority. When multiple transitions trigger at the same time, the first transition of highest priority is selected.
- L249 _public enumerator_ `None UMETA(Hidden)`
- L252 _public enumerator_ `Low` — Low priority.
- L255 _public enumerator_ `Normal` — Normal priority.
- L258 _public enumerator_ `Medium` — Medium priority.
- L261 _public enumerator_ `High` — High priority.
- L264 _public enumerator_ `Critical` — Critical priority.

#### struct `FStateTreeStateHandle`  
`struct FStateTreeStateHandle`  
_L276-323_
- reflection: `USTRUCT(BlueprintType)`
- desc: Handle to a StateTree state
- L280 _public member_ `static constexpr uint16 InvalidIndex = uint16(-1);` — Index value indicating invalid state.
- L281 _public member_ `static constexpr uint16 SucceededIndex = uint16(-2);` — Index value indicating a Succeeded state.
- L282 _public member_ `static constexpr uint16 FailedIndex = uint16(-3);` — Index value indicating a Failed state.
- L283 _public member_ `static constexpr uint16 StoppedIndex = uint16(-4);` — Index value indicating a Stopped state.
- L285 _public member_ `static const FStateTreeStateHandle Invalid;`
- L286 _public member_ `static const FStateTreeStateHandle Succeeded;`
- L287 _public member_ `static const FStateTreeStateHandle Failed;`
- L288 _public member_ `static const FStateTreeStateHandle Stopped;`
- L289 _public member_ `static const FStateTreeStateHandle Root;`
- L292 _public function_ `static bool IsValidIndex(const int32 Index)` — @return true if the given index can be represented by the type.
- L302 _public prototype_ `FStateTreeStateHandle() = default;`
- L303 _public function_ `explicit FStateTreeStateHandle(const uint16 InIndex) : Index(InIndex)`
- L304 _public function_ `explicit FStateTreeStateHandle(const int32 InIndex) : Index()`
- L310 _public function_ `bool IsValid() const`
- L311 _public function_ `void Invalidate()`
- L312 _public function_ `bool IsCompletionState() const`
- L313 _public prototype_ `EStateTreeRunStatus ToCompletionStatus() const;`
- L314 _public prototype_ `static FStateTreeStateHandle FromCompletionStatus(const EStateTreeRunStatus Status);`
- L316 _public function_ `bool operator==(const FStateTreeStateHandle& RHS) const`
- L317 _public function_ `bool operator!=(const FStateTreeStateHandle& RHS) const`
- L319 _public prototype_ `FString Describe() const;`
- L322 _public member_ `uint16 Index = InvalidIndex;` — `UPROPERTY()`

#### enum `EStateTreeDataSourceType`  
`enum class EStateTreeDataSourceType : uint8`  
_L328-388_
- reflection: `UENUM(BlueprintType)`
- desc: Data type the FStateTreeDataHandle is pointing at.
- L330 _public enumerator_ `None UMETA(Hidden)`
- L333 _public enumerator_ `GlobalInstanceData` — Global Tasks, Evaluators.
- L336 _public enumerator_ `GlobalInstanceDataObject` — Global Tasks, Evaluators.
- L339 _public enumerator_ `ActiveInstanceData` — Active State Tasks
- L342 _public enumerator_ `ActiveInstanceDataObject` — Active State Tasks
- L345 _public enumerator_ `SharedInstanceData` — Conditions, considerations and function bindings.
- L348 _public enumerator_ `SharedInstanceDataObject` — Conditions, considerations and function bindings
- L351 _public enumerator_ `EvaluationScopeInstanceData` — Temporary data constructor, used and destroyed immediately. Used by conditions, considerations and function bindings.
- L354 _public enumerator_ `EvaluationScopeInstanceDataObject` — Temporary data constructor, used and destroyed immediately. Used by conditions, considerations and function bindings.
- L357 _public enumerator_ `ExecutionRuntimeData` — Node instance data for the duration of the execution.
- L360 _public enumerator_ `ExecutionRuntimeDataObject` — Node instance data for the duration of the execution.
- L363 _public enumerator_ `ExecutionRuntimeDataAny` — Node instance data for the duration of the execution. Discover at runtime if it's a struct or an object.
- L366 _public enumerator_ `ContextData` — Context Data, Tree Parameters
- L369 _public enumerator_ `ExternalData` — External Data required by the nodes.
- L372 _public enumerator_ `GlobalParameterData` — Global parameters
- L375 _public enumerator_ `SubtreeParameterData` — Parameters for subtree (may resolve to a linked state's parameters or default params)
- L378 _public enumerator_ `StateParameterData` — Parameters for regular and linked states
- L381 _public enumerator_ `TransitionEvent` — Event used in transition.
- L384 _public enumerator_ `StateEvent` — Event used in state selection.
- L387 _public enumerator_ `ExternalGlobalParameterData` — Global parameters provided externally

#### enum `EStateTreeParameterDataType`  
`enum class EStateTreeParameterDataType : uint8`  
_L392-396_
- reflection: `UENUM()`
- desc: Data type the global parameter type uses.
- L394 _public enumerator_ `GlobalParameterData`
- L395 _public enumerator_ `ExternalGlobalParameterData`

#### struct `FStateTreeDataHandle`  
`struct FStateTreeDataHandle`  
_L408-515_
- reflection: `USTRUCT(BlueprintType)`
- desc: Handle to a StateTree data
- L412 _public member_ `static const FStateTreeDataHandle Invalid;`
- L413 _public member_ `static constexpr uint16 InvalidIndex = MAX_uint16;`
- L416 _public function_ `static bool IsValidIndex(const int32 Index)` — @return true if the given index can be represented by the type.
- L421 _public function_ `bool HasValidIndex() const`
- L434 _public prototype_ `FStateTreeDataHandle() = default;`
- L436 _public function_ `explicit FStateTreeDataHandle(const EStateTreeDataSourceType InSource, const uint16 InIndex, const FStateTreeStateHandle InStateHandle = FStateTreeStateHandle::Invalid) : Source(InSource) , Index(InIndex) , StateHandle(InStateHandle)`
- L447 _public function_ `explicit FStateTreeDataHandle(const EStateTreeDataSourceType InSource, const int32 InIndex, const FStateTreeStateHandle InStateHandle = FStateTreeStateHandle::Invalid) : Source(InSource) , StateHandle(InStateHandle)`
- L458 _public function_ `explicit FStateTreeDataHandle(const EStateTreeDataSourceType InSource) : FStateTreeDataHandle(InSource, FStateTreeDataHandle::InvalidIndex)`
- L462 _public function_ `bool IsValid() const`
- L467 _public function_ `void Reset()`
- L474 _public function_ `bool operator==(const FStateTreeDataHandle& RHS) const`
- L479 _public function_ `bool operator!=(const FStateTreeDataHandle& RHS) const`
- L484 _public function_ `EStateTreeDataSourceType GetSource() const`
- L489 _public function_ `int32 GetIndex() const`
- L494 _public function_ `FStateTreeStateHandle GetState() const`
- L499 _public prototype_ `bool IsObjectSource() const;`
- L501 _public prototype_ `FStateTreeDataHandle ToObjectSource() const;`
- L502 _public prototype_ `FStateTreeDataHandle ToStructSource() const;`
- L504 _public prototype_ `FString Describe() const;`
- L508 _private member_ `EStateTreeDataSourceType Source = EStateTreeDataSourceType::None;` — `UPROPERTY()`
- L511 _private member_ `uint16 Index = InvalidIndex;` — `UPROPERTY()`
- L514 _private member_ `FStateTreeStateHandle StateHandle = FStateTreeStateHandle::Invalid;` — `UPROPERTY()`

#### struct `UE::StateTree::InstanceData::FEvaluationScopeMemoryRequirement`  
`struct FEvaluationScopeMemoryRequirement`  
_L520-529_
- desc: The memory requirement for the container allocation.
- L522 _public member_ `int32 Size = 0;`
- L523 _public member_ `int32 Alignment = 0;`
- L524 _public member_ `int32 NumberOfElements = 0;`
- L525 _public function_ `bool HasMemory() const`

#### struct `FStateTreeRandomTimeDuration`  
`struct FStateTreeRandomTimeDuration`  
_L537-594_
- reflection: `USTRUCT()`
- desc: Time duration with random variance. Stored compactly as two uint16s, which gives time range of about 650 seconds. The variance is symmetric (+-) around the specified duration.
- L542 _public function_ `void Reset()` — Reset duration to empty.
- L549 _public function_ `void Set(const float InDuration, const float InRandomVariance)` — Sets the time duration with random variance.
- L556 _public function_ `float GetDuration() const` — @return the fixed duration.
- L562 _public function_ `float GetRandomVariance() const` — @return the maximum random variance.
- L568 _public function_ `bool IsEmpty() const` — @return True of the duration is empty (always returns 0).
- L574 _public function_ `float GetRandomDuration(const FRandomStream& RandomStream) const` — @return Returns random duration around Duration, varied by +-RandomVariation.
- L582 _protected member_ `static constexpr float Scale = 100.0f;`
- L584 _protected function_ `uint16 Quantize(const float Value) const`
- L590 _protected member_ `uint16 Duration = 0;` — `UPROPERTY(EditDefaultsOnly, Category = Default)`
- L593 _protected member_ `uint16 RandomVariance = 0;` — `UPROPERTY(EditDefaultsOnly, Category = Default)`

#### enum `EStateTreeSelectionFallback`  
`enum class EStateTreeSelectionFallback : uint8`  
_L598-605_
- reflection: `UENUM()`
- desc: Fallback behavior indicating what to do after failing to select a state
- L601 _public enumerator_ `None` — No fallback
- L604 _public enumerator_ `NextSelectableSibling` — Find next selectable sibling, if any, and select it

#### struct `FCompactEventDesc`  
`struct FCompactEventDesc`  
_L611-650_
- reflection: `USTRUCT()`
- desc: Runtime representation of an event description.
- L617 _public member_ `TObjectPtr<const UScriptStruct> PayloadStruct = nullptr;` — `UPROPERTY()` — Event Payload Struct.
- L621 _public member_ `FGameplayTag Tag;` — `UPROPERTY()` — Event Tag.
- L624 _public function_ `bool IsValid() const` — Returns true if describes an event correctly.
- L630 _public function_ `bool IsSubsetOfAnotherDesc(const FCompactEventDesc& Desc) const` — Returns true if described events is a subset of events described by another EventDesc.
- L649 _public prototype_ `bool DoesEventMatchDesc(const FStateTreeEvent& Event) const;` — Returns true provided event matches description.

#### enum `EStateTreeTransitionChangeTypeRules`  
`enum class EStateTreeTransitionChangeTypeRules : uint8`  
_L657-662_
- reflection: `UENUM()`
- desc: Additional rules for if state was changed or sustained per transition. This is exposed to designers as "Reactivation" w/ "Override" & "Denied" options.
- L659 _public enumerator_ `ForceChanged`
- L660 _public enumerator_ `ForceSustained`
- L661 _public enumerator_ `Default`

#### struct `FCompactStateTransition`  
`struct FCompactStateTransition`  
_L668-747_
- reflection: `USTRUCT()`
- desc: Runtime representation of a StateTree transition.
- L672 _public function_ `explicit FCompactStateTransition()`
- L677 _public function_ `bool HasDelay() const` — @return True if the transition has delay.
- L683 _public function_ `EStateTreeStateSelectionRules GetStateSelectionRulesForTransition(EStateTreeStateSelectionRules ModifiedStateSelectionRules) const` — @return flags for state selection based on this transition's configuration
- L699 _public member_ `FCompactEventDesc RequiredEvent;` — `UPROPERTY()` — Event Description
- L703 _public member_ `FStateTreeDelegateDispatcher RequiredDelegateDispatcher;` — `UPROPERTY()` — Delegate dispatcher the transition is waiting for.
- L706 _public member_ `UE::StateTree::InstanceData::FEvaluationScopeMemoryRequirement ConditionEvaluationScopeMemoryRequirement;` — The amount of memory used by the condition when it uses the evaluation scope data type.
- L710 _public member_ `uint16 ConditionsBegin = 0;` — `UPROPERTY()` — Index to first condition to test
- L714 _public member_ `FStateTreeStateHandle State = FStateTreeStateHandle::Invalid;` — `UPROPERTY()` — Target state of the transition
- L718 _public member_ `FStateTreeRandomTimeDuration Delay;` — `UPROPERTY()` — Transition delay.
- L722 _public member_ `EStateTreeTransitionTrigger Trigger = EStateTreeTransitionTrigger::None;` — `UPROPERTY()` — Type of the transition trigger.
- L726 _public member_ `EStateTreeTransitionPriority Priority = EStateTreeTransitionPriority::Normal;` — `UPROPERTY()` — Priority of the transition.
- L730 _public member_ `EStateTreeSelectionFallback Fallback = EStateTreeSelectionFallback::None;` — `UPROPERTY()` — Fallback of the transition if it fails to select the target state
- L734 _public member_ `uint8 ConditionsNum = 0;` — `UPROPERTY()` — Number of conditions to test.
- L738 _public member_ `EStateTreeTransitionChangeTypeRules ChangeTypeTargetStateRule = EStateTreeTransitionChangeTypeRules::Default;` — `UPROPERTY()` — Additional rules for state changed or sustain. Their instance data will be reinstantiated.
- L742 _public member_ `uint8 bTransitionEnabled : 1 = true;` — `UPROPERTY()` — Indicates if the transition is enabled and should be considered.
- L746 _public member_ `uint8 bConsumeEventOnSelect : 1 = true;` — `UPROPERTY()` — If set to true, the required event is consumed (later state selection cannot react to it) if state selection can be made.

#### struct `FCompactStateTreeFrame`  
`struct FCompactStateTreeFrame`  
_L753-768_
- reflection: `USTRUCT()`
- desc: Runtime representation of a StateTree frame.
- L759 _public member_ `FStateTreeStateHandle RootState = FStateTreeStateHandle::Invalid;` — `UPROPERTY()` — The root state of the frame (e.g. Root state or a subtree).
- L767 _public member_ `uint8 NumberOfTasksStatusMasks = 0;` — `UPROPERTY()` — The max number of masks needed by the frame. It is the worst case of all the possible active state combinations for the frame. It includes the global tasks.

#### struct `FCompactStateTreeState`  
`struct FCompactStateTreeState`  
_L774-1039_
- reflection: `USTRUCT()`
- desc: Runtime representation of a StateTree state.
- L779 _public function_ `uint16 GetNextSibling() const` — @return Index to the next sibling state.
- L785 _public function_ `bool HasChildren() const` — @return True if the state has any child states
- L791 _public function_ `bool DoesRequestTickTasks(bool bHasEvent) const` — @return True if the state has any tasks that need ticking.
- L797 _public function_ `bool ShouldTickTasks(bool bHasEvent) const` — @return True if the state has any tasks that ticks.
- L803 _public function_ `bool ShouldTickTransitions(bool bHasEvent, bool bHasBroadcastedDelegates) const` — @return True if the state has any transitions that need ticking.
- L815 _public function_ `bool ShouldTickCompletionTransitions(bool bSucceeded, bool bFailed) const` — A state can complete with Stopped, Succeeded, and Failed. The state can contain transitions that trigger on any completes, or only if the state succeeded, or only if the state failed. @param bSucceeded Whenever the state completion succeeded. @param bFailed Whenever the state completion failed. @return True if the state has any transitions that tick on completion.
- L824 _public member_ `FCompactEventDesc RequiredEventToEnter;` — `UPROPERTY()` — Description of an event required to enter the state.
- L828 _public member_ `FName Name;` — `UPROPERTY()` — Name of the State
- L832 _public member_ `FGameplayTag Tag;` — `UPROPERTY()` — GameplayTag describing the State
- L835 _public member_ `UE::StateTree::InstanceData::FEvaluationScopeMemoryRequirement EnterConditionEvaluationScopeMemoryRequirement;` — The amount of memory used by the condition when it uses the evaluation scope data type.
- L838 _public member_ `UE::StateTree::InstanceData::FEvaluationScopeMemoryRequirement ConsiderationEvaluationScopeMemoryRequirement;` — The amount of memory used by the consideration when it uses the evaluation scope data type.
- L841 _public member_ `TObjectPtr<UStateTree> LinkedAsset = nullptr;` — `UPROPERTY()`
- L845 _public member_ `FStateTreeStateHandle LinkedState = FStateTreeStateHandle::Invalid;` — `UPROPERTY()` — Linked state handle if the state type is linked state.
- L849 _public member_ `FStateTreeStateHandle Parent = FStateTreeStateHandle::Invalid;` — `UPROPERTY()` — Parent state handle, invalid if root state.
- L853 _public member_ `uint16 ChildrenBegin = 0;` — `UPROPERTY()` — Index to first child state
- L857 _public member_ `uint16 ChildrenEnd = 0;` — `UPROPERTY()` — Index one past the last child state.
- L861 _public member_ `uint16 EnterConditionsBegin = 0;` — `UPROPERTY()` — Index to first state enter condition
- L865 _public member_ `uint16 UtilityConsiderationsBegin = 0;` — `UPROPERTY()` — Index to first state utility consideration
- L869 _public member_ `uint16 TransitionsBegin = 0;` — `UPROPERTY()` — Index to first transition
- L873 _public member_ `uint16 TasksBegin = 0;` — `UPROPERTY()` — Index to first task
- L877 _public member_ `FStateTreeIndex16 ParameterTemplateIndex = FStateTreeIndex16::Invalid;` — `UPROPERTY()` — Index to state instance data.
- L880 _public member_ `FStateTreeDataHandle ParameterDataHandle = FStateTreeDataHandle::Invalid;` — `UPROPERTY()`
- L883 _public member_ `FStateTreeIndex16 ParameterBindingsBatch = FStateTreeIndex16::Invalid;` — `UPROPERTY()`
- L886 _public member_ `FStateTreeIndex16 EventDataIndex = FStateTreeIndex16::Invalid;` — `UPROPERTY()`
- L890 _public member_ `float Weight = 1.f;` — `UPROPERTY()` — Weight used to scale the normalized final utility score for this state
- L898 _public member_ `float CustomTickRate = 0.f;` — `UPROPERTY()` — Tick rate in seconds the state tasks and transitions should tick If set the state cannot sleep. Must be greater than or equal to 0.
- L902 _public member_ `uint32 CompletionTasksMask = 0;` — `UPROPERTY()` — Mask used to test the tasks completion.
- L909 _public member_ `uint8 CompletionTasksMaskBufferIndex = 0;` — `UPROPERTY()` — Index in the mask buffer used by the state. CompletionTasksMaskBufferIndex = (Final Task Bit) / (size of mask:32)
- L917 _public member_ `uint8 CompletionTasksMaskBitsOffset = 0;` — `UPROPERTY()` — Offset, in bits, of the first flag inside the mask. Used to access the bit from the state task index. CompletionTasksMaskBitsOffset = (Final Task Bit) % (size of mask:32)
- L921 _public member_ `EStateTreeTaskCompletionType CompletionTasksControl = EStateTreeTaskCompletionType::Any;` — `UPROPERTY()` — How the tasks control the completion of the state.
- L925 _public member_ `uint8 EnterConditionsNum = 0;` — `UPROPERTY()` — Number of enter conditions
- L929 _public member_ `uint8 UtilityConsiderationsNum = 0;` — `UPROPERTY()` — Number of utility considerations
- L933 _public member_ `uint8 TransitionsNum = 0;` — `UPROPERTY()` — Number of transitions
- L937 _public member_ `uint8 TasksNum = 0;` — `UPROPERTY()` — Number of tasks
- L944 _public member_ `uint8 EnabledTasksNum = 0;` — `UPROPERTY()` — Number of enabled tasks todo: this should be removed once we finished only compiling enabled elements for StateTree Compiler
- L948 _public member_ `uint8 InstanceDataNum = 0;` — `UPROPERTY()` — Number of instance data
- L952 _public member_ `uint8 Depth = 0;` — `UPROPERTY()` — Distance to root state.
- L956 _public member_ `EStateTreeStateType Type = EStateTreeStateType::State;` — `UPROPERTY()` — Type of the state
- L960 _public member_ `EStateTreeStateSelectionBehavior SelectionBehavior = EStateTreeStateSelectionBehavior::TrySelectChildrenInOrder;` — `UPROPERTY()` — What to do when the state is considered for selection.
- L964 _public member_ `uint8 bCanOverrideLinkedAssetAtRuntime : 1 = true;` — `UPROPERTY()` — Whether the linked state supports Linked Asset override.
- L968 _public member_ `uint8 bHasTransitionTasks : 1 = false;` — `UPROPERTY()` — True if the state contains tasks that should be called during transition handling.
- L972 _public member_ `uint8 bHasStateChangeConditions : 1 = false;` — `UPROPERTY()` — True if the state contains conditions which require call to enter/completed/exit state.
- L975 _public member_ `uint8 bHasTickTasks : 1 = false;` — True if any task has bShouldCallTick.
- L981 _public member_ `uint8 bHasTickTasksOnlyOnEvents : 1 = false;` — True if any task has bShouldCallTickOnlyOnEvents. No effect if bHasTickTasks is true.
- L985 _public member_ `uint8 bCachedRequestTick : 1 = false;` — True if any state tasks request a tick every frame.
- L991 _public member_ `uint8 bCachedRequestTickOnlyOnEvents : 1 = false;` — True if any state tasks request a tick every frame but only if there are events. No effect if bCachedRequestTick is true.
- L995 _public member_ `uint8 bHasTickTriggerTransitions : 1 = false;` — `UPROPERTY()` — True if the state contains transitions with tick trigger.
- L999 _public member_ `uint8 bHasEventTriggerTransitions : 1 = false;` — `UPROPERTY()` — True if the state contains transitions with event trigger.
- L1003 _public member_ `uint8 bHasDelegateTriggerTransitions : 1 = false;` — `UPROPERTY()` — True if the state contains transitions with delegate trigger.
- L1007 _public member_ `uint8 bHasCompletedTriggerTransitions : 1 = false;` — `UPROPERTY()` — True if the state contains transitions with completed trigger.
- L1011 _public member_ `uint8 bHasSucceededTriggerTransitions : 1 = false;` — `UPROPERTY()` — True if the state contains transitions with Succeeded trigger.
- L1015 _public member_ `uint8 bHasFailedTriggerTransitions : 1 = false;` — `UPROPERTY()` — True if the state contains transitions with Succeeded trigger.
- L1019 _public member_ `uint8 bCheckPrerequisitesWhenActivatingChildDirectly : 1 = false;` — `UPROPERTY()` — Should state's required event and enter conditions be evaluated when transition leads directly to it's child.
- L1023 _public member_ `uint8 bEnabled : 1 = true;` — `UPROPERTY()` — True if the state is Enabled (i.e. not explicitly marked as disabled).
- L1027 _public member_ `uint8 bConsumeEventOnSelect : 1 = true;` — `UPROPERTY()` — If set to true, the required event is consumed (later state selection cannot react to it) if state selection can be made.
- L1031 _public member_ `uint8 bHasCustomTickRate : 1 = false;` — `UPROPERTY()` — If set to true, the state has a custom tick rate.
- L1038 _public member_ `uint8 bCopyParameterBindingsOnTick : 1 = false;` — `UPROPERTY()` — If true, state parameter bindings are copied on each task tick. Parameters bindings are always copied on state enter and state exit.

#### struct `FCompactStateTreeParameters`  
`struct FCompactStateTreeParameters`  
_L1042-1088_
- reflection: `USTRUCT()`
- L1047 _public prototype_ `FCompactStateTreeParameters() = default;`
- L1048 _public prototype_ `FCompactStateTreeParameters(const FCompactStateTreeParameters&) = default;`
- L1049 _public prototype_ `FCompactStateTreeParameters(FCompactStateTreeParameters&&) = default;`
- L1050 _public prototype_ `FCompactStateTreeParameters& operator=(const FCompactStateTreeParameters&) = default;`
- L1051 _public prototype_ `FCompactStateTreeParameters& operator=(FCompactStateTreeParameters&&) = default;`
- L1054 _public function_ `explicit FCompactStateTreeParameters(FInstancedPropertyBag InParameters) : Parameters(MoveTemp(InParameters))`
- L1059 _public function_ `explicit FCompactStateTreeParameters(FInstancedStruct InParameters) : InstancedParameters(MoveTemp(InParameters))`
- L1065 _public function_ `FConstStructView GetValue() const`
- L1072 _public function_ `FStructView GetMutableValue()`
- L1083 _private member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY()` — To hold a PropertyBag for internal state parameters.
- L1087 _private member_ `FInstancedStruct InstancedParameters;` — `UPROPERTY()` — To hold a UScriptStruct for a linked state tree asset.

#### enum `EStateTreeExternalDataRequirement`  
`enum class EStateTreeExternalDataRequirement : uint8`  
_L1091-1095_
- reflection: `UENUM()`
- L1093 _public enumerator_ `Required` — StateTree cannot be executed if the data is not present.
- L1094 _public enumerator_ `Optional` — Data is optional for StateTree execution.

#### enum `EStateTreePropertyUsage`  
`enum class EStateTreePropertyUsage : uint8`  
_L1099-1106_
- reflection: `UENUM()`
- L1101 _public enumerator_ `Invalid`
- L1102 _public enumerator_ `Context`
- L1103 _public enumerator_ `Input`
- L1104 _public enumerator_ `Parameter`
- L1105 _public enumerator_ `Output`

#### struct `FStateTreeStateIdToHandle`  
`struct FStateTreeStateIdToHandle`  
_L1112-1128_
- reflection: `USTRUCT()`
- desc: Pair of state guid and its associated state handle created at compilation.
- L1116 _public prototype_ `FStateTreeStateIdToHandle() = default;`
- L1117 _public function_ `explicit FStateTreeStateIdToHandle(const FGuid& Id, const FStateTreeStateHandle Handle) : Id(Id) , Handle(Handle)`
- L1124 _public member_ `FGuid Id;` — `UPROPERTY()`
- L1127 _public member_ `FStateTreeStateHandle Handle;` — `UPROPERTY()`

#### struct `FStateTreeNodeIdToIndex`  
`struct FStateTreeNodeIdToIndex`  
_L1134-1150_
- reflection: `USTRUCT()`
- desc: Pair of node id and its associated node index created at compilation.
- L1138 _public prototype_ `FStateTreeNodeIdToIndex() = default;`
- L1139 _public function_ `explicit FStateTreeNodeIdToIndex(const FGuid& Id, const FStateTreeIndex16 Index) : Id(Id) , Index(Index)`
- L1146 _public member_ `FGuid Id;` — `UPROPERTY()`
- L1149 _public member_ `FStateTreeIndex16 Index;` — `UPROPERTY()`

#### struct `FStateTreeTransitionIdToIndex`  
`struct FStateTreeTransitionIdToIndex`  
_L1156-1172_
- reflection: `USTRUCT()`
- desc: Pair of transition id and its associated compact transition index created at compilation.
- L1160 _public prototype_ `FStateTreeTransitionIdToIndex() = default;`
- L1161 _public function_ `explicit FStateTreeTransitionIdToIndex(const FGuid& Id, const FStateTreeIndex16 Index) : Id(Id) , Index(Index)`
- L1168 _public member_ `FGuid Id;` — `UPROPERTY()`
- L1171 _public member_ `FStateTreeIndex16 Index;` — `UPROPERTY()`

#### struct `FStateTreeStructRef`  
`struct FStateTreeStructRef`  
_L1199-1256_
- reflection: `USTRUCT(BlueprintType)`
- desc: StateTree struct ref allows to get a reference/pointer to a specified type via property binding. It is useful for referencing larger properties to avoid copies of the data, or to be able to write to a bounds property. The expected type of the reference should be set in "BaseStruct" meta tag. Example: USTRUCT() struct FAwesomeTaskInstanceData { GENERATED_BODY() UPROPERTY(VisibleAnywhere, Category = Input, meta = (BaseStruct = "/Script/AwesomeModule.AwesomeData")) FStateTreeStructRef Data; }; if (const FAwesomeData* Awesome = InstanceData.Data.GetPtr<FAwesomeData>()) { ... }
- L1203 _public prototype_ `FStateTreeStructRef() = default;`
- L1206 _public function_ `bool IsValid() const` — @return true if the reference is valid (safe to use the reference getters).
- L1212 _public function_ `void Set(FStructView NewData)` — Sets the struct ref (used by property copy)
- L1219 _public function_ `template <typename T> const T& Get() const` — Returns const reference to the struct, this getter assumes that all data is valid.
- L1226 _public function_ `template <typename T> const T* GetPtr() const` — Returns const pointer to the struct, or nullptr if cast is not valid.
- L1233 _public function_ `template <typename T> T& GetMutable()` — Returns mutable reference to the struct, this getter assumes that all data is valid.
- L1240 _public function_ `template <typename T> T* GetMutablePtr()` — Returns mutable pointer to the struct, or nullptr if cast is not valid.
- L1246 _public function_ `const UScriptStruct* GetScriptStruct() const` — @return Struct describing the data type.
- L1252 _public prototype_ `bool ExportTextItem(FString& ValueStr, const FStateTreeStructRef& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const;`
- L1255 _protected member_ `FStructView Data;`
- L1258 _function_ `inline bool FStateTreeStructRef::ExportTextItem(FString& ValueStr, const FStateTreeStructRef& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FStateTreeStructRef> : TStructOpsTypeTraitsBase2<FStateTreeStructRef>`  
_L1270-1276_
- inherits: `TStructOpsTypeTraitsBase2<FStateTreeStructRef>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L1273-1275_

#### struct `FStateTreeDataView`  
`struct FStateTreeDataView : public FPropertyBindingDataView`  
_L1283-1286_
- inherits: `FPropertyBindingDataView`
- desc: Helper struct to facilitate transition to FPropertyBindingDataView in the StateTree module. @see FPropertyBindingDataView

#### struct `FStateTreeStateLink`  
`struct FStateTreeStateLink`  
_L1292-1337_
- reflection: `USTRUCT(BlueprintType)`
- desc: Link to another state in StateTree
- L1296 _public prototype_ `FStateTreeStateLink() = default;`
- L1299 _public function_ `FStateTreeStateLink(const EStateTreeTransitionType InType) : LinkType(InType)`
- L1303 _public prototype_ `FStateTreeStateLink(const FStateTreeStateLink& Other) = default;`
- L1304 _public prototype_ `FStateTreeStateLink(FStateTreeStateLink&& Other) = default;`
- L1305 _public prototype_ `FStateTreeStateLink& operator=(FStateTreeStateLink const& Other) = default;`
- L1306 _public prototype_ `FStateTreeStateLink& operator=(FStateTreeStateLink&& Other) = default;`
- L1309 _public prototype_ `bool Serialize(FStructuredArchive::FSlot Slot);`
- L1310 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L1315 _public member_ `FName Name;` — `UPROPERTY(EditDefaultsOnly, Category = "Link")` — Name of the state at the time of linking, used for error reporting.
- L1319 _public member_ `FGuid ID;` — `UPROPERTY(EditDefaultsOnly, Category = "Link")` — ID of the state linked to.
- L1323 _public member_ `EStateTreeTransitionType LinkType = EStateTreeTransitionType::None;` — `UPROPERTY(EditDefaultsOnly, Category = "Link")` — Type of the transition, used at edit time to describe e.g. next state (which is calculated at compile time).
- L1327 _public member_ `EStateTreeTransitionType Type_DEPRECATED = EStateTreeTransitionType::GotoState;` — `UE_DEPRECATED(all, "Use LinkType instead.")` — `UPROPERTY()`
- L1332 _public member_ `FStateTreeStateHandle StateHandle;` — `UPROPERTY()` — Handle of the linked state.
- L1336 _public member_ `EStateTreeSelectionFallback Fallback = EStateTreeSelectionFallback::None;` — `UPROPERTY()` — Fallback of the transition if it fails to select the target state

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FStateTreeStateLink> : public TStructOpsTypeTraitsBase2<FStateTreeStateLink>`  
_L1340-1347_
- inherits: `TStructOpsTypeTraitsBase2<FStateTreeStateLink>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L1343-1346_

#### Free symbols / members of external scopes

- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStateTree, Warning, All);`
- L20 _macro_ `#define WITH_STATETREE_DEBUG (!(UE_BUILD_SHIPPING || UE_BUILD_SHIPPING_WITH_EDITOR || UE_BUILD_TEST) && 1)`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace StateTree` (scope `UE`)
- L28 _variable_ `inline constexpr int32 MaxExpressionIndent = 4;` (scope `UE::StateTree`)
- L30 _variable_ `inline const FName SchemaTag(TEXT("Sche` (scope `UE::StateTree`)
- L32 _variable_ `inline const FName SchemaCanBeOverridenTag(TEXT("Sche` (scope `UE::StateTree`)
- L34 _namespace_ `namespace Colors` (scope `UE::StateTree`)
- L37 _externvar_ `extern const FColor Grey;` (scope `UE::StateTree::Colors`) — Common and consistent colors to be used with State Tree nodes.
- L38 _externvar_ `extern const FColor DarkGrey;` (scope `UE::StateTree::Colors`)
- L39 _externvar_ `extern const FColor Red;` (scope `UE::StateTree::Colors`)
- L40 _externvar_ `extern const FColor DarkRed;` (scope `UE::StateTree::Colors`)
- L41 _externvar_ `extern const FColor Orange;` (scope `UE::StateTree::Colors`)
- L42 _externvar_ `extern const FColor DarkOrange;` (scope `UE::StateTree::Colors`)
- L43 _externvar_ `extern const FColor Yellow;` (scope `UE::StateTree::Colors`)
- L44 _externvar_ `extern const FColor DarkYellow;` (scope `UE::StateTree::Colors`)
- L45 _externvar_ `extern const FColor Green;` (scope `UE::StateTree::Colors`)
- L46 _externvar_ `extern const FColor DarkGreen;` (scope `UE::StateTree::Colors`)
- L47 _externvar_ `extern const FColor Cyan;` (scope `UE::StateTree::Colors`)
- L48 _externvar_ `extern const FColor DarkCyan;` (scope `UE::StateTree::Colors`)
- L49 _externvar_ `extern const FColor Blue;` (scope `UE::StateTree::Colors`)
- L50 _externvar_ `extern const FColor DarkBlue;` (scope `UE::StateTree::Colors`)
- L51 _externvar_ `extern const FColor Purple;` (scope `UE::StateTree::Colors`)
- L52 _externvar_ `extern const FColor DarkPurple;` (scope `UE::StateTree::Colors`)
- L53 _externvar_ `extern const FColor Magenta;` (scope `UE::StateTree::Colors`)
- L54 _externvar_ `extern const FColor DarkMagenta;` (scope `UE::StateTree::Colors`)
- L55 _externvar_ `extern const FColor Bronze;` (scope `UE::StateTree::Colors`)
- L56 _externvar_ `extern const FColor DarkBronze;` (scope `UE::StateTree::Colors`)
- L133 _prototype_ `ENUM_CLASS_FLAGS(EStateTreeStateSelectionRules);`
- L200 _namespace_ `namespace UE`
- L200 _namespace_ `namespace StateTree` (scope `UE`)
- L202 _function_ `static bool IsSelectionBehaviorUsingUtility(const EStateTreeStateSelectionBehavior Value)` (scope `UE::StateTree`)
- L267 _function_ `inline bool operator<(const EStateTreeTransitionPriority Lhs, const EStateTreeTransitionPriority Rhs)`
- L268 _function_ `inline bool operator>(const EStateTreeTransitionPriority Lhs, const EStateTreeTransitionPriority Rhs)`
- L269 _function_ `inline bool operator<=(const EStateTreeTransitionPriority Lhs, const EStateTreeTransitionPriority Rhs)`
- L270 _function_ `inline bool operator>=(const EStateTreeTransitionPriority Lhs, const EStateTreeTransitionPriority Rhs)`
- L271 _function_ `inline bool operator==(const EStateTreeTransitionPriority Lhs, const EStateTreeTransitionPriority Rhs)`
- L272 _function_ `inline bool operator!=(const EStateTreeTransitionPriority Lhs, const EStateTreeTransitionPriority Rhs)`
- L297 _function_ `friend inline uint32 GetTypeHash(const FStateTreeStateHandle& Handle)`
- L398 _namespace_ `namespace UE`
- L398 _namespace_ `namespace StateTree` (scope `UE`)
- L400 _function_ `static EStateTreeDataSourceType CastToDataSourceType(EStateTreeParameterDataType Value)` (scope `UE::StateTree`)
- L426 _function_ `friend inline uint32 GetTypeHash(const FStateTreeDataHandle& Handle)`
- L517 _namespace_ `namespace UE`
- L517 _namespace_ `namespace StateTree` (scope `UE`)
- L517 _namespace_ `namespace InstanceData` (scope `UE::StateTree`)
- L1274 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anon884c9b6a0103`)
- L1344 _enumerator_ `WithStructuredSerializer = true` (scope `TStructOpsTypeTraits::__anon884c9b6a0203`)
- L1345 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon884c9b6a0203`)
- L1357 _macro_ `#define UE_STATETREE_CONSTRUCTED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA(Type) \` — Helper macro to define instance data as a trivial type. The type can be safely copied using memcpy and don't require special copy construction or destruction. It requires a default constructor. The type defined default values. ex: struct { int32 A = 3; }; This is not appropriate for element types that require non-trivial copy constructor/assignment  or non-trivial move constructor/assignment. ex: struct { TObjectPtr<UObject> A; }; // No. TObjectPtr has a non-trivial copy constructor when UE_OBJECT_PTR_GC_BARRIER is enabled.
- L1376 _macro_ `#define UE_STATETREE_ZEROED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA(Type) \` — Helper macro to define instance data as a trivial type. The type can be safely copied using memcpy and don't require special construction or destruction. The memory will be memset to 0. ex: struct { int32 A = 0; }; This is not appropriate for element types that require construction. ex: struct { FFrameRate A; }; // No. FFrameRate has a constructor.
- L1388 _macro_ `#define STATETREE_POD_INSTANCEDATA(Type) UE_DEPRECATED_MACRO(5.8, "Use UE_STATETREE_CONSTRUCTED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA or UE_STATETREE_ZEROED_TRIVIALLY_COPIED_NO_DESTRUCTOR_INSTANCEDATA."); UE_STATETREE_ZEROED_TRIVIALLY`

### `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/Tasks/StateTreeRunParallelStateTreeTask.h` (Public)


#### struct `FStateTreeRunParallelStateTreeTaskInstanceData`  
`struct FStateTreeRunParallelStateTreeTaskInstanceData`  
_L14-35_
- reflection: `USTRUCT()`
- L20 _public prototype_ `void UpdateGlobalParameters();` — Copies the global parameters from the parent tree to the parallel tree's root parameters.
- L25 _public member_ `FStateTreeReference StateTree;` — `UPROPERTY(EditAnywhere, Category = "Parameter", DisplayName = "State Tree", meta=(SchemaCanBeOverriden))` — State tree and parameters that will be run when this task is started.
- L28 _public member_ `FStateTreeInstanceData TreeInstanceData;` — `UPROPERTY(Transient)`
- L31 _public member_ `TObjectPtr<const UStateTree> RunningStateTree = nullptr;` — `UPROPERTY(Transient)`
- L34 _public member_ `UE::StateTree::FScheduledTickHandle ScheduledTickHandle;` — The handle of the scheduled tick.

#### struct `FStateTreeRunParallelStateTreeExecutionExtension`  
`struct FStateTreeRunParallelStateTreeExecutionExtension : public FStateTreeExecutionExtension`  
_L38-47_
- reflection: `USTRUCT()`
- inherits: `FStateTreeExecutionExtension`
- L43 _public prototype_ `virtual void ScheduleNextTick(const FContextParameters& Context, const FNextTickArguments& Args) override;`
- L45 _public member_ `FStateTreeWeakExecutionContext WeakExecutionContext;`
- L46 _public member_ `UE::StateTree::FScheduledTickHandle ScheduledTickHandle;`

#### struct `FStateTreeRunParallelStateTreeTask`  
`struct FStateTreeRunParallelStateTreeTask : public FStateTreeTaskCommonBase`  
_L55-130_
- reflection: `USTRUCT(meta = (DisplayName = "Run Parallel Tree", Category = "Common"))`
- inherits: `FStateTreeTaskCommonBase`
- desc: Task that will run another state tree in the current state while allowing the current tree to continue selection and process of child state. It will succeed, fail or run depending on the result of the parallel tree. Less efficient then Linked Asset state, it has the advantage of allowing multiple trees to run in parallel.
- L58 _public typedef_ `using FInstanceDataType = FStateTreeRunParallelStateTreeTaskInstanceData;`
- L60 _public prototype_ `FStateTreeRunParallelStateTreeTask();`
- L64 _public function_ `void SetEventHandlingPriority(const EStateTreeTransitionPriority NewPriority)` — Sets event handling priority
- L71 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L73 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transitions) const override;`
- L74 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L75 _protected prototype_ `virtual void TriggerTransitions(FStateTreeExecutionContext& Context) const override;`
- L76 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L78 _protected prototype_ `virtual void PostLoad(FStateTreeDataView InstanceDataView) override;`
- L81 _protected prototype_ `virtual EDataValidationResult Compile(UE::StateTree::ICompileNodeContext& Context) override;`
- L82 _protected prototype_ `virtual void PostEditInstanceDataChangeChainProperty(const FPropertyChangedChainEvent& PropertyChangedEvent, FStateTreeDataView InstanceDataView) override;`
- L83 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L84 _protected function_ `virtual FName GetIconName() const override`
- L88 _protected function_ `virtual FColor GetIconColor() const override`
- L94 _protected prototype_ `const FStateTreeReference& GetStateTreeToRun(FStateTreeExecutionContext& Context, FInstanceDataType& InstanceData) const;`
- L99 _public member_ `FGameplayTag StateTreeOverrideTag;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — If set the task will look at the linked state tree override to replace the state tree it's running.
- L107 _public member_ `bool bShouldCopyParametersOnTick = false;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — If set to true, copy the values of the state tree global parameters before calling Tick(). Only copy if the state tree was not overridden. Enable when you have bound properties that you want to update during the execution of the state tree.
- L115 _public member_ `bool bShouldCopyParametersOnExitState = false;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — If set to true, copy the values of the state tree global parameters before calling ExitState() Only copy if the state tree was not overridden. Enable when you have bound properties that you want to update during the execution of the state tree.
- L128 _protected member_ `EStateTreeTransitionPriority EventHandlingPriority = EStateTreeTransitionPriority::Normal;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — At what priority the events should be handled in the parallel State Tree. If set to 'Normal' the order of the States in the State Tree will define the handling order. If the priority is set to Low, the main tree is let to handle the transitions first. If set to High or above, the parallel tree has change to handle events first. If multiple tasks has same priority, the State order of the States defines the handling order. The tree handling order is: States and handle from leaf to root, tasks before and handled before transitions per State.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API STATETREEMODULE_API`
