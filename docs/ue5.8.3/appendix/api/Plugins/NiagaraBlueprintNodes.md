# Plugins / NiagaraBlueprintNodes

- module root: `Plugins/FX/Niagara/Source/NiagaraBlueprintNodes`
- headers: 6; symbols: 105
- symbol kinds: class=15, function=11, member=10, prototype=69
- PrivateDependencyModuleNames: BlueprintEditorLibrary, BlueprintGraph, CoreUObject, Engine, Kismet, KismetCompiler, Niagara, NiagaraCore, PropertyEditor, Slate, SlateCore, StructUtilsEditor, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/FX/Niagara/Source/NiagaraBlueprintNodes/Internal/K2Node_DataChannelBase.h` (Internal)


#### class `UK2Node_DataChannelBase`  
`class UK2Node_DataChannelBase : public UK2Node_CallFunction`  
_L13-63_
- reflection: `UCLASS(MinimalAPI, Abstract, NotBlueprintable)`
- inherits: `UK2Node_CallFunction`
- L18 _public prototype_ `UNiagaraDataChannel* GetDataChannel() const;`
- L19 _public prototype_ `bool HasValidDataChannel() const;`
- L21 _public prototype_ `virtual void PostLoad() override;`
- L24 _public prototype_ `virtual void AllocateDefaultPins() override;` — //~ Begin UEdGraphNode Interface.
- L25 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L26 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L30 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;`
- L31 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L32 _public prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L33 _public prototype_ `virtual void PreloadRequiredAssets() override;`
- L34 _public prototype_ `virtual bool ShouldShowNodeProperties() const override;`
- L35 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L36 _public prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason)const override;`
- L40 _public member_ `TSet<FGuid> IgnoredVariables;` — `UPROPERTY()`
- L44 _protected prototype_ `UEdGraphPin* GetChannelSelectorPin() const;`
- L45 _protected prototype_ `UEdGraphPin* GetAccessContextPin(EEdGraphPinDirection Direction) const;`
- L49 _protected member_ `FGuid DataChannelVersion;` — `UPROPERTY()`
- L53 _protected function_ `[[nodiscard]] virtual bool SupportsDynamicDataChannel()const` — Some nodes support a dynamic NDC reference via a pin connection. By default this is false and nodes must specify an inline NDC asset reference.
- L55 _protected prototype_ `virtual void AddNDCDerivedPins();`
- L56 _protected prototype_ `virtual void RemoveNDCDerivedPins();`
- L57 _protected member_ `TArray<UEdGraphPin*> NDCDerivedGeneratedPins;`
- L62 _private member_ `TObjectPtr<UNiagaraDataChannelAsset> DataChannel;` — `UPROPERTY()`

### `Plugins/FX/Niagara/Source/NiagaraBlueprintNodes/Internal/K2Node_DataChannel_WithContext.h` (Internal)


#### class `UK2Node_WriteDataChannel_WithContext`  
`class UK2Node_WriteDataChannel_WithContext : public UK2Node_DataChannelBase`  
_L25-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_DataChannelBase`
- desc: A node handling expansion of UNiagaraDataChannelLibrary::WriteToNiagaraDataChannel_WithContext.
- L29 _public prototype_ `UK2Node_WriteDataChannel_WithContext();`
- L31 _public function_ `[[nodiscard]] virtual bool SupportsDynamicDataChannel()const override`

#### class `UK2Node_ReadDataChannel_WithContext`  
`class UK2Node_ReadDataChannel_WithContext : public UK2Node_DataChannelBase`  
_L38-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_DataChannelBase`
- desc: A node handling expansion of UNiagaraDataChannelLibrary::ReadFromNiagaraDataChannel_WithContext.
- L42 _public prototype_ `UK2Node_ReadDataChannel_WithContext();`
- L44 _public function_ `[[nodiscard]] virtual bool SupportsDynamicDataChannel()const override`

#### class `UK2Node_DataChannelGetNum_WithContext`  
`class UK2Node_DataChannelGetNum_WithContext : public UK2Node_DataChannelBase`  
_L52-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_DataChannelBase`
- desc: A node handling expansion of UNiagaraDataChannelLibrary::GetDataChannelElementCount_WithContext.
- L57 _public prototype_ `UK2Node_DataChannelGetNum_WithContext();`
- L59 _public function_ `[[nodiscard]] virtual bool SupportsDynamicDataChannel()const override`

