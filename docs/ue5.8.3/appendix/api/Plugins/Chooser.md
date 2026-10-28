# Plugins / Chooser

- module root: `Plugins/Chooser/Source/Chooser`
- headers: 44; symbols: 1040
- symbol kinds: class=32, delegate=4, enum=14, enumerator=46, function=275, macro=35, member=287, namespace=4, prototype=257, struct=83, typedef=2, union=1
- PrivateDependencyModuleNames: AnimGraphRuntime, AnimationCore, BlendStack, Core, CoreUObject, Engine, GameplayTags, RewindDebuggerRuntimeInterface, TraceLog
- PublicDependencyModuleNames: 

### `Plugins/Chooser/Source/Chooser/Internal/AnimNode_ChooserPlayer.h` (Internal)


#### struct `FAnimNode_ChooserPlayer`  
`struct FAnimNode_ChooserPlayer : public FAnimNode_BlendStack_Standalone #if CPP , public IHasContextClass #endif`  
_L16-113_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendStack_Standalone,IHasContextClass`
- L23 _public prototype_ `FAnimNode_ChooserPlayer();`
- L26 _public function_ `virtual TConstArrayView<FInstancedStruct> GetContextData() const override`
- L30 _public member_ `EChooserEvaluationFrequency EvaluationFrequency = EChooserEvaluationFrequency::OnBecomeRelevant;` — `UPROPERTY(EditAnywhere, Category = "Chooser")` — How often the chooser should be evaluated
- L34 _public member_ `FInstancedStruct Chooser;` — `UPROPERTY(EditAnywhere, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ObjectChooserBase"), Category = "Chooser")` — Type of chooser logic to use: Use "Evaluate Chooser" for chooser table evaluation, and "Lookup Proxy" for proxy table lookups
- L38 _public member_ `TObjectPtr<UMirrorDataTable> MirrorDataTable;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if set and bMirrored MirrorDataTable will be used for mirroring the aniamtion
- L42 _public member_ `float BlendSpaceX = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))` — requested blend space blend X parameter (if AnimationAsset is a blend space)
- L46 _public member_ `float BlendSpaceY = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))` — requested blend space blend Y parameter (if AnimationAsset is a blend space)
- L49 _public member_ `bool bUpdateAllActiveBlendSpaces = true;` — Should BlendSpaceParameters be applied to all blend spaces, including ones that are in the process of blending out.
- L53 _public member_ `FChooserPlayerSettings DefaultSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))` — Settings when starting an animation - these can be overridden per animation asset by the chooser itself
- L56 _public member_ `TArray<FInstancedStruct> ChooserContextDefinition;` — `UPROPERTY()`
- L60 _public member_ `bool bStartFromMatchingPose = false;` — `UPROPERTY(EditAnywhere, Category = PoseMatching, meta = (PinHiddenByDefault))` — Use pose matching to choose the start position. Requires PoseSearch plugin.
- L63 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L64 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L68 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;` — FAnimNode_AssetPlayerBase interface
- L69 _public prototype_ `virtual FName GetGroupName() const override;`
- L70 _public prototype_ `virtual EAnimGroupRole::Type GetGroupRole() const override;`
- L71 _public prototype_ `virtual EAnimSyncMethod GetGroupMethod() const override;`
- L72 _public prototype_ `virtual bool GetIgnoreForRelevancyTest() const override;`
- L73 _public prototype_ `virtual bool IsLooping() const override;`
- L74 _public prototype_ `virtual bool SetGroupName(FName InGroupName) override;`
- L75 _public prototype_ `virtual bool SetGroupRole(EAnimGroupRole::Type InRole) override;`
- L76 _public prototype_ `virtual bool SetGroupMethod(EAnimSyncMethod InMethod) override;`
- L77 _public prototype_ `virtual bool SetIgnoreForRelevancyTest(bool bInIgnoreForRelevancyTest) override;`
- L81 _private prototype_ `UAnimationAsset* ChooseAsset(const FAnimationUpdateContext& Context);`
- L82 _private member_ `FChooserPlayerSettings Settings;`
- L83 _private member_ `UAnimationAsset* CurrentAsset = nullptr;`
- L84 _private member_ `float CurrentStartTime = 0;`
- L85 _private member_ `bool CurrentMirror = false;`
- L86 _private member_ `bool bInitialized = false;`
- L87 _private member_ `uint32 CurrentCurveOverridesHash = 0;`
- L90 _private member_ `FGraphTraversalCounter UpdateCounter;` — Update Counter for detecting being relevant
- L97 _private member_ `FName GroupName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — The group name that we synchronize with (NAME_None if it is not part of any group). Note that this is the name of the group used to sync the output of this node - it will not force syncing of animations contained by it.
- L102 _private member_ `TEnumAsByte<EAnimGroupRole::Type> GroupRole = EAnimGroupRole::CanBeLeader;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — The role this node can assume within the group (ignored if GroupName is not set). Note that this is the role of the output of this node, not of animations contained by it.
- L107 _private member_ `EAnimSyncMethod Method = EAnimSyncMethod::DoNotSync;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — How this node will synchronize with other animations. Note that this determines how the output of this node is used for synchronization, not of animations contained by it.
- L111 _private member_ `bool bIgnoreForRelevancyTest = false;` — `UPROPERTY(EditAnywhere, Category = Relevancy, meta = (FoldProperty, PinHiddenByDefault))` — If true, "Relevant anim" nodes that look for the highest weighted animation in a state will ignore this node

### `Plugins/Chooser/Source/Chooser/Private/ChooserModule.h` (Private)


#### class `FChooserModule`  
`class FChooserModule : public IModuleInterface`  
_L9-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `FRewindDebuggerChooserRuntime ChooserExtension;`

### `Plugins/Chooser/Source/Chooser/Private/ConsoleVariableParameters.h` (Private)


#### struct `FBoolCVarProperty`  
`struct FBoolCVarProperty : public FChooserParameterBoolBase`  
_L12-23_
- reflection: `USTRUCT(DisplayName = "Bool CVar Param")`
- inherits: `FChooserParameterBoolBase`
- L18 _public member_ `FString VariableName;` — `UPROPERTY(EditAnywhere, Category="Variable")`
- L20 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, bool& OutResult) const override;`
- L21 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, bool InValue) const override;`
- L22 _public prototype_ `virtual void GetDisplayName(FText& OutName) const override;`

#### struct `FFloatCVarProperty`  
`struct FFloatCVarProperty : public FChooserParameterFloatBase`  
_L26-37_
- reflection: `USTRUCT(DisplayName = "Float CVar Param")`
- inherits: `FChooserParameterFloatBase`
- L32 _public member_ `FString VariableName;` — `UPROPERTY(EditAnywhere, Category="Variable")`
- L34 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, double& OutResult) const override;`
- L35 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, double InValue) const override;`
- L36 _public prototype_ `virtual void GetDisplayName(FText& OutName) const override;`

#### struct `FEnumCVarProperty`  
`struct FEnumCVarProperty : public FChooserParameterEnumBase`  
_L40-60_
- reflection: `USTRUCT(DisplayName = "Enum CVar Param")`
- inherits: `FChooserParameterEnumBase`
- L47 _public member_ `FString VariableName;` — `UPROPERTY(EditAnywhere, Category="Variable")`
- L50 _public member_ `TObjectPtr<UEnum> Enum;` — `UPROPERTY(EditAnywhere, Category="Variable")`
- L52 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, uint8& OutResult) const override;`
- L53 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, uint8 InValue) const override;`
- L55 _public prototype_ `virtual void GetDisplayName(FText& OutName) const override;`
- L58 _public function_ `virtual const UEnum* GetEnum() const override`

### `Plugins/Chooser/Source/Chooser/Private/RewindDebuggerChooserRuntime.h` (Private)


#### class `FRewindDebuggerChooserRuntime`  
`class FRewindDebuggerChooserRuntime : public IRewindDebuggerRuntimeExtension`  
_L9-14_
- inherits: `IRewindDebuggerRuntimeExtension`
- L12 _public prototype_ `virtual void RecordingStarted() override;`
- L13 _public prototype_ `virtual void RecordingStopped() override;`

### `Plugins/Chooser/Source/Chooser/Public/BoolColumn.h` (Public)


#### enum `EBoolColumnCellValue`  
`enum class EBoolColumnCellValue : uint8`  
_L15-20_
- reflection: `UENUM()`
- L17 _public enumerator_ `MatchFalse = 0`
- L18 _public enumerator_ `MatchTrue = 1`
- L19 _public enumerator_ `MatchAny = 2`

#### struct `FBoolContextProperty`  
`struct FBoolContextProperty : public FChooserParameterBoolBase`  
_L24-49_
- reflection: `USTRUCT(DisplayName = "Bool Property Binding")`
- inherits: `FChooserParameterBoolBase`
- L30 _public member_ `TArray<FName> PropertyBindingChain_DEPRECATED;` — `UPROPERTY()`
- L33 _public member_ `FChooserPropertyBinding Binding;` — `UPROPERTY(EditAnywhere, Meta = (BindingType = "bool", BindingAllowFunctions = "true", BindingColor = "BooleanPinTypeColor"), Category = "Binding")`
- L35 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, bool& OutResult) const override;`
- L36 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, bool InValue) const override;`
- L38 _public function_ `virtual void PostLoad() override`
- L47 _public prototype_ `CHOOSER_PARAMETER_BOILERPLATE();`

#### struct `FBoolColumn`  
`struct FBoolColumn : public FChooserColumnBase`  
_L52-113_
- reflection: `USTRUCT(DisplayName = "Bool", Meta = (Category = "Filter", Tooltip = "A column that filters rows based on the value of a Bool."))`
- inherits: `FChooserColumnBase`
- L56 _public prototype_ `FBoolColumn();`
- L59 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterBoolBase", ToolTip="The bool property this column will filter based on" ), Category = "Data")`
- L63 _public member_ `TArray<bool> RowValues_DEPRECATED;` — `UPROPERTY()`
- L66 _public member_ `EBoolColumnCellValue DefaultRowValue = EBoolColumnCellValue::MatchAny;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L70 _public member_ `TArray<EBoolColumnCellValue> RowValuesWithAny;` — `UPROPERTY(EditAnywhere, Category= "Data", DisplayName="RowValues")`
- L72 _public prototype_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut) const override;`
- L75 _public member_ `mutable bool TestValue = false;`
- L76 _public function_ `virtual bool EditorTestFilter(int32 RowIndex) const override`
- L81 _public function_ `virtual void SetTestValue(TArrayView<const uint8> Value) override`
- L87 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L88 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L91 _public function_ `virtual void PostLoad() override`
- L112 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE2(FChooserParameterBoolBase, RowValuesWithAny);`

#### class `UDEPRECATED_ChooserParameterBool_ContextProperty`  
`class UDEPRECATED_ChooserParameterBool_ContextProperty : public UObject, public IChooserParameterBool`  
_L118-131_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "LiveLink", deprecated)`
- inherits: `UObject,IChooserParameterBool`
- L123 _public member_ `TArray<FName> PropertyBindingChain;` — `UPROPERTY()`
- L125 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const override`

#### class `UDEPRECATED_ChooserColumnBool`  
`class UDEPRECATED_ChooserColumnBool : public UObject, public IChooserColumn`  
_L134-168_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "LiveLink", deprecated)`
- inherits: `UObject,IChooserColumn`
- L138 _public function_ `UDEPRECATED_ChooserColumnBool()`
- L139 _public function_ `UDEPRECATED_ChooserColumnBool(const FObjectInitializer& ObjectInitializer)`
- L145 _public member_ `TScriptInterface<IChooserParameterBool> InputValue;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L150 _public member_ `TArray<bool> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L152 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/Chooser.h` (Public)


#### class `UChooserTable`  
`class UChooserTable : public UChooserSignature`  
_L22-218_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UChooserSignature`
- desc: Data table used to choose an asset based on input parameters
- L26 _public function_ `UChooserTable()`
- L27 _public prototype_ `virtual void BeginDestroy() override;`
- L29 _public prototype_ `virtual void PostLoad() override;`
- L30 _public prototype_ `virtual void Compile(bool bForce = false) override;`
- L31 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L34 _public prototype_ `void RemoveDisabledData();`
- L35 _public prototype_ `void PopulateCookedData(bool bCooking);`
- L36 _public prototype_ `void DeleteNestedChooser(UChooserTable* NestedChooser);`
- L37 _public prototype_ `void DeleteNestedObject(UObject* ObjectToDelete);`
- L40 _public function_ `bool IsRowDisabled(int32 RowIndex) const`
- L49 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L51 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L53 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L55 _public function_ `void OnDependentStructChanged(UUserDefinedStruct* Blueprint)`
- L56 _public function_ `void OnDependencyCompiled(UBlueprint* Blueprint)`
- L57 _public prototype_ `virtual void AddCompileDependency(const UStruct* Struct) override;`
- L58 _public member_ `FChooserOutputObjectTypeChanged OnOutputObjectTypeChanged;`
- L60 _public prototype_ `virtual void PostEditUndo() override;`
- L61 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L64 _public function_ `void SetDebugSelectedRow(int32 Index) const`
- L65 _public function_ `void SetDebugSelectedRows(const TArray<int32>& Indices) const`
- L66 _public function_ `const TArray<int32>& GetDebugSelectedRows() const`
- L67 _public function_ `bool HasDebugTarget() const`
- L69 _public function_ `void SetDebugTarget(FString Name)`
- L70 _public function_ `void ResetDebugTarget()`
- L71 _public function_ `const FString& GetDebugTargetName() const`
- L74 _public prototype_ `void AddRecentContextObject(const FString& ObjectName) const;`
- L75 _public prototype_ `void IterateRecentContextObjects(TFunction<void(const FString&)> Callback) const;`
- L76 _public prototype_ `void UpdateDebugging(FChooserEvaluationContext& Context) const;`
- L78 _public member_ `static const FName PropertyNamesTag;`
- L79 _public member_ `static const FString PropertyTagDelimiter;`
- L82 _public function_ `void SetEnableDebugTesting(bool bValue)`
- L87 _public function_ `bool GetEnableDebugTesting() const`
- L92 _public function_ `void SetDebugTestValuesValid(bool bValue) const`
- L97 _public function_ `bool GetDebugTestValuesValid() const`
- L104 _private member_ `bool bEnableDebugTesting = false;` — enable display of which cells pass/fail based on current TestValue for each column
- L105 _private member_ `mutable bool bDebugTestValuesValid = false;`
- L108 _private member_ `UClass* CachedPreviousOutputObjectType = nullptr;` — caching the OutputObjectType and ContextObjectType so that on Undo, we can tell if we should fire the changed delegate
- L109 _private member_ `EObjectChooserResultType CachedPreviousResultType = EObjectChooserResultType::ObjectResult;`
- L112 _private member_ `mutable TArray<FString> RecentContextObjects;` — objects this chooser has been recently evaluated on
- L113 _private member_ `mutable FCriticalSection DebugLock;`
- L115 _private member_ `mutable TWeakObjectPtr<const UObject> DebugTarget;` — reference to the UObject in PIE  which we want to get debug info for
- L116 _private member_ `FString DebugTargetName;`
- L119 _private member_ `mutable TArray<int32> DebugSelectedRows;` — Rows which were selected last time this chooser was evaluated on DebugTarget
- L121 _private member_ `TArray<TWeakObjectPtr<UStruct>> CompileDependencies;`
- L128 _public member_ `TArray<TScriptInterface<IObjectChooser>> Results_DEPRECATED;` — `UPROPERTY()` — deprecated UObject Results
- L132 _public member_ `TObjectPtr<UClass> ContextObjectType_DEPRECATED;` — `UPROPERTY()` — deprecated single context object
- L136 _public member_ `TArray<TScriptInterface<IChooserColumn>> Columns_DEPRECATED;` — `UPROPERTY()` — deprecated UObject Columns
- L140 _public function_ `UChooserTable* GetRootChooser()`
- L141 _public function_ `const UChooserTable* GetRootChooser() const`
- L143 _public function_ `UChooserTable* GetContextOwner()`
- L144 _public function_ `const UChooserTable* GetContextOwner() const`
- L147 _public member_ `TObjectPtr<UChooserTable> RootChooser;` — `UPROPERTY()`
- L151 _public member_ `FInstancedStruct FallbackResult;` — `UPROPERTY()` — FallbackResult will be used as the Result if there are no rows in the chooser which pass all filters.  If FallbackResult is not assigned, then the Chooser will return null in that case.
- L154 _public function_ `virtual TConstArrayView<FInstancedStruct> GetContextData() const override` — IHasContextClass implementation
- L159 _public member_ `TArray<FInstancedStruct> ResultsStructs;` — `UPROPERTY()` — Each possible Result (Rows of chooser table)
- L162 _public member_ `TArray<bool> DisabledRows;` — `UPROPERTY()`
- L165 _public member_ `TArray<TObjectPtr<UChooserTable>> NestedChoosers;` — `UPROPERTY()`
- L168 _public member_ `TArray<TObjectPtr<UObject>> NestedObjects;` — `UPROPERTY()`
- L170 _public prototype_ `void AddNestedChooser(UChooserTable* Chooser);`
- L171 _public prototype_ `void RemoveNestedChooser(UChooserTable* Chooser);`
- L172 _public member_ `FSimpleMulticastDelegate NestedChoosersChanged;`
- L174 _public prototype_ `void AddNestedObject(UObject* Object);`
- L175 _public prototype_ `void RemoveNestedObject(UObject* Object);`
- L176 _public member_ `FSimpleMulticastDelegate NestedObjectsChanged;`
- L180 _public member_ `TObjectPtr<UChooserTable> ParentTable;` — `UPROPERTY()` — deprecated in favor of RootChooser
- L183 _public member_ `float EditorResultsColumnWidth = 300;` — `UPROPERTY()`
- L186 _public member_ `uint32 Version = 0;` — `UPROPERTY()`
- L188 _public member_ `static constexpr int CurrentVersion = 3;`
- L191 _private member_ `bool bIsCookedPackage = false;`
- L197 _public prototype_ `bool ResultAssetFilter(const FAssetData& AssetData);` — `UFUNCTION()`
- L200 _public member_ `TArray<FInstancedStruct> CookedResults;` — `UPROPERTY()`
- L204 _public member_ `TArray<FInstancedStruct> ColumnsStructs;` — `UPROPERTY(EditAnywhere, NoClear, DisplayName = "Columns", Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserColumnBase"), Category = "Hidden")` — Columns which filter Results
- L206 _public function_ `bool IsCookedData() const`
- L214 _public prototype_ `static FObjectChooserBase::EIteratorStatus EvaluateChooser(FChooserEvaluationContext& Context, const UChooserTable* Chooser, FObjectChooserBase::FObjectChooserIteratorCallback Callback);`
- L215 _public prototype_ `static FObjectChooserBase::EIteratorStatus EvaluateChooser(FChooserEvaluationContext& Context, const UChooserTable* Chooser, FObjectChooserBase::FObjectChooserSoftObjectIteratorCallback Callback);`
- L216 _public prototype_ `static FObjectChooserBase::EIteratorStatus IterateChooser(FChooserEvaluationContext& Context, const UChooserTable* Chooser, FObjectChooserBase::FObjectChooserIteratorCallback Callback);`
- L217 _public prototype_ `static FObjectChooserBase::EIteratorStatus IterateChooser(const UChooserTable* Chooser, FObjectChooserBase::FObjectChooserIteratorCallback Callback);`

