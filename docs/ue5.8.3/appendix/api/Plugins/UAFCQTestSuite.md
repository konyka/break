# Plugins / UAFCQTestSuite

- module root: `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFCQTestSuite`
- headers: 4; symbols: 42
- symbol kinds: class=7, function=18, member=2, namespace=1, prototype=12, struct=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CQTest, CoreUObject, Engine, RigVM, RigVMDeveloper, UAF, UAFAnimGraph, UAFAnimGraphEditor, UAFAnimNodeTestData, UAFEditor, UAFStateTree, UAFStateTreeEditor, UAFTestSuite, UAFUncookedOnly, WorkspaceEditor
- PublicDependencyModuleNames: Core, UnrealEd

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFCQTestSuite/Private/UAFAssetDataTests.h` (Private)


#### struct `FUAFGraphFactoryAsset_Test`  
`struct FUAFGraphFactoryAsset_Test : public FUAFGraphFactoryAsset`  
_L11-16_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FUAFGraphFactoryAsset`
- L15 _public member_ `int TestData = 0;`

#### class `UUAFAssetDataTestObject`  
`class UUAFAssetDataTestObject : public UObject`  
_L19-25_
- reflection: `UCLASS()`
- inherits: `UObject`
- L24 _public member_ `int TestData = 0;`

#### class `UUAFAssetDataTestObject_ChildA`  
`class UUAFAssetDataTestObject_ChildA : public UUAFAssetDataTestObject`  
_L31-34_
- reflection: `UCLASS()`
- inherits: `UUAFAssetDataTestObject`
- desc: Subclass of UUAFAssetDataTestObject that IS registered with its own asset type (FUAFGraphFactoryAsset_TestChildA). GetRegisteredObjectClasses with the parent's asset type should NOT include it because it stops recursing at classes that have their own registered initializer.

#### struct `FUAFGraphFactoryAsset_TestChildA`  
`struct FUAFGraphFactoryAsset_TestChildA : public FUAFGraphFactoryAsset`  
_L38-41_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FUAFGraphFactoryAsset`
- desc: Factory Asset to register the asset type of UUAFAssetDataTestObject_ChildA

#### class `UUAFAssetDataTestObject_ChildB`  
`class UUAFAssetDataTestObject_ChildB : public UUAFAssetDataTestObject`  
_L46-49_
- reflection: `UCLASS()`
- inherits: `UUAFAssetDataTestObject`
- desc: Subclass of UUAFAssetDataTestObject that is NOT registered with FAssetDataFactory. GetRegisteredObjectClasses with the parent's asset type should include it

#### class `UUAFAssetDataTestObject_GrandChildA`  
`class UUAFAssetDataTestObject_GrandChildA : public UUAFAssetDataTestObject_ChildA`  
_L55-58_
- reflection: `UCLASS()`
- inherits: `UUAFAssetDataTestObject_ChildA`
- desc: Subclass of UUAFAssetDataTestObject_ChildA GetRegisteredObjectClasses with UUAFAssetDataTestObject_ChildA as base type should include this GetRegisteredObjectClasses with UUAFAssetDataTestObject should not include this

#### class `UUAFAssetDataTestObject_GrandChildB`  
`class UUAFAssetDataTestObject_GrandChildB : public UUAFAssetDataTestObject_ChildB`  
_L63-66_
- reflection: `UCLASS()`
- inherits: `UUAFAssetDataTestObject_ChildB`
- desc: Subclass of UUAFAssetDataTestObject_ChildB GetRegisteredObjectClasses with UUAFAssetDataTestObject should include this and its parent

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFCQTestSuite/Private/UAFTestBlueprintLibrary.h` (Private)


