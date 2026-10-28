# Plugins / UAFAnimGraphUncookedOnly

- module root: `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly`
- headers: 25; symbols: 282
- symbol kinds: class=22, function=39, macro=16, member=33, namespace=37, prototype=128, struct=7
- PrivateDependencyModuleNames: AnimGraph, AssetDefinition, BlueprintGraph, Core, CoreUObject, Engine, Projects, RigVM, RigVMDeveloper, RigVMEditor, Slate, UAF, UAFAnimGraph, UAFEditor, UAFUncookedOnly, UnrealEd, WorkspaceEditor
- PublicDependencyModuleNames: SlateCore

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/AnimGraphUncookedOnlyUtils.h` (Internal)


#### struct `UE::UAF::UncookedOnly::FAnimGraphUtils`  
`struct FAnimGraphUtils`  
_L24-33_
- L27 _public prototype_ `static void SetupAnimGraph(const FName EntryName, URigVMController* InController, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — Set up a simple animation graph
- L30 _public prototype_ `static bool IsTraitStackNode(const URigVMNode* InModelNode);` — Check whether the supplied node is a trait stack
- L32 _public prototype_ `static bool RequestVMAutoRecompile(UUAFRigVMAssetEditorData* EditorData);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFANIMGRAPHUNCOOKEDONLY_API`
- L18 _macro_ `#define GET_PIN_PATH_STRING_CHECKED(StructName, MemberName) \` — Gets a 'pin path' (e.g. MyTrait.MyMember from GET_PIN_PATH_STRING_CHECKED(FMyTrait, MyMember)) while statically verifying that the struct amen member exist
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace UAF` (scope `UE`)
- L21 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/AnimNextAnimGraphWorkspaceAssetUserData.h` (Internal)


#### struct `FAnimNextAnimationGraphOutlinerData`  
`struct FAnimNextAnimationGraphOutlinerData : public FAnimNextRigVMAssetOutlinerData`  
_L14-24_
- reflection: `USTRUCT()`
- inherits: `FAnimNextRigVMAssetOutlinerData`
- L18 _public prototype_ `FAnimNextAnimationGraphOutlinerData() = default;`
- L20 _public function_ `UUAFAnimGraph* GetAnimationGraph() const`

#### class `UAnimNextAnimGraphWorkspaceAssetUserData`  
`class UAnimNextAnimGraphWorkspaceAssetUserData : public UAssetUserData`  
_L27-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetUserData`
- L33 _public function_ `virtual bool IsEditorOnly() const override`
- L37 _protected prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L40 _protected prototype_ `virtual void GetRootAssetExport(FAssetRegistryTagsContext Context) const;` — Get root asset workspace exports.
- L43 _protected prototype_ `virtual void GetWorkspaceAssetExports(FAssetRegistryTagsContext Context) const;` — Get all workspace asset exports except for the root asset.
- L47 _protected member_ `mutable FWorkspaceOutlinerItemExports CachedExports;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPHUNCOOKEDONLY_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/AnimNextController.h` (Internal)


#### class `UAnimNextController`  
`class UAnimNextController : public UAnimNextControllerBase`  
_L20-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimNextControllerBase`
- desc: Implements AnimNext RigVM controller extensions
- L29 _public prototype_ `FName AddTraitStruct(URigVMUnitNode* InNode, const TInstancedStruct<FAnimNextTraitSharedData>& InTraitDefaults, int32 InTraitIndex, bool bSetupUndoRedo, bool bPrintPythonCommand);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Controller")` — Adds a new Trait to the Stack, with default struct values Returns Trait Instance Name (or NAME_None on failure)
- L34 _public prototype_ `FName AddTraitByName(FName InNodeName, FName InNewTraitTypeName, int32 InPinIndex, const FString& InNewTraitDefaultValue = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Controller")` — Adds a new Trait to the Stack, with default struct values Returns Trait Instance Name (or NAME_None on failure)
- L39 _public prototype_ `bool RemoveTraitByName(FName InNodeName, FName InTraitInstanceName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Controller")` — Removes a Trait from the Stack, using Trait Instance Name Returns operation success (true) or failure (false)
- L44 _public prototype_ `FName SwapTraitByName(FName InNodeName, FName InTraitInstanceName, int32 InCurrentTraitPinIndex, FName InNewTraitTypeName, const FString& InNewTraitDefaultValue = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Controller")` — Swap a Trait from the Stack with a new one, using existing Trait Instance Name and new Trait Type Name Returns Trait Instance Name (or NAME_None on failure)
- L49 _public prototype_ `bool SetTraitPinIndex(FName InNodeName, FName InTraitInstanceName, int32 InNewPinIndex, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Controller")` — Move a Trait from its current PinIndex to the specified one (moving it visually in the stack) Returns operation success (true) or failure (false)
- L52 _public prototype_ `bool UpgradeTraitByName(FName InNodeName, FName InTraitInstanceName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — Upgrade a trait if it needs to be
- L55 _public prototype_ `URigVMUnitNode* AddUnitNodeWithPins(UScriptStruct* InScriptStruct, const FRigVMPinInfoArray& PinArray, const FName& InMethodName = TEXT("Execute"), const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand =` — Adds a unit node with a dynamic number of pins

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/AnimNextTraitStackUnitNode.h` (Internal)


#### class `UAnimNextTraitStackUnitNode`  
`class UAnimNextTraitStackUnitNode : public URigVMUnitNode`  
_L25-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigVMUnitNode`
- desc: Implements AnimNext RigVM unit node extensions for Trait Stacks
- L31 _public prototype_ `virtual FString GetNodeSubTitle() const override;` — Override node functions
- L32 _public prototype_ `virtual FText GetToolTipText() const override;`
- L35 _public prototype_ `FString GetDefaultNodeTitle() const;` — Wrap the template for defaults
- L36 _public prototype_ `FLinearColor GetDefaultNodeColor() const;`
- L37 _public prototype_ `const FSlateBrush* GetDefaultNodeIconBrush() const;`
- L44 _private prototype_ `void HandlePinDefaultValueChanged(UAnimNextController* InController, URigVMPin* InPin);`
- L45 _private prototype_ `void HandleAssetRenamed(UAnimNextController* InController, const FAssetData& InAssetData, const FString& InOldName);`
- L49 _private member_ `TSubclassOf<UUAFGraphNodeTemplate> Template;` — `UPROPERTY(VisibleAnywhere, Category = "Template")` — The template that defines our behavior

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPHUNCOOKEDONLY_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)
- L16 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/Entries/AnimNextAnimationGraphEntry.h` (Internal)


#### class `UAnimNextAnimationGraphEntry`  
`class UAnimNextAnimationGraphEntry : public UUAFRigVMAssetEntry, public IUAFRigVMGraphInterface, public IUAFRigVMExportInterface`  
_L31-74_
- reflection: `UCLASS(MinimalAPI, Category = "Animation Graphs", DisplayName = "Animation Graph")`
- inherits: `UUAFRigVMAssetEntry,IUAFRigVMGraphInterface,IUAFRigVMExportInterface`
- desc: An Animation Graph entry in an AnimNext module asset
- L42 _private prototype_ `virtual FAnimNextParamType GetExportType() const override;` — IAnimNextRigVMExportInterface interface
- L43 _private prototype_ `virtual FName GetExportName() const override;`
- L44 _private prototype_ `virtual EAnimNextExportAccessSpecifier GetExportAccessSpecifier() const override;`
- L45 _private prototype_ `virtual void SetExportAccessSpecifier(EAnimNextExportAccessSpecifier InAccessSpecifier, bool bSetupUndoRedo = true) override;`
- L48 _private prototype_ `virtual FName GetEntryName() const override;` — UUAFRigVMAssetEntry interface
- L49 _private prototype_ `virtual void SetEntryName(FName InName, bool bSetupUndoRedo = true) override;`
- L52 _private prototype_ `virtual const FName& GetGraphName() const override;` — IAnimNextRigVMGraphInterface interface
- L53 _private prototype_ `virtual URigVMGraph* GetRigVMGraph() const override;`
- L54 _private prototype_ `virtual URigVMEdGraph* GetEdGraph() const override;`
- L55 _private prototype_ `virtual void SetRigVMGraph(URigVMGraph* InGraph) override;`
- L56 _private prototype_ `virtual void SetEdGraph(URigVMEdGraph* InGraph) override;`
- L61 _protected member_ `EAnimNextExportAccessSpecifier Access = EAnimNextExportAccessSpecifier::Private;` — `UPROPERTY(EditAnywhere, Category = AnimationGraph)` — Access specifier - whether the graph's entry point is visible external to this asset
- L65 _protected member_ `FName GraphName;` — `UPROPERTY(VisibleAnywhere, Category = AnimationGraph)` — The name of the graph
- L69 _protected member_ `TObjectPtr<URigVMGraph> Graph;` — `UPROPERTY()` — RigVM graph
- L73 _protected member_ `TObjectPtr<UAnimNextEdGraph> EdGraph;` — `UPROPERTY()` — Editor graph

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)
- L16 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UAF` (scope `UE`)
- L22 _namespace_ `namespace Tests` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/Graph/AnimGraph/AnimGraphNode_AnimNextGraph.h` (Internal)


#### class `UAnimGraphNode_AnimNextGraph`  
`class UAnimGraphNode_AnimNextGraph : public UAnimGraphNode_CustomProperty`  
_L13-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_CustomProperty`
- L18 _private member_ `FAnimNode_AnimNextGraph Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L20 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L21 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L22 _private prototype_ `virtual void PostReconstructNode() override;`
- L23 _private prototype_ `virtual void GetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const override;`
- L27 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L28 _private prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L29 _private prototype_ `virtual FText GetTooltipText() const override;`
- L30 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L31 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L34 _private function_ `virtual FAnimNode_CustomProperty* GetCustomPropertyNode() override`
- L35 _private function_ `virtual const FAnimNode_CustomProperty* GetCustomPropertyNode() const override`
- L38 _private prototype_ `void GetVariables(bool bInput, TMap<FName, FRigVMExternalVariable>& OutParameters) const;` — property related things
- L40 _private member_ `TMap<FName, FRigVMExternalVariable> InputVariables;`
- L41 _private member_ `TMap<FName, FRigVMExternalVariable> OutputVariables;`
- L43 _private prototype_ `void RebuildExposedProperties();`
- L44 _private prototype_ `virtual void CreateCustomPins(TArray<UEdGraphPin*>* OldPins) override;`
- L45 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L48 _private prototype_ `bool IsPropertyExposeEnabled(FName PropertyName) const;` — pin option related
- L49 _private prototype_ `ECheckBoxState IsPropertyExposed(FName PropertyName) const;`
- L50 _private prototype_ `void OnPropertyExposeCheckboxChanged(ECheckBoxState NewState, FName PropertyName);`
- L52 _private prototype_ `bool IsInputProperty(const FName& PropertyName) const;`
- L54 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/Graph/AnimGraphEditorSchemaActions.h` (Internal)


#### struct `FAnimNextSchemaAction_AddTemplateNode`  
`struct FAnimNextSchemaAction_AddTemplateNode : public FAnimNextSchemaAction`  
_L16-31_
- reflection: `USTRUCT()`
- inherits: `FAnimNextSchemaAction`
- L20 _public prototype_ `FAnimNextSchemaAction_AddTemplateNode() = default;`
- L22 _public prototype_ `FAnimNextSchemaAction_AddTemplateNode(const UE::UAF::FGraphNodeTemplateInfo& InNodeTemplateInfo, const FText& InKeywords = FText::GetEmpty());`
- L25 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction Interface
- L26 _public function_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override`
- L27 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L29 _public member_ `UE::UAF::FGraphNodeTemplateInfo NodeTemplateInfo;`
- L30 _public member_ `mutable FSlateBrush CachedIcon;`

#### struct `FAnimNextSchemaAction_NotifyEvent`  
`struct FAnimNextSchemaAction_NotifyEvent : public FAnimNextSchemaAction`  
_L34-43_
- reflection: `USTRUCT()`
- inherits: `FAnimNextSchemaAction`
- L38 _public prototype_ `FAnimNextSchemaAction_NotifyEvent();`
- L41 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction Interface
- L42 _public function_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UAFANIMGRAPHUNCOOKEDONLY_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/Graph/AnimNextAnimationGraphSchema.h` (Internal)


#### class `UAnimNextAnimationGraphSchema`  
`class UAnimNextAnimationGraphSchema : public UUAFRigVMAssetSchema`  
_L10-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUAFRigVMAssetSchema`
- L16 _public prototype_ `virtual bool CanSetNodeTitle(URigVMController* InController, const URigVMNode* InNode) const override;` — URigVMSchema interface
- L17 _public prototype_ `virtual bool CanRecolorNode(URigVMController* InController, const URigVMNode* InNode, const FLinearColor& InNewColor) const override;`
- L18 _public prototype_ `virtual bool CanUnfoldPin(URigVMController* InController, const URigVMPin* InPinToUnfold) const override;`
- L19 _public prototype_ `virtual bool ShouldUnfoldStruct(URigVMController* InController, const UStruct* InStruct) const override;`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/Graph/AnimNextAnimationGraph_EditorData.h` (Internal)


#### class `UAnimNextAnimationGraphLibrary`  
`class UAnimNextAnimationGraphLibrary : public UBlueprintFunctionLibrary`  
_L33-41_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Script-callable editor API hoisted onto UUAFAnimGraph
- L40 _public prototype_ `static UAnimNextAnimationGraphEntry* AddAnimationGraph(UUAFAnimGraph* InAsset, FName InName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "AnimNext|Entries", meta=(ScriptMethod))` — Adds an animation graph to an AnimNext asset

#### class `UUAFAnimGraph_EditorData`  
`class UUAFAnimGraph_EditorData : public UUAFSharedVariables_EditorData`  
_L45-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUAFSharedVariables_EditorData`
- desc: Editor data for UAF animation graphs
- L69 _public prototype_ `UUAFAnimGraph_EditorData();`
- L72 _public prototype_ `UAnimNextAnimationGraphEntry* AddAnimationGraph(FName InName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Adds an animation graph to this asset
- L76 _protected function_ `virtual TSubclassOf<URigVMController> GetControllerClass() const override` — UUAFRigVMAssetEditorData interface
- L77 _protected function_ `virtual UScriptStruct* GetExecuteContextStruct() const override`
- L78 _protected prototype_ `virtual TConstArrayView<TSubclassOf<UUAFRigVMAssetEntry>> GetEntryClasses() const override;`
- L79 _protected prototype_ `virtual bool CanAddNewEntry(TSubclassOf<UUAFRigVMAssetEntry> InClass) const override;`
- L80 _protected prototype_ `virtual TSubclassOf<UAssetUserData> GetAssetUserDataClass() const override;`
- L81 _protected prototype_ `virtual void InitializeAssetUserData() override;`
- L82 _protected prototype_ `virtual void OnCompileJobStarted() override;`
- L83 _protected prototype_ `virtual void OnPreCompileAsset(FRigVMCompileSettings& InSettings) override;`
- L84 _protected prototype_ `virtual void BuildFunctionHeadersContext(const FRigVMCompileSettings& InSettings, FAnimNextGetFunctionHeaderCompileContext& OutCompileContext) const override;`
- L85 _protected prototype_ `virtual void OnPreCompileProcessGraphs(const FRigVMCompileSettings& InSettings, FAnimNextProcessGraphCompileContext& OutCompileContext) override;`
- L86 _protected prototype_ `virtual void OnCompileJobFinished() override;`
- L87 _protected prototype_ `virtual UClass* GetRigVMEdGraphSchemaClass() const override;`
- L88 _protected prototype_ `virtual void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject) override;`
- L91 _private prototype_ `void HandleAssetRenamed(const FAssetData& InAssetData, const FString& InOldName);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMGRAPHUNCOOKEDONLY_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace UAF` (scope `UE`)
- L24 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/Injection/K2Node_AnimNextInjection.h` (Internal)


