# Plugins / OptimusCore

- module root: `Plugins/Animation/DeformerGraph/Source/OptimusCore`
- headers: 120; symbols: 3409
- symbol kinds: class=190, delegate=19, enum=31, enumerator=149, externvar=6, function=308, macro=43, member=887, namespace=7, prototype=1575, struct=160, typedef=34
- PrivateDependencyModuleNames: ComputeFramework, ControlRig, Core, CoreUObject, Engine, MeshDescription, OptimusSettings, Projects, RHI, RenderCore, Renderer, RigVM, RigVMDeveloper, StaticMeshDescription
- PublicDependencyModuleNames: SlateCore

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Actions/OptimusAction.h` (Private)


#### struct `FOptimusAction`  
`struct FOptimusAction`  
_L14-50_
- reflection: `USTRUCT()`
- desc: Base action class. This is a UStruct so that we can use UE's RAII to check for type similarity.
- L18 _public prototype_ `FOptimusAction(const FString& InTitle = {});`
- L19 _public prototype_ `virtual ~FOptimusAction();`
- L21 _public function_ `const FString& GetTitle() const`
- L26 _public function_ `void SetTitle(const FString& InTitle)`
- L32 _public function_ `template <typename... ArgTypes> void SetTitlef(::UE::Core::TCheckedFormatString<FString::FmtCharType, ArgTypes...> Fmt, ArgTypes... Args)`
- L42 _protected prototype_ `virtual bool Do(IOptimusPathResolver* InRoot) PURE_VIRTUAL(FOptimusAction::Do, return false; );` — Performs the action as set by the action's constructor.
- L45 _protected prototype_ `virtual bool Undo(IOptimusPathResolver* InRoot) PURE_VIRTUAL(FOptimusAction::Undo, return false; );` — Reverts the action performed by the action's Do function.
- L49 _private member_ `FString Title;` — The title of the action. Should be set by the constructor of the derived objects.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FOptimusAction> : TStructOpsTypeTraitsBase2<FOptimusAction>`  
_L54-61_
- inherits: `TStructOpsTypeTraitsBase2<FOptimusAction>`
- desc: Mark FOptimusAction as pure virtual, so that the UObject machinery won't attempt to instantiate it.

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L58-60_

#### struct `FOptimusCompoundAction`  
`struct FOptimusCompoundAction : public FOptimusAction`  
_L65-117_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L70 _public function_ `FOptimusCompoundAction(const FString& InTitle = {}) : FOptimusAction(InTitle)`
- L75 _public function_ `FOptimusCompoundAction(const FOptimusCompoundAction &)` — Copy nothing.
- L76 _public function_ `FOptimusCompoundAction &operator=(const FOptimusCompoundAction &)`
- L78 _public prototype_ `FOptimusCompoundAction(FOptimusCompoundAction&&) = default;`
- L79 _public prototype_ `FOptimusCompoundAction& operator=(FOptimusCompoundAction&&) = default;`
- L82 _public function_ `template <typename... ArgTypes> FOptimusCompoundAction(::UE::Core::TCheckedFormatString<FString::FmtCharType, ArgTypes...> Fmt, ArgTypes ...Args) : FOptimusAction(FString::Printf(Fmt, Args...))`
- L89 _public prototype_ `TWeakPtr<FOptimusAction> AddSubAction(FOptimusAction* InAction);` — Add a sub-action from a heap-constructed action. This takes ownership of the pointer. @param InAction The action to add. Returns a weakptr for subsequent actions reference the result of this action
- L93 _public function_ `AddSubAction(ArgTypes&& ...Args)`
- L100 _public function_ `bool HasSubActions() const`
- L107 _protected function_ `void AddSubAction(TSharedPtr<FOptimusAction> InAction)`
- L112 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L113 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L116 _private member_ `TArray<TSharedPtr<FOptimusAction>> SubActions;`

#### Free symbols / members of external scopes

- L59 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anon28f550a30103`)

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Actions/OptimusComponentBindingActions.h` (Private)


#### struct `FOptimusComponentBindingAction_AddBinding`  
`struct FOptimusComponentBindingAction_AddBinding : public FOptimusAction`  
_L15-39_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L20 _public prototype_ `FOptimusComponentBindingAction_AddBinding() = default;`
- L22 _public prototype_ `FOptimusComponentBindingAction_AddBinding( const UOptimusComponentSource *InComponentSource, FName InName );`
- L27 _public prototype_ `UOptimusComponentSourceBinding* GetComponentBinding(IOptimusPathResolver* InRoot) const;`
- L30 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L31 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L35 _private member_ `FName ComponentBindingName;` — The name of the component binding to create.
- L38 _private member_ `FTopLevelAssetPath ComponentSourceClassPath;` — The class path of the component source to use.

#### struct `FOptimusComponentBindingAction_RemoveBinding`  
`struct FOptimusComponentBindingAction_RemoveBinding : public FOptimusAction`  
_L43-70_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L48 _public prototype_ `FOptimusComponentBindingAction_RemoveBinding() = default;`
- L50 _public prototype_ `FOptimusComponentBindingAction_RemoveBinding( UOptimusComponentSourceBinding* InBinding );`
- L55 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L56 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L60 _private member_ `FName ComponentBindingName;` — The name of the component binding to remove.
- L63 _private member_ `FTopLevelAssetPath ComponentSourceClassPath;` — The class path of the component source to recreate on undo.
- L66 _private member_ `TArray<FName> ComponentTags;` — Stored component tags
- L69 _private member_ `int32 ComponentBindingIndex = 0;` — The index of the binding in the list.

#### struct `FOptimusComponentBindingAction_RenameBinding`  
`struct FOptimusComponentBindingAction_RenameBinding : public FOptimusAction`  
_L74-96_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L80 _public prototype_ `FOptimusComponentBindingAction_RenameBinding() = default;`
- L82 _public prototype_ `FOptimusComponentBindingAction_RenameBinding( UOptimusComponentSourceBinding* InBinding, FName InNewName);`
- L87 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L88 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L92 _private member_ `FName NewName;` — The new name to give the component binding.
- L95 _private member_ `FName OldName;` — The old name of the component binding.

#### struct `FOptimusComponentBindingAction_SetComponentSource`  
`struct FOptimusComponentBindingAction_SetComponentSource : public FOptimusAction`  
_L100-130_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L105 _public prototype_ `FOptimusComponentBindingAction_SetComponentSource() = default;`
- L107 _public prototype_ `FOptimusComponentBindingAction_SetComponentSource( UOptimusComponentSourceBinding* InComponentBinding, const UOptimusComponentSource* InComponentSource );`
- L113 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L114 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L117 _private prototype_ `bool SetComponentSource( IOptimusPathResolver* InRoot, FTopLevelAssetPath InComponentSourceClassPath ) const;`
- L123 _private member_ `FName BindingName;` — The name of the variable to update.
- L126 _private member_ `FTopLevelAssetPath NewComponentSourceClassPath;` — The class path of the component source to set
- L129 _private member_ `FTopLevelAssetPath OldComponentSourceClassPath;` — The class path of the old component source to set on undo.

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Actions/OptimusNodeActions.h` (Private)


#### struct `FOptimusNodeAction_RenameNode`  
`struct FOptimusNodeAction_RenameNode : public FOptimusAction`  
_L17-43_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L23 _public prototype_ `FOptimusNodeAction_RenameNode() = default;`
- L25 _public prototype_ `FOptimusNodeAction_RenameNode( UOptimusNode* InNode, FText InNewName );`
- L31 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L32 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L36 _private member_ `FString NodePath;` — The path of the node to be renamed.
- L39 _private member_ `FText NewName;` — The node's new name
- L42 _private member_ `FText OldName;` — The node's old name

#### struct `FOptimusNodeAction_MoveNode`  
`struct FOptimusNodeAction_MoveNode : public FOptimusAction`  
_L47-73_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L53 _public prototype_ `FOptimusNodeAction_MoveNode() = default;`
- L55 _public prototype_ `FOptimusNodeAction_MoveNode( UOptimusNode* InNode, const FVector2D &InPosition );`
- L61 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L62 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L66 _private member_ `FString NodePath;` — The path of the node to be moved.
- L69 _private member_ `FDeprecateSlateVector2D NewPosition;` — The node's new position
- L72 _private member_ `FDeprecateSlateVector2D OldPosition;` — The node's old position

#### struct `FOptimusCommentNodeAction_ResizeNode`  
`struct FOptimusCommentNodeAction_ResizeNode : public FOptimusAction`  
_L76-100_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L82 _public prototype_ `FOptimusCommentNodeAction_ResizeNode() = default;`
- L84 _public prototype_ `FOptimusCommentNodeAction_ResizeNode( UOptimusNode_Comment* InNode, const UE::Slate::FDeprecateVector2DParameter& InNewSize );`
- L90 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L91 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L95 _private member_ `FString NodePath;` — The path of the node to be resized
- L97 _private member_ `FDeprecateSlateVector2D OldSize;`
- L99 _private member_ `FDeprecateSlateVector2D NewSize;`

#### struct `FOptimusNodeAction_SetPinValue`  
`struct FOptimusNodeAction_SetPinValue : public FOptimusAction`  
_L103-129_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L109 _public prototype_ `FOptimusNodeAction_SetPinValue() = default;`
- L111 _public prototype_ `FOptimusNodeAction_SetPinValue( UOptimusNodePin *InPin, const FString &InNewValue );`
- L117 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L118 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L122 _private member_ `FString PinPath;` — The path of the pin to set the value on
- L125 _private member_ `FString NewValue;` — The new value to set
- L128 _private member_ `FString OldValue;` — The old value

#### struct `FOptimusNodeAction_SetPinName`  
`struct FOptimusNodeAction_SetPinName : public FOptimusAction`  
_L133-163_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L139 _public prototype_ `FOptimusNodeAction_SetPinName() = default;`
- L141 _public prototype_ `FOptimusNodeAction_SetPinName( UOptimusNodePin *InPin, FName InPinName );`
- L147 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L148 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L151 _private prototype_ `bool SetPinName( IOptimusPathResolver* InRoot, FName InName);`
- L156 _private member_ `FString PinPath;` — The path of the pin to set the value on
- L159 _private member_ `FName NewPinName;` — The new name to set
- L162 _private member_ `FName OldPinName;` — The old name

#### struct `FOptimusNodeAction_SetPinType`  
`struct FOptimusNodeAction_SetPinType : public FOptimusAction`  
_L167-197_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L173 _public prototype_ `FOptimusNodeAction_SetPinType() = default;`
- L175 _public prototype_ `FOptimusNodeAction_SetPinType( UOptimusNodePin *InPin, FOptimusDataTypeRef InDataType );`
- L181 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L182 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L185 _private prototype_ `bool SetPinType( IOptimusPathResolver* InRoot, FName InDataType) const;`
- L190 _private member_ `FString PinPath;` — The path of the pin to set the value on
- L193 _private member_ `FName NewDataTypeName;` — The new type to set
- L196 _private member_ `FName OldDataTypeName;` — The old data type

#### struct `FOptimusNodeAction_SetPinDataDomain`  
`struct FOptimusNodeAction_SetPinDataDomain : public FOptimusAction`  
_L201-232_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L207 _public prototype_ `FOptimusNodeAction_SetPinDataDomain() = default;`
- L209 _public prototype_ `FOptimusNodeAction_SetPinDataDomain( const UOptimusNodePin *InPin, const FOptimusDataDomain& InDataDomain );`
- L215 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L216 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L219 _private prototype_ `bool SetPinDataDomain( IOptimusPathResolver* InRoot, const FOptimusDataDomain& InDataDomain ) const;`
- L225 _private member_ `FString PinPath;` — The path of the pin to set the value on
- L228 _private member_ `FOptimusDataDomain NewDataDomain;` — The new data domain to set
- L231 _private member_ `FOptimusDataDomain OldDataDomain;` — The old data domain

#### struct `FOptimusNodeAction_AddRemovePin`  
`struct FOptimusNodeAction_AddRemovePin : public FOptimusAction`  
_L235-297_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L240 _public prototype_ `FOptimusNodeAction_AddRemovePin() = default;`
- L242 _public prototype_ `FOptimusNodeAction_AddRemovePin( UOptimusNode* InNode, FName InName, EOptimusNodePinDirection InDirection, const FOptimusDataDomain& InDataDomain, FOptimusDataTypeRef InDataType, const UOptimusNodePin* InBeforePin = nullptr, const UOptimusNodePin* InParentPin = nullptr );`
- L252 _public prototype_ `FOptimusNodeAction_AddRemovePin( UOptimusNode* InNode, FName InName, EOptimusNodePinDirection InDirection, const UOptimusNodePin* InBeforePin = nullptr );`
- L259 _public prototype_ `FOptimusNodeAction_AddRemovePin( UOptimusNodePin *InPin );`
- L264 _protected prototype_ `bool AddPin(IOptimusPathResolver* InRoot);`
- L265 _protected prototype_ `bool RemovePin(IOptimusPathResolver* InRoot) const;`
- L268 _protected member_ `FString NodePath;` — The path of the node to have the pin added/removed from.
- L272 _protected member_ `FName PinName = NAME_None;` — Name of the new pin. After Do is called, this will be changed to the actual pin name that got constructed.
- L275 _protected member_ `EOptimusNodePinDirection Direction = EOptimusNodePinDirection::Unknown;` — The pin direction (input or output)
- L278 _protected member_ `bool bIsGroupingPin = false;` — Is it a grouping pin?
- L281 _protected member_ `FOptimusDataDomain DataDomain;` — The the data domain assumed for this pin.
- L284 _protected member_ `FName DataType = NAME_None;` — The data type of the pin to create
- L287 _protected member_ `FString BeforePinPath;` — (Optional) The pin that will be located right after this new pin.
- L290 _protected member_ `FString ParentPinPath;` — (Optional) The pin that will be the parent of this new new pin.
- L293 _protected member_ `FString PinPath;` — The path of the newly created pin
- L296 _protected member_ `bool bExpanded = false;` — Expanded state of the pin being removed.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FOptimusNodeAction_AddRemovePin> : TStructOpsTypeTraitsBase2<FOptimusNodeAction_AddRemovePin>`  
_L300-307_
- inherits: `TStructOpsTypeTraitsBase2<FOptimusNodeAction_AddRemovePin>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L304-306_

#### struct `FOptimusNodeAction_AddPin`  
`struct FOptimusNodeAction_AddPin : public FOptimusNodeAction_AddRemovePin`  
_L311-337_
- reflection: `USTRUCT()`
- inherits: `FOptimusNodeAction_AddRemovePin`
- L316 _public prototype_ `FOptimusNodeAction_AddPin() = default;`
- L318 _public function_ `FOptimusNodeAction_AddPin( UOptimusNode* InNode, FName InName, EOptimusNodePinDirection InDirection, FOptimusDataDomain InDataDomain, FOptimusDataTypeRef InDataType, const UOptimusNodePin* InBeforePin = nullptr, const UOptimusNodePin* InParentPin = nullptr ) : FOptimusNodeAction_AddRemovePin(InNode, InName, InDirection, InDataDomain, InDataType, InBeforePin, InParentPin)`
- L332 _public prototype_ `UOptimusNodePin* GetPin(IOptimusPathResolver* InRoot) const;` — Called to retrieve the pin that was created by Do after it has been called.
- L335 _protected function_ `bool Do(IOptimusPathResolver* InRoot) override`
- L336 _protected function_ `bool Undo(IOptimusPathResolver* InRoot) override`

#### struct `FOptimusNodeAction_AddGroupingPin`  
`struct FOptimusNodeAction_AddGroupingPin : public FOptimusNodeAction_AddRemovePin`  
_L341-364_
- reflection: `USTRUCT()`
- inherits: `FOptimusNodeAction_AddRemovePin`
- L346 _public prototype_ `FOptimusNodeAction_AddGroupingPin() = default;`
- L348 _public function_ `FOptimusNodeAction_AddGroupingPin( UOptimusNode* InNode, FName InName, EOptimusNodePinDirection InDirection, const UOptimusNodePin* InBeforePin = nullptr ) : FOptimusNodeAction_AddRemovePin(InNode, InName, InDirection, InBeforePin)`
- L359 _public prototype_ `UOptimusNodePin* GetPin(IOptimusPathResolver* InRoot) const;` — Called to retrieve the pin that was created by Do after it has been called.
- L362 _protected function_ `bool Do(IOptimusPathResolver* InRoot) override`
- L363 _protected function_ `bool Undo(IOptimusPathResolver* InRoot) override`

#### struct `FOptimusNodeAction_RemovePin`  
`struct FOptimusNodeAction_RemovePin : public FOptimusNodeAction_AddRemovePin`  
_L368-384_
- reflection: `USTRUCT()`
- inherits: `FOptimusNodeAction_AddRemovePin`
- L373 _public prototype_ `FOptimusNodeAction_RemovePin() = default;`
- L375 _public function_ `FOptimusNodeAction_RemovePin( UOptimusNodePin *InPinToRemove ) : FOptimusNodeAction_AddRemovePin(InPinToRemove)`
- L382 _protected function_ `bool Do(IOptimusPathResolver* InRoot) override`
- L383 _protected function_ `bool Undo(IOptimusPathResolver* InRoot) override`

#### struct `FOptimusNodeAction_MovePin`  
`struct FOptimusNodeAction_MovePin : public FOptimusAction`  
_L388-418_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L393 _public prototype_ `FOptimusNodeAction_MovePin() = default;`
- L395 _public prototype_ `FOptimusNodeAction_MovePin( UOptimusNodePin *InPinToMove, const UOptimusNodePin* InPinBefore );`
- L401 _protected function_ `bool Do(IOptimusPathResolver* InRoot) override`
- L402 _protected function_ `bool Undo(IOptimusPathResolver* InRoot) override`
- L405 _private prototype_ `bool MovePin( IOptimusPathResolver* InRoot, const FString& InBeforePinPath );`
- L411 _private member_ `FString PinPath;` — The path of the pin to move
- L414 _private member_ `FString OldBeforePinPath;` — The pin that this pin was next before, before the move. Empty string if it was the last pin.
- L417 _private member_ `FString NewBeforePinPath;` — The pin that this pin will be next before, after the move. Empty string if it will be the last pin.

#### Free symbols / members of external scopes

- L305 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anon11eea4bc0103`)

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Actions/OptimusNodeGraphActions.h` (Private)


#### struct `FOptimusNodeGraphAction_AddGraph`  
`struct FOptimusNodeGraphAction_AddGraph : public FOptimusAction`  
_L28-72_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L34 _public prototype_ `FOptimusNodeGraphAction_AddGraph() = default;`
- L36 _public prototype_ `FOptimusNodeGraphAction_AddGraph( const FString& InGraphOwnerPath, EOptimusNodeGraphType InGraphType, FName InGraphName, int32 InGraphIndex, TFunction<bool(UOptimusNodeGraph*)> InConfigureGraphFunc = {} );`
- L44 _public prototype_ `UOptimusNodeGraph* GetGraph(IOptimusPathResolver* InRoot) const;`
- L47 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L48 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L51 _protected member_ `EOptimusNodeGraphType GraphType;` — The type of graph to create
- L54 _protected member_ `FString GraphOwnerPath;` — The path to the graph owner
- L57 _protected member_ `FName GraphName;` — The name of the graph being created.
- L60 _protected member_ `int32 GraphIndex;` — The index of this new graph in the graph stack.
- L68 _protected member_ `TFunction<bool(UOptimusNodeGraph*)> ConfigureGraphFunc;` — An optional function called to configure the graph after it gets created, but before it gets added to the graph collection. This can only be used to configure properties of the graph itself and objects owned by the graph, otherwise those modification are unlikely to survive an undo/redo pass. The function should return false if the config fails. In that case the rest of the action gets unwound, leaving the asset in a consistent state.
- L71 _protected member_ `FString GraphPath;` — The path of the freshly created graph after the first call to Do.

#### struct `FOptimusNodeGraphAction_RemoveGraph`  
`struct FOptimusNodeGraphAction_RemoveGraph : public FOptimusAction`  
_L76-109_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L82 _public prototype_ `FOptimusNodeGraphAction_RemoveGraph() = default;`
- L84 _public prototype_ `FOptimusNodeGraphAction_RemoveGraph( UOptimusNodeGraph* InGraph);`
- L88 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L89 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L93 _private member_ `FString GraphPath;` — The path of the graph to remove.
- L96 _private member_ `FString GraphOwnerPath;` — The path of the graph's owner.
- L99 _private member_ `EOptimusNodeGraphType GraphType;` — The type of graph to reconstruct back to.
- L102 _private member_ `FName GraphName;` — The name to reconstruct the node as.
- L105 _private member_ `int32 GraphIndex;` — The absolute evaluation order the graph was in.
- L108 _private member_ `TArray<uint8> GraphData;` — The stored graph data.

#### struct `FOptimusNodeGraphAction_RenameGraph`  
`struct FOptimusNodeGraphAction_RenameGraph : public FOptimusAction`  
_L113-141_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L118 _public prototype_ `FOptimusNodeGraphAction_RenameGraph() = default;`
- L120 _public prototype_ `FOptimusNodeGraphAction_RenameGraph( UOptimusNodeGraph* InGraph, FName InNewName);`
- L125 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L126 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L131 _private member_ `FString GraphOwnerPath;` — The path of the graph owner that will actually perform the rename
- L134 _private member_ `FString GraphPath;` — The path of the graph to rename. This value will change after each rename.
- L137 _private member_ `FName NewGraphName;` — The new name for this graph. This name may be modified to retain namespace unicity.
- L140 _private member_ `FName OldGraphName;` — The previous name of the graph

#### struct `FOptimusNodeGraphAction_AddNode`  
`struct FOptimusNodeGraphAction_AddNode : public FOptimusAction`  
_L145-184_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L151 _public prototype_ `FOptimusNodeGraphAction_AddNode() = default;`
- L153 _public prototype_ `FOptimusNodeGraphAction_AddNode( const FString& InGraphPath, const UClass* InNodeClass, FName InNodeName, TFunction<bool(UOptimusNode*)> InConfigureNodeFunc );`
- L161 _public prototype_ `UOptimusNode* GetNode(IOptimusPathResolver* InRoot) const;` — Called to retrieve the node that was created by DoImpl after it has been called.
- L164 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L165 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L169 _private member_ `FString GraphPath;` — The path of the graph the node should be added to.
- L172 _private member_ `FString NodeClassPath;` — The class path of the node to add.
- L176 _private member_ `TFunction<bool(UOptimusNode*)> ConfigureNodeFunc;` — An optional function called to configure the node after it gets created, but before it gets added to the graph.
- L179 _private member_ `FString NodePath;` — The path of the newly added node or the node to remove.
- L183 _private member_ `FName NodeName = NAME_None;` — The name of the newly added node. Used if we undo and then redo the action to ensure we reconstruct the node with the same name.

#### struct `FOptimusNodeGraphAction_DuplicateNode`  
`struct FOptimusNodeGraphAction_DuplicateNode : public FOptimusAction`  
_L188-235_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L194 _public prototype_ `FOptimusNodeGraphAction_DuplicateNode() = default;`
- L196 _public prototype_ `FOptimusNodeGraphAction_DuplicateNode( const FString& InTargetGraphPath, UOptimusNode* InSourceNode, FName InNodeName, TFunction<bool(UOptimusNode*)> InConfigureNodeFunc );`
- L204 _public prototype_ `UOptimusNode* GetNode(IOptimusPathResolver* InRoot) const;` — Called to retrieve the node that was created by DoImpl after it has been called.
- L207 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L208 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L213 _private member_ `FString SourceNodePath;` — The path of the node to duplicate
- L216 _private member_ `FString GraphPath;` — The path of the graph the node should be added to.
- L220 _private member_ `FName NodeName;` — The name of the node to create. The original name of the node is used as a template but will be updated to avoid namespace collisions when first created.
- L223 _private member_ `FString NodeClassPath;` — The class path of the node to add.
- L227 _private member_ `TFunction<bool(UOptimusNode*)> ConfigureNodeFunc;` — An optional function called to configure the node after it gets created, but before it gets added to the graph.
- L231 _private member_ `TArray<uint8> CachedNodeData;` — State of the node when this action was created, useful when moving nodes from clipboard graph to a real graph not used if we can resolve the source node path during Do(), for regular duplicate usage
- L234 _private member_ `FString NodePath;` — Path to the node that gets created through duplication.

#### struct `FOptimusNodeGraphAction_RemoveNode`  
`struct FOptimusNodeGraphAction_RemoveNode : public FOptimusAction`  
_L239-270_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L245 _public prototype_ `FOptimusNodeGraphAction_RemoveNode() = default;`
- L247 _public prototype_ `FOptimusNodeGraphAction_RemoveNode( UOptimusNode* InNode );`
- L252 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L253 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L257 _private member_ `FString NodePath;` — Path to the node to remove.
- L260 _private member_ `FString GraphPath;` — The path of the graph the node should be added to.
- L263 _private member_ `FString NodeClassPath;` — The class path of the node to reconstruct.
- L266 _private member_ `FName NodeName;` — The name to reconstruct the node as.
- L269 _private member_ `TArray<uint8> NodeData;` — The stored node data.

#### struct `FOptimusNodeGraphAction_AddRemoveNodePair`  
`struct FOptimusNodeGraphAction_AddRemoveNodePair: public FOptimusAction`  
_L274-293_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- desc: A base action for adding/removing node pairs.
- L279 _public prototype_ `FOptimusNodeGraphAction_AddRemoveNodePair() = default;`
- L281 _public prototype_ `FOptimusNodeGraphAction_AddRemoveNodePair( const FString& InFirstNodePath, const FString& InSecondNodePath );`
- L287 _protected prototype_ `bool AddNodePair(IOptimusPathResolver* InRoot);`
- L288 _protected prototype_ `bool RemoveNodePair(IOptimusPathResolver* InRoot);`
- L290 _protected member_ `FString FirstNodePath;`
- L292 _protected member_ `FString SecondNodePath;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FOptimusNodeGraphAction_AddRemoveNodePair> : TStructOpsTypeTraitsBase2<FOptimusNodeGraphAction_AddRemoveNodePair>`  
_L298-305_
- inherits: `TStructOpsTypeTraitsBase2<FOptimusNodeGraphAction_AddRemoveNodePair>`
- desc: Mark FOptimusNodeGraphAction_AddRemoveNodePair as pure virtual, so that the UObject machinery won't attempt to instantiate it.

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L302-304_

#### struct `FOptimusNodeGraphAction_AddNodePair`  
`struct FOptimusNodeGraphAction_AddNodePair : public FOptimusNodeGraphAction_AddRemoveNodePair`  
_L310-336_
- reflection: `USTRUCT()`
- inherits: `FOptimusNodeGraphAction_AddRemoveNodePair`
- L315 _public prototype_ `FOptimusNodeGraphAction_AddNodePair() = default;`
- L318 _public prototype_ `FOptimusNodeGraphAction_AddNodePair( TWeakPtr<FOptimusNodeGraphAction_AddNode> InAddFirstNodeAction, TWeakPtr<FOptimusNodeGraphAction_AddNode> InAddSecondNodeAction );` — Use when the node paths are unknown after add node actions are performed
- L324 _public prototype_ `FOptimusNodeGraphAction_AddNodePair( const FString& InFirstNodePath, const FString& InSecondNodePath );` — Use when the node paths are available already
- L330 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L331 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L334 _protected member_ `TWeakPtr<FOptimusNodeGraphAction_AddNode> AddFirstNodeAction;`
- L335 _protected member_ `TWeakPtr<FOptimusNodeGraphAction_AddNode> AddSecondNodeAction;`

#### struct `FOptimusNodeGraphAction_RemoveNodePair`  
`struct FOptimusNodeGraphAction_RemoveNodePair : public FOptimusNodeGraphAction_AddRemoveNodePair`  
_L339-353_
- reflection: `USTRUCT()`
- inherits: `FOptimusNodeGraphAction_AddRemoveNodePair`
- L344 _public prototype_ `FOptimusNodeGraphAction_RemoveNodePair() = default;`
- L346 _public prototype_ `FOptimusNodeGraphAction_RemoveNodePair( const UOptimusNodePair* InNodePair );`
- L351 _protected function_ `bool Do(IOptimusPathResolver* InRoot) override`
- L352 _protected function_ `bool Undo(IOptimusPathResolver* InRoot) override`

#### struct `FOptimusNodeGraphAction_AddRemoveLink`  
`struct FOptimusNodeGraphAction_AddRemoveLink : public FOptimusAction`  
_L358-390_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- desc: A base action for adding/removing nodes.
- L363 _public prototype_ `FOptimusNodeGraphAction_AddRemoveLink() = default;`
- L365 _public prototype_ `FOptimusNodeGraphAction_AddRemoveLink( UOptimusNodePin* InNodeOutputPin, UOptimusNodePin* InNodeInputPin, bool bInCanFail = false );`
- L371 _public prototype_ `FOptimusNodeGraphAction_AddRemoveLink( const FString& InNodeOutputPinPath, const FString& InNodeInputPinPath, bool bInCanFail = false );`
- L378 _protected prototype_ `bool AddLink(IOptimusPathResolver* InRoot);`
- L379 _protected prototype_ `bool RemoveLink(IOptimusPathResolver* InRoot);`
- L382 _protected member_ `FString NodeOutputPinPath;` — The path of the output pin on the node to connect/disconnect to/from.
- L385 _protected member_ `FString NodeInputPinPath;` — The path of the output input on the node to connect/disconnect to/from.
- L389 _protected member_ `bool bCanFail = false;` — The operation is allowed to fail gracefully without terminating the rest of the actions being performed.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FOptimusNodeGraphAction_AddRemoveLink> : TStructOpsTypeTraitsBase2<FOptimusNodeGraphAction_AddRemoveLink>`  
_L395-402_
- inherits: `TStructOpsTypeTraitsBase2<FOptimusNodeGraphAction_AddRemoveLink>`
- desc: Mark FOptimusNodeGraphAction_AddRemoveLink as pure virtual, so that the UObject machinery won't attempt to instantiate it.

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L399-401_

#### struct `FOptimusNodeGraphAction_AddLink`  
`struct FOptimusNodeGraphAction_AddLink : public FOptimusNodeGraphAction_AddRemoveLink`  
_L407-429_
- reflection: `USTRUCT()`
- inherits: `FOptimusNodeGraphAction_AddRemoveLink`
- L412 _public prototype_ `FOptimusNodeGraphAction_AddLink() = default;`
- L414 _public prototype_ `FOptimusNodeGraphAction_AddLink( UOptimusNodePin* InNodeOutputPin, UOptimusNodePin* InNodeInputPin, bool bInCanFail = false );`
- L420 _public prototype_ `FOptimusNodeGraphAction_AddLink( const FString& InNodeOutputPinPath, const FString& InNodeInputPinPath, bool bInCanFail = false );`
- L427 _protected function_ `bool Do(IOptimusPathResolver* InRoot) override`
- L428 _protected function_ `bool Undo(IOptimusPathResolver* InRoot) override`

#### struct `FOptimusNodeGraphAction_RemoveLink`  
`struct FOptimusNodeGraphAction_RemoveLink : public FOptimusNodeGraphAction_AddRemoveLink`  
_L432-451_
- reflection: `USTRUCT()`
- inherits: `FOptimusNodeGraphAction_AddRemoveLink`
- L437 _public prototype_ `FOptimusNodeGraphAction_RemoveLink() = default;`
- L439 _public prototype_ `FOptimusNodeGraphAction_RemoveLink( const UOptimusNodeLink *InLink );`
- L443 _public prototype_ `FOptimusNodeGraphAction_RemoveLink( UOptimusNodePin* InNodeOutputPin, UOptimusNodePin* InNodeInputPin );`
- L449 _protected function_ `bool Do(IOptimusPathResolver* InRoot) override`
- L450 _protected function_ `bool Undo(IOptimusPathResolver* InRoot) override`

#### struct `FOptimusNodeGraphAction_ConnectAdderPin`  
`struct FOptimusNodeGraphAction_ConnectAdderPin : public FOptimusNodeGraphAction_AddRemoveLink`  
_L454-479_
- reflection: `USTRUCT()`
- inherits: `FOptimusNodeGraphAction_AddRemoveLink`
- L459 _public prototype_ `FOptimusNodeGraphAction_ConnectAdderPin() = default;`
- L461 _public prototype_ `FOptimusNodeGraphAction_ConnectAdderPin( IOptimusNodeAdderPinProvider* InAdderPinProvider, const IOptimusNodeAdderPinProvider::FAdderPinAction& InAction, UOptimusNodePin* InSourcePin );`
- L468 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L469 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L472 _private member_ `FString NodePath;`
- L474 _private member_ `IOptimusNodeAdderPinProvider::FAdderPinAction Action;`
- L476 _private member_ `FString SourcePinPath;`
- L478 _private member_ `TArray<FString> AddedPinPaths;`

#### struct `FOptimusNodeGraphAction_PackageKernelFunction`  
`struct FOptimusNodeGraphAction_PackageKernelFunction : public FOptimusAction`  
_L482-519_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L487 _public prototype_ `FOptimusNodeGraphAction_PackageKernelFunction() = default;`
- L489 _public prototype_ `FOptimusNodeGraphAction_PackageKernelFunction( UOptimusNode_CustomComputeKernel* InKernelNode, FName InNodeName);`
- L493 _public prototype_ `UOptimusNode *GetNode(IOptimusPathResolver* InRoot) const;`
- L496 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L497 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L501 _private member_ `FString GraphPath;` — The path of the graph we're creating the packaged node in.
- L504 _private member_ `FName NodeName;` — Node Data to both create packaged node and reconstruct the un-packaged node on undo.
- L505 _private member_ `FVector2D NodePosition;`
- L506 _private member_ `FName Category;`
- L507 _private member_ `FName KernelName;`
- L508 _private member_ `FIntVector GroupSize;`
- L509 _private member_ `TArray<FOptimusParameterBinding> InputBindings;`
- L510 _private member_ `TArray<FOptimusParameterBinding> OutputBindings;`
- L511 _private member_ `FString ShaderSource;`
- L515 _private member_ `FString NodeClassName;` — Once we've created the node class, we store it here, in case we need to remove it on undo.
- L518 _private member_ `FString NodePath;` — The path of the node we just created

#### struct `FOptimusNodeGraphAction_UnpackageKernelFunction`  
`struct FOptimusNodeGraphAction_UnpackageKernelFunction : public FOptimusAction`  
_L523-555_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L528 _public prototype_ `FOptimusNodeGraphAction_UnpackageKernelFunction() = default;`
- L530 _public prototype_ `FOptimusNodeGraphAction_UnpackageKernelFunction( UOptimusNode_ComputeKernelFunction* InKernelFunction, FName InNodeName);`
- L534 _public prototype_ `UOptimusNode *GetNode(IOptimusPathResolver* InRoot) const;`
- L537 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L538 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L542 _private member_ `FString GraphPath;` — The path of the graph we're creating the packaged node in.
- L545 _private member_ `FString ClassPath;` — The path to the node class for the function
- L548 _private member_ `FName NodeName;` — The name of the custom kernel node to create.
- L551 _private member_ `FVector2D NodePosition;` — The position to place it at. Everything else is copied from the class.
- L554 _private member_ `FString NodePath;` — The path of the node we just created

#### Free symbols / members of external scopes

- L303 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anon855c6c8e0103`)
- L400 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anon855c6c8e0203`)

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Actions/OptimusResourceActions.h` (Private)


#### struct `FOptimusResourceAction_AddResource`  
`struct FOptimusResourceAction_AddResource : public FOptimusAction`  
_L18-47_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L24 _public prototype_ `FOptimusResourceAction_AddResource() = default;`
- L26 _public prototype_ `FOptimusResourceAction_AddResource( FOptimusDataTypeRef InDataType, FName InName, FOptimusDataDomain InDataDomain = FOptimusDataDomain() );`
- L32 _public prototype_ `UOptimusResourceDescription* GetResource(IOptimusPathResolver* InRoot) const;`
- L35 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L36 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L40 _private member_ `FName ResourceName;` — The name of the resource to create.
- L43 _private member_ `FOptimusDataTypeRef DataType;` — The data type of the resource
- L46 _private member_ `FOptimusDataDomain DataDomain;` — The desired data domain of the resource

#### struct `FOptimusResourceAction_RemoveResource`  
`struct FOptimusResourceAction_RemoveResource : public FOptimusAction`  
_L51-79_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L57 _public prototype_ `FOptimusResourceAction_RemoveResource() = default;`
- L59 _public prototype_ `FOptimusResourceAction_RemoveResource( const UOptimusResourceDescription* InResource );`
- L64 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L65 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L69 _private member_ `FName ResourceName;` — The name of the resource to re-create
- L72 _private member_ `FOptimusDataTypeRef DataType;` — The data type of the resource
- L75 _private member_ `int32 ResourceIndex = 0;` — The index of the removed resource within the resource list
- L78 _private member_ `TArray<uint8> ResourceData;` — The stored resource data.

#### struct `FOptimusResourceAction_RenameResource`  
`struct FOptimusResourceAction_RenameResource : public FOptimusAction`  
_L83-105_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L89 _public prototype_ `FOptimusResourceAction_RenameResource() = default;`
- L91 _public prototype_ `FOptimusResourceAction_RenameResource( UOptimusResourceDescription* InResource, FName InNewName);`
- L96 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L97 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L101 _private member_ `FName NewName;` — The new name to give the resource.
- L104 _private member_ `FName OldName;` — The old name of the resource.

#### struct `FOptimusResourceAction_SetDataType`  
`struct FOptimusResourceAction_SetDataType : public FOptimusAction`  
_L109-140_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L115 _public prototype_ `FOptimusResourceAction_SetDataType() = default;`
- L117 _public prototype_ `FOptimusResourceAction_SetDataType( UOptimusResourceDescription* InResource, FOptimusDataTypeRef InDataType );`
- L123 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L124 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L127 _private prototype_ `bool SetDataType( IOptimusPathResolver* InRoot, FOptimusDataTypeRef InDataType ) const;`
- L133 _private member_ `FName ResourceName;` — The name of the resource to update.
- L136 _private member_ `FOptimusDataTypeRef NewDataType;` — The data type of the resource
- L139 _private member_ `FOptimusDataTypeRef OldDataType;` — The data type of the resource

#### struct `FOptimusResourceAction_SetDataDomain`  
`struct FOptimusResourceAction_SetDataDomain : public FOptimusAction`  
_L144-175_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L150 _public prototype_ `FOptimusResourceAction_SetDataDomain() = default;`
- L152 _public prototype_ `FOptimusResourceAction_SetDataDomain( UOptimusResourceDescription* InResource, const FOptimusDataDomain& InDataDomain );`
- L158 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L159 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L162 _private prototype_ `bool SetDataDomain( IOptimusPathResolver* InRoot, const FOptimusDataDomain& InDataDomain ) const;`
- L168 _private member_ `FName ResourceName;` — The name of the resource to update.
- L171 _private member_ `FOptimusDataDomain NewDataDomain;` — The data domain of the resource
- L174 _private member_ `FOptimusDataDomain OldDataDomain;` — The data type of the resource

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Actions/OptimusVariableActions.h` (Private)


#### struct `FOptimusVariableAction_AddVariable`  
`struct FOptimusVariableAction_AddVariable : public FOptimusAction`  
_L17-42_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L23 _public prototype_ `FOptimusVariableAction_AddVariable() = default;`
- L25 _public prototype_ `FOptimusVariableAction_AddVariable( FOptimusDataTypeRef InDataType, FName InName );`
- L30 _public prototype_ `UOptimusVariableDescription* GetVariable(IOptimusPathResolver* InRoot) const;`
- L33 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L34 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L38 _private member_ `FName VariableName;` — The name of the variable to create.
- L41 _private member_ `FOptimusDataTypeRef DataType;` — The data type of the variable

#### struct `FOptimusVariableAction_RemoveVariable`  
`struct FOptimusVariableAction_RemoveVariable : public FOptimusAction`  
_L46-76_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L52 _public prototype_ `FOptimusVariableAction_RemoveVariable() = default;`
- L54 _public prototype_ `FOptimusVariableAction_RemoveVariable( UOptimusVariableDescription* InVariable);`
- L58 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L59 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L63 _private member_ `FName VariableName;` — The name of the variable to remove and re-create on undo.
- L66 _private member_ `FOptimusDataTypeRef DataType;` — The data type of the variable
- L69 _private member_ `int32 VariableIndex = 0;` — THe index of the variable in the list
- L72 _private member_ `TArray<uint8> VariableData;` — The stored variable data.
- L75 _private member_ `TArray<uint8> DefaultValueData;` — The stored default value data

#### struct `FOptimusVariableAction_RenameVariable`  
`struct FOptimusVariableAction_RenameVariable : public FOptimusAction`  
_L80-102_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L86 _public prototype_ `FOptimusVariableAction_RenameVariable() = default;`
- L88 _public prototype_ `FOptimusVariableAction_RenameVariable( UOptimusVariableDescription* InVariable, FName InNewName);`
- L93 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L94 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L98 _private member_ `FName NewName;` — The new name to give the variable.
- L101 _private member_ `FName OldName;` — The old name of the variable.

#### struct `FOptimusVariableAction_SetDataType`  
`struct FOptimusVariableAction_SetDataType : public FOptimusAction`  
_L106-136_
- reflection: `USTRUCT()`
- inherits: `FOptimusAction`
- L111 _public prototype_ `FOptimusVariableAction_SetDataType() = default;`
- L113 _public prototype_ `FOptimusVariableAction_SetDataType( UOptimusVariableDescription* InVariable, FOptimusDataTypeRef InDataType );`
- L119 _protected prototype_ `bool Do(IOptimusPathResolver* InRoot) override;`
- L120 _protected prototype_ `bool Undo(IOptimusPathResolver* InRoot) override;`
- L123 _private prototype_ `bool SetDataType( IOptimusPathResolver* InRoot, FOptimusDataTypeRef InDataType ) const;`
- L129 _private member_ `FName VariableName;` — The name of the variable to update.
- L132 _private member_ `FOptimusDataTypeRef NewDataType;` — The new data type to give the variable, used when running Do.
- L135 _private member_ `FOptimusDataTypeRef OldDataType;` — The old data type of the variable, used when running Undo.

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/ComponentSources/OptimusSceneComponentSource.h` (Private)


#### class `UOptimusSceneComponentSource`  
`class UOptimusSceneComponentSource : public UOptimusComponentSource`  
_L11-21_
- reflection: `UCLASS()`
- inherits: `UOptimusComponentSource`
- L17 _public prototype_ `FText GetDisplayName() const override;` — UOptimusComponentSource implementations
- L18 _public function_ `FName GetBindingName() const override`
- L19 _public prototype_ `TSubclassOf<UActorComponent> GetComponentClass() const override;`
- L20 _public prototype_ `TArray<FName> GetExecutionDomains() const override;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/ComponentSources/OptimusSkeletalMeshComponentSource.h` (Private)


#### class `UOptimusSkeletalMeshComponentSource`  
`class UOptimusSkeletalMeshComponentSource : public UOptimusSkinnedMeshComponentSource`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UOptimusSkinnedMeshComponentSource`
- L17 _public prototype_ `FText GetDisplayName() const override;` — UOptimusComponentSource implementations
- L18 _public function_ `FName GetBindingName() const override`
- L19 _public prototype_ `TSubclassOf<UActorComponent> GetComponentClass() const override;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/ComponentSources/OptimusSkinnedMeshComponentSource.h` (Private)


#### class `UOptimusSkinnedMeshComponentSource`  
`class UOptimusSkinnedMeshComponentSource : public UOptimusComponentSource`  
_L11-31_
- reflection: `UCLASS()`
- inherits: `UOptimusComponentSource`
- L24 _public prototype_ `FText GetDisplayName() const override;` — UOptimusComponentSource implementations
- L25 _public function_ `FName GetBindingName() const override`
- L26 _public prototype_ `TSubclassOf<UActorComponent> GetComponentClass() const override;`
- L27 _public prototype_ `TArray<FName> GetExecutionDomains() const override;`
- L28 _public prototype_ `int32 GetLodIndex(const UActorComponent* InComponent) const override;`
- L29 _public prototype_ `uint32 GetDefaultNumInvocations(const UActorComponent* InComponent, int32 InLod) const override;`
- L30 _public prototype_ `bool GetComponentElementCountsForExecutionDomain(FName InDomainName, const UActorComponent* InComponent, int32 InLodIndex, TArray<int32>& OutInvocationElementCounts) const override;`

#### struct `UOptimusSkinnedMeshComponentSource::Domains`  
`struct Domains`  
_L16-21_
- L18 _public member_ `static FName Vertex;`
- L19 _public member_ `static FName Triangle;`
- L20 _public member_ `static FName DuplicateVertex;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/ControlRig/RigUnit_Optimus.h` (Private)


#### struct `FRigVMTrait_OptimusDeformer`  
`struct FRigVMTrait_OptimusDeformer: public FRigVMTrait`  
_L16-28_
- reflection: `USTRUCT(meta=(DocumentationPolicy = "Strict"))`
- inherits: `FRigVMTrait`
- desc: The trait representing the optimus deformer kernel for Control Rig
- L20 _public prototype_ `FRigVMTrait_OptimusDeformer() = default;`
- L21 _public prototype_ `FString GetDisplayName() const override;`
- L23 _public prototype_ `bool ShouldCreatePinForProperty(const FProperty* InProperty) const override;`
- L27 _public member_ `TSoftObjectPtr<UOptimusDeformer> DeformerGraph;` — `UPROPERTY(EditAnywhere, Category = "Deformer Graph")`

#### struct `FRigVMTrait_OptimusDeformerSettings`  
`struct FRigVMTrait_OptimusDeformerSettings: public FRigVMTrait`  
_L34-55_
- reflection: `USTRUCT(meta=(DocumentationPolicy = "Strict"))`
- inherits: `FRigVMTrait`
- desc: The trait representing the base settings for an optimus deformer in Control Rig
- L38 _public prototype_ `FRigVMTrait_OptimusDeformerSettings() = default;`
- L42 _public member_ `EOptimusDeformerExecutionPhase ExecutionPhase = EOptimusDeformerExecutionPhase::AfterDefaultDeformer;` — `UPROPERTY(EditAnywhere, Category = "Trait", meta=(Input))` — The phase at which the deformer will execute
- L46 _public member_ `int32 ExecutionGroup = 1;` — `UPROPERTY(EditAnywhere, Category = "Trait", meta=(Input))` — Deformers are first sorted by execution group index, then by the order in which they are added
- L50 _public member_ `bool DeformChildComponents = true;` — `UPROPERTY(EditAnywhere, Category = "Trait", meta=(Input))` — Whether to apply the deformer to all child components as well
- L54 _public member_ `FName ExcludeChildComponentsWithTag = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Trait", meta=(Input))` — Deformer won't be applied to child components that have the specified component tag

#### struct `FRigUnit_AddOptimusDeformer`  
`struct FRigUnit_AddOptimusDeformer: public FRigUnitMutable`  
_L59-79_
- reflection: `USTRUCT(meta = (DisplayName = "Add Deformer", Category = "Deformer Graph", NodeColor="1 1 1"))`
- inherits: `FRigUnitMutable`
- desc: Adds a deformer to the Skeletal Mesh Component
- L63 _public member_ `static const TCHAR* DeformerTraitName;`
- L64 _public member_ `static const TCHAR* DeformerSettingsTraitName;`
- L66 _public prototype_ `static bool IsVariableTraitName(const FString& InTraitName);`
- L68 _public prototype_ `FRigUnit_AddOptimusDeformer() = default;`
- L70 _public prototype_ `void OnUnitNodeCreated(FRigVMUnitNodeCreatedContext& InContext) const override;`
- L71 _public prototype_ `TArray<FRigVMUserWorkflow> GetSupportedWorkflows(const UObject* InSubject) const override;`
- L74 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L78 _public member_ `FGuid DeformerInstanceGuid;` — `UPROPERTY(meta=(Hidden))`

#### struct `FRigVMTrait_OptimusVariableBase`  
`struct FRigVMTrait_OptimusVariableBase: public FRigVMTrait`  
_L85-91_
- reflection: `USTRUCT(meta=(DocumentationPolicy = "Strict"))`
- inherits: `FRigVMTrait`
- desc: The base class for all optimus deformer variable traits for Control Rig
- L89 _public function_ `virtual void SetValue(UOptimusDeformerInstance* InInstance) const`
- L90 _public prototype_ `static const TCHAR* GetValuePinName();`

#### struct `FRigVMTrait_SetDeformerIntVariable`  
`struct FRigVMTrait_SetDeformerIntVariable: public FRigVMTrait_OptimusVariableBase`  
_L97-105_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set an Int variable on an optimus deformer in Control Rig
- L101 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L104 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerIntArrayVariable`  
`struct FRigVMTrait_SetDeformerIntArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L111-119_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set an Int array variable on an optimus deformer in Control Rig
- L115 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L118 _public member_ `TArray<int32> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerInt2Variable`  
`struct FRigVMTrait_SetDeformerInt2Variable: public FRigVMTrait_OptimusVariableBase`  
_L125-133_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set an Int2 variable on an optimus deformer in Control Rig
- L129 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L132 _public member_ `FIntPoint Value = FIntPoint::ZeroValue;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerInt2ArrayVariable`  
`struct FRigVMTrait_SetDeformerInt2ArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L139-147_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set an Int2 array variable on an optimus deformer in Control Rig
- L143 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L146 _public member_ `TArray<FIntPoint> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerInt3Variable`  
`struct FRigVMTrait_SetDeformerInt3Variable: public FRigVMTrait_OptimusVariableBase`  
_L153-161_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set an Int3 variable on an optimus deformer in Control Rig
- L157 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L160 _public member_ `FIntVector Value = FIntVector::ZeroValue;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerInt3ArrayVariable`  
`struct FRigVMTrait_SetDeformerInt3ArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L167-175_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set an Int3 array variable on an optimus deformer in Control Rig
- L171 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L174 _public member_ `TArray<FIntVector> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerInt4Variable`  
`struct FRigVMTrait_SetDeformerInt4Variable: public FRigVMTrait_OptimusVariableBase`  
_L181-189_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set an Int4 variable on an optimus deformer in Control Rig
- L185 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L188 _public member_ `FIntVector4 Value = FIntVector4::ZeroValue;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerInt4ArrayVariable`  
`struct FRigVMTrait_SetDeformerInt4ArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L195-203_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set an Int4 array variable on an optimus deformer in Control Rig
- L199 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L202 _public member_ `TArray<FIntVector4> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerFloatVariable`  
`struct FRigVMTrait_SetDeformerFloatVariable: public FRigVMTrait_OptimusVariableBase`  
_L209-217_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a double variable on an optimus deformer in Control Rig
- L213 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L216 _public member_ `double Value = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerFloatArrayVariable`  
`struct FRigVMTrait_SetDeformerFloatArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L223-231_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a double array variable on an optimus deformer in Control Rig
- L227 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L230 _public member_ `TArray<double> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerVector2Variable`  
`struct FRigVMTrait_SetDeformerVector2Variable: public FRigVMTrait_OptimusVariableBase`  
_L237-245_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Vector2 variable on an optimus deformer in Control Rig
- L241 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L244 _public member_ `FVector2D Value = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerVector2ArrayVariable`  
`struct FRigVMTrait_SetDeformerVector2ArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L251-259_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Vector2 array variable on an optimus deformer in Control Rig
- L255 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L258 _public member_ `TArray<FVector2D> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerVectorVariable`  
`struct FRigVMTrait_SetDeformerVectorVariable: public FRigVMTrait_OptimusVariableBase`  
_L265-273_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Vector variable on an optimus deformer in Control Rig
- L269 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L272 _public member_ `FVector Value = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerVectorArrayVariable`  
`struct FRigVMTrait_SetDeformerVectorArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L279-287_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Vector array variable on an optimus deformer in Control Rig
- L283 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L286 _public member_ `TArray<FVector> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerVector4Variable`  
`struct FRigVMTrait_SetDeformerVector4Variable: public FRigVMTrait_OptimusVariableBase`  
_L293-301_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Vector4 variable on an optimus deformer in Control Rig
- L297 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L300 _public member_ `FVector4 Value = FVector4::Zero();` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerVector4ArrayVariable`  
`struct FRigVMTrait_SetDeformerVector4ArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L307-315_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Vector4 array variable on an optimus deformer in Control Rig
- L311 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L314 _public member_ `TArray<FVector4> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerLinearColorVariable`  
`struct FRigVMTrait_SetDeformerLinearColorVariable: public FRigVMTrait_OptimusVariableBase`  
_L321-329_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a LinearColor variable on an optimus deformer in Control Rig
- L325 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L328 _public member_ `FLinearColor Value = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerLinearColorArrayVariable`  
`struct FRigVMTrait_SetDeformerLinearColorArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L335-343_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a LinearColor array variable on an optimus deformer in Control Rig
- L339 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L342 _public member_ `TArray<FLinearColor> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerQuatVariable`  
`struct FRigVMTrait_SetDeformerQuatVariable: public FRigVMTrait_OptimusVariableBase`  
_L349-357_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Quat variable on an optimus deformer in Control Rig
- L353 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L356 _public member_ `FQuat Value = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerQuatArrayVariable`  
`struct FRigVMTrait_SetDeformerQuatArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L363-371_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Quat array variable on an optimus deformer in Control Rig
- L367 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L370 _public member_ `TArray<FQuat> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerRotatorVariable`  
`struct FRigVMTrait_SetDeformerRotatorVariable: public FRigVMTrait_OptimusVariableBase`  
_L377-385_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Rotator variable on an optimus deformer in Control Rig
- L381 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L384 _public member_ `FRotator Value = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerRotatorArrayVariable`  
`struct FRigVMTrait_SetDeformerRotatorArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L391-399_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Rotator array variable on an optimus deformer in Control Rig
- L395 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L398 _public member_ `TArray<FRotator> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerTransformVariable`  
`struct FRigVMTrait_SetDeformerTransformVariable: public FRigVMTrait_OptimusVariableBase`  
_L405-413_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Transform variable on an optimus deformer in Control Rig
- L409 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L412 _public member_ `FTransform Value = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerTransformArrayVariable`  
`struct FRigVMTrait_SetDeformerTransformArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L419-427_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Transform array variable on an optimus deformer in Control Rig
- L423 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L426 _public member_ `TArray<FTransform> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerNameVariable`  
`struct FRigVMTrait_SetDeformerNameVariable: public FRigVMTrait_OptimusVariableBase`  
_L433-441_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Name variable on an optimus deformer in Control Rig
- L437 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L440 _public member_ `FName Value = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerNameArrayVariable`  
`struct FRigVMTrait_SetDeformerNameArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L447-455_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Name array variable on an optimus deformer in Control Rig
- L451 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L454 _public member_ `TArray<FName> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerBoolVariable`  
`struct FRigVMTrait_SetDeformerBoolVariable: public FRigVMTrait_OptimusVariableBase`  
_L461-469_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Bool variable on an optimus deformer in Control Rig
- L465 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L468 _public member_ `bool Value = false;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### struct `FRigVMTrait_SetDeformerBoolArrayVariable`  
`struct FRigVMTrait_SetDeformerBoolArrayVariable: public FRigVMTrait_OptimusVariableBase`  
_L475-483_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait_OptimusVariableBase`
- desc: A trait to set a Bool array variable on an optimus deformer in Control Rig
- L479 _public prototype_ `void SetValue(UOptimusDeformerInstance* InInstance) const override;`
- L482 _public member_ `TArray<bool> Value;` — `UPROPERTY(EditAnywhere, Category = "Trait")`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceAdvancedSkeleton.h` (Private)


#### struct `FOptimusAnimAttributeBufferDescription`  
`struct FOptimusAnimAttributeBufferDescription`  
_L26-58_
- reflection: `USTRUCT()`
- L31 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Data Interface")`
- L34 _public member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY(EditAnywhere, Category = "Data Interface", meta=(UseInPerBoneAnimAttribute))`
- L38 _public member_ `FOptimusValueContainerStruct DefaultValueStruct;` — `UPROPERTY(EditAnywhere, Category = "Data Interface")` — Default value if the animation attribute is not found
- L41 _public member_ `FString HlslId;` — `UPROPERTY()`
- L44 _public member_ `FName PinName;` — `UPROPERTY()`
- L46 _public member_ `static const TCHAR* PinNameDelimiter;`
- L47 _public member_ `static const TCHAR* HlslIdDelimiter;`
- L49 _public prototype_ `void UpdatePinNameAndHlslId(bool bInIncludeTypeName = true);`
- L52 _public prototype_ `FOptimusAnimAttributeBufferDescription& Init(const FString& InName, const FOptimusDataTypeRef& InDataType);` — Helpers
- L55 _private prototype_ `FString GetFormattedId( const FString& InDelimiter, bool bInIncludeTypeName) const;`

#### struct `FOptimusAnimAttributeBufferArray`  
`struct FOptimusAnimAttributeBufferArray`  
_L61-103_
- reflection: `USTRUCT()`
- L66 _public member_ `TArray<FOptimusAnimAttributeBufferDescription> InnerArray;` — `UPROPERTY(EditAnywhere, DisplayName = "Animation Attributes" ,Category = "Data Interface")`
- L69 _public function_ `template <typename Predicate> const FOptimusAnimAttributeBufferDescription* FindByPredicate(Predicate Pred) const`
- L74 _public function_ `bool IsEmpty() const`
- L79 _public function_ `FOptimusAnimAttributeBufferDescription& Last(int32 IndexFromTheEnd = 0)`
- L84 _public function_ `const FOptimusAnimAttributeBufferDescription& Last(int32 IndexFromTheEnd = 0) const`
- L89 _public function_ `FOptimusAnimAttributeBufferArray& operator=(const TArray<FOptimusAnimAttributeBufferDescription>& Rhs)`
- L95 _public function_ `int32 Num() const`
- L96 _public function_ `bool IsValidIndex(int32 Index) const`
- L97 _public function_ `const FOptimusAnimAttributeBufferDescription& operator[](int32 InIndex) const`
- L98 _public function_ `FOptimusAnimAttributeBufferDescription& operator[](int32 InIndex)`
- L99 _public function_ `FORCEINLINE TArray<FOptimusAnimAttributeBufferDescription>::RangedForIteratorType begin()`
- L100 _public function_ `FORCEINLINE TArray<FOptimusAnimAttributeBufferDescription>::RangedForConstIteratorType begin() const`
- L101 _public function_ `FORCEINLINE TArray<FOptimusAnimAttributeBufferDescription>::RangedForIteratorType end()`
- L102 _public function_ `FORCEINLINE TArray<FOptimusAnimAttributeBufferDescription>::RangedForConstIteratorType end() const`

#### class `UOptimusAdvancedSkeletonDataInterface`  
`class UOptimusAdvancedSkeletonDataInterface : public UOptimusComputeDataInterface`  
_L110-175_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Skeleton Data Interface provides data related to skinning.
- L118 _public prototype_ `void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L124 _public prototype_ `FString GetDisplayName() const override;`
- L125 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L126 _public prototype_ `TArray<FOptimusCDIPropertyPinDefinition> GetPropertyPinDefinitions() const override;`
- L127 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L129 _public prototype_ `void Initialize() override;`
- L130 _public function_ `bool CanPinDefinitionChange() override`
- L131 _public prototype_ `void RegisterPropertyChangeDelegatesForOwningNode(UOptimusNode* InNode) override;`
- L133 _public prototype_ `void OnDataTypeChanged(FName InTypeName) override;`
- L136 _public prototype_ `const FOptimusAnimAttributeBufferDescription& AddAnimAttribute(const FString& InName, const FOptimusDataTypeRef& InDataType);`
- L140 _public function_ `TCHAR const* GetClassName() const override`
- L141 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L142 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L143 _public prototype_ `void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L144 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L145 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L146 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L150 _public member_ `FName SkinWeightProfile = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Data Interface")`
- L156 _public member_ `bool bEnableLayeredSkinning = false;` — `UPROPERTY(EditAnywhere, Category = "Data Interface")` — If turned on, another set of bone matrices are computed per-frame to allow for layered skinning. It is typically used with a secondary skin weight profile storing the weights of a subset of bones like tweaker bones. The bind matrices for these bones are dynamic and computed based on their parent's current transform instead of initial transform
- L161 _public member_ `FOptimusAnimAttributeBufferArray AttributeBufferArray;` — `UPROPERTY(EditAnywhere, Category = "Data Interface", meta = (ShowOnlyInnerProperties))` — Per-bone animation attributes, allows for custom bone data to be used in kernels, one of the places you can create animation attributes is Control Rig
- L165 _private prototype_ `static FName GetSkinWeightProfilePropertyName();`
- L167 _private prototype_ `FString GetUnusedAttributeName(int32 CurrentAttributeIndex ,const FString& InName) const;`
- L168 _private prototype_ `void UpdateAttributePinNamesAndHlslIds();`
- L169 _private prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions_Internal(bool bGetAllPossiblePins = false, int32 AttributeIndexToExclude = INDEX_NONE) const;`
- L170 _private member_ `static TCHAR const* SkeletonTemplateFilePath;`
- L171 _private member_ `static TCHAR const* AttributeTemplateFilePath;`
- L172 _private member_ `FOnPinDefinitionChanged OnPinDefinitionChangedDelegate;`
- L173 _private member_ `FOnPinDefinitionRenamed OnPinDefinitionRenamedDelegate;`
- L174 _private member_ `FSimpleDelegate OnDisplayNameChangedDelegate;`

#### struct `FOptimusAnimAttributeBufferRuntimeData`  
`struct FOptimusAnimAttributeBufferRuntimeData`  
_L178-196_
- desc: Runtime data with cached values baked out from AttributeDescription
- L180 _public prototype_ `FOptimusAnimAttributeBufferRuntimeData() = default;`
- L182 _public prototype_ `FOptimusAnimAttributeBufferRuntimeData(const FOptimusAnimAttributeBufferDescription& InDescription);`
- L184 _public member_ `FName Name;`
- L185 _public member_ `FName HlslId;`
- L187 _public member_ `int32 Offset = INDEX_NONE;`
- L189 _public member_ `int32 Size = 0;`
- L191 _public member_ `FOptimusDataTypeRegistry::PropertyValueConvertFuncT ConvertFunc = nullptr;`
- L193 _public member_ `UScriptStruct* AttributeType = nullptr;`
- L195 _public member_ `FShaderValueContainer CachedDefaultValue;`

#### struct `FOptimusBoneTransformBuffer`  
`struct FOptimusBoneTransformBuffer`  
_L198-209_
- L200 _public member_ `TArray<FRDGBufferRef> BufferRefPerSection;`
- L201 _public member_ `TArray<FRDGBufferSRVRef> BufferSRVPerSection;`
- L202 _public member_ `TArray<TArray<uint8>> BufferData;`
- L203 _public member_ `TArray<int32> NumBones;`
- L205 _public prototype_ `void SetData(FSkeletalMeshLODRenderData const& InLodRenderData, const TArray<FTransform>& InBoneTransforms, bool bInUnifiedBoneMap);`
- L206 _public prototype_ `bool HasData() const;`
- L208 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder);`

#### class `UOptimusAdvancedSkeletonDataProvider`  
`class UOptimusAdvancedSkeletonDataProvider : public UComputeDataProvider, public IOptimusDeformerInstanceAccessor`  
_L213-251_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider,IOptimusDeformerInstanceAccessor`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L221 _public prototype_ `void SetDeformerInstance(UOptimusDeformerInstance* InInstance) override;`
- L223 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkeletalMesh = nullptr;`
- L225 _public member_ `TArray<FOptimusAnimAttributeBufferRuntimeData> AttributeBufferRuntimeData;`
- L227 _public member_ `int32 ParameterBufferSize = 0;`
- L229 _public member_ `FName SkinWeightProfile = NAME_None;`
- L231 _public member_ `bool bEnableLayeredSkinning = true;`
- L232 _public member_ `bool bIsLayeredSkinInitialized = false;`
- L233 _public member_ `TSet<uint32> CachedWeightedBoneIndices;`
- L234 _public member_ `TArray<int32> CachedBoundaryBoneIndex;`
- L235 _public member_ `TArray<FTransform> CachedLayerSpaceInitialBoneTransform;`
- L238 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L241 _public prototype_ `void Init( const UOptimusAdvancedSkeletonDataInterface* InDataInterface, USkeletalMeshComponent* InSkeletalMesh );`
- L246 _public prototype_ `void ComputeBoneTransformsForLayeredSkinning(TArray<FTransform>& OutBoneTransforms, FSkeletalMeshLODRenderData const& InLodRenderData, const FReferenceSkeleton& InRefSkeleton);`
- L248 _private member_ `TWeakObjectPtr<UOptimusDeformerInstance> WeakDeformerInstance;`
- L250 _private member_ `TWeakObjectPtr<const UOptimusAdvancedSkeletonDataInterface> WeakDataInterface;`

#### class `FOptimusAdvancedSkeletonDataProviderProxy`  
`class FOptimusAdvancedSkeletonDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L253-286_
- inherits: `FComputeDataProviderRenderProxy`
- L256 _public prototype_ `FOptimusAdvancedSkeletonDataProviderProxy();`
- L259 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L260 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L261 _public prototype_ `void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L262 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L265 _public typedef_ `using FDefaultParameters = FAdvancedSkeletonDataInterfaceDefaultParameters;`
- L268 _public member_ `FSceneInterface* SceneInterface = nullptr;` — Data supplied by data provider
- L269 _public member_ `FPrimitiveComponentId ComponentId;`
- L270 _public member_ `FName SkinWeightProfile = NAME_None;`
- L272 _public member_ `TArray<uint8> ParameterBuffer;`
- L274 _public member_ `TArray<FTransform> LayeredBoneMatrices;`
- L275 _public member_ `TArray<FOptimusAnimAttributeBufferRuntimeData> AttributeBufferRuntimeData;`
- L276 _public member_ `TArray<TArray<uint8>> Attributes;`
- L279 _public member_ `FOptimusBoneTransformBuffer LayeredBoneMatrixBuffer;` — Proxy managed data to be uploaded to GPU
- L281 _public member_ `TArray<TArray<FRDGBufferRef>> BuffersPerAttributePerSection;`
- L282 _public member_ `TArray<TArray<FRDGBufferSRVRef>> BufferSRVsPerAttributePerSection;`
- L283 _public member_ `TArray<TArray<TArray<uint8>>> AttributeBuffers;`
- L285 _public member_ `FRDGBufferSRVRef FallbackSRV = nullptr;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceAnimAttribute.h` (Private)


#### struct `FOptimusAnimAttributeDescription`  
`struct FOptimusAnimAttributeDescription`  
_L22-63_
- reflection: `USTRUCT()`
- L27 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Data Interface")`
- L31 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, Category = "Data Interface")` — Used to look for attributes associated with a specific bone. Default to use the root bone
- L34 _public member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY(EditAnywhere, Category = "Data Interface", meta=(UseInAnimAttribute))`
- L38 _public member_ `FOptimusValueContainerStruct DefaultValueStruct;` — `UPROPERTY(EditAnywhere, Category = "Data Interface")` — Default value if the animation attribute is not found
- L41 _public member_ `FString HlslId;` — `UPROPERTY()`
- L44 _public member_ `FName PinName;` — `UPROPERTY()`
- L46 _public prototype_ `void UpdatePinNameAndHlslId(bool bInIncludeBoneName = true, bool bInIncludeTypeName = true);`
- L49 _public prototype_ `FOptimusAnimAttributeDescription& Init(const FString& InName, FName InBoneName, const FOptimusDataTypeRef& InDataType);` — Helpers
- L55 _private prototype_ `FString GetFormattedId( const FString& InDelimiter, bool bInIncludeBoneName, bool bInIncludeTypeName) const;`
- L62 _private member_ `TObjectPtr<UOptimusValueContainer> DefaultValue_DEPRECATED = nullptr;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "use DefaultValueStruct instead"))` — Deprecated

#### struct `FOptimusAnimAttributeArray`  
`struct FOptimusAnimAttributeArray`  
_L66-108_
- reflection: `USTRUCT()`
- L71 _public member_ `TArray<FOptimusAnimAttributeDescription> InnerArray;` — `UPROPERTY(EditAnywhere, DisplayName = "Animation Attributes" ,Category = "Data Interface")`
- L74 _public function_ `template <typename Predicate> const FOptimusAnimAttributeDescription* FindByPredicate(Predicate Pred) const`
- L79 _public function_ `bool IsEmpty() const`
- L84 _public function_ `FOptimusAnimAttributeDescription& Last(int32 IndexFromTheEnd = 0)`
- L89 _public function_ `const FOptimusAnimAttributeDescription& Last(int32 IndexFromTheEnd = 0) const`
- L94 _public function_ `FOptimusAnimAttributeArray& operator=(const TArray<FOptimusAnimAttributeDescription>& Rhs)`
- L100 _public function_ `int32 Num() const`
- L101 _public function_ `bool IsValidIndex(int32 Index) const`
- L102 _public function_ `const FOptimusAnimAttributeDescription& operator[](int32 InIndex) const`
- L103 _public function_ `FOptimusAnimAttributeDescription& operator[](int32 InIndex)`
- L104 _public function_ `FORCEINLINE TArray<FOptimusAnimAttributeDescription>::RangedForIteratorType begin()`
- L105 _public function_ `FORCEINLINE TArray<FOptimusAnimAttributeDescription>::RangedForConstIteratorType begin() const`
- L106 _public function_ `FORCEINLINE TArray<FOptimusAnimAttributeDescription>::RangedForIteratorType end()`
- L107 _public function_ `FORCEINLINE TArray<FOptimusAnimAttributeDescription>::RangedForConstIteratorType end() const`

#### class `UOptimusAnimAttributeDataInterface`  
`class UOptimusAnimAttributeDataInterface : public UOptimusComputeDataInterface`  
_L113-161_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading animation attributes on skeletal mesh.
- L119 _public prototype_ `UOptimusAnimAttributeDataInterface();`
- L122 _public prototype_ `void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L124 _public prototype_ `void PostLoad() override;`
- L127 _public prototype_ `FString GetDisplayName() const override;`
- L128 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L129 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L131 _public prototype_ `void Initialize() override;`
- L132 _public function_ `bool CanPinDefinitionChange() override`
- L133 _public prototype_ `void RegisterPropertyChangeDelegatesForOwningNode(UOptimusNode* InNode) override;`
- L138 _public function_ `TCHAR const* GetClassName() const override`
- L139 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L140 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L141 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L142 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L143 _public prototype_ `void GetStructDeclarations(TSet<FString>& OutStructsSeen, TArray<FString>& OutStructs) const override;`
- L144 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L145 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L148 _public prototype_ `const FOptimusAnimAttributeDescription& AddAnimAttribute(const FString& InName, FName InBoneName, const FOptimusDataTypeRef& InDataType);`
- L150 _public prototype_ `void OnDataTypeChanged(FName InTypeName) override;`
- L153 _public member_ `FOptimusAnimAttributeArray AttributeArray;` — `UPROPERTY(EditAnywhere, Category = "Animation Attribute", meta = (ShowOnlyInnerProperties))`
- L156 _private prototype_ `FString GetUnusedAttributeName(const FString& InName) const;`
- L157 _private prototype_ `void UpdateAttributePinNamesAndHlslIds();`
- L159 _private member_ `FOnPinDefinitionChanged OnPinDefinitionChangedDelegate;`
- L160 _private member_ `FOnPinDefinitionRenamed OnPinDefinitionRenamedDelegate;`

#### struct `FOptimusAnimAttributeRuntimeData`  
`struct FOptimusAnimAttributeRuntimeData`  
_L164-190_
- desc: Runtime data with cached values baked out from AttributeDescription
- L166 _public prototype_ `FOptimusAnimAttributeRuntimeData() = default;`
- L168 _public prototype_ `FOptimusAnimAttributeRuntimeData(const FOptimusAnimAttributeDescription& InDescription);`
- L170 _public member_ `FName Name;`
- L171 _public member_ `FName HlslId;`
- L173 _public member_ `FName BoneName;`
- L175 _public member_ `int32 CachedBoneIndex = 0;`
- L177 _public member_ `int32 Offset = INDEX_NONE;`
- L179 _public member_ `int32 Size = 0;`
- L181 _public member_ `int32 ArrayIndexStart = INDEX_NONE;`
- L183 _public member_ `FOptimusDataTypeRegistry::PropertyValueConvertFuncT ConvertFunc = nullptr;`
- L185 _public member_ `TArray<FOptimusDataTypeRegistry::FArrayMetadata> ArrayMetadata;`
- L187 _public member_ `UScriptStruct* AttributeType = nullptr;`
- L189 _public member_ `FShaderValueContainer CachedDefaultValue;`

#### class `UOptimusAnimAttributeDataProvider`  
`class UOptimusAnimAttributeDataProvider : public UComputeDataProvider`  
_L194-217_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading animation attributes on skeletal mesh.
- L199 _public prototype_ `UOptimusAnimAttributeDataProvider() = default;`
- L201 _public prototype_ `void Init( USkeletalMeshComponent* InSkeletalMesh, const TArray<FOptimusAnimAttributeDescription>& InAttributeArray );`
- L206 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkeletalMesh = nullptr;`
- L208 _public member_ `TArray<FOptimusAnimAttributeRuntimeData> AttributeRuntimeData;`
- L210 _public member_ `int32 AttributeBufferSize = 0;`
- L212 _public member_ `int32 TotalNumArrays = 0;`
- L215 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusAnimAttributeDataProviderProxy`  
`class FOptimusAnimAttributeDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L219-247_
- inherits: `FComputeDataProviderRenderProxy`
- L228 _public prototype_ `FOptimusAnimAttributeDataProviderProxy( int32 InAttributeBufferSize, int32 InTotalNumArrays );`
- L234 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L235 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L236 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L240 _public member_ `TArray<uint8> AttributeBuffer;`
- L241 _public member_ `TArray<FArrayMetadata> AttributeArrayMetadata;`
- L242 _public member_ `TArray<FArrayShaderValue> AttributeArrayData;`
- L245 _private member_ `TArray<FRDGBuffer*> ArrayBuffers;`
- L246 _private member_ `TArray<FRDGBufferSRV*> ArrayBufferSRVs;`

#### struct `FOptimusAnimAttributeDataProviderProxy::FArrayMetadata`  
`struct FArrayMetadata`  
_L222-226_
- L224 _public member_ `int32 Offset;`
- L225 _public member_ `int32 ElementSize;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceCloth.h` (Private)


#### class `UOptimusClothDataInterface`  
`class UOptimusClothDataInterface : public UOptimusComputeDataInterface`  
_L19-43_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading cloth data.
- L25 _public prototype_ `FString GetDisplayName() const override;`
- L26 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L27 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L31 _public function_ `TCHAR const* GetClassName() const override`
- L32 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L33 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L34 _public prototype_ `void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L35 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L36 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L37 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L38 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L42 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusClothDataProvider`  
`class UOptimusClothDataProvider : public UComputeDataProvider`  
_L47-57_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L52 _public member_ `TWeakObjectPtr<USkinnedMeshComponent> SkinnedMesh = nullptr;`
- L55 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusClothDataProviderProxy`  
`class FOptimusClothDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L59-78_
- inherits: `FComputeDataProviderRenderProxy`
- L62 _public prototype_ `FOptimusClothDataProviderProxy(USkinnedMeshComponent* SkinnedMeshComponent);`
- L65 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L66 _public prototype_ `void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L67 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData);`
- L71 _private typedef_ `using FParameters = FClothDataInterfaceParameters;`
- L73 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L74 _private member_ `FPrimitiveComponentId ComponentId;`
- L75 _private member_ `float ClothBlendWeight = 1.0f;`
- L76 _private member_ `FVector3f MeshScale = FVector3f::OneVector;`
- L77 _private member_ `uint32 FrameNumber = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceConnectivity.h` (Private)


#### class `UOptimusConnectivityDataInterface`  
`class UOptimusConnectivityDataInterface : public UOptimusComputeDataInterface`  
_L22-49_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading skeletal mesh.
- L28 _public prototype_ `FString GetDisplayName() const override;`
- L29 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L30 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L34 _public function_ `TCHAR const* GetClassName() const override`
- L35 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L36 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L37 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L38 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L39 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L40 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L41 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L45 _public member_ `static const int32 MaxConnectedVertexCount = 12;` — Hardcoded max connected count.
- L48 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusConnectivityDataProvider`  
`class UOptimusConnectivityDataProvider : public UComputeDataProvider`  
_L53-65_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L58 _public member_ `TWeakObjectPtr<USkinnedMeshComponent> SkinnedMesh = nullptr;`
- L61 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L64 _public member_ `TArray< TArray<uint32> > AdjacencyBufferPerLod;`

#### class `FOptimusConnectivityDataProviderProxy`  
`class FOptimusConnectivityDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L67-87_
- inherits: `FComputeDataProviderRenderProxy`
- L70 _public prototype_ `FOptimusConnectivityDataProviderProxy(USkinnedMeshComponent* SkinnedMeshComponent, TArray< TArray<uint32> >& InAdjacencyBufferPerLod);`
- L73 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L74 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L75 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData);`
- L79 _private typedef_ `using FParameters = FConnectivityDataInterfaceParameters;`
- L81 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L82 _private member_ `FPrimitiveComponentId ComponentId;`
- L83 _private member_ `TArray< TArray<uint32> > const& AdjacencyBufferPerLod;`
- L85 _private member_ `FRDGBuffer* ConnectivityBuffer = nullptr;`
- L86 _private member_ `FRDGBufferSRV* ConnectivityBufferSRV = nullptr;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceCopyKernel.h` (Private)


#### class `UOptimusCopyKernelDataInterface`  
`class UOptimusCopyKernelDataInterface : public UComputeDataInterface, public IOptimusComputeKernelDataInterface`  
_L21-61_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UComputeDataInterface,IOptimusComputeKernelDataInterface`
- L29 _public function_ `TCHAR const* GetClassName() const override`
- L30 _public function_ `bool IsExecutionInterface() const override`
- L31 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L32 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L33 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L34 _public prototype_ `const TCHAR* GetShaderVirtualPath() const override;`
- L35 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L36 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L37 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L41 _public prototype_ `void SetExecutionDomain(const FString& InExecutionDomain) override;`
- L42 _public prototype_ `void SetComponentBinding(const UOptimusComponentSourceBinding* InBinding) override;`
- L43 _public prototype_ `const FString& GetExecutionDomain() const override;`
- L44 _public prototype_ `const TCHAR* GetReadNumThreadsFunctionName() const override;`
- L45 _public prototype_ `const TCHAR* GetReadNumThreadsPerInvocationFunctionName() const override;`
- L46 _public prototype_ `const TCHAR* GetReadThreadIndexOffsetFunctionName() const override;`
- L50 _public member_ `TWeakObjectPtr<const UOptimusComponentSourceBinding> ComponentSourceBinding;` — `UPROPERTY()`
- L53 _public member_ `FString NumThreadsExpression;` — `UPROPERTY()`
- L56 _protected member_ `static const TCHAR* TemplateFilePath;`
- L58 _protected member_ `static const TCHAR* ReadNumThreadsFunctionName;`
- L59 _protected member_ `static const TCHAR* ReadNumThreadsPerInvocationFunctionName;`
- L60 _protected member_ `static const TCHAR* ReadThreadIndexOffsetFunctionName;`

#### class `UOptimusCopyKernelDataProvider`  
`class UOptimusCopyKernelDataProvider : public UComputeDataProvider`  
_L65-81_
- reflection: `UCLASS()`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for each copy kernel.
- L71 _public prototype_ `void InitFromDataInterface(const UOptimusCopyKernelDataInterface* InDataInterface, const UObject* InBinding);`
- L74 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L78 _protected member_ `TWeakObjectPtr<const UActorComponent> WeakComponent = nullptr;`
- L79 _protected member_ `TWeakObjectPtr<const UOptimusComponentSource> WeakComponentSource = nullptr;`
- L80 _protected member_ `TVariant<Optimus::Expression::FExpressionObject, Optimus::Expression::FParseError> ParseResult;`

#### class `FOptimusCopyKernelDataProviderProxy`  
`class FOptimusCopyKernelDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L83-100_
- inherits: `FComputeDataProviderRenderProxy`
- L86 _public prototype_ `FOptimusCopyKernelDataProviderProxy( TArray<int32>&& InInvocationThreadCounts );`
- L91 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L92 _public prototype_ `int32 GetDispatchThreadCount(TArray<FIntVector>& InOutThreadCounts) const override;`
- L93 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L97 _private member_ `TArray<int32> InvocationThreadCounts;`
- L98 _private member_ `int32 TotalThreadCount = 0;`
- L99 _private typedef_ `using FParameters = FCopyKernelDataInterfaceParameters;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceCustomComputeKernel.h` (Private)


#### class `UOptimusCustomComputeKernelDataInterface`  
`class UOptimusCustomComputeKernelDataInterface : public UComputeDataInterface, public IOptimusComputeKernelDataInterface`  
_L23-67_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UComputeDataInterface,IOptimusComputeKernelDataInterface`
- L31 _public function_ `TCHAR const* GetClassName() const override`
- L32 _public function_ `bool IsExecutionInterface() const override`
- L33 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L35 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L36 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L37 _public prototype_ `const TCHAR* GetShaderVirtualPath() const override;`
- L38 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L39 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L40 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L44 _public prototype_ `void SetExecutionDomain(const FString& InExecutionDomain) override;`
- L45 _public prototype_ `void SetComponentBinding(const UOptimusComponentSourceBinding* InBinding) override;`
- L46 _public prototype_ `const FString& GetExecutionDomain() const override;`
- L47 _public prototype_ `const TCHAR* GetReadNumThreadsFunctionName() const override;`
- L48 _public prototype_ `const TCHAR* GetReadNumThreadsPerInvocationFunctionName() const override;`
- L49 _public prototype_ `const TCHAR* GetReadThreadIndexOffsetFunctionName() const override;`
- L53 _public member_ `TWeakObjectPtr<const UOptimusComponentSourceBinding> ComponentSourceBinding;` — `UPROPERTY()`
- L56 _public member_ `FString NumThreadsExpression;` — `UPROPERTY()`
- L59 _public member_ `FOptimusConstantIdentifier ExecutionDomainConstantIdentifier_DEPRECATED;` — `UPROPERTY()`
- L62 _protected member_ `static const TCHAR* TemplateFilePath;`
- L64 _protected member_ `static const TCHAR* ReadNumThreadsFunctionName;`
- L65 _protected member_ `static const TCHAR* ReadNumThreadsPerInvocationFunctionName;`
- L66 _protected member_ `static const TCHAR* ReadThreadIndexOffsetFunctionName;`

#### class `UOptimusCustomComputeKernelDataProvider`  
`class UOptimusCustomComputeKernelDataProvider : public UComputeDataProvider`  
_L71-87_
- reflection: `UCLASS()`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for each custom compute kernel.
- L77 _public prototype_ `void InitFromDataInterface(const UOptimusCustomComputeKernelDataInterface* InDataInterface, const UObject* InBinding);`
- L80 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L84 _protected member_ `TWeakObjectPtr<const UActorComponent> WeakComponent = nullptr;`
- L85 _protected member_ `TWeakObjectPtr<const UOptimusComponentSource> WeakComponentSource = nullptr;`
- L86 _protected member_ `TVariant<Optimus::Expression::FExpressionObject, Optimus::Expression::FParseError> ParseResult;`

#### class `FOptimusCustomComputeKernelDataProviderProxy`  
`class FOptimusCustomComputeKernelDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L89-106_
- inherits: `FComputeDataProviderRenderProxy`
- L92 _public prototype_ `FOptimusCustomComputeKernelDataProviderProxy( TArray<int32>&& InInvocationThreadCounts );`
- L97 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L98 _public prototype_ `int32 GetDispatchThreadCount(TArray<FIntVector>& InOutThreadCounts) const override;`
- L99 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L103 _private member_ `TArray<int32> InvocationThreadCounts;`
- L104 _private member_ `int32 TotalThreadCount = 0;`
- L105 _private typedef_ `using FParameters = FCustomComputeKernelDataInterfaceParameters;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceDebugDraw.h` (Private)


#### struct `FOptimusDebugDrawParameters`  
`struct FOptimusDebugDrawParameters`  
_L18-40_
- reflection: `USTRUCT()`
- desc: User controllable debug draw settings.
- L27 _public member_ `bool bForceEnable = false;` — `UPROPERTY(EditAnywhere, Category = DebugDraw)` — Force enable debug rendering. Otherwise "r.ShaderPrint 1" needs to be set.
- L30 _public member_ `int32 MaxLineCount = 10000;` — `UPROPERTY(EditAnywhere, Category = DebugDraw)` — Space to allocate for line collection.
- L33 _public member_ `int32 MaxTriangleCount = 2000;` — `UPROPERTY(EditAnywhere, Category = DebugDraw)` — Space to allocate for triangle collection.
- L36 _public member_ `int32 MaxCharacterCount = 2000;` — `UPROPERTY(EditAnywhere, Category = DebugDraw)` — Space to allocate for character collection.
- L39 _public member_ `int32 FontSize = 8;` — `UPROPERTY(EditAnywhere, Category = DebugDraw)` — Font size for characters.

#### class `UOptimusDebugDrawDataInterface`  
`class UOptimusDebugDrawDataInterface : public UOptimusComputeDataInterface`  
_L46-82_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Debug Draw Data Interface provides access to a set of debug drawing hlsl functions
- L51 _public prototype_ `UOptimusDebugDrawDataInterface();`
- L54 _public prototype_ `FString GetDisplayName() const override;`
- L55 _public prototype_ `FName GetCategory() const override;`
- L56 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L57 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L58 _public prototype_ `void RegisterTypes() override;`
- L59 _public prototype_ `TOptional<FText> ValidateForCompile() const override;`
- L63 _public function_ `TCHAR const* GetClassName() const override`
- L64 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L65 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L66 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L67 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L68 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L69 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L70 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L75 _public member_ `bool bIsSupported = false;` — `UPROPERTY(Transient, VisibleAnywhere, Category = DebugDraw, meta=(EditConditionHides, EditCondition="!bIsSupported"))` — Make sure DirectX12 and Shader Model 6 is enabled in project settings for DebugDraw to function, since DXC is required for shader compilation.
- L78 _public member_ `FOptimusDebugDrawParameters DebugDrawParameters;` — `UPROPERTY(EditAnywhere, Category = DebugDraw, meta = (ShowOnlyInnerProperties))`
- L81 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusDebugDrawDataProvider`  
`class UOptimusDebugDrawDataProvider : public UComputeDataProvider`  
_L86-98_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for writing skinned mesh.
- L91 _public member_ `TWeakObjectPtr<UPrimitiveComponent> PrimitiveComponent = nullptr;`
- L93 _public member_ `FOptimusDebugDrawParameters DebugDrawParameters;`
- L96 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusDebugDrawDataProviderProxy`  
`class FOptimusDebugDrawDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L100-119_
- inherits: `FComputeDataProviderRenderProxy`
- L103 _public prototype_ `FOptimusDebugDrawDataProviderProxy(UPrimitiveComponent* InPrimitiveComponent, FOptimusDebugDrawParameters const& InDebugDrawParameters);`
- L106 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L107 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L108 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L112 _private typedef_ `using FParameters = FDebugDrawDataInterfaceParameters;`
- L114 _private member_ `FSceneInterface const* Scene;`
- L115 _private member_ `FMatrix44f LocalToWorld;`
- L116 _private member_ `ShaderPrint::FShaderPrintSetup Setup;`
- L117 _private member_ `ShaderPrint::FShaderPrintCommonParameters ConfigParameters;`
- L118 _private member_ `ShaderPrint::FShaderParameters CachedParameters;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceDuplicateVertices.h` (Private)


#### class `UOptimusDuplicateVerticesDataInterface`  
`class UOptimusDuplicateVerticesDataInterface : public UOptimusComputeDataInterface`  
_L23-47_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading duplicate vertices on a mesh. These are vertices that are at the same location but that have been split because of discontinous color/UV etc.
- L29 _public prototype_ `FString GetDisplayName() const override;`
- L30 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L31 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L35 _public function_ `TCHAR const* GetClassName() const override`
- L36 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L37 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L38 _public prototype_ `void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L39 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L40 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L41 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L42 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L46 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusDuplicateVerticesDataProvider`  
`class UOptimusDuplicateVerticesDataProvider : public UComputeDataProvider`  
_L51-61_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L56 _public member_ `TWeakObjectPtr<USkinnedMeshComponent> SkinnedMesh = nullptr;`
- L59 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusDuplicateVerticesDataProviderProxy`  
`class FOptimusDuplicateVerticesDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L63-79_
- inherits: `FComputeDataProviderRenderProxy`
- L66 _public prototype_ `FOptimusDuplicateVerticesDataProviderProxy(USkinnedMeshComponent* SkinnedMeshComponent);`
- L69 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L70 _public prototype_ `void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L71 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L75 _private typedef_ `using FParameters = FDuplicateVerticesDataInterfaceParameters;`
- L77 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L78 _private member_ `FPrimitiveComponentId ComponentId;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceGraph.h` (Private)


#### struct `FOptimusGraphVariableDescription`  
`struct FOptimusGraphVariableDescription`  
_L22-51_
- reflection: `USTRUCT()`
- L27 _public member_ `FString Name;` — `UPROPERTY()`
- L30 _public member_ `FShaderValueTypeHandle ValueType;` — `UPROPERTY()`
- L33 _public member_ `FOptimusValueIdentifier ValueId;` — `UPROPERTY()`
- L36 _public member_ `int32 Offset = 0;` — `UPROPERTY()`
- L39 _public member_ `int32 CachedArrayIndexStart = 0;` — Cache below are set by the data provider, computed from serialized data
- L44 _public member_ `TArray<uint8> Value_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use ShaderValue instead"))` — Deprecated
- L47 _public member_ `FShaderValueContainer ShaderValue_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Values are now store on the deformer instance"))`
- L50 _public member_ `TSoftObjectPtr<UObject> SourceObject_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Node-Value mapping is now handled by deformer instance directly"))`

#### class `UOptimusGraphDataInterface`  
`class UOptimusGraphDataInterface : public UComputeDataInterface`  
_L55-83_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UComputeDataInterface`
- desc: Compute Framework Data Interface used for marshaling compute graph parameters and variables.
- L60 _public prototype_ `void Init(TArray<FOptimusGraphVariableDescription> const& InVariables);`
- L61 _public prototype_ `int32 FindFunctionIndex(const FOptimusValueIdentifier& InValueId) const;`
- L64 _public function_ `TCHAR const* GetClassName() const override`
- L65 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L66 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L67 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L68 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L69 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L72 _public prototype_ `void PostLoad() override;`
- L79 _private member_ `TArray<FOptimusGraphVariableDescription> Variables;` — `UPROPERTY()`
- L82 _private member_ `int32 ParameterBufferSize = 0;` — `UPROPERTY()`

#### class `UOptimusGraphDataProvider`  
`class UOptimusGraphDataProvider : public UComputeDataProvider, public IOptimusDeformerInstanceAccessor`  
_L87-122_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider,IOptimusDeformerInstanceAccessor`
- desc: Compute Framework Data Provider for marshaling compute graph parameters and variables.
- L96 _public member_ `TArray<FOptimusGraphVariableDescription> Variables;` — `UPROPERTY()`
- L98 _public member_ `int32 ParameterBufferSize = 0;`
- L107 _public member_ `TArray<FArrayMetadata> ParameterArrayMetadata;`
- L110 _public prototype_ `void Init(const TArray<FOptimusGraphVariableDescription>& InVariables, int32 InParameterBufferSize);`
- L113 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L117 _public prototype_ `void SetDeformerInstance(UOptimusDeformerInstance* InInstance) override;`
- L121 _private member_ `TWeakObjectPtr<UOptimusDeformerInstance> WeakDeformerInstance = nullptr;`

#### struct `UOptimusGraphDataProvider::FArrayMetadata`  
`struct FArrayMetadata`  
_L101-105_
- L103 _public member_ `int32 Offset;`
- L104 _public member_ `int32 ElementSize;`

#### class `FOptimusGraphDataProviderProxy`  
`class FOptimusGraphDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L124-147_
- inherits: `FComputeDataProviderRenderProxy`
- L127 _public prototype_ `FOptimusGraphDataProviderProxy( UOptimusDeformerInstance const* DeformerInstance, TArray<FOptimusGraphVariableDescription> const& Variables, int32 ParameterBufferSize, TArray<UOptimusGraphDataProvider::FArrayMetadata> const& InParameterArrayMetadata);`
- L134 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L135 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L136 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L140 _private member_ `TArray<uint8> ParameterData;`
- L142 _private member_ `TArray<UOptimusGraphDataProvider::FArrayMetadata> ParameterArrayMetadata;`
- L143 _private member_ `TArray<FArrayShaderValue> ParameterArrayData;`
- L145 _private member_ `TArray<FRDGBuffer*> ParameterArrayBuffers;`
- L146 _private member_ `TArray<FRDGBufferSRV*> ParameterArrayBufferSRVs;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceHalfEdge.h` (Private)


#### class `UOptimusHalfEdgeDataInterface`  
`class UOptimusHalfEdgeDataInterface : public UOptimusComputeDataInterface`  
_L30-54_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Half Edge Data Interface provides vertex connectivity info, even across material sections, see ComputeNormalsTangents deformer function for example usage. Skeletal mesh assets using this data interface should have "BuildHalfEdgeBuffers" turned on under LODInfo settings
- L36 _public prototype_ `FString GetDisplayName() const override;`
- L37 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L38 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L42 _public function_ `TCHAR const* GetClassName() const override`
- L43 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L44 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L45 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L46 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L47 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L48 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L49 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L53 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusHalfEdgeDataProvider`  
`class UOptimusHalfEdgeDataProvider : public UComputeDataProvider, public IOptimusDeformerAssetPathAccessor`  
_L58-89_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider,IOptimusDeformerAssetPathAccessor`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L66 _public member_ `TWeakObjectPtr<USkinnedMeshComponent> SkinnedMesh = nullptr;`
- L69 _public prototype_ `void BeginDestroy() override;`
- L70 _public prototype_ `bool IsReadyForFinishDestroy() override;`
- L74 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L78 _public prototype_ `void SetOptimusDeformerAssetPath(const FTopLevelAssetPath& InPath) override;` — IOptimusDeformerAssetPathAccessor
- L80 _public member_ `TArray<FHalfEdgeBuffers> OnDemandHalfEdgeBuffers;`
- L81 _public member_ `FRenderCommandFence DestroyFence;`
- L85 _protected prototype_ `void ValidateSkinnedAsset();`
- L86 _protected member_ `FTopLevelAssetPath DeformerAssetPath;`
- L87 _protected member_ `TSet<TWeakObjectPtr<USkinnedAsset>> ValidatedAssets;`

#### class `FOptimusHalfEdgeDataProviderProxy`  
`class FOptimusHalfEdgeDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L91-117_
- inherits: `FComputeDataProviderRenderProxy`
- L94 _public prototype_ `FOptimusHalfEdgeDataProviderProxy( USkinnedMeshComponent* InSkinnedMeshComponent, TArray<FHalfEdgeBuffers>& InOnDemandHalfEdgeBuffers);`
- L99 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L100 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L101 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData);`
- L105 _private typedef_ `using FParameters = FHalfEdgeDataInterfaceParameters;`
- L107 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L108 _private member_ `FPrimitiveComponentId ComponentId;`
- L110 _private member_ `TArray<FHalfEdgeBuffers>& OnDemandHalfEdgeBuffers;`
- L112 _private member_ `bool bUseBufferFromRenderData = false;`
- L113 _private member_ `FRDGBufferSRV* VertexToEdgeBufferSRV = nullptr;`
- L114 _private member_ `FRDGBufferSRV* EdgeToTwinEdgeBufferSRV = nullptr;`
- L116 _private member_ `FRDGBufferSRVRef FallbackSRV = nullptr;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceLoopTerminal.h` (Private)


#### class `UOptimusLoopTerminalDataInterface`  
`class UOptimusLoopTerminalDataInterface : public UOptimusComputeDataInterface`  
_L14-47_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading loop data.
- L20 _public function_ `FString GetDisplayName() const override`
- L21 _public function_ `bool IsVisible() const override`
- L22 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L23 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L27 _public function_ `TCHAR const* GetClassName() const override`
- L28 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L29 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L30 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L31 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L32 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L33 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L34 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L40 _private member_ `static TCHAR const* TemplateFilePath;`
- L43 _private member_ `uint32 Index = 0;` — `UPROPERTY()`
- L46 _private member_ `uint32 Count = 0;` — `UPROPERTY()`

#### class `UOptimusLoopTerminalDataProvider`  
`class UOptimusLoopTerminalDataProvider : public UComputeDataProvider`  
_L51-63_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading loop data.
- L57 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L60 _public member_ `uint32 Index = 0;`
- L62 _public member_ `uint32 Count = 0;`

#### class `FOptimusLoopTerminalDataProviderProxy`  
`class FOptimusLoopTerminalDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L65-80_
- inherits: `FComputeDataProviderRenderProxy`
- L68 _public prototype_ `FOptimusLoopTerminalDataProviderProxy(uint32 InIndex, uint32 InCount);`
- L71 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L72 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L76 _private typedef_ `using FParameters = FLoopTerminalDataInterfaceParameters;`
- L78 _private member_ `uint32 Index = 0;`
- L79 _private member_ `uint32 Count = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceMorphTarget.h` (Private)


#### class `UOptimusMorphTargetDataInterface`  
`class UOptimusMorphTargetDataInterface : public UOptimusComputeDataInterface`  
_L20-45_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading skeletal mesh.
- L26 _public prototype_ `FString GetDisplayName() const override;`
- L27 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L28 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L32 _public function_ `TCHAR const* GetClassName() const override`
- L33 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L34 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L35 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L36 _public prototype_ `void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L37 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L38 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L39 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L40 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L44 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusMorphTargetDataProvider`  
`class UOptimusMorphTargetDataProvider : public UComputeDataProvider`  
_L49-59_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L54 _public member_ `TWeakObjectPtr<USkinnedMeshComponent> SkinnedMesh = nullptr;`
- L57 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusMorphTargetDataProviderProxy`  
`class FOptimusMorphTargetDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L61-78_
- inherits: `FComputeDataProviderRenderProxy`
- L64 _public prototype_ `FOptimusMorphTargetDataProviderProxy(USkinnedMeshComponent* SkinnedMeshComponent);`
- L67 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L68 _public prototype_ `void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L69 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData);`
- L73 _private typedef_ `using FParameters = FMorphTargetDataInterfaceParameters;`
- L75 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L76 _private member_ `FPrimitiveComponentId ComponentId;`
- L77 _private member_ `uint32 FrameNumber = 0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceRawBuffer.h` (Private)


#### enum `EOptimusBufferReadType`  
`enum class EOptimusBufferReadType : uint8`  
_L27-32_
- L29 _public enumerator_ `ReadSize`
- L30 _public enumerator_ `Default`
- L31 _public enumerator_ `ForceUAV`

#### enum `EOptimusBufferWriteType`  
`enum class EOptimusBufferWriteType : uint8`  
_L36-43_
- reflection: `UENUM()`
- desc: Write to buffer operation types.
- L38 _public enumerator_ `Write UMETA(ToolTip = "Write the value to resource buffer.")`
- L39 _public enumerator_ `WriteAtomicAdd UMETA(ToolTip = "AtomicAdd the value to the value in the resource buffer.")`
- L40 _public enumerator_ `WriteAtomicMin UMETA(ToolTip = "AtomicMin the value with the value in the resource buffer.")`
- L41 _public enumerator_ `WriteAtomicMax UMETA(ToolTip = "AtomicMax the value with the value in the resource buffer.")`
- L42 _public enumerator_ `Count UMETA(Hidden)`

#### class `UOptimusRawBufferDataInterface`  
`class UOptimusRawBufferDataInterface : public UOptimusComputeDataInterface`  
_L46-109_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UOptimusComputeDataInterface`
- L51 _public prototype_ `static int32 GetReadValueInputIndex(EOptimusBufferReadType ReadType = EOptimusBufferReadType::Default);`
- L52 _public prototype_ `static int32 GetWriteValueOutputIndex(EOptimusBufferWriteType WriteType);`
- L55 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L56 _public function_ `bool IsVisible() const override`
- L57 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L61 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L62 _public prototype_ `void GetSupportedOutputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L63 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L64 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L65 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L70 _public member_ `FShaderValueTypeHandle ValueType;` — `UPROPERTY()` — The value type we should be allocating elements for
- L74 _public member_ `FOptimusDataDomain DataDomain;` — `UPROPERTY()` — The data domain this buffer covers
- L78 _public member_ `TWeakObjectPtr<UOptimusComponentSourceBinding> ComponentSourceBinding;` — `UPROPERTY()` — The component source to query component domain validity and sizing
- L81 _public member_ `FOptimusConstantIdentifier DomainConstantIdentifier_DEPRECATED;` — `UPROPERTY()`
- L84 _protected function_ `virtual bool UseSplitBuffers() const`
- L86 _protected prototype_ `int32 GetRawStride() const;`
- L89 _protected function_ `template<typename U> U* CreateProvider(TObjectPtr<UObject> InBinding) const`
- L104 _private member_ `static TCHAR const* TemplateFilePath;`
- L106 _private prototype_ `const UOptimusComponentSource* GetComponentSource() const;`
- L107 _private prototype_ `bool SupportsAtomics() const;`
- L108 _private prototype_ `FString GetRawType() const;`

#### class `UOptimusTransientBufferDataInterface`  
`class UOptimusTransientBufferDataInterface : public UOptimusRawBufferDataInterface`  
_L114-132_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusRawBufferDataInterface`
- desc: Compute Framework Data Interface for a transient buffer.
- L120 _public prototype_ `FString GetDisplayName() const override;`
- L124 _public function_ `TCHAR const* GetClassName() const override`
- L125 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L126 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L127 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L131 _public member_ `bool bZeroInitForAtomicWrites = false;` — `UPROPERTY()`

#### class `UOptimusImplicitPersistentBufferDataInterface`  
`class UOptimusImplicitPersistentBufferDataInterface : public UOptimusRawBufferDataInterface`  
_L136-155_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusRawBufferDataInterface`
- desc: Compute Framework Data Interface for a implicit persistent buffer.
- L142 _public prototype_ `FString GetDisplayName() const override;`
- L147 _public function_ `TCHAR const* GetClassName() const override`
- L148 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L149 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L150 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L154 _public member_ `bool bZeroInitForAtomicWrites = false;` — `UPROPERTY()`

#### class `UOptimusPersistentBufferDataInterface`  
`class UOptimusPersistentBufferDataInterface : public UOptimusRawBufferDataInterface`  
_L160-183_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusRawBufferDataInterface`
- desc: Compute Framework Data Interface for a transient buffer.
- L167 _public prototype_ `FString GetDisplayName() const override;`
- L171 _public function_ `TCHAR const* GetClassName() const override`
- L172 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L173 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L174 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L178 _public member_ `FName ResourceName;` — `UPROPERTY()`
- L182 _protected function_ `bool UseSplitBuffers() const override` — For persistent buffers, we only provide the UAV, not the SRV.

#### class `UOptimusRawBufferDataProvider`  
`class UOptimusRawBufferDataProvider : public UComputeDataProvider`  
_L188-213_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for a transient buffer.
- L198 _public prototype_ `bool GetLodAndInvocationElementCounts( int32& OutLodIndex, TArray<int32>& OutInvocationElementCounts ) const;` — Helper function to calculate the element count for each section invocation of the given skinned/skeletal mesh object and a data domain. Uses the execution domains to compute the information. Returns false if the data domain is not valid for computation.
- L204 _public member_ `TWeakObjectPtr<const UActorComponent> Component = nullptr;` — The skinned mesh component that governs the sizing and LOD of this buffer
- L206 _public member_ `TWeakObjectPtr<const UOptimusComponentSource> ComponentSource = nullptr;`
- L208 _public member_ `int32 ElementStride = 4;`
- L210 _public member_ `int32 RawStride = 0;`
- L212 _public member_ `TVariant<Optimus::Expression::FExpressionObject, Optimus::Expression::FParseError> DataDomainExpressionParseResult;`

#### class `UOptimusTransientBufferDataProvider`  
`class UOptimusTransientBufferDataProvider : public UOptimusRawBufferDataProvider`  
_L218-228_
- reflection: `UCLASS(MinimalAPI, BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UOptimusRawBufferDataProvider`
- desc: Compute Framework Data Provider for a transient buffer.
- L224 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L227 _public member_ `bool bZeroInitForAtomicWrites = false;`

#### class `UOptimusImplicitPersistentBufferDataProvider`  
`class UOptimusImplicitPersistentBufferDataProvider : public UOptimusRawBufferDataProvider, public IOptimusPersistentBufferProvider`  
_L233-256_
- reflection: `UCLASS(MinimalAPI, BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UOptimusRawBufferDataProvider,IOptimusPersistentBufferProvider`
- desc: Compute Framework Data Provider for a transient buffer.
- L241 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L245 _public function_ `void SetBufferPool(TSharedPtr<FOptimusPersistentBufferPool> InBufferPool) override`
- L248 _public member_ `bool bZeroInitForAtomicWrites = false;`
- L250 _public member_ `FName DataInterfaceName = NAME_None;`
- L255 _private member_ `TSharedPtr<FOptimusPersistentBufferPool> BufferPool;` — The buffer pool we refer to. Set by UOptimusDeformerInstance::SetupFromDeformer after providers have been created

#### class `UOptimusPersistentBufferDataProvider`  
`class UOptimusPersistentBufferDataProvider : public UOptimusRawBufferDataProvider, public IOptimusPersistentBufferProvider`  
_L260-283_
- reflection: `UCLASS(MinimalAPI, BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UOptimusRawBufferDataProvider,IOptimusPersistentBufferProvider`
- desc: Compute Framework Data Provider for a transient buffer.
- L268 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L272 _public function_ `void SetBufferPool(TSharedPtr<FOptimusPersistentBufferPool> InBufferPool) override`
- L276 _public member_ `FName ResourceName;` — The resource this buffer is provider to
- L282 _private member_ `TSharedPtr<FOptimusPersistentBufferPool> BufferPool;` — The buffer pool we refer to. Set by UOptimusDeformerInstance::SetupFromDeformer after providers have been created

#### class `FOptimusTransientBufferDataProviderProxy`  
`class FOptimusTransientBufferDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L285-314_
- inherits: `FComputeDataProviderRenderProxy`
- L289 _public prototype_ `FOptimusTransientBufferDataProviderProxy( TArray<int32> InInvocationElementCounts, int32 InElementStride, int32 InRawStride, bool bInZeroInitForAtomicWrites );`
- L297 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L298 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L299 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L303 _private typedef_ `using FParameters = FTransientBufferDataInterfaceParameters;`
- L305 _private member_ `const TArray<int32> InvocationElementCounts;`
- L306 _private member_ `int32 TotalElementCount;`
- L307 _private member_ `const int32 ElementStride;`
- L308 _private member_ `const int32 RawStride;`
- L309 _private member_ `const bool bZeroInitForAtomicWrites;`
- L311 _private member_ `FRDGBufferRef Buffer;`
- L312 _private member_ `FRDGBufferSRVRef BufferSRV;`
- L313 _private member_ `FRDGBufferUAVRef BufferUAV;`

#### class `FOptimusImplicitPersistentBufferDataProviderProxy`  
`class FOptimusImplicitPersistentBufferDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L316-352_
- inherits: `FComputeDataProviderRenderProxy`
- L320 _public prototype_ `FOptimusImplicitPersistentBufferDataProviderProxy( TArray<int32> InInvocationElementCounts, int32 InElementStride, int32 InRawStride, bool bInZeroInitForAtomicWrites, TSharedPtr<FOptimusPersistentBufferPool> InBufferPool, FName InDataInterfaceName, int32 InLODIndex );`
- L331 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L332 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L333 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L337 _private typedef_ `using FParameters = FImplicitPersistentBufferDataInterfaceParameters;`
- L339 _private member_ `const TArray<int32> InvocationElementCounts;`
- L340 _private member_ `int32 TotalElementCount;`
- L341 _private member_ `const int32 ElementStride;`
- L342 _private member_ `const int32 RawStride;`
- L343 _private member_ `const bool bZeroInitForAtomicWrites;`
- L345 _private member_ `const TSharedPtr<FOptimusPersistentBufferPool> BufferPool;`
- L346 _private member_ `FName DataInterfaceName;`
- L347 _private member_ `int32 LODIndex;`
- L349 _private member_ `FRDGBufferRef Buffer;`
- L350 _private member_ `FRDGBufferSRVRef BufferSRV;`
- L351 _private member_ `FRDGBufferUAVRef BufferUAV;`

#### class `FOptimusPersistentBufferDataProviderProxy`  
`class FOptimusPersistentBufferDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L354-386_
- inherits: `FComputeDataProviderRenderProxy`
- L358 _public prototype_ `FOptimusPersistentBufferDataProviderProxy( TArray<int32> InInvocationElementCounts, int32 InElementStride, int32 InRawStride, TSharedPtr<FOptimusPersistentBufferPool> InBufferPool, FName InResourceName, int32 InLODIndex );`
- L368 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L369 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData);`
- L370 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L374 _private typedef_ `using FParameters = FPersistentBufferDataInterfaceParameters;`
- L376 _private member_ `const TArray<int32> InvocationElementCounts;`
- L377 _private member_ `int32 TotalElementCount;`
- L378 _private member_ `const int32 ElementStride;`
- L379 _private member_ `const int32 RawStride;`
- L380 _private member_ `const TSharedPtr<FOptimusPersistentBufferPool> BufferPool;`
- L381 _private member_ `const FName ResourceName;`
- L382 _private member_ `const int32 LODIndex;`
- L384 _private member_ `FRDGBufferRef Buffer;`
- L385 _private member_ `TArray<FRDGBufferUAVRef> BufferUAVs;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceScene.h` (Private)


#### class `UOptimusSceneDataInterface`  
`class UOptimusSceneDataInterface : public UOptimusComputeDataInterface`  
_L14-38_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading general scene data.
- L20 _public prototype_ `FString GetDisplayName() const override;`
- L21 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L22 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L26 _public function_ `TCHAR const* GetClassName() const override`
- L27 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L28 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L29 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L30 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L31 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L32 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L33 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L37 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusSceneDataProvider`  
`class UOptimusSceneDataProvider : public UComputeDataProvider`  
_L42-52_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading general scene data.
- L47 _public member_ `TWeakObjectPtr<USceneComponent> SceneComponent = nullptr;`
- L50 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusSceneDataProviderProxy`  
`class FOptimusSceneDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L54-71_
- inherits: `FComputeDataProviderRenderProxy`
- L57 _public prototype_ `FOptimusSceneDataProviderProxy(USceneComponent* SceneComponent);`
- L60 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L61 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L65 _private typedef_ `using FParameters = FSceneDataInterfaceParameters;`
- L67 _private member_ `bool bIsValid;`
- L68 _private member_ `float GameTime;`
- L69 _private member_ `float GameTimeDelta;`
- L70 _private member_ `uint32 FrameNumber;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceSceneComponent.h` (Private)


#### class `UOptimusSceneComponentDataInterface`  
`class UOptimusSceneComponentDataInterface : public UOptimusComputeDataInterface`  
_L14-38_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading general scene component data.
- L20 _public prototype_ `virtual FString GetDisplayName() const override;`
- L21 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L22 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L26 _public function_ `virtual TCHAR const* GetClassName() const override`
- L27 _public function_ `virtual bool CanSupportUnifiedDispatch() const override`
- L28 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L29 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L30 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L31 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L32 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L33 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider() const override;`
- L37 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusSceneComponentDataProvider`  
`class UOptimusSceneComponentDataProvider : public UComputeDataProvider`  
_L42-53_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading general scene data.
- L47 _public member_ `TWeakObjectPtr<USceneComponent> SceneComponent = nullptr;`
- L50 _public prototype_ `virtual void Initialize(const UComputeDataInterface* InDataInterface, UObject* InBinding, uint64 InInputMask, uint64 InOutputMask) override;`
- L51 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusSceneComponentDataProviderProxy`  
`class FOptimusSceneComponentDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L55-70_
- inherits: `FComputeDataProviderRenderProxy`
- L58 _public prototype_ `FOptimusSceneComponentDataProviderProxy(USceneComponent* SceneComponent);`
- L61 _public prototype_ `virtual bool IsValid(FValidationData const& InValidationData) const override;`
- L62 _public prototype_ `virtual void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L66 _private typedef_ `using FParameters = FSceneComponentDataInterfaceParameters;`
- L68 _private member_ `bool bIsValid = false;`
- L69 _private member_ `FTransform WorldTransform = FTransform::Identity;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceSkeleton.h` (Private)


#### class `UOptimusSkeletonDataInterface`  
`class UOptimusSkeletonDataInterface : public UOptimusComputeDataInterface`  
_L20-46_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for skeletal data. (Outdated)
- L26 _public prototype_ `FString GetDisplayName() const override;`
- L27 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L29 _public function_ `bool IsVisible() const override` — UOptimusAdvancedSkeletonDataInterface is now a better version of this data interface
- L30 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L34 _public function_ `TCHAR const* GetClassName() const override`
- L35 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L36 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L37 _public prototype_ `void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L38 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L39 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L40 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L41 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L45 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusSkeletonDataProvider`  
`class UOptimusSkeletonDataProvider : public UComputeDataProvider`  
_L50-60_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L55 _public member_ `TWeakObjectPtr<USkinnedMeshComponent> SkinnedMesh = nullptr;`
- L58 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusSkeletonDataProviderProxy`  
`class FOptimusSkeletonDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L62-79_
- inherits: `FComputeDataProviderRenderProxy`
- L65 _public prototype_ `FOptimusSkeletonDataProviderProxy(USkinnedMeshComponent* SkinnedMeshComponent);`
- L68 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L69 _public prototype_ `void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L70 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L74 _private typedef_ `using FParameters = FSkeletonDataInterfaceParameters;`
- L76 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L77 _private member_ `FPrimitiveComponentId ComponentId;`
- L78 _private member_ `uint32 BoneRevisionNumber = 0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceSkinWeightsAsVertexMask.h` (Private)


#### class `UOptimusSkinWeightsAsVertexMaskDataInterface`  
`class UOptimusSkinWeightsAsVertexMaskDataInterface : public UOptimusComputeDataInterface`  
_L25-86_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for merging skin weights of one or more bones into a per-vertex float map.
- L32 _public prototype_ `FString GetDisplayName() const override;`
- L33 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L34 _public prototype_ `TArray<FOptimusCDIPropertyPinDefinition> GetPropertyPinDefinitions() const override;`
- L35 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L37 _public prototype_ `void RegisterPropertyChangeDelegatesForOwningNode(UOptimusNode* InNode) override;`
- L42 _public function_ `TCHAR const* GetClassName() const override`
- L43 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L44 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L45 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L46 _public prototype_ `void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L47 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L48 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L49 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L50 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L54 _public member_ `FName SkinWeightProfile = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Data Interface")`
- L58 _public member_ `TArray<FName> BoneNames = {TEXT("Root` — `UPROPERTY(EditAnywhere, Category = "Data Interface")` — Weights of selected bones are combined to form a single a vertex weight map
- L62 _public member_ `int32 ExpandTowardsRoot = 0;` — `UPROPERTY(EditAnywhere, Category = "Data Interface")` — Include all bones within the radius by expanding selection towards the root
- L66 _public member_ `int32 ExpandTowardsLeaf = 999;` — `UPROPERTY(EditAnywhere, Category = "Data Interface")` — Include children up to the specified depth
- L69 _public member_ `bool bDebugDrawIncludedBones = true;` — `UPROPERTY(EditAnywhere, Category = "Debug")`
- L72 _public member_ `FColor DebugDrawColor = FColor::Green;` — `UPROPERTY(EditAnywhere, Category = "Debug")`
- L76 _private prototype_ `static FName GetSkinWeightProfilePropertyName();`
- L77 _private prototype_ `static FName GetBoneNamesPropertyName();`
- L78 _private prototype_ `static FName GetExpandTowardsRootPropertyName();`
- L79 _private prototype_ `static FName GetExpandTowardsLeafPropertyName();`
- L80 _private prototype_ `static FName GetDebugDrawIncludedBonesPropertyName();`
- L82 _private member_ `static TCHAR const* TemplateFilePath;`
- L83 _private member_ `FOnPinDefinitionChanged OnPinDefinitionChangedDelegate;`
- L84 _private member_ `FOnPinDefinitionRenamed OnPinDefinitionRenamedDelegate;`
- L85 _private member_ `FSimpleDelegate OnDisplayNameChangedDelegate;`

#### class `UOptimusSkinWeightsAsVertexMaskDataProvider`  
`class UOptimusSkinWeightsAsVertexMaskDataProvider : public UComputeDataProvider, public IOptimusDeformerInstanceAccessor`  
_L91-126_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider,IOptimusDeformerInstanceAccessor`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L99 _public prototype_ `void Init(const UOptimusSkinWeightsAsVertexMaskDataInterface* InDataInterface, USkeletalMeshComponent* InSkeletalMesh);`
- L101 _public prototype_ `void SetDeformerInstance(UOptimusDeformerInstance* InInstance) override;`
- L103 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkeletalMesh = nullptr;`
- L105 _public member_ `FName SkinWeightProfile = NAME_None;`
- L107 _public member_ `TArray<FName> BoneNames;`
- L108 _public member_ `int32 ExpandTowardsRoot = 0;`
- L109 _public member_ `int32 ExpandTowardsLeaf = 0;`
- L110 _public member_ `bool bDebugDrawIncludedBones = false;`
- L111 _public member_ `FColor DebugDrawColor = FColor::Green;`
- L113 _public member_ `bool bIsInitialized = false;`
- L114 _public member_ `TSet<int32> CachedSelectedBones;`
- L115 _public member_ `TArray<TArray<TArray<uint32>>> CachedBoneIsSelectedPerSectionPerLod;`
- L118 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L123 _private member_ `TWeakObjectPtr<UOptimusDeformerInstance> WeakDeformerInstance;`
- L125 _private member_ `TWeakObjectPtr<const UOptimusSkinWeightsAsVertexMaskDataInterface> WeakDataInterface;`

#### class `FOptimusSkinWeightsAsVertexMaskDataProviderProxy`  
`class FOptimusSkinWeightsAsVertexMaskDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L128-150_
- inherits: `FComputeDataProviderRenderProxy`
- L131 _public prototype_ `FOptimusSkinWeightsAsVertexMaskDataProviderProxy() = default;`
- L134 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L135 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L136 _public prototype_ `void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L137 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L140 _public typedef_ `using FParameters = FSkinWeightsAsVertexMaskDataInterfaceParameters;`
- L142 _public member_ `FSceneInterface* SceneInterface = nullptr;`
- L143 _public member_ `FPrimitiveComponentId ComponentId;`
- L145 _public member_ `FName SkinWeightProfile = NAME_None;`
- L147 _public member_ `TArray<TArray<TArray<uint32>>> BoneIsSelectedPerSectionPerLod;`
- L148 _public member_ `TArray<FRDGBufferRef> BoneIsSelectedBuffersPerSection;`
- L149 _public member_ `TArray<FRDGBufferSRVRef> BoneIsSelectedBufferSRVsPerSection;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceSkinnedMesh.h` (Private)


#### class `UOptimusSkinnedMeshDataInterface`  
`class UOptimusSkinnedMeshDataInterface : public UOptimusComputeDataInterface`  
_L21-45_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading data from the skeletal mesh asset
- L27 _public prototype_ `FString GetDisplayName() const override;`
- L28 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L29 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L33 _public function_ `TCHAR const* GetClassName() const override`
- L34 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L35 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L36 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L37 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L38 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L39 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L40 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L44 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusSkinnedMeshDataProvider`  
`class UOptimusSkinnedMeshDataProvider : public UComputeDataProvider`  
_L49-59_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L54 _public member_ `TWeakObjectPtr<USkinnedMeshComponent> SkinnedMesh = nullptr;`
- L57 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusSkinnedMeshDataProviderProxy`  
`class FOptimusSkinnedMeshDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L61-82_
- inherits: `FComputeDataProviderRenderProxy`
- L64 _public prototype_ `FOptimusSkinnedMeshDataProviderProxy(USkinnedMeshComponent* SkinnedMeshComponent);`
- L67 _public prototype_ `virtual bool IsValid(FValidationData const& InValidationData) const override;`
- L68 _public prototype_ `virtual void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L69 _public prototype_ `virtual void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L73 _private typedef_ `using FParameters = FSkinnedMeshDataInterfaceParameters;`
- L75 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L76 _private member_ `FPrimitiveComponentId ComponentId;`
- L78 _private member_ `FShaderResourceViewRHIRef IndexBufferSRV;`
- L79 _private member_ `FShaderResourceViewRHIRef TangentsSRV;`
- L80 _private member_ `FShaderResourceViewRHIRef TexCoordsSRV;`
- L81 _private member_ `FShaderResourceViewRHIRef ColorsSRV;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceSkinnedMeshExec.h` (Private)


#### enum `EOptimusSkinnedMeshExecDomain`  
`enum class EOptimusSkinnedMeshExecDomain : uint8`  
_L20-27_
- reflection: `UENUM()`
- L22 _public enumerator_ `None = 0 UMETA(Hidden)`
- L24 _public enumerator_ `Vertex = 1` — Run kernel with one thread per vertex.
- L26 _public enumerator_ `Triangle` — Run kernel with one thread per triangle.

#### class `UDEPRECATED_OptimusSkinnedMeshExecDataInterface`  
`class UDEPRECATED_OptimusSkinnedMeshExecDataInterface : public UOptimusComputeDataInterface, public IOptimusDeprecatedExecutionDataInterface`  
_L31-67_
- reflection: `UCLASS(MinimalAPI, Deprecated, Category = ComputeFramework, meta = (DeprecationMessage ="This execution interface has been replaced with kernel specific execution data interface, see UOptimusCustomComputeKernelDataInterface"))`
- inherits: `UOptimusComputeDataInterface,IOptimusDeprecatedExecutionDataInterface`
- desc: Compute Framework Data Interface for executing kernels over a skinned mesh domain.
- L39 _public prototype_ `FString GetDisplayName() const override;`
- L40 _public prototype_ `FName GetCategory() const override;`
- L41 _public function_ `bool IsVisible() const override`
- L42 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L43 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L47 _public function_ `TCHAR const* GetClassName() const override`
- L48 _public function_ `bool IsExecutionInterface() const override`
- L49 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L50 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L51 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L52 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L53 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L54 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L55 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L59 _public prototype_ `FName GetSelectedExecutionDomainName() const override;`
- L63 _public member_ `EOptimusSkinnedMeshExecDomain Domain = EOptimusSkinnedMeshExecDomain::Vertex;` — `UPROPERTY(EditAnywhere, Category = Execution)`
- L66 _private member_ `static TCHAR const* TemplateFilePath;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceSkinnedMeshRead.h` (Private)


#### class `UOptimusSkinnedMeshReadDataInterface`  
`class UOptimusSkinnedMeshReadDataInterface : public UOptimusComputeDataInterface`  
_L25-52_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading the current state of skinned mesh, which may have been deformed by deformers run earlier
- L32 _public prototype_ `FString GetDisplayName() const override;`
- L33 _public prototype_ `FName GetCategory() const override;`
- L34 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L35 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L39 _public function_ `TCHAR const* GetClassName() const override`
- L40 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L41 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L42 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L43 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L44 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L45 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L46 _public prototype_ `void GetDefines(FComputeKernelDefinitionSet& OutDefinitionSet) const override;`
- L47 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L51 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusSkinnedMeshReadDataProvider`  
`class UOptimusSkinnedMeshReadDataProvider : public UComputeDataProvider, public IOptimusDeformerInstanceAccessor`  
_L56-77_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider,IOptimusDeformerInstanceAccessor`
- desc: Compute Framework Data Provider for writing skinned mesh.
- L63 _public member_ `TWeakObjectPtr<USkinnedMeshComponent> SkinnedMesh = nullptr;`
- L65 _public member_ `uint64 InputMask = 0;`
- L68 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L72 _public prototype_ `void SetDeformerInstance(UOptimusDeformerInstance* InInstance) override;`
- L76 _private member_ `TWeakObjectPtr<UOptimusDeformerInstance> WeakDeformerInstance = nullptr;`

#### class `FOptimusSkinnedMeshReadDataProviderProxy`  
`class FOptimusSkinnedMeshReadDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L79-105_
- inherits: `FComputeDataProviderRenderProxy`
- L82 _public prototype_ `FOptimusSkinnedMeshReadDataProviderProxy(USkinnedMeshComponent* InSkinnedMeshComponent, uint64 InInputMask, bool bInIsPrimaryComponent, FName InReaderExecutionGroup);`
- L85 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L86 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L87 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L91 _private typedef_ `using FParameters = FSkinnedMeshReadDataInterfaceParameters;`
- L93 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L94 _private member_ `FPrimitiveComponentId ComponentId;`
- L95 _private member_ `uint64 InputMask = 0;`
- L96 _private member_ `bool bIsPrimaryComponent = true;`
- L97 _private member_ `FName ReaderExecutionGroup;`
- L99 _private member_ `FShaderResourceViewRHIRef TangentsSRV;`
- L100 _private member_ `FShaderResourceViewRHIRef ColorsSRV;`
- L102 _private member_ `FRDGBufferSRV* PositionBufferSRV = nullptr;`
- L103 _private member_ `FRDGBufferSRV* TangentBufferSRV = nullptr;`
- L104 _private member_ `FRDGBufferSRV* ColorBufferSRV = nullptr;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceSkinnedMeshVertexAttribute.h` (Private)


#### class `UOptimusSkinnedMeshVertexAttributeDataInterface`  
`class UOptimusSkinnedMeshVertexAttributeDataInterface : public UOptimusComputeDataInterface`  
_L20-51_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- L26 _private prototype_ `FString GetDisplayName() const override;`
- L27 _private prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L28 _private prototype_ `TArray<FOptimusCDIPropertyPinDefinition> GetPropertyPinDefinitions() const override;`
- L29 _private prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L33 _private function_ `TCHAR const* GetClassName() const override`
- L34 _private function_ `virtual bool CanSupportUnifiedDispatch() const override`
- L35 _private prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L36 _private prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L37 _private prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L38 _private prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L39 _private prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L43 _private member_ `FName AttributeName;` — `UPROPERTY(EditAnywhere, Category="Vertex Attribute")`
- L46 _private member_ `float DefaultValue;` — `UPROPERTY(EditAnywhere, Category="Vertex Attribute")`
- L49 _private prototype_ `static FName GetAttributeNamePropertyName();`
- L50 _private prototype_ `static FName GetDefaultValuePropertyName();`

#### class `UOptimusSkinnedMeshVertexAttributeDataProvider`  
`class UOptimusSkinnedMeshVertexAttributeDataProvider : public UComputeDataProvider, public IOptimusDeformerInstanceAccessor`  
_L56-82_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider,IOptimusDeformerInstanceAccessor`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L63 _public member_ `TWeakObjectPtr<USkinnedMeshComponent> SkinnedMeshComponent = nullptr;`
- L66 _public member_ `FName AttributeName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VertexAttribute)`
- L69 _public member_ `float DefaultValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VertexAttribute)`
- L71 _public member_ `TWeakObjectPtr<const UOptimusSkinnedMeshVertexAttributeDataInterface> WeakDataInterface;`
- L74 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L77 _public prototype_ `void SetDeformerInstance(UOptimusDeformerInstance* InInstance) override;`
- L81 _private member_ `TWeakObjectPtr<UOptimusDeformerInstance> WeakDeformerInstance;`

#### class `FOptimusSkinnedMeshVertexAttributeDataProviderProxy`  
`class FOptimusSkinnedMeshVertexAttributeDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L84-104_
- inherits: `FComputeDataProviderRenderProxy`
- L87 _public prototype_ `FOptimusSkinnedMeshVertexAttributeDataProviderProxy( USkinnedMeshComponent* InSkinnedMeshComponent, FName InAttributeName, float InDefaultValue);`
- L93 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L94 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L98 _private typedef_ `using FParameters = FSkinnedMeshVertexAttributeDataInterfaceParameters;`
- L100 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L101 _private member_ `FPrimitiveComponentId ComponentId;`
- L102 _private member_ `FName AttributeName;`
- L103 _private member_ `float DefaultValue;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/DataInterfaces/OptimusDataInterfaceSkinnedMeshWrite.h` (Private)


#### class `UOptimusSkinnedMeshWriteDataInterface`  
`class UOptimusSkinnedMeshWriteDataInterface : public UOptimusComputeDataInterface, public IOptimusOutputBufferWriter`  
_L31-67_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface,IOptimusOutputBufferWriter`
- desc: Compute Framework Data Interface for writing skinned mesh.
- L39 _public prototype_ `FString GetDisplayName() const override;`
- L40 _public prototype_ `FName GetCategory() const override;`
- L41 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L42 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L46 _public function_ `TCHAR const* GetClassName() const override`
- L47 _public function_ `bool CanSupportUnifiedDispatch() const override`
- L48 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L49 _public prototype_ `void GetSupportedOutputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L50 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L51 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L52 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L53 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L54 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L55 _public function_ `bool GetRequiresReadback() const override`
- L56 _public function_ `bool GetRequiresPostSubmitCall() const override`
- L59 _public function_ `bool GetRequiresPerKernelInputOutputMasks() const override` — This DI can be bound to several kernels writing different pins. PostSubmit needs the per-kernel breakdown so MarkDeformed only tags buffers that the submitted kernel actually wrote.
- L63 _public prototype_ `EMeshDeformerOutputBuffer GetOutputBuffer(int32 InBoundOutputFunctionIndex) const override;`
- L66 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusSkinnedMeshWriteDataProvider`  
`class UOptimusSkinnedMeshWriteDataProvider : public UComputeDataProvider, public IOptimusDeformerInstanceAccessor, public IOptimusDeformerGeometryReadbackProvider`  
_L73-112_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider,IOptimusDeformerInstanceAccessor,IOptimusDeformerGeometryReadbackProvider`
- desc: Compute Framework Data Provider for writing skinned mesh.
- L81 _public prototype_ `UOptimusSkinnedMeshWriteDataProvider() = default;`
- L82 _public prototype_ `~UOptimusSkinnedMeshWriteDataProvider() = default;`
- L83 _public prototype_ `UOptimusSkinnedMeshWriteDataProvider(FVTableHelper& Helper);`
- L85 _public member_ `TWeakObjectPtr<USkinnedMeshComponent> SkinnedMesh = nullptr;`
- L87 _public member_ `uint64 OutputMask = 0;`
- L89 _public member_ `TMap<int32, FInputOutputMask> PerKernelMasks;`
- L92 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L93 _public prototype_ `void InitializePerKernelInputOutputMasks(TMap<int32, FInputOutputMask>&& InPerKernelMasks) override;`
- L97 _public prototype_ `void SetDeformerInstance(UOptimusDeformerInstance* InInstance) override;`
- L102 _public prototype_ `bool RequestReadbackDeformerGeometry(TUniquePtr<FMeshDeformerGeometryReadbackRequest> InRequest) override;`
- L106 _private member_ `TWeakObjectPtr<UOptimusDeformerInstance> WeakDeformerInstance = nullptr;`
- L110 _private member_ `TArray<TUniquePtr<FMeshDeformerGeometryReadbackRequest>> GeometryReadbackRequests;` — Readback requests for the current frame

#### class `FOptimusSkinnedMeshWriteDataProviderProxy`  
`class FOptimusSkinnedMeshWriteDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L114-158_
- inherits: `FComputeDataProviderRenderProxy`
- L118 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L119 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L120 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L121 _public prototype_ `void PostSubmit(FComputeContext& Context) const override;`
- L122 _public prototype_ `void GetReadbackData(TArray<FReadbackData>& OutReadbackData) const override;`
- L125 _public member_ `FSceneInterface* SceneInterface = nullptr;`
- L126 _public member_ `FPrimitiveComponentId ComponentId;`
- L127 _public member_ `uint64 OutputMask = 0;`
- L128 _public member_ `TMap<int32, UComputeDataProvider::FInputOutputMask> PerKernelMasks;`
- L129 _public member_ `FName ExecutionGroup;`
- L133 _public member_ `int32 FrameNumber = 0;`
- L135 _public member_ `USkeletalMesh* SkeletalMeshAsset = nullptr;`
- L137 _public member_ `mutable TArray<TUniquePtr<FMeshDeformerGeometryReadbackRequest>> GeometryReadbackRequests;` — Readback requests for the current frame
- L146 _public member_ `)> RequestGeometryReadback_RenderThread;`
- L150 _private typedef_ `using FParameters = FSkinedMeshWriteDataInterfaceParameters;`
- L152 _private member_ `FRDGBuffer* PositionBuffer = nullptr;`
- L153 _private member_ `FRDGBufferUAV* PositionBufferUAV = nullptr;`
- L154 _private member_ `FRDGBuffer* TangentBuffer = nullptr;`
- L155 _private member_ `FRDGBufferUAV* TangentBufferUAV = nullptr;`
- L156 _private member_ `FRDGBuffer* ColorBuffer = nullptr;`
- L157 _private member_ `FRDGBufferUAV* ColorBufferUAV = nullptr;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_AnimAttributeDataInterface.h` (Private)


#### class `UOptimusNode_AnimAttributeDataInterface`  
`class UOptimusNode_AnimAttributeDataInterface : public UOptimusNode_DataInterface`  
_L11-40_
- reflection: `UCLASS(Hidden)`
- inherits: `UOptimusNode_DataInterface`
- desc: Deprecated
- L17 _public prototype_ `UOptimusNode_AnimAttributeDataInterface();`
- L20 _public prototype_ `virtual void SetDataInterfaceClass(TSubclassOf<UOptimusComputeDataInterface> InDataInterfaceClass) override;` — UOptimusNode_DataInterface overrides
- L23 _public prototype_ `void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L27 _public prototype_ `virtual void OnDataTypeChanged(FName InTypeName) override;`
- L31 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;` — UObject overrides
- L34 _private prototype_ `void UpdatePinTypes();`
- L35 _private prototype_ `void UpdatePinNames();`
- L37 _private prototype_ `void ClearOutputPins();`
- L39 _private prototype_ `void RefreshOutputPins();`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_ComponentSource.h` (Private)


#### struct `FOptimusNode_ComponentSource_DuplicationInfo`  
`struct FOptimusNode_ComponentSource_DuplicationInfo`  
_L14-23_
- reflection: `USTRUCT()`
- L19 _public member_ `FName BindingName;` — `UPROPERTY()`
- L22 _public member_ `TSubclassOf<UOptimusComponentSource> ComponentType;` — `UPROPERTY()`

#### class `UOptimusNode_ComponentSource`  
`class UOptimusNode_ComponentSource : public UOptimusNode, public IOptimusComponentBindingProvider, public IOptimusNonCollapsibleNode`  
_L26-70_
- reflection: `UCLASS(Hidden)`
- inherits: `UOptimusNode,IOptimusComponentBindingProvider,IOptimusNonCollapsibleNode`
- L33 _public prototype_ `void SetComponentSourceBinding( UOptimusComponentSourceBinding* InBinding );`
- L38 _public prototype_ `FName GetNodeCategory() const override;` — UOptimusNode overrides
- L41 _public function_ `UOptimusComponentSourceBinding* GetComponentBinding(const FOptimusPinTraversalContext& InContext = {}) const override` — IOptimusComponentSourceBindingProvider implementation
- L50 _protected prototype_ `void ConstructNode() override;` — UOptimusNode overrides
- L51 _protected prototype_ `void PreDuplicateRequirementActions(const UOptimusNodeGraph* InTargetGraph, FOptimusCompoundAction* InCompoundAction) override;`
- L56 _protected prototype_ `UOptimusNodePin* GetComponentPin() const;` — Accessor to allow the UOptimusDeformer class to hook up data interface nodes to binding nodes automatically for backcomp.
- L59 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;` — UObject overrides
- L60 _protected prototype_ `void ExportCustomProperties(FOutputDevice& Out, uint32 Indent) override;`
- L61 _protected prototype_ `void ImportCustomProperties(const TCHAR* SourceText, FFeedbackContext* Warn) override;`
- L65 _private member_ `TObjectPtr<UOptimusComponentSourceBinding> Binding;` — `UPROPERTY()`
- L69 _private member_ `FOptimusNode_ComponentSource_DuplicationInfo DuplicationInfo;` — `UPROPERTY(DuplicateTransient)` — Duplication data across graphs/assets

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_ComputeKernelBase.h` (Private)


#### class `UOptimusNode_ComputeKernelBase`  
`class UOptimusNode_ComputeKernelBase : public UOptimusNode, public IOptimusComputeKernelProvider`  
_L19-136_
- reflection: `UCLASS(Abstract)`
- inherits: `UOptimusNode,IOptimusComputeKernelProvider`
- L27 _public function_ `virtual FString GetKernelHlslName() const PURE_VIRTUAL(UOptimusNode_ComputeKernelBase::GetKernelHlslName, return FString();) virtual FIntVector GetGroupSize() const PURE_VIRTUAL(UOptimusNode_ComputeKernelBase::GetGroupSize, return FIntVector();) virtual FString GetKernelSourceText(bool bInIsUnifiedDispatch) const PURE_VIRTUAL(UOptimusNode_ComputeKernelBase::GetKernelSourceText, return FString();) virtual TArray<TObjectPtr<UComputeSource>> GetAdditionalSources() const` — Implement this to return the HLSL kernel's function name
- L40 _public prototype_ `FOptimus_ComputeKernelResult CreateComputeKernel( UObject* InKernelSourceOuter, const FOptimusPinTraversalContext& InTraversalContext, const FOptimus_KernelInputMap& InKernelInputs, const FOptimus_KernelOutputMap& InKernelOutputs, UComputeDataInterface* InOutKernelDataInterface, FOptimus_InterfaceBindingMap& OutInputDataBindings, FOptimus_InterfaceBindingMap& OutOutputDataBindings ) const override;` — IOptimusComputeKernelProvider
- L51 _public prototype_ `FOptimusExecutionDomain GetExecutionDomain() const override PURE_VIRTUAL(UOptimusNode_ComputeKernelBase::GetExecutionDomain, return {}; );`
- L52 _public prototype_ `const UOptimusNodePin* GetPrimaryGroupPin() const override PURE_VIRTUAL(UOptimusNode_ComputeKernelBase::GetPrimaryGroupPin, return {}; );`
- L53 _public prototype_ `UComputeDataInterface* MakeKernelDataInterface(UObject* InOuter) const override PURE_VIRTUAL(UOptimusNode_ComputeKernelBase::MakeKernelDataInterface, return {}; );`
- L54 _public prototype_ `bool DoesOutputPinSupportAtomic(const UOptimusNodePin* InPin) const override PURE_VIRTUAL(UOptimusNode_ComputeKernelBase::DoesOutputPinSupportAtomic, return false; );`
- L55 _public prototype_ `bool DoesOutputPinSupportRead(const UOptimusNodePin* InPin) const override PURE_VIRTUAL(UOptimusNode_ComputeKernelBase::DoesOutputPinSupportRead, return false; );`
- L58 _public prototype_ `TOptional<FText> ValidateForCompile(const FOptimusPinTraversalContext& InContext) const override;` — -- UOptimusNode overrides
- L61 _protected function_ `static TArray<FString> GetIndexNamesFromDataDomainLevels( const TArray<FName> &InLevelNames )`
- L74 _protected function_ `static TArray<FString> GetIndexNamesFromDataDomain( const FOptimusDataDomain &InDomain )`
- L97 _protected prototype_ `static FString GetAtomicWriteFunctionName(EOptimusBufferWriteType InWriteType, const FString& InBindingName);`
- L98 _protected prototype_ `static FString GetReadFunctionName(const FString& InBindingName);`
- L99 _protected prototype_ `static const TCHAR* GetNumThreadsReservedName();`
- L103 _private prototype_ `TOptional<FText> BindKernelDataInterfaceForComputeKernel( const UOptimusComponentSourceBinding* InKernelPrimaryComponentSourceBinding, UComputeDataInterface* InOutKernelDataInterface, UOptimusKernelSource* InKernelSource, FOptimus_InterfaceBindingMap& OutInputDataBindings, TArray<FString>& OutGeneratedFunctions, bool& bOutUnifiedDispatchOnly ) const;`
- L112 _private prototype_ `TOptional<FText> ProcessInputPinForComputeKernel( bool bSupportUnifiedDispatchOnly, const FOptimusPinTraversalContext& InTraversalContext, const UOptimusNodePin* InInputPin, const FString& InGroupName, const FOptimus_KernelInputMap& InKernelInputs, UOptimusKernelSource* InKernelSource, TArray<FString>& OutGeneratedFunctions, FOptimus_InterfaceBindingMap& OutInputDataBindings, bool& bOutIsUnifiedDispatch ) const;`
- L124 _private prototype_ `TOptional<FText> ProcessOutputPinForComputeKernel( bool bSupportUnifiedDispatchOnly, const FOptimusPinTraversalContext& InTraversalContext, const UOptimusNodePin* InOutputPin, const FOptimus_KernelOutputMap& InKernelOutputs, UOptimusKernelSource* InKernelSource, TArray<FString>& OutGeneratedFunctions, FOptimus_InterfaceBindingMap& OutInputDataBindings, FOptimus_InterfaceBindingMap& OutOutputDataBindings, bool& bOutIsUnifiedDispatch ) const;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_ComputeKernelFunction.h` (Private)


#### class `UOptimusNode_ComputeKernelFunctionGeneratorClass`  
`class UOptimusNode_ComputeKernelFunctionGeneratorClass : public UClass`  
_L15-54_
- reflection: `UCLASS()`
- inherits: `UClass`
- L20 _public prototype_ `static UClass *CreateNodeClass( UObject* InPackage, FName InCategory, FName InKernelName, FIntVector InGroupSize, const TArray<FOptimusParameterBinding>& InInputBindings, const TArray<FOptimusParameterBinding>& InOutputBindings, const FString& InShaderSource );`
- L31 _public prototype_ `void InitPropertiesFromCustomList(uint8* InObjectPtr, const uint8* InCDOPtr) override;` — UClass overrides
- L32 _public prototype_ `void Link(FArchive& Ar, bool bRelinkExistingProperties) override;`
- L35 _public member_ `FName Category;` — `UPROPERTY()`
- L38 _public member_ `FName KernelName;` — `UPROPERTY()`
- L41 _public member_ `FOptimusExecutionDomain ExecutionDomain;` — `UPROPERTY()`
- L44 _public member_ `FIntVector GroupSize;` — `UPROPERTY()`
- L47 _public member_ `TArray<FOptimusParameterBinding> InputBindings;` — `UPROPERTY()`
- L50 _public member_ `TArray<FOptimusParameterBinding> OutputBindings;` — `UPROPERTY()`
- L53 _public member_ `FString ShaderSource;` — `UPROPERTY()`

#### class `UOptimusNode_ComputeKernelFunction`  
`class UOptimusNode_ComputeKernelFunction : public UOptimusNode_ComputeKernelBase`  
_L61-88_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UOptimusNode_ComputeKernelBase`
- L67 _public prototype_ `UOptimusNode_ComputeKernelFunction();`
- L70 _public prototype_ `FText GetDisplayName() const override;` — UOptimusNode overrides
- L71 _public prototype_ `FName GetNodeCategory() const override;`
- L74 _public prototype_ `FString GetKernelHlslName() const override;` — UOptimusNode_ComputeKernelBase overrides
- L75 _public prototype_ `FIntVector GetGroupSize() const override;`
- L76 _public prototype_ `FString GetKernelSourceText(bool bInIsUnifiedDispatch) const override;`
- L78 _public prototype_ `void ConstructNode() override;`
- L81 _public prototype_ `FOptimusExecutionDomain GetExecutionDomain() const override;` — IOptimusComputeKernelProvider
- L82 _public function_ `const UOptimusNodePin* GetPrimaryGroupPin() const override`
- L83 _public function_ `UComputeDataInterface* MakeKernelDataInterface(UObject* InOuter) const override`
- L84 _public function_ `bool DoesOutputPinSupportAtomic(const UOptimusNodePin* InPin) const override`
- L85 _public function_ `bool DoesOutputPinSupportRead(const UOptimusNodePin* InPin) const override`
- L87 _private prototype_ `UOptimusNode_ComputeKernelFunctionGeneratorClass *GetGeneratorClass() const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_ConstantValue.h` (Private)


#### class `UOptimusNode_ConstantValueGeneratorClass`  
`class UOptimusNode_ConstantValueGeneratorClass : public UClass`  
_L16-41_
- reflection: `UCLASS()`
- inherits: `UClass`
- L32 _public prototype_ `void Link(FArchive& Ar, bool bRelinkExistingProperties) override;` — UClass overrides
- L34 _public prototype_ `static UClass *GetClassForType( UPackage* InPackage, FOptimusDataTypeRef InDataType );`
- L40 _public member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY()`

#### class `UOptimusNode_ConstantValue`  
`class UOptimusNode_ConstantValue : public UOptimusNode, public IOptimusValueProvider, public IOptimusGeneratedClassDefiner, public IOptimusPinMutabilityDefiner`  
_L44-87_
- reflection: `UCLASS(Hidden)`
- inherits: `UOptimusNode,IOptimusValueProvider,IOptimusGeneratedClassDefiner,IOptimusPinMutabilityDefiner`
- L54 _public function_ `FName GetNodeCategory() const override`
- L60 _public prototype_ `void PostLoadNodeSpecificData() override;`
- L63 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L67 _public prototype_ `FOptimusValueIdentifier GetValueIdentifier() const override;` — IOptimusValueProvider overrides
- L68 _public prototype_ `FOptimusDataTypeRef GetValueDataType() const override;`
- L69 _public prototype_ `FOptimusValueContainerStruct GetValue() const override;`
- L72 _public prototype_ `FTopLevelAssetPath GetAssetPathForClassDefiner() const override;` — IOptimusGeneratedClassDefiner implementation
- L73 _public prototype_ `FString GetClassCreationString() const override;`
- L74 _public prototype_ `UClass* GetClassFromCreationString( UPackage* InPackage, const TCHAR* InCreationString ) const override;`
- L80 _public function_ `EOptimusPinMutability GetOutputPinMutability(const UOptimusNodePin* InPin) const override` — IOptimusPinMutabilityDefiner implementation
- L84 _protected prototype_ `void ConstructNode() override;`
- L86 _protected prototype_ `UOptimusNode_ConstantValueGeneratorClass* GetGeneratorClass() const;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_CustomComputeKernel.h` (Private)


#### struct `FOptimusSecondaryInputBindingsGroup`  
`struct FOptimusSecondaryInputBindingsGroup`  
_L22-31_
- reflection: `USTRUCT()`
- L27 _public member_ `FOptimusValidatedName GroupName;` — `UPROPERTY(EditAnywhere, Category=Group)`
- L30 _public member_ `FOptimusParameterBindingArray BindingArray;` — `UPROPERTY(EditAnywhere, Category=Group, DisplayName = "Bindings", meta=(AllowParameters))`

#### class `UOptimusNode_CustomComputeKernel`  
`class UOptimusNode_CustomComputeKernel : public UOptimusNode_ComputeKernelBase, public IOptimusShaderTextProvider, public IOptimusParameterBindingProvider, public IOptimusNodeAdderPinProvider, public IOptimusExecutionDomainProvider`  
_L35-210_
- reflection: `UCLASS()`
- inherits: `UOptimusNode_ComputeKernelBase,IOptimusShaderTextProvider,IOptimusParameterBindingProvider,IOptimusNodeAdderPinProvider,IOptimusExecutionDomainProvider`
- L45 _public prototype_ `UOptimusNode_CustomComputeKernel();`
- L48 _public function_ `FName GetNodeCategory() const override` — UOptimusNode overrides
- L53 _public prototype_ `void OnDataTypeChanged(FName InTypeName) override;`
- L54 _public prototype_ `void PostLoadNodeSpecificData() override;`
- L57 _public prototype_ `FString GetKernelHlslName() const override;` — UOptimusNode_ComputeKernelBase overrides
- L58 _public function_ `FIntVector GetGroupSize() const override`
- L59 _public prototype_ `FString GetKernelSourceText(bool bInIsUnifiedDispatch) const override;`
- L60 _public function_ `TArray<TObjectPtr<UComputeSource>> GetAdditionalSources() const override`
- L63 _public prototype_ `FOptimusExecutionDomain GetExecutionDomain() const override;` — IOptimusComputeKernelProvider
- L64 _public prototype_ `const UOptimusNodePin* GetPrimaryGroupPin() const override;`
- L65 _public prototype_ `UComputeDataInterface* MakeKernelDataInterface(UObject* InOuter) const override;`
- L66 _public prototype_ `bool DoesOutputPinSupportAtomic(const UOptimusNodePin* InPin) const override;`
- L67 _public prototype_ `bool DoesOutputPinSupportRead(const UOptimusNodePin* InPin) const override;`
- L71 _public prototype_ `FString GetNameForShaderTextEditor() const override;` — IOptimusShaderTextProvider overrides
- L72 _public prototype_ `FString GetDeclarations() const override;`
- L73 _public prototype_ `FString GetShaderText() const override;`
- L74 _public prototype_ `void SetShaderText(const FString& NewText) override;`
- L75 _public prototype_ `bool IsShaderTextReadOnly() const override;`
- L80 _public prototype_ `FString GetBindingDeclaration(FName BindingName) const override;` — IOptimusParameterBindingProvider
- L81 _public prototype_ `bool GetBindingSupportAtomicCheckBoxVisibility(FName BindingName) const override;`
- L82 _public prototype_ `bool GetBindingSupportReadCheckBoxVisibility(FName BindingName) const override;`
- L83 _public prototype_ `EOptimusDataTypeUsageFlags GetTypeUsageFlags(const FOptimusDataDomain& InDataDomain) const override;`
- L86 _public prototype_ `TArray<FAdderPinAction> GetAvailableAdderPinActions( const UOptimusNodePin* InSourcePin, EOptimusNodePinDirection InNewPinDirection, FString* OutReason = nullptr ) const override;` — IOptimusNodeAdderPinProvider
- L92 _public prototype_ `TArray<UOptimusNodePin*> TryAddPinFromPin( const FAdderPinAction& InSelectedAction, UOptimusNodePin* InSourcePin, FName InNameToUse ) override;`
- L98 _public prototype_ `bool RemoveAddedPins( TConstArrayView<UOptimusNodePin*> InAddedPinsToRemove ) override;`
- L105 _public prototype_ `TArray<FName> GetExecutionDomains() const override;` — IOptimusExecutionDomainProvider
- L110 _public member_ `FName Category = CategoryName::Deformers;` — `UPROPERTY(EditAnywhere, Category=Settings)` — FIXME: Use drop-down with a preset list + allow custom entry.
- L114 _public member_ `FOptimusValidatedName KernelName;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Name of kernel. This is also used as the entry point function name in generated code.
- L120 _public member_ `FOptimusExecutionDomain ExecutionDomain;` — `UPROPERTY(EditAnywhere, Category=Settings)` — The execution domain that this kernel operates on. The size of the domain is governed by the component binding that flows into the primary input group of this kernel.
- L128 _public member_ `FIntVector GroupSize = FIntVector(64, 1, 1);` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(Min=1))` — Number of threads in a thread group. Thread groups have 3 dimensions. It's better to have the total threads (X*Y*Z) be a value divisible by 32.
- L133 _public member_ `TArray<FOptimus_ShaderBinding> Parameters_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))` — Parameter bindings. Parameters are uniform values.
- L138 _public member_ `TArray<FOptimusParameterBinding> InputBindings_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))` — Input bindings. Each one is a function that should be connected to an implementation in a data interface.
- L142 _public member_ `TArray<FOptimusParameterBinding> OutputBindings_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))` — Output bindings. Each one is a function that should be connected to an implementation in a data interface.
- L146 _public member_ `FOptimusParameterBindingArray InputBindingArray;` — `UPROPERTY(EditAnywhere, Category = "Primary Bindings", DisplayName = "Input Bindings", meta=(AllowParameters))` — Input bindings. Each one is a function that should be connected to an implementation in a data interface.
- L150 _public member_ `FOptimusParameterBindingArray OutputBindingArray;` — `UPROPERTY(EditAnywhere, Category = "Primary Bindings", DisplayName = "Output Bindings")` — Output bindings. Each one is a function that should be connected to an implementation in a data interface.
- L154 _public member_ `TArray<FOptimusSecondaryInputBindingsGroup> SecondaryInputBindingGroups;` — `UPROPERTY(EditAnywhere, Category = "Secondary Input Bindings Groups", DisplayName = "Secondary Input Bindings")` — Secondary bindings.
- L158 _public member_ `TArray<TObjectPtr<UComputeSource>> AdditionalSources;` — `UPROPERTY(EditAnywhere, Category = Source)` — Additional source includes.
- L165 _public member_ `FOptimusShaderText ShaderSource;` — `UPROPERTY(EditAnywhere, Category = Source, meta = (DisplayName = "Kernel Source"))` — The kernel source code. If the code contains more than just the kernel entry function, then place the kernel entry function inside a KERNEL {} block.
- L168 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L171 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L175 _protected prototype_ `void ConstructNode() override;`
- L176 _protected prototype_ `bool ValidateConnection(const UOptimusNodePin& InThisNodesPin, const UOptimusNodePin& InOtherNodesPin, FString* OutReason) const override;`
- L177 _protected prototype_ `TOptional<FText> ValidateForCompile(const FOptimusPinTraversalContext& InContext) const override;`
- L182 _private prototype_ `void PropertyArrayPasted(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L183 _private prototype_ `void PropertyValueChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L184 _private prototype_ `void PropertyArrayItemAdded(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L185 _private prototype_ `void PropertyArrayItemRemoved(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L186 _private prototype_ `void PropertyArrayCleared(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L187 _private prototype_ `void PropertyArrayItemMoved(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L190 _private prototype_ `void UpdatePreamble();`
- L192 _private prototype_ `UOptimusNodePin* GetPrimaryGroupPin_Internal() const;`
- L193 _private prototype_ `void PostLoadExtractExecutionDomain();`
- L194 _private prototype_ `void PostLoadAddMissingPrimaryGroupPin();`
- L195 _private prototype_ `void PostLoadExtractAtomicModeFromConnectedResource();`
- L198 _private prototype_ `bool PostLoadRemoveDeprecatedNumThreadsPin();` — Called during UOptimusDeformer::PostLoad()
- L200 _private prototype_ `FName GetSanitizedNewPinName( UOptimusNodePin* InParentPin, FName InPinName );`
- L205 _private prototype_ `static FString GetDeclarationForBinding(const FOptimusParameterBinding& Binding, bool bIsInput);`
- L207 _private prototype_ `static bool DoesSourceSupportUnifiedDispatch(const UOptimusNodePin& InOtherNodesPin);`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_DataInterface.h` (Private)


#### class `UOptimusNode_DataInterface`  
`class UOptimusNode_DataInterface : public UOptimusNode, public IOptimusDataInterfaceProvider, public IOptimusComponentBindingProvider, public IOptimusPinMutabilityDefiner, public IOptimusPropertyPinProvider`  
_L21-110_
- reflection: `UCLASS(Hidden)`
- inherits: `UOptimusNode,IOptimusDataInterfaceProvider,IOptimusComponentBindingProvider,IOptimusPinMutabilityDefiner,IOptimusPropertyPinProvider`
- L31 _public prototype_ `UOptimusNode_DataInterface();`
- L33 _public prototype_ `virtual void SetDataInterfaceClass(TSubclassOf<UOptimusComputeDataInterface> InDataInterfaceClass);`
- L34 _public prototype_ `bool IsComponentSourceCompatible(const UOptimusComponentSource* InComponentSource) const;`
- L37 _public function_ `FName GetNodeCategory() const override` — -- UOptimusNode overrides
- L41 _public prototype_ `void InitializeTransientData() override;`
- L42 _public prototype_ `void RecreatePinsFromPinDefinitions() override;`
- L43 _public prototype_ `void RenamePinFromPinDefinition(FName InOld, FName InNew) override;`
- L44 _public prototype_ `void UpdateDisplayNameFromDataInterface() override;`
- L47 _public prototype_ `void Serialize(FArchive& Ar) override;` — -- UObject overrides
- L50 _public prototype_ `UOptimusComputeDataInterface *GetDataInterface(UObject *InOuter) const override;` — -- IOptimusDataInterfaceProvider implementations
- L51 _public prototype_ `int32 GetDataFunctionIndexFromPin(const UOptimusNodePin* InPin) const override;`
- L54 _public prototype_ `UOptimusComponentSourceBinding* GetComponentBinding(const FOptimusPinTraversalContext& InContext) const override;` — -- IOptimusDataInterfaceProvider & IOptimusComponentBindingProvider
- L57 _public prototype_ `EOptimusPinMutability GetOutputPinMutability(const UOptimusNodePin* InPin) const override;` — -- IOptimusPinMutabilityDefiner
- L60 _public prototype_ `TArray<UOptimusNodePin*> GetPropertyPins() const override;` — -- IOptimusPropertyPinProvider
- L63 _protected prototype_ `void ConstructNode() override;` — -- UOptimusNode overrides
- L64 _protected prototype_ `FText GetDisplayName() const override;`
- L65 _protected prototype_ `bool ValidateConnection(const UOptimusNodePin& InThisNodesPin, const UOptimusNodePin& InOtherNodesPin, FString* OutReason) const override;`
- L66 _protected prototype_ `TOptional<FText> ValidateForCompile(const FOptimusPinTraversalContext& InContext) const override;`
- L67 _protected prototype_ `void PostLoadNodeSpecificData() override;`
- L68 _protected prototype_ `void OnDataTypeChanged(FName InTypeName) override;`
- L69 _protected prototype_ `FText GetTooltipText() const override;`
- L71 _protected prototype_ `void ExportState(FArchive& Ar) const override;`
- L72 _protected prototype_ `void ImportState(FArchive& Ar) override;`
- L75 _protected prototype_ `void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;` — -- UObject overrides
- L78 _private prototype_ `void CreateShaderPinsFromDataInterface(const UOptimusComputeDataInterface *InDataInterface, bool bSupportUndo);`
- L79 _private prototype_ `void CreatePinFromDefinition( const FOptimusCDIPinDefinition &InDefinition, const TMap<FString, const FShaderFunctionDefinition *>& InReadFunctionMap, const TMap<FString, const FShaderFunctionDefinition *>& InWriteFunctionMap, bool bSupportUndo );`
- L86 _private prototype_ `void CreatePropertyPinsFromDataInterface(const UOptimusComputeDataInterface *InDataInterface, bool bSupportUndo);`
- L87 _private prototype_ `void CreateComponentPin();`
- L90 _private prototype_ `virtual void InitializePinsDisplayName() override;` — Allows the node to initialize all the pins display names from the definitions
- L99 _protected prototype_ `UOptimusNodePin* GetComponentPin() const;` — Accessor for the deformer object to connect this node automatically on backcomp and to unlink it as well if a component binding changes the source type.
- L105 _protected member_ `TObjectPtr<UClass> DataInterfaceClass;` — `UPROPERTY()` — The class of the data interface that this node represents. We call the CDO to interrogate display names and pin definitions. This may change in the future once data interfaces get tied closer to the objects they proxy.
- L109 _protected member_ `TObjectPtr<UOptimusComputeDataInterface> DataInterfaceData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category=DataInterface)` — Editable copy of the DataInterface for storing properties that will customize behavior on on the data interface.

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_FunctionReference.h` (Private)


#### class `UOptimusNode_FunctionReference`  
`class UOptimusNode_FunctionReference : public UOptimusNode, public IOptimusNodePinRouter, public IOptimusNodeGraphProvider, public IOptimusNodeSubGraphReferencer`  
_L16-67_
- reflection: `UCLASS(Hidden)`
- inherits: `UOptimusNode,IOptimusNodePinRouter,IOptimusNodeGraphProvider,IOptimusNodeSubGraphReferencer`
- L26 _public prototype_ `FName GetNodeCategory() const override;` — UOptimusNode overrides
- L27 _public prototype_ `FText GetDisplayName() const override;`
- L28 _public prototype_ `void ConstructNode() override;`
- L31 _public prototype_ `FOptimusRoutedNodePin GetPinCounterpart( UOptimusNodePin* InNodePin, const FOptimusPinTraversalContext& InTraversalContext ) const override;` — IOptimusNodePinRouter implementation
- L37 _public prototype_ `UOptimusNodeGraph* GetNodeGraphToShow() override;` — IOptimusNodeGraphProvider
- L40 _public prototype_ `UOptimusNodeSubGraph* GetReferencedSubGraph() const override;` — IOptimusNodeSubGraphReferencer
- L41 _public prototype_ `UOptimusComponentSourceBinding* GetDefaultComponentBinding(const FOptimusPinTraversalContext& InTraversalContext) const override;`
- L42 _public prototype_ `UOptimusNodePin* GetDefaultComponentBindingPin() const override;`
- L44 _public prototype_ `void SetReferencedFunctionGraph(const FOptimusFunctionGraphIdentifier& InGraphIdentifier);`
- L45 _public prototype_ `const FOptimusFunctionGraphIdentifier& GetReferencedFunctionGraphIdentifier();`
- L46 _public prototype_ `void UpdateDisplayName();`
- L49 _protected prototype_ `void PostLoadNodeSpecificData() override;`
- L50 _protected prototype_ `void InitializeTransientData() override;`
- L53 _protected member_ `FOptimusFunctionGraphIdentifier FunctionGraphIdentifier;` — `UPROPERTY()`
- L56 _protected member_ `TWeakObjectPtr<UOptimusNodePin> DefaultComponentPin;` — `UPROPERTY()`
- L59 _protected member_ `TWeakObjectPtr<UOptimusFunctionNodeGraph> ResolvedFunctionGraph;` — `UPROPERTY(Transient, VisibleAnywhere, Category=FunctionReference, DisplayName = "Referenced Function Graph")`
- L64 _private member_ `TSoftObjectPtr<UOptimusFunctionNodeGraph> FunctionGraph_DEPRECATED;` — `UE_DEPRECATED(5.6, "Use FunctionGraphIdentifier instead.")` — `UPROPERTY(Meta = (DeprecatedProperty))`
- L66 _private member_ `bool bDelayResolvingGraph = false;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_GetResource.h` (Private)


#### class `UOptimusNode_GetResource`  
`class UOptimusNode_GetResource : public UOptimusNode_ResourceAccessorBase`  
_L14-24_
- reflection: `UCLASS(Hidden)`
- inherits: `UOptimusNode_ResourceAccessorBase`
- L20 _private prototype_ `int32 GetDataFunctionIndexFromPin(const UOptimusNodePin* InPin) const override;` — IOptimusDataInterfaceProvider implementations
- L23 _protected prototype_ `void ConstructNode() override;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_GetVariable.h` (Private)


#### struct `FOptimusNode_GetVariable_DuplicationInfo`  
`struct FOptimusNode_GetVariable_DuplicationInfo`  
_L19-31_
- reflection: `USTRUCT()`
- desc: Information to hold data on the variable definition that persists over node duplication. FIXME: This could be generalized in a better fashion.
- L24 _public member_ `FName VariableName;` — `UPROPERTY()`
- L27 _public member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY()`
- L30 _public member_ `FString DefaultValue;` — `UPROPERTY()`

#### class `UOptimusNode_GetVariable`  
`class UOptimusNode_GetVariable : public UOptimusNode, public IOptimusValueProvider, public IOptimusPinMutabilityDefiner, public IOptimusNonCollapsibleNode`  
_L35-81_
- reflection: `UCLASS(Hidden)`
- inherits: `UOptimusNode,IOptimusValueProvider,IOptimusPinMutabilityDefiner,IOptimusNonCollapsibleNode`
- L44 _public prototype_ `void SetVariableDescription(UOptimusVariableDescription* InVariableDesc);`
- L46 _public prototype_ `UOptimusVariableDescription* GetVariableDescription() const;`
- L49 _public function_ `FName GetNodeCategory() const override` — UOptimusNode overrides
- L54 _public prototype_ `TOptional<FText> ValidateForCompile(const FOptimusPinTraversalContext& InContext) const override;`
- L57 _public prototype_ `FOptimusValueIdentifier GetValueIdentifier() const override;` — IOptimusValueProvider overrides
- L58 _public prototype_ `FOptimusDataTypeRef GetValueDataType() const override;`
- L59 _public prototype_ `FOptimusValueContainerStruct GetValue() const override;`
- L62 _public function_ `EOptimusPinMutability GetOutputPinMutability(const UOptimusNodePin* InPin) const override` — IOptimusPinMutabilityDefiner overrides
- L65 _protected prototype_ `void ConstructNode() override;`
- L67 _protected prototype_ `void PreDuplicateRequirementActions(const UOptimusNodeGraph* InTargetGraph, FOptimusCompoundAction* InCompoundAction) override;`
- L70 _protected prototype_ `void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;` — UObject overrides
- L71 _protected prototype_ `void ExportCustomProperties(FOutputDevice& Out, uint32 Indent) override;`
- L72 _protected prototype_ `void ImportCustomProperties(const TCHAR* SourceText, FFeedbackContext* Warn) override;`
- L76 _private member_ `TWeakObjectPtr<UOptimusVariableDescription> VariableDesc;` — `UPROPERTY()`
- L80 _private member_ `FOptimusNode_GetVariable_DuplicationInfo DuplicationInfo;` — `UPROPERTY(DuplicateTransient)` — Duplication data across graphs

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_GraphTerminal.h` (Private)


#### enum `EOptimusTerminalType`  
`enum class EOptimusTerminalType`  
_L17-22_
- reflection: `UENUM()`
- L19 _public enumerator_ `Unknown`
- L20 _public enumerator_ `Entry`
- L21 _public enumerator_ `Return`

#### class `UOptimusNode_GraphTerminal`  
`class UOptimusNode_GraphTerminal : public UOptimusNode, public IOptimusNodePinRouter, public IOptimusAlternativeSelectedObjectProvider, public IOptimusNonCollapsibleNode, public IOptimusNonCopyableNode`  
_L26-88_
- reflection: `UCLASS(Hidden)`
- inherits: `UOptimusNode,IOptimusNodePinRouter,IOptimusAlternativeSelectedObjectProvider,IOptimusNonCollapsibleNode,IOptimusNonCopyableNode`
- L36 _public member_ `static FName EntryNodeName;`
- L37 _public member_ `static FName ReturnNodeName;`
- L38 _public prototype_ `UOptimusNode_GraphTerminal();`
- L41 _public function_ `bool CanUserDeleteNode() const override` — UOptimusNode overrides
- L42 _public function_ `FName GetNodeCategory() const override`
- L43 _public prototype_ `FText GetDisplayName() const override;`
- L44 _public prototype_ `void ConstructNode() override;`
- L47 _public prototype_ `void BeginDestroy() override;` — UObject overrides
- L50 _public prototype_ `FOptimusRoutedNodePin GetPinCounterpart( UOptimusNodePin* InNodePin, const FOptimusPinTraversalContext& InTraversalContext ) const override;` — IOptimusNodePinRouter implementation
- L56 _public prototype_ `UObject* GetObjectToShowWhenSelected() const override;` — IOptimusAlternativeSelectedObjectProvider
- L58 _public prototype_ `UOptimusComponentSourceBinding* GetDefaultComponentBinding(const FOptimusPinTraversalContext& InTraversalContext) const;`
- L64 _protected prototype_ `void InitializeTransientData() override;`
- L65 _protected prototype_ `void SubscribeToOwningGraph();`
- L67 _protected prototype_ `void UnsubscribeFromOwningGraph() const;`
- L68 _protected prototype_ `TArray<UOptimusNodePin*> GetBindingPins();`
- L70 _protected prototype_ `void AddPinForNewBinding(FName InBindingArrayPropertyName);`
- L71 _protected prototype_ `void RemoveStalePins(FName InBindingArrayPropertyName);`
- L72 _protected prototype_ `void OnBindingMoved(FName InBindingArrayPropertyName);`
- L73 _protected prototype_ `void RecreateBindingPins(FName InBindingArrayPropertyName);`
- L74 _protected prototype_ `void SyncPinsToBindings(FName InBindingArrayPropertyName);`
- L78 _protected member_ `EOptimusTerminalType TerminalType;` — `UPROPERTY()` — Indicates whether this is an entry or a return terminal node
- L82 _protected member_ `TWeakObjectPtr<UOptimusNodePin> DefaultComponentPin;` — `UPROPERTY()`
- L87 _protected member_ `TWeakObjectPtr<UOptimusNodeSubGraph> OwningGraph;` — The graph that owns us. This contains all the necessary pin information to add on the terminal node. Initialized during InitializeTransientData()

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_LoopTerminal.h` (Private)


#### struct `FOptimusPinPairInfo`  
`struct FOptimusPinPairInfo`  
_L21-37_
- reflection: `USTRUCT()`
- L27 _public member_ `TArray<FName> InputPinPath;` — `UPROPERTY()`
- L30 _public member_ `TArray<FName> OutputPinPath;` — `UPROPERTY()`
- L32 _public function_ `bool operator==(const FOptimusPinPairInfo& InOther) const`

#### struct `FOptimusLoopTerminalInfo`  
`struct FOptimusLoopTerminalInfo`  
_L40-49_
- reflection: `USTRUCT()`
- L45 _public member_ `int32 Count = 1;` — `UPROPERTY(EditAnywhere, Category="Loop Terminal")`
- L48 _public member_ `FOptimusParameterBindingArray Bindings;` — `UPROPERTY(EditAnywhere, Category="Loop Terminal", meta=(FullyExpand="true", NoResetToDefault))`

#### class `UOptimusNode_LoopTerminal`  
`class UOptimusNode_LoopTerminal : public UOptimusNode, public IOptimusNodeAdderPinProvider, public IOptimusUnnamedNodePinProvider, public IOptimusNodePairProvider, public IOptimusPinMutabilityDefiner, public IOptimusParameterBindingProvider`  
_L52-154_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UOptimusNode,IOptimusNodeAdderPinProvider,IOptimusUnnamedNodePinProvider,IOptimusNodePairProvider,IOptimusPinMutabilityDefiner,IOptimusParameterBindingProvider`
- L63 _public prototype_ `UOptimusNode_LoopTerminal();`
- L67 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject overrides
- L71 _public function_ `FName GetNodeCategory() const override` — UOptimusNode overrides
- L72 _public prototype_ `FText GetDisplayName() const override;`
- L73 _public prototype_ `void ConstructNode() override;`
- L74 _public prototype_ `bool ValidateConnection(const UOptimusNodePin& InThisNodesPin, const UOptimusNodePin& InOtherNodesPin, FString* OutReason) const override;`
- L77 _public prototype_ `TArray<FAdderPinAction> GetAvailableAdderPinActions(const UOptimusNodePin* InSourcePin, EOptimusNodePinDirection InNewPinDirection, FString* OutReason) const override;` — IOptimusNodeAdderPinProvider
- L78 _public prototype_ `TArray<UOptimusNodePin*> TryAddPinFromPin(const FAdderPinAction& InSelectedAction, UOptimusNodePin* InSourcePin, FName InNameToUse) override;`
- L79 _public prototype_ `bool RemoveAddedPins(TConstArrayView<UOptimusNodePin*> InAddedPinsToRemove) override;`
- L82 _public prototype_ `bool IsPinNameHidden(UOptimusNodePin* InPin) const override;` — IOptimusUnnamedNodePinProvider
- L83 _public prototype_ `FName GetNameForAdderPin(UOptimusNodePin* InPin) const override;`
- L86 _public prototype_ `EOptimusPinMutability GetOutputPinMutability(const UOptimusNodePin* InPin) const override;` — IOptimusPinMutabilityDefiner
- L89 _public prototype_ `void PairToCounterpartNode(const IOptimusNodePairProvider* NodePairProvider) override;` — IOptimusNodePairProvider
- L92 _public prototype_ `FString GetBindingDeclaration(FName BindingName) const;` — IOptimusParameterBindingProvider
- L93 _public prototype_ `bool GetBindingSupportAtomicCheckBoxVisibility(FName BindingName) const;`
- L94 _public prototype_ `bool GetBindingSupportReadCheckBoxVisibility(FName BindingName) const;`
- L95 _public prototype_ `EOptimusDataTypeUsageFlags GetTypeUsageFlags(const FOptimusDataDomain& InDataDomain) const;`
- L97 _public prototype_ `UOptimusNodePin* GetPinCounterpart(const UOptimusNodePin* InNodePin, EOptimusTerminalType InTerminalType, TOptional<EOptimusNodePinDirection> InDirection = {}) const;`
- L98 _public prototype_ `UOptimusNode_LoopTerminal* GetOtherTerminal() const;`
- L99 _public prototype_ `int32 GetLoopCount() const;`
- L100 _public prototype_ `EOptimusTerminalType GetTerminalType() const;`
- L102 _public prototype_ `static int32 GetDataFunctionIndexFromPin(const UOptimusNodePin* InPin);`
- L109 _protected member_ `EOptimusTerminalType TerminalType;` — `UPROPERTY(VisibleAnywhere, Category="Loop Terminal")` — Indicates whether this is an entry or a return terminal node
- L113 _protected member_ `FOptimusLoopTerminalInfo LoopInfo;` — `UPROPERTY(EditAnywhere, Category="Loop Terminal", DisplayName="Settings", meta=(FullyExpand="true", EditCondition="TerminalType==EOptimusTerminalType::Entry", EditConditionHides))`
- L116 _protected member_ `TObjectPtr<UOptimusNodePin> IndexPin;` — `UPROPERTY()`
- L119 _protected member_ `TObjectPtr<UOptimusNodePin> CountPin;` — `UPROPERTY()`
- L122 _protected member_ `TArray<FOptimusPinPairInfo> PinPairInfos;` — `UPROPERTY()`
- L126 _private prototype_ `void PropertyArrayPasted(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L127 _private prototype_ `void PropertyValueChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L128 _private prototype_ `void PropertyArrayItemAdded(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L129 _private prototype_ `void PropertyArrayItemRemoved(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L130 _private prototype_ `void PropertyArrayCleared(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L131 _private prototype_ `void PropertyArrayItemMoved(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L134 _private prototype_ `TArray<UOptimusNodePin*> AddPinPairs(const FOptimusParameterBinding& InBinding);`
- L135 _private prototype_ `TArray<UOptimusNodePin*> AddPinPairsDirect(const FOptimusParameterBinding& InBinding);`
- L136 _private prototype_ `TArray<UOptimusNodePin*> GetPairedPins(const FOptimusPinPairInfo& InPair) const;`
- L137 _private prototype_ `static int32 GetPairIndex(const UOptimusNodePin* Pin);`
- L138 _private prototype_ `void RemovePinPair(int32 InPairIndex);`
- L139 _private prototype_ `void RemovePinPairDirect(int32 InPairIndex);`
- L140 _private prototype_ `void ClearPinPairs();`
- L141 _private prototype_ `void MovePinPair();`
- L142 _private prototype_ `void UpdatePinPairs();`
- L143 _private prototype_ `FOptimusLoopTerminalInfo* GetLoopInfo();`
- L144 _private prototype_ `const FOptimusLoopTerminalInfo* GetLoopInfo() const;`
- L146 _private prototype_ `void SanitizeBinding(FOptimusParameterBinding& InOutBinding, FName InOldName);`
- L147 _private prototype_ `UOptimusNode_LoopTerminal* GetTerminalByType(EOptimusTerminalType InType);`
- L148 _private prototype_ `const UOptimusNode_LoopTerminal* GetTerminalByType(EOptimusTerminalType InType) const;`
- L150 _private prototype_ `FName GetSanitizedBindingName( FName InNewName, FName InOldName );`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_Resource.h` (Private)


#### class `UOptimusNode_Resource`  
`class UOptimusNode_Resource : public UOptimusNode_ResourceAccessorBase`  
_L11-23_
- reflection: `UCLASS(Hidden)`
- inherits: `UOptimusNode_ResourceAccessorBase`
- L17 _private prototype_ `FName GetResourcePinName(int32 InPinIndex, FName InNameOverride = NAME_None) const override;` — UOptimusNode_Resource implementations
- L19 _private prototype_ `int32 GetDataFunctionIndexFromPin(const UOptimusNodePin* InPin) const override;` — IOptimusDataInterfaceProvider implementations
- L22 _protected prototype_ `void ConstructNode() override;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_ResourceAccessorBase.h` (Private)


#### struct `FOptimusNode_ResourceAccessorBase_DuplicationInfo`  
`struct FOptimusNode_ResourceAccessorBase_DuplicationInfo`  
_L20-32_
- reflection: `USTRUCT()`
- L25 _public member_ `FName ResourceName;` — `UPROPERTY()`
- L28 _public member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY()`
- L31 _public member_ `FOptimusDataDomain DataDomain;` — `UPROPERTY()`

#### class `UOptimusNode_ResourceAccessorBase`  
`class UOptimusNode_ResourceAccessorBase : public UOptimusNode, public IOptimusDataInterfaceProvider, public IOptimusComponentBindingProvider, public IOptimusPinMutabilityDefiner, public IOptimusNonCollapsibleNode`  
_L36-92_
- reflection: `UCLASS(Abstract)`
- inherits: `UOptimusNode,IOptimusDataInterfaceProvider,IOptimusComponentBindingProvider,IOptimusPinMutabilityDefiner,IOptimusNonCollapsibleNode`
- L46 _public prototype_ `void SetResourceDescription(UOptimusResourceDescription* InResourceDesc);`
- L48 _public prototype_ `UOptimusResourceDescription* GetResourceDescription() const;`
- L51 _public prototype_ `virtual FName GetResourcePinName(int32 InPinIndex, FName InNameOverride = NAME_None) const;` — Returns name to use when creating each pin on the node.
- L54 _public function_ `FName GetNodeCategory() const override` — UOptimusNode overrides
- L59 _public prototype_ `TOptional<FText> ValidateForCompile(const FOptimusPinTraversalContext& InContext) const override;`
- L62 _public prototype_ `UOptimusComputeDataInterface* GetDataInterface(UObject *InOuter) const override;` — IOptimusDataInterfaceProvider implementations
- L63 _public function_ `int32 GetDataFunctionIndexFromPin(const UOptimusNodePin* InPin) const override`
- L65 _public prototype_ `UOptimusComponentSourceBinding* GetComponentBinding(const FOptimusPinTraversalContext& InContext) const override;` — Also IOptimusComponentBindingProvider implementation
- L68 _public function_ `EOptimusBufferWriteType GetDeprecatedBufferWriteType() const`
- L72 _public function_ `EOptimusPinMutability GetOutputPinMutability(const UOptimusNodePin* InPin) const override` — IOptimusPinMutabilityDefiner overrides
- L75 _protected prototype_ `void PreDuplicateRequirementActions(const UOptimusNodeGraph* InTargetGraph, FOptimusCompoundAction* InCompoundAction) override;`
- L78 _protected prototype_ `void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;` — UObject overrides
- L79 _protected prototype_ `void ExportCustomProperties(FOutputDevice& Out, uint32 Indent) override;`
- L80 _protected prototype_ `void ImportCustomProperties(const TCHAR* SourceText, FFeedbackContext* Warn) override;`
- L84 _protected member_ `TWeakObjectPtr<UOptimusResourceDescription> ResourceDesc;` — `UPROPERTY()`
- L88 _protected member_ `EOptimusBufferWriteType WriteType_DEPRECATED= EOptimusBufferWriteType::Write;` — `UPROPERTY(meta=(DeprecatedProperty))` — Logical operation when writing to the resource.
- L91 _protected member_ `FOptimusNode_ResourceAccessorBase_DuplicationInfo DuplicationInfo;` — `UPROPERTY(DuplicateTransient)`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_SetResource.h` (Private)


#### class `UOptimusNode_SetResource`  
`class UOptimusNode_SetResource : public UOptimusNode_ResourceAccessorBase`  
_L11-21_
- reflection: `UCLASS(Hidden)`
- inherits: `UOptimusNode_ResourceAccessorBase`
- L17 _private prototype_ `int32 GetDataFunctionIndexFromPin(const UOptimusNodePin* InPin) const override;` — IOptimusDataInterfaceProvider implementations
- L20 _protected prototype_ `void ConstructNode() override;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/Nodes/OptimusNode_SubGraphReference.h` (Private)


#### class `UOptimusNode_SubGraphReference`  
`class UOptimusNode_SubGraphReference : public UOptimusNode, public IOptimusNodePinRouter, public IOptimusNodeGraphProvider, public IOptimusNodeSubGraphReferencer`  
_L19-87_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UOptimusNode,IOptimusNodePinRouter,IOptimusNodeGraphProvider,IOptimusNodeSubGraphReferencer`
- L28 _public prototype_ `UOptimusNode_SubGraphReference();`
- L31 _public function_ `FName GetNodeCategory() const override` — UOptimusNode overrides
- L32 _public prototype_ `FText GetDisplayName() const override;`
- L33 _public prototype_ `void ConstructNode() override;`
- L36 _public prototype_ `void BeginDestroy() override;` — UObject overrides
- L39 _public prototype_ `FOptimusRoutedNodePin GetPinCounterpart( UOptimusNodePin* InNodePin, const FOptimusPinTraversalContext& InTraversalContext ) const override;` — IOptimusNodePinRouter implementation
- L45 _public prototype_ `UOptimusNodeGraph* GetNodeGraphToShow() override;` — IOptimusNodeGraphProvider
- L48 _public prototype_ `UOptimusNodeSubGraph* GetReferencedSubGraph() const override;` — IOptimusNodeSubGraphReferencer
- L49 _public prototype_ `UOptimusComponentSourceBinding* GetDefaultComponentBinding(const FOptimusPinTraversalContext& InTraversalContext) const override;`
- L50 _public prototype_ `UOptimusNodePin* GetDefaultComponentBindingPin() const override;`
- L53 _public prototype_ `void InitializeSerializedSubGraphName(FName InInitialSubGraphName);` — Only used during node creation, cannot be used to reference a different graph once node is constructed
- L54 _public prototype_ `void RefreshSerializedSubGraphName();`
- L55 _public prototype_ `FName GetSerializedSubGraphName() const;`
- L59 _protected prototype_ `void InitializeTransientData() override;` — UOptimusNode overrides
- L61 _protected prototype_ `void ResolveSubGraphPointerAndSubscribe();`
- L62 _protected prototype_ `void SubscribeToSubGraph();`
- L63 _protected prototype_ `void UnsubscribeFromSubGraph() const;`
- L65 _protected prototype_ `void AddPinForNewBinding(FName InBindingArrayPropertyName);`
- L66 _protected prototype_ `void RemoveStalePins(FName InBindingArrayPropertyName);`
- L67 _protected prototype_ `void OnBindingMoved(FName InBindingArrayPropertyName);`
- L68 _protected prototype_ `void RecreateBindingPins(FName InBindingArrayPropertyName);`
- L69 _protected prototype_ `void SyncPinsToBindings(FName InBindingArrayPropertyName);`
- L71 _protected prototype_ `TArray<UOptimusNodePin*> GetBindingPinsByDirection(EOptimusNodePinDirection InDirection);`
- L75 _protected member_ `FName SubGraphName;` — `UPROPERTY()`
- L78 _protected member_ `TWeakObjectPtr<UOptimusNodePin> DefaultComponentPin;` — `UPROPERTY()`
- L86 _private member_ `TWeakObjectPtr<UOptimusNodeSubGraph> SubGraph;` — The graph that owns us. This contains all the necessary pin information to add on the terminal node. Initialized when the node is loaded/created

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/OptimusComputeGraph.h` (Private)


#### class `UOptimusComputeGraph`  
`class UOptimusComputeGraph : public UComputeGraph`  
_L16-39_
- reflection: `UCLASS()`
- inherits: `UComputeGraph`
- L23 _public prototype_ `void Serialize(FArchive& Ar) override;` — UObject overrides
- L24 _public prototype_ `void PostLoad() override;`
- L27 _public prototype_ `void OnKernelCompilationComplete(int32 InKernelIndex, FComputeKernelCompileResults const& InCompileResults) override;` — UComputeGraph overrides
- L29 _public prototype_ `EMeshDeformerOutputBuffer GetOutputBuffers() const;`
- L33 _protected member_ `TArray<TSoftObjectPtr<const UOptimusNode>> KernelToNode;` — `UPROPERTY()` — Lookup into Graphs array from the UComputeGraph kernel index.
- L35 _protected prototype_ `UOptimusGraphDataInterface* GetGraphDataInterfaceForPostLoadFixUp();`
- L36 _protected prototype_ `bool HasHalfEdgeDataInterface() const;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/OptimusCoreModule.h` (Private)


#### class `FOptimusCoreModule`  
`class FOptimusCoreModule : public IOptimusCoreModule`  
_L9-20_
- inherits: `IOptimusCoreModule`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `bool RegisterDataInterfaceClass(TSubclassOf<UOptimusComputeDataInterface> InDataInterfaceClass) override;` — IOptimusCoreModule implementation

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOptimusCore, Log, All);`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOptimusCore, Log, All);`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/OptimusGeometryReadbackProcessor.h` (Private)


#### class `FOptimusGeometryReadbackProcessor`  
`class FOptimusGeometryReadbackProcessor`  
_L11-53_
- L35 _public prototype_ `static FOptimusGeometryReadbackProcessor& Get();`
- L36 _public prototype_ `void Add(TSharedPtr<FGeometryReadback>);`
- L37 _public prototype_ `void ProcessCompletedGeometryReadback_RenderThread();`
- L41 _private prototype_ `static void ProcessReadbackRequestingMeshDescription(const TSharedPtr<FGeometryReadback>& Readback, int32 NumVertices);`
- L42 _private prototype_ `static void ProcessReadbackRequestingVertexDataArray(const TSharedPtr<FGeometryReadback>& Readback, int32 NumVertices);`
- L45 _private member_ `TMpscQueue<TSharedPtr<FGeometryReadback>> GeometryReadbacks;` — All data provider shares the same processor singleton
- L46 _private member_ `FGraphEventRef LastReadbackProcessingTask_RenderThread;`
- L48 _private member_ `static constexpr int32 SizeOfVertPosition = FSkeletalMeshDeformerHelpers::PosBufferElementMultiplier * FSkeletalMeshDeformerHelpers::PosBufferBytesPerElement;` — float3, 3 * float, 12 Bytes per vert
- L49 _private member_ `static constexpr int32 SizeOfVertTangents = FSkeletalMeshDeformerHelpers::TangentBufferElementMultiplier * FSkeletalMeshDeformerHelpers::TangentBufferBytesPerElement;` — 2 * half4, which is 4 * 2 bytes, 16 bytes per vert
- L50 _private member_ `static constexpr int32 SizeOfVertColor = FSkeletalMeshDeformerHelpers::ColorBufferBytesPerElement;` — 1 * 4 * 8bit, 4 bytes per vert

#### struct `FOptimusGeometryReadbackProcessor::FBufferReadback`  
`struct FBufferReadback`  
_L15-20_
- L17 _public member_ `bool bShouldReadback = false;`
- L18 _public member_ `TArray<uint8> ReadbackData;`
- L19 _public member_ `FComputeDataProviderRenderProxy::FReadbackCallback OnReadbackCompleted_RenderThread;`

#### struct `FOptimusGeometryReadbackProcessor::FGeometryReadback`  
`struct FGeometryReadback`  
_L22-33_
- L24 _public member_ `uint64 FrameNumber = 0;`
- L25 _public member_ `TArray<TUniquePtr<FMeshDeformerGeometryReadbackRequest>> GeometryReadbackRequests;`
- L27 _public member_ `TWeakObjectPtr<USkeletalMesh> SkeletalMesh;`
- L28 _public member_ `int32 LodIndex = 0;`
- L30 _public member_ `FBufferReadback Position;`
- L31 _public member_ `FBufferReadback Tangent;`
- L32 _public member_ `FBufferReadback Color;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Private/OptimusSkinnedMeshTrackingExtension.h` (Private)


#### class `FOptimusSkinnedMeshTrackingExtension`  
`class FOptimusSkinnedMeshTrackingExtension : public ISceneExtension`  
_L19-73_
- inherits: `ISceneExtension`
- desc: Scene extension that tracks per-component deformer state on the render thread. Entries are created on demand when MarkDeformed is called and removed via PreSceneUpdate when primitives leave the scene.
- L36 _public prototype_ `virtual ISceneExtensionUpdater* CreateUpdater() override;`
- L43 _public prototype_ `static void MarkDeformed( FRDGBuilder& GraphBuilder, FSceneInterface* SceneInterface, FPrimitiveComponentId ComponentId, FSkeletalMeshObject* MeshObject, EMeshDeformerOutputBuffer OutputBuffers, FName ExecutionGroup );` — RT: Mark a component as deformed by Optimus. Adds a RDG pass to make sure the passthrough vertex factory bind to buffers allocated by Optimus. Also keeps track of the deformer geometry buffers that Optimus writes to during the dispatch of each execution group
- L60 _public prototype_ `static EMeshDeformerOutputBuffer GetReadableDeformedBuffers( FSceneInterface* SceneInterface, FPrimitiveComponentId ComponentId, FName ReaderExecutionGroup, bool bIsPrimaryComponent);` — RT: Returns which deformer output buffers are safe to read for a given component. For primary component reads (bIsPrimaryComponent=true), all recorded output buffers are returned since deformer instances on the same component are dispatched sequentially. For secondary component reads, only output buffers from execution groups that dispatched earlier than the reader's execution group are returned — same-group cross-component reads are excluded because their relative dispatch order is not guaranteed.
- L69 _private prototype_ `static FOptimusSkinnedMeshTrackingExtension* Get(FSceneInterface* SceneInterface);`
- L72 _private member_ `TMap<FPrimitiveComponentId, FComponentData> ComponentDataMap;` — Map of component ID → tracking data. Accessed only on RT.

#### struct `FOptimusSkinnedMeshTrackingExtension::FComponentData`  
`struct FComponentData`  
_L25-31_
- desc: Per-component tracking data. Packed to 2 DWords (8 bytes).
- L27 _public member_ `int8 LastLodIndex = INDEX_NONE;`
- L28 _public member_ `EMeshDeformerOutputBuffer EndOfFrameUpdateOutputBuffers = EMeshDeformerOutputBuffer::None;`
- L29 _public member_ `EMeshDeformerOutputBuffer BeginInitViewsOutputBuffers = EMeshDeformerOutputBuffer::None;`
- L30 _public member_ `uint32 DeformedFrame = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusAlternativeSelectedObjectProvider.h` (Public)


#### class `UOptimusAlternativeSelectedObjectProvider`  
`class UOptimusAlternativeSelectedObjectProvider : public UInterface`  
_L11-15_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusAlternativeSelectedObjectProvider`  
`class IOptimusAlternativeSelectedObjectProvider`  
_L18-24_
- L23 _public prototype_ `virtual UObject* GetObjectToShowWhenSelected() const = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusComponentBindingProvider.h` (Public)


#### class `UOptimusComponentBindingProvider`  
`class UOptimusComponentBindingProvider : public UInterface`  
_L17-21_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusComponentBindingProvider`  
`class IOptimusComponentBindingProvider`  
_L24-31_
- L30 _public prototype_ `virtual UOptimusComponentSourceBinding *GetComponentBinding(const FOptimusPinTraversalContext& InContext) const = 0;` — Returns the component binding for the node that this interface is implemented on

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusComponentBindingReceiver.h` (Public)


#### class `UOptimusComponentBindingReceiver`  
`class UOptimusComponentBindingReceiver : public UInterface`  
_L14-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusComponentBindingReceiver`  
`class IOptimusComponentBindingReceiver`  
_L21-28_
- L27 _public prototype_ `virtual TArray<UOptimusNodePin*> GetUnconnectedComponentPins() const = 0;` — Returns unconnected component binding pins that would be using the default binding implicitly

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusComputeKernelDataInterface.h` (Public)


#### class `UOptimusComputeKernelDataInterface`  
`class UOptimusComputeKernelDataInterface : public UInterface`  
_L12-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusComputeKernelDataInterface`  
`class IOptimusComputeKernelDataInterface`  
_L21-33_
- desc: Interface that provides a mechanism for compute kernel to setup its kernel data interface
- L26 _public prototype_ `virtual void SetExecutionDomain(const FString& InExecutionDomain) = 0;`
- L27 _public prototype_ `virtual void SetComponentBinding(const UOptimusComponentSourceBinding* InBinding) = 0;`
- L28 _public prototype_ `virtual const FString& GetExecutionDomain() const = 0;`
- L29 _public prototype_ `virtual const TCHAR* GetReadNumThreadsFunctionName() const = 0;`
- L30 _public prototype_ `virtual const TCHAR* GetReadNumThreadsPerInvocationFunctionName() const = 0;`
- L31 _public prototype_ `virtual const TCHAR* GetReadThreadIndexOffsetFunctionName() const = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusComputeKernelProvider.h` (Public)


#### struct `FOptimus_InterfaceBinding`  
`struct FOptimus_InterfaceBinding`  
_L25-31_
- desc: Maps the data interface's data binding index to the function we would like to have present during kernel compilation to read/write values from/to that data interface's resource.
- L27 _public member_ `const UComputeDataInterface* DataInterface;`
- L28 _public member_ `int32 DataInterfaceBindingIndex;`
- L29 _public member_ `FString BindingFunctionName;`
- L30 _public member_ `FString BindingFunctionNamespace;`

#### struct `FOptimus_KernelParameterBinding`  
`struct FOptimus_KernelParameterBinding`  
_L35-45_
- desc: A map that goes from a value/variable node to a compute shader input parameter.
- L38 _public member_ `const UOptimusNode* ValueNode;` — The node to retrieve the value from
- L41 _public member_ `FString ParameterName;` — The name of the shader parameter
- L44 _public member_ `FShaderValueTypeHandle ValueType;` — The value type of the parameter

#### struct `FOptimus_KernelConnection`  
`struct FOptimus_KernelConnection`  
_L50-54_
- L52 _public member_ `UComputeDataInterface* DataInterface;`
- L53 _public member_ `const UOptimusNodePin* ConnectedPin;`

#### class `UOptimusComputeKernelProvider`  
`class UOptimusComputeKernelProvider : public UInterface`  
_L60-64_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusComputeKernelProvider`  
`class IOptimusComputeKernelProvider`  
_L69-109_
- desc: Interface that provides a mechanism to identify and work with node graph owners.
- L84 _public prototype_ `virtual FOptimus_ComputeKernelResult CreateComputeKernel( UObject* InKernelSourceOuter, const FOptimusPinTraversalContext& InTraversalContext, const FOptimus_KernelInputMap& InKernelInputs, const FOptimus_KernelOutputMap& InKernelOutputs, UComputeDataInterface* InOutKernelDataInterface, FOptimus_InterfaceBindingMap& OutInputDataBindings, FOptimus_InterfaceBindingMap& OutOutputDataBindings ) const = 0;` — Return an UOptimusKernelSource object, from a compute kernel node state that implements this interface. @param InKernelSourceOuter The outer object that will own the new kernel source. @param InTraversalContext The current context being used to traverse from the graph. Used mainly to keep track of graph nesting. @param InOutKernelDataInterface @param OutInputDataBindings @param OutOutputDataBindings
- L96 _public prototype_ `virtual FOptimusExecutionDomain GetExecutionDomain() const = 0;` — Returns the execution domain that this kernel should iterate over
- L99 _public prototype_ `virtual const UOptimusNodePin* GetPrimaryGroupPin() const = 0;` — Used for traversing up the graph to identify the component source of the compute kernel
- L102 _public prototype_ `virtual UComputeDataInterface* MakeKernelDataInterface(UObject* InOuter) const = 0;` — Each kernel may have its own data interface responsible for passing kernel related data to GPU
- L105 _public prototype_ `virtual bool DoesOutputPinSupportAtomic(const UOptimusNodePin* InPin) const = 0;` — Check if a specific pin needs to support atomic operation
- L108 _public prototype_ `virtual bool DoesOutputPinSupportRead(const UOptimusNodePin* InPin) const = 0;` — Check if a specific pin needs to support atomic operation

#### Free symbols / members of external scopes

- L32 _typedef_ `using FOptimus_InterfaceBindingMap = TMap<int32 , FOptimus_InterfaceBinding>;`
- L46 _typedef_ `using FOptimus_KernelParameterBindingList = TArray<FOptimus_KernelParameterBinding>;`
- L48 _typedef_ `using FOptimus_ComputeKernelResult = TVariant<UOptimusKernelSource* , FText >;`
- L56 _typedef_ `using FOptimus_KernelInputMap = TMap<const UOptimusNodePin*, FOptimus_KernelConnection>;`
- L57 _typedef_ `using FOptimus_KernelOutputMap = TMap<const UOptimusNodePin*, TArray<FOptimus_KernelConnection>>;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusCoreModule.h` (Public)


#### class `IOptimusCoreModule`  
`class IOptimusCoreModule : public IModuleInterface`  
_L16-33_
- inherits: `IModuleInterface`
- L19 _public function_ `static IOptimusCoreModule& Get()`
- L26 _public function_ `template<typename T> bool RegisterDataInterfaceClass()` — Register a data interface after the OptimusCore module has loaded
- L32 _protected prototype_ `virtual bool RegisterDataInterfaceClass(TSubclassOf<UOptimusComputeDataInterface> InDataInterfaceClass) = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusDataInterfaceProvider.h` (Public)


#### class `UOptimusDataInterfaceProvider`  
`class UOptimusDataInterfaceProvider : public UInterface`  
_L16-20_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusDataInterfaceProvider`  
`class IOptimusDataInterfaceProvider`  
_L23-47_
- L32 _public prototype_ `virtual UOptimusComputeDataInterface* GetDataInterface(UObject *InOuter) const = 0;` — Returns the data interface class that should be generated from the node that implements this interface.
- L43 _public prototype_ `virtual int32 GetDataFunctionIndexFromPin(const UOptimusNodePin* InPin) const = 0;` — Returns the index on the data interface that this pin on the node represents. E.g. for input pins, this would represent a write function on the data interface (and _not_ the proposed pin definitions). NOTE: Only valid for top-level pins. @param InPin * The pin to get the data interface function index for. @return The index of the function on the data interface that this top-level pin represents, or INDEX_NONE if it doesn't represent a function (or if the pin isn't top-level).
- L46 _public prototype_ `virtual UOptimusComponentSourceBinding* GetComponentBinding(const FOptimusPinTraversalContext& InContext) const = 0;` — Returns the component binding that this data interface is bound to (or nullptr if unbound)

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusDeformerAssetPathAccessor.h` (Public)


#### class `UOptimusDeformerAssetPathAccessor`  
`class UOptimusDeformerAssetPathAccessor : public UInterface`  
_L14-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusDeformerAssetPathAccessor`  
`class IOptimusDeformerAssetPathAccessor`  
_L21-27_
- L26 _public prototype_ `virtual void SetOptimusDeformerAssetPath(const FTopLevelAssetPath& InPath) = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusDeformerGeometryReadbackProvider.h` (Public)


#### class `UOptimusDeformerGeometryReadbackProvider`  
`class UOptimusDeformerGeometryReadbackProvider : public UInterface`  
_L13-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusDeformerGeometryReadbackProvider`  
`class IOptimusDeformerGeometryReadbackProvider`  
_L20-28_
- L26 _public prototype_ `virtual bool RequestReadbackDeformerGeometry(TUniquePtr<FMeshDeformerGeometryReadbackRequest> InRequest) = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusDeformerInstanceAccessor.h` (Public)


#### class `UOptimusDeformerInstanceAccessor`  
`class UOptimusDeformerInstanceAccessor : public UInterface`  
_L13-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusDeformerInstanceAccessor`  
`class IOptimusDeformerInstanceAccessor`  
_L20-26_
- L25 _public prototype_ `virtual void SetDeformerInstance(UOptimusDeformerInstance* InInstance) = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusDeprecatedExecutionDataInterface.h` (Public)


#### class `UOptimusDeprecatedExecutionDataInterface`  
`class UOptimusDeprecatedExecutionDataInterface: public UInterface`  
_L12-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusDeprecatedExecutionDataInterface`  
`class IOptimusDeprecatedExecutionDataInterface`  
_L22-28_
- desc: An interface that should be implemented by any legacy Data Interface Node whose data interface is an execution data interface. such that the serialized execution domain can be extracted and assigned to the kernel data interface
- L27 _public prototype_ `virtual FName GetSelectedExecutionDomainName() const = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusDeveloperModule.h` (Public)


#### class `IOptimusDeveloperModule`  
`class IOptimusDeveloperModule : public IModuleInterface`  
_L9-16_
- inherits: `IModuleInterface`
- L12 _public function_ `static IOptimusDeveloperModule& Get()`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusExecutionDomainProvider.h` (Public)


#### class `UOptimusExecutionDomainProvider`  
`class UOptimusExecutionDomainProvider : public UInterface`  
_L12-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusExecutionDomainProvider`  
`class IOptimusExecutionDomainProvider`  
_L22-31_
- desc: An interface that should be implemented by any class that has an FOptimusExecutionDomain member. This is used by the property detail specialization code to provide a list of possible domains.
- L30 _public prototype_ `virtual TArray<FName> GetExecutionDomains() const = 0;` — Returns a list of execution domains that the implementer of this interface provides.

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusGeneratedClassDefiner.h` (Public)


#### class `UOptimusGeneratedClassDefiner`  
`class UOptimusGeneratedClassDefiner : public UInterface`  
_L11-15_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusGeneratedClassDefiner`  
`class IOptimusGeneratedClassDefiner`  
_L21-40_
- desc: FIXME: A stop-gap shader value provider until we have a proper pin evaluation that handles paths that have a constant, computed, varying and a mix thereof, results.
- L28 _public prototype_ `virtual FTopLevelAssetPath GetAssetPathForClassDefiner() const = 0;` — Returns the class whose CDO we can get to get this interface to create a new generated class from a string definition.
- L32 _public prototype_ `virtual FString GetClassCreationString() const = 0;` — Export definition values for the given class which are sufficient to pass into a call to CreateClassFromCreationString to generate a class based on the class that hosts this interface.
- L36 _public prototype_ `virtual UClass* GetClassFromCreationString( UPackage* InPackage, const TCHAR* InCreationString ) const = 0;` — Create a generated class, within the package provided, from the creation string that was originally generated by GetClassCreationString.

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusNodeAdderPinProvider.h` (Public)


#### class `UOptimusNodeAdderPinProvider`  
`class UOptimusNodeAdderPinProvider : public UInterface`  
_L11-15_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusNodeAdderPinProvider`  
`class IOptimusNodeAdderPinProvider`  
_L20-49_
- desc: Interface that provides a mechanism to add pins to node from existing pins
- L34 _public prototype_ `virtual TArray<FAdderPinAction> GetAvailableAdderPinActions( const UOptimusNodePin* InSourcePin, EOptimusNodePinDirection InNewPinDirection, FString* OutReason = nullptr ) const = 0;`
- L42 _public prototype_ `virtual TArray<UOptimusNodePin*> TryAddPinFromPin( const FAdderPinAction& InSelectedAction, UOptimusNodePin* InSourcePin, FName InNameToUse ) = 0;` — Make sure pins created this way don't have different names each time the function is called. Because this function is called during undo/redo, output has to be stable(same input gives same output)
- L48 _public prototype_ `virtual bool RemoveAddedPins(TConstArrayView<UOptimusNodePin*> InAddedPinsToRemove) = 0;`

#### struct `IOptimusNodeAdderPinProvider::FAdderPinAction`  
`struct FAdderPinAction`  
_L25-32_
- L27 _public member_ `FName DisplayName;`
- L28 _public member_ `EOptimusNodePinDirection NewPinDirection;`
- L29 _public member_ `FName Key;`
- L30 _public member_ `FText ToolTip;`
- L31 _public member_ `bool bCanAutoLink = false;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusNodeFunctionLibraryOwner.h` (Public)


#### class `UOptimusNodeFunctionLibraryOwner`  
`class UOptimusNodeFunctionLibraryOwner : public UInterface`  
_L11-15_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusNodeFunctionLibraryOwner`  
`class IOptimusNodeFunctionLibraryOwner`  
_L20-26_
- desc: Interface that provides a mechanism to identify and work with node function library owners

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusNodeGraphCollectionOwner.h` (Public)


#### class `UOptimusNodeGraphCollectionOwner`  
`class UOptimusNodeGraphCollectionOwner : public UInterface`  
_L21-25_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusNodeGraphCollectionOwner`  
`class IOptimusNodeGraphCollectionOwner`  
_L30-117_
- desc: Interface that provides a mechanism to identify and work with node graph owners.
- L38 _public prototype_ `virtual IOptimusNodeGraphCollectionOwner* GetCollectionOwner() const = 0;` — Returns the collection that owns this collection, or nullptr if this is the root collection
- L42 _public prototype_ `virtual IOptimusNodeGraphCollectionOwner* GetCollectionRoot() const = 0;` — Returns root collection that owns all the collections
- L45 _public prototype_ `virtual FString GetCollectionPath() const = 0;` — Returns the path to this graph collection owner.
- L48 _public prototype_ `virtual const TArray<UOptimusNodeGraph*> &GetGraphs() const = 0;` — Returns all immediately owned node graphs.
- L50 _public prototype_ `virtual UOptimusNodeGraph* FindGraphByName(FName InGraphName) const = 0;`
- L63 _public prototype_ `virtual UOptimusNodeGraph* CreateGraphDirect( EOptimusNodeGraphType InType, FName InName = NAME_None, TOptional<int32> InInsertBefore = TOptional<int32>(INDEX_NONE) ) = 0;` — Create a new graph of a given type, with an optional name. The name may be changed to fit into the namespace. Only setup and trigger graphs can currently be created directly, and only a single setup graph. The setup graph is always the first, and the trigger graphs come after. @param InType The type of graph to create. @param InName  The name to give the graph. @param InInsertBefore The index at which the insert the graph at. This inserts the given graph before the graph already occupying this location. If unset, then the graph will not be inserted into the list of editable graphs, although it will be owned by this collection. @return The newly created graph.
- L75 _public prototype_ `virtual bool AddGraphDirect( UOptimusNodeGraph* InGraph, int32 InInsertBefore = INDEX_NONE ) = 0;` — @brief Takes an existing graph and adds it to this graph collection. If the graph cannot be added, the object remains unchanged and this function returns false. @param InGraph The graph to add. @param InInsertBefore The index at which the insert the graph at. This inserts the given graph before the graph already occupying this location. @return true if the graph was successfully added to the graph.
- L84 _public prototype_ `virtual bool RemoveGraphDirect( UOptimusNodeGraph* InGraph, bool bDeleteGraph = true ) = 0;` — Remove the given graph. @param InGraph The graph to remove, owned by this collection. The graph will be unowned by this graph collection and marked for GC. @return true if the graph was successfully removed.
- L96 _public prototype_ `virtual bool MoveGraphDirect( UOptimusNodeGraph* InGraph, int32 InInsertBefore) = 0;` — Re-order the graph relative to the other graphs. The insert location is relative to the graph list minus the graph being moved. \note Only trigger graphs can be moved around. @param InGraph The graph to move, owned by this collection. @param InInsertBefore The order at which the move the graph to. This inserts the given graph before the graph already occupying this location. @return true if the graph was successfully moved.
- L104 _public prototype_ `virtual bool RenameGraphDirect( UOptimusNodeGraph *InGraph, const FString &InNewName ) = 0;` — Rename the given graph, subject to validation of the name. @param InGraph The graph to rename, owned by this collection. @param InNewName The new name to give the graph. @return true if the graph was successfully renamed.
- L113 _public prototype_ `virtual bool RenameGraph( UOptimusNodeGraph *InGraph, const FString &InNewName ) = 0;` — Rename the given graph, subject to validation of the name. @param InGraph The graph to rename, owned by this collection. @param InNewName The new name to give the graph. @return true if the graph was successfully renamed.

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusNodeGraphProvider.h` (Public)


#### class `UOptimusNodeGraphProvider`  
`class UOptimusNodeGraphProvider : public UInterface`  
_L12-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusNodeGraphProvider`  
`class IOptimusNodeGraphProvider`  
_L21-27_
- desc: Interface that provides a mechanism to get a node graph to display
- L26 _public prototype_ `virtual UOptimusNodeGraph* GetNodeGraphToShow() = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusNodePairProvider.h` (Public)


#### class `UOptimusNodePairProvider`  
`class UOptimusNodePairProvider : public UInterface`  
_L10-14_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusNodePairProvider`  
`class IOptimusNodePairProvider`  
_L19-26_
- desc: Interface that provides a mechanism to add pins to node from existing pins
- L25 _public prototype_ `virtual void PairToCounterpartNode(const IOptimusNodePairProvider* NodePairProvider) = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusNodePinRouter.h` (Public)


#### struct `FOptimusPinTraversalContext`  
`struct FOptimusPinTraversalContext`  
_L20-39_
- desc: The context used for doing the pin traversal using the IOptimusNodePinRouter interface. This structure keeps track of where the traversal arrived from, so that we can exit at the same point. This is required because for functions, multiple reference nodes can refer to the same graph, including the same entry/return nodes.
- L22 _public member_ `TArray<const IOptimusNodePinRouter*, TInlineAllocator<4>> ReferenceNesting;`
- L24 _public function_ `bool operator==(FOptimusPinTraversalContext const& RHS) const`

#### struct `FOptimusRoutedNode`  
`struct FOptimusRoutedNode`  
_L42-59_
- desc: A utility struct for when traversing the graph through routed nodes.
- L44 _public member_ `UOptimusNode* Node = nullptr;`
- L45 _public member_ `FOptimusPinTraversalContext TraversalContext;`
- L47 _public function_ `bool operator==(FOptimusRoutedNode const& RHS) const`

#### struct `FOptimusRoutedConstNode`  
`struct FOptimusRoutedConstNode`  
_L61-78_
- L63 _public member_ `const UOptimusNode* Node = nullptr;`
- L64 _public member_ `FOptimusPinTraversalContext TraversalContext;`
- L66 _public function_ `bool operator==(FOptimusRoutedConstNode const& RHS) const`

#### struct `FOptimusRoutedNodePin`  
`struct FOptimusRoutedNodePin`  
_L86-103_
- desc: A utility structure to store information on routed pins when getting routed connections. The traversal context can be subsequently passed into the GetConnectedPinsWithRouting for the pin given in the struct to ensure that the traversal behaves correctly when going through library functions.
- L88 _public member_ `UOptimusNodePin* NodePin = nullptr;`
- L89 _public member_ `FOptimusPinTraversalContext TraversalContext;`
- L91 _public function_ `bool operator==(FOptimusRoutedNodePin const& RHS) const`

#### struct `FOptimusRoutedConstNodePin`  
`struct FOptimusRoutedConstNodePin`  
_L105-122_
- L107 _public member_ `const UOptimusNodePin* NodePin = nullptr;`
- L108 _public member_ `FOptimusPinTraversalContext TraversalContext;`
- L110 _public function_ `bool operator==(FOptimusRoutedConstNodePin const& RHS) const`

#### class `UOptimusNodePinRouter`  
`class UOptimusNodePinRouter : public UInterface`  
_L126-130_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusNodePinRouter`  
`class IOptimusNodePinRouter`  
_L133-155_
- L151 _public prototype_ `virtual FOptimusRoutedNodePin GetPinCounterpart( UOptimusNodePin* InNodePin, const FOptimusPinTraversalContext& InTraversalContext ) const = 0;` — Given a pin on this node, which can be a terminal node (entry/return), or a subgraph/ function reference node, return the pin matching it on the other side. E.g. if given an input pin on a terminal return node, return the output pin on the reference node in the graph above. If the pin isn't owned by this node, then a nullptr is returned. @param InNodePin The pin to find the counterpart for. @param InTraversalContext The context for the routing. This is used by the router to where it is in the traversal when traversing function references, to understand which node is the exit node. If a pin from a reference node is used to enter the function sub-graph the sub-graph reference router node is added to the context. If the pin is used to leave the sub-graph to go up, the last node in the array is used as the exit node. @return The counterpart pin. If the pin given was invalid and has no counterpart, the NodePin value will be a nullptr and the traversal context undefined.

#### Free symbols / members of external scopes

- L29 _function_ `friend uint32 GetTypeHash(const FOptimusPinTraversalContext& InContext)`
- L52 _function_ `friend uint32 GetTypeHash(const FOptimusRoutedNode& InRoutedNode)`
- L71 _function_ `friend uint32 GetTypeHash(const FOptimusRoutedConstNode& InRoutedNode)`
- L96 _function_ `friend uint32 GetTypeHash(const FOptimusRoutedNodePin& InRoutedNodePin)`
- L115 _function_ `friend uint32 GetTypeHash(const FOptimusRoutedConstNodePin& InRoutedNodePin)`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusNodeSubGraphReferencer.h` (Public)


#### class `UOptimusNodeSubGraphReferencer`  
`class UOptimusNodeSubGraphReferencer : public UInterface`  
_L16-20_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusNodeSubGraphReferencer`  
`class IOptimusNodeSubGraphReferencer`  
_L25-33_
- desc: Interface that provides a mechanism to get a node graph to display
- L30 _public prototype_ `virtual UOptimusNodeSubGraph* GetReferencedSubGraph() const = 0;`
- L31 _public prototype_ `virtual UOptimusComponentSourceBinding* GetDefaultComponentBinding(const FOptimusPinTraversalContext& InTraversalContext) const = 0;`
- L32 _public prototype_ `virtual UOptimusNodePin* GetDefaultComponentBindingPin() const = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusNonCollapsibleNode.h` (Public)


#### class `UOptimusNonCollapsibleNode`  
`class UOptimusNonCollapsibleNode : public UInterface`  
_L10-14_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusNonCollapsibleNode`  
`class IOptimusNonCollapsibleNode`  
_L19-23_
- desc: Interface that provides a mechanism to prevent node from being included in a subgraph

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusNonCopyableNode.h` (Public)


#### class `UOptimusNonCopyableNode`  
`class UOptimusNonCopyableNode : public UInterface`  
_L10-14_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusNonCopyableNode`  
`class IOptimusNonCopyableNode`  
_L19-23_
- desc: Interface that provides a mechanism to prevent node from being included in a subgraph

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusOutputBufferWriter.h` (Public)


#### class `UOptimusOutputBufferWriter`  
`class UOptimusOutputBufferWriter : public UInterface`  
_L13-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusOutputBufferWriter`  
`class IOptimusOutputBufferWriter`  
_L22-31_
- desc: An interface that should be implemented by data interfaces that overrides some engine internal buffers
- L30 _public prototype_ `virtual EMeshDeformerOutputBuffer GetOutputBuffer(int32 InBoundOutputFunctionIndex) const = 0;` — Returns the output buffer that it writes to for the given data interface output function index

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusParameterBindingProvider.h` (Public)


#### class `UOptimusParameterBindingProvider`  
`class UOptimusParameterBindingProvider : public UInterface`  
_L11-15_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusParameterBindingProvider`  
`class IOptimusParameterBindingProvider`  
_L20-29_
- desc: Interface that provides a mechanism to query information about parameter bindings
- L25 _public prototype_ `virtual FString GetBindingDeclaration(FName BindingName) const = 0;`
- L26 _public prototype_ `virtual bool GetBindingSupportAtomicCheckBoxVisibility(FName BindingName) const = 0;`
- L27 _public prototype_ `virtual bool GetBindingSupportReadCheckBoxVisibility(FName BindingName) const = 0;`
- L28 _public prototype_ `virtual EOptimusDataTypeUsageFlags GetTypeUsageFlags(const FOptimusDataDomain& InDataDomain) const = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusPathResolver.h` (Public)


#### class `UOptimusPathResolver`  
`class UOptimusPathResolver : public UInterface`  
_L20-24_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusPathResolver`  
`class IOptimusPathResolver`  
_L27-53_
- L34 _public prototype_ `virtual IOptimusNodeGraphCollectionOwner* ResolveCollectionPath(const FString& InPath) = 0;` — Takes a collection path string and attempts to resolve it to a specific graph collection. @return The node graph found from this path, or nullptr if nothing was found.
- L38 _public prototype_ `virtual UOptimusNodeGraph* ResolveGraphPath(const FString& InPath) = 0;` — Takes a graph path string and attempts to resolve it to a specific graph @return The node graph found from this path, or nullptr if nothing was found.
- L42 _public prototype_ `virtual UOptimusNode* ResolveNodePath(const FString& InPath) = 0;` — Takes a node path string and attempts to resolve it to a specific node @return The node found from this path, or nullptr if nothing was found.
- L46 _public prototype_ `virtual UOptimusNodePin* ResolvePinPath(const FString& InPinPath) = 0;` — Takes a dot-separated path string and attempts to resolve it to a specific pin on a node. @return The node found from this path, or nullptr if nothing was found.
- L48 _public prototype_ `virtual UOptimusResourceDescription* ResolveResource(FName InResourceName) const = 0;`
- L50 _public prototype_ `virtual UOptimusVariableDescription* ResolveVariable(FName InVariableName) const = 0;`
- L52 _public prototype_ `virtual UOptimusComponentSourceBinding* ResolveComponentBinding(FName InBindingName) const = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusPersistentBufferProvider.h` (Public)


#### class `UOptimusPersistentBufferProvider`  
`class UOptimusPersistentBufferProvider : public UInterface`  
_L13-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusPersistentBufferProvider`  
`class IOptimusPersistentBufferProvider`  
_L20-26_
- L25 _public prototype_ `virtual void SetBufferPool(TSharedPtr<FOptimusPersistentBufferPool> InBufferPool) = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusPinMutabilityDefiner.h` (Public)


#### class `UOptimusPinMutabilityDefiner`  
`class UOptimusPinMutabilityDefiner : public UInterface`  
_L12-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### enum `EOptimusPinMutability`  
`enum class EOptimusPinMutability`  
_L19-24_
- reflection: `UENUM()`
- L21 _public enumerator_ `Undefined`
- L22 _public enumerator_ `Immutable`
- L23 _public enumerator_ `Mutable`

#### class `IOptimusPinMutabilityDefiner`  
`class IOptimusPinMutabilityDefiner`  
_L26-33_
- L32 _public prototype_ `virtual EOptimusPinMutability GetOutputPinMutability(const UOptimusNodePin* InPin) const = 0;` — Returns whether the output pin is mutable, immutable or undefined

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusPropertyPinProvider.h` (Public)


#### class `UOptimusPropertyPinProvider`  
`class UOptimusPropertyPinProvider : public UInterface`  
_L14-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusPropertyPinProvider`  
`class IOptimusPropertyPinProvider`  
_L21-27_
- L26 _public prototype_ `virtual TArray<UOptimusNodePin*> GetPropertyPins() const = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusShaderTextProvider.h` (Public)


#### class `UOptimusShaderTextProvider`  
`class UOptimusShaderTextProvider : public UInterface`  
_L9-12_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusShaderTextProvider`  
`class IOptimusShaderTextProvider`  
_L17-34_
- desc: Interface for shader text edit widgets including the gathering of compilation diagnostics for display.
- L24 _public prototype_ `virtual FString GetNameForShaderTextEditor() const = 0;` — Get title for text editor tab.
- L26 _public prototype_ `virtual FString GetDeclarations() const = 0;` — Get test for declaration pane.
- L28 _public prototype_ `virtual FString GetShaderText() const = 0;` — Get shader text for editor pane.
- L30 _public prototype_ `virtual void SetShaderText(const FString& NewText) = 0;` — Set shader text after edit modifications.
- L32 _public prototype_ `virtual bool IsShaderTextReadOnly() const = 0;` — Return true is the shader text can be edited

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusUnnamedNodePinProvider.h` (Public)


#### class `UOptimusUnnamedNodePinProvider`  
`class UOptimusUnnamedNodePinProvider : public UInterface`  
_L12-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IOptimusUnnamedNodePinProvider`  
`class IOptimusUnnamedNodePinProvider`  
_L21-28_
- desc: Interface that provides a mechanism to add pins to node from existing pins
- L26 _public prototype_ `virtual bool IsPinNameHidden(UOptimusNodePin* InPin) const = 0;`
- L27 _public prototype_ `virtual FName GetNameForAdderPin(UOptimusNodePin* InPin) const = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/IOptimusValueProvider.h` (Public)


#### class `UOptimusValueProvider`  
`class UOptimusValueProvider : public UInterface`  
_L14-18_
- reflection: `UINTERFACE()`
- inherits: `UInterface`

#### class `IOptimusValueProvider`  
`class IOptimusValueProvider`  
_L24-35_
- desc: FIXME: A stop-gap shader value provider until we have a proper pin evaluation that handles paths that have a constant, computed, varying and a mix thereof, results.
- L30 _public prototype_ `virtual FOptimusValueIdentifier GetValueIdentifier() const = 0;` — Returns the value name.
- L32 _public prototype_ `virtual FOptimusDataTypeRef GetValueDataType() const = 0;` — Returns the value data type.
- L34 _public prototype_ `virtual FOptimusValueContainerStruct GetValue() const = 0;` — Returns the stored value.

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusActionStack.h` (Public)


#### class `UOptimusActionStack`  
`class UOptimusActionStack : public UObject`  
_L17-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base action class
- L22 _public prototype_ `UOptimusActionStack();`
- L27 _public prototype_ `bool RunAction(FOptimusAction* InAction);` — Run a heap-constructed action created with operator new. The action stack takes ownership of the pointer. If the function fails the pointer is no longer valid.
- L31 _public function_ `RunAction(ArgsType&& ...Args)`
- L36 _public prototype_ `IOptimusPathResolver *GetGraphCollectionRoot() const;`
- L38 _public prototype_ `void SetTransactionScopeFunctions( TFunction<int32(UObject* TransactObject, const FString& Title)> InBeginScopeFunc, TFunction<void(int32 InTransactionId)> InEndScopeFunc );`
- L43 _public prototype_ `bool Redo();`
- L44 _public prototype_ `bool Undo();`
- L48 _public prototype_ `void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L56 _protected prototype_ `void OpenActionScope(const FString& InTitle);` — Open a new action scope. All subsequent calls to RunAction will add actions to the scope but they won't be run until the last action scope is closed.
- L60 _protected prototype_ `bool CloseActionScope();` — Close the current action scope. Once all action scopes are closed, the collected actions are finally run in the order they got added.
- L64 _private prototype_ `bool RunAction(TSharedPtr<FOptimusAction> InAction);`
- L67 _private member_ `int32 TransactedActionIndex = 0;` — `UPROPERTY()`
- L69 _private member_ `int32 CurrentActionIndex = 0;`
- L71 _private member_ `bool bIsRunningAction = false;`
- L73 _private member_ `TArray<TSharedPtr<FOptimusAction>> Actions;`
- L75 _private member_ `TArray<TSharedPtr<FOptimusCompoundAction>> ActionScopes;`
- L77 _private member_ `TFunction<int(UObject* TransactObject, const FString& Title)> BeginScopeFunc;`
- L78 _private member_ `TFunction<void(int InTransactionId)> EndScopeFunc;`

#### class `FOptimusActionScope`  
`class FOptimusActionScope`  
_L81-91_
- L84 _public prototype_ `FOptimusActionScope(UOptimusActionStack& InActionStack, const FString& InTitle);`
- L86 _public prototype_ `~FOptimusActionScope();`
- L88 _public prototype_ `void SetTitle(const FString& InTitle);`
- L90 _private member_ `UOptimusActionStack& ActionStack;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusBindingTypes.h` (Public)


#### struct `FOptimus_ShaderBinding`  
`struct UE_DEPRECATED(5.1, "Replaced with FOptimusParameterBinding") FOptimus_ShaderBinding`  
_L11-26_
- reflection: `USTRUCT()`
- L16 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category=Binding)`
- L19 _public member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY(EditAnywhere, Category = Binding, meta=(UseInResource))`
- L22 _public function_ `bool IsValid() const` — Returns true if the binding is valid and has defined entries

#### struct `FOptimusParameterBinding`  
`struct FOptimusParameterBinding`  
_L30-56_
- reflection: `USTRUCT()`
- L35 _public member_ `FOptimusValidatedName Name;` — `UPROPERTY(EditAnywhere, Category=Binding)`
- L38 _public member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY(EditAnywhere, Category = Binding)`
- L41 _public function_ `bool IsValid() const` — Returns true if the binding is valid and has defined entries
- L47 _public member_ `FOptimusDataDomain DataDomain;` — `UPROPERTY(EditAnywhere, Category = Binding)`
- L51 _public member_ `bool bSupportAtomicIfCompatibleDataType = false;` — `UPROPERTY(EditAnywhere, DisplayName="Support Atomic", Category = Binding)` — Int type resource can optionally support atomic writes, memory is zero-initialized
- L55 _public member_ `bool bSupportRead = false;` — `UPROPERTY(EditAnywhere, DisplayName="Support Read", Category = Binding)` — Optionally support both read and write

#### struct `FOptimusParameterBindingArray`  
`struct FOptimusParameterBindingArray`  
_L60-120_
- reflection: `USTRUCT()`
- L65 _public member_ `TArray<FOptimusParameterBinding> InnerArray;` — `UPROPERTY(EditAnywhere, Category = Binding)`
- L68 _public function_ `template <typename Predicate> const FOptimusParameterBinding* FindByPredicate(Predicate Pred) const`
- L74 _public function_ `template <typename Predicate> FOptimusParameterBinding* FindByPredicate(Predicate Pred)`
- L80 _public function_ `template <typename Predicate> int32 IndexOfByPredicate(Predicate Pred) const`
- L86 _public function_ `template <typename Predicate> int32 IndexOfByPredicate(Predicate Pred)`
- L91 _public function_ `bool IsEmpty() const`
- L96 _public function_ `FOptimusParameterBinding& Last(int32 IndexFromTheEnd = 0)`
- L101 _public function_ `const FOptimusParameterBinding& Last(int32 IndexFromTheEnd = 0) const`
- L106 _public function_ `FOptimusParameterBindingArray& operator=(const TArray<FOptimusParameterBinding>& Rhs)`
- L112 _public function_ `int32 Num() const`
- L113 _public function_ `bool IsValidIndex(int32 Index) const`
- L114 _public function_ `const FOptimusParameterBinding& operator[](int32 InIndex) const`
- L115 _public function_ `FOptimusParameterBinding& operator[](int32 InIndex)`
- L116 _public function_ `inline TArray<FOptimusParameterBinding>::RangedForIteratorType begin()`
- L117 _public function_ `inline TArray<FOptimusParameterBinding>::RangedForConstIteratorType begin() const`
- L118 _public function_ `inline TArray<FOptimusParameterBinding>::RangedForIteratorType end()`
- L119 _public function_ `inline TArray<FOptimusParameterBinding>::RangedForConstIteratorType end() const`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusComponentSource.h` (Public)


#### class `UOptimusComponentSource`  
`class UOptimusComponentSource : public UObject`  
_L19-83_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L26 _public prototype_ `virtual FText GetDisplayName() const PURE_VIRTUAL(UOptimusComponentSource::GetDisplayName, return {}; );` — Returns the component display name to show in the lister. Should be unique.
- L30 _public prototype_ `virtual FName GetBindingName() const PURE_VIRTUAL(UOptimusComponentSource::GetSuggestedBindingName, return {}; );` — Returns a suggested name for the binding. The name may be modified to preserve uniqueness.
- L34 _public prototype_ `virtual TSubclassOf<UActorComponent> GetComponentClass() const PURE_VIRTUAL(UOptimusComponentSource::GetComponentClass, return {}; );` — Returns the actor component that this provider can operate on
- L39 _public prototype_ `virtual TArray<FName> GetExecutionDomains() const PURE_VIRTUAL(UOptimusComponentSource::GetExecutionContexts, return {}; );` — Returns the available execution contexts. The first context is a preferred context when setting initial data domain for a resource.
- L43 _public function_ `virtual int32 GetLodIndex(const UActorComponent* InComponent) const` — Returns the current LOD index associated with a component associated with this source.
- L50 _public function_ `virtual uint32 GetDefaultNumInvocations(const UActorComponent* InComponent, int32 InLod) const` — Returns the total number of thread invocations a component requires in case of non-unified dispatch.
- L58 _public function_ `virtual bool GetComponentElementCountsForExecutionDomain( FName InDomainName, const UActorComponent* InComponent, int32 InLodIndex, TArray<int32>& OutInvocationElementCounts ) const` — For a given execution domain, and component LOD index, return the range of the domain as given by the component that is associated with this source.
- L69 _public prototype_ `virtual bool IsUsableAsPrimarySource() const;` — Returns true if the source can be used by primary bindings.
- L74 _public prototype_ `static TArray<const UOptimusComponentSource*> GetAllSources();` — Returns all registered component source objects
- L77 _public prototype_ `static TSet<FName> GetAllExecutionDomains();` — Returns all execution domains from all available sources
- L80 _public prototype_ `static const UOptimusComponentSource* GetSourceFromDataInterface( const UOptimusComputeDataInterface* InDataInterface );` — Returns a component source that matches a data interface, or nullptr if nothing does

#### class `UOptimusComponentSourceBinding`  
`class UOptimusComponentSourceBinding : public UObject`  
_L87-136_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L95 _public prototype_ `UOptimusDeformer* GetOwningDeformer() const;` — FIXME: Move to interface-based system.
- L98 _public prototype_ `int32 GetIndex() const;` — Get the index of this binding within its container
- L102 _public member_ `FName BindingName;` — `UPROPERTY(EditAnywhere, Category=Binding, meta = (EditCondition = "!bIsPrimaryBinding", HideEditConditionToggle))` — The name to give the binding, to disambiguate it from other bindings of same component type.
- L106 _public member_ `TSubclassOf<UOptimusComponentSource> ComponentType;` — `UPROPERTY(EditAnywhere, Category=Binding)` — The component type that this binding applies to
- L110 _public member_ `TArray<FName> ComponentTags;` — `UPROPERTY(EditAnywhere, Category=Tags, meta=(EditCondition="!bIsPrimaryBinding", HideEditConditionToggle))` — Component tags to automatically bind this component binding to.
- L112 _public function_ `bool IsPrimaryBinding() const`
- L114 _public prototype_ `static FName GetPrimaryBindingName();`
- L116 _public prototype_ `const UOptimusComponentSource* GetComponentSource() const;`
- L119 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L120 _public prototype_ `void PreEditUndo() override;`
- L121 _public prototype_ `void PostEditUndo() override;`
- L128 _protected member_ `bool bIsPrimaryBinding = false;` — `UPROPERTY()`
- L130 _protected member_ `static const FName PrimaryBindingName;`
- L134 _private member_ `FName BindingNameForUndo;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusComputeDataInterface.h` (Public)


#### struct `FOptimusCDIPinDefinition`  
`struct FOptimusCDIPinDefinition`  
_L18-137_
- L23 _public function_ `FOptimusCDIPinDefinition( const FName InPinName, const FString InDataFunctionName, const bool bInMutable = true, const FName InDisplayName = NAME_None ) : PinName(InPinName), DataFunctionName(InDataFunctionName), bMutable(bInMutable), DisplayName(InDisplayName)` — Singleton value read/write. The context name is implied as Optimus::ContextName::Singleton.
- L36 _public function_ `FOptimusCDIPinDefinition( const FName InPinName, const FString InDataFunctionName, const FName InContextName, const FString InCountFunctionName, const bool bInMutable = true, const FName InDisplayName = NAME_None ) : PinName(InPinName), DataFunctionName(InDataFunctionName), DataDimensions` — A single level context lookup.
- L51 _public function_ `FOptimusCDIPinDefinition( const FName InPinName, const FString InDataFunctionName, const FName InContextName, const int32 InMultiplier, const FString InCountFunctionName, const bool bInMutable = true, const FName InDisplayName = NAME_None ) : PinName(InPinName), DataFunctionName(InDataFunctionName), DataDimensions`
- L68 _public function_ `FOptimusCDIPinDefinition( const FName InPinName, const FString InDataFunctionName, const std::initializer_list<FDimensionInfo> InContexts, const bool bInMutable = true, const FName InDisplayName = NAME_None ) : PinName(InPinName), DataFunctionName(InDataFunctionName), bMutable(bInMutable), DisplayName(InDisplayName)`
- L88 _public member_ `FName PinName;` — The name of the pin as seen by the user.
- L107 _public member_ `FString DataFunctionName;` — The name of the function that underlies the data access by the pin. The data functions are used to either read or write to data interfaces, whether explicit or implicit. The read functions take zero to N uint indices, determined by the number of count functions below, and return a value. The write functions take zero to N uint indices, followed by the value, with no return value. For example, for a pin that has two context levels, Vertex and Bone, the lookup function would look something like this: float GetBoneWeight(uint VertexIndex, uint BoneIndex); And the matching element count functions for this data function would look like: uint GetVertexCount(); uint GetVertexBoneCount(uint VertexIndex); Using these examples, the indexes to teh GetBoneWeight function would be limited in range like thus: 0 <= VertexIndex < GetVertexCount()   and 0 <= BoneIndex < GetVertexBoneCount(VertexIndex);
- L128 _public member_ `TArray<FDimensionInfo> DataDimensions;` — List of nested data contexts.
- L131 _public member_ `int32 DomainMultiplier = 1;` — For single-level domains, how many values per element of that dimension's range.
- L133 _public member_ `bool bMutable = true;`
- L136 _public member_ `FName DisplayName;` — Name used for display

#### struct `FOptimusCDIPinDefinition::FDimensionInfo`  
`struct FDimensionInfo`  
_L109-125_
- L113 _public member_ `FName ContextName;` — The data context for a given context level. For pins to be connectable they need to have identical set of contexts, in order.
- L124 _public member_ `FString CountFunctionName;` — The function to calls to get the item count for the data. If there is no count function name then the data is assumed to be a singleton and will be shown as a value pin rather than a resource pin. Otherwise, the number of count functions defines the dimensionality of the lookup. The first count function returns the count required for the context and should accept no arguments. The second count function takes as index any number between zero and the result of the first count function. For example: uint GetFirstDimCount(); uint GetSecondDimCount(uint FirstDimIndex); These two results then bound the indices used to call the data function.

#### struct `FOptimusCDIPropertyPinDefinition`  
`struct FOptimusCDIPropertyPinDefinition`  
_L139-144_
- L141 _public member_ `FName PinName = NAME_None;`
- L143 _public member_ `FOptimusDataTypeRef DataType;`

#### class `UOptimusComputeDataInterface`  
`class UOptimusComputeDataInterface : public UComputeDataInterface`  
_L147-219_
- reflection: `UCLASS(MinimalAPI, Abstract, Const)`
- inherits: `UComputeDataInterface`
- L152 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnPinDefinitionRenamed, FName , FName );`
- L153 _public prototype_ `DECLARE_DELEGATE(FOnPinDefinitionChanged);`
- L163 _public function_ `virtual FString GetDisplayName() const PURE_VIRTUAL(UOptimusComputeDataInterface::GetDisplayName, return {};)` — Returns the name to show on the node that will proxy this interface in the graph view.
- L169 _public function_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const PURE_VIRTUAL(UOptimusComputeDataInterface::GetPinDefinitions, return {};)` — Returns the list of pins that will map to the shader functions provided by this data interface.
- L175 _public function_ `virtual void Initialize()` — Data interface can use this to set default values/pins
- L177 _public prototype_ `virtual void ExportState(FArchive& Ar);`
- L178 _public prototype_ `virtual void ImportState(FArchive& Ar);`
- L181 _public function_ `virtual bool CanPinDefinitionChange()` — Whether the data interface allow users to add / remove pins
- L184 _public function_ `virtual void RegisterPropertyChangeDelegatesForOwningNode(UOptimusNode* InNode)` — Register delegates for data interface node to update when the data interface changes
- L189 _public function_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const PURE_VIRTUAL(UOptimusComputeDataInterface::GetRequiredComponent, return nullptr;) virtual void OnDataTypeChanged(FName InTypeName)` — @return Returns the component type that this data interface operates on.
- L196 _public function_ `virtual void RegisterTypes()` — Register any additional data types provided by this data interface.
- L201 _public prototype_ `TSet<TArray<FName>> GetUniqueNestedContexts() const;` — Returns the list of top-level contexts from this data interface. These can be used to define driver contexts and resource contexts on a kernel. Each nested context will be non-empty.
- L203 _public function_ `virtual bool IsVisible() const`
- L208 _public function_ `virtual TOptional<FText> ValidateForCompile() const`
- L211 _public prototype_ `static TArray<TSubclassOf<UOptimusComputeDataInterface>> GetAllComputeDataInterfaceClasses();` — Returns all known UOptimusComputeDataInterface-derived classes.
- L215 _public prototype_ `static TSet<TArray<FName>> GetUniqueDomainDimensions();` — Returns the list of all nested contexts from all known data interfaces. These can be used to define input/output pin contexts on a kernel.
- L218 _public prototype_ `static void RegisterAllTypes();` — Registers types for all known data interfaces.

#### struct `UOptimusComputeDataInterface::CategoryName`  
`struct CategoryName`  
_L155-160_
- L157 _public member_ `static const FName DataInterfaces;`
- L158 _public member_ `static const FName ExecutionDataInterfaces;`
- L159 _public member_ `static const FName OutputDataInterfaces;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API OPTIMUSCORE_API`
- L152 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnPinDefinitionRenamed, FName , FName );`
- L153 _delegate_ `DECLARE_DELEGATE(FOnPinDefinitionChanged);`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusConstant.h` (Public)


#### struct `FOptimusConstantIdentifier`  
`struct FOptimusConstantIdentifier`  
_L10-51_
- reflection: `USTRUCT()`
- L14 _public prototype_ `FOptimusConstantIdentifier() = default;`
- L15 _public prototype_ `FOptimusConstantIdentifier(const UOptimusNode* InNode, const FName& InGroupName, const FName& InConstantName);`
- L17 _public function_ `bool IsValid() const`
- L22 _public function_ `FName GetLocalConstantName() const`
- L38 _public function_ `bool operator==(FOptimusConstantIdentifier const& InOther) const`
- L44 _public member_ `FName NodePath;` — `UPROPERTY()`
- L47 _public member_ `FName GroupName;` — `UPROPERTY()`
- L50 _public member_ `FName ConstantName;` — `UPROPERTY()`

#### struct `FOptimusConstantDefinition`  
`struct FOptimusConstantDefinition`  
_L54-67_
- reflection: `USTRUCT()`
- L58 _public prototype_ `FOptimusConstantDefinition() = default;`
- L59 _public function_ `FOptimusConstantDefinition(const FOptimusConstantIdentifier& InReferencedConstant) : ReferencedConstant(InReferencedConstant)`
- L60 _public function_ `FOptimusConstantDefinition(const FString& InExpression) : Expression(InExpression)`
- L63 _public member_ `FOptimusConstantIdentifier ReferencedConstant;` — `UPROPERTY()`
- L66 _public member_ `FString Expression;` — `UPROPERTY()`

#### enum `EOptimusConstantType`  
`enum class EOptimusConstantType`  
_L70-74_
- reflection: `UENUM()`
- L72 _public enumerator_ `Input`
- L73 _public enumerator_ `Output`

#### struct `FOptimusConstant`  
`struct FOptimusConstant`  
_L77-105_
- reflection: `USTRUCT()`
- L81 _public prototype_ `FOptimusConstant() = default;`
- L82 _public function_ `FOptimusConstant( const FOptimusConstantIdentifier& InIdentifier, const FOptimusConstantDefinition& InDefinition, int32 InComponentBindingIndex, EOptimusConstantType InType ) : Identifier(InIdentifier), Definition(InDefinition), ComponentBindingIndex(InComponentBindingIndex), Type(InType)`
- L95 _public member_ `FOptimusConstantIdentifier Identifier;` — `UPROPERTY()`
- L98 _public member_ `FOptimusConstantDefinition Definition;` — `UPROPERTY()`
- L101 _public member_ `int32 ComponentBindingIndex = 0;` — `UPROPERTY()`
- L104 _public member_ `EOptimusConstantType Type = EOptimusConstantType::Input;` — `UPROPERTY()`

#### struct `FOptimusConstantIndex`  
`struct FOptimusConstantIndex`  
_L109-126_
- reflection: `USTRUCT()`
- L114 _public member_ `int32 KernelIndex = INDEX_NONE;` — `UPROPERTY()`
- L117 _public member_ `EOptimusConstantType Type = EOptimusConstantType::Input;` — `UPROPERTY()`
- L120 _public member_ `int32 ConstantIndex = INDEX_NONE;` — `UPROPERTY()`
- L122 _public function_ `bool IsValid() const`

#### struct `FOptimusKernelConstantContainer`  
`struct FOptimusKernelConstantContainer`  
_L131-145_
- reflection: `USTRUCT()`
- L135 _public prototype_ `void AddToKernelContainer(const FOptimusConstant& InConstant);`
- L138 _public member_ `TArray<FOptimusConstant> InputConstants;` — `UPROPERTY()`
- L141 _public member_ `TArray<FOptimusConstant> OutputConstants;` — `UPROPERTY()`
- L144 _public member_ `TMap<FName, int32> GroupNameToBindingIndex;` — `UPROPERTY()`

#### struct `FOptimusConstantContainer`  
`struct FOptimusConstantContainer`  
_L148-162_
- reflection: `USTRUCT()`
- L153 _public prototype_ `FOptimusKernelConstantContainer& AddContainerForKernel();`
- L155 _public prototype_ `void Reset();`
- L159 _private member_ `TArray<FOptimusKernelConstantContainer> KernelContainers;` — `UPROPERTY()`

#### struct `FOptimusConstantContainerInstance`  
`struct FOptimusConstantContainerInstance`  
_L164-174_
- L167 _public prototype_ `bool Initialize(const FOptimusConstantContainer& InContainer, const TMap<int32, TMap<FName, TArray<float>>>& InBindingIndexToConstantValues);`
- L168 _public prototype_ `TArray<float> GetConstantValuePerInvocation(const FOptimusConstantIdentifier& InIdentifier) const;`
- L171 _private member_ `TMap<FOptimusConstantIdentifier, TArray<float>> ConstantToValuePerInvocation;`
- L173 _private prototype_ `bool EvaluateAndSaveResult(const FOptimusConstantIdentifier InIdentifier, const FString& InExpression, const TMap<FName, TArray<float>>& InDependentConstants);`

#### Free symbols / members of external scopes

- L32 _function_ `friend uint32 GetTypeHash(const FOptimusConstantIdentifier& InIdentifier)`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusCoreNotify.h` (Public)


#### enum `EOptimusGlobalNotifyType`  
`enum class EOptimusGlobalNotifyType`  
_L12-44_
- L14 _public enumerator_ `GraphAdded` — A new graph has been added (Subject == UOptimusNodeGraph)
- L15 _public enumerator_ `GraphRemoved` — A graph is about to be removed (Subject == UOptimusNodeGraph)
- L16 _public enumerator_ `GraphIndexChanged` — A graph's index been changed (Subject == UOptimusNodeGraph)
- L17 _public enumerator_ `GraphRenamed` — A graph's name has been changed (Subject == UOptimusNodeGraph)
- L19 _public enumerator_ `ComponentBindingAdded` — A binding has been added (Subject == UOptimusResourceDescription)
- L20 _public enumerator_ `ComponentBindingRemoved` — A binding is about to be removed (Subject == UOptimusResourceDescription)
- L21 _public enumerator_ `ComponentBindingIndexChanged` — A binding's index has changed (Subject == UOptimusResourceDescription)
- L22 _public enumerator_ `ComponentBindingRenamed` — A binding has been renamed (Subject == UOptimusResourceDescription)
- L23 _public enumerator_ `ComponentBindingSourceChanged` — A binding's type has been changed (Subject == UOptimusResourceDescription)
- L25 _public enumerator_ `ResourceAdded` — A resource has been added (Subject == UOptimusResourceDescription)
- L26 _public enumerator_ `ResourceRemoved` — A resource is about to be removed (Subject == UOptimusResourceDescription)
- L27 _public enumerator_ `ResourceIndexChanged` — A resource's index has changed (Subject == UOptimusResourceDescription)
- L28 _public enumerator_ `ResourceRenamed` — A resource has been renamed (Subject == UOptimusResourceDescription)
- L29 _public enumerator_ `ResourceTypeChanged` — A resource's type has been changed (Subject == UOptimusResourceDescription)
- L30 _public enumerator_ `ResourceDomainChanged` — A resource's domain has been changed (Subject == UOptimusResourceDescription)
- L32 _public enumerator_ `VariableAdded` — A variable has been added (Subject == UOptimusVariableDescription)
- L33 _public enumerator_ `VariableRemoved` — A variable is about to be removed (Subject == UOptimusVariableDescription)
- L34 _public enumerator_ `VariableIndexChanged` — A variable's index has changed (Subject == UOptimusVariableDescription)
- L35 _public enumerator_ `VariableRenamed` — A variable has been renamed (Subject == UOptimusVariableDescription)
- L36 _public enumerator_ `VariableTypeChanged` — A variable's type has been changed (Subject == UOptimusVariableDescription)
- L38 _public enumerator_ `ConstantValueChanged` — A constant's value has been changed (Subject == UOptimusNode_ConstantValue)
- L40 _public enumerator_ `NodeTypeAdded` — A new node type has been added (Subject == UClass)
- L41 _public enumerator_ `NodeTypeRemoved` — A node type is about to be removed (Subject == UClass)
- L43 _public enumerator_ `DataTypeChanged` — A user defined struct type is changed (Subject == nullptr)

#### enum `EOptimusGraphNotifyType`  
`enum class EOptimusGraphNotifyType`  
_L50-69_
- L52 _public enumerator_ `NodeAdded` — A new node has been added (Subject == UOptimusNode)
- L53 _public enumerator_ `NodeRemoved` — A node has been removed (Subject == UOptimusNode)
- L54 _public enumerator_ `NodeDisplayNameChanged` — A node's display name has changed (Subject == UOptimusNode)
- L55 _public enumerator_ `NodePositionChanged` — A node's position in the graph has changed (Subject == UOptimusNode)
- L56 _public enumerator_ `NodeDiagnosticLevelChanged` — A node's error stat has changed (Subject == UOptimusNode)
- L58 _public enumerator_ `LinkAdded` — A link between nodes has been added (Subject == UOptimusNodeLink)
- L59 _public enumerator_ `LinkRemoved` — A link between nodes has been removed (Subject == UOptimusNodeLink)
- L61 _public enumerator_ `PinAdded` — A pin has been added to a node (Subject = UOptimusNodePin)
- L62 _public enumerator_ `PinRemoved` — A pin on a node is being removed (Subject = UOptimusNodePin)
- L63 _public enumerator_ `PinMoved` — A pin on a node has been moved (Subject = UOptimusNodePin)
- L64 _public enumerator_ `PinValueChanged` — A pin on a node has had its value changed (Subject = UOptimusNodePin)
- L65 _public enumerator_ `PinRenamed` — A pin's name has changed (Subject = UOptimusNodePin)
- L66 _public enumerator_ `PinTypeChanged` — A pin's underlying type has changed (Subject = UOptimusNodePin)
- L67 _public enumerator_ `PinDataDomainChanged` — A pin's data domain has changed (Subject = UOptimusNodePin)
- L68 _public enumerator_ `PinExpansionChanged` — A pin's expansion state has changed (Subject = UOptimusNodePin)

#### Free symbols / members of external scopes

- L47 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOptimusGlobalNotifyDelegate, EOptimusGlobalNotifyType , UObject* );` — A delegate for subscribing / reacting to Optimus global notifications.
- L47 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOptimusGlobalNotifyDelegate, EOptimusGlobalNotifyType , UObject* );` — A delegate for subscribing / reacting to Optimus global notifications.
- L72 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOptimusGraphNotifyDelegate, EOptimusGraphNotifyType , UOptimusNodeGraph* , UObject* );` — A delegate for subscribing / reacting to Optimus graph local notifications.
- L72 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOptimusGraphNotifyDelegate, EOptimusGraphNotifyType , UOptimusNodeGraph* , UObject* );` — A delegate for subscribing / reacting to Optimus graph local notifications.

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusDataDomain.h` (Public)


#### enum `EOptimusDataDomainType`  
`enum class EOptimusDataDomainType`  
_L30-34_
- reflection: `UENUM()`
- L32 _public enumerator_ `Dimensional = 0`
- L33 _public enumerator_ `Expression = 1` — Dimensional = 0,	  Dimensional, e.g. has zero or more named dimensions of lookup. Zero-dimensional data domain is a singleton, e.g. a parameter

#### struct `FOptimusDataDomain`  
`struct FOptimusDataDomain`  
_L50-154_
- reflection: `USTRUCT()`
- desc: A struct to specify the domain range of a resource buffer, as defined by compute kernels and data interfaces. Data domains can be multi-dimensional, expression-based, or empty. Empty domains on pins imply a single value, like a parameter. Domains come in two flavors, either as a pre-defined list with a multiplier, or as an arithmetic expression. For domains with a multiplier, the multiplier only applies to the innermost dimension (e.g. Vertex.Bone x 2, allows for two values per-bone, but not two values per-bone _and_ per-vertex) The expression can take any execution domain, or none (e.g. "Vertex * 2 + 1", "Triangle * 2 + Vertex * 6", "1024"). If an expression is used, the domain is one-dimensional. As of now, expression domain comparison is done on the string level, such that "Vertex * 2" and "2 * Vertex" are not marked as compatible domains.
- L54 _public prototype_ `FOptimusDataDomain() = default;`
- L56 _public function_ `explicit FOptimusDataDomain(TArray<FName> InDimensionNames) : DimensionNames(InDimensionNames)`
- L60 _public function_ `explicit FOptimusDataDomain(TArray<FName> InDimensionNames, int32 InMultiplier) : DimensionNames(InDimensionNames), Multiplier(DimensionNames.Num() == 1 ? FMath::Max(InMultiplier, 1) : 1)`
- L66 _public function_ `FOptimusDataDomain(FString InExpression) : Type(EOptimusDataDomainType::Expression), Expression(MoveTemp(InExpression))`
- L71 _public prototype_ `FOptimusDataDomain(const FOptimusExecutionDomain& InExecutionDomain);`
- L74 _public member_ `EOptimusDataDomainType Type = EOptimusDataDomainType::Dimensional;` — `UPROPERTY(EditAnywhere, Category = DataDomain)`
- L78 _public member_ `TArray<FName> DimensionNames;` — `UPROPERTY(EditAnywhere, Category = DataDomain, meta=(EditCondition="DomainType==EOptimusDataDomainType::Dimensional"))` — The name of the context that this resource/kernel applies to.
- L81 _public member_ `int32 Multiplier = 1;` — `UPROPERTY(EditAnywhere, Category = DataDomain, meta=(ClampMin=1, UIMax=8, SupportDynamicSliderMaxValue="true", EditCondition="DomainType==EOptimusDataDomainType::Dimensional"))`
- L84 _public member_ `FString Expression;` — `UPROPERTY(EditAnywhere, Category = DataDomain, meta=(EditCondition="DomainType==EOptimusDataDomainType::Expression"))`
- L88 _public function_ `bool IsSingleton() const` — Convenience function to check if this data domain is a singleton
- L94 _public function_ `bool IsMultiDimensional() const` — Convenience function to check if this data domain is Multi-dimensional
- L99 _public function_ `int NumDimensions() const`
- L116 _public function_ `bool IsOneDimensional() const` — Convenience function to check if this data domain is One-dimensional
- L122 _public function_ `bool IsFullyDefined() const`
- L133 _public prototype_ `FString ToString() const;` — Convert the data domain to a text serializable string
- L136 _public prototype_ `static FOptimusDataDomain FromString(const FString& InString);` — Create a data domain object from a serializable string generated by the above function.
- L138 _public prototype_ `bool operator==(const FOptimusDataDomain& InOtherDomain) const;`
- L139 _public function_ `bool operator!=(const FOptimusDataDomain& InOtherDomain) const`
- L140 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L141 _public prototype_ `void BackCompFixupLevels();`
- L143 _public prototype_ `TOptional<FString> AsExpression() const;`
- L145 _public prototype_ `TSet<FName> GetUsedConstants() const;`
- L147 _public prototype_ `FString GetDisplayName() const;`
- L149 _public prototype_ `static bool AreCompatible(const FOptimusDataDomain& InOutput, const FOptimusDataDomain& InInput, FString* OutReason);`
- L153 _private member_ `TArray<FName> LevelNames_DEPRECATED{"Ver` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FOptimusDataDomain> : public TStructOpsTypeTraitsBase2<FOptimusDataDomain>`  
_L157-164_
- inherits: `TStructOpsTypeTraitsBase2<FOptimusDataDomain>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L160-163_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OPTIMUSCORE_API`
- L13 _namespace_ `namespace Optimus`
- L13 _namespace_ `namespace DomainName` (scope `Optimus`)
- L15 _externvar_ `extern const FName Singleton;` (scope `Optimus::DomainName`)
- L16 _externvar_ `extern const FName Vertex;` (scope `Optimus::DomainName`)
- L17 _externvar_ `extern const FName Triangle;` (scope `Optimus::DomainName`)
- L18 _externvar_ `extern const FName Bone;` (scope `Optimus::DomainName`)
- L19 _externvar_ `extern const FName UVChannel;` (scope `Optimus::DomainName`)
- L20 _externvar_ `extern const FName Index0;` (scope `Optimus::DomainName`)
- L23 _namespace_ `namespace Optimus`
- L25 _prototype_ `FString FormatDimensionNames(const TArray<FName>& InNames);` (scope `Optimus`)
- L161 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonca4c9ddb0103`)
- L162 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonca4c9ddb0103`)

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusDataType.h` (Public)


#### enum `EOptimusDataTypeUsageFlags`  
`enum class EOptimusDataTypeUsageFlags : uint8`  
_L18-29_
- reflection: `UENUM(meta = (Bitflags))`
- desc: These flags govern how the data type can be used
- L20 _public enumerator_ `None= 0`
- L22 _public enumerator_ `Resource = 1 << 0`
- L23 _public enumerator_ `Variable = 1 << 1` — Resource				= 1 << 0,		  This type can be used in a resource
- L24 _public enumerator_ `AnimAttributes = 1 << 2` — Variable				= 1 << 1,		  This type can be used in a variable
- L25 _public enumerator_ `DataInterfaceOutput = 1 << 3` — AnimAttributes			= 1 << 2,		  This type can be used to query a single anim attribute on a single bone
- L26 _public enumerator_ `PinType = 1 << 4` — DataInterfaceOutput		= 1 << 3,		  This type can be used as output of a data interface (or input for terminal data interfaces)
- L27 _public enumerator_ `PerBoneAnimAttribute = 1 << 5` — PinType					= 1 << 4,		  This type can be used as pin type
- L28 _public enumerator_ `Property = 1 << 6` — PerBoneAnimAttribute	= 1 << 5,		  This type can be used to query a per-bone anim attribute to produce a bone buffer

#### enum `EOptimusDataTypeFlags`  
`enum class EOptimusDataTypeFlags : uint8`  
_L35-41_
- reflection: `UENUM(meta = (Bitflags))`
- desc: These flags are for indicating type behaviour
- L37 _public enumerator_ `None = 0`
- L39 _public enumerator_ `IsStructType = 1 << 0`
- L40 _public enumerator_ `ShowElements = 1 << 1` — IsStructType		= 1 << 0,		  This is a UScriptStruct-based type.

#### struct `FOptimusDataType`  
`struct FOptimusDataType`  
_L46-120_
- reflection: `USTRUCT()`
- L50 _public prototype_ `FOptimusDataType() = default;`
- L54 _public prototype_ `FProperty* CreateProperty( UStruct *InScope, FName InName ) const;` — Create an FProperty with the given scope and name, but only if the UsageFlags contains EOptimusDataTypeUsageFLags::Variable. Otherwise it returns a nullptr.
- L66 _public prototype_ `bool ConvertPropertyValueToShader( TArrayView<const uint8> InValue, FShaderValueContainer& OutConvertedValue ) const;` — Convert an FProperty value to a value compatible with the shader parameter data layout. The InValue parameter should point at the memory location governed by the FProperty for this data type, and OutConvertedValue is an array to store the bytes for the converted value. If the function failed, a nullptr is returned and the state of the OutConvertedValue is undefined. Upon success, the return value is a pointer to the value following the converted input value, and the converted output value array will have been grown to accommodate the newly converted value.
- L72 _public prototype_ `FShaderValueContainer MakeShaderValue() const;` — Return a value struct that can hold raw shader value of this type
- L75 _public prototype_ `bool CanCreateProperty() const;` — Returns true if the data type can create a FProperty object to represent it.
- L78 _public prototype_ `int32 GetNumArrays() const;` — Returns the total number of array members (recursive) in the shader type
- L81 _public prototype_ `int32 GetArrayShaderValueOffset(int32 InArrayIndex) const;` — Returns the offset from the beginning of shader type of each array typed shader struct member
- L84 _public prototype_ `int32 GetArrayElementShaderValueSize(int32 InArrayIndex) const;` — Returns the element size of each array typed shader struct member
- L86 _public prototype_ `bool IsArrayType() const;`
- L89 _public member_ `FName TypeName;` — `UPROPERTY()`
- L92 _public member_ `FText DisplayName;` — `UPROPERTY()`
- L96 _public member_ `FShaderValueTypeHandle ShaderValueType;` — `UPROPERTY()` — Shader value type that goes with this Optimus pin type.
- L101 _public member_ `int32 ShaderValueSize = 0;` — `UPROPERTY()` — Size of the shader value that can hold a value of this type. If this type is not a shader value, then this value is zero.
- L104 _public member_ `FName TypeCategory;` — `UPROPERTY()`
- L107 _public member_ `TWeakObjectPtr<UObject> TypeObject;` — `UPROPERTY()`
- L110 _public member_ `bool bHasCustomPinColor = false;` — `UPROPERTY()`
- L113 _public member_ `FLinearColor CustomPinColor = FLinearColor::Black;` — `UPROPERTY()`
- L116 _public member_ `EOptimusDataTypeUsageFlags UsageFlags = EOptimusDataTypeUsageFlags::None;` — `UPROPERTY()`
- L119 _public member_ `EOptimusDataTypeFlags TypeFlags = EOptimusDataTypeFlags::None;` — `UPROPERTY()`

#### struct `FOptimusDataTypeRef`  
`struct FOptimusDataTypeRef`  
_L128-178_
- reflection: `USTRUCT(BlueprintType)`
- desc: A reference object for an Optimus data type to use in UObjects and other UStruct-like things
- L132 _public prototype_ `FOptimusDataTypeRef(FOptimusDataTypeHandle InTypeHandle = {});`
- L134 _public function_ `bool IsValid() const`
- L141 _public function_ `explicit operator bool() const`
- L146 _public prototype_ `void Set(FOptimusDataTypeHandle InTypeHandle);`
- L148 _public prototype_ `FOptimusDataTypeHandle Resolve() const;`
- L150 _public function_ `const FOptimusDataType* operator->() const`
- L155 _public function_ `const FOptimusDataType& operator*() const`
- L160 _public function_ `bool operator==(const FOptimusDataTypeRef& InOther) const`
- L165 _public function_ `bool operator!=(const FOptimusDataTypeRef& InOther) const`
- L171 _public member_ `FName TypeName;` — `UPROPERTY(EditAnywhere, Category=Type)`
- L175 _public member_ `TSoftObjectPtr<UObject> TypeObject;` — `UPROPERTY(EditAnywhere, Category=Type)` — A soft pointer to the type object helps enforce asset dependency
- L177 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FOptimusDataTypeRef> : public TStructOpsTypeTraitsBase2<FOptimusDataTypeRef>`  
_L181-187_
- inherits: `TStructOpsTypeTraitsBase2<FOptimusDataTypeRef>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L184-186_

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API OPTIMUSCORE_API`
- L123 _typedef_ `using FOptimusDataTypeHandle = TSharedPtr<const FOptimusDataType>;`
- L185 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anona2d01fe50103`)

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusDataTypeRegistry.h` (Public)


#### class `FOptimusDataTypeRegistry`  
`class FOptimusDataTypeRegistry : public FGCObject`  
_L19-299_
- inherits: `FGCObject`
- L23 _public prototype_ `DECLARE_EVENT_OneParam(FOptimusDataTypeRegistry, FOnDataTypeChanged, FName );`
- L25 _public typedef_ `using PropertyCreateFuncT = TFunction<FProperty *(FFieldVariant InScope, FName InName)>;`
- L32 _public typedef_ `using PropertyValueConvertFuncT = TFunction<bool(TArrayView<const uint8> InRawValue, FShaderValueContainerView OutShaderValue)>;` — Defines a function that takes an array view on UE property data and converts it to a matching HLSL shader value data. It's expected that the input and output array views hold enough data to both read all property data for this type and write out shader values matching these data.
- L40 _public member_ `static const TCHAR* Matrix34TypeName;`
- L45 _public prototype_ `static FName GetTypeName(const FFieldClass& InFieldClass);`
- L46 _public prototype_ `static FName GetTypeName(UScriptStruct* InStruct);`
- L47 _public prototype_ `static FName GetTypeName(const FAssetData& InStructAsset);`
- L49 _public prototype_ `static FName GetArrayTypeName(const FFieldClass& InFieldClass);`
- L50 _public prototype_ `static FName GetArrayTypeName(UScriptStruct* InStruct);`
- L51 _public prototype_ `static FName GetArrayTypeName(FName InElementTypeName);`
- L54 _public prototype_ `static FOptimusDataTypeRegistry &Get();` — Get the singleton registry object
- L57 _public prototype_ `bool RegisterType( const FFieldClass &InFieldType, const FText& InDisplayName, FShaderValueTypeHandle InShaderValueType, PropertyCreateFuncT InPropertyCreateFunc, PropertyValueConvertFuncT InPropertyValueConvertFunc, FName InPinCategory, TOptional<FLinearColor> InPinColor, EOptimusDataTypeUsageFlags InUsageFlags );` — Register a POD type that has corresponding types on both the UE and HLSL side.
- L69 _public prototype_ `bool RegisterType( UScriptStruct *InStructType, FShaderValueTypeHandle InShaderValueType, TOptional<FLinearColor> InPinColor, bool bInShowElements, EOptimusDataTypeUsageFlags InUsageFlags );` — Register a complex type that has corresponding types on both the UE and HLSL side.
- L77 _public prototype_ `bool RegisterType( UScriptStruct *InStructType, const FText& InDisplayName, FShaderValueTypeHandle InShaderValueType, TOptional<FLinearColor> InPinColor, bool bInShowElements, EOptimusDataTypeUsageFlags InUsageFlags );`
- L88 _public prototype_ `bool RegisterType( UScriptStruct *InStructType, FShaderValueTypeHandle InShaderValueType, PropertyValueConvertFuncT InPropertyValueConvertFunc, TOptional<FLinearColor> InPinColor, bool bInShowElements, EOptimusDataTypeUsageFlags InUsageFlags );` — Register a complex type that has corresponding types on both the UE and HLSL side that requires a custom conversion function
- L97 _public prototype_ `bool RegisterType( UScriptStruct *InStructType, const FText& InDisplayName, FShaderValueTypeHandle InShaderValueType, PropertyValueConvertFuncT InPropertyValueConvertFunc, TOptional<FLinearColor> InPinColor, bool bInShowElements, EOptimusDataTypeUsageFlags InUsageFlags );`
- L108 _public prototype_ `bool RegisterType( UScriptStruct *InStructType, const FText& InDisplayName, TOptional<FLinearColor> InPinColor, EOptimusDataTypeUsageFlags InUsageFlags );` — Register a complex type that has only has correspondence on the UE side.
- L115 _public prototype_ `bool RegisterType( UClass* InClassType, const FText& InDisplayName, TOptional<FLinearColor> InPinColor, EOptimusDataTypeUsageFlags InUsageFlags );`
- L124 _public prototype_ `bool RegisterType( FName InTypeName, const FText& InDisplayName, FShaderValueTypeHandle InShaderValueType, FName InPinCategory, UObject* InPinSubCategory, FLinearColor InPinColor, EOptimusDataTypeUsageFlags InUsageFlags );` — Register a type that only has correspondence on the HLSL side. Presence of the EOptimusDataTypeFlags::UseInVariable results in an error.
- L135 _public prototype_ `bool RegisterStructType( UScriptStruct *InStructType );` — Register a complex type that has corresponding types on both the UE and HLSL side.
- L140 _public prototype_ `bool RegisterArrayTypeIfApplicable( FOptimusDataTypeHandle InElementDataType );` — Register a array type that has corresponding types on both the UE and HLSL side.
- L145 _public prototype_ `void RefreshStructType( UUserDefinedStruct *InStructType );` — Refresh struct type info in case a user defined struct is changed.
- L150 _public prototype_ `void UnregisterType(FName InTypeName);` — Unregister a type
- L153 _public prototype_ `TArray<FOptimusDataTypeHandle> GetAllTypes() const;` — Returns all registered types
- L158 _public prototype_ `FOptimusDataTypeHandle FindType(const FProperty &InProperty) const;` — Find the registered type associated with the given property's type. Returns an invalid handle if no registered type is associated.
- L163 _public prototype_ `FOptimusDataTypeHandle FindArrayType(const FProperty &InProperty) const;` — Find the registered array type associated with the given property's type. Returns an invalid handle if no registered type is associated.
- L168 _public prototype_ `FOptimusDataTypeHandle FindType(const FFieldClass& InFieldType) const;` — Find the registered type associated with the given field class. Returns an invalid handle if no registered type is associated.
- L173 _public prototype_ `FOptimusDataTypeHandle FindArrayType(const FFieldClass& InFieldType) const;` — Find the registered array type associated with the given field class. Returns an invalid handle if no registered array type is associated.
- L178 _public prototype_ `FOptimusDataTypeHandle FindType(const UClass& InClassType) const;` — Find the registered type associated with the given object class. Returns an invalid handle if no registered type is associated.
- L183 _public prototype_ `FOptimusDataTypeHandle FindArrayType(const UClass& InClassType) const;` — Find the registered array type associated with the given object class. Returns an invalid handle if no registered array type is associated.
- L188 _public prototype_ `FOptimusDataTypeHandle FindType(FName InTypeName) const;` — Find the registered type with the given name. Returns an invalid handle if no registered type with that name exists.
- L193 _public prototype_ `FOptimusDataTypeHandle FindArrayType(FName InTypeName) const;` — Find the registered array type with the given element type name. Returns an invalid handle if no registered type with that name exists.
- L198 _public prototype_ `FOptimusDataTypeHandle FindType(UScriptStruct* InStruct) const;` — Find the registered array type with the given struct. Returns an invalid handle if no registered type with that name exists.
- L203 _public prototype_ `FOptimusDataTypeHandle FindArrayType(UScriptStruct* InStruct) const;` — Find the registered arraytype with the given element type struct. Returns an invalid handle if no registered type with that name exists.
- L210 _public prototype_ `FOptimusDataTypeHandle FindType(FShaderValueTypeHandle InValueType) const;` — FIXME: We should allow for some kind of type hinting from the HLSL side (e.g. vector4 a color or a vector of four independent scalars).
- L217 _public prototype_ `FOptimusDataTypeHandle FindArrayType(FShaderValueTypeHandle InValueType) const;` — FIXME: We should allow for some kind of type hinting from the HLSL side (e.g. vector4 a color or a vector of four independent scalars).
- L222 _public prototype_ `PropertyValueConvertFuncT FindPropertyValueConvertFunc(FName InTypeName) const;` — A helper function to return a property conversion function. The function can be unbound and that should be checked prior to calling
- L225 _public prototype_ `TArray<FArrayMetadata> FindArrayMetadata(FName InTypeName) const;` — A helper function to return the array metadata.
- L228 _public prototype_ `UScriptStruct* FindAttributeType(FName InTypeName) const;` — A helper function to return the corresponding animation attribute type.
- L230 _public prototype_ `TArray<FOptimusDataTypeHandle> GetAllTypesWithAtomicSupport() const;`
- L232 _public prototype_ `bool DoesTypeSupportAtomic(FOptimusDataTypeHandle InType);`
- L234 _public prototype_ `FOnDataTypeChanged& GetOnDataTypeChanged();`
- L237 _public function_ `FString GetReferencerName() const override` — -- FGCObject overrides
- L238 _public prototype_ `void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L245 _protected prototype_ `static void RegisterBuiltinTypes();` — Call during module init to register all known built-in types
- L248 _protected prototype_ `static void UnregisterAllTypes();` — Call during module shutdown to release memory
- L251 _protected prototype_ `static void RegisterEngineCallbacks();` — Call during module init to register asset registry callbacks for struct type registration
- L254 _protected prototype_ `static void UnregisterEngineCallbacks();` — Call during module shutdown to unregister asset registry callbacks
- L259 _protected prototype_ `PropertyCreateFuncT FindPropertyCreateFunc(FName InTypeName) const;` — A helper function to return a property create function. The function can be unbound and that should be checked prior to calling
- L263 _private prototype_ `FOptimusDataTypeRegistry();`
- L266 _private prototype_ `void OnFilesLoaded();` — Callbacks to update registry when user defined structs are loaded/removed/renamed
- L267 _private prototype_ `void OnAssetRemoved(const FAssetData& InAssetData);`
- L268 _private prototype_ `void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldName);`
- L271 _private prototype_ `void OnAnimationAttributeRegistryChanged(const UScriptStruct* InScriptStruct, bool bIsAdded);` — Callbacks to update registry when list of user defined structs supported by the animation attribute system is changed
- L274 _private prototype_ `bool RegisterType( FName InTypeName, TFunction<void(FOptimusDataType &)> InFillFunc, PropertyCreateFuncT InPropertyCreateFunc = {}, PropertyValueConvertFuncT InPropertyValueConvertFunc = {}, TArray<FArrayMetadata> InArrayMetadata = {} );`
- L283 _private prototype_ `static EOptimusDataTypeUsageFlags GetStructTypeUsageFlag(UScriptStruct* InStruct);` — Check if a type can be registered
- L293 _private member_ `TMap<FName , FTypeInfo> RegisteredTypes;`
- L294 _private member_ `TArray<FName> RegistrationOrder;`
- L296 _private member_ `TSet<FName> TypeWithAtomicSupport;`
- L298 _private member_ `FOnDataTypeChanged OnDataTypeChanged;`

#### struct `FOptimusDataTypeRegistry::FArrayMetadata`  
`struct FArrayMetadata`  
_L34-38_
- L36 _public member_ `int32 ElementShaderValueSize;`
- L37 _public member_ `int32 ShaderValueOffset;`

#### struct `FOptimusDataTypeRegistry::FTypeInfo`  
`struct FTypeInfo`  
_L285-291_
- L287 _public member_ `TSharedPtr<FOptimusDataType> DataType;`
- L288 _public member_ `PropertyCreateFuncT PropertyCreateFunc;`
- L289 _public member_ `PropertyValueConvertFuncT PropertyValueConvertFunc;`
- L290 _public member_ `TArray<FArrayMetadata> ArrayMetadata;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_EVENT_OneParam(FOptimusDataTypeRegistry, FOnDataTypeChanged, FName );`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusDeformer.h` (Public)


#### enum `EOptimusDeformerStatus`  
`enum class EOptimusDeformerStatus : int32`  
_L50-56_
- reflection: `UENUM()`
- L52 _public enumerator_ `Compiled` — Compiled, no warnings, no errors
- L53 _public enumerator_ `CompiledWithWarnings` — Compiled, has warnings
- L54 _public enumerator_ `Modified` — Graph has been modified, needs recompilation
- L55 _public enumerator_ `HasErrors` — Graph produced errors at the last compile

#### struct `FOptimusComputeGraphInfo`  
`struct FOptimusComputeGraphInfo`  
_L60-72_
- reflection: `USTRUCT()`
- L65 _public member_ `EOptimusNodeGraphType GraphType = EOptimusNodeGraphType::Update;` — `UPROPERTY()`
- L68 _public member_ `FName GraphName;` — `UPROPERTY()`
- L71 _public member_ `TObjectPtr<UOptimusComputeGraph> ComputeGraph = nullptr;` — `UPROPERTY()`

#### struct `FOptimusNodeGraphCompilationResult`  
`struct FOptimusNodeGraphCompilationResult`  
_L74-81_
- L76 _public member_ `TArray<FOptimusComputeGraphInfo> ComputeGraphInfos;`
- L78 _public member_ `TMap<TWeakObjectPtr<const UComputeDataInterface>, FOptimusDataInterfacePropertyOverrideInfo> DataInterfacePropertyOverrideMap;`
- L80 _public member_ `TMap<FOptimusValueIdentifier, FOptimusValueDescription> ValueMap;`

#### class `UOptimusComponentSourceBindingContainer`  
`class UOptimusComponentSourceBindingContainer : public UObject`  
_L87-95_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A container class that owns component source bindings. This is used to ensure we don't end up with a namespace clash between graphs, variables, bindings and resources.
- L94 _public member_ `TArray<TObjectPtr<UOptimusComponentSourceBinding>> Bindings;` — `UPROPERTY()`

#### class `UOptimusVariableContainer`  
`class UOptimusVariableContainer : public UObject`  
_L101-109_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A container class that owns variable descriptors. This is used to ensure we don't end up with a namespace clash between graphs, variables and resources.
- L108 _public member_ `TArray<TObjectPtr<UOptimusVariableDescription>> Descriptions;` — `UPROPERTY()`

#### class `UOptimusResourceContainer`  
`class UOptimusResourceContainer : public UObject`  
_L116-124_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A container class that owns resource descriptors. This is used to ensure we don't end up with a namespace clash between graphs, variables and resources.
- L123 _public member_ `TArray<TObjectPtr<UOptimusResourceDescription>> Descriptions;` — `UPROPERTY()`

#### class `UOptimusDeformer`  
`class UOptimusDeformer : public UMeshDeformer, public IInterface_PreviewMeshProvider, public IOptimusPathResolver, public IOptimusNodeGraphCollectionOwner, public IOptimusNodeFunctionLibraryOwner, public ISkeletalMeshHalfEdgeBufferAccessor`  
_L132-586_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UMeshDeformer,IInterface_PreviewMeshProvider,IOptimusPathResolver,IOptimusNodeGraphCollectionOwner,IOptimusNodeFunctionLibraryOwner,ISkeletalMeshHalfEdgeBufferAccessor`
- desc: A Deformer Graph is an asset that is used to create and control custom deformations on skeletal meshes.
- L144 _public member_ `static const TCHAR* PublicFunctionsAssetTagName;`
- L145 _public member_ `static const TCHAR* PublicFunctionsWithGuidAssetTagName;`
- L148 _public prototype_ `UOptimusDeformer();`
- L151 _public prototype_ `UOptimusActionStack *GetActionStack();` — Get the action stack for this deformer graph
- L154 _public function_ `EOptimusDeformerStatus GetStatus() const` — Returns the current compilation/error status of the deformer
- L162 _public function_ `FOptimusGlobalNotifyDelegate& GetNotifyDelegate()` — Returns the global delegate used to notify on global operations (e.g. graph, variable, resource lifecycle events).
- L168 _public prototype_ `UOptimusNodeGraph* AddSetupGraph();` — Add a setup graph. This graph is executed once when the deformer is first run from a mesh component. If the graph already exists, this function does nothing and returns nullptr.
- L176 _public prototype_ `UOptimusNodeGraph* AddTriggerGraph(const FString &InName);` — Add a trigger graph. This graph will be scheduled to execute on next tick, prior to the update graph being executed, after being triggered from a blueprint. @param InName The name to give the graph. The name "Setup" cannot be used, since it's a reserved name.
- L179 _public prototype_ `UOptimusNodeGraph* GetUpdateGraph() const;` — Returns the update graph. The update graph will always exist, and there is only one.
- L181 _public prototype_ `bool RemoveGraph(UOptimusNodeGraph* InGraph);` — Remove a graph and delete it.
- L184 _public prototype_ `UOptimusNode* GetSubGraphReferenceNode( const UOptimusNodeSubGraph* InSubGraph ) const;` — Returns the sub graph reference node that is uniquely associated with the given subgraph
- L189 _public prototype_ `TArray<UOptimusFunctionNodeGraph*> GetFunctionGraphs(FName InAccessSpecifier = NAME_None) const;` — Returns all function graphs with the given access specifier. If InAccessSpecifier is None, it performs no filtering
- L191 _public prototype_ `UOptimusFunctionNodeGraph* FindFunctionByGuid(FGuid InFunctionGraphGuid);`
- L194 _public prototype_ `UOptimusVariableDescription* AddVariable( FOptimusDataTypeRef InDataTypeRef, FName InName = NAME_None );` — Variables
- L199 _public prototype_ `bool RemoveVariable( UOptimusVariableDescription* InVariableDesc );`
- L203 _public prototype_ `bool RenameVariable( UOptimusVariableDescription* InVariableDesc, FName InNewName, bool bInForceChange = false );`
- L209 _public prototype_ `bool SetVariableDataType( UOptimusVariableDescription* InVariableDesc, FOptimusDataTypeRef InDataType, bool bInForceChange = false );`
- L215 _public prototype_ `TArray<UOptimusNode*> GetNodesUsingVariable( const UOptimusVariableDescription* InVariableDesc ) const;`
- L220 _public function_ `const TArray<UOptimusVariableDescription*>& GetVariables() const` — `UFUNCTION(BlueprintGetter)`
- L222 _public prototype_ `UOptimusVariableDescription* ResolveVariable( FName InVariableName ) const override;`
- L227 _public prototype_ `UOptimusResourceDescription* AddResource( FOptimusDataTypeRef InDataTypeRef, FName InName = NAME_None );` — Resources
- L232 _public prototype_ `bool RemoveResource( UOptimusResourceDescription* InResourceDesc );`
- L236 _public prototype_ `bool RenameResource( UOptimusResourceDescription* InResourceDesc, FName InNewName, bool bInForceChange = false );`
- L242 _public prototype_ `bool SetResourceDataType( UOptimusResourceDescription* InResourceDesc, FOptimusDataTypeRef InDataType, bool bInForceChange = false );`
- L248 _public prototype_ `bool SetResourceDataDomain( UOptimusResourceDescription* InResourceDesc, const FOptimusDataDomain& InDataDomain, bool bInForceChange = false );`
- L254 _public prototype_ `TArray<UOptimusNode*> GetNodesUsingResource( const UOptimusResourceDescription* InResourceDesc ) const;`
- L259 _public function_ `const TArray<UOptimusResourceDescription*>& GetResources() const` — `UFUNCTION(BlueprintGetter)`
- L261 _public prototype_ `UOptimusResourceDescription* ResolveResource( FName InResourceName ) const override;`
- L266 _public prototype_ `UOptimusComponentSourceBinding* AddComponentBinding( const UOptimusComponentSource *InComponentSource, FName InName = NAME_None );` — Component Bindings
- L271 _public prototype_ `bool RemoveComponentBinding( UOptimusComponentSourceBinding* InBinding );`
- L275 _public prototype_ `bool RenameComponentBinding( UOptimusComponentSourceBinding* InBinding, FName InNewName, bool bInForceChange = false );`
- L281 _public prototype_ `bool SetComponentBindingSource( UOptimusComponentSourceBinding* InBinding, const UOptimusComponentSource *InComponentSource, bool bInForceChange = false );`
- L287 _public prototype_ `TArray<UOptimusNode*> GetNodesUsingComponentBinding( const UOptimusComponentSourceBinding* InBinding ) const;`
- L292 _public function_ `const TArray<UOptimusComponentSourceBinding*>& GetComponentBindings() const` — `UFUNCTION(BlueprintGetter)`
- L295 _public prototype_ `UOptimusComponentSourceBinding* GetPrimaryComponentBinding() const;` — `UFUNCTION(BlueprintGetter)`
- L297 _public prototype_ `UOptimusComponentSourceBinding* ResolveComponentBinding( FName InBindingName ) const override;`
- L304 _public prototype_ `bool Compile();`
- L308 _public function_ `FOptimusCompileBegin& GetCompileBeginDelegate()` — Returns a multicast delegate that can be subscribed to listen for the start of compilation.
- L310 _public function_ `FOptimusCompileEnd& GetCompileEndDelegate()` — Returns a multicast delegate that can be subscribed to listen for the end of compilation but before shader compilation is complete.
- L312 _public function_ `FOptimusGraphCompileMessageDelegate& GetCompileMessageDelegate()` — Returns a multicast delegate that can be subscribed to listen compilation results. Note that the shader compilation results are async and can be returned after the CompileEnd delegate.
- L314 _public prototype_ `void SetAllInstancesCanbeActive(bool bInCanBeActive) const;`
- L317 _public prototype_ `void MarkModified();` — Mark the deformer as modified.
- L320 _public prototype_ `void Serialize(FArchive& Ar) override;` — UObject overrides
- L321 _public prototype_ `void PostLoad() override;`
- L322 _public prototype_ `void BeginDestroy() override;`
- L326 _public prototype_ `void PostRename(UObject* OldOuter, const FName OldName) override;` — Whenever the asset is renamed/moved, generated classes parented to the old package are not moved to the new package automatically (see FAssetRenameManager), so we have to manually perform the move/rename, to avoid invalid reference to the old package
- L327 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L329 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L332 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L336 _public prototype_ `UMeshDeformerInstanceSettings* CreateSettingsInstance( UMeshComponent* InMeshComponent ) override;` — UMeshDeformer overrides
- L340 _public prototype_ `UMeshDeformerInstance* CreateInstance( UMeshComponent* InMeshComponent, UMeshDeformerInstanceSettings* InSettings ) override;`
- L346 _public prototype_ `UOptimusDeformerInstance* CreateOptimusInstance( UMeshComponent* InMeshComponent, UMeshDeformerInstanceSettings* InSettings );`
- L352 _public prototype_ `bool IsSkeletalMeshHalfEdgeBufferRequired() const override;` — ISkeletalMeshHalfEdgeBufferAccessor overrides
- L355 _public prototype_ `void SetPreviewMesh(USkeletalMesh* PreviewMesh, bool bMarkAsDirty = true) override;` — IInterface_PreviewMeshProvider overrides
- L356 _public prototype_ `USkeletalMesh* GetPreviewMesh() const override;`
- L359 _public prototype_ `IOptimusNodeGraphCollectionOwner* ResolveCollectionPath(const FString& InPath) override;` — IOptimusPathResolver overrides
- L360 _public prototype_ `UOptimusNodeGraph* ResolveGraphPath(const FString& InGraphPath) override;`
- L361 _public prototype_ `UOptimusNode* ResolveNodePath(const FString& InNodePath) override;`
- L362 _public prototype_ `UOptimusNodePin* ResolvePinPath(const FString& InPinPath) override;`
- L365 _public function_ `IOptimusNodeGraphCollectionOwner* GetCollectionOwner() const override` — IOptimusNodeGraphCollectionOwner overrides
- L366 _public function_ `IOptimusNodeGraphCollectionOwner* GetCollectionRoot() const override`
- L367 _public function_ `FString GetCollectionPath() const override`
- L369 _public function_ `const TArray<UOptimusNodeGraph*> &GetGraphs() const override`
- L371 _public prototype_ `UOptimusNodeGraph* FindGraphByName(FName InGraphName) const override;`
- L373 _public function_ `UOptimusNodeGraph* CreateGraph( EOptimusNodeGraphType InType, FName InName)`
- L378 _public prototype_ `UOptimusNodeGraph* CreateGraphDirect( EOptimusNodeGraphType InType, FName InName, TOptional<int32> InInsertBefore ) override;`
- L384 _public prototype_ `bool AddGraphDirect( UOptimusNodeGraph* InGraph, int32 InInsertBefore ) override;`
- L389 _public prototype_ `bool RemoveGraphDirect( UOptimusNodeGraph* InGraph, bool bDeleteGraph ) override;`
- L394 _public prototype_ `bool MoveGraphDirect( UOptimusNodeGraph* InGraph, int32 InInsertBefore ) override;`
- L399 _public prototype_ `bool RenameGraphDirect( UOptimusNodeGraph* InGraph, const FString& InNewName ) override;`
- L404 _public prototype_ `bool RenameGraph( UOptimusNodeGraph* InGraph, const FString& InNewName ) override;`
- L410 _public member_ `TObjectPtr<USkeletalMesh> Mesh = nullptr;` — `UPROPERTY(EditAnywhere, Category=Preview)`
- L434 _protected prototype_ `UOptimusResourceDescription* CreateResourceDirect( FName InName );` — Create a resource owned by this deformer but does not add it to the list of known resources. Call AddResource for that
- L439 _protected prototype_ `bool AddResourceDirect( UOptimusResourceDescription* InResourceDesc, const int32 InIndex );` — Adds a resource that was created by this deformer and is owned by it.
- L444 _protected prototype_ `bool RemoveResourceDirect( UOptimusResourceDescription* InResourceDesc );`
- L448 _protected prototype_ `bool RenameResourceDirect( UOptimusResourceDescription* InResourceDesc, FName InNewName );`
- L453 _protected prototype_ `bool SetResourceDataTypeDirect( UOptimusResourceDescription* InResourceDesc, FOptimusDataTypeRef InDataType );`
- L458 _protected prototype_ `bool SetResourceDataDomainDirect( UOptimusResourceDescription* InResourceDesc, const FOptimusDataDomain& InDataDomain );`
- L466 _protected prototype_ `UOptimusVariableDescription* CreateVariableDirect( FName InName );` — Create a resource owned by this deformer but does not add it to the list of known resources. Call AddResource for that
- L471 _protected prototype_ `bool AddVariableDirect( UOptimusVariableDescription* InVariableDesc, const int32 InIndex );` — Adds a resource that was created by this deformer and is owned by it.
- L476 _protected prototype_ `bool RemoveVariableDirect( UOptimusVariableDescription* InVariableDesc );`
- L480 _protected prototype_ `bool RenameVariableDirect( UOptimusVariableDescription* InVariableDesc, FName InNewName );`
- L485 _protected prototype_ `bool SetVariableDataTypeDirect( UOptimusVariableDescription* InResourceDesc, FOptimusDataTypeRef InDataType );`
- L490 _protected prototype_ `UOptimusComponentSourceBinding* CreateComponentBindingDirect( const UOptimusComponentSource *InComponentSource, FName InName = NAME_None );`
- L495 _protected prototype_ `bool AddComponentBindingDirect( UOptimusComponentSourceBinding* InComponentBinding, const int32 InIndex );`
- L500 _protected prototype_ `bool RemoveComponentBindingDirect( UOptimusComponentSourceBinding* InBinding );`
- L504 _protected prototype_ `bool RenameComponentBindingDirect( UOptimusComponentSourceBinding* InBinding, FName InNewName);`
- L508 _protected prototype_ `bool SetComponentBindingSourceDirect( UOptimusComponentSourceBinding* InBinding, const UOptimusComponentSource *InComponentSource );`
- L513 _protected prototype_ `void SetStatusFromDiagnostic(EOptimusDiagnosticLevel InDiagnosticLevel);`
- L515 _protected prototype_ `void Notify(EOptimusGlobalNotifyType InNotifyType, UObject *InObject) const;`
- L519 _protected member_ `TArray<FOptimusComputeGraphInfo> ComputeGraphs;` — `UPROPERTY()` — The compute graphs to execute.
- L522 _protected member_ `TMap<TWeakObjectPtr<const UComputeDataInterface>, FOptimusDataInterfacePropertyOverrideInfo> DataInterfacePropertyOverrideMap;` — `UPROPERTY()`
- L525 _protected member_ `TMap<FOptimusValueIdentifier, FOptimusValueDescription> ValueMap;` — `UPROPERTY()`
- L528 _private prototype_ `void PostLoadFixupMissingComponentBindingsCompat();`
- L529 _private prototype_ `void PostLoadFixupMismatchedResourceDataDomains();`
- L530 _private prototype_ `void PostLoadRemoveDeprecatedExecutionNodes();`
- L531 _private prototype_ `void PostLoadRemoveDeprecatedValueContainerGeneratorClass();`
- L532 _private prototype_ `void PostLoadMoveValueFromGraphDataInterfaceToDeformerValueMap();`
- L535 _private prototype_ `UOptimusComponentSourceBinding* FindCompatibleBindingWithInterface( const UOptimusComputeDataInterface* InDataInterface ) const;` — Find a compatible binding with the given data interface. Returns nullptr if no such binding exists
- L539 _private prototype_ `UOptimusNodeGraph* ResolveGraphPath(const FStringView InPath, FStringView& OutRemainingPath) const;`
- L540 _private prototype_ `UOptimusNode* ResolveNodePath(const FStringView InPath, FStringView& OutRemainingPath) const;`
- L541 _private prototype_ `int32 GetUpdateGraphIndex() const;`
- L543 _private prototype_ `TArray<UOptimusNode*> GetAllNodesOfClass(UClass* InNodeClass) const;`
- L544 _private prototype_ `void OnGraphRenamedOrRemoved(UOptimusNodeGraph* InGraph) const;`
- L545 _private prototype_ `void UpdateFunctionReferenceNodeDisplayName(const FOptimusFunctionGraphIdentifier& InRenamedFunction);`
- L549 _private prototype_ `FOptimusNodeGraphCompilationResult CompileNodeGraphToComputeGraphs( const UOptimusNodeGraph *InNodeGraph, TFunction<void(EOptimusDiagnosticLevel, FText, const UObject*)> InErrorReporter );` — Compile a node graph to a compute graph. Returns one or two complete compute graphs if compilation succeeded.
- L555 _private prototype_ `void OnDataTypeChanged(FName InTypeName);`
- L558 _private member_ `TObjectPtr<UOptimusActionStack> ActionStack = nullptr;` — `UPROPERTY(transient)`
- L561 _private member_ `EOptimusDeformerStatus Status = EOptimusDeformerStatus::Modified;` — `UPROPERTY()`
- L564 _private member_ `TArray<TObjectPtr<UOptimusNodeGraph>> Graphs;` — `UPROPERTY()`
- L567 _private member_ `TObjectPtr<UOptimusComponentSourceBindingContainer> Bindings;` — `UPROPERTY()`
- L570 _private member_ `TObjectPtr<UOptimusVariableContainer> Variables;` — `UPROPERTY()`
- L573 _private member_ `TObjectPtr<UOptimusResourceContainer> Resources;` — `UPROPERTY()`
- L575 _private member_ `FOptimusGlobalNotifyDelegate GlobalNotifyDelegate;`
- L577 _private member_ `FOptimusCompileBegin CompileBeginDelegate;`
- L579 _private member_ `FOptimusCompileEnd CompileEndDelegate;`
- L581 _private member_ `FOptimusGraphCompileMessageDelegate CompileMessageDelegate;`
- L583 _private member_ `FOptimusConstantValueUpdate ConstantValueUpdateDelegate;`
- L585 _private member_ `FOptimusSetAllInstancesCanbeActive SetAllInstancesCanbeActiveDelegate;`

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API OPTIMUSCORE_API`
- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOptimusCompileBegin, UOptimusDeformer *);`
- L43 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOptimusCompileBegin, UOptimusDeformer *);`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOptimusCompileEnd, UOptimusDeformer *);`
- L44 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOptimusCompileEnd, UOptimusDeformer *);`
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOptimusGraphCompileMessageDelegate, FOptimusCompilerDiagnostic const&);`
- L45 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOptimusGraphCompileMessageDelegate, FOptimusCompilerDiagnostic const&);`
- L46 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOptimusConstantValueUpdate, TSoftObjectPtr<UObject>, FOptimusValueContainerStruct const&);`
- L46 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOptimusConstantValueUpdate, TSoftObjectPtr<UObject>, FOptimusValueContainerStruct const&);`
- L47 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOptimusSetAllInstancesCanbeActive, bool);`
- L47 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOptimusSetAllInstancesCanbeActive, bool);`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusDeformerDynamicInstanceManager.h` (Public)


#### enum `EOptimusDeformerExecutionPhase`  
`enum class EOptimusDeformerExecutionPhase : uint8`  
_L19-24_
- reflection: `UENUM()`
- L21 _public enumerator_ `AfterDefaultDeformer = 0`
- L22 _public enumerator_ `OverrideDefaultDeformer = 1`
- L23 _public enumerator_ `BeforeDefaultDeformer = 2`

#### class `UOptimusDeformerDynamicInstanceManager`  
`class UOptimusDeformerDynamicInstanceManager : public UMeshDeformerInstance`  
_L30-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshDeformerInstance`
- desc: Enables composition of multiple deformer instances dynamically
- L36 _public prototype_ `void AllocateResources() override;` — Called to allocate any persistent render resources
- L39 _public prototype_ `void ReleaseResources() override;` — Called when persistent render resources should be released
- L42 _public prototype_ `void EnqueueWork(FEnqueueWorkDesc const& InDesc) override;` — Enqueue the mesh deformer workload on a scene.
- L45 _public prototype_ `EMeshDeformerOutputBuffer GetOutputBuffers() const override;` — Return the buffers that this deformer can potentially write to
- L49 _public prototype_ `bool RequestReadbackDeformerGeometry(TUniquePtr<FMeshDeformerGeometryReadbackRequest> InRequest) override;` — Readback the deformed geometry as mesh description
- L53 _public prototype_ `UMeshDeformerInstance* GetInstanceForSourceDeformer() override;` — InstanceManager is an intermediate instance, call this function to get the instance for the deformer that created this instance manager
- L56 _public prototype_ `void BeginDestroy() override;` — Begin destroying the managaer
- L59 _public prototype_ `void OnObjectBeginDestroy(IMeshDeformerProducer* InObject);` — Remove associated deformer instances when the object is removed
- L62 _public prototype_ `void AddProducerDeformer(IMeshDeformerProducer* InProducer, FGuid InInstanceGuid, UOptimusDeformer* InDeformer);` — Add a producer defomer to the manager (from game thread)
- L65 _public prototype_ `UOptimusDeformerInstance* GetDeformerInstance(FGuid InInstanceGuid);` — Get the object deformer given a guid
- L68 _public prototype_ `void EnqueueProducerDeformer(FGuid InInstanceGuid, EOptimusDeformerExecutionPhase InExecutionPhase, int32 InExecutionGroup);` — Enqueue an object deformer instance to be executed later (from anim/physics... threads )
- L71 _public member_ `TObjectPtr<UOptimusDeformerInstance> DefaultInstance;` — `UPROPERTY()`
- L75 _public member_ `TMap<FGuid, TObjectPtr<UOptimusDeformerInstance>> GuidToRigDeformerInstanceMap;` — `UE_DEPRECATED(5.6, "This property is going to be deleted and replaced by the private member GuidToInstanceMap")` — `UPROPERTY()`
- L81 _private member_ `TMap<FGuid, TObjectPtr<UOptimusDeformerInstance>> GuidToInstanceMap;` — `UPROPERTY()` — Guid to deformer instance map
- L84 _private member_ `TMap<TWeakObjectPtr<UObject>, TArray<FGuid>> ProducerToGuidsMap;` — Object ptr to deformer guids map
- L87 _private member_ `TArray<FGuid> GuidsPendingInit;` — Freshly created deformer instances should be initialized before dispatch
- L90 _private member_ `TMap<EOptimusDeformerExecutionPhase, TMap<int32, TArray<FGuid>>> ExecutionQueueMap;` — Instances per execution group per execution phase
- L93 _private member_ `FCriticalSection EnqueueCriticalSection;` — Enqueue critical section to be thread safe
- L97 _private member_ `TArray<TUniquePtr<FMeshDeformerGeometryReadbackRequest>> GeometryReadbackRequests;` — Readback requests for the current frame

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusDeformerInstance.h` (Public)


#### class `FOptimusPersistentBufferPool`  
`class FOptimusPersistentBufferPool`  
_L31-83_
- L40 _public prototype_ `void GetResourceBuffers( FRDGBuilder& GraphBuilder, FName InResourceName, int32 InLODIndex, int32 InElementStride, int32 InRawStride, TArray<int32> const& InElementCounts, TArray<FRDGBuffer*>& OutBuffers, bool& bOutJustAllocated);` — Get or allocate buffers for the given resource If the buffer already exists but has different sizing characteristics the allocation fails. The number of buffers will equal the size of the InElementCount array. But if the allocation fails, the returned array will be empty.
- L50 _public prototype_ `void GetImplicitPersistentBuffers( FRDGBuilder& GraphBuilder, FName DataInterfaceName, int32 LODIndex, int32 InElementStride, int32 InRawStride, TArray<int32> const& InElementCounts, TArray<FRDGBuffer*>& OutBuffers, bool& bOutJustAllocated);`
- L61 _public prototype_ `void ReleaseResources();` — Release _all_ resources allocated by this pool
- L64 _private prototype_ `void AllocateBuffers( FRDGBuilder& GraphBuilder, int32 InElementStride, int32 InRawStride, TArray<int32> const& InElementCounts, TArray<FOptimusPersistentStructuredBuffer>& OutResourceBuffers, TArray<FRDGBuffer*>& OutBuffers );`
- L73 _private prototype_ `void ValidateAndGetBuffers( FRDGBuilder& GraphBuilder, int32 InElementStride, TArray<int32> const& InElementCounts, const TArray<FOptimusPersistentStructuredBuffer>& InResourceBuffers, TArray<FRDGBuffer*>& OutBuffers ) const;`
- L81 _private member_ `TMap<FName, TMap<int32, TArray<FOptimusPersistentStructuredBuffer>>> ResourceBuffersMap;`
- L82 _private member_ `TMap<FName, TMap<int32, TArray<FOptimusPersistentStructuredBuffer>>> ImplicitBuffersMap;`

#### struct `FOptimusDeformerInstanceExecInfo`  
`struct FOptimusDeformerInstanceExecInfo`  
_L89-110_
- reflection: `USTRUCT()`
- desc: Structure with cached state for a single compute graph.
- L93 _public prototype_ `FOptimusDeformerInstanceExecInfo();`
- L97 _public member_ `FName GraphName;` — `UPROPERTY()` — The name of the graph
- L101 _public member_ `EOptimusNodeGraphType GraphType;` — `UPROPERTY()` — The graph type.
- L105 _public member_ `TObjectPtr<UComputeGraph> ComputeGraph = nullptr;` — `UPROPERTY()` — The ComputeGraph asset.
- L109 _public member_ `FComputeGraphInstance ComputeGraphInstance;` — `UPROPERTY()` — The cached state for the ComputeGraph.

#### struct `FOptimusDeformerInstanceComponentBinding`  
`struct FOptimusDeformerInstanceComponentBinding`  
_L117-137_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines a binding between a component provider in the graph and an actor component in the component hierarchy on the actor whose deformable component we're bound to.
- L123 _public member_ `FName ProviderName;` — `UPROPERTY(VisibleAnywhere, Category="Deformer", meta = (DisplayName = "Binding"))` — Binding name on deformer graph.
- L127 _public member_ `FName ComponentName;` — `UPROPERTY(EditAnywhere, Category="Deformer", meta = (DisplayName = "Component"))` — Component name to bind. This should be sanitized before storage.
- L130 _public prototype_ `TSoftObjectPtr<UActorComponent> GetActorComponent(AActor const* InActor) const;` — Get the component on an actor that matches the stored component name.
- L133 _public prototype_ `static bool GetSanitizedComponentName(FString& InOutName);` — Helpers to create ComponentName.
- L134 _public prototype_ `static FName GetSanitizedComponentName(FName InName);`
- L135 _public prototype_ `static FName GetSanitizedComponentName(UActorComponent const* InComponent);`
- L136 _public prototype_ `static TSoftObjectPtr<UActorComponent> GetActorComponent(AActor const* InActor, FString const& InName);`

#### class `UOptimusDeformerInstanceSettings`  
`class UOptimusDeformerInstanceSettings : public UMeshDeformerInstanceSettings`  
_L146-174_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UMeshDeformerInstanceSettings`
- L153 _private member_ `TWeakObjectPtr<UOptimusDeformer> Deformer;` — `UPROPERTY()` — Stored weak pointer to a deformer. This is only required by the details customization for resolving binding class types.
- L157 _private member_ `TArray<FOptimusDeformerInstanceComponentBinding> Bindings;` — `UPROPERTY(EditAnywhere, Category="Deformer|DeformerSettings", EditFixedSize, meta = (DisplayName = "Component Bindings", EditFixedOrder))` — Array of binding descriptions. This is fixed and used by GetComponentBindings() to resolve final bindings for a given context.
- L161 _public member_ `FOptimusComponentBindingResolver ComponentResolver;` — Optional resolver called for each non-primary binding before tag/class auto-resolution to supply explicit components programmatically.
- L164 _public prototype_ `void InitializeSettings(UOptimusDeformer* InDeformer, UMeshComponent* InPrimaryComponent);` — Setup the object. This initializes the binding names and the primary binding component.
- L167 _public prototype_ `void GetComponentBindings(UOptimusDeformer* InDeformer, UMeshComponent* InPrimaryComponent, TArray<UActorComponent*>& OutComponentBindings) const;` — Get an array of recommended component bindings, based on the stored settings.
- L173 _protected prototype_ `UOptimusComponentSourceBinding const* GetComponentBindingByName(FName InBindingName) const;` — Get a full component source binding object by binding name. Used only by details customization.

#### class `UOptimusDeformerInstance`  
`class UOptimusDeformerInstance : public UMeshDeformerInstance`  
_L182-373_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMeshDeformerInstance`
- desc: Class representing an instance of an Optimus Mesh Deformer, used in a OptimusDeformerDynamicInstanceManager It contains the per instance deformer variable state and local state for each of the graphs in the deformer.
- L191 _public prototype_ `void SetMeshComponent(UMeshComponent* InMeshComponent);` — Set the Mesh Component that owns this instance. Call once before first call to SetupFromDeformer().
- L197 _public prototype_ `void SetInstanceSettings(UOptimusDeformerInstanceSettings* InInstanceSettings);` — Set the instance settings that control this deformer instance. The deformer instance is transient whereas the settings are persistent.
- L204 _public prototype_ `void SetupFromDeformer(UOptimusDeformer* InDeformer);` — Setup the instance. Needs to be called after the UOptimusDeformer creates this instance, and whenever the instance is invalidated. Invalidation happens whenever any bound Data Providers become invalid.
- L208 _public prototype_ `bool SetBoolVariable(FName InVariableName, bool InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Boolean)"))` — Set the value of a boolean variable.
- L211 _public prototype_ `bool SetBoolArrayVariable(FName InVariableName, const TArray<bool>& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Boolean Array)"))`
- L215 _public prototype_ `bool SetIntVariable(FName InVariableName, int32 InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Integer)"))` — Set the value of an integer variable.
- L219 _public prototype_ `bool SetIntArrayVariable(FName InVariableName, const TArray<int32>& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Integer Array)"))`
- L223 _public prototype_ `bool SetInt2Variable(FName InVariableName, const FIntPoint& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Integer2)"))`
- L227 _public prototype_ `bool SetInt2ArrayVariable(FName InVariableName, const TArray<FIntPoint>& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Integer2 Array)"))`
- L231 _public prototype_ `bool SetInt3Variable(FName InVariableName, const FIntVector& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Integer3)"))`
- L235 _public prototype_ `bool SetInt3ArrayVariable(FName InVariableName, const TArray<FIntVector>& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Integer3 Array)"))`
- L239 _public prototype_ `bool SetInt4Variable(FName InVariableName, const FIntVector4& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Integer4)"))`
- L243 _public prototype_ `bool SetInt4ArrayVariable(FName InVariableName, const TArray<FIntVector4>& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Integer4 Array)"))`
- L247 _public prototype_ `bool SetFloatVariable(FName InVariableName, double InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Float)"))`
- L250 _public prototype_ `bool SetFloatArrayVariable(FName InVariableName, const TArray<double>& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Float Array)"))`
- L253 _public prototype_ `bool SetVector2Variable(FName InVariableName, const FVector2D& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Vector2)"))`
- L256 _public prototype_ `bool SetVector2ArrayVariable(FName InVariableName, const TArray<FVector2D>& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Vector2 Array)"))`
- L259 _public prototype_ `bool SetVectorVariable(FName InVariableName, const FVector& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Vector)"))`
- L262 _public prototype_ `bool SetVectorArrayVariable(FName InVariableName, const TArray<FVector>& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Vector Array)"))`
- L265 _public prototype_ `bool SetVector4Variable(FName InVariableName, const FVector4& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Vector4)"))`
- L268 _public prototype_ `bool SetVector4ArrayVariable(FName InVariableName, const TArray<FVector4>& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Vector4 Array)"))`
- L271 _public prototype_ `bool SetLinearColorVariable(FName InVariableName, const FLinearColor& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (LinearColor)"))`
- L274 _public prototype_ `bool SetLinearColorArrayVariable(FName InVariableName, const TArray<FLinearColor>& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (LinearColor Array)"))`
- L277 _public prototype_ `bool SetQuatVariable(FName InVariableName, const FQuat& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Quat)"))`
- L280 _public prototype_ `bool SetQuatArrayVariable(FName InVariableName, const TArray<FQuat>& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Quat Array)"))`
- L283 _public prototype_ `bool SetRotatorVariable(FName InVariableName, const FRotator& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Rotator)"))`
- L286 _public prototype_ `bool SetRotatorArrayVariable(FName InVariableName, const TArray<FRotator>& InValue);` — `UFUNCTION(BlueprintCallable, Category="Deformer", meta=(DisplayName="Set Variable (Rotator Array)"))`
- L290 _public prototype_ `bool SetTransformVariable(FName InVariableName, const FTransform& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Deformer", meta = (DisplayName = "Set Variable (Transform)"))` — Set the value of a transform variable.
- L293 _public prototype_ `bool SetTransformArrayVariable(FName InVariableName, const TArray<FTransform>& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Deformer", meta = (DisplayName = "Set Variable (Transform Array)"))`
- L296 _public prototype_ `bool SetNameVariable(FName InVariableName, const FName& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Deformer", meta = (DisplayName = "Set Variable (Name)"))`
- L299 _public prototype_ `bool SetNameArrayVariable(FName InVariableName, const TArray<FName>& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Deformer", meta = (DisplayName = "Set Variable (Name Array)"))`
- L303 _public prototype_ `bool EnqueueTriggerGraph(FName InTriggerGraphName);` — `UFUNCTION(BlueprintCallable, Category="Deformer")` — Trigger a named trigger graph to run on the next tick
- L306 _public prototype_ `void SetConstantValueDirect(TSoftObjectPtr<UObject> InSourceObject, FOptimusValueContainerStruct const& InValue);` — Directly set a graph constant value.
- L308 _public function_ `FOptimusPersistentBufferPoolPtr GetBufferPool() const`
- L310 _public prototype_ `void SetCanBeActive(bool bInCanBeActive);`
- L312 _public prototype_ `FOptimusValueContainerStruct GetDataInterfacePropertyOverride( const UComputeDataInterface* DataInterface, FName PinName );`
- L317 _public prototype_ `const FShaderValueContainer& GetShaderValue(const FOptimusValueIdentifier& InValueId) const;`
- L320 _public member_ `int32 GraphSortPriorityOffset = 0;` — Making sure compute graphs belong to this instance does not run before instances before it
- L324 _public member_ `FName CurrentExecutionGroupName = NAME_None;` — The execution group name for the current EnqueueWork call (e.g. EndOfFrameUpdate, BeginInitViews). Set on game thread before GetRenderProxy() calls, used by read/write proxies to inform the tracking extension.
- L327 _public function_ `UMeshComponent* GetMeshComponent() const` — Get the primary mesh component that owns this deformer instance.
- L331 _protected prototype_ `void AllocateResources() override;`
- L332 _protected prototype_ `void ReleaseResources() override;`
- L333 _protected prototype_ `void EnqueueWork(FEnqueueWorkDesc const& InDesc) override;`
- L334 _protected prototype_ `EMeshDeformerOutputBuffer GetOutputBuffers() const override;`
- L336 _protected prototype_ `bool RequestReadbackDeformerGeometry(TUniquePtr<FMeshDeformerGeometryReadbackRequest> InRequest) override;`
- L339 _protected function_ `UMeshDeformerInstance* GetInstanceForSourceDeformer() override`
- L344 _private member_ `TWeakObjectPtr<UMeshComponent> MeshComponent;` — `UPROPERTY()` — The Mesh Component that owns this Mesh Deformer Instance.
- L348 _private member_ `TWeakObjectPtr<UOptimusDeformerInstanceSettings> InstanceSettings;` — `UPROPERTY()` — The settings for this Mesh Deformer Instance.
- L352 _private member_ `TArray<FOptimusDeformerInstanceExecInfo> ComputeGraphExecInfos;` — `UPROPERTY()` — An array of state. One for each graph owned by the deformer.
- L354 _private member_ `TMap<FOptimusValueIdentifier, FOptimusValueDescription> ValueMap;`
- L356 _private member_ `TMap<TWeakObjectPtr<const UComputeDataInterface>, FOptimusDataInterfacePropertyOverrideInfo> DataInterfacePropertyOverrideMap;`
- L358 _private member_ `TArray<TWeakObjectPtr<UActorComponent>> WeakBoundComponents;`
- L360 _private member_ `TArray<TWeakObjectPtr<const UOptimusComponentSource>> WeakComponentSources;`
- L363 _private member_ `TSet<FName> GraphsToRunOnNextTick;` — List of graphs that should be run on the next tick.
- L364 _private member_ `FCriticalSection GraphsToRunOnNextTickLock;`
- L366 _private member_ `FOptimusPersistentBufferPoolPtr BufferPool;`
- L367 _private member_ `FSceneInterface* Scene = nullptr;`
- L370 _private member_ `TWeakInterfacePtr<IOptimusDeformerGeometryReadbackProvider> WeakGeometryReadbackProvider = nullptr;` — Data provider responsible for reading back the final deformed geometry after the deformer runs, only assigned when WITH_EDITORONLY_DATA
- L372 _private member_ `bool bCanBeActive = true;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API OPTIMUSCORE_API`
- L84 _typedef_ `using FOptimusPersistentBufferPoolPtr = TSharedPtr<FOptimusPersistentBufferPool>;`
- L143 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(UActorComponent*, FOptimusComponentBindingResolver, FName ) UCLASS(MinimalAPI, Blueprintable, BlueprintType) class UOptimusDeformerInstanceSettings : public UMeshDeformerInstanceSettings { GENERATED_BODY() UPROPERTY() TWeakObjectPtr<UOptimusDeformer> Deformer; UPROPERTY(EditAnywhere, Category="Deformer|DeformerSettings", EditFixedSize, meta = (DisplayName = "Component Bindings", EditFixedOrder)) TArray<FOptimusDeformerInstanceComponentBinding> Bindings; public: FOptimusComponentBindingResolver ComponentResolver; void InitializeSettings(UOptimusDeformer* InDeformer, UMeshComponent* InPrimaryComponent); void GetComponentBindings(UOptimusDeformer* InDeformer, UMeshComponent* InPrimaryComponent, TArray<UActorComponent*>& OutComponentBindings) const; protected: friend class FOptimusDeformerInstanceComponentBindingCustomization; UOptimusComponentSourceBinding const* GetComponentBindingByName(FName InBindingName) const; };` — Delegate called per non-primary binding during GetComponentBindings to supply an explicit component. If bound and returns non-null, the result bypasses tag/class auto-resolution for that binding.

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusDiagnostic.h` (Public)


#### enum `EOptimusDiagnosticLevel`  
`enum class EOptimusDiagnosticLevel : uint8`  
_L9-15_
- reflection: `UENUM()`
- L11 _public enumerator_ `None`
- L12 _public enumerator_ `Info`
- L13 _public enumerator_ `Warning`
- L14 _public enumerator_ `Error`

#### struct `FOptimusCompilerDiagnostic`  
`struct FOptimusCompilerDiagnostic`  
_L17-43_
- L19 _public prototype_ `FOptimusCompilerDiagnostic() = default;`
- L20 _public prototype_ `FOptimusCompilerDiagnostic(const FOptimusCompilerDiagnostic&) = default;`
- L21 _public prototype_ `FOptimusCompilerDiagnostic& operator=(const FOptimusCompilerDiagnostic&) = default;`
- L24 _public member_ `EOptimusDiagnosticLevel Level = EOptimusDiagnosticLevel::None;` — The severity of the issue.
- L27 _public member_ `FText Message;` — The actual diagnostic message
- L30 _public member_ `int32 Line = INDEX_NONE;` — Line location in source
- L33 _public member_ `int32 ColumnStart = INDEX_NONE;` — Starting column (inclusive)
- L36 _public member_ `int32 ColumnEnd = INDEX_NONE;` — Ending column (inclusive)
- L39 _public member_ `FString AbsoluteFilePath;` — Absolute path to file associated with this diagnostic
- L42 _public member_ `TWeakObjectPtr<const UObject> Object;` — UObject associated with this diagnostic

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusExecutionDomain.h` (Public)


#### enum `EOptimusExecutionDomainType`  
`enum class EOptimusExecutionDomainType`  
_L12-16_
- reflection: `UENUM()`
- L14 _public enumerator_ `DomainName = 0`
- L15 _public enumerator_ `Expression = 1`

#### struct `FOptimusExecutionDomain`  
`struct FOptimusExecutionDomain`  
_L23-54_
- reflection: `USTRUCT()`
- desc: A struct to hold onto a single-level domain for controlling a kernel's execution domain. The reason it's in a struct is so that we can apply a property panel customization for it to make it easier to select from a pre-defined list of execution domains.
- L27 _public prototype_ `FOptimusExecutionDomain() = default;`
- L28 _public function_ `FOptimusExecutionDomain(FName InExecutionDomainName) : Type(EOptimusExecutionDomainType::DomainName), Name(InExecutionDomainName)`
- L32 _public function_ `FOptimusExecutionDomain(const FString& InExpression) : Type(EOptimusExecutionDomainType::Expression), Expression(InExpression)`
- L37 _public prototype_ `FString AsExpression() const;`
- L39 _public prototype_ `bool IsDefined() const;`
- L43 _private member_ `EOptimusExecutionDomainType Type = EOptimusExecutionDomainType::DomainName;` — `UPROPERTY(EditAnywhere, Category = Domain)`
- L47 _private member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = Domain)` — The name of the execution domain that this kernel operates on.
- L50 _private member_ `FString Expression;` — `UPROPERTY(EditAnywhere, Category = Domain)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusExpressionEvaluator.h` (Public)


#### struct `Optimus::Expression::FParseLocation`  
`struct FParseLocation`  
_L16-36_
- L18 _public prototype_ `FParseLocation() = default;`
- L19 _public function_ `FParseLocation(int32 InStart, int32 InEndLocation) : Start(InStart), End(InEndLocation)`
- L23 _public function_ `FParseLocation(FStringView InParseRange, const TCHAR* InParseStart) : Start(static_cast<int32>(InParseRange.begin() - InParseStart)), End(static_cast<int32>(InParseRange.end() - InParseStart))`
- L29 _public function_ `FParseLocation Join(const FParseLocation& InLocation) const` — Merge two parse locations and return a new one
- L34 _public member_ `const int32 Start = INDEX_NONE;`
- L35 _public member_ `const int32 End = INDEX_NONE;`

#### struct `Optimus::Expression::FParseError`  
`struct FParseError`  
_L38-51_
- L40 _public prototype_ `FParseError() = default;`
- L41 _public function_ `FParseError(FString&& InMessage, FParseLocation InLocation) : Message(MoveTemp(InMessage)), Location(InLocation)`
- L47 _public member_ `const FString Message{};` — The human-readable parsing error
- L50 _public member_ `const FParseLocation Location{};` — The parse location where the error took place.

#### struct `Optimus::Expression::FExpressionObject`  
`struct FExpressionObject`  
_L53-88_
- L55 _public prototype_ `FString ToString() const;`
- L58 _public prototype_ `TSet<FName> GetUsedConstants() const;` — Returns all named constants used by this expression
- L60 _public prototype_ `TOptional<FName> GetAsSingleConstant() const;`
- L62 _public prototype_ `void Load(FArchive& Ar);`
- L63 _public prototype_ `void Save(FArchive& Ar) const;`
- L86 _private typedef_ `using OpElement = TVariant<EOperator, FName , FFunctionRef, float>;`
- L87 _private member_ `TArray<OpElement, TInlineAllocator<8>> Expression;`

#### enum `Optimus::Expression::FExpressionObject::EOperator`  
`enum class EOperator : int32`  
_L67-77_
- L69 _public enumerator_ `Negate` — Negation operator.
- L70 _public enumerator_ `Add` — Add last two values on stack and add the result to the stack.
- L71 _public enumerator_ `Subtract` — Same but subtract
- L72 _public enumerator_ `Multiply` — Same but multiply
- L73 _public enumerator_ `Divide` — Same but divide (div-by-zero returns zero)
- L74 _public enumerator_ `Modulo` — Same but modulo (mod-by-zero returns zero)
- L75 _public enumerator_ `Power` — Raise to power
- L76 _public enumerator_ `FloorDivide` — Divide and round the result down

#### struct `Optimus::Expression::FExpressionObject::FFunctionRef`  
`struct FFunctionRef`  
_L79-83_
- L81 _public function_ `FFunctionRef(int32 InIndex) : Index(InIndex)`
- L82 _public member_ `int32 Index;`

#### class `Optimus::Expression::FEngine`  
`class FEngine`  
_L117-240_
- L122 _public prototype_ `FParseResult Parse( FStringView InExpression, TFunction<TOptional<float>(FName InConstantName)> InConstantEvaluator = {} ) const;` — Parse an expression and either receive an error or a expression execution object that matches this evaluator.
- L131 _public prototype_ `float Execute( const FExpressionObject& InExpressionObject, TFunctionRef<TOptional<float>(FName InConstantName)> InConstantEvaluator ) const;` — Executes the given expression object. \param InExpressionObject The parsed expression object to evaluate. \param InConstantEvaluator A function that returns the value of a given constant, if it's known, or none otherwise.
- L139 _public prototype_ `TOptional<float> Evaluate( FStringView InExpression, TFunctionRef<TOptional<float>(FName InConstantName)> InConstantEvaluator ) const;` — Evaluate an expression directly and returns the result. If the expression is incorrectly formed, then the optional return value holds nothing.
- L146 _public prototype_ `TOptional<FParseError> Verify( FStringView InExpression, TFunction<TOptional<float>(FName InConstantName)> InConstantEvaluator = {} ) const;` — Verify an expression. Does not check for variable validity, only that the expression can be evaluated
- L168 _private typedef_ `using FToken = TVariant<EOperatorToken, FName, float>;`
- L204 _private prototype_ `static FTokenParseResult ParseFloat( FStringView& InOutParseRange, FStringView InExpression );` — Parse a floating point value and return the result (or error). Same semantics apply as with ParseToken.
- L212 _private prototype_ `static FTokenParseResult ParseIdentifier( FStringView& InOutParseRange, FStringView InExpression );` — Parse a constant reference and return the result (or error). Same semantics apply as with ParseToken.
- L222 _private prototype_ `static FTokenParseResult ParseToken( FStringView& InOutParseRange, FStringView InExpression );` — Parse a single token from the beginning of the range, returning either the token or an error, if one was encountered. If the token was successfully parsed, then the given string view range gets updated with the new starting point at the end of the token just parsed
- L228 _private prototype_ `static FString TokenToString( const FToken& InToken );` — Helper function to get a text version of a token.
- L234 _private typedef_ `using FunctionType = TFunction<float(TArrayView<const float>)>;`

#### enum `Optimus::Expression::FEngine::EOperatorToken`  
`enum class EOperatorToken`  
_L152-167_
- L154 _public enumerator_ `Negate` — Placeholder for when constructing the op stack. Gets converted to (0 - V)
- L155 _public enumerator_ `Add` — '+'
- L156 _public enumerator_ `Subtract` — '-'
- L157 _public enumerator_ `Multiply` — '*'
- L158 _public enumerator_ `Divide` — '/'
- L159 _public enumerator_ `Modulo` — '%'
- L160 _public enumerator_ `Power` — '**'
- L161 _public enumerator_ `FloorDivide` — '//'
- L162 _public enumerator_ `ParenOpen` — '('
- L163 _public enumerator_ `ParenClose` — ')'
- L164 _public enumerator_ `Comma` — ','
- L166 _public enumerator_ `Max` — Must be last

#### struct `Optimus::Expression::FEngine::FTokenParseResult`  
`struct FTokenParseResult`  
_L170-199_
- L172 _public prototype_ `FTokenParseResult() = default;`
- L174 _public function_ `FTokenParseResult(FToken&& InToken, FStringView InTokenRange, const TCHAR* InExpression) : Result(TInPlaceType<FToken>(), MoveTemp(InToken)), Location(InTokenRange, InExpression)`
- L179 _public function_ `FTokenParseResult(FString&& InError, FStringView InTokenRange, const TCHAR* InExpression) : Result(TInPlaceType<FString>(), MoveTemp(InError)), Location(InTokenRange, InExpression)`
- L184 _public function_ `bool IsError() const`
- L185 _public function_ `bool IsToken() const`
- L187 _public function_ `const FToken& GetToken() const`
- L192 _public function_ `FParseError GetParseError()`
- L197 _public member_ `TVariant<FString, FToken> Result;`
- L198 _public member_ `FParseLocation Location{};`

#### struct `Optimus::Expression::FEngine::FFunctionInfo`  
`struct FFunctionInfo`  
_L235-239_
- L237 _public member_ `int32 ArgumentCount;`
- L238 _public member_ `FunctionType FunctionPtr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OPTIMUSCORE_API`
- L13 _namespace_ `namespace Optimus`
- L13 _namespace_ `namespace Expression` (scope `Optimus`)
- L90 _typedef_ `using FParseResult = TVariant<FExpressionObject, FParseError>;` (scope `Optimus::Expression`)
- L245 _function_ `static FArchive& operator<<(FArchive& Ar, Optimus::Expression::FExpressionObject& InObject)`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusFunctionNodeGraph.h` (Public)


#### struct `FOptimusFunctionGraphIdentifier`  
`struct FOptimusFunctionGraphIdentifier`  
_L17-30_
- reflection: `USTRUCT()`
- L22 _public member_ `TObjectPtr<UOptimusDeformer> Asset;` — `UPROPERTY()`
- L25 _public member_ `FGuid Guid;` — `UPROPERTY()`
- L27 _public prototype_ `UOptimusFunctionNodeGraph* Resolve();`
- L29 _public prototype_ `bool operator==(const FOptimusFunctionGraphIdentifier& InOtherFunctionGraph) const = default;`

#### class `UOptimusFunctionNodeGraph`  
`class UOptimusFunctionNodeGraph : public UOptimusNodeSubGraph`  
_L37-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOptimusNodeSubGraph`
- L43 _public member_ `static FName AccessSpecifierPublicName;`
- L44 _public member_ `static FName AccessSpecifierPrivateName;`
- L46 _public prototype_ `UOptimusFunctionNodeGraph();`
- L47 _public prototype_ `void PostLoad() override;`
- L50 _public prototype_ `FString GetNodeName() const;` — The name to give the node based off of this graph
- L52 _public prototype_ `void Init();`
- L53 _public prototype_ `FOptimusFunctionGraphIdentifier GetGraphIdentifier() const;`
- L57 _public member_ `FName Category = UOptimusNode::CategoryName::Deformers;` — `UPROPERTY(EditAnywhere, Category=Settings)` — The category of the node based of of this graph for listing purposes
- L60 _public member_ `FName AccessSpecifier = AccessSpecifierPrivateName;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(GetOptions="GetAccessSpecifierOptions"))`
- L63 _public prototype_ `TArray<FName> GetAccessSpecifierOptions() const;` — `UFUNCTION()`
- L65 _public prototype_ `FOptimusFunctionNodeGraphHeaderWithGuid GetHeaderWithGuid() const;`
- L66 _public prototype_ `FGuid GetGuid() const;`
- L70 _public prototype_ `static FGuid GetGuidForGraphWithoutGuid(TSoftObjectPtr<UOptimusFunctionNodeGraph> InGraph);` — Used for PostLoad fixup to ensure function references hold on to the same Guid that the graph would get when it calls PostLoad()
- L75 _protected prototype_ `bool CanEditChange(const FProperty* InProperty) const override;` — UObject override
- L79 _protected member_ `FGuid Guid;` — `UPROPERTY(VisibleAnywhere, Category=Debug, AdvancedDisplay)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusFunctionNodeGraphHeader.h` (Public)


#### struct `FOptimusFunctionNodeGraphHeader`  
`struct FOptimusFunctionNodeGraphHeader`  
_L13-25_
- reflection: `USTRUCT()`
- L18 _public member_ `TSoftObjectPtr<UOptimusFunctionNodeGraph> GraphPath;` — `UPROPERTY()`
- L21 _public member_ `FName FunctionName;` — `UPROPERTY()`
- L24 _public member_ `FName Category;` — `UPROPERTY()`

#### struct `FOptimusFunctionNodeGraphHeaderArray`  
`struct FOptimusFunctionNodeGraphHeaderArray`  
_L28-34_
- reflection: `USTRUCT()`
- L33 _public member_ `TArray<FOptimusFunctionNodeGraphHeader> Headers;` — `UPROPERTY()`

#### struct `FOptimusFunctionReferenceNodeSet`  
`struct FOptimusFunctionReferenceNodeSet`  
_L37-43_
- reflection: `USTRUCT()`
- L42 _public member_ `TSet<TSoftObjectPtr<UOptimusNode_FunctionReference>> Nodes;` — `UPROPERTY()`

#### struct `FOptimusFunctionReferenceData`  
`struct FOptimusFunctionReferenceData`  
_L46-54_
- reflection: `USTRUCT()`
- L53 _public member_ `TMap<FSoftObjectPath, FOptimusFunctionReferenceNodeSet> FunctionReferences;` — `UPROPERTY()` — Group function reference nodes by function node graph path using FSoftObjectPath instead of TSoftObjectPtr such that ExportText(...) is deterministic

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusFunctionNodeGraphHeaderWithGuid.h` (Public)


#### struct `FOptimusFunctionNodeGraphHeaderWithGuid`  
`struct FOptimusFunctionNodeGraphHeaderWithGuid`  
_L12-24_
- reflection: `USTRUCT()`
- L17 _public member_ `FGuid FunctionGraphGuid;` — `UPROPERTY()`
- L20 _public member_ `FName FunctionName;` — `UPROPERTY()`
- L23 _public member_ `FName Category;` — `UPROPERTY()`

#### struct `FOptimusFunctionNodeGraphHeaderWithGuidArray`  
`struct FOptimusFunctionNodeGraphHeaderWithGuidArray`  
_L27-33_
- reflection: `USTRUCT()`
- L32 _public member_ `TArray<FOptimusFunctionNodeGraphHeaderWithGuid> Headers;` — `UPROPERTY()`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusHelpers.h` (Public)


#### struct `Optimus::FUniqueNameGenerator`  
`struct FUniqueNameGenerator`  
_L61-69_
- desc: Given an object scope, generate names that is not only unique within the scope, but also unique among all names generated before. Note: It uses GetUniqueNameForScope so using the same scope object and the same input name does not guarantee the same output name
- L63 _public prototype_ `explicit FUniqueNameGenerator(UObject* InScopeObject);`
- L64 _public prototype_ `FName GetUniqueName(FName InName);`
- L67 _private member_ `UObject* ScopeObject = nullptr;`
- L68 _private member_ `TArray<FName> GeneratedName;`

#### class `Optimus::FBinaryObjectReader`  
`class FBinaryObjectReader : public FObjectReader`  
_L73-83_
- inherits: `FObjectReader`
- desc: A small helper class to enable binary reads on an archive, since the FObjectReader::Serialize(TArray<uint8>& InBytes) constructor is protected
- L76 _public function_ `FBinaryObjectReader(UObject* Obj, const TArray<uint8>& InBytes)`

#### class `Optimus::FBinaryObjectWriter`  
`class FBinaryObjectWriter : public FObjectWriter`  
_L85-94_
- inherits: `FObjectWriter`
- L88 _public function_ `FBinaryObjectWriter(UObject* Obj, TArray<uint8>& OutBytes) : FObjectWriter(OutBytes)`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace Optimus`
- L31 _function_ `template<typename T> T* FindObjectInPackageOrGlobal(const FString& InObjectPath)` (scope `Optimus`) — Attempts to find an object, first within a specific package, if the dot prefix points to a known package, otherwise fall back to searching globally.
- L54 _prototype_ `FName GetUniqueNameForScope(UObject *InScopeObj, FName InName);` (scope `Optimus`) — Given an object scope, ensure that the given name is unique within that scope. If the name is already unique, it will be returned unchanged.
- L96 _prototype_ `FName GetSanitizedNameForHlsl(FName InName);` (scope `Optimus`)
- L98 _function_ `inline FMatrix44f ConvertFTransformToFMatrix44f(const FTransform& InTransform)` (scope `Optimus`)
- L103 _prototype_ `const void ConvertFTransformToFMatrix3x4(const FTransform& InTransform, FShaderValueContainerView OutShaderValue);` (scope `Optimus`)
- L105 _prototype_ `bool RenameObject(UObject* InObjectToRename, const TCHAR* InNewName, UObject* InNewOuter);` (scope `Optimus`)
- L108 _prototype_ `void RemoveObject(UObject* InObjectToRemove);` (scope `Optimus`) — Use this function to remove objects during postload safely
- L112 _prototype_ `TArray<UClass*> GetClassObjectsInPackage(UPackage* InPackage);` (scope `Optimus`) — Our generated classes are parented to the package, this is a utility function to collect them
- L116 _prototype_ `FName GetTypeName(UScriptStruct* InStruct, bool bInShouldGetUniqueNameForUserDefinedStruct = true);` (scope `Optimus`) — Return the unique type name for registry and kernel code generation if the bInShouldGetUniqueNameForUserDefinedStruct = true Otherise, it returns the friendly name for user-facing shader text display
- L120 _prototype_ `FName GetTypeName(const FAssetData& InStructAsset);` (scope `Optimus`) — Return the unique type name for registry and kernel code generation. Similar to the UScriptStruct version (with bInShouldGetUniqueNameForUserDefinedStruct true) but doesn't require loading the asset.
- L123 _prototype_ `FText GetTypeDisplayName(UScriptStruct* InStruct);` (scope `Optimus`) — Return the display name for the struct to be shown in type pickers
- L126 _prototype_ `FName GetMemberPropertyShaderName(UScriptStruct* InStruct, const FProperty* InMemberProperty);` (scope `Optimus`) — Helper function to remove guids from member property names for user defined structs
- L129 _prototype_ `void ConvertObjectPathToShaderFilePath(FString& InOutPath);` (scope `Optimus`) — Helpers to convert UObject path to a virtual shader paths.
- L131 _prototype_ `bool ConvertShaderFilePathToObjectPath(FString& InOutPath);` (scope `Optimus`) — Helpers to convert a virtual shader path back to a UObject path. Returns false if the virtual shader path wasn't recognized as a UObject path.
- L133 _prototype_ `FString GetCookedKernelSource( const FString& InObjectPathName, const FString& InShaderSource, const FString& InKernelName, FIntVector InGroupSize, const TCHAR* InReadNumThreadsPerInvocationFunctionName, const TCHAR* InReadThreadIndexOffsetFunctionName, bool bInIsUnifiedDispatch );` (scope `Optimus`)
- L143 _prototype_ `const TCHAR* GetKernelInternalNamespaceName();` (scope `Optimus`)
- L145 _prototype_ `Expression::FParseResult ParseExecutionDomainExpression( const FString& InExpression, TWeakObjectPtr<const UOptimusComponentSource> InComponentSource );` (scope `Optimus`)
- L150 _prototype_ `TVariant<bool, FText> IsExecutionDomainUnifiedDispatchOnly( const FString& InExpression, TWeakObjectPtr<const UOptimusComponentSource> InComponentSource );` (scope `Optimus`)
- L155 _prototype_ `bool EvaluateExecutionDomainExpressionParseResult( const TVariant<Expression::FExpressionObject, Expression::FParseError>& InParseResult, TWeakObjectPtr<const UOptimusComponentSource> InComponentSource, TWeakObjectPtr<const UActorComponent> InWeakComponent, TArray<int32>& OutInvocationThreadCount );` (scope `Optimus`)
- L162 _prototype_ `bool FindMovedItemInNameArray(const TArray<FName>& Old, const TArray<FName>& New, FName& OutSubjectName, FName& OutNextName);` (scope `Optimus`)
- L164 _prototype_ `FName GenerateUniqueNameFromExistingNames(FName InBaseName, const TArray<FName>& InExistingNames);` (scope `Optimus`)
- L166 _prototype_ `FString MakeUniqueValueName(const FString& InValueName, int32 InUniqueIndex);` (scope `Optimus`)
- L167 _prototype_ `FString ExtractSourceValueName(const FString& InUniqueValueName);` (scope `Optimus`)
- L169 _prototype_ `bool IsSkinWeightProfileAvailable(const FSkeletalMeshLODRenderData& InLODRenderData, FName InSkinWeightProfile);` (scope `Optimus`)
- L171 _prototype_ `void RequestSkinWeightProfileForDeformer(USkeletalMeshComponent* InSkeletalMeshComponent, FName InSkinWeightProfile, TOptional<int32> InLOD = {});` (scope `Optimus`)

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusKernelSource.h` (Public)


#### class `UOptimusKernelSource`  
`class UOptimusKernelSource : public UComputeKernelSource`  
_L9-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UComputeKernelSource`
- L16 _public function_ `void SetSource(FString const& InSource)`
- L22 _public function_ `FString GetSource() const override`
- L32 _protected member_ `FString Source;` — `UPROPERTY()`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusNode.h` (Public)


#### class `UOptimusNode`  
`class UOptimusNode : public UObject`  
_L27-474_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L49 _public prototype_ `UOptimusNode();`
- L50 _public prototype_ `virtual ~UOptimusNode();`
- L56 _public prototype_ `virtual FName GetNodeCategory() const PURE_VIRTUAL(, return NAME_None;);` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Returns the node class category. This is used for categorizing the node for display. @return The node class category.
- L59 _public function_ `virtual bool CanUserDeleteNode() const` — Returns true if the node can be deleted by the user
- L62 _public function_ `virtual void RecreatePinsFromPinDefinitions()` — Recreate the pins from the definition
- L65 _public function_ `virtual void RenamePinFromPinDefinition(FName InOld, FName InNew)` — Rename the pin from the definition
- L68 _public function_ `virtual void UpdateDisplayNameFromDataInterface()` — Update the display name
- L75 _public prototype_ `FName GetNodeName() const;` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Returns the node class name. This name is immutable for the given node class. @return The node class name.
- L82 _public prototype_ `virtual FText GetDisplayName() const;` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Returns the display name to use on the graphical node in the graph editor. @return The display name to show to the user.
- L89 _public prototype_ `bool SetDisplayName(FText InDisplayName);` — Set the display name for this node. @param InDisplayName The display name to use. Can not be empty. @return true if the call was successful and the node name updated.
- L95 _public prototype_ `virtual FText GetTooltipText() const;` — Returns the tool tip. @return The tool tip to show to the user.
- L103 _public prototype_ `bool SetGraphPosition(const FVector2D& InPosition);` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Sets the position in the graph UI that the node should be shown at. @param InPosition The coordinates of the node's position. @return true if setting the position was successful.
- L110 _public function_ `FVector2D GetGraphPosition() const` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Returns the position in the graph UI where the node is shown. @return The coordinates of the node's position.
- L117 _public prototype_ `FString GetNodePath() const;` — Returns the absolute path of the node. This can be passed to this graph collection root's IOptimusPathResolver interface to resolve to a node object. @return The absolute path of this node, rooted within the deformer.
- L120 _public prototype_ `UOptimusNodeGraph *GetOwningGraph() const;` — Returns the owning node graph of this node.
- L123 _public function_ `TArrayView<UOptimusNodePin* const> GetPins() const` — Returns the list of all the pins on this node
- L126 _public prototype_ `UOptimusNodePin* GetPinByName(const FName& PinName) const;` — Return the pin with a specific name
- L129 _public prototype_ `TArray<UOptimusNodePin*> GetPinsByDirection(EOptimusNodePinDirection InDirection, bool bInRecursive) const;` — Returns the list of pins on this node filtered by direction
- L139 _public prototype_ `bool CanConnectPinToPin( const UOptimusNodePin& InThisNodesPin, const UOptimusNodePin& InOtherNodesPin, FString* OutReason = nullptr ) const;` — Preliminary check for whether valid connection can be made between two existing pins. Can be overridden by derived nodes to add their own additional checks. @param InThisNodesPin The pin on this node that about to be connected @param InOtherNodesPin The pin that is about to be connect to this node @param OutReason The reason that the connection is cannot be made if it is invalid @return true if the other Pin can be connected to the specified side of the node.
- L153 _public prototype_ `bool CanConnectPinToNode( const UOptimusNodePin* InOtherPin, EOptimusNodePinDirection InConnectionDirection, FString* OutReason = nullptr ) const;` — Preliminary check for whether valid connection can be made between an existing pin and a potentially existing pin on this node. @param InOtherPin The pin that is about to be connect to this node @param InConnectionDirection The input/output side of the node to connect @param OutReason The reason that the connection is cannot be made if it is invalid @return true if the other Pin can be connected to the specified side of the node.
- L163 _public function_ `EOptimusDiagnosticLevel GetDiagnosticLevel() const` — Returns the node's diagnostic level (e.g. error state). For a node, only None, Warning, and Error are relevant.
- L168 _public prototype_ `void SetDiagnosticLevel(EOptimusDiagnosticLevel InDiagnosticLevel);` — Sets the node diagnostic level (e.g. error state).
- L174 _public prototype_ `UOptimusNodePin* FindPin(const FStringView InPinPath) const;` — Find the pin associated with the given dot-separated pin path. @param InPinPath The path of the pin. @return The pin object, if found, otherwise nullptr.
- L177 _public prototype_ `UOptimusNodePin* FindPinFromPath(const TArray<FName>& InPinPath) const;` — Find the pin from the given path array.
- L185 _public prototype_ `UOptimusNodePin* FindPinFromProperty( const FProperty* InRootProperty, const FProperty* InSubProperty ) const;` — Find the pin associated with the given FProperty object(s). @param InRootProperty The property representing the pin root we're interested in. @param InSubProperty The property representing the actual pin the value changed on. @return The pin object, if found, otherwise nullptr.
- L195 _public prototype_ `static TArray<UClass*> GetAllNodeClasses();` — Returns the class of all non-deprecated UOptimusNodeBase nodes that are defined, in no particular order. @return List of all classes that derive from UOptimusNodeBase.
- L201 _public prototype_ `void PostCreateNode();` — Called just after the node is created, either via direct creation or deletion undo. By default it creates the pins representing connectable properties.
- L207 _public prototype_ `void PostDeserializeNode();` — Called just after the node is deserialized, either via loading or pasting. It does not recreate the pins, instead it only initializes transient data.
- L210 _public prototype_ `void Serialize(FArchive& Ar) override;` — == UObject overrides
- L214 _public prototype_ `void PostLoad() override final;` — Using "final" here to make sure all derive nodes have InitializeTransientData() automatically called on them during PostLoad(), so please use PostLoadNodeSpecificData instead for any PostLoad fix-ups
- L217 _public prototype_ `virtual void PostLoadNodeSpecificData();` — Derived nodes should override this function for any PostLoad fix-ups
- L219 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L220 _public function_ `bool IsCreatedFromUI() const`
- L247 _protected prototype_ `static FName GetAvailablePinNameStable(const UObject* InNodeOrPin, FName InName);` — Returns a unique name for pin. If given the same pins to compare to, the output name will always be the same, unlike Optimus::GetUniqueNameForScope, which gives a different name each time it is called, use this function if pin names are generated during an action instead of prior to an action. Though ideally there should be only one way to generate pin names
- L250 _protected prototype_ `UOptimusActionStack* GetActionStack() const;` — Return the action stack for this node.
- L253 _protected prototype_ `virtual void ConstructNode();` — Called when the node is being constructed
- L256 _protected prototype_ `virtual void InitializeTransientData();` — Allows the node to initialize any transient data that can be derived from serialized properties
- L259 _protected function_ `virtual void InitializePinsDisplayName()` — Allows the node to initialize all the pins display names from the definitions
- L261 _protected function_ `virtual bool ValidateConnection( const UOptimusNodePin& InThisNodesPin, const UOptimusNodePin& InOtherNodesPin, FString* OutReason ) const`
- L274 _protected function_ `virtual TOptional<FText> ValidateForCompile(const FOptimusPinTraversalContext& InContext) const` — Optional: Perform local node validation for compilation. If failed, return the reason as a part of the optional return value. If success return an empty optional object.
- L282 _protected function_ `virtual void PreDuplicateRequirementActions( const UOptimusNodeGraph* InTargetGraph, FOptimusCompoundAction *InCompoundAction)` — Called prior to duplicate to allow the node to add its own graph requirements to to the list of actions being performed.
- L286 _protected prototype_ `virtual void ExportState(FArchive& Ar) const;`
- L287 _protected prototype_ `virtual void ImportState(FArchive& Ar);`
- L289 _protected prototype_ `void EnableDynamicPins();`
- L291 _protected function_ `virtual void OnDataTypeChanged(FName InTypeName)`
- L293 _protected prototype_ `UOptimusNodePin* AddPin( FName InName, EOptimusNodePinDirection InDirection, const FOptimusDataDomain& InDataDomain, FOptimusDataTypeRef InDataType, UOptimusNodePin* InBeforePin = nullptr, UOptimusNodePin* InGroupingPin = nullptr );`
- L303 _protected prototype_ `UOptimusNodePin* AddPin( const FOptimusParameterBinding& InBinding, EOptimusNodePinDirection InDirection, UOptimusNodePin* InBeforePin = nullptr );` — Add a new pin based on a parameter binding definition. Only allowed for top-level pins.
- L310 _protected prototype_ `UOptimusNodePin* AddPinDirect( FName InName, EOptimusNodePinDirection InDirection, const FOptimusDataDomain& InDataDomain, FOptimusDataTypeRef InDataType, UOptimusNodePin* InBeforePin = nullptr, UOptimusNodePin* InParentPin = nullptr );` — Create a pin and add it to the node in the location specified.
- L320 _protected prototype_ `UOptimusNodePin* AddPinDirect( const FOptimusParameterBinding& InBinding, EOptimusNodePinDirection InDirection, UOptimusNodePin* InBeforePin = nullptr );` — Add a new pin based on a parameter binding definition. Only allowed for top-level pins.
- L328 _protected prototype_ `UOptimusNodePin* AddGroupingPin( FName InName, EOptimusNodePinDirection InDirection, UOptimusNodePin* InBeforePin = nullptr );` — Add a new grouping pin. This is a pin that takes no connections but is shown as collapsible in the node UI.
- L334 _protected prototype_ `UOptimusNodePin* AddGroupingPinDirect( FName InName, EOptimusNodePinDirection InDirection, UOptimusNodePin* InBeforePin = nullptr );`
- L341 _protected prototype_ `bool RemovePin( UOptimusNodePin* InPin );` — Remove a pin.
- L346 _protected prototype_ `bool RemovePinDirect( UOptimusNodePin* InPin );` — Remove the pin with no undo.
- L351 _protected prototype_ `bool MovePin( UOptimusNodePin* InPinToMove, const UOptimusNodePin* InPinBefore );` — Swap two sibling pins
- L356 _protected prototype_ `bool MovePinDirect( UOptimusNodePin* InPinToMove, const UOptimusNodePin* InPinBefore );`
- L361 _protected prototype_ `bool MovePinToGroupPinDirect( UOptimusNodePin* InPinToMove, UOptimusNodePin* InGroupPin );`
- L367 _protected prototype_ `bool SetPinDataType( UOptimusNodePin* InPin, FOptimusDataTypeRef InDataType );` — Set the pin data type.
- L372 _protected prototype_ `bool SetPinDataTypeDirect( UOptimusNodePin* InPin, FOptimusDataTypeRef InDataType );`
- L379 _protected prototype_ `bool SetPinName( UOptimusNodePin* InPin, FName InNewName );` — FIXME: Hoist to public
- L384 _protected prototype_ `bool SetPinNameDirect( UOptimusNodePin* InPin, FName InNewName );`
- L392 _protected prototype_ `bool SetGraphPositionDirect( const FVector2D &InPosition );` — @brief Set a new position of the node in the graph UI. @param InPosition The coordinates of the new position. @return true if the position setting was successful (i.e. the coordinates are valid).
- L397 _protected prototype_ `bool SetPinDataDomain( UOptimusNodePin* InPin, const FOptimusDataDomain& InDataDomain );` — Set the pin's resource context names.
- L402 _protected prototype_ `bool SetPinDataDomainDirect( UOptimusNodePin* InPin, const FOptimusDataDomain& InDataDomain );`
- L407 _protected prototype_ `void SetPinExpanded(const UOptimusNodePin* InPin, bool bInExpanded);`
- L408 _protected prototype_ `bool GetPinExpanded(const UOptimusNodePin* InPin) const;`
- L411 _protected member_ `bool bSendNotifications = true;` — A sentinel to indicate whether sending notifications is allowed.
- L414 _private prototype_ `void InsertPinIntoHierarchy( UOptimusNodePin* InNewPin, UOptimusNodePin* InParentPin, UOptimusNodePin* InInsertBeforePin );`
- L420 _private prototype_ `void Notify( EOptimusGraphNotifyType InNotifyType );`
- L424 _private function_ `bool CanNotify() const`
- L430 _private prototype_ `void CreatePinsFromStructLayout( const UStruct *InStruct, UOptimusNodePin *InParentPin = nullptr );`
- L435 _private prototype_ `UOptimusNodePin* CreatePinFromProperty( EOptimusNodePinDirection InDirection, const FProperty* InProperty, UOptimusNodePin* InParentPin = nullptr );`
- L444 _private member_ `FText DisplayName;` — `UPROPERTY(NonTransactional)` — The display name to show. This is non-transactional because it is controlled by our action system rather than the transacting system for undo.
- L448 _private member_ `FVector2D GraphPosition;` — `UPROPERTY(NonTransactional)` — Node layout data
- L452 _private member_ `TArray<TObjectPtr<UOptimusNodePin> > Pins;` — `UPROPERTY(NonTransactional)` — The list of pins. Non-transactional for the same reason as above.
- L456 _private member_ `TSet<FName> ExpandedPins;` — `UPROPERTY(NonTransactional)` — The list of pins that should be shown as expanded in the graph view.
- L459 _private member_ `EOptimusDiagnosticLevel DiagnosticLevel = EOptimusDiagnosticLevel::None;` — `UPROPERTY()`
- L462 _private member_ `bool bDynamicPins = false;` — Set to true if the node is dynamic and can have pins arbitrarily added.
- L465 _private member_ `bool bConstructingNode = false;` — A sentinel to indicate we're doing node construction.
- L470 _private member_ `bool bCreatedFromUI = false;` — Optionally one can mark this node as created from UI during node creation for the Editor to do special things when the node is spawned
- L473 _private member_ `mutable TMap<TArray<FName>, UOptimusNodePin*> CachedPinLookup;` — Cached pin lookups

#### struct `UOptimusNode::CategoryName`  
`struct CategoryName`  
_L31-38_
- L33 _public member_ `static const FName DataInterfaces;`
- L34 _public member_ `static const FName Deformers;`
- L35 _public member_ `static const FName Resources;`
- L36 _public member_ `static const FName Variables;`
- L37 _public member_ `static const FName Values;`

#### struct `UOptimusNode::PropertyMeta`  
`struct PropertyMeta`  
_L40-47_
- L42 _public member_ `static const FName Category;`
- L43 _public member_ `static const FName Input;`
- L44 _public member_ `static const FName Output;`
- L45 _public member_ `static const FName Resource;`
- L46 _public member_ `static const FName AllowParameters;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusNodeGraph.h` (Public)


#### enum `EOptimusNodeGraphType`  
`enum class EOptimusNodeGraphType`  
_L39-49_
- reflection: `UENUM()`
- desc: The use type of a particular graph
- L42 _public enumerator_ `Setup` — Execution graphs
- L43 _public enumerator_ `Update` — Setup,					  Called once during an actor's setup event
- L44 _public enumerator_ `ExternalTrigger` — Update,					  Called on every tick
- L46 _public enumerator_ `Function` — Storage graphs
- L47 _public enumerator_ `SubGraph` — Function,				  Used to store function graphs
- L48 _public enumerator_ `Transient` — SubGraph,				  Used to store sub-graphs within other graphs

#### enum `EOptimusNodePinTraversalDirection`  
`enum class EOptimusNodePinTraversalDirection`  
_L51-56_
- L53 _public enumerator_ `Default`
- L54 _public enumerator_ `Upstream`
- L55 _public enumerator_ `Downstream`

#### class `UOptimusNodeGraph`  
`class UOptimusNodeGraph : public UObject, public IOptimusNodeGraphCollectionOwner`  
_L70-606_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IOptimusNodeGraphCollectionOwner`
- L78 _public member_ `static const FName SetupGraphName;` — Reserved names
- L79 _public member_ `static const FName UpdateGraphName;`
- L80 _public member_ `static const TCHAR* LibraryRoot;`
- L81 _public member_ `static const FName DefaultSubGraphName;`
- L82 _public member_ `static const FName DefaultSubGraphRefNodeName;`
- L85 _public prototype_ `static FString GetFunctionGraphCollectionPath(const FString& InFunctionName);` — Function Graphs are addressed in a special way
- L92 _public prototype_ `void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;` — Check if the duplication took place at the asset level if so, we have to recreate all constant/attribute nodes such that their class pointers don't point to classes in the source asset. This can happen because generated class in the source package/asset are not duplicated automatically to the new package/asset
- L94 _public prototype_ `void PostLoad() override;`
- L96 _public prototype_ `UOptimusNodeGraph *GetParentGraph() const;`
- L99 _public prototype_ `static bool IsValidUserGraphName( const FString& InGraphName, FText* OutFailureReason = nullptr );` — Verify if the given name is a valid graph name.
- L104 _public prototype_ `static FString ConstructPath(const FString& GraphPath, const FString& NodeName, const FString& PinPath);`
- L107 _public function_ `EOptimusNodeGraphType GetGraphType() const` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L110 _public function_ `bool IsExecutionGraph() const` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L116 _public function_ `bool IsFunctionGraph() const` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L121 _public prototype_ `bool IsReadOnly() const;`
- L124 _public prototype_ `int32 GetGraphIndex() const;` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L130 _public prototype_ `FOptimusGraphNotifyDelegate &GetNotifyDelegate();` — @brief Returns the modify event object that can listened to in case there are changes to the graph that need to be reacted to. @return The node core event object.
- L136 _public prototype_ `UOptimusNode* AddNode( const TSubclassOf<UOptimusNode> InNodeClass, const FVector2D& InPosition );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — TODO: Add magic connection from a pin.
- L142 _public prototype_ `UOptimusNode* AddValueNode( FOptimusDataTypeRef InDataTypeRef, const FVector2D& InPosition );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L148 _public prototype_ `UOptimusNode* AddDataInterfaceNode( const TSubclassOf<UOptimusComputeDataInterface> InDataInterfaceClass, const FVector2D& InPosition );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L154 _public prototype_ `TArray<UOptimusNode*> AddLoopTerminalNodes( const FVector2D& InPosition );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L159 _public prototype_ `UOptimusNode* AddCommentNode( const FVector2D& InPosition, const FVector2D& InSize, const FLinearColor& InColor );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L165 _public prototype_ `UOptimusNode* AddCommentNode( const FVector2D& InPosition, const FVector2D& InSize, const FLinearColor& InColor, bool bCreatedFromUI );`
- L173 _public prototype_ `UOptimusNode* AddFunctionReferenceNode( UOptimusFunctionNodeGraph* InFunctionGraph, const FVector2D& InPosition );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L179 _public prototype_ `UOptimusNode* AddResourceNode( UOptimusResourceDescription* InResourceDesc, const FVector2D& InPosition);` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L184 _public prototype_ `UOptimusNode* AddResourceGetNode( UOptimusResourceDescription *InResourceDesc, const FVector2D& InPosition);` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L189 _public prototype_ `UOptimusNode* AddResourceSetNode( UOptimusResourceDescription* InResourceDesc, const FVector2D& InPosition);` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L194 _public prototype_ `UOptimusNode* AddVariableGetNode( UOptimusVariableDescription* InVariableDesc, const FVector2D& InPosition );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L200 _public prototype_ `UOptimusNode* AddComponentBindingGetNode( UOptimusComponentSourceBinding* InComponentBinding, const FVector2D& InPosition );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L207 _public prototype_ `bool RemoveNode( UOptimusNode* InNode );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L212 _public prototype_ `bool RemoveNodes( const TArray<UOptimusNode*>& InNodes );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L216 _public prototype_ `int32 RemoveNodesAndCount( const TArray<UOptimusNode*>& InNodes );`
- L221 _public prototype_ `UOptimusNode* DuplicateNode( UOptimusNode* InNode, const FVector2D& InPosition );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L229 _public prototype_ `bool DuplicateNodes( const TArray<UOptimusNode*> &InNodes, const FVector2D& InPosition );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Duplicate a collection of nodes from the same graph, using the InPosition position to be the top-left origin of the pasted nodes.
- L233 _public prototype_ `bool DuplicateNodes( const TArray<UOptimusNode*> &InNodes, const FVector2D& InPosition, const FString& InActionName );`
- L240 _public prototype_ `bool AddLink( UOptimusNodePin* InNodeOutputPin, UOptimusNodePin* InNodeInputPin );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L247 _public prototype_ `bool RemoveLink( UOptimusNodePin* InNodeOutputPin, UOptimusNodePin* InNodeInputPin );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — @brief Removes a single link between two nodes. FIXME: Use UOptimusNodeLink instead.
- L253 _public prototype_ `bool RemoveAllLinks( UOptimusNodePin* InNodePin );` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — @brief Removes all links to the given pin, whether it's an input or an output pin.
- L262 _public prototype_ `UOptimusNode* ConvertCustomKernelToFunction(UOptimusNode *InCustomKernel);` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Takes a custom kernel and converts to a packaged function. If the given node is not a custom kernel or cannot be converted, a nullptr is returned.
- L268 _public prototype_ `UOptimusNode* ConvertFunctionToCustomKernel(UOptimusNode *InKernelFunction);` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Takes a kernel function and unpackages to a custom kernel. If the given node is not a kernel function or cannot be converted, a nullptr is returned.
- L275 _public prototype_ `UOptimusNode *CollapseNodesToFunction(const TArray<UOptimusNode*>& InNodes);` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Take a set of nodes and collapse them into a single function, replacing the given nodes with the new function node and returning it. A new function definition is made available as a new Function graph in the package.
- L281 _public prototype_ `UOptimusNode *CollapseNodesToSubGraph(const TArray<UOptimusNode*>& InNodes);` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Take a set of nodes and collapse them into a subgraph, replacing the given nodes with a new subgraph node and returning it.
- L288 _public prototype_ `TArray<UOptimusNode *> ExpandCollapsedNodes(UOptimusNode* InGraphReferenceNode);` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Take a function or subgraph node and expand it in-place, replacing the given function node. The function definition still remains, if a function node was expanded. If a sub-graph was expanded, the sub-graph is deleted.
- L293 _public prototype_ `bool ConvertToFunction(UOptimusNode* InSubGraphNode);` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Take a subgraph node convert it to a function in-place
- L298 _public prototype_ `bool ConvertToSubGraph(UOptimusNode* InFunctionNode);` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Take a function node convert it to a subgraph node in-place
- L304 _public prototype_ `bool IsCustomKernel(UOptimusNode *InNode) const;` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Returns true if the node in question is a custom kernel node that can be converted to a kernel function with ConvertCustomKernelToFunction.
- L310 _public prototype_ `bool IsKernelFunction(UOptimusNode *InNode) const;` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Returns true if the node in question is a kernel function node that can be converted to a custom kernel using ConvertFunctionToCustomKernel.
- L316 _public prototype_ `bool IsFunctionReference(UOptimusNode *InNode) const;` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Returns true if the node in question is a function reference node that can be expanded into a group of nodes using ExpandFunctionToNodes.
- L322 _public prototype_ `bool IsSubGraphReference(UOptimusNode *InNode) const;` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)` — Returns true if the node in question is a function sub-graph node that can be expanded into a group of nodes using ExpandFunctionToNodes.
- L326 _public prototype_ `UOptimusNodePair* GetNodePair(const UOptimusNode* InNode) const;` — Returns the node pair given a IOptimusNodePairProvider
- L330 _public prototype_ `UOptimusNode* GetNodeCounterpart(const UOptimusNode* InNode) const;` — Returns the paired node for the given IOptimusNodePairProvider
- L335 _public prototype_ `TArray<UOptimusNodePin *> GetConnectedPins( const UOptimusNodePin* InNodePin ) const;` — Returns all pins that have a _direct_ connection to this pin. If nothing is connected to this pin, it returns an empty array.
- L342 _public prototype_ `TArray<FOptimusRoutedNodePin> GetConnectedPinsWithRouting( const UOptimusNodePin* InNodePin, const FOptimusPinTraversalContext& InContext ) const;` — See UOptimusNodePin::GetConnectedRoutedPins for information on what this function does.
- L347 _public prototype_ `TArray<FOptimusRoutedNodePin> GetConnectedPinsWithRouting( const UOptimusNodePin* InNodePin, const FOptimusPinTraversalContext& InContext, EOptimusNodePinTraversalDirection Direction ) const;`
- L356 _public prototype_ `TSet<UOptimusComponentSourceBinding*> GetComponentSourceBindingsForPin( const UOptimusNodePin* InNodePin, const FOptimusPinTraversalContext& InContext ) const;` — Get all unique component bindings that lead to this pin. Note that only pins with a zero or single bindings are considered valid. We return all of them however for error messaging.
- L362 _public prototype_ `bool IsPinMutable( const UOptimusNodePin* InNodePin, const FOptimusPinTraversalContext& InContext ) const;` — Check if a pin represents time varying data
- L368 _public prototype_ `bool DoesNodeHaveMutableInput( const UOptimusNode* InNode, const FOptimusPinTraversalContext& InContext ) const;` — Check if a Node has mutable input pins
- L374 _public prototype_ `TSet<FOptimusRoutedConstNode> GetLoopEntryTerminalForPin( const UOptimusNodePin* InNodePin, const FOptimusPinTraversalContext& InContext = {} ) const;` — Gather connected loop entry terminals
- L380 _public prototype_ `TSet<FOptimusRoutedConstNode> GetLoopEntryTerminalForNode( const UOptimusNode* InNode, const FOptimusPinTraversalContext& InContext = {} ) const;` — Gather connected loop entry terminals
- L385 _public prototype_ `TArray<const UOptimusNodeLink *> GetPinLinks(const UOptimusNodePin* InNodePin) const;`
- L391 _public prototype_ `bool DoesLinkFormCycle( const UOptimusNode* InOutputNode, const UOptimusNode* InInputNode) const;` — Check to see if connecting these two nodes will form a graph cycle. @param InOutputNode The node from which the link originates @param InInputNode The node to which the link ends @return True if connecting these two nodes will result in a graph cycle.
- L401 _public prototype_ `bool ConnectAdderPin( IOptimusNodeAdderPinProvider* InTargetNode, const IOptimusNodeAdderPinProvider::FAdderPinAction& InSelectedAction, UOptimusNodePin* InSourcePin );` — Add a new pin to the target node with the type of source pin and connect the source pin to the new pin @param InTargetNode The node to add the pin to, it has to have an adder pin @param InSelectedAction The selected action that defines where the new pin should be added @param InSourcePin The pin to create the new pin and to connect to the new pin @return True if a new pin is created.
- L407 _public function_ `const TArray<UOptimusNode*>& GetAllNodes() const`
- L408 _public function_ `const TArray<UOptimusNodeLink*>& GetAllLinks() const`
- L409 _public function_ `const TArray<UOptimusNodePair*>& GetAllNodePairs() const`
- L411 _public prototype_ `UOptimusActionStack* GetActionStack() const;`
- L414 _public prototype_ `IOptimusNodeGraphCollectionOwner* GetCollectionOwner() const override;` — IOptimusNodeGraphCollectionOwner overrides
- L415 _public prototype_ `IOptimusNodeGraphCollectionOwner* GetCollectionRoot() const override;`
- L416 _public prototype_ `FString GetCollectionPath() const override;`
- L419 _public function_ `const TArray<UOptimusNodeGraph*> &GetGraphs() const override` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L421 _public prototype_ `UOptimusNodeGraph* FindGraphByName(FName InGraphName) const override;`
- L423 _public prototype_ `UOptimusNodeGraph* CreateGraphDirect( EOptimusNodeGraphType InType, FName InName, TOptional<int32> InInsertBefore) override;`
- L427 _public prototype_ `bool AddGraphDirect( UOptimusNodeGraph* InGraph, int32 InInsertBefore) override;`
- L430 _public prototype_ `bool RemoveGraphDirect( UOptimusNodeGraph* InGraph, bool bInDeleteGraph) override;`
- L435 _public prototype_ `bool MoveGraphDirect( UOptimusNodeGraph* InGraph, int32 InInsertBefore) override;` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L440 _public prototype_ `bool RenameGraphDirect( UOptimusNodeGraph* InGraph, const FString& InNewName) override;` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L445 _public prototype_ `bool RenameGraph( UOptimusNodeGraph* InGraph, const FString& InNewName) override;` — `UFUNCTION(BlueprintCallable, Category = OptimusNodeGraph)`
- L453 _public prototype_ `void SetViewLocationAndZoom(const FVector2D& InViewLocation, float InViewZoom);` — Set the graph view location and zoom, to ensure that the view location is stored between sessions and graph switching.
- L457 _public prototype_ `bool GetViewLocationAndZoom(FVector2D& OutViewLocation, float& OutViewZoom) const;` — Returns the graph view location and zoom, if set. If the location has never been set, this function returns false and the resulting out values are left undefined.
- L476 _protected prototype_ `UOptimusNode* CreateNodeDirect( const UClass* InNodeClass, FName InName, TFunction<bool(UOptimusNode*)> InConfigureNodeFunc );` — Direct edit functions. Used by the actions.
- L482 _protected prototype_ `bool AddNodeDirect( UOptimusNode* InNode );`
- L486 _protected prototype_ `void RemoveGraph( UOptimusNodeGraph* InNodeGraph );`
- L491 _protected prototype_ `bool RemoveNodeDirect( UOptimusNode* InNode, bool bFailIfLinks = true);` — Remove a node directly. If a node still has connections this call will fail.
- L495 _protected prototype_ `bool AddNodePairDirect(UOptimusNode* InFirstNode, UOptimusNode* InSecondNode);`
- L497 _protected prototype_ `bool RemoveNodePairDirect(UOptimusNode* InFirstNode, UOptimusNode* InSecondNode);`
- L499 _protected prototype_ `bool AddLinkDirect(UOptimusNodePin* InNodeOutputPin, UOptimusNodePin* InNodeInputPin);`
- L501 _protected prototype_ `bool RemoveLinkDirect(UOptimusNodePin* InNodeOutputPin, UOptimusNodePin* InNodeInputPin);`
- L503 _protected prototype_ `bool RemoveAllLinksToPinDirect(UOptimusNodePin* InNodePin);`
- L505 _protected prototype_ `bool RemoveAllLinksToNodeDirect(UOptimusNode* InNode);`
- L508 _protected function_ `void SetGraphType(EOptimusNodeGraphType InType)` — FIXME: Remove this.
- L513 _protected prototype_ `void Notify(EOptimusGraphNotifyType InNotifyType, UObject *InSubject) const;`
- L514 _protected prototype_ `void GlobalNotify(EOptimusGlobalNotifyType InNotifyType, UObject *InSubject) const;`
- L518 _protected member_ `EOptimusNodeGraphType GraphType = EOptimusNodeGraphType::Transient;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Overview)` — The type of graph this represents.
- L522 _protected member_ `bool bViewLocationSet = false;` — `UPROPERTY()`
- L525 _protected member_ `FVector2D ViewLocation = {0.0, 0.0};` — `UPROPERTY()`
- L528 _protected member_ `float ViewZoom = 0.0f;` — `UPROPERTY()`
- L532 _private prototype_ `IOptimusPathResolver* GetPathResolver() const;`
- L534 _private prototype_ `UOptimusNode* AddNodeInternal( const TSubclassOf<UOptimusNode> InNodeClass, const FVector2D& InPosition, TFunction<void(UOptimusNode*)> InNodeConfigFunc );`
- L540 _private prototype_ `TArray<UOptimusNode*> AddNodePairInternal( const TSubclassOf<UOptimusNode> InNodeClass, const FVector2D& InPosition, TFunction<void(UOptimusNode*)> InFirstNodeConfigFunc, TFunction<void(UOptimusNode*)> InSecondNodeConfigFunc );`
- L547 _private prototype_ `static void GatherRelatedObjects( const TArray<UOptimusNode*>& InNodes, TArray<UOptimusNode*>& OutNodes, TArray<UOptimusNodePair*>& OutNodePairs, TArray<UOptimusNodeSubGraph*>& OutSubGraphs );`
- L554 _private prototype_ `static bool DuplicateSubGraph( UOptimusActionStack* InActionStack, const FString& InGraphOwnerPath, UOptimusNodeSubGraph* InSourceSubGraph, FName InNewGraphName );`
- L561 _private prototype_ `void RemoveNodePairByIndex(int32 NodePairIndex);`
- L563 _private prototype_ `void RemoveLinkByIndex(int32 LinkIndex);`
- L572 _private prototype_ `TArray<int32> GetAllLinkIndexesToNode( const UOptimusNode* InNode, EOptimusNodePinDirection InDirection ) const;` — Returns the indexes of all links that connect to the node. If a direction is specified then only links coming into the node for that direction will be added (e.g. if Input is specified, then only links going into the input pins will be considered). @param InNode The node to retrieve all link connections for. @param InDirection The pins the links should be connected into, or Unknown if not direction is not important. @return A list of indexes into the Links array of links to the given node.
- L578 _private prototype_ `TArray<int32> GetAllLinkIndexesToNode( const UOptimusNode* InNode ) const;`
- L583 _private prototype_ `TArray<int32> GetAllLinkIndexesToPin( const UOptimusNodePin* InNodePin ) const;`
- L587 _private prototype_ `FString ConstructSubGraphPath(const FString& InSubGraphName) const;`
- L588 _private prototype_ `static FString ConstructSubGraphPath(const FString& InGraphOwnerPath, const FString& InSubGraphName);`
- L590 _private prototype_ `void PostLoadReplaceAnimAttributeDataInterfaceNodeWithGenericDataInterfaceNode();`
- L593 _private member_ `TArray<TObjectPtr<UOptimusNode>> Nodes;` — `UPROPERTY(NonTransactional)`
- L597 _private member_ `TArray<TObjectPtr<UOptimusNodeLink>> Links;` — `UPROPERTY(NonTransactional)` — FIXME: Use a map.
- L600 _private member_ `TArray<TObjectPtr<UOptimusNodePair>> NodePairs;` — `UPROPERTY(NonTransactional)`
- L603 _private member_ `TArray<TObjectPtr<UOptimusNodeGraph>> SubGraphs;` — `UPROPERTY(NonTransactional)`
- L605 _private member_ `FOptimusGraphNotifyDelegate GraphNotifyDelegate;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API OPTIMUSCORE_API`
- L58 _namespace_ `namespace Optimus`
- L60 _function_ `static bool IsExecutionGraphType(EOptimusNodeGraphType InGraphType)` (scope `Optimus`)

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusNodeLink.h` (Public)


#### class `UOptimusNodeLink`  
`class UOptimusNodeLink : public UObject`  
_L12-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L17 _public prototype_ `UOptimusNodeLink() = default;`
- L20 _public function_ `UOptimusNodePin* GetNodeOutputPin() const` — Returns the output pin on the node this link connects from.
- L23 _public function_ `UOptimusNodePin* GetNodeInputPin() const` — Returns the input pin on the node that this link connects to.
- L29 _protected member_ `TObjectPtr<UOptimusNodePin> NodeOutputPin;` — `UPROPERTY()`
- L32 _protected member_ `TObjectPtr<UOptimusNodePin> NodeInputPin;` — `UPROPERTY()`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusNodePair.h` (Public)


#### class `UOptimusNodePair`  
`class UOptimusNodePair : public UObject`  
_L14-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L19 _public prototype_ `UOptimusNodePair() = default;`
- L22 _public function_ `UOptimusNode* GetFirst() const` — Returns the output pin on the node this link connects from.
- L25 _public function_ `UOptimusNode* GetSecond() const` — Returns the input pin on the node that this link connects to.
- L27 _public prototype_ `bool Contains(const UOptimusNode* InFirst, const UOptimusNode* InSecond) const;`
- L29 _public prototype_ `bool Contains(const UOptimusNode* InNode) const;`
- L31 _public prototype_ `UOptimusNode* GetNodeCounterpart(const UOptimusNode* InNode) const;`
- L38 _protected member_ `TObjectPtr<UOptimusNode> First;` — `UPROPERTY()`
- L41 _protected member_ `TObjectPtr<UOptimusNode> Second;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusNodePin.h` (Public)


#### enum `EOptimusNodePinStorageType`  
`enum class UE_DEPRECATED(5.1, "Replaced with FOptimusDataDomain") EOptimusNodePinStorageType : uint8`  
_L21-25_
- reflection: `UENUM()`
- desc: Specifies the storage type of the pin data
- L23 _public enumerator_ `Value`
- L24 _public enumerator_ `Resource` — Value,				  Plain value of some type

#### enum `EOptimusNodePinDirection`  
`enum class EOptimusNodePinDirection : uint8`  
_L29-34_
- reflection: `UENUM()`
- L31 _public enumerator_ `Unknown`
- L32 _public enumerator_ `Input`
- L33 _public enumerator_ `Output`

#### class `UOptimusNodePin`  
`class UOptimusNodePin : public UObject`  
_L38-226_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L43 _public prototype_ `UOptimusNodePin() = default;`
- L47 _public function_ `EOptimusNodePinDirection GetDirection() const` — Returns whether this pin is an input or output connection. @return The direction of this pin.
- L50 _public function_ `bool IsGroupingPin() const` — Returns \c true if this pin is a grouping pin.
- L53 _public prototype_ `UOptimusNodePin* GetParentPin();` — Returns the parent pin of this pin, or nullptr if it is the top-most pin.
- L54 _public prototype_ `const UOptimusNodePin* GetParentPin() const;`
- L57 _public prototype_ `UOptimusNodePin* GetNextPin();` — Returns the next sibling of this pin, or nullptr if it is the last pin of its siblings.
- L58 _public prototype_ `const UOptimusNodePin* GetNextPin() const;`
- L61 _public prototype_ `UOptimusNodePin* GetRootPin();` — Returns the root pin of this pin hierarchy.
- L62 _public prototype_ `const UOptimusNodePin* GetRootPin() const;`
- L65 _public prototype_ `UOptimusNode* GetOwningNode() const;` — Returns the owning node of this pin and all its ancestors and children.
- L69 _public prototype_ `TArray<FName> GetPinNamePath() const;` — Returns the array of pin names from the root pin to this pin. Can be used to to easily traverse the pin hierarchy.
- L73 _public prototype_ `FName GetUniqueName() const;` — Returns a unique name for this pin within the namespace of the owning node. E.g: Direction.X
- L76 _public prototype_ `FText GetDisplayName() const;` — Returns a user-friendly display name for this pin
- L79 _public prototype_ `FText GetTooltipText() const;` — Returns a tooltip to use when hovering over the pin in the graph
- L83 _public prototype_ `FString GetPinPath() const;` — Returns the path of the pin from the graph collection owner root. E.g: SetupGraph/LinearBlendSkinning1.Direction.X
- L86 _public prototype_ `bool SetDisplayName(const FName& InDisplayName);` — Set the display name of the node pin
- L89 _public prototype_ `static TArray<FName> GetPinNamePathFromString(const FStringView InPinPathString);` — Returns a pin path from a string. Returns an empty array if string is invalid or empty.
- L92 _public function_ `FOptimusDataTypeHandle GetDataType() const` — Return the registered Optimus data type associated with this pin
- L95 _public function_ `const FOptimusDataDomain& GetDataDomain() const` — Returns the data domain that this pin is expected to cover
- L99 _public prototype_ `TSet<UOptimusComponentSourceBinding*> GetComponentSourceBindings(const FOptimusPinTraversalContext& InContext) const;` — Return all component source bindings that flow into pin.
- L103 _public prototype_ `TSet<UOptimusComponentSourceBinding*> GetComponentSourceBindingsRecursively(const FOptimusPinTraversalContext& InContext) const;` — Return all component source bindings that flow into this input pin and its sub-pins.
- L107 _public prototype_ `bool IsMutable(const FOptimusPinTraversalContext& InContext) const;` — Whether the data presented by the pin can change over time
- L113 _public prototype_ `FProperty *GetPropertyFromPin() const;` — Returns the FProperty object for this pin. This can be used to directly address the node data represented by this pin. Not all pins have an underlying resource so this can return nullptr.
- L116 _public prototype_ `FString GetValueAsString() const;` — Returns the current value of this pin, including sub-values if necessary, as a string.
- L119 _public prototype_ `bool SetValueFromString(const FString& InStringValue);` — Sets the value of this pin from a value string in an undoable fashion.
- L123 _public prototype_ `bool SetValueFromStringDirect(const FString &InStringValue);` — Sets the value of this pin from a value string with no undo (although if a transaction bracket is open, it will receive the modification).
- L127 _public function_ `TArrayView<const TObjectPtr<UOptimusNodePin>> GetSubPins() const` — Returns the sub-pins of this pin. For example for a pin representing the FVector type, this will return pins for the X, Y, and Z components of it (as float values).
- L131 _public prototype_ `TArray<UOptimusNodePin *> GetSubPinsRecursively(bool bInIncludeThisPin = false) const;` — Returns all sub-pins of this pin, recursively. In the returned list, the parent pins are listed before their child pins.
- L136 _public prototype_ `TArray<UOptimusNodePin *> GetConnectedPins() const;` — Returns all pins that have a _direct_ connection to this pin. If nothing is connected to this pin, it returns an empty array.
- L148 _public prototype_ `TArray<FOptimusRoutedNodePin> GetConnectedPinsWithRouting( const FOptimusPinTraversalContext& InContext = {} ) const;` — Returns all pins that are connected to working nodes, traversing fully through any router nodes. This is so that we can get a connection to an actual non-routing, working node. If there are no connections to this pin, it returns an empty array. Any connections that don't lead to a non-routing node are ignored. The routing assumes that we do not go higher up in the graph stack than the level at which we started (i.e. if this is called on a node inside of a sub-graph with an empty traversal context, and the connection leads to a return node and up into the graph that has a reference to that sub-graph, there are no more context levels to peel off and the connection will _not_ be included).
- L157 _public prototype_ `bool CanCannect(const UOptimusNodePin *InOtherPin, FString *OutReason = nullptr) const;` — Ask this pin if it allows a connection from the other pin. @param InOtherPin The other pin to connect to/from @param OutReason An optional string that will contain the reason why the connection cannot be made if this function returns false. @return True if the connection can be made, false otherwise.
- L161 _public prototype_ `void SetIsExpanded(bool bInIsExpanded);` — Set the expansion state of this pin. This is purely driven by the UI and is not an undoable operation. No notifications are sent if the state changes.
- L164 _public prototype_ `bool GetIsExpanded() const;` — Returns the stored expansion state
- L167 _public prototype_ `void PostLoad() override;` — UObject overrides
- L172 _protected prototype_ `void InitializeWithData( EOptimusNodePinDirection InDirection, FOptimusDataDomain InDataDomain, FOptimusDataTypeRef InDataTypeRef );` — Initialize the pin data from the given direction and property.
- L178 _protected prototype_ `void InitializeWithGrouping( EOptimusNodePinDirection InDirection );`
- L182 _protected prototype_ `void AddSubPin( UOptimusNodePin* InSubPin, UOptimusNodePin* InBeforePin = nullptr);`
- L186 _protected prototype_ `void ClearSubPins();`
- L188 _protected prototype_ `bool SetDataType( FOptimusDataTypeRef InDataType );`
- L192 _protected prototype_ `bool SetName( FName InName);`
- L195 _protected prototype_ `void Notify(EOptimusGraphNotifyType InNotifyType) const;`
- L198 _private prototype_ `uint8 *GetPropertyValuePtr() const;`
- L200 _private prototype_ `UOptimusActionStack* GetActionStack() const;`
- L202 _private prototype_ `bool VerifyValue(const FString& InStringValue) const;`
- L205 _private member_ `bool bIsGroupingPin = false;` — `UPROPERTY()`
- L208 _private member_ `EOptimusNodePinDirection Direction = EOptimusNodePinDirection::Unknown;` — `UPROPERTY()`
- L213 _private member_ `EOptimusNodePinStorageType StorageType_DEPRECATED = EOptimusNodePinStorageType::Value;` — `UE_DEPRECATED(5.1, "Use DataDomain")` — `UPROPERTY()`
- L217 _private member_ `FOptimusDataDomain DataDomain;` — `UPROPERTY()`
- L220 _private member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY()`
- L223 _private member_ `TArray<TObjectPtr<UOptimusNodePin>> SubPins;` — `UPROPERTY()`
- L225 _private member_ `FName DisplayName;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusNodeSubGraph.h` (Public)


#### class `UOptimusNodeSubGraph`  
`class UOptimusNodeSubGraph : public UOptimusNodeGraph, public IOptimusParameterBindingProvider`  
_L15-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOptimusNodeGraph,IOptimusParameterBindingProvider`
- L24 _public member_ `static FName GraphDefaultComponentPinName;`
- L25 _public member_ `static FName InputBindingsPropertyName;`
- L26 _public member_ `static FName OutputBindingsPropertyName;`
- L28 _public prototype_ `UOptimusNodeSubGraph();`
- L31 _public prototype_ `FString GetBindingDeclaration(FName BindingName) const override;` — IOptimusParameterBindingProvider
- L32 _public prototype_ `bool GetBindingSupportAtomicCheckBoxVisibility(FName BindingName) const override;`
- L33 _public prototype_ `bool GetBindingSupportReadCheckBoxVisibility(FName BindingName) const override;`
- L34 _public prototype_ `EOptimusDataTypeUsageFlags GetTypeUsageFlags(const FOptimusDataDomain& InDataDomain) const override;`
- L36 _public prototype_ `UOptimusComponentSourceBinding* GetDefaultComponentBinding(const FOptimusPinTraversalContext& InTraversalContext) const;`
- L38 _public prototype_ `UOptimusNode_GraphTerminal* GetTerminalNode(EOptimusTerminalType InTerminalType) const;`
- L40 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingArrayPasted, FName);`
- L41 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingValueChanged, FName);`
- L42 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingArrayItemAdded, FName);`
- L43 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingArrayItemRemoved, FName);`
- L44 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingArrayCleared, FName);`
- L45 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingArrayItemMoved, FName);`
- L47 _public function_ `FOnBindingArrayPasted& GetOnBindingArrayPasted()`
- L48 _public function_ `FOnBindingValueChanged& GetOnBindingValueChanged()`
- L49 _public function_ `FOnBindingArrayItemAdded& GetOnBindingArrayItemAdded()`
- L50 _public function_ `FOnBindingArrayItemRemoved& GetOnBindingArrayItemRemoved()`
- L51 _public function_ `FOnBindingArrayCleared& GetOnBindingArrayCleared()`
- L52 _public function_ `FOnBindingArrayItemMoved& GetOnBindingArrayItemMoved()`
- L56 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject overrides
- L60 _public member_ `FOptimusParameterBindingArray InputBindings;` — `UPROPERTY(EditAnywhere, Category=Bindings, meta=(AllowParameters))`
- L63 _public member_ `FOptimusParameterBindingArray OutputBindings;` — `UPROPERTY(EditAnywhere, Category=Bindings)`
- L69 _private prototype_ `void SanitizeBinding(FOptimusParameterBinding& InOutBinding, FName InOldName, bool bInAllowParameter);`
- L70 _private prototype_ `FName GetSanitizedBindingName(FName InNewName, FName InOldName);`
- L74 _private prototype_ `void PropertyArrayPasted(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L75 _private prototype_ `void PropertyValueChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L76 _private prototype_ `void PropertyArrayItemAdded(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L77 _private prototype_ `void PropertyArrayItemRemoved(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L78 _private prototype_ `void PropertyArrayCleared(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L79 _private prototype_ `void PropertyArrayItemMoved(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L82 _private member_ `FOnBindingArrayPasted OnBindingArrayPastedDelegate;`
- L83 _private member_ `FOnBindingValueChanged OnBindingValueChangedDelegate;`
- L84 _private member_ `FOnBindingArrayItemAdded OnBindingArrayItemAddedDelegate;`
- L85 _private member_ `FOnBindingArrayItemRemoved OnBindingArrayItemRemovedDelegate;`
- L86 _private member_ `FOnBindingArrayCleared OnBindingArrayClearedDelegate;`
- L87 _private member_ `FOnBindingArrayItemMoved OnBindingArrayItemMovedDelegate;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OPTIMUSCORE_API`
- L40 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingArrayPasted, FName);`
- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingValueChanged, FName);`
- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingArrayItemAdded, FName);`
- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingArrayItemRemoved, FName);`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingArrayCleared, FName);`
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingArrayItemMoved, FName);`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusNode_Comment.h` (Public)


#### class `UOptimusNode_Comment`  
`class UOptimusNode_Comment : public UOptimusNode`  
_L17-67_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UOptimusNode`
- L26 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L29 _public function_ `FName GetNodeCategory() const override`
- L31 _public prototype_ `bool SetSize(const UE::Slate::FDeprecateVector2DParameter& InSize);`
- L32 _public function_ `const UE::Slate::FDeprecateVector2DResult& GetSize()`
- L33 _public prototype_ `void SetComment(const FString& InNewComment);`
- L34 _public function_ `const FString& GetComment()`
- L36 _public function_ `FOnOptimusCommentNodePropertyChanged& GetOnPropertyChanged()`
- L40 _public member_ `FLinearColor CommentColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Category=Comment)` — Color to style comment with
- L44 _public member_ `int32 FontSize = 18;` — `UPROPERTY(EditAnywhere, Category=Comment, meta=(ClampMin=1, ClampMax=1000))` — Size of the text in the comment box
- L48 _public member_ `FString Comment = TEXT("Com` — `UPROPERTY(EditAnywhere, Category=Comment)` — Comment to show
- L52 _public member_ `bool bBubbleVisible = false;` — `UPROPERTY(EditAnywhere, Category=Comment, meta=(DisplayName="Show Bubble When Zoomed"))` — Whether to show a zoom-invariant comment bubble when zoomed out (making the comment readable at any distance).
- L56 _public member_ `bool bColorBubble = false;` — `UPROPERTY(EditAnywhere, Category=Comment, meta=(DisplayName="Color Bubble", EditCondition=bBubbleVisible))` — Whether to use Comment Color to color the background of the comment bubble shown when zoomed out.
- L61 _private prototype_ `bool SetSizeDirect(const FVector2f& InNewSize);`
- L64 _private member_ `FDeprecateSlateVector2D Size = FVector2f(400, 100);` — `UPROPERTY(NonTransactional)`
- L66 _private member_ `FOnOptimusCommentNodePropertyChanged OnPropertyChangedDelegate;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API OPTIMUSCORE_API`
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOptimusCommentNodePropertyChanged, UOptimusNode_Comment*);`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOptimusCommentNodePropertyChanged, UOptimusNode_Comment*);`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusObjectVersion.h` (Public)


#### struct `FOptimusObjectVersion`  
`struct FOptimusObjectVersion`  
_L8-39_
- L11 _public prototype_ `FOptimusObjectVersion() = delete;` — Not instantiable.
- L38 _public member_ `const static FGuid GUID;` — The GUID for this custom version number

#### enum `FOptimusObjectVersion::Type`  
`enum Type`  
_L13-35_
- L15 _public enumerator_ `InitialVersion`
- L17 _public enumerator_ `SwitchToMeshDeformerBase`
- L18 _public enumerator_ `ReparentResourcesAndVariables`
- L19 _public enumerator_ `SwitchToParameterBindingArrayStruct`
- L20 _public enumerator_ `AddBindingsToGraph`
- L21 _public enumerator_ `ComponentProviderSupport`
- L22 _public enumerator_ `SetPrimaryBindingName`
- L23 _public enumerator_ `DataDomainExpansion`
- L24 _public enumerator_ `KernelDataInterface`
- L25 _public enumerator_ `KernelParameterBindingToggleAtomic`
- L26 _public enumerator_ `PropertyBagValueContainer`
- L27 _public enumerator_ `SkinnedMeshWriteDIColorBufferManualFetchSwizzle`
- L28 _public enumerator_ `PropertyPinSupport`
- L29 _public enumerator_ `KernelThreadIndexUsingTotalThreadCount`
- L30 _public enumerator_ `FunctionGraphUseGuid`
- L33 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L34 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusResourceDescription.h` (Public)


#### class `UOptimusResourceDescription`  
`class UOptimusResourceDescription : public UObject`  
_L23-71_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L29 _public prototype_ `UOptimusResourceDescription() = default;`
- L33 _public prototype_ `UOptimusDeformer* GetOwningDeformer() const;` — FIXME: Move to interface-based system.
- L36 _public prototype_ `int32 GetIndex() const;` — Returns the index of the variable within the container
- L39 _public member_ `FName ResourceName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ResourceDescription, meta=(NoResetToDefault))`
- L43 _public member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY(EditAnywhere, Category=ResourceDescription, meta=(UseInResource, NoResetToDefault))` — The the data type of each element of the resource
- L47 _public member_ `TWeakObjectPtr<UOptimusComponentSourceBinding> ComponentBinding;` — `UPROPERTY(VisibleAnywhere, Category=ResourceDescription)` — The component binding that this resource description is bound to
- L51 _public member_ `FOptimusDataDomain DataDomain;` — `UPROPERTY(EditAnywhere, Category=ResourceDescription, meta=(EditCondition="ComponentBinding != nullptr", HideEditConditionToggle))` — The data domain for this resource.
- L54 _public member_ `TObjectPtr<UOptimusPersistentBufferDataInterface> DataInterface;` — `UPROPERTY()`
- L57 _public prototype_ `void PostLoad() override;` — UObject overrides
- L59 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L60 _public prototype_ `void PreEditUndo() override;`
- L61 _public prototype_ `void PostEditUndo() override;`
- L64 _public prototype_ `bool IsValidComponentBinding() const;`
- L65 _public prototype_ `FOptimusDataDomain GetDataDomainFromComponentBinding() const;`
- L69 _private member_ `FName ResourceNameForUndo;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusShaderText.h` (Public)


#### struct `FOptimusShaderText`  
`struct FOptimusShaderText`  
_L9-18_
- reflection: `USTRUCT()`
- L14 _public member_ `FString Declarations;` — `UPROPERTY(VisibleAnywhere, Category=ShaderText)`
- L17 _public member_ `FString ShaderText;` — `UPROPERTY(EditAnywhere, Category=ShaderText)`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusSource.h` (Public)


#### class `UOptimusSource`  
`class UOptimusSource : public UComputeSource , public IOptimusShaderTextProvider`  
_L12-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UComputeSource,IOptimusShaderTextProvider`
- L19 _public prototype_ `void SetSource(const FString& InText);`
- L21 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L25 _public function_ `FString GetSource() const override`
- L26 _public prototype_ `FString GetVirtualPath() const override;`
- L31 _public prototype_ `FString GetNameForShaderTextEditor() const override;`
- L32 _public function_ `FString GetDeclarations() const override`
- L33 _public function_ `FString GetShaderText() const override`
- L34 _public function_ `void SetShaderText(const FString& InText) override`
- L35 _public prototype_ `bool IsShaderTextReadOnly() const override;`
- L42 _protected member_ `FString SourceText;` — `UPROPERTY(EditAnywhere, Category = Source, meta = (DisplayAfter = "AdditionalSources"))` — HLSL Source.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusValidatedName.h` (Public)


#### struct `FOptimusValidatedName`  
`struct FOptimusValidatedName`  
_L15-40_
- reflection: `USTRUCT()`
- desc: Structure containing a FName that has been validated for use as a variable or function name in HLSL code. When using this as a UPROPERTY, the UI will use a property customization that validates text entry.
- L20 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category=Name)`
- L26 _public prototype_ `static bool IsValid(FString const& InName, FText* OutReason, FText const* InErrorCtx);` — Our default validation function. Returns true if InName is valid.
- L32 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);` — Allow serialization from a legacy FName or FString. Makes it easy to convert FName -> FOptimusValidateName.
- L35 _public function_ `operator FName () const` — Functions for compatibility with clients expecting a simple FName.
- L36 _public function_ `FOptimusValidatedName& operator=(FName const& RHS)`
- L37 _public function_ `bool operator==(FName const& RHS) const`
- L38 _public function_ `bool operator!=(FName const& RHS) const`
- L39 _public function_ `FString ToString() const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FOptimusValidatedName> : public TStructOpsTypeTraitsBase2<FOptimusValidatedName>`  
_L43-49_
- inherits: `TStructOpsTypeTraitsBase2<FOptimusValidatedName>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L46-48_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API OPTIMUSCORE_API`
- L47 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anona08c1d180103`)

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusValue.h` (Public)


#### enum `EOptimusValueUsage`  
`enum class EOptimusValueUsage: uint8`  
_L9-14_
- reflection: `UENUM()`
- L11 _public enumerator_ `None = 0`
- L12 _public enumerator_ `CPU = 1 << 0`
- L13 _public enumerator_ `GPU = 1 << 1`

#### enum `EOptimusValueType`  
`enum class EOptimusValueType : uint8`  
_L18-23_
- reflection: `UENUM()`
- L20 _public enumerator_ `Invalid`
- L21 _public enumerator_ `Constant`
- L22 _public enumerator_ `Variable`

#### struct `FOptimusValueIdentifier`  
`struct FOptimusValueIdentifier`  
_L26-45_
- reflection: `USTRUCT()`
- L31 _public member_ `EOptimusValueType Type = EOptimusValueType::Invalid;` — `UPROPERTY()`
- L34 _public member_ `FName Name = NAME_None;` — `UPROPERTY()`
- L41 _public function_ `bool operator==(FOptimusValueIdentifier const& InOther) const`

#### struct `FOptimusValueDescription`  
`struct FOptimusValueDescription`  
_L48-63_
- reflection: `USTRUCT()`
- L53 _public member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY()`
- L56 _public member_ `EOptimusValueUsage ValueUsage = EOptimusValueUsage::None;` — `UPROPERTY()`
- L59 _public member_ `FOptimusValueContainerStruct Value;` — `UPROPERTY()`
- L62 _public member_ `FShaderValueContainer ShaderValue;` — `UPROPERTY()`

#### struct `FOptimusDataInterfacePropertyOverrideInfo`  
`struct FOptimusDataInterfacePropertyOverrideInfo`  
_L66-72_
- reflection: `USTRUCT()`
- L71 _public member_ `TMap<FName, FOptimusValueIdentifier> PinNameToValueIdMap;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L15 _prototype_ `ENUM_CLASS_FLAGS(EOptimusValueUsage);`
- L36 _function_ `friend uint32 GetTypeHash(const FOptimusValueIdentifier& InIdentifier)`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusValueContainer.h` (Public)


#### class `UOptimusValueContainerGeneratorClass`  
`class UOptimusValueContainerGeneratorClass : public UClass`  
_L15-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UClass`
- desc: Deprecated
- L31 _private member_ `static FName ValuePropertyName;`
- L34 _private prototype_ `void Link(FArchive& Ar, bool bRelinkExistingProperties) override;` — UClass overrides
- L36 _private prototype_ `static UClass *GetClassForType( UPackage*InPackage, FOptimusDataTypeRef InDataType );`
- L41 _private prototype_ `static UClass *RefreshClassForType( UPackage*InPackage, FOptimusDataTypeRef InDataType );`
- L47 _private member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY()`

#### class `UOptimusValueContainer`  
`class UOptimusValueContainer : public UObject`  
_L52-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Deprecated
- L58 _public prototype_ `FOptimusValueContainerStruct MakeValueContainerStruct();` — Convert to the newer container type
- L61 _private prototype_ `void PostLoad() override;`
- L63 _private prototype_ `static UOptimusValueContainer* MakeValueContainer(UObject* InOwner, FOptimusDataTypeRef InDataTypeRef);`
- L65 _private prototype_ `FOptimusDataTypeRef GetValueType() const;`
- L66 _private prototype_ `FShaderValueContainer GetShaderValue() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OPTIMUSCORE_API`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusValueContainerStruct.h` (Public)


#### struct `FOptimusValueContainerStruct`  
`struct FOptimusValueContainerStruct`  
_L10-29_
- reflection: `USTRUCT()`
- L14 _public member_ `static const TCHAR* ValuePropertyName;`
- L17 _public member_ `FInstancedPropertyBag Value;` — `UPROPERTY(EditAnywhere, Category="Value", meta=(FixedLayout, ShowOnlyInnerProperties))`
- L19 _public prototype_ `bool IsInitialized() const;`
- L20 _public prototype_ `void SetType(FOptimusDataTypeRef InDataType);`
- L21 _public prototype_ `void SetValue(FOptimusDataTypeRef InDataType, TArrayView<const uint8> InValue);`
- L22 _public prototype_ `FShaderValueContainer GetShaderValue(FOptimusDataTypeRef InDataType) const;`
- L23 _public prototype_ `FString GetValueAsString() const;`
- L26 _private prototype_ `const FProperty* GetValueProperty() const;`
- L27 _private prototype_ `const uint8* GetValueMemory() const;`

### `Plugins/Animation/DeformerGraph/Source/OptimusCore/Public/OptimusVariableDescription.h` (Public)


#### struct `FOptimusVariableMetaDataEntry`  
`struct FOptimusVariableMetaDataEntry`  
_L23-39_
- reflection: `USTRUCT()`
- L27 _public function_ `FOptimusVariableMetaDataEntry()`
- L28 _public function_ `FOptimusVariableMetaDataEntry(FName InKey, FString&& InValue) : Key(InKey), Value(MoveTemp(InValue))`
- L34 _public member_ `FName Key;` — `UPROPERTY(EditAnywhere, Category = VariableMetaDataEntry)` — Name of metadata key
- L38 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, Category = VariableMetaDataEntry)` — Name of metadata value

#### class `UOptimusVariableDescription`  
`class UOptimusVariableDescription : public UObject`  
_L43-100_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L51 _public prototype_ `void SetDataType(FOptimusDataTypeRef InDataType);` — Set the data type, and recreate the backing data storage as well
- L55 _public prototype_ `UOptimusDeformer* GetOwningDeformer() const;` — FIXME: Move to interface-based system.
- L58 _public prototype_ `int32 GetIndex() const;` — Returns the index of the variable within the container
- L62 _public member_ `FGuid Guid;` — `UPROPERTY()` — An identifier that uniquely identifies this variable
- L66 _public member_ `FName VariableName;` — `UPROPERTY(EditAnywhere, Category = VariableDefinition, meta=(NoResetToDefault))` — Name of the variable
- L70 _public member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY(EditAnywhere, Category = VariableDefinition, meta=(UseInVariable, UseInProperty, NoResetToDefault))` — The data type of the variable
- L74 _public member_ `FOptimusValueContainerStruct DefaultValueStruct;` — `UPROPERTY(EditAnywhere, Category = VariableDefinition)` — The default value for the variable.
- L78 _public member_ `FShaderValueContainer CachedShaderValue;` — `UPROPERTY(Transient)` — Runtime container for variable values in a deformer instance
- L80 _public prototype_ `void PostLoad();`
- L82 _public prototype_ `void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L83 _public prototype_ `void PreEditUndo() override;`
- L84 _public prototype_ `void PostEditUndo() override;`
- L91 _private member_ `TArray<uint8> ValueData_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use CachedShaderValue instead"))` — Deprecated
- L95 _private member_ `TObjectPtr<UOptimusValueContainer> DefaultValue_DEPRECATED = nullptr;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "use DefaultValueStruct instead"))` — Deprecated
- L98 _private member_ `FName VariableNameForUndo;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API OPTIMUSCORE_API`
