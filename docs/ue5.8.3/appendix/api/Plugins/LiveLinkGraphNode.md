# Plugins / LiveLinkGraphNode

- module root: `Plugins/Animation/LiveLink/Source/LiveLinkGraphNode`
- headers: 5; symbols: 94
- symbol kinds: class=8, function=3, macro=4, member=4, namespace=3, prototype=72
- PrivateDependencyModuleNames: BlueprintGraph, Core, CoreUObject, Engine, KismetCompiler, LiveLink, LiveLinkAnimationCore, LiveLinkInterface, SlateCore, UnrealEd
- PublicDependencyModuleNames: AnimGraph

### `Plugins/Animation/LiveLink/Source/LiveLinkGraphNode/Private/K2Node_EvaluateLiveLinkCustom.h` (Private)


#### class `UK2Node_EvaluateLiveLinkFrameWithSpecificRole`  
`class UK2Node_EvaluateLiveLinkFrameWithSpecificRole : public UK2Node_EvaluateLiveLinkFrame`  
_L12-22_
- reflection: `UCLASS()`
- inherits: `UK2Node_EvaluateLiveLinkFrame`
- L17 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L18 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L20 _public prototype_ `virtual FName GetEvaluateFunctionName() const override;`
- L21 _public prototype_ `virtual void AddPins(FKismetCompilerContext& CompilerContext, UK2Node_CallFunction* EvaluateLiveLinkFrameFunction) override;`

#### class `UK2Node_EvaluateLiveLinkFrameAtWorldTime`  
`class UK2Node_EvaluateLiveLinkFrameAtWorldTime : public UK2Node_EvaluateLiveLinkFrame`  
_L25-35_
- reflection: `UCLASS()`
- inherits: `UK2Node_EvaluateLiveLinkFrame`
- L30 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L31 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L33 _public prototype_ `virtual FName GetEvaluateFunctionName() const override;`
- L34 _public prototype_ `virtual void AddPins(FKismetCompilerContext& CompilerContext, UK2Node_CallFunction* EvaluateLiveLinkFrameFunction) override;`

#### class `UK2Node_EvaluateLiveLinkFrameAtSceneTime`  
`class UK2Node_EvaluateLiveLinkFrameAtSceneTime : public UK2Node_EvaluateLiveLinkFrame`  
_L38-48_
- reflection: `UCLASS()`
- inherits: `UK2Node_EvaluateLiveLinkFrame`
- L43 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L44 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L46 _public prototype_ `virtual FName GetEvaluateFunctionName() const override;`
- L47 _public prototype_ `virtual void AddPins(FKismetCompilerContext& CompilerContext, UK2Node_CallFunction* EvaluateLiveLinkFrameFunction) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/Animation/LiveLink/Source/LiveLinkGraphNode/Private/K2Node_UpdateVirtualSubjectDataTyped.h` (Private)


