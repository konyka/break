# Plugins / ModelViewViewModelBlueprint

- module root: `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint`
- headers: 31; symbols: 1181
- symbol kinds: class=33, delegate=7, enum=18, enumerator=50, function=133, macro=13, member=343, namespace=45, prototype=493, struct=46
- PrivateDependencyModuleNames: BlueprintGraph, EnhancedInput, Kismet, KismetCompiler, PropertyEditor, PropertyPath, Slate, SlateCore, UMG, UMGEditor, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, FieldNotification, ModelViewViewModel

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Private/MVVMConversionFunctionGraphSchema.h` (Private)


#### class `UMVVMConversionFunctionGraphSchema`  
`class UMVVMConversionFunctionGraphSchema : public UEdGraphSchema_K2`  
_L13-22_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema_K2`
- desc: Schema for conversion functions, adds pin metadata needed on connections for MVVM
- L19 _public prototype_ `virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;`
- L20 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`

#### class `UMVVMAsyncConversionFunctionGraphSchema`  
`class UMVVMAsyncConversionFunctionGraphSchema : public UMVVMConversionFunctionGraphSchema`  
_L28-37_
- reflection: `UCLASS()`
- inherits: `UMVVMConversionFunctionGraphSchema`
- desc: Schema used by async conversion functions, currently same as regular graph schema. But will autocast objects.
- L34 _public prototype_ `virtual bool CreateAutomaticConversionNodeAndConnections(UEdGraphPin* A, UEdGraphPin* B) const override;`
- L35 _public prototype_ `[[nodiscard]] virtual TOptional<FFindSpecializedConversionNodeResults> FindSpecializedConversionNode(const FEdGraphPinType& OutputPinType, const UEdGraphPin& InputPin, bool bCreateNode) const override;`

#### class `UMVVMFakeTestUbergraphSchema`  
`class UMVVMFakeTestUbergraphSchema : public UEdGraphSchema_K2`  
_L45-51_
- reflection: `UCLASS(Hidden, HideDropDown)`
- inherits: `UEdGraphSchema_K2`
- desc: Schema used to test if a node is async or not Note: Keep in private header.
- L50 _public prototype_ `virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;`

#### class `UMVVMFakeTestUbergraph`  
`class UMVVMFakeTestUbergraph : public UEdGraph`  
_L59-65_
- reflection: `UCLASS(Hidden, HideDropDown)`
- inherits: `UEdGraph`
- desc: Graph used to test if a node is async or not Note: Keep in private header.
- L64 _public prototype_ `UMVVMFakeTestUbergraph();`

#### class `UMVVMFakeTestFunctiongraph`  
`class UMVVMFakeTestFunctiongraph : public UEdGraph`  
_L73-79_
- reflection: `UCLASS(Hidden, HideDropDown)`
- inherits: `UEdGraph`
- desc: Graph used to test if a node is async or not Note: Keep in private header.
- L78 _public prototype_ `UMVVMFakeTestFunctiongraph();`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Private/MVVMFunctionGraphHelper.h` (Private)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MVVM` (scope `UE`)
- L19 _namespace_ `namespace FunctionGraphHelper` (scope `UE::MVVM`)
- L23 _prototype_ `UEdGraph* CreateFunctionGraph(UBlueprint* Blueprint, const FStringView FunctionName, EFunctionFlags ExtraFunctionFlag, const FStringView Category, bool bIsEditable);` (scope `UE::MVVM::FunctionGraphHelper`) — Generate a function graph that can be viewed in the BP editor.
- L26 _prototype_ `UEdGraph* CreateIntermediateFunctionGraph(FKismetCompilerContext& Context, const FStringView FunctionName, EFunctionFlags ExtraFunctionFlag, const FStringView Category, bool bIsEditable);` (scope `UE::MVVM::FunctionGraphHelper`) — Generate a function graph that cannot be viewed in the BP editor.
- L29 _prototype_ `void SetVariableNodeMember(UK2Node_Variable* InVarNode, const FProperty* InProperty, UBlueprint* InTargetBlueprint);` (scope `UE::MVVM::FunctionGraphHelper`) — Set the UK2Node_Variable::VariableReference correctly base on the variable's owner.
- L32 _prototype_ `bool AddFunctionArgument(UEdGraph* FunctionGraph, TSubclassOf<UObject> Argument, FName ArgumentName);` (scope `UE::MVVM::FunctionGraphHelper`) — Add an input argument to an existing function graph.
- L35 _prototype_ `bool AddFunctionArgument(UEdGraph* FunctionGraph, const FProperty* Argument, FName ArgumentName);` (scope `UE::MVVM::FunctionGraphHelper`) — Add an input argument to an existing function graph.
- L38 _prototype_ `bool GenerateViewModelSetter(FKismetCompilerContext& Context, UEdGraph* FunctionGraph, FName ViewModelName);` (scope `UE::MVVM::FunctionGraphHelper`) — Generate the nodes needed for to call the MVVMView::SetViewModel function.
- L41 _prototype_ `bool GenerateViewModelFieldNotifySetter(FKismetCompilerContext& Context, UEdGraph* FunctionGraph, FProperty* Property, FName InputPinName);` (scope `UE::MVVM::FunctionGraphHelper`) — Generate the nodes needed for to set the property and to call the broadcast field notify function.
- L44 _prototype_ `bool GenerateViewModelFielNotifyBroadcast(FKismetCompilerContext& Context, UEdGraph* FunctionGraph, FProperty* Property);` (scope `UE::MVVM::FunctionGraphHelper`) — Generate the nodes needed to broadcast field notify function.
- L47 _prototype_ `bool GenerateSetter(UBlueprint* Blueprint, UEdGraph* FunctionGraph, TArrayView<UE::MVVM::FMVVMConstFieldVariant> SetterPath);` (scope `UE::MVVM::FunctionGraphHelper`) — Generate the nodes needed for to set a variable/function value.
- L50 _prototype_ `bool GenerateIntermediateSetter(FKismetCompilerContext& Context, UEdGraph* FunctionGraph, TArrayView<UE::MVVM::FMVVMConstFieldVariant> SetterPath);` (scope `UE::MVVM::FunctionGraphHelper`) — Generate the nodes needed to set a variable/function value. To use while while compiling the Blueprint.
- L53 _prototype_ `bool IsFunctionEntryMatchSignature(const UEdGraph* FunctionGraph, const UFunction* FunctionSignature);` (scope `UE::MVVM::FunctionGraphHelper`) — @return true when the entry node in the graph matches the function signature.
- L56 _prototype_ `void RenameObjectToTransientPackage(UObject* ObjectToRename);` (scope `UE::MVVM::FunctionGraphHelper`) — Moves the graph object to the transient package

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Private/MVVMViewBlueprintCompiler.h` (Private)


