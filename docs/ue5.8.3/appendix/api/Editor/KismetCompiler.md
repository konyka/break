# Editor / KismetCompiler

- module root: `Source/Editor/KismetCompiler`
- headers: 11; symbols: 512
- symbol kinds: class=11, delegate=2, enum=9, enumerator=70, function=83, macro=5, member=130, namespace=4, prototype=186, struct=9, typedef=3
- PrivateDependencyModuleNames: AnimGraph, BlueprintGraph, Core, CoreUObject, EditorFramework, Engine, FieldNotification, InputCore, Kismet, MessageLog, MovieScene, MovieSceneTools, ScriptDisassembler, UnrealEd

### `Source/Editor/KismetCompiler/Internal/BlueprintClassFlagUtils.h` (Internal)


#### class `FBlueprintClassFlagUtils`  
`class FBlueprintClassFlagUtils`  
_L12-23_
- desc: Utility functions for ClassFlags that is reused between normal and skeleton-only compilation.
- L16 _public prototype_ `static void PropagateParentClassFlags_CompileClassLayout(UClass* Class);` — Given a class, let it inherit class flags from its parent class. Only considers inheritable flags.
- L19 _public prototype_ `static void PropagateParentClassFlags_FinishCompilingClass(UClass* Class);` — Given a class, let it inherit class flags from its parent class. Only considers inheritable flags.
- L22 _public prototype_ `static void AppendPropertyBasedClassFlags(UClass* Class);` — Given a class, set any class flags that are based on its properties. Does not consider parent class properties.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API KISMETCOMPILER_API`

### `Source/Editor/KismetCompiler/Private/KismetCompilerBackend.h` (Private)


#### class `IKismetCompilerBackend`  
`class IKismetCompilerBackend`  
_L12-14_

#### class `FKismetCompilerVMBackend`  
`class FKismetCompilerVMBackend : public IKismetCompilerBackend`  
_L19-45_
- inherits: `IKismetCompilerBackend`
- L22 _public typedef_ `typedef TMap<FBlueprintCompiledStatement*, CodeSkipSizeType> TStatementToSkipSizeMap;`
- L25 _protected member_ `UBlueprint* Blueprint;`
- L26 _protected member_ `UEdGraphSchema_K2* Schema;`
- L27 _protected member_ `FCompilerResultsLog& MessageLog;`
- L28 _protected member_ `FKismetCompilerContext& CompilerContext;`
- L30 _protected member_ `TStatementToSkipSizeMap UbergraphStatementLabelMap;`
- L32 _public function_ `FKismetCompilerVMBackend(UBlueprint* InBlueprint, UEdGraphSchema_K2* InSchema, FKismetCompilerContext& InContext) : Blueprint(InBlueprint) , Schema(InSchema) , MessageLog(InContext.MessageLog) , CompilerContext(InContext)`
- L40 _public prototype_ `void GenerateCodeFromClass(UClass* SourceClass, TIndirectArray<FKismetFunctionContext>& Functions, bool bGenerateStubsOnly=false);`
- L44 _protected prototype_ `void ConstructFunction(FKismetFunctionContext& FunctionContext, bool bIsUbergraph, bool bGenerateStubOnly);` — Builds both the header declaration and body implementation of a function

### `Source/Editor/KismetCompiler/Public/BPTerminal.h` (Public)


#### struct `FBPTerminal`  
`struct FBPTerminal`  
_L15-155_
- desc: A terminal in the graph (literal or variable reference)
- L17 _public member_ `FString Name;`
- L18 _public member_ `FEdGraphPinType Type;`
- L19 _public member_ `bool bIsLiteral;`
- L20 _public member_ `bool bIsConst;`
- L21 _public member_ `bool bIsSavePersistent;`
- L22 _public member_ `bool bPassedByReference;`
- L25 _public member_ `UObject* Source;` — Source node
- L28 _public member_ `UEdGraphPin* SourcePin;` — Source pin
- L31 _public member_ `FBPTerminal* Context;` — Context->
- L34 _public member_ `FProperty* AssociatedVarProperty;` — For non-literal terms, this is the FProperty being referenced (in the stack if bIsLocal set, or on the context otherwise)
- L37 _public member_ `TObjectPtr<UObject> ObjectLiteral;` — Pointer to an object literal
- L40 _public member_ `FText TextLiteral;` — The FText literal
- L43 _public member_ `FString PropertyDefault;` — String representation of the default value of the property associated with this term (or path to object)
- L46 _public member_ `FBlueprintCompiledStatement* InlineGeneratedParameter;` — Used for MathExpression optimization. The parameter will be filled directly by a result of a function called inline. No local variable is necessary to pass the value.
- L48 _public function_ `FBPTerminal() : bIsLiteral(false) , bIsConst(false) , bIsSavePersistent(false) , bPassedByReference(false) , Source(nullptr) , SourcePin(nullptr) , Context(nullptr) , AssociatedVarProperty(nullptr) , ObjectLiteral(nullptr) , InlineGeneratedParameter(nullptr) , VarType(EVarType_Instanced) , ContextType(EContextType_Object)`
- L64 _public prototype_ `void CopyFromPin(UEdGraphPin* Net, FString NewName);`
- L65 _public function_ `void CopyFromPin(UEdGraphPin* Net, const FName NewName)`
- L67 _public function_ `bool IsTermWritable() const`
- L72 _public function_ `bool IsLocalVarTerm() const`
- L77 _public function_ `void SetVarTypeLocal(bool bIsLocal = true)`
- L82 _public function_ `bool IsSparseClassDataVarTerm() const`
- L87 _public function_ `void SetVarTypeSparseClassData()`
- L92 _public function_ `bool IsDefaultVarTerm() const`
- L97 _public function_ `void SetVarTypeDefault(bool bIsDefault = true)`
- L102 _public function_ `bool IsInstancedVarTerm() const`
- L107 _public function_ `bool IsClassContextType() const`
- L112 _public function_ `void SetContextTypeClass(bool bIsClassContext = true)`
- L117 _public function_ `bool IsStructContextType() const`
- L122 _public function_ `void SetContextTypeStruct(bool bIsStructContext = true)`
- L127 _public function_ `bool IsObjectContextType() const`
- L143 _private member_ `EVarType VarType;` — For non-literal terms, this is set to the type of variable reference
- L154 _private member_ `EContextType ContextType;` — If this term is also a context, this indicates which type of context it is

#### enum `FBPTerminal::EVarType`  
`enum EVarType`  
_L134-140_
- desc: Variable reference types (mutually-exclusive)
- L136 _public enumerator_ `EVarType_Local`
- L137 _public enumerator_ `EVarType_Default`
- L138 _public enumerator_ `EVarType_Instanced`
- L139 _public enumerator_ `EVarType_SparseClassData`

#### enum `FBPTerminal::EContextType`  
`enum EContextType`  
_L146-151_
- desc: Context types (mutually-exclusive)
- L148 _public enumerator_ `EContextType_Class`
- L149 _public enumerator_ `EContextType_Struct`
- L150 _public enumerator_ `EContextType_Object`

### `Source/Editor/KismetCompiler/Public/BlueprintCompiledStatement.h` (Public)


#### enum `EKismetCompiledStatementType`  
`enum EKismetCompiledStatementType`  
_L10-101_
- L12 _public enumerator_ `KCST_Nop = 0`
- L14 _public enumerator_ `KCST_CallFunction = 1` — [wiring =] TargetObject->FunctionToCall(wiring)
- L16 _public enumerator_ `KCST_Assignment = 2` — TargetObject->TargetProperty = [wiring]
- L18 _public enumerator_ `KCST_CompileError = 3` — One of the other types with a compilation error during statement generation
- L20 _public enumerator_ `KCST_UnconditionalGoto = 4` — goto TargetLabel
- L22 _public enumerator_ `KCST_PushState = 5` — FlowStack.Push(TargetLabel)
- L24 _public enumerator_ `KCST_GotoIfNot = 6` — [if (!TargetObject->TargetProperty)] goto TargetLabel
- L26 _public enumerator_ `KCST_Return = 7` — return TargetObject->TargetProperty
- L28 _public enumerator_ `KCST_EndOfThread = 8` — if (FlowStack.Num()) { NextState = FlowStack.Pop; } else { return; }
- L30 _public enumerator_ `KCST_Comment = 9` — Comment
- L32 _public enumerator_ `KCST_ComputedGoto = 10` — NextState = LHS;
- L34 _public enumerator_ `KCST_EndOfThreadIfNot = 11` — [if (!TargetObject->TargetProperty)] { same as KCST_EndOfThread; }
- L36 _public enumerator_ `KCST_DebugSite = 12` — NOP with recorded address
- L38 _public enumerator_ `KCST_CastObjToInterface = 13` — TargetInterface(TargetObject)
- L40 _public enumerator_ `KCST_DynamicCast = 14` — Cast<TargetClass>(TargetObject)
- L42 _public enumerator_ `KCST_ObjectToBool = 15` — (TargetObject != None)
- L44 _public enumerator_ `KCST_AddMulticastDelegate = 16` — TargetDelegate->Add(EventDelegate)
- L46 _public enumerator_ `KCST_ClearMulticastDelegate = 17` — TargetDelegate->Clear()
- L48 _public enumerator_ `KCST_WireTraceSite = 18` — NOP with recorded address (never a step target)
- L50 _public enumerator_ `KCST_BindDelegate = 19` — Creates simple delegate
- L52 _public enumerator_ `KCST_RemoveMulticastDelegate = 20` — TargetDelegate->Remove(EventDelegate)
- L54 _public enumerator_ `KCST_CallDelegate = 21` — TargetDelegate->Broadcast(...)
- L56 _public enumerator_ `KCST_CreateArray = 22` — Creates and sets an array literal term
- L58 _public enumerator_ `KCST_CrossInterfaceCast = 23` — TargetInterface(Interface)
- L60 _public enumerator_ `KCST_MetaCast = 24` — Cast<TargetClass>(TargetObject)
- L61 _public enumerator_ `KCST_AssignmentOnPersistentFrame = 25`
- L63 _public enumerator_ `KCST_CastInterfaceToObj = 26` — Cast<TargetClass>(TargetInterface)
- L65 _public enumerator_ `KCST_GotoReturn = 27` — goto ReturnLabel
- L67 _public enumerator_ `KCST_GotoReturnIfNot = 28` — [if (!TargetObject->TargetProperty)] goto TargetLabel
- L68 _public enumerator_ `KCST_SwitchValue = 29`
- L70 _public enumerator_ `KCST_DoubleToFloatCast = 30`
- L71 _public enumerator_ `KCST_FloatToDoubleCast = 31`
- L76 _public enumerator_ `KCST_InstrumentedEvent` — Instrumented event
- L78 _public enumerator_ `KCST_InstrumentedEventStop` — Instrumented event stop
- L80 _public enumerator_ `KCST_InstrumentedPureNodeEntry` — Instrumented pure node entry
- L82 _public enumerator_ `KCST_InstrumentedWireEntry` — Instrumented wiretrace entry
- L84 _public enumerator_ `KCST_InstrumentedWireExit` — Instrumented wiretrace exit
- L86 _public enumerator_ `KCST_InstrumentedStatePush` — Instrumented state push
- L88 _public enumerator_ `KCST_InstrumentedStateRestore` — Instrumented state restore
- L90 _public enumerator_ `KCST_InstrumentedStateReset` — Instrumented state reset
- L92 _public enumerator_ `KCST_InstrumentedStateSuspend` — Instrumented state suspend
- L94 _public enumerator_ `KCST_InstrumentedStatePop` — Instrumented state pop
- L96 _public enumerator_ `KCST_InstrumentedTunnelEndOfThread` — Instrumented tunnel exit
- L98 _public enumerator_ `KCST_ArrayGetByRef`
- L99 _public enumerator_ `KCST_CreateSet`
- L100 _public enumerator_ `KCST_CreateMap`

#### struct `FBlueprintCompiledStatement`  
`struct FBlueprintCompiledStatement`  
_L104-157_
- desc: @TODO: Too rigid / icky design
- L106 _public function_ `FBlueprintCompiledStatement() : Type(KCST_Nop) , FunctionContext(NULL) , FunctionToCall(NULL) , TargetLabel(NULL) , UbergraphCallIndex(-1) , LHS(NULL) , bIsJumpTarget(false) , bIsInterfaceContext(false) , bIsParentContext(false) , ExecContext(NULL)`
- L120 _public member_ `EKismetCompiledStatementType Type;`
- L123 _public member_ `struct FBPTerminal* FunctionContext;` — Object that the function should be called on, or NULL to indicate self (KCST_CallFunction)
- L126 _public member_ `UFunction* FunctionToCall;` — Function that executes the statement (KCST_CallFunction)
- L129 _public member_ `FBlueprintCompiledStatement* TargetLabel;` — Target label (KCST_Goto, or KCST_CallFunction that requires an ubergraph reference)
- L132 _public member_ `int32 UbergraphCallIndex;` — The index of the argument to replace (only used when KCST_CallFunction has a non-NULL TargetLabel)
- L135 _public member_ `struct FBPTerminal* LHS;` — Destination of assignment statement or result from function call
- L138 _public member_ `TArray<struct FBPTerminal*> RHS;` — Argument list of function call or source of assignment statement
- L141 _public member_ `bool bIsJumpTarget;` — Is this node a jump target?
- L144 _public member_ `bool bIsInterfaceContext;` — Is this node an interface context? (KCST_CallFunction)
- L147 _public member_ `bool bIsParentContext;` — Is this function called on a parent class (super, etc)?  (KCST_CallFunction)
- L150 _public member_ `class UEdGraphPin* ExecContext;` — Exec pin about to execute (KCST_WireTraceSite)
- L153 _public member_ `TArray<class UEdGraphPin*> PureOutputContextArray;` — Pure node output pin(s) linked to exec node input pins (KCST_InstrumentedPureNodeEntry)
- L156 _public member_ `FString Comment;` — Comment text

### `Source/Editor/KismetCompiler/Public/EdGraphCompilerUtilities.h` (Public)


#### class `FGraphCompilerContext`  
`class FGraphCompilerContext`  
_L17-91_
- L21 _public member_ `FCompilerResultsLog& MessageLog;` — Compiler message log (errors, warnings, notes)
- L28 _protected prototype_ `virtual void ValidateLink(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const;` — Validates that the interconnection between two pins is schema compatible
- L31 _protected prototype_ `virtual void ValidatePin(const UEdGraphPin* Pin) const;` — Validate that the wiring for a single pin is schema compatible
- L34 _protected prototype_ `virtual void ValidateNode(const UEdGraphNode* Node) const;` — Validates that the node is schema compatible
- L37 _protected function_ `virtual bool CanIgnoreNode(const UEdGraphNode* Node) const` — Can this node be ignored for further processing?
- L43 _protected function_ `virtual bool ShouldForceKeepNode(const UEdGraphNode* Node) const` — Should this node be kept even if it's not reached?
- L49 _protected function_ `virtual bool PinIsImportantForDependancies(const UEdGraphPin* Pin) const` — Does this pin potentially participate in data dependencies?
- L54 _protected function_ `FGraphCompilerContext(FCompilerResultsLog& InMessageLog) : MessageLog(InMessageLog)`
- L60 _protected prototype_ `bool ValidateGraphIsWellFormed(UEdGraph* Graph) const;` — Performs standard validation on the graph (outputs point to inputs, no more than one connection to each input, types match on both ends, etc...)
- L65 _protected prototype_ `UEdGraphNode* FindNodeByClass(const UEdGraph* Graph, TSubclassOf<UEdGraphNode> NodeClass, bool bExpectedUnique) const;` — Scans a graph for a node of the specified class.  Can optionally continue scanning and print errors if additional nodes of the same category are found.
- L68 _protected prototype_ `virtual void PruneIsolatedNodes(const TArray<UEdGraphNode*>& RootSet, TArray<UEdGraphNode*>& GraphNodes);` — Prunes any nodes that weren't visited from the graph, printing out a warning
- L74 _protected prototype_ `void CreateExecutionSchedule(const TArray<UEdGraphNode*>& GraphNodes, TArray<UEdGraphNode*>& LinearExecutionSchedule) const;` — Performs a topological sort on the graph of nodes passed in (which is expected to form a DAG), scheduling them. If there are cycles or unconnected nodes present in the graph, an error will be output for each node that failed to be scheduled.
- L77 _protected function_ `int32 CountIncomingEdges(const UEdGraphNode* Node) const` — Counts the number of incoming edges this node has (along all input pins)

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API KISMETCOMPILER_API`

### `Source/Editor/KismetCompiler/Public/KismetCastingUtils.h` (Public)


#### enum `UE::KismetCompiler::CastingUtils::FloatingPointCastType`  
`enum class FloatingPointCastType`  
_L16-23_
- L18 _public enumerator_ `None`
- L19 _public enumerator_ `FloatToDouble`
- L20 _public enumerator_ `DoubleToFloat`
- L21 _public enumerator_ `Container`
- L22 _public enumerator_ `Struct`

#### struct `UE::KismetCompiler::CastingUtils::FConversion`  
`struct FConversion`  
_L25-29_
- L27 _public member_ `FloatingPointCastType Type = FloatingPointCastType::None;`
- L28 _public member_ `UFunction* Function = nullptr;`

#### struct `UE::KismetCompiler::CastingUtils::FImplicitCastParams`  
`struct FImplicitCastParams`  
_L31-36_
- L33 _public member_ `FConversion Conversion;`
- L34 _public member_ `FBPTerminal* TargetTerminal = nullptr;`
- L35 _public member_ `UEdGraphNode* TargetNode = nullptr;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace KismetCompiler` (scope `UE`)
- L14 _namespace_ `namespace CastingUtils` (scope `UE::KismetCompiler`)
- L49 _prototype_ `FBPTerminal* MakeImplicitCastTerminal(FKismetFunctionContext& Context, UEdGraphPin* Net, UEdGraphNode* SourceNode = nullptr);` (scope `UE::KismetCompiler::CastingUtils`) — Directly creates a new FBPTerminal that holds the result of an implicit cast. Internally, this is used by InsertImplicitCastStatement, but it can be used by any node that has special semantics for handling implicit casts. The terminal is guaranteed to have a unique name in the context. @param Context - Current function context to add the terminal to. @param Net - The corresponding pin that we'll copy type details from. @param SourceNode - The source node for the terminal. This is usually the Net's owner, but it can be different if necessary. @return A new FBPTerminal for the temporary variable that holds the casted result.
- L59 _prototype_ `void RegisterImplicitCasts(FKismetFunctionContext& Context);` (scope `UE::KismetCompiler::CastingUtils`) — Analyzes the NetMap of the current function context for potential implicit casts. If any are found, they're added to ImplicitCastMap in the context. After function compilation, the Kismet compiler will validate that the map is empty. It's up to the nodes to check the map and insert cast statements where necessary. @param Context - Current function context to analyze. Assumes the NetMap has been populated.
- L69 _prototype_ `void InsertImplicitCastStatement(FKismetFunctionContext& Context, const FImplicitCastParams& CastParams, FBPTerminal* RHSTerm);` (scope `UE::KismetCompiler::CastingUtils`) — Utility function used by nodes for inserting implicit cast statements. A compiled cast statement is created on the target node with the given parameters. @param Context - Current function context to analyze. Assumes the ImplicitCastMap has been populated. @param CastParams - Parameters for the cast operation. @param RHSTerm - The current terminal that should have its data read from.
- L83 _prototype_ `FBPTerminal* InsertImplicitCastStatement(FKismetFunctionContext& Context, UEdGraphPin* DestinationPin, FBPTerminal* RHSTerm);` (scope `UE::KismetCompiler::CastingUtils`) — Utility function used by nodes for inserting implicit cast statements. Similar to above, but the cast parameters are read from the context's cast map using a destination pin as the key. If no entry exists in the map, null is returned. @param Context - Current function context to analyze. Assumes the ImplicitCastMap has been populated. @param DestinationPin - Used as a key in the ImplicitCastMap. These pins are always inputs. @param RHSTerm - The current terminal that should have its data read from. @return A new FBPTerminal for the temporary variable that holds the casted result (if one exists).
- L96 _prototype_ `bool RemoveRegisteredImplicitCast(FKismetFunctionContext& Context, const UEdGraphPin* DestinationPin);` (scope `UE::KismetCompiler::CastingUtils`) — Removes the specific UEdGraphPin from the context's implicit cast map. In most cases, InsertImplicitCastStatement should be used to remove the cast map entry. However, some nodes need to implement custom behavior for casting. @param Context - Current function context to analyze. Assumes the ImplicitCastMap has been populated. @param DestinationPin - Used as a key in the ImplicitCastMap. These pins are always inputs. @return True if DestinationPin was found in the ImplicitCastMap.
- L108 _prototype_ `FConversion GetFloatingPointConversion(const UEdGraphPin& SourcePin, const UEdGraphPin& DestinationPin);` (scope `UE::KismetCompiler::CastingUtils`) — Retrieves the conversion type needed between two arbitrary pins (if necessary). Specifically, this indicates if either a narrowing or widening cast is needed between a float or a double type (including containers). In addition to the corresponding FloatingPointCastType that represents the cast type, a UFunction* may be included for container and struct conversions. @param SourcePin - The source pin to compare. @param DestinationPin - The destination pin to compare. @return A new FConversion containing the cast information.

### `Source/Editor/KismetCompiler/Public/KismetCompiledFunctionContext.h` (Public)


#### enum `KismetCompilerDebugOptions::(anonymous)`  
`enum`  
_L23-23_
- desc: @TODO: K2: Turning this off is probably broken due to state merging not working with the current code generation

#### enum `KismetCompilerDebugOptions::(anonymous)`  
`enum`  
_L26-26_
- desc: Should the compiler emit node comments to the backends?

#### enum `ETerminalSpecification`  
`enum ETerminalSpecification`  
_L29-34_
- L31 _public enumerator_ `TS_Unspecified`
- L32 _public enumerator_ `TS_Literal`
- L33 _public enumerator_ `TS_ForcedShared`

#### struct `FKismetFunctionContext`  
`struct FKismetFunctionContext`  
_L39-423_
- L43 _public member_ `UBlueprint* Blueprint;` — Blueprint source
- L45 _public member_ `UEdGraph* SourceGraph;`
- L48 _public member_ `UK2Node_FunctionEntry* EntryPoint;` — The nominal function entry point
- L50 _public member_ `UFunction* Function;`
- L51 _public member_ `UBlueprintGeneratedClass* NewClass;`
- L54 _public member_ `TArray<UEdGraphNode*> LinearExecutionList;` — Linear execution schedule
- L56 _public member_ `FCompilerResultsLog& MessageLog;`
- L57 _public member_ `const UEdGraphSchema_K2* Schema;`
- L60 _public member_ `TArray< FBlueprintCompiledStatement* > AllGeneratedStatements;` — An UNORDERED listing of all statements (used for cleaning up the dynamically allocated statements)
- L63 _public member_ `TMap<UEdGraphNode*, TArray<FBlueprintCompiledStatement*>> StatementsPerNode;` — Individual execution lists for every node that generated code to be consumed by the backend
- L66 _public member_ `TMap<FBlueprintCompiledStatement*, UEdGraphPin*> GotoFixupRequestMap;` — Goto fixup requests (each statement (key) wants to goto the first statement attached to the exec out-pin (value))
- L68 _public member_ `TIndirectArray<FBPTerminal> Parameters;`
- L69 _public member_ `TIndirectArray<FBPTerminal> Results;`
- L70 _public member_ `TIndirectArray<FBPTerminal> VariableReferences;`
- L71 _public member_ `TIndirectArray<FBPTerminal> PersistentFrameVariableReferences;`
- L72 _public member_ `TIndirectArray<FBPTerminal> Literals;`
- L73 _public member_ `TIndirectArray<FBPTerminal> Locals;`
- L74 _public member_ `TIndirectArray<FBPTerminal> EventGraphLocals;`
- L75 _public member_ `TIndirectArray<FBPTerminal> LevelActorReferences;`
- L76 _public member_ `TIndirectArray<FBPTerminal> InlineGeneratedValues;` — A function generating the parameter will be called inline. The value won't be stored in a local variable.
- L79 _public member_ `TMap<UEdGraphPin*, FBPTerminal*> NetMap;` — Map from a net to an term (either a literal or a storage location)
- L80 _public member_ `TMap<UEdGraphPin*, FBPTerminal*> LiteralHackMap;`
- L83 _public member_ `TMap<UEdGraphPin*, UE::KismetCompiler::CastingUtils::FImplicitCastParams> ImplicitCastMap;` — Contains a map of destination pins that will need an implicit cast to either a float or double
- L85 _public member_ `bool bIsUbergraph;`
- L86 _public member_ `bool bCannotBeCalledFromOtherKismet;`
- L87 _public member_ `bool bIsInterfaceStub;`
- L88 _public member_ `bool bIsConstFunction;`
- L89 _public member_ `bool bEnforceConstCorrectness;`
- L90 _public member_ `bool bCreateDebugData;`
- L91 _public member_ `bool bIsSimpleStubGraphWithNoParams;`
- L92 _public member_ `uint32 NetFlags;`
- L93 _public member_ `FName DelegateSignatureName;`
- L96 _public member_ `UEdGraphNode* SourceEventFromStubGraph;` — If this function is an event stub, then this points to the node in the ubergraph that caused the stub to exist
- L99 _public member_ `struct FNetNameMapping* NetNameMap;` — Map from a name to the number of times it's been 'created' (same nodes create the same local variable names, so they need something appended)
- L100 _public member_ `bool bAllocatedNetNameMap;`
- L103 _public member_ `bool bUseFlowStack;` — Does this function use requires FlowStack ?
- L105 _public prototype_ `FKismetFunctionContext(FCompilerResultsLog& InMessageLog, const UEdGraphSchema_K2* InSchema, UBlueprintGeneratedClass* InNewClass, UBlueprint* InBlueprint);`
- L107 _public prototype_ `~FKismetFunctionContext();`
- L109 _public prototype_ `void SetExternalNetNameMap(FNetNameMapping* NewMap);`
- L111 _public function_ `bool IsValid() const`
- L116 _public function_ `bool IsEventGraph() const`
- L121 _public function_ `void MarkAsEventGraph()`
- L126 _public function_ `void MarkAsInternalOrCppUseOnly()`
- L131 _public function_ `bool CanBeCalledByKismet() const`
- L136 _public function_ `void MarkAsInterfaceStub()`
- L141 _public function_ `void MarkAsConstFunction(bool bInEnforceConstCorrectness)`
- L147 _public function_ `bool IsInterfaceStub() const`
- L152 _public function_ `void SetDelegateSignatureName(FName InName)`
- L158 _public function_ `bool IsDelegateSignature()`
- L163 _public function_ `bool IsConstFunction() const`
- L168 _public function_ `bool EnforceConstCorrectness() const`
- L173 _public function_ `void MarkAsNetFunction(uint32 InFunctionFlags)`
- L178 _public function_ `bool IsDebuggingOrInstrumentationRequired() const`
- L183 _public function_ `EKismetCompiledStatementType GetWireTraceType() const`
- L188 _public function_ `EKismetCompiledStatementType GetBreakpointType() const`
- L193 _public function_ `uint32 GetNetFlags() const`
- L198 _public function_ `FBPTerminal* RegisterLiteral(UEdGraphPin* Net)`
- L210 _public function_ `UStruct* GetScopeFromPinType(FEdGraphPinType& Type, UClass* SelfClass)` — Returns a UStruct scope corresponding to the pin type passed in, if one exists
- L228 _public function_ `UBlueprint* GetBlueprint()`
- L233 _public function_ `FBlueprintCompiledStatement& PrependStatementForNode(UEdGraphNode* Node)`
- L245 _public function_ `FBlueprintCompiledStatement& AppendStatementForNode(UEdGraphNode* Node)` — Enqueue a statement to be executed when the specified Node is triggered
- L257 _public function_ `void CopyAndPrependStatements(UEdGraphNode* Destination, UEdGraphNode* Source)` — Prepends the statements corresponding to Source to the set of statements corresponding to Dest
- L304 _public function_ `bool DidNodeGenerateCode(UEdGraphNode* Node)` — Returns true if Node generated code, and false otherwise
- L312 _private prototype_ `void MergeAdjacentStates();` — Optimize out any useless jumps (jump to the very next statement, where the control flow can just fall through)
- L315 _private prototype_ `void FinalSortLinearExecList();` — Sorts the 'linear execution list' again by likely execution order; the list should only contain impure nodes by this point.
- L318 _private prototype_ `void ResolveGotoFixups();` — Resolves all pending goto fixups; Should only be called after all nodes have had a chance to generate code!
- L322 _public prototype_ `static bool DoesStatementRequiresFlowStack(const FBlueprintCompiledStatement* Statement);` — Returns true if this statement cannot be optimized to remove the flow stack
- L325 _public prototype_ `void ResolveStatements();` — This function links gotos, sorts statments, and merges adjacent ones
- L335 _public function_ `void InsertWireTrace(FBlueprintCompiledStatement* GotoStatement, UEdGraphPin* AssociatedExecPin)` — Makes sure an KCST_WireTraceSite is inserted before the specified statement, and associates the specified pin with the inserted wire-trace (so we can backwards engineer which pin triggered the goto). @param  GotoStatement		The statement to insert a goto before. @param  AssociatedExecPin	The pin responsible for executing the goto.
- L377 _public function_ `UEdGraphPin* FindRequiredPinByName(const UEdGraphNode* Node, const FName PinName, EEdGraphPinDirection RequiredDirection = EGPD_MAX)` — Looks for a pin of the given name, erroring if the pin is not found or if the direction doesn't match (doesn't verify the pin type)
- L400 _public function_ `bool ValidatePinType(const UEdGraphPin* Pin, const FEdGraphPinType& TestType)` — Checks to see if a pin is of the requested type
- L421 _public prototype_ `FBPTerminal* CreateLocalTerminalFromPinAutoChooseScope(UEdGraphPin* Net, FString NewName);`
- L422 _public prototype_ `FBPTerminal* CreateLocalTerminal(ETerminalSpecification Spec = ETerminalSpecification::TS_Unspecified);`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace KismetCompilerDebugOptions`
- L23 _enumerator_ `enum { DebuggingCompiler = 1 }; enum { EmitNodeComments = DebuggingCompiler };` (scope `KismetCompilerDebugOptions::__anoncf8862ec0103`) — @TODO: K2: Turning this off is probably broken due to state merging not working with the current code generation
- L26 _enumerator_ `enum { EmitNodeComments = DebuggingCompiler };` (scope `KismetCompilerDebugOptions::__anoncf8862ec0203`) — Should the compiler emit node comments to the backends?

### `Source/Editor/KismetCompiler/Public/KismetCompiler.h` (Public)


#### enum `EInternalCompilerFlags`  
`enum class EInternalCompilerFlags`  
_L66-73_
- L68 _public enumerator_ `None = 0x0`
- L70 _public enumerator_ `PostponeLocalsGenerationUntilPhaseTwo = 0x1`
- L71 _public enumerator_ `PostponeDefaultObjectAssignmentUntilReinstancing = 0x2`
- L72 _public enumerator_ `SkipRefreshExternalBlueprintDependencyNodes = 0x4`

#### class `FKismetCompilerContext`  
`class FKismetCompilerContext : public FGraphCompilerContext`  
_L78-689_
- inherits: `FGraphCompilerContext`
- L82 _public prototype_ `DECLARE_EVENT_OneParam(FKismetCompilerContext, FOnFunctionListCompiled, FKismetCompilerContext*);`
- L83 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnPreCompileBlueprint, UBlueprint*);`
- L86 _protected typedef_ `typedef FGraphCompilerContext Super;`
- L89 _protected member_ `UEdGraphSchema_K2* Schema;` — Schema for the graph being compiled
- L92 _protected member_ `TMap< TSubclassOf<class UEdGraphNode>, FNodeHandlingFunctor*> NodeHandlers;` — Map from node class to a handler functor
- L95 _protected member_ `TArray<TFunction<void(const UObject::FPostCDOCompiledContext&, UObject*)>> PostCDOCompileSteps;` — Array of function refs to run after the CDO has been compiled in FKismetCompilerContext::PostCDOCompiled
- L98 _protected member_ `TMap<class UTimelineTemplate*, class FProperty*> TimelineToMemberVariableMap;` — Map of properties created for timelines; to aid in debug data generation
- L101 _protected member_ `TMap<FName, FString> DefaultPropertyValueMap;` — Map from UProperties to default object values, to be fixed up after compilation is complete
- L104 _protected member_ `TSet<FString> CreatedFunctionNames;` — Names of functions created
- L107 _protected member_ `TIndirectArray<FKismetFunctionContext> FunctionList;` — List of functions currently allocated
- L110 _protected member_ `TArray<UEdGraph*> GeneratedFunctionGraphs;` — Set of function graphs generated for the class layout at compile time
- L113 _protected member_ `TArray<UEdGraph*> GeneratedUbergraphPages;` — Set of ubergraph pages generated for the class layout at compile time
- L118 _protected member_ `TArray<FMulticastDelegateProperty*> GeneratedMulticastDelegateProps;` — Set of generated multicast delegate properties
- L121 _protected member_ `FOnFunctionListCompiled FunctionListCompiledEvent;` — Event that is broadcast immediately after the function list for this context has been compiled.
- L124 _protected member_ `FKismetCompilerOptions CompileOptions;` — This struct holds the various compilation options, such as which passes to perform, whether to save intermediate results, etc
- L127 _protected member_ `int32 MacroRowMaxHeight;` — Maximum height encountered in this row; used to position the next row appropriately
- L130 _protected member_ `int32 MinimumSpawnX;` — Maximum bounds of the spawning area
- L131 _protected member_ `int32 MaximumSpawnX;`
- L134 _protected member_ `int32 AverageNodeWidth;` — Average node size for nodes with no size
- L135 _protected member_ `int32 AverageNodeHeight;`
- L138 _protected member_ `int32 HorizontalSectionPadding;` — Padding
- L139 _protected member_ `int32 VerticalSectionPadding;`
- L140 _protected member_ `int32 HorizontalNodePadding;`
- L143 _protected member_ `int32 MacroSpawnX;` — Used to space expanded macro nodes when saving intermediate results
- L144 _protected member_ `int32 MacroSpawnY;`
- L146 _protected member_ `UScriptStruct* VectorStruct;`
- L147 _protected member_ `UScriptStruct* RotatorStruct;`
- L148 _protected member_ `UScriptStruct* TransformStruct;`
- L149 _protected member_ `UScriptStruct* LinearColorStruct;`
- L152 _public member_ `UBlueprint* Blueprint;`
- L153 _public member_ `UBlueprintGeneratedClass* NewClass;`
- L154 _public member_ `UBlueprintGeneratedClass* OldClass;`
- L157 _public member_ `UEdGraph* ConsolidatedEventGraph;` — The ubergraph; valid from roughly the start of CreateAndProcessEventGraph
- L160 _public member_ `FKismetFunctionContext* UbergraphContext;` — The ubergraph context; valid from the end of CreateAndProcessEventGraph
- L162 _public member_ `TMap<UEdGraphNode*, UEdGraphNode*> CallsIntoUbergraph;`
- L163 _public member_ `int32 bIsFullCompile:1;`
- L170 _public member_ `TMap<UEdGraphNode*, UEdGraphNode*> MacroGeneratedNodes;` — Map that can be used to find the macro node that spawned a provided node, if any. Macro instances can have more macros inside of them, so entries in this map may chain (i.e. values may also need to be used as keys to find the full chain). Used to generate deterministic, unique identifiers for properties generated by nodes.
- L173 _public member_ `TMap<FName, FProperty*> RepNotifyFunctionMap;` — Map from UProperties to their RepNotify graph
- L176 _public member_ `FNetNameMapping ClassScopeNetNameMap;` — Map from a name to the number of times it's been 'created' (identical nodes create the same variable names, so they need something appended)
- L179 _public member_ `UObject* OldCDO;` — Data that persists across CompileClassLayout/CompileFunctions calls:
- L180 _public member_ `int32 OldGenLinkerIdx;`
- L181 _public member_ `FLinkerLoad* OldLinker;`
- L182 _public member_ `UBlueprintGeneratedClass* TargetClass;`
- L186 _public member_ `bool bAssignDelegateSignatureFunction;` — Flag to trigger FMulticastDelegateProperty::SignatureFunction resolution in CreateClassVariablesFromBlueprint:
- L192 _private member_ `bool bAutomaticallyRegisterInputEvents;` — Set to true when there is an input event the graph and we want to automatically set up input component binding.
- L196 _public prototype_ `void SetAutomaticallyRegisterInputEvents(const bool bVal);`
- L197 _public prototype_ `bool GetAutomaticallyRegisterInputEvents() const;`
- L205 _public member_ `TMap<UK2Node_CreateDelegate*, FDelegateInfo> ConvertibleDelegates;`
- L207 _public member_ `static FSimpleMulticastDelegate OnPreCompile;`
- L208 _public member_ `static FSimpleMulticastDelegate OnPostCompile;`
- L209 _public member_ `static FOnPreCompileBlueprint OnPreCompileBlueprint;`
- L212 _public function_ `FOnFunctionListCompiled& OnFunctionListCompiled()` — Broadcasts a notification immediately after the function list for this context has been compiled.
- L214 _public prototype_ `FKismetCompilerContext(UBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions);`
- L215 _public prototype_ `virtual ~FKismetCompilerContext();`
- L218 _public prototype_ `void CompileClassLayout(EInternalCompilerFlags InternalFlags);` — Compile the class layout of the blueprint
- L221 _public prototype_ `void CompileFunctions(EInternalCompilerFlags InternalFlags);` — Compile the functions of the blueprint - must be done after compiling the class layout:
- L224 _public prototype_ `void PostCDOCompiled(const UObject::FPostCDOCompiledContext& Context);` — Called after the CDO has been generated, allows assignment of cached/derived data:
- L229 _public prototype_ `void AddPostCDOCompiledStep(TFunction<void (const UObject::FPostCDOCompiledContext&, UObject*)>&& StepFunction);` — Adds the given "StepFunction" to be run after the CDO has been compiled in FKismetCompilerContext::PostCDOCompiled.
- L232 _public prototype_ `void Compile();` — Compile a blueprint into a class and a set of functions
- L235 _public prototype_ `void SetNewClass(UBlueprintGeneratedClass* ClassToUse);` — Function used to assign the new class that will be used by the compiler
- L237 _public function_ `const UEdGraphSchema_K2* GetSchema() const`
- L241 _public prototype_ `UEdGraph* SpawnIntermediateFunctionGraph(const FString& InDesiredFunctionName, const UFunction* InSignature = nullptr, bool bUseUniqueName = true);` — Spawn an intermediate function graph for this compilation using the specified desired name (and optional signature), which may be modified to make it unique.
- L245 _public function_ `template <typename NodeType> NodeType* SpawnIntermediateNode(UEdGraphNode* SourceNode, UEdGraph* ParentGraph = nullptr)` — Spawns an intermediate node associated with the source node (for error purposes)
- L270 _public prototype_ `FPinConnectionResponse MovePinLinksToIntermediate(UEdGraphPin& SourcePin, UEdGraphPin& IntermediatePin);` — Moves pin links over from the source-pin to the specified intermediate, and validates the result (additionally logs a redirect from the intermediate-pin back to the source so we can back trace for debugging, etc.) @param  SourcePin		The pin you want disconnected. @param  IntermediatePin	The pin you want the SourcePin's links moved to. @return The result from calling the schema's MovePinLinks().
- L281 _public prototype_ `FPinConnectionResponse CopyPinLinksToIntermediate(UEdGraphPin& SourcePin, UEdGraphPin& IntermediatePin);` — Copies pin links over from the source-pin to the specified intermediate, and validates the result (additionally logs a redirect from the intermediate-pin back to the source so we can back trace for debugging, etc.) @param  SourcePin		The pin whose links you want copied. @param  IntermediatePin	The pin you want the SourcePin's links copied to. @return The result from calling the schema's CopyPinLinks().
- L295 _public prototype_ `UK2Node_TemporaryVariable* SpawnInternalVariable(UEdGraphNode* SourceNode, FName Category, FName SubCategory = NAME_None, UObject* SubcategoryObject = nullptr, EPinContainerType PinContainerType = EPinContainerType::None, const FEdGraphTerminalType& ValueTerminalType = FEdGraphTerminalType());`
- L297 _public prototype_ `bool UsePersistentUberGraphFrame() const;`
- L299 _public prototype_ `FString GetGuid(const UEdGraphNode* Node) const;`
- L301 _public prototype_ `static TSharedPtr<FKismetCompilerContext> GetCompilerForBP(UBlueprint* BP, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompileOptions);`
- L302 _public prototype_ `static void RegisterCompilerForBP(UClass* BPClass, CompilerContextFactoryFunction FactoryFunction );`
- L305 _public prototype_ `void ValidateVariableNames();` — Ensures that all variables have valid names for compilation/replication
- L308 _public prototype_ `void ValidateComponentClassOverrides();` — Ensures that all component class overrides are legal overrides of the parent class
- L315 _public prototype_ `void ValidateClassPropertyDefaults();` — Ensures that all class reference Properties are legal overrides of the parent class by checking the default value set on any PC_Class variable types. Requires a valid CDO in order to do this validation. Called in Stage V: Validate
- L318 _public prototype_ `void ResetAndPopulateBlueprintGeneratedVariables();` — Resets the blueprint's GeneratedVariables list and calls PopulateBlueprintGeneratedVariables
- L321 _public prototype_ `virtual void CreateClassVariablesFromBlueprint();` — Creates a class variable for each entry in the Blueprint NewVars array
- L326 _public prototype_ `FName GetEventStubFunctionName(UK2Node_Event* SrcEventNode);` — Picks the name to use for an autogenerated event stub
- L334 _public prototype_ `void RegisterClassDelegateProxiesFromBlueprint();` — Searches the function graphs and ubergraph pages for any delegate proxies, which are then registered with the compiler context. If a "captured" variable is needed, then a new property will be added to the current class. In this context, a captured variable is any target actor that the delegate will be called on.
- L337 _protected prototype_ `virtual UEdGraphSchema_K2* CreateSchema();`
- L338 _protected prototype_ `virtual void PostCreateSchema();`
- L339 _protected prototype_ `virtual void SpawnNewClass(const FString& NewClassName);`
- L340 _protected function_ `virtual void OnNewClassSet(UBlueprintGeneratedClass* ClassToUse)`
- L341 _protected function_ `virtual void OnPostCDOCompiled(const UObject::FPostCDOCompiledContext& Context)`
- L346 _protected prototype_ `virtual void EnsureProperGeneratedClass(UClass*& TargetClass);` — Backwards Compatability:  Ensures that the passed in TargetClass is of the proper type (e.g. BlueprintGeneratedClass, AnimBlueprintGeneratedClass), and NULLs the reference if it is not
- L354 _protected prototype_ `virtual void CleanAndSanitizeClass(UBlueprintGeneratedClass* ClassToClean, UObject*& OldCDO);` — Removes the properties and functions from a class, so that new ones can be created in its place @param ClassToClean		The UClass to scrub @param OldCDO			Reference to the old CDO of the class, so we can copy the properties from it to the new class's CDO
- L357 _protected function_ `virtual void PopulateBlueprintGeneratedVariables()` — Compilers are expected to populate the blueprint's full list of GeneratedVariables here as the list is reset at this point
- L382 _protected prototype_ `virtual void SaveSubObjectsFromCleanAndSanitizeClass(FSubobjectCollection& SubObjectsToSave, UBlueprintGeneratedClass* ClassToClean);` — Saves any SubObjects on the blueprint that need to survive the clean
- L389 _protected prototype_ `void CheckConnectionResponse(const FPinConnectionResponse &Response, const UEdGraphNode *Node);` — Checks a connection response, and errors if it didn't succeed (not public, users should be using MovePinLinksToIntermediate/CopyPinLinksToIntermediate instead of wrapping their own with this).
- L392 _protected prototype_ `void PruneIsolatedNodes(UEdGraph* InGraph, bool bInIncludeNodesThatCouldBeExpandedToRootSet);` — Prune isolated nodes given the specified graph
- L395 _protected prototype_ `virtual void ValidateLink(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const override;` — FGraphCompilerContext interface
- L396 _protected prototype_ `virtual void ValidatePin(const UEdGraphPin* Pin) const override;`
- L397 _protected prototype_ `virtual void ValidateNode(const UEdGraphNode* Node) const override;`
- L398 _protected prototype_ `virtual bool CanIgnoreNode(const UEdGraphNode* Node) const override;`
- L399 _protected prototype_ `virtual bool ShouldForceKeepNode(const UEdGraphNode* Node) const override;`
- L400 _protected prototype_ `virtual void PruneIsolatedNodes(const TArray<UEdGraphNode*>& RootSet, TArray<UEdGraphNode*>& GraphNodes) override;`
- L401 _protected function_ `virtual bool PinIsImportantForDependancies(const UEdGraphPin* Pin) const override`
- L408 _protected prototype_ `void ExpansionStep(UEdGraph* Graph, bool bAllowUbergraphExpansions);` — Expands out nodes that need it
- L411 _protected prototype_ `void AdvanceMacroPlacement(int32 Width, int32 Height);` — Advances the macro position tracking
- L412 _protected prototype_ `void AutoAssignNodePosition(UEdGraphNode* Node);`
- L413 _protected prototype_ `void CreateCommentBlockAroundNodes(const TArray<UEdGraphNode*>& Nodes, UObject* SourceObject, UEdGraph* TargetGraph, FString CommentText, FLinearColor CommentColor, int32& Out_OffsetX, int32& Out_OffsetY);`
- L416 _protected prototype_ `FProperty* CreateVariable(const FName Name, const FEdGraphPinType& Type);` — Creates a class variable
- L425 _protected prototype_ `FMulticastDelegateProperty* CreateMulticastDelegateVariable(const FName Name, const FEdGraphPinType& Type);` — Creates a multicast delegate variable & associated signature graph / function, use to generate events You must add an ubergraph page containing an 'UK2Node_GeneratedBoundEvent' that corresponds to this delegate to 'GeneratedUbergraphPages' in your 'FKismetCompilerContext'. We do not create this graph / page for you so that graph creation is not coupled to variable creation. We will associate this delegate with your node for you by name.
- L432 _protected prototype_ `FMulticastDelegateProperty* CreateMulticastDelegateVariable(const FName Name);` — Creates a multicast delegate variable & associated signature graph / Function, use to generate events Defaults to base MulticastDelegate type. See above version with 'Type' arg for more info.
- L435 _protected function_ `virtual void PostCompileDiagnostics()` — Gives derived classes a chance to emit debug data
- L438 _protected function_ `virtual void PreCompile()` — Gives derived classes a chance to hook up any custom logic
- L439 _protected function_ `virtual void PostCompile()`
- L442 _protected function_ `virtual void PostExpansionStep(const UEdGraph* Graph)` — Gives derived classes a chance to process post-node expansion
- L445 _protected prototype_ `virtual bool IsNodePure(const UEdGraphNode* Node) const;` — Determines if a node is pure
- L448 _protected prototype_ `void CreatePropertiesFromList(UStruct* Scope, FField::FLinkedListBuilder& PropertyListBuilder, TIndirectArray<FBPTerminal>& Terms, EPropertyFlags PropertyFlags, bool bPropertiesAreLocal, bool bPropertiesAreParameters = false);` — Creates a property with flags including PropertyFlags in the Scope structure for each entry in the Terms array
- L451 _protected prototype_ `void CreateParametersForFunction(FKismetFunctionContext& Context, UFunction* ParameterSignature, FField::FLinkedListBuilder& PropertyListBuilder);` — Create the properties on a function for input/output parameters
- L454 _protected prototype_ `void CreateLocalVariablesForFunction(FKismetFunctionContext& Context, FField::FLinkedListBuilder& PropertyListBuilder);` — Creates the properties on a function that store the local and event graph (if applicable) variables
- L457 _protected prototype_ `void CreateUserDefinedLocalVariablesForFunction(FKismetFunctionContext& Context, FField::FLinkedListBuilder& PropertyListBuilder);` — Creates user defined local variables for function
- L460 _protected prototype_ `static FProperty* CreateUserDefinedLocalVariableForFunction(const FBPVariableDescription& Variable, UFunction* Function, UBlueprintGeneratedClass* OwningClass, FField::FLinkedListBuilder& PropertyListBuilder, const UEdGraphSchema_K2* Schema, FCompilerResultsLog& MessageLog);` — Helper function for CreateUserDefinedLocalVariablesForFunction and compilation manager's FastGenerateSkeletonClass:
- L463 _protected prototype_ `void SetPropertyDefaultValue(const FProperty* PropertyToSet, FString& Value);` — Adds a default value entry into the DefaultPropertyValueMap for the property specified
- L466 _protected prototype_ `virtual void CopyTermDefaultsToDefaultObject(UObject* DefaultObject);` — Copies default values cached for the terms in the DefaultPropertyValueMap to the final CDO
- L469 _protected prototype_ `void PropagateValuesToCDO(UObject* NewCDO, UObject* OldCDO);` — Non virtual wrapper to encapsulate functions that occur when the CDO is ready for values:
- L475 _protected prototype_ `void SetCanEverTick() const;` — Function works only if subclass of AActor or UActorComponent. If ReceiveTick event is defined, force CanEverTick.
- L478 _protected prototype_ `const UK2Node_FunctionEntry* FindLocalEntryPoint(const UFunction* Function) const;` — Scan FunctionList and return Entry point, for matching one
- L481 _protected prototype_ `void PrintVerboseInfoStruct(UStruct* Struct) const;` — @TODO: Debug printing
- L482 _protected prototype_ `void PrintVerboseInformation(UClass* Class) const;`
- L488 _protected prototype_ `virtual void TransformNodes(FKismetFunctionContext& Context);` — Performs transformations on specific nodes that require it according to the schema
- L493 _protected prototype_ `virtual void MergeUbergraphPagesIn(UEdGraph* Ubergraph);` — Merges in any all ubergraph pages into the gathering ubergraph
- L498 _protected prototype_ `virtual void CreateFunctionList();` — Creates a list of functions to compile
- L501 _protected prototype_ `FKismetFunctionContext* CreateFunctionContext();` — Creates a new function context and adds it to the function list to be processed.
- L506 _protected prototype_ `virtual void MergeGraphIntoUbergraph(UEdGraph* SourceGraph, UEdGraph* Ubergraph);` — Merges a single ubergraph page into the main ubergraph
- L511 _protected prototype_ `virtual void ProcessOneFunctionGraph(UEdGraph* SourceGraph, bool bInternalFunction = false);` — Merges macros/subgraphs into the graph and validates it, creating a function list entry if it's reasonable.
- L516 _protected function_ `FName GetUbergraphCallName() const` — Gets the unique name for this context's ExecuteUbergraph function
- L525 _protected prototype_ `void ExpandTunnelsAndMacros(UEdGraph* SourceGraph);` — Expands any macro instances and collapses any tunnels in the nodes of SourceGraph
- L530 _protected prototype_ `void MapExpansionPathToTunnelInstance(const UEdGraphNode* InnerExpansionNode, const UEdGraphNode* OuterTunnelInstance);` — Maps the nodes in an intermediate tunnel expansion path back to the owning tunnel instance node.
- L546 _protected prototype_ `void ProcessIntermediateTunnelBoundary(UK2Node_Tunnel* TunnelInput, UK2Node_Tunnel* TunnelOutput);` — Processes an intermediate tunnel expansion boundary. We define a tunnel boundary as the input and output sides of an intermediate tunnel instance node expansion. Each boundary consists of a pair of tunnel nodes (input/output), with one side being the tunnel "instance" node that owns the expansion. After expansion, tunnel nodes are cropped and removed from the function graph, so they do not result in any actual bytecode. This function maps the nodes in the execution path through the expansion and back to the outer tunnel instance node. If Blueprint debugging is enabled, this function also spawns one or more intermediate "boundary" NOPs around the tunnel I/O pair. The boundary nodes are intended to serve as debug sites, allowing breakpoints to be hit on both sides of the tunnel. @param	TunnelInput		Tunnel input node. This will either be a tunnel instance node (OutputSource) or a tunnel exit node. @param	TunnelOutput	Tunnel output node. This will either be a tunnel entry node or a tunnel instance node (InputSink).
- L551 _protected prototype_ `void CreateAndProcessUbergraph();` — Merges pages and creates function stubs, etc...
- L554 _protected prototype_ `void CreateFunctionStubForEvent(UK2Node_Event* Event, UObject* OwnerOfTemporaries);` — Create a stub function graph for the event node, and have it invoke the correct point in the ubergraph
- L557 _protected prototype_ `void ExpandTimelineNodes(UEdGraph* SourceGraph);` — Expand timeline nodes into necessary nodes
- L567 _protected prototype_ `virtual void PrecompileFunction(FKismetFunctionContext& Context, EInternalCompilerFlags InternalFlags);` — First phase of compiling a function graph - Performs initial validation that the graph is at least well formed enough to be processed further - Creates a copy of the graph to allow further transformations to occur - Prunes the 'graph' to only included the connected portion that contains the function entry point - Schedules execution of each node based on data/execution dependencies - Creates a UFunction object containing parameters and local variables (but no script code yet)
- L570 _protected prototype_ `virtual void InitializeGeneratedEventNodes(EInternalCompilerFlags InternalFlags);` — Called to initialize generated event nodes that came from generated ubergraph pages after delegate signature compilation is done
- L575 _protected prototype_ `virtual void PreCompileUpdateBlueprintOnLoad(UBlueprint* BP);` — Used for performing custom patching during stage IX of the compilation during load.
- L581 _protected prototype_ `virtual void CompileFunction(FKismetFunctionContext& Context);` — Second phase of compiling a function graph - Generates an executable statement list
- L587 _protected prototype_ `virtual void PostcompileFunction(FKismetFunctionContext& Context);` — Final phase of compiling a function graph; called after all functions have had CompileFunction called - Patches up cross-references, etc..., and performs final validation
- L592 _protected prototype_ `void FinishCompilingFunction(FKismetFunctionContext& Context);` — Handles final post-compilation setup, flags, creates cached values that would normally be set during deserialization, etc...
- L595 _protected prototype_ `virtual void SetCalculatedMetaDataAndFlags(UFunction* Function, UK2Node_FunctionEntry* EntryNode, const UEdGraphSchema_K2* Schema );` — Adds metadata for a particular compiled function based on its characteristics
- L598 _protected prototype_ `static void SetDefaultInputValueMetaData(UFunction* Function, const TArray< TSharedPtr<FUserPinInfo> >& InputData);` — Reflects each pin's user set, default value into the function's metadata (so it can be queried for later by CallFunction nodes, etc.)
- L603 _protected prototype_ `virtual void AddInterfacesFromBlueprint(UClass* Class);` — Handles adding the implemented interface information to the class
- L608 _protected prototype_ `virtual void FinishCompilingClass(UClass* Class);` — Handles final post-compilation setup, flags, creates cached values that would normally be set during deserialization, etc...
- L611 _protected prototype_ `void BuildDynamicBindingObjects(UBlueprintGeneratedClass* Class);` — Build the dynamic bindings objects used to tie events to delegates at runtime
- L616 _protected prototype_ `void VerifyValidOverrideEvent(const UEdGraph* Graph);` — If a function in the graph cannot be placed as event make sure that it is not.
- L621 _protected prototype_ `void VerifyValidOverrideFunction(const UEdGraph* Graph);` — If a function in the graph cannot be overridden make sure that it is not.
- L626 _protected prototype_ `void ValidateSelfPinsInGraph(FKismetFunctionContext& Context);` — Checks if self pins are connected.
- L631 _protected prototype_ `void ValidateNoWildcardPinsInGraph(const UEdGraph* SourceGraph);` — Checks if pin types are unresolved (e.g. still wildcards).
- L634 _protected prototype_ `void ValidateTimelineNames();` — Ensures that all timelines have valid names for compilation/replication
- L637 _protected prototype_ `void ValidateFunctionGraphNames();` — Ensures that all function graphs have valid names for compilation/replication
- L640 _protected prototype_ `virtual bool ValidateGeneratedClass(UBlueprintGeneratedClass* Class);` — Validates the generated class
- L643 _protected prototype_ `void DetermineNodeExecLinks(UEdGraphNode* SourceNode, TMap<UEdGraphPin*, UEdGraphPin*>& SourceNodeLinks) const;` — Discovers exec pin links for the sourcenode
- L646 _private prototype_ `void CreateLocalsAndRegisterNets(FKismetFunctionContext& Context, FField::FLinkedListBuilder& PropertyListBuilder);`
- L651 _private prototype_ `void CreatePinEventNodeForTimelineFunction(UK2Node_Timeline* TimelineNode, UEdGraph* SourceGraph, FName FunctionName, const FName PinName, FName ExecFuncName);` — Handles creating a new event node for a given output on a timeline node utilizing the named function
- L654 _private prototype_ `class UK2Node_CallFunction* CreateCallTimelineFunction(UK2Node_Timeline* TimelineNode, UEdGraph* SourceGraph, FName FunctionName, UEdGraphPin* TimelineVarPin, UEdGraphPin* TimelineFunctionPin);` — Util for creating a node to call a function on a timeline and move connections to it
- L661 _private prototype_ `void ResetErrorFlags(UEdGraph* Graph) const;` — Function to reset graph node's error flag before compiling @param: Reference to graph instance
- L669 _private prototype_ `void RegisterConvertibleDelegates(UEdGraph* Graph);` — Registers any nodes that are bound to a "convertible" function signature. Specifically, these are function signatures that differ only by float/double parameters. @param: Reference to graph instance
- L680 _private prototype_ `void ReplaceConvertibleDelegates(UEdGraph* Graph);` — Modifies the graph to use a proxy delegate function if it uses a convertible delegate signature. This involves several steps: 1. Creates a new function graph that uses the exact function signature of the delegate. 2. Adds and links the original delegate function call, which implicity casts the input parameters. 3. If applicable, adds a node to the original graph that sets the variable of the target actor (ie: the captured variable) @param: Reference to graph instance