#### class `UK2Node_UpdateVirtualSubjectStaticData`  
`class UK2Node_UpdateVirtualSubjectStaticData : public UK2Node_UpdateVirtualSubjectDataBase`  
_L11-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_UpdateVirtualSubjectDataBase`
- L18 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L24 _protected prototype_ `virtual UScriptStruct* GetStructTypeFromRole(ULiveLinkRole* Role) const override;`
- L25 _protected prototype_ `virtual FName GetUpdateFunctionName() const override;`
- L26 _protected prototype_ `virtual FText GetStructPinName() const override;`
- L27 _protected function_ `virtual void AddPins(FKismetCompilerContext& CompilerContext, UK2Node_CallFunction* UpdateVirtualSubjectDataFunction) const override`

#### class `UK2Node_UpdateVirtualSubjectFrameData`  
`class UK2Node_UpdateVirtualSubjectFrameData : public UK2Node_UpdateVirtualSubjectDataBase`  
_L32-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_UpdateVirtualSubjectDataBase`
- L39 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L40 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L46 _protected prototype_ `virtual UScriptStruct* GetStructTypeFromRole(ULiveLinkRole* Role) const override;`
- L47 _protected prototype_ `virtual FName GetUpdateFunctionName() const override;`
- L48 _protected prototype_ `virtual FText GetStructPinName() const override;`
- L49 _protected prototype_ `virtual void AddPins(FKismetCompilerContext& CompilerContext, UK2Node_CallFunction* UpdateVirtualSubjectDataFunction) const override;`
- L53 _protected prototype_ `UEdGraphPin* GetTimestampFramePin() const;` — Returns the Timestamp pin
- L58 _private member_ `static const FName LiveLinkTimestampFramePinName;` — Name of the pin to enable/disable timestamping

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINKGRAPHNODE_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkGraphNode/Public/AnimGraphNode_LiveLinkPose.h` (Public)


#### class `UAnimGraphNode_LiveLinkPose`  
`class UAnimGraphNode_LiveLinkPose : public UAnimGraphNode_Base`  
_L17-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L24 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L26 _public prototype_ `virtual FText GetMenuCategory() const;`
- L30 _public prototype_ `virtual void ConvertDeprecatedNode(UEdGraph* Graph, bool bOnlySafeChanges) override;`
- L31 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L37 _public member_ `FAnimNode_LiveLinkPose Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LIVELINKGRAPHNODE_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Animation/LiveLink/Source/LiveLinkGraphNode/Public/K2Node_EvaluateLiveLinkFrame.h` (Public)


#### class `UK2Node_EvaluateLiveLinkFrame`  
`class UK2Node_EvaluateLiveLinkFrame : public UK2Node`  
_L22-93_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UK2Node`
- L28 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L29 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L30 _public prototype_ `virtual FText GetTooltipText() const override;`
- L31 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L32 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L33 _public prototype_ `virtual void PostReconstructNode() override;`
- L37 _public function_ `virtual bool IsNodeSafeToIgnore() const override`
- L38 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L39 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L40 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L41 _public prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L42 _public prototype_ `virtual void EarlyValidation(class FCompilerResultsLog& MessageLog) const override;`
- L43 _public prototype_ `virtual void PreloadRequiredAssets() override;`
- L44 _public prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L48 _public prototype_ `UScriptStruct* GetReturnTypeForOutputDataStruct() const;` — Get the return types of our struct
- L51 _public prototype_ `UEdGraphPin* GetLiveLinkRolePin() const;` — Get the Live Link Role input pin
- L54 _public prototype_ `UEdGraphPin* GetLiveLinkSubjectPin() const;` — Get the Live Link Subject input pin
- L57 _public prototype_ `UEdGraphPin* GetFrameNotAvailablePin() const;` — Get the exec output pin for when no frame is available for the desired role
- L60 _public prototype_ `UEdGraphPin* GetResultingDataPin() const;` — Get the result output pin
- L63 _public prototype_ `UScriptStruct* GetLiveLinkRoleOutputStructType() const;` — Get the type that the Live Link Role evaluates to to return
- L64 _public prototype_ `UScriptStruct* GetLiveLinkRoleOutputFrameStructType() const;`
- L69 _protected prototype_ `virtual FName GetEvaluateFunctionName() const PURE_VIRTUAL(UK2Node_EvaluateLiveLinkFrame::GetEvaluateFunctionName, return NAME_None; );` — Get the name of the UFunction we are trying to build from
- L72 _protected prototype_ `virtual void AddPins(FKismetCompilerContext& CompilerContext, UK2Node_CallFunction* EvaluateLiveLinkFrameFunction) PURE_VIRTUAL(UK2Node_EvaluateLiveLinkFrame::AddPins, );` — Add additionnal pin that the evaluate function would need
- L81 _protected prototype_ `void SetPinToolTip(UEdGraphPin& InOutMutatablePin, const FText& InPinDescription) const;` — Takes the specified "MutatablePin" and sets its 'PinToolTip' field (according to the specified description) @param   MutatablePin	The pin you want to set tool-tip text on @param   PinDescription	A string describing the pin's purpose
- L84 _protected prototype_ `void SetReturnTypeForOutputStruct(UScriptStruct* InClass);` — Set the return type of our structs
- L87 _protected prototype_ `void RefreshDataOutputPinType();` — Queries for the authoritative return type, then modifies the return pin to match
- L89 _protected prototype_ `TSubclassOf<ULiveLinkRole> GetDefaultRolePinValue() const;`
- L92 _protected prototype_ `bool IsRoleValidForEvaluation(TSubclassOf<ULiveLinkRole> InRoleClass) const;` — Verify if selected role class is valid for evaluation

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LIVELINKGRAPHNODE_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkGraphNode/Public/K2Node_UpdateVirtualSubjectDataBase.h` (Public)


#### class `UK2Node_UpdateVirtualSubjectDataBase`  
`class UK2Node_UpdateVirtualSubjectDataBase : public UK2Node`  
_L21-80_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UK2Node`
- L27 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L28 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L29 _public prototype_ `virtual FText GetTooltipText() const override;`
- L30 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L31 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L32 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L36 _public function_ `virtual bool IsNodeSafeToIgnore() const override`
- L37 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L38 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L39 _public prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L40 _public prototype_ `virtual void EarlyValidation(class FCompilerResultsLog& MessageLog) const override;`
- L44 _public prototype_ `UEdGraphPin* GetLiveLinkStructPin() const;` — Get the Live Link Struct input pin
- L54 _protected prototype_ `void SetPinToolTip(UEdGraphPin& InOutMutatablePin, const FText& InPinDescription) const;` — Takes the specified "MutatablePin" and sets its 'PinToolTip' field (according to the specified description) @param   MutatablePin	The pin you want to set tool-tip text on @param   PinDescription	A string describing the pin's purpose
- L57 _protected prototype_ `virtual UScriptStruct* GetStructTypeFromRole(ULiveLinkRole* Role) const PURE_VIRTUAL(UK2Node_UpdateVirtualSubjectDataBase::GetStructTypeFromRole, return nullptr; );` — Returns Struct type associated to the subject's role (static or frame)
- L60 _protected prototype_ `virtual FName GetUpdateFunctionName() const PURE_VIRTUAL(UK2Node_UpdateVirtualSubjectDataBase::GetUpdateFunctionName, return NAME_None; );` — Returns the custom thunk function name
- L63 _protected prototype_ `virtual FText GetStructPinName() const PURE_VIRTUAL(UK2Node_UpdateVirtualSubjectDataBase::GetStructPinName, return FText::GetEmpty(); );` — Returns the struct display name
- L66 _protected prototype_ `virtual void AddPins(FKismetCompilerContext& CompilerContext, UK2Node_CallFunction* UpdateVirtualSubjectDataFunction) const PURE_VIRTUAL(UK2Node_UpdateVirtualSubjectDataBase::AddPins, );` — Add additionnal pins that the update subject function could need
- L71 _private prototype_ `UScriptStruct* GetStructTypeFromBlueprint() const;` — Returns the Struct type associated to the role
- L76 _private member_ `static const FName LiveLinkStructPinName;` — Name of the struct pin
- L79 _private member_ `static const FText LiveLinkStructPinDescription;` — Struct pin description

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINKGRAPHNODE_API`
- L11 _namespace_ `namespace ENodeTitleType`