#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler`  
`struct FMVVMViewBlueprintCompiler`  
_L36-433_
- L53 _public prototype_ `FMVVMViewBlueprintCompiler(FWidgetBlueprintCompilerContext& InCreationContext, UMVVMBlueprintView* BlueprintView);`
- L55 _public function_ `FWidgetBlueprintCompilerContext& GetCompilerContext()`
- L60 _public prototype_ `void AddExtension(UWidgetBlueprintGeneratedClass* Class, UMVVMViewClass* ViewExtension);`
- L61 _public prototype_ `void CleanOldData(UWidgetBlueprintGeneratedClass* ClassToClean, UObject* OldCDO);`
- L64 _public prototype_ `void GatherGeneratedVariables(const FWidgetBlueprintCompilerContext::FPopulateGeneratedVariablesContext& Context);` — Update the list of compiler generated variables to be created by the kismet compiler
- L67 _public prototype_ `void CreateVariables(const FWidgetBlueprintCompilerContext::FCreateVariableContext& Context);` — Generate variable and public function in the Skeleton class and the generated class
- L69 _public prototype_ `void CreateFunctions(const FWidgetBlueprintCompilerContext::FCreateFunctionContext& Context);` — Generate function that are hidden from the user (not on the Skeleton class).
- L72 _public prototype_ `bool PreCompile(UWidgetBlueprintGeneratedClass* Class);` — Add all the field path and the bindings to the library compiler.
- L74 _public prototype_ `bool Compile(UWidgetBlueprintGeneratedClass* Class, UMVVMViewClass* ViewExtension);` — Compile the library and fill the view and viewclass
- L77 _public prototype_ `TArray<FName> GetGeneratedFunctions() const;` — Get the list of generated function during the compilation process.
- L79 _public prototype_ `static void TestGenerateSetter(const UBlueprint* Context, FStringView ObjectName, FStringView FieldPath, FStringView FunctionName);`
- L82 _private function_ `bool AreStepsValid() const`
- L88 _private prototype_ `void CreateWidgetMap(const FWidgetBlueprintCompilerContext::FPopulateGeneratedVariablesContext& Context);` — GatherGeneratedVariables
- L89 _private prototype_ `void CreateBindingList(const FWidgetBlueprintCompilerContext::FPopulateGeneratedVariablesContext& Context);`
- L90 _private prototype_ `void CreateEventList(const FWidgetBlueprintCompilerContext::FPopulateGeneratedVariablesContext& Context);`
- L91 _private prototype_ `void CreateConditionList(const FWidgetBlueprintCompilerContext::FPopulateGeneratedVariablesContext& Context);`
- L92 _private prototype_ `void CreateExtensionList(const FWidgetBlueprintCompilerContext::FPopulateGeneratedVariablesContext& Context);`
- L93 _private prototype_ `void CreateRequiredProperties(const FWidgetBlueprintCompilerContext::FPopulateGeneratedVariablesContext& Context);`
- L96 _private prototype_ `void CreatePublicFunctionsDeclaration(const FWidgetBlueprintCompilerContext::FCreateVariableContext& Context);` — CreateVariables
- L99 _private prototype_ `void CategorizeBindings(const FWidgetBlueprintCompilerContext::FCreateFunctionContext& Context);` — CreateFuntions
- L100 _private prototype_ `void CategorizeEvents(const FWidgetBlueprintCompilerContext::FCreateFunctionContext& Context);`
- L101 _private prototype_ `void CategorizeConditions(const FWidgetBlueprintCompilerContext::FCreateFunctionContext& Context);`
- L102 _private prototype_ `void CreateWriteFieldContexts(const FWidgetBlueprintCompilerContext::FCreateFunctionContext& Context);`
- L103 _private prototype_ `void CreateViewModelSetters(const FWidgetBlueprintCompilerContext::FCreateFunctionContext& Context);`
- L104 _private prototype_ `void CreateIntermediateGraphFunctions(const FWidgetBlueprintCompilerContext::FCreateFunctionContext& Context);`
- L105 _private prototype_ `void CategorizeAsyncFunctions(const FWidgetBlueprintCompilerContext::FCreateFunctionContext& Context);`
- L108 _private prototype_ `void FixCompilerBindingSelfSource(UWidgetBlueprintGeneratedClass* Class);` — PreCompile
- L109 _private prototype_ `void AddWarningForPropertyWithMVVMAndLegacyBinding(UWidgetBlueprintGeneratedClass* Class);`
- L110 _private prototype_ `void FixFieldPathContext(UWidgetBlueprintGeneratedClass* Class);`
- L111 _private prototype_ `void CreateReadFieldContexts(UWidgetBlueprintGeneratedClass* Class);`
- L112 _private prototype_ `void CreateCreatorContentFromBindingSource(UWidgetBlueprintGeneratedClass* Class);`
- L113 _private prototype_ `void PreCompileViewModelCreatorContexts(UWidgetBlueprintGeneratedClass* Class);`
- L114 _private prototype_ `void PreCompileBindings(UWidgetBlueprintGeneratedClass* Class);`
- L115 _private prototype_ `void PreCompileEvents(UWidgetBlueprintGeneratedClass* Class);`
- L116 _private prototype_ `void PreCompileConditions(UWidgetBlueprintGeneratedClass* Class);`
- L117 _private prototype_ `void PreCompileViewExtensions(UWidgetBlueprintGeneratedClass* Class);`
- L118 _private prototype_ `void PreCompileSourceDependencies(UWidgetBlueprintGeneratedClass* Class);`
- L121 _private prototype_ `void CompileSources(const FCompiledBindingLibraryCompiler::FCompileResult& CompileResult, UWidgetBlueprintGeneratedClass* Class, UMVVMViewClass* ViewExtension);` — Compile
- L122 _private prototype_ `void CompileBindings(const FCompiledBindingLibraryCompiler::FCompileResult& CompileResult, UWidgetBlueprintGeneratedClass* Class, UMVVMViewClass* ViewExtension);`
- L123 _private prototype_ `void CompileEvaluateSources(const FCompiledBindingLibraryCompiler::FCompileResult& CompileResult, UWidgetBlueprintGeneratedClass* Class, UMVVMViewClass* ViewExtension);`
- L124 _private prototype_ `void CompileEvents(const FCompiledBindingLibraryCompiler::FCompileResult& CompileResult, UWidgetBlueprintGeneratedClass* Class, UMVVMViewClass* ViewExtension);`
- L125 _private prototype_ `void CompileConditions(const FCompiledBindingLibraryCompiler::FCompileResult& CompileResult, UWidgetBlueprintGeneratedClass* Class, UMVVMViewClass* ViewExtension);`
- L126 _private prototype_ `void CompileViewExtensions(const FCompiledBindingLibraryCompiler::FCompileResult& CompileResult, UWidgetBlueprintGeneratedClass* Class, UMVVMViewClass* ViewExtension);`
- L127 _private prototype_ `void SortSourceFields(const FCompiledBindingLibraryCompiler::FCompileResult& CompileResult, UWidgetBlueprintGeneratedClass* Class, UMVVMViewClass* ViewExtension);`
- L152 _private member_ `TArray<TSharedRef<FCompilerBindingSource>> NeededBindingSources;`
- L172 _private member_ `TArray<FCompilerUserWidgetProperty> NeededUserWidgetProperties;`
- L186 _private member_ `TArray<FCompilerViewModelSetter> ViewModelSettersToGenerate;`
- L199 _private member_ `TArray<FCompilerViewModelCreatorContext> ViewModelCreatorContexts;`
- L211 _private member_ `TArray<FCompilerWidgetCreatorContext> WidgetCreatorContexts;`
- L225 _private member_ `TArray<TSharedRef<FCompilerSourceViewModelDynamicCreatorContext>> SourceViewModelDynamicCreatorContexts;`
- L241 _private member_ `TArray<TSharedPtr<FCompilerNotifyFieldId>> NotificationFields;`
- L262 _private member_ `TArray<TSharedRef<FGeneratedReadFieldPathContext>> GeneratedReadFieldPaths;`
- L292 _private member_ `TArray<TSharedRef<FGeneratedWriteFieldPathContext>> GeneratedWriteFieldPaths;`
- L334 _private member_ `TArray<TSharedRef<FCompilerBinding>> ValidBindings;`
- L352 _private member_ `TArray<TSharedRef<FCompilerEvent>> ValidEvents;`
- L365 _private member_ `TArray<TSharedRef<FCompilerCondition>> ValidConditions;`
- L374 _private member_ `TArray<TSharedRef<FCompilerExtension>> ValidExtensions;`
- L379 _private member_ `TArray<FName> FunctionPermissionsToAdd;` — List of public expose function
- L384 _private member_ `TArray<FName> GeneratedFunctions;` — List of generated function
- L387 _private member_ `TMap<FName, UWidget*> WidgetNameToWidgetPointerMap;`
- L388 _private member_ `FWidgetBlueprintCompilerContext& WidgetBlueprintCompilerContext;`
- L389 _private member_ `TObjectPtr<UMVVMBlueprintView> BlueprintView = nullptr;`
- L390 _private member_ `FCompiledBindingLibraryCompiler BindingLibraryCompiler;`
- L391 _private member_ `bool bIsGatherGeneratedVariablesStepValid = true;`
- L392 _private member_ `bool bIsCreateVariableStepValid = true;`
- L393 _private member_ `bool bIsCreateFunctionsStepValid = true;`
- L394 _private member_ `bool bIsPreCompileStepValid = true;`
- L395 _private member_ `bool bIsCompileStepValid = true;`
- L398 _private prototype_ `void AddMessage(const FText& MessageText, Compiler::EMessageType MessageType) const;`
- L399 _private prototype_ `void AddMessages(TArrayView<TWeakPtr<FCompilerBinding>> Bindings, TArrayView<TWeakPtr<FCompilerEvent>> Events, const FText& MessageText, Compiler::EMessageType MessageType) const;`
- L400 _private prototype_ `void AddMessageForBinding(const TSharedPtr<FCompilerBinding>& Binding, const FText& MessageText, Compiler::EMessageType MessageType, const FMVVMBlueprintPinId& PinId) const;`
- L401 _private prototype_ `void AddMessageForBinding(const FMVVMBlueprintViewBinding& Binding, const FText& MessageText, Compiler::EMessageType MessageType, const FMVVMBlueprintPinId& PinId) const;`
- L402 _private prototype_ `void AddMessageForEvent(const TSharedPtr<FCompilerEvent>& Event, const FText& MessageText, Compiler::EMessageType MessageType, const FMVVMBlueprintPinId& PinId) const;`
- L403 _private prototype_ `void AddMessageForEvent(const UMVVMBlueprintViewEvent* Event, const FText& MessageText, Compiler::EMessageType MessageType, const FMVVMBlueprintPinId& PinId) const;`
- L404 _private prototype_ `void AddMessageForCondition(const TSharedPtr<FCompilerCondition>& Condition, const FText& MessageText, Compiler::EMessageType MessageType, const FMVVMBlueprintPinId& PinId) const;`
- L405 _private prototype_ `void AddMessageForCondition(const UMVVMBlueprintViewCondition* Condition, const FText& MessageText, Compiler::EMessageType MessageType, const FMVVMBlueprintPinId& PinId) const;`
- L406 _private prototype_ `void AddMessageForViewModel(const FMVVMBlueprintViewModelContext& ViewModel, const FText& Message, Compiler::EMessageType MessageType) const;`
- L407 _private prototype_ `void AddMessageForViewModel(const FText& ViewModelDisplayName, const FText& Message, Compiler::EMessageType MessageType) const;`
- L423 _private prototype_ `TValueOrError<FGetFieldsResult, FText> GetFields(const UWidgetBlueprintGeneratedClass* Class, const FMVVMBlueprintPropertyPath& PropertyPath) const;`
- L424 _private prototype_ `TValueOrError<FCreateFieldsResult, FText> CreateFieldContext(const UWidgetBlueprintGeneratedClass* Class, const FMVVMBlueprintPropertyPath& PropertyPath, bool bForSourceReading) const;`
- L425 _private prototype_ `TValueOrError<TSharedPtr<FCompilerNotifyFieldId>, FText> CreateNotifyFieldId(const UWidgetBlueprintGeneratedClass* Class, const TSharedPtr<FGeneratedReadFieldPathContext>& ReadFieldContext);`
- L427 _private prototype_ `UMVVMViewClassExtension* CreateViewClassExtension(TSubclassOf<UMVVMViewClassExtension> ExtensionClass, UMVVMViewClass* ViewClass);`
- L429 _private prototype_ `static TArray<FMVVMConstFieldVariant> AppendBaseField(const UClass* Class, FName PropertyName, TArray<FMVVMConstFieldVariant> Properties);`
- L430 _private prototype_ `static bool IsPropertyPathValid(const UBlueprint* Context, TArrayView<const FMVVMConstFieldVariant> PropertyPath);`
- L431 _private prototype_ `static bool CanBeSetInNative(TArrayView<const FMVVMConstFieldVariant> PropertyPath);`
- L432 _private prototype_ `static TSharedRef<FGeneratedWriteFieldPathContext> MakeWriteFieldPath(EMVVMBlueprintFieldPathSource GeneratedFrom, TArray<UE::MVVM::FMVVMConstFieldVariant>&& GeneratedFields, TArray<UE::MVVM::FMVVMConstFieldVariant>&& SkeletalGeneratedFields);`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerBindingSource`  
`struct FCompilerBindingSource`  
_L137-151_
- desc: List of all the sources needed by the view to register/execute the bindings. They could be viewmodel, widget or any properties on the UserWidget. They could also be a viewmodel in a long path. It may not have an associated property (dynamicviewmodel). It may only have OneTime binding.
- L146 _public member_ `const UClass* AuthoritativeClass = nullptr;`
- L147 _public member_ `TArray<TWeakPtr<FCompilerBindingSource>> Dependencies;`
- L148 _public member_ `FName Name;`
- L149 _public member_ `EType Type;`
- L150 _public member_ `bool bIsOptional = false;`

#### enum `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerBindingSource::EType`  
`enum class EType`  
_L139-145_
- L141 _public enumerator_ `ViewModel = 0`
- L142 _public enumerator_ `DynamicViewmodel = 1`
- L143 _public enumerator_ `Widget = 2`
- L144 _public enumerator_ `Self = 3`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerUserWidgetProperty`  
`struct FCompilerUserWidgetProperty : Compiler::FBlueprintViewUserWidgetProperty`  
_L159-171_
- inherits: `Compiler::FBlueprintViewUserWidgetProperty`
- desc: Describe a Property that need to be added (if it doesn't already exist). They can be a Widget, a viewmodel, or any object owned by the UserWidget. They can be source or destination.
- L167 _public member_ `FString BlueprintSetter;`
- L168 _public member_ `ECreationType CreationType = ECreationType::None;`
- L169 _public member_ `bool bInstanced = false;`
- L170 _public member_ `bool bInstanceExposed = false;`

#### enum `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerUserWidgetProperty::ECreationType`  
`enum class ECreationType`  
_L161-166_
- L163 _public enumerator_ `None`
- L164 _public enumerator_ `CreateIfDoesntExist`
- L165 _public enumerator_ `CreateOnlyIfDoesntExist`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerViewModelSetter`  
`struct FCompilerViewModelSetter`  
_L177-185_
- desc: Describe a ViewModel generated setter function.
- L179 _public member_ `const UClass* Class = nullptr;`
- L180 _public member_ `FName PropertyName;`
- L181 _public member_ `FString BlueprintSetter;`
- L182 _public member_ `FText DisplayName;`
- L184 _public member_ `UEdGraph* SetterGraph = nullptr;`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerViewModelCreatorContext`  
`struct FCompilerViewModelCreatorContext`  
_L191-198_
- desc: Describe the data to initialize the view's properties/viewmodels.
- L193 _public member_ `FMVVMBlueprintViewModelContext ViewModelContext;`
- L194 _public member_ `TSharedPtr<FCompilerBindingSource> Source;`
- L196 _public member_ `TSharedPtr<FCompilerSourceViewModelDynamicCreatorContext> DynamicContext;`
- L197 _public member_ `FCompiledBindingLibraryCompiler::FFieldPathHandle ReadPropertyPathHandle;`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerWidgetCreatorContext`  
`struct FCompilerWidgetCreatorContext`  
_L204-210_
- desc: Describe the data to initialize the view's properties/widget.
- L206 _public member_ `TSharedPtr<FCompilerBindingSource> Source;`
- L207 _public member_ `bool bSelfReference = false;`
- L209 _public member_ `FCompiledBindingLibraryCompiler::FFieldPathHandle ReadPropertyPathHandle;`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerSourceViewModelDynamicCreatorContext`  
`struct FCompilerSourceViewModelDynamicCreatorContext`  
_L217-224_
- desc: Describe the data to initialize a viewmodel in a long path. The viewmodel is not added in the BlueprintView but it needs to be dynamic added.
- L219 _public member_ `TSharedPtr<FCompilerBindingSource> Source;`
- L220 _public member_ `TSharedPtr<FCompilerBindingSource> ParentSource;` — a dynamic always has a parent
- L222 _public member_ `FFieldNotificationId NotificationId;`
- L223 _public member_ `FCompiledBindingLibraryCompiler::FFieldIdHandle NotificationIdLibraryCompilerHandle;`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerNotifyFieldId`  
`struct FCompilerNotifyFieldId`  
_L230-240_
- desc: The field id for a specific ReadFieldPathContext
- L232 _public member_ `TArray<FGuid> BindingEditorKeys;`
- L233 _public member_ `TArray<FGuid> EventKeys;`
- L235 _public member_ `FFieldNotificationId NotificationId;`
- L236 _public member_ `TSharedPtr<FCompilerBindingSource> Source;`
- L237 _public member_ `TSharedPtr<FCompilerSourceViewModelDynamicCreatorContext> ViewModelDynamic;`
- L239 _public member_ `FCompiledBindingLibraryCompiler::FFieldIdHandle LibraryCompilerHandle;`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FGeneratedReadFieldPathContext`  
`struct FGeneratedReadFieldPathContext`  
_L247-261_
- desc: The source path we need to read from. Can be any EMVVMBindingMode (OneTime, OneWay, ...)
- L249 _public member_ `TArray<TWeakPtr<FCompilerBinding>> UsedByBindings;`
- L250 _public member_ `TArray<TWeakPtr<FCompilerEvent>> UsedByEvents;`
- L251 _public member_ `TArray<TWeakPtr<FCompilerCondition>> UsedByConditions;`
- L253 _public member_ `TSharedPtr<FCompilerBindingSource> Source;`
- L254 _public member_ `TArray<UE::MVVM::FMVVMConstFieldVariant> GeneratedFields;` — the string path converted into field
- L255 _public member_ `TArray<UE::MVVM::FMVVMConstFieldVariant> SkeletalGeneratedFields;` — the field path converted with getter and setter
- L256 _public member_ `EMVVMBlueprintFieldPathSource GeneratedFrom = EMVVMBlueprintFieldPathSource::None;`
- L257 _public member_ `bool bIsComponent = false;`
- L259 _public member_ `TSharedPtr<FCompilerNotifyFieldId> NotificationField;`
- L260 _public member_ `FCompiledBindingLibraryCompiler::FFieldPathHandle LibraryCompilerHandle;`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FGeneratedWriteFieldPathContext`  
`struct FGeneratedWriteFieldPathContext`  
_L269-291_
- desc: Destination path we need to write to. Only if the bindings/events have a destination. The info needs to be validate before we generate the functions list.
- L271 _public member_ `TArray<TWeakPtr<FCompilerBinding>> UsedByBindings;`
- L272 _public member_ `TArray<TWeakPtr<FCompilerEvent>> UsedByEvents;`
- L278 _public member_ `TSharedPtr<FCompilerBindingSource> OptionalSource;` — Can be invalid if it's a widget with no Read Path. It is the start of the path.
- L279 _public member_ `TSharedPtr<FCompilerBindingSource> OptionalDependencySource;`
- L282 _public member_ `TArray<UE::MVVM::FMVVMConstFieldVariant> GeneratedFields;` — The string path converted into field. It always start from the UserWidget.
- L284 _public member_ `TArray<UE::MVVM::FMVVMConstFieldVariant> SkeletalGeneratedFields;` — The field path converted with getter and setter. It always start from the UserWidget.
- L285 _public member_ `EMVVMBlueprintFieldPathSource GeneratedFrom = EMVVMBlueprintFieldPathSource::None;`
- L286 _public member_ `bool bCanBeSetInNative = true;`
- L287 _public member_ `bool bUseByNativeBinding = false;`
- L289 _public member_ `FName GeneratedFunctionName;`
- L290 _public member_ `FCompiledBindingLibraryCompiler::FFieldPathHandle LibraryCompilerHandle;`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerBinding`  
`struct FCompilerBinding`  
_L297-333_
- desc: The list of all the valid bindings to iterate on.
- L322 _public member_ `FKey Key;`
- L323 _public member_ `EType Type = EType::Unknown;`
- L324 _public member_ `bool bIsOneTimeBinding = false;`
- L326 _public member_ `TArray<TSharedPtr<FGeneratedReadFieldPathContext>> ReadPaths;`
- L327 _public member_ `TSharedPtr<FGeneratedWriteFieldPathContext> WritePath;`
- L328 _public member_ `TWeakObjectPtr<UMVVMBlueprintViewConversionFunction> ConversionFunction;`
- L330 _public member_ `FCompiledBindingLibraryCompiler::FBindingHandle BindingHandle;`
- L331 _public member_ `FCompiledBindingLibraryCompiler::FFieldPathHandle ConversionFunctionHandle;`
- L332 _public member_ `UE::MVVM::Compiler::FCompilerBindingHandle CompilerBindingHandle;`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerBinding::FKey`  
`struct FKey`  
_L299-312_
- L301 _public member_ `int32 ViewBindingIndex = INDEX_NONE;`
- L302 _public member_ `bool bIsForwardBinding = false;`
- L303 _public prototype_ `FKey() = default;`
- L304 _public function_ `FKey(int32 InIndex, bool bInForward) : ViewBindingIndex(InIndex) , bIsForwardBinding(bInForward)`
- L308 _public function_ `bool operator==(const FKey& Other) const`

#### enum `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerBinding::EType`  
`enum class EType : int32`  
_L313-321_
- L315 _public enumerator_ `Unknown = 0` — was not evaluated yet
- L316 _public enumerator_ `Invalid = -1` — evaluated and not valid
- L317 _public enumerator_ `Assignment = 1` — Destination=Source
- L318 _public enumerator_ `SimpleConversionFunction = 2` — Destination=Function(Source)
- L319 _public enumerator_ `ComplexConversionFunction = 3` — Destination=Function(SourceA, SourceB)

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerEvent`  
`struct FCompilerEvent`  
_L339-351_
- desc: The list of all the valid events to iterate on.
- L341 _public member_ `TWeakObjectPtr<UMVVMBlueprintViewEvent> Event;`
- L343 _public member_ `TArray<TSharedPtr<FGeneratedReadFieldPathContext>> ReadPaths;`
- L344 _public member_ `TSharedPtr<FGeneratedWriteFieldPathContext> WritePath;`
- L346 _public member_ `TSharedPtr<FGeneratedWriteFieldPathContext> DelegateFieldPath;`
- L348 _public member_ `FName GeneratedGraphName;`
- L349 _public member_ `FName SourceName;` — may not be in the NeededBindingSources
- L350 _public member_ `FCompiledBindingLibraryCompiler::FFieldPathHandle DelegateFieldPathHandle;`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerCondition`  
`struct FCompilerCondition`  
_L357-364_
- desc: The list of all the valid conditions to iterate on.
- L359 _public member_ `TWeakObjectPtr<UMVVMBlueprintViewCondition> Condition;`
- L360 _public member_ `TArray<TSharedPtr<FGeneratedReadFieldPathContext>> ReadPaths;`
- L361 _public member_ `FName GeneratedGraphName;`
- L362 _public member_ `FName SourceName;` — may not be in the NeededBindingSources
- L363 _public member_ `FCompiledBindingLibraryCompiler::FFieldPathHandle DelegateFieldPathHandle;`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCompilerExtension`  
`struct FCompilerExtension`  
_L370-373_
- desc: The list of all the valid extension to iterates on.
- L372 _public member_ `TWeakObjectPtr<UMVVMBlueprintViewExtension> Extension;`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FGetFieldsResult`  
`struct FGetFieldsResult`  
_L409-414_
- L411 _public member_ `TSharedPtr<FCompilerBindingSource> OptionalSource;`
- L412 _public member_ `EMVVMBlueprintFieldPathSource GeneratedFrom = EMVVMBlueprintFieldPathSource::None;`
- L413 _public member_ `TArray<FMVVMConstFieldVariant> GeneratedFields;`

#### struct `UE::MVVM::Private::FMVVMViewBlueprintCompiler::FCreateFieldsResult`  
`struct FCreateFieldsResult`  
_L415-422_
- L417 _public member_ `TSharedPtr<FCompilerBindingSource> OptionalSource;`
- L418 _public member_ `EMVVMBlueprintFieldPathSource GeneratedFrom = EMVVMBlueprintFieldPathSource::None;`
- L419 _public member_ `TArray<UE::MVVM::FMVVMConstFieldVariant> GeneratedFields;`
- L420 _public member_ `TArray<UE::MVVM::FMVVMConstFieldVariant> SkeletalGeneratedFields;`
- L421 _public member_ `bool bIsComponent;`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace MVVM` (scope `UE`)
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace MVVM` (scope `UE`)
- L33 _namespace_ `namespace Private` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Private/ModelViewViewModelBlueprintModule.h` (Private)
_(no declarations extracted)_

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Private/Node/MVVMK2Node_AreSourcesValidForBinding.h` (Private)


#### class `UMVVMK2Node_AreSourcesValidForBinding`  
`class UMVVMK2Node_AreSourcesValidForBinding : public UK2Node`  
_L15-32_
- reflection: `UCLASS(MinimalAPI, Hidden, HideDropDown)`
- inherits: `UK2Node`
- L21 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L22 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L26 _public prototype_ `UEdGraphPin* GetThenPin() const;` — Get the then output pin
- L28 _public prototype_ `UEdGraphPin* GetElsePin() const;` — Get the else output pin
- L31 _public member_ `FMVVMViewClass_BindingKey BindingKey;` — `UPROPERTY()`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Private/Node/MVVMK2Node_AreSourcesValidForEvent.h` (Private)


#### class `UMVVMK2Node_AreSourcesValidForEvent`  
`class UMVVMK2Node_AreSourcesValidForEvent : public UK2Node`  
_L15-30_
- reflection: `UCLASS(MinimalAPI, Hidden, HideDropDown)`
- inherits: `UK2Node`
- L21 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L22 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L26 _public prototype_ `UEdGraphPin* GetElsePin() const;` — Get the else output pin
- L29 _public member_ `FMVVMViewClass_EventKey EventKey;` — `UPROPERTY()`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Private/Node/MVVMK2Node_IsConditionValid.h` (Private)


#### class `UMVVMK2Node_IsConditionValid`  
`class UMVVMK2Node_IsConditionValid : public UK2Node`  
_L15-37_
- reflection: `UCLASS(MinimalAPI, Hidden, HideDropDown)`
- inherits: `UK2Node`
- L21 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L22 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L26 _public prototype_ `UEdGraphPin* GetThenPin() const;` — Get the then output pin
- L28 _public prototype_ `UEdGraphPin* GetElsePin() const;` — Get the else output pin
- L30 _public prototype_ `UEdGraphPin* GetOperationPin() const;`
- L31 _public prototype_ `UEdGraphPin* GetValuePin() const;`
- L32 _public prototype_ `UEdGraphPin* GetCompareValuePin() const;`
- L33 _public prototype_ `UEdGraphPin* GetCompareMaxValuePin() const;`
- L36 _public member_ `FMVVMViewClass_ConditionKey ConditionKey;` — `UPROPERTY()`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Private/Node/MVVMK2Node_LoadSoftResource.h` (Private)


#### class `UMVVMK2Node_LoadSoftResource`  
`class UMVVMK2Node_LoadSoftResource : public UK2Node_LoadAsset`  
_L21-48_
- reflection: `UCLASS(MinimalAPI, Abstract, Hidden, HideDropDown)`
- inherits: `UK2Node_LoadAsset`
- desc: Utility async node to load a type-specific a soft resource (Texture, Material, etc). Needed since we current do not support automatic dynamic casting in MVVM
- L27 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L31 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L35 _public prototype_ `UEdGraphPin* GetThenPin() const;` — Get the then output pin
- L38 _public prototype_ `UEdGraphPin* GetCompletedPin() const;` — Get the then output pin
- L43 _protected prototype_ `virtual const FName& GetOutputPinName() const;`
- L47 _protected prototype_ `virtual UClass* GetInputResourceClass() const;` — Get the type of the input arg pin

#### class `UMVVMK2Node_LoadSoftTexture`  
`class UMVVMK2Node_LoadSoftTexture : public UMVVMK2Node_LoadSoftResource`  
_L55-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMVVMK2Node_LoadSoftResource`
- L61 _public prototype_ `virtual FText GetTooltipText() const override;`
- L62 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L67 _protected prototype_ `virtual const FName& GetInputPinName() const;`
- L71 _protected prototype_ `virtual UClass* GetInputResourceClass() const override;`

#### class `UMVVMK2Node_LoadSoftMaterial`  
`class UMVVMK2Node_LoadSoftMaterial: public UMVVMK2Node_LoadSoftResource`  
_L80-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMVVMK2Node_LoadSoftResource`
- L86 _public prototype_ `virtual FText GetTooltipText() const override;`
- L87 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L92 _protected prototype_ `virtual const FName& GetInputPinName() const;`
- L96 _protected prototype_ `virtual UClass* GetInputResourceClass() const override;`

#### class `UMVVMK2Node_LoadSoftInputAction`  
`class UMVVMK2Node_LoadSoftInputAction : public UMVVMK2Node_LoadSoftResource`  
_L101-119_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMVVMK2Node_LoadSoftResource`
- L107 _public prototype_ `virtual FText GetTooltipText() const override;`
- L108 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L113 _protected prototype_ `virtual const FName& GetInputPinName() const;`
- L117 _protected prototype_ `virtual UClass* GetInputResourceClass() const override;`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Private/Node/MVVMK2Node_MakeBrushFromSoftResource.h` (Private)


#### class `UMVVMK2Node_MakeBrushFromSoftResource`  
`class UMVVMK2Node_MakeBrushFromSoftResource : public UK2Node_LoadAsset`  
_L21-51_
- reflection: `UCLASS(MinimalAPI, Abstract, Hidden, HideDropDown)`
- inherits: `UK2Node_LoadAsset`
- desc: Utility async node to create a slate brush from a soft resource (Texture, Material, etc). Needed since we cannot nest conversion functions (Ex: LoadAsset->MakeBrushFromTexture).
- L27 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L31 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L35 _public prototype_ `UEdGraphPin* GetThenPin() const;` — Get the then output pin
- L38 _public prototype_ `UEdGraphPin* GetCompletedPin() const;` — Get the completed output pin
- L43 _protected prototype_ `virtual const FName& GetOutputPinName() const;`
- L47 _protected prototype_ `virtual UClass* GetInputResourceClass() const;` — Get the type of the input arg pin
- L50 _protected prototype_ `virtual FName GetMakeBrushFunctionName() const;` — Get the name of the function

#### class `UMVVMK2Node_MakeBrushFromSoftTexture`  
`class UMVVMK2Node_MakeBrushFromSoftTexture : public UMVVMK2Node_MakeBrushFromSoftResource`  
_L58-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMVVMK2Node_MakeBrushFromSoftResource`
- L64 _public prototype_ `virtual FText GetTooltipText() const override;`
- L65 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L70 _protected prototype_ `virtual const FName& GetInputPinName() const;`
- L74 _protected prototype_ `virtual UClass* GetInputResourceClass() const override;`
- L75 _protected prototype_ `virtual FName GetMakeBrushFunctionName() const override;`

#### class `UMVVMK2Node_MakeBrushFromSoftMaterial`  
`class UMVVMK2Node_MakeBrushFromSoftMaterial: public UMVVMK2Node_MakeBrushFromSoftResource`  
_L84-103_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMVVMK2Node_MakeBrushFromSoftResource`
- L90 _public prototype_ `virtual FText GetTooltipText() const override;`
- L91 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L96 _protected prototype_ `virtual const FName& GetInputPinName() const;`
- L100 _protected prototype_ `virtual UClass* GetInputResourceClass() const override;`
- L101 _protected prototype_ `virtual FName GetMakeBrushFunctionName() const override;`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Private/Node/MVVMK2Node_SetSoftTextureParameter.h` (Private)


#### class `UMVVMK2Node_SetSoftTextureParameter`  
`class UMVVMK2Node_SetSoftTextureParameter : public UK2Node_LoadAsset`  
_L21-52_
- reflection: `UCLASS(MinimalAPI, Category = "Widget", meta = (MVVMBindToDestination = "TargetBrush"))`
- inherits: `UK2Node_LoadAsset`
- desc: Utility async node to create a slate brush from a soft resource (Texture, Material, etc). Needed since we cannot nest conversion functions (Ex: LoadAsset->MakeBrushFromTexture).
- L27 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L31 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L35 _public prototype_ `UEdGraphPin* GetThenPin() const;` — Get the then output pin
- L38 _public prototype_ `UEdGraphPin* GetCompletedPin() const;` — Get the completed output pin
- L43 _protected prototype_ `virtual const FName& GetOutputPinName() const override;`
- L44 _protected prototype_ `virtual const FName& GetInputPinName() const override;`
- L49 _public prototype_ `virtual FText GetTooltipText() const override;`
- L50 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/Bindings/MVVMCompiledBindingLibraryCompiler.h` (Public)


#### class `UE::MVVM::FCompiledBindingLibraryCompiler`  
`class FCompiledBindingLibraryCompiler`  
_L23-199_
- L58 _public function_ `friend uint32 GetTypeHash(const FFieldPathHandle& Handle)`
- L100 _public function_ `friend uint32 GetTypeHash(const FBindingHandle& Handle)`
- L142 _public function_ `friend uint32 GetTypeHash(const FFieldIdHandle& Handle)`
- L153 _public prototype_ `FCompiledBindingLibraryCompiler(UBlueprint* Context);`
- L157 _public prototype_ `TValueOrError<FFieldIdHandle, FText> AddFieldId(const UClass* SourceClass, FName FieldName);`
- L160 _public prototype_ `TValueOrError<FFieldPathHandle, FText> AddFieldPath(TArrayView<const UE::MVVM::FMVVMConstFieldVariant> FieldPath, bool bRead);`
- L163 _public prototype_ `TValueOrError<FFieldPathHandle, FText> AddObjectFieldPath(TArrayView<const UE::MVVM::FMVVMConstFieldVariant> FieldPath, const UClass* ExpectedType, bool bRead);`
- L166 _public prototype_ `TValueOrError<FFieldPathHandle, FText> AddConversionFunctionFieldPath(const UClass* SourceClass, const UFunction* Function);`
- L169 _public prototype_ `TValueOrError<FFieldPathHandle, FText> AddDelegateSignatureFieldPath(const UClass* SourceClass, const UFunction* Function);`
- L172 _public prototype_ `TValueOrError<FBindingHandle, FText> AddBinding(FFieldPathHandle Source, FFieldPathHandle Destination);`
- L175 _public prototype_ `TValueOrError<FBindingHandle, FText> AddBinding(FFieldPathHandle Source, FFieldPathHandle Destination, FFieldPathHandle ConversionFunction);`
- L178 _public prototype_ `TValueOrError<FBindingHandle, FText> AddComplexBinding(FFieldPathHandle Destination, FFieldPathHandle ConversionFunction);`
- L190 _public prototype_ `TValueOrError<FCompileResult, FText> Compile(FGuid LibraryId);`
- L194 _private prototype_ `TValueOrError<FFieldPathHandle, FText> AddFieldPathImpl(TArrayView<const UE::MVVM::FMVVMConstFieldVariant> FieldPath, bool bRead);`
- L195 _private prototype_ `TValueOrError<FBindingHandle, FText> AddBindingImpl(FFieldPathHandle Source, FFieldPathHandle Destination, FFieldPathHandle ConversionFunction, bool bIsComplexBinding);`
- L196 _private prototype_ `TValueOrError<FFieldPathHandle, FText> AddFunctionFieldPathImpl(const UClass* InSourceClass, const UFunction* InFunction, TFunctionRef<FText(const UFunction*)> ValidateFunctionCallback);`
- L198 _private member_ `TPimplPtr<Private::FCompiledBindingLibraryCompilerImpl> Impl;`

#### struct `UE::MVVM::FCompiledBindingLibraryCompiler::FFieldPathHandle`  
`struct FFieldPathHandle`  
_L27-66_
- L30 _public function_ `explicit FFieldPathHandle() : Id(0)`
- L35 _public function_ `static FFieldPathHandle MakeHandle()`
- L43 _public function_ `bool IsValid() const`
- L48 _public function_ `bool operator==(const FFieldPathHandle& Other) const`
- L53 _public function_ `bool operator!=(const FFieldPathHandle& Other) const`
- L64 _private member_ `static int32 IdGenerator;`
- L65 _private member_ `int32 Id;`

#### struct `UE::MVVM::FCompiledBindingLibraryCompiler::FBindingHandle`  
`struct FBindingHandle`  
_L69-108_
- L72 _public function_ `explicit FBindingHandle() : Id(0)`
- L77 _public function_ `static FBindingHandle MakeHandle()`
- L85 _public function_ `bool IsValid() const`
- L90 _public function_ `bool operator==(const FBindingHandle& Other) const`
- L95 _public function_ `bool operator!=(const FBindingHandle& Other) const`
- L106 _private member_ `static int32 IdGenerator;`
- L107 _private member_ `int32 Id;`

#### struct `UE::MVVM::FCompiledBindingLibraryCompiler::FFieldIdHandle`  
`struct FFieldIdHandle`  
_L111-150_
- L114 _public function_ `explicit FFieldIdHandle() : Id(0)`
- L119 _public function_ `static FFieldIdHandle MakeHandle()`
- L127 _public function_ `bool IsValid() const`
- L132 _public function_ `bool operator==(const FFieldIdHandle& Other) const`
- L137 _public function_ `bool operator!=(const FFieldIdHandle& Other) const`
- L148 _private member_ `static int32 IdGenerator;`
- L149 _private member_ `int32 Id;`

#### struct `UE::MVVM::FCompiledBindingLibraryCompiler::FCompileResult`  
`struct FCompileResult`  
_L180-187_
- L182 _public prototype_ `FCompileResult(FGuid LibraryId);`
- L183 _public member_ `FMVVMCompiledBindingLibrary Library;`
- L184 _public member_ `TMap<FFieldPathHandle, FMVVMVCompiledFieldPath> FieldPaths;`
- L185 _public member_ `TMap<FBindingHandle, FMVVMVCompiledBinding> Bindings;`
- L186 _public member_ `TMap<FFieldIdHandle, UE::FieldNotification::FFieldId> FieldIds;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MVVM` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MVVM` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::MVVM`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/Bindings/MVVMConversionFunctionHelper.h` (Public)


#### struct `UE::MVVM::ConversionFunctionHelper::FCreateGraphResult`  
`struct FCreateGraphResult`  
_L50-60_
- L53 _public member_ `UEdGraph* NewGraph = nullptr;` — The new graph created.
- L55 _public member_ `UK2Node* WrappedNode = nullptr;` — Node that owns the pins.
- L57 _public member_ `TMap<FName, UK2Node*> NamedNodes;` — Nodes of relevance beyond the wrapped node, keyed by name.
- L59 _public member_ `bool bIsUbergraphPage = false;` — True if this graph belongs in an ubergraph page

#### struct `UE::MVVM::ConversionFunctionHelper::FCreateGraphParams`  
`struct FCreateGraphParams`  
_L62-70_
- L64 _public member_ `bool bIsConst = false;`
- L65 _public member_ `bool bTransient = false;`
- L66 _public member_ `bool bIsForEvent = false;`
- L69 _public member_ `bool bCreateUbergraphPage = false;` — If true implies this graph will create events

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MVVM` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace MVVM` (scope `UE`)
- L25 _namespace_ `namespace ConversionFunctionHelper` (scope `UE::MVVM`)
- L28 _prototype_ `bool RequiresWrapper(const UFunction* Function);` (scope `UE::MVVM::ConversionFunctionHelper`) — Conversion function requires a wrapper.
- L31 _prototype_ `bool IsInputPin(const UEdGraphPin* Pin);` (scope `UE::MVVM::ConversionFunctionHelper`) — The pin is valid to use with a PropertyPath.
- L34 _prototype_ `FMVVMBlueprintPropertyPath GetPropertyPathForPin(const UBlueprint* WidgetBlueprint, const UEdGraphPin* Pin, bool bSkipResolve);` (scope `UE::MVVM::ConversionFunctionHelper`) — Find the property path of a given argument in the conversion function.
- L37 _prototype_ `void SetPropertyPathForPin(const UBlueprint* Blueprint, const FMVVMBlueprintPropertyPath& PropertyPath, UEdGraphPin* Pin);` (scope `UE::MVVM::ConversionFunctionHelper`) — Set the property path of a given argument in the conversion function.
- L40 _prototype_ `FMVVMBlueprintPropertyPath GetPropertyPathForArgument(const UBlueprint* WidgetBlueprint, const UK2Node_CallFunction* Function, FName ArgumentName, bool bSkipResolve);` (scope `UE::MVVM::ConversionFunctionHelper`) — Find the property path of a given argument in the conversion function.
- L43 _prototype_ `FName CreateWrapperName(const FMVVMBlueprintViewBinding& Binding, bool bSourceToDestination);` (scope `UE::MVVM::ConversionFunctionHelper`) — Create the name of the conversion function wrapper this binding should have.
- L48 _prototype_ `TValueOrError<void, FText> CanCreateSetterGraph(UBlueprint* WidgetBlueprint, const FMVVMBlueprintPropertyPath& PropertyPath);` (scope `UE::MVVM::ConversionFunctionHelper`) — If we can create a graph to set a property/function.
- L75 _prototype_ `TValueOrError<FCreateGraphResult, FText> CreateSetterGraph(UBlueprint* WidgetBlueprint, FName GraphName, const UFunction* Signature, const FMVVMBlueprintPropertyPath& PropertyPath, FCreateGraphParams InParams);` (scope `UE::MVVM::ConversionFunctionHelper`) — Create a graph to set a property/function. Used by Event Bindings
- L80 _prototype_ `TValueOrError<FCreateGraphResult, FText> CreateSetterGraph(UBlueprint* WidgetBlueprint, FName GraphName, const TSubclassOf<UK2Node> Node, const FMVVMBlueprintPropertyPath& PropertyPath, FCreateGraphParams InParams);` (scope `UE::MVVM::ConversionFunctionHelper`) — Create a graph to set a property/function. Used by conversion functions for async K2 Nodes.
- L83 _prototype_ `FCreateGraphResult CreateGraph(UBlueprint* WidgetBlueprint, FName GraphName, const UFunction* Signature, const UFunction* FunctionToWrap, FCreateGraphParams FCreateGraInParamsphParams);` (scope `UE::MVVM::ConversionFunctionHelper`) — Create a graph, used by conversion functions for UFunctions
- L86 _prototype_ `FCreateGraphResult CreateGraph(UBlueprint* WidgetBlueprint, FName GraphName, const UFunction* Signature, const TSubclassOf<UK2Node> Node, FCreateGraphParams InParams, TFunctionRef<void(UK2Node*)> InitNodeCallback);` (scope `UE::MVVM::ConversionFunctionHelper`) — Create a graph, used by conversion functions for K2 Nodes
- L89 _prototype_ `TValueOrError<FCreateGraphResult, FText> CreateSetterGraph(UBlueprint* WidgetBlueprint, FName GraphName, const UFunction* Signature, const FMVVMBlueprintPropertyPath& PropertyPath, bool bIsConst, bool bTransient, const bool bIsForEvent);` (scope `UE::MVVM::ConversionFunctionHelper`) — `UE_DEPRECATED(5.5, "Call the version of CreateSetterGraph that takes a FCreateGraphParams instead.")`
- L91 _prototype_ `FCreateGraphResult CreateGraph(UBlueprint* WidgetBlueprint, FName GraphName, const UFunction* Signature, const UFunction* FunctionToWrap, bool bIsConst, bool bTransient);` (scope `UE::MVVM::ConversionFunctionHelper`) — `UE_DEPRECATED(5.5, "Call the version of CreateGraph that takes a FCreateGraphParams instead.")`
- L93 _prototype_ `FCreateGraphResult CreateGraph(UBlueprint* WidgetBlueprint, FName GraphName, const UFunction* Signature, const TSubclassOf<UK2Node> Node, bool bIsConst, bool bTransient, TFunctionRef<void(UK2Node*)> InitNodeCallback);` (scope `UE::MVVM::ConversionFunctionHelper`) — `UE_DEPRECATED(5.5, "Call the version of CreateGraph that takes a FCreateGraphParams instead.")`
- L96 _prototype_ `UK2Node* InsertEarlyExitBranchNode(UEdGraph* Graph, TSubclassOf<UK2Node> BranchNode);` (scope `UE::MVVM::ConversionFunctionHelper`) — Insert a branch node to the existing graph to test before executing the rest of the .
- L99 _prototype_ `UK2Node* GetWrapperNode(const UEdGraph* Graph);` (scope `UE::MVVM::ConversionFunctionHelper`) — Find the main conversion function node from the given graph.
- L102 _prototype_ `UEdGraphPin* FindPin(const UEdGraph* Graph, const TArrayView<const FName> PinNames);` (scope `UE::MVVM::ConversionFunctionHelper`) — Find the conversion function node from the given graph.
- L105 _prototype_ `UEdGraphPin* FindPin(const UEdGraphNode* Node, const TArrayView<const FName> PinNames);` (scope `UE::MVVM::ConversionFunctionHelper`) — Find the conversion function node from the given graph.
- L108 _prototype_ `TArray<FName> FindPinId(const UEdGraphPin* GraphPin);` (scope `UE::MVVM::ConversionFunctionHelper`) — Find the conversion function node from the given graph.
- L111 _prototype_ `TArray<UEdGraphPin*> FindInputPins(const UK2Node* Node);` (scope `UE::MVVM::ConversionFunctionHelper`) — Return the pin used for arguments.
- L114 _prototype_ `UEdGraphPin* FindOutputPin(const UK2Node* Node);` (scope `UE::MVVM::ConversionFunctionHelper`) — Return the pin used as the return value.
- L117 _prototype_ `void SetMetaData(UEdGraph* NewGraph, FName MetaData, FStringView Value);` (scope `UE::MVVM::ConversionFunctionHelper`) — Add metadata to the Graph/Function.
- L120 _prototype_ `void MarkNodeAsAutoPromote(UEdGraphNode* Node);` (scope `UE::MVVM::ConversionFunctionHelper`) — Mark the node a auto promote. We try to hide those node in the editor.
- L123 _prototype_ `bool IsAutoPromoteNode(const UEdGraphNode* Node);` (scope `UE::MVVM::ConversionFunctionHelper`) — Is the node an auto promote node.
- L126 _prototype_ `bool IsAsyncNode(const TSubclassOf<UK2Node> Node);` (scope `UE::MVVM::ConversionFunctionHelper`) — Is the node an async node.
- L129 _prototype_ `bool IsNodeMarkedToKeepConnections(const UK2Node* Node);` (scope `UE::MVVM::ConversionFunctionHelper`) — `UE_DEPRECATED(5.6, "This function is deprecated and will always return false.")`
- L131 _prototype_ `void MarkNodeToKeepConnections(const UK2Node* Node);` (scope `UE::MVVM::ConversionFunctionHelper`) — `UE_DEPRECATED(5.6, "This function is deprecated and is not taken into consideration anymore.")`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/Extensions/MVVMBlueprintViewExtension.h` (Public)


#### class `UMVVMBlueprintViewExtension`  
`class UMVVMBlueprintViewExtension : public UObject`  
_L19-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: An extension class to define MVVM-related properties and behaviour. When WBP compiled, this information is copied into UMVVMViewClassExtension. This class provides a hook into the MVVM compiler and partially exposes it for injecting user-defined behaviour at compile-time.
- L25 _public function_ `virtual TArray<UE::MVVM::Compiler::FBlueprintViewUserWidgetProperty> AddProperties()`
- L30 _public function_ `virtual TArray<UE::MVVM::Compiler::FBlueprintViewUserWidgetWidgetProperty> AddWidgetProperties()`
- L35 _public function_ `virtual void Precompile(UE::MVVM::Compiler::IMVVMBlueprintViewPrecompile* Compiler, UWidgetBlueprintGeneratedClass* Class)`
- L36 _public function_ `virtual void Compile(UE::MVVM::Compiler::IMVVMBlueprintViewCompile* Compiler, UWidgetBlueprintGeneratedClass* Class, UMVVMViewClass* ViewExtension)`
- L37 _public function_ `virtual bool WidgetRenamed(FName OldName, FName NewName)`
- L42 _public function_ `virtual void OnPreviewContentChanged(TSharedRef<SWidget> NewContent)`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/Extensions/MVVMViewBlueprintListViewBaseExtension.h` (Public)


#### class `UMVVMBlueprintViewExtension_ListViewBase`  
`class UMVVMBlueprintViewExtension_ListViewBase : public UMVVMBlueprintViewExtension`  
_L29-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMVVMBlueprintViewExtension`
- L35 _public prototype_ `virtual void Precompile(UE::MVVM::Compiler::IMVVMBlueprintViewPrecompile* Compiler, UWidgetBlueprintGeneratedClass* Class) override;`
- L36 _public prototype_ `virtual void Compile(UE::MVVM::Compiler::IMVVMBlueprintViewCompile* Compiler, UWidgetBlueprintGeneratedClass* Class, UMVVMViewClass* ViewExtension) override;`
- L37 _public prototype_ `virtual bool WidgetRenamed(FName OldName, FName NewName) override;`
- L40 _public function_ `FGuid GetEntryViewModelId() const`
- L46 _private prototype_ `const UMVVMBlueprintView* GetEntryWidgetBlueprintView(const UWidgetBlueprint* EntryWidgetBlueprint) const;`
- L50 _private member_ `FName WidgetName;` — `UPROPERTY()`
- L53 _private member_ `FGuid EntryViewModelId;` — `UPROPERTY()`
- L55 _private member_ `UE::MVVM::FCompiledBindingLibraryCompiler::FFieldPathHandle WidgetPathHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MVVM` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MVVM` (scope `UE`)
- L22 _namespace_ `namespace Compiler` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/Extensions/MVVMViewBlueprintPanelWidgetExtension.h` (Public)


#### class `UMVVMBlueprintViewExtension_PanelWidget`  
`class UMVVMBlueprintViewExtension_PanelWidget : public UMVVMBlueprintViewExtension`  
_L33-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMVVMBlueprintViewExtension`
- L39 _public prototype_ `virtual TArray<UE::MVVM::Compiler::FBlueprintViewUserWidgetProperty> AddProperties() override;`
- L40 _public prototype_ `virtual TArray<UE::MVVM::Compiler::FBlueprintViewUserWidgetWidgetProperty> AddWidgetProperties() override;`
- L41 _public prototype_ `virtual void Precompile(UE::MVVM::Compiler::IMVVMBlueprintViewPrecompile* Compiler, UWidgetBlueprintGeneratedClass* Class) override;`
- L42 _public prototype_ `virtual void Compile(UE::MVVM::Compiler::IMVVMBlueprintViewCompile* Compiler, UWidgetBlueprintGeneratedClass* Class, UMVVMViewClass* ViewExtension) override;`
- L43 _public prototype_ `virtual bool WidgetRenamed(FName OldName, FName NewName) override;`
- L44 _public prototype_ `virtual void OnPreviewContentChanged(TSharedRef<SWidget> NewContent) override;`
- L47 _public function_ `FGuid GetEntryViewModelId() const`
- L53 _private prototype_ `const UMVVMBlueprintView* GetEntryWidgetBlueprintView(const UWidgetBlueprint* EntryWidgetBlueprint) const;`
- L55 _private prototype_ `static void RefreshDesignerPreviewEntries(UPanelWidget* PanelWidget, TSubclassOf<UUserWidget> EntryWidgetClass, UPanelSlot* SlotTemplate, int32 NumDesignerPreviewEntries, bool bFullRebuild);`
- L59 _private member_ `FName WidgetName;` — `UPROPERTY()`
- L62 _private member_ `FGuid EntryViewModelId;` — `UPROPERTY()`
- L65 _private member_ `TSubclassOf<UUserWidget> EntryWidgetClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EntryClass", meta = (AllowPrivateAccess = "true"))`
- L68 _private member_ `TObjectPtr<UPanelSlot> SlotObj;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Slot", meta = (AllowPrivateAccess = "true"))`
- L71 _private member_ `int32 NumDesignerPreviewEntries = 3;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NumDesignerPreviewEntries", meta = (AllowPrivateAccess = "true", ClampMin = 0, ClampMax = 20))`
- L74 _private member_ `FName PanelPropertyName;` — `UPROPERTY()`
- L77 _private member_ `TObjectPtr<UMVVMViewPanelWidgetClassExtension> ExtensionObj;` — `UPROPERTY()`
- L79 _private member_ `UE::MVVM::FCompiledBindingLibraryCompiler::FFieldPathHandle WidgetPathHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MVVM` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace MVVM` (scope `UE`)
- L25 _namespace_ `namespace Compiler` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMBlueprintFunctionReference.h` (Public)


#### enum `EMVVMBlueprintFunctionReferenceType`  
`enum class EMVVMBlueprintFunctionReferenceType : uint8`  
_L17-22_
- reflection: `UENUM()`
- L19 _public enumerator_ `None`
- L20 _public enumerator_ `Function`
- L21 _public enumerator_ `Node`

#### struct `FMVVMBlueprintFunctionReference`  
`struct FMVVMBlueprintFunctionReference`  
_L28-80_
- reflection: `USTRUCT(BlueprintType)`
- desc: A type that point to a function or a node that can be used to create a conversion function.
- L33 _public prototype_ `FMVVMBlueprintFunctionReference() = default;`
- L34 _public prototype_ `explicit FMVVMBlueprintFunctionReference(const UBlueprint* InContext, const UFunction* InFunction);`
- L35 _public prototype_ `explicit FMVVMBlueprintFunctionReference(FMemberReference InFunctionReference);`
- L36 _public prototype_ `explicit FMVVMBlueprintFunctionReference(TSubclassOf<UK2Node> InNode);`
- L39 _public prototype_ `const UFunction* GetFunction(const UBlueprint* SelfContext) const;` — If the node is of type Function, resolves the function. Uses the blueprint, if the function is defined on the BP itself.
- L41 _public prototype_ `const UFunction* GetFunction(const UClass* SelfContext) const;` — If the node is of type Function, resolves the function. Uses the blueprint, if the function is defined on the BP itself.
- L43 _public prototype_ `TSubclassOf<UK2Node> GetNode() const;` — If the node is of type Node, return the node class.
- L45 _public function_ `EMVVMBlueprintFunctionReferenceType GetType() const`
- L51 _public prototype_ `FString ToString() const;` — return a string representation of the reference.
- L54 _public prototype_ `FName GetName() const;` — return a name of the reference.
- L57 _public prototype_ `bool IsValid(const UBlueprint* SelfContext) const;` — The reference is a valid UFunction or a valid Node.
- L59 _public prototype_ `bool IsValid(const UClass* SelfContext) const;` — The reference is a valid UFunction or a valid Node.
- L61 _public prototype_ `bool operator==(const FMVVMBlueprintFunctionReference& Other) const;`
- L73 _private member_ `FMemberReference FunctionReference;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")`
- L76 _private member_ `TSubclassOf<UK2Node> Node;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")`
- L79 _private member_ `EMVVMBlueprintFunctionReferenceType Type = EMVVMBlueprintFunctionReferenceType::None;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")`

#### Free symbols / members of external scopes

- L63 _function_ `friend uint32 GetTypeHash(const FMVVMBlueprintFunctionReference& Value)`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMBlueprintInstancedViewModel.h` (Public)


#### class `UMVVMBlueprintInstancedViewModelBase`  
`class UMVVMBlueprintInstancedViewModelBase : public UObject`  
_L18-73_
- reflection: `UCLASS(MinimalAPI, Abstract, Within = MVVMBlueprintView)`
- inherits: `UObject`
- L23 _public prototype_ `UMVVMBlueprintInstancedViewModelBase();`
- L25 _public prototype_ `void GenerateClass(bool bForceGeneration);`
- L27 _public function_ `UClass* GetGeneratedClass() const`
- L33 _protected prototype_ `virtual void PreloadObjectsForCompilation();`
- L34 _protected prototype_ `virtual bool IsClassDirty() const;`
- L35 _protected prototype_ `virtual void CleanClass();`
- L36 _protected prototype_ `virtual void AddProperties();`
- L37 _protected prototype_ `virtual void ConstructClass();`
- L38 _protected prototype_ `virtual void SetDefaultValues();`
- L39 _protected prototype_ `virtual void ClassGenerated();`
- L50 _protected prototype_ `bool IsValidFieldName(const FName NewPropertyName) const;`
- L51 _protected prototype_ `bool IsValidFieldName(const FName NewPropertyName, UStruct* NewOwner) const;`
- L52 _protected prototype_ `FProperty* CreateProperty(const FProperty* FromProperty, UStruct* NewOwner);`
- L53 _protected prototype_ `FProperty* CreateProperty(const FProperty* FromProperty, UStruct* NewOwner, FName NewPropertyName);`
- L54 _protected prototype_ `void InitializeProperty(FProperty* NewProperty, FInitializePropertyArgs& Args);`
- L55 _protected prototype_ `void LinkProperty(FProperty* NewProperty) const;`
- L56 _protected prototype_ `void LinkProperty(FProperty* NewProperty, UStruct* NewOwner) const;`
- L57 _protected prototype_ `void AddOnRepFunction(FProperty* NewProperty);`
- L58 _protected prototype_ `void SafeRename(UObject* Object);`
- L59 _protected prototype_ `void SetDefaultValue(const FProperty* SourceProperty, void const* SourceValuePtr, const FProperty* DestinationProperty);`
- L64 _public member_ `TSubclassOf<UObject> ParentClass;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", meta=(AllowedClasses = "/Script/FieldNotification.NotifyFieldValueChanged", DisallowedClasses = "/Script/UMG.Widget"))` — The base object of the generated class.
- L67 _public member_ `TObjectPtr<UMVVMInstancedViewModelGeneratedClass> GeneratedClass;` — `UPROPERTY()`
- L72 _protected member_ `TSubclassOf<UMVVMInstancedViewModelGeneratedClass> GeneratedClassType;` — `UPROPERTY()`

#### struct `UMVVMBlueprintInstancedViewModelBase::FInitializePropertyArgs`  
`struct FInitializePropertyArgs`  
_L42-48_
- L44 _public member_ `bool bFieldNotify = false;`
- L45 _public member_ `bool bReadOnly = false;`
- L46 _public member_ `bool bNetwork = false;`
- L47 _public member_ `bool bPrivate = false;`

#### class `UMVVMBlueprintInstancedViewModel_PropertyBag`  
`class UMVVMBlueprintInstancedViewModel_PropertyBag : public UMVVMBlueprintInstancedViewModelBase`  
_L79-114_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMVVMBlueprintInstancedViewModelBase`
- L84 _public function_ `const UStruct* GetSourceStruct() const`
- L89 _public function_ `const uint8* GetSourceDefaults() const`
- L95 _protected prototype_ `virtual bool IsClassDirty() const override;`
- L96 _protected prototype_ `virtual void CleanClass() override;`
- L97 _protected prototype_ `virtual void AddProperties() override;`
- L98 _protected prototype_ `virtual void SetDefaultValues() override;`
- L99 _protected prototype_ `virtual void ClassGenerated() override;`
- L103 _private member_ `FInstancedPropertyBag Variables;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel")`
- L106 _private member_ `uint64 PropertiesHash = 0;` — `UPROPERTY()`
- L108 _private member_ `TMap<const FProperty*, FProperty*> FromPropertyToCreatedProperty;`
- L112 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMBlueprintPin.h` (Public)


#### enum `EMVVMBlueprintPinStatus`  
`enum class EMVVMBlueprintPinStatus : uint8`  
_L19-23_
- reflection: `UENUM()`
- L21 _public enumerator_ `Valid`
- L22 _public enumerator_ `Orphaned`

#### struct `FMVVMBlueprintPinId`  
`struct FMVVMBlueprintPinId`  
_L29-58_
- reflection: `USTRUCT()`
- desc: Pin name type to help with compare operation and moving it around.
- L33 _public prototype_ `FMVVMBlueprintPinId() = default;`
- L34 _public prototype_ `explicit FMVVMBlueprintPinId(const TArrayView<const FName> Names);`
- L35 _public prototype_ `explicit FMVVMBlueprintPinId(TArray<FName>&& Names);`
- L37 _public prototype_ `bool IsValid() const;`
- L39 _public function_ `const TArrayView<const FName> GetNames() const`
- L45 _public prototype_ `bool IsChildOf(const FMVVMBlueprintPinId& Other) const;` — return true if the Pin is part of the Other pin. It can be a grand child.
- L48 _public prototype_ `bool IsDirectChildOf(const FMVVMBlueprintPinId& Other) const;` — return true if the Pin is the directly child of the Other pin. It can be a child but not a grand child.
- L50 _public prototype_ `bool operator==(const FMVVMBlueprintPinId& Other) const;`
- L51 _public prototype_ `bool operator==(const TArrayView<const FName> Other) const;`
- L53 _public prototype_ `FString ToString() const;`
- L57 _private member_ `TArray<FName> PinNames;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")`

#### struct `FMVVMBlueprintPin`  
`struct FMVVMBlueprintPin`  
_L64-168_
- reflection: `USTRUCT()`
- L70 _private member_ `FMVVMBlueprintPinId Id;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")`
- L73 _private member_ `FMVVMBlueprintPropertyPath Path;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")`
- L77 _private member_ `FString DefaultString;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")` — Default value for this pin (used if the pin has no connections), stored as a string
- L81 _private member_ `FText DefaultText;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")` — If the default value for this pin should be an FText, it is stored here.
- L85 _private member_ `TObjectPtr<class UObject> DefaultObject;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")` — If the default value for this pin should be an object, we store a pointer to it
- L89 _private member_ `bool bSplit = false;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")` — The pin is split.
- L93 _private member_ `mutable EMVVMBlueprintPinStatus Status = EMVVMBlueprintPinStatus::Valid;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")` — The pin could not be set.
- L96 _private member_ `FName PinName_DEPRECATED;` — `UPROPERTY()`
- L99 _private member_ `FGuid PinId_DEPRECATED;` — `UPROPERTY()`
- L102 _public prototype_ `FMVVMBlueprintPin() = default;`
- L104 _public prototype_ `FMVVMBlueprintPin(FName PinName);` — `UE_DEPRECATED(5.4, "FMVVMBlueprintPin with a single name is deprecated. Use the TArrayView constructor instead")`
- L105 _public prototype_ `explicit FMVVMBlueprintPin(FMVVMBlueprintPinId PinId);`
- L106 _public prototype_ `explicit FMVVMBlueprintPin(const TArrayView<const FName> PinName);`
- L109 _public function_ `FName GetName() const` — `UE_DEPRECATED(5.4, "GetName is deprecated. Use GetId().GetNames instead")`
- L114 _public function_ `const FMVVMBlueprintPinId& GetId() const`
- L119 _public function_ `bool IsValid() const`
- L125 _public function_ `bool IsSplit() const` — The pin is split into its different components.
- L131 _public function_ `EMVVMBlueprintPinStatus GetStatus() const` — The pin could not be assigned to the graph pin.
- L137 _public function_ `bool UsedPathAsValue() const` — Are we using the path.
- L143 _public function_ `const FMVVMBlueprintPropertyPath& GetPath() const` — Get the path used by this pin.
- L148 _public prototype_ `FString GetValueAsString(const UClass* SelfContext) const;`
- L150 _public prototype_ `void SetDefaultValue(UObject* Value);`
- L151 _public prototype_ `void SetDefaultValue(const FText& Value);`
- L152 _public prototype_ `void SetDefaultValue(const FString& Value);`
- L153 _public prototype_ `void SetPath(const FMVVMBlueprintPropertyPath& Value);`
- L156 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L159 _public prototype_ `static bool IsInputPin(const UEdGraphPin* Pin);`
- L160 _public prototype_ `static TArray<FMVVMBlueprintPin> CopyAndReturnMissingPins(UBlueprint* Blueprint, UEdGraphNode* GraphNode, const TArray<FMVVMBlueprintPin>& Pins);`
- L161 _public prototype_ `static TArray<FMVVMBlueprintPin> CreateFromNode(UBlueprint* Blueprint, UEdGraphNode* GraphNode);`
- L162 _public prototype_ `static FMVVMBlueprintPin CreateFromPin(const UBlueprint* Blueprint, const UEdGraphPin* Pin);`
- L164 _public prototype_ `void CopyTo(const UBlueprint* WidgetBlueprint, UEdGraphNode* Node) const;`
- L165 _public prototype_ `UEdGraphPin* FindGraphPin(const UEdGraph* Graph) const;`
- L167 _public prototype_ `void Reset();`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMVVMBlueprintPin> : public TStructOpsTypeTraitsBase2<FMVVMBlueprintPin>`  
_L171-177_
- inherits: `TStructOpsTypeTraitsBase2<FMVVMBlueprintPin>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L174-176_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`
- L175 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonbf6175a30103`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMBlueprintView.h` (Public)


#### enum `UE::MVVM::EBindingMessageType`  
`enum class EBindingMessageType : uint8`  
_L21-26_
- L23 _public enumerator_ `Info`
- L24 _public enumerator_ `Warning`
- L25 _public enumerator_ `Error`

#### struct `UE::MVVM::FBindingMessage`  
`struct FBindingMessage`  
_L28-32_
- L30 _public member_ `FText MessageText;`
- L31 _public member_ `EBindingMessageType MessageType;`

#### class `UMVVMBlueprintViewSettings`  
`class UMVVMBlueprintViewSettings : public UObject`  
_L39-76_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L50 _public member_ `bool bInitializeSourcesOnConstruct = true;` — `UPROPERTY(EditAnywhere, Category = "View")` — Auto initialize the view sources when the Widget is constructed. If false, the user will have to initialize the sources manually. It prevents the sources evaluating until you are ready.
- L61 _public member_ `bool bInitializeBindingsOnConstruct = true;` — `UPROPERTY(EditAnywhere, Category = "View", meta=(EditCondition="bInitializeSourcesOnConstruct"))` — Auto initialize the view bindings when the Widget is constructed. If false, the user will have to initialize the bindings manually. It prevents bindings execution and improves performance when you know the widget won't be visible. @note All bindings are executed when the view is automatically initialized or manually initialized. @note Sources needs to be initialized before initializing the bindings. @note When Sources is manually initialized, the bindings will also be initialized if this is true.
- L68 _public member_ `bool bInitializeEventsOnConstruct = true;` — `UPROPERTY(EditAnywhere, Category = "View")` — Auto initialize the view events when the Widget is constructed. If false, the user will have to initialize the event manually.
- L75 _public member_ `bool bCreateViewWithoutBindings = false;` — `UPROPERTY(EditAnywhere, Category = "View")` — Create the view even when there are no view bindings or events. If false, the view models will not be automatically available for use in blueprints if there are no bindings.

#### class `UMVVMBlueprintView`  
`class UMVVMBlueprintView : public UObject`  
_L82-254_
- reflection: `UCLASS(MinimalAPI, Within=MVVMWidgetBlueprintExtension_View)`
- inherits: `UObject`
- L87 _public prototype_ `UMVVMBlueprintView();`
- L90 _public function_ `UMVVMBlueprintViewSettings* GetSettings()`
- L95 _public prototype_ `FMVVMBlueprintViewModelContext* FindViewModel(FGuid ViewModelId);`
- L96 _public prototype_ `const FMVVMBlueprintViewModelContext* FindViewModel(FGuid ViewModelId) const;`
- L97 _public prototype_ `const FMVVMBlueprintViewModelContext* FindViewModel(FName ViewModelName) const;`
- L99 _public prototype_ `void AddViewModel(const FMVVMBlueprintViewModelContext& NewContext);`
- L100 _public prototype_ `bool RemoveViewModel(FGuid ViewModelId);`
- L101 _public prototype_ `int32 RemoveViewModels(const TArrayView<FGuid> ViewModelIds);`
- L102 _public prototype_ `bool RenameViewModel(FName OldViewModelName, FName NewViewModelName);`
- L103 _public prototype_ `bool ReparentViewModel(FGuid ViewModelId, const UClass* ViewModelClass);`
- L105 _public function_ `const TArrayView<const FMVVMBlueprintViewModelContext> GetViewModels() const`
- L110 _public prototype_ `const FMVVMBlueprintViewBinding* FindBinding(const UWidget* Widget, const FProperty* Property) const;`
- L111 _public prototype_ `FMVVMBlueprintViewBinding* FindBinding(const UWidget* Widget, const FProperty* Property);`
- L113 _public prototype_ `void RemoveBinding(const FMVVMBlueprintViewBinding* Binding);`
- L114 _public prototype_ `const FMVVMBlueprintViewBinding* DuplicateBinding(const FMVVMBlueprintViewBinding* Binding);`
- L116 _public prototype_ `void RemoveBindingAt(int32 Index);`
- L118 _public prototype_ `FMVVMBlueprintViewBinding& AddDefaultBinding();`
- L120 _public function_ `int32 GetNumBindings() const`
- L125 _public prototype_ `FMVVMBlueprintViewBinding* GetBindingAt(int32 Index);`
- L126 _public prototype_ `const FMVVMBlueprintViewBinding* GetBindingAt(int32 Index) const;`
- L127 _public prototype_ `FMVVMBlueprintViewBinding* GetBinding(FGuid Id);`
- L128 _public prototype_ `const FMVVMBlueprintViewBinding* GetBinding(FGuid Id) const;`
- L130 _public function_ `TArrayView<FMVVMBlueprintViewBinding> GetBindings()`
- L135 _public function_ `const TArrayView<const FMVVMBlueprintViewBinding> GetBindings() const`
- L140 _public prototype_ `UMVVMBlueprintViewEvent* AddDefaultEvent();`
- L141 _public prototype_ `void AddEvent(UMVVMBlueprintViewEvent* Event);`
- L142 _public prototype_ `void RemoveEvent(UMVVMBlueprintViewEvent* Event);`
- L143 _public prototype_ `void ReplaceEvent(UMVVMBlueprintViewEvent* OldEvent, UMVVMBlueprintViewEvent* NewEvent);`
- L144 _public prototype_ `UMVVMBlueprintViewEvent* DuplicateEvent(UMVVMBlueprintViewEvent* Event);`
- L146 _public function_ `TArrayView<TObjectPtr<UMVVMBlueprintViewEvent>> GetEvents()`
- L151 _public function_ `const TArrayView<const TObjectPtr<UMVVMBlueprintViewEvent>> GetEvents() const`
- L156 _public prototype_ `UMVVMBlueprintViewCondition* AddDefaultCondition();`
- L157 _public prototype_ `void AddCondition(UMVVMBlueprintViewCondition* Condition);`
- L158 _public prototype_ `void RemoveCondition(UMVVMBlueprintViewCondition* Condition);`
- L159 _public prototype_ `void ReplaceCondition(UMVVMBlueprintViewCondition* OldCondition, UMVVMBlueprintViewCondition* NewCondition);`
- L160 _public prototype_ `UMVVMBlueprintViewCondition* DuplicateCondition(UMVVMBlueprintViewCondition* Condition);`
- L162 _public function_ `TArrayView<TObjectPtr<UMVVMBlueprintViewCondition>> GetConditions()`
- L167 _public function_ `const TArrayView<const TObjectPtr<UMVVMBlueprintViewCondition>> GetConditions() const`
- L172 _public function_ `bool HasAnyTypeOfBinding()`
- L177 _public prototype_ `TArray<FText> GetBindingMessages(FGuid Id, UE::MVVM::EBindingMessageType InMessageType) const;`
- L178 _public prototype_ `bool HasBindingMessage(FGuid Id) const;`
- L179 _public prototype_ `bool HasBindingMessage(FGuid Id, UE::MVVM::EBindingMessageType InMessageType) const;`
- L180 _public prototype_ `void AddMessageToBinding(FGuid Id, UE::MVVM::FBindingMessage MessageToAdd);`
- L181 _public prototype_ `void ResetBindingMessages();`
- L183 _public function_ `FGuid GetCompiledBindingLibraryId() const`
- L189 _public prototype_ `virtual void PostLoad() override;`
- L190 _public prototype_ `virtual void PreSave(FObjectPreSaveContext Context) override;`
- L191 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L192 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChainEvent) override;`
- L193 _public prototype_ `virtual void PostEditUndo() override;`
- L195 _public prototype_ `void AddAssetTags(FAssetRegistryTagsContext Context) const;`
- L197 _public prototype_ `void AddAssetTags(TArray<FAssetRegistryTag>& OutTags) const;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L198 _public prototype_ `void OnFieldRenamed(UClass* FieldOwnerClass, FName OldObjectName, FName NewObjectName);`
- L201 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L203 _public prototype_ `DECLARE_EVENT(UMVVMBlueprintView, FOnBindingsUpdated);`
- L204 _public member_ `FOnBindingsUpdated OnBindingsUpdated;`
- L206 _public prototype_ `DECLARE_EVENT(UMVVMBlueprintView, FOnBindingsAdded);`
- L207 _public member_ `FOnBindingsAdded OnBindingsAdded;`
- L209 _public prototype_ `DECLARE_EVENT(UMVVMBlueprintView, FOnEventsUpdated);`
- L210 _public member_ `FOnEventsUpdated OnEventsUpdated;`
- L212 _public prototype_ `DECLARE_EVENT(UMVVMBlueprintView, FOnConditionsUpdated);`
- L213 _public member_ `FOnConditionsUpdated OnConditionsUpdated;`
- L215 _public prototype_ `DECLARE_EVENT_OneParam(UMVVMBlueprintView, FOnEventParametersRegenerate, UMVVMBlueprintViewEvent*);`
- L216 _public member_ `FOnEventParametersRegenerate OnEventParametersRegenerate;`
- L218 _public prototype_ `DECLARE_EVENT_OneParam(UMVVMBlueprintView, FOnConditionParametersRegenerate, UMVVMBlueprintViewCondition*);`
- L219 _public member_ `FOnConditionParametersRegenerate OnConditionParametersRegenerate;`
- L221 _public prototype_ `DECLARE_EVENT(UMVVMBlueprintView, FOnViewModelsUpdated);`
- L222 _public member_ `FOnViewModelsUpdated OnViewModelsUpdated;`
- L226 _public member_ `TArray<TObjectPtr<UEdGraph>> TemporaryGraph;` — `UPROPERTY(Transient, NonTransactional)` — Use during compilation to clean the automatically generated graph.
- L230 _public member_ `TArray<FName> TemporaryGraphNames;` — `UPROPERTY(Transient)` — Use during compilation to clean the automatically generated graph.
- L234 _private member_ `TObjectPtr<UMVVMBlueprintViewSettings> Settings;` — `UPROPERTY(Instanced)`
- L237 _private member_ `TArray<FMVVMBlueprintViewBinding> Bindings;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel")`
- L240 _private member_ `TArray<TObjectPtr<UMVVMBlueprintViewEvent>> Events;` — `UPROPERTY(Instanced, EditAnywhere, Category = "Viewmodel")`
- L243 _private member_ `TArray<TObjectPtr<UMVVMBlueprintViewCondition>> Conditions;` — `UPROPERTY(Instanced, EditAnywhere, Category = "Viewmodel")`
- L246 _private member_ `TArray<FMVVMBlueprintViewModelContext> AvailableViewModels;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel")`
- L249 _private member_ `FGuid CompiledBindingLibraryId;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel", meta = (IgnoreForMemberInitializationTest))`
- L251 _private member_ `TMap<FGuid, TArray<UE::MVVM::FBindingMessage>> BindingMessages;`
- L253 _private member_ `bool bIsContextSensitive;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MVVM` (scope `UE`)
- L203 _delegate_ `DECLARE_EVENT(UMVVMBlueprintView, FOnBindingsUpdated);`
- L206 _delegate_ `DECLARE_EVENT(UMVVMBlueprintView, FOnBindingsAdded);`
- L209 _delegate_ `DECLARE_EVENT(UMVVMBlueprintView, FOnEventsUpdated);`
- L212 _delegate_ `DECLARE_EVENT(UMVVMBlueprintView, FOnConditionsUpdated);`
- L215 _delegate_ `DECLARE_EVENT_OneParam(UMVVMBlueprintView, FOnEventParametersRegenerate, UMVVMBlueprintViewEvent*);`
- L218 _delegate_ `DECLARE_EVENT_OneParam(UMVVMBlueprintView, FOnConditionParametersRegenerate, UMVVMBlueprintViewCondition*);`
- L221 _delegate_ `DECLARE_EVENT(UMVVMBlueprintView, FOnViewModelsUpdated);`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMBlueprintViewBinding.h` (Public)


#### struct `FMVVMBlueprintViewConversionPath`  
`struct FMVVMBlueprintViewConversionPath`  
_L21-87_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public member_ `FMemberReference DestinationToSourceFunction_DEPRECATED;` — `UPROPERTY()` — The Conversion function when converting the value from the destination to the source. @note if a wrapper is needed, this is the function that is wrapped.
- L39 _public member_ `FName DestinationToSourceWrapper_DEPRECATED;` — `UPROPERTY()` — The name of the graph that contains the conversion function when converting the value from the destination to the source. Valid when the function needs a wrapper and when the graph is generated on the fly.
- L47 _public member_ `FMemberReference SourceToDestinationFunction_DEPRECATED;` — `UPROPERTY()` — The Conversion function when converting the value from the source to the destination. @note if a wrapper is needed, this is the function that is wrapped.
- L55 _public member_ `FName SourceToDestinationWrapper_DEPRECATED;` — `UPROPERTY()` — The name of the graph that contains the conversion function when converting the value from the source to the destination. When the function needs a wrapper. Valid also when the graph is generated on the fly.
- L62 _public member_ `TObjectPtr<UMVVMBlueprintViewConversionFunction> DestinationToSourceConversion;` — `UPROPERTY(VisibleAnywhere, NoClear, Category = "Viewmodel", Instanced)` — The graph that contains the conversion function when converting the value from the destination to the source. When the function doesn't need a wrapper.
- L69 _public member_ `TObjectPtr<UMVVMBlueprintViewConversionFunction> SourceToDestinationConversion;` — `UPROPERTY(VisibleAnywhere, NoClear, Category = "Viewmodel", Instanced)` — The graph that contains the conversion function when converting the value from the source to the destination. When the function doesn't need a wrapper.
- L72 _public function_ `UMVVMBlueprintViewConversionFunction* GetConversionFunction(bool bSourceToDestination) const`
- L77 _public prototype_ `void GenerateWrapper(UBlueprint* Blueprint);`
- L78 _public prototype_ `void SavePinValues(UBlueprint* Blueprint);`
- L79 _public prototype_ `void DeprecateViewConversionFunction(UBlueprint* Blueprint, FMVVMBlueprintViewBinding& Owner);`
- L83 _public prototype_ `FMVVMBlueprintViewConversionPath() = default;`
- L84 _public prototype_ `FMVVMBlueprintViewConversionPath(const FMVVMBlueprintViewConversionPath&) = default;`
- L85 _public prototype_ `FMVVMBlueprintViewConversionPath& operator=(const FMVVMBlueprintViewConversionPath&) = default;`

#### struct `FMVVMBlueprintViewBinding`  
`struct FMVVMBlueprintViewBinding`  
_L93-146_
- reflection: `USTRUCT(BlueprintType)`
- L98 _public member_ `FMVVMBlueprintPropertyPath SourcePath;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L101 _public member_ `FMVVMBlueprintPropertyPath DestinationPath;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L105 _public member_ `EMVVMBindingMode BindingType = EMVVMBindingMode::OneWayToDestination;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel")`
- L108 _public member_ `bool bOverrideExecutionMode = false;` — `UPROPERTY()`
- L111 _public member_ `EMVVMExecutionMode OverrideExecutionMode = EMVVMExecutionMode::Immediate;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", meta=(EditCondition="bOverrideExecutionMode"))`
- L115 _public member_ `FMVVMBlueprintViewConversionPath Conversion;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L119 _public member_ `FGuid BindingId;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — The unique ID of this binding.
- L123 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel")` — Whether the binding is enabled or disabled by default. The instance may enable the binding at runtime.
- L127 _public member_ `bool bCompile = true;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel")` — The binding is visible in the editor, but is not compiled and cannot be used at runtime.
- L132 _public prototype_ `FName GetFName() const;` — Get an internal name. For use in the UI, use GetDisplayNameString()
- L138 _public prototype_ `FString GetDisplayNameString(const UWidgetBlueprint* WidgetBlueprint, bool bUseDisplayName = false) const;` — Get a string that identifies this binding. This is of the form: Widget.Property <- ViewModel.Property
- L145 _public prototype_ `FString GetSearchableString(const UWidgetBlueprint* WidgetBlueprint) const;` — Get a string that identifies this binding and is specifically formatted for search. This includes the display name and variable name of all fields and widgets, as well as all function keywords. For use in the UI, use GetDisplayNameString()

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMBlueprintViewCompilerInterface.h` (Public)


#### struct `UE::MVVM::Compiler::FCompilerBindingHandle`  
`struct FCompilerBindingHandle`  
_L16-55_
- L19 _public function_ `explicit FCompilerBindingHandle() : Id(0)`
- L24 _public function_ `static FCompilerBindingHandle MakeHandle()`
- L32 _public function_ `bool IsValid() const`
- L37 _public function_ `bool operator==(const FCompilerBindingHandle& Other) const`
- L42 _public function_ `bool operator!=(const FCompilerBindingHandle& Other) const`
- L53 _private member_ `static int32 IdGenerator;`
- L54 _private member_ `int32 Id;`

#### enum `UE::MVVM::Compiler::EMessageType`  
`enum class EMessageType`  
_L57-62_
- L59 _public enumerator_ `Info = 0`
- L60 _public enumerator_ `Warning = 1`
- L61 _public enumerator_ `Error = 2`

#### struct `UE::MVVM::Compiler::FBlueprintViewUserWidgetWidgetProperty`  
`struct FBlueprintViewUserWidgetWidgetProperty`  
_L67-70_
- desc: Data to be used by the compiler to create a property for a widget in the widget tree
- L69 _public member_ `FName WidgetName;`

#### struct `UE::MVVM::Compiler::FBlueprintViewUserWidgetProperty`  
`struct FBlueprintViewUserWidgetProperty`  
_L75-87_
- desc: Data to be used by the compiler to create new user widget properties
- L77 _public member_ `UClass* AuthoritativeClass = nullptr;`
- L78 _public member_ `FName Name;`
- L79 _public member_ `FText DisplayName;`
- L80 _public member_ `FString CategoryName;`
- L81 _public member_ `FGuid Guid;`
- L82 _public member_ `bool bExposeOnSpawn = false;`
- L83 _public member_ `bool bPrivate = false;`
- L84 _public member_ `bool bReadOnly = false;`
- L86 _public member_ `const FProperty* Property = nullptr;`

#### class `UE::MVVM::Compiler::IMVVMBlueprintViewPrecompile`  
`class IMVVMBlueprintViewPrecompile`  
_L92-155_
- desc: Exposed interface of MVVMViewBlueprintCompiler to be used in view extensions (MVVMViewBlueprintViewExtension) at precompile step
- L109 _public prototype_ `virtual const UMVVMBlueprintView* GetBlueprintView() const = 0;`
- L112 _public prototype_ `virtual const TMap<FName, UWidget*>& GetWidgetNameToWidgetPointerMap() const = 0;` — Returns a map of widget name to the widget pointer for all widgets in the blueprint.
- L115 _public prototype_ `virtual TArray<Compiler::FCompilerBindingHandle> GetAllBindings() const = 0;` — Returns all the bindings via handles
- L118 _public prototype_ `virtual TArray<TArray<UE::MVVM::FMVVMConstFieldVariant>> GetBindingReadFields(Compiler::FCompilerBindingHandle BindingHandle) = 0;` — Returns the field path for all the read fields of a binding (passed by handle)
- L121 _public prototype_ `virtual TArray<UE::MVVM::FMVVMConstFieldVariant> GetBindingWriteFields(Compiler::FCompilerBindingHandle BindingHandle) = 0;` — Returns the field path for the write field of a binding (passed by handle)
- L124 _public prototype_ `virtual const FProperty* GetBindingSourceProperty(Compiler::FCompilerBindingHandle BindingHandle) = 0;` — Returns the source of a binding (passed by handle) if it's valid
- L130 _public prototype_ `virtual TValueOrError<FCompiledBindingLibraryCompiler::FFieldPathHandle, FText> AddObjectFieldPath(const FObjectFieldPathArgs& Args) = 0;` — Add a new object property to the compiler. Store the returned the handle of this function to access the compiled path during Compile step by calling GetFieldPath.
- L136 _public prototype_ `virtual TValueOrError<FCompiledBindingLibraryCompiler::FFieldPathHandle, FText> AddFieldPath(TArrayView<const FMVVMConstFieldVariant> InFieldPath, bool bInRead) = 0;` — Adds a new field to the compiler. Store the returned the handle of this function to access the compiled path during Compile step by calling GetFieldPath.
- L142 _public prototype_ `virtual void AddMessageForBinding(Compiler::FCompilerBindingHandle BindingHandle, const FText& MessageText, EMessageType MessageType) const = 0;` — Shows a message for the given binding. If this is an error message, it will cause the blueprint compilation to fail. Next steps will still be executed.
- L148 _public prototype_ `virtual void AddMessage(const FText& MessageText, EMessageType MessageType) = 0;` — Shows a message in the compile logs. If this is an error message, it will cause the blueprint compilation to fail. Next steps will still be executed.
- L154 _public prototype_ `virtual void MarkPrecompileStepInvalid() = 0;` — Lets the compiler know that the precompile step for this extension failed. Calling this will cause the blueprint compilation to fail and next steps won't be executed.

#### struct `UE::MVVM::Compiler::IMVVMBlueprintViewPrecompile::FObjectFieldPathArgs`  
`struct FObjectFieldPathArgs`  
_L95-107_
- L97 _public function_ `FObjectFieldPathArgs(UWidgetBlueprintGeneratedClass* InClass, const FString& InObjectPath, UClass* InExpectedType) : Class(InClass) , ObjectPath(InObjectPath) , ExpectedType(InExpectedType)`
- L104 _public member_ `UWidgetBlueprintGeneratedClass* Class;`
- L105 _public member_ `FString ObjectPath;`
- L106 _public member_ `UClass* ExpectedType;`

#### class `UE::MVVM::Compiler::IMVVMBlueprintViewCompile`  
`class IMVVMBlueprintViewCompile`  
_L160-194_
- desc: Exposed interface of MVVMViewBlueprintCompiler to be used in view extensions (MVVMViewBlueprintViewExtension) at compile step
- L163 _public prototype_ `virtual const UMVVMBlueprintView* GetBlueprintView() const = 0;`
- L166 _public prototype_ `virtual const TMap<FName, UWidget*>& GetWidgetNameToWidgetPointerMap() const = 0;` — Returns a map of widget name to the widget pointer for all widgets in the blueprint.
- L172 _public prototype_ `virtual TValueOrError<FMVVMVCompiledFieldPath, void> GetFieldPath(FCompiledBindingLibraryCompiler::FFieldPathHandle FieldPath) = 0;` — Get the compiled field path of the passed handle. The field path should have been added in the precompile step using AddObjectFieldPath or AddFieldPath and the returned handle should be stored.
- L178 _public prototype_ `virtual void AddMessageForBinding(Compiler::FCompilerBindingHandle BindingHandle, const FText& MessageText, EMessageType MessageType) const = 0;` — Shows a message for the given binding. If this is an error message, it will cause the blueprint compilation to fail. Next steps will still be executed.
- L184 _public prototype_ `virtual void AddMessage(const FText& MessageText, EMessageType MessageType) = 0;` — Shows a message in the compile logs. If this is an error message, it will cause the blueprint compilation to fail. Next steps will still be executed.
- L190 _public prototype_ `virtual void MarkCompileStepInvalid() = 0;` — Lets the compiler know that the compile step for this extension failed. Calling this will cause the blueprint compilation to fail and next steps won't be executed.
- L193 _public prototype_ `virtual UMVVMViewClassExtension* CreateViewClassExtension(TSubclassOf<UMVVMViewClassExtension> ExtensionClass) = 0;` — Creates an extension object of the given class and adds it to the view class to be invoked at runtime.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MVVM` (scope `UE`)
- L13 _namespace_ `namespace Compiler` (scope `UE::MVVM`)
- L47 _function_ `friend uint32 GetTypeHash(const FCompilerBindingHandle& Handle)` (scope `UE::MVVM::Compiler`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMBlueprintViewCondition.h` (Public)


#### class `UMVVMBlueprintViewCondition`  
`class UMVVMBlueprintViewCondition : public UObject`  
_L27-214_
- reflection: `UCLASS(MinimalAPI, Within = MVVMBlueprintView)`
- inherits: `UObject`
- desc: Binding for an event that MVVM will listen too. Does not imply the MVVM graph itself will use events. Ex: UButton::OnClick
- L48 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel")` — Whether the event is enabled or disabled by default. The instance may enable the event at runtime.
- L52 _public member_ `bool bCompile = true;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel")` — The event is visible in the editor, but is not compiled and cannot be used at runtime.
- L55 _public function_ `const FMVVMBlueprintPropertyPath& GetConditionPath() const`
- L59 _public prototype_ `void SetConditionPath(FMVVMBlueprintPropertyPath ConditionPath);`
- L61 _public function_ `const FMVVMBlueprintPropertyPath& GetDestinationPath() const`
- L65 _public prototype_ `void SetDestinationPath(FMVVMBlueprintPropertyPath DestinationPath);`
- L67 _public function_ `EMVVMConditionOperation GetOperation() const`
- L72 _public prototype_ `void SetOperation(EMVVMConditionOperation Operation);`
- L74 _public function_ `float GetOperationValue() const`
- L78 _public prototype_ `void SetOperationValue(float NewValue);`
- L80 _public function_ `float GetOperationMaxValue() const`
- L84 _public prototype_ `void SetOperationMaxValue(float NewMaxValue);`
- L87 _public function_ `UEdGraph* GetWrapperGraph() const`
- L92 _public function_ `FName GetWrapperGraphName() const`
- L102 _public prototype_ `void RemoveWrapperGraph(ERemoveWrapperGraphParam ActionForCurrentValues = RemoveConversionFunctionCurrentValues);`
- L104 _public function_ `UK2Node* GetWrapperDestinationNode() const`
- L109 _public prototype_ `UEdGraph* GetOrCreateWrapperGraph();`
- L111 _public prototype_ `void RecreateWrapperGraph();`
- L114 _public function_ `TArrayView<const FMVVMBlueprintPin> GetPins() const`
- L120 _public prototype_ `void SavePinValues();` — Generates SavedPins from the wrapper graph, if it exists.
- L122 _public prototype_ `void UpdatePinValues();` — Keep the orphaned pins. Add the missing pins.
- L124 _public prototype_ `bool HasOrphanedPin() const;` — Keep the orphaned pins. Add the missing pins.
- L126 _public prototype_ `void UpdateConditionKey(FMVVMViewClass_ConditionKey ConditionKey);` — Condition sources are tested at runtime to check if they are valid.
- L128 _public prototype_ `UEdGraphPin* GetOrCreateGraphPin(const FMVVMBlueprintPinId& Pin);`
- L130 _public prototype_ `FMVVMBlueprintPropertyPath GetPinPath(const FMVVMBlueprintPinId& Pin) const;`
- L131 _public prototype_ `void SetPinPath(const FMVVMBlueprintPinId& Pin, const FMVVMBlueprintPropertyPath& Path);`
- L133 _public prototype_ `void SetPinPathNoGraphGeneration(const FMVVMBlueprintPinId& Pin, const FMVVMBlueprintPropertyPath& Path);` — To set a pin when loading the asset (no graph generation)
- L135 _public member_ `FSimpleMulticastDelegate OnWrapperGraphModified;`
- L138 _public prototype_ `TArray<FText> GetCompilationMessages(EMessageType InMessageType) const;`
- L139 _public prototype_ `bool HasCompilationMessage(EMessageType InMessageType) const;`
- L140 _public prototype_ `void AddCompilationToBinding(FMessage MessageToAdd) const;`
- L141 _public prototype_ `void ResetCompilationMessages();`
- L147 _public prototype_ `FText GetDisplayName(bool bUseDisplayName) const;` — Get a string that identifies this event.
- L154 _public prototype_ `FString GetSearchableString() const;` — Get a string that identifies this event and is specifically formatted for search. This includes the display name and variable name of all fields and widgets, as well as all function keywords. For use in the UI, use GetDisplayNameString()
- L157 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChainEvent) override;`
- L160 _private prototype_ `const UFunction* GetDestinationSignature() const;`
- L161 _private prototype_ `void HandleGraphChanged(const FEdGraphEditAction& Action);`
- L162 _private prototype_ `void HandleUserDefinedPinRenamed(UK2Node* InNode, FName OldPinName, FName NewPinName);`
- L163 _private prototype_ `UWidgetBlueprint* GetWidgetBlueprintInternal() const;`
- L164 _private prototype_ `void SetCachedWrapperGraphInternal(UEdGraph* Graph, UK2Node* Node, UMVVMK2Node_IsConditionValid* SourceNode);`
- L165 _private prototype_ `UEdGraph* CreateWrapperGraphInternal();`
- L166 _private prototype_ `void LoadPinValuesInternal();`
- L167 _private prototype_ `void UpdateConditionKeyInternal();`
- L171 _private member_ `FMVVMBlueprintPropertyPath ConditionPath;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L174 _private member_ `EMVVMConditionOperation ConditionOperation;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L177 _private member_ `float Value;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L180 _private member_ `float MaxValue;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L183 _private member_ `FMVVMBlueprintPropertyPath DestinationPath;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L190 _private member_ `TArray<FMVVMBlueprintPin> SavedPins;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — The pin that are modified and we saved data. The data may not be modified. We used the default value of the K2Node in that case.
- L193 _private member_ `FName GraphName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L196 _private member_ `FMVVMViewClass_ConditionKey ConditionKey;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L198 _private member_ `mutable TArray<FMessage> Messages;`
- L199 _private member_ `bool bLoadingPins = false;`
- L202 _private member_ `mutable TObjectPtr<UEdGraph> CachedWrapperGraph;` — `UPROPERTY(Transient, DuplicateTransient)`
- L205 _private member_ `mutable TObjectPtr<UK2Node> CachedWrapperDestinationNode;` — `UPROPERTY(Transient, DuplicateTransient)`
- L208 _private member_ `mutable TObjectPtr<UMVVMK2Node_IsConditionValid> CachedConditionValidNode;` — `UPROPERTY(Transient, DuplicateTransient)`
- L210 _private member_ `FDelegateHandle OnGraphChangedHandle;`
- L211 _private member_ `FDelegateHandle OnUserDefinedPinRenamedHandle;`
- L213 _private member_ `bool bNeedsToRegenerateChildren;`

#### enum `UMVVMBlueprintViewCondition::EMessageType`  
`enum class EMessageType : uint8`  
_L32-37_
- L34 _public enumerator_ `Info`
- L35 _public enumerator_ `Warning`
- L36 _public enumerator_ `Error`

#### struct `UMVVMBlueprintViewCondition::FMessage`  
`struct FMessage`  
_L39-43_
- L41 _public member_ `FText MessageText;`
- L42 _public member_ `EMessageType MessageType;`

#### enum `UMVVMBlueprintViewCondition::ERemoveWrapperGraphParam`  
`enum ERemoveWrapperGraphParam`  
_L97-101_
- L99 _public enumerator_ `RemoveConversionFunctionCurrentValues` — when removing or changing the conversion function, we want to remove all the conversion function parameters
- L100 _public enumerator_ `LeaveConversionFunctionCurrentValues` — when we remove the wrapper graph because the destination path or condition properties are changed, we want to keep the conversion function parameters

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMBlueprintViewConversionFunction.h` (Public)


#### class `UMVVMBlueprintViewConversionFunction`  
`class UMVVMBlueprintViewConversionFunction : public UObject`  
_L27-218_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: A conversion function converts between the source and destiation of a binding. Internally that function may be using native C++, K2Nodes, UFunctions, Events, etc.
- L32 _public prototype_ `static bool IsValidConversionFunction(const UBlueprint* WidgetBlueprint, const UFunction* Function);`
- L33 _public prototype_ `static bool IsValidConversionNode(const UBlueprint* WidgetBlueprint, const TSubclassOf<UK2Node> Function);`
- L37 _public prototype_ `const UFunction* GetCompiledFunction(const UClass* SelfContext) const;` — @return the conversion function uses at runtime. The wrapper function if complex or GetFunction is simple.
- L40 _public prototype_ `FName GetCompiledFunctionName(const UClass* SelfContext) const;` — @return the conversion function uses at runtime. The wrapper function if complex or GetFunction is simple.
- L44 _public prototype_ `TVariant<const UFunction*, TSubclassOf<UK2Node>> GetConversionFunction(const UBlueprint* SelfContext) const;` — `UE_DEPRECATED(5.4, "GetConversionFunction that returns a variant is deprecated.")` — @return the conversion function.
- L47 _public prototype_ `FMVVMBlueprintFunctionReference GetConversionFunction() const;` — @return the conversion function.
- L50 _public prototype_ `void Initialize(UBlueprint* SelfContext, FName GraphName, FMVVMBlueprintFunctionReference Function);` — Set the function. Generate a Graph.
- L53 _public prototype_ `void InitializeFromFunction(UBlueprint* SelfContext, FName GraphName, const UFunction* Function);` — Set the function. Generate a Graph.
- L56 _public prototype_ `void Deprecation_InitializeFromWrapperGraph(UBlueprint* SelfContext, UEdGraph* Graph);` — For deprecation
- L59 _public prototype_ `void Deprecation_InitializeFromMemberReference(UBlueprint* SelfContext, FName GraphName, FMemberReference MemberReference, const FMVVMBlueprintPropertyPath& Source);` — For deprecation
- L62 _public prototype_ `void Deprecation_SetWrapperGraphName(UBlueprint* Context, FName GraphName, const FMVVMBlueprintPropertyPath& Source);` — For deprecation
- L69 _public prototype_ `bool IsValid(const UBlueprint* SelfContext) const;` — The conversion is valid. The function was valid when created but may not be anymore. It doesn't check if the source and destination are valid.
- L72 _public prototype_ `bool NeedsWrapperGraph(const UBlueprint* SelfContext) const;` — The function has more than one argument and requires a wrapper or it uses a FunctionNode.
- L75 _public prototype_ `bool IsWrapperGraphTransient() const;` — The wrapper Graph is generated on load/compile and is not saved.
- L78 _public prototype_ `bool IsUbergraphPage() const;` — True if the graph is going to be used for an ubergraph page.
- L80 _public function_ `const FMVVMBlueprintPropertyPath& GetDestinationPath() const`
- L84 _public prototype_ `void SetDestinationPath(FMVVMBlueprintPropertyPath DestinationPath);`
- L87 _public function_ `UEdGraph* GetWrapperGraph() const` — Return the wrapper graph, if it exists.
- L92 _public function_ `FName GetWrapperGraphName() const`
- L98 _public function_ `UK2Node* GetWrapperNode() const` — Return the wrapper node, if it exists.
- L104 _public function_ `UEdGraphNode* GetLatentNodeUUID() const` — Return latent UUID Node.
- L113 _public prototype_ `UEdGraph* GetOrCreateIntermediateWrapperGraph(FKismetCompilerContext& Context);` — If needed, create the graph and all the nodes for that graph when compiling. Returns the existing one, if one was created from GetOrCreateWrapperGraph.
- L116 _public prototype_ `UEdGraph* GetOrCreateWrapperGraph(UBlueprint* Blueprint);` — If needed, create the graph and all the nodes for that graph.
- L118 _public prototype_ `void RecreateWrapperGraph(UBlueprint* Blueprint);`
- L124 _public prototype_ `void RemoveWrapperGraph(UBlueprint* Blueprint);` — The conversion function is going to be removed from the Blueprint. Do any cleanup that is needed.
- L130 _public prototype_ `UEdGraphPin* GetOrCreateGraphPin(UBlueprint* Blueprint, const FMVVMBlueprintPinId& PinId);` — Returns the pin from the graph. Create the graph and all the nodes for that graph if the graph doesn't exist and it's needed.
- L132 _public function_ `const TArrayView<const FMVVMBlueprintPin> GetPins() const`
- L138 _public prototype_ `void SetGraphPin(UBlueprint* Blueprint, const FMVVMBlueprintPinId& PinId, const FMVVMBlueprintPropertyPath& Value);`
- L141 _public prototype_ `void SavePinValues(UBlueprint* Blueprint);` — Generates SavedPins from the wrapper graph, if it exists.
- L143 _public prototype_ `void UpdatePinValues(UBlueprint* Blueprint);` — Keep the orphaned pins. Add the missing pins.
- L145 _public prototype_ `bool HasOrphanedPin() const;` — Keep the orphaned pins. Add the missing pins.
- L147 _public member_ `FSimpleMulticastDelegate OnWrapperGraphModified;`
- L149 _public prototype_ `virtual void PostLoad() override;`
- L152 _private prototype_ `void HandleGraphChanged(const FEdGraphEditAction& Action, TWeakObjectPtr<UBlueprint> Context);`
- L153 _private prototype_ `void HandleUserDefinedPinRenamed(UK2Node* InNode, FName OldPinName, FName NewPinName, TWeakObjectPtr<UBlueprint> WeakBlueprint);`
- L154 _private prototype_ `void SetCachedWrapperGraph(UBlueprint* Blueprint, UEdGraph* CachedGraph, UK2Node* CachedNode);`
- L155 _private prototype_ `UEdGraph* CreateWrapperGraphInternal(FKismetCompilerContext& Context);`
- L156 _private prototype_ `UEdGraph* CreateWrapperGraphInternal(UBlueprint* Blueprint);`
- L157 _private prototype_ `bool NeedsWrapperGraphInternal(const UClass* SkeletalSelfContext) const;`
- L158 _private prototype_ `void LoadPinValuesInternal(UBlueprint* Blueprint);`
- L159 _private prototype_ `FName GenerateUniqueGraphName() const;`
- L160 _private prototype_ `void CreateWrapperGraphName();`
- L161 _private prototype_ `void Reset();`
- L163 _private prototype_ `bool IsConversionFunctionAsyncNode();`
- L172 _private member_ `FMVVMBlueprintPropertyPath DestinationPath;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — Destination of the binding, currently only saved when the conversion function uses async nodes. Async graphs will handle value setting internally rather than using the MVVM subsystem.
- L179 _private member_ `FMVVMBlueprintFunctionReference ConversionFunction;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — Conversion reference. It can be simple, complex or a K2Node. @note The conversion is complex
- L183 _private member_ `FName GraphName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — Name of the generated graph if a wrapper is needed.
- L190 _private member_ `TArray<FMVVMBlueprintPin> SavedPins;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — The pin that are modified and we saved data. The data may not be modified. We used the default value of the K2Node in that case.
- L193 _private member_ `bool bWrapperGraphTransient = true;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L196 _private member_ `bool bIsUbergraphPage = false;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L199 _private member_ `mutable TObjectPtr<UEdGraph> CachedWrapperGraph;` — `UPROPERTY(Transient, DuplicateTransient)`
- L202 _private member_ `mutable TObjectPtr<UK2Node> CachedWrapperNode;` — `UPROPERTY(Transient, DuplicateTransient)`
- L208 _private member_ `TObjectPtr<UEdGraphNode> LatentEventNodeUUID;` — `UPROPERTY(Transient)` — Events require a node UUID for the latent manager to handle lantents with
- L210 _private member_ `FDelegateHandle OnGraphChangedHandle;`
- L211 _private member_ `FDelegateHandle OnUserDefinedPinRenamedHandle;`
- L212 _private member_ `bool bLoadingPins = false;`
- L215 _private member_ `FMemberReference FunctionReference_DEPRECATED;` — `UPROPERTY()`
- L217 _private member_ `TSubclassOf<UK2Node> FunctionNode_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMBlueprintViewEvent.h` (Public)


#### class `UMVVMBlueprintViewEvent`  
`class UMVVMBlueprintViewEvent : public UObject`  
_L26-189_
- reflection: `UCLASS(MinimalAPI, Within = MVVMBlueprintView)`
- inherits: `UObject`
- desc: Binding for an event that MVVM will listen too. Does not imply the MVVM graph itself will use events. Ex: UButton::OnClick
- L45 _public prototype_ `static bool Supports(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintPropertyPath& PropertyPath);` — @return true if the property path contains a multicast delegate property.
- L50 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel")` — Whether the event is enabled or disabled by default. The instance may enable the event at runtime.
- L54 _public member_ `bool bCompile = true;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel")` — The event is visible in the editor, but is not compiled and cannot be used at runtime.
- L57 _public function_ `const FMVVMBlueprintPropertyPath& GetEventPath() const`
- L61 _public prototype_ `void SetEventPath(FMVVMBlueprintPropertyPath EventPath);`
- L63 _public function_ `const FMVVMBlueprintPropertyPath& GetDestinationPath() const`
- L67 _public prototype_ `void SetDestinationPath(FMVVMBlueprintPropertyPath DestinationPath);`
- L70 _public function_ `UEdGraph* GetWrapperGraph() const`
- L75 _public function_ `FName GetWrapperGraphName() const`
- L85 _public prototype_ `void RemoveWrapperGraph(ERemoveWrapperGraphParam ActionForCurrentValues = RemoveConversionFunctionCurrentValues);`
- L87 _public function_ `UK2Node* GetWrapperNode() const`
- L92 _public prototype_ `UEdGraph* GetOrCreateWrapperGraph();`
- L94 _public prototype_ `void RecreateWrapperGraph();`
- L97 _public function_ `TArrayView<const FMVVMBlueprintPin> GetPins() const`
- L103 _public prototype_ `void SavePinValues();` — Generates SavedPins from the wrapper graph, if it exists.
- L105 _public prototype_ `void UpdatePinValues();` — Keep the orphaned pins. Add the missing pins.
- L107 _public prototype_ `bool HasOrphanedPin() const;` — Keep the orphaned pins. Add the missing pins.
- L109 _public prototype_ `void UpdateEventKey(FMVVMViewClass_EventKey EventKey);` — Event sources are tested at runtime to check if they are valid.
- L111 _public prototype_ `UEdGraphPin* GetOrCreateGraphPin(const FMVVMBlueprintPinId& Pin);`
- L113 _public prototype_ `FMVVMBlueprintPropertyPath GetPinPath(const FMVVMBlueprintPinId& Pin) const;`
- L114 _public prototype_ `void SetPinPath(const FMVVMBlueprintPinId& Pin, const FMVVMBlueprintPropertyPath& Path);`
- L116 _public prototype_ `void SetPinPathNoGraphGeneration(const FMVVMBlueprintPinId& Pin, const FMVVMBlueprintPropertyPath& Path);` — To set a pin when loading the asset (no graph generation)
- L118 _public member_ `FSimpleMulticastDelegate OnWrapperGraphModified;`
- L121 _public prototype_ `TArray<FText> GetCompilationMessages(EMessageType InMessageType) const;`
- L122 _public prototype_ `bool HasCompilationMessage(EMessageType InMessageType) const;`
- L123 _public prototype_ `void AddCompilationToBinding(FMessage MessageToAdd) const;`
- L124 _public prototype_ `void ResetCompilationMessages();`
- L130 _public prototype_ `FText GetDisplayName(bool bUseDisplayName) const;` — Get a string that identifies this event.
- L137 _public prototype_ `FString GetSearchableString() const;` — Get a string that identifies this event and is specifically formatted for search. This includes the display name and variable name of all fields and widgets, as well as all function keywords. For use in the UI, use GetDisplayNameString()
- L140 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChainEvent) override;`
- L143 _private prototype_ `static const UFunction* GetEventSignature(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintPropertyPath& PropertyPath);`
- L144 _private prototype_ `const UFunction* GetEventSignature() const;`
- L145 _private prototype_ `void HandleGraphChanged(const FEdGraphEditAction& Action);`
- L146 _private prototype_ `void HandleUserDefinedPinRenamed(UK2Node* InNode, FName OldPinName, FName NewPinName);`
- L147 _private prototype_ `UWidgetBlueprint* GetWidgetBlueprintInternal() const;`
- L148 _private prototype_ `void SetCachedWrapperGraphInternal(UEdGraph* Graph, UK2Node* Node, UMVVMK2Node_AreSourcesValidForEvent* SourceNode);`
- L149 _private prototype_ `UEdGraph* CreateWrapperGraphInternal();`
- L150 _private prototype_ `void LoadPinValuesInternal();`
- L151 _private prototype_ `void UpdateEventKeyInternal();`
- L155 _private member_ `FMVVMBlueprintPropertyPath EventPath;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L158 _private member_ `FMVVMBlueprintPropertyPath DestinationPath;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L165 _private member_ `TArray<FMVVMBlueprintPin> SavedPins;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")` — The pin that are modified and we saved data. The data may not be modified. We used the default value of the K2Node in that case.
- L168 _private member_ `FName GraphName;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L171 _private member_ `FMVVMViewClass_EventKey EventKey;` — `UPROPERTY(VisibleAnywhere, Category = "Viewmodel")`
- L173 _private member_ `mutable TArray<FMessage> Messages;`
- L174 _private member_ `bool bLoadingPins = false;`
- L177 _private member_ `mutable TObjectPtr<UEdGraph> CachedWrapperGraph;` — `UPROPERTY(Transient, DuplicateTransient)`
- L180 _private member_ `mutable TObjectPtr<UK2Node> CachedWrapperNode;` — `UPROPERTY(Transient, DuplicateTransient)`
- L183 _private member_ `mutable TObjectPtr<UMVVMK2Node_AreSourcesValidForEvent> CachedSourceValidNode;` — `UPROPERTY(Transient, DuplicateTransient)`
- L185 _private member_ `FDelegateHandle OnGraphChangedHandle;`
- L186 _private member_ `FDelegateHandle OnUserDefinedPinRenamedHandle;`
- L188 _private member_ `bool bNeedsToRegenerateChildren;`

#### enum `UMVVMBlueprintViewEvent::EMessageType`  
`enum class EMessageType : uint8`  
_L31-36_
- L33 _public enumerator_ `Info`
- L34 _public enumerator_ `Warning`
- L35 _public enumerator_ `Error`

#### struct `UMVVMBlueprintViewEvent::FMessage`  
`struct FMessage`  
_L38-42_
- L40 _public member_ `FText MessageText;`
- L41 _public member_ `EMessageType MessageType;`

#### enum `UMVVMBlueprintViewEvent::ERemoveWrapperGraphParam`  
`enum ERemoveWrapperGraphParam`  
_L80-84_
- L82 _public enumerator_ `RemoveConversionFunctionCurrentValues` — when removing or changing the conversion function, we want to remove all the conversion function parameters
- L83 _public enumerator_ `LeaveConversionFunctionCurrentValues` — when we remove the wrapper graph because the event path has changed, we want to keep the conversion function parameters

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMBlueprintViewModel.h` (Public)


