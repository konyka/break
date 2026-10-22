# Plugins / UAFAnimNode

- module root: `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode`
- headers: 55; symbols: 1063
- symbol kinds: class=22, enum=5, enumerator=10, externvar=1, function=167, macro=50, member=240, namespace=120, prototype=385, struct=56, typedef=7
- PrivateDependencyModuleNames: ControlRig, Core, CoreUObject, Engine, RigVM, TraceLog, UAFAnimGraph, UAFEditor, UAFUncookedOnly, WorkspaceEditor
- PublicDependencyModuleNames: UAF

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Internal/AnimNode/RigUnit_RunAnimNode_v1.h` (Internal)


#### struct `FUAFAnimNodeReference`  
`struct FUAFAnimNodeReference`  
_L18-23_
- reflection: `USTRUCT()`
- desc: TODO: Remove me once old content has been resaved
- L22 _public member_ `TInstancedStruct<UE::UAF::FUAFAnimNodeData> NodeData;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input, ExcludeBaseStruct))`

#### struct `FRunAnimNodeWorkData_v1`  
`struct FRunAnimNodeWorkData_v1`  
_L26-37_
- reflection: `USTRUCT()`
- L30 _public prototype_ `~FRunAnimNodeWorkData_v1();`
- L32 _public member_ `UE::UAF::FUAFAnimNodePtr AnimNodeInstance;`
- L34 _public member_ `TSharedPtr<UE::UAF::FUAFAnimNodeReferenceCollector> GCReferences;`
- L36 _public member_ `uint64 DebugInstanceId = 0;`

#### struct `FRigUnit_RunAnimNode_v1`  
`struct FRigUnit_RunAnimNode_v1 : public FRigUnit_AnimNextBase`  
_L41-75_
- reflection: `USTRUCT(meta=(Hidden, DisplayName="Run Anim Node (Deprecated)", Category="Anim Node", NodeColor="0, 1, 1", Keywords="Animation, Node, Graph, AnimNode"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Runs an AnimNode
- L45 _public prototype_ `RIGVM_METHOD() void Execute();`
- L50 _public member_ `UE::UAF::FUAFAnimNodeDataEx AnimNode;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input))` — The anim node to run
- L54 _public member_ `int32 LOD = -1;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input))` — LOD to run at. If this is -1 then the reference pose's source LOD will be used
- L58 _public member_ `FAnimNextGraphReferencePose ReferencePose;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input))` — Reference pose
- L62 _public member_ `FName AttributeSet;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input))` — The name of the attribute set to execute with, if 'None' will include everything
- L66 _public member_ `FAnimNextGraphLODPose Result;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Output))` — Pose result
- L70 _public member_ `FRunAnimNodeWorkData_v1 WorkData;` — `UPROPERTY(transient)` — Internal work data
- L74 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UAFANIMNODE_API`

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Internal/AnimNode/RigUnit_RunAnimNode_v2.h` (Internal)


#### struct `FRunAnimNodeWorkData_v2`  
`struct FRunAnimNodeWorkData_v2`  
_L17-28_
- reflection: `USTRUCT()`
- L21 _public prototype_ `~FRunAnimNodeWorkData_v2();`
- L23 _public member_ `UE::UAF::FUAFAnimNodePtr AnimNodeInstance;`
- L25 _public member_ `TSharedPtr<UE::UAF::FUAFAnimNodeReferenceCollector> GCReferences;`
- L27 _public member_ `uint64 DebugInstanceId = 0;`

#### struct `FRigUnit_RunAnimNode_v2`  
`struct FRigUnit_RunAnimNode_v2 : public FRigUnit_AnimNextBase`  
_L32-58_
- reflection: `USTRUCT(meta=(DisplayName="Run Anim Node", Category="Anim Node", NodeColor="0, 1, 1", Keywords="Animation, Node, Graph, AnimNode"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Runs an AnimNode
- L36 _public prototype_ `RIGVM_METHOD() void Execute();`
- L41 _public member_ `UE::UAF::FUAFAnimNodeDataEx AnimNode;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input))` — The anim node to run
- L45 _public member_ `FName AttributeSet;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input))` — The name of the attribute set to execute with, if 'None' will include everything
- L49 _public member_ `FUAFValueBundle Result;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Output))` — Result value
- L53 _public member_ `FRunAnimNodeWorkData_v2 WorkData;` — `UPROPERTY(transient)` — Internal work data
- L57 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UAFANIMNODE_API`

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/IUAFTransitionContainerNode.h` (Public)


#### struct `UE::UAF::IUAFTransitionContainerNode`  
`struct IUAFTransitionContainerNode`  
_L18-26_
- desc: IUAFTransitionContainerNode Interface implemented by Nodes which use transitions, in order to be notified when the transition completes
- L20 _public member_ `static constexpr FUAFAnimNodeInterfaceId InterfaceId = FUAFAnimNodeInterfaceId::MakeFromString(TEXT("IUAF`
- L22 _public prototype_ `virtual ~IUAFTransitionContainerNode() = default;`
- L25 _public prototype_ `virtual void NotifyTransitionComplete(const IUAFTransitionNode& TransitionNode) = 0;` — Called by transitions when they complete

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/IUAFTransitionNode.h` (Public)


#### struct `UE::UAF::IUAFTransitionNode`  
`struct IUAFTransitionNode`  
_L18-66_
- desc: IUAFTransitionNode Interface implemented by blend transitions
- L20 _public member_ `static constexpr FUAFAnimNodeInterfaceId InterfaceId = FUAFAnimNodeInterfaceId::MakeFromString(TEXT("IUAF`
- L22 _public prototype_ `virtual ~IUAFTransitionNode() = default;`
- L25 _public prototype_ `[[nodiscard]] virtual const FUAFAnimNodePtr& GetSource() const = 0;` — Returns the source node we are transitioning away from
- L28 _public prototype_ `[[nodiscard]] virtual const FUAFAnimNodePtr& GetTarget() const = 0;` — Returns the target node we are transitioning towards to
- L32 _public prototype_ `[[nodiscard]] virtual FUAFAnimNodePtr ReleaseSource() = 0;` — Un-parents the source node and returns it Can only be called when the transition has completed as this is used to steal ownership
- L36 _public prototype_ `[[nodiscard]] virtual FUAFAnimNodePtr ReleaseTarget() = 0;` — Un-parents the target node and returns it Can only be called when the transition has completed as this is used to steal ownership
- L39 _public prototype_ `[[nodiscard]] virtual bool IsComplete() const = 0;` — Returns whether or not the transition has completed
- L44 _public function_ `[[nodiscard]] FUAFAnimNodePtr Prune()` — Call Prune on a completed transition to get the unparented Target node Prune will also check if current target is another completed IUAFTransition, and will prune all the way down to a target node which is either not a transition, or not complete

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMNODE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFAnimNode.h` (Public)


#### class `UE::UAF::FUAFAnimNode`  
`class FUAFAnimNode`  
_L29-241_
- desc: FUAFAnimNode An anim node instance
- L35 _public prototype_ `FUAFAnimNode() = delete;` — We prohibit creating an anim node without an update context
- L40 _public prototype_ `void Reset();` — Resets this node to its initial state This must be called when a node is re-used Cannot be called if the node is attached to a parent
- L43 _public prototype_ `[[nodiscard]] const FUAFAnimNodePtr& GetChildAt(int32 ChildIndex) const;` — Returns the child at the specified index
- L46 _public prototype_ `[[nodiscard]] const FUAFAnimNodePtr& GetFirstChild() const;` — Returns the first child
- L49 _public prototype_ `[[nodiscard]] FUAFAnimNode* GetParent() const;` — Returns the node's parent
- L52 _public prototype_ `[[nodiscard]] int32 GetNumChildren() const;` — Returns the number of children held by this node
- L55 _public prototype_ `[[nodiscard]] bool HasChildren() const;` — Returns whether or not this node holds children
- L58 _public prototype_ `[[nodiscard]] const TArray<FUAFAnimNodePtr, TInlineAllocator<2>>& GetChildren() const;` — Returns the list of children held by this node
- L61 _public prototype_ `[[nodiscard]] float GetTotalWeight() const;` — Returns the current total weight factoring in all inherited blend weights
- L64 _public prototype_ `void SetTotalWeight(float Weight);` — Sets the total weight
- L67 _public prototype_ `[[nodiscard]] bool IsBlendingOut() const;` — Returns whether or not we are blending out
- L70 _public prototype_ `void SetIsBlendingOut(bool bIsBlendingOut);` — Sets whether or not we are blending out
- L75 _public prototype_ `[[nodiscard]] bool IsNewlyRelevant() const;` — Returns whether or not we are newly relevant A node is newly relevant the first time it updates If you wish to re-use a node after it has fully blended out, you must first reset it
- L80 _public prototype_ `void HintNewlyRelevant(bool bIsNewlyRelevant);` — Hints that this node is newly relevant This should be used when nodes are manually cached and re-used to hint when they become relevant again Note that if the node is already relevant, it cannot be made irrelevant until it updates
- L83 _public prototype_ `[[nodiscard]] FUAFAnimOp* GetPreAnimOp();` — Returns the AnimOp to perform before our children evaluate theirs
- L84 _public prototype_ `[[nodiscard]] const FUAFAnimOp* GetPreAnimOp() const;`
- L87 _public prototype_ `[[nodiscard]] FUAFAnimOp* GetPostAnimOp();` — Returns the AnimOp to perform after our children evaluate theirs
- L88 _public prototype_ `[[nodiscard]] const FUAFAnimOp* GetPostAnimOp() const;`
- L91 _public prototype_ `template<typename InterfaceType> [[nodiscard]] InterfaceType* GetInterface();` — Returns a pointer to the specified interface or nullptr if the interface is not supported by the current node data
- L97 _public prototype_ `static void AddReferencedObjects(FUAFAnimNode* This, FReferenceCollector& Collector);` — Called when garbage collection requests hard/strong object references @see UObject::AddReferencedObjects
- L100 _public prototype_ `virtual FString GetDebugName() const;`
- L101 _public prototype_ `virtual UStruct* GetDebugStruct() const;`
- L103 _public function_ `uint64 GetDebugInstanceId() const`
- L108 _public function_ `void SetDebugInstanceId(uint64 Id)`
- L116 _public prototype_ `[[nodiscard]] bool HasPreUpdated() const;` — Tests the debug update counters to determine if Pre/PostUpdate has been called or not yet
- L117 _public prototype_ `[[nodiscard]] bool HasPostUpdated() const;`
- L122 _protected prototype_ `explicit FUAFAnimNode(FUAFAnimGraphUpdateContext& UpdateContext);` — Only derived types can construct an anim node
- L125 _protected prototype_ `virtual ~FUAFAnimNode();` — Only a friend or derived type can call the destructor to ensure FUAFAnimNodePtr is used for lifetime management
- L129 _protected prototype_ `template<class AnimNodeType> void InitializeAs(FUAFAnimGraphUpdateContext& UpdateContext);` — Initialization function should be called within the constructor of derived types
- L136 _protected prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext);` — Main update entry point for node instances This function is responsible for updating topology (e.g. managing children) and advancing time/phase Called during the update pass before children have been queued and traversed When choosing whether to use PreUpdate or PostUpdate, favor the former when possible This is 'protected' to ensure that no one attempts to manually update untyped nodes.
- L144 _protected prototype_ `virtual void PostUpdate(FUAFAnimGraphUpdateContext& GraphContext);` — Main update entry point for node instances This function is responsible for updating topology (e.g. managing children) and advancing time/phase Called during the update pass after children have been queued and traversed Note that it is not possible to change the PreAnimOp while in PostUpdate as it has already been queued When choosing whether to use PreUpdate or PostUpdate, favor the former when possible This is 'protected' to ensure that no one attempts to manually update untyped nodes.
- L147 _protected prototype_ `int32 AddChild(FUAFAnimNodePtr&& Child);` — Adds a new child to this node and returns its index
- L148 _protected prototype_ `int32 AddChild(const FUAFAnimNodePtr& Child);`
- L152 _protected prototype_ `bool RemoveChild(const FUAFAnimNodePtr& Child);` — Removes the specified child Returns true on success if the child was found, false otherwise
- L155 _protected prototype_ `void RemoveChildAt(int32 ChildIndex);` — Removes the child at the specified index
- L158 _protected prototype_ `void SetChildAt(int32 ChildIndex, const FUAFAnimNodePtr& Child);` — Sets the child at the specified index
- L162 _protected prototype_ `void SetPreAnimOp(FUAFAnimOp* AnimOp);` — Sets the AnimOp to perform before our children evaluate theirs When choosing whether to use PreAnimOp or PostAnimOp, favor the latter when possible
- L167 _protected prototype_ `void SetPostAnimOp(FUAFAnimOp* AnimOp);` — Sets the AnimOp to perform after our children evaluate theirs When choosing whether to use PreAnimOp or PostAnimOp, favor the latter when possible Must be used by leaf nodes to produce an output
- L170 _protected member_ `uint64 DebugInstanceId = 0;`
- L175 _private prototype_ `void AddRef() const;` — Increments the reference count TRefCountPtr API
- L179 _private prototype_ `void Release() const;` — Decreases the reference count and queues this node for destruction when the count reaches zero TRefCountPtr API
- L183 _private prototype_ `FORCENOINLINE void QueueForDestruction();` — Queues this node for destruction within the current update context Don't inline to avoid code bloat
- L186 _private prototype_ `void ClearParent();` — Clears this node's parent (should only be called by SetChild/AddChild/RemoveChild functions)
- L189 _private prototype_ `void SetParent(FUAFAnimNode* Parent);` — Sets this node's parent (should only be called by SetChild/AddChild functions)
- L193 _private member_ `FUAFAnimNode* Parent = nullptr;` — A pointer to this node's parent This pointer is valid if the node is attached to a parent - do not modify directly, always call SetParent/ClearParent
- L197 _private member_ `TArray<FUAFAnimNodePtr, TInlineAllocator<2>> Children;` — An array of children owned by this node Note that children can be nullptr
- L200 _private member_ `FUAFAnimOp* PreAnimOp = nullptr;` — The AnimOps to perform before and after our children evaluate theirs
- L201 _private member_ `FUAFAnimOp* PostAnimOp = nullptr;`
- L205 _private member_ `float TotalWeight = 0.0f;` — The current total weight factoring in all inherited blend weights Nodes with a single child will automatically propagate this value
- L209 _private member_ `bool bIsBlendingOut : 1 = false;` — Whether or not we are blending out Nodes with a single child will automatically propagate this value
- L213 _private member_ `bool bIsNewlyRelevant : 1 = true;` — Whether or not we are newly relevant Nodes with a single child will automatically propagate this value
- L216 _private member_ `bool bHasAddReferencedObjects : 1 = false;` — Whether or not this node implements AddReferencedObjects(..)
- L220 _private member_ `bool bIsInitialized : 1 = false;` — Whether or not InitializeAs<T>(..) has been called
- L223 _private member_ `mutable bool bIsPendingDestroy : 1 = false;` — Whether or not the last reference was released and we have been queued for destruction
- L226 _private member_ `uint32 PreUpdateCounter = 0;` — Debug counters used to enforce invariants
- L227 _private member_ `uint32 PostUpdateCounter = 0;`
- L233 _private member_ `mutable uint8 ReferenceCount = 1;` — The number of references currently held on this node We only use 8-bits because we don't expect shared ownership semantics over a high number of nodes We are always created with one reference
- L250 _function_ `inline FUAFAnimNode::FUAFAnimNode(FUAFAnimGraphUpdateContext& UpdateContext)`
- L255 _function_ `template<class AnimNodeType> inline void FUAFAnimNode::InitializeAs(FUAFAnimGraphUpdateContext& UpdateContext)`
- L270 _function_ `inline void FUAFAnimNode::AddReferencedObjects(FUAFAnimNode* This, FReferenceCollector& Collector)`
- L275 _function_ `inline bool FUAFAnimNode::HasPreUpdated() const`
- L281 _function_ `inline bool FUAFAnimNode::HasPostUpdated() const`
- L288 _function_ `inline const FUAFAnimNodePtr& FUAFAnimNode::GetChildAt(int32 ChildIndex) const`
- L293 _function_ `inline const FUAFAnimNodePtr& FUAFAnimNode::GetFirstChild() const`
- L298 _function_ `inline FUAFAnimNode* FUAFAnimNode::GetParent() const`
- L303 _function_ `inline int32 FUAFAnimNode::GetNumChildren() const`
- L308 _function_ `inline bool FUAFAnimNode::HasChildren() const`
- L313 _function_ `inline const TArray<FUAFAnimNodePtr, TInlineAllocator<2>>& FUAFAnimNode::GetChildren() const`
- L318 _function_ `inline float FUAFAnimNode::GetTotalWeight() const`
- L323 _function_ `inline void FUAFAnimNode::SetTotalWeight(float Weight)`
- L332 _function_ `inline bool FUAFAnimNode::IsBlendingOut() const`
- L337 _function_ `inline void FUAFAnimNode::SetIsBlendingOut(bool bInIsBlendingOut)`
- L346 _function_ `inline bool FUAFAnimNode::IsNewlyRelevant() const`
- L351 _function_ `inline void FUAFAnimNode::HintNewlyRelevant(bool bInIsNewlyRelevant)`
- L356 _function_ `inline FUAFAnimOp* FUAFAnimNode::GetPreAnimOp()`
- L361 _function_ `inline const FUAFAnimOp* FUAFAnimNode::GetPreAnimOp() const`
- L366 _function_ `inline void FUAFAnimNode::SetPreAnimOp(FUAFAnimOp* AnimOp)`
- L375 _function_ `inline FUAFAnimOp* FUAFAnimNode::GetPostAnimOp()`
- L380 _function_ `inline const FUAFAnimOp* FUAFAnimNode::GetPostAnimOp() const`
- L385 _function_ `inline void FUAFAnimNode::SetPostAnimOp(FUAFAnimOp* AnimOp)`
- L395 _function_ `template<typename InterfaceType> inline InterfaceType* FUAFAnimNode::GetInterface()`
- L401 _function_ `template<typename InterfaceType> inline const InterfaceType* FUAFAnimNode::GetInterface() const`
- L406 _function_ `inline void FUAFAnimNode::AddRef() const`
- L412 _function_ `inline void FUAFAnimNode::Release() const`
- L421 _function_ `inline void FUAFAnimNode::SetParent(FUAFAnimNode* InParent)`
- L427 _function_ `inline void FUAFAnimNode::ClearParent()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UAFANIMNODE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L22 _typedef_ `using FUAFAnimNodePtr = TRefCountPtr<class FUAFAnimNode>;` (scope `UE::UAF`) — Smart pointer to an instance of FUAFAnimNode
- L245 _prototype_ `template<class AnimNodeType, typename... ArgTypes> FUAFAnimNodePtr MakeAnimNode(FUAFAnimGraphUpdateContext& UpdateContext, ArgTypes&&... Args);` (scope `UE::UAF`) — Constructs a new anim node of the specified type with the provided arguments and returns a smart pointer to it
- L433 _function_ `template<class AnimNodeType, typename... ArgTypes> inline FUAFAnimNodePtr MakeAnimNode(FUAFAnimGraphUpdateContext& UpdateContext, ArgTypes&&... Args)` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFAnimNodeData.h` (Public)


#### struct `UE::UAF::FUAFAnimNodeData`  
`struct FUAFAnimNodeData`  
_L22-36_
- reflection: `USTRUCT()`
- desc: FUAFAnimNodeData Base struct for anim node shared data. Node data must live at least as long as node instances that use it.
- L26 _public prototype_ `virtual ~FUAFAnimNodeData() = default;`
- L29 _public prototype_ `[[nodiscard]] virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const;` — Creates a new node instance based on the current node data
- L32 _public prototype_ `template<typename InterfaceType> [[nodiscard]] InterfaceType* GetInterface();` — Returns a pointer to the specified interface or nullptr if the interface is not supported by the current node data
- L35 _public prototype_ `[[nodiscard]] virtual void* GetInterface(FUAFAnimNodeDataInterfaceId Id);`
- L42 _function_ `template <typename InterfaceType> inline InterfaceType* FUAFAnimNodeData::GetInterface()`
- L48 _function_ `template <typename InterfaceType> inline const InterfaceType* FUAFAnimNodeData::GetInterface() const`
- L53 _function_ `inline void* FUAFAnimNodeData::GetInterface(FUAFAnimNodeDataInterfaceId Id)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMNODE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFAnimNodeDataEx.h` (Public)


#### struct `UE::UAF::FUAFAnimNodeDataEx`  
`struct FUAFAnimNodeDataEx`  
_L27-91_
- reflection: `USTRUCT(BlueprintType)`
- desc: FUAFAnimNodeDataEx Encapsulates a base anim node and a list of modifiers to apply to it. This struct has custom details panel tooling to generate an anim node from these.
- L33 _public prototype_ `static FUAFAnimNodeDataEx Make(const TInstancedStruct<FUAFAnimNodeData>& Base, const TArray<TInstancedStruct<FUAFModifierAnimNodeData>>& Modifiers);` — Creates an anim node from a base and a list of modifiers The base node is wrapped by each modifier (index 0 is the first modifier to wrap the base, index 1 wraps the first modifier, etc)
- L37 _public prototype_ `void Build(const TInstancedStruct<FUAFAnimNodeData>& Base, const TArray<TInstancedStruct<FUAFModifierAnimNodeData>>& Modifiers);` — Builds an anim node from a base and a list of modifiers The base node is wrapped by each modifier (index 0 is the first modifier to wrap the base, index 1 wraps the first modifier, etc)
- L40 _public prototype_ `bool IsValid() const;` — Returns whether or not this anim node is valid
- L43 _public prototype_ `const TInstancedStruct<FUAFAnimNodeData>& Get() const;` — Returns the generated anim node
- L48 _public prototype_ `void SetBase(const TInstancedStruct<FUAFAnimNodeData>& Base);` — Sets the base anim node The base will be wrapped by the list of modifiers
- L51 _public prototype_ `TInstancedStruct<FUAFAnimNodeData>& GetBase();` — Returns the base anim node
- L52 _public prototype_ `const TInstancedStruct<FUAFAnimNodeData>& GetBase() const;`
- L56 _public prototype_ `void SetModifiers(const TArray<TInstancedStruct<FUAFModifierAnimNodeData>>& Modifiers);` — Sets the list of modifiers The base node is wrapped by each modifier (index 0 is the first modifier to wrap the base, index 1 wraps the first modifier, etc)
- L59 _public prototype_ `TArray<TInstancedStruct<FUAFModifierAnimNodeData>>& GetModifiers();` — Returns the list of modifiers
- L60 _public prototype_ `const TArray<TInstancedStruct<FUAFModifierAnimNodeData>>& GetModifiers() const;`
- L63 _public prototype_ `void PostSerialize(const FArchive& Ar);` — StructOps API
- L64 _public prototype_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText);`
- L70 _private member_ `TInstancedStruct<FUAFAnimNodeData> BakedNode;` — `UPROPERTY(VisibleAnywhere, Category = "Data", meta = (ExcludeBaseStruct, EditCondition = "bShowBakedNode", EditConditionHides, HideEditConditionToggle))` — Baked anim node generated from the base and modifiers
- L74 _private prototype_ `void Refresh();` — Rebuilds the anim node from the editor data
- L78 _private member_ `TInstancedStruct<FUAFAnimNodeData> BaseNode;` — `UPROPERTY(EditAnywhere, Category = "Data", meta = (ExcludeBaseStruct))` — Base anim node that we'll wrap
- L83 _private member_ `TArray<TInstancedStruct<FUAFModifierAnimNodeData>> ModifierNodes;` — `UPROPERTY(EditAnywhere, Category = "Data", meta = (ExcludeBaseStruct))` — List of modifier anim nodes to apply Modifiers are applied in the order they are added (first wraps the base)
- L87 _private member_ `bool bShowBakedNode = false;` — `UPROPERTY()` — This flag is used to hide the baked node, can be enabled with a cvar
- L96 _function_ `inline FUAFAnimNodeDataEx FUAFAnimNodeDataEx::Make(const TInstancedStruct<FUAFAnimNodeData>& Base, const TArray<TInstancedStruct<FUAFModifierAnimNodeData>>& Modifiers)`
- L103 _function_ `inline bool FUAFAnimNodeDataEx::IsValid() const`
- L108 _function_ `inline const TInstancedStruct<FUAFAnimNodeData>& FUAFAnimNodeDataEx::Get() const`
- L114 _function_ `inline void FUAFAnimNodeDataEx::SetBase(const TInstancedStruct<FUAFAnimNodeData>& Base)`
- L120 _function_ `inline TInstancedStruct<FUAFAnimNodeData>& FUAFAnimNodeDataEx::GetBase()`
- L125 _function_ `inline const TInstancedStruct<FUAFAnimNodeData>& FUAFAnimNodeDataEx::GetBase() const`
- L130 _function_ `inline void FUAFAnimNodeDataEx::SetModifiers(const TArray<TInstancedStruct<FUAFModifierAnimNodeData>>& Modifiers)`
- L136 _function_ `inline TArray<TInstancedStruct<FUAFModifierAnimNodeData>>& FUAFAnimNodeDataEx::GetModifiers()`
- L141 _function_ `inline const TArray<TInstancedStruct<FUAFModifierAnimNodeData>>& FUAFAnimNodeDataEx::GetModifiers() const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<UE::UAF::FUAFAnimNodeDataEx> : TStructOpsTypeTraitsBase2<UE::UAF::FUAFAnimNodeDataEx>`  
_L150-157_
- inherits: `TStructOpsTypeTraitsBase2<UE::UAF::FUAFAnimNodeDataEx>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L153-156_

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMNODE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace AnimNodeEditor` (scope `UE::UAF`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L154 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon099629eb0103`)
- L155 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anon099629eb0103`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFAnimNodeDataInterfaceId.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L10 _typedef_ `using FUAFAnimNodeDataInterfaceId = FConstExprUID;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFAnimNodeFactory.h` (Public)


#### struct `UE::UAF::FUAFAnimNodeFactory`  
`struct FUAFAnimNodeFactory`  
_L18-54_
- desc: The FUAFAnimNodeFactory is used to produce FUAFAnimNode instances from UObjects. This is used in the runtime to produce AnimNodes for animation assets This factory links UObject class types to FUAFAnimNode types.
- L23 _public prototype_ `[[nodiscard]] static FUAFAnimNodePtr CreateUAFAnimNodeFromObject(UObject* Object, FUAFAnimGraphUpdateContext& Context);` — Create a UAFAnimNode instance from the supplied Object
- L26 _public typedef_ `using FAssetInitializer = TFunction<FUAFAnimNodePtr(UObject*, FUAFAnimGraphUpdateContext& Context)>;` — Asset initializer
- L31 _public prototype_ `static FTopLevelAssetPath RegisterAsset(UClass* ObjectClass, FAssetInitializer&& Initializer);` — Register a UAF asset with the factory provides a function which will return a FUAFAnimNodePtr from a UObject @return a FTopLevelAssetPath that can be used to unregister the asset type via UnregisterAsset
- L34 _public prototype_ `static void UnregisterAsset(const FTopLevelAssetPath& InObjectClassPath);` — Unregister an UAF asset with the factory
- L37 _public prototype_ `static bool IsAssetRegistered(const UClass* InAssetClass);` — check if an asset type is registered
- L52 _private prototype_ `static const FInitializerInfo* FindAssetInitializer(const UClass* Class);`
- L53 _private member_ `static TMap<FTopLevelAssetPath, FInitializerInfo> AssetInitializers;`

#### struct `UE::UAF::FUAFAnimNodeFactory::FInitializerInfo`  
`struct FInitializerInfo`  
_L41-49_
- L43 _public function_ `FInitializerInfo(FAssetInitializer Initializer) : Initializer(Initializer)`
- L46 _public prototype_ `FInitializerInfo() = default;`
- L48 _public member_ `FAssetInitializer Initializer;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFAnimNodeInterfaceId.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L10 _typedef_ `using FUAFAnimNodeInterfaceId = FConstExprUID;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFAnimNodeReferenceCollector.h` (Public)


#### class `UE::UAF::FUAFAnimNodeReferenceCollector`  
`class FUAFAnimNodeReferenceCollector : public FGCObject`  
_L15-46_
- inherits: `FGCObject`
- desc: Collects anim nodes that need exposure to GC
- L21 _public typedef_ `using AddReferencedObjectsFn = void(*)(FUAFAnimNode*, FReferenceCollector&);` — We use the same pattern as UObject::AddReferencedObjects and cache a function pointer to the function that will add the references. This is done to avoid an extra indirection when the GC runs.
- L23 _public prototype_ `FUAFAnimNodeReferenceCollector() = default;`
- L24 _public prototype_ `~FUAFAnimNodeReferenceCollector();`
- L28 _public prototype_ `void RegisterWithGC(FUAFAnimNode* AnimNode, AddReferencedObjectsFn GCFn);` — Registers the provided anim node with the GC system Once registered, TUAFAnimNode<T>::AddReferencedObjects will be called on it during GC
- L31 _public prototype_ `void UnregisterWithGC(FUAFAnimNode* AnimNode);` — Unregisters the provided anim node from the GC system
- L34 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject implementation
- L35 _public prototype_ `virtual FString GetReferencerName() const override;`
- L45 _private member_ `TArray<FEntry> AnimNodes;` — List of anim nodes that contain UObject references

#### struct `UE::UAF::FUAFAnimNodeReferenceCollector::FEntry`  
`struct FEntry`  
_L38-42_
- L40 _public member_ `FUAFAnimNode* AnimNode = nullptr;`
- L41 _public member_ `AddReferencedObjectsFn GCFn = nullptr;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFANIMNODE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFAnimNodeTrace.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMNODE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L21 _prototype_ `void TraceAnimOps(const TArray<FUAFAnimOp*>& AnimOps, const FUAFAssetInstance& AssetInstance, const UObject* OuterObject);` (scope `UE::UAF`)
- L22 _prototype_ `void TraceAnimNode(FUAFAnimGraphUpdateContext& Context, FUAFAnimNode* Node);` (scope `UE::UAF`)
- L24 _prototype_ `void TraceAnimNodeValue(FUAFAnimGraphUpdateContext& Context, FUAFAnimNode* Node, FName PropertyName, bool Value);` (scope `UE::UAF`)
- L25 _prototype_ `void TraceAnimNodeValue(FUAFAnimGraphUpdateContext& Context, FUAFAnimNode* Node, FName PropertyName, double Value);` (scope `UE::UAF`)
- L26 _prototype_ `void TraceAnimNodeValue(FUAFAnimGraphUpdateContext& Context, FUAFAnimNode* Node, FName PropertyName, const UObject* Value);` (scope `UE::UAF`)
- L27 _prototype_ `void TraceAnimNodeValue(FUAFAnimGraphUpdateContext& Context, FUAFAnimNode* Node, FName PropertyName, FStructView Value);` (scope `UE::UAF`)
- L30 _macro_ `#define UAF_TRACE_ANIMOPS(AnimOps, AssetInstance, Object) UE::UAF::TraceAnimOps(AnimOps, AssetInstance, Object);`
- L31 _macro_ `#define UAF_TRACE_ANIMNODE(UpdateContext, Node) UE::UAF::TraceAnimNode(UpdateContext, Node);`
- L32 _macro_ `#define UAF_TRACE_ANIMNODE_VALUE(UpdateContext, Node, Name, Value) UE::UAF::TraceAnimNodeValue(UpdateContext, Node, Name, Value);`
- L36 _macro_ `#define UAF_TRACE_ANIMOPS(AnimOps, AssetInstance, Object)`
- L37 _macro_ `#define UAF_TRACE_ANIMNODE(UpdateContext, Node)`
- L38 _macro_ `#define UAF_TRACE_ANIMNODE_VALUE(UpdateContext, Node, Name, Value)`

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFAnimNodeUpdate.h` (Public)


#### class `UE::UAF::FUAFAnimGraphUpdateContext`  
`class FUAFAnimGraphUpdateContext`  
_L37-118_
- desc: FUAFAnimGraphUpdateContext Contains the necessary machinery for traversal during the update pass.
- L42 _public prototype_ `FUAFAnimGraphUpdateContext(UObject* HostObject, FUAFAssetInstance* VariablesOwner, uint64 DebugOuterInstanceId, FUAFAnimNodeReferenceCollector& GCReferences, float DeltaTime);`
- L43 _public prototype_ `~FUAFAnimGraphUpdateContext();`
- L46 _public prototype_ `[[nodiscard]] static FUAFAnimGraphUpdateContext* GetCurrentFromTLS();` — Returns the current update context in use on this thread or nullptr if none are within our current scope
- L49 _public prototype_ `[[nodiscard]] FUAFAssetInstance* GetVariablesOwner();` — Returns the UAF asset that owns the shared variables
- L52 _public prototype_ `[[nodiscard]] UObject* GetHostObject();` — Returns the object that hosts the current graph
- L55 _public prototype_ `[[nodiscard]] FUAFAnimNodeReferenceCollector& GetGCReferences();` — Returns a reference collector for anim nodes that need exposure to GC
- L58 _public prototype_ `[[nodiscard]] float GetDeltaTime() const;` — Returns how much time should the update pass advance by factoring in the current play rate scaling
- L61 _public prototype_ `[[nodiscard]] float GetUpdateDeltaTime() const;` — Returns how much time should the update pass advance by
- L64 _public prototype_ `[[nodiscard]] float GetPlayRate() const;` — Returns the currently applied play rate when computing the delta time
- L67 _public prototype_ `void PushPlayRate(float PlayRate);` — Pushes a new play rate scale on top of the stack
- L70 _public prototype_ `void PopPlayRate();` — Pops the most recent play rate scale from the top of the stack
- L74 _public prototype_ `[[nodiscard]] uint32 GetUpdateCounter() const;` — Debug counter used to enforce invariants
- L78 _public function_ `uint64 GetOuterDebugInstanceId()`
- L84 _private prototype_ `void QueueForDestruction(FUAFAnimNode* AnimNode);`
- L86 _private member_ `FUAFAnimGraphUpdateContext* PreviousContext = nullptr;`
- L88 _private member_ `UObject* HostObject = nullptr;`
- L89 _private member_ `FUAFAssetInstance* VariablesOwner = nullptr;`
- L92 _private member_ `TArray<float> PreviousPlayRateStack;` — A stack of previous play rates
- L95 _private member_ `float CurrentPlayRate = 1.0f;` — The currently active play rate
- L98 _private member_ `float DeltaTime = 0.0f;` — The delta time as currently scaled by the play rate
- L101 _private member_ `float UpdateDeltaTime = 0.0f;` — The unscaled delta time used by the update pass
- L103 _private member_ `FUAFAnimNodeReferenceCollector& GCReferences;`
- L105 _private member_ `TArray<FUAFAnimNode*> NodesPendingDestruction;`
- L109 _private member_ `uint32 UpdateCounter = 0;` — Debug counter used to enforce invariants
- L113 _private member_ `uint64 OuterDebugInstanceId;`
- L185 _function_ `inline FUAFAssetInstance* FUAFAnimGraphUpdateContext::GetVariablesOwner()`
- L190 _function_ `inline UObject* FUAFAnimGraphUpdateContext::GetHostObject()`
- L195 _function_ `inline FUAFAnimNodeReferenceCollector& FUAFAnimGraphUpdateContext::GetGCReferences()`
- L200 _function_ `inline float FUAFAnimGraphUpdateContext::GetDeltaTime() const`
- L205 _function_ `inline float FUAFAnimGraphUpdateContext::GetUpdateDeltaTime() const`
- L210 _function_ `inline float FUAFAnimGraphUpdateContext::GetPlayRate() const`
- L216 _function_ `inline uint32 FUAFAnimGraphUpdateContext::GetUpdateCounter() const`

#### class `UE::UAF::FUAFEvaluateValuesArgs`  
`class FUAFEvaluateValuesArgs`  
_L129-165_
- desc: FUAFEvaluateValuesArgs Contains the necessary machinery for evaluating a list of AnimOps to produce a set of output values.
- L134 _public prototype_ `FUAFEvaluateValuesArgs(UAbstractSkeletonSetBinding& SkeletonSetBinding, FName SkeletonSetName, USkeletalMesh* SkeletalMesh, int32 LOD, const TArray<FUAFAnimOp*>& AnimOps, const FReferencePose& ReferencePose);`
- L137 _public prototype_ `[[nodiscard]] const TArray<FUAFAnimOp*>& GetAnimOps() const;` — Returns the list of AnimOps used to produce our output values
- L140 _public prototype_ `[[nodiscard]] const FReferencePose& GetReferencePose() const;` — Returns the reference pose used to produce our output values
- L143 _public prototype_ `[[nodiscard]] int32 GetLOD() const;` — Returns the current LOD used to produce our output values
- L146 _public prototype_ `[[nodiscard]] UAbstractSkeletonSetBinding* GetSkeletonSetBinding() const;` — Returns the abstract skeleton set binding asset used to produce our output values
- L149 _public prototype_ `[[nodiscard]] FName GetSkeletonSetName() const;` — Returns the abstract skeleton set name used to produce our output values
- L152 _public prototype_ `[[nodiscard]] USkeletalMesh* GetSkeletalMesh() const;` — Returns the skeletal mesh used to produce our output values
- L155 _private member_ `const FReferencePose& ReferencePose;`
- L156 _private member_ `const TArray<FUAFAnimOp*>& AnimOps;`
- L158 _private member_ `UAbstractSkeletonSetBinding* SkeletonSetBinding = nullptr;`
- L159 _private member_ `USkeletalMesh* SkeletalMesh = nullptr;`
- L160 _private member_ `FName SkeletonSetName;`
- L162 _private member_ `int32 LOD = 0;`
- L222 _function_ `inline const TArray<FUAFAnimOp*>& FUAFEvaluateValuesArgs::GetAnimOps() const`
- L227 _function_ `inline const FReferencePose& FUAFEvaluateValuesArgs::GetReferencePose() const`
- L232 _function_ `inline int32 FUAFEvaluateValuesArgs::GetLOD() const`
- L237 _function_ `inline UAbstractSkeletonSetBinding* FUAFEvaluateValuesArgs::GetSkeletonSetBinding() const`
- L242 _function_ `inline FName FUAFEvaluateValuesArgs::GetSkeletonSetName() const`
- L247 _function_ `inline USkeletalMesh* FUAFEvaluateValuesArgs::GetSkeletalMesh() const`

#### struct `UE::UAF::FUAFSyncContributor`  
`struct FUAFSyncContributor`  
_L174-177_
- desc: Encapsulates a phase synchronization contributor

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMNODE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::UAF`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace UAF` (scope `UE`)
- L122 _prototype_ `TArray<FUAFAnimOp*> UpdateGraph(FUAFAnimGraphUpdateContext& UpdateContext, FUAFAnimNode& RootNode);` (scope `UE::UAF`) — Updates the specified animation graph and advances time forward This populates a list of AnimOps
- L168 _prototype_ `void EvaluateValues(const FUAFEvaluateValuesArgs& Args, FAnimNextGraphLODPose& OutputValues);` (scope `UE::UAF`) — Evaluates the specified AnimOps to produce our value bundle (pose, curves, attributes, etc)
- L171 _prototype_ `TArray<FAnimNotifyEventReference> EvaluateNotifies(const TArray<FUAFAnimOp*>& AnimOps);` (scope `UE::UAF`) — Evaluates the specified AnimOps to produce a list of notifies
- L180 _prototype_ `TArray<FUAFSyncContributor> EvaluateSyncContributors(const TArray<FUAFAnimOp*>& AnimOps);` (scope `UE::UAF`) — Evaluates the specified AnimOps to produce a list of phase synchronization contributors

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFGraphFactoryAssetAnimNodeFactory.h` (Public)


#### struct `UE::UAF::FUAFGraphFactoryAssetAnimNodeFactory`  
`struct FUAFGraphFactoryAssetAnimNodeFactory`  
_L20-55_
- desc: The FUAFAnimNodeFactory is used to produce FUAFAnimNode instances from FUAFGraphFactoryAsset structs. This is primarily for compatibility between FUAFAnimNode, and Trait Graph systems, and in future FUAFGraphFactoryAsset should be replaced by FUAFAnimNodeData This factory links UObject class types to FUAFAnimNode types.
- L25 _public prototype_ `[[nodiscard]] static FUAFAnimNodePtr CreateUAFAnimNodeFromObject(TConstStructView<FUAFGraphFactoryAsset>, FUAFAnimGraphUpdateContext& Context);` — Create a UAFAnimNode instance from the supplied Struct
- L28 _public typedef_ `using FAssetInitializer = TFunction<FUAFAnimNodePtr(TConstStructView<FUAFGraphFactoryAsset>, FUAFAnimGraphUpdateContext& Context)>;` — Asset initializer
- L33 _public prototype_ `static FTopLevelAssetPath RegisterStruct(TSubScriptStructOf<FUAFGraphFactoryAsset>, FAssetInitializer&& Initializer);` — Register a Struct with the factory provides a function which will return a FUAFAnimNodePtr from a FUAFGraphFactoryAsset @return a FTopLevelAssetPath that can be used to unregister the asset type via UnregisterAsset
- L36 _public prototype_ `static void UnregisterStruct(const FTopLevelAssetPath& InStructPath);` — Unregister an UAF asset with the factory
- L39 _public prototype_ `static bool IsStructRegistered(TSubScriptStructOf<FUAFGraphFactoryAsset> InAssetClass);` — check if an asset type is registered
- L53 _private prototype_ `static const FInitializerInfo* FindAssetInitializer(const UStruct* Struct);`
- L54 _private member_ `static TMap<FTopLevelAssetPath, FInitializerInfo> AssetInitializers;`

#### struct `UE::UAF::FUAFGraphFactoryAssetAnimNodeFactory::FInitializerInfo`  
`struct FInitializerInfo`  
_L43-51_
- L45 _public function_ `FInitializerInfo(FAssetInitializer Initializer) : Initializer(Initializer)`
- L48 _public prototype_ `FInitializerInfo() = default;`
- L50 _public member_ `FAssetInitializer Initializer;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFInlineAnimNode.h` (Public)


#### class `UE::UAF::TUAFInlineAnimNode`  
`template <class AnimNodeType> class TUAFInlineAnimNode`  
_L21-36_
- desc: TUAFInlineAnimNode Wraps an anim node to allow their usage inline withour incurring an extra heap allocation. This is suitable when a node knows the type of its child and it can be hardcoded.
- L24 _public prototype_ `explicit TUAFInlineAnimNode(FUAFAnimGraphUpdateContext& Context);`
- L27 _public prototype_ `[[nodiscard]] AnimNodeType* Get();` — Returns a mutable pointer to the wrapped anim node
- L30 _public prototype_ `[[nodiscard]] AnimNodeType* operator->();` — Indirection operator to facilitate usage
- L31 _public prototype_ `[[nodiscard]] const AnimNodeType* operator->() const;`
- L35 _private member_ `AnimNodeType Node;` — The inline anim node we wrap
- L42 _function_ `template <class AnimNodeType> inline TUAFInlineAnimNode<AnimNodeType>::TUAFInlineAnimNode(FUAFAnimGraphUpdateContext& Context) : Node(Context)`
- L50 _function_ `template <class AnimNodeType> inline AnimNodeType* TUAFInlineAnimNode<AnimNodeType>::Get()`
- L56 _function_ `template <class AnimNodeType> inline AnimNodeType* TUAFInlineAnimNode<AnimNodeType>::operator->()`
- L62 _function_ `template <class AnimNodeType> inline const AnimNodeType* TUAFInlineAnimNode<AnimNodeType>::operator->() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFModifierAnimNode.h` (Public)


#### struct `UE::UAF::FUAFModifierAnimNode`  
`struct FUAFModifierAnimNode : public FUAFAnimNode`  
_L20-52_
- inherits: `FUAFAnimNode`
- desc: FUAFModifierAnimNode Base struct for modifier anim node instance data. Modifiers have a single child that they wrap.
- L23 _public prototype_ `virtual void* GetInterface(FUAFAnimNodeInterfaceId Id) override;` — FUAFAnimNode impl
- L26 _public prototype_ `bool HasChild() const;` — Returns whether or not this modifier has a valid child
- L29 _public prototype_ `const FUAFAnimNodePtr& GetChild() const;` — Returns the modifier child, can be an invalid pointer if no child has been initialized
- L32 _protected prototype_ `explicit FUAFModifierAnimNode(FUAFAnimGraphUpdateContext& Context);`
- L35 _protected prototype_ `void InitializeModifier(FUAFAnimGraphUpdateContext& Context, const FUAFModifierAnimNodeData& ModifierData);` — Initializes the modifier with the specified child
- L36 _protected prototype_ `void InitializeModifier(FUAFAnimGraphUpdateContext& Context, const TInstancedStruct<FUAFAnimNodeData>& Child);`
- L37 _protected prototype_ `void InitializeModifier(FUAFAnimGraphUpdateContext& Context, const FUAFAnimNodePtr& Child);`
- L40 _protected prototype_ `void SetChild(const FUAFAnimNodePtr& NewChild);` — Sets the modifier child
- L57 _function_ `inline bool FUAFModifierAnimNode::HasChild() const`
- L62 _function_ `inline const FUAFAnimNodePtr& FUAFModifierAnimNode::GetChild() const`
- L67 _function_ `inline void FUAFModifierAnimNode::SetChild(const FUAFAnimNodePtr& NewChild)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFANIMNODE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFModifierAnimNodeData.h` (Public)


#### struct `UE::UAF::FUAFModifierAnimNodeData`  
`struct FUAFModifierAnimNodeData : public FUAFAnimNodeData`  
_L19-36_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimNodeData`
- desc: FUAFModifierAnimNodeData Base struct for modifier anim node shared data. Modifiers have a single child that they wrap. Allows for special handling in details panel visualization.
- L24 _public member_ `TInstancedStruct<FUAFAnimNodeData> Child;` — `UPROPERTY(EditAnywhere, Category = "Data", meta = (ExcludeBaseStruct, EditCondition = "bShowChildren", EditConditionHides, HideEditConditionToggle))`
- L26 _public prototype_ `[[nodiscard]] virtual void* GetInterface(FUAFAnimNodeDataInterfaceId Id);`
- L32 _private member_ `bool bShowChildren = true;` — `UPROPERTY()` — This flag is used to hide child nodes within the editor details panel under certain authoring scenarios
- L41 _function_ `inline void* FUAFModifierAnimNodeData::GetInterface(FUAFAnimNodeDataInterfaceId Id)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodeCore/UAFTransitionNodeData.h` (Public)


#### struct `UE::UAF::FUAFTransitionNodeData`  
`struct FUAFTransitionNodeData`  
_L20-27_
- reflection: `USTRUCT(meta = (Hidden))`
- desc: FUAFTransitionNodeData Base structure for blend transition shared data
- L24 _public prototype_ `virtual ~FUAFTransitionNodeData() = default;`
- L26 _public prototype_ `[[nodiscard]] virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context, FUAFAnimNodePtr Source, FUAFAnimNodePtr Target) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMNODE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/IUAFAnimNodeDataHasAsset.h` (Public)


#### struct `UE::UAF::IUAFAnimNodeDataHasAsset`  
`struct IUAFAnimNodeDataHasAsset`  
_L10-16_
- L12 _public member_ `static constexpr FUAFAnimNodeDataInterfaceId InterfaceId = FUAFAnimNodeDataInterfaceId::MakeFromString(TEXT("IUAF`
- L14 _public prototype_ `virtual ~IUAFAnimNodeDataHasAsset() = default;`
- L15 _public prototype_ `[[nodiscard]] virtual UObject* GetAsset() const = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/IUAFAnimNodeTimeline.h` (Public)


#### struct `UE::UAF::IUAFAnimNodeTimeline`  
`struct IUAFAnimNodeTimeline`  
_L12-22_
- L14 _public member_ `static constexpr FUAFAnimNodeInterfaceId InterfaceId = FUAFAnimNodeInterfaceId::MakeFromString(TEXT("IUAF`
- L16 _public prototype_ `virtual ~IUAFAnimNodeTimeline() = default;`
- L17 _public prototype_ `[[nodiscard]] virtual float GetCurrentTime() const = 0;`
- L18 _public prototype_ `[[nodiscard]] virtual float GetLength() const = 0;`
- L19 _public prototype_ `[[nodiscard]] virtual bool IsLooping() const = 0;`
- L20 _public prototype_ `virtual void SetCurrentTime(float CurrentTime) = 0;`
- L21 _public prototype_ `[[nodiscard]] virtual ETypeAdvanceAnim GetTimeAdvanceResult() const = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/IUAFRootMotionProvider.h` (Public)


#### struct `UE::UAF::IUAFRootMotionProvider`  
`struct IUAFRootMotionProvider`  
_L12-19_
- L14 _public member_ `static constexpr FUAFAnimNodeInterfaceId InterfaceId = FUAFAnimNodeInterfaceId::MakeFromString(TEXT("IUAF`
- L16 _public prototype_ `virtual ~IUAFRootMotionProvider() = default;`
- L18 _public prototype_ `[[nodiscard]] virtual FTransform ExtractRootMotion(float StartTime, float DeltaTime, bool AllowLooping) const = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/InputValueAnimNode.h` (Public)


#### struct `UE::UAF::FUAFInputValueAnimOp`  
`struct FUAFInputValueAnimOp : public FUAFAnimOp`  
_L31-52_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- desc: FUAFInputValueAnimOp A leaf AnimOp that pushes a cached value bundle or LOD pose onto the evaluation stack. The cached pointers are set by FUAFInputValueAnimNode during PreUpdate because variable access is only available during the update phase, not during the evaluation phase. If no data is available, an empty bundle (reference pose) is pushed instead.
- L36 _public prototype_ `FUAFInputValueAnimOp();`
- L38 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;`
- L44 _public member_ `const FValueBundle* CachedBundle = nullptr;` — Cached data set by FUAFInputValueAnimNode::PreUpdate each frame. Non-owning pointers, only valid for the current evaluation cycle.
- L45 _public member_ `const FAnimNextGraphLODPose* CachedLODPose = nullptr;`
- L46 _public member_ `const TReferencePose<FDefaultAllocator, FDefaultSetAllocator>* TargetRefPose = nullptr;`
- L49 _public prototype_ `static void ConvertLODPoseToValueBundle(const FAnimNextGraphLODPose& InputPose, const TReferencePose<FDefaultAllocator, FDefaultSetAllocator>* TargetRefPose, FPoseValueBundleStack& OutValueBundle);` — Converts an FAnimNextGraphLODPose into a FValueBundleStack, with optional skeleton remapping.

#### struct `UE::UAF::FUAFInputValueAnimNodeData`  
`struct FUAFInputValueAnimNodeData : public FUAFAnimNodeData`  
_L59-68_
- reflection: `USTRUCT(DisplayName = "Input Value")`
- inherits: `FUAFAnimNodeData`
- desc: FUAFInputValueAnimNodeData Serializable data for the input value anim node.
- L65 _public member_ `FAnimNextVariableReference Input;` — `UPROPERTY(EditAnywhere, Category = "Input Value", meta = (AllowedType = FUAFValueBundle))` — The graph variable to read the input value bundle from.
- L67 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;`

#### struct `UE::UAF::FUAFInputValueAnimNode`  
`struct FUAFInputValueAnimNode : public FUAFAnimNode`  
_L74-93_
- inherits: `FUAFAnimNode`
- desc: FUAFInputValueAnimNode An AnimNode leaf that reads a FUAFValueBundle from a graph variable during PreUpdate and pushes it onto the evaluation stack via FUAFInputValueAnimOp.
- L76 _public prototype_ `FUAFInputValueAnimNode(FUAFAnimGraphUpdateContext& Context, const FUAFInputValueAnimNodeData& InData);`
- L79 _public function_ `virtual void* GetInterface(FUAFAnimNodeInterfaceId Id) override` — FUAFAnimNode interface
- L80 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;`
- L83 _public prototype_ `virtual FString GetDebugName() const override;`
- L84 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L89 _private member_ `FUAFInputValueAnimOp InputValueOp;` — The AnimOp that pushes the cached bundle onto the eval stack.
- L92 _private member_ `FAnimNextVariableReference VariableReference;` — Variable reference to read from.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API UAFANIMNODE_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/UAFApplyAdditive.h` (Public)


#### struct `UE::UAF::FUAFApplyAdditiveData`  
`struct FUAFApplyAdditiveData : public FUAFAnimNodeData`  
_L20-41_
- reflection: `USTRUCT(DisplayName = "Apply Additive")`
- inherits: `FUAFAnimNodeData`
- desc: Node to apply an additive animation onto a base animation Optionally can use a blend mask for partial application of the additive
- L26 _public member_ `TInstancedStruct<FUAFAnimNodeData> BaseNode;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — Node providing the base animation
- L30 _public member_ `TInstancedStruct<FUAFAnimNodeData> AdditiveNode;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — Node providing the additive animation
- L34 _public member_ `FBindableFloat AdditiveWeight = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — How much of the additive to apply to the base
- L38 _public member_ `TObjectPtr<UUAFBlendMask> BlendMask = nullptr;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — Optional blend mask to mask the additive with
- L40 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;`

#### class `UE::UAF::FUAFApplyAdditiveNode`  
`class FUAFApplyAdditiveNode : public FUAFAnimNode`  
_L44-67_
- inherits: `FUAFAnimNode`
- L47 _public prototype_ `explicit FUAFApplyAdditiveNode(FUAFAnimGraphUpdateContext& Context, const FUAFApplyAdditiveData& InData);`
- L50 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;` — FUAFAnimNode impl
- L51 _public prototype_ `virtual void* GetInterface(FUAFAnimNodeInterfaceId Id) override;`
- L52 _public prototype_ `static void AddReferencedObjects(FUAFAnimNode* This, FReferenceCollector& Collector);`
- L55 _public prototype_ `virtual FString GetDebugName() const override;`
- L56 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L60 _private member_ `static constexpr int32 BaseChildIndex = 0;`
- L61 _private member_ `static constexpr int32 AdditiveChildIndex = 1;`
- L64 _private member_ `const FUAFApplyAdditiveData& Data;` — Ptr to the nodes data - used to retrieve properties and evaluate bound values
- L66 _private member_ `FUAFApplyAdditiveAnimOp AdditiveAnimOp;` — AnimOp for this node - performs the actual animation operations

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UAFANIMNODE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/UAFBlendByBoolNode.h` (Public)


#### enum `UE::UAF::EBlendByBoolEvaluationFrequency`  
`enum class EBlendByBoolEvaluationFrequency`  
_L17-23_
- reflection: `UENUM()`
- desc: todo, since this is a common pattern this enum should probably be shared
- L20 _public enumerator_ `OnCreate` — Create a Node Instance of the appropriate child at creation time
- L22 _public enumerator_ `OnUpdate` — Check the input bool every frame, and when its value changes, transition to the appropriate child node

#### struct `UE::UAF::FUAFBlendByBoolNodeData`  
`struct FUAFBlendByBoolNodeData : public FUAFAnimNodeData`  
_L27-56_
- reflection: `USTRUCT(DisplayName = "Blend By Bool")`
- inherits: `FUAFAnimNodeData`
- desc: BlendByBool Anim Node selects between two child nodes based on a bool
- L36 _public member_ `FBindableBool BoolValue;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — Bool value used to select between TrueNode and FalseNode. Bind to a UAF bool variable at runtime by setting the Binding field.
- L40 _public member_ `EBlendByBoolEvaluationFrequency EvaluationFrequency = EBlendByBoolEvaluationFrequency::OnUpdate;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — Evaluation Frequency: should we select the appropriate child once at creation time, or every frame.
- L44 _public member_ `FUAFAnimNodeDataEx TrueNode;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — Child Node to instantiate if input bool is true
- L48 _public member_ `FUAFAnimNodeDataEx FalseNode;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — Child Node to instantiate if input bool is false
- L52 _public member_ `TInstancedStruct<FUAFTransitionNodeData> Transition;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — Transition and blend data for transitioning between child nodes
- L55 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;` — FUAFAnimNodeData impl

#### struct `UE::UAF::FUAFBlendByBoolNode`  
`struct FUAFBlendByBoolNode : public FUAFBlendStack`  
_L59-74_
- inherits: `FUAFBlendStack`
- desc: BlendByBool Instance
- L61 _public prototype_ `explicit FUAFBlendByBoolNode(FUAFAnimGraphUpdateContext& Context, const FUAFBlendByBoolNodeData* InData);`
- L64 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;` — FUAFAnimNode impl
- L67 _public prototype_ `virtual FString GetDebugName() const override;`
- L68 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L72 _private member_ `const FUAFBlendByBoolNodeData* Data = nullptr;`
- L73 _private member_ `bool bCurrentValue = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMNODE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/UAFBlendProfileTransition.h` (Public)


#### struct `UE::UAF::FUAFBlendProfileTransitionData`  
`struct FUAFBlendProfileTransitionData : public FUAFSimpleTransitionData`  
_L18-27_
- reflection: `USTRUCT(DisplayName = "Blend Profile Transition")`
- inherits: `FUAFSimpleTransitionData`
- L23 _public member_ `TObjectPtr<UUAFBlendProfile> BlendProfile;` — `UPROPERTY(EditAnywhere, Category = Blending)`
- L26 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context, FUAFAnimNodePtr Source, FUAFAnimNodePtr Target) const override;` — FUAFTransitionNodeData impl

#### class `UE::UAF::FUAFBlendProfileTransition`  
`class FUAFBlendProfileTransition : public FUAFTimedTransition`  
_L29-51_
- inherits: `FUAFTimedTransition`
- L32 _public prototype_ `FUAFBlendProfileTransition() = delete;`
- L33 _public prototype_ `FUAFBlendProfileTransition( FUAFAnimGraphUpdateContext& Context, FUAFAnimNodePtr InSource, FUAFAnimNodePtr InTarget, TNonNullPtr<UUAFBlendProfile> InBlendProfile, float InBaseDuration, EAlphaBlendOption InBlendOption);`
- L42 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;` — FUAFAnimNode impl
- L45 _public prototype_ `virtual FString GetDebugName() const override;`
- L46 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L50 _protected member_ `FUAFBlendTwoPerValueAnimOp BlendAnimOp;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMNODE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/UAFBlendStack.h` (Public)


#### class `UE::UAF::FUAFBlendStack`  
`class FUAFBlendStack : public FUAFAnimNode, public IUAFTransitionContainerNode`  
_L24-67_
- inherits: `FUAFAnimNode,IUAFTransitionContainerNode`
- L27 _public prototype_ `FUAFBlendStack(FUAFAnimGraphUpdateContext& Context);`
- L30 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& Context) override;` — FAnimNode
- L31 _public prototype_ `virtual void* GetInterface(FUAFAnimNodeInterfaceId Id) override;`
- L34 _public prototype_ `virtual void NotifyTransitionComplete(const IUAFTransitionNode& TransitionNode) override;` — IUAFTransitionContainerNode interface
- L37 _public prototype_ `void TransitionTo(FUAFAnimGraphUpdateContext& Context, FUAFAnimNode* TargetNodeData, const FUAFTransitionNodeData* TransitionData = nullptr);` — Trigger blend to new node instance
- L40 _public prototype_ `bool HasValidChild() const;` — returns true if the BlendStack has a valid child node
- L43 _public prototype_ `virtual FString GetDebugName() const override;`
- L44 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L48 _protected prototype_ `const FUAFAnimNodePtr& GetChild() const;`
- L49 _protected prototype_ `FUAFAnimNodePtr ReleaseChild();`
- L50 _protected prototype_ `void SetChild(const FUAFAnimNodePtr& NewChild);`
- L53 _protected prototype_ `void ValidateSingleChild();` — if there is no valid child, add a Reference Pose Op, if there is a valid child clear Op
- L57 _private prototype_ `void PruneTransitions();` — if the contained blend finished last update, replace it with it's target node
- L66 _private member_ `bool bTransitionCompleted = false;`
- L69 _function_ `inline bool FUAFBlendStack::HasValidChild() const`
- L74 _function_ `inline const FUAFAnimNodePtr& FUAFBlendStack::GetChild() const`
- L79 _function_ `inline FUAFAnimNodePtr FUAFBlendStack::ReleaseChild()`
- L86 _function_ `inline void FUAFBlendStack::SetChild(const FUAFAnimNodePtr& NewChild)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/UAFMakeDynamicAdditive.h` (Public)


#### struct `UE::UAF::FUAFMakeDynamicAdditiveData`  
`struct FUAFMakeDynamicAdditiveData : public FUAFAnimNodeData`  
_L20-37_
- reflection: `USTRUCT(DisplayName = "Make Dynamic Additive")`
- inherits: `FUAFAnimNodeData`
- desc: Node to generate an additive animation from Base and Source poses. The output is an additive pose. Additive =  (Source - Base). Generates an additive identity in case of a bad content setup.
- L26 _public member_ `TInstancedStruct<FUAFAnimNodeData> BaseNode;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — Node providing the base (reference) animation
- L30 _public member_ `TInstancedStruct<FUAFAnimNodeData> SourceNode;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — Node providing the Source animation to turn into an additive
- L34 _public member_ `bool bMeshSpaceAdditive = false;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — Whether to compute the additive delta in mesh space (rotation only).
- L36 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;`

#### class `UE::UAF::FUAFMakeDynamicAdditiveNode`  
`class FUAFMakeDynamicAdditiveNode : public FUAFAnimNode`  
_L39-60_
- inherits: `FUAFAnimNode`
- L42 _public prototype_ `explicit FUAFMakeDynamicAdditiveNode(FUAFAnimGraphUpdateContext& Context, const FUAFMakeDynamicAdditiveData& InData);`
- L45 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;` — FUAFAnimNode impl
- L46 _public prototype_ `virtual void* GetInterface(FUAFAnimNodeInterfaceId Id) override;`
- L47 _public prototype_ `static void AddReferencedObjects(FUAFAnimNode* This, FReferenceCollector& Collector);`
- L50 _public prototype_ `virtual FString GetDebugName() const override;`
- L51 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L55 _private member_ `static constexpr int32 BaseChildIndex = 0;`
- L56 _private member_ `static constexpr int32 SourceChildIndex = 1;`
- L58 _private member_ `const FUAFMakeDynamicAdditiveData* Data = nullptr;`
- L59 _private member_ `FUAFMakeDynamicAdditiveAnimOp MakeDynamicAdditiveAnimOp;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMNODE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/UAFNullPoseNode.h` (Public)


#### class `UE::UAF::FUAFNullPoseNode`  
`class FUAFNullPoseNode : public FUAFAnimNode`  
_L16-30_
- inherits: `FUAFAnimNode`
- L19 _public prototype_ `explicit FUAFNullPoseNode(FUAFAnimGraphUpdateContext& Context);`
- L21 _public function_ `virtual void* GetInterface(FUAFAnimNodeInterfaceId Id)`
- L27 _public prototype_ `virtual FString GetDebugName() const override;`
- L28 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMNODE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/UAFOffsetRootBoneNode.h` (Public)


#### struct `UE::UAF::FUAFOffsetRootBoneNodeData`  
`struct FUAFOffsetRootBoneNodeData : public FUAFModifierAnimNodeData`  
_L25-102_
- reflection: `USTRUCT(DisplayName = "Offset Root Bone")`
- inherits: `FUAFModifierAnimNodeData`
- desc: Adds a procedural offset to the root bone coming from incoming root motion. It can optionally fade this out over time (controlled by EUAFOffsetRootBoneNodeMode). This allows a code-controlled character to still be influenced by root motion, e.g. during plant turns. It can lead to less foot sliding in a motion matching setup.
- L31 _public member_ `FBindableFloat Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Alpha)` — Current strength of the skeletal control
- L35 _public member_ `FBindableEnum TranslationMode = FBindableEnum(EUAFOffsetRootBoneNodeMode::Interpolate);` — `UPROPERTY(EditAnywhere, Category = Settings)` — The translation offset behavior mode
- L39 _public member_ `FBindableEnum RotationMode = FBindableEnum(EUAFOffsetRootBoneNodeMode::Interpolate);` — `UPROPERTY(EditAnywhere, Category = Settings)` — The rotation offset behavior mode
- L44 _public member_ `FBindableFloat TranslationSmoothingTime = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Controls how fast the translation offset is blended out Values closer to 0 make it faster
- L49 _public member_ `FBindableFloat RotationSmoothingTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Controls how fast the rotation offset is blended out Values closer to 0 make it faster
- L54 _public member_ `FBindableFloat MaxTranslationError = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — How much the offset can deviate from the mesh component's translation in units Values lower than 0 disable this limit
- L59 _public member_ `FBindableFloat MaxRotationErrorDegrees = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — How much the offset can deviate from the mesh component's rotation in degrees Values lower than 0 disable this limit
- L64 _public member_ `bool bClampToTranslationVelocity = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Inline))` — Whether to limit the offset's translation interpolation speed to the velocity on the incoming motion Enabling this prevents the offset sliding when there's little to no translation speed
- L69 _public member_ `bool bClampToRotationVelocity = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Inline))` — Whether to limit the offset's rotation interpolation speed to the velocity on the incoming motion Enabling this prevents the offset sliding when there's little to no rotation speed
- L74 _public member_ `float TranslationSpeedRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditCondition = bClampToTranslationVelocity, Inline))` — How much the offset can blend out, relative to the incoming translation speed i.e. If root motion is moving at 400cm/s, at 0.5, the offset can blend out at 200cm/s
- L79 _public member_ `float RotationSpeedRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditCondition = bClampToRotationVelocity, Inline))` — How much the offset can blend out, relative to the incoming rotation speed i.e. If root motion is rotating at 90 degrees/s, at 0.5, the offset can blend out at 45 degree/s
- L83 _public member_ `FBindableTransform MeshComponentTransformWorld;` — `UPROPERTY(EditAnywhere, Category = Evaluation)` — This has to be the mesh component transform in world space
- L87 _public member_ `FBindableBool bOnGround = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Signals whether the offset root bone translation should be projected onto a projected ground plane
- L91 _public member_ `FBindableVector AnimatedGroundNormal = FVector(0, 0, 1);` — `UPROPERTY(EditAnywhere, Category = Settings)` — Surface normal that the current animation was authored for. Used with the bOnGround flag.
- L95 _public member_ `float TeleportDistanceThreshold = 300.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Inline))` — Distance threshold used to detect teleports
- L99 _public member_ `bool bResetOnTeleport = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Inline))` — If to reset the root bone offset on teleport
- L101 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;`

#### class `UE::UAF::FUAFOffsetRootBoneNode`  
`class FUAFOffsetRootBoneNode : public FUAFModifierAnimNode`  
_L104-120_
- inherits: `FUAFModifierAnimNode`
- L107 _public prototype_ `FUAFOffsetRootBoneNode(FUAFAnimGraphUpdateContext& Context, const FUAFOffsetRootBoneNodeData& InData);`
- L110 _public prototype_ `virtual FString GetDebugName() const override;`
- L111 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L115 _protected prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;`
- L117 _protected member_ `const FUAFOffsetRootBoneNodeData* Data;`
- L119 _protected member_ `FUAFOffsetRootBoneAnimOp OffsetRootBoneAnimOp;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMNODE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/UAFScalePlayRate.h` (Public)


