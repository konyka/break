# Plugins / NNERuntimeORT

- module root: `Plugins/NNE/NNERuntimeORT/Source/NNERuntimeORT`
- headers: 8; symbols: 208
- symbol kinds: class=17, delegate=1, enum=1, enumerator=2, function=16, member=60, namespace=25, prototype=78, struct=6, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, D3D12RHI, DeveloperSettings, NNE, NNEOnnxruntime, Projects, RHI, RenderCore

### `Plugins/NNE/NNERuntimeORT/Source/NNERuntimeORT/Private/NNERuntimeORT.h` (Private)


#### class `UNNERuntimeORTCpu`  
`class UNNERuntimeORTCpu : public UObject, public INNERuntime, public INNERuntimeCPU`  
_L23-46_
- reflection: `UCLASS()`
- inherits: `UObject,INNERuntime,INNERuntimeCPU`
- L28 _private member_ `TSharedPtr<UE::NNERuntimeORT::Private::FEnvironment> Environment;`
- L31 _public member_ `static FGuid GUID;`
- L32 _public member_ `static int32 Version;`
- L34 _public prototype_ `virtual ~UNNERuntimeORTCpu() = default;`
- L36 _public prototype_ `void Init(TSharedRef<UE::NNERuntimeORT::Private::FEnvironment> InEnvironment);`
- L38 _public prototype_ `virtual FString GetRuntimeName() const override;`
- L40 _public prototype_ `virtual ECanCreateModelDataStatus CanCreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L41 _public prototype_ `virtual TSharedPtr<UE::NNE::FSharedModelData> CreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) override;`
- L42 _public prototype_ `virtual FString GetModelDataIdentifier(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L44 _public prototype_ `virtual ECanCreateModelCPUStatus CanCreateModelCPU(const TObjectPtr<UNNEModelData> ModelData) const override;`
- L45 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelCPU> CreateModelCPU(const TObjectPtr<UNNEModelData> ModelData) override;`

#### class `INNERuntimeORTDmlImpl`  
`class INNERuntimeORTDmlImpl : public INNERuntime, public INNERuntimeGPU, public INNERuntimeRDG`  
_L48-52_
- inherits: `INNERuntime,INNERuntimeGPU,INNERuntimeRDG`
- L51 _public prototype_ `virtual void Init(TSharedRef<UE::NNERuntimeORT::Private::FEnvironment> InEnvironment, bool bInDirectMLAvailable) = 0;`

#### class `UNNERuntimeORTDmlProxy`  
`class UNNERuntimeORTDmlProxy : public UObject, public INNERuntime`  
_L55-73_
- reflection: `UCLASS()`
- inherits: `UObject,INNERuntime`
- L60 _public prototype_ `UNNERuntimeORTDmlProxy();`
- L61 _public prototype_ `~UNNERuntimeORTDmlProxy() = default;`
- L63 _public prototype_ `void Init(TSharedRef<UE::NNERuntimeORT::Private::FEnvironment> InEnvironment, bool bInDirectMLAvailable);`
- L65 _public prototype_ `virtual FString GetRuntimeName() const override;`
- L67 _public prototype_ `virtual ECanCreateModelDataStatus CanCreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L68 _public prototype_ `virtual TSharedPtr<UE::NNE::FSharedModelData> CreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) override;`
- L69 _public prototype_ `virtual FString GetModelDataIdentifier(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L72 _protected member_ `TUniquePtr<INNERuntimeORTDmlImpl> Impl;`

#### class `UNNERuntimeORTDml_GPU_RDG`  
`class UNNERuntimeORTDml_GPU_RDG : public UNNERuntimeORTDmlProxy, public INNERuntimeGPU, public INNERuntimeRDG`  
_L76-86_
- reflection: `UCLASS()`
- inherits: `UNNERuntimeORTDmlProxy,INNERuntimeGPU,INNERuntimeRDG`
- L81 _public function_ `virtual ECanCreateModelGPUStatus CanCreateModelGPU(const TObjectPtr<UNNEModelData> ModelData) const override`
- L82 _public function_ `virtual TSharedPtr<UE::NNE::IModelGPU> CreateModelGPU(const TObjectPtr<UNNEModelData> ModelData) override`
- L84 _public function_ `virtual ECanCreateModelRDGStatus CanCreateModelRDG(TObjectPtr<UNNEModelData> ModelData) const override`
- L85 _public function_ `virtual TSharedPtr<UE::NNE::IModelRDG> CreateModelRDG(TObjectPtr<UNNEModelData> ModelData) override`

#### class `UNNERuntimeORTDml_GPU`  
`class UNNERuntimeORTDml_GPU : public UNNERuntimeORTDmlProxy, public INNERuntimeGPU`  
_L89-96_
- reflection: `UCLASS()`
- inherits: `UNNERuntimeORTDmlProxy,INNERuntimeGPU`
- L94 _public function_ `virtual ECanCreateModelGPUStatus CanCreateModelGPU(const TObjectPtr<UNNEModelData> ModelData) const override`
- L95 _public function_ `virtual TSharedPtr<UE::NNE::IModelGPU> CreateModelGPU(const TObjectPtr<UNNEModelData> ModelData) override`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNERuntimeORT, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNERuntimeORT, Log, All);`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace NNERuntimeORT` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::NNERuntimeORT`)
- L98 _namespace_ `namespace UE`
- L98 _namespace_ `namespace NNERuntimeORT` (scope `UE`)
- L98 _namespace_ `namespace Private` (scope `UE::NNERuntimeORT`)
- L101 _prototype_ `TWeakObjectPtr<UNNERuntimeORTDmlProxy> MakeRuntimeDml(bool bDirectMLAvailable);` (scope `UE::NNERuntimeORT::Private`)