#### class `UK2Node_WriteDataChannelSingle_WithContext`  
`class UK2Node_WriteDataChannelSingle_WithContext : public UK2Node_WriteDataChannel`  
_L67-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_WriteDataChannel`
- desc: A node handling expansion of UNiagaraDataChannelLibrary::WriteToNiagaraDataChannelSingle_WithContext. This expands to multiple function calls to Write the individual NDC variables.
- L71 _public prototype_ `UK2Node_WriteDataChannelSingle_WithContext();`
- L73 _protected function_ `[[nodiscard]] virtual FName GetWriterFunctionName()const`

#### class `UK2Node_ReadDataChannelSingle_WithContext`  
`class UK2Node_ReadDataChannelSingle_WithContext : public UK2Node_ReadDataChannel`  
_L82-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_ReadDataChannel`
- desc: A node handling expansion of UNiagaraDataChannelLibrary::ReadFromNiagaraDataChannelSingle_WithContext. This expands to multiple function calls to Read the individual NDC variables.
- L86 _public prototype_ `UK2Node_ReadDataChannelSingle_WithContext();`
- L88 _protected function_ `[[nodiscard]] virtual FName GetReaderFunctionName()const`

#### class `UK2Node_DataChannelAccessContextOperation`  
`class UK2Node_DataChannelAccessContextOperation : public UK2Node_CallFunction`  
_L98-138_
- reflection: `UCLASS()`
- inherits: `UK2Node_CallFunction`
- desc: Base class for function calls operating on FNDCAccessContextInst structs. These nodes allow NDC users to create, set and get the members for the access contexts being passed to Write/Read NDC functions.
- L103 _public prototype_ `UK2Node_DataChannelAccessContextOperation(const FObjectInitializer& ObjectInitializer);`
- L106 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange)override;`
- L107 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)override;`
- L111 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L112 _public prototype_ `void PreloadRequiredAssets() override;`
- L113 _public prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason)const override;`
- L114 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const;`
- L115 _public prototype_ `virtual bool IsActionFilteredOut(class FBlueprintActionFilter const& Filter) override;`
- L117 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L118 _public prototype_ `virtual FText GetTooltipText() const override;`
- L120 _public function_ `[[nodiscard]] virtual bool ShouldShowNodeProperties()const override`
- L125 _public member_ `TArray<FOptionalPinFromProperty> ShowPinForProperties;` — `UPROPERTY(EditAnywhere, Category = "Access Context")`
- L128 _public member_ `TObjectPtr<UScriptStruct> ContextStruct;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Access Context", meta = (BaseStruct = "/Script/Niagara.NDCAccessContextBase"))`
- L132 _protected function_ `[[nodiscard]] virtual FText GetNodeTitleForContext(UScriptStruct* Struct) const`
- L133 _protected function_ `[[nodiscard]] virtual FText GetTooltipTextForContext(UScriptStruct* Struct) const`
- L135 _protected prototype_ `void ExpandNodeOptionalPins(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UEdGraphPin* AccessContextSourcePin, UEdGraphPin* CurrThen, FName PerPropertyFuncName);`
- L137 _protected member_ `TArray<FName> OldShownPins;`

#### class `UK2Node_DataChannelAccessContext_Make`  
`class UK2Node_DataChannelAccessContext_Make : public UK2Node_DataChannelAccessContextOperation`  
_L141-160_
- reflection: `UCLASS()`
- inherits: `UK2Node_DataChannelAccessContextOperation`
- L146 _public prototype_ `UK2Node_DataChannelAccessContext_Make(const FObjectInitializer& ObjectInitializer);`
- L149 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L153 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L158 _protected prototype_ `[[nodiscard]] virtual FText GetNodeTitleForContext(UScriptStruct* Struct) const override;`
- L159 _protected prototype_ `[[nodiscard]] virtual FText GetTooltipTextForContext(UScriptStruct* Struct) const override;`

#### class `UK2Node_DataChannelAccessContext_GetMembers`  
`class UK2Node_DataChannelAccessContext_GetMembers : public UK2Node_DataChannelAccessContextOperation`  
_L164-182_
- reflection: `UCLASS()`
- inherits: `UK2Node_DataChannelAccessContextOperation`
- L169 _public prototype_ `UK2Node_DataChannelAccessContext_GetMembers(const FObjectInitializer& ObjectInitializer);`
- L172 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L176 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L180 _protected prototype_ `[[nodiscard]] virtual FText GetNodeTitleForContext(UScriptStruct* Struct) const override;`
- L181 _protected prototype_ `[[nodiscard]] virtual FText GetTooltipTextForContext(UScriptStruct* Struct) const override;`

#### class `UK2Node_DataChannelAccessContext_SetMembers`  
`class UK2Node_DataChannelAccessContext_SetMembers : public UK2Node_DataChannelAccessContextOperation`  
_L186-205_
- reflection: `UCLASS()`
- inherits: `UK2Node_DataChannelAccessContextOperation`
- L191 _public prototype_ `UK2Node_DataChannelAccessContext_SetMembers(const FObjectInitializer& ObjectInitializer);`
- L194 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L198 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L203 _protected prototype_ `[[nodiscard]] virtual FText GetNodeTitleForContext(UScriptStruct* Struct) const override;`
- L204 _protected prototype_ `[[nodiscard]] virtual FText GetTooltipTextForContext(UScriptStruct* Struct) const override;`