#### class `UUAFTestBlueprintLibrary`  
`class UUAFTestBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L17-324_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L24 _public function_ `static void RecompileVM(UUAFRigVMAsset* InAsset)` — `UFUNCTION(BlueprintCallable, Category = "UAF|Test", meta=(ScriptMethod))`
- L37 _public function_ `static URigVMGraph* GetModel(UUAFRigVMAsset* InAsset, const UEdGraph* InEdGraph = nullptr)` — `UFUNCTION(BlueprintCallable, Category = "UAF|Test", meta=(ScriptMethod))`
- L52 _public function_ `static URigVMGraph* GetDefaultModel(UUAFRigVMAsset* InAsset)` — `UFUNCTION(BlueprintCallable, Category = "UAF|Test", meta=(ScriptMethod))`
- L67 _public function_ `static TArray<URigVMGraph*> GetAllModels(UUAFRigVMAsset* InAsset)` — `UFUNCTION(BlueprintCallable, Category = "UAF|Test", meta=(ScriptMethod))`
- L82 _public function_ `static URigVMFunctionLibrary* GetLocalFunctionLibrary(UUAFRigVMAsset* InAsset)` — `UFUNCTION(BlueprintCallable, Category = "UAF|Test", meta=(ScriptMethod))`
- L97 _public function_ `static URigVMFunctionLibrary* GetOrCreateLocalFunctionLibrary(UUAFRigVMAsset* InAsset, bool bSetupUndoRedo = true)` — `UFUNCTION(BlueprintCallable, Category = "UAF|Test", meta=(ScriptMethod))`
- L112 _public function_ `static URigVMGraph* AddModel(UUAFRigVMAsset* InAsset, FString InName = TEXT("Rig Graph"), bool bSetupUndoRedo = true, bool bPrintPythonCommand = true)` — `UFUNCTION(BlueprintCallable, Category = "UAF|Test", meta=(ScriptMethod))`
- L127 _public function_ `static bool RemoveModel(UUAFRigVMAsset* InAsset, FString InName = TEXT("Rig Graph"), bool bSetupUndoRedo = true, bool bPrintPythonCommand = true)` — `UFUNCTION(BlueprintCallable, Category = "UAF|Test", meta=(ScriptMethod))`
- L142 _public function_ `static URigVMController* GetController(UUAFRigVMAsset* InAsset, const URigVMGraph* InGraph = nullptr)` — `UFUNCTION(BlueprintCallable, Category = "UAF|Test", meta=(ScriptMethod))`
- L157 _public function_ `static URigVMController* GetControllerByName(UUAFRigVMAsset* InAsset, const FString InGraphName = TEXT(""))` — `UFUNCTION(BlueprintCallable, Category = "UAF|Test", meta=(ScriptMethod))`
- L172 _public function_ `static URigVMController* GetOrCreateController(UUAFRigVMAsset* InAsset, URigVMGraph* InGraph = nullptr)` — `UFUNCTION(BlueprintCallable, Category = "UAF|Test", meta=(ScriptMethod))`
- L187 _public function_ `static void ExecuteVM(UUAFSystem* InModule, const FName& InEventName, bool& bExecutionResult, TArray<FString>& OutMessages)` — `UFUNCTION(BlueprintCallable, Category="UAFTest", meta=(ScriptMethod))`
- L239 _public function_ `static UUAFRigVMAsset* CreateAsset(TSubclassOf<UFactory> InAssetFactoryClass, const FName& InName)` — `UFUNCTION(BlueprintCallable, Category="UAFTest")`
- L266 _public function_ `static void MarkFunctionAsPublic(UUAFRigVMAsset* InAsset, FName InFunctionName)` — Test helper: mark a function as public so it gets compiled into FunctionData
- L280 _public function_ `static FGuid GetFunctionGuid(const UUAFRigVMAsset* InAsset, FName InFunctionName)` — Test helper: get the FunctionGuid from a function's compiled FunctionData
- L300 _public function_ `static void AddTestFunctionData(UUAFRigVMAsset* InAsset, FName InFunctionName, FName InEventName, TArray<int32> InArgIndices)` — Test helper: register a function in the asset's FunctionData array so it can be called via GetFunctionHandle/ExecuteParameterlessFunction. This is needed because BuildFunctionWrapperEvents only processes programmatic function headers (from traits), not user-created graph functions.
- L313 _public function_ `static EAnimNextRigVMAssetState GetCompilationState(const UUAFRigVMAsset* InAsset)` — `UFUNCTION(BlueprintPure, Category="UAFTest", meta=(ScriptMethod))`

#### Free symbols / members of external scopes

- L226 _function_ `` (scope `UUAFTestBlueprintLibrary::ExecuteVM`)

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFCQTestSuite/Public/UAFCQTestSuiteModule.h` (Public)