#### struct `FNestedChooser`  
`struct FNestedChooser : public FObjectChooserBase`  
_L221-238_
- reflection: `USTRUCT(DisplayName = "Nested Chooser", Meta = (Category = "Chooser", Tooltip = "Reference another ChooserTable embedded in this asset, which will be evaluated at runtime if this row is selected."))`
- inherits: `FObjectChooserBase`
- L225 _public prototype_ `virtual void ChooseObject(FChooserEvaluationContext& Context, TSoftObjectPtr<UObject>& Result) const final override;`
- L226 _public prototype_ `virtual UObject* ChooseObject(FChooserEvaluationContext& Context) const final override;`
- L227 _public prototype_ `virtual EIteratorStatus ChooseMulti(FChooserEvaluationContext &Context, FObjectChooserIteratorCallback Callback) const final override;`
- L228 _public prototype_ `virtual EIteratorStatus ChooseMulti(FChooserEvaluationContext &Context, FObjectChooserSoftObjectIteratorCallback Callback) const final override;`
- L229 _public prototype_ `virtual EIteratorStatus IterateObjects(FChooserEvaluationContext& Context, FObjectChooserIteratorCallback Callback) const final override;`
- L230 _public prototype_ `virtual void GetDebugName(FString& OutDebugName) const override;`
- L234 _public prototype_ `FNestedChooser();`
- L237 _public member_ `TObjectPtr<UChooserTable> Chooser;` — `UPROPERTY()`

#### struct `FEvaluateChooser`  
`struct FEvaluateChooser : public FObjectChooserBase`  
_L241-261_
- reflection: `USTRUCT(DisplayName = "Evaluate Chooser", Meta = (Category = "Chooser", Tooltip = "Reference another ChooserTable asset, which will be evaluated at runtime if this row is selected."))`
- inherits: `FObjectChooserBase`
- L244 _public prototype_ `virtual void ChooseObject(FChooserEvaluationContext& Context, TSoftObjectPtr<UObject>& Result) const final override;`
- L245 _public prototype_ `virtual UObject* ChooseObject(FChooserEvaluationContext& Context) const final override;`
- L246 _public prototype_ `virtual EIteratorStatus ChooseMulti(FChooserEvaluationContext &Context, FObjectChooserIteratorCallback Callback) const final override;`
- L247 _public prototype_ `virtual EIteratorStatus ChooseMulti(FChooserEvaluationContext &Context, FObjectChooserSoftObjectIteratorCallback Callback) const final override;`
- L248 _public prototype_ `virtual EIteratorStatus IterateObjects(FChooserEvaluationContext& Context, FObjectChooserIteratorCallback Callback) const final override;`
- L249 _public prototype_ `virtual void GetDebugName(FString& OutDebugName) const override;`
- L252 _public function_ `virtual UObject* GetReferencedObject() const override`
- L256 _public function_ `FEvaluateChooser() : Chooser(nullptr)`
- L257 _public function_ `FEvaluateChooser(TObjectPtr<UChooserTable> Table) : Chooser(Table)`
- L260 _public member_ `TObjectPtr<UChooserTable> Chooser;` — `UPROPERTY(EditAnywhere, Category="Parameters")`

#### class `UDEPRECATED_ObjectChooser_EvaluateChooser`  
`class UDEPRECATED_ObjectChooser_EvaluateChooser : public UObject, public IObjectChooser`  
_L265-277_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "LiveLink", deprecated)`
- inherits: `UObject,IObjectChooser`
- desc: Deprecated class for converting old data
- L269 _private member_ `TObjectPtr<UChooserTable> Chooser;` — `UPROPERTY(EditAnywhere, Category="Parameters")`
- L271 _private function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const`

#### class `UChooserColumnMenuContext`  
`class UChooserColumnMenuContext : public UObject`  
_L281-288_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L285 _public member_ `class FAssetEditorToolkit* Editor;`
- L286 _public member_ `TWeakObjectPtr<UChooserTable> Chooser;`
- L287 _public member_ `int ColumnIndex;`

### `Plugins/Chooser/Source/Chooser/Public/ChooserFunctionLibrary.h` (Public)


#### class `UChooserFunctionLibrary`  
`class UChooserFunctionLibrary : public UBlueprintFunctionLibrary`  
_L18-155_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Chooser Function Library
- L31 _public prototype_ `static UObject* EvaluateChooser(const UObject* ContextObject, const UChooserTable* ChooserTable, TSubclassOf<UObject> ObjectClass);` — `UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly = "true", DeterminesOutputType = "ObjectClass"))` — Evaluate a chooser table and return the selected UObject, or null @param ContextObject			(in) An Object from which the parameters to the Chooser Table will be read @param ChooserTable			(in) The ChooserTable asset @param ObjectClass			(in) Expected type of result object
- L41 _public prototype_ `static TArray<UObject*> EvaluateChooserMulti(const UObject* ContextObject, const UChooserTable* ChooserTable, TSubclassOf<UObject> ObjectClass);` — `UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly = "true", DeterminesOutputType = "ObjectClass"))` — Evaluate a chooser table and return the list of all selected UObjects @param ContextObject			(in) An Object from which the parameters to the Chooser Table will be read @param ChooserTable			(in) The ChooserTable asset @param ObjectClass			(in) Expected type of result objects
- L52 _public prototype_ `static UObject* EvaluateObjectChooserBase(UPARAM(Ref) struct FChooserEvaluationContext& Context,UPARAM(Ref) const struct FInstancedStruct& ObjectChooser, TSubclassOf<UObject> ObjectClass, bool bResultIsClass = false);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly = "true", DeterminesOutputType = "ObjectClass"))` — Evaluate an ObjectChooserBase and return the selected UObject, or null @param Context			(in) A struct reference to the chooser evaluation context @param ObjectChooser		(in) An Instanced struct containing an ObjectChooserBase implementation, such as EvaluateChooser, or EvaluateProxyAsset @param ObjectClass		(in) Expected type of result object (or the type of UClass if bResultIsClass is true) @param bResultIsClass		(in) The Object being returned is a UClass, and the ObjectClass parameter indicates what it must be a subclass of
- L56 _public prototype_ `static TSoftObjectPtr<UObject> EvaluateObjectChooserBaseSoft(UPARAM(Ref) struct FChooserEvaluationContext& Context,UPARAM(Ref) const struct FInstancedStruct& ObjectChooser, TSubclassOf<UObject> ObjectClass, bool bResultIsClass = false);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly = "true", DeterminesOutputType = "ObjectClass"))`
- L67 _public prototype_ `static TArray<UObject*> EvaluateObjectChooserBaseMulti(UPARAM(Ref) FChooserEvaluationContext& Context,UPARAM(Ref) const FInstancedStruct& ObjectChooser, TSubclassOf<UObject> ObjectClass, bool bResultIsClass = false);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly = "true", DeterminesOutputType = "ObjectClass"))` — Evaluate a chooser table and return all selected UObjects @param Context			(in) A struct reference to the chooser evaluation context @param ObjectChooser		(in) An Instanced struct containing an ObjectChooserBase implementation, such as EvaluateChooser, or EvaluateProxyAsset @param ObjectClass		(in) Expected type of result object (or the type of UClass if bResultIsClass is true) @param bResultIsClass		(in) The Object being returned is a UClass, and the ObjectClass parameter indicates what it must be a subclass of
- L70 _public prototype_ `static TArray<TSoftObjectPtr<UObject>> EvaluateObjectChooserBaseMultiSoft(UPARAM(Ref) FChooserEvaluationContext& Context,UPARAM(Ref) const FInstancedStruct& ObjectChooser, TSubclassOf<UObject> ObjectClass, bool bResultIsClass = false);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly = "true", DeterminesOutputType = "ObjectClass"))`
- L79 _public prototype_ `static void AddChooserObjectInput(UPARAM(Ref) FChooserEvaluationContext& Context, UObject* Object);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly = "true"))` — Add an Object to a ChooserEvaluation context @param Context			(in) A struct reference to the chooser evaluation context @param Object				(in) The Object to add
- L88 _public prototype_ `static UObject* GetChooserObjectInput(UPARAM(Ref) FChooserEvaluationContext& Context, int32 Index, TSubclassOf<UObject> ObjectClass);` — `UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe ,BlueprintInternalUseOnly = "true", DeterminesOutputType = "ObjectClass"))` — Get an Object from a ChooserEvaluation context @param Context			(in) A struct reference to the chooser evaluation context @param Index				(in) the context index to get the object from
- L98 _public prototype_ `static UObject* GetChooserObject(UPARAM(Ref) FChooserEvaluationContext& Context, TSubclassOf<UObject> ObjectClass);` — `UFUNCTION(BlueprintPure, Category = "Animation | Experimental", meta = (BlueprintThreadSafe))` — Get an Object from a ChooserEvaluation context by class or interface Experimental, this feature might be removed without warning, not for production use @param Context			(in) A struct reference to the chooser evaluation context @param ObjectClass		(in) the wanted object class or interface
- L107 _public prototype_ `static void AddChooserStructInput(UPARAM(Ref) FChooserEvaluationContext& Context, int32 Value);` — `UFUNCTION(BlueprintCallable, CustomThunk, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly = "true", CustomStructureParam = "Value"))` — Add a Struct to a ChooserEvaluation context @param Context			(in) A struct reference to the chooser evaluation context @param Object				(in) The Object to add
- L118 _public prototype_ `static void AddChooserStructInputOutput(UPARAM(Ref) FChooserEvaluationContext& Context, int32 Value);` — `UFUNCTION(BlueprintCallable, CustomThunk, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly = "true", CustomStructureParam = "Value"))` — Add a Struct with output to a ChooserEvaluation context @param Context			(in) A struct reference to the chooser evaluation context @param Object				(in) The Object to add
- L129 _public prototype_ `static void GetChooserStructOutput(UPARAM(Ref) FChooserEvaluationContext& Context, int Index, int32& Value);` — `UFUNCTION(BlueprintPure, CustomThunk, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly = "true", CustomStructureParam = "Value"))` — Get a Struct to a ChooserEvaluation context @param Context			(in) A struct reference to the chooser evaluation context @param Object				(in) The Object to add
- L140 _public prototype_ `static void GetChooserStructOutputArray(UPARAM(Ref) FChooserEvaluationContext& Context, int Index, TArray<int32>& Value);` — `UFUNCTION(BlueprintPure, CustomThunk, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly = "true", ArrayParm = "Value"))` — Get a Struct to a ChooserEvaluation context @param Context			(in) A struct reference to the chooser evaluation context @param Object				(in) The Object to add
- L150 _public prototype_ `static FInstancedStruct MakeEvaluateChooser(UChooserTable* Chooser);` — `UFUNCTION(BlueprintPure, Category = "Animation", meta = (BlueprintThreadSafe, BlueprintInternalUseOnly="true", NativeMakeFunc))` — Create an EvaluateChooser struct @param Chooser				(in) the ChooserTable asset to evaluate
- L154 _public prototype_ `static FChooserEvaluationContext MakeChooserEvaluationContext();` — `UFUNCTION(BlueprintCallable, Category = "Animation", meta = (BlueprintThreadSafe, BlueprintInternalUseOnly="true"))`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/ChooserIndexArray.h` (Public)


#### class `FChooserIndexArray`  
`class FChooserIndexArray`  
_L7-86_
- L25 _public function_ `FChooserIndexArray(FIndexData* InData, uint32 InMaxSize): Data(InData), MaxSize(InMaxSize), Size(0)`
- L27 _public typedef_ `typedef FIndexData* iterator;`
- L28 _public typedef_ `typedef const FIndexData* const_iterator;`
- L30 _public function_ `iterator begin()`
- L31 _public function_ `const_iterator begin() const`
- L32 _public function_ `iterator end()`
- L33 _public function_ `const_iterator end() const`
- L36 _public function_ `void Push(const FIndexData& Value)`
- L42 _public function_ `bool IsEmpty() const`
- L47 _public function_ `uint32 Num() const`
- L52 _public function_ `void SetNum(uint32 Num)`
- L58 _public function_ `FIndexData& operator [] (uint32 Index)`
- L64 _public function_ `const FIndexData& operator [] (uint32 Index) const`
- L70 _public function_ `void operator = (const FChooserIndexArray& Other)`
- L77 _public function_ `FIndexData* GetData()`
- L79 _public function_ `bool HasCosts() const`
- L80 _public function_ `void SetHasCosts()`
- L82 _private member_ `FIndexData* Data;`
- L83 _private member_ `uint32 MaxSize;`
- L84 _private member_ `uint32 Size;`
- L85 _private member_ `bool bHasCosts = false;`

#### struct `FChooserIndexArray::FIndexData`  
`struct FIndexData`  
_L10-23_
- L13 _public function_ `FIndexData(uint32 InIndex) : Index(InIndex), Cost(0)` — `UE_DEPRECATED(5.5,"This is a fallback conversion operator for Chooser Column implementations which expect index data to be a uint32. Please convert Chooser Column implementations to use FIndexData before the next release")`
- L15 _public function_ `FIndexData(uint32 InIndex, float InCost) : Index(InIndex), Cost(InCost)`
- L18 _public function_ `operator uint32() const` — `UE_DEPRECATED(5.5, "This is a fallback conversion operator for Chooser Column implementations which expect index data to be a uint32. Please convert Chooser Column implementations to use FIndexData before the next release")`
- L19 _public member_ `uint32 Index;`
- L20 _public member_ `float Cost;`
- L22 _public function_ `bool operator < (const FIndexData& Other) const`

#### Free symbols / members of external scopes

- L88 _function_ `inline FChooserIndexArray::FIndexData* GetData(FChooserIndexArray& Array)`
- L93 _function_ `inline uint32 GetNum(FChooserIndexArray& Array)`

### `Plugins/Chooser/Source/Chooser/Public/ChooserParameterName.h` (Public)


#### struct `FChooserParameterNameBase`  
`struct FChooserParameterNameBase : public FChooserParameterBase`  
_L12-25_
- reflection: `USTRUCT()`
- inherits: `FChooserParameterBase`
- L16 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, FName& OutResult) const`
- L17 _public function_ `virtual bool SetValue(FChooserEvaluationContext& Context, const FName& InValue) const`
- L20 _public function_ `virtual FLinearColor GetIconColor() const override`