### `Plugins/NNE/NNERuntimeORT/Source/NNERuntimeORT/Private/NNERuntimeORTEnv.h` (Private)


#### class `UE::NNERuntimeORT::Private::FEnvironment`  
`class FEnvironment`  
_L11-38_
- L21 _public prototype_ `FEnvironment() = default;`
- L23 _public prototype_ `~FEnvironment() = default;`
- L25 _public prototype_ `void Configure(const FConfig& InConfig);`
- L27 _public prototype_ `const Ort::Env& GetOrtEnv() const;`
- L29 _public function_ `FConfig GetConfig() const`
- L32 _private prototype_ `void CreateOrtEnv() const;`
- L34 _private member_ `FConfig Config{};`
- L35 _private member_ `mutable Ort::Env OrtEnvironment{nullptr};`
- L37 _private member_ `mutable FCriticalSection CriticalSection;`

#### struct `UE::NNERuntimeORT::Private::FEnvironment::FConfig`  
`struct FConfig`  
_L14-19_
- L16 _public member_ `bool bUseGlobalThreadPool = false;`
- L17 _public member_ `int32 IntraOpNumThreads = 0;`
- L18 _public member_ `int32 InterOpNumThreads = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeORT` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeORT`)

### `Plugins/NNE/NNERuntimeORT/Source/NNERuntimeORT/Private/NNERuntimeORTModel.h` (Private)


#### struct `UE::NNERuntimeORT::Private::FRuntimeConf`  
`struct FRuntimeConf`  
_L18-21_
- L20 _public member_ `ExecutionMode ExecutionMode = ExecutionMode::ORT_SEQUENTIAL;`

#### class `UE::NNERuntimeORT::Private::FModelInstanceORTBase`  
`template <class ModelInterface> class FModelInstanceORTBase : public ModelInterface`  
_L24-44_
- inherits: `ModelInterface`
- L28 _public prototype_ `virtual ~FModelInstanceORTBase() = default;`
- L30 _public prototype_ `virtual TConstArrayView<NNE::FTensorDesc> GetInputTensorDescs() const override;`
- L31 _public prototype_ `virtual TConstArrayView<NNE::FTensorDesc> GetOutputTensorDescs() const override;`
- L32 _public prototype_ `virtual TConstArrayView<NNE::FTensorShape> GetInputTensorShapes() const override;`
- L33 _public prototype_ `virtual TConstArrayView<NNE::FTensorShape> GetOutputTensorShapes() const override;`
- L34 _public prototype_ `virtual typename ModelInterface::ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<NNE::FTensorShape> InInputShapes) override;`
- L38 _protected function_ `FModelInstanceORTBase()`
- L40 _protected member_ `TArray<NNE::FTensorShape> InputTensorShapes;`
- L41 _protected member_ `TArray<NNE::FTensorShape> OutputTensorShapes;`
- L42 _protected member_ `TArray<NNE::FTensorDesc> InputSymbolicTensors;`
- L43 _protected member_ `TArray<NNE::FTensorDesc> OutputSymbolicTensors;`

#### class `UE::NNERuntimeORT::Private::FModelInstanceORTRunSync`  
`template <class ModelInterface, class TensorBinding> class FModelInstanceORTRunSync : public FModelInstanceORTBase<ModelInterface>`  
_L47-85_
- inherits: `FModelInstanceORTBase<ModelInterface>`
- L51 _public prototype_ `FModelInstanceORTRunSync(const FRuntimeConf& InRuntimeConf, TSharedRef<FEnvironment> InEnvironment);`
- L52 _public prototype_ `virtual ~FModelInstanceORTRunSync();`
- L54 _public prototype_ `virtual typename ModelInterface::ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<NNE::FTensorShape> InInputShapes) override;`
- L56 _public prototype_ `bool Init(TConstArrayView64<uint8> ModelData);`
- L58 _public prototype_ `typename ModelInterface::ERunSyncStatus RunSync(TConstArrayView<TensorBinding> InInputBindings, TConstArrayView<TensorBinding> InOutputBindings) override;`
- L61 _protected prototype_ `virtual bool InitializedAndConfigureMembers();`
- L62 _protected prototype_ `bool ConfigureTensors(const bool InIsInput);`
- L64 _protected member_ `FRuntimeConf RuntimeConf;`
- L65 _protected member_ `FString TempDirForModelWithExternalData;`
- L68 _protected member_ `TSharedRef<FEnvironment> Environment;` — ORT-related variables
- L69 _protected member_ `TUniquePtr<Ort::Session> Session;`
- L70 _protected member_ `TUniquePtr<Ort::AllocatorWithDefaultOptions> Allocator;`
- L71 _protected member_ `TUniquePtr<Ort::SessionOptions> SessionOptions;`
- L72 _protected member_ `TUniquePtr<Ort::MemoryInfo> MemoryInfo;`
- L75 _protected member_ `TArray<ONNXTensorElementDataType> InputTensorsORTType;` — IO ORT-related variables
- L76 _protected member_ `TArray<ONNXTensorElementDataType> OutputTensorsORTType;`
- L78 _protected member_ `TArray<Ort::AllocatedStringPtr> InputTensorNameValues;`
- L79 _protected member_ `TArray<Ort::AllocatedStringPtr> OutputTensorNameValues;`
- L80 _protected member_ `TArray<char*> InputTensorNames;`
- L81 _protected member_ `TArray<char*> OutputTensorNames;`
- L83 _protected member_ `TArray<FTensor> InputTensors;`
- L84 _protected member_ `TArray<FTensor> OutputTensors;`

#### class `UE::NNERuntimeORT::Private::FModelInstanceORTCpu`  
`class FModelInstanceORTCpu : public FModelInstanceORTRunSync<NNE::IModelInstanceCPU, NNE::FTensorBindingCPU>`  
_L87-95_
- inherits: `FModelInstanceORTRunSync<NNE::IModelInstanceCPU,NNE::FTensorBindingCPU>`
- L90 _public function_ `FModelInstanceORTCpu(const FRuntimeConf& InRuntimeConf, TSharedRef<FEnvironment> InEnvironment) : FModelInstanceORTRunSync(InRuntimeConf, InEnvironment)`
- L91 _public prototype_ `virtual ~FModelInstanceORTCpu() = default;`
- L94 _private prototype_ `virtual bool InitializedAndConfigureMembers() override;`

#### class `UE::NNERuntimeORT::Private::FModelORTCpu`  
`class FModelORTCpu : public NNE::IModelCPU`  
_L97-108_
- inherits: `NNE::IModelCPU`
- L100 _public prototype_ `FModelORTCpu(TSharedRef<FEnvironment> InEnvironment, TSharedRef<UE::NNE::FSharedModelData> InModelData);`
- L101 _public prototype_ `virtual ~FModelORTCpu() = default;`
- L103 _public prototype_ `virtual TSharedPtr<NNE::IModelInstanceCPU> CreateModelInstanceCPU() override;`
- L106 _private member_ `TSharedRef<FEnvironment> Environment;`
- L107 _private member_ `TSharedRef<UE::NNE::FSharedModelData> ModelData;`

#### class `UE::NNERuntimeORT::Private::FModelORTDmlGPU`  
`class FModelORTDmlGPU : public NNE::IModelGPU`  
_L111-122_
- inherits: `NNE::IModelGPU`
- L114 _public prototype_ `FModelORTDmlGPU(TSharedRef<FEnvironment> InEnvironment, TSharedRef<UE::NNE::FSharedModelData> InModelData);`
- L115 _public prototype_ `virtual ~FModelORTDmlGPU() = default;`
- L117 _public prototype_ `virtual TSharedPtr<NNE::IModelInstanceGPU> CreateModelInstanceGPU() override;`
- L120 _private member_ `TSharedRef<FEnvironment> Environment;`
- L121 _private member_ `TSharedRef<UE::NNE::FSharedModelData> ModelData;`

#### class `UE::NNERuntimeORT::Private::FModelInstanceORTDmlGPU`  
`class FModelInstanceORTDmlGPU : public FModelInstanceORTRunSync<NNE::IModelInstanceGPU, NNE::FTensorBindingCPU>`  
_L124-132_
- inherits: `FModelInstanceORTRunSync<NNE::IModelInstanceGPU,NNE::FTensorBindingCPU>`
- L127 _public function_ `FModelInstanceORTDmlGPU(const FRuntimeConf& InRuntimeConf, TSharedRef<FEnvironment> InEnvironment) : FModelInstanceORTRunSync(InRuntimeConf, InEnvironment)`
- L128 _public prototype_ `virtual ~FModelInstanceORTDmlGPU() = default;`
- L131 _private prototype_ `virtual bool InitializedAndConfigureMembers() override;`

#### class `UE::NNERuntimeORT::Private::FModelORTDmlRDG`  
`class FModelORTDmlRDG : public NNE::IModelRDG`  
_L134-146_
- inherits: `NNE::IModelRDG`
- L137 _public prototype_ `FModelORTDmlRDG(TSharedRef<FEnvironment> InEnvironment, TSharedRef<UE::NNE::FSharedModelData> InModelData);`
- L139 _public prototype_ `virtual ~FModelORTDmlRDG() = default;`
- L141 _public prototype_ `virtual TSharedPtr<NNE::IModelInstanceRDG> CreateModelInstanceRDG() override;`
- L144 _private member_ `TSharedRef<FEnvironment> Environment;`
- L145 _private member_ `TSharedRef<UE::NNE::FSharedModelData> ModelData;`

#### class `UE::NNERuntimeORT::Private::FModelInstanceORTDmlRDG`  
`class FModelInstanceORTDmlRDG : public NNE::IModelInstanceRDG`  
_L148-180_
- inherits: `NNE::IModelInstanceRDG`
- L152 _public typedef_ `using ESetInputTensorShapesStatus = NNE::IModelInstanceRDG::ESetInputTensorShapesStatus;`
- L153 _public typedef_ `using EEnqueueRDGStatus = NNE::IModelInstanceRDG::EEnqueueRDGStatus;`
- L155 _public prototype_ `FModelInstanceORTDmlRDG(TSharedRef<UE::NNE::FSharedModelData> InModelData, const FRuntimeConf& InRuntimeConf, TSharedRef<FEnvironment> InEnvironment);`
- L157 _public prototype_ `virtual ~FModelInstanceORTDmlRDG();`
- L159 _public prototype_ `TConstArrayView<NNE::FTensorDesc> GetInputTensorDescs() const override;`
- L160 _public prototype_ `TConstArrayView<NNE::FTensorDesc> GetOutputTensorDescs() const override;`
- L161 _public prototype_ `TConstArrayView<NNE::FTensorShape> GetInputTensorShapes() const override;`
- L162 _public prototype_ `TConstArrayView<NNE::FTensorShape> GetOutputTensorShapes() const override;`
- L164 _public prototype_ `ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<NNE::FTensorShape> InInputShapes) override;`
- L165 _public prototype_ `ESetInputTensorShapesStatus SetInputTensorShapes_RenderThread(TConstArrayView<NNE::FTensorShape> InInputShapes);`
- L167 _public prototype_ `bool Init();`
- L169 _public prototype_ `EEnqueueRDGStatus EnqueueRDG(FRDGBuilder& GraphBuilder, TConstArrayView<NNE::FTensorBindingRDG> Inputs, TConstArrayView<NNE::FTensorBindingRDG> Outputs) override;`
- L172 _private member_ `TArray<NNE::FTensorShape> InputTensorShapes;` — Owned by Game/Render thread, copied for RHI thread
- L173 _private member_ `TArray<FTensor> InputTensors;` — Owned by Game/Render thread, copied for RHI thread
- L175 _private member_ `TArray<NNE::FTensorDesc> InitialInputSymbolicTensors;` — Copy for Game/Render Thread
- L176 _private member_ `TArray<NNE::FTensorDesc> InitialOutputSymbolicTensors;` — Copy for Game/Render Thread
- L179 _private member_ `TSharedPtr<FProxy> Proxy;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace NNERuntimeORT` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::NNERuntimeORT`)