#### class `FUAFCQTestSuiteModule`  
`class FUAFCQTestSuiteModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFCQTestSuite/Public/UAFTestsUtilities.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UAFTestsUtilities`
- L26 _prototype_ `UObject* CreateFactoryObject(UFactory* InFactory, UClass* InClass, const FString& InPackageName = TEXT(""));` (scope `UAFTestsUtilities`) — Creates the object instance for the specified asset class. @param InFactory  A pointer to the factory instance. @param InClass  A pointer to the asset static class. @param InPackageName  Name being assigned to the package, optional. @return A pointer to the object instance for the specified asset class, or nullptr otherwise.
- L38 _prototype_ `UEdGraphNode* AddUnitNode(UEdGraph* InParentGraph, const FString& InScriptStructPath, TArray<UEdGraphPin*>& InFromPins, const FVector2f& InRigUnitLocation, const FString& InUnitNodeClassPath = TEXT(""));` (scope `UAFTestsUtilities`) — Adds a new RigUnit node to the AnimNext graph specified. @param InParentGraph  A pointer to the AnimNext parent graph instance. @param InScriptStructPath:  Path to the script struct. @param InFromPins:  Pin to wire from. @param InRigUnitLocation:  Location of the RigUnit node on the graph. @param InUnitNodeClassPath:  Path to the unit node class path, optional @return A pointer to the RigUnit node instance, or nullptr otherwise.
- L47 _prototype_ `URigVMLibraryNode* AddFunctionNode(UUAFRigVMAsset* InAnimNextAsset, const FString& InFunctionName = TEXT("NewF` (scope `UAFTestsUtilities`) — Adds a new function node instance to the AnimNext Asset specified. @param InAnimNextAsset  A pointer to the AnimNext asset instance. @param InFunctionName  Name to assign to function node, optional. @return A pointer to the object instance for the function node, or nullptr otherwise.
- L58 _prototype_ `UAnimNextVariableEntry* AddVariable(UUAFRigVMAsset* InAnimNextAsset, const FAnimNextParamType& InVariableType, const FString& InVariableName = TEXT("NewVariable"), const FString& InDefaultValue =` (scope `UAFTestsUtilities`) — Adds a new variable instance to the AnimNext Asset specified. @param InAnimNextAsset  A pointer to the AnimNext asset instance. @param InVariableType:  Data type of variable. @param InVariableName  Name to assign to variable, optional. @param InDefaultValue  Default value to assign to variable, optional. @return A pointer to the object instance for the variable, or nullptr otherwise.
- L67 _prototype_ `UUAFSharedVariablesEntry* AddSharedVariables(UUAFRigVMAsset* InAnimNextAsset, UUAFSharedVariables* InSharedVariables);` (scope `UAFTestsUtilities`) — Adds a new shared variables instance to the AnimNext Asset specified. @param InAnimNextAsset  A pointer to the AnimNext asset instance. @param InSharedVariables:  A pointer to the AnimNext shared variables instance. @return A pointer to the object instance for the shared variables, or nullptr otherwise.
- L81 _prototype_ `UEdGraphNode* AddVariableNode(UEdGraph* InParentGraph, const UObject* InSourceObject, const FString& InVariableName, const FAnimNextParamType& InVariableType, const FAnimNextSchemaAction_Variable::EVariableAccessorChoice InVariableAccessorChoice, TArray<UEdGraphPin*>& InFromPins, const FVector2f& InVariableLocation);` (scope `UAFTestsUtilities`) — Adds a new variable node to the AnimNext graph specified. @param InParentGraph  A pointer to the AnimNext parent graph instance. @param InSourceObject The source object (asset or struct) that this variable comes from @param InVariableName  Name to assign to variable. @param InVariableType:  Data type of variable. @param InVariableAccessorChoice:  Accessor choice of the variable node. @param InFromPins:  Pin to wire from. @param InVariableLocation:  Location of the variable node on the graph. @return A pointer to the variable node instance, or nullptr otherwise.
- L95 _prototype_ `URigVMPin* AddPin(UUAFRigVMAsset* InAnimNextAsset, URigVMLibraryNode* InLibraryNode, ERigVMPinDirection InDirection, const FString& InCPPName = TEXT("Argument"), const FString& InCPPType = TEXT("bool"), const FName& InCPPTypeObjectPath = TEXT("None"), const FString& InDefaultVa` (scope `UAFTestsUtilities`) — Adds a new pin to the library node specified. @param InAnimNextAsset  A pointer to the AnimNext asset instance. @param InLibraryNode  A pointer to the library node instance. @param InDirection  Direction of the pin. @param InCPPName  Name assigned to the pin, optional. @param InCPPType  Data type assigned to the pin, optional. @param InCPPTypeObjectPath  Path assigned to the pin, optional. @param InDefaultValue  Default value assigned to the pin, optional. @return A pointer to the pin instance for the specified library node, or nullptr otherwise.
- L105 _prototype_ `bool AddLink(UUAFRigVMAsset* InAnimNextAsset, const FString& InOutputPinPath, const FString& InInputPinPath);` (scope `UAFTestsUtilities`) — Adds a new link between two pins. @param InAnimNextAsset  A pointer to the AnimNext asset instance. @param InOutputPinPath  A path to an output pin. @param InInputPinPath  A path to an input pin. @return True if add link is successful, False otherwise.
- L114 _prototype_ `bool SetNodeSelection(UUAFRigVMAsset* InAnimNextAsset, const TArray<FName>& InNodeNames);` (scope `UAFTestsUtilities`) — Select specified node(s). @param InAnimNextAsset  A pointer to the AnimNext asset instance. @param InNodeNames  Array of node name(s) to select. @return True if node(s) selection is successful, False otherwise.
- L125 _prototype_ `URigVMCollapseNode* CollapseNodes(UUAFRigVMAsset* InAnimNextAsset, const TArray<FName>& InNodeNames, const FString& InCollapseNodeName = TEXT(""), bool InCollapseToFunction = false);` (scope `UAFTestsUtilities`) — Collapse selected nodes to a single node. @param InAnimNextAsset  A pointer to the AnimNext asset instance. @param InNodeNames  Array of node names to collapse. @param InCollapseNodeName  Name of collapse node, optional @param InCollapseToFunction  Collapse to a function node, optional. @return A pointer to the pin instance for the collapse node, or nullptr otherwise.