#### struct `UE::UAF::FUAFScalePlayRateData`  
`struct FUAFScalePlayRateData : public FUAFModifierAnimNodeData`  
_L18-27_
- reflection: `USTRUCT(DisplayName = "Scale Play Rate")`
- inherits: `FUAFModifierAnimNodeData`
- desc: Anim node shared data for scaling the play rate of a child
- L23 _public member_ `FBindableFloat PlayRateMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Data")`
- L26 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;` — FUAFAnimNodeData impl

#### struct `UE::UAF::FUAFScalePlayRate`  
`struct FUAFScalePlayRate : public FUAFModifierAnimNode`  
_L30-48_
- inherits: `FUAFModifierAnimNode`
- desc: Anim node instance for scaling the play rate of a child
- L32 _public prototype_ `FUAFScalePlayRate(FUAFAnimGraphUpdateContext& Context, const FUAFScalePlayRateData& InData);`
- L36 _public prototype_ `void SetPlayRate(float PlayRate);` — Sets the play rate This clears any existing bindings
- L39 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& Context) override;` — FUAFAnimNode impl
- L40 _public prototype_ `virtual void PostUpdate(FUAFAnimGraphUpdateContext& Context) override;`
- L43 _public prototype_ `virtual FString GetDebugName() const override;`
- L44 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L47 _private member_ `FBindableFloat PlayRateMultiplier = 1.0f;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMNODE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/UAFSequencePlayer.h` (Public)