### `Plugins/Chooser/Source/Chooser/Public/ChooserPropertyAccess.h` (Public)


#### struct `UE::Chooser::FCompiledBindingElement`  
`struct FCompiledBindingElement`  
_L21-50_
- L23 _public function_ `FCompiledBindingElement() : bIsFunction(false), Offset(0)`
- L27 _public function_ `explicit FCompiledBindingElement(int InOffset)`
- L34 _public function_ `explicit FCompiledBindingElement(UFunction* InFunction)`
- L40 _public member_ `bool bIsFunction;`

#### union `UE::Chooser::FCompiledBindingElement::(anonymous)`  
``  
_L42-49_

#### struct `UE::Chooser::FCompiledBindingElement::__anonf31496b9010a::(anonymous)`  
``  
_L44-47_

#### enum `UE::Chooser::EChooserPropertyAccessType`  
`enum class EChooserPropertyAccessType`  
_L53-61_
- desc: property type, for numerical conversions
- L55 _public enumerator_ `None`
- L56 _public enumerator_ `Bool`
- L57 _public enumerator_ `Int32`
- L58 _public enumerator_ `Float`
- L59 _public enumerator_ `Double`
- L60 _public enumerator_ `SoftObjectRef`

#### struct `UE::Chooser::FCompiledBinding`  
`struct FCompiledBinding`  
_L63-77_
- L65 _public member_ `int ContextIndex = 0;`
- L66 _public member_ `EChooserPropertyAccessType PropertyType = EChooserPropertyAccessType::None;`
- L68 _public member_ `TArray<FCompiledBindingElement> CompiledChain;` — type info for number and enum conversions
- L69 _public member_ `const UStruct* TargetType = nullptr;`
- L72 _public member_ `const UStruct* StructType = nullptr;` — Type of struct for when the property itself is a struct
- L74 _public member_ `int SerialNumber = 0;`
- L75 _public member_ `TArray<const UStruct*> Dependencies;`

#### struct `FChooserPropertyBinding`  
`struct FChooserPropertyBinding`  
_L82-129_
- reflection: `USTRUCT()`
- L86 _public prototype_ `virtual ~FChooserPropertyBinding() = default;`
- L89 _public member_ `TArray<FName> PropertyBindingChain;` — `UPROPERTY()`
- L92 _public member_ `int ContextIndex = 0;` — `UPROPERTY()`
- L95 _public member_ `bool IsBoundToRoot = false;` — `UPROPERTY()`
- L99 _public member_ `FString DisplayName;` — `UPROPERTY()`
- L101 _public member_ `FText CompileMessage;`
- L103 _public function_ `virtual void SetPropertyData(const IHasContextClass* HasContext, FField* Property)`
- L106 _public member_ `TSharedPtr<UE::Chooser::FCompiledBinding> CompiledBinding;`
- L108 _public prototype_ `FName GetUniqueId() const;`
- L110 _public prototype_ `void Compile(IHasContextClass* HasContext, bool bForce = false);`
- L113 _public prototype_ `template <typename T> bool GetValuePtr(FChooserEvaluationContext& Context, T*& Value) const;`
- L116 _public prototype_ `template <typename T> bool GetStructPtr(FChooserEvaluationContext& Context, T*& Value, UStruct const* &StructType) const;`
- L119 _public prototype_ `template <typename T> bool GetStructValue(FChooserEvaluationContext& Context, T& Value) const;`
- L122 _public prototype_ `template <typename T> bool GetValue(FChooserEvaluationContext& Context, T& Value) const;`
- L125 _public prototype_ `template <typename T> typename TEnableIf<TIsArithmetic<T>::Value, bool>::Type SetValue(FChooserEvaluationContext& Context, const T& Value) const;`
- L128 _public prototype_ `template <typename T> typename TEnableIf<!TIsArithmetic<T>::Value, bool>::Type SetValue(FChooserEvaluationContext& Context, const T& Value) const;`
- L232 _function_ `template <typename T> bool FChooserPropertyBinding::GetValuePtr(FChooserEvaluationContext& Context, T*& OutResult) const`
- L249 _function_ `template <typename T> bool FChooserPropertyBinding::GetStructPtr(FChooserEvaluationContext& Context, T*& OutResult, UStruct const* &OutStructType) const`
- L267 _function_ `template <typename T> bool FChooserPropertyBinding::GetStructValue(FChooserEvaluationContext& Context, T& OutResult) const`
- L289 _function_ `template <typename T> bool FChooserPropertyBinding::GetValue(FChooserEvaluationContext& Context, T& OutResult) const`
- L400 _function_ `template <typename T> typename TEnableIf<TIsArithmetic<T>::Value, bool>::Type FChooserPropertyBinding::SetValue(FChooserEvaluationContext& Context, const T& Value) const`
- L455 _function_ `template <typename T> typename TEnableIf<!TIsArithmetic<T>::Value, bool>::Type FChooserPropertyBinding::SetValue(FChooserEvaluationContext& Context, const T& Value) const`

#### struct `FChooserEnumPropertyBinding`  
`struct FChooserEnumPropertyBinding : public FChooserPropertyBinding`  
_L132-142_
- reflection: `USTRUCT()`
- inherits: `FChooserPropertyBinding`
- L138 _public member_ `TObjectPtr<const UEnum> Enum = nullptr;` — `UPROPERTY()`
- L140 _public prototype_ `virtual void SetPropertyData(const IHasContextClass* HasContext, FField* Property) override;`

#### struct `FChooserObjectPropertyBinding`  
`struct FChooserObjectPropertyBinding : public FChooserPropertyBinding`  
_L145-155_
- reflection: `USTRUCT()`
- inherits: `FChooserPropertyBinding`
- L151 _public member_ `TObjectPtr<UClass> AllowedClass = nullptr;` — `UPROPERTY()`
- L153 _public prototype_ `virtual void SetPropertyData(const IHasContextClass* HasContext, FField* Property) override;`

#### struct `FChooserStructPropertyBinding`  
`struct FChooserStructPropertyBinding : public FChooserPropertyBinding`  
_L158-168_
- reflection: `USTRUCT()`
- inherits: `FChooserPropertyBinding`
- L164 _public member_ `TObjectPtr<UScriptStruct> StructType = nullptr;` — `UPROPERTY()`
- L166 _public prototype_ `virtual void SetPropertyData(const IHasContextClass* HasContext, FField* Property) override;`

#### enum `EContextObjectDirection`  
`enum class EContextObjectDirection`  
_L171-176_
- reflection: `UENUM()`
- L173 _public enumerator_ `Read UMETA(DisplayName="Input", Tooltip = "This Parameter will only be read from")`
- L174 _public enumerator_ `Write UMETA(DisplayName="Output", Tooltip = "This Parameter will only be written to")`
- L175 _public enumerator_ `ReadWrite UMETA(DisplayName="Input/Output", Tooltip = "This Parameter can be both read from and written to")`

#### struct `FContextObjectTypeBase`  
`struct FContextObjectTypeBase`  
_L179-185_
- reflection: `USTRUCT()`
- L184 _public member_ `EContextObjectDirection Direction = EContextObjectDirection::Read;` — `UPROPERTY(EditAnywhere, Category="Type", meta = (ToolTip="Select weather this property will be read from, written to, or both"))`

#### struct `FContextObjectTypeClass`  
`struct FContextObjectTypeClass : public FContextObjectTypeBase`  
_L189-194_
- reflection: `USTRUCT(DisplayName="Class Parameter")`
- inherits: `FContextObjectTypeBase`
- L193 _public member_ `TObjectPtr<UClass> Class;` — `UPROPERTY(EditAnywhere, Category="Type")`

#### struct `FContextObjectTypeStruct`  
`struct FContextObjectTypeStruct : public FContextObjectTypeBase`  
_L197-203_
- reflection: `USTRUCT(DisplayName = "Struct Parameter")`
- inherits: `FContextObjectTypeBase`
- L202 _public member_ `TObjectPtr<UScriptStruct> Struct;` — `UPROPERTY(EditAnywhere, Category="Type")`

#### struct `UE::Chooser::FResolvedPropertyChainResult`  
`struct FResolvedPropertyChainResult`  
_L214-222_
- L216 _public member_ `uint8* Container = nullptr;`
- L217 _public member_ `uint32 PropertyOffset = 0;`
- L218 _public member_ `UFunction* Function = nullptr;`
- L219 _public member_ `const UStruct* StructType = nullptr;`
- L220 _public member_ `EChooserPropertyAccessType PropertyType = EChooserPropertyAccessType::None;`
- L221 _public member_ `uint8 Mask = 0;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHOOSER_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Chooser` (scope `UE`)
- L45 _member_ `int Offset;` (scope `UE::Chooser::FCompiledBindingElement::__anonf31496b9010a::__anonf31496b90208`)
- L46 _member_ `uint8 Mask;` (scope `UE::Chooser::FCompiledBindingElement::__anonf31496b9010a::__anonf31496b90208`) — mask, for bitset bools
- L48 _member_ `UFunction* Function;` (scope `UE::Chooser::FCompiledBindingElement::__anonf31496b9010a`)
- L205 _namespace_ `namespace UE`
- L205 _namespace_ `namespace Chooser` (scope `UE`)
- L208 _prototype_ `void RuntimeValidateContext(const UObject* Asset, const TArray<FInstancedStruct>& ContextData, FChooserEvaluationContext& Context);` (scope `UE::Chooser`)
- L209 _macro_ `#define VALIDATE_CHOOSER_CONTEXT(Asset,ContextData,Context) UE::Chooser::RuntimeValidateContext(Asset, ContextData, Context)`
- L224 _prototype_ `bool ResolvePropertyChain(FChooserEvaluationContext& Context, const FChooserPropertyBinding& Binding, FResolvedPropertyChainResult& Result);` (scope `UE::Chooser`)
- L227 _prototype_ `void CopyPropertyChain(const TArray<FBindingChainElement>& InBindingChain, FChooserPropertyBinding& OutPropertyBinding);` (scope `UE::Chooser`)
- L472 _macro_ `#define CHOOSER_PARAMETER_BOILERPLATE() \`

### `Plugins/Chooser/Source/Chooser/Public/ChooserSignature.h` (Public)


#### class `UChooserSignature`  
`class UChooserSignature : public UObject, public IHasContextClass`  
_L16-38_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IHasContextClass`
- desc: Data table used to choose an asset based on input parameters
- L20 _public function_ `UChooserSignature()`
- L24 _public member_ `EObjectChooserResultType ResultType = EObjectChooserResultType::ObjectResult;` — `UPROPERTY(EditAnywhere, DisplayName = "Result Type", Category="Result", Meta = (EditConditionHides, EditCondition="ResultType != EObjectChooserResultType::NoPrimaryResult"))` — The kind of output this chooser has (Object or Class or No primary result)
- L28 _public member_ `TObjectPtr<UClass> OutputObjectType;` — `UPROPERTY(EditAnywhere, DisplayName= "Result Class", Category="Result", Meta = (AllowAbstract=true, EditConditionHides, EditCondition="ResultType != EObjectChooserResultType::NoPrimaryResult"))` — The Class of Object this Chooser returns when ResultType is set to ObjectOfType, or the Parent Class of the Classes returned by this chooser when ResultType is set to ClassOfType
- L32 _public member_ `TArray<FInstancedStruct> ContextData;` — `UPROPERTY(EditAnywhere, NoClear, DisplayName = "Parameters", Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ContextObjectTypeBase"), Category = "Parameters")` — Parameter Objects or Structs from which the chooser can read or write properties
- L35 _public function_ `virtual TConstArrayView<FInstancedStruct> GetContextData() const override` — IHasContextClass implementation
- L36 _public function_ `virtual FString GetContextOwnerName() const override`
- L37 _public function_ `virtual UObject* GetContextOwnerAsset() override`

### `Plugins/Chooser/Source/Chooser/Public/ChooserTrace.h` (Public)