#### class `UMVVMBlueprintViewModel`  
`class UMVVMBlueprintViewModel : public UObject`  
_L10-15_
- reflection: `UCLASS(MinimalAPI, DisplayName="ViewModel Blueprint")`
- inherits: `UObject`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMBlueprintViewModelContext.h` (Public)


#### enum `EMVVMBlueprintViewModelContextCreationType`  
`enum class EMVVMBlueprintViewModelContextCreationType : uint8`  
_L19-33_
- reflection: `UENUM()`
- L22 _public enumerator_ `Manual` — The viewmodel will be assigned later.
- L24 _public enumerator_ `CreateInstance` — A new instance of the viewmodel will be created when the widget is created.
- L26 _public enumerator_ `GlobalViewModelCollection` — The viewmodel exists and is added to the MVVMSubsystem. It will be fetched there.
- L28 _public enumerator_ `PropertyPath` — The viewmodel will be fetched by evaluating a function or a property path.
- L30 _public enumerator_ `Resolver` — The viewmodel will be fetched by evaluating the resolver object.
- L32 _public enumerator_ `Context` — The viewmodel will be fetched from any local context provider, can also be set manually

#### struct `FMVVMBlueprintViewModelContext`  
`struct FMVVMBlueprintViewModelContext`  
_L46-210_
- reflection: `USTRUCT()`
- L51 _public prototype_ `FMVVMBlueprintViewModelContext() = default;`
- L52 _public prototype_ `FMVVMBlueprintViewModelContext(const UClass* InClass, FName InViewModelName);`
- L54 _public function_ `FGuid GetViewModelId() const`
- L59 _public function_ `FName GetViewModelName() const`
- L64 _public prototype_ `FText GetDisplayName() const;`
- L66 _public function_ `UClass* GetViewModelClass() const`
- L71 _public function_ `void PostSerialize(const FArchive& Ar)`
- L99 _public function_ `bool IsValid() const`
- L104 _public function_ `bool CanRename() const`
- L110 _public prototype_ `[[nodiscard]] TObjectPtr<UMVVMViewModelContextResolver> CreateDefaultResolver(UObject* Outer) const;`
- L116 _private member_ `FGuid ViewModelContextId;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Viewmodel", meta = (DisplayName = "Viewmodel Context Id", NoResetToDefault))` — When the view is spawn, create an instance of the viewmodel.
- L120 _public member_ `TObjectPtr<UClass> NotifyFieldValueClass = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", NoClear, meta = (DisallowCreateNew, AllowedClasses = "/Script/FieldNotification.NotifyFieldValueChanged", DisallowedClasses = "/Script/UMG.Widget", NoResetToDefault))`
- L123 _public member_ `TSubclassOf<UMVVMViewModelBase> ViewModelClass_DEPRECATED;` — `UPROPERTY()`
- L126 _public member_ `FText OverrideDisplayName_DEPRECATED;` — `UPROPERTY()`
- L131 _public member_ `FName ViewModelName;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", meta = (DisplayName = "Viewmodel Name", NoResetToDefault))` — Property name that will be generated.
- L135 _public member_ `EMVVMBlueprintViewModelContextCreationType CreationType = EMVVMBlueprintViewModelContextCreationType::CreateInstance;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel")` — When the view is spawn, create an instance of the viewmodel.
- L139 _public member_ `FName GlobalViewModelIdentifier;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", meta = (DisplayName = "Global Viewmodel Identifier"))` — Identifier of an already registered viewmodel.
- L143 _public member_ `FString ViewModelPropertyPath;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", meta = (DisplayName = "Viewmodel Property Path"))` — The Path to get the viewmodel instance.
- L146 _public member_ `TObjectPtr<UMVVMViewModelContextResolver> Resolver = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", Instanced, meta = (EditInline))`
- L149 _public member_ `TObjectPtr<UMVVMBlueprintInstancedViewModelBase> InstancedViewModel;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", Instanced, NoClear, meta = (ShowOnlyInnerProperties))`
- L156 _public member_ `bool bCreateSetterFunction = false;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", AdvancedDisplay, meta = (DisplayName="Create Public Setter"))` — Generate a public setter for this viewmodel. @note Always true when the Creation Type is Manual.
- L163 _public member_ `bool bCreateGetterFunction = true;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", AdvancedDisplay, meta = (DisplayName = "Create Public Getter"))` — Generate a public getter for this viewmodel. @note Always false when using a Instanced viewmodel.
- L170 _public member_ `bool bOptional = false;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", AdvancedDisplay)` — Optional. Will not warn if the instance is not set or found. @note Always true when the Creation Type is Manual.
- L174 _public member_ `bool bExposeInstanceInEditor = false;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", AdvancedDisplay)` — Expose the viewmodel instance on every instance of the user widget for modification in editor.
- L178 _public member_ `bool bGlobalViewModelCollectionUpdate = false;` — `UPROPERTY(EditAnywhere, Category = "Viewmodel", AdvancedDisplay)` — Auto update the instance when the viewmodel is added/removed/modifed from the global viewmodel collection.
- L181 _public member_ `bool bOverrideForceExecuteBindingsOnSetSource = false;` — `UPROPERTY()`
- L189 _public member_ `bool bForceExecuteBindingsOnSetSource = false;` — `UPROPERTY(EditAnywhere, Category = "View", meta = (EditCondition = "bOverrideForceExecuteBindingsOnSetSource"))` — When a viewmodel is set manually and the viewmodel already initialized, then always execute the bindings associated with that viewmodel. For performance and to keep the same pattern in all UMG, the bindings are usually skip if the new viewmodel value match the previous viewmodel value. This behavior can be desired if the widget is inside a pool or a binding has a side effect with another widget.
- L193 _public member_ `bool bCanRename = true;` — `UPROPERTY()` — Can change the name in the editor.
- L197 _public member_ `bool bCanEdit = true;` — `UPROPERTY()` — Can change properties in the editor.
- L201 _public member_ `bool bCanRemove = true;` — `UPROPERTY()` — Can remove the viewmodel in the editor.
- L205 _public member_ `bool bUseAsInterface = false;` — `UPROPERTY(EditAnywhere, Category = "View")` — Will the viewmodel be handled as a property or as an interface in Verse.
- L209 _private member_ `bool bCreateSetterFunction_Deprecation = false;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMVVMBlueprintViewModelContext> : public TStructOpsTypeTraitsBase2<FMVVMBlueprintViewModelContext>`  
_L213-219_
- inherits: `TStructOpsTypeTraitsBase2<FMVVMBlueprintViewModelContext>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L216-218_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace MVVM` (scope `UE`)
- L38 _prototype_ `[[nodiscard]] TArray<EMVVMBlueprintViewModelContextCreationType> GetAllowedContextCreationType(const UClass* Class);` (scope `UE::MVVM`)
- L217 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon716a1cad0103`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMDeveloperProjectSettings.h` (Public)