#### struct `UE::UAF::FUAFSequencePlayerData`  
`struct FUAFSequencePlayerData : public FUAFAnimNodeData #if CPP , public IUAFAnimNodeDataHasAsset #endif`  
_L23-46_
- reflection: `USTRUCT(DisplayName = "Sequence Player")`
- inherits: `FUAFAnimNodeData,IUAFAnimNodeDataHasAsset`
- desc: Anim node shared data for playing an AnimSequence
- L31 _public member_ `TObjectPtr<UAnimSequence> Sequence;` — `UPROPERTY(EditAnywhere, Category="Data")`
- L35 _public member_ `EAnimAssetLoopMode LoopMode = EAnimAssetLoopMode::Auto;` — `UPROPERTY(EditAnywhere, Category = "Data")` — Whether to use the asset's default looping behavior or force an override.
- L38 _public member_ `float StartTime = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Data")`
- L41 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;` — FUAFAnimNodeData impl
- L42 _public prototype_ `virtual void* GetInterface(FUAFAnimNodeDataInterfaceId Id) override;`
- L45 _public function_ `virtual UObject* GetAsset() const override` — IAnimNodeDataHasAsset impl

#### struct `UE::UAF::FUAFSequencePlayer`  
`struct FUAFSequencePlayer : public FUAFAnimNode, public IUAFAnimNodeTimeline, public IUAFRootMotionProvider`  
_L49-76_
- inherits: `FUAFAnimNode,IUAFAnimNodeTimeline,IUAFRootMotionProvider`
- desc: Anim node instance for playing an AnimSequence
- L51 _public prototype_ `explicit FUAFSequencePlayer(FUAFAnimGraphUpdateContext& Context, const FUAFSequencePlayerData* InData);`
- L52 _public prototype_ `explicit FUAFSequencePlayer(FUAFAnimGraphUpdateContext& Context, const UAnimSequence* Sequence, EAnimAssetLoopMode LoopMode = EAnimAssetLoopMode::Auto);`
- L55 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;` — FUAFAnimNode impl
- L56 _public prototype_ `virtual void* GetInterface(FUAFAnimNodeInterfaceId Id) override;`
- L57 _public prototype_ `static void AddReferencedObjects(FUAFAnimNode* This, FReferenceCollector& Collector);`
- L60 _public prototype_ `virtual FString GetDebugName() const override;`
- L61 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L65 _public prototype_ `virtual float GetCurrentTime() const override;` — IUAFAnimNodeTimeline
- L66 _public prototype_ `virtual void SetCurrentTime(float InCurrentTime) override;`
- L67 _public prototype_ `virtual bool IsLooping() const override;`
- L68 _public prototype_ `virtual float GetLength() const override;`
- L69 _public prototype_ `virtual ETypeAdvanceAnim GetTimeAdvanceResult() const override;`
- L72 _public prototype_ `virtual FTransform ExtractRootMotion(float StartTime, float DeltaTime, bool AllowLooping) const override;` — IUAFRootMotionProvider
- L75 _private member_ `FUAFDecompressAnimSequenceAnimOp DecompressAnimOp;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API UAFANIMNODE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/UAFSimpleTransition.h` (Public)