#### struct `FChooserTrace`  
`struct FChooserTrace`  
_L21-34_
- L23 _public prototype_ `static void OutputChooserEvaluation(const UObject* ChooserAsset, const FChooserEvaluationContext& Context, int32 SelectedIndex);`
- L24 _public prototype_ `static void OutputChooserEvaluation(const UObject* ChooserAsset, const FChooserEvaluationContext& Context, const FChooserIndexArray& SelectedIndex);`
- L25 _public prototype_ `static void OutputChooserValueArchive(const FChooserEvaluationContext& Context, const TCHAR* Key, const FBufferArchive& ValueArchive);`
- L28 _public function_ `template<typename T> static void OutputChooserValue(const FChooserEvaluationContext& Context, const TCHAR* Key, const T& Value)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CHOOSER_API`
- L36 _macro_ `#define TRACE_CHOOSER_EVALUATION(Chooser, Context, SelectedIndex) \`
- L39 _macro_ `#define TRACE_CHOOSER_VALUE(Context, Key, Value) \`
- L43 _macro_ `#define TRACE_CHOOSER_EVALUATION(...)`
- L44 _macro_ `#define TRACE_CHOOSER_VALUE(...)`

### `Plugins/Chooser/Source/Chooser/Public/ChooserTypes.h` (Public)


#### enum `EChooserEvaluationFrequency`  
`enum class EChooserEvaluationFrequency`  
_L12-22_
- reflection: `UENUM()`
- L15 _public enumerator_ `OnInitialUpdate` — Evaluate the Chooser once the Node starts updating for the first time
- L17 _public enumerator_ `OnBecomeRelevant` — Evaluate the Chooser when the Node starts updating
- L19 _public enumerator_ `OnLoop` — Evaluate the Chooser when the animation it's playing has looped
- L21 _public enumerator_ `OnUpdate` — Evaluate the Chooser every update

#### struct `FAnimCurveOverride`  
`struct FAnimCurveOverride`  
_L26-35_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public member_ `FName CurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CurveValue)` — Name of curve to override
- L34 _public member_ `float CurveValue = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CurveValue)` — Value to set to the curve

#### struct `TTypeTraits`  
`template <> struct TTypeTraits<FAnimCurveOverride> : public TTypeTraitsBase < FAnimCurveOverride >`  
_L38-41_
- inherits: `TTypeTraitsBase<FAnimCurveOverride>`

#### enum `TTypeTraits::(anonymous)`  
`enum`  
_L40-40_

#### struct `FAnimCurveOverrideList`  
`struct FAnimCurveOverrideList`  
_L44-54_
- reflection: `USTRUCT(BlueprintType)`
- L48 _public member_ `TArray<FAnimCurveOverride> Values;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Values, meta = (ExpandByDefault = true))`
- L51 _public member_ `uint32 Hash = 0;` — `UPROPERTY()`
- L53 _public prototype_ `void ComputeHash();`

#### struct `FChooserPlayerSettings`  
`struct FChooserPlayerSettings`  
_L57-130_
- reflection: `USTRUCT(BlueprintType)`
- L61 _public prototype_ `bool Serialize(FArchive& Ar);`
- L62 _public prototype_ `bool Serialize(FStructuredArchive::FSlot Slot);`
- L66 _public member_ `bool bMirror = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Set this value to mirror animations - the MirrorDataTable must also be set on the AnimNode
- L70 _public member_ `float StartTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (FrameTimeEditor))` — Start offset when starting the Animation Asset
- L74 _public member_ `bool bForceLooping = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Loop the animation asset, even if the asset is not set as looping
- L78 _public member_ `float PlaybackRate = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — playback rate modifier
- L82 _public member_ `FAnimCurveOverrideList CurveOverrides;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ExpandByDefault = true))` — List of curve values to set
- L85 _public member_ `float BlendTime = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blending, meta = (FrameTimeEditor))`
- L89 _public member_ `TObjectPtr<UBlendProfile> BlendProfile;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blending, meta = (UseAsBlendProfile = true))` — Set Blend Profiles (editable in the skeleton) to determine how the blending is distributed among your character's bones. It could be used to differentiate between upper body and lower body to blend timing.
- L93 _public member_ `EAlphaBlendOption BlendOption = UE::Anim::DefaultBlendOption;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blending)` — How the blend is applied over time to the bones. Common selections are linear, ease in, ease out, and ease in and out.
- L96 _public member_ `bool bUseInertialBlend = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blending)`
- L100 _public member_ `bool bForceBlendTo = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blending)` — Experimental, this feature might be removed without warning, not for production use
- L107 _public member_ `float MinDeltaTimeToForceBlendTo = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blending, meta = (FrameTimeEditor))` — Experimental, this feature might be removed without warning, not for production use the chooser player will continue playing an asset previously selected at time "PreviousStartTime", integrating it by the simulation "DeltaSeconds", unless the current "StartTime" is far away "MinDeltaTimeToForceBlendTo" from "PreviousStartTime": if |PreviousStartTime - StartTime| > MinDeltaTimeToForceBlendTo then bForceBlendTo = true and the chooser player will ask blend stack to blend to the same asset at a different "StartTime"
- L112 _public member_ `TObjectPtr<const UObject> PlayingAsset = nullptr;` — `UPROPERTY(Transient)` — Experimental, this feature might be removed without warning, not for production use Currently playing animation
- L117 _public member_ `float PlayingAssetAccumulatedTime = 0.f;` — `UPROPERTY(Transient)` — Experimental, this feature might be removed without warning, not for production use Currently playing animation accumulated time
- L121 _public member_ `bool bIsPlayingAssetMirrored = false;` — `UPROPERTY(Transient)` — Experimental, this feature might be removed without warning, not for production use
- L126 _public member_ `FVector PlayingAssetBlendParameters = FVector::ZeroVector;` — `UPROPERTY(Transient)` — Experimental, this feature might be removed without warning, not for production use PlayingAsset associated BlendParameters (if PlayingAsset is a UBlendSpace)
- L129 _public member_ `const struct FAnimationUpdateContext* AnimationUpdateContext = nullptr;` — Experimental, this feature might be removed without warning, not for production use

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChooserPlayerSettings> : public TStructOpsTypeTraitsBase2<FChooserPlayerSettings>`  
_L132-139_
- inherits: `TStructOpsTypeTraitsBase2<FChooserPlayerSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L135-138_

#### Free symbols / members of external scopes

- L40 _enumerator_ `enum { IsBytewiseComparable = true };` (scope `TTypeTraits::__anona0e294b70103`)
- L136 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anona0e294b70203`)
- L137 _enumerator_ `WithStructuredSerializer = true` (scope `TStructOpsTypeTraits::__anona0e294b70203`)

### `Plugins/Chooser/Source/Chooser/Public/EnumColumn.h` (Public)


#### enum `EEnumColumnCellValueComparison`  
`enum class EEnumColumnCellValueComparison`  
_L17-24_
- reflection: `UENUM()`
- L19 _public enumerator_ `MatchEqual`
- L20 _public enumerator_ `MatchNotEqual`
- L21 _public enumerator_ `MatchAny`
- L23 _public enumerator_ `Modulus` — used for cycling through the other values

#### struct `FEnumContextProperty`  
`struct FEnumContextProperty : public FChooserParameterEnumBase`  
_L27-64_
- reflection: `USTRUCT(DisplayName = "Enum Property Binding")`
- inherits: `FChooserParameterEnumBase`
- L32 _public member_ `TArray<FName> PropertyBindingChain_DEPRECATED;` — `UPROPERTY()`
- L35 _public member_ `FChooserEnumPropertyBinding Binding;` — `UPROPERTY(EditAnywhere, Meta = (BindingType = "enum", BindingColor = "BytePinTypeColor"), Category = "Binding")`
- L37 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, uint8& OutResult) const override;`
- L38 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, uint8 InValue) const override;`
- L40 _public function_ `virtual void PostLoad() override`
- L53 _public prototype_ `CHOOSER_PARAMETER_BOILERPLATE();`
- L56 _public function_ `virtual const UEnum* GetEnum() const override`
- L62 _private member_ `TObjectPtr<const UEnum> Enum_DEPRECATED = nullptr;` — `UPROPERTY()`

#### struct `FChooserEnumRowData`  
`struct FChooserEnumRowData`  
_L67-86_
- reflection: `USTRUCT()`
- L73 _public member_ `bool CompareNotEqual_DEPRECATED = false;` — `UPROPERTY()`
- L76 _public member_ `FName ValueName;` — `UPROPERTY(EditAnywhere, Category = EditorOnly)`
- L80 _public member_ `EEnumColumnCellValueComparison Comparison = EEnumColumnCellValueComparison::MatchEqual;` — `UPROPERTY(EditAnywhere, Category = Runtime, Meta = (ValidEnumValues = "MatchEqual, MatchNotEqual, MatchAny"))`
- L83 _public member_ `uint8 Value = 0;` — `UPROPERTY(EditAnywhere, Category = Runtime)`
- L85 _public prototype_ `bool Evaluate(const uint8 LeftHandSide) const;`

#### struct `FEnumColumnBase`  
`struct FEnumColumnBase : public FChooserColumnBase`  
_L90-95_
- reflection: `USTRUCT(Meta=(Hidden))`
- inherits: `FChooserColumnBase`
- L94 _public function_ `virtual void EnumChanged(const UEnum* Enum)`

#### struct `FEnumColumn`  
`struct FEnumColumn : public FEnumColumnBase`  
_L98-151_
- reflection: `USTRUCT(DisplayName = "Enum", Meta = (Category = "Filter", Tooltip = "A column that filters rows based on the value of an Enum, with Equal Not Equal, or Any as cell comparison options."))`
- inherits: `FEnumColumnBase`
- L102 _public prototype_ `FEnumColumn();`
- L105 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterEnumBase", ToolTip="The Enum property this column will filter based on"), Category = "Data")`
- L109 _public member_ `FChooserEnumRowData DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L115 _public member_ `TArray<FChooserEnumRowData> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L117 _public prototype_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut) const override;`
- L120 _public function_ `const UEnum* GetEnum() const`
- L130 _public member_ `mutable uint8 TestValue = 0;`
- L131 _public function_ `virtual bool EditorTestFilter(int32 RowIndex) const override`
- L136 _public function_ `virtual void SetTestValue(TArrayView<const uint8> Value) override`
- L142 _public prototype_ `virtual void AddToDetails (FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L143 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L145 _public prototype_ `virtual void EnumChanged(const UEnum* Enum) override;`
- L148 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterEnumBase);`
- L150 _public prototype_ `virtual void PostLoad() override;`

#### class `UDEPRECATED_ChooserParameterEnum_ContextProperty`  
`class UDEPRECATED_ChooserParameterEnum_ContextProperty : public UObject, public IChooserParameterEnum`  
_L155-168_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "LiveLink", deprecated)`
- inherits: `UObject,IChooserParameterEnum`
- desc: deprecated class version for converting old data
- L160 _public member_ `TArray<FName> PropertyBindingChain;` — `UPROPERTY()`
- L162 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const override`

#### class `UDEPRECATED_ChooserColumnEnum`  
`class UDEPRECATED_ChooserColumnEnum : public UObject, public IChooserColumn`  
_L171-197_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "LiveLink", deprecated)`
- inherits: `UObject,IChooserColumn`
- L175 _public prototype_ `UDEPRECATED_ChooserColumnEnum() = default;`
- L176 _public function_ `UDEPRECATED_ChooserColumnEnum(const FObjectInitializer& ObjectInitializer)`
- L182 _public member_ `TScriptInterface<IChooserParameterEnum> InputValue;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L185 _public member_ `TArray<FChooserEnumRowData> RowValues;` — `UPROPERTY(EditAnywhere, Category = Runtime)`
- L187 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/FloatDistanceColumn.h` (Public)


#### struct `FChooserFloatDistanceRowData`  
`struct FChooserFloatDistanceRowData`  
_L18-30_
- reflection: `USTRUCT()`
- L23 _public member_ `float Value=0;` — `UPROPERTY(EditAnywhere, Category=Runtime)`
- L28 _public member_ `bool DisableAutoPopulate = false;` — `UPROPERTY(EditAnywhere, Category=Runtime)` — Set this property to lock the current cell value, preventing it from being updated by AutoPopulate

#### class `UFloatAutoPopulator`  
`class UFloatAutoPopulator : public UObject`  
_L33-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L37 _public function_ `virtual void NativeAutoPopulate(UObject* InObject, bool& OutSuccess, float& OutValue)`

#### struct `FFloatDistanceColumn`  
`struct FFloatDistanceColumn : public FChooserColumnBase`  
_L41-120_
- reflection: `USTRUCT(DisplayName = "Float Difference", Meta = (Category = "Scoring", Tooltip = "A column which scores rows based on their difference from an Input float."))`
- inherits: `FChooserColumnBase`
- L45 _public prototype_ `FFloatDistanceColumn();`
- L48 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterFloatBase", ToolTip="The Float column this fillter will Score based on"), Category = "Data")`
- L52 _public member_ `double MaxDistance= 100;` — `UPROPERTY(EditAnywhere, Category = "Data")` — Maximum Distance used for normalizing scoring (greater distances will be considered equal to the max)
- L56 _public member_ `float CostMultiplier = 1;` — `UPROPERTY(EditAnywhere, Category = "Data")` — Multiplier for controlling which scoring column has the most influence.  Higher values will make the match from this column more important.
- L60 _public member_ `bool bFilterOverMaxDistance = false;` — `UPROPERTY(EditAnywhere, Category = "Data")` — For rows with distance greater than MaxDistance, filter out the row
- L63 _public member_ `bool bWrapInput = false;` — `UPROPERTY(EditAnywhere, Category = "Data")` — Wrap input, and distance calculations for numbers such as angles
- L67 _public member_ `double MinValue = -180;` — `UPROPERTY(EditAnywhere, Category = "Data", meta=(DisplayAfter="bWrapInput", EditCondition="bWrapInput"))` — Minimum value (for WrapInput)
- L71 _public member_ `double MaxValue = 180;` — `UPROPERTY(EditAnywhere, Category = "Data", meta=(DisplayAfter="bWrapInput", EditCondition="bWrapInput"))` — Maximum value (for WrapInput)
- L75 _public member_ `FChooserFloatDistanceRowData DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L79 _public member_ `TSubclassOf<UFloatAutoPopulator> AutoPopulator;` — `UPROPERTY(EditAnywhere, Category = "Data")` — Optional class to auto populate column data based on the result asset
- L85 _public member_ `TArray<FChooserFloatDistanceRowData> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L87 _public function_ `virtual bool HasFilters() const`
- L88 _public prototype_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut) const override;`
- L90 _public function_ `virtual bool HasCosts() const override`
- L93 _public member_ `mutable double TestValue = 0.0;`
- L94 _public prototype_ `virtual bool EditorTestFilter(int32 RowIndex) const override;`
- L95 _public prototype_ `virtual float EditorTestCost(int32 RowIndex) const override;`
- L97 _public function_ `virtual void SetTestValue(TArrayView<const uint8> Value) override`
- L103 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L104 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L106 _public function_ `virtual bool AutoPopulates() const override`
- L107 _public prototype_ `virtual void AutoPopulate(int32 RowIndex, UObject* OutputObject) override;`
- L110 _public function_ `virtual void PostLoad() override`
- L118 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterFloatBase);`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/FloatRangeColumn.h` (Public)


#### struct `FFloatContextProperty`  
`struct FFloatContextProperty : public FChooserParameterFloatBase`  
_L17-40_
- reflection: `USTRUCT(DisplayName = "Float Property Binding")`
- inherits: `FChooserParameterFloatBase`
- L21 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, double& OutResult) const override;`
- L22 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, double Value) const override;`
- L25 _public member_ `TArray<FName> PropertyBindingChain_DEPRECATED;` — `UPROPERTY()`
- L28 _public member_ `FChooserPropertyBinding Binding;` — `UPROPERTY(EditAnywhere, Meta = (BindingType = "double", BindingAllowFunctions = "true", BindingColor = "FloatPinTypeColor"), Category = "Binding")`
- L30 _public function_ `virtual void PostLoad() override`
- L39 _public prototype_ `CHOOSER_PARAMETER_BOILERPLATE();`

#### struct `FChooserFloatRangeRowData`  
`struct FChooserFloatRangeRowData`  
_L43-60_
- reflection: `USTRUCT()`
- L48 _public member_ `float Min=0;` — `UPROPERTY(EditAnywhere, meta=(DisplayAfter="bNoMin", EditCondition="bNoMin==false"), Category=Runtime)`
- L51 _public member_ `float Max=0;` — `UPROPERTY(EditAnywhere, meta=(DisplayAfter="bNoMax", EditCondition="bNoMax==false"), Category=Runtime)`
- L55 _public member_ `bool bNoMin=false;` — `UPROPERTY(EditAnywhere, Category=Runtime)` — Infinite minimum range
- L59 _public member_ `bool bNoMax=false;` — `UPROPERTY(EditAnywhere, Category=Runtime)` — Infinite maximum range

#### struct `FFloatRangeColumn`  
`struct FFloatRangeColumn : public FChooserColumnBase`  
_L64-119_
- reflection: `USTRUCT(DisplayName = "Float Range", Meta = (Category = "Filter", Tooltip = "A column which filters rows if an input value is not within the range specified for the row."))`
- inherits: `FChooserColumnBase`
- L68 _public prototype_ `FFloatRangeColumn();`
- L71 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterFloatBase", ToolTip="The Float property this column will filter based on"), Category = "Data")`
- L75 _public member_ `bool bWrapInput = false;` — `UPROPERTY(EditAnywhere, Category = "Data")` — Wrap input, and comparisons for numbers such as angles which
- L78 _public member_ `double MinValue = -180;` — `UPROPERTY(EditAnywhere, Category = "Data", meta=(DisplayAfter="bWrapInput", EditCondition="bWrapInput"))` — Minimum value (for WrapInput)
- L81 _public member_ `double MaxValue = 180;` — `UPROPERTY(EditAnywhere, Category = "Data", meta=(DisplayAfter="bWrapInput", EditCondition="bWrapInput"))` — Maximum value (for WrapInput)
- L85 _public member_ `FChooserFloatRangeRowData DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L91 _public member_ `TArray<FChooserFloatRangeRowData> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L93 _public prototype_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut) const override;`
- L96 _public member_ `mutable double TestValue = 0.0;`
- L97 _public prototype_ `virtual bool EditorTestFilter(int32 RowIndex) const override;`
- L99 _public function_ `virtual void SetTestValue(TArrayView<const uint8> Value) override`
- L105 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L106 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L109 _public function_ `virtual void PostLoad() override`
- L117 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterFloatBase);`