#### struct `FMVVMDeveloperProjectWidgetSettings`  
`struct FMVVMDeveloperProjectWidgetSettings`  
_L23-34_
- reflection: `USTRUCT()`
- L29 _public member_ `TSet<FName> DisallowedFieldNames;` — `UPROPERTY(EditAnywhere, config, Category = "Viewmodel")` — Properties or functions name that should not be use for binding (read or write).
- L33 _public member_ `TSet<FName> AdvancedFieldNames;` — `UPROPERTY(EditAnywhere, config, Category = "Viewmodel")` — Properties or functions name that are displayed in the advanced category.

#### enum `EFilterFlag`  
`enum class EFilterFlag : uint8`  
_L37-41_
- reflection: `UENUM()`
- L39 _public enumerator_ `None = 0`
- L40 _public enumerator_ `All = 1 << 0`

#### struct `FMVVMViewBindingFilterSettings`  
`struct FMVVMViewBindingFilterSettings`  
_L45-52_
- reflection: `USTRUCT()`
- L51 _public member_ `EFilterFlag FilterFlags = EFilterFlag::None;` — `UPROPERTY(EditAnywhere, config, Category = "Viewmodel")` — Filter out the properties and functions that are not valid in the context of the binding.

#### enum `EMVVMDeveloperConversionFunctionFilterType`  
`enum class EMVVMDeveloperConversionFunctionFilterType : uint8`  
_L58-62_
- reflection: `UENUM()`
- L60 _public enumerator_ `BlueprintActionRegistry`
- L61 _public enumerator_ `AllowedList UMETA(DisplayName="Conversion Function Library")`