#### struct `UE::UAF::FUAFSimpleTransitionData`  
`struct FUAFSimpleTransitionData : public FUAFTransitionNodeData`  
_L26-38_
- reflection: `USTRUCT(DisplayName = "Simple Transition")`
- inherits: `FUAFTransitionNodeData`
- desc: FUAFSimpleTransitionData Shared data for a simple blend transition.
- L31 _public member_ `float Duration = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Blending)`
- L34 _public member_ `EAlphaBlendOption BlendOption = UE::Anim::DefaultBlendOption;` — `UPROPERTY(EditAnywhere, Category = Blending)`
- L37 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context, FUAFAnimNodePtr Source, FUAFAnimNodePtr Target) const override;` — FUAFTransitionNodeData impl

#### class `UE::UAF::FUAFSimpleTransition`  
`class FUAFSimpleTransition : public FUAFTimedTransition`  
_L45-58_
- inherits: `FUAFTimedTransition`
- desc: FUAFSimpleTransition Instance data for a simple blend transition
- L48 _public prototype_ `FUAFSimpleTransition(FUAFAnimGraphUpdateContext& Context, FUAFAnimNodePtr InSource, FUAFAnimNodePtr InTarget, float InDuration, EAlphaBlendOption InBlendOption);`
- L51 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;` — FUAFAnimNode impl
- L54 _public prototype_ `virtual FString GetDebugName() const override;`
- L55 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L57 _public member_ `FUAFBlendTwoAnimOp BlendAnimOp;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API UAFANIMNODE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/UAFSteeringNode.h` (Public)