#### class `UDEPRECATED_ChooserParameterFloat_ContextProperty`  
`class UDEPRECATED_ChooserParameterFloat_ContextProperty : public UObject, public IChooserParameterFloat`  
_L124-137_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "LiveLink", deprecated)`
- inherits: `UObject,IChooserParameterFloat`
- L129 _public member_ `TArray<FName> PropertyBindingChain;` — `UPROPERTY()`
- L131 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const override`

#### class `UDEPRECATED_ChooserColumnFloatRange`  
`class UDEPRECATED_ChooserColumnFloatRange : public UObject, public IChooserColumn`  
_L140-168_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "LiveLink", deprecated)`
- inherits: `UObject,IChooserColumn`
- L144 _public function_ `UDEPRECATED_ChooserColumnFloatRange()`
- L145 _public function_ `UDEPRECATED_ChooserColumnFloatRange(const FObjectInitializer& ObjectInitializer)`
- L151 _public member_ `TScriptInterface<IChooserParameterFloat> InputValue;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L156 _public member_ `TArray<FChooserFloatRangeRowData> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L158 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const override`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/GameplayTagColumn.h` (Public)


#### struct `FGameplayTagContextProperty`  
`struct FGameplayTagContextProperty : public FChooserParameterGameplayTagBase`  
_L19-42_
- reflection: `USTRUCT(DisplayName = "Gameplay Tags Property Binding")`
- inherits: `FChooserParameterGameplayTagBase`
- L24 _public member_ `TArray<FName> PropertyBindingChain_DEPRECATED;` — `UPROPERTY()`
- L27 _public member_ `FChooserPropertyBinding Binding;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (BindingType = "FGameplayTagContainer", BindingColor = "StructPinTypeColor"), Category = "Binding")`
- L29 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, const FGameplayTagContainer*& OutResult) const override;`
- L30 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, const FGameplayTagContainer& Value) const override;`
- L32 _public function_ `virtual void PostLoad() override`
- L41 _public prototype_ `CHOOSER_PARAMETER_BOILERPLATE();`

#### enum `EGameplayTagMatchDirection`  
`enum class EGameplayTagMatchDirection : uint8`  
_L45-51_
- reflection: `UENUM()`
- L48 _public enumerator_ `RowValueInInput` — Row will pass if the Column Input Tags contains the Row Tag(s)
- L50 _public enumerator_ `InputInRowValue` — Row will pass if the Row Tags contain the Column Input Tag(s)

#### struct `FGameplayTagColumn`  
`struct FGameplayTagColumn : public FChooserColumnBase`  
_L54-120_
- reflection: `USTRUCT(DisplayName = "Gameplay Tag", Meta = (Category = "Filter", Tooltip = "A column which filters rows by comparing Gameplay Tags."))`
- inherits: `FChooserColumnBase`
- L58 _public prototype_ `FGameplayTagColumn();`
- L61 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterGameplayTagBase", ToolTip="The GameplayTagCollection property this column will filter based on"), Category = "Data")`
- L64 _public member_ `EGameplayContainerMatchType TagMatchType = EGameplayContainerMatchType::Any;` — `UPROPERTY(EditAnywhere, Category="Data")`
- L68 _public member_ `EGameplayTagMatchDirection TagMatchDirection = EGameplayTagMatchDirection::RowValueInInput;` — `UPROPERTY(EditAnywhere, Category="Data")`
- L72 _public member_ `bool bMatchExact = false;` — `UPROPERTY(EditAnywhere, Category="Data")` — If true, leaf tags must match exactly.
- L76 _public member_ `bool bInvertMatchingLogic = false;` — `UPROPERTY(EditAnywhere, Category="Data")` — If true, rows that pass the normal tag filter will be rejected, and vice versa
- L80 _public member_ `FGameplayTagContainer DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L86 _public member_ `TArray<FGameplayTagContainer> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L88 _public prototype_ `bool TestRow(int32 RowIndex, const FGameplayTagContainer& Value) const;`
- L90 _public prototype_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut) const override;`
- L93 _public member_ `mutable FGameplayTagContainer TestValue;`
- L94 _public function_ `virtual bool EditorTestFilter(int32 RowIndex) const override`
- L99 _public function_ `virtual void SetTestValue(TArrayView<const uint8> Value) override`
- L107 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L108 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L111 _public function_ `virtual void PostLoad() override`
- L119 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterGameplayTagBase);`

#### class `UDEPRECATED_ChooserParameterGameplayTag_ContextProperty`  
`class UDEPRECATED_ChooserParameterGameplayTag_ContextProperty : public UObject, public IChooserParameterGameplayTag`  
_L125-138_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "LiveLink", deprecated)`
- inherits: `UObject,IChooserParameterGameplayTag`
- L130 _public member_ `TArray<FName> PropertyBindingChain;` — `UPROPERTY()`
- L132 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const override`

#### class `UDEPRECATED_ChooserColumnGameplayTag`  
`class UDEPRECATED_ChooserColumnGameplayTag : public UObject, public IChooserColumn`  
_L141-173_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "LiveLink", deprecated)`
- inherits: `UObject,IChooserColumn`
- L145 _public function_ `UDEPRECATED_ChooserColumnGameplayTag()`
- L146 _public function_ `UDEPRECATED_ChooserColumnGameplayTag(const FObjectInitializer& ObjectInitializer)`
- L152 _public member_ `TScriptInterface<IChooserParameterGameplayTag> InputValue;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L155 _public member_ `EGameplayContainerMatchType TagMatchType = EGameplayContainerMatchType::Any;` — `UPROPERTY(EditAnywhere, Category=Runtime)`
- L160 _public member_ `TArray<FGameplayTagContainer> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L163 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/GameplayTagQueryColumn.h` (Public)


#### struct `FGameplayTagQueryColumn`  
`struct FGameplayTagQueryColumn : public FChooserColumnBase`  
_L15-66_
- reflection: `USTRUCT(DisplayName = "Gameplay Tag Query", Meta = (Category = "Filter", Tooltip = "A column which filters rows by matching the input against a Gameplay Tag Query."))`
- inherits: `FChooserColumnBase`
- L19 _public prototype_ `FGameplayTagQueryColumn();`
- L22 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterGameplayTagBase", ToolTip="The GameplayTagContainer property this column will filter by apply the query on"), Category = "Data")`
- L26 _public member_ `FGameplayTagQuery DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L32 _public member_ `TArray<FGameplayTagQuery> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L34 _public prototype_ `bool TestRow(int32 RowIndex, const FGameplayTagContainer& Value) const;`
- L36 _public prototype_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut) const override;`
- L39 _public member_ `mutable FGameplayTagContainer TestValue;`
- L40 _public function_ `virtual bool EditorTestFilter(int32 RowIndex) const override`
- L45 _public function_ `virtual void SetTestValue(TArrayView<const uint8> Value) override`
- L53 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L54 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L57 _public function_ `virtual void PostLoad() override`
- L65 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterGameplayTagBase);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/IChooserColumn.h` (Public)


#### class `UChooserColumn`  
`class UChooserColumn : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IChooserColumn`  
`class IChooserColumn`  
_L19-24_
- L23 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const`

#### struct `FChooserColumnBase`  
`struct FChooserColumnBase`  
_L34-131_
- reflection: `USTRUCT()`
- L39 _public prototype_ `virtual ~FChooserColumnBase() = default;`
- L40 _public function_ `virtual void PostLoad()`
- L42 _public function_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut) const`
- L45 _public function_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut, TArrayView<uint8> ScratchArea) const` — Experimental, this feature might be removed without warning, not for production use
- L50 _public function_ `virtual bool HasCosts() const`
- L51 _public function_ `virtual bool HasFilters() const`
- L52 _public function_ `virtual bool HasOutputs() const`
- L54 _public function_ `virtual void SetOutputs(FChooserEvaluationContext& Context, int RowIndex) const`
- L57 _public function_ `virtual void SetOutputs(FChooserEvaluationContext& Context, int RowIndex, TArrayView<uint8> ScratchArea) const` — Experimental, this feature might be removed without warning, not for production use
- L62 _public function_ `virtual void Compile(IHasContextClass* Owner, bool bForce)`
- L76 _public function_ `virtual void SetTestValue(TArrayView<const uint8> Value)`
- L77 _public function_ `virtual FChooserParameterBase* GetInputValue()`
- L78 _public function_ `virtual FInstancedStruct* GetInputValuePtr()`
- L81 _public function_ `virtual int32 GetScratchAreaSize() const` — Experimental, this feature might be removed without warning, not for production use
- L83 _public function_ `virtual void InitializeScratchArea(TArrayView<uint8> ScratchArea) const` — Experimental, this feature might be removed without warning, not for production use
- L85 _public function_ `virtual void DeinitializeScratchArea(TArrayView<uint8> ScratchArea) const` — Experimental, this feature might be removed without warning, not for production use
- L88 _public function_ `virtual void Initialize(UChooserTable* OuterChooser)`
- L90 _public function_ `virtual FName RowValuesPropertyName()`
- L91 _public function_ `virtual void SetNumRows(int32 NumRows)`
- L92 _public function_ `virtual void DeleteRows(TArrayView<int> RowIndices)`
- L93 _public function_ `virtual void MoveRow(int SourceIndex, int TargetIndex)`
- L94 _public function_ `virtual void InsertRows(int Index, int Count)`
- L95 _public function_ `virtual void CopyRow(FChooserColumnBase& SourceColumn, int SourceIndex, int TargetIndex)`
- L96 _public function_ `virtual void CopyFallback(FChooserColumnBase& SourceColumn)`
- L98 _public function_ `virtual UScriptStruct* GetInputBaseType() const`
- L99 _public function_ `virtual const UScriptStruct* GetInputType() const`
- L100 _public function_ `virtual void SetInputType(const UScriptStruct* Type)`
- L101 _public function_ `virtual void InputValueChanged()`
- L103 _public function_ `virtual bool HasPrimaryInput()`
- L110 _public function_ `virtual bool IsRandomizeColumn() const` — random columns must go last, and get a special icon using a virtual fucntion to identify them (rather than hard coding a specific type) to potentially support multiple varieties of randomization column.
- L112 _public function_ `virtual bool AutoPopulates() const`
- L113 _public function_ `virtual void AutoPopulate(int32 RowIndex, UObject* OutputObject)`
- L115 _public function_ `virtual float EditorTestCost(int32 RowIndex) const`
- L116 _public function_ `virtual bool EditorTestFilter(int32 RowIndex) const`
- L118 _public function_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex)`
- L119 _public function_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex)`
- L121 _public function_ `virtual void ReplaceReferences(UObject* ReferenceToReplace, UObject* ReplaceWith)`
- L126 _public member_ `bool bDisabled = false;` — `UPROPERTY(EditAnywhere, Category=Base)`
- L129 _public member_ `float EditorColumnWidth = 200;` — `UPROPERTY()`

#### enum `(anonymous)`  
`enum`  
_L133-133_

#### Free symbols / members of external scopes

- L133 _enumerator_ `enum { ChooserColumn_SpecialIndex_Fallback = -2 }; #if WITH_EDITOR #define CHOOSER_COLUMN_BOILERPLATE2(ParameterType, RowValuesProperty) \ virtual FName RowValuesPropertyName() override { return #RowValuesProperty; }\ virtual void SetNumRows(int32 NumRows) override\ {\ if (NumRows <= RowValuesProperty.Num())\` (scope `__anon5c1339d90103`)
- L136 _macro_ `#define CHOOSER_COLUMN_BOILERPLATE2(ParameterType, RowValuesProperty) \`
- L194 _macro_ `#define CHOOSER_COLUMN_BOILERPLATE(ParameterType) CHOOSER_COLUMN_BOILERPLATE2(ParameterType, RowValues)`

### `Plugins/Chooser/Source/Chooser/Public/IChooserParameterBase.h` (Public)


#### struct `FChooserParameterBase`  
`struct FChooserParameterBase`  
_L13-45_
- reflection: `USTRUCT()`
- L17 _public function_ `virtual FString GetDebugName() const`
- L24 _public function_ `virtual void GetDisplayName(FText& OutName) const`
- L25 _public function_ `virtual void AddSearchNames(FStringBuilderBase& Builder) const`
- L26 _public function_ `virtual void ReplaceString(FStringView FindString, ESearchCase::Type, bool MatchWholeWord, FStringView ReplaceString)`
- L28 _public function_ `virtual void PostLoad()`
- L29 _public function_ `virtual void Compile(IHasContextClass* Owner, bool bForce)`
- L30 _public function_ `virtual bool HasCompileErrors(FText& OutMessage) const`
- L33 _public function_ `virtual FName GetIconName() const`
- L38 _public function_ `virtual FLinearColor GetIconColor() const`
- L44 _public prototype_ `virtual ~FChooserParameterBase() = default;`