#### class `UK2Node_AnimNextInjection`  
`class UK2Node_AnimNextInjection : public UK2Node_BaseAsyncTask`  
_L10-24_
- reflection: `UCLASS()`
- inherits: `UK2Node_BaseAsyncTask`
- L14 _private prototype_ `UK2Node_AnimNextInjection();`
- L17 _private prototype_ `virtual FText GetTooltipText() const override;`
- L18 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L22 _private prototype_ `virtual FText GetMenuCategory() const override;`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/PlayAnim/K2Node_AnimNextPlayAnim.h` (Internal)


#### class `UK2Node_AnimNextPlayAnim`  
`class UK2Node_AnimNextPlayAnim : public UK2Node_BaseAsyncTask`  
_L12-26_
- reflection: `UCLASS()`
- inherits: `UK2Node_BaseAsyncTask`
- L16 _private prototype_ `UK2Node_AnimNextPlayAnim();`
- L19 _private prototype_ `virtual FText GetTooltipText() const override;`
- L20 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L24 _private prototype_ `virtual FText GetMenuCategory() const override;`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/PlayAnim/K2Node_AnimNextPlayAsset.h` (Internal)


#### class `UDEPRECATED_K2Node_AnimNextPlayAsset`  
`class UDEPRECATED_K2Node_AnimNextPlayAsset : public UK2Node_BaseAsyncTask`  
_L12-24_
- reflection: `UCLASS(deprecated)`
- inherits: `UK2Node_BaseAsyncTask`
- L16 _private prototype_ `UDEPRECATED_K2Node_AnimNextPlayAsset();`
- L19 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode Interface
- L20 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L23 _private prototype_ `virtual FText GetMenuCategory() const override;` — UK2Node Interface

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Internal/Templates/GraphNodeTemplateRegistry.h` (Internal)


#### struct `UE::UAF::FGraphNodeTemplateInfo`  
`struct FGraphNodeTemplateInfo`  
_L20-28_
- L22 _public member_ `FTopLevelAssetPath ClassPath;`
- L23 _public member_ `FText MenuDescription;`
- L24 _public member_ `FText Tooltip;`
- L25 _public member_ `FText Category;`
- L26 _public member_ `TArray<FTopLevelAssetPath> DragDropAssetTypes;`
- L27 _public member_ `TArray<FAnimNextParamType> DragDropVariableTypes;`

#### class `UE::UAF::FGraphNodeTemplateRegistry`  
`class FGraphNodeTemplateRegistry`  
_L30-50_
- L34 _public prototype_ `static const TMap<FTopLevelAssetPath, FGraphNodeTemplateInfo>& GetAllTemplates();` — Get all templates map (class -> template info)
- L37 _public prototype_ `static TConstArrayView<FGraphNodeTemplateInfo> GetDragDropHandlersForAsset(const FAssetData& InAssetData);` — Get all drag drop handlers registered to an asset type
- L40 _public prototype_ `static TConstArrayView<FGraphNodeTemplateInfo> GetDragDropHandlersForVariable(const FAnimNextParamType& InVariableType);` — Get all drag drop handlers registered to a variable type
- L46 _private prototype_ `static void LazyInitialize();` — Initialize the registry (called internally when needed)
- L49 _private prototype_ `static void Shutdown();` — Release any resources

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFANIMGRAPHUNCOOKEDONLY_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace AnimGraph` (scope `UE::UAF`)
- L12 _namespace_ `namespace UncookedOnly` (scope `UE::UAF::AnimGraph`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Private/Graph/RigVMTrait_AnimNextPublicVariablesUncookedOnly.h` (Private)


#### struct `UE::UAF::UncookedOnly::FPublicVariablesImpl`  
`struct FPublicVariablesImpl`  
_L17-23_
- desc: UncookedOnly-side impl for FRigVMTrait_AnimNextPublicVariables
- L19 _public prototype_ `static void Register();`
- L20 _public prototype_ `static FString GetDisplayName(const FRigVMTrait_AnimNextPublicVariables& InTrait);`
- L21 _public prototype_ `static void GetProgrammaticPins(const FRigVMTrait_AnimNextPublicVariables& InTrait, URigVMController* InController, int32 InParentPinIndex, const FString& InDefaultValue, FRigVMPinInfoArray& OutPinArray);`
- L22 _public prototype_ `static bool ShouldCreatePinForProperty(const FRigVMTrait_AnimNextPublicVariables& InTrait, const FProperty* InProperty);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAFANIMGRAPHUNCOOKEDONLY_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Private/Graph/UAFAnimGraphEdGraphSchema.h` (Private)


#### class `UUAFAnimGraphEdGraphSchema`  
`class UUAFAnimGraphEdGraphSchema : public UAnimNextEdGraphSchema`  
_L10-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimNextEdGraphSchema`
- L15 _private prototype_ `virtual void DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;` — UEdGraphSchema interface
- L16 _private prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L17 _private prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Private/Injection/K2Node_InjectionCallbackProxySetVariable.h` (Private)


#### class `UK2Node_InjectionCallbackProxySetVariable`  
`class UK2Node_InjectionCallbackProxySetVariable : public UK2Node_AnimNextComponentSetVariable`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UK2Node_AnimNextComponentSetVariable`
- desc: A custom node that supports SetVariable functionality
- L16 _public function_ `UK2Node_InjectionCallbackProxySetVariable()`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Private/Templates/UAFGraphNodeTemplate_BlendByBool.h` (Private)


#### class `UUAFGraphNodeTemplate_BlendByBool`  
`class UUAFGraphNodeTemplate_BlendByBool : public UUAFGraphNodeTemplate`  
_L16-44_
- reflection: `UCLASS()`
- inherits: `UUAFGraphNodeTemplate`
- L20 _private function_ `UUAFGraphNodeTemplate_BlendByBool()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "UAFGraphNodeTemplate_BlendByBool"`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Private/Templates/UAFGraphNodeTemplate_BlendSpacePlayer.h` (Private)


#### class `UUAFGraphNodeTemplate_BlendSpacePlayer`  
`class UUAFGraphNodeTemplate_BlendSpacePlayer : public UUAFGraphNodeTemplate`  
_L16-111_
- reflection: `UCLASS()`
- inherits: `UUAFGraphNodeTemplate`
- L20 _private function_ `UUAFGraphNodeTemplate_BlendSpacePlayer()`
- L44 _private function_ `virtual void HandleAssetDropped_Implementation(UAnimNextController* Controller, URigVMUnitNode* Node, UObject* Asset) const`
- L69 _private function_ `virtual void HandlePinDefaultValueChanged_Implementation(UAnimNextController* Controller, URigVMPin* Pin) const`
- L91 _private function_ `virtual void HandleAssetRenamed_Implementation(UAnimNextController* Controller, URigVMNode* Node, const FAssetData& AssetData, const FString& OldName) const`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "UAFGraphNodeTemplate_SequencePlayer"`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Private/Templates/UAFGraphNodeTemplate_InjectionSite.h` (Private)


#### class `UUAFGraphNodeTemplate_InjectionSite`  
`class UUAFGraphNodeTemplate_InjectionSite : public UUAFGraphNodeTemplate`  
_L16-42_
- reflection: `UCLASS()`
- inherits: `UUAFGraphNodeTemplate`
- L20 _private function_ `UUAFGraphNodeTemplate_InjectionSite()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "UAFGraphNodeTemplate_InjectionSite"`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Private/Templates/UAFGraphNodeTemplate_InlineSubGraph.h` (Private)


#### class `UUAFGraphNodeTemplate_InlineSubGraph`  
`class UUAFGraphNodeTemplate_InlineSubGraph : public UUAFGraphNodeTemplate`  
_L17-109_
- reflection: `UCLASS()`
- inherits: `UUAFGraphNodeTemplate`
- L21 _private function_ `UUAFGraphNodeTemplate_InlineSubGraph()`
- L44 _private function_ `virtual void HandleAssetDropped_Implementation(UAnimNextController* Controller, URigVMUnitNode* Node, UObject* Asset) const`
- L67 _private function_ `virtual void HandlePinDefaultValueChanged_Implementation(UAnimNextController* Controller, URigVMPin* Pin) const`
- L89 _private function_ `virtual void HandleAssetRenamed_Implementation(UAnimNextController* Controller, URigVMNode* Node, const FAssetData& AssetData, const FString& OldName) const`

#### Free symbols / members of external scopes

- L14 _macro_ `#define LOCTEXT_NAMESPACE "UAFGraphNodeTemplate_InlineSubGraph"`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Private/Templates/UAFGraphNodeTemplate_InputPose.h` (Private)


#### class `UUAFGraphNodeTemplate_InputValue`  
`class UUAFGraphNodeTemplate_InputValue : public UUAFGraphNodeTemplate`  
_L16-79_
- reflection: `UCLASS()`
- inherits: `UUAFGraphNodeTemplate`
- L20 _private function_ `UUAFGraphNodeTemplate_InputValue()`
- L41 _private function_ `virtual void HandleVariableDropped_Implementation(UAnimNextController* Controller, URigVMUnitNode* Node, FAnimNextVariableReference Variable) const`
- L63 _private function_ `virtual void HandlePinDefaultValueChanged_Implementation(UAnimNextController* Controller, URigVMPin* Pin) const`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "UAFGraphNodeTemplate_InputValue"`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Private/Templates/UAFGraphNodeTemplate_SequencePlayer.h` (Private)


#### class `UUAFGraphNodeTemplate_SequencePlayer`  
`class UUAFGraphNodeTemplate_SequencePlayer : public UUAFGraphNodeTemplate`  
_L18-108_
- reflection: `UCLASS()`
- inherits: `UUAFGraphNodeTemplate`
- L22 _private function_ `UUAFGraphNodeTemplate_SequencePlayer()`
- L45 _private function_ `virtual void HandleAssetDropped_Implementation(UAnimNextController* Controller, URigVMUnitNode* Node, UObject* Asset) const`
- L66 _private function_ `virtual void HandlePinDefaultValueChanged_Implementation(UAnimNextController* Controller, URigVMPin* Pin) const`
- L88 _private function_ `virtual void HandleAssetRenamed_Implementation(UAnimNextController* Controller, URigVMNode* Node, const FAssetData& AssetData, const FString& OldName) const`

#### Free symbols / members of external scopes

- L15 _macro_ `#define LOCTEXT_NAMESPACE "UAFGraphNodeTemplate_SequencePlayer"`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Private/UAFAnimGraphUncookedOnlyStyle.h` (Private)


#### class `FUAFAnimGraphUncookedOnlyStyle`  
`class FUAFAnimGraphUncookedOnlyStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `static FUAFAnimGraphUncookedOnlyStyle& Get();`
- L13 _private prototype_ `FUAFAnimGraphUncookedOnlyStyle();`
- L14 _private prototype_ `~FUAFAnimGraphUncookedOnlyStyle();`
- L17 _private prototype_ `static FString InResources(const FString& RelativePath);` — Resolve path relative to plugin's resources directory

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Public/Templates/GraphNodeColors.h` (Public)


#### struct `UE::UAF::UncookedOnly::FGraphNodeColors`  
`struct FGraphNodeColors`  
_L12-18_
- L14 _public member_ `static FLinearColor Blends;`
- L15 _public member_ `static FLinearColor Controls;`
- L16 _public member_ `static FLinearColor SubGraphs;`
- L17 _public member_ `static FLinearColor Generators;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAFANIMGRAPHUNCOOKEDONLY_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphUncookedOnly/Public/Templates/UAFGraphNodeTemplate.h` (Public)


#### class `UUAFGraphNodeTemplate`  
`class UUAFGraphNodeTemplate : public UObject`  
_L34-227_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- L39 _public prototype_ `UUAFGraphNodeTemplate();`
- L43 _public prototype_ `FText GetTitle() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Get the title of this node
- L44 _public function_ `virtual FText GetTitle_Implementation() const`
- L51 _public prototype_ `FText GetSubTitle() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Get the subtitle of this node
- L52 _public function_ `virtual FText GetSubTitle_Implementation() const`
- L59 _public prototype_ `FText GetTooltipText() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Get the tooltip text of this node
- L60 _public function_ `virtual FText GetTooltipText_Implementation() const`
- L67 _public prototype_ `FText GetCategory() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Get the category of this node
- L68 _public function_ `virtual FText GetCategory_Implementation() const`
- L75 _public prototype_ `FText GetMenuDescription() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Get the menu description of this node
- L76 _public function_ `virtual FText GetMenuDescription_Implementation() const`
- L83 _public prototype_ `FSlateBrush GetIcon() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Get the icon of this node
- L84 _public function_ `FSlateBrush GetIcon_Implementation() const`
- L90 _public function_ `const FSlateBrush* GetIconBrush() const` — Get the icon of this node
- L98 _public prototype_ `FLinearColor GetColor() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Get the title color of this node
- L99 _public function_ `virtual FLinearColor GetColor_Implementation() const`
- L106 _public prototype_ `bool ConfigureNewNode(UAnimNextController* Controller, URigVMUnitNode* Node) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Called in editor when a node is first spawned
- L107 _public prototype_ `virtual bool ConfigureNewNode_Implementation(UAnimNextController* Controller, URigVMUnitNode* Node) const;`
- L111 _public prototype_ `FRigVMNodeLayout GetNodeLayout() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Get the node layout
- L112 _public function_ `virtual FRigVMNodeLayout GetNodeLayout_Implementation() const`
- L119 _public prototype_ `void HandleAssetDropped(UAnimNextController* Controller, URigVMUnitNode* Node, UObject* Asset) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Called in editor when an asset is drag/dropped. Called after ConfigureNewNode.
- L120 _public prototype_ `virtual void HandleAssetDropped_Implementation(UAnimNextController* Controller, URigVMUnitNode* Node, UObject* Asset) const;`
- L124 _public prototype_ `void HandleVariableDropped(UAnimNextController* Controller, URigVMUnitNode* Node, FAnimNextVariableReference Variable) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Called in editor when a variable is drag/dropped. Called after ConfigureNewNode.
- L125 _public prototype_ `virtual void HandleVariableDropped_Implementation(UAnimNextController* Controller, URigVMUnitNode* Node, FAnimNextVariableReference Variable) const;`
- L129 _public prototype_ `void HandlePinDefaultValueChanged(UAnimNextController* Controller, URigVMPin* Pin) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Called in editor when a pin default value is changed, e.g. to be used to reconfigure the nodes appearance
- L130 _public function_ `virtual void HandlePinDefaultValueChanged_Implementation(UAnimNextController* Controller, URigVMPin* Pin) const`
- L134 _public prototype_ `void HandleAssetRenamed(UAnimNextController* Controller, URigVMNode* Node, const FAssetData& AssetData, const FString& OldName) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "UAF|Template")` — Called in editor when an asset is renamed, e.g. to be used to reconfigure the nodes appearance
- L135 _public function_ `virtual void HandleAssetRenamed_Implementation(UAnimNextController* Controller, URigVMNode* Node, const FAssetData& AssetData, const FString& OldName) const`
- L139 _public prototype_ `FRigVMNodeLayout GetDefaultCategoryLayout() const;` — `UFUNCTION(BlueprintCallable, Category = "UAF|Template")` — Get a layout that assigns all trait pins to the default category
- L143 _public prototype_ `FRigVMNodeLayout GetPerTraitCategoriesLayout() const;` — `UFUNCTION(BlueprintCallable, Category = "UAF|Template")` — Get a layout that assigns all trait pins categories of their traits
- L147 _public prototype_ `static void SetDisplayNameForPinInLayout(FString PinPath, FString PinDisplayName, FRigVMNodeLayout& Layout);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Template")` — Sets the display name for a supplied pin in a node layout
- L151 _public prototype_ `static void SetCategoryForPinsInLayout(const TArray<FString>& PinPaths, FString CategoryPath, FRigVMNodeLayout& Layout, bool bExpandedByDefault = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Template")` — Sets the category of the supplied pins in a node layout
- L154 _public function_ `TConstArrayView<TSubclassOf<UObject>> GetDragDropAssetTypes() const` — Get all the types of asset this template handles for drag-drop
- L160 _public function_ `TConstArrayView<FAnimNextParamType> GetDragDropVariableTypes() const` — Get all the types of variable this template handles for drag-drop
- L166 _public prototype_ `URigVMUnitNode* CreateNewNode(UAnimNextController* Controller, const FVector2D& InLocation) const;` — Utility function used to create and configure a new node according to a template
- L169 _public prototype_ `void InitializeTemplateFromNode(const UAnimNextTraitStackUnitNode* InNode);` — Utility function used to initialize this template from an existing trait stack node
- L172 _public prototype_ `void RefreshNodeFromTemplate(UAnimNextController* InController, UAnimNextTraitStackUnitNode* InNode) const;` — Utility function used to refresh an existing node from this templates
- L175 _public prototype_ `static void AddDefaultTraitPinsToLayout(const UScriptStruct* Struct, FRigVMNodeLayout& InOutLayout);` — Utility function used to add all of a trait's pins to a category, named according to their display name
- L183 _protected member_ `FText Title;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Template")` — The default title of the node
- L187 _protected member_ `FText SubTitle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Template")` — The default subtitle of the node
- L191 _protected member_ `FText TooltipText;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AssetRegistrySearchable, Category="Template", meta=(MultiLine))` — The default tooltip text of the node
- L195 _protected member_ `FText Category;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AssetRegistrySearchable, Category="Template")` — The default category of the node
- L199 _protected member_ `FText MenuDescription;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AssetRegistrySearchable, Category="Template")` — The default menu description of the node
- L203 _protected member_ `FSlateBrush Icon;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AssetRegistrySearchable, Category="Template")` — The icon of the node
- L207 _protected member_ `mutable FSlateBrush CachedIcon;` — `UPROPERTY()` — Cached icon for the node
- L211 _protected member_ `FLinearColor Color = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Template")` — The default color of the node
- L215 _protected member_ `TArray<TInstancedStruct<FAnimNextTraitSharedData>> Traits;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Template")` — The traits that we will instantiate
- L219 _protected member_ `TArray<TSubclassOf<UObject>> DragDropAssetTypes;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AssetRegistrySearchable, Category="Template")` — Asset types that we handle for drag-drop
- L223 _protected member_ `TArray<FAnimNextParamType> DragDropVariableTypes;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AssetRegistrySearchable, Category="Template")` — Variable types that we handle for drag-drop
- L226 _protected member_ `FRigVMNodeLayout NodeLayout;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Template")`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace UAF` (scope `UE`)
- L24 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L29 _macro_ `#define UE_API UAFANIMGRAPHUNCOOKEDONLY_API`
