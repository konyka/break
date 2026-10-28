# Developer / DistributedBuildInterface

- module root: `Source/Developer/DistributedBuildInterface`
- headers: 1; symbols: 46
- symbol kinds: class=1, function=12, member=22, prototype=5, struct=5, typedef=1

### `Source/Developer/DistributedBuildInterface/Public/DistributedBuildControllerInterface.h` (Public)


#### struct `FDistributedBuildTaskResult`  
`struct FDistributedBuildTaskResult`  
_L16-22_
- L18 _public member_ `int32 ReturnCode;`
- L19 _public member_ `bool bCompleted;`
- L21 _public member_ `TArray<uint8> OutputData;` — If the distributed controller supports virtual files, the output file data will be populated here instead of being written to a file on disk

#### struct `FDistributedBuildStats`  
`struct FDistributedBuildStats`  
_L24-28_
- L26 _public member_ `uint32 MaxRemoteAgents = 0;`
- L27 _public member_ `uint32 MaxActiveAgentCores = 0;`

#### struct `FTaskCommandData`  
`struct FTaskCommandData`  
_L30-47_
- L32 _public member_ `FString Command;`
- L33 _public member_ `FString WorkingDirectory;`
- L34 _public member_ `FString InputFileName;`
- L35 _public member_ `FString OutputFileName;`
- L39 _public member_ `FString ExtraCommandArgs;` — Command-line arguments for the remote task. Positional args first (consumed by index), flags after. Controllers must APPEND their own flags, never prepend, to keep the positional prefix intact.
- L40 _public member_ `FString Description;` — Optional string describing the task; can be used by the controller implementation for debug purposes (i.e. UBA breadcrumbs)
- L41 _public member_ `uint32 DispatcherPID = 0;`
- L42 _public member_ `TArray<uint8> InputFileData;` — Optional byte array containing the contents of the input file; only used if the controller supports virtual files
- L43 _public member_ `TArray <FMemoryView> SourceData;` — Optional array of memory views containing the compressed source files; only used if the controller supports virtual files
- L44 _public member_ `TSharedPtr<void, ESPMode::ThreadSafe> SourceDataOwner;` — Optional shared pointer to opaque data keeping the memory referenced by SourceData alive
- L45 _public member_ `TArray<FString> AdditionalOutputFolders;` — Optional additional folder(s) which task may write artifacts to
- L46 _public member_ `FOutputDataValidator OutputValidator;` — Optional custom output data validator. If set, HandleUbaJobFinished calls this instead of the default format and size check.

#### struct `FDistributedBuildTask`  
`struct FDistributedBuildTask`  
_L49-80_
- L51 _public member_ `uint32 ID;`
- L52 _public member_ `FTaskCommandData CommandData;`
- L53 _public member_ `TPromise<FDistributedBuildTaskResult> Promise;`
- L55 _public function_ `FDistributedBuildTask(uint32 ID, const FTaskCommandData& CommandData, TPromise<FDistributedBuildTaskResult>&& Promise) : ID(ID) , CommandData(CommandData) , Promise(MoveTemp(Promise))`
- L63 _public function_ `void Cancel()` — Sets the promised task result to being incomplete, i.e. FDistributedBuildTaskResult::bCompleted=false.
- L72 _public function_ `void Finalize(int32 InReturnCode, TArray<uint8>&& OutputData = {})` — Sets the promised task result to being completed with the specified return code.

#### struct `FTaskResponse`  
`struct FTaskResponse`  
_L82-86_
- L84 _public member_ `uint32 ID;`
- L85 _public member_ `int32 ReturnCode;`

#### class `IDistributedBuildController`  
`class IDistributedBuildController : public IModuleInterface, public IModularFeature`  
_L88-131_
- inherits: `IModuleInterface,IModularFeature`
- L91 _public function_ `virtual bool SupportsDynamicReloading() override`
- L94 _public function_ `virtual bool SupportsLocalWorkers()` — Returns true if this distributed controller also supports local workers alongside remote workers. By default false.
- L96 _public function_ `virtual bool RequiresRelativePaths()`
- L100 _public function_ `virtual bool SupportsVirtualFiles() const` — Override to return true if this distributed controller supports file virtualization; by doing so the distributed compilation thread will skip writing input files to disk and instead populate FTaskCommandData::InputFileData and FTaskCommandData::SourceData, as well as reading results from memory instead of a file on disk
- L103 _public function_ `virtual void SetMaxLocalWorkers(int32 InMaxNumLocalWorkers)` — Sets the maxmium number of local workers. Ignored if this controller does not support local workers.
- L105 _public prototype_ `virtual void InitializeController() = 0;`
- L108 _public prototype_ `virtual bool IsSupported() = 0;` — Returns true if the controller may be used.
- L111 _public prototype_ `virtual const FString GetName() = 0;` — Returns the name of the controller. Used for logging purposes.
- L113 _public function_ `virtual FString RemapPath(const FString& SourcePath) const`
- L115 _public function_ `virtual void Tick(float DeltaSeconds)`
- L118 _public prototype_ `virtual FString CreateUniqueFilePath() = 0;` — Returns a new file path to be used for writing input data to.
- L121 _public function_ `virtual bool PollStats(FDistributedBuildStats& OutStats)` — Returns the distributed build statistics since the last call and resets its internal values. Returns false if there are no statistics provided.
- L124 _public prototype_ `virtual TFuture<FDistributedBuildTaskResult> EnqueueTask(const FTaskCommandData& CommandData) = 0;` — Launches a task. Returns a future which can be waited on for the results.
- L126 _public function_ `static const FName& GetModularFeatureType()`

#### Free symbols / members of external scopes

- L14 _typedef_ `using FOutputDataValidator = TFunction<bool(TArrayView<const uint8> OutputData)>;` — Optional custom output data validator. When set on FTaskCommandData, this callback is invoked by HandleUbaJobFinished instead of the default format and size check. Return true if the output data is semantically valid for the producing task type.
