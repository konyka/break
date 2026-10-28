# Plugins / NNERuntimeCoreML

- module root: `Plugins/Experimental/NNERuntimeCoreML/Source/NNERuntimeCoreML`
- headers: 6; symbols: 98
- symbol kinds: class=12, enum=1, enumerator=2, function=10, member=17, namespace=10, prototype=44, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, NNE, NNERuntimeCoreMLUtils, Projects

### `Plugins/Experimental/NNERuntimeCoreML/Source/NNERuntimeCoreML/Internal/NNERuntimeCoreMLLog.h` (Internal)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNERuntimeCoreML, Log, All);`

### `Plugins/Experimental/NNERuntimeCoreML/Source/NNERuntimeCoreML/Private/NNERuntimeCoreML.h` (Private)


#### class `UNNERuntimeCoreML`  
`class UNNERuntimeCoreML : public UObject, public INNERuntime`  
_L16-41_
- reflection: `UCLASS()`
- inherits: `UObject,INNERuntime`
- L21 _public prototype_ `virtual ~UNNERuntimeCoreML() = default;`
- L24 _public member_ `static FGuid GUID;`
- L25 _public member_ `static int32 Version;`
- L28 _public prototype_ `virtual FString GetRuntimeName() const override;`
- L29 _public prototype_ `virtual ECanCreateModelDataStatus CanCreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L30 _public prototype_ `virtual TSharedPtr<UE::NNE::FSharedModelData> CreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) override;`
- L31 _public prototype_ `virtual FString GetModelDataIdentifier(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L35 _public function_ `virtual FString GetRuntimeName() const override`
- L36 _public function_ `virtual ECanCreateModelDataStatus CanCreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override`
- L37 _public function_ `virtual TSharedPtr<UE::NNE::FSharedModelData> CreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) override`
- L38 _public function_ `virtual FString GetModelDataIdentifier(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override`

#### class `UNNERuntimeCoreMLCpuGpu`  
`class UNNERuntimeCoreMLCpuGpu : public UNNERuntimeCoreML, public INNERuntimeCPU, public INNERuntimeGPU`  
_L44-72_
- reflection: `UCLASS()`
- inherits: `UNNERuntimeCoreML,INNERuntimeCPU,INNERuntimeGPU`
- L49 _public prototype_ `virtual ~UNNERuntimeCoreMLCpuGpu() = default;`
- L53 _public prototype_ `virtual ECanCreateModelCPUStatus CanCreateModelCPU(const TObjectPtr<UNNEModelData> ModelData) const override;`
- L54 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelCPU> CreateModelCPU(const TObjectPtr<UNNEModelData> ModelData) override;`
- L58 _public prototype_ `virtual ECanCreateModelGPUStatus CanCreateModelGPU(const TObjectPtr<UNNEModelData> ModelData) const override;`
- L59 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelGPU> CreateModelGPU(const TObjectPtr<UNNEModelData> ModelData) override;`
- L63 _public function_ `virtual ECanCreateModelCPUStatus CanCreateModelCPU(const TObjectPtr<UNNEModelData> ModelData) const override`
- L64 _public function_ `virtual TSharedPtr<UE::NNE::IModelCPU> CreateModelCPU(const TObjectPtr<UNNEModelData> ModelData) override`
- L68 _public function_ `virtual ECanCreateModelGPUStatus CanCreateModelGPU(const TObjectPtr<UNNEModelData> ModelData) const override`
- L69 _public function_ `virtual TSharedPtr<UE::NNE::IModelGPU> CreateModelGPU(const TObjectPtr<UNNEModelData> ModelData) override`

#### class `UNNERuntimeCoreMLCpuGpuNpu`  
`class UNNERuntimeCoreMLCpuGpuNpu : public UNNERuntimeCoreMLCpuGpu, public INNERuntimeNPU`  
_L75-93_
- reflection: `UCLASS()`
- inherits: `UNNERuntimeCoreMLCpuGpu,INNERuntimeNPU`
- L80 _public prototype_ `virtual ~UNNERuntimeCoreMLCpuGpuNpu() = default;`
- L84 _public prototype_ `virtual ECanCreateModelNPUStatus CanCreateModelNPU(const TObjectPtr<UNNEModelData> ModelData) const override;`
- L85 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelNPU> CreateModelNPU(const TObjectPtr<UNNEModelData> ModelData) override;`
- L89 _public function_ `virtual ECanCreateModelNPUStatus CanCreateModelNPU(const TObjectPtr<UNNEModelData> ModelData) const override`
- L90 _public function_ `virtual TSharedPtr<UE::NNE::IModelNPU> CreateModelNPU(const TObjectPtr<UNNEModelData> ModelData) override`

### `Plugins/Experimental/NNERuntimeCoreML/Source/NNERuntimeCoreML/Private/NNERuntimeCoreMLModel.h` (Private)


#### class `UE::NNERuntimeCoreML::Private::FModelInstanceCoreMLBase`  
`template <class InstanceType> class FModelInstanceCoreMLBase : public InstanceType`  
_L26-54_
- inherits: `InstanceType`
- L29 _public prototype_ `FModelInstanceCoreMLBase() = default;`
- L30 _public prototype_ `virtual ~FModelInstanceCoreMLBase();`
- L32 _public typedef_ `using ESetInputTensorShapesStatus = UE::NNE::IModelInstanceCPU::ESetInputTensorShapesStatus;`
- L33 _public typedef_ `using ERunSyncStatus = UE::NNE::IModelInstanceCPU::ERunSyncStatus;`
- L35 _public prototype_ `bool Init(TConstArrayView64<uint8> ModelData);`
- L37 _public prototype_ `virtual TConstArrayView<NNE::FTensorDesc> GetInputTensorDescs() const override;`
- L38 _public prototype_ `virtual TConstArrayView<NNE::FTensorDesc> GetOutputTensorDescs() const override;`
- L39 _public prototype_ `virtual TConstArrayView<NNE::FTensorShape> GetInputTensorShapes() const override;`
- L40 _public prototype_ `virtual TConstArrayView<NNE::FTensorShape> GetOutputTensorShapes() const override;`
- L41 _public prototype_ `virtual ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<NNE::FTensorShape> InInputShapes) override;`
- L42 _public prototype_ `virtual ERunSyncStatus RunSync(TConstArrayView<NNE::FTensorBindingCPU> InInputTensors, TConstArrayView<NNE::FTensorBindingCPU> InOutputTensors) override;`
- L45 _private member_ `TArray<NNE::FTensorShape> InputTensorShapes;`
- L46 _private member_ `TArray<NNE::FTensorShape> OutputTensorShapes;`
- L47 _private member_ `TArray<NNE::FTensorDesc> InputSymbolicTensors;`
- L48 _private member_ `TArray<NNE::FTensorDesc> OutputSymbolicTensors;`
- L50 _private member_ `TArray<FString> InputFeatureNames;`
- L51 _private member_ `TArray<FString> OutputFeatureNames;`
- L52 _private member_ `MLModel * CoreMLModelInstance;`

#### class `UE::NNERuntimeCoreML::Private::FModelInstanceCoreMLCpu`  
`class FModelInstanceCoreMLCpu : public FModelInstanceCoreMLBase<NNE::IModelInstanceCPU>`  
_L56-61_
- inherits: `FModelInstanceCoreMLBase<NNE::IModelInstanceCPU>`
- L59 _public prototype_ `FModelInstanceCoreMLCpu() = default;`
- L60 _public prototype_ `virtual ~FModelInstanceCoreMLCpu() = default;`

#### class `UE::NNERuntimeCoreML::Private::FModelInstanceCoreMLGpu`  
`class FModelInstanceCoreMLGpu : public FModelInstanceCoreMLBase<NNE::IModelInstanceGPU>`  
_L63-68_
- inherits: `FModelInstanceCoreMLBase<NNE::IModelInstanceGPU>`
- L66 _public prototype_ `FModelInstanceCoreMLGpu() = default;`
- L67 _public prototype_ `virtual ~FModelInstanceCoreMLGpu() = default;`

#### class `UE::NNERuntimeCoreML::Private::FModelInstanceCoreMLNpu`  
`class FModelInstanceCoreMLNpu : public FModelInstanceCoreMLBase<NNE::IModelInstanceNPU>`  
_L70-75_
- inherits: `FModelInstanceCoreMLBase<NNE::IModelInstanceNPU>`
- L73 _public prototype_ `FModelInstanceCoreMLNpu() = default;`
- L74 _public prototype_ `virtual ~FModelInstanceCoreMLNpu() = default;`

#### class `UE::NNERuntimeCoreML::Private::FModelCoreMLCpu`  
`class FModelCoreMLCpu : public NNE::IModelCPU`  
_L77-87_
- inherits: `NNE::IModelCPU`
- L80 _public prototype_ `FModelCoreMLCpu(TSharedRef<NNE::FSharedModelData> InModelData);`
- L81 _public prototype_ `virtual ~FModelCoreMLCpu() = default;`
- L83 _public prototype_ `virtual TSharedPtr<NNE::IModelInstanceCPU> CreateModelInstanceCPU() override;`
- L86 _private member_ `TSharedRef<NNE::FSharedModelData> ModelData;`

#### class `UE::NNERuntimeCoreML::Private::FModelCoreMLGpu`  
`class FModelCoreMLGpu : public NNE::IModelGPU`  
_L89-99_
- inherits: `NNE::IModelGPU`
- L92 _public prototype_ `FModelCoreMLGpu(TSharedRef<NNE::FSharedModelData> InModelData);`
- L93 _public prototype_ `virtual ~FModelCoreMLGpu() = default;`
- L95 _public prototype_ `virtual TSharedPtr<NNE::IModelInstanceGPU> CreateModelInstanceGPU() override;`
- L98 _private member_ `TSharedRef<NNE::FSharedModelData> ModelData;`

#### class `UE::NNERuntimeCoreML::Private::FModelCoreMLNpu`  
`class FModelCoreMLNpu : public NNE::IModelNPU`  
_L101-111_
- inherits: `NNE::IModelNPU`
- L104 _public prototype_ `FModelCoreMLNpu(TSharedRef<NNE::FSharedModelData> InModelData);`
- L105 _public prototype_ `virtual ~FModelCoreMLNpu() = default;`
- L107 _public prototype_ `virtual TSharedPtr<NNE::IModelInstanceNPU> CreateModelInstanceNPU() override;`
- L110 _private member_ `TSharedRef<NNE::FSharedModelData> ModelData;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace NNE` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace NNERuntimeCoreML` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::NNERuntimeCoreML`)

### `Plugins/Experimental/NNERuntimeCoreML/Source/NNERuntimeCoreML/Private/NNERuntimeCoreMLModelData.h` (Private)


#### enum `UE::NNERuntimeCoreML::EModelType`  
`enum class EModelType : uint8`  
_L10-14_
- L12 _public enumerator_ `MLModel`
- L13 _public enumerator_ `MLPackage`

#### class `UE::NNERuntimeCoreML::FModelData`  
`class FModelData`  
_L16-33_
- L19 _public member_ `FGuid GUID;`
- L21 _public member_ `int32 Version = 0;`
- L23 _public member_ `EModelType ModelType = EModelType::MLModel;`
- L26 _public member_ `TConstArrayView64<uint8> FileDataView;` — Non-owning view into file data. On saving, copy of file data is written. When loading, points to source passed to Load().
- L28 _public prototype_ `bool Load(TConstArrayView64<uint8> InData);`
- L30 _public prototype_ `bool Store(TArray64<uint8>& OutData);`
- L32 _public prototype_ `bool CheckGUIDAndVersion(const FGuid& ReferenceGUID, int32 ReferenceVersion) const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeCoreML` (scope `UE`)

### `Plugins/Experimental/NNERuntimeCoreML/Source/NNERuntimeCoreML/Private/NNERuntimeCoreMLModule.h` (Private)


#### class `FNNERuntimeCoreMLModule`  
`class FNNERuntimeCoreMLModule : public IModuleInterface`  
_L14-23_
- inherits: `IModuleInterface`
- L18 _private member_ `TWeakObjectPtr<UNNERuntimeCoreML> NNERuntimeCoreML{ nullptr };`
- L21 _private prototype_ `virtual void StartupModule() override;`
- L22 _private prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/NNERuntimeCoreML/Source/NNERuntimeCoreML/Private/NNERuntimeCoreMLNPUHelper.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace NNERuntimeCoreML` (scope `UE`)
- L5 _namespace_ `namespace Private` (scope `UE::NNERuntimeCoreML`)
- L8 _prototype_ `bool IsNPUAvailable();` (scope `UE::NNERuntimeCoreML::Private`)