### `Plugins/Chooser/Source/Chooser/Public/IChooserParameterBool.h` (Public)


#### class `UChooserParameterBool`  
`class UChooserParameterBool : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IChooserParameterBool`  
`class IChooserParameterBool`  
_L18-23_
- L22 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const`

#### struct `FChooserParameterBoolBase`  
`struct FChooserParameterBoolBase : public FChooserParameterBase`  
_L26-40_
- reflection: `USTRUCT()`
- inherits: `FChooserParameterBase`
- L31 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, bool& OutResult) const`
- L32 _public function_ `virtual bool SetValue(FChooserEvaluationContext& Context, bool InValue) const`
- L35 _public function_ `virtual FLinearColor GetIconColor() const override`

### `Plugins/Chooser/Source/Chooser/Public/IChooserParameterEnum.h` (Public)


#### class `UChooserParameterEnum`  
`class UChooserParameterEnum : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IChooserParameterEnum`  
`class IChooserParameterEnum`  
_L17-22_
- L21 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const`

#### struct `FChooserParameterEnumBase`  
`struct FChooserParameterEnumBase : public FChooserParameterBase`  
_L25-40_
- reflection: `USTRUCT()`
- inherits: `FChooserParameterBase`
- L29 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, uint8& OutResult) const`
- L30 _public function_ `virtual bool SetValue(FChooserEvaluationContext& Context, uint8 InValue) const`
- L33 _public function_ `virtual const UEnum* GetEnum() const`
- L35 _public function_ `virtual FLinearColor GetIconColor() const override`

### `Plugins/Chooser/Source/Chooser/Public/IChooserParameterFloat.h` (Public)


#### class `UChooserParameterFloat`  
`class UChooserParameterFloat : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IChooserParameterFloat`  
`class IChooserParameterFloat`  
_L18-23_
- L22 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const`

#### struct `FChooserParameterFloatBase`  
`struct FChooserParameterFloatBase : public FChooserParameterBase`  
_L26-40_
- reflection: `USTRUCT()`
- inherits: `FChooserParameterBase`
- L31 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, double& OutResult) const`
- L32 _public function_ `virtual bool SetValue(FChooserEvaluationContext& Context, double InValue) const`
- L35 _public function_ `virtual FLinearColor GetIconColor() const override`

### `Plugins/Chooser/Source/Chooser/Public/IChooserParameterGameplayTag.h` (Public)


#### class `UChooserParameterGameplayTag`  
`class UChooserParameterGameplayTag : public UInterface`  
_L16-19_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IChooserParameterGameplayTag`  
`class IChooserParameterGameplayTag`  
_L21-26_
- L25 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const`

#### struct `FChooserParameterGameplayTagBase`  
`struct FChooserParameterGameplayTagBase : public FChooserParameterBase`  
_L29-34_
- reflection: `USTRUCT()`
- inherits: `FChooserParameterBase`
- L32 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, const FGameplayTagContainer*& OutResult) const`
- L33 _public function_ `virtual bool SetValue(FChooserEvaluationContext& Context, const FGameplayTagContainer& Value) const`

#### struct `FChooserParameterGameplayTagQueryBase`  
`struct FChooserParameterGameplayTagQueryBase : public FChooserParameterBase`  
_L37-41_
- reflection: `USTRUCT()`
- inherits: `FChooserParameterBase`
- L40 _public function_ `virtual bool SetValue(FChooserEvaluationContext& Context, const FGameplayTagQuery& Value) const`

### `Plugins/Chooser/Source/Chooser/Public/IChooserParameterObject.h` (Public)


#### struct `FChooserParameterObjectBase`  
`struct FChooserParameterObjectBase : public FChooserParameterBase`  
_L12-29_
- reflection: `USTRUCT()`
- inherits: `FChooserParameterBase`
- L16 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, FSoftObjectPath& OutResult) const`
- L17 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, UObject*& OutResult) const`
- L18 _public function_ `virtual bool SetValue(FChooserEvaluationContext& Context, const FSoftObjectPath& OutResult) const`
- L19 _public function_ `virtual bool SetValue(FChooserEvaluationContext& Context, UObject* OutResult) const`
- L22 _public function_ `virtual UClass* GetAllowedClass() const`
- L24 _public function_ `virtual FLinearColor GetIconColor() const override`

### `Plugins/Chooser/Source/Chooser/Public/IChooserParameterRandomize.h` (Public)


#### struct `FRandomizationState`  
`struct FRandomizationState`  
_L12-20_
- L16 _public member_ `TArray<int32, TInlineAllocator<4>> RecentlySelectedRows;` — A ring buffer of recently selected rows (size determined by the size of FRandomizeColumn::RepeatProbabilityMultipliers) Where each entry is a row index into the ChooserTable, which was recently selected.
- L19 _public member_ `int LastSelectedRow;` — Index into RecentlySelectedRows marking the one most recently selected entry (the next most recently selected entry is at (LastSelectedRowIndex - 1 + Num) % Num

#### struct `FChooserRandomizationContext`  
`struct FChooserRandomizationContext`  
_L23-28_
- reflection: `USTRUCT(BlueprintType)`
- L27 _public member_ `TMap<const void*, FRandomizationState> StateMap;`

#### struct `FChooserParameterRandomizeBase`  
`struct FChooserParameterRandomizeBase : public FChooserParameterBase`  
_L31-36_
- reflection: `USTRUCT()`
- inherits: `FChooserParameterBase`
- L34 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, FChooserRandomizationContext*& OutResult) const`
- L35 _public function_ `virtual bool IsBound() const`

### `Plugins/Chooser/Source/Chooser/Public/IChooserParameterStruct.h` (Public)


#### struct `FChooserParameterStructBase`  
`struct FChooserParameterStructBase : public FChooserParameterBase`  
_L13-22_
- reflection: `USTRUCT()`
- inherits: `FChooserParameterBase`
- L17 _public function_ `virtual bool SetValue(FChooserEvaluationContext& Context, const FInstancedStruct &Value) const`
- L20 _public function_ `virtual UScriptStruct* GetStructType() const`

### `Plugins/Chooser/Source/Chooser/Public/IHasContext.h` (Public)


#### class `UHasContextClass`  
`class UHasContextClass : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IHasContextClass`  
`class IHasContextClass`  
_L21-36_
- L25 _public member_ `FContextClassChanged OnContextClassChanged;`
- L26 _public function_ `virtual TConstArrayView<FInstancedStruct> GetContextData() const`
- L28 _public function_ `virtual FString GetContextOwnerName() const`
- L29 _public function_ `virtual UObject* GetContextOwnerAsset()`
- L31 _public function_ `virtual void Compile(bool bForce = false)`
- L33 _public function_ `virtual void AddCompileDependency(const UStruct* Struct)`

#### enum `EObjectChooserResultType`  
`enum class EObjectChooserResultType`  
_L41-49_
- reflection: `UENUM()`
- L44 _public enumerator_ `ObjectResult UMETA(DisplayName = "Object Of Type")` — The Chooser returns an Object of the specified Result Class
- L46 _public enumerator_ `ClassResult UMETA(DisplayName = "SubClass Of")` — The Chooser returns a Class that is a SubClass of the specified Result Class (eg a chooser could return a type of Character to spawn, or a type of AnimInstance to link)
- L48 _public enumerator_ `NoPrimaryResult UMETA(Hidden)` — The Chooser returns nothing, but can write to one or more outputs (useful if you are only interested in returning integral types like a float or string)

#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChooser, Log, All);`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE(FContextClassChanged) class IHasContextClass { GENERATED_BODY() public: FContextClassChanged OnContextClassChanged; virtual TConstArrayView<FInstancedStruct> GetContextData() const { return TConstArrayView<FInstancedStruct>(); } virtual FString GetContextOwnerName() const { return ""; } virtual UObject* GetContextOwnerAsset() { return nullptr; } virtual void Compile(bool bForce = false) {} #if WITH_EDITOR virtual void AddCompileDependency(const UStruct* Struct) { } #endif };`
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChooserOutputObjectTypeChanged, const UClass* OutputObjectType);`
- L38 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChooserOutputObjectTypeChanged, const UClass* OutputObjectType);`

### `Plugins/Chooser/Source/Chooser/Public/IObjectChooser.h` (Public)


#### class `UObjectChooser`  
`class UObjectChooser : public UInterface`  
_L21-24_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IObjectChooser`  
`class IObjectChooser`  
_L26-31_
- L30 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const`

#### struct `FChooserDebuggingInfo`  
`struct FChooserDebuggingInfo`  
_L34-38_
- L36 _public member_ `const UObject* CurrentChooser = nullptr;`
- L37 _public member_ `bool bCurrentDebugTarget = false;`

#### struct `FChooserEvaluationInputObject`  
`struct FChooserEvaluationInputObject`  
_L43-49_
- reflection: `USTRUCT()`
- L46 _public function_ `FChooserEvaluationInputObject()`
- L47 _public function_ `FChooserEvaluationInputObject (UObject* InObject) : Object(InObject)`
- L48 _public member_ `TObjectPtr<UObject> Object;`

#### struct `FChooserEvaluationOutputArray`  
`struct FChooserEvaluationOutputArray`  
_L54-65_
- reflection: `USTRUCT()`
- desc: special context entry for mult-struct output keeps copies of a context struct for each returned result object
- L57 _public function_ `FChooserEvaluationOutputArray()`
- L58 _public function_ `FChooserEvaluationOutputArray(uint32 InSourceParamIndex)`
- L63 _public member_ `TArray<FInstancedStruct> OutputValues;`
- L64 _public member_ `uint32 SourceParamIndex = 0;`

#### struct `FChooserEvaluationContext`  
`struct FChooserEvaluationContext`  
_L68-124_
- reflection: `USTRUCT(BlueprintType)`
- L70 _public function_ `FChooserEvaluationContext()`
- L71 _public function_ `FChooserEvaluationContext(UObject* ContextObject)`
- L77 _public function_ `void AddObjectParam(UObject* Param)` — Add a UObject Parameter to the context
- L84 _public function_ `UObject* GetFirstObjectParam()` — Helper to get the first object parameter if there is one
- L90 _public function_ `const UObject* GetFirstObjectParam() const` — Helper to get the first object parameter if there is one
- L97 _public function_ `void AddStructViewParam(FStructView Param)` — Add a struct view Parameter to the Context the struct will be referred to by reference, and so must have a lifetime that is longer than this context
- L105 _public function_ `template <class T> void AddStructParam(T& Param)` — Add a struct Parameter to the Context the struct will be referred to by reference, and so must have a lifetime that is longer than this context
- L111 _public member_ `FChooserDebuggingInfo DebuggingInfo;`
- L115 _public member_ `TArray<FStructView, TInlineAllocator<4>> Params;`
- L118 _public member_ `TArray<FChooserEvaluationInputObject, TInlineAllocator<4>> ObjectParams;` — storage for Object Params, call AddObjectParam to allocate one FChooserEvaluationInputObject in this array and then add a StructView of it to the Params array
- L121 _public member_ `TArray<FChooserEvaluationOutputArray, TInlineAllocator<2>> OutputArrays;` — storage for output struct data in multi-output mode
- L123 _public member_ `FRandomStream* RandomStream = nullptr;`

#### struct `FObjectChooserBase`  
`struct FObjectChooserBase`  
_L127-186_
- reflection: `USTRUCT()`
- L132 _public prototype_ `virtual ~FObjectChooserBase() = default;`
- L142 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( EIteratorStatus, FObjectChooserIteratorCallback, UObject*);`
- L143 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( EIteratorStatus, FObjectChooserSoftObjectIteratorCallback, const TSoftObjectPtr<UObject>&);`
- L145 _public function_ `virtual void Compile(class IHasContextClass* HasContext, bool bForce)`
- L146 _public function_ `virtual bool HasCompileErrors(FText& Message)`
- L148 _public function_ `virtual void ChooseObject(FChooserEvaluationContext& Context, TSoftObjectPtr<UObject>& Result) const`
- L154 _public function_ `virtual UObject* ChooseObject(FChooserEvaluationContext& Context) const`
- L155 _public function_ `virtual EIteratorStatus ChooseMulti(FChooserEvaluationContext& ContextData, FObjectChooserIteratorCallback Callback) const`
- L165 _public function_ `virtual EIteratorStatus ChooseMulti(FChooserEvaluationContext& ContextData, FObjectChooserSoftObjectIteratorCallback Callback) const`
- L179 _public function_ `virtual EIteratorStatus IterateObjects(FChooserEvaluationContext& Context, FObjectChooserIteratorCallback Callback) const`
- L180 _public function_ `virtual void GetDebugName(FString& OutDebugName) const`
- L184 _public function_ `virtual UObject* GetReferencedObject() const` — for implementations with a reference to an asset or other object, get the object for use in editor

#### enum `FObjectChooserBase::EIteratorStatus`  
`enum class EIteratorStatus`  
_L134-140_
- L136 _public enumerator_ `Continue` — Succeeded, but continue on to the next entry (for getting multiple results from choosers)
- L137 _public enumerator_ `ContinueWithOutputs = Continue` — Backwards compatibility from when only single outputs were supported
- L138 _public enumerator_ `Stop` — Succeeded, and stop iterating now  (for getting first result from choosers)
- L139 _public enumerator_ `Failed` — Failed, continue iterating to the next entry  (will trigger chooser to continue evaluating to find a valid result, including evaluating the fallback row)

#### Free symbols / members of external scopes

- L13 _macro_ `#define CHOOSER_TRACE_ENABLED 1`
- L15 _macro_ `#define CHOOSER_TRACE_ENABLED 0`
- L18 _macro_ `#define CHOOSER_DEBUGGING_ENABLED ((CHOOSER_TRACE_ENABLED) || (WITH_EDITOR))`
- L142 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( EIteratorStatus, FObjectChooserIteratorCallback, UObject*);`
- L143 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( EIteratorStatus, FObjectChooserSoftObjectIteratorCallback, const TSoftObjectPtr<UObject>&);`

### `Plugins/Chooser/Source/Chooser/Public/MultiEnumColumn.h` (Public)


#### struct `FChooserMultiEnumRowData`  
`struct FChooserMultiEnumRowData`  
_L18-29_
- reflection: `USTRUCT()`
- L23 _public member_ `uint32 Value = 0;` — `UPROPERTY(EditAnywhere, Category = Runtime)`
- L25 _public function_ `bool Evaluate(const uint32 LeftHandSide) const`