#### struct `FKismetCompilerContext::FDelegateInfo`  
`struct FDelegateInfo`  
_L199-203_
- L201 _public member_ `FName ProxyFunctionName;`
- L202 _public member_ `FName CapturedVariableName;`

#### struct `FKismetCompilerContext::FNameParameterHelper`  
`struct FNameParameterHelper`  
_L283-293_
- L285 _public function_ `FNameParameterHelper(const FName InNameParameter) : NameParameter(InNameParameter)`
- L286 _public function_ `FNameParameterHelper(const FString& InNameParameter) : NameParameter(*InNameParameter)`
- L287 _public function_ `FNameParameterHelper(const TCHAR* InNameParameter) : NameParameter(InNameParameter)`
- L289 _public function_ `FName operator*() const`
- L292 _private member_ `FName NameParameter;`

#### struct `FKismetCompilerContext::FSubobjectCollection`  
`struct FSubobjectCollection`  
_L359-377_
- L362 _private member_ `TSet<const UObject*> Collection;`
- L365 _public prototype_ `void AddObject(const UObject* const InObject);`
- L368 _public function_ `template<typename TOBJ> void AddObjects(const TArray<TOBJ>& InObjects)`
- L376 _public prototype_ `bool operator()(const UObject* const RemovalCandidate) const;`