#### struct `UE::UAF::FUAFSteeringNodeData`  
`struct FUAFSteeringNodeData : public FUAFModifierAnimNodeData`  
_L18-60_
- reflection: `USTRUCT(DisplayName = "Steering")`
- inherits: `FUAFModifierAnimNodeData`
- L23 _public member_ `FBindableFloat Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L26 _public member_ `FBindableQuat TargetOrientation;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L29 _public member_ `FBindableTransform RootBoneTransform;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L33 _public member_ `FBindableFloat ProceduralTargetTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category=Settings)` — The number of seconds in the future before we should reach the TargetOrientation when play animations with no root motion rotation
- L37 _public member_ `FBindableFloat AnimatedTargetTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category=Settings)` — The number of seconds in the future before we should reach the TargetOrientation when playing animations with root motion rotation
- L40 _public member_ `FBindableFloat RootMotionAngleThresholdDegrees = 1.0f;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L44 _public member_ `FBindableFloat MinScaleRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Will clamp the scaling ratio applied to above this threashold. Any error remaining will be compensated for linearly (using ProceduralTargetTime)
- L48 _public member_ `FBindableFloat MaxScaleRatio = 1.5f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Will clamp the scaling ratio applied to below this threashold. Any error remaining will be compensated for linearly (using ProceduralTargetTime)
- L52 _public member_ `FBindableFloat DisableAdditiveBelowSpeed = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — below this movement speed (based on the root motion in the animation) disable steering coming from the additive spring based correction
- L56 _public member_ `FBindableFloat DisableSteeringBelowSpeed = 1.0f;` — `UPROPERTY(EditAnywhere, Category=Settings)` — below this movement speed (based on the root motion in the animation) disable steering completely (both scaling and additive)
- L59 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;` — FUAFTransitionNodeData impl

#### class `UE::UAF::FUAFSteeringNode`  
`class FUAFSteeringNode : public FUAFModifierAnimNode`  
_L62-79_
- inherits: `FUAFModifierAnimNode`
- L65 _public prototype_ `FUAFSteeringNode(FUAFAnimGraphUpdateContext& Context, const FUAFSteeringNodeData& InData);`
- L68 _public prototype_ `virtual FString GetDebugName() const override;`
- L69 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L73 _protected prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;`
- L74 _protected prototype_ `virtual void PostUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;`
- L76 _protected member_ `const FUAFSteeringNodeData* Data;`
- L78 _protected member_ `FUAFSteeringAnimOp SteeringAnimOp;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMNODE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimNodes/UAFTimedTransition.h` (Public)


#### class `UE::UAF::FUAFTimedTransition`  
`class FUAFTimedTransition : public FUAFAnimNode, public IUAFTransitionNode, public IUAFTransitionContainerNode`  
_L18-51_
- inherits: `FUAFAnimNode,IUAFTransitionNode,IUAFTransitionContainerNode`
- desc: FUAFTimedTransition
- L21 _public prototype_ `FUAFTimedTransition(FUAFAnimGraphUpdateContext& Context, FUAFAnimNodePtr InSource, FUAFAnimNodePtr InTarget, float InDuration, EAlphaBlendOption InBlendOption);`
- L24 _public prototype_ `virtual const FUAFAnimNodePtr& GetSource() const override;` — ITransitionInstance impl
- L25 _public prototype_ `virtual const FUAFAnimNodePtr& GetTarget() const override;`
- L26 _public prototype_ `virtual FUAFAnimNodePtr ReleaseSource() override;`
- L27 _public prototype_ `virtual FUAFAnimNodePtr ReleaseTarget() override;`
- L28 _public prototype_ `virtual bool IsComplete() const override;`
- L31 _public prototype_ `virtual void NotifyTransitionComplete(const IUAFTransitionNode& TransitionNode) override;` — ITransitionContainer impl
- L34 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;` — FUAFAnimNode impl
- L35 _public prototype_ `virtual void* GetInterface(FUAFAnimNodeInterfaceId Id) override;`
- L38 _public prototype_ `virtual FString GetDebugName() const override;`
- L39 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L43 _protected member_ `static constexpr int32 SourceChildIndex = 0;`
- L44 _protected member_ `static constexpr int32 TargetChildIndex = 1;`
- L46 _protected member_ `float Duration = 0.1f;`
- L47 _protected member_ `EAlphaBlendOption BlendOption = UE::Anim::DefaultBlendOption;`
- L49 _protected member_ `float TimeRemaining = 0.0f;`
- L50 _protected member_ `bool bNestedTransitionComplete = false;`
- L56 _function_ `inline const FUAFAnimNodePtr& FUAFTimedTransition::GetSource() const`
- L61 _function_ `inline const FUAFAnimNodePtr& FUAFTimedTransition::GetTarget() const`
- L66 _function_ `inline bool FUAFTimedTransition::IsComplete() const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMNODE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOpCore/UAFAnimOp.h` (Public)