### `Plugins/NNE/NNERuntimeORT/Source/NNERuntimeORT/Private/NNERuntimeORTModelFormat.h` (Private)


#### struct `UE::NNERuntimeORT::Private::FOnnxAdditionalDataDescriptor`  
`struct FOnnxAdditionalDataDescriptor`  
_L10-15_
- L12 _public member_ `FString Path;`
- L13 _public member_ `int64 Offset;`
- L14 _public member_ `int64 Size;`

#### struct `UE::NNERuntimeORT::Private::FOnnxDataDescriptor`  
`struct FOnnxDataDescriptor`  
_L25-30_
- L28 _public member_ `int64 OnnxModelDataSize = 0;`
- L29 _public member_ `TArray<FOnnxAdditionalDataDescriptor> AdditionalDataDescriptors;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeORT` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeORT`)
- L17 _function_ `FORCEINLINE FArchive& operator <<(FArchive& Ar, FOnnxAdditionalDataDescriptor& AdditionalDataDescriptor)` (scope `UE::NNERuntimeORT::Private`)
- L32 _function_ `FORCEINLINE FArchive& operator <<(FArchive& Ar, FOnnxDataDescriptor& OnnxDataDescriptor)` (scope `UE::NNERuntimeORT::Private`)

### `Plugins/NNE/NNERuntimeORT/Source/NNERuntimeORT/Private/NNERuntimeORTModule.h` (Private)


#### class `FNNERuntimeORTModule`  
`class FNNERuntimeORTModule : public IModuleInterface`  
_L19-34_
- inherits: `IModuleInterface`
- L22 _private member_ `TWeakObjectPtr<UNNERuntimeORTDmlProxy> NNERuntimeORTDml{ nullptr };`
- L23 _private member_ `TWeakObjectPtr<UNNERuntimeORTCpu> NNERuntimeORTCpu{ nullptr };`
- L25 _private prototype_ `virtual void StartupModule() override;`
- L26 _private prototype_ `virtual void ShutdownModule() override;`
- L29 _private prototype_ `void OnSettingsChanged(UObject* InObject, struct FPropertyChangedEvent& InPropertyChangedEvent);`
- L32 _private member_ `TArray<void*> DllHandles;`
- L33 _private member_ `TSharedPtr<UE::NNERuntimeORT::Private::FEnvironment> Environment;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace NNERuntimeORT` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::NNERuntimeORT`)