#### Free symbols / members of external scopes

- L37 _macro_ `#define UE_API KISMETCOMPILER_API`
- L61 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogK2Compiler, Log, All);`
- L76 _typedef_ `typedef TFunction<TSharedPtr<FKismetCompilerContext>(UBlueprint*, FCompilerResultsLog&, const FKismetCompilerOptions&)> CompilerContextFactoryFunction;`
- L82 _delegate_ `DECLARE_EVENT_OneParam(FKismetCompilerContext, FOnFunctionListCompiled, FKismetCompilerContext*);`
- L83 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnPreCompileBlueprint, UBlueprint*);`

### `Source/Editor/KismetCompiler/Public/KismetCompilerMisc.h` (Public)


#### enum `ConvertibleSignatureMatchResult`  
`enum class ConvertibleSignatureMatchResult`  
_L44-49_
- desc: Used by DoSignaturesHaveConvertibleFloatTypes
- L46 _public enumerator_ `ExactMatch` — The function signatures are an exact match
- L47 _public enumerator_ `HasConvertibleFloatParams` — The function signatures are identical, except for float/double mismatches, which can be converted
- L48 _public enumerator_ `Different` — The function signatures are completely different

#### class `FKismetCompilerUtilities`  
`class FKismetCompilerUtilities`  
_L52-166_
- desc: This is a loose collection of utilities used when 'compiling' a new UClass from a K2 graph.
- L56 _public prototype_ `static void ConsignToOblivion(UClass* OldClass, bool bForceNoResetLoaders);` — Rename a class and it's CDO into the transient package, and clear RF_Public on both of them
- L59 _public prototype_ `static void UpdateBlueprintSkeletonStubClassAfterFailedCompile(UBlueprint* Blueprint, UClass* StubClass);`
- L72 _public prototype_ `static bool IsTypeCompatibleWithProperty(UEdGraphPin* SourcePin, FProperty* Property, FCompilerResultsLog& MessageLog, const UEdGraphSchema_K2* Schema, UClass* SelfClass);` — Tests to see if a pin is schema compatible with a property. @param	SourcePin		If non-null, source object. @param	Property		The property to check. @param	MessageLog  	The message log. @param	Schema			Schema. @param	SelfClass   	Self class (needed for pins marked Self). @return	true if the pin type/direction is compatible with the property.
- L75 _public prototype_ `static FProperty* FindPropertyInScope(UStruct* Scope, UEdGraphPin* Pin, FCompilerResultsLog& MessageLog, const UEdGraphSchema_K2* Schema, UClass* SelfClass, bool& bIsSparseProperty);` — Finds a property by name, starting in the specified scope; Validates property type and returns NULL along with emitting an error if there is a mismatch.
- L78 _public prototype_ `static FProperty* FindNamedPropertyInScope(UStruct* Scope, FName PropertyName, bool& bIsSparseProperty, const bool bAllowDeprecated = false);` — Finds a property by name, starting in the specified scope, returning NULL if it's not found
- L81 _public prototype_ `static const UFunction* FindOverriddenImplementableEvent(const FName& EventName, const UClass* Class);` — return function, that overrides BlueprintImplementableEvent with given name in given class (super-classes are not considered)
- L84 _public prototype_ `static FProperty* CreatePrimitiveProperty( FFieldVariant PropertyScope, const FName& ValidatedPropertyName, const FName& PinCategory, const FName& PinSubCategory, UObject* PinSubCategoryObject, UClass* SelfClass, bool bIsWeakPointer, const class UEdGraphSchema_K2* Schema, FCompilerResultsLog& MessageLog);` — Helper function for creating property for primitive types. Used only to create inner peroperties for FArrayProperty, FSetProperty, and FMapProperty:
- L87 _public prototype_ `static FProperty* CreatePropertyOnScope(UStruct* Scope, const FName& PropertyName, const FEdGraphPinType& Type, UClass* SelfClass, EPropertyFlags PropertyFlags, const class UEdGraphSchema_K2* Schema, FCompilerResultsLog& MessageLog, UEdGraphPin* SourcePin = nullptr);` — Creates a property named PropertyName of type PropertyType in the Scope or returns NULL if the type is unknown, but does *not* link that property in
- L94 _public prototype_ `static FFieldVariant CheckPropertyNameOnScope(UStruct* Scope, const FName& PropertyName);` — Checks that the property name isn't taken in the given scope (used by CreatePropertyOnScope()) @return	Ptr to an existing object with that name in the given scope or nullptr if none exists
- L97 _public prototype_ `static TArray<TSet<UEdGraphNode*>> FindUnsortedSeparateExecutionGroups(const TArray<UEdGraphNode*>& Nodes);` — Find groups of nodes, that can be executed separately.
- L101 _private member_ `static uint32 ConsignToOblivionCounter;` — Counter to ensure unique names in the transient package, to avoid GC collection issues with classes and their CDOs
- L103 _public prototype_ `static void CompileDefaultProperties(UClass* Class);`
- L105 _public prototype_ `static void LinkAddedProperty(UStruct* Structure, FProperty* NewProperty);`
- L107 _public prototype_ `static void RemoveObjectRedirectorIfPresent(UObject* Package, const FString& ClassName, UObject* ObjectBeingMovedIn);`
- L110 _public prototype_ `static void ValidateEnumProperties(const UObject* DefaultObject, FCompilerResultsLog& MessageLog);` — checks if enum variables from given object store proper indexes
- L113 _public prototype_ `static bool ValidateSelfCompatibility(const UEdGraphPin* Pin, FKismetFunctionContext& Context);` — checks if the specified pin can default to self
- L116 _public prototype_ `static UEdGraphPin* GenerateAssignmentNodes(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UK2Node* CallBeginSpawnNode, UEdGraphNode* SpawnNode, UEdGraphPin* CallBeginResult, const UClass* ForClass, const UEdGraphPin* CallBeginClassInput = nullptr);` — Create 'set var by name' nodes and hook them up - used to set values when components are added or actor are created at run time. Returns the 'last then' pin of the assignment nodes
- L119 _public prototype_ `static TTuple<UEdGraphPin*, UEdGraphPin*> GenerateFieldNotificationSetNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UEdGraphNode* SourceNode, UEdGraphPin* SelfPin, FProperty* VariableProperty, const FMemberReference& VariableReference, bool bHasLocalRepNotify, bool bShouldFlushDormancyOnSet, bool bIsNetProperty);` — Create node that replace regular setter and use the SetPropertyValueAndBroadcast.
- L122 _public prototype_ `static TTuple<UEdGraphPin*, UEdGraphPin*> GenerateBroadcastFieldNotificationNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UEdGraphNode* SourceNode, FProperty* Property);` — Create node to broadcast a FieldNotification value changed
- L125 _public prototype_ `static void CreateObjectAssignmentStatement(FKismetFunctionContext& Context, UEdGraphNode* Node, FBPTerminal* SrcTerm, FBPTerminal* DstTerm, UEdGraphPin* DstPin = nullptr);` — Create Kismet assignment statement with proper object <-> interface cast
- L128 _public prototype_ `static void ValidateProperEndExecutionPath(FKismetFunctionContext& Context);` — `UE_DEPRECATED(5.4, "ValidateProperEndExecutionPath is deprecated.")`
- L131 _public prototype_ `static void DetectValuesReturnedByRef(const UFunction* Func, const UK2Node * Node, FCompilerResultsLog& MessageLog);` — Generate an error for non-const output parameters
- L134 _public prototype_ `static bool IsPropertyUsesFieldNotificationSetValueAndBroadcast(const FProperty* Property);` — @return true when the property is a BP user variable that should uses UFieldNotificationLibrary::SetPropertyValueAndBroadcast to set its value.
- L136 _public prototype_ `static bool IsStatementReducible(EKismetCompiledStatementType StatementType);`
- L146 _public prototype_ `static bool IsMissingMemberPotentiallyLoading(const UBlueprint* SelfBlueprint, const UStruct* MemberOwner);` — Intended to avoid errors that come from checking for external member (function, variable, etc.) dependencies. This can happen when a Blueprint was saved without having new members compiled in (saving w/out compiling), and a Blueprint that uses those members is compiled-on-load before the uncompiled one. Any valid errors should surface later, when the dependant Blueprint's bytecode is recompiled.
- L149 _public prototype_ `static bool IsIntermediateFunctionGraphTrivial(FName FunctionName, const UEdGraph* FunctionGraph);` — @return true if the graph in question contains only an entry node or only an entry node and a call to its parent if the graph is an override
- L152 _public prototype_ `static void UpdateDependentBlueprints(UBlueprint* BP);` — Add this BP to any BPs that it in
- L155 _public prototype_ `static bool CheckFunctionThreadSafety(const FKismetFunctionContext& InContext, FCompilerResultsLog& InMessageLog, bool InbEmitErrors = true);` — Check the passed-in function to verify its thread safety. This makes sure that it only uses/calls thread-safe functions/nodes.
- L158 _public prototype_ `static bool CheckFunctionCompiledStatementsThreadSafety(const UEdGraphNode* InNode, const UEdGraph* InSourceGraph, const TArray<FBlueprintCompiledStatement*>& InStatements, FCompilerResultsLog& InMessageLog, bool InbEmitErrors = true, TSet<const FBPTerminal*>* InThreadSafeObjectTerms = nullptr);` — Helper function used by CheckFunctionThreadSafety. Split out to allow the ability to examine individual compiled statement lists (e.g. for the ubergraph)
- L165 _public prototype_ `static ConvertibleSignatureMatchResult DoSignaturesHaveConvertibleFloatTypes(const UFunction* SourceFunction, const UFunction* OtherFunction);` — Similar to UFunction::IsSignatureCompatibleWith, but also checks if the function signatures are convertible. For example, if a parameter in SourceFunction is of type float, but its corresponding type in OtherFunction is double, then the function is deemed "convertible". This is primarily used for binding Blueprint functions with native delegate signatures that use float types.