#### class `UK2Node_DataChannelAccessContext_Prepare`  
`class UK2Node_DataChannelAccessContext_Prepare : public UK2Node_DataChannelAccessContextOperation`  
_L209-228_
- reflection: `UCLASS()`
- inherits: `UK2Node_DataChannelAccessContextOperation`
- desc: Prepares a usable access context ready for accessing an NDC.
- L214 _public prototype_ `UK2Node_DataChannelAccessContext_Prepare(const FObjectInitializer& ObjectInitializer);`
- L217 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L221 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L226 _protected prototype_ `[[nodiscard]] virtual FText GetNodeTitleForContext(UScriptStruct* Struct) const override;`
- L227 _protected prototype_ `[[nodiscard]] virtual FText GetTooltipTextForContext(UScriptStruct* Struct) const override;`

### `Plugins/FX/Niagara/Source/NiagaraBlueprintNodes/Internal/K2Node_ReadDataChannel.h` (Internal)


#### class `UK2Node_ReadDataChannel`  
`class UK2Node_ReadDataChannel : public UK2Node_DataChannelBase`  
_L11-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_DataChannelBase`
- L16 _public prototype_ `UK2Node_ReadDataChannel();`
- L19 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L24 _protected prototype_ `virtual void AddNDCDerivedPins()override;`
- L27 _private prototype_ `UFunction* GetReadFunctionForType(const FNiagaraTypeDefinition& TypeDef);`
- L28 _private prototype_ `UEdGraphPin* GetVarPin(const FName& Name) const;`
- L29 _private function_ `virtual FName GetReaderFunctionName()const`

### `Plugins/FX/Niagara/Source/NiagaraBlueprintNodes/Internal/K2Node_WriteDataChannel.h` (Internal)


#### class `UK2Node_WriteDataChannel`  
`class UK2Node_WriteDataChannel : public UK2Node_DataChannelBase`  
_L11-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_DataChannelBase`
- L16 _public prototype_ `UK2Node_WriteDataChannel();`
- L19 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L24 _protected prototype_ `virtual void AddNDCDerivedPins()override;`
- L26 _protected prototype_ `UFunction* GetWriteFunctionForType(const FNiagaraTypeDefinition& TypeDef);`
- L28 _protected function_ `[[nodiscard]] virtual FName GetWriterFunctionName()const`

### `Plugins/FX/Niagara/Source/NiagaraBlueprintNodes/Internal/NiagaraBlueprintUtil.h` (Internal)


#### class `FNiagaraBlueprintUtil`  
`class FNiagaraBlueprintUtil`  
_L8-15_
- L14 _public prototype_ `static FEdGraphPinType TypeDefinitionToBlueprintType(const FNiagaraTypeDefinition& TypeDef);` — Attempts to convert the existing Niagara type to a matching type for BP pins

### `Plugins/FX/Niagara/Source/NiagaraBlueprintNodes/Private/NiagaraBlueprintNodesDetails.h` (Private)


#### class `FNDCAccessContextOperationNodeDetailsDetails`  
`class FNDCAccessContextOperationNodeDetailsDetails : public IDetailCustomization`  
_L22-47_
- inherits: `IDetailCustomization`
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L28 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L32 _protected prototype_ `void OnGenerateElementForPropertyPin(TSharedRef<IPropertyHandle> ElementProperty, int32 ElementIndex, IDetailChildrenBuilder& ChildrenBuilder, FName CategoryName);`
- L35 _protected prototype_ `ECheckBoxState GetShowPinValueForProperty(TSharedRef<IPropertyHandle> InElementProperty) const;` — Returns the current value of the checkbox being displayed for the bShowPin property
- L38 _protected prototype_ `void OnShowPinChanged(ECheckBoxState InNewState, TSharedRef<IPropertyHandle> InElementProperty);` — Helper function for changing the value of the bShowPin checkbox to update the property
- L41 _protected prototype_ `FReply HideAllUnconnectedPins(const bool bHideInputPins);` — Handler to hide all unconnected pins on a BreakStruct node
- L44 _private member_ `IDetailCategoryBuilder* DetailCategory;`
- L45 _private member_ `TWeakObjectPtr<class UK2Node_DataChannelAccessContextOperation> HideUnconnectedPinsNode;`
- L46 _private member_ `TSharedPtr<class IPropertyHandleArray> ArrayProperty;`