### `Plugins/NNE/NNERuntimeORT/Source/NNERuntimeORT/Private/NNERuntimeORTSettings.h` (Private)


#### enum `EExecutionMode`  
`enum EExecutionMode : uint8`  
_L11-15_
- reflection: `UENUM()`
- desc: An enum to represent denoiser NNE runtime type
- L13 _public enumerator_ `SEQUENTIAL`
- L14 _public enumerator_ `PARALLEL`

#### struct `FThreadingOptions`  
`struct FThreadingOptions`  
_L19-46_
- reflection: `USTRUCT()`
- desc: Threading options to configure glocal/local thread pools and exection mode
- L27 _public member_ `bool bUseGlobalThreadPool = false;` — `UPROPERTY(Config, EditAnywhere, Category = "ONNX Runtime", meta = ( DisplayName = "Use global thread pool", ToolTip = "Use global threadpools that will be shared across sessions."))` — Use global threadpools that will be shared across sessions
- L33 _public member_ `int32 IntraOpNumThreads = 0;` — `UPROPERTY(Config, EditAnywhere, Category = "ONNX Runtime", meta = ( DisplayName = "Intra-op thread count", ToolTip = "Set thread count of intra-op thread pool, which is utilized by ONNX Runtime to parallelize computation inside each operator.\nSpecial values:\n 0 = Use default thread count\n 1 = The invoking thread will be used; no threads will be created in the thread pool."))` — Thread count to parallelize the execution within nodes
- L39 _public member_ `int32 InterOpNumThreads = 0;` — `UPROPERTY(Config, EditAnywhere, Category = "ONNX Runtime", meta = ( DisplayName = "Inter-op thread count", ToolTip = "Set thread count of the inter-op thread pool, which enables parallelism between operators and will only be created when session execution mode set to parallel.\nSpecial values:\n 0 = Use default thread count\n 1 = The invoking thread will be used; no threads will be created in the thread pool."))` — Thread count used to parallelize the execution of the graph
- L45 _public member_ `TEnumAsByte<EExecutionMode> ExecutionMode = EExecutionMode::SEQUENTIAL;` — `UPROPERTY(Config, EditAnywhere, Category = "ONNX Runtime", meta = ( DisplayName = "Execution mode", ToolTip = "Controls whether multiple operators in the graph (across nodes) run sequentially or in parallel.\nNote: DirectML EP requires sequential execution and therefore ignores this setting."))` — Execution mode controls whether multiple operators in the graph (across nodes) run sequentially or in parallel