#### class `FNodeHandlingFunctor`  
`class FNodeHandlingFunctor`  
_L171-227_
- L174 _public member_ `class FKismetCompilerContext& CompilerContext;`
- L178 _protected prototype_ `void ResolveAndRegisterScopedTerm(FKismetFunctionContext& Context, UEdGraphPin* Net, TIndirectArray<FBPTerminal>& NetArray);` — Helper function that verifies the variable name referenced by the net exists in the associated scope (either the class being compiled or via an object reference on the Self pin), and then creates/registers a term for that variable access.
- L181 _protected prototype_ `FBlueprintCompiledStatement& GenerateSimpleThenGoto(FKismetFunctionContext& Context, UEdGraphNode& Node, UEdGraphPin* ThenExecPin);` — Generate a goto on the corresponding exec pin
- L184 _protected prototype_ `FBlueprintCompiledStatement& GenerateSimpleThenGoto(FKismetFunctionContext& Context, UEdGraphNode& Node);` — Generate a goto corresponding to the then pin(s)
- L189 _protected prototype_ `bool ValidateAndRegisterNetIfLiteral(FKismetFunctionContext& Context, UEdGraphPin* Net);` — If the net is a literal, it validates the default value and registers it. Returns true if the net is *not* a literal, or if it's a literal that is valid. Returns false only for a bogus literal value.
- L192 _protected prototype_ `virtual FBPTerminal* RegisterLiteral(FKismetFunctionContext& Context, UEdGraphPin* Net);` — Helper to register literal term
- L194 _public function_ `FNodeHandlingFunctor(FKismetCompilerContext& InCompilerContext) : CompilerContext(InCompilerContext)`
- L199 _public prototype_ `virtual ~FNodeHandlingFunctor() = default;`
- L201 _public function_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node)`
- L205 _public function_ `virtual void Transform(FKismetFunctionContext& Context, UEdGraphNode* Node)`
- L209 _public function_ `virtual void RegisterNet(FKismetFunctionContext& Context, UEdGraphPin* Pin)`
- L213 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node);`
- L216 _public function_ `virtual bool RequiresRegisterNetsBeforeScheduling() const` — Returns true if this kind of node needs to be handled in the first pass, prior to execution scheduling (this is only used for function entry and return nodes)
- L226 _public prototype_ `static void SanitizeName(FString& Name);` — Creates a sanitized name. @param [in,out]	Name	The name to modify and make a legal C++ identifier.

