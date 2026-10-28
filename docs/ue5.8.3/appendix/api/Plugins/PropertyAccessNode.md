# Plugins / PropertyAccessNode

- module root: `Plugins/Developer/PropertyAccessNode/Source/PropertyAccessNode`
- headers: 4; symbols: 55
- symbol kinds: class=3, function=12, member=11, prototype=29
- PrivateDependencyModuleNames: AnimGraph, BlueprintGraph, Core, CoreUObject, Engine, GraphEditor, InputCore, KismetCompiler, KismetWidgets, PropertyAccessEditor, Slate, SlateCore, UnrealEd

### `Plugins/Developer/PropertyAccessNode/Source/PropertyAccessNode/Private/K2Node_PropertyAccess.h` (Private)


#### class `UK2Node_PropertyAccess`  
`class UK2Node_PropertyAccess : public UK2Node, public IClassVariableCreator`  
_L15-131_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,IClassVariableCreator`
- L21 _public prototype_ `void SetPath(const TArray<FString>& InPath);` — Set the path and attempt to resolve the leaf property.
- L22 _public prototype_ `void SetPath(TArray<FString>&& InPath);`
- L25 _public prototype_ `void ClearPath();` — Clear the path
- L28 _public function_ `const TArray<FString>& GetPath() const` — Get the path
- L31 _public function_ `const FText& GetTextPath() const` — Get the path as text
- L34 _public prototype_ `const FProperty* GetResolvedProperty() const;` — Get the resolved leaf property, if any.
- L37 _public function_ `int32 GetResolvedArrayIndex() const` — Get the resolved leaf property's array index, if any.
- L40 _public function_ `const FEdGraphPinType& GetResolvedPinType() const` — Get the resolved pin type, if any.
- L43 _public prototype_ `bool HasResolvedPinType() const;` — Check whether we have a resolved pin type
- L46 _public function_ `UEdGraphPin* GetOutputPin() const` — Get the output pin
- L49 _public function_ `FName GetContextId() const` — Get the context Id
- L52 _public function_ `void SetContextId(const FName& InContextId)` — Set the context Id
- L55 _public function_ `const FText& GetCompiledContext() const` — Get the the context that this access was assigned during compilation. This can be empty.
- L58 _public function_ `const FText& GetCompiledContextDesc() const` — Get the description of the context that this access was assigned during compilation. This can be empty.
- L63 _private member_ `TArray<FString> Path;` — `UPROPERTY()` — Path that this access exposes
- L67 _private member_ `FText TextPath;` — `UPROPERTY()` — Path as text, for display
- L71 _private member_ `FEdGraphPinType ResolvedPinType;` — `UPROPERTY()` — Resolved pin type
- L75 _private member_ `FName GeneratedPropertyName = NAME_None;` — `UPROPERTY()` — Generated property created during compilation
- L79 _private member_ `FName ContextId;` — `UPROPERTY()` — Property access context (set by the user) that is intended to be used
- L82 _private member_ `mutable TFieldPath<FProperty> ResolvedProperty;` — Resolved leaf property for the path, NULL if path cant be resolved or is empty.
- L85 _private member_ `mutable int32 ResolvedArrayIndex = INDEX_NONE;` — Resolved array index, if the leaf property is an array. If this is INDEX_NONE then the property refers to the entire array
- L88 _private member_ `mutable bool bWasResolvedThreadSafe = false;` — Whether the path was resolved as thread safe the last time the ResolvedProperty was updated
- L91 _private member_ `FDelegateHandle PostLibraryCompiledHandle;` — Handle used to hook into property access compilation machinery
- L94 _private member_ `FText CompiledContext;` — The context that this access was assigned during compilation
- L97 _private member_ `FText CompiledContextDesc;` — Description of the context that this access was assigned during compilation (used for tooltips)
- L100 _private prototype_ `virtual void CreateClassVariablesFromBlueprint(IAnimBlueprintVariableCreationContext& InCreationContext) override;` — IClassVariableCreator interface
- L103 _private prototype_ `virtual void PostEditUndo() override;` — UObject interface
- L106 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L107 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L108 _private prototype_ `virtual void AddPinSearchMetaDataInfo(const UEdGraphPin* InPin, TArray<FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L109 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L110 _private prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* TargetGraph) const override;`
- L113 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;` — UK2Node interface
- L114 _private prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L115 _private function_ `virtual bool IsNodePure() const override`
- L116 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L117 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L118 _private function_ `virtual bool DrawNodeAsVariable() const override`
- L119 _private prototype_ `virtual FText GetTooltipText() const override;`
- L120 _private prototype_ `virtual void HandleVariableRenamed(UBlueprint* InBlueprint, UClass* InVariableClass, UEdGraph* InGraph, const FName& InOldVarName, const FName& InNewVarName) override;`
- L121 _private prototype_ `virtual void HandleFunctionRenamed(UBlueprint* InBlueprint, UClass* InFunctionClass, UEdGraph* InGraph, const FName& InOldFuncName, const FName& InNewFuncName) override;`
- L122 _private prototype_ `virtual void ReplaceReferences(UBlueprint* InBlueprint, UBlueprint* InReplacementBlueprint, const FMemberReference& InSource, const FMemberReference& InReplacement) override;`
- L123 _private prototype_ `virtual bool ReferencesVariable(const FName& InVarName, const UStruct* InScope) const override;`
- L124 _private prototype_ `virtual bool ReferencesFunction(const FName& InFunctionName,const UStruct* InScope) const override;`
- L127 _private prototype_ `void AllocatePins(UEdGraphPin* InOldOutputPin = nullptr);` — Helper function for pin allocation
- L130 _private prototype_ `void ResolvePropertyAccess() const;` — Attempt to resolve the path to a leaf property. Const function that modifies mutable internally cached values

### `Plugins/Developer/PropertyAccessNode/Source/PropertyAccessNode/Private/PropertyAccessNodeFactory.h` (Private)


#### class `FPropertyAccessNodeFactory`  
`class FPropertyAccessNodeFactory : public FGraphPanelNodeFactory`  
_L7-11_
- inherits: `FGraphPanelNodeFactory`
- L10 _private prototype_ `virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* InNode) const override;` — FGraphPanelNodeFactory interface

### `Plugins/Developer/PropertyAccessNode/Source/PropertyAccessNode/Private/PropertyAccessNodeLibrary.h` (Private)
_(no declarations extracted)_

### `Plugins/Developer/PropertyAccessNode/Source/PropertyAccessNode/Private/SPropertyAccessNode.h` (Private)


#### class `SPropertyAccessNode`  
`class SPropertyAccessNode : public SGraphNodeK2Var`  
_L9-25_
- inherits: `SGraphNodeK2Var`
- L12 _public function_ `SLATE_BEGIN_ARGS(SPropertyAccessNode)`
- L16 _public prototype_ `void Construct(const FArguments& InArgs, UK2Node_PropertyAccess* InNode);`
- L19 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;` — SGraphNode interface
- L20 _public prototype_ `virtual TSharedRef<SWidget> UpdateTitleWidget(FText InTitleText, TSharedPtr<SWidget> InTitleWidget, EHorizontalAlignment& InOutTitleHAlign, FMargin& InOutTitleMargin) const override;`
- L24 _private prototype_ `bool CanBindProperty(FProperty* InProperty) const;` — Helper for property/function binding