#### class `UNNERuntimeORTSettings`  
`class UNNERuntimeORTSettings : public UDeveloperSettings`  
_L50-73_
- reflection: `UCLASS(config = Engine, defaultconfig, meta = (DisplayName = "NNERuntimeORT"))`
- inherits: `UDeveloperSettings`
- desc: Settings used to configure NNERuntimeORT
- L54 _private prototype_ `UNNERuntimeORTSettings(const FObjectInitializer& ObjectInitlaizer);`
- L60 _public member_ `FThreadingOptions EditorThreadingOptions{true, 0, 0, EExecutionMode::SEQUENTIAL};` — `UPROPERTY(Config, EditAnywhere, Category = "ONNX Runtime", meta = (DisplayName = "Editor threading options", ToolTip = "Threading options in Editor targets", ConfigRestartRequired = true))` — Threading options in Editor targets
- L64 _public member_ `FThreadingOptions GameThreadingOptions{false, 1, 1, EExecutionMode::SEQUENTIAL};` — `UPROPERTY(Config, EditAnywhere, Category = "ONNX Runtime", meta = (DisplayName = "Game threading options", ToolTip = "Threading options in Non-Editor (Game, Program, ...) targets", ConfigRestartRequired = true))` — Threading options in Non-Editor (Game, Program, ...) targets
- L67 _public prototype_ `virtual FName GetCategoryName() const override;`
- L69 _public prototype_ `virtual FText GetSectionText() const override;`