#### struct `UE::UAF::FUAFAnimOp`  
`struct FUAFAnimOp`  
_L35-107_
- reflection: `USTRUCT()`
- desc: FUAFAnimOp An anim operation instance. AnimOps are used to produce and manipulate: animated values, notifies, and sync contributors.
- L40 _public prototype_ `explicit FUAFAnimOp(EForceInit);` — ForceInit constructor for TCppStructOps that creates an invalid AnimOp
- L41 _public prototype_ `virtual ~FUAFAnimOp();`
- L44 _public prototype_ `virtual const UScriptStruct* GetStruct() const;` — Returns the derived type for the AnimOp
- L47 _public prototype_ `[[nodiscard]] uint8 GetNumInputs() const;` — Returns the number of inputs this AnimOp consumes
- L50 _public prototype_ `[[nodiscard]] bool HasEvaluateValues() const;` — Whether or not this op implements EvaluateValues(..)
- L53 _public prototype_ `[[nodiscard]] bool HasEvaluateNotifies() const;` — Whether or not this op implements EvaluateNotifies(..)
- L56 _public prototype_ `[[nodiscard]] bool HasEvaluateSynchronization() const;` — Whether or not this op implements EvaluateSynchronization(..)
- L60 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator);` — Entry point for AnimOps that manipulate animated values Values are evaluated first
- L64 _public prototype_ `virtual void EvaluateNotifies(FUAFAnimOpNotifyEvaluator& Evaluator);` — Entry point for AnimOps that manipulate notifies Notifies are evaluated second
- L68 _public prototype_ `virtual void EvaluateSynchronization(FUAFAnimOpSyncEvaluator& Evaluator);` — Entry point for AnimOps that manipulate synchronization contributors Synchronization is evaluated third
- L72 _public prototype_ `[[nodiscard]] const FUAFAnimNode* GetDebugOwner() const;` — Gets the debug owner for this AnimOp Can be nullptr
- L75 _public prototype_ `void SetDebugOwner(const FUAFAnimNode* Owner);` — Sets the debug owner for this AnimOp
- L80 _protected prototype_ `template<class AnimOpType> void InitializeAs();` — Initialization function should be called within the constructor of derived types
- L82 _protected prototype_ `FUAFAnimOp(uint8 NumInputs);`
- L87 _private member_ `const FUAFAnimNode* DebugOwner = nullptr;` — The optional anim node that owns this AnimOp
- L92 _private member_ `uint8 NumInputs = 0;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — How many inputs does this AnimOp consume
- L95 _private member_ `bool bHasEvaluateValues : 1 = false;` — Whether or not this op implements EvaluateValues(..)
- L98 _private member_ `bool bHasEvaluateNotifies : 1 = false;` — Whether or not this op implements EvaluateNotifies(..)
- L101 _private member_ `bool bHasEvaluateSynchronization : 1 = false;` — Whether or not this op implements EvaluateSynchronization(..)
- L105 _private member_ `bool bIsInitialized : 1 = false;` — Whether or not InitializeAs<T>(..) has been called
- L112 _function_ `inline FUAFAnimOp::FUAFAnimOp(EForceInit) : NumInputs(0)`
- L120 _function_ `inline const UScriptStruct* FUAFAnimOp::GetStruct() const`
- L125 _function_ `inline uint8 FUAFAnimOp::GetNumInputs() const`
- L130 _function_ `inline bool FUAFAnimOp::HasEvaluateValues() const`
- L135 _function_ `inline bool FUAFAnimOp::HasEvaluateNotifies() const`
- L140 _function_ `inline bool FUAFAnimOp::HasEvaluateSynchronization() const`
- L146 _function_ `template<class AnimOpType> inline void FUAFAnimOp::InitializeAs()`
- L157 _function_ `inline const FUAFAnimNode* FUAFAnimOp::GetDebugOwner() const`
- L166 _function_ `inline void FUAFAnimOp::SetDebugOwner(const FUAFAnimNode* Owner)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<UE::UAF::FUAFAnimOp> : TStructOpsTypeTraitsBase2<UE::UAF::FUAFAnimOp>`  
_L175-181_
- inherits: `TStructOpsTypeTraitsBase2<UE::UAF::FUAFAnimOp>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L178-180_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMNODE_API`
- L12 _macro_ `#define UAF_ENABLE_DEBUG_ANIMOP_OWNER (!UE_BUILD_SHIPPING && !UE_BUILD_TEST)` — Disable the debug pointer to our AnimOp owner in Test and Shipping builds
- L15 _macro_ `#define UAF_DECLARE_ANIMOP(AnimOpName) \` — Declares various implementation details for an animation operation
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace UAF` (scope `UE`)
- L179 _enumerator_ `WithNoInitConstructor = true` (scope `TStructOpsTypeTraits::__anondcb9d7460103`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOpCore/UAFAnimOpArrayView.h` (Public)


#### struct `UE::UAF::FUAFAnimOpArrayView`  
`struct FUAFAnimOpArrayView : public FUAFAnimOpListBase`  
_L18-41_
- inherits: `FUAFAnimOpListBase`
- desc: FUAFAnimOpArrayView An array view of AnimOps. AnimOps are evaluated in the ascending order.
- L20 _public prototype_ `FUAFAnimOpArrayView();`
- L23 _public prototype_ `template<size_t Count> static FUAFAnimOpArrayView Make(FUAFAnimOp*(&AnimOps)[Count]);` — Creates an array view from a C-style array
- L27 _public prototype_ `template<class AllocatorType> static FUAFAnimOpArrayView Make(const TArray<FUAFAnimOp*, AllocatorType>& AnimOps);` — Creates an array view from a TArray with any allocator
- L31 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl
- L32 _public prototype_ `virtual void EvaluateNotifies(FUAFAnimOpNotifyEvaluator& Evaluator) override;`
- L33 _public prototype_ `virtual void EvaluateSynchronization(FUAFAnimOpSyncEvaluator& Evaluator) override;`
- L37 _protected prototype_ `virtual void GetAnimOps(TAdderRef<const FUAFAnimOp*> OutAnimOps) const override;` — FUAFAnimOpListBase impl
- L40 _protected member_ `TArrayView<FUAFAnimOp*> AnimOps;` — An array view of AnimOps, evaluated in ascending order
- L46 _function_ `inline FUAFAnimOpArrayView::FUAFAnimOpArrayView() : FUAFAnimOpListBase()`
- L53 _function_ `template<size_t Count> inline FUAFAnimOpArrayView FUAFAnimOpArrayView::Make(FUAFAnimOp* (&AnimOps)[Count])`
- L61 _function_ `template<size_t Count> inline FUAFAnimOpArrayView FUAFAnimOpArrayView::Make(FUAFAnimOp* (&AnimOps)[Count], int32 Num)`
- L71 _function_ `template<class AllocatorType> inline FUAFAnimOpArrayView FUAFAnimOpArrayView::Make(const TArray<FUAFAnimOp*, AllocatorType>& AnimOps)`
- L79 _function_ `template<class AllocatorType> inline FUAFAnimOpArrayView FUAFAnimOpArrayView::Make(const TArray<FUAFAnimOp*, AllocatorType>& AnimOps, int32 Num)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFANIMNODE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOpCore/UAFAnimOpEvaluator.h` (Public)


#### class `UE::UAF::FUAFAnimOpEvaluator`  
`class FUAFAnimOpEvaluator`  
_L17-41_
- desc: FUAFAnimOpEvaluator Base class for AnimOp evaluators that provides basic functionality.
- L24 _public prototype_ `template<typename ValueType> [[nodiscard]] TUAFStack<ValueType>& GetOrCreateStack(const FUAFStackName& StackName);` — Returns a user defined stack and creates it if it doesn't exist yet
- L28 _public prototype_ `template<typename ValueType> [[nodiscard]] TUAFStack<ValueType>* FindStack(const FUAFStackName& StackName);` — Returns a pointer to a user defined stack, can be nullptr if it doesn't exist yet
- L32 _public prototype_ `template<typename ValueType> [[nodiscard]] const TUAFStack<ValueType>* FindStack(const FUAFStackName& StackName) const;` — Returns a pointer to a user defined stack, can be nullptr if it doesn't exist yet
- L35 _protected prototype_ `FUAFAnimOpEvaluator();`
- L36 _protected prototype_ `~FUAFAnimOpEvaluator();`
- L40 _private member_ `TMap<FName, TUniquePtr<FUAFStack>> UserDefinedStacks;` — User defined stacks that AnimOps can use
- L47 _function_ `template<typename ValueType> inline TUAFStack<ValueType>& FUAFAnimOpEvaluator::GetOrCreateStack(const FUAFStackName& StackName)`
- L60 _function_ `template<typename ValueType> inline TUAFStack<ValueType>* FUAFAnimOpEvaluator::FindStack(const FUAFStackName& StackName)`
- L68 _function_ `template<typename ValueType> inline const TUAFStack<ValueType>* FUAFAnimOpEvaluator::FindStack(const FUAFStackName& StackName) const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFANIMNODE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOpCore/UAFAnimOpListBase.h` (Public)


#### struct `UE::UAF::FUAFAnimOpListBase`  
`struct FUAFAnimOpListBase : public FUAFAnimOp`  
_L19-32_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- desc: FUAFAnimOpListBase Base type for lists of AnimOps.
- L25 _public prototype_ `explicit FUAFAnimOpListBase(EForceInit);` — ForceInit constructor for TCppStructOps that creates an invalid AnimOp
- L28 _public prototype_ `virtual void GetAnimOps(TAdderRef<const FUAFAnimOp*> OutAnimOps) const PURE_VIRTUAL(FUAFAnimOpListBase::GetAnimOps,);` — Returns the list of AnimOps contained within
- L31 _protected prototype_ `FUAFAnimOpListBase();`
- L37 _function_ `inline FUAFAnimOpListBase::FUAFAnimOpListBase(EForceInit ForceInit) : FUAFAnimOp(ForceInit)`
- L42 _function_ `inline FUAFAnimOpListBase::FUAFAnimOpListBase() : FUAFAnimOp(0)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<UE::UAF::FUAFAnimOpListBase> : TStructOpsTypeTraitsBase2<UE::UAF::FUAFAnimOpListBase>`  
_L49-56_
- inherits: `TStructOpsTypeTraitsBase2<UE::UAF::FUAFAnimOpListBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L52-55_

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L53 _enumerator_ `WithNoInitConstructor = true` (scope `TStructOpsTypeTraits::__anon7467de9d0103`)
- L54 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anon7467de9d0103`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOpCore/UAFAnimOpNotifyEvaluator.h` (Public)


#### class `UE::UAF::FUAFAnimOpNotifyEvaluator`  
`class FUAFAnimOpNotifyEvaluator : public FUAFAnimOpEvaluator`  
_L19-32_
- inherits: `FUAFAnimOpEvaluator`
- desc: FUAFAnimOpNotifyEvaluator The AnimOp notify evaluator provides the necessary machinery for notify evaluation.
- L22 _public prototype_ `FUAFAnimOpNotifyEvaluator();`
- L23 _public prototype_ `~FUAFAnimOpNotifyEvaluator();`
- L26 _public prototype_ `[[nodiscard]] TArray<FAnimNotifyEventReference>& GetNotifies();` — Returns the list of notifies currently being evaluated
- L27 _public prototype_ `[[nodiscard]] const TArray<FAnimNotifyEventReference>& GetNotifies() const;`
- L31 _private member_ `TArray<FAnimNotifyEventReference> Notifies;` — The list of notifies being produced
- L37 _function_ `inline TArray<FAnimNotifyEventReference>& FUAFAnimOpNotifyEvaluator::GetNotifies()`
- L42 _function_ `inline const TArray<FAnimNotifyEventReference>& FUAFAnimOpNotifyEvaluator::GetNotifies() const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFANIMNODE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOpCore/UAFAnimOpTuple.h` (Public)


#### struct `UE::UAF::TUAFAnimOpTuple`  
`template<typename... AnimOpTypes> struct TUAFAnimOpTuple : public FUAFAnimOpListBase`  
_L18-37_
- inherits: `FUAFAnimOpListBase`
- desc: TUAFAnimOpTuple A tuple of AnimOps. AnimOps are evaluated in the order specified: left to right.
- L20 _public prototype_ `TUAFAnimOpTuple();`
- L23 _public prototype_ `template<uint32 Index> UE_REWRITE decltype(auto) Get();` — Returns the AnimOp with the specified index from the specified order
- L27 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl
- L28 _public prototype_ `virtual void EvaluateNotifies(FUAFAnimOpNotifyEvaluator& Evaluator) override;`
- L29 _public prototype_ `virtual void EvaluateSynchronization(FUAFAnimOpSyncEvaluator& Evaluator) override;`
- L33 _protected prototype_ `virtual void GetAnimOps(TAdderRef<const FUAFAnimOp*> OutAnimOps) const override;` — FUAFAnimOpListBase impl
- L36 _protected member_ `TTuple<AnimOpTypes...> AnimOps;` — A list of AnimOps, evaluated left to right
- L43 _function_ `template<typename... AnimOpTypes> inline TUAFAnimOpTuple<AnimOpTypes...>::TUAFAnimOpTuple() : FUAFAnimOpListBase()`
- L51 _function_ `template<typename... AnimOpTypes> template<uint32 Index> inline decltype(auto) TUAFAnimOpTuple<AnimOpTypes...>::Get()`
- L58 _function_ `template<typename... AnimOpTypes> template<uint32 Index> inline decltype(auto) TUAFAnimOpTuple<AnimOpTypes...>::Get() const`
- L64 _function_ `template<typename... AnimOpTypes> inline void TUAFAnimOpTuple<AnimOpTypes...>::GetAnimOps(TAdderRef<const FUAFAnimOp*> OutAnimOps) const`
- L70 _function_ `template<typename... AnimOpTypes> inline void TUAFAnimOpTuple<AnimOpTypes...>::EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator)`
- L88 _function_ `template<typename... AnimOpTypes> inline void TUAFAnimOpTuple<AnimOpTypes...>::EvaluateNotifies(FUAFAnimOpNotifyEvaluator& Evaluator)`
- L104 _function_ `template<typename... AnimOpTypes> inline void TUAFAnimOpTuple<AnimOpTypes...>::EvaluateSynchronization(FUAFAnimOpSyncEvaluator& Evaluator)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L66 _function_ `VisitTupleElements([&OutAnimOps](auto& AnimOp) { OutAnimOps.Add(&AnimOp); }, AnimOps);` (scope `UE::UAF::TUAFAnimOpTuple::GetAnimOps`)
- L76 _function_ `` (scope `UE::UAF::TUAFAnimOpTuple::EvaluateValues`)
- L92 _function_ `` (scope `UE::UAF::TUAFAnimOpTuple::EvaluateNotifies`)
- L108 _function_ `` (scope `UE::UAF::TUAFAnimOpTuple::EvaluateSynchronization`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOpCore/UAFAnimOpValueEvaluator.h` (Public)


#### class `UE::UAF::FUAFAnimOpValueEvaluationContext`  
`class FUAFAnimOpValueEvaluationContext final`  
_L30-76_
- desc: FUAFAnimOpValueEvaluationContext Encapsulates the state that controls what values AnimOps should produce.
- L33 _public prototype_ `FUAFAnimOpValueEvaluationContext();`
- L34 _public prototype_ `FUAFAnimOpValueEvaluationContext(TNonNullPtr<const UAbstractSkeletonSetBinding> SetBinding, const USkeletalMesh* SkeletalMesh, FName SetName);`
- L37 _public prototype_ `[[nodiscard]] bool IsValid() const;` — Returns whether or not this context is valid
- L40 _public prototype_ `[[nodiscard]] const UAbstractSkeletonSetBinding* GetSetBinding() const;` — Returns the abstract skeleton set binding asset we are evaluating with (or nullptr if we aren't valid)
- L43 _public prototype_ `[[nodiscard]] const USkeleton* GetSkeleton() const;` — Returns the concrete skeleton we are evaluating with (or nullptr if we aren't valid)
- L46 _public prototype_ `[[nodiscard]] const USkeletalMesh* GetSkeletalMesh() const;` — Returns the skeletal mesh we are evaluating with, may be nullptr)
- L49 _public prototype_ `[[nodiscard]] const FAttributeNamedSetPtr& GetNamedSet() const;` — Returns the named set we are currently evaluating with (or nullptr if we aren't valid)
- L53 _public prototype_ `[[nodiscard]] bool SetNamedSet(FName SetName);` — Sets the named set Returns true if we succeeded and the set exists in the current binding, false otherwise
- L56 _public prototype_ `[[nodiscard]] const FPoseValueBundlePtr& GetDefaultAttributeValues() const;` — Returns the default attribute values for the current named set (or nullptr if we aren't valid)
- L60 _private member_ `const UAbstractSkeletonSetBinding* SetBinding = nullptr;` — The set binding we are evaluating with
- L63 _private member_ `const USkeletalMesh* SkeletalMesh = nullptr;` — The target skeletal mesh with are evaluating with, may be nullptr
- L66 _private member_ `const USkeleton* Skeleton = nullptr;` — The target skeleton we are evaluating with
- L69 _private member_ `FAttributeBindingDataPtr BindingData;` — Binding data owned by the set binding
- L72 _private member_ `FAttributeNamedSetPtr NamedSet;` — Named set instance to produce an output for
- L75 _private member_ `FPoseValueBundlePtr DefaultAttributeValues;` — Default values as specified by the current set binding and named set
- L133 _function_ `inline const UAbstractSkeletonSetBinding* FUAFAnimOpValueEvaluationContext::GetSetBinding() const`
- L138 _function_ `inline const USkeleton* FUAFAnimOpValueEvaluationContext::GetSkeleton() const`
- L143 _function_ `inline const USkeletalMesh* FUAFAnimOpValueEvaluationContext::GetSkeletalMesh() const`
- L148 _function_ `inline const FAttributeNamedSetPtr& FUAFAnimOpValueEvaluationContext::GetNamedSet() const`
- L153 _function_ `inline const FPoseValueBundlePtr& FUAFAnimOpValueEvaluationContext::GetDefaultAttributeValues() const`
- L158 _function_ `inline bool FUAFAnimOpValueEvaluationContext::IsValid() const`

#### class `UE::UAF::FUAFAnimOpValueEvaluator`  
`class FUAFAnimOpValueEvaluator : public FUAFAnimOpEvaluator`  
_L83-128_
- inherits: `FUAFAnimOpEvaluator`
- desc: FUAFAnimOpValueEvaluator The AnimOp value evaluator provides the necessary machinery for value evaluation.
- L86 _public prototype_ `FUAFAnimOpValueEvaluator(TNonNullPtr<const UAbstractSkeletonSetBinding> SetBinding, const USkeletalMesh* SkeletalMesh, FName SetName, int32 CurrentLOD);`
- L89 _public prototype_ `[[nodiscard]] TUAFStack<FPoseValueBundleCoWRef>& GetEvaluationStack();` — Returns the evaluation stack for value bundles
- L90 _public prototype_ `[[nodiscard]] const TUAFStack<FPoseValueBundleCoWRef>& GetEvaluationStack() const;`
- L93 _public prototype_ `[[nodiscard]] const FUAFAnimOpValueEvaluationContext& GetActiveEvaluationContext() const;` — Returns the evaluation context that controls what values we produce
- L96 _public prototype_ `[[nodiscard]] const FAttributeNamedSetPtr& GetActiveNamedSet() const;` — Returns the named set we are currently evaluating with
- L100 _public prototype_ `[[nodiscard]] bool PushEvaluationContext(TNonNullPtr<const UAbstractSkeletonSetBinding> SetBinding, const USkeletalMesh* SkeletalMesh, FName SetName);` — Pushes a new binding and named set to evaluate with Returns true if we succeeded and the set exists in the specified binding, false otherwise
- L104 _public prototype_ `[[nodiscard]] bool PushEvaluationContext(FName SetName);` — Pushes a new named set to evaluate with Returns true if we succeeded and the set exists in the currently active binding, false otherwise
- L108 _public prototype_ `bool PopEvaluationContext();` — Pops the current active named set Returns whether or not we succeeded (we need to retain at least one named set)
- L111 _public prototype_ `[[nodiscard]] int32 GetCurrentLOD() const;` — Returns the current LOD
- L114 _public prototype_ `[[nodiscard]] const FValueTransformerMapPtr& GetTransformerMap() const;` — Returns the value transformer map
- L118 _private member_ `TUAFStack<FPoseValueBundleCoWRef> EvaluationStack;` — The main evaluation stack for values
- L121 _private member_ `TArray<FUAFAnimOpValueEvaluationContext> EvaluationContextStack;` — The internal context that controls what values we are producing
- L124 _private member_ `FValueTransformerMapPtr ValueTransformerMap;` — Shared map of value transformers
- L127 _private member_ `int32 CurrentLOD = 0;` — Current LOD we are evaluating at
- L163 _function_ `inline TUAFStack<FPoseValueBundleCoWRef>& FUAFAnimOpValueEvaluator::GetEvaluationStack()`
- L168 _function_ `inline const TUAFStack<FPoseValueBundleCoWRef>& FUAFAnimOpValueEvaluator::GetEvaluationStack() const`
- L173 _function_ `inline int32 FUAFAnimOpValueEvaluator::GetCurrentLOD() const`
- L178 _function_ `inline const FValueTransformerMapPtr& FUAFAnimOpValueEvaluator::GetTransformerMap() const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMNODE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L21 _typedef_ `using FPoseValueBundleCoWRef = TUAFCoWRef<FPoseValueBundle, TMemStackAllocator<>>;` (scope `UE::UAF`) — A stack of FPoseValueBundle instances used when sampling sequences and blending their results Their container instances will use the MemStack but internally they can use any allocator
- L22 _externvar_ `extern const FUAFStackName VALUE_STACK_NAME;` (scope `UE::UAF`)
- L23 _prototype_ `UE_UAF_REGISTER_STACK_TYPE(FPoseValueBundleCoWRef);` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOpCore/UAFInstancedAnimOpList.h` (Public)


#### struct `UE::UAF::FUAFInstancedAnimOpList`  
`struct FUAFInstancedAnimOpList`  
_L17-26_
- reflection: `USTRUCT()`
- L21 _public prototype_ `FUAFInstancedAnimOpList() = default;`
- L22 _public prototype_ `FUAFInstancedAnimOpList(const TArray<FUAFAnimOp*>& AnimOps);`
- L25 _public member_ `TArray<FInstancedStruct> AnimOps;` — `UPROPERTY(EditAnywhere, Category = "AnimOps", meta = (ExpandByDefault))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMNODE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOps/UAFApplyAdditiveAnimOp.h` (Public)


#### struct `UE::UAF::FUAFApplyAdditiveAnimOp`  
`struct FUAFApplyAdditiveAnimOp : public FUAFAnimOp`  
_L19-43_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- L25 _public prototype_ `FUAFApplyAdditiveAnimOp();`
- L28 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl
- L30 _public prototype_ `void SetAdditiveWeight(float InWeight);`
- L31 _public prototype_ `void SetBlendMask(const TObjectPtr<UUAFBlendMask> InBlendMask);`
- L34 _private prototype_ `void BuildPerValueWeights(const FUAFAnimOpValueEvaluator& Evaluator, const FPoseValueBundle& BaseInput, FValueBundleStack& OutPerValueWeights);`
- L39 _private member_ `TObjectPtr<UUAFBlendMask> OptionalBlendMask = nullptr;` — `UPROPERTY(Transient)` — Optional blend mask for per-bone application of the additive
- L42 _private member_ `float AdditiveWeight = 1.0f;` — The uniform weight to apply the additive with

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMNODE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOps/UAFBlendAccumulateAnimOp.h` (Public)


#### struct `UE::UAF::FUAFBlendAccumulateAnimOp`  
`struct FUAFBlendAccumulateAnimOp : public FUAFAnimOp`  
_L24-44_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- desc: FUAFBlendAccumulateAnimOp This pops the top two evaluation stack results (A and B, let B be at the top). B is the input that we accumulate on top of; while A is the input we scale. The result is pushed back onto the stack. Top = B + (A * ScaleFactor) Top = Top + (Top-1 * ScaleFactor)
- L29 _public prototype_ `FUAFBlendAccumulateAnimOp();`
- L32 _public prototype_ `float GetScaleFactor() const;` — Returns the scale factor to apply to the top-1 result of the evaluation stack
- L35 _public prototype_ `void SetScaleFactor(float ScaleFactor);` — Sets the scale factor to apply to the top-1 result of the evaluation stack
- L38 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl
- L43 _private member_ `float ScaleFactor = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The scale factor to apply to the keyframe
- L49 _function_ `inline float FUAFBlendAccumulateAnimOp::GetScaleFactor() const`
- L54 _function_ `inline void FUAFBlendAccumulateAnimOp::SetScaleFactor(float InScaleFactor)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMNODE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOps/UAFBlendOverwriteAnimOp.h` (Public)


#### struct `UE::UAF::FUAFBlendOverwriteAnimOp`  
`struct FUAFBlendOverwriteAnimOp : public FUAFAnimOp`  
_L20-40_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- desc: FUAFBlendOverwriteAnimOp This pops the top result from the evaluation stack, scales it by a weight factor, then pushes back the result.
- L25 _public prototype_ `FUAFBlendOverwriteAnimOp();`
- L28 _public prototype_ `float GetScaleFactor() const;` — Returns the scale factor to apply to the top result of the evaluation stack
- L31 _public prototype_ `void SetScaleFactor(float ScaleFactor);` — Sets the scale factor to apply to the top result of the evaluation stack
- L34 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl
- L39 _private member_ `float ScaleFactor = 1.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The scale factor to apply to the top result of the evaluations tack
- L45 _function_ `inline float FUAFBlendOverwriteAnimOp::GetScaleFactor() const`
- L50 _function_ `inline void FUAFBlendOverwriteAnimOp::SetScaleFactor(float InScaleFactor)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMNODE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOps/UAFBlendTwoAnimOp.h` (Public)


#### struct `UE::UAF::FUAFBlendTwoAnimOp`  
`struct FUAFBlendTwoAnimOp : public FUAFAnimOp`  
_L33-72_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- desc: FUAFBlendTwoAnimOp A simple AnimOp that blends two inputs. This pops the top two inputs from the evaluation stack, it interpolates them, and pushes back the result onto the evaluation stack. Let B be the input keyframe at the top of the stack and A be the second from the top. Then we have: Result = Interpolate(A, B, Alpha) An Alpha of 0.0 returns A while 1.0 returns B (top)
- L38 _public prototype_ `FUAFBlendTwoAnimOp();`
- L40 _public prototype_ `void SetInterpolationAlpha(float InterpolationAlpha);`
- L41 _public prototype_ `void SetInterpolationCurve(const FName& AlphaSourceCurveName, const int8 AlphaCurveInputIndex, TFunction<float(float)> InputScaleBiasClampFn);`
- L43 _public prototype_ `void SetBlendOption(EAlphaBlendOption InBlendOption);`
- L46 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl
- L50 _protected prototype_ `[[nodiscard]] float GetInterpolationAlpha(const FPoseValueBundle& InputA, const FPoseValueBundle& InputB) const;` — Compute the current alpha value for curves or return the interpolation alpha otherwise
- L54 _protected member_ `float DesiredInterpolationAlpha = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The desired interpolation alpha between the two input keyframes
- L58 _protected member_ `float ActualInterpolationAlpha = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The actual interpolation alpha between the two input keyframes
- L62 _protected member_ `FName AlphaSourceCurveName = NAME_None;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The curve to evaluate and extract the interpolation alpha between the two input keyframes
- L66 _protected member_ `int8 AlphaCurveInputIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — Which input to take our curve from (0 for A or 1 for B)
- L69 _protected member_ `EAlphaBlendOption BlendOption = UE::Anim::DefaultBlendOption;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`
- L71 _protected member_ `TFunction<float(float)> InputScaleBiasClampFn;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMNODE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOps/UAFBlendTwoPerValueAnimOp.h` (Public)


#### struct `UE::UAF::FUAFBlendTwoPerValueAnimOp`  
`struct FUAFBlendTwoPerValueAnimOp : public FUAFAnimOp`  
_L18-41_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- L23 _public prototype_ `FUAFBlendTwoPerValueAnimOp();`
- L24 _public prototype_ `FUAFBlendTwoPerValueAnimOp(TNonNullPtr<UUAFBlendProfile> BlendProfile, EAlphaBlendOption BlendOption);`
- L26 _public prototype_ `void SetLinearWeightB(float InterpolationAlpha);`
- L29 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl
- L34 _protected member_ `float LinearGlobalWeightB = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The interpolation alpha between the two input keyframes
- L37 _protected member_ `TObjectPtr<UUAFBlendProfile> BlendProfile = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`
- L40 _protected member_ `EAlphaBlendOption BlendOption = UE::Anim::DefaultBlendOption;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMNODE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOps/UAFDecompressAnimSequenceAnimOp.h` (Public)


#### struct `UE::UAF::FUAFDecompressAnimSequenceAnimOp`  
`struct FUAFDecompressAnimSequenceAnimOp : public FUAFAnimOp`  
_L23-93_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- desc: FUAFDecompressAnimSequenceAnimOp Decompresses the data from an animation sequence. Produces: values, notifies, and sync contribution.
- L28 _public prototype_ `FUAFDecompressAnimSequenceAnimOp();`
- L31 _public prototype_ `void Initialize(TObjectPtr<const UAnimSequence> AnimSequence, float StartTime, bool bIsLooping, bool bInterpolate, bool bExtractTrajectory);` — Initializes the AnimOp
- L34 _public prototype_ `ETypeAdvanceAnim AdvanceTime(float DeltaTime);` — Advances time by the specified delta
- L37 _public prototype_ `const UAnimSequence* GetAnimSequence() const;` — Returns the current animation sequence being decompressed
- L40 _public prototype_ `float GetCurrentTime() const;` — Returns the current time being sampled
- L43 _public prototype_ `float GetPreviousTime() const;` — Returns the previous time being sampled
- L46 _public prototype_ `float GetDuration() const;` — Returns the animation sequence duration
- L49 _public prototype_ `ETypeAdvanceAnim GetTimeAdvanceResult() const;` — Returns how time was advanced in the last call to AdvanceTime(..)
- L52 _public prototype_ `bool IsLooping() const;` — Returns whether or not this AnimOp is looping
- L55 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl
- L56 _public prototype_ `virtual void EvaluateNotifies(FUAFAnimOpNotifyEvaluator& Evaluator) override;`
- L61 _private member_ `TObjectPtr<const UAnimSequence> AnimSequence;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — Anim Sequence to grab the keyframe from
- L64 _private member_ `FDeltaTimeRecord DeltaTimeRecord;` — Delta time range required for root motion extraction
- L68 _private member_ `float CurrentTime = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The current playback position within the animation sequence.
- L72 _private member_ `float PreviousTime = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The previous playback position within the animation sequence.
- L76 _private member_ `float Duration = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The animation sequence duration
- L80 _private member_ `TEnumAsByte<ETypeAdvanceAnim> TimeAdvanceResult = ETAA_Default;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — How time advanced in the last call to AdvanceTime(..)
- L85 _private member_ `bool bInterpolate = false;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — Whether to interpolate or step the animation sequence. Only used when the sample time is used.
- L89 _private member_ `bool bExtractTrajectory = false;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — Whether to extract trajectory or not
- L92 _private member_ `bool bIsLooping = false;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`
- L98 _function_ `inline const UAnimSequence* FUAFDecompressAnimSequenceAnimOp::GetAnimSequence() const`
- L103 _function_ `inline float FUAFDecompressAnimSequenceAnimOp::GetCurrentTime() const`
- L108 _function_ `inline float FUAFDecompressAnimSequenceAnimOp::GetPreviousTime() const`
- L113 _function_ `inline float FUAFDecompressAnimSequenceAnimOp::GetDuration() const`
- L118 _function_ `inline ETypeAdvanceAnim FUAFDecompressAnimSequenceAnimOp::GetTimeAdvanceResult() const`
- L123 _function_ `inline bool FUAFDecompressAnimSequenceAnimOp::IsLooping() const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMNODE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOps/UAFMakeDynamicAdditiveAnimOp.h` (Public)


#### struct `UE::UAF::FUAFMakeDynamicAdditiveAnimOp`  
`struct FUAFMakeDynamicAdditiveAnimOp : public FUAFAnimOp`  
_L19-37_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- desc: Anim Op to generate an additive animation from Base and Source poses. The output is (Source - Base) from the stack.
- L25 _public prototype_ `FUAFMakeDynamicAdditiveAnimOp();`
- L28 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl
- L30 _public prototype_ `void SetMeshSpaceAdditive(bool bInMeshSpaceAdditive);`
- L36 _private member_ `bool bMeshSpaceAdditive = false;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — Whether to compute the additive delta in mesh space (rotation only).

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMNODE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOps/UAFNullAnimOp.h` (Public)


#### struct `UE::UAF::FUAFNullAnimOp`  
`struct FUAFNullAnimOp : public FUAFAnimOp`  
_L24-36_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- desc: FUAFNullAnimOp A dummy AnimOp that produces empty outputs. Leaf anim nodes that cannot produce a meaningful result should produce a Null AnimOp. This way, a parent AnimOp can reason meaningfully about the missing input. When possible, use the globally static instance through FUAFNullAnimOp::Get().
- L29 _public prototype_ `FUAFNullAnimOp();`
- L32 _public prototype_ `[[nodiscard]] static FUAFNullAnimOp* Get();` — Returns a globally static instance of a Null AnimOp
- L35 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMNODE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOps/UAFOffsetRootBoneAnimOp.h` (Public)


#### enum `EUAFOffsetRootBoneNodeMode`  
`enum class EUAFOffsetRootBoneNodeMode : uint8`  
_L12-25_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Accumulate` — Accumulate the mesh component's movement into the offset. In this mode, if the mesh component moves the offset will counter the motion, and the root will stay in place
- L21 _public enumerator_ `Interpolate` — Continuously interpolate the offset out In this mode, if the mesh component moves The root will stay behind, but will attempt to catch up
- L24 _public enumerator_ `Release` — Release the offset and stop accumulating the mesh component's movement delta. In this mode we will "blend out" the offset

#### struct `UE::UAF::FUAFOffsetRootBoneAnimOp`  
`struct FUAFOffsetRootBoneAnimOp : public FUAFAnimOp`  
_L31-104_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- L36 _public prototype_ `FUAFOffsetRootBoneAnimOp();`
- L39 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl
- L44 _public member_ `float DeltaTime = 0.f;` — `UPROPERTY()`
- L47 _public member_ `float Alpha = 1.0f;` — `UPROPERTY()`
- L50 _public member_ `FTransform MeshComponentTransformWorld = FTransform::Identity;` — `UPROPERTY()`
- L53 _public member_ `EUAFOffsetRootBoneNodeMode TranslationMode = EUAFOffsetRootBoneNodeMode::Interpolate;` — `UPROPERTY()`
- L56 _public member_ `EUAFOffsetRootBoneNodeMode RotationMode = EUAFOffsetRootBoneNodeMode::Interpolate;` — `UPROPERTY()`
- L59 _public member_ `float TranslationSmoothingTime = 0.1f;` — `UPROPERTY()`
- L62 _public member_ `float RotationSmoothingTime = 0.2f;` — `UPROPERTY()`
- L65 _public member_ `float MaxTranslationError = -1.0f;` — `UPROPERTY()`
- L68 _public member_ `float MaxRotationErrorDegrees = -1.0f;` — `UPROPERTY()`
- L71 _public member_ `bool bOnGround = true;` — `UPROPERTY()`
- L74 _public member_ `FVector AnimatedGroundNormal = FVector(0, 0, 1);` — `UPROPERTY()`
- L79 _public member_ `bool bClampToTranslationVelocity = false;` — `UPROPERTY()`
- L82 _public member_ `bool bClampToRotationVelocity = false;` — `UPROPERTY()`
- L85 _public member_ `float TranslationSpeedRatio = 0.5f;` — `UPROPERTY()`
- L88 _public member_ `float RotationSpeedRatio = 0.5f;` — `UPROPERTY()`
- L91 _public member_ `float TeleportDistanceThreshold = 300.0f;` — `UPROPERTY()`
- L94 _public member_ `bool bResetOnTeleport = false;` — `UPROPERTY()`
- L98 _public member_ `bool bIsFirstUpdate = true;`
- L99 _public member_ `FTransform LastMeshComponentTransformWorld = FTransform::Identity;`
- L100 _public member_ `FVector SimulatedTranslation = FVector::ZeroVector;`
- L101 _public member_ `FQuat SimulatedRotation = FQuat::Identity;`
- L103 _public member_ `UObject* HostObject = nullptr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMNODE_API`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOps/UAFSanitizeAnimOp.h` (Public)


#### struct `UE::UAF::FUAFSanitizeAnimOp`  
`struct FUAFSanitizeAnimOp : public FUAFAnimOp`  
_L22-31_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- desc: FUAFSanitizeAnimOp Sanitizes an input value. For pose values, rotations are normalized. For float values, we validate that values are not NaN/Inf.
- L27 _public prototype_ `FUAFSanitizeAnimOp();`
- L30 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMNODE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/AnimOps/UAFSteeringAnimOp.h` (Public)


#### struct `UE::UAF::FUAFSteeringAnimOp`  
`struct FUAFSteeringAnimOp : public FUAFAnimOp`  
_L21-75_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- L26 _public prototype_ `FUAFSteeringAnimOp();`
- L29 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;` — FUAFAnimOp impl
- L32 _public member_ `float DeltaTime = 0.f;` — `UPROPERTY()`
- L35 _public member_ `float Alpha = 1.0f;` — `UPROPERTY()`
- L38 _public member_ `FVector AngularVelocity = FVector::ZeroVector;` — `UPROPERTY()`
- L41 _public member_ `FQuat TargetOrientation = FQuat::Identity;` — `UPROPERTY()`
- L44 _public member_ `FTransform RootBoneTransform = FTransform::Identity;` — `UPROPERTY()`
- L47 _public member_ `float ProceduralTargetTime = 0.2f;` — `UPROPERTY()`
- L50 _public member_ `float AnimatedTargetTime = 0.f;` — `UPROPERTY()`
- L53 _public member_ `float DisableSteeringBelowSpeed = 0.f;` — `UPROPERTY()`
- L56 _public member_ `float RootMotionAngleThresholdDegrees = 1.0f;` — `UPROPERTY()`
- L60 _public member_ `float DisableAdditiveBelowSpeed = -1.0f;` — `UPROPERTY()` — below this movement speed (based on the root motion in the animation) disable steering coming from the additive spring based correction
- L64 _public member_ `float MinScaleRatio = 0.5f;` — `UPROPERTY()` — Will clamp the scaling ratio applied to above this threashold. Any error remaining will be compensated for linearly (using ProceduralTargetTime)
- L68 _public member_ `float MaxScaleRatio = 1.5f;` — `UPROPERTY()` — Will clamp the scaling ratio applied to below this threashold. Any error remaining will be compensated for linearly (using ProceduralTargetTime)
- L70 _public member_ `UObject* HostObject = nullptr;`
- L73 _public member_ `IUAFRootMotionProvider* RootMotionProvider = nullptr;` — These interfaces are needed if AnimatedTargetTime is greater than 0 (i.e. if we want to take into account predicted root motion)
- L74 _public member_ `IUAFAnimNodeTimeline* Timeline = nullptr;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMNODE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/UAFCoWRef.h` (Public)


#### class `UE::UAF::TUAFCoWRef`  
`template<class ValueType, class AllocatorType = FDefaultAllocator> class TUAFCoWRef`  
_L38-117_
- desc: TUAFCoWRef A reference to a value type that performs Copy-on-Write. A reference is never invalid, it must always be constructed from valid data. A CoW Reference tracks 3 things: - A pointer to an allocated value - Whether or not it owns the allocated memory (if we own it, the reference is unique) - Whether or not the reference is immutable For performance reasons, this tracking is performed using a single pointer where the bottom two bits are used to store our metadata. We thus require an alignment of 4 bytes for all allocations. Mutability is enforced at runtime not through the type system (e.g. with 'const'). The specified allocator will be used when a copy is made and memory is owned by the reference. Copying or assigning a reference to another always performs a copy where the new reference owns the resulting memory. This occurs regardless whether or not the source/target are mutable/immutable. It is always safe to query for a const reference using TUAFCoWRef::Get() regardless of whether or not the underlying reference is immutable. However, care must be taken when using TUAFCoWRef::GetMutable(). It is the responsibility of the caller to ensure that the reference is mutable before attempting to use it as such. If the reference is not mutable, TUAFCoWRef::ForceMutable() can be used to convert it. Two allocators are supported: FDefaultAllocator and TMemStackAllocator.
- L43 _public prototype_ `[[nodiscard]] static TUAFCoWRef<ValueType, AllocatorType> MakeFrom(ValueType&& Value);` — Constructs a new mutable reference from the specified value by performing a move of the input. The reference will be unique as its memory will be owned by us.
- L47 _public prototype_ `[[nodiscard]] static TUAFCoWRef<ValueType, AllocatorType> MakeMutable(ValueType* ValuePtr);` — Constructs a new mutable reference from the specified value pointer. The reference will not be unique as its memory will not be owned by us.
- L51 _public prototype_ `[[nodiscard]] static TUAFCoWRef<ValueType, AllocatorType> MakeImmutable(const ValueType* ValuePtr);` — Constructs a new immutable reference from the specified value pointer. The reference will not be unique as its memory will not be owned by us.
- L55 _public prototype_ `TUAFCoWRef(const TUAFCoWRef<ValueType, AllocatorType>& Other);` — Constructs a new mutable reference by performing a copy of the input reference. The reference will be unique as its memory will be owned by us.
- L60 _public prototype_ `template<class OtherAllocatorType> TUAFCoWRef(const TUAFCoWRef<ValueType, OtherAllocatorType>& Other);` — Constructs a new mutable reference by performing a copy of the input reference. The reference will be unique as its memory will be owned by us.
- L63 _public prototype_ `TUAFCoWRef(TUAFCoWRef<ValueType, AllocatorType>&& Other);` — Move a reference into another
- L67 _public prototype_ `~TUAFCoWRef();` — Destroys the current reference If it owned the memory within, it is freed
- L71 _public prototype_ `TUAFCoWRef<ValueType, AllocatorType>& operator=(const TUAFCoWRef<ValueType, AllocatorType>& Other);` — Assign a new mutable reference by performing a copy of the input reference. The reference will be unique as its memory will be owned by us.
- L76 _public prototype_ `template<class OtherAllocatorType> TUAFCoWRef<ValueType, AllocatorType>& operator=(const TUAFCoWRef<ValueType, OtherAllocatorType>& Other);` — Assign a new mutable reference by performing a copy of the input reference. The reference will be unique as its memory will be owned by us.
- L79 _public prototype_ `TUAFCoWRef<ValueType, AllocatorType>& operator=(TUAFCoWRef<ValueType, AllocatorType>&& Other);` — Move assign a reference into another
- L83 _public prototype_ `TUAFCoWRef<ValueType, AllocatorType>& operator=(ValueType&& Value);` — Move assign a value into a reference by performing a move of the input. The reference will be unique as its memory will be owned by us.
- L86 _public prototype_ `[[nodiscard]] const ValueType& Get() const;` — Returns an immutable reference to the value contained within
- L89 _public prototype_ `[[nodiscard]] ValueType& GetMutable();` — Returns a mutable reference to the value contained within
- L94 _public prototype_ `void ForceMutable();` — Ensures that this reference is mutable If the current reference was immutable and we do not own the memory, this performs a copy (Copy-on-Write) Note that any existing const references will remain valid since the original owner is keeping it alive
- L97 _public prototype_ `[[nodiscard]] bool IsMutable() const;` — Returns whether or not this reference is mutable
- L101 _public prototype_ `[[nodiscard]] bool IsUnique() const;` — Returns whether or not this reference is unique A reference is unique if we own its memory
- L104 _private member_ `static constexpr uintptr_t VALUE_PTR_MASK = static_cast<uintptr_t>(~0x0llu & ~0x03llu);`
- L105 _private member_ `static constexpr uintptr_t FLAGS_MASK = 0x03llu;`
- L106 _private member_ `static constexpr uintptr_t IS_MUTABLE_FLAG_BIT = 0x02llu;`
- L107 _private member_ `static constexpr uintptr_t OWNS_MEMORY_FLAG_BIT = 0x01llu;`
- L110 _private prototype_ `TUAFCoWRef() = default;` — Disable construction of empty references
- L112 _private prototype_ `ValueType* GetValuePtr();`
- L113 _private prototype_ `const ValueType* GetValuePtr() const;`
- L116 _private member_ `uintptr_t ValuePtrAndFlags = 0;` — Stores a pointer to a value and 2 flags in the LSBs
- L130 _function_ `template<class ValueType, class AllocatorType> inline TUAFCoWRef<ValueType, AllocatorType> TUAFCoWRef<ValueType, AllocatorType>::MakeFrom(ValueType&& Value)`
- L146 _function_ `template<class ValueType, class AllocatorType> inline TUAFCoWRef<ValueType, AllocatorType> TUAFCoWRef<ValueType, AllocatorType>::MakeMutable(ValueType* ValuePtr)`
- L160 _function_ `template<class ValueType, class AllocatorType> inline TUAFCoWRef<ValueType, AllocatorType> TUAFCoWRef<ValueType, AllocatorType>::MakeImmutable(const ValueType* ValuePtr)`
- L173 _function_ `template<class ValueType, class AllocatorType> inline TUAFCoWRef<ValueType, AllocatorType>::TUAFCoWRef(const TUAFCoWRef<ValueType, AllocatorType>& Other)`
- L186 _function_ `template<class ValueType, class AllocatorType> template<class OtherAllocatorType> inline TUAFCoWRef<ValueType, AllocatorType>::TUAFCoWRef(const TUAFCoWRef<ValueType, OtherAllocatorType>& Other)`
- L198 _function_ `template<class ValueType, class AllocatorType> inline TUAFCoWRef<ValueType, AllocatorType>::TUAFCoWRef(TUAFCoWRef<ValueType, AllocatorType>&& Other) : ValuePtrAndFlags(Other.ValuePtrAndFlags)`
- L205 _function_ `template<class ValueType, class AllocatorType> inline TUAFCoWRef<ValueType, AllocatorType>::~TUAFCoWRef()`
- L217 _function_ `template<class ValueType, class AllocatorType> inline TUAFCoWRef<ValueType, AllocatorType>& TUAFCoWRef<ValueType, AllocatorType>::operator=(const TUAFCoWRef<ValueType, AllocatorType>& Other)`
- L243 _function_ `template<class ValueType, class AllocatorType> template<class OtherAllocatorType> inline TUAFCoWRef<ValueType, AllocatorType>& TUAFCoWRef<ValueType, AllocatorType>::operator=(const TUAFCoWRef<ValueType, OtherAllocatorType>& Other)`
- L265 _function_ `template<class ValueType, class AllocatorType> inline TUAFCoWRef<ValueType, AllocatorType>& TUAFCoWRef<ValueType, AllocatorType>::operator=(TUAFCoWRef<ValueType, AllocatorType>&& Other)`
- L285 _function_ `template<class ValueType, class AllocatorType> inline TUAFCoWRef<ValueType, AllocatorType>& TUAFCoWRef<ValueType, AllocatorType>::operator=(ValueType&& Value)`
- L307 _function_ `template<class ValueType, class AllocatorType> inline const ValueType& TUAFCoWRef<ValueType, AllocatorType>::Get() const`
- L313 _function_ `template<class ValueType, class AllocatorType> inline ValueType& TUAFCoWRef<ValueType, AllocatorType>::GetMutable()`
- L320 _function_ `template<class ValueType, class AllocatorType> inline void TUAFCoWRef<ValueType, AllocatorType>::ForceMutable()`
- L349 _function_ `template<class ValueType, class AllocatorType> inline bool TUAFCoWRef<ValueType, AllocatorType>::IsMutable() const`
- L355 _function_ `template<class ValueType, class AllocatorType> inline bool TUAFCoWRef<ValueType, AllocatorType>::IsUnique() const`
- L361 _function_ `template<class ValueType, class AllocatorType> inline ValueType* TUAFCoWRef<ValueType, AllocatorType>::GetValuePtr()`
- L367 _function_ `template<class ValueType, class AllocatorType> inline const ValueType* TUAFCoWRef<ValueType, AllocatorType>::GetValuePtr() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L124 _prototype_ `template<class ValueType, class AllocatorType> TUAFCoWRef<ValueType, AllocatorType>& FindMutableCoWRef(TUAFCoWRef<ValueType, AllocatorType>& Arg0, TUAFCoWRef<ValueType, AllocatorType>& Arg1);` (scope `UE::UAF`) — Returns a mutable reference from a list of potential candidates. If candidates are mutable, the first one will be returned. Otherwise, the first unique immutable reference is returned. If none of the candidates are mutable or unique, we perform a Copy-on-Write with the last immutable reference.
- L373 _function_ `template<class ValueType, class AllocatorType> inline TUAFCoWRef<ValueType, AllocatorType>& FindMutableCoWRef(TUAFCoWRef<ValueType, AllocatorType>& Arg0, TUAFCoWRef<ValueType, AllocatorType>& Arg1)` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNode/Public/UAF/UAFStack.h` (Public)


#### class `UE::UAF::FUAFStackName`  
`class FUAFStackName final`  
_L36-55_
- desc: FUAFStackName A small struct to wrap an FName and cache its type hash.
- L40 _public function_ `FUAFStackName(const FName& InName) : Name(InName) , NameHash(GetTypeHash(InName))` — Implicitly coerce or construct a stack name from an FName
- L47 _public prototype_ `[[nodiscard]] const FName& GetName() const;` — Returns the stack name
- L50 _public prototype_ `[[nodiscard]] uint32 GetNameHash() const;` — Returns the stack name hash
- L53 _private member_ `FName Name;`
- L54 _private member_ `uint32 NameHash = 0;`
- L149 _function_ `inline const FName& FUAFStackName::GetName() const`
- L154 _function_ `inline uint32 FUAFStackName::GetNameHash() const`

#### class `UE::UAF::FUAFStack`  
`class FUAFStack`  
_L66-116_
- desc: FUAFStack A simple stack implementation that supports an indirect allocator for its entries. Type safety is enforced at runtime and compile time where possible. In order to use a stack with a new type, make sure that the type has been registered with the following macro: UE_UAF_REGISTER_STACK_TYPE.
- L70 _public prototype_ `virtual ~FUAFStack() = default;` — Virtual destructor to simplify destruction
- L73 _public prototype_ `[[nodiscard]] const FName& GetName() const;` — Returns the stack name
- L76 _public prototype_ `[[nodiscard]] uint32 Num() const;` — Returns the number of stack entries
- L79 _public prototype_ `[[nodiscard]] bool IsEmpty() const;` — Returns whether or not the stack is empty
- L82 _public prototype_ `[[nodiscard]] uint32 GetTypeID() const;` — Returns the stack type ID
- L102 _protected prototype_ `FUAFStack(const FUAFStackName& Name, uint32 TypeID);`
- L103 _protected prototype_ `[[nodiscard]] const FEntryHeader* PeekImpl(uint32 OffsetFromTop) const;`
- L106 _protected member_ `FEntryHeader* Top = nullptr;` — The top entry on the stack
- L109 _protected member_ `FUAFStackName Name;` — The name of this stack
- L112 _protected member_ `uint32 NumEntries = 0;` — How many entries we have on the stack
- L115 _protected member_ `uint32 TypeID = 0;` — Type ID used for runtime checks to make sure we always read/write using the same type
- L159 _function_ `inline const FName& FUAFStack::GetName() const`
- L164 _function_ `inline uint32 FUAFStack::Num() const`
- L169 _function_ `inline bool FUAFStack::IsEmpty() const`
- L174 _function_ `inline uint32 FUAFStack::GetTypeID() const`
- L179 _function_ `inline FUAFStack::FUAFStack(const FUAFStackName& InName, uint32 InTypeID) : Name(InName) , TypeID(InTypeID)`

#### struct `UE::UAF::FUAFStack::FEntryHeader`  
`struct FEntryHeader`  
_L85-100_
- L88 _public member_ `FEntryHeader* PrevTop = nullptr;` — The top entry at the time this new entry was pushed
- L91 _public member_ `uint32 Size = 0;` — The allocated size of this entry, includes sizeof(FEntry) and any required alignment
- L94 _public member_ `uint32 Offset = 0;` — The entry start offset from 'this'
- L98 _public prototype_ `[[nodiscard]] void* GetValuePtr();`
- L99 _public prototype_ `[[nodiscard]] const void* GetValuePtr() const;`
- L185 _function_ `inline void* FUAFStack::FEntryHeader::GetValuePtr()`
- L190 _function_ `inline const void* FUAFStack::FEntryHeader::GetValuePtr() const`

#### class `UE::UAF::TUAFStack`  
`template<typename ValueType> class TUAFStack : public FUAFStack`  
_L128-144_
- inherits: `FUAFStack`
- desc: TUAFStack A simple stack implementation that supports an indirect allocator for its entries. Type safety is enforced at runtime and compile time where possible. In order to use a stack with a new type, make sure that the type has been registered with the following macro: UE_UAF_REGISTER_STACK_TYPE.
- L132 _public prototype_ `TUAFStack(const FUAFStackName& Name);` — Constructs a named stack
- L136 _public prototype_ `void Push(ValueType&& Value);` — Pushes a new value onto the stack
- L139 _public prototype_ `[[nodiscard]] ValueType Pop();` — Pops and returns a value from the stack
- L142 _public prototype_ `[[nodiscard]] const ValueType* Peek(uint32 OffsetFromTop = 0) const;` — Peeks at an element with the specified offset from the top and returns it
- L143 _public prototype_ `[[nodiscard]] ValueType* PeekMutable(uint32 OffsetFromTop = 0);`
- L196 _function_ `template<typename ValueType> inline TUAFStack<ValueType>::TUAFStack(const FUAFStackName& Name) : FUAFStack(Name, GetStackTypeID<ValueType>())`
- L202 _function_ `template<typename ValueType> inline TUAFStack<ValueType>::~TUAFStack()`
- L217 _function_ `template<typename ValueType> inline void TUAFStack<ValueType>::Push(ValueType&& Value)`
- L239 _function_ `template<typename ValueType> inline ValueType TUAFStack<ValueType>::Pop()`
- L259 _function_ `template<typename ValueType> inline const ValueType* TUAFStack<ValueType>::Peek(uint32 OffsetFromTop) const`
- L268 _function_ `template<typename ValueType> inline ValueType* TUAFStack<ValueType>::PeekMutable(uint32 OffsetFromTop)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFANIMNODE_API`
- L13 _macro_ `#define UE_UAF_REGISTER_STACK_TYPE(Type) \` — If you wish to use a custom type with a stack when evaluating AnimOps, you'll have to enable its usage through this macro to ensure that GetStackTypeID<T>() is declared for your type. Use this macro inside the UE::UAF namespace
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L25 _function_ `template<typename Type> [[nodiscard]] constexpr uint32 GetStackTypeID()` (scope `UE::UAF`) — Helper function that returns a UID for the specified stack element type @see UE_UAF_REGISTER_STACK_TYPE