#### class `FKCHandler_Passthru`  
`class FKCHandler_Passthru : public FNodeHandlingFunctor`  
_L229-242_
- inherits: `FNodeHandlingFunctor`
- L232 _public function_ `FKCHandler_Passthru(FKismetCompilerContext& InCompilerContext) : FNodeHandlingFunctor(InCompilerContext)`
- L237 _public function_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node)`

#### struct `FNetNameMapping`  
`struct FNetNameMapping`  
_L249-307_
- desc: Map from a name to the number of times it's been 'created' (identical nodes create the same variable names, so they need something appended)
- L254 _public function_ `FString MakeValidName(const UEdGraphNode* Net, const FString& Context = TEXT(""))` — Come up with a valid, unique (within the scope of NetNameMap) name based on an existing Net object and (optional) context. The resulting name is stable across multiple calls if given the same pointer.
- L255 _public function_ `FString MakeValidName(const UEdGraphPin* Net, const FString& Context = TEXT(""))`
- L256 _public function_ `FString MakeValidName(const UObject* Net, const FString& Context = TEXT(""))`
- L259 _private prototype_ `static FString MakeBaseName(const UEdGraphNode* Net);`
- L260 _private prototype_ `static FString MakeBaseName(const UEdGraphPin* Net);`
- L261 _private prototype_ `static FString MakeBaseName(const UObject* Net);`
- L264 _private function_ `template< typename NetType > FString MakeValidNameImpl(NetType Net, const FString& Context)`
- L287 _private function_ `FString GetUniqueName(FString NetName)`
- L305 _private member_ `TMap<const void*, FString> NetToName;`
- L306 _private member_ `TMap<FString, const void*> NameToNet;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API KISMETCOMPILER_API`

### `Source/Editor/KismetCompiler/Public/KismetCompilerModule.h` (Public)


#### class `IBlueprintCompiler`  
`class IBlueprintCompiler`  
_L26-52_
- L29 _public function_ `virtual void PreCompile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions)`
- L34 _public prototype_ `virtual bool CanCompile(const UBlueprint* Blueprint) = 0;`
- L35 _public prototype_ `virtual void Compile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions, FCompilerResultsLog& Results) = 0;`
- L37 _public function_ `virtual void PostCompile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions)`
- L42 _public function_ `virtual bool GetBlueprintTypesForClass(UClass* ParentClass, UClass*& OutBlueprintClass, UClass*& OutBlueprintGeneratedClass) const`
- L50 _protected function_ `virtual void PreCompile(UBlueprint* Blueprint)`
- L51 _protected function_ `virtual void PostCompile(UBlueprint* Blueprint)`

#### class `IKismetCompilerInterface`  
`class IKismetCompilerInterface : public IModuleInterface`  
_L54-106_
- inherits: `IModuleInterface`
- L63 _public prototype_ `virtual void RefreshVariables(UBlueprint* Blueprint)=0;` — Synchronizes Blueprint's GeneratedClass's properties with the NewVariable declarations in the blueprint Used on load to ensure that all properties are present for instances. @param Blueprint The blueprint that may be missing variables
- L71 _public prototype_ `virtual void CompileStructure(class UUserDefinedStruct* Struct, FCompilerResultsLog& Results)=0;` — Compiles a user defined structure. @param	Struct		The structure to compile. @param	Results  	The results log for warnings and errors.
- L78 _public prototype_ `virtual void RecoverCorruptedBlueprint(class UBlueprint* Blueprint)=0;` — Attempts to recover a corrupted blueprint package. @param	Blueprint	The blueprint to recover.
- L85 _public prototype_ `virtual void RemoveBlueprintGeneratedClasses(class UBlueprint* Blueprint)=0;` — Clears the blueprint's generated classes, and consigns them to oblivion @param	Blueprint	The blueprint to clear the classes for
- L90 _public prototype_ `virtual TArray<IBlueprintCompiler*>& GetCompilers() = 0;` — Gets a list of all compilers for blueprints.  You can register new compilers through this list.
- L93 _public prototype_ `virtual void OverrideBPTypeForClass(UClass* Class, TSubclassOf<UBlueprint> BlueprintType) = 0;` — Facilities for establishing mappings between UClasses, UBlueprints, and UBlueprintGenerated Classes
- L95 _public prototype_ `virtual void OverrideBPTypeForClassInEditor(UClass* Class, TSubclassOf<UBlueprint> BlueprintType) = 0;` — `UE_DEPRECATED(5.4, "Conditional overrides in editor have been deprecated - make a new sentinel type if required to keep UBlueprint mappings unambiguous")`
- L96 _public prototype_ `virtual void OverrideBPGCTypeForBPType(TSubclassOf<UBlueprint> BlueprintType, TSubclassOf<UBlueprintGeneratedClass> BPGCType) = 0;`
- L98 _public prototype_ `virtual void ValidateBPAndClassType(UBlueprint* BP, FCompilerResultsLog& OutResults) = 0;`
- L104 _public prototype_ `virtual void GetBlueprintTypesForClass(UClass* ParentClass, UClass*& OutBlueprintClass, UClass*& OutBlueprintGeneratedClass) const = 0;` — Get the blueprint class and generated blueprint class for a particular class type.  Not every blueprint is a normal UBlueprint, like UUserWidget blueprints should be UWidgetBlueprints.
- L105 _public prototype_ `virtual void GetSubclassesWithDifferingBlueprintTypes(UClass* Class, TSet<const UClass*>& OutMismatchedSubclasses) const = 0;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define KISMET_COMPILER_MODULENAME "KismetCompiler"`

### `Source/Editor/KismetCompiler/Public/UserDefinedStructureCompilerUtils.h` (Public)


#### class `FUserDefinedStructureCompilerUtils`  
`class FUserDefinedStructureCompilerUtils`  
_L9-21_
- L13 _public prototype_ `static void CompileStruct(class UUserDefinedStruct* Struct, class FCompilerResultsLog& MessageLog, bool bForceRecompile);` — ASSUMPTION, structure doesn't need to be renamed or removed
- L15 _public prototype_ `static void ReplaceStructWithTempDuplicateByPredicate( UUserDefinedStruct* StructureToReinstance, TFunctionRef<bool(FStructProperty* InStructProperty)> ShouldReplaceStructInStructProperty, TFunctionRef<void(UStruct* InStruct)> PostReplace);`
- L20 _public prototype_ `static void ReplaceStructWithTempDuplicateSafe(UUserDefinedStruct* Struct);`