#### struct `FMultiEnumColumn`  
`struct FMultiEnumColumn : public FChooserColumnBase`  
_L32-83_
- reflection: `USTRUCT(DisplayName = "Enum (Or)", Meta = (Category = "Filter", Tooltip = "A column which filters rows using an Enum variable, where rows pass if the enum is one of any of the checked values."))`
- inherits: `FChooserColumnBase`
- L36 _public prototype_ `FMultiEnumColumn();`
- L39 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterEnumBase", ToolTip="The Enum property this column will filter based on"), Category = "Data")`
- L43 _public member_ `FChooserMultiEnumRowData DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L49 _public member_ `TArray<FChooserMultiEnumRowData> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L51 _public prototype_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut) const override;`
- L54 _public function_ `const UEnum* GetEnum() const`
- L64 _public member_ `mutable uint8 TestValue = 0;`
- L65 _public function_ `virtual bool EditorTestFilter(int32 RowIndex) const override`
- L70 _public function_ `virtual void SetTestValue(TArrayView<const uint8> Value) override`
- L76 _public prototype_ `virtual void AddToDetails (FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex);`
- L77 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex);`
- L80 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterEnumBase);`
- L82 _public prototype_ `virtual void PostLoad() override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/NameColumn.h` (Public)


#### struct `FNameContextProperty`  
`struct FNameContextProperty : public FChooserParameterNameBase`  
_L17-28_
- reflection: `USTRUCT(DisplayName = "Name Binding")`
- inherits: `FChooserParameterNameBase`
- L22 _public member_ `FChooserPropertyBinding Binding;` — `UPROPERTY(EditAnywhere, Meta = (BindingType = "FName", BindingColor = "StructPinTypeColor"), Category = "Binding")`
- L24 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, FName& OutResult) const override;`
- L25 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, const FName& InValue) const override;`
- L27 _public prototype_ `CHOOSER_PARAMETER_BOILERPLATE();`

#### enum `ENameColumnCellValueComparison`  
`enum class ENameColumnCellValueComparison`  
_L31-38_
- reflection: `UENUM()`
- L33 _public enumerator_ `MatchEqual`
- L34 _public enumerator_ `MatchNotEqual`
- L35 _public enumerator_ `MatchAny`
- L37 _public enumerator_ `Modulus` — used for cycling through the other values

#### struct `FChooserNameRowData`  
`struct FChooserNameRowData`  
_L41-52_
- reflection: `USTRUCT()`
- L46 _public member_ `ENameColumnCellValueComparison Comparison = ENameColumnCellValueComparison::MatchEqual;` — `UPROPERTY(EditAnywhere, Category = Runtime, Meta = (ValidEnumValues = "MatchEqual, MatchNotEqual, MatchAny"))`
- L49 _public member_ `FName Value;` — `UPROPERTY(EditAnywhere, Category = "Runtime")`
- L51 _public prototype_ `bool Evaluate(const FName& LeftHandSide) const;`

#### struct `FChooserNameColumn`  
`struct FChooserNameColumn : public FChooserColumnBase`  
_L55-105_
- reflection: `USTRUCT(DisplayName = "Name", Meta = (Category = "Filter", Tooltip = "A column which filters rows by an input Name compared to Names specified on each row."))`
- inherits: `FChooserColumnBase`
- L59 _public prototype_ `FChooserNameColumn();`
- L62 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterNameBase", ToolTip="The Name reference property this column will filter based on"), Category = "Data")`
- L66 _public member_ `FChooserNameRowData DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L70 _public member_ `TArray<FChooserNameRowData> RowValues;` — `UPROPERTY()`
- L72 _public prototype_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut) const override;`
- L75 _public member_ `mutable FName TestValue;`
- L76 _public function_ `virtual bool EditorTestFilter(int32 RowIndex) const override`
- L80 _public function_ `virtual void SetTestValue(TArrayView<const uint8> Value) override`
- L88 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L89 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L92 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterNameBase);`
- L95 _public function_ `virtual void PostLoad() override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/ObjectChooser_Asset.h` (Public)


#### struct `FAssetChooser`  
`struct FAssetChooser : public FObjectChooserBase`  
_L12-26_
- reflection: `USTRUCT(DisplayName = "Asset", Meta = (ResultType = "Object", Category = "Basic", Tooltip = "A hard reference to a specific asset"))`
- inherits: `FObjectChooserBase`
- L17 _public prototype_ `virtual UObject* ChooseObject(FChooserEvaluationContext& Context) const final override;` — FObjectChooserBase interface
- L18 _public prototype_ `virtual EIteratorStatus IterateObjects(FChooserEvaluationContext& Context, FObjectChooserIteratorCallback Callback) const final override;`
- L21 _public function_ `virtual UObject* GetReferencedObject() const override`
- L25 _public member_ `TObjectPtr<UObject> Asset;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (GetAssetFilter="ResultAssetFilter"))`

#### struct `FSoftAssetChooser`  
`struct FSoftAssetChooser : public FObjectChooserBase`  
_L29-44_
- reflection: `USTRUCT(DisplayName = "Asset (Soft Reference)", Meta = (ResultType = "Object", Category = "Basic", Tooltip = "A soft object reference to a specific asset\nAssets will need to be preloaded manually to avoid a hitch if they are selected."))`
- inherits: `FObjectChooserBase`
- L34 _public prototype_ `virtual void ChooseObject(FChooserEvaluationContext& Context, TSoftObjectPtr<UObject>& Result) const final override;` — FObjectChooserBase interface
- L35 _public prototype_ `virtual UObject* ChooseObject(FChooserEvaluationContext& Context) const final override;`
- L36 _public prototype_ `virtual EIteratorStatus IterateObjects(FChooserEvaluationContext& Context, FObjectChooserIteratorCallback Callback) const final override;`
- L39 _public function_ `virtual UObject* GetReferencedObject() const override`
- L43 _public member_ `TSoftObjectPtr<UObject> Asset;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (GetAssetFilter="ResultAssetFilter"))`

#### class `UDEPRECATED_ObjectChooser_Asset`  
`class UDEPRECATED_ObjectChooser_Asset : public UObject, public IObjectChooser`  
_L48-62_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "LiveLink", deprecated)`
- inherits: `UObject,IObjectChooser`
- desc: deprecated class for upgrading old data
- L53 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const override`
- L61 _public member_ `TObjectPtr<UObject> Asset;` — `UPROPERTY(EditAnywhere, Category = "Parameters")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/ObjectChooser_Class.h` (Public)


#### struct `FClassChooser`  
`struct FClassChooser : public FObjectChooserBase`  
_L12-22_
- reflection: `USTRUCT(DisplayName = "Class", Meta = (ResultType = "Class", Category = "Basic", Tooltip = "A reference to a Class.\nOnly for use in Choosers with ResultType set to Sub Class Of"))`
- inherits: `FObjectChooserBase`
- L17 _public prototype_ `virtual UObject* ChooseObject(FChooserEvaluationContext& Context) const final override;` — FObjectChooserBase interface
- L18 _public prototype_ `virtual EIteratorStatus IterateObjects(FChooserEvaluationContext& Context, FObjectChooserIteratorCallback Callback) const final override;`
- L21 _public member_ `TObjectPtr<UClass> Class;` — `UPROPERTY(EditAnywhere, Category = "Parameters")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/ObjectClassColumn.h` (Public)


#### enum `EObjectClassColumnCellValueComparison`  
`enum class EObjectClassColumnCellValueComparison`  
_L16-23_
- reflection: `UENUM()`
- L18 _public enumerator_ `Equal`
- L19 _public enumerator_ `NotEqual`
- L20 _public enumerator_ `SubClassOf`
- L21 _public enumerator_ `NotSubClassOf`
- L22 _public enumerator_ `Any`

#### struct `FChooserObjectClassRowData`  
`struct FChooserObjectClassRowData`  
_L26-37_
- reflection: `USTRUCT()`
- L31 _public member_ `EObjectClassColumnCellValueComparison Comparison = EObjectClassColumnCellValueComparison::SubClassOf;` — `UPROPERTY(EditAnywhere, Category = Runtime)`
- L34 _public member_ `TObjectPtr<UClass> Value;` — `UPROPERTY(EditAnywhere, Category = "Runtime")`
- L36 _public prototype_ `bool Evaluate(const UObject* LeftHandSide) const;`

#### struct `FObjectClassColumn`  
`struct FObjectClassColumn : public FChooserColumnBase`  
_L40-100_
- reflection: `USTRUCT(DisplayName = "Object Class", Meta = (Category = "Filter", Tooltip = "A column which filters rows using an Object reference variable, by checking if that object is of a certain Class."))`
- inherits: `FChooserColumnBase`
- L44 _public prototype_ `FObjectClassColumn();`
- L47 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterObjectBase", ToolTip="The Object reference property this column will filter based on"), Category = "Data")`
- L51 _public member_ `FChooserObjectClassRowData DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category = "Data", Meta =(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L57 _public member_ `TArray<FChooserObjectClassRowData> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L59 _public prototype_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut) const override;`
- L62 _public member_ `mutable FSoftObjectPath TestValue;`
- L63 _public function_ `virtual bool EditorTestFilter(int32 RowIndex) const override`
- L75 _public function_ `virtual void SetTestValue(TArrayView<const uint8> Value) override`
- L83 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L84 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L87 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterObjectBase);`
- L90 _public function_ `virtual void PostLoad() override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/ObjectColumn.h` (Public)


#### struct `FObjectContextProperty`  
`struct FObjectContextProperty : public FChooserParameterObjectBase`  
_L17-34_
- reflection: `USTRUCT(DisplayName = "Object Property Binding")`
- inherits: `FChooserParameterObjectBase`
- L22 _public member_ `FChooserObjectPropertyBinding Binding;` — `UPROPERTY(EditAnywhere, Meta = (BindingType = "object", BindingColor = "ObjectPinTypeColor"), Category = "Binding")`
- L24 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, FSoftObjectPath& OutResult) const override;`
- L25 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, UObject*& OutResult) const override;`
- L26 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, UObject* InValue) const override;`
- L27 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, const FSoftObjectPath& InValue) const override;`
- L29 _public prototype_ `CHOOSER_PARAMETER_BOILERPLATE();`
- L32 _public function_ `virtual UClass* GetAllowedClass() const override`

#### enum `EObjectColumnCellValueComparison`  
`enum class EObjectColumnCellValueComparison`  
_L37-44_
- reflection: `UENUM()`
- L39 _public enumerator_ `MatchEqual`
- L40 _public enumerator_ `MatchNotEqual`
- L41 _public enumerator_ `MatchAny`
- L43 _public enumerator_ `Modulus` — used for cycling through the other values

#### struct `FChooserObjectRowData`  
`struct FChooserObjectRowData`  
_L47-58_
- reflection: `USTRUCT()`
- L52 _public member_ `EObjectColumnCellValueComparison Comparison = EObjectColumnCellValueComparison::MatchEqual;` — `UPROPERTY(EditAnywhere, Category = Runtime, Meta = (ValidEnumValues = "MatchEqual, MatchNotEqual, MatchAny"))`
- L55 _public member_ `TSoftObjectPtr<UObject> Value;` — `UPROPERTY(EditAnywhere, Category = "Runtime")`
- L57 _public prototype_ `bool Evaluate(const FSoftObjectPath& LeftHandSide) const;`

#### struct `FObjectColumn`  
`struct FObjectColumn : public FChooserColumnBase`  
_L61-113_
- reflection: `USTRUCT(DisplayName = "Object", Meta = (Category = "Filter", Tooltip = "A column which filters rows by an input Object to specified Objects for each row."))`
- inherits: `FChooserColumnBase`
- L65 _public prototype_ `FObjectColumn();`
- L68 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterObjectBase", ToolTip="The Object reference property this column will filter based on"), Category = "Data")`
- L72 _public member_ `FChooserObjectRowData DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L78 _public member_ `TArray<FChooserObjectRowData> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L80 _public prototype_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut) const override;`
- L83 _public member_ `mutable FSoftObjectPath TestValue;`
- L84 _public function_ `virtual bool EditorTestFilter(int32 RowIndex) const override`
- L88 _public function_ `virtual void SetTestValue(TArrayView<const uint8> Value) override`
- L96 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L97 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L100 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterObjectBase);`
- L103 _public function_ `virtual void PostLoad() override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/OutputBoolColumn.h` (Public)


#### struct `FOutputBoolColumn`  
`struct FOutputBoolColumn : public FChooserColumnBase`  
_L14-57_
- reflection: `USTRUCT(DisplayName = "Output Bool", Meta = (Category = "Output", Tooltip = "A column which writes a Bool value."))`
- inherits: `FChooserColumnBase`
- L18 _public prototype_ `FOutputBoolColumn();`
- L19 _public function_ `virtual bool HasFilters() const override`
- L20 _public function_ `virtual bool HasOutputs() const override`
- L21 _public prototype_ `virtual void SetOutputs(FChooserEvaluationContext& Context, int RowIndex) const override;`
- L24 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterBoolBase", ToolTip="The Bool property this column will write to"), Category = "Hidden")`
- L27 _public member_ `mutable bool TestValue=false;`
- L29 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L30 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L31 _public function_ `virtual void CopyFallback(FChooserColumnBase& SourceColumn) override`
- L34 _public function_ `bool& GetValueForIndex(int32 Index)`
- L39 _public function_ `bool GetValueForIndex(int32 Index) const`
- L46 _public member_ `bool bFallbackValue = false;` — `UPROPERTY()` — FallbackValue will be used as the output value if the all rows in the chooser fail, and the FallbackResult from the chooser is used.
- L50 _public member_ `bool DefaultRowValue = false;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L54 _public member_ `TArray<bool> RowValues;` — `UPROPERTY()`
- L56 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterBoolBase);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/OutputEnumColumn.h` (Public)


#### struct `FChooserOutputEnumRowData`  
`struct FChooserOutputEnumRowData`  
_L15-26_
- reflection: `USTRUCT()`
- L20 _public member_ `uint8 Value = 0;` — `UPROPERTY(EditAnywhere, Category = Runtime)`
- L24 _public member_ `FName ValueName;` — `UPROPERTY(EditAnywhere, Category = EditorOnly)`

#### struct `FOutputEnumColumn`  
`struct FOutputEnumColumn : public FEnumColumnBase`  
_L30-87_
- reflection: `USTRUCT(DisplayName = "Output Enum", Meta = (Category = "Output", Tooltip = "A column which writes an Enum value."))`
- inherits: `FEnumColumnBase`
- L34 _public prototype_ `FOutputEnumColumn();`
- L35 _public function_ `virtual bool HasFilters() const override`
- L36 _public function_ `virtual bool HasOutputs() const override`
- L37 _public prototype_ `virtual void SetOutputs(FChooserEvaluationContext& Context, int RowIndex) const override;`
- L40 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterEnumBase", ToolTip="The Enum property this column will write to"), Category = "Data")`
- L44 _public member_ `FChooserOutputEnumRowData FallbackValue;` — `UPROPERTY()` — FallbackValue will be used as the output value if the all rows in the chooser fail, and the FallbackResult from the chooser is used.
- L48 _public member_ `FChooserOutputEnumRowData DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L50 _public prototype_ `virtual void PostLoad() override;`
- L56 _public member_ `TArray<FChooserOutputEnumRowData> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L59 _public function_ `const UEnum* GetEnum() const`
- L69 _public member_ `mutable uint8 TestValue;`
- L71 _public prototype_ `virtual void AddToDetails (FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L72 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L73 _public function_ `virtual void CopyFallback(FChooserColumnBase& SourceColumn) override`
- L75 _public prototype_ `virtual void EnumChanged(const UEnum* Enum) override;`
- L77 _public function_ `FChooserOutputEnumRowData& GetValueForIndex(int32 Index)`
- L81 _public function_ `const FChooserOutputEnumRowData& GetValueForIndex(int32 Index) const`
- L86 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterEnumBase);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/OutputFloatColumn.h` (Public)


