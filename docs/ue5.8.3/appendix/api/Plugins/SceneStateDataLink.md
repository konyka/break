# Plugins / SceneStateDataLink

- module root: `Plugins/VirtualProduction/SceneStateDataLink/Source/SceneStateDataLink`
- headers: 2; symbols: 18
- symbol kinds: delegate=1, member=4, namespace=2, prototype=8, struct=2, typedef=1
- PublicDependencyModuleNames: Core, CoreUObject, DataLink, Engine, SceneState, SceneStateBinding

### `Plugins/VirtualProduction/SceneStateDataLink/Source/SceneStateDataLink/Private/SceneStateDataLinkLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneStateDataLink, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneStateDataLink, Log, All);`

### `Plugins/VirtualProduction/SceneStateDataLink/Source/SceneStateDataLink/Public/SceneStateRunDataLinkTask.h` (Public)


#### struct `FSceneStateDataLinkRequestTaskInstance`  
`struct FSceneStateDataLinkRequestTaskInstance : public FSceneStateTaskInstance`  
_L21-48_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L26 _public prototype_ `FDataLinkInstance CreateDataLinkInstance() const;` — Creates a FDataLinkInstance from this Task Instance
- L30 _public member_ `TObjectPtr<UDataLinkGraph> DataLinkGraph;` — `UPROPERTY(EditAnywhere, Category="Data Link", meta=(NoBinding))` — The data link graph to execute
- L37 _public member_ `TArray<FDataLinkInputData> InputData;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category="Data Link", meta=(EditFixedOrder, NoBindingSelfOnly))` — Input data required to run the Data Link Graph. The type of input data is determined by the Task's Data Link Graph property
- L44 _public member_ `FSceneStatePropertyReference OutputTarget;` — `UPROPERTY(EditAnywhere, Category="Data Link", meta=(RefType="AnyStruct"))` — The output struct reference to write the data link results to. NOTE: Must match the data link output struct type, or will fail to write!
- L47 _public member_ `TSharedPtr<FDataLinkExecutor> Executor;` — The object handling the execution

#### struct `FSceneStateRunDataLinkTask`  
`struct FSceneStateRunDataLinkTask : public FSceneStateTask`  
_L52-74_
- reflection: `USTRUCT(DisplayName="Run Data Link", Category="Data Link", meta=(UtilityTask))`
- inherits: `FSceneStateTask`
- desc: Runs a Data Link Graph and writes the result to the Output Target
- L56 _public typedef_ `using FInstanceDataType = FSceneStateDataLinkRequestTaskInstance;`
- L61 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L62 _protected prototype_ `virtual void OnBuildTaskInstance(UObject* InOuter, FStructView InTaskInstance) const override;`
- L64 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`
- L65 _protected prototype_ `virtual void OnStop(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, ESceneStateTaskStopReason InStopReason) const override;`
- L70 _private prototype_ `static void OnOutputData(const FDataLinkExecutor& InExecutor, FConstStructView InOutputDataView, UE::SceneState::FTaskExecutionContext InTaskContext);` — Called when data link has broadcast output data
- L73 _private prototype_ `static void OnFinished(const FDataLinkExecutor& InExecutor, EDataLinkExecutionResult InExecutionResult, UE::SceneState::FTaskExecutionContext InTaskContext);` — Called when a data link execution has finished

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SceneState` (scope `UE`)