### `Plugins/NNE/NNERuntimeORT/Source/NNERuntimeORT/Private/NNERuntimeORTTensor.h` (Private)


#### class `UE::NNERuntimeORT::Private::FTensor`  
`class FTensor`  
_L9-42_
- L12 _private member_ `NNE::FTensorShape Shape;`
- L13 _private member_ `uint64 DataSize = 0;`
- L15 _private prototype_ `FTensor() = default;`
- L18 _public function_ `const NNE::FTensorShape& GetShape() const`
- L23 _public function_ `uint64 GetDataSize() const`
- L28 _public function_ `static FTensor Make(const NNE::FTensorShape& InShape, ENNETensorDataType DataType)`
- L38 _public function_ `static FTensor MakeFromSymbolicDesc(const NNE::FTensorDesc& TensorDesc)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeORT` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeORT`)

### `Plugins/NNE/NNERuntimeORT/Source/NNERuntimeORT/Private/NNERuntimeORTUtils.h` (Private)


#### struct `UE::NNERuntimeORT::Private::TypeInfoORT`  
`struct TypeInfoORT`  
_L35-39_
- L37 _public member_ `ENNETensorDataType DataType = ENNETensorDataType::None;`
- L38 _public member_ `uint64 ElementSize = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNERuntimeORT` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::NNERuntimeORT`)
- L15 _prototype_ `bool IsRHID3D12Available();` (scope `UE::NNERuntimeORT::Private`)
- L17 _prototype_ `bool IsD3D12Available();` (scope `UE::NNERuntimeORT::Private`)
- L19 _namespace_ `namespace OrtHelper` (scope `UE::NNERuntimeORT::Private`)
- L21 _prototype_ `TArray<uint32> GetShape(const Ort::Value& OrtTensor);` (scope `UE::NNERuntimeORT::Private::OrtHelper`)
- L24 _prototype_ `GraphOptimizationLevel GetGraphOptimizationLevelForCPU(bool bIsOnline, bool bIsCooking = false);` (scope `UE::NNERuntimeORT::Private`)
- L26 _prototype_ `GraphOptimizationLevel GetGraphOptimizationLevelForDML(bool bIsOnline, bool bIsCooking = false);` (scope `UE::NNERuntimeORT::Private`)
- L28 _prototype_ `TUniquePtr<Ort::SessionOptions> CreateSessionOptionsDefault(const TSharedRef<FEnvironment> &Environment);` (scope `UE::NNERuntimeORT::Private`)
- L30 _prototype_ `TUniquePtr<Ort::SessionOptions> CreateSessionOptionsForDirectML(const TSharedRef<FEnvironment> &Environment, bool bRHID3D12Required = true);` (scope `UE::NNERuntimeORT::Private`)
- L32 _prototype_ `bool OptimizeModel(const TSharedRef<FEnvironment>& Environment, Ort::SessionOptions& SessionOptions, TConstArrayView64<uint8>& InputModel, TArray64<uint8>& OptimizedModel);` (scope `UE::NNERuntimeORT::Private`)
- L41 _prototype_ `TypeInfoORT TranslateTensorTypeORTToNNE(ONNXTensorElementDataType OrtDataType);` (scope `UE::NNERuntimeORT::Private`)
- L43 _prototype_ `uint64 CalcRDGBufferSizeForDirectML(uint64 DataSize);` (scope `UE::NNERuntimeORT::Private`)
- L45 _prototype_ `TUniquePtr<Ort::Session> CreateOrtSessionFromArray(const FEnvironment& Environment, TConstArrayView64<uint8> ModelBuffer, const Ort::SessionOptions& SessionOptions);` (scope `UE::NNERuntimeORT::Private`)
- L46 _prototype_ `TUniquePtr<Ort::Session> CreateOrtSession(const FEnvironment& Environment, const FString& ModelPath, const Ort::SessionOptions& SessionOptions);` (scope `UE::NNERuntimeORT::Private`)
