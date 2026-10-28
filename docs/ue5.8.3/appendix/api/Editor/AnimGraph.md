# Editor / AnimGraph

- module root: `Source/Editor/AnimGraph`
- headers: 168; symbols: 2928
- symbol kinds: class=176, delegate=7, enum=11, enumerator=40, function=339, macro=30, member=507, namespace=2, prototype=1772, struct=27, typedef=8, variable=9
- PrivateDependencyModuleNames: AnimationEditMode, ContentBrowser, DeveloperSettings, EditorFramework, EditorWidgets, GraphEditor, InputCore, Kismet, KismetCompiler, KismetWidgets, PropertyEditor, SlateCore, ToolMenus, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: AnimationBlueprintEditor
- PublicDependencyModuleNames: AnimGraphRuntime, BlueprintGraph, Core, CoreUObject, Engine, Slate

### `Source/Editor/AnimGraph/Internal/AnimBlueprintExtension_Base.h` (Internal)


#### class `UAnimBlueprintExtension_Base`  
`class UAnimBlueprintExtension_Base : public UAnimBlueprintExtension`  
_L26-283_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimBlueprintExtension`
- L32 _public prototype_ `void ProcessPosePins(UAnimGraphNode_Base* InNode, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Processes pose pins, building a map of pose links for later processing
- L44 _public prototype_ `FRIEND_ENUM_CLASS_FLAGS(EPinProcessingFlags);`
- L49 _public prototype_ `void ProcessNonPosePins(UAnimGraphNode_Base* InNode, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData, EPinProcessingFlags InFlags);` — Processes a node's non-pose pins: - Adds a map of struct eval handlers for the specified node - Builds property binding data
- L52 _public prototype_ `void CreateEvaluationHandlerForNode(IAnimBlueprintCompilationContext& InCompilationContext, UAnimGraphNode_Base* InNode);` — Create an 'expanded' evaluation handler for the specified node, called in the compiler's node expansion step
- L56 _private prototype_ `virtual void HandleStartCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;` — UAnimBlueprintExtension interface
- L57 _private prototype_ `virtual void HandleFinishCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L58 _private prototype_ `virtual void HandlePostExpansionStep(const UEdGraph* InGraph, IAnimBlueprintPostExpansionStepContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L59 _private prototype_ `virtual void HandleCopyTermDefaultsToDefaultObject(UObject* InDefaultObject, IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintExtensionCopyTermDefaultsContext& InPerExtensionContext) override;`
- L62 _private prototype_ `void PatchEvaluationHandlers(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Patch all node's evaluation handlers
- L260 _private prototype_ `void CreateEvaluationHandler(IAnimBlueprintCompilationContext& InCompilationContext, UAnimGraphNode_Base* InNode, FEvaluationHandlerRecord& Record);` — Create an evaluation handler for the specified node/record
- L263 _private prototype_ `void RedirectPropertyAccesses(IAnimBlueprintCompilationContext& InCompilationContext, UAnimGraphNode_Base* InNode, FEvaluationHandlerRecord& InRecord);` — Redirect any property accesses that are affected by constant folding
- L267 _private member_ `TMap<UAnimGraphNode_Base*, FEvaluationHandlerRecord> PerNodeStructEvalHandlers;` — Records of pose pins for later patchup with an associated evaluation handler
- L270 _private member_ `TArray<FEvaluationHandlerRecord> ValidEvaluationHandlerList;` — List of successfully created evaluation handlers
- L271 _private member_ `TMap<UAnimGraphNode_Base*, int32> ValidEvaluationHandlerMap;`
- L274 _private member_ `TSet<FName> HandlerFunctionNames;` — Set of used handler function names
- L277 _private member_ `FDelegateHandle PreLibraryCompiledDelegateHandle;` — Delegate handle for registering against library pre/post-compilation
- L278 _private member_ `FDelegateHandle PostLibraryCompiledDelegateHandle;`
- L282 _private member_ `FAnimSubsystem_Base Subsystem;` — `UPROPERTY()` — Base subsystem data containing eval handlers

#### enum `UAnimBlueprintExtension_Base::EPinProcessingFlags`  
`enum class EPinProcessingFlags : int32`  
_L34-42_
- L36 _public enumerator_ `Constants = (1 << 0)`
- L37 _public enumerator_ `BlueprintHandlers = (1 << 1)`
- L38 _public enumerator_ `PropertyAccessBindings = (1 << 3)`
- L39 _public enumerator_ `PropertyAccessFastPath = (1 << 4)`
- L41 _public enumerator_ `All = Constants | BlueprintHandlers | PropertyAccessBindings | PropertyAccessFastPath`

#### struct `UAnimBlueprintExtension_Base::FPropertyCopyRecord`  
`struct FPropertyCopyRecord`  
_L66-132_
- desc: Record of a single copy operation
- L68 _public function_ `FPropertyCopyRecord(UEdGraphPin* InDestPin, FProperty* InDestProperty, int32 InDestArrayIndex, TArray<FString>&& InDestPropertyPath) : DestPin(InDestPin) , DestProperty(InDestProperty) , DestArrayIndex(InDestArrayIndex) , DestPropertyPath(MoveTemp(InDestPropertyPath)) , BindingContextId(NAME_None) , Operation(EPostCopyOperation::None) , bIsFastPath(true) , bOnlyUpdateWhenActive(false)`
- L79 _public function_ `FPropertyCopyRecord(const TArray<FString>& InSourcePropertyPath, const TArray<FString>& InDestPropertyPath) : DestPin(nullptr) , DestProperty(nullptr) , DestArrayIndex(INDEX_NONE) , SourcePropertyPath(InSourcePropertyPath) , DestPropertyPath(InDestPropertyPath) , BindingContextId(NAME_None) , Operation(EPostCopyOperation::None) , bIsFastPath(true) , bOnlyUpdateWhenActive(false)`
- L91 _public function_ `bool IsFastPath() const`
- L96 _public function_ `void InvalidateFastPath()`
- L102 _public member_ `UEdGraphPin* DestPin;` — The destination pin we are copying to
- L105 _public member_ `FProperty* DestProperty;` — The destination property we are copying to (on an animation node)
- L108 _public member_ `int32 DestArrayIndex;` — The array index we use if the destination property is an array
- L111 _public member_ `TArray<FString> SourcePropertyPath;` — The property path relative to the class
- L114 _public member_ `TArray<FString> DestPropertyPath;` — The property path relative to the class
- L117 _public member_ `FPropertyAccessHandle LibraryHandle;` — The handle of the copy in the property access compiler
- L120 _public member_ `FCompiledPropertyAccessHandle LibraryCompiledHandle;` — The handle of the copy in the property access library
- L123 _public member_ `FName BindingContextId;` — Context in which a property binding occurs
- L126 _public member_ `EPostCopyOperation Operation;` — Any operation we want to perform post-copy on the destination data
- L129 _public member_ `bool bIsFastPath;` — Fast-path flag
- L131 _public member_ `bool bOnlyUpdateWhenActive;`

#### struct `UAnimBlueprintExtension_Base::FCopyRecordGraphCheckContext`  
`struct FCopyRecordGraphCheckContext`  
_L135-151_
- desc: Context used to build fast-path copy records
- L137 _public function_ `FCopyRecordGraphCheckContext(FPropertyCopyRecord& InCopyRecord, TArray<FPropertyCopyRecord>& InAdditionalCopyRecords, FCompilerResultsLog& InMessageLog) : CopyRecord(&InCopyRecord) , AdditionalCopyRecords(InAdditionalCopyRecords) , MessageLog(InMessageLog)`
- L144 _public member_ `FPropertyCopyRecord* CopyRecord;` — Copy record we are operating on
- L147 _public member_ `TArray<FPropertyCopyRecord>& AdditionalCopyRecords;` — Things like split input pins can add additional copy records
- L150 _public member_ `FCompilerResultsLog& MessageLog;` — Message log used to recover original nodes

#### struct `UAnimBlueprintExtension_Base::FAnimNodeSinglePropertyHandler`  
`struct FAnimNodeSinglePropertyHandler`  
_L154-166_
- desc: Wireup record for a single anim node property (which might be an array)
- L157 _public member_ `TArray<FPropertyCopyRecord> CopyRecords;` — Copy records
- L160 _public member_ `bool bInstanceIsTarget;` — If the anim instance is the container target instead of the node.
- L162 _public function_ `FAnimNodeSinglePropertyHandler() : bInstanceIsTarget(false)`

#### struct `UAnimBlueprintExtension_Base::FEvaluationHandlerRecord`  
`struct FEvaluationHandlerRecord`  
_L169-257_
- desc: BP execution handler for Anim node
- L173 _public member_ `UAnimGraphNode_Base* AnimGraphNode;` — The Node this record came from
- L176 _public member_ `FStructProperty* NodeVariableProperty;` — The node variable that the handler is in
- L179 _public member_ `int32 EvaluationHandlerIdx;` — The specific evaluation handler inside the specified node
- L182 _public member_ `bool bServicesNodeProperties;` — Whether or not our serviced properties are actually on the anim node
- L185 _public member_ `bool bServicesInstanceProperties;` — Whether or not our serviced properties are actually on the instance instead of the node
- L188 _public member_ `bool bHasProperties;` — This eval handler has properties
- L191 _public member_ `TMap<FName, FAnimNodeSinglePropertyHandler> ServicedProperties;` — Set of properties serviced by this handler (Map from property name to the record for that property)
- L194 _public member_ `TArray<UEdGraphNode*> CustomEventNodes;` — The generated custom event node
- L197 _public member_ `FName HandlerFunctionName;` — The resulting function name
- L201 _public function_ `FEvaluationHandlerRecord() : AnimGraphNode(nullptr) , NodeVariableProperty(nullptr) , EvaluationHandlerIdx(INDEX_NONE) , bServicesNodeProperties(false) , bServicesInstanceProperties(false) , bHasProperties(false) , HandlerFunctionName(NAME_None)`
- L211 _public function_ `bool IsFastPath() const`
- L228 _public function_ `bool IsValid() const`
- L234 _public prototype_ `void PatchAnimNodeExposedValueHandler(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext) const;`
- L236 _public prototype_ `void RegisterPin(UEdGraphPin* DestPin, FProperty* AssociatedProperty, int32 AssociatedPropertyArrayIndex, bool bAllowFastPath);`
- L238 _public prototype_ `void RegisterPropertyBinding(FProperty* InProperty, const FAnimGraphNodePropertyBinding& InBinding);`
- L240 _public function_ `FStructProperty* GetHandlerNodeProperty() const`
- L242 _public prototype_ `void BuildFastPathCopyRecords(IAnimBlueprintPostExpansionStepContext& InCompilationContext);`
- L246 _private prototype_ `bool CheckForVariableGet(FCopyRecordGraphCheckContext& Context, UEdGraphPin* DestPin);`
- L248 _private prototype_ `bool CheckForLogicalNot(FCopyRecordGraphCheckContext& Context, UEdGraphPin* DestPin);`
- L250 _private prototype_ `bool CheckForStructMemberAccess(FCopyRecordGraphCheckContext& Context, UEdGraphPin* DestPin);`
- L252 _private prototype_ `bool CheckForMemberOnlyAccess(FPropertyCopyRecord& Context, UEdGraphPin* DestPin);`
- L254 _private prototype_ `bool CheckForSplitPinAccess(FCopyRecordGraphCheckContext& Context, UEdGraphPin* DestPin);`
- L256 _private prototype_ `bool CheckForArrayAccess(FCopyRecordGraphCheckContext& Context, UEdGraphPin* DestPin);`

#### Free symbols / members of external scopes

- L285 _prototype_ `ENUM_CLASS_FLAGS(UAnimBlueprintExtension_Base::EPinProcessingFlags);`

### `Source/Editor/AnimGraph/Internal/AnimGraphNodeBinding.h` (Internal)


#### class `UAnimGraphNodeBinding`  
`class UAnimGraphNodeBinding : public UObject`  
_L16-70_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L26 _private function_ `virtual UScriptStruct* GetAnimNodeHandlerStruct() const PURE_VIRTUAL(UAnimGraphNodeBinding::GetAnimNodeHandlerStruct, return nullptr;)` — Get the struct type for the runtime handling of this binding
- L32 _private function_ `virtual void OnReconstructNode(UAnimGraphNode_Base* InNode)` — Override point for when the hosting node is reconstructed
- L35 _private function_ `virtual void OnExpandNode(IAnimBlueprintCompilationContext& InCompilationContext, UAnimGraphNode_Base* InNode, UEdGraph* InSourceGraph)` — Override point for when the hosting node is expanded during compilation
- L38 _private function_ `virtual bool HasBinding(FName InBindingName, bool bCheckArrayIndexName) const PURE_VIRTUAL(UAnimGraphNodeBinding::HasBinding, return false;)` — Check whether this binding binds to the specified name
- L46 _private function_ `virtual void HandleVariableRenamed(UBlueprint* InBlueprint, UClass* InVariableClass, UEdGraph* InGraph, const FName& InOldVarName, const FName& InNewVarName)`
- L48 _private function_ `virtual void HandleFunctionRenamed(UBlueprint* InBlueprint, UClass* InFunctionClass, UEdGraph* InGraph, const FName& InOldFuncName, const FName& InNewFuncName)`
- L50 _private function_ `virtual void ReplaceReferences(UBlueprint* InBlueprint, UBlueprint* InReplacementBlueprint, const FMemberReference& InSource, const FMemberReference& InReplacement)`
- L52 _private function_ `virtual bool ReferencesVariable(const FName& InVarName, const UStruct* InScope) const`
- L54 _private function_ `virtual bool ReferencesFunction(const FName& InFunctionName, const UStruct* InScope) const`
- L58 _private function_ `virtual void UpdateBindingNames(TFunctionRef<FString(const FString& InOldName)> InModifierFunction) PURE_VIRTUAL(UAnimGraphNodeBinding::UpdateBindingNames, )` — Update function for binding names - if a binding string tghat differs from InOldName is returned from InModifierFunction then the binding will be replaced
- L64 _private function_ `virtual void ProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData)` — Process binding for this node during compilation
- L68 _private function_ `virtual TSharedRef<SWidget> MakePropertyBindingWidget(const UAnimGraphNode_Base::FAnimPropertyBindingWidgetArgs& InArgs)` — Create the binding widget for a pin/property. This is only called on the CDO. Use InArgs to determine the nodes to create the widget for.

### `Source/Editor/AnimGraph/Private/AnimBlueprintCompilationContext.h` (Private)


#### class `FAnimBlueprintCompilationContext`  
`class FAnimBlueprintCompilationContext : public IAnimBlueprintCompilationContext`  
_L17-51_
- inherits: `IAnimBlueprintCompilationContext`
- L23 _private function_ `FAnimBlueprintCompilationContext(FAnimBlueprintCompilerContext* InCompilerContext) : CompilerContext(InCompilerContext)`
- L27 _private prototype_ `virtual void AddPoseLinkMappingRecordImpl(const FPoseLinkMappingRecord& InRecord) override;`
- L28 _private prototype_ `virtual void ProcessAnimationNodesImpl(TArray<UAnimGraphNode_Base*>& AnimNodeList) override;`
- L29 _private prototype_ `virtual void PruneIsolatedAnimationNodesImpl(const TArray<UAnimGraphNode_Base*>& RootSet, TArray<UAnimGraphNode_Base*>& GraphNodes) override;`
- L30 _private prototype_ `virtual void ExpansionStepImpl(UEdGraph* Graph, bool bAllowUbergraphExpansions) override;`
- L31 _private prototype_ `virtual FCompilerResultsLog& GetMessageLogImpl() const override;`
- L32 _private prototype_ `virtual bool ValidateGraphIsWellFormedImpl(UEdGraph* Graph) const override;`
- L33 _private prototype_ `virtual int32 GetAllocationIndexOfNodeImpl(UAnimGraphNode_Base* VisualAnimNode) const override;`
- L34 _private prototype_ `virtual const UBlueprint* GetBlueprintImpl() const override;`
- L35 _private prototype_ `virtual const UAnimBlueprint* GetAnimBlueprintImpl() const override;`
- L36 _private prototype_ `virtual UEdGraph* GetConsolidatedEventGraphImpl() const override;`
- L37 _private prototype_ `virtual void GetLinkedAnimNodesImpl(UAnimGraphNode_Base* InGraphNode, TArray<UAnimGraphNode_Base*>& LinkedAnimNodes) const override;`
- L38 _private prototype_ `virtual const TMap<UAnimGraphNode_Base*, int32>& GetAllocatedAnimNodeIndicesImpl() const override;`
- L39 _private prototype_ `virtual const TMap<UAnimGraphNode_Base*, UAnimGraphNode_Base*>& GetSourceNodeToProcessedNodeMapImpl() const override;`
- L40 _private prototype_ `virtual const TMap<int32, FProperty*>& GetAllocatedPropertiesByIndexImpl() const override;`
- L41 _private prototype_ `virtual const TMap<UAnimGraphNode_Base*, FProperty*>& GetAllocatedPropertiesByNodeImpl() const override;`
- L42 _private prototype_ `virtual const TMap<UAnimGraphNode_Base*, FProperty*>& GetAllocatedHandlerPropertiesByNodeImpl() const override;`
- L43 _private prototype_ `virtual void AddAttributesToNodeImpl(UAnimGraphNode_Base* InNode, TArrayView<const FName> InAttributes) const override;`
- L44 _private prototype_ `virtual TArrayView<const FName> GetAttributesFromNodeImpl(UAnimGraphNode_Base* InNode) const override;`
- L45 _private prototype_ `virtual bool IsAnimGraphNodeFoldedImpl(UAnimGraphNode_Base* InNode) const override;`
- L46 _private prototype_ `virtual const IAnimBlueprintCompilationContext::FFoldedPropertyRecord* GetFoldedPropertyRecordImpl(UAnimGraphNode_Base* InNode, FName InPropertyName) const override;`
- L47 _private prototype_ `virtual const FStructProperty* GetMutableDataPropertyImpl() const override;`
- L48 _private prototype_ `virtual FKismetCompilerContext* GetKismetCompiler() const override;`
- L50 _private member_ `FAnimBlueprintCompilerContext* CompilerContext;`

#### class `FAnimBlueprintCompilationBracketContext`  
`class FAnimBlueprintCompilationBracketContext : public IAnimBlueprintCompilationBracketContext`  
_L53-67_
- inherits: `IAnimBlueprintCompilationBracketContext`
- L58 _private function_ `FAnimBlueprintCompilationBracketContext(FAnimBlueprintCompilerContext* InCompilerContext) : CompilerContext(InCompilerContext)`
- L62 _private prototype_ `virtual FCompilerResultsLog& GetMessageLogImpl() const override;`
- L63 _private prototype_ `virtual const TMap<UAnimGraphNode_Base*, int32>& GetAllocatedAnimNodeIndicesImpl() const override;`
- L64 _private prototype_ `virtual const TMap<UAnimGraphNode_Base*, FProperty*>& GetAllocatedHandlerPropertiesByNodeImpl() const override;`
- L66 _private member_ `FAnimBlueprintCompilerContext* CompilerContext;`

#### class `FAnimBlueprintCopyTermDefaultsContext`  
`class FAnimBlueprintCopyTermDefaultsContext : public IAnimBlueprintCopyTermDefaultsContext`  
_L69-82_
- inherits: `IAnimBlueprintCopyTermDefaultsContext`
- L74 _private function_ `FAnimBlueprintCopyTermDefaultsContext(FAnimBlueprintCompilerContext* InCompilerContext) : CompilerContext(InCompilerContext)`
- L78 _private prototype_ `virtual FCompilerResultsLog& GetMessageLogImpl() const override;`
- L79 _private prototype_ `virtual const UAnimBlueprint* GetAnimBlueprintImpl() const override;`
- L81 _private member_ `FAnimBlueprintCompilerContext* CompilerContext;`

#### class `FAnimBlueprintNodeCopyTermDefaultsContext`  
`class FAnimBlueprintNodeCopyTermDefaultsContext : public IAnimBlueprintNodeCopyTermDefaultsContext`  
_L84-108_
- inherits: `IAnimBlueprintNodeCopyTermDefaultsContext`
- L89 _private function_ `FAnimBlueprintNodeCopyTermDefaultsContext(UObject* InCDO, const FProperty* InTargetProperty, uint8* InDestinationPtr, const uint8* InSourcePtr, int32 InNodePropertyIndex) : CDO(InCDO) , TargetProperty(InTargetProperty) , DestinationPtr(InDestinationPtr) , SourcePtr(InSourcePtr) , NodePropertyIndex(InNodePropertyIndex)`
- L97 _private function_ `virtual UObject* GetClassDefaultObjectImpl() const override`
- L98 _private function_ `virtual const FProperty* GetTargetPropertyImpl() const override`
- L99 _private function_ `virtual uint8* GetDestinationPtrImpl() const override`
- L100 _private function_ `virtual const uint8* GetSourcePtrImpl() const override`
- L101 _private function_ `virtual int32 GetNodePropertyIndexImpl() const override`
- L103 _private member_ `UObject* CDO;`
- L104 _private member_ `const FProperty* TargetProperty;`
- L105 _private member_ `uint8* DestinationPtr;`
- L106 _private member_ `const uint8* SourcePtr;`
- L107 _private member_ `int32 NodePropertyIndex;`

#### class `FAnimBlueprintExtensionCopyTermDefaultsContext`  
`class FAnimBlueprintExtensionCopyTermDefaultsContext : public IAnimBlueprintExtensionCopyTermDefaultsContext`  
_L110-134_
- inherits: `IAnimBlueprintExtensionCopyTermDefaultsContext`
- L115 _private function_ `FAnimBlueprintExtensionCopyTermDefaultsContext(UObject* InCDO, const FProperty* InTargetProperty, uint8* InDestinationPtr, const uint8* InSourcePtr, int32 InNodePropertyIndex) : CDO(InCDO) , TargetProperty(InTargetProperty) , DestinationPtr(InDestinationPtr) , SourcePtr(InSourcePtr) , NodePropertyIndex(InNodePropertyIndex)`
- L123 _private function_ `virtual UObject* GetClassDefaultObjectImpl() const override`
- L124 _private function_ `virtual const FProperty* GetTargetPropertyImpl() const override`
- L125 _private function_ `virtual uint8* GetDestinationPtrImpl() const override`
- L126 _private function_ `virtual const uint8* GetSourcePtrImpl() const override`
- L127 _private function_ `virtual int32 GetNodePropertyIndexImpl() const override`
- L129 _private member_ `UObject* CDO;`
- L130 _private member_ `const FProperty* TargetProperty;`
- L131 _private member_ `uint8* DestinationPtr;`
- L132 _private member_ `const uint8* SourcePtr;`
- L133 _private member_ `int32 NodePropertyIndex;`

#### class `FAnimBlueprintPostExpansionStepContext`  
`class FAnimBlueprintPostExpansionStepContext : public IAnimBlueprintPostExpansionStepContext`  
_L136-151_
- inherits: `IAnimBlueprintPostExpansionStepContext`
- L141 _private function_ `FAnimBlueprintPostExpansionStepContext(FAnimBlueprintCompilerContext* InCompilerContext) : CompilerContext(InCompilerContext)`
- L145 _private prototype_ `virtual FCompilerResultsLog& GetMessageLogImpl() const override;`
- L146 _private prototype_ `virtual UEdGraph* GetConsolidatedEventGraphImpl() const override;`
- L147 _private prototype_ `virtual const FKismetCompilerOptions& GetCompileOptionsImpl() const override;`
- L148 _private prototype_ `virtual const TMap<UAnimGraphNode_Base*, int32>& GetAllocatedAnimNodeIndicesImpl() const override;`
- L150 _private member_ `FAnimBlueprintCompilerContext* CompilerContext;`

#### class `FAnimBlueprintNodeOverrideAssetsContext`  
`class FAnimBlueprintNodeOverrideAssetsContext : public IAnimBlueprintNodeOverrideAssetsContext`  
_L153-178_
- inherits: `IAnimBlueprintNodeOverrideAssetsContext`
- L158 _private function_ `FAnimBlueprintNodeOverrideAssetsContext(FAnimNode_Base* InAnimNode, UScriptStruct* InAnimNodeType) : AnimNode(InAnimNode) , AnimNodeType(InAnimNodeType)`
- L164 _private function_ `void AddAsset(UObject* InAsset)` — Add an asset to this context
- L166 _private function_ `virtual FAnimNode_Base* GetAnimNodeImpl() const override`
- L167 _private function_ `virtual UScriptStruct* GetAnimNodeTypeImpl() const override`
- L168 _private function_ `virtual TArrayView<UObject* const> GetAssetsImpl() const override`
- L171 _private member_ `FAnimNode_Base* AnimNode;` — The anim node we are targeting
- L174 _private member_ `UScriptStruct* AnimNodeType;` — The type of the anim node we are targeting
- L177 _private member_ `TArray<UObject*> Assets;` — All the assets to override

### `Source/Editor/AnimGraph/Private/AnimBlueprintCompiler.h` (Private)


#### class `FAnimBlueprintCompilerContext`  
`class FAnimBlueprintCompilerContext : public FKismetCompilerContext`  
_L42-216_
- inherits: `FKismetCompilerContext`
- desc: FAnimBlueprintCompilerContext
- L53 _protected typedef_ `typedef FKismetCompilerContext Super;`
- L55 _public prototype_ `FAnimBlueprintCompilerContext(UAnimBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompileOptions);`
- L56 _public prototype_ `virtual ~FAnimBlueprintCompilerContext();`
- L60 _protected prototype_ `virtual void CreateClassVariablesFromBlueprint() override;` — Implementation of FKismetCompilerContext interface
- L61 _protected prototype_ `virtual UEdGraphSchema_K2* CreateSchema() override;`
- L62 _protected prototype_ `virtual void MergeUbergraphPagesIn(UEdGraph* Ubergraph) override;`
- L63 _protected prototype_ `virtual void ProcessOneFunctionGraph(UEdGraph* SourceGraph, bool bInternalFunction = false) override;`
- L64 _protected prototype_ `virtual void SpawnNewClass(const FString& NewClassName) override;`
- L65 _protected prototype_ `virtual void OnNewClassSet(UBlueprintGeneratedClass* ClassToUse) override;`
- L66 _protected prototype_ `virtual void OnPostCDOCompiled(const UObject::FPostCDOCompiledContext& Context) override;`
- L67 _protected prototype_ `virtual void CopyTermDefaultsToDefaultObject(UObject* DefaultObject) override;`
- L68 _protected prototype_ `virtual void PostCompile() override;`
- L69 _protected prototype_ `virtual void PostCompileDiagnostics() override;`
- L70 _protected prototype_ `virtual void EnsureProperGeneratedClass(UClass*& TargetClass) override;`
- L71 _protected prototype_ `virtual void CleanAndSanitizeClass(UBlueprintGeneratedClass* ClassToClean, UObject*& InOldCDO) override;`
- L72 _protected prototype_ `virtual void FinishCompilingClass(UClass* Class) override;`
- L73 _protected prototype_ `virtual void PrecompileFunction(FKismetFunctionContext& Context, EInternalCompilerFlags InternalFlags) override;`
- L74 _protected prototype_ `virtual void SetCalculatedMetaDataAndFlags(UFunction* Function, UK2Node_FunctionEntry* EntryNode, const UEdGraphSchema_K2* Schema ) override;`
- L75 _protected prototype_ `virtual bool ShouldForceKeepNode(const UEdGraphNode* Node) const override;`
- L76 _protected prototype_ `virtual void PostExpansionStep(const UEdGraph* Graph) override;`
- L77 _protected prototype_ `virtual void PreCompileUpdateBlueprintOnLoad(UBlueprint* BP) override;`
- L81 _protected typedef_ `typedef TArray<UEdGraphPin*> UEdGraphPinArray;`
- L84 _protected member_ `UScriptStruct* NewAnimBlueprintConstants;`
- L85 _protected member_ `UScriptStruct* NewAnimBlueprintMutables;`
- L86 _protected member_ `FStructProperty* NewMutablesProperty;`
- L87 _protected member_ `UAnimBlueprint* AnimBlueprint;`
- L90 _protected member_ `UScriptStruct* OldSparseClassDataStruct;` — Old sparse class data stored to patchup linker when doing a full compile
- L92 _protected member_ `UAnimationGraphSchema* AnimSchema;`
- L95 _protected member_ `TMap<class UAnimGraphNode_Base*, FProperty*> AllocatedAnimNodes;` — Map of allocated v3 nodes that are members of the class
- L96 _protected member_ `TMap<class UAnimGraphNode_Base*, FProperty*> AllocatedAnimNodeHandlers;`
- L97 _protected member_ `TMap<FProperty*, class UAnimGraphNode_Base*> AllocatedNodePropertiesToNodes;`
- L98 _protected member_ `TMap<FProperty*, class UAnimGraphNode_Base*> AllocatedNodeConstantPropertiesToNodes;`
- L99 _protected member_ `TMap<int32, FProperty*> AllocatedPropertiesByIndex;`
- L102 _protected member_ `TMap<class UAnimGraphNode_Base*, UAnimGraphNode_Base*> SourceNodeToProcessedNodeMap;` — Map of true source objects (user edited ones) to the cloned ones that are actually compiled
- L105 _protected member_ `int32 AllocateNodeIndexCounter;` — Index of the nodes (must match up with the runtime discovery process of nodes, which runs thru the property chain)
- L106 _protected member_ `TMap<class UAnimGraphNode_Base*, int32> AllocatedAnimNodeIndices;`
- L110 _protected member_ `TArray<FPoseLinkMappingRecord> ValidPoseLinkList;` — Map from pose link LinkID address @TODO: Bad structure for a list of these
- L113 _protected member_ `TArray<UEdGraph*> GeneratedStubGraphs;` — Stub graphs we generated for animation graph functions
- L116 _protected member_ `bool bIsDerivedAnimBlueprint;` — True if any parent class is also generated from an animation blueprint
- L119 _protected member_ `TArray<TSubclassOf<UEdGraphSchema>> KnownGraphSchemas;` — Graph schema classes that this compiler is aware of - they will skip default function processing
- L125 _protected member_ `TArray<TSharedRef<IAnimBlueprintCompilationContext::FFoldedPropertyRecord>> ConstantPropertyRecords;` — Records of folded properties gleaned from nodes
- L126 _protected member_ `TArray<TSharedRef<IAnimBlueprintCompilationContext::FFoldedPropertyRecord>> MutablePropertyRecords;`
- L129 _protected member_ `TMap<UAnimGraphNode_Base*, TArray<TSharedRef<IAnimBlueprintCompilationContext::FFoldedPropertyRecord>>> NodeToFoldedPropertyRecordMap;` — Allows lookups to see if a node participates in constant folding
- L132 _protected member_ `TMap<UAnimBlueprintExtension*, FStructProperty*> ExtensionToInstancePropertyMap;` — Maps of extension <-> generated property on the instance
- L133 _protected member_ `TMap<FStructProperty*, UAnimBlueprintExtension*> InstancePropertyToExtensionMap;`
- L136 _protected member_ `TMap<UAnimBlueprintExtension*, FStructProperty*> ExtensionToClassPropertyMap;` — Maps of extension <-> generated property on the class
- L137 _protected member_ `TMap<FStructProperty*, UAnimBlueprintExtension*> ClassPropertyToExtensionMap;`
- L141 _private function_ `UAnimBlueprintGeneratedClass* GetNewAnimBlueprintClass() const` — Get the generated class as an anim blueprint generated class
- L144 _private prototype_ `void ForAllSubGraphs(UEdGraph* InGraph, TFunctionRef<void(UEdGraph*)> InPerGraphFunction);` — Run a function on the passed-in graph and each subgraph of it
- L147 _private prototype_ `void PruneIsolatedAnimationNodes(const TArray<UAnimGraphNode_Base*>& RootSet, TArray<UAnimGraphNode_Base*>& GraphNodes);` — Prunes any nodes that aren't reachable via a pose link
- L150 _private prototype_ `void ProcessAnimationNode(UAnimGraphNode_Base* VisualAnimNode);` — Compiles one animation node
- L153 _private prototype_ `void GatherFoldRecordsForAnimationNode(const UScriptStruct* InNodeType, FStructProperty* InNodeProperty, UAnimGraphNode_Base* InVisualAnimNode);` — Called during ProcessAnimationNode - gather property folding records for the node
- L156 _private prototype_ `void ProcessAllAnimationNodes();` — Compiles an entire animation graph
- L159 _private prototype_ `void ProcessAnimationNodes(TArray<UAnimGraphNode_Base*>& AnimNodeList);` — Processes all the supplied anim nodes
- L162 _private prototype_ `void ProcessExtensions();` — Process all the requested extensions
- L165 _private prototype_ `void GetLinkedAnimNodes(UAnimGraphNode_Base* InGraphNode, TArray<UAnimGraphNode_Base*>& LinkedAnimNodes) const;` — Gets all anim graph nodes that are piped into the provided node (traverses input pins)
- L166 _private prototype_ `void GetLinkedAnimNodes_TraversePin(UEdGraphPin* InPin, TArray<UAnimGraphNode_Base*>& LinkedAnimNodes) const;`
- L167 _private prototype_ `void GetLinkedAnimNodes_ProcessAnimNode(UAnimGraphNode_Base* AnimNode, TArray<UAnimGraphNode_Base*>& LinkedAnimNodes) const;`
- L170 _private prototype_ `int32 GetAllocationIndexOfNode(UAnimGraphNode_Base* VisualAnimNode);` — Returns the allocation index of the specified node, processing it if it was pending
- L173 _private prototype_ `void CreateAnimGraphStubFunctions();` — Create transient stub functions for each anim graph we are compiling
- L176 _private prototype_ `void DestroyAnimGraphStubFunctions();` — Clean up transient stub functions
- L179 _private prototype_ `void ExpandSplitPins(UEdGraph* InGraph);` — Expands split pins for a graph
- L182 _private prototype_ `void AddAttributesToNode(UAnimGraphNode_Base* InNode, TArrayView<const FName> InAttributes) const;` — Add the specified compiled-in attribute uniquely to the specified node
- L185 _private prototype_ `TArrayView<const FName> GetAttributesFromNode(UAnimGraphNode_Base* InNode) const;` — Get the current compiled-in attributes uniquely assigned to the specified node
- L188 _private prototype_ `void RecreateMutables();` — Called at the start of compilation to (re-) create the mutable struct
- L194 _private prototype_ `void RecreateSparseClassData();` — (Re-)creates sparse class data structure. Called at the start of compilation to (re-) create the internal sparse class data. For derived anim BPs this is called just-in-time before CDO copy. This is to ensure that the sparse class data is always updated, as in some cases as the layout does not change a full compilation of a (data-only) derived anim BP may be skipped.
- L197 _private prototype_ `FProperty* CreateUniqueVariable(UObject* InForObject, const FEdGraphPinType& Type);` — Create a uniquely named variable corresponding to an object in the current class
- L200 _private prototype_ `FProperty* CreateStructVariable(UScriptStruct* InStruct, const FName VarName, const FEdGraphPinType& VarType);` — Creates a variable on the specified struct
- L203 _private prototype_ `void AddFoldedPropertyRecord(UAnimGraphNode_Base* InAnimGraphNode, FStructProperty* InAnimNodeProperty, FProperty* InProperty, bool bInExposedOnPin, bool bInPinConnected, bool bInAlwaysDynamic);` — Adds a record for a potentially-folded anim node property
- L206 _private prototype_ `void ProcessFoldedPropertyRecords();` — Process any anim node properties that are 'foldable'
- L209 _private prototype_ `bool IsAnimGraphNodeFolded(UAnimGraphNode_Base* InNode) const;` — Check whether an anim node participates in constant folding
- L212 _private prototype_ `void CopyAnimNodeDataFromRoot() const;` — Copy the AnimNodeData array etc. from root anim BP class to a derived anim BP
- L215 _private prototype_ `const IAnimBlueprintCompilationContext::FFoldedPropertyRecord* GetFoldedPropertyRecord(UAnimGraphNode_Base* InNode, FName InPropertyName) const;` — Get the folded property record, if any, for the supplied node & named property

### `Source/Editor/AnimGraph/Private/AnimBlueprintCompilerCreationContext.h` (Private)


#### class `FAnimBlueprintCompilerCreationContext`  
`class FAnimBlueprintCompilerCreationContext : public IAnimBlueprintCompilerCreationContext`  
_L11-25_
- inherits: `IAnimBlueprintCompilerCreationContext`
- L16 _private function_ `FAnimBlueprintCompilerCreationContext(FAnimBlueprintCompilerContext* InCompilerContext) : CompilerContext(InCompilerContext)`
- L21 _private prototype_ `virtual void RegisterKnownGraphSchema(TSubclassOf<UEdGraphSchema> InGraphSchemaClass) override;` — IAnimBlueprintCompilerCreationContext interface
- L24 _private member_ `FAnimBlueprintCompilerContext* CompilerContext;`

### `Source/Editor/AnimGraph/Private/AnimBlueprintDetails.h` (Private)


#### class `FAnimBlueprintDetails`  
`class FAnimBlueprintDetails : public IDetailCustomization`  
_L10-20_
- inherits: `IDetailCustomization`
- L13 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/AnimGraph/Private/AnimBlueprintExtension_Attributes.h` (Private)


#### class `UAnimBlueprintExtension_Attributes`  
`class UAnimBlueprintExtension_Attributes : public UAnimBlueprintExtension`  
_L16-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimBlueprintExtension`
- desc: Extension to propogate attributes from outputs to inputs and to build a static debug record of their path through the graph
- L22 _private prototype_ `virtual void HandlePostProcessAnimationNodes(TArrayView<UAnimGraphNode_Base*> InAnimNodes, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;` — UAnimBlueprintExtension interface

### `Source/Editor/AnimGraph/Private/AnimBlueprintExtension_BlendSpaceGraph.h` (Private)


#### class `UAnimBlueprintExtension_BlendSpaceGraph`  
`class UAnimBlueprintExtension_BlendSpaceGraph : public UAnimBlueprintExtension`  
_L12-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimBlueprintExtension`
- L19 _private prototype_ `virtual void HandleStartCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;` — UAnimBlueprintExtension interface
- L24 _private prototype_ `UBlendSpace* AddBlendSpace(UBlendSpace* InSourceBlendSpace);` — Add a class-internal blendspace @param	InSourceBlendSpace	The blendspace to duplicate @return a duplicate of the blendspace outered to the class
- L29 _private member_ `TObjectPtr<UClass> Class;` — `UPROPERTY(Transient)` — The class that is being compiled
- L33 _private member_ `FAnimSubsystem_BlendSpaceGraph Subsystem;` — `UPROPERTY()`

### `Source/Editor/AnimGraph/Private/AnimBlueprintExtension_CachedPose.h` (Private)


#### class `UAnimBlueprintExtension_CachedPose`  
`class UAnimBlueprintExtension_CachedPose : public UAnimBlueprintExtension`  
_L17-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimBlueprintExtension`
- L23 _public prototype_ `const TMap<FString, UAnimGraphNode_SaveCachedPose*>& GetSaveCachedPoseNodes() const;` — Get the map of cache name to encountered save cached pose nodes
- L26 _private prototype_ `virtual void HandleStartCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L27 _private prototype_ `virtual void HandlePreProcessAnimationNodes(TArrayView<UAnimGraphNode_Base*> InAnimNodes, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L28 _private prototype_ `virtual void HandlePostProcessAnimationNodes(TArrayView<UAnimGraphNode_Base*> InAnimNodes, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L31 _private prototype_ `void BuildCachedPoseNodeUpdateOrder(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Builds the update order list for saved pose nodes in this blueprint
- L34 _private prototype_ `void CachePoseNodeOrdering_StartNewTraversal(IAnimBlueprintCompilationContext& InCompilationContext, UAnimGraphNode_Base* InRootNode, TArray<UAnimGraphNode_SaveCachedPose*> &OrderedSavePoseNodes, TArray<UAnimGraphNode_Base*> VisitedRootNodes);` — Traverses a graph to collect save pose nodes starting at InRootNode, then processes each node
- L37 _private prototype_ `void CachePoseNodeOrdering_TraverseInternal_SubGraph(IAnimBlueprintCompilationContext& InCompilationContext, UEdGraph* InGraph, TArray<UAnimGraphNode_SaveCachedPose*> &OrderedSavePoseNodes);` — Traverse a node's subgraph to collect save pose nodes
- L40 _private prototype_ `void CachePoseNodeOrdering_TraverseInternal(IAnimBlueprintCompilationContext& InCompilationContext, UAnimGraphNode_Base* InAnimGraphNode, TArray<UAnimGraphNode_SaveCachedPose*> &OrderedSavePoseNodes);` — Traverses a graph to collect save pose nodes starting at InAnimGraphNode, does NOT process saved pose nodes afterwards
- L44 _private member_ `TMap<FString, UAnimGraphNode_SaveCachedPose*> SaveCachedPoseNodes;` — Map of cache name to encountered save cached pose nodes

### `Source/Editor/AnimGraph/Private/AnimBlueprintExtension_CallFunction.h` (Private)


#### class `UAnimBlueprintExtension_CallFunction`  
`class UAnimBlueprintExtension_CallFunction : public UAnimBlueprintExtension`  
_L12-31_
- reflection: `UCLASS()`
- inherits: `UAnimBlueprintExtension`
- L17 _public prototype_ `virtual void HandleStartCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L20 _public prototype_ `FName AddCustomEventName(UAnimGraphNode_Base* InNode);` — Add a custom event name for the specified node
- L23 _public prototype_ `FName FindCustomEventName(UAnimGraphNode_Base* InNode) const;` — Find the custom event name for the specified node. @return NAME_None if the node was not found
- L27 _private member_ `int32 Counter = 0;` — Counter to allow us to create unique stub function names
- L30 _private member_ `TMap<UAnimGraphNode_Base*, FName> CustomEventNames;` — Set of used custom event names per-node

### `Source/Editor/AnimGraph/Private/AnimBlueprintExtension_LinkedAnimGraph.h` (Private)


#### class `UAnimBlueprintExtension_LinkedAnimGraph`  
`class UAnimBlueprintExtension_LinkedAnimGraph : public UAnimBlueprintExtension`  
_L15-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimBlueprintExtension`
- L21 _private prototype_ `virtual void HandlePreProcessAnimationNodes(TArrayView<UAnimGraphNode_Base*> InAnimNodes, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;` — UAnimBlueprintExtension interface

### `Source/Editor/AnimGraph/Private/AnimBlueprintExtension_LinkedInputPose.h` (Private)


#### class `UAnimBlueprintExtension_LinkedInputPose`  
`class UAnimBlueprintExtension_LinkedInputPose : public UAnimBlueprintExtension`  
_L15-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimBlueprintExtension`
- L21 _private prototype_ `virtual void HandlePreProcessAnimationNodes(TArrayView<UAnimGraphNode_Base*> InAnimNodes, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;` — UAnimBlueprintExtension interface

### `Source/Editor/AnimGraph/Private/AnimBlueprintExtension_NodeRelevancy.h` (Private)


#### class `UAnimBlueprintExtension_NodeRelevancy`  
`class UAnimBlueprintExtension_NodeRelevancy : public UAnimBlueprintExtension`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimBlueprintExtension`
- L17 _private member_ `FAnimSubsystemInstance_NodeRelevancy Subsystem;` — `UPROPERTY()`

### `Source/Editor/AnimGraph/Private/AnimBlueprintExtension_SharedLinkedAnimLayers.h` (Private)


#### class `UAnimBlueprintExtension_SharedLinkedAnimLayers`  
`class UAnimBlueprintExtension_SharedLinkedAnimLayers : public UAnimBlueprintExtension`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimBlueprintExtension`
- L17 _private member_ `FAnimSubsystem_SharedLinkedAnimLayers Subsystem;` — `UPROPERTY()`

### `Source/Editor/AnimGraph/Private/AnimBlueprintExtension_StateMachine.h` (Private)


#### class `UAnimBlueprintExtension_StateMachine`  
`class UAnimBlueprintExtension_StateMachine : public UAnimBlueprintExtension`  
_L23-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimBlueprintExtension`
- L34 _public prototype_ `int32 ExpandGraphAndProcessNodes(UEdGraph* SourceGraph, UAnimGraphNode_Base* SourceRootNode, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData, UAnimStateTransitionNode* TransitionNode = nullptr, TArray<UEdGraphNode*>* ClonedNodes = nullptr);` — This function does the following steps: Clones the nodes in the specified source graph Merges them into the ConsolidatedEventGraph Processes any animation nodes Returns the index of the processed cloned version of SourceRootNode If supplied, will also return an array of all cloned nodes
- L38 _private prototype_ `virtual void HandleBeginCompilation(IAnimBlueprintCompilerCreationContext& InCreationContext) override;` — UAnimBlueprintExtension interface
- L39 _private prototype_ `virtual void HandleStartCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L40 _private prototype_ `virtual void HandlePreProcessAnimationNodes(TArrayView<UAnimGraphNode_Base*> InAnimNodes, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L41 _private prototype_ `virtual void HandlePostProcessAnimationNodes(TArrayView<UAnimGraphNode_Base*> InAnimNodes, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L44 _private prototype_ `UK2Node_CallFunction* SpawnCallAnimInstanceFunction(IAnimBlueprintCompilationContext& InCompilationContext, UEdGraphNode* SourceNode, FName FunctionName);` — Spawns a function call node, calling a function on the anim instance
- L47 _private prototype_ `void ProcessTransitionGetter(UK2Node_TransitionRuleGetter* Getter, UAnimStateTransitionNode* TransitionNode, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Convert transition getters into a function call/etc...
- L50 _private prototype_ `void AutoWireAnimGetter(UK2Node_AnimGetter* Getter, UAnimStateTransitionNode* InTransitionNode, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Automatically fill in parameters for the specified Getter node
- L54 _private member_ `TArray<UK2Node_AnimGetter*> FoundGetterNodes;` — List of getter node's we've found so the auto-wire can be deferred till after state machine compilation
- L57 _private member_ `TArray<UK2Node_TransitionRuleGetter*> RootTransitionGetters;` — Preprocessed lists of getters from the root of the ubergraph
- L58 _private member_ `TArray<UK2Node_AnimGetter*> RootGraphAnimGetters;`

### `Source/Editor/AnimGraph/Private/AnimBlueprintExtension_Tag.h` (Private)


#### class `UAnimBlueprintExtension_Tag`  
`class UAnimBlueprintExtension_Tag : public UAnimBlueprintExtension`  
_L16-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimBlueprintExtension`
- L22 _public prototype_ `void AddTaggedNode(UAnimGraphNode_Base* InNode, IAnimBlueprintCompilationContext& InCompilationContext);` — Add a tagged node
- L25 _public prototype_ `void RequestTaggedNode(UK2Node_AnimNodeReference* InNode, const FName InTag, UK2Node_CallFunction* InCallFunction);` — Register the provided node to be hooked-up to the given tag during HandlePostProcessAnimationNodes, if the tag exists, error otherwise
- L29 _private prototype_ `virtual void HandleStartCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;` — UAnimBlueprintExtension interface
- L30 _private prototype_ `virtual void HandlePostExpansionStep(const UEdGraph* InGraph, IAnimBlueprintPostExpansionStepContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L31 _private prototype_ `virtual void HandleFinishCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L35 _private member_ `TMap<FName, UAnimGraphNode_Base*> TaggedNodes;` — Map of tag -> tagged nodes
- L45 _private member_ `TArray<FNodeReferenceTag> RequestedNodes;` — Array of nodes to process during HandlePostProcessAnimationNodes
- L48 _private member_ `FAnimSubsystem_Tag Subsystem;` — `UPROPERTY()`

#### struct `UAnimBlueprintExtension_Tag::FNodeReferenceTag`  
`struct FNodeReferenceTag`  
_L37-42_
- L39 _public member_ `UK2Node_AnimNodeReference* Node = nullptr;`
- L40 _public member_ `UK2Node_CallFunction* CallFunction = nullptr;`
- L41 _public member_ `FName Tag;`

### `Source/Editor/AnimGraph/Private/AnimBlueprintGeneratedClassCompiledData.h` (Private)


#### class `FAnimBlueprintGeneratedClassCompiledData`  
`class FAnimBlueprintGeneratedClassCompiledData : public IAnimBlueprintGeneratedClassCompiledData`  
_L9-30_
- inherits: `IAnimBlueprintGeneratedClassCompiledData`
- L12 _public function_ `FAnimBlueprintGeneratedClassCompiledData(UAnimBlueprintGeneratedClass* InClass) : Class(InClass)`
- L18 _private prototype_ `virtual TArray<FBakedAnimationStateMachine>& GetBakedStateMachines() const override;` — IAnimBlueprintGeneratedClassCompiledData interface
- L19 _private prototype_ `virtual TMap<FName, FCachedPoseIndices>& GetOrderedSavedPoseIndicesMap() const override;`
- L20 _private prototype_ `virtual FBlueprintDebugData& GetBlueprintDebugData() const override;`
- L21 _private prototype_ `virtual TArray<FAnimNotifyEvent>& GetAnimNotifies() const override;`
- L22 _private prototype_ `virtual int32 FindOrAddNotify(FAnimNotifyEvent& Notify) const override;`
- L23 _private prototype_ `virtual FAnimBlueprintDebugData& GetAnimBlueprintDebugData() const override;`
- L24 _private prototype_ `virtual TMap<FName, FGraphAssetPlayerInformation>& GetGraphAssetPlayerInformation() const override;`
- L25 _private prototype_ `virtual UBlendSpace* AddBlendSpace(UBlendSpace* InSourceBlendSpace) override;`
- L29 _private member_ `UAnimBlueprintGeneratedClass* Class;` — The class we are wrapping

### `Source/Editor/AnimGraph/Private/AnimBlueprintNodeOptionalPinManager.h` (Private)


#### struct `FAnimBlueprintNodeOptionalPinManager`  
`struct FAnimBlueprintNodeOptionalPinManager : public FOptionalPinManager`  
_L10-28_
- inherits: `FOptionalPinManager`
- L13 _protected member_ `class UAnimGraphNode_Base* BaseNode;`
- L14 _protected member_ `TArray<UEdGraphPin*>* OldPins;`
- L16 _protected member_ `TMap<FName, UEdGraphPin*> OldPinMap;`
- L19 _public prototype_ `FAnimBlueprintNodeOptionalPinManager(class UAnimGraphNode_Base* Node, TArray<UEdGraphPin*>* InOldPins);`
- L22 _public prototype_ `virtual void GetRecordDefaults(FProperty* TestProperty, FOptionalPinFromProperty& Record) const override;` — FOptionalPinManager interface
- L23 _public prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex, FProperty* Property) const override;`
- L24 _public prototype_ `virtual void PostInitNewPin(UEdGraphPin* Pin, FOptionalPinFromProperty& Record, int32 ArrayIndex, FProperty* Property, uint8* PropertyAddress, uint8* DefaultPropertyAddress) const override;`
- L25 _public prototype_ `virtual void PostRemovedOldPin(FOptionalPinFromProperty& Record, int32 ArrayIndex, FProperty* Property, uint8* PropertyAddress, uint8* DefaultPropertyAddress) const override;`
- L27 _public prototype_ `void AllocateDefaultPins(UStruct* SourceStruct, uint8* StructBasePtr, uint8* DefaultsPtr);`

### `Source/Editor/AnimGraph/Private/AnimBlueprintPinInfoDetails.h` (Private)


#### class `FAnimBlueprintFunctionPinInfoDetails`  
`class FAnimBlueprintFunctionPinInfoDetails : public IPropertyTypeCustomization`  
_L12-45_
- inherits: `IPropertyTypeCustomization`
- L15 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;` — IDetailCustomization interface
- L22 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils)`
- L26 _private prototype_ `bool IsNameValid(const FString& InNewName);` — Check to see if this name is valid
- L29 _private prototype_ `FEdGraphPinType GetTargetPinType() const;` — UI handlers
- L30 _private prototype_ `void HandlePinTypeChanged(const FEdGraphPinType& InPinType);`
- L31 _private prototype_ `void HandleTextChanged(const FText& InNewText);`
- L32 _private prototype_ `void HandleTextCommitted(const FText& InNewText, ETextCommit::Type InCommitType);`
- L36 _private member_ `TSharedPtr<IPropertyHandle> NamePropertyHandle;` — Property handles to edit
- L37 _private member_ `TSharedPtr<IPropertyHandle> TypePropertyHandle;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L41 _private member_ `TSharedPtr<SEditableTextBox> NameTextBox;` — Text box for editing names
- L44 _private member_ `TWeakObjectPtr<UAnimGraphNode_LinkedInputPose> WeakOuterNode;` — The node we are editing on

### `Source/Editor/AnimGraph/Private/AnimBlueprintVariableCreationContext.h` (Private)


#### class `FAnimBlueprintVariableCreationContext`  
`class FAnimBlueprintVariableCreationContext : public IAnimBlueprintVariableCreationContext`  
_L9-23_
- inherits: `IAnimBlueprintVariableCreationContext`
- L14 _private function_ `FAnimBlueprintVariableCreationContext(FAnimBlueprintCompilerContext* InCompilerContext) : CompilerContext(InCompilerContext)`
- L19 _private prototype_ `virtual FProperty* CreateVariable(const FName Name, const FEdGraphPinType& Type) override;` — IAnimBlueprintVariableCreationContext interface
- L20 _private prototype_ `virtual FProperty* CreateUniqueVariable(UObject* InForObject, const FEdGraphPinType& Type) override;`
- L22 _private member_ `FAnimBlueprintCompilerContext* CompilerContext;`

### `Source/Editor/AnimGraph/Private/AnimGraphDetails.h` (Private)


#### class `FAnimGraphDetails`  
`class FAnimGraphDetails : public IDetailCustomization`  
_L23-74_
- inherits: `IDetailCustomization`
- desc: Customization for editing animation graphs
- L27 _public prototype_ `static TSharedPtr<IDetailCustomization> MakeInstance(TSharedPtr<IBlueprintEditor> InBlueprintEditor);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L29 _public function_ `FAnimGraphDetails(TSharedPtr<IAnimationBlueprintEditor> InAnimBlueprintEditor, UAnimBlueprint* AnimBlueprint) : AnimBlueprintEditorPtr(InAnimBlueprintEditor) , AnimBlueprintPtr(AnimBlueprint)`
- L35 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L39 _private prototype_ `FReply OnAddNewInputPoseClicked();` — UI handlers
- L40 _private prototype_ `EVisibility OnGetNewInputPoseTextVisibility(TWeakPtr<SWidget> WeakInputsHeaderWidget) const;`
- L41 _private prototype_ `FReply OnRemoveInputPoseClicked(UAnimGraphNode_LinkedInputPose* InLinkedInputPose);`
- L42 _private prototype_ `FText OnGetGroupText() const;`
- L43 _private prototype_ `void OnGroupTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);`
- L44 _private prototype_ `void OnGroupSelectionChanged(TSharedPtr<FText> ProposedSelection, ESelectInfo::Type SelectInfo);`
- L45 _private prototype_ `TSharedRef<ITableRow> MakeGroupViewWidget(TSharedPtr<FText> Item, const TSharedRef< STableViewBase >& OwnerTable);`
- L48 _private prototype_ `bool IsInterface() const;` — Helper function to check if this is the anim graph details for an anim bp interface
- L51 _private prototype_ `void RefreshGroupSource();` — Refresh the displayed groups
- L55 _private member_ `TWeakPtr<IAnimationBlueprintEditor> AnimBlueprintEditorPtr;` — The Blueprint editor we are embedded in
- L58 _private member_ `TWeakObjectPtr<UAnimBlueprint> AnimBlueprintPtr;` — The blueprint we are editing
- L61 _private member_ `UEdGraph* Graph;` — The graph we are editing
- L64 _private member_ `IDetailLayoutBuilder* DetailLayoutBuilder;` — Hold onto the builder so we can refresh the panel
- L67 _private member_ `TWeakPtr<SComboButton> GroupComboButton;` — Cached combo button widget
- L70 _private member_ `TWeakPtr<SListView<TSharedPtr<FText>>> GroupListView;` — Cached list view widget
- L73 _private member_ `TArray<TSharedPtr<FText>> GroupSource;` — A list of all group names to choose from

### `Source/Editor/AnimGraph/Private/AnimGraphNodeBinding_Base.h` (Private)


#### class `UAnimGraphNodeBinding_Base`  
`class UAnimGraphNodeBinding_Base : public UAnimGraphNodeBinding`  
_L9-40_
- reflection: `UCLASS(EditInlineNew, DisplayName = "Default Anim Graph Node Binding")`
- inherits: `UAnimGraphNodeBinding`
- L18 _private prototype_ `virtual UScriptStruct* GetAnimNodeHandlerStruct() const override;` — UAnimGraphNodeBinding interface
- L19 _private prototype_ `virtual void OnInternalPinCreation(UAnimGraphNode_Base* InNode) override;`
- L20 _private prototype_ `virtual void OnReconstructNode(UAnimGraphNode_Base* InNode) override;`
- L21 _private prototype_ `virtual bool HasBinding(FName InBindingName, bool bCheckArrayIndexName) const override;`
- L22 _private prototype_ `virtual void RemoveBindings(FName InBindingName) override;`
- L23 _private prototype_ `virtual void AddPinSearchMetaDataInfo(const UEdGraphPin* InPin, FName InBindingName, TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L24 _private prototype_ `virtual void HandleVariableRenamed(UBlueprint* InBlueprint, UClass* InVariableClass, UEdGraph* InGraph, const FName& InOldVarName, const FName& InNewVarName) override;`
- L25 _private prototype_ `virtual void HandleFunctionRenamed(UBlueprint* InBlueprint, UClass* InFunctionClass, UEdGraph* InGraph, const FName& InOldFuncName, const FName& InNewFuncName) override;`
- L26 _private prototype_ `virtual void ReplaceReferences(UBlueprint* InBlueprint, UBlueprint* InReplacementBlueprint, const FMemberReference& InSource, const FMemberReference& InReplacement) override;`
- L27 _private prototype_ `virtual bool ReferencesVariable(const FName& InVarName, const UStruct* InScope) const override;`
- L28 _private prototype_ `virtual bool ReferencesFunction(const FName& InFunctionName, const UStruct* InScope) const override;`
- L29 _private prototype_ `virtual void UpdateBindingNames(TFunctionRef<FString(const FString& InOldName)> InModifierFunction) override;`
- L30 _private prototype_ `virtual void ProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L32 _private prototype_ `virtual TSharedRef<SWidget> MakePropertyBindingWidget(const UAnimGraphNode_Base::FAnimPropertyBindingWidgetArgs& InArgs) override;`
- L35 _private prototype_ `static void RecalculateBindingType(UAnimGraphNode_Base* InNode, FAnimGraphNodePropertyBinding& InBinding);`
- L39 _private member_ `TMap<FName, FAnimGraphNodePropertyBinding> PropertyBindings;` — `UPROPERTY()` — Map from property name->binding info

### `Source/Editor/AnimGraph/Private/AnimGraphNode_CallFunction.h` (Private)


#### class `UAnimGraphNode_CallFunction`  
`class UAnimGraphNode_CallFunction : public UAnimGraphNode_Base`  
_L16-75_
- reflection: `UCLASS(MinimalAPI, Experimental, meta=(Keywords = "Event"))`
- inherits: `UAnimGraphNode_Base`
- L23 _private member_ `TObjectPtr<UEdGraph> InnerGraph;` — `UPROPERTY()` — Inner graph we maintain to hook into the function call machinery
- L27 _private member_ `TObjectPtr<UK2Node_CallFunction> CallFunctionPrototype;` — `UPROPERTY()` — Inner node we maintain to hook into the function call machinery
- L30 _private member_ `FAnimNode_CallFunction Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L33 _private member_ `FDelegateHandle GraphChangedHandle;` — Delegate handles used to hook into inner graph & function nodes
- L34 _private member_ `FDelegateHandle PinRenamedHandle;`
- L37 _private prototype_ `virtual void PostLoad() override;` — UObject interface
- L40 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L41 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L42 _private prototype_ `virtual FText GetTooltipText() const override;`
- L43 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L44 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& InOldPins) override;`
- L45 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L46 _private prototype_ `virtual void JumpToDefinition() const override;`
- L47 _private prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L50 _private prototype_ `virtual FText GetMenuCategory() const override;` — UK2Node interface
- L51 _private prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L52 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L53 _private prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L56 _private prototype_ `virtual void GetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const override;` — UAnimGraphNode_Base interface
- L57 _private function_ `virtual bool ShouldCreateStructEvalHandlers() const override`
- L58 _private prototype_ `virtual void OnProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L61 _private prototype_ `void AllocateFunctionPins();`
- L64 _private prototype_ `void SetupFromFunction(UFunction* InFunction);` — Sets up node internals
- L65 _private prototype_ `void BindDelegates();`
- L68 _private prototype_ `bool IsFunctionDenied(const UFunction* InFunction) const;` — Checks to see if the passed-in function is disallowed in anim graphs.
- L71 _private prototype_ `bool AreFunctionParamsValid(const UFunction* InFunction) const;` — Validate the function's parameters to check if it can be called in anim graphs
- L74 _private prototype_ `bool ValidateFunction(const UFunction* InFunction, FCompilerResultsLog* InMessageLog = nullptr) const;` — Validates a function. Used for populating menu actions and verifying already-referenced functions

### `Source/Editor/AnimGraph/Private/AnimGraphNode_Sync.h` (Private)


#### class `UAnimGraphNode_Sync`  
`class UAnimGraphNode_Sync : public UAnimGraphNode_Base`  
_L11-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L16 _private member_ `FAnimNode_Sync Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L19 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L22 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UAnimGraphNode_Base interface
- L23 _private prototype_ `virtual FText GetTooltipText() const override;`
- L24 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L25 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L26 _private prototype_ `virtual void BakeDataDuringCompilation(class FCompilerResultsLog& MessageLog) override;`
- L27 _private prototype_ `virtual void GetInputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`

### `Source/Editor/AnimGraph/Private/AnimSequenceTransformProviderFactories.h` (Private)


#### class `UAnimSequenceTransformProviderLayerStackFactory`  
`class UAnimSequenceTransformProviderLayerStackFactory : public UFactory`  
_L9-17_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L14 _public prototype_ `UAnimSequenceTransformProviderLayerStackFactory();`
- L15 _public prototype_ `virtual FText GetDisplayName() const override;`
- L16 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### class `UAnimSequenceTransformProviderSequenceListFactory`  
`class UAnimSequenceTransformProviderSequenceListFactory : public UFactory`  
_L20-28_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L25 _public prototype_ `UAnimSequenceTransformProviderSequenceListFactory();`
- L26 _public prototype_ `virtual FText GetDisplayName() const override;`
- L27 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### class `UAnimSequenceTransformProviderBlendSpaceListFactory`  
`class UAnimSequenceTransformProviderBlendSpaceListFactory : public UFactory`  
_L31-39_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L36 _public prototype_ `UAnimSequenceTransformProviderBlendSpaceListFactory();`
- L37 _public prototype_ `virtual FText GetDisplayName() const override;`
- L38 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Source/Editor/AnimGraph/Private/AnimSequenceTransformProviderLayerCustomization.h` (Private)


#### class `FAnimSequenceTransformProviderLayerCustomization`  
`class FAnimSequenceTransformProviderLayerCustomization : public IPropertyTypeCustomization`  
_L7-14_
- inherits: `IPropertyTypeCustomization`
- L10 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L12 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& Utils) override;`
- L13 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& Utils) override;`

### `Source/Editor/AnimGraph/Private/CustomPropertyOptionalPinManager.h` (Private)


#### struct `FCustomPropertyOptionalPinManager`  
`struct FCustomPropertyOptionalPinManager : public FOptionalPinManager`  
_L15-30_
- inherits: `FOptionalPinManager`
- L18 _protected member_ `UAnimGraphNode_CustomProperty* CustomPropertyNode;`
- L19 _protected member_ `TArray<UEdGraphPin*>* OldPins;`
- L22 _public prototype_ `FCustomPropertyOptionalPinManager(UAnimGraphNode_CustomProperty* InCustomPropertyNode, TArray<UEdGraphPin*>* InOldPins);`
- L25 _public prototype_ `virtual void GetRecordDefaults(FProperty* TestProperty, FOptionalPinFromProperty& Record) const override;` — FOptionalPinManager interface
- L26 _public prototype_ `virtual bool CanTreatPropertyAsOptional(FProperty* TestProperty) const override;`
- L27 _public prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex, FProperty* Property) const override;`
- L29 _public prototype_ `void CreateCustomPins(UStruct* TargetClass);`

### `Source/Editor/AnimGraph/Private/EditModes/AnimDynamicsEditMode.h` (Private)


#### enum `FAnimDynamicsViewportObjectType`  
`enum class FAnimDynamicsViewportObjectType`  
_L21-21_
- L21 _public enumerator_ `enum class FAnimDynamicsViewportObjectType { PlaneLimit, SphericalLimit, SphericalColisionVolume, BoxExtents }; struct FAnimDynamicsViewportObjectReference { FAnimDynamicsViewportObjectReference(const uint32 InEditorNodeUniqueId, const FAnimDynamicsViewportObjectType InType, const uint32 Index);`
- L21 _public enumerator_ `enum class FAnimDynamicsViewportObjectType { PlaneLimit, SphericalLimit, SphericalColisionVolume, BoxExtents }; struct FAnimDynamicsViewportObjectReference { FAnimDynamicsViewportObjectReference(const uint32 InEditorNodeUniqueId, const FAnimDynamicsViewportObjectType InType, const uint32 Index);`
- L21 _public enumerator_ `enum class FAnimDynamicsViewportObjectType { PlaneLimit, SphericalLimit, SphericalColisionVolume, BoxExtents }; struct FAnimDynamicsViewportObjectReference { FAnimDynamicsViewportObjectReference(const uint32 InEditorNodeUniqueId, const FAnimDynamicsViewportObjectType InType, const uint32 Index);`
- L21 _public enumerator_ `enum class FAnimDynamicsViewportObjectType { PlaneLimit, SphericalLimit, SphericalColisionVolume, BoxExtents }; struct FAnimDynamicsViewportObjectReference { FAnimDynamicsViewportObjectReference(const uint32 InEditorNodeUniqueId, const FAnimDynamicsViewportObjectType InType, const uint32 Index);`

#### struct `FAnimDynamicsViewportObjectReference`  
`struct FAnimDynamicsViewportObjectReference`  
_L26-33_
- desc: FAnimDynamicsViewportObjectReference Used to identify a viewport editable structure (i.e. a physics object joint offset) in an AnimDynamics node.
- L28 _public prototype_ `FAnimDynamicsViewportObjectReference(const uint32 InEditorNodeUniqueId, const FAnimDynamicsViewportObjectType InType, const uint32 Index);`
- L30 _public member_ `uint32 EditorNodeUniqueId;`
- L31 _public member_ `FAnimDynamicsViewportObjectType Type;`
- L32 _public member_ `uint32 Index;`

#### class `FAnimDynamicsEditMode`  
`class FAnimDynamicsEditMode : public FAnimNodeEditMode`  
_L37-79_
- inherits: `FAnimNodeEditMode`
- L40 _public prototype_ `FAnimDynamicsEditMode();`
- L43 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;` — IAnimNodeEditMode interface
- L44 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L45 _public prototype_ `virtual void ExitMode() override;`
- L46 _public prototype_ `virtual ECoordSystem GetWidgetCoordinateSystem() const override;`
- L47 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L48 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L49 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L50 _public prototype_ `virtual UE::Widget::EWidgetMode ChangeToNextWidgetMode(UE::Widget::EWidgetMode InCurWidgetMode) override;`
- L51 _public prototype_ `virtual bool SetWidgetMode(UE::Widget::EWidgetMode InWidgetMode) override;`
- L52 _public prototype_ `virtual FName GetSelectedBone() const override;`
- L53 _public prototype_ `virtual void DoTranslation(FVector& InTranslation) override;`
- L54 _public prototype_ `virtual void DoRotation(FRotator& InRotation) override;`
- L55 _public prototype_ `virtual void DoScale(FVector& InScale) override;`
- L56 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L57 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L60 _private prototype_ `UE::Widget::EWidgetMode FindValidWidgetMode(UE::Widget::EWidgetMode InWidgetMode) const;`
- L61 _private prototype_ `const class UAnimGraphNode_AnimDynamics* const FindSelectedEditorAnimNode(const int32 InEditorNodeId) const;`
- L62 _private prototype_ `class UAnimGraphNode_AnimDynamics* const FindSelectedEditorAnimNode(const int32 InEditorNodeId);`
- L63 _private prototype_ `const bool IsValidWidgetMode(UE::Widget::EWidgetMode InWidgetMode) const;`
- L64 _private prototype_ `UE::Widget::EWidgetMode GetNextWidgetMode(UE::Widget::EWidgetMode InWidgetMode) const;`
- L66 _private prototype_ `const FTransform GetActiveViewportObjectTransform() const;`
- L67 _private prototype_ `const FTransform GetViewportObjectTransform(const FAnimDynamicsViewportObjectReference* const SelectedObjectRef) const;`
- L68 _private prototype_ `const FTransform GetViewportObjectLocalSpaceTransform(const FAnimDynamicsViewportObjectReference* const SelectedObjectRef) const;`
- L69 _private prototype_ `const FAnimDynamicsViewportObjectReference* const GetActiveViewportObject() const;`
- L73 _private member_ `TArray< FAnimDynamicsViewportObjectReference > SelectedViewportObjects;`
- L75 _private member_ `mutable UE::Widget::EWidgetMode CurWidgetMode;`
- L78 _private member_ `bool bIsInteractingWithWidget;` — Set true every frame where DoTranslation fn is called, reset in Tick fn.

#### Free symbols / members of external scopes

- L35 _prototype_ `const bool operator==(const FAnimDynamicsViewportObjectReference& Lhs, const FAnimDynamicsViewportObjectReference& Rhs);`

### `Source/Editor/AnimGraph/Private/EditModes/CCDIKEditMode.h` (Private)


#### class `FCCDIKEditMode`  
`class FCCDIKEditMode : public FAnimNodeEditMode`  
_L13-27_
- inherits: `FAnimNodeEditMode`
- L17 _public prototype_ `virtual void EnterMode(class UAnimGraphNode_Base* InEditorNode, struct FAnimNode_Base* InRuntimeNode) override;` — IAnimNodeEditMode interface
- L18 _public prototype_ `virtual void ExitMode() override;`
- L19 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L20 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L21 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode InWidgetMode) const override;`
- L22 _public prototype_ `virtual void DoTranslation(FVector& InTranslation) override;`
- L23 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L25 _private member_ `struct FAnimNode_CCDIK* RuntimeNode;`
- L26 _private member_ `class UAnimGraphNode_CCDIK* GraphNode;`

### `Source/Editor/AnimGraph/Private/EditModes/ConstraintEditMode.h` (Private)


#### class `FConstraintEditMode`  
`class FConstraintEditMode : public FAnimNodeEditMode`  
_L8-24_
- inherits: `FAnimNodeEditMode`
- L11 _public prototype_ `FConstraintEditMode();`
- L14 _public prototype_ `virtual void EnterMode(class UAnimGraphNode_Base* InEditorNode, struct FAnimNode_Base* InRuntimeNode) override;` — IAnimNodeEditMode interface
- L15 _public prototype_ `virtual void ExitMode() override;`
- L19 _private member_ `struct FAnimNode_Constraint* RuntimeNode;`
- L20 _private member_ `class UAnimGraphNode_Constraint* GraphNode;`
- L23 _private member_ `mutable UE::Widget::EWidgetMode CurWidgetMode;` — storing current widget mode

### `Source/Editor/AnimGraph/Private/EditModes/FabrikEditMode.h` (Private)


#### class `FFabrikEditMode`  
`class FFabrikEditMode : public FAnimNodeEditMode`  
_L9-23_
- inherits: `FAnimNodeEditMode`
- L13 _public prototype_ `virtual void EnterMode(class UAnimGraphNode_Base* InEditorNode, struct FAnimNode_Base* InRuntimeNode) override;` — IAnimNodeEditMode interface
- L14 _public prototype_ `virtual void ExitMode() override;`
- L15 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L16 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L17 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode InWidgetMode) const override;`
- L18 _public prototype_ `virtual void DoTranslation(FVector& InTranslation) override;`
- L21 _private member_ `struct FAnimNode_Fabrik* RuntimeNode;`
- L22 _private member_ `class UAnimGraphNode_Fabrik* GraphNode;`

### `Source/Editor/AnimGraph/Private/EditModes/LookAtEditMode.h` (Private)


#### class `FLookAtEditMode`  
`class FLookAtEditMode : public FAnimNodeEditMode`  
_L10-27_
- inherits: `FAnimNodeEditMode`
- L14 _public prototype_ `virtual void EnterMode(class UAnimGraphNode_Base* InEditorNode, struct FAnimNode_Base* InRuntimeNode) override;` — IAnimNodeEditMode interface
- L15 _public prototype_ `virtual void ExitMode() override;`
- L16 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L17 _public prototype_ `virtual ECoordSystem GetWidgetCoordinateSystem() const override;`
- L18 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L19 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode InWidgetMode) const override;`
- L20 _public prototype_ `virtual FName GetSelectedBone() const override;`
- L21 _public prototype_ `virtual void DoTranslation(FVector& InTranslation) override;`
- L22 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L25 _private member_ `struct FAnimNode_LookAt* RuntimeNode;`
- L26 _private member_ `class UAnimGraphNode_LookAt* GraphNode;`

### `Source/Editor/AnimGraph/Private/EditModes/ModifyBoneEditMode.h` (Private)


#### class `FModifyBoneEditMode`  
`class FModifyBoneEditMode : public FAnimNodeEditMode`  
_L12-44_
- inherits: `FAnimNodeEditMode`
- L15 _public prototype_ `FModifyBoneEditMode();`
- L18 _public prototype_ `virtual void EnterMode(class UAnimGraphNode_Base* InEditorNode, struct FAnimNode_Base* InRuntimeNode) override;` — IAnimNodeEditMode interface
- L19 _public prototype_ `virtual void ExitMode() override;`
- L20 _public prototype_ `virtual ECoordSystem GetWidgetCoordinateSystem() const override;`
- L21 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L22 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L23 _public prototype_ `virtual UE::Widget::EWidgetMode ChangeToNextWidgetMode(UE::Widget::EWidgetMode InCurWidgetMode) override;`
- L24 _public prototype_ `virtual bool SetWidgetMode(UE::Widget::EWidgetMode InWidgetMode) override;`
- L25 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode InWidgetMode) const override;`
- L26 _public prototype_ `virtual FName GetSelectedBone() const override;`
- L27 _public prototype_ `virtual void DoTranslation(FVector& InTranslation) override;`
- L28 _public prototype_ `virtual void DoRotation(FRotator& InRotation) override;`
- L29 _public prototype_ `virtual void DoScale(FVector& InScale) override;`
- L30 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L34 _private prototype_ `UE::Widget::EWidgetMode FindValidWidgetMode(UE::Widget::EWidgetMode InWidgetMode) const;` — methods to find a valid widget mode for gizmo because doesn't need to show gizmo when the mode is "Ignore"
- L35 _private prototype_ `EBoneModificationMode GetBoneModificationMode(UE::Widget::EWidgetMode InWidgetMode) const;`
- L36 _private prototype_ `UE::Widget::EWidgetMode GetNextWidgetMode(UE::Widget::EWidgetMode InWidgetMode) const;`
- L39 _private member_ `struct FAnimNode_ModifyBone* RuntimeNode;`
- L40 _private member_ `class UAnimGraphNode_ModifyBone* GraphNode;`
- L43 _private member_ `mutable UE::Widget::EWidgetMode CurWidgetMode;` — storing current widget mode

### `Source/Editor/AnimGraph/Private/EditModes/ObserveBoneEditMode.h` (Private)


#### class `FObserveBoneEditMode`  
`class FObserveBoneEditMode : public FAnimNodeEditMode`  
_L10-25_
- inherits: `FAnimNodeEditMode`
- L14 _public prototype_ `virtual void EnterMode(class UAnimGraphNode_Base* InEditorNode, struct FAnimNode_Base* InRuntimeNode) override;` — IAnimNodeEditMode interface
- L15 _public prototype_ `virtual void ExitMode() override;`
- L16 _public prototype_ `virtual ECoordSystem GetWidgetCoordinateSystem() const override;`
- L17 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L18 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L19 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode InWidgetMode) const override;`
- L20 _public prototype_ `virtual FName GetSelectedBone() const override;`
- L23 _private member_ `struct FAnimNode_ObserveBone* RuntimeNode;`
- L24 _private member_ `class UAnimGraphNode_ObserveBone* GraphNode;`

### `Source/Editor/AnimGraph/Private/EditModes/PoseDriverEditMode.h` (Private)


#### class `FPoseDriverEditMode`  
`class FPoseDriverEditMode : public FAnimNodeEditMode`  
_L14-28_
- inherits: `FAnimNodeEditMode`
- L18 _public prototype_ `virtual void EnterMode(class UAnimGraphNode_Base* InEditorNode, struct FAnimNode_Base* InRuntimeNode) override;` — IAnimNodeEditMode interface
- L19 _public prototype_ `virtual void ExitMode() override;`
- L22 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;` — FEdMode interface
- L23 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L26 _private member_ `struct FAnimNode_PoseDriver* RuntimeNode;`
- L27 _private member_ `class UAnimGraphNode_PoseDriver* GraphNode;`

### `Source/Editor/AnimGraph/Private/EditModes/SplineIKEditMode.h` (Private)


#### class `FSplineIKEditMode`  
`class FSplineIKEditMode : public FAnimNodeEditMode`  
_L21-61_
- inherits: `FAnimNodeEditMode`
- L24 _public prototype_ `FSplineIKEditMode();`
- L27 _public prototype_ `virtual void EnterMode(class UAnimGraphNode_Base* InEditorNode, struct FAnimNode_Base* InRuntimeNode) override;` — IAnimNodeEditMode interface
- L28 _public prototype_ `virtual void ExitMode() override;`
- L29 _public prototype_ `ECoordSystem GetWidgetCoordinateSystem() const;`
- L30 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L31 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L32 _public prototype_ `virtual UE::Widget::EWidgetMode ChangeToNextWidgetMode(UE::Widget::EWidgetMode CurWidgetMode) override;`
- L33 _public prototype_ `virtual bool SetWidgetMode(UE::Widget::EWidgetMode InWidgetMode) override;`
- L34 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode InWidgetMode) const override;`
- L35 _public prototype_ `virtual FName GetSelectedBone() const override;`
- L36 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L37 _public prototype_ `virtual void DoTranslation(FVector& InTranslation) override;`
- L38 _public prototype_ `virtual void DoRotation(FRotator& InRot) override;`
- L39 _public prototype_ `virtual void DoScale(FVector& InScale) override;`
- L42 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;` — FEdMode interface
- L43 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L47 _private prototype_ `bool IsModeValid(UE::Widget::EWidgetMode InWidgetMode) const;` — Mode helper functions
- L48 _private prototype_ `UE::Widget::EWidgetMode GetNextWidgetMode(UE::Widget::EWidgetMode InWidgetMode) const;`
- L49 _private prototype_ `UE::Widget::EWidgetMode FindValidWidgetMode(UE::Widget::EWidgetMode InWidgetMode) const;`
- L53 _private member_ `FAnimNode_SplineIK* SplineIKRuntimeNode;` — Cache the typed nodes
- L54 _private member_ `UAnimGraphNode_SplineIK* SplineIKGraphNode;`
- L57 _private member_ `int32 SelectedSplinePoint;` — The currently selected spline point
- L60 _private member_ `UE::Widget::EWidgetMode WidgetMode;` — Current widget mode

### `Source/Editor/AnimGraph/Private/EditModes/TwoBoneIKEditMode.h` (Private)


#### class `FTwoBoneIKEditMode`  
`class FTwoBoneIKEditMode : public FAnimNodeEditMode`  
_L22-70_
- inherits: `FAnimNodeEditMode`
- L33 _public prototype_ `FTwoBoneIKEditMode();`
- L36 _public prototype_ `virtual void EnterMode(class UAnimGraphNode_Base* InEditorNode, struct FAnimNode_Base* InRuntimeNode) override;` — IAnimNodeEditMode interface
- L37 _public prototype_ `virtual void ExitMode() override;`
- L38 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L39 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L40 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode InWidgetMode) const override;`
- L41 _public prototype_ `FBoneSocketTarget GetSelectedTarget() const;`
- L42 _public prototype_ `virtual void DoTranslation(FVector& InTranslation) override;`
- L45 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;` — FEdMode interface
- L46 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L47 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L50 _protected prototype_ `void OnExternalNodePropertyChange(FPropertyChangedEvent& InPropertyEvent);`
- L51 _protected member_ `FDelegateHandle NodePropertyDelegateHandle;`
- L55 _private prototype_ `void DrawTargetLocation(FPrimitiveDrawInterface* PDI, BoneSelectModeType InBoneSelectMode, const FColor& TargetColor, const FColor& BoneColor) const;` — Helper function for Render()
- L58 _private prototype_ `FVector GetWidgetLocation(BoneSelectModeType InBoneSelectMode) const;` — Helper funciton for GetWidgetLocation() and joint rendering
- L62 _private member_ `struct FAnimNode_TwoBoneIK* TwoBoneIKRuntimeNode;` — Cache the typed nodes
- L63 _private member_ `UAnimGraphNode_TwoBoneIK* TwoBoneIKGraphNode;`
- L66 _private member_ `BoneSelectModeType BoneSelectMode;` — The current bone selection mode
- L69 _private member_ `EBoneControlSpace PreviousBoneSpace;` — The bone space we last saw for the current node

#### enum `FTwoBoneIKEditMode::BoneSelectModeType`  
`enum BoneSelectModeType`  
_L26-31_
- desc: Bone selection mode
- L28 _public enumerator_ `BSM_EndEffector`
- L29 _public enumerator_ `BSM_JointTarget`
- L30 _public enumerator_ `BSM_Max`

### `Source/Editor/AnimGraph/Private/PoseDriverDetails.h` (Private)


#### struct `FPDD_TargetInfo`  
`struct FPDD_TargetInfo`  
_L47-65_
- desc: Entry in backing list for target list widget
- L49 _public member_ `int32 TargetIndex;`
- L52 _public function_ `static TSharedRef<FPDD_TargetInfo> Make(int32 InTargetIndex)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L58 _public member_ `FSimpleMulticastDelegate ExpandTargetDelegate;` — Executed when we want to expand this target info UI
- L62 _protected function_ `FPDD_TargetInfo(int32 InTargetIndex) : TargetIndex(InTargetIndex)` — Hidden constructor, always use Make above

#### class `SPDD_TargetRow`  
`class SPDD_TargetRow : public SMultiColumnTableRow< TSharedPtr<FPDD_TargetInfo> > , public FCurveOwnerInterface`  
_L72-167_
- inherits: `SMultiColumnTableRow<TSharedPtr<FPDD_TargetInfo>>,FCurveOwnerInterface`
- desc: Widget for displaying info on a paricular target
- L77 _public function_ `SLATE_BEGIN_ARGS(SPDD_TargetRow)`
- L78 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FPDD_TargetInfo>, TargetInfo) SLATE_ARGUMENT(TWeakPtr<FPoseDriverDetails>, PoseDriverDetails) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);`
- L84 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L87 _public prototype_ `FPoseDriverTarget* GetTarget() const;` — Return underlying FPoseDriverTarget this widget represents
- L89 _public prototype_ `UAnimGraphNode_PoseDriver* GetPoseDriverGraphNode() const;` — Get the pose drive node we are editing
- L91 _public prototype_ `bool IsEditingRotation() const;` — If we are editing rotation or translation
- L93 _public prototype_ `void NotifyTargetChanged();` — Call when target is modified, so change is propagated to preview instance
- L95 _public prototype_ `float GetTargetWeight() const;` — Get current weight of this target in preview
- L98 _public prototype_ `int32 GetTargetIndex() const;` — Get index of target this represents on pose driver
- L101 _public prototype_ `bool IsOverrideEnabled() const;` — If we should enable the display of override controls
- L103 _public prototype_ `int32 GetTransRotWidgetIndex() const;`
- L104 _public prototype_ `TOptional<float> GetTranslation(int32 BoneIndex, EAxis::Type Axis) const;`
- L105 _public prototype_ `TOptional<float> GetRotation(int32 BoneIndex, EAxis::Type Axis) const;`
- L106 _public prototype_ `TOptional<float> GetScale() const;`
- L107 _public prototype_ `FText GetTargetTitleText() const;`
- L108 _public prototype_ `FText GetTargetWeightText() const;`
- L109 _public prototype_ `FSlateColor GetWeightBarColor() const;`
- L111 _public prototype_ `void SetTranslation(float NewTrans, int32 BoneIndex, EAxis::Type Axis);`
- L112 _public prototype_ `void SetRotation(float NewRot, int32 BoneIndex, EAxis::Type Axis);`
- L113 _public prototype_ `void SetScale(float NewScale);`
- L114 _public prototype_ `void SetDrivenNameText(const FText& NewText, ETextCommit::Type CommitType);`
- L116 _public prototype_ `void ExpandTargetInfo();`
- L117 _public prototype_ `void OnTargetExpansionChanged(bool bExpanded);`
- L118 _public prototype_ `FText GetDrivenNameText() const;`
- L119 _public prototype_ `void OnDrivenNameChanged(TSharedPtr<FString> NewName, ESelectInfo::Type SelectInfo);`
- L120 _public prototype_ `TSharedRef<SWidget> MakeDrivenNameWidget(TSharedPtr<FString> InItem);`
- L122 _public prototype_ `bool IsCustomCurveEnabled() const;`
- L123 _public prototype_ `void OnApplyCustomCurveChanged(const ECheckBoxState NewCheckState);`
- L125 _public prototype_ `bool IsHidden() const;`
- L126 _public prototype_ `void OnIsHiddenChanged(const ECheckBoxState NewCheckState);`
- L128 _public prototype_ `FText GetDistanceMethodAsText() const;`
- L129 _public prototype_ `void OnDistanceMethodChanged(TSharedPtr<FString> InItem, ESelectInfo::Type SelectionType);`
- L130 _public prototype_ `FText GetFunctionTypeAsText() const;`
- L131 _public prototype_ `void OnFunctionTypeChanged(TSharedPtr<FString> InItem, ESelectInfo::Type SelectionType);`
- L134 _public prototype_ `void RemoveTarget();` — Remove this target from
- L136 _public prototype_ `void SoloTargetStart();`
- L137 _public prototype_ `void SoloTargetEnd();`
- L140 _public prototype_ `bool IsSoloTarget() const;` — Returns true if the target is currently set to solo.
- L144 _public prototype_ `virtual TArray<FRichCurveEditInfoConst> GetCurves() const override;` — `UE_DEPRECATED(5.6, "Use version taking a TAdderReserverRef")` — FCurveOwnerInterface interface
- L145 _public prototype_ `virtual void GetCurves(TAdderReserverRef<FRichCurveEditInfoConst> Curves) const override;`
- L146 _public prototype_ `virtual TArray<FRichCurveEditInfo> GetCurves() override;`
- L147 _public prototype_ `virtual void ModifyOwner() override;`
- L148 _public prototype_ `virtual TArray<const UObject*> GetOwners() const override;`
- L149 _public prototype_ `virtual void MakeTransactional() override;`
- L150 _public prototype_ `virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override;`
- L151 _public prototype_ `virtual bool IsValidCurve(FRichCurveEditInfo CurveInfo) override;`
- L154 _public member_ `TSharedPtr<SExpandableArea> ExpandArea;` — Expandable area used for this widget
- L157 _public member_ `TSharedPtr<SCurveEditor> CurveEditor;` — Curve editor for custom curves
- L160 _public member_ `TWeakPtr<FPoseDriverDetails> PoseDriverDetailsPtr;` — Pointer back to owning customization
- L163 _public member_ `TWeakPtr<FPDD_TargetInfo> TargetInfoPtr;` — Info that this widget represents
- L165 _public member_ `static TArray< TSharedPtr<FString> > DistanceMethodOptions;`
- L166 _public member_ `static TArray< TSharedPtr<FString> > FunctionTypeOptions;`

#### class `FPoseDriverDetails`  
`class FPoseDriverDetails : public IDetailCustomization`  
_L171-236_
- inherits: `IDetailCustomization`
- desc: Details customization for PoseDriver node
- L175 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L178 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L181 _public prototype_ `void ClickedOnCopyFromPoseAsset();`
- L182 _public prototype_ `bool CopyFromPoseAssetIsEnabled() const;`
- L183 _public prototype_ `void ClickedOnAutoScaleFactors();`
- L184 _public prototype_ `bool AutoScaleFactorsIsEnabled() const;`
- L185 _public prototype_ `FReply ClickedAddTarget();`
- L186 _public prototype_ `TSharedRef<ITableRow> GenerateTargetRow(TSharedPtr<FPDD_TargetInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable);`
- L187 _public prototype_ `void OnTargetSelectionChanged(TSharedPtr<FPDD_TargetInfo> InInfo, ESelectInfo::Type SelectInfo);`
- L188 _public prototype_ `void OnPoseAssetChanged();`
- L189 _public prototype_ `void OnSourceBonesChanged();`
- L190 _public prototype_ `void OnSoloDrivenOnlyChanged(const ECheckBoxState NewCheckState);`
- L191 _public prototype_ `void SelectedTargetChanged();`
- L194 _public prototype_ `TSharedRef<SWidget> GetToolsMenuContent();` — Get tools popup menu content
- L195 _public prototype_ `FSlateColor GetToolsForegroundColor() const;`
- L198 _public prototype_ `void RemoveTarget(int32 TargetIndex);` — Remove a target from node
- L203 _public prototype_ `void SetSoloTarget(int32 TargetIndex);` — Set this target to show at 100% and others at 0% until the next compile, unless it is already a solo target, in which case it will get un-soloed and the normal weight computation applies.
- L206 _public prototype_ `int32 GetSoloTarget() const;` — Returns the current solo target index, or INDEX_NONE if no target is set to solo
- L209 _public prototype_ `bool IsSoloDrivenOnly() const;` — Returns true if the solo is for driven poses/curves only.
- L212 _public prototype_ `void SelectTarget(int32 TargetIndex, bool bExpandTarget);` — Set the currently selected Target
- L215 _public prototype_ `UAnimGraphNode_PoseDriver* GetFirstSelectedPoseDriver() const;` — Util to get the first selected PoseDriver node
- L218 _public prototype_ `void UpdateTargetInfosList();` — Refresh list of TargetInfos, mirroring PoseTargets list on node
- L221 _public prototype_ `void UpdateDrivenNameOptions();` — Update list of options for targets to drive (use by combo box)
- L225 _public member_ `TArray< TWeakObjectPtr<UObject> > SelectedObjectsList;` — Cached array of selected objects
- L227 _public member_ `TArray< TSharedPtr<FPDD_TargetInfo> > TargetInfos;` — Array source for target list
- L229 _public member_ `TArray< TSharedPtr<FString> > DrivenNameOptions;` — List of things a target can drive (curves or morphs), used by combo box
- L231 _public member_ `TSharedPtr<SPDD_TargetListType> TargetListWidget;` — Target list widget
- L233 _public member_ `TSharedPtr<IPropertyHandle> NodePropHandle;` — Property handle to node
- L235 _public member_ `TSharedPtr<SComboButton> ToolsButton;` — Pointer to Tools menu button

#### Free symbols / members of external scopes

- L68 _typedef_ `typedef SListView< TSharedPtr<FPDD_TargetInfo> > SPDD_TargetListType;` — Type of target list widget

### `Source/Editor/AnimGraph/Private/PropertyAccessAnimBlueprintBinding.h` (Private)


#### class `FPropertyAccessAnimBlueprintBinding`  
`class FPropertyAccessAnimBlueprintBinding : public IPropertyAccessBlueprintBinding`  
_L10-16_
- inherits: `IPropertyAccessBlueprintBinding`
- L14 _public prototype_ `virtual bool CanBindToContext(const FContext& InContext) const override;` — IPropertyAccessBlueprintBinding interface
- L15 _public prototype_ `virtual TSharedPtr<FExtender> MakeBindingMenuExtender(const FContext& InContext, const FBindingMenuArgs& InArgs) const override;`

### `Source/Editor/AnimGraph/Public/AnimBlueprintExtension.h` (Public)


#### class `UAnimBlueprintExtension`  
`class UAnimBlueprintExtension : public UBlueprintExtension`  
_L25-238_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintExtension`
- desc: Extension that allows per-system data to be held on the anim blueprint, and per-system logic to be executed during compilation
- L32 _public function_ `template<typename ExtensionType> static ExtensionType* RequestExtension(UAnimBlueprint* InAnimBlueprint)` — Request an anim blueprint extension for an anim blueprint. It is illegal to perform this operation once compilation has commenced, use GetExtension instead.
- L38 _public prototype_ `static UAnimBlueprintExtension* RequestExtension(UAnimBlueprint* InAnimBlueprint, TSubclassOf<UAnimBlueprintExtension> InExtensionType);` — Request an anim blueprint extension for an anim blueprint. It is illegal to perform this operation once compilation has commenced, use GetExtension instead.
- L42 _public function_ `template<typename ExtensionType> static ExtensionType* GetExtension(UAnimBlueprint* InAnimBlueprint)` — Get an already-requested extension for an anim blueprint. Will assert if the extension is not found.
- L49 _public function_ `template<typename ExtensionType> static ExtensionType* FindExtension(UAnimBlueprint* InAnimBlueprint)` — Get an already-requested extension for an anim blueprint. @return nullptr if the extension is not found.
- L55 _public prototype_ `static UAnimBlueprintExtension* GetExtension(UAnimBlueprint* InAnimBlueprint, TSubclassOf<UAnimBlueprintExtension> InExtensionType);` — Get an already-requested an anim blueprint extension for an anim blueprint.
- L58 _public prototype_ `static void ForEachExtension(UAnimBlueprint* InAnimBlueprint, TFunctionRef<void(UAnimBlueprintExtension*)> InFunction);` — Iterate over all registered UAnimBlueprintExtensions in an anim BP
- L61 _public prototype_ `static TArray<UAnimBlueprintExtension*> GetExtensions(UAnimBlueprint* InAnimBlueprint);` — Get all subsystems currently present on an anim blueprint
- L64 _public prototype_ `static void RequestExtensionsForNode(UAnimGraphNode_Base* InAnimGraphNode);` — Request all extensions that a node needs
- L67 _public prototype_ `static void RefreshExtensions(UAnimBlueprint* InAnimBlueprint);` — Refresh all extensions according to nodes present in an anim BP
- L70 _public prototype_ `const UScriptStruct* GetInstanceDataType() const;` — Get the structure that will be added to any BP-derived UAnimInstance
- L73 _public prototype_ `const UScriptStruct* GetClassDataType() const;` — Get the structure that will be added to any anim BP class
- L76 _public prototype_ `const FStructProperty* GetInstanceDataProperty() const;` — Get the property of the instance data
- L79 _public prototype_ `const FStructProperty* GetClassDataProperty() const;` — Get the property of the class data
- L83 _public function_ `template<typename ClassDataType> ClassDataType& GetClassData()` — Get the defaults that will be held on the class
- L90 _public function_ `template<typename InstanceDataType> InstanceDataType& GetInstanceData()` — Get the defaults that will be held on the instance
- L97 _protected prototype_ `UAnimBlueprint* GetAnimBlueprint() const;` — Get the anim blueprint that hosts this extension
- L106 _private function_ `virtual void HandleBeginCompilation(IAnimBlueprintCompilerCreationContext& InCreationContext)` — Override point called when a compiler context is created for the anim blueprint @param	InCreationContext	The compiler context for the current compilation
- L114 _private function_ `virtual void HandleStartCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData)` — Override point called when the class starts compiling. The class may be new or recycled. @param	InClass			The class that is being compiled. This could be a newly created class or a recycled class @param	InCompilerContext	The compiler context for the current compilation @param	OutCompiledData	The compiled data that this handler can write to
- L122 _private function_ `virtual void HandlePreProcessAnimationNodes(TArrayView<UAnimGraphNode_Base*> InAnimNodes, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData)` — Override point called before all animation nodes are processed @param	InAnimNodes		The set of anim nodes that should be processed. Note that these nodes have not yet been pruned for connectivity @param	InCompilerContext	The compiler context for the current compilation @param	OutCompiledData	The compiled data that this handler can write to
- L130 _private function_ `virtual void HandlePostProcessAnimationNodes(TArrayView<UAnimGraphNode_Base*> InAnimNodes, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData)` — Override point called after all animation nodes are processed @param	InAnimNodes		The set of anim nodes that were processed. Note that these nodes were not pruned for connectivity (they will be the same set passed to PreProcessAnimationNodes) @param	InCompilerContext	The compiler context for the current compilation @param	OutCompiledData	The compiled data that this handler can write to
- L138 _private function_ `virtual void HandlePostExpansionStep(const UEdGraph* InGraph, IAnimBlueprintPostExpansionStepContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData)` — Override point called post graph expansion @param	InGraph		The graph that was just expanded @param	InCompilerContext	The compiler context for the current compilation @param	OutCompiledData	The compiled data that this handler can write to
- L146 _private function_ `virtual void HandleFinishCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData)` — Override point called when the class has finished compiling @param	InClass			The class that was compiled @param	InCompilerContext	The compiler context for the current compilation @param	OutCompiledData	The compiled data that this handler can write to
- L154 _private function_ `virtual void HandleCopyTermDefaultsToDefaultObject(UObject* InDefaultObject, IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintExtensionCopyTermDefaultsContext& InPerExtensionContext)` — Override point called when data is being copied to the CDO @param	InDefaultObject		The CDO for the just-compiled class @param	InCompilerContext	The compiler context for the current compilation @param	InPerExtensionContext	The extension context for the current compilation
- L162 _private function_ `virtual void HandleCopyTermDefaultsToSparseClassData(IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintExtensionCopyTermDefaultsContext& InPerExtensionContext)` — Override point called when data is being copied to the sparse class data @param	InDefaultObject		The CDO for the just-compiled class @param	InCompilerContext	The compiler context for the current compilation @param	InPerExtensionContext	The extension context for the current compilation
- L165 _private function_ `virtual void HandleEndCompilation()` — Override point called when a compiler context is destroyed for the anim blueprint. Can be used to clean up resources.
- L172 _private prototype_ `void BeginCompilation(IAnimBlueprintCompilerCreationContext& InCreationContext);` — Called when a compiler context is created for the anim blueprint @param	InCreationContext	The compiler context for the current compilation
- L180 _private prototype_ `void StartCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Called when the class starts compiling. The class may be new or recycled. @param	InClass			The class that is being compiled. This could be a newly created class or a recycled class @param	InCompilerContext	The compiler context for the current compilation @param	OutCompiledData	The compiled data that this handler can write to
- L188 _private prototype_ `void PreProcessAnimationNodes(TArrayView<UAnimGraphNode_Base*> InAnimNodes, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Called before all animation nodes are processed @param	InAnimNodes		The set of anim nodes that should be processed. Note that these nodes have not yet been pruned for connectivity @param	InCompilerContext	The compiler context for the current compilation @param	OutCompiledData	The compiled data that this handler can write to
- L196 _private prototype_ `void PostProcessAnimationNodes(TArrayView<UAnimGraphNode_Base*> InAnimNodes, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Called after all animation nodes are processed @param	InAnimNodes		The set of anim nodes that were processed. Note that these nodes were not pruned for connectivity (they will be the same set passed to PreProcessAnimationNodes) @param	InCompilerContext	The compiler context for the current compilation @param	OutCompiledData	The compiled data that this handler can write to
- L204 _private prototype_ `void PostExpansionStep(const UEdGraph* InGraph, IAnimBlueprintPostExpansionStepContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Called post graph expansion @param	InGraph		The graph that was just expanded @param	InCompilerContext	The compiler context for the current compilation @param	OutCompiledData	The compiled data that this handler can write to
- L212 _private prototype_ `void FinishCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Called when the class has finished compiling @param	InClass			The class that was compiled @param	InCompilerContext	The compiler context for the current compilation @param	OutCompiledData	The compiled data that this handler can write to
- L220 _private prototype_ `void CopyTermDefaultsToDefaultObject(UObject* InDefaultObject, IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintExtensionCopyTermDefaultsContext& InPerExtensionContext);` — Called when data is being copied to the CDO @param	InDefaultObject		The CDO for the just-compiled class @param	InCompilerContext	The compiler context for the current compilation @param	InPerExtensionContext	The extension context for the current compilation
- L228 _private prototype_ `void CopyTermDefaultsToSparseClassData(IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintExtensionCopyTermDefaultsContext& InPerExtensionContext);` — Called when data is being copied to the sparse class data @param	InDefaultObject		The CDO for the just-compiled class @param	InCompilerContext	The compiler context for the current compilation @param	InPerExtensionContext	The extension context for the current compilation
- L231 _private prototype_ `void EndCompilation();` — Called when a compiler context is destroyed for the anim blueprint. Can be used to clean up resources.
- L234 _private prototype_ `void* GetClassDataInternal();` — Get the defaults that will be held on the class
- L237 _private prototype_ `void* GetInstanceDataInternal();` — Get the defaults that will be held on the instance

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimBlueprintExtension_PropertyAccess.h` (Public)


#### class `UAnimBlueprintExtension_PropertyAccess`  
`class UAnimBlueprintExtension_PropertyAccess : public UAnimBlueprintExtension`  
_L40-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimBlueprintExtension`
- L48 _public member_ `static const FName ContextId_Automatic;` — Try to determine the context in which this property access can safely be performed.
- L51 _public member_ `static const FName ContextId_UnBatched_ThreadSafe;` — Can safely be executed on worker threads
- L54 _public member_ `static const FName ContextId_Batched_WorkerThreadPreEventGraph;` — Executed batched on the game thread before the event graph is run
- L57 _public member_ `static const FName ContextId_Batched_WorkerThreadPostEventGraph;` — Executed batched on the game thread after the event graph is run
- L60 _public member_ `static const FName ContextId_Batched_GameThreadPreEventGraph;` — Executed batched on the game thread before the event graph is run
- L63 _public member_ `static const FName ContextId_Batched_GameThreadPostEventGraph;` — Executed batched on the game thread after the event graph is run
- L68 _public prototype_ `FPropertyAccessHandle AddCopy(TArrayView<FString> InSourcePath, TArrayView<FString> InDestPath, const FName& InContextId, UObject* InObject = nullptr);` — Add a copy to the property access library we are compiling @return an integer handle to the pending copy. This can be resolved to a true copy index by calling GetCompiledHandle
- L72 _public prototype_ `FPropertyAccessHandle AddAccess(TArrayView<FString> InPath, UObject* InObject = nullptr);` — Add an access to the property access library we are compiling @return an integer handle to the pending access. This can be resolved to a true access index by calling GetCompiledHandle
- L75 _public function_ `FSimpleMulticastDelegate& OnPreLibraryCompiled()` — Delegate called when the library is compiled (whether successfully or not)
- L78 _public function_ `FOnPostLibraryCompiled& OnPostLibraryCompiled()` — Delegate called when the library is compiled (whether successfully or not)
- L81 _public prototype_ `FCompiledPropertyAccessHandle GetCompiledHandle(FPropertyAccessHandle InHandle) const;` — Maps the initial copy handle to a true handle, post compilation
- L84 _public prototype_ `EPropertyAccessCopyType GetCompiledHandleAccessType(FPropertyAccessHandle InHandle) const;` — Get the access type for the specified handle
- L87 _public prototype_ `void ExpandPropertyAccess(FKismetCompilerContext& InCompilerContext, TArrayView<FString> InSourcePath, UEdGraph* InParentGraph, UEdGraphPin* InTargetPin) const;` — Expands a property access path to a pure chain of BP nodes
- L90 _public prototype_ `static FText GetCompiledHandleContext(FCompiledPropertyAccessHandle InHandle);` — Maps a compiled handle back to a human-readable context
- L93 _public prototype_ `static FText GetCompiledHandleContextDesc(FCompiledPropertyAccessHandle InHandle);` — Maps a compiled handle back to a human-readable context description
- L96 _public prototype_ `static bool ContextRequiresCachedVariable(FName InName);` — Whether a context name requires an auto-generated variable to be cached for an access
- L100 _private prototype_ `virtual void HandleStartCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;` — UAnimBlueprintExtension interface
- L101 _private prototype_ `virtual void HandleFinishCompilingClass(const UClass* InClass, IAnimBlueprintCompilationBracketContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L105 _private member_ `TUniquePtr<IPropertyAccessLibraryCompiler> PropertyAccessLibraryCompiler;` — Property access library compiler
- L108 _private member_ `FSimpleMulticastDelegate OnPreLibraryCompiledDelegate;` — Delegate called before the library is compiled
- L111 _private member_ `FOnPostLibraryCompiled OnPostLibraryCompiledDelegate;` — Delegate called when the library is compiled (whether successfully or not)
- L114 _private member_ `FAnimSubsystem_PropertyAccess Subsystem;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API ANIMGRAPH_API`
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPostLibraryCompiled, IAnimBlueprintCompilationBracketContext& , IAnimBlueprintGeneratedClassCompiledData& ) UCLASS(MinimalAPI) class UAnimBlueprintExtension_PropertyAccess : public UAnimBlueprintExtension { GENERATED_BODY() friend class UAnimBlueprintExtension_Base; public:` — Delegate called when the library is compiled (whether successfully or not)

### `Source/Editor/AnimGraph/Public/AnimBlueprintPostCompileValidation.h` (Public)


#### struct `FAnimBPCompileValidationParams`  
`struct FAnimBPCompileValidationParams`  
_L18-37_
- desc: Encapsulated Parameters, to upgrade these without changing function signature.
- L20 _public member_ `const class UAnimInstance* const DefaultAnimInstance;`
- L21 _public member_ `const class UAnimBlueprintGeneratedClass* const NewAnimBlueprintClass;`
- L22 _public member_ `FCompilerResultsLog& MessageLog;`
- L23 _public member_ `const TMap<FProperty*, class UAnimGraphNode_Base*>& AllocatedNodePropertiesToNodes;`
- L25 _public function_ `FAnimBPCompileValidationParams ( const class UAnimInstance* const InDefaultAnimInstance, const class UAnimBlueprintGeneratedClass* const InNewAnimBlueprintClass, FCompilerResultsLog& InMessageLog, const TMap<FProperty*, class UAnimGraphNode_Base*>& InAllocatedNodePropertiesToNodes ) : DefaultAnimInstance(InDefaultAnimInstance) , NewAnimBlueprintClass(InNewAnimBlueprintClass) , MessageLog(InMessageLog) , AllocatedNodePropertiesToNodes(InAllocatedNodePropertiesToNodes)`

#### class `UAnimBlueprintPostCompileValidation`  
`class UAnimBlueprintPostCompileValidation : public UObject`  
_L41-129_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: This class is a base class for performing AnimBlueprint Post Compilation Validation.
- L46 _public prototype_ `virtual void DoPostCompileValidation(FAnimBPCompileValidationParams& InParams) const;`
- L49 _protected prototype_ `static void PCV_PreloadObject(const UObject* const ReferencedObject);`
- L51 _protected prototype_ `static void PCV_GatherAnimSequences(TArray<const UAnimSequence*>& OutAnimSequences, const UAnimSequenceBase* const InAnimSequenceBase);`
- L52 _protected prototype_ `static void PCV_GatherAnimSequences(TArray<const UAnimSequence*>& OutAnimSequences, const class UBlendSpace* const InBlendSpace);`
- L89 _protected prototype_ `static void PCV_GatherAnimSequencesFromGraph(TArray<const UAnimSequence*>& OutAnimSequences, FAnimBPCompileValidationParams& PCV_Params, const FPCV_GatherParams& GatherParams);`
- L90 _protected prototype_ `static void PCV_GatherBlendSpacesFromGraph(TArray<const class UBlendSpace*>& OutBlendSpaces, FAnimBPCompileValidationParams& PCV_Params);`
- L122 _protected prototype_ `static void PCV_GatherAllReferencedAnimSequences(TArray<FPCV_ReferencedAnimSequence>& OutRefAnimSequences, FAnimBPCompileValidationParams& PCV_Params);`
- L123 _protected prototype_ `static void PCV_GatherAnimSequencesFromStruct(TArray<FPCV_ReferencedAnimSequence>& OutRefAnimSequences, FAnimBPCompileValidationParams& PCV_Params, const UStruct* InStruct, const void* InData, TArray<FPCV_PropertyAndValue> InPropertyCallChain);`
- L124 _protected prototype_ `static void PCV_GatherAnimSequencesFromProperty(TArray<FPCV_ReferencedAnimSequence>& OutRefAnimSequences, FAnimBPCompileValidationParams& PCV_Params, const FProperty* InProperty, const void* InData, TArray<FPCV_PropertyAndValue> InPropertyCallChain);`
- L127 _private function_ `virtual bool NeedsLoadForClient() const override`
- L128 _private function_ `virtual bool NeedsLoadForServer() const override`

#### struct `UAnimBlueprintPostCompileValidation::FPCV_GatherParams`  
`struct FPCV_GatherParams`  
_L54-87_
- L56 _public member_ `bool bFilterBySyncGroup;`
- L57 _public member_ `FName SyncGroupName;`
- L58 _public member_ `bool bFilterByLoopingCondition;`
- L59 _public member_ `bool bLoopingCondition;`
- L62 _public function_ `FPCV_GatherParams ( bool InbFilterBySyncGroup = false, int32 InSyncGroupIndex = INDEX_NONE, bool InbFilterByLoopingCondition = false, bool InbLoopingCondition = false ) : bFilterBySyncGroup(InbFilterBySyncGroup) , SyncGroupName(NAME_None) , bFilterByLoopingCondition(InbFilterByLoopingCondition) , bLoopingCondition(InbLoopingCondition)` — `UE_DEPRECATED(4.26, "Please use the constructor that takes an FName for the sync group")`
- L75 _public function_ `FPCV_GatherParams ( bool InbFilterBySyncGroup = false, FName InSyncGroupName = NAME_None, bool InbFilterByLoopingCondition = false, bool InbLoopingCondition = false ) : bFilterBySyncGroup(InbFilterBySyncGroup) , SyncGroupName(InSyncGroupName) , bFilterByLoopingCondition(InbFilterByLoopingCondition) , bLoopingCondition(InbLoopingCondition)`

#### struct `UAnimBlueprintPostCompileValidation::FPCV_ReferencedAnimSequence`  
`struct FPCV_ReferencedAnimSequence`  
_L92-105_
- L94 _public member_ `const UAnimSequence* AnimSequence;`
- L95 _public member_ `const UObject* Referencer;`
- L97 _public function_ `FPCV_ReferencedAnimSequence ( const UAnimSequence* InAnimSequence, const UObject* InReferencer ) : AnimSequence(InAnimSequence) , Referencer(InReferencer)`

#### struct `UAnimBlueprintPostCompileValidation::FPCV_PropertyAndValue`  
`struct FPCV_PropertyAndValue`  
_L107-120_
- L109 _public member_ `const FProperty* Property;`
- L110 _public member_ `const void* Value;`
- L112 _public function_ `FPCV_PropertyAndValue ( const FProperty* InProperty, const void* InValue ) : Property(InProperty) , Value(InValue)`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphAttributes.h` (Public)


#### enum `EAnimGraphAttributesDisplayMode`  
`enum class EAnimGraphAttributesDisplayMode`  
_L24-34_
- reflection: `UENUM()`
- L27 _public enumerator_ `HideOnPins` — Always hide on pins
- L30 _public enumerator_ `ShowOnPins` — Always show on pins
- L33 _public enumerator_ `Automatic` — Automatically calculate visibility based on graph connectivity/usage

#### enum `EAnimGraphAttributeBlend`  
`enum class EAnimGraphAttributeBlend`  
_L37-44_
- reflection: `UENUM()`
- L40 _public enumerator_ `Blendable` — Attribute is subject to weighted blends as it flows through the graph
- L43 _public enumerator_ `NonBlendable` — Attribute is not blended. Corresponds to messaging between two nodes that are not necessarily directly connected.

#### struct `FAnimGraphAttributeDesc`  
`struct FAnimGraphAttributeDesc`  
_L48-92_
- reflection: `USTRUCT()`
- desc: Description of an attribute
- L52 _public prototype_ `FAnimGraphAttributeDesc() = default;`
- L54 _public function_ `FAnimGraphAttributeDesc(FName InName, EAnimGraphAttributeBlend InBlend, FSlateBrush InIcon = FSlateBrush(), FText InDisplayName = FText(), FText InToolTipText = FText(), FSlateColor InColor = FSlateColor::UseSubduedForeground(), EAnimGraphAttributesDisplayMode InDisplayMode = EAnimGraphAttributesDisplayMode::Automatic, int32 InSortOrder = INDEX_NONE) : Name(InName) , Icon(InIcon) , DisplayName(InDisplayName.IsEmpty() ? FText::FromName(InName) : InDisplayName) , ToolTipText(InToolTipText.IsEmpty() ? FText::FromName(InName) : InToolTipText) , Color(InColor) , DisplayMode(InDisplayMode) , Blend(InBlend) , SortOrder(InSortOrder)`
- L67 _public member_ `FName Name;` — `UPROPERTY(config)`
- L70 _public member_ `FSlateBrush Icon;` — `UPROPERTY(config)`
- L73 _public member_ `FText DisplayName;` — `UPROPERTY(config)`
- L76 _public member_ `FText ToolTipText;` — `UPROPERTY(config)`
- L79 _public member_ `FSlateColor Color;` — `UPROPERTY(config)`
- L83 _public member_ `EAnimGraphAttributesDisplayMode DisplayMode = EAnimGraphAttributesDisplayMode::Automatic;` — `UPROPERTY(config)` — How the attribute is displayed in the graph. This overrides any settings per node type.
- L87 _public member_ `EAnimGraphAttributeBlend Blend = EAnimGraphAttributeBlend::Blendable;` — `UPROPERTY(config)` — Blendability of the attribute
- L91 _public member_ `int32 SortOrder = INDEX_NONE;` — `UPROPERTY(config)` — How to sort the attribute

#### class `UAnimGraphAttributes`  
`class UAnimGraphAttributes : public UObject`  
_L95-123_
- reflection: `UCLASS(MinimalAPI, Config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L101 _public prototype_ `void Register(const FAnimGraphAttributeDesc& InDesc);` — Register an anim graph attribute
- L106 _public prototype_ `const FAnimGraphAttributeDesc* FindAttributeDesc(FName InName) const;` — Get a previously registered attribute desc @param	InName	The name of a previously registered attribute @return nullptr if no desc is registered with the specified name
- L110 _public prototype_ `void ForEachAttribute(TFunctionRef<void(const FAnimGraphAttributeDesc&)> InFunction) const;` — Iterate over all attributes that are registered @param	InFunction	FUnction receiving the various attribute descriptors
- L114 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L119 _private member_ `TArray<FAnimGraphAttributeDesc> Attributes;` — `UPROPERTY(config)` — All attributes
- L122 _private member_ `TMap<FName, int32> AttributesMap;` — Cached attribute index map for faster lookup

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphCommands.h` (Public)


#### class `FAnimGraphCommands`  
`class FAnimGraphCommands : public TCommands<FAnimGraphCommands>`  
_L19-72_
- inherits: `TCommands<FAnimGraphCommands>`
- desc: Anim Graph Commands
- L22 _public function_ `FAnimGraphCommands() : TCommands<FAnimGraphCommands>(TEXT("AnimGraph"), NSLOCTEXT("Contexts", "AnimGraphCommands", "Anim Graph Commands"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L27 _public prototype_ `virtual void RegisterCommands() override;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> TogglePoseWatch;` — Toggle pose watching for a given node
- L35 _public member_ `TSharedPtr<FUICommandInfo> HideUnboundPropertyPins;` — Hide unbound property pins
- L38 _public member_ `TSharedPtr< FUICommandInfo > SelectBone;` — SkeletalControl specific commands
- L40 _public member_ `TSharedPtr< FUICommandInfo > AddBlendListPin;` — Blend list options
- L41 _public member_ `TSharedPtr< FUICommandInfo > RemoveBlendListPin;`
- L44 _public member_ `TSharedPtr< FUICommandInfo > ConvertToSeqEvaluator;` — options for sequence/evaluator converter
- L45 _public member_ `TSharedPtr< FUICommandInfo > ConvertToSeqPlayer;`
- L48 _public member_ `TSharedPtr< FUICommandInfo > ConvertToBSEvaluator;` — options for blendspace converter
- L49 _public member_ `TSharedPtr< FUICommandInfo > ConvertToBSPlayer;`
- L50 _public member_ `TSharedPtr< FUICommandInfo > ConvertToBSGraph;`
- L53 _public member_ `TSharedPtr< FUICommandInfo > ConvertToAimOffsetLookAt;` — options for aimoffset converter
- L54 _public member_ `TSharedPtr< FUICommandInfo > ConvertToAimOffsetSimple;`
- L55 _public member_ `TSharedPtr< FUICommandInfo > ConvertToAimOffsetGraph;`
- L58 _public member_ `TSharedPtr< FUICommandInfo > ConvertToPoseBlender;` — options for sequence/evaluator converter
- L59 _public member_ `TSharedPtr< FUICommandInfo > ConvertToPoseByName;`
- L62 _public member_ `TSharedPtr< FUICommandInfo > OpenRelatedAsset;` — option for opening the asset related to the graph node
- L65 _public member_ `TSharedPtr< FUICommandInfo > CreateSelfTransition;` — Create an alias for this state adds a transition to it
- L68 _public member_ `TSharedPtr< FUICommandInfo > SetActiveState;` — Set the current state as active
- L71 _public member_ `TSharedPtr< FUICommandInfo > ReverseTransition;` — Reverse the selected transition(s)

### `Source/Editor/AnimGraph/Public/AnimGraphDefinitions.h` (Public)
_(no declarations extracted)_

### `Source/Editor/AnimGraph/Public/AnimGraphNodeAlphaOptions.h` (Public)


#### struct `FAnimGraphNodeAlphaOptions`  
`struct FAnimGraphNodeAlphaOptions`  
_L13-162_
- desc: Helper struct used to handle graph (editor) node alpha options
- L43 _public function_ `template<typename AnimNodeType> static void HandleCustomizePinData(const AnimNodeType& InAnimNode, UEdGraphPin* InPin)` — Called from an UAnimGraphNode_Base-derived classes CustomizePinData to update alpha pins
- L73 _public function_ `template<typename AnimNodeType> static void HandlePostEditChangeProperty(const AnimNodeType& InAnimNode, UAnimGraphNode_Base* InNode, FPropertyChangedEvent& PropertyChangedEvent)` — Called from an UAnimGraphNode_Base-derived classes PostEditChangeProperty to update alpha properties and pins
- L137 _public function_ `template<typename AnimNodeType> static void HandleCustomizeDetails(const AnimNodeType& InAnimNode, TSharedRef<IPropertyHandle> InNodeHandle, IDetailLayoutBuilder& InDetailBuilder)` — Called from an UAnimGraphNode_Base-derived classes CustomizeDetails to update alpha properties and pins

### `Source/Editor/AnimGraph/Public/AnimGraphNodeCustomizationInterface.h` (Public)


#### class `UAnimGraphNodeCustomizationInterface`  
`class UAnimGraphNodeCustomizationInterface : public UInterface`  
_L10-13_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable)`
- inherits: `UInterface`

#### class `IAnimGraphNodeCustomizationInterface`  
`class IAnimGraphNodeCustomizationInterface`  
_L15-29_
- L24 _public prototype_ `FLinearColor GetTitleColor() const;` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "Customization")` — Get the custom color for this node
- L25 _public function_ `virtual FLinearColor GetTitleColor_Implementation() const`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_AimOffsetLookAt.h` (Public)


#### class `UAnimGraphNode_AimOffsetLookAt`  
`class UAnimGraphNode_AimOffsetLookAt : public UAnimGraphNode_BlendSpaceBase`  
_L16-49_
- reflection: `UCLASS(MinimalAPI, hidecategories = Coordinates)`
- inherits: `UAnimGraphNode_BlendSpaceBase`
- L21 _private member_ `FAnimNode_AimOffsetLookAt Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L24 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L25 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L29 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L30 _private function_ `virtual UAnimationAsset* GetAnimationAsset() const override`
- L31 _private prototype_ `virtual void GetAllAnimationSequencesReferred(TArray<UAnimationAsset*>& AnimationAssets) const override;`
- L32 _private prototype_ `virtual void ReplaceReferredAnimations(const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap) override;`
- L33 _private prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L37 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L38 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L39 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L43 _private prototype_ `virtual void SetAnimationAsset(UAnimationAsset* Asset) override;` — UAnimGraphNode_AssetPlayerBase interface
- L48 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/AnimGraph/Public/AnimGraphNode_AnimDynamics.h` (Public)


#### class `UAnimGraphNode_AnimDynamics`  
`class UAnimGraphNode_AnimDynamics : public UAnimGraphNode_SkeletalControlBase`  
_L35-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L41 _public member_ `FAnimNode_AnimDynamics Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L45 _public member_ `bool bPreviewLive;` — `UPROPERTY(EditAnywhere, Category = Preview)` — Preview the live physics object on the mesh
- L49 _public member_ `bool bShowLinearLimits;` — `UPROPERTY(EditAnywhere, Category = Preview)` — Show linear (prismatic) limits in the viewport
- L53 _public member_ `bool bShowAngularLimits;` — `UPROPERTY(EditAnywhere, Category = Preview)` — Show angular limit ranges in the viewport
- L57 _public member_ `bool bShowPlanarLimit;` — `UPROPERTY(EditAnywhere, Category = Preview)` — Show planar limit info (actual plane, plane normal) in the viewport
- L61 _public member_ `bool bShowSphericalLimit;` — `UPROPERTY(EditAnywhere, Category = Preview)` — Show spherical limits in the viewport (preview live only)
- L65 _public member_ `bool bShowCollisionSpheres;` — `UPROPERTY(EditAnywhere, Category = Preview)` — If planar limits are enabled and the collision mode isn't CoM, draw sphere collision sizes
- L67 _public prototype_ `virtual void PostLoad() override;`
- L69 _public prototype_ `static FReply ResetButtonClicked(IDetailLayoutBuilder* DetailLayoutBuilder);`
- L70 _public prototype_ `void ResetSim();`
- L73 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L76 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode_Base
- L77 _public prototype_ `virtual FText GetTooltipText() const override;`
- L78 _public prototype_ `virtual FString GetNodeCategory() const override;`
- L81 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base
- L82 _public prototype_ `virtual FEditorModeID GetEditorMode() const override;`
- L83 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L86 _public prototype_ `virtual void GetOnScreenDebugInfo(TArray<FText>& DebugInfo, FAnimNode_Base* RuntimeAnimNode, USkeletalMeshComponent* PreviewSkelMeshComp) const override;` — UAnimGraphNode_SkeletalControlBase
- L88 _public prototype_ `FAnimNode_AnimDynamics* GetPreviewDynamicsNode() const;`
- L89 _public function_ `bool IsPreviewLiveActive() const`
- L92 _public prototype_ `void OnPhysicsBodyDefCustomizeDetails(TSharedRef<IPropertyHandle> ElementProperty, int32 ElementIndex, IDetailChildrenBuilder& ChildrenBuilder, IDetailLayoutBuilder* DetailLayout);` — UI callbacks for customising the physics bodies array in the details panel.
- L93 _public prototype_ `FText BodyDefinitionUINameString(const uint32 BodyIndex) const;`
- L95 _public prototype_ `void UpdatePreviewDynamicsNode(const int32 PhysicsBodyIndex);`
- L99 _protected prototype_ `virtual FText GetControllerDescription() const override;`
- L101 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L103 _protected prototype_ `void DrawLinearLimits(FPrimitiveDrawInterface* PDI, FTransform ShapeTransform, const FAnimNode_AnimDynamics& NodeToVisualise) const;`
- L104 _protected prototype_ `void DrawAngularLimits(FPrimitiveDrawInterface* PDI, FTransform JointTransform, const FAnimNode_AnimDynamics& NodeToVisualize) const;`
- L107 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override` — UAnimGraphNode_SkeletalControlBase protected interface
- L110 _protected prototype_ `USkeleton* GetSkeleton() const;`
- L114 _private member_ `FNodeTitleTextTable CachedNodeTitles;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace AnimDynamicsNodeConstants`
- L23 _variable_ `const FLinearColor ShapeDrawColor = FLinearColor::White;` (scope `AnimDynamicsNodeConstants`)
- L24 _variable_ `const FLinearColor ActiveBodyDrawColor = FLinearColor::Yellow;` (scope `AnimDynamicsNodeConstants`)
- L25 _variable_ `const FLinearColor LimitLineDrawColor = FLinearColor::Yellow;` (scope `AnimDynamicsNodeConstants`)
- L26 _variable_ `const float LimitPlaneDrawSize = 50.0f;` (scope `AnimDynamicsNodeConstants`)
- L27 _variable_ `const float ShapeLineWidth = 0.2f;` (scope `AnimDynamicsNodeConstants`)
- L28 _variable_ `const float SelectedShapeLineWidth = 0.4f;` (scope `AnimDynamicsNodeConstants`)
- L29 _variable_ `const float BodyLineWidth = 0.2f;` (scope `AnimDynamicsNodeConstants`)
- L30 _variable_ `const float TransformLineWidth = 0.05f;` (scope `AnimDynamicsNodeConstants`)
- L31 _variable_ `const float TransformBasisScale = 10.0f;` (scope `AnimDynamicsNodeConstants`)

### `Source/Editor/AnimGraph/Public/AnimGraphNode_ApplyAdditive.h` (Public)


#### class `UAnimGraphNode_ApplyAdditive`  
`class UAnimGraphNode_ApplyAdditive : public UAnimGraphNode_Base`  
_L12-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_ApplyAdditive Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L20 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L24 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L25 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L31 _private prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;` — UAnimGraphNode_Base interface
- L32 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L33 _private prototype_ `virtual FString GetNodeCategory() const override;`
- L34 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_ApplyLimits.h` (Public)


#### class `UAnimGraphNode_ApplyLimits`  
`class UAnimGraphNode_ApplyLimits : public UAnimGraphNode_SkeletalControlBase`  
_L12-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L17 _private member_ `FAnimNode_ApplyLimits Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L21 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L24 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L30 _protected prototype_ `void DrawAngularLimits(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* SkelMeshComp, const FAnimNode_ApplyLimits& NodeToVisualize) const;`
- L33 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L34 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L35 _protected prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent * PreviewSkelMeshComp) const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_ApplyMeshSpaceAdditive.h` (Public)


#### class `UAnimGraphNode_ApplyMeshSpaceAdditive`  
`class UAnimGraphNode_ApplyMeshSpaceAdditive : public UAnimGraphNode_Base`  
_L12-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_ApplyMeshSpaceAdditive Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L20 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L24 _private prototype_ `FText GetTooltipText() const override;` — UEdGraphNode interface
- L25 _private prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L27 _private prototype_ `void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L31 _private prototype_ `FString GetNodeCategory() const override;` — UAnimGraphNode_Base interface
- L32 _private prototype_ `void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L33 _private prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L34 _private prototype_ `void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_AssetPlayerBase.h` (Public)


#### class `UAnimGraphNode_AssetPlayerBase`  
`class UAnimGraphNode_AssetPlayerBase : public UAnimGraphNode_Base`  
_L22-80_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAnimGraphNode_Base`
- desc: Helper / intermediate for asset player graphical nodes
- L28 _public member_ `FAnimationGroupReference SyncGroup_DEPRECATED;` — `UPROPERTY()` — Deprecated - sync group data is held on the contained FAnimNode_Base
- L31 _public prototype_ `void Serialize(FArchive& Ar) override;` — UObject interface
- L32 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L35 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;` — UEdGraphNode interface
- L36 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L37 _public prototype_ `virtual FText GetTooltipText() const override;`
- L40 _public prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;` — UK2Node interface
- L43 _public prototype_ `virtual void OnProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;` — UAnimGraphNode_Base interface
- L44 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L45 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L46 _public function_ `virtual void SetAnimationAsset(UAnimationAsset* Asset)`
- L49 _public function_ `virtual void CopySettingsFromAnimationAsset(UAnimationAsset* Asset)` — Override this to copy any relevant settings from the animation asset used when creating a node with a drag/drop operation
- L52 _public prototype_ `static void GetMenuActionsHelper( FBlueprintActionDatabaseRegistrar& InActionRegistrar, TSubclassOf<UAnimGraphNode_Base> InNodeClass, const TArray<TSubclassOf<UObject>>& InAssetTypes, const TArray<TSubclassOf<UObject>>& InExcludedAssetTypes, const TFunctionRef<FText(const FAssetData&, UClass*)>& InMenuNameFunction, const TFunctionRef<FText(const FAssetData&, UClass*)>& InMenuTooltipFunction, const TFunction<void(UEdGraphNode*, bool, const FAssetData)>& InSetupNewNodeFromAssetFunction, const TFunction<void(UEdGraphNode*, bool, TSubclassOf<UObject>)>& InSetupNewNodeFromClassFunction = {}, const TFunction<FText(const FAssetData&)>& InMenuCategoryFunction = nullptr);` — Helper function to gather menu actions from specific asset types supported by this node
- L64 _public prototype_ `void ValidateAnimNodeDuringCompilationHelper(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog, UAnimationAsset* InAsset, TSubclassOf<UAnimationAsset> InAssetType, UEdGraphPin* InExposedPin, FName InPropertyName);` — Helper function to validate player nodes
- L67 _public prototype_ `void PreloadRequiredAssetsHelper(UAnimationAsset* InAsset, UEdGraphPin* InExposedPin);` — Helper function to preload required assets (including those referenced on pins)
- L71 _protected prototype_ `FText GetNodeTitleHelper(ENodeTitleType::Type InTitleType, UEdGraphPin* InAssetPin, const FText& InAssetDesc, const TFunction<FText(UAnimationAsset*)> InPostFixFunctionRef = nullptr) const;` — Helper functions to build a title for an asset player node
- L72 _protected prototype_ `FText GetNodeTitleForAsset(ENodeTitleType::Type InTitleType, UAnimationAsset* InAsset, const FText& InAssetDesc, const TFunction<FText(UAnimationAsset*)> InPostFixFunctionRef = nullptr) const;`
- L73 _protected prototype_ `void AddSyncGroupToNodeTitle(ENodeTitleType::Type InTitleType, FText & InOutTitle) const;`
- L76 _protected prototype_ `static void SetupNewNode(UEdGraphNode* InNewNode, bool bInIsTemplateNode, const FAssetData InAssetData);` — Default setup function that can be used with GetMenuActionsHalper
- L79 _protected member_ `FString UnloadedSkeletonName;` — Used for filtering in the Blueprint context menu when the sequence asset this node uses is unloaded

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMGRAPH_API`
- L15 _prototype_ `UClass* GetNodeClassForAsset(const UClass* AssetClass);` — Get the default anim node class for playing a particular asset
- L18 _prototype_ `bool SupportNodeClassForAsset(const UClass* AssetClass, UClass* NodeClass);` — See if a particular anim NodeClass can play a particular anim AssetClass

### `Source/Editor/AnimGraph/Public/AnimGraphNode_Base.h` (Public)


#### struct `FPoseLinkMappingRecord`  
`struct FPoseLinkMappingRecord`  
_L38-110_
- L41 _public function_ `static FPoseLinkMappingRecord MakeFromArrayEntry(UAnimGraphNode_Base* LinkingNode, UAnimGraphNode_Base* LinkedNode, FArrayProperty* ArrayProperty, int32 ArrayIndex)`
- L54 _public function_ `static FPoseLinkMappingRecord MakeFromMember(UAnimGraphNode_Base* LinkingNode, UAnimGraphNode_Base* LinkedNode, FStructProperty* MemberProperty)`
- L67 _public function_ `static FPoseLinkMappingRecord MakeInvalid()`
- L73 _public function_ `bool IsValid() const`
- L78 _public function_ `UAnimGraphNode_Base* GetLinkedNode() const`
- L83 _public function_ `UAnimGraphNode_Base* GetLinkingNode() const`
- L88 _public prototype_ `void PatchLinkIndex(uint8* DestinationPtr, int32 LinkID, int32 SourceLinkID) const;`
- L90 _protected function_ `FPoseLinkMappingRecord() : LinkedNode(nullptr) , LinkingNode(nullptr) , ChildProperty(nullptr) , ChildPropertyIndex(INDEX_NONE)`
- L100 _protected member_ `UAnimGraphNode_Base* LinkedNode;` — Linked node for this pose link, can be nullptr
- L103 _protected member_ `UAnimGraphNode_Base* LinkingNode;` — Linking node for this pose link, can be nullptr
- L106 _protected member_ `FProperty* ChildProperty;` — Will either be an array property containing FPoseLinkBase derived structs, indexed by ChildPropertyIndex, or a FPoseLinkBase derived struct property
- L109 _protected member_ `int32 ChildPropertyIndex;` — Index when ChildProperty is an array

#### enum `EBlueprintUsage`  
`enum class EBlueprintUsage : uint8`  
_L113-118_
- reflection: `UENUM()`
- L115 _public enumerator_ `NoProperties`
- L116 _public enumerator_ `DoesNotUseBlueprint`
- L117 _public enumerator_ `UsesBlueprint`

#### enum `EAnimAssetHandlerType`  
`enum class EAnimAssetHandlerType : uint8`  
_L121-126_
- desc: Enum that indicates level of support of this node for a particular asset class
- L123 _public enumerator_ `PrimaryHandler`
- L124 _public enumerator_ `Supported`
- L125 _public enumerator_ `NotSupported`

#### enum `EAnimGraphNodePropertyBindingType`  
`enum class EAnimGraphNodePropertyBindingType`  
_L130-135_
- reflection: `UENUM()`
- desc: The type of a property binding
- L132 _public enumerator_ `None`
- L133 _public enumerator_ `Property`
- L134 _public enumerator_ `Function`

#### struct `FAnimGraphNodePropertyBinding`  
`struct FAnimGraphNodePropertyBinding`  
_L138-191_
- reflection: `USTRUCT()`
- L142 _public prototype_ `FAnimGraphNodePropertyBinding() = default;`
- L146 _public member_ `FEdGraphPinType PinType;` — `UPROPERTY()` — Pin type
- L150 _public member_ `FEdGraphPinType PromotedPinType;` — `UPROPERTY()` — Source type if the binding is a promotion
- L154 _public member_ `FName PropertyName = NAME_None;` — `UPROPERTY()` — Property binding name
- L157 _public member_ `int32 ArrayIndex = INDEX_NONE;` — `UPROPERTY()`
- L161 _public member_ `FText PathAsText;` — `UPROPERTY()` — The property path as text
- L165 _public member_ `TArray<FString> PropertyPath;` — `UPROPERTY()` — The property path a pin is bound to
- L169 _public member_ `FName ContextId = NAME_None;` — `UPROPERTY()` — The context of the binding
- L172 _public member_ `FText CompiledContext;` — `UPROPERTY()`
- L175 _public member_ `FText CompiledContextDesc;` — `UPROPERTY()`
- L179 _public member_ `EAnimGraphNodePropertyBindingType Type = EAnimGraphNodePropertyBindingType::Property;` — `UPROPERTY()` — Whether the binding is a function or not
- L183 _public member_ `bool bIsBound = false;` — `UPROPERTY()` — Whether the pin is bound or not
- L187 _public member_ `bool bIsPromotion = false;` — `UPROPERTY()` — Whether the pin binding is a promotion (e.g. bool->int)
- L190 _public member_ `bool bOnlyUpdateWhenActive = false;` — `UPROPERTY()`

#### class `UAnimGraphNode_Base`  
`class UAnimGraphNode_Base : public UK2Node`  
_L200-663_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UK2Node`
- desc: This is the base class for any animation graph nodes that generate or consume an animation pose in the animation blend graph. Any concrete implementations will be paired with a runtime graph node derived from FAnimNode_Base
- L205 _private member_ `TArray<FOptionalPinFromProperty> ShowPinForProperties;` — `UPROPERTY(EditAnywhere, Category=PinOptions, EditFixedSize)`
- L209 _private member_ `TMap<FName, FAnimGraphNodePropertyBinding> PropertyBindings_DEPRECATED;` — `UPROPERTY()` — Map from property name->binding info
- L213 _private member_ `TSet<FName> AlwaysDynamicProperties;` — `UPROPERTY()` — Properties marked as always dynamic, so they can be set externally
- L216 _private member_ `EBlueprintUsage BlueprintUsage;` — `UPROPERTY(Transient)`
- L220 _private member_ `FMemberReference InitialUpdateFunction;` — `UPROPERTY(EditAnywhere, Category = Functions, meta=(FunctionReference, AllowFunctionLibraries, PrototypeFunction="/Script/AnimGraphRuntime.AnimExecutionContextLibrary.Prototype_ThreadSafeAnimUpdateCall", DefaultBindingName="OnInitialUpdate"), DisplayName="On Initial Update")` — Function called before the node is updated for the first time
- L224 _private member_ `FMemberReference BecomeRelevantFunction;` — `UPROPERTY(EditAnywhere, Category = Functions, meta=(FunctionReference, AllowFunctionLibraries, PrototypeFunction="/Script/AnimGraphRuntime.AnimExecutionContextLibrary.Prototype_ThreadSafeAnimUpdateCall", DefaultBindingName="OnBecomeRelevant"), DisplayName="On Become Relevant")` — Function called when the node becomes relevant, meaning it goes from having no weight to any weight.
- L228 _private member_ `FMemberReference UpdateFunction;` — `UPROPERTY(EditAnywhere, Category = Functions, meta=(FunctionReference, AllowFunctionLibraries, PrototypeFunction="/Script/AnimGraphRuntime.AnimExecutionContextLibrary.Prototype_ThreadSafeAnimUpdateCall", DefaultBindingName="OnUpdate"), DisplayName="On Update")` — Function called when the node is updated
- L233 _private member_ `TObjectPtr<UAnimGraphNodeBinding> Binding;` — `UPROPERTY(EditAnywhere, Instanced, Category=Bindings)` — Bindings for pins that this node exposes
- L237 _private member_ `FName Tag;` — `UPROPERTY(EditAnywhere, Category = Tag)` — Optional reference tag name. If this is set then this node can be referenced from elsewhere in this animation blueprint using an anim node reference
- L241 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L242 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L243 _public prototype_ `virtual void PostEditUndo() override;`
- L244 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L248 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L249 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L250 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L251 _public prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;`
- L252 _public function_ `virtual bool ShowPaletteIconOnNode() const override`
- L253 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L254 _public prototype_ `virtual FString GetPinMetaData(FName InPinName, FName InKey) override;`
- L255 _public prototype_ `virtual void AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L256 _public prototype_ `virtual void AddPinSearchMetaDataInfo(const UEdGraphPin* Pin, TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L257 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L258 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L259 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L260 _public prototype_ `virtual void PostPasteNode() override;`
- L261 _public prototype_ `virtual void DestroyNode() override;`
- L265 _public prototype_ `virtual void ReconstructNode() override;` — UK2Node interface
- L266 _public function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L267 _public function_ `virtual bool ShouldShowNodeProperties() const override`
- L268 _public function_ `virtual bool CanPlaceBreakpoints() const override`
- L269 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L270 _public prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;`
- L271 _public prototype_ `virtual void GetNodeAttributes(TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes) const override;`
- L272 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L273 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L274 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L277 _public function_ `virtual UObject* GetJumpTargetForDoubleClick() const override` — By default return any animation assets we have
- L278 _public prototype_ `virtual bool CanJumpToDefinition() const override;`
- L279 _public prototype_ `virtual void JumpToDefinition() const override;`
- L280 _public prototype_ `virtual void HandleVariableRenamed(UBlueprint* InBlueprint, UClass* InVariableClass, UEdGraph* InGraph, const FName& InOldVarName, const FName& InNewVarName) override;`
- L281 _public prototype_ `virtual void HandleFunctionRenamed(UBlueprint* InBlueprint, UClass* InFunctionClass, UEdGraph* InGraph, const FName& InOldFuncName, const FName& InNewFuncName) override;`
- L282 _public prototype_ `virtual void ReplaceReferences(UBlueprint* InBlueprint, UBlueprint* InReplacementBlueprint, const FMemberReference& InSource, const FMemberReference& InReplacement) override;`
- L283 _public prototype_ `virtual bool ReferencesVariable(const FName& InVarName, const UStruct* InScope) const override;`
- L284 _public prototype_ `virtual bool ReferencesFunction(const FName& InFunctionName, const UStruct* InScope) const override;`
- L290 _public function_ `virtual bool IsPoseWatchable() const` — Whether or not you can add a pose watch on this node
- L293 _public prototype_ `virtual FString GetNodeCategory() const;` — Gets the menu category this node belongs in
- L296 _public function_ `virtual bool IsSinkNode() const` — Is this node a sink that has no pose outputs?
- L299 _public prototype_ `virtual void CreateOutputPins();` — Create any output pins necessary for this node
- L302 _public function_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const` — customize pin data based on the input
- L305 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog);` — Gives each visual node a chance to do final validation before it's node is harvested for use at runtime
- L308 _public function_ `virtual void ValidateAnimNodePostCompile(FCompilerResultsLog& MessageLog, UAnimBlueprintGeneratedClass* CompiledClass, int32 CompiledNodeIndex)` — Gives each visual node a chance to validate that they are still valid in the context of the compiled class, giving a last shot at error or warning generation after primary compilation is finished
- L311 _public function_ `virtual bool UsingCopyPoseFromMesh() const` — If using CopyPoseFromMesh, the AnimBlueprint Compiler will cache this off for optimizations.
- L314 _public function_ `virtual void BakeDataDuringCompilation(FCompilerResultsLog& MessageLog)` — Gives each visual node a chance to update the node template before it is inserted in the compiled class
- L317 _public prototype_ `virtual void PostProcessPinName(const UEdGraphPin* Pin, FString& DisplayName) const;` — Give the node a chance to change the display name of a pin
- L320 _public function_ `UAnimBlueprint* GetAnimBlueprint() const` — Get the animation blueprint to which this node belongs
- L323 _public function_ `virtual void GetAllAnimationSequencesReferred(TArray<UAnimationAsset*>& AnimAssets) const` — Populate the supplied arrays with the currently reffered to animation assets
- L326 _public function_ `virtual void ReplaceReferredAnimations(const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap)` — Replace references to animations that exist in the supplied maps
- L329 _public prototype_ `void HandleAnimReferenceCollection(UAnimationAsset* AnimAsset, TArray<UAnimationAsset*>& AnimationAssets) const;` — Helper function for GetAllAnimationSequencesReferred
- L333 _public prototype_ `template<class AssetType> void HandleAnimReferenceReplacement(AssetType*& OriginalAsset, const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap);` — Helper function for ReplaceReferredAnimations
- L335 _public prototype_ `template<class AssetType> void HandleAnimReferenceReplacement(TObjectPtr<AssetType>& OriginalAsset, const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap);`
- L344 _public prototype_ `virtual void OnNodeSelected(bool bInIsSelected, class FEditorModeTools& InModeTools, struct FAnimNode_Base* InRuntimeNode);` — Selection notification callback. If a node needs to handle viewport input etc. then it should push an editor mode here. @param	bInIsSelected	Whether we selected or deselected the node @param	InModeTools		The mode tools. Use this to push the editor mode if required. @param	InRuntimeNode	The runtime node to go with this skeletal control. This may be NULL in some cases when bInIsSelected is false.
- L347 _public prototype_ `virtual void OnPoseWatchChanged(const bool IsPoseWatchEnabled, TObjectPtr<class UPoseWatch> InPoseWatch, FEditorModeTools& InModeTools, FAnimNode_Base* InRuntimeNode);` — Pose Watch change notification callback. Should be called every time a pose watch on this node is created or destroyed.
- L353 _public prototype_ `virtual FEditorModeID GetEditorMode() const;` — Override this function to push an editor mode when this node is selected @return the editor mode to use when this node is selected
- L356 _public function_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent * PreviewSkelMeshComp) const` — Draw function for supporting visualization
- L362 _public prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* PreviewSkelMeshComp, const bool bIsSelected, const bool bIsPoseWatchEnabled) const;` — Draw function called on nodes that are selected and / or have a pose watch enabled. Default implementation calls the basic draw function for selected nodes and does nothing for pose watched nodes. Nodes that should render something when a pose watch is enabled but they are not selected should override this function.
- L365 _public function_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas, USkeletalMeshComponent * PreviewSkelMeshComp) const` — Canvas draw function to draw to viewport
- L369 _public function_ `virtual void GetOnScreenDebugInfo(TArray<FText>& DebugInfo, FAnimNode_Base* RuntimeAnimNode, USkeletalMeshComponent* PreviewSkelMeshComp) const` — Function to collect strings from nodes to display in the viewport. Use this rather than DrawCanvas when adding general text to the viewport.
- L372 _public function_ `virtual void CopyPinDefaultsToNodeData(UEdGraphPin* InPin)` — Called after editing a default value to update internal node from pin defaults. This is needed for forwarding code to propagate values to preview.
- L375 _public function_ `virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* InPreviewNode)` — Called to propagate data from the internal node to the preview in Persona.
- L380 _public function_ `virtual bool DoesSupportTimeForTransitionGetter() const` — BEGIN Interface to support transition getter if you return true for DoesSupportExposeTimeForTransitionGetter you should implement all below functions
- L381 _public function_ `virtual UAnimationAsset* GetAnimationAsset() const`
- L382 _public function_ `virtual TSubclassOf<UAnimationAsset> GetAnimationAssetClass() const`
- L383 _public function_ `virtual const TCHAR* GetTimePropertyName() const`
- L384 _public function_ `virtual UScriptStruct* GetTimePropertyStruct() const`
- L388 _public function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)` — can customize details tab
- L391 _public prototype_ `FAnimNode_Base* FindDebugAnimNode(USkeletalMeshComponent * PreviewSkelMeshComp) const;` — Try to find the preview node instance for this anim graph node
- L394 _public function_ `template<typename NodeType> NodeType* GetActiveInstanceNode(UObject* AnimInstanceObject) const`
- L413 _public prototype_ `virtual EAnimAssetHandlerType SupportsAssetClass(const UClass* AssetClass) const;` — Returns whether this node supports the supplied asset class @param	bPrimaryAssetHandler	Is this the 'primary' handler for this asset (the node that should be created when asset is dropped)
- L417 _public prototype_ `DECLARE_EVENT_OneParam(UAnimGraphNode_Base, FOnNodePropertyChangedEvent, FPropertyChangedEvent&);` — Event that observers can bind to so that they are notified about changes made to this node through the property system
- L418 _public function_ `FOnNodePropertyChangedEvent& OnNodePropertyChanged()`
- L421 _public prototype_ `DECLARE_EVENT_TwoParams(UAnimGraphNode_Base, FPinVisibilityChangedEvent, bool , int32 );` — Event that observers can bind to so that they are notified about changes to pin visibility
- L422 _public function_ `FPinVisibilityChangedEvent& OnPinVisibilityChanged()`
- L430 _public prototype_ `bool IsPinExposedAndLinked(const FString& InPinName, const EEdGraphPinDirection Direction = EGPD_MAX) const;` — Helper function to check whether a pin is valid and linked to something else in the graph @param	InPinName		The name of the pin @see UEdGraphNode::FindPin @param	InPinDirection	The direction of the pin we are looking for. If this is EGPD_MAX, all directions are considered @return true if the pin is present and connected
- L438 _public prototype_ `bool IsPinExposedAndBound(const FString& InPinName, const EEdGraphPinDirection InDirection = EGPD_MAX) const;` — Helper function to check whether a pin is valid and bound via property access @param	InPinName		The name of the pin @see UEdGraphNode::FindPin @param	InPinDirection	The direction of the pin we are looking for. If this is EGPD_MAX, all directions are considered @return true if the pin is present and bound
- L446 _public prototype_ `bool IsPinUnlinkedUnboundAndUnset(const FString& InPinName, const EEdGraphPinDirection InDirection) const;` — Helper function to check whether a pin is not linked, not bound via property access and still has its default value @param	InPinName		The name of the pin @see UEdGraphNode::FindPin @param	InPinDirection	The direction of the pin we are looking for. If this is EGPD_MAX, all directions are considered @return true if the pin is unlinked, unbound and still has its default value
- L450 _public prototype_ `DECLARE_EVENT(UAnimGraphNode_Base, FOnNodeTitleChangedEvent);` — Event that is broadcast to inform observers that the node title has changed The default SAnimationGraphNode uses this to invalidate cached node title text
- L451 _public function_ `FOnNodeTitleChangedEvent& OnNodeTitleChangedEvent()`
- L453 _public typedef_ `using FNodeAttributeArray = TArray<FName, TInlineAllocator<4>>;`
- L456 _public function_ `virtual void GetInputLinkAttributes(FNodeAttributeArray& OutAttributes) const` — Get the named attribute types that this node takes (absorbs) as inputs. Other attributes are assumed to 'pass through' this node.
- L459 _public function_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const` — Get the named attribute types that this node provides as outputs. Other attributes are assumed to 'pass through' this node.
- L462 _public function_ `virtual bool ShouldShowAttributesOnPins() const` — @return wether to show graph attribute icons on pins for this node.
- L467 _public function_ `virtual const UAnimGraphNode_Base* GetProxyNodeForAttributes() const` — Some anim graph nodes can act as proxies to outer nodes (e.g. sink nodes in nested graphs). Returning that outer node here allows attribute visualization to be forwarded to the inner node from the outer. @return the proxy for attribute display
- L470 _public prototype_ `void SetPinVisibility(bool bInVisible, int32 InOptionalPinIndex);` — Sets the visibility of the specified pin, reconstructs the node if it changes
- L520 _public prototype_ `static TSharedRef<SWidget> MakePropertyBindingWidget(const FAnimPropertyBindingWidgetArgs& InArgs);` — Make a property binding widget to edit the bindings of the passed-in nodes
- L523 _public prototype_ `FProperty* GetPinProperty(const UEdGraphPin* InPin) const;` — Get the property corresponding to a pin. For array element pins returns the outer array property. Returns null if a property cannot be found.
- L524 _public prototype_ `virtual FProperty* GetPinProperty(FName InPinName) const;`
- L527 _public prototype_ `virtual bool IsPinBindable(const UEdGraphPin* InPin) const;` — Check whether the named pin is bindable
- L530 _public function_ `FName GetTag() const` — Get the tag for this node, if any
- L533 _public prototype_ `void SetTag(FName InTag);` — Set the tag for this node
- L537 _public function_ `FAnimNode_Base* GetDebuggedAnimNode() const` — Get the currently-debugged runtime anim node (in the anim BP debugger that this node is currently being edited in) @return nullptr if the node cannot be found
- L541 _public prototype_ `template< typename TNodeType > TNodeType* GetDebuggedAnimNode() const;` — Get the currently-debugged runtime anim node of a specified type (in the anim BP debugger that this node is currently being edited in) @return nullptr if the node cannot be found
- L546 _public prototype_ `void PostEditRefreshDebuggedComponent();` — Refreshes the debugged component post-edit. This is required to see changes as the component may be either an editor-only component that is not ticking, or in a paused PIE world
- L550 _public prototype_ `virtual void GetBoundFunctionsInfo(TArray<TPair<FName, FName>> & InOutBindingsInfo);` — Gets editor information for all the bound anim node functions (category metadata string, member variable's name) Used by SAnimGraphNode to display all bound functions of an anim node.
- L553 _public prototype_ `static bool IsPotentiallyBoundFunction(const FMemberReference& FunctionReference);` — Check if a specified function reference appears to be valid by inspecting only the validity of the name and guid
- L556 _public prototype_ `virtual bool HasBinding(FName InPropertyName) const;` — Check whether the specified property is bound via PropertyBindings
- L559 _public prototype_ `bool RedirectBinding(FName OldPropertyBindingName, FName NewPropertyBindingName);` — Update the property binding name
- L562 _public function_ `const UAnimGraphNodeBinding* GetBinding() const` — Get the bindings for this node
- L565 _public function_ `UAnimGraphNodeBinding* GetMutableBinding()` — Get the mutable bindings for this node
- L568 _public prototype_ `void RemoveBindings(FName InBindingName);` — Remove any bindings for the specified name
- L571 _public prototype_ `UScriptStruct* GetFNodeType() const;` — Gets the animation FNode type represented by this ed graph node
- L574 _public prototype_ `FStructProperty* GetFNodeProperty() const;` — Gets the animation FNode property represented by this ed graph node
- L577 _public prototype_ `FAnimNode_Base* GetFNode();` — Get the runtime anim node that we template
- L588 _protected function_ `void SetTagInternal(FName InTag)` — Set the tag for this node but without regenerating any BP data for tagging
- L591 _protected function_ `virtual void GetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const` — Get the extension types that this node type holds on the anim blueprint. Some extension types are always requested by the system
- L596 _protected prototype_ `virtual void CreatePinsForPoseLink(FProperty* PoseProperty, int32 ArrayIndex);` — This will be called when a pose link is found, and can be called with PoseProperty being either of: - an array property (ArrayIndex >= 0) - a single pose property (ArrayIndex == INDEX_NONE)
- L599 _protected prototype_ `virtual FPoseLinkMappingRecord GetLinkIDLocation(const UScriptStruct* NodeType, UEdGraphPin* InputLinkPin);`
- L602 _protected prototype_ `virtual void GetPinAssociatedProperty(const UScriptStruct* NodeType, const UEdGraphPin* InputPin, FProperty*& OutProperty, int32& OutIndex) const;` — Get the property (and possibly array index) associated with the supplied pin
- L605 _protected prototype_ `void ProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Process this node's data during compilation
- L608 _protected function_ `virtual void OnProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData)` — Process this node's data during compilation (override point)
- L611 _protected prototype_ `void CopyTermDefaultsToDefaultObject(IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintNodeCopyTermDefaultsContext& InPerNodeContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Copy this node's data during the last phase of compilation where term defaults are copied to the new CDO
- L615 _protected function_ `virtual void OnCopyTermDefaultsToDefaultObject(IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintNodeCopyTermDefaultsContext& InPerNodeContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData)` — Override point for CopyTermDefaultsToDefaultObject Copy this node's data during the last phase of compilation where term defaults are copied to the new CDO
- L618 _protected prototype_ `void OverrideAssets(IAnimBlueprintNodeOverrideAssetsContext& InContext) const;` — Called to override the assets held on a runtime anim node. Implements per-node logic for child anim blueprints.
- L621 _protected function_ `virtual void OnOverrideAssets(IAnimBlueprintNodeOverrideAssetsContext& InContext) const` — Override point for OverrideAssets
- L624 _protected function_ `virtual bool ShouldCreateStructEvalHandlers() const` — Whether this node should create BP evaluation handlers as part of compilation
- L627 _protected prototype_ `void InternalPinCreation(TArray<UEdGraphPin*>* OldPins);` — Allocates or reallocates pins
- L632 _protected function_ `virtual void CreateCustomPins(TArray<UEdGraphPin*>* OldPins)` — Override point to create custom pins @param	OldPins		In the case of reconstruction, the OldPins array contains all the pins that the node had prior, otherwise if the node is being created anew the array ptr will be null
- L640 _protected prototype_ `virtual bool GetPinBindingInfo(FName InPinName, FName& OutBindingName, FProperty*& OutPinProperty, int32& OutOptionalPinIndex) const;` — Get the pin binding info for the supplied pin @param	InPinName	The name of the pin @param	OutBindingName	The name of the binding that this pin represents (for array pins the binding name includes the array index as e.g. Binding_1) @param	OutPinProperty	The property that the binding represents @param	OutOptionalPinIndex	The optional pin index (index into the ShowPinForProperties array) @return false if the pin cannot be bound
- L642 _protected member_ `FOnNodePropertyChangedEvent PropertyChangeEvent;`
- L644 _protected member_ `FOnNodeTitleChangedEvent NodeTitleChangedEvent;`
- L646 _protected member_ `FPinVisibilityChangedEvent PinVisibilityChangedEvent;`
- L649 _protected prototype_ `void RecalculateBindingType(FAnimGraphNodePropertyBinding& InBinding);` — Helper function used to refresh the type of a binding
- L652 _protected prototype_ `UObject* GetObjectBeingDebugged() const;` — @return the current object being debugged from the blueprint for this node. Can be nullptr.
- L655 _protected prototype_ `void ValidateFunctionRef(FName InPropertyName, const FMemberReference& InRef, const FText& InFunctionName, FCompilerResultsLog& MessageLog);` — Helper function used to validate anim node function references
- L658 _protected prototype_ `void EnsureBindingsArePresent();` — Create the bindings subobject if required
- L662 _protected member_ `TArray<FName> OldShownPins;` — Old shown pins. Needs to be a member variable to track pin visibility changes between Pre and PostEditChange
- L666 _function_ `template<class AssetType> void UAnimGraphNode_Base::HandleAnimReferenceReplacement(AssetType*& OriginalAsset, const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap)`
- L678 _function_ `template<class AssetType> void UAnimGraphNode_Base::HandleAnimReferenceReplacement(TObjectPtr<AssetType>& OriginalAsset, const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap)`
- L683 _function_ `template<class TNodeType> TNodeType* UAnimGraphNode_Base::GetDebuggedAnimNode() const`

#### struct `UAnimGraphNode_Base::FAnimPropertyBindingWidgetArgs`  
`struct FAnimPropertyBindingWidgetArgs`  
_L473-517_
- desc: Arguments used to construct a property binding widget
- L475 _public function_ `FAnimPropertyBindingWidgetArgs(const TArray<UAnimGraphNode_Base*>& InNodes, FProperty* InPinProperty, FName InPinName, FName InBindingName, int32 InOptionalPinIndex) : Nodes(InNodes) , PinProperty(InPinProperty) , PinName(InPinName) , BindingName(InBindingName) , OptionalPinIndex(InOptionalPinIndex) , bOnGraphNode(true) , bPropertyIsOnFNode(true)`
- L487 _public member_ `TArray<UAnimGraphNode_Base*> Nodes;` — The nodes to display the binding for
- L490 _public member_ `FProperty* PinProperty = nullptr;` — The pin property for this binding
- L493 _public member_ `FName PinName = NAME_None;` — The name of the pin
- L496 _public member_ `FName BindingName = NAME_None;` — The name of the property we are binding to
- L499 _public member_ `int32 OptionalPinIndex = INDEX_NONE;` — The optional pin index that refers to this pin
- L502 _public member_ `bool bOnGraphNode = true;` — Whether this is for display on a graph node
- L505 _public member_ `bool bPropertyIsOnFNode = true;` — Whether the property is on the FAnimNode_Base of this anim node
- L508 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnGetOptionalPins, UAnimGraphNode_Base* , TArrayView<FOptionalPinFromProperty>& );` — Delegate used to to access property bindings to modify for the specified node
- L509 _public member_ `FOnGetOptionalPins OnGetOptionalPins;`
- L512 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnSetPinVisibility, UAnimGraphNode_Base* , bool , int32 );` — Delegate used to set pin visibility
- L513 _public member_ `FOnSetPinVisibility OnSetPinVisibility;`
- L516 _public member_ `TSharedPtr<FExtender> MenuExtender;` — Menu extender used to add custom entries in the binding menu

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API ANIMGRAPH_API`
- L417 _delegate_ `DECLARE_EVENT_OneParam(UAnimGraphNode_Base, FOnNodePropertyChangedEvent, FPropertyChangedEvent&);` — Event that observers can bind to so that they are notified about changes made to this node through the property system
- L421 _delegate_ `DECLARE_EVENT_TwoParams(UAnimGraphNode_Base, FPinVisibilityChangedEvent, bool , int32 );` — Event that observers can bind to so that they are notified about changes to pin visibility
- L450 _delegate_ `DECLARE_EVENT(UAnimGraphNode_Base, FOnNodeTitleChangedEvent);` — Event that is broadcast to inform observers that the node title has changed The default SAnimationGraphNode uses this to invalidate cached node title text
- L508 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGetOptionalPins, UAnimGraphNode_Base* , TArrayView<FOptionalPinFromProperty>& );` — Delegate used to to access property bindings to modify for the specified node
- L512 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnSetPinVisibility, UAnimGraphNode_Base* , bool , int32 );` — Delegate used to set pin visibility

### `Source/Editor/AnimGraph/Public/AnimGraphNode_BlendBoneByChannel.h` (Public)


#### class `UAnimGraphNode_BlendBoneByChannel`  
`class UAnimGraphNode_BlendBoneByChannel : public UAnimGraphNode_Base`  
_L12-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_BlendBoneByChannel BlendNode;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L20 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L21 _private prototype_ `virtual FText GetTooltipText() const override;`
- L22 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private prototype_ `virtual FString GetNodeCategory() const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_BlendListBase.h` (Public)


#### class `UAnimGraphNode_BlendListBase`  
`class UAnimGraphNode_BlendListBase : public UAnimGraphNode_Base`  
_L13-35_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAnimGraphNode_Base`
- L17 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L20 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L21 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L22 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L26 _private prototype_ `virtual FString GetNodeCategory() const override;` — UAnimGraphNode_Base interface
- L27 _private prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L32 _protected prototype_ `void RemovePinsFromOldPins(TArray<UEdGraphPin*>& OldPins, int32 RemovedArrayIndex);` — removes removed pins and adjusts array indices of remained pins
- L34 _protected member_ `int32 RemovedPinArrayIndex;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_BlendListByBool.h` (Public)


#### class `UAnimGraphNode_BlendListByBool`  
`class UAnimGraphNode_BlendListByBool : public UAnimGraphNode_BlendListBase`  
_L12-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendListBase`
- L17 _private member_ `FAnimNode_BlendListByBool Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L20 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L21 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _private prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;` — UAnimGraphNode_Base interface

### `Source/Editor/AnimGraph/Public/AnimGraphNode_BlendListByEnum.h` (Public)


#### class `UAnimGraphNode_BlendListByEnum`  
`class UAnimGraphNode_BlendListByEnum : public UAnimGraphNode_BlendListBase, public INodeDependingOnEnumInterface`  
_L16-76_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendListBase,INodeDependingOnEnumInterface`
- L21 _private member_ `FAnimNode_BlendListByEnum Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L26 _protected member_ `TObjectPtr<UEnum> BoundEnum;` — `UPROPERTY()` — Name of the enum being switched on
- L29 _protected member_ `TArray<FName> VisibleEnumEntries;` — `UPROPERTY()`
- L32 _public prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L33 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L34 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L35 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L39 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L43 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UAnimGraphNode_Base interface
- L44 _public prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L45 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;`
- L46 _public prototype_ `virtual void BakeDataDuringCompilation(class FCompilerResultsLog& MessageLog) override;`
- L47 _public prototype_ `virtual void PreloadRequiredAssets() override;`
- L48 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L52 _public prototype_ `virtual void RemovePinFromBlendList(UEdGraphPin* Pin);` — @TODO: Generalize this behavior (returning a list of actions/delegates maybe?)
- L55 _public function_ `virtual class UEnum* GetEnum() const override` — INodeDependingOnEnumInterface
- L56 _public prototype_ `virtual void ReloadEnum(class UEnum* InEnum) override;`
- L57 _public function_ `virtual bool ShouldBeReconstructedAfterEnumChanged() const override`
- L61 _protected prototype_ `void ExposeEnumElementAsPin(FName EnumElementName);` — Exposes a pin corresponding to the specified element name
- L64 _protected prototype_ `static void GetPinInformation(const FString& InPinName, int32& Out_PinIndex, bool& Out_bIsPosePin, bool& Out_bIsTimePin);` — Gets information about the specified pin.  If both bIsPosePin and bIsTimePin are false, the index is meaningless
- L67 _private prototype_ `void ClearEnum();`
- L69 _private prototype_ `static void RefreshAvailableEnums();`
- L72 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title
- L75 _private member_ `static TArray<TSharedPtr<FString>> AvailableEnums;` — Shared array that contains all possible enums to select from

### `Source/Editor/AnimGraph/Public/AnimGraphNode_BlendListByInt.h` (Public)


#### class `UAnimGraphNode_BlendListByInt`  
`class UAnimGraphNode_BlendListByInt : public UAnimGraphNode_BlendListBase`  
_L12-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendListBase`
- L17 _private member_ `FAnimNode_BlendListByInt Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L21 _private prototype_ `virtual void AddPinToBlendList();` — Adds a new pose pin @TODO: Generalize this behavior (returning a list of actions/delegates maybe?)
- L22 _private prototype_ `virtual void RemovePinFromBlendList(UEdGraphPin* Pin);`
- L25 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L26 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L27 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L31 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface

### `Source/Editor/AnimGraph/Public/AnimGraphNode_BlendSpaceBase.h` (Public)


#### class `UAnimGraphNode_BlendSpaceBase`  
`class UAnimGraphNode_BlendSpaceBase : public UAnimGraphNode_AssetPlayerBase`  
_L12-36_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UAnimGraphNode_AssetPlayerBase`
- L17 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L18 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L19 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L23 _private prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;` — UAnimGraphNode_Base interface
- L24 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L25 _private prototype_ `virtual void PostProcessPinName(const UEdGraphPin* Pin, FString& DisplayName) const override;`
- L26 _private prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const;`
- L27 _private function_ `virtual TSubclassOf<UAnimationAsset> GetAnimationAssetClass() const`
- L28 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L32 _protected function_ `UBlendSpace* GetBlendSpace() const`
- L35 _protected prototype_ `static bool IsAimOffsetBlendSpace(const UClass* BlendSpaceClass);` — Util to determine is an asset class is an aim offset

### `Source/Editor/AnimGraph/Public/AnimGraphNode_BlendSpaceEvaluator.h` (Public)


#### class `UAnimGraphNode_BlendSpaceEvaluator`  
`class UAnimGraphNode_BlendSpaceEvaluator : public UAnimGraphNode_BlendSpaceBase`  
_L15-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendSpaceBase`
- L20 _private member_ `FAnimNode_BlendSpaceEvaluator Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L23 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L24 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L25 _private prototype_ `virtual FText GetTooltipText() const override;`
- L29 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L30 _private prototype_ `virtual void BakeDataDuringCompilation(class FCompilerResultsLog& MessageLog) override;`
- L32 _private prototype_ `virtual bool DoesSupportTimeForTransitionGetter() const override;` — Interface to support transition getter
- L33 _private prototype_ `virtual UAnimationAsset* GetAnimationAsset() const override;`
- L34 _private prototype_ `virtual const TCHAR* GetTimePropertyName() const override;`
- L35 _private prototype_ `virtual UScriptStruct* GetTimePropertyStruct() const override;`
- L36 _private prototype_ `virtual EAnimAssetHandlerType SupportsAssetClass(const UClass* AssetClass) const override;`
- L37 _private prototype_ `virtual void OnOverrideAssets(IAnimBlueprintNodeOverrideAssetsContext& InContext) const override;`
- L41 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L45 _private prototype_ `virtual void SetAnimationAsset(UAnimationAsset* Asset) override;` — UAnimGraphNode_AssetPlayerBase interface
- L46 _private prototype_ `virtual void CopySettingsFromAnimationAsset(UAnimationAsset* Asset) override;`
- L50 _private prototype_ `FText GetNodeTitleForBlendSpace(ENodeTitleType::Type TitleType, UBlendSpace* InBlendSpace) const;`
- L54 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/AnimGraph/Public/AnimGraphNode_BlendSpaceGraph.h` (Public)


#### class `UAnimGraphNode_BlendSpaceGraph`  
`class UAnimGraphNode_BlendSpaceGraph : public UAnimGraphNode_BlendSpaceGraphBase`  
_L16-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendSpaceGraphBase`
- L22 _private member_ `FAnimNode_BlendSpaceGraph Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L25 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L28 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L31 _private prototype_ `virtual void BakeDataDuringCompilation(FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_BlendSpaceGraphBase.h` (Public)


#### class `UAnimGraphNode_BlendSpaceGraphBase`  
`class UAnimGraphNode_BlendSpaceGraphBase : public UAnimGraphNode_Base`  
_L21-119_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAnimGraphNode_Base`
- L26 _public prototype_ `UAnimGraphNode_BlendSpaceGraphBase();`
- L29 _public function_ `TArrayView<UEdGraph* const> GetGraphs() const` — Access the graphs for each sample
- L32 _public function_ `UBlendSpaceGraph* GetBlendSpaceGraph() const` — Access the 'dummy' blendspace graph
- L35 _public prototype_ `UAnimationBlendSpaceSampleGraph* AddGraph(FName InSampleName, UAnimSequence* InSequence);` — Adds a new graph to the internal array
- L38 _public prototype_ `int32 GetSampleIndex(const UEdGraph* Graph) const;` — Returns the sample index associated with the graph, or -1 if not found
- L41 _public prototype_ `void RemoveGraph(int32 InSampleIndex);` — Removes the graph at the specified index
- L44 _public prototype_ `void ReplaceGraph(int32 InSampleIndex, UAnimSequence* InSequence);` — Replaces the graph at the specified index
- L47 _public prototype_ `void SetupFromAsset(const FAssetData& InAssetData, bool bInIsTemplateNode);` — Setup this node from the specified asset
- L50 _public prototype_ `virtual void PostPlacedNewNode() override;` — UEdGraphNode interface
- L53 _public prototype_ `FName GetSyncGroupName() const;` — @return the sync group name assigned to this node
- L56 _public prototype_ `void SetSyncGroupName(FName InName);` — Set the sync group name assigned to this node
- L60 _protected prototype_ `FString GetBlendSpaceGraphName() const;` — Get the name of the blendspace graph
- L63 _protected prototype_ `FString GetBlendSpaceName() const;` — Get the name of the blendspace
- L66 _protected prototype_ `void SetupFromClass(TSubclassOf<UBlendSpace> InBlendSpaceClass, bool bInIsTemplateNode);` — Setup this node from the specified class
- L70 _protected member_ `TObjectPtr<UBlendSpace> BlendSpace;` — `UPROPERTY()` — Internal blendspace
- L74 _protected member_ `TSubclassOf<UBlendSpace> BlendSpaceClass;` — `UPROPERTY()` — Blendspace class, for template nodes
- L78 _protected member_ `TObjectPtr<UBlendSpaceGraph> BlendSpaceGraph;` — `UPROPERTY()` — Dummy blendspace graph (used for navigation only)
- L82 _protected member_ `TArray<TObjectPtr<UEdGraph>> Graphs;` — `UPROPERTY()` — Linked animation graphs for sample points
- L85 _protected member_ `FString SkeletonName;` — Skeleton name used for filtering unloaded assets
- L89 _protected prototype_ `virtual FText GetMenuCategory() const override;` — UEdGraphNode interface
- L90 _protected prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L91 _protected prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L92 _protected prototype_ `virtual FText GetTooltipText() const override;`
- L93 _protected prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L94 _protected prototype_ `virtual void JumpToDefinition() const override;`
- L95 _protected prototype_ `virtual TArray<UEdGraph*> GetSubGraphs() const override;`
- L96 _protected prototype_ `virtual void DestroyNode() override;`
- L97 _protected prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L98 _protected prototype_ `virtual TSharedPtr<INameValidatorInterface> MakeNameValidator() const override;`
- L99 _protected prototype_ `virtual void PostPasteNode() override;`
- L100 _protected prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L101 _protected prototype_ `virtual void PostProcessPinName(const UEdGraphPin* Pin, FString& DisplayName) const override;`
- L104 _protected prototype_ `virtual void OnProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;` — UAnimGraphNode_Base interface
- L105 _protected prototype_ `virtual void OnCopyTermDefaultsToDefaultObject(IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintNodeCopyTermDefaultsContext& InPerNodeContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L106 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L107 _protected prototype_ `virtual void GetInputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L108 _protected prototype_ `virtual void GetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const override;`
- L111 _protected prototype_ `virtual void PreloadRequiredAssets() override;` — UK2Node interface
- L112 _protected prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L115 _protected prototype_ `UAnimGraphNode_Base* ExpandGraphAndProcessNodes(UEdGraph* SourceGraph, UAnimGraphNode_Base* SourceRootNode, IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);` — Helper function for compilation
- L118 _protected prototype_ `UAnimationBlendSpaceSampleGraph* AddGraphInternal(FName InSampleName, UAnimSequence* InSequence);` — Helper function for AddGraph/ReplaceGraph - builds the new graph but doesn't add it to Graphs array.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_BlendSpacePlayer.h` (Public)


#### class `UAnimGraphNode_BlendSpacePlayer`  
`class UAnimGraphNode_BlendSpacePlayer : public UAnimGraphNode_BlendSpaceBase`  
_L16-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendSpaceBase`
- L21 _private member_ `FAnimNode_BlendSpacePlayer Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L24 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L28 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L29 _private prototype_ `virtual void BakeDataDuringCompilation(class FCompilerResultsLog& MessageLog) override;`
- L30 _private prototype_ `virtual bool DoesSupportTimeForTransitionGetter() const override;`
- L31 _private prototype_ `virtual UAnimationAsset* GetAnimationAsset() const override;`
- L32 _private prototype_ `virtual const TCHAR* GetTimePropertyName() const override;`
- L33 _private prototype_ `virtual UScriptStruct* GetTimePropertyStruct() const override;`
- L34 _private prototype_ `virtual void GetAllAnimationSequencesReferred(TArray<UAnimationAsset*>& AnimationAssets) const override;`
- L35 _private prototype_ `virtual void ReplaceReferredAnimations(const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap) override;`
- L36 _private prototype_ `virtual EAnimAssetHandlerType SupportsAssetClass(const UClass* AssetClass) const override;`
- L37 _private prototype_ `virtual void OnOverrideAssets(IAnimBlueprintNodeOverrideAssetsContext& InContext) const override;`
- L41 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L42 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L43 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L47 _private prototype_ `virtual void SetAnimationAsset(UAnimationAsset* Asset) override;` — UAnimGraphNode_AssetPlayerBase interface
- L48 _private prototype_ `virtual void CopySettingsFromAnimationAsset(UAnimationAsset* Asset) override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_BlendSpaceSampleResult.h` (Public)


#### class `UAnimGraphNode_BlendSpaceSampleResult`  
`class UAnimGraphNode_BlendSpaceSampleResult : public UAnimGraphNode_Base`  
_L12-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_BlendSpaceSampleResult Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L20 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L21 _private prototype_ `virtual FText GetTooltipText() const override;`
- L22 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L23 _private function_ `virtual bool CanUserDeleteNode() const override`
- L24 _private function_ `virtual bool CanDuplicateNode() const override`
- L25 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L26 _private function_ `virtual bool IsNodeRootSet() const override`
- L30 _private function_ `virtual bool IsSinkNode() const override`
- L31 _private prototype_ `virtual void GetInputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L32 _private prototype_ `virtual UAnimGraphNode_Base* GetProxyNodeForAttributes() const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_BoneDrivenController.h` (Public)


#### class `UAnimGraphNode_BoneDrivenController`  
`class UAnimGraphNode_BoneDrivenController : public UAnimGraphNode_SkeletalControlBase`  
_L26-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- desc: This is the 'source version' of a bone driven controller, which maps part of the state from one bone to another (e.g., 2 * source.x -> target.z)
- L31 _private member_ `FAnimNode_BoneDrivenController Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L35 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L39 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L40 _public prototype_ `virtual FText GetTooltipText() const override;`
- L44 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L45 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L49 _public prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* SkelMeshComp) const override;` — UAnimGraphNode_SkeletalControlBase interface
- L55 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase protected interface
- L56 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L60 _protected prototype_ `static EVisibility AreNonCurveMappingValuesVisible(IDetailLayoutBuilder* DetailLayoutBuilder);` — Should non-curve mapping values be shown (multiplier, range)?
- L61 _protected prototype_ `static EVisibility AreRemappingValuesVisible(IDetailLayoutBuilder* DetailLayoutBuilder);`
- L64 _protected prototype_ `static EVisibility AreTargetBonePropertiesVisible(IDetailLayoutBuilder* DetailLayoutBuilder);` — Should destination bone or morph target properties be visible
- L65 _protected prototype_ `static EVisibility AreTargetCurvePropertiesVisible(IDetailLayoutBuilder* DetailLayoutBuilder);`
- L67 _protected prototype_ `static void AddTripletPropertyRow(const FText& Name, const FText& Tooltip, IDetailCategoryBuilder& Category, TSharedRef<IPropertyHandle> PropertyHandle, const FName XPropertyName, const FName YPropertyName, const FName ZPropertyName, TAttribute<EVisibility> VisibilityAttribute);`
- L68 _protected prototype_ `static void AddRangePropertyRow(const FText& Name, const FText& Tooltip, IDetailCategoryBuilder& Category, TSharedRef<IPropertyHandle> PropertyHandle, const FName MinPropertyName, const FName MaxPropertyName, TAttribute<EVisibility> VisibilityAttribute);`
- L69 _protected prototype_ `static FText ComponentTypeToText(EComponentType::Type Component);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_CCDIK.h` (Public)


#### class `UAnimGraphNode_CCDIK`  
`class UAnimGraphNode_CCDIK : public UAnimGraphNode_SkeletalControlBase`  
_L11-40_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- desc: Editor node for CCDIK IK skeletal controller
- L16 _private member_ `FAnimNode_CCDIK Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L20 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L24 _public prototype_ `virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* AnimNode) override;` — UAnimGraphNode_Base interface
- L25 _public prototype_ `virtual FEditorModeID GetEditorMode() const override;`
- L29 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L33 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L34 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L39 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/AnimGraph/Public/AnimGraphNode_ComponentToLocalSpace.h` (Public)


#### class `UAnimGraphNode_ComponentToLocalSpace`  
`class UAnimGraphNode_ComponentToLocalSpace : public UAnimGraphNode_Base`  
_L12-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_ConvertComponentToLocalSpace Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L20 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L21 _private prototype_ `virtual FText GetTooltipText() const override;`
- L22 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L23 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L27 _private prototype_ `virtual void PostProcessPinName(const UEdGraphPin* Pin, FString& DisplayName) const override;` — UAnimGraphNode_Base interface

### `Source/Editor/AnimGraph/Public/AnimGraphNode_Constraint.h` (Public)


#### class `UAnimGraphNode_Constraint`  
`class UAnimGraphNode_Constraint : public UAnimGraphNode_SkeletalControlBase`  
_L13-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L18 _private member_ `FAnimNode_Constraint Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L23 _public prototype_ `virtual FText GetTooltipText() const override;`
- L27 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L32 _protected prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L33 _protected prototype_ `virtual void PostProcessPinName(const UEdGraphPin* Pin, FString& DisplayName) const override;`
- L37 _protected prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* SkelMeshComp) const override;` — UAnimGraphNode_SkeletalControlBase interface
- L38 _protected prototype_ `virtual FText GetControllerDescription() const override;`
- L39 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L44 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_CopyBone.h` (Public)


#### class `UAnimGraphNode_CopyBone`  
`class UAnimGraphNode_CopyBone : public UAnimGraphNode_SkeletalControlBase`  
_L13-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L18 _private member_ `FAnimNode_CopyBone Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L23 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L29 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L34 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/AnimGraph/Public/AnimGraphNode_CopyBoneDelta.h` (Public)


#### class `UAnimGraphNode_CopyBoneDelta`  
`class UAnimGraphNode_CopyBoneDelta : public UAnimGraphNode_SkeletalControlBase`  
_L12-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L17 _private member_ `FAnimNode_CopyBoneDelta Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L23 _public prototype_ `virtual FText GetTooltipText() const override;`
- L29 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L31 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_CopyPoseFromMesh.h` (Public)


#### class `UAnimGraphNode_CopyPoseFromMesh`  
`class UAnimGraphNode_CopyPoseFromMesh : public UAnimGraphNode_Base`  
_L12-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_CopyPoseFromMesh Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L21 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L22 _public prototype_ `virtual FText GetTooltipText() const override;`
- L23 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L27 _public function_ `virtual bool UsingCopyPoseFromMesh() const override` — UAnimGraphNode_Base interface
- L28 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_CurveSource.h` (Public)


#### class `UAnimGraphNode_CurveSource`  
`class UAnimGraphNode_CurveSource : public UAnimGraphNode_Base`  
_L13-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- desc: Supply curves from some external source (e.g. audio)
- L18 _private member_ `FAnimNode_CurveSource Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L22 _public prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L27 _public prototype_ `virtual FString GetNodeCategory() const override;` — UAnimGraphNode_Base interface
- L28 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_CustomProperty.h` (Public)


#### class `UAnimGraphNode_CustomProperty`  
`class UAnimGraphNode_CustomProperty : public UAnimGraphNode_Base, public IClassVariableCreator`  
_L21-110_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAnimGraphNode_Base,IClassVariableCreator`
- L28 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L29 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L30 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L33 _public prototype_ `virtual void CreateClassVariablesFromBlueprint(IAnimBlueprintVariableCreationContext& InCreationContext) override;` — IClassVariableCreator interface
- L36 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L37 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L38 _public prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput ) const override;`
- L39 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L43 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — UAnimGraphNode_Base interface
- L44 _public prototype_ `virtual void OnProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L45 _public prototype_ `virtual void OnCopyTermDefaultsToDefaultObject(IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintNodeCopyTermDefaultsContext& InPerNodeContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L46 _public prototype_ `virtual void CreateCustomPins(TArray<UEdGraphPin*>* OldPins) override;`
- L47 _public prototype_ `virtual FProperty* GetPinProperty(FName InPinName) const override;`
- L48 _public prototype_ `virtual bool IsPinBindable(const UEdGraphPin* InPin) const override;`
- L49 _public prototype_ `virtual bool GetPinBindingInfo(FName InPinName, FName& OutBindingName, FProperty*& OutPinProperty, int32& OutOptionalPinIndex) const override;`
- L50 _public prototype_ `virtual bool HasBinding(FName InBindingName) const override;`
- L53 _public prototype_ `void GetInstancePinProperty(const IAnimBlueprintCompilationContext& InCompilationContext, UEdGraphPin* InInputPin, FProperty*& OutProperty);` — Gets the property on InOwnerInstanceClass that corresponds to InInputPin
- L55 _public prototype_ `FString GetPinTargetVariableName(const UEdGraphPin* InPin) const;` — Gets the unique name for the property linked to a given pin
- L57 _public prototype_ `FString GetPinTargetVariableName(FName InPinName) const;` — Gets the unique name for the property linked to a given pin name
- L59 _public prototype_ `UClass* GetTargetClass() const;` — Gets Target Class this properties to link
- L60 _public function_ `virtual UStruct* GetTargetStruct() const`
- L62 _public prototype_ `void AddSourceTargetProperties(const FName& InSourcePropertyName, const FName& InTargetPropertyName);` — Add Source and Target Properties - Check FAnimNode_CustomProperty
- L64 _public prototype_ `virtual UClass* GetTargetSkeletonClass() const;` — Helper used to get the skeleton class we are targeting
- L65 _public function_ `virtual UStruct* GetTargetSkeletonStruct() const`
- L69 _public prototype_ `void OnStructuralPropertyChanged(IDetailLayoutBuilder* DetailBuilder);` — ----- UI CALLBACKS ----- // User changed the instance class etc.
- L71 _public prototype_ `void OnInstanceClassChanged(IDetailLayoutBuilder* DetailBuilder);` — User changed the instance class
- L82 _protected member_ `TArray<FName> KnownExposableProperties_DEPRECATED;` — `UPROPERTY()` — List of property names we know to exist on the target class, so we can detect when Properties are added or removed on reconstruction Deprecated, use CustomPinProperties instead.
- L86 _protected member_ `TArray<FName> ExposedPropertyNames_DEPRECATED;` — `UPROPERTY()` — Names of properties the user has chosen to expose. Deprecated, use CustomPinProperties instead.
- L90 _protected member_ `TArray<FOptionalPinFromProperty> CustomPinProperties;` — `UPROPERTY()` — Exposed pin data for custom properties
- L93 _protected prototype_ `FText GetPropertyTypeText(FProperty* Property);` — Gets a property's type as FText (for UI)
- L96 _protected prototype_ `virtual FAnimNode_CustomProperty* GetCustomPropertyNode() PURE_VIRTUAL(UAnimGraphNode_CustomProperty::GetCustomPropertyNode, return nullptr;);` — internal node accessor
- L97 _protected prototype_ `virtual const FAnimNode_CustomProperty* GetCustomPropertyNode() const PURE_VIRTUAL(UAnimGraphNode_CustomProperty::GetCustomPropertyNode, return nullptr;);`
- L100 _protected function_ `virtual bool IsStructuralProperty(FProperty* InProperty) const` — Check whether the specified property is structural (i.e. should we rebuild the UI if it changes)
- L103 _protected function_ `virtual bool NeedsToSpecifyValidTargetClass() const` — Whether this node needs a valid target class up-front
- L106 _protected prototype_ `void SetCustomPinVisibility(bool bInVisible, int32 InOptionalPinIndex);` — Sets the visibility of the specified pin, reconstructs the node if it changes
- L109 _protected prototype_ `FString GetPinTargetVariableNameBase(FName InPinName) const;` — Helper function for GetPinTargetVariableName

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_CustomTransitionResult.h` (Public)


#### class `UAnimGraphNode_CustomTransitionResult`  
`class UAnimGraphNode_CustomTransitionResult : public UAnimGraphNode_StateResult`  
_L11-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_StateResult`
- L16 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L17 _private prototype_ `virtual FText GetTooltipText() const override;`
- L18 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_DeadBlending.h` (Public)


#### class `UAnimGraphNode_DeadBlending`  
`class UAnimGraphNode_DeadBlending : public UAnimGraphNode_Base`  
_L12-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_DeadBlending Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L20 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L23 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L24 _private prototype_ `virtual FText GetTooltipText() const override;`
- L25 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L27 _private prototype_ `virtual void GetInputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L28 _private prototype_ `virtual void OnCopyTermDefaultsToDefaultObject(IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintNodeCopyTermDefaultsContext& InPerNodeContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_Fabrik.h` (Public)


#### class `UAnimGraphNode_Fabrik`  
`class UAnimGraphNode_Fabrik : public UAnimGraphNode_SkeletalControlBase`  
_L16-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- desc: Editor node for FABRIK IK skeletal controller
- L21 _private member_ `FAnimNode_Fabrik Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L25 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L29 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L33 _public prototype_ `virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* AnimNode) override;` — UAnimGraphNode_Base interface
- L34 _public prototype_ `virtual FEditorModeID GetEditorMode() const override;`
- L35 _public prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent * PreviewSkelMeshComp) const override;`
- L40 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L41 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_HandIKRetargeting.h` (Public)


#### class `UAnimGraphNode_HandIKRetargeting`  
`class UAnimGraphNode_HandIKRetargeting : public UAnimGraphNode_SkeletalControlBase`  
_L12-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L17 _private member_ `FAnimNode_HandIKRetargeting Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L21 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L22 _public prototype_ `virtual FText GetTooltipText() const override;`
- L27 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L28 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_IdentityPose.h` (Public)


#### class `UAnimGraphNode_IdentityPose`  
`class UAnimGraphNode_IdentityPose : public UAnimGraphNode_RefPoseBase`  
_L11-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_RefPoseBase`
- L16 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L17 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_Inertialization.h` (Public)


#### class `UAnimGraphNode_Inertialization`  
`class UAnimGraphNode_Inertialization : public UAnimGraphNode_Base`  
_L12-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_Inertialization Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L19 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L20 _private prototype_ `virtual FText GetTooltipText() const override;`
- L21 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L22 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L23 _private prototype_ `virtual void GetInputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L24 _private prototype_ `virtual void OnCopyTermDefaultsToDefaultObject(IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintNodeCopyTermDefaultsContext& InPerNodeContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_LayeredBoneBlend.h` (Public)


#### class `UAnimGraphNode_LayeredBoneBlend`  
`class UAnimGraphNode_LayeredBoneBlend : public UAnimGraphNode_BlendListBase`  
_L12-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendListBase`
- L17 _private member_ `FAnimNode_LayeredBoneBlend Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L21 _private prototype_ `virtual void AddPinToBlendByFilter();` — Adds a new pose pin @TODO: Generalize this behavior (returning a list of actions/delegates maybe?)
- L22 _private prototype_ `virtual void RemovePinFromBlendByFilter(UEdGraphPin* Pin);`
- L25 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L26 _private prototype_ `virtual void PostLoad() override;`
- L30 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L31 _private prototype_ `virtual FText GetTooltipText() const override;`
- L32 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L33 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L37 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L41 _private prototype_ `virtual FString GetNodeCategory() const override;` — UAnimGraphNode_Base interface
- L42 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L43 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L48 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;` — Gives each visual node a chance to validate that they are still valid in the context of the compiled class, giving a last shot at error or warning generation after primary compilation is finished

### `Source/Editor/AnimGraph/Public/AnimGraphNode_LegIK.h` (Public)


#### class `UAnimGraphNode_LegIK`  
`class UAnimGraphNode_LegIK : public UAnimGraphNode_SkeletalControlBase`  
_L13-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L18 _private member_ `FAnimNode_LegIK Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L23 _public prototype_ `virtual FText GetTooltipText() const override;`
- L24 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L32 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L33 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_LinkedAnimGraph.h` (Public)


#### class `UAnimGraphNode_LinkedAnimGraph`  
`class UAnimGraphNode_LinkedAnimGraph : public UAnimGraphNode_LinkedAnimGraphBase, public IK2Node_ExternalGraphInterface`  
_L14-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_LinkedAnimGraphBase,IK2Node_ExternalGraphInterface`
- L21 _public member_ `FAnimNode_LinkedAnimGraph Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L24 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L27 _public prototype_ `virtual void PostPasteNode() override;`
- L30 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L31 _public prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L34 _public prototype_ `virtual FAnimNode_CustomProperty* GetCustomPropertyNode() override;`
- L35 _public prototype_ `virtual const FAnimNode_CustomProperty* GetCustomPropertyNode() const override;`
- L38 _public prototype_ `virtual FAnimNode_LinkedAnimGraph* GetLinkedAnimGraphNode() override;`
- L39 _public prototype_ `virtual const FAnimNode_LinkedAnimGraph* GetLinkedAnimGraphNode() const override;`
- L42 _public prototype_ `virtual TArray<UEdGraph*> GetExternalGraphs() const override;` — IK2Node_ExternalGraphInterface interface
- L46 _private prototype_ `void SetupFromAsset(const FAssetData& InAssetData, bool bInIsTemplateNode);` — Setup the node from a specified anim BP

#### Free symbols / members of external scopes

- L50 _typedef_ `typedef UAnimGraphNode_LinkedAnimGraph UAnimGraphNode_SubInstance;` — `UE_DEPRECATED(4.24, "UAnimGraphNode_SubInstance has been renamed to UAnimGraphNode_LinkedAnimGraph")`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_LinkedAnimGraphBase.h` (Public)


#### class `UAnimGraphNode_LinkedAnimGraphBase`  
`class UAnimGraphNode_LinkedAnimGraphBase : public UAnimGraphNode_CustomProperty, public IK2Node_EventNodeInterface`  
_L22-108_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAnimGraphNode_CustomProperty,IK2Node_EventNodeInterface`
- L28 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L31 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L32 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L33 _public prototype_ `virtual FText GetTooltipText() const override;`
- L34 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L35 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L36 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L37 _public prototype_ `virtual void CreateOutputPins() override;`
- L38 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L39 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L43 _public prototype_ `virtual FPoseLinkMappingRecord GetLinkIDLocation(const UScriptStruct* NodeType, UEdGraphPin* SourcePin) override;` — UAnimGraphNode_Base interface
- L44 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L45 _public function_ `virtual bool ShouldShowAttributesOnPins() const override`
- L46 _public prototype_ `virtual void OnCopyTermDefaultsToDefaultObject(IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintNodeCopyTermDefaultsContext& InPerNodeContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L47 _public prototype_ `virtual void GetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const override;`
- L50 _public prototype_ `virtual bool IsStructuralProperty(FProperty* InProperty) const override;` — UAnimGraphNode_CustomProperty interface
- L51 _public function_ `virtual bool NeedsToSpecifyValidTargetClass() const override`
- L54 _public prototype_ `virtual FAnimNode_LinkedAnimGraph* GetLinkedAnimGraphNode() PURE_VIRTUAL(UAnimGraphNode_LinkedAnimGraphBase::GetLinkedAnimGraphNode, return nullptr;);` — Node accessor
- L55 _public prototype_ `virtual const FAnimNode_LinkedAnimGraph* GetLinkedAnimGraphNode() const PURE_VIRTUAL(UAnimGraphNode_LinkedAnimGraphBase::GetLinkedAnimGraphNode, return nullptr;);`
- L58 _public prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetEventNodeAction(const FText& ActionCategory) override;` — IK2Node_EventNodeInterface interface
- L64 _protected prototype_ `void AllocatePoseLinks();` — Called pre-compilation to allocate pose links
- L67 _protected prototype_ `bool HasInstanceLoop();` — Finds out whether there is a loop in the graph formed by linked instances from this node
- L70 _protected prototype_ `void GenerateExposedPinsDetails(IDetailLayoutBuilder &DetailBuilder);` — Generates widgets for exposing/hiding Pins for this node using the provided detail builder
- L76 _protected prototype_ `static bool HasInstanceLoop_Recursive(UAnimGraphNode_LinkedAnimGraphBase* CurrNode, TArray<FGuid>& VisitedNodes, TArray<FGuid>& NodeStack);` — Finds out whether there is a loop in the graph formed by linked instances from CurrNode, used by HasInstanceLoop. VisitedNodes and NodeStack are required to track the graph links VisitedNodes - Node we have searched the links of, so we don't do it twice NodeStack - The currently considered chain of nodes. If a loop is detected this will contain the chain that causes the loop
- L81 _protected prototype_ `virtual FString GetCurrentInstanceBlueprintPath() const;` — Gets path to the currently selected instance class' blueprint
- L83 _protected prototype_ `virtual bool OnShouldFilterInstanceBlueprint(const FAssetData& AssetData) const;` — Filter callback for blueprints (only accept matching skeletons/interfaces)
- L85 _protected prototype_ `void OnSetInstanceBlueprint(const FAssetData& AssetData, IDetailLayoutBuilder* InDetailBuilder);` — Instance blueprint was changed by user
- L88 _protected prototype_ `virtual FLinearColor GetDefaultNodeTitleColor() const;`
- L91 _protected function_ `virtual void HandleFunctionReferenceChanged(FName InNewName)` — Handler for when the function reference gets re-resolved on node reconstruction
- L94 _protected prototype_ `void IterateFunctionParameters(UFunction* InFunction, TFunctionRef<void(const FName&, const FEdGraphPinType&)> InFunc) const;` — Helper func for generating pins
- L98 _protected member_ `FMemberReference FunctionReference;` — `UPROPERTY()` — Reference to the stub function that this node uses
- L101 _protected member_ `FString SkeletonName;` — Skeleton name used for filtering unloaded classes
- L104 _protected member_ `bool bIsTemplateAnimBlueprint = false;` — Template flag used for filtering unloaded classes
- L107 _protected member_ `bool bIsInterfaceBlueprint = false;` — Interface flag used for filtering unloaded classes

#### Free symbols / members of external scopes

- L111 _typedef_ `typedef UAnimGraphNode_LinkedAnimGraphBase UAnimGraphNode_SubInstanceBase;` — `UE_DEPRECATED(4.24, "UAnimGraphNode_SubInstanceBase has been renamed to UAnimGraphNode_LinkedAnimGraphBase")`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_LinkedAnimLayer.h` (Public)


#### class `UAnimGraphNode_LinkedAnimLayer`  
`class UAnimGraphNode_LinkedAnimLayer : public UAnimGraphNode_LinkedAnimGraphBase`  
_L19-113_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_LinkedAnimGraphBase`
- L26 _public member_ `FAnimNode_LinkedAnimLayer Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L30 _public member_ `FGuid InterfaceGuid;` — `UPROPERTY()` — Guid of the named layer graph we refer to
- L33 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L36 _public prototype_ `virtual FText GetTooltipText() const override;`
- L37 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L38 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L39 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L40 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L41 _public prototype_ `virtual void JumpToDefinition() const override;`
- L42 _public prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput ) const override;`
- L43 _public prototype_ `virtual void ReconstructNode() override;`
- L47 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L48 _public prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L51 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — UAnimGraphNode_Base interface
- L54 _public prototype_ `void UpdateGuidForLayer();` — Optionally updates layer GUID if it is invalid
- L57 _public prototype_ `void SetLayerName(FName InName);` — Sets the name of the layer we refer to
- L60 _public prototype_ `FName GetLayerName() const;` — Gets the name of the layer we refer to
- L63 _protected prototype_ `void GetLinkTarget(UObject* &OutTargetGraph, UBlueprint* &OutTargetBlueprint) const;`
- L67 _protected prototype_ `void GetLayerNames(TArray<TSharedPtr<FString>>& OutStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems);` — ----- UI CALLBACKS ----- // Handlers for layer combo
- L68 _protected prototype_ `FString GetLayerNameString() const;`
- L69 _protected prototype_ `void OnLayerChanged(IDetailLayoutBuilder* DetailBuilder);`
- L70 _protected prototype_ `bool HasAvailableLayers() const;`
- L71 _protected prototype_ `bool HasValidNonSelfLayer() const;`
- L72 _protected prototype_ `void HandleSetObjectBeingDebugged(UObject* InDebugObj);`
- L73 _protected prototype_ `void HandleInstanceChanged();`
- L77 _protected prototype_ `virtual FProperty* GetPinProperty(FName InPinName) const override;` — UAnimGraphNode_Base interface
- L78 _protected prototype_ `virtual void CreateCustomPins(TArray<UEdGraphPin*>* OldPins) override;`
- L81 _protected function_ `virtual FAnimNode_CustomProperty* GetCustomPropertyNode() override`
- L82 _protected function_ `virtual const FAnimNode_CustomProperty* GetCustomPropertyNode() const override`
- L83 _protected prototype_ `virtual UClass* GetTargetSkeletonClass() const override;`
- L86 _protected prototype_ `virtual FAnimNode_LinkedAnimGraph* GetLinkedAnimGraphNode() override;`
- L87 _protected prototype_ `virtual const FAnimNode_LinkedAnimGraph* GetLinkedAnimGraphNode() const override;`
- L88 _protected prototype_ `virtual bool OnShouldFilterInstanceBlueprint(const FAssetData& AssetData) const override;`
- L89 _protected prototype_ `virtual FString GetCurrentInstanceBlueprintPath() const override;`
- L90 _protected prototype_ `virtual bool IsStructuralProperty(FProperty* InProperty) const override;`
- L91 _protected prototype_ `virtual FLinearColor GetDefaultNodeTitleColor() const override;`
- L92 _protected prototype_ `virtual void HandleFunctionReferenceChanged(FName InNewName) override;`
- L97 _protected prototype_ `TSubclassOf<UInterface> GetInterfaceForLayer() const;` — Helper function to get the interface currently in use by the selected layer
- L100 _protected prototype_ `FGuid GetGuidForLayer() const;` — Helper function to get the interface graph GUID currently in use by the selected layer
- L103 _protected prototype_ `FAnimNode_LinkedAnimLayer* GetPreviewNode() const;` — Get the preview node, if any, when instanced in an animation blueprint and debugged
- L106 _protected prototype_ `void SetupFromLayerId(FName InLayerId);` — Helper function to setup a newly spawned node
- L109 _protected prototype_ `void ValidateCircularRefAndNesting(const UEdGraph* CurrentGraph, const TArray<UEdGraph*>& AllGraphs, TArray<const UEdGraph*> GraphStack, bool bWithinLinkedLayerGraph, FCompilerResultsLog& MessageLog);` — Used during compilation to check if the blueprint structure causes any circular references or nested linked layer nodes
- L112 _protected member_ `FDelegateHandle SetObjectBeingDebuggedHandle;` — Handle used to hook into object being debugged changing

#### Free symbols / members of external scopes

- L116 _typedef_ `typedef UAnimGraphNode_LinkedAnimLayer UAnimGraphNode_Layer;` — `UE_DEPRECATED(4.24, "UAnimGraphNode_Layer has been renamed to UAnimGraphNode_LinkedAnimLayer")`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_LinkedInputPose.h` (Public)


#### struct `FAnimBlueprintFunctionPinInfo`  
`struct FAnimBlueprintFunctionPinInfo`  
_L20-43_
- reflection: `USTRUCT()`
- desc: Required info for reconstructing a manually specified pin
- L24 _public function_ `FAnimBlueprintFunctionPinInfo() : Name(NAME_None)`
- L30 _public function_ `FAnimBlueprintFunctionPinInfo(const FName& InName, const FEdGraphPinType& InType) : Name(InName) , Type(InType)`
- L38 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Inputs")` — The name of this parameter
- L42 _public member_ `FEdGraphPinType Type;` — `UPROPERTY(EditAnywhere, Category = "Inputs")` — The type of this parameter

#### class `UAnimGraphNode_LinkedInputPose`  
`class UAnimGraphNode_LinkedInputPose : public UAnimGraphNode_Base, public IClassVariableCreator`  
_L46-141_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base,IClassVariableCreator`
- L52 _public member_ `FAnimNode_LinkedInputPose Node;` — `UPROPERTY(EditAnywhere, Category = "Inputs")`
- L55 _public member_ `TArray<FAnimBlueprintFunctionPinInfo> Inputs;` — `UPROPERTY(EditAnywhere, Category = "Inputs")`
- L59 _public member_ `FMemberReference FunctionReference;` — `UPROPERTY()` — Reference to the stub function we use to build our parameters
- L63 _public member_ `int32 InputPoseIndex;` — `UPROPERTY()` — The index of the input pose, used alongside FunctionReference to build parameters
- L65 _public prototype_ `UAnimGraphNode_LinkedInputPose();`
- L68 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L71 _public prototype_ `virtual void CreateClassVariablesFromBlueprint(IAnimBlueprintVariableCreationContext& InCreationContext) override;` — IClassVariableCreator interface
- L74 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L75 _public prototype_ `virtual FText GetTooltipText() const override;`
- L76 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L77 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L78 _public prototype_ `virtual bool CanUserDeleteNode() const override;`
- L79 _public prototype_ `virtual bool CanDuplicateNode() const override;`
- L80 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L81 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L82 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L83 _public prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;`
- L84 _public prototype_ `virtual bool HasExternalDependencies(TArray<UStruct*>* OptionalOutput) const override;`
- L87 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& InCompilerContext, UEdGraph* InSourceGraph) override;` — UK2Node interface
- L90 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — UAnimGraphNode_Base interface
- L91 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L92 _public function_ `virtual bool ShouldShowAttributesOnPins() const override`
- L93 _public prototype_ `virtual void OnCopyTermDefaultsToDefaultObject(IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintNodeCopyTermDefaultsContext& InPerNodeContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L94 _public prototype_ `virtual void GetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const override;`
- L97 _public prototype_ `TSharedRef<SWidget> MakeNameWidget(IDetailLayoutBuilder& DetailBuilder);` — Make a name widget for this linked input pose node
- L100 _public function_ `bool IsEditable() const` — @return whether this node is editable. Non-editable nodes are implemented from function interfaces
- L103 _public prototype_ `int32 GetNumInputs() const;` — @return the number of parameter inputs this node provides. This is either determined via the Inputs array or via the FunctionReference.
- L106 _public prototype_ `void PromoteFromInterfaceOverride();` — Promotes the node from being a part of an interface override to a full function that allows for parameter and result pin additions
- L109 _public prototype_ `void ConformInputPoseName();` — Conform input pose name according to function
- L112 _public prototype_ `bool ValidateAgainstFunctionReference() const;` — Validate pose index against the function reference (used to determine whether we should exist or not)
- L115 _public prototype_ `void IterateFunctionParameters(TFunctionRef<void(const FName&, const FEdGraphPinType&)> InFunc) const;` — Helper function for iterating stub function parameters
- L122 _private prototype_ `void AllocatePinsInternal();` — Helper function for common code in AllocateDefaultPins and ReallocatePinsDuringReconstruction
- L125 _private prototype_ `void CreateUserDefinedPins();` — Create pins from the user-defined Inputs array
- L128 _private prototype_ `void CreatePinsFromStubFunction(const UFunction* Function);` — Create pins from the stub function FunctionReference
- L132 _private prototype_ `void AnalyzeLinks(TArrayView<UAnimGraphNode_Base*> InAnimNodes);` — Called pre-compilation to evaluate is this input pose is used
- L135 _private prototype_ `static void ReconstructLayerNodes(UBlueprint* InBlueprint);` — Reconstruct any layer nodes in this BP post-edit
- L139 _private prototype_ `void HandleInputPoseArrayChanged();` — UI helper functions
- L140 _private prototype_ `void HandleInputPinArrayChanged();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API ANIMGRAPH_API`
- L144 _typedef_ `typedef UAnimGraphNode_LinkedInputPose UAnimGraphNode_SubInput;` — `UE_DEPRECATED(4.24, "UAnimGraphNode_SubInput has been renamed to UAnimGraphNode_LinkedInputPose")`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_LocalRefPose.h` (Public)


#### class `UAnimGraphNode_LocalRefPose`  
`class UAnimGraphNode_LocalRefPose : public UAnimGraphNode_RefPoseBase`  
_L11-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_RefPoseBase`
- L16 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L17 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_LocalToComponentSpace.h` (Public)


#### class `UAnimGraphNode_LocalToComponentSpace`  
`class UAnimGraphNode_LocalToComponentSpace : public UAnimGraphNode_Base`  
_L12-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_ConvertLocalToComponentSpace Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L20 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L21 _private prototype_ `virtual FText GetTooltipText() const override;`
- L22 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L23 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L27 _private prototype_ `virtual void CreateOutputPins() override;` — UAnimGraphNode_Base interface
- L28 _private prototype_ `virtual void PostProcessPinName(const UEdGraphPin* Pin, FString& DisplayName) const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_LookAt.h` (Public)


#### class `UAnimGraphNode_LookAt`  
`class UAnimGraphNode_LookAt : public UAnimGraphNode_SkeletalControlBase`  
_L16-49_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Look At, Follow, Trace, Track"))`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L21 _private member_ `FAnimNode_LookAt Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L26 _public prototype_ `virtual FText GetTooltipText() const override;`
- L27 _public prototype_ `virtual FEditorModeID GetEditorMode() const override;`
- L28 _public prototype_ `virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* InPreviewNode) override;`
- L29 _public prototype_ `virtual void CopyPinDefaultsToNodeData(UEdGraphPin* InPin) override;`
- L33 _public prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* SkelMeshComp) const override;` — UAnimGraphNode_SkeletalControlBase interface
- L34 _public prototype_ `virtual void GetOnScreenDebugInfo(TArray<FText>& DebugInfo, FAnimNode_Base* RuntimeAnimNode, USkeletalMeshComponent* PreviewSkelMeshComp) const override;`
- L39 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L40 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L44 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L48 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/AnimGraph/Public/AnimGraphNode_MakeDynamicAdditive.h` (Public)


#### class `UAnimGraphNode_MakeDynamicAdditive`  
`class UAnimGraphNode_MakeDynamicAdditive : public UAnimGraphNode_Base`  
_L12-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_MakeDynamicAdditive Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L20 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L21 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L22 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L26 _private prototype_ `virtual FString GetNodeCategory() const override;` — UAnimGraphNode_Base interface
- L27 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_MeshRefPose.h` (Public)


#### class `UAnimGraphNode_MeshRefPose`  
`class UAnimGraphNode_MeshRefPose : public UAnimGraphNode_Base`  
_L12-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_MeshSpaceRefPose Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L20 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L21 _private prototype_ `virtual FText GetTooltipText() const override;`
- L22 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private prototype_ `virtual FString GetNodeCategory() const override;` — UAnimGraphNode_Base interface
- L27 _private prototype_ `virtual void CreateOutputPins() override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_Mirror.h` (Public)


#### class `UAnimGraphNode_Mirror`  
`class UAnimGraphNode_Mirror : public UAnimGraphNode_Base`  
_L12-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L18 _public member_ `FAnimNode_Mirror Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L20 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L21 _public prototype_ `virtual FText GetTooltipText() const override;`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L23 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L24 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L25 _public prototype_ `virtual void PostLoad() override;`
- L26 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L27 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L28 _public prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L29 _public prototype_ `virtual EAnimAssetHandlerType SupportsAssetClass(const UClass* AssetClass) const override;`
- L30 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L31 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _public prototype_ `virtual void PreloadRequiredAssets() override;`
- L33 _public prototype_ `void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;`
- L36 _private prototype_ `static FText GetTitleGivenAssetInfo(const FText& AssetName);`
- L37 _private prototype_ `void OnMirrorDataTableChanged();`
- L38 _private prototype_ `void BindMirrorDataTableChangedDelegate();`
- L39 _private prototype_ `bool HasMirrorDataTableForBlueprints(const TArray<UBlueprint*>& Blueprints) const;`
- L41 _private member_ `FString UnloadedSkeletonName;` — Used for filtering in the Blueprint context menu when the sequence asset this node uses is unloaded

### `Source/Editor/AnimGraph/Public/AnimGraphNode_ModifyBone.h` (Public)


#### class `UAnimGraphNode_ModifyBone`  
`class UAnimGraphNode_ModifyBone : public UAnimGraphNode_SkeletalControlBase`  
_L17-46_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Modify Transform"))`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L22 _private member_ `FAnimNode_ModifyBone Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L26 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L27 _public prototype_ `virtual FText GetTooltipText() const override;`
- L32 _protected prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L33 _protected prototype_ `virtual FEditorModeID GetEditorMode() const override;`
- L34 _protected prototype_ `virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* InPreviewNode) override;`
- L35 _protected prototype_ `virtual void CopyPinDefaultsToNodeData(UEdGraphPin* InPin) override;`
- L39 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L40 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L45 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_ModifyCurve.h` (Public)


#### class `UAnimGraphNode_ModifyCurve`  
`class UAnimGraphNode_ModifyCurve : public UAnimGraphNode_Base`  
_L15-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- desc: Easy way to modify curve values on a pose
- L20 _private member_ `FAnimNode_ModifyCurve Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L23 _public prototype_ `UAnimGraphNode_ModifyCurve();`
- L26 _public prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L27 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L28 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L32 _public prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;` — UAnimGraphNode_Base interface
- L36 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L41 _private prototype_ `void RemoveCurvePin(FName CurveName);` — Remove a curve pin with the given name
- L43 _private prototype_ `void AddCurvePin(FName CurveName);` — Add a curve pin with the given name
- L45 _private prototype_ `void GetAddCurveMenuActions(FMenuBuilder& MenuBuilder) const;` — Create submenu with options for curves to add
- L47 _private prototype_ `void GetRemoveCurveMenuActions(FMenuBuilder& MenuBuilder) const;` — Create submenu with options for curves to remove

### `Source/Editor/AnimGraph/Public/AnimGraphNode_MultiWayBlend.h` (Public)


#### class `UAnimGraphNode_MultiWayBlend`  
`class UAnimGraphNode_MultiWayBlend : public UAnimGraphNode_Base`  
_L9-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L14 _private member_ `FAnimNode_MultiWayBlend Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L18 _private prototype_ `virtual void AddPinToBlendNode();` — Adds a new pose pin @TODO: Generalize this behavior (returning a list of actions/delegates maybe?)
- L19 _private prototype_ `virtual void RemovePinFromBlendNode(UEdGraphPin* Pin);`
- L20 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L23 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L24 _private prototype_ `virtual FText GetTooltipText() const override;`
- L25 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L30 _private prototype_ `virtual FString GetNodeCategory() const override;`
- L34 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L38 _private prototype_ `virtual void PostEditUndo() override;`
- L42 _private member_ `int32 RemovedPinArrayIndex;`
- L45 _private prototype_ `void RemovePinsFromOldPins(TArray<UEdGraphPin*>& OldPins, int32 RemovedArrayIndex);` — removes removed pins and adjusts array indices of remained pins

### `Source/Editor/AnimGraph/Public/AnimGraphNode_ObserveBone.h` (Public)


#### class `UAnimGraphNode_ObserveBone`  
`class UAnimGraphNode_ObserveBone : public UAnimGraphNode_SkeletalControlBase`  
_L19-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- desc: This allows you to observe the state of a bone at a particular point in the graph, showing it in any space and optionally relative to the reference pose
- L24 _private member_ `FAnimNode_ObserveBone Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L28 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L29 _public prototype_ `virtual FText GetTooltipText() const override;`
- L30 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L31 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L36 _protected prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L37 _protected prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L38 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L39 _protected prototype_ `virtual FEditorModeID GetEditorMode() const override;`
- L43 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L44 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_PoseBlendNode.h` (Public)


#### class `UAnimGraphNode_PoseBlendNode`  
`class UAnimGraphNode_PoseBlendNode : public UAnimGraphNode_PoseHandler`  
_L14-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_PoseHandler`
- L19 _private member_ `FAnimNode_PoseBlendNode Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L22 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L26 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L27 _private prototype_ `virtual FText GetTooltipText() const override;`
- L28 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L33 _private prototype_ `virtual bool DoesSupportTimeForTransitionGetter() const override;` — UAnimGraphNode_Base interface Interface to support transition getter
- L34 _private prototype_ `virtual void GetAllAnimationSequencesReferred(TArray<UAnimationAsset*>& AnimationAssets) const override;`
- L35 _private prototype_ `virtual void ReplaceReferredAnimations(const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap) override;`
- L36 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L37 _private prototype_ `virtual EAnimAssetHandlerType SupportsAssetClass(const UClass* AssetClass) const override;`
- L41 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L45 _private prototype_ `FText GetNodeTitleForPoseAsset(ENodeTitleType::Type TitleType, UPoseAsset* InPoseAsset) const;`
- L48 _private prototype_ `static FText GetTitleGivenAssetInfo(const FText& AssetName);`
- L51 _private member_ `FString UnloadedSkeletonName;` — Used for filtering in the Blueprint context menu when the pose asset this node uses is unloaded
- L54 _protected function_ `virtual FAnimNode_PoseHandler* GetPoseHandlerNode() override`
- L55 _protected function_ `virtual const FAnimNode_PoseHandler* GetPoseHandlerNode() const override`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_PoseByName.h` (Public)


#### class `UAnimGraphNode_PoseByName`  
`class UAnimGraphNode_PoseByName : public UAnimGraphNode_AssetPlayerBase`  
_L15-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_AssetPlayerBase`
- L20 _private member_ `FAnimNode_PoseByName Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L23 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L24 _private prototype_ `virtual FText GetTooltipText() const override;`
- L25 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L29 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L30 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L32 _private prototype_ `virtual bool DoesSupportTimeForTransitionGetter() const override;` — Interface to support transition getter
- L33 _private prototype_ `virtual UAnimationAsset* GetAnimationAsset() const override;`
- L34 _private prototype_ `virtual void GetAllAnimationSequencesReferred(TArray<UAnimationAsset*>& AnimationAssets) const override;`
- L35 _private prototype_ `virtual void ReplaceReferredAnimations(const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap) override;`
- L36 _private prototype_ `virtual EAnimAssetHandlerType SupportsAssetClass(const UClass* AssetClass) const override;`
- L40 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L41 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L46 _private prototype_ `virtual void SetAnimationAsset(UAnimationAsset* Asset) override;` — UAnimGraphNode_AssetPlayerBase interface
- L50 _private prototype_ `FText GetNodeTitleForPoseAsset(ENodeTitleType::Type TitleType, UPoseAsset* InPoseAsset) const;`
- L54 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/AnimGraph/Public/AnimGraphNode_PoseDriver.h` (Public)


#### class `UAnimGraphNode_PoseDriver`  
`class UAnimGraphNode_PoseDriver : public UAnimGraphNode_PoseHandler`  
_L17-134_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAnimGraphNode_PoseHandler`
- L22 _private member_ `FAnimNode_PoseDriver Node;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L26 _private member_ `float AxisLength;` — `UPROPERTY(EditAnywhere, Category = Debugging, meta = (DefaultValue = "20.0", UIMin = "1.0", UIMax = "100.0"))` — Length of axis in world units used for debug drawing
- L30 _private member_ `int32 ConeSubdivision;` — `UPROPERTY(EditAnywhere, Category = Debugging, meta = (DefaultValue = "32", UIMin = "6", UIMax = "128"))` — Number of subdivisions / lines used when debug drawing a cone
- L34 _private member_ `bool bDrawDebugCones;` — `UPROPERTY(EditAnywhere, Category = Debugging, meta = (DefaultValue = "True"))` — If checked the cones will be drawn in 3d for debugging
- L37 _private member_ `int32 SelectedTargetIndex;` — Used to indicate selected target to edit mode drawing
- L39 _private member_ `FSimpleMulticastDelegate SelectedTargetChangeDelegate;` — Delegate to call when selection changes
- L44 _public prototype_ `FAnimNode_PoseDriver* GetPreviewPoseDriverNode() const;` — Get the current preview node instance
- L48 _public prototype_ `void CopyTargetsFromPoseAsset();` — `UFUNCTION(BlueprintCallable, Category=PoseDriver)` — Util to replace current contents of PoseTargets with info from assigned PoseAsset
- L52 _public prototype_ `void SetSourceBones(const TArray<FName>& BoneNames);` — `UFUNCTION(BlueprintCallable, Category=PoseDriver)` — Sets the pose-driver its source bones by name
- L56 _public prototype_ `void GetSourceBoneNames(TArray<FName>& BoneNames);` — `UFUNCTION(BlueprintPure, Category=PoseDriver)` — Returns the pose-driver its source bones by name
- L60 _public prototype_ `void SetDrivingBones(const TArray<FName>& BoneNames);` — `UFUNCTION(BlueprintCallable, Category=PoseDriver)` — Set the pose-driver its driven bones by name
- L64 _public prototype_ `void GetDrivingBoneNames(TArray<FName>& BoneNames);` — `UFUNCTION(BlueprintPure, Category=PoseDriver)` — Returns the pose-driver its driven bones by name
- L68 _public prototype_ `void SetRBFParameters(FRBFParams Parameters);` — `UFUNCTION(BlueprintCallable, Category=PoseDriver)`
- L72 _public prototype_ `FRBFParams& GetRBFParameters();` — `UFUNCTION(BlueprintPure, Category=PoseDriver)`
- L76 _public prototype_ `void SetPoseDriverSource(EPoseDriverSource DriverSource);` — `UFUNCTION(BlueprintCallable, Category=PoseDriver)`
- L80 _public prototype_ `EPoseDriverSource& GetPoseDriverSource();` — `UFUNCTION(BlueprintPure, Category=PoseDriver)`
- L84 _public prototype_ `void SetPoseDriverOutput(EPoseDriverOutput DriverOutput);` — `UFUNCTION(BlueprintCallable, Category=PoseDriver)`
- L88 _public prototype_ `EPoseDriverOutput& GetPoseDriverOutput();` — `UFUNCTION(BlueprintPure, Category=PoseDriver)`
- L91 _public prototype_ `void AutoSetTargetScales(float& OutMaxDistance);` — Automatically modify TargetScale for each PoseTarget, based on distance to nearest neighbor
- L94 _public prototype_ `void AddNewTarget();` — Adds a new target, reallocating transforms array appropriately
- L97 _public prototype_ `void ReserveTargetTransforms();` — Reallocates transforms arrays as necessary to accommodate source bones
- L100 _public prototype_ `FLinearColor GetColorFromWeight(float InWeight);` — Return the color for a given weight. Used for Details and EditMode
- L104 _public member_ `TObjectPtr<USkeletalMeshComponent> LastPreviewComponent;` — `UPROPERTY(Transient)` — Used to refer back to preview instance in anim tools
- L107 _public prototype_ `virtual void PostLoad() override;`
- L108 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L112 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L113 _public prototype_ `virtual FText GetTooltipText() const override;`
- L114 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L115 _public prototype_ `virtual FLinearColor GetNodeBodyTintColor() const override;`
- L119 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L120 _public prototype_ `virtual FEditorModeID GetEditorMode() const override;`
- L121 _public prototype_ `virtual EAnimAssetHandlerType SupportsAssetClass(const UClass* AssetClass) const override;`
- L122 _public prototype_ `virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* InPreviewNode) override;`
- L127 _protected function_ `virtual bool IsPoseAssetRequired() override` — UAnimGraphNode_PoseHandler interface
- L128 _protected function_ `virtual FAnimNode_PoseHandler* GetPoseHandlerNode() override`
- L129 _protected function_ `virtual const FAnimNode_PoseHandler* GetPoseHandlerNode() const override`
- L133 _protected member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_PoseHandler.h` (Public)


#### class `UAnimGraphNode_PoseHandler`  
`class UAnimGraphNode_PoseHandler : public UAnimGraphNode_AssetPlayerBase`  
_L13-34_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UAnimGraphNode_AssetPlayerBase`
- L18 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L19 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L20 _private prototype_ `virtual UAnimationAsset* GetAnimationAsset() const override;`
- L21 _private prototype_ `virtual TSubclassOf<UAnimationAsset> GetAnimationAssetClass() const override;`
- L22 _private prototype_ `virtual void OnOverrideAssets(IAnimBlueprintNodeOverrideAssetsContext& InContext) const override;`
- L26 _private prototype_ `virtual void SetAnimationAsset(UAnimationAsset* Asset) override;` — UAnimGraphNode_AssetPlayerBase interface
- L30 _private function_ `virtual bool IsPoseAssetRequired()` — UAnimGraphNode_PoseHandler interface
- L31 _private prototype_ `virtual FAnimNode_PoseHandler* GetPoseHandlerNode() PURE_VIRTUAL(UAnimGraphNode_PoseHandler::GetPoseHandlerNode, return nullptr;);`
- L32 _private prototype_ `virtual const FAnimNode_PoseHandler* GetPoseHandlerNode() const PURE_VIRTUAL(UAnimGraphNode_PoseHandler::GetPoseHandlerNode, return nullptr;);`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_PoseSnapshot.h` (Public)


#### class `UAnimGraphNode_PoseSnapshot`  
`class UAnimGraphNode_PoseSnapshot : public UAnimGraphNode_Base`  
_L13-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L18 _private member_ `FAnimNode_PoseSnapshot Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L21 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L22 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L23 _private prototype_ `virtual FText GetMenuCategory() const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_RandomPlayer.h` (Public)


#### class `UAnimGraphNode_RandomPlayer`  
`class UAnimGraphNode_RandomPlayer : public UAnimGraphNode_Base`  
_L12-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L19 _public member_ `FAnimNode_RandomPlayer Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L23 _public prototype_ `virtual FText GetTooltipText() const override;`
- L24 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L29 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;` — UAnimGraphNode_Base interface
- L30 _public prototype_ `virtual void PreloadRequiredAssets() override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_RefPoseBase.h` (Public)


#### class `UAnimGraphNode_RefPoseBase`  
`class UAnimGraphNode_RefPoseBase : public UAnimGraphNode_Base`  
_L12-23_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_RefPose Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L20 _private prototype_ `virtual FString GetNodeCategory() const override;` — UEdGraphNode interface
- L21 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_RemoveCurve.h` (Public)


#### class `UAnimGraphNode_RemoveCurve`  
`class UAnimGraphNode_RemoveCurve : public UAnimGraphNode_Base`  
_L12-30_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UAnimGraphNode_Base`
- desc: Removes animation curves on a pose
- L17 _private member_ `FAnimNode_RemoveCurve Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L21 _public prototype_ `UAnimGraphNode_RemoveCurve();`
- L24 _public prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _public prototype_ `virtual FText GetMenuCategory() const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_ResetRoot.h` (Public)


#### class `UAnimGraphNode_ResetRoot`  
`class UAnimGraphNode_ResetRoot : public UAnimGraphNode_SkeletalControlBase`  
_L12-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L17 _private member_ `FAnimNode_ResetRoot Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L21 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L24 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L31 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L32 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_RigidBody.h` (Public)


#### class `UAnimGraphNode_RigidBody`  
`class UAnimGraphNode_RigidBody : public UAnimGraphNode_SkeletalControlBase`  
_L11-50_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Simulate Rigid Body Physics Ragdoll"))`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L16 _private member_ `FAnimNode_RigidBody Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L20 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L21 _public prototype_ `virtual FText GetTooltipText() const override;`
- L22 _public prototype_ `virtual FString GetNodeCategory() const override;`
- L23 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L27 _public prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* PreviewSkelMeshComp, const bool bIsSelected, const bool bIsPoseWatchEnabled) const override;` — UAnimGraphNode_Base
- L28 _public prototype_ `virtual void OnPoseWatchChanged(const bool IsPoseWatchActive, TObjectPtr<UPoseWatch> InPoseWatch, FEditorModeTools& InModeTools, FAnimNode_Base* InRuntimeNode) override;`
- L30 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L31 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L33 _public prototype_ `void ToggleBodyVisibility();`
- L34 _public prototype_ `void ToggleConstraintVisibility();`
- L38 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L39 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L42 _protected prototype_ `bool AreAnyBodiesHidden() const;`
- L43 _protected prototype_ `bool AreAnyConstraintsHidden() const;`
- L45 _protected prototype_ `static EVisibility ShouldShowPoseScalePropagationSettings();`
- L48 _private member_ `TWeakObjectPtr<UPoseWatchElement> PoseWatchElementBodies;`
- L49 _private member_ `TWeakObjectPtr<UPoseWatchElement> PoseWatchElementConstraints;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_Root.h` (Public)


#### class `UAnimGraphNode_Root`  
`class UAnimGraphNode_Root : public UAnimGraphNode_Base`  
_L14-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L19 _private member_ `FAnimNode_Root Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L22 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L26 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _private prototype_ `virtual FText GetTooltipText() const override;`
- L28 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L29 _private function_ `virtual bool CanUserDeleteNode() const override`
- L30 _private function_ `virtual bool CanDuplicateNode() const override`
- L31 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L32 _private function_ `virtual bool IsNodeRootSet() const override`
- L36 _private prototype_ `virtual bool IsPoseWatchable() const override;`
- L37 _private prototype_ `virtual bool IsSinkNode() const override;`
- L38 _private prototype_ `virtual void OnProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L39 _private prototype_ `virtual void OnCopyTermDefaultsToDefaultObject(IAnimBlueprintCopyTermDefaultsContext& InCompilationContext, IAnimBlueprintNodeCopyTermDefaultsContext& InPerNodeContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L42 _private prototype_ `virtual FString GetDocumentationLink() const override;` — Get the link to the documentation

### `Source/Editor/AnimGraph/Public/AnimGraphNode_RotateRootBone.h` (Public)


#### class `UAnimGraphNode_RotateRootBone`  
`class UAnimGraphNode_RotateRootBone : public UAnimGraphNode_Base`  
_L13-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L18 _private member_ `FAnimNode_RotateRootBone Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L21 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L22 _private prototype_ `virtual FText GetTooltipText() const override;`
- L23 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L24 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L25 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L29 _private prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_RotationMultiplier.h` (Public)


#### class `UAnimGraphNode_RotationMultiplier`  
`class UAnimGraphNode_RotationMultiplier : public UAnimGraphNode_SkeletalControlBase`  
_L13-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L18 _private member_ `FAnimNode_RotationMultiplier Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L23 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L29 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L34 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/AnimGraph/Public/AnimGraphNode_RotationOffsetBlendSpace.h` (Public)


#### class `UAnimGraphNode_RotationOffsetBlendSpace`  
`class UAnimGraphNode_RotationOffsetBlendSpace: public UAnimGraphNode_BlendSpaceBase`  
_L16-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendSpaceBase`
- L21 _private member_ `FAnimNode_RotationOffsetBlendSpace Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L24 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L28 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L29 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L33 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L34 _private prototype_ `virtual UAnimationAsset* GetAnimationAsset() const override;`
- L35 _private prototype_ `virtual void OnOverrideAssets(IAnimBlueprintNodeOverrideAssetsContext& InContext) const override;`
- L36 _private prototype_ `virtual void GetAllAnimationSequencesReferred(TArray<UAnimationAsset*>& AnimationAssets) const override;`
- L37 _private prototype_ `virtual void ReplaceReferredAnimations(const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap) override;`
- L38 _private prototype_ `virtual EAnimAssetHandlerType SupportsAssetClass(const UClass* AssetClass) const override;`
- L39 _private prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L40 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L44 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L45 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L46 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L50 _private prototype_ `virtual void SetAnimationAsset(UAnimationAsset* Asset) override;` — UAnimGraphNode_AssetPlayerBase interface
- L55 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/AnimGraph/Public/AnimGraphNode_RotationOffsetBlendSpaceGraph.h` (Public)


#### class `UAnimGraphNode_RotationOffsetBlendSpaceGraph`  
`class UAnimGraphNode_RotationOffsetBlendSpaceGraph : public UAnimGraphNode_BlendSpaceGraphBase`  
_L16-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendSpaceGraphBase`
- L22 _private member_ `FAnimNode_RotationOffsetBlendSpaceGraph Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L25 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L28 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L31 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L32 _private prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L35 _private prototype_ `virtual void BakeDataDuringCompilation(FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L36 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_SaveCachedPose.h` (Public)


#### class `UAnimGraphNode_SaveCachedPose`  
`class UAnimGraphNode_SaveCachedPose : public UAnimGraphNode_Base`  
_L17-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L22 _private member_ `FAnimNode_SaveCachedPose Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L25 _private member_ `FString CacheName;` — `UPROPERTY(EditAnywhere, Category=CachedPose)`
- L28 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L29 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L30 _private prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L31 _private prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L32 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L33 _private function_ `virtual bool IsNodeRootSet() const override`
- L34 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L35 _private prototype_ `virtual void PostPasteNode() override;`
- L39 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface.
- L43 _private prototype_ `virtual FString GetNodeCategory() const override;` — UAnimGraphNode_Base interface
- L44 _private function_ `virtual bool IsSinkNode() const override`
- L45 _private prototype_ `virtual void GetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const override;`
- L50 _private prototype_ `bool MakeUniqueCacheName();`
- L53 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/AnimGraph/Public/AnimGraphNode_ScaleChainLength.h` (Public)


#### class `UAnimGraphNode_ScaleChainLength`  
`class UAnimGraphNode_ScaleChainLength : public UAnimGraphNode_Base`  
_L12-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_ScaleChainLength Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L20 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L21 _private prototype_ `virtual FText GetTooltipText() const override;`
- L22 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private prototype_ `virtual FString GetNodeCategory() const override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_SequenceEvaluator.h` (Public)


#### class `UAnimGraphNode_SequenceEvaluator`  
`class UAnimGraphNode_SequenceEvaluator : public UAnimGraphNode_AssetPlayerBase`  
_L15-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_AssetPlayerBase`
- L20 _private member_ `FAnimNode_SequenceEvaluator Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L23 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L24 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L25 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L29 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L30 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L31 _private prototype_ `virtual void BakeDataDuringCompilation(class FCompilerResultsLog& MessageLog) override;`
- L33 _private prototype_ `virtual bool DoesSupportTimeForTransitionGetter() const override;` — Interface to support transition getter
- L34 _private prototype_ `virtual UAnimationAsset* GetAnimationAsset() const override;`
- L35 _private prototype_ `virtual const TCHAR* GetTimePropertyName() const override;`
- L36 _private prototype_ `virtual UScriptStruct* GetTimePropertyStruct() const override;`
- L37 _private prototype_ `virtual void GetAllAnimationSequencesReferred(TArray<UAnimationAsset*>& AnimationAssets) const override;`
- L38 _private prototype_ `virtual void ReplaceReferredAnimations(const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap) override;`
- L39 _private prototype_ `virtual EAnimAssetHandlerType SupportsAssetClass(const UClass* AssetClass) const override;`
- L40 _private prototype_ `virtual void OnOverrideAssets(IAnimBlueprintNodeOverrideAssetsContext& InContext) const override;`
- L41 _private prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L45 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L46 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L50 _private prototype_ `virtual void SetAnimationAsset(UAnimationAsset* Asset) override;` — UAnimGraphNode_AssetPlayerBase interface
- L51 _private prototype_ `virtual void CopySettingsFromAnimationAsset(UAnimationAsset* Asset) override;`
- L54 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_SequencePlayer.h` (Public)


#### class `UAnimGraphNode_SequencePlayer`  
`class UAnimGraphNode_SequencePlayer : public UAnimGraphNode_AssetPlayerBase`  
_L15-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_AssetPlayerBase`
- L20 _private member_ `FAnimNode_SequencePlayer Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L23 _private prototype_ `void Serialize(FArchive& Ar) override;` — UObject interface
- L26 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L27 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L28 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L29 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L30 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L34 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — UAnimGraphNode_Base interface
- L35 _private prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L36 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;`
- L37 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L38 _private prototype_ `virtual void BakeDataDuringCompilation(class FCompilerResultsLog& MessageLog) override;`
- L39 _private prototype_ `virtual bool DoesSupportTimeForTransitionGetter() const override;`
- L40 _private prototype_ `virtual UAnimationAsset* GetAnimationAsset() const override;`
- L41 _private prototype_ `virtual const TCHAR* GetTimePropertyName() const override;`
- L42 _private prototype_ `virtual UScriptStruct* GetTimePropertyStruct() const override;`
- L43 _private prototype_ `virtual void GetAllAnimationSequencesReferred(TArray<UAnimationAsset*>& AnimationAssets) const override;`
- L44 _private prototype_ `virtual void ReplaceReferredAnimations(const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap) override;`
- L45 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L46 _private prototype_ `virtual EAnimAssetHandlerType SupportsAssetClass(const UClass* AssetClass) const override;`
- L47 _private prototype_ `virtual void OnOverrideAssets(IAnimBlueprintNodeOverrideAssetsContext& InContext) const override;`
- L48 _private prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L49 _private function_ `virtual TSubclassOf<UAnimationAsset> GetAnimationAssetClass() const`
- L53 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L57 _private prototype_ `virtual void SetAnimationAsset(UAnimationAsset* Asset) override;` — UAnimGraphNode_AssetPlayerBase interface
- L58 _private prototype_ `virtual void CopySettingsFromAnimationAsset(UAnimationAsset* Asset) override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_SkeletalControlBase.h` (Public)


#### class `UAnimGraphNode_SkeletalControlBase`  
`class UAnimGraphNode_SkeletalControlBase : public UAnimGraphNode_Base`  
_L25-175_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAnimGraphNode_Base`
- desc: This is the base class for the 'source version' of all skeletal control animation graph nodes (nodes that manipulate the pose rather than playing animations to create a pose or blending between poses) Concrete subclasses should contain a member struct derived from FAnimNode_SkeletalControlBase
- L31 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L35 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L36 _public prototype_ `virtual FText GetTooltipText() const override;`
- L37 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L38 _public prototype_ `virtual bool ShowVisualWarning() const override;`
- L39 _public prototype_ `virtual FText GetVisualWarningTooltipText() const override;`
- L43 _public prototype_ `virtual FString GetNodeCategory() const override;` — UAnimGraphNode_Base interface
- L44 _public prototype_ `virtual void CreateOutputPins() override;`
- L45 _public prototype_ `virtual void ValidateAnimNodePostCompile(FCompilerResultsLog& MessageLog, UAnimBlueprintGeneratedClass* CompiledClass, int32 CompiledNodeIndex) override;`
- L46 _public prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L47 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L54 _public function_ `virtual FVector GetWidgetLocation(const USkeletalMeshComponent* SkelComp, struct FAnimNode_SkeletalControlBase* AnimNode)` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — methods related to widget control
- L60 _public function_ `virtual void CopyNodeDataTo(FAnimNode_Base* OutAnimNode)` — `UE_DEPRECATED(4.14, "This function is deprecated and is no longer used, please use CopyNodeDataToPreviewNode")`
- L63 _public function_ `virtual void CopyNodeDataFrom(const FAnimNode_Base* NewAnimNode)` — `UE_DEPRECATED(4.14, "This function is deprecated and is no longer used")`
- L66 _public prototype_ `bool IsPinShown(const FName PinName) const;` — Are we currently showing this pin
- L70 _public prototype_ `virtual int32 GetWidgetCoordinateSystem(const USkeletalMeshComponent* SkelComp);` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — Returns the coordinate system that should be used for this bone
- L74 _public prototype_ `virtual int32 GetWidgetMode(const USkeletalMeshComponent* SkelComp);` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — return current widget mode this anim graph node supports
- L77 _public prototype_ `virtual int32 ChangeToNextWidgetMode(const USkeletalMeshComponent* SkelComp, int32 CurWidgetMode);` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — called when the user changed widget mode by pressing "Space" key
- L80 _public function_ `virtual bool SetWidgetMode(const USkeletalMeshComponent* SkelComp, int32 InWidgetMode)` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — called when the user set widget mode directly, returns true if InWidgetMode is available
- L84 _public prototype_ `virtual FName FindSelectedBone();` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")`
- L88 _public function_ `virtual void MoveSelectActorLocation(const USkeletalMeshComponent* SkelComp, FAnimNode_SkeletalControlBase* InAnimNode)` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — if anim graph node needs other actors to select other bones, move actor's positions when this is called
- L91 _public function_ `virtual bool IsActorClicked(HActor* ActorHitProxy)` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")`
- L93 _public function_ `virtual void ProcessActorClick(HActor* ActorHitProxy)` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")`
- L96 _public function_ `virtual void DeselectActor(USkeletalMeshComponent* SkelComp)` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — if it has select-actors, should hide all actors when de-select is called
- L100 _public function_ `virtual void DoTranslation(const USkeletalMeshComponent* SkelComp, FVector& Drag, FAnimNode_Base* InOutAnimNode)` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — called when the widget is dragged in translation mode
- L103 _public function_ `virtual void DoRotation(const USkeletalMeshComponent* SkelComp, FRotator& Rotation, FAnimNode_Base* InOutAnimNode)` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — called when the widget is dragged in rotation mode
- L106 _public function_ `virtual void DoScale(const USkeletalMeshComponent* SkelComp, FVector& Scale, FAnimNode_Base* InOutAnimNode)` — `UE_DEPRECATED(4.14, "This function is deprecated. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — called when the widget is dragged in scale mode
- L111 _public prototype_ `void SetDefaultValue(const FName InDefaultValueName, const FVector& InValue);` — set literal value for FVector
- L113 _public prototype_ `void GetDefaultValue(const FName UpdateDefaultValueName, FVector& OutVec);` — get literal value for vector
- L115 _public function_ `void GetDefaultValue(const FName PropName, FRotator& OutValue)`
- L125 _public function_ `template<class ValueType> ValueType GetNodeValue(const FName PropName, const ValueType& CompileNodeValue)`
- L136 _public function_ `void SetDefaultValue(const FName PropName, const FRotator& InValue)`
- L143 _public function_ `template<class ValueType> void SetNodeValue(const FName PropName, ValueType& CompileNodeValue, const ValueType& InValue)`
- L154 _protected prototype_ `virtual FText GetControllerDescription() const;` — Returns the short descriptive name of the controller
- L161 _protected prototype_ `void ConvertToComponentSpaceTransform(const USkeletalMeshComponent* SkelComp, const FTransform & InTransform, FTransform & OutCSTransform, int32 BoneIndex, EBoneControlSpace Space) const;` — `UE_DEPRECATED(4.14, "This function is moved to FAnimNodeEditMode. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — local conversion function for drawing
- L164 _protected prototype_ `FVector ConvertCSVectorToBoneSpace(const USkeletalMeshComponent* SkelComp, FVector& InCSVector, FCSPose<FCompactHeapPose>& MeshBases, const FName& BoneName, const EBoneControlSpace Space);` — `UE_DEPRECATED(4.14, "This function is moved to FAnimNodeEditMode. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — convert drag vector in component space to bone space
- L167 _protected prototype_ `FQuat ConvertCSRotationToBoneSpace(const USkeletalMeshComponent* SkelComp, FRotator& InCSRotator, FCSPose<FCompactHeapPose>& MeshBases, const FName& BoneName, const EBoneControlSpace Space);` — `UE_DEPRECATED(4.14, "This function is moved to FAnimNodeEditMode. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — convert rotator in component space to bone space
- L170 _protected prototype_ `FVector ConvertWidgetLocation(const USkeletalMeshComponent* InSkelComp, FCSPose<FCompactHeapPose>& InMeshBases, const FName& BoneName, const FVector& InLocation, const EBoneControlSpace Space);` — `UE_DEPRECATED(4.14, "This function is moved to FAnimNodeEditMode. Use a IAnimNodeEditMode-derived class to implement a new editor mode and override GetEditorMode to return its ID")` — convert widget location according to bone control space
- L172 _protected prototype_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const PURE_VIRTUAL(UAnimGraphNode_SkeletalControlBase::GetNode, return nullptr;);`
- L174 _protected prototype_ `FAnimNode_SkeletalControlBase* GetDebuggedNode() const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_Slot.h` (Public)


#### class `UAnimGraphNode_Slot`  
`class UAnimGraphNode_Slot : public UAnimGraphNode_Base`  
_L13-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L18 _private member_ `FAnimNode_Slot Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L21 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L22 _private prototype_ `virtual FText GetTooltipText() const override;`
- L23 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L27 _private prototype_ `virtual FString GetNodeCategory() const override;`
- L28 _private prototype_ `virtual void BakeDataDuringCompilation(class FCompilerResultsLog& MessageLog) override;`
- L29 _private prototype_ `virtual void GetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const override;`
- L35 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/AnimGraph/Public/AnimGraphNode_SplineIK.h` (Public)


#### class `UAnimGraphNode_SplineIK`  
`class UAnimGraphNode_SplineIK : public UAnimGraphNode_SkeletalControlBase`  
_L11-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L16 _private member_ `FAnimNode_SplineIK Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L21 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L22 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L26 _public prototype_ `virtual FText GetTooltipText() const override;`
- L29 _public prototype_ `virtual FEditorModeID GetEditorMode() const;` — UAnimGraphNode_Base interface
- L32 _public function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override` — UAnimGraphNode_SkeletalControlBase interface
- L36 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L40 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/AnimGraph/Public/AnimGraphNode_SpringBone.h` (Public)


#### class `UAnimGraphNode_SpringBone`  
`class UAnimGraphNode_SpringBone : public UAnimGraphNode_SkeletalControlBase`  
_L13-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L18 _private member_ `FAnimNode_SpringBone Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L21 _private prototype_ `virtual void PostLoad();`
- L26 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L27 _public prototype_ `virtual FText GetTooltipText() const override;`
- L32 _protected prototype_ `virtual FText GetControllerDescription() const override;`
- L33 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L38 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/AnimGraph/Public/AnimGraphNode_StateMachine.h` (Public)


#### class `UAnimGraphNode_StateMachine`  
`class UAnimGraphNode_StateMachine : public UAnimGraphNode_StateMachineBase`  
_L12-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_StateMachineBase`
- L18 _private member_ `FAnimNode_StateMachine Node;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Runtime state machine representation (empty; populated during compilation)
- L21 _private function_ `virtual FAnimNode_StateMachine& GetNode() override` — UAnimGraphNode_StateMachineBase interface

### `Source/Editor/AnimGraph/Public/AnimGraphNode_StateMachineBase.h` (Public)


#### class `UAnimGraphNode_StateMachineBase`  
`class UAnimGraphNode_StateMachineBase : public UAnimGraphNode_Base`  
_L17-57_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAnimGraphNode_Base`
- L23 _private member_ `TObjectPtr<class UAnimationStateMachineGraph> EditorStateMachineGraph;` — `UPROPERTY()` — Editor state machine representation
- L26 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L27 _private prototype_ `virtual FText GetTooltipText() const override;`
- L28 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L29 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L30 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L31 _private prototype_ `virtual void JumpToDefinition() const override;`
- L32 _private prototype_ `virtual void DestroyNode() override;`
- L33 _private prototype_ `virtual void PostPasteNode() override;`
- L34 _private prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L35 _private prototype_ `virtual FString GetDocumentationLink() const override;`
- L36 _private prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L37 _private prototype_ `virtual TArray<UEdGraph*> GetSubGraphs() const override;`
- L38 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L42 _private prototype_ `virtual void OnProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;` — UAnimGraphNode_Base interface
- L43 _private prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L44 _private prototype_ `virtual void GetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const override;`
- L48 _private prototype_ `FString GetStateMachineName();` — @return the name of this state machine
- L51 _private prototype_ `virtual FAnimNode_StateMachine& GetNode() PURE_VIRTUAL(UAnimGraphNode_StateMachineBase::GetNode, static FAnimNode_StateMachine Dummy; return Dummy;);` — Interface for derived classes to implement
- L56 _private member_ `FNodeTextCache CachedFullTitle;` — Constructing FText strings can be costly, so we cache the node's title

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_StateResult.h` (Public)


#### class `UAnimGraphNode_StateResult`  
`class UAnimGraphNode_StateResult : public UAnimGraphNode_Base`  
_L13-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L18 _private member_ `FAnimNode_StateResult Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L21 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L24 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _private prototype_ `virtual FText GetTooltipText() const override;`
- L26 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L27 _private function_ `virtual bool CanUserDeleteNode() const override`
- L28 _private function_ `virtual bool CanDuplicateNode() const override`
- L29 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L30 _private function_ `virtual bool IsNodeRootSet() const override`
- L34 _private prototype_ `virtual bool IsSinkNode() const override;`
- L35 _private prototype_ `virtual void OnProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L36 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L37 _private prototype_ `virtual void AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L38 _private prototype_ `virtual void GetBoundFunctionsInfo(TArray<TPair<FName, FName>>& InOutBindingsInfo) override;`
- L41 _private prototype_ `virtual bool ReferencesFunction(const FName& InFunctionName, const UStruct* InScope) const override;` — UK2Node interface
- L44 _private prototype_ `virtual FString GetDocumentationLink() const override;` — Get the link to the documentation
- L50 _private member_ `FMemberReference StateEntryFunction;` — `UPROPERTY(EditAnywhere, Category = "Functions", meta=(FunctionReference, AllowFunctionLibraries, PrototypeFunction="/Script/AnimGraphRuntime.AnimExecutionContextLibrary.Prototype_ThreadSafeAnimUpdateCall", DefaultBindingName="OnStateEntry"), DisplayName="On State Entry")` — Function called when the owning state is entered, meaning it becomes the state machine's current state.
- L59 _private member_ `FMemberReference StateFullyBlendedInFunction;` — `UPROPERTY(EditAnywhere, Category = "Functions", meta=(FunctionReference, AllowFunctionLibraries, PrototypeFunction="/Script/AnimGraphRuntime.AnimExecutionContextLibrary.Prototype_ThreadSafeAnimUpdateCall", DefaultBindingName="OnStateFullyBlendedIn"), DisplayName="On State Fully Blended In")` — Function called when the owning state is fully blended in. Notes: - This is only called for the state machine's current state since its the most recent transition's target state. - This will not be called if the state is skipped. This can happen when the flag bSkipFirstUpdateTransition on the state machine node is set to true.
- L63 _private member_ `FMemberReference StateExitFunction;` — `UPROPERTY(EditAnywhere, Category = "Functions", meta=(FunctionReference, AllowFunctionLibraries, PrototypeFunction="/Script/AnimGraphRuntime.AnimExecutionContextLibrary.Prototype_ThreadSafeAnimUpdateCall", DefaultBindingName="OnStateExit"), DisplayName="On State Exit")` — Function called when the owning state is exited, meaning it stops being the state machine's current state.
- L72 _private member_ `FMemberReference StateFullyBlendedOutFunction;` — `UPROPERTY(EditAnywhere, Category = "Functions", meta=(FunctionReference, AllowFunctionLibraries, PrototypeFunction="/Script/AnimGraphRuntime.AnimExecutionContextLibrary.Prototype_ThreadSafeAnimUpdateCall", DefaultBindingName="OnStateFullyBlendedOut"), DisplayName="On State Fully Blended Out")` — Function called when the owning state is fully blended out. Notes: - This will be called for any states that had weight. - This will not be called if the state is skipped. This can happen when the flag bSkipFirstUpdateTransition on the state machine node is set to true.

### `Source/Editor/AnimGraph/Public/AnimGraphNode_Trail.h` (Public)


#### class `UAnimGraphNode_Trail`  
`class UAnimGraphNode_Trail : public UAnimGraphNode_SkeletalControlBase`  
_L13-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L18 _private member_ `FAnimNode_Trail Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L22 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L23 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L27 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L29 _public prototype_ `virtual FText GetTooltipText() const override;` — virtual FString GetNodeNativeTitle(ENodeTitleType::Type TitleType) const override;
- L30 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L35 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L36 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`
- L37 _protected prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent * PreviewSkelMeshComp) const override;`
- L41 _protected prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L42 _protected prototype_ `virtual void OnNodeSelected(bool bInIsSelected, class FEditorModeTools& InModeTools, struct FAnimNode_Base* InRuntimeNode);`
- L46 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title
- L47 _private prototype_ `void DrawAngularLimits(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* SkelMeshComp, const FAnimNode_Trail& NodeToVisualize, const TArray<FName>& TrailBoneList) const;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_TransitionPoseEvaluator.h` (Public)


#### class `UAnimGraphNode_TransitionPoseEvaluator`  
`class UAnimGraphNode_TransitionPoseEvaluator : public UAnimGraphNode_Base`  
_L16-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L21 _private member_ `FAnimNode_TransitionPoseEvaluator Node;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)`
- L24 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L25 _private prototype_ `virtual FText GetTooltipText() const override;`
- L26 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L27 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;`
- L28 _private function_ `virtual bool CanDuplicateNode() const override`
- L29 _private prototype_ `virtual bool CanUserDeleteNode() const override;`
- L30 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L34 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — UAnimGraphNode_Base interface
- L35 _private prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L39 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface.
- L44 _private prototype_ `static EVisibility GetCacheFramesVisibility(IDetailLayoutBuilder* DetailLayoutBuilder);` — Details customization helpers

### `Source/Editor/AnimGraph/Public/AnimGraphNode_TransitionResult.h` (Public)


#### class `UAnimGraphNode_TransitionResult`  
`class UAnimGraphNode_TransitionResult : public UAnimGraphNode_Base`  
_L14-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L19 _private member_ `FAnimNode_TransitionResult Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L22 _private function_ `virtual bool CanUserDeleteNode() const override` — UEdGraphNode interface
- L23 _private function_ `virtual bool CanDuplicateNode() const override`
- L24 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _private prototype_ `virtual FText GetTooltipText() const override;`
- L26 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L27 _private function_ `virtual bool IsNodeRootSet() const override`
- L28 _private prototype_ `virtual bool ShowVisualWarning() const override;`
- L29 _private prototype_ `virtual FText GetVisualWarningTooltipText() const override;`
- L33 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface.
- L37 _private function_ `virtual bool IsSinkNode() const override` — UAnimGraphNode_Base interface

### `Source/Editor/AnimGraph/Public/AnimGraphNode_TwistCorrectiveNode.h` (Public)


#### class `UAnimGraphNode_TwistCorrectiveNode`  
`class UAnimGraphNode_TwistCorrectiveNode : public UAnimGraphNode_SkeletalControlBase`  
_L19-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- desc: This is the 'source version' of a bone driven controller, which maps part of the state from one bone to another (e.g., 2 * source.x -> target.z)
- L24 _private member_ `FAnimNode_TwistCorrectiveNode Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L29 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L30 _public prototype_ `virtual FText GetTooltipText() const override;`
- L36 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase protected interface
- L37 _protected prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L38 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_TwoBoneIK.h` (Public)


#### class `UAnimGraphNode_TwoBoneIK`  
`class UAnimGraphNode_TwoBoneIK : public UAnimGraphNode_SkeletalControlBase`  
_L20-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L25 _private member_ `FAnimNode_TwoBoneIK Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L29 _private member_ `bool bEnableDebugDraw;` — `UPROPERTY(EditAnywhere, Category=Debug)` — Enable drawing of the debug information of the node
- L32 _private member_ `static TSharedPtr<class FTwoBoneIKDelegate> TwoBoneIKDelegate;` — just for refreshing UIs when bone space was changed
- L36 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L40 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L41 _public prototype_ `virtual FText GetTooltipText() const override;`
- L45 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — UAnimGraphNode_Base interface
- L46 _public prototype_ `virtual FEditorModeID GetEditorMode() const;`
- L47 _public prototype_ `virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* InPreviewNode) override;`
- L48 _public prototype_ `virtual void CopyPinDefaultsToNodeData(UEdGraphPin* InPin) override;`
- L52 _public function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override` — UAnimGraphNode_SkeletalControlBase interface
- L55 _public member_ `IDetailLayoutBuilder* DetailLayout;`
- L59 _protected prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* SkelMeshComp) const override;` — UAnimGraphNode_SkeletalControlBase interface
- L60 _protected prototype_ `virtual FText GetControllerDescription() const override;`
- L65 _private member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

#### Free symbols / members of external scopes

- L14 _macro_ `#define ABoneSelectActor ATargetPoint` — actor class used for bone selector

### `Source/Editor/AnimGraph/Public/AnimGraphNode_TwoWayBlend.h` (Public)


#### class `UAnimGraphNode_TwoWayBlend`  
`class UAnimGraphNode_TwoWayBlend : public UAnimGraphNode_Base`  
_L12-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_TwoWayBlend BlendNode;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L20 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L24 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _private prototype_ `virtual FText GetTooltipText() const override;`
- L26 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L27 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L28 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _private prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L33 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Source/Editor/AnimGraph/Public/AnimGraphNode_UseCachedPose.h` (Public)


#### class `UAnimGraphNode_UseCachedPose`  
`class UAnimGraphNode_UseCachedPose : public UAnimGraphNode_Base`  
_L15-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L21 _public member_ `FAnimNode_UseCachedPose Node;` — `UPROPERTY()`
- L24 _public member_ `mutable TWeakObjectPtr<UAnimGraphNode_SaveCachedPose> SaveCachedPoseNode;` — `UPROPERTY()`
- L28 _public prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L29 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L30 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L31 _public prototype_ `virtual void JumpToDefinition() const override;`
- L35 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface.
- L36 _public prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L40 _public prototype_ `virtual FString GetNodeCategory() const override;` — UAnimGraphNode_Base interface
- L41 _public prototype_ `virtual void EarlyValidation(class FCompilerResultsLog& MessageLog) const override;`
- L42 _public prototype_ `virtual void OnProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L43 _public prototype_ `virtual void GetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const override;`
- L48 _private member_ `mutable FString NameOfCache;` — `UPROPERTY()`

### `Source/Editor/AnimGraph/Public/AnimGraphSettings.h` (Public)


#### class `UAnimGraphSettings`  
`class UAnimGraphSettings : public UDeveloperSettings`  
_L9-34_
- reflection: `UCLASS(config=Editor)`
- inherits: `UDeveloperSettings`
- L15 _public prototype_ `virtual FName GetContainerName() const override;`
- L16 _public prototype_ `virtual FName GetCategoryName() const override;`
- L18 _public prototype_ `virtual FText GetSectionText() const override;`
- L19 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L28 _public member_ `bool bShowInstancedEnumBlendAnimNodeBlueprintActions = true;` — `UPROPERTY(EditAnywhere, config, Category = "Workflow")` — If true, populates the blueprint action menu with pre-bound blend-by-enum nodes for supported enums. For large projects this can clutter the context menu so it may be preferable to hide those entries.
- L32 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Source/Editor/AnimGraph/Public/AnimNodeEditMode.h` (Public)


#### class `FAnimNodeEditMode`  
`class FAnimNodeEditMode : public IAnimNodeEditMode`  
_L40-129_
- inherits: `IAnimNodeEditMode`
- desc: Base implementation for anim node edit modes
- L43 _public prototype_ `FAnimNodeEditMode();`
- L46 _public prototype_ `virtual ECoordSystem GetWidgetCoordinateSystem() const override;` — IAnimNodeEditMode interface
- L47 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L48 _public prototype_ `virtual UE::Widget::EWidgetMode ChangeToNextWidgetMode(UE::Widget::EWidgetMode CurWidgetMode) override;`
- L49 _public prototype_ `virtual bool SetWidgetMode(UE::Widget::EWidgetMode InWidgetMode) override;`
- L50 _public prototype_ `virtual FName GetSelectedBone() const override;`
- L51 _public prototype_ `virtual void DoTranslation(FVector& InTranslation) override;`
- L52 _public prototype_ `virtual void DoRotation(FRotator& InRotation) override;`
- L53 _public prototype_ `virtual void DoScale(FVector& InScale) override;`
- L54 _public prototype_ `virtual void EnterMode(class UAnimGraphNode_Base* InEditorNode, struct FAnimNode_Base* InRuntimeNode) override;`
- L55 _public prototype_ `virtual void ExitMode() override;`
- L56 _public function_ `virtual bool SupportsPoseWatch() override`
- L59 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override;` — IPersonaEditMode interface
- L60 _public prototype_ `virtual class IPersonaPreviewScene& GetAnimPreviewScene() const override;`
- L61 _public prototype_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugInfo) const override;`
- L64 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;` — FEdMode interface
- L65 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L66 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L67 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L68 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L69 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L70 _public prototype_ `virtual bool InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent) override;`
- L71 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L72 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L73 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L74 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L75 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L76 _public prototype_ `virtual void Exit() override;`
- L77 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L79 _public prototype_ `virtual void RegisterPoseWatchedNode(UAnimGraphNode_Base* InEditorNode, FAnimNode_Base* InRuntimeNode);`
- L96 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;` — Start IGizmoEdModeInterface overrides
- L97 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L102 _protected prototype_ `static void ConvertToComponentSpaceTransform(const USkeletalMeshComponent* SkelComp, const FTransform & InTransform, FTransform & OutCSTransform, int32 BoneIndex, EBoneControlSpace Space);` — local conversion functions for drawing
- L103 _protected prototype_ `static void ConvertToBoneSpaceTransform(const USkeletalMeshComponent* SkelComp, const FTransform & InCSTransform, FTransform & OutBSTransform, int32 BoneIndex, EBoneControlSpace Space);`
- L105 _protected prototype_ `static FVector ConvertCSVectorToBoneSpace(const USkeletalMeshComponent* SkelComp, FVector& InCSVector, FCSPose<FCompactHeapPose>& MeshBases, const FName& BoneName, const EBoneControlSpace Space);` — convert drag vector in component space to bone space
- L106 _protected prototype_ `static FVector ConvertCSVectorToBoneSpace(const USkeletalMeshComponent* SkelComp, FVector& InCSVector, FCSPose<FCompactHeapPose>& MeshBases, const FBoneSocketTarget& InTarget, const EBoneControlSpace Space);`
- L108 _protected prototype_ `static FQuat ConvertCSRotationToBoneSpace(const USkeletalMeshComponent* SkelComp, FRotator& InCSRotator, FCSPose<FCompactHeapPose>& MeshBases, const FName& BoneName, const EBoneControlSpace Space);` — convert rotator in component space to bone space
- L110 _protected prototype_ `static FVector ConvertWidgetLocation(const USkeletalMeshComponent* InSkelComp, FCSPose<FCompactHeapPose>& InMeshBases, const FName& BoneName, const FVector& InLocation, const EBoneControlSpace Space);` — convert widget location according to bone control space
- L111 _protected prototype_ `static FVector ConvertWidgetLocation(const USkeletalMeshComponent* InSkelComp, FCSPose<FCompactHeapPose>& InMeshBases, const FBoneSocketTarget& Target, const FVector& InLocation, const EBoneControlSpace Space);`
- L113 _protected prototype_ `virtual UAnimGraphNode_Base* GetActiveWidgetAnimNode() const;` — Return the editor node associated with the selected widget. All widget operations are performed on this node.
- L114 _protected prototype_ `virtual FAnimNode_Base* GetActiveWidgetRuntimeAnimNode() const;` — Return the runtime node associated with the selected widget. All widget operations are performed on this node.
- L116 _protected function_ `const bool IsManipulatingWidget() const`
- L119 _protected prototype_ `bool HandleBeginTransform();` — Manage the start and end of a transform action in the viewport.
- L120 _protected prototype_ `bool HandleEndTransform();`
- L122 _protected member_ `TArray< EditorRuntimeNodePair > SelectedAnimNodes;` — Selected Anim Graph Nodes
- L123 _protected member_ `TArray< EditorRuntimeNodePair > PoseWatchedAnimNodes;` — Pose Watched Anim Graph Nodes.
- L126 _private member_ `bool bManipulating;`
- L128 _private member_ `bool bInTransaction;`

#### struct `FAnimNodeEditMode::EditorRuntimeNodePair`  
`struct EditorRuntimeNodePair`  
_L81-93_
- L83 _public function_ `EditorRuntimeNodePair(UAnimGraphNode_Base* InEditorAnimNode, FAnimNode_Base* InRuntimeAnimNode) : EditorAnimNode(InEditorAnimNode) , RuntimeAnimNode(InRuntimeAnimNode)`
- L89 _public member_ `UAnimGraphNode_Base* EditorAnimNode;` — The node we are operating on
- L92 _public member_ `FAnimNode_Base* RuntimeAnimNode;` — The runtime node in the preview scene

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimNodeEditModes.h` (Public)


#### struct `AnimNodeEditModes`  
`struct AnimNodeEditModes`  
_L10-22_
- L12 _public member_ `const static FEditorModeID AnimDynamics;`
- L13 _public member_ `const static FEditorModeID AnimNode;`
- L14 _public member_ `const static FEditorModeID TwoBoneIK;`
- L15 _public member_ `const static FEditorModeID ObserveBone;`
- L16 _public member_ `const static FEditorModeID ModifyBone;`
- L17 _public member_ `const static FEditorModeID Fabrik;`
- L18 _public member_ `const static FEditorModeID CCDIK;`
- L19 _public member_ `const static FEditorModeID PoseDriver;`
- L20 _public member_ `const static FEditorModeID SplineIK;`
- L21 _public member_ `const static FEditorModeID LookAt;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimPreviewAttacheInstance.h` (Public)


#### struct `FAnimPreviewAttacheInstanceProxy`  
`struct FAnimPreviewAttacheInstanceProxy : public FAnimInstanceProxy`  
_L16-38_
- reflection: `USTRUCT()`
- inherits: `FAnimInstanceProxy`
- desc: Proxy override for this UAnimInstance-derived class
- L21 _public function_ `FAnimPreviewAttacheInstanceProxy()`
- L25 _public function_ `FAnimPreviewAttacheInstanceProxy(UAnimInstance* InAnimInstance) : FAnimInstanceProxy(InAnimInstance)`
- L30 _public prototype_ `virtual void Initialize(UAnimInstance* InAnimInstance) override;`
- L31 _public prototype_ `virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;`
- L32 _public prototype_ `virtual void UpdateAnimationNode(const FAnimationUpdateContext& InContext) override;`
- L33 _public prototype_ `virtual bool Evaluate(FPoseContext& Output) override;`
- L37 _private member_ `FAnimNode_CopyPoseFromMesh CopyPoseFromMesh;` — Pose blend node for evaluating pose assets (for previewing curve sources)

#### class `UAnimPreviewAttacheInstance`  
`class UAnimPreviewAttacheInstance : public UAnimInstance`  
_L46-53_
- reflection: `UCLASS(MinimalAPI, transient, NotBlueprintable, noteditinlinenew)`
- inherits: `UAnimInstance`
- L51 _private prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimPreviewInstance.h` (Public)


#### enum `EMontagePreviewType`  
`enum EMontagePreviewType : int`  
_L20-27_
- reflection: `UENUM()`
- desc: Enum to know how montage is being played
- L23 _public enumerator_ `EMPT_Normal` — Playing montage in usual way.
- L25 _public enumerator_ `EMPT_AllSections` — Playing all sections.
- L26 _public enumerator_ `EMPT_MAX`

#### struct `FAnimPreviewInstanceProxy`  
`struct FAnimPreviewInstanceProxy : public FAnimSingleNodeInstanceProxy`  
_L32-156_
- reflection: `USTRUCT()`
- inherits: `FAnimSingleNodeInstanceProxy`
- desc: Proxy override for this UAnimInstance-derived class
- L37 _public function_ `FAnimPreviewInstanceProxy()`
- L42 _public function_ `FAnimPreviewInstanceProxy(UAnimInstance* InAnimInstance) : FAnimSingleNodeInstanceProxy(InAnimInstance) , SkeletalControlAlpha(1.0f) , bEnableControllers(true) , bSetKey(false)`
- L51 _public prototype_ `virtual void Initialize(UAnimInstance* InAnimInstance) override;`
- L52 _public prototype_ `virtual void Update(float DeltaSeconds) override;`
- L53 _public prototype_ `virtual void UpdateAnimationNode(const FAnimationUpdateContext& InContext) override;`
- L54 _public prototype_ `virtual bool Evaluate(FPoseContext& Output) override;`
- L55 _public prototype_ `virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;`
- L56 _public prototype_ `virtual void SetAnimationAsset(UAnimationAsset* NewAsset, USkeletalMeshComponent* MeshComponent, bool bIsLooping, float InPlayRate) override;`
- L58 _public prototype_ `void ResetModifiedBone(bool bCurveController = false);`
- L60 _public prototype_ `FAnimNode_ModifyBone* FindModifiedBone(const FName& InBoneName, bool bCurveController = false);`
- L62 _public prototype_ `FAnimNode_ModifyBone& ModifyBone(const FName& InBoneName, bool bCurveController = false);`
- L64 _public prototype_ `void RemoveBoneModification(const FName& InBoneName, bool bCurveController = false);`
- L66 _public function_ `void EnableControllers(bool bEnable)`
- L71 _public function_ `void SetSkeletalControlAlpha(float InSkeletalControlAlpha)`
- L77 _public function_ `void SetKey()`
- L82 _public function_ `FDelegateHandle AddKeyCompleteDelegate(FSimpleMulticastDelegate::FDelegate InOnSetKeyCompleteDelegate)`
- L87 _public function_ `void RemoveKeyCompleteDelegate(FDelegateHandle InDelegateHandle)`
- L93 _public prototype_ `void RefreshCurveBoneControllers(UAnimationAsset* AssetToRefreshFrom);`
- L95 _public function_ `TArray<FAnimNode_ModifyBone>& GetBoneControllers()`
- L100 _public function_ `TArray<FAnimNode_ModifyBone>& GetCurveBoneControllers()`
- L105 _public function_ `virtual void AddImpulseAtLocation(FVector Impulse, FVector Location, FName BoneName = NAME_None)`
- L108 _public prototype_ `void SetDebugSkeletalMeshComponent(USkeletalMeshComponent* InSkeletalMeshComponent);` — Sets an external debug skeletal mesh component to use to debug
- L111 _public prototype_ `USkeletalMeshComponent* GetDebugSkeletalMeshComponent() const;` — Gets the external debug skeletal mesh component we are debugging
- L114 _private prototype_ `void UpdateCurveController();`
- L116 _private prototype_ `void ApplyBoneControllers(TArray<FAnimNode_ModifyBone> &InBoneControllers, FComponentSpacePoseContext& ComponentSpacePoseContext);`
- L118 _private prototype_ `void SetKeyImplementation(const FCompactPose& PreControllerInLocalSpace, const FCompactPose& PostControllerInLocalSpace);`
- L120 _private prototype_ `void AddKeyToSequence(UAnimSequence* Sequence, float Time, const FName& BoneName, const FTransform& AdditiveTransform);`
- L124 _private member_ `TArray<FAnimNode_ModifyBone> BoneControllers;` — Controllers for individual bones
- L127 _private member_ `TArray<FAnimNode_ModifyBone> CurveBoneControllers;` — Curve modifiers
- L130 _private member_ `FAnimNode_CurveSource CurveSource;` — External curve for in-editor curve sources (such as audio)
- L133 _private member_ `FAnimNode_PoseBlendNode PoseBlendNode;` — Pose blend node for evaluating pose assets (for previewing curve sources)
- L136 _private member_ `FAnimNode_CopyPoseFromMesh CopyPoseNode;` — Allows us to copy a pose from the mesh being debugged
- L141 _private member_ `FSimpleMulticastDelegate OnSetKeyCompleteDelegate;` — Delegate to call after Key is set
- L144 _private member_ `float SkeletalControlAlpha;` — Shared parameters for previewing blendspace or animsequence
- L150 _private member_ `bool bEnableControllers;` — Used to determine if controller has to be applied or not Used to disable controller during editing
- L155 _private member_ `bool bSetKey;` — When this flag is true, it sets key

#### class `UAnimPreviewInstance`  
`class UAnimPreviewInstance : public UAnimSingleNodeInstance`  
_L164-294_
- reflection: `UCLASS(MinimalAPI, transient, NotBlueprintable, noteditinlinenew)`
- inherits: `UAnimSingleNodeInstance`
- L173 _private member_ `int32 MontagePreviewStartSectionIdx;` — `UPROPERTY(transient)`
- L176 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L180 _private prototype_ `virtual void NativeInitializeAnimation() override;`
- L181 _private prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;`
- L182 _private function_ `virtual bool CanRunParallelWork() const`
- L184 _protected prototype_ `virtual void Montage_Advance(float DeltaTime) override;`
- L189 _public prototype_ `void SetSkeletalControlAlpha(float SkeletalControlAlpha);` — Set SkeletalControl Alpha
- L191 _public prototype_ `UAnimSequence* GetAnimSequence();`
- L194 _public prototype_ `virtual void RestartMontage(UAnimMontage* Montage, FName FromSection = FName()) override;`
- L195 _public prototype_ `virtual void SetAnimationAsset(UAnimationAsset* NewAsset, bool bIsLooping = true, float InPlayRate = 1.f) override;`
- L199 _public prototype_ `void MontagePreview_JumpToStart();` — Montage preview functions
- L200 _public prototype_ `void MontagePreview_JumpToEnd();`
- L201 _public prototype_ `void MontagePreview_JumpToPreviewStart();`
- L202 _public prototype_ `void MontagePreview_Restart();`
- L203 _public prototype_ `void MontagePreview_PreviewNormal(int32 FromSectionIdx = INDEX_NONE, bool bPlay = true);`
- L204 _public prototype_ `void MontagePreview_SetLoopNormal(bool bIsLooping, int32 PreferSectionIdx = INDEX_NONE);`
- L205 _public prototype_ `void MontagePreview_PreviewAllSections(bool bPlay = true);`
- L206 _public prototype_ `void MontagePreview_SetLoopAllSections(bool bIsLooping);`
- L207 _public prototype_ `void MontagePreview_SetLoopAllSetupSections(bool bIsLooping);`
- L208 _public prototype_ `void MontagePreview_ResetSectionsOrder();`
- L209 _public prototype_ `void MontagePreview_SetLooping(bool bIsLooping);`
- L210 _public prototype_ `void MontagePreview_SetPlaying(bool bIsPlaying);`
- L211 _public prototype_ `void MontagePreview_SetReverse(bool bInReverse);`
- L212 _public prototype_ `void MontagePreview_StepForward();`
- L213 _public prototype_ `void MontagePreview_StepBackward();`
- L214 _public prototype_ `void MontagePreview_JumpToPosition(float NewPosition);`
- L215 _public prototype_ `int32 MontagePreview_FindFirstSectionAsInMontage(int32 AnySectionIdx);`
- L216 _public prototype_ `int32 MontagePreview_FindLastSection(int32 StartSectionIdx);`
- L217 _public prototype_ `float MontagePreview_CalculateStepLength();`
- L218 _public prototype_ `void MontagePreview_RemoveBlendOut();`
- L219 _public function_ `bool IsPlayingMontage()`
- L226 _public prototype_ `FAnimNode_ModifyBone* FindModifiedBone(const FName& InBoneName, bool bCurveController=false);` — Finds an already modified bone @param	InBoneName	The name of the bone modification to find @return the bone modification or NULL if no current modification was found
- L233 _public prototype_ `FAnimNode_ModifyBone& ModifyBone(const FName& InBoneName, bool bCurveController=false);` — Modifies a single bone. Create a new FAnimNode_ModifyBone if one does not exist for the passed-in bone. @param	InBoneName	The name of the bone to modify @return the new or existing bone modification
- L239 _public prototype_ `void RemoveBoneModification(const FName& InBoneName, bool bCurveController=false);` — Removes an existing bone modification @param	InBoneName	The name of the existing modification to remove
- L244 _public prototype_ `void ResetModifiedBone(bool bCurveController=false);` — Reset all bone modified
- L249 _public prototype_ `const TArray<FAnimNode_ModifyBone>& GetBoneControllers();` — Returns all currently active bone controllers on this instance's proxy
- L258 _public prototype_ `void SetKey();` — Convert current modified bone transforms (BoneControllers) to transform curves (CurveControllers) it does based on CurrentTime. This function does not set key directly here. It does wait until next update, and it gets the delta of transform before applying curves, and creates curves from it, so you'll need delegate if you'd like to do something after (set with SetKeyCompleteDelegate)
- L265 _public prototype_ `FDelegateHandle AddKeyCompleteDelegate(FSimpleMulticastDelegate::FDelegate InOnSetKeyCompleteDelegate);` — Add the delegate to be called when a key is set. @param Delegate To be called once set key is completed
- L272 _public prototype_ `void RemoveKeyCompleteDelegate(FDelegateHandle InDelegateHandle);` — Add the delegate to be called when a key is set. @param Delegate To be called once set key is completed
- L278 _public prototype_ `void RefreshCurveBoneControllers();` — Refresh Curve Bone Controllers based on TransformCurves from Animation data
- L284 _public prototype_ `void EnableControllers(bool bEnable);` — Enable Controllers This is used by when editing, when controller has to be disabled
- L287 _public prototype_ `void AddImpulseAtLocation(FVector Impulse, FVector Location, FName BoneName = NAME_None);` — Preview physics interaction
- L290 _public prototype_ `void SetDebugSkeletalMeshComponent(USkeletalMeshComponent* InSkeletalMeshComponent);` — Sets an external debug skeletal mesh component to use to debug
- L293 _public prototype_ `USkeletalMeshComponent* GetDebugSkeletalMeshComponent() const;` — Gets the external debug skeletal mesh component we are debugging

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimPropertyAccessUtils.h` (Public)
_(no declarations extracted)_

### `Source/Editor/AnimGraph/Public/AnimStateAliasNode.h` (Public)


#### class `UAnimStateAliasNode`  
`class UAnimStateAliasNode : public UAnimStateNodeBase`  
_L27-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimStateNodeBase`
- L33 _public member_ `bool bGlobalAlias;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Alias")`
- L36 _public member_ `FString StateAliasName;` — `UPROPERTY()`
- L39 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L42 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L43 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L44 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L45 _public prototype_ `virtual FText GetTooltipText() const override;`
- L46 _public function_ `virtual bool CanDuplicateNode() const override`
- L47 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L48 _public prototype_ `virtual void PostPasteNode() override;`
- L49 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L50 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L54 _public prototype_ `virtual UEdGraphPin* GetInputPin() const override;`
- L55 _public prototype_ `virtual UEdGraphPin* GetOutputPin() const override;`
- L56 _public prototype_ `virtual FString GetStateName() const override;`
- L57 _public prototype_ `virtual FString GetDesiredNewNodeName() const override;`
- L58 _public prototype_ `UObject* GetJumpTargetForDoubleClick() const;`
- L61 _public prototype_ `const TSet<TWeakObjectPtr<UAnimStateNodeBase>>& GetAliasedStates() const;`
- L62 _public prototype_ `TSet<TWeakObjectPtr<UAnimStateNodeBase>>& GetAliasedStates();`
- L65 _public prototype_ `UAnimStateNodeBase* GetAliasedState() const;` — Returns null if aliasing more than one state.
- L67 _public function_ `static FName GetAliasedStateNodesPropertyName()`
- L71 _private prototype_ `void RebuildAliasedStateNodeReferences();`
- L74 _private member_ `TSet<TWeakObjectPtr<UAnimStateNodeBase>> AliasedStateNodes;` — `UPROPERTY()`

### `Source/Editor/AnimGraph/Public/AnimStateConduitNode.h` (Public)


#### class `UAnimStateConduitNode`  
`class UAnimStateConduitNode : public UAnimStateNodeBase`  
_L14-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimStateNodeBase`
- L21 _public member_ `TObjectPtr<class UEdGraph> BoundGraph;` — `UPROPERTY()` — The transition graph for this conduit; it's a logic graph, not an animation graph
- L24 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L25 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L26 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L27 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _public function_ `virtual bool CanDuplicateNode() const override`
- L29 _public prototype_ `virtual void PostPasteNode() override;`
- L30 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L31 _public prototype_ `virtual void DestroyNode() override;`
- L32 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L33 _public function_ `virtual TArray<UEdGraph*> GetSubGraphs() const override`
- L37 _public prototype_ `virtual UEdGraphPin* GetInputPin() const override;`
- L38 _public prototype_ `virtual UEdGraphPin* GetOutputPin() const override;`
- L39 _public prototype_ `virtual FString GetStateName() const override;`
- L40 _public prototype_ `virtual FString GetDesiredNewNodeName() const override;`
- L41 _public function_ `virtual UEdGraph* GetBoundGraph() const override`
- L42 _public function_ `virtual void ClearBoundGraph() override`

### `Source/Editor/AnimGraph/Public/AnimStateEntryNode.h` (Public)


#### class `UAnimStateEntryNode`  
`class UAnimStateEntryNode : public UEdGraphNode`  
_L16-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- L22 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L23 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L24 _private prototype_ `virtual FText GetTooltipText() const override;`
- L25 _private function_ `virtual bool CanUserDeleteNode() const override`
- L26 _private function_ `virtual bool CanDuplicateNode() const override`
- L29 _private prototype_ `UEdGraphNode* GetOutputNode() const;`
- L30 _private prototype_ `UEdGraphPin* GetOutputPin() const;`

### `Source/Editor/AnimGraph/Public/AnimStateNode.h` (Public)


#### enum `EAnimStateType`  
`enum EAnimStateType : int`  
_L16-20_
- reflection: `UENUM()`
- L18 _public enumerator_ `AST_SingleAnimation UMETA(DisplayName="Single animation")`
- L19 _public enumerator_ `AST_BlendGraph UMETA(DisplayName="Blend graph")`

#### class `UAnimStateNode`  
`class UAnimStateNode : public UAnimStateNodeBase`  
_L24-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimStateNodeBase`
- L31 _public member_ `TObjectPtr<class UEdGraph> BoundGraph;` — `UPROPERTY()` — The animation graph for this state
- L35 _public member_ `TEnumAsByte<EAnimStateType> StateType;` — `UPROPERTY()` — The type of the contents of this state
- L38 _public member_ `FAnimNotifyEvent StateEntered;` — `UPROPERTY(EditAnywhere, Category = "Animation State")`
- L41 _public member_ `FAnimNotifyEvent StateLeft;` — `UPROPERTY(EditAnywhere, Category = "Animation State")`
- L44 _public member_ `FAnimNotifyEvent StateFullyBlended;` — `UPROPERTY(EditAnywhere, Category = "Animation State")`
- L48 _public member_ `bool bAlwaysResetOnEntry;` — `UPROPERTY(EditAnywhere, Category = "Animation State")` — Whether or not this state will ALWAYS reset it's state on reentry, regardless of remaining weight
- L51 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L55 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L56 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L57 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L58 _public prototype_ `virtual FText GetTooltipText() const override;`
- L59 _public function_ `virtual bool CanDuplicateNode() const override`
- L60 _public prototype_ `virtual void PostPasteNode() override;`
- L61 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L62 _public prototype_ `virtual void DestroyNode() override;`
- L63 _public function_ `virtual TArray<UEdGraph*> GetSubGraphs() const override`
- L64 _public prototype_ `virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;`
- L68 _public prototype_ `virtual UEdGraphPin* GetInputPin() const override;`
- L69 _public prototype_ `virtual UEdGraphPin* GetOutputPin() const override;`
- L70 _public prototype_ `virtual FString GetStateName() const override;`
- L74 _public prototype_ `UEdGraphPin* GetPoseSinkPinInsideState() const;` — @return the pose pin of the state sink node within the anim graph of this state
- L77 _public prototype_ `UAnimGraphNode_StateResult* GetResultNodeInsideState() const;` — @return the state sink node within the anim graph of this state
- L80 _public function_ `virtual UEdGraph* GetBoundGraph() const override`
- L81 _public function_ `virtual void ClearBoundGraph() override`

### `Source/Editor/AnimGraph/Public/AnimStateNodeBase.h` (Public)


#### class `UAnimStateNodeBase`  
`class UAnimStateNodeBase : public UEdGraphNode`  
_L17-58_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UEdGraphNode`
- L21 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L22 _private prototype_ `virtual void PostLoad() override;`
- L25 _private prototype_ `virtual void PostPasteNode() override;` — UEdGraphNode interface
- L26 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L27 _private prototype_ `virtual bool CanJumpToDefinition() const override;`
- L28 _private prototype_ `virtual void JumpToDefinition() const override;`
- L29 _private prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;`
- L30 _private prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L31 _private prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L35 _private function_ `virtual UEdGraphPin* GetInputPin() const` — @return the input pin for this state
- L38 _private function_ `virtual UEdGraphPin* GetOutputPin() const` — @return the output pin for this state
- L41 _private function_ `virtual FString GetStateName() const` — @return the name of this state
- L44 _private prototype_ `virtual void GetTransitionList(TArray<class UAnimStateTransitionNode*>& OutTransitions, bool bWantSortedList = false) const;` — Populates the OutTransitions array with a list of transition nodes connected to this state
- L46 _private function_ `virtual UEdGraph* GetBoundGraph() const`
- L47 _private function_ `virtual void ClearBoundGraph()`
- L49 _private prototype_ `UAnimBlueprint* GetAnimBlueprint() const;`
- L53 _protected function_ `virtual FString GetDesiredNewNodeName() const` — Name used as a seed when pasting nodes
- L57 _public prototype_ `virtual FString GetDocumentationLink() const override;` — Gets the animation state node documentation link

### `Source/Editor/AnimGraph/Public/AnimStateTransitionNode.h` (Public)


#### class `UAnimStateTransitionNode`  
`class UAnimStateTransitionNode : public UAnimStateNodeBase`  
_L20-226_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UAnimStateNodeBase`
- L26 _private member_ `TObjectPtr<class UEdGraph> BoundGraph;` — `UPROPERTY()` — The transition logic graph for this transition (returning a boolean)
- L30 _private member_ `TObjectPtr<class UEdGraph> CustomTransitionGraph;` — `UPROPERTY()` — The animation graph for this transition if it uses custom blending (returning a pose)
- L35 _private member_ `int32 PriorityOrder;` — `UPROPERTY(EditAnywhere, Category=Transition)` — The priority order of this transition. If multiple transitions out of a state go true at the same time, the one with the smallest priority order will take precedent
- L39 _private member_ `float CrossfadeDuration;` — `UPROPERTY(EditAnywhere, Config, Category=Transition, Meta=(ClampMin="0.0", ForceUnits="s"))` — The duration to cross-fade for
- L43 _private member_ `TEnumAsByte<ETransitionBlendMode::Type> CrossfadeMode_DEPRECATED;` — `UPROPERTY()` — The type of blending to use in the crossfade
- L46 _private member_ `EAlphaBlendOption BlendMode;` — `UPROPERTY(EditAnywhere, Category=Transition)`
- L49 _private member_ `TObjectPtr<UCurveFloat> CustomBlendCurve;` — `UPROPERTY(EditAnywhere, Category=Transition)`
- L54 _private member_ `TObjectPtr<UBlendProfile> BlendProfile_DEPRECATED;` — `UE_DEPRECATED(5.6, "Use the interfaced blend profile instead")` — `UPROPERTY()` — The blend profile to use to evaluate this transition per-bone
- L58 _private member_ `FBlendProfileInterfaceWrapper BlendProfileWrapper;` — `UPROPERTY(EditAnywhere, Category=Transition, meta=(UseAsBlendProfile=true))` — The blend profile to use to evaluate this transition per-bone
- L62 _private member_ `bool bAutomaticRuleBasedOnSequencePlayerInState;` — `UPROPERTY(EditAnywhere, Category=Transition)` — Try setting the rule automatically based on most relevant asset player node's remaining time and the Automatic Rule Trigger Time of the transition, ignoring the internal time
- L68 _private member_ `float AutomaticRuleTriggerTime;` — `UPROPERTY(EditAnywhere, Category=Transition, meta=(ForceUnits="s"))` — When should the automatic transition rule trigger relative to the time remaining on the relevant asset player: < 0 means trigger the transition 'Crossfade Duration' seconds before the end of the asset player, so a standard blend would finish just as the asset player ends >= 0 means trigger the transition 'Automatic Rule Trigger Time' seconds before the end of the asset player
- L74 _private member_ `float MinTimeBeforeReentry;` — `UPROPERTY(EditAnywhere, Category=Transition, DisplayName="Min Time Before Re-entry", meta=(ForceUnits="s"))` — The minimum time elapsed (in seconds) before the target state can be re-entered via this transition Has no effect when set to -1.0. When set to zero, wait at least one frame before re-entry via this transition is allowed.
- L78 _private member_ `FName SyncGroupNameToRequireValidMarkersRule;` — `UPROPERTY(EditAnywhere, Category = Transition)` — If SyncGroupName is specified, Transition will only be taken if the SyncGroup has valid markers (other transition rules still apply in addition to that).
- L82 _private member_ `TEnumAsByte<ETransitionLogicType::Type> LogicType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transition)` — What transition logic to use
- L85 _private member_ `FAnimNotifyEvent TransitionStart;` — `UPROPERTY(EditAnywhere, Category=Events)`
- L88 _private member_ `FAnimNotifyEvent TransitionEnd;` — `UPROPERTY(EditAnywhere, Category=Events)`
- L91 _private member_ `FAnimNotifyEvent TransitionInterrupt;` — `UPROPERTY(EditAnywhere, Category=Events)`
- L96 _private member_ `bool bAllowInertializationForSelfTransitions;` — `UPROPERTY(EditAnywhere, Category="Transition|Experimental")` — Whether to fall back to inertialization/dead blending when reentering an already-active state. This can avoid pops. The target state must enable bAlwaysResetOnEntry for the inertial blend to trigger.
- L100 _private member_ `bool Bidirectional;` — `UPROPERTY(EditAnywhere, Category=Transition)` — This transition can go both directions
- L104 _private member_ `bool bDisabled;` — `UPROPERTY(EditAnywhere, Category=Transition)` — Whether or not to disable this transition from being enterable
- L108 _private member_ `bool bOnlyEvaluateWhenActive;` — `UPROPERTY(EditAnywhere, Category=Transition)` — If true, this transition rule will not be evaluated when the state machine's update context is inactive (e.g. when blending out).
- L112 _private member_ `bool bSharedRules;` — `UPROPERTY()` — The rules for this transition may be shared with other transition nodes
- L116 _private member_ `bool bSharedCrossfade;` — `UPROPERTY()` — The cross-fade settings of this node may be shared
- L120 _private member_ `FString SharedRulesName;` — `UPROPERTY()` — What we call this transition if we are shared ('Transition X to Y' can't be used since its used in multiple places)
- L124 _private member_ `FGuid SharedRulesGuid;` — `UPROPERTY()` — Shared rules guid useful when copying between different state machines
- L128 _private member_ `FLinearColor SharedColor;` — `UPROPERTY()` — Color we draw in the editor as if we are shared
- L131 _private member_ `FString SharedCrossfadeName;` — `UPROPERTY()`
- L134 _private member_ `FGuid SharedCrossfadeGuid;` — `UPROPERTY()`
- L137 _private member_ `int32 SharedCrossfadeIdx;` — `UPROPERTY()`
- L140 _private member_ `FVector2D CachedRotation;` — `UPROPERTY()`
- L143 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L144 _private prototype_ `virtual void PostLoad() override;`
- L145 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L149 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L150 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L151 _private prototype_ `virtual FText GetTooltipText() const override;`
- L152 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L153 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L154 _private function_ `virtual bool CanDuplicateNode() const override`
- L155 _private prototype_ `virtual void PrepareForCopying() override;`
- L156 _private prototype_ `virtual void PostPasteNode() override;`
- L157 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L158 _private prototype_ `virtual void DestroyNode() override;`
- L159 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L160 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L161 _private prototype_ `virtual TArray<UEdGraph*> GetSubGraphs() const override;`
- L162 _private prototype_ `virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;`
- L166 _private function_ `virtual UEdGraph* GetBoundGraph() const override`
- L167 _private function_ `virtual void ClearBoundGraph() override`
- L168 _private function_ `virtual UEdGraphPin* GetInputPin() const override`
- L169 _private function_ `virtual UEdGraphPin* GetOutputPin() const override`
- L173 _private prototype_ `FString GetStateName() const override;` — @return the name of this state
- L175 _private prototype_ `UAnimStateNodeBase* GetPreviousState() const;`
- L176 _private prototype_ `UAnimStateNodeBase* GetNextState() const;`
- L177 _private prototype_ `void CreateConnections(UAnimStateNodeBase* PreviousState, UAnimStateNodeBase* NextState);`
- L183 _private prototype_ `void RelinkHead(UAnimStateNodeBase* NewTargetState);` — Relink transition head (where the arrow head is of a state transition) to a new state. @param[in] NewTargetState The new transition target.
- L189 _private prototype_ `void RelinkTail(UAnimStateNodeBase* NewSourceState);` — Relink transition tail (where the arrow base is of a state transition) to a new state. @param[in] NewSourceState The new transition source.
- L194 _private prototype_ `void Reverse();` — Reverse the direction of this transition
- L200 _private prototype_ `static TArray<UAnimStateTransitionNode*> GetListTransitionNodesToRelink(UEdGraphPin* SourcePin, UEdGraphPin* OldTargetPin, const TArray<UEdGraphNode*>& InSelectedGraphNodes);` — Helper function to gather the transition nodes to be relinked by taking the graph selection into account as well. For example when relinking a transition holding several transition nodes but only a few are selected to be relinked.
- L202 _private prototype_ `bool IsBoundGraphShared() const;`
- L204 _private prototype_ `void MakeRulesShareable(FString ShareName);`
- L205 _private prototype_ `void MakeCrossfadeShareable(FString ShareName);`
- L207 _private prototype_ `void UnshareRules();`
- L208 _private prototype_ `void UnshareCrossade();`
- L210 _private prototype_ `void UseSharedRules(const UAnimStateTransitionNode* Node);`
- L211 _private prototype_ `void UseSharedCrossfade(const UAnimStateTransitionNode* Node);`
- L213 _private prototype_ `void CopyCrossfadeSettings(const UAnimStateTransitionNode* SrcNode);`
- L214 _private prototype_ `void PropagateCrossfadeSettings();`
- L216 _private prototype_ `bool IsReverseTrans(const UAnimStateNodeBase* Node);`
- L218 _protected prototype_ `void CreateBoundGraph();`
- L219 _protected prototype_ `void CreateCustomTransitionGraph();`
- L222 _public function_ `UEdGraph* GetCustomTransitionGraph() const`
- L225 _public prototype_ `bool ValidateBlendProfile();` — Validates any currently set blend profile, ensuring it's valid for the current skeleton

### `Source/Editor/AnimGraph/Public/AnimationBlendSpaceSampleGraph.h` (Public)


#### class `UAnimationBlendSpaceSampleGraph`  
`class UAnimationBlendSpaceSampleGraph : public UAnimationGraph`  
_L13-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimationGraph`
- L20 _public member_ `TObjectPtr<UAnimGraphNode_BlendSpaceSampleResult> ResultNode;` — `UPROPERTY()` — Result node within the state's animation graph

### `Source/Editor/AnimGraph/Public/AnimationConduitGraphSchema.h` (Public)


#### class `UAnimationConduitGraphSchema`  
`class UAnimationConduitGraphSchema : public UEdGraphSchema_K2`  
_L12-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema_K2`
- desc: @TODO: Should this derive from AnimationTransitionSchema (with appropriate suppression of state-based queries)
- L17 _private prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;` — UEdGraphSchema interface
- L18 _private function_ `virtual bool CanDuplicateGraph(UEdGraph* InSourceGraph) const override`
- L19 _private prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;`
- L20 _private function_ `virtual bool ShouldAlwaysPurgeOnModification() const override`
- L21 _private prototype_ `virtual void HandleGraphBeingDeleted(UEdGraph& GraphBeingRemoved) const override;`
- L25 _private function_ `virtual bool DoesSupportCollapsedNodes() const override` — UEdGraphSchema_K2 interface
- L26 _private function_ `virtual bool DoesSupportEventDispatcher() const override`

### `Source/Editor/AnimGraph/Public/AnimationCustomTransitionGraph.h` (Public)


#### class `UAnimationCustomTransitionGraph`  
`class UAnimationCustomTransitionGraph : public UAnimationGraph`  
_L11-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimationGraph`
- L17 _private member_ `TObjectPtr<class UAnimGraphNode_CustomTransitionResult> MyResultNode;` — `UPROPERTY()` — Result node within the state's animation graph
- L20 _private prototype_ `class UAnimGraphNode_CustomTransitionResult* GetResultNode();` — @TODO: Document

### `Source/Editor/AnimGraph/Public/AnimationCustomTransitionSchema.h` (Public)


#### class `UAnimationCustomTransitionSchema`  
`class UAnimationCustomTransitionSchema : public UAnimationGraphSchema`  
_L11-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimationGraphSchema`
- L16 _private prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L17 _private prototype_ `void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;`
- L18 _private prototype_ `virtual void HandleGraphBeingDeleted(UEdGraph& GraphBeingRemoved) const override;`

### `Source/Editor/AnimGraph/Public/AnimationGraph.h` (Public)


#### class `UAnimationGraph`  
`class UAnimationGraph : public UEdGraph`  
_L20-41_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UEdGraph`
- L25 _private member_ `FOnPinDefaultValueChanged OnPinDefaultValueChanged;` — Delegate fired when a pin's default value is changed
- L29 _private member_ `FAnimGraphBlendOptions BlendOptions;` — `UPROPERTY(EditAnywhere, Category = GraphBlending, meta = (ShowOnlyInnerProperties))` — Blending options for animation graphs in Linked Animation Blueprints.
- L33 _private prototype_ `void GetGraphNodesOfClass(TSubclassOf<UAnimGraphNode_Base> NodeClass, TArray<UAnimGraphNode_Base*>& GraphNodes, bool bIncludeChildClasses = true);` — `UFUNCTION(BlueprintCallable, Category=AnimationGraph)` — Returns contained graph nodes of the specified (or child) class
- L37 _private prototype_ `virtual void PostEditUndo() override;` — UObject interface
- L40 _private prototype_ `void ReconstructLayerNodes() const;` — Reconstruct layer nodes post-undo

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMGRAPH_API`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPinDefaultValueChanged, UEdGraphPin* ) UCLASS(MinimalAPI, BlueprintType) class UAnimationGraph : public UEdGraph { GENERATED_UCLASS_BODY() FOnPinDefaultValueChanged OnPinDefaultValueChanged; UPROPERTY(EditAnywhere, Category = GraphBlending, meta = (ShowOnlyInnerProperties)) FAnimGraphBlendOptions BlendOptions; UFUNCTION(BlueprintCallable, Category=AnimationGraph) void GetGraphNodesOfClass(TSubclassOf<UAnimGraphNode_Base> NodeClass, TArray<UAnimGraphNode_Base*>& GraphNodes, bool bIncludeChildClasses = true); private:` — Delegate fired when a pin's default value is changed

### `Source/Editor/AnimGraph/Public/AnimationGraphSchema.h` (Public)


#### class `UAnimationGraphSchema`  
`class UAnimationGraphSchema : public UEdGraphSchema_K2`  
_L23-131_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema_K2`
- L28 _private member_ `FString PN_SequenceName;` — `UPROPERTY()` — Common PinNames
- L31 _private member_ `FName NAME_NeverAsPin;` — `UPROPERTY()`
- L34 _private member_ `FName NAME_PinHiddenByDefault;` — `UPROPERTY()`
- L37 _private member_ `FName NAME_PinShownByDefault;` — `UPROPERTY()`
- L40 _private member_ `FName NAME_AlwaysAsPin;` — `UPROPERTY()`
- L43 _private member_ `FName NAME_CustomizeProperty;` — `UPROPERTY()`
- L46 _private member_ `FName NAME_OnEvaluate;` — `UPROPERTY()`
- L49 _private member_ `FName DefaultEvaluationHandlerName;` — `UPROPERTY()`
- L52 _private prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L53 _private prototype_ `virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;`
- L54 _private prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L55 _private prototype_ `virtual void HandleGraphBeingDeleted(UEdGraph& GraphBeingRemoved) const override;`
- L56 _private prototype_ `virtual bool CreateAutomaticConversionNodeAndConnections(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;`
- L57 _private prototype_ `virtual void DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;`
- L58 _private prototype_ `virtual void DroppedAssetsOnNode(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraphNode* Node) const override;`
- L59 _private prototype_ `virtual void DroppedAssetsOnPin(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraphPin* Pin) const override;`
- L60 _private prototype_ `virtual void GetAssetsNodeHoverMessage(const TArray<FAssetData>& Assets, const UEdGraphNode* HoverNode, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L61 _private prototype_ `virtual void GetAssetsPinHoverMessage(const TArray<FAssetData>& Assets, const UEdGraphPin* HoverPin, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L62 _private prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L63 _private prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L64 _private prototype_ `virtual FText GetPinDisplayName(const UEdGraphPin* Pin) const override;`
- L65 _private prototype_ `virtual bool CanDuplicateGraph(UEdGraph* InSourceGraph) const override;`
- L66 _private function_ `virtual bool ShouldAlwaysPurgeOnModification() const override`
- L67 _private prototype_ `virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;`
- L68 _private prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;`
- L69 _private prototype_ `virtual bool CanGraphBeDropped(TSharedPtr<FEdGraphSchemaAction> InAction) const override;`
- L70 _private prototype_ `virtual FReply BeginGraphDragAction(TSharedPtr<FEdGraphSchemaAction> InAction, const FPointerEvent& MouseEvent = FPointerEvent()) const override;`
- L74 _private prototype_ `virtual const FPinConnectionResponse DetermineConnectionResponseOfCompatibleTypedPins(const UEdGraphPin* PinA, const UEdGraphPin* PinB, const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin) const override;`
- L75 _private prototype_ `virtual TOptional<FSearchForAutocastFunctionResults> SearchForAutocastFunction(const FEdGraphPinType& OutputPinType, const FEdGraphPinType& InputPinType) const;`
- L76 _private prototype_ `virtual bool ArePinsCompatible(const UEdGraphPin* PinA, const UEdGraphPin* PinB, const UClass* CallingContext = NULL, bool bIgnoreArray = false) const override;`
- L77 _private function_ `virtual bool DoesSupportCollapsedNodes() const override`
- L78 _private function_ `virtual bool DoesSupportEventDispatcher() const override`
- L79 _private prototype_ `virtual bool DoesSupportAnimNotifyActions() const override;`
- L80 _private prototype_ `virtual void CreateFunctionGraphTerminators(UEdGraph& Graph, UClass* Class) const override;`
- L81 _private prototype_ `virtual bool CanShowDataTooltipForPin(const UEdGraphPin& Pin) const override;`
- L85 _private prototype_ `static void SpawnNodeFromAsset(UAnimationAsset* Asset, const UE::Slate::FDeprecateVector2DParameter& GraphPosition, UEdGraph* Graph, UEdGraphPin* PinIfAvailable);` — Spawn the correct node in the Animation Graph using the given AnimationAsset at the supplied location
- L88 _private prototype_ `static void SpawnRigidBodyNodeFromAsset(UPhysicsAsset* Asset, const UE::Slate::FDeprecateVector2DParameter& GraphPosition, UEdGraph* Graph);` — Spawn a rigid body node if we drop a physics asset on the graph
- L91 _private prototype_ `static void UpdateNodeWithAsset(class UK2Node* K2Node, UAnimationAsset* Asset);` — Update the specified node to a new asset
- L94 _private prototype_ `static void AutoArrangeInterfaceGraph(UEdGraph& Graph);` — Auto-arranges a graph's inputs and outputs. Does nothing to nodes that are not roots or inputs
- L97 _private prototype_ `static bool IsPosePin(const FEdGraphPinType& PinType);` — Checks to see whether the passed-in pin type is a pose pin (local or component space)
- L100 _private prototype_ `static bool IsLocalSpacePosePin(const FEdGraphPinType& PinType);` — Checks to see whether the passed-in pin type is a local space pose pin
- L103 _private prototype_ `static bool IsComponentSpacePosePin(const FEdGraphPinType& PinType);` — Checks to see whether the passed-in pin type is a component space pose pin
- L106 _private prototype_ `static FEdGraphPinType MakeLocalSpacePosePin();` — Makes a local space pose pin type
- L109 _private prototype_ `static FEdGraphPinType MakeComponentSpacePosePin();` — Makes a component space pose pin type
- L112 _private prototype_ `static void ConformAnimGraphToInterface(UBlueprint* InBlueprint, UEdGraph& InGraph, UFunction* InFunction);` — Conforms an anim graph to an interface function
- L115 _private prototype_ `static void ConformAnimLayersByGuid(const UAnimBlueprint* InAnimBlueprint, const FBPInterfaceDescription& CurrentInterfaceDesc);` — Conforms anim layer nodes to an interface desc by GUID
- L118 _private function_ `static FVector2D GetPositionForNewSubInputNode(UEdGraph& InGraph)` — `UE_DEPRECATED(4.24, "Function renamed, please use GetPositionForNewLinkedInputPoseNode")`
- L121 _private prototype_ `static FVector2D GetPositionForNewLinkedInputPoseNode(UEdGraph& InGraph);` — Find a position for a newly created linked input pose
- L124 _private prototype_ `static TSharedPtr<SWidget> MakeBindingWidgetForPin(const TArray<UAnimGraphNode_Base*>& InAnimGraphNodes, FName InPinName, bool bInOnGraphNode, TAttribute<bool> bInIsEnabled);` — Create a binding widget for the specified named pin on the specified anim graph nodes
- L127 _private prototype_ `static void HideUnboundPropertyPins(UAnimGraphNode_LinkedAnimGraphBase* Node);` — Unexpose pins that are unused on a linked anim graph node
- L130 _private prototype_ `static TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter(const UEdGraph* Graph);`

### `Source/Editor/AnimGraph/Public/AnimationStateGraph.h` (Public)


#### class `UAnimationStateGraph`  
`class UAnimationStateGraph : public UAnimationGraph`  
_L11-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimationGraph`
- L17 _private member_ `TObjectPtr<class UAnimGraphNode_StateResult> MyResultNode;` — `UPROPERTY()` — Result node within the state's animation graph
- L19 _private prototype_ `class UAnimGraphNode_StateResult* GetResultNode();`

### `Source/Editor/AnimGraph/Public/AnimationStateGraphSchema.h` (Public)


#### class `UAnimationStateGraphSchema`  
`class UAnimationStateGraphSchema : public UAnimationGraphSchema`  
_L11-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimationGraphSchema`
- L16 _private prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L17 _private prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;`
- L18 _private prototype_ `virtual bool CanDuplicateGraph(UEdGraph* InSourceGraph) const override;`

### `Source/Editor/AnimGraph/Public/AnimationStateMachineGraph.h` (Public)


#### class `UAnimationStateMachineGraph`  
`class UAnimationStateMachineGraph : public UEdGraph`  
_L16-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- L22 _private member_ `TObjectPtr<class UAnimStateEntryNode> EntryNode;` — `UPROPERTY()` — Entry node within the state machine
- L26 _private member_ `TObjectPtr<class UAnimGraphNode_StateMachineBase> OwnerAnimGraphNode;` — `UPROPERTY()` — Parent instance node

### `Source/Editor/AnimGraph/Public/AnimationStateMachineSchema.h` (Public)


#### struct `FEdGraphSchemaAction_NewStateNode`  
`struct FEdGraphSchemaAction_NewStateNode : public FEdGraphSchemaAction`  
_L20-47_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a node to the graph
- L24 _public member_ `TObjectPtr<UEdGraphNode> NodeTemplate;`
- L26 _public function_ `FEdGraphSchemaAction_NewStateNode() : FEdGraphSchemaAction() , NodeTemplate(nullptr)`
- L31 _public function_ `FEdGraphSchemaAction_NewStateNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) , NodeTemplate(nullptr)`
- L36 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L37 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L40 _public function_ `template <typename NodeType> static NodeType* SpawnNodeFromTemplate(class UEdGraph* ParentGraph, NodeType* InTemplateNode, const UE::Slate::FDeprecateVector2DParameter Location = FVector2f(0.0f, 0.0f), bool bSelectNewNode = true)`

#### struct `FEdGraphSchemaAction_NewStateComment`  
`struct FEdGraphSchemaAction_NewStateComment : public FEdGraphSchemaAction`  
_L51-66_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to create new comment
- L55 _public function_ `FEdGraphSchemaAction_NewStateComment() : FEdGraphSchemaAction()`
- L59 _public function_ `FEdGraphSchemaAction_NewStateComment(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L64 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### class `UAnimationStateMachineSchema`  
`class UAnimationStateMachineSchema : public UEdGraphSchema`  
_L70-101_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L74 _private member_ `static const FName PC_Exec;`
- L77 _private prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L78 _private prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L79 _private prototype_ `virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;`
- L80 _private prototype_ `virtual bool CreateAutomaticConversionNodeAndConnections(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;`
- L81 _private prototype_ `virtual bool TryRelinkConnectionTarget(UEdGraphPin* SourcePin, UEdGraphPin* OldTargetPin, UEdGraphPin* NewTargetPin, const TArray<UEdGraphNode*>& InSelectedGraphNodes) const override;`
- L82 _private prototype_ `virtual bool IsConnectionRelinkingAllowed(UEdGraphPin* InPin) const override;`
- L83 _private prototype_ `virtual const FPinConnectionResponse CanRelinkConnectionToPin(const UEdGraphPin* OldSourcePin, const UEdGraphPin* TargetPinCandidate) const override;`
- L84 _private prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L85 _private prototype_ `virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;`
- L86 _private prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L87 _private prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L88 _private prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;`
- L89 _private prototype_ `virtual void DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;`
- L90 _private prototype_ `virtual void DroppedAssetsOnNode(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraphNode* Node) const override;`
- L91 _private prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L92 _private prototype_ `virtual void GetAssetsNodeHoverMessage(const TArray<FAssetData>& Assets, const UEdGraphNode* HoverNode, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L94 _private prototype_ `virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;`
- L95 _private prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotification) const override;`
- L96 _private prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L100 _private prototype_ `static TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter(const UEdGraph* Graph);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/AnimationTransitionGraph.h` (Public)


#### class `UAnimationTransitionGraph`  
`class UAnimationTransitionGraph : public UAnimationGraph`  
_L11-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimationGraph`
- L16 _private member_ `TObjectPtr<class UAnimGraphNode_TransitionResult> MyResultNode;` — `UPROPERTY()`
- L18 _private prototype_ `class UAnimGraphNode_TransitionResult* GetResultNode();`

### `Source/Editor/AnimGraph/Public/AnimationTransitionSchema.h` (Public)


#### class `UAnimationTransitionSchema`  
`class UAnimationTransitionSchema : public UEdGraphSchema_K2`  
_L16-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema_K2`
- desc: This class is the schema for transition rule graphs in animation state machines
- L21 _private prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L22 _private function_ `virtual bool CanDuplicateGraph(UEdGraph* InSourceGraph) const override`
- L23 _private prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;`
- L24 _private function_ `virtual bool ShouldAlwaysPurgeOnModification() const override`
- L25 _private prototype_ `virtual void HandleGraphBeingDeleted(UEdGraph& GraphBeingRemoved) const override;`
- L29 _private function_ `virtual bool DoesSupportCollapsedNodes() const override`
- L30 _private function_ `virtual bool DoesSupportEventDispatcher() const override`
- L34 _private prototype_ `static UAnimStateTransitionNode* GetTransitionNodeFromGraph(const FAnimBlueprintDebugData& DebugData, const UEdGraph* Graph);`
- L36 _private prototype_ `static UAnimStateNode* GetStateNodeFromGraph(const FAnimBlueprintDebugData& DebugData, const UEdGraph* Graph);`

### `Source/Editor/AnimGraph/Public/BlendSpaceGraph.h` (Public)


#### class `UBlendSpaceGraph`  
`class UBlendSpaceGraph : public UEdGraph`  
_L17-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- desc: Dummy graph to hold sub-graphs for blendspaces. Not edited directly.
- L23 _private prototype_ `virtual void PostLoad() override;` — UObject interface
- L28 _public member_ `TObjectPtr<UBlendSpace> BlendSpace;` — `UPROPERTY(VisibleAnywhere, Category="BlendSpace", Instanced, NoClear, meta = (ShowOnlyInnerProperties))` — Blendspace that we wrap

### `Source/Editor/AnimGraph/Public/IAnimBlueprintCompilationBracketContext.h` (Public)


#### class `IAnimBlueprintCompilationBracketContext`  
`class IAnimBlueprintCompilationBracketContext`  
_L11-34_
- desc: Interface passed to start/end compilation delegates
- L14 _public prototype_ `virtual ~IAnimBlueprintCompilationBracketContext() = default;`
- L17 _public function_ `FCompilerResultsLog& GetMessageLog() const` — Get the message log for the current compilation
- L20 _public function_ `const TMap<UAnimGraphNode_Base*, int32>& GetAllocatedAnimNodeIndices() const` — Index of the nodes (must match up with the runtime discovery process of nodes, which runs thru the property chain)
- L23 _public function_ `const TMap<UAnimGraphNode_Base*, FProperty*>& GetAllocatedHandlerPropertiesByNode() const` — Map of anim node indices to node handler properties in sparse class data struct
- L27 _protected prototype_ `virtual FCompilerResultsLog& GetMessageLogImpl() const = 0;` — Get the message log for the current compilation
- L30 _protected prototype_ `virtual const TMap<UAnimGraphNode_Base*, int32>& GetAllocatedAnimNodeIndicesImpl() const = 0;` — Map of anim node properties to original anim graph node
- L33 _protected prototype_ `virtual const TMap<UAnimGraphNode_Base*, FProperty*>& GetAllocatedHandlerPropertiesByNodeImpl() const = 0;` — Map of anim node indices to node handler properties in sparse class data struct

### `Source/Editor/AnimGraph/Public/IAnimBlueprintCompilationContext.h` (Public)


#### class `IAnimBlueprintCompilationContext`  
`class IAnimBlueprintCompilationContext`  
_L25-213_
- desc: Interface to the anim BP compiler context for use while compilation is in progress
- L65 _public prototype_ `virtual ~IAnimBlueprintCompilationContext() = default;`
- L68 _public prototype_ `static TUniquePtr<IAnimBlueprintCompilationContext> Get(FKismetCompilerContext& InKismetCompiler);` — Get a compilation context from a kismet compiler context assuming that it is an FAnimBlueprintCompilerContext
- L72 _public function_ `template <typename NodeType> NodeType* SpawnIntermediateNode(UEdGraphNode* SourceNode, UEdGraph* ParentGraph = nullptr)` — Spawns an intermediate node associated with the source node (for error purposes)
- L79 _public function_ `template <typename FieldType> FieldType* FindClassFProperty(const TCHAR* InFieldPath) const` — Find a property in the currently-compiled class
- L85 _public function_ `void AddPoseLinkMappingRecord(const FPoseLinkMappingRecord& InRecord)` — Adds a pose link mapping record
- L88 _public function_ `void ProcessAnimationNodes(TArray<UAnimGraphNode_Base*>& AnimNodeList)` — Process the passed-in list of nodes
- L91 _public function_ `void PruneIsolatedAnimationNodes(const TArray<UAnimGraphNode_Base*>& RootSet, TArray<UAnimGraphNode_Base*>& GraphNodes)` — Prunes any nodes that aren't reachable via a pose link
- L94 _public function_ `void ExpansionStep(UEdGraph* Graph, bool bAllowUbergraphExpansions)` — Perform an expansion step for the specified graph
- L97 _public function_ `FCompilerResultsLog& GetMessageLog() const` — Get the message log for the current compilation
- L100 _public function_ `bool ValidateGraphIsWellFormed(UEdGraph* Graph) const` — Performs standard validation on the graph (outputs point to inputs, no more than one connection to each input, types match on both ends, etc...)
- L103 _public function_ `int32 GetAllocationIndexOfNode(UAnimGraphNode_Base* VisualAnimNode) const` — Returns the allocation index of the specified node, processing it if it was pending
- L106 _public function_ `const UBlueprint* GetBlueprint() const` — Get the currently-compiled blueprint
- L109 _public function_ `const UAnimBlueprint* GetAnimBlueprint() const` — Get the currently-compiled anim blueprint
- L112 _public function_ `UEdGraph* GetConsolidatedEventGraph() const` — Get the consolidated uber graph during compilation
- L115 _public function_ `void GetLinkedAnimNodes(UAnimGraphNode_Base* InGraphNode, TArray<UAnimGraphNode_Base*>& LinkedAnimNodes) const` — Gets all anim graph nodes that are piped into the provided node (traverses input pins)
- L118 _public function_ `const TMap<UAnimGraphNode_Base*, int32>& GetAllocatedAnimNodeIndices() const` — Index of the nodes (must match up with the runtime discovery process of nodes, which runs thru the property chain)
- L121 _public function_ `const TMap<UAnimGraphNode_Base*, UAnimGraphNode_Base*>& GetSourceNodeToProcessedNodeMap() const` — Map of true source objects (user edited ones) to the cloned ones that are actually compiled
- L124 _public function_ `const TMap<int32, FProperty*>& GetAllocatedPropertiesByIndex() const` — Map of anim node indices to node properties
- L127 _public function_ `const TMap<UAnimGraphNode_Base*, FProperty*>& GetAllocatedPropertiesByNode() const` — Map of anim node indices to node properties
- L130 _public function_ `const TMap<UAnimGraphNode_Base*, FProperty*>& GetAllocatedHandlerPropertiesByNode() const` — Map of anim node indices to node handler properties in sparse class data struct
- L133 _public function_ `void AddAttributesToNode(UAnimGraphNode_Base* InNode, TArrayView<const FName> InAttributes) const` — Add the specified compiled-in attribute uniquely to the specified node
- L136 _public function_ `TArrayView<const FName> GetAttributesFromNode(UAnimGraphNode_Base* InNode) const` — Get the current compiled-in attributes uniquely assigned to the specified node
- L139 _public function_ `bool IsAnimGraphNodeFolded(UAnimGraphNode_Base* InNode) const` — Check whether an anim node participates in constant folding
- L142 _public function_ `const FFoldedPropertyRecord* GetFoldedPropertyRecord(UAnimGraphNode_Base* InNode, FName InPropertyName) const` — Get the folded property record, if any, for the supplied node & named property
- L145 _public function_ `virtual const FStructProperty* GetMutableDataProperty() const` — Get the generated property of the class that mutable data is added to
- L149 _protected prototype_ `virtual void AddPoseLinkMappingRecordImpl(const FPoseLinkMappingRecord& InRecord) = 0;` — Adds a pose link mapping record
- L152 _protected prototype_ `virtual void ProcessAnimationNodesImpl(TArray<UAnimGraphNode_Base*>& AnimNodeList) = 0;` — Process the passed-in list of nodes
- L155 _protected prototype_ `virtual void PruneIsolatedAnimationNodesImpl(const TArray<UAnimGraphNode_Base*>& RootSet, TArray<UAnimGraphNode_Base*>& GraphNodes) = 0;` — Prunes any nodes that aren't reachable via a pose link
- L158 _protected prototype_ `virtual void ExpansionStepImpl(UEdGraph* Graph, bool bAllowUbergraphExpansions) = 0;` — Perform an expansion step for the specified graph
- L161 _protected prototype_ `virtual FCompilerResultsLog& GetMessageLogImpl() const = 0;` — Get the message log for the current compilation
- L164 _protected prototype_ `virtual bool ValidateGraphIsWellFormedImpl(UEdGraph* Graph) const = 0;` — Performs standard validation on the graph (outputs point to inputs, no more than one connection to each input, types match on both ends, etc...)
- L167 _protected prototype_ `virtual int32 GetAllocationIndexOfNodeImpl(UAnimGraphNode_Base* VisualAnimNode) const = 0;` — Returns the allocation index of the specified node, processing it if it was pending
- L170 _protected prototype_ `virtual const UBlueprint* GetBlueprintImpl() const = 0;` — Get the currently-compiled blueprint
- L173 _protected prototype_ `virtual const UAnimBlueprint* GetAnimBlueprintImpl() const = 0;` — Get the currently-compiled anim blueprint
- L176 _protected prototype_ `virtual UEdGraph* GetConsolidatedEventGraphImpl() const = 0;` — Get the consolidated uber graph during compilation
- L179 _protected prototype_ `virtual void GetLinkedAnimNodesImpl(UAnimGraphNode_Base* InGraphNode, TArray<UAnimGraphNode_Base*>& LinkedAnimNodes) const = 0;` — Gets all anim graph nodes that are piped into the provided node (traverses input pins)
- L182 _protected prototype_ `virtual const TMap<UAnimGraphNode_Base*, int32>& GetAllocatedAnimNodeIndicesImpl() const = 0;` — Index of the nodes (must match up with the runtime discovery process of nodes, which runs thru the property chain)
- L185 _protected prototype_ `virtual const TMap<UAnimGraphNode_Base*, UAnimGraphNode_Base*>& GetSourceNodeToProcessedNodeMapImpl() const = 0;` — Map of true source objects (user edited ones) to the cloned ones that are actually compiled
- L188 _protected prototype_ `virtual const TMap<int32, FProperty*>& GetAllocatedPropertiesByIndexImpl() const = 0;` — Map of anim node indices to node properties
- L191 _protected prototype_ `virtual const TMap<UAnimGraphNode_Base*, FProperty*>& GetAllocatedPropertiesByNodeImpl() const = 0;` — Map of anim node indices to node properties
- L194 _protected prototype_ `virtual const TMap<UAnimGraphNode_Base*, FProperty*>& GetAllocatedHandlerPropertiesByNodeImpl() const = 0;` — Map of anim node indices to node handler properties in sparse class data struct
- L197 _protected prototype_ `virtual void AddAttributesToNodeImpl(UAnimGraphNode_Base* InNode, TArrayView<const FName> InAttributes) const = 0;` — Add the specified compiled-in attribute uniquely to the specified node
- L200 _protected prototype_ `virtual TArrayView<const FName> GetAttributesFromNodeImpl(UAnimGraphNode_Base* InNode) const = 0;` — Get the current compiled-in attributes uniquely assigned to the specified node
- L203 _protected prototype_ `virtual bool IsAnimGraphNodeFoldedImpl(UAnimGraphNode_Base* InNode) const = 0;` — Check whether an anim node participates in constant folding
- L206 _protected prototype_ `virtual const FFoldedPropertyRecord* GetFoldedPropertyRecordImpl(UAnimGraphNode_Base* InNode, FName InPropertyName) const = 0;` — Get the folded property record, if any, for the supplied node & named property
- L209 _protected prototype_ `virtual const FStructProperty* GetMutableDataPropertyImpl() const = 0;` — Get the generated property of the class that mutable data is added to
- L212 _protected prototype_ `virtual FKismetCompilerContext* GetKismetCompiler() const = 0;` — Get the compiler as a base class to avoid circular include issues with templated functions/classes

#### struct `IAnimBlueprintCompilationContext::FFoldedPropertyRecord`  
`struct FFoldedPropertyRecord`  
_L29-63_
- desc: Record of a property that can be folded into the class members/constant blocks
- L31 _public function_ `FFoldedPropertyRecord(UAnimGraphNode_Base* InAnimGraphNode, FStructProperty* InAnimNodeProperty, FProperty* InProperty, bool bInIsOnClass) : AnimGraphNode(InAnimGraphNode) , AnimNodeProperty(InAnimNodeProperty) , Property(InProperty) , GeneratedProperty(nullptr) , FoldIndex(INDEX_NONE) , PropertyIndex(INDEX_NONE) , bIsOnClass(bInIsOnClass)`
- L43 _public member_ `UAnimGraphNode_Base* AnimGraphNode = nullptr;` — The anim graph node that this property record came from
- L46 _public member_ `FStructProperty* AnimNodeProperty = nullptr;` — The property of the FAnimNode_Base-derived structure within the anim graph node
- L49 _public member_ `FProperty* Property = nullptr;` — The original property within the FAnimNode_Base
- L52 _public member_ `FProperty* GeneratedProperty = nullptr;` — The generated property within the respective data area (either constants or mutables)
- L55 _public member_ `int32 FoldIndex = INDEX_NONE;` — The index that this property was folded to. INDEX_NONE if it was not folded.
- L59 _public member_ `int32 PropertyIndex = INDEX_NONE;` — The index of the property in its respective data area (either constant or mutable) This will be INDEX_NONE if the property was folded.
- L62 _public member_ `bool bIsOnClass = false;` — Whether this property will be held on the class (constants on sparse class data), or on the instance (mutables struct)

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ANIMGRAPH_API`
- L22 _macro_ `#define ANIM_FUNC_DECORATOR TEXT("__AnimFunc")`

### `Source/Editor/AnimGraph/Public/IAnimBlueprintCompilerCreationContext.h` (Public)


#### class `IAnimBlueprintCompilerCreationContext`  
`class IAnimBlueprintCompilerCreationContext`  
_L11-18_
- desc: Interface to the creation of an anim BP compiler context
- L14 _public prototype_ `virtual ~IAnimBlueprintCompilerCreationContext() = default;`
- L17 _public prototype_ `virtual void RegisterKnownGraphSchema(TSubclassOf<UEdGraphSchema> InGraphSchemaClass) = 0;` — Registers a graphs schema class to the anim BP compiler so that default function processing is not performed on it

### `Source/Editor/AnimGraph/Public/IAnimBlueprintCopyTermDefaultsContext.h` (Public)


#### class `IAnimBlueprintCopyTermDefaultsContext`  
`class IAnimBlueprintCopyTermDefaultsContext`  
_L12-29_
- desc: Interface passed to CopyTermDefaults delegate
- L15 _public prototype_ `virtual ~IAnimBlueprintCopyTermDefaultsContext() = default;`
- L18 _public function_ `FCompilerResultsLog& GetMessageLog() const` — Get the message log for the current compilation
- L21 _public function_ `const UAnimBlueprint* GetAnimBlueprint() const` — Get the currently-compiled anim blueprint
- L25 _protected prototype_ `virtual FCompilerResultsLog& GetMessageLogImpl() const = 0;` — Get the message log for the current compilation
- L28 _protected prototype_ `virtual const UAnimBlueprint* GetAnimBlueprintImpl() const = 0;` — Get the currently-compiled anim blueprint

#### class `IAnimBlueprintNodeCopyTermDefaultsContext`  
`class IAnimBlueprintNodeCopyTermDefaultsContext`  
_L33-86_
- desc: Interface passed to per-node CopyTermDefaults override point
- L36 _public prototype_ `virtual ~IAnimBlueprintNodeCopyTermDefaultsContext() = default;`
- L39 _public function_ `UObject* GetClassDefaultObject() const` — Get the CDO that we are writing to
- L42 _public function_ `const FProperty* GetTargetProperty() const` — Get the property that we are writing to
- L45 _public function_ `uint8* GetDestinationPtr() const` — Get the destination ptr (the node) that we are writing to
- L48 _public function_ `const uint8* GetSourcePtr() const` — Get the source ptr (the node in the anim graph node) that we are reading from
- L51 _public function_ `int32 GetNodePropertyIndex() const` — Get the property index for this node
- L55 _public function_ `template <typename NodeType> const NodeType& GetSourceNode() const` — Get the source node cast to the correct type
- L64 _public function_ `template <typename NodeType> NodeType& GetDestinationNode() const` — Get the destination node cast to the correct type
- L73 _protected prototype_ `virtual UObject* GetClassDefaultObjectImpl() const = 0;` — Get the CDO that we are writing to
- L76 _protected prototype_ `virtual const FProperty* GetTargetPropertyImpl() const = 0;` — Get the property that we are writing to
- L79 _protected prototype_ `virtual uint8* GetDestinationPtrImpl() const = 0;` — Get the destination ptr (the node) that we are writing to
- L82 _protected prototype_ `virtual const uint8* GetSourcePtrImpl() const = 0;` — Get the source ptr (the node in the anim graph node) that we are reading from
- L85 _protected prototype_ `virtual int32 GetNodePropertyIndexImpl() const = 0;` — Get the property index for this node

#### class `IAnimBlueprintExtensionCopyTermDefaultsContext`  
`class IAnimBlueprintExtensionCopyTermDefaultsContext`  
_L89-124_
- desc: Interface passed to per-extension CopyTermDefaults override point
- L92 _public prototype_ `virtual ~IAnimBlueprintExtensionCopyTermDefaultsContext() = default;`
- L95 _public function_ `UObject* GetClassDefaultObject() const` — Get the CDO that we are writing to
- L98 _public function_ `const FProperty* GetTargetProperty() const` — Get the property that we are writing to
- L101 _public function_ `uint8* GetDestinationPtr() const` — Get the destination ptr (the node) that we are writing to
- L104 _public function_ `const uint8* GetSourcePtr() const` — Get the source ptr (the node in the anim graph node) that we are reading from
- L107 _public function_ `int32 GetNodePropertyIndex() const` — Get the property index for this node
- L111 _protected prototype_ `virtual UObject* GetClassDefaultObjectImpl() const = 0;` — Get the CDO that we are writing to
- L114 _protected prototype_ `virtual const FProperty* GetTargetPropertyImpl() const = 0;` — Get the property that we are writing to
- L117 _protected prototype_ `virtual uint8* GetDestinationPtrImpl() const = 0;` — Get the destination ptr (the node) that we are writing to
- L120 _protected prototype_ `virtual const uint8* GetSourcePtrImpl() const = 0;` — Get the source ptr (the node in the anim graph node) that we are reading from
- L123 _protected prototype_ `virtual int32 GetNodePropertyIndexImpl() const = 0;` — Get the property index for this node

### `Source/Editor/AnimGraph/Public/IAnimBlueprintGeneratedClassCompiledData.h` (Public)


#### class `IAnimBlueprintGeneratedClassCompiledData`  
`class IAnimBlueprintGeneratedClassCompiledData`  
_L16-44_
- desc: Interface to the writable parts of the generated class that handlers can operate on
- L20 _public prototype_ `virtual TArray<FBakedAnimationStateMachine>& GetBakedStateMachines() const = 0;` — Get the baked state machines data for the currently-compiled class
- L23 _public prototype_ `virtual TMap<FName, FCachedPoseIndices>& GetOrderedSavedPoseIndicesMap() const = 0;` — Get the saved pose indices map data for the currently-compiled class
- L26 _public prototype_ `virtual FBlueprintDebugData& GetBlueprintDebugData() const = 0;` — Get the debug data for the currently-compiled class
- L29 _public prototype_ `virtual TArray<FAnimNotifyEvent>& GetAnimNotifies() const = 0;` — Get the currently-compiled classes anim notifies
- L32 _public prototype_ `virtual int32 FindOrAddNotify(FAnimNotifyEvent& Notify) const = 0;` — Finds a notify event or adds if it doesn't already exist
- L35 _public prototype_ `virtual FAnimBlueprintDebugData& GetAnimBlueprintDebugData() const = 0;` — Get the anim debug data for the currently-compiled class
- L38 _public prototype_ `virtual TMap<FName, FGraphAssetPlayerInformation>& GetGraphAssetPlayerInformation() const = 0;` — Get the currently-compiled classes graph asset player information
- L43 _public prototype_ `virtual UBlendSpace* AddBlendSpace(UBlendSpace* InSourceBlendSpace) = 0;` — Add a class-internal blendspace @param	InSourceBlendSpace	The blendspace to duplicate @return a duplicate of the blendspace outered to the class

### `Source/Editor/AnimGraph/Public/IAnimBlueprintNodeOverrideAssetsContext.h` (Public)


#### class `IAnimBlueprintNodeOverrideAssetsContext`  
`class IAnimBlueprintNodeOverrideAssetsContext`  
_L11-36_
- desc: Interface passed to per-node OverrideAssets override point
- L14 _public prototype_ `virtual ~IAnimBlueprintNodeOverrideAssetsContext() = default;`
- L18 _public function_ `template<typename AnimNodeType> AnimNodeType& GetAnimNode() const` — Get the anim node to override
- L25 _public function_ `TArrayView<UObject* const> GetAssets() const` — Get all of the assets to override with
- L29 _protected prototype_ `virtual FAnimNode_Base* GetAnimNodeImpl() const = 0;` — Get the anim node to override
- L32 _protected prototype_ `virtual UScriptStruct* GetAnimNodeTypeImpl() const = 0;` — Get the type of the anim node to override
- L35 _protected prototype_ `virtual TArrayView<UObject* const> GetAssetsImpl() const = 0;` — Get all of the assets to override with

### `Source/Editor/AnimGraph/Public/IAnimBlueprintPostExpansionStepContext.h` (Public)


#### class `IAnimBlueprintPostExpansionStepContext`  
`class IAnimBlueprintPostExpansionStepContext`  
_L13-41_
- desc: Interface passed to PostExpansionStep delegate
- L16 _public prototype_ `virtual ~IAnimBlueprintPostExpansionStepContext() = default;`
- L19 _public function_ `FCompilerResultsLog& GetMessageLog() const` — Get the message log for the current compilation
- L22 _public function_ `const TMap<UAnimGraphNode_Base*, int32>& GetAllocatedAnimNodeIndices() const` — Index of the nodes (must match up with the runtime discovery process of nodes, which runs thru the property chain)
- L25 _public function_ `UEdGraph* GetConsolidatedEventGraph() const` — Get the consolidated uber graph during compilation
- L28 _public function_ `const FKismetCompilerOptions& GetCompileOptions() const` — Get the compiler options we are currently using
- L32 _protected prototype_ `virtual FCompilerResultsLog& GetMessageLogImpl() const = 0;` — Get the message log for the current compilation
- L34 _protected prototype_ `virtual const TMap<UAnimGraphNode_Base*, int32>& GetAllocatedAnimNodeIndicesImpl() const = 0;`
- L37 _protected prototype_ `virtual UEdGraph* GetConsolidatedEventGraphImpl() const = 0;` — Get the consolidated uber graph during compilation
- L40 _protected prototype_ `virtual const FKismetCompilerOptions& GetCompileOptionsImpl() const = 0;` — Get the compiler options we are currently using

### `Source/Editor/AnimGraph/Public/IAnimGraph_SequencerMixerTargetConnector.h` (Public)


#### class `IAnimGraph_SequencerMixerTargetConnector`  
`class IAnimGraph_SequencerMixerTargetConnector : public IModularFeature`  
_L10-32_
- inherits: `IModularFeature`
- L14 _public function_ `static FName GetModularFeatureName()`
- L20 _public function_ `static const IAnimGraph_SequencerMixerTargetConnector* Get()`
- L29 _public prototype_ `virtual ~IAnimGraph_SequencerMixerTargetConnector() = default;`
- L31 _public prototype_ `virtual void GetSequencerMixerTargetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const = 0;`

### `Source/Editor/AnimGraph/Public/IAnimNodeEditMode.h` (Public)


#### class `IAnimNodeEditMode`  
`class IAnimNodeEditMode : public FAnimationEditMode`  
_L13-51_
- inherits: `FAnimationEditMode`
- desc: Base interface for skeletal control edit modes
- L17 _public prototype_ `virtual ECoordSystem GetWidgetCoordinateSystem() const = 0;` — Returns the coordinate system that should be used for this bone
- L20 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const = 0;` — @return current widget mode this anim graph node supports
- L23 _public prototype_ `virtual UE::Widget::EWidgetMode ChangeToNextWidgetMode(UE::Widget::EWidgetMode CurWidgetMode) = 0;` — Called when the user changed widget mode by pressing "Space" key
- L26 _public prototype_ `virtual bool SetWidgetMode(UE::Widget::EWidgetMode InWidgetMode) = 0;` — Called when the user set widget mode directly, returns true if InWidgetMode is available
- L29 _public prototype_ `virtual FName GetSelectedBone() const = 0;` — Get the bone that the skeletal control is manipulating
- L32 _public prototype_ `virtual void DoTranslation(FVector& InTranslation) = 0;` — Called when the widget is dragged in translation mode
- L35 _public prototype_ `virtual void DoRotation(FRotator& InRotation) = 0;` — Called when the widget is dragged in rotation mode
- L38 _public prototype_ `virtual void DoScale(FVector& InScale) = 0;` — Called when the widget is dragged in scale mode
- L41 _public prototype_ `virtual void EnterMode(UAnimGraphNode_Base* InEditorNode, FAnimNode_Base* InRuntimeNode) = 0;` — Called when entering this edit mode
- L44 _public prototype_ `virtual void ExitMode() = 0;` — Called when exiting this edit mode
- L47 _public prototype_ `virtual bool SupportsPoseWatch() = 0;` — Called to determine whether this edit mode should be drawn when nodes edited by this edit mode are pose watched
- L50 _public prototype_ `virtual void RegisterPoseWatchedNode(UAnimGraphNode_Base* InEditorNode, FAnimNode_Base* InRuntimeNode) = 0;` — Called when a Pose Watch is created on a node edited by this edit mode

### `Source/Editor/AnimGraph/Public/IClassVariableCreator.h` (Public)


#### class `IAnimBlueprintVariableCreationContext`  
`class IAnimBlueprintVariableCreationContext`  
_L15-23_
- desc: Context passed to IClassVariableCreator::CreateClassVariablesFromBlueprint
- L19 _public prototype_ `virtual FProperty* CreateVariable(const FName Name, const FEdGraphPinType& Type) = 0;` — Create a class variable in the current class. Note that no name confick resolution is performed, if a unique name is needed, use CreateUniqueVariable
- L22 _public prototype_ `virtual FProperty* CreateUniqueVariable(UObject* InForObject, const FEdGraphPinType& Type) = 0;` — Create a uniquely named variable corresponding to an object in the current class.

#### class `UClassVariableCreator`  
`class UClassVariableCreator : public UInterface`  
_L26-29_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IClassVariableCreator`  
`class IClassVariableCreator`  
_L31-42_
- L41 _public prototype_ `virtual void CreateClassVariablesFromBlueprint(IAnimBlueprintVariableCreationContext& InCreationContext) = 0;` — Implement this in a graph node and the anim BP compiler will call this expecting to generate class variables. @param	InVariableCreator	The variable creation context for the current BP compilation

### `Source/Editor/AnimGraph/Public/K2Node_AnimGetter.h` (Public)


#### struct `FNodeSpawnData`  
`struct FNodeSpawnData`  
_L30-63_
- reflection: `USTRUCT()`
- L34 _public prototype_ `FNodeSpawnData();`
- L38 _public member_ `FText CachedTitle;` — `UPROPERTY()` — Title to use for the spawned node
- L42 _public member_ `TObjectPtr<UAnimGraphNode_Base> SourceNode;` — `UPROPERTY()` — The node the spawned getter accesses, if any
- L46 _public member_ `TObjectPtr<UAnimStateNodeBase> SourceStateNode;` — `UPROPERTY()` — The state node the spawned getter accesses
- L50 _public member_ `TObjectPtr<UClass> AnimInstanceClass;` — `UPROPERTY()` — The instance class the spawned getter is defined on
- L54 _public member_ `TObjectPtr<const UAnimBlueprint> SourceBlueprint;` — `UPROPERTY()` — The blueprint the getter is valid within
- L58 _public member_ `TObjectPtr<UField> Getter;` — `UPROPERTY()` — The UFunction (as a UField)
- L62 _public member_ `FString GetterContextString;` — `UPROPERTY()` — String of combined valid contexts for the spawned getter

#### class `UK2Node_AnimGetter`  
`class UK2Node_AnimGetter : public UK2Node_CallFunction`  
_L66-153_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction`
- L72 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L73 _public prototype_ `virtual void PostPasteNode() override;`
- L74 _public prototype_ `virtual void PostLoad() override;`
- L75 _public prototype_ `virtual void BeginDestroy() override;`
- L79 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L80 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L81 _public prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;`
- L82 _public prototype_ `virtual bool IsActionFilteredOut(FBlueprintActionFilter const& Filter) override;`
- L83 _public prototype_ `virtual void PostPlacedNewNode();`
- L87 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L88 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L93 _public member_ `TObjectPtr<UAnimGraphNode_Base> SourceNode;` — `UPROPERTY()` — The node that is required for the getter
- L98 _public member_ `TObjectPtr<UAnimStateNodeBase> SourceStateNode;` — `UPROPERTY()` — UAnimStateNode doesn't use the same hierarchy so we need to have a seperate property here to handle those.
- L102 _public member_ `TObjectPtr<UClass> GetterClass;` — `UPROPERTY()` — The UAnimInstance derived class that implements the getter we are running
- L106 _public member_ `TObjectPtr<const UAnimBlueprint> SourceAnimBlueprint;` — `UPROPERTY()` — The anim blueprint that generated this getter
- L110 _public member_ `FText CachedTitle;` — `UPROPERTY()` — Cached node title
- L114 _public member_ `TArray<FString> Contexts;` — `UPROPERTY()` — List of valid contexts for the node
- L121 _protected prototype_ `void RestoreStateMachineState();` — Fixes the SourceStateNode to be the state of the node's owner
- L124 _protected prototype_ `void RestoreStateMachineNode();` — Fixes the SourceNode to be the state machine owner of SourceStateNode (if it is not null)
- L127 _protected prototype_ `static bool GetterRequiresParameter(const UFunction* Getter, FString ParamName);` — Returns whether or not the provided UFunction requires the named parameter
- L130 _protected prototype_ `bool IsContextValidForSchema(const UEdGraphSchema* Schema) const;` — Checks the cached context strings to make sure this getter is valid within the provided schema
- L133 _protected prototype_ `void PostSpawnNodeSetup(UEdGraphNode* NewNode, bool bIsTemplateNode, FNodeSpawnData SpawnData);` — Passed to blueprint spawners to configure spawned nodes
- L136 _protected prototype_ `void UpdateCachedTitle();` — Recache the title, used if the source node or source state changes
- L139 _protected prototype_ `static void UpdateCachedTitle(FNodeSpawnData& SpawnData);` — Sets CachedTitle for a new node to be created
- L142 _protected prototype_ `static FText GenerateTitle(UFunction* Getter, UAnimStateNodeBase* SourceStateNode, UAnimGraphNode_Base* SourceNode);` — Generates a title for the node based on its function and the context it is in
- L145 _protected function_ `virtual bool CanToggleNodePurity() const override` — UK2Node_CallFunction interface
- L148 _protected prototype_ `virtual void RegisterDelegates();`
- L149 _protected prototype_ `virtual void UnregisterDelegates();`
- L152 _private member_ `FDelegateHandle GraphRenameHandle;`

### `Source/Editor/AnimGraph/Public/K2Node_AnimNodeReference.h` (Public)


#### class `UK2Node_AnimNodeReference`  
`class UK2Node_AnimNodeReference : public UK2Node`  
_L26-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L32 _public prototype_ `FText GetLabelText() const;` — Get the text used for the node's label
- L35 _public function_ `FName GetTag() const` — Get the tag for this node, if any
- L38 _public function_ `void SetTag(FName InTag)` — Set the tag for this node
- L42 _private member_ `FName Tag;` — `UPROPERTY()` — The node tag we reference
- L45 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L46 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L47 _private prototype_ `virtual void AddSearchMetaDataInfo(TArray<FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L48 _private prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* TargetGraph) const override;`
- L51 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;` — UK2Node interface
- L52 _private function_ `virtual bool IsNodePure() const override`
- L53 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L54 _private prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L55 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L56 _private function_ `virtual bool DrawNodeAsVariable() const override`
- L57 _private prototype_ `virtual FText GetTooltipText() const override;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API ANIMGRAPH_API`

### `Source/Editor/AnimGraph/Public/K2Node_PlayMontage.h` (Public)


#### class `UK2Node_PlayMontage`  
`class UK2Node_PlayMontage : public UK2Node_BaseAsyncTask`  
_L19-32_
- reflection: `UCLASS()`
- inherits: `UK2Node_BaseAsyncTask`
- L24 _private prototype_ `virtual FText GetTooltipText() const override;`
- L25 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;`
- L30 _private prototype_ `virtual FText GetMenuCategory() const override;`

### `Source/Editor/AnimGraph/Public/K2Node_TransitionRuleGetter.h` (Public)


#### enum `ETransitionGetter::Type`  
`enum Type : int`  
_L29-40_
- L31 _public enumerator_ `AnimationAsset_GetCurrentTime`
- L32 _public enumerator_ `AnimationAsset_GetLength`
- L33 _public enumerator_ `AnimationAsset_GetCurrentTimeFraction`
- L34 _public enumerator_ `AnimationAsset_GetTimeFromEnd`
- L35 _public enumerator_ `AnimationAsset_GetTimeFromEndFraction`
- L36 _public enumerator_ `CurrentState_ElapsedTime`
- L37 _public enumerator_ `CurrentState_GetBlendWeight`
- L38 _public enumerator_ `CurrentTransitionDuration`
- L39 _public enumerator_ `ArbitraryState_GetBlendWeight`

#### class `UK2Node_TransitionRuleGetter`  
`class UK2Node_TransitionRuleGetter : public UK2Node`  
_L45-91_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L50 _private member_ `TEnumAsByte<ETransitionGetter::Type> GetterType;` — `UPROPERTY()`
- L53 _private member_ `TObjectPtr<UAnimGraphNode_Base> AssociatedAnimAssetPlayerNode;` — `UPROPERTY()`
- L56 _private member_ `TObjectPtr<UAnimStateNode> AssociatedStateNode;` — `UPROPERTY()`
- L59 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L60 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L61 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L62 _private prototype_ `virtual FText GetTooltipText() const override;`
- L63 _private function_ `virtual bool ShowPaletteIconOnNode() const override`
- L64 _private prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;`
- L65 _private prototype_ `virtual bool IsActionFilteredOut(FBlueprintActionFilter const& Filter) override;`
- L69 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L70 _private function_ `virtual bool IsNodePure() const override`
- L74 _private prototype_ `UEdGraphPin* GetOutputPin() const;` — @todo document
- L77 _private prototype_ `static FText GetFriendlyName(ETransitionGetter::Type TypeID);` — @todo document
- L81 _private prototype_ `void GetStateSpecificAnimGraphSchemaMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar, const UAnimBlueprint* AnimBlueprint, UAnimStateNode* StateNode) const;` — Helper function for GetStateSpecificMenuActions, finds actions for AnimBlueprint states that can be used in AnimGraphSchema graphs
- L84 _private prototype_ `void GetStateSpecificAnimTransitionSchemaMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar, const UAnimBlueprint* AnimBlueprint, UAnimStateNode* StateNode) const;` — Helper function for GetStateSpecificMenuActions, finds actions for AnimBlueprint states that can be used in AnimTransitionSchema graphs
- L87 _private prototype_ `void GetStateSpecificMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar, const UAnimBlueprint* AnimBlueprint) const;` — Helper function for GetMenuActions, goes through all states in an AnimBlueprint and finds possible actions
- L90 _private prototype_ `void GetNonStateSpecificMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const;` — Helper function for GetMenuActions, generates non-state specific actions that use this node

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace ETransitionGetter`
