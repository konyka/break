# Editor / BlueprintGraph

- module root: `Source/Editor/BlueprintGraph`
- headers: 154; symbols: 3982
- symbol kinds: class=168, delegate=13, enum=24, enumerator=87, function=534, macro=51, member=722, namespace=3, prototype=2301, struct=56, typedef=22, union=1
- PrivateDependencyModuleNames: AssetTools, EditorFramework, EditorSubsystem, GraphEditor, Kismet, KismetCompiler, KismetWidgets, PropertyEditor, SlateCore, ToolMenus, UMG, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, InputCore, Slate

### `Source/Editor/BlueprintGraph/Classes/AssetBlueprintGraphActions.h` (Public)


#### struct `FAssetBlueprintGraphActions`  
`struct FAssetBlueprintGraphActions`  
_L15-36_
- desc: Struct to handle Asset Blueprint Graph actions Essentially this is used to help generate asset nodes/responses for Blueprint graphs and keeping Blueprint code from being dependent on something it shouldn't For example, this can be used to help with dragging/dropping assets on a Blueprint graph
- L17 _public prototype_ `virtual ~FAssetBlueprintGraphActions() = default;`
- L25 _public prototype_ `virtual FText GetGraphHoverMessage(const FAssetData& AssetData, const UEdGraph* HoverGraph) const = 0;` — Gets the hover message when when holding a asset over a Blueprint graph from a drag/drop operation @param AssetData The asset being dragged/dropped @param HoverGraph The Blueprint graph to drop the asset on @return Message to display when hovering.
- L35 _public prototype_ `virtual bool TryCreatingAssetNode(const FAssetData& AssetData, UEdGraph* ParentGraph, const FVector2D Location, EK2NewNodeFlags Options) const = 0;` — Tries to create a node from the asset passed on the graph passed in @param AssetData The asset being dragged/dropped @param ParentGraph The Blueprint graph to drop the asset on @param Location Location to spawn the new asset node at @param Options Flags for node creation @return Bool of whether a node was successfully created

### `Source/Editor/BlueprintGraph/Classes/BlueprintAssetNodeSpawner.h` (Public)


#### class `UBlueprintAssetNodeSpawner`  
`class UBlueprintAssetNodeSpawner : public UBlueprintNodeSpawner`  
_L27-56_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBlueprintNodeSpawner`
- desc: Takes care of spawning various asset related nodes (nodes associated with an asset).
- L43 _public prototype_ `static UBlueprintAssetNodeSpawner* Create(TSubclassOf<UEdGraphNode> const InNodeClass, const FAssetData& InAssetData, UObject* InOuter = nullptr, FCustomizeNodeDelegate InPostSpawnDelegate = FCustomizeNodeDelegate());` — Creates a new UBlueprintAssetNodeSpawner for the supplied asset. Does not do any compatibility checking to ensure that the asset is viable for blueprint use. @param  InNodeClass			The type of node you want the spawner to create. @param  InAssetData			The asset you want assigned to new nodes. @param  InOuter				Optional outer for the new spawner (if left null, the transient package will be used). @param  InPostSpawnDelegate	A delegate to perform specialized node setup post-spawn. @return A newly allocated instance of this class.
- L50 _public prototype_ `const FAssetData& GetAssetData() const;` — Retrieves the asset that this assigns to spawned nodes. @return The asset that this class was initialized with.
- L55 _private member_ `FAssetData AssetData;` — `UPROPERTY()` — The asset to configure new nodes with.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/BlueprintBoundEventNodeSpawner.h` (Public)


#### class `UBlueprintBoundEventNodeSpawner`  
`class UBlueprintBoundEventNodeSpawner : public UBlueprintEventNodeSpawner`  
_L37-74_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBlueprintEventNodeSpawner`
- desc: Takes care of spawning UK2Node_Event nodes. Acts as the "action" portion of certain FBlueprintActionMenuItems. Will not spawn a new event node if one associated with the specified function already exits (instead, Invoke() will return the existing one). Evolved from FEdGraphSchemaAction_K2AddEvent and FEdGraphSchemaAction_K2ViewNode.
- L51 _public prototype_ `static UBlueprintBoundEventNodeSpawner* Create(TSubclassOf<UK2Node_Event> NodeClass, FMulticastDelegateProperty* EventDelegate, UObject* Outer = nullptr);` — Creates a new UBlueprintEventNodeSpawner for delegate bound events. Does not come bound, instead it is left up to the ui to bind @param  NodeClass		The event node type that you want this to spawn. @param  EventDelegate	The delegate that you want to trigger the spawned event. @param  Outer			Optional outer for the new spawner (if left null, the transient package will be used). @return A newly allocated instance of this class.
- L54 _public prototype_ `virtual FBlueprintNodeSignature GetSpawnerSignature() const override;` — UBlueprintNodeSpawner interface
- L55 _public prototype_ `virtual UEdGraphNode* Invoke(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location) const override;`
- L59 _public prototype_ `virtual UK2Node_Event const* FindPreExistingEvent(UBlueprint* Blueprint, FBindingSet const& Bindings) const override;` — UBlueprintEventNodeSpawner interface
- L63 _public prototype_ `virtual bool IsBindingCompatible(FBindingObject BindingCandidate) const override;` — IBlueprintNodeBinder interface
- L64 _public prototype_ `virtual bool BindToNode(UEdGraphNode* Node, FBindingObject Binding) const override;`
- L68 _public prototype_ `FMulticastDelegateProperty const* GetEventDelegate() const;` — @return
- L73 _private member_ `TFieldPath<FMulticastDelegateProperty> EventDelegate;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/BlueprintBoundNodeSpawner.h` (Public)


#### class `UBlueprintBoundNodeSpawner`  
`class UBlueprintBoundNodeSpawner : public UBlueprintNodeSpawner`  
_L31-70_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBlueprintNodeSpawner`
- desc: Takes care of spawning various bound nodes. Acts as the "action" portion of certain FBlueprintActionMenuItems.
- L34 _private prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanBindObjectDelegate, UObject const*);`
- L35 _private prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBindObjectDelegate, UEdGraphNode*, UObject*);`
- L36 _private prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(UEdGraphNode*, FFindPreExistingNodeDelegate, const UBlueprint*, IBlueprintNodeBinder::FBindingSet const& );`
- L42 _public prototype_ `static UBlueprintBoundNodeSpawner* Create(TSubclassOf<UEdGraphNode> NodeClass, UObject* Outer = nullptr);` — @return A newly allocated instance of this class.
- L45 _public prototype_ `virtual FBlueprintNodeSignature GetSpawnerSignature() const override;` — UBlueprintNodeSpawner interface
- L46 _public prototype_ `virtual UEdGraphNode* Invoke(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location) const override;`
- L50 _public prototype_ `virtual bool IsBindingCompatible(FBindingObject BindingCandidate) const override;` — FBlueprintNodeBinder interface
- L51 _public prototype_ `virtual bool BindToNode(UEdGraphNode* Node, FBindingObject Binding) const override;`
- L58 _public member_ `FCanBindObjectDelegate CanBindObjectDelegate;` — A delegate to perform specialized node binding verification
- L63 _public member_ `FOnBindObjectDelegate OnBindObjectDelegate;` — A delegate to perform specialized node setup during binding
- L69 _public member_ `FFindPreExistingNodeDelegate FindPreExistingNodeDelegate;` — A delegate to find a node that is already spawned, instead of spawning a node we will focus on the pre-existing node found by the delegate

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API BLUEPRINTGRAPH_API`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanBindObjectDelegate, UObject const*);`
- L35 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBindObjectDelegate, UEdGraphNode*, UObject*);`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(UEdGraphNode*, FFindPreExistingNodeDelegate, const UBlueprint*, IBlueprintNodeBinder::FBindingSet const& );`

### `Source/Editor/BlueprintGraph/Classes/BlueprintComponentNodeSpawner.h` (Public)


#### class `UBlueprintComponentNodeSpawner`  
`class UBlueprintComponentNodeSpawner : public UBlueprintNodeSpawner`  
_L33-79_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBlueprintNodeSpawner`
- desc: Takes care of spawning UK2Node_AddComponent nodes. Acts as the "action" portion of certain FBlueprintActionMenuItems. Evolved from FEdGraphSchemaAction_K2AddComponent.
- L46 _public prototype_ `static UBlueprintComponentNodeSpawner* Create(const struct FComponentTypeEntry& Entry);` — Creates a new UBlueprintComponentNodeSpawner for the specified class. Does not do any compatibility checking to ensure that the class is viable as a spawnable component (do that before calling this). @param  ComponentClass	The component type you want spawned nodes to spawn. @return A newly allocated instance of this class.
- L49 _public prototype_ `virtual FBlueprintNodeSignature GetSpawnerSignature() const override;` — UBlueprintNodeSpawner interface
- L50 _public prototype_ `virtual FBlueprintActionUiSpec GetUiSpec(FBlueprintActionContext const& Context, FBindingSet const& Bindings) const override;`
- L51 _public prototype_ `virtual UEdGraphNode* Invoke(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location) const override;`
- L52 _public prototype_ `virtual bool IsTemplateNodeFilteredOut(const FBlueprintActionFilter& Filter) const override;`
- L56 _public prototype_ `virtual bool IsBindingCompatible(FBindingObject BindingCandidate) const override;` — IBlueprintNodeBinder interface
- L57 _public prototype_ `virtual bool BindToNode(UEdGraphNode* Node, FBindingObject Binding) const override;`
- L65 _public prototype_ `TSubclassOf<UActorComponent> GetComponentClass() const;` — Retrieves the component class that this configures spawned nodes with. @return The component type that this class was initialized with.
- L70 _private member_ `TSubclassOf<UActorComponent> ComponentClass;` — `UPROPERTY()` — The component class to configure new nodes with.
- L74 _private member_ `FString ComponentName;` — `UPROPERTY()` — The name of the component class to configure new nodes with.
- L78 _private member_ `FString ComponentAssetName;` — `UPROPERTY()` — The name of the asset name that needs to be loaded

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/BlueprintDelegateNodeSpawner.h` (Public)


#### class `UBlueprintDelegateNodeSpawner`  
`class UBlueprintDelegateNodeSpawner : public UBlueprintFieldNodeSpawner`  
_L27-51_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBlueprintFieldNodeSpawner`
- desc: Takes care of spawning various nodes associated with delegates. Serves as the "action" portion for certain FBlueprintActionMenuItems. Evolved from FEdGraphSchemaAction_K2Delegate, FEdGraphSchemaAction_K2AssignDelegate, etc.
- L42 _public prototype_ `static UBlueprintDelegateNodeSpawner* Create(TSubclassOf<UK2Node_BaseMCDelegate> NodeClass, FMulticastDelegateProperty const* const Property, UObject* Outer = nullptr);` — Creates a new UBlueprintDelegateNodeSpawner for the specified property. Does not do any compatibility checking to ensure that the property is accessible from blueprints (do that before calling this). @param  NodeClass	The node type that you want the spawner to spawn. @param  Property		The property you want assigned to spawned nodes. @param  Outer		Optional outer for the new spawner (if left null, the transient package will be used). @return A newly allocated instance of this class.
- L50 _public prototype_ `FMulticastDelegateProperty const* GetDelegateProperty() const;` — Accessor to the delegate property that this spawner wraps (the delegate that this will assign spawned nodes with). @return The delegate property that this was initialized with.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/BlueprintEventNodeSpawner.h` (Public)


#### class `UBlueprintEventNodeSpawner`  
`class UBlueprintEventNodeSpawner : public UBlueprintNodeSpawner`  
_L37-100_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBlueprintNodeSpawner`
- desc: Takes care of spawning UK2Node_Event nodes. Acts as the "action" portion of certain FBlueprintActionMenuItems. Will not spawn a new event node if one associated with the specified function already exits (instead, Invoke() will return the existing one). Evolved from FEdGraphSchemaAction_K2AddEvent and FEdGraphSchemaAction_K2ViewNode.
- L51 _public prototype_ `static UBlueprintEventNodeSpawner* Create(UFunction const* const EventFunc, UObject* Outer = nullptr);` — Creates a new UBlueprintEventNodeSpawner for the specified function. Does not do any compatibility checking to ensure that the function is viable as a blueprint event (do that before calling this). @param  EventFunc	The function you want assigned to new nodes. @param  Outer		Optional outer for the new spawner (if left null, the transient package will be used). @return A newly allocated instance of this class.
- L63 _public prototype_ `static UBlueprintEventNodeSpawner* Create(TSubclassOf<UK2Node_Event> NodeClass, FName CustomEventName, UObject* Outer = nullptr);` — Creates a new UBlueprintEventNodeSpawner for custom events. The CustomEventName can be left blank if the node will pick one itself on instantiation. @param  NodeClass		The event node type that you want this to spawn. @param  CustomEventName	The name you want assigned to the event. @param  Outer			Optional outer for the new spawner (if left null, the transient package will be used). @return A newly allocated instance of this class.
- L66 _public prototype_ `virtual FBlueprintNodeSignature GetSpawnerSignature() const override;` — UBlueprintNodeSpawner interface
- L67 _public prototype_ `virtual UEdGraphNode* Invoke(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location) const override;`
- L75 _public prototype_ `bool IsForCustomEvent() const;` — @return
- L83 _public prototype_ `UFunction const* GetEventFunction() const;` — Retrieves the function that this assigns to spawned nodes (defines the event's signature). Can be null if this spawner was for a custom event. @return The event function that this class was initialized with.
- L90 _public prototype_ `virtual UK2Node_Event const* FindPreExistingEvent(UBlueprint* Blueprint, FBindingSet const& Bindings) const;` — @return
- L95 _protected member_ `TObjectPtr<UFunction const> EventFunc;` — `UPROPERTY()` — The function to configure new nodes with.
- L99 _protected member_ `FName CustomEventName;` — `UPROPERTY()` — The custom name to configure new event nodes with.

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/BlueprintFieldNodeSpawner.h` (Public)


#### class `UBlueprintFieldNodeSpawner`  
`class UBlueprintFieldNodeSpawner : public UBlueprintNodeSpawner`  
_L38-91_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBlueprintNodeSpawner`
- desc: Takes care of spawning various field related nodes (nodes associated with functions, enums, structs, properties, etc.). Acts as the "action" portion for certain FBlueprintActionMenuItems.
- L41 _private prototype_ `DECLARE_DELEGATE_TwoParams(FSetNodeFieldDelegate, UEdGraphNode*, FFieldVariant);`
- L55 _public prototype_ `static UBlueprintFieldNodeSpawner* Create(TSubclassOf<UK2Node> NodeClass, FFieldVariant Field, UObject* Outer = nullptr, UClass const* OwnerClass = nullptr);` — Creates a new UBlueprintFieldNodeSpawner for the supplied field. Does not do any compatibility checking to ensure that the field is viable for blueprint use. @param  NodeClass	The type of node you want the spawner to create. @param  Field		The field you want assigned to new nodes. @param  Outer		Optional outer for the new spawner (if left null, the transient package will be used). @param  OwnerClass	The class that the variable is a member of or the class it is associated with if it is in a sidecar data structure. @return A newly allocated instance of this class.
- L58 _public prototype_ `virtual FBlueprintNodeSignature GetSpawnerSignature() const override;` — UBlueprintNodeSpawner interface
- L59 _public prototype_ `virtual UEdGraphNode* Invoke(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location) const override;`
- L63 _public member_ `FSetNodeFieldDelegate SetNodeFieldDelegate;` — Callback to define how the field should be applied to new nodes
- L71 _public prototype_ `FFieldVariant GetField() const;` — Retrieves the field that this assigns to spawned nodes (defines the node's signature). @return The field that this class was initialized with.
- L78 _protected prototype_ `void SetField(FFieldVariant InField);` — Sets the field for this spawner
- L82 _protected member_ `TObjectPtr<UClass const> OwnerClass;` — `UPROPERTY()` — The owning class to configure new nodes with.
- L87 _private member_ `TObjectPtr<UField> Field;` — `UPROPERTY()` — The field to configure new nodes with.
- L90 _private member_ `TFieldPath<FProperty> Property;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API BLUEPRINTGRAPH_API`
- L41 _delegate_ `DECLARE_DELEGATE_TwoParams(FSetNodeFieldDelegate, UEdGraphNode*, FFieldVariant);`

### `Source/Editor/BlueprintGraph/Classes/BlueprintFunctionNodeSpawner.h` (Public)


#### class `UBlueprintFunctionNodeSpawner`  
`class UBlueprintFunctionNodeSpawner : public UBlueprintFieldNodeSpawner`  
_L33-80_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBlueprintFieldNodeSpawner`
- desc: Takes care of spawning various UK2Node_CallFunction nodes. Acts as the "action" portion of certain FBlueprintActionMenuItems.
- L47 _public prototype_ `static UBlueprintFunctionNodeSpawner* Create(UFunction const* const Function, UObject* Outer = nullptr);` — Creates a new UBlueprintFunctionNodeSpawner for the specified function. Does not do any compatibility checking to ensure that the function is viable as a blueprint function call (do that before calling this). @param  Function		The function you want assigned to new nodes. @param  Outer		Optional outer for the new spawner (if left null, the transient package will be used). @return A newly allocated instance of this class.
- L59 _public prototype_ `static UBlueprintFunctionNodeSpawner* Create(TSubclassOf<UK2Node_CallFunction> NodeClass, UFunction const* const Function, UObject* Outer = nullptr);` — Creates a new UBlueprintFunctionNodeSpawner for the specified function. Does not do any compatibility checking to ensure that the function is viable as a blueprint function call (do that before calling this). @param  NodeClass	The type of node you want the spawner to create. @param  Function		The function you want assigned to new nodes. @param  Outer		Optional outer for the new spawner (if left null, the transient package will be used). @return A newly allocated instance of this class.
- L62 _public prototype_ `virtual void Prime() override;` — UBlueprintNodeSpawner interface
- L63 _public prototype_ `virtual FBlueprintActionUiSpec GetUiSpec(FBlueprintActionContext const& Context, FBindingSet const& Bindings) const override;`
- L64 _public prototype_ `virtual UEdGraphNode* Invoke(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location) const override;`
- L68 _public prototype_ `virtual bool IsBindingCompatible(FBindingObject BindingCandidate) const override;` — IBlueprintNodeBinder interface
- L69 _public prototype_ `virtual bool CanBindMultipleObjects() const override;`
- L70 _public prototype_ `virtual bool BindToNode(UEdGraphNode* Node, FBindingObject Binding) const override;`
- L79 _public prototype_ `UFunction const* GetFunction() const;` — Retrieves the function that this assigns to spawned nodes (defines the node's signature). @return The function that this class was initialized with.

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/BlueprintNodeBinder.h` (Public)


#### class `FBindingObject`  
`class FBindingObject`  
_L16-210_
- L18 _private member_ `TObjectPtr<UObject> Object;`
- L19 _private member_ `FField* Field;`
- L20 _private member_ `bool bIsUObject;`
- L22 _public function_ `FBindingObject() : bIsUObject(false)`
- L29 _public function_ `FBindingObject(T InObject) : Object(InObject) , bIsUObject(true)`
- L33 _public function_ `FBindingObject(FField* InField) : Field(InField) , bIsUObject(false)`
- L37 _public function_ `FBindingObject(const FFieldVariant& InFieldOrObject)`
- L53 _public function_ `FBindingObject& operator=(T InObject)`
- L60 _public function_ `FBindingObject& operator=(FField* InField)`
- L67 _public function_ `FBindingObject& operator=(TYPE_OF_NULLPTR)`
- L73 _public function_ `bool IsUObject() const`
- L77 _public function_ `bool IsValid() const`
- L81 _public function_ `FName GetFName() const`
- L85 _public function_ `FString GetName() const`
- L89 _public function_ `FString GetPathName() const`
- L93 _public function_ `FString GetFullName() const`
- L97 _public function_ `bool IsA(const UClass* InClass) const`
- L101 _public function_ `bool IsA(const FFieldClass* InClass) const`
- L106 _public function_ `template <typename T> bool IsA() const`
- L125 _public function_ `template <typename T> T* Get() const`
- L149 _public function_ `bool operator==(const FBindingObject &Other) const`
- L153 _public function_ `bool operator!=(const FBindingObject &Other) const`
- L209 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FBindingObject> : public TStructOpsTypeTraitsBase2<FBindingObject>`  
_L213-219_
- inherits: `TStructOpsTypeTraitsBase2<FBindingObject>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L216-218_

#### class `IBlueprintNodeBinder`  
`class IBlueprintNodeBinder`  
_L221-276_
- L225 _public typedef_ `typedef TSet< FBindingObject > FBindingSet;`
- L234 _public prototype_ `virtual bool IsBindingCompatible(FBindingObject BindingCandidate) const = 0;` — Checks to see if the specified object can be bound by this. @param  BindingCandidate	The object you want to check for. @return True if BindingCandidate can be bound by this controller, false if not.
- L242 _public prototype_ `virtual bool CanBindMultipleObjects() const = 0;` — Determines if this will accept more than one binding (used to block multiple bindings from being applied to nodes that can only have one). @return True if this will accept multiple bindings, otherwise false.
- L250 _public function_ `bool ApplyBindings(UEdGraphNode* Node, FBindingSet const& Bindings) const` — Attempts to bind all bindings to the supplied node. @param  Node	 The node you want bound to. @return True if all bindings were successfully applied, false if any failed.
- L275 _protected prototype_ `virtual bool BindToNode(UEdGraphNode* Node, FBindingObject Binding) const = 0;` — Attempts to apply the specified binding to the supplied node. @param  Node		The node you want bound. @param  Binding	The binding you want applied to Node. @return True if the binding was successful, false if not.

#### Free symbols / members of external scopes

- L144 _function_ `friend uint32 GetTypeHash(const FBindingObject& BindingObject)`
- L158 _function_ `friend bool operator==(const FBindingObject &Lhs, const UObject* Rhs)`
- L162 _function_ `friend bool operator!=(const FBindingObject &Lhs, const UObject* Rhs)`
- L166 _function_ `friend bool operator==(const UObject* Lhs, const FBindingObject &Rhs)`
- L170 _function_ `friend bool operator!=(const UObject* Lhs, const FBindingObject &Rhs)`
- L175 _function_ `friend bool operator==(const FBindingObject &Lhs, const FField* Rhs)`
- L179 _function_ `friend bool operator!=(const FBindingObject &Lhs, const FField* Rhs)`
- L183 _function_ `friend bool operator==(const FField* Lhs, const FBindingObject &Rhs)`
- L187 _function_ `friend bool operator!=(const FField* Lhs, const FBindingObject &Rhs)`
- L192 _function_ `friend bool operator==(const FBindingObject &Lhs, TYPE_OF_NULLPTR)`
- L196 _function_ `friend bool operator!=(const FBindingObject &Lhs, TYPE_OF_NULLPTR)`
- L200 _function_ `friend bool operator==(TYPE_OF_NULLPTR, const FBindingObject &Rhs)`
- L204 _function_ `friend bool operator!=(TYPE_OF_NULLPTR, const FBindingObject &Rhs)`
- L217 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon19fcda640103`)

### `Source/Editor/BlueprintGraph/Classes/BlueprintTypePromotion.h` (Public)


#### class `FTypePromotion`  
`class FTypePromotion : private FNoncopyable`  
_L33-207_
- inherits: `FNoncopyable`
- desc: Contains behavior needed to handle type promotion in blueprints. Creates a map of "Operations" to any of their matching UFunctions so that we can find the best possible match given several pin types.
- L38 _public prototype_ `static FTypePromotion& Get();` — Creates a new singleton instance of TypePromotion if there isn't one and returns a reference to it
- L41 _public prototype_ `static void Shutdown();` — Deletes the singleton instance of type promotion if there is one
- L47 _public prototype_ `static UFunction* FindBestMatchingFunc(FName Operation, const TArray<UEdGraphPin*>& PinsToConsider);` — Find the function that is the best match given the pins to consider. Ex: Given "Add" operator and an array of two Vector pins, it will return "Add_VectorVector"
- L50 _public prototype_ `static void GetAllFuncsForOp(FName Operation, TArray<UFunction*>& OutFuncs);` — Returns all functions for a specific operation. Will empty the given array and populate it with UFunction pointers
- L53 _public prototype_ `static const TSet<FName>& GetAllOpNames();` — Get a set of the supported operator names for type promo. Ex: "Add", "Subtract", "Multiply"
- L56 _public prototype_ `static const TSet<FName>& GetComparisonOpNames();` — Set of comparison operator names (GreaterThan, LessThan, etc)
- L59 _public prototype_ `static const FText& GetKeywordsForOperator(const FName Operator);` — Get the keywords metadata for the given operator name
- L62 _public prototype_ `static const FText& GetUserFacingOperatorName(const FName Operator);` — Get the user facing version of this operator name
- L65 _public prototype_ `static bool IsComparisonFunc(UFunction const* const Func);` — Returns true if the given function is a comparison operator
- L68 _public prototype_ `static bool IsComparisonOpName(const FName OpName);` — Returns true if the given op name is a comparison operator name
- L77 _public prototype_ `static FName GetOpNameFromFunction(UFunction const* const Func);` — Parse the name of the operator that this function matches to (Add, Subtract, etc) @param Func		The function to parse the operator name from @return FName		Name of the operator for this function, NO_OP if does not exist.
- L84 _public prototype_ `static FEdGraphPinType GetPromotedType(const TArray<UEdGraphPin*>& WildcardPins);` — Determine what type a given set of wildcard pins would result in @return	Pin type that is the "highest" of all the given pins
- L87 _public prototype_ `static bool IsFunctionPromotionReady(const UFunction* const FuncToConsider);` — Returns true if the given function has been registered within the operator table
- L102 _public prototype_ `static ETypeComparisonResult GetHigherType(const FEdGraphPinType& A, const FEdGraphPinType& B);` — Given the two pin types check which pin type is higher. Given two structs it will return equal, this does NOT compare PinDefaultSubobjects
- L105 _public prototype_ `static bool IsValidPromotion(const FEdGraphPinType& A, const FEdGraphPinType& B);` — Returns true if A can be promoted to type B correctly, or if the types are equal
- L108 _public prototype_ `static bool HasStructConversion(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin);` — Returns true if the given input pin can correctly be converted to the output type as a struct
- L111 _public prototype_ `static bool IsOperatorSpawnerRegistered(UFunction const* const Func);` — Returns true if the given function has a registered operator node spawner
- L114 _public prototype_ `static UBlueprintFunctionNodeSpawner* GetOperatorSpawner(FName OpName);` — Function node spawner associated with this operation
- L118 _public prototype_ `static void RegisterOperatorSpawner(FName OpName, UBlueprintFunctionNodeSpawner* Spawner);` — keep track of the operator that this function provides so that we don't add multiple to the BP context menu
- L124 _public prototype_ `static void ClearNodeSpawners();` — Clear all registered node spawners for operators from the system. This is necessary during hot reload to ensure that all operator spawners are up to date.
- L132 _public prototype_ `static void RefreshPromotionTables(EReloadCompleteReason Reason = EReloadCompleteReason::None);` — Clear out the promotion table and rebuild it, reassessing each available UFunction. @param Reason	The reason for refreshing the promotion tables, which can indicate whether or not it came from a Live Coding recompile.
- L140 _public prototype_ `static const TMap<FName, TArray<FName>>* const GetPrimitivePromotionTable();` — Get the "Primitive Promotion Table" which represents what base Pin types can be promoted to others. @return Const pointer to the primitive promotion table
- L149 _public prototype_ `static const TArray<FName>* GetAvailablePrimitivePromotions(const FEdGraphPinType& Type);` — Get a pointer to an array of available promotion types to a given pin type @param Type		The pin type to find available promotions to @return const TArray<FName>*	Pointer to the available promotions, nullptr if there are none.
- L153 _private prototype_ `explicit FTypePromotion();`
- L154 _private prototype_ `~FTypePromotion();`
- L156 _private prototype_ `bool IsFunctionPromotionReady_Internal(const UFunction* const FuncToConsider) const;`
- L158 _private prototype_ `FEdGraphPinType GetPromotedType_Internal(const TArray<UEdGraphPin*>& WildcardPins) const;`
- L160 _private prototype_ `UFunction* FindBestMatchingFunc_Internal(FName Operation, const TArray<UEdGraphPin*>& PinsToConsider);`
- L162 _private prototype_ `void GetAllFuncsForOp_Internal(FName Operation, TArray<UFunction*>& OutFuncs);`
- L165 _private prototype_ `static bool IsPromotableFunction(const UFunction* Function);` — Returns true if the given function is a candidate to handle type promotion
- L172 _private prototype_ `ETypeComparisonResult GetHigherType_Internal(const FEdGraphPinType& A, const FEdGraphPinType& B) const;` — Determines which pin type is "higher" @see FTypePromotion::PromotionTable
- L175 _private prototype_ `void CreateOpTable();` — Creates a lookup table of types and operations to their appropriate UFunction
- L178 _private prototype_ `TMap<FName, TArray<FName>> CreatePromotionTable();` — Creates the table of what types can be promoted to others
- L180 _private prototype_ `void AddOpFunction(FName OpName, UFunction* Function);`
- L182 _private member_ `static FTypePromotion* Instance;`
- L185 _private member_ `const TMap<FName, TArray<FName>> PromotionTable;` — A map of 'Type' to its 'available promotions'. See ctor for creation
- L192 _private typedef_ `typedef TArray<UFunction*> FFunctionsList;` — A single operator can have multiple functions associated with it; usually for handling different types (int*int, vs. int*vector), hence this array. This is the same implementation style as the Math Expression node.
- L197 _private member_ `mutable FCriticalSection Lock;` — Protects internal data from multi-threaded access.
- L203 _private member_ `TMap<FName, FFunctionsList> OperatorTable;` — A lookup table, mapping operator strings (like "Add", "Multiply", etc.) to a list of associated functions.
- L206 _private member_ `TMap<FName, UBlueprintFunctionNodeSpawner*> OperatorNodeSpawnerMap;` — Map of operators to their node spawner so that we can clean up the context menu

#### enum `FTypePromotion::ETypeComparisonResult`  
`enum class ETypeComparisonResult : uint8`  
_L90-96_
- desc: Represents the possible results when comparing two types for promotion
- L92 _public enumerator_ `TypeAHigher`
- L93 _public enumerator_ `TypeBHigher`
- L94 _public enumerator_ `TypesEqual`
- L95 _public enumerator_ `InvalidComparison`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API BLUEPRINTGRAPH_API`
- L209 _namespace_ `namespace TypePromoDebug`
- L215 _function_ `static bool IsTypePromoEnabled()` (scope `TypePromoDebug`) — Checks if the type promotion editor pref is true or false (The bEnableTypePromotion BP editor setting)

### `Source/Editor/BlueprintGraph/Classes/BlueprintVariableNodeSpawner.h` (Public)


#### class `UBlueprintVariableNodeSpawner`  
`class UBlueprintVariableNodeSpawner : public UBlueprintFieldNodeSpawner`  
_L42-135_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBlueprintFieldNodeSpawner`
- desc: Takes care of spawning variable getter/setter nodes. Serves as the "action" portion for certain FBlueprintActionMenuItems. Evolved from FEdGraphSchemaAction_K2Var, and can spawn nodes for both member-variables and local function variables.
- L57 _public prototype_ `static UBlueprintVariableNodeSpawner* CreateFromMemberOrParam(TSubclassOf<UK2Node_Variable> NodeClass, FProperty const* VarProperty, UEdGraph* VarContext = nullptr, UClass* OwnerClass = nullptr);` — Creates a new UBlueprintVariableNodeSpawner, charged with spawning a member-variable node (for a variable that has an associated FProperty) @param  NodeClass	The node type that you want the spawner to spawn. @param  VarProperty	The property that represents the member-variable you want nodes spawned for. @param  VarContext	The graph that the local variable belongs to. @param  OwnerClass	The class that the variable is a member of or the class it is associated with if it is in a sidecar data structure. @return A newly allocated instance of this class.
- L70 _public prototype_ `static UBlueprintVariableNodeSpawner* CreateFromLocal(TSubclassOf<UK2Node_Variable> NodeClass, UEdGraph* VarContext, FBPVariableDescription const& VarDesc, FProperty* VarProperty, UObject* Outer = nullptr);` — Creates a new UBlueprintVariableNodeSpawner, charged with spawning a local-variable node (for a variable that belongs to a specific graph). @param  NodeClass	The node type that you want the spawner to spawn. @param  VarContext	The graph that the local variable belongs to. @param  VarDesc		Details the local variable (name, type, etc.) @param  VarProperty	The property that represents the local-variable you want nodes spawned for. @param  Outer		Optional outer for the new spawner (if left null, the transient package will be used). @return A newly allocated instance of this class.
- L73 _public prototype_ `virtual void Prime() override;` — UBlueprintNodeSpawner interface
- L74 _public prototype_ `virtual FBlueprintNodeSignature GetSpawnerSignature() const override;`
- L75 _public prototype_ `virtual FBlueprintActionUiSpec GetUiSpec(FBlueprintActionContext const& Context, FBindingSet const& Bindings) const override;`
- L76 _public prototype_ `virtual UEdGraphNode* Invoke(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location) const override;`
- L82 _public prototype_ `bool IsUserLocalVariable() const;` — @return True if this is a user-created local variable
- L90 _public prototype_ `bool IsLocalVariable() const;` — Since this spawner can wrap both local and member variables, we use this method to discern between the two. @return True if this spawner wraps a local variable, false if not.
- L99 _public prototype_ `FFieldVariant GetVarOuter() const;` — If this is a local variable, then this will return the UEdGraph that it belongs to, otherwise it pulls the outer from the wrapped member-variable property. @return Null if the variable is no longer valid, otherwise an object pointer to the variable's owner.
- L107 _public prototype_ `FProperty const* GetVarProperty() const;` — Accessor to the variable's property. Will be null if this is for a local variable (as they don't have UProperties associated with them). @return Null if this wraps a local variable (or if the variable property is stale), otherwise the property this was initialized with.
- L116 _public prototype_ `FEdGraphPinType GetVarType() const;` — Utility function for easily accessing the variable's type (needs to pull the information differently if it is a local variable as opposed to a member variable with a FProperty). @return A struct detailing the wrapped variable's type.
- L126 _private prototype_ `FText GetVariableName() const;` — Utility function for easily accessing the variable's name (needs to pull the information differently if it is a local variable as opposed to a member variable with a FProperty). @return A friendly, user presentable, name for the variable that this wraps.
- L130 _private member_ `TObjectPtr<UEdGraph> LocalVarOuter;` — `UPROPERTY()` — The graph that the local variable belongs to (if this is a local variable spawner).
- L134 _private member_ `FBPVariableDescription LocalVarDesc;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/EdGraphSchema_K2.h` (Public)


#### struct `FEdGraphSchemaAction_K2Struct`  
`struct FEdGraphSchemaAction_K2Struct : public FEdGraphSchemaAction`  
_L56-88_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Reference to an structure (only used in 'docked' palette)
- L61 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L62 _public function_ `virtual FName GetTypeId() const override`
- L64 _public member_ `TObjectPtr<UStruct> Struct;`
- L66 _public function_ `void AddReferencedObjects( FReferenceCollector& Collector ) override`
- L74 _public function_ `FName GetPathName() const`
- L79 _public function_ `FEdGraphSchemaAction_K2Struct() : FEdGraphSchemaAction() , Struct(nullptr)`
- L84 _public function_ `FEdGraphSchemaAction_K2Struct(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) , Struct(nullptr)`

#### struct `FBlueprintMetadata`  
`struct FBlueprintMetadata`  
_L91-315_
- desc: Constants used for metadata, etc... in blueprints
- L96 _public member_ `static const FName MD_AllowableBlueprintVariableType;` — Struct/Enum/Class: If true, this class, struct, or enum is a valid type for use as a variable in a blueprint
- L99 _public member_ `static const FName MD_NotAllowableBlueprintVariableType;` — If true, this class, struct, or enum is not valid for use as a variable in a blueprint
- L103 _public member_ `static const FName MD_BlueprintSpawnableComponent;` — Class: [ClassMetadata] If present, the component class can be spawned by a blueprint
- L106 _public member_ `static const FName MD_IsBlueprintBase;` — If true, the class will be usable as a base for blueprints
- L109 _public member_ `static const FName MD_RestrictedToClasses;` — A listing of classes that this class is accessible from (and only those classes, if present).  Note that this determines the GRAPH CONTEXTS in which the node cannot be placed (e.g. right click menu, palette), and does NOT control menus when dragging off of a context pin (i.e. contextual drag)
- L112 _public member_ `static const FName MD_ChildCanTick;` — [ClassMetadata] Used for Actor and Component classes. If the native class cannot tick, Blueprint generated classes based this Actor or Component can have bCanEverTick flag overridden even if bCanBlueprintsTickByDefault is false.
- L115 _public member_ `static const FName MD_ChildCannotTick;` — [ClassMetadata] Used for Actor and Component classes. If the native class cannot tick, Blueprint generated classes based this Actor or Component can never tick even if bCanBlueprintsTickByDefault is true.
- L118 _public member_ `static const FName MD_IgnoreCategoryKeywordsInSubclasses;` — [ClassMetadata] Used to make the first subclass of a class ignore all inherited showCategories and hideCategories commands
- L121 _public member_ `static const FName MD_CustomThunkTemplates;` — Specifies which struct implements the custom thunk functions for this class
- L125 _public member_ `static const FName MD_Protected;` — Specifies a UFUNCTION as Kismet protected, which can only be called from itself
- L128 _public member_ `static const FName MD_Latent;` — Marks a UFUNCTION as latent execution
- L131 _public member_ `static const FName MD_CustomThunk;` — Indicates that the UFUNCTION implements its own thunk function
- L134 _public member_ `static const FName MD_Variadic;` — Marks a UFUNCTION as accepting variadic arguments
- L137 _public member_ `static const FName MD_UnsafeForConstructionScripts;` — Marks a UFUNCTION as unsafe for use in the UCS, which prevents it from being called from the UCS.  Useful for things that spawn actors, etc that should never happen in the UCS
- L140 _public member_ `static const FName MD_FunctionCategory;` — The category that a function appears under in the palette
- L143 _public member_ `static const FName MD_DeprecatedFunction;` — [FunctionMetadata] Indicates that the function is deprecated
- L146 _public member_ `static const FName MD_DeprecatedProperty;` — [FunctionMetadata] Indicates that the property is deprecated
- L149 _public member_ `static const FName MD_DeprecationMessage;` — [FunctionMetadata] Supplies the custom message to use for deprecation
- L152 _public member_ `static const FName MD_CompactNodeTitle;` — [FunctionMetadata] Indicates that the function should be drawn as a compact node with the specified body title
- L155 _public member_ `static const FName MD_DisplayName;` — [FunctionMetadata] Indicates that the function should be drawn with this title over the function name
- L158 _public member_ `static const FName MD_ReturnDisplayName;` — [FunctionMetadata] Indicates the display name of the return value pin
- L161 _public member_ `static const FName MD_InternalUseParam;` — [FunctionMetadata] Indicates that a particular function parameter is for internal use only, which means it will be both hidden and not connectible.
- L164 _public member_ `static const FName MD_ForceAsFunction;` — [FunctionMetadata] Indicates that the function should appear as blueprint function even if it doesn't return a value.
- L167 _public member_ `static const FName MD_IgnoreTypePromotion;` — [FunctionMetadata] Indicates that the function should be ignored when considered for blueprint type promotion
- L172 _public member_ `static const FName MD_ExposeOnSpawn;` — UPROPERTY will be exposed on "Spawn Blueprint" nodes as an input
- L175 _public member_ `static const FName MD_PropertyGetFunction;` — UPROPERTY uses the specified function as a getter rather than reading from the property directly
- L178 _public member_ `static const FName MD_PropertySetFunction;` — UPROPERTY uses the specified function as a setter rather than writing to the property directly
- L181 _public member_ `static const FName MD_Private;` — UPROPERTY cannot be modified by other blueprints
- L184 _public member_ `static const FName MD_HideSelfPin;` — If true, the self pin should not be shown or connectable regardless of purity, const, etc. similar to InternalUseParam
- L187 _public member_ `static const FName MD_DefaultToSelf;` — If true, the specified UObject parameter will default to "self" if nothing is connected
- L190 _public member_ `static const FName MD_WorldContext;` — The specified parameter should be used as the context object when retrieving a UWorld pointer (implies hidden and default-to-self)
- L193 _public member_ `static const FName MD_CallableWithoutWorldContext;` — For functions that have the MD_WorldContext metadata but are safe to be called from contexts that do not have the ability to provide the world context (either through GetWorld() or ShowWorldContextPin class metadata
- L196 _public member_ `static const FName MD_DevelopmentOnly;` — For functions that should be compiled in development mode only
- L199 _public member_ `static const FName MD_AutoCreateRefTerm;` — If true, an unconnected pin will generate a UPROPERTY under the hood to connect as the input, which will be set to the literal value for the pin.  Only valid for reference parameters.
- L202 _public member_ `static const FName MD_HideAssetPicker;` — `UE_DEPRECATED(5.6, "Use MD_HidePinAssetPicker instead.")`
- L206 _public member_ `static const FName MD_HidePinAssetPicker;` — For properties, forcibly hide the asset picker for the pin corresponding to the property.
- L209 _public member_ `static const FName MD_ShowWorldContextPin;` — If true, the hidden world context pin will be visible when the function is placed in a child blueprint of the class.
- L212 _public member_ `static const FName MD_HidePin;` — Comma delimited list of pins that should be hidden on this function.
- L214 _public member_ `static const FName MD_BlueprintInternalUseOnly;`
- L215 _public member_ `static const FName MD_BlueprintInternalUseOnlyHierarchical;`
- L216 _public member_ `static const FName MD_NeedsLatentFixup;`
- L218 _public member_ `static const FName MD_LatentInfo;`
- L219 _public member_ `static const FName MD_LatentCallbackTarget;`
- L222 _public member_ `static const FName MD_AllowPrivateAccess;` — If true, properties defined in the C++ private scope will be accessible to blueprints
- L225 _public member_ `static const FName MD_ExposeFunctionCategories;` — Categories of functions to expose on this property
- L228 _public member_ `static const FName MD_CannotImplementInterfaceInBlueprint;` — [InterfaceMetadata]
- L229 _public member_ `static const FName MD_ProhibitedInterfaces;`
- L232 _public member_ `static const FName MD_FunctionKeywords;` — Keywords used when searching for functions
- L235 _public member_ `static const FName MD_ExpandEnumAsExecs;` — Indicates that during compile we want to create multiple exec pins from an enum param
- L238 _public member_ `static const FName MD_ExpandBoolAsExecs;` — Synonym for MD_ExpandEnumAsExecs
- L240 _public member_ `static const FName MD_CommutativeAssociativeBinaryOperator;`
- L243 _public member_ `static const FName MD_MaterialParameterCollectionFunction;` — Metadata string that indicates to use the MaterialParameterCollectionFunction node.
- L246 _public member_ `static const FName MD_Tooltip;` — Metadata string that sets the tooltip
- L249 _public member_ `static const FName MD_CallInEditor;` — Metadata string that indicates the specified event can be triggered in editor
- L252 _public member_ `static const FName MD_DataTablePin;` — Metadata to identify an DataTable Pin. Depending on which DataTable is selected, we display different RowName options
- L255 _public member_ `static const FName MD_NativeMakeFunction;` — Metadata that flags make/break functions for specific struct types.
- L256 _public member_ `static const FName MD_NativeBreakFunction;`
- L257 _public member_ `static const FName MD_NativeDisableSplitPin;`
- L260 _public member_ `static const FName MD_DynamicOutputType;` — Metadata that flags function params that govern what type of object the function returns
- L262 _public member_ `static const FName MD_DynamicOutputParam;` — Metadata that flags the function output param that will be controlled by the "MD_DynamicOutputType" pin
- L264 _public member_ `static const FName MD_CustomStructureParam;`
- L266 _public member_ `static const FName MD_ArrayParam;`
- L267 _public member_ `static const FName MD_ArrayDependentParam;`
- L270 _public member_ `static const FName MD_SetParam;` — Metadata that flags TSet parameters that will have their type determined at blueprint compile time
- L273 _public member_ `static const FName MD_MapParam;` — Metadata that flags TMap function parameters that will have their type determined at blueprint compile time
- L274 _public member_ `static const FName MD_MapKeyParam;`
- L275 _public member_ `static const FName MD_MapValueParam;`
- L278 _public member_ `static const FName MD_Bitmask;` — Metadata that identifies an integral property as a bitmask.
- L280 _public member_ `static const FName MD_BitmaskEnum;` — Metadata that associates a bitmask property with a bitflag enum.
- L282 _public member_ `static const FName MD_Bitflags;` — Metadata that identifies an enum as a set of explicitly-named bitflags.
- L284 _public member_ `static const FName MD_UseEnumValuesAsMaskValuesInEditor;` — Metadata that signals to the editor that enum values correspond to mask values instead of bitshift (index) values.
- L287 _public member_ `static const FName MD_AnimBlueprintFunction;` — Stub function used internally by animation blueprints
- L290 _public member_ `static const FName MD_ShowDisplayNames;` — Metadata that should be used with UPARAM to specify whether a TSubclassOf argument should use the DisplayName of classes
- L293 _public member_ `static const FName MD_AllowAbstractClasses;` — Metadata that should be used with UPARAM to specify whether a TSubclassOf argument allows abstract classes
- L295 _public member_ `static const FName MD_AllowedClasses;` — Metadata that should be used with UPARAM to specify which classes are allowed in selection
- L298 _public member_ `static const FName MD_GetOptions;` — Metadata that should be used with UPARAM to specify a function name that generates a list of available values
- L301 _public member_ `static const FName MD_Namespace;` — Namespace into which a type can be optionally defined; if empty or not set, the type will belong to the global namespace (default).
- L304 _public member_ `static const FName MD_ThreadSafe;` — Function or class marked as thread-safe. Opts class/function compilation into thread-safety checks.
- L307 _public member_ `static const FName MD_NotThreadSafe;` — Function marked as explicitly not thread-safe. Opts function out of class-level thread-safety checks.
- L310 _public member_ `static const FName MD_FieldNotify;` — Metadata to add the property or function to the FieldNotification system.
- L314 _private function_ `FBlueprintMetadata()` — This class should never be instantiated

#### struct `FBlueprintCallableFunctionRedirect`  
`struct FBlueprintCallableFunctionRedirect`  
_L320-338_
- desc: Structure used to automatically convert blueprintcallable functions (that have blueprint parameter) calls (in bp graph) into their never versions (with class param instead of blueprint).
- L325 _public member_ `FString ClassName;` — `UPROPERTY()`
- L328 _public member_ `FString OldFunctionName;` — `UPROPERTY()`
- L331 _public member_ `FString NewFunctionName;` — `UPROPERTY()`
- L334 _public member_ `FString BlueprintParamName;` — `UPROPERTY()`
- L337 _public member_ `FString ClassParamName;` — `UPROPERTY()`

#### struct `FAllowedMutableContainerFunction`  
`struct FAllowedMutableContainerFunction`  
_L341-360_
- reflection: `USTRUCT()`
- L346 _public member_ `TObjectPtr<UFunction> Function;` — `UPROPERTY()`
- L349 _public member_ `FString ContainerParameterName;` — `UPROPERTY()`
- L356 _public function_ `bool operator==(const FAllowedMutableContainerFunction& RHS) const`

#### enum `EObjectReferenceType`  
`enum class EObjectReferenceType : uint8`  
_L362-370_
- L364 _public enumerator_ `NotAnObject = 0x00`
- L365 _public enumerator_ `ObjectReference = 0x01`
- L366 _public enumerator_ `ClassReference = 0x02`
- L367 _public enumerator_ `SoftObject = 0x04`
- L368 _public enumerator_ `SoftClass = 0x08`
- L369 _public enumerator_ `AllTypes = 0x0f`

#### enum `ETypeTreeFilter`  
`enum class ETypeTreeFilter : uint8`  
_L375-382_
- desc: Filter flags for GetVariableTypeTree
- L377 _public enumerator_ `None = 0x00` — No Exec or Wildcards
- L378 _public enumerator_ `AllowExec = 0x01` — Include Executable pins
- L379 _public enumerator_ `AllowWildcard = 0x02` — Include Wildcard pins
- L380 _public enumerator_ `IndexTypesOnly = 0x04` — Exclude all pins that aren't index types
- L381 _public enumerator_ `RootTypesOnly = 0x08` — Exclude all pins that aren't root types

#### class `UEdGraphSchema_K2`  
`class UEdGraphSchema_K2 : public UEdGraphSchema`  
_L387-1301_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UEdGraphSchema`
- L392 _private member_ `static const FName PC_Exec;` — Allowable PinType.PinCategory values
- L393 _private member_ `static const FName PC_Boolean;`
- L394 _private member_ `static const FName PC_Byte;`
- L395 _private member_ `static const FName PC_Class;` — SubCategoryObject is the MetaClass of the Class passed thru this pin, or SubCategory can be 'self'. The DefaultValue string should always be empty, use DefaultObject.
- L396 _private member_ `static const FName PC_SoftClass;`
- L397 _private member_ `static const FName PC_Int;`
- L398 _private member_ `static const FName PC_Int64;`
- L399 _private member_ `static const FName PC_Float;`
- L400 _private member_ `static const FName PC_Double;`
- L401 _private member_ `static const FName PC_Real;`
- L402 _private member_ `static const FName PC_Name;`
- L403 _private member_ `static const FName PC_Delegate;` — SubCategoryObject is the UFunction of the delegate signature
- L404 _private member_ `static const FName PC_MCDelegate;` — SubCategoryObject is the UFunction of the delegate signature
- L405 _private member_ `static const FName PC_Object;` — SubCategoryObject is the Class of the object passed thru this pin, or SubCategory can be 'self'. The DefaultValue string should always be empty, use DefaultObject.
- L406 _private member_ `static const FName PC_Interface;` — SubCategoryObject is the Class of the object passed thru this pin.
- L407 _private member_ `static const FName PC_SoftObject;` — SubCategoryObject is the Class of the AssetPtr passed thru this pin.
- L408 _private member_ `static const FName PC_String;`
- L409 _private member_ `static const FName PC_Text;`
- L410 _private member_ `static const FName PC_Struct;` — SubCategoryObject is the ScriptStruct of the struct passed thru this pin, 'self' is not a valid SubCategory. DefaultObject should always be empty, the DefaultValue string may be used for supported structs.
- L411 _private member_ `static const FName PC_Wildcard;` — Special matching rules are imposed by the node itself
- L412 _private member_ `static const FName PC_Enum;` — SubCategoryObject is the UEnum object passed thru this pin
- L413 _private member_ `static const FName PC_FieldPath;` — SubCategoryObject is the Class of the property passed thru this pin.
- L416 _private member_ `static const FName PSC_Self;` — Common PinType.PinSubCategory values
- L418 _private member_ `static const FName PSC_Index;` — Category=PC_Wildcard, indicates the wildcard will only accept Int, Bool, Byte and Enum pins (used when a pin represents indexing a list)
- L419 _private member_ `static const FName PSC_Bitmask;` — Category=PC_Byte or PC_Int, indicates that the pin represents a bitmask field. SubCategoryObject is either NULL or the UEnum object to which the bitmap is linked for bitflag name specification.
- L422 _private member_ `static const FName PN_Execute;` — Pin names that have special meaning and required types in some contexts (depending on the node type)
- L423 _private member_ `static const FName PN_Then;` — Category=PC_Exec, singleton, output
- L424 _private member_ `static const FName PN_Completed;` — Category=PC_Exec, singleton, output
- L425 _private member_ `static const FName PN_DelegateEntry;` — Category=PC_Exec, singleton, output; entry point for a dynamically bound delegate
- L426 _private member_ `static const FName PN_EntryPoint;` — entry point to the ubergraph
- L427 _private member_ `static const FName PN_Self;` — Category=PC_Object, singleton, input
- L428 _private member_ `static const FName PN_Else;` — Category=PC_Exec, singleton, output
- L429 _private member_ `static const FName PN_Loop;` — Category=PC_Exec, singleton, output
- L430 _private member_ `static const FName PN_After;` — Category=PC_Exec, singleton, output
- L431 _private member_ `static const FName PN_ReturnValue;` — Category=PC_Object, singleton, output
- L432 _private member_ `static const FName PN_ObjectToCast;` — Category=PC_Object, singleton, input
- L433 _private member_ `static const FName PN_Condition;` — Category=PC_Boolean, singleton, input
- L434 _private member_ `static const FName PN_Start;` — Category=PC_Int, singleton, input
- L435 _private member_ `static const FName PN_Stop;` — Category=PC_Int, singleton, input
- L436 _private member_ `static const FName PN_Index;` — Category=PC_Int, singleton, output
- L437 _private member_ `static const FName PN_Item;` — Category=PC_Int, singleton, output
- L438 _private member_ `static const FName PN_CastSucceeded;` — Category=PC_Exec, singleton, output
- L439 _private member_ `static const FName PN_CastFailed;` — Category=PC_Exec, singleton, output
- L440 _private member_ `static const FString PN_CastedValuePrefix;` — Category=PC_Object, singleton, output; actual pin name varies depending on the type to be casted to, this is just a prefix
- L443 _private member_ `static const FName FN_UserConstructionScript;` — construction script function names
- L444 _private member_ `static const FName FN_ExecuteUbergraphBase;`
- L452 _private member_ `static const FName GN_EventGraph;` — graph names
- L453 _private member_ `static const FName GN_AnimGraph;`
- L456 _private member_ `static const FText VR_DefaultCategory;` — variable names
- L459 _private member_ `static const int32 AG_LevelReference;` — action grouping values
- L462 _private member_ `static bool bGeneratingDocumentation;` — Somewhat hacky mechanism to prevent tooltips created for pins from including the display name and type when generating BP API documentation
- L465 _private member_ `static int32 CurrentCacheRefreshID;` — ID for checking dirty status of node titles against, increases every compile
- L468 _private member_ `static const FName AllObjectTypes;` — Pin Selector category for all object types
- L471 _private member_ `TArray<FBlueprintCallableFunctionRedirect> EditoronlyBPFunctionRedirects;` — `UPROPERTY(globalconfig)`
- L474 _private member_ `bool bEnableMutableContainerWarnings;` — `UPROPERTY(globalconfig)`
- L477 _private member_ `TSet<FAllowedMutableContainerFunction> AllowedMutableContainerFunctions;` — `UPROPERTY(globalconfig)`
- L564 _public prototype_ `void SelectAllNodesInDirection(TEnumAsByte<enum EEdGraphPinDirection> InDirection, UEdGraph* Graph, UEdGraphPin* InGraphPin);`
- L567 _public prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L568 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L569 _public prototype_ `virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;`
- L570 _public prototype_ `virtual bool CreateAutomaticConversionNodeAndConnections(UEdGraphPin* A, UEdGraphPin* B) const override;`
- L571 _public prototype_ `virtual bool CreatePromotedConnection(UEdGraphPin* A, UEdGraphPin* B) const override;`
- L572 _public prototype_ `virtual FString IsPinDefaultValid(const UEdGraphPin* Pin, const FString& NewDefaultValue, TObjectPtr<UObject> NewDefaultObject, const FText& InNewDefaultText) const override;`
- L573 _public prototype_ `virtual bool DoesSupportPinWatching() const override;`
- L574 _public prototype_ `virtual bool IsPinBeingWatched(UEdGraphPin const* Pin) const override;`
- L575 _public prototype_ `virtual void ClearPinWatch(UEdGraphPin const* Pin) const override;`
- L576 _public prototype_ `virtual void TrySetDefaultValue(UEdGraphPin& Pin, const FString& NewDefaultValue, bool bMarkAsModified = true) const override;`
- L577 _public prototype_ `virtual void TrySetDefaultObject(UEdGraphPin& Pin, UObject* NewDefaultObject, bool bMarkAsModified = true) const override;`
- L578 _public prototype_ `virtual void TrySetDefaultText(UEdGraphPin& InPin, const FText& InNewDefaultText, bool bMarkAsModified = true) const override;`
- L579 _public prototype_ `virtual bool DoesDefaultValueMatchAutogenerated(const UEdGraphPin& InPin) const override;`
- L580 _public prototype_ `virtual void ResetPinToAutogeneratedDefaultValue(UEdGraphPin* Pin, bool bCallModifyCallbacks = true) const override;`
- L581 _public prototype_ `virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;`
- L582 _public prototype_ `virtual bool ShouldShowAssetPickerForPin(UEdGraphPin* Pin) const override;`
- L583 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L584 _public prototype_ `virtual FLinearColor GetSecondaryPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L585 _public prototype_ `virtual FText GetPinDisplayName(const UEdGraphPin* Pin) const override;`
- L586 _public prototype_ `virtual void ConstructBasicPinTooltip(const UEdGraphPin& Pin, const FText& PinDescription, FString& TooltipOut) const override;`
- L587 _public prototype_ `virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;`
- L588 _public prototype_ `virtual bool IsTitleBarPin(const UEdGraphPin& Pin) const override;`
- L589 _public prototype_ `virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;`
- L590 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L591 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L592 _public prototype_ `virtual void ReconstructNode(UEdGraphNode& TargetNode, bool bIsBatchRequest=false) const override;`
- L593 _public prototype_ `virtual bool CanEncapuslateNode(UEdGraphNode const& TestNode) const override;`
- L594 _public prototype_ `virtual void HandleGraphBeingDeleted(UEdGraph& GraphBeingRemoved) const override;`
- L595 _public prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;`
- L596 _public prototype_ `virtual void DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;`
- L597 _public prototype_ `virtual void DroppedAssetsOnNode(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraphNode* Node) const override;`
- L598 _public prototype_ `virtual void DroppedAssetsOnPin(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraphPin* Pin) const override;`
- L599 _public prototype_ `virtual void GetAssetsPinHoverMessage(const TArray<FAssetData>& Assets, const UEdGraphPin* HoverPin, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L600 _public prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L601 _public prototype_ `virtual bool CanDuplicateGraph(UEdGraph* InSourceGraph) const override;`
- L602 _public prototype_ `virtual UEdGraph* DuplicateGraph(UEdGraph* GraphToDuplicate) const override;`
- L603 _public prototype_ `virtual UEdGraphNode* CreateSubstituteNode(UEdGraphNode* Node, const UEdGraph* Graph, FObjectInstancingGraph* InstanceGraph, TSet<FName>& InOutExtraNames) const override;`
- L604 _public prototype_ `virtual int32 GetNodeSelectionCount(const UEdGraph* Graph) const override;`
- L605 _public prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetCreateCommentAction() const override;`
- L606 _public prototype_ `virtual bool FadeNodeWhenDraggingOffPin(const UEdGraphNode* Node, const UEdGraphPin* Pin) const override;`
- L607 _public prototype_ `virtual void BackwardCompatibilityNodeConversion(UEdGraph* Graph, bool bOnlySafeChanges) const override;`
- L608 _public function_ `virtual bool ShouldAlwaysPurgeOnModification() const override`
- L609 _public prototype_ `virtual void SplitPin(UEdGraphPin* Pin, bool bNotify = true) const override;`
- L610 _public prototype_ `virtual void RecombinePin(UEdGraphPin* Pin) const override;`
- L611 _public prototype_ `virtual void OnPinConnectionDoubleCicked(UEdGraphPin* PinA, UEdGraphPin* PinB, const FVector2f& GraphPosition) const override;`
- L612 _public prototype_ `virtual UEdGraphPin* DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const override;`
- L613 _public prototype_ `virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const override;`
- L614 _public prototype_ `virtual bool IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const override;`
- L615 _public prototype_ `virtual int32 GetCurrentVisualizationCacheID() const override;`
- L616 _public prototype_ `virtual void ForceVisualizationCacheClear() const override;`
- L617 _public prototype_ `virtual bool SafeDeleteNodeFromGraph(UEdGraph* Graph, UEdGraphNode* NodeToDelete) const override;`
- L618 _public function_ `virtual bool CanVariableBeDropped(UEdGraph* InGraph, FProperty* InVariableToDrop) const override`
- L619 _public prototype_ `virtual bool CanShowDataTooltipForPin(const UEdGraphPin& Pin) const override;`
- L622 _public prototype_ `virtual float GetActionFilteredWeight(const FEdGraphSchemaAction& InCurrentAction, const TArray<FString>& InFilterTerms, const TArray<FString>& InSanitizedFilterTerms, const TArray<UEdGraphPin*>& DraggedFromPins) const override;`
- L625 _public prototype_ `virtual float GetActionFilteredWeight(const FGraphActionListBuilderBase::ActionGroup& InCurrentAction, const TArray<FString>& InFilterTerms, const TArray<FString>& InSanitizedFilterTerms, const TArray<UEdGraphPin*>& DraggedFromPins) const override;` — `UE_DEPRECATED(5.5, "FGraphActionListBuilderBase::ActionGroup weight calculation was always performed on the first action, provide that if scoring a FGraphActionListBuilderBase::ActionGroup, or just provide the FEdGraphSchemaAction")`
- L627 _public prototype_ `virtual FGraphSchemaSearchWeightModifiers GetSearchWeightModifiers() const override;`
- L637 _public function_ `virtual bool DoesSupportCollapsedNodes() const` — Determine if this graph supports collapsing nodes into subgraphs @return True if this schema supports collapsed node subgraphs
- L645 _public function_ `virtual bool DoesSupportEventDispatcher() const` — Determine if this graph supports event dispatcher @return True if this schema supports Event Dispatcher
- L655 _public prototype_ `static void ConfigureVarNode(class UK2Node_Variable* InVarNode, FName InVariableName, UStruct* InVariableSource, UBlueprint* InTargetBlueprint);` — Configure the supplied variable node based on the supplied info @param	InVarNode			The variable node to be configured @param	InVariableName		The name of the current variable @param	InVaraiableSource	The source of the variable @param	InTargetBlueprint	The blueprint this node will be used on
- L666 _public prototype_ `virtual class UK2Node_VariableGet* SpawnVariableGetNode(const FVector2D GraphPosition, class UEdGraph* ParentGraph, FName VariableName, UStruct* Source) const;` — Creates a new variable getter node and adds it to ParentGraph @param	GraphPosition		The location of the new node inside the graph @param	ParentGraph			The graph to spawn the new node in @param	VariableName		The name of the variable @param	Source				The source of the variable @return	A pointer to the newly spawned node
- L677 _public prototype_ `virtual class UK2Node_VariableSet* SpawnVariableSetNode(const FVector2D GraphPosition, class UEdGraph* ParentGraph, FName VariableName, UStruct* Source) const;` — Creates a new variable setter node and adds it to ParentGraph @param	GraphPosition		The location of the new node inside the graph @param	ParentGraph			The graph to spawn the new node in @param	VariableName		The name of the variable @param	Source				The source of the variable @return	A pointer to the newly spawned node
- L680 _public prototype_ `bool PinHasSplittableStructType(const UEdGraphPin* InGraphPin) const;` — Returns whether the supplied Pin is a splittable struct
- L683 _public prototype_ `bool PinDefaultValueIsEditable(const UEdGraphPin& InGraphPin) const;` — Returns true if the pin has a value field that can be edited inline
- L686 _public prototype_ `bool PinHasCustomDefaultFormat(const UEdGraphPin& InGraphPin) const;` — Returns true if the pin has a custom default string format and it is not safe to use ExportText
- L709 _public prototype_ `UK2Node* CreateSplitPinNode(UEdGraphPin* Pin, const FCreateSplitPinNodeParams& Params) const;` — Helper function to create the expansion node. If the CompilerContext is specified this will be created as an intermediate node
- L712 _public prototype_ `virtual void GetPinDefaultValuesFromString(const FEdGraphPinType& PinType, UObject* OwningObject, const FString& NewValue, FString& UseDefaultValue, TObjectPtr<UObject>& UseDefaultObject, FText& UseDefaultText, bool bPreserveTextIdentity = true) const;` — Reads in a FString and gets the values of the pin defaults for that type. This can be passed to DefaultValueSimpleValidation to validate. OwningObject can be null
- L715 _public prototype_ `virtual bool DefaultValueSimpleValidation(const FEdGraphPinType& PinType, const FName PinName, const FString& NewDefaultValue, TObjectPtr<UObject> NewDefaultObject, const FText& InText, FString* OutMsg = nullptr) const;` — Do validation, that doesn't require a knowledge about actual pin
- L718 _public prototype_ `static bool IsAutoCreateRefTerm(const UEdGraphPin* Pin);` — Returns true if the owning node is a function with AutoCreateRefTerm meta data
- L721 _public prototype_ `bool ClassHasBlueprintAccessibleMembers(const UClass* InClass) const;` — See if a class has any members that are accessible by a blueprint
- L729 _public prototype_ `static bool IsConstructionScript(const UEdGraph* TestEdGraph);` — Checks to see if the specified graph is a construction script @param	TestEdGraph		Graph to test @return	true if this is a construction script
- L737 _public prototype_ `bool IsCompositeGraph(const UEdGraph* TestEdGraph) const;` — Checks to see if the specified graph is a composite graph @param	TestEdGraph		Graph to test @return	true if this is a composite graph
- L746 _public prototype_ `bool IsConstFunctionGraph(const UEdGraph* TestEdGraph, bool* bOutIsEnforcingConstCorrectness = nullptr) const;` — Checks to see if the specified graph is a const function graph @param	TestEdGraph		Graph to test @param	bOutIsEnforcingConstCorrectness (Optional) Whether or not this graph is enforcing const correctness during compilation @return	true if this is a const function graph
- L754 _public prototype_ `bool IsStaticFunctionGraph(const UEdGraph* TestEdGraph) const;` — Checks to see if the specified graph is a static function graph @param	TestEdGraph		Graph to test @return	true if this is a const function graph
- L762 _public function_ `static inline bool IsExecPin(const UEdGraphPin& Pin)` — Checks to see if a pin is an execution pin. @param	Pin	The pin to check. @return	true if it is an execution pin.
- L773 _public prototype_ `virtual bool IsSelfPin(const UEdGraphPin& Pin) const override;` — Checks to see if a pin is a Self pin (indicating the calling context for the node) @param	Pin	The pin to check. @return	true if it is a Self pin.
- L781 _public function_ `inline bool IsMetaPin(const UEdGraphPin& Pin) const` — Checks to see if a pin is a meta-pin (either a Self or Exec pin) @param	Pin	The pin to check. @return	true if it is a Self or Exec pin.
- L787 _public prototype_ `virtual bool IsDelegateCategory(const FName Category) const override;` — Is given string a delegate category name ?
- L790 _public function_ `inline bool IsIndexWildcardCompatible(const FEdGraphPinType& PinType) const` — Returns whether a pin category is compatible with an Index Wildcard (PC_Wildcard and PSC_Index)
- L809 _public function_ `UEdGraphPin* FindExecutionPin(const UEdGraphNode& Node, EEdGraphPinDirection PinDirection) const` — Searches for the first execution pin with the specified direction on the node @param	Node			The node to search. @param	PinDirection	The required pin direction. @return	the first found execution pin with the correct direction or null if there were no matching pins.
- L832 _public function_ `UEdGraphPin* FindSelfPin(const UEdGraphNode& Node, EEdGraphPinDirection PinDirection) const` — Searches for the first Self pin with the specified direction on the node @param	Node			The node to search. @param	PinDirection	The required pin direction. @return	the first found self pin with the correct direction or null if there were no matching pins.
- L848 _public prototype_ `bool CanPromotePinToVariable (const UEdGraphPin& Pin, bool bInToMemberVariable) const;` — Can Pin be promoted to a variable?
- L851 _public prototype_ `bool CanSplitStructPin(const UEdGraphPin& Pin) const;` — Can Pin be split in to its component elements
- L854 _public prototype_ `bool CanRecombineStructPin(const UEdGraphPin& Pin) const;` — Can Pin be recombined back to its original form
- L861 _public prototype_ `static bool GetPropertyCategoryInfo(const FProperty* TestProperty, FName& OutCategory, FName& OutSubCategory, UObject*& OutSubCategoryObject, bool& bOutIsWeakPointer);` — Helper function for filling out Category, SubCategory, and SubCategoryObject based on a FProperty @return	true on success, false if the property is unsupported or invalid.
- L871 _public prototype_ `bool ConvertPropertyToPinType(const FProperty* Property, FEdGraphPinType& TypeOut) const;` — Convert the type of a FProperty to the corresponding pin type. @param		Property	The property to convert. @param [out]	TypeOut		The resulting pin type. @return	true on success, false if the property is unsupported or invalid.
- L874 _public prototype_ `static bool HasWildcardParams(const UFunction* Function);` — Returns true if the function has wildcard parameters, e.g. uses runtime type information that may require safe failure handling
- L877 _public prototype_ `static bool IsWildcardProperty(const FProperty* ParamProperty);` — Determines if the specified param property is intended to be used as a wildcard (for custom thunk functions, like in our array library, etc.)
- L894 _public prototype_ `static UFunction* GetCallableParentFunction(UFunction* Function);` — Finds the parent function for the specified function, if any @param	Function			The function to find a parent function for @return	The UFunction parentfunction, if any.
- L897 _public prototype_ `bool IsActorValidForLevelScriptRefs(const AActor* TestActor, const UBlueprint* Blueprint) const;` — Whether or not the specified actor is a valid target for bound events and literal references (in the right level, not a builder brush, etc
- L905 _public prototype_ `void AddSelectedReplaceableNodes(FToolMenuSection& Section, UBlueprint* Blueprint, const UEdGraphNode* InGraphNode) const;` — Generate a list of replaceable nodes for context menu based on the editor's current selection @param	Reference to graph node @param	Reference to context menu builder
- L913 _public prototype_ `void ReplaceSelectedNode(UEdGraphNode* SourceNode, AActor* TargetActor);` — Function to replace current graph node reference object with a new object @param Reference to graph node @param Reference to new reference object
- L916 _public prototype_ `static bool FunctionCanBePlacedAsEvent(const UFunction* InFunction);` — Returns whether a function is marked 'override' and doesn't have any out parameters
- L919 _public prototype_ `static bool FunctionCanBeUsedInDelegate(const UFunction* InFunction);` — Can this function be called by kismet delegate
- L922 _public prototype_ `static bool CanUserKismetCallFunction(const UFunction* Function);` — Can this function be called by kismet code
- L925 _public prototype_ `static bool HasFunctionAnyOutputParameter(const UFunction* Function);` — Returns if function has output parameter(s)
- L935 _public prototype_ `static bool CanUserKismetAccessVariable(const FProperty* Property, const UClass* InClass, EDelegateFilterMode FilterMode);` — Can this variable be accessed by kismet code
- L938 _public prototype_ `static bool CanKismetOverrideFunction(const UFunction* Function);` — Can this function be overridden by kismet (either placed as event or new function graph created)
- L941 _public prototype_ `static FText GetFriendlySignatureName(const UFunction* Function);` — returns friendly signature name if possible or Removes any mangling to get the unmangled signature name of the function
- L944 _public prototype_ `static bool IsAllowableBlueprintVariableType(const UEnum* InEnum);` — Returns true if this enum is safe to be used as a variable in blueprints
- L951 _public prototype_ `static bool IsAllowableBlueprintVariableType(const UClass* InClass, bool bAssumeBlueprintType = false);` — Returns true if this class is safe to be used as a variable in blueprints @param	bImpliedBlueprintType	If true, the class is implied to be a blueprint type and will be allowed unless it is specifically forbidden
- L958 _public prototype_ `static bool IsAllowableBlueprintVariableType(const UScriptStruct *InStruct, bool bForInternalUse = false);` — Returns true if this struct is safe to to be used as a variable in blueprints @param	bForInternalUse			If true, the struct is for internal usage so BlueprintInternalUseOnly is allowed
- L960 _public prototype_ `static bool IsPropertyExposedOnSpawn(const FProperty* Property);`
- L963 _public prototype_ `static bool IsPropertyDeprecated(const FProperty* Property);` — returns whether the property is deprecated.
- L971 _public prototype_ `static void GetAutoEmitTermParameters(const UFunction* Function, TArray<FString>& AutoEmitParameterNames);` — Returns a list of parameters for the function that are specified as automatically emitting terms for unconnected ref parameters in the compiler (MD_AutoCreateRefTerm) @param	Function				The function to check for auto-emitted ref terms on @param	AutoEmitParameterNames	(out) Returns an array of param names that should be auto-emitted if nothing is connected
- L983 _public prototype_ `bool FunctionHasParamOfType(const UFunction* InFunction, UEdGraph const* InGraph, const FEdGraphPinType& DesiredPinType, bool bWantOutput) const;` — Determine if a function has a parameter of a specific type. @param	InFunction	  	The function to search. @param	InGraph			The graph that you're looking to call the function from (some functions hide different pins depending on the graph they're in) @param	DesiredPinType	The type that at least one function parameter needs to be. @param	bWantOutput   	The direction that the parameter needs to be. @return	true if at least one parameter is of the correct type and direction.
- L991 _public prototype_ `void AddExtraFunctionFlags(const UEdGraph* CurrentGraph, int32 ExtraFlags) const;` — Add the specified flags to the function entry node of the graph, to make sure they get compiled in to the generated function @param	CurrentGraph	The graph of the function to modify the flags for @param	ExtraFlags		The flags to add to the function entry node
- L999 _public prototype_ `void MarkFunctionEntryAsEditable(const UEdGraph* CurrentGraph, bool bNewEditable) const;` — Marks the function entry of a graph as editable via function editor or not-editable @param	CurrentGraph	The graph of the function to modify the entry node for @param	bNewEditable	Whether or not the function entry for the graph should be editable via the function editor
- L1007 _public prototype_ `virtual void CreateMacroGraphTerminators(UEdGraph& Graph, UClass* Class) const;` — Populate new macro graph with entry and possibly return node @param	Graph			Graph to add the function terminators to @param	ContextClass	If specified, the graph terminators will use this class to search for context for signatures (i.e. interface functions)
- L1015 _public prototype_ `virtual void CreateFunctionGraphTerminators(UEdGraph& Graph, UClass* Class) const;` — Populate new function graph with entry and possibly return node @param	Graph			Graph to add the function terminators to @param	ContextClass	If specified, the graph terminators will use this class to search for context for signatures (i.e. interface functions)
- L1023 _public prototype_ `virtual void CreateFunctionGraphTerminators(UEdGraph& Graph, const UFunction* FunctionSignature) const;` — Populate new function graph with entry and possibly return node @param	Graph			Graph to add the function terminators to @param	FunctionSignature	The function signature to mimic when creating the inputs and outputs for the function.
- L1032 _public prototype_ `static FText TypeToText(const FProperty* const Property);` — Converts the type of a property into a fully qualified string (e.g., object'ObjectName'). @param	Property	The property to convert into a string. @return	The converted type string.
- L1045 _public prototype_ `static FText TerminalTypeToText(const FName Category, const FName SubCategory, UObject* SubCategoryObject, bool bIsWeakPtr);` — Converts a terminal type into a fully qualified FText (e.g., object'ObjectName'). Primarily used as a helper when converting containers to TypeToText. @param	Category					The category to convert into a FText. @param	SubCategory					The subcategory to convert into FText @param	SubCategoryObject			The SubcategoryObject to convert into FText @param	bIsWeakPtr					Whether the type is a WeakPtr @return	The converted type text.
- L1054 _public prototype_ `static FText TypeToText(const FEdGraphPinType& Type);` — Converts a pin type into a fully qualified FText (e.g., object'ObjectName'). @param	Type	The type to convert into a FText. @return	The converted type text.
- L1064 _public prototype_ `static FText GetCategoryText(const FName Category, const bool bForMenu = false);` — Returns the FText to use for a given schema category @param	Category	The category to convert into a FText. @param	bForMenu	Indicates if this is for display in tooltips or menu @return	The text to display for the category.
- L1075 _public prototype_ `static FText GetCategoryText(FName Category, FName SubCategory, bool bForMenu = false);` — Returns the FText to use for a given schema category and subcategory @param	Category	The category to convert into a FText. @param	SubCategory	The subcategory to convert into a FText. @param	bForMenu	Indicates if this is for display in tooltips or menu @return	The text to display for the category.
- L1083 _public prototype_ `virtual void GetVariableTypeTree(TArray< TSharedPtr<FPinTypeTreeInfo> >& TypeTree, ETypeTreeFilter TypeTreeFilter = ETypeTreeFilter::None) const;` — Get the type tree for all of the property types valid for this schema @param	TypeTree		The array that will contain the type tree hierarchy for this schema upon returning @param	TypeTreeFilter	ETypeTreeFilter flags that determine how the TypeTree is populated.
- L1090 _public prototype_ `bool DoesTypeHaveSubtypes( const FName Category ) const;` — Returns whether or not the specified type has valid subtypes available @param	Type	The type to check for subtypes
- L1103 _public prototype_ `virtual bool ArePinsCompatible(const UEdGraphPin* PinA, const UEdGraphPin* PinB, const UClass* CallingContext = NULL, bool bIgnoreArray = false) const override;` — Returns true if the types and directions of two pins are schema compatible. Handles outputting a more derived type to an input pin expecting a less derived type. @param	PinA		  	The pin a. @param	PinB		  	The pin b. @param	CallingContext	(optional) The calling context (required to properly evaluate pins of type Self) @param	bIgnoreArray	(optional) Whether or not to ignore differences between array and non-array types @return	true if the pin types and directions are compatible.
- L1116 _public prototype_ `virtual const FPinConnectionResponse DetermineConnectionResponseOfCompatibleTypedPins(const UEdGraphPin* PinA, const UEdGraphPin* PinB, const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin) const;` — Returns the connection response for connecting PinA to PinB, which have already been determined to be compatible types with a compatible direction.  InputPin and OutputPin are PinA and PinB or vis versa, indicating their direction. @param	PinA		  	The pin a. @param	PinB		  	The pin b. @param	InputPin	  	Either PinA or PinB, depending on which one is the input. @param	OutputPin	  	Either PinA or PinB, depending on which one is the output. @return	The message and action to take on trying to make this connection.
- L1129 _public prototype_ `virtual bool ArePinTypesCompatible(const FEdGraphPinType& Output, const FEdGraphPinType& Input, const UClass* CallingContext = NULL, bool bIgnoreArray = false) const;` — Returns true if the two pin types are schema compatible.  Handles outputting a more derived type to an input pin expecting a less derived type. @param	Output		  	The output type. @param	Input		  	The input type. @param	CallingContext	(optional) The calling context (required to properly evaluate pins of type Self) @param	bIgnoreArray	(optional) Whether or not to ignore differences between array and non-array types @return	true if the pin types are compatible.
- L1139 _public prototype_ `virtual bool ArePinTypesEquivalent(const FEdGraphPinType& PinA, const FEdGraphPinType& PinB) const;` — Returns true if the types are schema Equivalent. @param	PinA		  	The type of Pin A. @param	PinB		  	The type of Pin B. @return	true if the pin types and directions are compatible.
- L1142 _public prototype_ `virtual void SetPinAutogeneratedDefaultValue(UEdGraphPin* Pin, const FString& NewValue) const;` — Sets the autogenerated default value for a pin, optionally using the passed in function and parameter. This will also reset the current default value to the autogenerated one
- L1145 _public prototype_ `virtual void SetPinAutogeneratedDefaultValueBasedOnType(UEdGraphPin* Pin) const;` — Sets the autogenerated default value for a pin using the default for that type. This will also reset the current default value to the autogenerated one
- L1148 _public prototype_ `virtual void SetPinDefaultValueAtConstruction(UEdGraphPin* Pin, const FString& DefaultValueString) const;` — Sets the pin defaults, but not autogenerated defaults, at pin construction time. This is like TrySetDefaultValue but does not do validation or callbacks
- L1151 _public prototype_ `virtual void HandleParameterDefaultValueChanged(UK2Node* TargetNode) const;` — Call to let blueprint and UI know that parameters have changed for a function/macro/etc
- L1154 _public prototype_ `static bool FindFunctionParameterDefaultValue(const UFunction* Function, const FProperty* Param, FString& OutString);` — Given a function and property, return the default value
- L1157 _public prototype_ `static void ValidateExistingConnections(UEdGraphPin* Pin);` — Utility that makes sure existing connections are valid, breaking any that are now illegal.
- L1160 _public prototype_ `static UFunction* FindSetVariableByNameFunction(const FEdGraphPinType& PinType);` — Find a 'set value by name' function for the specified pin, if it exists
- L1168 _public prototype_ `[[nodiscard]] virtual TOptional<FSearchForAutocastFunctionResults> SearchForAutocastFunction(const FEdGraphPinType& OutputPinType, const FEdGraphPinType& InputPinType) const;`
- L1175 _public prototype_ `[[nodiscard]] virtual TOptional<FFindSpecializedConversionNodeResults> FindSpecializedConversionNode(const FEdGraphPinType& OutputPinType, const UEdGraphPin& InputPin, bool bCreateNode) const;`
- L1178 _public prototype_ `void GetNonExistentVariableMenu(FToolMenuSection& Section, const UEdGraphNode* InGraphNode, UBlueprint* OwnerBlueprint) const;` — Create menu for variable get/set nodes which refer to a variable which does not exist.
- L1188 _public prototype_ `void GetReplaceVariableMenu(FToolMenuSection& Section, const UEdGraphNode* InGraphNode, UBlueprint* InOwnerBlueprint, bool bInReplaceExistingVariable = false) const;` — Create menu for variable get/set nodes which allows for the replacement of variables @param InGraphNode					Variable node to replace @param InOwnerBlueprint				The owning Blueprint of the variable @param InMenuBuilder					MenuBuilder to place the menu items into @param bInReplaceExistingVariable	TRUE if replacing an existing variable, will keep the variable from appearing on the list
- L1191 _public prototype_ `static FVector2D CalculateAveragePositionBetweenNodes(UEdGraphPin* InputPin, UEdGraphPin* OutputPin);` — Calculates an average position between the nodes owning the two specified pins
- L1194 _public prototype_ `void AutowireConversionNode(UEdGraphPin* InputPin, UEdGraphPin* OutputPin, UEdGraphNode* ConversionNode) const;` — Tries to connect any pins with matching types and directions from the conversion node to the specified input and output pins
- L1197 _public prototype_ `static float EstimateNodeHeight( UEdGraphNode* Node );` — Calculates an estimated height for the specified node
- L1200 _public prototype_ `static float EstimateNodeWidth( const UEdGraphNode* Node );` — Calculates an estimated width for the specified node
- L1209 _public prototype_ `bool DoesGraphSupportImpureFunctions(const UEdGraph* InGraph) const;` — Checks if the graph supports impure functions @param InGraph		Graph to check @return				True if the graph supports impure functions
- L1216 _public prototype_ `bool IsGraphMarkedThreadSafe(const UEdGraph* InGraph) const;` — Checks if the graph is marked as thread safe @param InGraph		Graph to check @return			True if the graph is marked theead safe
- L1228 _public prototype_ `bool CanFunctionBeUsedInGraph(const UClass* InClass, const UFunction* InFunction, const UEdGraph* InDestGraph, uint32 InFunctionTypes, bool bInCalledForEach, FText* OutReason = nullptr) const;` — Checks to see if the passed in function is valid in the graph for the current class @param	InClass  			Class being checked to see if the function is valid for @param	InFunction			Function being checked @param	InDestGraph			Graph we will be using action for (may be NULL) @param	InFunctionTypes		Combination of EFunctionType to indicate types of functions accepted @param	bInCalledForEach	Call for each element in an array (a node accepts array) @param	OutReason			Allows callers to receive a localized string containing more detail when the function is determined to be invalid (optional)
- L1241 _public prototype_ `bool CollapseGatewayNode(UK2Node* InNode, UEdGraphNode* InEntryNode, UEdGraphNode* InResultNode, class FKismetCompilerContext* CompilerContext = nullptr, TSet<UEdGraphNode*>* OutExpandedNodes = nullptr) const;` — Makes connections into/or out of the gateway node, connect directly to the associated networks on the opposite side of the tunnel When done, none of the pins on the gateway node will be connected to anything. Requires both this gateway node and it's associated node to be in the same graph already (post-merging) @param InGatewayNode			The function or tunnel node @param InEntryNode			The entry node in the inner graph @param InResultNode			The result node in the inner graph @return						Returns TRUE if successful
- L1248 _public prototype_ `void CombineTwoPinNetsAndRemoveOldPins(UEdGraphPin* InPinA, UEdGraphPin* InPinB) const;` — Connects all of the linked pins from PinA to all of the linked pins from PinB, removing both PinA and PinB from being linked to anything else Requires the nodes that own the pins to be in the same graph already (post-merging)
- L1253 _public prototype_ `void LinkDataPinFromOutputToInput(UEdGraphNode* InOutputNode, UEdGraphNode* InInputNode) const;` — Make links from all data pins from InOutputNode output to InInputNode input.
- L1256 _public prototype_ `bool ReplaceOldNodeWithNew(UEdGraphNode* OldNode, UEdGraphNode* NewNode, const TMap<FName, FName>& OldPinToNewPinMap) const;` — Moves all connections from the old node to the new one. Returns true and destroys OldNode on success. Fails if it cannot find a mapping from an old pin.
- L1259 _public prototype_ `UK2Node* ConvertDeprecatedNodeToFunctionCall(UK2Node* OldNode, UFunction* NewFunction, TMap<FName, FName>& OldPinToNewPinMap, UEdGraph* Graph) const;` — Convert a deprecated node into a function call node, called from per-node ConvertDeprecatedNode
- L1262 _public function_ `virtual bool DoesSupportAnimNotifyActions() const` — some inherited schemas don't want anim-notify actions listed, so this is an easy way to check that
- L1268 _public prototype_ `static void OnCreateNonExistentVariable(class UK2Node_Variable* Variable, UBlueprint* OwnerBlueprint);` — Create the variable that the broken node refers to
- L1271 _public prototype_ `static void OnCreateNonExistentLocalVariable(class UK2Node_Variable* Variable, UBlueprint* OwnerBlueprint);` — Create the local variable that the broken node refers to
- L1274 _public prototype_ `static void OnReplaceVariableForVariableNode(class UK2Node_Variable* Variable, UBlueprint* OwnerBlueprint, FName VariableName, bool bIsSelfMember);` — Replace the variable that a variable node refers to when the variable it refers to does not exist
- L1277 _public prototype_ `static void GetReplaceVariableMenu(UToolMenu* Menu, class UK2Node_Variable* Variable, UBlueprint* OwnerBlueprint, bool bReplaceExistingVariable = false);` — Create sub menu that shows all possible variables that can be used to replace the existing variable reference
- L1280 _public prototype_ `static void Shutdown();` — Function called when the owning module is shut down
- L1283 _private prototype_ `static TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter(const UBlueprint* Blueprint);`
- L1290 _private prototype_ `bool DoesFunctionHaveOutParameters( const UFunction* Function ) const;` — Returns true if the specified function has any out parameters @param [in] Function	The function to check for out parameters @return true if there are out parameters, else false
- L1292 _private prototype_ `bool ShouldShowPanelContextMenuForIncompatibleConnectionsImpl() const override;`
- L1294 _private member_ `static const UScriptStruct* VectorStruct;`
- L1295 _private member_ `static const UScriptStruct* Vector3fStruct;`
- L1296 _private member_ `static const UScriptStruct* Vector2DStruct;`
- L1297 _private member_ `static const UScriptStruct* RotatorStruct;`
- L1298 _private member_ `static const UScriptStruct* TransformStruct;`
- L1299 _private member_ `static const UScriptStruct* LinearColorStruct;`
- L1300 _private member_ `static const UScriptStruct* ColorStruct;`

#### class `UEdGraphSchema_K2::FPinTypeTreeInfo`  
`class FPinTypeTreeInfo`  
_L484-561_
- desc: Class used for creating type tree selection info, which aggregates the various PC_* and PinSubtypes in the schema into a hierarchy
- L488 _private member_ `FEdGraphPinType PinType;` — The pin type corresponding to the schema type
- L489 _private member_ `uint8 PossibleObjectReferenceTypes;`
- L492 _private member_ `FAssetData CachedAssetData;` — Asset Data, used when PinType.PinSubCategoryObject is not loaded yet
- L495 _private member_ `FText CachedDescription;` — The pin type description, localized
- L498 _private member_ `TSharedPtr<FString> CachedDescriptionString;` — A copy of the localized CachedDescription string, for sorting
- L501 _public member_ `TArray< TSharedPtr<FPinTypeTreeInfo> > Children;` — The children of this pin type
- L504 _public member_ `bool bReadOnly;` — Whether or not this pin type is selectable as an actual type, or is just a category, with some subtypes
- L507 _public member_ `FText Tooltip;` — Text for regular tooltip
- L510 _public prototype_ `const FEdGraphPinType& GetPinType(bool bForceLoadedSubCategoryObject);`
- L511 _public function_ `const FEdGraphPinType& GetPinTypeNoResolve() const`
- L512 _public function_ `void SetPinSubTypeCategory(const FName SubCategory)`
- L517 _public prototype_ `FPinTypeTreeInfo(const FText& InFriendlyName, const FName CategoryName, const UEdGraphSchema_K2* Schema, const FText& InTooltip, bool bInReadOnly = false);`
- L518 _public prototype_ `FPinTypeTreeInfo(const FName CategoryName, UObject* SubCategoryObject, const FText& InTooltip, bool bInReadOnly = false, uint8 InPossibleObjectReferenceTypes = 0);`
- L519 _public prototype_ `FPinTypeTreeInfo(const FText& InFriendlyName, const FName CategoryName, const FAssetData& AssetData, const FText& InTooltip, bool bInReadOnly = false, uint8 InPossibleObjectReferenceTypes = 0);`
- L520 _public prototype_ `FPinTypeTreeInfo(TSharedPtr<FPinTypeTreeInfo> InInfo);`
- L523 _public prototype_ `const FText& GetDescription() const;` — Returns a succinct menu description of this type
- L526 _public function_ `const FString& GetCachedDescriptionString() const` — Returns the localized description as a string, for faster sorting
- L531 _public function_ `FText GetToolTip() const`
- L546 _public function_ `uint8 GetPossibleObjectReferenceTypes() const`
- L551 _public prototype_ `const FAssetData& GetCachedAssetData() const;`
- L555 _private function_ `FPinTypeTreeInfo() : PossibleObjectReferenceTypes(0) , bReadOnly(false)`
- L560 _private prototype_ `FText GenerateDescription();`

#### struct `UEdGraphSchema_K2::FCreateSplitPinNodeParams`  
`struct FCreateSplitPinNodeParams`  
_L688-705_
- L690 _public function_ `FCreateSplitPinNodeParams(const bool bInTransient) : CompilerContext(nullptr) , SourceGraph(nullptr) , bTransient(bInTransient)`
- L696 _public function_ `FCreateSplitPinNodeParams(class FKismetCompilerContext* InCompilerContext, UEdGraph* InSourceGraph) : CompilerContext(InCompilerContext) , SourceGraph(InSourceGraph) , bTransient(false)`
- L702 _public member_ `FKismetCompilerContext* CompilerContext;`
- L703 _public member_ `UEdGraph* SourceGraph;`
- L704 _public member_ `bool bTransient;`

#### enum `UEdGraphSchema_K2::EFunctionType`  
`enum EFunctionType`  
_L880-886_
- desc: Flags to indicate different types of blueprint callable functions
- L882 _public enumerator_ `FT_Imperative = 0x01`
- L883 _public enumerator_ `FT_Pure = 0x02`
- L884 _public enumerator_ `FT_Const = 0x04`
- L885 _public enumerator_ `FT_Protected = 0x08`

#### enum `UEdGraphSchema_K2::EDelegateFilterMode`  
`enum EDelegateFilterMode`  
_L927-932_
- L929 _public enumerator_ `CannotBeDelegate`
- L930 _public enumerator_ `MustBeDelegate`
- L931 _public enumerator_ `VariablesAndDelegates`

#### struct `UEdGraphSchema_K2::FSearchForAutocastFunctionResults`  
`struct FSearchForAutocastFunctionResults`  
_L1163-1167_
- desc: Find an appropriate function to call to perform an automatic cast operation
- L1165 _public member_ `FName TargetFunction;`
- L1166 _public member_ `UClass* FunctionOwner = nullptr;`

#### struct `UEdGraphSchema_K2::FFindSpecializedConversionNodeResults`  
`struct FFindSpecializedConversionNodeResults`  
_L1171-1174_
- desc: Find an appropriate node that can convert from one pin type to another (not a cast; e.g. "MakeLiteralArray" node)
- L1173 _public member_ `class UK2Node* TargetNode = nullptr;`

#### Free symbols / members of external scopes

- L37 _macro_ `#define UE_API BLUEPRINTGRAPH_API`
- L351 _function_ `friend uint32 GetTypeHash(const FAllowedMutableContainerFunction& Input)`
- L384 _prototype_ `ENUM_CLASS_FLAGS(ETypeTreeFilter);`

### `Source/Editor/BlueprintGraph/Classes/EdGraphSchema_K2_Actions.h` (Public)


#### enum `EK2NewNodeFlags`  
`enum class EK2NewNodeFlags`  
_L49-55_
- L51 _public enumerator_ `None = 0x0`
- L53 _public enumerator_ `SelectNewNode = 0x1`
- L54 _public enumerator_ `GotoNewNode = 0x2`

#### struct `FEdGraphSchemaAction_K2NewNode`  
`struct FEdGraphSchemaAction_K2NewNode : public FEdGraphSchemaAction`  
_L60-132_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a node to the graph
- L65 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L66 _public function_ `virtual FName GetTypeId() const override`
- L70 _public member_ `TObjectPtr<class UK2Node> NodeTemplate;` — `UPROPERTY()` — Template of node we want to create
- L73 _public member_ `bool bGotoNode;` — `UPROPERTY()`
- L75 _public function_ `FEdGraphSchemaAction_K2NewNode() : FEdGraphSchemaAction() , NodeTemplate(nullptr) , bGotoNode(false)`
- L81 _public function_ `FEdGraphSchemaAction_K2NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, FText InKeywords = FText()) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping, MoveTemp(InKeywords)) , NodeTemplate(nullptr) , bGotoNode(false)`
- L89 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L90 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L91 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L95 _public function_ `template <typename NodeType> static NodeType* SpawnNodeFromTemplate(class UEdGraph* ParentGraph, NodeType* InTemplateNode, const FVector2D Location, bool bSelectNewNode = true)`
- L106 _public function_ `template <typename NodeType> static NodeType* SpawnNode(class UEdGraph* ParentGraph, const FVector2D Location, EK2NewNodeFlags Options, TFunctionRef<void(NodeType*)> InitializerFn)`
- L125 _public function_ `template <typename NodeType> static NodeType* SpawnNode(class UEdGraph* ParentGraph, const FVector2D Location, EK2NewNodeFlags Options)`
- L130 _public prototype_ `static UEdGraphNode* CreateNode(UEdGraph* ParentGraph, TArrayView<UEdGraphPin*> FromPins, const FVector2D Location, UK2Node* NodeTemplate, EK2NewNodeFlags Options);`
- L131 _public prototype_ `static UEdGraphNode* CreateNode(UEdGraph* ParentGraph, TArrayView<UEdGraphPin*> FromPins, const FVector2D Location, TFunctionRef<UK2Node*(UEdGraph*)> ConstructionFn, TFunctionRef<void(UK2Node*)> InitializerFn, EK2NewNodeFlags Options);`

#### struct `FEdGraphSchemaAction_K2ViewNode`  
`struct FEdGraphSchemaAction_K2ViewNode : public FEdGraphSchemaAction`  
_L140-167_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to view a node to the graph
- L145 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L146 _public function_ `virtual FName GetTypeId() const override`
- L150 _public member_ `TObjectPtr<const UK2Node> NodePtr;` — `UPROPERTY()` — node we want to view
- L152 _public function_ `FEdGraphSchemaAction_K2ViewNode() : FEdGraphSchemaAction() , NodePtr(nullptr)`
- L157 _public function_ `FEdGraphSchemaAction_K2ViewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) , NodePtr(nullptr)`
- L163 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction interface
- L164 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FEdGraphSchemaAction_K2AssignDelegate`  
`struct FEdGraphSchemaAction_K2AssignDelegate : public FEdGraphSchemaAction_K2NewNode`  
_L175-195_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction_K2NewNode`
- desc: Action to add a node to the graph
- L179 _public function_ `static FName StaticGetTypeId()`
- L180 _public function_ `virtual FName GetTypeId() const override`
- L182 _public function_ `FEdGraphSchemaAction_K2AssignDelegate() :FEdGraphSchemaAction_K2NewNode()`
- L186 _public function_ `FEdGraphSchemaAction_K2AssignDelegate(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction_K2NewNode(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L191 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction interface
- L194 _public prototype_ `static UEdGraphNode* AssignDelegate(class UK2Node* NodeTemplate, class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode);`

#### struct `FEdGraphSchemaAction_EventFromFunction`  
`struct FEdGraphSchemaAction_EventFromFunction : public FEdGraphSchemaAction`  
_L203-228_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a node to the graph
- L207 _public function_ `static FName StaticGetTypeId()`
- L208 _public function_ `virtual FName GetTypeId() const override`
- L211 _public member_ `TObjectPtr<class UFunction> SignatureFunction;` — `UPROPERTY()`
- L213 _public function_ `FEdGraphSchemaAction_EventFromFunction() :FEdGraphSchemaAction() , SignatureFunction(nullptr)`
- L218 _public function_ `FEdGraphSchemaAction_EventFromFunction(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) , SignatureFunction(nullptr)`
- L224 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction interface
- L225 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L226 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`

#### struct `FEdGraphSchemaAction_K2AddComponent`  
`struct FEdGraphSchemaAction_K2AddComponent : public FEdGraphSchemaAction_K2NewNode`  
_L236-268_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction_K2NewNode`
- desc: Action to add an 'add component' node to the graph
- L241 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L242 _public function_ `virtual FName GetTypeId() const override`
- L246 _public member_ `TSubclassOf<class UActorComponent> ComponentClass;` — `UPROPERTY()` — Class of component we want to add
- L250 _public member_ `TObjectPtr<class UObject> ComponentAsset;` — `UPROPERTY()` — Option asset to assign to newly created component
- L252 _public function_ `FEdGraphSchemaAction_K2AddComponent() : FEdGraphSchemaAction_K2NewNode() , ComponentClass(NULL) , ComponentAsset(NULL)`
- L258 _public function_ `FEdGraphSchemaAction_K2AddComponent(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction_K2NewNode(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) , ComponentClass(NULL) , ComponentAsset(NULL)`
- L265 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction interface
- L266 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`

#### struct `FEdGraphSchemaAction_K2AddEvent`  
`struct FEdGraphSchemaAction_K2AddEvent : public FEdGraphSchemaAction_K2NewNode`  
_L276-298_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction_K2NewNode`
- desc: Action to add a 'event' node to the graph
- L281 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L282 _public function_ `virtual FName GetTypeId() const override`
- L284 _public function_ `FEdGraphSchemaAction_K2AddEvent() : FEdGraphSchemaAction_K2NewNode()`
- L288 _public function_ `FEdGraphSchemaAction_K2AddEvent(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction_K2NewNode(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L293 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction interface
- L297 _public prototype_ `bool EventHasAlreadyBeenPlaced(UBlueprint const* Blueprint, class UK2Node_Event const** FoundEventOut = NULL) const;`

#### struct `FEdGraphSchemaAction_K2AddCustomEvent`  
`struct FEdGraphSchemaAction_K2AddCustomEvent : public FEdGraphSchemaAction_K2NewNode`  
_L306-325_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction_K2NewNode`
- desc: Action to add a 'custom event' node to the graph
- L311 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L312 _public function_ `virtual FName GetTypeId() const override`
- L314 _public function_ `FEdGraphSchemaAction_K2AddCustomEvent() : FEdGraphSchemaAction_K2NewNode()`
- L318 _public function_ `FEdGraphSchemaAction_K2AddCustomEvent(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction_K2NewNode(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L323 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction interface

#### struct `FEdGraphSchemaAction_K2AddCallOnActor`  
`struct FEdGraphSchemaAction_K2AddCallOnActor : public FEdGraphSchemaAction_K2NewNode`  
_L333-357_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction_K2NewNode`
- desc: Action to add a 'call function on actor(s)' set of nodes to the graph
- L338 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L339 _public function_ `virtual FName GetTypeId() const override`
- L343 _public member_ `TArray<TObjectPtr<class AActor>> LevelActors;` — `UPROPERTY()` — Pointer to actors in level we want to call function on
- L345 _public function_ `FEdGraphSchemaAction_K2AddCallOnActor() : FEdGraphSchemaAction_K2NewNode()`
- L349 _public function_ `FEdGraphSchemaAction_K2AddCallOnActor(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction_K2NewNode(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L354 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction interface
- L355 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`

#### struct `FEdGraphSchemaAction_K2AddComment`  
`struct FEdGraphSchemaAction_K2AddComment : public FEdGraphSchemaAction`  
_L365-387_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a 'comment' node to the graph
- L370 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L371 _public function_ `virtual FName GetTypeId() const override`
- L373 _public function_ `FEdGraphSchemaAction_K2AddComment() : FEdGraphSchemaAction(FText(), NSLOCTEXT("K2AddComment", "AddComment", "Add Comment..."), NSLOCTEXT("K2AddComment", "AddComment_Tooltip", "Create a resizable comment box."), 0)`
- L378 _public function_ `FEdGraphSchemaAction_K2AddComment(FText InDescription, FText InToolTip) : FEdGraphSchemaAction(FText(), MoveTemp(InDescription), MoveTemp(InToolTip), 0)`
- L385 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FEdGraphSchemaAction_K2TargetNode`  
`struct FEdGraphSchemaAction_K2TargetNode : public FEdGraphSchemaAction_K2NewNode`  
_L395-416_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction_K2NewNode`
- desc: Action to target a specific node on graph
- L401 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L402 _public function_ `virtual FName GetTypeId() const override`
- L404 _public function_ `FEdGraphSchemaAction_K2TargetNode() : FEdGraphSchemaAction_K2NewNode()`
- L408 _public function_ `FEdGraphSchemaAction_K2TargetNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction_K2NewNode(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L414 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FEdGraphSchemaAction_K2PasteHere`  
`struct FEdGraphSchemaAction_K2PasteHere : public FEdGraphSchemaAction`  
_L424-444_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to paste at this location on graph
- L429 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L430 _public function_ `virtual FName GetTypeId() const override`
- L432 _public function_ `FEdGraphSchemaAction_K2PasteHere() : FEdGraphSchemaAction()`
- L436 _public function_ `FEdGraphSchemaAction_K2PasteHere (FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L442 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FEdGraphSchemaAction_K2Enum`  
`struct FEdGraphSchemaAction_K2Enum : public FEdGraphSchemaAction`  
_L452-484_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Reference to an enumeration (only used in 'docked' palette)
- L457 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L458 _public function_ `virtual FName GetTypeId() const override`
- L460 _public member_ `TObjectPtr<UEnum> Enum;`
- L462 _public function_ `void AddReferencedObjects( FReferenceCollector& Collector ) override`
- L470 _public function_ `FName GetPathName() const`
- L475 _public function_ `FEdGraphSchemaAction_K2Enum() : FEdGraphSchemaAction() , Enum(nullptr)`
- L480 _public function_ `FEdGraphSchemaAction_K2Enum(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) , Enum(nullptr)`

#### struct `FEdGraphSchemaAction_BlueprintVariableBase`  
`struct FEdGraphSchemaAction_BlueprintVariableBase : public FEdGraphSchemaAction`  
_L492-578_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Reference to a variable (only used in 'My Blueprints' but used for member variables, local variables, delegates, etc...)
- L498 _private member_ `FName VarName;` — Name of function or class
- L501 _private member_ `TWeakObjectPtr<UObject> VariableSource;` — The struct that owns this item
- L504 _private member_ `bool bIsVarBool;` — TRUE if the variable's type is boolean
- L507 _public function_ `void SetVariableInfo(const FName& InVarName, const UObject* InOwningScope, bool bInIsVarBool)`
- L517 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L518 _public function_ `virtual FName GetTypeId() const override`
- L520 _public function_ `FEdGraphSchemaAction_BlueprintVariableBase() : FEdGraphSchemaAction()`
- L524 _public function_ `FEdGraphSchemaAction_BlueprintVariableBase(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, const int32 InSectionID) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping, FText(), InSectionID)`
- L528 _public function_ `FName GetVariableName() const`
- L533 _public function_ `FString GetFriendlyVariableName() const`
- L538 _public function_ `virtual UClass* GetVariableClass() const`
- L543 _public function_ `UObject* GetVariableScope() const`
- L548 _public function_ `virtual FProperty* GetProperty() const`
- L557 _public function_ `virtual FEdGraphPinType GetPinType() const`
- L559 _public function_ `virtual void ChangeVariableType(const FEdGraphPinType& NewPinType)`
- L561 _public function_ `virtual void RenameVariable(const FName& NewName)`
- L563 _public function_ `virtual bool IsValidName(const FName& NewName, FText& OutErrorMessage) const`
- L565 _public function_ `virtual void DeleteVariable()`
- L567 _public function_ `virtual bool IsVariableUsed()`
- L570 _public prototype_ `virtual void MovePersistentItemToCategory(const FText& NewCategoryName) override;` — FEdGraphSchemaAction interface
- L571 _public prototype_ `virtual int32 GetReorderIndexInContainer() const override;`
- L572 _public prototype_ `virtual bool ReorderToBeforeAction(TSharedRef<FEdGraphSchemaAction> OtherAction) override;`
- L573 _public prototype_ `virtual FEdGraphSchemaActionDefiningObject GetPersistentItemDefiningObject() const override;`
- L574 _public function_ `virtual bool IsAVariable() const`
- L577 _public prototype_ `UBlueprint* GetSourceBlueprint() const;`

#### struct `FEdGraphSchemaAction_K2Var`  
`struct FEdGraphSchemaAction_K2Var : public FEdGraphSchemaAction_BlueprintVariableBase`  
_L587-608_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction_BlueprintVariableBase`
- desc: Reference to a variable (only used in 'docked' palette)
- L593 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L594 _public function_ `virtual FName GetTypeId() const override`
- L596 _public function_ `FEdGraphSchemaAction_K2Var() : FEdGraphSchemaAction_BlueprintVariableBase()`
- L600 _public function_ `FEdGraphSchemaAction_K2Var(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, const int32 InSectionID) : FEdGraphSchemaAction_BlueprintVariableBase(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping, InSectionID)`
- L604 _public function_ `virtual bool IsA(const FName& InType) const override`

#### struct `FEdGraphSchemaAction_K2LocalVar`  
`struct FEdGraphSchemaAction_K2LocalVar : public FEdGraphSchemaAction_BlueprintVariableBase`  
_L616-644_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction_BlueprintVariableBase`
- desc: Reference to a local variable (only used in 'docked' palette)
- L622 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L623 _public function_ `virtual FName GetTypeId() const override`
- L624 _public prototype_ `virtual int32 GetReorderIndexInContainer() const override;`
- L626 _public function_ `FEdGraphSchemaAction_K2LocalVar() : FEdGraphSchemaAction_BlueprintVariableBase()`
- L630 _public function_ `FEdGraphSchemaAction_K2LocalVar(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, const int32 InSectionID) : FEdGraphSchemaAction_BlueprintVariableBase(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping, InSectionID)`
- L634 _public function_ `virtual bool IsA(const FName& InType) const override`
- L639 _public function_ `virtual UClass* GetVariableClass() const override`

#### enum `EEdGraphSchemaAction_K2Graph::Type`  
`enum Type : int`  
_L654-662_
- L656 _public enumerator_ `Graph`
- L657 _public enumerator_ `Subgraph`
- L658 _public enumerator_ `Function`
- L659 _public enumerator_ `Interface`
- L660 _public enumerator_ `Macro`
- L661 _public enumerator_ `MAX`

#### struct `FEdGraphSchemaAction_K2Graph`  
`struct FEdGraphSchemaAction_K2Graph : public FEdGraphSchemaAction`  
_L667-704_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Reference to a function, macro, event graph, or timeline (only used in 'docked' palette)
- L672 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L673 _public function_ `virtual FName GetTypeId() const override`
- L676 _public member_ `FName FuncName;` — Name of function or class
- L679 _public member_ `EEdGraphSchemaAction_K2Graph::Type GraphType;` — The type of graph that action is
- L682 _public member_ `UEdGraph* EdGraph;` — The associated editor graph for this schema
- L684 _public function_ `FEdGraphSchemaAction_K2Graph() : FEdGraphSchemaAction()`
- L688 _public function_ `FEdGraphSchemaAction_K2Graph(EEdGraphSchemaAction_K2Graph::Type InType, FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, const int32 InSectionID = 0) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping, FText(), InSectionID) , GraphType(InType) , EdGraph(nullptr)`
- L695 _public function_ `virtual bool IsParentable() const override` — FEdGraphSchemaAction interface
- L696 _public prototype_ `virtual void MovePersistentItemToCategory(const FText& NewCategoryName) override;`
- L697 _public prototype_ `virtual int32 GetReorderIndexInContainer() const override;`
- L698 _public prototype_ `virtual bool ReorderToBeforeAction(TSharedRef<FEdGraphSchemaAction> OtherAction) override;`
- L699 _public prototype_ `virtual FEdGraphSchemaActionDefiningObject GetPersistentItemDefiningObject() const override;`
- L702 _public prototype_ `UFunction* GetFunction() const;`
- L703 _public prototype_ `UBlueprint* GetSourceBlueprint() const;`

#### struct `FEdGraphSchemaAction_K2Event`  
`struct FEdGraphSchemaAction_K2Event : public FEdGraphSchemaAction_K2TargetNode`  
_L715-754_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction_K2TargetNode`
- desc: A reference to a specific event (living inside a Blueprint graph)... intended to be used the 'docked' palette only.
- L723 _public function_ `FEdGraphSchemaAction_K2Event() : FEdGraphSchemaAction_K2TargetNode()` — An empty default constructor (stubbed out for arrays and other containers that need to allocate default instances of this struct)
- L735 _public function_ `FEdGraphSchemaAction_K2Event(FText Category, FText MenuDescription, FText Tooltip, int32 const Grouping) : FEdGraphSchemaAction_K2TargetNode(MoveTemp(Category), MoveTemp(MenuDescription), MoveTemp(Tooltip), Grouping)` — The primary constructor, used to customize the Super FEdGraphSchemaAction. @param   Category		The tree parent header (or path, delimited by '|') you want to sort this action under. @param   MenuDescription	The string you want displayed in the tree, corresponding to this action. @param   Tooltip			A string to display when hovering over this action entry. @param   Grouping		Used to override list ordering (actions with the same number get grouped together, higher numbers get sorted first).
- L744 _public function_ `static FName StaticGetTypeId()` — Provides a set identifier for all FEdGraphSchemaAction_K2Event actions. @return A static identifier for actions of this type.
- L751 _public function_ `virtual FName GetTypeId() const override` — FEdGraphSchemaAction interface
- L752 _public function_ `virtual bool IsParentable() const override`

#### struct `FEdGraphSchemaAction_K2InputAction`  
`struct FEdGraphSchemaAction_K2InputAction : public FEdGraphSchemaAction_K2TargetNode`  
_L765-804_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction_K2TargetNode`
- desc: A reference to a specific event (living inside a Blueprint graph)... intended to be used the 'docked' palette only.
- L773 _public function_ `FEdGraphSchemaAction_K2InputAction() : FEdGraphSchemaAction_K2TargetNode()` — An empty default constructor (stubbed out for arrays and other containers that need to allocate default instances of this struct)
- L785 _public function_ `FEdGraphSchemaAction_K2InputAction(FText Category, FText MenuDescription, FText Tooltip, int32 const Grouping) : FEdGraphSchemaAction_K2TargetNode(MoveTemp(Category), MoveTemp(MenuDescription), MoveTemp(Tooltip), Grouping)` — The primary constructor, used to customize the Super FEdGraphSchemaAction. @param   Category		The tree parent header (or path, delimited by '|') you want to sort this action under. @param   MenuDescription	The string you want displayed in the tree, corresponding to this action. @param   Tooltip			A string to display when hovering over this action entry. @param   Grouping		Used to override list ordering (actions with the same number get grouped together, higher numbers get sorted first).
- L794 _public function_ `static FName StaticGetTypeId()` — Provides a set identifier for all FEdGraphSchemaAction_K2InputAction actions. @return A static identifier for actions of this type.
- L801 _public function_ `virtual FName GetTypeId() const override` — FEdGraphSchemaAction interface
- L802 _public function_ `virtual bool IsParentable() const override`

#### struct `FEdGraphSchemaAction_K2Delegate`  
`struct FEdGraphSchemaAction_K2Delegate : public FEdGraphSchemaAction_BlueprintVariableBase`  
_L812-853_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction_BlueprintVariableBase`
- desc: Reference to a delegate
- L818 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L819 _public function_ `virtual FName GetTypeId() const override`
- L822 _public member_ `UEdGraph* EdGraph;` — The associated editor graph for this schema
- L824 _public function_ `FEdGraphSchemaAction_K2Delegate() : FEdGraphSchemaAction_BlueprintVariableBase() , EdGraph(nullptr)`
- L829 _public function_ `FEdGraphSchemaAction_K2Delegate(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, const int32 InSectionID) : FEdGraphSchemaAction_BlueprintVariableBase(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping, InSectionID) , EdGraph(nullptr)`
- L834 _public function_ `FName GetDelegateName() const`
- L839 _public function_ `UClass* GetDelegateClass() const`
- L844 _public function_ `FMulticastDelegateProperty* GetDelegateProperty() const`
- L849 _public function_ `virtual bool IsA(const FName& InType) const override`

#### Free symbols / members of external scopes

- L38 _macro_ `#define UE_API BLUEPRINTGRAPH_API`
- L114 _function_ `` (scope `FEdGraphSchemaAction_K2NewNode::SpawnNode`)
- L127 _function_ `return SpawnNode<NodeType>(ParentGraph, Location, Options, [](NodeType*){});` (scope `FEdGraphSchemaAction_K2NewNode::SpawnNode`)
- L652 _namespace_ `namespace EEdGraphSchemaAction_K2Graph`

### `Source/Editor/BlueprintGraph/Classes/K2Node.h` (Public)


#### struct `FOldOptionalPinSettings`  
`struct FOldOptionalPinSettings`  
_L52-69_
- desc: Helper structure to cache old data for optional pins so the data can be restored during reconstruction
- L55 _public member_ `uint8 bOldVisibility:1;` — TRUE if optional pin was previously visible
- L57 _public member_ `uint8 bIsOldOverrideEnabled:1;` — TRUE if the optional pin's override value was previously enabled
- L59 _public member_ `uint8 bIsOldSetValuePinVisible:1;` — TRUE if the optional pin's value was previously editable
- L61 _public member_ `uint8 bIsOldOverridePinVisible:1;` — TRUE if the optional pin's override value was previously editable
- L63 _public function_ `FOldOptionalPinSettings(bool bInOldVisibility, bool bInIsOldOverrideEnabled, bool bInIsOldSetValuePinVisible, bool bInIsOldOverridePinVisible) : bOldVisibility(bInOldVisibility) , bIsOldOverrideEnabled(bInIsOldOverrideEnabled) , bIsOldSetValuePinVisible(bInIsOldSetValuePinVisible) , bIsOldOverridePinVisible(bInIsOldOverridePinVisible)`

#### struct `FOptionalPinFromProperty`  
`struct FOptionalPinFromProperty`  
_L72-144_
- reflection: `USTRUCT()`
- L77 _public member_ `FName PropertyName;` — `UPROPERTY(EditAnywhere, Category= OptionalPin)`
- L80 _public member_ `FString PropertyFriendlyName;` — `UPROPERTY(EditAnywhere, Category= OptionalPin)`
- L83 _public member_ `FText PropertyTooltip;` — `UPROPERTY(EditAnywhere, Category= OptionalPin)`
- L86 _public member_ `FName CategoryName;` — `UPROPERTY(EditAnywhere, Category=OptionalPin)`
- L89 _public member_ `uint8 bShowPin:1;` — `UPROPERTY(EditAnywhere, Category=OptionalPin)`
- L92 _public member_ `uint8 bCanToggleVisibility:1;` — `UPROPERTY(EditAnywhere, Category=OptionalPin)`
- L95 _public member_ `uint8 bPropertyIsCustomized:1;` — `UPROPERTY(EditAnywhere, Category=OptionalPin)`
- L98 _public member_ `uint8 bHasOverridePin:1;` — `UPROPERTY(EditAnywhere, Category=OptionalPin)`
- L101 _public member_ `uint8 bIsMarkedForAdvancedDisplay:1;` — `UPROPERTY(EditAnywhere, Category=OptionalPin)`
- L105 _public member_ `uint8 bIsOverrideEnabled:1;` — `UPROPERTY(EditAnywhere, Category = OptionalPin)` — TRUE if the override value is enabled for use
- L109 _public member_ `uint8 bIsSetValuePinVisible:1;` — `UPROPERTY(EditAnywhere, Category = OptionalPin)` — TRUE if the override value should be set through this pin
- L113 _public member_ `uint8 bIsOverridePinVisible:1;` — `UPROPERTY(EditAnywhere, Category = OptionalPin)` — TRUE if the override pin is visible
- L115 _public function_ `FOptionalPinFromProperty() : bShowPin(false) , bCanToggleVisibility(false) , bPropertyIsCustomized(false) , bHasOverridePin(false) , bIsMarkedForAdvancedDisplay(false) , bIsOverrideEnabled(true) , bIsSetValuePinVisible(true) , bIsOverridePinVisible(true)`
- L127 _public function_ `FOptionalPinFromProperty(FName InPropertyName, bool bInShowPin, bool bInCanToggleVisibility, const FString& InFriendlyName, const FText& InTooltip, bool bInPropertyIsCustomized, FName InCategoryName, bool bInHasOverridePin) : PropertyName(InPropertyName) , PropertyFriendlyName(InFriendlyName) #if WITH_EDITORONLY_DATA , PropertyTooltip(InTooltip) #endif , CategoryName(InCategoryName) , bShowPin(bInShowPin) , bCanToggleVisibility(bInCanToggleVisibility) , bPropertyIsCustomized(bInPropertyIsCustomized) , bHasOverridePin(bInHasOverridePin) , bIsMarkedForAdvancedDisplay(false) , bIsOverrideEnabled(true) , bIsSetValuePinVisible(true) , bIsOverridePinVisible(true)`

#### struct `FOptionalPinManager`  
`struct FOptionalPinManager`  
_L147-191_
- desc: Manager to build or refresh a list of optional pins
- L150 _public prototype_ `virtual ~FOptionalPinManager() = default;`
- L153 _public prototype_ `virtual void GetRecordDefaults(FProperty* TestProperty, FOptionalPinFromProperty& Record) const;` — Should the specified property be displayed by default
- L156 _public prototype_ `virtual bool CanTreatPropertyAsOptional(FProperty* TestProperty) const;` — Can this property be managed as an optional pin (with the ability to be shown or hidden)
- L164 _public prototype_ `void RebuildPropertyList(TArray<FOptionalPinFromProperty>& Properties, UStruct* SourceStruct);` — Reconstructs the specified property array using the SourceStruct @param [in,out] Properties	The property array @param SourceStruct			The source structure to update the properties array from @param bDefaultVisibility
- L175 _public prototype_ `void CreateVisiblePins(TArray<FOptionalPinFromProperty>& Properties, UStruct* SourceStruct, EEdGraphPinDirection Direction, class UK2Node* TargetNode, uint8* StructBasePtr = nullptr, uint8* DefaultsPtr = nullptr);` — Creates a pin for each visible property on the specified node @param Properties	The property array @param SourceStruct	The source structure to update the properties array from @param Direction		Direction of pins to create @param TargetNode	Node to generate pins for @param StructBasePtr	Struct that is iterated over, to represent the current version of the data @param DefaultsPtr	Struct that is iterated over, to represent the default version of the data, used for delta serialization
- L178 _public function_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex, FProperty* Property = NULL) const` — Customize automatically created pins if desired
- L181 _public prototype_ `static void CacheShownPins(const TArray<FOptionalPinFromProperty>& OptionalPins, TArray<FName>& OldShownPins);` — Helper function to make consistent behavior between nodes that use optional pins
- L184 _public prototype_ `static void EvaluateOldShownPins(const TArray<FOptionalPinFromProperty>& OptionalPins, TArray<FName>& OldShownPins, UK2Node* Node);` — Helper function to make consistent behavior between nodes that use optional pins
- L188 _protected function_ `virtual void PostInitNewPin(UEdGraphPin* Pin, FOptionalPinFromProperty& Record, int32 ArrayIndex, FProperty* Property, uint8* PropertyAddress, uint8* DefaultPropertyAddress) const`
- L189 _protected function_ `virtual void PostRemovedOldPin(FOptionalPinFromProperty& Record, int32 ArrayIndex, FProperty* Property, uint8* PropertyAddress, uint8* DefaultPropertyAddress) const`
- L190 _protected prototype_ `void RebuildProperty(FProperty* TestProperty, FName CategoryName, TArray<FOptionalPinFromProperty>& Properties, UStruct* SourceStruct, TMap<FName, FOldOptionalPinSettings>& OldSettings);`

#### enum `ERenamePinResult`  
`enum ERenamePinResult`  
_L193-198_
- L195 _public enumerator_ `ERenamePinResult_Success`
- L196 _public enumerator_ `ERenamePinResult_NoSuchPin`
- L197 _public enumerator_ `ERenamePinResult_NameCollision`

#### class `UK2Node`  
`class UK2Node : public UEdGraphNode`  
_L204-604_
- reflection: `UCLASS(abstract, MinimalAPI)`
- inherits: `UEdGraphNode`
- desc: Abstract base class of all blueprint graph nodes.
- L210 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;` — UObject interface
- L211 _public prototype_ `virtual void PostLoad() override;`
- L212 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L213 _public prototype_ `virtual bool HasNonEditorOnlyReferences() const override;`
- L217 _public prototype_ `virtual void ReconstructNode() override;` — UEdGraphNode interface
- L218 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L219 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L220 _public prototype_ `void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L221 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L222 _public prototype_ `virtual bool CanJumpToDefinition() const override;`
- L223 _public prototype_ `virtual void JumpToDefinition() const override;`
- L224 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L225 _public prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;`
- L226 _public function_ `virtual bool ShowPaletteIconOnNode() const override`
- L227 _public prototype_ `virtual bool CanSplitPin(const UEdGraphPin* Pin) const override;`
- L228 _public prototype_ `virtual UEdGraphPin* GetPassThroughPin(const UEdGraphPin* FromPin) const override;`
- L229 _public prototype_ `virtual bool IsInDevelopmentMode() const override;`
- L230 _public prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L231 _public prototype_ `virtual FString GetPinMetaData(FName InPinName, FName InKey) override;`
- L241 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins);` — Reallocate pins during reconstruction; by default ignores the old pins and calls AllocateDefaultPins() If you override this to create additional pins you likely need to call RestoreSplitPins to restore any pins that have been split (e.g. a vector pin split into its components)
- L244 _public function_ `virtual bool IsNodePure() const` — Returns whether this node is considered 'pure' by the compiler
- L247 _public prototype_ `virtual bool CanPlaceBreakpoints() const;` — Returns whether this node can have breakpoints placed on it in the debugger
- L250 _public function_ `virtual bool DrawNodeAsEntry() const` — Return whether to draw this node as an entry
- L253 _public function_ `virtual bool DrawNodeAsExit() const` — Return whether to draw this node as an entry
- L256 _public function_ `virtual bool DrawNodeAsVariable() const` — Return whether to draw this node as a small variable node
- L259 _public function_ `virtual bool ShouldDrawCompact() const` — Should draw compact
- L262 _public function_ `virtual FText GetCompactNodeTitle() const` — Return title if drawing this node in 'compact' mode
- L265 _public prototype_ `virtual FText GetToolTipHeading() const;`
- L270 _public function_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter)` — Determine if the node of this type should be filtered in the actions menu
- L273 _public function_ `virtual bool ShouldShowNodeProperties() const` — Return whether the node's properties display in the blueprint details panel
- L276 _public function_ `virtual bool CanEverInsertExecutionPin() const` — Return whether the node's execution pins should support the insert execution pin action
- L279 _public function_ `virtual bool CanEverRemoveExecutionPin() const` — Return whether the node's execution pins should support the remove execution pin action
- L282 _public function_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin)` — Called when the connection list of one of the pins of this node is changed in the editor, after the pin has had it's literal cleared
- L292 _public prototype_ `bool CreatePinsForFunctionEntryExit(const UFunction* Function, bool bForFunctionEntry);` — Creates the pins required for a function entry or exit node (only inputs as outputs or outputs as inputs respectively) @param	Function	The function being implemented that the entry or exit nodes are for. @param	bForFunctionEntry	True indicates a function entry node, false indicates an exit node. @return	true on success.
- L295 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph);` — Expands a node while compiling, which may add additional nodes or delete this node
- L298 _public function_ `virtual void ClearCachedBlueprintData(UBlueprint* Blueprint)` — Clears out any cached data that needs to be regenerated after a structural blueprint change
- L301 _public function_ `virtual void ConvertDeprecatedNode(UEdGraph* Graph, bool bOnlySafeChanges)` — Performs a node-specific deprecation fixup, which may delete this node and replace it with another one
- L303 _public function_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const`
- L305 _public prototype_ `UK2Node* ExpandSplitPin(class FKismetCompilerContext* CompilerContext, UEdGraph* SourceGraph, UEdGraphPin* Pin);`
- L312 _public function_ `virtual bool IsNodeSafeToIgnore() const` — Query if this is a node that is safe to ignore (e.g., a comment node or other non-structural annotation that can be pruned with no warnings). @return	true if node safe to ignore.
- L315 _public function_ `virtual bool IsNodeRootSet() const` — Query if this node should be kept as part of the root set during the pruning stage of compilation. Prevents the node being pruned as isolated.
- L318 _public prototype_ `virtual void PostReconstructNode();` — Called at the end of ReconstructNode, allows node specific work to be performed
- L321 _public function_ `virtual bool NodeCausesStructuralBlueprintChange() const` — Return true if adding/removing this node requires calling MarkBlueprintAsStructurallyModified on the Blueprint
- L328 _public prototype_ `bool HasValidBlueprint() const;` — Return true if this node has a valid blueprint outer, or false otherwise. This is useful for checking validity of the node for UI list refreshes, which may operate on stale nodes for a frame until the list is refreshed.
- L331 _public prototype_ `UBlueprint* GetBlueprint() const;` — Get the Blueprint object to which this node belongs. This will return null if HasValidBlueprint is false
- L334 _public prototype_ `TNotNull<UBlueprint*> GetBlueprintChecked() const;` — Get the Blueprint object to which this node belongs. This will assert if HasValidBlueprint is false
- L337 _public prototype_ `UEdGraphPin* GetExecPin() const;` — Get the input execution pin of this node (if one exists)
- L340 _public prototype_ `UEdGraphPin* GetThenPin() const;` — Get the output then pin of this node (if one exists)
- L347 _public function_ `virtual AActor* GetReferencedLevelActor() const` — If this node references an actor in the level that should be selectable by "Find Actors In Level," this will return a reference to that actor @return	Reference to an actor corresponding to this node, or NULL if no actors are referenced
- L350 _public prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;` — Can this node be created under the specified schema
- L353 _public function_ `virtual UClass* GetDynamicBindingClass() const` — Returns which dynamic binding class (if any) to use for this node
- L356 _public function_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const` — Puts information about this node into the dynamic binding object
- L359 _public prototype_ `ERenamePinResult RenameUserDefinedPin(const FName OldName, const FName NewName, bool bTest = false);` — Renames a user defined pin and broadcasts the result to any OnUserDefinedPinRenamed listeners on success (if bTest is false)
- L362 _public prototype_ `FOnUserDefinedPinRenamed& OnUserDefinedPinRenamed();` — Retrieves a delegate that is called when a user-defined pin on this node is renamed
- L371 _public prototype_ `void InsertNewNode(UEdGraphPin* FromPin, UEdGraphPin* NewLinkPin, TSet<UEdGraphNode*>& OutNodeList);` — Handles inserting the node between the FromPin and what the FromPin was original connected to @param FromPin			The pin this node is being spawned from @param NewLinkPin		The new pin the FromPin will connect to @param OutNodeList		Any nodes that are modified will get added to this list for notification purposes
- L374 _public function_ `virtual bool AllowMultipleSelfs(bool bInputAsArray) const` — @return true if this function can be called on multiple contexts at once
- L377 _public function_ `virtual FName GetCornerIcon() const` — @return name of brush for special icon in upper-right corner
- L380 _public function_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const` — @return true, is pins cannot be connected due to node's inner logic, put message for user in OutReason
- L383 _public prototype_ `virtual void EarlyValidation(FCompilerResultsLog& MessageLog) const;` — This function if used for nodes that needs CDO for validation (Called before expansion)
- L386 _public prototype_ `virtual void GetNodeAttributes(TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes) const;` — This function returns an arbitrary number of attributes that describe this node for analytics events
- L389 _public function_ `virtual void PreloadRequiredAssets()` — Called before compilation begins, giving a blueprint time to force the linker to load data
- L399 _public function_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const` — Replacement for GetMenuEntries(). Override to add specific UBlueprintNodeSpawners pertaining to the sub-class type. Serves as an extensible way for new nodes, and game module nodes to add themselves to context menus. @param  ActionListOut	The list to be populated with new spawners.
- L407 _public function_ `virtual FText GetMenuCategory() const` — Override to provide a default category for specific node types to be listed under. @return A localized category string (or an empty string if you want this node listed at the menu's root).
- L420 _public function_ `virtual FBlueprintNodeSignature GetSignature() const` — Retrieves a unique identifier for this node type. Built from the node's class, as well as other signature items (like functions for CallFunction nodes). NOTE: This is not the same as a node identification GUID, two node instances can have the same signature (if both call the same function, etc.). @return A signature struct, discerning this node from others.
- L429 _public function_ `virtual int32 GetNodeRefreshPriority() const`
- L431 _public prototype_ `bool DoesWildcardPinAcceptContainer(const UEdGraphPin* Pin);`
- L432 _public function_ `virtual bool DoesInputWildcardPinAcceptArray(const UEdGraphPin* Pin) const`
- L433 _public function_ `virtual bool DoesOutputWildcardPinAcceptContainer(const UEdGraphPin* Pin) const`
- L436 _public function_ `virtual void HandleVariableRenamed(UBlueprint* InBlueprint, UClass* InVariableClass, UEdGraph* InGraph, const FName& InOldVarName, const FName& InNewVarName)` — Handle when a variable is renamed in the Blueprint Palette
- L439 _public function_ `virtual bool ReferencesVariable(const FName& InVarName, const UStruct* InScope) const` — Return whether this node references the specified variable, give the supplied scope. Used when variable types are changed.
- L442 _public function_ `virtual void HandleFunctionRenamed(UBlueprint* InBlueprint, UClass* InFunctionClass, UEdGraph* InGraph, const FName& InOldFuncName, const FName& InNewFuncName)` — Handle when a function is renamed in the Blueprint Palette
- L445 _public function_ `virtual bool ReferencesFunction(const FName& InFunctionName, const UStruct* InScope) const` — Return whether this node references the specified function, identified by a name and guid pair
- L454 _public function_ `virtual void ReplaceReferences(UBlueprint* InBlueprint, UBlueprint* InReplacementBlueprint, const FMemberReference& InSource, const FMemberReference& InReplacement)` — Replace any member references of source with replacement @param	InBlueprint		The blueprint that the source reference is from @param	InReplacementBlueprint	The blueprint that the replacement reference is from @param	InSource		The reference to be replaced @param	InReplacement		The reference to replace with
- L457 _public prototype_ `void ExpandSplitPins(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph);` — Helper function for ExpandNode(), allowing other contexts to call pin expansion alone
- L460 _public function_ `virtual bool IsLatentForMacros() const` — Hook for allowing derived types to determine if they should be treated as a latent node by macros
- L477 _protected prototype_ `void ReconstructSinglePin(UEdGraphPin* NewPin, UEdGraphPin* OldPin, ERedirectType RedirectType);` — Handles the actual reconstruction (copying data, links, name, etc...) from two pins that have already been matched together
- L480 _protected prototype_ `void RewireOldPinsToNewPins(TArray<UEdGraphPin*>& InOldPins, TArray<UEdGraphPin*>& InNewPins, TMap<UEdGraphPin*, UEdGraphPin*>* NewPinToOldPin);` — Helper function to rewire old pins to new pins during node reconstruction (or other regeneration of pins)
- L483 _protected prototype_ `void DestroyPinList(TArray<UEdGraphPin*>& InPins);` — Helper function to properly destroy a set of pins
- L486 _protected prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const;` — Whether or not two pins match for purposes of reconnection after reconstruction.  This allows pins that may have had their names changed via reconstruction to be matched to their old values on a node-by-node basis, if needed
- L489 _protected prototype_ `virtual void GetRedirectPinNames(const UEdGraphPin& Pin, TArray<FString>& RedirectPinNames) const;` — Determines what the possible redirect pin names are
- L492 _protected prototype_ `virtual ERenamePinResult RenameUserDefinedPinImpl(const FName OldName, const FName NewName, bool bTest);` — Implementation function that renames an existing pin on the node. Does not broadcast notifications.
- L495 _protected prototype_ `void BroadcastUserDefinedPinRenamed(FName OldName, FName NewName);` — Attempt to broadcast an event for a user-defined pin being renamed on this node
- L502 _protected prototype_ `ERedirectType ShouldRedirectParam(const TArray<FString>& OldPinNames, FName& NewPinName, const UK2Node* NewPinNode) const;` — Searches ParamRedirect Map and find if there is matching new param returns the redirect type
- L505 _protected prototype_ `void RestoreSplitPins(TArray<UEdGraphPin*>& OldPins);` — Helper function to restore Split Pins after ReallocatePinsDuringReconstruction, call after recreating all pins to restore split pin state
- L512 _protected function_ `template<typename... ArgTypes> void Message_Note(const FString& Message, ArgTypes... Args) const` — Sends a message to the owning blueprint's CurrentMessageLog, if there is one available.  Otherwise, defaults to logging to the normal channels. Should use this for node actions that happen during compilation!
- L526 _protected function_ `template<typename... ArgTypes> void Message_Warn(const FString& Message, ArgTypes... Args) const`
- L540 _protected function_ `template<typename... ArgTypes> void Message_Error(const FString& Message, ArgTypes... Args) const`
- L558 _protected function_ `void PreloadObject(UObject* ReferencedObject)` — Ensures the specified object is preloaded.  ReferencedObject can be NULL.
- L567 _protected prototype_ `virtual void FixupPinDefaultValues();` — Handle backwards compatible fixes on load
- L570 _protected prototype_ `virtual void FixupPinStringDataReferences(FArchive* SavingArchive);` — Fixes up structure/soft object ref pins, on both save and load
- L578 _private prototype_ `void ValidateOrphanPins(FCompilerResultsLog& MessageLog, bool bStore) const;` — Utility function to write messages about orphan nodes in to the compiler log. bStore indicates whether to write immediately to the log, or to store as a potential message to be committed once node pruning has completed
- L579 _private prototype_ `void ValidateOrphanPin(UEdGraphPin* Pin, FCompilerResultsLog& MessageLog, bool bStore) const;`
- L586 _private prototype_ `void ValidateLinkedPinTypes(UEdGraphPin* OutputPin, FCompilerResultsLog& MessageLog) const;` — Checks that pins are type compatible with their links. If there's a type mismatch (eg: due to a underlying type change), then we'll automatically insert a conversion node into the graph if one exists between the two types.
- L596 _private prototype_ `bool TryInsertDefaultValueConversionNode(const UEdGraphPin& OldPin, UEdGraphPin& NewPin) const;` — If there's a type mismatch between old and new pins during rewiring *and* the old pin has a default value, then we'll need a way to keep the old default value and convert it to the new type. This function achieves that by inserting both a literal and a conversion node. The literal node will use the original default value. Returns true if the conversion was successful.
- L599 _private prototype_ `bool TryRewireOldPinsToNewPinsFast(TArray<UEdGraphPin*>& InOldPins, TArray<UEdGraphPin*>& InNewPins, TMap<UEdGraphPin*, UEdGraphPin*>* NewPinToOldPin);` — A fast pin rewiring function that does not handle split pins or orphaned pins, but safely aborts if any are found
- L603 _public prototype_ `UClass* GetBlueprintClassFromNode() const;` — Util to get the generated class from a node.

#### enum `UK2Node::EBaseNodeRefreshPriority`  
`enum EBaseNodeRefreshPriority`  
_L422-427_
- L424 _public enumerator_ `Low_UsesDependentWildcard = 100`
- L425 _public enumerator_ `Low_ReceivesDelegateSignature = 150`
- L426 _public enumerator_ `Normal = 200`

#### enum `UK2Node::ERedirectType`  
`enum ERedirectType`  
_L464-474_
- L467 _public enumerator_ `ERedirectType_None` — The pins do not match
- L469 _public enumerator_ `ERedirectType_Name` — The pins match by name or redirect and have the same type (or we're ok with the mismatched type)
- L471 _public enumerator_ `ERedirectType_Value` — The pins match via a redirect and the value needs to also be redirected
- L473 _public enumerator_ `ERedirectType_DefaultValue` — The pins differ by type and have a default value

#### Free symbols / members of external scopes

- L28 _macro_ `#define UE_API BLUEPRINTGRAPH_API`
- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUserDefinedPinRenamed, UK2Node*, FName, FName);`
- L49 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUserDefinedPinRenamed, UK2Node*, FName, FName);`

### `Source/Editor/BlueprintGraph/Classes/K2Node_ActorBoundEvent.h` (Public)


#### class `UK2Node_ActorBoundEvent`  
`class UK2Node_ActorBoundEvent : public UK2Node_Event`  
_L29-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Event`
- L35 _private member_ `FName DelegatePropertyName;` — `UPROPERTY()` — Delegate property name that this event is associated with
- L39 _private member_ `TObjectPtr<UClass> DelegateOwnerClass;` — `UPROPERTY()` — Delegate property's owner class that this event is associated with
- L43 _private member_ `TObjectPtr<class AActor> EventOwner;` — `UPROPERTY()` — The event that this event is bound to
- L46 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L50 _private prototype_ `virtual void ReconstructNode() override;`
- L51 _private prototype_ `virtual void DestroyNode() override;`
- L52 _private prototype_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;`
- L53 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L54 _private prototype_ `virtual FText GetTooltipText() const override;`
- L55 _private prototype_ `virtual FString GetDocumentationLink() const override;`
- L56 _private prototype_ `virtual FString GetDocumentationExcerptName() const override;`
- L60 _private prototype_ `virtual AActor* GetReferencedLevelActor() const override;`
- L61 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L62 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L63 _private prototype_ `virtual FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override;`
- L66 _private prototype_ `virtual bool IsUsedByAuthorityOnlyDelegate() const override;`
- L74 _private prototype_ `void InitializeActorBoundEventParams(AActor* InEventOwner, const FMulticastDelegateProperty* InDelegateProperty);` — Initialized the members of the node, given the specified owner and delegate property.  This will fill out all the required members for the event, such as CustomFunctionName @param InEventOwner			The target for this bound event @param InDelegateProperty	The multicast delegate property associated with the event, which will have a delegate added to it in the level script actor, matching its signature
- L77 _private prototype_ `FMulticastDelegateProperty* GetTargetDelegateProperty() const;` — Return the delegate property that this event is bound to
- L78 _private prototype_ `FMulticastDelegateProperty* GetTargetDelegatePropertyFromSkel() const;`
- L81 _private prototype_ `FText GetTargetDelegateDisplayName() const;` — Gets the proper display name for the property
- L85 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/BlueprintGraph/Classes/K2Node_AddComponent.h` (Public)


#### class `UK2Node_AddComponent`  
`class UK2Node_AddComponent : public UK2Node_CallFunction`  
_L30-118_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction`
- L35 _private member_ `static const FString ComponentTemplateNamePrefix;` — Prefix used for component template object name.
- L38 _private member_ `uint32 bHasExposedVariable:1;` — `UPROPERTY()`
- L42 _private member_ `FString TemplateBlueprint;` — `UPROPERTY()` — The blueprint name we came from, so we can lookup the template after a paste
- L45 _private member_ `TObjectPtr<UClass> TemplateType;` — `UPROPERTY()`
- L48 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L52 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L53 _private prototype_ `virtual void DestroyNode() override;`
- L54 _private prototype_ `virtual void PrepareForCopying() override;`
- L55 _private prototype_ `virtual void PostPasteNode() override;`
- L56 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L57 _private prototype_ `virtual FString GetDocumentationLink() const override;`
- L58 _private prototype_ `virtual FString GetDocumentationExcerptName() const override;`
- L59 _private prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;`
- L60 _private prototype_ `virtual void ReconstructNode() override;`
- L61 _private prototype_ `virtual void FindDiffs(class UEdGraphNode* OtherNode, struct FDiffResults& Results) override;`
- L65 _private prototype_ `virtual void PostReconstructNode() override;`
- L66 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L67 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L68 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L71 _private prototype_ `void AllocateDefaultPinsWithoutExposedVariables();`
- L72 _private prototype_ `void AllocatePinsForExposedVariables();`
- L74 _private function_ `UEdGraphPin* GetTemplateNamePinChecked() const`
- L81 _private function_ `UEdGraphPin* GetRelativeTransformPin() const`
- L86 _private function_ `UEdGraphPin* GetManualAttachmentPin() const`
- L92 _private prototype_ `UActorComponent* GetTemplateFromNode() const;` — Tries to get a template object from this node.
- L95 _private prototype_ `FName MakeNewComponentTemplateName(UObject* InOuter, UClass* InComponentClass);` — Helper method used to generate a new, unique component template name.
- L98 _private prototype_ `void MakeNewComponentTemplate();` — Helper method used to instantiate a new component template after duplication.
- L101 _private prototype_ `static FName GetAddComponentFunctionName();` — Static name of function to call
- L105 _protected function_ `virtual bool CanToggleNodePurity() const override`
- L109 _private function_ `UEdGraphPin* GetTemplateNamePin() const`
- L114 _private prototype_ `UClass* GetSpawnedType() const;`
- L116 _private member_ `static const FName NAME_RelativeTransform;`
- L117 _private member_ `static const FName NAME_ManualAttachment;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_AddComponentByClass.h` (Public)


#### class `UK2Node_AddComponentByClass`  
`class UK2Node_AddComponentByClass : public UK2Node_ConstructObjectFromClass`  
_L26-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_ConstructObjectFromClass`
- desc: Implementation of K2Node for creating a component based on a selected or passed in class
- L31 _public prototype_ `UK2Node_AddComponentByClass(const FObjectInitializer& ObjectInitializer);`
- L34 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L35 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L36 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L40 _public prototype_ `virtual void CreatePinsForClass(UClass* InClass, TArray<UEdGraphPin*>* OutClassPins) override;`
- L43 _protected prototype_ `virtual FText GetBaseNodeTitle() const override;`
- L44 _protected prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L45 _protected prototype_ `virtual FText GetNodeTitleFormat() const override;`
- L46 _protected prototype_ `virtual UClass* GetClassPinBaseClass() const override;`
- L47 _protected prototype_ `virtual bool IsSpawnVarPin(UEdGraphPin* Pin) const override;`
- L50 _protected prototype_ `UEdGraphPin* GetRelativeTransformPin() const;`
- L51 _protected prototype_ `UEdGraphPin* GetManualAttachmentPin() const;`
- L54 _protected prototype_ `bool IsSceneComponent() const;` — Returns true if the currently selected or linked class is known to be a scene component
- L57 _protected prototype_ `void SetSceneComponentPinsHidden(bool bHidden);` — Utility function to set whether the scene component specific pins are hidden or not

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_AddDelegate.h` (Public)


#### class `UK2Node_AddDelegate`  
`class UK2Node_AddDelegate : public UK2Node_BaseMCDelegate`  
_L10-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_BaseMCDelegate`
- L16 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L17 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L21 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L22 _public prototype_ `virtual void GetNodeAttributes( TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes ) const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_AddPinInterface.h` (Public)


#### class `UK2Node_AddPinInterface`  
`class UK2Node_AddPinInterface : public UInterface`  
_L20-23_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IK2Node_AddPinInterface`  
`class IK2Node_AddPinInterface`  
_L34-90_
- desc: Interface for adding the small "Add Pin" symbol to a node in the bottom right hand side. Implementing this interface will provide the API needed to get the UI up and running, but the actual pin creation/naming is up to the specific node. @see UK2Node_CommutativeAssociativeBinaryOperator, UK2Node_DoOnceMultiInput
- L47 _public function_ `static constexpr int32 GetMaxInputPinsNum()` — Determine the maximum number of additional input pins this node can have. The node is limited by the number of letters in the alphabet for display purposes @return constexpr int32
- L59 _public prototype_ `static FName GetNameForAdditionalPin(int32 PinIndex);` — GetNameForAdditionalPin @param PinIndex		The additional pin index to get the name of @return FName			Name of this additional pin
- L64 _public prototype_ `virtual void AddInputPin() = 0;` — Add an additional input pin to this node
- L72 _public function_ `virtual bool CanAddPin() const` — Determines if a pin can be added to this node. Typically used within UK2Node::GetNodeContextMenuActions to determine what options there should be. @return bool	True if a new pin can be added, false if it cannot.
- L80 _public function_ `virtual void RemoveInputPin(UEdGraphPin* Pin)` — Attempt to remove the given pin from this node. Should fail if the given pin is not an additional pin to the node @param Pin		The pin to remove
- L89 _public function_ `virtual bool CanRemovePin(const UEdGraphPin* Pin) const` — Returns true if the given pin can be removed from this node. @param Pin		The pin to test @return bool		True if the pin can be removed, false otherwise.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_AssignDelegate.h` (Public)


#### class `UK2Node_AssignDelegate`  
`class UK2Node_AssignDelegate : public UK2Node_AddDelegate`  
_L23-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_AddDelegate`
- desc: Modeled after FEdGraphSchemaAction_K2AssignDelegate for the newer Blueprint menu system. Acts simply as a UK2Node_AddDelegate with an attached custom- event node (spawned in PostPlacedNewNode).
- L29 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L30 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L31 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L32 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L37 _private member_ `FNodeTextCache CachedListTitle;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/BlueprintGraph/Classes/K2Node_AssignmentStatement.h` (Public)


#### class `UK2Node_AssignmentStatement`  
`class UK2Node_AssignmentStatement : public UK2Node`  
_L24-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L30 _private member_ `static FName VariablePinName;` — Name of the Variable pin for this node
- L32 _private member_ `static FName ValuePinName;` — Name of the Value pin for this node
- L35 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L36 _private prototype_ `virtual FText GetTooltipText() const override;`
- L37 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L38 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L39 _private prototype_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;`
- L43 _private prototype_ `virtual void PostReconstructNode() override;`
- L44 _private prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L45 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L46 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L47 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L48 _private function_ `virtual int32 GetNodeRefreshPriority() const override`
- L52 _private prototype_ `UEdGraphPin* GetVariablePin() const;` — Get the Variable input pin
- L54 _private prototype_ `UEdGraphPin* GetValuePin() const;` — Get the Value input pin

### `Source/Editor/BlueprintGraph/Classes/K2Node_AsyncAction.h` (Public)


#### class `UK2Node_AsyncAction`  
`class UK2Node_AsyncAction : public UK2Node_BaseAsyncTask`  
_L20-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_BaseAsyncTask`
- L25 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L29 _private prototype_ `void InitializeProxyFromFunction(const UFunction* ProxyFunction);` — Initialize the async task from a known function

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_BaseAsyncTask.h` (Public)


#### struct `FAsyncTaskPinRedirectMapInfo`  
`struct FAsyncTaskPinRedirectMapInfo`  
_L44-47_
- L46 _public member_ `TMap<FName, TArray<UClass*> > OldPinToProxyClassMap;`

#### class `UK2Node_BaseAsyncTask`  
`class UK2Node_BaseAsyncTask : public UK2Node`  
_L54-157_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UK2Node`
- desc: Base class used for a blueprint node that calls a function and provides asynchronous exec pins when the function is complete. The created proxy object should have RF_StrongRefOnFrame flag.
- L60 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L61 _public prototype_ `virtual FText GetTooltipText() const override;`
- L62 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L63 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L64 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L65 _public prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;`
- L66 _public prototype_ `virtual FString GetPinMetaData(FName InPinName, FName InKey) override;`
- L67 _public prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L68 _public prototype_ `virtual bool IsLatentForMacros() const override;`
- L72 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;` — UK2Node interface
- L73 _public prototype_ `virtual FName GetCornerIcon() const override;`
- L74 _public prototype_ `virtual FText GetToolTipHeading() const override;`
- L75 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L76 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L77 _public prototype_ `virtual void GetRedirectPinNames(const UEdGraphPin& Pin, TArray<FString>& RedirectPinNames) const override;`
- L78 _public prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L82 _public prototype_ `UFunction* GetFactoryFunction() const;` — Returns the primary function that this node will call
- L96 _protected prototype_ `bool ExpandDefaultToSelfPin(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UK2Node_CallFunction* IntermediateProxyNode);` — If a the DefaultToSelf pin exists then it needs an actual connection to get properly casted during compilation. @param CompilerContext			The current compiler context used during expansion @param SourceGraph				The graph to place the expanded self node on @param IntermediateProxyNode		The spawned intermediate proxy node that has a DefaultToSelfPin @return	True if a successful connection was made to an intermediate node or if one was not necessary. False if a connection was failed.
- L100 _protected member_ `FName ProxyFactoryFunctionName;` — `UPROPERTY()` — The name of the function to call to create a proxy object
- L104 _protected member_ `TObjectPtr<UClass> ProxyFactoryClass;` — `UPROPERTY()` — The class containing the proxy object functions
- L108 _protected member_ `TObjectPtr<UClass> ProxyClass;` — `UPROPERTY()` — The type of proxy object that will be created
- L112 _protected member_ `FName ProxyActivateFunctionName;` — `UPROPERTY()` — The name of the 'go' function on the proxy object that will be called after delegates are in place, can be NAME_None
- L136 _protected member_ `static TMap<FName, FAsyncTaskPinRedirectMapInfo> AsyncTaskPinRedirectMap;` — Pin Redirector support
- L137 _protected member_ `static bool bAsyncTaskPinRedirectMapInitialized;`
- L140 _protected prototype_ `virtual bool HandleDelegates( const TArray<FBaseAsyncTaskHelper::FOutputPinAndLocalVariable>& VariableOutputs, UEdGraphPin* ProxyObjectPin, UEdGraphPin*& InOutLastThenPin, UEdGraph* SourceGraph, FKismetCompilerContext& CompilerContext);` — Expand out the logic to handle the delegate output pins
- L146 _private function_ `void InvalidatePinTooltips()` — Invalidates current pin tool tips, so that they will be refreshed before being displayed:
- L153 _private prototype_ `void GeneratePinTooltip(UEdGraphPin& Pin) const;` — Creates hover text for the specified pin. @param   Pin				The pin you want hover text for (should belong to this node)
- L156 _private member_ `mutable bool bPinTooltipsValid;` — Flag used to track validity of pin tooltips, when tooltips are invalid they will be refreshed before being displayed

#### struct `UK2Node_BaseAsyncTask::FBaseAsyncTaskHelper`  
`struct FBaseAsyncTaskHelper`  
_L114-133_
- L124 _public prototype_ `static bool ValidDataPin(const UEdGraphPin* Pin, EEdGraphPinDirection Direction);`
- L125 _public prototype_ `static bool CreateDelegateForNewFunction(UEdGraphPin* DelegateInputPin, FName FunctionName, UK2Node* CurrentNode, UEdGraph* SourceGraph, FKismetCompilerContext& CompilerContext);`
- L126 _public prototype_ `static bool CopyEventSignature(UK2Node_CustomEvent* CENode, UFunction* Function, const UEdGraphSchema_K2* Schema);`
- L127 _public prototype_ `static bool HandleDelegateImplementation( FMulticastDelegateProperty* CurrentProperty, const TArray<FBaseAsyncTaskHelper::FOutputPinAndLocalVariable>& VariableOutputs, UEdGraphPin* ProxyObjectPin, UEdGraphPin*& InOutLastThenPin, UEdGraphPin*& OutLastActivatedThenPin, UK2Node* CurrentNode, UEdGraph* SourceGraph, FKismetCompilerContext& CompilerContext);`
- L132 _public prototype_ `static const FName GetAsyncTaskProxyName();`

#### struct `UK2Node_BaseAsyncTask::FBaseAsyncTaskHelper::FOutputPinAndLocalVariable`  
`struct FOutputPinAndLocalVariable`  
_L116-122_
- L118 _public member_ `UEdGraphPin* OutputPin;`
- L119 _public member_ `UK2Node_TemporaryVariable* TempVar;`
- L121 _public function_ `FOutputPinAndLocalVariable(UEdGraphPin* Pin, UK2Node_TemporaryVariable* Var) : OutputPin(Pin), TempVar(Var)`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_BaseMCDelegate.h` (Public)


#### class `UK2Node_BaseMCDelegate`  
`class UK2Node_BaseMCDelegate : public UK2Node`  
_L16-77_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UK2Node`
- L22 _private member_ `FMemberReference DelegateReference;` — `UPROPERTY()` — Reference to delegate
- L27 _public function_ `virtual bool IsNodePure() const override` — UK2Node interface
- L28 _public prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L29 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L30 _public prototype_ `virtual FString GetDocumentationExcerptName() const override;`
- L31 _public function_ `virtual bool AllowMultipleSelfs(bool bInputAsArray) const override`
- L32 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L33 _public prototype_ `virtual void GetNodeAttributes( TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes ) const override;`
- L34 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L35 _public prototype_ `virtual bool HasDeprecatedReference() const override;`
- L36 _public prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType DeprecationType) const override;`
- L40 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L41 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L42 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L43 _public prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L46 _public function_ `void SetFromProperty(const FProperty* Property, bool bSelfContext, UClass* OwnerClass)`
- L51 _public function_ `FProperty* GetProperty() const`
- L56 _public function_ `FName GetPropertyName() const`
- L61 _public function_ `FText GetPropertyDisplayName() const`
- L67 _public prototype_ `UFunction* GetDelegateSignature(bool bForceNotFromSkelClass = false) const;`
- L69 _public prototype_ `UEdGraphPin* GetDelegatePin() const;`
- L72 _public prototype_ `bool IsAuthorityOnly() const;` — Is the delegate BlueprintAuthorityOnly
- L76 _protected member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/BlueprintGraph/Classes/K2Node_BitmaskLiteral.h` (Public)


#### class `UK2Node_BitmaskLiteral`  
`class UK2Node_BitmaskLiteral : public UK2Node, public INodeDependingOnEnumInterface`  
_L24-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,INodeDependingOnEnumInterface`
- L29 _private member_ `TObjectPtr<UEnum> BitflagsEnum;` — `UPROPERTY()`
- L32 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L36 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L37 _private prototype_ `virtual void ReconstructNode() override;`
- L38 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L42 _private function_ `virtual bool IsNodePure() const override`
- L43 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L44 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L45 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L46 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L50 _private function_ `virtual class UEnum* GetEnum() const override`
- L51 _private prototype_ `virtual void ReloadEnum(class UEnum* InEnum) override;`
- L52 _private function_ `virtual bool ShouldBeReconstructedAfterEnumChanged() const override`
- L55 _private prototype_ `static const FName& GetBitmaskInputPinName();`
- L59 _protected prototype_ `void ValidateBitflagsEnumType();` — Internal helper method used to validate the current enum type

### `Source/Editor/BlueprintGraph/Classes/K2Node_BreakStruct.h` (Public)


#### class `UK2Node_BreakStruct`  
`class UK2Node_BreakStruct : public UK2Node_StructMemberGet`  
_L28-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_StructMemberGet`
- L35 _private member_ `bool bMadeAfterOverridePinRemoval;` — `UPROPERTY()` — Helper property to handle upgrades from an old system of displaying pins for the override values that properties referenced as a conditional of being set in a struct
- L45 _private prototype_ `static bool CanBeBroken(const UScriptStruct* Struct, bool bForInternalUse = false);` — Returns false if: 1. The Struct has a 'native break' method Returns true if: 1. The Struct is tagged as BlueprintType and 2. The Struct has any property that is tagged as CPF_BlueprintVisible
- L48 _private function_ `static bool CanBeSplit(const UScriptStruct* Struct)` — Can this struct be used as a split pin
- L51 _private prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;` — UObject interface
- L52 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L56 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L57 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L58 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L59 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L60 _private prototype_ `virtual FText GetTooltipText() const override;`
- L61 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L62 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L63 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L67 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L68 _private function_ `virtual bool IsNodePure() const override`
- L69 _private function_ `virtual bool DrawNodeAsVariable() const override`
- L70 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L71 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L72 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L73 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L74 _private prototype_ `virtual void ConvertDeprecatedNode(UEdGraph* Graph, bool bOnlySafeChanges) override;`
- L79 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L80 _private member_ `FNodeTextCache CachedNodeTitle;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_CallArrayFunction.h` (Public)


#### struct `FArrayPropertyPinCombo`  
`struct FArrayPropertyPinCombo`  
_L21-30_
- L23 _public member_ `UEdGraphPin* ArrayPin;`
- L24 _public member_ `UEdGraphPin* ArrayPropPin;`
- L26 _public function_ `FArrayPropertyPinCombo() : ArrayPin(NULL) , ArrayPropPin(NULL)`

#### class `UK2Node_CallArrayFunction`  
`class UK2Node_CallArrayFunction : public UK2Node_CallFunction`  
_L33-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction`
- L38 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L39 _private prototype_ `virtual void PostReconstructNode() override;`
- L43 _private prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L44 _private function_ `virtual bool DoesInputWildcardPinAcceptArray(const UEdGraphPin* Pin) const override`
- L45 _private function_ `virtual bool DoesOutputWildcardPinAcceptContainer(const UEdGraphPin* Pin) const override`
- L46 _private prototype_ `virtual void ConvertDeprecatedNode(UEdGraph* Graph, bool bOnlySafeChanges) override;`
- L50 _private prototype_ `UEdGraphPin* GetTargetArrayPin() const;` — Retrieves the target pin for the function
- L57 _private prototype_ `void GetArrayPins(TArray< FArrayPropertyPinCombo >& OutArrayPinInfo ) const;` — Retrieves the array pins and their property pins as a combo-struct @param OutArrayPinInfo		The pins and their property pins will be added to this array
- L67 _private prototype_ `static bool IsWildcardProperty(UFunction* InArrayFunction, const FProperty* InProperty);` — Checks if the passed in property is a wildcard property @param InArrayFunction		The array function to check @param InProperty			Property to examine to see if it is marked in metadata as a wildcard @return						TRUE if the property is a wildcard.
- L75 _private prototype_ `void GetArrayTypeDependentPins(TArray<UEdGraphPin*>& OutPins) const;` — Gather all pins on this node that are dependent on the array type, including the Array target pin. @param OutPins		Array of pins to populate
- L77 _private prototype_ `void PropagateArrayTypeInfo(const UEdGraphPin* SourcePin);`

### `Source/Editor/BlueprintGraph/Classes/K2Node_CallDataTableFunction.h` (Public)


#### class `UK2Node_CallDataTableFunction`  
`class UK2Node_CallDataTableFunction : public UK2Node_CallFunction`  
_L16-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction`
- L21 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L22 _private prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L26 _private function_ `virtual bool CanToggleNodePurity() const override`

### `Source/Editor/BlueprintGraph/Classes/K2Node_CallDelegate.h` (Public)


#### class `UK2Node_CallDelegate`  
`class UK2Node_CallDelegate : public UK2Node_BaseMCDelegate`  
_L10-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_BaseMCDelegate`
- L17 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L18 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L22 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;` — UK2Node interface
- L23 _public prototype_ `virtual FName GetCornerIcon() const override;`
- L26 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L27 _public prototype_ `bool CreatePinsForFunctionInputs(const UFunction* Function);`

### `Source/Editor/BlueprintGraph/Classes/K2Node_CallFunction.h` (Public)


#### enum `ENodePurityOverride`  
`enum class ENodePurityOverride : int8`  
_L40-45_
- reflection: `UENUM()`
- L42 _public enumerator_ `Unset = 0`
- L43 _public enumerator_ `Pure`
- L44 _public enumerator_ `Impure`

#### class `UK2Node_CallFunction`  
`class UK2Node_CallFunction : public UK2Node`  
_L48-287_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L54 _private member_ `uint32 bDefaultsToPureFunc:1;` — `UPROPERTY()` — Indicates that the bound function defaults to a pure state
- L57 _private member_ `uint32 bIsPureFunc:1;` — `UE_DEPRECATED(5.5, "bIsPureFunc is deprecated. Use bDefaultsToPureFunc or IsNodePure instead.")`
- L61 _private member_ `uint32 bWantsEnumToExecExpansion:1;` — `UPROPERTY()` — Indicates that during compile we want to create multiple exec pins from an enum param
- L64 _private member_ `uint32 bIsConstFunc:1;` — `UE_DEPRECATED(5.5, "bIsConstFunc is deprecated. Check for FUNC_Const on FunctionReference.ResolveMember<UFunction>() instead.")`
- L67 _private member_ `uint32 bIsInterfaceCall:1;` — `UE_DEPRECATED(5.5, "bIsInterfaceCall is deprecated. Check for CLASS_Interface on FunctionReference.GetMemberParentClass() instead.")`
- L71 _private member_ `FMemberReference FunctionReference;` — `UPROPERTY()` — The function to call
- L76 _private member_ `FName CallFunctionName_DEPRECATED;` — `UPROPERTY()` — The name of the function to call
- L80 _private member_ `TSubclassOf<class UObject> CallFunctionClass_DEPRECATED;` — `UPROPERTY()` — The class that the function is from.
- L84 _protected member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's tooltip
- L88 _private member_ `mutable bool bPinTooltipsValid;` — Flag used to track validity of pin tooltips, when tooltips are invalid they will be refreshed before being displayed
- L90 _private member_ `TArray<UEdGraphPin*> ExpandAsEnumPins;`
- L95 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;` — UObject interface
- L96 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L100 _public prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;` — UEdGraphNode interface
- L101 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L102 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L103 _public prototype_ `virtual FString GetFindReferenceSearchString_Impl(EGetFindReferenceSearchStringFlags InFlags) const override;`
- L104 _public prototype_ `virtual FText GetTooltipText() const override;`
- L105 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L106 _public prototype_ `virtual FString GetDescriptiveCompiledName() const override;`
- L107 _public prototype_ `virtual bool HasDeprecatedReference() const override;`
- L108 _public prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType DeprecationType) const override;`
- L109 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L110 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L111 _public prototype_ `virtual FString GetDocumentationExcerptName() const override;`
- L112 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L113 _public prototype_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;`
- L114 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L115 _public prototype_ `virtual void AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L116 _public prototype_ `virtual void AddPinSearchMetaDataInfo(const UEdGraphPin* Pin, TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L117 _public prototype_ `virtual TSharedPtr<SWidget> CreateNodeImage() const override;`
- L118 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L119 _public prototype_ `virtual bool CanJumpToDefinition() const override;`
- L120 _public prototype_ `virtual void JumpToDefinition() const override;`
- L121 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L122 _public prototype_ `virtual FString GetPinMetaData(FName InPinName, FName InKey) override;`
- L123 _public prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L124 _public prototype_ `virtual bool IsLatentForMacros() const override;`
- L128 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;` — UK2Node interface
- L129 _public prototype_ `virtual bool IsNodePure() const override;`
- L130 _public prototype_ `virtual void PostReconstructNode() override;`
- L131 _public prototype_ `virtual bool ShouldDrawCompact() const override;`
- L132 _public prototype_ `virtual FText GetCompactNodeTitle() const override;`
- L133 _public prototype_ `virtual void PostPasteNode() override;`
- L134 _public prototype_ `virtual bool CanSplitPin(const UEdGraphPin* Pin) const override;`
- L135 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L136 _public prototype_ `virtual bool ShouldShowNodeProperties() const override;`
- L137 _public prototype_ `virtual void GetRedirectPinNames(const UEdGraphPin& Pin, TArray<FString>& RedirectPinNames) const override;`
- L138 _public prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L139 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L140 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L141 _public prototype_ `virtual FName GetCornerIcon() const override;`
- L142 _public prototype_ `virtual FText GetToolTipHeading() const override;`
- L143 _public prototype_ `virtual void GetNodeAttributes( TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes ) const override;`
- L144 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L145 _public prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L146 _public prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L150 _public prototype_ `UFunction* GetTargetFunction() const;` — Returns the UFunction that this class is pointing to
- L153 _public prototype_ `UEdGraphPin* GetReturnValuePin() const;` — Get the return value pin
- L156 _public prototype_ `bool IsLatentFunction() const;` — @return	true if the function is a latent operation
- L159 _public prototype_ `virtual bool AllowMultipleSelfs(bool bInputAsArray) const override;` — @return true if this function can be called on multiple contexts at once
- L168 _public prototype_ `virtual UEdGraphPin* CreateSelfPin(const UFunction* Function);` — Creates a self pin for the graph, taking into account the scope of the function call @param	Function	The function to be called by the Node. @return	Pointer to the pin that was created
- L177 _public prototype_ `bool CreatePinsForFunctionCall(const UFunction* Function);` — Creates all of the pins required to call a particular UFunction. @param	Function	The function to be called by the Node. @return	true on success.
- L180 _public prototype_ `void CreateExecPinsForFunctionCall(const UFunction* Function);` — Create exec pins for this function. May be multiple is using 'expand enum as execs'
- L183 _public prototype_ `FName GetFunctionName() const;` — Gets the name of the referenced function
- L185 _public function_ `virtual void PostParameterPinCreated(UEdGraphPin *Pin)`
- L188 _public prototype_ `static FText GetUserFacingFunctionName(const UFunction* Function, ENodeTitleType::Type NodeTitleType = ENodeTitleType::EditableTitle);` — `UE_DEPRECATED(5.5, "Moved to ObjectTools::GetUserFacingFunctionName.")`
- L191 _public prototype_ `static void GeneratePinTooltipFromFunction(UEdGraphPin& Pin, const UFunction* Function);` — Set up a pins tooltip from a function's tooltip
- L194 _public prototype_ `static FString GetDefaultTooltipForFunction(const UFunction* Function);` — `UE_DEPRECATED(5.5, "Moved to ObjectTools::GetDefaultTooltipForFunction.")`
- L197 _public prototype_ `static FText GetDefaultCategoryForFunction(const UFunction* Function, const FText& BaseCategory);` — Get default category for this function in action menu
- L199 _public prototype_ `static FText GetKeywordsForFunction(const UFunction* Function);` — Get keywords for this function in the action menu
- L201 _public prototype_ `static bool ShouldDrawCompact(const UFunction* Function);` — Should be drawn compact for this function
- L203 _public prototype_ `static FString GetCompactNodeTitle(const UFunction* Function);` — Get the compact name for this function
- L206 _public prototype_ `virtual FText GetFunctionContextString() const;` — Get the text to use to explain the context for this function (used on node title)
- L209 _public prototype_ `virtual void SetFromFunction(const UFunction* Function);` — Set properties of this node from a supplied function (does not save ref to function)
- L211 _public prototype_ `static void CallForEachElementInArrayExpansion(UK2Node* Node, UEdGraphPin* MultiSelf, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph);`
- L213 _public prototype_ `static UEdGraphPin* InnerHandleAutoCreateRef(UK2Node* Node, UEdGraphPin* Pin, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, bool bForceAssignment);`
- L220 _public prototype_ `UEdGraph* GetFunctionGraph(const UEdGraphNode*& OutGraphNode) const;` — Returns the graph for this function, if available. In cases of calling an event, it will be the ubergraph for the event @param OutGraphNode		If this function calls an event, this param is the event node, otherwise it is NULL
- L223 _public prototype_ `static bool IsStructureWildcardProperty(const UFunction* InFunction, const FName PropertyName);` — Checks if the property is marked as "CustomStructureParam"
- L226 _public prototype_ `static bool IsWildcardProperty(const UFunction* InFunction, const FProperty* InProperty);` — returns true if InProperty should be treated as a wildcard (e.g. due to SetParam markup)
- L229 _public prototype_ `static bool CanFunctionSupportMultipleTargets(UFunction const* InFunction);` — Used to determine the result of AllowMultipleSelfs() (without having a node instance)
- L232 _public prototype_ `static bool CanEditorOnlyFunctionBeCalled(const UFunction* InFunction, const UObject* InObject);` — Checks if the input function can be called in the input object with respect to editor-only/runtime mismatch
- L235 _public prototype_ `static FSlateIcon GetPaletteIconForFunction(UFunction const* Function, FLinearColor& OutColor);`
- L237 _public prototype_ `static void GetExpandEnumPinNames(const UFunction* Function, TArray<FName>& EnumNamesToCheck);`
- L241 _private prototype_ `void DetermineWantsEnumToExecExpansion(const UFunction* Function);` — Looks at function metadata and properties to determine if this node should be using enum to exec expansion
- L248 _private prototype_ `void GeneratePinTooltip(UEdGraphPin& Pin) const;` — Creates hover text for the specified pin. @param   Pin				The pin you want hover text for (should belong to this node)
- L253 _private prototype_ `bool ReconnectPureExecPins(TArray<UEdGraphPin*>& OldPins);` — Connect Execute and Then pins for functions, which became pure.
- L256 _private prototype_ `void ConformContainerPins();` — Conforms container pins
- L259 _private member_ `ENodePurityOverride NodePurityOverride;` — `UPROPERTY()`
- L261 _private prototype_ `bool AreExecPinsVisible() const;`
- L262 _private prototype_ `bool FunctionHasOutputs() const;`
- L263 _private prototype_ `void ToggleNodePurityOverride();`
- L268 _protected prototype_ `void InvalidatePinTooltips();` — Invalidates current pin tool tips, so that they will be refreshed before being displayed:
- L271 _protected prototype_ `virtual void FixupSelfMemberContext();` — Helper function to ensure function is called in our context
- L274 _protected prototype_ `virtual bool CanToggleNodePurity() const;` — By default, pure nodes can be toggled. Return false if you don't want your node to support toggling.
- L277 _protected prototype_ `void SuppressDeprecationWarning() const;` — Adds this function to the suppressed deprecation warnings list for this project
- L280 _protected prototype_ `static TSet<FName> GetRequiredParamNames(const UFunction* ForFunction);` — Helper function for searching a UFunction for the names of requires pins/params:
- L283 _protected prototype_ `void ValidateRequiredPins(const UFunction* Function, class FCompilerResultsLog& MessageLog) const;` — Routine for validating that all UPARAM(Required) parmas have a connection:
- L286 _protected prototype_ `UFunction* GetTargetFunctionFromSkeletonClass() const;` — Helper function to find UFunction entries from the skeleton class, use with caution..

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_CallFunctionOnMember.h` (Public)


#### class `UK2Node_CallFunctionOnMember`  
`class UK2Node_CallFunctionOnMember : public UK2Node_CallFunction`  
_L22-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction`
- L28 _private member_ `FMemberReference MemberVariableToCallOn;` — `UPROPERTY()` — Reference to member variable to call function on
- L30 _private prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L33 _private prototype_ `virtual UEdGraphPin* CreateSelfPin(const UFunction* Function) override;`
- L34 _private prototype_ `virtual FText GetFunctionContextString() const override;`
- L35 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L36 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L39 _protected function_ `virtual bool CanToggleNodePurity() const override`

### `Source/Editor/BlueprintGraph/Classes/K2Node_CallMaterialParameterCollectionFunction.h` (Public)


#### class `UK2Node_CallMaterialParameterCollectionFunction`  
`class UK2Node_CallMaterialParameterCollectionFunction : public UK2Node_CallFunction`  
_L16-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction`
- L21 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L22 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L23 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_CallParentFunction.h` (Public)


#### class `UK2Node_CallParentFunction`  
`class UK2Node_CallParentFunction : public UK2Node_CallFunction`  
_L20-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction`
- L25 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L27 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L28 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L29 _private prototype_ `virtual void AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L32 _private prototype_ `virtual void SetFromFunction(const UFunction* Function) override;`
- L37 _protected prototype_ `virtual void FixupSelfMemberContext() override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_CastByteToEnum.h` (Public)


#### class `UK2Node_CastByteToEnum`  
`class UK2Node_CastByteToEnum : public UK2Node, public INodeDependingOnEnumInterface`  
_L31-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,INodeDependingOnEnumInterface`
- L36 _private member_ `TObjectPtr<UEnum> Enum;` — `UPROPERTY()`
- L40 _private member_ `bool bSafe;` — `UPROPERTY()` — if true, the node returns always a valid value
- L42 _private member_ `static const FName ByteInputPinName;`
- L45 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L46 _private prototype_ `virtual FText GetTooltipText() const override;`
- L47 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L48 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L49 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L53 _private prototype_ `virtual FText GetCompactNodeTitle() const override;`
- L54 _private function_ `virtual bool ShouldDrawCompact() const override`
- L55 _private function_ `virtual bool IsNodePure() const override`
- L56 _private prototype_ `FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override;`
- L57 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L58 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L59 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L60 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L64 _private function_ `virtual class UEnum* GetEnum() const override` — INodeDependingOnEnumInterface
- L65 _private prototype_ `virtual void ReloadEnum(class UEnum* InEnum) override;`
- L66 _private function_ `virtual bool ShouldBeReconstructedAfterEnumChanged() const override`
- L69 _private prototype_ `virtual FName GetFunctionName() const;`
- L73 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's tooltip

### `Source/Editor/BlueprintGraph/Classes/K2Node_ClassDynamicCast.h` (Public)


#### class `UK2Node_ClassDynamicCast`  
`class UK2Node_ClassDynamicCast : public UK2Node_DynamicCast`  
_L22-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_DynamicCast`
- L27 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L28 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L29 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L30 _private prototype_ `virtual FText GetTooltipText() const override;`
- L34 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L35 _private function_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override`
- L36 _private function_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override`
- L40 _private prototype_ `virtual UEdGraphPin* GetCastSourcePin() const override;`
- L41 _private prototype_ `virtual UEdGraphPin* GetBoolSuccessPin() const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_ClearDelegate.h` (Public)


#### class `UK2Node_ClearDelegate`  
`class UK2Node_ClearDelegate : public UK2Node_BaseMCDelegate`  
_L10-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_BaseMCDelegate`
- L16 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L20 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_CommutativeAssociativeBinaryOperator.h` (Public)


#### class `UK2Node_CommutativeAssociativeBinaryOperator`  
`class UK2Node_CommutativeAssociativeBinaryOperator : public UK2Node_CallFunction, public IK2Node_AddPinInterface`  
_L19-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction,IK2Node_AddPinInterface`
- L25 _private member_ `int32 NumAdditionalInputs;` — `UPROPERTY()` — The number of additional input pins to generate for this node (2 base pins are not included)
- L28 _private member_ `const static int32 BinaryOperatorInputsNum = 2;`
- L30 _private prototype_ `FEdGraphPinType GetType() const;`
- L32 _private prototype_ `void AddInputPinInner(int32 AdditionalPinIndex);`
- L35 _protected prototype_ `bool CanRemovePin(const UEdGraphPin* Pin) const override;`
- L38 _public prototype_ `UEdGraphPin* FindOutPin() const;`
- L39 _public prototype_ `UEdGraphPin* FindSelfPin() const;`
- L42 _public prototype_ `UEdGraphPin* GetInputPin(int32 InputPinIndex);` — Get TRUE input type (self, etc.. are skipped)
- L45 _public function_ `int32 GetNumberOfAdditionalInputs() const` — Returns the number of additional input pins that this node has
- L47 _public prototype_ `virtual void RemoveInputPin(UEdGraphPin* Pin) override;`
- L50 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L51 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L52 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L53 _public function_ `virtual bool IncludeParentNodeContextMenu() const override`
- L57 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;` — UK2Node interface
- L61 _public prototype_ `virtual void AddInputPin() override;` — IK2Node_AddPinInterface interface
- L62 _public prototype_ `virtual bool CanAddPin() const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_ComponentBoundEvent.h` (Public)


#### class `UK2Node_ComponentBoundEvent`  
`class UK2Node_ComponentBoundEvent : public UK2Node_Event`  
_L30-91_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Event`
- L36 _private member_ `FName DelegatePropertyName;` — `UPROPERTY()` — Delegate property name that this event is associated with
- L40 _private member_ `TObjectPtr<UClass> DelegateOwnerClass;` — `UPROPERTY()` — Delegate property's owner class that this event is associated with
- L44 _private member_ `FName ComponentPropertyName;` — `UPROPERTY()` — Name of property in Blueprint class that pointer to component we want to bind to
- L47 _private prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;`
- L48 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L52 _private prototype_ `virtual void ReconstructNode() override;`
- L53 _private prototype_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;`
- L54 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L55 _private prototype_ `virtual FText GetTooltipText() const override;`
- L56 _private prototype_ `virtual FString GetDocumentationLink() const override;`
- L57 _private prototype_ `virtual FString GetDocumentationExcerptName() const override;`
- L58 _private prototype_ `virtual bool HasDeprecatedReference() const override;`
- L59 _private prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType DeprecationType) const override;`
- L63 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L64 _private prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L65 _private prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`
- L66 _private prototype_ `virtual void HandleVariableRenamed(UBlueprint* InBlueprint, UClass* InVariableClass, UEdGraph* InGraph, const FName& InOldVarName, const FName& InNewVarName) override;`
- L67 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L70 _private prototype_ `virtual bool IsUsedByAuthorityOnlyDelegate() const override;`
- L73 _private prototype_ `FMulticastDelegateProperty* GetTargetDelegateProperty() const;` — Return the delegate property that this event is bound to
- L76 _private prototype_ `FText GetTargetDelegateDisplayName() const;` — Gets the proper display name for the property
- L78 _private prototype_ `void InitializeComponentBoundEventParams(FObjectProperty const* InComponentProperty, const FMulticastDelegateProperty* InDelegateProperty);`
- L82 _public function_ `FName GetComponentPropertyName() const`
- L87 _private prototype_ `bool IsDelegateValid() const;` — Returns true if there is an FObjectProperty on this blueprint with a name that matches ComponentPropertyName
- L90 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/BlueprintGraph/Classes/K2Node_Composite.h` (Public)


#### class `UK2Node_Composite`  
`class UK2Node_Composite : public UK2Node_Tunnel`  
_L26-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Tunnel`
- L32 _private member_ `TObjectPtr<class UEdGraph> BoundGraph;` — `UPROPERTY()` — The graph that this composite node is representing
- L35 _private prototype_ `virtual void PostEditUndo() override;`
- L39 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L40 _private prototype_ `virtual void DestroyNode() override;`
- L41 _private prototype_ `virtual void PostPasteNode() override;`
- L42 _private prototype_ `virtual FText GetTooltipText() const override;`
- L43 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L44 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L45 _private prototype_ `virtual bool CanUserDeleteNode() const override;`
- L46 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L47 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L48 _private prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L49 _private prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L50 _private function_ `virtual TArray<UEdGraph*> GetSubGraphs() const override`
- L51 _private prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;`
- L55 _private function_ `virtual bool DrawNodeAsExit() const override`
- L56 _private function_ `virtual bool DrawNodeAsEntry() const override`
- L57 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L61 _private prototype_ `UK2Node_Tunnel* GetEntryNode() const;` — Get the entry/exit nodes inside this collapsed graph
- L62 _private prototype_ `UK2Node_Tunnel* GetExitNode() const;`
- L66 _protected prototype_ `void FixupInputAndOutputSink();` — Fixes up the input and output sink when needed, useful after PostEditUndo which changes which graph these nodes point to
- L73 _private prototype_ `void RenameBoundGraphCloseToName(const FString& Name);` — Rename the BoundGraph to a unique name - this is a special case rename: RenameGraphCloseToName() assumes that we are only concurrned with the immediate Outer() scope, but in the case of the BoundGraph we must also look into the Outer of the composite node(a Graph), and make sure no graphs in its SubGraph array are already using the name.
- L76 _private prototype_ `bool IsCompositeNameAvailable( const FString& NewName );` — Determine if the name already used by another graph in composite nodes chain
- L79 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_ConstructObjectFromClass.h` (Public)


#### class `UK2Node_ConstructObjectFromClass`  
`class UK2Node_ConstructObjectFromClass : public UK2Node`  
_L29-108_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UK2Node`
- L34 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L35 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L36 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L37 _private prototype_ `virtual FText GetTooltipText() const override;`
- L38 _private prototype_ `virtual FText GetKeywords() const override;`
- L39 _private prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L40 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L41 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin);`
- L42 _private prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;`
- L43 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L44 _private prototype_ `virtual void AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L45 _private prototype_ `virtual FString GetPinMetaData(FName InPinName, FName InKey) override;`
- L49 _private function_ `virtual bool IsNodeSafeToIgnore() const override`
- L50 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L51 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L52 _private prototype_ `virtual void GetNodeAttributes( TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes ) const override;`
- L53 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L54 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L58 _private prototype_ `virtual void CreatePinsForClass(UClass* InClass, TArray<UEdGraphPin*>* OutClassPins = nullptr);` — Create new pins to show properties on archetype
- L61 _private prototype_ `virtual bool IsSpawnVarPin(UEdGraphPin* Pin) const;` — See if this is a spawn variable pin, or a 'default' pin
- L64 _private prototype_ `UEdGraphPin* GetClassPin(const TArray<UEdGraphPin*>* InPinsToSearch=NULL) const;` — Get the blueprint input pin
- L66 _private prototype_ `UEdGraphPin* GetWorldContextPin() const;` — Get the world context input pin, can return NULL
- L68 _private prototype_ `UEdGraphPin* GetResultPin() const;` — Get the result output pin
- L70 _private prototype_ `UEdGraphPin* GetOuterPin() const;` — Get the result input pin
- L73 _private prototype_ `UClass* GetClassToSpawn(const TArray<UEdGraphPin*>* InPinsToSearch=NULL) const;` — Get the class that we are going to spawn, if it's defined as default value
- L76 _private prototype_ `virtual bool UseWorldContext() const;` — Returns if the node uses World Object Context input
- L79 _private function_ `virtual bool UseOuter() const` — Returns if the node uses Outer input
- L83 _protected prototype_ `virtual FText GetBaseNodeTitle() const;` — Gets the node for use in lists and menus
- L85 _protected prototype_ `virtual FText GetDefaultNodeTitle() const;` — Gets the default node title when no class is selected
- L87 _protected prototype_ `virtual FText GetNodeTitleFormat() const;` — Gets the node title when a class has been selected.
- L89 _protected prototype_ `virtual UClass* GetClassPinBaseClass() const;` — Gets base class to use for the 'class' pin.  UObject by default.
- L98 _protected prototype_ `void SetPinToolTip(UEdGraphPin& MutatablePin, const FText& PinDescription) const;` — Takes the specified "MutatablePin" and sets its 'PinToolTip' field (according to the specified description) @param   MutatablePin	The pin you want to set tool-tip text on @param   PinDescription	A string describing the pin's purpose
- L101 _protected prototype_ `void OnClassPinChanged();` — Refresh pins when class was changed
- L104 _protected member_ `FText NodeTooltip;` — Tooltip text for this node.
- L107 _protected member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_ConvertAsset.h` (Public)


#### class `UK2Node_ConvertAsset`  
`class UK2Node_ConvertAsset : public UK2Node`  
_L25-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- desc: This node converts between hard and soft references, for both objects and classes. The name is historical from when they were called asset IDs
- L31 _public prototype_ `UClass* GetTargetClass() const;` — Returns the class for the object being converted
- L33 _public prototype_ `bool IsClassType() const;` — True if this is converting a class, false for object or unknown
- L35 _public prototype_ `bool IsConvertToSoft() const;` — True if this is going from hard to soft, false for opposite or unknown
- L38 _public prototype_ `UEdGraphPin* GetInputPin() const;` — Pin Accessors
- L39 _public prototype_ `UEdGraphPin* GetOutputPin() const;`
- L42 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L43 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L44 _public prototype_ `virtual FText GetKeywords() const override;`
- L45 _public prototype_ `virtual FText GetTooltipText() const override;`
- L49 _public prototype_ `virtual void PostReconstructNode() override;` — UK2Node interface
- L50 _public function_ `virtual bool IsNodePure() const override`
- L51 _public function_ `virtual bool ShouldDrawCompact() const override`
- L52 _public function_ `virtual int32 GetNodeRefreshPriority() const override`
- L53 _public function_ `virtual bool DoesInputWildcardPinAcceptArray(const UEdGraphPin* Pin) const override`
- L54 _public function_ `virtual bool DoesOutputWildcardPinAcceptContainer(const UEdGraphPin* Pin) const override`
- L56 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L57 _public prototype_ `virtual FText GetCompactNodeTitle() const override;`
- L58 _public prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const;`
- L59 _public prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L60 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L61 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L62 _public prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L66 _protected prototype_ `void RefreshPinTypes();`

### `Source/Editor/BlueprintGraph/Classes/K2Node_Copy.h` (Public)


#### class `UK2Node_Copy`  
`class UK2Node_Copy : public UK2Node`  
_L23-55_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Duplicate"))`
- inherits: `UK2Node`
- L28 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L29 _private prototype_ `virtual FText GetTooltipText() const override;`
- L30 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L31 _private prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L35 _private prototype_ `virtual void PostReconstructNode() override;`
- L36 _private function_ `virtual bool IsNodeSafeToIgnore() const override`
- L37 _private function_ `virtual bool IsNodePure() const override`
- L38 _private prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L39 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L40 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L41 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L42 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L43 _private function_ `virtual int32 GetNodeRefreshPriority() const override`
- L44 _private function_ `virtual bool CanSplitPin(const UEdGraphPin* Pin) const override`
- L48 _private prototype_ `UEdGraphPin* GetInputReferencePin() const;` — Get the input reference pin
- L50 _private prototype_ `UEdGraphPin* GetCopyResultPin() const;` — Get the return value pin
- L54 _protected prototype_ `void PropagatePinType(FEdGraphPinType& InType);` — Propagates pin type to the between the input and output pins

### `Source/Editor/BlueprintGraph/Classes/K2Node_CreateDelegate.h` (Public)


#### class `UK2Node_CreateDelegate`  
`class UK2Node_CreateDelegate : public UK2Node`  
_L28-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L33 _private member_ `FName SelectedFunctionName;` — `UPROPERTY(meta = (BlueprintSearchable = "true"))`
- L36 _private member_ `FGuid SelectedFunctionGuid;` — `UPROPERTY()`
- L40 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L41 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L42 _public prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L43 _public prototype_ `virtual void NodeConnectionListChanged() override;`
- L44 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L45 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L46 _public prototype_ `virtual void FindDiffs(UEdGraphNode* OtherNode, struct FDiffResults& Results) override;`
- L47 _public prototype_ `virtual void AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L51 _public function_ `virtual bool IsNodePure() const override` — UK2Node interface
- L52 _public prototype_ `virtual void PostReconstructNode() override;`
- L53 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L54 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L55 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L56 _public function_ `virtual int32 GetNodeRefreshPriority() const override`
- L57 _public prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L60 _public prototype_ `bool IsValid(FString* OutMsg = nullptr, bool bDontUseSkeletalClassForSelf = false) const;`
- L63 _public prototype_ `void SetFunction(FName Name);` — Set new Function name (Without notifying about the change)
- L65 _public prototype_ `UFunction* GetDelegateSignature() const;`
- L66 _public prototype_ `UClass* GetScopeClass(bool bDontUseSkeletalClassForSelf = false) const;`
- L68 _public prototype_ `FName GetFunctionName() const;`
- L69 _public prototype_ `UEdGraphPin* GetDelegateOutPin() const;`
- L70 _public prototype_ `UEdGraphPin* GetObjectInPin() const;`
- L72 _public prototype_ `void HandleAnyChange(bool bForceModify = false);`
- L73 _public prototype_ `void HandleAnyChangeWithoutNotifying();`
- L75 _public prototype_ `void ValidationAfterFunctionsAreCreated(class FCompilerResultsLog& MessageLog, bool bFullCompile) const;`
- L78 _public prototype_ `void HandleAnyChange(UEdGraph*& OutGraph, UBlueprint*& OutBlueprint);` — return Graph and Blueprint, when they should be notified about change. It allows to call BroadcastChanged only once per blueprint.

### `Source/Editor/BlueprintGraph/Classes/K2Node_CustomEvent.h` (Public)


#### class `UK2Node_CustomEvent`  
`class UK2Node_CustomEvent : public UK2Node_Event`  
_L35-135_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Event`
- L41 _private member_ `FString DeprecationMessage;` — `UPROPERTY()` — Optional message to display when the event is deprecated
- L45 _private member_ `bool bIsDeprecated;` — `UPROPERTY()` — Specifies that usage of this event has been deprecated
- L49 _private member_ `bool bCallInEditor;` — `UPROPERTY()` — Specifies that the event can be triggered in Editor
- L51 _private prototype_ `virtual bool IsEditable() const override;`
- L54 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L58 _private prototype_ `virtual void ReconstructNode() override;`
- L59 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L60 _private prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L61 _private prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L62 _private prototype_ `virtual FText GetTooltipText() const override;`
- L63 _private prototype_ `virtual FString GetDocumentationLink() const override;`
- L64 _private prototype_ `virtual FString GetDocumentationExcerptName() const override;`
- L65 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L66 _private prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L67 _private prototype_ `virtual void AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L68 _private prototype_ `virtual FText GetKeywords() const override;`
- L69 _private function_ `virtual bool HasDeprecatedReference() const override`
- L70 _private prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType DeprecationType) const override;`
- L71 _private prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L75 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L76 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L77 _private prototype_ `virtual void FixupPinStringDataReferences(FArchive* SavingArchive) override;`
- L78 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L82 _private function_ `virtual bool ShouldUseConstRefParams() const override`
- L83 _private prototype_ `virtual UEdGraphPin* CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> NewPinInfo) override;`
- L84 _private prototype_ `virtual bool CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage) override;`
- L85 _private prototype_ `virtual bool ModifyUserDefinedPinDefaultValue(TSharedPtr<FUserPinInfo> PinInfo, const FString& NewDefaultValue) override;`
- L88 _private prototype_ `virtual bool IsUsedByAuthorityOnlyDelegate() const override;`
- L91 _private prototype_ `void RenameCustomEventCloseToName(int32 StartIndex = 1);` — Rename this custom event to have unique name
- L93 _private prototype_ `static UK2Node_CustomEvent* CreateFromFunction(FVector2D GraphPosition, UEdGraph* ParentGraph, const FString& Name, const UFunction* Function, bool bSelectNewNode = true);`
- L102 _private prototype_ `bool IsOverride() const;` — Discernible from the base UK2Node_Event's bOverrideFunction field. This checks to see if this UK2Node_CustomEvent overrides another CustomEvent declared in a parent blueprint. @return True if this CustomEvent's name matches another CustomEvent's name, declared in a parent (false if not).
- L111 _private prototype_ `uint32 GetNetFlags() const;` — If a CustomEvent overrides another CustomEvent, then it inherits the super's net flags. This method does that work for you, either returning the super function's flags, or this node's flags (if it's not an override). @return If this CustomEvent is an override, then this is the super's net flags, otherwise it's from the FunctionFlags set on this node.
- L119 _private prototype_ `void SetDelegateSignature(const UFunction* DelegateSignature);` — Updates the Signature of this event. Empties current pins and adds the new given parameters. Does nothing if DelegateSignature is nullptr @param DelegateSignature	The new signature for this function to have
- L123 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title
- L127 _private member_ `FKismetUserDeclaredFunctionMetadata MetaData;` — `UPROPERTY()` — Custom event metadata that can be used for adding custom keywords
- L131 _public function_ `FKismetUserDeclaredFunctionMetadata& GetUserDefinedMetaData()`

### `Source/Editor/BlueprintGraph/Classes/K2Node_DeadClass.h` (Public)


#### class `UK2Node_DeadClass`  
`class UK2Node_DeadClass : public UK2Node`  
_L15-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`

### `Source/Editor/BlueprintGraph/Classes/K2Node_DelegateSet.h` (Public)


#### class `UK2Node_DelegateSet`  
`class UK2Node_DelegateSet : public UK2Node`  
_L28-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L34 _private member_ `FName DelegatePropertyName;` — `UPROPERTY()` — Delegate property name that this event is associated with on the target
- L38 _private member_ `TSubclassOf<class UObject> DelegatePropertyClass;` — `UPROPERTY()` — Class that the delegate property is defined in
- L41 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L42 _private prototype_ `virtual FText GetTooltipText() const override;`
- L43 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L44 _private function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L49 _private function_ `virtual bool DrawNodeAsEntry() const override`
- L50 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L51 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L52 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L53 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L54 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L58 _private prototype_ `UEdGraphPin* GetDelegateOwner() const;` — @todo document
- L61 _private function_ `FName GetDelegateTargetEntryPointName() const` — @todo document
- L68 _private prototype_ `UFunction* GetDelegateSignature();` — @todo document
- L69 _private prototype_ `UFunction* GetDelegateSignature() const;`
- L73 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L74 _private member_ `FNodeTextCache CachedNodeTitle;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_DoOnceMultiInput.h` (Public)


#### class `UK2Node_DoOnceMultiInput`  
`class UK2Node_DoOnceMultiInput : public UK2Node, public IK2Node_AddPinInterface`  
_L23-76_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,IK2Node_AddPinInterface`
- L29 _private member_ `int32 NumAdditionalInputs;` — `UPROPERTY()` — The number of additional input pins to generate for this node (2 base pins are not included)
- L31 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L35 _private member_ `TObjectPtr<class UK2Node_TemporaryVariable> DataNode;` — `UPROPERTY(transient)` — Reference to the integer that contains
- L37 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L41 _private member_ `const static int32 NumBaseInputs = 1;`
- L43 _private prototype_ `static FText GetNameForPin(int32 PinIndex, bool In);`
- L45 _private prototype_ `FEdGraphPinType GetInType() const;`
- L46 _private prototype_ `FEdGraphPinType GetOutType() const;`
- L48 _private prototype_ `void AddPinsInner(int32 AdditionalPinIndex);`
- L49 _private prototype_ `bool CanRemovePin(const UEdGraphPin* Pin) const override;`
- L51 _public prototype_ `UEdGraphPin* FindOutPin() const;`
- L52 _public prototype_ `UEdGraphPin* FindSelfPin() const;`
- L55 _public prototype_ `UEdGraphPin* GetInputPin(int32 InputPinIndex);` — Get TRUE input type (self, etc.. are skipped)
- L56 _public prototype_ `UEdGraphPin* GetOutputPin(int32 InputPinIndex);`
- L58 _public prototype_ `virtual void RemoveInputPin(UEdGraphPin* Pin) override;`
- L61 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L62 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L63 _public function_ `virtual bool IncludeParentNodeContextMenu() const override`
- L67 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;` — UK2Node interface
- L68 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L69 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L73 _public prototype_ `virtual void AddInputPin() override;` — IK2Node_AddPinInterface interface
- L74 _public prototype_ `virtual bool CanAddPin() const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_DynamicCast.h` (Public)


#### enum `EPureState`  
`enum class EPureState : uint8`  
_L29-34_
- reflection: `UENUM()`
- L31 _public enumerator_ `Pure`
- L32 _public enumerator_ `Impure`
- L33 _public enumerator_ `UseDefault`

#### class `UK2Node_DynamicCast`  
`class UK2Node_DynamicCast : public UK2Node`  
_L37-129_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L43 _private member_ `TSubclassOf<class UObject> TargetType;` — `UPROPERTY()` — The type that the input should try to be cast to
- L46 _private prototype_ `virtual void Serialize(FArchive& Ar);`
- L50 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L51 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L52 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L53 _private prototype_ `virtual FText GetTooltipText() const override;`
- L54 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L55 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L56 _private function_ `virtual bool IncludeParentNodeContextMenu() const override`
- L57 _private prototype_ `virtual void PostReconstructNode() override;`
- L58 _private prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L62 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L63 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L64 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L65 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L66 _private function_ `virtual bool IsNodePure() const override`
- L67 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L68 _private prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L69 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L70 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L71 _private prototype_ `virtual bool IsActionFilteredOut(const class FBlueprintActionFilter& Filter) override;`
- L75 _private prototype_ `UEdGraphPin* GetValidCastPin() const;` — Get the 'valid cast' exec pin
- L78 _private prototype_ `UEdGraphPin* GetInvalidCastPin() const;` — Get the 'invalid cast' exec pin
- L81 _private prototype_ `UEdGraphPin* GetCastResultPin() const;` — Get the cast result pin
- L84 _private prototype_ `virtual UEdGraphPin* GetCastSourcePin() const;` — Get the input object to be casted pin
- L87 _private prototype_ `virtual UEdGraphPin* GetBoolSuccessPin() const;` — Get the boolean output pin that signifies a successful/failed cast.
- L95 _private prototype_ `void SetPurity(bool bNewPurity);` — Will change the node's purity, and reallocate pins accordingly (adding/ removing exec pins). @param  bNewPurity  Whether to configure node as pure.
- L99 _protected prototype_ `void CreateExecPins();` — Determine purity and create exec pins if needed
- L102 _protected prototype_ `void CreateSuccessPin();` — Create success output signal pin (visible only if pure)
- L105 _protected prototype_ `void TogglePurity();` — Flips the node's purity (adding/removing exec pins as needed).
- L108 _protected prototype_ `bool ReconnectPureExecPins(TArray<UEdGraphPin*>& OldPins);` — Update exec pins when converting from impure to pure.
- L111 _protected prototype_ `void InitPureState();` — Sets the pure state to Pure or Impure if it's using the default one
- L114 _protected member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title
- L118 _protected member_ `bool bIsPureCast;` — `UE_DEPRECATED(5.3, "Use IsNodePure() instead.")` — [DEPRECATED] This member is no longer in use.
- L124 _private member_ `EPureState PureState;` — `UPROPERTY()` — Internal state used to determine purity
- L128 _private member_ `bool bIsPureCast_DEPRECATED;` — `UPROPERTY()` — [DEPRECATED] Receives the old value on load if previously saved

### `Source/Editor/BlueprintGraph/Classes/K2Node_EaseFunction.h` (Public)


#### struct `FCustomPin`  
`struct FCustomPin`  
_L28-43_
- reflection: `USTRUCT()`
- L34 _public member_ `FName PinName;` — `UPROPERTY()` — Name of the pin within the current node
- L38 _public member_ `FName CallFuncPinName;` — `UPROPERTY()` — Name of the pin of the call function
- L42 _public member_ `bool bValuePin = false;` — `UPROPERTY()` — If TRUE this is a custom pin that does come from the type of wildcard pin connected

#### class `UK2Node_EaseFunction`  
`class UK2Node_EaseFunction : public UK2Node`  
_L46-119_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L51 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L52 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L53 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Contex) const override;`
- L54 _private function_ `virtual bool IncludeParentNodeContextMenu() const override`
- L55 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L56 _private prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L57 _private prototype_ `virtual FText GetTooltipText() const override;`
- L58 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L62 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L63 _private prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L64 _private prototype_ `virtual void PostReconstructNode() override;`
- L65 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L66 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L67 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L68 _private function_ `virtual bool IsNodePure() const override`
- L73 _private prototype_ `void ResetToWildcards();` — Reset the A, B and Result pins to its initial wildcard state
- L76 _private prototype_ `UEdGraphPin* GetEaseFuncPin() const;` — returns the EaseFunc pin
- L79 _private function_ `bool CanCustomizeCurve() const` — Returns TRUE if the selected curve can feature customization, FALSE otherwise
- L90 _private prototype_ `void ChangePinType(UEdGraphPin* Pin);` — Notification from the editor that the user wants to change the PinType on a selected pin @param Pin	The pin the user wants to change the type for
- L93 _private prototype_ `void RefreshPinVisibility();` — Generates the available custom pins for the current ease function if applicable
- L96 _private prototype_ `bool UpdatePin(UEdGraphPin* MyPin, UEdGraphPin* OtherPin);` — Update MyPin with data from another pin. Return FALSE in case nothing was changed, TRUE otherwise.
- L105 _private prototype_ `void SetPinToolTip(UEdGraphPin& MutatablePin, const FText& PinDescription) const;` — Takes the specified "MutatablePin" and sets its 'PinToolTip' field (according to the specified description) @param   MutatablePin	The pin you want to set tool-tip text on @param   PinDescription	A string describing the pin's purpose
- L108 _private prototype_ `void GenerateExtraPins();` — Called right after the wildcard pins has been assigned a value
- L112 _private member_ `FName EaseFunctionName;` — `UPROPERTY()` — Name of the kismet ease function to be called
- L115 _private member_ `FText NodeTooltip;` — Tooltip text for this node.
- L118 _private member_ `UEdGraphPin* CachedEaseFuncPin;` — The "EaseFunc" input pin, used to enable/disable easing customization

### `Source/Editor/BlueprintGraph/Classes/K2Node_EditablePinBase.h` (Public)


#### struct `FUserPinInfo`  
`struct FUserPinInfo`  
_L31-60_
- reflection: `USTRUCT()`
- L35 _public function_ `FUserPinInfo() : DesiredPinDirection(EGPD_MAX)`
- L40 _public prototype_ `explicit FUserPinInfo(const UEdGraphPin& InPin);` — Constructs a FUserPinInfo to match an existing Pin
- L44 _public member_ `FName PinName;` — `UPROPERTY()` — The name of the pin, as defined by the user
- L48 _public member_ `struct FEdGraphPinType PinType;` — `UPROPERTY()` — Type info for the pin
- L52 _public member_ `TEnumAsByte<EEdGraphPinDirection> DesiredPinDirection;` — `UPROPERTY()` — Desired direction for the pin. The direction will be forced to work with the node if necessary
- L56 _public member_ `FString PinDefaultValue;` — `UPROPERTY()` — The default value of the pin

#### struct `FKismetUserDeclaredFunctionMetadata`  
`struct FKismetUserDeclaredFunctionMetadata`  
_L65-130_
- reflection: `USTRUCT()`
- desc: This structure describes metadata associated with a user declared function or macro It will be turned into regular metadata during compilation
- L70 _public member_ `FText ToolTip;` — `UPROPERTY()`
- L73 _public member_ `FText Category;` — `UPROPERTY()`
- L76 _public member_ `FText Keywords;` — `UPROPERTY()`
- L79 _public member_ `FText CompactNodeTitle;` — `UPROPERTY()`
- L82 _public member_ `FLinearColor InstanceTitleColor;` — `UPROPERTY()`
- L85 _public member_ `FString DeprecationMessage;` — `UPROPERTY()`
- L88 _public member_ `bool bIsDeprecated;` — `UPROPERTY()`
- L91 _public member_ `bool bCallInEditor;` — `UPROPERTY()`
- L94 _public member_ `bool bThreadSafe;` — `UPROPERTY()`
- L97 _public member_ `bool bIsUnsafeDuringActorConstruction;` — `UPROPERTY()`
- L101 _public member_ `int8 HasLatentFunctions;` — `UPROPERTY(transient)` — Cached value for whether or not the graph has latent functions, positive for TRUE, zero for FALSE, and INDEX_None for undetermined
- L104 _public function_ `FKismetUserDeclaredFunctionMetadata() : InstanceTitleColor(FLinearColor::White) , bIsDeprecated(false) , bCallInEditor(false) , bThreadSafe(false) , bIsUnsafeDuringActorConstruction(false) , HasLatentFunctions(INDEX_NONE)`
- L115 _public prototype_ `void SetMetaData(FName Key, FString&& Value);` — Set a metadata value on the function
- L117 _public prototype_ `void SetMetaData(FName Key, const FStringView Value);` — Set a metadata value on the function
- L119 _public prototype_ `const FString& GetMetaData(FName Key) const;` — Gets a metadata value on the function; asserts if the value isn't present.
- L121 _public prototype_ `void RemoveMetaData(FName Key);` — Clear metadata value on the function
- L123 _public prototype_ `bool HasMetaData(FName Key) const;` — Checks if there is metadata for a key
- L125 _public prototype_ `const TMap<FName, FString>& GetMetaDataMap() const;` — Gets all metadata associated with this function
- L129 _private member_ `TMap<FName, FString> MetaDataMap;` — `UPROPERTY()`

#### class `UK2Node_EditablePinBase`  
`class UK2Node_EditablePinBase : public UK2Node`  
_L133-239_
- reflection: `UCLASS(abstract, MinimalAPI)`
- inherits: `UK2Node`
- L139 _private member_ `uint32 bIsEditable:1;` — `UPROPERTY()` — Whether or not this entry node should be user-editable with the function editor
- L142 _private member_ `TArray< TSharedPtr<FUserPinInfo> >UserDefinedPins;` — Pins defined by the user
- L144 _private function_ `virtual bool IsEditable() const`
- L147 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L148 _private prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L149 _private prototype_ `virtual void ExportCustomProperties(FOutputDevice& Out, uint32 Indent) override;`
- L150 _private prototype_ `virtual void ImportCustomProperties(const TCHAR* SourceText, FFeedbackContext* Warn) override;`
- L154 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L155 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L159 _private function_ `virtual bool ShouldShowNodeProperties() const override` — UK2Node interface
- L169 _private function_ `virtual bool CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage)` — Queries if a user defined pin of the passed type can be constructed on this node. Node will return false by default and must opt into this functionality @param			InPinType			The type info for the pin to create @param			OutErrorMessage		Only filled with an error if there is pin add support but there is an error with the pin type @return			TRUE if a user defined pin can be constructed
- L178 _private prototype_ `UEdGraphPin* CreateUserDefinedPin(const FName InPinName, const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, bool bUseUniqueName = true);` — Creates a UserPinInfo from the specified information, and also adds a pin based on that description to the node @param	InPinName				Name of the pin to create @param	InPinType				The type info for the pin to create @param	InDesiredDirection		Desired direction of the pin, will auto-correct if the direction is not allowed on the pin.
- L185 _private prototype_ `void RemoveUserDefinedPin( TSharedPtr<FUserPinInfo> PinToRemove );` — Removes a pin from the user-defined array, and removes the pin with the same name from the Pins array @param	PinToRemove	Shared pointer to the pin to remove from the UserDefinedPins array.  Corresponding pin in the Pins array will also be removed
- L192 _private prototype_ `void RemoveUserDefinedPinByName(const FName PinName);` — Removes from the user-defined array, and removes the pin with the same name from the Pins array @param	PinName name of pin to remove
- L200 _private prototype_ `bool UserDefinedPinExists(const FName PinName) const;` — Check if a pin with this name exists in the user defined pin set @param	PinName name of pin check existence of @return	True if a user defined pin with this name exists
- L208 _private function_ `virtual UEdGraphPin* CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> NewPinInfo)` — Creates a new pin on the node from the specified user pin info. Must be overridden so each type of node can ensure that the pin is created in the proper direction, etc @param	NewPinInfo		Shared pointer to the struct containing the info for this pin
- L211 _private prototype_ `virtual bool ModifyUserDefinedPinDefaultValue(TSharedPtr<FUserPinInfo> PinInfo, const FString& NewDefaultValue);` — Modifies the default value of an existing pin on the node, this will update both the UserPinInfo and the linked editor pin
- L214 _private prototype_ `virtual bool UpdateUserDefinedPinDefaultValues();` — Copies default value data from the graph pins to the user pins, returns true if any were modified
- L219 _private prototype_ `virtual bool CreateUserDefinedPinsForFunctionEntryExit(const UFunction* Function, bool bForFunctionEntry);` — Creates function pins that are user defined based on a function signature.
- L224 _private function_ `virtual bool CanModifyExecutionWires()` — Can this node have execution wires added or removed?
- L229 _private function_ `virtual bool CanUseRefParams() const` — Can this node have pass-by-reference parameters?
- L234 _private function_ `virtual bool ShouldUseConstRefParams() const` — Should this node require 'const' for pass-by-reference parameters?
- L238 _private prototype_ `bool UpdateEdGraphPinDefaultValue(TSharedPtr<FUserPinInfo> PinInfo, FString& NewDefaultValue);` — Internal function that just updates the UEdGraphPin, separate to avoid recursive update calls

### `Source/Editor/BlueprintGraph/Classes/K2Node_EnumEquality.h` (Public)


#### class `UK2Node_EnumEquality`  
`class UK2Node_EnumEquality : public UK2Node`  
_L27-61_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "=="))`
- inherits: `UK2Node`
- L32 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L33 _private prototype_ `virtual FText GetTooltipText() const override;`
- L34 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L38 _private prototype_ `virtual void PostReconstructNode() override;`
- L39 _private function_ `virtual bool IsNodeSafeToIgnore() const override`
- L40 _private function_ `virtual bool IsNodePure() const override`
- L41 _private function_ `virtual bool ShouldDrawCompact() const override`
- L42 _private function_ `virtual FText GetCompactNodeTitle() const override`
- L43 _private prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L44 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L45 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L46 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L47 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L48 _private function_ `virtual int32 GetNodeRefreshPriority() const override`
- L49 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L53 _private prototype_ `UEdGraphPin* GetReturnValuePin() const;` — Get the return value pin
- L55 _private prototype_ `UEdGraphPin* GetInput1Pin() const;` — Get the first input pin
- L57 _private prototype_ `UEdGraphPin* GetInput2Pin() const;` — Get the second input pin
- L60 _private prototype_ `virtual void GetConditionalFunction(FName& FunctionName, UClass** FunctionClass) const;` — Gets the name and class of the EqualEqual_ByteByte function

### `Source/Editor/BlueprintGraph/Classes/K2Node_EnumInequality.h` (Public)


#### class `UK2Node_EnumInequality`  
`class UK2Node_EnumInequality : public UK2Node_EnumEquality`  
_L20-35_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "!="))`
- inherits: `UK2Node_EnumEquality`
- L25 _private prototype_ `virtual FText GetTooltipText() const override;`
- L26 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L30 _private function_ `virtual FText GetCompactNodeTitle() const override`
- L34 _private prototype_ `virtual void GetConditionalFunction(FName& FunctionName, UClass** FunctionClass) const override;` — Gets the name and class of the EqualEqual_ByteByte function

### `Source/Editor/BlueprintGraph/Classes/K2Node_EnumLiteral.h` (Public)


#### class `UK2Node_EnumLiteral`  
`class UK2Node_EnumLiteral : public UK2Node, public INodeDependingOnEnumInterface`  
_L29-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,INodeDependingOnEnumInterface`
- L34 _private member_ `TObjectPtr<UEnum> Enum;` — `UPROPERTY()`
- L36 _private prototype_ `static const FName GetEnumInputPinName();`
- L39 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L40 _private prototype_ `virtual FText GetTooltipText() const override;`
- L41 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L42 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L43 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L44 _private prototype_ `virtual void AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L48 _private function_ `virtual bool IsNodePure() const override`
- L49 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L50 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L51 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L55 _private function_ `virtual class UEnum* GetEnum() const override` — INodeDependingOnEnumInterface
- L56 _private prototype_ `virtual void ReloadEnum(class UEnum* InEnum) override;`
- L57 _private function_ `virtual bool ShouldBeReconstructedAfterEnumChanged() const override`
- L62 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's tootltip

### `Source/Editor/BlueprintGraph/Classes/K2Node_Event.h` (Public)


#### class `UK2Node_Event`  
`class UK2Node_Event : public UK2Node_EditablePinBase, public IK2Node_EventNodeInterface`  
_L38-144_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_EditablePinBase,IK2Node_EventNodeInterface`
- L41 _private member_ `static const FName DelegateOutputName;`
- L45 _private member_ `FName EventSignatureName_DEPRECATED;` — `UPROPERTY()` — Name of function signature that this event implements
- L49 _private member_ `TSubclassOf<class UObject> EventSignatureClass_DEPRECATED;` — `UPROPERTY()` — Class that the function signature is from.
- L53 _private member_ `FMemberReference EventReference;` — `UPROPERTY()` — Reference for the function this event is linked to
- L57 _private member_ `uint32 bOverrideFunction:1;` — `UPROPERTY()` — If true, we are actually overriding this function, not making a new event with a signature that matches
- L61 _private member_ `uint32 bInternalEvent:1;` — `UPROPERTY()` — If true, this event is internal machinery, and should not be marked BlueprintCallable
- L65 _private member_ `FName CustomFunctionName;` — `UPROPERTY()` — If this is not an override, allow user to specify a name for the function created by this entry point
- L69 _private member_ `uint32 FunctionFlags;` — `UPROPERTY()` — Additional function flags to apply to this function
- L72 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L73 _private prototype_ `virtual void PostLoad() override;`
- L74 _private prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L78 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L79 _private prototype_ `virtual FText GetTooltipText() const override;`
- L80 _private prototype_ `virtual FText GetKeywords() const override;`
- L81 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L82 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L83 _private prototype_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;`
- L84 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L85 _private prototype_ `virtual FName GetCornerIcon() const override;`
- L86 _private prototype_ `virtual bool HasDeprecatedReference() const override;`
- L87 _private prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType DeprecationType) const override;`
- L88 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L89 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L90 _private prototype_ `virtual FString GetFindReferenceSearchString_Impl(EGetFindReferenceSearchStringFlags InFlags) const override;`
- L91 _private prototype_ `virtual void FindDiffs(UEdGraphNode* OtherNode, struct FDiffResults& Results) override;`
- L92 _private prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L93 _private prototype_ `virtual void AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L97 _private function_ `virtual bool DrawNodeAsEntry() const override`
- L98 _private prototype_ `virtual bool NodeCausesStructuralBlueprintChange() const override;`
- L99 _private prototype_ `virtual void GetRedirectPinNames(const UEdGraphPin& Pin, TArray<FString>& RedirectPinNames) const override;`
- L100 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L101 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L102 _private prototype_ `virtual void PostReconstructNode() override;`
- L103 _private prototype_ `virtual FString GetDocumentationLink() const override;`
- L104 _private prototype_ `virtual FString GetDocumentationExcerptName() const override;`
- L105 _private prototype_ `virtual FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override;`
- L106 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L107 _private prototype_ `virtual FText GetToolTipHeading() const override;`
- L108 _private prototype_ `virtual void GetNodeAttributes( TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes ) const override;`
- L109 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L113 _private prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetEventNodeAction(const FText& ActionCategory) override;`
- L117 _private prototype_ `virtual bool IsFunctionEntryCompatible(const class UK2Node_FunctionEntry* EntryNode) const;` — Checks whether the parameters for this event node are compatible with the specified function entry node
- L119 _private prototype_ `bool IsInterfaceEventNode() const;` — Checks if this event node is implementing an interface event
- L121 _private prototype_ `UFunction* FindEventSignatureFunction() const;`
- L122 _private prototype_ `void UpdateDelegatePin(bool bSilent = false);`
- L123 _private prototype_ `FName GetFunctionName() const;`
- L124 _private function_ `virtual bool IsUsedByAuthorityOnlyDelegate() const`
- L125 _private prototype_ `virtual bool IsCosmeticTickEvent() const;`
- L130 _private prototype_ `static FText GetLocalizedNetString(uint32 NetFlags, bool Calling);` — Returns localized string describing replication settings. Calling - whether this function is being called ("sending") or showing implementation ("receiving"). Determined whether we output "Replicated To Server" or "Replicated From Client".
- L133 _private prototype_ `static bool AreEventNodesIdentical(const UK2Node_Event* InNodeA, const UK2Node_Event* InNodeB);` — Helper function to identify if two Event nodes are the same
- L136 _private prototype_ `UEdGraphPin* GetDelegatePin() const;` — Accessor to the delegate pin
- L139 _protected prototype_ `void FixupEventReference(bool bForce = false);`
- L143 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's tooltip

### `Source/Editor/BlueprintGraph/Classes/K2Node_EventNodeInterface.h` (Public)


#### class `UK2Node_EventNodeInterface`  
`class UK2Node_EventNodeInterface : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IK2Node_EventNodeInterface`  
`class IK2Node_EventNodeInterface`  
_L18-24_
- L23 _public prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetEventNodeAction(const FText& ActionCategory) = 0;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_ExecutionSequence.h` (Public)


#### class `UK2Node_ExecutionSequence`  
`class UK2Node_ExecutionSequence : public UK2Node, public IK2Node_AddPinInterface`  
_L27-80_
- reflection: `UCLASS(MinimalAPI, meta = (Keywords = "sequence"))`
- inherits: `UK2Node,IK2Node_AddPinInterface`
- L32 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L33 _private prototype_ `virtual FText GetTooltipText() const override;`
- L34 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L35 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L36 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L40 _private prototype_ `void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L41 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L42 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L43 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L44 _private function_ `virtual bool CanEverInsertExecutionPin() const override`
- L45 _private function_ `virtual bool CanEverRemoveExecutionPin() const override`
- L49 _private prototype_ `virtual void AddInputPin() override;` — IK2Node_AddPinInterface interface
- L55 _private prototype_ `FName GetUniquePinName();` — Gets a unique pin name, the next in the sequence
- L62 _private prototype_ `void InsertPinIntoExecutionNode(UEdGraphPin* PinToInsertBefore, EPinInsertPosition Position);` — Inserts a new execution pin, before the specified execution pin, into an execution node @param	PinToInsertBefore	The pin to insert a new pin before on the node
- L69 _private prototype_ `void RemovePinFromExecutionNode(UEdGraphPin* TargetPin);` — Removes the specified execution pin from an execution node @param	TargetPin	The pin to remove from the node
- L72 _private prototype_ `bool CanRemoveExecutionPin() const;` — Whether an execution pin can be removed from the node or not
- L75 _private prototype_ `UEdGraphPin* GetThenPinGivenIndex(int32 Index);` — @todo document
- L79 _private prototype_ `virtual FName GetPinNameGivenIndex(int32 Index) const;` — Returns the exec output pin name for a given 0-based index

### `Source/Editor/BlueprintGraph/Classes/K2Node_ExternalGraphInterface.h` (Public)


#### class `UK2Node_ExternalGraphInterface`  
`class UK2Node_ExternalGraphInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IK2Node_ExternalGraphInterface`  
`class IK2Node_ExternalGraphInterface`  
_L17-24_
- L23 _public prototype_ `virtual TArray<UEdGraph*> GetExternalGraphs() const = 0;` — Get external graphs to display for this node

### `Source/Editor/BlueprintGraph/Classes/K2Node_ForEachElementInEnum.h` (Public)


#### class `UK2Node_ForEachElementInEnum`  
`class UK2Node_ForEachElementInEnum : public UK2Node, public INodeDependingOnEnumInterface`  
_L26-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,INodeDependingOnEnumInterface`
- L31 _private member_ `TObjectPtr<UEnum> Enum;` — `UPROPERTY()`
- L33 _private member_ `static const FName InsideLoopPinName;`
- L34 _private member_ `static const FName EnumOuputPinName;`
- L35 _private member_ `static const FName SkipHiddenPinName;`
- L38 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L39 _private prototype_ `virtual FText GetTooltipText() const override;`
- L40 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L41 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L45 _private function_ `virtual bool IsNodePure() const override`
- L46 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L47 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L48 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L49 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L50 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L54 _private function_ `virtual class UEnum* GetEnum() const override` — INodeDependingOnEnumInterface
- L55 _private prototype_ `virtual void ReloadEnum(class UEnum* InEnum) override;`
- L56 _private function_ `virtual bool ShouldBeReconstructedAfterEnumChanged() const override`
- L61 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/BlueprintGraph/Classes/K2Node_FormatText.h` (Public)


#### class `UK2Node_FormatText`  
`class UK2Node_FormatText : public UK2Node`  
_L24-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L29 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L33 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L34 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L35 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L36 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L37 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L38 _private prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L39 _private prototype_ `virtual FText GetTooltipText() const override;`
- L40 _private prototype_ `virtual FText GetPinDisplayName(const UEdGraphPin* Pin) const override;`
- L44 _private function_ `virtual bool IsNodePure() const override`
- L45 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L46 _private prototype_ `virtual void PostReconstructNode() override;`
- L47 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L48 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L49 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L50 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L51 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L52 _private function_ `virtual int32 GetNodeRefreshPriority() const override`
- L57 _public prototype_ `void AddArgumentPin();` — Adds a new pin to the node
- L60 _public function_ `int32 GetArgumentCount() const` — Returns the number of arguments currently available in the node
- L68 _public prototype_ `FText GetArgumentName(int32 InIndex) const;` — Returns argument name based on argument index @param InIndex		The argument's index to find the name for @return				Returns the argument's name if available
- L71 _public prototype_ `void RemoveArgument(int32 InIndex);` — Removes the argument at a given index
- L79 _public prototype_ `void SetArgumentName(int32 InIndex, FName InName);` — Sets an argument name @param InIndex		The argument's index to find the name for @param InName		Name to set the argument to
- L82 _public prototype_ `void SwapArguments(int32 InIndexA, int32 InIndexB);` — Swaps two arguments by index
- L85 _public prototype_ `UEdGraphPin* GetFormatPin() const;` — returns Format pin
- L88 _public function_ `bool CanEditArguments() const` — Returns TRUE if the arguments are allowed to be edited
- L96 _public prototype_ `UEdGraphPin* FindArgumentPin(const FName InPinName) const;` — Finds an argument pin by name, checking strings in a strict, case sensitive fashion @param InPinName		The pin name to check for @return				NULL if the pin was not found, otherwise the found pin.
- L100 _private prototype_ `void SynchronizeArgumentPinType(UEdGraphPin* Pin);` — Synchronize the type of the given argument pin with the type its connected to, or reset it to a wildcard pin if there's no connection
- L103 _private prototype_ `FName GetUniquePinName();` — Returns a unique pin name to use for a pin
- L108 _private member_ `TArray<FName> PinNames;` — `UPROPERTY()` — When adding arguments to the node, their names are placed here and are generated as pins during construction
- L111 _private member_ `UEdGraphPin* CachedFormatPin;` — The "Format" input pin, always available on the node
- L114 _private member_ `FText NodeTooltip;` — Tooltip text for this node.

### `Source/Editor/BlueprintGraph/Classes/K2Node_FunctionEntry.h` (Public)


#### class `UK2Node_FunctionEntry`  
`class UK2Node_FunctionEntry : public UK2Node_FunctionTerminator`  
_L36-169_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_FunctionTerminator`
- L42 _private member_ `FName CustomGeneratedFunctionName;` — `UPROPERTY()` — If specified, the function that is created for this entry point will have this name.  Otherwise, it will have the function signature's name
- L46 _private member_ `struct FKismetUserDeclaredFunctionMetadata MetaData;` — `UPROPERTY()` — Function metadata
- L50 _private member_ `TArray<FBPVariableDescription> LocalVariables;` — `UPROPERTY()` — Array of local variables to be added to generated function
- L54 _private member_ `bool bEnforceConstCorrectness;` — `UPROPERTY()` — Whether or not to enforce const-correctness for const function overrides
- L57 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L58 _private prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L59 _private prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L60 _private prototype_ `virtual void PostLoad() override;`
- L64 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L65 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L66 _private prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L67 _private prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L68 _private prototype_ `virtual bool GetCanRenameNode() const override;`
- L69 _private function_ `virtual bool CanUserDeleteNode() const override`
- L70 _private prototype_ `virtual bool HasDeprecatedReference() const override;`
- L71 _private prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType DeprecationType) const override;`
- L72 _private prototype_ `virtual FText GetTooltipText() const override;`
- L73 _private prototype_ `virtual void FindDiffs(UEdGraphNode* OtherNode, struct FDiffResults& Results) override;`
- L74 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* InGraph) const override;`
- L75 _private prototype_ `virtual void PostPasteNode() override;`
- L76 _private prototype_ `virtual void AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L80 _private function_ `virtual bool DrawNodeAsEntry() const override`
- L81 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L82 _private prototype_ `virtual void GetRedirectPinNames(const UEdGraphPin& Pin, TArray<FString>& RedirectPinNames) const override;`
- L83 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L84 _private prototype_ `virtual void PostReconstructNode() override;`
- L85 _private prototype_ `virtual void ClearCachedBlueprintData(UBlueprint* Blueprint) override;`
- L86 _private prototype_ `virtual void FixupPinStringDataReferences(FArchive* SavingArchive) override;`
- L87 _private prototype_ `virtual ERenamePinResult RenameUserDefinedPinImpl(FName OldName, FName NewName, bool bTest) override;`
- L91 _private function_ `virtual bool CanUseRefParams() const override`
- L92 _private prototype_ `virtual bool ShouldUseConstRefParams() const override;`
- L93 _private prototype_ `virtual bool ModifyUserDefinedPinDefaultValue(TSharedPtr<FUserPinInfo> PinInfo, const FString& NewDefaultValue) override;`
- L97 _private prototype_ `virtual bool CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage) override;`
- L98 _private prototype_ `virtual UEdGraphPin* CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> NewPinInfo) override;`
- L102 _private prototype_ `TSharedPtr<FStructOnScope> GetFunctionVariableCache(bool bForceRefresh = false);` — Gets the UFunction and function variable cache structure that should be used for serialization fixups for local variables. If bForceRefresh is true it will always recreate the cache
- L105 _private prototype_ `bool RefreshFunctionVariableCache();` — Copies data from the local variable defaults into the variable cache
- L108 _private prototype_ `bool UpdateLoadedDefaultValues(bool bForceRefresh = false);` — Handles updating loaded default values, by going default string into variable cache and back, if bForceRefresh it will happen even if the cache is already setup
- L111 _private prototype_ `void RemoveOutputPin(UEdGraphPin* PinToRemove);` — Removes an output pin from the node
- L114 _private prototype_ `UEdGraphPin* GetAutoWorldContextPin() const;` — Returns pin for the automatically added WorldContext parameter (used only by BlueprintFunctionLibrary).
- L117 _private prototype_ `int32 GetFunctionFlags() const;` — Retrieves the function flags from the UFunction that this function entry node represents
- L120 _private function_ `int32 GetExtraFlags() const` — Retrieves the extra flags set on this node.
- L126 _private function_ `void SetExtraFlags(int32 InFlags)` — Set the extra flags on this node
- L131 _private function_ `void AddExtraFlags(int32 InFlags)`
- L136 _private function_ `void ClearExtraFlags(int32 InFlags)`
- L142 _private function_ `bool HasAnyExtraFlags(int32 FlagsToCheck) const` — Used to safely check whether the passed in flag is set.
- L148 _private function_ `bool HasAllExtraFlags(int32 FlagsToCheck) const` — Used to safely check whether all of the passed in flags are set.
- L155 _protected prototype_ `bool UpdateVariableStructFromDefaults(const UStruct* VariableStruct, uint8* VariableStructData);` — Copies data from any local variables matching properties in VariableStruct into the VariableStructData
- L158 _protected prototype_ `bool UpdateDefaultsFromVariableStruct(const UStruct* VariableStruct, uint8* VariableStructData);` — Copies data from VariableStruct into the local variables
- L162 _protected member_ `int32 ExtraFlags;` — `UPROPERTY()` — Any extra flags that the function may need
- L165 _protected member_ `TSharedPtr<FStructOnScope> FunctionVariableCache;` — Holds a an in-memory representation of the UFunction struct, used to fixup local and user variables
- L168 _protected member_ `bool bUpdatedDefaultValuesOnLoad;` — True if we've updated the default values on this node at least once

### `Source/Editor/BlueprintGraph/Classes/K2Node_FunctionResult.h` (Public)


#### class `UK2Node_FunctionResult`  
`class UK2Node_FunctionResult : public UK2Node_FunctionTerminator`  
_L28-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_FunctionTerminator`
- L33 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L34 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L35 _private prototype_ `virtual FText GetTooltipText() const override;`
- L36 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L40 _private function_ `virtual bool DrawNodeAsExit() const override`
- L41 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L42 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L43 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L44 _private prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const;`
- L45 _private prototype_ `virtual void PostPlacedNewNode();`
- L46 _private prototype_ `virtual void PostPasteNode() override;`
- L47 _private prototype_ `virtual bool CanUserDeleteNode() const override;`
- L48 _private prototype_ `virtual void FixupPinStringDataReferences(FArchive* SavingArchive) override;`
- L49 _private prototype_ `virtual ERenamePinResult RenameUserDefinedPinImpl(FName OldName, FName NewName, bool bTest) override;`
- L53 _private prototype_ `virtual bool CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage) override;`
- L54 _private prototype_ `virtual UEdGraphPin* CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> NewPinInfo) override;`
- L58 _private prototype_ `virtual void PromoteFromInterfaceOverride(bool bIsPrimaryTerminator = true);`
- L61 _private prototype_ `TArray<UK2Node_FunctionResult*> GetAllResultNodes() const;`
- L64 _protected prototype_ `void SyncWithEntryNode();`
- L65 _protected prototype_ `void SyncWithPrimaryResultNode();`
- L66 _protected prototype_ `void MakePinsEditable();`

### `Source/Editor/BlueprintGraph/Classes/K2Node_FunctionTerminator.h` (Public)


#### class `UK2Node_FunctionTerminator`  
`class UK2Node_FunctionTerminator : public UK2Node_EditablePinBase`  
_L26-69_
- reflection: `UCLASS(abstract, MinimalAPI)`
- inherits: `UK2Node_EditablePinBase`
- L32 _private member_ `FMemberReference FunctionReference;` — `UPROPERTY()` — Reference to the function signature. This is only resolvable by default if this is an inherited function
- L35 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L39 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L40 _private prototype_ `virtual FString GetFindReferenceSearchString_Impl(EGetFindReferenceSearchStringFlags InFlags) const override;`
- L41 _private prototype_ `virtual FName CreateUniquePinName(FName SourcePinName) const override;`
- L42 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L43 _private prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L47 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L48 _private prototype_ `virtual void PostPasteNode() override;`
- L52 _private prototype_ `virtual bool CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage) override;`
- L56 _private prototype_ `virtual void PromoteFromInterfaceOverride(bool bIsPrimaryTerminator = true);` — Promotes the node from being a part of an interface override to a full function that allows for parameter and result pin additions
- L59 _private prototype_ `UFunction* FindSignatureFunction() const;` — Returns the UFunction that this node actually represents, this will work for both inherited and newly created functions
- L64 _private member_ `TSubclassOf<class UObject> SignatureClass_DEPRECATED;` — `UPROPERTY()` — (DEPRECATED) Function signature class. Replaced by the 'FunctionReference' property.
- L68 _private member_ `FName SignatureName_DEPRECATED;` — `UPROPERTY()` — (DEPRECATED) Function signature name. Replaced by the 'FunctionReference' property.

### `Source/Editor/BlueprintGraph/Classes/K2Node_GeneratedBoundEvent.h` (Public)


#### class `UK2Node_GeneratedBoundEvent`  
`class UK2Node_GeneratedBoundEvent : public UK2Node_Event`  
_L34-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Event`
- desc: Node used during generation of ubergraph pages. This node should never be used at editor time, so various editor related features are not implemented
- L42 _public member_ `FName DelegatePropertyName;` — `UPROPERTY()` — Delegate property name that this event is associated with
- L46 _public member_ `TObjectPtr<UClass> DelegateOwnerClass;` — `UPROPERTY()` — Delegate property's owner class that this event is associated with
- L49 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L50 _public prototype_ `virtual void ReconstructNode() override;`
- L54 _public function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L55 _public prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L56 _public prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`
- L57 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L61 _public prototype_ `virtual bool IsUsedByAuthorityOnlyDelegate() const override;`
- L65 _public prototype_ `FMulticastDelegateProperty* GetTargetDelegateProperty() const;` — Return the delegate property that this event is bound to
- L68 _public prototype_ `FText GetTargetDelegateDisplayName() const;` — Gets the proper display name for the property
- L71 _public prototype_ `void InitializeGeneratedBoundEventParams(const FMulticastDelegateProperty* InDelegateProperty);` — Initialize this node with the provided delegate
- L76 _private prototype_ `bool IsDelegateValid() const;` — Returns true if there is a delegate on this blueprint with a name that matches ComponentPropertyName

### `Source/Editor/BlueprintGraph/Classes/K2Node_GenericCreateObject.h` (Public)


#### class `UK2Node_GenericCreateObject`  
`class UK2Node_GenericCreateObject : public UK2Node_ConstructObjectFromClass`  
_L20-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_ConstructObjectFromClass`
- L25 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L26 _private prototype_ `virtual void EarlyValidation(class FCompilerResultsLog& MessageLog) const override;`
- L27 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L30 _private function_ `virtual bool UseWorldContext() const override`
- L31 _private function_ `virtual bool UseOuter() const override`
- L42 _private prototype_ `bool ExpandDefaultToSelfPin(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UK2Node_CallFunction* CallCreateNode);` — attaches a self node to the self pin of 'this' if the CallCreateNode function has DefaultToSelf in it's metadata @param	CompilerContext		the context to expand in - likely passed from ExpandNode @param	SourceGraph			the graph to expand in - likely passed from ExpandNode @param	CallCreateNode		the CallFunction node that 'this' is imitating @return	true on success.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_GenericToText.h` (Public)


#### class `UK2Node_GenericToText`  
`class UK2Node_GenericToText : public UK2Node`  
_L12-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L17 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L18 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L19 _private prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L20 _private prototype_ `virtual void NodeConnectionListChanged() override;`
- L21 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L22 _private prototype_ `virtual void PostReconstructNode() override;`
- L23 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L24 _private function_ `virtual bool IsNodePure() const override`
- L28 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L33 _private prototype_ `virtual FText GetTooltipText() const override;`
- L34 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L35 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L36 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L41 _private prototype_ `void SynchronizeArgumentPinType();` — Synchronize the type of the given argument pin with the type its connected to, or reset it to a wildcard pin if there's no connection

### `Source/Editor/BlueprintGraph/Classes/K2Node_GetArrayItem.h` (Public)


#### class `UK2Node_GetArrayItem`  
`class UK2Node_GetArrayItem : public UK2Node`  
_L32-84_
- reflection: `UCLASS(MinimalAPI, Category = "Utilities|Array", meta=(Keywords = "array"))`
- inherits: `UK2Node`
- L38 _public function_ `virtual bool IsNodePure() const override` — UEdGraphNode interface
- L39 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L40 _public prototype_ `virtual void PostReconstructNode() override;`
- L41 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L42 _public prototype_ `virtual FText GetTooltipText() const override;`
- L43 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L44 _public prototype_ `virtual TSharedPtr<SWidget> CreateNodeImage() const override;`
- L45 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L46 _public function_ `virtual bool IncludeParentNodeContextMenu() const override`
- L47 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L51 _public function_ `virtual bool ShouldDrawCompact() const` — UK2Node interface
- L52 _public prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L53 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L54 _public prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L55 _public function_ `virtual int32 GetNodeRefreshPriority() const override`
- L56 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L57 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L58 _public prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L59 _public prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L63 _public function_ `UEdGraphPin* GetTargetArrayPin() const` — Helper function to return the array pin
- L66 _public function_ `UEdGraphPin* GetIndexPin() const` — Helper function to return the index pin
- L69 _public function_ `UEdGraphPin* GetResultPin() const` — Helper function to return the result pin
- L72 _public prototype_ `void SetDesiredReturnType(bool bAsReference);` — Sets weather we want the array item returned as a reference or by value (as a copy)
- L76 _private prototype_ `void ToggleReturnPin();` — Flips the node's desired 'ReturnByRef' setting & refreshes the node if necessary
- L78 _private prototype_ `void PropagatePinType(FEdGraphPinType& InType);` — Propagates pin type to the Array pin and the Result pin
- L80 _private prototype_ `bool IsSetToReturnRef() const;` — Determines if this node wants to return by ref, and if it is able to do so
- L83 _private member_ `bool bReturnByRefDesired;` — `UPROPERTY()`

### `Source/Editor/BlueprintGraph/Classes/K2Node_GetClassDefaults.h` (Public)


#### class `UK2Node_GetClassDefaults`  
`class UK2Node_GetClassDefaults : public UK2Node`  
_L28-125_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L33 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L34 _private prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L35 _private prototype_ `virtual void PostLoad() override;`
- L39 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L40 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L41 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L42 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L43 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L44 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L45 _private prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L49 _private function_ `virtual bool IsNodePure() const override`
- L50 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L51 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L52 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L53 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L54 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L55 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L60 _public function_ `UEdGraphPin* FindClassPin() const` — Finds and returns the class input pin from the current set of pins.
- L66 _public function_ `UClass* GetInputClass() const` — Retrieves the current input class type.
- L71 _public prototype_ `void OnBlueprintClassModified(UBlueprint* TargetBlueprint);`
- L79 _protected prototype_ `UEdGraphPin* FindClassPin(const TArray<UEdGraphPin*>& FromPins) const;` — Finds and returns the class input pin. @param FromPins	A list of pins to search.
- L86 _protected prototype_ `UClass* GetInputClass(const UEdGraphPin* FromPin) const;` — Determines the input class type from the given pin. @param FromPin	Input class pin.
- L93 _protected prototype_ `void CreateOutputPins(UClass* InClass);` — Creates the full set of output pins (properties) from the given input class. @param InClass	Input class type.
- L96 _protected prototype_ `void OnClassPinChanged();` — Will be called whenever the class pin selector changes its value.
- L100 _private member_ `static FName ClassPinName;` — Class pin name
- L104 _private member_ `TObjectPtr<UBlueprint> BlueprintSubscribedTo;` — `UPROPERTY(Transient)` — Blueprint that we subscribed OnBlueprintChangedDelegate and OnBlueprintCompiledDelegate to
- L107 _private member_ `FDelegateHandle OnBlueprintChangedDelegate;` — Blueprint.OnChanged delegate handle
- L110 _private member_ `FDelegateHandle OnBlueprintCompiledDelegate;` — Blueprint.OnCompiled delegate handle
- L114 _private member_ `TArray<FOptionalPinFromProperty> ShowPinForProperties;` — `UPROPERTY(EditAnywhere, Category=PinOptions, EditFixedSize)` — Output pin visibility control
- L116 _private member_ `TArray<FName> OldShownPins;`
- L120 _private member_ `bool bExcludeObjectContainers;` — `UPROPERTY()` — Whether or not to exclude object container properties
- L124 _private member_ `bool bExcludeObjectArrays_DEPRECATED;` — `UPROPERTY()` — Whether or not to exclude object array properties (deprecated)

### `Source/Editor/BlueprintGraph/Classes/K2Node_GetDataTableRow.h` (Public)


#### class `UK2Node_GetDataTableRow`  
`class UK2Node_GetDataTableRow : public UK2Node`  
_L31-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L36 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L37 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L38 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L39 _private prototype_ `virtual FText GetTooltipText() const override;`
- L40 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L41 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L42 _private prototype_ `virtual void PostReconstructNode() override;`
- L46 _private function_ `virtual bool IsNodeSafeToIgnore() const override`
- L47 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L48 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L49 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L50 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L51 _private prototype_ `virtual void EarlyValidation(class FCompilerResultsLog& MessageLog) const override;`
- L52 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L53 _private prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L57 _private prototype_ `UScriptStruct* GetReturnTypeForStruct();` — Get the return type of our struct
- L60 _private prototype_ `UEdGraphPin* GetDataTablePin(const TArray<UEdGraphPin*>* InPinsToSearch=NULL) const;` — Get the Data Table input pin
- L62 _private prototype_ `UEdGraphPin* GetRowNamePin() const;` — Get the spawn transform input pin
- L64 _private prototype_ `UEdGraphPin* GetRowNotFoundPin() const;` — Get the exec output pin for when the row was not found
- L66 _private prototype_ `UEdGraphPin* GetResultPin() const;` — Get the result output pin
- L69 _private prototype_ `UScriptStruct* GetDataTableRowStructType() const;` — Get the type of the TableRow to return
- L71 _private prototype_ `void OnDataTableRowListChanged(const UDataTable* DataTable);`
- L80 _private prototype_ `void SetPinToolTip(UEdGraphPin& MutatablePin, const FText& PinDescription) const;` — Takes the specified "MutatablePin" and sets its 'PinToolTip' field (according to the specified description) @param   MutatablePin	The pin you want to set tool-tip text on @param   PinDescription	A string describing the pin's purpose
- L83 _private prototype_ `void SetReturnTypeForStruct(UScriptStruct* InClass);` — Set the return type of our struct
- L85 _private prototype_ `void RefreshOutputPinType();` — Queries for the authoritative return type, then modifies the return pin to match
- L87 _private prototype_ `void RefreshRowNameOptions();` — Triggers a refresh which will update the node's widget; aimed at updating the dropdown menu for the RowName input
- L90 _private member_ `FText NodeTooltip;` — Tooltip text for this node.
- L93 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_GetEnumeratorName.h` (Public)


#### class `UK2Node_GetEnumeratorName`  
`class UK2Node_GetEnumeratorName : public UK2Node`  
_L25-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L32 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L33 _public prototype_ `virtual FText GetTooltipText() const override;`
- L34 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L35 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L36 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L40 _public prototype_ `virtual FText GetCompactNodeTitle() const override;`
- L41 _public function_ `virtual bool ShouldDrawCompact() const override`
- L42 _public function_ `virtual bool IsNodePure() const override`
- L43 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L44 _public prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L45 _public prototype_ `virtual void EarlyValidation(class FCompilerResultsLog& MessageLog) const override;`
- L46 _public prototype_ `virtual void PostReconstructNode() override;`
- L47 _public prototype_ `virtual void NodeConnectionListChanged() override;`
- L48 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L49 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L50 _public function_ `virtual int32 GetNodeRefreshPriority() const override`
- L55 _protected member_ `static FName EnumeratorPinName;`
- L59 _private prototype_ `UEnum* GetConnectedEnum() const;`
- L60 _private prototype_ `virtual FName GetFunctionName() const;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_GetEnumeratorNameAsString.h` (Public)


#### class `UK2Node_GetEnumeratorNameAsString`  
`class UK2Node_GetEnumeratorNameAsString : public UK2Node_GetEnumeratorName`  
_L21-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_GetEnumeratorName`
- L28 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L29 _public prototype_ `virtual FText GetTooltipText() const override;`
- L30 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L31 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L35 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L36 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L37 _public function_ `virtual bool ShouldDrawCompact() const override`
- L42 _private prototype_ `virtual FName GetFunctionName() const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_GetInputAxisKeyValue.h` (Public)


#### class `UK2Node_GetInputAxisKeyValue`  
`class UK2Node_GetInputAxisKeyValue : public UK2Node_CallFunction`  
_L28-67_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Get"))`
- inherits: `UK2Node_CallFunction`
- L33 _private member_ `FKey InputAxisKey;` — `UPROPERTY()`
- L37 _private member_ `uint32 bConsumeInput:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Prevents actors with lower priority from handling this input
- L41 _private member_ `uint32 bExecuteWhenPaused:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Should the binding gather input even when the game is paused
- L44 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L45 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L46 _private prototype_ `virtual FText GetTooltipText() const override;`
- L47 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L48 _private prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;`
- L52 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L53 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L54 _private prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L55 _private prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`
- L56 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L57 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L58 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L61 _private prototype_ `void Initialize(const FKey AxisKey);`
- L65 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L66 _private member_ `FNodeTextCache CachedNodeTitle;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_GetInputAxisValue.h` (Public)


#### class `UK2Node_GetInputAxisValue`  
`class UK2Node_GetInputAxisValue : public UK2Node_CallFunction`  
_L26-64_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Get"))`
- inherits: `UK2Node_CallFunction`
- L31 _private member_ `FName InputAxisName;` — `UPROPERTY()`
- L35 _private member_ `uint32 bConsumeInput:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Prevents actors with lower priority from handling this input
- L39 _private member_ `uint32 bExecuteWhenPaused:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Should the binding gather input even when the game is paused
- L42 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L43 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L44 _private prototype_ `virtual FText GetTooltipText() const override;`
- L45 _private prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;`
- L49 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L50 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L51 _private prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L52 _private prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`
- L53 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L54 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L55 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L58 _private prototype_ `void Initialize(const FName AxisName);`
- L62 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L63 _private member_ `FNodeTextCache CachedNodeTitle;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_GetInputVectorAxisValue.h` (Public)


#### class `UK2Node_GetInputVectorAxisValue`  
`class UK2Node_GetInputVectorAxisValue : public UK2Node_GetInputAxisKeyValue`  
_L20-37_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Get"))`
- inherits: `UK2Node_GetInputAxisKeyValue`
- L25 _private prototype_ `virtual FText GetTooltipText() const override;`
- L29 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L30 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L31 _private prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L32 _private prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`
- L33 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L36 _private prototype_ `void Initialize(const FKey AxisKey);`

### `Source/Editor/BlueprintGraph/Classes/K2Node_GetNumEnumEntries.h` (Public)


#### class `UK2Node_GetNumEnumEntries`  
`class UK2Node_GetNumEnumEntries : public UK2Node, public INodeDependingOnEnumInterface`  
_L25-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,INodeDependingOnEnumInterface`
- L30 _private member_ `TObjectPtr<UEnum> Enum;` — `UPROPERTY()`
- L33 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L34 _private prototype_ `virtual FText GetTooltipText() const override;`
- L35 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L36 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L40 _private function_ `virtual bool IsNodePure() const override`
- L41 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L42 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L43 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L47 _private function_ `virtual class UEnum* GetEnum() const override` — INodeDependingOnEnumInterface
- L48 _private prototype_ `virtual void ReloadEnum(class UEnum* InEnum) override;`
- L49 _private function_ `virtual bool ShouldBeReconstructedAfterEnumChanged() const override`
- L54 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L55 _private member_ `FNodeTextCache CachedNodeTitle;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_GetSubsystem.h` (Public)


#### class `UK2Node_GetSubsystem`  
`class UK2Node_GetSubsystem : public UK2Node`  
_L33-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L38 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L40 _public prototype_ `void Initialize(UClass* NodeClass);`
- L42 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L43 _public prototype_ `virtual FString GetPinMetaData(FName InPinName, FName InKey) override;`
- L44 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L45 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L46 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L47 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L48 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L49 _public prototype_ `virtual bool CanJumpToDefinition() const override;`
- L50 _public prototype_ `virtual void JumpToDefinition() const override;`
- L51 _public prototype_ `virtual FText GetTooltipText() const override;`
- L54 _public function_ `virtual bool IsNodePure() const`
- L55 _public function_ `virtual bool IsNodeSafeToIgnore() const override`
- L56 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L57 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L58 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L59 _public prototype_ `virtual void GetNodeAttributes(TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes) const override;`
- L60 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L63 _public prototype_ `UEdGraphPin* GetClassPin(const TArray< UEdGraphPin* >* InPinsToSearch = nullptr) const;` — Get the blueprint input pin
- L65 _public prototype_ `UEdGraphPin* GetWorldContextPin() const;` — Get the world context input pin, can return NULL
- L67 _public prototype_ `UEdGraphPin* GetResultPin() const;` — Get the result output pin
- L69 _public function_ `virtual bool ShouldDrawCompact() const override`
- L73 _protected member_ `TSubclassOf<USubsystem> CustomClass;` — `UPROPERTY()`

#### class `UK2Node_GetSubsystemFromPC`  
`class UK2Node_GetSubsystemFromPC : public UK2Node_GetSubsystem`  
_L77-94_
- reflection: `UCLASS()`
- inherits: `UK2Node_GetSubsystem`
- L83 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L84 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L85 _public prototype_ `virtual FText GetTooltipText() const override;`
- L88 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L89 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L92 _public prototype_ `UEdGraphPin* GetPlayerControllerPin() const;` — Get the world context input pin, can return NULL

#### class `UK2Node_GetEngineSubsystem`  
`class UK2Node_GetEngineSubsystem : public UK2Node_GetSubsystem`  
_L97-111_
- reflection: `UCLASS()`
- inherits: `UK2Node_GetSubsystem`
- L103 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L104 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L105 _public prototype_ `virtual FText GetTooltipText() const override;`
- L108 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L109 _public prototype_ `virtual FText GetMenuCategory() const override;`

#### class `UK2Node_GetEditorSubsystem`  
`class UK2Node_GetEditorSubsystem : public UK2Node_GetSubsystem`  
_L114-131_
- reflection: `UCLASS()`
- inherits: `UK2Node_GetSubsystem`
- L120 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L121 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L122 _public prototype_ `virtual FText GetTooltipText() const override;`
- L123 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L126 _public prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L128 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L129 _public prototype_ `virtual FText GetMenuCategory() const override;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_IfThenElse.h` (Public)


#### class `UK2Node_IfThenElse`  
`class UK2Node_IfThenElse : public UK2Node`  
_L23-45_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "if bool branch"))`
- inherits: `UK2Node`
- L28 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L29 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L30 _private prototype_ `virtual FText GetTooltipText() const override;`
- L31 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L32 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L36 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L37 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L38 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L42 _private prototype_ `UEdGraphPin* GetElsePin() const;` — Get the return value pin
- L44 _private prototype_ `UEdGraphPin* GetConditionPin() const;` — Get the condition pin

### `Source/Editor/BlueprintGraph/Classes/K2Node_InputAction.h` (Public)


#### class `UK2Node_InputAction`  
`class UK2Node_InputAction : public UK2Node, public IK2Node_EventNodeInterface`  
_L34-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,IK2Node_EventNodeInterface`
- L39 _private member_ `FName InputActionName;` — `UPROPERTY()`
- L43 _private member_ `uint32 bConsumeInput:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Prevents actors with lower priority from handling this input
- L47 _private member_ `uint32 bExecuteWhenPaused:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Should the binding execute even when the game is paused
- L51 _private member_ `uint32 bOverrideParentBinding:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Should any bindings to this event in parent classes be removed
- L54 _private prototype_ `virtual void PostLoad() override;`
- L58 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L59 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L60 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L61 _private prototype_ `virtual FText GetTooltipText() const override;`
- L62 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L63 _private prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;`
- L64 _private prototype_ `virtual bool IsDeprecated() const override;`
- L65 _private prototype_ `virtual bool HasDeprecatedReference() const override;`
- L66 _private prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType DeprecationType) const override;`
- L70 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L71 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L72 _private prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L73 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L74 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L75 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L79 _private prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetEventNodeAction(const FText& ActionCategory) override;`
- L83 _private prototype_ `UEdGraphPin* GetPressedPin() const;` — Get the 'pressed' input pin
- L86 _private prototype_ `UEdGraphPin* GetReleasedPin() const;` — Get the 'released' input pin
- L90 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L91 _private member_ `FNodeTextCache CachedNodeTitle;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_InputActionEvent.h` (Public)


#### class `UK2Node_InputActionEvent`  
`class UK2Node_InputActionEvent : public UK2Node_Event`  
_L24-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Event`
- L29 _private member_ `FName InputActionName;` — `UPROPERTY()`
- L32 _private member_ `TEnumAsByte<EInputEvent> InputKeyEvent;` — `UPROPERTY()`
- L35 _private member_ `uint32 bConsumeInput:1;` — `UPROPERTY()`
- L38 _private member_ `uint32 bExecuteWhenPaused:1;` — `UPROPERTY()`
- L41 _private member_ `uint32 bOverrideParentBinding:1;` — `UPROPERTY()`
- L44 _private prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L45 _private prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_InputAxisEvent.h` (Public)


#### class `UK2Node_InputAxisEvent`  
`class UK2Node_InputAxisEvent : public UK2Node_Event`  
_L28-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Event`
- L33 _private member_ `FName InputAxisName;` — `UPROPERTY()`
- L37 _private member_ `uint32 bConsumeInput:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Prevents actors with lower priority from handling this input
- L41 _private member_ `uint32 bExecuteWhenPaused:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Should the binding execute even when the game is paused
- L45 _private member_ `uint32 bOverrideParentBinding:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Should any bindings to this event in parent classes be removed
- L48 _private prototype_ `virtual void PostLoad() override;`
- L49 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L53 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L54 _private prototype_ `virtual FText GetTooltipText() const override;`
- L55 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L56 _private prototype_ `virtual bool IsDeprecated() const override;`
- L57 _private prototype_ `virtual bool HasDeprecatedReference() const override;`
- L58 _private prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType DeprecationType) const override;`
- L62 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L63 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L64 _private prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L65 _private prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`
- L66 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L67 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L68 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L69 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L72 _private prototype_ `void Initialize(const FName AxisName);`
- L76 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L77 _private member_ `FNodeTextCache CachedNodeTitle;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_InputAxisKeyEvent.h` (Public)


#### class `UK2Node_InputAxisKeyEvent`  
`class UK2Node_InputAxisKeyEvent : public UK2Node_Event`  
_L30-76_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Event`
- L35 _private member_ `FKey AxisKey;` — `UPROPERTY()`
- L39 _private member_ `uint32 bConsumeInput : 1;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Prevents actors with lower priority from handling this input
- L43 _private member_ `uint32 bExecuteWhenPaused : 1;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Should the binding execute even when the game is paused
- L47 _private member_ `uint32 bOverrideParentBinding : 1;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Should any bindings to this event in parent classes be removed
- L50 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L54 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L55 _private prototype_ `virtual FText GetTooltipText() const override;`
- L56 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L57 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L61 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L62 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L63 _private prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L64 _private prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`
- L65 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L66 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L67 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L68 _private prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L71 _private prototype_ `void Initialize(const FKey AxisKey);`
- L75 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's tooltip

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_InputKey.h` (Public)


#### class `UK2Node_InputKey`  
`class UK2Node_InputKey : public UK2Node, public IK2Node_EventNodeInterface`  
_L35-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,IK2Node_EventNodeInterface`
- L41 _private member_ `FKey InputKey;` — `UPROPERTY(EditAnywhere, Category="Input")` — The key that is bound
- L45 _private member_ `uint32 bConsumeInput:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Prevents actors with lower priority from handling this input
- L49 _private member_ `uint32 bExecuteWhenPaused:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Should the binding execute even when the game is paused
- L53 _private member_ `uint32 bOverrideParentBinding:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Should any bindings to this event in parent classes be removed
- L57 _private member_ `uint32 bControl:1;` — `UPROPERTY(EditAnywhere, Category="Modifier")` — Does this binding require the control key on PC or the command key on Mac to be held
- L61 _private member_ `uint32 bAlt:1;` — `UPROPERTY(EditAnywhere, Category="Modifier")` — Does this binding require the alt key to be held
- L65 _private member_ `uint32 bShift:1;` — `UPROPERTY(EditAnywhere, Category="Modifier")` — Does this binding require the shift key to be held
- L69 _private member_ `uint32 bCommand:1;` — `UPROPERTY(EditAnywhere, Category="Modifier")` — Does this binding require the windows key on PC or the control key on Mac to be held
- L72 _private prototype_ `virtual void PostLoad() override;`
- L73 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L77 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L78 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L79 _private prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L80 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L81 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L82 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L86 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L87 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L88 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L89 _private prototype_ `virtual FText GetTooltipText() const override;`
- L90 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L91 _private prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;`
- L95 _private prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetEventNodeAction(const FText& ActionCategory) override;`
- L99 _private prototype_ `FText GetModifierText() const;`
- L101 _private prototype_ `FName GetModifierName() const;`
- L103 _private prototype_ `FText GetKeyText() const;`
- L106 _private prototype_ `UEdGraphPin* GetPressedPin() const;` — Get the 'pressed' input pin
- L109 _private prototype_ `UEdGraphPin* GetReleasedPin() const;` — Get the 'released' input pin
- L113 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L114 _private member_ `FNodeTextCache CachedNodeTitle;`

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_InputKeyEvent.h` (Public)


#### class `UK2Node_InputKeyEvent`  
`class UK2Node_InputKeyEvent : public UK2Node_Event`  
_L24-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Event`
- L29 _private member_ `FInputChord InputChord;` — `UPROPERTY()`
- L32 _private member_ `TEnumAsByte<EInputEvent> InputKeyEvent;` — `UPROPERTY()`
- L35 _private member_ `uint32 bConsumeInput:1;` — `UPROPERTY()`
- L38 _private member_ `uint32 bExecuteWhenPaused:1;` — `UPROPERTY()`
- L41 _private member_ `uint32 bOverrideParentBinding:1;` — `UPROPERTY()`
- L44 _private prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L45 _private prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_InputTouch.h` (Public)


#### class `UK2Node_InputTouch`  
`class UK2Node_InputTouch : public UK2Node, public IK2Node_EventNodeInterface`  
_L29-83_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,IK2Node_EventNodeInterface`
- L35 _private member_ `uint32 bConsumeInput:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Prevents actors with lower priority from handling this input
- L39 _private member_ `uint32 bExecuteWhenPaused:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Should the binding execute even when the game is paused
- L43 _private member_ `uint32 bOverrideParentBinding:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Should any bindings to this event in parent classes be removed
- L46 _private prototype_ `virtual void PostLoad() override;`
- L50 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L51 _private prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L55 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L56 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L57 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L58 _private prototype_ `virtual FText GetTooltipText() const override;`
- L59 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L60 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L61 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L62 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L66 _private prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetEventNodeAction(const FText& ActionCategory) override;`
- L69 _private prototype_ `static UEnum* GetTouchIndexEnum();`
- L72 _private prototype_ `UEdGraphPin* GetPressedPin() const;` — Get the 'pressed' input pin
- L75 _private prototype_ `UEdGraphPin* GetReleasedPin() const;` — Get the 'released' input pin
- L78 _private prototype_ `UEdGraphPin* GetMovedPin() const;` — Get the 'moved' input pin
- L80 _private prototype_ `UEdGraphPin* GetLocationPin() const;`
- L81 _private prototype_ `UEdGraphPin* GetFingerIndexPin() const;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_InputTouchEvent.h` (Public)


#### class `UK2Node_InputTouchEvent`  
`class UK2Node_InputTouchEvent : public UK2Node_Event`  
_L21-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Event`
- L26 _private member_ `TEnumAsByte<EInputEvent> InputKeyEvent;` — `UPROPERTY()`
- L29 _private member_ `uint8 bConsumeInput:1;` — `UPROPERTY()`
- L32 _private member_ `uint8 bExecuteWhenPaused:1;` — `UPROPERTY()`
- L35 _private member_ `uint8 bOverrideParentBinding:1;` — `UPROPERTY()`
- L38 _private prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L39 _private prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_InputVectorAxisEvent.h` (Public)


#### class `UK2Node_InputVectorAxisEvent`  
`class UK2Node_InputVectorAxisEvent : public UK2Node_InputAxisKeyEvent`  
_L19-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_InputAxisKeyEvent`
- L24 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L28 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L29 _private prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L30 _private prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`
- L31 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_InstancedStruct.h` (Public)


#### class `UK2Node_InstancedStruct`  
`class UK2Node_InstancedStruct : public UK2Node_CallFunction`  
_L16-32_
- reflection: `UCLASS()`
- inherits: `UK2Node_CallFunction`
- desc: Node customization for MakeInstancedStruct(), SetInstancedStructValue(), and GetInstancedStructValue().
- L21 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L25 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L30 _protected function_ `virtual bool CanToggleNodePurity() const override`

### `Source/Editor/BlueprintGraph/Classes/K2Node_Knot.h` (Public)


#### class `UK2Node_Knot`  
`class UK2Node_Knot : public UK2Node`  
_L25-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L31 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L32 _public prototype_ `virtual FText GetTooltipText() const override;`
- L33 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L34 _public prototype_ `virtual bool ShouldOverridePinNames() const override;`
- L35 _public prototype_ `virtual FText GetPinNameOverride(const UEdGraphPin& Pin) const override;`
- L36 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L37 _public prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L38 _public prototype_ `virtual bool CanSplitPin(const UEdGraphPin* Pin) const override;`
- L39 _public function_ `virtual bool IsCompilerRelevant() const override`
- L40 _public prototype_ `virtual UEdGraphPin* GetPassThroughPin(const UEdGraphPin* FromPin) const override;`
- L41 _public function_ `virtual bool ShouldDrawNodeAsControlPointOnly(int32& OutInputPinIndex, int32& OutOutputPinIndex) const override`
- L45 _public prototype_ `virtual bool IsNodeSafeToIgnore() const override;` — UK2Node interface
- L46 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L47 _public prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L48 _public prototype_ `virtual void PostReconstructNode() override;`
- L49 _public function_ `virtual int32 GetNodeRefreshPriority() const override`
- L50 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L51 _public function_ `virtual bool IsNodePure() const override`
- L54 _public function_ `UEdGraphPin* GetInputPin() const`
- L59 _public function_ `UEdGraphPin* GetOutputPin() const`
- L64 _public prototype_ `void PropagatePinType();`
- L66 _public prototype_ `UEdGraphNode* GetExecTerminal() const;`
- L69 _private prototype_ `void PropagatePinTypeFromDirection(bool bFromInput);`
- L72 _private member_ `bool bRecursionGuard;` — Recursion guard boolean to prevent PropagatePinType from infinitely recursing if you manage to create a loop of knots

### `Source/Editor/BlueprintGraph/Classes/K2Node_Literal.h` (Public)


#### class `UK2Node_Literal`  
`class UK2Node_Literal : public UK2Node`  
_L26-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L33 _private member_ `TObjectPtr<class UObject> ObjectRef;` — `UPROPERTY()` — If this is an object reference literal, keep a reference here so that it can be updated as objects move around
- L38 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L39 _public prototype_ `virtual FText GetTooltipText() const override;`
- L40 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L41 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L42 _public function_ `virtual bool ShouldOverridePinNames() const override`
- L43 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L47 _public function_ `virtual bool IsNodePure() const override`
- L48 _public prototype_ `virtual AActor* GetReferencedLevelActor() const override;`
- L49 _public function_ `virtual bool DrawNodeAsVariable() const override`
- L50 _public prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L51 _public function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L52 _public prototype_ `virtual void PostReconstructNode() override;`
- L53 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L54 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L58 _public prototype_ `UEdGraphPin* GetValuePin() const;` — Accessor for the value pin of the node
- L61 _public prototype_ `void SetObjectRef(UObject* NewValue);` — Sets the LiteralValue for the pin, and changes the pin type, if necessary
- L64 _public function_ `UObject* GetObjectRef() const` — Gets the referenced object

### `Source/Editor/BlueprintGraph/Classes/K2Node_LoadAsset.h` (Public)


#### class `UK2Node_LoadAsset`  
`class UK2Node_LoadAsset : public UK2Node`  
_L25-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L30 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L31 _public prototype_ `virtual FText GetTooltipText() const override;`
- L32 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L33 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L37 _public function_ `virtual bool IsNodePure() const override` — UK2Node interface
- L38 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L39 _public prototype_ `virtual FName GetCornerIcon() const override;`
- L40 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L41 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L42 _public function_ `virtual bool NodeCausesStructuralBlueprintChange() const`
- L43 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L46 _public prototype_ `virtual const FName& GetInputPinName() const;`
- L47 _public prototype_ `virtual const FName& GetOutputPinName() const;`
- L50 _protected prototype_ `virtual FName NativeFunctionName() const;`
- L52 _protected prototype_ `virtual const FName& GetInputCategory() const;`
- L53 _protected prototype_ `virtual const FName& GetOutputCategory() const;`

#### class `UK2Node_LoadAssetClass`  
`class UK2Node_LoadAssetClass : public UK2Node_LoadAsset`  
_L57-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_LoadAsset`
- L62 _public prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L63 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L67 _protected prototype_ `virtual FName NativeFunctionName() const override;`
- L69 _protected prototype_ `virtual const FName& GetInputCategory() const override;`
- L70 _protected prototype_ `virtual const FName& GetOutputCategory() const override;`
- L72 _protected prototype_ `virtual const FName& GetInputPinName() const override;`
- L73 _protected prototype_ `virtual const FName& GetOutputPinName() const override;`

#### class `UK2Node_LoadAssets`  
`class UK2Node_LoadAssets : public UK2Node_LoadAsset`  
_L77-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_LoadAsset`
- L82 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L83 _public prototype_ `virtual FText GetTooltipText() const override;`
- L84 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L88 _protected prototype_ `virtual FName NativeFunctionName() const override;`
- L90 _protected prototype_ `virtual const FName& GetInputPinName() const override;`
- L91 _protected prototype_ `virtual const FName& GetOutputPinName() const override;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_LocalVariable.h` (Public)


#### class `UDEPRECATED_K2Node_LocalVariable`  
`class UDEPRECATED_K2Node_LocalVariable : public UK2Node_TemporaryVariable`  
_L24-59_
- reflection: `UCLASS(MinimalAPI, deprecated)`
- inherits: `UK2Node_TemporaryVariable`
- L30 _private member_ `FName CustomVariableName;` — `UPROPERTY()` — If this is not an override, allow user to specify a name for the function created by this entry point
- L34 _private member_ `FText VariableTooltip;` — `UPROPERTY()` — The local variable's assigned tooltip
- L37 _private prototype_ `virtual FText GetTooltipText() const override;`
- L38 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L39 _private prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L40 _private prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L41 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L42 _private prototype_ `virtual void PostPasteNode() override;`
- L43 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L44 _private prototype_ `virtual void ReconstructNode() override;`
- L48 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L49 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L50 _private function_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override`
- L58 _private prototype_ `void ChangeVariableType(const FEdGraphPinType& InVariableType);` — Assigns the local variable a type @param InVariableType		The type to assign this local variable to

### `Source/Editor/BlueprintGraph/Classes/K2Node_MacroInstance.h` (Public)


#### class `UK2Node_MacroInstance`  
`class UK2Node_MacroInstance : public UK2Node_Tunnel`  
_L36-126_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Tunnel`
- L44 _private member_ `TObjectPtr<class UEdGraph> MacroGraph_DEPRECATED;` — `UPROPERTY()` — A macro is like a composite node, except that the associated graph lives in another blueprint, and can be instanced multiple times.
- L47 _private member_ `FGraphReference MacroGraphReference;` — `UPROPERTY()`
- L52 _public member_ `struct FEdGraphPinType ResolvedWildcardType;` — `UPROPERTY()` — Stored type info for what type the wildcard pins in this macro should become.
- L55 _public member_ `bool bReconstructNode;` — Whether we need to reconstruct the node after the pins have changed
- L58 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L62 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L63 _public prototype_ `virtual void PreloadRequiredAssets() override;`
- L64 _public prototype_ `virtual FText GetTooltipText() const override;`
- L65 _public prototype_ `virtual FText GetKeywords() const override;`
- L66 _public prototype_ `virtual void PostPasteNode() override;`
- L67 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L68 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L69 _public function_ `virtual bool CanUserDeleteNode() const override`
- L70 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L71 _public prototype_ `virtual void NodeConnectionListChanged() override;`
- L72 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L73 _public prototype_ `virtual FString GetDocumentationExcerptName() const override;`
- L74 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L75 _public prototype_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;`
- L76 _public function_ `virtual UObject* GetJumpTargetForDoubleClick() const override`
- L77 _public prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L81 _public function_ `virtual bool DrawNodeAsExit() const override`
- L82 _public function_ `virtual bool DrawNodeAsEntry() const override`
- L83 _public prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L84 _public prototype_ `virtual void PostReconstructNode() override;`
- L85 _public prototype_ `virtual void GetNodeAttributes( TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes ) const override;`
- L86 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L87 _public function_ `virtual int32 GetNodeRefreshPriority() const override`
- L88 _public prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L89 _public prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L90 _public prototype_ `virtual FText GetCompactNodeTitle() const override;`
- L91 _public prototype_ `virtual bool ShouldDrawCompact() const override;`
- L92 _public prototype_ `virtual FName GetCornerIcon() const override;`
- L96 _public function_ `virtual bool CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage) override`
- L100 _public prototype_ `virtual void PostFixupAllWildcardPins(bool bInAllWildcardPinsUnlinked) override;`
- L103 _public function_ `void SetMacroGraph(UEdGraph* Graph)`
- L104 _public function_ `UEdGraph* GetMacroGraph() const`
- L105 _public function_ `UBlueprint* GetSourceBlueprint() const`
- L109 _public prototype_ `void InferWildcards(const TArray<UEdGraphNode*>& InNodes) const;` — Public function for inferring wildcards after macro expansion. Intended for use only by the blueprint compiler. Inference is typically performed automatically when a pin connection is made.
- L112 _public prototype_ `static FKismetUserDeclaredFunctionMetadata* GetAssociatedGraphMetadata(const UEdGraph* AssociatedMacroGraph);` — Finds the associated metadata for the macro instance if there is any; this function is not particularly fast.
- L113 _public prototype_ `static void FindInContentBrowser(TWeakObjectPtr<UK2Node_MacroInstance> MacroInstance);`
- L120 _private prototype_ `void InferWildcards();` — Helpers and implementation of 'smart' wildcard inference - which doesn't just grab the first user type and overwrite every wildcard pin with it. Instead it intelligently propagates types from the macro inputs throughout the graph, and then back to any input pins:
- L121 _private prototype_ `TArray<UEdGraphPin*> GetAllWildcardPins() const;`
- L122 _private prototype_ `void SmartInferWildcardsImpl(const TArray<UEdGraphNode*>& InNodes) const;`
- L125 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's tooltip

### `Source/Editor/BlueprintGraph/Classes/K2Node_MakeArray.h` (Public)


#### class `UK2Node_MakeArray`  
`class UK2Node_MakeArray : public UK2Node_MakeContainer`  
_L22-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_MakeContainer`
- L28 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L29 _public prototype_ `virtual FText GetTooltipText() const override;`
- L30 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L31 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L35 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L36 _public function_ `virtual bool IncludeParentNodeContextMenu() const override`
- L37 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L38 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L42 _public prototype_ `virtual FName GetOutputPinName() const override;` — UK2Node_MakeContainer interface

### `Source/Editor/BlueprintGraph/Classes/K2Node_MakeContainer.h` (Public)


#### class `FKCHandler_MakeContainer`  
`class FKCHandler_MakeContainer : public FNodeHandlingFunctor`  
_L32-45_
- inherits: `FNodeHandlingFunctor`
- L35 _public function_ `FKCHandler_MakeContainer(FKismetCompilerContext& InCompilerContext) : FNodeHandlingFunctor(InCompilerContext)`
- L40 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L41 _public prototype_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L44 _protected member_ `EKismetCompiledStatementType CompiledStatementType;`

#### class `UK2Node_MakeContainer`  
`class UK2Node_MakeContainer : public UK2Node, public IK2Node_AddPinInterface`  
_L49-104_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UK2Node,IK2Node_AddPinInterface`
- L55 _private member_ `int32 NumInputs;` — `UPROPERTY()` — The number of input pins to generate for this node
- L58 _public prototype_ `void RemoveInputPin(UEdGraphPin* Pin);`
- L60 _public prototype_ `UEdGraphPin* GetOutputPin() const;`
- L63 _public prototype_ `virtual FName GetOutputPinName() const PURE_VIRTUAL(UK2Node_MakeContainer::GetOutputPinName, return NAME_None;);` — returns a reference to the output array pin of this node, which is responsible for defining the type
- L64 _public prototype_ `virtual FName GetPinName(int32 PinIndex) const;`
- L65 _public prototype_ `virtual void GetKeyAndValuePins(TArray<UEdGraphPin*>& KeyPins, TArray<UEdGraphPin*>& ValuePins) const;`
- L69 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L70 _public prototype_ `virtual void PostReconstructNode() override;`
- L74 _public function_ `virtual bool IsNodePure() const override` — UK2Node interface
- L75 _public prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L76 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override PURE_VIRTUAL(UK2Node_MakeContainer::CreateNodeHandler, return nullptr;);`
- L77 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L78 _public function_ `virtual int32 GetNodeRefreshPriority() const override`
- L79 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins);`
- L80 _public prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L84 _public prototype_ `virtual void AddInputPin() override;` — IK2Node_AddPinInterface interface
- L91 _protected prototype_ `void ClearPinTypeToWildcard();` — If needed, will clear all pins to be wildcards
- L93 _protected prototype_ `bool CanResetToWildcard() const;`
- L96 _protected prototype_ `void InteractiveAddInputPin();` — Helper function for context menu add pin to ensure transaction is set up correctly.
- L99 _protected prototype_ `void PropagatePinType();` — Propagates the pin type from the output (set) pin to the inputs, to make sure types are consistent
- L101 _protected prototype_ `void SyncPinNames();`
- L103 _protected member_ `EPinContainerType ContainerType;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_MakeMap.h` (Public)


#### class `UK2Node_MakeMap`  
`class UK2Node_MakeMap : public UK2Node_MakeContainer`  
_L25-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_MakeContainer`
- L31 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L32 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L33 _public prototype_ `virtual FText GetTooltipText() const override;`
- L34 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L35 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L39 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L40 _public function_ `virtual bool IncludeParentNodeContextMenu() const override`
- L41 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L42 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L46 _public prototype_ `virtual FName GetOutputPinName() const override;` — UK2Node_MakeContainer interface
- L47 _public prototype_ `virtual FName GetPinName(int32 PinIndex) const override;`
- L48 _public prototype_ `virtual void GetKeyAndValuePins(TArray<UEdGraphPin*>& KeyPins, TArray<UEdGraphPin*>& ValuePins) const override;`
- L52 _public prototype_ `virtual void AddInputPin() override;` — IK2Node_AddPinInterface interface

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_MakeSet.h` (Public)


#### class `UK2Node_MakeSet`  
`class UK2Node_MakeSet : public UK2Node_MakeContainer`  
_L22-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_MakeContainer`
- L28 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L29 _public prototype_ `virtual FText GetTooltipText() const override;`
- L30 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L31 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L35 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UK2Node interface
- L36 _public function_ `virtual bool IncludeParentNodeContextMenu() const override`
- L37 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L38 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L42 _public prototype_ `virtual FName GetOutputPinName() const override;` — UK2Node_MakeContainer interface

### `Source/Editor/BlueprintGraph/Classes/K2Node_MakeStruct.h` (Public)


#### class `UK2Node_MakeStruct`  
`class UK2Node_MakeStruct : public UK2Node_StructMemberSet`  
_L33-104_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_StructMemberSet`
- desc: Pure kismet node that creates a struct with specified values for each member
- L40 _private member_ `bool bMadeAfterOverridePinRemoval;` — `UPROPERTY()` — Helper property to handle upgrades from an old system of displaying pins for the override values that properties referenced as a conditional of being set in a struct
- L50 _private prototype_ `static bool CanBeMade(const UScriptStruct* Struct, bool bForInternalUse = false);` — Returns false if: 1. The Struct has a 'native make' method Returns true if: 1. The Struct is tagged as BlueprintType and 2. The Struct has any property that is tagged as CPF_BlueprintVisible and is not CPF_BlueprintReadOnly
- L53 _private prototype_ `static bool CanBeSplit(const UScriptStruct* Struct, UBlueprint* InBP);` — Can this struct be used as a split pin
- L56 _private prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;` — UObject interface
- L57 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L61 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L62 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L63 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L64 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L65 _private prototype_ `virtual FText GetTooltipText() const override;`
- L66 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L67 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L68 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L72 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L73 _private function_ `virtual bool IsNodePure() const override`
- L74 _private function_ `virtual bool DrawNodeAsVariable() const override`
- L75 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L76 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L77 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L78 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L79 _private prototype_ `virtual void ConvertDeprecatedNode(UEdGraph* Graph, bool bOnlySafeChanges) override;`
- L102 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L103 _private member_ `FNodeTextCache CachedNodeTitle;`

#### struct `UK2Node_MakeStruct::FMakeStructPinManager`  
`struct FMakeStructPinManager : public FStructOperationOptionalPinManager`  
_L83-98_
- inherits: `FStructOperationOptionalPinManager`
- L85 _public member_ `const uint8* const SampleStructMemory;`
- L86 _public member_ `UBlueprint* OwningBP;`
- L88 _public prototype_ `FMakeStructPinManager(const uint8* InSampleStructMemory, UBlueprint* InOwningBP);`
- L90 _public function_ `bool HasAdvancedPins() const`
- L92 _protected prototype_ `virtual void GetRecordDefaults(FProperty* TestProperty, FOptionalPinFromProperty& Record) const override;`
- L93 _protected prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex, FProperty* Property) const override;`
- L94 _protected prototype_ `virtual bool CanTreatPropertyAsOptional(FProperty* TestProperty) const override;`
- L97 _protected member_ `mutable bool bHasAdvancedPins;` — set by GetRecordDefaults(), mutable as it is a const function

### `Source/Editor/BlueprintGraph/Classes/K2Node_MakeVariable.h` (Public)


#### class `UK2Node_MakeVariable`  
`class UK2Node_MakeVariable : public UK2Node`  
_L23-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L29 _private member_ `FBPVariableDescription VariableType;` — `UPROPERTY()`
- L32 _public prototype_ `void SetupVariable(const FBPVariableDescription& InVariableType, UEdGraphPin* TargetInputPin, FKismetCompilerContext& CompilerContext, UFunction* Scope, const FProperty* Property );`
- L35 _public function_ `virtual bool IsNodePure() const override` — UK2Node interface
- L36 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L39 _public prototype_ `UEdGraphPin* GetOutputPin() const;`
- L40 _public function_ `const FBPVariableDescription& GetVariableType() const`

### `Source/Editor/BlueprintGraph/Classes/K2Node_MapForEach.h` (Public)


#### class `UK2Node_MapForEach`  
`class UK2Node_MapForEach : public UK2Node`  
_L11-70_
- reflection: `UCLASS(MinimalAPI, CollapseCategories)`
- inherits: `UK2Node`
- desc: Custom blueprint node for iterating Maps in blueprints
- L17 _public prototype_ `UK2Node_MapForEach();`
- L20 _public prototype_ `[[nodiscard]] UEdGraphPin* GetMapPin() const;` — Pin Accessors
- L21 _public prototype_ `[[nodiscard]] UEdGraphPin* GetBreakPin() const;`
- L22 _public prototype_ `[[nodiscard]] UEdGraphPin* GetForEachPin() const;`
- L23 _public prototype_ `[[nodiscard]] UEdGraphPin* GetKeyPin() const;`
- L24 _public prototype_ `[[nodiscard]] UEdGraphPin* GetValuePin() const;`
- L25 _public prototype_ `[[nodiscard]] UEdGraphPin* GetCompletedPin() const;`
- L28 _public function_ `[[nodiscard]] virtual bool IsNodeSafeToIgnore() const override` — UK2Node interface
- L29 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L30 _public prototype_ `[[nodiscard]] virtual FText GetMenuCategory() const override;`
- L31 _public prototype_ `virtual void PostReconstructNode() override;`
- L35 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L36 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L37 _public prototype_ `[[nodiscard]] virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L38 _public prototype_ `[[nodiscard]] virtual FText GetTooltipText() const override;`
- L39 _public prototype_ `[[nodiscard]] virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L40 _public prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L41 _public function_ `[[nodiscard]] virtual bool ShouldShowNodeProperties() const override`
- L45 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L51 _private member_ `static const FName MapPinName;` — Pin Names
- L52 _private member_ `static const FName BreakPinName;`
- L53 _private member_ `static const FName KeyPinName;`
- L54 _private member_ `static const FName ValuePinName;`
- L55 _private member_ `static const FName CompletedPinName;`
- L58 _private prototype_ `[[nodiscard]] bool CheckForErrors(const FKismetCompilerContext& CompilerContext);` — Determine if there is any configuration options that shouldn't be allowed
- L61 _private prototype_ `void RefreshWildcardPins();` — Updates the wildcard pins based on current links
- L65 _private member_ `FString KeyName;` — `UPROPERTY(EditDefaultsOnly, Category = "Map For Each")` — A user editable hook for the display name of the key pin
- L69 _private member_ `FString ValueName;` — `UPROPERTY(EditDefaultsOnly, Category = "Map For Each")` — A user editable hook for the display name of the value pin

### `Source/Editor/BlueprintGraph/Classes/K2Node_MathExpression.h` (Public)


#### class `UK2Node_MathExpression`  
`class UK2Node_MathExpression : public UK2Node_Composite`  
_L35-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Composite`
- desc: This node type acts like a collapsed node, a single node that represents a larger sub-network of nodes (contained within a sub-graph). This node will take the math expression it was named with, and attempt to convert it into a series of math nodes. If it is unsuccessful, then it generates a series of actionable errors.
- L43 _public member_ `FString Expression;` — `UPROPERTY(EditAnywhere, Category = Expression)` — The math expression to evaluate
- L46 _public member_ `bool bMadeAfterRotChange;` — `UPROPERTY()`
- L50 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L51 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L55 _public prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L56 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L57 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L58 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L59 _public prototype_ `virtual void ReconstructNode() override;`
- L60 _public prototype_ `virtual void FindDiffs(class UEdGraphNode* OtherNode, struct FDiffResults& Results ) override;`
- L61 _public function_ `virtual bool ShouldMergeChildGraphs() const override`
- L65 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L66 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L67 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L68 _public function_ `virtual bool IsNodePure() const`
- L72 _public function_ `virtual bool CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage) override`
- L77 _private prototype_ `bool ShouldExpandInsteadCompile() const;` — Returns true, when the node can/should not be optimized.
- L85 _private prototype_ `void RebuildExpression(FString NewExpression);` — Clears this node's sub-graph, and then takes the supplied string and parses, and converts it into a series of new graph nodes. @param  NewExpression	The new string we wish to replace the current "Expression".
- L92 _private prototype_ `void ClearExpression();` — Clears the cached expression string, deletes all generated node, clears input pins, and resets the parser and graph generator (priming this node for a new expression).
- L95 _private prototype_ `FString SanitizeDisplayExpression(FString InExpression) const;` — Sanitizes an expression for display, removing outermost parentheses
- L98 _private prototype_ `FText GetFullTitle(FText InExpression) const;` — Helper function to build the node's full title
- L101 _private member_ `TSharedPtr<class FCompilerResultsLog> CachedMessageLog;` — Cached so we don't have to regenerate it when the graph is recompiled
- L104 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title
- L107 _private member_ `FNodeTextCache CachedDisplayExpression;` — Constructing the display string for a Math Expression is costly, so we cache it

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_Message.h` (Public)


#### class `UK2Node_Message`  
`class UK2Node_Message : public UK2Node_CallFunction`  
_L23-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction`
- L29 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L30 _private prototype_ `virtual FText GetTooltipText() const override;`
- L34 _private function_ `virtual bool IsNodeSafeToIgnore() const override`
- L35 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L36 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L37 _private prototype_ `virtual FName GetCornerIcon() const override;`
- L38 _private function_ `virtual bool IsNodePure() const override`
- L42 _private prototype_ `virtual UEdGraphPin* CreateSelfPin(const UFunction* Function) override;`
- L45 _protected prototype_ `virtual void FixupSelfMemberContext() override;`
- L47 _protected function_ `virtual bool CanToggleNodePurity() const override`
- L60 _protected prototype_ `void ExpandLevelStreamingHandlers(class FKismetCompilerContext& InCompilerContext, UEdGraph* InSourceGraph, class UEdGraphPin* InStartingExecPin, class UEdGraphPin* InMessageSelfPin, class UK2Node_DynamicCast* InCastToInterfaceNode);` — Helper function for expand node to expand the message to handle the case that a ULevelStreaming may be passed which needs to have its LevelScriptActor pulled out @param InCompilerContext			CompilerContext from ExpandNode @param InSourceGraph				Graph that the node are expanding from @param InStartingExecPin			Exec pin that connects to the message node, to correctly be mapped into the exec pins of the expanded nodes @param InMessageSelfPin			The message node's self pin, to correctly be mapped into the object pins of the expanded nodes @param InCastToInterfaceNode		Previously generated node to cast to the message's interface, to be wired into the expanded nodes
- L63 _protected member_ `FNodeTitleTextTable CachedNodeTitles;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/BlueprintGraph/Classes/K2Node_MultiGate.h` (Public)


#### class `UK2Node_MultiGate`  
`class UK2Node_MultiGate : public UK2Node_ExecutionSequence`  
_L26-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_ExecutionSequence`
- L32 _private member_ `TObjectPtr<class UK2Node_TemporaryVariable> DataNode;` — `UPROPERTY(transient)` — Reference to the integer that contains
- L35 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L36 _private prototype_ `virtual FText GetTooltipText() const override;`
- L37 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L38 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L42 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L43 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L44 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L45 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L49 _private prototype_ `virtual bool CanAddPin() const override;`
- L53 _private prototype_ `UEdGraphPin* GetResetPin() const;` — Getting pin access
- L54 _private prototype_ `UEdGraphPin* GetIsRandomPin() const;`
- L55 _private prototype_ `UEdGraphPin* GetLoopPin() const;`
- L56 _private prototype_ `UEdGraphPin* GetStartIndexPin() const;`
- L57 _private prototype_ `void GetOutPins(TArray<UEdGraphPin*>& OutPins) const;`
- L58 _private prototype_ `int32 GetNumOutPins() const;`
- L61 _private prototype_ `void GetMarkBitFunction(FName& FunctionName, UClass** FunctionClass);` — Gets the name and class of the MarkBit function from the KismetNodeHelperLibrary
- L63 _private prototype_ `void GetHasUnmarkedBitFunction(FName& FunctionName, UClass** FunctionClass);` — Gets the name and class of the HasUnmarkedBit function from the KismetNodeHelperLibrary
- L65 _private prototype_ `void GetUnmarkedBitFunction(FName& FunctionName, UClass** FunctionClass);` — Gets the name and class of the MarkFirstUnmarkedBit function from the KismetNodeHelperLibrary
- L67 _private prototype_ `void GetConditionalFunction(FName& FunctionName, UClass** FunctionClass);` — Gets the name and class of the Greater_IntInt function from the KismetMathLibrary
- L69 _private prototype_ `void GetEqualityFunction(FName& FunctionName, UClass** FunctionClass);` — Gets the name and class of the EqualEqual_IntInt function from the KismetMathLibrary
- L71 _private prototype_ `void GetBoolNotEqualFunction(FName& FunctionName, UClass** FunctionClass);` — Gets the name and class of the NotEqual_BoolBool function from the KismetMathLibrary
- L73 _private prototype_ `void GetPrintStringFunction(FName& FunctionName, UClass** FunctionClass);` — Gets the name and class of the PrintString function
- L75 _private prototype_ `void GetClearAllBitsFunction(FName& FunctionName, UClass** FunctionClass);` — Gets the name and class of the ClearAllBits function from the KismetNodeHelperLibrary
- L79 _private prototype_ `virtual FName GetPinNameGivenIndex(int32 Index) const override;` — Returns the exec output pin name for a given 0-based index

### `Source/Editor/BlueprintGraph/Classes/K2Node_PromotableOperator.h` (Public)


#### class `UK2Node_PromotableOperator`  
`class UK2Node_PromotableOperator : public UK2Node_CallFunction, public IK2Node_AddPinInterface`  
_L29-218_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction,IK2Node_AddPinInterface`
- desc: The promotable operator node allows for pin types to be promoted to others, i.e. float to double
- L36 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L37 _public prototype_ `virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;`
- L38 _public prototype_ `virtual FText GetTooltipText() const override;`
- L39 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L40 _public prototype_ `virtual void NodeConnectionListChanged() override;`
- L41 _public prototype_ `virtual void PostPasteNode() override;`
- L45 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;` — UK2Node interface
- L46 _public prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* ChangedPin) override;`
- L47 _public prototype_ `virtual void PostReconstructNode() override;`
- L48 _public prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L49 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L50 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L51 _public prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;`
- L55 _public prototype_ `virtual void AddInputPin() override;` — IK2Node_AddPinInterface interface
- L56 _public prototype_ `virtual bool CanAddPin() const override;`
- L57 _public prototype_ `virtual bool CanRemovePin(const UEdGraphPin* Pin) const override;`
- L58 _public prototype_ `virtual void RemoveInputPin(UEdGraphPin* Pin) override;`
- L62 _public prototype_ `UEdGraphPin* GetAdditionalPin(int32 PinIndex) const;` — Gets the additional pin that was created at this index
- L65 _public prototype_ `UEdGraphPin* FindTolerancePin() const;` — Attempts to find the error tolerance pin on this node. Can return nullptr.
- L68 _public prototype_ `virtual void SetFromFunction(const UFunction* Function);` — UK2Node_CallFunction interface
- L72 _public prototype_ `void ResetNodeToWildcard();` — Recombines all split pins and sets the node to have default values (all wildcard pins)
- L76 _protected function_ `virtual bool CanToggleNodePurity() const override` — UK2Node_CallFunction interface
- L85 _private prototype_ `UEdGraphPin* AddInputPinImpl(int32 PinIndex);` — Add an additional pin to this node based on it's index. Will create a new wildcard pin with the appropriate name and notify that this pin has changed
- L88 _private prototype_ `bool IsAdditionalPin(const UEdGraphPin& Pin) const;` — Returns true if this pin was added via the IK2Node_AddPinInterface interface
- L91 _private prototype_ `bool IsTolerancePin(const UEdGraphPin& Pin) const;` — Returns true if the given pin is a tolerance pin for a comparison operator
- L94 _private prototype_ `void RecombineAllSplitPins();` — Helper function to recombine all split pins that this node may have
- L97 _private prototype_ `void UpdateFromBestMatchingFunction();` — Update the pins on this node with the function that is the best match given the current connections
- L103 _private prototype_ `bool HasAnyConnectionsOrDefaults() const;` — @return	True if this node has any connections attached to it, or the default values have been modified by the user
- L111 _private prototype_ `bool HasDeterminingComparisonTypes() const;` — @return	True if this is a comparison operator node and there are no connections/default values on input pins. The output pins is not considered in this check, because it will always be a bool so it does not determine the types.
- L118 _private prototype_ `bool CreateIntermediateCast(UK2Node_CallFunction* SourceNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UEdGraphPin* InputPin, UEdGraphPin* OutputPin);` — Attempts to create a cast node and connect it to a call function node @return	True if the intermediate connection was made successfully
- L126 _private prototype_ `UK2Node_CallFunction* CreateIntermediateNode(UK2Node_CallFunction* PreviousNode, const UFunction* const OpFunction, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph);` — Spawn a new intermediate call function node with the given operator function and allocate its default pins. Place it next to the given Previous node @return	An intermediate call function node placed next to the "PreviousNode"
- L135 _private prototype_ `void EvaluatePinsFromChange(UEdGraphPin* ChangedPin, const bool bFromConversion = false);` — Re-evaluates the in types on this node based on all the current connections and the given pin that has changed. @param ChangedPin			The pin that has been change @param bFromConversion	True if the pin modification is coming from a conversion.
- L138 _private prototype_ `bool UpdateOpName();` — Helper to make sure we have the most up to date operation name. Returns true upon success
- L144 _private prototype_ `void UpdatePinsFromFunction(const UFunction* Function, UEdGraphPin* ChangedPin = nullptr, bool bIsFromConversion = false);` — Update the pins on this node based on the given function. This modifies pins, meant for use by PinConnectionListChanged, not during node construction.
- L151 _private prototype_ `TArray<UEdGraphPin*> GetInputPins(bool bIncludeLinks = false) const;` — Returns all pins that have the EGPD_Input direction @param bIncludeLinks	If true, than this will also include all the pins that are linked to the inputs. This is useful for gathering what the highest type may be
- L159 _private prototype_ `void GetPinsToConsider(TArray<UEdGraphPin*>& OutArray) const;` — Get all pins on this node that can be considered when determining what function is the best match @param OutArray	Array to populate with the considered pins
- L169 _private prototype_ `void CreateConversionMenu(struct FToolMenuSection& ConversionSection, UEdGraphPin* ContextPin) const;` — Build the context menu to convert the given pin to a different type. If the pin is a wildcard, offer any possible types. Otherwise, offer to reset the node to wildcard. @param Menu			The parent context menu @param ContextPin		The pin to convert
- L173 _private member_ `FName OperationName;` — `UPROPERTY()` — The name that this operation uses ("Add", "Multiply", etc)
- L177 _private member_ `int32 NumAdditionalInputs;` — `UPROPERTY()` — The current number of additional pins on this node
- L180 _private member_ `bool bDefaultValueReentranceGuard;` — Guard to prevent possible recursive calls from ResetPinToAutogeneratedDefaultValue when breaking all links to this node
- L185 _public prototype_ `UEdGraphPin* GetOutputPin() const;` — Returns the first pin with the EGPD_Output direction
- L187 _public function_ `const FName GetOperationName() const`
- L197 _public prototype_ `void ConvertPinType(UEdGraphPin* PinToChange, const FEdGraphPinType NewPinType);` — Convert the given pin to the new pin type. If the new type is wildcard then break all connections and reset the node. Invalidates tooltips upon completion. This function is to be used by the context menu and includes a transaction. @param PinToChange		The Pin to convert @param NewPinType			The pin's new type
- L206 _public prototype_ `bool CanConvertPinType(const UEdGraphPin* Pin) const;` — Returns true if the given pin can be converted via the context menu to another type @param Pin		The pin to consider @return bool		True if a conversion is possible
- L212 _public prototype_ `static bool CanConvertComparisonOperatorNodeType(const UEdGraphNode* Node);` — Returns true if we can convert this node to another comparison operator type. This will only be true if the current operator is a comparison operator such as ==, !=, <, etc.
- L217 _public prototype_ `static void ConvertComparisonOperatorNode(UEdGraphNode* Node, const FName NewOpName);` — Converts the given node to use the new operator name

### `Source/Editor/BlueprintGraph/Classes/K2Node_PureAssignmentStatement.h` (Public)


#### class `UK2Node_PureAssignmentStatement`  
`class UK2Node_PureAssignmentStatement : public UK2Node`  
_L19-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L24 _private member_ `static FName VariablePinName;` — Name of the Variable pin for this node
- L26 _private member_ `static FName ValuePinName;` — Name of the Value pin for this node
- L28 _private member_ `static FName OutputPinName;` — Name of the output pin for this node
- L31 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L35 _private function_ `virtual bool IsNodePure() const override`
- L36 _private prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L37 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L38 _private function_ `virtual int32 GetNodeRefreshPriority() const override`
- L42 _private prototype_ `UEdGraphPin* GetOutputPin() const;` — Get the Then output pin
- L44 _private prototype_ `UEdGraphPin* GetVariablePin() const;` — Get the Variable input pin
- L46 _private prototype_ `UEdGraphPin* GetValuePin() const;` — Get the Value input pin

### `Source/Editor/BlueprintGraph/Classes/K2Node_RemoveDelegate.h` (Public)


#### class `UK2Node_RemoveDelegate`  
`class UK2Node_RemoveDelegate : public UK2Node_BaseMCDelegate`  
_L10-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_BaseMCDelegate`
- L16 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L17 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L21 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_Select.h` (Public)


#### class `UK2Node_Select`  
`class UK2Node_Select : public UK2Node, public INodeDependingOnEnumInterface, public IK2Node_AddPinInterface`  
_L32-143_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Ternary Select"))`
- inherits: `UK2Node,INodeDependingOnEnumInterface,IK2Node_AddPinInterface`
- L39 _private member_ `int32 NumOptionPins;` — `UPROPERTY()` — The number of selectable options this node currently has
- L43 _private member_ `FEdGraphPinType IndexPinType;` — `UPROPERTY()` — The pin type of the index pin
- L47 _private member_ `TObjectPtr<UEnum> Enum;` — `UPROPERTY()` — Name of the enum being switched on
- L51 _private member_ `TArray<FName> EnumEntries;` — `UPROPERTY()` — List of the current entries in the enum (Pin Names)
- L55 _private member_ `TArray<FText> EnumEntryFriendlyNames;` — `UPROPERTY(Transient)` — List of the current entries in the enum (Pin Friendly Names)
- L59 _private member_ `uint8 bReconstructNode:1;` — `UPROPERTY(Transient)` — Whether we need to reconstruct the node after the pins have changed
- L61 _private member_ `uint8 bReconstructForPinTypeChange:1;`
- L67 _private prototype_ `void OnPinTypeChanged(UEdGraphPin* Pin);` — Respond to a change to the PinType for a selected pin @param Pin	The pin that is changing type
- L72 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L73 _public prototype_ `virtual FText GetTooltipText() const override;`
- L74 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L75 _public prototype_ `virtual void NodeConnectionListChanged() override;`
- L76 _public prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L77 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L78 _public prototype_ `virtual void PostPasteNode() override;`
- L79 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L83 _public prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L84 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L85 _public prototype_ `virtual void PostReconstructNode() override;`
- L86 _public function_ `virtual bool IsNodeSafeToIgnore() const override`
- L87 _public function_ `virtual bool IsNodePure() const override`
- L88 _public prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L89 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L90 _public prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L91 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L92 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L93 _public function_ `virtual int32 GetNodeRefreshPriority() const override`
- L94 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L98 _public function_ `virtual class UEnum* GetEnum() const override` — INodeDependingOnEnumInterface
- L99 _public prototype_ `virtual void ReloadEnum(class UEnum* InEnum) override;`
- L100 _public function_ `virtual bool ShouldBeReconstructedAfterEnumChanged() const override`
- L104 _public prototype_ `virtual bool CanAddPin() const override;`
- L105 _public prototype_ `virtual void AddInputPin() override;`
- L109 _public prototype_ `UEdGraphPin* GetReturnValuePin() const;` — Get the return value pin
- L111 _public prototype_ `virtual UEdGraphPin* GetIndexPin() const;` — Get the condition pin
- L113 _public prototype_ `virtual void GetOptionPins(TArray<UEdGraphPin*>& OptionPins) const;` — Returns a list of pins that represent the selectable options
- L116 _public prototype_ `void GetConditionalFunction(FName& FunctionName, UClass** FunctionClass);` — Gets the name and class of the EqualEqual_IntInt function
- L118 _public prototype_ `static void GetPrintStringFunction(FName& FunctionName, UClass** FunctionClass);` — Gets the name and class of the PrintString function
- L121 _public prototype_ `void RemoveOptionPinToNode();` — Removes the last option pin from the node
- L123 _public prototype_ `virtual bool CanRemoveOptionPinToNode() const;` — Return whether an option pin can be removed to the node
- L130 _public prototype_ `void ChangePinType(UEdGraphPin* Pin);` — Notification from the editor that the user wants to change the PinType on a selected pin @param Pin	The pin the user wants to change the type for
- L136 _public prototype_ `bool CanChangePinType(UEdGraphPin* Pin) const;` — Whether the user can change the pintype on a selected pin @param Pin	The pin in question
- L139 _public prototype_ `virtual void SetEnum(UEnum* InEnum, bool bForceRegenerate = false);` — Bind the options to a named enum
- L142 _private prototype_ `UEdGraphPin* GetIndexPinUnchecked() const;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_Self.h` (Public)


#### class `UK2Node_Self`  
`class UK2Node_Self : public UK2Node`  
_L20-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L25 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private prototype_ `virtual FText GetTooltipText() const override;`
- L27 _private prototype_ `virtual FText GetKeywords() const override;`
- L28 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L29 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L33 _private function_ `virtual bool IsNodePure() const override`
- L34 _private function_ `virtual bool DrawNodeAsVariable() const override`
- L35 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L36 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L37 _private prototype_ `virtual FText GetMenuCategory() const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_SetFieldsInStruct.h` (Public)


#### class `UK2Node_SetFieldsInStruct`  
`class UK2Node_SetFieldsInStruct : public UK2Node_MakeStruct`  
_L29-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_MakeStruct`
- desc: Pure kismet node that creates a struct with specified values for each member
- L34 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L35 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L36 _private prototype_ `virtual FText GetTooltipText() const override;`
- L37 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L38 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L39 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L40 _private prototype_ `virtual bool CanSplitPin(const UEdGraphPin* Pin) const override;`
- L41 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L45 _private function_ `virtual bool IsNodePure() const override`
- L46 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L47 _private function_ `virtual void ConvertDeprecatedNode(UEdGraph* Graph, bool bOnlySafeChanges) override`
- L50 _private prototype_ `static bool ShowCustomPinActions(const UEdGraphPin* InGraphPin, bool bIgnorePinsNum);`
- L58 _private prototype_ `void RemoveFieldPins(UEdGraphPin* InGraphPin, EPinsToRemove Selection);`
- L59 _private prototype_ `bool AllPinsAreShown() const;`
- L60 _private prototype_ `void RestoreAllPins();`
- L63 _protected prototype_ `void BackTracePinPath(UEdGraphPin* OutputPin, TFunctionRef<void(UEdGraphPin*)> Predicate) const;`
- L76 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L77 _private member_ `FNodeTextCache CachedNodeTitle;`
- L79 _private member_ `mutable bool bRecursionGuard;`

#### enum `UK2Node_SetFieldsInStruct::EPinsToRemove`  
`enum EPinsToRemove`  
_L52-56_
- L54 _public enumerator_ `GivenPin`
- L55 _public enumerator_ `AllOtherPins`

#### struct `UK2Node_SetFieldsInStruct::FSetFieldsInStructPinManager`  
`struct FSetFieldsInStructPinManager : public FMakeStructPinManager`  
_L65-72_
- inherits: `FMakeStructPinManager`
- L68 _public function_ `FSetFieldsInStructPinManager(const uint8* InSampleStructMemory, UBlueprint* BP) : FMakeStructPinManager(InSampleStructMemory, BP)`
- L71 _public prototype_ `virtual void GetRecordDefaults(FProperty* TestProperty, FOptionalPinFromProperty& Record) const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_SetForEach.h` (Public)


#### class `UK2Node_SetForEach`  
`class UK2Node_SetForEach : public UK2Node`  
_L11-64_
- reflection: `UCLASS(MinimalAPI, CollapseCategories)`
- inherits: `UK2Node`
- desc: Custom blueprint node for iterating Sets in blueprints
- L17 _public prototype_ `UK2Node_SetForEach();`
- L20 _public prototype_ `[[nodiscard]] UEdGraphPin* GetSetPin() const;` — Pin Accessors
- L21 _public prototype_ `[[nodiscard]] UEdGraphPin* GetBreakPin() const;`
- L22 _public prototype_ `[[nodiscard]] UEdGraphPin* GetForEachPin() const;`
- L23 _public prototype_ `[[nodiscard]] UEdGraphPin* GetValuePin() const;`
- L24 _public prototype_ `[[nodiscard]] UEdGraphPin* GetCompletedPin() const;`
- L27 _public function_ `[[nodiscard]] virtual bool IsNodeSafeToIgnore() const override` — UK2Node interface
- L28 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L29 _public prototype_ `[[nodiscard]] virtual FText GetMenuCategory() const override;`
- L30 _public prototype_ `virtual void PostReconstructNode() override;`
- L34 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L35 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L36 _public prototype_ `[[nodiscard]] virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L37 _public prototype_ `[[nodiscard]] virtual FText GetTooltipText() const override;`
- L38 _public prototype_ `[[nodiscard]] virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L39 _public prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L40 _public function_ `[[nodiscard]] virtual bool ShouldShowNodeProperties() const override`
- L44 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L50 _private member_ `static const FName SetPinName;` — Pin Names
- L51 _private member_ `static const FName BreakPinName;`
- L52 _private member_ `static const FName ValuePinName;`
- L53 _private member_ `static const FName CompletedPinName;`
- L56 _private prototype_ `[[nodiscard]] bool CheckForErrors(const FKismetCompilerContext& CompilerContext);` — Determine if there is any configuration options that shouldn't be allowed
- L59 _private prototype_ `void RefreshWildcardPins();` — Updates the wildcard pins based on current links
- L63 _private member_ `FString ValueName;` — `UPROPERTY(EditDefaultsOnly, Category = "Set For Each")` — A user editable hook for the display name of the value pin

### `Source/Editor/BlueprintGraph/Classes/K2Node_SetVariableOnPersistentFrame.h` (Public)


#### class `UK2Node_SetVariableOnPersistentFrame`  
`class UK2Node_SetVariableOnPersistentFrame : public UK2Node`  
_L21-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L27 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L31 _public function_ `virtual bool IsNodePure() const override`
- L32 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_SpawnActor.h` (Public)


#### class `UK2Node_SpawnActor`  
`class UK2Node_SpawnActor : public UK2Node`  
_L29-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L34 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L35 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L36 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L37 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L38 _private prototype_ `virtual FText GetTooltipText() const override;`
- L39 _private prototype_ `virtual bool IsDeprecated() const override;`
- L40 _private prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType DeprecationType) const override;`
- L41 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L42 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L43 _private prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L47 _private function_ `virtual bool IsNodeSafeToIgnore() const override`
- L48 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L49 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L50 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L51 _private prototype_ `virtual void GetNodeAttributes( TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes ) const override;`
- L56 _private prototype_ `void CreatePinsForClass(UClass* InClass);` — Create new pins to show properties on archetype
- L58 _private prototype_ `bool IsSpawnVarPin(UEdGraphPin* Pin) const;` — See if this is a spawn variable pin, or a 'default' pin
- L61 _private prototype_ `UEdGraphPin* GetBlueprintPin(const TArray<UEdGraphPin*>* InPinsToSearch=NULL) const;` — Get the blueprint input pin
- L63 _private prototype_ `UEdGraphPin* GetWorldContextPin() const;` — Get the world context input pin, can return NULL
- L65 _private prototype_ `UEdGraphPin* GetSpawnTransformPin() const;` — Get the spawn transform input pin
- L67 _private prototype_ `UEdGraphPin* GetNoCollisionFailPin() const;` — Get the no collision fail input pin
- L69 _private prototype_ `UEdGraphPin* GetResultPin() const;` — Get the result output pin
- L73 _private prototype_ `UClass* GetClassToSpawn(const TArray<UEdGraphPin*>* InPinsToSearch=NULL) const;` — Get the class that we are going to spawn
- L76 _private member_ `FText NodeTooltip;` — Tooltip text for this node.
- L79 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/BlueprintGraph/Classes/K2Node_SpawnActorFromClass.h` (Public)


#### class `UK2Node_SpawnActorFromClass`  
`class UK2Node_SpawnActorFromClass : public UK2Node_ConstructObjectFromClass`  
_L33-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_ConstructObjectFromClass`
- L38 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L39 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L40 _private prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;`
- L41 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L42 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L43 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L44 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L48 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L49 _private prototype_ `virtual void PostLoad() override;`
- L53 _private function_ `virtual bool IsNodeSafeToIgnore() const override`
- L54 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L55 _private prototype_ `virtual void GetNodeAttributes( TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes ) const override;`
- L56 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L60 _private prototype_ `virtual UClass* GetClassPinBaseClass() const;`
- L61 _private prototype_ `virtual bool IsSpawnVarPin(UEdGraphPin* Pin) const override;`
- L66 _private prototype_ `void FixupScaleMethodPin();`
- L69 _private prototype_ `UEdGraphPin* GetSpawnTransformPin() const;` — Get the spawn transform input pin
- L71 _private prototype_ `UEdGraphPin* GetCollisionHandlingOverridePin() const;` — Get the collision handling method input pin
- L73 _private prototype_ `UEdGraphPin* GetScaleMethodPin() const;` — Get the collision handling method input pin
- L74 _private prototype_ `UEdGraphPin* TryGetScaleMethodPin() const;`
- L76 _private prototype_ `UEdGraphPin* GetOwnerPin() const;` — Get the actor owner pin
- L78 _private prototype_ `void MaybeUpdateCollisionPin(TArray<UEdGraphPin*>& OldPins);`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_StructMemberGet.h` (Public)


#### class `UK2Node_StructMemberGet`  
`class UK2Node_StructMemberGet : public UK2Node_StructOperation`  
_L25-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_StructOperation`
- desc: Pure kismet node that gets one or more member variables of a struct
- L30 _private member_ `TArray<FOptionalPinFromProperty> ShowPinForProperties;` — `UPROPERTY(EditAnywhere, Category=PinOptions, EditFixedSize)`
- L33 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L34 _private prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L38 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L39 _private prototype_ `virtual FText GetTooltipText() const override;`
- L40 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L44 _private function_ `virtual bool IsNodePure() const override` — UK2Node interface
- L45 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L46 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L50 _private prototype_ `void AllocatePinsForSingleMemberGet(FName MemberName);` — AllocateDefaultPins with just one member set
- L54 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L55 _private member_ `FNodeTextCache CachedNodeTitle;`
- L57 _private member_ `TArray<FName> OldShownPins;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_StructMemberSet.h` (Public)


#### class `UK2Node_StructMemberSet`  
`class UK2Node_StructMemberSet : public UK2Node_StructOperation`  
_L27-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_StructOperation`
- desc: Imperative kismet node that sets one or more member variables of a struct
- L32 _private member_ `TArray<FOptionalPinFromProperty> ShowPinForProperties;` — `UPROPERTY(EditAnywhere, Category=PinOptions, EditFixedSize)`
- L35 _private prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;` — UObject interface
- L36 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L40 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L41 _private prototype_ `virtual FText GetTooltipText() const override;`
- L42 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L46 _private function_ `virtual bool IsNodePure() const override` — UK2Node interface
- L47 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L48 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L49 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L53 _private prototype_ `void AllocateExecPins();` — Helper for AllocateDefaultPins
- L56 _private prototype_ `FBoolProperty* GetOverrideConditionForProperty(const FProperty* InProperty) const;` — Returns the override condition that's bound to the given property, if one exists. An override is a edit condition flag that is not exposed as an optional input pin.
- L60 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L61 _private member_ `FNodeTextCache CachedNodeTitle;`
- L63 _private member_ `TArray<FName> OldShownPins;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_StructOperation.h` (Public)


#### class `UK2Node_StructOperation`  
`class UK2Node_StructOperation : public UK2Node_Variable`  
_L29-81_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UK2Node_Variable`
- L35 _private member_ `TObjectPtr<UScriptStruct> StructType;` — `UPROPERTY()` — Class that this variable is defined in.
- L38 _private prototype_ `virtual FString GetPinMetaData(FName InPinName, FName InKey) override;`
- L39 _private prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput = nullptr) const override;`
- L44 _private function_ `virtual bool ShouldShowNodeProperties() const override` — virtual bool DrawNodeAsVariable() const override { return true; }
- L45 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L46 _private prototype_ `virtual FString GetFindReferenceSearchString_Impl(EGetFindReferenceSearchStringFlags InFlags) const override;`
- L47 _private prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L76 _protected prototype_ `bool DoRenamedPinsMatch(const UEdGraphPin* NewPin, const UEdGraphPin* OldPin, bool bStructInVariablesOut) const;`
- L79 _protected prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FMakeStructSpawnerAllowedDelegate, const UScriptStruct*, bool);` — Utility function to set up menu actions to set the struct type and promote category
- L80 _protected prototype_ `void SetupMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar, const FMakeStructSpawnerAllowedDelegate& AllowedDelegate, EEdGraphPinDirection PinDirectionToPromote) const;`

#### struct `UK2Node_StructOperation::FStructOperationOptionalPinManager`  
`struct FStructOperationOptionalPinManager : public FOptionalPinManager`  
_L52-74_
- inherits: `FOptionalPinManager`
- desc: Updater for subclasses that allow hiding pins
- L55 _public function_ `virtual void GetRecordDefaults(FProperty* TestProperty, FOptionalPinFromProperty& Record) const override`
- L72 _public prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex, FProperty* Property) const override;`

#### Free symbols / members of external scopes

- L79 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FMakeStructSpawnerAllowedDelegate, const UScriptStruct*, bool);` — Utility function to set up menu actions to set the struct type and promote category

### `Source/Editor/BlueprintGraph/Classes/K2Node_Switch.h` (Public)


#### class `UK2Node_Switch`  
`class UK2Node_Switch : public UK2Node`  
_L29-110_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UK2Node`
- L35 _private member_ `uint32 bHasDefaultPin:1;` — `UPROPERTY(EditAnywhere, Category=PinOptions)` — If true switch has a default pin
- L39 _private member_ `FName FunctionName;` — `UPROPERTY()` — The function underpining the switch, if required
- L43 _private member_ `TSubclassOf<class UObject> FunctionClass;` — `UPROPERTY()` — The class that the function is from.
- L46 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L50 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L51 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L52 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L56 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;` — UK2Node interface
- L57 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L58 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L59 _private function_ `virtual bool CanEverRemoveExecutionPin() const override`
- L64 _private prototype_ `virtual FString GetExportTextForPin(const UEdGraphPin* Pin) const;`
- L67 _private function_ `virtual FName GetUniquePinName()` — Gets a unique pin name, the next in the sequence
- L70 _private prototype_ `virtual FEdGraphPinType GetPinType() const PURE_VIRTUAL(UK2Node_Switch::GetPinType, return FEdGraphPinType();) virtual FEdGraphPinType GetInnerCaseType() const;` — Gets the pin type from the schema for the subclass
- L77 _private prototype_ `virtual void AddPinToSwitchNode();` — Adds a new execution pin to a switch node
- L84 _private prototype_ `virtual void RemovePinFromSwitchNode(UEdGraphPin* TargetPin);` — Removes the specified execution pin from an switch node @param	TargetPin	The pin to remove from the node
- L87 _private prototype_ `virtual bool CanRemoveExecutionPin(UEdGraphPin* TargetPin) const;` — Whether an execution pin can be removed from the node or not
- L90 _private function_ `virtual bool SupportsAddPinButton() const` — Determines whether the add button should be enabled
- L93 _private prototype_ `UEdGraphPin* GetSelectionPin() const;` — Getting pin access
- L94 _private prototype_ `UEdGraphPin* GetDefaultPin() const;`
- L95 _private prototype_ `UEdGraphPin* GetFunctionPin() const;`
- L97 _private prototype_ `static FName GetSelectionPinName();`
- L99 _private prototype_ `virtual FName GetPinNameGivenIndex(int32 Index) const;`
- L102 _protected function_ `virtual void CreateSelectionPin()`
- L103 _protected function_ `virtual void CreateCasePins()`
- L104 _protected prototype_ `virtual void CreateFunctionPin();`
- L105 _protected function_ `virtual void RemovePin(UEdGraphPin* TargetPin)`
- L109 _private member_ `bool bHasDefaultPinValueChanged;` — Editor-only field that signals a default pin setting change

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_SwitchEnum.h` (Public)


#### class `UK2Node_SwitchEnum`  
`class UK2Node_SwitchEnum : public UK2Node_Switch, public INodeDependingOnEnumInterface`  
_L29-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Switch,INodeDependingOnEnumInterface`
- L35 _private member_ `TObjectPtr<UEnum> Enum;` — `UPROPERTY()` — Name of the enum being switched on
- L39 _private member_ `TArray<FName> EnumEntries;` — `UPROPERTY()` — List of the current entries in the enum
- L43 _private member_ `TArray<FText> EnumFriendlyNames;` — `UPROPERTY(Transient)` — List of the current entries in the enum
- L46 _private function_ `virtual class UEnum* GetEnum() const override` — INodeDependingOnEnumInterface
- L47 _private prototype_ `virtual void ReloadEnum(class UEnum* InEnum) override;`
- L48 _private function_ `virtual bool ShouldBeReconstructedAfterEnumChanged() const override`
- L52 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L53 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L54 _private prototype_ `virtual void AddPinSearchMetaDataInfo(const UEdGraphPin* Pin, TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L55 _private prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L59 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;` — UK2Node interface
- L60 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L61 _private function_ `virtual bool CanEverRemoveExecutionPin() const override`
- L62 _private function_ `virtual bool CanUserEditPinAdvancedViewFlag() const override`
- L63 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L67 _private prototype_ `virtual FEdGraphPinType GetPinType() const override;` — UK2Node_Switch Interface
- L68 _private prototype_ `virtual void AddPinToSwitchNode() override;`
- L69 _private prototype_ `virtual void RemovePinFromSwitchNode(UEdGraphPin* TargetPin) override;`
- L70 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L71 _private function_ `virtual bool SupportsAddPinButton() const`
- L75 _private prototype_ `void SetEnum(UEnum* InEnum);` — Bind the switch to a named enum
- L79 _protected prototype_ `virtual void CreateCasePins() override;` — Helper method to set-up pins
- L81 _protected prototype_ `virtual void CreateSelectionPin() override;` — Helper method to set-up correct selection pin
- L84 _protected function_ `virtual void RemovePin(UEdGraphPin* TargetPin) override` — Don't support removing pins from an enum
- L88 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/BlueprintGraph/Classes/K2Node_SwitchInteger.h` (Public)


#### class `UK2Node_SwitchInteger`  
`class UK2Node_SwitchInteger : public UK2Node_Switch`  
_L23-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Switch`
- L29 _private member_ `int32 StartIndex;` — `UPROPERTY(EditAnywhere, Category=PinOptions, meta=(NoSpinbox=true))` — Set the starting index for the node
- L32 _private prototype_ `void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L36 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L37 _private prototype_ `virtual FText GetTooltipText() const override;`
- L38 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L42 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L46 _private prototype_ `virtual FName GetUniquePinName() override;` — UK2Node_Switch Interface
- L47 _private prototype_ `virtual FName GetPinNameGivenIndex(int32 Index) const override;`
- L48 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L49 _private prototype_ `virtual FEdGraphPinType GetPinType() const override;`
- L50 _private prototype_ `virtual bool CanRemoveExecutionPin(UEdGraphPin* TargetPin) const override;`
- L54 _protected prototype_ `virtual void CreateCasePins() override;`
- L55 _protected prototype_ `virtual void CreateSelectionPin() override;`
- L56 _protected prototype_ `virtual void RemovePin(UEdGraphPin* TargetPin) override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_SwitchName.h` (Public)


#### class `UK2Node_SwitchName`  
`class UK2Node_SwitchName : public UK2Node_Switch`  
_L23-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Switch`
- L28 _private member_ `TArray<FName> PinNames;` — `UPROPERTY(EditAnywhere, Category=PinOptions)`
- L31 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L35 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L36 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L37 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L41 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L45 _private prototype_ `virtual void AddPinToSwitchNode() override;` — UK2Node_Switch Interface
- L46 _private prototype_ `virtual FName GetUniquePinName() override;`
- L47 _private prototype_ `virtual FEdGraphPinType GetPinType() const override;`
- L50 _private prototype_ `virtual FName GetPinNameGivenIndex(int32 Index) const override;`
- L53 _protected prototype_ `virtual void CreateSelectionPin() override;`
- L54 _protected prototype_ `virtual void CreateCasePins() override;`
- L55 _protected prototype_ `virtual void RemovePin(UEdGraphPin* TargetPin) override;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_SwitchString.h` (Public)


#### class `UK2Node_SwitchString`  
`class UK2Node_SwitchString : public UK2Node_Switch`  
_L23-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Switch`
- L28 _private member_ `TArray<FName> PinNames;` — `UPROPERTY(EditAnywhere, Category=PinOptions)`
- L31 _private member_ `uint32 bIsCaseSensitive : 1;` — `UPROPERTY(EditAnywhere, Category=PinOptions)`
- L34 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L38 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L39 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L40 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L41 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L45 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L49 _private prototype_ `virtual void AddPinToSwitchNode() override;` — UK2Node_Switch Interface
- L50 _private prototype_ `virtual FName GetUniquePinName() override;`
- L51 _private prototype_ `virtual FEdGraphPinType GetPinType() const override;`
- L54 _private prototype_ `virtual FName GetPinNameGivenIndex(int32 Index) const override;`
- L57 _protected prototype_ `virtual void CreateSelectionPin() override;`
- L58 _protected prototype_ `virtual void CreateCasePins() override;`
- L59 _protected prototype_ `virtual void RemovePin(UEdGraphPin* TargetPin) override;`
- L62 _protected prototype_ `void SetupCaseSensitivityFunction();` — Sets the nodes function to call based on case sensitivity

### `Source/Editor/BlueprintGraph/Classes/K2Node_TemporaryVariable.h` (Public)


#### class `UK2Node_TemporaryVariable`  
`class UK2Node_TemporaryVariable : public UK2Node`  
_L25-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L30 _private member_ `struct FEdGraphPinType VariableType;` — `UPROPERTY()`
- L34 _private member_ `bool bIsPersistent;` — `UPROPERTY()` — Whether or not this variable should be flagged with CPF_SaveGame, and inherit its name from the GUID of the macro that that gave rise to it
- L37 _private prototype_ `UEdGraphPin* GetVariablePin();` — get variable pin
- L40 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L41 _private prototype_ `virtual FText GetTooltipText() const override;`
- L42 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L43 _private prototype_ `virtual FString GetDescriptiveCompiledName() const override;`
- L44 _private prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* TargetGraph) const override;`
- L45 _private prototype_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;`
- L49 _private prototype_ `virtual bool IsNodePure() const override;`
- L50 _private prototype_ `virtual void PostReconstructNode() override;`
- L51 _private prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L52 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L53 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L54 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L55 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L60 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L61 _private member_ `FNodeTextCache CachedNodeTitle;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_Timeline.h` (Public)


#### class `UK2Node_Timeline`  
`class UK2Node_Timeline : public UK2Node`  
_L33-131_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L39 _private member_ `FName TimelineName;` — `UPROPERTY()` — The name of the timeline. Used to name ONLY the member variable (Component). To obtain the name of timeline template use UTimelineTemplate::TimelineVariableNameToTemplateName
- L43 _private member_ `uint32 bAutoPlay:1;` — `UPROPERTY(Transient)` — If the timeline is set to autoplay
- L47 _private member_ `FGuid TimelineGuid;` — `UPROPERTY()` — Unique ID for the template we use, required to indentify the timeline after a paste
- L51 _private member_ `uint32 bLoop:1;` — `UPROPERTY(Transient)` — If the timeline is set to loop
- L55 _private member_ `uint32 bReplicated:1;` — `UPROPERTY(Transient)` — If the timeline is set to replicate
- L59 _private member_ `uint32 bIgnoreTimeDilation : 1;` — `UPROPERTY(Transient)` — If the timeline should ignore global time dilation
- L62 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L63 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L64 _private prototype_ `virtual void DestroyNode() override;`
- L65 _private prototype_ `virtual void PostPasteNode() override;`
- L66 _private prototype_ `virtual void PrepareForCopying() override;`
- L67 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L68 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L69 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L70 _private prototype_ `virtual void FindDiffs(class UEdGraphNode* OtherNode, struct FDiffResults& Results ) override;`
- L71 _private prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L72 _private prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L73 _private prototype_ `virtual FText GetTooltipText() const override;`
- L74 _private prototype_ `virtual FString GetDocumentationExcerptName() const override;`
- L75 _private prototype_ `virtual FName GetCornerIcon() const override;`
- L76 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L77 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L78 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L82 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L83 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L84 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L85 _private prototype_ `virtual void GetNodeAttributes( TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes ) const override;`
- L86 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L87 _private prototype_ `virtual FText GetToolTipHeading() const override;`
- L91 _private prototype_ `UEdGraphPin* GetPlayPin() const;` — Get the 'play' input pin
- L94 _private prototype_ `UEdGraphPin* GetPlayFromStartPin() const;` — Get the 'play from start' input pin
- L97 _private prototype_ `UEdGraphPin* GetStopPin() const;` — Get the 'stop' input pin
- L100 _private prototype_ `UEdGraphPin* GetUpdatePin() const;` — Get the 'update' output pin
- L103 _private prototype_ `UEdGraphPin* GetReversePin() const;` — Get the 'reverse' input pin
- L106 _private prototype_ `UEdGraphPin* GetReverseFromEndPin() const;` — Get the 'reverse from end' input pin
- L109 _private prototype_ `UEdGraphPin* GetFinishedPin() const;` — Get the 'finished' output pin
- L112 _private prototype_ `UEdGraphPin* GetNewTimePin() const;` — Get the 'newtime' input pin
- L115 _private prototype_ `UEdGraphPin* GetSetNewTimePin() const;` — Get the 'setnewtime' input pin
- L118 _private prototype_ `UEdGraphPin* GetDirectionPin() const;` — Get the 'Direction' output pin
- L121 _private prototype_ `UEdGraphPin* GetTrackPin(const FName TrackName) const;` — Get the 'Direction' output pin
- L127 _private prototype_ `bool RenameTimeline(const FString& NewName);` — Try to rename the timeline @param NewName	The newname for the timeline @return bool	true if node was successfully renamed, false otherwise
- L130 _private prototype_ `void ExpandForPin(UEdGraphPin* TimelinePin, const FName PropertyName, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph);`

### `Source/Editor/BlueprintGraph/Classes/K2Node_Tunnel.h` (Public)


#### class `UK2Node_Tunnel`  
`class UK2Node_Tunnel : public UK2Node_EditablePinBase`  
_L33-116_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_EditablePinBase`
- L42 _private member_ `TObjectPtr<UK2Node_Tunnel> OutputSourceNode;` — `UPROPERTY()` — The output pins of this tunnel node came from the input pins of OutputSourceNode
- L46 _private member_ `TObjectPtr<UK2Node_Tunnel> InputSinkNode;` — `UPROPERTY()` — The input pins of this tunnel go to the output pins of InputSinkNode
- L50 _private member_ `uint32 bCanHaveInputs:1;` — `UPROPERTY()` — Whether this node is allowed to have inputs
- L54 _private member_ `uint32 bCanHaveOutputs:1;` — `UPROPERTY()` — Whether this node is allowed to have outputs
- L59 _private member_ `struct FKismetUserDeclaredFunctionMetadata MetaData;` — `UPROPERTY()` — The metadata for the function/subgraph associated with this tunnel node; it's only editable and used on the tunnel entry node inside the subgraph or macro.  This structure is ignored on any other tunnel nodes.
- L62 _private prototype_ `virtual void DestroyNode() override;`
- L63 _private prototype_ `virtual void PostPasteNode() override;`
- L64 _private prototype_ `virtual FText GetTooltipText() const override;`
- L65 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L66 _private prototype_ `virtual bool CanUserDeleteNode() const override;`
- L67 _private prototype_ `virtual bool CanDuplicateNode() const override;`
- L68 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L69 _private prototype_ `virtual FName CreateUniquePinName(FName SourcePinName) const override;`
- L70 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L71 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* InGraph) const override;`
- L75 _private prototype_ `virtual bool IsNodeSafeToIgnore() const override;`
- L76 _private prototype_ `virtual bool DrawNodeAsEntry() const override;`
- L77 _private prototype_ `virtual bool DrawNodeAsExit() const override;`
- L78 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L79 _private prototype_ `virtual void ClearCachedBlueprintData(UBlueprint* Blueprint) override;`
- L80 _private prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L81 _private prototype_ `virtual void FixupPinStringDataReferences(FArchive* SavingArchive) override;`
- L85 _private prototype_ `virtual UEdGraphPin* CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> NewPinInfo) override;`
- L86 _private prototype_ `virtual bool CanModifyExecutionWires() override;`
- L87 _private prototype_ `virtual ERenamePinResult RenameUserDefinedPinImpl(const FName OldName, const FName NewName, bool bTest = false) override;`
- L88 _private function_ `virtual bool CanUseRefParams() const override`
- L89 _private prototype_ `virtual bool CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage) override;`
- L90 _private prototype_ `virtual bool ModifyUserDefinedPinDefaultValue(TSharedPtr<FUserPinInfo> PinInfo, const FString& NewDefaultValue) override;`
- L99 _protected function_ `virtual void PostFixupAllWildcardPins(bool bInAllWildcardPinsUnlinked)` — Handles any work needed to be done after fixing up all wildcard pins during reconstruction @param bInAllWildcardPinsUnlinked	TRUE if all wildcard pins were unlinked
- L102 _protected prototype_ `static bool ShouldDoSmartWildcardInference();` — Feature flag for 'smart' wildcard inference which allows for multiple types to be inferred.
- L105 _protected prototype_ `void CacheWildcardPins();` — Utility function that subclasses must call after allocating their default pins
- L108 _protected member_ `TArray<UEdGraphPin*> WildcardPins;` — Cache of the pins that were created as wildcards
- L112 _public prototype_ `virtual UK2Node_Tunnel* GetInputSink() const;` — The input pins of this tunnel go to the output pins of InputSinkNode (can be NULL).
- L115 _public prototype_ `virtual UK2Node_Tunnel* GetOutputSource() const;` — The output pins of this tunnel node came from the input pins of OutputSourceNode (can be NULL).

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_TunnelBoundary.h` (Public)


#### enum `ETunnelBoundaryType`  
`enum class ETunnelBoundaryType : uint8`  
_L24-30_
- reflection: `UENUM()`
- L26 _public enumerator_ `Unknown = 0`
- L27 _public enumerator_ `EntrySite`
- L28 _public enumerator_ `InputSite`
- L29 _public enumerator_ `OutputSite`

#### class `UK2Node_TunnelBoundary`  
`class UK2Node_TunnelBoundary : public UK2Node`  
_L33-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L39 _private member_ `FName BaseName;` — `UPROPERTY(Transient)` — Base Name
- L43 _private member_ `ETunnelBoundaryType TunnelBoundaryType;` — `UPROPERTY(Transient)` — Node Type
- L48 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L52 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override;`
- L53 _public function_ `virtual int32 GetNodeRefreshPriority() const override`
- L57 _public function_ `ETunnelBoundaryType GetTunnelBoundaryType() const` — Returns the type of tunnel boundary this node is
- L60 _public prototype_ `void SetNodeAttributes(const UK2Node_Tunnel* SourceNode);` — Set node attributes based on the tunnel source node

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_Variable.h` (Public)


#### enum `ESelfContextInfo::Type`  
`enum Type : int`  
_L44-48_
- L46 _public enumerator_ `Unspecified`
- L47 _public enumerator_ `NotSelfContext`

#### class `UK2Node_Variable`  
`class UK2Node_Variable : public UK2Node`  
_L52-229_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UK2Node`
- L58 _private member_ `FMemberReference VariableReference;` — `UPROPERTY(meta=(BlueprintSearchable="true", BlueprintSearchableHiddenExplicit="true", BlueprintSearchableFormatVersion="FIB_VER_VARIABLE_REFERENCE"))` — Reference to variable we want to set/get
- L61 _private member_ `TEnumAsByte<ESelfContextInfo::Type> SelfContextInfo;` — `UPROPERTY()`
- L66 _protected member_ `TSubclassOf<class UObject> VariableSourceClass_DEPRECATED;` — `UPROPERTY()` — Class that this variable is defined in. Should be NULL if bSelfContext is true.
- L70 _protected member_ `FName VariableName_DEPRECATED;` — `UPROPERTY()` — Name of variable
- L74 _protected member_ `uint32 bSelfContext_DEPRECATED:1;` — `UPROPERTY()` — Whether or not this should be a "self" context
- L80 _protected prototype_ `bool RemapRestrictedLinkReference(FName OldVariableName, FName NewVariableName, const UClass* MatchInVariableClass, const UClass* RemapIfLinkedToClass, bool bLogWarning);` — Remap a reference from one variable to another, if this variable is of class type 'MatchInVariableClass', and if linked to anything that is a child of 'RemapIfLinkedToClass'. Only intended for versioned fixup where redirects can't be applied.
- L84 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L88 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L89 _public prototype_ `virtual FString GetFindReferenceSearchString_Impl(EGetFindReferenceSearchStringFlags InFlags) const override;`
- L90 _public prototype_ `virtual void ReconstructNode() override;`
- L91 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L92 _public prototype_ `virtual FString GetDocumentationExcerptName() const override;`
- L93 _public prototype_ `virtual FName GetCornerIcon() const override;`
- L94 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L95 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L96 _public prototype_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;`
- L97 _public prototype_ `virtual void PostPasteNode() override;`
- L98 _public prototype_ `virtual bool HasDeprecatedReference() const override;`
- L99 _public prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType DeprecationType) const override;`
- L100 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L101 _public prototype_ `virtual bool CanJumpToDefinition() const override;`
- L102 _public prototype_ `virtual void JumpToDefinition() const override;`
- L103 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L104 _public prototype_ `virtual FString GetPinMetaData(FName InPinName, FName InKey) override;`
- L105 _public prototype_ `virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;`
- L109 _public function_ `virtual bool DrawNodeAsVariable() const override`
- L110 _public prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L111 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L112 _public prototype_ `virtual FText GetToolTipHeading() const override;`
- L113 _public prototype_ `virtual void GetNodeAttributes(TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes) const override;`
- L114 _public prototype_ `virtual void HandleVariableRenamed(UBlueprint* InBlueprint, UClass* InVariableClass, UEdGraph* InGraph, const FName& InOldVarName, const FName& InNewVarName) override;`
- L115 _public prototype_ `virtual void ReplaceReferences(UBlueprint* InBlueprint, UBlueprint* InReplacementBlueprint, const FMemberReference& InSource, const FMemberReference& InReplacement) override;`
- L116 _public prototype_ `virtual bool ReferencesVariable(const FName& InVarName, const UStruct* InScope) const override;`
- L120 _public prototype_ `void SetFromProperty(const FProperty* Property, bool bSelfContext, UClass* OwnerClass);` — Set up this variable node from the supplied FProperty
- L123 _public function_ `FString GetVarNameString() const` — Util to get variable name as a string
- L128 _public function_ `FText GetVarNameText() const`
- L135 _public function_ `FName GetVarName() const` — Util to get variable name
- L148 _public prototype_ `bool CreatePinForVariable(EEdGraphPinDirection Direction, FName InPinName = NAME_None);` — Creates a reader or writer pin for a variable. @param	Direction	  	The direction of the variable access. @param	InPinName		Optional pin name, will default to the variable name if not included. @return	true if it succeeds, false if it fails.
- L151 _public prototype_ `void CreatePinForSelf();` — Creates 'self' pin
- L162 _public prototype_ `bool RecreatePinForVariable(EEdGraphPinDirection Direction, TArray<UEdGraphPin*>& OldPins, FName InPinName = NAME_None);` — Creates a reader or writer pin for a variable from an old pin. @param	Direction	  	The direction of the variable access. @param	OldPins			Old pins. @param	InPinName		Optional pin name, will default to the variable name if not included. @return	true if it succeeds, false if it fails.
- L165 _public prototype_ `UClass* GetVariableSourceClass() const;` — Get the class to look for this variable in
- L168 _public prototype_ `FProperty* GetPropertyForVariable() const;` — Get the FProperty for this variable node
- L169 _public prototype_ `FProperty* GetPropertyForVariableFromSkeleton() const;`
- L172 _public prototype_ `static bool DoesRenamedVariableMatch(FName OldVariableName, FName NewVariableName, UStruct* StructType);` — Returns true if the variable names match, this looks for redirectors
- L178 _private prototype_ `FProperty* GetPropertyForVariable_Internal(UClass* OwningClass) const;` — Gets the property for the variable on the owning class or on the owning class's sparse class data structure.
- L183 _public prototype_ `UEdGraphPin* GetValuePin() const;` — Accessor for the value output pin of the node
- L186 _public prototype_ `void CheckForErrors(const class UEdGraphSchema_K2* Schema, class FCompilerResultsLog& MessageLog);` — Validates there are no errors in the node
- L197 _public prototype_ `static FSlateIcon GetVariableIconAndColor(const UStruct* VarScope, FName VarName, FLinearColor& IconColorOut);` — Utility method intended to serve as a choke point for various slate widgets to grab an icon from (for a specified variable). @param  VarScope		The scope that owns the variable in question. @param  VarName		The name of the variable you're querying for. @param  IconColorOut	A color out, further discerning the variable's type. @return A icon representing the specified variable's type.
- L207 _public prototype_ `static FSlateIcon GetVarIconFromPinType(const FEdGraphPinType& InPinType, FLinearColor& IconColorOut);` — Utility method intended to serve as a choke point for various slate widgets to grab an icon from (for a specified variable pin type). @param  InPinType	The pin type of the variable in question. @param  IconColorOut	A color out, further discerning the variable's type. @return A icon representing the specified variable's type.
- L215 _protected prototype_ `FBPVariableDescription const* GetBlueprintVarDescription() const;` — @return
- L222 _protected prototype_ `const UActorComponent* GetActorComponent(const FProperty* VariableProperty) const;` — Utility function to retrieve actor component for variable property. @return Found UActorComponent for the FProperty, else nullptr
- L225 _protected prototype_ `void SuppressDeprecationWarning() const;` — Adds the variable reference to the suppressed deprecation warnings list
- L228 _protected prototype_ `static bool FunctionParameterExists(const UEdGraph* InFunctionGraph, const FName InParameterName);` — Returns whether a Function Graph contains a parameter with the given name

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API BLUEPRINTGRAPH_API`
- L42 _namespace_ `namespace ESelfContextInfo`

### `Source/Editor/BlueprintGraph/Classes/K2Node_VariableGet.h` (Public)


#### enum `EGetNodeVariation`  
`enum class EGetNodeVariation`  
_L31-36_
- reflection: `UENUM()`
- L33 _public enumerator_ `Pure`
- L34 _public enumerator_ `ValidatedObject`
- L35 _public enumerator_ `Branch`

#### class `UK2Node_VariableGet`  
`class UK2Node_VariableGet : public UK2Node_Variable`  
_L39-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Variable`
- L46 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L50 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L51 _public prototype_ `virtual FText GetTooltipText() const override;`
- L52 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L53 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L54 _public function_ `virtual bool IncludeParentNodeContextMenu() const override`
- L55 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L59 _public function_ `virtual bool IsNodePure() const override`
- L60 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L61 _public function_ `virtual bool ShouldShowNodeProperties() const override`
- L62 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L63 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L66 _public prototype_ `static FText GetPropertyTooltip(const FProperty* VariableProperty);`
- L67 _public prototype_ `static FText GetBlueprintVarTooltip(const FBPVariableDescription& VarDesc);`
- L75 _public prototype_ `void SetPurity(bool bNewPurity);` — Will change the node's purity, and reallocate pins accordingly (adding/ removing exec pins). @param  bNewPurity  The new value for bNewPurity.
- L80 _private prototype_ `void CreateImpurePins(TArray<UEdGraphPin*>* InOldPinsPtr);` — Adds pins required for the node to function in a impure manner
- L83 _private prototype_ `void TogglePurity(EGetNodeVariation BoundVariation);` — Flips the node's purity (adding/removing exec pins as needed).
- L86 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L87 _private member_ `FNodeTextCache CachedNodeTitle;`
- L90 _private member_ `bool bIsPureGet_DEPRECATED = true;` — `UPROPERTY()`
- L93 _private member_ `EGetNodeVariation CurrentVariation;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Classes/K2Node_VariableSet.h` (Public)


#### class `UK2Node_VariableSet`  
`class UK2Node_VariableSet : public UK2Node_Variable`  
_L28-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Variable`
- L33 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L34 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L35 _private prototype_ `virtual FText GetTooltipText() const override;`
- L36 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L37 _private function_ `virtual bool ShouldOverridePinNames() const override`
- L38 _private prototype_ `virtual FText GetPinNameOverride(const UEdGraphPin& Pin) const override;`
- L39 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L43 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L44 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L45 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L49 _private prototype_ `FName GetVariableOutputPinName() const;` — Retrieves the output pin name for the node
- L51 _private prototype_ `bool HasLocalRepNotify() const;`
- L52 _private prototype_ `FName GetRepNotifyName() const;`
- L53 _private prototype_ `bool ShouldFlushDormancyOnSet() const;`
- L54 _private prototype_ `bool IsNetProperty() const;`
- L55 _private prototype_ `bool IsFieldNotifyProperty() const;`
- L56 _private prototype_ `bool HasFieldNotificationBroadcast() const;`
- L58 _private prototype_ `static FText GetPropertyTooltip(FProperty const* VariableProperty);`
- L59 _private prototype_ `static FText GetBlueprintVarTooltip(FBPVariableDescription const& VarDesc);`
- L63 _private prototype_ `void CreateOutputPinTooltip();` — Sets up the tooltip for the output pin
- L67 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L68 _private member_ `FNodeTextCache CachedNodeTitle;`

### `Source/Editor/BlueprintGraph/Classes/K2Node_VariableSetRef.h` (Public)


#### class `UK2Node_VariableSetRef`  
`class UK2Node_VariableSetRef : public UK2Node`  
_L25-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L30 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L31 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L32 _private prototype_ `virtual FText GetTooltipText() const override;`
- L33 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L37 _private prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L38 _private prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L39 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L40 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L41 _private function_ `virtual int32 GetNodeRefreshPriority() const override`
- L42 _private prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L50 _private prototype_ `void CoerceTypeFromPin(const UEdGraphPin* Pin);` — Changes the type of variable set by this node, based on the specified pin @param Pin				The pin to gather type information from.
- L53 _private prototype_ `UEdGraphPin* GetTargetPin() const;` — Returns the pin that specifies which by-ref variable to set
- L56 _private prototype_ `UEdGraphPin* GetValuePin() const;` — Returns the pin that specifies the value to set
- L60 _private member_ `FNodeTextCache CachedNodeTitle;` — Constructing FText strings can be costly, so we cache the node's title

### `Source/Editor/BlueprintGraph/Classes/NodeDependingOnEnumInterface.h` (Public)


#### class `UNodeDependingOnEnumInterface`  
`class UNodeDependingOnEnumInterface : public UInterface`  
_L17-20_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `INodeDependingOnEnumInterface`  
`class INodeDependingOnEnumInterface`  
_L22-31_
- L26 _private prototype_ `virtual class UEnum* GetEnum() const PURE_VIRTUAL(INodeDependingOnEnumInterface::GetEnum,return NULL;);`
- L28 _private prototype_ `virtual void ReloadEnum(class UEnum*) PURE_VIRTUAL(INodeDependingOnEnumInterface::ReloadEnum, return;);`
- L30 _private function_ `virtual bool ShouldBeReconstructedAfterEnumChanged() const`

### `Source/Editor/BlueprintGraph/Private/BasicTokenParser.h` (Private)


#### class `FBasicToken`  
`class FBasicToken`  
_L22-129_
- desc: Information regarding a token that was parsed from some expression string (type, value, etc.).
- L25 _public prototype_ `FBasicToken();` — invokes InitToken()
- L33 _public prototype_ `void InitToken(EPropertyType InConstType = CPT_None);` — Resets this token, clearing any details that were previously set (allows you to init the token to some predefined value type). @param  InConstType	Optional param that lets you init this to some known value type.
- L40 _public prototype_ `void Clone(const FBasicToken& Other);` — Copies the properties from another token into this one. @param  Other		The token to copy properties from.
- L47 _public prototype_ `bool Matches(const FName& Name) const;` — Determines if this token matches the specified name.
- L50 _public prototype_ `bool Matches(const TCHAR* Str, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase) const;` — Determines if this token matches the specified string.
- L53 _public prototype_ `bool StartsWith(const TCHAR* Str, bool bCaseSensitive = false) const;` — Determines if this token has the specified string as a prefix.
- L56 _public prototype_ `bool IsBool() const;` — Determines if this token has a boolean ConstantType.
- L62 _public prototype_ `void SetConstInt(int32 InInt);`
- L63 _public prototype_ `void SetConstBool(bool InBool);`
- L64 _public prototype_ `void SetConstDouble(double InDouble);`
- L65 _public prototype_ `void SetConstName(FName InName);`
- L66 _public prototype_ `void SetConstString(TCHAR* InString, int32 MaxLength=MAX_STRING_CONST_SIZE);`
- L67 _public prototype_ `void SetGuid(TCHAR* InString, int32 MaxLength=MAX_STRING_CONST_SIZE);`
- L80 _public prototype_ `bool GetConstInt(int32& ValOut) const;` — Retrieves an int value from this token (if it is a constant int/byte/double/etc. type). @param  ValOut	Will hold the integer value if this is successfully. @return True if this represents a constant that can be converted to an integer, otherwise false (ValOut is invalid).
- L89 _public prototype_ `FString GetConstantValue() const;` — If this represents a constant value, then this returns a string representing the value of said constant (formated according to the type). @return A default error string if this is not a constant (or an unsupported type), else a string containing the constant value.
- L102 _public member_ `ETokenType TokenType;` — Type of this token.
- L105 _public member_ `FName TokenName;` — Name of this token.
- L108 _public member_ `int32 StartPos;` — Starting position in expression stream where this token came from.
- L111 _public member_ `int32 StartLine;` — Starting line in the expression.
- L114 _public member_ `TCHAR Identifier[NAME_SIZE];` — Always valid.
- L117 _public member_ `EPropertyType ConstantType;` — Only valid when TokenType is TOKEN_Const

#### enum `FBasicToken::ETokenType`  
`enum ETokenType`  
_L92-100_
- L94 _public enumerator_ `TOKEN_None = 0x00` — No token.
- L95 _public enumerator_ `TOKEN_Identifier = 0x01` — Alphanumeric identifier.
- L96 _public enumerator_ `TOKEN_Symbol = 0x02` — Symbol.
- L97 _public enumerator_ `TOKEN_Const = 0x03` — A constant.
- L98 _public enumerator_ `TOKEN_Guid = 0x04` — A variable guid
- L99 _public enumerator_ `TOKEN_Max = 0x0D`

#### union `FBasicToken::(anonymous)`  
``  
_L121-128_

#### class `FBasicTokenParser`  
`class FBasicTokenParser`  
_L140-412_
- desc: Provides a base set of expression parsing functionality for sub-classes to utilize when tokenizing a TCHAR stream (discerns operators from literals/ variables, strips out comments, etc.).
- L147 _protected function_ `FBasicTokenParser()` — FBasicTokenParser is conceptually abstract, and should only be instantiated through a subclass.
- L157 _protected prototype_ `void ResetParser(const TCHAR* SourceBuffer, int32 StartingLineNumber = 1);` — Sets up this to start parsing a new expression string and resets any state lingering from the previous one. @param  SourceBuffer			The expression string you wish to parse next. @param  StartingLineNumber	The base line number to start counting from as this parses.
- L162 _protected prototype_ `void ClearCachedComment();` — Clears out the most recent parsed comment.
- L180 _protected prototype_ `bool GetToken(FBasicToken& Token, bool bNoConsts = false);` — Gets the next token from the input stream, advancing the variables which keep track of the current input position and line. @param  Token [out]	Receives the value of the parsed text; if Token is pre-initialized, special logic is performed to attempt to evaluated Token in the context of that type. Useful for distinguishing between ambiguous symbols like enum tags. @param  bNoConsts	Specify true to indicate that tokens representing literal const values are not allowed. @return True if a token was successfully processed, false otherwise.
- L191 _protected prototype_ `bool GetRawToken(FBasicToken& Token, TCHAR StopChar = TCHAR('\n'));` — Put all text from the current position up to either EOL or the StopToken into Token. Advances the compiler's current position. @param  Token [out]	Will contain the text that was parsed. @param  StopChar		Stop processing when this character is reached. @return True if a token was successfully processed, false otherwise.
- L199 _protected prototype_ `bool GetRawTokenRespectingQuotes(FBasicToken& Token, TCHAR StopChar = TCHAR('\n'));` — Doesn't quit if StopChar is found inside a double-quoted string, but does NOT support quote escapes. @return True if a token was successfully processed, false otherwise.
- L206 _protected prototype_ `bool GetIdentifier(FBasicToken& Token, bool bNoConsts = false);` — Parse out an identifier from the expression stream. @return True if a token was successfully processed, false otherwise.
- L213 _protected prototype_ `bool GetSymbol(FBasicToken& Token);` — Parse out a symbol from the expression stream. @return True if a token was successfully processed, false otherwise.
- L220 _protected prototype_ `bool GetConstInt(int32& Result, const TCHAR* ErrorContext = NULL);` — Parse out an int constant from the expression stream. @return True if a int was successfully processed, false otherwise.
- L226 _protected prototype_ `void UngetToken(FBasicToken& Token);` — Rolls back the line number and moves the parsing pointer back to where the specified token started.
- L236 _protected prototype_ `TCHAR PeekChar();` — Look at a single character from the input stream and return it, or 0=end. Has no effect on the input stream.
- L241 _protected prototype_ `TCHAR GetChar(bool bLiteral = false);` — Get a single character from the input stream and return it, or 0=end.
- L246 _protected prototype_ `TCHAR GetLeadingChar();` — Skip past all spaces, tabs, and comments in the input stream.
- L251 _protected prototype_ `void UngetChar();` — Unget the previous character retrieved with GetChar().
- L265 _protected prototype_ `bool MatchIdentifier(FName Match);` — Determines if the next token in the stream is an identifier that matches the specified FName  (and consumes it if it does). This is used primarily for checking for required symbols during parsing. @param  Match	The name you wish to check for. @return True if a match was consumed, false otherwise.
- L271 _protected prototype_ `bool MatchIdentifier(const TCHAR* Match);` — Determines if the next token in the stream is an identifier that matches the specified string (and consumes it if it does).
- L277 _protected prototype_ `bool PeekIdentifier(FName Match);` — Determines if the next token in the stream is an identifier that matches the specified name (does NOT consume it).
- L283 _protected prototype_ `bool PeekIdentifier(const TCHAR* Match);` — Determines if the next token in the stream is an identifier that matches the specified string (does NOT consume it).
- L289 _protected prototype_ `bool MatchSymbol(const TCHAR* Match);` — Determines if the next token in the stream is a symbol that matches the specified string (and consumes it if it does).
- L295 _protected prototype_ `bool PeekSymbol(const TCHAR* Match);` — Determines if the next token in the stream is a symbol that matches the specified string (does NOT consume it).
- L305 _protected prototype_ `bool RequireIdentifier(FName Match, const TCHAR* ErrorContext);` — Ensures that the next token in the stream is an identifier that matches the specified name (and errors out if it isn't).
- L311 _protected prototype_ `bool RequireIdentifier(const TCHAR* Match, const TCHAR* ErrorContext);` — Ensures that the next token in the stream is an identifier that matches the specified string (and errors out if it isn't).
- L317 _protected prototype_ `bool RequireSymbol(const TCHAR* Match, const TCHAR* ErrorContext);` — Ensures that the next token in the stream is a symbol that matches the specified string (and errors out if it isn't).
- L323 _protected prototype_ `bool RequireSemi();` — Ensures that the next token in the stream is a semi-colon character (and errors out if it isn't).
- L333 _public prototype_ `bool IsValid() const;` — Checks to see if an error has been caught by the internal error state.
- L366 _public prototype_ `const FErrorState& GetErrorState() const;` — Retrieves the parser's internal error state (so that users can interpret what might have gone wrong while tokenizing).
- L381 _protected prototype_ `void SetError(TEnumAsByte<FErrorState::EErrorType> ErrorCode, FText Description, bool bLogFatal = false);` — Takes the provided error and throws it (if the ErrorCode isn't FErrorState::NoError). @param  ErrorCode	Should match up with FErrorState::EErrorType, but is meant to be extensible by subclasses (so it could be out of that range). @param  Description	A detailed localized string, describing what exactly went wrong (meant to be user facing). @param  bLogFatal	Optional param where you can make a fatal log along with the thrown error (in case error handling is turned off).
- L386 _protected prototype_ `void ClearErrorState();` — Resets the internal error state, such that the parser can continue on.
- L390 _protected member_ `const TCHAR* Input;` — Input text
- L393 _protected member_ `int32 InputLen;` — Length of input text
- L396 _protected member_ `int32 InputPos;` — Current position in text
- L399 _protected member_ `int32 InputLine;` — Current line in text
- L402 _protected member_ `int32 PrevPos;` — Position previous to last GetChar() call
- L405 _protected member_ `int32 PrevLine;` — Line previous to last GetChar() call.
- L408 _protected member_ `FString PrevComment;` — Previous comment parsed by GetChar() call.
- L411 _protected member_ `FErrorState CurrentError;` — Keeps track of the last error to occur

#### struct `FBasicTokenParser::FErrorState`  
`struct FErrorState`  
_L336-360_
- desc: A struct for easily describing a specific error that occurred while parsing
- L347 _public function_ `FErrorState() : State(NoError)`
- L352 _public prototype_ `void Throw(bool bLogFatal) const;` — Will take the current error and logs it, optionally fatally
- L356 _public member_ `TEnumAsByte<EErrorType> State;` — Should match up with EErrorType, but is extensible by subclasses (comes from a subclass if >= SubClassErrorStart)
- L359 _public member_ `FText Description;` — A detailed localized string, describing what exactly went wrong (meant to be user facing)

#### enum `FBasicTokenParser::FErrorState::EErrorType`  
`enum EErrorType`  
_L338-345_
- L340 _public enumerator_ `NoError`
- L341 _public enumerator_ `ParseError` — generic error that occurred while tokenizing the expression
- L342 _public enumerator_ `RequireError` — explicit error that was invoked through a call to one of the Require methods
- L344 _public enumerator_ `SubClassErrorStart` — the starting value for a subclass's

#### Free symbols / members of external scopes

- L122 _member_ `uint8 Byte;` (scope `FBasicToken::__anone920de12010a`) — If CPT_Byte.
- L123 _member_ `int32 Int;` (scope `FBasicToken::__anone920de12010a`) — If CPT_Int.
- L124 _member_ `bool NativeBool;` (scope `FBasicToken::__anone920de12010a`) — If CPT_Bool
- L125 _member_ `double Double;` (scope `FBasicToken::__anone920de12010a`) — If CPT_Double.
- L126 _member_ `uint8 NameBytes[sizeof(FScriptName)];` (scope `FBasicToken::__anone920de12010a`) — If CPT_Name.
- L127 _member_ `TCHAR String[MAX_STRING_CONST_SIZE];` (scope `FBasicToken::__anone920de12010a`) — If CPT_String

### `Source/Editor/BlueprintGraph/Private/BlueprintActionFilterResultCache.h` (Private)


#### struct `FActionFilterCacheKey`  
`struct FActionFilterCacheKey`  
_L18-23_
- desc: Wrapper for a hashed action key
- L20 _public member_ `uint32 KeyHash;`
- L22 _public prototype_ `explicit FActionFilterCacheKey(const FBlueprintActionInfo& InAction);`

#### class `FActionFilterCacheNode`  
`class FActionFilterCacheNode : public TSharedFromThis<FActionFilterCacheNode>`  
_L38-163_
- inherits: `TSharedFromThis<FActionFilterCacheNode>`
- desc: This class is used by FActionFilterCache to create a tree structure that is used to store cached filter results in such a way that they can be looked up using all the relevant context data that determines how items are filtered. each node has a type agnostic key so that we can easily change how the cache is keyed in the future. (See FActionFilterCache::GetIsFilteredByThisCache)
- L45 _public typedef_ `using FWeakNode = TWeakPtr<FActionFilterCacheNode>;` — Branching nodes
- L47 _public typedef_ `template<typename TKeyType> using TWeakKeyNode = TWeakPtr<TActionFilterCacheKeyNode<TKeyType>>;`
- L49 _public typedef_ `template<typename TKeyType> using TWeakLeaf = TWeakPtr<TActionFilterCacheLeaf<TKeyType>>;`
- L52 _public typedef_ `using FSharedNode = TSharedPtr<FActionFilterCacheNode>;` — Leaf nodes
- L54 _public typedef_ `template<typename TKeyType> using TSharedKeyNode = TSharedPtr<TActionFilterCacheKeyNode<TKeyType>>;`
- L56 _public typedef_ `template<typename TKeyType> using TSharedLeaf = TSharedPtr<TActionFilterCacheLeaf<TKeyType>>;`
- L58 _public prototype_ `FActionFilterCacheNode() = default;`
- L59 _public prototype_ `virtual ~FActionFilterCacheNode() = default;`
- L63 _public function_ `template<typename TKeyType> TSharedKeyNode<TKeyType> Find(const TKeyType& Key) const` — Looks up a child of this node by key. Note: the key is not hashed. This is O(n)
- L80 _public function_ `template<typename TKeyType> TSharedKeyNode<TKeyType> FindOrCacheChildNode(const TKeyType& Key, const FString& InDebugName = FString(), TDelegate<bool(const TKeyType&, const TKeyType&)> Comparison = nullptr, bool* OutFoundWithoutCaching = nullptr)` — Looks up a child of this node by key and creates one if one doesnt exist. The node that is created will be a TActionFilterCacheKeyNode. Use FindOrCacheChildLeaf if you need it to be a TActionFilterCacheLeaf Note: the key is not hashed. This is O(n)
- L104 _public function_ `template<typename TKeyType> TSharedLeaf<TKeyType> FindOrCacheChildLeaf(const TKeyType& Key, const FString& InDebugName = FString(), TDelegate<bool(const TKeyType&, const TKeyType&)> Comparison = nullptr, bool* OutFoundWithoutCaching = nullptr)` — Looks up a child of this node by key and creates one if one doesnt exist. The node that is created will be a TActionFilterCacheLeaf. Use FindOrCacheChildNode if you need it to be a TActionFilterCacheKeyNode Note: the key is not hashed. This is O(n)
- L126 _public function_ `virtual uint32 GetLeafAccessCount() const` — get the number of times this leaf has been accessed Warning: throws and error if this isn't a TActionFilterCacheLeaf
- L134 _public function_ `virtual void DecrementLeafAccessCount()` — decrement the number of times this leaf has been accessed Warning: throws and error if this isn't a TActionFilterCacheLeaf
- L140 _public function_ `virtual void UnCacheSelf()` — remove this node from the the tree
- L143 _public member_ `FString DebugName;`
- L147 _protected function_ `virtual bool KeysMatch(const void* RawKey) const`
- L154 _protected function_ `template<typename TNodeType> TSharedPtr<TNodeType> Cache(TNodeType* Child)`
- L161 _protected member_ `TArray<FSharedNode> Children;`
- L162 _protected member_ `FWeakNode Parent;`

#### class `FActionFilterCache`  
`class FActionFilterCache`  
_L175-238_
- desc: This class creates a tree structure that is used to store cached filter results in such a way that they can be looked up using all the relevant context data that determines how items are filtered. each node has a type agnostic key so that we can easily change how the cache is keyed. (See FActionFilterCache::GetIsFilteredByThisCache)
- L178 _public prototype_ `FActionFilterCache();`
- L180 _public prototype_ `static void OnReloadComplete(EReloadCompleteReason Reason);`
- L181 _public prototype_ `static void OnModuleChanged(FName ModuleName, EModuleChangeReason ChangeReason);`
- L182 _public prototype_ `static void ClearAllCache();`
- L186 _private prototype_ `TSharedPtr<TMap<FActionFilterCacheKey, bool>> GetCachedFilterResults(const FBlueprintActionFilter& Filter);` — get the cached map used by FBlueprintActionFilter::IsFilteredByThis to determine whether BP actions are filtered out
- L189 _private function_ `template<typename TKeyType> void FindOrCacheChildNode(TSharedPtr<FActionFilterCacheNode>& Current, const TKeyType& Key, FString DebugName, TDelegate<bool(const TKeyType&, const TKeyType&)> Comparison = nullptr)`
- L197 _private function_ `template<typename TKeyType> void FindOrCacheLeaf(TSharedPtr<FActionFilterCacheNode>& Current, const TKeyType& Key, FString DebugName, TDelegate<bool(const TKeyType&, const TKeyType&)> Comparison = nullptr)`
- L216 _private prototype_ `static void PopCache();` — Find the least likely item in the cache to be used again, and remove it to make room for more data
- L219 _private prototype_ `void CacheFilteredResult(const FBlueprintActionFilter& Filter, FBlueprintActionInfo& BlueprintAction, bool bWasFilteredOut);` — Cache result
- L222 _private prototype_ `bool IsFilteredByCachedResult(const FBlueprintActionFilter& Filter, FBlueprintActionInfo& BlueprintAction);` — Filter function
- L226 _private member_ `static TSharedPtr<FActionFilterCacheNode> SharedCache;` — the shared tree that stores previously calculated filter results for several different contects
- L228 _private member_ `static TAutoConsoleVariable<int32> CVarCacheLeafCapacity;`
- L231 _private member_ `static TArray<TWeakPtr<FActionFilterCacheNode>> CacheLeafs;` — array of all the leaf nodes in SharedCache so we can pop a rarely used node if we exceed CacheLeafCapacity
- L233 _private member_ `static FDelegateHandle ReloadCompleteDelegate;`
- L234 _private member_ `static FDelegateHandle ModuleChangedDelegate;`
- L237 _private member_ `TSharedPtr<TMap<FActionFilterCacheKey, bool>> CachedFilterResults;` — cached results from GetIsFilteredByThisCache so we don't have to re-search the tree

#### Free symbols / members of external scopes

- L25 _prototype_ `bool operator==(const FActionFilterCacheKey& A, const FActionFilterCacheKey& B);`
- L26 _prototype_ `uint32 GetTypeHash(const FActionFilterCacheKey& InKey);`

### `Source/Editor/BlueprintGraph/Private/BlueprintNodeSpawnerUtils.h` (Private)


#### struct `FBlueprintNodeSpawnerUtils`  
`struct FBlueprintNodeSpawnerUtils`  
_L13-62_
- L22 _public prototype_ `static FFieldVariant GetAssociatedField(UBlueprintNodeSpawner const* BlueprintAction);` — Certain node-spawners are associated with specific UFields (functions, properties, etc.). This attempts to retrieve the field from the spawner. @param  BlueprintAction	The node-spawner you want an associated field for. @return The action's associated field (null if it doesn't have one).
- L32 _public prototype_ `static UFunction const* GetAssociatedFunction(UBlueprintNodeSpawner const* BlueprintAction);` — Certain node-spawners are associated with specific UFunctions (call- function, and event spawners). This attempts to retrieve the function from the spawner. @param  BlueprintAction	The node-spawner you want an associated function for. @return The action's associated function (null if it doesn't have one).
- L42 _public prototype_ `static FProperty const* GetAssociatedProperty(UBlueprintNodeSpawner const* BlueprintAction);` — Certain node-spawners are associated with specific UProperties (get/set nodes, delegates, etc.). This attempts to retrieve a property from the the spawner. @param  BlueprintAction	The node-spawner you want an associated property for. @return The action's associated property (null if it doesn't have one).
- L52 _public prototype_ `static UClass* GetBindingClass(FBindingObject Binding);` — Utility function to pull UClass info from a tentative binding object (defaults to the object's class, uses the PropertyClass if the object is an object property). @param  Binding	The binding you want a class for. @return A UClass that corresponds to the supplied binding.
- L61 _public prototype_ `static bool IsStaleFieldAction(UBlueprintNodeSpawner const* BlueprintAction);` — Checks if the node-spawner's associated action is stale (meaning it belongs to a TRASH or REINST class). @param  BlueprintAction    The node-spawner you want to check. @return True if the action is stale (associated with a TRASH or REINST class).

### `Source/Editor/BlueprintGraph/Private/DelegateNodeHandlers.h` (Private)


#### struct `FDelegateOwnerId`  
`struct FDelegateOwnerId`  
_L22-44_
- L24 _public typedef_ `typedef TMap<FDelegateOwnerId, FBPTerminal*> FInnerTermMap;`
- L26 _public member_ `const class UEdGraphPin* OutputPin;`
- L27 _public member_ `const class UK2Node_BaseMCDelegate* DelegateNode;`
- L29 _public function_ `FDelegateOwnerId(const class UEdGraphPin* InOutputPin, const class UK2Node_BaseMCDelegate* InDelegateNode) : OutputPin(InOutputPin), DelegateNode(InDelegateNode)`
- L35 _public function_ `bool operator==(const FDelegateOwnerId& Other) const`

#### class `FKCHandler_AddRemoveDelegate`  
`class FKCHandler_AddRemoveDelegate : public FNodeHandlingFunctor`  
_L48-62_
- inherits: `FNodeHandlingFunctor`
- L50 _private member_ `EKismetCompiledStatementType Command;`
- L51 _private member_ `FDelegateOwnerId::FInnerTermMap InnerTermMap;`
- L54 _public function_ `FKCHandler_AddRemoveDelegate(FKismetCompilerContext& InCompilerContext, EKismetCompiledStatementType InCommand) : FNodeHandlingFunctor(InCompilerContext) , Command(InCommand)`
- L60 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L61 _public prototype_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`

#### class `FKCHandler_CreateDelegate`  
`class FKCHandler_CreateDelegate : public FNodeHandlingFunctor`  
_L67-77_
- inherits: `FNodeHandlingFunctor`
- L70 _public function_ `FKCHandler_CreateDelegate(FKismetCompilerContext& InCompilerContext) : FNodeHandlingFunctor(InCompilerContext)`
- L75 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L76 _public prototype_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`

#### class `FKCHandler_ClearDelegate`  
`class FKCHandler_ClearDelegate : public FNodeHandlingFunctor`  
_L82-94_
- inherits: `FNodeHandlingFunctor`
- L84 _private member_ `FDelegateOwnerId::FInnerTermMap InnerTermMap;`
- L87 _public function_ `FKCHandler_ClearDelegate(FKismetCompilerContext& InCompilerContext) : FNodeHandlingFunctor(InCompilerContext)`
- L92 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L93 _public prototype_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`

#### class `FKCHandler_CallDelegate`  
`class FKCHandler_CallDelegate : public FKCHandler_CallFunction`  
_L99-114_
- inherits: `FKCHandler_CallFunction`
- L101 _private member_ `FDelegateOwnerId::FInnerTermMap InnerTermMap;`
- L104 _public function_ `FKCHandler_CallDelegate(FKismetCompilerContext& InCompilerContext) : FKCHandler_CallFunction(InCompilerContext)`
- L109 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L110 _public prototype_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L111 _public prototype_ `virtual UFunction* FindFunction(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L112 _public function_ `virtual void CheckIfFunctionIsCallable(UFunction* Function, FKismetFunctionContext& Context, UEdGraphNode* Node) override`
- L113 _public prototype_ `virtual void AdditionalCompiledStatementHandling(FKismetFunctionContext& Context, UEdGraphNode* Node, FBlueprintCompiledStatement& Statement) override;`

#### Free symbols / members of external scopes

- L40 _function_ `friend uint32 GetTypeHash(const FDelegateOwnerId& DelegateOwnerId)`

### `Source/Editor/BlueprintGraph/Private/DynamicCastHandler.h` (Private)


#### class `FKCHandler_DynamicCast`  
`class FKCHandler_DynamicCast : public FNodeHandlingFunctor`  
_L18-34_
- inherits: `FNodeHandlingFunctor`
- L21 _protected member_ `TMap<UEdGraphNode*, FBPTerminal*> BoolTermMap;` — should be deprecated at a certain point (left in for backwards compatibility)
- L22 _protected member_ `EKismetCompiledStatementType CastType;`
- L25 _public function_ `FKCHandler_DynamicCast(FKismetCompilerContext& InCompilerContext, EKismetCompiledStatementType InCastType) : FNodeHandlingFunctor(InCompilerContext) , CastType(InCastType)`
- L31 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L32 _public prototype_ `virtual void RegisterNet(FKismetFunctionContext& Context, UEdGraphPin* Net) override;`
- L33 _public prototype_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`

### `Source/Editor/BlueprintGraph/Private/K2Node_EditorPropertyAccess.h` (Private)


#### class `UK2Node_EditorPropertyAccessBase`  
`class UK2Node_EditorPropertyAccessBase : public UK2Node_CallFunction`  
_L18-38_
- reflection: `UCLASS(Abstract)`
- inherits: `UK2Node_CallFunction`
- L24 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L28 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L29 _public prototype_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;`
- L30 _public prototype_ `virtual bool IsActionFilteredOut(const class FBlueprintActionFilter& Filter) override;`
- L31 _public prototype_ `virtual void EarlyValidation(class FCompilerResultsLog& MessageLog) const override;`
- L36 _protected function_ `virtual bool CanToggleNodePurity() const override`

#### class `UK2Node_GetEditorProperty`  
`class UK2Node_GetEditorProperty : public UK2Node_EditorPropertyAccessBase`  
_L41-47_
- reflection: `UCLASS()`
- inherits: `UK2Node_EditorPropertyAccessBase`
- L46 _public prototype_ `UK2Node_GetEditorProperty();`

#### class `UK2Node_SetEditorProperty`  
`class UK2Node_SetEditorProperty : public UK2Node_EditorPropertyAccessBase`  
_L50-56_
- reflection: `UCLASS()`
- inherits: `UK2Node_EditorPropertyAccessBase`
- L55 _public prototype_ `UK2Node_SetEditorProperty();`

### `Source/Editor/BlueprintGraph/Private/MakeStructHandler.h` (Private)


#### class `FKCHandler_MakeStruct`  
`class FKCHandler_MakeStruct : public FNodeHandlingFunctor`  
_L17-35_
- inherits: `FNodeHandlingFunctor`
- L20 _public prototype_ `FKCHandler_MakeStruct(FKismetCompilerContext& InCompilerContext);`
- L22 _public prototype_ `virtual UEdGraphPin* FindStructPinChecked(UEdGraphNode* Node) const;`
- L24 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* InNode) override;`
- L25 _public prototype_ `virtual void RegisterNet(FKismetFunctionContext& Context, UEdGraphPin* Net) override;`
- L26 _public prototype_ `void RegisterNetsImpl(FKismetFunctionContext& Context, UK2Node_MakeStruct* Node);`
- L28 _public prototype_ `virtual FBPTerminal* RegisterLiteral(FKismetFunctionContext& Context, UEdGraphPin* Net) override;`
- L30 _public prototype_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* InNode) override;`
- L34 _protected member_ `bool bAutoGenerateGotoForPure;` — Prevents this handler from auto-generating a GoTo to jump to the end of the node's compiled code so that child handlers can override the functionality

### `Source/Editor/BlueprintGraph/Private/PushModelHelpers.h` (Private)


#### struct `FKCPushModelHelpers`  
`struct FKCPushModelHelpers`  
_L8-20_
- L19 _public prototype_ `static class UEdGraphNode* ConstructMarkDirtyNodeForProperty(struct FKismetFunctionContext& Context, class FProperty* RepProperty, class UEdGraphPin* PropertyObjectPin);` — Generates nodes that will call the necessary functions for marking Push Model Properties dirty. These nodes should be generated and linked whenever we know there's a replicated property that is likely to have its value changed. @param Context				Current compilcation context. @param RepProperty			The Replicated Property that's being reference. @param PropertyObjectPin		The pin we'll use to grab a reference to the Object that owns the property.

### `Source/Editor/BlueprintGraph/Private/StructMemberNodeHandlers.h` (Private)


#### class `FKCHandler_StructMemberVariableGet`  
`class FKCHandler_StructMemberVariableGet : public FNodeHandlingFunctor`  
_L13-23_
- inherits: `FNodeHandlingFunctor`
- L16 _public function_ `FKCHandler_StructMemberVariableGet(FKismetCompilerContext& InCompilerContext) : FNodeHandlingFunctor(InCompilerContext)`
- L21 _public prototype_ `virtual void RegisterNet(FKismetFunctionContext& Context, UEdGraphPin* Net) override;`
- L22 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* InNode) override;`

#### class `FKCHandler_StructMemberVariableSet`  
`class FKCHandler_StructMemberVariableSet : public FKCHandler_VariableSet`  
_L25-34_
- inherits: `FKCHandler_VariableSet`
- L28 _public function_ `FKCHandler_StructMemberVariableSet(FKismetCompilerContext& InCompilerContext) : FKCHandler_VariableSet(InCompilerContext)`
- L33 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* InNode) override;`

### `Source/Editor/BlueprintGraph/Public/AnimNotifyEventNodeSpawner.h` (Public)


#### class `UAnimNotifyEventNodeSpawner`  
`class UAnimNotifyEventNodeSpawner : public UBlueprintEventNodeSpawner`  
_L12-32_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBlueprintEventNodeSpawner`
- L23 _public prototype_ `static UAnimNotifyEventNodeSpawner* Create(const FSoftObjectPath& InSkeletonObjectPath, FName InNotifyName);` — Creates a new UAnimNotifyEventNodeSpawner @param  NotifyName	The name you want assigned to the event. @return A newly allocated instance of this class.
- L26 _public function_ `const FSoftObjectPath& GetSkeletonObjectPath() const` — @return the skeleton object path
- L31 _private member_ `FSoftObjectPath SkeletonObjectPath;` — `UPROPERTY()` — The skeleton that supplied this notify, used for filtering

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Public/BlueprintActionDatabase.h` (Public)


#### class `FBlueprintActionDatabase`  
`class FBlueprintActionDatabase : public FGCObject, public FTickableEditorObject`  
_L46-280_
- inherits: `FGCObject,FTickableEditorObject`
- desc: Serves as a container for all available blueprint actions (no matter the type of blueprint/graph they belong in). The actions stored here are not tied to a specific ui menu; each action is a UBlueprintNodeSpawner which is charged with spawning a specific node type. Should be set up in a way where class specific actions are refreshed when the associated class is regenerated. @TODO:  Hook up to handle class recompile events, along with enum/struct asset creation events.
- L49 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDatabaseEntryUpdated, UObject*);`
- L51 _public typedef_ `typedef TMap<FObjectKey, int32> FPrimingQueue;`
- L52 _public typedef_ `typedef TArray<TObjectPtr<UBlueprintNodeSpawner>> FActionList;`
- L53 _public typedef_ `typedef TMap<FObjectKey, FActionList> FActionRegistry;`
- L54 _public typedef_ `typedef TMap<FSoftObjectPath, FActionList> FUnloadedActionRegistry;`
- L58 _public prototype_ `virtual ~FBlueprintActionDatabase();` — Destructor
- L66 _public prototype_ `static FBlueprintActionDatabase& Get();` — Getter to access the database singleton. Will populate the database first if this is the first time accessing it. @return The singleton instance of FBlueprintActionDatabase.
- L69 _public prototype_ `static FBlueprintActionDatabase* TryGet();` — Getter to access the datbase singleton, will return null if the database has not been initialized
- L72 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject interface
- L73 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L74 _public prototype_ `virtual TStatId GetStatId() const override;`
- L78 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L79 _public prototype_ `virtual FString GetReferencerName() const override;`
- L94 _public prototype_ `FActionRegistry const& GetAllActions();` — Will populate the database first if it hasn't been created yet, and then returns it in its entirety. Each node spawner is categorized by a class orasset. A spawner that corresponds to a specific class field (like a function, property, enum, etc.) will be listed under that field's class owner. Remaining spawners that can't be categorized this way will be registered by asset or node type. @return The entire action database, which maps specific objects to arrays of associated node-spawners.
- L100 _public prototype_ `void RefreshAll();` — Populates the action database from scratch. Loops over every known class and records a set of node-spawners associated with each.
- L105 _public prototype_ `void RefreshWorlds();` — Populates the action database with all level script actions from all active editor worlds.
- L110 _public prototype_ `void DeferredRemoveEntry(FObjectKey const& InKey);` — Removes the entry with the given key on the next tick.
- L118 _public prototype_ `void RefreshClassActions(UClass* const Class);` — Finds the database entry for the specified class and wipes it, repopulating it with a fresh set of associated node-spawners. @param  Class	The class entry you want rebuilt.
- L126 _public prototype_ `void RefreshAssetActions(UObject* const AssetObject);` — Finds the database entry for the specified asset and wipes it, repopulating it with a fresh set of associated node-spawners. @param  AssetObject	The asset entry you want rebuilt.
- L131 _public prototype_ `void RefreshComponentActions();` — Updates all component related actions
- L140 _public prototype_ `bool ClearAssetActions(UObject* const AssetObject);` — Finds the database entry for the specified object and wipes it. The entry won't be rebuilt, unless RefreshAssetActions() is explicitly called after. @param  AssetObject @return True if an entry was found and removed.
- L149 _public prototype_ `bool ClearAssetActions(const FObjectKey& AssetObjectKey);` — Finds the database entry for the specified object and wipes it. The entry won't be rebuilt, unless RefreshAssetActions() is explicitly called after. @param  AssetObjectKey @return True if an entry was found and removed.
- L157 _public prototype_ `void ClearUnloadedAssetActions(const FSoftObjectPath& ObjectPath);` — Finds the database entry for the specified unloaded asset and wipes it. The entry won't be rebuilt, unless RefreshAssetActions() is explicitly called after. @param ObjectPath	Object's path to lookup into the database
- L165 _public prototype_ `void MoveUnloadedAssetActions(const FSoftObjectPath& SourceObjectPath, const FSoftObjectPath& TargetObjectPath);` — Moves the unloaded asset actions from one location to another @param SourceObjectPath	The object path that the data can currently be found under @param TargetObjectPath	The object path that the data should be moved to
- L168 _public function_ `FOnDatabaseEntryUpdated& OnEntryUpdated()`
- L170 _public function_ `FOnDatabaseEntryUpdated& OnEntryRemoved()`
- L192 _public prototype_ `static bool IsClassAllowed(UClass const* InClass, EPermissionsContext InContext);` — Check whether the global filter applies to this class
- L193 _public prototype_ `static bool IsClassAllowed(const FTopLevelAssetPath& InClassPath, EPermissionsContext InContext);`
- L196 _public prototype_ `static bool HasClassFiltering();` — Check whether we have any class filtering applied
- L199 _public prototype_ `static bool IsFieldAllowed(UField const* InField, EPermissionsContext InContext);` — Check whether permissions allow this field
- L202 _public prototype_ `static bool IsFunctionAllowed(UFunction const* InFunction, EPermissionsContext InContext);` — Check whether permissions allow this function
- L205 _public prototype_ `static bool IsEnumAllowed(UEnum const* InEnum, EPermissionsContext InContext);` — Check whether permissions allow this enum
- L206 _public prototype_ `static bool IsEnumAllowed(const FTopLevelAssetPath& InEnumPath, EPermissionsContext InContext);`
- L209 _public prototype_ `static bool IsStructAllowed(UScriptStruct const* InStruct, EPermissionsContext InContext);` — Check whether permissions allow this struct
- L210 _public prototype_ `static bool IsStructAllowed(const FTopLevelAssetPath& InStructPath, EPermissionsContext InContext);`
- L213 _public prototype_ `static bool IsPinTypeAllowed(const FEdGraphPinType& InPinType, const FTopLevelAssetPath& InUnloadedAssetPath = FTopLevelAssetPath());` — Check whether permissions allow this pin type. InUnloadedAssetPath will be used in the case where a InPinType.PinSubCategoryObject is unable to be resolved.
- L217 _private prototype_ `FBlueprintActionDatabase();` — Private constructor for singleton purposes.
- L218 _private prototype_ `void Init();`
- L225 _private prototype_ `void RegisterAllNodeActions(FBlueprintActionDatabaseRegistrar& Registrar);` — @param  Registrar
- L230 _private prototype_ `void OnBlueprintChanged( UBlueprint* );` — This exists only because we need a pointer to associate our delegates with
- L233 _private prototype_ `void PreRefresh(bool bRefreshAll);` — Refresh other systems before a full or partial refresh
- L242 _private member_ `FActionRegistry ActionRegistry;` — A map of associated node-spawners for each class/asset. A spawner that corresponds to a specific class field (like a function, property, enum, etc.) will be mapped under that field's class outer. Other spawners (that can't be associated with a class outer), will be filed under the desired node's type, or an associated asset.
- L249 _private member_ `FUnloadedActionRegistry UnloadedActionRegistry;` — A map of associated object paths for each node-class that is associated with it. This is used for unloaded assets that will need to be replaced after the asset is loaded with the final (and more complete) nodespawner.
- L256 _private member_ `FPrimingQueue ActionPrimingQueue;` — References newly allocated actions that need to be "primed". Priming is something we do on Tick() aimed at speeding up performance (like pre- caching each spawner's template-node, etc.).
- L259 _private member_ `TArray<FObjectKey> ActionRemoveQueue;` — List of action keys to be removed on the next tick.
- L262 _private member_ `FOnDatabaseEntryUpdated EntryRefreshDelegate;`
- L263 _private member_ `FOnDatabaseEntryUpdated EntryRemovedDelegate;`
- L266 _private member_ `FDelegateHandle OnAssetLoadedDelegateHandle;` — Handles to registered delegates.
- L267 _private member_ `FDelegateHandle OnAssetAddedDelegateHandle;`
- L268 _private member_ `FDelegateHandle OnAssetRemovedDelegateHandle;`
- L269 _private member_ `FDelegateHandle OnAssetRenamedDelegateHandle;`
- L270 _private member_ `FDelegateHandle OnAssetsPreDeleteDelegateHandle;`
- L271 _private member_ `FDelegateHandle OnBlueprintUnloadedDelegateHandle;`
- L272 _private member_ `FDelegateHandle OnWorldAddedDelegateHandle;`
- L273 _private member_ `FDelegateHandle OnWorldDestroyedDelegateHandle;`
- L274 _private member_ `FDelegateHandle RefreshLevelScriptActionsDelegateHandle;`
- L275 _private member_ `FDelegateHandle OnModulesChangedDelegateHandle;`
- L276 _private member_ `FDelegateHandle OnReloadCompleteDelegateHandle;`
- L279 _private member_ `const TArray<struct FComponentTypeEntry>* ComponentTypes;` — Pointer to the shared list of currently existing component types

#### enum `FBlueprintActionDatabase::EPermissionsContext`  
`enum class EPermissionsContext`  
_L176-189_
- desc: Field visibility is different depending on context, this enum differentiates between the different contexts that fields can be present in
- L179 _public enumerator_ `Property` — A property on a class - from a user perspective a variable in the My Blueprint tab
- L182 _public enumerator_ `Asset` — An asset - e.g. an anim blueprint asset player or skeleton notify
- L185 _public enumerator_ `Node` — A K2 node in a graph - e.g. a function call
- L188 _public enumerator_ `Pin` — An exposed pin on a K2 node

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API BLUEPRINTGRAPH_API`
- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDatabaseEntryUpdated, UObject*);`

### `Source/Editor/BlueprintGraph/Public/BlueprintActionDatabaseRegistrar.h` (Public)


#### class `FBlueprintActionDatabaseRegistrar`  
`class FBlueprintActionDatabaseRegistrar`  
_L33-170_
- desc: From the BlueprintActionDatabase, passed around to all UK2Nodes, giving each a chance to register its own actions (specifically for UK2Nodes in other modules that the database doesn't have access to).
- L43 _public prototype_ `bool AddBlueprintAction(UBlueprintNodeSpawner* NodeSpawner);` — Attempts to suss out the key that this action should be registered under; if it doesn't find a better one then it associates the action with the node filling this out. @param  NodeSpawner	The new node spawner that you wish to register.
- L53 _public prototype_ `bool AddBlueprintAction(UClass const* ClassOwner, UBlueprintNodeSpawner* NodeSpawner);` — Each action should be recorded under a specific UField key; primarily to refresh those actions when the corresponding asset is updated (Blueprint regenerated, struct added/deleted, etc.). @param  FieldOwner	A field object that the node is associated with (flags when this action should be updated). @param  NodeSpawner	The new node spawner that you wish to register.
- L54 _public prototype_ `bool AddBlueprintAction(UEnum const* EnumOwner, UBlueprintNodeSpawner* NodeSpawner);`
- L55 _public prototype_ `bool AddBlueprintAction(UScriptStruct const* StructOwner, UBlueprintNodeSpawner* NodeSpawner);`
- L56 _public prototype_ `bool AddBlueprintAction(UField const* FieldOwner, UBlueprintNodeSpawner* NodeSpawner);`
- L57 _public prototype_ `bool AddBlueprintAction(FAssetData const& AssetDataOwner, UBlueprintNodeSpawner* NodeSpawner);`
- L66 _public prototype_ `bool AddBlueprintAction(UObject const* AssetOwner, UBlueprintNodeSpawner* NodeSpawner);` — Special case for asset bound actions (we want to clean-up/refresh these when the corresponding asset is updated). AssetOwner must be an asset! @param  AssetOwner	An asset object that the node is associated with (flags when this action should be updated). @param  NodeSpawner	The new node spawner that you wish to register.
- L78 _public prototype_ `bool IsOpenForRegistration(UObject const* OwnerKey);` — Occasionally (when an asset is added/refreshed), this registrar will be passed around to gather only specific keyed actions (see ActionKeyFilter). In that case, it will block registration of all unwanted keys. Functionality wise this doesn't matter to UK2Node, but UK2Node may be able to save on some work/allocations if it knew this beforehand. @param  OwnerKey		The key you wish to register your action(s) under. @return True if the OwnerKey would is allowed to register actions, false if it would be blocked.
- L79 _public prototype_ `bool IsOpenForRegistration(FAssetData const& AssetDataOwner);`
- L82 _public function_ `UObject const* GetActionKeyFilter() const` — Returns the current key the registrar is being filtered using
- L88 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(UBlueprintNodeSpawner*, FMakeStructSpawnerDelegate, const UScriptStruct*);`
- L95 _public prototype_ `int32 RegisterStructActions(const FMakeStructSpawnerDelegate& MakeActionCallback);` — @param  MakeActionCallback @return
- L98 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(UBlueprintNodeSpawner*, FMakeEnumSpawnerDelegate, const UEnum*);`
- L105 _public prototype_ `int32 RegisterEnumActions(const FMakeEnumSpawnerDelegate& MakeActionCallback);` — @param  MakeActionCallback @return
- L108 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(UBlueprintNodeSpawner*, FMakeFuncSpawnerDelegate, const UFunction*);`
- L116 _public function_ `template<class T> int32 RegisterClassFactoryActions(const FMakeFuncSpawnerDelegate& MakeActionCallback)` — @param  MakeActionCallback @return
- L122 _private typedef_ `typedef FBlueprintActionDatabase::FActionRegistry FActionRegistry;`
- L123 _private typedef_ `typedef FBlueprintActionDatabase::FUnloadedActionRegistry FUnloadedActionRegistry;`
- L124 _private typedef_ `typedef FBlueprintActionDatabase::FPrimingQueue FPrimingQueue;`
- L128 _private prototype_ `FBlueprintActionDatabaseRegistrar(FActionRegistry& Database, FUnloadedActionRegistry& UnloadedDatabase, FPrimingQueue& PrimingQueue, TSubclassOf<UEdGraphNode> DefaultKey = {});`
- L137 _private prototype_ `int32 RegisterClassFactoryActions(const UClass* TargetType, const FMakeFuncSpawnerDelegate& MakeActionCallback);` — @param  TargetType @param  MakeActionCallback @return
- L145 _private prototype_ `bool AddActionToDatabase(UObject const* ActionKey, UBlueprintNodeSpawner* NodeSpawner);` — Internal method that actually adds the action to the database. @param  ActionKey	The key you want the action listed under. @param  NodeSpawner	The new node spawner that you wish to register.
- L149 _private member_ `TSubclassOf<UEdGraphNode> GeneratingClass;` — The node type that this is currently passed to (acts as a fallback database key).
- L152 _private member_ `FActionRegistry& ActionDatabase;` — A reference to FBlueprintActionDatabase's internal map
- L155 _private member_ `FUnloadedActionRegistry& UnloadedActionDatabase;` — A reference to FBlueprintActionDatabase's internal map
- L163 _private member_ `UObject const* ActionKeyFilter;` — When an asset is added/updated we want to poll nodes again for new/refreshed actions, but only for that specific asset. This serves as a filter in that scenario (to keep nodes from adding unrelated, probably duplicate, actions).
- L166 _private member_ `FPrimingQueue& ActionPrimingQueue;` — A reference to FBlueprintActionDatabase's action priming queue
- L169 _private member_ `IAssetTools* AssetTools;` — Cached ptr to asset tools to avoid LoadModule calls per-AddBlueprintAction call

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API BLUEPRINTGRAPH_API`
- L88 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(UBlueprintNodeSpawner*, FMakeStructSpawnerDelegate, const UScriptStruct*);`
- L98 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(UBlueprintNodeSpawner*, FMakeEnumSpawnerDelegate, const UEnum*);`
- L108 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(UBlueprintNodeSpawner*, FMakeFuncSpawnerDelegate, const UFunction*);`

### `Source/Editor/BlueprintGraph/Public/BlueprintActionFilter.h` (Public)


#### struct `FBlueprintActionContext`  
`struct FBlueprintActionContext`  
_L49-85_
- L56 _public member_ `TWeakPtr<IBlueprintEditor> EditorPtr;` — A weak reference to the Blueprint editor context in which actions are being filtered. Note that this may be NULL or invalid if we're filtering actions outside of an editor context (e.g. commandlet).
- L63 _public member_ `TArray<UBlueprint*> Blueprints;` — A list of all blueprints you want actions for. Generally, this will only contain a single blueprint, but it can have many (where an action has to be available for every blueprint listed to pass the filter).
- L70 _public member_ `TArray<UEdGraph*> Graphs;` — A list of graphs you want compatible actions for. Generally, this will contain a single graph, but it can have several (where an action has to be viable for every graph to pass the filter).
- L77 _public member_ `TArray<UEdGraphPin*> Pins;` — A list of pins you want compatible actions for. Generally, this will contain a single pin, but it can have several (where an action has to be viable for every pin to pass the filter).
- L84 _public member_ `TArray<FFieldVariant> SelectedObjects;` — A list of objects the user currently has selected (things like blueprint properties, level actors, content-browser assets, etc.). Bound actions have to be tied to one of these objects in order to pass the filter.

#### struct `FBlueprintActionInfo`  
`struct FBlueprintActionInfo`  
_L96-183_
- desc: Info struct passed around to filter rejection tests. Wraps a UBlueprintNodeSpawner, and caches associated fields/files/etc. as they're requested (to optimize duplicated queries cross rejection tests).
- L99 _public prototype_ `FBlueprintActionInfo(UObject const* ActionOwner, UBlueprintNodeSpawner const* Action);`
- L102 _public prototype_ `FBlueprintActionInfo(FBlueprintActionInfo const& Rhs, IBlueprintNodeBinder::FBindingSet const& Bindings);`
- L110 _public prototype_ `UObject const* GetActionOwner() const;` — Retrieves the key that the wrapped action is associated with in the FBlueprintActionDatabase (either a UClass, or asset object). @return The class/asset that this action conceptually belongs to.
- L117 _public prototype_ `IBlueprintNodeBinder::FBindingSet const& GetBindings() const;` — Retrieves any bindings that the action will apply to spawned nodes. @return The set of bindings tied to this action.
- L127 _public prototype_ `UClass const* GetOwnerClass();` — Retrieves a class associated with the wrapped action. Intended to be the action's class "owner". Could be null if the action is keyed to an asset. Will not be the spawner's NodeClass (even if it is keyed to it in the database). @return The class that this action conceptually belongs to (null if the action is keyed to an asset that we cannot derive a class from).
- L135 _public prototype_ `UClass const* GetNodeClass();` — Retrieves the node class that the wrapped action will spawn (assume to be not null). @return The node type that the action will spawn.
- L144 _public prototype_ `FFieldVariant GetAssociatedMemberField();` — Certain actions are associated with specific member fields (a member function call, a variable get/set, etc.) This retrieves that member field if there is one (not all actions have an associated field). @return The member field associated with the wrapped action (null if there isn't one).
- L154 _public prototype_ `FProperty const* GetAssociatedProperty();` — Certain actions are associated with specific properties (like delegate node spawners, or variable get/set spawners) This retrieves that property from the wrapped action if it can (not all actions have an associated property). @return The property associated with the wrapped action (null if there isn't one).
- L163 _public prototype_ `UFunction const* GetAssociatedFunction();` — Certain actions are associated with specific functions (like function call spawners, or event spawners) This retrieves the function from the wrapped action if it can (not all actions have an associated function). @return The function associated with the wrapped action (null if there isn't one).
- L166 _public member_ `UBlueprintNodeSpawner const* const NodeSpawner;` — The raw action that this struct represent (const so we don't mutate the database)
- L170 _private member_ `TWeakObjectPtr<const UObject> ActionOwner;` — The class or asset-object that the NodeSpawner action is keyed to (in the action database)
- L173 _private member_ `uint32 CacheFlags;` — Keeps track of the fields we've cached (needed in case one turns out to be null)
- L176 _private member_ `TWeakObjectPtr<const UClass> CachedOwnerClass;`
- L177 _private member_ `FFieldVariant CachedActionField;`
- L178 _private member_ `FProperty const* CachedActionProperty;`
- L179 _private member_ `UFunction const* CachedActionFunction;`
- L182 _private member_ `IBlueprintNodeBinder::FBindingSet Bindings;`

#### enum `EActionFilterTestFlags`  
`enum class EActionFilterTestFlags`  
_L190-203_
- desc: @todo - Need to revisit this later; for now these flags remain in place for backcompat but are currently not in use.
- L192 _public enumerator_ `None = 0`
- L200 _public enumerator_ `CacheResults = 1 << 0` — these tests will be have their combined result cached for faster lookup. note: rejection tests can only be cached if they either A: Don't access any mutable data or B: Only access mutable data that is listed as a filter key in FActionFilterCache::GetCachedFilterResults
- L202 _public enumerator_ `Default = None` — this would allow us to change the default behavior

#### struct `FActionFilterTest`  
`struct FActionFilterTest : TSharedFromThis<FActionFilterTest>`  
_L212-233_
- inherits: `TSharedFromThis<FActionFilterTest>`
- desc: @todo - Need to revisit this later; for now this wrapper type remains in place for backcompat, but flags are currently not in use.
- L214 _public member_ `static TAutoConsoleVariable<bool> CVarEnableCaching;`
- L217 _public typedef_ `typedef FBlueprintGraphModule::FActionMenuRejectionTest FRejectionDelegate;` — The filter uses a series of rejection tests matching
- L219 _public prototype_ `FActionFilterTest(const FRejectionDelegate Delegate, FString Name, EActionFilterTestFlags Flags = EActionFilterTestFlags::Default);`
- L221 _public function_ `TSharedRef<FActionFilterTest> WithFlags(EActionFilterTestFlags InFlags)`
- L227 _public prototype_ `bool Call(FBlueprintActionFilter const& Filter, FBlueprintActionInfo& ActionInfo);`
- L228 _public prototype_ `bool operator==(const FActionFilterTest& other) const;`
- L230 _public member_ `FRejectionDelegate RejectionDelegate;`
- L231 _public member_ `FString Name;` — this name must be unique
- L232 _public member_ `EActionFilterTestFlags Flags = EActionFilterTestFlags::Default;`

#### class `FBlueprintActionFilter`  
`class FBlueprintActionFilter`  
_L244-454_
- L248 _public typedef_ `typedef FBlueprintGraphModule::FActionMenuRejectionTest FRejectionTestDelegate;` — The filter uses a series of rejection tests matching
- L294 _public prototype_ `FBlueprintActionFilter(const EFlags InFlags = BPFILTER_NoFlags);` — @param InFlags - Filter configuration flags.
- L300 _public member_ `FBlueprintActionContext Context;` — Contains the full blueprint/graph/pin context that this is filtering actions for.
- L308 _public member_ `TArray< TSubclassOf<UEdGraphNode> > PermittedNodeTypes;` — A list of allowed node types. If a spawner's NodeClass isn't one of these types, then it is filtered out. Use the "RejectPermittedNodeSubClasses" flag to aggressively filter out child classes as well (enforcing an explicit match).
- L315 _public member_ `TArray< TSubclassOf<UEdGraphNode> > RejectedNodeTypes;` — A list of node types that should be filtered out. If a node class is listed both here and in PermittedNodeTypes, then the exclusion wins (it will be filtered out).
- L332 _public member_ `TArray<FTargetClassFilterData> TargetClasses;`
- L335 _public prototype_ `static void AddUnique(TArray<FTargetClassFilterData>& ToArray, UClass* TargetClass);` — Helper to add a class to the TargetClasses, TargetClass may already be in the array
- L338 _public prototype_ `static void Add(TArray<FTargetClassFilterData>& ToArray, UClass* TargetClass);` — Helper to add a class to the TargetClasses, fills out FTargetClassFilterData
- L341 _public member_ `class FBlueprintGraphModule* BluprintGraphModule;` — Cached reference to the BluprintGraphModule, which has extra rejection tests:
- L344 _public member_ `TSharedPtr<IAssetReferenceFilter> AssetReferenceFilter;` — Filter for asset references
- L353 _public prototype_ `void AddRejectionTest(FRejectionTestDelegate RejectionTestDelegate);` — Users can extend the filter and add their own rejection tests with this method. We use rejection "IsFiltered" tests rather than inclusive tests because it is more optimal to whittle down the list of actions early. @param  RejectionTestDelegate	The rejection test you wish to add to this filter.
- L359 _public prototype_ `void AddRejectionTest(TSharedRef<FActionFilterTest> RejectionTest);` — @param  RejectionTest	a test this filter will run to cull blueprint actions @param  Flags	List of flags that will be added in the provided rejection test
- L369 _public prototype_ `bool IsFiltered(FBlueprintActionInfo& BlueprintAction);` — Query to check and see if the specified action gets filtered out by this (and any and'd/or'd filters). NOT marked const to keep FIsFilteredDelegates from recursively calling. @param  BlueprintAction	The node-spawner you wish to test. @return False if the action passes the filter, otherwise false (the action got filtered out).
- L381 _public prototype_ `FBlueprintActionFilter const& operator|=(FBlueprintActionFilter const& Rhs);` — Appends another filter to be utilized in IsFiltered() queries, extending the query to be: IsFilteredByThis() || Rhs.IsFiltered() NOTE: Appending additional filters can hinder performance (as the additional filter has to loop over its tests foreach database entry) @param  Rhs	The filter to append to this one. @return This.
- L393 _public prototype_ `FBlueprintActionFilter const& operator&=(FBlueprintActionFilter const& Rhs);` — Appends another filter to be utilized in IsFiltered() queries, extending the query to be: IsFilteredByThis() && Rhs.IsFiltered() NOTE: Appending additional filters can hinder performance (as the additional filter has to loop over its tests foreach database entry) @param  Rhs	The filter to append to this one. @return This.
- L398 _public function_ `inline bool HasAnyFlags(EFlags InFlags) const` — @return TRUE if any of the given configuration flags are set on this filter.
- L406 _public function_ `inline bool HasAllFlags(EFlags InFlags) const` — @return TRUE if all of the given configuration flags are set on this filter.
- L412 _public prototype_ `static bool IsFilterTestTraceLoggingEnabled();`
- L413 _public prototype_ `static bool IsFilterTestStatsLoggingEnabled();`
- L414 _public prototype_ `TArray<FString> GetFilterTestProfile();`
- L425 _private prototype_ `bool IsFilteredByThis(FBlueprintActionInfo& BlueprintAction) const;` — Query to check and see if the specified action gets filtered out by this (does not take into consideration any and'd/or'd filters). @param  BlueprintAction	The node-spawner you wish to test. @return False if the action passes the filter, otherwise true (the action got filtered out).
- L428 _private member_ `EFlags FilterFlags = BPFILTER_NoFlags;` — Configuration flags for this filter.
- L431 _private member_ `TArray<FRejectionTestDelegate> FilterTests;` — Set of rejection tests for this specific filter.
- L434 _private member_ `TArray<FBlueprintActionFilter> AndFilters;` — Filters to be logically and'd in with the IsFilteredByThis() result.
- L437 _private member_ `TArray<FBlueprintActionFilter> OrFilters;` — Alternative filters to be logically or'd in with the IsFilteredByThis() result.
- L449 _private member_ `mutable TMap<int32, FFilterTestProfileRecord> FilterTestProfiles;`
- L451 _private prototype_ `FFilterTestProfileRecord* BeginFilterTestProfileEvent(int32 FilterTestIndex, uint64 FilterTestFuncPtr) const;`
- L452 _private prototype_ `void EndFilterTestProfileEvent(FFilterTestProfileRecord* InEvent, bool bWasFiltered, double StartTime) const;`

#### enum `FBlueprintActionFilter::EFlags`  
`enum EFlags`  
_L250-291_
- desc: Flags, which configure certain rejection tests.
- L252 _public enumerator_ `BPFILTER_NoFlags = (0)`
- L255 _public enumerator_ `BPFILTER_PermitDeprecated = (1<<0)` — Deprecated class actions will not be filtered out
- L263 _public enumerator_ `BPFILTER_RejectGlobalFields = (1<<1)` — Rejects actions associated with global/static ("persistent") fields. However, static members of TargetClasses are kept, and not outright rejected by this (if TargetClasses is left empty, then all "persistent" fields are rejected).
- L270 _public enumerator_ `BPFILTER_RejectPermittedSubClasses = (1<<2)` — Makes PermittedNodeType tests more aggressive by rejecting node sub-classes, (actions would have to explicitly match a class listed in PermittedNodeTypes).
- L277 _public enumerator_ `BPFILTER_PermitRejectionSubClasses = (1<<3)` — Makes RejectedNodeType tests less aggressive by permitting node sub-classes, (actions would have to explicitly match a class listed in RejectedNodeTypes).
- L284 _public enumerator_ `BPFILTER_RejectNonImportedFields = (1<<4)` — Actions that reference member variables or functions that belong to a struct that exists outside the scope of the current set of imported namespaces will be filtered out.
- L290 _public enumerator_ `BPFILTER_RejectIncompatibleThreadSafety = (1<<5)` — Rejects actions that would spawn nodes with thread safety characteristics that are incompatible with the specification of the containing graph

#### struct `FBlueprintActionFilter::FTargetClassFilterData`  
`struct FTargetClassFilterData`  
_L323-331_
- desc: A list of classes that you want members for. If an action would produce a node with a TargetPin, and that pin is incompatible with one of these classes, then the action is filtered out. Extra data is cached in FTargetClassFilterData so that it can be reused by filters efficiently.
- L325 _public member_ `UClass* TargetClass;`
- L326 _public member_ `TArray<FString> HiddenCategories;`
- L327 _public function_ `bool operator==(const FTargetClassFilterData& Other) const`

#### struct `FBlueprintActionFilter::FFilterTestProfileRecord`  
`struct FFilterTestProfileRecord`  
_L440-447_
- L442 _public member_ `uint64 TestFuncPtr = 0;`
- L443 _public member_ `float TotalTimeMs = 0.0f;`
- L444 _public member_ `int32 NumIterations = 0;`
- L445 _public member_ `int32 NumFilteredOut = 0;`
- L446 _public member_ `bool bOutputBeginEventEmitted = false;`

#### Free symbols / members of external scopes

- L29 _macro_ `#define UE_API BLUEPRINTGRAPH_API`
- L31 _macro_ `#define ENABLE_BLUEPRINT_ACTION_FILTER_PROFILING (!(UE_BUILD_SHIPPING || UE_BUILD_TEST) && 0)`
- L205 _prototype_ `ENUM_CLASS_FLAGS(EActionFilterTestFlags);`
- L237 _macro_ `#define MAKE_ACTION_FILTER_REJECTION_TEST(TestFunc, ...) \` — @todo - Need to revisit this; currently defined for backcompat but we may deprecate its use later as it is somewhat rigid. constructor for TSharedRef<FBlueprintActionFilterRejectionTest> that auto deduces the name
- L456 _prototype_ `ENUM_CLASS_FLAGS(FBlueprintActionFilter::EFlags);`

### `Source/Editor/BlueprintGraph/Public/BlueprintEditorSettings.h` (Public)


#### enum `ESaveOnCompile`  
`enum ESaveOnCompile : int`  
_L41-46_
- reflection: `UENUM()`
- L43 _public enumerator_ `SoC_Never UMETA(DisplayName="Never")`
- L44 _public enumerator_ `SoC_SuccessOnly UMETA(DisplayName="On Success Only")`
- L45 _public enumerator_ `SoC_Always UMETA(DisplayName = "Always")`

#### struct `FPerBlueprintSettings`  
`struct FPerBlueprintSettings`  
_L53-67_
- reflection: `USTRUCT()`
- desc: Blueprint Editor settings that are different for each blueprint. See FKismetDebugUtilities for helper functions
- L58 _public member_ `TArray<FBlueprintBreakpoint> Breakpoints;` — `UPROPERTY()`
- L61 _public member_ `TArray<FBlueprintWatchedPin> WatchedPins;` — `UPROPERTY()`
- L63 _public function_ `bool operator==(const FPerBlueprintSettings& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPerBlueprintSettings> : public TStructOpsTypeTraitsBase2<FPerBlueprintSettings>`  
_L69-75_
- inherits: `TStructOpsTypeTraitsBase2<FPerBlueprintSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L72-74_

#### struct `FAdditionalBlueprintCategory`  
`struct FAdditionalBlueprintCategory`  
_L78-87_
- reflection: `USTRUCT()`
- L83 _public member_ `FText Name;` — `UPROPERTY(EditAnywhere, Category = Category)`
- L86 _public member_ `FSoftClassPath ClassFilter;` — `UPROPERTY(EditAnywhere, Category = Category)`

#### class `UBlueprintEditorSettings`  
`class UBlueprintEditorSettings : public UDeveloperSettings`  
_L90-433_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- L98 _private member_ `bool bDrawMidpointArrowsInBlueprints;` — `UPROPERTY(EditAnywhere, config, Category=VisualStyle, meta=(DisplayName="Draw midpoint arrows in Blueprints"))` — Should arrows indicating data/execution flow be drawn halfway along wires?
- L102 _private member_ `bool bShowGraphInstructionText;` — `UPROPERTY(EditAnywhere, config, Category = VisualStyle)` — Determines if lightweight tutorial text shows up at the top of empty blueprint graphs
- L106 _private member_ `bool bHideUnrelatedNodes;` — `UPROPERTY(EditAnywhere, config, Category = VisualStyle)` — If true, fade nodes which are not connected to the selected nodes
- L110 _private member_ `bool bShowShortTooltips;` — `UPROPERTY(EditAnywhere, config, Category = VisualStyle)` — If true, use short tooltips whenever possible
- L114 _private member_ `bool bShowFunctionParameterIcon;` — `UPROPERTY(EditAnywhere, config, Category = VisualStyle)` — If true, show an icon next to function parameter nodes.
- L118 _private member_ `bool bShowFunctionLocalVariableIcon;` — `UPROPERTY(EditAnywhere, config, Category = VisualStyle)` — If true, show an icon next to function local variable nodes.
- L127 _private member_ `bool bEnableInputTriggerSupportWarnings;` — `UPROPERTY(EditAnywhere, Config, Category=Workflow, meta=(DisplayName="Enhanced Input: Enable Input Trigger Support Warnings"))` — If enabled Input Action nodes will hide unsupported trigger pins and give warnings when using unsupported triggers. This warning only works with triggers set up in an Input Action, not Input Mapping Contexts.
- L131 _private member_ `bool bSplitContextTargetSettings;` — `UPROPERTY(EditAnywhere, config, Category=Workflow, meta=(DisplayName="Context Menu: Divide Context Target Preferences"))` — If enabled, we'll save off your chosen target setting based off of the context (allowing you to have different preferences based off what you're operating on).
- L135 _private member_ `bool bExposeAllMemberComponentFunctions;` — `UPROPERTY(EditAnywhere, config, Category=Workflow, meta=(DisplayName="Context Menu: Expose All Sub-Component Functions"))` — If enabled, then ALL component functions are exposed to the context menu (when the contextual target is a component owner). Ignores "ExposeFunctionCategories" metadata for components.
- L139 _private member_ `bool bShowContextualFavorites;` — `UPROPERTY(EditAnywhere, config, Category=Workflow, meta=(DisplayName="Context Menu: Show Favorites Section"))` — If enabled, then a separate section with your Blueprint favorites will be pinned to the top of the context menu.
- L143 _private member_ `bool bExposeDeprecatedFunctions;` — `UPROPERTY(EditAnywhere, config, Category = Workflow)` — If enabled, deprecated functions will be visible in the context menu and will be available for override implementation. By default, functions marked as deprecated are not exposed in either case.
- L147 _private member_ `bool bCompactCallOnMemberNodes;` — `UPROPERTY(EditAnywhere, config, Category=Workflow)` — If enabled, then call-on-member actions will be spawned as a single node (instead of a GetMember + FunctionCall node).
- L151 _private member_ `bool bFlattenFavoritesMenus;` — `UPROPERTY(EditAnywhere, config, Category=Workflow)` — If enabled, then your Blueprint favorites will be uncategorized, leaving you with less nested categories to sort through.
- L155 _private member_ `bool bAutoCastObjectConnections;` — `UPROPERTY(EditAnywhere, config, Category=Workflow)` — If enabled, then you'll be able to directly connect arbitrary object pins together (a pure cast node will be injected automatically).
- L159 _private member_ `bool bShowViewportOnSimulate;` — `UPROPERTY(EditAnywhere, config, Category=Workflow)` — If true will show the viewport tab when simulate is clicked.
- L163 _private member_ `bool bSpawnDefaultBlueprintNodes;` — `UPROPERTY(EditAnywhere, config, Category = Workflow)` — If set will spawn default "ghost" event nodes in new Blueprints, modifiable in the [DefaultEventNodes] section of EditorPerProjectUserSettings
- L167 _private member_ `bool bHideConstructionScriptComponentsInDetailsView;` — `UPROPERTY(EditAnywhere, config, Category = Workflow)` — If set will exclude components added in a Blueprint class Construction Script from the component details view
- L171 _private member_ `bool bNavigateToNativeFunctionsFromCallNodes;` — `UPROPERTY(EditAnywhere, config, Category = Workflow)` — If set, double clicking on a call function node will attempt to navigate an open C++ editor to the native source definition
- L175 _private member_ `bool bDoubleClickNavigatesToParent;` — `UPROPERTY(config, EditAnywhere, Category = Workflow)` — Double click to navigate up to the parent graph
- L179 _private member_ `bool bEnableTypePromotion;` — `UPROPERTY(config, EditAnywhere, Category = Workflow)` — Allows for pin types to be promoted to others, i.e. float to double
- L183 _private member_ `bool bShowPanelContextMenuForIncompatibleConnections;` — `UPROPERTY(config, EditAnywhere, Category = Workflow)` — When enabled the the list of compatible nodes will be shown when a connection is attempted between incompatible pins
- L187 _private member_ `TSet<FName> TypePromotionPinDenyList;` — `UPROPERTY(config, EditAnywhere, Category = Workflow, meta=(EditCondition="bEnableTypePromotion"))` — If a pin type is within this list, then it will never be marked as a possible promotable function.
- L191 _private member_ `TArray<FAdditionalBlueprintCategory> AdditionalBlueprintCategories;` — `UPROPERTY(config, EditAnywhere, Category = Workflow)` — List of additional category names to show in Blueprints, optionally filtered by parent class type.
- L195 _private member_ `EBlueprintBreakpointReloadMethod BreakpointReloadMethod;` — `UPROPERTY(config, EditAnywhere, Category = Workflow)` — How to handle previously-set breakpoints on reload.
- L199 _private member_ `bool bEnablePinValueInspectionTooltips;` — `UPROPERTY(config, EditAnywhere, Category = Workflow)` — If enabled, pin tooltips during PIE will be interactive
- L203 _private member_ `bool bEnableNamespaceEditorFeatures;` — `UPROPERTY(config, EditAnywhere, Category = Workflow)` — Whether to enable namespace importing and filtering features in the Blueprint editor
- L207 _private member_ `TArray<FString> NamespacesToAlwaysInclude;` — `UPROPERTY(EditAnywhere, config, Category = Workflow, meta = (EditCondition = "bEnableNamespaceEditorFeatures", DisplayName = "Global Namespace Imports (Local User Only)"))` — A list of namespace identifiers that the Blueprint editor should always import by default. Requires Blueprint namespace features to be enabled and only applies to the current local user. Editing this list will also cause any visible Blueprint editor windows to be closed.
- L211 _private member_ `bool bEnableContextMenuTimeSlicing;` — `UPROPERTY(EditAnywhere, config, Category = Workflow, meta = (DisplayName = "Enable Non-Blocking Context Menu"))` — When the Blueprint graph context menu is invoked (e.g. by right-clicking in the graph or dragging off a pin), do not block the UI while populating the available actions list.
- L215 _private member_ `int32 ContextMenuTimeSlicingThresholdMs;` — `UPROPERTY(EditAnywhere, config, Category = Workflow, AdvancedDisplay, meta = (EditCondition = "bEnableContextMenuTimeSlicing", DisplayName = "Context Menu: Non-Blocking Per-Frame Threshold (ms)", ClampMin = "1"))` — The maximum amount of time (in milliseconds) allowed per frame for Blueprint graph context menu building when the non-blocking option is enabled. Larger values will complete the menu build in fewer frames, but will also make the UI feel less responsive. Smaller values will make the UI feel more responsive, but will also take longer to fully populate the menu.
- L219 _private member_ `bool bIncludeActionsForSelectedAssetsInContextMenu;` — `UPROPERTY(EditAnywhere, config, Category = Workflow, meta = (DisplayName = "Context Menu: Include Pre-Bound Actions for Selected Assets"))` — If enabled, invoking the Blueprint graph context menu with one or more compatible assets selected in the Content Browser will generate an additional set of pre-bound menu actions when the "Context Sensitive" option is enabled. For example, selecting a Static Mesh asset in the Content Browser will result in an extra "Add Static Mesh Component" menu action that's already bound to the selected asset.
- L223 _private member_ `bool bLimitAssetActionBindingToSingleSelectionOnly;` — `UPROPERTY(EditAnywhere, config, Category = Workflow, meta = (EditCondition = "bIncludeActionsForSelectedAssetsInContextMenu", DisplayName = "Context Menu: Pre-Bound Actions: Restrict to Single Selection"))` — Only generate pre-bound "Add Component" actions when there is a single asset selected in the Content Browser. If more than one asset is selected, pre-bound "Add Component" actions will not be generated. Enabling this option can improve UI responsiveness and decrease the time it takes to build the context menu, while still preserving the ability to include actions pre-bound to the selected asset.
- L227 _private member_ `bool bLoadSelectedAssetsForContextMenuActionBinding;` — `UPROPERTY(EditAnywhere, config, Category = Workflow, meta = (EditCondition = "bIncludeActionsForSelectedAssetsInContextMenu", DisplayName = "Context Menu: Pre-Bound Actions: Always Load Selected Asset(s)"))` — When generating pre-bound "Add Component" actions, any selected assets that are not yet loaded will be synchronously loaded as part of building the Blueprint Graph context menu. Enabling this option will ensure that all pre-bound actions for all selected assets are included in the menu, but load times may also affect editor UI responsiveness while the context menu is building.
- L231 _private member_ `bool bDoNotMarkAllInstancesDirtyOnDefaultValueChange;` — `UPROPERTY(EditAnywhere, config, Category = Workflow)` — If enabled, assets containing Blueprint instances (e.g. maps) will not be marked dirty when default values are edited, unless it results in the instance becoming realigned with the new default value.
- L237 _private member_ `bool bFavorPureCastNodes;` — `UPROPERTY(EditAnywhere, config, AdvancedDisplay, Category = Experimental, meta = (DisplayName = "Default to Using Pure Cast Nodes"))` — If enabled, then placed cast nodes will default to their "pure" form (meaning: without execution pins).
- L243 _private member_ `TEnumAsByte<ESaveOnCompile> SaveOnCompile;` — `UPROPERTY(EditAnywhere, config, Category = Compiler)` — Determines when to save Blueprints post-compile
- L247 _private member_ `bool bJumpToNodeErrors;` — `UPROPERTY(EditAnywhere, config, Category = Compiler)` — When enabled, if a blueprint has compiler errors, then the graph will jump and focus on the first node generating an error
- L251 _private member_ `bool bAllowExplicitImpureNodeDisabling;` — `UPROPERTY(EditAnywhere, config, Category = Compiler, meta = (DisplayName = "Show Node Enable/Disable Options"))` — If enabled, nodes with execution pins can be disabled via context menu. Disabled nodes will not be compiled, but also will not break existing connections.
- L257 _private member_ `bool bShowActionMenuItemSignatures;` — `UPROPERTY(EditAnywhere, config, Category = DeveloperTools)` — If enabled, tooltips on action menu items will show the associated action's signature id (can be used to setup custom favorites menus).
- L261 _private member_ `bool bBlueprintNodeUniqueNames;` — `UPROPERTY(EditAnywhere, config, Category = DeveloperTools, meta = (DisplayName = "Display Unique Names for Blueprint Nodes"))` — If enabled, blueprint nodes in the event graph will display with unique names rather than their display name.
- L267 _private member_ `float NodeTemplateCacheCapMB;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, config, Category = Performance, DisplayName = "Node-Template Cache Cap (MB)", meta = (ClampMin = "0", UIMin = "0"))` — The node template cache is used to speed up blueprint menuing. This determines the peak data size for that cache.
- L273 _private member_ `EFiBIndexAllPermission AllowIndexAllBlueprints;` — `UPROPERTY(EditAnywhere, config, Category = FindInBlueprints)` — Whether to enable the "Index All" action in the Find-in-Blueprints search window when blueprint assets with an out-of-date index (search metadata) are found and whether to allow automatic resaving. WARNING: Only allow "Index All" if your project is small enough that all assets can be loaded in memory at once. Only enable saving if you are allowed to potentially checkout and resave all assets.
- L277 _private member_ `bool bSearchForReferencesWhenVariableTypeChanged;` — `UPROPERTY(EditAnywhere, config, Category = FindInBlueprints)` — If true we'll automatically search for references to a variable when its type is changed
- L281 _private member_ `bool bShowInheritedVariables;` — `UPROPERTY(config)` — If set we'll show the inherited variables in the My Blueprint view.
- L285 _private member_ `bool bAlwaysShowInterfacesInOverrides;` — `UPROPERTY(config)` — If set interface functions will always show in the overrides menu, even if they are already shown in the interfaces menu
- L289 _private member_ `bool bShowParentClassInOverrides;` — `UPROPERTY(config)` — If set then the parent class will be listed next to the override function name in the overrides function menu
- L293 _private member_ `bool bShowEmptySections;` — `UPROPERTY(config)` — If set we'll show empty sections in the My Blueprint view.
- L297 _private member_ `bool bShowAccessSpecifier;` — `UPROPERTY(config)` — If set we'll show the access specifier of functions in the My Blueprint view
- L301 _private member_ `TMap<FGuid, FEditedDocumentInfo> Bookmarks;` — `UPROPERTY(config)` — Blueprint bookmark database
- L305 _private member_ `TArray<FBPEditorBookmarkNode> BookmarkNodes;` — `UPROPERTY(config)` — Blueprint bookmark nodes (for display)
- L309 _private member_ `TMap<FString, FPerBlueprintSettings> PerBlueprintSettings;` — `UPROPERTY(config)` — Maps Blueprint path to settings such as breakpoints
- L313 _private member_ `bool bIncludeCommentNodesInBookmarksTab;` — `UPROPERTY(config)` — If enabled, comment nodes will be included in the tree view display in the Bookmarks tab.
- L317 _private member_ `bool bShowBookmarksForCurrentDocumentOnlyInTab;` — `UPROPERTY(config)` — If enabled, only the bookmarks for the current document will be shown in the Bookmarks tab.
- L321 _private member_ `TMap<int32, FEditedDocumentInfo> GraphEditorQuickJumps;` — `UPROPERTY(config)` — Blueprint graph editor "Quick Jump" command bindings
- L326 _private member_ `bool bEnableNamespaceFilteringFeatures;` — `UPROPERTY(Transient)` — @todo_namespaces - Remove this if/when dependent code is changed to utilize the single setting above.
- L331 _private member_ `bool bEnableNamespaceImportingFeatures;` — `UPROPERTY(Transient)` — @todo_namespaces - Remove this if/when dependent code is changed to utilize the single setting above.
- L336 _private member_ `bool bInheritImportedNamespacesFromParentBP;` — `UPROPERTY(Transient)` — @todo_namespaces - Remove this if/when this becomes a permanent setting. For now this is experimental.
- L344 _private member_ `TArray<TSoftClassPtr<UObject>> BaseClassesToAllowRecompilingDuringPlayInEditor;` — `UE_DEPRECATED(5.6, "This is now the default behavior (true). If you have classes that should not compile during PIE add them to BaseClassesToDisallowRecompilingDuringPlayInEditor.")` — `UPROPERTY(config)` — Any blueprint deriving from one of these base classes will be allowed to recompile during Play-in-Editor (This setting exists both as an editor preference and project setting, and will be allowed if listed in either place)
- L351 _private member_ `TArray<TSoftClassPtr<UObject>> BaseClassesToDisallowRecompilingDuringPlayInEditor;` — `UPROPERTY(EditAnywhere, config, Category=Play, meta=(AllowAbstract, ShowObjectRootClass))` — Any blueprint deriving from one of these base classes will be disallowed to recompile during Play-in-Editor (This setting exists both as an editor preference and project setting, and will be allowed if listed in either place)
- L354 _private function_ `FPathPermissionList& GetFunctionPermissions()` — Get allowed functions permissions list
- L357 _private function_ `FPathPermissionList& GetStructPermissions()` — Get allowed structs permissions list
- L360 _private function_ `FPathPermissionList& GetEnumPermissions()` — Get allowed enums permissions list
- L363 _private function_ `FNamePermissionList& GetPinCategoryPermissions()` — Get allowed pin categories permissions list
- L365 _private typedef_ `using FOnIsClassAllowed = TDelegate<bool(const UClass* InClass)>;`
- L366 _private typedef_ `using FOnIsClassPathAllowed = TDelegate<bool(const FTopLevelAssetPath& InClassPath)>;`
- L367 _private typedef_ `using FOnIsFunctionAllowedForAsset = TDelegate<bool(const UBlueprint* InBlueprint, const FName InFunctionName)>;`
- L370 _private prototype_ `void RegisterIsClassAllowedDelegate(const FName OwnerName, FOnIsClassAllowed Delegate);` — Delegates called to determine whether a class type is allowed
- L371 _private prototype_ `void UnregisterIsClassAllowedDelegate(const FName OwnerName);`
- L372 _private prototype_ `bool IsClassAllowed(const UClass* InClass) const;`
- L373 _private function_ `bool HasClassFiltering() const`
- L375 _private prototype_ `void RegisterIsClassPathAllowedDelegate(const FName OwnerName, FOnIsClassPathAllowed Delegate);`
- L376 _private prototype_ `void UnregisterIsClassPathAllowedDelegate(const FName OwnerName);`
- L377 _private prototype_ `bool IsClassPathAllowed(const FTopLevelAssetPath& InClassPath) const;`
- L378 _private function_ `bool HasClassPathFiltering() const`
- L380 _private prototype_ `void RegisterIsClassAllowedOnPinDelegate(const FName OwnerName, FOnIsClassAllowed Delegate);`
- L381 _private prototype_ `void UnregisterIsClassAllowedOnPinDelegate(const FName OwnerName);`
- L382 _private prototype_ `bool IsClassAllowedOnPin(const UClass* InClass) const;`
- L383 _private function_ `bool HasClassOnPinFiltering() const`
- L385 _private prototype_ `void RegisterIsClassPathAllowedOnPinDelegate(const FName OwnerName, FOnIsClassPathAllowed Delegate);`
- L386 _private prototype_ `void UnregisterIsClassPathAllowedOnPinDelegate(const FName OwnerName);`
- L387 _private prototype_ `bool IsClassPathAllowedOnPin(const FTopLevelAssetPath& InClassPath) const;`
- L388 _private function_ `bool HasClassPathOnPinFiltering() const`
- L391 _private prototype_ `void RegisterIsFunctionAllowedForAssetDelegate(const FName OwnerName, FOnIsFunctionAllowedForAsset Delegate);` — Delegates called to determine whether a function is allowed for a given Blueprint asset
- L392 _private prototype_ `void UnregisterIsFunctionAllowedForAssetDelegate(const FName OwnerName);`
- L394 _private prototype_ `bool IsFunctionAllowed(const UBlueprint* InBlueprint, const FName InFunctionName) const;`
- L396 _private prototype_ `bool IsFunctionAllowedForAsset(const UBlueprint* InBlueprint, const FName InFunctionName) const;`
- L398 _private prototype_ `static bool IsFunctionAllowedForPermissions(const UBlueprint* InBlueprint, const FName FunctionName, const FPathPermissionList& InFunctionPermissions);`
- L402 _private member_ `FPathPermissionList FunctionPermissions;` — All function permissions
- L405 _private member_ `FPathPermissionList StructPermissions;` — All struct permissions
- L408 _private member_ `FPathPermissionList EnumPermissions;` — All enum permissions
- L411 _private member_ `FNamePermissionList PinCategoryPermissions;` — All pin category permissions
- L414 _private member_ `TMap<FName, FOnIsClassAllowed> IsClassAllowedDelegates;` — Delegates called to determine whether a class type is allowed to be displayed
- L415 _private member_ `TMap<FName, FOnIsClassPathAllowed> IsClassPathAllowedDelegates;`
- L418 _private member_ `TMap<FName, FOnIsClassAllowed> IsClassAllowedOnPinDelegates;` — Delegates called to determine whether a class type is allowed to be displayed on a pin
- L419 _private member_ `TMap<FName, FOnIsClassPathAllowed> IsClassPathAllowedOnPinDelegates;`
- L422 _private member_ `TMap<FName, FOnIsFunctionAllowedForAsset> IsFunctionAllowedForAssetDelegates;` — Delegates called to determine whether a function is allowed for a given Blueprint asset
- L426 _protected prototype_ `virtual void PostInitProperties();`
- L427 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L430 _protected prototype_ `void OnAssetRenamed(FAssetData const& AssetInfo, const FString& InOldName);`
- L432 _protected prototype_ `void OnAssetRemoved(UObject* Object);`

#### Free symbols / members of external scopes

- L32 _macro_ `#define UE_API BLUEPRINTGRAPH_API`
- L73 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon093c01530103`)

### `Source/Editor/BlueprintGraph/Public/BlueprintGraphDefinitions.h` (Public)
_(no declarations extracted)_

### `Source/Editor/BlueprintGraph/Public/BlueprintGraphModule.h` (Public)


#### class `FBlueprintGraphModule`  
`class FBlueprintGraphModule : public IModuleInterface`  
_L14-41_
- inherits: `IModuleInterface`
- L17 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FActionMenuRejectionTest, FBlueprintActionFilter const&, FBlueprintActionInfo&);`
- L29 _public function_ `TArray<FActionMenuRejectionTest>& GetExtendedActionMenuFilters()` — Provides access to a list of additional rejection tests that will be utilized when constructing Blueprint context/action menus. Helpful to game modules, so they can inject their own custom filtering (and hide options that may be undesired for their specific project). These rejection tests will be ran after all the standard filter tests, and in the order that they are in this array. @return An array of additional rejection tests for FBlueprintActionFilter.
- L31 _public prototype_ `virtual void ShutdownModule() override;`
- L32 _public prototype_ `void RegisterGraphAction(const UClass* AssetType, TUniquePtr<FAssetBlueprintGraphActions> Action);`
- L33 _public prototype_ `void UnregisterGraphAction(const UClass* AssetType);`
- L34 _public prototype_ `const FAssetBlueprintGraphActions* GetAssetBlueprintGraphActions(const UClass* AssetType) const;`
- L38 _private member_ `TMap<const UClass*, TUniquePtr< FAssetBlueprintGraphActions>> AssetBlueprintGraphActions;` — Customizations for specific assets that want to customize their interactions with the Blueprint Graph window
- L40 _private member_ `TArray<FActionMenuRejectionTest> ExtendedMenuFilters;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FActionMenuRejectionTest, FBlueprintActionFilter const&, FBlueprintActionInfo&);`

### `Source/Editor/BlueprintGraph/Public/BlueprintGraphPanelPinFactory.h` (Public)


#### class `FBlueprintGraphPanelPinFactory`  
`class FBlueprintGraphPanelPinFactory: public FGraphPanelPinFactory`  
_L13-16_
- inherits: `FGraphPanelPinFactory`
- L15 _private prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Public/BlueprintNodeSignature.h` (Public)


#### struct `FBlueprintNodeSignature`  
`struct FBlueprintNodeSignature`  
_L19-94_
- L22 _public function_ `FBlueprintNodeSignature()`
- L23 _public prototype_ `FBlueprintNodeSignature(FString const& UserString);`
- L24 _public prototype_ `FBlueprintNodeSignature(TSubclassOf<UEdGraphNode> NodeClass);`
- L32 _public prototype_ `void SetNodeClass(TSubclassOf<UEdGraphNode> NodeClass);` — @param  NodeClass @return
- L40 _public prototype_ `void AddSubObject(FFieldVariant SignatureObj);` — @param  SignatureObj @return
- L48 _public prototype_ `void AddKeyValue(FString const& KeyValue);` — @param  Value @return
- L57 _public prototype_ `void AddNamedValue(FName SignatureKey, FString const& Value);` — @param  SignatureKey @param  Value @return
- L64 _public prototype_ `bool IsValid() const;` — @return
- L71 _public prototype_ `FString const& ToString() const;` — @return
- L78 _public prototype_ `FGuid const& AsGuid() const;` — @return
- L86 _private prototype_ `void MarkDirty();` — @return
- L89 _private typedef_ `typedef TMap<FName, FString> FSignatureSet;`
- L90 _private member_ `FSignatureSet SignatureSet;`
- L92 _private member_ `mutable FGuid CachedSignatureGuid;`
- L93 _private member_ `mutable FString CachedSignatureString;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Public/BlueprintNodeSpawner.h` (Public)


#### struct `FBlueprintActionUiSpec`  
`struct FBlueprintActionUiSpec`  
_L34-103_
- L36 _public function_ `FBlueprintActionUiSpec() : IconTint(FLinearColor::White)`
- L40 _public function_ `FBlueprintActionUiSpec(FBlueprintActionUiSpec&& Other)`
- L45 _public function_ `FBlueprintActionUiSpec& operator=(FBlueprintActionUiSpec&& Other)`
- L54 _public function_ `FBlueprintActionUiSpec(const FBlueprintActionUiSpec& Other)`
- L59 _public function_ `FBlueprintActionUiSpec& operator=(const FBlueprintActionUiSpec& Other)`
- L68 _public prototype_ `~FBlueprintActionUiSpec() = default;`
- L70 _public member_ `FText MenuName;`
- L71 _public member_ `FText Category;`
- L72 _public member_ `FText Tooltip;`
- L73 _public member_ `FText Keywords;`
- L74 _public member_ `FSlateIcon Icon;`
- L75 _public member_ `FLinearColor IconTint;`
- L76 _public member_ `FString DocLink;`
- L77 _public member_ `FString DocExcerptTag;`
- L80 _private function_ `void Move(FBlueprintActionUiSpec& Other)`
- L92 _private function_ `void Copy(const FBlueprintActionUiSpec& Other)`

#### class `UBlueprintNodeSpawner`  
`class UBlueprintNodeSpawner : public UObject, public IBlueprintNodeBinder`  
_L116-298_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UObject,IBlueprintNodeBinder`
- desc: Intended to be wrapped and used by FBlueprintActionMenuItem. Rather than sub-classing the menu item, we choose to subclass this instead (for different node types). That way, we get the type inference that comes with UObjects (and we don't have to continuously compare identification strings).
- L119 _private prototype_ `DECLARE_DELEGATE_TwoParams(FCustomizeNodeDelegate, UEdGraphNode*, bool);`
- L120 _private prototype_ `DECLARE_DELEGATE_ThreeParams(FUiSpecOverrideDelegate, FBlueprintActionContext const&, FBindingSet const&, FBlueprintActionUiSpec*);`
- L133 _public prototype_ `static UBlueprintNodeSpawner* Create(TSubclassOf<UEdGraphNode> const NodeClass, UObject* Outer = nullptr, FCustomizeNodeDelegate PostSpawnDelegate = FCustomizeNodeDelegate());` — Creates a new UBlueprintNodeSpawner for the specified node class. Sets the allocated spawner's NodeClass and CustomizeNodeDelegate fields from the supplied parameters. @param  NodeClass			The node type that you want the spawner to spawn. @param  Outer				Optional outer for the new spawner (if left null, the transient package will be used). @param  PostSpawnDelegate    A delegate to perform specialized node setup post-spawn. @return A newly allocated instance of this class.
- L144 _public prototype_ `template<class NodeType> static UBlueprintNodeSpawner* Create(UObject* Outer = nullptr, FCustomizeNodeDelegate PostSpawnDelegate = FCustomizeNodeDelegate());` — Templatized version of the above Create() method (where we specify the spawner's node class through the template argument). @param  Outer				Optional outer for the new spawner (if left null, the transient package will be used). @param  PostSpawnDelegate    A delegate to perform specialized node setup post-spawn. @return A newly allocated instance of this class.
- L149 _public member_ `TSubclassOf<UEdGraphNode> NodeClass;` — `UPROPERTY()` — Holds the node type that this spawner will instantiate.
- L152 _public member_ `FBlueprintActionUiSpec DefaultMenuSignature;` — Defines how this spawner is presented in the ui
- L155 _public member_ `FCustomizeNodeDelegate CustomizeNodeDelegate;` — A delegate to perform specialized node setup post-spawn (so you don't have to sub-class this for every node type).
- L158 _public member_ `FUiSpecOverrideDelegate DynamicUiSignatureGetter;` — Provides a way to override DefaultMenuSignature based off blueprint/graph/menu context
- L161 _public prototype_ `virtual void BeginDestroy() override;` — UObject interface
- L169 _public prototype_ `virtual void Prime();` — Not required, but intended to passively help speed up menu building operations. Will cache a node-template (via GetTemplateNode), along with any expensive text strings, to avoid constructing them all on demand.
- L178 _public prototype_ `FBlueprintActionUiSpec const& PrimeDefaultUiSpec(UEdGraph* TargetGraph = nullptr) const;` — Takes the FBlueprintActionUiSpec that this was spawned with and attempts to fill in any missing fields (by polling a template node). @param  TargetGraph	Optional context for helping spawn the template node. @return This spawner's default ui spec.
- L188 _public prototype_ `virtual FBlueprintNodeSignature GetSpawnerSignature() const;` — We want to be able to compare spawners, and have a signature that is rebuildable on subsequent runs. So, what makes each spawner unique is the type of node that it spawns, and any fields the node would be initialized with; that is what this returns. @return A set of object-paths/names that distinguish this spawner from others.
- L198 _public prototype_ `virtual FBlueprintActionUiSpec GetUiSpec(FBlueprintActionContext const& Context, FBindingSet const& Bindings) const;` — Takes the default FBlueprintActionUiSpec and modifies it dynamically to accommodate the current context. @param  Context		Context that this spawner will be presented under. @param  Bindings		Bindings that will be applied to the node post-spawn. @return A ui spec, detailing how to present this action in the menu.
- L215 _public prototype_ `virtual UEdGraphNode* Invoke(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location) const;` — Takes care of spawning a node for the specified graph. Looks to see if the supplied graph is transient, and if so, spawns a NOT fully formed node (intended for template use). This function is intended to be overridden; sub-classes may return a pre-existing node, instead of a newly allocated one (for cases where only one instance of the node type can exist). Callers should check for this case upon use. @param  ParentGraph	The graph you want the node spawned into. @param  Bindings @param  Location     Where you want the new node positioned in the graph. @return Null if it failed to spawn a node, otherwise a newly spawned node or possibly one that already existed.
- L223 _public prototype_ `UEdGraphNode* GetCachedTemplateNode() const;` — Retrieves a cached template for the node that this is set to spawn. Will NOT spawn one if it is not already cached. @return The cached template-node (if one already exists for this spawner).
- L235 _public prototype_ `UEdGraphNode* GetTemplateNode(UEdGraph* TargetGraph = nullptr, FBindingSet const& Bindings = FBindingSet()) const;` — Retrieves a cached template for the node that this is set to spawn. Will instantiate a new template if one didn't previously exist. If the template-node is not compatible with any of our cached UEdGraph outers, then we use TargetGraph as a model to create one that will work. @param  TargetGraph    Optional param that defines a compatible graph outer (used as an achetype if we don't have a compatible outer on hand). @param  Bindings    	  Objects to bind to the template node @return Should return a new/cached template-node (but could be null, or some pre-existing node... depends on the sub-class's Invoke() method).
- L242 _public prototype_ `void ClearCachedTemplateNode() const;` — Removes the spawner's cached template node (if it has one), meaning that the next GetTemplateNode() call will spawn a new one (and that calls to GetCachedTemplateNode() will return null).
- L247 _public prototype_ `virtual bool IsTemplateNodeFilteredOut(FBlueprintActionFilter const& Filter) const;` — Determine if the node of this spawner's template's type should be filtered in the actions menu
- L250 _public function_ `virtual bool IsBindingCompatible(FBindingObject BindingCandidate) const override` — IBlueprintNodeBinder interface
- L251 _public function_ `virtual bool CanBindMultipleObjects() const override`
- L253 _protected function_ `virtual bool BindToNode(UEdGraphNode* Node, FBindingObject Binding) const override`
- L268 _protected prototype_ `template <class NodeType> NodeType* SpawnNode(TSubclassOf<UEdGraphNode> NodeClass, UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location, FCustomizeNodeDelegate PostSpawnDelegate) const;` — Protected SpawnNode() that let's sub-classes specify their own post-spawn delegate and node class. @param  NodeClass			The type of node you want spawned. @param  ParentGraph			The graph you want the node spawned into. @param  Bindings				The bindings to apply to the node (post spawn). @param  Location				Where you want the new node positioned in the graph. @param  PostSpawnDelegate	A delegate to run after spawning the node, but prior to allocating the node's pins. @return Null if it failed to spawn a node (if NodeClass is null), otherwise a newly spawned node.
- L282 _protected prototype_ `template <class NodeType> NodeType* SpawnNode(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location, FCustomizeNodeDelegate PostSpawnDelegate) const;` — Simplified version of the other SpawnNode(), that just let's sub-classes specify their own post-spawn delegate (the node class is comes directly from the template parameter). @param  ParentGraph			The graph you want the node spawned into. @param  Bindings				The bindings to apply to the node (post spawn). @param  Location				Where you want the new node positioned in the graph. @param  PostSpawnDelegate	A delegate to run after spawning the node, but prior to allocating the node's pins. @return Null if it failed to spawn a node (if NodeClass is null), otherwise a newly spawned node.
- L297 _private prototype_ `UEdGraphNode* SpawnEdGraphNode(TSubclassOf<UEdGraphNode> NodeClass, UEdGraph* ParentGraph, const FBindingSet& Bindings, FVector2D Location, FCustomizeNodeDelegate PostSpawnDelegate) const;` — Does the actual node spawning. Creates a new node (of the specified type), sets the node's position, calls PostSpawnDelegate on the new node, and finally applies any bindings that were passed to it. @param  NodeClass			The type of node you want spawned. @param  ParentGraph			The graph you want the node spawned into. @param  Bindings				The bindings to apply to the node (post spawn). @param  Location				Where you want the new node positioned in the graph. @param  PostSpawnDelegate	A delegate to run after spawning the node, but prior to allocating the node's pins. @return Null if it failed to spawn a node (if NodeClass is null), otherwise a newly spawned node.
- L306 _function_ `template<class NodeType> UBlueprintNodeSpawner* UBlueprintNodeSpawner::Create(UObject* Outer, FCustomizeNodeDelegate PostSpawnDelegate)`
- L313 _function_ `template <class NodeType> NodeType* UBlueprintNodeSpawner::SpawnNode(TSubclassOf<UEdGraphNode> InNodeClass, UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location, FCustomizeNodeDelegate PostSpawnDelegate) const`
- L320 _function_ `template <class NodeType> NodeType* UBlueprintNodeSpawner::SpawnNode(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location, FCustomizeNodeDelegate PostSpawnDelegate) const`

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API BLUEPRINTGRAPH_API`
- L119 _delegate_ `DECLARE_DELEGATE_TwoParams(FCustomizeNodeDelegate, UEdGraphNode*, bool);`
- L120 _delegate_ `DECLARE_DELEGATE_ThreeParams(FUiSpecOverrideDelegate, FBlueprintActionContext const&, FBindingSet const&, FBlueprintActionUiSpec*);`

### `Source/Editor/BlueprintGraph/Public/BlueprintNodeStatics.h` (Public)


#### class `FBlueprintNodeStatics`  
`class FBlueprintNodeStatics`  
_L15-22_
- L19 _public prototype_ `static UEdGraphPin* CreateSelfPin(UK2Node* Node, const UFunction* Function);`
- L21 _public prototype_ `static bool CreateParameterPinsForFunction(UK2Node* Node, const UFunction* Function, TFunctionRef<void(UEdGraphPin* )> PostParameterPinCreatedCallback);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Public/BlueprintNodeTemplateCache.h` (Public)


#### class `FBlueprintNodeTemplateCache`  
`class FBlueprintNodeTemplateCache : public FGCObject`  
_L28-142_
- inherits: `FGCObject`
- desc: Serves as a centralized data-store for all UBlueprintNodeSpawner node- templates. Implemented this way (rather than internal to UBlueprintNodeSpawner) since node-templates require a UEdGraph/UBlueprint outer chain. Instead of instantiating a bunch of graphs/blueprints per UBlueprintNodeSpawner, we'd rather have a small centralized set here.
- L32 _public prototype_ `FBlueprintNodeTemplateCache();`
- L44 _public prototype_ `UEdGraphNode* GetNodeTemplate(UBlueprintNodeSpawner const* NodeSpawner, UEdGraph* TargetGraph = nullptr);` — Retrieves a cached template associated with the supplied spawner. Will instantiate a new template if one didn't already exist. If the template-node is not compatible with any cached UEdGraph outer, then we use TargetGraph as a model to create one that will work. @param  NodeSpawner	Acts as the key for the template lookup; takes care of spawning the template-node if one didn't already exist. @param  TargetGraph	Optional param that defines a compatible graph outer (used as an achetype if we don't have a compatible outer on hand). @return Should return a new/cached template-node (but could be null, or some pre-existing node... depends on the sub-class's Invoke() method).
- L54 _public prototype_ `UEdGraphNode* GetNodeTemplate(UBlueprintNodeSpawner const* NodeSpawner, ENoInit) const;` — Retrieves a cached template associated with the supplied spawner. Does NOT attempt to allocate one if it doesn't exist. @param  NodeSpawner	The spawner you want a template node for. @param  ENoInit Signifies to use this function over the other (mutating) GetNodeTemplate(). @return Should return the cached template-node (if one exists, otherwise false).
- L63 _public prototype_ `void ClearCachedTemplate(UBlueprintNodeSpawner const* NodeSpawner);` — Wipes any nodes that were cached on behalf of the specified spawner (should be called when NodeSpawner is destroyed, in case GetNodeTemplate() was called for it). @param  NodeSpawner	The spawner we want cached node-templates cleared for.
- L72 _public prototype_ `static bool IsTemplateOuter(UEdGraph* ParentGraph);` — Utility method to help external systems identify if a graph they have belongs here, to the FBlueprintNodeTemplateCache system. @param  ParentGraph	The graph you want to check. @return True if the graph was allocated by a FBlueprintNodeTemplateCache (to house template nodes).
- L80 _public prototype_ `int64 GetEstimateCacheSize() const;` — Approximates the current memory footprint of the entire cache (instantiated UObject sizes + allocated container space). @return The approximated total (in bytes) that this cache has allocated.
- L90 _public prototype_ `int64 RecalculateCacheSize();` — External systems can make changes that alter the memory footprint of the cache (like calling AllocateDefaultPins), and since we don't recalculate the cache's size every frame sometimes we need to update the internal estimate. @return The new approximated total (in bytes) that this cache has allocated.
- L93 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L94 _public prototype_ `virtual FString GetReferencerName() const override;`
- L107 _private prototype_ `bool CacheBlueprintOuter(UBlueprint* Blueprint);` — Caches the supplied blueprint, so that it may be reused as an outer for template nodes (certain nodes types assume they'll have a graph outer, with a blueprint outer beyond that, so we cannot just spawn nodes into the transient package). @param  Blueprint	The blueprint you wish to store for reuse. @return True if the blueprint was successfully cached (the cache could be full, and therefore this could fail).
- L117 _private prototype_ `bool CacheTemplateNode(UBlueprintNodeSpawner const* NodeSpawner, UEdGraphNode* NewNode);` — Attempts to cache the supplied node, and associates it with the specified spawner (so that we can remove it later if it is no longer needed). @param  NodeSpawner	Acts as the key for the given template node. @param  NewNode		The template node you want stored. @return True if the node was successfully cached (the cache could be full, and therefore this could fail).
- L130 _private member_ `TArray<TObjectPtr<UBlueprint>> TemplateOuters;` — Unfortunately, we cannot nest template-nodes in the transient package. Certain nodes operate on the assumption that they have a UEdGraph outer, while a certain subset expect the graph to have a UBlueprint outer. This means we cannot spawn templates without a blueprint/graph to add them to. This array holds intermediate blueprints that we use to parent the template-nodes. Ideally we only need a small handful that are compatible with all nodes.
- L133 _private member_ `TMap<UBlueprintNodeSpawner const*, TObjectPtr<UEdGraphNode>> NodeTemplateCache;`
- L141 _private member_ `int64 ApproximateObjectMem;` — It can be costly to tally back up the estimated cache size every time an entry is added, so we keep this approximate tally of memory allocated for UObjects (owned by this system).

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API BLUEPRINTGRAPH_API`

### `Source/Editor/BlueprintGraph/Public/CallFunctionHandler.h` (Public)


#### class `FKCHandler_CallFunction`  
`class FKCHandler_CallFunction : public FNodeHandlingFunctor`  
_L24-56_
- inherits: `FNodeHandlingFunctor`
- L27 _public function_ `FKCHandler_CallFunction(FKismetCompilerContext& InCompilerContext) : FNodeHandlingFunctor(InCompilerContext)`
- L36 _public prototype_ `void CreateFunctionCallStatement(FKismetFunctionContext& Context, UEdGraphNode* Node, UEdGraphPin* SelfPin);` — Searches for the function referenced by a graph node in the CallingContext class's list of functions, validates that the wiring matches up correctly, and creates an execution statement.
- L40 _private prototype_ `virtual FName GetFunctionNameFromNode(UEdGraphNode* Node) const;` — Get the name of the function to call from the node
- L41 _private prototype_ `UClass* GetCallingContext(FKismetFunctionContext& Context, UEdGraphNode* Node);`
- L42 _private prototype_ `UClass* GetTrueCallingClass(FKismetFunctionContext& Context, UEdGraphPin* SelfPin);`
- L46 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L47 _public prototype_ `virtual void RegisterNet(FKismetFunctionContext& Context, UEdGraphPin* Net) override;`
- L48 _public prototype_ `virtual UFunction* FindFunction(FKismetFunctionContext& Context, UEdGraphNode* Node);`
- L49 _public prototype_ `virtual void Transform(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L50 _public prototype_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L51 _public prototype_ `virtual void CheckIfFunctionIsCallable(UFunction* Function, FKismetFunctionContext& Context, UEdGraphNode* Node);`
- L52 _public function_ `virtual void AdditionalCompiledStatementHandling(FKismetFunctionContext& Context, UEdGraphNode* Node, FBlueprintCompiledStatement& Statement)`
- L55 _private member_ `TMap<UEdGraphPin*, FBPTerminal*> InterfaceTermMap;`

### `Source/Editor/BlueprintGraph/Public/EventEntryHandler.h` (Public)


#### class `FKCHandler_EventEntry`  
`class FKCHandler_EventEntry : public FNodeHandlingFunctor`  
_L16-26_
- inherits: `FNodeHandlingFunctor`
- L19 _public function_ `FKCHandler_EventEntry(FKismetCompilerContext& InCompilerContext) : FNodeHandlingFunctor(InCompilerContext)`
- L24 _public prototype_ `virtual void RegisterNet(FKismetFunctionContext& Context, UEdGraphPin* Net) override;`
- L25 _public prototype_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`

### `Source/Editor/BlueprintGraph/Public/MathExpressionHandler.h` (Public)


#### class `FKCHandler_MathExpression`  
`class FKCHandler_MathExpression : public FNodeHandlingFunctor`  
_L18-36_
- inherits: `FNodeHandlingFunctor`
- L20 _private prototype_ `FBlueprintCompiledStatement* GenerateFunctionRPN(UEdGraphNode* CurrentNode , FKismetFunctionContext& Context , UK2Node_MathExpression& MENode , FBPTerminal* ResultTerm , TMap<UEdGraphPin*, UEdGraphPin*>& InnerToOuterInput);`
- L27 _public function_ `FKCHandler_MathExpression(FKismetCompilerContext& InCompilerContext) : FNodeHandlingFunctor(InCompilerContext)`
- L31 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* InNode) override;`
- L32 _public prototype_ `virtual void RegisterNet(FKismetFunctionContext& Context, UEdGraphPin* Net) override;`
- L33 _public prototype_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L35 _public prototype_ `static bool CanBeCalledByMathExpression(const UFunction* Function);`

### `Source/Editor/BlueprintGraph/Public/VariableSetHandler.h` (Public)


#### class `FKCHandler_VariableSet`  
`class FKCHandler_VariableSet : public FNodeHandlingFunctor`  
_L16-36_
- inherits: `FNodeHandlingFunctor`
- L19 _public function_ `FKCHandler_VariableSet(FKismetCompilerContext& InCompilerContext) : FNodeHandlingFunctor(InCompilerContext)`
- L24 _public prototype_ `virtual void RegisterNet(FKismetFunctionContext& Context, UEdGraphPin* Net) override;`
- L25 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L26 _public prototype_ `void InnerAssignment(FKismetFunctionContext& Context, UEdGraphNode* Node, UEdGraphPin* VariablePin, UEdGraphPin* ValuePin);`
- L27 _public prototype_ `void GenerateAssigments(FKismetFunctionContext& Context, UEdGraphNode* Node);`
- L28 _public prototype_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L29 _public prototype_ `virtual void Transform(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L35 _protected function_ `virtual bool UsesVariablePinAsKey() const` — Used for implicit casting. Some nodes need to use the variable pin when performing a lookup in the implicit cast table.
