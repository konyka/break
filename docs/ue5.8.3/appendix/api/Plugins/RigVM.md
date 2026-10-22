# Plugins / RigVM

- module root: `Plugins/Runtime/RigVM/Source/RigVM`
- headers: 116; symbols: 7143
- symbol kinds: class=44, delegate=16, enum=77, enumerator=360, externvar=46, function=1717, macro=71, member=2221, namespace=14, prototype=1869, struct=678, typedef=20, variable=10
- PrivateDependencyModuleNames: AssetTools, BlueprintGraph, StructUtilsEditor, UnrealEd
- PublicDependencyModuleNames: AnimGraphRuntime, AnimationCore, Core, CoreUObject, DeveloperSettings, Engine, Projects, RewindDebuggerRuntimeInterface, TraceLog

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMBlueprintGeneratedClass.h` (Public)


#### class `URigVMBlueprintGeneratedClass`  
`class URigVMBlueprintGeneratedClass : public UBlueprintGeneratedClass, public IRigVMGraphFunctionHost, public IRigVMRuntimeAssetInterface`  
_L17-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintGeneratedClass,IRigVMGraphFunctionHost,IRigVMRuntimeAssetInterface`
- L24 _public prototype_ `virtual uint8* GetPersistentUberGraphFrame(UObject* Obj, UFunction* FuncToCheck) const override;` — UClass interface
- L25 _public prototype_ `virtual void PostInitInstance(UObject* InObj, FObjectInstancingGraph* InstanceGraph) override;`
- L28 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L29 _public prototype_ `virtual void PostLoad() override;`
- L30 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L33 _public function_ `virtual const FRigVMGraphFunctionStore* GetRigVMGraphFunctionStore() const override` — IRigVMGraphFunctionHost interface
- L34 _public function_ `virtual FRigVMGraphFunctionStore* GetRigVMGraphFunctionStore() override`
- L38 _public function_ `virtual UObject* GetEditorOnlyData() override`
- L39 _public function_ `virtual const UObject* GetEditorOnlyData() const override`
- L41 _public prototype_ `virtual UClass* GetRigVMHostClass() const override;`
- L42 _public function_ `virtual URigVM* GetVM() override`
- L43 _public function_ `virtual TArray<FRigVMExternalVariable> GetExternalVariables() override`
- L44 _public function_ `virtual const UStruct* GetVariablesStruct() override`
- L45 _public function_ `virtual uint8* GetVariablesMemory() override`
- L46 _public function_ `virtual const uint8* GetVariablesMemory() const override`
- L47 _public function_ `virtual FProperty* FindGeneratedPropertyByName(const FName& InName) override`
- L48 _public function_ `virtual FRigVMRuntimeSettings& GetVMRuntimeSettings() override`
- L49 _public function_ `virtual FRigVMVariant& GetAssetVariant() override`
- L50 _public function_ `virtual TMap<FString, FSoftObjectPath>& GetUserDefinedStructGuidToPathName() override`
- L51 _public function_ `virtual TMap<FString, FSoftObjectPath>& GetUserDefinedEnumToPathName() override`
- L52 _public function_ `virtual TSet<TObjectPtr<UObject>>& GetUserDefinedTypesInUse() override`
- L53 _public function_ `virtual TArray<FName>& GetSupportedEventNames() override`
- L54 _public prototype_ `virtual void UpdateSupportedEventNames() override;`
- L55 _public prototype_ `virtual TArray<UObject*> GetArchetypeInstances(bool bIncludeDerivedClass) const override;`
- L56 _public function_ `virtual FRigVMExtendedExecuteContext* GetRigVMExtendedExecuteContext() override`
- L57 _public function_ `virtual void RemoveInstance(UObject* InInstance) override`
- L58 _public function_ `virtual URigVMHost* InstantiateObject(UObject* InOuter, FName InName, EObjectFlags InFlags) override`
- L59 _public function_ `virtual bool InitializeInstance(URigVMHost* InInstance) override`
- L60 _public prototype_ `virtual bool InitializeVariables(URigVMHost* InInstance) override;`
- L61 _public function_ `virtual bool IsObjectInstanceOfAsset(URigVMHost* InInstance) override`
- L62 _public function_ `virtual FRigVMDrawContainer& GetDrawContainer() override`
- L63 _public function_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override`
- L65 _public function_ `virtual FRigVMDebugInfo& GetDebugInfo() override`
- L69 _public member_ `FRigVMGraphFunctionStore GraphFunctionStore;` — `UPROPERTY()`
- L72 _public member_ `TArray<FName> SupportedEventNames;` — `UPROPERTY(AssetRegistrySearchable)`
- L76 _public member_ `FRigVMVariant AssetVariant;` — `UPROPERTY(AssetRegistrySearchable)` — Variant information about this asset

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVM.h` (Public)


#### enum `ERigVMParameterType`  
`enum class ERigVMParameterType : uint8`  
_L54-59_
- reflection: `UENUM(BlueprintType)`
- desc: The type of parameter for a VM
- L56 _public enumerator_ `Input`
- L57 _public enumerator_ `Output`
- L58 _public enumerator_ `Invalid`

#### struct `FRigVMParameter`  
`struct FRigVMParameter`  
_L67-147_
- reflection: `USTRUCT(BlueprintType)`
- desc: The RigVMParameter define an input or output of the RigVM. Parameters are mapped to work state memory registers and can be used to set input parameters as well as retrieve output parameters.
- L73 _public function_ `FRigVMParameter() : Type(ERigVMParameterType::Invalid) , Name(NAME_None) , RegisterIndex(INDEX_NONE) , CPPType() , ScriptStruct(nullptr) , ScriptStructPath()`
- L83 _public prototype_ `void Serialize(FArchive& Ar);`
- L84 _public prototype_ `void Save(FArchive& Ar);`
- L85 _public prototype_ `void Load(FArchive& Ar);`
- L94 _public function_ `bool IsValid() const` — returns true if the parameter is valid
- L97 _public function_ `ERigVMParameterType GetType() const` — returns the type of this parameter
- L100 _public function_ `const FName& GetName() const` — returns the name of this parameters
- L103 _public function_ `int32 GetRegisterIndex() const` — returns the register index of this parameter in the work memory
- L106 _public function_ `FString GetCPPType() const` — returns the cpp type of the parameter
- L109 _public prototype_ `UScriptStruct* GetScriptStruct() const;` — Returns the script struct used by this parameter (in case it is a struct)
- L113 _private function_ `FRigVMParameter(ERigVMParameterType InType, const FName& InName, int32 InRegisterIndex, const FString& InCPPType, UScriptStruct* InScriptStruct) : Type(InType) , Name(InName) , RegisterIndex(InRegisterIndex) , CPPType(InCPPType) , ScriptStruct(InScriptStruct) , ScriptStructPath(NAME_None)`
- L128 _private member_ `ERigVMParameterType Type;` — `UPROPERTY()`
- L131 _private member_ `FName Name;` — `UPROPERTY()`
- L134 _private member_ `int32 RegisterIndex;` — `UPROPERTY()`
- L137 _private member_ `FString CPPType;` — `UPROPERTY()`
- L140 _private member_ `TObjectPtr<UScriptStruct> ScriptStruct;` — `UPROPERTY(transient)`
- L143 _private member_ `FName ScriptStructPath;` — `UPROPERTY()`

#### class `URigVM`  
`class URigVM : public UObject`  
_L155-1068_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: The RigVM is the main object for evaluating FRigVMByteCode instructions. It combines the byte code, a list of required function pointers for execute instructions and required memory in one class.
- L160 _public prototype_ `URigVM();`
- L161 _public prototype_ `virtual ~URigVM();`
- L164 _public prototype_ `virtual void Serialize(FArchive& Ar);` — UObject interface
- L165 _public prototype_ `virtual void Save(FArchive& Ar);`
- L166 _public prototype_ `virtual void Load(FArchive& Ar);`
- L167 _public prototype_ `void CopyDataForSerialization(URigVM* InVM);`
- L168 _public prototype_ `void CopyExternalVariableDefs(URigVM* InVM);`
- L170 _public prototype_ `static bool IsSerializingToDisk(const FArchive& Ar);`
- L172 _public prototype_ `virtual void PostLoad() override;`
- L175 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L178 _public prototype_ `bool IsContextValidForExecution(FRigVMExtendedExecuteContext& Context) const;`
- L181 _public function_ `virtual bool IsNativized() const` — returns true if this is a nativized VM
- L184 _public prototype_ `virtual void SetVMHash(uint32 InVMHash);` — Stores the current VM hash
- L187 _public prototype_ `virtual uint32 GetVMHash() const;` — returns the cached VM hash
- L190 _public prototype_ `virtual uint32 ComputeVMHash() const;` — Generates a unique hash to compare VMs
- L191 _public prototype_ `virtual uint32 ComputeVMHash(const TArray<FRigVMExternalVariableDef>& InExternalVariables) const;`
- L192 _public prototype_ `virtual uint32 ComputeVMHash(const TArray<FRigVMExternalVariable>& InExternalVariables) const;`
- L195 _public prototype_ `UClass* GetNativizedClass(uint32 InHash) const;` — returns the VM's matching nativized class if it exists
- L198 _public prototype_ `virtual void Reset(FRigVMExtendedExecuteContext& Context);` — resets the container and maintains all memory
- L201 _public prototype_ `virtual void Empty(FRigVMExtendedExecuteContext& Context);` — resets the container and removes all memory
- L204 _public prototype_ `virtual bool Initialize(FRigVMExtendedExecuteContext& Context);` — Prepares caches and memory for execution
- L207 _public prototype_ `virtual bool InitializeInstance(FRigVMExtendedExecuteContext& Context, bool bCopyMemory = true);` — Initializes cached memory handles and optionally copies work memory from the CDO to the Context
- L211 _public prototype_ `virtual ERigVMExecuteResult ExecuteVM(FRigVMExtendedExecuteContext& Context, const FName& InEntryName = NAME_None);` — Executes the VM. You can optionally provide optional additional operands.
- L215 _public function_ `virtual bool Execute(FRigVMExtendedExecuteContext& Context, const FName& InEntryName = NAME_None)` — `UE_DEPRECATED(5.4, "Please, use ExecuteVM with Context param")` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported."))`
- L218 _public prototype_ `ERigVMExecuteResult ExecuteBranch(FRigVMExtendedExecuteContext& Context, const FRigVMBranchInfo& InBranchToRun);` — Executes a single branch on the VM. We assume that the memory is already set correctly at this point.
- L221 _private prototype_ `ERigVMExecuteResult ExecuteInstructions(FRigVMExtendedExecuteContext& Context, int32 InFirstInstruction, int32 InLastInstruction);`
- L228 _public prototype_ `virtual int32 AddRigVMFunction(UScriptStruct* InRigVMStruct, const FName& InMethodName);` — `UFUNCTION()` — Add a function for execute instructions to this VM. Execute instructions can then refer to the function by index.
- L229 _public prototype_ `virtual int32 AddRigVMFunction(const FString& InFunctionName);`
- L230 _public prototype_ `virtual int32 AddRigVMFunction(const FName& InFunctionFName);`
- L233 _private prototype_ `virtual int32 AddRigVMFunctionImpl(const FName& InFunctionFName, const FString& InFunctionName);`
- L238 _public prototype_ `virtual FString GetRigVMFunctionName(int32 InFunctionIndex) const;` — `UFUNCTION()` — Returns the name of a function given its index
- L241 _public prototype_ `virtual FRigVMMemoryStorageStruct* GetMemoryByType(FRigVMExtendedExecuteContext& Context, ERigVMMemoryType InMemoryType);` — Returns a memory storage by type
- L242 _public prototype_ `virtual const FRigVMMemoryStorageStruct* GetMemoryByType(const FRigVMExtendedExecuteContext& Context, ERigVMMemoryType InMemoryType) const;`
- L245 _public function_ `FRigVMMemoryStorageStruct* GetLiteralMemory()` — The default const literal memory
- L249 _public function_ `const FRigVMMemoryStorageStruct* GetLiteralMemory() const`
- L255 _public function_ `FRigVMMemoryStorageStruct* GetWorkMemory(FRigVMExtendedExecuteContext& Context)` — The instance mutable work memory the VM will use to execute
- L259 _public function_ `const FRigVMMemoryStorageStruct* GetWorkMemory(const FRigVMExtendedExecuteContext& Context) const`
- L265 _public function_ `FRigVMMemoryStorageStruct* GetDebugMemory(FRigVMExtendedExecuteContext& Context)` — The instance debug watch memory
- L269 _public function_ `const FRigVMMemoryStorageStruct* GetDebugMemory(const FRigVMExtendedExecuteContext& Context) const`
- L275 _public prototype_ `FRigVMMemoryStorageStruct* CreateDebugMemory(FRigVMExtendedExecuteContext& Context);` — creates the debug memory for a single instance of this VM
- L278 _public function_ `const FRigVMMemoryStorageStruct& GetDefaultLiteralMemory() const` — The default non mutable reference literal memory (generated by the compiler and copied to the instances as initial state)
- L282 _public function_ `FRigVMMemoryStorageStruct& GetDefaultLiteralMemory()`
- L288 _public function_ `const FRigVMMemoryStorageStruct& GetDefaultWorkMemory() const` — The default non mutable reference work memory (generated by the compiler and copied to the instances as initial state)
- L292 _public function_ `FRigVMMemoryStorageStruct& GetDefaultWorkMemory()`
- L298 _public prototype_ `virtual void GenerateMemoryType(FRigVMExtendedExecuteContext& Context, ERigVMMemoryType InMemoryType, const TArray<FRigVMPropertyDescription>* InProperties);` — Generates the Default memory and copy it to the Context if required by the type of memory
- L301 _public prototype_ `virtual void GenerateDefaultMemoryType(ERigVMMemoryType InMemoryType, const TArray<FRigVMPropertyDescription>* InProperties);` — Used by the compiler and EngineTests to generate the default VM memory storages
- L304 _public prototype_ `virtual const FRigVMMemoryStorageStruct* GetDefaultMemoryByType(ERigVMMemoryType InMemoryType) const;` — Returns a default memory storage by type
- L305 _public prototype_ `virtual FRigVMMemoryStorageStruct* GetDefaultMemoryByType(ERigVMMemoryType InMemoryType);`
- L310 _public prototype_ `virtual void ClearMemory(FRigVMExtendedExecuteContext& Context);`
- L313 _public member_ `FRigVMMemoryStorageStruct LiteralMemoryStorage;` — `UPROPERTY()`
- L316 _public member_ `FRigVMMemoryStorageStruct DefaultWorkMemoryStorage;` — `UPROPERTY()`
- L319 _public member_ `FRigVMMemoryStorageStruct DefaultDebugMemoryStorage_DEPRECATED;` — `UPROPERTY()`
- L324 _public member_ `TObjectPtr<URigVMMemoryStorage> WorkMemoryStorageObject_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Please, use DefaultWorkMemoryStorage for compiling and WorkMemoryStorage in the ExtendedExecuteContext for intance execution"))` — Deprecated 5.4
- L330 _public member_ `TObjectPtr<URigVMMemoryStorage> LiteralMemoryStorageObject_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Please, use LiteralMemoryStorage"))` — Deprecated 5.4
- L336 _public member_ `TObjectPtr<URigVMMemoryStorage> DebugMemoryStorageObject_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Please use DefaultDebugMemoryStorage for compiling and DebugMemoryStorage in the ExtendedExecuteContext for intance execution"))` — Deprecated 5.4,
- L339 _public member_ `TArray<FRigVMPropertyPathDescription> ExternalPropertyPathDescriptions;`
- L340 _public member_ `TArray<FRigVMPropertyPath> ExternalPropertyPaths;`
- L344 _public member_ `FRigVMByteCode ByteCodeStorage;` — `UPROPERTY()` — The byte code of the VM
- L345 _public member_ `FRigVMByteCode* ByteCodePtr;`
- L346 _public function_ `FRigVMByteCode& GetByteCode()`
- L347 _public function_ `virtual const FRigVMByteCode& GetByteCode() const`
- L350 _public prototype_ `virtual const FRigVMInstructionArray& GetInstructions();` — Returns the instructions of the VM
- L353 _public prototype_ `virtual bool ContainsEntry(const FName& InEntryName) const;` — Returns true if this VM's bytecode contains a given entry
- L356 _public prototype_ `virtual int32 FindEntry(const FName& InEntryName) const;` — Returns the index of an entry
- L359 _public prototype_ `virtual const TArray<FName>& GetEntryNames() const;` — Returns a list of all valid entry names for this VM's bytecode
- L362 _public prototype_ `bool CanExecuteEntry(const FRigVMExtendedExecuteContext& Context, const FName& InEntryName, bool bLogErrorForMissingEntry = true) const;` — returns false if an entry can not be executed
- L365 _public function_ `TMap<int32, TArray<FRigVMTraitScope>> GetTraits(FRigVMExtendedExecuteContext& InContext, const UScriptStruct* InScriptStruct = nullptr)` — returns the traits for this VM's bytecode and Context
- L372 _public function_ `template<typename T> TMap<int32, TArray<FRigVMTraitScope>> GetTraits(FRigVMExtendedExecuteContext& InContext)` — returns the traits of a given type for this VM's bytecode and Context
- L378 _public function_ `TMap<int32, TArray<FRigVMTraitScope>> GetTraits(FRigVMExtendedExecuteContext& InContext, TArray<FRigVMMemoryHandle>& OutAdditionalMemoryHandles, const UScriptStruct* InScriptStruct = nullptr)` — returns the traits for this VM's bytecode and Context, as well as any additional memory handles
- L385 _public function_ `template<typename T> TMap<int32, TArray<FRigVMTraitScope>> GetTraits(FRigVMExtendedExecuteContext& InContext, TArray<FRigVMMemoryHandle>& OutAdditionalMemoryHandles)` — returns the traits of a given type for this VM's bytecode and Context, as well as any additional memory handles
- L391 _public function_ `TArray<FRigVMTraitScope> GetTraitsForInstruction(const FRigVMInstruction& InInstruction, FRigVMExtendedExecuteContext& InContext, const UScriptStruct* InScriptStruct = nullptr)` — returns the traits for the provided memory for a single instruction
- L398 _public function_ `template<typename T> TArray<FRigVMTraitScope> GetTraitsForInstruction(const FRigVMInstruction& InInstruction, FRigVMExtendedExecuteContext& InContext)` — returns the traits of a given type for the provided memory for a single instruction
- L406 _public function_ `bool WasInstructionVisitedDuringLastRun(const FRigVMExtendedExecuteContext& Context, int32 InIndex) const` — Returns true if the given instruction has been visited during the last run
- L412 _public function_ `int32 GetInstructionVisitedCount(const FRigVMExtendedExecuteContext& Context, int32 InIndex) const` — Returns the number of times an instruction has been hit
- L422 _public function_ `int32 GetCallableVisitedCount(const FRigVMExtendedExecuteContext& Context, int32 InIndex) const` — Returns the number of times a callable has been hit
- L434 _public function_ `uint64 GetInstructionCycles(const FRigVMExtendedExecuteContext& Context, int32 InIndex) const` — Returns accumulated cycles spent in an instruction during the last run This requires bEnabledProfiling to be turned on in the runtime settings. If there is no information available this function returns UINT64_MAX.
- L446 _public function_ `uint64 GetCallableCycles(const FRigVMExtendedExecuteContext& Context, int32 InIndex) const` — Returns accumulated cycles spent in a callable  during the last run This requires bEnabledProfiling to be turned on in the runtime settings. If there is no information available this function returns UINT64_MAX.
- L458 _public function_ `double GetInstructionMicroSeconds(const FRigVMExtendedExecuteContext& Context, int32 InIndex) const` — Returns accumulated duration of the instruction in microseconds during the last run Note: this requires bEnabledProfiling to be turned on in the runtime settings. If there is no information available this function returns -1.0.
- L471 _public function_ `double GetCallableMicroSeconds(const FRigVMExtendedExecuteContext& Context, int32 InIndex) const` — Returns accumulated duration of the callable in microseconds during the last run Note: this requires bEnabledProfiling to be turned on in the runtime settings. If there is no information available this function returns -1.0.
- L482 _public function_ `const TArray<int32> GetInstructionVisitOrder(const FRigVMExtendedExecuteContext& Context) const` — Returns the order of all instructions during the last run
- L493 _public prototype_ `bool ResumeExecution(FRigVMExtendedExecuteContext& Context, const FName& InEntryName = NAME_None);` — `UE_DEPRECATED(5.7, "ResumeExecution is no longer supported.")`
- L498 _public prototype_ `const TArray<FRigVMParameter>& GetParameters() const;` — Returns the parameters of the VM
- L501 _public prototype_ `FRigVMParameter GetParameterByName(const FName& InParameterName);` — Returns a parameter given it's name
- L503 _public function_ `FRigVMParameter AddParameter(FRigVMExtendedExecuteContext& Context, ERigVMParameterType InType, const FName& InParameterName, const FName& InWorkMemoryPropertyName)`
- L531 _public function_ `int32 GetParameterArraySize(FRigVMExtendedExecuteContext& Context, const FRigVMParameter& InParameter)` — Retrieve the array size of the parameter
- L548 _public function_ `int32 GetParameterArraySize(FRigVMExtendedExecuteContext& Context, int32 InParameterIndex)` — Retrieve the array size of the parameter
- L554 _public function_ `int32 GetParameterArraySize(FRigVMExtendedExecuteContext& Context, const FName& InParameterName)` — Retrieve the array size of the parameter
- L565 _public function_ `template<class T> T GetParameterValue(FRigVMExtendedExecuteContext& Context, const FRigVMParameter& InParameter, int32 InArrayIndex = 0, T DefaultValue = T{})` — Retrieve the value of a parameter
- L590 _public function_ `template<class T> T GetParameterValue(FRigVMExtendedExecuteContext& Context, int32 InParameterIndex, int32 InArrayIndex = 0, T DefaultValue = T{})` — Retrieve the value of a parameter given its index
- L600 _public function_ `template<class T> T GetParameterValue(FRigVMExtendedExecuteContext& Context, const FName& InParameterName, int32 InArrayIndex = 0, T DefaultValue = T{})` — Retrieve the value of a parameter given its name
- L611 _public function_ `template<class T> void SetParameterValue(FRigVMExtendedExecuteContext& Context, const FRigVMParameter& InParameter, const T& InNewValue, int32 InArrayIndex = 0)` — Set the value of a parameter
- L636 _public function_ `template<class T> void SetParameterValue(FRigVMExtendedExecuteContext& Context, int32 ParameterIndex, const T& InNewValue, int32 InArrayIndex = 0)` — Set the value of a parameter given its index
- L646 _public function_ `template<class T> void SetParameterValue(FRigVMExtendedExecuteContext& Context, const FName& InParameterName, const T& InNewValue, int32 InArrayIndex = 0)` — Set the value of a parameter given its name
- L653 _public function_ `bool GetParameterValueBool(const FName& InParameterName, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L656 _public function_ `float GetParameterValueFloat(const FName& InParameterName, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L659 _public function_ `double GetParameterValueDouble(const FName& InParameterName, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L662 _public function_ `int32 GetParameterValueInt(const FName& InParameterName, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L665 _public function_ `FName GetParameterValueName(const FName& InParameterName, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L668 _public function_ `FString GetParameterValueString(const FName& InParameterName, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L671 _public function_ `FVector2D GetParameterValueVector2D(const FName& InParameterName, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L674 _public function_ `FVector GetParameterValueVector(const FName& InParameterName, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L677 _public function_ `FQuat GetParameterValueQuat(const FName& InParameterName, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L680 _public function_ `FTransform GetParameterValueTransform(const FName& InParameterName, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L683 _public function_ `void SetParameterValueBool(const FName& InParameterName, bool InValue, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L686 _public function_ `void SetParameterValueFloat(const FName& InParameterName, float InValue, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L689 _public function_ `void SetParameterValueDouble(const FName& InParameterName, double InValue, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L692 _public function_ `void SetParameterValueInt(const FName& InParameterName, int32 InValue, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L695 _public function_ `void SetParameterValueName(const FName& InParameterName, const FName& InValue, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L698 _public function_ `void SetParameterValueString(const FName& InParameterName, const FString& InValue, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L701 _public function_ `void SetParameterValueVector2D(const FName& InParameterName, const FVector2D& InValue, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L704 _public function_ `void SetParameterValueVector(const FName& InParameterName, const FVector& InValue, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L707 _public function_ `void SetParameterValueQuat(const FName& InParameterName, const FQuat& InValue, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L710 _public function_ `void SetParameterValueTransform(const FName& InParameterName, const FTransform& InValue, int32 InArrayIndex = 0)` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported, please, update your code."))`
- L713 _public prototype_ `void ClearExternalVariables(FRigVMExtendedExecuteContext& Context);` — Clears the external variables of the VM
- L716 _public function_ `const TArray<FRigVMExternalVariableDef>& GetExternalVariableDefs() const` — Returns the external variables of the VM (without variable memory, as it is stored in Context)
- L722 _public function_ `const TArray<FRigVMExternalVariable> GetExternalVariables(const FRigVMExtendedExecuteContext& Context) const` — Returns the external variables of the VM with variable memory
- L739 _public prototype_ `FRigVMExternalVariableDef GetExternalVariableDefByName(const FName& InExternalVariableName);` — Returns an external variable Def given it's name
- L742 _public prototype_ `FRigVMExternalVariable GetExternalVariableByName(const FRigVMExtendedExecuteContext& Context, const FName& InExternalVariableName);` — Returns an external variable given it's name
- L745 _public prototype_ `void SetExternalVariableDefs(const TArray<FRigVMExternalVariable>& InExternalVariables);` — Sets the external variables without the instance data
- L748 _public function_ `virtual void SetExternalVariablesInstanceData(FRigVMExtendedExecuteContext& Context, const TArray<FRigVMExternalVariable>& InExternalVariables, bool bAllowNullMemory = false)` — Sets the external variables instance data required for execution
- L770 _public function_ `FRigVMOperand AddExternalVariable(FRigVMExtendedExecuteContext& Context, const FRigVMExternalVariable& InExternalVariable, bool bAllowNullMemory = false)` — Adds a new external / unowned variable to the VM
- L780 _public prototype_ `void SetPropertyValueFromString(FRigVMExtendedExecuteContext& Context, const FRigVMOperand& InOperand, const FString& InDefaultValue);`
- L784 _public function_ `FRigVMStatistics GetStatistics() const` — `UFUNCTION(BlueprintPure, Category = "RigVM", meta=(DeprecatedFunction))` — returns the statistics information
- L812 _public prototype_ `FRigVMRegistry_NoLock* GetLocalizedRegistry() const;` — Returns the localized registry this VM uses or nullptr
- L815 _public prototype_ `bool CreateLocalizedRegistryIfRequired(bool bForce = false);` — Creates a localized registry for this VM
- L816 _public prototype_ `bool CreateLocalizedRegistryIfRequired_NoLock(bool bForce = false);`
- L820 _protected member_ `TSharedPtr<FRigVMRegistry_NoLock> LocalizedRegistry;` — The local registry to use by the VM
- L822 _protected prototype_ `FString GetLocalizedRegistryAsString() const;`
- L823 _protected prototype_ `void SetLocalizedRegistryFromString(const FString& InData);`
- L829 _public prototype_ `TArray<FString> DumpByteCodeAsTextArray(FRigVMExtendedExecuteContext& Context, const TArray<int32> & InInstructionOrder = TArray<int32>(), bool bIncludeLineNumbers = true, TFunction<FString(const FString& RegisterName, const FString& RegisterOffsetName)> OperandFormatFunction = nullptr);` — returns the instructions as text, OperandFormatFunction is an optional argument that allows you to override how operands are displayed, for example, see SRigVMExecutionStackView::PopulateStackView
- L831 _public prototype_ `FString DumpByteCodeAsText(FRigVMExtendedExecuteContext& Context, const TArray<int32>& InInstructionOrder = TArray<int32>(), bool bIncludeLineNumbers = true);`
- L836 _public prototype_ `FString GetOperandLabel(FRigVMExtendedExecuteContext& Context, const FRigVMOperand & InOperand, TFunction<FString(const FString& RegisterName, const FString& RegisterOffsetName)> FormatFunction = nullptr);` — FormatFunction is an optional argument that allows you to override how operands are displayed, for example, see SRigVMExecutionStackView::PopulateStackView
- L840 _private prototype_ `bool ResolveFunctionsIfRequired();`
- L841 _private prototype_ `void RefreshInstructionsIfRequired();`
- L844 _public prototype_ `void InvalidateCachedMemory(FRigVMExtendedExecuteContext& Context);`
- L847 _private prototype_ `void InstructionOpEval( FRigVMExtendedExecuteContext& Context, FRigVMRegistryHandle& RegistryHandle, int32 InstructionIndex, int32 InHandleBaseIndex, const TFunctionRef<void( FRigVMExtendedExecuteContext& , FRigVMRegistryHandle& , int32 , int32 , const FRigVMBranchInfoKey& , const FRigVMOperand& )>& InOpFunc);`
- L860 _private prototype_ `void PrepareMemoryForExecution(FRigVMExtendedExecuteContext& Context);`
- L861 _private prototype_ `void CacheMemoryHandles(FRigVMExtendedExecuteContext& Context);`
- L862 _private prototype_ `void RebuildByteCodeOnLoad();`
- L865 _private member_ `FRigVMInstructionArray Instructions;` — `UPROPERTY(transient)`
- L869 _protected function_ `[[nodiscard]] virtual bool SetInstructionIndex(FRigVMExtendedExecuteContext& Context, FRigVMExecuteContext& PublicData, int32 InInstructionIndex) const`
- L884 _protected function_ `[[nodiscard]] bool IncrementInstructionIndex(FRigVMExtendedExecuteContext& Context, FRigVMExecuteContext& PublicData) const`
- L891 _protected member_ `uint32 NumExecutions_DEPRECATED = 0;` — `UPROPERTY(transient)`
- L894 _protected prototype_ `UE_MT_DECLARE_TS_RW_ACCESS_DETECTOR(AccessDetector);`
- L897 _public prototype_ `bool ValidateBytecode();`
- L898 _public prototype_ `void RefreshArgumentNameCaches();`
- L899 _public prototype_ `TArray<const UObject*> GetUserDefinedDependencies(const TArray<const FRigVMMemoryStorageStruct*> InMemory);`
- L900 _public prototype_ `void GetRequiredPlugins(TArray<FString>& OutPlugins);`
- L905 _private member_ `TArray<FName> FunctionNamesStorage;` — `UPROPERTY()`
- L906 _private member_ `TArray<FName>* FunctionNamesPtr;`
- L908 _public function_ `TArray<FName>& GetFunctionNames()`
- L909 _public function_ `virtual const TArray<FName>& GetFunctionNames() const`
- L911 _private member_ `TArray<const FRigVMFunction*> FunctionsStorage;`
- L912 _private member_ `TArray<const FRigVMFunction*>* FunctionsPtr;`
- L914 _public function_ `TArray<const FRigVMFunction*>& GetFunctions()`
- L915 _public function_ `virtual const TArray<const FRigVMFunction*>& GetFunctions() const`
- L917 _private member_ `TArray<const FRigVMDispatchFactory*> FactoriesStorage;`
- L918 _private member_ `TArray<const FRigVMDispatchFactory*>* FactoriesPtr;`
- L920 _public function_ `TArray<const FRigVMDispatchFactory*>& GetFactories()`
- L921 _public function_ `virtual const TArray<const FRigVMDispatchFactory*>& GetFactories() const`
- L925 _private member_ `TArray<FRigVMParameter> Parameters;` — `UPROPERTY()`
- L927 _private member_ `TMap<FName, int32> ParametersNameMap;`
- L929 _private member_ `TArray<uint32> FirstHandleForInstruction;`
- L931 _private member_ `int32 MemoryHandleCount = 0;`
- L933 _private member_ `TArray<FRigVMMemoryHandle> PreCachedMemoryHandles;`
- L934 _private member_ `TArray<ERigVMMemoryType> PreCachedMemoryHandlesMemoryType;`
- L936 _private member_ `TArray<FRigVMExternalVariableDef> ExternalVariables;`
- L937 _private member_ `TArray<FRigVMLazyBranch> LazyBranches;`
- L940 _private function_ `static int32 GetContainerIndex(ERigVMMemoryType InType)` — this function should be kept in sync with FRigVMOperand::GetContainerIndex()
- L955 _private prototype_ `void ClearDebugMemory(FRigVMExtendedExecuteContext& Context);` — debug watch register memory needs to be cleared for each execution
- L957 _private prototype_ `void PreCacheSingleMemoryHandle(const FRigVMRegistryHandle& InRegistry, int32 InInstructionIndex, int32 InHandleIndex, const FRigVMBranchInfoKey& InBranchInfoKey, const FRigVMOperand& InArg, bool bForExecute = false);`
- L959 _private prototype_ `static void GeneratePatchedHandles( const TArrayView<FRigVMMemoryHandle>& OutHandles, const TArray<FRigVMExternalVariableRuntimeData>& ExternalVariablesRuntimeData, const TStaticArray<uint8*, (int32)ERigVMMemoryType::Num>& VMMemoryPtrs, const TArray<FRigVMMemoryHandle>& PreCachedMemoryHandles, const TArray<ERigVMMemoryType>& PreCachedMemoryHandlesMemoryType, int32 FirstHandleIndex, int32 OperandCount);`
- L968 _private prototype_ `static FRigVMMemoryHandle GeneratePatchedHandle( const TArray<FRigVMExternalVariableRuntimeData>& ExternalVariablesRuntimeData, const TStaticArray<uint8*, (int32)ERigVMMemoryType::Num>& VMMemoryPtrs, ERigVMMemoryType HandleMemoryType, const FRigVMMemoryHandle& PreCachedHandle);`
- L974 _private function_ `void CopyOperandForDebuggingIfNeeded(FRigVMExtendedExecuteContext& Context, const FRigVMOperand& InArg, const FRigVMMemoryHandle& InHandle)`
- L984 _private prototype_ `void CopyOperandForDebuggingImpl(FRigVMExtendedExecuteContext& Context, const FRigVMOperand& InArg, const FRigVMMemoryHandle& InHandle, const FRigVMOperand& InDebugOperand);`
- L986 _private prototype_ `FRigVMCopyOp GetCopyOpForOperands(const FRigVMOperand& InSource, const FRigVMOperand& InTarget);`
- L987 _private prototype_ `void RefreshExternalPropertyPaths();`
- L1043 _private member_ `uint32 CachedVMHash = 0;` — `UPROPERTY()`
- L1045 _private member_ `mutable TOptional<uint32> CachedNativizedVMHash;`
- L1047 _private member_ `mutable TArray<FName> EntryNames;`
- L1049 _private member_ `bool bIsSerializing = false;`
- L1052 _protected prototype_ `const URigVMHost* GetHostCDO() const;`
- L1054 _protected prototype_ `void Reset_Internal();`
- L1055 _protected prototype_ `void ClearMemory_Internal();`
- L1056 _protected prototype_ `void InvalidateCachedMemory_Internal();`
- L1058 _protected prototype_ `void SetupInstructionTracking(FRigVMExtendedExecuteContext& Context, int32 InInstructionCount, int32 InCallableCount, const FName& InEntryName);`
- L1059 _protected prototype_ `void StartProfiling(FRigVMExtendedExecuteContext& Context);`
- L1060 _protected prototype_ `void StopProfiling(FRigVMExtendedExecuteContext& Context);`
- L1062 _protected member_ `FTransactionallySafeCriticalSection ResolveFunctionsMutex;`
- L1063 _protected member_ `mutable FTransactionallySafeCriticalSection CreateLocalizedRegistryMutex;`

#### struct `URigVM::FEntryExecuteGuard`  
`struct FEntryExecuteGuard`  
_L991-1008_
- L994 _public function_ `FEntryExecuteGuard(TArray<int32>& InOutStack, int32 InEntryIndex) : Stack(InOutStack)`
- L1000 _public function_ `~FEntryExecuteGuard()`
- L1007 _private member_ `TArray<int32>& Stack;`

#### struct `URigVM::FInstructionBracketGuard`  
`struct FInstructionBracketGuard`  
_L1011-1037_
- L1014 _public function_ `FInstructionBracketGuard(FRigVMExtendedExecuteContext& InOutContext, int32 InFirstInstruction, int32 InLastInstruction) : Context(InOutContext)`
- L1026 _public function_ `~FInstructionBracketGuard()`
- L1033 _private member_ `FRigVMExtendedExecuteContext& Context;`
- L1034 _private member_ `FString ErrorMessage;`

#### Free symbols / members of external scopes

- L87 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMParameter& P)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMAssetUserData.h` (Public)


#### class `UNameSpacedUserData`  
`class UNameSpacedUserData : public UAssetUserData`  
_L16-180_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UAssetUserData`
- desc: User data that can be attached to assets to provide namespaced data access.
- L126 _public function_ `virtual ~UNameSpacedUserData() override`
- L131 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L135 _public member_ `FString NameSpace;` — `UPROPERTY(EditAnywhere, Category = General)` — The namespace to use when looking up values inside of the user data.
- L138 _public function_ `bool ContainsUserData(const FString& InPath) const` — Returns true if userdata exists for a given path
- L141 _public prototype_ `virtual const FUserData* GetUserData(const FString& InPath, FString* OutErrorMessage = nullptr) const;` — Returns a user data path given its string path
- L144 _public prototype_ `virtual const TArray<const FUserData*>& GetUserDataArray(const FString& InParentPath = FString(), FString* OutErrorMessage = nullptr) const;` — Retrieves the user data paths given a (optional) parent path
- L147 _public function_ `const FUserData* GetParentUserData(const FString& InPath, FString* OutErrorMessage = nullptr) const` — Retrieves the user data path given the path string
- L159 _protected prototype_ `const FUserData* GetUserDataWithinStruct(const UStruct* InStruct, const uint8* InMemory, const FString& InPath, const FString& InPropertyName, FString* OutErrorMessage = nullptr) const;`
- L160 _protected prototype_ `const TArray<const FUserData*>& GetUserDataArrayWithinStruct(UStruct* InStruct, const uint8* InMemory, const FString& InPath, FString* OutErrorMessage = nullptr) const;`
- L161 _protected prototype_ `const TArray<const FUserData*>& GetUserDataArrayWithinArray(const FArrayProperty* InArrayProperty, const uint8* InMemory, const FString& InPath, FString* OutErrorMessage = nullptr) const;`
- L162 _protected prototype_ `static const FProperty* FindPropertyByName(const UStruct* InStruct, const FName& InName);`
- L164 _protected prototype_ `void InvalidateCache() const;`
- L165 _protected prototype_ `const FUserData* StoreCacheForUserData(const FUserData& InUserData) const;`
- L166 _protected prototype_ `const TArray<const FUserData*>& StoreCacheForUserDataArray(const FString& InPath, const TArray<const FUserData*>& InUserDataArray) const;`
- L167 _protected prototype_ `virtual bool IsPropertySupported(const FProperty* InProperty, const FString& InPath, bool bCheckPropertyFlags, FString* OutErrorMessage = nullptr) const;`
- L169 _protected member_ `static const TArray<const FUserData*> EmptyUserDatas;`
- L171 _protected member_ `mutable TMap<FString, FUserData*> CachedUserData;`
- L172 _protected member_ `mutable TMap<FString, TArray<const FUserData*>> CachedUserDataArray;`
- L173 _protected member_ `mutable FTransactionallySafeCriticalSection CacheLock;`
- L175 _protected member_ `static inline constexpr TCHAR PathNotFoundFormat[] = TEXT("Use`
- L176 _protected member_ `static inline constexpr TCHAR InvalidMemoryFormat[] = TEXT("Use`
- L177 _protected member_ `static inline constexpr TCHAR InvalidArrayIndexFormat[] = TEXT("Pro`
- L178 _protected member_ `static inline constexpr TCHAR OutOfBoundArrayIndexFormat[] = TEXT("Pro`
- L179 _protected member_ `static inline constexpr TCHAR UnSupportedSubPathsFormat[] = TEXT("Can`

#### struct `UNameSpacedUserData::FUserData`  
`struct FUserData`  
_L23-124_
- desc: A helper struct to represent a single user data
- L27 _public function_ `FUserData() : Path() , CPPType(NAME_None) , Property(nullptr) , Memory(nullptr)`
- L35 _public function_ `FUserData(const FString& InPath, const FProperty* InProperty, const uint8* InMemory) : Path(InPath) , CPPType(NAME_None) , Property(InProperty) , Memory(InMemory)`
- L43 _public function_ `FUserData(const FString& InPath, const FName& InCPPType, const FProperty* InProperty, const uint8* InMemory) : Path(InPath) , CPPType(InCPPType) , Property(InProperty) , Memory(InMemory)`
- L52 _public function_ `bool IsValid() const` — Returns true if this user data is mapped correctly
- L57 _public function_ `operator bool() const`
- L59 _public function_ `operator FString() const`
- L62 _public function_ `const FString& GetPath() const` — returns the string path inside of the asset user data
- L65 _public prototype_ `FString GetName() const;` — returns the name of the last segment of the path
- L70 _public prototype_ `FString GetDisplayName() const;` — returns the display name of the last segment of the path
- L75 _public function_ `const FName& GetCPPType() const` — returns the CPP type of this user data (computes it from the property as needed)
- L84 _public prototype_ `bool IsArray() const;`
- L86 _public prototype_ `bool IsArrayElement() const;`
- L88 _public prototype_ `bool IsUObject() const;`
- L91 _public function_ `const FProperty* GetProperty() const` — returns the property of this user data or nullptr
- L94 _public function_ `const uint8* GetMemory() const` — returns the mapped memory of this user data
- L97 _public function_ `static FString Join(const FString& InLeft, const FString& InRight)` — joints two user data path strings
- L105 _public function_ `static bool SplitAtStart(const FString& InPath, FString& OutLeft, FString& OutRight)` — splits a user data string path at the first segment
- L111 _public function_ `static bool SplitAtEnd(const FString& InPath, FString& OutLeft, FString& OutRight)` — splits a user data string path at the last segment
- L116 _public prototype_ `static TArray<UStruct*> GetSuperStructs(UStruct* InStruct);`
- L120 _private member_ `FString Path;`
- L121 _private member_ `mutable FName CPPType;`
- L122 _private member_ `const FProperty* Property;`
- L123 _private member_ `const uint8* Memory;`

#### class `UDataAssetLink`  
`class UDataAssetLink : public UNameSpacedUserData`  
_L186-217_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UNameSpacedUserData`
- desc: Namespaced user data which provides access to a linked data asset
- L194 _public member_ `TSoftObjectPtr<UDataAsset> DataAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, BlueprintGetter = GetDataAsset, BlueprintSetter = SetDataAsset, Meta = (DisplayAfter="NameSpace"))` — If assigned, the data asset link will provide access to the data asset's content.
- L197 _public function_ `TSoftObjectPtr<UDataAsset> GetDataAsset() const` — `UFUNCTION(BlueprintGetter)`
- L200 _public prototype_ `void SetDataAsset(TSoftObjectPtr<UDataAsset> InDataAsset);` — `UFUNCTION(BlueprintSetter)`
- L202 _public prototype_ `virtual const FUserData* GetUserData(const FString& InPath, FString* OutErrorMessage = nullptr) const override;`
- L203 _public prototype_ `virtual const TArray<const FUserData*>& GetUserDataArray(const FString& InParentPath = FString(), FString* OutErrorMessage = nullptr) const override;`
- L205 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L207 _public function_ `virtual bool IsPostLoadThreadSafe() const override`
- L208 _public prototype_ `virtual void PostLoad() override;`
- L209 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L214 _protected member_ `TObjectPtr<UDataAsset> DataAssetCached;` — `UPROPERTY()`
- L216 _protected member_ `static inline constexpr TCHAR DataAssetNullFormat[] = TEXT("Use`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMByteCode.h` (Public)


#### struct `FRigVMBranchInfoKey`  
`struct FRigVMBranchInfoKey`  
_L33-98_
- L35 _public function_ `FRigVMBranchInfoKey() : InstructionIndex(INDEX_NONE) , ArgumentIndex(INDEX_NONE) , Label(NAME_None)`
- L41 _public function_ `FRigVMBranchInfoKey(int32 InInstructionIndex, int32 InArgumentIndex) : InstructionIndex(InInstructionIndex) , ArgumentIndex(InArgumentIndex) , Label(NAME_None)`
- L47 _public function_ `FRigVMBranchInfoKey(int32 InInstructionIndex, const FName& InLabel) : InstructionIndex(InInstructionIndex) , ArgumentIndex(INDEX_NONE) , Label(InLabel)`
- L53 _public function_ `FRigVMBranchInfoKey(int32 InInstructionIndex, int32 InArgumentIndex, const FName& InLabel) : InstructionIndex(InInstructionIndex) , ArgumentIndex(InArgumentIndex) , Label(InLabel)`
- L59 _public function_ `bool IsValid() const`
- L75 _public function_ `bool operator ==(const FRigVMBranchInfoKey& InOther) const`
- L95 _public member_ `int32 InstructionIndex;`
- L96 _public member_ `int32 ArgumentIndex;`
- L97 _public member_ `FName Label;`

#### struct `FRigVMPredicateBranch`  
`struct FRigVMPredicateBranch`  
_L102-118_
- reflection: `USTRUCT()`
- desc: A description of a predicate branch in the VM's bytecode
- L106 _public function_ `FRigVMPredicateBranch() : VM(nullptr)`
- L112 _public prototype_ `ERigVMExecuteResult Execute(FRigVMExtendedExecuteContext& Context);`
- L113 _public function_ `bool IsValid()`
- L115 _public member_ `FRigVMBranchInfo BranchInfo;`
- L116 _public member_ `FRigVMMemoryHandleArray MemoryHandles;`
- L117 _public member_ `URigVM* VM;`

#### struct `FRigVMCallableArgument`  
`struct FRigVMCallableArgument`  
_L122-173_
- reflection: `USTRUCT()`
- desc: An argument for a callable in the bytecode.
- L126 _public function_ `FRigVMCallableArgument() : Name(NAME_None) , Direction(ERigVMPinDirection::Invalid)`
- L132 _public member_ `FName Name;` — `UPROPERTY()`
- L135 _public member_ `FString TypeString;` — `UPROPERTY()`
- L138 _public member_ `FRigVMOperand InterfaceOperand;` — `UPROPERTY()`
- L141 _public member_ `FRigVMOperand ForwardedOperand;` — `UPROPERTY()`
- L144 _public member_ `ERigVMPinDirection Direction;` — `UPROPERTY()`
- L146 _public prototype_ `void Serialize(FArchive& Ar);`
- L153 _public function_ `bool IsInput() const`
- L158 _public function_ `bool IsOutput() const`

#### struct `FRigVMCallableInfo`  
`struct FRigVMCallableInfo`  
_L178-246_
- reflection: `USTRUCT()`
- desc: A callable section of the rigvm bytecode. This is used to represent functions and events with arguments.
- L182 _public function_ `FRigVMCallableInfo() : Index(INDEX_NONE) , Name(NAME_None) , FunctionHash(0) , FirstInstruction(INDEX_NONE) , LastInstruction(INDEX_NONE)`
- L191 _public function_ `FRigVMCallableInfo(int32 InIndex, const FName& InName, uint32 InHash, int32 InFirstInstruction, int32 InLastInstruction) : Index(InIndex) , Name(InName) , FunctionHash(InHash) , FirstInstruction(InFirstInstruction) , LastInstruction(InLastInstruction)`
- L201 _public member_ `int32 Index;` — `UPROPERTY()`
- L204 _public member_ `FName Name;` — `UPROPERTY()`
- L207 _public member_ `uint32 FunctionHash;` — `UPROPERTY()`
- L210 _public member_ `TArray<FRigVMCallableArgument> Arguments;` — `UPROPERTY()`
- L213 _public member_ `int32 FirstInstruction;` — `UPROPERTY()`
- L216 _public member_ `int32 LastInstruction;` — `UPROPERTY()`
- L218 _public prototype_ `int32 GetArgumentIndex(const FName& InName) const;`
- L219 _public prototype_ `const FRigVMCallableArgument* FindArgument(const FName& InName) const;`
- L220 _public function_ `int32 GetNumInstructions() const`
- L225 _public prototype_ `void Serialize(FArchive& Ar);`

#### enum `ERigVMOpCode`  
`enum class ERigVMOpCode : uint8`  
_L250-360_
- reflection: `UENUM()`
- desc: The code for a single operation within the RigVM
- L252 _public enumerator_ `Execute_0_Operands` — (DEPRECATED) execute a rig function with 0 operands
- L253 _public enumerator_ `Execute_1_Operands` — (DEPRECATED) execute a rig function with 1 operands
- L254 _public enumerator_ `Execute_2_Operands` — (DEPRECATED) execute a rig function with 2 operands
- L255 _public enumerator_ `Execute_3_Operands` — (DEPRECATED) execute a rig function with 3 operands
- L256 _public enumerator_ `Execute_4_Operands` — (DEPRECATED) execute a rig function with 4 operands
- L257 _public enumerator_ `Execute_5_Operands` — (DEPRECATED) execute a rig function with 5 operands
- L258 _public enumerator_ `Execute_6_Operands` — (DEPRECATED) execute a rig function with 6 operands
- L259 _public enumerator_ `Execute_7_Operands` — (DEPRECATED) execute a rig function with 7 operands
- L260 _public enumerator_ `Execute_8_Operands` — (DEPRECATED) execute a rig function with 8 operands
- L261 _public enumerator_ `Execute_9_Operands` — (DEPRECATED) execute a rig function with 9 operands
- L262 _public enumerator_ `Execute_10_Operands` — (DEPRECATED) execute a rig function with 10 operands
- L263 _public enumerator_ `Execute_11_Operands` — (DEPRECATED) execute a rig function with 11 operands
- L264 _public enumerator_ `Execute_12_Operands` — (DEPRECATED) execute a rig function with 12 operands
- L265 _public enumerator_ `Execute_13_Operands` — (DEPRECATED) execute a rig function with 13 operands
- L266 _public enumerator_ `Execute_14_Operands` — (DEPRECATED) execute a rig function with 14 operands
- L267 _public enumerator_ `Execute_15_Operands` — (DEPRECATED) execute a rig function with 15 operands
- L268 _public enumerator_ `Execute_16_Operands` — (DEPRECATED) execute a rig function with 16 operands
- L269 _public enumerator_ `Execute_17_Operands` — (DEPRECATED) execute a rig function with 17 operands
- L270 _public enumerator_ `Execute_18_Operands` — (DEPRECATED) execute a rig function with 18 operands
- L271 _public enumerator_ `Execute_19_Operands` — (DEPRECATED) execute a rig function with 19 operands
- L272 _public enumerator_ `Execute_20_Operands` — (DEPRECATED) execute a rig function with 20 operands
- L273 _public enumerator_ `Execute_21_Operands` — (DEPRECATED) execute a rig function with 21 operands
- L274 _public enumerator_ `Execute_22_Operands` — (DEPRECATED) execute a rig function with 22 operands
- L275 _public enumerator_ `Execute_23_Operands` — (DEPRECATED) execute a rig function with 23 operands
- L276 _public enumerator_ `Execute_24_Operands` — (DEPRECATED) execute a rig function with 24 operands
- L277 _public enumerator_ `Execute_25_Operands` — (DEPRECATED) execute a rig function with 25 operands
- L278 _public enumerator_ `Execute_26_Operands` — (DEPRECATED) execute a rig function with 26 operands
- L279 _public enumerator_ `Execute_27_Operands` — (DEPRECATED) execute a rig function with 27 operands
- L280 _public enumerator_ `Execute_28_Operands` — (DEPRECATED) execute a rig function with 28 operands
- L281 _public enumerator_ `Execute_29_Operands` — (DEPRECATED) execute a rig function with 29 operands
- L282 _public enumerator_ `Execute_30_Operands` — (DEPRECATED) execute a rig function with 30 operands
- L283 _public enumerator_ `Execute_31_Operands` — (DEPRECATED) execute a rig function with 31 operands
- L284 _public enumerator_ `Execute_32_Operands` — (DEPRECATED) execute a rig function with 32 operands
- L285 _public enumerator_ `Execute_33_Operands` — (DEPRECATED) execute a rig function with 33 operands
- L286 _public enumerator_ `Execute_34_Operands` — (DEPRECATED) execute a rig function with 34 operands
- L287 _public enumerator_ `Execute_35_Operands` — (DEPRECATED) execute a rig function with 35 operands
- L288 _public enumerator_ `Execute_36_Operands` — (DEPRECATED) execute a rig function with 36 operands
- L289 _public enumerator_ `Execute_37_Operands` — (DEPRECATED) execute a rig function with 37 operands
- L290 _public enumerator_ `Execute_38_Operands` — (DEPRECATED) execute a rig function with 38 operands
- L291 _public enumerator_ `Execute_39_Operands` — (DEPRECATED) execute a rig function with 39 operands
- L292 _public enumerator_ `Execute_40_Operands` — (DEPRECATED) execute a rig function with 40 operands
- L293 _public enumerator_ `Execute_41_Operands` — (DEPRECATED) execute a rig function with 41 operands
- L294 _public enumerator_ `Execute_42_Operands` — (DEPRECATED) execute a rig function with 42 operands
- L295 _public enumerator_ `Execute_43_Operands` — (DEPRECATED) execute a rig function with 43 operands
- L296 _public enumerator_ `Execute_44_Operands` — (DEPRECATED) execute a rig function with 44 operands
- L297 _public enumerator_ `Execute_45_Operands` — (DEPRECATED) execute a rig function with 45 operands
- L298 _public enumerator_ `Execute_46_Operands` — (DEPRECATED) execute a rig function with 46 operands
- L299 _public enumerator_ `Execute_47_Operands` — (DEPRECATED) execute a rig function with 47 operands
- L300 _public enumerator_ `Execute_48_Operands` — (DEPRECATED) execute a rig function with 48 operands
- L301 _public enumerator_ `Execute_49_Operands` — (DEPRECATED) execute a rig function with 49 operands
- L302 _public enumerator_ `Execute_50_Operands` — (DEPRECATED) execute a rig function with 50 operands
- L303 _public enumerator_ `Execute_51_Operands` — (DEPRECATED) execute a rig function with 51 operands
- L304 _public enumerator_ `Execute_52_Operands` — (DEPRECATED) execute a rig function with 52 operands
- L305 _public enumerator_ `Execute_53_Operands` — (DEPRECATED) execute a rig function with 53 operands
- L306 _public enumerator_ `Execute_54_Operands` — (DEPRECATED) execute a rig function with 54 operands
- L307 _public enumerator_ `Execute_55_Operands` — (DEPRECATED) execute a rig function with 55 operands
- L308 _public enumerator_ `Execute_56_Operands` — (DEPRECATED) execute a rig function with 56 operands
- L309 _public enumerator_ `Execute_57_Operands` — (DEPRECATED) execute a rig function with 57 operands
- L310 _public enumerator_ `Execute_58_Operands` — (DEPRECATED) execute a rig function with 58 operands
- L311 _public enumerator_ `Execute_59_Operands` — (DEPRECATED) execute a rig function with 59 operands
- L312 _public enumerator_ `Execute_60_Operands` — (DEPRECATED) execute a rig function with 60 operands
- L313 _public enumerator_ `Execute_61_Operands` — (DEPRECATED) execute a rig function with 61 operands
- L314 _public enumerator_ `Execute_62_Operands` — (DEPRECATED) execute a rig function with 62 operands
- L315 _public enumerator_ `Execute_63_Operands` — (DEPRECATED) execute a rig function with 63 operands
- L316 _public enumerator_ `Execute_64_Operands` — (DEPRECATED) execute a rig function with 64 operands
- L317 _public enumerator_ `Zero` — zero the memory of a given register
- L318 _public enumerator_ `BoolFalse` — set a given register to false
- L319 _public enumerator_ `BoolTrue` — set a given register to true
- L320 _public enumerator_ `Copy` — copy the content of one register to another
- L321 _public enumerator_ `Increment` — increment a int32 register
- L322 _public enumerator_ `Decrement` — decrement a int32 register
- L323 _public enumerator_ `Equals` — fill a bool register with the result of (A == B)
- L324 _public enumerator_ `NotEquals` — fill a bool register with the result of (A != B)
- L325 _public enumerator_ `JumpAbsolute` — jump to an absolute instruction index
- L326 _public enumerator_ `JumpForward` — jump forwards given a relative instruction index offset
- L327 _public enumerator_ `JumpBackward` — jump backwards given a relative instruction index offset
- L328 _public enumerator_ `JumpAbsoluteIf` — jump to an absolute instruction index based on a condition register
- L329 _public enumerator_ `JumpForwardIf` — jump forwards given a relative instruction index offset based on a condition register
- L330 _public enumerator_ `JumpBackwardIf` — jump backwards given a relative instruction index offset based on a condition register
- L331 _public enumerator_ `ChangeType` — change the type of a register (deprecated)
- L332 _public enumerator_ `Exit` — exit the execution loop
- L333 _public enumerator_ `BeginBlock` — begins a new memory slice / block
- L334 _public enumerator_ `EndBlock` — ends the last memory slice / block
- L335 _public enumerator_ `ArrayReset` — (DEPRECATED) clears an array and resets its content
- L336 _public enumerator_ `ArrayGetNum` — (DEPRECATED) reads and returns the size of an array (binary op, in array, out int32)
- L337 _public enumerator_ `ArraySetNum` — (DEPRECATED) resizes an array (binary op, in out array, in int32)
- L338 _public enumerator_ `ArrayGetAtIndex` — (DEPRECATED) returns an array element by index (ternary op, in array, in int32, out element)
- L339 _public enumerator_ `ArraySetAtIndex` — (DEPRECATED) sets an array element by index (ternary op, in out array, in int32, in element)
- L340 _public enumerator_ `ArrayAdd` — (DEPRECATED) adds an element to an array (ternary op, in out array, in element, out int32 index)
- L341 _public enumerator_ `ArrayInsert` — (DEPRECATED) inserts an element to an array (ternary op, in out array, in int32, in element)
- L342 _public enumerator_ `ArrayRemove` — (DEPRECATED) removes an element from an array (binary op, in out array, in inindex)
- L343 _public enumerator_ `ArrayFind` — (DEPRECATED) finds and returns the index of an element (quaternery op, in array, in element, out int32 index, out bool success)
- L344 _public enumerator_ `ArrayAppend` — (DEPRECATED) appends an array to another (binary op, in out array, in array)
- L345 _public enumerator_ `ArrayClone` — (DEPRECATED) clones an array (binary op, in array, out array)
- L346 _public enumerator_ `ArrayIterator` — (DEPRECATED) iterates over an array (senary op, in array, out element, out index, out count, out ratio, out continue)
- L347 _public enumerator_ `ArrayUnion` — (DEPRECATED) merges two arrays while avoiding duplicates (binary op, in out array, in other array)
- L348 _public enumerator_ `ArrayDifference` — (DEPRECATED) returns a new array containing elements only found in one array (ternary op, in array, in array, out result)
- L349 _public enumerator_ `ArrayIntersection` — (DEPRECATED) returns a new array containing elements found in both of the input arrays (ternary op, in array, in array, out result)
- L350 _public enumerator_ `ArrayReverse` — (DEPRECATED) returns the reverse of the input array (unary op, in out array)
- L351 _public enumerator_ `InvokeEntry` — invokes an entry from the entry list
- L352 _public enumerator_ `JumpToBranch` — jumps to a branch based on a name operand
- L353 _public enumerator_ `Execute` — single execute op (formerly Execute_0_Operands to Execute_64_Operands)
- L354 _public enumerator_ `RunInstructions` — runs a set of instructions lazily
- L355 _public enumerator_ `SetupTraits` — sets up a list of traits on executecontext
- L356 _public enumerator_ `InvokeCallable` — invoke a section of the bytecode as a callable
- L357 _public enumerator_ `Invalid`
- L358 _public enumerator_ `FirstArrayOpCode = ArrayReset`
- L359 _public enumerator_ `LastArrayOpCode = ArrayReverse`

#### struct `FRigVMBaseOp`  
`struct FRigVMBaseOp`  
_L364-384_
- reflection: `USTRUCT()`
- desc: Base class for all VM operations
- L368 _public function_ `FRigVMBaseOp(ERigVMOpCode InOpCode = ERigVMOpCode::Invalid) : OpCode(InOpCode)`
- L373 _public member_ `ERigVMOpCode OpCode;`
- L380 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`

#### struct `FRigVMInvokeCallableOp`  
`struct FRigVMInvokeCallableOp : public FRigVMBaseOp`  
_L388-441_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseOp`
- desc: invoke a callable
- L392 _public function_ `FRigVMInvokeCallableOp() : FRigVMBaseOp() , CallableIndex(0) , ArgumentCount(0)`
- L399 _public function_ `FRigVMInvokeCallableOp(uint16 InCallableIndex, uint16 InArgumentCount) : FRigVMBaseOp(ERigVMOpCode::InvokeCallable) , CallableIndex(InCallableIndex) , ArgumentCount(InArgumentCount)`
- L406 _public function_ `FRigVMInvokeCallableOp(ERigVMOpCode InOpCode, uint16 InCallableIndex, uint16 InArgumentCount) : FRigVMBaseOp(InOpCode) , CallableIndex(InCallableIndex) , ArgumentCount(InArgumentCount)`
- L413 _public member_ `uint16 CallableIndex;`
- L414 _public member_ `uint16 ArgumentCount;`
- L427 _public function_ `uint16 GetOperandCount() const`
- L429 _public prototype_ `void Serialize(FArchive& Ar);`
- L436 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`

#### struct `FRigVMExecuteOp`  
`struct FRigVMExecuteOp : public FRigVMInvokeCallableOp`  
_L445-472_
- reflection: `USTRUCT()`
- inherits: `FRigVMInvokeCallableOp`
- desc: execute a function
- L449 _public function_ `FRigVMExecuteOp() : FRigVMInvokeCallableOp() , FirstPredicateIndex(INDEX_NONE) , PredicateCount(0)`
- L456 _public function_ `FRigVMExecuteOp(uint16 InFunctionIndex, uint16 InArgumentCount) : FRigVMInvokeCallableOp(ERigVMOpCode::Execute, InFunctionIndex, InArgumentCount) , FirstPredicateIndex(INDEX_NONE) , PredicateCount(0)`
- L463 _public member_ `uint16 FirstPredicateIndex;`
- L464 _public member_ `uint16 PredicateCount;`
- L466 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FRigVMUnaryOp`  
`struct FRigVMUnaryOp : public FRigVMBaseOp`  
_L476-526_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseOp`
- desc: operator used for zero, false, true, increment, decrement
- L480 _public function_ `FRigVMUnaryOp() : FRigVMBaseOp(ERigVMOpCode::Invalid) , Arg()`
- L486 _public function_ `FRigVMUnaryOp(ERigVMOpCode InOpCode, FRigVMOperand InArg) : FRigVMBaseOp(InOpCode) , Arg(InArg)`
- L506 _public member_ `FRigVMOperand Arg;`
- L513 _public prototype_ `void Serialize(FArchive& Ar);`
- L520 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`

#### struct `FRigVMBinaryOp`  
`struct FRigVMBinaryOp : public FRigVMBaseOp`  
_L530-573_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseOp`
- desc: operator used for beginblock and array reset
- L534 _public function_ `FRigVMBinaryOp() : FRigVMBaseOp(ERigVMOpCode::Invalid) , ArgA() , ArgB()`
- L541 _public function_ `FRigVMBinaryOp(ERigVMOpCode InOpCode, FRigVMOperand InArgA, FRigVMOperand InArgB) : FRigVMBaseOp(InOpCode) , ArgA(InArgA) , ArgB(InArgB)`
- L548 _public member_ `FRigVMOperand ArgA;`
- L549 _public member_ `FRigVMOperand ArgB;`
- L559 _public prototype_ `void Serialize(FArchive& Ar);`
- L566 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`

#### struct `FRigVMTernaryOp`  
`struct FRigVMTernaryOp : public FRigVMBaseOp`  
_L577-625_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseOp`
- desc: operator used for some array operations
- L581 _public function_ `FRigVMTernaryOp() : FRigVMBaseOp(ERigVMOpCode::Invalid) , ArgA() , ArgB() , ArgC()`
- L589 _public function_ `FRigVMTernaryOp(ERigVMOpCode InOpCode, FRigVMOperand InArgA, FRigVMOperand InArgB, FRigVMOperand InArgC) : FRigVMBaseOp(InOpCode) , ArgA(InArgA) , ArgB(InArgB) , ArgC(InArgC)`
- L597 _public member_ `FRigVMOperand ArgA;`
- L598 _public member_ `FRigVMOperand ArgB;`
- L599 _public member_ `FRigVMOperand ArgC;`
- L610 _public prototype_ `void Serialize(FArchive& Ar);`
- L617 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`

#### struct `FRigVMQuaternaryOp`  
`struct FRigVMQuaternaryOp : public FRigVMBaseOp`  
_L629-683_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseOp`
- desc: operator used for some array operations
- L633 _public function_ `FRigVMQuaternaryOp() : FRigVMBaseOp(ERigVMOpCode::Invalid) , ArgA() , ArgB() , ArgC() , ArgD()`
- L642 _public function_ `FRigVMQuaternaryOp(ERigVMOpCode InOpCode, FRigVMOperand InArgA, FRigVMOperand InArgB, FRigVMOperand InArgC, FRigVMOperand InArgD) : FRigVMBaseOp(InOpCode) , ArgA(InArgA) , ArgB(InArgB) , ArgC(InArgC) , ArgD(InArgD)`
- L652 _public member_ `FRigVMOperand ArgA;`
- L653 _public member_ `FRigVMOperand ArgB;`
- L654 _public member_ `FRigVMOperand ArgC;`
- L655 _public member_ `FRigVMOperand ArgD;`
- L667 _public prototype_ `void Serialize(FArchive& Ar);`
- L674 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`

#### struct `FRigVMQuinaryOp`  
`struct FRigVMQuinaryOp : public FRigVMBaseOp`  
_L687-745_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseOp`
- desc: operator used for some array operations
- L691 _public function_ `FRigVMQuinaryOp() : FRigVMBaseOp(ERigVMOpCode::Invalid) , ArgA() , ArgB() , ArgC() , ArgD() , ArgE()`
- L701 _public function_ `FRigVMQuinaryOp(ERigVMOpCode InOpCode, FRigVMOperand InArgA, FRigVMOperand InArgB, FRigVMOperand InArgC, FRigVMOperand InArgD, FRigVMOperand InArgE) : FRigVMBaseOp(InOpCode) , ArgA(InArgA) , ArgB(InArgB) , ArgC(InArgC) , ArgD(InArgD) , ArgE(InArgE)`
- L711 _public member_ `FRigVMOperand ArgA;`
- L712 _public member_ `FRigVMOperand ArgB;`
- L713 _public member_ `FRigVMOperand ArgC;`
- L714 _public member_ `FRigVMOperand ArgD;`
- L715 _public member_ `FRigVMOperand ArgE;`
- L728 _public prototype_ `void Serialize(FArchive& Ar);`
- L735 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`

#### struct `FRigVMSenaryOp`  
`struct FRigVMSenaryOp : public FRigVMBaseOp`  
_L749-812_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseOp`
- desc: operator used for some array operations
- L753 _public function_ `FRigVMSenaryOp() : FRigVMBaseOp(ERigVMOpCode::Invalid) , ArgA() , ArgB() , ArgC() , ArgD() , ArgE() , ArgF()`
- L764 _public function_ `FRigVMSenaryOp(ERigVMOpCode InOpCode, FRigVMOperand InArgA, FRigVMOperand InArgB, FRigVMOperand InArgC, FRigVMOperand InArgD, FRigVMOperand InArgE, FRigVMOperand InArgF) : FRigVMBaseOp(InOpCode) , ArgA(InArgA) , ArgB(InArgB) , ArgC(InArgC) , ArgD(InArgD) , ArgE(InArgE) , ArgF(InArgF)`
- L775 _public member_ `FRigVMOperand ArgA;`
- L776 _public member_ `FRigVMOperand ArgB;`
- L777 _public member_ `FRigVMOperand ArgC;`
- L778 _public member_ `FRigVMOperand ArgD;`
- L779 _public member_ `FRigVMOperand ArgE;`
- L780 _public member_ `FRigVMOperand ArgF;`
- L794 _public prototype_ `void Serialize(FArchive& Ar);`
- L801 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`

#### enum `ERigVMCopyType`  
`enum class ERigVMCopyType : uint8`  
_L816-821_
- reflection: `UENUM()`
- desc: The kind of copy operation to perform
- L818 _public enumerator_ `Default`
- L819 _public enumerator_ `FloatToDouble`
- L820 _public enumerator_ `DoubleToFloat`

#### struct `FRigVMCopyOp`  
`struct FRigVMCopyOp : public FRigVMBaseOp`  
_L825-893_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseOp`
- desc: copy the content of one register to another
- L831 _public function_ `FRigVMCopyOp() : FRigVMBaseOp(ERigVMOpCode::Copy) , Source() , Target() , RegisterType(ERigVMRegisterType::Invalid) , CopyType(ERigVMCopyType::Default)`
- L840 _public function_ `FRigVMCopyOp( FRigVMOperand InSource, FRigVMOperand InTarget ) : FRigVMBaseOp(ERigVMOpCode::Copy) , Source(InSource) , Target(InTarget) , RegisterType(ERigVMRegisterType::Invalid) , CopyType(ERigVMCopyType::Default)`
- L852 _public function_ `bool IsValid() const`
- L861 _public member_ `FRigVMOperand Source;`
- L862 _public member_ `FRigVMOperand Target;`
- L873 _private member_ `ERigVMRegisterType RegisterType;`
- L874 _private member_ `ERigVMCopyType CopyType;`
- L877 _public prototype_ `void Serialize(FArchive& Ar);`
- L884 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`

#### struct `FRigVMComparisonOp`  
`struct FRigVMComparisonOp : public FRigVMBaseOp`  
_L897-954_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseOp`
- desc: used for equals and not equals comparisons
- L901 _public function_ `FRigVMComparisonOp() : FRigVMBaseOp(ERigVMOpCode::Invalid) , A() , B() , Result()`
- L909 _public function_ `FRigVMComparisonOp( ERigVMOpCode InOpCode, FRigVMOperand InA, FRigVMOperand InB, FRigVMOperand InResult ) : FRigVMBaseOp(InOpCode) , A(InA) , B(InB) , Result(InResult)`
- L926 _public member_ `FRigVMOperand A;`
- L927 _public member_ `FRigVMOperand B;`
- L928 _public member_ `FRigVMOperand Result;`
- L939 _public prototype_ `void Serialize(FArchive& Ar);`
- L946 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`

#### struct `FRigVMJumpOp`  
`struct FRigVMJumpOp : public FRigVMBaseOp`  
_L960-1023_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseOp`
- desc: jump to a new instruction index. the instruction can be absolute, relative forward or relative backward based on the opcode
- L964 _public function_ `FRigVMJumpOp() : FRigVMBaseOp(ERigVMOpCode::Invalid) , InstructionIndex(INDEX_NONE)`
- L970 _public function_ `FRigVMJumpOp(ERigVMOpCode InOpCode, int32 InInstructionIndex) : FRigVMBaseOp(InOpCode) , InstructionIndex(InInstructionIndex)`
- L978 _public member_ `int32 InstructionIndex;`
- L987 _public prototype_ `void Serialize(FArchive& Ar);`
- L994 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`
- L1000 _public function_ `static int32 GetTargetInstruction(ERigVMOpCode InOpCode, const int32 InCurrentInstruction, const int32 InOpJumpIndex)`

#### struct `FRigVMJumpIfOp`  
`struct FRigVMJumpIfOp : public FRigVMUnaryOp`  
_L1029-1073_
- reflection: `USTRUCT()`
- inherits: `FRigVMUnaryOp`
- desc: jump to a new instruction index based on a condition. the instruction can be absolute, relative forward or relative backward based on the opcode
- L1033 _public function_ `FRigVMJumpIfOp() : InstructionIndex(INDEX_NONE) , Condition(true)`
- L1039 _public function_ `FRigVMJumpIfOp(ERigVMOpCode InOpCode, FRigVMOperand InConditionArg, int32 InInstructionIndex, bool InCondition = false) : FRigVMUnaryOp(InOpCode, InConditionArg) , InstructionIndex(InInstructionIndex) , Condition(InCondition)`
- L1048 _public member_ `int32 InstructionIndex;`
- L1049 _public member_ `bool Condition;`
- L1059 _public prototype_ `void Serialize(FArchive& Ar);`
- L1066 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`

#### struct `FRigVMChangeTypeOp`  
`struct FRigVMChangeTypeOp : public FRigVMUnaryOp`  
_L1077-1087_
- reflection: `USTRUCT()`
- inherits: `FRigVMUnaryOp`
- desc: change the type of a register
- L1081 _public prototype_ `static void Serialize(FArchive& Ar);`

#### struct `FRigVMInvokeEntryOp`  
`struct FRigVMInvokeEntryOp : public FRigVMBaseOp`  
_L1091-1124_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseOp`
- desc: invoke another entry
- L1095 _public function_ `FRigVMInvokeEntryOp() : FRigVMBaseOp(ERigVMOpCode::InvokeEntry) , EntryName(NAME_None)`
- L1100 _public function_ `FRigVMInvokeEntryOp(FName InEntryName) : FRigVMBaseOp(ERigVMOpCode::InvokeEntry) , EntryName(InEntryName)`
- L1105 _public member_ `FName EntryName;`
- L1112 _public prototype_ `void Serialize(FArchive& Ar);`
- L1119 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMBaseOp* InMemory)`

#### struct `FRigVMJumpToBranchOp`  
`struct FRigVMJumpToBranchOp : public FRigVMUnaryOp`  
_L1128-1159_
- reflection: `USTRUCT()`
- inherits: `FRigVMUnaryOp`
- desc: jump into a branch based on a name argument
- L1132 _public function_ `FRigVMJumpToBranchOp() : FRigVMUnaryOp() , FirstBranchInfoIndex(INDEX_NONE)`
- L1138 _public function_ `FRigVMJumpToBranchOp(FRigVMOperand InBranchNameArg, int32 InFirstBranchInfoIndex) : FRigVMUnaryOp(ERigVMOpCode::JumpToBranch, InBranchNameArg) , FirstBranchInfoIndex(InFirstBranchInfoIndex)`
- L1144 _public member_ `int32 FirstBranchInfoIndex;`
- L1153 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FRigVMRunInstructionsOp`  
`struct FRigVMRunInstructionsOp : public FRigVMUnaryOp`  
_L1163-1198_
- reflection: `USTRUCT()`
- inherits: `FRigVMUnaryOp`
- desc: runs a set of instructions lazily
- L1167 _public function_ `FRigVMRunInstructionsOp() : FRigVMUnaryOp() , StartInstruction(INDEX_NONE) , EndInstruction(INDEX_NONE)`
- L1174 _public function_ `FRigVMRunInstructionsOp(FRigVMOperand InExecutionStateArg, int32 InStartInstruction, int32 InEndInstruction) : FRigVMUnaryOp(ERigVMOpCode::RunInstructions, InExecutionStateArg) , StartInstruction(InStartInstruction) , EndInstruction(InEndInstruction)`
- L1181 _public member_ `int32 StartInstruction;`
- L1182 _public member_ `int32 EndInstruction;`
- L1192 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FRigVMSetupTraitsOp`  
`struct FRigVMSetupTraitsOp : public FRigVMUnaryOp`  
_L1202-1215_
- reflection: `USTRUCT()`
- inherits: `FRigVMUnaryOp`
- desc: sets up a list of traits in the execute context
- L1206 _public function_ `FRigVMSetupTraitsOp() : FRigVMUnaryOp()`
- L1211 _public function_ `FRigVMSetupTraitsOp(FRigVMOperand InTraitListArg) : FRigVMUnaryOp(ERigVMOpCode::SetupTraits, InTraitListArg)`

#### struct `FRigVMInstruction`  
`struct FRigVMInstruction`  
_L1222-1245_
- reflection: `USTRUCT()`
- desc: The FRigVMInstruction represents a single instruction within the VM.
- L1226 _public function_ `FRigVMInstruction(ERigVMOpCode InOpCode = ERigVMOpCode::Invalid, int32 InIndex = INDEX_NONE, int32 InByteCodeIndex = INDEX_NONE, uint8 InOperandAlignment = 0) : Index(InIndex) , ByteCodeIndex(InByteCodeIndex) , OpCode(InOpCode) , OperandAlignment(InOperandAlignment)`
- L1235 _public member_ `int32 Index;` — `UPROPERTY()`
- L1238 _public member_ `int32 ByteCodeIndex;` — `UPROPERTY()`
- L1241 _public member_ `ERigVMOpCode OpCode;` — `UPROPERTY()`
- L1244 _public member_ `uint8 OperandAlignment;` — `UPROPERTY()`

#### struct `FRigVMInstructionArray`  
`struct FRigVMInstructionArray`  
_L1253-1290_
- reflection: `USTRUCT()`
- desc: The FRigVMInstructionArray represents all current instructions within a RigVM and can be used to iterate over all operators and retrieve each instruction's data.
- L1259 _public prototype_ `FRigVMInstructionArray();`
- L1262 _public prototype_ `void Reset();` — Resets the data structure and maintains all storage.
- L1265 _public prototype_ `void Empty();` — Resets the data structure and removes all storage.
- L1268 _public function_ `bool IsValidIndex(int32 InIndex) const` — Returns true if a given instruction index is valid.
- L1271 _public function_ `int32 Num() const` — Returns the number of instructions.
- L1274 _public function_ `const FRigVMInstruction& operator[](int32 InIndex) const` — const accessor for an instruction given its index
- L1276 _public function_ `TArray<FRigVMInstruction>::RangedForConstIteratorType begin() const`
- L1277 _public function_ `TArray<FRigVMInstruction>::RangedForConstIteratorType end() const`
- L1279 _public function_ `const FRigVMInstruction* GetData() const`
- L1284 _private prototype_ `FRigVMInstructionArray(const FRigVMByteCode& InByteCode, bool bByteCodeIsAligned = true);` — hide utility constructor
- L1287 _private member_ `TArray<FRigVMInstruction> Instructions;` — `UPROPERTY()`

#### struct `FRigVMByteCodeEntry`  
`struct FRigVMByteCodeEntry`  
_L1293-1309_
- reflection: `USTRUCT()`
- L1297 _public function_ `FRigVMByteCodeEntry() : Name(NAME_None) , InstructionIndex(0)`
- L1303 _public member_ `FName Name;` — `UPROPERTY()`
- L1306 _public member_ `int32 InstructionIndex;` — `UPROPERTY()`
- L1308 _public prototype_ `FString GetSanitizedName() const;`

#### struct `FRigVMByteCode`  
`struct FRigVMByteCode`  
_L1318-1837_
- reflection: `USTRUCT()`
- desc: The FRigVMByteCode is a container to store a list of instructions with their corresponding data. The byte code is then used within a VM to execute. To iterate over the instructions within the byte code you can use GetInstructions() to retrieve a FRigVMInstructionArray.
- L1324 _public prototype_ `FRigVMByteCode();`
- L1326 _public prototype_ `void Serialize(FArchive& Ar);`
- L1327 _public prototype_ `void Save(FArchive& Ar);`
- L1328 _public prototype_ `void Load(FArchive& Ar);`
- L1336 _public prototype_ `void Reset();` — resets the container and maintains all memory
- L1339 _public prototype_ `void Empty();` — resets the container and removes all memory
- L1342 _public prototype_ `void Shrink();` — shrinks the container and reduces the memory
- L1345 _public prototype_ `uint32 GetByteCodeHash() const;` — returns a unique hash identifying this bytecode
- L1348 _public prototype_ `uint32 GetOperatorHash(const FRigVMInstruction& InInstruction) const;` — returns a unique hash for an operator at a given instruction index
- L1357 _public prototype_ `int32 Num() const;` — returns the number of instructions in this container
- L1360 _public function_ `const uint8& operator[](int32 InIndex) const` — const accessor for a byte given its index
- L1363 _public prototype_ `int32 NumEntries() const;` — returns the number of entries
- L1366 _public prototype_ `const FRigVMByteCodeEntry& GetEntry(int32 InEntryIndex) const;` — returns the entry with a given index
- L1369 _public prototype_ `int32 FindEntryIndex(const FName& InEntryName) const;` — returns the index of an entry given a name or INDEX_NONE
- L1372 _public prototype_ `int32 NumCallables() const;` — returns the number of callables
- L1375 _public prototype_ `bool IsValidCallableIndex(int32 InCallableIndex) const;` — returns true if the provided callable index is valid
- L1376 _public prototype_ `bool IsValidCallableIndex(uint16 InCallableIndex) const;`
- L1379 _public prototype_ `const FRigVMCallableInfo* GetCallable(int32 InCallableIndex) const;` — returns the callable info with a given index
- L1380 _public prototype_ `FRigVMCallableInfo* GetCallable(int32 InCallableIndex);`
- L1381 _public prototype_ `const FRigVMCallableInfo* GetCallable(uint16 InCallableIndex) const;`
- L1382 _public prototype_ `FRigVMCallableInfo* GetCallable(uint16 InCallableIndex);`
- L1385 _public prototype_ `int32 GetCallableIndex(const uint32& InHash) const;` — returns the callable's index' with a given its hash
- L1388 _public prototype_ `const FRigVMCallableInfo* FindCallable(const uint32& InHash) const;` — returns a callable given its hash
- L1391 _public prototype_ `const FRigVMCallableInfo* FindCallable(const FName& InName) const;` — returns a callable given its name
- L1394 _public prototype_ `const FRigVMCallableInfo* FindCallableForInstruction(int32 InInstructionIndex) const;` — returns a callable given an instruction within the callable
- L1397 _public prototype_ `int32 AddExecuteOp(int32 InFunctionIndex, const FRigVMOperandArray& InOperands, const int32 InStartPredicateIndex, const int32 InPredicateCount);` — adds an execute operator given its function index operands
- L1400 _public prototype_ `int32 InlineFunction(const FRigVMByteCode* FunctionByteCode, int32 InFirstIndex, int32 InLastIndex);` — adds an execute operator given its function index operands
- L1403 _public prototype_ `int32 AddZeroOp(const FRigVMOperand& InArg);` — adds a zero operator to zero the memory of a given argument
- L1406 _public prototype_ `int32 AddFalseOp(const FRigVMOperand& InArg);` — adds a false operator to set a given argument to false
- L1409 _public prototype_ `int32 AddTrueOp(const FRigVMOperand& InArg);` — adds a true operator to set a given argument to true
- L1412 _public prototype_ `int32 AddCopyOp(const FRigVMOperand& InSource, const FRigVMOperand& InTarget);` — adds a copy operator to copy the content of a source argument to a target argument
- L1415 _public prototype_ `int32 AddCopyOp(const FRigVMCopyOp& InCopyOp);` — adds a copy operator to copy the content of a source argument to a target argument
- L1418 _public prototype_ `int32 AddIncrementOp(const FRigVMOperand& InArg);` — adds an increment operator to increment a int32 argument
- L1421 _public prototype_ `int32 AddDecrementOp(const FRigVMOperand& InArg);` — adds an decrement operator to decrement a int32 argument
- L1424 _public prototype_ `int32 AddEqualsOp(const FRigVMOperand& InA, const FRigVMOperand& InB, const FRigVMOperand& InResult);` — adds an equals operator to store the comparison result of A and B into a Result argument
- L1427 _public prototype_ `int32 AddNotEqualsOp(const FRigVMOperand& InA, const FRigVMOperand& InB, const FRigVMOperand& InResult);` — adds an not-equals operator to store the comparison result of A and B into a Result argument
- L1430 _public prototype_ `int32 AddJumpOp(ERigVMOpCode InOpCode, int32 InInstructionIndex);` — adds an absolute, forward or backward jump operator
- L1433 _public prototype_ `int32 AddJumpIfOp(ERigVMOpCode InOpCode, int32 InInstructionIndex, const FRigVMOperand& InConditionArg, bool bJumpWhenConditionIs = false);` — adds an absolute, forward or backward jump operator based on a condition argument
- L1436 _public prototype_ `int32 AddExitOp();` — adds an exit operator to exit the execution loop
- L1439 _public prototype_ `int32 AddBeginBlockOp(FRigVMOperand InCountArg, FRigVMOperand InIndexArg);` — adds an operator to end the last memory slice
- L1442 _public prototype_ `int32 AddEndBlockOp();` — adds an operator to end the last memory slice
- L1445 _public prototype_ `int32 AddInvokeEntryOp(const FName& InEntryName);` — adds an invoke entry operator
- L1448 _public prototype_ `int32 AddInvokeCallableOp(const uint32& InCallableHash, const FRigVMOperandArray& InOperands);` — adds an invoke callable operator
- L1449 _public prototype_ `int32 AddInvokeCallableOpByIndex(const uint16& InCallableIndex, const FRigVMOperandArray& InOperands);`
- L1452 _public prototype_ `int32 AddJumpToBranchOp(FRigVMOperand InBranchNameArg, int32 InFirstBranchInfoIndex);` — adds a jump to branch operator
- L1455 _public prototype_ `int32 AddRunInstructionsOp(FRigVMOperand InExecuteStateArg, int32 InStartInstruction, int32 InEndInstruction);` — adds a run instructions op
- L1458 _public prototype_ `int32 AddSetupTraitsOp(FRigVMOperand InTraitListArg);` — adds a setup traits op
- L1461 _public prototype_ `int32 AddBranchInfo(const FRigVMBranchInfo& InBranchInfo);` — adds information about a branch for an instruction's argument
- L1462 _public prototype_ `int32 AddBranchInfo(const FName& InBranchLabel, int32 InInstructionIndex, int32 InArgumentIndex, int32 InFirstBranchInstruction, int32 InLastBranchInstruction);`
- L1465 _public prototype_ `int32 AddPredicateBranch(const FRigVMPredicateBranch& InPredicateBranch);` — adds information about a predicate branch for an instruction
- L1468 _public function_ `int32 NumBranches() const` — returns the number of branches within this bytecode
- L1471 _public function_ `const FRigVMBranchInfo& GetBranch(int32 InIndex) const` — returns the branch given the branch index
- L1477 _public prototype_ `const FRigVMBranchInfo* FindBranch(int32 InInstructionIndex, int32 InArgumentIndex) const;` — returns the branch for a given argument index
- L1480 _public prototype_ `const FRigVMBranchInfo* FindBranch(int32 InInstructionIndex, const FName& InLabel) const;` — returns the branch for a given label
- L1483 _public function_ `int32 NumPredicateBranches() const` — returns the number of predicate branches within this bytecode
- L1486 _public function_ `const FRigVMPredicateBranch& GetPredicateBranch(int32 InIndex) const` — returns the predicate branch given the branch index
- L1492 _public function_ `FRigVMInstructionArray GetInstructions() const` — returns an instruction array for iterating over all operators
- L1498 _public function_ `static bool IsCallableOpCode(const ERigVMOpCode InOpCode)` — returns true if the provided opcode refers to a callable
- L1504 _public function_ `static int32 GetCallableOpSize(const ERigVMOpCode InOpCode)` — returns the size of a callable op
- L1510 _public function_ `ERigVMOpCode GetOpCodeAt(int32 InByteCodeIndex) const` — returns the opcode at a given byte index
- L1517 _public prototype_ `int32 GetOpNumBytesAt(int32 InByteCodeIndex, bool bIncludeOperands) const;` — returns the size of the operator in bytes at a given byte index
- L1521 _public function_ `template<class OpType> const OpType& GetOpAt(int32 InByteCodeIndex) const` — returns an operator at a given byte code index
- L1529 _public function_ `template<class OpType> const OpType& GetOpAt(const FRigVMInstruction& InInstruction) const` — returns an operator for a given instruction
- L1536 _public function_ `template<class OpType> OpType& GetOpAt(int32 InByteCodeIndex)` — returns an operator at a given byte code index
- L1544 _public function_ `template<class OpType> OpType& GetOpAt(const FRigVMInstruction& InInstruction)` — returns an operator for a given instruction
- L1550 _public function_ `FRigVMOperandArray GetOperandsAt(int32 InByteCodeIndex, int32 InArgumentCount) const` — returns a list of operands at a given byte code index
- L1563 _public function_ `FRigVMOperandArray GetOperandsForExecuteOp(const FRigVMInstruction& InInstruction) const` — `UE_DEPRECATED(5.8, "Please use GetOperandsForCallableOp instead.")` — returns the operands for a given execute instruction
- L1568 _public function_ `FRigVMOperandArray GetOperandsForCallableOp(const FRigVMInstruction& InInstruction) const`
- L1584 _public prototype_ `FRigVMOperandArray GetOperandsForOp(const FRigVMInstruction& InInstruction) const;` — returns all of the operands for a given instruction
- L1587 _public prototype_ `int32 GetFirstOperandByteIndex(const FRigVMInstruction& InInstruction) const;` — returns the byte index of the first operand for this instructions
- L1590 _public prototype_ `TArray<int32> GetInstructionsForOperand(const FRigVMOperand& InOperand) const;` — returns all instructions for a given operand
- L1594 _public prototype_ `TArray<int32> GetInstructionsForInputOperand(const FRigVMOperand& InOperand) const;` — returns all instructions for a given input operand
- L1597 _public prototype_ `TArray<int32> GetInstructionsForOutputOperand(const FRigVMOperand& InOperand) const;` — returns all instructions for a given output operand
- L1601 _public function_ `bool IsOperandShared(const FRigVMOperand& InOperand) const` — returns true if the operator in question is used by multiple instructions
- L1604 _public function_ `TConstArrayView<uint8> GetByteCode() const` — returns the raw data of the byte code
- L1610 _public function_ `FRigVMByteCodeStatistics GetStatistics() const` — returns the statistics information
- L1619 _public function_ `int32 GetNumInstructions() const` — returns the number of instructions within this byte code
- L1622 _public prototype_ `static int32 GetOpAlignment(ERigVMOpCode InOpCode);` — returns the alignment for an operator given its opcode
- L1625 _public prototype_ `static int32 GetOperandAlignment();` — returns the alignment for an operand
- L1627 _public prototype_ `FString DumpToText() const;`
- L1629 _public function_ `bool HasPublicContextAssetPath() const`
- L1634 _public function_ `const FTopLevelAssetPath& GetPublicContextAssetPath() const`
- L1639 _public function_ `void SetPublicContextAssetPath(const FTopLevelAssetPath& InPublicContextAssetPath)`
- L1648 _public prototype_ `UObject* GetSubjectForInstruction(int32 InInstructionIndex) const;` — returns the subject which was used to inject a given instruction
- L1651 _public prototype_ `int32 GetFirstInstructionIndexForSubject(UObject* InSubject) const;` — returns the first hit instruction index for a given subject (or INDEX_NONE)
- L1654 _public prototype_ `const TArray<int32>& GetAllInstructionIndicesForSubject(UObject* InSubject) const;` — returns all found instruction indices for a given subject
- L1657 _public prototype_ `FString GetCallPathForInstruction(int32 InInstructionIndex) const;` — returns the callpath which was used to inject a given instruction
- L1660 _public prototype_ `int32 GetFirstInstructionIndexForCallPath(const FString& InCallPath, bool bStartsWith = false, bool bEndsWith = false) const;` — returns the first hit instruction index for a given callpath (or INDEX_NONE)
- L1663 _public prototype_ `TArray<int32> GetAllInstructionIndicesForCallPath(const FString& InCallPath, bool bStartsWith = false, bool bEndsWith = false) const;` — returns all found instruction indices for a given callpath
- L1666 _public prototype_ `int32 GetFirstInstructionIndexForCallstack(const TArray<TWeakObjectPtr<UObject>>& InCallstack) const;` — returns the first hit instruction index for a given callpath (or INDEX_NONE)
- L1669 _public prototype_ `const TArray<int32>& GetAllInstructionIndicesForCallstack(const TArray<TWeakObjectPtr<UObject>>& InCallstack) const;` — returns all found instruction indices for a given callpath
- L1672 _public prototype_ `const TArray<TWeakObjectPtr<UObject>>* GetCallstackForInstruction(int32 InInstructionIndex) const;` — returns the callstack which was used to inject a given instruction
- L1675 _public prototype_ `uint32 GetCallstackHashForInstruction(int32 InInstructionIndex) const;` — returns the callstack hash which was used to inject a given instruction
- L1678 _public prototype_ `static uint32 GetCallstackHash(const TArray<TWeakObjectPtr<UObject>>& InCallstack);` — computes a hash for a given callstack
- L1679 _public prototype_ `static uint32 GetCallstackHash(const TArrayView<TWeakObjectPtr<UObject> const>& InCallstack);`
- L1682 _public function_ `FRigVMOperandArray GetInputOperands(int32 InInstructionIndex) const` — returns the input operands of a given instruction
- L1695 _public function_ `FRigVMOperandArray GetOutputOperands(int32 InInstructionIndex) const` — returns the output operands of a given instruction
- L1707 _public prototype_ `void SetOperandsForInstruction(const FRigVMInstruction& InInstruction, const FRigVMOperandArray& InputOperands, const FRigVMOperandArray& OutputOperands);`
- L1712 _public prototype_ `TMap<int32, TArray<FRigVMTraitScope>> GetTraits(FRigVMMemoryStorageStruct& InLiteralMemory, FRigVMMemoryStorageStruct& InWorkMemory, const UScriptStruct* InScriptStruct = nullptr) const;` — returns the traits for the provided memory
- L1715 _public prototype_ `TMap<int32, TArray<FRigVMTraitScope>> GetTraits(FRigVMMemoryStorageStruct& InLiteralMemory, FRigVMMemoryStorageStruct& InWorkMemory, TArray<FRigVMMemoryHandle>& OutAdditionalMemoryHandles, const UScriptStruct* InScriptStruct = nullptr) const;` — returns the traits for the provided memory and any additional memory handles
- L1719 _public function_ `template<typename T> TMap<int32, TArray<FRigVMTraitScope>> GetTraits(FRigVMMemoryStorageStruct& InLiteralMemory, FRigVMMemoryStorageStruct& InWorkMemory) const` — returns the traits of a given type for the provided memory
- L1726 _public function_ `template<typename T> TMap<int32, TArray<FRigVMTraitScope>> GetTraits(FRigVMMemoryStorageStruct& InLiteralMemory, FRigVMMemoryStorageStruct& InWorkMemory, TArray<FRigVMMemoryHandle>& OutAdditionalMemoryHandles) const` — returns the traits of a given type for the provided memory and any additional memorty handles
- L1732 _public prototype_ `TArray<FRigVMTraitScope> GetTraitsForInstruction(const FRigVMInstruction& InInstruction, FRigVMMemoryStorageStruct& InLiteralMemory, FRigVMMemoryStorageStruct& InWorkMemory, const UScriptStruct* InScriptStruct = nullptr) const;` — returns the traits for the provided memory for a single instruction
- L1735 _public prototype_ `TArray<FRigVMTraitScope> GetTraitsForInstruction(const FRigVMInstruction& InInstruction, FRigVMMemoryStorageStruct& InLiteralMemory, FRigVMMemoryStorageStruct& InWorkMemory, TArray<FRigVMMemoryHandle>& OutAdditionalMemoryHandles, const UScriptStruct* InScriptStruct = nullptr) const;` — returns the traits for the provided memory for a single instruction and any additional memory handles
- L1739 _public function_ `template<typename T> TArray<FRigVMTraitScope> GetTraitsForInstruction(const FRigVMInstruction& InInstruction, FRigVMMemoryStorageStruct& InLiteralMemory, FRigVMMemoryStorageStruct& InWorkMemory) const` — returns the traits of a given type for the provided memory for a single instruction
- L1746 _public function_ `template<typename T> TArray<FRigVMTraitScope> GetTraitsForInstruction(const FRigVMInstruction& InInstruction, FRigVMMemoryStorageStruct& InLiteralMemory, FRigVMMemoryStorageStruct& InWorkMemory, TArray<FRigVMMemoryHandle>& OutAdditionalMemoryHandles) const` — returns the traits of a given type for the provided memory for a single instruction and any additional memory handles
- L1754 _private function_ `template<class OpType> int32 AddOp(const OpType& InOp)`
- L1770 _private prototype_ `void AlignByteCode();`
- L1774 _private member_ `TArray<uint8> ByteCode;` — `UPROPERTY()` — memory for all instructions
- L1778 _private member_ `int32 NumInstructions;` — `UPROPERTY()` — number of instructions stored here
- L1782 _private member_ `TArray<TWeakObjectPtr<UObject>> SubjectPerInstruction;`
- L1783 _private member_ `TMap<TWeakObjectPtr<UObject>, TArray<int32>> SubjectToInstructions;`
- L1784 _private member_ `TArray<FString> CallPathPerInstruction;`
- L1785 _private member_ `TMap<FString, TArray<int32>> CallPathToInstructions;`
- L1786 _private member_ `TArray<TArray<TWeakObjectPtr<UObject>>> CallstackPerInstruction;`
- L1787 _private member_ `TMap<uint32, TArray<int32>> CallstackHashToInstructions;`
- L1788 _private member_ `TArray<uint32> CallstackHashPerInstruction;`
- L1789 _private member_ `TArray<TArray<FRigVMOperand>> InputOperandsPerInstruction;`
- L1790 _private member_ `TArray<TArray<FRigVMOperand>> OutputOperandsPerInstruction;`
- L1796 _private prototype_ `void SetSubject(int32 InInstructionIndex, const FString& InCallPath, const TArray<TWeakObjectPtr<UObject>>& InCallstack);`
- L1797 _private prototype_ `void AddInstructionForSubject(UObject* InSubject, int32 InInstructionIndex);`
- L1803 _private member_ `TArray<FRigVMByteCodeEntry> Entries;` — `UPROPERTY()` — a look up table from entry name to instruction index
- L1807 _private member_ `TArray<FRigVMBranchInfo> BranchInfos;` — `UPROPERTY()` — a list of all lazily evaluation branches
- L1811 _private member_ `TArray<FRigVMPredicateBranch> PredicateBranches;` — `UPROPERTY()` — a list of all predicate branches
- L1815 _private member_ `TArray<FRigVMCallableInfo> CallableInfos;` — `UPROPERTY()` — a list of stored callables
- L1818 _private member_ `FTopLevelAssetPath PublicContextAssetPath;` — `UPROPERTY()`
- L1820 _private prototype_ `const FRigVMBranchInfo* GetBranchInfo(const FRigVMBranchInfoKey& InBranchInfoKey) const;`
- L1821 _private member_ `mutable TMap<FRigVMBranchInfoKey, const FRigVMBranchInfo*> BranchInfoLookup;`
- L1824 _private member_ `bool bByteCodeIsAligned;` — if this is set to true the stored bytecode is aligned / padded
- L1826 _private member_ `bool bHasPublicContextAssetPath = false;` — If the serialization has loaded a PublicContextPathName, so we check on new versions and skip check on older
- L1828 _private member_ `static TArray<int32> EmptyInstructionIndices;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_API RIGVM_API`
- L64 _function_ `friend uint32 GetTypeHash(const FRigVMBranchInfoKey& InKey)`
- L147 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMCallableArgument& P)`
- L163 _function_ `friend uint32 GetTypeHash(const FRigVMCallableArgument& InArgument)`
- L226 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMCallableInfo& P)`
- L232 _function_ `friend uint32 GetTypeHash(const FRigVMCallableInfo& InCallableInfo)`
- L375 _function_ `friend uint32 GetTypeHash(const FRigVMBaseOp& Op)`
- L416 _function_ `friend uint32 GetTypeHash(const FRigVMInvokeCallableOp& Op)`
- L430 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMInvokeCallableOp& P)`
- L467 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMExecuteOp& P)`
- L508 _function_ `friend uint32 GetTypeHash(const FRigVMUnaryOp& Op)`
- L514 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMUnaryOp& P)`
- L551 _function_ `friend uint32 GetTypeHash(const FRigVMBinaryOp& Op)`
- L560 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMBinaryOp& P)`
- L601 _function_ `friend uint32 GetTypeHash(const FRigVMTernaryOp& Op)`
- L611 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMTernaryOp& P)`
- L657 _function_ `friend uint32 GetTypeHash(const FRigVMQuaternaryOp& Op)`
- L668 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMQuaternaryOp& P)`
- L717 _function_ `friend uint32 GetTypeHash(const FRigVMQuinaryOp& Op)`
- L729 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMQuinaryOp& P)`
- L782 _function_ `friend uint32 GetTypeHash(const FRigVMSenaryOp& Op)`
- L795 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMSenaryOp& P)`
- L864 _function_ `friend uint32 GetTypeHash(const FRigVMCopyOp& Op)`
- L878 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMCopyOp& P)`
- L930 _function_ `friend uint32 GetTypeHash(const FRigVMComparisonOp& Op)`
- L940 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMComparisonOp& P)`
- L980 _function_ `friend uint32 GetTypeHash(const FRigVMJumpOp& Op)`
- L988 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMJumpOp& P)`
- L1051 _function_ `friend uint32 GetTypeHash(const FRigVMJumpIfOp& Op)`
- L1060 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMJumpIfOp& P)`
- L1082 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMChangeTypeOp& P)`
- L1107 _function_ `friend uint32 GetTypeHash(const FRigVMInvokeEntryOp& Op)`
- L1113 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMInvokeEntryOp& P)`
- L1146 _function_ `friend uint32 GetTypeHash(const FRigVMJumpToBranchOp& Op)`
- L1154 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMJumpToBranchOp& P)`
- L1184 _function_ `friend uint32 GetTypeHash(const FRigVMRunInstructionsOp& Op)`
- L1193 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMRunInstructionsOp& P)`
- L1329 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMByteCode& P)`
- L1351 _function_ `friend uint32 GetTypeHash(const FRigVMByteCode& InByteCode)` — overload for GetTypeHash

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMCore.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMDebugDrawSettings.h` (Public)


#### struct `FRigVMDebugDrawSettings`  
`struct FRigVMDebugDrawSettings`  
_L9-18_
- reflection: `USTRUCT()`
- L14 _public member_ `TEnumAsByte<ESceneDepthPriorityGroup> DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground;` — `UPROPERTY(meta = (Input, DisplayPriority = MAX_int32), Category = "DebugSettings")`
- L17 _public member_ `float Lifetime = -1.f;` — `UPROPERTY(meta = (Input, DisplayPriority = MAX_int32), Category = "DebugSettings")`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMDebugInfo.h` (Public)


#### enum `ERigVMStepMode`  
`enum class ERigVMStepMode : uint8`  
_L21-29_
- reflection: `UENUM()`
- L23 _public enumerator_ `None`
- L24 _public enumerator_ `Stopped` — Parked at a specific instruction
- L25 _public enumerator_ `Forward` — Next instruction at same callable depth
- L26 _public enumerator_ `Into` — Enter next callable
- L27 _public enumerator_ `Out` — Exit current callable
- L28 _public enumerator_ `RunTo` — Run until target instruction (first hit)

#### struct `FRigVMStepCondition`  
`struct FRigVMStepCondition`  
_L47-105_
- reflection: `USTRUCT()`
- desc: FRigVMStepCondition tracks: - Mode - None, Stopped, Forward, Into, Out, RunTo - OriginInstruction - instruction index where we're stopped - OriginCallstackPath - array of call site instruction indices (full callstack context) - OriginIterationPath - array of loop iteration indices - bHasPassedOrigin - flag to ensure we've reached the origin before detecting forward progress Step behaviors: - Into - stops when entering a callable (deeper), advancing at same level, or exiting a callable (shallower) - Forward - stops when advancing at same level or exiting a callable (shallower) - Out - stops only when exiting a callable (shallower) - RunTo - stops at target instruction regardless of context - Stopped - re-halts at exact same location (callstack + instruction + iteration)
- L51 _public function_ `FRigVMStepCondition() : Mode(ERigVMStepMode::None) , OriginInstruction(INDEX_NONE) , TargetInstruction(INDEX_NONE) , bHasPassedOrigin(false)`
- L59 _public member_ `ERigVMStepMode Mode;`
- L60 _public member_ `int32 OriginInstruction;`
- L61 _public member_ `int32 TargetInstruction;` — For RunTo mode
- L62 _public member_ `bool bHasPassedOrigin;` — True once we've passed the origin point during re-execution
- L65 _public member_ `TArray<int32, TInlineAllocator<16>> OriginCallstackPath;` — Callstack path - instruction index at each call site
- L68 _public member_ `TArray<int32, TInlineAllocator<16>> OriginIterationPath;` — Iteration path when stopped - for re-halting at same location
- L70 _public function_ `FString ToString() const`

#### struct `FRigVMDebugInfo`  
`struct FRigVMDebugInfo`  
_L108-179_
- reflection: `USTRUCT()`
- L112 _public function_ `FRigVMDebugInfo()`
- L116 _public function_ `void Reset()`
- L121 _public function_ `bool IsActive() const`
- L126 _public prototype_ `bool ShouldStop(const FRigVMExtendedExecuteContext& Context, int32 CurrentInstruction);`
- L128 _public function_ `void StepForward()`
- L133 _public function_ `void StepInto()`
- L138 _public function_ `void StepOut()`
- L143 _public function_ `void RunToInstruction(int32 Instruction)`
- L149 _public function_ `void BeginExecution()`
- L154 _public function_ `const FRigVMStepCondition& GetStepCondition() const`
- L159 _public function_ `void SetStepCondition(const FRigVMStepCondition& InStepCondition)`
- L164 _public prototype_ `DECLARE_EVENT_ThreeParams(URigVM, FExecutionHaltedEvent, int32, UObject*, const FName&);`
- L165 _public function_ `FExecutionHaltedEvent& ExecutionHalted()`
- L171 _private prototype_ `void TransitionToStopped(const FRigVMExtendedExecuteContext& Context, int32 CurrentInstruction);`
- L172 _private prototype_ `static void CaptureCallstackPath(const FRigVMExtendedExecuteContext& Context, TArray<int32, TInlineAllocator<16>>& OutPath);`
- L173 _private prototype_ `static int32 CompareCallstackPath(const FRigVMExtendedExecuteContext& Context, const TArray<int32, TInlineAllocator<16>>& InPath);`
- L174 _private prototype_ `static void CaptureIterationPath(const FRigVMExtendedExecuteContext& Context, TArray<int32, TInlineAllocator<16>>& OutPath);`
- L175 _private prototype_ `static int32 CompareIterationPath(const FRigVMExtendedExecuteContext& Context, const TArray<int32, TInlineAllocator<16>>& InPath);`
- L177 _private member_ `FRigVMStepCondition StepCondition;`
- L178 _private member_ `FExecutionHaltedEvent OnExecutionHalted;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVM_API`
- L164 _delegate_ `DECLARE_EVENT_ThreeParams(URigVM, FExecutionHaltedEvent, int32, UObject*, const FName&);`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMDispatchFactory.h` (Public)


#### struct `FRigVMDispatchContext`  
`struct FRigVMDispatchContext`  
_L32-44_
- desc: A context used for inquiring from dispatch factories
- L34 _public function_ `FRigVMDispatchContext() : Instance() , Subject(nullptr) , StringRepresentation()`
- L41 _public member_ `TSharedPtr<FStructOnScope> Instance;`
- L42 _public member_ `const UObject* Subject;`
- L43 _public member_ `FString StringRepresentation;`

#### struct `FRigVMDispatchFactory`  
`struct FRigVMDispatchFactory`  
_L50-305_
- reflection: `USTRUCT()`
- desc: A factory to generate a template and its dispatch functions
- L56 _public function_ `FRigVMDispatchFactory() : FactoryIndex(INDEX_NONE) , FactoryName(NAME_None) , FactoryScriptStruct(nullptr) , CachedTemplate(nullptr) , OwnerRegistry(nullptr)`
- L66 _public function_ `virtual ~FRigVMDispatchFactory()`
- L72 _public function_ `int32 GetFactoryIndex() const` — returns the index of this factory in its registry
- L75 _public prototype_ `FName GetFactoryName() const;` — returns the name of this factory
- L78 _public prototype_ `static FName GetFactoryName(const UScriptStruct* InFactoryStruct);` — returns the name of the factory given the factory's struct
- L81 _public function_ `UScriptStruct* GetScriptStruct() const` — returns the struct for this dispatch factory
- L84 _public function_ `const FRigVMRegistry_NoLock* GetOwnerRegistry() const` — returns the registry this factory belongs top
- L87 _public function_ `virtual bool SupportsRenaming() const` — returns true if nodes provided by this factory can be renamed
- L92 _public function_ `virtual FString GetNodeTitle(const FRigVMTemplateTypeMap& InTypes) const` — returns the title of the node for a given type set.
- L95 _public prototype_ `virtual FLinearColor GetNodeColor() const;` — returns the color of the node for a given type set.
- L98 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const;` — returns the tooltip for the node
- L101 _public prototype_ `virtual FString GetArgumentDefaultValue(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const;` — returns the default value for an argument
- L104 _public function_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const` — returns the tooltip for an argument
- L107 _public function_ `virtual TArray<FName> GetAggregateInputArguments() const` — returns the names of the input aggregate arguments
- L110 _public function_ `virtual TArray<FName> GetAggregateOutputArguments() const` — returns the names of the output aggregate arguments
- L113 _public prototype_ `virtual FName GetNextAggregateName(const FName& InLastAggregatePinName) const;` — returns the next name to be used for an aggregate pin
- L116 _public prototype_ `virtual FName GetDisplayNameForArgument(const FName& InArgumentName, const FRigVMTemplateTypeMap& InTypes) const;` — Returns the display name text for an argument
- L119 _public prototype_ `virtual FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const;` — Returns meta data on the property of the permutations
- L122 _public function_ `bool HasArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const` — Returns true if the factory provides metadata for a given argument
- L128 _public prototype_ `virtual FString GetCategory() const;` — Returns the category this factory is under
- L131 _public prototype_ `virtual FString GetKeywords() const;` — Returns the keywords used for looking up this factory
- L134 _public prototype_ `bool IsLazyInputArgument(const FName& InArgumentName) const;` — Returns true if the argument is lazy
- L141 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const;` — Returns the name to use for the branch info / argument based on the operand index. operand index count may be different than the number of arguments, since fixed size array arguments get unrolled.
- L145 _public function_ `bool IsControlFlowDispatch(const FRigVMDispatchContext& InContext, const FRigVMTemplateTypeMap& InTypeMap) const` — returns true if the dispatch is a control flow dispatch
- L148 _public prototype_ `const TArray<FName>& GetControlFlowBlocks(const FRigVMDispatchContext& InContext, const FRigVMTemplateTypeMap& InTypeMap) const;` — returns the control flow blocks of this dispatch
- L152 _public function_ `virtual const bool IsControlFlowBlockSliced(const FName& InBlockName) const` — returns true if a given control flow block needs to be sliced
- L155 _public function_ `virtual UScriptStruct* GetExecuteContextStruct() const` — Returns the execute context support for this dispatch factory
- L158 _public prototype_ `bool SupportsExecuteContextStruct(const UScriptStruct* InExecuteContextStruct) const;` — Returns truf if this factory supports a given executecontext struct
- L163 _public function_ `virtual void RegisterDependencyTypes_NoLock(FRigVMRegistryHandle& InRegistry) const` — registered needed types during registration of the factory. this is called within a NoLock code path - so make sure to access the FRigVMRegistry_NoLock within as needed.
- L166 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const;` — returns the arguments of the template
- L169 _public prototype_ `TArray<FRigVMExecuteArgument> GetExecuteArguments_NoLock(const FRigVMDispatchContext& InContext, const FRigVMRegistryHandle& InRegistry) const;` — returns the execute arguments of the template
- L174 _public function_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const` — this function is deprecated, please use GetPermutationsFromArgumentType returns the new permutation argument types after a new type is defined for one argument this happens if types are being loaded later after this factory has already been deployed (like UUserDefinedStruct)
- L177 _public function_ `virtual bool GetPermutationsFromArgumentType(const FName& InArgumentName, const TRigVMTypeIndex& InTypeIndex, TArray<FRigVMTemplateTypeMap, TInlineAllocator<1>>& OutPermutations, FRigVMRegistryHandle& InRegistry) const` — returns the new permutations argument types after a new type is defined for one argument
- L189 _public function_ `virtual FRigVMStructUpgradeInfo GetUpgradeInfo(const FRigVMTemplateTypeMap& InTypes, const FRigVMDispatchContext& InContext) const` — returns the upgrade info to use for this factory
- L192 _public prototype_ `FRigVMFunctionPtr GetOrCreateDispatchFunction(const FRigVMTemplateTypeMap& InTypes) const;` — returns the dispatch function for a given type set
- L195 _public prototype_ `const FRigVMTemplate* GetTemplate() const;` — builds and returns the template
- L198 _public prototype_ `const FRigVMTemplate* GetTemplate_NoLock(FRigVMRegistryHandle& InRegistry) const;` — builds and returns the template
- L201 _public prototype_ `FName GetTemplateNotation() const;` — returns the name of the factory template
- L202 _public prototype_ `FName GetTemplateNotation_NoLock(FRigVMRegistryHandle& InRegistry) const;`
- L205 _public prototype_ `FString GetPermutationName(const FRigVMTemplateTypeMap& InTypes) const;` — returns the name of the permutation for a given set of types
- L206 _public prototype_ `FString GetPermutationName_NoLock(const FRigVMTemplateTypeMap& InTypes, FRigVMRegistryHandle& InRegistry) const;`
- L209 _public function_ `virtual bool IsSingleton() const` — returns true if the dispatch uses the same function ptr for all permutations
- L214 _protected prototype_ `const FRigVMTemplate* CreateTemplateForArgumentInfos_NoLock(const TArray<FRigVMTemplateArgumentInfo>& InArguments, FRigVMRegistryHandle& InRegistry);` — creates the template based on existing argument infos
- L217 _protected prototype_ `FRigVMFunctionPtr GetOrCreateDispatchFunction_NoLock(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const;` — returns the dispatch function for a given type set
- L220 _protected prototype_ `TArray<FRigVMTemplateArgumentInfo> BuildArgumentListFromPrimaryArgument(const TArray<FRigVMTemplateArgumentInfo>& InInfos, const FName& InPrimaryArgumentName, FRigVMRegistryHandle& InRegistry) const;` — for each type defined in the primary argument, this function will call GetPermutationsFromArgumentType to construct an array of arguments with the appropiate permutations
- L223 _protected prototype_ `FString GetPermutationNameImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const;` — returns the name of the permutation for a given set of types
- L225 _protected prototype_ `FRigVMFunctionPtr CreateDispatchFunction_NoLock(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const;`
- L227 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const`
- L229 _protected prototype_ `TArray<FRigVMFunction> CreateDispatchPredicates_NoLock(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const;`
- L231 _protected function_ `virtual TArray<FRigVMFunction> GetDispatchPredicatesImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const`
- L233 _protected prototype_ `virtual const TArray<FRigVMExecuteArgument>& GetExecuteArguments_Impl(const FRigVMDispatchContext& InContext) const;`
- L235 _protected prototype_ `static bool CopyProperty( const FProperty* InTargetProperty, uint8* InTargetPtr, const FProperty* InSourceProperty, const uint8* InSourcePtr);`
- L245 _protected function_ `static FString GetDefaultValueForStruct(const T& InValue)`
- L270 _protected function_ `bool CheckArgumentType(bool bCondition, const FName& InArgumentName) const`
- L281 _protected prototype_ `virtual const TArray<FName>& GetControlFlowBlocks_Impl(const FRigVMDispatchContext& InContext, const FRigVMTemplateTypeMap& InTypeMap) const;`
- L284 _protected member_ `static const inline TCHAR* DispatchPrefix = TEXT("DIS`
- L285 _protected member_ `static const inline TCHAR* TrueString = TEXT("Tru`
- L287 _protected prototype_ `const TArray<FName>* UpdateArgumentNameCache(int32 InNumberOperands, FRigVMRegistryHandle& InRegistry) const;`
- L288 _protected prototype_ `const TArray<FName>* UpdateArgumentNameCache_NoLock(int32 InNumberOperands, FRigVMRegistryHandle& InRegistry) const;`
- L290 _protected member_ `int32 FactoryIndex;`
- L291 _protected member_ `mutable FName FactoryName;`
- L292 _protected member_ `FString FactoryNameString;`
- L293 _protected member_ `UScriptStruct* FactoryScriptStruct;`
- L294 _protected member_ `mutable const FRigVMTemplate* CachedTemplate;`
- L295 _protected member_ `const FRigVMRegistry_NoLock* OwnerRegistry;`
- L296 _protected member_ `static FCriticalSection GetTemplateMutex;`
- L297 _protected member_ `mutable TMap<int32, TSharedPtr<TArray<FName>>> ArgumentNamesMap;`
- L298 _protected member_ `FCriticalSection* ArgumentNamesMutex;`
- L299 _protected member_ `mutable TArray<FRigVMTemplateArgumentInfo> CachedArgumentInfos;`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMDrawContainer.h` (Public)


#### struct `FRigVMDrawContainer`  
`struct FRigVMDrawContainer`  
_L10-33_
- reflection: `USTRUCT()`
- L13 _public prototype_ `virtual ~FRigVMDrawContainer() = default;`
- L15 _public function_ `int32 Num() const`
- L16 _public prototype_ `int32 GetIndex(const FName& InName) const;`
- L17 _public function_ `const FRigVMDrawInstruction& operator[](int32 InIndex) const`
- L18 _public function_ `FRigVMDrawInstruction& operator[](int32 InIndex)`
- L19 _public function_ `const FRigVMDrawInstruction& operator[](const FName& InName) const`
- L20 _public function_ `FRigVMDrawInstruction& operator[](const FName& InName)`
- L22 _public function_ `TArray<FRigVMDrawInstruction>::RangedForIteratorType begin()`
- L23 _public function_ `TArray<FRigVMDrawInstruction>::RangedForConstIteratorType begin() const`
- L24 _public function_ `TArray<FRigVMDrawInstruction>::RangedForIteratorType end()`
- L25 _public function_ `TArray<FRigVMDrawInstruction>::RangedForConstIteratorType end() const`
- L27 _public function_ `uint32 GetAllocatedSize() const`
- L29 _public prototype_ `void Reset();`
- L32 _public member_ `TArray<FRigVMDrawInstruction> Instructions;` — `UPROPERTY(EditAnywhere, Category = "DrawContainer")`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMDrawInstruction.h` (Public)


#### enum `ERigVMDrawSettings::Primitive`  
`enum Primitive : int`  
_L15-22_
- L17 _public enumerator_ `Points`
- L18 _public enumerator_ `Lines`
- L19 _public enumerator_ `LineStrip`
- L20 _public enumerator_ `DynamicMesh`
- L21 _public enumerator_ `Text`

#### struct `FRigVMDrawInstruction`  
`struct FRigVMDrawInstruction`  
_L26-95_
- reflection: `USTRUCT()`
- L31 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "DrawInstruction")`
- L34 _public member_ `TEnumAsByte<ERigVMDrawSettings::Primitive> PrimitiveType = ERigVMDrawSettings::Points;` — `UPROPERTY(EditAnywhere, Category = "DrawInstruction")`
- L37 _public member_ `TArray<FVector> Positions;` — `UPROPERTY(EditAnywhere, Category = "DrawInstruction")`
- L40 _public member_ `FLinearColor Color = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = "DrawInstruction")`
- L43 _public member_ `float Thickness = 0.f;` — `UPROPERTY(EditAnywhere, Category = "DrawInstruction")`
- L46 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "DrawInstruction")`
- L49 _public member_ `TEnumAsByte<ESceneDepthPriorityGroup> DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground;` — `UPROPERTY(EditAnywhere, Category = "DrawInstruction")`
- L52 _public member_ `float Lifetime = -1.f;` — `UPROPERTY(EditAnywhere, Category = "DrawInstruction")`
- L58 _public member_ `FString Text;` — `UPROPERTY(EditAnywhere, Category = "DrawInstruction")` — Only used when PrimitiveType is Text. The string is rendered on the 2D canvas by the edit mode via FCanvasTextItem, anchored at Positions[0] (additional entries in Positions are ignored).
- L61 _public member_ `float FontScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "DrawInstruction")`
- L64 _public member_ `TArray<FDynamicMeshVertex> MeshVerts;` — This is to draw cone, they're not UPROPERTY
- L65 _public member_ `TArray<uint32> MeshIndices;`
- L66 _public member_ `FMaterialRenderProxy* MaterialRenderProxy = nullptr;`
- L68 _public prototype_ `FRigVMDrawInstruction() = default;`
- L70 _public function_ `FRigVMDrawInstruction(ERigVMDrawSettings::Primitive InPrimitiveType, const FLinearColor& InColor, float InThickness = 0.f, FTransform InTransform = FTransform::Identity, ESceneDepthPriorityGroup InDepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float InLifetime = -1.f) : PrimitiveType(InPrimitiveType) , Color(InColor) , Thickness(InThickness) , Transform(InTransform) , DepthPriority(InDepthPriority) , Lifetime(InLifetime)`
- L79 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ERigVMDrawSettings`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMDrawInterface.h` (Public)


#### struct `FRigVMDrawInterface`  
`struct FRigVMDrawInterface : public FRigVMDrawContainer`  
_L12-45_
- reflection: `USTRUCT()`
- inherits: `FRigVMDrawContainer`
- L18 _public prototype_ `void DrawInstruction(const FRigVMDrawInstruction& InInstruction);`
- L19 _public prototype_ `void DrawPoint(const FTransform& WorldOffset, const FVector& Position, float Size, const FLinearColor& Color, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L20 _public prototype_ `void DrawPoints(const FTransform& WorldOffset, const TArrayView<const FVector>& Points, float Size, const FLinearColor& Color, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L21 _public prototype_ `void DrawLine(const FTransform& WorldOffset, const FVector& LineStart, const FVector& LineEnd, const FLinearColor& Color, float Thickness = 0.f, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L22 _public prototype_ `void DrawLines(const FTransform& WorldOffset, const TArrayView<const FVector>& Positions, const FLinearColor& Color, float Thickness = 0.f, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L23 _public prototype_ `void DrawLineStrip(const FTransform& WorldOffset, const TArrayView<const FVector>& Positions, const FLinearColor& Color, float Thickness = 0.f, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L25 _public prototype_ `void DrawBox(const FTransform& WorldOffset, const FTransform& Transform, const FLinearColor& Color, float Thickness = 0.f, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);` — This draws a scaled unit cube, with the transforms applied. When drawing a box, put the position/orientation into WorldOffset and the extents into Transform.
- L26 _public prototype_ `void DrawSphere(const FTransform& WorldOffset, const FTransform& Transform, float Radius, const FLinearColor& Color, float Thickness = 0.f, int32 Detail = 12, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L28 _public prototype_ `void DrawHemisphere(const FTransform& WorldOffset, const FTransform& Transform, float Radius, const FLinearColor& Color, float Thickness = 0.f, int32 Detail = 12, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);` — Hemispheres are drawn so that they extend up along +ve Z
- L30 _public prototype_ `void DrawCapsule(const FTransform& WorldOffset, const FTransform& Transform, float Radius, float Length, const FLinearColor& Color, float Thickness = 0.f, int32 Detail = 12, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);` — Capsules are drawn so that they extend along Z
- L31 _public prototype_ `void DrawAxes(const FTransform& WorldOffset, const FTransform& Transform, float Size, float Thickness = 0.f, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L32 _public prototype_ `void DrawAxes(const FTransform& WorldOffset, const TArrayView<const FTransform>& Transforms, float Size, float Thickness = 0.f, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L33 _public prototype_ `void DrawAxes(const FTransform& WorldOffset, const FTransform& Transform, const FLinearColor& InColor, float Size, float Thickness = 0.f, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L34 _public prototype_ `void DrawAxes(const FTransform& WorldOffset, const TArrayView<const FTransform>& Transforms, const FLinearColor& InColor, float Size, float Thickness = 0.f, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L35 _public prototype_ `void DrawRectangle(const FTransform& WorldOffset, const FTransform& Transform, float Size, const FLinearColor& Color, float Thickness, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L36 _public prototype_ `void DrawArc(const FTransform& WorldOffset, const FTransform& Transform, float Radius, float MinimumAngle, float MaximumAngle, const FLinearColor& Color, float Thickness, int32 Detail, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L38 _public prototype_ `void DrawCircle(const FTransform& WorldOffset, const FTransform& Transform, float Radius, const FLinearColor& Color, float Thickness, int32 Detail, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);` — Circles are drawn in the XY plane
- L39 _public prototype_ `void DrawCone(const FTransform& WorldOffset, const FTransform& ConeOffset, float Angle1, float Angle2, uint32 NumSides, bool bDrawSideLines, const FLinearColor& SideLineColor, FMaterialRenderProxy* const MaterialRenderProxy, float SideLineThickness = 1.0f, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L40 _public prototype_ `void DrawArrow(const FTransform& WorldOffset, const FVector& Direction, const FVector& Side, const FLinearColor& InColor, float Thickness, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L41 _public prototype_ `void DrawPlane(const FTransform& WorldOffset, const FVector2D& Scale, const FLinearColor& MeshColor, bool bDrawLines, const FLinearColor& LineColor, FMaterialRenderProxy* const MaterialRenderProxy, ESceneDepthPriorityGroup DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground, float Lifetime = -1.f);`
- L42 _public prototype_ `void DrawText(const FTransform& WorldOffset, const FVector& Position, const FString& Text, const FLinearColor& Color, float FontScale = 1.f, float Lifetime = -1.f);`
- L44 _public prototype_ `bool IsEnabled() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMExecuteContext.h` (Public)


#### enum `ERigVMSliceType`  
`enum class ERigVMSliceType : uint8`  
_L50-55_
- L52 _public enumerator_ `Invalid`
- L53 _public enumerator_ `Loop`
- L54 _public enumerator_ `Callable`

#### struct `FRigVMSlice`  
`struct FRigVMSlice`  
_L57-234_
- L61 _public function_ `FRigVMSlice() : SliceType(ERigVMSliceType::Invalid) , LowerBound(0) , UpperBound(0) , Index(INDEX_NONE) , Offset(0) , InstructionOrCallableIndex(INDEX_NONE)`
- L72 _public function_ `static FRigVMSlice MakeForLoop(int32 InCount)`
- L81 _public function_ `static FRigVMSlice MakeForCallable()`
- L90 _public function_ `bool IsValid() const`
- L95 _public function_ `ERigVMSliceType GetType() const`
- L100 _public function_ `bool IsLoop() const`
- L105 _public function_ `bool IsCallable() const`
- L110 _public function_ `bool IsComplete() const`
- L115 _public function_ `int32 GetIndex() const`
- L120 _public function_ `int32 GetRelativeIndex() const`
- L125 _public function_ `void SetRelativeIndex(int32 InIndex)`
- L130 _public function_ `float GetRelativeRatio() const`
- L135 _public function_ `int32 GetOffset() const`
- L140 _public function_ `void SetOffset(int32 InSliceOffset)`
- L145 _public function_ `int32 GetInstructionOrCallableIndex() const`
- L150 _public function_ `void SetInstructionOrCallableIndex(int32 InInstructionOrCallableIndex)`
- L155 _public function_ `int32 Num() const`
- L160 _public function_ `int32 TotalNum() const`
- L165 _public function_ `operator bool() const`
- L170 _public function_ `bool operator !() const`
- L175 _public function_ `operator int32() const`
- L180 _public function_ `FRigVMSlice& operator++()`
- L186 _public function_ `FRigVMSlice operator++(int32)`
- L193 _public function_ `bool Next()`
- L209 _public function_ `void Reset()`
- L221 _public function_ `uint32 GetHash() const`
- L228 _private member_ `ERigVMSliceType SliceType;`
- L229 _private member_ `int32 LowerBound;`
- L230 _private member_ `int32 UpperBound;`
- L231 _private member_ `int32 Index;`
- L232 _private member_ `int32 Offset;`
- L233 _private member_ `int32 InstructionOrCallableIndex;`

#### struct `FRigVMRuntimeSettings`  
`struct FRigVMRuntimeSettings`  
_L237-279_
- reflection: `USTRUCT()`
- L246 _public member_ `int32 MaximumArraySize = 2048;` — `UPROPERTY(EditAnywhere, Category = "VM")` — The largest allowed size for arrays within the RigVM. Accessing or creating larger arrays will cause runtime errors in the rig.
- L258 _public member_ `bool bEnableProfiling = false;` — `UPROPERTY(EditAnywhere, Category = "VM")` — When enabled records the timing of each instruction / node on each node and within the execution stack window. Keep in mind when looking at nodes in a function the duration represents the accumulated duration of all invocations of the function currently running. Note: This can only be used when in Debug Mode. Click the "Release" button in the top toolbar to switch to Debug mode.
- L264 _public typedef_ `using LogFunctionType = TFunction<void(const FRigVMLogSettings&,const FRigVMExecuteContext*,const FString&)>;` — The function to use for logging anything from the VM to the host
- L265 _public member_ `TSharedPtr<LogFunctionType> LogFunction = nullptr;`
- L267 _public function_ `void SetLogFunction(LogFunctionType InLogFunction)`
- L275 _public function_ `void Validate()` — Validate the settings

#### struct `FRigVMExecuteContextFixLayout`  
`struct FRigVMExecuteContextFixLayout`  
_L282-285_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L284 _public prototype_ `virtual ~FRigVMExecuteContextFixLayout() = default;`

#### struct `FRigVMExecutePin`  
`struct FRigVMExecutePin #if CPP : public FRigVMExecuteContextFixLayout #endif`  
_L295-301_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMExecuteContextFixLayout`
- desc: This structure is used for semantically describing a pin on a RigVMStruct - but without any content. So rather than adding an actual FRigVMExecuteContext this can be added as the type for a pin and it won't use any memory. To customize which FRigVMExecuteContext structure to use on your node you can add the ExecuteContext=FMyExecuteContext meta data tag on the USTRUCT macro.

#### struct `FRigVMExecuteContext`  
`struct FRigVMExecuteContext : public FRigVMExecutePin`  
_L308-640_
- reflection: `USTRUCT(BlueprintType, meta=(DisplayName="Execute Context"))`
- inherits: `FRigVMExecutePin`
- desc: The execute context is used for mutable nodes to indicate execution order.
- L312 _public function_ `FRigVMExecuteContext() : InstructionIndex(0) , EventName(NAME_None) , FunctionName(NAME_None) , NumExecutions(0) , DeltaTime(0.0) , AbsoluteTime(0.0) , FramesPerSecond(1.0 / 60.0) #if WITH_EDITOR , bHostBeingDebugged(false) #endif #if RIGVM_TRACE_ENABLED , bHostPlayingRewindDebugTrace(false) #endif , RuntimeSettings() , NameCache(nullptr) #if WITH_EDITOR , LogPtr(nullptr) #endif , DrawInterfacePtr(nullptr) , DrawContainerPtr(nullptr) , ToWorldSpaceTransform(FTransform::Identity) , OwningObject(nullptr) , OwningActor(nullptr) , World(nullptr) , Traits()`
- L341 _public prototype_ `virtual ~FRigVMExecuteContext() = default;`
- L343 _public function_ `virtual void Log(const FRigVMLogSettings& InLogSettings, const FString& InMessage) const`
- L367 _public function_ `template <typename... Types> void Logf(const FRigVMLogSettings& InLogSettings, ::UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L372 _public function_ `int32 GetInstructionIndex() const`
- L374 _public function_ `uint32 GetNumExecutions() const`
- L376 _public function_ `FName GetFunctionName() const`
- L378 _public function_ `FName GetEventName() const`
- L379 _public function_ `void SetEventName(const FName& InName)`
- L382 _public function_ `template<typename T = double> requires std::is_floating_point_v<T> T GetDeltaTime() const`
- L383 _public function_ `void SetDeltaTime(double InDeltaTime)`
- L386 _public function_ `template<typename T = double> requires std::is_floating_point_v<T> T GetAbsoluteTime() const`
- L387 _public function_ `void SetAbsoluteTime(double InAbsoluteTime)`
- L390 _public function_ `template<typename T = double> requires std::is_floating_point_v<T> T GetFramesPerSecond() const`
- L391 _public function_ `void SetFramesPerSecond(double InFramesPerSecond)`
- L394 _public function_ `bool IsHostBeingDebugged() const`
- L395 _public function_ `void SetHostBeingDebugged(bool InIsHostBeingDebugged)`
- L399 _public function_ `bool IsHostPlayingRewindDebugTrace() const`
- L400 _public function_ `void SetHostPlayingRewindDebugTrace(bool InIsHostPlayingRewindDebugTrace)`
- L404 _public function_ `const FTransform& GetToWorldSpaceTransform() const` — The current transform going from rig (global) space to world space
- L407 _public function_ `const UObject* GetOwningObject() const` — The current object this VM is owned by
- L410 _public function_ `const USceneComponent* GetOwningComponent() const` — The current component this VM is owned by
- L413 _public function_ `USceneComponent* GetMutableOwningComponent() const` — The current component this VM is owned by
- L416 _public function_ `const AActor* GetOwningActor() const` — The current actor this VM is owned by
- L419 _public function_ `const UWorld* GetWorld() const` — The world this VM is running in
- L421 _public prototype_ `void SetOwningObject(const UObject* InOwningObject);`
- L423 _public prototype_ `void SetOwningComponent(const USceneComponent* InOwningComponent);`
- L425 _public prototype_ `void SetOwningActor(const AActor* InActor);`
- L427 _public prototype_ `void SetWorld(const UWorld* InWorld);`
- L429 _public function_ `void SetToWorldSpaceTransform(const FTransform& InToWorldSpaceTransform)`
- L434 _public function_ `FTransform ToWorldSpace(const FTransform& InTransform) const` — Converts a transform from VM (global) space to world space
- L442 _public function_ `FTransform ToVMSpace(const FTransform& InTransform) const` — Converts a transform from world space to VM (global) space
- L450 _public function_ `FVector ToWorldSpace(const FVector& InLocation) const` — Converts a location from VM (global) space to world space
- L458 _public function_ `FVector ToVMSpace(const FVector& InLocation) const` — Converts a location from world space to VM (global) space
- L466 _public function_ `FQuat ToWorldSpace(const FQuat& InRotation) const` — Converts a rotation from VM (global) space to world space
- L474 _public function_ `FQuat ToVMSpace(const FQuat& InRotation) const` — Converts a rotation from world space to VM (global) space
- L479 _public function_ `FRigVMNameCache* GetNameCache() const`
- L482 _public function_ `FRigVMLog* GetLog() const`
- L483 _public function_ `void SetLog(FRigVMLog* InLog)`
- L484 _public function_ `virtual void Report(const FRigVMLogSettings& InLogSettings, const FName& InFunctionName, int32 InInstructionIndex, const FString& InMessage) const`
- L497 _public function_ `FRigVMDrawInterface* GetDrawInterface() const`
- L498 _public function_ `void SetDrawInterface(FRigVMDrawInterface* InDrawInterface)`
- L500 _public function_ `const FRigVMDrawContainer* GetDrawContainer() const`
- L501 _public function_ `FRigVMDrawContainer* GetDrawContainer()`
- L502 _public function_ `void SetDrawContainer(FRigVMDrawContainer* InDrawContainer)`
- L504 _public function_ `TArrayView<const FRigVMTraitScope> GetTraits() const`
- L513 _public function_ `TArrayView<FRigVMTraitScope> GetTraits()`
- L518 _public function_ `virtual void Initialize()`
- L527 _public function_ `virtual void Copy(const FRigVMExecuteContext* InOtherContext)`
- L540 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);` — Serialize this type from another
- L545 _public function_ `void MarkExecutionCompleted()` — Completes the execution of this run.
- L553 _public function_ `void ResetNumExecutions()` — Resets the number of executions
- L558 _public member_ `int32 InstructionIndex;`
- L562 _protected function_ `virtual void Reset()`
- L567 _protected member_ `FName EventName;`
- L569 _protected member_ `FName FunctionName;`
- L571 _protected member_ `uint32 NumExecutions;`
- L573 _protected member_ `double DeltaTime;`
- L575 _protected member_ `double AbsoluteTime;`
- L577 _protected member_ `double FramesPerSecond;`
- L580 _protected member_ `bool bHostBeingDebugged;`
- L584 _protected member_ `bool bHostPlayingRewindDebugTrace;`
- L587 _protected member_ `FRigVMRuntimeSettings RuntimeSettings;`
- L589 _protected member_ `mutable FRigVMNameCache* NameCache;`
- L592 _protected member_ `FRigVMLog* LogPtr;`
- L594 _protected member_ `FRigVMDrawInterface* DrawInterfacePtr;`
- L595 _protected member_ `FRigVMDrawContainer* DrawContainerPtr;`
- L598 _protected member_ `FTransform ToWorldSpaceTransform;` — The current transform going from rig (global) space to world space
- L601 _protected member_ `const UObject* OwningObject;` — The current object (usually a component) this VM is owned by
- L604 _protected member_ `const AActor* OwningActor;` — The current actor this VM is owned by
- L607 _protected member_ `const UWorld* World;` — The world this VM is running in
- L610 _protected member_ `TArray<FRigVMTraitScope> Traits;` — The traits accessible to the current instruction
- L613 _protected member_ `TArray<FRigVMMemoryHandle> AdditionalTraitMemoryHandles;` — Additional memory handles for each trait
- L617 _public member_ `bool bDebugExecution = false;`
- L618 _public member_ `FString DebugMemoryString;`
- L620 _protected member_ `TArray<FString> PreviousWorkMemory;`
- L622 _protected member_ `UEnum* InstanceOpCodeEnum;`
- L626 _public function_ `const FRigVMExtendedExecuteContext* GetExtendedExecuteContext() const`
- L627 _public function_ `FRigVMExtendedExecuteContext* GetExtendedExecuteContext()`
- L628 _public prototype_ `const FRigVMFunction* FindDispatchFunction(const FName& InDispatchFunctionName) const;`
- L632 _private member_ `FRigVMExtendedExecuteContext* ExtendedExecuteContext = nullptr;` — Pointer back to owner execute context. Required for lazy branches Execute

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRigVMExecuteContext> : public TStructOpsTypeTraitsBase2<FRigVMExecuteContext>`  
_L643-649_
- inherits: `TStructOpsTypeTraitsBase2<FRigVMExecuteContext>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L646-648_

#### struct `FRigVMExternalVariableRuntimeData`  
`struct FRigVMExternalVariableRuntimeData`  
_L651-659_
- L653 _public function_ `explicit FRigVMExternalVariableRuntimeData(uint8* InMemory) : Memory(InMemory)`
- L658 _public member_ `uint8* Memory = nullptr;`

#### class `FRigVMNativizedVMVariables`  
`class FRigVMNativizedVMVariables`  
_L661-663_

#### struct `FRigVMExecuteCallstackEntry`  
`struct FRigVMExecuteCallstackEntry`  
_L665-677_
- L667 _public prototype_ `FRigVMExecuteCallstackEntry() = default;`
- L669 _public function_ `FRigVMExecuteCallstackEntry(int32 InInstructionIndex, const FRigVMCallableInfo* InCallable) : InstructionIndex(InInstructionIndex) , Callable(InCallable)`
- L675 _public member_ `int32 InstructionIndex = INDEX_NONE;`
- L676 _public member_ `const FRigVMCallableInfo* Callable = nullptr;`

#### struct `FRigVMExecuteCallstack`  
`struct FRigVMExecuteCallstack`  
_L679-724_
- L681 _public prototype_ `FRigVMExecuteCallstack() = default;`
- L683 _public function_ `void Reset()`
- L688 _public function_ `bool IsValidIndex(int32 InIndex) const`
- L693 _public function_ `int32 Num() const`
- L698 _public function_ `bool IsEmpty() const`
- L703 _public function_ `const FRigVMExecuteCallstackEntry& Last() const`
- L708 _public function_ `const FRigVMExecuteCallstackEntry& operator[](int32 InIndex) const`
- L713 _public function_ `int32 Push(const FRigVMExecuteCallstackEntry& InEntry)`
- L718 _public function_ `FRigVMExecuteCallstackEntry Pop()`
- L723 _public member_ `TArray<FRigVMExecuteCallstackEntry> Entries;`

#### struct `FRigVMExecuteCallFrame`  
`struct FRigVMExecuteCallFrame`  
_L733-756_
- desc: Slice addressing and lazy branch execution state for one callable invocation. Loops push/pop slices here; SliceOffsetsPerInstruction and SliceOffsetsPerCallable map each node and callsite to the correct offset into Work memory arrays. Entering a nativized RigVMStruct bends FRigVMExtendedExecuteContext::Frame to point at the Work-owned FRigVMExecuteCallFrame for the duration of StaticExecute.
- L735 _public function_ `void Reset()`
- L744 _public member_ `TArray<FRigVMSlice> Slices;` — The list of active slices. Slices can introduced by loops or callables
- L748 _public member_ `TArray<uint16> SliceOffsetsPerInstruction;` — The slice offset per instruction. Typically only loop / control flow nodes will introduce a new loop slice - thus their offset will increase.
- L753 _public member_ `TArray<uint16> SliceOffsetsPerCallable;` — The slice offset per callable. When multiple call sites invoke the same callable, the offset for that callable index will be increased to make sure each call site gets its own memory.
- L755 _public member_ `TArray<FRigVMInstructionSetExecuteState> LazyBranchExecuteState;`

#### struct `FRigVMExtendedExecuteContext`  
`struct FRigVMExtendedExecuteContext`  
_L763-1173_
- reflection: `USTRUCT(Blueprintable)`
- desc: The execute context is used for mutable nodes to indicate execution order.
- L769 _public function_ `FRigVMExtendedExecuteContext() : PublicDataScope(FRigVMExecuteContext::StaticStruct())`
- L776 _public function_ `FRigVMExtendedExecuteContext(const UScriptStruct* InExecuteContextStruct) : PublicDataScope(InExecuteContextStruct)`
- L787 _public function_ `FRigVMExtendedExecuteContext(const FRigVMExtendedExecuteContext& InOther)`
- L792 _public prototype_ `virtual ~FRigVMExtendedExecuteContext();`
- L795 _public prototype_ `void Reset();` — Full context reset
- L798 _public prototype_ `void ResetExecutionState();` — Resets VM execution state
- L800 _public prototype_ `void CopyMemoryStorage(const FRigVMExtendedExecuteContext& Other);`
- L802 _public prototype_ `FRigVMExtendedExecuteContext& operator =(const FRigVMExtendedExecuteContext& Other);`
- L804 _public prototype_ `virtual void Initialize(const UScriptStruct* InScriptStruct);`
- L806 _public function_ `const UScriptStruct* GetContextPublicDataStruct() const`
- L811 _public function_ `void SetContextPublicDataStruct(const UScriptStruct* InScriptStruct)`
- L821 _public function_ `template<typename ExecuteContextType = FRigVMExecuteContext> const ExecuteContextType& GetPublicData() const`
- L828 _public function_ `template<typename ExecuteContextType = FRigVMExecuteContext> ExecuteContextType& GetPublicData()`
- L836 _public function_ `template<typename ExecuteContextType = FRigVMExecuteContext> ExecuteContextType& GetPublicDataSafe()`
- L845 _public function_ `const FRigVMSlice& GetSlice() const`
- L850 _public function_ `FRigVMSlice& GetSlice()`
- L855 _public function_ `void BeginLoopSlice(int32 InCount, int32 InRelativeIndex = 0)`
- L864 _public function_ `void EndLoopSlice()`
- L884 _public function_ `void BeginCallableSlice(int32 InCallableIndex)`
- L892 _public function_ `void EndCallableSlice()`
- L905 _public function_ `bool IsSliceComplete() const`
- L910 _public function_ `uint32 GetSliceHash() const`
- L920 _public function_ `const FRigVMExecuteCallstack& GetCallstack() const`
- L925 _public function_ `uint32 GetCallstackHash() const`
- L930 _public function_ `uint32 GetHashForLazyBranch() const`
- L935 _public prototype_ `bool StepForward();`
- L936 _public prototype_ `bool StepInto();`
- L937 _public prototype_ `bool StepOut();`
- L939 _public function_ `bool IsValidArrayIndex(int32& InOutIndex, const FScriptArrayHelper& InArrayHelper) const`
- L944 _public function_ `bool IsValidArrayIndex(int32& InOutIndex, int32 InArraySize) const`
- L964 _public function_ `bool IsValidArraySize(int32 InSize) const`
- L981 _public function_ `void SetRuntimeSettings(FRigVMRuntimeSettings InRuntimeSettings)`
- L987 _public function_ `void SetDefaultNameCache()`
- L992 _public function_ `void SetNameCache(FRigVMNameCache* InNameCache)`
- L997 _public function_ `void InvalidateCachedMemory()`
- L1002 _public function_ `void UpdateInstanceMemory(FRigVMMemoryStorageStruct* InLiteralMemory)`
- L1013 _public function_ `uint32 GetNumExecutions() const`
- L1022 _public function_ `void ResetNumExecutions()`
- L1030 _public prototype_ `int32 GetInstructionIndex() const;`
- L1031 _public prototype_ `const URigVM* GetVM() const;`
- L1032 _public prototype_ `URigVM* GetVM();`
- L1033 _public prototype_ `FString GetVMPathName() const;`
- L1034 _public prototype_ `void SetVM(URigVM* InVM);`
- L1036 _public prototype_ `const FRigVMFunction* FindDispatchFunction(const FName& InDispatchFunctionName) const;`
- L1038 _public member_ `uint32 VMHash = 0;`
- L1040 _public member_ `FRigVMMemoryStorageStruct WorkMemoryStorage;`
- L1042 _public member_ `FRigVMMemoryStorageStruct DebugMemoryStorage;`
- L1047 _public member_ `TObjectPtr<URigVMMemoryStorage> WorkMemoryStorageObject_DEPRECATED;` — `UPROPERTY(transient, meta = (DeprecatedProperty, DeprecationMessage = "Please, use WorkMemoryStorage"))` — Deprecated 5.4
- L1053 _public member_ `TObjectPtr<URigVMMemoryStorage> DebugMemoryStorageObject_DEPRECATED;` — `UPROPERTY(transient, meta = (DeprecatedProperty, DeprecationMessage = "Please, use DebugMemoryStorage"))` — Deprecated 5.4
- L1056 _public member_ `FStructOnScope PublicDataScope;`
- L1057 _public member_ `URigVMHost* Host = nullptr;`
- L1059 _private member_ `URigVM* VM = nullptr;`
- L1063 _public member_ `FRigVMExecuteCallFrame FrameStorage;`
- L1064 _public member_ `FRigVMExecuteCallFrame* Frame = nullptr;`
- L1066 _public member_ `FRigVMExecuteCallstack Callstack;`
- L1067 _public member_ `uint32 CallstackHash = 0;`
- L1069 _public member_ `const FRigVMDispatchFactory* Factory = nullptr;`
- L1070 _public member_ `mutable TMap<FName, const FRigVMFunction*> DispatchFunctionMap;`
- L1071 _public member_ `FRigVMNameCache NameCache;`
- L1073 _public member_ `int32 ExecutingThreadId = INDEX_NONE;`
- L1075 _public member_ `TArray<int32> EntriesBeingExecuted;`
- L1077 _public member_ `ERigVMExecuteResult CurrentExecuteResult = ERigVMExecuteResult::Failed;`
- L1078 _public member_ `FName CurrentEntryName = NAME_None;`
- L1079 _public member_ `bool bCurrentlyRunningRootEntry = false;`
- L1081 _public member_ `TArray<FRigVMMemoryStorageStruct*, TInlineAllocator<3>> CurrentVMMemory;`
- L1085 _public member_ `TArray<FRigVMMemoryHandle> CachedMemoryHandles;` — `UE_DEPRECATED(5.8, "CachedMemoryHandles has been deprecated.")`
- L1089 _public member_ `TFunction<void(const FName& EventName)> OnExecutionReachedExitCallback;` — Callback for external objects to be notified when the VM reaches an Exit Operation
- L1091 _public member_ `TArray<FRigVMExternalVariableRuntimeData> ExternalVariableRuntimeData;`
- L1092 _public member_ `TSharedPtr<FRigVMNativizedVMVariables> NativizedVMVariables;`
- L1094 _public prototype_ `const FRigVMOperand* GetDebugOperandForOperand(const FRigVMOperand& InOperand) const;`
- L1095 _public prototype_ `void MarkOperandForDebugging(const FRigVMOperand& InOperand, bool bEnableDebugging = true);`
- L1096 _public prototype_ `void UnmarkOperandForDebugging(const FRigVMOperand& InOperand);`
- L1097 _public prototype_ `void MarkAllOperandsForDebugging(bool bEnableDebugging = true);`
- L1098 _public prototype_ `void UnmarkAllOperandsForDebugging();`
- L1101 _public member_ `TMap<FRigVMOperand, FRigVMOperand> OperandToDebugRegister;` — An optional operand to debug register map only for this context's memory
- L1104 _public member_ `TSet<FRigVMOperand> DebuggedOperands;` — A set indicating which operands should be debugged
- L1109 _public member_ `FRigVMDebugInfo* DebugInfo = nullptr;` — `UE_DEPRECATED(5.8, "DebugInfo pointer has been deprecated, please use DebugInfoWeak.")`
- L1111 _public member_ `TWeakPtr<FRigVMDebugInfo> DebugInfoWeak;`
- L1112 _public member_ `FRigVMDebugInfo* DebugInfoStrong = nullptr;`
- L1114 _public member_ `FRigVMInstructionVisitInfo* InstructionVisitInfo = nullptr;`
- L1116 _public function_ `void SetInstructionVisitInfo(FRigVMInstructionVisitInfo* InInstructionVisitInfo)`
- L1121 _public function_ `FRigVMInstructionVisitInfo* GetRigVMInstructionVisitInfo() const`
- L1126 _public function_ `void SetDebugInfo(const TSharedPtr<FRigVMDebugInfo>& InSharedDebugInfo, bool bForce)`
- L1146 _public function_ `void SetDebugInfo(FRigVMDebugInfo* InDebugInfo)` — `UE_DEPRECATED(5.8, "SetDebugInfo with DebugInfo pointer has been deprecated, please use SharedDebugInfo version.")`
- L1149 _public function_ `FRigVMDebugInfo* GetRigVMDebugInfo() const` — `UE_DEPRECATED(5.8, "GetRigVMDebugInfo has been deprecated, please use GetRigVMDebugInfoWeak instead.")`
- L1151 _public function_ `const TWeakPtr<FRigVMDebugInfo>& GetRigVMDebugInfoWeak() const`
- L1156 _public member_ `FRigVMProfilingInfo* ProfilingInfo = nullptr;`
- L1158 _public function_ `void SetProfilingInfo(FRigVMProfilingInfo* InProfilingInfo)`
- L1163 _public function_ `FRigVMProfilingInfo* GetRigVMProfilingInfo() const`
- L1168 _public member_ `TArray<TTuple<int32, int32>> InstructionBrackets;`

#### Free symbols / members of external scopes

- L37 _macro_ `#define UE_API RIGVM_API`
- L48 _externvar_ `extern TAutoConsoleVariable<bool> CVarRigVMReportAllMessages;`
- L647 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon27b4ce800103`)

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMExternalVariable.h` (Public)


#### struct `FRigVMExternalVariableDef`  
`struct FRigVMExternalVariableDef`  
_L22-157_
- reflection: `USTRUCT(BlueprintType)`
- desc: The external variable can be used to map external / unowned memory into the VM and back out
- L28 _public prototype_ `FRigVMExternalVariableDef() = default;`
- L30 _public function_ `bool operator == (const FRigVMExternalVariableDef& Other) const`
- L42 _public function_ `bool IsValid() const`
- L50 _public function_ `const FGuid& GetGuid() const`
- L60 _public function_ `const FName& GetName() const`
- L65 _public function_ `void SetName(const FName& InName)`
- L70 _public function_ `const FProperty* GetProperty() const`
- L75 _public function_ `void SetProperty(const FProperty* InProperty)`
- L80 _public function_ `const FName& GetBaseCPPType() const`
- L85 _public function_ `const FName& GetExtendedCPPType() const`
- L98 _public function_ `bool IsSameType(const FRigVMExternalVariableDef& InOther) const`
- L105 _public function_ `const UObject* GetCPPTypeObject() const`
- L110 _public function_ `UObject* GetCPPTypeObject()`
- L115 _public function_ `bool IsArray() const`
- L120 _public function_ `bool IsPublic() const`
- L125 _public function_ `void SetIsPublic(bool InIsPublic)`
- L130 _public function_ `bool IsReadOnly() const`
- L135 _public function_ `void SetIsReadOnly(bool InIsReadOnly)`
- L144 _protected prototype_ `void CheckCPPTypeIntegrity() const;`
- L146 _protected member_ `FGuid Guid = FGuid();`
- L147 _protected member_ `FName Name = NAME_None;`
- L148 _protected member_ `const FProperty* Property = nullptr;`
- L149 _protected member_ `FName BaseCPPType = NAME_None;`
- L150 _protected member_ `mutable TOptional<FName> ExtendedCPPType;`
- L151 _protected member_ `UObject* CPPTypeObject = nullptr;`
- L152 _protected member_ `bool bIsArray = false;`
- L153 _protected member_ `bool bIsPublic = false;`
- L154 _protected member_ `bool bIsReadOnly = false;`

#### struct `FRigVMExternalVariable`  
`struct FRigVMExternalVariable : public FRigVMExternalVariableDef`  
_L160-664_
- reflection: `USTRUCT()`
- inherits: `FRigVMExternalVariableDef`
- L165 _public function_ `FRigVMExternalVariable() : FRigVMExternalVariableDef()`
- L170 _public function_ `FRigVMExternalVariable(const FRigVMExternalVariableDef& Other) : FRigVMExternalVariableDef(Other) , Memory(nullptr)`
- L177 _public function_ `FRigVMExternalVariable(const FRigVMExternalVariableDef& Other, uint8* InMemory) : FRigVMExternalVariableDef(Other) , Memory(InMemory)`
- L184 _public function_ `FRigVMExternalVariable(const FRigVMExternalVariable& Other) : FRigVMExternalVariableDef(Other) , Memory(Other.Memory)`
- L190 _public function_ `uint32 GetTypeHash() const`
- L195 _public function_ `const uint8* GetMemory() const`
- L200 _public function_ `uint8* GetMemory()`
- L205 _public function_ `void SetMemory(uint8* InMemory)`
- L218 _public function_ `bool operator == (const FRigVMExternalVariableDef& Other) const`
- L223 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FProperty* InProperty, void* InContainer, const FName& InOptionalName = NAME_None)`
- L253 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, bool& InValue)`
- L266 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, TArray<bool>& InValue)`
- L279 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, int32& InValue)`
- L292 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, TArray<int32>& InValue)`
- L305 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, uint8& InValue)`
- L318 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, TArray<uint8>& InValue)`
- L331 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, float& InValue)`
- L344 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, TArray<float>& InValue)`
- L357 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, double& InValue)`
- L370 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, TArray<double>& InValue)`
- L383 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, FString& InValue)`
- L396 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, TArray<FString>& InValue)`
- L409 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, FName& InValue)`
- L422 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, TArray<FName>& InValue)`
- L439 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, T& InValue)`
- L456 _public function_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, TArray<T>& InValue)`
- L572 _public function_ `template<typename T> T GetValue() const`
- L579 _public function_ `template<typename T> T& GetRef()`
- L586 _public function_ `template<typename T> const T& GetRef() const`
- L593 _public function_ `template<typename T> void SetValue(const T& InValue)`
- L600 _public function_ `template<typename T> TArray<T> GetArray()`
- L607 _public function_ `template<typename T> void SetArray(const TArray<T>& InValue)`
- L613 _public function_ `bool IsValid(bool bAllowNullPtr = false) const`
- L619 _public prototype_ `TRigVMTypeIndex GetTypeIndex() const;`
- L621 _public function_ `FString GetCPPTypeObjectPathName() const`
- L631 _public function_ `template<typename VarType> static void MergeExternalVariable(TArray<VarType>& OutVariables, const VarType& InVariable)`
- L651 _public prototype_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, const FEdGraphPinType& InPinType, bool bInPublic = false, bool bInReadonly = false);`
- L655 _public prototype_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, const FString& InCPPTypePath, bool bInPublic = false, bool bInReadonly = false);`
- L657 _public prototype_ `static FRigVMExternalVariable Make(const FGuid InGuid, const FName& InName, const FString& InCPPType, UObject* InCPPTypeObject, bool bInPublic = false, bool bInReadonly = false);`
- L661 _private member_ `uint8* Memory = nullptr;`

#### Free symbols / members of external scopes

- L210 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMExternalVariable& Variable)`
- L666 _namespace_ `namespace RigVMTypeUtils`
- L669 _prototype_ `FRigVMExternalVariable ExternalVariableFromBPVariableDescription(const FBPVariableDescription& InVariableDescription);` (scope `RigVMTypeUtils`)
- L671 _prototype_ `FRigVMExternalVariable ExternalVariableFromBPVariableDescription(const FBPVariableDescription& InVariableDescription, const UStruct* VariablesStruct, void* Container);` (scope `RigVMTypeUtils`)
- L673 _prototype_ `FRigVMExternalVariable ExternalVariableFromPinType(const FGuid InGuid, const FName& InName, const FEdGraphPinType& InPinType, bool bInPublic = false, bool bInReadonly = false);` (scope `RigVMTypeUtils`)
- L675 _prototype_ `FRigVMExternalVariable ExternalVariableFromCPPTypePath(const FGuid InGuid, const FName& InName, const FString& InCPPTypePath, bool bInPublic = false, bool bInReadonly = false);` (scope `RigVMTypeUtils`)
- L677 _prototype_ `FRigVMExternalVariable ExternalVariableFromCPPType(const FGuid InGuid, const FName& InName, const FString& InCPPType, UObject* InCPPTypeObject, bool bInPublic = false, bool bInReadonly = false);` (scope `RigVMTypeUtils`)
- L680 _prototype_ `TArray<FRigVMExternalVariableDef> GetExternalVariableDefs(const TArray<FRigVMExternalVariable>& ExternalVariables);` (scope `RigVMTypeUtils`)

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMFunction.h` (Public)


#### enum `ERigVMPinDirection`  
`enum class ERigVMPinDirection : uint8`  
_L40-48_
- reflection: `UENUM(BlueprintType)`
- desc: The Pin Direction is used to differentiate different kinds of pins in the data flow graph - inputs, outputs etc.
- L42 _public enumerator_ `Input` — A const input value
- L43 _public enumerator_ `Output` — A mutable output value
- L44 _public enumerator_ `IO` — A mutable input and output value
- L45 _public enumerator_ `Visible` — A const value that cannot be connected to
- L46 _public enumerator_ `Hidden` — A mutable hidden value (used for interal state)
- L47 _public enumerator_ `Invalid` — The max value for this enum - used for guarding.

#### enum `ERigVMFunctionArgumentDirection`  
`enum class ERigVMFunctionArgumentDirection : uint8`  
_L55-60_
- reflection: `UENUM(BlueprintType)`
- desc: The Function Argument is used to differentiate different kinds of pins in the data flow graph - inputs or outputs
- L57 _public enumerator_ `Input` — A const input value
- L58 _public enumerator_ `Output` — A mutable output value
- L59 _public enumerator_ `Invalid` — The max value for this enum - used for guarding.

#### struct `FRigVMCompiledInFunctionArgument`  
`struct FRigVMCompiledInFunctionArgument`  
_L63-68_
- desc: Version of FRigVMFunctionArgument for UHT code generation
- L65 _public member_ `const TCHAR* Name = nullptr;`
- L66 _public member_ `const TCHAR* Type = nullptr;`
- L67 _public member_ `ERigVMFunctionArgumentDirection Direction = ERigVMFunctionArgumentDirection::Input;`

#### struct `FRigVMCompiledInFunction`  
`struct FRigVMCompiledInFunction`  
_L70-75_
- L72 _public member_ `const TCHAR* MethodName = nullptr;`
- L73 _public member_ `FRigVMFunctionPtr Function = nullptr;`
- L74 _public member_ `TConstArrayView<FRigVMCompiledInFunctionArgument> Parameters;`

#### struct `FRigVMFunctionArgument`  
`struct FRigVMFunctionArgument : public FRigVMCompiledInFunctionArgument`  
_L80-112_
- inherits: `FRigVMCompiledInFunctionArgument`
- desc: The FRigVMFunctionArgument describes an argument necessary for the C++ invocation of the RIGVM_METHOD backed function
- L82 _public member_ `TSharedPtr<FString> NameString;`
- L83 _public member_ `TSharedPtr<FString> TypeString;`
- L85 _public function_ `FRigVMFunctionArgument() : FRigVMCompiledInFunctionArgument`
- L90 _public function_ `FRigVMFunctionArgument(FRigVMCompiledInFunctionArgument InBase) : FRigVMCompiledInFunctionArgument(InBase)`
- L95 _public function_ `FRigVMFunctionArgument(const TCHAR* InName, const TCHAR* InType, const ERigVMFunctionArgumentDirection InDirection = ERigVMFunctionArgumentDirection::Input) : FRigVMCompiledInFunctionArgument`
- L100 _public function_ `FRigVMFunctionArgument(const FString& InName, const FString& InType, const ERigVMFunctionArgumentDirection InDirection = ERigVMFunctionArgumentDirection::Input) : FRigVMCompiledInFunctionArgument`
- L109 _public prototype_ `void Serialize_NoLock(FArchive& Ar);`
- L111 _public prototype_ `bool operator ==(const FRigVMFunctionArgument& InOther) const;`

#### struct `FRigVMExecuteArgument`  
`struct FRigVMExecuteArgument`  
_L119-138_
- desc: The FRigVMExecuteArgument describes an execute argument.
- L121 _public member_ `FName Name;`
- L122 _public member_ `ERigVMPinDirection Direction;`
- L123 _public member_ `TRigVMTypeIndex TypeIndex;`
- L125 _public function_ `FRigVMExecuteArgument() : Name(NAME_None) , Direction(ERigVMPinDirection::Invalid) , TypeIndex(INDEX_NONE)`
- L132 _public function_ `FRigVMExecuteArgument(const FName& InName, const ERigVMPinDirection& InDirection, const TRigVMTypeIndex& InTypeIndex = INDEX_NONE) : Name(InName) , Direction(InDirection) , TypeIndex(InTypeIndex)`

#### struct `FRigVMFunction`  
`struct FRigVMFunction`  
_L144-212_
- desc: The FRigVMFunction is used to represent a function pointer generated by UHT for a given name. The name might be something like "FMyStruct::MyVirtualMethod"
- L146 _public member_ `FString Name;`
- L147 _public member_ `UScriptStruct* Struct;`
- L148 _public member_ `FRigVMDispatchFactory* Factory;`
- L149 _public member_ `FRigVMRegistry_NoLock* OwnerRegistry;`
- L150 _public member_ `FRigVMFunctionPtr FunctionPtr;`
- L151 _public member_ `int32 Index;`
- L152 _public member_ `int32 TemplateIndex;`
- L153 _public member_ `int32 PermutationIndex;`
- L154 _public member_ `TArray<FRigVMFunctionArgument> Arguments;`
- L155 _public member_ `mutable TArray<TRigVMTypeIndex> ArgumentTypeIndices;`
- L156 _public member_ `mutable TArray<FName> ArgumentNames;`
- L158 _public function_ `FRigVMFunction() : Name() , Struct(nullptr) , Factory(nullptr) , OwnerRegistry(nullptr) , FunctionPtr(nullptr) , Index(INDEX_NONE) , TemplateIndex(INDEX_NONE) , PermutationIndex(INDEX_NONE) , Arguments() , ArgumentTypeIndices() , ArgumentNames()`
- L173 _public prototype_ `FRigVMFunction(const TCHAR* InName, FRigVMFunctionPtr InFunctionPtr, UScriptStruct* InStruct = nullptr, int32 InIndex = INDEX_NONE, const TArray<FRigVMFunctionArgument>& InArguments = TArray<FRigVMFunctionArgument>());`
- L175 _public function_ `FRigVMFunction(const FString& InName, FRigVMFunctionPtr InFunctionPtr, FRigVMDispatchFactory* InFactory, int32 InIndex = INDEX_NONE, const TArray<FRigVMFunctionArgument>& InArguments = TArray<FRigVMFunctionArgument>()) : Name(InName) , Struct(nullptr) , Factory(InFactory) , OwnerRegistry(nullptr) , FunctionPtr(InFunctionPtr) , Index(InIndex) , TemplateIndex(INDEX_NONE) , PermutationIndex(INDEX_NONE) , Arguments(InArguments) , ArgumentNames()`
- L189 _public function_ `bool IsValid() const`
- L190 _public prototype_ `FString GetName() const;`
- L191 _public prototype_ `FName GetMethodName() const;`
- L192 _public prototype_ `FString GetModuleName() const;`
- L193 _public prototype_ `FString GetModuleRelativeHeaderPath() const;`
- L194 _public function_ `const TArray<FRigVMFunctionArgument>& GetArguments() const`
- L195 _public prototype_ `int32 GetArgumentIndex(const FName& InArgumentName) const;`
- L196 _public prototype_ `const TArray<TRigVMTypeIndex>& GetArgumentTypeIndices() const;`
- L197 _public prototype_ `const TArray<TRigVMTypeIndex>& GetArgumentTypeIndices_NoLock(FRigVMRegistryHandle& InRegistry) const;`
- L198 _public prototype_ `void GetArgumentTypeIndices_NoLock(FRigVMRegistryHandle& InRegistry, TArray<TRigVMTypeIndex>& OutTypeIndices) const;`
- L199 _public prototype_ `const FRigVMTemplate* GetTemplate() const;`
- L200 _public prototype_ `const FRigVMTemplate* GetTemplate_NoLock(const FRigVMRegistryHandle& InRegistry) const;`
- L201 _public prototype_ `const UScriptStruct* GetExecuteContextStruct() const;`
- L202 _public prototype_ `const UScriptStruct* GetExecuteContextStruct_NoLock(const FRigVMRegistryHandle& InRegistry) const;`
- L203 _public prototype_ `bool SupportsExecuteContextStruct(const UScriptStruct* InExecuteContextStruct) const;`
- L204 _public prototype_ `bool SupportsExecuteContextStruct_NoLock(const UScriptStruct* InExecuteContextStruct, const FRigVMRegistryHandle& InRegistry) const;`
- L205 _public prototype_ `const FName& GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const;`
- L206 _public prototype_ `void Serialize_NoLock(FArchive& Ar, FRigVMRegistryHandle& InRegistry, const UObject* Owner = nullptr);`
- L209 _public prototype_ `bool IsFixedSizeArray(const FName& InArgumentName) const;`
- L210 _public prototype_ `bool IsLazyValue(const FName& InArgumentName) const;`

#### Free symbols / members of external scopes

- L27 _typedef_ `typedef TArrayView<FRigVMMemoryHandle> FRigVMMemoryHandleArray;`
- L28 _typedef_ `typedef TArrayView<FRigVMPredicateBranch> FRigVMPredicateBranchArray;`
- L30 _typedef_ `typedef void (*FRigVMFunctionPtr)(FRigVMExtendedExecuteContext& RigVMExecuteContext, FRigVMMemoryHandleArray RigVMMemoryHandles, FRigVMPredicateBranchArray RigVMBranches);`
- L114 _typedef_ `typedef TArray<FRigVMFunctionArgument> FRigVMFunctionArgumentArray;`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMGraphFunctionDefinition.h` (Public)


#### struct `FRigVMFunctionCompilationPropertyDescription`  
`struct FRigVMFunctionCompilationPropertyDescription`  
_L27-68_
- reflection: `USTRUCT()`
- L33 _public member_ `FName Name;` — `UPROPERTY()` — The name of the property to create
- L37 _public member_ `FString CPPType;` — `UPROPERTY()` — The complete CPP type to base a new property off of (for ex: 'TArray<TArray<FVector>>')
- L41 _public member_ `TSoftObjectPtr<UObject> CPPTypeObject;` — `UPROPERTY()` — The tail CPP Type object, for example the UScriptStruct for a struct
- L45 _public member_ `FString DefaultValue;` — `UPROPERTY()` — The default value to use for this property (for example: '(((X=1.000000, Y=2.000000, Z=3.000000)))')
- L66 _public prototype_ `FRigVMPropertyDescription ToPropertyDescription() const;`
- L67 _public prototype_ `static TArray<FRigVMPropertyDescription> ToPropertyDescription(const TArray<FRigVMFunctionCompilationPropertyDescription>& InDescriptions);`

#### struct `FRigVMFunctionCompilationPropertyPath`  
`struct FRigVMFunctionCompilationPropertyPath`  
_L71-99_
- reflection: `USTRUCT()`
- L76 _public member_ `int32 PropertyIndex = INDEX_NONE;` — `UPROPERTY()`
- L79 _public member_ `FString HeadCPPType;` — `UPROPERTY()`
- L82 _public member_ `FString SegmentPath;` — `UPROPERTY()`

#### struct `FRigVMFunctionCompilationData`  
`struct FRigVMFunctionCompilationData`  
_L102-268_
- reflection: `USTRUCT(BlueprintType)`
- L106 _public function_ `FRigVMFunctionCompilationData() : Hash(0) , bEncounteredSurpressedErrors(false)`
- L111 _public function_ `FRigVMFunctionCompilationData(const FRigVMFunctionCompilationData& InOther)`
- L117 _public member_ `FRigVMByteCode ByteCode;` — `UPROPERTY()`
- L120 _public member_ `TArray<FName> FunctionNames;` — `UPROPERTY()`
- L123 _public member_ `TArray<FRigVMFunctionCompilationPropertyDescription> WorkPropertyDescriptions;` — `UPROPERTY()`
- L126 _public member_ `TArray<FRigVMFunctionCompilationPropertyPath> WorkPropertyPathDescriptions;` — `UPROPERTY()`
- L129 _public member_ `TArray<FRigVMFunctionCompilationPropertyDescription> LiteralPropertyDescriptions;` — `UPROPERTY()`
- L132 _public member_ `TArray<FRigVMFunctionCompilationPropertyPath> LiteralPropertyPathDescriptions;` — `UPROPERTY()`
- L135 _public member_ `TArray<FRigVMFunctionCompilationPropertyDescription> DebugPropertyDescriptions;` — `UPROPERTY()`
- L138 _public member_ `TArray<FRigVMFunctionCompilationPropertyPath> DebugPropertyPathDescriptions;` — `UPROPERTY()`
- L141 _public member_ `TArray<FRigVMFunctionCompilationPropertyDescription> ExternalPropertyDescriptions;` — `UPROPERTY()`
- L144 _public member_ `TArray<FRigVMFunctionCompilationPropertyPath> ExternalPropertyPathDescriptions;` — `UPROPERTY()`
- L147 _public member_ `TMap<int32, FName> ExternalRegisterIndexToVariable;` — `UPROPERTY()`
- L150 _public member_ `TMap<FString, FRigVMOperand> Operands;` — `UPROPERTY()`
- L153 _public member_ `TMap<FName, FRigVMOperand> InterfaceOperands;` — `UPROPERTY()`
- L156 _public member_ `uint32 Hash;` — `UPROPERTY()`
- L159 _public member_ `bool bEncounteredSurpressedErrors;` — `UPROPERTY(Transient)`
- L161 _public function_ `bool IsValid() const`
- L166 _public function_ `bool RequiresRecompilation() const`
- L171 _public prototype_ `void Reset();`
- L173 _public prototype_ `FRigVMFunctionCompilationData& operator =(const FRigVMFunctionCompilationData& InOther);`
- L182 _public prototype_ `bool SupportsCallable() const;` — If this function can be turned into a callable. Exceptions include: Array parameters passed in. External variables passed in. Any use of traits.
- L184 _public prototype_ `const TArray<FRigVMFunctionCompilationPropertyDescription>& GetPropertyDescriptions(ERigVMMemoryType InMemoryType) const;`
- L185 _public prototype_ `const TArray<FRigVMFunctionCompilationPropertyPath>& GetPropertyPathDescriptions(ERigVMMemoryType InMemoryType) const;`
- L264 _public member_ `mutable TOptional<bool> bSupportsCallable;`
- L265 _public member_ `mutable FCriticalSection TaskMutex;`

#### struct `FRigVMGraphFunctionArgument`  
`struct FRigVMGraphFunctionArgument`  
_L271-359_
- reflection: `USTRUCT(BlueprintType)`
- L275 _public function_ `FRigVMGraphFunctionArgument() : Name(NAME_None) , DisplayName(NAME_None) , CPPType(NAME_None) , CPPTypeObject(nullptr) , bIsArray(false) , Direction(ERigVMPinDirection::Input) , bIsConst(false) , bIsInputVariable(false)`
- L286 _public prototype_ `FRigVMGraphFunctionArgument(const FRigVMExternalVariable& InExternalVariable);`
- L289 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L292 _public member_ `FName DisplayName;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L295 _public member_ `FName CPPType;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L298 _public member_ `TSoftObjectPtr<UObject> CPPTypeObject;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L301 _public member_ `bool bIsArray;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L304 _public member_ `ERigVMPinDirection Direction;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L307 _public member_ `FString DefaultValue;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L310 _public member_ `bool bIsConst;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L313 _public member_ `bool bIsInputVariable;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L316 _public member_ `TMap<FString, FText> PathToTooltip;` — `UPROPERTY()`
- L319 _public prototype_ `bool IsValid() const;` — True if CPP Type or obj type is valid. May potentially load the CPP Type Object
- L322 _public prototype_ `bool IsCPPTypeObjectValid() const;` — validates and potentially loads the CPP Type Object
- L325 _public prototype_ `bool IsExecuteContext() const;` — returns true if this argument is an execute context
- L345 _public function_ `bool operator==(const FRigVMGraphFunctionArgument& Other) const`
- L350 _public prototype_ `void Serialize(FArchive& Ar);`
- L358 _public prototype_ `FRigVMExternalVariable ToExternalVariable() const;`

#### struct `FRigVMGraphFunctionHeader`  
`struct FRigVMGraphFunctionHeader`  
_L362-464_
- reflection: `USTRUCT(BlueprintType)`
- L366 _public function_ `FRigVMGraphFunctionHeader() : LibraryPointer(nullptr, FString()) , Name(NAME_None)`
- L372 _public member_ `FRigVMGraphFunctionIdentifier LibraryPointer;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionHeader)`
- L375 _public member_ `FRigVMVariant Variant;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionIdentifier)`
- L378 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionHeader)`
- L381 _public member_ `FString NodeTitle;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionHeader)`
- L384 _public member_ `FLinearColor NodeColor = FLinearColor::White;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionHeader)`
- L387 _public member_ `FText Tooltip_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L390 _public member_ `FString Description;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionHeader)`
- L393 _public member_ `FString Category;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionHeader)`
- L396 _public member_ `FString Keywords;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionHeader)`
- L399 _public member_ `TArray<FRigVMGraphFunctionArgument> Arguments;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionHeader)`
- L402 _public member_ `TMap<FRigVMGraphFunctionIdentifier, uint32> Dependencies;` — `UPROPERTY()`
- L405 _public member_ `TArray<FRigVMExternalVariable> ExternalVariables;` — `UPROPERTY()`
- L408 _public member_ `FRigVMNodeLayout Layout;` — `UPROPERTY()`
- L410 _public prototype_ `bool IsMutable() const;`
- L412 _public function_ `bool IsValid() const`
- L414 _public function_ `FString GetHash() const`
- L424 _public function_ `bool operator==(const FRigVMGraphFunctionHeader& Other) const`
- L430 _public prototype_ `IRigVMGraphFunctionHost* GetFunctionHost(bool bLoadIfNecessary = true) const;` — `UE_DEPRECATED(5.8, "Use GetFunctionHostObject instead")`
- L431 _public prototype_ `TScriptInterface<IRigVMGraphFunctionHost> GetFunctionHostObject(bool bLoadIfNecessary = true) const;`
- L433 _public prototype_ `FRigVMGraphFunctionData* GetFunctionData(bool bLoadIfNecessary = true) const;`
- L435 _public function_ `FText GetTooltip() const`
- L446 _public prototype_ `static FRigVMGraphFunctionHeader FindGraphFunctionHeader(const FSoftObjectPath& InFunctionObjectPath, bool* bOutIsPublic = nullptr, FString* OutErrorMessage = nullptr);`
- L448 _public prototype_ `static FRigVMGraphFunctionHeader FindGraphFunctionHeader(const FSoftObjectPath& InHostObjectPath, const FName& InFunctionName, bool* bOutIsPublic = nullptr, FString* OutErrorMessage = nullptr);`
- L450 _public prototype_ `static FRigVMGraphFunctionHeader FindGraphFunctionHeader(const FRigVMGraphFunctionIdentifier& InIdentifier, bool* bOutIsPublic = nullptr, FString* OutErrorMessage = nullptr);`
- L452 _public prototype_ `static FRigVMGraphFunctionHeader FindGraphFunctionHeaderFromHash(const FString& InFunctionHash, bool* bOutIsPublic = nullptr, FString* OutErrorMessage = nullptr);`
- L454 _public prototype_ `TArray<FRigVMExternalVariable> GetExternalVariables() const;`
- L458 _protected prototype_ `static FName GetFunctionNameFromObjectPath(const FString& InObjectPath, const FName& InOptionalFunctionName = NAME_None);`
- L460 _protected member_ `static TFunction<FRigVMGraphFunctionHeader(const FSoftObjectPath&, const FName&, bool*)> FindFunctionHeaderFromPathFunc;`

#### struct `FRigVMGraphFunctionHeaderArray`  
`struct FRigVMGraphFunctionHeaderArray`  
_L467-473_
- reflection: `USTRUCT()`
- L472 _public member_ `TArray<FRigVMGraphFunctionHeader> Headers;` — `UPROPERTY()`

#### struct `FRigVMGraphFunctionData`  
`struct FRigVMGraphFunctionData`  
_L476-528_
- reflection: `USTRUCT(BlueprintType)`
- L480 _public function_ `FRigVMGraphFunctionData()`
- L482 _public function_ `FRigVMGraphFunctionData(const FRigVMGraphFunctionHeader& InHeader) : Header(InHeader)`
- L486 _public member_ `FRigVMGraphFunctionHeader Header;` — `UPROPERTY()`
- L489 _public member_ `FRigVMFunctionCompilationData CompilationData;` — `UPROPERTY()`
- L492 _public member_ `FString SerializedCollapsedNode_DEPRECATED;` — `UPROPERTY()`
- L495 _public member_ `FRigVMObjectArchive CollapseNodeArchive;` — `UPROPERTY()`
- L497 _public prototype_ `bool IsMutable() const;`
- L499 _public prototype_ `bool IsPublic() const;`
- L501 _public function_ `bool operator==(const FRigVMGraphFunctionData& Other) const`
- L506 _public function_ `void ClearCompilationData()`
- L510 _public prototype_ `static FRigVMGraphFunctionData* FindFunctionData(const FSoftObjectPath& InHostObjectPath, const FName& InFunctionName, bool* bOutIsPublic = nullptr, FString* OutErrorMessage = nullptr);`
- L512 _public prototype_ `static FRigVMGraphFunctionData* FindFunctionData(const FRigVMGraphFunctionIdentifier& InIdentifier, bool* bOutIsPublic = nullptr, FString* OutErrorMessage = nullptr);`
- L514 _public prototype_ `static FString GetArgumentNameFromPinHash(const FString& InPinHash);`
- L516 _public prototype_ `FRigVMOperand GetOperandForArgument(const FName& InArgumentName) const;`
- L518 _public prototype_ `bool IsAnyOperandSharedAcrossArguments() const;`
- L520 _public prototype_ `bool PatchSharedArgumentOperandsIfRequired();`
- L521 _public prototype_ `bool PatchExternalVariablesToArguments();`
- L523 _public member_ `static const inline TCHAR* EntryString = TEXT("Ent`
- L524 _public member_ `static const inline TCHAR* ReturnString = TEXT("Ret`
- L525 _public member_ `static TFunction<IRigVMGraphFunctionHost*(UObject*)> GetFunctionHostFromObjectFunc;`

#### struct `FRigVMReferenceNodeData`  
`struct FRigVMReferenceNodeData`  
_L531-553_
- reflection: `USTRUCT()`
- L537 _public function_ `FRigVMReferenceNodeData() :ReferenceNodePath(), ReferencedFunctionIdentifier()`
- L542 _public member_ `FString ReferenceNodePath;` — `UPROPERTY()`
- L545 _public member_ `FString ReferencedFunctionPath_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L548 _public member_ `FRigVMGraphFunctionHeader ReferencedHeader_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L551 _public member_ `FRigVMGraphFunctionIdentifier ReferencedFunctionIdentifier;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API RIGVM_API`
- L23 _externvar_ `extern TAutoConsoleVariable<bool> CVarRigVMCompileFunctionsToCallables;`
- L24 _externvar_ `extern TAutoConsoleVariable<bool> CVarRigVMAllowCallableFallbackToInlining;`
- L47 _function_ `friend uint32 GetTypeHash(const FRigVMFunctionCompilationPropertyDescription& Description)`
- L57 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMFunctionCompilationPropertyDescription& Data)`
- L84 _function_ `friend uint32 GetTypeHash(const FRigVMFunctionCompilationPropertyPath& Path)`
- L92 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMFunctionCompilationPropertyPath& Data)`
- L187 _function_ `friend uint32 GetTypeHash(const FRigVMFunctionCompilationData& Data)`
- L251 _function_ `` (scope `FRigVMFunctionCompilationData::GetTypeHash`)
- L327 _function_ `friend uint32 GetTypeHash(const FRigVMGraphFunctionArgument& Argument)`
- L352 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMGraphFunctionArgument& Data)`
- L419 _function_ `friend uint32 GetTypeHash(const FRigVMGraphFunctionHeader& Header)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMGraphFunctionHost.h` (Public)


#### class `URigVMGraphFunctionHost`  
`class URigVMGraphFunctionHost : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IRigVMGraphFunctionHost`  
`class IRigVMGraphFunctionHost`  
_L19-28_
- desc: Interface that allows an object to host a rig VM graph function Host.
- L26 _public prototype_ `virtual FRigVMGraphFunctionStore* GetRigVMGraphFunctionStore() = 0;` — IRigVMClientHost interface
- L27 _public prototype_ `virtual const FRigVMGraphFunctionStore* GetRigVMGraphFunctionStore() const = 0;`

#### struct `FRigVMGraphFunctionStore`  
`struct FRigVMGraphFunctionStore`  
_L32-103_
- reflection: `USTRUCT()`
- desc: A management struct containing graph functions
- L40 _public member_ `TArray<FRigVMGraphFunctionData> PublicFunctions;` — `UPROPERTY()` — Exposed public functions on this rig
- L43 _public member_ `TArray<FRigVMGraphFunctionData> PrivateFunctions;` — `UPROPERTY(Transient)`
- L45 _public prototype_ `const FRigVMGraphFunctionData* FindFunction(const FRigVMGraphFunctionIdentifier& InLibraryPointer, bool* bOutIsPublic = nullptr) const;`
- L47 _public prototype_ `FRigVMGraphFunctionData* FindFunction(const FRigVMGraphFunctionIdentifier& InLibraryPointer, bool* bOutIsPublic = nullptr);`
- L49 _public prototype_ `FRigVMGraphFunctionData* FindFunctionByName(const FName& Name, bool *bOutIsPublic = nullptr);`
- L51 _public prototype_ `bool ContainsFunction(const FRigVMGraphFunctionIdentifier& InLibraryPointer) const;`
- L53 _public prototype_ `bool IsFunctionPublic(const FRigVMGraphFunctionIdentifier& InLibraryPointer) const;`
- L55 _public prototype_ `FRigVMGraphFunctionData* AddFunction(const FRigVMGraphFunctionHeader& FunctionHeader, bool bIsPublic);`
- L57 _public prototype_ `bool RemoveFunction(const FRigVMGraphFunctionIdentifier& InLibraryPointer, bool* bIsPublic = nullptr);`
- L59 _public prototype_ `bool MarkFunctionAsPublic(const FRigVMGraphFunctionIdentifier& InLibraryPointer, bool bIsPublic);`
- L61 _public prototype_ `FRigVMGraphFunctionData* UpdateFunctionInterface(const FRigVMGraphFunctionHeader& Header);`
- L63 _public prototype_ `bool UpdateDependencies(const FRigVMGraphFunctionIdentifier& InLibraryPointer, TMap<FRigVMGraphFunctionIdentifier, uint32>& Dependencies);`
- L65 _public prototype_ `bool UpdateExternalVariables(const FRigVMGraphFunctionIdentifier& InLibraryPointer, TArray<FRigVMExternalVariable> InExternalVariables);`
- L67 _public prototype_ `bool UpdateFunctionCompilationData(const FRigVMGraphFunctionIdentifier& InLibraryPointer, const FRigVMFunctionCompilationData& CompilationData);`
- L69 _public prototype_ `bool RemoveFunctionCompilationData(const FRigVMGraphFunctionIdentifier& InLibraryPointer);`
- L71 _public prototype_ `bool RemoveAllCompilationData();`
- L91 _public function_ `void PostLoad()`
- L102 _private prototype_ `const FRigVMGraphFunctionData* FindFunctionImpl(const FRigVMGraphFunctionIdentifier& InLibraryPointer, bool* bOutIsPublic = nullptr) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVM_API`
- L73 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMGraphFunctionStore& Host)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMGraphFunctionIdentifier.h` (Public)


#### struct `FRigVMGraphFunctionIdentifier`  
`struct FRigVMGraphFunctionIdentifier`  
_L13-109_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `FSoftObjectPath LibraryNode_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L22 _private member_ `mutable FString LibraryNodePath;` — `UPROPERTY(VisibleAnywhere, Category=FunctionIdentifier)`
- L28 _public member_ `FSoftObjectPath HostObject;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionIdentifier)` — A path to the IRigVMGraphFunctionHost that stores the function information, and compilation data (e.g. RigVMBlueprintGeneratedClass)
- L30 _public function_ `FRigVMGraphFunctionIdentifier() : LibraryNodePath(FString()), HostObject(nullptr)`
- L33 _public function_ `FRigVMGraphFunctionIdentifier(FSoftObjectPath InHostObject, FString InLibraryNodePath) : LibraryNodePath(InLibraryNodePath), HostObject(InHostObject)`
- L41 _public function_ `bool operator==(const FRigVMGraphFunctionIdentifier& Other) const`
- L46 _public function_ `bool IsValid() const`
- L51 _public function_ `FString GetFunctionName() const`
- L65 _public function_ `FName GetFunctionFName() const`
- L74 _public function_ `FString& GetLibraryNodePath() const`
- L83 _public function_ `void SetLibraryNodePath(const FString& InPath)`
- L88 _public function_ `FSoftObjectPath GetNodeSoftPath() const`
- L94 _public prototype_ `FAssetData GetAssetData() const;`
- L99 _public prototype_ `bool IsVariant() const;`
- L100 _public prototype_ `TArray<FRigVMVariantRef> GetVariants(bool bIncludeSelf = false) const;`
- L101 _public prototype_ `TArray<FRigVMGraphFunctionIdentifier> GetVariantIdentifiers(bool bIncludeSelf = false) const;`
- L102 _public prototype_ `bool IsVariantOf(const FRigVMGraphFunctionIdentifier& InOther) const;`
- L106 _protected member_ `static TFunction<TArray<FRigVMVariantRef>(const FGuid& InGuid)> GetVariantRefsByGuidFunc;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVM_API`
- L36 _function_ `friend uint32 GetTypeHash(const FRigVMGraphFunctionIdentifier& Pointer)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMLog.h` (Public)


#### struct `FRigVMLogSettings`  
`struct FRigVMLogSettings`  
_L10-19_
- L12 _public function_ `FRigVMLogSettings(EMessageSeverity::Type InSeverity, bool InLogOnce = true) : Severity(InSeverity) , bLogOnce(InLogOnce)`
- L17 _public member_ `EMessageSeverity::Type Severity;`
- L18 _public member_ `bool bLogOnce;`

#### struct `FRigVMLog`  
`struct FRigVMLog`  
_L21-55_
- L25 _public function_ `FRigVMLog()`
- L26 _public prototype_ `virtual ~FRigVMLog() = default;`
- L43 _public member_ `TArray<FLogEntry> Entries;`
- L44 _public member_ `TMap<FString, bool> KnownMessages;`
- L46 _public prototype_ `TArray<FLogEntry> GetEntries(EMessageSeverity::Type InSeverity = EMessageSeverity::Info, bool bIncludeHigherSeverity = true);`
- L49 _public prototype_ `virtual void Reset();`
- L50 _public prototype_ `virtual void Report(const FRigVMLogSettings& InLogSettings, const FName& InFunctionName, int32 InInstructionIndex, const FString& InMessage);`
- L53 _public prototype_ `void RemoveRedundantEntries();`

#### struct `FRigVMLog::FLogEntry`  
`struct FLogEntry`  
_L29-42_
- L31 _public function_ `FLogEntry(EMessageSeverity::Type InSeverity, const FName& InFunctionName, int32 InInstructionIndex, const FString& InMessage) : Severity(InSeverity) , FunctionName(InFunctionName) , InstructionIndex(InInstructionIndex) , Message(InMessage)`
- L38 _public member_ `EMessageSeverity::Type Severity;`
- L39 _public member_ `FName FunctionName;`
- L40 _public member_ `int32 InstructionIndex;`
- L41 _public member_ `FString Message;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMMemory.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMMemoryCommon.h` (Public)


#### enum `ERigVMMemoryType`  
`enum class ERigVMMemoryType: uint8`  
_L40-48_
- reflection: `UENUM()`
- desc: The type of memory used. Typically we differentiate between Work (Mutable) and Literal (Constant) memory.
- L42 _public enumerator_ `Work = 0` — Mutable state
- L43 _public enumerator_ `Literal = 1` — Const / fixed state
- L44 _public enumerator_ `External = 2` — Unowned external memory
- L45 _public enumerator_ `Debug = 3` — Owned memory used for debug watches
- L46 _public enumerator_ `Invalid`
- L47 _public enumerator_ `Num = Invalid`

#### struct `FRigVMInstructionSetExecuteState`  
`struct FRigVMInstructionSetExecuteState`  
_L68-80_
- reflection: `USTRUCT(BlueprintType)`
- desc: A runtime cache for determining if a set of instruction has to run for this execution of the VM
- L72 _public function_ `FRigVMInstructionSetExecuteState()`
- L76 _public prototype_ `bool RequiresExecute(const uint32& InSliceHash, const uint32& InHashForLazyBranch);`
- L79 _public member_ `TMap<uint32, uint32> SliceHashToCallStackHash;` — `UPROPERTY(transient)`

#### struct `FRigVMOperand`  
`struct FRigVMOperand`  
_L93-189_
- reflection: `USTRUCT()`
- desc: The FRigVMOperand represents an argument used for an operator within the virtual machine. Operands provide information about which memory needs to be referred to, which register within the memory all the way to the actual byte address in memory. The FRigVMOperand is a light weight address for a register in a FRigVMMemoryContainer. For external variables the register index represents the index of the external variable within the running VM.
- L99 _public function_ `FRigVMOperand() : MemoryType(ERigVMMemoryType::Work) , RegisterIndex(UINT16_MAX) , RegisterOffset(UINT16_MAX)`
- L106 _public function_ `FRigVMOperand(ERigVMMemoryType InMemoryType, int32 InRegisterIndex, int32 InRegisterOffset = INDEX_NONE) : MemoryType(InMemoryType) , RegisterIndex(InRegisterIndex < 0 ? UINT16_MAX : (uint16)InRegisterIndex) , RegisterOffset(InRegisterOffset < 0 ? UINT16_MAX : (uint16)InRegisterOffset)`
- L113 _public function_ `bool operator == (const FRigVMOperand& InOther) const`
- L120 _public function_ `bool operator != (const FRigVMOperand& InOther) const`
- L126 _public function_ `bool IsValid() const` — returns the memory type of this argument
- L129 _public function_ `ERigVMMemoryType GetMemoryType() const` — returns the memory type of this argument
- L133 _public function_ `int32 GetContainerIndex() const` — returns the index of the container of this argument this function should be kept in sync with URigVM::GetContainerIndex()
- L148 _public function_ `int32 GetRegisterIndex() const` — returns the index of the register of this argument
- L151 _public function_ `int32 GetRegisterOffset() const` — returns the register offset of this argument
- L158 _public prototype_ `void Serialize(FArchive& Ar);`
- L165 _public function_ `static void ZeroPaddedMemoryIfNeeded(FRigVMOperand* InOperand)`
- L170 _public prototype_ `FString ToString() const;`
- L175 _private member_ `ERigVMMemoryType MemoryType;` — `UPROPERTY()`
- L182 _private member_ `uint16 RegisterIndex;` — `UPROPERTY()` — The index of the register inside of the specific type of memory (work, literal etc). For external variables the register index represents the index of the external variable within the running VM.
- L185 _private member_ `uint16 RegisterOffset;` — `UPROPERTY()`

#### class `FRigVMMemoryStorageImportErrorContext`  
`class FRigVMMemoryStorageImportErrorContext : public FOutputDevice`  
_L197-212_
- inherits: `FOutputDevice`
- desc: Helper class to catch default value import errors on properties
- L201 _public member_ `bool bLogErrors;`
- L202 _public member_ `int32 NumErrors;`
- L204 _public function_ `explicit FRigVMMemoryStorageImportErrorContext(bool InLogErrors = true) : FOutputDevice() , bLogErrors(InLogErrors) , NumErrors(0)`
- L211 _public prototype_ `void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category) override;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define DEBUG_RIGVMMEMORY 0`
- L27 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigVMMemory, Log, All);`
- L28 _macro_ `#define UE_LOG_RIGVMMEMORY(Format, ...) UE_LOG(LogRigVMMemory, Display, (Format), ##__VA_ARGS__)`
- L30 _macro_ `#define UE_LOG_RIGVMMEMORY(Format, ...)`
- L50 _namespace_ `namespace RigVM`
- L53 _function_ `template<typename T = uint8> void ZeroPaddedMemory(void* InFirstMember, const void* InSecondMember)` (scope `RigVM`)
- L153 _function_ `friend uint32 GetTypeHash(const FRigVMOperand& Operand)`
- L159 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMOperand& P)`
- L191 _typedef_ `typedef TArrayView<const FRigVMOperand> FRigVMOperandArray;`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMMemoryDeprecated.h` (Public)


#### enum `ERigVMRegisterType`  
`enum class ERigVMRegisterType : uint8`  
_L34-41_
- reflection: `UENUM()`
- desc: The type of register within the memory.
- L36 _public enumerator_ `Plain` — bool, int32, float, FVector etc. (also structs that do NOT require a constructor / destructor to be valid)
- L37 _public enumerator_ `String` — FString
- L38 _public enumerator_ `Name` — FName
- L39 _public enumerator_ `Struct` — Any USTRUCT (structs which require a constructor / destructor to be valid. structs which have indirection (arrays or strings in them, for example).
- L40 _public enumerator_ `Invalid`

#### struct `FRigVMRegister`  
`struct FRigVMRegister`  
_L54-191_
- reflection: `USTRUCT()`
- desc: The register represents an address with the VM's memory. Within a register we can store arbitrary data, so it provides a series of properties to describe the memory location. Registers also support the notion of slices. A slice is a complete copy of the memory - so for example if your register stores 4 Vectors, then a slice would contain 48 bytes (4 * 3 * 4). The register can however store multiple slices / copies of that if needed. Slices can be used to provide per-invocation memory to functions within the same register. An integrator for example that needs to store a simulated position might want access to a separate memory per loop iteration.
- L58 _public function_ `FRigVMRegister() : Type(ERigVMRegisterType::Invalid) , ByteIndex(INDEX_NONE) , ElementSize(0) , ElementCount(0) , SliceCount(1) , AlignmentBytes(0) , TrailingBytes(0) , Name(NAME_None) , ScriptStructIndex(INDEX_NONE) , bIsArray(false) , bIsDynamic(false) #if WITH_EDITORONLY_DATA , BaseCPPType(NAME_None) , BaseCPPTypeObject(nullptr) #endif`
- L79 _public member_ `ERigVMRegisterType Type;` — `UPROPERTY()` — The type of register (plain, name, string, etc.)
- L83 _public member_ `uint32 ByteIndex;` — `UPROPERTY()` — The index of the first work byte
- L87 _public member_ `uint16 ElementSize;` — `UPROPERTY()` — The size of each store element (for example 4 for a float)
- L91 _public member_ `uint16 ElementCount;` — `UPROPERTY()` — The number of elements in this register (for example the number of elements in an array)
- L96 _public member_ `uint16 SliceCount;` — `UPROPERTY()` — The number of slices (complete copies) (for example the number of iterations on a fixed loop) Potentially redundant state - can be removed.
- L102 _public member_ `uint8 AlignmentBytes;` — `UPROPERTY()` — The number of leading bytes for alignment. Bytes that had to be introduced before the register to align the registers memory as per platform specification.
- L108 _public member_ `uint16 TrailingBytes;` — `UPROPERTY()` — The number of trailing bytes. These originate after shrinking a register. Potentially unused state - can be removed.
- L112 _public member_ `FName Name;` — `UPROPERTY()` — The name of the register (can be None)
- L117 _public member_ `int32 ScriptStructIndex;` — `UPROPERTY()` — For struct registers this is the index of the struct used - otherwise INDEX_NONE
- L121 _public member_ `bool bIsArray;` — `UPROPERTY()` — If true defines this register as an array
- L127 _public member_ `bool bIsDynamic;` — `UPROPERTY()` — If true defines this register to use dynamic storage. Is this an array or singleton value with multiple slices which potentially requires changing count at runtime.
- L134 _public member_ `FName BaseCPPType;` — `UPROPERTY(transient)` — Defines the CPP type used for the register This is only used for debugging purposes in editor.
- L139 _public member_ `TObjectPtr<UObject> BaseCPPTypeObject;` — `UPROPERTY(transient)` — The resolved UScriptStruct / UObject (in the future) used for debugging.
- L143 _public prototype_ `void Serialize(FArchive& Ar);`
- L144 _public prototype_ `void Save(FArchive& Ar);`
- L145 _public prototype_ `void Load(FArchive& Ar);`
- L153 _public function_ `bool IsDynamic() const` — returns true if this register is using a dynamic array for storage
- L156 _public function_ `bool IsNestedDynamic() const` — returns true if this register is using a dynamic array for storage
- L161 _public function_ `uint64 GetWorkByteIndex(int32 InSliceIndex = 0) const` — returns the current address of the register within the data byte array. this can change over time - as the register is moving through slices. use GetFirstAllocatedByte to get the fixed first byte.
- L168 _public function_ `uint64 GetFirstAllocatedByte() const` — returns the first allocated byte in the data byte array
- L174 _public function_ `uint8 GetAlignmentBytes() const` — Returns the leading alignment bytes
- L177 _public function_ `bool IsArray() const` — Returns true if the register stores more than one element
- L180 _public function_ `uint16 GetAllocatedBytes() const` — Returns the number of allocated bytes (including alignment + trailing bytes)
- L183 _public function_ `uint16 GetNumBytesPerSlice() const` — Returns the number of bytes for a complete slice
- L186 _public function_ `uint16 GetNumBytesAllSlices() const` — Returns the number of bytes for all slices
- L189 _public function_ `uint32 GetTotalElementCount() const` — Returns the total number of elements (elementcount * slicecount) in the register

#### struct `FRigVMRegisterOffset`  
`struct FRigVMRegisterOffset`  
_L198-292_
- reflection: `USTRUCT()`
- desc: The register offset represents a memory offset within a register's memory. This can be used to represent memory addresses of array elements within a struct, for example. A register offset's path can look like MyTransformStruct.Transforms[3].Translation.X
- L205 _public function_ `FRigVMRegisterOffset() : Segments() , Type(ERigVMRegisterType::Invalid) , CPPType(NAME_None) , ScriptStruct(nullptr) , ParentScriptStruct(nullptr) , ArrayIndex(0) , ElementSize(0) , CachedSegmentPath()` — default constructor
- L217 _public prototype_ `void Serialize(FArchive& Ar);`
- L218 _public prototype_ `void Save(FArchive& Ar);`
- L219 _public prototype_ `void Load(FArchive& Ar);`
- L227 _public prototype_ `FRigVMRegisterOffset(UScriptStruct* InScriptStruct, const FString& InSegmentPath, int32 InInitialOffset = 0, uint16 InElementSize = 0, const FName& InCPPType = NAME_None);` — constructs a path given a struct and a segment path
- L230 _public prototype_ `uint8* GetData(uint8* InContainer) const;` — returns the data pointer within a container
- L233 _public function_ `const TArray<int32>& GetSegments() const` — returns the segments of this path
- L238 _public prototype_ `bool ContainsArraySegment() const;` — returns true if this register offset contains an array segment. this means the register offset has to traverse a pointer and cannot be cached / collapsed easily
- L240 _public prototype_ `bool operator == (const FRigVMRegisterOffset& InOther) const;`
- L242 _public function_ `bool IsValid() const`
- L243 _public function_ `ERigVMRegisterType GetType() const`
- L244 _public function_ `FName GetCPPType() const`
- L245 _public function_ `FString GetCachedSegmentPath() const`
- L246 _public function_ `int32 GetArrayIndex() const`
- L247 _public prototype_ `uint16 GetElementSize() const;`
- L248 _public function_ `void SetElementSize(uint16 InElementSize)`
- L249 _public prototype_ `UScriptStruct* GetScriptStruct() const;`
- L260 _private member_ `TArray<int32> Segments;` — `UPROPERTY()` — Segments represent the memory offset(s) to use when accessing the target memory. In case of indirection in the source memory each memory offset / jump is stored. So for example: If you are accessing the third Rotation.X of an array of transforms, the segments would read as: [-2, 12] (second array element, and the fourth float) Segment indices less than zero represent array element offsets, while positive numbers represents jumps within a struct.
- L264 _private member_ `ERigVMRegisterType Type;` — `UPROPERTY()` — Type of resulting register (for example Plain for Transform.Translation.X)
- L268 _private member_ `FName CPPType;` — `UPROPERTY()` — The c++ type of the resulting memory (for example float for Transform.Translation.X)
- L272 _private member_ `TObjectPtr<UScriptStruct> ScriptStruct;` — `UPROPERTY()` — The c++ script struct of the resulting memory (for example FVector for Transform.Translation)
- L276 _private member_ `TObjectPtr<UScriptStruct> ParentScriptStruct;` — `UPROPERTY()` — The c++ script struct of the source memory (for example FTransform for Transform.Translation)
- L280 _private member_ `int32 ArrayIndex;` — `UPROPERTY()` — The index of the element within an array (for example 3 for Transform[3])
- L284 _private member_ `uint16 ElementSize;` — `UPROPERTY()` — The number of bytes of the resulting memory (for example 4 (float) for Transform.Translation.X)
- L288 _private member_ `FString CachedSegmentPath;` — `UPROPERTY()` — The cached path of the segments within this register, for example FTransform.Translation.X

#### struct `FRigVMMemoryContainer`  
`struct FRigVMMemoryContainer`  
_L318-597_
- reflection: `USTRUCT()`
- desc: The FRigVMMemoryContainer provides a heterogeneous memory container to store arbitrary data. Each element stored can be referred to using a FRigVMRegister. Elements can be accessed by index (index of the register), FRigVMOperand or by name. Name access is optional and is specified upon construction of the container. The memory container provides a series of templated functions to add and get data. For example: int32 Index = Container.Add<float>(4.f); float& ValueRef = Container.GetRef<float>(Index); This can also be done with arrays: TArray<float> MyArray = {3.f, 4.f, 5.f}; int32 Index = Container.AddFixedArray<float>(MyArray); FRigVMFixedArray<float> ArrayView = Container.GetFixedArray<float>(Index); Registers can store dynamically resizable memory as well by reyling on indirection. Arrays with a single slice are going to be stored as a FRigVMByteArray, [unit8], so for example for a float array in C++ it would be (TArray<float> Param). Single values with multiple slices are also going to be stored as a FRigVMByteArray, [unit8], so for example for a float array in C++ it would be (float Param). Arrays with multiple slices are going to be stored as a FRigVMNestedByteArray, [[unit8]], so for example for a float array in C++ it would be (TArray<float> Param).
- L324 _public prototype_ `FRigVMMemoryContainer(bool bInUseNames = true);`
- L326 _public prototype_ `FRigVMMemoryContainer(const FRigVMMemoryContainer& Other);`
- L327 _public prototype_ `~FRigVMMemoryContainer();`
- L329 _public prototype_ `bool CopyRegisters(const FRigVMMemoryContainer &InOther);`
- L330 _public prototype_ `FRigVMMemoryContainer& operator= (const FRigVMMemoryContainer &InOther);`
- L333 _public function_ `ERigVMMemoryType GetMemoryType() const` — returns the memory type of this container
- L336 _public function_ `void SetMemoryType(ERigVMMemoryType InMemoryType)` — sets the memory type. should only be used when the container is empty
- L339 _public function_ `bool SupportsNames() const` — returns true if this container supports name based lookup
- L342 _public function_ `int32 Num() const` — returns the number of registers in this container
- L345 _public prototype_ `void Reset();` — resets the container but maintains storage.
- L348 _public prototype_ `void Empty();` — resets the container and removes all storage.
- L351 _public function_ `const FRigVMRegister& operator[](int32 InIndex) const` — const accessor for a register based on index
- L354 _public function_ `FRigVMRegister& operator[](int32 InIndex)` — accessor for a register based on index
- L357 _public function_ `const FRigVMRegister& operator[](const FRigVMOperand& InArg) const` — const accessor for a register based on an argument
- L360 _public function_ `FRigVMRegister& operator[](const FRigVMOperand& InArg)` — accessor for a register based on an argument
- L363 _public function_ `const FRigVMRegister& operator[](const FName& InName) const` — const accessor for a register based on a a name. note: only works if SupportsNames() == true
- L366 _public function_ `FRigVMRegister& operator[](const FName& InName)` — accessor for a register based on a a name. note: only works if SupportsNames() == true
- L368 _public function_ `TArray<FRigVMRegister>::RangedForIteratorType begin()`
- L369 _public function_ `TArray<FRigVMRegister>::RangedForConstIteratorType begin() const`
- L370 _public function_ `TArray<FRigVMRegister>::RangedForIteratorType end()`
- L371 _public function_ `TArray<FRigVMRegister>::RangedForConstIteratorType end() const`
- L374 _public function_ `const FRigVMRegister& GetRegister(int32 InIndex) const` — const accessor for a register based on index
- L377 _public function_ `FRigVMRegister& GetRegister(int32 InIndex)` — accessor for a register based on index
- L380 _public function_ `const FRigVMRegister& GetRegister(const FRigVMOperand& InArg) const` — const accessor for a register based on an argument
- L383 _public function_ `FRigVMRegister& GetRegister(const FRigVMOperand& InArg)` — accessor for a register based on an argument
- L386 _public function_ `const FRigVMRegister& GetRegister(const FName& InName) const` — const accessor for a register based on a a name. note: only works if SupportsNames() == true
- L389 _public function_ `FRigVMRegister& GetRegister(const FName& InName)` — accessor for a register based on a a name. note: only works if SupportsNames() == true
- L391 _public prototype_ `void Serialize(FArchive& Ar);`
- L392 _public prototype_ `void Save(FArchive& Ar);`
- L393 _public prototype_ `void Load(FArchive& Ar);`
- L402 _public function_ `FRigVMOperand GetOperand(int32 InRegisterIndex, int32 InRegisterOffset)` — Returns an argument for a given register. This is typically used to store a light weight address for use within a VM.
- L410 _public function_ `FRigVMOperand GetOperand(int32 InRegisterIndex, const FString& InSegmentPath = FString(), int32 InArrayElement = INDEX_NONE)` — Returns an argument for a given register. This is typically used to store a light weight address for use within a VM.
- L429 _private function_ `uint8* GetDataPtr(const FRigVMRegister& Register, int32 InRegisterOffset = INDEX_NONE, int32 InSliceIndex = 0, bool bArrayContent = false) const`
- L481 _public function_ `UScriptStruct* GetScriptStruct(const FRigVMRegister& Register) const` — Returns the script struct used for a given register (can be nullptr for non-struct-registers).
- L492 _public function_ `UScriptStruct* GetScriptStruct(int32 InRegisterIndex, int32 InRegisterOffset = INDEX_NONE) const` — Returns the script struct used for a given register index (can be nullptr for non-struct-registers).
- L507 _public function_ `int32 GetIndex(const FName& InName) const` — Returns the index of a register based on the register name. Note: This only works if SupportsNames() == true
- L537 _public function_ `bool IsNameAvailable(const FName& InPotentialNewName) const` — Returns true if a given name is available for a new register.
- L547 _public prototype_ `int32 GetOrAddRegisterOffset(int32 InRegisterIndex, int32 InArrayElement = 0);` — Adds a register path and returns its index
- L550 _public prototype_ `int32 GetOrAddRegisterOffset(int32 InRegisterIndex, const FString& InSegmentPath, int32 InArrayElement = 0);` — Adds a register path and returns its index
- L553 _public prototype_ `int32 GetOrAddRegisterOffset(int32 InRegisterIndex, UScriptStruct* InScriptStruct, const FString& InSegmentPath, int32 InInitialOffset = 0, int32 InElementSize = 0);` — Adds a register path and returns its index
- L556 _public prototype_ `void UpdateRegisters();` — Updates internal data for topological changes
- L559 _public prototype_ `int32 Allocate(const FName& InNewName, int32 InElementSize, int32 InElementCount, int32 InSliceCount, const uint8* InDataPtr = nullptr, bool bUpdateRegisters = true);` — Allocates a new named register
- L562 _public prototype_ `int32 Allocate(int32 InElementSize, int32 InElementCount, int32 InSliceCount, const uint8* InDataPtr = nullptr, bool bUpdateRegisters = true);` — Allocates a new unnamed register
- L565 _public prototype_ `bool Construct(int32 InRegisterIndex, int32 InElementIndex = INDEX_NONE, int32 InSliceIndex = 0);` — Performs optional construction of data within a struct register
- L568 _public prototype_ `bool Destroy(int32 InRegisterIndex, int32 InElementIndex = INDEX_NONE, int32 InSliceIndex = 0);` — Performs optional destruction of data within a struct register
- L571 _public prototype_ `int32 FindOrAddScriptStruct(UScriptStruct* InScriptStruct);` — Ensures to add a script struct to the internal map if needed
- L574 _public member_ `bool bUseNameMap;` — `UPROPERTY()`
- L577 _public member_ `ERigVMMemoryType MemoryType;` — `UPROPERTY()`
- L580 _public member_ `TArray<FRigVMRegister> Registers;` — `UPROPERTY()`
- L583 _public member_ `TArray<FRigVMRegisterOffset> RegisterOffsets;` — `UPROPERTY()`
- L586 _public member_ `TArray<uint8> Data;` — `UPROPERTY(transient)`
- L589 _public member_ `TArray<TObjectPtr<UScriptStruct>> ScriptStructs;` — `UPROPERTY(transient)`
- L592 _public member_ `TMap<FName, int32> NameMap;` — `UPROPERTY(transient)`
- L595 _public member_ `bool bEncounteredErrorDuringLoad;` — `UPROPERTY(transient)`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API RIGVM_API`
- L27 _typedef_ `typedef TArray<uint8> FRigVMByteArray;`
- L28 _typedef_ `typedef TArray<FRigVMByteArray> FRigVMNestedByteArray;`
- L146 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMRegister& P)`
- L220 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMRegisterOffset& P)`
- L394 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMMemoryContainer& P)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMMemoryStorage.h` (Public)


#### enum `ERigVMExecuteResult`  
`enum class ERigVMExecuteResult : uint8`  
_L45-52_
- L47 _public enumerator_ `Failed`
- L48 _public enumerator_ ``
- L50 _public enumerator_ ``

#### struct `FRigVMBranchInfo`  
`struct FRigVMBranchInfo`  
_L60-122_
- reflection: `USTRUCT()`
- desc: A description of a branch in the VM's bytecode
- L64 _public function_ `FRigVMBranchInfo() : Index(INDEX_NONE) , Label(NAME_None) , InstructionIndex(INDEX_NONE) , ArgumentIndex(INDEX_NONE) , FirstInstruction(INDEX_NONE) , LastInstruction(INDEX_NONE)`
- L73 _public function_ `bool IsValid() const`
- L78 _public prototype_ `void Serialize(FArchive& Ar);`
- L95 _public function_ `static FString GetFixedArrayLabel(const FString& InArrayName, const FString& InElementName)`
- L100 _public function_ `static FName GetFixedArrayLabel(const FName& InArrayName, const FName& InElementName)`
- L106 _public member_ `int32 Index;` — `UPROPERTY()`
- L109 _public member_ `FName Label;` — `UPROPERTY()`
- L112 _public member_ `int32 InstructionIndex;` — `UPROPERTY()`
- L115 _public member_ `int32 ArgumentIndex;` — `UPROPERTY()`
- L118 _public member_ `int32 FirstInstruction;` — `UPROPERTY()`
- L121 _public member_ `int32 LastInstruction;` — `UPROPERTY()`

#### struct `FRigVMLazyBranch`  
`struct FRigVMLazyBranch`  
_L128-157_
- desc: A branch which can be lazily executed
- L132 _public function_ `FRigVMLazyBranch() : VM(nullptr) , BranchInfo() , FunctionPtr(nullptr)`
- L138 _public function_ `FRigVMLazyBranch(int32 InBranchIndex, const TFunction<ERigVMExecuteResult()>& InFunctionPtr) : VM(nullptr) , BranchInfo() , FunctionPtr(InFunctionPtr)`
- L146 _public prototype_ `ERigVMExecuteResult Execute(FRigVMExtendedExecuteContext& Context);`
- L147 _public prototype_ `ERigVMExecuteResult ExecuteIfRequired(FRigVMExtendedExecuteContext& Context, uint32 InSliceHash);`
- L151 _private member_ `URigVM* VM;`
- L152 _private member_ `FRigVMBranchInfo BranchInfo;`
- L153 _private member_ `TFunction<ERigVMExecuteResult()> FunctionPtr;`

#### struct `TRigVMLazyValueBase`  
`struct TRigVMLazyValueBase`  
_L162-184_
- desc: A template container for a lazily computed value
- L166 _public function_ `TRigVMLazyValueBase() : bFollowPropertyPath(false) , SliceHash(UINT32_MAX) , MemoryHandle(nullptr)`
- L173 _public prototype_ `const uint8* GetData(const FRigVMExecuteContext& Context) const;`
- L174 _public function_ `const FRigVMMemoryHandle& GetMemoryHandle()const`
- L178 _protected member_ `bool bFollowPropertyPath;`
- L179 _protected member_ `uint32 SliceHash;`
- L180 _protected member_ `FRigVMMemoryHandle* MemoryHandle;`

#### struct `TRigVMLazyValue`  
`template<typename ComputedType> struct TRigVMLazyValue : public TRigVMLazyValueBase`  
_L190-223_
- inherits: `TRigVMLazyValueBase`
- desc: A template container for a lazily computed value
- L194 _public function_ `TRigVMLazyValue(ComputedType InConstValue) : TRigVMLazyValueBase() , ConstValue(InConstValue)`
- L199 _public function_ `virtual ~TRigVMLazyValue()`
- L203 _public function_ `const ComputedType& Get(const FRigVMExecuteContext& ExecuteContext) const`
- L214 _protected prototype_ `TRigVMLazyValue(const TRigVMLazyValue<ComputedType>& InOther) = delete;`
- L216 _protected function_ `TRigVMLazyValue(const TRigVMLazyValueBase& InOther) : TRigVMLazyValueBase(InOther)`
- L220 _protected member_ `ComputedType ConstValue;`

#### struct `FRigVMForwardedMemoryHandle`  
`struct FRigVMForwardedMemoryHandle`  
_L236-248_
- reflection: `USTRUCT()`
- desc: The FRigVMForwardedMemoryHandle is used to forward memory from a call site to a callable. The compiler compiled callables arguments to this structure. FRigVMMemoryHandles pointing to this structure will use the pointer to perform indirection on the memory.
- L240 _public member_ `const FProperty* Property = nullptr;`
- L241 _public member_ `uint8* Memory = nullptr;`
- L243 _public function_ `void Reset()`

#### struct `FRigVMMemoryHandle`  
`struct FRigVMMemoryHandle`  
_L266-1052_
- desc: The FRigVMMemoryHandle is used to access the memory used within a URigMemoryStorage. The Memory Handle caches the pointer of the head property, and can rely on a RigVMPropertyPath to traverse towards a tail property. For example it can cache the pointer of a TArray<FTransform> property's memory and use a property path of '[2].Translation.X' to retrieve the element 2's translation X float / double. Additionally the FRigVMMemoryHandle can be used to access 'sliced' memory. Sliced memory in this case simply means another level of a nested TArray. So a 'sliced' FTransform is stored as a TArray<FTransform>, which the handle can traverse into and return the memory of a specific FTransform within that array.
- L271 _public function_ `FRigVMMemoryHandle() : Ptr(nullptr) , Property(nullptr) , PropertyPath(nullptr) , LazyBranch(nullptr) , bIsForwarded(false)` — Default constructor
- L280 _public function_ `FRigVMMemoryHandle(uint8* InPtr, const FProperty* InProperty, const FRigVMPropertyPath* InPropertyPath, FRigVMLazyBranch* InLazyBranch = nullptr) : Ptr(InPtr) , Property(InProperty) , PropertyPath(InPropertyPath) , LazyBranch(InLazyBranch) , bIsForwarded(false)` — Constructor from complete data
- L300 _public function_ `uint8* GetData(bool bFollowPropertyPath, int32 InSliceIndex)` — `UE_DEPRECATED(5.7, "Please use GetInputData, GetOutputData or GetPrivateData instead.")` — Returns the cached pointer stored within the handle. @param bFollowPropertyPath If set to true the memory handle will traverse the memory using the property path @param InSliceIndex If this is != INDEX_NONE the memory handle will return the slice of the memory requested @return The traversed memory cached by this handle.
- L312 _public function_ `const uint8* GetData(bool bFollowPropertyPath, int32 InSliceIndex) const` — `UE_DEPRECATED(5.7, "Please use GetInputData, GetOutputData or GetPrivateData instead.")` — Computes the data if necessary and returns the cached pointer stored within the handle. @param bFollowPropertyPath If set to true the memory handle will traverse the memory using the property path @param InSliceIndex If this is != INDEX_NONE the memory handle will return the slice of the memory requested @return The traversed memory cached by this handle (const)
- L322 _public function_ `const uint8* GetInputData(int32 InSliceIndex = INDEX_NONE) const` — Returns the cached pointer stored within the handle. @param InSliceIndex If this is != INDEX_NONE the memory handle will return the slice of the memory requested @return The traversed memory cached by this handle.
- L332 _public function_ `uint8* GetOutputData(int32 InSliceIndex = INDEX_NONE)` — Returns the cached pointer stored within the handle. @param InSliceIndex If this is != INDEX_NONE the memory handle will return the slice of the memory requested @return The traversed memory cached by this handle.
- L342 _public function_ `uint8* GetPrivateData(int32 InSliceIndex)` — Returns the cached pointer stored within the handle. @param InSliceIndex If this is != INDEX_NONE the memory handle will return the slice of the memory requested @return The traversed memory cached by this handle.
- L353 _public function_ `template<typename ComputedType> TRigVMLazyValue<ComputedType> GetDataLazily(int32 InSliceIndex = INDEX_NONE) const` — Computes the data if necessary and returns the cached pointer stored within the handle. @param InSliceIndex If this is != INDEX_NONE the memory handle will return the slice of the memory requested @return The traversed memory cached by this handle (const)
- L362 _public function_ `bool IsLazy() const` — Returns true if this memory handle depends on a lazily executed branch @return True if this memory handle depends on a lazily executed branch
- L371 _public prototype_ `bool ComputeLazyValueIfNecessary(FRigVMExtendedExecuteContext& Context, uint32 InSliceHash);` — Computes the data if necessary and returns true if the value is valid @return True if the value of the handle is valid after the compute
- L374 _public function_ `const FProperty* GetProperty() const` — Returns the head property of this handle
- L386 _public function_ `const FRigVMPropertyPath* GetPropertyPath() const` — Returns the [optional] property path used within this handle
- L392 _public function_ `const FRigVMPropertyPath& GetPropertyPathRef() const` — Returns the [optional] property path used within this handle (ref)
- L402 _public function_ `const FProperty* GetResolvedProperty(bool bIsHiddenArgument = false) const` — Returns the resolved property the data is pointing to
- L418 _public function_ `template<typename PropertyType> bool IsPropertyType(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to a given type of property
- L426 _public function_ `template<typename PropertyType> bool IsPropertyArrayType(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to a given array type of property
- L441 _public function_ `bool IsType(bool bIsHiddenArgument = false) const`
- L462 _public function_ `bool IsTypeArray(bool bIsHiddenArgument = false) const`
- L647 _public function_ `bool IsBool(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to a bool property
- L653 _public function_ `bool IsBoolArray(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to a bool array property
- L659 _public function_ `bool IsFloat(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to a float property
- L665 _public function_ `bool IsFloatArray(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to a float array property
- L671 _public function_ `bool IsDouble(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to a double property
- L677 _public function_ `bool IsDoubleArray(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to a double array property
- L683 _public function_ `bool IsInt32(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to a int32 property
- L689 _public function_ `bool IsInt32Array(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to a int32 array property
- L695 _public function_ `bool IsName(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to an FName property
- L701 _public function_ `bool IsNameArray(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to an FName array property
- L707 _public function_ `bool IsString(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to an FString property
- L713 _public function_ `bool IsStringArray(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to an FString array property
- L719 _public function_ `bool IsEnum(const UEnum* InEnum, bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to an enum property
- L726 _public function_ `bool IsEnumArray(const UEnum* InEnum, bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to an enum array property
- L742 _public function_ `template<typename T> bool IsEnum(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to an enum property
- L749 _public function_ `template<typename T> bool IsEnumArray(bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to an enum array property
- L755 _public function_ `bool IsStruct(const UScriptStruct* InStruct, bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to a struct property
- L762 _public function_ `bool IsStructArray(const UScriptStruct* InStruct, bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to a struct array property
- L781 _public function_ `bool IsStruct(bool bIsHiddenArgument = false) const`
- L801 _public function_ `bool IsStructArray(bool bIsHiddenArgument = false) const`
- L817 _public function_ `bool IsObject(const UClass* InClass, bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to an object property
- L824 _public function_ `bool IsObjectArray(const UClass* InClass, bool bIsHiddenArgument = false) const` — Returns true if this memory handle maps to an objct array property
- L843 _public function_ `bool IsObject(bool bIsHiddenArgument = false) const`
- L853 _public function_ `bool IsObjectArray(bool bIsHiddenArgument = false) const`
- L860 _private function_ `uint8* GetData_Internal(bool bFollowPropertyPath, int32 InSliceIndex) const`
- L950 _private function_ `TRigVMLazyValueBase GetDataLazily_Internal(bool bFollowPropertyPath, uint32 InSliceHash) const`
- L960 _private function_ `static const FProperty* GetArrayElementProperty(const FProperty* InProperty)`
- L969 _private function_ `static const FProperty* GetArrayElementPropertyChecked(const FProperty* InProperty)`
- L975 _private function_ `static bool IsEnum(const FProperty* InProperty, const UEnum* InEnum, bool bUseArrayElement)`
- L999 _private function_ `static bool IsStruct(const FProperty* InProperty, const UScriptStruct* InScriptStruct, bool bUseArrayElement)`
- L1016 _private function_ `static bool IsObject(const FProperty* InProperty, const UClass* InClass, bool bUseArrayElement)`
- L1034 _private member_ `uint8* Ptr;` — The pointer of the memory of the head property
- L1037 _private member_ `const FProperty* Property;` — The head property used by this handle
- L1040 _private member_ `const FRigVMPropertyPath* PropertyPath;` — The [optional] property path used by this handle
- L1043 _private member_ `FRigVMLazyBranch* LazyBranch;` — The [optional] lazy branch used by this handle
- L1046 _private member_ `bool bIsForwarded;` — If this is true the handle points to a FRigVMForwardedMemoryHandle

#### class `URigVMMemoryStorageGeneratorClass`  
`class URigVMMemoryStorageGeneratorClass : public UClass`  
_L1062-1176_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UClass`
- desc: The URigVMMemoryStorageGeneratorClass is used to create / represent heterogeneous memory storages. The generator can produce a UClass which contains a series of properties. This UClass is then used to instantiate URigVMMemoryStorage objects to be consumed by the RigVM. The memory storage objects can contain the literals / constant values used by the virtual machine or work state.
- L1079 _public function_ `URigVMMemoryStorageGeneratorClass() : Super() , MemoryType(ERigVMMemoryType::Literal) , CachedMemoryHash(0)` — Default constructor
- L1086 _public prototype_ `void PurgeClass(bool bRecompilingOnLoad) override;` — UClass overrides
- L1087 _public prototype_ `void Link(FArchive& Ar, bool bRelinkExistingProperties) override;`
- L1088 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L1089 _public prototype_ `virtual void PostLoad() override;`
- L1092 _public prototype_ `static const FString& GetClassName(ERigVMMemoryType InMemoryType);` — Returns the name of a storage class for a given memory type. The name is unique within the package.
- L1095 _public prototype_ `static URigVMMemoryStorageGeneratorClass* GetStorageClass(UObject* InOuter, ERigVMMemoryType InMemoryType);` — Returns an existing class for a memory type within the package (or nullptr)
- L1104 _public prototype_ `static URigVMMemoryStorageGeneratorClass* CreateStorageClass( UObject* InOuter, ERigVMMemoryType InMemoryType, const TArray<FRigVMPropertyDescription>& InProperties, const TArray<FRigVMPropertyPathDescription>& InPropertyPaths = TArray<FRigVMPropertyPathDescription>());` — Creates a new class provided a list of properties and property paths @param InOuter The package or the outer object of this class @param InMemoryType The memory type to use for this class (affects class name) @param InProperties The descriptions for the properties to create @param InPropertyPaths The descriptions for the property paths to create
- L1115 _public prototype_ `static bool RemoveStorageClass( UObject* InOuter, ERigVMMemoryType InMemoryType);` — Removes an existing storage class @param InOuter The package or the outer object of this class @param InMemoryType The memory type to use for this class (affects class name)
- L1120 _public function_ `ERigVMMemoryType GetMemoryType() const` — Returns the type of memory of this class (literal, work, etc)
- L1123 _public prototype_ `uint32 GetMemoryHash() const;` — Returns a hash of unique to the configuration of the memory
- L1126 _public function_ `const TArray<const FProperty*>& GetProperties() const` — The properties stored within this class
- L1129 _public function_ `const TArray<FRigVMPropertyPath>& GetPropertyPaths() const` — The property paths stored within this class
- L1132 _public prototype_ `FRigVMMemoryStatistics GetStatistics() const;` — returns the statistics information
- L1137 _protected prototype_ `static FProperty* AddProperty(URigVMMemoryStorageGeneratorClass* InClass, const FRigVMPropertyDescription& InProperty, FField::FLinkedListBuilder& PropertyListBuilder);` — Adds a single property to a class.
- L1141 _public prototype_ `void RefreshLinkedProperties();`
- L1142 _public prototype_ `void RefreshPropertyPaths();`
- L1144 _public function_ `bool IsValidPropertyPathDescriptionIndex(int32 Index) const`
- L1149 _public function_ `const FRigVMPropertyPathDescription* GetPropertyPathDescriptionByIndex(int32 Index) const`
- L1157 _private member_ `ERigVMMemoryType MemoryType;` — The type of memory of this class
- L1160 _private member_ `TArray<const FProperty*> LinkedProperties;` — A cached list of all linked properties (created by RefreshLinkedProperties)
- L1163 _private member_ `TArray<FRigVMPropertyPath> PropertyPaths;` — A cached list of all property paths (created by RefreshPropertyPaths)
- L1166 _private member_ `TArray<FRigVMPropertyPathDescription> PropertyPathDescriptions;` — A list of decriptions for the property paths - used for serialization
- L1168 _private member_ `mutable uint32 CachedMemoryHash;`

#### class `URigVMMemoryStorage`  
`class URigVMMemoryStorage : public UObject`  
_L1183-1490_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The URigVMMemoryStorage represents an instance of heterogeneous memory. The memory layout is defined by the URigVMMemoryStorageGeneratorClass.
- L1194 _public function_ `ERigVMMemoryType GetMemoryType() const` — Returns the memory type of this memory
- L1205 _public function_ `uint32 GetMemoryHash() const` — Returns a hash of unique to the configuration of the memory
- L1216 _public function_ `int32 Num() const` — Returns the number of properties stored in this instance
- L1222 _public function_ `bool IsValidIndex(int32 InIndex) const` — Returns true if a provided property index is valid
- L1228 _public prototype_ `const TArray<const FProperty*>& GetProperties() const;` — Returns the properties provided by this instance
- L1231 _public prototype_ `const TArray<FRigVMPropertyPath>& GetPropertyPaths() const;` — Returns the property paths provided by this instance
- L1234 _public prototype_ `int32 GetPropertyIndex(const FProperty* InProperty) const;` — Returns the index of a property given the property itself
- L1237 _public prototype_ `int32 GetPropertyIndexByName(const FName& InName) const;` — Returns the index of a property given its name
- L1240 _public function_ `const FProperty* GetProperty(int32 InPropertyIndex) const` — Returns a property given its index
- L1246 _public prototype_ `FProperty* FindPropertyByName(const FName& InName) const;` — Returns a property given its name (or nullptr if the name wasn't found)
- L1249 _public prototype_ `FRigVMOperand GetOperand(int32 InPropertyIndex, int32 InPropertyPathIndex = INDEX_NONE) const;` — Creates and returns a new operand for a property (and optionally a property path)
- L1252 _public prototype_ `FRigVMOperand GetOperandByName(const FName& InName, int32 InPropertyPathIndex = INDEX_NONE) const;` — Creates and returns a new operand for a property (and optionally a property path)
- L1255 _public function_ `FRigVMMemoryStatistics GetStatistics() const` — returns the statistics information
- L1270 _public function_ `bool IsArray(int32 InPropertyIndex) const` — Returns true if the property at a given index is a TArray
- L1276 _public function_ `bool IsMap(int32 InPropertyIndex) const` — Returns true if the property at a given index is a TMap
- L1283 _public function_ `template<typename T> T* GetData(int32 InPropertyIndex)` — Returns the memory for a property given its index
- L1292 _public function_ `template<typename T> T* GetDataByName(const FName& InName)` — Returns the memory for a property given its name (or nullptr)
- L1304 _public function_ `template<typename T> T* GetData(int32 InPropertyIndex, const FRigVMPropertyPath& InPropertyPath)` — Returns the memory for a property given its index and a matching property path
- L1312 _public function_ `template<typename T> T* GetDataByName(const FName& InName, const FRigVMPropertyPath& InPropertyPath)` — Returns the memory for a property given its name and a matching property path (or nullptr)
- L1324 _public function_ `template<typename T> T* GetData(const FRigVMOperand& InOperand)` — Returns the memory for a property (and optionally a property path) given an operand
- L1342 _public function_ `template<typename T> T& GetRef(int32 InPropertyIndex)` — Returns the ref of an element stored at a given property index
- L1349 _public function_ `template<typename T> T& GetRefByName(const FName& InName)` — Returns the ref of an element stored at a given property name (throws if name is invalid)
- L1356 _public function_ `template<typename T> T& GetRef(int32 InPropertyIndex, const FRigVMPropertyPath& InPropertyPath)` — Returns the ref of an element stored at a given property index and a property path
- L1363 _public function_ `template<typename T> T& GetRefByName(const FName& InName, const FRigVMPropertyPath& InPropertyPath)` — Returns the ref of an element stored at a given property name and a property path (throws if name is invalid)
- L1370 _public function_ `template<typename T> T& GetRef(const FRigVMOperand& InOperand)` — Returns the ref of an element stored for a given operand
- L1376 _public prototype_ `FString GetDataAsString(int32 InPropertyIndex, int32 PortFlags = PPF_None);` — Returns the exported text for a given property index
- L1379 _public function_ `FString GetDataAsStringByName(const FName& InName, int32 PortFlags = PPF_None)` — Returns the exported text for given property name
- L1386 _public prototype_ `FString GetDataAsString(const FRigVMOperand& InOperand, int32 PortFlags = PPF_None);` — Returns the exported text for a given operand
- L1389 _public prototype_ `FString GetDataAsStringSafe(int32 InPropertyIndex, int32 PortFlags = PPF_None);` — Returns the exported text for a given property index
- L1392 _public function_ `FString GetDataAsStringByNameSafe(const FName& InName, int32 PortFlags = PPF_None)` — Returns the exported text for given property name
- L1399 _public prototype_ `FString GetDataAsStringSafe(const FRigVMOperand& InOperand, int32 PortFlags = PPF_None);` — Returns the exported text for a given operand
- L1402 _public prototype_ `bool SetDataFromString(int32 InPropertyIndex, const FString& InValue);` — Sets the content of a property by index given an exported string. Returns true if succeeded
- L1405 _public function_ `bool SetDataFromStringByName(const FName& InName, const FString& InValue)` — Sets the content of a property by name given an exported string. Returns true if succeeded
- L1412 _public prototype_ `FRigVMMemoryHandle GetHandle(int32 InPropertyIndex, const FRigVMPropertyPath* InPropertyPath = nullptr);` — Returns the handle for a given property by index (and optionally property path)
- L1415 _public function_ `FRigVMMemoryHandle GetHandleByName(const FName& InName, const FRigVMPropertyPath* InPropertyPath = nullptr)` — Returns the handle for a given property by name (and optionally property path)
- L1429 _public prototype_ `static bool CopyProperty( const FProperty* InTargetProperty, uint8* InTargetPtr, const FProperty* InSourceProperty, const uint8* InSourcePtr);` — Copies the content of a source property and memory into the memory of a target property @param InTargetProperty The target property to copy into @param InTargetPtr The memory of the target value to copy into @param InSourceProperty The source property to copy from @param InSourcePtr The memory of the source value to copy from @return true if the copy operations was successful
- L1446 _public prototype_ `static bool CopyProperty( const FProperty* InTargetProperty, uint8* InTargetPtr, const FRigVMPropertyPath& InTargetPropertyPath, const FProperty* InSourceProperty, const uint8* InSourcePtr, const FRigVMPropertyPath& InSourcePropertyPath);` — Copies the content of a source property and memory into the memory of a target property. This variant supports property paths for both target and source. @param InTargetProperty The target property to copy into @param InTargetPtr The memory of the target value to copy into @param InTargetPropertyPath The property path to use when traversing the target memory. @param InSourceProperty The source property to copy from @param InSourcePtr The memory of the source value to copy from @param InSourcePropertyPath The property path to use when traversing the source memory. @return true if the copy operations was successful
- L1465 _public prototype_ `static bool CopyProperty( URigVMMemoryStorage* InTargetStorage, int32 InTargetPropertyIndex, const FRigVMPropertyPath& InTargetPropertyPath, URigVMMemoryStorage* InSourceStorage, int32 InSourcePropertyIndex, const FRigVMPropertyPath& InSourcePropertyPath);` — Copies the content of a source property and memory into the memory of a target property. This variant retrieves the memory pointers given target and source storage objects. @param InTargetStorage The target property to copy into @param InTargetPropertyIndex The index of the value to use on the InTargetStorage @param InTargetPropertyPath The property path to use when traversing the target memory. @param InSourceStorage The source property to copy from @param InSourcePropertyIndex The index of the value to use on the InSourceStorage @param InSourcePropertyPath The property path to use when traversing the source memory. @return true if the copy operations was successful
- L1480 _public prototype_ `static bool CopyProperty( FRigVMMemoryHandle& InTargetHandle, FRigVMMemoryHandle& InSourceHandle);` — Copies the content of a source property and memory into the memory of a target property. This variant retrieves the memory pointers given target and source storage objects. @param InTargetHandle The handle of the target memory to copy into @param InSourceHandle The handle of the source memory to copy from @return true if the copy operations was successful
- L1484 _public prototype_ `void CopyFrom(URigVMMemoryStorage* InSourceMemory);`
- L1488 _private member_ `static const TArray<const FProperty*> EmptyProperties;`
- L1489 _private member_ `static const TArray<FRigVMPropertyPath> EmptyPropertyPaths;`

#### Free symbols / members of external scopes

- L79 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMBranchInfo& P)`
- L85 _function_ `friend uint32 GetTypeHash(const FRigVMBranchInfo& InBranchInfo)`
- L443 _typedef_ `typedef typename T::ElementType ElementType;` (scope `FRigVMMemoryHandle::IsType`)

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMMemoryStorageStruct.h` (Public)


#### struct `FRigVMMemoryStorageStruct`  
`struct FRigVMMemoryStorageStruct : public FInstancedPropertyBag`  
_L14-424_
- reflection: `USTRUCT()`
- inherits: `FInstancedPropertyBag`
- L18 _public prototype_ `FRigVMMemoryStorageStruct();`
- L19 _public prototype_ `explicit FRigVMMemoryStorageStruct(ERigVMMemoryType InMemoryType);`
- L20 _public prototype_ `FRigVMMemoryStorageStruct(ERigVMMemoryType InMemoryType, const TArray<FRigVMPropertyDescription>& InPropertyDescriptions, const TArray<FRigVMPropertyPathDescription>& InPropertyPaths = TArray<FRigVMPropertyPathDescription>());`
- L21 _public prototype_ `~FRigVMMemoryStorageStruct();`
- L23 _public prototype_ `void InitializeFromNativeStruct(const UScriptStruct* InStruct);`
- L25 _public prototype_ `bool Serialize(FArchive& Ar);`
- L26 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector);`
- L27 _public prototype_ `void GetUserDefinedDependencies(TArray<const UObject*>& OutDependencies) const;`
- L28 _public prototype_ `void GetRequiredPlugins(TArray<FString>& OutPlugins) const;`
- L36 _public function_ `static bool IsClassOf(const FRigVMMemoryStorageStruct* InElement)`
- L43 _public function_ `void SetMemoryType(ERigVMMemoryType InMemoryType)`
- L47 _public function_ `ERigVMMemoryType GetMemoryType() const`
- L59 _public prototype_ `void AddProperties(const TArray<FRigVMPropertyDescription>& InPropertyDescriptions, const TArray<FRigVMPropertyPathDescription>& InPropertyPathDescriptions = TArray<FRigVMPropertyPathDescription>());` — Adds properties to the storage. If property of same name already exists, it will be replaced with the new type. Numeric property values will be converted if possible, when a property's type changes. @param Descriptors : Descriptors of new properties to add.
- L63 _public function_ `int32 Num() const` — Returns the number of properties stored in this instance
- L70 _public function_ `bool IsValidIndex(int32 InIndex) const` — Returns true if a provided property index is valid
- L78 _public function_ `const TArray<const FProperty*>& GetProperties() const` — Returns the properties provided by this instance
- L84 _public function_ `const TArray<FRigVMPropertyPath>& GetPropertyPaths() const` — Returns the property paths provided by this instance
- L90 _public prototype_ `int32 GetPropertyIndex(const FProperty* InProperty) const;` — Returns the index of a property given the property itself
- L93 _public prototype_ `int32 GetPropertyIndexByName(const FName& InName) const;` — Returns the index of a property given its name
- L96 _public function_ `const FProperty* GetProperty(int32 InPropertyIndex) const` — Returns a property given its index
- L103 _public prototype_ `FProperty* FindPropertyByName(const FName& InName) const;` — Returns a property given its name (or nullptr if the name wasn't found)
- L106 _public prototype_ `FRigVMOperand GetOperand(int32 InPropertyIndex, int32 InPropertyPathIndex = INDEX_NONE) const;` — Creates and returns a new operand for a property (and optionally a property path)
- L109 _public prototype_ `FRigVMOperand GetOperandByName(const FName& InName, int32 InPropertyPathIndex = INDEX_NONE) const;` — Creates and returns a new operand for a property (and optionally a property path)
- L112 _public prototype_ `void* GetContainerPtr() const;` — Returns the raw memory storage pointer
- L114 _public prototype_ `uint32 GetMemoryHash() const;`
- L117 _public function_ `bool IsArray(int32 InPropertyIndex) const` — Returns true if the property at a given index is a TArray
- L123 _public function_ `bool IsMap(int32 InPropertyIndex) const` — Returns true if the property at a given index is a TMap
- L132 _public function_ `template<typename T> T* GetData(int32 InPropertyIndex)` — Returns the memory for a property given its index
- L139 _public function_ `template<typename T> const T* GetData(int32 InPropertyIndex) const`
- L148 _public function_ `template<typename T> T* GetDataByName(const FName& InName)` — Returns the memory for a property given its name (or nullptr)
- L160 _public function_ `template<typename T> T* GetData(const FProperty* Property)` — Returns the mutable memory for a given property (or nullptr if does not belong to this storage)
- L170 _public function_ `template<typename T> const T* GetData(const FProperty* Property) const`
- L182 _public function_ `template<typename T> T* GetData(int32 InPropertyIndex, const FRigVMPropertyPath& InPropertyPath)` — Returns the memory for a property given its index and a matching property path
- L190 _public function_ `template<typename T> T* GetDataByName(const FName& InName, const FRigVMPropertyPath& InPropertyPath)` — Returns the memory for a property given its name and a matching property path (or nullptr)
- L202 _public function_ `template<typename T> T* GetData(const FRigVMOperand& InOperand)` — Returns the memory for a property (and optionally a property path) given an operand
- L220 _public function_ `template<typename T> T& GetRef(int32 InPropertyIndex)` — Returns the ref of an element stored at a given property index
- L227 _public function_ `template<typename T> T& GetRefByName(const FName& InName)` — Returns the ref of an element stored at a given property name (throws if name is invalid)
- L234 _public function_ `template<typename T> T& GetRef(int32 InPropertyIndex, const FRigVMPropertyPath& InPropertyPath)` — Returns the ref of an element stored at a given property index and a property path
- L241 _public function_ `template<typename T> T& GetRefByName(const FName& InName, const FRigVMPropertyPath& InPropertyPath)` — Returns the ref of an element stored at a given property name and a property path (throws if name is invalid)
- L248 _public function_ `template<typename T> T& GetRef(const FRigVMOperand& InOperand)` — Returns the ref of an element stored for a given operand
- L256 _public prototype_ `FString GetDataAsString(int32 InPropertyIndex, int32 PortFlags = PPF_None) const;` — Returns the exported text for a given property index
- L259 _public function_ `FString GetDataAsStringByName(const FName& InName, int32 PortFlags = PPF_None) const` — Returns the exported text for given property name
- L266 _public prototype_ `FString GetDataAsString(const FRigVMOperand& InOperand, int32 PortFlags = PPF_None) const;` — Returns the exported text for a given operand
- L269 _public prototype_ `FString GetDataAsStringSafe(int32 InPropertyIndex, int32 PortFlags = PPF_None) const;` — Returns the exported text for a given property index
- L272 _public function_ `FString GetDataAsStringByNameSafe(const FName& InName, int32 PortFlags = PPF_None) const` — Returns the exported text for given property name
- L279 _public prototype_ `FString GetDataAsStringSafe(const FRigVMOperand& InOperand, int32 PortFlags = PPF_None) const;` — Returns the exported text for a given operand
- L282 _public prototype_ `bool SetDataFromString(int32 InPropertyIndex, const FString& InValue);` — Sets the content of a property by index given an exported string. Returns true if succeeded
- L285 _public function_ `bool SetDataFromStringByName(const FName& InName, const FString& InValue)` — Sets the content of a property by name given an exported string. Returns true if succeeded
- L294 _public prototype_ `FRigVMMemoryHandle GetHandle(int32 InPropertyIndex, const FRigVMPropertyPath* InPropertyPath = nullptr);` — Returns the handle for a given property by index (and optionally property path)
- L297 _public function_ `FRigVMMemoryHandle GetHandleByName(const FName& InName, const FRigVMPropertyPath* InPropertyPath = nullptr)` — Returns the handle for a given property by name (and optionally property path)
- L305 _public function_ `void SetPropertyPathDescriptions(const TArray<FRigVMPropertyPathDescription>& InPropertyPathDescriptions)`
- L310 _public function_ `void ResetPropertyPathDescriptions()`
- L315 _public prototype_ `void Refresh();`
- L316 _public prototype_ `void RefreshPropertyPaths();`
- L318 _public function_ `bool IsValidPropertyPathDescriptionIndex(int32 Index) const`
- L323 _public function_ `const FRigVMPropertyPathDescription* GetPropertyPathDescriptionByIndex(int32 Index) const`
- L336 _public prototype_ `static bool CopyProperty( const FProperty* InTargetProperty, uint8* InTargetPtr, const FProperty* InSourceProperty, const uint8* InSourcePtr);` — Copies the content of a source property and memory into the memory of a target property @param InTargetProperty The target property to copy into @param InTargetPtr The memory of the target value to copy into @param InSourceProperty The source property to copy from @param InSourcePtr The memory of the source value to copy from @return true if the copy operations was successful
- L353 _public prototype_ `static bool CopyProperty( const FProperty* InTargetProperty, uint8* InTargetPtr, const FRigVMPropertyPath& InTargetPropertyPath, const FProperty* InSourceProperty, const uint8* InSourcePtr, const FRigVMPropertyPath& InSourcePropertyPath);` — Copies the content of a source property and memory into the memory of a target property. This variant supports property paths for both target and source. @param InTargetProperty The target property to copy into @param InTargetPtr The memory of the target value to copy into @param InTargetPropertyPath The property path to use when traversing the target memory. @param InSourceProperty The source property to copy from @param InSourcePtr The memory of the source value to copy from @param InSourcePropertyPath The property path to use when traversing the source memory. @return true if the copy operations was successful
- L372 _public prototype_ `static bool CopyProperty( FRigVMMemoryStorageStruct* InTargetStorage, int32 InTargetPropertyIndex, const FRigVMPropertyPath& InTargetPropertyPath, FRigVMMemoryStorageStruct* InSourceStorage, int32 InSourcePropertyIndex, const FRigVMPropertyPath& InSourcePropertyPath);` — Copies the content of a source property and memory into the memory of a target property. This variant retrieves the memory pointers given target and source storage objects. @param InTargetStorage The target property to copy into @param InTargetPropertyIndex The index of the value to use on the InTargetStorage @param InTargetPropertyPath The property path to use when traversing the target memory. @param InSourceStorage The source property to copy from @param InSourcePropertyIndex The index of the value to use on the InSourceStorage @param InSourcePropertyPath The property path to use when traversing the source memory. @return true if the copy operations was successful
- L387 _public prototype_ `static bool CopyProperty( FRigVMMemoryHandle& InTargetHandle, FRigVMMemoryHandle& InSourceHandle);` — Copies the content of a source property and memory into the memory of a target property. This variant retrieves the memory pointers given target and source storage objects. @param InTargetHandle The handle of the target memory to copy into @param InSourceHandle The handle of the source memory to copy from @return true if the copy operations was successful
- L394 _public prototype_ `const UStruct * GetStruct() const;` — Returns the PropertyBag struct using a standard function signature, so it can be used at IStructureDataProvider
- L397 _public prototype_ `static FPropertyBagPropertyDesc GeneratePropertyBagDescriptor(const FRigVMPropertyDescription& RigVMDescriptor);` — Helper function to generate a property bag desc from a FRigVMPropertyDescription
- L400 _protected member_ `ERigVMMemoryType MemoryType = ERigVMMemoryType::Invalid;`
- L402 _protected member_ `TArray<FRigVMPropertyPathDescription> PropertyPathDescriptions;`
- L405 _protected member_ `TArray<const FProperty*> LinkedProperties;` — A cached list of all linked properties (created by RefreshLinkedProperties)
- L408 _protected member_ `TArray<FRigVMPropertyPath> PropertyPaths;` — A cached list of all property paths (created by RefreshPropertyPaths)
- L412 _protected member_ `mutable int32 CachedMemoryHash = 0;`
- L414 _protected member_ `static const TArray<const FProperty*> EmptyProperties;`
- L415 _protected member_ `static const TArray<FRigVMPropertyPath> EmptyPropertyPaths;`
- L417 _protected prototype_ `void ForEachObjectDependency(const TFunction<void(const UObject*)>& InCallBack) const;`
- L419 _protected prototype_ `void RefreshLinkedProperties();`
- L421 _protected prototype_ `void SetDefaultValues(const TArray<FRigVMPropertyDescription>& InPropertyDescriptions);`
- L423 _protected prototype_ `static bool GetPropertyTypeDataFromVMDescriptor(const FRigVMPropertyDescription& RigVMDescriptor, EPropertyBagPropertyType& OutBagPropertyType, FPropertyBagContainerTypes& OutBagContainerTypes);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRigVMMemoryStorageStruct> : public TStructOpsTypeTraitsBase2<FRigVMMemoryStorageStruct>`  
_L426-433_
- inherits: `TStructOpsTypeTraitsBase2<FRigVMMemoryStorageStruct>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L429-432_

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGVM_API`
- L30 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMMemoryStorageStruct& P)`
- L430 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon341d67bb0103`)
- L431 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon341d67bb0103`)

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMNameCache.h` (Public)


#### enum `ERigVMNameOp`  
`enum class ERigVMNameOp : uint8`  
_L7-23_
- L9 _public enumerator_ `None`
- L10 _public enumerator_ `Concat`
- L11 _public enumerator_ `Left`
- L12 _public enumerator_ `Right`
- L13 _public enumerator_ `LeftChop`
- L14 _public enumerator_ `RightChop`
- L15 _public enumerator_ `ReplaceCase`
- L16 _public enumerator_ `ReplaceNoCase`
- L17 _public enumerator_ `EndsWithCase`
- L18 _public enumerator_ `EndsWithNoCase`
- L19 _public enumerator_ `StartsWithCase`
- L20 _public enumerator_ `StartsWithNoCase`
- L21 _public enumerator_ `ContainsCase`
- L22 _public enumerator_ `ContainsNoCase`

#### struct `FRigVMNameOp`  
`struct FRigVMNameOp`  
_L25-107_
- L29 _public function_ `FRigVMNameOp() : A(INDEX_NONE) , B(INDEX_NONE) , C(INDEX_NONE) , Type(ERigVMNameOp::None)`
- L36 _public function_ `static uint32 GetTypeHash(const FName& InName)`
- L41 _public prototype_ `static FRigVMNameOp Concat(const FName& InA, const FName& InB);`
- L42 _public prototype_ `static FRigVMNameOp Left(const FName& InA, const uint32 InCount);`
- L43 _public prototype_ `static FRigVMNameOp Right(const FName& InA, const uint32 InCount);`
- L44 _public prototype_ `static FRigVMNameOp LeftChop(const FName& InA, const uint32 InCount);`
- L45 _public prototype_ `static FRigVMNameOp RightChop(const FName& InA, const uint32 InCount);`
- L46 _public prototype_ `static FRigVMNameOp Replace(const FName& InA, const FName& InB, const FName& InC, const ESearchCase::Type InSearchCase);`
- L47 _public prototype_ `static FRigVMNameOp EndsWith(const FName& InA, const FName& InB, const ESearchCase::Type InSearchCase);`
- L48 _public prototype_ `static FRigVMNameOp StartsWith(const FName& InA, const FName& InB, const ESearchCase::Type InSearchCase);`
- L49 _public prototype_ `static FRigVMNameOp Contains(const FName& InA, const FName& InB, const ESearchCase::Type InSearchCase);`
- L56 _public function_ `bool operator ==(const FRigVMNameOp& Other) const`
- L61 _public function_ `bool operator !=(const FRigVMNameOp& Other) const`
- L66 _public function_ `bool operator <(const FRigVMNameOp& Other) const`
- L83 _public function_ `bool operator >(const FRigVMNameOp& Other) const`
- L103 _private member_ `uint32 A;`
- L104 _private member_ `uint32 B;`
- L105 _private member_ `uint32 C;`
- L106 _private member_ `ERigVMNameOp Type;`

#### class `FRigVMNameCache`  
`class FRigVMNameCache`  
_L109-146_
- L113 _public function_ `void Reset()`
- L119 _public prototype_ `FName Concat(const FName& InA, const FName& InB);`
- L120 _public prototype_ `FName Left(const FName& InA, const uint32 InCount);`
- L121 _public prototype_ `FName Right(const FName& InA, const uint32 InCount);`
- L122 _public prototype_ `FName LeftChop(const FName& InA, const uint32 InCount);`
- L123 _public prototype_ `FName RightChop(const FName& InA, const uint32 InCount);`
- L124 _public prototype_ `FName Replace(const FName& InA, const FName& InB, const FName& InC, const ESearchCase::Type InSearchCase);`
- L125 _public prototype_ `bool EndsWith(const FName& InA, const FName& InB, const ESearchCase::Type InSearchCase);`
- L126 _public prototype_ `bool StartsWith(const FName& InA, const FName& InB, const ESearchCase::Type InSearchCase);`
- L127 _public prototype_ `bool Contains(const FName& InA, const FName& InB, const ESearchCase::Type InSearchCase);`
- L129 _public function_ `const TMap<FRigVMNameOp, FName>& GetNameCache() const`
- L130 _public function_ `const TMap<FRigVMNameOp, bool>& GetBoolCache() const`
- L131 _public prototype_ `TArray<FRigVMNameOp> GetNameOps() const;`
- L132 _public prototype_ `TArray<FName> GetNameValues() const;`
- L133 _public prototype_ `TArray<FRigVMNameOp> GetBoolOps() const;`
- L134 _public prototype_ `TArray<bool> GetBoolValues() const;`
- L139 _private prototype_ `bool CheckCacheSize() const;`
- L144 _private member_ `TMap<FRigVMNameOp, FName> NameCache;`
- L145 _private member_ `TMap<FRigVMNameOp, bool> BoolCache;`

#### Free symbols / members of external scopes

- L51 _function_ `friend uint32 GetTypeHash(const FRigVMNameOp& Op)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMNativized.h` (Public)


#### struct `FRigVMNativizedContext`  
`struct FRigVMNativizedContext`  
_L59-64_
- L61 _public prototype_ `FRigVMNativizedContext(FRigVMExtendedExecuteContext& InExecuteContext, FRigVMExecuteContext& InPublicContext);`
- L62 _public member_ `FRigVMExtendedExecuteContext& ExecuteContext;`
- L63 _public member_ `FRigVMExecuteContext& PublicContextBase;`

#### class `TRigVMNativizedLazyValue`  
`template<typename ComputedType> class TRigVMNativizedLazyValue : public TRigVMLazyValue<ComputedType>`  
_L67-108_
- inherits: `TRigVMLazyValue<ComputedType>`
- L70 _public function_ `TRigVMNativizedLazyValue(const ComputedType& Value, const FProperty* Property) : TRigVMLazyValue<ComputedType>(Value) , NativizedMemoryHandle((uint8*)&Value, Property, nullptr, nullptr)`
- L77 _public function_ `TRigVMNativizedLazyValue(const ComputedType& Value, const FProperty* Property, int32 InBranchIndex, const TFunction<ERigVMExecuteResult()>& ComputeCallback) : TRigVMLazyValue<ComputedType>(Value) , LazyBranch(InBranchIndex, ComputeCallback) , NativizedMemoryHandle((uint8*)&Value, Property, nullptr, &LazyBranch)`
- L85 _public function_ `TRigVMNativizedLazyValue(const ComputedType& Value, const FProperty* Property, const TFunction<ERigVMExecuteResult()>& ComputeCallback) : TRigVMNativizedLazyValue(Value, Property, INDEX_NONE, ComputeCallback)`
- L90 _public function_ `virtual ~TRigVMNativizedLazyValue() override`
- L94 _public function_ `operator const ComputedType& () const`
- L99 _public function_ `operator ComputedType& ()`
- L106 _private member_ `FRigVMLazyBranch LazyBranch;`
- L107 _private member_ `FRigVMMemoryHandle NativizedMemoryHandle;`

#### class `URigVMNativized`  
`class URigVMNativized : public URigVM`  
_L111-558_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `URigVM`
- L117 _public prototype_ `URigVMNativized();`
- L120 _public prototype_ `static UClass* FindClassForHash(uint32 InVMHash);`
- L121 _public prototype_ `static void RegisterClassForHash(uint32 InVMHash, UClass* InClass);`
- L122 _public prototype_ `static TMap<uint32, UClass*>& GetNativizedClassMap();`
- L125 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — URigVM interface
- L126 _public function_ `virtual void PostLoad() override`
- L127 _public prototype_ `virtual void Reset(FRigVMExtendedExecuteContext& Context) override;`
- L128 _public function_ `virtual bool IsNativized() const override`
- L129 _public function_ `virtual void Empty(FRigVMExtendedExecuteContext& Context) override`
- L130 _public prototype_ `virtual bool Initialize(FRigVMExtendedExecuteContext& Context) override;`
- L131 _public prototype_ `virtual ERigVMExecuteResult ExecuteVM(FRigVMExtendedExecuteContext& Context, const FName& InEntryName = NAME_None) override;`
- L132 _public function_ `virtual int32 AddRigVMFunction(UScriptStruct* InRigVMStruct, const FName& InMethodName) override`
- L133 _public function_ `virtual FString GetRigVMFunctionName(int32 InFunctionIndex) const override`
- L134 _public prototype_ `virtual FRigVMMemoryStorageStruct* GetMemoryByType(FRigVMExtendedExecuteContext& Context, ERigVMMemoryType InMemoryType) override;`
- L135 _public prototype_ `virtual const FRigVMMemoryStorageStruct* GetMemoryByType(const FRigVMExtendedExecuteContext& Context, ERigVMMemoryType InMemoryType) const override;`
- L136 _public function_ `virtual void ClearMemory(FRigVMExtendedExecuteContext& Context) override`
- L137 _public prototype_ `virtual const FRigVMInstructionArray& GetInstructions() override;`
- L138 _public prototype_ `virtual const FRigVMByteCode& GetByteCode() const override;`
- L139 _public prototype_ `virtual const TArray<const FRigVMFunction*>& GetFunctions() const override;`
- L140 _public prototype_ `virtual const TArray<FName>& GetFunctionNames() const override;`
- L141 _public prototype_ `virtual const TArray<const FRigVMDispatchFactory*>& GetFactories() const override;`
- L142 _public function_ `virtual bool ContainsEntry(const FName& InEntryName) const override`
- L143 _public function_ `virtual int32 FindEntry(const FName& InEntryName) const override`
- L144 _public function_ `virtual const TArray<FName>& GetEntryNames() const override`
- L147 _public function_ `[[nodiscard]] virtual bool SetInstructionIndex(FRigVMExtendedExecuteContext& Context, FRigVMExecuteContext& PublicData, int32 InInstructionIndex) const override` — `UE_DEPRECATED(5.8, "Please, use with FRigVMNativizedContext param")`
- L164 _public function_ `[[nodiscard]] bool SetInstructionIndex(FRigVMNativizedContext& Context, int32 InInstructionIndex) const`
- L180 _public prototype_ `virtual URigVM* GetSourceVM() const;`
- L182 _public prototype_ `void SetSourceVM(URigVM* InSourceVM);`
- L186 _public function_ `template<typename T> T* SetupNativizedVariables(FRigVMExtendedExecuteContext& Context)`
- L192 _public function_ `template<typename T> T* GetNativizedVariables(FRigVMExtendedExecuteContext& Context)`
- L198 _public function_ `virtual void SetExternalVariablesInstanceData(FRigVMExtendedExecuteContext& Context, const TArray<FRigVMExternalVariable>& InExternalVariables, bool bAllowNullMemory = false) override`
- L203 _protected function_ `template<typename ExecuteContextType = FRigVMExecuteContext> ExecuteContextType& GetPublicContext(FRigVMExtendedExecuteContext& Context, int32 InNumberInstructions, int32 InNumberCallables, const FName& InEntryName)`
- L214 _protected prototype_ `const FRigVMFunction* FindDispatchFunction(const FString& InIdentifier) const;`
- L217 _protected member_ `mutable TWeakObjectPtr<URigVM> WeakSourceVM;`
- L238 _protected function_ `void BeginLoopSlice(FRigVMNativizedContext& Context, int32 InCount, int32 InRelativeIndex = 0)`
- L243 _protected function_ `void EndLoopSlice(FRigVMNativizedContext& Context)`
- L248 _protected function_ `void BeginCallableSlice(FRigVMNativizedContext& Context, int32 InCallableIndex)`
- L253 _protected function_ `void EndCallableSlice(FRigVMNativizedContext& Context)`
- L258 _protected function_ `bool IsValidArraySize(const FRigVMNativizedContext& Context, int32 InArraySize) const`
- L264 _protected function_ `template<typename T> bool IsValidArrayIndex(const FRigVMNativizedContext& Context, int32& InOutIndex, const TArray<T>& InArray) const`
- L270 _protected function_ `template<typename T> static const T& GetArrayElementSafe(const TArray<T>& InArray, const int32 InIndex)`
- L281 _protected function_ `template<typename T> static T& GetArrayElementSafe(TArray<T>& InArray, const int32 InIndex)`
- L292 _protected function_ `template<typename A, typename B> static void CopyUnrelatedArrays(TArray<A>& Target, const TArray<B>& Source)`
- L302 _protected function_ `void BroadcastExecutionReachedExit(FRigVMExtendedExecuteContext& Context)`
- L315 _protected function_ `template<typename T> T& GetExternalVariableRef(const FName& InExternalVariableName, const FName& InExpectedType, const TArray<FRigVMExternalVariable>& InExternalVariables, TMap<FName,int32>& InLookup) const`
- L344 _public function_ `template<typename TargetT, typename SourceT> static void Copy(const SourceT& InSource, TargetT& InTarget)`
- L350 _public function_ `template<typename ArrayType> static typename ArrayType::ElementType& GetOperandSlice(FRigVMNativizedContext& Context, ArrayType& InOutArray, const typename ArrayType::ElementType* InDefaultValue = nullptr)`
- L356 _public function_ `template<typename ArrayType> static typename ArrayType::ElementType& GetOperandSlice(FRigVMExtendedExecuteContext& Context, ArrayType& InOutArray, const typename ArrayType::ElementType* InDefaultValue = nullptr)`
- L377 _public function_ `static T GetStructConstant(const FString& InDefaultValue)`
- L407 _public function_ `static TArray<T> GetStructArrayConstant(const FString& InDefaultValue)`
- L437 _public function_ `static TArray<TArray<T>> GetStructArrayArrayConstant(const FString& InDefaultValue)`
- L547 _protected function_ `bool ImportDefaultValue(T& OutValue, const FProperty* Property, const FString& InBuffer)`
- L561 _function_ `template<> inline void URigVMNativized::Copy(const double& InSource, float& InTarget)`
- L567 _function_ `template<> inline void URigVMNativized::Copy(const float& InSource, double& InTarget)`
- L573 _function_ `template<> inline void URigVMNativized::Copy(const TArray<double>& InSource, TArray<float>& InTarget)`
- L584 _function_ `template<> inline void URigVMNativized::Copy(const TArray<float>& InSource, TArray<double>& InTarget)`

#### class `URigVMNativized::FErrorPipe`  
`class FErrorPipe : public FOutputDevice`  
_L220-236_
- inherits: `FOutputDevice`
- L224 _public member_ `int32 NumErrors;`
- L226 _public function_ `FErrorPipe() : FOutputDevice() , NumErrors(0)`
- L232 _public function_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category) override`

#### class `URigVMNativized::FDefaultValueImportErrorPipe`  
`class FDefaultValueImportErrorPipe : public FOutputDevice`  
_L465-480_
- inherits: `FOutputDevice`
- L469 _public member_ `FString Owner;`
- L470 _public member_ `int32 NumErrors;`
- L472 _public function_ `FDefaultValueImportErrorPipe(const FString& InOwner) : FOutputDevice() , Owner(InOwner) , NumErrors(0)`
- L479 _public prototype_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category) override;`

#### struct `URigVMNativized::FRigVMNativizedCallstackGuard`  
`struct FRigVMNativizedCallstackGuard`  
_L482-543_
- L485 _public function_ `FRigVMNativizedCallstackGuard(FRigVMNativizedContext& InContext, const FRigVMCallableInfo* InCallable = nullptr) : Context(InContext.ExecuteContext) , PublicData(InContext.PublicContextBase) , PreviousInstructionIndex(INDEX_NONE) , PreviousNumSlices(InContext.ExecuteContext.Frame->Slices.Num()) , PreviousCallstackHash(Context.CallstackHash) , bIsCallable(false)`
- L511 _public function_ `~FRigVMNativizedCallstackGuard()`
- L537 _private member_ `FRigVMExtendedExecuteContext& Context;`
- L538 _private member_ `FRigVMExecuteContext& PublicData;`
- L539 _private member_ `int32 PreviousInstructionIndex;`
- L540 _private member_ `int32 PreviousNumSlices;`
- L541 _private member_ `uint32 PreviousCallstackHash;`
- L542 _private member_ `bool bIsCallable;`

#### struct `FPlaneRef`  
`struct FPlaneRef`  
_L594-613_
- L597 _public function_ `FPlaneRef(FMatrix& InMatrix, int32 InColumn) : Matrix(InMatrix) , Column(InColumn) , X(Matrix.M[0][InColumn]) , Y(Matrix.M[1][InColumn]) , Z(Matrix.M[2][InColumn]) , W(Matrix.M[3][InColumn])`
- L607 _public member_ `FMatrix& Matrix;`
- L608 _public member_ `int32 Column;`
- L609 _public member_ `FMatrix::FReal& X;`
- L610 _public member_ `FMatrix::FReal& Y;`
- L611 _public member_ `FMatrix::FReal& Z;`
- L612 _public member_ `FMatrix::FReal& W;`

#### Free symbols / members of external scopes

- L33 _macro_ `#define UE_API RIGVM_API`
- L39 _macro_ `#define RIGVMNATIVIZED_ARRAYTYPE_BODY(NativeType) \`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMNodeLayout.h` (Public)


#### struct `FRigVMPinCategory`  
`struct FRigVMPinCategory`  
_L11-73_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public function_ `FRigVMPinCategory() : Path() , Elements() , bExpandedByDefault(true)`
- L22 _public member_ `FString Path;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L25 _public member_ `TArray<FString> Elements;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L28 _public member_ `bool bExpandedByDefault;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L30 _public prototype_ `FString GetName() const;`
- L43 _public function_ `bool operator < (const FRigVMPinCategory& Other) const`
- L70 _public prototype_ `bool IsDefaultCategory() const;`
- L72 _public prototype_ `static const FString& GetDefaultCategoryName();`

#### struct `FRigVMNodeLayout`  
`struct FRigVMNodeLayout`  
_L76-135_
- reflection: `USTRUCT(BlueprintType)`
- L80 _public function_ `FRigVMNodeLayout() : Categories() , DisplayNames()`
- L86 _public member_ `TArray<FRigVMPinCategory> Categories;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L89 _public member_ `TMap<FString, int32> PinIndexInCategory;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L92 _public member_ `TMap<FString, FString> DisplayNames;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=FunctionArgument)`
- L94 _public function_ `void Reset()`
- L101 _public prototype_ `bool IsValid() const;`
- L121 _public function_ `bool operator ==(const FRigVMNodeLayout& OtherLayout) const`
- L126 _public function_ `bool operator !=(const FRigVMNodeLayout& OtherLayout) const`
- L133 _public prototype_ `const FString* FindCategory(const FString& InElement) const;`
- L134 _public prototype_ `const FString* FindDisplayName(const FString& InElement) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVM_API`
- L32 _function_ `friend uint32 GetTypeHash(const FRigVMPinCategory& Category)`
- L48 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMPinCategory& Category)`
- L103 _function_ `friend uint32 GetTypeHash(const FRigVMNodeLayout& Layout)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMObjectArchive.h` (Public)


#### struct `FRigVMObjectArchive`  
`struct FRigVMObjectArchive`  
_L11-59_
- reflection: `USTRUCT()`
- L16 _public function_ `FRigVMObjectArchive() : UncompressedSize(INDEX_NONE) , CompressedSize(INDEX_NONE) , bIsCompressed(false)`
- L23 _public prototype_ `void Reset();`
- L24 _public prototype_ `void Empty();`
- L25 _public prototype_ `bool IsEmpty() const;`
- L26 _public prototype_ `void Compress();`
- L27 _public prototype_ `bool Decompress();`
- L28 _public function_ `bool IsCompressed() const`
- L33 _public prototype_ `FString ToString();`
- L34 _public prototype_ `bool SetFromString(const FString& InString);`
- L38 _public prototype_ `void SetVersionsFromArchive(const FArchive& Ar);`
- L43 _private member_ `TMap<FGuid,int32> Versions;` — `UPROPERTY()`
- L46 _private member_ `TArray<uint8> Buffer;` — `UPROPERTY()`
- L49 _private member_ `int32 UncompressedSize;` — `UPROPERTY()`
- L52 _private member_ `int32 CompressedSize;` — `UPROPERTY()`
- L55 _private member_ `bool bIsCompressed;` — `UPROPERTY()`

#### class `FRigVMObjectArchiveWriter`  
`class FRigVMObjectArchiveWriter : public FArchiveUObject`  
_L61-89_
- inherits: `FArchiveUObject`
- L64 _public prototype_ `FRigVMObjectArchiveWriter( FRigVMObjectArchive& InOutArchive, const UObject* InRoot );`
- L66 _public prototype_ `virtual void Serialize( void* V, int64 Length ) override;`
- L67 _public prototype_ `virtual int64 Tell() override;`
- L68 _public prototype_ `virtual int64 TotalSize() override;`
- L69 _public prototype_ `virtual void Seek(int64 InPos) override;`
- L71 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override;`
- L72 _public prototype_ `virtual FArchive& operator<<(FName& Value) override;`
- L73 _public prototype_ `virtual FArchive& operator<<(FText& Value) override;`
- L77 _protected member_ `FRigVMObjectArchive& Archive;`
- L78 _protected member_ `int64 Offset;`
- L79 _protected member_ `const UObject* Root;`
- L80 _protected member_ `const FString RootPathName;`
- L81 _protected member_ `TSet<UObject*> VisitedObjects;`
- L82 _protected member_ `TMap<FName,int64> NameToOffset;`
- L84 _protected member_ `static inline constexpr uint8 StoringNullptr = 0;`
- L85 _protected member_ `static inline constexpr uint8 StoringFullObject = 1;`
- L86 _protected member_ `static inline constexpr uint8 StoringArchiveLocalPath = 2;`
- L87 _protected member_ `static inline constexpr uint8 StoringNameAsString = 0;`
- L88 _protected member_ `static inline constexpr uint8 StoringNameAsOffset = 1;`

#### class `FRigVMObjectArchiveReader`  
`class FRigVMObjectArchiveReader : public FRigVMObjectArchiveWriter`  
_L91-133_
- inherits: `FRigVMObjectArchiveWriter`
- L95 _public prototype_ `FRigVMObjectArchiveReader( FRigVMObjectArchive& InOutArchive, const UObject* InRoot );`
- L96 _public prototype_ `virtual void Serialize( void* V, int64 Length ) override;`
- L98 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override;`
- L99 _public prototype_ `virtual FArchive& operator<<(FName& Value) override;`
- L100 _public prototype_ `virtual FArchive& operator<<(FText& Value) override;`
- L122 _public prototype_ `FObjectHeader ReadObjectHeader(int64 InPosition = INDEX_NONE);`
- L123 _public prototype_ `FObjectHeader GetRootObjectHeader();`
- L127 _protected prototype_ `void ReadVersions();`
- L129 _protected member_ `TMap<FName, UClass*> ReadClasses;`
- L130 _protected member_ `TMap<FName, UObject*> ReadObjects;`
- L131 _protected member_ `TArray<UObject*> DeserializedObjects;`
- L132 _protected member_ `TMap<int64,FName> OffsetToName;`

#### struct `FRigVMObjectArchiveReader::FObjectHeader`  
`struct FObjectHeader`  
_L102-120_
- L104 _public function_ `FObjectHeader()`
- L111 _public function_ `bool IsValid() const`
- L116 _public member_ `UClass* Class;`
- L117 _public member_ `FName Name;`
- L118 _public member_ `EObjectFlags Flags;`
- L119 _public member_ `FName OuterPathName;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMProfilingInfo.h` (Public)


#### struct `FRigVMInstructionVisitInfo`  
`struct FRigVMInstructionVisitInfo`  
_L15-86_
- reflection: `USTRUCT()`
- L19 _public function_ `FRigVMInstructionVisitInfo()`
- L23 _public function_ `void Reset()`
- L32 _public function_ `inline void ResetInstructionVisitedDuringLastRun(int32 NewSize = 0)`
- L33 _public function_ `inline void SetNumInstructionVisitedDuringLastRunZeroed(int32 Num)`
- L34 _public function_ `inline void SetInstructionVisitedDuringLastRun(int32 InstructionIndex)`
- L41 _public function_ `inline int32 GetInstructionVisitedCountDuringLastRun(int32 InstructionIndex) const`
- L42 _public function_ `inline const TArray<int32>& GetInstructionVisitedCountDuringLastRun() const`
- L44 _public function_ `inline void ResetInstructionVisitOrder(int32 NewSize = 0)`
- L45 _public function_ `inline void AddInstructionIndexToVisitOrder(int32 InstructionIndex)`
- L46 _public function_ `inline const TArray<int32>& GetInstructionVisitOrder() const`
- L48 _public function_ `inline void ResetCallableVisitedDuringLastRun(int32 NewSize = 0)`
- L49 _public function_ `inline void SetNumCallableVisitedDuringLastRunZeroed(int32 Num)`
- L50 _public function_ `inline void SetCallableVisitedDuringLastRun(int32 CallableIndex)`
- L57 _public function_ `inline int32 GetCallableVisitedCountDuringLastRun(int32 CallableIndex) const`
- L58 _public function_ `inline const TArray<int32>& GetCallableVisitedCountDuringLastRun() const`
- L60 _public function_ `inline void ResetCallableVisitOrder(int32 NewSize = 0)`
- L61 _public function_ `inline void AddCallableIndexToVisitOrder(int32 CallableIndex)`
- L62 _public function_ `inline const TArray<int32>& GetCallableVisitOrder() const`
- L64 _public function_ `inline const void SetFirstEntryEventInEventQueue(const FName& InFirstEventName)`
- L65 _public function_ `inline const FName& GetFirstEntryEventInEventQueue() const`
- L67 _public prototype_ `void SetupInstructionTracking(int32 InInstructionCount, int32 InCallableCount);`
- L72 _private member_ `TArray<int32> InstructionVisitedDuringLastRun;` — stores the number of times each instruction was visited
- L73 _private member_ `TArray<int32> InstructionVisitOrder;`
- L76 _private member_ `TArray<int32> CallableVisitedDuringLastRun;` — stores the number of times each callable was visited
- L77 _private member_ `TArray<int32> CallableVisitOrder;`
- L81 _private member_ `FName FirstEntryEventInQueue = NAME_None;` — A RigVMHost can run multiple events per evaluation, such as the Backward&Forward Solve Mode, store the first event such that we know when to reset data for a new round of rig evaluation

#### struct `FFirstEntryEventGuard`  
`struct FFirstEntryEventGuard`  
_L88-105_
- L91 _public function_ `FFirstEntryEventGuard(FRigVMInstructionVisitInfo* InVisitInfo, const FName& InFirstEvent) : VisitInfo(InVisitInfo)`
- L98 _public function_ `~FFirstEntryEventGuard()`
- L103 _public member_ `FName OldEntry;`
- L104 _public member_ `FRigVMInstructionVisitInfo* VisitInfo;`

#### struct `FRigVMProfilingInfo`  
`struct FRigVMProfilingInfo`  
_L108-206_
- reflection: `USTRUCT()`
- L112 _public function_ `FRigVMProfilingInfo()`
- L116 _public function_ `void Reset()`
- L123 _public function_ `inline uint64 GetStartCycles() const`
- L124 _public function_ `inline void SetStartCycles(uint64 InStartCycles)`
- L126 _public function_ `inline uint64 GetOverallCycles() const`
- L127 _public function_ `inline void SetOverallCycles(uint64 Cycles)`
- L128 _public function_ `inline void AddOverallCycles(uint64 Cycles)`
- L130 _public function_ `inline void ResetInstructionCyclesDuringLastRun(int32 NewSize = 0)`
- L131 _public function_ `inline uint64 GetInstructionCyclesDuringLastRun(int32 InstructionIndex) const`
- L135 _public function_ `inline void SetInstructionCyclesDuringLastRun(int32 InstructionIndex, uint64 CyclesDuringLastRun)`
- L142 _public function_ `inline void AddInstructionCyclesDuringLastRun(int32 InstructionIndex, uint64 CyclesDuringLastRun)`
- L149 _public function_ `inline void InitInstructionCyclesDuringLastRunValues(int32 NewSize, uint64 DefaultValue)`
- L158 _public function_ `inline void ResetCallableCyclesDuringLastRun(int32 NewSize = 0)`
- L159 _public function_ `inline uint64 GetCallableCyclesDuringLastRun(int32 CallableIndex) const`
- L163 _public function_ `inline void SetCallableCyclesDuringLastRun(int32 CallableIndex, uint64 CyclesDuringLastRun)`
- L170 _public function_ `inline void AddCallableCyclesDuringLastRun(int32 CallableIndex, uint64 CyclesDuringLastRun)`
- L177 _public function_ `inline void InitCallableCyclesDuringLastRunValues(int32 NewSize, uint64 DefaultValue)`
- L186 _public prototype_ `void SetupInstructionTracking(int32 InInstructionCount, int32 InCallableCount, bool bEnableProfiling);`
- L188 _public function_ `double GetLastExecutionMicroSeconds() const`
- L189 _public function_ `void SetLastExecutionMicroSeconds(double InLastExecutionMicroSeconds)`
- L191 _public prototype_ `void StartProfiling(bool bEnableProfiling);`
- L192 _public prototype_ `void StopProfiling();`
- L197 _private member_ `TArray<uint64> InstructionCyclesDuringLastRun;` — stores the cycles for each instruction
- L198 _private member_ `TArray<uint64> CallableCyclesDuringLastRun;`
- L200 _private member_ `uint64 StartCycles = 0;`
- L201 _private member_ `uint64 OverallCycles = 0;`
- L203 _private member_ `double LastExecutionMicroSeconds = 0.0;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMPropertyBag.h` (Public)


#### struct `FRigVMPropertyDescription`  
`struct FRigVMPropertyDescription`  
_L26-107_
- desc: The property description is used to provide all required information to create a property for the memory storage class.
- L29 _public member_ `static const FName MD_DisplayName;` — Metadata string that sets the display name
- L34 _public member_ `FGuid Guid;` — The guid of the property to create
- L37 _public member_ `FName Name;` — The name of the property to create
- L40 _public member_ `const FProperty* Property;` — The property to base a new property off of
- L44 _public member_ `EPropertyFlags PropertyFlags;` — The property flags that should be set. These will be used in the PropertyBag hash Changing a flag in the PropertyBag will change it for all the instances that share the same PropertyBag hash
- L47 _public member_ `FString CPPType;` — The complete CPP type to base a new property off of (for ex: 'TArray<TArray<FVector>>')
- L50 _public member_ `UObject* CPPTypeObject;` — The tail CPP Type object, for example the UScriptStruct for a struct
- L53 _public member_ `TArray<EPinContainerType> Containers;` — A list of containers to use for this property, for example [Array, Array]
- L56 _public member_ `FString DefaultValue;` — The default value to use for this property (for example: '(((X=1.000000, Y=2.000000, Z=3.000000)))')
- L60 _public member_ `TMap<FName, FString> MetaData;` — All the metadata on the PropertyBag. This will be used in the PropertyBag hash.
- L64 _public function_ `FRigVMPropertyDescription() : Name(NAME_None) , Property(nullptr) , CPPType() , CPPTypeObject(nullptr) , Containers() , DefaultValue()` — Default constructor
- L74 _public prototype_ `FRigVMPropertyDescription(const FProperty* InProperty, const FString& InDefaultValue, const FName& InName = NAME_None, const bool bAllowSpacesInName = false);` — Constructor from an existing property
- L77 _public prototype_ `FRigVMPropertyDescription(const FName& InName, const FString& InCPPType, UObject* InCPPTypeObject, const FString& InDefaultValue, const bool bAllowSpacesInName = false);` — Constructor from complete data
- L81 _public prototype_ `FRigVMPropertyDescription(const FName& InName, const FString& InCPPType, UObject* InCPPTypeObject, const FString& InDefaultValue, const EPropertyFlags InPropertyFlags, const TMap<FName, FString>& InMetaData, const bool bAllowSpacesInName = false);` — Constructor from complete data
- L84 _public prototype_ `FRigVMPropertyDescription(const FName& InName, const FString& InCPPType, UObject* InCPPTypeObject, const FString& InDefaultValue, const EPropertyFlags InPropertyFlags, const bool bAllowSpacesInName = false);` — Constructor from complete data
- L88 _public prototype_ `static FName SanitizeName(const FName& InName, const bool bAllowSpaces = false);` — Returns a sanitized, valid name to use for a new property
- L91 _public prototype_ `static void SanitizeName(FString& InString, const bool bAllowSpaces = false);` — Sanitizes a name using a string ref, creating a valid name to use for a new property
- L94 _public prototype_ `void SanitizeName(const bool bAllowSpaces = false);` — Sanitize the name of this description in line
- L97 _public function_ `bool IsValid() const` — Returns true if this property description is valid
- L100 _public prototype_ `FString GetTailCPPType() const;` — Returns the CPP type of the tail property, for ex: '[2].Translation' it is 'FVector'
- L104 _private member_ `static const inline TCHAR* ArrayPrefix = TEXT("TAr`
- L105 _private member_ `static const inline TCHAR* MapPrefix = TEXT("TMa`
- L106 _private member_ `static const inline TCHAR* ContainerSuffix = TEXT(">")`

#### struct `FRigVMPropertyBag`  
`struct FRigVMPropertyBag : public FInstancedPropertyBag`  
_L110-374_
- reflection: `USTRUCT()`
- inherits: `FInstancedPropertyBag`
- L114 _public prototype_ `FRigVMPropertyBag();`
- L116 _public prototype_ `bool Serialize(FArchive& Ar);`
- L117 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector);`
- L118 _public prototype_ `void GetUserDefinedDependencies(TArray<const UObject*>& OutDependencies) const;`
- L119 _public prototype_ `void GetRequiredPlugins(TArray<FString>& OutPlugins) const;`
- L127 _public function_ `static bool IsClassOf(const FRigVMPropertyBag* InElement)`
- L139 _public prototype_ `void AddProperties(const TArray<FRigVMPropertyDescription>& InPropertyDescriptions);` — Adds properties to the storage. If property of same name already exists, it will be replaced with the new type. Numeric property values will be converted if possible, when a property's type changes. @param InPropertyDescriptions : Descriptors of new properties to add.
- L146 _public prototype_ `EPropertyBagAlterationResult RemovePropertyByName(const FName& InPropertyName);` — Remove property from the storage. @param InPropertyName : The name of the property to remove @return Success if the property was successfully removed
- L150 _public function_ `int32 Num() const` — Returns the number of properties stored in this instance
- L157 _public function_ `bool IsValidIndex(int32 InIndex) const` — Returns true if a provided property index is valid
- L165 _public function_ `const TArray<const FProperty*>& GetProperties() const` — Returns the properties provided by this instance
- L171 _public prototype_ `int32 GetPropertyIndex(const FProperty* InProperty) const;` — Returns the index of a property given the property itself
- L174 _public prototype_ `int32 GetPropertyIndexByName(const FName& InName) const;` — Returns the index of a property given its name
- L177 _public function_ `const FProperty* GetProperty(int32 InPropertyIndex) const` — Returns a property given its index
- L184 _public prototype_ `FProperty* FindPropertyByName(const FName& InName) const;` — Returns a property given its name (or nullptr if the name wasn't found)
- L187 _public prototype_ `void* GetContainerPtr() const;` — Returns the raw memory storage pointer
- L190 _public function_ `bool IsArray(int32 InPropertyIndex) const` — Returns true if the property at a given index is a TArray
- L196 _public function_ `bool IsMap(int32 InPropertyIndex) const` — Returns true if the property at a given index is a TMap
- L205 _public function_ `template<typename T> T* GetData(int32 InPropertyIndex)` — Returns the memory for a property given its index
- L212 _public function_ `template<typename T> const T* GetData(int32 InPropertyIndex) const`
- L221 _public function_ `template<typename T> T* GetDataByName(const FName& InName)` — Returns the memory for a property given its name (or nullptr)
- L233 _public function_ `template<typename T> T* GetData(const FProperty* Property)` — Returns the mutable memory for a given property (or nullptr if does not belong to this storage)
- L243 _public function_ `template<typename T> const T* GetData(const FProperty* Property) const`
- L255 _public function_ `template<typename T> T* GetData(int32 InPropertyIndex, const FRigVMPropertyPath& InPropertyPath)` — Returns the memory for a property given its index and a matching property path
- L263 _public function_ `template<typename T> T* GetDataByName(const FName& InName, const FRigVMPropertyPath& InPropertyPath)` — Returns the memory for a property given its name and a matching property path (or nullptr)
- L275 _public function_ `template<typename T> T& GetRef(int32 InPropertyIndex)` — Returns the ref of an element stored at a given property index
- L282 _public function_ `template<typename T> T& GetRefByName(const FName& InName)` — Returns the ref of an element stored at a given property name (throws if name is invalid)
- L289 _public function_ `template<typename T> T& GetRef(int32 InPropertyIndex, const FRigVMPropertyPath& InPropertyPath)` — Returns the ref of an element stored at a given property index and a property path
- L296 _public function_ `template<typename T> T& GetRefByName(const FName& InName, const FRigVMPropertyPath& InPropertyPath)` — Returns the ref of an element stored at a given property name and a property path (throws if name is invalid)
- L304 _public prototype_ `FString GetDataAsString(int32 InPropertyIndex, int32 PortFlags = PPF_None) const;` — Returns the exported text for a given property index
- L307 _public function_ `FString GetDataAsStringByName(const FName& InName, int32 PortFlags = PPF_None) const` — Returns the exported text for given property name
- L314 _public prototype_ `FString GetDataAsStringSafe(int32 InPropertyIndex, int32 PortFlags = PPF_None) const;` — Returns the exported text for a given property index
- L317 _public function_ `FString GetDataAsStringByNameSafe(const FName& InName, int32 PortFlags = PPF_None) const` — Returns the exported text for given property name
- L324 _public prototype_ `bool SetDataFromString(int32 InPropertyIndex, const FString& InValue);` — Sets the content of a property by index given an exported string. Returns true if succeeded
- L327 _public function_ `bool SetDataFromStringByName(const FName& InName, const FString& InValue)` — Sets the content of a property by name given an exported string. Returns true if succeeded
- L334 _public prototype_ `void Refresh();`
- L344 _public prototype_ `static bool CopyProperty( const FProperty* InTargetProperty, uint8* InTargetPtr, const FProperty* InSourceProperty, const uint8* InSourcePtr);` — Copies the content of a source property and memory into the memory of a target property @param InTargetProperty The target property to copy into @param InTargetPtr The memory of the target value to copy into @param InSourceProperty The source property to copy from @param InSourcePtr The memory of the source value to copy from @return true if the copy operations was successful
- L352 _public prototype_ `static FPropertyBagPropertyDesc GeneratePropertyBagDescriptor(const FRigVMPropertyDescription& RigVMDescriptor, bool bComputeId = true);` — Helper function to generate a property bag desc from a FRigVMPropertyDescription
- L357 _protected member_ `TArray<const FProperty*> LinkedProperties;` — A cached list of all linked properties (created by RefreshLinkedProperties)
- L360 _protected member_ `mutable int32 CachedMemoryHash = 0;`
- L362 _protected member_ `static const TArray<const FProperty*> EmptyProperties;`
- L364 _protected prototype_ `void ForEachObjectDependency(const TFunction<void(const UObject*)>& InCallBack) const;`
- L366 _protected prototype_ `void RefreshLinkedProperties();`
- L368 _protected prototype_ `void SetDefaultValues(const TArray<FRigVMPropertyDescription>& InPropertyDescriptions);`
- L371 _protected prototype_ `void SetDefaultValuesOnTailProperties(const TArray<FRigVMPropertyDescription>& InPropertyDescriptions);` — Set default values on the last properties added
- L373 _protected prototype_ `static bool GetPropertyTypeDataFromVMDescriptor(const FRigVMPropertyDescription& RigVMDescriptor, EPropertyBagPropertyType& OutBagPropertyType, FPropertyBagContainerTypes& OutBagContainerTypes);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRigVMPropertyBag> : public TStructOpsTypeTraitsBase2<FRigVMPropertyBag>`  
_L376-383_
- inherits: `TStructOpsTypeTraitsBase2<FRigVMPropertyBag>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L379-382_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVM_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RigVM` (scope `UE`)
- L12 _namespace_ `namespace RigVMCore` (scope `UE::RigVM`)
- L12 _namespace_ `namespace Private` (scope `UE::RigVM::RigVMCore`)
- L14 _variable_ `inline constexpr TCHAR BraceFormat[] = TEXT("(%s` (scope `UE::RigVM::RigVMCore::Private`)
- L15 _variable_ `inline const FString EmptyBraces = TEXT("()"` (scope `UE::RigVM::RigVMCore::Private`)
- L121 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMPropertyBag& P)`
- L380 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon7cdd4b570103`)
- L381 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon7cdd4b570103`)

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMPropertyPath.h` (Public)


#### struct `FRigVMPropertyPathDescription`  
`struct FRigVMPropertyPathDescription`  
_L26-64_
- desc: The RigVMPropertyPathDescription is used to provide all of the information necessary to describe a property path for creating it. This is used by the RigVMCompiler, which collects all descriptions first and then passes them onto the RigVMStorageGeneratorClass for construction. Furthermore the RigVMPropertyPathDescription is used to serialize property paths and recreate them on load.
- L29 _public member_ `int32 PropertyIndex;` — The index of the property this property path belongs to.
- L33 _public member_ `FString HeadCPPType;` — The CPP type of the head property. For Transform.Translation.X the HeadCPPType is 'FTransform'
- L37 _public member_ `FString SegmentPath;` — The segment path of the properties below the head property. For Transform.Translation.X the SegmentPath is 'Translation.X'
- L40 _public function_ `FRigVMPropertyPathDescription() : PropertyIndex(INDEX_NONE) , HeadCPPType() , SegmentPath()` — Default constructor
- L47 _public function_ `FRigVMPropertyPathDescription(int32 InPropertyIndex, const FString& InHeadCPPType, const FString& InSegmentPath) : PropertyIndex(InPropertyIndex) , HeadCPPType(InHeadCPPType) , SegmentPath(InSegmentPath)` — Constructor from complete data
- L54 _public function_ `bool IsValid() const` — returns true if this property path is valid

#### enum `ERigVMPropertyPathSegmentType`  
`enum ERigVMPropertyPathSegmentType`  
_L70-75_
- desc: The RigVMPropertyPathSegmentType is used to differentiate segments under a property path.
- L72 _public enumerator_ `StructMember` — The segment represents a member of a struct
- L73 _public enumerator_ `ArrayElement` — The segment represents an element of an array
- L74 _public enumerator_ `MapValue` — The segments represents a value within a map. Typically maps supported use FName as the key.

#### struct `FRigVMPropertyPathSegment`  
`struct FRigVMPropertyPathSegment`  
_L81-94_
- desc: The RigVMPropertyPathSegment represents a single step needed to go from the head property of a property path to the tail.
- L84 _public member_ `ERigVMPropertyPathSegmentType Type;` — The type of segment / step.
- L87 _public member_ `FName Name;` — The name of the segment - can be the name of the struct member of key for a map element.
- L90 _public member_ `int32 Index;` — The index of the segment - used to represent the array index for array elements.
- L93 _public member_ `const FProperty* Property;` — The property for this segment - on the chain towards the tail property.

#### class `FRigVMPropertyPath`  
`class FRigVMPropertyPath`  
_L104-203_
- desc: The RigVMPropertyPath is used to access a memory pointer for a tail property given the memory of the head property. A property path allows to traverse struct members, array elements and map values. For example given an array of transforms the property path '[2].Translation.X' is represented as three segments (1 array element and 2 struct members).
- L109 _public prototype_ `FRigVMPropertyPath();` — Default constructor
- L116 _public prototype_ `FRigVMPropertyPath(const FProperty* InProperty, const FString& InSegmentPath);` — Constructor from complete data @param InProperty The head property to base this property path off of @param InSegmentPath A . separated string providing all of the segments of this path
- L119 _public function_ `const FString& ToString() const` — Returns the property path as a string (the sanitized SegmentPath)
- L122 _public prototype_ `FString GetName() const;` — Returns a descriptive name
- L125 _public function_ `int32 Num() const` — Returns the number of segments
- L128 _public function_ `bool IsValid() const` — Returns true if the property path is valid (has any segments)
- L131 _public function_ `bool IsEmpty() const` — Returns true if the property is empty (no segments)
- L134 _public function_ `const FRigVMPropertyPathSegment& operator[](int32 InIndex) const` — Index based access operator for a segment
- L137 _public function_ `const TArray<FRigVMPropertyPathSegment>& GetSegments() const` — Returns the segments of this property path
- L139 _public function_ `bool operator ==(const FRigVMPropertyPath& Other) const`
- L144 _public function_ `bool operator !=(const FRigVMPropertyPath& Other) const`
- L149 _public function_ `bool operator >(const FRigVMPropertyPath& Other) const`
- L154 _public function_ `bool operator <(const FRigVMPropertyPath& Other) const`
- L165 _public function_ `template<typename T> T* GetData(uint8* InPtr, const FProperty* InProperty) const` — Accessor for traversing the path and returning the memory of the tail @param InPtr The memory of the head property @param InProperty The head property to traverse off of
- L185 _public prototype_ `FString GetHeadCPPType() const;` — Return the owner's native type. the owner can be a property or a struct.
- L188 _public prototype_ `const FProperty* GetTailProperty() const;` — Returns the property of the last segment
- L191 _public member_ `static FRigVMPropertyPath Empty;` — Static empty property path (used for comparisons)
- L196 _private prototype_ `uint8* GetData_Internal(uint8* InPtr, const FProperty* InProperty) const;` — Internal traversal method
- L199 _private member_ `FString Path;` — Stored string representation of the segment path
- L202 _private member_ `TArray<FRigVMPropertyPathSegment> Segments;` — Resolved segments of the property path

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVM_API`
- L57 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMPropertyPathDescription& Path)` — Archive operator for serialization
- L171 _function_ `friend uint32 GetTypeHash(const FRigVMPropertyPath& InPropertyPath)` — Returns a unique hash for the property path

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMRegistry.h` (Public)


#### struct `FRigVMRegistry_NoLock`  
`struct FRigVMRegistry_NoLock : public FGCObject, public TSharedFromThis<FRigVMRegistry_NoLock>`  
_L46-515_
- inherits: `FGCObject,TSharedFromThis<FRigVMRegistry_NoLock>`
- desc: The FRigVMRegistry is used to manage all known function pointers for use in the RigVM. The Register method is called automatically when the static struct is initially constructed for each USTRUCT hosting a RIGVM_METHOD enabled virtual function. Inheriting from FGCObject to ensure that all type objects cannot be GCed
- L58 _public function_ `bool IsGlobalRegistry() const` — returns true for the singleton global registry
- L61 _public prototype_ `const FRigVMRegistryHandle& GetHandle_NoLock() const;` — returns the handle referring to this hierarchy
- L62 _public prototype_ `FRigVMRegistryHandle& GetHandle_NoLock();`
- L65 _public prototype_ `static TSharedRef<FRigVMRegistry_NoLock> CreateLocalizedRegistry();` — Constructor for a localized, independent registry
- L68 _public prototype_ `static TSharedRef<FRigVMRegistry_NoLock> CloneLocalizedRegistry(FRigVMRegistry_NoLock* InRegistry);` — Constructor for a localized, independent registry based on an existing registry
- L70 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRigVMRegistryChanged);`
- L75 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject overrides
- L76 _public prototype_ `virtual FString GetReferencerName() const override;`
- L81 _public prototype_ `virtual void Register_NoLock(const TCHAR* InName, FRigVMFunctionPtr InFunctionPtr, UScriptStruct* InStruct = nullptr, const TArray<FRigVMFunctionArgument>& InArguments = TArray<FRigVMFunctionArgument>());` — Registers a function given its name. The name will be the name of the struct and virtual method, for example "FMyStruct::MyVirtualMethod"
- L84 _public prototype_ `virtual void RegisterCompiledInStruct_NoLock(UScriptStruct* InStruct, TConstArrayView<FRigVMCompiledInFunction> InFunctions);` — Register many functions, as if calling Register_NoLock in a loop
- L87 _public prototype_ `virtual bool RemoveFunction_NoLock(int32 InFunctionIndex);` — This keeps the function index stable - but assigns an invalid function
- L90 _public prototype_ `virtual const FRigVMDispatchFactory* RegisterFactory_NoLock(UScriptStruct* InFactoryStruct, const TArray<FRigVMTemplateArgumentInfo>& InArgumentInfos = {});` — Registers a dispatch factory given its struct.
- L94 _public prototype_ `virtual bool RemoveFactory_NoLock(UScriptStruct* InFactoryStruct);` — Unregisters a factory given its script struct. This keeps the template index stable
- L98 _public prototype_ `virtual bool RemoveTemplate_NoLock(int32 InTemplateIndex);` — Unregisters a template given its index. This keeps the template index stable - but assigns an invalid template
- L101 _public prototype_ `virtual void RegisterPredicate_NoLock(UScriptStruct* InStruct, const TCHAR* InName, const TArray<FRigVMFunctionArgument>& InArguments);` — Register a predicate contained in the input struct
- L114 _public prototype_ `virtual void RegisterObjectTypes_NoLock(TConstArrayView<TPair<UClass*, ERegisterObjectOperation>> InClasses);` — Register a set of allowed object types
- L117 _public prototype_ `virtual void RegisterStructTypes_NoLock(TConstArrayView<UScriptStruct*> InStructs);` — Register a set of allowed struct types
- L121 _public prototype_ `virtual void RefreshEngineTypes_NoLock();` — Refreshes the list and finds the function pointers based on the names.
- L124 _public prototype_ `virtual bool RefreshFunctionsAndDispatches_NoLock();` — Refreshes the registered functions and dispatches.
- L128 _public prototype_ `virtual void RefreshEngineTypesIfRequired_NoLock();` — Refreshes the list and finds the function pointers based on the names.
- L131 _public prototype_ `virtual bool OnCleanupUnloadingObjects_NoLock(const TArrayView<UObject*> InObjects);` — Update the registry when old types are being unloaded
- L134 _public prototype_ `virtual void OnAssetRenamed_NoLock(const FAssetData& InAssetData, const FString& InOldObjectPath);` — Update the registry when types are renamed
- L137 _public prototype_ `virtual bool OnAssetRemoved_NoLock(const FAssetData& InAssetData);` — Update the registry when old types are removed
- L140 _public prototype_ `static TArray<FString> GetPluginModulePrefixes(const IPlugin& InPlugin);` — Returns the prefixes for all modules within a plugin
- L143 _public prototype_ `static bool IsWithinPlugin(const IPlugin& InPlugin, const UObject* InObject);` — Returns true if a given object is part of a plugin
- L146 _public prototype_ `static bool IsWithinPlugin(const TArray<FString>& InModulePrefixes, const UObject* InObject);` — Returns true if a given object is part of a plugin object path
- L149 _public prototype_ `virtual bool OnPluginLoaded_NoLock(IPlugin& InPlugin);` — May add factories and unit functions declared in the plugin
- L152 _public prototype_ `virtual bool OnPluginUnloaded_NoLock(IPlugin& InPlugin);` — Removes all types associated with a plugin that's being unloaded.
- L155 _public prototype_ `virtual bool OnModulesUnloaded_NoLock(TConstArrayView<FName> ModuleNames);` — Removes all types associated with modules that are being unloaded.
- L159 _public prototype_ `virtual void OnAnimationAttributeTypesChanged_NoLock(const UScriptStruct* InStruct, bool bIsAdded);` — Update the registry when new types are added to the attribute system so that they can be selected on Attribute Nodes
- L162 _public prototype_ `virtual void Reset_NoLock();` — Clear the registry
- L165 _public prototype_ `void Serialize_NoLock(FArchive& Ar, const UObject* Owner = nullptr);` — Serializes the registry to an archive. This throws for the global registry.
- L169 _public prototype_ `virtual TRigVMTypeIndex FindOrAddType_NoLock(const FRigVMTemplateArgumentType& InType, bool bForce = false);` — Adds a type if it doesn't exist yet and returns its index. This function is thread-safe
- L173 _public prototype_ `virtual bool RemoveType_NoLock(const FSoftObjectPath& InObjectPath);` — Removes a type from the registry, and updates all dependent templates which also creates invalid permutations in templates that we should ignore
- L177 _public prototype_ `virtual bool RemoveType_NoLock(TRigVMTypeIndex InTypeIndex);` — Removes a type from the registry, and updates all dependent templates which also creates invalid permutations in templates that we should ignore
- L180 _public prototype_ `virtual TRigVMTypeIndex GetTypeIndex_NoLock(const FRigVMTemplateArgumentType& InType) const;` — Returns the type index given a type
- L183 _public function_ `virtual TRigVMTypeIndex GetTypeIndex_NoLock(const FName& InCPPType, UObject* InCPPTypeObject) const` — Returns the type index given a cpp type and a type object
- L193 _public function_ `TRigVMTypeIndex GetTypeIndex_NoLock(bool bAsArray = false) const`
- L249 _public prototype_ `virtual const FRigVMTemplateArgumentType& GetType_NoLock(TRigVMTypeIndex InTypeIndex) const;` — Returns the type given its index
- L252 _public function_ `virtual int32 NumTypes_NoLock() const` — Returns the number of types
- L255 _public prototype_ `virtual const FRigVMTemplateArgumentType& FindTypeFromCPPType_NoLock(const FString& InCPPType) const;` — Returns the type given only its cpp type
- L258 _public prototype_ `virtual TRigVMTypeIndex GetTypeIndexFromCPPType_NoLock(const FString& InCPPType) const;` — Returns the type index given only its cpp type
- L261 _public prototype_ `virtual bool IsArrayType_NoLock(TRigVMTypeIndex InTypeIndex) const;` — Returns true if the type is an array
- L264 _public prototype_ `virtual bool IsExecuteType_NoLock(TRigVMTypeIndex InTypeIndex) const;` — Returns true if the type is an execute type
- L267 _public prototype_ `virtual bool ConvertExecuteContextToBaseType_NoLock(TRigVMTypeIndex& InOutTypeIndex) const;` — Converts the given execute context type to the base execute context type
- L270 _public prototype_ `virtual int32 GetArrayDimensionsForType_NoLock(TRigVMTypeIndex InTypeIndex) const;` — Returns the dimensions of the array
- L273 _public prototype_ `virtual bool IsWildCardType_NoLock(TRigVMTypeIndex InTypeIndex) const;` — Returns true if the type is a wildcard type
- L276 _public prototype_ `virtual bool CanMatchTypes_NoLock(TRigVMTypeIndex InTypeIndexA, TRigVMTypeIndex InTypeIndexB, bool bAllowFloatingPointCasts) const;` — Returns true if the types can be matched.
- L279 _public prototype_ `virtual const TArray<TRigVMTypeIndex>& GetCompatibleTypes_NoLock(TRigVMTypeIndex InTypeIndex) const;` — Returns the list of compatible types for a given type
- L282 _public prototype_ `virtual const TArray<TRigVMTypeIndex>& GetTypesForCategory_NoLock(FRigVMTemplateArgument::ETypeCategory InCategory) const;` — Returns all compatible types given a category
- L285 _public prototype_ `virtual TRigVMTypeIndex GetArrayTypeFromBaseTypeIndex_NoLock(TRigVMTypeIndex InTypeIndex) const;` — Returns the type index of the array matching the given element type index
- L288 _public prototype_ `virtual TRigVMTypeIndex GetBaseTypeFromArrayTypeIndex_NoLock(TRigVMTypeIndex InTypeIndex) const;` — Returns the type index of the element matching the given array type index
- L291 _public prototype_ `virtual bool IsSpecificallyAllowedType_NoLock(const UObject* InObject) const;` — Returns true if the given type is specifically allowed
- L294 _public prototype_ `virtual void AddSpecificallyAllowedType_NoLock(const UObject* InObject);` — Sets a given type as specifically allowed
- L297 _public prototype_ `virtual const FRigVMFunction* FindFunction_NoLock(const TCHAR* InName, const FRigVMUserDefinedTypeResolver& InTypeResolver = FRigVMUserDefinedTypeResolver()) const;` — Returns the function given its name (or nullptr)
- L300 _public prototype_ `virtual const FRigVMFunction* FindFunction_NoLock(UScriptStruct* InStruct, const TCHAR* InName, const FRigVMUserDefinedTypeResolver& InResolvalInfo = FRigVMUserDefinedTypeResolver()) const;` — Returns the function given its backing up struct and method name
- L303 _public prototype_ `virtual const TChunkedArray<FRigVMFunction>& GetFunctions_NoLock() const;` — Returns all current RigVM functions
- L306 _public prototype_ `virtual const FRigVMTemplate* FindTemplate_NoLock(const FName& InNotation, bool bIncludeDeprecated = false, bool bRemapToCoreDispatch = true) const;` — Returns a template pointer given its notation (or nullptr)
- L309 _public prototype_ `virtual const TChunkedArray<FRigVMTemplate>& GetTemplates_NoLock() const;` — Returns all current RigVM functions
- L312 _public prototype_ `virtual const FRigVMTemplate* GetOrAddTemplateFromArguments_NoLock( const FName& InName, const TArray<FRigVMTemplateArgumentInfo>& InInfos, const FRigVMTemplateDelegates& InDelegates);` — Defines and retrieves a template given its arguments
- L318 _public prototype_ `virtual const FRigVMTemplate* AddTemplateFromArguments_NoLock( const FName& InName, const TArray<FRigVMTemplateArgumentInfo>& InInfos, const FRigVMTemplateDelegates& InDelegates);` — Adds a new template given its arguments
- L324 _public prototype_ `virtual FRigVMDispatchFactory* FindDispatchFactory_NoLock(const FName& InFactoryName) const;` — Returns a dispatch factory given its name (or nullptr)
- L327 _public prototype_ `virtual FRigVMDispatchFactory* FindOrAddDispatchFactory_NoLock(UScriptStruct* InFactoryStruct);` — Returns a dispatch factory given its static struct (or nullptr)
- L334 _public function_ `FRigVMDispatchFactory* FindOrAddDispatchFactory_NoLock()`
- L340 _public prototype_ `virtual FString FindOrAddSingletonDispatchFunction_NoLock(UScriptStruct* InFactoryStruct);` — Returns a dispatch factory's singleton function name if that exists
- L347 _public function_ `FString FindOrAddSingletonDispatchFunction_NoLock()`
- L353 _public prototype_ `virtual const TArray<FRigVMDispatchFactory*>& GetFactories_NoLock() const;` — Returns all dispatch factories
- L356 _public prototype_ `virtual const TArray<FRigVMFunction>* GetPredicatesForStruct_NoLock(const FName& InStructName) const;` — Given a struct name, return the predicates
- L358 _public prototype_ `static const TArray<UScriptStruct*>& GetMathTypes();`
- L362 _public prototype_ `virtual uint32 GetHashForType_NoLock(TRigVMTypeIndex InTypeIndex) const;` — Returns a unique hash per type index
- L363 _public prototype_ `virtual uint32 GetHashForScriptStruct_NoLock(const UScriptStruct* InScriptStruct, bool bCheckTypeIndex = true) const;`
- L364 _public prototype_ `virtual uint32 GetHashForStruct_NoLock(const UStruct* InStruct) const;`
- L365 _public prototype_ `virtual uint32 GetHashForEnum_NoLock(const UEnum* InEnum, bool bCheckTypeIndex = true) const;`
- L366 _public prototype_ `virtual uint32 GetHashForProperty_NoLock(const FProperty* InProperty) const;`
- L368 _public prototype_ `virtual void RebuildRegistry_NoLock();`
- L370 _public member_ `static inline const FLazyName TemplateNameMetaName = FLazyName(TEXT("Temp`
- L372 _public prototype_ `static void OnEngineInit();`
- L377 _protected prototype_ `FRigVMRegistry_NoLock(bool InIsGlobalRegistry);`
- L380 _protected prototype_ `FRigVMRegistry_NoLock(const FRigVMRegistry_NoLock&);` — disable copy constructor
- L382 _protected prototype_ `FRigVMRegistry_NoLock& operator= (const FRigVMRegistry_NoLock &InOther) = delete;` — disable assignment operator
- L411 _protected prototype_ `void InitializeBaseTypes_NoLock();` — Initialize the base types
- L413 _protected function_ `static EObjectFlags DisallowedFlags()`
- L418 _protected function_ `static EObjectFlags NeededFlags()`
- L423 _protected prototype_ `bool OnModulesUnloadedInternal(const TArray<FString>& ModulePrefixes);`
- L425 _protected prototype_ `bool IsAllowedType_NoLock(const FProperty* InProperty) const;`
- L426 _protected prototype_ `bool IsAllowedType_NoLock(const UEnum* InEnum) const;`
- L427 _protected prototype_ `bool IsAllowedType_NoLock(const UStruct* InStruct) const;`
- L428 _protected prototype_ `bool IsAllowedType_NoLock(const UClass* InClass) const;`
- L429 _protected prototype_ `static bool IsTypeOfByName(const UObject* InObject, const FName& InName);`
- L431 _protected prototype_ `void RegisterTypeInCategory_NoLock(const FRigVMTemplateArgument::ETypeCategory InCategory, const TRigVMTypeIndex InTypeIndex);`
- L432 _protected prototype_ `void PropagateTypeAddedToCategory_NoLock(const FRigVMTemplateArgument::ETypeCategory InCategory, const TRigVMTypeIndex InTypeIndex);`
- L433 _protected prototype_ `void RemoveTypeInCategory_NoLock(FRigVMTemplateArgument::ETypeCategory InCategory, TRigVMTypeIndex InTypeIndex);`
- L436 _protected member_ `mutable FRigVMRegistryHandle ThisHandle;` — the handle storing this registry
- L439 _protected member_ `bool bIsGlobalRegistry;` — true if this registry is the globally shared registry
- L442 _protected member_ `TArray<FTypeInfo> Types;` — memory for all (known) types
- L443 _protected member_ `TMap<FRigVMTemplateArgumentType, TRigVMTypeIndex> TypeToIndex;`
- L447 _protected member_ `TChunkedArray<FRigVMFunction> Functions;` — memory for all functions We use TChunkedArray because we need the memory locations to be stable, since we only ever add and never remove.
- L450 _protected member_ `TChunkedArray<FRigVMTemplate> Templates;` — memory for all non-deprecated templates
- L453 _protected member_ `TChunkedArray<FRigVMTemplate> DeprecatedTemplates;` — memory for all deprecated templates
- L456 _protected member_ `TArray<FRigVMDispatchFactory*> Factories;` — memory for all dispatch factories
- L459 _protected member_ `TMap<FName, FRigVMDispatchFactory*> FactoryNameToFactory;` — name lookup for factories
- L462 _protected member_ `TMap<const UScriptStruct*, FRigVMDispatchFactory*> FactoryStructToFactory;` — struct lookup for factories
- L465 _protected member_ `TMap<FName, int32> FunctionNameToIndex;` — name lookup for functions
- L468 _protected member_ `TMap<FName, int32> PreviousFunctionNameToIndex;` — Previous value for name lookups - this can happen to functions which get deregistered
- L471 _protected member_ `TMap<FName, TArray<FRigVMFunction>> StructNameToPredicates;` — lookup all the predicate functions of this struct
- L474 _protected member_ `TMap<FName, int32> TemplateNotationToIndex;` — name lookup for non-deprecated templates
- L477 _protected member_ `TMap<FName, int32> PreviousTemplateNotationToIndex;` — previous name lookup for templates which got removed
- L480 _protected member_ `TMap<FName, int32> DeprecatedTemplateNotationToIndex;` — name lookup for deprecated templates
- L483 _protected member_ `TMap<FRigVMTemplateArgument::ETypeCategory, TArray<TRigVMTypeIndex>> TypesPerCategory;` — Maps storing the default types per type category
- L486 _protected member_ `TMap<FRigVMTemplateArgument::ETypeCategory, TArray<int32>> TemplatesPerCategory;` — Lookup per type category to know which template to keep in sync
- L489 _protected typedef_ `using TRigVMTypeIndexTriple = TTuple<TRigVMTypeIndex, TRigVMTypeIndex, TRigVMTypeIndex>;` — This type index triple represents the single value, array value, and 2d array value type indices.
- L493 _protected member_ `TMap<FSoftObjectPath, TRigVMTypeIndexTriple> SoftObjectPathToTypeIndex;` — Name lookup for types since they can be deleted. When that happens, it won't be safe to reload deleted assets so only type names are reliable
- L496 _protected member_ `TSet<TObjectPtr<const UClass>> AllowedClasses;` — All allowed classes
- L499 _protected member_ `TSet<TObjectPtr<const UScriptStruct>> AllowedStructs;` — All allowed structs
- L503 _protected member_ `bool bAvoidTypePropagation;` — If this is true the registry is currently refreshing all types and we want to avoid propagating types to the templates
- L506 _protected member_ `bool bEverRefreshedEngineTypes;` — This is true if the engine has ever refreshed the engine types
- L509 _protected member_ `bool bEverRefreshedDispatchFactoriesAfterEngineInit;` — This is true if the dispatch factories and functions have been greedily loaded once during engine init

#### enum `FRigVMRegistry_NoLock::ELockType`  
`enum ELockType : uint8`  
_L50-55_
- L52 _public enumerator_ `LockType_Read`
- L53 _public enumerator_ `LockType_Write`
- L54 _public enumerator_ `LockType_Invalid`

#### enum `FRigVMRegistry_NoLock::ERegisterObjectOperation`  
`enum class ERegisterObjectOperation`  
_L104-111_
- desc: How to register an object's class when passed to RegisterObjectTypes
- L106 _public enumerator_ `Class`
- L108 _public enumerator_ `ClassAndParents`
- L110 _public enumerator_ `ClassAndChildren`

#### struct `FRigVMRegistry_NoLock::FTypeInfo`  
`struct FTypeInfo`  
_L384-408_
- L386 _public function_ `FTypeInfo() : Type() , BaseTypeIndex(INDEX_NONE) , ArrayTypeIndex(INDEX_NONE) , bIsArray(false) , bIsExecute(false) , Hash(UINT32_MAX)`
- L395 _public member_ `FRigVMTemplateArgumentType Type;`
- L396 _public member_ `TRigVMTypeIndex BaseTypeIndex;`
- L397 _public member_ `TRigVMTypeIndex ArrayTypeIndex;`
- L398 _public member_ `bool bIsArray;`
- L399 _public member_ `bool bIsExecute;`
- L400 _public member_ `mutable uint32 Hash;`
- L402 _public prototype_ `void Serialize_NoLock(FArchive& Ar);`
- L404 _public function_ `bool IsUnknownType() const`

#### struct `FRigVMRegistry_RWLock`  
`struct FRigVMRegistry_RWLock final : public FRigVMRegistry_NoLock`  
_L525-1578_
- inherits: `FRigVMRegistry_NoLock`
- desc: The FRigVMRegistry is used to manage all known function pointers for use in the RigVM. The Register method is called automatically when the static struct is initially constructed for each USTRUCT hosting a RIGVM_METHOD enabled virtual function. Inheriting from FGCObject to ensure that all type objects cannot be GCed
- L527 _public typedef_ `typedef FRigVMRegistry_NoLock Super;`
- L707 _public prototype_ `static FRigVMRegistry_RWLock& Get();` — Returns the singleton registry
- L709 _public prototype_ `static FRigVMRegistry_NoLock& Get(ELockType InLockType) = delete;`
- L710 _public prototype_ `static const FRigVMRegistry_NoLock& GetForRead() = delete;`
- L711 _public prototype_ `static FRigVMRegistry_NoLock& GetForWrite() = delete;`
- L716 _public function_ `void Register(const TCHAR* InName, FRigVMFunctionPtr InFunctionPtr, UScriptStruct* InStruct = nullptr, const TArray<FRigVMFunctionArgument>& InArguments = TArray<FRigVMFunctionArgument>(), bool bLockRegistry = true)` — Registers a function given its name. The name will be the name of the struct and virtual method, for example "FMyStruct::MyVirtualMethod"
- L722 _public function_ `void RegisterCompiledInStruct(UScriptStruct* InStruct, TConstArrayView<FRigVMCompiledInFunction> InFunctions)`
- L730 _public function_ `bool RemoveFunction(int32 InFunctionIndex)` — Unregisters a function given its function index. This keeps the function index stable - but assigns an invalid function
- L737 _public function_ `const FRigVMDispatchFactory* RegisterFactory(UScriptStruct* InFactoryStruct)` — Registers a dispatch factory given its struct.
- L745 _public function_ `bool RemoveFactory(UScriptStruct* InFactoryStruct)` — Unregisters a factory given its script struct. This keeps the template index stable
- L753 _public function_ `bool RemoveTemplate(int32 InTemplateIndex)` — Unregisters a template given its index. This keeps the template index stable - but assigns an invalid template
- L760 _public function_ `void RegisterPredicate(UScriptStruct* InStruct, const TCHAR* InName, const TArray<FRigVMFunctionArgument>& InArguments)` — Register a predicate contained in the input struct
- L767 _public function_ `void RegisterObjectTypes(TConstArrayView<TPair<UClass*, ERegisterObjectOperation>> InClasses)` — Register a set of allowed object types
- L774 _public function_ `void RegisterStructTypes(TConstArrayView<UScriptStruct*> InStructs)` — Register a set of allowed struct types
- L782 _public function_ `void RefreshEngineTypes()` — Refreshes the list and finds the function pointers based on the names.
- L790 _public function_ `void RefreshEngineTypesIfRequired()` — Refreshes the list and finds the function pointers based on the names.
- L797 _public function_ `bool RefreshFunctionsAndDispatches()` — Refreshes the registered functions and dispatches.
- L804 _public function_ `void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath)` — Update the registry when types are renamed
- L811 _public prototype_ `void OnCleanupUnloadingObjects(const TArrayView<UObject*> InObjects);` — Update the registry when old types are being unloaded
- L814 _public prototype_ `void OnAssetRemoved(const FAssetData& InAssetData);` — Update the registry when old types are removed
- L817 _public prototype_ `void OnPluginLoaded(IPlugin& InPlugin);` — May add factories and unit functions declared in the plugin
- L820 _public prototype_ `void OnPluginUnloaded(IPlugin& InPlugin);` — Removes all types associated with a plugin that's being unloaded.
- L823 _public prototype_ `void OnModulesUnloaded(TConstArrayView<FName> ModuleNames);` — Removes all types associated with modules that are being unloaded.
- L827 _public prototype_ `void OnAnimationAttributeTypesChanged(const UScriptStruct* InStruct, bool bIsAdded);` — Update the registry when new types are added to the attribute system so that they can be selected on Attribute Nodes
- L830 _public function_ `FOnRigVMRegistryChanged& OnRigVMRegistryChanged()` — Notifies other system that types have been added/removed, and template permutations have been updated
- L833 _public function_ `void Reset()` — Clear the registry
- L841 _public function_ `TRigVMTypeIndex FindOrAddType(const FRigVMTemplateArgumentType& InType, bool bForce = false)` — Adds a type if it doesn't exist yet and returns its index. This function is thread-safe
- L849 _public function_ `bool RemoveType(const FSoftObjectPath& InObjectPath)` — Removes a type from the registry, and updates all dependent templates which also creates invalid permutations in templates that we should ignore
- L857 _public function_ `bool RemoveType(TRigVMTypeIndex InTypeIndex)` — Removes a type from the registry, and updates all dependent templates which also creates invalid permutations in templates that we should ignore
- L864 _public function_ `TRigVMTypeIndex GetTypeIndex(const FRigVMTemplateArgumentType& InType) const` — Returns the type index given a type
- L871 _public function_ `TRigVMTypeIndex GetTypeIndex(const FName& InCPPType, UObject* InCPPTypeObject) const` — Returns the type index given a cpp type and a type object
- L878 _public function_ `template <typename T> TRigVMTypeIndex GetTypeIndex(bool bAsArray = false) const` — Returns the type index given an enum, struct, or object
- L885 _public function_ `const FRigVMTemplateArgumentType& GetType(TRigVMTypeIndex InTypeIndex) const` — Returns the type given its index
- L892 _public function_ `int32 NumTypes() const` — Returns the number of types
- L899 _public function_ `const FRigVMTemplateArgumentType& FindTypeFromCPPType(const FString& InCPPType) const` — Returns the type given only its cpp type
- L906 _public function_ `TRigVMTypeIndex GetTypeIndexFromCPPType(const FString& InCPPType) const` — Returns the type index given only its cpp type
- L913 _public function_ `bool IsArrayType(TRigVMTypeIndex InTypeIndex) const` — Returns true if the type is an array
- L920 _public function_ `bool IsExecuteType(TRigVMTypeIndex InTypeIndex) const` — Returns true if the type is an execute type
- L927 _public function_ `bool ConvertExecuteContextToBaseType(TRigVMTypeIndex& InOutTypeIndex) const` — Converts the given execute context type to the base execute context type
- L934 _public function_ `int32 GetArrayDimensionsForType(TRigVMTypeIndex InTypeIndex) const` — Returns the dimensions of the array
- L941 _public function_ `bool IsWildCardType(TRigVMTypeIndex InTypeIndex) const` — Returns true if the type is a wildcard type
- L948 _public function_ `bool CanMatchTypes(TRigVMTypeIndex InTypeIndexA, TRigVMTypeIndex InTypeIndexB, bool bAllowFloatingPointCasts) const` — Returns true if the types can be matched.
- L955 _public function_ `const TArray<TRigVMTypeIndex>& GetCompatibleTypes(TRigVMTypeIndex InTypeIndex) const` — Returns the list of compatible types for a given type
- L962 _public function_ `const TArray<TRigVMTypeIndex>& GetTypesForCategory(FRigVMTemplateArgument::ETypeCategory InCategory) const` — Returns all compatible types given a category
- L969 _public function_ `TRigVMTypeIndex GetArrayTypeFromBaseTypeIndex(TRigVMTypeIndex InTypeIndex) const` — Returns the type index of the array matching the given element type index
- L976 _public function_ `TRigVMTypeIndex GetBaseTypeFromArrayTypeIndex(TRigVMTypeIndex InTypeIndex) const` — Returns the type index of the element matching the given array type index
- L983 _public function_ `bool IsSpecificallyAllowedType(const UObject* InObject) const` — Returns true if the given type is specifically allowed
- L990 _public function_ `void AddSpecificallyAllowedType(const UObject* InObject)` — Sets a given type as specifically allowed
- L997 _public function_ `const FRigVMFunction* FindFunction(const TCHAR* InName, const FRigVMUserDefinedTypeResolver& InTypeResolver = FRigVMUserDefinedTypeResolver()) const` — Returns the function given its name (or nullptr)
- L1004 _public function_ `const FRigVMFunction* FindFunction(UScriptStruct* InStruct, const TCHAR* InName, const FRigVMUserDefinedTypeResolver& InResolvalInfo = FRigVMUserDefinedTypeResolver()) const` — Returns the function given its backing up struct and method name
- L1011 _public function_ `const TChunkedArray<FRigVMFunction>& GetFunctions() const` — Returns all current RigVM functions
- L1018 _public function_ `const FRigVMTemplate* FindTemplate(const FName& InNotation, bool bIncludeDeprecated = false, bool bRemapToCoreDispatch = true) const` — Returns a template pointer given its notation (or nullptr)
- L1025 _public function_ `const TChunkedArray<FRigVMTemplate>& GetTemplates() const` — Returns all current RigVM functions
- L1032 _public function_ `const FRigVMTemplate* GetOrAddTemplateFromArguments( const FName& InName, const TArray<FRigVMTemplateArgumentInfo>& InInfos, const FRigVMTemplateDelegates& InDelegates)` — Defines and retrieves a template given its arguments
- L1042 _public function_ `const FRigVMTemplate* AddTemplateFromArguments( const FName& InName, const TArray<FRigVMTemplateArgumentInfo>& InInfos, const FRigVMTemplateDelegates& InDelegates)` — Adds a new template given its arguments
- L1052 _public function_ `FRigVMDispatchFactory* FindDispatchFactory(const FName& InFactoryName) const` — Returns a dispatch factory given its name (or nullptr)
- L1059 _public function_ `FRigVMDispatchFactory* FindOrAddDispatchFactory(UScriptStruct* InFactoryStruct)` — Returns a dispatch factory given its static struct (or nullptr)
- L1070 _public function_ `FRigVMDispatchFactory* FindOrAddDispatchFactory()`
- L1077 _public function_ `FString FindOrAddSingletonDispatchFunction(UScriptStruct* InFactoryStruct)` — Returns a dispatch factory's singleton function name if that exists
- L1088 _public function_ `FString FindOrAddSingletonDispatchFunction()`
- L1095 _public function_ `const TArray<FRigVMDispatchFactory*>& GetFactories() const` — Returns all dispatch factories
- L1102 _public function_ `const TArray<FRigVMFunction>* GetPredicatesForStruct(const FName& InStructName) const` — Given a struct name, return the predicates
- L1109 _public function_ `uint32 GetHashForType(TRigVMTypeIndex InTypeIndex) const` — Returns a unique hash per type index
- L1115 _public function_ `uint32 GetHashForScriptStruct(const UScriptStruct* InScriptStruct, bool bCheckTypeIndex = true) const`
- L1121 _public function_ `uint32 GetHashForStruct(const UStruct* InStruct) const`
- L1127 _public function_ `uint32 GetHashForEnum(const UEnum* InEnum, bool bCheckTypeIndex = true) const`
- L1133 _public function_ `uint32 GetHashForProperty(const FProperty* InProperty) const`
- L1139 _public function_ `void RebuildRegistry()`
- L1151 _protected function_ `virtual void Register_NoLock(const TCHAR* InName, FRigVMFunctionPtr InFunctionPtr, UScriptStruct* InStruct = nullptr, const TArray<FRigVMFunctionArgument>& InArguments = TArray<FRigVMFunctionArgument>()) override` — Registers a function given its name. The name will be the name of the struct and virtual method, for example "FMyStruct::MyVirtualMethod" Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1157 _protected function_ `virtual void RegisterCompiledInStruct_NoLock(UScriptStruct* InStruct, TConstArrayView<FRigVMCompiledInFunction> InFunctions) override` — As above but registers a collection of functions for a struct
- L1163 _protected function_ `virtual bool RemoveFunction_NoLock(int32 InFunctionIndex) override` — This keeps the function index stable - but assigns an invalid function
- L1170 _protected function_ `virtual const FRigVMDispatchFactory* RegisterFactory_NoLock(UScriptStruct* InFactoryStruct, const TArray<FRigVMTemplateArgumentInfo>& InArgumentInfos = {}) override` — Registers a dispatch factory given its struct. Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1177 _protected function_ `virtual bool RemoveFactory_NoLock(UScriptStruct* InFactoryStruct) override` — Unregisters a factory given its script struct. This keeps the template index stable
- L1184 _protected function_ `virtual bool RemoveTemplate_NoLock(int32 InTemplateIndex) override` — Unregisters a template given its index. This keeps the template index stable - but assigns an invalid template
- L1191 _protected function_ `virtual void RegisterPredicate_NoLock(UScriptStruct* InStruct, const TCHAR* InName, const TArray<FRigVMFunctionArgument>& InArguments) override` — Register a predicate contained in the input struct Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1198 _protected function_ `virtual void RegisterObjectTypes_NoLock(TConstArrayView<TPair<UClass*, ERegisterObjectOperation>> InClasses) override` — Register a set of allowed object types Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1206 _protected function_ `virtual void RefreshEngineTypes_NoLock() override` — Refreshes the list and finds the function pointers based on the names. Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1212 _protected function_ `virtual bool RefreshFunctionsAndDispatches_NoLock() override` — Refreshes the registered functions and dispatches.
- L1220 _protected function_ `virtual void RefreshEngineTypesIfRequired_NoLock() override` — Refreshes the list and finds the function pointers based on the names. Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1227 _protected function_ `virtual bool OnCleanupUnloadingObjects_NoLock(const TArrayView<UObject*> InObjects) override` — Update the registry when old types are being unloaded Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1234 _protected function_ `virtual void OnAssetRenamed_NoLock(const FAssetData& InAssetData, const FString& InOldObjectPath) override` — Update the registry when types are renamed Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1241 _protected function_ `virtual bool OnAssetRemoved_NoLock(const FAssetData& InAssetData) override` — Update the registry when old types are removed Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1248 _protected function_ `virtual bool OnPluginLoaded_NoLock(IPlugin& InPlugin) override` — May add factories and unit functions declared in the plugin Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1255 _protected function_ `virtual bool OnPluginUnloaded_NoLock(IPlugin& InPlugin) override` — Removes all types associated with a plugin that's being unloaded. Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1263 _protected function_ `virtual void OnAnimationAttributeTypesChanged_NoLock(const UScriptStruct* InStruct, bool bIsAdded) override` — Update the registry when new types are added to the attribute system so that they can be selected on Attribute Nodes Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1270 _protected function_ `virtual void Reset_NoLock() override` — Clear the registry Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1278 _protected function_ `virtual TRigVMTypeIndex FindOrAddType_NoLock(const FRigVMTemplateArgumentType& InType, bool bForce = false) override` — Adds a type if it doesn't exist yet and returns its index. This function is thread-safe Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1286 _protected function_ `virtual bool RemoveType_NoLock(const FSoftObjectPath& InObjectPath) override` — Removes a type from the registry, and updates all dependent templates which also creates invalid permutations in templates that we should ignore Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1294 _protected function_ `virtual bool RemoveType_NoLock(TRigVMTypeIndex InTypeIndex) override` — Removes a type from the registry, and updates all dependent templates which also creates invalid permutations in templates that we should ignore Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1301 _protected function_ `virtual TRigVMTypeIndex GetTypeIndex_NoLock(const FRigVMTemplateArgumentType& InType) const override` — Returns the type index given a type Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1308 _protected function_ `virtual TRigVMTypeIndex GetTypeIndex_NoLock(const FName& InCPPType, UObject* InCPPTypeObject) const override` — Returns the type index given a cpp type and a type object Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1315 _protected function_ `virtual const FRigVMTemplateArgumentType& GetType_NoLock(TRigVMTypeIndex InTypeIndex) const override` — Returns the type given its index Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1322 _protected function_ `virtual int32 NumTypes_NoLock() const override` — Returns the number of types Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1329 _protected function_ `virtual const FRigVMTemplateArgumentType& FindTypeFromCPPType_NoLock(const FString& InCPPType) const override` — Returns the type given only its cpp type Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1336 _protected function_ `virtual TRigVMTypeIndex GetTypeIndexFromCPPType_NoLock(const FString& InCPPType) const override` — Returns the type index given only its cpp type Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1343 _protected function_ `virtual bool IsArrayType_NoLock(TRigVMTypeIndex InTypeIndex) const override` — Returns true if the type is an array Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1350 _protected function_ `virtual bool IsExecuteType_NoLock(TRigVMTypeIndex InTypeIndex) const override` — Returns true if the type is an execute type Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1357 _protected function_ `virtual bool ConvertExecuteContextToBaseType_NoLock(TRigVMTypeIndex& InOutTypeIndex) const override` — Converts the given execute context type to the base execute context type Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1364 _protected function_ `virtual int32 GetArrayDimensionsForType_NoLock(TRigVMTypeIndex InTypeIndex) const override` — Returns the dimensions of the array Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1371 _protected function_ `virtual bool IsWildCardType_NoLock(TRigVMTypeIndex InTypeIndex) const override` — Returns true if the type is a wildcard type Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1378 _protected function_ `virtual bool CanMatchTypes_NoLock(TRigVMTypeIndex InTypeIndexA, TRigVMTypeIndex InTypeIndexB, bool bAllowFloatingPointCasts) const override` — Returns true if the types can be matched. Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1385 _protected function_ `virtual const TArray<TRigVMTypeIndex>& GetCompatibleTypes_NoLock(TRigVMTypeIndex InTypeIndex) const override` — Returns the list of compatible types for a given type Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1392 _protected function_ `virtual const TArray<TRigVMTypeIndex>& GetTypesForCategory_NoLock(FRigVMTemplateArgument::ETypeCategory InCategory) const override` — Returns all compatible types given a category Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1399 _protected function_ `virtual TRigVMTypeIndex GetArrayTypeFromBaseTypeIndex_NoLock(TRigVMTypeIndex InTypeIndex) const override` — Returns the type index of the array matching the given element type index Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1406 _protected function_ `virtual TRigVMTypeIndex GetBaseTypeFromArrayTypeIndex_NoLock(TRigVMTypeIndex InTypeIndex) const override` — Returns the type index of the element matching the given array type index Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1413 _protected function_ `virtual bool IsSpecificallyAllowedType_NoLock(const UObject* InObject) const override` — Returns true if the given type is specifically allowed Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1420 _protected function_ `virtual void AddSpecificallyAllowedType_NoLock(const UObject* InObject) override` — Sets a given type as specifically allowed Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1427 _protected function_ `virtual const FRigVMFunction* FindFunction_NoLock(const TCHAR* InName, const FRigVMUserDefinedTypeResolver& InTypeResolver = FRigVMUserDefinedTypeResolver()) const override` — Returns the function given its name (or nullptr) Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1434 _protected function_ `virtual const FRigVMFunction* FindFunction_NoLock(UScriptStruct* InStruct, const TCHAR* InName, const FRigVMUserDefinedTypeResolver& InResolvalInfo = FRigVMUserDefinedTypeResolver()) const override` — Returns the function given its backing up struct and method name Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1441 _protected function_ `virtual const TChunkedArray<FRigVMFunction>& GetFunctions_NoLock() const override` — Returns all current RigVM functions Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1448 _protected function_ `virtual const FRigVMTemplate* FindTemplate_NoLock(const FName& InNotation, bool bIncludeDeprecated = false, bool bRemapToCoreDispatch = true) const override` — Returns a template pointer given its notation (or nullptr) Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1455 _protected function_ `virtual const TChunkedArray<FRigVMTemplate>& GetTemplates_NoLock() const override` — Returns all current RigVM functions Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1462 _protected function_ `virtual const FRigVMTemplate* GetOrAddTemplateFromArguments_NoLock( const FName& InName, const TArray<FRigVMTemplateArgumentInfo>& InInfos, const FRigVMTemplateDelegates& InDelegates) override` — Defines and retrieves a template given its arguments Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1472 _protected function_ `virtual const FRigVMTemplate* AddTemplateFromArguments_NoLock( const FName& InName, const TArray<FRigVMTemplateArgumentInfo>& InInfos, const FRigVMTemplateDelegates& InDelegates) override` — Adds a new template given its arguments Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1482 _protected function_ `virtual FRigVMDispatchFactory* FindDispatchFactory_NoLock(const FName& InFactoryName) const override` — Returns a dispatch factory given its name (or nullptr) Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1489 _protected function_ `virtual FRigVMDispatchFactory* FindOrAddDispatchFactory_NoLock(UScriptStruct* InFactoryStruct) override` — Returns a dispatch factory given its static struct (or nullptr) Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1496 _protected function_ `virtual FString FindOrAddSingletonDispatchFunction_NoLock(UScriptStruct* InFactoryStruct) override` — Returns a dispatch factory's singleton function name if that exists Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1503 _protected function_ `virtual const TArray<FRigVMDispatchFactory*>& GetFactories_NoLock() const override` — Returns all dispatch factories Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1510 _protected function_ `virtual const TArray<FRigVMFunction>* GetPredicatesForStruct_NoLock(const FName& InStructName) const override` — Given a struct name, return the predicates Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1517 _protected function_ `virtual uint32 GetHashForType_NoLock(TRigVMTypeIndex InTypeIndex) const override` — Returns a unique hash per type index Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1523 _protected function_ `virtual uint32 GetHashForScriptStruct_NoLock(const UScriptStruct* InScriptStruct, bool bCheckTypeIndex = true) const override` — Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1529 _protected function_ `virtual uint32 GetHashForStruct_NoLock(const UStruct* InStruct) const override` — Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1535 _protected function_ `virtual uint32 GetHashForEnum_NoLock(const UEnum* InEnum, bool bCheckTypeIndex = true) const override` — Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1541 _protected function_ `virtual uint32 GetHashForProperty_NoLock(const FProperty* InProperty) const override` — Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1547 _protected function_ `virtual void RebuildRegistry_NoLock() override` — Note: Only call NoLock methods on the FRigVMRegistry_NoLock
- L1554 _private prototype_ `FRigVMRegistry_RWLock(bool bInIsGlobalRegistry);`
- L1556 _private prototype_ `static void EnsureLocked(ELockType InLockType);`
- L1558 _private prototype_ `void Initialize_NoLock();`
- L1560 _private prototype_ `static void SuspendGlobalUnmount();`
- L1561 _private prototype_ `static void ResumeGlobalUnmount();`
- L1563 _private member_ `mutable FTransactionallySafeRWLock Lock;`
- L1564 _private member_ `mutable std::atomic<ELockType> LockType = LockType_Invalid;`
- L1565 _private member_ `mutable std::atomic<int32> LockCount = 0;`
- L1566 _private member_ `mutable std::atomic<uint32> WriteLockOwnerThread = static_cast<uint32>(-1);`
- L1570 _private member_ `FOnRigVMRegistryChanged OnRigVMRegistryChangedDelegate;` — Notifies other system that types have been added/removed, and template permutations have been updated

#### class `FRigVMRegistry_RWLock::FConditionalScopeLock`  
`class FConditionalScopeLock : public FRigVMRegistryHandleLock`  
_L531-663_
- inherits: `FRigVMRegistryHandleLock`
- L534 _public function_ `UE_NODISCARD_CTOR explicit FConditionalScopeLock(const FRigVMRegistry_RWLock& InRegistry, ELockType InLockType, bool bInLockEnabled = true) : FRigVMRegistryHandleLock(&InRegistry, bInLockEnabled) , Registry(const_cast<FRigVMRegistry_RWLock*>(&InRegistry)) , DesiredLockType(InLockType)`
- L601 _public function_ `~FConditionalScopeLock()`
- L648 _public function_ `FRigVMRegistry_NoLock& GetRegistry()`
- L653 _public function_ `const FRigVMRegistry_NoLock& GetRegistry() const`
- L659 _private member_ `FRigVMRegistry_RWLock* Registry;`
- L660 _private member_ `ELockType DesiredLockType;`

#### class `FRigVMRegistry_RWLock::FConditionalReadScopeLock`  
`class FConditionalReadScopeLock : public FConditionalScopeLock`  
_L667-681_
- inherits: `FConditionalScopeLock`
- L670 _public function_ `UE_NODISCARD_CTOR explicit FConditionalReadScopeLock(const FRigVMRegistry_RWLock& InRegistry, bool bInLockEnabled = true) : FConditionalScopeLock(InRegistry, LockType_Read, bInLockEnabled)`
- L675 _public function_ `UE_NODISCARD_CTOR explicit FConditionalReadScopeLock(bool bInLockEnabled = true) : FConditionalReadScopeLock(FRigVMRegistry_RWLock::Get(), bInLockEnabled)`

#### class `FRigVMRegistry_RWLock::FConditionalWriteScopeLock`  
`class FConditionalWriteScopeLock : public FConditionalScopeLock`  
_L683-697_
- inherits: `FConditionalScopeLock`
- L686 _public function_ `UE_NODISCARD_CTOR explicit FConditionalWriteScopeLock(const FRigVMRegistry_RWLock& InRegistry, bool bInLockEnabled = true) : FConditionalScopeLock(InRegistry, LockType_Write, bInLockEnabled)`
- L691 _public function_ `UE_NODISCARD_CTOR explicit FConditionalWriteScopeLock(bool bInLockEnabled = true) : FConditionalWriteScopeLock(FRigVMRegistry_RWLock::Get(), bInLockEnabled)`

#### class `FRigVMRegistry_RWLock::FSuspendPluginUnmounting`  
`class FSuspendPluginUnmounting`  
_L699-704_
- L702 _public function_ `UE_NODISCARD_CTOR FSuspendPluginUnmounting()`
- L703 _public function_ `~FSuspendPluginUnmounting()`

#### struct `FRigVMCompiledInStruct`  
`struct FRigVMCompiledInStruct`  
_L1585-1589_
- desc: Structs used by UHT to register UScriptStructs that have RigVM functions
- L1587 _public member_ `UScriptStruct* Struct = nullptr;`
- L1588 _public member_ `TConstArrayView<FRigVMCompiledInFunction> Functions;`

#### struct `FRegisterRigVMStructs`  
`struct FRegisterRigVMStructs`  
_L1591-1597_
- L1593 _public member_ `TConstArrayView<FRigVMCompiledInStruct> Structs;`
- L1594 _public member_ `FRegisterRigVMStructs* Next = nullptr;`
- L1596 _public prototype_ `FRegisterRigVMStructs(TConstArrayView<FRigVMCompiledInStruct> InStructs);`

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API RIGVM_API`
- L34 _typedef_ `typedef FRigVMRegistry_RWLock FRigVMRegistry;`
- L36 _externvar_ `extern TAutoConsoleVariable<bool> CVarRigVMEnableLocalizedRegistry;`
- L70 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRigVMRegistryChanged);`
- L576 _function_ `` (scope `FRigVMRegistry_RWLock::FConditionalScopeLock::FConditionalScopeLock`)
- L1580 _typedef_ `using FRigVMRegistryReadLock = FRigVMRegistry_RWLock::FConditionalReadScopeLock;`
- L1581 _typedef_ `using FRigVMRegistryWriteLock = FRigVMRegistry_RWLock::FConditionalWriteScopeLock;`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMRegistryHandle.h` (Public)


#### struct `FRigVMRegistryHandle`  
`struct FRigVMRegistryHandle`  
_L11-34_
- L15 _public prototype_ `FRigVMRegistryHandle();`
- L17 _public prototype_ `bool IsValid() const;`
- L19 _public prototype_ `FRigVMRegistry_NoLock* operator->();`
- L20 _public prototype_ `const FRigVMRegistry_NoLock* operator->() const;`
- L22 _public prototype_ `FRigVMRegistry_NoLock* GetRegistry();`
- L23 _public prototype_ `const FRigVMRegistry_NoLock* GetRegistry() const;`
- L28 _protected prototype_ `FRigVMRegistryHandle(const FRigVMRegistry_NoLock* InRegistry);`
- L30 _protected member_ `FRigVMRegistry_NoLock* Registry;`

#### struct `FRigVMRegistryHandleLock`  
`struct FRigVMRegistryHandleLock : public FRigVMRegistryHandle`  
_L36-48_
- inherits: `FRigVMRegistryHandle`
- L38 _public function_ `FRigVMRegistryHandleLock(const FRigVMRegistry_NoLock* InRegistry, bool bInLockEnabled) : FRigVMRegistryHandle(InRegistry) , bLockEnabled(bInLockEnabled)`
- L47 _protected member_ `bool bLockEnabled;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMStatistics.h` (Public)


#### struct `FRigVMMemoryStatistics`  
`struct FRigVMMemoryStatistics`  
_L9-23_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `int32 RegisterCount = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")`
- L19 _public member_ `int32 DataBytes = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")`
- L22 _public member_ `int32 TotalBytes = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")`

#### struct `FRigVMByteCodeStatistics`  
`struct FRigVMByteCodeStatistics`  
_L26-37_
- reflection: `USTRUCT(BlueprintType)`
- L33 _public member_ `int32 InstructionCount = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")`
- L36 _public member_ `int32 DataBytes = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")`

#### struct `FRigVMStatistics`  
`struct FRigVMStatistics`  
_L40-66_
- reflection: `USTRUCT(BlueprintType)`
- L47 _public member_ `int32 BytesForCDO = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")`
- L50 _public member_ `int32 BytesPerInstance = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")`
- L53 _public member_ `FRigVMMemoryStatistics LiteralMemory;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")`
- L56 _public member_ `FRigVMMemoryStatistics WorkMemory;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")`
- L59 _public member_ `FRigVMMemoryStatistics DebugMemory;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")`
- L62 _public member_ `int32 BytesForCaching = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")`
- L65 _public member_ `FRigVMByteCodeStatistics ByteCode;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMStruct.h` (Public)


#### enum `ERigVMNodeCreatedReason`  
`enum class ERigVMNodeCreatedReason : uint8`  
_L42-49_
- desc: Context as of why the node was created
- L44 _public enumerator_ `NodeSpawner`
- L45 _public enumerator_ `ScriptedEvent`
- L46 _public enumerator_ `Paste`
- L47 _public enumerator_ `BackwardsCompatibility`
- L48 _public enumerator_ `Unknown`

#### struct `FRigVMUnitNodeCreatedContext`  
`struct FRigVMUnitNodeCreatedContext`  
_L54-179_
- desc: A context struct passed to FRigVMStruct::OnUnitNodeCreated
- L91 _public prototype_ `bool IsValid() const;` — Returns true if this context is valid to use
- L94 _public function_ `ERigVMNodeCreatedReason GetReason() const` — Get the reason why this node was created
- L97 _public function_ `URigVMController* GetController() const`
- L98 _public function_ `IRigVMClientHost* GetHost() const`
- L102 _public function_ `FName GetNodeName() const` — Get the name of this node
- L105 _public prototype_ `TArray<FRigVMExternalVariable> GetExternalVariables() const;` — Returns all currently existing external variables
- L108 _public prototype_ `FName AddExternalVariable(const FRigVMExternalVariable& InVariableToCreate, FString InDefaultValue = FString());` — Creates a new variable within the host of this VM
- L111 _public prototype_ `bool BindPinToExternalVariable(FString InPinPath, FString InVariablePath);` — Binds a pin to an external variable on the created node
- L114 _public prototype_ `FRigVMExternalVariable FindVariable(FName InVariableName) const;` — Returns a variable given a name (or a non-valid variable if not found)
- L117 _public prototype_ `FName FindFirstVariableOfType(FName InCPPTypeName) const;` — Returns the name of the first variable given a(or NAME_None if not found)
- L124 _public function_ `FName FindFirstVariableOfType() const`
- L159 _public function_ `FRigVMGetExternalVariablesDelegate& GetAllExternalVariablesDelegate()`
- L160 _public function_ `FRigVMCreateExternalVariableDelegate& GetCreateExternalVariableDelegate()`
- L161 _public function_ `FRigVMBindPinToExternalVariableDelegate& GetBindPinToExternalVariableDelegate()`
- L166 _private member_ `URigVMController* Controller = nullptr;`
- L167 _private member_ `IRigVMClientHost* Host = nullptr;`
- L169 _private member_ `FName NodeName = NAME_None;`
- L170 _private member_ `ERigVMNodeCreatedReason Reason = ERigVMNodeCreatedReason::Unknown;`
- L171 _private member_ `FRigVMGetExternalVariablesDelegate AllExternalVariablesDelegate;`
- L172 _private member_ `FRigVMCreateExternalVariableDelegate CreateExternalVariableDelegate;`
- L173 _private member_ `FRigVMBindPinToExternalVariableDelegate BindPinToExternalVariableDelegate;`
- L175 _private prototype_ `FName FindFirstVariableOfType(UObject* InCPPTypeObject) const;`

#### struct `FRigVMUnitNodeCreatedContext::FScope`  
`struct FScope`  
_L58-88_
- L61 _public function_ `FScope(FRigVMUnitNodeCreatedContext& InContext, ERigVMNodeCreatedReason InReason, IRigVMClientHost* InHost) : Context(InContext) , PreviousReason(InContext.GetReason()) #if WITH_EDITOR , PreviousHost(InContext.GetHost()) #endif`
- L74 _public function_ `~FScope()`
- L83 _private member_ `FRigVMUnitNodeCreatedContext& Context;`
- L84 _private member_ `ERigVMNodeCreatedReason PreviousReason;`
- L86 _private member_ `IRigVMClientHost* PreviousHost = nullptr;`

#### struct `FRigVMStruct`  
`struct FRigVMStruct`  
_L185-345_
- reflection: `USTRUCT()`
- desc: The base class for all RigVM enabled structs.
- L189 _public prototype_ `virtual ~FRigVMStruct() = default;`
- L190 _public function_ `virtual FString ProcessPinLabelForInjection(const FString& InLabel) const`
- L191 _public function_ `virtual FName GetEventName() const`
- L192 _public function_ `virtual bool CanOnlyExistOnce() const`
- L193 _public function_ `virtual FString GetUnitLabel() const`
- L194 _public function_ `virtual FString GetUnitSubTitle() const`
- L199 _public function_ `virtual const UScriptStruct* GetExecuteContextStruct() const` — return the execute script struct this unit wants to use
- L202 _public function_ `virtual void Initialize()` — initialize logic for this struct
- L205 _public function_ `virtual void Execute()` — Execute logic for this struct
- L208 _public function_ `virtual int32 GetNumSlices() const` — control flow related
- L210 _public prototype_ `bool IsForLoop() const;`
- L211 _public prototype_ `bool IsControlFlowNode() const;`
- L212 _public prototype_ `const TArray<FName>& GetControlFlowBlocks() const;`
- L214 _public function_ `virtual const bool IsControlFlowBlockSliced(const FName& InBlockName) const`
- L217 _public function_ `virtual void OnUnitNodeCreated(FRigVMUnitNodeCreatedContext& InContext) const` — node creation
- L220 _public prototype_ `TArray<FRigVMUserWorkflow> GetWorkflows(ERigVMUserWorkflowType InType, const UObject* InSubject) const;` — user workflow
- L223 _public prototype_ `static bool ValidateStruct(UScriptStruct* InStruct, FString* OutErrorMessage);`
- L224 _public prototype_ `static bool CheckPinType(UScriptStruct* InStruct, const FName& PinName, const FString& ExpectedType, FString* OutErrorMessage = nullptr);`
- L225 _public prototype_ `static bool CheckPinDirection(UScriptStruct* InStruct, const FName& PinName, const FName& InDirectionMetaName);`
- L226 _public prototype_ `static ERigVMPinDirection GetPinDirectionFromProperty(FProperty* InProperty);`
- L227 _public prototype_ `static bool CheckPinExists(UScriptStruct* InStruct, const FName& PinName, const FString& ExpectedType = FString(), FString* OutErrorMessage = nullptr);`
- L228 _public prototype_ `static bool CheckMetadata(UScriptStruct* InStruct, const FName& PinName, const FName& InMetadataKey, FString* OutErrorMessage = nullptr);`
- L229 _public prototype_ `static bool CheckFunctionExists(UScriptStruct* InStruct, const FName& FunctionName, FString* OutErrorMessage = nullptr);`
- L230 _public prototype_ `virtual bool ShouldCreatePinForProperty(const FProperty* InProperty) const;`
- L232 _public prototype_ `static FString ExportToFullyQualifiedText(const FProperty* InMemberProperty, const uint8* InMemberMemoryPtr, bool bUseQuotes = true);`
- L233 _public prototype_ `static FString ExportToFullyQualifiedText(const UScriptStruct* InStruct, const uint8* InStructMemoryPtr, bool bUseQuotes = true);`
- L239 _public function_ `static FString ExportToFullyQualifiedText(const T& InStructValue)`
- L253 _public prototype_ `FString ExportToFullyQualifiedText(const UScriptStruct* InScriptStruct, const FName& InPropertyName, const uint8* InStructMemoryPointer = nullptr, bool bUseQuotes = true) const;`
- L255 _public prototype_ `virtual FName GetNextAggregateName(const FName& InLastAggregatePinName) const;`
- L256 _public function_ `virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const`
- L258 _public member_ `static inline const FLazyName DeprecatedMetaName = FLazyName(TEXT("Depr`
- L259 _public member_ `static inline const FLazyName InputMetaName = FLazyName(TEXT("Inpu`
- L260 _public member_ `static inline const FLazyName OutputMetaName = FLazyName(TEXT("Outp`
- L261 _public member_ `static inline const FLazyName IOMetaName = FLazyName(TEXT("IO")`
- L262 _public member_ `static inline const FLazyName HiddenMetaName = FLazyName(TEXT("Hidd`
- L263 _public member_ `static inline const FLazyName VisibleMetaName = FLazyName(TEXT("Visi`
- L265 _public member_ `static inline const FLazyName ExternalVariableMetaName = FLazyName(TEXT("Exte` — Meta tag for input pins that are mutable (passed by non-const reference). Must be combined with Input.
- L266 _public member_ `static inline const FLazyName DetailsOnlyMetaName = FLazyName(TEXT("Deta`
- L267 _public member_ `static inline const FLazyName AbstractMetaName = FLazyName(TEXT("Abst`
- L268 _public member_ `static inline const FLazyName CategoryMetaName = FLazyName(TEXT("Cate`
- L269 _public member_ `static inline const FLazyName DisplayNameMetaName = FLazyName(TEXT("Disp`
- L270 _public member_ `static inline const FLazyName MenuDescSuffixMetaName = FLazyName(TEXT("Menu`
- L271 _public member_ `static inline const FLazyName ShowVariableNameInTitleMetaName = FLazyName(TEXT("Show`
- L272 _public member_ `static inline const FLazyName CustomWidgetMetaName = FLazyName(TEXT("Cust`
- L273 _public member_ `static inline const FLazyName ConstantMetaName = FLazyName(TEXT("Cons`
- L274 _public member_ `static inline const FLazyName NoOpMetaName = FLazyName(TEXT("NoOp`
- L275 _public member_ `static inline const FLazyName TitleColorMetaName = FLazyName(TEXT("Titl`
- L276 _public member_ `static inline const FLazyName NodeColorMetaName = FLazyName(TEXT("Node`
- L280 _public member_ `static inline const FLazyName IconMetaName = FLazyName(TEXT("Icon` — icon meta name format: StyleSetName|StyleName|SmallStyleName|StatusOverlayStyleName the last two names are optional, see FSlateIcon() for reference Example: Icon="EditorStyle|GraphEditor.Sequence_16x"
- L281 _public member_ `static inline const FLazyName KeywordsMetaName = FLazyName(TEXT("Keyw`
- L282 _public member_ `static inline const FLazyName FixedSizeArrayMetaName = FLazyName(TEXT("Fixe`
- L283 _public member_ `static inline const FLazyName ShowOnlySubPinsMetaName = FLazyName(TEXT("Show`
- L284 _public member_ `static inline const FLazyName HideSubPinsMetaName = FLazyName(TEXT("Hide`
- L285 _public member_ `static inline const FLazyName ArraySizeMetaName = FLazyName(TEXT("Arra`
- L286 _public member_ `static inline const FLazyName AggregateMetaName = FLazyName(TEXT("Aggr`
- L287 _public member_ `static inline const FLazyName ExpandPinByDefaultMetaName = FLazyName(TEXT("Expa`
- L288 _public member_ `static inline const FLazyName DefaultArraySizeMetaName = FLazyName(TEXT("Defa`
- L289 _public member_ `static inline const FLazyName VaryingMetaName = FLazyName(TEXT("Vary`
- L290 _public member_ `static inline const FLazyName PureMetaName = FLazyName(TEXT("Pure` — The node will not modify the context
- L291 _public member_ `static inline const FLazyName SingletonMetaName = FLazyName(TEXT("Sing`
- L292 _public member_ `static inline const FLazyName SliceContextMetaName = FLazyName(TEXT("Slic`
- L293 _public member_ `static inline const FLazyName ExecuteName = FLazyName(TEXT("Exec`
- L294 _public member_ `static inline const FLazyName ExecuteContextName = FLazyName(TEXT("Exec`
- L295 _public member_ `static inline const FLazyName ExecutePinName = FLazyName(TEXT("Exec`
- L296 _public member_ `static inline const FLazyName ForLoopCountPinName = FLazyName(TEXT("Coun`
- L297 _public member_ `static inline const FLazyName ForLoopContinuePinName = FLazyName(TEXT("Cont`
- L298 _public member_ `static inline const FLazyName ForLoopCompletedPinName = FLazyName(TEXT("Comp`
- L299 _public member_ `static inline const FLazyName ForLoopIndexPinName = FLazyName(TEXT("Inde`
- L300 _public member_ `static inline const FLazyName ComputeLazilyMetaName = FLazyName(TEXT("Lazy`
- L301 _public member_ `static inline const FLazyName ControlFlowBlockToRunName = FLazyName(TEXT("Bloc`
- L302 _public member_ `static inline const FLazyName ControlFlowCompletedName = FLazyName(TEXT("Comp`
- L303 _public member_ `static inline const FLazyName ControlFlowCountName = FLazyName(TEXT("Coun`
- L304 _public member_ `static inline const FLazyName ControlFlowIndexName = FLazyName(TEXT("Inde`
- L312 _public function_ `static bool HasMetaData(const UScriptStruct* InStruct, const FName& InMetaDataKey)` — Checks if any struct in the hierarchy has the specified metadata. UScriptStruct metadata is not inherited automatically, so this walks up the hierarchy to check each struct in the chain.
- L327 _protected prototype_ `static float GetRatioFromIndex(int32 InIndex, int32 InCount);`
- L328 _protected prototype_ `TMap<FName, FString> GetDefaultValues(UScriptStruct* InScriptStruct) const;`
- L329 _protected prototype_ `static TMap<FName, FString> GetDefaultValues(const void* InValue, UScriptStruct* InScriptStruct);`
- L330 _protected prototype_ `bool ApplyUpgradeInfo(const FRigVMStructUpgradeInfo& InUpgradeInfo);`
- L331 _protected function_ `virtual TArray<FRigVMUserWorkflow> GetSupportedWorkflows(const UObject* InSubject) const`
- L334 _protected prototype_ `virtual const TArray<FName>& GetControlFlowBlocks_Impl() const;`
- L338 _protected prototype_ `static void ValidateControlFlowBlocks(const TArray<FName>& InBlocks);`

#### struct `FRigVMStructMutable`  
`struct FRigVMStructMutable : public FRigVMStruct`  
_L351-365_
- reflection: `USTRUCT()`
- inherits: `FRigVMStruct`
- desc: The base mutable class for all RigVM enabled structs.
- L355 _public prototype_ `virtual ~FRigVMStructMutable() = default;`
- L364 _public member_ `FRigVMExecutePin ExecutePin;` — `UPROPERTY(DisplayName = "Execute", Transient, meta = (Input, Output))` — This property is used to chain multiple mutable nodes together

#### Free symbols / members of external scopes

- L33 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<FRigVMExternalVariable>, FRigVMGetExternalVariablesDelegate) DECLARE_DELEGATE_RetVal_TwoParams(FName, FRigVMCreateExternalVariableDelegate, FRigVMExternalVariable, FString) DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMBindPinToExternalVariableDelegate, FString, FString) struct FRigVMStruct;` — delegates used for variable introspection / creation
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FName, FRigVMCreateExternalVariableDelegate, FRigVMExternalVariable, FString) DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMBindPinToExternalVariableDelegate, FString, FString) struct FRigVMStruct;`
- L35 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMBindPinToExternalVariableDelegate, FString, FString) struct FRigVMStruct;`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMStructTest.h` (Public)


#### class `FRigVMStructTestBase`  
`template<typename ExecuteContextType = FRigVMExecuteContext> class FRigVMStructTestBase : public FAutomationTestBase`  
_L9-35_
- inherits: `FAutomationTestBase`
- L12 _public function_ `FRigVMStructTestBase(const FString& InName, bool bIsComplex) : FAutomationTestBase(InName, bIsComplex) , ExtendedExecuteContext(nullptr) , ExecuteContext(DefaultExecuteContext)`
- L19 _public prototype_ `~FRigVMStructTestBase() = default;`
- L21 _public function_ `virtual void Initialize()`
- L28 _protected member_ `FRigVMExtendedExecuteContext ExtendedExecuteContext;`
- L31 _public member_ `ExecuteContextType& ExecuteContext;`
- L34 _private member_ `ExecuteContextType DefaultExecuteContext;`

#### Free symbols / members of external scopes

- L37 _macro_ `#define RIGVMSTRUCT_TEST_STRINGIFY(Content) #Content`
- L38 _macro_ `#define IMPLEMENT_RIGVMSTRUCT_AUTOMATION_TEST(TRigVMStruct) \`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMStructUpgradeInfo.h` (Public)


#### struct `FRigVMStructUpgradeInfo`  
`struct FRigVMStructUpgradeInfo`  
_L13-108_
- desc: Structure used to upgrade to a new implementation of a node
- L17 _public prototype_ `FRigVMStructUpgradeInfo();`
- L20 _public function_ `template<typename Old, typename New> FRigVMStructUpgradeInfo(const Old& InOld, const New& InNew)`
- L29 _public function_ `FRigVMStructUpgradeInfo(UScriptStruct* InOldDispatchStruct, UScriptStruct* InNewDispatchStruct, const FName& InOldDispatchFunction, const FName& InNewDispatchFunction)`
- L40 _public prototype_ `bool IsValid() const;` — returns true if this upgrade info can be applied
- L43 _public function_ `UScriptStruct* GetOldStruct() const` — returns the old struct trying to be upgraded
- L46 _public function_ `UScriptStruct* GetNewStruct() const` — returns the new struct to upgrade to
- L49 _public function_ `const TMap<FName, FString>& GetDefaultValues() const` — returns the map for all default values
- L52 _public prototype_ `const FString& GetDefaultValueForPin(const FName& InPinName) const;` — returns the default value for a given pin
- L55 _public prototype_ `void SetDefaultValueForPin(const FName& InPinName, const FString& InDefaultValue);` — sets the default value for a given pin
- L58 _public prototype_ `void AddRemappedPin(const FString& InOldPinPath, const FString& InNewPinPath, bool bAsInput = true, bool bAsOutput = true);` — adds a pin to be remapped
- L61 _public prototype_ `FString RemapPin(const FString& InPinPath, bool bIsInput, bool bContainsNodeName) const;` — remaps a pin path based on our internals
- L64 _public prototype_ `FString AddAggregatePin(FString InPinName = FString());` — adds a new aggregate pin
- L67 _public function_ `const TArray<FString>& GetAggregatePins() const` — returns the aggregate pins to add
- L70 _public prototype_ `static FRigVMTemplateTypeMap GetTypeMapFromStruct(UScriptStruct* InScriptStruct);` — returns a type map representing the struct members
- L76 _private member_ `FString NodePath;` — The complete node path including models / collapse node. The path may look like "RigGraph|CollapseNode1|Add"
- L79 _private member_ `UScriptStruct* OldStruct;` — The old struct this upgrade info originates from
- L82 _private member_ `UScriptStruct* NewStruct;` — The new struct this upgrade info is targeting
- L85 _private member_ `FName OldDispatchFunction;` — The old optional function name this upgrade info originates from
- L88 _private member_ `FName NewDispatchFunction;` — The new optional function name this upgrade info is targeting
- L92 _private member_ `TMap<FString, FString> InputLinkMap;` — Remapping info for re-linking inputs Entries can be root pins or sub pins
- L96 _private member_ `TMap<FString, FString> OutputLinkMap;` — Remapping info for re-linking outputs Entries can be root pins or sub pins
- L99 _private member_ `TMap<FName, FString> DefaultValues;` — New sets of default values
- L102 _private member_ `TArray<FString> AggregatePins;` — Aggregate pins to add
- L105 _private prototype_ `void SetDefaultValues(const void* InNewStructMemory);` — sets the default values from the new struct.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMTemplate.h` (Public)


#### struct `FRigVMTemplateDelegates`  
`struct FRigVMTemplateDelegates`  
_L40-44_
- L42 _public member_ `FRigVMTemplate_NewArgumentTypeDelegate NewArgumentTypeDelegate;`
- L43 _public member_ `FRigVMTemplate_GetDispatchFactoryDelegate GetDispatchFactoryDelegate;`

#### struct `FRigVMTemplateArgumentType`  
`struct FRigVMTemplateArgumentType`  
_L47-162_
- reflection: `USTRUCT()`
- L52 _public member_ `FName CPPType;` — `UPROPERTY()`
- L55 _public member_ `TObjectPtr<UObject> CPPTypeObject;` — `UPROPERTY()`
- L57 _public function_ `FRigVMTemplateArgumentType() : CPPType(NAME_None) , CPPTypeObject(nullptr)`
- L65 _public prototype_ `FRigVMTemplateArgumentType(const FName& InCPPType, UObject* InCPPTypeObject = nullptr, bool bIsSerializing = false);`
- L67 _public function_ `FRigVMTemplateArgumentType(UClass* InClass, RigVMTypeUtils::EClassArgType InClassArgType = RigVMTypeUtils::EClassArgType::AsObject) : CPPType(*RigVMTypeUtils::CPPTypeFromObject(InClass, InClassArgType)) , CPPTypeObject(InClass)`
- L73 _public function_ `FRigVMTemplateArgumentType(UScriptStruct* InScriptStruct) : CPPType(*RigVMTypeUtils::GetUniqueStructTypeName(InScriptStruct)) , CPPTypeObject(InScriptStruct)`
- L79 _public function_ `FRigVMTemplateArgumentType(UEnum* InEnum) : CPPType(*RigVMTypeUtils::CPPTypeFromEnum(InEnum)) , CPPTypeObject(InEnum)`
- L85 _public function_ `bool IsValid() const`
- L90 _public function_ `bool IsUnknownType() const`
- L99 _public prototype_ `void Serialize_NoLock(FArchive& Ar);`
- L101 _public function_ `static FRigVMTemplateArgumentType Array()`
- L106 _public function_ `bool operator == (const FRigVMTemplateArgumentType& InOther) const`
- L111 _public function_ `bool operator != (const FRigVMTemplateArgumentType& InOther) const`
- L121 _public function_ `FName GetCPPTypeObjectPath() const`
- L130 _public function_ `bool IsWildCard() const`
- L137 _public function_ `bool IsArray() const`
- L142 _public function_ `FString GetBaseCPPType() const`
- L151 _public function_ `FRigVMTemplateArgumentType& ConvertToArray()`
- L157 _public function_ `FRigVMTemplateArgumentType& ConvertToBaseElement()`

#### struct `FRigVMTemplateArgument`  
`struct FRigVMTemplateArgument`  
_L168-376_
- desc: The template argument represents a single parameter in a function call and all of its possible types
- L170 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FTypeFilter, const TRigVMTypeIndex&, const FRigVMRegistryHandle&);`
- L208 _public prototype_ `FRigVMTemplateArgument();` — default constructor
- L210 _public prototype_ `FRigVMTemplateArgument(const FName& InName, ERigVMPinDirection InDirection);`
- L211 _public prototype_ `FRigVMTemplateArgument(const FName& InName, ERigVMPinDirection InDirection, TRigVMTypeIndex InType, const FRigVMRegistryHandle& InRegistry);`
- L212 _public prototype_ `FRigVMTemplateArgument(const FName& InName, ERigVMPinDirection InDirection, const TArray<TRigVMTypeIndex>& InTypeIndices, const FRigVMRegistryHandle& InRegistry);`
- L213 _public prototype_ `FRigVMTemplateArgument(const FName& InName, ERigVMPinDirection InDirection, const TArray<ETypeCategory>& InTypeCategories, TFunction<bool(const TRigVMTypeIndex&, const FRigVMRegistryHandle&)> InFilterType, const FRigVMRegistryHandle& InRegistry);`
- L216 _public function_ `const FName& GetName() const` — returns the name of the argument
- L219 _public function_ `ERigVMPinDirection GetDirection() const` — returns the direction of the argument
- L223 _public prototype_ `bool SupportsTypeIndex(TRigVMTypeIndex InTypeIndex, TRigVMTypeIndex* OutTypeIndex = nullptr) const;` — returns true if this argument supports a given type across a set of permutations
- L224 _public prototype_ `bool SupportsTypeIndex_NoLock(const FRigVMRegistryHandle& InRegistry, TRigVMTypeIndex InTypeIndex, TRigVMTypeIndex* OutTypeIndex = nullptr) const;`
- L228 _public prototype_ `void GetAllTypes(TArray<TRigVMTypeIndex>& OutTypes) const;` — returns the flat list of types (including duplicates) of this argument
- L229 _public prototype_ `void GetAllTypes_NoLock(TArray<TRigVMTypeIndex>& OutTypes, const FRigVMRegistryHandle& InRegistry) const;`
- L231 _public prototype_ `TRigVMTypeIndex GetTypeIndex(const int32 InIndex) const;`
- L232 _public prototype_ `TRigVMTypeIndex GetTypeIndex_NoLock(const int32 InIndex, const FRigVMRegistryHandle& InRegistry) const;`
- L233 _public prototype_ `TOptional<TRigVMTypeIndex> TryToGetTypeIndex(const int32 InIndex) const;`
- L234 _public prototype_ `TOptional<TRigVMTypeIndex> TryToGetTypeIndex_NoLock(const int32 InIndex, const FRigVMRegistryHandle& InRegistry) const;`
- L235 _public prototype_ `int32 GetNumTypes(const FRigVMRegistryHandle& InRegistry) const;`
- L236 _public prototype_ `int32 GetNumTypes_NoLock(const FRigVMRegistryHandle& InRegistry) const;`
- L237 _public prototype_ `void AddTypeIndex(const TRigVMTypeIndex InTypeIndex);`
- L238 _public prototype_ `void RemoveType(const int32 InIndex);`
- L239 _public prototype_ `void ForEachType(TFunction<bool(const TRigVMTypeIndex InType)>&& InCallback, const FRigVMRegistryHandle& InRegistry) const;`
- L240 _public prototype_ `int32 FindTypeIndex(const TRigVMTypeIndex InTypeIndex, const FRigVMRegistryHandle& InRegistry) const;`
- L243 _public function_ `template <typename Predicate> int32 IndexOfByPredicate(Predicate Pred, const FRigVMRegistryHandle& InRegistry) const`
- L276 _public prototype_ `TArray<TRigVMTypeIndex> GetSupportedTypeIndices(const TArray<int32>& InPermutationIndices = TArray<int32>()) const;` — returns an array of all of the supported types
- L277 _public prototype_ `TArray<TRigVMTypeIndex> GetSupportedTypeIndices_NoLock(const TArray<int32>& InPermutationIndices, const FRigVMRegistryHandle& InRegistry) const;`
- L280 _public prototype_ `TArray<FString> GetSupportedTypeStrings(const TArray<int32>& InPermutationIndices = TArray<int32>()) const;` — returns an array of all supported types as strings. this is used for automated testing only.
- L281 _public prototype_ `TArray<FString> GetSupportedTypeStrings_NoLock(const TArray<int32>& InPermutationIndices, const FRigVMRegistryHandle& InRegistry) const;`
- L284 _public prototype_ `bool IsSingleton(const TArray<int32>& InPermutationIndices = TArray<int32>()) const;` — returns true if an argument is singleton (same type for all variants)
- L285 _public prototype_ `bool IsSingleton_NoLock(const TArray<int32>& InPermutationIndices, const FRigVMRegistryHandle& InRegistry) const;`
- L288 _public prototype_ `bool IsExecute() const;` — returns true if this argument is an execute
- L289 _public prototype_ `bool IsExecute_NoLock(const FRigVMRegistryHandle& InRegistry) const;`
- L292 _public prototype_ `EArrayType GetArrayType() const;` — returns true if the argument uses an array container
- L293 _public prototype_ `EArrayType GetArrayType_NoLock(const FRigVMRegistryHandle& InRegistry) const;`
- L299 _public prototype_ `const TArray<int32>& GetPermutations(const TRigVMTypeIndex InType) const;` — Get the map of types to permutation indices
- L300 _public prototype_ `const TArray<int32>& GetPermutations_NoLock(const TRigVMTypeIndex InType, const FRigVMRegistryHandle& InRegistry) const;`
- L301 _public prototype_ `void InvalidatePermutations(const TRigVMTypeIndex InType);`
- L306 _protected member_ `int32 Index = INDEX_NONE;`
- L307 _protected member_ `FName Name = NAME_None;`
- L308 _protected member_ `ERigVMPinDirection Direction = ERigVMPinDirection::IO;`
- L310 _protected member_ `TArray<TRigVMTypeIndex> TypeIndices;`
- L312 _protected member_ `mutable TMap<TRigVMTypeIndex, TArray<int32>> TypeToPermutations;`
- L315 _protected member_ `bool bUseCategories = false;`
- L316 _protected member_ `TArray<ETypeCategory> TypeCategories;`
- L317 _protected member_ `TFunction<bool(const TRigVMTypeIndex&, const FRigVMRegistryHandle&)> FilterType;`
- L318 _protected member_ `mutable TOptional<EArrayType> CachedArrayType;`
- L321 _protected prototype_ `FRigVMTemplateArgument(FProperty* InProperty, FRigVMRegistryHandle& InRegistry);` — constructor from a property. this forces the type to be created
- L324 _protected prototype_ `static FRigVMTemplateArgument Make(FProperty* InProperty);` — static make function using a lock to create it
- L327 _protected prototype_ `static FRigVMTemplateArgument Make_NoLock(FProperty* InProperty);` — static make function using a lock to create it
- L328 _protected prototype_ `static FRigVMTemplateArgument Make_NoLock(FProperty* InProperty, FRigVMRegistryHandle& InRegistry);`
- L330 _protected prototype_ `void EnsureValidExecuteType_NoLock(const FRigVMRegistryHandle& InRegistry);`
- L333 _protected prototype_ `void UpdateTypeToPermutationsSlow(const FRigVMRegistryHandle& InRegistry);`

#### enum `FRigVMTemplateArgument::EArrayType`  
`enum EArrayType`  
_L172-179_
- L174 _public enumerator_ `EArrayType_SingleValue`
- L175 _public enumerator_ `EArrayType_ArrayValue`
- L176 _public enumerator_ `EArrayType_ArrayArrayValue`
- L177 _public enumerator_ `EArrayType_Mixed`
- L178 _public enumerator_ `EArrayType_Invalid`

#### enum `FRigVMTemplateArgument::ETypeCategory`  
`enum ETypeCategory : uint8`  
_L181-205_
- L183 _public enumerator_ `ETypeCategory_Execute`
- L184 _public enumerator_ `ETypeCategory_SingleAnyValue`
- L185 _public enumerator_ `ETypeCategory_ArrayAnyValue`
- L186 _public enumerator_ `ETypeCategory_ArrayArrayAnyValue`
- L187 _public enumerator_ `ETypeCategory_SingleSimpleValue`
- L188 _public enumerator_ `ETypeCategory_ArraySimpleValue`
- L189 _public enumerator_ `ETypeCategory_ArrayArraySimpleValue`
- L190 _public enumerator_ `ETypeCategory_SingleMathStructValue`
- L191 _public enumerator_ `ETypeCategory_ArrayMathStructValue`
- L192 _public enumerator_ `ETypeCategory_ArrayArrayMathStructValue`
- L193 _public enumerator_ `ETypeCategory_SingleScriptStructValue`
- L194 _public enumerator_ `ETypeCategory_ArrayScriptStructValue`
- L195 _public enumerator_ `ETypeCategory_ArrayArrayScriptStructValue`
- L196 _public enumerator_ `ETypeCategory_SingleEnumValue`
- L197 _public enumerator_ `ETypeCategory_ArrayEnumValue`
- L198 _public enumerator_ `ETypeCategory_ArrayArrayEnumValue`
- L199 _public enumerator_ `ETypeCategory_SingleObjectValue`
- L200 _public enumerator_ `ETypeCategory_ArrayObjectValue`
- L201 _public enumerator_ `ETypeCategory_ArrayArrayObjectValue`
- L202 _public enumerator_ `ETypeCategory_Invalid`
- L204 _public enumerator_ `ETypeCategory_Count`

#### struct `FRigVMTemplateArgument::CategoryViews`  
`struct CategoryViews`  
_L346-375_
- L348 _public prototype_ `CategoryViews() = delete;`
- L349 _public prototype_ `CategoryViews(const TArray<ETypeCategory>& InCategories, const FRigVMRegistryHandle& InRegistry);`
- L351 _public prototype_ `void ForEachType(TFunction<bool(const TRigVMTypeIndex InType)>&& InCallback) const;`
- L353 _public prototype_ `TRigVMTypeIndex GetTypeIndex(int32 InIndex) const;`
- L355 _public prototype_ `int32 FindIndex(const TRigVMTypeIndex InTypeIndex) const;`
- L358 _public function_ `template <typename Predicate> int32 IndexOfByPredicate(Predicate Pred) const`
- L374 _private member_ `TArray<TArrayView<const TRigVMTypeIndex>, TInlineAllocator<(uint32)ETypeCategory::ETypeCategory_Count>> Types;`

#### struct `FRigVMTemplateArgumentInfo`  
`struct FRigVMTemplateArgumentInfo`  
_L382-417_
- L386 _public typedef_ `using ArgumentCallback = TFunction<FRigVMTemplateArgument(const FName , ERigVMPinDirection , const FRigVMRegistryHandle& )>;`
- L387 _public typedef_ `using TypeFilterCallback = TFunction<bool(const TRigVMTypeIndex& , const FRigVMRegistryHandle& )>;`
- L389 _public member_ `FName Name = NAME_None;`
- L390 _public member_ `ERigVMPinDirection Direction = ERigVMPinDirection::Invalid;`
- L391 _public function_ `ArgumentCallback FactoryCallback = [](const FName, ERigVMPinDirection, const FRigVMRegistryHandle&)`
- L391 _public member_ `ArgumentCallback FactoryCallback = [](const FName, ERigVMPinDirection, const FRigVMRegistryHandle&) { return FRigVMTemplateArgument(); };`
- L392 _public member_ `TArray<TRigVMTypeIndex> TypeIndices;`
- L394 _public prototype_ `FRigVMTemplateArgumentInfo(const FName InName, ERigVMPinDirection InDirection, TRigVMTypeIndex InTypeIndex);`
- L395 _public prototype_ `FRigVMTemplateArgumentInfo(const FName InName, ERigVMPinDirection InDirection, const TArray<TRigVMTypeIndex>& InTypeIndices);`
- L396 _public prototype_ `FRigVMTemplateArgumentInfo(const FName InName, ERigVMPinDirection InDirection, const TArray<FRigVMTemplateArgument::ETypeCategory>& InTypeCategories, TypeFilterCallback InTypeFilter = nullptr);`
- L397 _public prototype_ `FRigVMTemplateArgumentInfo(const FName InName, ERigVMPinDirection InDirection);`
- L398 _public prototype_ `FRigVMTemplateArgumentInfo(const FName InName, ERigVMPinDirection InDirection, ArgumentCallback&& InCallback);`
- L400 _public prototype_ `static FRigVMTemplateArgumentInfo MakeFlattenedFromTypeIndices(const FName InName, ERigVMPinDirection InDirection, const TArray<TRigVMTypeIndex>& InTypeIndices);`
- L402 _public prototype_ `FRigVMTemplateArgument GetArgument() const;`
- L403 _public prototype_ `FRigVMTemplateArgument GetArgument_NoLock(const FRigVMRegistryHandle& InRegistry) const;`
- L405 _public prototype_ `static FName ComputeTemplateNotation( const FName InTemplateName, const TArray<FRigVMTemplateArgumentInfo>& InInfos);`
- L409 _public prototype_ `static TArray<TRigVMTypeIndex> GetTypesFromCategories( const TArray<FRigVMTemplateArgument::ETypeCategory>& InTypeCategories, const FRigVMTemplateArgument::FTypeFilter& InTypeFilter = {});`
- L413 _public prototype_ `static TArray<TRigVMTypeIndex> GetTypesFromCategories_NoLock( const TArray<FRigVMTemplateArgument::ETypeCategory>& InTypeCategories, const FRigVMTemplateArgument::FTypeFilter& InTypeFilter, const FRigVMRegistryHandle& InRegistry);`

#### struct `FRigVMTemplate`  
`struct FRigVMTemplate`  
_L425-662_
- desc: The template is used to group multiple rigvm functions that share the same notation. Templates can then be used to build polymorphic nodes (RigVMTemplateNode) that can take on any of the permutations supported by the template.
- L429 _public typedef_ `typedef FRigVMTemplateTypeMap FTypeMap;`
- L430 _public typedef_ `typedef TPair<FName, TRigVMTypeIndex> FTypePair;`
- L433 _public prototype_ `FRigVMTemplate();` — Default constructor
- L436 _public prototype_ `bool IsValid() const;` — returns true if this is a valid template
- L439 _public prototype_ `const FName& GetNotation() const;` — Returns the notation of this template
- L442 _public prototype_ `FName GetName() const;` — Returns the name of the template
- L445 _public prototype_ `FName GetNodeName() const;` — Returns the name to use for a node
- L448 _public prototype_ `bool Merge(const FRigVMTemplate& InOther, const FRigVMRegistryHandle& InRegistry);` — returns true if this template can merge another one
- L451 _public function_ `int32 NumArguments() const` — returns the number of args of this template
- L454 _public function_ `const FRigVMTemplateArgument* GetArgument(int32 InIndex) const` — returns an argument for a given index
- L457 _public prototype_ `const FRigVMTemplateArgument* FindArgument(const FName& InArgumentName) const;` — returns an argument given a name (or nullptr)
- L460 _public prototype_ `int32 NumExecuteArguments(const FRigVMDispatchContext& InContext) const;` — returns the number of args of this template
- L463 _public prototype_ `const FRigVMExecuteArgument* GetExecuteArgument(int32 InIndex, const FRigVMDispatchContext& InContext) const;` — returns an argument for a given index
- L466 _public prototype_ `const FRigVMExecuteArgument* FindExecuteArgument(const FName& InArgumentName, const FRigVMDispatchContext& InContext) const;` — returns an argument given a name (or nullptr)
- L467 _public prototype_ `const FRigVMExecuteArgument* FindExecuteArgument_NoLock(const FName& InArgumentName, const FRigVMDispatchContext& InContext, const FRigVMRegistryHandle& InRegistry) const;`
- L470 _public prototype_ `const UScriptStruct* GetExecuteContextStruct() const;` — returns the top level execute context struct this template uses
- L471 _public prototype_ `const UScriptStruct* GetExecuteContextStruct_NoLock(const FRigVMRegistryHandle& InRegistry) const;`
- L474 _public prototype_ `bool SupportsExecuteContextStruct(const UScriptStruct* InExecuteContextStruct) const;` — returns true if this template supports a given execute context struct
- L475 _public prototype_ `bool SupportsExecuteContextStruct_NoLock(const UScriptStruct* InExecuteContextStruct, const FRigVMRegistryHandle& InRegistry) const;`
- L479 _public prototype_ `bool ArgumentSupportsTypeIndex(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, TRigVMTypeIndex* OutTypeIndex = nullptr) const;` — returns true if a given arg supports a type
- L483 _public prototype_ `int32 NumPermutations() const;` — returns the number of permutations supported by this template
- L484 _public function_ `int32 NumPermutations_NoLock(const FRigVMRegistryHandle& InRegistry) const`
- L487 _public prototype_ `const FRigVMFunction* GetPrimaryPermutation() const;` — returns the first / primary permutation of the template
- L488 _public prototype_ `const FRigVMFunction* GetPrimaryPermutation_NoLock(const FRigVMRegistryHandle& InRegistry) const;`
- L491 _public prototype_ `const FRigVMFunction* GetPermutation(int32 InIndex) const;` — returns a permutation given an index
- L492 _public prototype_ `const FRigVMFunction* GetPermutation_NoLock(int32 InIndex, const FRigVMRegistryHandle& InRegistry) const;`
- L495 _public prototype_ `const FRigVMFunction* GetOrCreatePermutation(int32 InIndex);` — returns a permutation given an index and creates it using the backing factory if needed
- L496 _public prototype_ `const FRigVMFunction* GetOrCreatePermutation_NoLock(int32 InIndex, FRigVMRegistryHandle& InRegistry);`
- L499 _public prototype_ `bool ContainsPermutation(const FRigVMFunction* InPermutation) const;` — returns true if a given function is a permutation of this template
- L500 _public prototype_ `bool ContainsPermutation_NoLock(const FRigVMFunction* InPermutation, const FRigVMRegistryHandle& InRegistry) const;`
- L503 _public prototype_ `int32 FindPermutation(const FRigVMFunction* InPermutation) const;` — returns the index of the permutation within the template of a given function (or INDEX_NONE)
- L504 _public prototype_ `int32 FindPermutation_NoLock(const FRigVMFunction* InPermutation, const FRigVMRegistryHandle& InRegistry) const;`
- L507 _public prototype_ `int32 FindPermutation(const FTypeMap& InTypes) const;` — returns the index of the permutation within the template of a given set of types
- L508 _public prototype_ `int32 FindPermutation_NoLock(const FTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const;`
- L511 _public prototype_ `bool FullyResolve(FTypeMap& InOutTypes, int32& OutPermutationIndex) const;` — returns true if the template was able to resolve to single permutation
- L512 _public prototype_ `bool FullyResolve_NoLock(FTypeMap& InOutTypes, int32& OutPermutationIndex, const FRigVMRegistryHandle& InRegistry) const;`
- L515 _public prototype_ `bool Resolve(FTypeMap& InOutTypes, TArray<int32> & OutPermutationIndices, bool bAllowFloatingPointCasts) const;` — returns true if the template was able to resolve to at least one permutation
- L516 _public prototype_ `bool Resolve_NoLock(FTypeMap& InOutTypes, TArray<int32>& OutPermutationIndices, bool bAllowFloatingPointCasts, const FRigVMRegistryHandle& InRegistry) const;`
- L520 _public prototype_ `uint32 GetTypesHashFromTypes(const FTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const;` — Will return the hash of the input type map, if it is a valid type map. Otherwise, will return 0. It is only a valid type map if it includes all arguments, and non of the types is a wildcard.
- L523 _public prototype_ `bool ContainsPermutation(const FTypeMap& InTypes) const;` — returns true if the template was able to resolve to at least one permutation
- L524 _public prototype_ `bool ContainsPermutation_NoLock(const FTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const;`
- L527 _public prototype_ `bool ResolveArgument(const FName& InArgumentName, const TRigVMTypeIndex InTypeIndex, FTypeMap& InOutTypes) const;` — returns true if the template can resolve an argument to a new type
- L528 _public prototype_ `bool ResolveArgument_NoLock(const FName& InArgumentName, const TRigVMTypeIndex InTypeIndex, FTypeMap& InOutTypes, const FRigVMRegistryHandle& InRegistry) const;`
- L531 _public prototype_ `FRigVMTemplateTypeMap GetTypesForPermutation(const int32 InPermutationIndex) const;` — returns the types for a specific permutation
- L532 _public prototype_ `FRigVMTemplateTypeMap GetTypesForPermutation_NoLock(const int32 InPermutationIndex, const FRigVMRegistryHandle& InRegistry) const;`
- L535 _public prototype_ `static bool IsValidArgumentForTemplate(const ERigVMPinDirection InDirection);` — returns true if a given argument is valid for a template
- L538 _public prototype_ `static const FString& GetDirectionPrefix(const ERigVMPinDirection InDirection);` — returns the prefix for an argument in the notation
- L541 _public prototype_ `static FString GetArgumentNotation(const FName InName, const ERigVMPinDirection InDirection);` — returns the notation of an argument
- L544 _public prototype_ `void ComputeNotationFromArguments(const FString& InTemplateName);` — recomputes the notation from its arguments
- L547 _public prototype_ `static TArray<UStruct*> GetSuperStructs(UStruct* InStruct, bool bIncludeLeaf = true);` — returns an array of structs in the inheritance order of a given struct
- L550 _public prototype_ `FTypeMap GetArgumentTypesFromString(const FString& InTypeString, const FRigVMUserDefinedTypeResolver* InTypeResolver = nullptr) const;` — converts the types provided by a string (like "A:float,B:int32") into a type map
- L553 _public prototype_ `static FString GetStringFromArgumentTypes(const FTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry);` — converts the types provided to a string (like "A:float,B:int32")
- L558 _public prototype_ `FLinearColor GetColor(const TArray<int32>& InPermutationIndices = TArray<int32>()) const;` — Returns the color based on the permutation's metadata
- L561 _public prototype_ `FText GetTooltipText(const TArray<int32>& InPermutationIndices = TArray<int32>()) const;` — Returns the tooltip based on the permutation's metadata
- L564 _public prototype_ `FText GetDisplayNameForArgument(const FName& InArgumentName, const TArray<int32>& InPermutationIndices = TArray<int32>()) const;` — Returns the display name text for an argument
- L567 _public prototype_ `FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey, const TArray<int32>& InPermutationIndices = TArray<int32>()) const;` — Returns meta data on the property of the permutations
- L569 _public prototype_ `FString GetCategory() const;`
- L570 _public prototype_ `FString GetKeywords() const;`
- L576 _public prototype_ `bool UpdateAllArgumentTypesSlow(FRigVMRegistryHandle& InRegistry);` — Updates the template's argument types. This only affects templates which have category based arguments and will resolve the other arguments to the expected types.
- L579 _public prototype_ `bool HandlePropagatedArgumentType(const TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry);` — Updates the template's argument types by adding a single new type
- L582 _public prototype_ `void HandleTypeRemoval(TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry);` — Invalidates template permutations whenever a type such as a user defined struct is removed
- L586 _public function_ `FRigVMTemplate_NewArgumentTypeDelegate& OnNewArgumentType()` — Returns the delegate to be able to react to type changes dynamically This delegate is deprecated
- L589 _public prototype_ `const FRigVMDispatchFactory* GetDispatchFactory() const;` — Returns the factory this template was created by
- L592 _public prototype_ `const FRigVMDispatchFactory* GetDispatchFactory_NoLock(const FRigVMRegistryHandle& InRegistry) const;` — Returns the factory this template was created by
- L595 _public function_ `bool UsesDispatch() const` — Returns true if this template is backed by a dispatch factory
- L600 _public prototype_ `void RecomputeTypesHashToPermutations(const FRigVMRegistryHandle& InRegistry);`
- L601 _public prototype_ `void RecomputeTypesHashToPermutations(const TArray<FRigVMTypeCacheScope_NoLock>& InTypeCaches, const FRigVMRegistryHandle& InRegistry);`
- L603 _public prototype_ `void UpdateTypesHashToPermutation(const int32 InPermutation, const FRigVMRegistryHandle& InRegistry);`
- L608 _public prototype_ `TArray<FRigVMTemplateArgumentInfo> GetFlattenedArgumentInfos_NoLock(FRigVMRegistryHandle& InRegistry) const;`
- L609 _public prototype_ `TArray<FRigVMTemplateArgumentInfo> GetFlattenedArgumentInfosForFunctions_NoLock(const TArray<const FRigVMFunction*>& InFunctions, FRigVMRegistryHandle& InRegistry) const;`
- L612 _public prototype_ `FRigVMTemplate(UScriptStruct* InStruct, const FString& InTemplateName, int32 InFunctionIndex, FRigVMRegistryHandle& InRegistry);` — Constructor from a struct, a template name and a function index
- L615 _public prototype_ `FRigVMTemplate(const FName& InTemplateName, const TArray<FRigVMTemplateArgumentInfo>& InInfos, const FRigVMRegistryHandle& InRegistry);` — Constructor from a template name and argument infos
- L619 _private prototype_ `static FLinearColor GetColorFromMetadata(FString InMetadata);`
- L621 _private prototype_ `void UpdateTypesIndicesToPermutationIndices(int32 InPermutationIndex, const FRigVMRegistryHandle& InRegistry);`
- L622 _private function_ `void InvalidateHash()`
- L623 _private prototype_ `const TArray<FRigVMExecuteArgument>& GetExecuteArguments(const FRigVMDispatchContext& InContext) const;`
- L624 _private prototype_ `const TArray<FRigVMExecuteArgument>& GetExecuteArguments_NoLock(const FRigVMDispatchContext& InContext, const FRigVMRegistryHandle& InRegistry) const;`
- L626 _private prototype_ `FTypeMap GetArgumentTypesFromString_NoLock(const FString& InTypeString, const FRigVMUserDefinedTypeResolver* InTypeResolver, FRigVMRegistryHandle& InRegistry) const;`
- L628 _private prototype_ `uint32 ComputeTypeHash(const FRigVMRegistryHandle& InRegistry) const;`
- L630 _private prototype_ `bool UpdateArgumentTypes_Impl( const FRigVMTemplateArgument& InPrimaryArgument, const TRigVMTypeIndex InPrimaryTypeIndex, FRigVMRegistryHandle& InRegistry, const FRigVMDispatchFactory* InFactory, TArray<FRigVMTemplateTypeMap, TInlineAllocator<1>>& InOutTypesArray);`
- L639 _private prototype_ `bool IsIgnoredType(const TRigVMTypeIndex& InTypeIndex) const;` — returns true if this is a type which should be ignored by this template since it got removed by unloading a plugin
- L640 _private prototype_ `bool IsIgnoredType(const FName& InTypeName) const;`
- L642 _private member_ `int32 Index;`
- L643 _private member_ `FName Notation;`
- L644 _private member_ `TArray<FRigVMTemplateArgument> Arguments;`
- L645 _private member_ `mutable TArray<FRigVMExecuteArgument> ExecuteArguments;`
- L646 _private member_ `TArray<int32> Permutations;`
- L647 _private member_ `TMap<uint32, int32> TypesHashToPermutation;`
- L648 _private member_ `TMap<TRigVMTypeIndex, TArray<int32>> TypesIndicesToPermutationIndices;`
- L649 _private member_ `TArray<int32> RemovedPermutationIndices;`
- L650 _private member_ `mutable uint32 Hash;`
- L651 _private member_ `FRigVMRegistry_NoLock* OwnerRegistry;`
- L653 _private member_ `FRigVMTemplateDelegates Delegates;`
- L655 _private member_ `TArray<TRigVMTypeIndex> TypeIndicesToIgnore;`
- L656 _private member_ `TArray<FName> TypeNamesToIgnore;`

#### class `FRigVMTypeCacheScope_NoLock`  
`class FRigVMTypeCacheScope_NoLock`  
_L664-685_
- L667 _public prototype_ `FRigVMTypeCacheScope_NoLock();`
- L668 _public prototype_ `FRigVMTypeCacheScope_NoLock(const FRigVMRegistryHandle& InRegistry, const FRigVMTemplateArgument& InArgument);`
- L669 _public prototype_ `~FRigVMTypeCacheScope_NoLock();`
- L671 _public function_ `bool IsValid() const`
- L672 _public prototype_ `const FRigVMTypeCacheScope_NoLock& UpdateIfRequired(const FRigVMRegistryHandle& InRegistry, const FRigVMTemplateArgument& InArgument);`
- L673 _public prototype_ `int32 GetNumTypes_NoLock() const;`
- L674 _public prototype_ `TRigVMTypeIndex GetTypeIndex_NoLock(int32 InIndex) const;`
- L678 _private prototype_ `void UpdateTypesIfRequired() const;`
- L680 _private member_ `FRigVMRegistry_NoLock* Registry;`
- L681 _private member_ `const FRigVMTemplateArgument* Argument;`
- L682 _private member_ `bool bShouldCopyTypes;`
- L683 _private member_ `mutable TOptional<int32> NumTypes;`
- L684 _private member_ `mutable TOptional<TArray<TRigVMTypeIndex>> Types;`

#### Free symbols / members of external scopes

- L34 _typedef_ `typedef TMap<FName, TRigVMTypeIndex> FRigVMTemplateTypeMap;`
- L37 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FRigVMTemplateTypeMap, FRigVMTemplate_NewArgumentTypeDelegate, const FName& , TRigVMTypeIndex , const FRigVMRegistryHandle& );` — FRigVMTemplate_NewArgumentTypeDelegate is deprecated, use FRigVMTemplate_GetPermutationsFromArgumentTypeDelegate
- L37 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FRigVMTemplateTypeMap, FRigVMTemplate_NewArgumentTypeDelegate, const FName& , TRigVMTypeIndex , const FRigVMRegistryHandle& );` — FRigVMTemplate_NewArgumentTypeDelegate is deprecated, use FRigVMTemplate_GetPermutationsFromArgumentTypeDelegate
- L38 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FRigVMDispatchFactory*, FRigVMTemplate_GetDispatchFactoryDelegate, const FRigVMRegistryHandle& );`
- L38 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FRigVMDispatchFactory*, FRigVMTemplate_GetDispatchFactoryDelegate, const FRigVMRegistryHandle& );`
- L116 _function_ `friend inline uint32 GetTypeHash(const FRigVMTemplateArgumentType& InType)`
- L170 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FTypeFilter, const TRigVMTypeIndex&, const FRigVMRegistryHandle&);`
- L254 _function_ `` (scope `FRigVMTemplateArgument::IndexOfByPredicate`)

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMTrait.h` (Public)


#### struct `FRigVMTrait`  
`struct FRigVMTrait : public FRigVMStruct`  
_L21-75_
- reflection: `USTRUCT()`
- inherits: `FRigVMStruct`
- desc: The base class for all RigVM traits.
- L27 _public function_ `FRigVMTrait()`
- L30 _public prototype_ `virtual ~FRigVMTrait() = default;`
- L33 _public function_ `FString GetName() const` — returns the name of the trait (the instance of it on the node)
- L36 _public function_ `virtual FString GetDisplayName() const` — returns the display name of the trait
- L44 _public function_ `virtual bool CanBeAddedToNode(URigVMNode* InNode, FString* OutFailureReason) const` — returns true if this trait can be added to a given node
- L47 _public function_ `virtual void OnTraitAdded(URigVMController* InController, URigVMNode* InNode)` — allows the trait to react when added to a node
- L50 _public function_ `virtual void GetProgrammaticPins(URigVMController* InController, int32 InParentPinIndex, const URigVMPin* InTraitPin, const FString& InDefaultValue, struct FRigVMPinInfoArray& OutPinArray) const` — allows the trait to return dynamic pins (parent pin index must be INDEX_NONE or point to a valid index of the parent pin in the OutPinArray)
- L52 _public function_ `virtual UScriptStruct* GetTraitSharedDataStruct() const`
- L54 _public function_ `virtual bool ShouldCreatePinForProperty(const FProperty* InProperty) const override`
- L63 _public function_ `virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const`
- L70 _private member_ `FString Name;` — `UPROPERTY()` — The name of the trait on the node

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMTraitScope.h` (Public)


#### class `FRigVMTraitScope`  
`class FRigVMTraitScope`  
_L12-94_
- L15 _public function_ `FRigVMTraitScope() : Trait(nullptr) , ScriptStruct(nullptr)`
- L21 _public function_ `FRigVMTraitScope(FRigVMTrait* InTrait, const UScriptStruct* InScriptStruct) : Trait(InTrait) , ScriptStruct(InScriptStruct)`
- L27 _public function_ `FRigVMTraitScope(FRigVMTrait* InTrait, const UScriptStruct* InScriptStruct, TConstArrayView<FRigVMMemoryHandle> InAdditionalMemoryHandles) : Trait(InTrait) , ScriptStruct(InScriptStruct) , AdditionalMemoryHandles(InAdditionalMemoryHandles)`
- L34 _public function_ `bool IsValid() const`
- L40 _public function_ `template<typename T> bool IsA() const`
- L46 _public function_ `template<typename T = FRigVMTrait> const T* GetTrait() const`
- L56 _public function_ `template<typename T = FRigVMTrait> const T* GetTraitChecked() const`
- L63 _public function_ `template<typename T = FRigVMTrait> T* GetTrait()`
- L73 _public function_ `template<typename T = FRigVMTrait> T* GetTraitChecked()`
- L79 _public function_ `const UScriptStruct* GetScriptStruct() const`
- L84 _public function_ `TConstArrayView<FRigVMMemoryHandle> GetAdditionalMemoryHandles() const`
- L91 _private member_ `FRigVMTrait* Trait;`
- L92 _private member_ `const UScriptStruct* ScriptStruct;`
- L93 _private member_ `TConstArrayView<FRigVMMemoryHandle> AdditionalMemoryHandles;`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMTraits.h` (Public)


#### struct `CRigVMUStruct`  
`struct CRigVMUStruct`  
_L10-16_
- L13 _public prototype_ `template <typename T> auto Requires(UScriptStruct*& Val) -> decltype( Val = T::StaticStruct() );`

#### struct `CRigVMUClass`  
`struct CRigVMUClass`  
_L18-24_
- L21 _public prototype_ `template <typename T> auto Requires(UClass*& Val) -> decltype( Val = T::StaticClass() );`

#### struct `TRigVMIsBool`  
`template <typename T> struct TRigVMIsBool`  
_L27-30_

#### enum `TRigVMIsBool::(anonymous)`  
`enum`  
_L29-29_

#### enum `TRigVMIsBool::(anonymous)`  
`template <> struct TRigVMIsBool<bool>`  
_L31-31_

#### struct `TRigVMIsBool`  
`template <> struct TRigVMIsBool<bool>`  
_L31-31_

#### struct `TRigVMIsFloat`  
`template <typename T> struct TRigVMIsFloat`  
_L34-37_

#### enum `TRigVMIsFloat::(anonymous)`  
`enum`  
_L36-36_

#### enum `TRigVMIsFloat::(anonymous)`  
`template <> struct TRigVMIsFloat<float>`  
_L38-38_

#### struct `TRigVMIsFloat`  
`template <> struct TRigVMIsFloat<float>`  
_L38-38_

#### struct `TRigVMIsDouble`  
`template <typename T> struct TRigVMIsDouble`  
_L41-44_

#### enum `TRigVMIsDouble::(anonymous)`  
`enum`  
_L43-43_

#### enum `TRigVMIsDouble::(anonymous)`  
`template <> struct TRigVMIsDouble<double>`  
_L45-45_

#### struct `TRigVMIsDouble`  
`template <> struct TRigVMIsDouble<double>`  
_L45-45_

#### struct `TRigVMIsInt32`  
`template <typename T> struct TRigVMIsInt32`  
_L48-51_

#### enum `TRigVMIsInt32::(anonymous)`  
`enum`  
_L50-50_

#### enum `TRigVMIsInt32::(anonymous)`  
`template <> struct TRigVMIsInt32<int32>`  
_L52-52_

#### struct `TRigVMIsInt32`  
`template <> struct TRigVMIsInt32<int32>`  
_L52-52_

#### struct `TRigVMIsName`  
`template <typename T> struct TRigVMIsName`  
_L55-58_

#### enum `TRigVMIsName::(anonymous)`  
`enum`  
_L57-57_

#### enum `TRigVMIsName::(anonymous)`  
`template <> struct TRigVMIsName<FName>`  
_L59-59_

#### struct `TRigVMIsName`  
`template <> struct TRigVMIsName<FName>`  
_L59-59_

#### struct `TRigVMIsString`  
`template <typename T> struct TRigVMIsString`  
_L62-65_

#### enum `TRigVMIsString::(anonymous)`  
`enum`  
_L64-64_

#### enum `TRigVMIsString::(anonymous)`  
`template <> struct TRigVMIsString<FString>`  
_L66-66_

#### struct `TRigVMIsString`  
`template <> struct TRigVMIsString<FString>`  
_L66-66_

#### struct `TRigVMIsBaseStructure`  
`template <typename T> struct TRigVMIsBaseStructure`  
_L69-72_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`enum`  
_L71-71_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FRotator>`  
_L74-74_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FRotator>`  
_L74-74_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FRotator>`  
_L75-75_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FRotator>`  
_L75-75_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FRotator>`  
_L76-76_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FRotator>`  
_L76-76_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FLinearColor>`  
_L78-78_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FLinearColor>`  
_L78-78_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FColor>`  
_L80-80_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FColor>`  
_L80-80_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FPlane>`  
_L82-82_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FPlane>`  
_L82-82_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FVector>`  
_L84-84_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FVector>`  
_L84-84_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FVector2D>`  
_L86-86_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FVector2D>`  
_L86-86_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FVector4>`  
_L88-88_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FVector4>`  
_L88-88_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FRandomStream>`  
_L90-90_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FRandomStream>`  
_L90-90_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FGuid>`  
_L92-92_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FGuid>`  
_L92-92_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FBox2D>`  
_L94-94_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FBox2D>`  
_L94-94_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FFallbackStruct>`  
_L96-96_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FFallbackStruct>`  
_L96-96_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FFloatRangeBound>`  
_L98-98_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FFloatRangeBound>`  
_L98-98_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FFloatRange>`  
_L100-100_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FFloatRange>`  
_L100-100_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FInt32RangeBound>`  
_L102-102_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FInt32RangeBound>`  
_L102-102_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FInt32Range>`  
_L104-104_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FInt32Range>`  
_L104-104_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FFloatInterval>`  
_L106-106_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FFloatInterval>`  
_L106-106_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FInt32Interval>`  
_L108-108_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FInt32Interval>`  
_L108-108_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FFrameNumber>`  
_L110-110_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FFrameNumber>`  
_L110-110_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FSoftObjectPath>`  
_L112-112_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FSoftObjectPath>`  
_L112-112_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FSoftClassPath>`  
_L114-114_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FSoftClassPath>`  
_L114-114_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FPrimaryAssetType>`  
_L116-116_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FPrimaryAssetType>`  
_L116-116_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FPrimaryAssetId>`  
_L118-118_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FPrimaryAssetId>`  
_L118-118_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FDateTime>`  
_L120-120_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FDateTime>`  
_L120-120_

#### enum `TRigVMIsBaseStructure::(anonymous)`  
`template<> struct TRigVMIsBaseStructure<FPolyglotTextData>`  
_L122-122_

#### struct `TRigVMIsBaseStructure`  
`template<> struct TRigVMIsBaseStructure<FPolyglotTextData>`  
_L122-122_

#### Free symbols / members of external scopes

- L29 _enumerator_ `enum { Value = false };` (scope `TRigVMIsBool::__anon454c8e7f0103`)
- L31 _enumerator_ `template <> struct TRigVMIsBool<bool> { enum { Value = true }; }; template <typename T> struct TRigVMIsFloat { enum { Value = false }; }; template <> struct TRigVMIsFloat<float> { enum { Value = true }; };` (scope `TRigVMIsBool::__anon454c8e7f0203`)
- L36 _enumerator_ `enum { Value = false };` (scope `TRigVMIsFloat::__anon454c8e7f0303`)
- L38 _enumerator_ `template <> struct TRigVMIsFloat<float> { enum { Value = true }; }; template <typename T> struct TRigVMIsDouble { enum { Value = false }; }; template <> struct TRigVMIsDouble<double> { enum { Value = true }; };` (scope `TRigVMIsFloat::__anon454c8e7f0403`)
- L43 _enumerator_ `enum { Value = false };` (scope `TRigVMIsDouble::__anon454c8e7f0503`)
- L45 _enumerator_ `template <> struct TRigVMIsDouble<double> { enum { Value = true }; }; template <typename T> struct TRigVMIsInt32 { enum { Value = false }; }; template <> struct TRigVMIsInt32<int32> { enum { Value = true }; };` (scope `TRigVMIsDouble::__anon454c8e7f0603`)
- L50 _enumerator_ `enum { Value = false };` (scope `TRigVMIsInt32::__anon454c8e7f0703`)
- L52 _enumerator_ `template <> struct TRigVMIsInt32<int32> { enum { Value = true }; }; template <typename T> struct TRigVMIsName { enum { Value = false }; }; template <> struct TRigVMIsName<FName> { enum { Value = true }; };` (scope `TRigVMIsInt32::__anon454c8e7f0803`)
- L57 _enumerator_ `enum { Value = false };` (scope `TRigVMIsName::__anon454c8e7f0903`)
- L59 _enumerator_ `template <> struct TRigVMIsName<FName> { enum { Value = true }; }; template <typename T> struct TRigVMIsString { enum { Value = false }; }; template <> struct TRigVMIsString<FString> { enum { Value = true }; };` (scope `TRigVMIsName::__anon454c8e7f0a03`)
- L64 _enumerator_ `enum { Value = false };` (scope `TRigVMIsString::__anon454c8e7f0b03`)
- L66 _enumerator_ `template <> struct TRigVMIsString<FString> { enum { Value = true }; }; template <typename T> struct TRigVMIsBaseStructure { enum { Value = false }; };` (scope `TRigVMIsString::__anon454c8e7f0c03`)
- L71 _enumerator_ `enum { Value = false };` (scope `TRigVMIsBaseStructure::__anon454c8e7f0d03`)
- L74 _enumerator_ `template<> struct TRigVMIsBaseStructure<FRotator> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FQuat> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FTransform> { enum { Value = true }; }; struct FLinearColor; template<> struct TRigVMIsBaseStructure<FLinearColor> { enum { Value = true }; }; struct FColor; template<> struct TRigVMIsBaseStructure<FColor> { enum { Value = true }; };` (scope `TRigVMIsBaseStructure::__anon454c8e7f0e03`)
- L75 _enumerator_ `template<> struct TRigVMIsBaseStructure<FQuat> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FTransform> { enum { Value = true }; }; struct FLinearColor; template<> struct TRigVMIsBaseStructure<FLinearColor> { enum { Value = true }; }; struct FColor; template<> struct TRigVMIsBaseStructure<FColor> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FPlane> { enum { Value = true }; };` (scope `TRigVMIsBaseStructure::__anon454c8e7f0f03`)
- L76 _enumerator_ `template<> struct TRigVMIsBaseStructure<FTransform> { enum { Value = true }; }; struct FLinearColor; template<> struct TRigVMIsBaseStructure<FLinearColor> { enum { Value = true }; }; struct FColor; template<> struct TRigVMIsBaseStructure<FColor> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FPlane> { enum { Value = true }; };` (scope `TRigVMIsBaseStructure::__anon454c8e7f1003`)
- L78 _enumerator_ `template<> struct TRigVMIsBaseStructure<FLinearColor> { enum { Value = true }; }; struct FColor; template<> struct TRigVMIsBaseStructure<FColor> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FPlane> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FVector> { enum { Value = true }; };` (scope `TRigVMIsBaseStructure::__anon454c8e7f1103`)
- L80 _enumerator_ `template<> struct TRigVMIsBaseStructure<FColor> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FPlane> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FVector> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FVector2D> { enum { Value = true }; };` (scope `TRigVMIsBaseStructure::__anon454c8e7f1203`)
- L82 _enumerator_ `template<> struct TRigVMIsBaseStructure<FPlane> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FVector> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FVector2D> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FVector4> { enum { Value = true }; }; struct FRandomStream;` (scope `TRigVMIsBaseStructure::__anon454c8e7f1303`)
- L84 _enumerator_ `template<> struct TRigVMIsBaseStructure<FVector> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FVector2D> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FVector4> { enum { Value = true }; }; struct FRandomStream; template<> struct TRigVMIsBaseStructure<FRandomStream> { enum { Value = true }; }; struct FGuid;` (scope `TRigVMIsBaseStructure::__anon454c8e7f1403`)
- L86 _enumerator_ `template<> struct TRigVMIsBaseStructure<FVector2D> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FVector4> { enum { Value = true }; }; struct FRandomStream; template<> struct TRigVMIsBaseStructure<FRandomStream> { enum { Value = true }; }; struct FGuid; template<> struct TRigVMIsBaseStructure<FGuid> { enum { Value = true }; };` (scope `TRigVMIsBaseStructure::__anon454c8e7f1503`)
- L88 _enumerator_ `template<> struct TRigVMIsBaseStructure<FVector4> { enum { Value = true }; }; struct FRandomStream; template<> struct TRigVMIsBaseStructure<FRandomStream> { enum { Value = true }; }; struct FGuid; template<> struct TRigVMIsBaseStructure<FGuid> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FBox2D> { enum { Value = true }; }; struct FFallbackStruct;` (scope `TRigVMIsBaseStructure::__anon454c8e7f1603`)
- L90 _enumerator_ `template<> struct TRigVMIsBaseStructure<FRandomStream> { enum { Value = true }; }; struct FGuid; template<> struct TRigVMIsBaseStructure<FGuid> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FBox2D> { enum { Value = true }; }; struct FFallbackStruct; template<> struct TRigVMIsBaseStructure<FFallbackStruct> { enum { Value = true }; }; struct FFloatRangeBound;` (scope `TRigVMIsBaseStructure::__anon454c8e7f1703`)
- L92 _enumerator_ `template<> struct TRigVMIsBaseStructure<FGuid> { enum { Value = true }; }; template<> struct TRigVMIsBaseStructure<FBox2D> { enum { Value = true }; }; struct FFallbackStruct; template<> struct TRigVMIsBaseStructure<FFallbackStruct> { enum { Value = true }; }; struct FFloatRangeBound; template<> struct TRigVMIsBaseStructure<FFloatRangeBound> { enum { Value = true }; }; struct FFloatRange;` (scope `TRigVMIsBaseStructure::__anon454c8e7f1803`)
- L94 _enumerator_ `template<> struct TRigVMIsBaseStructure<FBox2D> { enum { Value = true }; }; struct FFallbackStruct; template<> struct TRigVMIsBaseStructure<FFallbackStruct> { enum { Value = true }; }; struct FFloatRangeBound; template<> struct TRigVMIsBaseStructure<FFloatRangeBound> { enum { Value = true }; }; struct FFloatRange; template<> struct TRigVMIsBaseStructure<FFloatRange> { enum { Value = true }; }; struct FInt32RangeBound;` (scope `TRigVMIsBaseStructure::__anon454c8e7f1903`)
- L96 _enumerator_ `template<> struct TRigVMIsBaseStructure<FFallbackStruct> { enum { Value = true }; }; struct FFloatRangeBound; template<> struct TRigVMIsBaseStructure<FFloatRangeBound> { enum { Value = true }; }; struct FFloatRange; template<> struct TRigVMIsBaseStructure<FFloatRange> { enum { Value = true }; }; struct FInt32RangeBound; template<> struct TRigVMIsBaseStructure<FInt32RangeBound> { enum { Value = true }; }; struct FInt32Range;` (scope `TRigVMIsBaseStructure::__anon454c8e7f1a03`)
- L98 _enumerator_ `template<> struct TRigVMIsBaseStructure<FFloatRangeBound> { enum { Value = true }; }; struct FFloatRange; template<> struct TRigVMIsBaseStructure<FFloatRange> { enum { Value = true }; }; struct FInt32RangeBound; template<> struct TRigVMIsBaseStructure<FInt32RangeBound> { enum { Value = true }; }; struct FInt32Range; template<> struct TRigVMIsBaseStructure<FInt32Range> { enum { Value = true }; }; struct FFloatInterval;` (scope `TRigVMIsBaseStructure::__anon454c8e7f1b03`)
- L100 _enumerator_ `template<> struct TRigVMIsBaseStructure<FFloatRange> { enum { Value = true }; }; struct FInt32RangeBound; template<> struct TRigVMIsBaseStructure<FInt32RangeBound> { enum { Value = true }; }; struct FInt32Range; template<> struct TRigVMIsBaseStructure<FInt32Range> { enum { Value = true }; }; struct FFloatInterval; template<> struct TRigVMIsBaseStructure<FFloatInterval> { enum { Value = true }; }; struct FInt32Interval;` (scope `TRigVMIsBaseStructure::__anon454c8e7f1c03`)
- L102 _enumerator_ `template<> struct TRigVMIsBaseStructure<FInt32RangeBound> { enum { Value = true }; }; struct FInt32Range; template<> struct TRigVMIsBaseStructure<FInt32Range> { enum { Value = true }; }; struct FFloatInterval; template<> struct TRigVMIsBaseStructure<FFloatInterval> { enum { Value = true }; }; struct FInt32Interval; template<> struct TRigVMIsBaseStructure<FInt32Interval> { enum { Value = true }; }; struct FFrameNumber;` (scope `TRigVMIsBaseStructure::__anon454c8e7f1d03`)
- L104 _enumerator_ `template<> struct TRigVMIsBaseStructure<FInt32Range> { enum { Value = true }; }; struct FFloatInterval; template<> struct TRigVMIsBaseStructure<FFloatInterval> { enum { Value = true }; }; struct FInt32Interval; template<> struct TRigVMIsBaseStructure<FInt32Interval> { enum { Value = true }; }; struct FFrameNumber; template<> struct TRigVMIsBaseStructure<FFrameNumber> { enum { Value = true }; }; struct FSoftObjectPath;` (scope `TRigVMIsBaseStructure::__anon454c8e7f1e03`)
- L106 _enumerator_ `template<> struct TRigVMIsBaseStructure<FFloatInterval> { enum { Value = true }; }; struct FInt32Interval; template<> struct TRigVMIsBaseStructure<FInt32Interval> { enum { Value = true }; }; struct FFrameNumber; template<> struct TRigVMIsBaseStructure<FFrameNumber> { enum { Value = true }; }; struct FSoftObjectPath; template<> struct TRigVMIsBaseStructure<FSoftObjectPath> { enum { Value = true }; }; struct FSoftClassPath;` (scope `TRigVMIsBaseStructure::__anon454c8e7f1f03`)
- L108 _enumerator_ `template<> struct TRigVMIsBaseStructure<FInt32Interval> { enum { Value = true }; }; struct FFrameNumber; template<> struct TRigVMIsBaseStructure<FFrameNumber> { enum { Value = true }; }; struct FSoftObjectPath; template<> struct TRigVMIsBaseStructure<FSoftObjectPath> { enum { Value = true }; }; struct FSoftClassPath; template<> struct TRigVMIsBaseStructure<FSoftClassPath> { enum { Value = true }; }; struct FPrimaryAssetType;` (scope `TRigVMIsBaseStructure::__anon454c8e7f2003`)
- L110 _enumerator_ `template<> struct TRigVMIsBaseStructure<FFrameNumber> { enum { Value = true }; }; struct FSoftObjectPath; template<> struct TRigVMIsBaseStructure<FSoftObjectPath> { enum { Value = true }; }; struct FSoftClassPath; template<> struct TRigVMIsBaseStructure<FSoftClassPath> { enum { Value = true }; }; struct FPrimaryAssetType; template<> struct TRigVMIsBaseStructure<FPrimaryAssetType> { enum { Value = true }; }; struct FPrimaryAssetId;` (scope `TRigVMIsBaseStructure::__anon454c8e7f2103`)
- L112 _enumerator_ `template<> struct TRigVMIsBaseStructure<FSoftObjectPath> { enum { Value = true }; }; struct FSoftClassPath; template<> struct TRigVMIsBaseStructure<FSoftClassPath> { enum { Value = true }; }; struct FPrimaryAssetType; template<> struct TRigVMIsBaseStructure<FPrimaryAssetType> { enum { Value = true }; }; struct FPrimaryAssetId; template<> struct TRigVMIsBaseStructure<FPrimaryAssetId> { enum { Value = true }; }; struct FDateTime;` (scope `TRigVMIsBaseStructure::__anon454c8e7f2203`)
- L114 _enumerator_ `template<> struct TRigVMIsBaseStructure<FSoftClassPath> { enum { Value = true }; }; struct FPrimaryAssetType; template<> struct TRigVMIsBaseStructure<FPrimaryAssetType> { enum { Value = true }; }; struct FPrimaryAssetId; template<> struct TRigVMIsBaseStructure<FPrimaryAssetId> { enum { Value = true }; }; struct FDateTime; template<> struct TRigVMIsBaseStructure<FDateTime> { enum { Value = true }; }; struct FPolyglotTextData;` (scope `TRigVMIsBaseStructure::__anon454c8e7f2303`)
- L116 _enumerator_ `template<> struct TRigVMIsBaseStructure<FPrimaryAssetType> { enum { Value = true }; }; struct FPrimaryAssetId; template<> struct TRigVMIsBaseStructure<FPrimaryAssetId> { enum { Value = true }; }; struct FDateTime; template<> struct TRigVMIsBaseStructure<FDateTime> { enum { Value = true }; }; struct FPolyglotTextData; template<> struct TRigVMIsBaseStructure<FPolyglotTextData> { enum { Value = true }; };` (scope `TRigVMIsBaseStructure::__anon454c8e7f2403`)
- L118 _enumerator_ `template<> struct TRigVMIsBaseStructure<FPrimaryAssetId> { enum { Value = true }; }; struct FDateTime; template<> struct TRigVMIsBaseStructure<FDateTime> { enum { Value = true }; }; struct FPolyglotTextData; template<> struct TRigVMIsBaseStructure<FPolyglotTextData> { enum { Value = true }; };` (scope `TRigVMIsBaseStructure::__anon454c8e7f2503`)
- L120 _enumerator_ `template<> struct TRigVMIsBaseStructure<FDateTime> { enum { Value = true }; }; struct FPolyglotTextData; template<> struct TRigVMIsBaseStructure<FPolyglotTextData> { enum { Value = true }; }; template< typename T` (scope `TRigVMIsBaseStructure::__anon454c8e7f2603`)
- L122 _enumerator_ `template<> struct TRigVMIsBaseStructure<FPolyglotTextData> { enum { Value = true }; }; template< typename T` (scope `TRigVMIsBaseStructure::__anon454c8e7f2703`)
- L130 _function_ `void RigVMInitialize(void* InPtr, int32 InCount = 1)`
- L140 _function_ `void RigVMDestroy(void* InPtr, int32 InCount = 1)`
- L149 _function_ `void RigVMCopy(void* InTargetPtr, const void* InSourcePtr, int32 InCount = 1)`
- L159 _function_ `void RigVMInitialize(void* InPtr, int32 InCount)`
- L175 _function_ `void RigVMDestroy(void* InPtr, int32 InCount)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMTypeIndex.h` (Public)


#### class `TRigVMTypeIndex`  
`class TRigVMTypeIndex`  
_L9-86_
- L17 _public function_ `TRigVMTypeIndex() : Name(NAME_None) , Index(0)` — default constructor provided just to avoid compilation error in your code if you need to represent an invalid type, use INDEX_NONE instead of TRigVMTypeIndex() the reason being that because we typedef int32 to TRigVMTypeIndex, default constructor of TRigVMTypeIndex should be the same as int32, which defaults to 0 and is not an invalid type
- L22 _public function_ `TRigVMTypeIndex(int32 InIndex) : Name(NAME_None) , Index(InIndex)`
- L27 _public function_ `int32 GetIndex() const`
- L28 _public function_ `const FName& GetName() const`
- L30 _public function_ `operator int() const`
- L35 _public function_ `bool operator ==(const TRigVMTypeIndex& Other) const`
- L40 _public function_ `bool operator ==(const int32& Other) const`
- L45 _public function_ `bool operator !=(const TRigVMTypeIndex& Other) const`
- L50 _public function_ `bool operator !=(const int32& Other) const`
- L55 _public function_ `bool operator >(const TRigVMTypeIndex& Other) const`
- L60 _public function_ `bool operator >(const int32& Other) const`
- L65 _public function_ `bool operator <(const TRigVMTypeIndex& Other) const`
- L70 _public function_ `bool operator <(const int32& Other) const`
- L81 _protected member_ `FName Name;`
- L82 _protected member_ `int32 Index;`

#### Free symbols / members of external scopes

- L75 _function_ `friend uint32 GetTypeHash(const TRigVMTypeIndex& InIndex)`
- L88 _typedef_ `typedef int32 TRigVMTypeIndex;`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMUnknownType.h` (Public)


#### struct `FRigVMUnknownType`  
`struct FRigVMUnknownType`  
_L16-28_
- reflection: `USTRUCT(meta=(DisplayName="Wildcard"))`
- desc: The unknown type is used to identify untyped nodes
- L20 _public function_ `FRigVMUnknownType() : Hash(0)`
- L27 _private member_ `uint32 Hash;` — `UPROPERTY()`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMUserWorkflow.h` (Public)


#### enum `ERigVMUserWorkflowType`  
`enum class ERigVMUserWorkflowType : uint8`  
_L35-43_
- reflection: `UENUM(BlueprintType)`
- desc: Types of workflows offered by a rigvm struct node
- L37 _public enumerator_ `Invalid = 0 UMETA(Hidden)`
- L38 _public enumerator_ `NodeContext = 0x001`
- L39 _public enumerator_ `PinContext = 0x002`
- L40 _public enumerator_ `OnPinDefaultChanged = 0x004`
- L41 _public enumerator_ `NodeContextButton = 0x008`
- L42 _public enumerator_ `All = NodeContext | PinContext | OnPinDefaultChanged | NodeContextButton`

#### struct `FRigVMUserWorkflow`  
`struct FRigVMUserWorkflow`  
_L46-106_
- reflection: `USTRUCT(BlueprintType)`
- L52 _public function_ `FRigVMUserWorkflow() : Type(ERigVMUserWorkflowType::Invalid) , OptionsClass(nullptr)`
- L57 _public function_ `FRigVMUserWorkflow( const FString& InTitle, const FString& InTooltip, ERigVMUserWorkflowType InType, FRigVMPerformUserWorkflowDelegate InGetActionsDelegate, UClass* InOptionsClass) : Title(InTitle) , Tooltip(InTooltip) , Type(InType) , PerformDelegate(InGetActionsDelegate) , OptionsClass(InOptionsClass)`
- L70 _public prototype_ `virtual ~FRigVMUserWorkflow() = default;`
- L72 _public function_ `bool IsValid() const`
- L79 _public function_ `const FString& GetTitle() const`
- L80 _public function_ `const FString& GetTooltip() const`
- L81 _public function_ `ERigVMUserWorkflowType GetType() const`
- L82 _public function_ `UClass* GetOptionsClass() const`
- L84 _public prototype_ `bool Perform(const URigVMUserWorkflowOptions* InOptions, UObject* InController) const;`
- L88 _protected prototype_ `bool ValidateOptions(const URigVMUserWorkflowOptions* InOptions) const;`
- L91 _protected member_ `FString Title;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Workflow, meta = (AllowPrivateAccess = true))`
- L94 _protected member_ `FString Tooltip;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Workflow, meta = (AllowPrivateAccess = true))`
- L97 _protected member_ `ERigVMUserWorkflowType Type;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Workflow, meta = (AllowPrivateAccess = true))`
- L99 _protected member_ `FRigVMPerformUserWorkflowDelegate PerformDelegate;`
- L102 _protected member_ `FRigVMPeformUserWorkflowDynamicDelegate PerformDynamicDelegate;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Workflow, meta = (ScriptName = "OnPerformWorkflow", AllowPrivateAccess = true))`
- L105 _protected member_ `TObjectPtr<UClass> OptionsClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Workflow, meta = (AllowPrivateAccess = true))`

#### class `URigVMUserWorkflowOptions`  
`class URigVMUserWorkflowOptions : public UObject`  
_L109-175_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L116 _public function_ `bool IsValid() const` — `UFUNCTION(BlueprintCallable, Category=Options)`
- L119 _public prototype_ `bool RequiresDialog() const;` — `UFUNCTION(BlueprintCallable, Category=Options)`
- L122 _public function_ `template<typename T = UObject> T* GetSubject() const`
- L124 _public function_ `UObject* GetSubjectChecked() const`
- L132 _public function_ `template<typename T> T* GetSubjectChecked() const`
- L134 _public function_ `const FRigVMUserWorkflow& GetWorkflow() const`
- L136 _public prototype_ `void Report(EMessageSeverity::Type InSeverity, const FString& InMessage) const;`
- L139 _public function_ `template <typename... Types> void Reportf(EMessageSeverity::Type InSeverity, UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L145 _public function_ `void ReportError(const FString& InMessage)` — `UFUNCTION(BlueprintCallable, Category=Options)`
- L151 _public function_ `void ReportWarning(const FString& InMessage)` — `UFUNCTION(BlueprintCallable, Category=Options)`
- L157 _public function_ `void ReportInfo(const FString& InMessage)` — `UFUNCTION(BlueprintCallable, Category=Options)`
- L164 _protected prototype_ `virtual bool RequiresDialog(const FProperty* InProperty) const;`
- L167 _protected member_ `TObjectPtr<UObject> Subject;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Options, meta = (AllowPrivateAccess = true))`
- L170 _protected member_ `FRigVMUserWorkflow Workflow;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Options, meta = (AllowPrivateAccess = true))`
- L172 _protected member_ `FRigVMReportDelegate ReportDelegate;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API RIGVM_API`
- L29 _delegate_ `DECLARE_DELEGATE_ThreeParams(FRigVMReportDelegate, EMessageSeverity::Type, UObject*, const FString&);`
- L29 _prototype_ `DECLARE_DELEGATE_ThreeParams(FRigVMReportDelegate, EMessageSeverity::Type, UObject*, const FString&);`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMPerformUserWorkflowDelegate, const URigVMUserWorkflowOptions*, UObject*);`
- L30 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMPerformUserWorkflowDelegate, const URigVMUserWorkflowOptions*, UObject*);`
- L31 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FRigVMPeformUserWorkflowDynamicDelegate, const URigVMUserWorkflowOptions*, InOptions, UObject*, InController);`
- L31 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FRigVMPeformUserWorkflowDynamicDelegate, const URigVMUserWorkflowOptions*, InOptions, UObject*, InController);`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMVariableDescription.h` (Public)


#### struct `FRigVMGraphVariableDescription`  
`struct FRigVMGraphVariableDescription`  
_L18-87_
- reflection: `USTRUCT(BlueprintType)`
- desc: The variable description is used to convey information about unique variables within a Graph. Multiple Variable Nodes can share the same variable description.
- L25 _public function_ `bool operator ==(const FRigVMGraphVariableDescription& Other) const` — comparison operator
- L36 _public member_ `FGuid Guid;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RigVMGraphVariableDescription)` — The guid of the variable
- L40 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RigVMGraphVariableDescription)` — The name of the variable
- L44 _public member_ `FString CPPType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RigVMGraphVariableDescription)` — The C++ data type of the variable
- L48 _public member_ `TObjectPtr<UObject> CPPTypeObject = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RigVMGraphVariableDescription)` — The Struct of the C++ data type of the variable (or nullptr)
- L51 _public member_ `FName CPPTypeObjectPath;` — `UPROPERTY()`
- L55 _public member_ `FString DefaultValue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RigVMGraphVariableDescription)` — The default value of the variable
- L59 _public member_ `FText Category;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RigVMGraphVariableDescription)` — The category of the variable
- L63 _public member_ `FText Tooltip;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RigVMGraphVariableDescription)` — The tooltip of the variable
- L67 _public member_ `bool bExposedOnSpawn = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RigVMGraphVariableDescription)` — Should this variable be exposed on spawn
- L71 _public member_ `bool bExposeToCinematics = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RigVMGraphVariableDescription)` — Should this variable be exposed on spawn
- L75 _public member_ `bool bPublic = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RigVMGraphVariableDescription)` — Is this variable public
- L80 _public member_ `bool bPrivate = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RigVMGraphVariableDescription)` — This property should soon become deprecated, since it does not make sense for blueprint independent assets Is this variable private
- L83 _public prototype_ `FRigVMExternalVariable ToExternalVariable() const;` — Returns nullptr external variable matching this description
- L85 _public prototype_ `bool ChangeType(const FString& InCPPType, UObject* InCPPTypeObject);`

#### Free symbols / members of external scopes

- L89 _namespace_ `namespace RigVMVariableUtils`
- L91 _prototype_ `FRigVMExternalVariable ExternalVariableFromRigVMVariableDescription(const FRigVMGraphVariableDescription& InVariableDescription);` (scope `RigVMVariableUtils`)
- L93 _prototype_ `FRigVMGraphVariableDescription VariableDescriptionFromPropertyDesc(const FPropertyBagPropertyDesc& InPropertyDesc);` (scope `RigVMVariableUtils`)
- L95 _prototype_ `FRigVMPropertyDescription PropertyDescriptionFromVariableDescription(const FRigVMGraphVariableDescription& InVariableDescription, const bool bAllowSpacesInName);` (scope `RigVMVariableUtils`)

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMCore/RigVMVariant.h` (Public)


#### struct `FRigVMTag`  
`struct FRigVMTag`  
_L15-108_
- reflection: `USTRUCT(BlueprintType)`
- desc: User applied tag
- L19 _public function_ `FRigVMTag() : Name(NAME_None) , Label() , ToolTip() , Color(FLinearColor::White) , bShowInUserInterface(true) , bMarksSubjectAsInvalid(false)`
- L28 _public function_ `FRigVMTag(const FName& InName, const FString& InLabel, const FText& InToolTip, const FLinearColor& InColor, bool InShowInUserInterface = true, bool InMarksSubjectAsInvalid = false) : Name(InName) , Label(InLabel) , ToolTip(InToolTip) , Color(InColor) , bShowInUserInterface(InShowInUserInterface) , bMarksSubjectAsInvalid(InMarksSubjectAsInvalid)`
- L38 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Variant)`
- L41 _public member_ `FString Label;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Variant)`
- L44 _public member_ `FText ToolTip;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Variant)`
- L47 _public member_ `FLinearColor Color;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Variant)`
- L53 _public member_ `bool bShowInUserInterface;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Variant)` — Enabling this will show tags in the user interface within the variant widgets and other places. Disabling this will interpret this tag as automation / scripting only.
- L59 _public member_ `bool bMarksSubjectAsInvalid;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Variant, meta=(DisplayName="Mark Subject Deprecated"))` — Enabling this will mark the subject (asset, function etc) as (soft) deprecated. The content referring to variants with this tag will continue to work, but the user interface will suggest the user to upgrade to a later variant.
- L61 _public function_ `bool IsValid() const`
- L66 _public function_ `FString GetLabel() const`

#### struct `FRigVMVariant`  
`struct FRigVMVariant`  
_L111-154_
- reflection: `USTRUCT(BlueprintType)`
- L115 _public function_ `FRigVMVariant(const FRigVMVariant& OtherVariant)`
- L123 _public member_ `FGuid Guid;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=Variant)` — Guid which is shared by all variants of the same element
- L127 _public member_ `TArray<FRigVMTag> Tags;` — `UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category=Variant)` — Tags applied to this variant
- L129 _public function_ `FRigVMVariant() : Guid(FGuid())`
- L132 _public function_ `bool IsValid() const`
- L146 _public function_ `static FGuid GenerateGUID(const FString InPath = FString())`

#### struct `FRigVMVariantRef`  
`struct FRigVMVariantRef`  
_L159-188_
- reflection: `USTRUCT(BlueprintType)`
- desc: This struct should not be serialized. It is generated on demand.
- L163 _public function_ `FRigVMVariantRef()`
- L165 _public function_ `FRigVMVariantRef(const FSoftObjectPath& InPath, const FRigVMVariant& InVariant) : ObjectPath(InPath), Variant(InVariant)`
- L168 _public function_ `bool operator == (const FRigVMVariantRef& Other) const`
- L173 _public function_ `bool IsValid() const`
- L184 _public member_ `FSoftObjectPath ObjectPath;` — `UPROPERTY(BlueprintReadOnly, Category=RigVMVariantRef)`
- L187 _public member_ `FRigVMVariant Variant;` — `UPROPERTY(BlueprintReadOnly, Category=RigVMVariantRef)`

#### Free symbols / members of external scopes

- L11 _externvar_ `extern TAutoConsoleVariable<bool> CVarRigVMEnableVariants;`
- L75 _function_ `friend uint32 GetTypeHash(const FRigVMTag& InTag)`
- L86 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMTag& Data)`
- L99 _function_ `friend bool operator==(const FRigVMTag& A, const FRigVMTag& B)`
- L137 _function_ `friend FArchive& operator<<(FArchive& Ar, FRigVMVariant& Data)`
- L178 _function_ `friend uint32 GetTypeHash(const FRigVMVariantRef& InVariantRef)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMDefines.h` (Public)


#### class `FRigVMArchiveTrace`  
`class FRigVMArchiveTrace`  
_L58-80_
- L62 _public function_ `FRigVMArchiveTrace() : Counter(1) , Archive(nullptr)`
- L70 _private member_ `int32 Counter;`
- L71 _private member_ `FArchive* Archive;`
- L73 _private prototype_ `static FRigVMArchiveTrace* AddRefTrace(FArchive* InArchive);`
- L74 _private prototype_ `static void DecRefTrace(FRigVMArchiveTrace* InTrace);`
- L76 _private member_ `static TMap<FArchive*, TSharedPtr<FRigVMArchiveTrace>> ActiveTraces;`
- L77 _private member_ `static FCriticalSection AddRemoveTracesMutex;`

#### class `FRigVMArchiveTraceBracket`  
`class FRigVMArchiveTraceBracket`  
_L82-104_
- L86 _public prototype_ `FRigVMArchiveTraceBracket(FArchive& InArchive, const FString& InScope);`
- L87 _public prototype_ `~FRigVMArchiveTraceBracket();`
- L89 _public prototype_ `void AddEntry(FArchive& InArchive, const FString& InScope);`
- L91 _public prototype_ `static FString WhiteSpace(int32 InCount);`
- L92 _public prototype_ `static FString ArchiveOffsetToString(int64 InOffset);`
- L96 _private member_ `FRigVMArchiveTrace* Trace;`
- L97 _private member_ `int32 Indentation;`
- L98 _private member_ `int64 ArchivePos;`
- L99 _private member_ `int64 LastArchivePos;`
- L100 _private member_ `bool bEnabled;`
- L101 _private member_ `FString ArchiveName;`
- L102 _private member_ `FString ArchiveWhiteSpace;`
- L103 _private member_ `FString ArchivePrefix;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_RIGVM_UCLASS_BASED_STORAGE_DISABLED 0`
- L14 _macro_ `#define UE_RIGVM_UOBJECT_PROPERTIES_ENABLED 1`
- L18 _macro_ `#define UE_RIGVM_UINTERFACE_PROPERTIES_ENABLED 1`
- L22 _macro_ `#define UE_RIGVM_AGGREGATE_NODES_ENABLED 1`
- L26 _macro_ `#define UE_RIGVM_DEBUG_TYPEINDEX 1`
- L32 _macro_ `#define UE_RIGVM_DEBUG_TYPEINDEX 0`
- L36 _macro_ `#define UE_RIGVM_DEBUG_EXECUTION 0`
- L40 _macro_ `#define UE_RIGVMCONTROLLER_VERBOSE_REPOPULATE 0`
- L44 _macro_ `#define UE_RIGVM_ARCHIVETRACE_ENABLE 0`
- L109 _macro_ `#define UE_RIGVM_ARCHIVETRACE_SCOPE(Ar, Scope) \`
- L112 _macro_ `#define UE_RIGVM_ARCHIVETRACE_SCOPE(Ar, Scope)`
- L119 _macro_ `#define UE_RIGVM_ARCHIVETRACE_ENTRY(Ar, Scope) \`
- L122 _macro_ `#define UE_RIGVM_ARCHIVETRACE_ENTRY(Ar, Scope)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Animation/RigVMFunction_AnimBase.h` (Public)


#### struct `FRigVMFunction_AnimBase`  
`struct FRigVMFunction_AnimBase : public FRigVMStruct`  
_L12-15_
- reflection: `USTRUCT(meta=(Abstract, Category = "Animation", NodeColor = "0.05 0.05 0.25", DocumentationPolicy = "Strict"))`
- inherits: `FRigVMStruct`
- desc: The base class for all animation related nodes

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Animation/RigVMFunction_AnimEasing.h` (Public)


#### struct `FRigVMFunction_AnimEasingType`  
`struct FRigVMFunction_AnimEasingType : public FRigVMFunction_AnimBase`  
_L13-28_
- reflection: `USTRUCT(meta = (DisplayName = "EaseType", Keywords = "Constant"))`
- inherits: `FRigVMFunction_AnimBase`
- desc: A constant value of an easing type
- L17 _public function_ `FRigVMFunction_AnimEasingType()`
- L22 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L27 _public member_ `ERigVMAnimEasingType Type;` — `UPROPERTY(meta = (Input, Output))` — The pass through constant easing type

#### struct `FRigVMFunction_AnimEasing`  
`struct FRigVMFunction_AnimEasing : public FRigVMFunction_AnimBase`  
_L34-76_
- reflection: `USTRUCT(meta=(DisplayName="Ease", Keywords="Easing,Profile,Smooth,Cubic"))`
- inherits: `FRigVMFunction_AnimBase`
- desc: Returns the eased version of the input value
- L38 _public function_ `FRigVMFunction_AnimEasing()`
- L46 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L51 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The value to ease using the easing functions
- L55 _public member_ `ERigVMAnimEasingType Type;` — `UPROPERTY(meta=(Input))` — The type of easing to apply
- L59 _public member_ `float SourceMinimum;` — `UPROPERTY(meta=(Input))` — The minimum value of the input
- L63 _public member_ `float SourceMaximum;` — `UPROPERTY(meta=(Input))` — The maximum value of the input
- L67 _public member_ `float TargetMinimum;` — `UPROPERTY(meta=(Input))` — The minimum value of the output
- L71 _public member_ `float TargetMaximum;` — `UPROPERTY(meta=(Input))` — The maximum value of the output
- L75 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting eased output value

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Animation/RigVMFunction_AnimEvalRichCurve.h` (Public)


#### struct `FRigVMFunction_AnimEvalRichCurve`  
`struct FRigVMFunction_AnimEvalRichCurve : public FRigVMFunction_AnimBase`  
_L15-59_
- reflection: `USTRUCT(meta=(DisplayName="Evaluate Curve", Keywords="Curve,Profile"))`
- inherits: `FRigVMFunction_AnimBase`
- desc: Evaluates the provided curve. Values are normalized between 0 and 1
- L19 _public function_ `FRigVMFunction_AnimEvalRichCurve()`
- L29 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L34 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The input value to evaluate the curve at
- L38 _public member_ `FRuntimeFloatCurve Curve;` — `UPROPERTY(meta=(Input))` — The curve to evaluate
- L42 _public member_ `float SourceMinimum;` — `UPROPERTY(meta=(Input))` — The minimum range of the input value (typically 0.0)
- L46 _public member_ `float SourceMaximum;` — `UPROPERTY(meta=(Input))` — The maximum range of the input value (typically 1.0)
- L50 _public member_ `float TargetMinimum;` — `UPROPERTY(meta=(Input))` — The minimum range of the output
- L54 _public member_ `float TargetMaximum;` — `UPROPERTY(meta=(Input))` — The maximum range of the output
- L58 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The evaluated value of the curve at the input value

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Animation/RigVMFunction_AnimRichCurve.h` (Public)


#### struct `FRigVMFunction_AnimRichCurve`  
`struct FRigVMFunction_AnimRichCurve : public FRigVMFunction_AnimBase`  
_L13-30_
- reflection: `USTRUCT(meta=(DisplayName="Curve", Keywords="Curve,Profile"))`
- inherits: `FRigVMFunction_AnimBase`
- desc: Provides a constant curve to be used for multiple curve evaluations
- L17 _public function_ `FRigVMFunction_AnimRichCurve()`
- L24 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L29 _public member_ `FRuntimeFloatCurve Curve;` — `UPROPERTY(meta=(Input, Output, Constant))` — The pass through animation rich curve

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Animation/RigVMFunction_GetDeltaTime.h` (Public)


#### struct `FRigVMFunction_GetDeltaTime`  
`struct FRigVMFunction_GetDeltaTime : public FRigVMFunction_AnimBase`  
_L12-27_
- reflection: `USTRUCT(meta=(DisplayName="Delta Time", Varying))`
- inherits: `FRigVMFunction_AnimBase`
- desc: Returns the time gone by from the previous evaluation
- L16 _public function_ `FRigVMFunction_GetDeltaTime()`
- L21 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L26 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The current delta time in seconds

#### struct `FRigVMFunction_GetAbsoluteTime`  
`struct FRigVMFunction_GetAbsoluteTime : public FRigVMFunction_AnimBase`  
_L33-48_
- reflection: `USTRUCT(meta=(DisplayName="Absolute Time", Varying))`
- inherits: `FRigVMFunction_AnimBase`
- desc: Returns the time gone by since the start of the world / the time within sequencer
- L37 _public function_ `FRigVMFunction_GetAbsoluteTime()`
- L42 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L47 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The current absolute time in seconds

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Animation/RigVMFunction_GetWorldTime.h` (Public)


#### struct `FRigVMFunction_GetWorldTime`  
`struct FRigVMFunction_GetWorldTime : public FRigVMFunction_AnimBase`  
_L12-55_
- reflection: `USTRUCT(meta = (DisplayName = "Now", Keywords = "Time,Clock", Varying))`
- inherits: `FRigVMFunction_AnimBase`
- desc: Returns the current time (year, month, day, hour, minute)
- L16 _public function_ `FRigVMFunction_GetWorldTime()`
- L21 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L26 _public member_ `float Year;` — `UPROPERTY(meta = (Output))` — The Year of the world time
- L30 _public member_ `float Month;` — `UPROPERTY(meta = (Output))` — The Month of the world time
- L34 _public member_ `float Day;` — `UPROPERTY(meta = (Output))` — The Day of the world time
- L38 _public member_ `float WeekDay;` — `UPROPERTY(meta = (Output))` — The WeekDay of the world time
- L42 _public member_ `float Hours;` — `UPROPERTY(meta = (Output))` — The Hours of the world time
- L46 _public member_ `float Minutes;` — `UPROPERTY(meta = (Output))` — The Minutes of the world time
- L50 _public member_ `float Seconds;` — `UPROPERTY(meta = (Output))` — The Seconds of the world time
- L54 _public member_ `float OverallSeconds;` — `UPROPERTY(meta = (Output))` — The OverallSeconds of the world time

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Animation/RigVMFunction_TimeConversion.h` (Public)


#### struct `FRigVMFunction_FramesToSeconds`  
`struct FRigVMFunction_FramesToSeconds : public FRigVMFunction_AnimBase`  
_L12-31_
- reflection: `USTRUCT(meta=(DisplayName="Frames to Seconds", Varying))`
- inherits: `FRigVMFunction_AnimBase`
- desc: Converts frames to seconds based on the current frame rate
- L16 _public function_ `FRigVMFunction_FramesToSeconds()`
- L21 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L26 _public member_ `float Frames;` — `UPROPERTY(meta=(Input))` — The input value representing a number of frames to convert to seconds
- L30 _public member_ `float Seconds;` — `UPROPERTY(meta=(Output))` — The resulting time in seconds

#### struct `FRigVMFunction_SecondsToFrames`  
`struct FRigVMFunction_SecondsToFrames : public FRigVMFunction_AnimBase`  
_L37-56_
- reflection: `USTRUCT(meta=(DisplayName="Seconds to Frames", Varying))`
- inherits: `FRigVMFunction_AnimBase`
- desc: Converts seconds to frames based on the current frame rate
- L41 _public function_ `FRigVMFunction_SecondsToFrames()`
- L46 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L51 _public member_ `float Seconds;` — `UPROPERTY(meta=(Input))` — The input time as seconds
- L55 _public member_ `float Frames;` — `UPROPERTY(meta=(Output))` — The resulting number of frames

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Debug/RigVMFunction_DebugBase.h` (Public)


#### struct `FRigVMFunction_DebugBase`  
`struct FRigVMFunction_DebugBase : public FRigVMStruct`  
_L13-20_
- reflection: `USTRUCT(meta=(Abstract, Category="Debug", NodeColor = "0.83077 0.846873 0.049707", DocumentationPolicy = "Strict"))`
- inherits: `FRigVMStruct`
- desc: The base class for all pure debug draw nodes
- L19 _public member_ `FRigVMDebugDrawSettings DebugDrawSettings;` — `UPROPERTY(meta = (Input, DetailsOnly, DisplayName = "Draw Settings"))` — The debug draw settings for this node

#### struct `FRigVMFunction_DebugBaseMutable`  
`struct FRigVMFunction_DebugBaseMutable : public FRigVMStructMutable`  
_L26-33_
- reflection: `USTRUCT(meta=(Abstract, Category="Debug", NodeColor = "0.83077 0.846873 0.049707", DocumentationPolicy = "Strict", Pure))`
- inherits: `FRigVMStructMutable`
- desc: The base class for all mutable debug draw nodes
- L32 _public member_ `FRigVMDebugDrawSettings DebugDrawSettings;` — `UPROPERTY(meta = (Input, DetailsOnly, DisplayName = "Draw Settings"))` — The debug draw settings for this node

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Debug/RigVMFunction_DebugLine.h` (Public)


#### struct `FRigVMFunction_DebugLineNoSpace`  
`struct FRigVMFunction_DebugLineNoSpace : public FRigVMFunction_DebugBaseMutable`  
_L14-53_
- reflection: `USTRUCT(meta=(DisplayName="Draw Line"))`
- inherits: `FRigVMFunction_DebugBaseMutable`
- desc: Draws a line in the viewport given a start and end vector
- L18 _public function_ `FRigVMFunction_DebugLineNoSpace()`
- L27 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L32 _public member_ `FVector A;` — `UPROPERTY(meta = (Input))` — The global start position of the line
- L36 _public member_ `FVector B;` — `UPROPERTY(meta = (Input))` — The global end position of the line
- L40 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input))` — The color to use for the drawing
- L44 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input))` — The line thickness to use for the drawing
- L48 _public member_ `FTransform WorldOffset;` — `UPROPERTY(meta = (Input))` — The world offset to pre-multiply the positions with
- L52 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))` — If set to False the debug drawing will be skipped

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Debug/RigVMFunction_DebugLineStrip.h` (Public)


#### struct `FRigVMFunction_DebugLineStripNoSpace`  
`struct FRigVMFunction_DebugLineStripNoSpace : public FRigVMFunction_DebugBaseMutable`  
_L12-46_
- reflection: `USTRUCT(meta=(DisplayName="Draw Line Strip"))`
- inherits: `FRigVMFunction_DebugBaseMutable`
- desc: Draws a line strip in the viewport given any number of points
- L16 _public function_ `FRigVMFunction_DebugLineStripNoSpace()`
- L24 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L29 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (Input))` — The array of input positions to treat as a line-strip
- L33 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input))` — The color to use for the drawing
- L37 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input))` — The line thickness to use for the drawing
- L41 _public member_ `FTransform WorldOffset;` — `UPROPERTY(meta = (Input))` — The world offset to pre-multiply the positions with
- L45 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))` — If set to False the debug drawing will be skipped

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Debug/RigVMFunction_DebugPoint.h` (Public)


#### enum `ERigUnitDebugPointMode`  
`enum class ERigUnitDebugPointMode : uint8`  
_L9-19_
- reflection: `UENUM(meta = (RigVMTypeAllowed))`
- L12 _public enumerator_ `Point` — Draw as point
- L15 _public enumerator_ `Vector` — Draw as vector
- L18 _public enumerator_ `Max UMETA(Hidden)` — MAX - invalid

#### struct `FRigVMFunction_DebugPoint`  
`struct FRigVMFunction_DebugPoint : public FRigVMFunction_DebugBase`  
_L22-66_
- reflection: `USTRUCT(meta=(DisplayName="Draw Point In Place", Keywords="Draw Vector", Deprecated = "4.25.0"))`
- inherits: `FRigVMFunction_DebugBase`
- L26 _public function_ `FRigVMFunction_DebugPoint()`
- L37 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L41 _public member_ `FVector Vector;` — `UPROPERTY(meta = (Input, Output))`
- L44 _public member_ `ERigUnitDebugPointMode Mode;` — `UPROPERTY(meta = (Input))`
- L47 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input))`
- L50 _public member_ `float Scale;` — `UPROPERTY(meta = (Input))`
- L53 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input))`
- L56 _public member_ `FName Space;` — `UPROPERTY(meta = (Input))`
- L59 _public member_ `FTransform WorldOffset;` — `UPROPERTY(meta = (Input))`
- L62 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input, Constant))`
- L64 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_DebugPointMutable`  
`struct FRigVMFunction_DebugPointMutable : public FRigVMFunction_DebugBaseMutable`  
_L69-115_
- reflection: `USTRUCT(meta=(DisplayName="Draw Point", Keywords="Draw Vector", Deprecated = "4.25.0"))`
- inherits: `FRigVMFunction_DebugBaseMutable`
- L73 _public function_ `FRigVMFunction_DebugPointMutable()`
- L84 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L88 _public member_ `FVector Vector;` — `UPROPERTY(meta = (Input))`
- L91 _public member_ `ERigUnitDebugPointMode Mode;` — `UPROPERTY(meta = (Input))`
- L94 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input))`
- L97 _public member_ `float Scale;` — `UPROPERTY(meta = (Input))`
- L100 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input))`
- L103 _public member_ `FName Space;` — `UPROPERTY(meta = (Input))`
- L106 _public member_ `FTransform WorldOffset;` — `UPROPERTY(meta = (Input))`
- L111 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input, Constant))`
- L113 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Debug/RigVMFunction_DebugPrimitives.h` (Public)


#### struct `FRigVMFunction_DebugRectangle`  
`struct FRigVMFunction_DebugRectangle : public FRigVMFunction_DebugBaseMutable`  
_L11-57_
- reflection: `USTRUCT(meta=(DisplayName="Draw Rectangle", Keywords="Draw Square", Deprecated = "4.25"))`
- inherits: `FRigVMFunction_DebugBaseMutable`
- L15 _public function_ `FRigVMFunction_DebugRectangle()`
- L25 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L30 _public member_ `FTransform Transform;` — `UPROPERTY(meta = (Input))` — The transform of the rectangle to draw
- L34 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input))` — The color to use for the debug draw
- L38 _public member_ `float Scale;` — `UPROPERTY(meta = (Input))` — The scale to apply to the debug draw
- L42 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input))` — The line thickness to use for the debug draw
- L45 _public member_ `FName Space;` — `UPROPERTY(meta = (Input))`
- L49 _public member_ `FTransform WorldOffset;` — `UPROPERTY(meta = (Input))` — The world offset to pre-multiply the positions with
- L53 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input, Constant))` — If set to False the debug drawing will be skipped
- L55 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_DebugRectangleNoSpace`  
`struct FRigVMFunction_DebugRectangleNoSpace : public FRigVMFunction_DebugBaseMutable`  
_L63-103_
- reflection: `USTRUCT(meta=(DisplayName="Draw Rectangle", Keywords="Draw Square"))`
- inherits: `FRigVMFunction_DebugBaseMutable`
- desc: Draws a rectangle in the viewport given a transform
- L67 _public function_ `FRigVMFunction_DebugRectangleNoSpace()`
- L77 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L82 _public member_ `FTransform Transform;` — `UPROPERTY(meta = (Input))` — The transform of the rectangle to draw
- L86 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input))` — The color to use for the debug draw
- L90 _public member_ `float Scale;` — `UPROPERTY(meta = (Input))` — The scale to apply to the debug draw
- L94 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input))` — The line thickness to use for the debug draw
- L98 _public member_ `FTransform WorldOffset;` — `UPROPERTY(meta = (Input))` — The world offset to pre-multiply the positions with
- L102 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))` — If set to False the debug drawing will be skipped

#### struct `FRigVMFunction_DebugArc`  
`struct FRigVMFunction_DebugArc : public FRigVMFunction_DebugBaseMutable`  
_L107-162_
- reflection: `USTRUCT(meta=(DisplayName="Draw Arc", Keywords="Draw Ellipse, Draw Circle", Deprecated = "4.25"))`
- inherits: `FRigVMFunction_DebugBaseMutable`
- L111 _public function_ `FRigVMFunction_DebugArc()`
- L123 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L127 _public member_ `FTransform Transform;` — `UPROPERTY(meta = (Input))`
- L131 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input))` — The color to use for the debug draw
- L134 _public member_ `float Radius;` — `UPROPERTY(meta = (Input))`
- L137 _public member_ `float MinimumDegrees;` — `UPROPERTY(meta = (Input))`
- L140 _public member_ `float MaximumDegrees;` — `UPROPERTY(meta = (Input))`
- L144 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input))` — The line thickness to use for the debug draw
- L147 _public member_ `int32 Detail;` — `UPROPERTY(meta = (Input))`
- L150 _public member_ `FName Space;` — `UPROPERTY(meta = (Input))`
- L154 _public member_ `FTransform WorldOffset;` — `UPROPERTY(meta = (Input))` — The world offset to pre-multiply the positions with
- L158 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input, Constant))` — If set to False the debug drawing will be skipped
- L160 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_DebugArcNoSpace`  
`struct FRigVMFunction_DebugArcNoSpace : public FRigVMFunction_DebugBaseMutable`  
_L168-222_
- reflection: `USTRUCT(meta=(DisplayName="Draw Arc", Keywords="Draw Ellipse, Draw Circle"))`
- inherits: `FRigVMFunction_DebugBaseMutable`
- desc: Draws an arc in the viewport, can take in different min and max degrees
- L172 _public function_ `FRigVMFunction_DebugArcNoSpace()`
- L184 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L189 _public member_ `FTransform Transform;` — `UPROPERTY(meta = (Input))` — The transform of the arc to draw
- L193 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input))` — The color to use for the debug draw
- L197 _public member_ `float Radius;` — `UPROPERTY(meta = (Input))` — The radius of the arc to draw
- L201 _public member_ `float MinimumDegrees;` — `UPROPERTY(meta = (Input))` — The minimum angle in degrees of the arc
- L205 _public member_ `float MaximumDegrees;` — `UPROPERTY(meta = (Input))` — The maximum angle in degrees of the arc
- L209 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input))` — The line thickness to use for the debug draw
- L213 _public member_ `int32 Detail;` — `UPROPERTY(meta = (Input))` — The detail to use when drawing the arc
- L217 _public member_ `FTransform WorldOffset;` — `UPROPERTY(meta = (Input))` — The world offset to pre-multiply the positions with
- L221 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))` — If set to False the debug drawing will be skipped

#### struct `FRigVMFunction_DebugBoxNoSpace`  
`struct FRigVMFunction_DebugBoxNoSpace : public FRigVMFunction_DebugBaseMutable`  
_L228-264_
- reflection: `USTRUCT(meta=(DisplayName="Draw Box", Keywords="BoundingBox,Bbox"))`
- inherits: `FRigVMFunction_DebugBaseMutable`
- desc: Draws a box in the viewport
- L232 _public function_ `FRigVMFunction_DebugBoxNoSpace()`
- L242 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L247 _public member_ `FBox Box;` — `UPROPERTY(meta = (Input))` — The input bounding box to draw
- L251 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input))` — The color to use for the debug draw
- L255 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input))` — The line thickness to use for the debug draw
- L259 _public member_ `FTransform WorldOffset;` — `UPROPERTY(meta = (Input))` — The world offset to pre-multiply the positions with
- L263 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))` — If set to False the debug drawing will be skipped

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Debug/RigVMFunction_DebugTransform.h` (Public)


#### enum `ERigUnitDebugTransformMode`  
`enum class ERigUnitDebugTransformMode : uint8`  
_L9-22_
- reflection: `UENUM(meta = (RigVMTypeAllowed))`
- L12 _public enumerator_ `Point` — Draw as point
- L15 _public enumerator_ `Axes` — Draw as axes
- L18 _public enumerator_ `Box` — Draw as box
- L21 _public enumerator_ `Max UMETA(Hidden)` — MAX - invalid

#### struct `FRigVMFunction_DebugTransformMutableNoSpace`  
`struct FRigVMFunction_DebugTransformMutableNoSpace : public FRigVMFunction_DebugBaseMutable`  
_L28-72_
- reflection: `USTRUCT(meta=(DisplayName="Draw Transform"))`
- inherits: `FRigVMFunction_DebugBaseMutable`
- desc: Given a transform, will draw a point, axis, or a box in the viewport
- L32 _public function_ `FRigVMFunction_DebugTransformMutableNoSpace()`
- L42 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L47 _public member_ `FTransform Transform;` — `UPROPERTY(meta = (Input))` — The transform to draw
- L51 _public member_ `ERigUnitDebugTransformMode Mode;` — `UPROPERTY(meta = (Input))` — The mode to use when drawing the transform
- L55 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input))` — The debug color to use
- L59 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input))` — The line thickness to use
- L63 _public member_ `float Scale;` — `UPROPERTY(meta = (Input))` — The scale to scale the transform by
- L67 _public member_ `FTransform WorldOffset;` — `UPROPERTY(meta = (Input))` — The world offset to pre-multiply the transform with
- L71 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))` — If False the debug drawing will be skipped

#### struct `FRigVMFunction_DebugTransformArrayMutable_WorkData`  
`struct FRigVMFunction_DebugTransformArrayMutable_WorkData`  
_L75-81_
- reflection: `USTRUCT()`
- L80 _public member_ `TArray<FTransform> DrawTransforms;` — `UPROPERTY()`

#### struct `FRigVMFunction_DebugTransformArrayMutableNoSpace`  
`struct FRigVMFunction_DebugTransformArrayMutableNoSpace : public FRigVMFunction_DebugBaseMutable`  
_L87-137_
- reflection: `USTRUCT(meta=(DisplayName="Draw Transform Array"))`
- inherits: `FRigVMFunction_DebugBaseMutable`
- desc: Given a transform array, will draw a point, axis, or a box in the viewport
- L91 _public function_ `FRigVMFunction_DebugTransformArrayMutableNoSpace()`
- L101 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L106 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY(meta = (Input))` — An array of input transforms to draw
- L112 _public member_ `TArray<int32> ParentIndices;` — `UPROPERTY(meta = (Input))` — An array of parent indices for each transform. If this is specified lines will be drawn from each child to parent to represent a hierarchy.
- L116 _public member_ `ERigUnitDebugTransformMode Mode;` — `UPROPERTY(meta = (Input))` — The mode to use when drawing the transforms
- L120 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input))` — The debug color to use
- L124 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input))` — The line thickness to use
- L128 _public member_ `float Scale;` — `UPROPERTY(meta = (Input))` — The scale to scale the transforms by
- L132 _public member_ `FTransform WorldOffset;` — `UPROPERTY(meta = (Input))` — The world offset to pre-multiply the transforms with
- L136 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))` — If False the debug drawing will be skipped

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Debug/RigVMFunction_VisualDebug.h` (Public)


#### enum `ERigUnitVisualDebugPointMode`  
`enum class ERigUnitVisualDebugPointMode : uint8`  
_L9-19_
- reflection: `UENUM(meta = (RigVMTypeAllowed))`
- L12 _public enumerator_ `Point` — Draw as point
- L15 _public enumerator_ `Vector` — Draw as vector
- L18 _public enumerator_ `Max UMETA(Hidden)` — MAX - invalid

#### struct `FRigVMFunction_VisualDebugVector`  
`struct FRigVMFunction_VisualDebugVector : public FRigVMFunction_DebugBase`  
_L22-63_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Debug Vector", Keywords = "Draw,Point", Deprecated = "4.25", Varying))`
- inherits: `FRigVMFunction_DebugBase`
- L26 _public function_ `FRigVMFunction_VisualDebugVector()`
- L37 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L41 _public member_ `FVector Value;` — `UPROPERTY(meta = (Input, Output))`
- L44 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))`
- L47 _public member_ `ERigUnitVisualDebugPointMode Mode;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))`
- L50 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))`
- L53 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))`
- L56 _public member_ `float Scale;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))`
- L59 _public member_ `FName BoneSpace;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))`
- L61 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_VisualDebugVectorNoSpace`  
`struct FRigVMFunction_VisualDebugVectorNoSpace : public FRigVMFunction_DebugBase`  
_L69-109_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Debug Vector", TemplateName="VisualDebug", Keywords = "Draw,Point", Varying))`
- inherits: `FRigVMFunction_DebugBase`
- desc: Debug draw parameters for a Point or Vector given a vector
- L73 _public function_ `FRigVMFunction_VisualDebugVectorNoSpace()`
- L83 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L88 _public member_ `FVector Value;` — `UPROPERTY(meta = (Input, Output))` — The pass through vector to draw
- L92 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))` — If set to False the debug drawing will be skipped
- L96 _public member_ `ERigUnitVisualDebugPointMode Mode;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))` — The mode to draw the vector with
- L100 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))` — The color to use for the debug draw
- L104 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))` — The line thickness to use for the drawing
- L108 _public member_ `float Scale;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))` — The scale to apply to the vector when drawing

#### struct `FRigVMFunction_VisualDebugQuat`  
`struct FRigVMFunction_VisualDebugQuat : public FRigVMFunction_DebugBase`  
_L112-145_
- reflection: `USTRUCT(meta = (DisplayName = "Visual Debug Quat", Keywords = "Draw,Rotation", Deprecated = "4.25", Varying))`
- inherits: `FRigVMFunction_DebugBase`
- L116 _public function_ `FRigVMFunction_VisualDebugQuat()`
- L125 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L129 _public member_ `FQuat Value;` — `UPROPERTY(meta = (Input, Output))`
- L132 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))`
- L135 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))`
- L138 _public member_ `float Scale;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))`
- L141 _public member_ `FName BoneSpace;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))`
- L143 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_VisualDebugQuatNoSpace`  
`struct FRigVMFunction_VisualDebugQuatNoSpace : public FRigVMFunction_DebugBase`  
_L151-181_
- reflection: `USTRUCT(meta = (DisplayName = "Visual Debug Quat", TemplateName="VisualDebug", Keywords = "Draw,Rotation", Varying))`
- inherits: `FRigVMFunction_DebugBase`
- desc: Debug draw parameters for an Axis given a quaternion
- L155 _public function_ `FRigVMFunction_VisualDebugQuatNoSpace()`
- L163 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L168 _public member_ `FQuat Value;` — `UPROPERTY(meta = (Input, Output))` — The pass through rotation to draw
- L172 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))` — If set to False the debug drawing will be skipped
- L176 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))` — The line thickness to use for the drawing
- L180 _public member_ `float Scale;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))` — The scale to apply to the axes drawn

#### struct `FRigVMFunction_VisualDebugTransform`  
`struct FRigVMFunction_VisualDebugTransform : public FRigVMFunction_DebugBase`  
_L184-217_
- reflection: `USTRUCT(meta=(DisplayName="Visual Debug Transform", Keywords = "Draw,Axes", Deprecated = "4.25", Varying))`
- inherits: `FRigVMFunction_DebugBase`
- L188 _public function_ `FRigVMFunction_VisualDebugTransform()`
- L197 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L201 _public member_ `FTransform Value;` — `UPROPERTY(meta = (Input, Output, Constant))`
- L204 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))`
- L207 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))`
- L210 _public member_ `float Scale;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))`
- L213 _public member_ `FName BoneSpace;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))`
- L215 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_VisualDebugTransformNoSpace`  
`struct FRigVMFunction_VisualDebugTransformNoSpace : public FRigVMFunction_DebugBase`  
_L223-253_
- reflection: `USTRUCT(meta=(DisplayName="Visual Debug Transform", TemplateName="VisualDebug", Keywords = "Draw,Axes", Varying))`
- inherits: `FRigVMFunction_DebugBase`
- desc: Debug draw parameters for an Axis given a transform
- L227 _public function_ `FRigVMFunction_VisualDebugTransformNoSpace()`
- L235 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L240 _public member_ `FTransform Value;` — `UPROPERTY(meta = (Input, Output, Constant))` — The pass through transform to draw
- L244 _public member_ `bool bEnabled;` — `UPROPERTY(meta = (Input))` — If set to False the debug drawing will be skipped
- L248 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))` — The line thickness to use for the drawing
- L252 _public member_ `float Scale;` — `UPROPERTY(meta = (Input, EditCondition = "bEnabled"))` — The scale to apply to the axes drawn

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Debug/RigVMFunction_VisualLog.h` (Public)


#### struct `FRigVMFunction_VisualLogBase`  
`struct FRigVMFunction_VisualLogBase : public FRigVMFunction_DebugBaseMutable`  
_L10-21_
- reflection: `USTRUCT(meta=(Abstract, Keywords = "Draw,Point"))`
- inherits: `FRigVMFunction_DebugBaseMutable`
- desc: Base RigVMFunction used for Visual Logger output
- L16 _public member_ `FString Text;` — `UPROPERTY(meta=(Input))` — The text to log
- L20 _public member_ `FName Category = TEXT("Vis` — `UPROPERTY(meta=(Input))` — The category of the logged text

#### struct `FRigVMFunction_VisualLogText`  
`struct FRigVMFunction_VisualLogText : public FRigVMFunction_VisualLogBase`  
_L25-31_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Log Text", Keywords = "Draw,String"))`
- inherits: `FRigVMFunction_VisualLogBase`
- desc: Logs simple text string with Visual Logger - recording for Visual Logs has to be enabled to record this data
- L29 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_VisualLogObject`  
`struct FRigVMFunction_VisualLogObject : public FRigVMFunction_VisualLogBase`  
_L35-42_
- reflection: `USTRUCT(meta=(Abstract, Keywords = "Draw,String"))`
- inherits: `FRigVMFunction_VisualLogBase`
- desc: Base RigVMFunction for visual logging of objects
- L41 _public member_ `FLinearColor ObjectColor = FLinearColor::Blue;` — `UPROPERTY(meta=(Input))` — The color of the logged object

#### struct `FRigVMFunction_VisualLogLocation`  
`struct FRigVMFunction_VisualLogLocation : public FRigVMFunction_VisualLogObject`  
_L46-60_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Log Location", Keywords = "Draw,String,Sphere"))`
- inherits: `FRigVMFunction_VisualLogObject`
- desc: Logs location as sphere with given radius - recording for Visual Logs has to be enabled to record this data
- L50 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L55 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta=(Input))` — The location to log
- L59 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta=(Input))` — The radius of the sphere to log the location with

#### struct `FRigVMFunction_VisualLogWireframeOptional`  
`struct FRigVMFunction_VisualLogWireframeOptional : public FRigVMFunction_VisualLogObject`  
_L64-71_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_VisualLogObject`
- desc: Base RigVMFunction for visual logging of objects that can be wirefame
- L70 _public member_ `bool bWireframe = false;` — `UPROPERTY(meta=(Input))` — Whether to display as wireframe

#### struct `FRigVMFunction_VisualLogSphere`  
`struct FRigVMFunction_VisualLogSphere : public FRigVMFunction_VisualLogWireframeOptional`  
_L75-89_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Log Sphere", Keywords = "Draw,String"))`
- inherits: `FRigVMFunction_VisualLogWireframeOptional`
- desc: Logs sphere shape - recording for Visual Logs has to be enabled to record this data
- L79 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L84 _public member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY(meta=(Input))` — The centre of the sphere
- L88 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta=(Input))` — The radius of the sphere

#### struct `FRigVMFunction_VisualLogCone`  
`struct FRigVMFunction_VisualLogCone : public FRigVMFunction_VisualLogWireframeOptional`  
_L93-115_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Log Cone", Keywords = "Draw,String"))`
- inherits: `FRigVMFunction_VisualLogWireframeOptional`
- desc: Logs cone shape - recording for Visual Logs has to be enabled to record this data
- L97 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L102 _public member_ `FVector Origin = FVector::ZeroVector;` — `UPROPERTY(meta=(Input))` — The origin of the cone
- L106 _public member_ `FVector Direction = FVector(0.0f, 0.0f, 1.0f);` — `UPROPERTY(meta=(Input))` — The direction of the cone
- L110 _public member_ `float Length = 10.0f;` — `UPROPERTY(meta=(Input))` — The length of the cone
- L114 _public member_ `float Angle = 10.0f;` — `UPROPERTY(meta=(Input))` — The angle of the cone

#### struct `FRigVMFunction_VisualLogCylinder`  
`struct FRigVMFunction_VisualLogCylinder : public FRigVMFunction_VisualLogWireframeOptional`  
_L119-137_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Log Cylinder", Keywords = "Draw,String"))`
- inherits: `FRigVMFunction_VisualLogWireframeOptional`
- desc: Logs cylinder shape - recording for Visual Logs has to be enabled to record this data
- L123 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L128 _public member_ `FVector Start = FVector::ZeroVector;` — `UPROPERTY(meta=(Input))` — The start of the line segment forming the cylinder
- L132 _public member_ `FVector End = FVector::ZeroVector;` — `UPROPERTY(meta=(Input))` — The end of the line segment forming the cylinder
- L136 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta=(Input))` — The radius of the cylinder

#### struct `FRigVMFunction_VisualLogCapsule`  
`struct FRigVMFunction_VisualLogCapsule : public FRigVMFunction_VisualLogWireframeOptional`  
_L141-163_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Log Capsule", Keywords = "Draw,String"))`
- inherits: `FRigVMFunction_VisualLogWireframeOptional`
- desc: Logs capsule shape - recording for Visual Logs has to be enabled to record this data
- L145 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L150 _public member_ `FVector Base = FVector::ZeroVector;` — `UPROPERTY(meta=(Input))` — The base or origin of the capsule
- L154 _public member_ `float HalfHeight = 10.0f;` — `UPROPERTY(meta=(Input))` — Half the height of the capsule
- L158 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta=(Input))` — The radius of the capsule
- L162 _public member_ `FQuat Rotation = FQuat::Identity;` — `UPROPERTY(meta=(Input))` — The orientation of the capsule

#### struct `FRigVMFunction_VisualLogBox`  
`struct FRigVMFunction_VisualLogBox : public FRigVMFunction_VisualLogWireframeOptional`  
_L167-177_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Log Box", Keywords = "Draw,String"))`
- inherits: `FRigVMFunction_VisualLogWireframeOptional`
- desc: Logs box shape - recording for Visual Logs has to be enabled to record this data
- L171 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L176 _public member_ `FBox Box = FBox(ForceInit);` — `UPROPERTY(meta=(Input))` — The box to draw

#### struct `FRigVMFunction_VisualLogOrientedBox`  
`struct FRigVMFunction_VisualLogOrientedBox : public FRigVMFunction_VisualLogWireframeOptional`  
_L181-195_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Log Oriented Box", Keywords = "Draw,String"))`
- inherits: `FRigVMFunction_VisualLogWireframeOptional`
- desc: Logs oriented box shape - recording for Visual Logs has to be enabled to record this data
- L185 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L190 _public member_ `FBox Box = FBox(ForceInit);` — `UPROPERTY(meta=(Input))` — The box to draw
- L194 _public member_ `FTransform Transform;` — `UPROPERTY(meta=(Input))` — The transform of the box

#### struct `FRigVMFunction_VisualLogArrow`  
`struct FRigVMFunction_VisualLogArrow : public FRigVMFunction_VisualLogObject`  
_L199-217_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Log Arrow", Keywords = "Draw,String,Direction"))`
- inherits: `FRigVMFunction_VisualLogObject`
- desc: Logs arrow - recording for Visual Logs has to be enabled to record this data
- L203 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L208 _public member_ `FVector SegmentStart = FVector::ZeroVector;` — `UPROPERTY(meta=(Input))` — The start of the arrow
- L212 _public member_ `FVector SegmentEnd = FVector::ZeroVector;` — `UPROPERTY(meta=(Input))` — The end of the arrow
- L216 _public member_ `float ArrowHeadSize = 8.0f;` — `UPROPERTY(meta=(Input))` — The size of the arrow head

#### struct `FRigVMFunction_VisualLogCircle`  
`struct FRigVMFunction_VisualLogCircle : public FRigVMFunction_VisualLogWireframeOptional`  
_L221-243_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Log Circle", Keywords = "Draw,String,Disc"))`
- inherits: `FRigVMFunction_VisualLogWireframeOptional`
- desc: Logs circle - recording for Visual Logs has to be enabled to record this data
- L225 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L230 _public member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY(meta=(Input))` — The center of the circle
- L234 _public member_ `FVector UpAxis = FVector(0.0f, 0.0f, 1.0f);` — `UPROPERTY(meta=(Input))` — The up axis/normal of the circle's plane
- L238 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta=(Input))` — The radius of the circle
- L242 _public member_ `float Thickness = 0.0f;` — `UPROPERTY(meta=(Input))` — The thickness of the circle

#### struct `FRigVMFunction_VisualLogSegment`  
`struct FRigVMFunction_VisualLogSegment : public FRigVMFunction_VisualLogObject`  
_L247-265_
- reflection: `USTRUCT(meta=(DisplayName = "Visual Log Segment", Keywords = "Draw,String,Line"))`
- inherits: `FRigVMFunction_VisualLogObject`
- desc: Logs segment - recording for Visual Logs has to be enabled to record this data
- L251 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L256 _public member_ `FVector SegmentStart = FVector::ZeroVector;` — `UPROPERTY(meta=(Input))` — The start of the line segment
- L260 _public member_ `FVector SegmentEnd = FVector::ZeroVector;` — `UPROPERTY(meta=(Input))` — The end of the line segment
- L264 _public member_ `float Thickness = 0.0f;` — `UPROPERTY(meta=(Input))` — The thickness of the segment

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Execution/RigVMFunction_BreakLoop.h` (Public)


#### struct `FRigVMFunction_BreakFromLoop`  
`struct FRigVMFunction_BreakFromLoop : public FRigVMStruct`  
_L45-73_
- reflection: `USTRUCT(meta=(DisplayName="Break From Loop", Category="Execution", NodeColor = "0, 0, 0, 1", Keywords="Break,Stop,Exit,Loop", Icon="EditorStyle|GraphEditor.Macro.Loop_16x"))`
- inherits: `FRigVMStruct`
- desc: Breaks out of the enclosing For Loop or For Each loop at the end of the current iteration. When executed, it sets the enclosing loop's BlockToRun to "Completed", causing the loop to skip remaining iterations and proceed to its Completed branch. Must be placed inside a loop body; the compiler will emit an error if this node is used outside a loop scope.
- L49 _public function_ `FRigVMFunction_BreakFromLoop()`
- L55 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Writes ControlFlowCompletedName into BlockToRun to signal the enclosing loop to exit.
- L61 _public member_ `FRigVMExecuteContext ExecuteContext;` — `UPROPERTY(meta = (Input, DisplayName = "Execute"))` — Input-only execution pin — no output execution since the compiler emits a JumpForward after this node, making any downstream nodes dead code.
- L72 _public member_ `FName BlockToRun;` — `UPROPERTY(meta = (Singleton))` — The name of the block the enclosing loop should run next. Singleton meta causes the compiler to alias this property to the enclosing loop's BlockToRun register — no separate memory is allocated for this node. At runtime, Execute() writes ControlFlowCompletedName here, and the loop's JumpToBranch reads it to decide whether to re-enter the body or jump to Completed. Do NOT add Hidden meta — it suppresses pin creation and prevents aliasing.

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Execution/RigVMFunction_Context.h` (Public)


#### struct `FRigVMFunction_IsHostBeingDebugged`  
`struct FRigVMFunction_IsHostBeingDebugged : public FRigVMStruct`  
_L12-26_
- reflection: `USTRUCT(meta=(DisplayName="Is Asset Editor Open", Category="Execution", TitleColor="1 0 0", NodeColor="1 1 1", Keywords="Debug,Open,Inspect"))`
- inherits: `FRigVMStruct`
- desc: Returns true if a graph is run with its asset editor open. This is editor only - in shipping it always returns false.
- L16 _public function_ `FRigVMFunction_IsHostBeingDebugged() : Result(false)`
- L20 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L25 _public member_ `bool Result;` — `UPROPERTY(EditAnywhere, Transient, Category = "Execution", meta = (Output))` — True if the graph is currently open in the asset editor

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Execution/RigVMFunction_ContinueLoop.h` (Public)


#### struct `FRigVMFunction_ContinueLoop`  
`struct FRigVMFunction_ContinueLoop : public FRigVMStruct`  
_L48-60_
- reflection: `USTRUCT(meta=(DisplayName="Continue Loop", Category="Execution", NodeColor = "0, 0, 0, 1", Keywords="Continue,Skip,Next,Loop", Icon="EditorStyle|GraphEditor.Macro.Loop_16x"))`
- inherits: `FRigVMStruct`
- desc: Skips the remaining body nodes of the current loop iteration and re-enters the enclosing For Loop or For Each loop at the next iteration. The loop itself is not terminated — only the current iteration's remaining nodes are bypassed. Must be placed inside a loop body; the compiler will emit an error if this node is used outside a loop scope.
- L53 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Intentionally empty — continue semantics are handled by the compiler's JumpForward.
- L59 _public member_ `FRigVMExecuteContext ExecuteContext;` — `UPROPERTY(meta = (Input, DisplayName = "Execute"))` — Input-only execution pin — no output execution since the compiler emits a JumpForward after this node, making any downstream nodes dead code.

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Execution/RigVMFunction_ForLoop.h` (Public)


#### struct `FRigVMFunction_ForLoopCount`  
`struct FRigVMFunction_ForLoopCount : public FRigVMStructMutable`  
_L12-57_
- reflection: `USTRUCT(meta=(DisplayName="For Loop", Category="Execution", TitleColor="1 0 0", NodeColor="1 1 1", Keywords="Iterate", Icon="EditorStyle|GraphEditor.Macro.Loop_16x", DocumentationPolicy="Strict", Pure))`
- inherits: `FRigVMStructMutable`
- desc: Given a count, execute iteratively until the count is up
- L16 _public function_ `FRigVMFunction_ForLoopCount()`
- L26 _public function_ `virtual const TArray<FName>& GetControlFlowBlocks_Impl() const override`
- L32 _public function_ `virtual const bool IsControlFlowBlockSliced(const FName& InBlockName) const`
- L33 _public function_ `virtual int32 GetNumSlices() const override`
- L35 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L40 _public member_ `FName BlockToRun;` — `UPROPERTY(meta = (Singleton))` — The internal block to run as this node progressed
- L44 _public member_ `int32 Count;` — `UPROPERTY(meta = (Singleton, Input))` — The number of iterations for this loop
- L48 _public member_ `int32 Index;` — `UPROPERTY(meta = (Singleton, Output))` — The index of the current iteration
- L52 _public member_ `float Ratio;` — `UPROPERTY(meta = (Singleton, Output))` — The ratio of the current iteration (from 0.0 for the first to 1.0 for the last)
- L56 _public member_ `FRigVMExecuteContext Completed;` — `UPROPERTY(EditAnywhere, Transient, Category = "ForLoop", meta = (Output))` — The completed branch to run once the loop has finished all iterations

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Execution/RigVMFunction_Sequence.h` (Public)


#### struct `FRigVMFunction_Sequence`  
`struct FRigVMFunction_Sequence : public FRigVMStruct`  
_L12-30_
- reflection: `USTRUCT(meta=(DisplayName="Sequence", Category="Execution", TitleColor="1 0 0", NodeColor="1 1 1", Icon="EditorStyle|GraphEditor.Sequence_16x", Pure))`
- inherits: `FRigVMStruct`
- desc: Allows for a single execution pulse to trigger a series of events in order.
- L16 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L21 _public member_ `FRigVMExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, Transient, DisplayName = "Execute", Category = "SequenceExecution", meta = (Input, Aggregate))` — The execution input
- L25 _public member_ `FRigVMExecuteContext A;` — `UPROPERTY(EditAnywhere, Transient, Category = "SequenceExecution", meta = (Output, Aggregate))` — The execution result A
- L29 _public member_ `FRigVMExecuteContext B;` — `UPROPERTY(EditAnywhere, Transient, Category = "SequenceExecution", meta = (Output, Aggregate))` — The execution result B

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Execution/RigVMFunction_UserDefinedEvent.h` (Public)


#### struct `FRigVMFunction_UserDefinedEvent`  
`struct FRigVMFunction_UserDefinedEvent : public FRigVMStruct`  
_L14-37_
- reflection: `USTRUCT(meta=(DisplayName="User Defined Event", Category="Events", NodeColor="1, 0, 0", Keywords="Event,Entry,MyEvent"))`
- inherits: `FRigVMStruct`
- desc: User Defined Event for running custom logic
- L18 _public function_ `FRigVMFunction_UserDefinedEvent()`
- L23 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L26 _public prototype_ `virtual FString GetUnitLabel() const override;`
- L27 _public function_ `virtual FName GetEventName() const override`
- L28 _public function_ `virtual bool CanOnlyExistOnce() const override`
- L32 _public member_ `FRigVMExecutePin ExecutePin;` — `UPROPERTY(EditAnywhere, Transient, DisplayName = "Execute", Category = "UserDefinedEvent", meta = (Output))` — The execution result
- L36 _public member_ `FName EventName;` — `UPROPERTY(EditAnywhere, Transient, Category = "UserDefinedEvent", meta = (Input,Constant,DetailsOnly))` — The name of the event. Given this name the event can be invoked using the run event node.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathBase.h` (Public)


#### struct `FRigVMFunction_MathBase`  
`struct FRigVMFunction_MathBase : public FRigVMStruct`  
_L13-18_
- reflection: `USTRUCT(meta=(Abstract, NodeColor = "0.05 0.25 0.05", DocumentationPolicy="Strict"))`
- inherits: `FRigVMStruct`
- desc: The base class for all pure math nodes
- L17 _public function_ `virtual void Execute()`

#### struct `FRigVMFunction_MathMutableBase`  
`struct FRigVMFunction_MathMutableBase : public FRigVMStructMutable`  
_L24-29_
- reflection: `USTRUCT(meta=(Abstract, NodeColor = "0.05 0.25 0.05", DocumentationPolicy="Strict"))`
- inherits: `FRigVMStructMutable`
- desc: The base class for all mutable math nodes
- L28 _public function_ `virtual void Execute()`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathBool.h` (Public)


#### struct `FRigVMFunction_MathBoolBase`  
`struct FRigVMFunction_MathBoolBase : public FRigVMFunction_MathBase`  
_L12-15_
- reflection: `USTRUCT(meta=(Abstract, Category="Math|Boolean"))`
- inherits: `FRigVMFunction_MathBase`
- desc: The base class for all pure bool math nodes

#### struct `FRigVMFunction_MathBoolConstant`  
`struct FRigVMFunction_MathBoolConstant : public FRigVMFunction_MathBoolBase`  
_L21-33_
- reflection: `USTRUCT(meta=(Abstract, NoOp))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: The base class for all bool math constants
- L25 _public function_ `FRigVMFunction_MathBoolConstant()`
- L32 _public member_ `bool Value;` — `UPROPERTY(meta=(Output,Constant))` — The value of the constant

#### struct `FRigVMFunction_MathBoolUnaryOp`  
`struct FRigVMFunction_MathBoolUnaryOp : public FRigVMFunction_MathBoolBase`  
_L39-55_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: The base class for all unary bool math operations
- L43 _public function_ `FRigVMFunction_MathBoolUnaryOp()`
- L50 _public member_ `bool Value;` — `UPROPERTY(meta=(Input))` — The input value
- L54 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — The result of the operation

#### struct `FRigVMFunction_MathBoolBinaryOp`  
`struct FRigVMFunction_MathBoolBinaryOp : public FRigVMFunction_MathBoolBase`  
_L61-81_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: The base class for all binary bool math operations
- L65 _public function_ `FRigVMFunction_MathBoolBinaryOp()`
- L72 _public member_ `bool A;` — `UPROPERTY(meta=(Input))` — The first value for the operation
- L76 _public member_ `bool B;` — `UPROPERTY(meta=(Input))` — The second value for the operation
- L80 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — The resulting value

#### struct `FRigVMFunction_MathBoolBinaryAggregateOp`  
`struct FRigVMFunction_MathBoolBinaryAggregateOp : public FRigVMFunction_MathBoolBase`  
_L87-107_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: The base class for all aggregational bool math operations
- L91 _public function_ `FRigVMFunction_MathBoolBinaryAggregateOp()`
- L98 _public member_ `bool A;` — `UPROPERTY(meta=(Input, Aggregate))` — The first value for the operation
- L102 _public member_ `bool B;` — `UPROPERTY(meta=(Input, Aggregate))` — The second value for the operation
- L106 _public member_ `bool Result;` — `UPROPERTY(meta=(Output, Aggregate))` — The resulting value

#### struct `FRigVMFunction_MathBoolMake`  
`struct FRigVMFunction_MathBoolMake : public FRigVMFunction_MathBoolBase`  
_L113-130_
- reflection: `USTRUCT(meta=(DisplayName="Bool", Keywords="Make,Construct,Constant", Deprecated="5.7"))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: A boolean constant
- L117 _public function_ `FRigVMFunction_MathBoolMake()`
- L122 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L126 _public member_ `bool Value;` — `UPROPERTY(meta=(Input, Output, Constant))`
- L128 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathBoolConstTrue`  
`struct FRigVMFunction_MathBoolConstTrue : public FRigVMFunction_MathBoolConstant`  
_L136-147_
- reflection: `USTRUCT(meta=(DisplayName="True", Keywords="Yes"))`
- inherits: `FRigVMFunction_MathBoolConstant`
- desc: Returns true
- L140 _public function_ `FRigVMFunction_MathBoolConstTrue()`
- L145 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathBoolConstFalse`  
`struct FRigVMFunction_MathBoolConstFalse : public FRigVMFunction_MathBoolConstant`  
_L153-164_
- reflection: `USTRUCT(meta=(DisplayName="False", Keywords="No"))`
- inherits: `FRigVMFunction_MathBoolConstant`
- desc: Returns false
- L157 _public function_ `FRigVMFunction_MathBoolConstFalse()`
- L162 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathBoolNot`  
`struct FRigVMFunction_MathBoolNot : public FRigVMFunction_MathBoolUnaryOp`  
_L170-176_
- reflection: `USTRUCT(meta=(DisplayName="Not", TemplateName="Not", Keywords="!"))`
- inherits: `FRigVMFunction_MathBoolUnaryOp`
- desc: Returns true if the condition is false
- L174 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathBoolAnd`  
`struct FRigVMFunction_MathBoolAnd : public FRigVMFunction_MathBoolBinaryAggregateOp`  
_L182-188_
- reflection: `USTRUCT(meta=(DisplayName="And", TemplateName="And", Keywords="&&"))`
- inherits: `FRigVMFunction_MathBoolBinaryAggregateOp`
- desc: Returns true if both conditions are true
- L186 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathBoolNand`  
`struct FRigVMFunction_MathBoolNand : public FRigVMFunction_MathBoolBinaryOp`  
_L194-203_
- reflection: `USTRUCT(meta=(DisplayName="Nand", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathBoolBinaryOp`
- desc: Returns true if both conditions are false
- L198 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L201 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathBoolNand2`  
`struct FRigVMFunction_MathBoolNand2 : public FRigVMFunction_MathBoolBinaryOp`  
_L209-215_
- reflection: `USTRUCT(meta=(DisplayName="Nand", TemplateName="Nand"))`
- inherits: `FRigVMFunction_MathBoolBinaryOp`
- desc: Returns false if both conditions are true
- L213 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathBoolOr`  
`struct FRigVMFunction_MathBoolOr : public FRigVMFunction_MathBoolBinaryAggregateOp`  
_L221-227_
- reflection: `USTRUCT(meta=(DisplayName="Or", TemplateName="Or", Keywords="||"))`
- inherits: `FRigVMFunction_MathBoolBinaryAggregateOp`
- desc: Returns true if one of the conditions is true
- L225 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathBoolEquals`  
`struct FRigVMFunction_MathBoolEquals : public FRigVMFunction_MathBoolBase`  
_L233-256_
- reflection: `USTRUCT(meta=(DisplayName="Equals", TemplateName="Equals", Keywords="Same,==", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: Returns true if the value A equals B
- L236 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L239 _public function_ `FRigVMFunction_MathBoolEquals()`
- L246 _public member_ `bool A;` — `UPROPERTY(meta=(Input))`
- L249 _public member_ `bool B;` — `UPROPERTY(meta=(Input))`
- L252 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))`
- L254 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathBoolNotEquals`  
`struct FRigVMFunction_MathBoolNotEquals : public FRigVMFunction_MathBoolBase`  
_L262-285_
- reflection: `USTRUCT(meta=(DisplayName="Not Equals", TemplateName="NotEquals", Keywords="Different,!=,Xor", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: Returns true if the value A does not equal B
- L265 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L268 _public function_ `FRigVMFunction_MathBoolNotEquals()`
- L275 _public member_ `bool A;` — `UPROPERTY(meta=(Input))`
- L278 _public member_ `bool B;` — `UPROPERTY(meta=(Input))`
- L281 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))`
- L283 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathBoolToggled`  
`struct FRigVMFunction_MathBoolToggled : public FRigVMFunction_MathBoolBase`  
_L291-315_
- reflection: `USTRUCT(meta=(DisplayName="Toggled", TemplateName="Toggled", Keywords="Changed,Different"))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: Returns true if the value has changed from the last run
- L294 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L297 _public function_ `FRigVMFunction_MathBoolToggled()`
- L304 _public member_ `bool Value;` — `UPROPERTY(meta=(Input))` — The value to check / compare
- L308 _public member_ `bool Toggled;` — `UPROPERTY(meta=(Output))` — True if the input value has been toggled
- L311 _public member_ `bool Initialized;` — `UPROPERTY()`
- L314 _public member_ `bool LastValue;` — `UPROPERTY()`

#### struct `FRigVMFunction_MathBoolFlipFlop`  
`struct FRigVMFunction_MathBoolFlipFlop : public FRigVMFunction_MathBoolBase`  
_L321-354_
- reflection: `USTRUCT(meta=(DisplayName="FlipFlop", Keywords="Toggle,Changed,Different", Varying))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: Returns true and false as a sequence.
- L324 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L327 _public function_ `FRigVMFunction_MathBoolFlipFlop()`
- L336 _public member_ `bool StartValue;` — `UPROPERTY(meta=(Visible))` — The initial value to use for the flag
- L343 _public member_ `float Duration;` — `UPROPERTY(meta = (Input))` — The duration in seconds at which the result won't change. Use 0 for a different result every time.
- L347 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — The resulting value
- L350 _public member_ `bool LastValue;` — `UPROPERTY()`
- L353 _public member_ `float TimeLeft;` — `UPROPERTY()`

#### struct `FRigVMFunction_MathBoolOnce`  
`struct FRigVMFunction_MathBoolOnce : public FRigVMFunction_MathBoolBase`  
_L360-389_
- reflection: `USTRUCT(meta=(DisplayName="Once", Keywords="FlipFlop,Toggle,Changed,Different", Varying))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: Returns true once the first time this node is hit
- L363 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L366 _public function_ `FRigVMFunction_MathBoolOnce()`
- L378 _public member_ `float Duration;` — `UPROPERTY(meta = (Visible))` — The duration in seconds at which the result is true Use 0 for a different result every time.
- L382 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — The resulting value - true once the first time this node is hit
- L385 _public member_ `bool LastValue;` — `UPROPERTY()`
- L388 _public member_ `float TimeLeft;` — `UPROPERTY()`

#### struct `FRigVMFunction_MathBoolToFloat`  
`struct FRigVMFunction_MathBoolToFloat : public FRigVMFunction_MathBoolBase`  
_L395-414_
- reflection: `USTRUCT(meta=(DisplayName="To Float", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext"))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: Turns the given bool into a float value
- L398 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L401 _public function_ `FRigVMFunction_MathBoolToFloat()`
- L409 _public member_ `bool Value;` — `UPROPERTY(meta = (Input))` — The bool value to convert
- L413 _public member_ `float Result;` — `UPROPERTY(meta= (Output))` — The resulting float number (0 or 1)

#### struct `FRigVMFunction_MathBoolToInteger`  
`struct FRigVMFunction_MathBoolToInteger : public FRigVMFunction_MathBoolBase`  
_L420-439_
- reflection: `USTRUCT(meta=(DisplayName="To Integer", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext"))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: Turns the given bool into an integer value
- L423 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L426 _public function_ `FRigVMFunction_MathBoolToInteger()`
- L434 _public member_ `bool Value;` — `UPROPERTY(meta = (Input))` — The bool value to convert
- L438 _public member_ `int32 Result;` — `UPROPERTY(meta= (Output))` — The resulting int number (0 or 1)

#### struct `FRigVMFunction_MathBoolAny`  
`struct FRigVMFunction_MathBoolAny : public FRigVMFunction_MathBoolBase`  
_L445-471_
- reflection: `USTRUCT(meta = (DisplayName = "Any", Keywords = "Any"))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: Returns true if any item in the array is true
- L449 _public function_ `FRigVMFunction_MathBoolAny()`
- L456 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L461 _public member_ `TArray<bool> Array;` — `UPROPERTY(meta = (Input))` — The input array
- L465 _public member_ `bool Result;` — `UPROPERTY(meta = (Output))` — The resulting value. False if input array is empty
- L469 _public member_ `bool IsEmpty;` — `UPROPERTY(meta = (Output))` — True if the array is empty

#### struct `FRigVMFunction_MathBoolAll`  
`struct FRigVMFunction_MathBoolAll : public FRigVMFunction_MathBoolBase`  
_L477-503_
- reflection: `USTRUCT(meta = (DisplayName = "All", Keywords = "All"))`
- inherits: `FRigVMFunction_MathBoolBase`
- desc: Returns true if all the items in the array are true
- L481 _public function_ `FRigVMFunction_MathBoolAll()`
- L488 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L493 _public member_ `TArray<bool> Array;` — `UPROPERTY(meta = (Input))` — The input array
- L497 _public member_ `bool Result;` — `UPROPERTY(meta = (Output))` — The resulting value. True if input array is empty
- L501 _public member_ `bool IsEmpty;` — `UPROPERTY(meta = (Output))` — True if the array is empty

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathBox.h` (Public)


#### struct `FRigVMFunction_MathBoxBase`  
`struct FRigVMFunction_MathBoxBase : public FRigVMFunction_MathBase`  
_L13-16_
- reflection: `USTRUCT(meta=(Abstract, Category="Math|Box", MenuDescSuffix="(Box)"))`
- inherits: `FRigVMFunction_MathBase`
- desc: The base class for all pure box math nodes

#### struct `FRigVMFunction_MathBoxFromArray`  
`struct FRigVMFunction_MathBoxFromArray : public FRigVMFunction_MathBoxBase`  
_L22-59_
- reflection: `USTRUCT(meta = (DisplayName = "Box from Array", Keywords = "ArrayBounds,CreateBox,CreateBoundingBox,NewBox,NewBoundingBoxMakeBox,MakeBoundingBox,BoundingBox,Bbox,Bounds"))`
- inherits: `FRigVMFunction_MathBoxBase`
- desc: Returns bounding box of the given array of positions
- L26 _public function_ `FRigVMFunction_MathBoxFromArray()`
- L33 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L38 _public member_ `TArray<FVector> Array;` — `UPROPERTY(meta = (Input))` — The array of input positions
- L42 _public member_ `FBox Box;` — `UPROPERTY(meta = (Output))` — The resulting bounding box
- L46 _public member_ `FVector Minimum;` — `UPROPERTY(meta = (Output))` — The resulting minimum value of the bounding box
- L50 _public member_ `FVector Maximum;` — `UPROPERTY(meta = (Output))` — The resulting maximum value of the bounding box
- L54 _public member_ `FVector Center;` — `UPROPERTY(meta = (Output))` — The resulting center value of the bounding box
- L58 _public member_ `FVector Size;` — `UPROPERTY(meta = (Output))` — The resulting size value of the bounding box

#### struct `FRigVMFunction_MathBoxIsValid`  
`struct FRigVMFunction_MathBoxIsValid : public FRigVMFunction_MathBoxBase`  
_L65-86_
- reflection: `USTRUCT(meta = (DisplayName = "Is Box Valid", Keywords = "IsValid,HasVolume,ContainsPoints,Bounds,BoundingBox,Bbox"))`
- inherits: `FRigVMFunction_MathBoxBase`
- desc: Returns true if the box has any content / is valid
- L69 _public function_ `FRigVMFunction_MathBoxIsValid()`
- L76 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L81 _public member_ `FBox Box;` — `UPROPERTY(meta = (Input))` — The box to check
- L85 _public member_ `bool Valid;` — `UPROPERTY(meta = (Output))` — Returns true if the box has any content / is valid

#### struct `FRigVMFunction_MathBoxGetCenter`  
`struct FRigVMFunction_MathBoxGetCenter : public FRigVMFunction_MathBoxBase`  
_L92-113_
- reflection: `USTRUCT(meta = (DisplayName = "Get Box Center", Keywords = "Middle,Origin,Bounds,BoundingBox,Bbox"))`
- inherits: `FRigVMFunction_MathBoxBase`
- desc: Returns the center of a bounding box
- L96 _public function_ `FRigVMFunction_MathBoxGetCenter()`
- L103 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L108 _public member_ `FBox Box;` — `UPROPERTY(meta = (Input))` — The box to retrieve the center for
- L112 _public member_ `FVector Center;` — `UPROPERTY(meta = (Output))` — The center of the box

#### struct `FRigVMFunction_MathBoxGetSize`  
`struct FRigVMFunction_MathBoxGetSize : public FRigVMFunction_MathBoxBase`  
_L119-144_
- reflection: `USTRUCT(meta = (DisplayName = "Get Box Size", Keywords = "Middle,Origin,Bounds,BoundingBox,Bbox"))`
- inherits: `FRigVMFunction_MathBoxBase`
- desc: Returns the size of a bounding box
- L123 _public function_ `FRigVMFunction_MathBoxGetSize()`
- L130 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L135 _public member_ `FBox Box;` — `UPROPERTY(meta = (Input))` — The box to retrieve the size for
- L139 _public member_ `FVector Size;` — `UPROPERTY(meta = (Output))` — the overall size of the box
- L143 _public member_ `FVector Extent;` — `UPROPERTY(meta = (Output))` — the half size of the box

#### struct `FRigVMFunction_MathBoxShift`  
`struct FRigVMFunction_MathBoxShift : public FRigVMFunction_MathBoxBase`  
_L150-175_
- reflection: `USTRUCT(meta = (DisplayName = "Shift Box", Keywords = "Bbox,Translate,Move,BoundingBox"))`
- inherits: `FRigVMFunction_MathBoxBase`
- desc: Move the box by a certain amount
- L154 _public function_ `FRigVMFunction_MathBoxShift()`
- L161 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L166 _public member_ `FBox Box;` — `UPROPERTY(meta = (Input))` — the box to move
- L170 _public member_ `FVector Amount;` — `UPROPERTY(meta = (Input))` — the amount / vector to shift the box by
- L174 _public member_ `FBox Result;` — `UPROPERTY(meta = (Output))` — The resulting moved box

#### struct `FRigVMFunction_MathBoxMoveTo`  
`struct FRigVMFunction_MathBoxMoveTo : public FRigVMFunction_MathBoxBase`  
_L181-206_
- reflection: `USTRUCT(meta = (DisplayName = "Move Box To", Keywords = "Bbox,Translate,Move,BoundingBox"))`
- inherits: `FRigVMFunction_MathBoxBase`
- desc: Moves the center of the box to a new location
- L185 _public function_ `FRigVMFunction_MathBoxMoveTo()`
- L192 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L197 _public member_ `FBox Box;` — `UPROPERTY(meta = (Input))` — the box to move
- L201 _public member_ `FVector Center;` — `UPROPERTY(meta = (Input))` — the new center for the box
- L205 _public member_ `FBox Result;` — `UPROPERTY(meta = (Output))` — The resulting moved box

#### struct `FRigVMFunction_MathBoxExpand`  
`struct FRigVMFunction_MathBoxExpand : public FRigVMFunction_MathBoxBase`  
_L212-237_
- reflection: `USTRUCT(meta = (DisplayName = "Expand Box", Keywords = "Bbox,Scale,Grow,Shrink,BoundingBox"))`
- inherits: `FRigVMFunction_MathBoxBase`
- desc: Expands the size of the box by a given amount
- L216 _public function_ `FRigVMFunction_MathBoxExpand()`
- L223 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L228 _public member_ `FBox Box;` — `UPROPERTY(meta = (Input))` — the box to expand
- L232 _public member_ `FVector Amount;` — `UPROPERTY(meta = (Input))` — the amount to grow / shrink the box by
- L236 _public member_ `FBox Result;` — `UPROPERTY(meta = (Output))` — the resulting expanded box

#### struct `FRigVMFunction_MathBoxTransform`  
`struct FRigVMFunction_MathBoxTransform : public FRigVMFunction_MathBoxBase`  
_L243-268_
- reflection: `USTRUCT(meta = (DisplayName = "Transform Box", Keywords = "Bbox,BoundingBox"))`
- inherits: `FRigVMFunction_MathBoxBase`
- desc: Transforms the box by a given transform
- L247 _public function_ `FRigVMFunction_MathBoxTransform()`
- L254 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L259 _public member_ `FBox Box;` — `UPROPERTY(meta = (Input))` — the box to transform
- L263 _public member_ `FTransform Transform;` — `UPROPERTY(meta = (Input))` — the transform to apply to the box
- L267 _public member_ `FBox Result;` — `UPROPERTY(meta = (Output))` — the resulting transformed box

#### struct `FRigVMFunction_MathBoxGetDistance`  
`struct FRigVMFunction_MathBoxGetDistance : public FRigVMFunction_MathBoxBase`  
_L274-310_
- reflection: `USTRUCT(meta = (DisplayName = "Get Distance to Box", Keywords = "Bbox,Closest,BoundingBox"))`
- inherits: `FRigVMFunction_MathBoxBase`
- desc: Returns the distance to a given box
- L278 _public function_ `FRigVMFunction_MathBoxGetDistance()`
- L288 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L293 _public member_ `FBox Box;` — `UPROPERTY(meta = (Input))` — The box to measure the distance to
- L297 _public member_ `FVector Position;` — `UPROPERTY(meta = (Input))` — The position to measure the distance to
- L301 _public member_ `bool Square;` — `UPROPERTY(meta = (Input))` — if true the distance will be returned square
- L305 _public member_ `bool Valid;` — `UPROPERTY(meta = (Output))` — Returns true if the computed distance is valid
- L309 _public member_ `float Distance;` — `UPROPERTY(meta = (Output))` — The distance between the box and the position

#### struct `FRigVMFunction_MathBoxIsInside`  
`struct FRigVMFunction_MathBoxIsInside : public FRigVMFunction_MathBoxBase`  
_L316-342_
- reflection: `USTRUCT(meta = (DisplayName = "Is Inside Box", Keywords = "Bbox,Contains,Encompasses,BoundingBox"))`
- inherits: `FRigVMFunction_MathBoxBase`
- desc: Returns true if a point is inside a given box
- L320 _public function_ `FRigVMFunction_MathBoxIsInside()`
- L328 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L333 _public member_ `FBox Box;` — `UPROPERTY(meta = (Input))` — The box to test
- L337 _public member_ `FVector Position;` — `UPROPERTY(meta = (Input))` — The position to check for
- L341 _public member_ `bool Result;` — `UPROPERTY(meta = (Output))` — Returns true if the given point is inside the given box

#### struct `FRigVMFunction_MathBoxGetVolume`  
`struct FRigVMFunction_MathBoxGetVolume : public FRigVMFunction_MathBoxBase`  
_L349-370_
- reflection: `USTRUCT(meta = (DisplayName = "Get Box Volume", Keywords = "Bbox,BoundingBox"))`
- inherits: `FRigVMFunction_MathBoxBase`
- desc: Returns the volume of a given box
- L353 _public function_ `FRigVMFunction_MathBoxGetVolume()`
- L360 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L365 _public member_ `FBox Box;` — `UPROPERTY(meta = (Input))` — The box to retrieve the volume for
- L369 _public member_ `float Volume;` — `UPROPERTY(meta = (Output))` — The volume of the box

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathColor.h` (Public)


#### struct `FRigVMFunction_MathColorBase`  
`struct FRigVMFunction_MathColorBase : public FRigVMFunction_MathBase`  
_L12-15_
- reflection: `USTRUCT(meta=(Abstract, Category="Math|Color", MenuDescSuffix="(Color)"))`
- inherits: `FRigVMFunction_MathBase`
- desc: The base class for all pure color math nodes

#### struct `FRigVMFunction_MathColorBinaryAggregateOp`  
`struct FRigVMFunction_MathColorBinaryAggregateOp : public FRigVMFunction_MathColorBase`  
_L21-41_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathColorBase`
- desc: The base class for all aggregational color math operations
- L25 _public function_ `FRigVMFunction_MathColorBinaryAggregateOp()`
- L32 _public member_ `FLinearColor A;` — `UPROPERTY(meta=(Input, Aggregate))` — The first value for the operation
- L36 _public member_ `FLinearColor B;` — `UPROPERTY(meta=(Input, Aggregate))` — The second value for the operation
- L40 _public member_ `FLinearColor Result;` — `UPROPERTY(meta=(Output, Aggregate))` — The resulting value

#### struct `FRigVMFunction_MathColorMake`  
`struct FRigVMFunction_MathColorMake : public FRigVMFunction_MathColorBase`  
_L47-77_
- reflection: `USTRUCT(meta=(DisplayName="Make Color", Keywords="Make,Construct,Constant", Deprecated="5.7"))`
- inherits: `FRigVMFunction_MathColorBase`
- desc: Makes a color from its components
- L50 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L53 _public function_ `FRigVMFunction_MathColorMake()`
- L61 _public member_ `float R;` — `UPROPERTY(meta=(Input))`
- L64 _public member_ `float G;` — `UPROPERTY(meta=(Input))`
- L67 _public member_ `float B;` — `UPROPERTY(meta=(Input))`
- L70 _public member_ `float A;` — `UPROPERTY(meta=(Input))`
- L73 _public member_ `FLinearColor Result;` — `UPROPERTY(meta=(Output))`
- L75 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathColorFromFloat`  
`struct FRigVMFunction_MathColorFromFloat : public FRigVMFunction_MathColorBase`  
_L83-102_
- reflection: `USTRUCT(meta=(DisplayName="From Float", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathColorBase`
- desc: Makes a color from a single float
- L86 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L89 _public function_ `FRigVMFunction_MathColorFromFloat()`
- L97 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The float value to convert to a color
- L101 _public member_ `FLinearColor Result;` — `UPROPERTY(meta=(Output))` — The resulting color

#### struct `FRigVMFunction_MathColorFromDouble`  
`struct FRigVMFunction_MathColorFromDouble : public FRigVMFunction_MathColorBase`  
_L108-127_
- reflection: `USTRUCT(meta=(DisplayName="From Double", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathColorBase`
- desc: Makes a color from a single double
- L111 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L114 _public function_ `FRigVMFunction_MathColorFromDouble()`
- L122 _public member_ `double Value;` — `UPROPERTY(meta=(Input))` — The double value to convert to a color
- L126 _public member_ `FLinearColor Result;` — `UPROPERTY(meta=(Output))` — The resulting color

#### struct `FRigVMFunction_MathColorAdd`  
`struct FRigVMFunction_MathColorAdd : public FRigVMFunction_MathColorBinaryAggregateOp`  
_L133-139_
- reflection: `USTRUCT(meta=(DisplayName="Add", TemplateName="Add", Keywords="Sum,+"))`
- inherits: `FRigVMFunction_MathColorBinaryAggregateOp`
- desc: Returns the sum of the two values
- L137 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathColorSub`  
`struct FRigVMFunction_MathColorSub : public FRigVMFunction_MathColorBinaryAggregateOp`  
_L145-151_
- reflection: `USTRUCT(meta=(DisplayName="Subtract", TemplateName="Subtract", Keywords="-"))`
- inherits: `FRigVMFunction_MathColorBinaryAggregateOp`
- desc: Returns the difference of the two values
- L149 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathColorMul`  
`struct FRigVMFunction_MathColorMul : public FRigVMFunction_MathColorBinaryAggregateOp`  
_L157-168_
- reflection: `USTRUCT(meta=(DisplayName="Multiply", TemplateName="Multiply", Keywords="Product,*"))`
- inherits: `FRigVMFunction_MathColorBinaryAggregateOp`
- desc: Returns the product of the two values
- L161 _public function_ `FRigVMFunction_MathColorMul()`
- L166 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathColorLerp`  
`struct FRigVMFunction_MathColorLerp : public FRigVMFunction_MathColorBase`  
_L174-203_
- reflection: `USTRUCT(meta=(DisplayName="Interpolate", TemplateName="Interpolate", Keywords="Lerp,Mix,Blend"))`
- inherits: `FRigVMFunction_MathColorBase`
- desc: Linearly interpolates between A and B using the ratio T
- L178 _public function_ `FRigVMFunction_MathColorLerp()`
- L185 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L190 _public member_ `FLinearColor A;` — `UPROPERTY(meta=(Input))` — The first color to interpolate from
- L194 _public member_ `FLinearColor B;` — `UPROPERTY(meta=(Input))` — The second color to interpolate to
- L198 _public member_ `float T;` — `UPROPERTY(meta=(Input, UIMin = "0", UIMax = "1"))` — The blend value for the interpolation
- L202 _public member_ `FLinearColor Result;` — `UPROPERTY(meta=(Output))` — The resulting interpolated color

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathDouble.h` (Public)


#### struct `FRigVMFunction_MathDoubleBase`  
`struct FRigVMFunction_MathDoubleBase : public FRigVMFunction_MathBase`  
_L12-15_
- reflection: `USTRUCT(meta=(Abstract, Category="Math|Double", MenuDescSuffix="(Double)"))`
- inherits: `FRigVMFunction_MathBase`
- desc: The base class for all pure double math nodes

#### struct `FRigVMFunction_MathDoubleConstant`  
`struct FRigVMFunction_MathDoubleConstant : public FRigVMFunction_MathDoubleBase`  
_L21-33_
- reflection: `USTRUCT(meta=(Abstract, NoOp))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: The base class for all double math constants
- L25 _public function_ `FRigVMFunction_MathDoubleConstant()`
- L32 _public member_ `double Value;` — `UPROPERTY(meta=(Output,Constant))` — The value of the constant

#### struct `FRigVMFunction_MathDoubleUnaryOp`  
`struct FRigVMFunction_MathDoubleUnaryOp : public FRigVMFunction_MathDoubleBase`  
_L39-55_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: The base class for all unary double math operations
- L43 _public function_ `FRigVMFunction_MathDoubleUnaryOp()`
- L50 _public member_ `double Value;` — `UPROPERTY(meta=(Input))` — The input value
- L54 _public member_ `double Result;` — `UPROPERTY(meta=(Output))` — The result of the operation

#### struct `FRigVMFunction_MathDoubleBinaryOp`  
`struct FRigVMFunction_MathDoubleBinaryOp : public FRigVMFunction_MathDoubleBase`  
_L61-81_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: The base class for all binary double math operations
- L65 _public function_ `FRigVMFunction_MathDoubleBinaryOp()`
- L72 _public member_ `double A;` — `UPROPERTY(meta=(Input))` — The first value for the operation
- L76 _public member_ `double B;` — `UPROPERTY(meta=(Input))` — The second value for the operation
- L80 _public member_ `double Result;` — `UPROPERTY(meta=(Output))` — The resulting value

#### struct `FRigVMFunction_MathDoubleBinaryAggregateOp`  
`struct FRigVMFunction_MathDoubleBinaryAggregateOp : public FRigVMFunction_MathDoubleBase`  
_L87-107_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: The base class for all aggregational double math operations
- L91 _public function_ `FRigVMFunction_MathDoubleBinaryAggregateOp()`
- L98 _public member_ `double A;` — `UPROPERTY(meta=(Input, Aggregate))` — The first value for the operation
- L102 _public member_ `double B;` — `UPROPERTY(meta=(Input, Aggregate))` — The second value for the operation
- L106 _public member_ `double Result;` — `UPROPERTY(meta=(Output, Aggregate))` — The resulting value

#### struct `FRigVMFunction_MathDoubleMake`  
`struct FRigVMFunction_MathDoubleMake : public FRigVMFunction_MathDoubleBase`  
_L113-130_
- reflection: `USTRUCT(meta=(DisplayName="Double", Keywords="Make,Construct,Constant", Deprecated="5.7"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: A double constant
- L117 _public function_ `FRigVMFunction_MathDoubleMake()`
- L122 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L126 _public member_ `double Value;` — `UPROPERTY(meta=(Input, Output, Constant))`
- L128 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathDoubleConstPi`  
`struct FRigVMFunction_MathDoubleConstPi : public FRigVMFunction_MathDoubleConstant`  
_L136-147_
- reflection: `USTRUCT(meta=(DisplayName="Pi", TemplateName="Pi"))`
- inherits: `FRigVMFunction_MathDoubleConstant`
- desc: Returns PI
- L140 _public function_ `FRigVMFunction_MathDoubleConstPi()`
- L145 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleConstHalfPi`  
`struct FRigVMFunction_MathDoubleConstHalfPi : public FRigVMFunction_MathDoubleConstant`  
_L153-164_
- reflection: `USTRUCT(meta=(DisplayName="Half Pi", TemplateName="HalfPi"))`
- inherits: `FRigVMFunction_MathDoubleConstant`
- desc: Returns PI * 0.5
- L157 _public function_ `FRigVMFunction_MathDoubleConstHalfPi()`
- L162 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleConstTwoPi`  
`struct FRigVMFunction_MathDoubleConstTwoPi : public FRigVMFunction_MathDoubleConstant`  
_L170-181_
- reflection: `USTRUCT(meta=(DisplayName="Two Pi", TemplateName="TwoPi", Keywords="Tau"))`
- inherits: `FRigVMFunction_MathDoubleConstant`
- desc: Returns PI * 2.0
- L174 _public function_ `FRigVMFunction_MathDoubleConstTwoPi()`
- L179 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleConstE`  
`struct FRigVMFunction_MathDoubleConstE : public FRigVMFunction_MathDoubleConstant`  
_L187-198_
- reflection: `USTRUCT(meta=(DisplayName="E", TemplateName="E", Keywords="Euler"))`
- inherits: `FRigVMFunction_MathDoubleConstant`
- desc: Returns E
- L191 _public function_ `FRigVMFunction_MathDoubleConstE()`
- L196 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleAdd`  
`struct FRigVMFunction_MathDoubleAdd : public FRigVMFunction_MathDoubleBinaryAggregateOp`  
_L204-210_
- reflection: `USTRUCT(meta=(DisplayName="Add", TemplateName="Add", Keywords="Sum,+"))`
- inherits: `FRigVMFunction_MathDoubleBinaryAggregateOp`
- desc: Returns the sum of the two values
- L208 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleSub`  
`struct FRigVMFunction_MathDoubleSub : public FRigVMFunction_MathDoubleBinaryAggregateOp`  
_L216-222_
- reflection: `USTRUCT(meta=(DisplayName="Subtract", TemplateName="Subtract", Keywords="-"))`
- inherits: `FRigVMFunction_MathDoubleBinaryAggregateOp`
- desc: Returns the difference of the two values
- L220 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleMul`  
`struct FRigVMFunction_MathDoubleMul : public FRigVMFunction_MathDoubleBinaryAggregateOp`  
_L228-240_
- reflection: `USTRUCT(meta=(DisplayName="Multiply", TemplateName="Multiply", Keywords="Product,*"))`
- inherits: `FRigVMFunction_MathDoubleBinaryAggregateOp`
- desc: Returns the product of the two values
- L232 _public function_ `FRigVMFunction_MathDoubleMul()`
- L238 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleDiv`  
`struct FRigVMFunction_MathDoubleDiv : public FRigVMFunction_MathDoubleBinaryOp`  
_L246-257_
- reflection: `USTRUCT(meta=(DisplayName="Divide", TemplateName="Divide", Keywords="Division,Divisor,/"))`
- inherits: `FRigVMFunction_MathDoubleBinaryOp`
- desc: Returns the division of the two values
- L250 _public function_ `FRigVMFunction_MathDoubleDiv()`
- L255 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleMod`  
`struct FRigVMFunction_MathDoubleMod : public FRigVMFunction_MathDoubleBinaryOp`  
_L263-275_
- reflection: `USTRUCT(meta=(DisplayName="Modulo", TemplateName="Modulo", Keywords="%,fmod"))`
- inherits: `FRigVMFunction_MathDoubleBinaryOp`
- desc: Returns the modulo of the two values
- L267 _public function_ `FRigVMFunction_MathDoubleMod()`
- L273 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleMin`  
`struct FRigVMFunction_MathDoubleMin : public FRigVMFunction_MathDoubleBinaryAggregateOp`  
_L281-287_
- reflection: `USTRUCT(meta=(DisplayName="Minimum", TemplateName="Minimum"))`
- inherits: `FRigVMFunction_MathDoubleBinaryAggregateOp`
- desc: Returns the smaller of the two values
- L285 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleMax`  
`struct FRigVMFunction_MathDoubleMax : public FRigVMFunction_MathDoubleBinaryAggregateOp`  
_L293-299_
- reflection: `USTRUCT(meta=(DisplayName="Maximum", TemplateName="Maximum"))`
- inherits: `FRigVMFunction_MathDoubleBinaryAggregateOp`
- desc: Returns the larger of the two values
- L297 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoublePow`  
`struct FRigVMFunction_MathDoublePow : public FRigVMFunction_MathDoubleBinaryOp`  
_L305-317_
- reflection: `USTRUCT(meta=(DisplayName="Power", TemplateName="Power"))`
- inherits: `FRigVMFunction_MathDoubleBinaryOp`
- desc: Returns the value of A raised to the power of B.
- L309 _public function_ `FRigVMFunction_MathDoublePow()`
- L315 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleSqrt`  
`struct FRigVMFunction_MathDoubleSqrt : public FRigVMFunction_MathDoubleUnaryOp`  
_L323-329_
- reflection: `USTRUCT(meta=(DisplayName="Sqrt", TemplateName="Sqrt", Keywords="Root,Square"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns the square root of the given value
- L327 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleNegate`  
`struct FRigVMFunction_MathDoubleNegate : public FRigVMFunction_MathDoubleUnaryOp`  
_L335-341_
- reflection: `USTRUCT(meta=(DisplayName="Negate", TemplateName="Negate", Keywords="-,Abs"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns the negative value
- L339 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleAbs`  
`struct FRigVMFunction_MathDoubleAbs : public FRigVMFunction_MathDoubleUnaryOp`  
_L347-353_
- reflection: `USTRUCT(meta=(DisplayName="Absolute", TemplateName="Absolute", Keywords="Abs,Neg"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns the absolute (positive) value
- L351 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleOneMinus`  
`struct FRigVMFunction_MathDoubleOneMinus : public FRigVMFunction_MathDoubleUnaryOp`  
_L360-366_
- reflection: `USTRUCT(meta=(DisplayName="One Minus", TemplateName="OneMinus", Keywords="Invert,Inverse,Subtract,One,Minus,Negate,Flip"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns one minus the input value (1 - x). Commonly used for inverting normalized values such as blend weights.
- L364 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleFloor`  
`struct FRigVMFunction_MathDoubleFloor : public FRigVMFunction_MathDoubleBase`  
_L372-396_
- reflection: `USTRUCT(meta=(DisplayName="Floor", TemplateName="Floor", Keywords="Round"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns the closest lower full number (integer) of the value
- L376 _public function_ `FRigVMFunction_MathDoubleFloor()`
- L382 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L387 _public member_ `double Value;` — `UPROPERTY(meta=(Input))` — The input value to apply the floor to
- L391 _public member_ `double Result;` — `UPROPERTY(meta=(Output))` — The resulting closest lower full number (integer) of the input value
- L395 _public member_ `int32 Int;` — `UPROPERTY(meta=(Output))` — The result as an integer value

#### struct `FRigVMFunction_MathDoubleCeil`  
`struct FRigVMFunction_MathDoubleCeil : public FRigVMFunction_MathDoubleBase`  
_L402-426_
- reflection: `USTRUCT(meta=(DisplayName="Ceiling", TemplateName="Ceiling", Keywords="Round"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns the closest higher full number (integer) of the value
- L406 _public function_ `FRigVMFunction_MathDoubleCeil()`
- L412 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L417 _public member_ `double Value;` — `UPROPERTY(meta=(Input))` — The input value to apply the ceiling to
- L421 _public member_ `double Result;` — `UPROPERTY(meta=(Output))` — The resulting closest higher full number (integer) of the input value
- L425 _public member_ `int32 Int;` — `UPROPERTY(meta=(Output))` — The result as an integer value

#### struct `FRigVMFunction_MathDoubleRound`  
`struct FRigVMFunction_MathDoubleRound : public FRigVMFunction_MathDoubleBase`  
_L432-456_
- reflection: `USTRUCT(meta=(DisplayName="Round", TemplateName="Round"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns the rounded value of the given double number
- L436 _public function_ `FRigVMFunction_MathDoubleRound()`
- L442 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L447 _public member_ `double Value;` — `UPROPERTY(meta=(Input))` — The input value to round
- L451 _public member_ `double Result;` — `UPROPERTY(meta=(Output))` — The rounded value of the given double number
- L455 _public member_ `int32 Int;` — `UPROPERTY(meta=(Output))` — The result as an integer

#### struct `FRigVMFunction_MathDoubleToInt`  
`struct FRigVMFunction_MathDoubleToInt : public FRigVMFunction_MathDoubleBase`  
_L462-482_
- reflection: `USTRUCT(meta=(DisplayName="To Int", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns the double cast to an int (this uses floor)
- L466 _public function_ `FRigVMFunction_MathDoubleToInt()`
- L472 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L477 _public member_ `double Value;` — `UPROPERTY(meta=(Input))` — The input value to floor to an int
- L481 _public member_ `int32 Result;` — `UPROPERTY(meta=(Output))` — The resulting (floored) integer

#### struct `FRigVMFunction_MathDoubleToFloat`  
`struct FRigVMFunction_MathDoubleToFloat : public FRigVMFunction_MathDoubleBase`  
_L488-508_
- reflection: `USTRUCT(meta=(DisplayName="To Float", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns the double cast to a float
- L492 _public function_ `FRigVMFunction_MathDoubleToFloat()`
- L498 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L503 _public member_ `double Value;` — `UPROPERTY(meta=(Input))` — The double number to cast to float
- L507 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting float number

#### struct `FRigVMFunction_MathDoubleSign`  
`struct FRigVMFunction_MathDoubleSign : public FRigVMFunction_MathDoubleUnaryOp`  
_L514-520_
- reflection: `USTRUCT(meta=(DisplayName="Sign", TemplateName="Sign"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns the sign of the value (+1 for >= 0.0, -1 for < 0.0)
- L518 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleClamp`  
`struct FRigVMFunction_MathDoubleClamp : public FRigVMFunction_MathDoubleBase`  
_L526-553_
- reflection: `USTRUCT(meta=(DisplayName="Clamp", TemplateName="Clamp", Keywords="Range,Remap"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Clamps the given value within the range provided by minimum and maximum
- L530 _public function_ `FRigVMFunction_MathDoubleClamp()`
- L535 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L540 _public member_ `double Value;` — `UPROPERTY(meta=(Input))` — The number to clamp
- L544 _public member_ `double Minimum;` — `UPROPERTY(meta=(Input))` — The Minimum for the resulting range
- L548 _public member_ `double Maximum;` — `UPROPERTY(meta=(Input))` — The Maximum for the resulting range
- L552 _public member_ `double Result;` — `UPROPERTY(meta=(Output))` — The resulting clamped value

#### struct `FRigVMFunction_MathDoubleWrap`  
`struct FRigVMFunction_MathDoubleWrap : public FRigVMFunction_MathDoubleBase`  
_L560-589_
- reflection: `USTRUCT(meta = (DisplayName = "Wrap", TemplateName = "Wrap", Keywords = "Range,Remap"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Wraps the given value to be within minimum and maximum, inclusive When the value can wrap to both Min and Max, it will wrap to Min if it lies below the range and wrap to Max if it is above the range.
- L564 _public function_ `FRigVMFunction_MathDoubleWrap()`
- L571 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L576 _public member_ `double Value;` — `UPROPERTY(meta = (Input))` — The number to wrap
- L580 _public member_ `double Minimum;` — `UPROPERTY(meta = (Input))` — The Minimum for the resulting range
- L584 _public member_ `double Maximum;` — `UPROPERTY(meta = (Input))` — The Maximum for the resulting range
- L588 _public member_ `double Result;` — `UPROPERTY(meta = (Output))` — The resulting wrapped value

#### struct `FRigVMFunction_MathDoubleLerp`  
`struct FRigVMFunction_MathDoubleLerp : public FRigVMFunction_MathDoubleBase`  
_L595-623_
- reflection: `USTRUCT(meta=(DisplayName="Interpolate", TemplateName="Interpolate", Keywords="Lerp,Mix,Blend"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Linearly interpolates between A and B using the ratio T
- L599 _public function_ `FRigVMFunction_MathDoubleLerp()`
- L605 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L610 _public member_ `double A;` — `UPROPERTY(meta=(Input))` — The first value to interpolate from
- L614 _public member_ `double B;` — `UPROPERTY(meta=(Input))` — The second value to interpolate to
- L618 _public member_ `double T;` — `UPROPERTY(meta=(Input, UIMin = "0", UIMax = "1"))` — The blend value for the interpolation
- L622 _public member_ `double Result;` — `UPROPERTY(meta=(Output))` — The resulting interpolated value

#### struct `FRigVMFunction_MathDoubleRemap`  
`struct FRigVMFunction_MathDoubleRemap : public FRigVMFunction_MathDoubleBase`  
_L629-670_
- reflection: `USTRUCT(meta=(DisplayName="Remap", TemplateName="Remap", Keywords="Rescale,Scale"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Remaps the given value from a source range to a target range.
- L633 _public function_ `FRigVMFunction_MathDoubleRemap()`
- L640 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L645 _public member_ `double Value;` — `UPROPERTY(meta=(Input))` — The input value to remap
- L649 _public member_ `double SourceMinimum;` — `UPROPERTY(meta=(Input))` — The minimum of the range of the input / source value
- L653 _public member_ `double SourceMaximum;` — `UPROPERTY(meta=(Input))` — The maximum of the range of the input / source value
- L657 _public member_ `double TargetMinimum;` — `UPROPERTY(meta=(Input))` — The minimum of the range of the output / target value
- L661 _public member_ `double TargetMaximum;` — `UPROPERTY(meta=(Input))` — The maximum of the range of the output / target value
- L665 _public member_ `bool bClamp;` — `UPROPERTY(meta=(Input))` — If set to true the result is clamped to the target range
- L669 _public member_ `double Result;` — `UPROPERTY(meta=(Output))` — The resulting remapped value

#### struct `FRigVMFunction_MathDoubleEquals`  
`struct FRigVMFunction_MathDoubleEquals : public FRigVMFunction_MathDoubleBase`  
_L676-699_
- reflection: `USTRUCT(meta=(DisplayName="Equals", TemplateName="Equals", Keywords="Same,==", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns true if the value A equals B
- L679 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L682 _public function_ `FRigVMFunction_MathDoubleEquals()`
- L689 _public member_ `double A;` — `UPROPERTY(meta=(Input))`
- L692 _public member_ `double B;` — `UPROPERTY(meta=(Input))`
- L695 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))`
- L697 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathDoubleNotEquals`  
`struct FRigVMFunction_MathDoubleNotEquals : public FRigVMFunction_MathDoubleBase`  
_L705-728_
- reflection: `USTRUCT(meta=(DisplayName="Not Equals", TemplateName="NotEquals", Keywords="Different,!=", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns true if the value A does not equal B
- L708 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L711 _public function_ `FRigVMFunction_MathDoubleNotEquals()`
- L718 _public member_ `double A;` — `UPROPERTY(meta=(Input))`
- L721 _public member_ `double B;` — `UPROPERTY(meta=(Input))`
- L724 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))`
- L726 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathDoubleGreater`  
`struct FRigVMFunction_MathDoubleGreater : public FRigVMFunction_MathDoubleBase`  
_L734-758_
- reflection: `USTRUCT(meta=(DisplayName="Greater", TemplateName="Greater", Keywords="Larger,Bigger,>"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns true if the value A is greater than B
- L738 _public function_ `FRigVMFunction_MathDoubleGreater()`
- L744 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L749 _public member_ `double A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L753 _public member_ `double B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L757 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is greater than B

#### struct `FRigVMFunction_MathDoubleLess`  
`struct FRigVMFunction_MathDoubleLess : public FRigVMFunction_MathDoubleBase`  
_L764-788_
- reflection: `USTRUCT(meta=(DisplayName="Less", TemplateName="Less", Keywords="Smaller,<"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns true if the value A is less than B
- L768 _public function_ `FRigVMFunction_MathDoubleLess()`
- L774 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L779 _public member_ `double A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L783 _public member_ `double B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L787 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is less than B

#### struct `FRigVMFunction_MathDoubleGreaterEqual`  
`struct FRigVMFunction_MathDoubleGreaterEqual : public FRigVMFunction_MathDoubleBase`  
_L794-818_
- reflection: `USTRUCT(meta=(DisplayName="Greater Equal", TemplateName="GreaterEqual", Keywords="Larger,Bigger,>="))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns true if the value A is greater than or equal to B
- L798 _public function_ `FRigVMFunction_MathDoubleGreaterEqual()`
- L804 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L809 _public member_ `double A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L813 _public member_ `double B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L817 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is greater than or equal to B

#### struct `FRigVMFunction_MathDoubleLessEqual`  
`struct FRigVMFunction_MathDoubleLessEqual : public FRigVMFunction_MathDoubleBase`  
_L824-848_
- reflection: `USTRUCT(meta=(DisplayName="Less Equal", TemplateName="LessEqual", Keywords="Smaller,<="))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns true if the value A is less than or equal to B
- L828 _public function_ `FRigVMFunction_MathDoubleLessEqual()`
- L834 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L839 _public member_ `double A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L843 _public member_ `double B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L847 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is less than or equal to B

#### struct `FRigVMFunction_MathDoubleIsNearlyZero`  
`struct FRigVMFunction_MathDoubleIsNearlyZero : public FRigVMFunction_MathDoubleBase`  
_L854-878_
- reflection: `USTRUCT(meta=(DisplayName="Is Nearly Zero", TemplateName="IsNearlyZero", Keywords="AlmostZero,0"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns true if the value is nearly zero
- L858 _public function_ `FRigVMFunction_MathDoubleIsNearlyZero()`
- L864 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L869 _public member_ `double Value;` — `UPROPERTY(meta=(Input))` — The input value to check
- L873 _public member_ `double Tolerance;` — `UPROPERTY(meta=(Input))` — The tolerance to apply for the comparison
- L877 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value is nearly zero

#### struct `FRigVMFunction_MathDoubleIsNearlyEqual`  
`struct FRigVMFunction_MathDoubleIsNearlyEqual : public FRigVMFunction_MathDoubleBase`  
_L884-912_
- reflection: `USTRUCT(meta=(DisplayName="Is Nearly Equal", TemplateName="IsNearlyEqual", Keywords="AlmostEqual,=="))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns true if the value A is almost equal to B
- L888 _public function_ `FRigVMFunction_MathDoubleIsNearlyEqual()`
- L894 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L899 _public member_ `double A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L903 _public member_ `double B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L907 _public member_ `double Tolerance;` — `UPROPERTY(meta=(Input))` — The tolerance to apply for the comparison
- L911 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is almost equal to B

#### struct `FRigVMFunction_MathDoubleDeg`  
`struct FRigVMFunction_MathDoubleDeg : public FRigVMFunction_MathDoubleUnaryOp`  
_L918-924_
- reflection: `USTRUCT(meta=(DisplayName="Degrees", TemplateName="Degrees"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns the degrees of a given value in radians
- L922 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleRad`  
`struct FRigVMFunction_MathDoubleRad : public FRigVMFunction_MathDoubleUnaryOp`  
_L930-936_
- reflection: `USTRUCT(meta=(DisplayName="Radians", TemplateName="Radians"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns the radians of a given value in degrees
- L934 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleSin`  
`struct FRigVMFunction_MathDoubleSin : public FRigVMFunction_MathDoubleUnaryOp`  
_L942-948_
- reflection: `USTRUCT(meta=(DisplayName="Sin", TemplateName="Sin"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns the trigonometric sine value of the given angle (in radians)
- L946 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleCos`  
`struct FRigVMFunction_MathDoubleCos : public FRigVMFunction_MathDoubleUnaryOp`  
_L954-960_
- reflection: `USTRUCT(meta=(DisplayName="Cos", TemplateName="Cos"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns the trigonometric cosine value of the given angle (in radians)
- L958 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleTan`  
`struct FRigVMFunction_MathDoubleTan : public FRigVMFunction_MathDoubleUnaryOp`  
_L966-972_
- reflection: `USTRUCT(meta=(DisplayName="Tan", TemplateName="Tan"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns the trigonometric tangent value of the given angle (in radians)
- L970 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleAsin`  
`struct FRigVMFunction_MathDoubleAsin : public FRigVMFunction_MathDoubleUnaryOp`  
_L978-984_
- reflection: `USTRUCT(meta=(DisplayName="Asin", TemplateName="Asin", Keywords="Arcsin"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns the inverse sine value (in radians between -pi/2 and pi/2) of the given value
- L982 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleAcos`  
`struct FRigVMFunction_MathDoubleAcos : public FRigVMFunction_MathDoubleUnaryOp`  
_L990-996_
- reflection: `USTRUCT(meta=(DisplayName="Acos", TemplateName="Acos", Keywords="Arccos"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns the inverse cosine value (in radians between 0 and pi) of the given value
- L994 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleAtan`  
`struct FRigVMFunction_MathDoubleAtan : public FRigVMFunction_MathDoubleUnaryOp`  
_L1002-1008_
- reflection: `USTRUCT(meta=(DisplayName="Atan", TemplateName="Atan", Keywords="Arctan"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Returns the inverse tangent value (in radians between -pi/2 and pi/2) of the given value
- L1006 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleAtan2`  
`struct FRigVMFunction_MathDoubleAtan2 : public FRigVMFunction_MathDoubleBinaryOp`  
_L1014-1020_
- reflection: `USTRUCT(meta=(DisplayName="Atan2", TemplateName="Atan2", Keywords="Arctan"))`
- inherits: `FRigVMFunction_MathDoubleBinaryOp`
- desc: Returns the inverse tangent value (in radians between -pi and pi) of A/B, using the signs of A and B to determine the correct quadrant.
- L1018 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleLawOfCosine`  
`struct FRigVMFunction_MathDoubleLawOfCosine : public FRigVMFunction_MathDoubleBase`  
_L1026-1066_
- reflection: `USTRUCT(meta = (DisplayName = "Law Of Cosine", TemplateName="LawOfCosine"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Computes the angles alpha, beta and gamma (in radians) between the three sides A, B and C
- L1030 _public function_ `FRigVMFunction_MathDoubleLawOfCosine()`
- L1036 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1041 _public member_ `double A;` — `UPROPERTY(meta = (Input))` — The length of the first edge of the triangle
- L1045 _public member_ `double B;` — `UPROPERTY(meta = (Input))` — The length of the second edge of the triangle
- L1049 _public member_ `double C;` — `UPROPERTY(meta = (Input))` — The length of the third edge of the triangle
- L1053 _public member_ `double AlphaAngle;` — `UPROPERTY(meta = (Output))` — The angle between B and C
- L1057 _public member_ `double BetaAngle;` — `UPROPERTY(meta = (Output))` — The angle between A and C
- L1061 _public member_ `double GammaAngle;` — `UPROPERTY(meta = (Output))` — The angle between A and B
- L1065 _public member_ `bool bValid;` — `UPROPERTY(meta = (Output))` — True if the results are valid

#### struct `FRigVMFunction_MathDoubleExponential`  
`struct FRigVMFunction_MathDoubleExponential : public FRigVMFunction_MathDoubleUnaryOp`  
_L1072-1078_
- reflection: `USTRUCT(meta = (DisplayName = "Exponential", TemplateName="Exponential"))`
- inherits: `FRigVMFunction_MathDoubleUnaryOp`
- desc: Computes the base-e exponential of the given value
- L1076 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathDoubleArraySum`  
`struct FRigVMFunction_MathDoubleArraySum : public FRigVMFunction_MathDoubleBase`  
_L1084-1104_
- reflection: `USTRUCT(meta = (DisplayName = "Array Sum", TemplateName = "ArraySum"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns the sum of the given array
- L1088 _public function_ `FRigVMFunction_MathDoubleArraySum()`
- L1094 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L1099 _public member_ `TArray<double> Array;` — `UPROPERTY(meta = (Input))` — The array of numbers to add up
- L1103 _public member_ `double Sum;` — `UPROPERTY(meta = (Output))` — The resulting sum of all numbers

#### struct `FRigVMFunction_MathDoubleArrayAverage`  
`struct FRigVMFunction_MathDoubleArrayAverage : public FRigVMFunction_MathDoubleBase`  
_L1110-1130_
- reflection: `USTRUCT(meta = (DisplayName = "Array Average", TemplateName = "ArrayAverage"))`
- inherits: `FRigVMFunction_MathDoubleBase`
- desc: Returns the average of the given array
- L1114 _public function_ `FRigVMFunction_MathDoubleArrayAverage()`
- L1120 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L1125 _public member_ `TArray<double> Array;` — `UPROPERTY(meta = (Input))` — The array of numbers to average
- L1129 _public member_ `double Average;` — `UPROPERTY(meta = (Output))` — The resulting average

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathFloat.h` (Public)


#### struct `FRigVMFunction_MathFloatBase`  
`struct FRigVMFunction_MathFloatBase : public FRigVMFunction_MathBase`  
_L14-17_
- reflection: `USTRUCT(meta=(Abstract, Category="Math|Float", MenuDescSuffix="(Float)"))`
- inherits: `FRigVMFunction_MathBase`
- desc: The base class for all pure float math nodes

#### struct `FRigVMFunction_MathFloatConstant`  
`struct FRigVMFunction_MathFloatConstant : public FRigVMFunction_MathFloatBase`  
_L23-35_
- reflection: `USTRUCT(meta=(Abstract, NoOp))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: The base class for all float math constants
- L27 _public function_ `FRigVMFunction_MathFloatConstant()`
- L34 _public member_ `float Value;` — `UPROPERTY(meta=(Output,Constant))` — The value of the constant

#### struct `FRigVMFunction_MathFloatUnaryOp`  
`struct FRigVMFunction_MathFloatUnaryOp : public FRigVMFunction_MathFloatBase`  
_L41-57_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: The base class for all unary float math operations
- L45 _public function_ `FRigVMFunction_MathFloatUnaryOp()`
- L52 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The input value
- L56 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The result of the operation

#### struct `FRigVMFunction_MathFloatBinaryOp`  
`struct FRigVMFunction_MathFloatBinaryOp : public FRigVMFunction_MathFloatBase`  
_L63-83_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: The base class for all binary float math operations
- L67 _public function_ `FRigVMFunction_MathFloatBinaryOp()`
- L74 _public member_ `float A;` — `UPROPERTY(meta=(Input))` — The first value for the operation
- L78 _public member_ `float B;` — `UPROPERTY(meta=(Input))` — The second value for the operation
- L82 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting value

#### struct `FRigVMFunction_MathFloatBinaryAggregateOp`  
`struct FRigVMFunction_MathFloatBinaryAggregateOp : public FRigVMFunction_MathFloatBase`  
_L89-109_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: The base class for all aggregational float math operations
- L93 _public function_ `FRigVMFunction_MathFloatBinaryAggregateOp()`
- L100 _public member_ `float A;` — `UPROPERTY(meta=(Input, Aggregate))` — The first value for the operation
- L104 _public member_ `float B;` — `UPROPERTY(meta=(Input, Aggregate))` — The second value for the operation
- L108 _public member_ `float Result;` — `UPROPERTY(meta=(Output, Aggregate))` — The resulting value

#### struct `FRigVMFunction_MathFloatMake`  
`struct FRigVMFunction_MathFloatMake : public FRigVMFunction_MathFloatBase`  
_L115-132_
- reflection: `USTRUCT(meta=(DisplayName="Float", Keywords="Make,Construct,Constant", Deprecated="5.7"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: A float constant
- L119 _public function_ `FRigVMFunction_MathFloatMake()`
- L124 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L128 _public member_ `float Value;` — `UPROPERTY(meta=(Input, Output, Constant))`
- L130 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathFloatConstPi`  
`struct FRigVMFunction_MathFloatConstPi : public FRigVMFunction_MathFloatConstant`  
_L138-149_
- reflection: `USTRUCT(meta=(DisplayName="Pi", TemplateName="Pi"))`
- inherits: `FRigVMFunction_MathFloatConstant`
- desc: Returns PI
- L142 _public function_ `FRigVMFunction_MathFloatConstPi()`
- L147 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatConstHalfPi`  
`struct FRigVMFunction_MathFloatConstHalfPi : public FRigVMFunction_MathFloatConstant`  
_L155-166_
- reflection: `USTRUCT(meta=(DisplayName="Half Pi", TemplateName="HalfPi"))`
- inherits: `FRigVMFunction_MathFloatConstant`
- desc: Returns PI * 0.5
- L159 _public function_ `FRigVMFunction_MathFloatConstHalfPi()`
- L164 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatConstTwoPi`  
`struct FRigVMFunction_MathFloatConstTwoPi : public FRigVMFunction_MathFloatConstant`  
_L172-183_
- reflection: `USTRUCT(meta=(DisplayName="Two Pi", TemplateName="TwoPi", Keywords="Tau"))`
- inherits: `FRigVMFunction_MathFloatConstant`
- desc: Returns PI * 2.0
- L176 _public function_ `FRigVMFunction_MathFloatConstTwoPi()`
- L181 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatConstE`  
`struct FRigVMFunction_MathFloatConstE : public FRigVMFunction_MathFloatConstant`  
_L189-200_
- reflection: `USTRUCT(meta=(DisplayName="E", TemplateName="E", Keywords="Euler"))`
- inherits: `FRigVMFunction_MathFloatConstant`
- desc: Returns E
- L193 _public function_ `FRigVMFunction_MathFloatConstE()`
- L198 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatAdd`  
`struct FRigVMFunction_MathFloatAdd : public FRigVMFunction_MathFloatBinaryAggregateOp`  
_L206-212_
- reflection: `USTRUCT(meta=(DisplayName="Add", TemplateName="Add", Keywords="Sum,+"))`
- inherits: `FRigVMFunction_MathFloatBinaryAggregateOp`
- desc: Returns the sum of the two values
- L210 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatSub`  
`struct FRigVMFunction_MathFloatSub : public FRigVMFunction_MathFloatBinaryAggregateOp`  
_L218-224_
- reflection: `USTRUCT(meta=(DisplayName="Subtract", TemplateName="Subtract", Keywords="-"))`
- inherits: `FRigVMFunction_MathFloatBinaryAggregateOp`
- desc: Returns the difference of the two values
- L222 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatMul`  
`struct FRigVMFunction_MathFloatMul : public FRigVMFunction_MathFloatBinaryAggregateOp`  
_L230-242_
- reflection: `USTRUCT(meta=(DisplayName="Multiply", TemplateName="Multiply", Keywords="Product,*"))`
- inherits: `FRigVMFunction_MathFloatBinaryAggregateOp`
- desc: Returns the product of the two values
- L234 _public function_ `FRigVMFunction_MathFloatMul()`
- L240 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatDiv`  
`struct FRigVMFunction_MathFloatDiv : public FRigVMFunction_MathFloatBinaryOp`  
_L248-259_
- reflection: `USTRUCT(meta=(DisplayName="Divide", TemplateName="Divide", Keywords="Division,Divisor,/"))`
- inherits: `FRigVMFunction_MathFloatBinaryOp`
- desc: Returns the division of the two values
- L252 _public function_ `FRigVMFunction_MathFloatDiv()`
- L257 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatMod`  
`struct FRigVMFunction_MathFloatMod : public FRigVMFunction_MathFloatBinaryOp`  
_L265-277_
- reflection: `USTRUCT(meta=(DisplayName="Modulo", TemplateName="Modulo", Keywords="%,fmod"))`
- inherits: `FRigVMFunction_MathFloatBinaryOp`
- desc: Returns the modulo of the two values
- L269 _public function_ `FRigVMFunction_MathFloatMod()`
- L275 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatMin`  
`struct FRigVMFunction_MathFloatMin : public FRigVMFunction_MathFloatBinaryAggregateOp`  
_L283-289_
- reflection: `USTRUCT(meta=(DisplayName="Minimum", TemplateName="Minimum"))`
- inherits: `FRigVMFunction_MathFloatBinaryAggregateOp`
- desc: Returns the smaller of the two values
- L287 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatMax`  
`struct FRigVMFunction_MathFloatMax : public FRigVMFunction_MathFloatBinaryAggregateOp`  
_L295-301_
- reflection: `USTRUCT(meta=(DisplayName="Maximum", TemplateName="Maximum"))`
- inherits: `FRigVMFunction_MathFloatBinaryAggregateOp`
- desc: Returns the larger of the two values
- L299 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatPow`  
`struct FRigVMFunction_MathFloatPow : public FRigVMFunction_MathFloatBinaryOp`  
_L307-319_
- reflection: `USTRUCT(meta=(DisplayName="Power", TemplateName="Power"))`
- inherits: `FRigVMFunction_MathFloatBinaryOp`
- desc: Returns the value of A raised to the power of B.
- L311 _public function_ `FRigVMFunction_MathFloatPow()`
- L317 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatSqrt`  
`struct FRigVMFunction_MathFloatSqrt : public FRigVMFunction_MathFloatUnaryOp`  
_L325-331_
- reflection: `USTRUCT(meta=(DisplayName="Sqrt", TemplateName="Sqrt", Keywords="Root,Square"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns the square root of the given value
- L329 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatNegate`  
`struct FRigVMFunction_MathFloatNegate : public FRigVMFunction_MathFloatUnaryOp`  
_L337-343_
- reflection: `USTRUCT(meta=(DisplayName="Negate", TemplateName="Negate", Keywords="-,Abs"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns the negative value
- L341 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatAbs`  
`struct FRigVMFunction_MathFloatAbs : public FRigVMFunction_MathFloatUnaryOp`  
_L349-355_
- reflection: `USTRUCT(meta=(DisplayName="Absolute", TemplateName="Absolute", Keywords="Abs,Neg"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns the absolute (positive) value
- L353 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatOneMinus`  
`struct FRigVMFunction_MathFloatOneMinus : public FRigVMFunction_MathFloatUnaryOp`  
_L362-368_
- reflection: `USTRUCT(meta=(DisplayName="One Minus", TemplateName="OneMinus", Keywords="Invert,Inverse,Subtract,One,Minus,Negate,Flip"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns one minus the input value (1 - x). Commonly used for inverting normalized values such as blend weights.
- L366 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatFloor`  
`struct FRigVMFunction_MathFloatFloor : public FRigVMFunction_MathFloatBase`  
_L374-398_
- reflection: `USTRUCT(meta=(DisplayName="Floor", TemplateName="Floor", Keywords="Round"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns the closest lower full number (integer) of the value
- L378 _public function_ `FRigVMFunction_MathFloatFloor()`
- L384 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L389 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The input value to apply the floor to
- L393 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting closest lower full number (integer) of the input value
- L397 _public member_ `int32 Int;` — `UPROPERTY(meta=(Output))` — The result as an integer value

#### struct `FRigVMFunction_MathFloatCeil`  
`struct FRigVMFunction_MathFloatCeil : public FRigVMFunction_MathFloatBase`  
_L404-428_
- reflection: `USTRUCT(meta=(DisplayName="Ceiling", TemplateName="Ceiling", Keywords="Round"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns the closest higher full number (integer) of the value
- L408 _public function_ `FRigVMFunction_MathFloatCeil()`
- L414 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L419 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The input value to apply the ceiling to
- L423 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting closest higher full number (integer) of the input value
- L427 _public member_ `int32 Int;` — `UPROPERTY(meta=(Output))` — The result as an integer value

#### struct `FRigVMFunction_MathFloatRound`  
`struct FRigVMFunction_MathFloatRound : public FRigVMFunction_MathFloatBase`  
_L434-458_
- reflection: `USTRUCT(meta=(DisplayName="Round", TemplateName="Round"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns the rounded value of the given float number
- L438 _public function_ `FRigVMFunction_MathFloatRound()`
- L444 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L449 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The input value to round
- L453 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The rounded value of the given float number
- L457 _public member_ `int32 Int;` — `UPROPERTY(meta=(Output))` — The result as an integer

#### struct `FRigVMFunction_MathFloatToInt`  
`struct FRigVMFunction_MathFloatToInt : public FRigVMFunction_MathFloatBase`  
_L464-484_
- reflection: `USTRUCT(meta=(DisplayName="To Int", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns the float cast to an int (this uses floor)
- L468 _public function_ `FRigVMFunction_MathFloatToInt()`
- L474 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L479 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The input value to floor to an int
- L483 _public member_ `int32 Result;` — `UPROPERTY(meta=(Output))` — The resulting (floored) integer

#### struct `FRigVMFunction_MathFloatToDouble`  
`struct FRigVMFunction_MathFloatToDouble : public FRigVMFunction_MathFloatBase`  
_L490-510_
- reflection: `USTRUCT(meta=(DisplayName="To Double", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns the float cast to a double
- L494 _public function_ `FRigVMFunction_MathFloatToDouble()`
- L500 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L505 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The float number to cast to double
- L509 _public member_ `double Result;` — `UPROPERTY(meta=(Output))` — The resulting double number

#### struct `FRigVMFunction_MathFloatSign`  
`struct FRigVMFunction_MathFloatSign : public FRigVMFunction_MathFloatUnaryOp`  
_L516-522_
- reflection: `USTRUCT(meta=(DisplayName="Sign", TemplateName="Sign"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns the sign of the value (+1 for >= 0.f, -1 for < 0.f)
- L520 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatClamp`  
`struct FRigVMFunction_MathFloatClamp : public FRigVMFunction_MathFloatBase`  
_L528-555_
- reflection: `USTRUCT(meta=(DisplayName="Clamp", TemplateName="Clamp", Keywords="Range,Remap"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Clamps the given value within the range provided by minimum and maximum
- L532 _public function_ `FRigVMFunction_MathFloatClamp()`
- L537 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L542 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The number to clamp
- L546 _public member_ `float Minimum;` — `UPROPERTY(meta=(Input))` — The Minimum for the resulting range
- L550 _public member_ `float Maximum;` — `UPROPERTY(meta=(Input))` — The Maximum for the resulting range
- L554 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting clamped value

#### struct `FRigVMFunction_MathFloatWrap`  
`struct FRigVMFunction_MathFloatWrap : public FRigVMFunction_MathFloatBase`  
_L562-591_
- reflection: `USTRUCT(meta = (DisplayName = "Wrap", TemplateName = "Wrap", Keywords = "Range,Remap"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Wraps the given value to be within minimum and maximum, inclusive When the value can wrap to both Min and Max, it will wrap to Min if it lies below the range and wrap to Max if it is above the range.
- L566 _public function_ `FRigVMFunction_MathFloatWrap()`
- L573 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L578 _public member_ `float Value;` — `UPROPERTY(meta = (Input))` — The number to wrap
- L582 _public member_ `float Minimum;` — `UPROPERTY(meta = (Input))` — The Minimum for the resulting range
- L586 _public member_ `float Maximum;` — `UPROPERTY(meta = (Input))` — The Maximum for the resulting range
- L590 _public member_ `float Result;` — `UPROPERTY(meta = (Output))` — The resulting wrapped value

#### struct `FRigVMFunction_MathFloatLerp`  
`struct FRigVMFunction_MathFloatLerp : public FRigVMFunction_MathFloatBase`  
_L597-625_
- reflection: `USTRUCT(meta=(DisplayName="Interpolate", TemplateName="Interpolate", Keywords="Lerp,Mix,Blend"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Linearly interpolates between A and B using the ratio T
- L601 _public function_ `FRigVMFunction_MathFloatLerp()`
- L607 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L612 _public member_ `float A;` — `UPROPERTY(meta=(Input))` — The first value to interpolate from
- L616 _public member_ `float B;` — `UPROPERTY(meta=(Input))` — The second value to interpolate to
- L620 _public member_ `float T;` — `UPROPERTY(meta=(Input, UIMin = "0", UIMax = "1"))` — The blend value for the interpolation
- L624 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting interpolated value

#### struct `FRigVMFunction_MathFloatRemap`  
`struct FRigVMFunction_MathFloatRemap : public FRigVMFunction_MathFloatBase`  
_L631-672_
- reflection: `USTRUCT(meta=(DisplayName="Remap", TemplateName="Remap", Keywords="Rescale,Scale"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Remaps the given value from a source range to a target range.
- L635 _public function_ `FRigVMFunction_MathFloatRemap()`
- L642 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L647 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The input value to remap
- L651 _public member_ `float SourceMinimum;` — `UPROPERTY(meta=(Input))` — The minimum of the range of the input / source value
- L655 _public member_ `float SourceMaximum;` — `UPROPERTY(meta=(Input))` — The maximum of the range of the input / source value
- L659 _public member_ `float TargetMinimum;` — `UPROPERTY(meta=(Input))` — The minimum of the range of the output / target value
- L663 _public member_ `float TargetMaximum;` — `UPROPERTY(meta=(Input))` — The maximum of the range of the output / target value
- L667 _public member_ `bool bClamp;` — `UPROPERTY(meta=(Input))` — If set to true the result is clamped to the target range
- L671 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting remapped value

#### struct `FRigVMFunction_MathFloatEquals`  
`struct FRigVMFunction_MathFloatEquals : public FRigVMFunction_MathFloatBase`  
_L678-701_
- reflection: `USTRUCT(meta=(DisplayName="Equals", TemplateName="Equals", Keywords="Same,==", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns true if the value A equals B
- L681 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L684 _public function_ `FRigVMFunction_MathFloatEquals()`
- L691 _public member_ `float A;` — `UPROPERTY(meta=(Input))`
- L694 _public member_ `float B;` — `UPROPERTY(meta=(Input))`
- L697 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))`
- L699 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathFloatNotEquals`  
`struct FRigVMFunction_MathFloatNotEquals : public FRigVMFunction_MathFloatBase`  
_L707-730_
- reflection: `USTRUCT(meta=(DisplayName="Not Equals", TemplateName="NotEquals", Keywords="Different,!=", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns true if the value A does not equal B
- L710 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L713 _public function_ `FRigVMFunction_MathFloatNotEquals()`
- L720 _public member_ `float A;` — `UPROPERTY(meta=(Input))`
- L723 _public member_ `float B;` — `UPROPERTY(meta=(Input))`
- L726 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))`
- L728 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathFloatGreater`  
`struct FRigVMFunction_MathFloatGreater : public FRigVMFunction_MathFloatBase`  
_L736-760_
- reflection: `USTRUCT(meta=(DisplayName="Greater", TemplateName="Greater", Keywords="Larger,Bigger,>"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns true if the value A is greater than B
- L740 _public function_ `FRigVMFunction_MathFloatGreater()`
- L746 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L751 _public member_ `float A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L755 _public member_ `float B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L759 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is greater than B

#### struct `FRigVMFunction_MathFloatLess`  
`struct FRigVMFunction_MathFloatLess : public FRigVMFunction_MathFloatBase`  
_L766-790_
- reflection: `USTRUCT(meta=(DisplayName="Less", TemplateName="Less", Keywords="Smaller,<"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns true if the value A is less than B
- L770 _public function_ `FRigVMFunction_MathFloatLess()`
- L776 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L781 _public member_ `float A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L785 _public member_ `float B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L789 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is less than B

#### struct `FRigVMFunction_MathFloatGreaterEqual`  
`struct FRigVMFunction_MathFloatGreaterEqual : public FRigVMFunction_MathFloatBase`  
_L796-820_
- reflection: `USTRUCT(meta=(DisplayName="Greater Equal", TemplateName="GreaterEqual", Keywords="Larger,Bigger,>="))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns true if the value A is greater than or equal to B
- L800 _public function_ `FRigVMFunction_MathFloatGreaterEqual()`
- L806 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L811 _public member_ `float A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L815 _public member_ `float B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L819 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is greater than or equal to B

#### struct `FRigVMFunction_MathFloatLessEqual`  
`struct FRigVMFunction_MathFloatLessEqual : public FRigVMFunction_MathFloatBase`  
_L826-850_
- reflection: `USTRUCT(meta=(DisplayName="Less Equal", TemplateName="LessEqual", Keywords="Smaller,<="))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns true if the value A is less than or equal to B
- L830 _public function_ `FRigVMFunction_MathFloatLessEqual()`
- L836 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L841 _public member_ `float A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L845 _public member_ `float B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L849 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is less than or equal to B

#### struct `FRigVMFunction_MathFloatIsNearlyZero`  
`struct FRigVMFunction_MathFloatIsNearlyZero : public FRigVMFunction_MathFloatBase`  
_L856-880_
- reflection: `USTRUCT(meta=(DisplayName="Is Nearly Zero", TemplateName="IsNearlyZero", Keywords="AlmostZero,0"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns true if the value is nearly zero
- L860 _public function_ `FRigVMFunction_MathFloatIsNearlyZero()`
- L866 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L871 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The input value to compare
- L875 _public member_ `float Tolerance;` — `UPROPERTY(meta=(Input))` — The tolerance to apply for the comparison
- L879 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value is nearly zero

#### struct `FRigVMFunction_MathFloatIsNearlyEqual`  
`struct FRigVMFunction_MathFloatIsNearlyEqual : public FRigVMFunction_MathFloatBase`  
_L886-914_
- reflection: `USTRUCT(meta=(DisplayName="Is Nearly Equal", TemplateName="IsNearlyEqual", Keywords="AlmostEqual,=="))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns true if the value A is almost equal to B
- L890 _public function_ `FRigVMFunction_MathFloatIsNearlyEqual()`
- L896 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L901 _public member_ `float A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L905 _public member_ `float B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L909 _public member_ `float Tolerance;` — `UPROPERTY(meta=(Input))` — The tolerance to apply for the comparison
- L913 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is almost equal to B

#### struct `FRigVMFunction_MathFloatSelectBool`  
`struct FRigVMFunction_MathFloatSelectBool : public FRigVMFunction_MathFloatBase`  
_L920-947_
- reflection: `USTRUCT(meta=(DisplayName="Select", Keywords="Pick,If", Deprecated = "4.26.0"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Return one of the two values based on the condition
- L924 _public function_ `FRigVMFunction_MathFloatSelectBool()`
- L930 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L934 _public member_ `bool Condition;` — `UPROPERTY(meta=(Input))`
- L937 _public member_ `float IfTrue;` — `UPROPERTY(meta=(Input))`
- L940 _public member_ `float IfFalse;` — `UPROPERTY(meta=(Input))`
- L943 _public member_ `float Result;` — `UPROPERTY(meta=(Output))`
- L945 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathFloatDeg`  
`struct FRigVMFunction_MathFloatDeg : public FRigVMFunction_MathFloatUnaryOp`  
_L953-959_
- reflection: `USTRUCT(meta=(DisplayName="Degrees", TemplateName="Degrees"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns the degrees of a given value in radians
- L957 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatRad`  
`struct FRigVMFunction_MathFloatRad : public FRigVMFunction_MathFloatUnaryOp`  
_L965-971_
- reflection: `USTRUCT(meta=(DisplayName="Radians", TemplateName="Radians"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns the radians of a given value in degrees
- L969 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatSin`  
`struct FRigVMFunction_MathFloatSin : public FRigVMFunction_MathFloatUnaryOp`  
_L977-983_
- reflection: `USTRUCT(meta=(DisplayName="Sin", TemplateName="Sin"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns the trigonometric sine value of the given angle (in radians)
- L981 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatCos`  
`struct FRigVMFunction_MathFloatCos : public FRigVMFunction_MathFloatUnaryOp`  
_L989-995_
- reflection: `USTRUCT(meta=(DisplayName="Cos", TemplateName="Cos"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns the trigonometric cosine value of the given angle (in radians)
- L993 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatTan`  
`struct FRigVMFunction_MathFloatTan : public FRigVMFunction_MathFloatUnaryOp`  
_L1001-1007_
- reflection: `USTRUCT(meta=(DisplayName="Tan", TemplateName="Tan"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns the trigonometric tangent value of the given angle (in radians)
- L1005 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatAsin`  
`struct FRigVMFunction_MathFloatAsin : public FRigVMFunction_MathFloatUnaryOp`  
_L1013-1019_
- reflection: `USTRUCT(meta=(DisplayName="Asin", TemplateName="Asin", Keywords="Arcsin"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns the inverse sine value (in radians between -pi/2 and pi/2) of the given value
- L1017 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatAcos`  
`struct FRigVMFunction_MathFloatAcos : public FRigVMFunction_MathFloatUnaryOp`  
_L1025-1031_
- reflection: `USTRUCT(meta=(DisplayName="Acos", TemplateName="Acos", Keywords="Arccos"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns the inverse cosine value (in radians between 0 and pi) of the given value
- L1029 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatAtan`  
`struct FRigVMFunction_MathFloatAtan : public FRigVMFunction_MathFloatUnaryOp`  
_L1037-1043_
- reflection: `USTRUCT(meta=(DisplayName="Atan", TemplateName="Atan", Keywords="Arctan"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Returns the inverse tangent value (in radians between -pi/2 and pi/2) of the given value
- L1041 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatAtan2`  
`struct FRigVMFunction_MathFloatAtan2 : public FRigVMFunction_MathFloatBinaryOp`  
_L1049-1055_
- reflection: `USTRUCT(meta=(DisplayName="Atan2", TemplateName="Atan2", Keywords="Arctan"))`
- inherits: `FRigVMFunction_MathFloatBinaryOp`
- desc: Returns the inverse tangent value (in radians between -pi and pi) of A/B, using the signs of A and B to determine the correct quadrant.
- L1053 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatLawOfCosine`  
`struct FRigVMFunction_MathFloatLawOfCosine : public FRigVMFunction_MathFloatBase`  
_L1061-1101_
- reflection: `USTRUCT(meta = (DisplayName = "Law Of Cosine", TemplateName="LawOfCosine"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Computes the angles alpha, beta and gamma (in radians) between the three sides A, B and C
- L1065 _public function_ `FRigVMFunction_MathFloatLawOfCosine()`
- L1071 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1076 _public member_ `float A;` — `UPROPERTY(meta = (Input))` — The length of the first edge of the triangle
- L1080 _public member_ `float B;` — `UPROPERTY(meta = (Input))` — The length of the second edge of the triangle
- L1084 _public member_ `float C;` — `UPROPERTY(meta = (Input))` — The length of the third edge of the triangle
- L1088 _public member_ `float AlphaAngle;` — `UPROPERTY(meta = (Output))` — The angle of between B and C
- L1092 _public member_ `float BetaAngle;` — `UPROPERTY(meta = (Output))` — The angle of between A and C
- L1096 _public member_ `float GammaAngle;` — `UPROPERTY(meta = (Output))` — The angle of between A and B
- L1100 _public member_ `bool bValid;` — `UPROPERTY(meta = (Output))` — True if the results are valid

#### struct `FRigVMFunction_MathFloatExponential`  
`struct FRigVMFunction_MathFloatExponential : public FRigVMFunction_MathFloatUnaryOp`  
_L1107-1113_
- reflection: `USTRUCT(meta = (DisplayName = "Exponential", TemplateName="Exponential"))`
- inherits: `FRigVMFunction_MathFloatUnaryOp`
- desc: Computes the base-e exponential of the given value
- L1111 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathFloatArraySum`  
`struct FRigVMFunction_MathFloatArraySum : public FRigVMFunction_MathFloatBase`  
_L1119-1139_
- reflection: `USTRUCT(meta = (DisplayName = "Array Sum", TemplateName = "ArraySum"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns the sum of the given array
- L1123 _public function_ `FRigVMFunction_MathFloatArraySum()`
- L1129 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L1134 _public member_ `TArray<float> Array;` — `UPROPERTY(meta = (Input))` — The array of numbers to add up
- L1138 _public member_ `float Sum;` — `UPROPERTY(meta = (Output))` — The resulting sum of all numbers

#### struct `FRigVMFunction_MathFloatArrayAverage`  
`struct FRigVMFunction_MathFloatArrayAverage : public FRigVMFunction_MathFloatBase`  
_L1145-1165_
- reflection: `USTRUCT(meta = (DisplayName = "Array Average", TemplateName = "ArrayAverage"))`
- inherits: `FRigVMFunction_MathFloatBase`
- desc: Returns the average of the given array
- L1149 _public function_ `FRigVMFunction_MathFloatArrayAverage()`
- L1155 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L1160 _public member_ `TArray<float> Array;` — `UPROPERTY(meta = (Input))` — The array of numbers to average
- L1164 _public member_ `float Average;` — `UPROPERTY(meta = (Output))` — The resulting average

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathInt.h` (Public)


#### struct `FRigVMFunction_MathIntBase`  
`struct FRigVMFunction_MathIntBase : public FRigVMFunction_MathBase`  
_L12-15_
- reflection: `USTRUCT(meta=(Abstract, Category="Math|Int", MenuDescSuffix="(Int)"))`
- inherits: `FRigVMFunction_MathBase`
- desc: The base class for all pure int math nodes

#### struct `FRigVMFunction_MathIntUnaryOp`  
`struct FRigVMFunction_MathIntUnaryOp : public FRigVMFunction_MathIntBase`  
_L21-37_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: The base class for all unary int math operations
- L25 _public function_ `FRigVMFunction_MathIntUnaryOp()`
- L32 _public member_ `int32 Value;` — `UPROPERTY(meta=(Input))` — The input value
- L36 _public member_ `int32 Result;` — `UPROPERTY(meta=(Output))` — The result of the operation

#### struct `FRigVMFunction_MathIntBinaryOp`  
`struct FRigVMFunction_MathIntBinaryOp : public FRigVMFunction_MathIntBase`  
_L43-63_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: The base class for all binary int math operations
- L47 _public function_ `FRigVMFunction_MathIntBinaryOp()`
- L54 _public member_ `int32 A;` — `UPROPERTY(meta=(Input))` — The first value for the operation
- L58 _public member_ `int32 B;` — `UPROPERTY(meta=(Input))` — The second value for the operation
- L62 _public member_ `int32 Result;` — `UPROPERTY(meta=(Output))` — The resulting value

#### struct `FRigVMFunction_MathIntBinaryAggregateOp`  
`struct FRigVMFunction_MathIntBinaryAggregateOp : public FRigVMFunction_MathIntBase`  
_L69-89_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: The base class for all aggregational int math operations
- L73 _public function_ `FRigVMFunction_MathIntBinaryAggregateOp()`
- L80 _public member_ `int32 A;` — `UPROPERTY(meta=(Input, Aggregate))` — The first value for the operation
- L84 _public member_ `int32 B;` — `UPROPERTY(meta=(Input, Aggregate))` — The second value for the operation
- L88 _public member_ `int32 Result;` — `UPROPERTY(meta=(Output, Aggregate))` — The resulting value

#### struct `FRigVMFunction_MathIntMake`  
`struct FRigVMFunction_MathIntMake : public FRigVMFunction_MathIntBase`  
_L95-112_
- reflection: `USTRUCT(meta=(DisplayName="Integer", Keywords="Make,Construct,Constant", Deprecated="5.7"))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: A integer constant
- L99 _public function_ `FRigVMFunction_MathIntMake()`
- L104 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L108 _public member_ `int32 Value;` — `UPROPERTY(meta=(Input, Output, Constant))`
- L110 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathIntAdd`  
`struct FRigVMFunction_MathIntAdd : public FRigVMFunction_MathIntBinaryAggregateOp`  
_L118-124_
- reflection: `USTRUCT(meta=(DisplayName="Add", TemplateName="Add", Keywords="Sum,+"))`
- inherits: `FRigVMFunction_MathIntBinaryAggregateOp`
- desc: Returns the sum of the two values
- L122 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathIntSub`  
`struct FRigVMFunction_MathIntSub : public FRigVMFunction_MathIntBinaryAggregateOp`  
_L130-136_
- reflection: `USTRUCT(meta=(DisplayName="Subtract", TemplateName="Subtract", Keywords="-"))`
- inherits: `FRigVMFunction_MathIntBinaryAggregateOp`
- desc: Returns the difference of the two values
- L134 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathIntMul`  
`struct FRigVMFunction_MathIntMul : public FRigVMFunction_MathIntBinaryAggregateOp`  
_L142-154_
- reflection: `USTRUCT(meta=(DisplayName="Multiply", TemplateName="Multiply", Keywords="Product,*"))`
- inherits: `FRigVMFunction_MathIntBinaryAggregateOp`
- desc: Returns the product of the two values
- L146 _public function_ `FRigVMFunction_MathIntMul()`
- L152 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathIntDiv`  
`struct FRigVMFunction_MathIntDiv : public FRigVMFunction_MathIntBinaryOp`  
_L160-171_
- reflection: `USTRUCT(meta=(DisplayName="Divide", TemplateName="Divide", Keywords="Division,Divisor,/"))`
- inherits: `FRigVMFunction_MathIntBinaryOp`
- desc: Returns the division of the two values
- L164 _public function_ `FRigVMFunction_MathIntDiv()`
- L169 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathIntMod`  
`struct FRigVMFunction_MathIntMod : public FRigVMFunction_MathIntBinaryOp`  
_L177-189_
- reflection: `USTRUCT(meta=(DisplayName="Modulo", TemplateName="Modulo", Keywords="%,fmod"))`
- inherits: `FRigVMFunction_MathIntBinaryOp`
- desc: Returns the modulo of the two values
- L181 _public function_ `FRigVMFunction_MathIntMod()`
- L187 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathIntMin`  
`struct FRigVMFunction_MathIntMin : public FRigVMFunction_MathIntBinaryAggregateOp`  
_L195-201_
- reflection: `USTRUCT(meta=(DisplayName="Minimum", TemplateName="Minimum"))`
- inherits: `FRigVMFunction_MathIntBinaryAggregateOp`
- desc: Returns the smaller of the two values
- L199 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathIntMax`  
`struct FRigVMFunction_MathIntMax : public FRigVMFunction_MathIntBinaryAggregateOp`  
_L207-213_
- reflection: `USTRUCT(meta=(DisplayName="Maximum", TemplateName="Maximum"))`
- inherits: `FRigVMFunction_MathIntBinaryAggregateOp`
- desc: Returns the larger of the two values
- L211 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathIntPow`  
`struct FRigVMFunction_MathIntPow : public FRigVMFunction_MathIntBinaryOp`  
_L219-231_
- reflection: `USTRUCT(meta=(DisplayName="Power", TemplateName="Power"))`
- inherits: `FRigVMFunction_MathIntBinaryOp`
- desc: Returns the value of A raised to the power of B.
- L223 _public function_ `FRigVMFunction_MathIntPow()`
- L229 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathIntNegate`  
`struct FRigVMFunction_MathIntNegate : public FRigVMFunction_MathIntUnaryOp`  
_L237-243_
- reflection: `USTRUCT(meta=(DisplayName="Negate", TemplateName="Negate", Keywords="-,Abs"))`
- inherits: `FRigVMFunction_MathIntUnaryOp`
- desc: Returns the negative value
- L241 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathIntAbs`  
`struct FRigVMFunction_MathIntAbs : public FRigVMFunction_MathIntUnaryOp`  
_L249-255_
- reflection: `USTRUCT(meta=(DisplayName="Absolute", TemplateName="Absolute", Keywords="Abs,Neg"))`
- inherits: `FRigVMFunction_MathIntUnaryOp`
- desc: Returns the absolute (positive) value
- L253 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathIntToFloat`  
`struct FRigVMFunction_MathIntToFloat : public FRigVMFunction_MathIntBase`  
_L261-281_
- reflection: `USTRUCT(meta=(DisplayName="To Float", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext"))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Returns the int cast to a float
- L265 _public function_ `FRigVMFunction_MathIntToFloat()`
- L271 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L276 _public member_ `int32 Value;` — `UPROPERTY(meta=(Input))` — The int to cast
- L280 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting float value

#### struct `FRigVMFunction_MathIntToDouble`  
`struct FRigVMFunction_MathIntToDouble : public FRigVMFunction_MathIntBase`  
_L287-307_
- reflection: `USTRUCT(meta=(DisplayName="To Double", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext"))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Returns the int cast to a double
- L291 _public function_ `FRigVMFunction_MathIntToDouble()`
- L297 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L302 _public member_ `int32 Value;` — `UPROPERTY(meta=(Input))` — The int to cast to double
- L306 _public member_ `double Result;` — `UPROPERTY(meta=(Output))` — The resulting double value

#### struct `FRigVMFunction_MathIntSign`  
`struct FRigVMFunction_MathIntSign : public FRigVMFunction_MathIntUnaryOp`  
_L313-319_
- reflection: `USTRUCT(meta=(DisplayName="Sign", TemplateName="Sign"))`
- inherits: `FRigVMFunction_MathIntUnaryOp`
- desc: Returns the sign of the value (+1 for >= 0, -1 for < 0)
- L317 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathIntClamp`  
`struct FRigVMFunction_MathIntClamp : public FRigVMFunction_MathIntBase`  
_L325-352_
- reflection: `USTRUCT(meta=(DisplayName="Clamp", TemplateName="Clamp", Keywords="Range,Remap"))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Clamps the given value within the range provided by minimum and maximum
- L329 _public function_ `FRigVMFunction_MathIntClamp()`
- L334 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L339 _public member_ `int32 Value;` — `UPROPERTY(meta=(Input))` — The number to clamp
- L343 _public member_ `int32 Minimum;` — `UPROPERTY(meta=(Input))` — The Minimum for the resulting range
- L347 _public member_ `int32 Maximum;` — `UPROPERTY(meta=(Input))` — The Maximum for the resulting range
- L351 _public member_ `int32 Result;` — `UPROPERTY(meta=(Output))` — The resulting clamped value

#### struct `FRigVMFunction_MathIntEquals`  
`struct FRigVMFunction_MathIntEquals : public FRigVMFunction_MathIntBase`  
_L358-381_
- reflection: `USTRUCT(meta=(DisplayName="Equals", TemplateName="Equals", Keywords="Same,==", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Returns true if the value A equals B
- L361 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L364 _public function_ `FRigVMFunction_MathIntEquals()`
- L371 _public member_ `int32 A;` — `UPROPERTY(meta=(Input))`
- L374 _public member_ `int32 B;` — `UPROPERTY(meta=(Input))`
- L377 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))`
- L379 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathIntNotEquals`  
`struct FRigVMFunction_MathIntNotEquals : public FRigVMFunction_MathIntBase`  
_L387-410_
- reflection: `USTRUCT(meta=(DisplayName="Not Equals", TemplateName="NotEquals", Keywords="Different,!=", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Returns true if the value A does not equal B
- L390 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L393 _public function_ `FRigVMFunction_MathIntNotEquals()`
- L400 _public member_ `int32 A;` — `UPROPERTY(meta=(Input))`
- L403 _public member_ `int32 B;` — `UPROPERTY(meta=(Input))`
- L406 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))`
- L408 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathIntGreater`  
`struct FRigVMFunction_MathIntGreater : public FRigVMFunction_MathIntBase`  
_L416-440_
- reflection: `USTRUCT(meta=(DisplayName="Greater", TemplateName="Greater", Keywords="Larger,Bigger,>"))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Returns true if the value A is greater than B
- L420 _public function_ `FRigVMFunction_MathIntGreater()`
- L426 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L431 _public member_ `int32 A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L435 _public member_ `int32 B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L439 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is greater than B

#### struct `FRigVMFunction_MathIntLess`  
`struct FRigVMFunction_MathIntLess : public FRigVMFunction_MathIntBase`  
_L446-470_
- reflection: `USTRUCT(meta=(DisplayName="Less", TemplateName="Less", Keywords="Smaller,<"))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Returns true if the value A is less than B
- L450 _public function_ `FRigVMFunction_MathIntLess()`
- L456 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L461 _public member_ `int32 A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L465 _public member_ `int32 B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L469 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is less than B

#### struct `FRigVMFunction_MathIntGreaterEqual`  
`struct FRigVMFunction_MathIntGreaterEqual : public FRigVMFunction_MathIntBase`  
_L476-500_
- reflection: `USTRUCT(meta=(DisplayName="Greater Equal", TemplateName="GreaterEqual", Keywords="Larger,Bigger,>="))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Returns true if the value A is greater than or equal to B
- L480 _public function_ `FRigVMFunction_MathIntGreaterEqual()`
- L486 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L491 _public member_ `int32 A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L495 _public member_ `int32 B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L499 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is greater than or equal to B

#### struct `FRigVMFunction_MathIntLessEqual`  
`struct FRigVMFunction_MathIntLessEqual : public FRigVMFunction_MathIntBase`  
_L506-530_
- reflection: `USTRUCT(meta=(DisplayName="Less Equal", TemplateName="LessEqual", Keywords="Smaller,<="))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Returns true if the value A is less than or equal to B
- L510 _public function_ `FRigVMFunction_MathIntLessEqual()`
- L516 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L521 _public member_ `int32 A;` — `UPROPERTY(meta=(Input))` — The first value to compare
- L525 _public member_ `int32 B;` — `UPROPERTY(meta=(Input))` — The second value to compare
- L529 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the value A is less than or equal to B

#### struct `FRigVMFunction_MathIntArraySum`  
`struct FRigVMFunction_MathIntArraySum : public FRigVMFunction_MathIntBase`  
_L536-556_
- reflection: `USTRUCT(meta = (DisplayName = "Array Sum", TemplateName = "ArraySum"))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Returns the sum of the given array
- L540 _public function_ `FRigVMFunction_MathIntArraySum()`
- L546 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L551 _public member_ `TArray<int32> Array;` — `UPROPERTY(meta = (Input))` — The array of numbers to add up
- L555 _public member_ `int32 Sum;` — `UPROPERTY(meta = (Output))` — The resulting sum

#### struct `FRigVMFunction_MathIntArrayAverage`  
`struct FRigVMFunction_MathIntArrayAverage : public FRigVMFunction_MathIntBase`  
_L563-583_
- reflection: `USTRUCT(meta = (DisplayName = "Array Average", TemplateName = "ArrayAverage"))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Returns the average of the given array
- L567 _public function_ `FRigVMFunction_MathIntArrayAverage()`
- L573 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L578 _public member_ `TArray<int32> Array;` — `UPROPERTY(meta = (Input))` — The array of numbers to average
- L582 _public member_ `int32 Average;` — `UPROPERTY(meta = (Output))` — The resulting average

#### struct `FRigVMFunction_MathIntToString`  
`struct FRigVMFunction_MathIntToString : public FRigVMFunction_MathIntBase`  
_L589-616_
- reflection: `USTRUCT(meta = (DisplayName = "Int to String", TemplateName="Int to Name"))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Converts an integer to a string
- L593 _public function_ `FRigVMFunction_MathIntToString()`
- L599 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this function
- L604 _public member_ `int32 Number;` — `UPROPERTY(meta = (Input))` — The number to convert
- L611 _public member_ `int32 PaddedSize;` — `UPROPERTY(meta = (Input))` — For positive numbers you can pad the result to a required width so rather than '13' return '00013' for a padded size of 5.
- L615 _public member_ `FString Result;` — `UPROPERTY(meta = (Output))` — The resulting potentially padded string

#### struct `FRigVMFunction_MathIntToName`  
`struct FRigVMFunction_MathIntToName : public FRigVMFunction_MathIntBase`  
_L622-649_
- reflection: `USTRUCT(meta = (DisplayName = "Int to Name", TemplateName="Int to Name"))`
- inherits: `FRigVMFunction_MathIntBase`
- desc: Converts an integer to a name
- L626 _public function_ `FRigVMFunction_MathIntToName()`
- L632 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this function
- L637 _public member_ `int32 Number;` — `UPROPERTY(meta = (Input))` — The number to convert
- L644 _public member_ `int32 PaddedSize;` — `UPROPERTY(meta = (Input))` — For positive numbers you can pad the result to a required width so rather than '13' return '00013' for a padded size of 5.
- L648 _public member_ `FName Result;` — `UPROPERTY(meta = (Output))` — The resulting potentially padded name

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathMatrix.h` (Public)


#### struct `FRigVMFunction_MathMatrixBase`  
`struct FRigVMFunction_MathMatrixBase : public FRigVMFunction_MathBase`  
_L13-16_
- reflection: `USTRUCT(meta=(Abstract, Category="Math|Matrix", MenuDescSuffix="(Matrix)"))`
- inherits: `FRigVMFunction_MathBase`
- desc: The base class for all pure matrix math nodes

#### struct `FRigVMFunction_MathMatrixUnaryOp`  
`struct FRigVMFunction_MathMatrixUnaryOp : public FRigVMFunction_MathMatrixBase`  
_L22-38_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathMatrixBase`
- desc: The base class for all unary matrix math operations
- L26 _public function_ `FRigVMFunction_MathMatrixUnaryOp()`
- L33 _public member_ `FMatrix Value;` — `UPROPERTY(meta=(Input))` — The input value
- L37 _public member_ `FMatrix Result;` — `UPROPERTY(meta=(Output))` — The result of the operation

#### struct `FRigVMFunction_MathMatrixBinaryOp`  
`struct FRigVMFunction_MathMatrixBinaryOp : public FRigVMFunction_MathMatrixBase`  
_L44-64_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathMatrixBase`
- desc: The base class for all binary matrix math operations
- L48 _public function_ `FRigVMFunction_MathMatrixBinaryOp()`
- L55 _public member_ `FMatrix A;` — `UPROPERTY(meta=(Input))` — The first value for the operation
- L59 _public member_ `FMatrix B;` — `UPROPERTY(meta=(Input))` — The second value for the operation
- L63 _public member_ `FMatrix Result;` — `UPROPERTY(meta=(Output))` — The resulting value

#### struct `FRigVMFunction_MathMatrixBinaryAggregateOp`  
`struct FRigVMFunction_MathMatrixBinaryAggregateOp : public FRigVMFunction_MathMatrixBase`  
_L70-90_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathMatrixBase`
- desc: The base class for all aggregational matrix math nodes
- L74 _public function_ `FRigVMFunction_MathMatrixBinaryAggregateOp()`
- L81 _public member_ `FMatrix A;` — `UPROPERTY(meta=(Input, Aggregate))` — The first matrix for the operation
- L85 _public member_ `FMatrix B;` — `UPROPERTY(meta=(Input, Aggregate))` — The second matrix for the operation
- L89 _public member_ `FMatrix Result;` — `UPROPERTY(meta=(Output, Aggregate))` — The resulting matrix

#### struct `FRigVMFunction_MathMatrixToTransform`  
`struct FRigVMFunction_MathMatrixToTransform : public FRigVMFunction_MathMatrixBase`  
_L96-116_
- reflection: `USTRUCT(meta=(DisplayName="To Transform", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathMatrixBase`
- desc: Makes a transform from a matrix
- L100 _public function_ `FRigVMFunction_MathMatrixToTransform()`
- L106 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L111 _public member_ `FMatrix Value;` — `UPROPERTY(meta=(Input))` — The matrix to convert to a transform
- L115 _public member_ `FTransform Result;` — `UPROPERTY(meta=(Output))` — The resulting transform

#### struct `FRigVMFunction_MathMatrixFromTransform`  
`struct FRigVMFunction_MathMatrixFromTransform : public FRigVMFunction_MathMatrixBase`  
_L122-143_
- reflection: `USTRUCT(meta=(DisplayName="From Transform", Keywords="Make,Construct", Deprecated="5.0.1"))`
- inherits: `FRigVMFunction_MathMatrixBase`
- desc: Makes a matrix from a transform
- L126 _public function_ `FRigVMFunction_MathMatrixFromTransform()`
- L132 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L136 _public member_ `FTransform Transform;` — `UPROPERTY(meta=(Input))`
- L139 _public member_ `FMatrix Result;` — `UPROPERTY(meta=(Output))`
- L141 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathMatrixFromTransformV2`  
`struct FRigVMFunction_MathMatrixFromTransformV2 : public FRigVMFunction_MathMatrixBase`  
_L149-169_
- reflection: `USTRUCT(meta=(DisplayName="From Transform", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathMatrixBase`
- desc: Makes a matrix from a transform
- L153 _public function_ `FRigVMFunction_MathMatrixFromTransformV2()`
- L159 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L164 _public member_ `FTransform Value;` — `UPROPERTY(meta=(Input))` — The transform to convert to a matrix
- L168 _public member_ `FMatrix Result;` — `UPROPERTY(meta=(Output))` — The resulting matrix

#### struct `FRigVMFunction_MathMatrixToVectors`  
`struct FRigVMFunction_MathMatrixToVectors : public FRigVMFunction_MathMatrixBase`  
_L175-210_
- reflection: `USTRUCT(meta=(DisplayName="To Vectors", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathMatrixBase`
- desc: Converts the matrix to its vectors
- L179 _public function_ `FRigVMFunction_MathMatrixToVectors()`
- L188 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L193 _public member_ `FMatrix Value;` — `UPROPERTY(meta=(Input))` — The matrix to split up to vectors
- L197 _public member_ `FVector Origin;` — `UPROPERTY(meta=(Output))` — The resulting origin
- L201 _public member_ `FVector X;` — `UPROPERTY(meta=(Output))` — The resulting X component
- L205 _public member_ `FVector Y;` — `UPROPERTY(meta=(Output))` — The resulting Y component
- L209 _public member_ `FVector Z;` — `UPROPERTY(meta=(Output))` — The resulting Z component

#### struct `FRigVMFunction_MathMatrixFromVectors`  
`struct FRigVMFunction_MathMatrixFromVectors : public FRigVMFunction_MathMatrixBase`  
_L216-251_
- reflection: `USTRUCT(meta=(DisplayName="From Vectors", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathMatrixBase`
- desc: Makes a matrix from its vectors
- L220 _public function_ `FRigVMFunction_MathMatrixFromVectors()`
- L229 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L234 _public member_ `FVector Origin;` — `UPROPERTY(meta=(Input))` — The input origin for the matrix
- L238 _public member_ `FVector X;` — `UPROPERTY(meta=(Input))` — The input X component for the matrix
- L242 _public member_ `FVector Y;` — `UPROPERTY(meta=(Input))` — The input Y component for the matrix
- L246 _public member_ `FVector Z;` — `UPROPERTY(meta=(Input))` — The input Z component for the matrix
- L250 _public member_ `FMatrix Result;` — `UPROPERTY(meta=(Output))` — The resulting matrix

#### struct `FRigVMFunction_MathMatrixMul`  
`struct FRigVMFunction_MathMatrixMul : public FRigVMFunction_MathMatrixBinaryAggregateOp`  
_L257-262_
- reflection: `USTRUCT(meta=(DisplayName="Multiply", TemplateName="Multiply", Keywords="Product,*,Global"))`
- inherits: `FRigVMFunction_MathMatrixBinaryAggregateOp`
- desc: Returns the product of the two values
- L260 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathMatrixInverse`  
`struct FRigVMFunction_MathMatrixInverse : public FRigVMFunction_MathMatrixUnaryOp`  
_L268-273_
- reflection: `USTRUCT(meta=(DisplayName="Inverse", TemplateName="Inverse"))`
- inherits: `FRigVMFunction_MathMatrixUnaryOp`
- desc: Returns the inverse value
- L271 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathQuaternion.h` (Public)


#### struct `FRigVMFunction_MathQuaternionBase`  
`struct FRigVMFunction_MathQuaternionBase : public FRigVMFunction_MathBase`  
_L15-18_
- reflection: `USTRUCT(meta=(Abstract, Category="Math|Quaternion", MenuDescSuffix="(Quaternion)"))`
- inherits: `FRigVMFunction_MathBase`
- desc: The base class for all pure quaternion math nodes

#### struct `FRigVMFunction_MathQuaternionUnaryOp`  
`struct FRigVMFunction_MathQuaternionUnaryOp : public FRigVMFunction_MathQuaternionBase`  
_L24-40_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: The base class for all unary quaternion math operations
- L28 _public function_ `FRigVMFunction_MathQuaternionUnaryOp()`
- L35 _public member_ `FQuat Value;` — `UPROPERTY(meta=(Input))` — The input value
- L39 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The result of the operation

#### struct `FRigVMFunction_MathQuaternionBinaryOp`  
`struct FRigVMFunction_MathQuaternionBinaryOp : public FRigVMFunction_MathQuaternionBase`  
_L46-66_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: The base class for all binary quaternion math operations
- L50 _public function_ `FRigVMFunction_MathQuaternionBinaryOp()`
- L57 _public member_ `FQuat A;` — `UPROPERTY(meta=(Input))` — The first value for the operation
- L61 _public member_ `FQuat B;` — `UPROPERTY(meta=(Input))` — The second value for the operation
- L65 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The resulting value

#### struct `FRigVMFunction_MathQuaternionBinaryAggregateOp`  
`struct FRigVMFunction_MathQuaternionBinaryAggregateOp : public FRigVMFunction_MathQuaternionBase`  
_L72-92_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: The base class for all aggregational quaternion math operations
- L76 _public function_ `FRigVMFunction_MathQuaternionBinaryAggregateOp()`
- L83 _public member_ `FQuat A;` — `UPROPERTY(meta=(Input, Aggregate))` — The first value for the operation
- L87 _public member_ `FQuat B;` — `UPROPERTY(meta=(Input, Aggregate))` — The second value for the operation
- L91 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output, Aggregate))` — The resulting value

#### struct `FRigVMFunction_MathQuaternionMake`  
`struct FRigVMFunction_MathQuaternionMake : public FRigVMFunction_MathQuaternionBase`  
_L98-129_
- reflection: `USTRUCT(meta=(DisplayName="Make Quat", Keywords="Make,Construct,Constant"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Makes a quaternion from its components
- L101 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L104 _public function_ `FRigVMFunction_MathQuaternionMake()`
- L112 _public member_ `float X;` — `UPROPERTY(meta=(Input))` — The X of the quaternion
- L116 _public member_ `float Y;` — `UPROPERTY(meta=(Input))` — The Y of the quaternion
- L120 _public member_ `float Z;` — `UPROPERTY(meta=(Input))` — The Z of the quaternion
- L124 _public member_ `float W;` — `UPROPERTY(meta=(Input))` — The W of the quaternion
- L128 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The resulting composed quaternion

#### struct `FRigVMFunction_MathQuaternionFromAxisAndAngle`  
`struct FRigVMFunction_MathQuaternionFromAxisAndAngle : public FRigVMFunction_MathQuaternionBase`  
_L135-160_
- reflection: `USTRUCT(meta=(DisplayName="From Axis And Angle", TemplateName="FromAxisAndAngle", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Makes a quaternion from an axis and an angle in radians
- L139 _public function_ `FRigVMFunction_MathQuaternionFromAxisAndAngle()`
- L146 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L151 _public member_ `FVector Axis;` — `UPROPERTY(meta=(Input))` — The axis to use for the quaternion
- L155 _public member_ `float Angle;` — `UPROPERTY(meta=(Input))` — The angle in radians to use for the quaternion
- L159 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The resulting composed quaternion

#### struct `FRigVMFunction_MathQuaternionFromEuler`  
`struct FRigVMFunction_MathQuaternionFromEuler : public FRigVMFunction_MathQuaternionBase`  
_L166-191_
- reflection: `USTRUCT(meta=(DisplayName="From Euler", TemplateName="FromEuler", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Makes a quaternion from euler values in degrees
- L170 _public function_ `FRigVMFunction_MathQuaternionFromEuler()`
- L177 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L182 _public member_ `FVector Euler;` — `UPROPERTY(meta = (Input))` — The euler representation of the rotation in degrees.
- L186 _public member_ `EEulerRotationOrder RotationOrder;` — `UPROPERTY(meta = (Input))` — The rotation order to use when interpreting the euler angles
- L190 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The resulting composed quaternion

#### struct `FRigVMFunction_MathQuaternionFromRotator`  
`struct FRigVMFunction_MathQuaternionFromRotator : public FRigVMFunction_MathQuaternionBase`  
_L197-218_
- reflection: `USTRUCT(meta=(DisplayName="From Rotator", Keywords="Make,Construct", Deprecated="5.0.1"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Makes a quaternion from a rotator
- L201 _public function_ `FRigVMFunction_MathQuaternionFromRotator()`
- L207 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L211 _public member_ `FRotator Rotator;` — `UPROPERTY(meta=(Input))`
- L214 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))`
- L216 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathQuaternionFromRotatorV2`  
`struct FRigVMFunction_MathQuaternionFromRotatorV2 : public FRigVMFunction_MathQuaternionBase`  
_L224-244_
- reflection: `USTRUCT(meta=(DisplayName="From Rotator", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Makes a quaternion from a rotator
- L228 _public function_ `FRigVMFunction_MathQuaternionFromRotatorV2()`
- L234 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L239 _public member_ `FRotator Value;` — `UPROPERTY(meta=(Input))` — The rotator representation of the rotation
- L243 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The resulting composed quaternion

#### struct `FRigVMFunction_MathQuaternionFromTwoVectors`  
`struct FRigVMFunction_MathQuaternionFromTwoVectors : public FRigVMFunction_MathQuaternionBase`  
_L250-274_
- reflection: `USTRUCT(meta=(DisplayName="From Two Vectors", TemplateName="FromTwoVectors", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Makes a quaternion from two vectors, representing the shortest rotation between the two vectors.
- L254 _public function_ `FRigVMFunction_MathQuaternionFromTwoVectors()`
- L260 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L265 _public member_ `FVector A;` — `UPROPERTY(meta=(Input))` — A vector representing a direction prior to rotation
- L269 _public member_ `FVector B;` — `UPROPERTY(meta=(Input))` — A vector representing a direction after a rotation
- L273 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The quaternion representing the rotation from A to B

#### struct `FRigVMFunction_MathQuaternionToAxisAndAngle`  
`struct FRigVMFunction_MathQuaternionToAxisAndAngle : public FRigVMFunction_MathQuaternionBase`  
_L280-305_
- reflection: `USTRUCT(meta=(DisplayName="To Axis And Angle", TemplateName="ToAxisAndAngle", Keywords="Make,Construct,GetAxis,GetAngle"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Retrieves the axis and angle of a quaternion in radians
- L284 _public function_ `FRigVMFunction_MathQuaternionToAxisAndAngle()`
- L291 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L296 _public member_ `FQuat Value;` — `UPROPERTY(meta=(Input))` — The input quaternion
- L300 _public member_ `FVector Axis;` — `UPROPERTY(meta=(Output))` — The axis of the quaternion
- L304 _public member_ `float Angle;` — `UPROPERTY(meta=(Output))` — The angle in radians of the quaternion

#### struct `FRigVMFunction_MathQuaternionToVectors`  
`struct FRigVMFunction_MathQuaternionToVectors : public FRigVMFunction_MathQuaternionBase`  
_L311-339_
- reflection: `USTRUCT(meta=(DisplayName="To Vectors", TemplateName="ToVectors", Keywords="Forward,Right,Up"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Retrieves the forward, right and up vectors of a quaternion
- L315 _public function_ `FRigVMFunction_MathQuaternionToVectors()`
- L321 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L326 _public member_ `FQuat Value;` — `UPROPERTY(meta=(Input))` — The input quaternion
- L330 _public member_ `FVector Forward;` — `UPROPERTY(meta=(Output))` — The forward axis of the quaternion
- L334 _public member_ `FVector Right;` — `UPROPERTY(meta=(Output))` — The right axis of the quaternion
- L338 _public member_ `FVector Up;` — `UPROPERTY(meta=(Output))` — The up axis of the quaternion

#### struct `FRigVMFunction_MathQuaternionScale`  
`struct FRigVMFunction_MathQuaternionScale : public FRigVMFunction_MathQuaternionBase`  
_L345-366_
- reflection: `USTRUCT(meta=(DisplayName="Scale", Keywords="Multiply,Angle,Scale", Constant, Deprecated = "5.0.1"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Scales a quaternion's angle
- L349 _public function_ `FRigVMFunction_MathQuaternionScale()`
- L355 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L359 _public member_ `FQuat Value;` — `UPROPERTY(meta=(Input, Output))`
- L362 _public member_ `float Scale;` — `UPROPERTY(meta=(Input))`
- L364 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathQuaternionScaleV2`  
`struct FRigVMFunction_MathQuaternionScaleV2 : public FRigVMFunction_MathQuaternionBase`  
_L372-396_
- reflection: `USTRUCT(meta=(DisplayName="Scale", TemplateName="Scale", Keywords="Multiply,Angle,Scale", Constant))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Scales a quaternion's angle
- L376 _public function_ `FRigVMFunction_MathQuaternionScaleV2()`
- L382 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L387 _public member_ `FQuat Value;` — `UPROPERTY(meta=(Input))` — The input quaternion
- L391 _public member_ `float Factor;` — `UPROPERTY(meta=(Input))` — The scale factor to scale the input by
- L395 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The resulting scaled quaternion

#### struct `FRigVMFunction_MathQuaternionToEuler`  
`struct FRigVMFunction_MathQuaternionToEuler : public FRigVMFunction_MathQuaternionBase`  
_L402-427_
- reflection: `USTRUCT(meta=(DisplayName="To Euler", TemplateName="ToEuler", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Retrieves the euler angles in degrees
- L406 _public function_ `FRigVMFunction_MathQuaternionToEuler()`
- L413 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L418 _public member_ `FQuat Value;` — `UPROPERTY(meta=(Input))` — The input quaternion
- L422 _public member_ `EEulerRotationOrder RotationOrder;` — `UPROPERTY(meta = (Input))` — The rotation order to use when encoding the euler angles
- L426 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The euler angles in degrees representing the quaternion in the given rotation order

#### struct `FRigVMFunction_MathQuaternionToRotator`  
`struct FRigVMFunction_MathQuaternionToRotator : public FRigVMFunction_MathQuaternionBase`  
_L433-453_
- reflection: `USTRUCT(meta=(DisplayName="To Rotator", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Retrieves the rotator
- L437 _public function_ `FRigVMFunction_MathQuaternionToRotator()`
- L443 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L448 _public member_ `FQuat Value;` — `UPROPERTY(meta=(Input))` — The input quaternion
- L452 _public member_ `FRotator Result;` — `UPROPERTY(meta=(Output))` — The rotator representation of the rotation

#### struct `FRigVMFunction_MathQuaternionMul`  
`struct FRigVMFunction_MathQuaternionMul : public FRigVMFunction_MathQuaternionBinaryAggregateOp`  
_L459-464_
- reflection: `USTRUCT(meta=(DisplayName="Multiply", TemplateName="Multiply", Keywords="Product,*"))`
- inherits: `FRigVMFunction_MathQuaternionBinaryAggregateOp`
- desc: Returns the product of the two values
- L462 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathQuaternionInverse`  
`struct FRigVMFunction_MathQuaternionInverse : public FRigVMFunction_MathQuaternionUnaryOp`  
_L470-475_
- reflection: `USTRUCT(meta=(DisplayName="Inverse", TemplateName="Inverse"))`
- inherits: `FRigVMFunction_MathQuaternionUnaryOp`
- desc: Returns the negative value
- L473 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathQuaternionSlerp`  
`struct FRigVMFunction_MathQuaternionSlerp : public FRigVMFunction_MathQuaternionBase`  
_L481-509_
- reflection: `USTRUCT(meta=(DisplayName="Interpolate", TemplateName="Interpolate", Keywords="Lerp,Mix,Blend,Slerp,SphericalInterpolate"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Performs a spherical interpolation of the quaternions A and B based on the blend value T.
- L485 _public function_ `FRigVMFunction_MathQuaternionSlerp()`
- L491 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L496 _public member_ `FQuat A;` — `UPROPERTY(meta=(Input))` — The first quaternion to interpolate from
- L500 _public member_ `FQuat B;` — `UPROPERTY(meta=(Input))` — The second quaternion to interpolate to
- L504 _public member_ `float T;` — `UPROPERTY(meta=(Input, UIMin = "0", UIMax = "1"))` — The blend value for the interpolation
- L508 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The resulting interpolated quaternion

#### struct `FRigVMFunction_MathQuaternionEquals`  
`struct FRigVMFunction_MathQuaternionEquals : public FRigVMFunction_MathQuaternionBase`  
_L515-539_
- reflection: `USTRUCT(meta=(DisplayName="Equals", TemplateName="Equals", Keywords="Same,==", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Returns true if the value A equals B
- L519 _public function_ `FRigVMFunction_MathQuaternionEquals()`
- L525 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L529 _public member_ `FQuat A;` — `UPROPERTY(meta=(Input))`
- L532 _public member_ `FQuat B;` — `UPROPERTY(meta=(Input))`
- L535 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))`
- L537 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathQuaternionNotEquals`  
`struct FRigVMFunction_MathQuaternionNotEquals : public FRigVMFunction_MathQuaternionBase`  
_L545-569_
- reflection: `USTRUCT(meta=(DisplayName="Not Equals", TemplateName="NotEquals", Keywords="Different,!=", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Returns true if the value A does not equal B
- L549 _public function_ `FRigVMFunction_MathQuaternionNotEquals()`
- L555 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L559 _public member_ `FQuat A;` — `UPROPERTY(meta=(Input))`
- L562 _public member_ `FQuat B;` — `UPROPERTY(meta=(Input))`
- L565 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))`
- L567 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathQuaternionSelectBool`  
`struct FRigVMFunction_MathQuaternionSelectBool : public FRigVMFunction_MathQuaternionBase`  
_L575-602_
- reflection: `USTRUCT(meta=(DisplayName="Select", Keywords="Pick,If", Deprecated = "4.26.0"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Return one of the two values based on the condition
- L579 _public function_ `FRigVMFunction_MathQuaternionSelectBool()`
- L585 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L589 _public member_ `bool Condition;` — `UPROPERTY(meta=(Input))`
- L592 _public member_ `FQuat IfTrue;` — `UPROPERTY(meta=(Input))`
- L595 _public member_ `FQuat IfFalse;` — `UPROPERTY(meta=(Input))`
- L598 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))`
- L600 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathQuaternionDot`  
`struct FRigVMFunction_MathQuaternionDot : public FRigVMFunction_MathQuaternionBase`  
_L608-632_
- reflection: `USTRUCT(meta=(DisplayName="Dot", Keywords="Dot,|"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Returns the dot product between two quaternions
- L612 _public function_ `FRigVMFunction_MathQuaternionDot()`
- L618 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L623 _public member_ `FQuat A;` — `UPROPERTY(meta=(Input))` — The first quaternion to compute the dot product for
- L627 _public member_ `FQuat B;` — `UPROPERTY(meta=(Input))` — The second quaternion to compute the dot product for
- L631 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting dot product between two quaternions

#### struct `FRigVMFunction_MathQuaternionUnit`  
`struct FRigVMFunction_MathQuaternionUnit : public FRigVMFunction_MathQuaternionUnaryOp`  
_L638-643_
- reflection: `USTRUCT(meta=(DisplayName="Unit", TemplateName="Unit", Keywords="Normalize"))`
- inherits: `FRigVMFunction_MathQuaternionUnaryOp`
- desc: Returns the normalized quaternion
- L641 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathQuaternionRotateVector`  
`struct FRigVMFunction_MathQuaternionRotateVector : public FRigVMFunction_MathQuaternionBase`  
_L649-673_
- reflection: `USTRUCT(meta=(DisplayName="Rotate Vector", TemplateName="Rotate Vector", Keywords="Transform,Multiply"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Rotates a given vector by the quaternion
- L653 _public function_ `FRigVMFunction_MathQuaternionRotateVector()`
- L659 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L664 _public member_ `FQuat Transform;` — `UPROPERTY(meta=(Input))` — The input quaternion to rotate the input vector by
- L668 _public member_ `FVector Vector;` — `UPROPERTY(meta=(Input))` — The input vector to rotate
- L672 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting rotated vector

#### struct `FRigVMFunction_MathQuaternionGetAxis`  
`struct FRigVMFunction_MathQuaternionGetAxis: public FRigVMFunction_MathQuaternionBase`  
_L679-704_
- reflection: `USTRUCT(meta = (DisplayName = "Axis", TemplateName="Axis", Keywords = "GetAxis,xAxis,yAxis,zAxis"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Extracts an axis from a quaternion rotation
- L683 _public function_ `FRigVMFunction_MathQuaternionGetAxis()`
- L690 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L695 _public member_ `FQuat Quaternion;` — `UPROPERTY(meta = (Input))` — The input quaternion
- L699 _public member_ `TEnumAsByte<EAxis::Type> Axis;` — `UPROPERTY(meta = (Input))` — The axis to extract
- L703 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting extracted axis

#### struct `FRigVMFunction_MathQuaternionSwingTwist`  
`struct FRigVMFunction_MathQuaternionSwingTwist : public FRigVMFunction_MathQuaternionBase`  
_L711-739_
- reflection: `USTRUCT(meta = (DisplayName = "To Swing & Twist"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Computes the swing and twist components of a quaternion
- L715 _public function_ `FRigVMFunction_MathQuaternionSwingTwist()`
- L721 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L726 _public member_ `FQuat Input;` — `UPROPERTY(meta = (Input))` — The input quaternion
- L730 _public member_ `FVector TwistAxis;` — `UPROPERTY(meta = (Input))` — The axis to treat as the twist axis
- L734 _public member_ `FQuat Swing;` — `UPROPERTY(meta = (Output))` — The resulting swing quaternion of the input quaternion
- L738 _public member_ `FQuat Twist;` — `UPROPERTY(meta = (Output))` — The resulting twist quaternion of the input quaternion

#### struct `FRigVMFunction_MathQuaternionRotationOrder`  
`struct FRigVMFunction_MathQuaternionRotationOrder : public FRigVMFunction_MathBase`  
_L745-761_
- reflection: `USTRUCT(meta = (DisplayName = "Rotation Order", Category = "Math|Quaternion", Constant))`
- inherits: `FRigVMFunction_MathBase`
- desc: Enum of possible rotation orders
- L749 _public function_ `FRigVMFunction_MathQuaternionRotationOrder()`
- L756 _public member_ `EEulerRotationOrder RotationOrder;` — `UPROPERTY(meta = (Input, Output))` — The constant rotation order
- L759 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathQuaternionMakeRelative`  
`struct FRigVMFunction_MathQuaternionMakeRelative : public FRigVMFunction_MathQuaternionBase`  
_L767-790_
- reflection: `USTRUCT(meta=(DisplayName="Make Relative", TemplateName="Make Relative", Keywords="Local,Global,Absolute"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Returns the relative local rotation within a parent's rotation
- L771 _public function_ `FRigVMFunction_MathQuaternionMakeRelative()`
- L776 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L781 _public member_ `FQuat Global;` — `UPROPERTY(meta=(Input))` — The global rotation quaternion to make relative
- L785 _public member_ `FQuat Parent;` — `UPROPERTY(meta=(Input))` — The parent global rotation to make the input relative to
- L789 _public member_ `FQuat Local;` — `UPROPERTY(meta=(Output))` — The resulting relative rotation

#### struct `FRigVMFunction_MathQuaternionMakeAbsolute`  
`struct FRigVMFunction_MathQuaternionMakeAbsolute : public FRigVMFunction_MathQuaternionBase`  
_L796-819_
- reflection: `USTRUCT(meta = (DisplayName = "Make Absolute", TemplateName="Make Absolute", Keywords = "Local,Global,Relative"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Returns the absolute global rotation within a parent's rotation
- L800 _public function_ `FRigVMFunction_MathQuaternionMakeAbsolute()`
- L805 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L810 _public member_ `FQuat Local;` — `UPROPERTY(meta = (Input))` — The input local rotation to make absolute
- L814 _public member_ `FQuat Parent;` — `UPROPERTY(meta = (Input))` — The parent global rotation to make the local absolute to
- L818 _public member_ `FQuat Global;` — `UPROPERTY(meta = (Output))` — The resulting global rotation

#### struct `FRigVMFunction_MathQuaternionMirrorTransform`  
`struct FRigVMFunction_MathQuaternionMirrorTransform : public FRigVMFunction_MathQuaternionBase`  
_L825-859_
- reflection: `USTRUCT(meta=(DisplayName="Mirror", TemplateName="Mirror"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Mirror a rotation about a central transform.
- L829 _public function_ `FRigVMFunction_MathQuaternionMirrorTransform()`
- L837 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L842 _public member_ `FQuat Value;` — `UPROPERTY(meta=(Input))` — The input quaternion
- L846 _public member_ `TEnumAsByte<EAxis::Type> MirrorAxis;` — `UPROPERTY(meta=(Input))` — the axis to mirror against
- L850 _public member_ `TEnumAsByte<EAxis::Type> AxisToFlip;` — `UPROPERTY(meta=(Input))` — the axis to flip for rotations
- L854 _public member_ `FTransform CentralTransform;` — `UPROPERTY(meta=(Input))` — The transform about which to mirror
- L858 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The resulting mirrored rotation

#### struct `FRigVMFunction_MathQuaternionFromXVector`  
`struct FRigVMFunction_MathQuaternionFromXVector : public FRigVMFunction_MathQuaternionBase`  
_L868-886_
- reflection: `USTRUCT(meta=(DisplayName="Rotation From X Vector", Keywords = "Orientation, From Axis"))`
- inherits: `FRigVMFunction_MathQuaternionBase`
- desc: Return the Quaternion orientation corresponding to the direction in which the vector points. Similar to the blueprint "Rotation From X Vector" version, returns a result without roll such that it preserves the up vector. @note If you don't care about preserving the up vector and just want the most direct rotation, you can use the faster "From Two Vectors"
- L872 _public function_ `FRigVMFunction_MathQuaternionFromXVector()`
- L876 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L881 _public member_ `FVector Value = FVector::XAxisVector;` — `UPROPERTY(meta=(Input))` — The input direction vector
- L885 _public member_ `FQuat Result = FQuat::Identity;` — `UPROPERTY(meta=(Output))` — The resulting rotation

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathRBFInterpolate.h` (Public)


#### enum `ERBFKernelType`  
`enum class ERBFKernelType : uint8`  
_L19-26_
- reflection: `UENUM()`
- desc: Function to use for each target falloff
- L21 _public enumerator_ `Gaussian`
- L22 _public enumerator_ `Exponential`
- L23 _public enumerator_ `Linear`
- L24 _public enumerator_ `Cubic`
- L25 _public enumerator_ `Quintic`

#### enum `ERBFQuatDistanceType`  
`enum class ERBFQuatDistanceType : uint8`  
_L31-37_
- reflection: `UENUM()`
- desc: Function to use for computing distance between the input and target quaternions.
- L33 _public enumerator_ `Euclidean`
- L34 _public enumerator_ `ArcLength`
- L35 _public enumerator_ `SwingAngle`
- L36 _public enumerator_ `TwistAngle`

#### enum `ERBFVectorDistanceType`  
`enum class ERBFVectorDistanceType : uint8`  
_L42-47_
- reflection: `UENUM()`
- desc: Function to use for computing distance between the input and target quaternions.
- L44 _public enumerator_ `Euclidean`
- L45 _public enumerator_ `Manhattan`
- L46 _public enumerator_ `ArcLength`

#### struct `FRigVMFunction_MathRBFInterpolateQuatWorkData`  
`struct FRigVMFunction_MathRBFInterpolateQuatWorkData`  
_L51-62_
- reflection: `USTRUCT()`
- L58 _public member_ `TRBFInterpolator<FQuat> Interpolator;` — There's no current mechanism for detecting whether an entire input stream is constant or variable in the RigVM. So what we do here is that the firs time around we set up an interpolator
- L59 _public member_ `TArray<FQuat> Targets;`
- L60 _public member_ `uint64 Hash = 0;`
- L61 _public member_ `bool bAreTargetsConstant = true;`

#### struct `FRigVMFunction_MathRBFInterpolateVectorWorkData`  
`struct FRigVMFunction_MathRBFInterpolateVectorWorkData`  
_L65-73_
- reflection: `USTRUCT()`
- L69 _public member_ `TRBFInterpolator<FVector> Interpolator;`
- L70 _public member_ `TArray<FVector> Targets;`
- L71 _public member_ `uint64 Hash = 0;`
- L72 _public member_ `bool bAreTargetsConstant = true;`

#### struct `FRigVMFunction_MathRBFInterpolateBase`  
`struct FRigVMFunction_MathRBFInterpolateBase : public FRigVMFunction_MathBase`  
_L80-84_
- reflection: `USTRUCT(meta = (Abstract, Category = "Math|RBF Interpolation"))`
- inherits: `FRigVMFunction_MathBase`
- desc: The base class for all pure RBF nodes

#### struct `FRigVMFunction_MathRBFInterpolateQuatBase`  
`struct FRigVMFunction_MathRBFInterpolateQuatBase : public FRigVMFunction_MathRBFInterpolateBase`  
_L90-138_
- reflection: `USTRUCT(meta = (Abstract, TemplateName="RBF Quaternion", Keywords = "RBF,Interpolate,Quaternion"))`
- inherits: `FRigVMFunction_MathRBFInterpolateBase`
- desc: The base class for all quaternion RBF nodes
- L97 _public member_ `FQuat Input = FQuat::Identity;` — `UPROPERTY(meta = (Input))` — The input quaternion
- L101 _public member_ `ERBFQuatDistanceType DistanceFunction = ERBFQuatDistanceType::ArcLength;` — `UPROPERTY(meta = (Input, Constant))` — The distance function to use
- L105 _public member_ `ERBFKernelType SmoothingFunction = ERBFKernelType::Gaussian;` — `UPROPERTY(meta = (Input, Constant))` — The smoothing function to use
- L109 _public member_ `float SmoothingAngle = 45.0f;` — `UPROPERTY(meta = (Input, Constant, UIMin = "0", UIMax = "180"))` — The smoothing angle
- L113 _public member_ `bool bNormalizeOutput = false;` — `UPROPERTY(meta = (Input, Constant))` — If true the resulting output will be normalized
- L117 _public member_ `FVector TwistAxis = FVector::ForwardVector;` — `UPROPERTY(meta = (Input, EditCondition = "DistanceFunction == ERBFQuatDistanceType::SwingAngle || DistanceFunction == ERBFQuatDistanceType::TwistAngle"))` — The twist axis of the input quaternion
- L120 _public member_ `FRigVMFunction_MathRBFInterpolateQuatWorkData WorkData;` — `UPROPERTY(transient)`
- L125 _protected prototype_ `template<typename T> static void GetInterpolatedWeights( FRigVMFunction_MathRBFInterpolateQuatWorkData& WorkData, const TArrayView<const T>& Targets, const FQuat& Input, ERBFQuatDistanceType DistanceFunction, ERBFKernelType SmoothingFunction, float SmoothingAngle, bool bNormalizeOutput, FVector TwistAxis, TArray<float>& Weights );`
- L137 _protected prototype_ `static uint64 HashTargets(const TArrayView<const FQuat>& Targets);`

#### struct `FRigVMFunction_MathRBFInterpolateVectorBase`  
`struct FRigVMFunction_MathRBFInterpolateVectorBase : public FRigVMFunction_MathRBFInterpolateBase`  
_L144-186_
- reflection: `USTRUCT(meta = (Abstract, TemplateName="RBF Vector", Keywords = "RBF,Interpolate,Vector"))`
- inherits: `FRigVMFunction_MathRBFInterpolateBase`
- desc: The base class for all vector RBF nodes
- L151 _public member_ `FVector Input = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — The input vector
- L155 _public member_ `ERBFVectorDistanceType DistanceFunction = ERBFVectorDistanceType::Euclidean;` — `UPROPERTY(meta = (Input, Constant))` — The distance function to use
- L159 _public member_ `ERBFKernelType SmoothingFunction = ERBFKernelType::Gaussian;` — `UPROPERTY(meta = (Input, Constant))` — The smoothing function to use
- L163 _public member_ `float SmoothingRadius = 5.0f;` — `UPROPERTY(meta = (Input, Constant))` — The radius to apply for the smoothing function
- L167 _public member_ `bool bNormalizeOutput = false;` — `UPROPERTY(meta = (Input, Constant))` — If true the resulting output will be normalized
- L170 _public member_ `FRigVMFunction_MathRBFInterpolateVectorWorkData WorkData;` — `UPROPERTY(transient)`
- L174 _protected prototype_ `template<typename T> static void GetInterpolatedWeights( FRigVMFunction_MathRBFInterpolateVectorWorkData& WorkData, const TArrayView<const T>& Targets, const FVector& Input, ERBFVectorDistanceType DistanceFunction, ERBFKernelType SmoothingFunction, float SmoothingRadius, bool bNormalizeOutput, TArray<float>& Weights );`
- L185 _protected prototype_ `static uint64 HashTargets(const TArrayView<const FVector>& Targets);`

#### struct `FMathRBFInterpolateQuatFloat_Target`  
`struct FMathRBFInterpolateQuatFloat_Target`  
_L193-202_
- reflection: `USTRUCT()`
- L198 _public member_ `FQuat Target = FQuat::Identity;` — `UPROPERTY(meta = (Input))`
- L201 _public member_ `float Value = 0.0f;` — `UPROPERTY(meta = (Input))`

#### struct `FRigVMFunction_MathRBFInterpolateQuatFloat`  
`struct FRigVMFunction_MathRBFInterpolateQuatFloat : public FRigVMFunction_MathRBFInterpolateQuatBase`  
_L206-221_
- reflection: `USTRUCT(meta = (Abstract, DisplayName = "RBF Quaternion to Float"))`
- inherits: `FRigVMFunction_MathRBFInterpolateQuatBase`
- desc: A RBF interpolator from quaternion to float
- L213 _public member_ `TArray<FMathRBFInterpolateQuatFloat_Target> Targets;` — `UPROPERTY(meta = (Input))` — The array of targets to interpolate within
- L217 _public member_ `float Output = 0.0f;` — `UPROPERTY(meta = (Output))` — The interpolated result
- L219 _public prototype_ `RIGVM_METHOD() void Execute() override;`

#### struct `FMathRBFInterpolateQuatVector_Target`  
`struct FMathRBFInterpolateQuatVector_Target`  
_L225-234_
- reflection: `USTRUCT()`
- L230 _public member_ `FQuat Target = FQuat::Identity;` — `UPROPERTY(meta = (Input))`
- L233 _public member_ `FVector Value = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))`

#### struct `FRigVMFunction_MathRBFInterpolateQuatVector`  
`struct FRigVMFunction_MathRBFInterpolateQuatVector : public FRigVMFunction_MathRBFInterpolateQuatBase`  
_L238-253_
- reflection: `USTRUCT(meta = (Abstract, DisplayName = "RBF Quaternion to Vector"))`
- inherits: `FRigVMFunction_MathRBFInterpolateQuatBase`
- desc: A RBF interpolator from quaternion to vector
- L245 _public member_ `TArray<FMathRBFInterpolateQuatVector_Target> Targets;` — `UPROPERTY(meta = (Input))` — The array of targets to interpolate within
- L249 _public member_ `FVector Output = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The interpolated result
- L251 _public prototype_ `RIGVM_METHOD() void Execute() override;`

#### struct `FMathRBFInterpolateQuatColor_Target`  
`struct FMathRBFInterpolateQuatColor_Target`  
_L257-266_
- reflection: `USTRUCT()`
- L262 _public member_ `FQuat Target = FQuat::Identity;` — `UPROPERTY(meta = (Input))`
- L265 _public member_ `FLinearColor Value = FLinearColor::Transparent;` — `UPROPERTY(meta = (Input))`

#### struct `FRigVMFunction_MathRBFInterpolateQuatColor`  
`struct FRigVMFunction_MathRBFInterpolateQuatColor : public FRigVMFunction_MathRBFInterpolateQuatBase`  
_L270-285_
- reflection: `USTRUCT(meta = (Abstract, DisplayName = "RBF Quaternion to Color"))`
- inherits: `FRigVMFunction_MathRBFInterpolateQuatBase`
- desc: A RBF interpolator from quaternion to color
- L277 _public member_ `TArray<FMathRBFInterpolateQuatColor_Target> Targets;` — `UPROPERTY(meta = (Input))` — The array of targets to interpolate within
- L281 _public member_ `FLinearColor Output = FLinearColor::Transparent;` — `UPROPERTY(meta = (Output))` — The interpolated result
- L283 _public prototype_ `RIGVM_METHOD() void Execute() override;`

#### struct `FMathRBFInterpolateQuatQuat_Target`  
`struct FMathRBFInterpolateQuatQuat_Target`  
_L289-298_
- reflection: `USTRUCT()`
- L294 _public member_ `FQuat Target = FQuat::Identity;` — `UPROPERTY(meta = (Input))`
- L297 _public member_ `FQuat Value = FQuat::Identity;` — `UPROPERTY(meta = (Input))`

#### struct `FRigVMFunction_MathRBFInterpolateQuatQuat`  
`struct FRigVMFunction_MathRBFInterpolateQuatQuat : public FRigVMFunction_MathRBFInterpolateQuatBase`  
_L302-317_
- reflection: `USTRUCT(meta = (Abstract, DisplayName = "RBF Quaternion to Quaternion"))`
- inherits: `FRigVMFunction_MathRBFInterpolateQuatBase`
- desc: A RBF interpolator from quaternion to quaternion
- L309 _public member_ `TArray<FMathRBFInterpolateQuatQuat_Target> Targets;` — `UPROPERTY(meta = (Input))` — The array of targets to interpolate within
- L313 _public member_ `FQuat Output = FQuat::Identity;` — `UPROPERTY(meta = (Output))` — The interpolated result
- L315 _public prototype_ `RIGVM_METHOD() void Execute() override;`

#### struct `FMathRBFInterpolateQuatXform_Target`  
`struct FMathRBFInterpolateQuatXform_Target`  
_L321-330_
- reflection: `USTRUCT()`
- L326 _public member_ `FQuat Target = FQuat::Identity;` — `UPROPERTY(meta = (Input))`
- L329 _public member_ `FTransform Value = FTransform::Identity;` — `UPROPERTY(meta = (Input))`

#### struct `FRigVMFunction_MathRBFInterpolateQuatXform`  
`struct FRigVMFunction_MathRBFInterpolateQuatXform : public FRigVMFunction_MathRBFInterpolateQuatBase`  
_L334-349_
- reflection: `USTRUCT(meta = (Abstract, DisplayName = "RBF Quaternion to Transform"))`
- inherits: `FRigVMFunction_MathRBFInterpolateQuatBase`
- desc: A RBF interpolator from quaternion to transform
- L341 _public member_ `TArray<FMathRBFInterpolateQuatXform_Target> Targets;` — `UPROPERTY(meta = (Input))` — The array of targets to interpolate within
- L345 _public member_ `FTransform Output = FTransform::Identity;` — `UPROPERTY(meta = (Output))` — The interpolated result
- L347 _public prototype_ `RIGVM_METHOD() void Execute() override;`

#### struct `FMathRBFInterpolateVectorFloat_Target`  
`struct FMathRBFInterpolateVectorFloat_Target`  
_L355-364_
- reflection: `USTRUCT()`
- L360 _public member_ `FVector Target = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))`
- L363 _public member_ `float Value = 0.0f;` — `UPROPERTY(meta = (Input))`

#### struct `FRigVMFunction_MathRBFInterpolateVectorFloat`  
`struct FRigVMFunction_MathRBFInterpolateVectorFloat : public FRigVMFunction_MathRBFInterpolateVectorBase`  
_L368-383_
- reflection: `USTRUCT(meta = (Abstract, DisplayName = "RBF Vector to Float", Keywords = "RBF,Interpolate,Vector"))`
- inherits: `FRigVMFunction_MathRBFInterpolateVectorBase`
- desc: A RBF interpolator from vector to float
- L375 _public member_ `TArray<FMathRBFInterpolateVectorFloat_Target> Targets;` — `UPROPERTY(meta = (Input))` — The array of targets to interpolate within
- L379 _public member_ `float Output = 0.0f;` — `UPROPERTY(meta = (Output))` — The interpolated result
- L381 _public prototype_ `RIGVM_METHOD() void Execute() override;`

#### struct `FMathRBFInterpolateVectorVector_Target`  
`struct FMathRBFInterpolateVectorVector_Target`  
_L387-396_
- reflection: `USTRUCT()`
- L392 _public member_ `FVector Target = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))`
- L395 _public member_ `FVector Value = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))`

#### struct `FRigVMFunction_MathRBFInterpolateVectorVector`  
`struct FRigVMFunction_MathRBFInterpolateVectorVector : public FRigVMFunction_MathRBFInterpolateVectorBase`  
_L400-415_
- reflection: `USTRUCT(meta = (Abstract, DisplayName = "RBF Vector to Vector", Keywords = "RBF,Interpolate,Vector"))`
- inherits: `FRigVMFunction_MathRBFInterpolateVectorBase`
- desc: A RBF interpolator from vector to vector
- L407 _public member_ `TArray<FMathRBFInterpolateVectorVector_Target> Targets;` — `UPROPERTY(meta = (Input))` — The array of targets to interpolate within
- L411 _public member_ `FVector Output = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The interpolated result
- L413 _public prototype_ `RIGVM_METHOD() void Execute() override;`

#### struct `FMathRBFInterpolateVectorColor_Target`  
`struct FMathRBFInterpolateVectorColor_Target`  
_L419-428_
- reflection: `USTRUCT()`
- L424 _public member_ `FVector Target = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))`
- L427 _public member_ `FLinearColor Value = FLinearColor::Transparent;` — `UPROPERTY(meta = (Input))`

#### struct `FRigVMFunction_MathRBFInterpolateVectorColor`  
`struct FRigVMFunction_MathRBFInterpolateVectorColor : public FRigVMFunction_MathRBFInterpolateVectorBase`  
_L432-447_
- reflection: `USTRUCT(meta = (Abstract, DisplayName = "RBF Vector to Color", Keywords = "RBF,Interpolate,Vector"))`
- inherits: `FRigVMFunction_MathRBFInterpolateVectorBase`
- desc: A RBF interpolator from vector to color
- L439 _public member_ `TArray<FMathRBFInterpolateVectorColor_Target> Targets;` — `UPROPERTY(meta = (Input))` — The array of targets to interpolate within
- L443 _public member_ `FLinearColor Output = FLinearColor::Transparent;` — `UPROPERTY(meta = (Output))` — The interpolated result
- L445 _public prototype_ `RIGVM_METHOD() void Execute() override;`

#### struct `FMathRBFInterpolateVectorQuat_Target`  
`struct FMathRBFInterpolateVectorQuat_Target`  
_L452-461_
- reflection: `USTRUCT()`
- L457 _public member_ `FVector Target = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))`
- L460 _public member_ `FQuat Value = FQuat::Identity;` — `UPROPERTY(meta = (Input))`

#### struct `FRigVMFunction_MathRBFInterpolateVectorQuat`  
`struct FRigVMFunction_MathRBFInterpolateVectorQuat : public FRigVMFunction_MathRBFInterpolateVectorBase`  
_L465-480_
- reflection: `USTRUCT(meta = (Abstract, DisplayName = "RBF Vector to Quat", Keywords = "RBF,Interpolate,Vector"))`
- inherits: `FRigVMFunction_MathRBFInterpolateVectorBase`
- desc: A RBF interpolator from vector to quaternion
- L472 _public member_ `TArray<FMathRBFInterpolateVectorQuat_Target> Targets;` — `UPROPERTY(meta = (Input))` — The array of targets to interpolate within
- L476 _public member_ `FQuat Output = FQuat::Identity;` — `UPROPERTY(meta = (Output))` — The interpolated result
- L478 _public prototype_ `RIGVM_METHOD() void Execute() override;`

#### struct `FMathRBFInterpolateVectorXform_Target`  
`struct FMathRBFInterpolateVectorXform_Target`  
_L483-492_
- reflection: `USTRUCT()`
- L488 _public member_ `FVector Target = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))`
- L491 _public member_ `FTransform Value = FTransform::Identity;` — `UPROPERTY(meta = (Input))`

#### struct `FRigVMFunction_MathRBFInterpolateVectorXform`  
`struct FRigVMFunction_MathRBFInterpolateVectorXform : public FRigVMFunction_MathRBFInterpolateVectorBase`  
_L496-511_
- reflection: `USTRUCT(meta = (Abstract, DisplayName = "RBF Vector to Transform", Keywords = "RBF,Interpolate,Vector"))`
- inherits: `FRigVMFunction_MathRBFInterpolateVectorBase`
- desc: A RBF interpolator from vector to transform
- L503 _public member_ `TArray<FMathRBFInterpolateVectorXform_Target> Targets;` — `UPROPERTY(meta = (Input))` — The array of targets to interpolate within
- L507 _public member_ `FTransform Output = FTransform::Identity;` — `UPROPERTY(meta = (Output))` — The interpolated result
- L509 _public prototype_ `RIGVM_METHOD() void Execute() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathRay.h` (Public)


#### struct `FRigVMFunction_MathRayBase`  
`struct FRigVMFunction_MathRayBase : public FRigVMFunction_MathBase`  
_L14-17_
- reflection: `USTRUCT(meta=(Abstract, Category="Math|Ray", MenuDescSuffix="(Ray)"))`
- inherits: `FRigVMFunction_MathBase`
- desc: The base class for all pure ray math nodes

#### struct `FRigVMFunction_MathRayIntersectRay`  
`struct FRigVMFunction_MathRayIntersectRay : public FRigVMFunction_MathRayBase`  
_L23-62_
- reflection: `USTRUCT(meta = (DisplayName = "Intersect Ray", Keywords = "Closest,Ray,Cross"))`
- inherits: `FRigVMFunction_MathRayBase`
- desc: Returns the closest point intersection of a ray with another ray
- L27 _public function_ `FRigVMFunction_MathRayIntersectRay()`
- L34 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L39 _public member_ `FRay A;` — `UPROPERTY(meta = (Input))` — The first ray to intersect
- L43 _public member_ `FRay B;` — `UPROPERTY(meta = (Input))` — The second ray to intersect
- L49 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting intersection position. This is either on the rays themselves or at the closest position between the two.
- L53 _public member_ `float Distance;` — `UPROPERTY(meta = (Output))` — The distance between the two rays (or 0 if they touch)
- L57 _public member_ `float RatioA;` — `UPROPERTY(meta = (Output))` — The ratio on the first ray at the intersection
- L61 _public member_ `float RatioB;` — `UPROPERTY(meta = (Output))` — The ratio on the second ray at the intersection

#### struct `FRigVMFunction_MathRayIntersectPlane`  
`struct FRigVMFunction_MathRayIntersectPlane : public FRigVMFunction_MathRayBase`  
_L68-107_
- reflection: `USTRUCT(meta = (DisplayName = "Intersect Plane", Keywords = "Closest,Ray,Cross"))`
- inherits: `FRigVMFunction_MathRayBase`
- desc: Returns the closest point intersection of a ray with a plane
- L72 _public function_ `FRigVMFunction_MathRayIntersectPlane()`
- L81 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L86 _public member_ `FRay Ray;` — `UPROPERTY(meta = (Input))` — The ray to intersect with the plane
- L90 _public member_ `FVector PlanePoint;` — `UPROPERTY(meta = (Input))` — The point on the plane to intersect the ray with
- L94 _public member_ `FVector PlaneNormal;` — `UPROPERTY(meta = (Input))` — The normal of the plane to intersect the ray with
- L98 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting intersection position
- L102 _public member_ `float Distance;` — `UPROPERTY(meta = (Output))` — The distance of the ray origin to the plane
- L106 _public member_ `float Ratio;` — `UPROPERTY(meta = (Output))` — The ratio along the ray up to the intersection point

#### struct `FRigVMFunction_MathRayGetAt`  
`struct FRigVMFunction_MathRayGetAt : public FRigVMFunction_MathRayBase`  
_L113-138_
- reflection: `USTRUCT(meta=(DisplayName="GetAt", Keywords="Ratio,Percentage"))`
- inherits: `FRigVMFunction_MathRayBase`
- desc: Returns the position on a ray
- L117 _public function_ `FRigVMFunction_MathRayGetAt()`
- L124 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L129 _public member_ `FRay Ray;` — `UPROPERTY(meta = (Input))` — The ray to query
- L133 _public member_ `float Ratio;` — `UPROPERTY(meta = (Input))` — The ratio to query the ray at
- L137 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting position on the ray

#### struct `FRigVMFunction_MathRayTransform`  
`struct FRigVMFunction_MathRayTransform : public FRigVMFunction_MathRayBase`  
_L144-168_
- reflection: `USTRUCT(meta=(DisplayName="Transform Ray", Keywords="Multiply,Project"))`
- inherits: `FRigVMFunction_MathRayBase`
- desc: Transforms a ray
- L148 _public function_ `FRigVMFunction_MathRayTransform()`
- L154 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L159 _public member_ `FRay Ray;` — `UPROPERTY(meta = (Input))` — The ray to transform
- L163 _public member_ `FTransform Transform;` — `UPROPERTY(meta = (Input))` — The transform to apply to the ray
- L167 _public member_ `FRay Result;` — `UPROPERTY(meta = (Output))` — The resulting transformed ray

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathTransform.h` (Public)


#### struct `FRigVMFunction_MathTransformBase`  
`struct FRigVMFunction_MathTransformBase : public FRigVMFunction_MathBase`  
_L15-18_
- reflection: `USTRUCT(meta=(Abstract, Category="Math|Transform", MenuDescSuffix="(Transform)"))`
- inherits: `FRigVMFunction_MathBase`
- desc: The base class for all pure transform math nodes

#### struct `FRigVMFunction_MathTransformMutableBase`  
`struct FRigVMFunction_MathTransformMutableBase : public FRigVMFunction_MathMutableBase`  
_L24-27_
- reflection: `USTRUCT(meta=(Abstract, Category="Math|Transform", MenuDescSuffix="(Transform)"))`
- inherits: `FRigVMFunction_MathMutableBase`
- desc: The base class for all mutable transform math nodes

#### struct `FRigVMFunction_MathTransformUnaryOp`  
`struct FRigVMFunction_MathTransformUnaryOp : public FRigVMFunction_MathTransformBase`  
_L33-49_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: The base class for all unary transform math operations
- L37 _public function_ `FRigVMFunction_MathTransformUnaryOp()`
- L44 _public member_ `FTransform Value;` — `UPROPERTY(meta=(Input))` — The input value
- L48 _public member_ `FTransform Result;` — `UPROPERTY(meta=(Output))` — The result of the operation

#### struct `FRigVMFunction_MathTransformBinaryOp`  
`struct FRigVMFunction_MathTransformBinaryOp : public FRigVMFunction_MathTransformBase`  
_L55-75_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: The base class for all binary transform math operations
- L59 _public function_ `FRigVMFunction_MathTransformBinaryOp()`
- L66 _public member_ `FTransform A;` — `UPROPERTY(meta=(Input))` — The first value for the operation
- L70 _public member_ `FTransform B;` — `UPROPERTY(meta=(Input))` — The second value for the operation
- L74 _public member_ `FTransform Result;` — `UPROPERTY(meta=(Output))` — The resulting value

#### struct `FRigVMFunction_MathTransformBinaryAggregateOp`  
`struct FRigVMFunction_MathTransformBinaryAggregateOp : public FRigVMFunction_MathTransformBase`  
_L81-101_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: The base class for all aggregational transform math operations
- L85 _public function_ `FRigVMFunction_MathTransformBinaryAggregateOp()`
- L92 _public member_ `FTransform A;` — `UPROPERTY(meta=(Input, Aggregate))` — The first value for the operation
- L96 _public member_ `FTransform B;` — `UPROPERTY(meta=(Input, Aggregate))` — The second value for the operation
- L100 _public member_ `FTransform Result;` — `UPROPERTY(meta=(Output, Aggregate))` — The resulting value

#### struct `FRigVMFunction_MathTransformMake`  
`struct FRigVMFunction_MathTransformMake : public FRigVMFunction_MathTransformBase`  
_L107-135_
- reflection: `USTRUCT(meta=(DisplayName="Make Transform", Keywords="Make,Construct,Constant", Deprecated="5.7"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Makes a transform from its components
- L110 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L113 _public function_ `FRigVMFunction_MathTransformMake()`
- L122 _public member_ `FVector Translation;` — `UPROPERTY(meta=(Input))`
- L125 _public member_ `FQuat Rotation;` — `UPROPERTY(meta=(Input))`
- L128 _public member_ `FVector Scale;` — `UPROPERTY(meta=(Input))`
- L131 _public member_ `FTransform Result;` — `UPROPERTY(meta=(Output))`
- L133 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathTransformFromEulerTransform`  
`struct FRigVMFunction_MathTransformFromEulerTransform : public FRigVMFunction_MathTransformBase`  
_L141-162_
- reflection: `USTRUCT(meta=(DisplayName="From Euler Transform", TemplateName="FromEulerTransform", Keywords="Make,Construct", Deprecated="5.0.1"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Makes a quaternion based transform from a euler based transform
- L145 _public function_ `FRigVMFunction_MathTransformFromEulerTransform()`
- L151 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L155 _public member_ `FEulerTransform EulerTransform;` — `UPROPERTY(meta=(Input))`
- L158 _public member_ `FTransform Result;` — `UPROPERTY(meta=(Output))`
- L160 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathTransformFromEulerTransformV2`  
`struct FRigVMFunction_MathTransformFromEulerTransformV2 : public FRigVMFunction_MathTransformBase`  
_L168-188_
- reflection: `USTRUCT(meta=(DisplayName="To Transform", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Makes a quaternion based transform from a euler based transform
- L172 _public function_ `FRigVMFunction_MathTransformFromEulerTransformV2()`
- L178 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L183 _public member_ `FEulerTransform Value;` — `UPROPERTY(meta=(Input))` — The input euler transform to convert
- L187 _public member_ `FTransform Result;` — `UPROPERTY(meta=(Output))` — The resulting composed transform

#### struct `FRigVMFunction_MathTransformToEulerTransform`  
`struct FRigVMFunction_MathTransformToEulerTransform : public FRigVMFunction_MathTransformBase`  
_L194-214_
- reflection: `USTRUCT(meta=(DisplayName="To Euler Transform", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Retrieves a euler based transform from a quaternion based transform
- L198 _public function_ `FRigVMFunction_MathTransformToEulerTransform()`
- L204 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L209 _public member_ `FTransform Value;` — `UPROPERTY(meta=(Input))` — The input transform to convert
- L213 _public member_ `FEulerTransform Result;` — `UPROPERTY(meta=(Output))` — The resulting composed euler transform

#### struct `FRigVMFunction_MathTransformToVectors`  
`struct FRigVMFunction_MathTransformToVectors : public FRigVMFunction_MathTransformBase`  
_L220-248_
- reflection: `USTRUCT(meta=(DisplayName="To Vectors", TemplateName="ToVectors", Keywords="Forward,Right,Up"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Retrieves the forward, right and up vectors of a transform's quaternion
- L224 _public function_ `FRigVMFunction_MathTransformToVectors()`
- L230 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L235 _public member_ `FTransform Value;` — `UPROPERTY(meta=(Input))` — The input transform
- L239 _public member_ `FVector Forward;` — `UPROPERTY(meta=(Output))` — The rotation's forward axis
- L243 _public member_ `FVector Right;` — `UPROPERTY(meta=(Output))` — The rotation's right axis
- L247 _public member_ `FVector Up;` — `UPROPERTY(meta=(Output))` — The rotation's up axis

#### struct `FRigVMFunction_MathTransformMul`  
`struct FRigVMFunction_MathTransformMul : public FRigVMFunction_MathTransformBinaryAggregateOp`  
_L254-259_
- reflection: `USTRUCT(meta=(DisplayName="Multiply", TemplateName="Multiply", Keywords="Product,*,Global"))`
- inherits: `FRigVMFunction_MathTransformBinaryAggregateOp`
- desc: Returns the product of the two values
- L257 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathTransformMakeRelative`  
`struct FRigVMFunction_MathTransformMakeRelative : public FRigVMFunction_MathTransformBase`  
_L265-288_
- reflection: `USTRUCT(meta=(DisplayName="Make Relative", TemplateName="Make Relative", Keywords="Local,Global,Absolute"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Returns the relative local transform within a parent's transform
- L269 _public function_ `FRigVMFunction_MathTransformMakeRelative()`
- L274 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L279 _public member_ `FTransform Global;` — `UPROPERTY(meta=(Input))` — The global transform to make relative
- L283 _public member_ `FTransform Parent;` — `UPROPERTY(meta=(Input))` — The parent global transform to make the input relative to
- L287 _public member_ `FTransform Local;` — `UPROPERTY(meta=(Output))` — The resulting relative transform

#### struct `FRigVMFunction_MathTransformMakeAbsolute`  
`struct FRigVMFunction_MathTransformMakeAbsolute : public FRigVMFunction_MathTransformBase`  
_L294-317_
- reflection: `USTRUCT(meta = (DisplayName = "Make Absolute", TemplateName="Make Absolute", Keywords = "Local,Global,Relative"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Returns the absolute global transform within a parent's transform
- L298 _public function_ `FRigVMFunction_MathTransformMakeAbsolute()`
- L303 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L308 _public member_ `FTransform Local;` — `UPROPERTY(meta = (Input))` — The input local transform to make absolute
- L312 _public member_ `FTransform Parent;` — `UPROPERTY(meta = (Input))` — The parent global transform to make the local absolute to
- L316 _public member_ `FTransform Global;` — `UPROPERTY(meta = (Output))` — The resulting global transform

#### struct `FRigVMFunction_MathTransformAccumulateArray`  
`struct FRigVMFunction_MathTransformAccumulateArray : public FRigVMFunction_MathTransformMutableBase`  
_L325-362_
- reflection: `USTRUCT(meta=(DisplayName="Make Transform Array Relative", Keywords="Local,Global,Absolute,Array,Accumulate"))`
- inherits: `FRigVMFunction_MathTransformMutableBase`
- desc: Treats the provided transforms as a chain with global / local transforms, and projects each transform into the target space. Optionally you can provide a custom parent indices array, with which you can represent more than just chains.
- L329 _public function_ `FRigVMFunction_MathTransformAccumulateArray()`
- L335 _public prototype_ `virtual FString GetUnitLabel() const override;`
- L337 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L342 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY(meta=(Input, Output))` — The input transform array to accumulate
- L348 _public member_ `ERigVMTransformSpace TargetSpace;` — `UPROPERTY(meta = (Input))` — Defines the space to project to
- L354 _public member_ `FTransform Root;` — `UPROPERTY(meta=(Input))` — Provides the parent transform for the root
- L361 _public member_ `TArray<int32> ParentIndices;` — `UPROPERTY(meta=(Input))` — If this array is the same size as the transforms array the indices will be used to look up each transform's parent. They are expected to be in order.

#### struct `FRigVMFunction_MathTransformInverse`  
`struct FRigVMFunction_MathTransformInverse : public FRigVMFunction_MathTransformUnaryOp`  
_L368-373_
- reflection: `USTRUCT(meta=(DisplayName="Inverse", TemplateName="Inverse"))`
- inherits: `FRigVMFunction_MathTransformUnaryOp`
- desc: Returns the inverted transform of the input
- L371 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathTransformLerp`  
`struct FRigVMFunction_MathTransformLerp : public FRigVMFunction_MathTransformBase`  
_L379-407_
- reflection: `USTRUCT(meta=(DisplayName="Interpolate", TemplateName="Interpolate", Keywords="Lerp,Mix,Blend"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Linearly interpolates between A and B using the ratio T
- L383 _public function_ `FRigVMFunction_MathTransformLerp()`
- L389 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L394 _public member_ `FTransform A;` — `UPROPERTY(meta=(Input))` — The first transform to interpolate from
- L398 _public member_ `FTransform B;` — `UPROPERTY(meta=(Input))` — The second transform to interpolate to
- L402 _public member_ `float T;` — `UPROPERTY(meta=(Input, UIMin = "0", UIMax = "1"))` — The blend value for the interpolation
- L406 _public member_ `FTransform Result;` — `UPROPERTY(meta=(Output))` — The resulting interpolated transform

#### struct `FRigVMFunction_MathTransformSelectBool`  
`struct FRigVMFunction_MathTransformSelectBool : public FRigVMFunction_MathTransformBase`  
_L413-440_
- reflection: `USTRUCT(meta=(DisplayName="Select", Keywords="Pick,If", Deprecated = "4.26.0"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Return one of the two values based on the condition
- L417 _public function_ `FRigVMFunction_MathTransformSelectBool()`
- L423 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L427 _public member_ `bool Condition;` — `UPROPERTY(meta=(Input))`
- L430 _public member_ `FTransform IfTrue;` — `UPROPERTY(meta=(Input))`
- L433 _public member_ `FTransform IfFalse;` — `UPROPERTY(meta=(Input))`
- L436 _public member_ `FTransform Result;` — `UPROPERTY(meta=(Output))`
- L438 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathTransformRotateVector`  
`struct FRigVMFunction_MathTransformRotateVector : public FRigVMFunction_MathTransformBase`  
_L446-470_
- reflection: `USTRUCT(meta=(DisplayName="Rotate Vector", TemplateName="Rotate Vector", Keywords="Transform,Direction,TransformDirection"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Rotates a given vector (direction) by the transform
- L450 _public function_ `FRigVMFunction_MathTransformRotateVector()`
- L456 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L461 _public member_ `FTransform Transform;` — `UPROPERTY(meta=(Input))` — The input transform to rotate the input vector by
- L465 _public member_ `FVector Vector;` — `UPROPERTY(meta=(Input))` — The input vector to rotate
- L469 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting rotated vector

#### struct `FRigVMFunction_MathTransformTransformVector`  
`struct FRigVMFunction_MathTransformTransformVector : public FRigVMFunction_MathTransformBase`  
_L476-500_
- reflection: `USTRUCT(meta=(DisplayName="Transform Location", Keywords="Multiply"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Multiplies a given vector (location) by the transform
- L480 _public function_ `FRigVMFunction_MathTransformTransformVector()`
- L486 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L491 _public member_ `FTransform Transform;` — `UPROPERTY(meta=(Input))` — The input transform to transform the input vector by
- L495 _public member_ `FVector Location;` — `UPROPERTY(meta=(Input))` — The input vector to transform
- L499 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting transformed vector

#### struct `FRigVMFunction_MathTransformFromSRT`  
`struct FRigVMFunction_MathTransformFromSRT : public FRigVMFunction_MathTransformBase`  
_L506-546_
- reflection: `USTRUCT(meta=(DisplayName="Transform from SRT", Keywords ="EulerTransform,Scale,Rotation,Orientation,Translation,Location"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Composes a Transform (and Euler Transform) from its components.
- L510 _public function_ `FRigVMFunction_MathTransformFromSRT()`
- L520 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L525 _public member_ `FVector Location;` — `UPROPERTY(meta=(Input))` — The location for the desired transform
- L529 _public member_ `FVector Rotation;` — `UPROPERTY(meta=(Input))` — The euler angles in degrees for the desired transform
- L533 _public member_ `EEulerRotationOrder RotationOrder;` — `UPROPERTY(meta=(Input))` — The rotation order to interpret the euler angles by
- L537 _public member_ `FVector Scale;` — `UPROPERTY(meta=(Input))` — The scale for the desired transform
- L541 _public member_ `FTransform Transform;` — `UPROPERTY(meta=(Output))` — The result as a transform
- L545 _public member_ `FEulerTransform EulerTransform;` — `UPROPERTY(meta=(Output))` — The result as a euler transform

#### struct `FRigVMFunction_MathTransformArrayToSRT`  
`struct FRigVMFunction_MathTransformArrayToSRT : public FRigVMFunction_MathTransformBase`  
_L553-579_
- reflection: `USTRUCT(meta = (DisplayName = "Transform Array to SRT", Keywords = "EulerTransform,Scale,Rotation,Orientation,Translation,Location"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Decomposes a Transform Array to its components.
- L557 _public function_ `FRigVMFunction_MathTransformArrayToSRT()`
- L561 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L566 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY(meta = (Input))` — The input transform array to decompose
- L570 _public member_ `TArray<FVector> Translations;` — `UPROPERTY(meta = (Output))` — The array of translations - one for each input transform
- L574 _public member_ `TArray<FQuat> Rotations;` — `UPROPERTY(meta = (Output))` — The array of rotation - one for each input transform
- L578 _public member_ `TArray<FVector> Scales;` — `UPROPERTY(meta = (Output))` — The array of scale values - one for each input transform

#### struct `FRigVMFunction_MathTransformClampSpatially`  
`struct FRigVMFunction_MathTransformClampSpatially : public FRigVMFunction_MathTransformBase`  
_L585-650_
- reflection: `USTRUCT(meta = (DisplayName = "Clamp Spatially", TemplateName="ClampSpatially", Keywords = "Collide,Collision"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Clamps a transform's position using a plane collision, cylindric collision or spherical collision.
- L589 _public function_ `FRigVMFunction_MathTransformClampSpatially()`
- L602 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L607 _public member_ `FTransform Value;` — `UPROPERTY(meta = (Input))` — The input transform to clamp
- L611 _public member_ `TEnumAsByte<EAxis::Type> Axis;` — `UPROPERTY(meta = (Input))` — The axis to use for the filter
- L615 _public member_ `TEnumAsByte<ERigVMClampSpatialMode::Type> Type;` — `UPROPERTY(meta = (Input))` — The filter / spatial mode to use
- L621 _public member_ `float Minimum;` — `UPROPERTY(meta = (Input))` — The minimum allowed distance at which a collision occurs. Note: For capsule this represents the radius. Disable by setting to 0.0.
- L628 _public member_ `float Maximum;` — `UPROPERTY(meta = (Input))` — This maximum allowed distance. A collision will occur towards the center at this wall. Note: For capsule this represents the length. Disable by setting to 0.0.
- L633 _public member_ `FTransform Space;` — `UPROPERTY(meta = (Input))` — The space this spatial clamp happens within. The input position will be projected into this space.
- L637 _public member_ `bool bDrawDebug;` — `UPROPERTY(meta = (Input))` — Draws debug information if True
- L641 _public member_ `FLinearColor DebugColor;` — `UPROPERTY(meta = (Input))` — The color to use for the debug draw
- L645 _public member_ `float DebugThickness;` — `UPROPERTY(meta = (Input))` — The thickness to use for the debug draw
- L649 _public member_ `FTransform Result;` — `UPROPERTY(meta = (Output))` — The resulting transform with a clamped position

#### struct `FRigVMFunction_MathTransformMirrorTransform`  
`struct FRigVMFunction_MathTransformMirrorTransform : public FRigVMFunction_MathTransformBase`  
_L656-690_
- reflection: `USTRUCT(meta=(DisplayName="Mirror", TemplateName="Mirror"))`
- inherits: `FRigVMFunction_MathTransformBase`
- desc: Mirror a transform about a central transform.
- L660 _public function_ `FRigVMFunction_MathTransformMirrorTransform()`
- L668 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L673 _public member_ `FTransform Value;` — `UPROPERTY(meta=(Input))` — The input transform to mirror
- L677 _public member_ `TEnumAsByte<EAxis::Type> MirrorAxis;` — `UPROPERTY(meta=(Input))` — the axis to mirror against
- L681 _public member_ `TEnumAsByte<EAxis::Type> AxisToFlip;` — `UPROPERTY(meta=(Input))` — the axis to flip for rotations
- L685 _public member_ `FTransform CentralTransform;` — `UPROPERTY(meta=(Input))` — The transform about which to mirror
- L689 _public member_ `FTransform Result;` — `UPROPERTY(meta=(Output))` — The resulting mirrored transform

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_MathVector.h` (Public)


#### struct `FRigVMFunction_MathVectorBase`  
`struct FRigVMFunction_MathVectorBase : public FRigVMFunction_MathBase`  
_L13-16_
- reflection: `USTRUCT(meta=(Abstract, Category="Math|Vector", MenuDescSuffix="(Vector)"))`
- inherits: `FRigVMFunction_MathBase`
- desc: The base class for all pure vector math nodes

#### struct `FRigVMFunction_MathVectorUnaryOp`  
`struct FRigVMFunction_MathVectorUnaryOp : public FRigVMFunction_MathVectorBase`  
_L22-38_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: The base class for all unary vector math operations
- L26 _public function_ `FRigVMFunction_MathVectorUnaryOp()`
- L33 _public member_ `FVector Value;` — `UPROPERTY(meta=(Input))` — The input value
- L37 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The result of the operation

#### struct `FRigVMFunction_MathVectorBinaryOp`  
`struct FRigVMFunction_MathVectorBinaryOp : public FRigVMFunction_MathVectorBase`  
_L44-64_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: The base class for all binary vector math operations
- L48 _public function_ `FRigVMFunction_MathVectorBinaryOp()`
- L55 _public member_ `FVector A;` — `UPROPERTY(meta=(Input))` — The first value for the operation
- L59 _public member_ `FVector B;` — `UPROPERTY(meta=(Input))` — The second value for the operation
- L63 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting value

#### struct `FRigVMFunction_MathVectorBinaryAggregateOp`  
`struct FRigVMFunction_MathVectorBinaryAggregateOp : public FRigVMFunction_MathVectorBase`  
_L70-90_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: The base class for all aggregational vector math operations
- L74 _public function_ `FRigVMFunction_MathVectorBinaryAggregateOp()`
- L81 _public member_ `FVector A;` — `UPROPERTY(meta=(Input, Aggregate))` — The first value for the operation
- L85 _public member_ `FVector B;` — `UPROPERTY(meta=(Input, Aggregate))` — The second value for the operation
- L89 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output, Aggregate))` — The resulting value

#### struct `FRigVMFunction_MathVectorMake`  
`struct FRigVMFunction_MathVectorMake : public FRigVMFunction_MathVectorBase`  
_L96-122_
- reflection: `USTRUCT(meta=(DisplayName="Make Vector", Keywords="Make,Construct,Constant", Deprecated="5.7"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Makes a vector from its components
- L99 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L102 _public function_ `FRigVMFunction_MathVectorMake()`
- L109 _public member_ `float X;` — `UPROPERTY(meta=(Input))`
- L112 _public member_ `float Y;` — `UPROPERTY(meta=(Input))`
- L115 _public member_ `float Z;` — `UPROPERTY(meta=(Input))`
- L118 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))`
- L120 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathVectorFromFloat`  
`struct FRigVMFunction_MathVectorFromFloat : public FRigVMFunction_MathVectorBase`  
_L128-147_
- reflection: `USTRUCT(meta=(DisplayName="From Float", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Makes a vector from a single float
- L131 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L134 _public function_ `FRigVMFunction_MathVectorFromFloat()`
- L142 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The input float value to use for all vector components
- L146 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting (Value,Value,Value) vector

#### struct `FRigVMFunction_MathVectorFromDouble`  
`struct FRigVMFunction_MathVectorFromDouble : public FRigVMFunction_MathVectorBase`  
_L153-172_
- reflection: `USTRUCT(meta=(DisplayName="From Double", TemplateName="Cast", ExecuteContext="FRigVMExecuteContext", Keywords="Make,Construct"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Makes a vector from a single double
- L156 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L159 _public function_ `FRigVMFunction_MathVectorFromDouble()`
- L167 _public member_ `double Value;` — `UPROPERTY(meta=(Input))` — The input value to use for all vector components
- L171 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting (Value,Value,Value) vector

#### struct `FRigVMFunction_MathVectorAdd`  
`struct FRigVMFunction_MathVectorAdd : public FRigVMFunction_MathVectorBinaryAggregateOp`  
_L178-184_
- reflection: `USTRUCT(meta=(DisplayName="Add", TemplateName="Add", Keywords="Sum,+"))`
- inherits: `FRigVMFunction_MathVectorBinaryAggregateOp`
- desc: Returns the sum of the two values
- L182 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorSub`  
`struct FRigVMFunction_MathVectorSub : public FRigVMFunction_MathVectorBinaryAggregateOp`  
_L190-196_
- reflection: `USTRUCT(meta=(DisplayName="Subtract", TemplateName="Subtract", Keywords="-"))`
- inherits: `FRigVMFunction_MathVectorBinaryAggregateOp`
- desc: Returns the difference of the two values
- L194 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorMul`  
`struct FRigVMFunction_MathVectorMul : public FRigVMFunction_MathVectorBinaryAggregateOp`  
_L202-213_
- reflection: `USTRUCT(meta=(DisplayName="Multiply", TemplateName="Multiply", Keywords="Product,*"))`
- inherits: `FRigVMFunction_MathVectorBinaryAggregateOp`
- desc: Returns the product of the two values
- L206 _public function_ `FRigVMFunction_MathVectorMul()`
- L211 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorScale`  
`struct FRigVMFunction_MathVectorScale : public FRigVMFunction_MathVectorBase`  
_L219-243_
- reflection: `USTRUCT(meta = (DisplayName = "Scale", TemplateName="Scale", Keywords = "Multiply,Product,*,ByScalar,ByFloat"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns the product of the vector and the float value
- L223 _public function_ `FRigVMFunction_MathVectorScale()`
- L229 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L234 _public member_ `FVector Value;` — `UPROPERTY(meta = (Input))` — The input vector to scale
- L238 _public member_ `float Factor;` — `UPROPERTY(meta = (Input))` — The factor to scale the input vector by
- L242 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting scaled vector

#### struct `FRigVMFunction_MathVectorDiv`  
`struct FRigVMFunction_MathVectorDiv : public FRigVMFunction_MathVectorBinaryOp`  
_L249-260_
- reflection: `USTRUCT(meta=(DisplayName="Divide", TemplateName="Divide", Keywords="Division,Divisor,/"))`
- inherits: `FRigVMFunction_MathVectorBinaryOp`
- desc: Returns the division of the two values
- L253 _public function_ `FRigVMFunction_MathVectorDiv()`
- L258 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorMod`  
`struct FRigVMFunction_MathVectorMod : public FRigVMFunction_MathVectorBinaryOp`  
_L266-278_
- reflection: `USTRUCT(meta=(DisplayName="Modulo", TemplateName="Modulo", Keywords="%,fmod"))`
- inherits: `FRigVMFunction_MathVectorBinaryOp`
- desc: Returns the modulo of the two values
- L270 _public function_ `FRigVMFunction_MathVectorMod()`
- L276 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorMin`  
`struct FRigVMFunction_MathVectorMin : public FRigVMFunction_MathVectorBinaryAggregateOp`  
_L284-290_
- reflection: `USTRUCT(meta=(DisplayName="Minimum", TemplateName="Minimum"))`
- inherits: `FRigVMFunction_MathVectorBinaryAggregateOp`
- desc: Returns the smaller of the two values for each component
- L288 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorMax`  
`struct FRigVMFunction_MathVectorMax : public FRigVMFunction_MathVectorBinaryAggregateOp`  
_L296-302_
- reflection: `USTRUCT(meta=(DisplayName="Maximum", TemplateName="Maximum"))`
- inherits: `FRigVMFunction_MathVectorBinaryAggregateOp`
- desc: Returns the larger of the two values each component
- L300 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorNegate`  
`struct FRigVMFunction_MathVectorNegate : public FRigVMFunction_MathVectorUnaryOp`  
_L308-314_
- reflection: `USTRUCT(meta=(DisplayName="Negate", TemplateName="Negate", Keywords="-,Abs"))`
- inherits: `FRigVMFunction_MathVectorUnaryOp`
- desc: Returns the negative value
- L312 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorAbs`  
`struct FRigVMFunction_MathVectorAbs : public FRigVMFunction_MathVectorUnaryOp`  
_L320-326_
- reflection: `USTRUCT(meta=(DisplayName="Absolute", TemplateName="Absolute", Keywords="Abs,Neg"))`
- inherits: `FRigVMFunction_MathVectorUnaryOp`
- desc: Returns the absolute (positive) value
- L324 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorFloor`  
`struct FRigVMFunction_MathVectorFloor : public FRigVMFunction_MathVectorUnaryOp`  
_L332-338_
- reflection: `USTRUCT(meta=(DisplayName="Floor", Keywords="Round"))`
- inherits: `FRigVMFunction_MathVectorUnaryOp`
- desc: Returns the closest lower full number (integer) of the value for each component
- L336 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorCeil`  
`struct FRigVMFunction_MathVectorCeil : public FRigVMFunction_MathVectorUnaryOp`  
_L344-350_
- reflection: `USTRUCT(meta=(DisplayName="Ceiling", Keywords="Round"))`
- inherits: `FRigVMFunction_MathVectorUnaryOp`
- desc: Returns the closest higher full number (integer) of the value for each component
- L348 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorRound`  
`struct FRigVMFunction_MathVectorRound : public FRigVMFunction_MathVectorUnaryOp`  
_L356-362_
- reflection: `USTRUCT(meta=(DisplayName="Round"))`
- inherits: `FRigVMFunction_MathVectorUnaryOp`
- desc: Returns the closest full number (integer) of the value for each component
- L360 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorSign`  
`struct FRigVMFunction_MathVectorSign : public FRigVMFunction_MathVectorUnaryOp`  
_L368-374_
- reflection: `USTRUCT(meta=(DisplayName="Sign", TemplateName="Sign"))`
- inherits: `FRigVMFunction_MathVectorUnaryOp`
- desc: Returns the sign of the value (+1 for >= FVector(0.f, 0.f, 0.f), -1 for < 0.f) for each component
- L372 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorClamp`  
`struct FRigVMFunction_MathVectorClamp : public FRigVMFunction_MathVectorBase`  
_L380-408_
- reflection: `USTRUCT(meta=(DisplayName="Clamp", TemplateName="Clamp", Keywords="Range,Remap"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Clamps the given value within the range provided by minimum and maximum for each component
- L384 _public function_ `FRigVMFunction_MathVectorClamp()`
- L390 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L395 _public member_ `FVector Value;` — `UPROPERTY(meta=(Input))` — The input vector to clamp
- L399 _public member_ `FVector Minimum;` — `UPROPERTY(meta=(Input))` — The Minimum vector to clamp the input by
- L403 _public member_ `FVector Maximum;` — `UPROPERTY(meta=(Input))` — The Maximum vector to clamp the input by
- L407 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting clamped vector

#### struct `FRigVMFunction_MathVectorLerp`  
`struct FRigVMFunction_MathVectorLerp : public FRigVMFunction_MathVectorBase`  
_L414-443_
- reflection: `USTRUCT(meta=(DisplayName="Interpolate", TemplateName="Interpolate", Keywords="Lerp,Mix,Blend"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Linearly interpolates between A and B using the ratio T
- L418 _public function_ `FRigVMFunction_MathVectorLerp()`
- L425 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L430 _public member_ `FVector A;` — `UPROPERTY(meta=(Input))` — The first vector to interpolate from
- L434 _public member_ `FVector B;` — `UPROPERTY(meta=(Input))` — The second vector to interpolate to
- L438 _public member_ `float T;` — `UPROPERTY(meta=(Input, UIMin = "0", UIMax = "1"))` — The blend value for the interpolation
- L442 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting interpolated vector

#### struct `FRigVMFunction_MathVectorRemap`  
`struct FRigVMFunction_MathVectorRemap : public FRigVMFunction_MathVectorBase`  
_L449-490_
- reflection: `USTRUCT(meta=(DisplayName="Remap", TemplateName="Remap", Keywords="Rescale,Scale"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Remaps the given value from a source range to a target range for each component
- L453 _public function_ `FRigVMFunction_MathVectorRemap()`
- L460 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L465 _public member_ `FVector Value;` — `UPROPERTY(meta=(Input))` — The input vector to remap
- L469 _public member_ `FVector SourceMinimum;` — `UPROPERTY(meta=(Input))` — The minimum of the input vector for each component
- L473 _public member_ `FVector SourceMaximum;` — `UPROPERTY(meta=(Input))` — The maximum of the input vector for each component
- L477 _public member_ `FVector TargetMinimum;` — `UPROPERTY(meta=(Input))` — The minimum for the output vector for each component
- L481 _public member_ `FVector TargetMaximum;` — `UPROPERTY(meta=(Input))` — The maximum for the output vector for each component
- L485 _public member_ `bool bClamp;` — `UPROPERTY(meta=(Input))` — If set to true the result is clamped to the target range
- L489 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting remapped vector

#### struct `FRigVMFunction_MathVectorEquals`  
`struct FRigVMFunction_MathVectorEquals : public FRigVMFunction_MathVectorBase`  
_L496-520_
- reflection: `USTRUCT(meta=(DisplayName="Equals", TemplateName="Equals", Keywords="Same,==", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns true if the value A equals B
- L500 _public function_ `FRigVMFunction_MathVectorEquals()`
- L506 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L510 _public member_ `FVector A;` — `UPROPERTY(meta=(Input))`
- L513 _public member_ `FVector B;` — `UPROPERTY(meta=(Input))`
- L516 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))`
- L518 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathVectorNotEquals`  
`struct FRigVMFunction_MathVectorNotEquals : public FRigVMFunction_MathVectorBase`  
_L526-550_
- reflection: `USTRUCT(meta=(DisplayName="Not Equals", TemplateName="NotEquals", Keywords="Different,!=", Deprecated="5.1"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns true if the value A does not equal B
- L530 _public function_ `FRigVMFunction_MathVectorNotEquals()`
- L536 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L540 _public member_ `FVector A;` — `UPROPERTY(meta=(Input))`
- L543 _public member_ `FVector B;` — `UPROPERTY(meta=(Input))`
- L546 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))`
- L548 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathVectorIsNearlyZero`  
`struct FRigVMFunction_MathVectorIsNearlyZero : public FRigVMFunction_MathVectorBase`  
_L556-581_
- reflection: `USTRUCT(meta=(DisplayName="Is Nearly Zero", TemplateName="IsNearlyZero", Keywords="AlmostZero,0"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns true if each component of the value is within a tolerance of zero
- L560 _public function_ `FRigVMFunction_MathVectorIsNearlyZero()`
- L567 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L572 _public member_ `FVector Value;` — `UPROPERTY(meta=(Input))` — The input vector to check
- L576 _public member_ `float Tolerance;` — `UPROPERTY(meta=(Input))` — The tolerance to use when comparing each component with zero
- L580 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the input vector is within Tolerance of zero in each component

#### struct `FRigVMFunction_MathVectorIsNearlyEqual`  
`struct FRigVMFunction_MathVectorIsNearlyEqual : public FRigVMFunction_MathVectorBase`  
_L587-616_
- reflection: `USTRUCT(meta=(DisplayName="Is Nearly Equal", TemplateName="IsNearlyEqual", Keywords="AlmostEqual,=="))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns true if value A is within a tolerance (in each component) of B
- L591 _public function_ `FRigVMFunction_MathVectorIsNearlyEqual()`
- L598 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L603 _public member_ `FVector A;` — `UPROPERTY(meta=(Input))` — The first vector to compare
- L607 _public member_ `FVector B;` — `UPROPERTY(meta=(Input))` — The second vector to compare
- L611 _public member_ `float Tolerance;` — `UPROPERTY(meta=(Input))` — The tolerance to use for the comparison
- L615 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if every component of A is within Tolerance of the corresponding component of B

#### struct `FRigVMFunction_MathVectorSelectBool`  
`struct FRigVMFunction_MathVectorSelectBool : public FRigVMFunction_MathVectorBase`  
_L622-649_
- reflection: `USTRUCT(meta=(DisplayName="Select", Keywords="Pick,If", Deprecated = "4.26.0"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Return one of the two values based on the condition
- L626 _public function_ `FRigVMFunction_MathVectorSelectBool()`
- L632 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L636 _public member_ `bool Condition;` — `UPROPERTY(meta=(Input))`
- L639 _public member_ `FVector IfTrue;` — `UPROPERTY(meta=(Input))`
- L642 _public member_ `FVector IfFalse;` — `UPROPERTY(meta=(Input))`
- L645 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))`
- L647 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathVectorDeg`  
`struct FRigVMFunction_MathVectorDeg : public FRigVMFunction_MathVectorUnaryOp`  
_L655-661_
- reflection: `USTRUCT(meta=(DisplayName="Degrees", TemplateName="Degrees"))`
- inherits: `FRigVMFunction_MathVectorUnaryOp`
- desc: Returns the degrees of a given value in radians
- L659 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorRad`  
`struct FRigVMFunction_MathVectorRad : public FRigVMFunction_MathVectorUnaryOp`  
_L667-673_
- reflection: `USTRUCT(meta=(DisplayName="Radians", TemplateName="Radians"))`
- inherits: `FRigVMFunction_MathVectorUnaryOp`
- desc: Returns the radians of a given value in degrees
- L671 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorLengthSquared`  
`struct FRigVMFunction_MathVectorLengthSquared : public FRigVMFunction_MathVectorBase`  
_L679-699_
- reflection: `USTRUCT(meta=(DisplayName="Length Squared", TemplateName="LengthSquared", Keywords="Length,Size,Magnitude"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns the squared length of the vector
- L683 _public function_ `FRigVMFunction_MathVectorLengthSquared()`
- L689 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L694 _public member_ `FVector Value;` — `UPROPERTY(meta=(Input))` — The input vector to compute the squared length of
- L698 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting squared length of the vector

#### struct `FRigVMFunction_MathVectorLength`  
`struct FRigVMFunction_MathVectorLength : public FRigVMFunction_MathVectorBase`  
_L705-725_
- reflection: `USTRUCT(meta=(DisplayName="Length", TemplateName="Length", Keywords="Size,Magnitude"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns the length of the vector
- L709 _public function_ `FRigVMFunction_MathVectorLength()`
- L715 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L720 _public member_ `FVector Value;` — `UPROPERTY(meta=(Input))` — The input vector to compute the length for
- L724 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting length of the vector

#### struct `FRigVMFunction_MathVectorDistance`  
`struct FRigVMFunction_MathVectorDistance : public FRigVMFunction_MathVectorBase`  
_L731-755_
- reflection: `USTRUCT(meta=(DisplayName="Distance Between", TemplateName="Distance"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns the distance from A to B
- L735 _public function_ `FRigVMFunction_MathVectorDistance()`
- L741 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L746 _public member_ `FVector A;` — `UPROPERTY(meta=(Input))` — The first vector to measure the distance between
- L750 _public member_ `FVector B;` — `UPROPERTY(meta=(Input))` — The second vector to measure the distance between
- L754 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The distance between the two vectors A and B

#### struct `FRigVMFunction_MathVectorCross`  
`struct FRigVMFunction_MathVectorCross : public FRigVMFunction_MathVectorBinaryOp`  
_L761-766_
- reflection: `USTRUCT(meta=(DisplayName="Cross", TemplateName="Cross", Keywords="^"))`
- inherits: `FRigVMFunction_MathVectorBinaryOp`
- desc: Returns the cross product between two vectors
- L764 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorDot`  
`struct FRigVMFunction_MathVectorDot : public FRigVMFunction_MathVectorBase`  
_L772-796_
- reflection: `USTRUCT(meta=(DisplayName="Dot", Keywords="Dot,|"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns the dot product between two vectors
- L776 _public function_ `FRigVMFunction_MathVectorDot()`
- L782 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L787 _public member_ `FVector A;` — `UPROPERTY(meta=(Input))` — The first vector to compute the dot product for
- L791 _public member_ `FVector B;` — `UPROPERTY(meta=(Input))` — The second vector to compute the dot product for
- L795 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting dot product between A and B

#### struct `FRigVMFunction_MathVectorUnit`  
`struct FRigVMFunction_MathVectorUnit : public FRigVMFunction_MathVectorUnaryOp`  
_L802-808_
- reflection: `USTRUCT(meta=(DisplayName="Unit", TemplateName="Unit", Keywords="Normalize"))`
- inherits: `FRigVMFunction_MathVectorUnaryOp`
- desc: Returns the normalized value
- L806 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigVMFunction_MathVectorSetLength`  
`struct FRigVMFunction_MathVectorSetLength: public FRigVMFunction_MathVectorBase`  
_L814-841_
- reflection: `USTRUCT(meta = (DisplayName = "SetLength", TemplateName="SetLength", Keywords = "Unit,Normalize,Scale"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Sets the length of a given vector
- L818 _public function_ `FRigVMFunction_MathVectorSetLength()`
- L824 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L829 _public member_ `FVector Value;` — `UPROPERTY(meta = (Input))` — The input vector to set the length of
- L833 _public member_ `float Length;` — `UPROPERTY(meta = (Input))` — The desired length of the vector
- L840 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting scaled input vector (or 0,0,0 in case the input was also 0,0,0)

#### struct `FRigVMFunction_MathVectorClampLength`  
`struct FRigVMFunction_MathVectorClampLength: public FRigVMFunction_MathVectorBase`  
_L847-880_
- reflection: `USTRUCT(meta = (DisplayName = "ClampLength", TemplateName="ClampLength", Keywords = "Unit,Normalize,Scale"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Clamps the length of a given vector between a minimum and maximum
- L851 _public function_ `FRigVMFunction_MathVectorClampLength()`
- L859 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L864 _public member_ `FVector Value;` — `UPROPERTY(meta = (Input))` — The input vector to clamp the length of
- L868 _public member_ `float MinimumLength;` — `UPROPERTY(meta = (Input))` — The minimum length to clamp by
- L872 _public member_ `float MaximumLength;` — `UPROPERTY(meta = (Input))` — The maximum length to clamp by
- L879 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting clamped input vector (or 0,0,0 in case the input was also 0,0,0)

#### struct `FRigVMFunction_MathVectorMirror`  
`struct FRigVMFunction_MathVectorMirror : public FRigVMFunction_MathVectorBase`  
_L886-910_
- reflection: `USTRUCT(meta=(DisplayName="Mirror on Normal"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Mirror a vector about a normal vector.
- L890 _public function_ `FRigVMFunction_MathVectorMirror()`
- L896 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L901 _public member_ `FVector Value;` — `UPROPERTY(meta=(Input))` — The input vector to mirror
- L905 _public member_ `FVector Normal;` — `UPROPERTY(meta=(Input))` — The normal to mirror the vector by
- L909 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting mirrored vector

#### struct `FRigVMFunction_MathVectorAngle`  
`struct FRigVMFunction_MathVectorAngle : public FRigVMFunction_MathVectorBase`  
_L916-940_
- reflection: `USTRUCT(meta=(DisplayName="Angle Between", TemplateName="AngleBetween"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns the angle between two vectors in radians
- L920 _public function_ `FRigVMFunction_MathVectorAngle()`
- L926 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L931 _public member_ `FVector A;` — `UPROPERTY(meta=(Input))` — The first vector to measure the angle between
- L935 _public member_ `FVector B;` — `UPROPERTY(meta=(Input))` — The second vector to measure the angle between
- L939 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The angle between A and B in radians

#### struct `FRigVMFunction_MathVectorParallel`  
`struct FRigVMFunction_MathVectorParallel : public FRigVMFunction_MathVectorBase`  
_L946-970_
- reflection: `USTRUCT(meta=(DisplayName="Parallel", TemplateName="Parallel"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns true if the two vectors are parallel
- L950 _public function_ `FRigVMFunction_MathVectorParallel()`
- L956 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L961 _public member_ `FVector A;` — `UPROPERTY(meta=(Input))` — The first vector to compare
- L965 _public member_ `FVector B;` — `UPROPERTY(meta=(Input))` — The second vector to compare
- L969 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the two vectors A and B are parallel

#### struct `FRigVMFunction_MathVectorOrthogonal`  
`struct FRigVMFunction_MathVectorOrthogonal : public FRigVMFunction_MathVectorBase`  
_L976-1001_
- reflection: `USTRUCT(meta=(DisplayName="Orthogonal", TemplateName="Orthogonal"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns true if the two vectors are orthogonal
- L980 _public function_ `FRigVMFunction_MathVectorOrthogonal()`
- L987 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L992 _public member_ `FVector A;` — `UPROPERTY(meta=(Input))` — The first vector to compare
- L996 _public member_ `FVector B;` — `UPROPERTY(meta=(Input))` — The second vector to compare
- L1000 _public member_ `bool Result;` — `UPROPERTY(meta=(Output))` — True if the two vectors A and B are orthogonal

#### struct `FRigVMFunction_MathVectorBezierFourPoint`  
`struct FRigVMFunction_MathVectorBezierFourPoint : public FRigVMFunction_MathVectorBase`  
_L1007-1039_
- reflection: `USTRUCT(meta=(DisplayName="Bezier Four Point", Deprecated = "5.0"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns the 4 point bezier interpolation
- L1011 _public function_ `FRigVMFunction_MathVectorBezierFourPoint()`
- L1018 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1023 _public member_ `FRigVMFourPointBezier Bezier;` — `UPROPERTY(meta=(Input))` — The input four point structure
- L1027 _public member_ `float T;` — `UPROPERTY(meta=(Input))` — The interpolation T value along the bezier to compute
- L1031 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting position at value T on the bezier
- L1035 _public member_ `FVector Tangent;` — `UPROPERTY(meta=(Output))` — The resulting tangent at value T on the bezier
- L1037 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathVectorMakeBezierFourPoint`  
`struct FRigVMFunction_MathVectorMakeBezierFourPoint : public FRigVMFunction_MathVectorBase`  
_L1045-1062_
- reflection: `USTRUCT(meta = (DisplayName = "Make Bezier Four Point", Constant, Deprecated = "5.0"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Creates a bezier four point
- L1049 _public function_ `FRigVMFunction_MathVectorMakeBezierFourPoint()`
- L1054 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1058 _public member_ `FRigVMFourPointBezier Bezier;` — `UPROPERTY(meta = (Input, Output))`
- L1060 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_MathVectorClampSpatially`  
`struct FRigVMFunction_MathVectorClampSpatially: public FRigVMFunction_MathVectorBase`  
_L1070-1135_
- reflection: `USTRUCT(meta = (DisplayName = "Clamp Spatially", TemplateName="ClampSpatially", Keywords="Collide,Collision"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Clamps a position using a plane collision, cylindric collision or spherical collision. The collision happens both towards an inner envelope (minimum) and towards an outer envelope (maximum). You can disable the inner / outer envelope / collision by setting the minimum / maximum to 0.0.
- L1074 _public function_ `FRigVMFunction_MathVectorClampSpatially()`
- L1087 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1092 _public member_ `FVector Value;` — `UPROPERTY(meta = (Input))` — The input position to clamp
- L1096 _public member_ `TEnumAsByte<EAxis::Type> Axis;` — `UPROPERTY(meta = (Input))` — The axis to use for the filter
- L1100 _public member_ `TEnumAsByte<ERigVMClampSpatialMode::Type> Type;` — `UPROPERTY(meta = (Input))` — The type of filter / mode to apply
- L1106 _public member_ `float Minimum;` — `UPROPERTY(meta = (Input))` — The minimum allowed distance at which a collision occurs. Note: For capsule this represents the radius. Disable by setting to 0.0.
- L1113 _public member_ `float Maximum;` — `UPROPERTY(meta = (Input))` — This maximum allowed distance. A collision will occur towards the center at this wall. Note: For capsule this represents the length. Disable by setting to 0.0.
- L1118 _public member_ `FTransform Space;` — `UPROPERTY(meta = (Input))` — The space this spatial clamp happens within. The input position will be projected into this space.
- L1122 _public member_ `bool bDrawDebug;` — `UPROPERTY(meta = (Input))` — Draws debug information if True
- L1126 _public member_ `FLinearColor DebugColor;` — `UPROPERTY(meta = (Input))` — The color to use for the debug draw
- L1130 _public member_ `float DebugThickness;` — `UPROPERTY(meta = (Input))` — The thickness to use for the debug draw
- L1134 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting clamped position

#### struct `FRigVMFunction_MathIntersectPlane`  
`struct FRigVMFunction_MathIntersectPlane : public FRigVMFunction_MathVectorBase`  
_L1141-1178_
- reflection: `USTRUCT(meta = (DisplayName = "Intersect Plane", Keywords = "Collide,Intersect,Raycast"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Intersects a plane with a vector given a start and direction
- L1145 _public function_ `FRigVMFunction_MathIntersectPlane()`
- L1152 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1157 _public member_ `FVector Start;` — `UPROPERTY(meta = (Input))` — The start of the ray to intersect with the plane
- L1161 _public member_ `FVector Direction;` — `UPROPERTY(meta = (Input))` — The direction of the ray to intersect with the plane
- L1165 _public member_ `FVector PlanePoint;` — `UPROPERTY(meta = (Input))` — The point on the plane to intersect with
- L1169 _public member_ `FVector PlaneNormal;` — `UPROPERTY(meta = (Input))` — The normal of the plane to intersect with
- L1173 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting position on the plane
- L1177 _public member_ `float Distance;` — `UPROPERTY(meta = (Output))` — The distance along the ray to the intersection

#### struct `FRigVMFunction_MathDistanceToPlane`  
`struct FRigVMFunction_MathDistanceToPlane : public FRigVMFunction_MathVectorBase`  
_L1184-1217_
- reflection: `USTRUCT(meta = (DisplayName = "Distance To Plane", Keywords = "Distance,Plane,Closest,Project"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Find the point on the plane that is closest to the given point and the distance between them.
- L1188 _public function_ `FRigVMFunction_MathDistanceToPlane()`
- L1195 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1200 _public member_ `FVector Point;` — `UPROPERTY(meta = (Input))` — The point to measure against the plane
- L1204 _public member_ `FVector PlanePoint;` — `UPROPERTY(meta = (Input))` — A point on the plane to measure against
- L1208 _public member_ `FVector PlaneNormal;` — `UPROPERTY(meta = (Input))` — The normal of the plane to measure against
- L1212 _public member_ `FVector ClosestPointOnPlane;` — `UPROPERTY(meta = (Output))` — The resulting closest point on the plane
- L1216 _public member_ `float SignedDistance;` — `UPROPERTY(meta = (Output))` — The distance to the plane as a signed (positive or negative) value

#### struct `FRigVMFunction_MathVectorMakeRelative`  
`struct FRigVMFunction_MathVectorMakeRelative : public FRigVMFunction_MathVectorBase`  
_L1223-1246_
- reflection: `USTRUCT(meta=(DisplayName="Make Relative", TemplateName="Make Relative", Keywords="Local,Global,Absolute"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns the relative local vector within a parent's vector
- L1227 _public function_ `FRigVMFunction_MathVectorMakeRelative()`
- L1232 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1237 _public member_ `FVector Global;` — `UPROPERTY(meta=(Input))` — The global position to make relative
- L1241 _public member_ `FVector Parent;` — `UPROPERTY(meta=(Input))` — The parent global position to make the input relative to
- L1245 _public member_ `FVector Local;` — `UPROPERTY(meta=(Output))` — The resulting relative position

#### struct `FRigVMFunction_MathVectorMakeAbsolute`  
`struct FRigVMFunction_MathVectorMakeAbsolute : public FRigVMFunction_MathVectorBase`  
_L1252-1275_
- reflection: `USTRUCT(meta = (DisplayName = "Make Absolute", TemplateName="Make Absolute", Keywords = "Local,Global,Relative"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns the absolute global vector within a parent's vector
- L1256 _public function_ `FRigVMFunction_MathVectorMakeAbsolute()`
- L1261 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1266 _public member_ `FVector Local;` — `UPROPERTY(meta = (Input))` — The input local position to make absolute
- L1270 _public member_ `FVector Parent;` — `UPROPERTY(meta = (Input))` — The parent global position to make the local absolute to
- L1274 _public member_ `FVector Global;` — `UPROPERTY(meta = (Output))` — The resulting global position

#### struct `FRigVMFunction_MathVectorMirrorTransform`  
`struct FRigVMFunction_MathVectorMirrorTransform : public FRigVMFunction_MathVectorBase`  
_L1281-1315_
- reflection: `USTRUCT(meta=(DisplayName="Mirror", TemplateName="Mirror"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Mirror a vector about a central transform.
- L1285 _public function_ `FRigVMFunction_MathVectorMirrorTransform()`
- L1293 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1298 _public member_ `FVector Value;` — `UPROPERTY(meta=(Input))` — The input vector to mirror
- L1302 _public member_ `TEnumAsByte<EAxis::Type> MirrorAxis;` — `UPROPERTY(meta=(Input))` — the axis to mirror against
- L1306 _public member_ `TEnumAsByte<EAxis::Type> AxisToFlip;` — `UPROPERTY(meta=(Input))` — the axis to flip for rotations
- L1310 _public member_ `FTransform CentralTransform;` — `UPROPERTY(meta=(Input))` — The transform about which to mirror
- L1314 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting mirrored vector

#### struct `FRigVMFunction_MathVectorArraySum`  
`struct FRigVMFunction_MathVectorArraySum : public FRigVMFunction_MathVectorBase`  
_L1321-1341_
- reflection: `USTRUCT(meta = (DisplayName = "Array Sum", TemplateName = "ArraySum"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns the sum of the given array
- L1325 _public function_ `FRigVMFunction_MathVectorArraySum()`
- L1331 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L1336 _public member_ `TArray<FVector> Array;` — `UPROPERTY(meta = (Input))` — The array of vector to add up
- L1340 _public member_ `FVector Sum;` — `UPROPERTY(meta = (Output))` — The sum of all vectors in the input array

#### struct `FRigVMFunction_MathVectorArrayAverage`  
`struct FRigVMFunction_MathVectorArrayAverage : public FRigVMFunction_MathVectorBase`  
_L1348-1368_
- reflection: `USTRUCT(meta = (DisplayName = "Array Average", TemplateName = "ArrayAverage"))`
- inherits: `FRigVMFunction_MathVectorBase`
- desc: Returns the average of the given array
- L1352 _public function_ `FRigVMFunction_MathVectorArrayAverage()`
- L1358 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L1363 _public member_ `TArray<FVector> Array;` — `UPROPERTY(meta = (Input))` — The array of vectors to average
- L1367 _public member_ `FVector Average;` — `UPROPERTY(meta = (Output))` — The resulting average vector of the input array

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_Noise.h` (Public)


#### struct `FRigVMFunction_NoiseFloat`  
`struct FRigVMFunction_NoiseFloat : public FRigVMFunction_MathBase`  
_L12-52_
- reflection: `USTRUCT(meta=(DisplayName="Noise (Float)", Category="Math|Noise", TemplateName="Noise"))`
- inherits: `FRigVMFunction_MathBase`
- desc: Generates a float through a noise fluctuation process between a min and a max through speed
- L16 _public function_ `FRigVMFunction_NoiseFloat()`
- L23 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L28 _public member_ `float Value;` — `UPROPERTY(meta = (Input))` — The input value to retrieve the noise for
- L32 _public member_ `float Speed;` — `UPROPERTY(meta = (Input))` — The speed of the noise field
- L36 _public member_ `float Frequency;` — `UPROPERTY(meta = (Input))` — The frequency of the noise field
- L40 _public member_ `float Minimum;` — `UPROPERTY(meta = (Input))` — The minimum range of the noise
- L44 _public member_ `float Maximum;` — `UPROPERTY(meta = (Input))` — The maximum range of the noise
- L48 _public member_ `float Result;` — `UPROPERTY(meta = (Output))` — The resulting value in the noise field
- L51 _public member_ `float Time;` — `UPROPERTY()`

#### struct `FRigVMFunction_NoiseDouble`  
`struct FRigVMFunction_NoiseDouble : public FRigVMFunction_MathBase`  
_L58-98_
- reflection: `USTRUCT(meta=(DisplayName="Noise (Double)", Category="Math|Noise", TemplateName="Noise"))`
- inherits: `FRigVMFunction_MathBase`
- desc: Generates a double through a noise fluctuation process between a min and a max through speed
- L62 _public function_ `FRigVMFunction_NoiseDouble()`
- L69 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L74 _public member_ `double Value;` — `UPROPERTY(meta = (Input))` — The input value to retrieve the noise for
- L78 _public member_ `double Speed;` — `UPROPERTY(meta = (Input))` — The speed of the noise field
- L82 _public member_ `double Frequency;` — `UPROPERTY(meta = (Input))` — The frequency of the noise field
- L86 _public member_ `double Minimum;` — `UPROPERTY(meta = (Input))` — The minimum range of the noise
- L90 _public member_ `double Maximum;` — `UPROPERTY(meta = (Input))` — The maximum range of the noise
- L94 _public member_ `double Result;` — `UPROPERTY(meta = (Output))` — The resulting value in the noise field
- L97 _public member_ `double Time;` — `UPROPERTY()`

#### struct `FRigVMFunction_NoiseVector`  
`struct FRigVMFunction_NoiseVector : public FRigVMFunction_MathBase`  
_L104-143_
- reflection: `USTRUCT(meta = (DisplayName = "Noise (Vector)", Category = "Math|Noise", Deprecated = "5.0.0"))`
- inherits: `FRigVMFunction_MathBase`
- desc: Generates a vector through a noise fluctuation process between a min and a max through speed
- L108 _public function_ `FRigVMFunction_NoiseVector()`
- L117 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L121 _public member_ `FVector Position;` — `UPROPERTY(meta = (Input))`
- L124 _public member_ `FVector Speed;` — `UPROPERTY(meta = (Input))`
- L127 _public member_ `FVector Frequency;` — `UPROPERTY(meta = (Input))`
- L130 _public member_ `float Minimum;` — `UPROPERTY(meta = (Input))`
- L133 _public member_ `float Maximum;` — `UPROPERTY(meta = (Input))`
- L136 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))`
- L139 _public member_ `FVector Time;` — `UPROPERTY()`
- L141 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigVMFunction_NoiseVector2`  
`struct FRigVMFunction_NoiseVector2 : public FRigVMFunction_MathBase`  
_L149-191_
- reflection: `USTRUCT(meta = (DisplayName = "Noise (Vector)", Category = "Math|Noise", TemplateName="Noise"))`
- inherits: `FRigVMFunction_MathBase`
- desc: Generates a vector through a noise fluctuation process between a min and a max through speed
- L153 _public function_ `FRigVMFunction_NoiseVector2()`
- L162 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L167 _public member_ `FVector Value;` — `UPROPERTY(meta = (Input))` — The input position to retrieve the noise for
- L171 _public member_ `FVector Speed;` — `UPROPERTY(meta = (Input))` — The speed of the noise field
- L175 _public member_ `FVector Frequency;` — `UPROPERTY(meta = (Input))` — The frequency of the noise field
- L179 _public member_ `double Minimum;` — `UPROPERTY(meta = (Input))` — The minimum range of the noise
- L183 _public member_ `double Maximum;` — `UPROPERTY(meta = (Input))` — The maximum range of the noise
- L187 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting vector in the noise field
- L190 _public member_ `FVector Time;` — `UPROPERTY()`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_Random.h` (Public)


#### struct `FRigVMFunction_RandomInt`  
`struct FRigVMFunction_RandomInt : public FRigVMFunction_MathBase`  
_L12-63_
- reflection: `USTRUCT(meta = (DisplayName = "Random (Int)", Category = "Math|Random", TemplateName = "Random"))`
- inherits: `FRigVMFunction_MathBase`
- desc: Generates a random integer between a min and a max (inclusive)
- L16 _public function_ `FRigVMFunction_RandomInt()`
- L25 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L30 _public member_ `int32 Seed;` — `UPROPERTY(meta = (Input))` — The seed for the random number generator
- L34 _public member_ `int32 Minimum = 0;` — `UPROPERTY(meta = (Input))` — The minimum value for the random number range
- L38 _public member_ `int32 Maximum = 1;` — `UPROPERTY(meta = (Input))` — The maximum value for the random number range (inclusive)
- L46 _public member_ `float Duration;` — `UPROPERTY(meta = (Input))` — The duration at which the number won't change. Use 0 for a different number every time. A negative number (for ex: -1) results in an infinite duration.
- L50 _public member_ `int32 Result;` — `UPROPERTY(meta = (Output))` — The resulting random number
- L53 _public member_ `int32 LastResult;` — `UPROPERTY()`
- L56 _public member_ `int32 LastSeed;` — `UPROPERTY()`
- L59 _public member_ `int32 BaseSeed;` — `UPROPERTY()`
- L62 _public member_ `float TimeLeft;` — `UPROPERTY()`

#### struct `FRigVMFunction_RandomFloat`  
`struct FRigVMFunction_RandomFloat : public FRigVMFunction_MathBase`  
_L69-120_
- reflection: `USTRUCT(meta=(DisplayName="Random (Float)", Category="Math|Random", TemplateName="Random"))`
- inherits: `FRigVMFunction_MathBase`
- desc: Generates a random float between a min and a max
- L73 _public function_ `FRigVMFunction_RandomFloat()`
- L82 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L87 _public member_ `int32 Seed;` — `UPROPERTY(meta = (Input))` — The seed for the random number generator
- L91 _public member_ `float Minimum;` — `UPROPERTY(meta = (Input))` — The minimum value for the random number range
- L95 _public member_ `float Maximum;` — `UPROPERTY(meta = (Input))` — The maximum value for the random number range
- L103 _public member_ `float Duration;` — `UPROPERTY(meta = (Input))` — The duration at which the number won't change. Use 0 for a different number every time. A negative number (for ex: -1) results in an infinite duration.
- L107 _public member_ `float Result;` — `UPROPERTY(meta = (Output))` — The resulting random number
- L110 _public member_ `float LastResult;` — `UPROPERTY()`
- L113 _public member_ `int32 LastSeed;` — `UPROPERTY()`
- L116 _public member_ `int32 BaseSeed;` — `UPROPERTY()`
- L119 _public member_ `float TimeLeft;` — `UPROPERTY()`

#### struct `FRigVMFunction_RandomVector`  
`struct FRigVMFunction_RandomVector: public FRigVMFunction_MathBase`  
_L126-178_
- reflection: `USTRUCT(meta = (DisplayName = "Random (Vector)", Category = "Math|Random", TemplateName="Random"))`
- inherits: `FRigVMFunction_MathBase`
- desc: Generates a random vector between a min and a max
- L130 _public function_ `FRigVMFunction_RandomVector()`
- L140 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L145 _public member_ `int32 Seed;` — `UPROPERTY(meta = (Input))` — The seed for the random number generator
- L149 _public member_ `float Minimum;` — `UPROPERTY(meta = (Input))` — The minimum value for the random number range for all components of the vector
- L153 _public member_ `float Maximum;` — `UPROPERTY(meta = (Input))` — The maximum value for the random number range for all components of the vector
- L161 _public member_ `float Duration;` — `UPROPERTY(meta = (Input))` — The duration at which the number won't change. Use 0 for a different number every time. A negative number (for ex: -1) results in an infinite duration.
- L165 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting random vector
- L168 _public member_ `FVector LastResult;` — `UPROPERTY()`
- L171 _public member_ `int32 LastSeed;` — `UPROPERTY()`
- L174 _public member_ `int32 BaseSeed;` — `UPROPERTY()`
- L177 _public member_ `float TimeLeft;` — `UPROPERTY()`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMFunction_SpringMath.h` (Public)


#### struct `FRigVMFunction_DampFloat`  
`struct FRigVMFunction_DampFloat : public FRigVMFunction_MathBase`  
_L12-34_
- reflection: `USTRUCT(meta=(DisplayName="Damp (Float)", Category="Math|Damp", TemplateName="Damp"))`
- inherits: `FRigVMFunction_MathBase`
- desc: Damps a float value using exponential decay damping
- L16 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L21 _public member_ `float Value = 0.0f;` — `UPROPERTY(meta = (Input))` — The value to damp
- L25 _public member_ `float Target = 0.0f;` — `UPROPERTY(meta = (Input))` — The target value to damp towards
- L29 _public member_ `float SmoothingTime = 0.2f;` — `UPROPERTY(meta = (Input, ClampMin = "0", UIMin = "0", ForceUnits = "s"))` — The time to apply smoothing for
- L33 _public member_ `float Result = 0.0f;` — `UPROPERTY(meta = (Output))` — Resulting damped value

#### struct `FRigVMFunction_DampVector`  
`struct FRigVMFunction_DampVector : public FRigVMFunction_MathBase`  
_L40-62_
- reflection: `USTRUCT(meta=(DisplayName="Damp (Vector)", Category="Math|Damp", TemplateName="Damp"))`
- inherits: `FRigVMFunction_MathBase`
- desc: Damps a vector value using exponential decay damping
- L44 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L49 _public member_ `FVector Value = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — The value to damp
- L53 _public member_ `FVector Target = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — The target value to damp towards
- L57 _public member_ `float SmoothingTime = 0.2f;` — `UPROPERTY(meta = (Input, ClampMin = "0", UIMin = "0", ForceUnits = "s"))` — The time to apply smoothing for
- L61 _public member_ `FVector Result = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — Resulting damped value

#### struct `FRigVMFunction_DampQuaternion`  
`struct FRigVMFunction_DampQuaternion : public FRigVMFunction_MathBase`  
_L68-90_
- reflection: `USTRUCT(meta=(DisplayName="Damp (Quaternion)", Category="Math|Damp", TemplateName="Damp"))`
- inherits: `FRigVMFunction_MathBase`
- desc: Damps a quaternion value using exponential decay damping
- L72 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L77 _public member_ `FQuat Value = FQuat::Identity;` — `UPROPERTY(meta = (Input))` — The value to damp
- L81 _public member_ `FQuat Target = FQuat::Identity;` — `UPROPERTY(meta = (Input))` — The target value to damp towards
- L85 _public member_ `float SmoothingTime = 0.2f;` — `UPROPERTY(meta = (Input, ClampMin = "0", UIMin = "0", ForceUnits = "s"))` — The time to apply smoothing for
- L89 _public member_ `FQuat Result = FQuat::Identity;` — `UPROPERTY(meta = (Output))` — Resulting damped value

#### struct `FRigVMFunction_SpringDampFloat`  
`struct FRigVMFunction_SpringDampFloat : public FRigVMFunction_MathMutableBase`  
_L96-118_
- reflection: `USTRUCT(meta=(DisplayName="Critical Spring Damp (Float)", Category="Math|Damp", TemplateName="Critical Spring Damp"))`
- inherits: `FRigVMFunction_MathMutableBase`
- desc: Damps a float using a spring damper
- L100 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L105 _public member_ `float Value = 0.0f;` — `UPROPERTY(meta = (Input, Output))` — The value to damp
- L109 _public member_ `float ValueVelocity = 0.0f;` — `UPROPERTY(meta = (Input, Output))` — The velocity of the value
- L113 _public member_ `float Target = 0.0f;` — `UPROPERTY(meta = (Input))` — The target to damp towards
- L117 _public member_ `float SmoothingTime = 0.2f;` — `UPROPERTY(meta = (Input, ClampMin = "0", UIMin = "0", ForceUnits = "s"))` — The time to apply smoothing for

#### struct `FRigVMFunction_SpringDampVector`  
`struct FRigVMFunction_SpringDampVector : public FRigVMFunction_MathMutableBase`  
_L124-146_
- reflection: `USTRUCT(meta=(DisplayName="Critical Spring Damp (Vector)", Category="Math|Damp", TemplateName="Critical Spring Damp"))`
- inherits: `FRigVMFunction_MathMutableBase`
- desc: Damps a vector using a spring damper
- L128 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L133 _public member_ `FVector Value = FVector::ZeroVector;` — `UPROPERTY(meta = (Input, Output))` — The value to damp
- L137 _public member_ `FVector ValueVelocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Input, Output))` — The velocity of the value
- L141 _public member_ `FVector Target = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — The target to damp towards
- L145 _public member_ `float SmoothingTime = 0.2f;` — `UPROPERTY(meta = (Input, ClampMin = "0", UIMin = "0", ForceUnits = "s"))` — The time to apply smoothing for

#### struct `FRigVMFunction_SpringDampQuat`  
`struct FRigVMFunction_SpringDampQuat : public FRigVMFunction_MathMutableBase`  
_L152-174_
- reflection: `USTRUCT(meta=(DisplayName="Critical Spring Damp (Quat)", Category="Math|Damp", TemplateName="Critical Spring Damp"))`
- inherits: `FRigVMFunction_MathMutableBase`
- desc: Damps a quaternion using a spring damper
- L156 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L161 _public member_ `FQuat Value = FQuat::Identity;` — `UPROPERTY(meta = (Input, Output))` — The value to damp
- L165 _public member_ `FVector ValueVelocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Input, Output))` — The velocity of the value
- L169 _public member_ `FQuat Target = FQuat::Identity;` — `UPROPERTY(meta = (Input))` — The target to damp towards
- L173 _public member_ `float SmoothingTime = 0.2f;` — `UPROPERTY(meta = (Input, ClampMin = "0", UIMin = "0", ForceUnits = "s"))` — The time to apply smoothing for

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Math/RigVMMathLibrary.h` (Public)


#### enum `ERigVMAnimEasingType`  
`enum class ERigVMAnimEasingType : uint8`  
_L12-45_
- reflection: `UENUM(meta = (RigVMTypeAllowed))`
- L14 _public enumerator_ `Linear`
- L15 _public enumerator_ `QuadraticEaseIn`
- L16 _public enumerator_ `QuadraticEaseOut`
- L17 _public enumerator_ `QuadraticEaseInOut`
- L18 _public enumerator_ `CubicEaseIn`
- L19 _public enumerator_ `CubicEaseOut`
- L20 _public enumerator_ `CubicEaseInOut`
- L21 _public enumerator_ `QuarticEaseIn`
- L22 _public enumerator_ `QuarticEaseOut`
- L23 _public enumerator_ `QuarticEaseInOut`
- L24 _public enumerator_ `QuinticEaseIn`
- L25 _public enumerator_ `QuinticEaseOut`
- L26 _public enumerator_ `QuinticEaseInOut`
- L27 _public enumerator_ `SineEaseIn`
- L28 _public enumerator_ `SineEaseOut`
- L29 _public enumerator_ `SineEaseInOut`
- L30 _public enumerator_ `CircularEaseIn`
- L31 _public enumerator_ `CircularEaseOut`
- L32 _public enumerator_ `CircularEaseInOut`
- L33 _public enumerator_ `ExponentialEaseIn`
- L34 _public enumerator_ `ExponentialEaseOut`
- L35 _public enumerator_ `ExponentialEaseInOut`
- L36 _public enumerator_ `ElasticEaseIn`
- L37 _public enumerator_ `ElasticEaseOut`
- L38 _public enumerator_ `ElasticEaseInOut`
- L39 _public enumerator_ `BackEaseIn`
- L40 _public enumerator_ `BackEaseOut`
- L41 _public enumerator_ `BackEaseInOut`
- L42 _public enumerator_ `BounceEaseIn`
- L43 _public enumerator_ `BounceEaseOut`
- L44 _public enumerator_ `BounceEaseInOut`

#### struct `FRigVMFourPointBezier`  
`struct FRigVMFourPointBezier`  
_L48-68_
- reflection: `USTRUCT(BlueprintType)`
- L52 _public function_ `FRigVMFourPointBezier()`
- L58 _public member_ `FVector A;` — `UPROPERTY(EditAnywhere, Category=Bezier)`
- L61 _public member_ `FVector B;` — `UPROPERTY(EditAnywhere, Category=Bezier)`
- L64 _public member_ `FVector C;` — `UPROPERTY(EditAnywhere, Category=Bezier)`
- L67 _public member_ `FVector D;` — `UPROPERTY(EditAnywhere, Category=Bezier)`

#### struct `FRigVMMirrorSettings`  
`struct FRigVMMirrorSettings`  
_L71-99_
- reflection: `USTRUCT(BlueprintType)`
- L75 _public function_ `FRigVMMirrorSettings() : MirrorAxis(EAxis::X) , AxisToFlip(EAxis::Z)`
- L83 _public member_ `TEnumAsByte<EAxis::Type> MirrorAxis;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings)` — the axis to mirror against
- L87 _public member_ `TEnumAsByte<EAxis::Type> AxisToFlip;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings)` — the axis to flip for rotations
- L91 _public member_ `FString SearchString;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, DisplayName = "Search")` — the string to search for
- L95 _public member_ `FString ReplaceString;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, DisplayName = "Replace")` — the string to replace the search occurrences with
- L97 _public prototype_ `FTransform MirrorTransform(const FTransform& InTransform) const;`
- L98 _public prototype_ `FVector MirrorVector(const FVector& InVector) const;`

#### enum `ERigVMSimPointIntegrateType`  
`enum class ERigVMSimPointIntegrateType : uint8`  
_L102-106_
- reflection: `UENUM(meta = (RigVMTypeAllowed))`
- L104 _public enumerator_ `Verlet`
- L105 _public enumerator_ `SemiExplicitEuler`

#### struct `FRigVMSimPoint`  
`struct FRigVMSimPoint`  
_L109-162_
- reflection: `USTRUCT(BlueprintType)`
- L113 _public function_ `FRigVMSimPoint()`
- L126 _public member_ `float Mass;` — `UPROPERTY(EditAnywhere, Category=Simulation)` — The mass of the point
- L132 _public member_ `float Size;` — `UPROPERTY(EditAnywhere, Category=Simulation)` — Size of the point - only used for collision
- L138 _public member_ `float LinearDamping;` — `UPROPERTY(EditAnywhere, Category=Simulation)` — The linear damping of the point
- L146 _public member_ `float InheritMotion;` — `UPROPERTY(EditAnywhere, Category=Simulation)` — Defines how much the point will inherit motion from its input. This does not have an effect on passive (mass == 0.0) points. Values can be higher than 1 due to timestep - but they are clamped internally.
- L152 _public member_ `FVector Position;` — `UPROPERTY(EditAnywhere, Category=Simulation)` — The position of the point
- L158 _public member_ `FVector LinearVelocity;` — `UPROPERTY(EditAnywhere, Category=Simulation)` — The velocity of the point per second
- L160 _public prototype_ `FRigVMSimPoint IntegrateVerlet(const FVector& InForce, float InBlend, float InDeltaTime) const;`
- L161 _public prototype_ `FRigVMSimPoint IntegrateSemiExplicitEuler(const FVector& InForce, float InDeltaTime) const;`

#### class `FRigVMMathLibrary`  
`class FRigVMMathLibrary`  
_L164-181_
- L167 _public prototype_ `static float AngleBetween(const FVector& A, const FVector& B);`
- L168 _public prototype_ `static void FourPointBezier(const FVector& A, const FVector& B, const FVector& C, const FVector& D, float T, FVector& OutPosition, FVector& OutTangent);`
- L169 _public prototype_ `static void FourPointBezier(const FRigVMFourPointBezier& Bezier, float T, FVector& OutPosition, FVector& OutTangent);`
- L170 _public prototype_ `static float EaseFloat(float Value, ERigVMAnimEasingType Type);`
- L171 _public prototype_ `static FTransform LerpTransform(const FTransform& A, const FTransform& B, float T);`
- L172 _public prototype_ `static FVector ClampSpatially(const FVector& Value, EAxis::Type Axis, ERigVMClampSpatialMode::Type Type, float Minimum, float Maximum, FTransform Space);`
- L173 _public prototype_ `static FQuat FindQuatBetweenVectors(const FVector& A, const FVector& B);`
- L174 _public prototype_ `static FQuat FindQuatBetweenNormals(const FVector& A, const FVector& B);`
- L178 _public prototype_ `static FVector GetEquivalentEulerAngle(const FVector& InEulerAngle, const EEulerRotationOrder& InOrder);` — See - "Computing Euler angles from a rotation matrix" by Gregory G. Slabaugh Each spatial orientation can be mapped to two equivalent euler angles within range (-180, 180)
- L180 _public prototype_ `static FVector& ChooseBetterEulerAngleForAxisFilter(const FVector& Base, FVector& A, FVector& B);`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMDispatch_Array.h` (Public)


#### struct `FRigVMDispatch_ArrayBase`  
`struct FRigVMDispatch_ArrayBase : public FRigVMDispatch_CoreBase`  
_L11-42_
- reflection: `USTRUCT(meta=(Abstract, Category = "Array", Keywords = "List,Collection", NodeColor = "1,1,1,1"))`
- inherits: `FRigVMDispatch_CoreBase`
- L16 _public function_ `virtual ERigVMOpCode GetOpCode() const`
- L17 _public prototype_ `static UScriptStruct* GetFactoryDispatchForOpCode(ERigVMOpCode InOpCode);`
- L18 _public prototype_ `static FName GetFactoryNameForOpCode(ERigVMOpCode InOpCode);`
- L20 _public prototype_ `virtual FString GetArgumentDefaultValue(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L22 _public function_ `virtual bool IsSingleton() const override`
- L25 _protected prototype_ `static FRigVMTemplateArgumentInfo CreateArgumentInfo(const FName& InName, ERigVMPinDirection InDirection);`
- L26 _protected prototype_ `static TMap<uint32, int32> GetArrayHash(FScriptArrayHelper& InArrayHelper, const FArrayProperty* InArrayProperty);`
- L28 _protected member_ `static inline FLazyName ArrayName = FLazyName(TEXT("Arra`
- L29 _protected member_ `static inline FLazyName ValuesName = FLazyName(TEXT("Valu`
- L30 _protected member_ `static inline FLazyName NumName = FLazyName(TEXT("Num"`
- L31 _protected member_ `static inline FLazyName IsEmptyName = FLazyName(TEXT("IsEm`
- L32 _protected member_ `static inline FLazyName IndexName = FLazyName(TEXT("Inde`
- L33 _protected member_ `static inline FLazyName ElementName = FLazyName(TEXT("Elem`
- L34 _protected member_ `static inline FLazyName SuccessName = FLazyName(TEXT("Succ`
- L35 _protected member_ `static inline FLazyName OtherName = FLazyName(TEXT("Othe`
- L36 _protected member_ `static inline FLazyName CloneName = FLazyName(TEXT("Clon`
- L37 _protected member_ `static inline FLazyName CountName = FLazyName(TEXT("Coun`
- L38 _protected member_ `static inline FLazyName RatioName = FLazyName(TEXT("Rati`
- L39 _protected member_ `static inline FLazyName ResultName = FLazyName(TEXT("Resu`

#### struct `FRigVMDispatch_ArrayBaseMutable`  
`struct FRigVMDispatch_ArrayBaseMutable : public FRigVMDispatch_ArrayBase`  
_L45-51_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigVMDispatch_ArrayBase`
- L50 _public prototype_ `virtual const TArray<FRigVMExecuteArgument>& GetExecuteArguments_Impl(const FRigVMDispatchContext& InContext) const override;`

#### struct `FRigVMDispatch_ArrayMake`  
`struct FRigVMDispatch_ArrayMake : public FRigVMDispatch_ArrayBase`  
_L54-77_
- reflection: `USTRUCT(meta=(DisplayName = "Make Array", Keywords = "Make,MakeArray,Constant,Reroute"))`
- inherits: `FRigVMDispatch_ArrayBase`
- L59 _public function_ `FRigVMDispatch_ArrayMake()`
- L64 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L65 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L67 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L68 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L69 _public prototype_ `virtual FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const override;`
- L70 _public prototype_ `virtual FString GetArgumentDefaultValue(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L72 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L75 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L76 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayReset`  
`struct FRigVMDispatch_ArrayReset : public FRigVMDispatch_ArrayBaseMutable`  
_L80-102_
- reflection: `USTRUCT(meta=(DisplayName = "Reset", Pure))`
- inherits: `FRigVMDispatch_ArrayBaseMutable`
- L85 _public function_ `FRigVMDispatch_ArrayReset()`
- L90 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L91 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L92 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L93 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L95 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L96 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L100 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L101 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayGetNum`  
`struct FRigVMDispatch_ArrayGetNum : public FRigVMDispatch_ArrayBase`  
_L105-127_
- reflection: `USTRUCT(meta=(DisplayName = "Num"))`
- inherits: `FRigVMDispatch_ArrayBase`
- L110 _public function_ `FRigVMDispatch_ArrayGetNum()`
- L115 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L116 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L117 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L118 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L120 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L121 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L125 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L126 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArraySetNum`  
`struct FRigVMDispatch_ArraySetNum : public FRigVMDispatch_ArrayBaseMutable`  
_L130-152_
- reflection: `USTRUCT(meta=(DisplayName = "Set Num", Pure))`
- inherits: `FRigVMDispatch_ArrayBaseMutable`
- L135 _public function_ `FRigVMDispatch_ArraySetNum()`
- L140 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L141 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L142 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L143 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L145 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L146 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L150 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L151 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayIsEmpty`  
`struct FRigVMDispatch_ArrayIsEmpty : public FRigVMDispatch_ArrayBase`  
_L155-176_
- reflection: `USTRUCT(meta=(DisplayName = "IsEmpty"))`
- inherits: `FRigVMDispatch_ArrayBase`
- L160 _public function_ `FRigVMDispatch_ArrayIsEmpty()`
- L165 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L166 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L167 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L169 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L170 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L174 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L175 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayInit`  
`struct FRigVMDispatch_ArrayInit : public FRigVMDispatch_ArrayBaseMutable`  
_L179-200_
- reflection: `USTRUCT(meta=(DisplayName = "Init", Pure))`
- inherits: `FRigVMDispatch_ArrayBaseMutable`
- L184 _public function_ `FRigVMDispatch_ArrayInit()`
- L189 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L190 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L191 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L193 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L194 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L198 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L199 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayGetAtIndex`  
`struct FRigVMDispatch_ArrayGetAtIndex : public FRigVMDispatch_ArrayBase`  
_L203-225_
- reflection: `USTRUCT(meta=(DisplayName = "At", Keywords = "Get Index,At Index,[]"))`
- inherits: `FRigVMDispatch_ArrayBase`
- L208 _public function_ `FRigVMDispatch_ArrayGetAtIndex()`
- L213 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L214 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L215 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L216 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L218 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L219 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L223 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L224 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArraySetAtIndex`  
`struct FRigVMDispatch_ArraySetAtIndex : public FRigVMDispatch_ArrayBaseMutable`  
_L228-250_
- reflection: `USTRUCT(meta=(DisplayName = "Set At", Pure))`
- inherits: `FRigVMDispatch_ArrayBaseMutable`
- L233 _public function_ `FRigVMDispatch_ArraySetAtIndex()`
- L238 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L239 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L240 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L241 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L243 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L244 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L248 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L249 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayAdd`  
`struct FRigVMDispatch_ArrayAdd : public FRigVMDispatch_ArraySetAtIndex`  
_L253-274_
- reflection: `USTRUCT(meta=(DisplayName = "Add", Pure))`
- inherits: `FRigVMDispatch_ArraySetAtIndex`
- L258 _public function_ `FRigVMDispatch_ArrayAdd()`
- L263 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L264 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L265 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L267 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L268 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L272 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L273 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayInsert`  
`struct FRigVMDispatch_ArrayInsert : public FRigVMDispatch_ArraySetAtIndex`  
_L277-296_
- reflection: `USTRUCT(meta=(DisplayName = "Insert", Pure))`
- inherits: `FRigVMDispatch_ArraySetAtIndex`
- L282 _public function_ `FRigVMDispatch_ArrayInsert()`
- L287 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L289 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L290 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L294 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L295 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayRemove`  
`struct FRigVMDispatch_ArrayRemove : public FRigVMDispatch_ArrayBaseMutable`  
_L299-321_
- reflection: `USTRUCT(meta=(DisplayName = "Remove", Pure))`
- inherits: `FRigVMDispatch_ArrayBaseMutable`
- L304 _public function_ `FRigVMDispatch_ArrayRemove()`
- L309 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L310 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L311 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L312 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L314 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L315 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L319 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L320 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayReverse`  
`struct FRigVMDispatch_ArrayReverse : public FRigVMDispatch_ArrayReset`  
_L324-344_
- reflection: `USTRUCT(meta=(DisplayName = "Reverse", Pure))`
- inherits: `FRigVMDispatch_ArrayReset`
- L329 _public function_ `FRigVMDispatch_ArrayReverse()`
- L334 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L336 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L337 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L342 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L343 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayFind`  
`struct FRigVMDispatch_ArrayFind : public FRigVMDispatch_ArrayBase`  
_L347-369_
- reflection: `USTRUCT(meta=(DisplayName = "Find"))`
- inherits: `FRigVMDispatch_ArrayBase`
- L352 _public function_ `FRigVMDispatch_ArrayFind()`
- L357 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L358 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L359 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L360 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L362 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L363 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L367 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L368 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayAppend`  
`struct FRigVMDispatch_ArrayAppend : public FRigVMDispatch_ArrayBaseMutable`  
_L372-394_
- reflection: `USTRUCT(meta=(DisplayName = "Append", Pure))`
- inherits: `FRigVMDispatch_ArrayBaseMutable`
- L377 _public function_ `FRigVMDispatch_ArrayAppend()`
- L382 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L383 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L384 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L385 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L387 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L388 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L392 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L393 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayClone`  
`struct FRigVMDispatch_ArrayClone : public FRigVMDispatch_ArrayBase`  
_L397-419_
- reflection: `USTRUCT(meta=(DisplayName = "Clone"))`
- inherits: `FRigVMDispatch_ArrayBase`
- L402 _public function_ `FRigVMDispatch_ArrayClone()`
- L407 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L408 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L409 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L410 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L412 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L413 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L417 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L418 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayUnion`  
`struct FRigVMDispatch_ArrayUnion : public FRigVMDispatch_ArrayAppend`  
_L422-441_
- reflection: `USTRUCT(meta=(DisplayName = "Union", Pure))`
- inherits: `FRigVMDispatch_ArrayAppend`
- L427 _public function_ `FRigVMDispatch_ArrayUnion()`
- L432 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L434 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L435 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L439 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L440 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayDifference`  
`struct FRigVMDispatch_ArrayDifference : public FRigVMDispatch_ArrayBase`  
_L444-466_
- reflection: `USTRUCT(meta=(DisplayName = "Difference"))`
- inherits: `FRigVMDispatch_ArrayBase`
- L449 _public function_ `FRigVMDispatch_ArrayDifference()`
- L454 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L455 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L456 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L457 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L459 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L460 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L464 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L465 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayIntersection`  
`struct FRigVMDispatch_ArrayIntersection : public FRigVMDispatch_ArrayDifference`  
_L469-488_
- reflection: `USTRUCT(meta=(DisplayName = "Intersection"))`
- inherits: `FRigVMDispatch_ArrayDifference`
- L474 _public function_ `FRigVMDispatch_ArrayIntersection()`
- L479 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L481 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L482 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L486 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L487 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigVMDispatch_ArrayIterator`  
`struct FRigVMDispatch_ArrayIterator : public FRigVMDispatch_ArrayBaseMutable`  
_L491-518_
- reflection: `USTRUCT(meta=(DisplayName = "For Each", Icon="EditorStyle|GraphEditor.Macro.ForEach_16x", Pure))`
- inherits: `FRigVMDispatch_ArrayBaseMutable`
- L496 _public function_ `FRigVMDispatch_ArrayIterator()`
- L501 _public function_ `virtual ERigVMOpCode GetOpCode() const override`
- L502 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L503 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L504 _public prototype_ `virtual const TArray<FRigVMExecuteArgument>& GetExecuteArguments_Impl(const FRigVMDispatchContext& InContext) const override;`
- L506 _public prototype_ `virtual const TArray<FName>& GetControlFlowBlocks_Impl(const FRigVMDispatchContext& InContext, const FRigVMTemplateTypeMap& InTypeMap) const override;`
- L508 _public prototype_ `virtual const bool IsControlFlowBlockSliced(const FName& InBlockName) const override;`
- L509 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L511 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L512 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L516 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L517 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMDispatch_CastEnum.h` (Public)


#### struct `FRigVMDispatch_CastEnumBase`  
`struct FRigVMDispatch_CastEnumBase`  
_L8-12_
- L10 _public member_ `static inline const FLazyName ValueName = FLazyName(TEXT("Valu`
- L11 _public member_ `static inline const FLazyName ResultName = FLazyName(TEXT("Resu`

#### struct `FRigVMDispatch_CastEnumToInt`  
`struct FRigVMDispatch_CastEnumToInt : public FRigVMDispatchFactory #if CPP , public FRigVMDispatch_CastEnumBase #endif`  
_L15-40_
- reflection: `USTRUCT(meta=(DisplayName = "Cast", Category = "Enum", Keywords = "As", NodeColor = "1,1,1,1"))`
- inherits: `FRigVMDispatchFactory,FRigVMDispatch_CastEnumBase`
- L23 _public function_ `FRigVMDispatch_CastEnumToInt()`
- L28 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L29 _public prototype_ `virtual bool GetPermutationsFromArgumentType(const FName& InArgumentName, const TRigVMTypeIndex& InTypeIndex, TArray<FRigVMTemplateTypeMap, TInlineAllocator<1>>& OutPermutations, FRigVMRegistryHandle& InRegistry) const override;`
- L31 _public prototype_ `virtual FString GetNodeTitle(const FRigVMTemplateTypeMap& InTypes) const override;`
- L32 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L33 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L35 _public function_ `virtual bool IsSingleton() const override`
- L38 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L39 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`

#### struct `FRigVMDispatch_CastIntToEnum`  
`struct FRigVMDispatch_CastIntToEnum : public FRigVMDispatchFactory #if CPP , public FRigVMDispatch_CastEnumBase #endif`  
_L43-68_
- reflection: `USTRUCT(meta=(DisplayName = "Cast", Category = "Enum", Keywords = "As", NodeColor = "1,1,1,1"))`
- inherits: `FRigVMDispatchFactory,FRigVMDispatch_CastEnumBase`
- L51 _public function_ `FRigVMDispatch_CastIntToEnum()`
- L56 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L57 _public prototype_ `virtual bool GetPermutationsFromArgumentType(const FName& InArgumentName, const TRigVMTypeIndex& InTypeIndex, TArray<FRigVMTemplateTypeMap, TInlineAllocator<1>>& OutPermutations, FRigVMRegistryHandle& InRegistry) const override;`
- L59 _public prototype_ `virtual FString GetNodeTitle(const FRigVMTemplateTypeMap& InTypes) const override;`
- L60 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L61 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L63 _public function_ `virtual bool IsSingleton() const override`
- L66 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L67 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMDispatch_CastObject.h` (Public)


#### struct `FRigVMDispatch_CastObject`  
`struct FRigVMDispatch_CastObject : public FRigVMDispatchFactory`  
_L10-35_
- reflection: `USTRUCT(meta=(DisplayName = "Cast", Category = "Object", Keywords = "As", NodeColor = "1,1,1,1"))`
- inherits: `FRigVMDispatchFactory`
- L15 _public function_ `FRigVMDispatch_CastObject()`
- L20 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L21 _public prototype_ `virtual bool GetPermutationsFromArgumentType(const FName& InArgumentName, const TRigVMTypeIndex& InTypeIndex, TArray<FRigVMTemplateTypeMap, TInlineAllocator<1>>& OutPermutations, FRigVMRegistryHandle& InRegistry) const override;`
- L23 _public prototype_ `virtual FString GetNodeTitle(const FRigVMTemplateTypeMap& InTypes) const override;`
- L24 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L25 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L27 _public function_ `virtual bool IsSingleton() const override`
- L30 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L31 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`
- L33 _protected member_ `static inline const FLazyName ValueName = FLazyName(TEXT("Valu`
- L34 _protected member_ `static inline const FLazyName ResultName = FLazyName(TEXT("Resu`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMDispatch_Constant.h` (Public)


#### struct `FRigVMDispatch_Constant`  
`struct FRigVMDispatch_Constant : public FRigVMDispatch_CoreBase`  
_L11-40_
- reflection: `USTRUCT(meta=(DisplayName = "Constant", Category = "Core", Keywords = "Value,Reroute", NodeColor = "1,1,1,1"))`
- inherits: `FRigVMDispatch_CoreBase`
- L16 _public function_ `FRigVMDispatch_Constant()`
- L21 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L22 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L24 _public prototype_ `virtual FString GetNodeTitle(const FRigVMTemplateTypeMap& InTypes) const override;`
- L25 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L26 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L27 _public prototype_ `virtual FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const override;`
- L29 _public function_ `virtual bool IsSingleton() const override`
- L30 _public function_ `virtual bool SupportsRenaming() const override`
- L33 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L34 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`
- L36 _protected member_ `static inline const FLazyName ValueName = FLazyName(TEXT("Valu`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMDispatch_Core.h` (Public)


#### struct `FRigVMDispatch_CoreBase`  
`struct FRigVMDispatch_CoreBase : public FRigVMDispatchFactory`  
_L9-12_
- reflection: `USTRUCT(meta=(Abstract, Category = "Core", NodeColor = "0.762745, 1,0, 0.329412"))`
- inherits: `FRigVMDispatchFactory`

#### struct `FRigVMDispatch_CoreEquals`  
`struct FRigVMDispatch_CoreEquals : public FRigVMDispatch_CoreBase`  
_L18-92_
- reflection: `USTRUCT(meta=(DisplayName = "Equals", Keywords = "Same,=="))`
- inherits: `FRigVMDispatch_CoreBase`
- desc: Compares any two values and returns true if they are identical
- L24 _public function_ `FRigVMDispatch_CoreEquals()`
- L29 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L30 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L31 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L34 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L39 _protected prototype_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override;`
- L40 _protected prototype_ `static bool AdaptResult(bool bResult, const FRigVMExtendedExecuteContext& InContext);`
- L41 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`
- L44 _protected function_ `template<typename T> static void Equals(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates)`
- L55 _protected function_ `static void NameEquals(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates)`
- L66 _protected function_ `static void StringEquals(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates)`
- L78 _protected function_ `template<typename T> static void MathTypeEquals(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates)`
- L89 _protected member_ `static inline FLazyName AName = FLazyName(TEXT("A"))`
- L90 _protected member_ `static inline FLazyName BName = FLazyName(TEXT("B"))`
- L91 _protected member_ `static inline FLazyName ResultName = FLazyName(TEXT("Resu`

#### struct `FRigVMDispatch_CoreNotEquals`  
`struct FRigVMDispatch_CoreNotEquals : public FRigVMDispatch_CoreEquals`  
_L98-113_
- reflection: `USTRUCT(meta=(DisplayName = "Not Equals", Keywords = "Different,!=,Xor"))`
- inherits: `FRigVMDispatch_CoreEquals`
- desc: Compares any two values and returns true if they are not identical
- L102 _public function_ `FRigVMDispatch_CoreNotEquals()`
- L107 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMDispatch_If.h` (Public)


#### struct `FRigVMDispatch_If`  
`struct FRigVMDispatch_If : public FRigVMDispatch_CoreBase`  
_L13-43_
- reflection: `USTRUCT(meta=(DisplayName = "If", Category = "Execution", Keywords = "Branch,Condition", NodeColor = "0,1,0,1", Pure))`
- inherits: `FRigVMDispatch_CoreBase`
- desc: Chooses between two values based on a condition
- L19 _public function_ `FRigVMDispatch_If()`
- L24 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L25 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L26 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L27 _public function_ `virtual bool IsSingleton() const override`
- L30 _public prototype_ `virtual FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const override;`
- L31 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L36 _protected prototype_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override;`
- L37 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`
- L39 _protected member_ `static inline const FLazyName ConditionName = FLazyName(TEXT("Cond`
- L40 _protected member_ `static inline const FLazyName TrueName = FLazyName(TEXT("True`
- L41 _protected member_ `static inline const FLazyName FalseName = FLazyName(TEXT("Fals`
- L42 _protected member_ `static inline const FLazyName ResultName = FLazyName(TEXT("Resu`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMDispatch_MakeStruct.h` (Public)


#### struct `FRigVMDispatch_MakeStruct`  
`struct FRigVMDispatch_MakeStruct : public FRigVMDispatch_CoreBase`  
_L11-42_
- reflection: `USTRUCT(meta=(DisplayName = "Make", Category = "Core", Keywords = "Compose,Composition,Create,Constant", NodeColor = "1,1,1,1"))`
- inherits: `FRigVMDispatch_CoreBase`
- L16 _public function_ `FRigVMDispatch_MakeStruct()`
- L21 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L22 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L24 _public prototype_ `virtual FString GetNodeTitle(const FRigVMTemplateTypeMap& InTypes) const override;`
- L25 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L26 _public prototype_ `virtual FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const override;`
- L27 _public prototype_ `virtual FString GetKeywords() const override;`
- L28 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L30 _public function_ `virtual bool SupportsRenaming() const override`
- L33 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L34 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`
- L36 _protected member_ `static inline const FLazyName ElementsName = FLazyName(TEXT("Elem`
- L37 _protected member_ `static inline const FLazyName StructName = FLazyName(TEXT("Stru`

#### struct `FRigVMDispatch_BreakStruct`  
`struct FRigVMDispatch_BreakStruct : public FRigVMDispatch_MakeStruct`  
_L45-62_
- reflection: `USTRUCT(meta=(DisplayName = "Break", Keywords = "Decompose,Decomposition"))`
- inherits: `FRigVMDispatch_MakeStruct`
- L50 _public function_ `FRigVMDispatch_BreakStruct()`
- L55 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L57 _public prototype_ `virtual FText GetNodeTooltip(const FRigVMTemplateTypeMap& InTypes) const override;`
- L58 _public prototype_ `virtual FString GetKeywords() const override;`
- L59 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L61 _public function_ `virtual bool SupportsRenaming() const override`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMDispatch_Print.h` (Public)


#### struct `FRigVMDispatch_Print`  
`struct FRigVMDispatch_Print : public FRigVMDispatchFactory`  
_L12-48_
- reflection: `USTRUCT(meta=(DisplayName = "Print", NodeColor = "0.8, 0, 0.2, 1", Pure))`
- inherits: `FRigVMDispatchFactory`
- desc: Prints any value to the log
- L18 _public function_ `FRigVMDispatch_Print()`
- L23 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L24 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L25 _public prototype_ `virtual const TArray<FRigVMExecuteArgument>& GetExecuteArguments_Impl(const FRigVMDispatchContext& InContext) const override;`
- L26 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L27 _public function_ `virtual bool IsSingleton() const override`
- L30 _public prototype_ `virtual FString GetArgumentDefaultValue(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L31 _public prototype_ `virtual FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const override;`
- L32 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L37 _protected function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L41 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`
- L43 _protected member_ `static inline const FLazyName PrefixName = FLazyName(TEXT("Pref`
- L44 _protected member_ `static inline const FLazyName ValueName = FLazyName(TEXT("Valu`
- L45 _protected member_ `static inline const FLazyName EnabledName = FLazyName(TEXT("Enab`
- L46 _protected member_ `static inline const FLazyName ScreenDurationName = FLazyName(TEXT("Scre`
- L47 _protected member_ `static inline const FLazyName ScreenColorName = FLazyName(TEXT("Scre`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMDispatch_Select.h` (Public)


#### struct `FRigVMDispatch_SelectInt32`  
`struct FRigVMDispatch_SelectInt32 : public FRigVMDispatch_CoreBase`  
_L13-42_
- reflection: `USTRUCT(meta=(DisplayName = "Select", Category = "Execution", Keywords = "Switch,Case", NodeColor = "0,1,0,1", Pure))`
- inherits: `FRigVMDispatch_CoreBase`
- desc: Pick from a list of values based on an integer index
- L19 _public function_ `FRigVMDispatch_SelectInt32()`
- L24 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L25 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L26 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L28 _public prototype_ `virtual FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const override;`
- L29 _public prototype_ `virtual FString GetArgumentDefaultValue(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L30 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L32 _public function_ `virtual bool IsSingleton() const override`
- L36 _protected prototype_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override;`
- L37 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`
- L39 _protected member_ `static inline FLazyName IndexName = FLazyName(TEXT("Inde`
- L40 _protected member_ `static inline FLazyName ValuesName = FLazyName(TEXT("Valu`
- L41 _protected member_ `static inline FLazyName ResultName = FLazyName(TEXT("Resu`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMDispatch_Switch.h` (Public)


#### struct `FRigVMDispatch_SwitchBase`  
`struct FRigVMDispatch_SwitchBase : public FRigVMDispatch_CoreBase`  
_L10-32_
- reflection: `USTRUCT(meta=(Abstract, Category = "Switch", NodeColor = "0.762745, 1,0, 0.329412"))`
- inherits: `FRigVMDispatch_CoreBase`
- L16 _public prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L17 _public prototype_ `virtual const TArray<FRigVMExecuteArgument>& GetExecuteArguments_Impl(const FRigVMDispatchContext& InContext) const override;`
- L18 _public function_ `virtual bool IsSingleton() const override`
- L21 _public prototype_ `virtual FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const override;`
- L22 _public prototype_ `virtual FString GetArgumentDefaultValue(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L23 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L28 _protected prototype_ `static FName GetCaseName(int32 InIndex);`
- L30 _protected member_ `static inline const FLazyName IndexName = FLazyName(TEXT("Inde`
- L31 _protected member_ `static inline const FLazyName CasesName = FLazyName(TEXT("Case`

#### struct `FRigVMDispatch_SwitchInt32`  
`struct FRigVMDispatch_SwitchInt32 : public FRigVMDispatch_SwitchBase`  
_L38-64_
- reflection: `USTRUCT(meta=(DisplayName = "Switch", Category = "Execution", Keywords = "Case", NodeColor = "0,1,0,1", Pure))`
- inherits: `FRigVMDispatch_SwitchBase`
- desc: Run a branch based on an integer index
- L44 _public function_ `FRigVMDispatch_SwitchInt32()`
- L49 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L52 _public prototype_ `virtual FName GetDisplayNameForArgument(const FName& InArgumentName, const FRigVMTemplateTypeMap& InTypes) const override;`
- L56 _public prototype_ `virtual const TArray<FName>& GetControlFlowBlocks_Impl(const FRigVMDispatchContext& InContext, const FRigVMTemplateTypeMap& InTypeMap) const override;`
- L61 _protected prototype_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override;`
- L62 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`
- L63 _protected prototype_ `static FName GetCaseDisplayName(int32 InIndex);`

#### struct `FRigVMDispatch_SwitchEnum`  
`struct FRigVMDispatch_SwitchEnum : public FRigVMDispatch_SwitchBase`  
_L70-102_
- reflection: `USTRUCT(meta=(DisplayName = "Switch Enum", Category = "Execution", Keywords = "Case", NodeColor = "0,1,0,1", Pure))`
- inherits: `FRigVMDispatch_SwitchBase`
- desc: Run a branch based on an enum index
- L76 _public function_ `FRigVMDispatch_SwitchEnum()`
- L81 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L82 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L85 _public prototype_ `virtual FName GetDisplayNameForArgument(const FName& InArgumentName, const FRigVMTemplateTypeMap& InTypes) const override;`
- L89 _public prototype_ `virtual const TArray<FName>& GetControlFlowBlocks_Impl(const FRigVMDispatchContext& InContext, const FRigVMTemplateTypeMap& InTypeMap) const override;`
- L94 _protected prototype_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override;`
- L95 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`
- L98 _protected prototype_ `static FName GetCaseDisplayName(int32 InIndex, const UEnum* InEnum = nullptr);`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMFunctionDefines.h` (Public)


#### enum `ERigVMTransformSpace`  
`enum class ERigVMTransformSpace : uint8`  
_L11-21_
- reflection: `UENUM(meta = (RigVMTypeAllowed))`
- L14 _public enumerator_ `LocalSpace` — Apply in parent space
- L17 _public enumerator_ `GlobalSpace` — Apply in rig space
- L20 _public enumerator_ `Max UMETA(Hidden)` — MAX - invalid

#### enum `ERigVMClampSpatialMode::Type`  
`enum Type : int`  
_L26-32_
- L28 _public enumerator_ `Plane`
- L29 _public enumerator_ `Cylinder`
- L30 _public enumerator_ `Sphere`
- L31 _public enumerator_ `Capsule`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace ERigVMClampSpatialMode`
- L36 _macro_ `#define UE_RIGVMSTRUCT_REPORT(Severity, Format, ...) \`
- L41 _macro_ `#define UE_RIGVMSTRUCT_LOG_MESSAGE(Format, ...) UE_RIGVMSTRUCT_REPORT(Info, (Format), ##__VA_ARGS__)`
- L42 _macro_ `#define UE_RIGVMSTRUCT_REPORT_WARNING(Format, ...) UE_RIGVMSTRUCT_REPORT(Warning, (Format), ##__VA_ARGS__)`
- L43 _macro_ `#define UE_RIGVMSTRUCT_REPORT_ERROR(Format, ...) UE_RIGVMSTRUCT_REPORT(Error, (Format), ##__VA_ARGS__)`
- L45 _macro_ `#define UE_RIGVMSTRUCT_REPORT(Severity, Format, ...)`
- L46 _macro_ `#define UE_RIGVMSTRUCT_LOG_MESSAGE(Format, ...)`
- L47 _macro_ `#define UE_RIGVMSTRUCT_REPORT_WARNING(Format, ...)`
- L48 _macro_ `#define UE_RIGVMSTRUCT_REPORT_ERROR(Format, ...)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMFunction_ControlFlow.h` (Public)


#### struct `FRigVMFunction_ControlFlowBase`  
`struct FRigVMFunction_ControlFlowBase : public FRigVMStruct`  
_L12-15_
- reflection: `USTRUCT(meta=(Abstract, Category="Execution", NodeColor = "0, 0, 0, 1", DocumentationPolicy = "Strict"))`
- inherits: `FRigVMStruct`
- desc: The base class for all control flow nodes

#### struct `FRigVMFunction_ControlFlowBranch`  
`struct FRigVMFunction_ControlFlowBranch : public FRigVMFunction_ControlFlowBase`  
_L21-69_
- reflection: `USTRUCT(meta = (DisplayName = "Branch", Keywords = "If", Pure))`
- inherits: `FRigVMFunction_ControlFlowBase`
- desc: Executes either the True or False branch based on the condition
- L25 _public function_ `FRigVMFunction_ControlFlowBranch()`
- L31 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L35 _public function_ `virtual const TArray<FName>& GetControlFlowBlocks_Impl() const override`
- L48 _public member_ `FRigVMExecuteContext ExecuteContext;` — `UPROPERTY(meta=(Input, DisplayName="Execute"))` — The input execution pin to hook up to the graph
- L52 _public member_ `bool Condition;` — `UPROPERTY(meta=(Input))` — The condition based on which to pick between the True and False branches
- L56 _public member_ `FRigVMExecuteContext True;` — `UPROPERTY(meta=(Output))` — The branch to run if the condition is True
- L60 _public member_ `FRigVMExecuteContext False;` — `UPROPERTY(meta=(Output))` — The branch to run if the condition is False
- L64 _public member_ `FRigVMExecuteContext Completed;` — `UPROPERTY(meta=(Output))` — The execute flow to run when the True or False branch is complete
- L68 _public member_ `FName BlockToRun;` — `UPROPERTY(meta=(Singleton))` — The internal block to run as the node progresses

#### struct `FRigVMFunction_ControlFlowRunOnce`  
`struct FRigVMFunction_ControlFlowRunOnce : public FRigVMFunction_ControlFlowBase`  
_L75-118_
- reflection: `USTRUCT(meta = (DisplayName = "Run Once", Keywords = "Branch,if"))`
- inherits: `FRigVMFunction_ControlFlowBase`
- desc: Executes the Once branch only once
- L79 _public function_ `FRigVMFunction_ControlFlowRunOnce()`
- L85 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L89 _public function_ `virtual const TArray<FName>& GetControlFlowBlocks_Impl() const override`
- L101 _public member_ `FRigVMExecuteContext ExecuteContext;` — `UPROPERTY(meta=(Input, DisplayName="Execute"))` — The input execution pin to hook up to the graph
- L105 _public member_ `FRigVMExecuteContext Once;` — `UPROPERTY(meta=(Output))` — The branch to run once
- L109 _public member_ `FRigVMExecuteContext Completed;` — `UPROPERTY(meta=(Output))` — The execute flow to run every frame
- L113 _public member_ `FName BlockToRun;` — `UPROPERTY(meta=(Singleton))` — The internal block to run as the node progresses
- L117 _public member_ `bool HasRun;` — `UPROPERTY()` — The internal condition indicating if this has run once or now

#### struct `FRigVMFunction_ControlFlowTimer`  
`struct FRigVMFunction_ControlFlowTimer : public FRigVMFunction_ControlFlowBase`  
_L124-217_
- reflection: `USTRUCT(meta = (DisplayName = "Timer", Keywords = "Branch,If,Timeline,Execute"))`
- inherits: `FRigVMFunction_ControlFlowBase`
- desc: Executes the output branches based on a timer
- L128 _public function_ `FRigVMFunction_ControlFlowTimer()`
- L136 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L140 _public function_ `virtual const TArray<FName>& GetControlFlowBlocks_Impl() const override`
- L154 _public member_ `FRigVMExecuteContext ExecuteContext;` — `UPROPERTY(meta=(Input, DisplayName="Execute"))` — The input execution pin to hook up to the graph
- L158 _public member_ `bool Reset;` — `UPROPERTY(meta = (Input))` — A flag to reset / restart the timer
- L162 _public member_ `float Speed;` — `UPROPERTY(meta = (Input))` — The speed to apply to the played back time
- L166 _public member_ `float Duration;` — `UPROPERTY(meta = (Input))` — The duration in seconds the timer will take to complete
- L170 _public member_ `bool Repeats;` — `UPROPERTY(meta = (Input))` — A flag indicating if the timer is a one-shot or if it should repeat / loop
- L174 _public member_ `FRigVMExecuteContext JustStarted;` — `UPROPERTY(meta=(Output))` — The branch to run when the timer has just started
- L178 _public member_ `FRigVMExecuteContext IsRunning;` — `UPROPERTY(meta=(Output))` — The branch to run when the timer is running
- L182 _public member_ `FRigVMExecuteContext JustFinished;` — `UPROPERTY(meta=(Output))` — The branch to run when the timer has just finished
- L186 _public member_ `float Time;` — `UPROPERTY(meta=(Output))` — The played back / accumulated time in seconds
- L190 _public member_ `float Ratio;` — `UPROPERTY(meta=(Output))` — The played back / accumulated time as a ratio of time / duration (0.0 - 1.0)
- L194 _public member_ `FRigVMExecuteContext Completed;` — `UPROPERTY(meta=(Output))` — The execute flow to run every frame after all other branches
- L198 _public member_ `FName BlockToRun;` — `UPROPERTY(meta=(Singleton))` — The internal block to run as the node progresses
- L201 _public member_ `float AccumulatedValue;` — `UPROPERTY()`
- L204 _public member_ `bool bIsInitialized;` — `UPROPERTY()`
- L208 _public member_ `bool bJustStarted;` — `UPROPERTY(meta=(Singleton))` — True if the timer has just started
- L212 _public member_ `bool bIsRunning;` — `UPROPERTY(meta=(Singleton))` — True if the timer is running
- L216 _public member_ `bool bJustFinished;` — `UPROPERTY(meta=(Singleton))` — True if the timer has just finished

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMFunction_Name.h` (Public)


#### struct `FRigVMFunction_NameBase`  
`struct FRigVMFunction_NameBase : public FRigVMStruct`  
_L12-17_
- reflection: `USTRUCT(meta=(Abstract, Category="Core|Name", NodeColor = "0.462745, 1,0, 0.329412", DocumentationPolicy = "Strict"))`
- inherits: `FRigVMStruct`
- desc: The base class for all name operation nodes
- L16 _public function_ `virtual void Execute()`

#### struct `FRigVMFunction_NameConcat`  
`struct FRigVMFunction_NameConcat : public FRigVMFunction_NameBase`  
_L23-46_
- reflection: `USTRUCT(meta = (DisplayName = "Concat", TemplateName = "Concat", Keywords = "Add,+,Combine,Merge,Append"))`
- inherits: `FRigVMFunction_NameBase`
- desc: Concatenates two names together to make a new name
- L27 _public function_ `FRigVMFunction_NameConcat()`
- L32 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L37 _public member_ `FName A;` — `UPROPERTY(meta=(Input, Aggregate))` — The first / left name to concatenate
- L41 _public member_ `FName B;` — `UPROPERTY(meta=(Input, Aggregate))` — The second / right name to concatenate
- L45 _public member_ `FName Result;` — `UPROPERTY(meta=(Output, Aggregate))` — The resulting concatenated name

#### struct `FRigVMFunction_NameTruncate`  
`struct FRigVMFunction_NameTruncate : public FRigVMFunction_NameBase`  
_L52-85_
- reflection: `USTRUCT(meta = (DisplayName = "Chop", TemplateName = "Chop", Keywords = "Truncate,-,Remove,Subtract,Split"))`
- inherits: `FRigVMFunction_NameBase`
- desc: Returns the left or right most characters from the name chopping the given number of characters from the start or the end
- L56 _public function_ `FRigVMFunction_NameTruncate()`
- L63 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L68 _public member_ `FName Name;` — `UPROPERTY(meta=(Input))` — The input name to chop
- L72 _public member_ `int32 Count;` — `UPROPERTY(meta=(Input))` — Number of characters to remove from left or right
- L76 _public member_ `bool FromEnd;` — `UPROPERTY(meta=(Input))` — if set to true the characters will be removed from the end
- L80 _public member_ `FName Remainder;` — `UPROPERTY(meta=(Output))` — the part of the name without the chopped characters
- L84 _public member_ `FName Chopped;` — `UPROPERTY(meta = (Output))` — the part of the name that has been chopped off

#### struct `FRigVMFunction_NameReplace`  
`struct FRigVMFunction_NameReplace : public FRigVMFunction_NameBase`  
_L91-118_
- reflection: `USTRUCT(meta = (DisplayName = "Replace", TemplateName = "Replace", Keywords = "Search,Emplace,Find"))`
- inherits: `FRigVMFunction_NameBase`
- desc: Replace all occurrences of a subname in this name
- L95 _public function_ `FRigVMFunction_NameReplace()`
- L100 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L105 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The input name to search within
- L109 _public member_ `FName Old;` — `UPROPERTY(meta = (Input))` — The old name to search for
- L113 _public member_ `FName New;` — `UPROPERTY(meta = (Input))` — The new name to replace the old name with
- L117 _public member_ `FName Result;` — `UPROPERTY(meta = (Output))` — The resulting replaced name

#### struct `FRigVMFunction_EndsWith`  
`struct FRigVMFunction_EndsWith : public FRigVMFunction_NameBase`  
_L124-148_
- reflection: `USTRUCT(meta = (DisplayName = "Ends With", TemplateName = "EndsWith", Keywords = "Right"))`
- inherits: `FRigVMFunction_NameBase`
- desc: Tests whether this name ends with given name
- L128 _public function_ `FRigVMFunction_EndsWith()`
- L134 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L139 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The input name to search within
- L143 _public member_ `FName Ending;` — `UPROPERTY(meta = (Input))` — The ending name to look for
- L147 _public member_ `bool Result;` — `UPROPERTY(meta = (Output))` — True if the given input name ends with the given ending

#### struct `FRigVMFunction_StartsWith`  
`struct FRigVMFunction_StartsWith : public FRigVMFunction_NameBase`  
_L154-178_
- reflection: `USTRUCT(meta = (DisplayName = "Starts With", TemplateName = "StartsWith", Keywords = "Left"))`
- inherits: `FRigVMFunction_NameBase`
- desc: Tests whether this name starts with given name
- L158 _public function_ `FRigVMFunction_StartsWith()`
- L164 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L169 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The input name to search within
- L173 _public member_ `FName Start;` — `UPROPERTY(meta = (Input))` — The start name to look for
- L177 _public member_ `bool Result;` — `UPROPERTY(meta = (Output))` — True if the given input name starts with the given start string

#### struct `FRigVMFunction_Contains`  
`struct FRigVMFunction_Contains : public FRigVMFunction_NameBase`  
_L184-208_
- reflection: `USTRUCT(meta = (DisplayName = "Contains", TemplateName = "Contains", Keywords = "Contains,Find,Has,Search"))`
- inherits: `FRigVMFunction_NameBase`
- desc: Returns true or false if a given name exists in another given name
- L188 _public function_ `FRigVMFunction_Contains()`
- L194 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L199 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The input name to search within
- L203 _public member_ `FName Search;` — `UPROPERTY(meta = (Input))` — The name to search for
- L207 _public member_ `bool Result;` — `UPROPERTY(meta = (Output))` — True if a given name exists in another given name

#### struct `FRigVMFunction_IsNone`  
`struct FRigVMFunction_IsNone : public FRigVMFunction_NameBase`  
_L214-234_
- reflection: `USTRUCT(meta = (DisplayName = "Is None", TemplateName = "IsNone", Keywords = "Empty,Valid"))`
- inherits: `FRigVMFunction_NameBase`
- desc: Returns true if this name is none
- L218 _public function_ `FRigVMFunction_IsNone()`
- L224 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L229 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The input name to check
- L233 _public member_ `bool Result;` — `UPROPERTY(meta = (Output))` — True if the input name is None

#### struct `FRigVMFunction_IsNameValid`  
`struct FRigVMFunction_IsNameValid : public FRigVMFunction_NameBase`  
_L240-260_
- reflection: `USTRUCT(meta = (DisplayName = "Is Valid", TemplateName = "IsValid", Keywords = "Empty,Valid"))`
- inherits: `FRigVMFunction_NameBase`
- desc: Returns true if this name is valid / is not none
- L244 _public function_ `FRigVMFunction_IsNameValid()`
- L250 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L255 _public member_ `FName Value;` — `UPROPERTY(meta = (Input))` — The input name to check
- L259 _public member_ `bool Result;` — `UPROPERTY(meta = (Output))` — True if the name is valid/ is not None

#### struct `FRigVMFunction_GetNameNumericSuffix`  
`struct FRigVMFunction_GetNameNumericSuffix : public FRigVMFunction_NameBase`  
_L266-291_
- reflection: `USTRUCT(meta = (DisplayName = "Get Numeric Suffix", Keywords = "Suffix,Number,Integer"))`
- inherits: `FRigVMFunction_NameBase`
- desc: Tests whether this name ends with a numeric suffix
- L270 _public function_ `FRigVMFunction_GetNameNumericSuffix()`
- L277 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L282 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The input name to check for a numeric suffix
- L286 _public member_ `int32 Suffix;` — `UPROPERTY(meta = (Output))` — The resulting suffix (if it exists)
- L290 _public member_ `bool Success;` — `UPROPERTY(meta = (Output))` — True if the name ends with the given numeric suffix

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/RigVMFunction_String.h` (Public)


#### struct `FRigVMFunction_StringBase`  
`struct FRigVMFunction_StringBase : public FRigVMStruct`  
_L13-16_
- reflection: `USTRUCT(meta=(Abstract, Category="Core|String", NodeColor = "0.462745, 1,0, 0.329412", DocumentationPolicy = "Strict"))`
- inherits: `FRigVMStruct`
- desc: The base class for all string operation nodes

#### struct `FRigVMFunction_StringConcat`  
`struct FRigVMFunction_StringConcat : public FRigVMFunction_StringBase`  
_L22-45_
- reflection: `USTRUCT(meta = (DisplayName = "Concat", TemplateName = "Concat", Keywords = "Add,+,Combine,Merge,Append"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Concatenates two strings together to make a new string
- L26 _public function_ `FRigVMFunction_StringConcat()`
- L31 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L36 _public member_ `FString A;` — `UPROPERTY(meta=(Input, Aggregate))` — The first / left string to concatenate
- L40 _public member_ `FString B;` — `UPROPERTY(meta=(Input, Aggregate))` — The second / right string to concatenate
- L44 _public member_ `FString Result;` — `UPROPERTY(meta=(Output, Aggregate))` — The resulting concatenated string

#### struct `FRigVMFunction_StringTruncate`  
`struct FRigVMFunction_StringTruncate : public FRigVMFunction_StringBase`  
_L51-84_
- reflection: `USTRUCT(meta = (DisplayName = "Chop", TemplateName = "Chop", Keywords = "Truncate,-,Remove,Subtract,Split"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Returns the left or right most characters from the string chopping the given number of characters from the start or the end
- L55 _public function_ `FRigVMFunction_StringTruncate()`
- L62 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L67 _public member_ `FString Name;` — `UPROPERTY(meta=(Input))` — The input string to chop
- L71 _public member_ `int32 Count;` — `UPROPERTY(meta=(Input))` — Number of characters to remove from left or right
- L75 _public member_ `bool FromEnd;` — `UPROPERTY(meta=(Input))` — if set to true the characters will be removed from the end
- L79 _public member_ `FString Remainder;` — `UPROPERTY(meta=(Output))` — the part of the string without the chopped characters
- L83 _public member_ `FString Chopped;` — `UPROPERTY(meta = (Output))` — the part of the name that has been chopped off

#### struct `FRigVMFunction_StringReplace`  
`struct FRigVMFunction_StringReplace : public FRigVMFunction_StringBase`  
_L90-117_
- reflection: `USTRUCT(meta = (DisplayName = "Replace", TemplateName = "Replace", Keywords = "Search,Emplace,Find"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Replace all occurrences of a substring in this string
- L94 _public function_ `FRigVMFunction_StringReplace()`
- L99 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L104 _public member_ `FString Name;` — `UPROPERTY(meta = (Input))` — The input string to search within
- L108 _public member_ `FString Old;` — `UPROPERTY(meta = (Input))` — The old string to search for
- L112 _public member_ `FString New;` — `UPROPERTY(meta = (Input))` — The new string to replace the old string with
- L116 _public member_ `FString Result;` — `UPROPERTY(meta = (Output))` — The resulting replaced string

#### struct `FRigVMFunction_StringEndsWith`  
`struct FRigVMFunction_StringEndsWith : public FRigVMFunction_StringBase`  
_L123-147_
- reflection: `USTRUCT(meta = (DisplayName = "Ends With", TemplateName = "EndsWith", Keywords = "Right"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Tests whether this string ends with given string
- L127 _public function_ `FRigVMFunction_StringEndsWith()`
- L133 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L138 _public member_ `FString Name;` — `UPROPERTY(meta = (Input))` — The input string to search within
- L142 _public member_ `FString Ending;` — `UPROPERTY(meta = (Input))` — The ending string to look for
- L146 _public member_ `bool Result;` — `UPROPERTY(meta = (Output))` — True if the given input string ends with the given ending

#### struct `FRigVMFunction_StringStartsWith`  
`struct FRigVMFunction_StringStartsWith : public FRigVMFunction_StringBase`  
_L153-177_
- reflection: `USTRUCT(meta = (DisplayName = "Starts With", TemplateName = "StartsWith", Keywords = "Left"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Tests whether this string starts with given string
- L157 _public function_ `FRigVMFunction_StringStartsWith()`
- L163 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L168 _public member_ `FString Name;` — `UPROPERTY(meta = (Input))` — The input string to search within
- L172 _public member_ `FString Start;` — `UPROPERTY(meta = (Input))` — The start string to look for
- L176 _public member_ `bool Result;` — `UPROPERTY(meta = (Output))` — True if the given input string starts with the given start string

#### struct `FRigVMFunction_StringContains`  
`struct FRigVMFunction_StringContains : public FRigVMFunction_StringBase`  
_L183-207_
- reflection: `USTRUCT(meta = (DisplayName = "Contains", TemplateName = "Contains", Keywords = "Contains,Find,Has,Search"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Returns true or false if a given name exists in another given name
- L187 _public function_ `FRigVMFunction_StringContains()`
- L193 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L198 _public member_ `FString Name;` — `UPROPERTY(meta = (Input))` — The input string to search within
- L202 _public member_ `FString Search;` — `UPROPERTY(meta = (Input))` — The string to search for
- L206 _public member_ `bool Result;` — `UPROPERTY(meta = (Output))` — True if a given string exists in another given string

#### struct `FRigVMFunction_StringLength`  
`struct FRigVMFunction_StringLength : public FRigVMFunction_StringBase`  
_L213-233_
- reflection: `USTRUCT(meta = (DisplayName = "Length"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Returns the length of a string
- L217 _public function_ `FRigVMFunction_StringLength()`
- L223 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L228 _public member_ `FString Value;` — `UPROPERTY(meta = (Input))` — The input string to retrieve the length for
- L232 _public member_ `int32 Length;` — `UPROPERTY(meta = (Output))` — The resulting length of the input string

#### struct `FRigVMFunction_StringTrimWhitespace`  
`struct FRigVMFunction_StringTrimWhitespace : public FRigVMFunction_StringBase`  
_L239-258_
- reflection: `USTRUCT(meta = (DisplayName = "Trim Whitespace", Keywords = "Space,WhiteSpace,Remove,Truncate"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Trims the whitespace from a string (start and end)
- L243 _public function_ `FRigVMFunction_StringTrimWhitespace()`
- L248 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L253 _public member_ `FString Value;` — `UPROPERTY(meta = (Input))` — The input string to trim
- L257 _public member_ `FString Result;` — `UPROPERTY(meta = (Output))` — The resulting trimmed string

#### struct `FRigVMFunction_StringToUppercase`  
`struct FRigVMFunction_StringToUppercase : public FRigVMFunction_StringBase`  
_L264-283_
- reflection: `USTRUCT(meta = (DisplayName = "To Uppercase"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Converts the string to upper case
- L268 _public function_ `FRigVMFunction_StringToUppercase()`
- L273 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L278 _public member_ `FString Value;` — `UPROPERTY(meta = (Input))` — The input string to convert to uppercase
- L282 _public member_ `FString Result;` — `UPROPERTY(meta = (Output))` — The resulting uppercased string

#### struct `FRigVMFunction_StringToLowercase`  
`struct FRigVMFunction_StringToLowercase : public FRigVMFunction_StringBase`  
_L289-308_
- reflection: `USTRUCT(meta = (DisplayName = "To Lowercase"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Converts the string to lower case
- L293 _public function_ `FRigVMFunction_StringToLowercase()`
- L298 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L303 _public member_ `FString Value;` — `UPROPERTY(meta = (Input))` — The input string to convert to lowercase
- L307 _public member_ `FString Result;` — `UPROPERTY(meta = (Output))` — The resulting lowercased string

#### struct `FRigVMFunction_StringReverse`  
`struct FRigVMFunction_StringReverse : public FRigVMFunction_StringBase`  
_L314-333_
- reflection: `USTRUCT(meta = (DisplayName = "Reverse"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Returns the reverse of the input string
- L318 _public function_ `FRigVMFunction_StringReverse()`
- L323 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L328 _public member_ `FString Value;` — `UPROPERTY(meta = (Input))` — The input string to reverse
- L332 _public member_ `FString Reverse;` — `UPROPERTY(meta = (Output))` — The resulting reversed string

#### struct `FRigVMFunction_StringLeft`  
`struct FRigVMFunction_StringLeft : public FRigVMFunction_StringBase`  
_L339-363_
- reflection: `USTRUCT(meta = (DisplayName = "Left", Keywords = "Start,Begin"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Returns the left most characters of a string
- L343 _public function_ `FRigVMFunction_StringLeft()`
- L349 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L354 _public member_ `FString Value;` — `UPROPERTY(meta = (Input))` — The input string to retrieve the left most characters of
- L358 _public member_ `int32 Count;` — `UPROPERTY(meta = (Input))` — The number of characters to retrieve
- L362 _public member_ `FString Result;` — `UPROPERTY(meta = (Output))` — The resulting left most characters of the input string

#### struct `FRigVMFunction_StringRight`  
`struct FRigVMFunction_StringRight : public FRigVMFunction_StringBase`  
_L369-393_
- reflection: `USTRUCT(meta = (DisplayName = "Right", Keywords = "End"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Returns the right most characters of a string
- L373 _public function_ `FRigVMFunction_StringRight()`
- L379 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L384 _public member_ `FString Value;` — `UPROPERTY(meta = (Input))` — The input string to retrieve the right most characters of
- L388 _public member_ `int32 Count;` — `UPROPERTY(meta = (Input))` — The number of characters to retrieve
- L392 _public member_ `FString Result;` — `UPROPERTY(meta = (Output))` — The resulting right most characters of the input string

#### struct `FRigVMFunction_StringMiddle`  
`struct FRigVMFunction_StringMiddle : public FRigVMFunction_StringBase`  
_L399-428_
- reflection: `USTRUCT(meta = (DisplayName = "Middle", Keywords = "Within,Center"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Returns the middle section of a string
- L403 _public function_ `FRigVMFunction_StringMiddle()`
- L410 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L415 _public member_ `FString Value;` — `UPROPERTY(meta = (Input))` — The input string to retrieve a section of
- L419 _public member_ `int32 Start;` — `UPROPERTY(meta = (Input))` — the index of the first character
- L423 _public member_ `int32 Count;` — `UPROPERTY(meta = (Input))` — if count is set to -1 all character from Start will be returned
- L427 _public member_ `FString Result;` — `UPROPERTY(meta = (Output))` — The resulting section of the input string given start and count

#### struct `FRigVMFunction_StringFind`  
`struct FRigVMFunction_StringFind : public FRigVMFunction_StringBase`  
_L434-463_
- reflection: `USTRUCT(meta = (DisplayName = "Find", Keywords = "IndexOf"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Finds a string within another string
- L438 _public function_ `FRigVMFunction_StringFind()`
- L445 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L450 _public member_ `FString Value;` — `UPROPERTY(meta = (Input))` — The input string to search within
- L454 _public member_ `FString Search;` — `UPROPERTY(meta = (Input))` — The string to search for
- L458 _public member_ `bool Found;` — `UPROPERTY(meta = (Output))` — True if the search string was found in the input string
- L462 _public member_ `int32 Index;` — `UPROPERTY(meta = (Output))` — The index of the search string within the input string (or INDEX_NONE)

#### struct `FRigVMFunction_StringSplit`  
`struct FRigVMFunction_StringSplit : public FRigVMFunction_StringBase`  
_L469-492_
- reflection: `USTRUCT(meta = (DisplayName = "Split"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Splits a string into multiple sections given a separator
- L473 _public function_ `FRigVMFunction_StringSplit()`
- L478 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L483 _public member_ `FString Value;` — `UPROPERTY(meta = (Input))` — The input string to split up
- L487 _public member_ `FString Separator;` — `UPROPERTY(meta = (Input))` — The separator to use to split up the input string
- L491 _public member_ `TArray<FString> Result;` — `UPROPERTY(meta = (Output))` — The array of split up parts of the input string

#### struct `FRigVMFunction_StringJoin`  
`struct FRigVMFunction_StringJoin : public FRigVMFunction_StringBase`  
_L498-521_
- reflection: `USTRUCT(meta = (DisplayName = "Join", Keywords = "Combine"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Joins a string into multiple sections given a separator
- L502 _public function_ `FRigVMFunction_StringJoin()`
- L507 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L512 _public member_ `TArray<FString> Values;` — `UPROPERTY(meta = (Input))` — An array of input strings to join
- L516 _public member_ `FString Separator;` — `UPROPERTY(meta = (Input))` — The separator to use when joining the parts
- L520 _public member_ `FString Result;` — `UPROPERTY(meta = (Output))` — The resulting joined string

#### struct `FRigVMFunction_StringPadInteger`  
`struct FRigVMFunction_StringPadInteger : public FRigVMFunction_StringBase`  
_L527-552_
- reflection: `USTRUCT(meta = (DisplayName = "Pad Integer", Keywords = "FromInt,Number,LeadingZeroes"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Converts an integer number to a string with padding
- L531 _public function_ `FRigVMFunction_StringPadInteger()`
- L538 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L543 _public member_ `int32 Value;` — `UPROPERTY(meta = (Input))` — The input number to convert to a string (for example 4)
- L547 _public member_ `int32 Digits;` — `UPROPERTY(meta = (Input))` — The number of digits in total to use (for example 3)
- L551 _public member_ `FString Result;` — `UPROPERTY(meta = (Output))` — The resulting string representing the padded integer (for example '004')

#### struct `FRigVMFunction_StringToInteger`  
`struct FRigVMFunction_StringToInteger : public FRigVMFunction_StringBase`  
_L558-591_
- reflection: `USTRUCT(meta = (DisplayName = "To Integer", Keywords = "ToInt,Number"))`
- inherits: `FRigVMFunction_StringBase`
- desc: Converts a string to an integer
- L562 _public function_ `FRigVMFunction_StringToInteger()`
- L569 _public prototype_ `RIGVM_METHOD() virtual void Execute();`
- L574 _public member_ `FString Value;` — `UPROPERTY(meta = (Input))` — The input string to convert to integer
- L578 _public member_ `bool ChopLeft;` — `UPROPERTY(meta = (Input))` — chops non-digit characters from the left of the string
- L582 _public member_ `bool ChopRight;` — `UPROPERTY(meta = (Input))` — chops non-digit characters from the right of the string
- L586 _public member_ `int32 Result;` — `UPROPERTY(meta = (Output))` — The resulting integer number (or INDEX_NONE)
- L590 _public member_ `bool Success;` — `UPROPERTY(meta = (Output))` — True if the string was successfully converted to integer

#### struct `FRigDispatch_ToString`  
`struct FRigDispatch_ToString : public FRigVMDispatchFactory`  
_L597-614_
- reflection: `USTRUCT(meta=(DisplayName = "To String", NodeColor = "0.462745, 1,0, 0.329412"))`
- inherits: `FRigVMDispatchFactory`
- desc: Converts any value to string
- L603 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L604 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L607 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L612 _protected prototype_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override;`
- L613 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

#### struct `FRigDispatch_FromString`  
`struct FRigDispatch_FromString : public FRigVMDispatchFactory`  
_L620-637_
- reflection: `USTRUCT(meta=(DisplayName = "From String", NodeColor = "0.462745, 1,0, 0.329412"))`
- inherits: `FRigVMDispatchFactory`
- desc: Converts a string into any value
- L626 _public prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L627 _public prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L630 _public prototype_ `virtual FText GetArgumentTooltip(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex) const override;`
- L635 _protected prototype_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override;`
- L636 _protected prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray Predicates);`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Simulation/RigVMFunction_Accumulate.h` (Public)


#### struct `FRigVMFunction_AccumulateBase`  
`struct FRigVMFunction_AccumulateBase : public FRigVMFunction_SimBase`  
_L12-15_
- reflection: `USTRUCT(meta=(Category="Simulation|Accumulate"))`
- inherits: `FRigVMFunction_SimBase`
- desc: The base class for all accumulation nodes

#### struct `FRigVMFunction_AccumulateFloatAdd`  
`struct FRigVMFunction_AccumulateFloatAdd : public FRigVMFunction_AccumulateBase`  
_L21-59_
- reflection: `USTRUCT(meta=(DisplayName="Accumulate Add (Float)", TemplateName="AccumulateAdd", Keywords="Simulate,++"))`
- inherits: `FRigVMFunction_AccumulateBase`
- desc: Adds a value over time over and over again
- L25 _public function_ `FRigVMFunction_AccumulateFloatAdd()`
- L32 _public function_ `virtual void Initialize() override`
- L34 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L39 _public member_ `float Increment;` — `UPROPERTY(meta=(Input))` — The value added on every iteration (depending on the IntegrateDeltaTime flag)
- L43 _public member_ `float InitialValue;` — `UPROPERTY(meta = (Input))` — The initial value to start at
- L48 _public member_ `bool bIntegrateDeltaTime;` — `UPROPERTY(meta=(Input))` — If True, the increment will be multiplied by the delta time as it is accumulated, treating it as a rate of change. This is advisable when dealing with variable frame rates.
- L52 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting accumulated value
- L55 _public member_ `float AccumulatedValue;` — `UPROPERTY()`
- L58 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_AccumulateVectorAdd`  
`struct FRigVMFunction_AccumulateVectorAdd : public FRigVMFunction_AccumulateBase`  
_L65-103_
- reflection: `USTRUCT(meta = (DisplayName="Accumulate Add (Vector)", TemplateName="AccumulateAdd", Keywords="Simulate,++"))`
- inherits: `FRigVMFunction_AccumulateBase`
- desc: Adds a vector over time over and over again
- L69 _public function_ `FRigVMFunction_AccumulateVectorAdd()`
- L76 _public function_ `virtual void Initialize() override`
- L78 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L83 _public member_ `FVector Increment;` — `UPROPERTY(meta = (Input))` — The value added on every iteration (depending on the IntegrateDeltaTime flag)
- L87 _public member_ `FVector InitialValue;` — `UPROPERTY(meta = (Input))` — The initial value to start at
- L92 _public member_ `bool bIntegrateDeltaTime;` — `UPROPERTY(meta = (Input))` — If True, the increment will be multiplied by the delta time as it is accumulated, treating it as a rate of change. This is advisable when dealing with variable frame rates.
- L96 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting accumulated value
- L99 _public member_ `FVector AccumulatedValue;` — `UPROPERTY()`
- L102 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_AccumulateFloatMul`  
`struct FRigVMFunction_AccumulateFloatMul : public FRigVMFunction_AccumulateBase`  
_L109-147_
- reflection: `USTRUCT(meta=(DisplayName="Accumulate Mul (Float)", TemplateName="AccumulateMul", Keywords="Simulate,**"))`
- inherits: `FRigVMFunction_AccumulateBase`
- desc: Multiplies a value over time over and over again
- L113 _public function_ `FRigVMFunction_AccumulateFloatMul()`
- L120 _public function_ `virtual void Initialize() override`
- L122 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L127 _public member_ `float Multiplier;` — `UPROPERTY(meta=(Input))` — The multiplier to apply on every iteration (depending on the IntegrateDeltaTime flag)
- L131 _public member_ `float InitialValue;` — `UPROPERTY(meta = (Input))` — The initial value to start at
- L136 _public member_ `bool bIntegrateDeltaTime;` — `UPROPERTY(meta=(Input))` — If True, the multiplier will be scaled depending on the delta time as it is accumulated, making the resulting accumulation less sensitive to varying frame rates.
- L140 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting accumulated value
- L143 _public member_ `float AccumulatedValue;` — `UPROPERTY()`
- L146 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_AccumulateVectorMul`  
`struct FRigVMFunction_AccumulateVectorMul : public FRigVMFunction_AccumulateBase`  
_L153-191_
- reflection: `USTRUCT(meta = (DisplayName="Accumulate Mul (Vector)", TemplateName="AccumulateMul", Keywords="Simulate,**"))`
- inherits: `FRigVMFunction_AccumulateBase`
- desc: Multiplies a vector over time over and over again
- L157 _public function_ `FRigVMFunction_AccumulateVectorMul()`
- L164 _public function_ `virtual void Initialize() override`
- L166 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L171 _public member_ `FVector Multiplier;` — `UPROPERTY(meta = (Input))` — The multiplier to apply on every iteration (depending on the IntegrateDeltaTime flag)
- L175 _public member_ `FVector InitialValue;` — `UPROPERTY(meta = (Input))` — The initial value to start at
- L180 _public member_ `bool bIntegrateDeltaTime;` — `UPROPERTY(meta = (Input))` — If True, the multiplier will be scaled depending on the delta time as it is accumulated, making the resulting accumulation less sensitive to varying frame rates.
- L184 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting accumulated value
- L187 _public member_ `FVector AccumulatedValue;` — `UPROPERTY()`
- L190 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_AccumulateQuatMul`  
`struct FRigVMFunction_AccumulateQuatMul : public FRigVMFunction_AccumulateBase`  
_L197-239_
- reflection: `USTRUCT(meta=(DisplayName="Accumulate Mul (Quaternion)", TemplateName="AccumulateMul", Keywords="Simulate,**"))`
- inherits: `FRigVMFunction_AccumulateBase`
- desc: Multiplies a quaternion over time over and over again
- L201 _public function_ `FRigVMFunction_AccumulateQuatMul()`
- L208 _public function_ `virtual void Initialize() override`
- L210 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L215 _public member_ `FQuat Multiplier;` — `UPROPERTY(meta=(Input))` — The multiplier to apply on every iteration (depending on the IntegrateDeltaTime flag)
- L219 _public member_ `FQuat InitialValue;` — `UPROPERTY(meta = (Input))` — The initial value to start at
- L223 _public member_ `bool bFlipOrder;` — `UPROPERTY(meta = (Input))` — If True the multiplier will be pre-multiplied, otherwise post-multiplied
- L228 _public member_ `bool bIntegrateDeltaTime;` — `UPROPERTY(meta=(Input))` — If True, the multiplier will be scaled depending on the delta time as it is accumulated, making the resulting accumulation less sensitive to varying frame rates.
- L232 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The resulting accumulated value
- L235 _public member_ `FQuat AccumulatedValue;` — `UPROPERTY()`
- L238 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_AccumulateTransformMul`  
`struct FRigVMFunction_AccumulateTransformMul : public FRigVMFunction_AccumulateBase`  
_L245-287_
- reflection: `USTRUCT(meta = (DisplayName="Accumulate Mul (Transform)", TemplateName="AccumulateMul", Keywords="Simulate,**"))`
- inherits: `FRigVMFunction_AccumulateBase`
- desc: Multiplies a transform over time over and over again
- L249 _public function_ `FRigVMFunction_AccumulateTransformMul()`
- L256 _public function_ `virtual void Initialize() override`
- L258 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L263 _public member_ `FTransform Multiplier;` — `UPROPERTY(meta = (Input))` — The multiplier to apply for every iteration (depending on the IntegrateDeltaTime flag)
- L267 _public member_ `FTransform InitialValue;` — `UPROPERTY(meta = (Input))` — The initial value to start at
- L271 _public member_ `bool bFlipOrder;` — `UPROPERTY(meta = (Input))` — If True the multiplier will be pre-multiplied, otherwise post-multiplied
- L276 _public member_ `bool bIntegrateDeltaTime;` — `UPROPERTY(meta = (Input))` — If True, the multiplier will be scaled depending on the delta time as it is accumulated, making the resulting accumulation less sensitive to varying frame rates.
- L280 _public member_ `FTransform Result;` — `UPROPERTY(meta = (Output))` — The resulting accumulated value
- L283 _public member_ `FTransform AccumulatedValue;` — `UPROPERTY()`
- L286 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_AccumulateFloatLerp`  
`struct FRigVMFunction_AccumulateFloatLerp : public FRigVMFunction_AccumulateBase`  
_L293-336_
- reflection: `USTRUCT(meta=(DisplayName="Accumulate Lerp (Float)", TemplateName="AccumulateLerp", Keywords="Simulate,Ramp"))`
- inherits: `FRigVMFunction_AccumulateBase`
- desc: Interpolates two values over time over and over again
- L297 _public function_ `FRigVMFunction_AccumulateFloatLerp()`
- L304 _public function_ `virtual void Initialize() override`
- L306 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L311 _public member_ `float TargetValue;` — `UPROPERTY(meta=(Input))` — The target value to interpolate towards
- L315 _public member_ `float InitialValue;` — `UPROPERTY(meta = (Input))` — The initial value to start at
- L320 _public member_ `float Blend;` — `UPROPERTY(meta = (Input))` — The blend to use for the interpolation. This value may be scaled down based on the Integrate Delta Time setting
- L325 _public member_ `bool bIntegrateDeltaTime;` — `UPROPERTY(meta=(Input))` — If True the integration will be relying on the delta time to create more deterministic results with varying framerates.
- L329 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting accumulated value
- L332 _public member_ `float AccumulatedValue;` — `UPROPERTY()`
- L335 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_AccumulateVectorLerp`  
`struct FRigVMFunction_AccumulateVectorLerp : public FRigVMFunction_AccumulateBase`  
_L342-386_
- reflection: `USTRUCT(meta = (DisplayName="Accumulate Lerp (Vector)", TemplateName="AccumulateLerp", Keywords="Simulate,Ramp"))`
- inherits: `FRigVMFunction_AccumulateBase`
- desc: Interpolates two vectors over time over and over again
- L346 _public function_ `FRigVMFunction_AccumulateVectorLerp()`
- L354 _public function_ `virtual void Initialize() override`
- L356 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L361 _public member_ `FVector TargetValue;` — `UPROPERTY(meta = (Input))` — The target value to interpolate towards
- L365 _public member_ `FVector InitialValue;` — `UPROPERTY(meta = (Input))` — The initial value to start at
- L370 _public member_ `float Blend;` — `UPROPERTY(meta = (Input))` — The blend to use for the interpolation. This value may be scaled down based on the Integrate Delta Time setting
- L375 _public member_ `bool bIntegrateDeltaTime;` — `UPROPERTY(meta = (Input))` — If True the integration will be relying on the delta time to create more deterministic results with varying framerates.
- L379 _public member_ `FVector Result;` — `UPROPERTY(meta = (Output))` — The resulting accumulated value
- L382 _public member_ `FVector AccumulatedValue;` — `UPROPERTY()`
- L385 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_AccumulateQuatLerp`  
`struct FRigVMFunction_AccumulateQuatLerp : public FRigVMFunction_AccumulateBase`  
_L392-436_
- reflection: `USTRUCT(meta=(DisplayName="Accumulate Lerp (Quaternion)", TemplateName="AccumulateLerp", Keywords="Simulate,Ramp"))`
- inherits: `FRigVMFunction_AccumulateBase`
- desc: Interpolates two quaternions over time over and over again
- L396 _public function_ `FRigVMFunction_AccumulateQuatLerp()`
- L404 _public function_ `virtual void Initialize() override`
- L406 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L411 _public member_ `FQuat TargetValue;` — `UPROPERTY(meta=(Input))` — The target value to interpolate towards
- L415 _public member_ `FQuat InitialValue;` — `UPROPERTY(meta = (Input))` — The initial value to start at
- L420 _public member_ `float Blend;` — `UPROPERTY(meta = (Input))` — The blend to use for the interpolation. This value may be scaled down based on the Integrate Delta Time setting
- L425 _public member_ `bool bIntegrateDeltaTime;` — `UPROPERTY(meta=(Input))` — If True the integration will be relying on the delta time to create more deterministic results with varying framerates.
- L429 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The resulting accumulated value
- L432 _public member_ `FQuat AccumulatedValue;` — `UPROPERTY()`
- L435 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_AccumulateTransformLerp`  
`struct FRigVMFunction_AccumulateTransformLerp : public FRigVMFunction_AccumulateBase`  
_L442-486_
- reflection: `USTRUCT(meta = (DisplayName="Accumulate Lerp (Transform)", TemplateName="AccumulateLerp", Keywords="Simulate,Ramp"))`
- inherits: `FRigVMFunction_AccumulateBase`
- desc: Interpolates two transforms over time over and over again
- L446 _public function_ `FRigVMFunction_AccumulateTransformLerp()`
- L454 _public function_ `virtual void Initialize() override`
- L456 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L461 _public member_ `FTransform TargetValue;` — `UPROPERTY(meta = (Input))` — The target value to interpolate towards
- L465 _public member_ `FTransform InitialValue;` — `UPROPERTY(meta = (Input))` — The initial value to start at
- L470 _public member_ `float Blend;` — `UPROPERTY(meta = (Input))` — The blend to use for the interpolation. This value may be scaled down based on the Integrate Delta Time setting
- L475 _public member_ `bool bIntegrateDeltaTime;` — `UPROPERTY(meta = (Input))` — If True the integration will be relying on the delta time to create more deterministic results with varying framerates.
- L479 _public member_ `FTransform Result;` — `UPROPERTY(meta = (Output))` — The resulting accumulated value
- L482 _public member_ `FTransform AccumulatedValue;` — `UPROPERTY()`
- L485 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_AccumulateFloatRange`  
`struct FRigVMFunction_AccumulateFloatRange : public FRigVMFunction_AccumulateBase`  
_L492-527_
- reflection: `USTRUCT(meta=(DisplayName="Accumulate Range (Float)", TemplateName="AccumulateRange", Keywords="Range"))`
- inherits: `FRigVMFunction_AccumulateBase`
- desc: Accumulates the min and max values over time
- L496 _public function_ `FRigVMFunction_AccumulateFloatRange()`
- L502 _public function_ `virtual void Initialize() override`
- L504 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L509 _public member_ `float Value;` — `UPROPERTY(meta = (Input))` — The value to accumulate the min and max value of
- L513 _public member_ `float Minimum;` — `UPROPERTY(meta= (Output))` — The accumulated minimum value of the input
- L517 _public member_ `float Maximum;` — `UPROPERTY(meta= (Output))` — The accumulated maximum value of the input
- L520 _public member_ `float AccumulatedMinimum;` — `UPROPERTY()`
- L523 _public member_ `float AccumulatedMaximum;` — `UPROPERTY()`
- L526 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_AccumulateVectorRange`  
`struct FRigVMFunction_AccumulateVectorRange : public FRigVMFunction_AccumulateBase`  
_L533-568_
- reflection: `USTRUCT(meta = (DisplayName="Accumulate Range (Vector)", TemplateName="AccumulateRange", Keywords="Range"))`
- inherits: `FRigVMFunction_AccumulateBase`
- desc: Accumulates the min and max values over time
- L537 _public function_ `FRigVMFunction_AccumulateVectorRange()`
- L543 _public function_ `virtual void Initialize() override`
- L545 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L550 _public member_ `FVector Value;` — `UPROPERTY(meta = (Input))` — The value to accumulate the min and max value of
- L554 _public member_ `FVector Minimum;` — `UPROPERTY(meta= (Output))` — The accumulated minimum value of the input (for each component)
- L558 _public member_ `FVector Maximum;` — `UPROPERTY(meta= (Output))` — The accumulated maximum value of the input (for each component)
- L561 _public member_ `FVector AccumulatedMinimum;` — `UPROPERTY()`
- L564 _public member_ `FVector AccumulatedMaximum;` — `UPROPERTY()`
- L567 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Simulation/RigVMFunction_AlphaInterp.h` (Public)


#### struct `FRigVMFunction_AlphaInterp`  
`struct FRigVMFunction_AlphaInterp : public FRigVMFunction_SimBase`  
_L13-93_
- reflection: `USTRUCT(meta=(DisplayName="Alpha Interpolate", Keywords="Alpha,Lerp,LinearInterpolate", Category = "Simulation|Time", TemplateName="AlphaInterp", MenuDescSuffix = "(Float)"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Takes in a float value and outputs an accumulated value with a customized scale and clamp
- L17 _public function_ `FRigVMFunction_AlphaInterp()`
- L34 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L37 _public prototype_ `virtual FString ProcessPinLabelForInjection(const FString& InLabel) const override;`
- L41 _public member_ `float Value;` — `UPROPERTY(meta=(Input))` — The input value to interpolate
- L45 _public member_ `float Scale;` — `UPROPERTY(meta = (Input))` — The scale to apply to the interpolation
- L49 _public member_ `float Bias;` — `UPROPERTY(meta = (Input))` — The bias to use for the interpolation
- L53 _public member_ `bool bMapRange;` — `UPROPERTY(meta=(Input, Constant))` — If True the input value will be mapped using the min and max range
- L57 _public member_ `FInputRange InRange;` — `UPROPERTY(meta=(Input, EditCondition = "bMapRange"))` — The minimum and maximum for the input range
- L61 _public member_ `FInputRange OutRange;` — `UPROPERTY(meta=(Input, EditCondition = "bMapRange"))` — The minimum and maximum for the output range
- L65 _public member_ `bool bClampResult;` — `UPROPERTY(meta = (Input, Constant))` — If True the output value will be clamped by the min and max
- L69 _public member_ `float ClampMin;` — `UPROPERTY(meta=(Input, EditCondition = "bClampResult"))` — The minimum for the output's clamp range
- L73 _public member_ `float ClampMax;` — `UPROPERTY(meta=(Input, EditCondition = "bClampResult"))` — The maximum for the output's clamp range
- L77 _public member_ `bool bInterpResult;` — `UPROPERTY(meta = (Input, Constant))` — If True to the output result will be further intepolated
- L81 _public member_ `float InterpSpeedIncreasing;` — `UPROPERTY(meta=(Input, EditCondition = "bInterpResult"))` — The output interpolation increasing speed
- L85 _public member_ `float InterpSpeedDecreasing;` — `UPROPERTY(meta=(Input, EditCondition = "bInterpResult"))` — The output interpolation decreasing speed
- L89 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting interpolated value
- L92 _public member_ `FInputScaleBiasClamp ScaleBiasClamp;` — `UPROPERTY()`

#### struct `FRigVMFunction_AlphaInterpVector`  
`struct FRigVMFunction_AlphaInterpVector : public FRigVMFunction_SimBase`  
_L99-179_
- reflection: `USTRUCT(meta=(DisplayName="Alpha Interpolate", Keywords="Alpha,Lerp,LinearInterpolate", Category = "Simulation|Time", TemplateName="AlphaInterp", MenuDescSuffix = "(Vector)"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Takes in a vector value and outputs an accumulated value with a customized scale and clamp
- L103 _public function_ `FRigVMFunction_AlphaInterpVector()`
- L120 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L123 _public prototype_ `virtual FString ProcessPinLabelForInjection(const FString& InLabel) const override;`
- L127 _public member_ `FVector Value;` — `UPROPERTY(meta=(Input))` — The input value to interpolate
- L131 _public member_ `float Scale;` — `UPROPERTY(meta = (Input))` — The scale to apply to the interpolation
- L135 _public member_ `float Bias;` — `UPROPERTY(meta = (Input))` — The bias to use for the interpolation
- L139 _public member_ `bool bMapRange;` — `UPROPERTY(meta = (Input, Constant))` — If True the input value will be mapped using the min and max range
- L143 _public member_ `FInputRange InRange;` — `UPROPERTY(meta = (Input, EditCondition = "bMapRange"))` — The minimum and maximum for the input range
- L147 _public member_ `FInputRange OutRange;` — `UPROPERTY(meta = (Input, EditCondition = "bMapRange"))` — The minimum and maximum for the output range
- L151 _public member_ `bool bClampResult;` — `UPROPERTY(meta = (Input, Constant))` — If True the output value will be clamped by the min and max
- L155 _public member_ `float ClampMin;` — `UPROPERTY(meta = (Input, EditCondition = "bClampResult"))` — The minimum for the output's clamp range
- L159 _public member_ `float ClampMax;` — `UPROPERTY(meta = (Input, EditCondition = "bClampResult"))` — The maximum for the output's clamp range
- L163 _public member_ `bool bInterpResult;` — `UPROPERTY(meta = (Input, Constant))` — If True to the output result will be further intepolated
- L167 _public member_ `float InterpSpeedIncreasing;` — `UPROPERTY(meta = (Input, EditCondition = "bInterpResult"))` — The output interpolation increasing speed
- L171 _public member_ `float InterpSpeedDecreasing;` — `UPROPERTY(meta = (Input, EditCondition = "bInterpResult"))` — The output interpolation decreasing speed
- L175 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting interpolated value
- L178 _public member_ `FInputScaleBiasClamp ScaleBiasClamp;` — `UPROPERTY()`

#### struct `FRigVMFunction_AlphaInterpQuat`  
`struct FRigVMFunction_AlphaInterpQuat : public FRigVMFunction_SimBase`  
_L185-265_
- reflection: `USTRUCT(meta=(DisplayName="Alpha Interpolate", Keywords="Alpha,Lerp,LinearInterpolate", Category = "Simulation|Time", TemplateName="AlphaInterp", MenuDescSuffix = "(Quat)"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Takes in a quaternion value and outputs an accumulated value with a customized scale and clamp
- L189 _public function_ `FRigVMFunction_AlphaInterpQuat()`
- L206 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L209 _public prototype_ `virtual FString ProcessPinLabelForInjection(const FString& InLabel) const override;`
- L213 _public member_ `FQuat Value;` — `UPROPERTY(meta=(Input))` — The input value to interpolate
- L217 _public member_ `float Scale;` — `UPROPERTY(meta = (Input))` — The scale to apply to the interpolation
- L221 _public member_ `float Bias;` — `UPROPERTY(meta = (Input))` — The bias to use for the interpolation
- L225 _public member_ `bool bMapRange;` — `UPROPERTY(meta = (Input, Constant))` — If True the input value will be mapped using the min and max range
- L229 _public member_ `FInputRange InRange;` — `UPROPERTY(meta = (Input, EditCondition = "bMapRange"))` — The minimum and maximum for the input range
- L233 _public member_ `FInputRange OutRange;` — `UPROPERTY(meta = (Input, EditCondition = "bMapRange"))` — The minimum and maximum for the output range
- L237 _public member_ `bool bClampResult;` — `UPROPERTY(meta = (Input, Constant))` — If True the output value will be clamped by the min and max
- L241 _public member_ `float ClampMin;` — `UPROPERTY(meta = (Input, EditCondition = "bClampResult"))` — The minimum for the output's clamp range
- L245 _public member_ `float ClampMax;` — `UPROPERTY(meta = (Input, EditCondition = "bClampResult"))` — The maximum for the output's clamp range
- L249 _public member_ `bool bInterpResult;` — `UPROPERTY(meta = (Input, Constant))` — If True to the output result will be further intepolated
- L253 _public member_ `float InterpSpeedIncreasing;` — `UPROPERTY(meta = (Input, EditCondition = "bInterpResult"))` — The output interpolation increasing speed
- L257 _public member_ `float InterpSpeedDecreasing;` — `UPROPERTY(meta = (Input, EditCondition = "bInterpResult"))` — The output interpolation decreasing speed
- L261 _public member_ `FQuat Result;` — `UPROPERTY(meta=(Output))` — The resulting interpolated value
- L264 _public member_ `FInputScaleBiasClamp ScaleBiasClamp;` — `UPROPERTY()`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Simulation/RigVMFunction_DeltaFromPrevious.h` (Public)


#### struct `FRigVMFunction_DeltaFromPreviousFloat`  
`struct FRigVMFunction_DeltaFromPreviousFloat : public FRigVMFunction_SimBase`  
_L14-44_
- reflection: `USTRUCT(meta=(DisplayName="DeltaFromPrevious (Float)", Category = "Simulation|Time", TemplateName="DeltaFromPrevious", Keywords="Difference,Velocity,Acceleration"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Computes the difference from the previous value going through the node
- L18 _public function_ `FRigVMFunction_DeltaFromPreviousFloat()`
- L24 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L29 _public member_ `float Value;` — `UPROPERTY(meta = (Input))` — The input value to compute the delta of
- L33 _public member_ `float Delta;` — `UPROPERTY(meta=(Output))` — The resulting delta from the previous iteration
- L37 _public member_ `float PreviousValue;` — `UPROPERTY(meta=(Output))` — The value from the previous iteration
- L40 _public member_ `float Cache;` — `UPROPERTY()`
- L43 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_DeltaFromPreviousVector`  
`struct FRigVMFunction_DeltaFromPreviousVector : public FRigVMFunction_SimBase`  
_L50-80_
- reflection: `USTRUCT(meta=(DisplayName="DeltaFromPrevious (Vector)", Category = "Simulation|Time", TemplateName="DeltaFromPrevious", Keywords="Difference,Velocity,Acceleration"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Computes the difference from the previous value going through the node
- L54 _public function_ `FRigVMFunction_DeltaFromPreviousVector()`
- L60 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L65 _public member_ `FVector Value;` — `UPROPERTY(meta = (Input))` — The input value to compute the delta of
- L69 _public member_ `FVector Delta;` — `UPROPERTY(meta=(Output))` — The resulting delta from the previous iteration
- L73 _public member_ `FVector PreviousValue;` — `UPROPERTY(meta=(Output))` — The value from the previous iteration
- L76 _public member_ `FVector Cache;` — `UPROPERTY()`
- L79 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_DeltaFromPreviousQuat`  
`struct FRigVMFunction_DeltaFromPreviousQuat : public FRigVMFunction_SimBase`  
_L86-116_
- reflection: `USTRUCT(meta=(DisplayName="DeltaFromPrevious (Quaternion)", Category = "Simulation|Time", TemplateName="DeltaFromPrevious", Keywords="Difference,Velocity,Acceleration"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Computes the difference from the previous value going through the node
- L90 _public function_ `FRigVMFunction_DeltaFromPreviousQuat()`
- L96 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L101 _public member_ `FQuat Value;` — `UPROPERTY(meta = (Input))` — The input value to compute the delta of
- L105 _public member_ `FQuat Delta;` — `UPROPERTY(meta=(Output))` — The resulting delta from the previous iteration
- L109 _public member_ `FQuat PreviousValue;` — `UPROPERTY(meta=(Output))` — The value from the previous iteration
- L112 _public member_ `FQuat Cache;` — `UPROPERTY()`
- L115 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_DeltaFromPreviousTransform`  
`struct FRigVMFunction_DeltaFromPreviousTransform : public FRigVMFunction_SimBase`  
_L122-152_
- reflection: `USTRUCT(meta=(DisplayName="DeltaFromPrevious (Transform)", Category = "Simulation|Time", TemplateName="DeltaFromPrevious", Keywords="Difference,Velocity,Acceleration"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Computes the difference from the previous value going through the node
- L126 _public function_ `FRigVMFunction_DeltaFromPreviousTransform()`
- L132 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L137 _public member_ `FTransform Value;` — `UPROPERTY(meta = (Input))` — The input value to compute the delta of
- L141 _public member_ `FTransform Delta;` — `UPROPERTY(meta=(Output))` — The resulting delta from the previous iteration
- L145 _public member_ `FTransform PreviousValue;` — `UPROPERTY(meta=(Output))` — The value from the previous iteration
- L148 _public member_ `FTransform Cache;` — `UPROPERTY()`
- L151 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Simulation/RigVMFunction_Kalman.h` (Public)


#### struct `FRigVMFunction_KalmanFloat`  
`struct FRigVMFunction_KalmanFloat : public FRigVMFunction_SimBase`  
_L13-46_
- reflection: `USTRUCT(meta=(DisplayName="Average Over Time (Float)", Category = "Simulation|Time", TemplateName="KalmanFilter", Keywords="Average,Smooth,KalmanFilter"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Averages a value over time. This uses a Kalman Filter internally.
- L17 _public function_ `FRigVMFunction_KalmanFloat()`
- L24 _public function_ `virtual void Initialize() override`
- L26 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L31 _public member_ `float Value;` — `UPROPERTY(meta = (Input))` — The value to filter
- L35 _public member_ `int32 BufferSize;` — `UPROPERTY(meta=(Input, Constant))` — The buffer size to use (the higher the more precise)
- L39 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting averaged / filtered value
- L42 _public member_ `TArray<float> Buffer;` — `UPROPERTY(meta=(ArraySize = "FMath::Clamp<int32>(BufferSize, 1, 512)"))`
- L45 _public member_ `int32 LastInsertIndex;` — `UPROPERTY()`

#### struct `FRigVMFunction_KalmanVector`  
`struct FRigVMFunction_KalmanVector : public FRigVMFunction_SimBase`  
_L53-86_
- reflection: `USTRUCT(meta=(DisplayName="Average Over Time (Vector)", Category = "Simulation|Time", TemplateName="KalmanFilter", Keywords="Average,Smooth,KalmanFilter"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Averages a value over time. This uses a Kalman Filter internally.
- L57 _public function_ `FRigVMFunction_KalmanVector()`
- L64 _public function_ `virtual void Initialize() override`
- L66 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L71 _public member_ `FVector Value;` — `UPROPERTY(meta = (Input))` — The value to filter
- L75 _public member_ `int32 BufferSize;` — `UPROPERTY(meta=(Input, Constant))` — The buffer size to use (the higher the more precise)
- L79 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting averaged / filtered value
- L82 _public member_ `TArray<FVector> Buffer;` — `UPROPERTY(meta=(ArraySize = "FMath::Clamp<int32>(BufferSize, 1, 512)"))`
- L85 _public member_ `int32 LastInsertIndex;` — `UPROPERTY()`

#### struct `FRigVMFunction_KalmanTransform`  
`struct FRigVMFunction_KalmanTransform : public FRigVMFunction_SimBase`  
_L93-126_
- reflection: `USTRUCT(meta=(DisplayName="Average Over Time (Transform)", Category = "Simulation|Time", TemplateName="KalmanFilter", Keywords="Average,Smooth,KalmanFilter"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Averages a transform over time. This uses a Kalman Filter internally.
- L97 _public function_ `FRigVMFunction_KalmanTransform()`
- L104 _public function_ `virtual void Initialize() override`
- L106 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L111 _public member_ `FTransform Value;` — `UPROPERTY(meta = (Input))` — The value to filter
- L115 _public member_ `int32 BufferSize;` — `UPROPERTY(meta=(Input, Constant))` — The buffer size to use (the higher the more precise)
- L119 _public member_ `FTransform Result;` — `UPROPERTY(meta=(Output))` — The resulting averaged / filtered value
- L122 _public member_ `TArray<FTransform> Buffer;` — `UPROPERTY(meta = (ArraySize = "FMath::Clamp<int32>(BufferSize, 1, 512)"))`
- L125 _public member_ `int32 LastInsertIndex;` — `UPROPERTY()`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Simulation/RigVMFunction_SimBase.h` (Public)


#### struct `FRigVMFunction_SimBase`  
`struct FRigVMFunction_SimBase : public FRigVMStruct`  
_L12-15_
- reflection: `USTRUCT(meta=(Abstract, Category = "Simulation", NodeColor = "0.25 0.05 0.05", DocumentationPolicy = "Strict"))`
- inherits: `FRigVMStruct`
- desc: The base class for all pure simulation nodes

#### struct `FRigVMFunction_SimBaseMutable`  
`struct FRigVMFunction_SimBaseMutable : public FRigVMStructMutable`  
_L21-24_
- reflection: `USTRUCT(meta=(Abstract, Category = "Simulation", NodeColor = "0.25 0.05 0.05", DocumentationPolicy = "Strict"))`
- inherits: `FRigVMStructMutable`
- desc: The base class for all mutable simulation nodes

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Simulation/RigVMFunction_TimeOffset.h` (Public)


#### struct `FRigVMFunction_TimeOffsetFloat`  
`struct FRigVMFunction_TimeOffsetFloat : public FRigVMFunction_SimBase`  
_L12-62_
- reflection: `USTRUCT(meta=(DisplayName="Value Over Time (Float)", Category = "Simulation|Time", TemplateName="TimeOffset", Keywords="Buffer,Delta,History,Previous,TimeOffset,Delay"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Records a value over time and can access the value from the past
- L16 _public function_ `FRigVMFunction_TimeOffsetFloat()`
- L26 _public function_ `virtual void Initialize() override`
- L28 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L33 _public member_ `float Value;` — `UPROPERTY(meta = (Input))` — The value to record
- L37 _public member_ `float SecondsAgo;` — `UPROPERTY(meta = (Input))` — Seconds of time in the past you want to query the value for
- L41 _public member_ `int32 BufferSize;` — `UPROPERTY(meta=(Input, Constant))` — The sampling precision of the buffer. The higher the more precise - the more memory usage.
- L45 _public member_ `float TimeRange;` — `UPROPERTY(meta=(Input, Constant))` — The maximum time required for offsetting in seconds.
- L49 _public member_ `float Result;` — `UPROPERTY(meta=(Output))` — The resulting offset value
- L52 _public member_ `TArray<float> Buffer;` — `UPROPERTY(meta = (ArraySize = "FMath::Clamp<int32>(BufferSize, 2, 512)"))`
- L55 _public member_ `TArray<float> DeltaTimes;` — `UPROPERTY(meta = (ArraySize = "FMath::Clamp<int32>(BufferSize, 2, 512)"))`
- L58 _public member_ `int32 LastInsertIndex;` — `UPROPERTY()`
- L61 _public member_ `int32 UpperBound;` — `UPROPERTY()`

#### struct `FRigVMFunction_TimeOffsetVector`  
`struct FRigVMFunction_TimeOffsetVector : public FRigVMFunction_SimBase`  
_L68-118_
- reflection: `USTRUCT(meta=(DisplayName="Value Over Time (Vector)", Category = "Simulation|Time", TemplateName="TimeOffset", Keywords="Buffer,Delta,History,Previous,TimeOffset,Delay"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Records a value over time and can access the value from the past
- L72 _public function_ `FRigVMFunction_TimeOffsetVector()`
- L82 _public function_ `virtual void Initialize() override`
- L84 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L89 _public member_ `FVector Value;` — `UPROPERTY(meta = (Input))` — The value to record
- L93 _public member_ `float SecondsAgo;` — `UPROPERTY(meta = (Input))` — Seconds of time in the past you want to query the value for
- L97 _public member_ `int32 BufferSize;` — `UPROPERTY(meta=(Input, Constant))` — The sampling precision of the buffer. The higher the more precise - the more memory usage.
- L101 _public member_ `float TimeRange;` — `UPROPERTY(meta=(Input, Constant))` — The maximum time required for offsetting in seconds.
- L105 _public member_ `FVector Result;` — `UPROPERTY(meta=(Output))` — The resulting offset value
- L108 _public member_ `TArray<FVector> Buffer;` — `UPROPERTY(meta = (ArraySize = "FMath::Clamp<int32>(BufferSize, 2, 512)"))`
- L111 _public member_ `TArray<float> DeltaTimes;` — `UPROPERTY(meta = (ArraySize = "FMath::Clamp<int32>(BufferSize, 2, 512)"))`
- L114 _public member_ `int32 LastInsertIndex;` — `UPROPERTY()`
- L117 _public member_ `int32 UpperBound;` — `UPROPERTY()`

#### struct `FRigVMFunction_TimeOffsetTransform`  
`struct FRigVMFunction_TimeOffsetTransform : public FRigVMFunction_SimBase`  
_L124-174_
- reflection: `USTRUCT(meta=(DisplayName="Value Over Time (Transform)", Category = "Simulation|Time", TemplateName="TimeOffset", Keywords="Buffer,Delta,History,Previous,TimeOffset,Delay"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Records a value over time and can access the value from the past
- L128 _public function_ `FRigVMFunction_TimeOffsetTransform()`
- L138 _public function_ `virtual void Initialize() override`
- L140 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L145 _public member_ `FTransform Value;` — `UPROPERTY(meta = (Input))` — The value to record
- L149 _public member_ `float SecondsAgo;` — `UPROPERTY(meta = (Input))` — Seconds of time in the past you want to query the value for
- L153 _public member_ `int32 BufferSize;` — `UPROPERTY(meta=(Input, Constant))` — The sampling precision of the buffer. The higher the more precise - the more memory usage.
- L157 _public member_ `float TimeRange;` — `UPROPERTY(meta=(Input, Constant))` — The maximum time required for offsetting in seconds.
- L161 _public member_ `FTransform Result;` — `UPROPERTY(meta=(Output))` — The resulting offset value
- L164 _public member_ `TArray<FTransform> Buffer;` — `UPROPERTY(meta = (ArraySize = "FMath::Clamp<int32>(BufferSize, 2, 512)"))`
- L167 _public member_ `TArray<float> DeltaTimes;` — `UPROPERTY(meta = (ArraySize = "FMath::Clamp<int32>(BufferSize, 2, 512)"))`
- L170 _public member_ `int32 LastInsertIndex;` — `UPROPERTY()`
- L173 _public member_ `int32 UpperBound;` — `UPROPERTY()`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Simulation/RigVMFunction_Timeline.h` (Public)


#### struct `FRigVMFunction_TimeBase`  
`struct FRigVMFunction_TimeBase : public FRigVMFunction_SimBase`  
_L12-17_
- reflection: `USTRUCT(meta=(Abstract, Category="Simulation|Time"))`
- inherits: `FRigVMFunction_SimBase`
- desc: The base class for all time nodes
- L16 _public function_ `virtual void Execute()`

#### struct `FRigVMFunction_Timeline`  
`struct FRigVMFunction_Timeline : public FRigVMFunction_TimeBase`  
_L23-52_
- reflection: `USTRUCT(meta=(DisplayName="Accumulated Time", Keywords="Playback,Pause,Timeline"))`
- inherits: `FRigVMFunction_TimeBase`
- desc: Simulates a time value - can act as a timeline playing back
- L27 _public function_ `FRigVMFunction_Timeline()`
- L34 _public function_ `virtual void Initialize() override`
- L36 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L41 _public member_ `float Speed;` — `UPROPERTY(meta = (Input))` — The speed to apply to the played back time
- L45 _public member_ `float Time;` — `UPROPERTY(meta=(Output))` — The played back / accumulated time in seconds
- L48 _public member_ `float AccumulatedValue;` — `UPROPERTY()`
- L51 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_TimeLoop`  
`struct FRigVMFunction_TimeLoop : public FRigVMFunction_TimeBase`  
_L58-120_
- reflection: `USTRUCT(meta=(DisplayName="Time Loop", Keywords="Playback,Pause,Timeline"))`
- inherits: `FRigVMFunction_TimeBase`
- desc: Simulates a time value - and outputs loop information
- L62 _public function_ `FRigVMFunction_TimeLoop()`
- L73 _public function_ `virtual void Initialize() override`
- L75 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L80 _public member_ `float Speed;` — `UPROPERTY(meta = (Input))` — The speed to play-back the time at
- L84 _public member_ `float Duration;` — `UPROPERTY(meta = (Input))` — the duration of a single loop in seconds
- L89 _public member_ `bool Normalize;` — `UPROPERTY(meta = (Input))` — if set to true the output relative and flipflop will be normalized over the duration.
- L93 _public member_ `float Absolute;` — `UPROPERTY(meta=(Output))` — the overall time in seconds
- L97 _public member_ `float Relative;` — `UPROPERTY(meta=(Output))` — the relative time in seconds (within the loop)
- L103 _public member_ `float FlipFlop;` — `UPROPERTY(meta=(Output))` — the relative time in seconds (within the loop), going from 0 to duration and then back from duration to 0, or 0 to 1 and 1 to 0 if Normalize is turned on
- L107 _public member_ `bool Even;` — `UPROPERTY(meta=(Output))` — true if the iteration of the loop is even
- L110 _public member_ `float AccumulatedAbsolute;` — `UPROPERTY()`
- L113 _public member_ `float AccumulatedRelative;` — `UPROPERTY()`
- L116 _public member_ `int32 NumIterations;` — `UPROPERTY()`
- L119 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

#### struct `FRigVMFunction_TimerValue`  
`struct FRigVMFunction_TimerValue : public FRigVMFunction_TimeBase`  
_L126-183_
- reflection: `USTRUCT(meta=(DisplayName="Timer Value", Keywords="Playback,Pause,Timeline"))`
- inherits: `FRigVMFunction_TimeBase`
- desc: Starts a timer and provides access to the time simulation
- L130 _public function_ `FRigVMFunction_TimerValue()`
- L137 _public function_ `virtual void Initialize() override`
- L139 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L144 _public member_ `bool Reset;` — `UPROPERTY(meta = (Input))` — A flag to reset / restart the timer
- L148 _public member_ `float Speed;` — `UPROPERTY(meta = (Input))` — The speed to apply to the played back time
- L152 _public member_ `float Duration;` — `UPROPERTY(meta = (Input))` — The duration in seconds the timer will take to complete
- L156 _public member_ `bool Repeats;` — `UPROPERTY(meta = (Input))` — A flag indicating if the timer is a one-shot or if it should repeat / loop
- L160 _public member_ `bool JustStarted;` — `UPROPERTY(meta=(Output))` — True if the timer has just started
- L164 _public member_ `bool IsRunning;` — `UPROPERTY(meta=(Output))` — True if the timer is running
- L168 _public member_ `bool JustFinished;` — `UPROPERTY(meta=(Output))` — True if the timer has just finished
- L172 _public member_ `float Time;` — `UPROPERTY(meta=(Output))` — The played back / accumulated time in seconds
- L176 _public member_ `float Ratio;` — `UPROPERTY(meta=(Output))` — The played back / accumulated time as a ratio of time / duration (0.0 - 1.0)
- L179 _public member_ `float AccumulatedValue;` — `UPROPERTY()`
- L182 _public member_ `bool bIsInitialized;` — `UPROPERTY()`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMFunctions/Simulation/RigVMFunction_Verlet.h` (Public)


#### struct `FRigVMFunction_VerletIntegrateVector`  
`struct FRigVMFunction_VerletIntegrateVector : public FRigVMFunction_SimBase`  
_L14-68_
- reflection: `USTRUCT(meta=(DisplayName="Verlet (Vector)", Category = "Simulation|Springs", TemplateName="Verlet", Keywords="Simulate,Integrate"))`
- inherits: `FRigVMFunction_SimBase`
- desc: Simulates a single position over time using Verlet integration. It is recommended to use SpringInterp instead as it is more accurate and stable, and has more meaningful parameters.
- L18 _public function_ `FRigVMFunction_VerletIntegrateVector()`
- L28 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L33 _public member_ `FVector Target;` — `UPROPERTY(meta = (Input))` — The target value to interpolate / integrate towards
- L37 _public member_ `float Strength;` — `UPROPERTY(meta = (Input))` — The strength of the verlet spring
- L41 _public member_ `float Damp;` — `UPROPERTY(meta = (Input))` — The amount of damping to apply ( 0.0 to 1.0, but usually really low like 0.005 )
- L45 _public member_ `float Blend;` — `UPROPERTY(meta = (Input))` — The amount of blending to apply per second
- L49 _public member_ `FVector Force;` — `UPROPERTY(meta = (Input))` — The force feeding into the solver. Can be used for gravity.
- L53 _public member_ `FVector Position;` — `UPROPERTY(meta = (Output))` — The resulting simulated position
- L57 _public member_ `FVector Velocity;` — `UPROPERTY(meta = (Output))` — The resulting simulated velocity
- L61 _public member_ `FVector Acceleration;` — `UPROPERTY(meta = (Output))` — The resulting simulated acceleration
- L64 _public member_ `FRigVMSimPoint Point;` — `UPROPERTY(transient)`
- L67 _public member_ `bool bInitialized;` — `UPROPERTY(transient)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMHost.h` (Public)


#### struct `FRigVMUserDefinedTypesInfo`  
`struct FRigVMUserDefinedTypesInfo`  
_L33-43_
- reflection: `USTRUCT()`
- L38 _public member_ `TMap<FString, FSoftObjectPath> StructGuidToPathName;` — `UPROPERTY()`
- L40 _public member_ `TMap<FString, FSoftObjectPath> EnumToPathName;` — `UPROPERTY()`
- L42 _public member_ `TSet<TObjectPtr<UObject>> TypesInUse;` — `UPROPERTY(transient)`

#### class `URigVMHost`  
`class URigVMHost : public UObject, public IInterface_AssetUserData`  
_L46-705_
- reflection: `UCLASS(Abstract, editinlinenew, MinimalAPI)`
- inherits: `UObject,IInterface_AssetUserData`
- L53 _public prototype_ `static TArray<URigVMHost*> FindRigVMHosts(UObject* Outer, TSubclassOf<URigVMHost> OptionalClass);` — `UFUNCTION(BlueprintCallable, Category = RigVM)`
- L55 _public prototype_ `static bool IsGarbageOrDestroyed(const UObject* InObject);`
- L58 _public prototype_ `virtual UWorld* GetWorld() const override;` — UObject interface
- L59 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L60 _public prototype_ `virtual void PostLoad() override;`
- L61 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L62 _public prototype_ `virtual void BeginDestroy() override;`
- L63 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L65 _public prototype_ `virtual void PostEditImport() override;`
- L70 _public function_ `float GetAbsoluteTime() const` — `UFUNCTION(BlueprintPure, Category = "RigVM")` — Gets the current absolute time
- L74 _public function_ `float GetDeltaTime() const` — `UFUNCTION(BlueprintPure, Category = "RigVM")` — Gets the current delta time
- L78 _public prototype_ `void SetDeltaTime(float InDeltaTime);` — `UFUNCTION(BlueprintCallable, Category="RigVM")` — Set the current delta time
- L82 _public prototype_ `void SetAbsoluteTime(float InAbsoluteTime, bool InSetDeltaTimeZero = false);` — `UFUNCTION(BlueprintCallable, Category = "RigVM")` — Set the current absolute time
- L86 _public prototype_ `void SetAbsoluteAndDeltaTime(float InAbsoluteTime, float InDeltaTime);` — `UFUNCTION(BlueprintCallable, Category = "RigVM")` — Set the current absolute and delta times
- L90 _public prototype_ `void SetFramesPerSecond(float InFramesPerSecond);` — `UFUNCTION(BlueprintCallable, Category = "RigVM")` — Set the current fps
- L94 _public prototype_ `float GetCurrentFramesPerSecond() const;` — `UFUNCTION(BlueprintPure, Category = "RigVM")` — Returns the current frames per second (this may change over time)
- L97 _public function_ `virtual UScriptStruct* GetPublicContextStruct() const` — Returns the public context script struct to use for this owner
- L101 _public prototype_ `virtual bool CanExecute() const;` — `UFUNCTION(BlueprintPure, Category="RigVM")` — Is valid for execution
- L104 _public prototype_ `virtual void Initialize(bool bRequestInit = true);` — Initialize things for the RigVM owner
- L107 _public prototype_ `virtual bool InitializeVM(const FName& InEventName);` — Initialize this Host VM Instance
- L110 _public prototype_ `virtual void Evaluate_AnyThread();` — Evaluate at Any Thread
- L113 _public function_ `FTransactionallySafeCriticalSection& GetEvaluateMutex()` — Locks for the scope of Evaluate_AnyThread
- L116 _public function_ `FTransactionallySafeCriticalSection& GetEventQueueToRunOnceMutex() const` — Lock for editing the event queue to run once
- L121 _public prototype_ `virtual bool IsReadOnly() const;` — Returns true if this host is read only - so if it's not support to be mutated / changed
- L127 _public prototype_ `virtual bool IsPlayingRewindDebugTrace() const;` — Returns true if this host is currently playing back a rewind debugger trace
- L132 _public prototype_ `virtual void StartPlayingRewindDebugTrace();` — Starts a potentially connected rewind debug trace for playback
- L137 _public prototype_ `virtual void StopPlayingRewindDebugTrace();` — Stops a potentially connected rewind debug trace from playing back
- L144 _public prototype_ `virtual UObject* GetBoundOuterForTrace() const;` — Returns the bound outer this host is nested under.
- L147 _public prototype_ `TArray<FRigVMExternalVariable> GetExternalVariables() const;` — Returns the member properties as an external variable array
- L150 _public prototype_ `TArray<FRigVMExternalVariable> GetPublicVariables() const;` — Returns the public member properties as an external variable array
- L153 _public prototype_ `UStruct* GetVariablesStruct() const;` — The struct where the variable properties are defined (for the BP-based host, this would be GetClass, for the BP-independent, it would be the property bag struct)
- L156 _public prototype_ `uint8* GetVariablesMemory();` — The memory where the variables are stored (for the BP-based host, the memory is this, for the BP-independent, it would be the raw ptr of the property bag)
- L159 _public prototype_ `FRigVMExternalVariable GetVariableByName(const FName& InVariableName) const;` — Returns a variable given its name
- L162 _public prototype_ `FRigVMExternalVariable GetPublicVariableByName(const FName& InVariableName) const;` — Returns a public variable given its name
- L166 _public prototype_ `TArray<FName> GetScriptAccessibleVariables() const;` — `UFUNCTION(BlueprintPure, Category = "RigVM", meta=(DisplayName="Get Variables"))` — Returns the names of variables accessible in scripting
- L170 _public prototype_ `FName GetVariableType(const FName& InVariableName) const;` — `UFUNCTION(BlueprintPure, Category = "RigVM")` — Returns the type of a given variable
- L174 _public prototype_ `FString GetVariableAsString(const FName& InVariableName) const;` — `UFUNCTION(BlueprintPure, Category = "RigVM")` — Returns the value of a given variable as a string
- L178 _public prototype_ `bool SetVariableFromString(const FName& InVariableName, const FString& InValue);` — `UFUNCTION(BlueprintCallable, Category = "RigVM")` — Returns the value of a given variable as a string
- L181 _public function_ `template<class T> T GetPublicVariableValue(const FName& InVariableName)`
- L192 _public function_ `template<class T> void SetPublicVariableValue(const FName& InVariableName, const T& InValue)`
- L201 _public function_ `virtual FString GetName() const`
- L209 _public member_ `FRigVMRuntimeSettings VMRuntimeSettings;` — `UPROPERTY()`
- L211 _public prototype_ `virtual void InvalidateCachedMemory();`
- L214 _public prototype_ `virtual void RecreateCachedMemory();` — Regenerates cached handles after a structural change (i.e. new UUserStruct)
- L218 _public prototype_ `virtual bool Execute(const FName& InEventName);` — `UFUNCTION(BlueprintCallable, Category = "RigVM")` — Execute
- L223 _public prototype_ `DECLARE_EVENT_OneParam(URigVMHost, FOnEndLoadPackage, URigVMHost*);` — Bindable event for external objects to be notified that a RigVMHost is fully end-loaded
- L227 _public function_ `void BroadCastEndLoadPackage()` — these are needed so that sequencer can have a chance to update its RigVMHost instances after the package is fully end-loaded
- L228 _public function_ `FOnEndLoadPackage& OnEndLoadPackage()`
- L231 _private member_ `FOnEndLoadPackage EndLoadPackageEvent;`
- L238 _protected prototype_ `virtual bool InitializeCDOVM();` — Initialize the CDO VM
- L241 _protected prototype_ `virtual bool Execute_Internal(const FName& InEventName);` — ExecuteUnits
- L243 _protected prototype_ `static bool DisableExecution();`
- L246 _protected prototype_ `virtual void TraceConstantData(FRigVMTraceArchiveWriter& InArchive) const;`
- L248 _public prototype_ `virtual bool MatchesTracedConstantData(FRigVMTraceArchiveReader& InArchive) const;`
- L250 _protected prototype_ `virtual void LoadTracedConstantData(FRigVMTraceArchiveReader& InArchive);`
- L251 _protected prototype_ `virtual void TraceExecuteData(FRigVMTraceArchiveWriter& InArchive) const;`
- L252 _protected prototype_ `virtual void LoadTracedExecuteData(FRigVMTraceArchiveReader& InArchive);`
- L258 _public function_ `template<class T> bool SupportsEvent() const`
- L264 _public prototype_ `virtual bool SupportsEvent(const FName& InEventName) const;` — `UFUNCTION(BlueprintPure, Category = "RigVM")`
- L267 _public prototype_ `virtual const TArray<FName>& GetSupportedEvents() const;` — `UFUNCTION(BlueprintPure, Category = "RigVM")`
- L271 _public prototype_ `bool ExecuteEvent(const FName& InEventName);` — `UFUNCTION(BlueprintCallable, Category = "RigVM")` — Execute a user defined event
- L275 _public prototype_ `virtual void RequestInit();` — `UFUNCTION(BlueprintCallable, Category = "RigVM")` — Requests to perform an init during the next execution
- L279 _public function_ `virtual bool IsInitRequired() const` — `UFUNCTION(BlueprintPure, Category = "RigVM")` — Returns true if this host requires the VM memory to be initialized
- L289 _public prototype_ `virtual void RequestRunOnceEvent(const FName& InEventName, int32 InEventIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = "RigVM")` — Requests to run an event once @param InEventName The event to run @param InEventIndex Deprecated argument. Not used.
- L293 _public prototype_ `bool RemoveRunOnceEvent(const FName& InEventName);` — `UFUNCTION(BlueprintCallable, Category = "RigVM")` — Removes an event running once
- L296 _public prototype_ `bool IsRunOnceEvent(const FName& InEventName) const;` — Returns true if an event is queued to run once
- L299 _public function_ `const TArray<FName>& GetEventQueue() const` — Returns the queue of events to run
- L302 _public prototype_ `void SetEventQueue(const TArray<FName>& InEventNames);` — Sets the queue of events to run
- L305 _public function_ `virtual void AdaptEventQueueForEvaluate(TArray<FName>& InOutEventQueueToRun)` — Provides the chance to a subclass to modify the event queue as needed
- L308 _public prototype_ `void UpdateVMSettings();` — Update the settings such as array bound and log facilities
- L311 _public prototype_ `URigVM* GetVM();` — `UFUNCTION(BlueprintPure, Category = "RigVM")`
- L315 _public function_ `const FRigVMLog* GetLog() const`
- L316 _public function_ `FRigVMLog* GetLog()`
- L317 _public function_ `void SetLog(FRigVMLog* InLog)`
- L321 _public prototype_ `virtual const FRigVMMemoryStorageStruct* GetDefaultMemoryByType(ERigVMMemoryType InMemoryType) const;` — Returns the compiler generated VM memory storage by type
- L324 _public prototype_ `virtual FRigVMMemoryStorageStruct* GetMemoryByType(ERigVMMemoryType InMemoryType);` — Returns an instanced VM memory storage by type
- L325 _public prototype_ `virtual const FRigVMMemoryStorageStruct* GetMemoryByType(ERigVMMemoryType InMemoryType) const;`
- L328 _public function_ `FRigVMMemoryStorageStruct* GetWorkMemory()` — The instanced mutable work memory
- L329 _public function_ `const FRigVMMemoryStorageStruct* GetWorkMemory() const`
- L332 _public function_ `FRigVMMemoryStorageStruct* GetLiteralMemory()` — The default const literal memory
- L333 _public function_ `const FRigVMMemoryStorageStruct* GetLiteralMemory() const`
- L336 _public prototype_ `FRigVMMemoryStorageStruct* GetDebugMemory(bool bCreateIfRequired = false);` — The instanced debug watch memory
- L337 _public function_ `const FRigVMMemoryStorageStruct* GetDebugMemory() const`
- L339 _public prototype_ `DECLARE_EVENT_TwoParams(URigVM, FRigVMExecutedEvent, class URigVMHost*, const FName&);`
- L340 _public function_ `FRigVMExecutedEvent& OnInitialized_AnyThread()`
- L341 _public function_ `FRigVMExecutedEvent& OnExecuted_AnyThread()`
- L342 _public function_ `FRigVMExecutedEvent& OnPreExecuted_AnyThread()`
- L349 _public prototype_ `DECLARE_EVENT_TwoParams(URigVMHost, FRigVMHostEarlyExitEvent, class URigVMHost*, EEarlyExitReason);`
- L350 _public function_ `FRigVMHostEarlyExitEvent& OnEarlyExit_AnyThread()`
- L352 _public function_ `const FRigVMDrawInterface& GetDrawInterface() const`
- L353 _public function_ `FRigVMDrawInterface& GetDrawInterface()`
- L355 _public function_ `const FRigVMDrawContainer& GetDrawContainer() const`
- L356 _public function_ `FRigVMDrawContainer& GetDrawContainer()`
- L358 _public prototype_ `void DrawIntoPDI(FPrimitiveDrawInterface* PDI, const FTransform& InTransform);`
- L359 _public prototype_ `void DrawIntoCanvas(class FCanvas* Canvas, const class FSceneView* View, const FTransform& InTransform);`
- L361 _public prototype_ `virtual USceneComponent* GetOwningSceneComponent();`
- L363 _public prototype_ `virtual void PostInitInstanceIfRequired();`
- L364 _public prototype_ `void SwapVMToNativizedIfRequired(UClass* InNativizedClass = nullptr);`
- L365 _public prototype_ `bool AreNativizedVMsEnabled() const;`
- L366 _public prototype_ `bool CanSwapVMToNativized() const;`
- L369 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L373 _public member_ `bool bDebugExecutionEnabled = false;`
- L374 _public prototype_ `const FString GetDebugExecutionString();`
- L380 _public function_ `virtual FRigVMExtendedExecuteContext& GetExtendedExecuteContext()` — `UE_DEPRECATED(5.4, "Please, use GetRigVMExtendedExecuteContext")` — `UFUNCTION(BlueprintCallable, Category = RigVM, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and it is no longer supported."))` — Provide access to the ExtendedExecuteContext
- L386 _public prototype_ `void SetRigVMExtendedExecuteContext(FRigVMExtendedExecuteContext* InRigVMExtendedExecuteContext);`
- L388 _public function_ `inline FRigVMExtendedExecuteContext& GetRigVMExtendedExecuteContext()`
- L393 _public function_ `inline const FRigVMExtendedExecuteContext& GetRigVMExtendedExecuteContext() const`
- L399 _public prototype_ `UObject* ResolveUserDefinedTypeById(const FString& InTypeName) const;`
- L401 _public prototype_ `const TArray<FString>& GetRequiredPlugins() const;`
- L403 _public function_ `TScriptInterface<IRigVMRuntimeAssetInterface> GetGeneratedByAsset() const`
- L406 _public prototype_ `void EnableNativizedVM(bool bEnable = true);`
- L411 _protected prototype_ `virtual void PostInitInstance(URigVMHost* InCDO);`
- L412 _protected prototype_ `virtual void PostInitProperties() override;`
- L414 _protected prototype_ `URigVM* GetSourceVM() const;`
- L417 _protected member_ `float DeltaTime;` — Current delta time
- L420 _protected member_ `float AbsoluteTime;` — Current delta time
- L423 _protected member_ `float FramesPerSecond;` — Current delta time
- L426 _protected member_ `bool bAccumulateTime;` — true if we should increase the AbsoluteTime
- L430 _protected member_ `bool bIsBeingDebugged;` — true if the instance is being debugged in an asset editor
- L433 _protected member_ `bool bEnableNativizedVMs;` — true if this instance is allowed to use nativized VMs
- L436 _protected member_ `mutable TOptional<uint32> LastNativizedVMHash;`
- L437 _protected member_ `mutable TOptional<TWeakObjectPtr<UClass>> WeakNativizedVMClass;`
- L441 _protected member_ `bool bIsPlayingRewindDebugTrace;` — true if this instance is playing back a rewind debug trace
- L445 _protected member_ `TObjectPtr<URigVM> VM;` — `UPROPERTY(Transient)`
- L448 _protected member_ `FRigVMPropertyBag Variables;` — `UPROPERTY()`
- L451 _protected member_ `TScriptInterface<IRigVMRuntimeAssetInterface> GeneratedBy;` — `UPROPERTY()`
- L454 _protected member_ `FRigVMLog* RigVMLog;`
- L455 _protected member_ `bool bEnableLogging;`
- L458 _protected prototype_ `void GenerateUserDefinedDependenciesData(FRigVMExtendedExecuteContext& Context);`
- L459 _protected prototype_ `TArray<const UObject*> GetUserDefinedDependencies(const TArray<const FRigVMMemoryStorageStruct*> InMemory);`
- L460 _protected prototype_ `virtual void GenerateRequiredPluginsData(FRigVMExtendedExecuteContext& Context);`
- L463 _protected member_ `TMap<FString, FSoftObjectPath> UserDefinedStructGuidToPathName;` — `UPROPERTY()`
- L465 _protected member_ `TMap<FString, FSoftObjectPath> UserDefinedEnumToPathName;` — `UPROPERTY()`
- L467 _protected member_ `TArray<FString> RequiredPlugins;` — `UPROPERTY()`
- L471 _private member_ `TSet<TObjectPtr<UObject>> UserDefinedTypesInUse;` — `UPROPERTY(transient)`
- L475 _private member_ `FRigVMExtendedExecuteContext ExtendedExecuteContext_DEPRECATED;` — `UPROPERTY()`
- L478 _private member_ `FRigVMExtendedExecuteContext* RigVMExtendedExecuteContext = nullptr;`
- L482 _protected prototype_ `void HandleExecutionReachedExit(const FName& InEventName);`
- L484 _protected prototype_ `virtual TArray<FRigVMExternalVariable> GetExternalVariablesImpl(bool bFallbackToBlueprint) const;`
- L486 _protected function_ `FProperty* GetVariableProperty(const FName& InVariableName) const`
- L500 _protected function_ `FProperty* GetPublicVariableProperty(const FName& InVariableName) const`
- L516 _protected function_ `FGuid GetVariableGuid(const FName& InVariableName) const`
- L533 _public member_ `FRigVMDrawContainer DrawContainer;` — `UPROPERTY()`
- L537 _public member_ `FRigVMDrawInterface DrawInterface;` — `UPROPERTY(transient)` — The draw interface for the units to use
- L541 _public member_ `TArray<FName> EventQueue;` — `UPROPERTY(transient)` — The event name used during an update
- L542 _public member_ `TArray<FName> EventQueueToRun;`
- L543 _public member_ `TArray<FName> EventsToRunOnce;`
- L546 _public function_ `bool IsEvaluating() const` — Returns true if Evaluate_AnyThread is currently executing
- L549 _public function_ `bool HasEvaluationsLeft() const` — Returns true if this host can run at least once
- L558 _public function_ `int32 GetEvaluationsLeft() const` — Returns the number of evaluations left for this host or INDEX_NONE if the host can run indefinitely.
- L564 _public function_ `void SetEvaluationsLeft(int32 InEvaluationsLeft)` — Request to limit this hosts number of evaluations
- L570 _public function_ `void ResetEvaluationsLeft()` — Reset the number of evaluations left and allow this host to run indefinitely
- L576 _public prototype_ `void InstantiateVMFromCDO();` — Copy the VM from the default object
- L579 _public prototype_ `void CopyExternalVariableDefaultValuesFromCDO();` — Copy the default values of external variables from the default object
- L582 _public member_ `FRigVMExecutedEvent InitializedEvent;` — Broadcasts a notification whenever the RigVMHost's memory is initialized.
- L585 _public member_ `FRigVMExecutedEvent ExecutedEvent;` — Broadcasts a notification whenever the RigVMHost is executed / updated.
- L588 _public member_ `FRigVMExecutedEvent PreExecutedEvent;` — Broadcasts a notification before the RigVMHost is executed / updated.
- L591 _public member_ `FRigVMHostEarlyExitEvent EarlyExitEvent;` — Broadcasts when the host cannot execute and needs to early exit during an evaluation
- L595 _protected prototype_ `virtual void InitializeFromCDO();`
- L597 _protected prototype_ `virtual void CopyVMMemory(FRigVMExtendedExecuteContext& TargetContext, const FRigVMExtendedExecuteContext& SourceContext);`
- L601 _public prototype_ `virtual void AddAssetUserData(UAssetUserData* InUserData) override;`
- L602 _public prototype_ `virtual void RemoveUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L603 _public prototype_ `virtual UAssetUserData* GetAssetUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L604 _public prototype_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override;`
- L610 _protected member_ `TArray<TObjectPtr<UAssetUserData>> AssetUserData;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Instanced, Category = "Default")` — Array of user data stored with the asset
- L615 _protected member_ `TArray<TObjectPtr<UAssetUserData>> AssetUserDataEditorOnly;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Instanced, Category = "Default")` — Array of user data stored with the asset
- L621 _protected member_ `int32 EvaluationsLeft;` — the number of evaluations left. INDEX_NONE represents unlimited
- L623 _protected member_ `bool bRequiresInitExecution;`
- L625 _protected member_ `int32 InitBracket;`
- L626 _protected member_ `int32 ExecuteBracket;`
- L628 _protected member_ `TWeakObjectPtr<USceneComponent> OuterSceneComponent;`
- L630 _protected function_ `bool IsInitializing() const`
- L635 _protected function_ `bool IsExecuting() const`
- L646 _private member_ `bool bIsInDebugMode;` — `UPROPERTY(transient)` — The current execution mode
- L654 _protected member_ `FRigVMInstructionVisitInfo InstructionVisitInfo;`
- L655 _protected member_ `TSharedRef<FRigVMDebugInfo> DebugInfo;`
- L656 _protected member_ `FRigVMProfilingInfo ProfilingInfo;`
- L657 _protected member_ `TMap<FString, bool> LoggedMessages;`
- L658 _protected prototype_ `void LogOnce(EMessageSeverity::Type InSeverity, int32 InInstructionIndex, const FString& InMessage);`
- L662 _public function_ `void SetIsInDebugMode(const bool bValue)`
- L663 _public function_ `bool IsInDebugMode() const`
- L664 _public function_ `bool IsProfilingEnabled() const`
- L669 _public function_ `const FRigVMOperand* GetDebugOperandForOperand(const FRigVMOperand& InOperand) const`
- L674 _public function_ `FRigVMDebugInfo& GetDebugInfo()`
- L675 _public function_ `const FRigVMDebugInfo& GetDebugInfo() const`
- L677 _public function_ `FRigVMProfilingInfo& GetProfilingInfo()`
- L678 _public function_ `const FRigVMProfilingInfo& GetProfilingInfo() const`
- L684 _private member_ `FTransactionallySafeCriticalSection EvaluateMutex;`
- L685 _private member_ `mutable FTransactionallySafeCriticalSection EventQueueToRunOnceMutex;`
- L690 _protected member_ `int32 ProfilingRunsLeft;`
- L691 _protected member_ `uint64 AccumulatedCycles;`

#### enum `URigVMHost::EEarlyExitReason`  
`enum EEarlyExitReason`  
_L344-347_
- L346 _public enumerator_ `EEarlyExitReason_NoEvaluationsLeft`

#### class `FRigVMBracketScope`  
`class FRigVMBracketScope`  
_L707-725_
- L711 _public function_ `FRigVMBracketScope(int32& InBracket) : Bracket(InBracket)`
- L717 _public function_ `~FRigVMBracketScope()`
- L724 _private member_ `int32& Bracket;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API RIGVM_API`
- L27 _macro_ `#define UE_RIGVM_PROFILE_EXECUTE_UNITS_NUM 0`
- L223 _delegate_ `DECLARE_EVENT_OneParam(URigVMHost, FOnEndLoadPackage, URigVMHost*);` — Bindable event for external objects to be notified that a RigVMHost is fully end-loaded
- L339 _delegate_ `DECLARE_EVENT_TwoParams(URigVM, FRigVMExecutedEvent, class URigVMHost*, const FName&);`
- L349 _delegate_ `DECLARE_EVENT_TwoParams(URigVMHost, FRigVMHostEarlyExitEvent, class URigVMHost*, EEarlyExitReason);`
- L520 _function_ `` (scope `URigVMHost::GetVariableGuid`)

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMModule.h` (Public)


#### class `FRigVMModule`  
`class FRigVMModule : public IModuleInterface`  
_L22-33_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _private member_ `FRigVMTrace RewindDebuggerRigVMExtension;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API RIGVM_API`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigVM, Log, All);`
- L35 _namespace_ `namespace RigVMCore`
- L37 _prototype_ `bool SupportsUObjects();` (scope `RigVMCore`)
- L38 _prototype_ `bool SupportsUInterfaces();` (scope `RigVMCore`)

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMObjectVersion.h` (Public)


#### struct `FRigVMObjectVersion`  
`struct FRigVMObjectVersion`  
_L10-103_
- desc: Custom serialization version for changes made in Dev-Anim stream
- L99 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L102 _private function_ `FRigVMObjectVersion()`

#### enum `FRigVMObjectVersion::Type`  
`enum Type`  
_L12-96_
- L15 _public enumerator_ `BeforeCustomVersionWasAdded` — Before any version changes were made
- L18 _public enumerator_ `AddedVMHashChecks` — ControlRig & RigVMHost compute and checks VM Hash
- L21 _public enumerator_ `PredicatesAddedToExecuteOps` — Predicates added to execute operations
- L24 _public enumerator_ `VMStoringUserDefinedStructMap` — Storing paths to user defined structs map
- L27 _public enumerator_ `VMStoringUserDefinedEnumMap` — Storing paths to user defined enums map
- L30 _public enumerator_ `HostStoringUserDefinedData` — Storing paths to user defined enums map
- L33 _public enumerator_ `VMMemoryStorageStructSerialized` — VM Memory Storage Struct serialized
- L36 _public enumerator_ `VMMemoryStorageDefaultsGeneratedAtVM` — VM Memory Storage Defaults generated at VM
- L39 _public enumerator_ `VMBytecodeStorePublicContextPath` — VM Bytecode Stores the Public Context Path
- L42 _public enumerator_ `VMRemoveTooltipFromFunctionHeader` — Removing unused tooltip property from frunction header
- L45 _public enumerator_ `RemoveLibraryNodeReferenceFromFunctionIdentifier` — Removing library node FSoftObjectPath from FRigVMGraphFunctionIdentifier
- L48 _public enumerator_ `AddVariantToFunctionIdentifier` — Adding variant struct to function identifier
- L51 _public enumerator_ `AddVariantToRigVMAssets` — Adding variant to every RigVM asset
- L54 _public enumerator_ `FunctionHeaderStoresLayout` — Storing user interface layout within function header
- L57 _public enumerator_ `FunctionHeaderLayoutStoresPinIndexInCategory` — Storing user interface relevant pin index in category
- L60 _public enumerator_ `FunctionHeaderLayoutStoresCategoryExpansion` — Storing user interface relevant category expansion
- L63 _public enumerator_ `RigVMSaveSerializedGraphInGraphFunctionDataAsByteArray` — Storing function graph collapse node content as part of the header
- L66 _public enumerator_ `VMBytecodeStorePublicContextPathAsTopLevelAssetPath` — VM Bytecode Stores the Public Context Path as a FTopLevelAssetPath
- L70 _public enumerator_ `ByteCodeCleanup` — Serialized instruction offsets are now int32 rather than uint16, NumBytes has been removed from RigVMCopyOp
- L73 _public enumerator_ `LocalizedRegistry` — The VM stores a local snapshot registry to use in cooked environments instead of the shared global registry
- L76 _public enumerator_ `LocalizedRegistryWithRelativeSeekOffset` — The VM stores a relative seek offset to be able to skip the registry during load
- L79 _public enumerator_ `FunctionArgumentCanRepresentInputVariable` — Function arguments can now represent an input variable (an external variable passed into a function)
- L82 _public enumerator_ `ObjectArchiveVersionContainerSerialization` — Object archive is now storing the version container
- L85 _public enumerator_ `DebugOperandMappingSimplified` — Debug operand mapping simplified and moved to context only
- L88 _public enumerator_ `RigVMCallables` — Introduction of callables to the rigvm bytecode
- L91 _public enumerator_ `GuidForVariables` — Referencing variables through Guids
- L94 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L95 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### enum `ERigVMCookVersion::Type`  
`enum Type : int`  
_L108-116_
- L113 _public enumerator_ `AlwaysSerializeLocalizedRegistry` — even when the localized registry is turned off, make sure to always serialize it so that we can decide in code if we want to utilize it.
- L115 _public enumerator_ `LatestVersion`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API RIGVM_API`
- L106 _namespace_ `namespace ERigVMCookVersion`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMPropertyUtils.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace RigVMPropertyUtils`
- L22 _prototype_ `void GetTypeFromProperty(const FProperty* InProperty, FName& OutTypeName, UObject*& OutTypeObject);` (scope `RigVMPropertyUtils`) — Given a property, return the C++ type name for it and the associated type object. If the type is an unambiguous simple type, such as a bool or an int, the OutTypeObject value will be nullptr. If the property represents a ambiguous type, like an object pointer, interface or an enum, then the OutTypeObject will be the class of the pointed to object, or the enum definition. For container properties, the type object is always the contained type, rather than the type of the container. \param InProperty The property to get the type for. \param OutTypeName The C++ type name. \param OutTypeObject The object class, if the property type is complex or ambiguous.
- L34 _prototype_ `uint32 GetPropertyHashFast(const FProperty* InProperty, const uint8* InMemory, EPropertyPointerType InContainerType = EPropertyPointerType::Container);` (scope `RigVMPropertyUtils`) — Given a property and a value storage for it, return a 32-bit hash value for the underlying value of tha type. \note The resulting hash is not suitable for serialization, since the underlying hash combine function is not guaranteed to be stable between releases. \param InProperty The property to get a hash value for. \param InMemory The underlying memory that the property is defined for. \param InContainerType The type of memory being pointed at. For UObjects, use EPropertyPointerType::Container. If pointing directly at the value location in memory, use EPropertyPointerType::Direct. \return The hash value of the value of the property at the memory location the property lives at.
- L46 _prototype_ `uint32 GetPropertyHashStable(const FProperty* InProperty, const uint8* InMemory, EPropertyPointerType InContainerType = EPropertyPointerType::Container);` (scope `RigVMPropertyUtils`) — Given a property and a value storage for it, return a 32-bit hash value for the underlying value of tha type. \note This hash is suitable for serialization, since the underlying hash combine function is guaranteed to be stable between releases. \param InProperty The property to get a hash value for. \param InMemory The underlying UObject memory that the property is defined for. \param InContainerType The type of memory being pointed at. For UObjects, use EPropertyPointerType::Container. If pointing directly at the value location in memory, use EPropertyPointerType::Direct. \return The hash value of the value of the property at the memory location the property lives at.

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMRuntimeAsset.h` (Public)


#### enum `ERigVMAssetStatus`  
`enum ERigVMAssetStatus : int`  
_L25-40_
- reflection: `UENUM()`
- desc: Enumerates states a RigVMAsset can be in. Copied from EBlueprintStatus.
- L28 _public enumerator_ `RVMA_Unknown` — Asset is in an unknown state.
- L30 _public enumerator_ `RVMA_Dirty` — Asset has been modified but not recompiled.
- L32 _public enumerator_ `RVMA_Error` — Asset tried but failed to be compiled.
- L34 _public enumerator_ `RVMA_UpToDate` — Asset has been compiled since it was last modified.
- L36 _public enumerator_ `RVMA_BeingCreated` — Asset is in the process of being created for the first time.
- L38 _public enumerator_ `RVMA_UpToDateWithWarnings` — Asset has been compiled since it was last modified. There are warnings.
- L39 _public enumerator_ `RVMA_MAX`

#### class `URigVMRuntimeAssetInterface`  
`class URigVMRuntimeAssetInterface : public UInterface`  
_L43-46_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType)`
- inherits: `UInterface`

#### class `IRigVMRuntimeAssetInterface`  
`class IRigVMRuntimeAssetInterface`  
_L48-99_
- L53 _protected member_ `mutable TArray<TWeakObjectPtr<UObject>> ArchetypeInstances;`
- L57 _public prototype_ `static TScriptInterface<IRigVMRuntimeAssetInterface> GetInterfaceOuter(const UObject* InObject);`
- L60 _public prototype_ `virtual UObject* GetEditorOnlyData() = 0;`
- L61 _public prototype_ `virtual const UObject* GetEditorOnlyData() const = 0;`
- L64 _public prototype_ `virtual UClass* GetRigVMHostClass() const = 0;`
- L65 _public prototype_ `virtual URigVM* GetVM() = 0;`
- L67 _public prototype_ `virtual TArray<FRigVMExternalVariable> GetExternalVariables() = 0;`
- L68 _public prototype_ `virtual const UStruct* GetVariablesStruct() = 0;`
- L69 _public prototype_ `virtual uint8* GetVariablesMemory() = 0;`
- L70 _public prototype_ `virtual const uint8* GetVariablesMemory() const = 0;`
- L71 _public prototype_ `virtual FProperty* FindGeneratedPropertyByName(const FName& InName) = 0;`
- L72 _public function_ `virtual const FProperty* FindGeneratedPropertyByName(const FName& InName) const`
- L74 _public prototype_ `virtual FRigVMRuntimeSettings& GetVMRuntimeSettings() = 0;`
- L75 _public prototype_ `virtual FRigVMVariant& GetAssetVariant() = 0;`
- L76 _public function_ `virtual const FRigVMVariant& GetAssetVariant() const`
- L77 _public prototype_ `virtual TMap<FString, FSoftObjectPath>& GetUserDefinedStructGuidToPathName() = 0;`
- L78 _public prototype_ `virtual TMap<FString, FSoftObjectPath>& GetUserDefinedEnumToPathName() = 0;`
- L79 _public prototype_ `virtual TSet<TObjectPtr<UObject>>& GetUserDefinedTypesInUse() = 0;`
- L80 _public prototype_ `virtual TArray<FName>& GetSupportedEventNames() = 0;`
- L81 _public prototype_ `virtual void UpdateSupportedEventNames() = 0;`
- L82 _public prototype_ `virtual TArray<UObject*> GetArchetypeInstances(bool bIncludeDerivedClass) const = 0;`
- L83 _public prototype_ `virtual FRigVMExtendedExecuteContext* GetRigVMExtendedExecuteContext() = 0;`
- L84 _public prototype_ `virtual void RemoveInstance(UObject* InInstance) = 0;`
- L85 _public prototype_ `virtual URigVMHost* InstantiateObject(UObject* InOuter, FName InName, EObjectFlags InFlags) = 0;`
- L86 _public prototype_ `virtual bool InitializeInstance(URigVMHost* InInstance) = 0;`
- L87 _public prototype_ `virtual bool InitializeVariables(URigVMHost* InInstance) = 0;`
- L88 _public prototype_ `virtual bool IsObjectInstanceOfAsset(URigVMHost* InInstance) = 0;`
- L89 _public prototype_ `virtual FRigVMDrawContainer& GetDrawContainer() = 0;`
- L90 _public function_ `const FRigVMDrawContainer& GetDrawContainer() const`
- L92 _public prototype_ `virtual FRigVMDebugInfo& GetDebugInfo() = 0;`
- L94 _public prototype_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const = 0;`

#### class `URigVMRuntimeAsset`  
`class URigVMRuntimeAsset : public UObject, public IRigVMRuntimeAssetInterface, public IRigVMGraphFunctionHost`  
_L102-307_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IRigVMRuntimeAssetInterface,IRigVMGraphFunctionHost`
- L108 _protected function_ `virtual FRigVMGraphFunctionStore* GetRigVMGraphFunctionStore() override`
- L109 _protected function_ `virtual const FRigVMGraphFunctionStore* GetRigVMGraphFunctionStore() const override`
- L111 _protected prototype_ `virtual void PostLoad() override;`
- L112 _protected prototype_ `virtual void PreDuplicate(FObjectDuplicationParameters& DupParams) override;`
- L113 _protected prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L114 _protected prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L116 _protected prototype_ `virtual void MarkInstancesAsGarbage();`
- L119 _protected function_ `virtual UClass* GetRigVMHostClass() const override` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L120 _protected function_ `virtual URigVM* GetVM() override`
- L123 _protected prototype_ `virtual TArray<FRigVMExternalVariable> GetExternalVariables() override;` — Variables Begin
- L124 _protected function_ `virtual const UStruct* GetVariablesStruct() override`
- L125 _protected function_ `virtual uint8* GetVariablesMemory() override`
- L126 _protected function_ `virtual const uint8* GetVariablesMemory() const override`
- L128 _protected prototype_ `virtual TArray<FRigVMGraphVariableDescription> GetAssetVariables() const;` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L129 _protected prototype_ `virtual FRigVMGraphVariableDescription FindAssetVariable(const FName& InName) const;`
- L130 _protected prototype_ `int32 GetVariableIndex(const FName& InName) const;`
- L131 _protected prototype_ `int32 GetVariableIndex(const FGuid& InGuid) const;`
- L133 _protected member_ `FOnRigVMPreVariablesChanged OnPreVariablesChangedDelegate;`
- L134 _protected member_ `FOnRigVMPostVariablesChanged OnPostVariablesChangedDelegate;`
- L135 _protected function_ `virtual FOnRigVMPreVariablesChanged& OnPreVariablesChanged()`
- L136 _protected function_ `virtual FOnRigVMPreVariablesChanged& OnPostVariablesChanged()`
- L137 _protected member_ `bool bIsModifyingVariables = false;`
- L139 _protected prototype_ `virtual bool RemoveMemberVariable(const FName& InName);` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L141 _protected prototype_ `virtual bool BulkRemoveMemberVariables(const TArray<FName>& InNames);` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L142 _protected prototype_ `virtual bool RenameMemberVariable(const FName& InOldName, const FName& InNewName);`
- L143 _protected prototype_ `virtual bool ChangeMemberVariableType(const FName& InName, const FString& InCPPType, bool bIsPublic, bool bIsReadOnly, FString InDefaultValue);`
- L144 _protected prototype_ `bool SetVariableIndex(const FName& InName, int32 NewIndex);`
- L145 _protected prototype_ `virtual bool SetVariableIndex(const FGuid& InVariableGuid, int32 NewIndex);`
- L146 _protected prototype_ `virtual FText GetVariableTooltip(const FName& InName) const;`
- L147 _protected prototype_ `virtual bool SetVariableTooltip(const FName& InName, const FText& InTooltip);`
- L148 _protected prototype_ `virtual FString GetVariableCategory(const FName& InName) const;`
- L149 _protected prototype_ `virtual bool SetVariableCategory(const FName& InName, const FString& InCategory);`
- L150 _protected prototype_ `virtual FString GetVariableMetadataValue(const FName& InName, const FName& InKey) const;`
- L151 _protected prototype_ `virtual bool SetVariableMetadataValue(const FName& InName, const FName& InKey, const FString& InValue);`
- L152 _protected prototype_ `virtual bool RemoveVariableMetadataValue(const FName& InName, const FName& InKey);`
- L153 _protected prototype_ `virtual bool SetVariableExposeOnSpawn(const FName& InName, const bool bInExposeOnSpawn);`
- L154 _protected prototype_ `virtual bool SetVariableExposeToCinematics(const FName& InName, const bool bInExposeToCinematics);`
- L155 _protected prototype_ `virtual bool SetVariablePrivate(const FName& InName, const bool bInPrivate);`
- L156 _protected prototype_ `virtual bool SetVariablePublic(const FName& InName, const bool bIsPublic);`
- L157 _protected prototype_ `virtual FName AddHostMemberVariableFromExternal(FRigVMExternalVariable InVariableToCreate, FString InDefaultValue = FString());`
- L158 _protected function_ `virtual FString GetVariableDefaultValue(const FName& InName) const`
- L162 _protected function_ `virtual FRigVMRuntimeSettings& GetVMRuntimeSettings() override`
- L163 _protected function_ `virtual FRigVMVariant& GetAssetVariant() override`
- L164 _protected function_ `virtual TMap<FString, FSoftObjectPath>& GetUserDefinedStructGuidToPathName() override`
- L165 _protected function_ `virtual TMap<FString, FSoftObjectPath>& GetUserDefinedEnumToPathName() override`
- L166 _protected function_ `virtual TSet<TObjectPtr<UObject>>& GetUserDefinedTypesInUse() override`
- L167 _protected prototype_ `virtual void UpdateSupportedEventNames() override;`
- L168 _protected function_ `virtual ERigVMAssetStatus GetAssetStatus() const`
- L169 _protected function_ `virtual void SetAssetStatus(const ERigVMAssetStatus& InStatus)`
- L170 _protected prototype_ `virtual bool IsUpToDate() const;`
- L171 _protected function_ `virtual FRigVMExtendedExecuteContext* GetRigVMExtendedExecuteContext() override`
- L172 _protected prototype_ `virtual void MarkAssetAsModified(FPropertyChangedEvent PropertyChangedEvent = FPropertyChangedEvent(nullptr));`
- L173 _protected prototype_ `virtual void MarkAssetAsStructurallyModified(bool bSkipDirtyAssetStatus);`
- L174 _protected prototype_ `virtual const TArray<FString>& GetRequiredPlugins(bool bRefresh = true) const;`
- L175 _protected prototype_ `virtual void GenerateRequiredPluginsData(FRigVMExtendedExecuteContext& InContext);`
- L176 _protected function_ `virtual FRigVMPropertyBag* GetVariablesPropertyBag()`
- L177 _protected function_ `virtual FRigVMDrawContainer& GetDrawContainer() override`
- L179 _protected function_ `virtual FRigVMDebugInfo& GetDebugInfo() override`
- L181 _protected prototype_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override;`
- L184 _public prototype_ `virtual FProperty* FindGeneratedPropertyByName(const FName& InName) override;`
- L185 _public function_ `virtual TArray<FName>& GetSupportedEventNames() override`
- L186 _public prototype_ `virtual void PostInitProperties() override;`
- L187 _public prototype_ `virtual void Initialize(UClass* InEditorOnlyDataClass);`
- L188 _public prototype_ `virtual void RemoveInstance(UObject* InInstance) override;`
- L189 _public prototype_ `virtual URigVMHost* InstantiateObject(UObject* InOuter, FName InName, EObjectFlags InFlags) override;`
- L190 _public prototype_ `virtual bool InitializeInstance(URigVMHost* InInstance) override;`
- L191 _public prototype_ `virtual bool InitializeVariables(URigVMHost* InInstance) override;`
- L192 _public function_ `virtual bool IsObjectInstanceOfAsset(URigVMHost* InInstance) override`
- L193 _public prototype_ `virtual TArray<UObject*> GetArchetypeInstances(bool bIncludeDerivedClass) const override;`
- L196 _public function_ `virtual UObject* GetEditorOnlyData() override`
- L197 _public function_ `virtual const UObject* GetEditorOnlyData() const override`
- L201 _public member_ `FString PreRenameOldAssetPath;` — Transient storage for pre-rename asset paths, used by EditorAsset::PostRename These are set before EditorAsset->Rename() and cleared after
- L202 _public member_ `FString PreRenameNewAssetPath;`
- L208 _public function_ `virtual UObject* GetEditorAsset()` — `UFUNCTION(BlueprintCallable, Category="VM")` — This is the reflection for python usage, we cannot add the UFUNCTION in the WITH_EDITORONLY_DATA section
- L211 _public function_ `virtual UObject* GetObjectBeingDebugged(bool bEvenIfPendingKill = false)`
- L212 _public function_ `virtual const FString& GetObjectBeingDebuggedPath() const`
- L213 _public function_ `virtual void SetObjectBeingDebuggedPath(const FString& InPath)`
- L214 _public function_ `virtual void SetObjectBeingDebugged(UObject* InObject)`
- L215 _public function_ `virtual UWorld* GetWorldBeingDebugged() const`
- L216 _public function_ `virtual void SetWorldBeingDebugged(UWorld* NewWorld)`
- L219 _public function_ `virtual TArray<FRigVMReferenceNodeData>& GetFunctionReferenceNodeData()`
- L221 _public function_ `virtual const TArray<FRigVMGraphFunctionHeader>& GetPublicGraphFunctions() const`
- L222 _public function_ `virtual void SetPublicGraphFunctions(const TArray<FRigVMGraphFunctionHeader>& InHeaders)`
- L227 _protected member_ `TObjectPtr<URigVM> VM;` — `UPROPERTY()`
- L230 _protected member_ `FRigVMExtendedExecuteContext ExecuteContext;` — `UPROPERTY()`
- L233 _protected member_ `FRigVMPropertyBag Variables;` — `UPROPERTY()`
- L236 _protected member_ `FRigVMGraphFunctionStore GraphFunctionStore;` — `UPROPERTY()`
- L240 _protected member_ `TArray<FRigVMGraphFunctionHeader> PublicGraphFunctions;` — `UPROPERTY(AssetRegistrySearchable)` — Asset searchable information about exposed public functions on this rig
- L243 _protected member_ `FRigVMRuntimeSettings RuntimeSettings;` — `UPROPERTY(EditAnywhere, Category = "VM")`
- L246 _protected member_ `FRigVMDrawContainer DrawContainer;` — `UPROPERTY()`
- L250 _protected member_ `FRigVMVariant AssetVariant;` — `UPROPERTY(EditAnywhere, AssetRegistrySearchable, Category = "Variant")` — Variant information about this asset
- L253 _protected member_ `TMap<FString, FSoftObjectPath> UserDefinedStructGuidToPathName;` — `UPROPERTY()`
- L255 _protected member_ `TMap<FString, FSoftObjectPath> UserDefinedEnumToPathName;` — `UPROPERTY()`
- L257 _protected member_ `TSet<TObjectPtr<UObject>> UserDefinedTypesInUse;` — `UPROPERTY(transient)`
- L261 _protected member_ `TArray<FName> SupportedEventNames;` — `UPROPERTY(AssetRegistrySearchable)` — The event names this rigvm blueprint contains
- L265 _protected member_ `TEnumAsByte<ERigVMAssetStatus> Status;` — `UPROPERTY(transient)` — The current status of this blueprint
- L269 _protected member_ `TObjectPtr<UObject> EditorAsset;` — `UPROPERTY()` — The outer of this object is the runtime asset
- L273 _protected member_ `TArray<FRigVMReferenceNodeData> FunctionReferenceNodeData;` — `UPROPERTY(AssetRegistrySearchable)` — Asset searchable information function references in this rig
- L278 _protected member_ `TArray<FString> RequiredPlugins;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Dependencies")`
- L282 _protected member_ `TArray<TObjectPtr<UAssetUserData>> AssetUserData;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Instanced, Category = "Default")` — Array of user data stored with the asset
- L287 _protected member_ `TArray<TObjectPtr<UAssetUserData>> AssetUserDataEditorOnly;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Instanced, Category = "Default")` — Array of user data stored with the asset
- L291 _protected member_ `TWeakObjectPtr< UObject > CurrentObjectBeingDebugged;` — Current object being debugged for this blueprint
- L294 _protected member_ `FString ObjectPathToDebug;` — Raw path of object to be debugged, this might have been spawned inside a specific PIE level so is not stored as an object path type
- L297 _protected member_ `TWeakObjectPtr< class UWorld > CurrentWorldBeingDebugged;` — Current world being debugged for this blueprint
- L299 _protected member_ `FRigVMDebugInfo DebugInfo;`

#### class `FRigVMAssetVariablesChangeScope`  
`class FRigVMAssetVariablesChangeScope`  
_L310-322_
- L314 _public prototype_ `FRigVMAssetVariablesChangeScope(URigVMRuntimeAsset* InAsset, const FName InVariableName);`
- L316 _public prototype_ `~FRigVMAssetVariablesChangeScope();`
- L320 _private member_ `const FName VariableName;`
- L321 _private member_ `URigVMRuntimeAsset* Asset;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVM_API`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRigVMPreVariablesChanged, const FName);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRigVMPreVariablesChanged, const FName);`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRigVMPostVariablesChanged, const FName);`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRigVMPostVariablesChanged, const FName);`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMSettings.h` (Public)


#### enum `ERigVMSaveOnCompile`  
`enum class ERigVMSaveOnCompile : uint8`  
_L21-26_
- reflection: `UENUM()`
- desc: Determines when to save RigVM assets after compilation.
- L23 _public enumerator_ `Never UMETA(DisplayName="Never")`
- L24 _public enumerator_ `SuccessOnly UMETA(DisplayName="On Success Only")`
- L25 _public enumerator_ `Always UMETA(DisplayName = "Always")`

#### class `URigVMEditorSettings`  
`class URigVMEditorSettings : public UDeveloperSettings`  
_L32-92_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, meta=(DisplayName="RigVM Editor"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: Customize RigVM Rig Editor.
- L38 _public function_ `virtual FName GetCategoryName() const override` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L45 _public member_ `ERigVMSaveOnCompile SaveOnCompile = ERigVMSaveOnCompile::Never;` — `UPROPERTY(EditAnywhere, config, Category = Compiler)` — Determines when the asset should be saved after compilation. This applies to RigVM assets that are not blueprint-based (e.g., Control Rig Runtime Assets).
- L50 _public member_ `bool bHighlightSimilarNodes;` — `UPROPERTY(EditAnywhere, config, Category = Interaction)` — with this checked similar nodes in the graph will be highlighted. this highlighting can then also be used to functionize items
- L54 _public member_ `bool bFadeOutUnrelatedNodes;` — `UPROPERTY(EditAnywhere, config, Category = Interaction)` — fade out unrelated nodes
- L58 _public member_ `bool bUseFlashLight;` — `UPROPERTY(EditAnywhere, config, Category = Interaction)` — use a flash light to brighten up nodes
- L63 _public member_ `bool bAutoLinkMutableNodes;` — `UPROPERTY(EditAnywhere, config, Category = Interaction)` — When this is checked mutable nodes (nodes with an execute pin) will be hooked up automatically.
- L72 _public member_ `bool bDirectRerouteNodeEditing = false;` — `UPROPERTY(EditAnywhere, config, Category = Interaction)` — When enabled: - Left Mouse Button drag drags nodes - Ctrl Left Mouse Button drag creates connections - Double-clicking near a spline in the Graph creates a reroute node
- L76 _public member_ `bool bEnableContextMenuTimeSlicing;` — `UPROPERTY(EditAnywhere, config, Category = Workflow, meta = (DisplayName = "Enable Non-Blocking Context Menu"))` — When the Blueprint graph context menu is invoked (e.g. by right-clicking in the graph or dragging off a pin), do not block the UI while populating the available actions list.
- L83 _public member_ `bool bEnableFuzzySearchInActionMenu;` — `UPROPERTY(EditAnywhere, config, Category = Workflow, meta = (DisplayName = "Enable fuzzy search in action menu"))` — When right-clicking in a RigVM based graph (for example Control Rig) enabling this option will apply a fuzzy string search to find items
- L90 _public member_ `float MinimumFuzzyScore;` — `UPROPERTY(EditAnywhere, config, Category = Workflow, meta = (DisplayName = "Minimum Fuzzy Score", UIMin = "0.0", UIMax = "100.0"))` — Fuzzy searches will return a weight between 0.0 and 100.0. By specifying the minimum weight you can remove unlikely matches.

#### class `URigVMProjectSettings`  
`class URigVMProjectSettings : public UDeveloperSettings`  
_L96-108_
- reflection: `UCLASS(config = Editor, meta=(DisplayName="RigVM Project Settings"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L103 _public member_ `TArray<FRigVMTag> VariantTags;` — `UPROPERTY(EditAnywhere, config, Category = Variants)`
- L106 _public prototype_ `FRigVMTag GetTag(FName InTagName) const;` — `UFUNCTION(BlueprintPure, Category= Variants)`
- L107 _public prototype_ `const FRigVMTag* FindTag(FName InTagName) const;`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMStringUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace RigVMStringUtils`
- L10 _prototype_ `FString JoinStrings(const FString& InStringA, const FString& InStringB, const TCHAR* InSeparator, const TCHAR* InPrefix = nullptr, const TCHAR* InSuffix = nullptr);` (scope `RigVMStringUtils`) — Joins two strings given a separator
- L13 _prototype_ `FString JoinStrings(const TArray<FString>& InStrings, const TCHAR* InSeparator, const TCHAR* InPrefix = nullptr, const TCHAR* InSuffix = nullptr);` (scope `RigVMStringUtils`) — Joins a series of strings given a separator
- L14 _prototype_ `FString JoinStrings(const TArrayView<FString>& InStrings, const TCHAR* InSeparator, const TCHAR* InPrefix = nullptr, const TCHAR* InSuffix = nullptr);` (scope `RigVMStringUtils`)
- L15 _prototype_ `FString JoinStringsConst(const TArrayView<const FString>& InStrings, const TCHAR* InSeparator, const TCHAR* InPrefix = nullptr, const TCHAR* InSuffix = nullptr);` (scope `RigVMStringUtils`)
- L18 _prototype_ `bool SplitString(const FString& InString, const TCHAR* InSeparator, TArray<FString>& InOutParts);` (scope `RigVMStringUtils`) — Splits a string up into its parts
- L21 _prototype_ `FString MakeTemplateNotation(const FString& InTemplateName, const TArray<FString>& InArgumentNotations);` (scope `RigVMStringUtils`) — Creates a template notation such as "MyTemplate(float,bool,float)"
- L24 _prototype_ `bool SplitNodePathAtStart(const FString& InNodePath, FString& LeftMost, FString& Right);` (scope `RigVMStringUtils`) — Splits a NodePath at the start, so for example "CollapseNodeA|CollapseNodeB|CollapseNodeC" becomes "CollapseNodeA" and "CollapseNodeB|CollapseNodeC"
- L27 _prototype_ `bool SplitNodePathAtEnd(const FString& InNodePath, FString& Left, FString& RightMost);` (scope `RigVMStringUtils`) — Splits a NodePath at the end, so for example "CollapseNodeA|CollapseNodeB|CollapseNodeC" becomes "CollapseNodeA|CollapseNodeB" and "CollapseNodeC"
- L30 _prototype_ `bool SplitNodePath(const FString& InNodePath, TArray<FString>& Parts);` (scope `RigVMStringUtils`) — Splits a NodePath into all segments, so for example "Node.Color.R" becomes ["Node", "Color", "R"]
- L33 _prototype_ `FString JoinNodePath(const FString& Left, const FString& Right);` (scope `RigVMStringUtils`) — Joins a NodePath from to segments, so for example "CollapseNodeA" and "CollapseNodeB|CollapseNodeC" becomes "CollapseNodeA|CollapseNodeB|CollapseNodeC"
- L36 _prototype_ `FString JoinNodePath(const TArray<FString>& InParts);` (scope `RigVMStringUtils`) — Joins a NodePath from to segments, so for example ["CollapseNodeA", "CollapseNodeB", "CollapseNodeC"] becomes "CollapseNodeA|CollapseNodeB|CollapseNodeC"
- L39 _prototype_ `bool SplitPinPathAtStart(const FString& InPinPath, FString& LeftMost, FString& Right);` (scope `RigVMStringUtils`) — Splits a PinPath at the start, so for example "Node.Color.R" becomes "Node" and "Color.R"
- L40 _prototype_ `bool SplitPinPathAtStart(FStringView InPinPath, FStringView& LeftMost, FStringView& Right);` (scope `RigVMStringUtils`)
- L43 _prototype_ `bool SplitPinPathAtEnd(const FString& InPinPath, FString& Left, FString& RightMost);` (scope `RigVMStringUtils`) — Splits a PinPath at the start, so for example "Node.Color.R" becomes "Node.Color" and "R"
- L46 _prototype_ `bool SplitPinPath(const FString& InPinPath, TArray<FString>& Parts);` (scope `RigVMStringUtils`) — Splits a PinPath into all segments, so for example "Node.Color.R" becomes ["Node", "Color", "R"]
- L49 _prototype_ `FString JoinPinPath(const FString& Left, const FString& Right);` (scope `RigVMStringUtils`) — Joins a PinPath from to segments, so for example "Node.Color" and "R" becomes "Node.Color.R"
- L52 _prototype_ `FString JoinPinPath(const TArray<FString>& InParts);` (scope `RigVMStringUtils`) — Joins a PinPath from to segments, so for example ["Node", "Color", "R"] becomes "Node.Color.R"
- L55 _prototype_ `FString JoinDefaultValue(const TArray<FString>& InParts);` (scope `RigVMStringUtils`) — Joins the name value pairs into a single default value string
- L58 _prototype_ `TArray<FString> SplitDefaultValue(const FString& InDefaultValue);` (scope `RigVMStringUtils`) — Splits the default value into name-value pairs
- L61 _prototype_ `void SanitizeName(FString& InOutName, bool bAllowPeriod, bool bAllowSpace, int32 InMaxNameLength);` (scope `RigVMStringUtils`) — Sanitizes a name as per ruleset

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMTrace.h` (Public)


#### struct `FRigVMTraceBaseData`  
`struct FRigVMTraceBaseData`  
_L32-52_
- desc: Base structure for all RigVM trace structures
- L34 _public function_ `FRigVMTraceBaseData() : Cycles(0) , ProfileTime(0) , RecordingTime(0) , RigVMObjectVersion(0)`
- L43 _public member_ `uint64 Cycles;` — Cycles the frame took
- L46 _public member_ `double ProfileTime;` — The time of the sample at machine time
- L48 _public member_ `double RecordingTime;` — The time of the sample at internal time of the host
- L51 _public member_ `int32 RigVMObjectVersion;` — The version used (FRigVMObjectVersion)

#### struct `FRigVMTraceConstantData`  
`struct FRigVMTraceConstantData : FRigVMTraceBaseData`  
_L71-94_
- inherits: `FRigVMTraceBaseData`
- desc: The constant data stored in the stream only once when tracing a RigVMHost
- L73 _public function_ `FRigVMTraceConstantData() : FRigVMTraceBaseData() , HostId(0) , BoundOuterId(0) , VMHash(0) , ByteCodeHash(0)`
- L83 _public member_ `uint64 HostId;` — The object id of the traced RigVM Host
- L85 _public member_ `uint64 BoundOuterId;` — The object id of the actor / component this host owned by
- L87 _public member_ `uint32 VMHash;` — The hash of the traced VM
- L89 _public member_ `uint32 ByteCodeHash;` — The hash of the traced bytecode
- L91 _public member_ `FRigVMTraceArchive LiteralMemory;` — An archive storing the literal memory
- L93 _public member_ `FRigVMTraceArchive HostConstantData;` — An archive storing auxiliary constant data from the host

#### struct `FRigVMTraceExecuteData`  
`struct FRigVMTraceExecuteData : FRigVMTraceBaseData`  
_L118-156_
- inherits: `FRigVMTraceBaseData`
- desc: The data to be traced per frame for a RigVMHost.
- L120 _public function_ `FRigVMTraceExecuteData() : FRigVMTraceBaseData() , AbsoluteTime(0) , DeltaTime(0) , WorldId(0) , HostId(0) , OverallCycles(0)`
- L131 _public member_ `double AbsoluteTime;` — The sample's absolute time of the host
- L133 _public member_ `double DeltaTime;` — The sample's delta time of the host
- L135 _public member_ `uint64 WorldId;` — The id of the world this host belongs to
- L137 _public member_ `uint64 HostId;` — The id of the host
- L139 _public member_ `FRigVMTraceArchive WorkMemory;` — An archive storing the work memory of the VM
- L141 _public member_ `FRigVMTraceArchive DebugMemory;` — An archive storing the debug memory of the VM
- L143 _public member_ `FRigVMTraceArchive ExternalMemory;` — An archive storing the external memory (variables) of the VM
- L145 _public member_ `FString Entries;` — The names of the entries being executed
- L147 _public member_ `TArray<int32> VisitedInstructions;` — The instructions visited during this sample
- L149 _public member_ `uint64 OverallCycles;` — The overall duration in cycles
- L151 _public member_ `TArray<uint64> InstructionCycles;` — The cycles spent in each instruction
- L153 _public member_ `FRigVMTraceArchive DrawInterface;` — The content of the debug draw interface
- L155 _public member_ `FRigVMTraceArchive HostExecuteData;` — Auxiliary data provided by the host's virtual TraceExecuteData

#### class `FRigVMTrace`  
`class FRigVMTrace : public IRewindDebuggerRuntimeExtension`  
_L161-171_
- inherits: `IRewindDebuggerRuntimeExtension`
- desc: The base service to allow tracing of RigVM host instances
- L164 _public prototype_ `virtual void RecordingStarted() override;`
- L165 _public prototype_ `virtual void RecordingStopped() override;`
- L167 _public prototype_ `static void SetupRigVMEvaluation(FRigVMExtendedExecuteContext& InContext);`
- L168 _public prototype_ `static void TraceRigVMEvaluation(const FRigVMExtendedExecuteContext& InContext);`
- L169 _public prototype_ `static bool RestoreRigVMConstantData(FRigVMExtendedExecuteContext& InOutContext, const FRigVMTraceConstantData& InConstantData);`
- L170 _public prototype_ `static bool RestoreRigVMExecuteData(FRigVMExtendedExecuteContext& InOutContext, const FRigVMTraceExecuteData& InExecuteData);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVM_API`
- L16 _macro_ `#define RIGVM_TRACE_ENABLED 1`
- L18 _macro_ `#define RIGVM_TRACE_ENABLED 0`
- L173 _macro_ `#define TRACE_SETUP_RIGVM_EVALUATION(InContext) \`
- L176 _macro_ `#define TRACE_RIGVM_EVALUATION(InContext) \`
- L181 _macro_ `#define TRACE_SETUP_RIGVM_EVALUATION(...)`
- L182 _macro_ `#define TRACE_RIGVM_EVALUATION(...)`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMTraceArchive.h` (Public)


#### struct `FRigVMTraceArchive`  
`struct FRigVMTraceArchive`  
_L16-65_
- desc: The trace archive is used to store compressed data for a RewindDebugger stream.
- L19 _public prototype_ `FRigVMTraceArchive();`
- L30 _public prototype_ `void Reset();`
- L31 _public prototype_ `void Empty();`
- L32 _public prototype_ `bool IsPayloadEmpty() const;`
- L33 _public prototype_ `bool Compress();`
- L34 _public prototype_ `bool Decompress();`
- L36 _public prototype_ `const FHeader& GetHeader() const;`
- L37 _public prototype_ `bool IsCompressed() const;`
- L38 _public prototype_ `int32 GetUncompressedSize() const;`
- L39 _public prototype_ `int32 GetCompressedSize() const;`
- L41 _public prototype_ `uint8* GetPayloadData();`
- L42 _public prototype_ `const uint8* GetPayloadData() const;`
- L43 _public prototype_ `int32 PayloadNum() const;`
- L45 _public prototype_ `uint8* GetOverallData();`
- L46 _public prototype_ `const uint8* GetOverallData() const;`
- L47 _public prototype_ `int32 OverallNum() const;`
- L53 _protected prototype_ `void SetOverallBuffer(const TArrayView<const uint8>& InBuffer);`
- L54 _protected prototype_ `void SetOverallBuffer(const TArrayView<uint8>& InBuffer);`
- L58 _private member_ `TArray<uint8, TSizedDefaultAllocator<32>> Buffer;`
- L60 _private prototype_ `FHeader& Header();`

#### struct `FRigVMTraceArchive::FHeader`  
`struct FHeader`  
_L21-28_
- L23 _public member_ `bool bIsCompressed = false;`
- L24 _public member_ `int32 UncompressedSize = INDEX_NONE;`
- L25 _public member_ `int32 CompressedSize = INDEX_NONE;`
- L26 _public member_ `int32 NumVersions = INDEX_NONE;`
- L27 _public member_ `int64 VersionsOffset = INDEX_NONE;`

#### class `FRigVMTraceArchiveWriter`  
`class FRigVMTraceArchiveWriter : public FArchiveUObject`  
_L71-97_
- inherits: `FArchiveUObject`
- desc: The trace archive writer is a wrapping archive used to write into a trace archive.
- L74 _public prototype_ `FRigVMTraceArchiveWriter( FRigVMTraceArchive& InOutArchive );`
- L75 _public prototype_ `~FRigVMTraceArchiveWriter();`
- L76 _public prototype_ `virtual void Serialize( void* V, int64 Length ) override;`
- L77 _public prototype_ `virtual int64 Tell() override;`
- L78 _public prototype_ `virtual int64 TotalSize() override;`
- L79 _public prototype_ `virtual void Seek(int64 InPos) override;`
- L81 _public prototype_ `void WriteUObject(const UObject* Obj);`
- L82 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override;`
- L83 _public prototype_ `virtual FArchive& operator<<(FName& Value) override;`
- L84 _public prototype_ `virtual FArchive& operator<<(FText& Value) override;`
- L88 _protected prototype_ `void WriteVersions();`
- L90 _protected member_ `FRigVMTraceArchive& Archive;`
- L91 _protected member_ `int64 Offset;`
- L92 _protected member_ `TMap<FName,int64> NameToOffset;`
- L93 _protected member_ `TMap<const UObject*, uint64> ObjectIdMap;`
- L95 _protected member_ `static inline constexpr uint8 StoringStringAsString = 0;`
- L96 _protected member_ `static inline constexpr uint8 StoringStringAsOffset = 1;`

#### class `FRigVMTraceArchiveReader`  
`class FRigVMTraceArchiveReader : public FRigVMTraceArchiveWriter`  
_L103-122_
- inherits: `FRigVMTraceArchiveWriter`
- desc: The trace archive reader is a wrapping archive used to read from a trace archive.
- L107 _public prototype_ `FRigVMTraceArchiveReader( FRigVMTraceArchive& InOutArchive );`
- L108 _public prototype_ `virtual void Serialize( void* V, int64 Length ) override;`
- L110 _public prototype_ `void ReadUObject(UObject*& Obj);`
- L111 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override;`
- L112 _public prototype_ `virtual FArchive& operator<<(FName& Value) override;`
- L113 _public prototype_ `virtual FArchive& operator<<(FText& Value) override;`
- L117 _protected prototype_ `void ReadVersions();`
- L119 _protected member_ `TMap<uint64, UObject*> ObjectIdMap;`
- L120 _protected member_ `TMap<int64,FName> OffsetToName;`
- L121 _protected member_ `TMap<int64,FString> OffsetToString;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGVM_API`

### `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMTypeUtils.h` (Public)


#### struct `FRigVMUserDefinedTypeResolver`  
`struct FRigVMUserDefinedTypeResolver`  
_L22-50_
- L24 _public prototype_ `FRigVMUserDefinedTypeResolver() = default;`
- L25 _public function_ `explicit FRigVMUserDefinedTypeResolver(const TFunction<UObject*(const FString&)>& InResolver) : Resolver(InResolver)`
- L26 _public function_ `explicit FRigVMUserDefinedTypeResolver(TMap<FString, FSoftObjectPath>&& InObjectMap) : ObjectMap(InObjectMap)`
- L28 _public function_ `UObject* GetTypeObjectByName(const FString& InTypeName) const`
- L42 _public function_ `bool IsValid() const`
- L48 _private member_ `TFunction<UObject*(const FString&)> Resolver;`
- L49 _private member_ `TMap<FString, FSoftObjectPath> ObjectMap;`

#### class `FRigVMPluginsPrefixCache`  
`class FRigVMPluginsPrefixCache : public TSharedFromThis<FRigVMPluginsPrefixCache>`  
_L52-83_
- inherits: `TSharedFromThis<FRigVMPluginsPrefixCache>`
- L56 _public prototype_ `static TSharedRef<FRigVMPluginsPrefixCache> Get();`
- L57 _public prototype_ `virtual ~FRigVMPluginsPrefixCache();`
- L59 _public prototype_ `FString GetPluginName(const UObject* InObject) const;`
- L60 _public prototype_ `void Refresh();`
- L63 _private prototype_ `FRigVMPluginsPrefixCache();`
- L65 _private prototype_ `FRigVMPluginsPrefixCache(const FRigVMPluginsPrefixCache&) = delete;`
- L66 _private prototype_ `FRigVMPluginsPrefixCache& operator=(const FRigVMPluginsPrefixCache&) = delete;`
- L68 _private prototype_ `void OnPluginMounted(IPlugin& InPlugin);`
- L69 _private prototype_ `void OnPluginUnmounted(IPlugin& InPlugin);`
- L77 _private member_ `TMap<FString, FRigVMPluginReferences> CachedPluginPrefixes;`
- L78 _private member_ `bool bInitialized = false;`
- L79 _private member_ `mutable FRWLock CacheLock;`

#### struct `FRigVMPluginsPrefixCache::FRigVMPluginReferences`  
`struct FRigVMPluginReferences`  
_L71-75_
- L73 _public member_ `FString PluginName;`
- L74 _public member_ `uint16 Count = 0;`

#### class `RigVMTypeUtils::TypeIndex`  
`class TypeIndex`  
_L139-162_
- L142 _public member_ `static TRigVMTypeIndex Execute;`
- L143 _public member_ `static TRigVMTypeIndex ExecuteArray;`
- L144 _public member_ `static TRigVMTypeIndex Bool;`
- L145 _public member_ `static TRigVMTypeIndex Float;`
- L146 _public member_ `static TRigVMTypeIndex Double;`
- L147 _public member_ `static TRigVMTypeIndex Int32;`
- L148 _public member_ `static TRigVMTypeIndex UInt32;`
- L149 _public member_ `static TRigVMTypeIndex UInt8;`
- L150 _public member_ `static TRigVMTypeIndex FName;`
- L151 _public member_ `static TRigVMTypeIndex FString;`
- L152 _public member_ `static TRigVMTypeIndex WildCard;`
- L153 _public member_ `static TRigVMTypeIndex BoolArray;`
- L154 _public member_ `static TRigVMTypeIndex FloatArray;`
- L155 _public member_ `static TRigVMTypeIndex DoubleArray;`
- L156 _public member_ `static TRigVMTypeIndex Int32Array;`
- L157 _public member_ `static TRigVMTypeIndex UInt32Array;`
- L158 _public member_ `static TRigVMTypeIndex UInt8Array;`
- L159 _public member_ `static TRigVMTypeIndex FNameArray;`
- L160 _public member_ `static TRigVMTypeIndex FStringArray;`
- L161 _public member_ `static TRigVMTypeIndex WildCardArray;`

#### enum `RigVMTypeUtils::EClassArgType`  
`enum class EClassArgType`  
_L257-264_
- desc: A UClass argument is used to signify both the object type and its class type. This argument differentiates between the two
- L260 _public enumerator_ `AsClass` — This type signifies a class
- L263 _public enumerator_ `AsObject` — This type signifies an object

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API RIGVM_API`
- L85 _namespace_ `namespace RigVMTypeUtils`
- L87 _variable_ `constexpr TCHAR TArrayPrefix[] = TEXT("TAr` (scope `RigVMTypeUtils`)
- L88 _variable_ `constexpr TCHAR TObjectPtrPrefix[] = TEXT("TOb` (scope `RigVMTypeUtils`)
- L89 _variable_ `constexpr TCHAR TSubclassOfPrefix[] = TEXT("TSu` (scope `RigVMTypeUtils`)
- L90 _variable_ `constexpr TCHAR TScriptInterfacePrefix[] = TEXT("TSc` (scope `RigVMTypeUtils`)
- L91 _variable_ `constexpr TCHAR TArrayTemplate[] = TEXT("TAr` (scope `RigVMTypeUtils`)
- L92 _variable_ `constexpr TCHAR TObjectPtrTemplate[] = TEXT("TOb` (scope `RigVMTypeUtils`)
- L93 _variable_ `constexpr TCHAR TSubclassOfTemplate[] = TEXT("TSu` (scope `RigVMTypeUtils`)
- L94 _variable_ `constexpr TCHAR TScriptInterfaceTemplate[] = TEXT("TSc` (scope `RigVMTypeUtils`)
- L96 _externvar_ `extern const TCHAR BoolType[];` (scope `RigVMTypeUtils`)
- L97 _externvar_ `extern const TCHAR FloatType[];` (scope `RigVMTypeUtils`)
- L98 _externvar_ `extern const TCHAR DoubleType[];` (scope `RigVMTypeUtils`)
- L99 _externvar_ `extern const TCHAR IntType[];` (scope `RigVMTypeUtils`)
- L100 _externvar_ `extern const TCHAR Int32Type[];` (scope `RigVMTypeUtils`)
- L101 _externvar_ `extern const TCHAR Int64Type[];` (scope `RigVMTypeUtils`)
- L102 _externvar_ `extern const TCHAR UInt8Type[];` (scope `RigVMTypeUtils`)
- L103 _externvar_ `extern const TCHAR UInt32Type[];` (scope `RigVMTypeUtils`)
- L104 _externvar_ `extern const TCHAR UInt64Type[];` (scope `RigVMTypeUtils`)
- L105 _externvar_ `extern const TCHAR FNameType[];` (scope `RigVMTypeUtils`)
- L106 _externvar_ `extern const TCHAR FStringType[];` (scope `RigVMTypeUtils`)
- L107 _externvar_ `extern const TCHAR FTextType[];` (scope `RigVMTypeUtils`)
- L108 _externvar_ `extern const TCHAR BoolArrayType[];` (scope `RigVMTypeUtils`)
- L109 _externvar_ `extern const TCHAR FloatArrayType[];` (scope `RigVMTypeUtils`)
- L110 _externvar_ `extern const TCHAR DoubleArrayType[];` (scope `RigVMTypeUtils`)
- L111 _externvar_ `extern const TCHAR Int32ArrayType[];` (scope `RigVMTypeUtils`)
- L112 _externvar_ `extern const TCHAR UInt32ArrayType[];` (scope `RigVMTypeUtils`)
- L113 _externvar_ `extern const TCHAR UInt8ArrayType[];` (scope `RigVMTypeUtils`)
- L114 _externvar_ `extern const TCHAR FNameArrayType[];` (scope `RigVMTypeUtils`)
- L115 _externvar_ `extern const TCHAR FStringArrayType[];` (scope `RigVMTypeUtils`)
- L116 _externvar_ `extern const TCHAR FTextArrayType[];` (scope `RigVMTypeUtils`)
- L118 _externvar_ `extern const FLazyName BoolTypeName;` (scope `RigVMTypeUtils`)
- L119 _externvar_ `extern const FLazyName FloatTypeName;` (scope `RigVMTypeUtils`)
- L120 _externvar_ `extern const FLazyName DoubleTypeName;` (scope `RigVMTypeUtils`)
- L121 _externvar_ `extern const FLazyName IntTypeName;` (scope `RigVMTypeUtils`)
- L122 _externvar_ `extern const FLazyName Int32TypeName;` (scope `RigVMTypeUtils`)
- L123 _externvar_ `extern const FLazyName Int64TypeName;` (scope `RigVMTypeUtils`)
- L124 _externvar_ `extern const FLazyName UInt8TypeName;` (scope `RigVMTypeUtils`)
- L125 _externvar_ `extern const FLazyName UInt32TypeName;` (scope `RigVMTypeUtils`)
- L126 _externvar_ `extern const FLazyName UInt64TypeName;` (scope `RigVMTypeUtils`)
- L127 _externvar_ `extern const FLazyName FNameTypeName;` (scope `RigVMTypeUtils`)
- L128 _externvar_ `extern const FLazyName FStringTypeName;` (scope `RigVMTypeUtils`)
- L129 _externvar_ `extern const FLazyName FTextTypeName;` (scope `RigVMTypeUtils`)
- L130 _externvar_ `extern const FLazyName BoolArrayTypeName;` (scope `RigVMTypeUtils`)
- L131 _externvar_ `extern const FLazyName FloatArrayTypeName;` (scope `RigVMTypeUtils`)
- L132 _externvar_ `extern const FLazyName DoubleArrayTypeName;` (scope `RigVMTypeUtils`)
- L133 _externvar_ `extern const FLazyName Int32ArrayTypeName;` (scope `RigVMTypeUtils`)
- L134 _externvar_ `extern const FLazyName UInt32ArrayTypeName;` (scope `RigVMTypeUtils`)
- L135 _externvar_ `extern const FLazyName UInt8ArrayTypeName;` (scope `RigVMTypeUtils`)
- L136 _externvar_ `extern const FLazyName FNameArrayTypeName;` (scope `RigVMTypeUtils`)
- L137 _externvar_ `extern const FLazyName FStringArrayTypeName;` (scope `RigVMTypeUtils`)
- L165 _function_ `inline bool IsArrayType(const FString& InCPPType)` (scope `RigVMTypeUtils`) — Returns true if the type specified is an array
- L170 _function_ `inline FString ArrayTypeFromBaseType(const FString& InCPPType)` (scope `RigVMTypeUtils`)
- L175 _function_ `inline FString BaseTypeFromArrayType(const FString& InCPPType)` (scope `RigVMTypeUtils`)
- L180 _function_ `inline FString GetUniqueStructTypeName(const FGuid& InStructGuid)` (scope `RigVMTypeUtils`)
- L186 _function_ `inline FString GetUniqueStructTypeName(const UScriptStruct* InScriptStruct)` (scope `RigVMTypeUtils`)
- L196 _function_ `inline FString CPPTypeFromEnum(const UEnum* InEnum)` (scope `RigVMTypeUtils`)
- L206 _function_ `inline bool IsUClassType(const FString& InCPPType)` (scope `RigVMTypeUtils`)
- L211 _function_ `inline bool IsUObjectType(const FString& InCPPType)` (scope `RigVMTypeUtils`)
- L216 _function_ `inline bool IsInterfaceType(const FString& InCPPType)` (scope `RigVMTypeUtils`)
- L221 _function_ `static UScriptStruct* GetWildCardCPPTypeObject()` (scope `RigVMTypeUtils`)
- L227 _function_ `static const FString& GetWildCardCPPType()` (scope `RigVMTypeUtils`)
- L233 _function_ `static const FLazyName& GetWildCardCPPTypeName()` (scope `RigVMTypeUtils`)
- L239 _function_ `static const FString& GetWildCardArrayCPPType()` (scope `RigVMTypeUtils`)
- L245 _function_ `static const FLazyName& GetWildCardArrayCPPTypeName()` (scope `RigVMTypeUtils`)
- L251 _prototype_ `bool RequiresCPPTypeObject(const FString& InCPPType);` (scope `RigVMTypeUtils`)
- L253 _prototype_ `UObject* FindObjectGlobally(const TCHAR* InObjectName, bool bUseRedirector);` (scope `RigVMTypeUtils`)
- L266 _prototype_ `FString CPPTypeFromObject(const UObject* InCPPTypeObject, EClassArgType InClassArgType = EClassArgType::AsObject);` (scope `RigVMTypeUtils`)
- L269 _prototype_ `UObject* UserDefinedTypeFromCPPType(FString& InOutCPPType, const FRigVMUserDefinedTypeResolver* InTypeResolver = nullptr);` (scope `RigVMTypeUtils`) — Finds the CPPTypeObject from a CPP type of a potentially missing / unloaded user defined struct or enum
- L272 _prototype_ `UObject* ObjectFromCPPType(FString& InOutCPPType, bool bUseRedirector = true, const FRigVMUserDefinedTypeResolver* InTypeResolver = nullptr);` (scope `RigVMTypeUtils`) — Finds the CPPTypeObject from the CPPType. If not found, tries to use redirectors and modifies the InOutCPPType.
- L274 _function_ `static void CleanupCPPType(FString& CPPType)` (scope `RigVMTypeUtils`)
- L286 _function_ `static FString GetCPPTypeFromProperty(const FProperty* InProperty)` (scope `RigVMTypeUtils`)
- L297 _prototype_ `UObject* GetCPPTypeObjectFromProperty(const FProperty* InProperty);` (scope `RigVMTypeUtils`)
- L299 _prototype_ `FString PostProcessCPPType(const FString& InCPPType, UObject* InCPPTypeObject = nullptr, const FRigVMUserDefinedTypeResolver* InResolvalInfo = nullptr, bool bIsSerializing = false);` (scope `RigVMTypeUtils`)
- L301 _prototype_ `bool FixCPPTypeAndObject(FString& InOutCPPType, TObjectPtr<UObject>& InOutCPPTypeObject, const FRigVMUserDefinedTypeResolver* InResolvalInfo = nullptr);` (scope `RigVMTypeUtils`)
- L304 _prototype_ `UObject* FindObjectFromCPPTypeObjectPath(const FString& InObjectPath);` (scope `RigVMTypeUtils`) — helper function to retrieve an object from a path
- L307 _function_ `template<class T> static T* FindObjectFromCPPTypeObjectPath(const FString& InObjectPath)` (scope `RigVMTypeUtils`)
- L312 _prototype_ `bool AreCompatible(const FProperty* InSourceProperty, const FProperty* InTargetProperty);` (scope `RigVMTypeUtils`)
- L314 _prototype_ `FString GetPluginName(const UObject* InObject);` (scope `RigVMTypeUtils`)
- L315 _prototype_ `TArray<FString> GetPluginModulePrefixes(const IPlugin& InPlugin);` (scope `RigVMTypeUtils`)
- L317 _prototype_ `bool CPPTypeFromExternalVariable(const FRigVMExternalVariable& InExternalVariable, FString& OutCPPType, UObject** OutCPPTypeObject);` (scope `RigVMTypeUtils`)
