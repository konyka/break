# Plugins / UAFUncookedOnly

- module root: `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly`
- headers: 41; symbols: 865
- symbol kinds: class=32, delegate=2, enum=8, enumerator=37, externvar=1, function=82, macro=13, member=148, namespace=97, prototype=408, struct=32, typedef=2, variable=3
- DynamicallyLoadedModuleNames: UAFEditor
- PrivateDependencyModuleNames: AdvancedWidgets, AnimGraph, AnimationCore, BlueprintGraph, Core, CoreUObject, Engine, Kismet, LiveCoding, MessageLog, Slate, SlateCore, SourceControl, StructUtilsEditor, ToolMenus, UniversalObjectLocator, UniversalObjectLocatorEditor, UnrealEd, WorkspaceEditor
- PrivateIncludePathModuleNames: UAFEditor
- PublicDependencyModuleNames: RigVM, RigVMDeveloper, UAF, WorkspaceEditor

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/AnimNextAssetWorkspaceAssetUserData.h` (Internal)


#### struct `FAnimNextRigVMAssetOutlinerData`  
`struct FAnimNextRigVMAssetOutlinerData : public FWorkspaceOutlinerItemData`  
_L20-33_
- reflection: `USTRUCT()`
- inherits: `FWorkspaceOutlinerItemData`
- desc: Base struct used to identify asset entries
- L24 _public prototype_ `FAnimNextRigVMAssetOutlinerData() = default;`
- L26 _public function_ `UUAFRigVMAsset* GetAsset() const`
- L32 _public member_ `TSoftObjectPtr<UUAFRigVMAsset> SoftAssetPtr;` — `UPROPERTY(VisibleAnywhere, Category=AnimNext)`

#### struct `FAnimNextModuleOutlinerData`  
`struct FAnimNextModuleOutlinerData : public FAnimNextRigVMAssetOutlinerData`  
_L36-46_
- reflection: `USTRUCT()`
- inherits: `FAnimNextRigVMAssetOutlinerData`
- L40 _public prototype_ `FAnimNextModuleOutlinerData() = default;`
- L42 _public function_ `UUAFSystem* GetModule() const`

#### struct `FAnimNextSharedVariablesOutlinerData`  
`struct FAnimNextSharedVariablesOutlinerData : public FAnimNextRigVMAssetOutlinerData`  
_L49-59_
- reflection: `USTRUCT()`
- inherits: `FAnimNextRigVMAssetOutlinerData`
- L53 _public prototype_ `FAnimNextSharedVariablesOutlinerData() = default;`
- L55 _public function_ `UUAFSharedVariables* GetSharedVariables() const`

#### struct `FAnimNextAssetEntryOutlinerData`  
`struct FAnimNextAssetEntryOutlinerData : public FWorkspaceOutlinerItemData`  
_L63-76_
- reflection: `USTRUCT()`
- inherits: `FWorkspaceOutlinerItemData`
- desc: Base struct used to identify asset sub-entries
- L67 _public prototype_ `FAnimNextAssetEntryOutlinerData() = default;`
- L69 _public function_ `UUAFRigVMAssetEntry* GetEntry() const`
- L75 _public member_ `TSoftObjectPtr<UUAFRigVMAssetEntry> SoftEntryPtr;` — `UPROPERTY(VisibleAnywhere, Category=AnimNext)`

#### struct `FAnimNextVariableOutlinerData`  
`struct FAnimNextVariableOutlinerData : public FAnimNextAssetEntryOutlinerData`  
_L79-87_
- reflection: `USTRUCT()`
- inherits: `FAnimNextAssetEntryOutlinerData`
- L83 _public prototype_ `FAnimNextVariableOutlinerData() = default;`
- L86 _public member_ `FAnimNextParamType Type;` — `UPROPERTY(VisibleAnywhere, Category=AnimNext)`

#### struct `FAnimNextCollapseGraphsOutlinerDataBase`  
`struct FAnimNextCollapseGraphsOutlinerDataBase : public FWorkspaceOutlinerItemData`  
_L90-103_
- reflection: `USTRUCT()`
- inherits: `FWorkspaceOutlinerItemData`
- L94 _public prototype_ `FAnimNextCollapseGraphsOutlinerDataBase() = default;`
- L97 _public member_ `TSoftObjectPtr<URigVMEdGraph> SoftEditorObject;` — `UPROPERTY(VisibleAnywhere, Category=AnimNext)`
- L99 _public function_ `static bool IsCollapsedGraphBase(const FWorkspaceOutlinerItemExport& InExport)`

#### struct `FAnimNextCollapseGraphOutlinerData`  
`struct FAnimNextCollapseGraphOutlinerData : public FAnimNextCollapseGraphsOutlinerDataBase`  
_L106-111_
- reflection: `USTRUCT()`
- inherits: `FAnimNextCollapseGraphsOutlinerDataBase`
- L110 _public prototype_ `FAnimNextCollapseGraphOutlinerData() = default;`

#### struct `FAnimNextGraphFunctionOutlinerData`  
`struct FAnimNextGraphFunctionOutlinerData : public FAnimNextCollapseGraphsOutlinerDataBase`  
_L114-122_
- reflection: `USTRUCT()`
- inherits: `FAnimNextCollapseGraphsOutlinerDataBase`
- L118 _public prototype_ `FAnimNextGraphFunctionOutlinerData() = default;`
- L121 _public member_ `TSoftObjectPtr<URigVMEdGraphNode> SoftEdGraphNode;` — `UPROPERTY(VisibleAnywhere, Category=AnimNext)`

#### struct `FAnimNextGraphOutlinerData`  
`struct FAnimNextGraphOutlinerData : public FAnimNextAssetEntryOutlinerData`  
_L125-143_
- reflection: `USTRUCT()`
- inherits: `FAnimNextAssetEntryOutlinerData`
- L129 _public prototype_ `FAnimNextGraphOutlinerData() = default;`
- L131 _public function_ `IUAFRigVMGraphInterface* GetGraphInterface() const`

#### class `UAnimNextAssetWorkspaceAssetUserData`  
`class UAnimNextAssetWorkspaceAssetUserData : public UAssetUserData`  
_L146-157_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetUserData`
- L149 _public function_ `virtual bool IsEditorOnly() const override`
- L154 _private prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L156 _private member_ `mutable FWorkspaceOutlinerItemExports CachedExports;`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/AnimNextControllerBase.h` (Internal)


#### class `UAnimNextControllerBase`  
`class UAnimNextControllerBase : public URigVMController`  
_L17-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigVMController`
- desc: Implements AnimNext RigVM controller extensions
- L24 _public prototype_ `UUAFSharedVariableNode* AddAssetSharedVariableNode(const UUAFSharedVariables* InAsset, const FName& InVariableName, const FString& InCPPType, UObject* InCPPTypeObject, bool bIsGetter, const FString& InDefaultValue, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Add a shared variable from the specified asset
- L28 _public prototype_ `UUAFSharedVariableNode* AddStructSharedVariableNode(const UScriptStruct* InStruct, const FName& InVariableName, const FString& InCPPType, UObject* InCPPTypeObject, bool bIsGetter, const FString& InDefaultValue, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Add a shared variable from the specified struct
- L32 _public prototype_ `void RefreshSharedVariableNode(const FName& InNodeName, const FString& InSourceObjectPath, const FName& InVariableName, const FString& InCPPType, UObject* InCPPTypeObject, bool bSetupUndoRedo, bool bSetupOrphanPins = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Refreshes a UUAFSharedVariableNode instance with provided data (similar to URigVMController::RefreshVariableNode)
- L36 _public prototype_ `UUAFSharedVariableNode* AddSharedVariableNode(const FString& InSourceObjectPath, const FName& InVariableName, const FString& InCPPType, const FString& InCPPTypeObjectPath, bool bIsGetter, const FString& InDefaultValue, const FVector2D& InPosition, const FString& InNodeName, bool bSetupUndoRedo, bool bPrintPythonCommand);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Add a shared variable from the specified source object
- L42 _public prototype_ `URigVMUnitNode* AddUnitNodeOfClass(const FString& InScriptStructPath, const FString& InUnitNodeClassPath, const FName& InMethodName, const FVector2D& InPosition, const FString& InNodeName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Controller")` — Adds a Function / Struct Node to the edited Graph. UnitNode represent a RIGVM_METHOD declaration on a USTRUCT. This causes a NodeAdded modified event.
- L44 _public prototype_ `UUAFSharedVariableNode* ReplaceVariableNodeWithSharedVariableNode(URigVMVariableNode* InVariableNode, FName InNewVariableName, const UObject* InAssetOrStruct, bool bSetupUndoRedo, bool bPrintPythonCommand);`
- L45 _public prototype_ `URigVMVariableNode* ReplaceSharedVariableNodeWithVariableNode(UUAFSharedVariableNode* InVariableNode, FName InNewVariableName, bool bSetupUndoRedo, bool bPrintPythonCommand);`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/AnimNextEdGraph.h` (Internal)


#### class `UAnimNextEdGraph`  
`class UAnimNextEdGraph : public URigVMEdGraph`  
_L20-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigVMEdGraph`
- desc: Wraps UEdGraph which represents the node graph
- L28 _private prototype_ `virtual void PostLoad() override;` — UObject interface
- L31 _private prototype_ `virtual FRigVMClient* GetRigVMClient() const override;` — URigVMEdGraph interface
- L33 _private prototype_ `void Initialize(UUAFRigVMAssetEditorData* InEditorData);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/AnimNextEdGraphNode.h` (Internal)


#### class `UAnimNextEdGraphNode`  
`class UAnimNextEdGraphNode : public URigVMEdGraphNode`  
_L13-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigVMEdGraphNode`
- desc: EdGraphNode representation for AnimNext nodes. No longer has a specific use, but keeping this class around just in case.
- L19 _public member_ `FLinearColor NodeColor;` — `UPROPERTY(EditAnywhere, Category = "Customization", Transient)`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/AnimNextEdGraphSchema.h` (Internal)


#### class `UAnimNextEdGraphSchema`  
`class UAnimNextEdGraphSchema : public URigVMEdGraphSchema`  
_L15-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigVMEdGraphSchema`
- L20 _private function_ `virtual TSubclassOf<URigVMEdGraphNode> GetGraphNodeClass(const URigVMEdGraph* InGraph) const override` — URigVMEdGraphSchema interface
- L21 _private prototype_ `virtual bool ShouldHidePinOnNode(const URigVMPin* InModelPin) const override;`
- L22 _private prototype_ `virtual bool IsStructEditable(UStruct* InStruct) const override;`
- L25 _private prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;` — UEdGraphSchema interface
- L28 _protected prototype_ `static TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter(const UEdGraph* Graph);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/AnimNextRigVMAssetEditorData.h` (Internal)


#### enum `EAnimNextEditorDataNotifType`  
`enum class EAnimNextEditorDataNotifType : uint8`  
_L93-109_
- L95 _public enumerator_ `PropertyChanged` — An property was changed (Subject == UObject)
- L96 _public enumerator_ `EntryAdded` — An entry has been added (Subject == UUAFVMAssetEntry)
- L97 _public enumerator_ `EntryRemoved` — An entry has been removed (Subject == UUAFRigVMAssetEditorData)
- L98 _public enumerator_ `EntryRenamed` — An entry has been renamed (Subject == UUAFRigVMAssetEntry)
- L99 _public enumerator_ `EntryAccessSpecifierChanged` — An entry access specifier has been changed (Subject == UUAFRigVMAssetEntry)
- L100 _public enumerator_ `VariableTypeChanged` — A variable entry type changed (Subject == UAnimNextVariableEntry)
- L101 _public enumerator_ `UndoRedo` — Transaction was performed (Subject == UObject)
- L102 _public enumerator_ `VariableDefaultValueChanged` — A variable entry default value changed (Subject == UAnimNextVariableEntry)
- L103 _public enumerator_ `VariableBindingChanged` — A variable entry binding changed (Subject == UAnimNextVariableEntry)
- L104 _public enumerator_ `VariableCategoryChanged` — A variable entry its category changed (Subject == UAnimNextVariableEntry)
- L105 _public enumerator_ `CategoryAdded` — A category has been added (Subject == UUAFRigVMAssetEditorData)
- L106 _public enumerator_ `CategoryChanged` — A category has been changed (Subject == UUAFRigVMAssetEditorData)
- L107 _public enumerator_ `CategoryRemoved` — A category has been removed (Subject == UUAFRigVMAssetEditorData)
- L108 _public enumerator_ `VariablesReordered` — Asset entries have been reordered (Subject == UUAFRigVMAssetEditorData)

#### class `UUAFRigVMAssetLibrary`  
`class UUAFRigVMAssetLibrary : public UBlueprintFunctionLibrary`  
_L122-178_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Script-callable editor API hoisted onto UUAFRigVMAsset
- L129 _public prototype_ `static UUAFRigVMAssetEntry* FindEntry(UUAFRigVMAsset* InAsset, FName InName);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Finds an entry in an AnimNext asset
- L133 _public prototype_ `static bool RemoveEntry(UUAFRigVMAsset* InAsset, UUAFRigVMAssetEntry* InEntry, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Removes an entry from an UAF asset
- L137 _public prototype_ `static bool RemoveEntries(UUAFRigVMAsset* InAsset, const TArray<UUAFRigVMAssetEntry*>& InEntries, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Removes multiple entries from an UAF asset
- L141 _public prototype_ `static bool RemoveAllEntries(UUAFRigVMAsset* InAsset, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Removes all entries from an UAF asset
- L145 _public prototype_ `static UAnimNextVariableEntry* AddVariable(UUAFRigVMAsset* InAsset, FName InName, EPropertyBagPropertyType InValueType, EPropertyBagContainerType InContainerType = EPropertyBagContainerType::None, const UObject* InValueTypeObject = nullptr, const FString& InDefaultValue = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Adds a parameter to an UAF asset
- L149 _public prototype_ `static UAnimNextEventGraphEntry* AddEventGraph(UUAFRigVMAsset* InAsset, FName InName, UScriptStruct* InEventStruct, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Adds an event graph to an UAF asset
- L153 _public prototype_ `static UUAFSharedVariablesEntry* AddSharedVariables(UUAFRigVMAsset* InAsset, UUAFSharedVariables* InSharedVariables, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Adds shared variables to an UAF asset
- L157 _public prototype_ `static UUAFSharedVariablesEntry* AddSharedVariablesStruct(UUAFRigVMAsset* InAsset, UScriptStruct* InStruct, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Adds shared variables struct to an UAF asset
- L161 _public prototype_ `static URigVMLibraryNode* AddFunction(UUAFRigVMAsset* InAsset, FName InFunctionName, bool bInMutable, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Adds a function to an UAF asset
- L165 _public prototype_ `static bool AddCategory(UUAFRigVMAsset* InAsset, const FString& CategoryName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Adds a category to an UAF asset
- L169 _public prototype_ `static bool RenameCategory(UUAFRigVMAsset* InAsset, const FString& CategoryName, const FString& NewCategoryName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Renames a category within an UAF asset
- L173 _public prototype_ `static bool RemoveCategory(UUAFRigVMAsset* InAsset, const FString& CategoryName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Removes a category from within an UAF asset
- L177 _public prototype_ `static bool RenameVariable(UUAFRigVMAsset* InAsset, FName InVariableName, FName InNewName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Entries", meta=(ScriptMethod))` — Renames a variable in an UAF asset, updating all references across the project

#### class `UUAFRigVMAssetEditorData`  
`class UUAFRigVMAssetEditorData : public UObject, public IRigVMClientHost, public IRigVMGraphFunctionHost, public IRigVMClientExternalModelHost`  
_L182-792_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject,IRigVMClientHost,IRigVMGraphFunctionHost,IRigVMClientExternalModelHost`
- desc: Base class for all AnimNext editor data objects that use RigVM
- L188 _public prototype_ `UAnimNextVariableEntry* AddVariable(FName InName, FAnimNextParamType InType, const FString& InDefaultValue = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Adds a parameter to this asset
- L191 _public prototype_ `UAnimNextEventGraphEntry* AddEventGraph(FName InName, UScriptStruct* InEventStruct, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Adds an event graph to this asset
- L194 _public prototype_ `UUAFSharedVariablesEntry* AddSharedVariables(const UUAFSharedVariables* InSharedVariables, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Adds shared variables to this asset
- L197 _public prototype_ `UUAFSharedVariablesEntry* AddSharedVariablesStruct(const UScriptStruct* InStruct, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Adds shared variables struct to this asset
- L200 _public prototype_ `UUAFSharedVariablesEntry* AddSharedVariablesRigVMAsset(const IRigVMRuntimeAssetInterface* InRigVMAsset, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Adds shared variables from IRigVMRuntimeAssetInterfaces to this asset
- L203 _public prototype_ `URigVMLibraryNode* AddFunction(FName InFunctionName, bool bInMutable, bool bInSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Adds a function to this asset
- L206 _public prototype_ `UUAFRigVMAssetEntry* FindEntry(FName InName) const;` — Find an entry by name
- L209 _public prototype_ `bool AddCategory(const FString& CategoryName, bool bInSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Adds a category for variables/functions to this asset
- L212 _public prototype_ `bool RenameCategory(const FString& OldName, const FString& NewName, bool bInSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Renames a category using provided new name
- L215 _public prototype_ `bool RemoveCategory(const FString CategoryName, bool bInSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Removes category with provided name
- L218 _public prototype_ `void ReorderCategory(const FString& CategoryName, const FString& BeforeCategoryName, bool bInSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Reorders category entry to appear before provided BeforeCategoryName
- L221 _public prototype_ `void ReorderVariable(UAnimNextVariableEntry* VariableEntry, const UAnimNextVariableEntry* BeforeVariableEntry, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Reorders variable entry to appear before provided BeforeVariableEntry
- L224 _public prototype_ `static void ReportError(const TCHAR* InMessage);` — Report an error to the user, typically used for scripting APIs
- L289 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L290 _protected prototype_ `virtual void PostLoad() override;`
- L291 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L292 _protected prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L293 _protected prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L294 _protected function_ `virtual bool IsEditorOnly() const override`
- L295 _protected prototype_ `virtual bool Rename(const TCHAR* NewName = nullptr, UObject* NewOuter = nullptr, ERenameFlags Flags = REN_None) override;`
- L296 _protected prototype_ `virtual void PreDuplicate(FObjectDuplicationParameters& DupParams) override;`
- L297 _protected prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L299 _protected prototype_ `void HandlePackageDone(const FEndLoadPackageContext& Context);`
- L300 _protected prototype_ `void HandlePackageDone();`
- L302 _protected prototype_ `virtual void GetAnimNextAssetRegistryTags(FAssetRegistryTagsContext& Context, FAnimNextAssetRegistryExports& OutExports) const;`
- L305 _protected function_ `virtual FString GetAssetName() const override` — IRigVMClientHost interface
- L306 _protected prototype_ `virtual UClass* GetRigVMSchemaClass() const override;`
- L307 _protected prototype_ `virtual UScriptStruct* GetRigVMExecuteContextStruct() const override;`
- L308 _protected prototype_ `virtual UClass* GetRigVMEdGraphClass() const override;`
- L309 _protected prototype_ `virtual UClass* GetRigVMEdGraphNodeClass() const override;`
- L310 _protected prototype_ `virtual UClass* GetRigVMEdGraphSchemaClass() const override;`
- L311 _protected prototype_ `virtual UClass* GetRigVMEditorSettingsClass() const override;`
- L312 _protected prototype_ `virtual FRigVMClient* GetRigVMClient() override;`
- L313 _protected prototype_ `virtual const FRigVMClient* GetRigVMClient() const override;`
- L314 _protected prototype_ `virtual TScriptInterface<IRigVMGraphFunctionHost> GetRigVMGraphFunctionHost() override;`
- L315 _protected prototype_ `virtual TScriptInterface<const IRigVMGraphFunctionHost> GetRigVMGraphFunctionHost() const override;`
- L316 _protected prototype_ `virtual void HandleRigVMGraphAdded(const FRigVMClient* InClient, const FString& InNodePath) override;`
- L317 _protected prototype_ `virtual void HandleRigVMGraphRemoved(const FRigVMClient* InClient, const FString& InNodePath) override;`
- L318 _protected prototype_ `virtual void HandleRigVMGraphRenamed(const FRigVMClient* InClient, const FString& InOldNodePath, const FString& InNewNodePath) override;`
- L319 _protected prototype_ `virtual void HandleConfigureRigVMController(const FRigVMClient* InClient, URigVMController* InControllerToConfigure) override;`
- L320 _protected prototype_ `virtual UObject* GetEditorObjectForRigVMGraph(const URigVMGraph* InVMGraph) const override;`
- L321 _protected prototype_ `virtual URigVMGraph* GetRigVMGraphForEditorObject(UObject* InObject) const override;`
- L322 _protected prototype_ `virtual void RecompileVM() override;`
- L323 _protected prototype_ `virtual void RecompileVMIfRequired() override;`
- L324 _protected prototype_ `virtual void RequestAutoVMRecompilation() override;`
- L325 _protected prototype_ `virtual void SetAutoVMRecompile(bool bAutoRecompile) override;`
- L326 _protected prototype_ `virtual bool GetAutoVMRecompile() const override;`
- L327 _protected prototype_ `virtual void IncrementVMRecompileBracket() override;`
- L328 _protected prototype_ `virtual void DecrementVMRecompileBracket() override;`
- L329 _protected prototype_ `virtual void RefreshAllModels(ERigVMLoadType InLoadType) override;`
- L330 _protected prototype_ `virtual void OnRigVMRegistryChanged() override;`
- L331 _protected prototype_ `virtual void RequestRigVMInit() override;`
- L332 _protected prototype_ `virtual URigVMGraph* GetModel(const UEdGraph* InEdGraph = nullptr) const override;`
- L333 _protected prototype_ `virtual URigVMGraph* GetModel(const FString& InNodePath) const override;`
- L334 _protected prototype_ `virtual URigVMGraph* GetDefaultModel() const override;`
- L335 _protected prototype_ `virtual TArray<URigVMGraph*> GetAllModels() const override;`
- L336 _protected prototype_ `virtual URigVMFunctionLibrary* GetLocalFunctionLibrary() const override;`
- L337 _protected prototype_ `virtual URigVMFunctionLibrary* GetOrCreateLocalFunctionLibrary(bool bSetupUndoRedo = true) override;`
- L338 _protected prototype_ `virtual URigVMGraph* AddModel(FString InName = TEXT("Rig Graph"), bool bSetupUndoRedo = true, bool bPrintPythonCommand = true)`
- L339 _protected prototype_ `virtual bool RemoveModel(FString InName = TEXT("Rig Graph"), bool bSetupUndoRedo = true, bool bPrintPythonCommand = true)`
- L340 _protected prototype_ `virtual FRigVMGetFocusedGraph& OnGetFocusedGraph() override;`
- L341 _protected prototype_ `virtual const FRigVMGetFocusedGraph& OnGetFocusedGraph() const override;`
- L342 _protected prototype_ `virtual URigVMGraph* GetFocusedModel() const override;`
- L343 _protected prototype_ `virtual URigVMController* GetController(const URigVMGraph* InGraph = nullptr) const override;`
- L344 _protected prototype_ `virtual URigVMController* GetControllerByName(const FString InGraphName = TEXT("")) const override;`
- L345 _protected prototype_ `virtual URigVMController* GetOrCreateController(URigVMGraph* InGraph = nullptr) override;`
- L346 _protected prototype_ `virtual URigVMController* GetController(const UEdGraph* InEdGraph) const override;`
- L347 _protected prototype_ `virtual URigVMController* GetOrCreateController(const UEdGraph* InGraph) override;`
- L348 _protected prototype_ `virtual TArray<FString> GeneratePythonCommands() override;`
- L350 _protected function_ `virtual TArray<FString> GeneratePythonCommands(const FString InNewBlueprintName) override` — `UE_DEPRECATED(5.8, "Use TArray<FString> GeneratePythonCommands() instead.")`
- L351 _protected prototype_ `virtual void SetupPinRedirectorsForBackwardsCompatibility() override;`
- L352 _protected prototype_ `virtual FRigVMGraphModifiedEvent& OnModified() override;`
- L353 _protected prototype_ `virtual bool IsFunctionPublic(const FName& InFunctionName) const override;`
- L354 _protected prototype_ `virtual void MarkFunctionPublic(const FName& InFunctionName, bool bIsPublic = true) override;`
- L355 _protected prototype_ `virtual void RenameGraph(const FString& InNodePath, const FName& InNewName) override;`
- L359 _protected prototype_ `virtual FRigVMGraphFunctionStore* GetRigVMGraphFunctionStore() override;` — IRigVMGraphFunctionHost interface
- L360 _protected prototype_ `virtual const FRigVMGraphFunctionStore* GetRigVMGraphFunctionStore() const override;`
- L363 _protected function_ `virtual const TArray<TObjectPtr<URigVMGraph>>& GetExternalModels() const override` — IRigVMClientExternalModelHost interface
- L364 _protected prototype_ `virtual TObjectPtr<URigVMGraph> CreateContainedGraphModel(URigVMCollapseNode* CollapseNode, const FName& Name) override;`
- L367 _protected function_ `virtual TSubclassOf<URigVMController> GetControllerClass() const` — Override called during initialization to determine what RigVM controller class is used
- L370 _protected prototype_ `virtual UScriptStruct* GetExecuteContextStruct() const PURE_VIRTUAL(UUAFRigVMAssetEditorData::GetExecuteContextStruct, return nullptr;)` — Override called during initialization to determine what RigVM execute struct is used
- L376 _protected prototype_ `virtual void CreateEdGraphForCollapseNode(URigVMCollapseNode* InNode, bool bForce);` — Create and store a UEdGraph that corresponds to a URigVMCollapseNode
- L379 _protected prototype_ `virtual bool RemoveEdGraphForCollapseNode(URigVMCollapseNode* InNode, bool bNotify);` — Destroy a UEdGraph that corresponds to a URigVMCollapseNode
- L382 _protected prototype_ `virtual bool RemoveEdGraph(URigVMGraph* InModel);` — Remove the UEdGraph that corresponds to a URigVMGraph
- L385 _protected prototype_ `virtual void Initialize(bool bRecompileVM);` — Initialize the asset for use
- L388 _protected prototype_ `virtual void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);` — Handle RigVM modification events
- L391 _protected prototype_ `virtual TSubclassOf<UAssetUserData> GetAssetUserDataClass() const;` — Class to use when instantiating AssetUserData for the EditorData instance
- L395 _protected prototype_ `virtual void InitializeAssetUserData();` — Override point called during initialization (PostLoad/PostDuplicate) used for setting up asset user data. By default this instantiates any asset user data that is missing according to GetAssetUserDataClass().
- L398 _protected function_ `virtual TConstArrayView<TSubclassOf<UUAFRigVMAssetEntry>> GetEntryClasses() const PURE_VIRTUAL(UUAFRigVMAssetEditorData::GetEntryClasses, return {};)` — Get all the kinds of entry for this asset
- L407 _protected function_ `virtual void OnCompileJobStarted()` — Called before a batch of compile jobs for dependent asset starts
- L410 _protected function_ `virtual void OnPreCompileAsset(FRigVMCompileSettings& InSettings)` — Compilation phase 1: Called before RigVM compilation to setup compiler settings and clean our outer asset of compiler-generated data
- L414 _protected function_ `virtual void OnPreCompileGetProgrammaticFunctionHeaders(const FRigVMCompileSettings& InSettings, FAnimNextGetFunctionHeaderCompileContext& OutCompileContext)` — Compilation phase 2: Called before RigVM compilation to allow this asset to specify function headers that require generation, along with function generation metadata. While users may manually generate graphs using function headers, for convience we provide an autogeneration process for function headers requested here.
- L418 _protected function_ `virtual void OnPreCompileGetProgrammaticVariables(const FRigVMCompileSettings& InSettings, FAnimNextGetVariableCompileContext& OutCompileContext)` — Compilation phase 3: Called before RigVM compilation to allow this asset to generate variables to be injected, separate method to allow programmatic graphs to use these vars These variables will be regenerated each compile, and are not saved between compiles
- L422 _protected function_ `virtual void OnPostCompileVariables(const FRigVMCompileSettings& InSettings, const FAnimNextGetVariableCompileContext& InCompileContext)` — Compilation phase 3.1: Called after variable compilation, before RigVM compilation to allow this asset to generate variables to be injected, separate method to allow programmatic graphs to use these vars These variables will be regenerated each compile, and are not saved between compiles
- L425 _protected function_ `virtual void OnPreCompileGetProgrammaticGraphs(const FRigVMCompileSettings& InSettings, FAnimNextGetGraphCompileContext& OutCompileContext)` — Compilation phase 4: Called before RigVM compilation to allow this asset to generate graphs to be injected
- L428 _protected function_ `virtual void OnPreCompileProcessGraphs(const FRigVMCompileSettings& InSettings, FAnimNextProcessGraphCompileContext& OutCompileContext)` — Compilation phase 5: Called before RigVM compilation to allow this asset to process, transform or replace the graphs that will be compiled
- L431 _protected function_ `virtual void OnPostCompileCleanup(const FRigVMCompileSettings& InSettings)` — Compilation phase 6: Called after RigVM compilation to clean up/finish the compilation process
- L434 _protected function_ `virtual void OnCompileJobFinished()` — Called after a batch of compile jobs for dependent asset finishes and re-allocation can occur
- L440 _protected prototype_ `FAnimNextGetFunctionHeaderCompileContext GetFunctionHeaderContext(const FRigVMCompileSettings& InSettings, FAnimNextRigVMAssetCompileContext& InCompileContext) const;` — Return a function header compile context. Used when an external asset needs compile contexts for this asset.
- L443 _protected prototype_ `FAnimNextGetVariableCompileContext GetVariableCompileContext(const FRigVMCompileSettings& InSettings, FAnimNextRigVMAssetCompileContext& InCompileContext) const;` — Return a variable compile context. Used when an external asset needs compile contexts for this asset.
- L446 _protected function_ `virtual void CustomizeNewAssetEntry(UUAFRigVMAssetEntry* InNewEntry) const` — Customization point for derived types to transform new asset entries
- L449 _protected prototype_ `static UObject* CreateNewSubEntry(UUAFRigVMAssetEditorData* InEditorData, TSubclassOf<UObject> InClass);` — Helper for creating new sub-entries. Sets package flags and outers appropriately
- L453 _protected function_ `template<typename EntryClassType> static EntryClassType* CreateNewSubEntry(UUAFRigVMAssetEditorData* InEditorData)` — Helper for creating new sub-entries. Sets package flags and outers appropriately
- L459 _protected function_ `TConstArrayView<TObjectPtr<UUAFRigVMAssetEntry>> GetAllEntries() const` — Get all the entries for this asset
- L462 _protected prototype_ `TArray<UEdGraph*> GetAllEdGraphs() const;` — Access all the UEdGraphs in this asset
- L465 _protected prototype_ `void GatherDefaultComponents(UUAFRigVMAsset* InAsset);` — Called during compilation to gather instance components from nodes etc.
- L470 _protected function_ `template<typename EntryType, typename PredicateType> void ForEachEntryOfType(PredicateType InPredicate) const` — Iterate over all entries of the specified type If predicate returns false, iteration is stopped
- L486 _protected function_ `template<typename EntryType> EntryType* FindFirstEntryOfType() const` — Find the first entry of the specified type
- L499 _protected function_ `template<class T> void GetAllNodesOfClass(TArray<T*>& OutNodes) const` — Returns all nodes in all graphs of the specified class
- L545 _protected prototype_ `bool RemoveEntry(UUAFRigVMAssetEntry* InEntry, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Remove an entry from the asset @return true if the item was removed
- L549 _protected prototype_ `bool RemoveEntries(TConstArrayView<UUAFRigVMAssetEntry*> InEntries, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Remove a number of entries from the asset @return true if any items were removed
- L553 _protected prototype_ `bool RemoveAllEntries(bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — Remove all entries from the asset @return true if any items were removed
- L555 _protected prototype_ `void BroadcastModified(EAnimNextEditorDataNotifType InType, UObject* InSubject);`
- L557 _protected prototype_ `void ReconstructAllNodes();`
- L559 _protected prototype_ `void RequestVMRecompilation();`
- L562 _protected prototype_ `UUAFRigVMAssetEntry* FindEntryForRigVMGraph(const URigVMGraph* InRigVMGraph) const;` — Find an entry that corresponds to the specified RigVMGraph. This uses the name of the graph to match the entry
- L565 _protected prototype_ `UUAFRigVMAssetEntry* FindEntryForRigVMEdGraph(const URigVMEdGraph* InRigVMEdGraph) const;` — Find an entry that corresponds to the specified RigVMGraph. This uses the name of the graph to match the entry
- L568 _protected prototype_ `bool HasPublicVariables() const;` — Checks all entries to see if any are public variables
- L581 _protected function_ `friend uint32 GetTypeHash(const FVariableInfo& Info)`
- L613 _protected prototype_ `void GetAllVariables(TArray<FVariableInfo>& OutVariables, EVariableRecursion InRecursion, EVariableAccessFilter InAccess) const;` — Gets any variables that this asset has according to the pass-in params. Variables have no specified order. May recurse into shared variables, so variables returned by this function may not be directly owned by this asset. In this case the SourceObject will indicate where the variable came from.
- L616 _protected prototype_ `void RefreshExternalModels();` — Refresh the 'external' models for the RigVM client to reference
- L619 _protected prototype_ `void RefreshFunctionImplementationGraphs();` — Update referenced function impl graph nodes to avoid compile issues. Doesn't recompile, only updates graph nodes.
- L622 _protected prototype_ `void ClearErrorInfoForAllEdGraphs();` — Clear the error info for all EdGraphNodes
- L625 _protected prototype_ `void HandleReportFromCompiler(EMessageSeverity::Type InSeverity, UObject* InSubject, const FString& InMessage) const;` — Handle compiler reporting
- L626 _protected prototype_ `void HandleMessageFromCompiler(TSharedRef<FTokenizedMessage> InMessage, bool bAddMessageToLog = true) const;`
- L629 _protected prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);` — Support extra references in GC
- L632 _protected prototype_ `void AddEntryInternal(UUAFRigVMAssetEntry* InEntry);` — Add a new entry to this asset, taking into account external packaging status
- L635 _protected prototype_ `void InsertEntryInternal(UUAFRigVMAssetEntry* InEntry, int32 InsertionIndex);` — Inserts a new entry to this asset, at the provided index, while taking into account external packaging status
- L638 _protected prototype_ `void RemoveEntryInternal(UUAFRigVMAssetEntry* InEntry);` — Remove an entry to this asset, taking into account external packaging status
- L641 _protected prototype_ `void RemoveProgrammaticGraphs(TArrayView<URigVMGraph*> InGraphs);` — Remove any programmatic graphs generated during compilation and consign them to the transient package
- L644 _protected prototype_ `void RemoveTransientGraphs(TArrayView<URigVMGraph*> InGraphs);` — Remove any transient graphs in the passed-in array (e.g. generated during compilation) and consign them to the transient package
- L647 _protected prototype_ `static void HandleRemoveNotify(UObject* InAsset, const FString& InFindString, bool bFindWholeWord, ESearchCase::Type InSearchCase);` — Handle removing a notify
- L650 _protected prototype_ `static void HandleReplaceNotify(UObject* InAsset, const FString& InFindString, const FString& InReplaceString, bool bFindWholeWord, ESearchCase::Type InSearchCase);` — Handle replacing a notify
- L653 _protected prototype_ `bool IsDirtyForRecompilation() const;` — Check whether this asset should be recompiled
- L656 _protected prototype_ `virtual void BuildFunctionHeadersContext(const FRigVMCompileSettings& InSettings, FAnimNextGetFunctionHeaderCompileContext& OutCompileContext) const;` — Called pre programmatic function header population to allow population of compile context in a const manner. May be used by external assets querying our VM.
- L659 _protected function_ `virtual void BuildProgrammaticVariablesContext(const FRigVMCompileSettings& InSettings, FAnimNextGetVariableCompileContext& OutCompileContext) const` — Called pre programmatic variable population to allow population of compile context in a const manner. May be used by external assets querying our VM.
- L662 _protected prototype_ `void BuildFunctionWrapperEventVariables(FAnimNextRigVMAssetCompileContext& InContext) const;` — Called during compilation to generate internal variables used for natively-callable RigVM functions
- L665 _protected prototype_ `void BuildFunctionWrapperEvents(FAnimNextRigVMAssetCompileContext& InContext, const FRigVMCompileSettings& InSettings);` — Called during compilation to generate wrapper events for natively-callable RigVM functions
- L668 _protected prototype_ `FInstancedPropertyBag GenerateCombinedPropertyBag(const FRigVMCompileSettings& InSettings, const FAnimNextGetVariableCompileContext& InCompileContext) const;` — Generates a combined property bag consisting of all variables both internal and shared
- L671 _protected prototype_ `void UpgradeDataInterfaces();` — Serialization/post-load fixup for old data
- L674 _protected prototype_ `void ConditionalPatchFunctionsOnLoad();` — Conditionally calls PatchFunctionReferencesOnLoad and PatchFunctionsOnLoad on the RigVMClient
- L676 _protected prototype_ `void SetVMRecompilationRequired(bool bInIsRequired);`
- L680 _protected member_ `TArray<TObjectPtr<UUAFRigVMAssetEntry>> Entries;` — `UPROPERTY()` — All entries in this asset
- L684 _protected member_ `TArray<TObjectPtr<UUAFRigVMAssetEntry>> InternalEntries_DEPRECATED;` — `UE_DEPRECATED(5.7, "This property is deprecated. Please use Entries instead")` — `UPROPERTY()`
- L687 _protected member_ `FRigVMClient RigVMClient;` — `UPROPERTY()`
- L690 _protected member_ `FRigVMGraphFunctionStore GraphFunctionStore;` — `UPROPERTY()`
- L695 _protected member_ `TObjectPtr<const UScriptStruct> NativeInterface_DEPRECATED;` — `UE_DEPRECATED(5.6, "This property is deprecated. Please use NativeInterfaces instead")` — `UPROPERTY()` — The native C++ struct that is used to communicate with this asset
- L700 _protected member_ `TArray<TObjectPtr<const UScriptStruct>> NativeInterfaces_DEPRECATED;` — `UE_DEPRECATED(5.6, "This property is deprecated. Please use NativeInterfaces instead")` — `UPROPERTY()` — The list of native C++ structs that are used to communicate with this asset
- L703 _protected member_ `FRigVMEdGraphDisplaySettings RigGraphDisplaySettings;` — `UPROPERTY(EditAnywhere, Category = "User Interface")`
- L706 _protected member_ `FRigVMRuntimeSettings VMRuntimeSettings;` — `UPROPERTY(EditAnywhere, Category = "VM")`
- L709 _protected member_ `FRigVMCompileSettings VMCompileSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VM", meta = (AllowPrivateAccess = "true"))`
- L712 _protected member_ `TMap<FString, FRigVMOperand> PinToOperandMap;` — `UPROPERTY(transient, DuplicateTransient)`
- L715 _protected member_ `TArray<FEditedDocumentInfo> LastEditedDocuments;` — `UPROPERTY()`
- L719 _protected member_ `TArray<TInstancedStruct<FUAFAssetInstanceComponent>> AdditionalComponents;` — `UPROPERTY(EditAnywhere, Category = Components)` — Additional components that should be allocated for instances of this asset
- L724 _protected member_ `TArray<TInstancedStruct<FUAFAssetInstanceComponent>> Components;` — `UPROPERTY(VisibleAnywhere, Category=Components, AdvancedDisplay, meta = (DisplayName = "Required Components"))` — Components that will be allocated for instances of this asset This is a combination of required components based on the asset and additional components added by the user
- L726 _protected member_ `int32 VMRecompilationBracket = 0;`
- L727 _protected member_ `bool bVMRecompilationRequired = false;`
- L728 _protected member_ `bool bIsCompiling = false;`
- L732 _protected member_ `bool bUsesExternalPackages_DEPRECATED = false;` — `UE_DEPRECATED(5.7, "Storing asset entries as external packages has been deprecated")` — `UPROPERTY()`
- L735 _protected member_ `FName DefaultInjectionSite_DEPRECATED;` — `UPROPERTY()`
- L739 _protected member_ `FAnimNextVariableReference DefaultInjectionSiteReference;` — `UPROPERTY(EditAnywhere, DisplayName = "Default Injection Site", Category=Injection, meta=(AllowedType = FAnimNextAnimGraph))` — The injection site (AnimNext Graph) that will be used by default
- L743 _protected member_ `TArray<FString> VariableAndFunctionCategories;` — `UPROPERTY()` — Set of category names, assignable to variables/functions by user
- L745 _protected member_ `FOnRigVMCompiledEvent RigVMCompiledEvent;`
- L747 _protected member_ `FRigVMGraphModifiedEvent RigVMGraphModifiedEvent;`
- L750 _protected member_ `FSimpleMulticastDelegate RecompileRequiredChangedEvent;` — Compile status depends upon bVMRecompilationRequired so it useful to know when this value is changed
- L753 _protected member_ `UE::UAF::UncookedOnly::FOnEditorDataModified ModifiedDelegate;` — Delegate to subscribe to modifications to this editor data
- L756 _protected member_ `UE::UAF::UncookedOnly::FOnInteractionBracketFinished InteractionBracketFinished;` — Delegate to get notified when an interaction bracket reaches 0
- L759 _protected member_ `mutable TOptional<FAnimNextAssetRegistryExports> CachedExports;` — Cached exports, generated lazily or on compilation
- L762 _protected member_ `TArray<TObjectPtr<URigVMGraph>> GraphModels;` — Collection of models gleaned from graphs
- L766 _protected member_ `TArray<TObjectPtr<URigVMEdGraph>> FunctionEdGraphs;` — `UPROPERTY()` — Set of functions implemented for this graph
- L770 _protected member_ `TObjectPtr<UAnimNextEdGraph> FunctionLibraryEdGraph;` — `UPROPERTY()` — Default FunctionLibrary EdGraph
- L773 _protected member_ `bool bAutoRecompileVM = true;` — `UPROPERTY()`
- L777 _protected member_ `bool bDisplayCompilePIEWarning;` — `UPROPERTY(transient)` — Whether to show a warning when attempting to start in PIE and there is a compiler error on this asset
- L779 _protected member_ `bool bVMRecompilationRequested = false;`
- L780 _protected member_ `mutable bool bErrorsDuringCompilation = false;`
- L781 _protected member_ `mutable bool bWarningsDuringCompilation = false;`
- L782 _protected member_ `bool bSuspendModelNotificationsForSelf = false;`
- L783 _protected member_ `bool bSuspendAllNotifications = false;`
- L784 _protected member_ `bool bCompileInDebugMode = false;`
- L785 _protected member_ `bool bSuspendPythonMessagesForRigVMClient = true;`
- L786 _protected member_ `bool bSuspendEditorDataNotifications = false;`
- L787 _protected member_ `bool bSuspendCompilationNotifications = false;`
- L788 _protected member_ `bool bSuspendCompilerReports = false;`
- L789 _protected member_ `bool bUpgradeDataInterfacesOnLoad = false;`
- L790 _protected member_ `bool bFunctionsPatched = false;`
- L791 _protected member_ `bool bHasCompiledVariables = false;`

#### struct `UUAFRigVMAssetEditorData::FVariableInfo`  
`struct FVariableInfo`  
_L571-594_
- desc: Information about a variable returned from GetAllVariables
- L573 _public member_ `FName Name;`
- L574 _public member_ `FAnimNextParamType Type;`
- L575 _public member_ `const UObject* SourceObject = nullptr;`
- L576 _public member_ `EAnimNextExportAccessSpecifier Access = EAnimNextExportAccessSpecifier::Private;`
- L577 _public member_ `const FProperty* Property = nullptr;`
- L578 _public member_ `TConstArrayView<uint8> DefaultValue;`
- L579 _public member_ `FGuid StableGuid;`
- L586 _public function_ `bool operator==(const FVariableInfo& Other) const`

#### enum `UUAFRigVMAssetEditorData::EVariableRecursion`  
`enum class EVariableRecursion`  
_L597-601_
- desc: How to recurse when getting variable info
- L599 _public enumerator_ `SelfOnly`
- L600 _public enumerator_ `IncludeShared`

#### enum `UUAFRigVMAssetEditorData::EVariableAccessFilter`  
`enum class EVariableAccessFilter`  
_L604-608_
- desc: How to filter variables by access level when getting variable info
- L606 _public enumerator_ `PublicOnly`
- L607 _public enumerator_ `All`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace UAF` (scope `UE`)
- L33 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L43 _namespace_ `namespace UE`
- L43 _namespace_ `namespace UAF` (scope `UE`)
- L43 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L81 _namespace_ `namespace UE`
- L81 _namespace_ `namespace UAF` (scope `UE`)
- L81 _namespace_ `namespace Tests` (scope `UE::UAF`)
- L111 _namespace_ `namespace UE`
- L111 _namespace_ `namespace UAF` (scope `UE`)
- L111 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L114 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnEditorDataModified, UUAFRigVMAssetEditorData* , EAnimNextEditorDataNotifType , UObject* );` — A delegate for subscribing / reacting to editor data modifications.
- L114 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnEditorDataModified, UUAFRigVMAssetEditorData* , EAnimNextEditorDataNotifType , UObject* );` (scope `UE::UAF::UncookedOnly`) — A delegate for subscribing / reacting to editor data modifications.
- L117 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionBracketFinished, UUAFRigVMAssetEditorData* );` — An interaction bracket count reached 0
- L117 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionBracketFinished, UUAFRigVMAssetEditorData* );` (scope `UE::UAF::UncookedOnly`) — An interaction bracket count reached 0
- L490 _function_ `` (scope `UUAFRigVMAssetEditorData::FindFirstEntryOfType`)
- L502 _function_ `` (scope `UUAFRigVMAssetEditorData::GetAllNodesOfClass`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/AnimNextRigVMAssetSchema.h` (Internal)


#### class `UUAFRigVMAssetSchema`  
`class UUAFRigVMAssetSchema : public URigVMSchema`  
_L13-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigVMSchema`
- L17 _private function_ `virtual UClass* GetEdGraphSchemaClass() const override`
- L22 _private function_ `virtual bool SupportsNodeLayouts(const URigVMGraph* InGraph) const override`
- L28 _protected prototype_ `UUAFRigVMAssetSchema();`
- L30 _protected function_ `virtual bool ShouldPatchGraphSchema() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/AnimNextSharedVariableNode.h` (Internal)


#### class `UUAFSharedVariableNode`  
`class UUAFSharedVariableNode : public URigVMVariableNode`  
_L23-54_
- reflection: `UCLASS()`
- inherits: `URigVMVariableNode`
- L28 _private prototype_ `virtual FString GetNodeSubTitle() const override;` — URigVMVariableNode interface
- L29 _private prototype_ `virtual void PostLoad() override;`
- L30 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L33 _private prototype_ `void UpdateCachedVariableGUID();`
- L41 _private member_ `TObjectPtr<const UUAFSharedVariables> Asset;` — `UPROPERTY()`
- L44 _private member_ `TObjectPtr<const UScriptStruct> Struct;` — `UPROPERTY()`
- L47 _private member_ `TScriptInterface<const IRigVMRuntimeAssetInterface> RigVMAsset;` — `UPROPERTY()`
- L50 _private member_ `EAnimNextSharedVariablesType Type;` — `UPROPERTY()`
- L53 _private member_ `FGuid CachedGuid;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L17 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/AnimNextUnitNode.h` (Internal)


#### class `UAnimNextUnitNode`  
`class UAnimNextUnitNode : public URigVMUnitNode`  
_L14-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigVMUnitNode`
- desc: Implements AnimNext RigVM unit node extensions
- L20 _public function_ `virtual bool HasNonNativePins() const` — Override node functions

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Compilation/AnimNextGetFunctionHeaderCompileContext.h` (Internal)


#### struct `FAnimNextGetFunctionHeaderCompileContext`  
`struct FAnimNextGetFunctionHeaderCompileContext`  
_L14-27_
- desc: Struct holding temporary compilation info during function header population
- L16 _public prototype_ `FAnimNextGetFunctionHeaderCompileContext(FAnimNextRigVMAssetCompileContext& InCompilerContext);`
- L20 _public prototype_ `const TArray<FAnimNextProgrammaticFunctionHeader>& GetFunctionHeaders() const;`
- L21 _public prototype_ `void AddUniqueFunctionHeader(const FAnimNextProgrammaticFunctionHeader& InFunctionHeader);`
- L22 _public prototype_ `const UUAFRigVMAssetEditorData* GetOwningAssetEditorData() const;`
- L26 _protected member_ `FAnimNextRigVMAssetCompileContext& CompilerContext;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Compilation/AnimNextGetGraphCompileContext.h` (Internal)


#### struct `FAnimNextGetGraphCompileContext`  
`struct FAnimNextGetGraphCompileContext`  
_L14-29_
- desc: Struct holding temporary compilation info during function header population
- L16 _public prototype_ `FAnimNextGetGraphCompileContext(FAnimNextRigVMAssetCompileContext& InCompilerContext);`
- L20 _public prototype_ `const TArray<FAnimNextProgrammaticFunctionHeader>& GetFunctionHeaders() const;`
- L22 _public prototype_ `const TArray<URigVMGraph*>& GetProgrammaticGraphs() const;`
- L23 _public prototype_ `TArray<URigVMGraph*>& GetMutableProgrammaticGraphs();`
- L24 _public prototype_ `const UUAFRigVMAssetEditorData* GetOwningAssetEditorData() const;`
- L28 _protected member_ `FAnimNextRigVMAssetCompileContext& CompilerContext;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Compilation/AnimNextGetVariableCompileContext.h` (Internal)


#### struct `FAnimNextGetVariableCompileContext`  
`struct FAnimNextGetVariableCompileContext`  
_L14-31_
- desc: Struct holding temporary compilation info during function header population
- L16 _public prototype_ `FAnimNextGetVariableCompileContext(FAnimNextRigVMAssetCompileContext& InCompilerContext);`
- L20 _public prototype_ `const TArray<FAnimNextProgrammaticFunctionHeader>& GetFunctionHeaders() const;`
- L22 _public prototype_ `const TArray<FAnimNextProgrammaticVariable>& GetProgrammaticVariables() const;`
- L23 _public prototype_ `TArray<FAnimNextProgrammaticVariable>& GetMutableProgrammaticVariables();`
- L24 _public prototype_ `const UUAFRigVMAssetEditorData* GetOwningAssetEditorData() const;`
- L26 _public prototype_ `const FAnimNextRigVMAssetCompileContext& GetAssetCompileContext() const;`
- L30 _protected member_ `FAnimNextRigVMAssetCompileContext& CompilerContext;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Compilation/AnimNextProcessGraphCompileContext.h` (Internal)


#### struct `FAnimNextProcessGraphCompileContext`  
`struct FAnimNextProcessGraphCompileContext`  
_L14-27_
- desc: Struct holding temporary compilation info during function header population
- L16 _public prototype_ `FAnimNextProcessGraphCompileContext(FAnimNextRigVMAssetCompileContext& InCompilerContext);`
- L20 _public prototype_ `const TArray<URigVMGraph*>& GetAllGraphs() const;`
- L21 _public prototype_ `TArray<URigVMGraph*>& GetMutableAllGraphs();`
- L22 _public prototype_ `const UUAFRigVMAssetEditorData* GetOwningAssetEditorData() const;`
- L26 _protected member_ `FAnimNextRigVMAssetCompileContext& CompilerContext;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Compilation/AnimNextProgrammaticFunctionHeader.h` (Internal)


#### struct `FAnimNextProgrammaticFunctionHeader`  
`struct FAnimNextProgrammaticFunctionHeader`  
_L13-19_
- desc: Struct wrapping a RigVM Function header. Also contains some metadata used to drive compilation.
- L16 _public member_ `FRigVMGraphFunctionHeader FunctionHeader;` — RigVM Function Header we are wrapping
- L18 _public prototype_ `bool operator==(const FAnimNextProgrammaticFunctionHeader& Other) const = default;`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Compilation/AnimNextRigVMAssetCompileContext.h` (Internal)


#### struct `FAnimNextRigVMAssetCompileContext`  
`struct FAnimNextRigVMAssetCompileContext`  
_L23-98_
- desc: Struct holding temporary compilation info for a single RigVM asset Note: Sub compile contexts give limited access. But feel free to expand the access of any particular sub context as needed.
- L27 _public function_ `FAnimNextRigVMAssetCompileContext(const UUAFRigVMAssetEditorData* InOwningAssetEditorData) : OwningAssetEditorData(InOwningAssetEditorData)`
- L34 _public function_ `template<typename... ArgTypes> void Error(UObject* Object, FTextFormat Format, ArgTypes... Args) const`
- L40 _public function_ `template<typename... ArgTypes> void Error(FTextFormat Format, ArgTypes... Args) const`
- L46 _public function_ `template<typename... ArgTypes> void Warning(UObject* Object, FTextFormat Format, ArgTypes... Args) const`
- L52 _public function_ `template<typename... ArgTypes> void Warning(FTextFormat Format, ArgTypes... Args) const`
- L58 _public function_ `template<typename... ArgTypes> void Info(UObject* Object, FTextFormat Format, ArgTypes... Args) const`
- L64 _public function_ `template<typename... ArgTypes> void Info(FTextFormat Format, ArgTypes... Args) const`
- L69 _public prototype_ `void Message(TSharedRef<FTokenizedMessage> InMessage) const;`
- L72 _private prototype_ `void Message(EMessageSeverity::Type Severity, UObject* Object, const FText& Message) const;`
- L85 _protected member_ `TArray<FAnimNextProgrammaticFunctionHeader> FunctionHeaders;` — Function Headers we should generate variables / graphs for
- L88 _protected member_ `TArray<FAnimNextProgrammaticVariable> ProgrammaticVariables;` — Programmtic variables generated during this compile
- L91 _protected member_ `TArray<URigVMGraph*> ProgrammaticGraphs;` — Programmtic graphs generated during this compile
- L94 _protected member_ `TArray<URigVMGraph*> AllGraphs;` — All graphs compiled by this RigVM Asset
- L97 _protected member_ `const UUAFRigVMAssetEditorData* OwningAssetEditorData;` — RigVM Asset Editor Data this compile context is designed for. Used to ensure we don't cross contexts.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Entries/AnimNextCategoryEntry.h` (Internal)


#### class `UAnimNextCategoryEntry`  
`class UAnimNextCategoryEntry : public UUAFRigVMAssetEntry`  
_L17-33_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Category")`
- inherits: `UUAFRigVMAssetEntry`
- L26 _private prototype_ `virtual void Initialize(UUAFRigVMAssetEditorData* InEditorData) override;` — UUAFRigVMAssetEntry interface
- L27 _private function_ `virtual FName GetEntryName() const override`
- L28 _private prototype_ `virtual void SetEntryName(FName InName, bool bSetupUndoRedo = true) override;`
- L32 _protected member_ `FName CategoryName;` — `UPROPERTY(VisibleAnywhere, Category = "Category")`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Entries/AnimNextEventGraphEntry.h` (Internal)


#### class `UAnimNextEventGraphEntry`  
`class UAnimNextEventGraphEntry : public UUAFRigVMAssetEntry, public IUAFRigVMGraphInterface`  
_L32-71_
- reflection: `UCLASS(MinimalAPI, Category = "Event Graphs", DisplayName = "Event Graph")`
- inherits: `UUAFRigVMAssetEntry,IUAFRigVMGraphInterface`
- L48 _private function_ `virtual FName GetEntryName() const override` — UUAFRigVMAssetEntry interface
- L49 _private prototype_ `virtual void SetEntryName(FName InName, bool bSetupUndoRedo = true) override;`
- L50 _private prototype_ `virtual FText GetDisplayName() const override;`
- L51 _private prototype_ `virtual FText GetDisplayNameTooltip() const override;`
- L54 _private prototype_ `virtual const FName& GetGraphName() const override;` — IAnimNextRigVMGraphInterface interface
- L55 _private prototype_ `virtual URigVMGraph* GetRigVMGraph() const override;`
- L56 _private prototype_ `virtual URigVMEdGraph* GetEdGraph() const override;`
- L57 _private prototype_ `virtual void SetRigVMGraph(URigVMGraph* InGraph) override;`
- L58 _private prototype_ `virtual void SetEdGraph(URigVMEdGraph* InGraph) override;`
- L62 _private member_ `FName GraphName;` — `UPROPERTY(VisibleAnywhere, Category = "Event Graph")` — The name of the graph
- L66 _private member_ `TObjectPtr<URigVMGraph> Graph;` — `UPROPERTY()` — Graph
- L70 _private member_ `TObjectPtr<UAnimNextEdGraph> EdGraph;` — `UPROPERTY()` — Graph

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)
- L16 _namespace_ `namespace Tests` (scope `UE::UAF`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace UAF` (scope `UE`)
- L26 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Entries/AnimNextRigVMAssetEntry.h` (Internal)


#### class `UUAFRigVMAssetEntry`  
`class UUAFRigVMAssetEntry : public UObject`  
_L26-70_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UObject`
- desc: Base class that defines an entry in a module, e.g. a parameter or a graph
- L31 _public prototype_ `virtual void Initialize(UUAFRigVMAssetEditorData* InEditorData);` — Binds delegates to owning editor data
- L34 _public function_ `virtual void HandleRigVMGraphModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject)` — Allow entries the opportunity to handle RigVM modification events
- L37 _public function_ `virtual FName GetEntryName() const PURE_VIRTUAL(UUAFRigVMAssetEntry::GetEntryName, return NAME_None;)` — Get this entry's name
- L43 _public function_ `virtual FText GetDisplayName() const` — Get the name to be displayed in the UI for this entry
- L46 _public function_ `virtual FText GetDisplayNameTooltip() const` — Get the tooltip to be displayed for the name in the UI for this entry
- L49 _public function_ `void SetHiddenInOutliner(bool bInHide)` — Set whether this entry is hidden in the outliner
- L52 _public function_ `bool IsHiddenInOutliner() const` — Get whether this entry is hidden in the outliner
- L55 _public prototype_ `virtual bool IsAsset() const override;` — UObject interface
- L57 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L58 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L59 _public prototype_ `virtual void PostEditUndo() override;`
- L63 _protected prototype_ `void BroadcastModified(EAnimNextEditorDataNotifType InType);`
- L69 _protected member_ `uint32 bHiddenInOutliner : 1 = false;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)
- L16 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Entries/AnimNextSharedVariablesEntry.h` (Internal)


#### enum `EAnimNextSharedVariablesType`  
`enum class EAnimNextSharedVariablesType : uint8`  
_L37-42_
- reflection: `UENUM()`
- L39 _public enumerator_ `Asset` — reference to shared variable defined in UUAFSharedVariables
- L40 _public enumerator_ `Struct` — Reference to a property of a native struct
- L41 _public enumerator_ `RigVMAsset` — Reference to an external variable defined in a RigVMAsset

#### class `UUAFSharedVariablesEntry`  
`class UUAFSharedVariablesEntry : public UUAFRigVMAssetEntry`  
_L45-131_
- reflection: `UCLASS(MinimalAPI, Category = "Shared Variables", DisplayName = "Shared Variables")`
- inherits: `UUAFRigVMAssetEntry`
- L66 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L67 _private prototype_ `virtual void PostLoad() override;`
- L70 _private prototype_ `virtual void Initialize(UUAFRigVMAssetEditorData* InEditorData) override;` — UUAFRigVMAssetEntry interface
- L71 _private prototype_ `virtual FName GetEntryName() const override;`
- L72 _private function_ `virtual void SetEntryName(FName InName, bool bSetupUndoRedo = true) override`
- L73 _private prototype_ `virtual FText GetDisplayName() const override;`
- L74 _private prototype_ `virtual FText GetDisplayNameTooltip() const override;`
- L77 _private function_ `EAnimNextSharedVariablesType GetType() const` — Get the type of this shared variables entry
- L83 _private prototype_ `void SetAsset(const UUAFSharedVariables* InAsset, bool bSetupUndoRedo = true);` — Set this entry to use an asset (rather than a struct)
- L86 _private prototype_ `void SetRigVMAsset(const IRigVMRuntimeAssetInterface* InRigVMAsset, bool bSetupUndoRedo = true);` — Set this entry to use an asset (rather than a struct)
- L89 _private prototype_ `const UUAFSharedVariables* GetAsset() const;` — Get the asset that this entry represents. If this entry uses a struct, this call will return nullptr
- L92 _private prototype_ `FSoftObjectPath GetObjectPath() const;` — Get the path to the asset/struct path that this entry represents, if any
- L95 _private prototype_ `void SetStruct(const UScriptStruct* InStruct, bool bSetupUndoRedo = true);` — Set this entry to use a struct (rather than an asset)
- L98 _private prototype_ `const UScriptStruct* GetStruct() const;` — Get the struct that this entry represents. If this entry uses an asset, this call will return nullptr
- L100 _private function_ `const TScriptInterface<const IRigVMRuntimeAssetInterface>& GetRigVMAsset() const`
- L103 _private prototype_ `void HandleAssetModified(UUAFRigVMAssetEditorData* InEditorData, EAnimNextEditorDataNotifType InType, UObject* InSubject);` — Recompiles this asset when the linked asset is modified
- L106 _private prototype_ `void HandleAssetRequiresCompilation(TWeakObjectPtr<UUAFRigVMAssetEditorData> WeakEditorData) const;` — Marks this asset as requiring compilation when the linked asset is marked as such
- L110 _private prototype_ `void HandlePatchComplete();` — Recompiles this asset when live coding is run (potentially modifying the struct we reference)
- L115 _private member_ `TObjectPtr<const UUAFSharedVariables> Asset;` — `UPROPERTY(VisibleAnywhere, Category = "Asset")` — The asset whose variables we share
- L119 _private member_ `TScriptInterface<const IRigVMRuntimeAssetInterface> RigVMAsset;` — `UPROPERTY(VisibleAnywhere, Category = "Asset")` — The asset whose variables we share
- L123 _private member_ `FSoftObjectPath ObjectPath;` — `UPROPERTY()` — Soft reference to the asset/struct for error reporting
- L127 _private member_ `TObjectPtr<const UScriptStruct> Struct;` — `UPROPERTY(VisibleAnywhere, Category = "Asset")` — The struct whose variables we use
- L130 _private member_ `EAnimNextSharedVariablesType Type;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace UAF` (scope `UE`)
- L30 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Entries/AnimNextVariableEntry.h` (Internal)


#### class `UAnimNextVariableEntry`  
`class UAnimNextVariableEntry : public UUAFRigVMAssetEntry, public IUAFRigVMVariableInterface, public IUAFRigVMExportInterface`  
_L58-186_
- reflection: `UCLASS(MinimalAPI, Category = "Variables", DisplayName = "Variable")`
- inherits: `UUAFRigVMAssetEntry,IUAFRigVMVariableInterface,IUAFRigVMExportInterface`
- L95 _private prototype_ `UAnimNextVariableEntry();`
- L98 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L99 _private prototype_ `virtual void PostLoad() override;`
- L101 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L105 _private prototype_ `virtual FAnimNextParamType GetExportType() const override;` — IAnimNextRigVMExportInterface interface
- L106 _private prototype_ `virtual FName GetExportName() const override;`
- L107 _private prototype_ `virtual EAnimNextExportAccessSpecifier GetExportAccessSpecifier() const override;`
- L108 _private prototype_ `virtual void SetExportAccessSpecifier(EAnimNextExportAccessSpecifier InAccessSpecifier, bool bSetupUndoRedo = true) override;`
- L111 _private prototype_ `virtual FName GetEntryName() const override;` — UUAFRigVMAssetEntry interface
- L112 _private prototype_ `virtual void SetEntryName(FName InName, bool bSetupUndoRedo = true) override;`
- L113 _private prototype_ `virtual FText GetDisplayName() const override;`
- L114 _private prototype_ `virtual FText GetDisplayNameTooltip() const override;`
- L117 _private prototype_ `virtual FAnimNextParamType GetType() const override;` — IAnimNextRigVMVariableInterface interface
- L118 _private prototype_ `virtual bool SetType(const FAnimNextParamType& InType, bool bSetupUndoRedo = true) override;`
- L119 _private prototype_ `virtual FName GetVariableName() const override;`
- L120 _private prototype_ `virtual void SetVariableName(FName InName, bool bSetupUndoRedo = true) override;`
- L121 _private prototype_ `virtual bool SetDefaultValue(TConstArrayView<uint8> InValue, bool bSetupUndoRedo = true) override;`
- L122 _private prototype_ `virtual bool SetDefaultValueFromString(const FString& InDefaultValue, bool bSetupUndoRedo = true) override;`
- L123 _private prototype_ `virtual const FInstancedPropertyBag& GetPropertyBag() const override;`
- L124 _private prototype_ `virtual bool GetDefaultValue(const FProperty*& OutProperty, TConstArrayView<uint8>& OutValue) const override;`
- L125 _private prototype_ `virtual bool GetDefaultValueString(FString& OutValueString) const override;`
- L126 _private prototype_ `virtual void SetBindingType(UScriptStruct* InBindingTypeStruct, bool bSetupUndoRedo = true) override;`
- L127 _private prototype_ `virtual void SetBinding(TInstancedStruct<FAnimNextVariableBindingData>&& InBinding, bool bSetupUndoRedo = true) override;`
- L128 _private prototype_ `virtual TConstStructView<FAnimNextVariableBindingData> GetBinding() const override;`
- L129 _private prototype_ `virtual FStringView GetVariableCategory() const override;`
- L130 _private prototype_ `virtual void SetVariableCategory(FStringView InCategoryName, bool bSetupUndoRedo = true) override;`
- L131 _private function_ `virtual const FGuid& GetGuid() const override`
- L135 _private function_ `template<typename ValueType> bool SetDefaultValue(const ValueType& InValue, bool bSetupUndoRedo = true)` — Set the default value
- L157 _private member_ `EAnimNextExportAccessSpecifier Access = EAnimNextExportAccessSpecifier::Private;` — `UPROPERTY(EditAnywhere, Category = "Variable")` — Access specifier - whether the variable is visible external to this asset
- L161 _private member_ `FName ParameterName;` — `UPROPERTY(VisibleAnywhere, Category = "Variable")` — Parameter name we reference
- L165 _private member_ `FAnimNextParamType Type = FAnimNextParamType::GetType<bool>();` — `UPROPERTY(EditAnywhere, Category = "Variable")` — The variable's type
- L169 _private member_ `FAnimNextVariableBinding Binding;` — `UPROPERTY(EditAnywhere, Category = "Variable")` — Binding data
- L173 _private member_ `FString Comment;` — `UPROPERTY(EditAnywhere, Category = "Variable", meta=(MultiLine))` — Comment to display in editor
- L177 _private member_ `FString Category;` — `UPROPERTY(EditAnywhere, Category = "Variable")` — Category this variable should be assigned to
- L181 _private member_ `FInstancedPropertyBag DefaultValue;` — `UPROPERTY()` — Property bag holding the default value of the variable
- L185 _private member_ `FGuid Guid;` — `UPROPERTY()` — Stable (unique) Guid used to reference variable without requiring ParameterName

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UAF` (scope `UE`)
- L22 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace UAF` (scope `UE`)
- L41 _namespace_ `namespace Tests` (scope `UE::UAF`)
- L50 _namespace_ `namespace UE`
- L50 _namespace_ `namespace UAF` (scope `UE`)
- L50 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/IAnimNextRigVMExportInterface.h` (Internal)


#### enum `EAnimNextExportAccessSpecifier`  
`enum class EAnimNextExportAccessSpecifier : int32`  
_L11-18_
- reflection: `UENUM()`
- L14 _public enumerator_ `Private` — Export can only be used/referenced in the graph it is declared in
- L17 _public enumerator_ `Public` — Export can be used/referenced in other graphs/contexts (e.g. BP, Verse)

#### class `UUAFRigVMExportInterface`  
`class UUAFRigVMExportInterface : public UInterface`  
_L21-24_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IUAFRigVMExportInterface`  
`class IUAFRigVMExportInterface`  
_L26-42_
- L32 _public prototype_ `virtual FAnimNextParamType GetExportType() const = 0;` — Get the export type
- L35 _public prototype_ `virtual FName GetExportName() const = 0;` — Get the export name (e.g. asset path + entry name)
- L38 _public prototype_ `virtual EAnimNextExportAccessSpecifier GetExportAccessSpecifier() const = 0;` — Get the export access specifier
- L41 _public prototype_ `virtual void SetExportAccessSpecifier(EAnimNextExportAccessSpecifier InAccessSpecifier, bool bSetupUndoRedo = true) = 0;` — Set the export access specifier

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/IAnimNextRigVMGraphInterface.h` (Internal)


#### class `UUAFRigVMGraphInterface`  
`class UUAFRigVMGraphInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IUAFRigVMGraphInterface`  
`class IUAFRigVMGraphInterface`  
_L18-40_
- desc: Interface for entries that contain a RigVM graph
- L24 _public prototype_ `virtual const FName& GetGraphName() const = 0;` — Get the AnimNext graph name
- L27 _public prototype_ `virtual URigVMGraph* GetRigVMGraph() const = 0;` — Get the RigVM graph
- L30 _public prototype_ `virtual URigVMEdGraph* GetEdGraph() const = 0;` — Get the Editor graph
- L36 _private prototype_ `virtual void SetRigVMGraph(URigVMGraph* InGraph) = 0;` — Set the RigVM graph
- L39 _private prototype_ `virtual void SetEdGraph(URigVMEdGraph* InGraph) = 0;` — Get the Editor graph

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Module/AnimNextEventGraphSchema.h` (Internal)


#### class `UAnimNextEventGraphSchema`  
`class UAnimNextEventGraphSchema : public UUAFRigVMAssetSchema`  
_L10-16_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUAFRigVMAssetSchema`
- L15 _private prototype_ `virtual bool SupportsUnitFunction_NoLock(URigVMController* InController, const FRigVMFunction* InUnitFunction, FRigVMRegistryHandle& InRegistry) const override;` — URigVMSchema interface

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Module/AnimNextModule_EditorData.h` (Internal)


#### class `UUAFSystem_EditorData`  
`class UUAFSystem_EditorData : public UUAFSharedVariables_EditorData`  
_L34-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUAFSharedVariables_EditorData`
- desc: Editor data for UAF systems
- L53 _public member_ `static inline FName DefaultEventGraphName = TEXT("Eve`
- L57 _private function_ `virtual UScriptStruct* GetExecuteContextStruct() const override` — UUAFRigVMAssetEditorData interface
- L58 _private prototype_ `virtual TConstArrayView<TSubclassOf<UUAFRigVMAssetEntry>> GetEntryClasses() const override;`
- L59 _private prototype_ `virtual void OnPreCompileAsset(FRigVMCompileSettings& InSettings) override;`
- L60 _private prototype_ `virtual void OnPreCompileGetProgrammaticGraphs(const FRigVMCompileSettings& InSettings, FAnimNextGetGraphCompileContext& OutCompileContext) override;`
- L61 _private prototype_ `virtual void OnPreCompileProcessGraphs(const FRigVMCompileSettings& InSettings, FAnimNextProcessGraphCompileContext& OutCompileContext) override;`
- L62 _private prototype_ `virtual void CustomizeNewAssetEntry(UUAFRigVMAssetEntry* InNewEntry) const override;`
- L66 _private member_ `TArray<TObjectPtr<UAnimNextEdGraph>> Graphs_DEPRECATED;` — `UPROPERTY()`
- L70 _private member_ `TArray<TInstancedStruct<FRigVMTrait_ModuleEventDependency>> Dependencies;` — `UPROPERTY(EditAnywhere, Category = "Dependencies", NoClear, meta=(ExcludeBaseStruct))` — All dependencies that should be set up when the module initializes

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace UAF` (scope `UE`)
- L25 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/UncookedOnlyUtils.h` (Internal)


#### struct `UE::UAF::UncookedOnly::FUtils`  
`struct FUtils`  
_L58-267_
- L60 _public prototype_ `static void CompileVariables(const FRigVMCompileSettings& InSettings, UUAFRigVMAsset* InAsset, FAnimNextGetVariableCompileContext& OutCompileContext);`
- L62 _public prototype_ `static FInstancedPropertyBag MakePropertyBagForEditorData(const UUAFRigVMAssetEditorData* InEditorData, const FAnimNextGetVariableCompileContext& InCompileContext);`
- L64 _public prototype_ `static void CompileVariableBindings(const FRigVMCompileSettings& InSettings, UUAFRigVMAsset* InAsset, TArray<URigVMGraph*>& OutGraphs);`
- L66 _public prototype_ `static void RecreateVM(UUAFRigVMAsset* InAsset);`
- L69 _public prototype_ `static UUAFRigVMAsset* GetAsset(UUAFRigVMAssetEditorData* InEditorData);` — Get the corresponding asset from an asset's editor data (casts the outer appropriately)
- L72 _public function_ `template<typename AssetType, typename EditorDataType> static AssetType* GetAsset(EditorDataType* InEditorData)`
- L79 _public prototype_ `static UUAFRigVMAssetEditorData* GetEditorData(UUAFRigVMAsset* InAsset);` — Get the corresponding editor data from an asset (casts the editor data appropriately)
- L80 _public prototype_ `static const UUAFRigVMAssetEditorData* GetEditorData(const UUAFRigVMAsset* InAsset);`
- L83 _public function_ `template<typename EditorDataType, typename AssetType> static EditorDataType* GetEditorData(AssetType* InAsset)`
- L93 _public prototype_ `static FAnimNextParamType GetParamTypeFromPinType(const FEdGraphPinType& InPinType);` — Get an AnimNext parameter type from an FEdGraphPinType. Note that the returned handle may not be valid, so should be checked using IsValid() before use.
- L99 _public prototype_ `static FEdGraphPinType GetPinTypeFromParamType(const FAnimNextParamType& InParamType);` — Get an FEdGraphPinType from an AnimNext parameter type/handle. Note that the returned pin type may not be valid.
- L105 _public prototype_ `static FRigVMTemplateArgumentType GetRigVMArgTypeFromParamType(const FAnimNextParamType& InParamType);` — Get an FRigVMTemplateArgumentType from an AnimNext parameter type/handle. Note that the returned pin type may not be valid.
- L108 _public prototype_ `static void SetupEventGraph(URigVMController* InController, UScriptStruct* InEventStruct, FName InEventName = NAME_None, bool bPrintPythonCommand = false);` — Set up a simple event graph
- L111 _public prototype_ `static bool GetExportedVariablesForAsset(const FAssetData& InAsset, FAnimNextAssetRegistryExports& OutExports);` — Gets the variables that are exported to the asset registry for an asset
- L114 _public prototype_ `static bool GetExportedVariablesFromAssetRegistry(TMap<FAssetData, FAnimNextAssetRegistryExports>& OutExports);` — Gets all the variables that are exported to the asset registry
- L117 _public function_ `template<typename ExportDataType> static bool GetExportsOfTypeForAsset(const FAssetData& InAsset, FAnimNextAssetRegistryExports& OutExports)`
- L139 _public function_ `template<typename ExportDataType> static bool GetExportsOfTypeFromAssetRegistry(TMap<FAssetData, FAnimNextAssetRegistryExports>& OutExports)`
- L166 _public prototype_ `static void GetAssetVariableExports(const UUAFRigVMAssetEditorData* EditorData, FAnimNextAssetRegistryExports& OutExports, FAssetRegistryTagsContext Context);`
- L169 _public prototype_ `static bool GetExportedFunctionsFromAssetRegistry(FName Tag, TMap<FAssetData, FRigVMGraphFunctionHeaderArray>& OutExports);` — Gets all the functions that are exported to the asset registry for the specified Tag
- L172 _public prototype_ `static void GetAssetFunctions(const UUAFRigVMAssetEditorData* InEditorData, FRigVMGraphFunctionHeaderArray& OutExports);` — Gets the exported public functions that are used by a RigVM asset
- L175 _public prototype_ `static void GetAssetPrivateFunctions(const UUAFRigVMAssetEditorData* InEditorData, FRigVMGraphFunctionHeaderArray& OutExports);` — Gets the non-exported private functions that are used by a RigVM asset
- L179 _public prototype_ `static void GetAssetWorkspaceExports(const UUAFRigVMAssetEditorData* EditorData, FWorkspaceOutlinerItemExports& OutExports, FAssetRegistryTagsContext Context);` — Gets the asset-registry information needed for representing the contained data into the Workspace Outliner Note: We pass parent as index to avoid the ref from being invalidated due to realloc as the export array grows recursively
- L184 _public prototype_ `static FAnimNextParamType FindVariableType(const FAnimNextVariableReference& InVariableReference);` — Attempts to determine the type from a variable name & asset/struct path If the name cannot be found, the returned type will be invalid Note that this is expensive and can query the asset registry
- L185 _public prototype_ `static FAnimNextParamType FindVariableType(const FAnimNextSoftVariableReference& InSoftVariableReference);`
- L188 _public prototype_ `static const FText& GetFunctionLibraryDisplayName();` — Returns an user friendly name for the Function Library
- L191 _public prototype_ `static void OpenProgrammaticGraphs(UUAFRigVMAssetEditorData* InEditorData, const TArray<URigVMGraph*>& ProgrammaticGraphs);`
- L195 _public prototype_ `static FString MakeFunctionWrapperVariableName(FName InFunctionName, FName InVariableName);` — Make a variable name that we use as a wrapper for a function param or return
- L198 _public prototype_ `static FString MakeFunctionWrapperEventName(FName InFunctionName);` — Make an event name that we use as a wrapper to call RigVM functions
- L201 _public prototype_ `static void GetVariableNames(UUAFRigVMAssetEditorData* InEditorData, TArray<FName>& OutVariableNames, bool bRecursive = true);` — Returns all unique variable names found within provided editor data, optionally recursing into SharedVariable entries
- L204 _public prototype_ `static FName GetValidVariableName(UUAFRigVMAssetEditorData* InEditorData, FName InBaseName);` — Return valid variable FName within the context of the provided EditorData (recurses into SharedVariable entries as well)
- L207 _public prototype_ `static FName GetValidVariableName(FName InBaseName, const TArrayView<FName> ExistingNames);` — Return valid variable FName within the context of the provided set of existing variable names
- L210 _public prototype_ `static void DeleteVariable(UAnimNextVariableEntry* VariableEntry, bool bSetupUndoRedo = true, bool bPrintPythonCommands = true);` — Deletes the provided variable entry from its editor data, removing any references across the project its assets
- L213 _public prototype_ `static void RenameVariable(UAnimNextVariableEntry* VariableEntry, const FName NewName, bool bSetupUndoRedo = true, bool bPrintPythonCommands = true);` — Deletes the provided variable entry from its editor data, renaming any references across the project its assets to reference it by the NewName
- L216 _public prototype_ `static UAnimNextVariableEntry* MoveVariableToAsset(UAnimNextVariableEntry* VariableEntry, UUAFRigVMAsset* NewOuter, bool bSetupUndoRedo = true, bool bPrintPythonCommands = true);` — Moves the provided variable entry from its editor data to the NewOuter, replacing any references across the project its assets to reference it by its new outer asset
- L219 _public prototype_ `static void SetVariableType(UAnimNextVariableEntry* VariableEntry, const FAnimNextParamType NewType, bool bSetupUndoRedo = true, bool bPrintPythonCommands = true);` — Changes the provided variable entry its data type, replacing any references across the project to reference using its new data type
- L222 _public prototype_ `static void ReplaceVariableReferences(UUAFRigVMAssetEditorData* InEditorData, const FAnimNextSoftVariableReference& ReferenceToFind, const FAnimNextSoftVariableReference& ReferenceToReplaceWith, bool bForceReplace = false, bool bSetupUndoRedo = true, bool bPrintPythonCommands = true);` — Replaces the provided variable reference with ReferenceToReplaceWith within the context of InEditorData
- L225 _public prototype_ `static void ReplaceVariableReferencesAcrossProject(const FAnimNextSoftVariableReference& ReferenceToFind, const FAnimNextSoftVariableReference& ReferenceToReplaceWith, bool bForceLoadAssets = false, bool bForceReplace = false, bool bSetupUndoRedo = true, bool bPrintPythonCommands = true);` — Replaces the provided variable reference with ReferenceToReplaceWith within the context of the project
- L228 _public prototype_ `static FGuid GenerateScriptStructPropertyGUID(const FProperty* Property);` — Generates a deterministic GUID provided a UStruct FProperty entry
- L231 _public prototype_ `static bool CanAddSharedVariablesReference(UUAFRigVMAssetEditorData* InEditorData, const UUAFSharedVariables* InSharedVariables, FString* OutErrorMessage = nullptr);` — Returns whether or not it is valid to add InSharedVariables to InEditorData, and if not OutErrorMessage will contain the reasoning
- L234 _public prototype_ `static bool RemoveSharedVariablesReference(UUAFRigVMAssetEditorData* EditorData, const FSoftObjectPath& SharedVariablesPath);` — Removes a SharedVariable reference from the provided EditorData, and ensures that any references to variables within the SharedVariables are replaced
- L237 _public prototype_ `static FWorkspaceOutlinerItemExport MakeFunctionExport(const URigVMLibraryNode* FunctionNode, const FWorkspaceOutlinerItemExport& ParentExport);` — Generate a (function) workspace export for the provided URigVMLibraryNode
- L240 _public prototype_ `static FWorkspaceOutlinerItemExport MakeCollapsedGraphExport(const URigVMCollapseNode* CollapseNode, const FWorkspaceOutlinerItemExport& ParentExport);` — Generate a (collapse graph) workspace export for the provided URigVMCollapseNode
- L243 _public prototype_ `static FWorkspaceOutlinerItemExport MakeAssetReferenceExport(const FSoftObjectPath& ReferencedAssetPath, const FWorkspaceOutlinerItemExport& ParentExport, bool bShouldExpand = true);` — Generate a (asset reference) workspace export for the provided asset path
- L245 _public prototype_ `static void GetExternalVariables(const UUAFRigVMAssetEditorData* EditorData, TArray<FRigVMExternalVariable>& OutVariables);`
- L248 _public prototype_ `static FAnimNextVariableReference ParseVariableReferenceFromPin(const UEdGraphPin* InPin);` — Parse a FAnimNextVariableReference from a pin's default value. Returns the parsed reference (may be None/invalid).
- L251 _public prototype_ `static void PreloadVariableReferenceAssets(const UEdGraphPin* InVariablePin);` — Preload assets referenced by a variable reference pin. Call from PreloadRequiredAssets.
- L254 _private prototype_ `static void GetInternalVariables(const UUAFRigVMAssetEditorData* EditorData, TArray<FRigVMExternalVariable>& OutVariables);`
- L256 _private prototype_ `static void CompileVariableBindingsInternal(const FRigVMCompileSettings& InSettings, UUAFRigVMAsset* InAsset, TArray<URigVMGraph*>& OutGraphs, bool bInThreadSafe);`
- L258 _private prototype_ `static void GetSubGraphWorkspaceExportsRecursive(const UUAFRigVMAssetEditorData* EditorData, FWorkspaceOutlinerItemExports& OutExports, const FWorkspaceOutlinerItemExport& RootExport, int32 ParentExportIndex, URigVMEdGraph* RigVMEdGraph, FAssetRegistryTagsContext Context);`
- L261 _private prototype_ `static void GetAssetVariableExports(const UUAFRigVMAssetEditorData* EditorData, TSet<FAnimNextExport>& OutExports, FAssetRegistryTagsContext Context, EAnimNextExportedVariableFlags InFlags = EAnimNextExportedVariableFlags::NoFlags);` — Gets the exported variables that are used by a RigVM asset
- L263 _private prototype_ `static void GetStructVariableExports(const UScriptStruct* Struct, TSet<FAnimNextExport>& OutExports);`
- L264 _private prototype_ `static void GetSubGraphVariableExportsRecursive(const URigVMEdGraph* RigVMEdGraph, TSet<FAnimNextExport>& OutExports);`
- L265 _private prototype_ `static void ProcessPinAssetReferences(const URigVMPin* InPin, FWorkspaceOutlinerItemExports& OutExports, const FWorkspaceOutlinerItemExport& RootExport, int32 ParentExportIndex);`
- L266 _private prototype_ `static void RetrieveReferencedSharedVariableSources(const UUAFRigVMAsset* InAsset, TSet<const UUAFRigVMAsset*>& ReferencedVariableAssets, TSet<const UScriptStruct*>& ReferencedVariableStructs, TSet<TScriptInterface<const IRigVMRuntimeAssetInterface>>& ReferencedVariableRigVMAssets);`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`
- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace UAF` (scope `UE`)
- L49 _variable_ `static const FLazyName AnimNextPublicGraphFunctionsExportsRegistryTag = TEXT("Ani` (scope `UE::UAF`)
- L50 _variable_ `static const FLazyName ControlRigAssetPublicGraphFunctionsExportsRegistryTag = TEXT("Pub` (scope `UE::UAF`)
- L53 _namespace_ `namespace UE`
- L53 _namespace_ `namespace UAF` (scope `UE`)
- L53 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L56 _externvar_ `extern TAutoConsoleVariable<bool> CVarDumpProgrammaticGraphs;` (scope `UE::UAF::UncookedOnly`)
- L74 _typedef_ `using NonConstEditorDataType = std::remove_const_t<EditorDataType>;` (scope `UE::UAF::UncookedOnly::FUtils::GetAsset`)
- L85 _typedef_ `using NonConstAssetType = std::remove_const_t<AssetType>;` (scope `UE::UAF::UncookedOnly::FUtils::GetEditorData`)
- L126 _function_ `` (scope `UE::UAF::UncookedOnly::FUtils::GetExportsOfTypeForAsset`)
- L153 _function_ `` (scope `UE::UAF::UncookedOnly::FUtils::GetExportsOfTypeFromAssetRegistry`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Variables/AnimNextSharedVariables_EditorData.h` (Internal)


#### class `UUAFSharedVariables_EditorData`  
`class UUAFSharedVariables_EditorData : public UUAFRigVMAssetEditorData`  
_L21-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUAFRigVMAssetEditorData`
- desc: Editor data for UAF shared variables
- L27 _protected function_ `virtual UScriptStruct* GetExecuteContextStruct() const override` — UUAFRigVMAssetEditorData interface
- L28 _protected prototype_ `virtual TConstArrayView<TSubclassOf<UUAFRigVMAssetEntry>> GetEntryClasses() const override;`
- L29 _protected prototype_ `virtual void CustomizeNewAssetEntry(UUAFRigVMAssetEntry* InNewEntry) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L14 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Variables/AnimNextUniversalObjectLocatorBindingData.h` (Internal)


#### enum `FAnimNextUniversalObjectLocatorBindingType`  
`enum class FAnimNextUniversalObjectLocatorBindingType : uint8`  
_L13-23_
- reflection: `UENUM()`
- desc: Type of binding
- L16 _public enumerator_ `UOL` — Binding resolves via the result of the UOL (only valid for object type bindings)
- L18 _public enumerator_ `Property` — Binding resolves via resolving a property on the UOL's resolved object
- L20 _public enumerator_ `Function` — Binding resolves via calling a function on the UOL's resolved object
- L22 _public enumerator_ `HoistedFunction` — Binding resolves via calling a hoisted function on a BP function library with the UOL's resolved object

#### struct `FAnimNextUniversalObjectLocatorBindingData`  
`struct FAnimNextUniversalObjectLocatorBindingData : public FAnimNextVariableBindingData`  
_L27-56_
- reflection: `USTRUCT(DisplayName = "Universal Object Locator")`
- inherits: `FAnimNextVariableBindingData`
- desc: Allows binding of module variables to gameplay data via Universal Object Locators
- L33 _public member_ `TFieldPath<FProperty> Property;` — `UPROPERTY(EditAnywhere, Category = "Binding")` — Property to use (if a property)
- L37 _public member_ `TSoftObjectPtr<UFunction> Function;` — `UPROPERTY(EditAnywhere, Category = "Binding")` — Function to use (if a function)
- L41 _public member_ `FUniversalObjectLocator Locator;` — `UPROPERTY(EditAnywhere, Category = "Binding", meta = (LocatorContext="UAFContext"))` — Object locator
- L44 _public member_ `FAnimNextUniversalObjectLocatorBindingType Type = FAnimNextUniversalObjectLocatorBindingType::Property;` — `UPROPERTY(EditAnywhere, Category = "Binding")`
- L47 _public function_ `virtual bool IsValid() const override` — FAnimNextVariableBindingData interface
- L54 _public prototype_ `virtual bool IsThreadSafe() const override;` — Check if this binding data is safe to execute on a worker thread

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Variables/K2Node_AnimNextComponentSetVariable.h` (Internal)


#### class `UK2Node_AnimNextComponentSetVariable`  
`class UK2Node_AnimNextComponentSetVariable : public UK2Node_CallFunction`  
_L10-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction`
- desc: A custom node that supports SetVariable functionality
- L15 _public prototype_ `UK2Node_AnimNextComponentSetVariable();`
- L19 _private prototype_ `virtual void ReconstructNode() override;` — //~ Begin UEdGraphNode Interface.
- L20 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L21 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L25 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;`
- L26 _private prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L27 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L30 _private prototype_ `void CachePinType();`
- L31 _private prototype_ `void PropagateCachedTypeToPin();`
- L35 _private member_ `FEdGraphPinType CachedPinType;` — `UPROPERTY()` — Cached type of the pin used for regenerating after wildcard is reconstructed

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Variables/K2Node_UAFComponentGetVariable.h` (Internal)


#### class `UK2Node_UAFComponentGetVariable`  
`class UK2Node_UAFComponentGetVariable : public UK2Node_CallFunction`  
_L10-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction`
- L15 _public prototype_ `UK2Node_UAFComponentGetVariable();`
- L19 _private prototype_ `virtual void ReconstructNode() override;` — //~ Begin UEdGraphNode Interface.
- L20 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L24 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;`
- L25 _private prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L26 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L29 _private prototype_ `void CachePinType();`
- L30 _private prototype_ `void PropagateCachedTypeToPin();`
- L34 _private member_ `FEdGraphPinType CachedPinType;` — `UPROPERTY()` — Cached type of the pin used for regenerating after wildcard is reconstructed

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Internal/Variables/K2Node_UAFComponentSetInputBinding.h` (Internal)


#### class `UK2Node_UAFComponentSetInputBinding`  
`class UK2Node_UAFComponentSetInputBinding : public UK2Node_CallFunction`  
_L10-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction`
- desc: A custom node that supports setting dynamic input bindings on UAF components, restricted to FValueBundle variables
- L15 _public prototype_ `UK2Node_UAFComponentSetInputBinding();`
- L19 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L23 _private prototype_ `virtual FString GetPinMetaData(FName InPinName, FName InKey) override;`
- L24 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;`
- L25 _private prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L26 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L29 _private member_ `static const FName VariablePinName;`
- L30 _private member_ `static const FName ComponentPinName;`
- L31 _private member_ `static const TArray<const UClass*> AllowedComponentClasses;`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Private/AnimNextUncookedOnlyModule.h` (Private)


#### class `UE::UAF::UncookedOnly::FModule`  
`class FModule : public IAnimNextUncookedOnlyModule`  
_L16-38_
- inherits: `IAnimNextUncookedOnlyModule`
- L20 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L21 _private prototype_ `virtual void ShutdownModule() override;`
- L24 _private prototype_ `virtual void RegisterVariableBindingType(FName InStructName, TSharedPtr<IVariableBindingType> InType) override;` — IAnimNextUncookedOnlyModule interface
- L25 _private prototype_ `virtual void UnregisterVariableBindingType(FName InStructName) override;`
- L26 _private prototype_ `virtual TSharedPtr<IVariableBindingType> FindVariableBindingType(const UScriptStruct* InInstanceIdStruct) const override;`
- L28 _private prototype_ `virtual FGuid GetVariableGuidByName(const FName InName, const UObject* InObject) const override;`
- L29 _private prototype_ `virtual FName GetVariableNameByGuid(const FGuid InGuid, const UObject* InObject) const override;`
- L31 _private prototype_ `virtual void GetExternalVariablesForAsset(const UUAFRigVMAsset* InAsset, TArray<FRigVMExternalVariable>& OutVariables) const override;`
- L32 _private prototype_ `virtual bool DoesAssetVariablesRequireCompilation(const UUAFRigVMAsset* InAsset) const override;`
- L35 _private member_ `TMap<FName, TSharedPtr<IVariableBindingType>> VariableBindingTypes;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Private/Variables/ClassProxy.h` (Private)


#### enum `UE::UAF::UncookedOnly::EClassProxyParameterAccessType`  
`enum class EClassProxyParameterAccessType : int32`  
_L11-21_
- L14 _public enumerator_ `Property` — Access via FProperty
- L17 _public enumerator_ `AccessorFunction` — Access via UFunction with accessor signature Val = Obj.Func()
- L20 _public enumerator_ `HoistedFunction` — Access via UFunction with hoisted signature Val = Func(Obj)

#### struct `UE::UAF::UncookedOnly::FClassProxyParameter`  
`struct FClassProxyParameter`  
_L24-52_
- desc: Cached info about how a class property or function maps to a parameter
- L27 _public member_ `FName ParameterName;` — The parameter name that this proxy corresponds to
- L30 _public member_ `TWeakObjectPtr<UFunction> Function;` — The function to call to get this parameter
- L34 _public member_ `TFieldPath<FProperty> Property;` — The property to copy to get this parameter TFieldPath to accomodate potential reinstancing
- L37 _public member_ `FAnimNextParamType Type;` — The type of the property
- L40 _public member_ `EClassProxyParameterAccessType AccessType;` — How this parameter is accessed
- L44 _public member_ `FText DisplayName;` — Name to display in editor
- L47 _public member_ `FText Tooltip;` — Tooltip to display in editor
- L50 _public member_ `bool bThreadSafe = false;` — Whether this parameter is safe to access on worker threads

#### struct `UE::UAF::UncookedOnly::FClassProxy`  
`struct FClassProxy`  
_L55-78_
- desc: Proxy struct used to hold data about a kind of UClass to cache data for
- L57 _public prototype_ `explicit FClassProxy(const UClass* InClass);`
- L60 _public prototype_ `void Refresh(const UClass* InClass);` — Refresh the cached class info
- L63 _public member_ `TWeakObjectPtr<const UClass> Class;` — The class that this proxy wraps
- L66 _public member_ `TArray<FClassProxyParameter> Parameters;` — Cache of properties, fetched from Class
- L69 _public member_ `TMap<FName, int32> ParameterNameMap;` — Map of parameter name to index in Parameters array
- L73 _public member_ `bool bHasThreadSafeParameters = false;` — Whether any parameters are safe to access on worker threads
- L76 _public member_ `bool bHasNonThreadSafeParameters = true;` — Whether any parameters are not safe to access on worker threads

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Private/Variables/UniversalObjectLocatorBindingType.h` (Private)


#### class `UE::UAF::UncookedOnly::FUniversalObjectLocatorBindingType`  
`class FUniversalObjectLocatorBindingType : public IVariableBindingType`  
_L17-28_
- inherits: `IVariableBindingType`
- desc: Provides information about object proxy parameter sources
- L21 _private prototype_ `virtual TSharedRef<SWidget> CreateEditWidget(const TSharedRef<IPropertyHandle>& InPropertyHandle, const FAnimNextParamType& InType) const override;` — IVariableBindingType interface
- L22 _private prototype_ `virtual FText GetDisplayText(TConstStructView<FAnimNextVariableBindingData> InBindingData) const override;`
- L23 _private prototype_ `virtual FText GetTooltipText(TConstStructView<FAnimNextVariableBindingData> InBindingData) const override;`
- L24 _private prototype_ `virtual bool Validate(TConstStructView<FAnimNextVariableBindingData> InBindingData, FText& OutError) const override;`
- L25 _private prototype_ `virtual void BuildBindingGraphFragment(const FRigVMCompileSettings& InSettings, const FBindingGraphFragmentArgs& InArgs, URigVMPin*& OutExecTail, FVector2D& OutLocation) const override;`
- L27 _private prototype_ `static const UClass* GetClass(TConstStructView<FAnimNextVariableBindingData> InBindingData);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Public/AnimNextExports.h` (Public)


#### enum `EAnimNextExportedVariableFlags`  
`enum class EAnimNextExportedVariableFlags : uint32`  
_L17-26_
- reflection: `UENUM()`
- L19 _public enumerator_ `NoFlags = 0x0`
- L20 _public enumerator_ `Public = 0x1`
- L21 _public enumerator_ `Read = 0x02`
- L22 _public enumerator_ `Write = 0x04`
- L23 _public enumerator_ `Declared = 0x08`
- L24 _public enumerator_ `Referenced = 0x10`
- L25 _public enumerator_ `Max`

#### struct `FAnimNextExportData`  
`struct FAnimNextExportData`  
_L31-36_
- reflection: `USTRUCT()`
- L35 _public prototype_ `FAnimNextExportData() = default;`

#### struct `FAnimNextExport`  
`struct FAnimNextExport`  
_L39-72_
- reflection: `USTRUCT()`
- L43 _public prototype_ `FAnimNextExport() = default;`
- L46 _public member_ `FName Identifier;` — `UPROPERTY()`
- L49 _public member_ `TInstancedStruct<FAnimNextExportData> Data;` — `UPROPERTY()`
- L51 _public function_ `bool operator==(const FAnimNextExport& Other) const`
- L64 _public function_ `template<typename ItemDataType, typename... TArgs> static FAnimNextExport MakeExport(const FName& InIdentifier, TArgs&&... InArgs)`

#### struct `FAnimNextVariableReferenceData`  
`struct FAnimNextVariableReferenceData : public FAnimNextExportData`  
_L75-93_
- reflection: `USTRUCT()`
- inherits: `FAnimNextExportData`
- L79 _public prototype_ `FAnimNextVariableReferenceData() = default;`
- L80 _public function_ `FAnimNextVariableReferenceData(const FName& InGraphName, FStringView InNodePath, FStringView InPinPath, EAnimNextExportedVariableFlags InFlags) : GraphName(InGraphName), NodePath(InNodePath), PinPath(InPinPath), Flags(static_cast<uint32>(InFlags))`
- L83 _public member_ `FName GraphName;` — `UPROPERTY()`
- L86 _public member_ `FString NodePath;` — `UPROPERTY()`
- L89 _public member_ `FString PinPath;` — `UPROPERTY()`
- L92 _public member_ `uint32 Flags = static_cast<uint32>(EAnimNextExportedVariableFlags::NoFlags);` — `UPROPERTY()`

#### struct `FAnimNextVariableDeclarationData`  
`struct FAnimNextVariableDeclarationData : public FAnimNextExportData`  
_L96-111_
- reflection: `USTRUCT()`
- inherits: `FAnimNextExportData`
- L100 _public prototype_ `FAnimNextVariableDeclarationData() = default;`
- L101 _public function_ `FAnimNextVariableDeclarationData(const FAnimNextParamType& InType, const FGuid& InGuid, const EAnimNextExportedVariableFlags& InFlags) : Type(InType), Guid(InGuid), Flags(static_cast<uint32>(InFlags))`
- L104 _public member_ `FAnimNextParamType Type;` — `UPROPERTY()`
- L107 _public member_ `FGuid Guid;` — `UPROPERTY()`
- L110 _public member_ `uint32 Flags = static_cast<uint32>(EAnimNextExportedVariableFlags::NoFlags);` — `UPROPERTY()`

#### struct `FAnimNextManifestNodeData`  
`struct FAnimNextManifestNodeData : public FAnimNextExportData`  
_L114-147_
- reflection: `USTRUCT()`
- inherits: `FAnimNextExportData`
- L118 _public prototype_ `FAnimNextManifestNodeData() = default;`
- L120 _public function_ `FAnimNextManifestNodeData(const TObjectPtr<URigVMGraph>& InModelGraph, const FString& InNodeName, const FString& InNodeCategory, const FString& InMenuDesc, const FString& InToolTip) : ModelGraph(FSoftObjectPath::ConstructFromObject(InModelGraph)) , NodeName(InNodeName) , NodeCategory(InNodeCategory) , MenuDesc(InMenuDesc) , ToolTip(InToolTip)`
- L128 _public function_ `bool operator==(const FAnimNextManifestNodeData& Other) const`
- L134 _public member_ `FSoftObjectPath ModelGraph;` — `UPROPERTY()`
- L137 _public member_ `FString NodeName;` — `UPROPERTY()`
- L140 _public member_ `FString NodeCategory;` — `UPROPERTY()`
- L143 _public member_ `FString MenuDesc;` — `UPROPERTY()`
- L146 _public member_ `FString ToolTip;` — `UPROPERTY()`

#### struct `FAnimNextAssetRegistryExports`  
`struct FAnimNextAssetRegistryExports`  
_L150-194_
- reflection: `USTRUCT()`
- L154 _public prototype_ `FAnimNextAssetRegistryExports() = default;`
- L157 _public member_ `TArray<FAnimNextExport> Exports;` — `UPROPERTY()`
- L160 _public function_ `template<typename ExportType> void ForEachExportOfType(TFunctionRef<bool(const FName&, const ExportType&)> FunctionRef)`
- L178 _public function_ `template<typename ExportType> void ForEachExportOfType(TFunctionRef<bool(const FName&, ExportType&)> FunctionRef)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L13 _variable_ `static const FLazyName ExportsAnimNextAssetRegistryTag = TEXT("Ani` (scope `UE::UAF`)
- L58 _function_ `friend uint32 GetTypeHash(const FAnimNextExport& Entry)`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Public/IAnimNextUncookedOnlyModule.h` (Public)


#### class `UE::UAF::UncookedOnly::IAnimNextUncookedOnlyModule`  
`class IAnimNextUncookedOnlyModule : public IModuleInterface`  
_L22-60_
- inherits: `IModuleInterface`
- L28 _public prototype_ `virtual void RegisterVariableBindingType(FName InStructName, TSharedPtr<IVariableBindingType> InType) = 0;` — Register a variable binding type, used to query information and process variable bindings @param   InStructName     The full path name of the struct type for this variable binding's data (must be a child struct of FAnimNextVariableBindingData) @param   InType           The type to register
- L32 _public prototype_ `virtual void UnregisterVariableBindingType(FName InStructName) = 0;` — Unregister a variable binding type previously passed to RegisterVariableBindingType @param   InStructName     The full path name of the struct type for this variable binding's data
- L36 _public prototype_ `virtual TSharedPtr<IVariableBindingType> FindVariableBindingType(const UScriptStruct* InInstanceIdStruct) const = 0;` — Find a variable binding type previously passed to RegisterVariableBindingType @param   InStruct         The struct type for this variable binding's data (must be a child struct of FAnimNextVariableBindingData)
- L42 _public prototype_ `virtual FGuid GetVariableGuidByName(const FName InName, const UObject* InObject) const = 0;` — Try and retrieve a valid FGuid representing the provided variable (by name) within the source object @param	InName			Name of the variable to retrieve the FGuid for @param	InObject		Object, supposed to be, containing the variable (UScriptStruct, UUAFRigVMAsset or UUAFRigVMAssetEditorData)
- L47 _public prototype_ `virtual FName GetVariableNameByGuid(const FGuid InGuid, const UObject* InObject) const = 0;` — @param	InGuid			FGuid of the variable to retrieve the FName for @param	InObject		Object, supposed to be, containing the variable (UScriptStruct, UUAFRigVMAsset or UUAFRigVMAssetEditorData)
- L52 _public prototype_ `virtual void GetExternalVariablesForAsset(const UUAFRigVMAsset* InAsset, TArray<FRigVMExternalVariable>& OutVariables) const = 0;` — Try and retrieve all local and referenced (through shared variable asset/struct(s)) variables for provided asset @param	InAsset			Asset to retrieve variables for @param	OutVariables	Output array of (referenced) external variables
- L56 _public prototype_ `virtual bool DoesAssetVariablesRequireCompilation(const UUAFRigVMAsset* InAsset) const = 0;` — Whether an Asset its compiled data is out-of-date, indicating it should not be relied upon @param	InAsset			Asset to check for
- L59 _public function_ `static IAnimNextUncookedOnlyModule& Get()`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L14 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Public/UAFCompilationScope.h` (Public)


#### struct `UE::UAF::UncookedOnly::Compilation`  
`struct Compilation`  
_L15-21_
- L18 _public prototype_ `static void RequestAssetCompilation(UUAFRigVMAsset* InAsset);` — Request to synchronously compile the asset
- L20 _public prototype_ `static void RequestAssetCompilation(TConstArrayView<UUAFRigVMAsset*> InAssets);` — Request to synchronously compile a set of assets

#### class `UE::UAF::UncookedOnly::FCompilationScope`  
`class FCompilationScope`  
_L25-49_
- desc: RAII helper for scoping compilation batches The re-allocation of compiled assets and their dependencies is deferred until the outermost scope exits.
- L29 _public prototype_ `explicit FCompilationScope(const FText& InJobName);` — Standalone scope with no immediate related assets
- L32 _public prototype_ `explicit FCompilationScope(UUAFRigVMAsset* InAsset);` — Scope with a single asset which the caller will compile
- L35 _public prototype_ `explicit FCompilationScope(TConstArrayView<UUAFRigVMAsset*> InAssets);` — Scope with a set of assets which the caller will compile
- L38 _public prototype_ `explicit FCompilationScope(const FText& InJobName, TConstArrayView<UUAFRigVMAsset*> InAssets);` — Scope with a explicit name and set of assets which the caller will compile
- L41 _public prototype_ `explicit FCompilationScope(const FText& InJobName, UUAFRigVMAsset* InAsset);` — Scope with explicit name and a single asset which the caller will compile
- L43 _public prototype_ `~FCompilationScope();`
- L46 _public prototype_ `static FCompilerResultsLog& GetLogForObject(const UObject* InObject);` — Returns a CompilerResultsLog instance specifically for the provided UObject
- L48 _private prototype_ `static void ProcessAssets(const FText& InJobName, TConstArrayView<UUAFRigVMAsset*, int> InAssets);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Public/Variables/AnimNextProgrammaticVariable.h` (Public)


#### struct `FAnimNextProgrammaticVariable`  
`struct FAnimNextProgrammaticVariable`  
_L17-67_
- desc: Struct wrapping a graph variable. Includes default value.
- L21 _public prototype_ `FAnimNextParamType GetType() const;` — Get arg AnimNext param type
- L24 _public prototype_ `bool SetType(const FAnimNextParamType& InType, bool bSetupUndoRedo = true);` — Set AnimNext param type, also sets propertybag to hold that type
- L27 _public prototype_ `FName GetVariableName() const;` — Get VM variable name
- L30 _public prototype_ `void SetVariableName(FName InName, bool bSetupUndoRedo = true);` — Set VM variable name
- L33 _public prototype_ `bool SetDefaultValue(TConstArrayView<uint8> InValue, bool bSetupUndoRedo = true);` — Set variable default value in propertybag
- L36 _public prototype_ `bool SetDefaultValueFromString(const FString& InDefaultValue, bool bSetupUndoRedo = true);` — Set variable default value in propertybag via string
- L39 _public prototype_ `const FInstancedPropertyBag& GetPropertyBag() const;` — Get inner propertybag storing values
- L42 _public prototype_ `FInstancedPropertyBag& GetMutablePropertyBag();` — Get inner propertybag storing values, mutable
- L45 _public prototype_ `bool GetDefaultValue(const FProperty*& OutProperty, TConstArrayView<uint8>& OutValue) const;` — Get default value via property
- L48 _public prototype_ `const uint8* GetValuePtr() const;` — Access the memory for the internal value
- L51 _public prototype_ `FGuid GetGuid() const;` — Returns deterministic GUID
- L55 _public member_ `FName Name;` — Name of the variable
- L58 _public member_ `FAnimNextParamType Type = FAnimNextParamType::GetType<bool>();` — The variable's type
- L61 _public member_ `FInstancedPropertyBag DefaultValue;` — Property bag holding the default value of the variable
- L66 _public prototype_ `static FAnimNextProgrammaticVariable FromRigVMGraphFunctionArgument(const FRigVMGraphFunctionArgument& RigVMGraphFunctionArgument);` — Construct a parameter type from the passed in FRigVMTemplateArgumentType.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Public/Variables/AnimNextVariableBinding.h` (Public)


#### struct `FAnimNextVariableBinding`  
`struct FAnimNextVariableBinding`  
_L11-25_
- reflection: `USTRUCT()`
- L15 _public prototype_ `FAnimNextVariableBinding() = default;`
- L18 _public function_ `bool IsValid() const` — Returns whether this binding is valid
- L24 _public member_ `TInstancedStruct<FAnimNextVariableBindingData> BindingData;` — `UPROPERTY(EditAnywhere, Category = "Binding", meta=(ExcludeBaseStruct))`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Public/Variables/AnimNextVariableBindingData.h` (Public)


#### struct `FAnimNextVariableBindingData`  
`struct FAnimNextVariableBindingData`  
_L10-21_
- reflection: `USTRUCT(meta=(Hidden))`
- desc: Base struct that abstracts binding source data
- L14 _public prototype_ `virtual ~FAnimNextVariableBindingData() = default;`
- L17 _public function_ `virtual bool IsValid() const` — Returns whether this binding data is valid or not
- L20 _public function_ `virtual bool IsThreadSafe() const` — Returns whether this binding data is thread safe or not

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Public/Variables/IAnimNextRigVMVariableInterface.h` (Public)


#### class `UUAFRigVMVariableInterface`  
`class UUAFRigVMVariableInterface : public UInterface`  
_L16-19_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IUAFRigVMVariableInterface`  
`class IUAFRigVMVariableInterface`  
_L21-85_
- L27 _public prototype_ `virtual FAnimNextParamType GetType() const = 0;` — Get the variable type
- L30 _public prototype_ `virtual bool SetType(const FAnimNextParamType& InType, bool bSetupUndoRedo = true) = 0;` — Set the variable type
- L33 _public prototype_ `virtual FName GetVariableName() const = 0;` — Get the variable name
- L36 _public prototype_ `virtual void SetVariableName(FName InName, bool bSetupUndoRedo = true) = 0;` — Set the variable name
- L39 _public prototype_ `virtual bool SetDefaultValue(TConstArrayView<uint8> InValue, bool bSetupUndoRedo = true) = 0;` — Set the default value
- L42 _public prototype_ `virtual bool SetDefaultValueFromString(const FString& InDefaultValue, bool bSetupUndoRedo = true) = 0;` — Set the default value from a string
- L45 _public prototype_ `virtual const FInstancedPropertyBag& GetPropertyBag() const = 0;` — Access the backing storage property bag for the parameter
- L48 _public function_ `FInstancedPropertyBag& GetMutablePropertyBag()` — Access the mutable backing storage property bag for the parameter
- L53 _public prototype_ `virtual bool GetDefaultValue(const FProperty*& OutProperty, TConstArrayView<uint8>& OutValue) const = 0;`
- L54 _public prototype_ `virtual bool GetDefaultValueString(FString& OutValueString) const = 0;`
- L57 _public prototype_ `virtual void SetBindingType(UScriptStruct* InBindingTypeStruct, bool bSetupUndoRedo = true) = 0;` — Set the binding type for this variable (initializes it to default if the struct type is valid)
- L60 _public prototype_ `virtual void SetBinding(TInstancedStruct<FAnimNextVariableBindingData>&& InBinding, bool bSetupUndoRedo = true) = 0;` — Set the binding for this variable
- L63 _public prototype_ `virtual TConstStructView<FAnimNextVariableBindingData> GetBinding() const = 0;` — Get the binding for this variable, if any
- L66 _public prototype_ `virtual FStringView GetVariableCategory() const = 0;` — Get the category for this variable, empty string if none assigned
- L69 _public prototype_ `virtual void SetVariableCategory(FStringView InCategoryName, bool bSetupUndoRedo = true) = 0;` — Set the category for this variable
- L72 _public prototype_ `virtual const FGuid& GetGuid() const = 0;` — Returns (stable and unique) GUID representing this variable
- L75 _public function_ `const uint8* GetValuePtr() const` — Access the memory for the internal value
- L84 _public member_ `static const FLazyName ValueName;` — The name of the value property in the internal property bag

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFUNCOOKEDONLY_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFUncookedOnly/Public/Variables/IVariableBindingType.h` (Public)


#### class `UE::UAF::UncookedOnly::IVariableBindingType`  
`class IVariableBindingType`  
_L33-89_
- desc: Interface used in editor/uncooked situations to determine the characteristics of a variable binding
- L36 _public prototype_ `virtual ~IVariableBindingType() = default;`
- L71 _private prototype_ `virtual TSharedRef<SWidget> CreateEditWidget(const TSharedRef<IPropertyHandle>& InPropertyHandle, const FAnimNextParamType& InType) const = 0;` — Create a widget used to edit the binding (displayed in a submenu from a combobox)
- L74 _private prototype_ `virtual FText GetDisplayText(TConstStructView<FAnimNextVariableBindingData> InBindingData) const = 0;` — Get the display text for the specified instance ID
- L77 _private prototype_ `virtual FText GetTooltipText(TConstStructView<FAnimNextVariableBindingData> InBindingData) const = 0;` — Get the tooltip text for the specified instance ID
- L80 _private prototype_ `virtual bool Validate(TConstStructView<FAnimNextVariableBindingData> InBindingData, FText& OutError) const = 0;` — Validate the binding data
- L84 _private prototype_ `virtual void BuildBindingGraphFragment(const FRigVMCompileSettings& InSettings, const FBindingGraphFragmentArgs& InArgs, URigVMPin*& OutExecTail, FVector2D& OutLocation) const = 0;` — Transforms the inputs into graph fragments. Called to convert variable bindings (derived from FAnimNextVariableBindingData) into intermediate RigVM graphs for consumption by the compiler

#### struct `UE::UAF::UncookedOnly::IVariableBindingType::FBindingGraphInput`  
`struct FBindingGraphInput`  
_L39-49_
- L42 _public member_ `FName VariableName;` — Name of the target variable that this binding is bound to
- L44 _public member_ `FString CPPType;` — CPPType of the variable
- L46 _public member_ `TObjectPtr<UObject> CPPTypeObject;` — CPPTypeObject of the variable
- L48 _public member_ `TConstStructView<FAnimNextVariableBindingData> BindingData;` — Binding data of the type that this processor is registered against

#### struct `UE::UAF::UncookedOnly::IVariableBindingType::FBindingGraphFragmentArgs`  
`struct FBindingGraphFragmentArgs`  
_L51-67_
- L54 _public member_ `UScriptStruct* Event;` — The event (e.g. FRigUnit_AnimNextExecuteBindings_GT) that is currently being processed
- L56 _public member_ `TConstArrayView<FBindingGraphInput> Inputs;` — All inputs, corresponding to variables
- L58 _public member_ `URigVMController* Controller;` — Controller to use for instantiation
- L60 _public member_ `URigVMGraph* BindingGraph;` — Graph to instantiate nodes into
- L62 _public member_ `URigVMPin* ExecTail;` — The exec pin of the last node that was instantiated, for chaining
- L64 _public member_ `FVector2D CurrentLocation;` — The current spawn location, useful for making user-readable graphs
- L66 _public member_ `bool bThreadSafe;` — Whether we should be processing thread-safe bindings

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace UAF` (scope `UE`)
- L24 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UAF` (scope `UE`)
- L29 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