#### class `UMVVMDeveloperProjectSettings`  
`class UMVVMDeveloperProjectSettings : public UDeveloperSettings`  
_L69-225_
- reflection: `UCLASS(MinimalAPI, config=ModelViewViewModel, defaultconfig)`
- inherits: `UDeveloperSettings`
- desc: Implements the settings for the MVVM Editor
- L74 _public prototype_ `UMVVMDeveloperProjectSettings();`
- L76 _public prototype_ `virtual FName GetCategoryName() const override;`
- L77 _public prototype_ `virtual FText GetSectionText() const override;`
- L79 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L82 _public prototype_ `bool PropertyHasFiltering(const UStruct* ObjectStruct, const FProperty* Property) const;`
- L83 _public prototype_ `bool IsPropertyAllowed(const UBlueprint* Context, const UStruct* ObjectStruct, const FProperty* Property) const;`
- L84 _public prototype_ `bool IsFunctionAllowed(const UBlueprint* Context, const UClass* ObjectClass, const UFunction* Function) const;`
- L85 _public prototype_ `bool IsConversionFunctionAllowed(const UBlueprint* Context, const UFunction* Function) const;`
- L86 _public prototype_ `bool IsConversionFunctionAllowed(const UBlueprint* Context, const TSubclassOf<UK2Node> Function) const;`
- L88 _public function_ `bool IsExecutionModeAllowed(EMVVMExecutionMode ExecutionMode) const`
- L93 _public function_ `bool IsContextCreationTypeAllowed(EMVVMBlueprintViewModelContextCreationType ContextCreationType) const`
- L98 _public function_ `EMVVMDeveloperConversionFunctionFilterType GetConversionFunctionFilter() const`
- L103 _public prototype_ `TArray<const UClass*> GetAllowedConversionFunctionClasses() const;`
- L104 _public prototype_ `TArray<const UClass*> GetDeniedConversionFunctionClasses() const;`
- L106 _public prototype_ `bool IsExtensionSupportedForPanelClass(TSubclassOf<UPanelWidget> ClassToSupport) const;`
- L107 _public prototype_ `bool IsExtensionSupportedForListViewBaseClass(TSubclassOf<UListViewBase> ClassToSupport) const;`
- L110 _public function_ `FPathPermissionList& GetGeneratedFunctionPermissions()` — Get generated functions permission list.
- L115 _private member_ `TMap<FSoftClassPath, FMVVMDeveloperProjectWidgetSettings> FieldSelectorPermissions;` — `UPROPERTY(EditAnywhere, config, Category = "UX", meta=(AllowAbstract = true))` — Permission list for filtering which properties are visible in UI.
- L119 _private member_ `TSet<EMVVMExecutionMode> AllowedExecutionMode;` — `UPROPERTY(EditAnywhere, config, Category = "Defaults")` — Permission list for filtering which execution mode is allowed.
- L123 _private member_ `TSet<EMVVMBlueprintViewModelContextCreationType> AllowedContextCreationType;` — `UPROPERTY(EditAnywhere, config, Category = "Defaults")` — Permission list for filtering which context creation type is allowed.
- L128 _public member_ `bool bAllowBindingFromDetailView = true;` — `UPROPERTY(EditAnywhere, config, Category = "UX")` — Binding can be made from the DetailView Bind option.
- L132 _public member_ `bool bAllowGeneratedViewModelSetter = true;` — `UPROPERTY(EditAnywhere, config, Category = "Features", meta=(DisplayName="Allow Generated Viewmodel Setter"))` — When generating a source in the viewmodel editor, allow the compiler to generate a setter function.
- L136 _public member_ `bool bAllowLongSourcePath = true;` — `UPROPERTY(EditAnywhere, config, Category = "Features")` — When generating a binding with a long source path, allow the compiler to generate a new viewmodel source.
- L140 _public member_ `bool bShowDetailViewOptionInBindingPanel = true;` — `UPROPERTY(EditAnywhere, config, Category = "UX")` — For the binding list widget, allow the user to edit the binding in the detail view.
- L144 _public member_ `bool bShowViewSettings = true;` — `UPROPERTY(EditAnywhere, config, Category = "UX")` — For the binding list widget and the viewmodel panel, allow the user to edit the view settings in the detail view.
- L148 _public member_ `bool bShowDeveloperGenerateGraphSettings = true;` — `UPROPERTY(EditAnywhere, config, Category = "UX")` — For the binding list widget, allow the user to generate a copy of the binding/event graph.
- L156 _public member_ `bool bAllowConversionFunctionGeneratedGraphInEditor_DEPRECATED = false;` — `UPROPERTY()` — When a conversion function requires a wrapper graph, add and save the generated graph to the blueprint. It is strongly suggested to not use this feature. It can easly break deprecation and the graph will not auto update with new features.
- L160 _public member_ `bool bAllowBindingEvent = true;` — `UPROPERTY(EditAnywhere, config, Category = "Features")` — When binding to a multicast delegate property, allow to create an event.
- L163 _public member_ `bool bAllowConditionBinding = true;` — `UPROPERTY(EditAnywhere, config, Category = "Features")`
- L167 _public member_ `bool bCanCreateViewModelInView = false;` — `UPROPERTY(EditAnywhere, config, Category = "Features", meta=(DisplayName="Experimental - Can Create Viewmodel In View"))` — Allow to create an instanced viewmodel directly in the view editor.
- L174 _public member_ `bool bExposeViewModelInstanceInEditor = false;` — `UPROPERTY(EditAnywhere, config, Category = "Features")` — When a viewmodel is set to Create Instance, allow modifying the viewmodel instance in the editor on all instances of the owning widget. The per-viewmodel setting "Expose Instance In Editor" overrides this.
- L178 _public member_ `EMVVMDeveloperConversionFunctionFilterType ConversionFunctionFilter = EMVVMDeveloperConversionFunctionFilterType::BlueprintActionRegistry;` — `UPROPERTY(EditAnywhere, config, Category = "Defaults")` — Permission list for filtering which execution mode is allowed.
- L182 _public member_ `TSet<FSoftClassPath> AllowedClassForConversionFunctions;` — `UPROPERTY(EditAnywhere, config, Category = "Defaults", meta = (AllowAbstract = true, EditCondition = "ConversionFunctionFilter == EMVVMDeveloperConversionFunctionFilterType::AllowedList"))` — Classes to include in conversion function list. It includes the child class.
- L186 _public member_ `TSet<FSoftClassPath> DeniedClassForConversionFunctions;` — `UPROPERTY(EditAnywhere, config, Category = "Defaults", meta = (AllowAbstract = true, EditCondition = "ConversionFunctionFilter == EMVVMDeveloperConversionFunctionFilterType::AllowedList"))` — Classes excluded for conversion function list.
- L190 _public member_ `TSet<FName> DeniedModuleForConversionFunctions;` — `UPROPERTY(EditAnywhere, config, Category = "Defaults", meta = (EditCondition = "ConversionFunctionFilter == EMVVMDeveloperConversionFunctionFilterType::AllowedList"))` — Modules excluded for conversion function list. ie. "/Script/MyModule"
- L192 _public member_ `FSimpleMulticastDelegate OnLibrarySettingChanged;`
- L196 _public member_ `bool bForceExecuteBindingsOnSetSource = false;` — `UPROPERTY(EditAnywhere, config, Category = "Defaults")` — The default value of UMVVMBlueprintViewSettings::bForceExecuteBindingOnSetSource.
- L200 _public member_ `FMVVMViewBindingFilterSettings FilterSettings;` — `UPROPERTY(EditAnywhere, config, Category = "UX")` — Settings for filtering the list of available properties and functions on binding creation.
- L204 _public member_ `TSet<TSoftClassPtr<UPanelWidget>> SupportedPanelClassesForExtension;` — `UPROPERTY(EditAnywhere, config, Category = "Widget Extension")` — Sub-classes of panel widget that are supported to have an extension for binding their entries to viewmodels.
- L208 _public member_ `TSet<TSoftClassPtr<UListViewBase>> SupportedListViewBaseClassesForExtension;` — `UPROPERTY(EditAnywhere, config, Category = "Widget Extension")` — Sub-classes of ListViewBase that are supported to have an extension for binding their entries to viewmodels.
- L212 _public member_ `TSoftClassPtr<UMVVMViewModelContextResolver> DefaultResolverValue;` — `UPROPERTY(EditAnywhere, config, Category = "Defaults")` — Resolver class to use as the default value when selecting resolver creation mode
- L216 _public member_ `bool bAllowBindingEditingWithoutViewModel = false;` — `UPROPERTY()` — Useful in the case we want to create binders directly on widget fields, without requiring to add a viewmodel.
- L220 _public member_ `bool bAllowWidgetInConditionSource = false;` — `UPROPERTY()` — Useful in the case we want to create conditions directly on widget fields.
- L224 _private member_ `FPathPermissionList GeneratedFunctionPermissions;` — MVVM Generated function permission list

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMPropertyPath.h` (Public)


#### struct `FMVVMBlueprintFieldPath`  
`struct FMVVMBlueprintFieldPath`  
_L18-90_
- reflection: `USTRUCT()`
- desc: A single item in a Property Path
- L25 _private member_ `FMemberReference BindingReference;` — `UPROPERTY(EditAnywhere, Category = "MVVM")` — Reference to property for this binding.
- L29 _private member_ `EBindingKind BindingKind = EBindingKind::Function;` — `UPROPERTY()` — If we are referencing a UFunction or FProperty
- L32 _public prototype_ `FMVVMBlueprintFieldPath() = default;`
- L34 _public prototype_ `FMVVMBlueprintFieldPath(const UBlueprint* InContext, UE::MVVM::FMVVMConstFieldVariant InField);`
- L40 _public prototype_ `FName GetRawFieldName() const;` — Get the binding name. It won't resolve the field. That should only be used while compiling the skeletal class.
- L43 _public prototype_ `FName GetFieldName(const UClass* SelfContext) const;` — Get the binding name, resolves reference deprecation / redirectors / etc before returning
- L46 _public prototype_ `UE::MVVM::FMVVMConstFieldVariant GetField(const UClass* SelfContext) const;`
- L48 _public function_ `bool IsFieldLocalScope() const`
- L53 _public function_ `bool IsFieldSelfContext() const`
- L58 _public prototype_ `UClass* GetParentClass(const UClass* SelfContext) const;`
- L60 _public function_ `EBindingKind GetBindingKind() const`
- L67 _public prototype_ `void SetDeprecatedBindingReference(const FMemberReference& InBindingReference, EBindingKind InBindingKind);`
- L69 _public prototype_ `void SetDeprecatedSelfReference(const UBlueprint* Context);`
- L71 _public function_ `void SetMemberName(FName NewName)`
- L78 _public function_ `bool operator==(const FMVVMBlueprintFieldPath& Other) const`
- L83 _public function_ `bool operator!=(const FMVVMBlueprintFieldPath& Other) const`
- L89 _private prototype_ `UE::MVVM::FMVVMConstFieldVariant GetFieldInternal(const UClass* SelfContext) const;`

#### enum `EMVVMBlueprintFieldPathSource`  
`enum class EMVVMBlueprintFieldPathSource : uint8`  
_L96-102_
- reflection: `UENUM()`
- L98 _public enumerator_ `None`
- L99 _public enumerator_ `Widget`
- L100 _public enumerator_ `ViewModel`
- L101 _public enumerator_ `SelfContext`

#### struct `FMVVMBlueprintPropertyPath`  
`struct FMVVMBlueprintPropertyPath`  
_L110-325_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base path to properties for MVVM view models and widgets. Used to associate properties within MVVM bindings in editor & during MVVM compilation
- L117 _private member_ `TArray<FMVVMBlueprintFieldPath> Paths;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")` — Reference to property for this binding.
- L120 _private member_ `FName WidgetName;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")`
- L123 _private member_ `FGuid ContextId;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")`
- L126 _private member_ `EMVVMBlueprintFieldPathSource Source = EMVVMBlueprintFieldPathSource::None;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")`
- L130 _private member_ `bool bIsComponent = false;` — `UPROPERTY(VisibleAnywhere, Category = "MVVM")` — True if this property path is for a UI component. This affects how some fields in the path are filtered out.
- L135 _private member_ `FMemberReference BindingReference_DEPRECATED;` — `UPROPERTY()` — Use the Paths. BindingReference and BindingKind are deprecated.
- L137 _private member_ `EBindingKind BindingKind_DEPRECATED = EBindingKind::Function;` — `UPROPERTY()`
- L140 _private member_ `bool bDeprecatedSource = false;` — `UPROPERTY()` — Is the deprecation source done.
- L144 _public function_ `bool HasPaths() const`
- L149 _public function_ `const TArrayView<const FMVVMBlueprintFieldPath> GetFieldPaths() const`
- L158 _public prototype_ `TArray<FName> GetFieldNames(const UClass* SelfContext) const;` — Get the binding names. Resolves reference deprecation / redirectors. Returns Field.SubProperty.SubProperty from ViewModel.Field.SubProperty.SubProperty
- L164 _public prototype_ `TArray<UE::MVVM::FMVVMConstFieldVariant> GetFields(const UClass* SelfContext) const;` — Get the binding fields. Resolves reference deprecation / redirectors. Returns Field.SubProperty.SubProperty from ViewModel.Field.SubProperty.SubProperty
- L170 _public prototype_ `TArray<UE::MVVM::FMVVMConstFieldVariant> GetCompleteFields(const UBlueprint* SelfContext, bool bIsForDisplay = false) const;` — Get the binding fields. Resolves reference deprecation / redirectors. Returns Viewmodel.Field.SubProperty.SubProperty from ViewModel.Field.SubProperty.SubProperty
- L176 _public prototype_ `FString GetPropertyPath(const UClass* SelfContext) const;` — Get the full path without the first property name. Returns Field.SubProperty.SubProperty from ViewModel.Field.SubProeprty.SubProperty
- L178 _public prototype_ `bool HasFieldInLocalScope() const;`
- L180 _public function_ `bool PropertyPathContains(const UClass* InSelfContext, UE::MVVM::FMVVMConstFieldVariant Field) const`
- L185 _public function_ `void SetPropertyPath(const UBlueprint* InContext, UE::MVVM::FMVVMConstFieldVariant InField)`
- L191 _public function_ `void AppendPropertyPath(const UBlueprint* InContext, UE::MVVM::FMVVMConstFieldVariant InField)`
- L199 _public function_ `void ResetPropertyPath()`
- L204 _public function_ `void ResetSource()`
- L212 _public function_ `EMVVMBlueprintFieldPathSource GetSource(const UBlueprint* InContext) const`
- L222 _public function_ `bool IsFromWidget() const` — `UE_DEPRECATED(5.4, "Use GetSource instead.")`
- L228 _public function_ `bool IsFromViewModel() const` — `UE_DEPRECATED(5.4, "Use GetSource instead.")`
- L233 _public function_ `FGuid GetViewModelId() const`
- L238 _public function_ `void SetViewModelId(FGuid InViewModelId)`
- L245 _public function_ `FName GetWidgetName() const`
- L250 _public function_ `void SetWidgetName(FName InWidgetName)`
- L257 _public function_ `void SetSelfContext()`
- L263 _public function_ `void SetIsComponent(bool InIsComponent)`
- L268 _public function_ `bool IsComponent() const`
- L277 _public prototype_ `bool OnFieldRenamed(const UBlueprint* InContext, UClass* FieldClass, FName OldObjectName, FName NewObjectName);` — Handle when a field that is part of the path is renamed Returns true if the renamed field was part of the path
- L279 _public function_ `bool IsValid() const`
- L287 _public function_ `bool IsEmpty() const` — `UE_DEPRECATED(5.4, "Use IsValid instead.")`
- L292 _public function_ `bool operator==(const FMVVMBlueprintPropertyPath& Other) const`
- L301 _public function_ `bool operator!=(const FMVVMBlueprintPropertyPath& Other) const`
- L306 _public function_ `void PostSerialize(const FArchive& Ar)`
- L319 _public prototype_ `FText ToText(const UWidgetBlueprint* Blueprint, bool bUseDisplayName) const;`
- L320 _public prototype_ `FString ToString(const UWidgetBlueprint* Blueprint, bool bUseDisplayName, bool bIncludeMetaData) const;`
- L323 _private prototype_ `void DeprecationUpdateSource(const UBlueprint* InContext);`
- L324 _private prototype_ `TArray<UE::MVVM::FMVVMConstFieldVariant> GetComponentFields(const UClass* InSelfContext) const;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMVVMBlueprintPropertyPath> : public TStructOpsTypeTraitsBase2<FMVVMBlueprintPropertyPath>`  
_L328-334_
- inherits: `TStructOpsTypeTraitsBase2<FMVVMBlueprintPropertyPath>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L331-333_

#### Free symbols / members of external scopes

- L182 _function_ `return Paths.ContainsByPredicate([InSelfContext, Field](const FMVVMBlueprintFieldPath& FieldPath) { return FieldPath.GetField(InSelfContext) == Field; });` (scope `FMVVMBlueprintPropertyPath::PropertyPathContains`)
- L332 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon64c6cd190203`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMWidgetBlueprintDiff.h` (Public)


#### struct `UE::MVVM::FMVVMDiffCustomObjectProvider`  
`struct FMVVMDiffCustomObjectProvider : TSharedFromThis<FMVVMDiffCustomObjectProvider>`  
_L17-25_
- inherits: `TSharedFromThis<FMVVMDiffCustomObjectProvider>`
- L19 _public prototype_ `virtual ~FMVVMDiffCustomObjectProvider() = default;`
- L20 _public function_ `virtual TSharedPtr<IDiffCustomObject> CreateObjectDiff(const UWidgetBlueprint* NewBlueprint, const UWidgetBlueprint* OldBlueprint)`
- L21 _public function_ `virtual TSharedPtr<IDiffCustomProperty> CreatePropertyBindingDiff(FGuid NewBinding, FGuid OldBinding)`
- L22 _public function_ `virtual TSharedPtr<IDiffCustomProperty> CreatePropertyConditionDiff(const UMVVMBlueprintViewCondition* NewCondition, const UMVVMBlueprintViewCondition* OldCondition)`
- L23 _public function_ `virtual TSharedPtr<IDiffCustomProperty> CreatePropertyEventDiff(const UMVVMBlueprintViewEvent* NewEvent, const UMVVMBlueprintViewEvent* OldEvent)`
- L24 _public function_ `virtual TSharedPtr<IDiffCustomProperty> CreatePropertyParameterDiff(const FMVVMBlueprintPinId& NewParameter, const FMVVMBlueprintPinId& OldParameter)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MVVM` (scope `UE`)
- L27 _namespace_ `namespace FMVVMWidgetBlueprintDiff` (scope `UE::MVVM`)
- L29 _prototype_ `void FindDiffs(const UWidgetBlueprint* NewBlueprint, const UWidgetBlueprint* OldBlueprint, FDiffResults& Results);` (scope `UE::MVVM::FMVVMWidgetBlueprintDiff`)
- L30 _prototype_ `void RegisterCustomDiff(TSharedPtr<FMVVMDiffCustomObjectProvider> DiffCustomObject);` (scope `UE::MVVM::FMVVMWidgetBlueprintDiff`)
- L31 _prototype_ `void UnregisterCustomDiff();` (scope `UE::MVVM::FMVVMWidgetBlueprintDiff`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMWidgetBlueprintExtension_View.h` (Public)


