# Plugins / WebAPIBlueprintGraph

- module root: `Plugins/Experimental/Web/WebAPI/Source/WebAPIBlueprintGraph`
- headers: 4; symbols: 84
- symbol kinds: class=1, delegate=2, enum=1, enumerator=2, function=5, member=12, namespace=7, prototype=49, struct=2, variable=3
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, AssetTools, BlueprintGraph, Core, CoreUObject, EditorStyle, Engine, GraphEditor, InputCore, Json, Kismet, KismetCompiler, KismetWidgets, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd, WebAPI

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIBlueprintGraph/Private/K2Node_WebAPIOperation.h` (Private)


#### struct `UE::WebAPI::Private::FOutputPinAndLocalVariable`  
`struct FOutputPinAndLocalVariable`  
_L19-27_
- L21 _public member_ `UEdGraphPin* OutputPin;`
- L22 _public member_ `UK2Node_TemporaryVariable* TempVar;`
- L24 _public function_ `FOutputPinAndLocalVariable(UEdGraphPin* Pin, UK2Node_TemporaryVariable* Var) : OutputPin(Pin) , TempVar(Var)`

#### enum `EWebAPIOperationAsyncType`  
`enum class EWebAPIOperationAsyncType : uint8`  
_L32-36_
- reflection: `UENUM()`
- L34 _public enumerator_ `LatentAction = 0`
- L35 _public enumerator_ `Callback = 1`

#### class `UK2Node_WebAPIOperation`  
`class UK2Node_WebAPIOperation : public UK2Node`  
_L42-188_
- reflection: `UCLASS()`
- inherits: `UK2Node`
- L49 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L50 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L51 _public prototype_ `virtual FText GetTooltipText() const override;`
- L52 _public prototype_ `virtual void ReconstructNode() override;`
- L53 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L54 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L55 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L56 _public prototype_ `virtual void PostPasteNode() override;`
- L57 _public prototype_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;`
- L61 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;` — UK2Node interface
- L62 _public prototype_ `virtual FName GetCornerIcon() const override;`
- L63 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L64 _public prototype_ `virtual void PostReconstructNode() override;`
- L68 _public prototype_ `void SetAsyncType(EWebAPIOperationAsyncType InAsyncType);` — Set the operation call type. If it differs from the current, the node will be re-arranged to suit the new type.
- L71 _public prototype_ `bool IsValid() const;` — Validity of this node.
- L75 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — Add node validity to data validation messages.
- L80 _protected prototype_ `virtual UFunction* GetFactoryFunction() const;` — Returns the factory function (checked)
- L83 _protected prototype_ `virtual void GetRedirectPinNames(const UEdGraphPin& Pin, TArray<FString>& RedirectPinNames) const override;` — Determines what the possible redirect pin names are
- L96 _protected prototype_ `bool ExpandDefaultToSelfPin(FKismetCompilerContext& InCompilerContext, UEdGraph* InSourceGraph, UK2Node_CallFunction* InIntermediateProxyNode);` — If a the DefaultToSelf pin exists then it needs an actual connection to get properly casted during compilation. @param InCompilerContext			The current compiler context used during expansion @param InSourceGraph				The graph to place the expanded self node on @param InIntermediateProxyNode		The spawned intermediate proxy node that has a DefaultToSelfPin @return	True if a successful connection was made to an intermediate node or if one was not necessary. False if a connection was failed.
- L99 _protected prototype_ `virtual bool HandleDelegates( const TArray<UE::WebAPI::Private::FOutputPinAndLocalVariable>& VariableOutputs, UEdGraphPin* ProxyObjectPin, UEdGraphPin*& InOutLastThenPin, UEdGraph* SourceGraph, FKismetCompilerContext& CompilerContext);` — Expand out the logic to handle the delegate output pins
- L104 _protected prototype_ `bool CacheOutcomeDelegates();` — Checks and caches outcome (success, error) delegates, returning true if both resolved.
- L107 _protected prototype_ `void InvalidatePinTooltips();` — Invalidates current pin tool tips, so that they will be refreshed before being displayed:
- L115 _private prototype_ `UEdGraphPin* FindPin( const FName& InName, const EEdGraphPinDirection& InDirection = EEdGraphPinDirection::EGPD_MAX, const FName& InCategory = NAME_All, bool bFindPartial = false) const;` — Find a single pin according to various criteria.
- L122 _private prototype_ `TArray<UEdGraphPin*> FindPins( const FString& InName, const EEdGraphPinDirection& InDirection = EEdGraphPinDirection::EGPD_MAX, bool bOnlySplitPins = true) const;` — Find multiple pins according to various criteria.
- L127 _private prototype_ `UEdGraphPin* FindThenPin() const;`
- L130 _private prototype_ `TArray<UEdGraphPin*> GetRequestPins() const;` — Get all input pins that correspond to operation parameters.
- L133 _private prototype_ `TArray<UEdGraphPin*> GetRequestDelegatePins() const;` — Get both input request delegate pins, will return empty if this is Latent.
- L136 _private prototype_ `TArray<UEdGraphPin*> GetResponsePins() const;` — Get all (non-exec, non-error) output pins, will return empty if this uses Callbacks.
- L139 _private prototype_ `TArray<UEdGraphPin*> GetResponseExecPins() const;` — Get both outcome exec pins, will return empty if this uses Callbacks.
- L142 _private prototype_ `TArray<UEdGraphPin*> GetErrorResponsePins() const;` — Get all error output pins, will return empty if this uses Callbacks.
- L145 _private prototype_ `class UK2Node_CustomEvent* MakeCustomEvent(const FName& InName, const UFunction* InSignature, const FVector2D& InPosition = {});` — Make and return a custom event in either the calling graph (if not function), or event graph.
- L150 _private prototype_ `static const UK2Node_CustomEvent* GetCustomEventForOutcomeDelegate(const UK2Node_WebAPIOperation* InNode, const FName& InOutcomeName);` — Get or make a custom event node for the supplied outcome.
- L153 _private prototype_ `void ConvertLatentToCallback();` — Called when converting FROM latent TO callback.
- L156 _private prototype_ `void ConvertCallbackToLatent();` — Called when converting FROM callback TO latent.
- L159 _private prototype_ `void ToggleAsyncType();` — Flips the node's Async Type.
- L163 _private member_ `TObjectPtr<UClass> OperationClass;` — `UPROPERTY()` — The class containing the operation functions, AND is the return type of the latent function.
- L167 _private member_ `FName LatentFunctionName;` — `UPROPERTY()` — The name of the latent function to call to create an operation object.
- L171 _private member_ `FName DelegatedFunctionName;` — `UPROPERTY()` — The name of the delegated function to call to create an operation object.
- L174 _private member_ `TWeakFieldPtr<FMulticastDelegateProperty> PositiveDelegateProperty;` — Reference to the operations' positive outcome delegate property.
- L177 _private member_ `TWeakFieldPtr<FMulticastDelegateProperty> NegativeDelegateProperty;` — Reference to the operations' negative outcome delegate property.
- L181 _private member_ `EWebAPIOperationAsyncType OperationAsyncType = EWebAPIOperationAsyncType::LatentAction;` — `UPROPERTY()` — Latent Action is preferred, but not compatible when used in a function, so allow conversion between the two.
- L184 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's tooltip
- L187 _private member_ `mutable bool bPinTooltipsValid;` — Flag used to track validity of pin tooltips, when tooltips are invalid they will be refreshed before being displayed

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace WebAPI` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::WebAPI`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIBlueprintGraph/Private/WebAPIBlueprintGraphLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebAPIBlueprintGraph, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebAPIBlueprintGraph, Log, All);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIBlueprintGraph/Private/WebAPIBlueprintGraphStats.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_STATS_GROUP(TEXT("WebAPIBlueprintGraph"), STATGROUP_WebAPIBlueprintGraph`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIBlueprintGraph/Private/WebAPIBlueprintGraphUtilities.h` (Private)


#### struct `UE::WebAPI::Operation::FCachedOutcome`  
`struct FCachedOutcome`  
_L17-48_
- desc: Stores references to outcome delegate properties for a given operation.
- L20 _public member_ `TWeakFieldPtr<const FMulticastDelegateProperty> PositiveOutcomeDelegate;`
- L21 _public member_ `TWeakFieldPtr<const FMulticastDelegateProperty> NegativeOutcomeDelegate;`
- L24 _public function_ `template <uint32 Index, typename TEnableIf<Index < 2>::Type* = nullptr> const TWeakFieldPtr<const FMulticastDelegateProperty>& Get() const`
- L37 _public function_ `template <uint32 Index, typename TEnableIf<Index < 2>::Type* = nullptr> void Set(const FMulticastDelegateProperty* InDelegateProperty)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace WebAPI` (scope `UE`)
- L14 _namespace_ `namespace Operation` (scope `UE::WebAPI`)
- L51 _variable_ `inline const static FName PositiveOutcomeName = TEXT("Suc` (scope `UE::WebAPI::Operation`) — String denoting a positive outcome, should match generated delegate name.
- L54 _variable_ `inline const static FName NegativeOutcomeName = TEXT("Err` (scope `UE::WebAPI::Operation`) — String denoting a negative outcome, should match generated delegate name.
- L57 _variable_ `static TMap<FName, FCachedOutcome> CachedOutcomeDelegates;` (scope `UE::WebAPI::Operation`) — Cached positive and negative (in order) delegates per operation class (name).
- L59 _prototype_ `const FMulticastDelegateProperty* GetPositiveOutcomeDelegate(const TSubclassOf<UWebAPIOperationObject>& InOperationClass);` (scope `UE::WebAPI::Operation`)
- L62 _function_ `template <class OperationType = UWebAPIOperationObject> const FMulticastDelegateProperty* GetPositiveOutcomeDelegate()` (scope `UE::WebAPI::Operation`)
- L67 _prototype_ `const FMulticastDelegateProperty* GetNegativeOutcomeDelegate(const TSubclassOf<UWebAPIOperationObject>& InOperationClass);` (scope `UE::WebAPI::Operation`)
- L70 _function_ `template <class OperationType = UWebAPIOperationObject> const FMulticastDelegateProperty* GetNegativeOutcomeDelegate()` (scope `UE::WebAPI::Operation`)
- L75 _prototype_ `UFunction* GetOutcomeDelegateSignatureFunction(const TSubclassOf<UWebAPIOperationObject>& InOperationClass);` (scope `UE::WebAPI::Operation`)
- L78 _namespace_ `namespace Graph` (scope `UE::WebAPI`)
- L81 _prototype_ `void TransferPinConnections(const UEdGraphPin* InSrc, UEdGraphPin* InDst);` (scope `UE::WebAPI::Graph`) — Connects all pins linked to src, to dst.
- L84 _prototype_ `void TransferPins(const TArray<UEdGraphPin*>& InSrcPins, const TArray<UEdGraphPin*>& InDstPins);` (scope `UE::WebAPI::Graph`) — Connects all pins linked to all src pins, to matching (same named) dst pins.
- L87 _prototype_ `bool SplitPins(const TArray<UEdGraphPin*>& InPins);` (scope `UE::WebAPI::Graph`) — Split multiple pins according to various criteria, like unwrapping single property structs, etc.
- L90 _prototype_ `bool SplitPin(UEdGraphPin* InPin);` (scope `UE::WebAPI::Graph`) — Split single pin according to various criteria, like unwrapping single property structs, etc.
- L93 _prototype_ `TArray<UEdGraphPin*> FilterPinsByRelated(const UEdGraphPin* InExecutionPin, const TArray<UEdGraphPin*>& InPinsToFilter);` (scope `UE::WebAPI::Graph`) — Filter the inputs pins by the input execution chain (like "Hide Unrelated").
- L96 _prototype_ `UEdGraphPin* FindPin( const UEdGraphNode* InNode, const FName& InName, const EEdGraphPinDirection& InDirection = EEdGraphPinDirection::EGPD_MAX, const FName& InCategory = NAME_All, bool bFindPartial = false);` (scope `UE::WebAPI::Graph`) — Find a single pin according to various criteria.
- L104 _prototype_ `TArray<UEdGraphPin*> FindPins( const UEdGraphNode* InNode, const FString& InName, const EEdGraphPinDirection& InPinDirection, bool bOnlySplitPins = true);` (scope `UE::WebAPI::Graph`) — Find multiple pins according to various criteria.
- L111 _prototype_ `TArray<UEdGraphPin*> GetResponsePins(const UEdGraphNode* InNode);` (scope `UE::WebAPI::Graph`) — Get all (non-exec, non-error) output pins, will return empty if this uses Callbacks.
- L114 _prototype_ `TArray<UEdGraphPin*> GetErrorResponsePins(const UEdGraphNode* InNode);` (scope `UE::WebAPI::Graph`) — Get all error output pins, will return empty if this uses Callbacks.
- L117 _prototype_ `void CleanupPinNameInline(FString& InPinName);` (scope `UE::WebAPI::Graph`) — Returns the last part of a string, split by underscores.