#### struct `FOutputFloatColumn`  
`struct FOutputFloatColumn : public FChooserColumnBase`  
_L14-57_
- reflection: `USTRUCT(DisplayName = "Output Float", Meta = (Category = "Output", Tooltip = "A column which writes a Float value."))`
- inherits: `FChooserColumnBase`
- L18 _public prototype_ `FOutputFloatColumn();`
- L19 _public function_ `virtual bool HasFilters() const override`
- L20 _public function_ `virtual bool HasOutputs() const override`
- L21 _public prototype_ `virtual void SetOutputs(FChooserEvaluationContext& Context, int RowIndex) const override;`
- L24 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, Meta = (ExcludeBaseStruct, NoClear, BaseStruct = "/Script/Chooser.ChooserParameterFloatBase", ToolTip="The Float property this column will write to"), Category = "Hidden")`
- L27 _public member_ `mutable double TestValue=false;`
- L29 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L30 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L31 _public function_ `virtual void CopyFallback(FChooserColumnBase& SourceColumn) override`
- L34 _public function_ `double& GetValueForIndex(int32 Index)`
- L39 _public function_ `double GetValueForIndex(int32 Index) const`
- L46 _public member_ `double FallbackValue = 0.0;` — `UPROPERTY()` — FallbackValue will be used as the output value if the all rows in the chooser fail, and the FallbackResult from the chooser is used.
- L50 _public member_ `double DefaultRowValue = 0.0;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L54 _public member_ `TArray<double> RowValues;` — `UPROPERTY()`
- L56 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterFloatBase);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/OutputGameplayTagColumn.h` (Public)


#### struct `FOutputGameplayTagColumn`  
`struct FOutputGameplayTagColumn : public FChooserColumnBase`  
_L15-58_
- reflection: `USTRUCT(DisplayName = "Output Gameplay Tag", Meta = (Category = "Output", Tooltip = "A column which writes a Gameplay Tag Container value."))`
- inherits: `FChooserColumnBase`
- L19 _public prototype_ `FOutputGameplayTagColumn();`
- L21 _public function_ `virtual bool HasFilters() const override`
- L22 _public function_ `virtual bool HasOutputs() const override`
- L23 _public prototype_ `virtual void SetOutputs(FChooserEvaluationContext& Context, int RowIndex) const override;`
- L26 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.FChooserParameterGameplayTagBase", ToolTip="The Gameplay Tag Container property this column will write to"), Category = "Hidden")`
- L30 _public member_ `FGameplayTagContainer DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L34 _public member_ `TArray<FGameplayTagContainer> RowValues;` — `UPROPERTY()`
- L37 _public member_ `mutable FGameplayTagContainer TestValue;`
- L38 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L39 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L40 _public function_ `virtual void CopyFallback(FChooserColumnBase& SourceColumn) override`
- L45 _public member_ `FGameplayTagContainer FallbackValue;` — `UPROPERTY()` — FallbackValue will be used as the output value if the all rows in the chooser fail, and the FallbackResult from the chooser is used.
- L47 _public function_ `FGameplayTagContainer& GetValueForIndex(int32 Index)`
- L52 _public function_ `const FGameplayTagContainer& GetValueForIndex(int32 Index) const`
- L57 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterGameplayTagBase);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/OutputGameplayTagQueryColumn.h` (Public)


#### struct `FGameplayTagQueryContextProperty`  
`struct FGameplayTagQueryContextProperty : public FChooserParameterGameplayTagQueryBase`  
_L15-26_
- reflection: `USTRUCT(DisplayName = "Gameplay Tags Query Property Binding")`
- inherits: `FChooserParameterGameplayTagQueryBase`
- L21 _public member_ `FChooserPropertyBinding Binding;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (BindingType = "FGameplayTagQuery", BindingColor = "StructPinTypeColor"), Category = "Binding")`
- L23 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, const FGameplayTagQuery& Value) const override;`
- L25 _public prototype_ `CHOOSER_PARAMETER_BOILERPLATE();`

#### struct `FOutputGameplayTagQueryColumn`  
`struct FOutputGameplayTagQueryColumn : public FChooserColumnBase`  
_L29-72_
- reflection: `USTRUCT(DisplayName = "Output Gameplay Tag Query", Meta = (Category = "Output", Tooltip = "A column which writes a Gameplay Tag Query value."))`
- inherits: `FChooserColumnBase`
- L33 _public prototype_ `FOutputGameplayTagQueryColumn();`
- L35 _public function_ `virtual bool HasFilters() const override`
- L36 _public function_ `virtual bool HasOutputs() const override`
- L37 _public prototype_ `virtual void SetOutputs(FChooserEvaluationContext& Context, int RowIndex) const override;`
- L40 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.FChooserParameterGameplayTagQueryBase", ToolTip="The Gameplay Tag Query property this column will write to"), Category = "Hidden")`
- L44 _public member_ `FGameplayTagQuery DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L48 _public member_ `TArray<FGameplayTagQuery> RowValues;` — `UPROPERTY()`
- L51 _public member_ `mutable FGameplayTagQuery TestValue;`
- L52 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L53 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L54 _public function_ `virtual void CopyFallback(FChooserColumnBase& SourceColumn) override`
- L59 _public member_ `FGameplayTagQuery FallbackValue;` — `UPROPERTY()` — FallbackValue will be used as the output value if the all rows in the chooser fail, and the FallbackResult from the chooser is used.
- L61 _public function_ `FGameplayTagQuery& GetValueForIndex(int32 Index)`
- L66 _public function_ `const FGameplayTagQuery& GetValueForIndex(int32 Index) const`
- L71 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterGameplayTagQueryBase);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/OutputNameColumn.h` (Public)


#### struct `FChooserOutputNameColumn`  
`struct FChooserOutputNameColumn : public FChooserColumnBase`  
_L18-91_
- reflection: `USTRUCT(DisplayName = "Output Name", Meta = (Category = "Output", Tooltip = "A column which writes a FName value."))`
- inherits: `FChooserColumnBase`
- L22 _public prototype_ `FChooserOutputNameColumn();`
- L23 _public function_ `virtual bool HasFilters() const override`
- L24 _public function_ `virtual bool HasOutputs() const override`
- L25 _public prototype_ `virtual void SetOutputs(FChooserEvaluationContext& Context, int RowIndex) const override;`
- L28 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterNameBase", ToolTip="The Name reference property this column will write to"), Category = "Hidden")`
- L31 _public member_ `TArray<FName> RowValues;` — `UPROPERTY()`
- L34 _public member_ `mutable FName TestValue = NAME_None;`
- L35 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L36 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L37 _public function_ `virtual void CopyFallback(FChooserColumnBase& SourceColumn) override`
- L40 _public function_ `FName& GetValueForIndex(int32 Index)`
- L54 _public function_ `FName GetValueForIndex(int32 Index) const`
- L70 _public member_ `FName FallbackValue = NAME_None;` — `UPROPERTY()` — FallbackValue will be used as the output value if the all rows in the chooser fail, and the FallbackResult from the chooser is used.
- L72 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterNameBase);`
- L75 _public function_ `virtual void PostLoad() override`
- L88 _public member_ `FName DefaultRowValue = NAME_None;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/OutputObjectColumn.h` (Public)


#### struct `FChooserOutputObjectRowData`  
`struct FChooserOutputObjectRowData`  
_L17-23_
- reflection: `USTRUCT(DisplayName = "Output Object", Meta = (Category = "Output", Tooltip = "A column which writes an Object reference."))`
- L22 _public member_ `FInstancedStruct Value;` — `UPROPERTY(EditAnywhere, Category="Value", Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ObjectChooserBase"))`

#### struct `FOutputObjectColumn`  
`struct FOutputObjectColumn : public FChooserColumnBase`  
_L26-84_
- reflection: `USTRUCT(DisplayName = "Output Object", Meta = (Category = "Output", Tooltip = "A column which an Object Reference."))`
- inherits: `FChooserColumnBase`
- L30 _public prototype_ `FOutputObjectColumn();`
- L33 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterObjectBase"), Category = "Data")`
- L37 _public member_ `FChooserOutputObjectRowData DefaultRowValue;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L43 _public member_ `TArray<FChooserOutputObjectRowData> RowValues;` — array of results (cells for this column for each row in the table) should match the length of the Results array
- L47 _public member_ `FChooserOutputObjectRowData FallbackValue;` — `UPROPERTY()` — FallbackValue will be used as the output value if the all rows in the chooser fail, and the FallbackResult from the chooser is used.
- L49 _public function_ `virtual bool HasFilters() const override`
- L50 _public function_ `virtual bool HasOutputs() const override`
- L51 _public prototype_ `virtual void SetOutputs(FChooserEvaluationContext& Context, int RowIndex) const override;`
- L54 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L55 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L56 _public function_ `virtual void CopyFallback(FChooserColumnBase& SourceColumn) override`
- L59 _public function_ `FChooserOutputObjectRowData& GetValueForIndex(int32 Index)`
- L64 _public function_ `const FChooserOutputObjectRowData& GetValueForIndex(int32 Index) const`
- L69 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterObjectBase);`
- L71 _public prototype_ `virtual void Compile(IHasContextClass* Owner, bool bForce) override;`
- L74 _public function_ `virtual void PostLoad() override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/OutputStructColumn.h` (Public)


#### struct `FStructContextProperty`  
`struct FStructContextProperty : public FChooserParameterStructBase`  
_L16-30_
- reflection: `USTRUCT(DisplayName = "Struct Property Binding")`
- inherits: `FChooserParameterStructBase`
- L21 _public member_ `FChooserStructPropertyBinding Binding;` — `UPROPERTY(EditAnywhere, Meta = (BindingType = "struct", BindingColor = "StructPinTypeColor"), Category = "Binding")`
- L23 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, const FInstancedStruct &Value) const override;`
- L25 _public prototype_ `CHOOSER_PARAMETER_BOILERPLATE();`
- L28 _public function_ `virtual UScriptStruct* GetStructType() const override`

#### struct `FOutputStructColumn`  
`struct FOutputStructColumn : public FChooserColumnBase`  
_L33-78_
- reflection: `USTRUCT(DisplayName = "Output Struct", Meta = (Category = "Output", Tooltip = "A column which writes all elements of a Struct.\n The data for each row must be set in the details panel, and the table cells will display values which differ from the struct default."))`
- inherits: `FChooserColumnBase`
- L37 _public prototype_ `FOutputStructColumn();`
- L38 _public function_ `virtual bool HasFilters() const override`
- L39 _public function_ `virtual bool HasOutputs() const override`
- L40 _public prototype_ `virtual void SetOutputs(FChooserEvaluationContext& Context, int RowIndex) const override;`
- L43 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterStructBase", ToolTip="The Struct property this column wil write to"), Category = "Hidden")`
- L46 _public prototype_ `virtual void InputValueChanged() override;`
- L47 _public prototype_ `void StructTypeChanged();`
- L48 _public member_ `mutable FInstancedStruct TestValue;`
- L50 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L51 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L52 _public function_ `virtual void CopyFallback(FChooserColumnBase& SourceColumn) override`
- L55 _public function_ `FInstancedStruct& GetValueForIndex(int32 Index)`
- L60 _public function_ `const FInstancedStruct& GetValueForIndex(int32 Index) const`
- L67 _public member_ `FInstancedStruct FallbackValue;` — `UPROPERTY()` — FallbackValue will be used as the output value if the all rows in the chooser fail, and the FallbackResult from the chooser is used.
- L71 _public member_ `FInstancedStruct DefaultRowValue;` — `UPROPERTY(EditAnywhere, Meta = (StructTypeConst, ToolTip="DefaultRowValue will be assigned to cells when new rows are created"), Category=Data)`
- L75 _public member_ `TArray<FInstancedStruct> RowValues;` — `UPROPERTY(EditAnywhere, Meta = (StructTypeConst), Category=Data)`
- L77 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterStructBase);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHOOSER_API`

### `Plugins/Chooser/Source/Chooser/Public/RandomizeColumn.h` (Public)


#### struct `FRandomizeContextProperty`  
`struct FRandomizeContextProperty : public FChooserParameterRandomizeBase`  
_L14-29_
- reflection: `USTRUCT(DisplayName = "Randomize Property Binding")`
- inherits: `FChooserParameterRandomizeBase`
- L20 _public member_ `FChooserPropertyBinding Binding;` — `UPROPERTY(EditAnywhere, Meta = (BindingType = "FChooserRandomizationContext", BindingAllowFunctions = "false", BindingColor = "StructPinTypeColor"), Category = "Binding")`
- L22 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, FChooserRandomizationContext*& OutResult) const override;`
- L23 _public function_ `virtual bool IsBound() const override`
- L28 _public prototype_ `CHOOSER_PARAMETER_BOILERPLATE();`

#### struct `FRandomizeColumn`  
`struct FRandomizeColumn : public FChooserColumnBase`  
_L32-112_
- reflection: `USTRUCT(DisplayName = "Randomize", Meta = (Category = "Random", Tooltip = "The Randomize column will randomly select between whatever values have passed all filters.\n The value specified in each cell is a probability weighting for the row.\n A row with a value twice as likely as another will be twice as likely to be selected.\n Using the optional RandomizationContext binding, it can track the most recent selection, and reduce the probability of randomly picking the same entry twice"))`
- inherits: `FChooserColumnBase`
- L36 _public prototype_ `FRandomizeColumn();`
- L39 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.RandomizeContextProperty", ToolTip="Optional reference to a ChooserRandomizationContext struct. If bound, this is used to store the most recent selection (for each Choosers referencing it - you only need to create one variable per Character or context), for use with RepateProbabilityMultiplier to reduce the chance of selecting the same entry twice."), Category = "Data")`
- L42 _public member_ `TArray<float> RepeatProbabilityMultipliers;` — `UPROPERTY(EditAnywhere, Category= "Data", meta=(ClampMin="0.0",Tooltip="Multiplies the weight of recently chosen results, where the number of entries in this array indicates how many recently selected choices to remember (A value of zero means to avoid repeating an entry unless it's the only choice). You must bind a RandomizationContext struct for this feature to work."))`
- L45 _public member_ `float EqualCostThreshold = 0.001f;` — `UPROPERTY(EditAnywhere, Category= "Data", meta=(ClampMin="0.0",Tooltip="When columns with scoring are used, randomize will pick from among all rows that have a cost nearly equal to the minumum cost, using this threshold"))`
- L49 _public member_ `float DefaultRowValue = 1.0f;` — `UPROPERTY(EditAnywhere, Category=Data, meta=(ToolTip="DefaultRowValue will be assigned to cells when new rows are created"))`
- L52 _public member_ `float RepeatProbabilityMultiplier = 1.0f;` — `UPROPERTY()`
- L56 _public member_ `TArray<float> RowValues;` — `UPROPERTY()`
- L58 _public prototype_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut) const override;`
- L59 _public prototype_ `virtual void SetOutputs(FChooserEvaluationContext& Context, int RowIndex) const override;`
- L61 _public function_ `virtual bool HasFilters() const override`
- L62 _public function_ `virtual bool HasOutputs() const override`
- L65 _public function_ `virtual bool EditorTestFilter(int32 RowIndex) const override`
- L70 _public prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L71 _public prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L73 _public function_ `virtual bool HasPrimaryInput() override`
- L79 _public function_ `virtual void PostLoad() override`
- L95 _public function_ `virtual void Compile(IHasContextClass* Owner, bool bForce) override`
- L107 _public prototype_ `CHOOSER_COLUMN_BOILERPLATE(FChooserParameterRandomizeBase);`
- L110 _public function_ `virtual bool IsRandomizeColumn() const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHOOSER_API`