#### struct `FMVVMExtensionItem`  
`struct FMVVMExtensionItem`  
_L28-47_
- reflection: `USTRUCT()`
- L33 _public member_ `FName WidgetName = NAME_None;` — `UPROPERTY()`
- L36 _public member_ `FGuid ViewmodelId = FGuid();` — `UPROPERTY()`
- L39 _public member_ `TObjectPtr<UMVVMBlueprintViewExtension> ExtensionObj;` — `UPROPERTY()`
- L41 _public function_ `bool operator==(const FMVVMExtensionItem& OtherExt) const`

#### class `UMVVMWidgetBlueprintExtension_View`  
`class UMVVMWidgetBlueprintExtension_View : public UWidgetBlueprintExtension`  
_L53-141_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidgetBlueprintExtension`
- L58 _public prototype_ `void CreateBlueprintViewInstance();`
- L59 _public prototype_ `void DestroyBlueprintViewInstance();`
- L61 _public function_ `UMVVMBlueprintView* GetBlueprintView()`
- L66 _public function_ `const UMVVMBlueprintView* GetBlueprintView() const`
- L71 _public function_ `FSimpleMulticastDelegate& OnBlueprintViewChangedDelegate()`
- L76 _public function_ `const TArrayView<const FName> GetGeneratedFunctions() const`
- L83 _public prototype_ `virtual void PostLoad() override;`
- L85 _public prototype_ `virtual void PostInitProperties() override;`
- L90 _public prototype_ `virtual void HandlePreloadObjectsForCompilation(UBlueprint* OwningBlueprint) override;`
- L91 _public prototype_ `virtual void HandleBeginCompilation(FWidgetBlueprintCompilerContext& InCreationContext) override;`
- L92 _public prototype_ `virtual void HandleCleanAndSanitizeClass(UWidgetBlueprintGeneratedClass* ClassToClean, UObject* OldCDO) override;`
- L93 _public prototype_ `virtual void HandlePopulateGeneratedVariables(const FWidgetBlueprintCompilerContext::FPopulateGeneratedVariablesContext& Context) override;`
- L94 _public prototype_ `virtual void HandleCreateClassVariablesFromBlueprint(const FWidgetBlueprintCompilerContext::FCreateVariableContext& Context) override;`
- L95 _public prototype_ `virtual void HandleCreateFunctionList(const FWidgetBlueprintCompilerContext::FCreateFunctionContext& Context) override;`
- L96 _public prototype_ `virtual void HandleFinishCompilingClass(UWidgetBlueprintGeneratedClass* Class) override;`
- L97 _public prototype_ `virtual void HandleEndCompilation() override;`
- L98 _public prototype_ `virtual FSearchData HandleGatherSearchData(const UBlueprint* OwningBlueprint) const override;`
- L101 _public prototype_ `virtual void FindDiffs(const UWidgetBlueprint* OwningBlueprint, const UWidgetBlueprint* OtherBlueprint, FDiffResults& Results) const override;`
- L102 _public prototype_ `virtual void GatherWidgetMemberReferences(FName WidgetVariableName, const UClass* WidgetClass, TSet<FName>& OutReferencedProperties, TSet<FName>& OutReferencedFunctions) const override;`
- L106 _public prototype_ `void VerifyWidgetExtensions();`
- L107 _public prototype_ `void OnFieldRenamed(UClass* FieldOwnerClass, FName OldName, FName NewName);`
- L108 _public prototype_ `void RenameWidgetExtensions(FName OldWidgetName, FName NewWidgetName);`
- L109 _public prototype_ `UMVVMBlueprintViewExtension* CreateBlueprintWidgetExtension(TSubclassOf<UMVVMBlueprintViewExtension> ExtensionClass, FName WidgetName);`
- L110 _public prototype_ `void RemoveBlueprintWidgetExtension(UMVVMBlueprintViewExtension* ExtensionToRemove, FName WidgetName);`
- L111 _public prototype_ `TArray<UMVVMBlueprintViewExtension*> GetBlueprintExtensionsForWidget(FName WidgetName) const;`
- L112 _public prototype_ `TArray<UMVVMBlueprintViewExtension*> GetAllBlueprintExtensions() const;`
- L114 _public prototype_ `void SetFilterSettings(FMVVMViewBindingFilterSettings InFilterSettings);`
- L115 _public function_ `FMVVMViewBindingFilterSettings GetFilterSettings() const`
- L121 _public member_ `TMap<FGuid, TWeakObjectPtr<UObject>> TemporaryViewModelInstances;` — `UPROPERTY(Transient)`
- L125 _private member_ `TObjectPtr<UMVVMBlueprintView> BlueprintView;` — `UPROPERTY(Instanced)`
- L128 _private member_ `FMVVMViewBindingFilterSettings FilterSettings;` — `UPROPERTY(Transient)`
- L131 _private member_ `TArray<FName> GeneratedFunctions;` — `UPROPERTY(Transient)`
- L133 _private member_ `FSimpleMulticastDelegate BlueprintViewChangedDelegate;`
- L134 _private member_ `TPimplPtr<UE::MVVM::Private::FMVVMViewBlueprintCompiler> CurrentCompilerContext;`
- L137 _private member_ `TArray<FMVVMExtensionItem> BlueprintExtensions;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELVIEWVIEWMODELBLUEPRINT_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MVVM` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MVVM` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/ViewModel/MVVMViewModelBlueprint.h` (Public)


#### class `UMVVMViewModelBlueprint`  
`class UMVVMViewModelBlueprint : public UBlueprint`  
_L20-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprint`
- desc: Will be deprecated in the next version.
