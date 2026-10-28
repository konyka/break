# Plugins / NNERuntimeIREE

- module root: `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREE`
- headers: 10; symbols: 244
- symbol kinds: class=18, enum=1, enumerator=4, function=8, member=83, namespace=29, prototype=84, struct=12, typedef=5
- PrivateDependencyModuleNames: Core, CoreUObject, DerivedDataCache, DeveloperSettings, Engine, IREE, IREEDriverRDG, IREEUtils, Json, NNE, NNEMlirTools, Projects, RHI, RenderCore, TargetPlatform

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREE/Internal/NNERuntimeIREELog.h` (Internal)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNERuntimeIREE, Log, All);`

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREE/Internal/NNERuntimeIREEMetaData.h` (Internal)


#### struct `UE::NNERuntimeIREE::FFunctionMetaData`  
`struct FFunctionMetaData`  
_L10-15_
- L12 _public member_ `FString Name;`
- L13 _public member_ `TArray<UE::NNE::FTensorDesc> InputDescs;`
- L14 _public member_ `TArray<UE::NNE::FTensorDesc> OutputDescs;`

#### class `UE::NNERuntimeIREE::FModuleMetaData`  
`class FModuleMetaData`  
_L17-26_
- L21 _public prototype_ `void Serialize(FArchive& Ar);`
- L23 _public prototype_ `bool ParseFromBuffer(TConstArrayView64<uint8> Buffer);`
- L25 _public member_ `TArray<UE::NNERuntimeIREE::FFunctionMetaData> FunctionMetaData;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeIREE` (scope `UE`)

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREE/Private/NNERuntimeIREE.h` (Private)


#### class `UNNERuntimeIREECpu`  
`class UNNERuntimeIREECpu : public UObject, public INNERuntime, public INNERuntimeCPU`  
_L23-63_
- reflection: `UCLASS()`
- inherits: `UObject,INNERuntime,INNERuntimeCPU`
- L29 _public member_ `static FGuid GUID;`
- L30 _public member_ `static int32 Version;`
- L32 _public prototype_ `void Init(TSharedRef<UE::NNERuntimeIREE::Private::FEnvironment> InEnvironment);`
- L35 _public prototype_ `virtual FString GetRuntimeName() const override;`
- L36 _public prototype_ `virtual ECanCreateModelDataStatus CanCreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L37 _public prototype_ `virtual TSharedPtr<UE::NNE::FSharedModelData> CreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) override;`
- L38 _public prototype_ `virtual FString GetModelDataIdentifier(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L39 _public prototype_ `virtual UObject* CreateDefaultRuntimeSettings() const override;`
- L43 _public prototype_ `virtual ECanCreateModelCPUStatus CanCreateModelCPU(const TObjectPtr<UNNEModelData> ModelData) const override;`
- L44 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelCPU> CreateModelCPU(const TObjectPtr<UNNEModelData> ModelData) override;`
- L48 _private member_ `TSharedPtr<UE::NNERuntimeIREE::Private::FEnvironment> Environment;`

#### class `UNNERuntimeIREEGpu`  
`class UNNERuntimeIREEGpu : public UObject, public INNERuntime, public INNERuntimeGPU`  
_L66-100_
- reflection: `UCLASS()`
- inherits: `UObject,INNERuntime,INNERuntimeGPU`
- L73 _public prototype_ `virtual FString GetRuntimeName() const override;`
- L74 _public prototype_ `virtual ECanCreateModelDataStatus CanCreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L75 _public prototype_ `virtual TSharedPtr<UE::NNE::FSharedModelData> CreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) override;`
- L76 _public prototype_ `virtual FString GetModelDataIdentifier(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L80 _public prototype_ `virtual ECanCreateModelGPUStatus CanCreateModelGPU(const TObjectPtr<UNNEModelData> ModelData) const override;`
- L81 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelGPU> CreateModelGPU(const TObjectPtr<UNNEModelData> ModelData) override;`
- L84 _public prototype_ `virtual bool IsAvailable() const;`
- L85 _public prototype_ `virtual FGuid GetGUID() const;`
- L86 _public prototype_ `virtual int32 GetVersion() const;`

#### class `UNNERuntimeIREECuda`  
`class UNNERuntimeIREECuda : public UNNERuntimeIREEGpu`  
_L103-122_
- reflection: `UCLASS()`
- inherits: `UNNERuntimeIREEGpu`
- L109 _public member_ `static FGuid GUID;`
- L110 _public member_ `static int32 Version;`
- L113 _public prototype_ `virtual FString GetRuntimeName() const override;`
- L117 _public prototype_ `virtual bool IsAvailable() const override;`
- L118 _public prototype_ `virtual FGuid GetGUID() const override;`
- L119 _public prototype_ `virtual int32 GetVersion() const override;`

#### class `UNNERuntimeIREEVulkan`  
`class UNNERuntimeIREEVulkan : public UNNERuntimeIREEGpu`  
_L125-144_
- reflection: `UCLASS()`
- inherits: `UNNERuntimeIREEGpu`
- L131 _public member_ `static FGuid GUID;`
- L132 _public member_ `static int32 Version;`
- L135 _public prototype_ `virtual FString GetRuntimeName() const override;`
- L139 _public prototype_ `virtual bool IsAvailable() const override;`
- L140 _public prototype_ `virtual FGuid GetGUID() const override;`
- L141 _public prototype_ `virtual int32 GetVersion() const override;`

#### class `UNNERuntimeIREERdg`  
`class UNNERuntimeIREERdg : public UObject, public INNERuntime, public INNERuntimeRDG`  
_L147-182_
- reflection: `UCLASS()`
- inherits: `UObject,INNERuntime,INNERuntimeRDG`
- L153 _public member_ `static FGuid GUID;`
- L154 _public member_ `static int32 Version;`
- L157 _public prototype_ `virtual FString GetRuntimeName() const override;`
- L158 _public prototype_ `virtual ECanCreateModelDataStatus CanCreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L159 _public prototype_ `virtual TSharedPtr<UE::NNE::FSharedModelData> CreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) override;`
- L160 _public prototype_ `virtual FString GetModelDataIdentifier(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L164 _public prototype_ `virtual ECanCreateModelRDGStatus CanCreateModelRDG(const TObjectPtr<UNNEModelData> ModelData) const override;`
- L165 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelRDG> CreateModelRDG(const TObjectPtr<UNNEModelData> ModelData) override;`
- L168 _public prototype_ `bool IsAvailable() const;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace NNERuntimeIREE` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::NNERuntimeIREE`)

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREE/Private/NNERuntimeIREECompiler.h` (Private)


#### struct `FNNERuntimeIREEArchitectureInfoCPU`  
`struct FNNERuntimeIREEArchitectureInfoCPU`  
_L14-35_
- reflection: `USTRUCT()`
- L19 _public member_ `FString Architecture;` — `UPROPERTY()`
- L22 _public member_ `TArray<FString> X86Features;` — `UPROPERTY()`
- L25 _public member_ `FString RelativeDirPath;` — `UPROPERTY()`
- L28 _public member_ `FString SharedLibraryFileName;` — `UPROPERTY()`
- L31 _public member_ `FString VmfbFileName;` — `UPROPERTY()`
- L34 _public member_ `FString SharedLibraryEntryPointName;` — `UPROPERTY()`

#### struct `FNNERuntimeIREECompilerResultCPU`  
`struct FNNERuntimeIREECompilerResultCPU`  
_L38-49_
- reflection: `USTRUCT()`
- L43 _public member_ `TArray<FNNERuntimeIREEArchitectureInfoCPU> ArchitectureInfos;` — `UPROPERTY()`
- L45 _public function_ `void Reset()`

#### struct `UE::NNERuntimeIREE::CPU::FBuildTarget`  
`struct FBuildTarget : public FJsonSerializable`  
_L56-71_
- inherits: `FJsonSerializable`
- L58 _public member_ `FString Name;`
- L59 _public member_ `FString Architecture;`
- L60 _public member_ `TArray<FString> X86Features;`
- L61 _public member_ `FString CompilerArguments;`
- L62 _public member_ `FString LinkerArguments;`

#### struct `UE::NNERuntimeIREE::CPU::FBuildConfig`  
`struct FBuildConfig : public FJsonSerializable`  
_L73-90_
- inherits: `FJsonSerializable`
- L75 _public member_ `TArray<FString> ImporterCommand;`
- L76 _public member_ `FString ImporterArguments;`
- L77 _public member_ `TArray<FString> CompilerCommand;`
- L78 _public member_ `TArray<FString> LinkerCommand;`
- L79 _public member_ `FString SharedLibExt;`
- L80 _public member_ `TArray<FBuildTarget> BuildTargets;`

#### class `UE::NNERuntimeIREE::CPU::FCompiler`  
`class FCompiler`  
_L92-114_
- L95 _private prototype_ `FCompiler(const FString& InImporterCommand, const FString& InImporterArguments, const FString& InCompilerCommand, const FString& InLinkerCommand, const FString& InSharedLibExt, TConstArrayView<FBuildTarget> InBuildTargets, const FMD5Hash& InHash);`
- L98 _public function_ `~FCompiler()`
- L99 _public prototype_ `static TUniquePtr<FCompiler> Make(const FString& InTargetPlatformName, const FNNERuntimeIREECpuCompilerSettings& CompilerSettings);`
- L102 _public function_ `const FMD5Hash& GetHash() const`
- L103 _public prototype_ `bool ImportOnnx(TConstArrayView<uint8> InFileData, const FString& InModelName, const FString& InOutputDir, TArray64<uint8>& OutMlirData);`
- L104 _public prototype_ `bool CompileMlir(TConstArrayView<uint8> InFileData, const FString& InModelName, const FString& InOutputDir, FNNERuntimeIREECompilerResultCPU& OutCompilerResult);`
- L107 _private member_ `FString ImporterCommand;`
- L108 _private member_ `FString ImporterArguments;`
- L109 _private member_ `FString CompilerCommand;`
- L110 _private member_ `FString LinkerCommand;`
- L111 _private member_ `FString SharedLibExt;`
- L112 _private member_ `TArray<FBuildTarget> BuildTargets;`
- L113 _private member_ `const FMD5Hash Hash;`

#### Free symbols / members of external scopes

- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace NNERuntimeIREE` (scope `UE`)
- L54 _namespace_ `namespace CPU` (scope `UE::NNERuntimeIREE`)

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREE/Private/NNERuntimeIREEEnvironment.h` (Private)


#### class `UE::NNERuntimeIREE::Private::FEnvironment`  
`class FEnvironment`  
_L25-51_
- desc: IREE Environment that holds global state, e.g. containing global thread pool etc.
- L33 _public prototype_ `FEnvironment();`
- L34 _public prototype_ `~FEnvironment();`
- L36 _public prototype_ `void Configure(const FConfig& InConfig);`
- L38 _public prototype_ `TArray<iree_task_executor_t*> GetTaskExecutors() const;`
- L40 _public function_ `FConfig GetConfig() const`
- L43 _private prototype_ `bool Create() const;`
- L45 _private member_ `FConfig Config{};`
- L48 _private member_ `mutable TUniquePtr<FInternalState> InternalState;`
- L50 _private member_ `mutable FCriticalSection CriticalSection;`

#### struct `UE::NNERuntimeIREE::Private::FEnvironment::FConfig`  
`struct FConfig`  
_L28-31_
- L30 _public member_ `FNNERuntimeIREEThreadingOptions ThreadingOptions;`

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef struct iree_status_handle_t* iree_status_t;`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace NNERuntimeIREE` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::NNERuntimeIREE`)
- L19 _prototype_ `iree_allocator_t MakeHostAllocator();` (scope `UE::NNERuntimeIREE::Private`) — Make IREE host allocator that uses Unreal Engine FMemory
- L22 _prototype_ `void PrintIREEError(const FString& InMessage, iree_status_t InStatus);` (scope `UE::NNERuntimeIREE::Private`) — Print IREE error formatted

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREE/Private/NNERuntimeIREEModel.h` (Private)


#### class `UE::NNERuntimeIREE::CPU::FModelInstance`  
`class FModelInstance : public UE::NNE::IModelInstanceCPU`  
_L31-54_
- inherits: `UE::NNE::IModelInstanceCPU`
- L34 _private prototype_ `FModelInstance(TSharedRef<UE::NNERuntimeIREE::CPU::Private::FSession> InSession);`
- L37 _public prototype_ `static TSharedPtr<FModelInstance> Make(TSharedRef<UE::NNERuntimeIREE::CPU::Private::FDevice> InDevice, TSharedRef<UE::NNERuntimeIREE::Private::FModule> InModule);`
- L40 _public typedef_ `using ESetInputTensorShapesStatus = UE::NNE::IModelInstanceCPU::ESetInputTensorShapesStatus;`
- L41 _public typedef_ `using ERunSyncStatus = UE::NNE::IModelInstanceCPU::ERunSyncStatus;`
- L44 _public prototype_ `virtual TConstArrayView<UE::NNE::FTensorDesc> GetInputTensorDescs() const override;`
- L45 _public prototype_ `virtual TConstArrayView<UE::NNE::FTensorDesc> GetOutputTensorDescs() const override;`
- L46 _public prototype_ `virtual TConstArrayView<UE::NNE::FTensorShape> GetInputTensorShapes() const override;`
- L47 _public prototype_ `virtual TConstArrayView<UE::NNE::FTensorShape> GetOutputTensorShapes() const override;`
- L48 _public prototype_ `virtual ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<UE::NNE::FTensorShape> InInputShapes) override;`
- L49 _public prototype_ `virtual ERunSyncStatus RunSync(TConstArrayView<UE::NNE::FTensorBindingCPU> InInputBindings, TConstArrayView<UE::NNE::FTensorBindingCPU> InOutputBindings) override;`
- L53 _private member_ `TSharedRef<UE::NNERuntimeIREE::CPU::Private::FSession> Session;`

#### class `UE::NNERuntimeIREE::CPU::FModel`  
`class FModel : public UE::NNE::IModelCPU`  
_L56-72_
- inherits: `UE::NNE::IModelCPU`
- L59 _private prototype_ `FModel(TSharedRef<UE::NNERuntimeIREE::CPU::Private::FDevice> InDevice, TSharedRef<UE::NNERuntimeIREE::Private::FModule> InModule);`
- L62 _public prototype_ `static TSharedPtr<FModel> Make(UE::NNERuntimeIREE::Private::FEnvironment& InEnvironment, const FString& InDirPath, const FString& InSharedLibraryFileName, const FString& InVmfbFileName, const FString& InLibraryQueryFunctionName, const FModuleMetaData& InModuleMetaData);`
- L66 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelInstanceCPU> CreateModelInstanceCPU() override;`
- L70 _private member_ `TSharedRef<UE::NNERuntimeIREE::CPU::Private::FDevice> Device;`
- L71 _private member_ `TSharedRef<UE::NNERuntimeIREE::Private::FModule> Module;`

#### class `UE::NNERuntimeIREE::RDG::FModelInstance`  
`class FModelInstance : public UE::NNE::IModelInstanceRDG`  
_L84-107_
- inherits: `UE::NNE::IModelInstanceRDG`
- L87 _private prototype_ `FModelInstance(TSharedRef<UE::NNERuntimeIREE::RDG::Private::FSession> InSession);`
- L90 _public prototype_ `static TSharedPtr<FModelInstance> Make(TSharedRef<UE::NNERuntimeIREE::RDG::Private::FDevice> InDevice, TSharedRef<UE::NNERuntimeIREE::Private::FModule> InModule);`
- L93 _public typedef_ `using ESetInputTensorShapesStatus = UE::NNE::IModelInstanceRDG::ESetInputTensorShapesStatus;`
- L94 _public typedef_ `using EEnqueueRDGStatus = UE::NNE::IModelInstanceRDG::EEnqueueRDGStatus;`
- L97 _public prototype_ `virtual TConstArrayView<UE::NNE::FTensorDesc> GetInputTensorDescs() const override;`
- L98 _public prototype_ `virtual TConstArrayView<UE::NNE::FTensorDesc> GetOutputTensorDescs() const override;`
- L99 _public prototype_ `virtual TConstArrayView<UE::NNE::FTensorShape> GetInputTensorShapes() const override;`
- L100 _public prototype_ `virtual TConstArrayView<UE::NNE::FTensorShape> GetOutputTensorShapes() const override;`
- L101 _public prototype_ `virtual ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<UE::NNE::FTensorShape> InInputShapes) override;`
- L102 _public prototype_ `virtual EEnqueueRDGStatus EnqueueRDG(FRDGBuilder& RDGBuilder, TConstArrayView<UE::NNE::FTensorBindingRDG> InInputBindings, TConstArrayView<UE::NNE::FTensorBindingRDG> InOutputBindings) override;`
- L106 _private member_ `TSharedRef<UE::NNERuntimeIREE::RDG::Private::FSession> Session;`

#### class `UE::NNERuntimeIREE::RDG::FModel`  
`class FModel : public UE::NNE::IModelRDG`  
_L109-125_
- inherits: `UE::NNE::IModelRDG`
- L112 _private prototype_ `FModel(TSharedRef<UE::NNERuntimeIREE::RDG::Private::FDevice> InDevice, TSharedRef<UE::NNERuntimeIREE::Private::FModule> InModule);`
- L115 _public prototype_ `static TSharedPtr<FModel> Make(const FString& InDirPath, TConstArrayView64<uint8> VmfbData, const FModuleMetaData& InModuleMetaData, const TMap<FString, TConstArrayView<uint8>>& Executables);`
- L119 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelInstanceRDG> CreateModelInstanceRDG() override;`
- L123 _private member_ `TSharedRef<UE::NNERuntimeIREE::RDG::Private::FDevice> Device;`
- L124 _private member_ `TSharedRef<UE::NNERuntimeIREE::Private::FModule> Module;`

#### Free symbols / members of external scopes

- L13 _prototype_ `LLM_DECLARE_TAG(NNERuntimeIREE_Cpu);`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace NNERuntimeIREE` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::NNERuntimeIREE`)
- L23 _namespace_ `namespace CPU` (scope `UE::NNERuntimeIREE`)
- L25 _namespace_ `namespace Private` (scope `UE::NNERuntimeIREE::CPU`)
- L76 _namespace_ `namespace RDG` (scope `UE::NNERuntimeIREE`)
- L78 _namespace_ `namespace Private` (scope `UE::NNERuntimeIREE::RDG`)

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREE/Private/NNERuntimeIREEModelData.h` (Private)


#### class `UE::NNERuntimeIREE::CPU::Private::FModelData`  
`class FModelData`  
_L17-71_
- desc: IREECpu model data class.
- L25 _public prototype_ `bool Load(TConstArrayView64<uint8> Data);` — Loads this model from Data that was produced using the Store method @return true if loading was successfull, false otherwise, this leaves the object in an undefined state
- L32 _public prototype_ `bool Store(TArray64<uint8>& Data);` — Serializes this model into Data @return true if storing was successfull, false otherwise
- L37 _public prototype_ `static bool IsSameGuidAndVersion(TConstArrayView64<uint8> Data, FGuid Guid, int32 Version);` — Check data for matching Guid and Version without deserializing everything.
- L42 _public member_ `FGuid GUID;` — A Guid that uniquely identifies this IREE model data.
- L47 _public member_ `int32 Version;` — Current version of this IREE model data.
- L52 _public member_ `FGuid FileId;` — A Guid that uniquely identifies the model.
- L57 _public member_ `FModuleMetaData ModuleMetaData;` — Module meta data.
- L62 _public member_ `FNNERuntimeIREECompilerResultCPU CompilerResult;` — Compiler output.
- L67 _public member_ `FMD5Hash CompilerHash;` — Hash of the compiler that created CompilerResult
- L70 _private prototype_ `void Serialize(FArchive& Ar);`

#### struct `UE::NNERuntimeIREE::RDG::Private::FModelDataHeader`  
`struct FModelDataHeader`  
_L80-108_
- desc: IREERdg model data header struct.
- L82 _public prototype_ `void Serialize(FArchive& Ar);`
- L87 _public member_ `FGuid GUID;` — A Guid that uniquely identifies this IREE model data.
- L92 _public member_ `int32 Version = 0;` — Current version of this IREE model data.
- L97 _public member_ `FGuid FileId;` — A Guid that uniquely identifies the model.
- L102 _public member_ `TArray<FString> ShaderPlatforms;` — List of shader platforms supported by this IREE model data.
- L107 _public member_ `FMD5Hash CompilerHash;` — Hash of the compiler that created CompilerResult

#### class `UE::NNERuntimeIREE::RDG::Private::FModelData`  
`class FModelData`  
_L113-152_
- desc: IREERdg model data class.
- L121 _public prototype_ `bool Load(TConstArrayView64<uint8> Data);` — Loads this model from Data that was produced using the Store method @return true if loading was successfull, false otherwise, this leaves the object in an undefined state
- L128 _public prototype_ `bool Store(TArray64<uint8>& Data);` — Serializes this model into Data @return true if storing was successfull, false otherwise
- L133 _public prototype_ `static bool ReadHeaderAndIsSameGuidAndVersion(FArchive& Ar, FGuid Guid, int32 Version, FModelDataHeader& OutHeader);` — Gets Header without loading entire ModelData and checks for matching Guid and Version
- L138 _public member_ `FModelDataHeader Header;` — Model data header.
- L143 _public member_ `FModuleMetaData ModuleMetaData;` — Module meta data.
- L148 _public member_ `FIREECompilerRDGResult CompilerResult;` — Compiler output.
- L151 _private prototype_ `void Serialize(FArchive& Ar);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace NNERuntimeIREE` (scope `UE`)
- L12 _namespace_ `namespace CPU` (scope `UE::NNERuntimeIREE`)
- L12 _namespace_ `namespace Private` (scope `UE::NNERuntimeIREE::CPU`)
- L75 _namespace_ `namespace UE`
- L75 _namespace_ `namespace NNERuntimeIREE` (scope `UE`)
- L75 _namespace_ `namespace RDG` (scope `UE::NNERuntimeIREE`)
- L75 _namespace_ `namespace Private` (scope `UE::NNERuntimeIREE::RDG`)

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREE/Private/NNERuntimeIREEModule.h` (Private)


#### class `FNNERuntimeIREEModule`  
`class FNNERuntimeIREEModule : public IModuleInterface`  
_L13-29_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private member_ `void* DllHandle{};`
- L23 _private member_ `TWeakObjectPtr<UNNERuntimeIREECpu> NNERuntimeIREECpu;`
- L24 _private member_ `TWeakObjectPtr<UNNERuntimeIREECuda> NNERuntimeIREECuda;`
- L25 _private member_ `TWeakObjectPtr<UNNERuntimeIREEVulkan> NNERuntimeIREEVulkan;`
- L26 _private member_ `TWeakObjectPtr<UNNERuntimeIREERdg> NNERuntimeIREERdg;`
- L27 _private member_ `TSharedPtr<UE::NNERuntimeIREE::Private::FEnvironment> Environment;`

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREE/Private/NNERuntimeIREESettings.h` (Private)


#### enum `ENNERuntimeIREEThreadingAffinityGroupSpecifierType`  
`enum class ENNERuntimeIREEThreadingAffinityGroupSpecifierType : uint8`  
_L12-18_
- reflection: `UENUM()`
- desc: Specifies the thread affinity group type
- L14 _public enumerator_ `Index UMETA(DisplayName = "Specify group by index")`
- L15 _public enumerator_ `Current UMETA(DisplayName = "Use same group as calling thread")`
- L16 _public enumerator_ `All UMETA(DisplayName = "Use all groups")`
- L17 _public enumerator_ `Any UMETA(DisplayName = "Use any group")`

#### struct `FNNERuntimeIREEThreadingAffinity`  
`struct FNNERuntimeIREEThreadingAffinity`  
_L22-43_
- reflection: `USTRUCT()`
- desc: Specifies the processor affinity for a particular thread given by processor group the thread should be assigned to (aka NUMA node, cluster etc., depending on the platform) and the processor it should be scheduled on
- L30 _public member_ `ENNERuntimeIREEThreadingAffinityGroupSpecifierType GroupSpecifierType = ENNERuntimeIREEThreadingAffinityGroupSpecifierType::Any;` — `UPROPERTY(Config, EditAnywhere, Category = "IREE Runtime", meta = ( DisplayName = "Group specifier", ToolTip = "Specify the group (type) the thread should be assigned to."))` — How is the group specified?
- L36 _public member_ `int32 GroupIndex = -1;` — `UPROPERTY(Config, EditAnywhere, Category = "IREE Runtime", meta = ( DisplayName = "Group index", ToolTip = "Specify with an index the group the thread should be assigned to. Only used if group specifier type is 'Index'."))` — Group index, only used if node specifier type is 'Index'
- L42 _public member_ `int32 CoreIndex = -1;` — `UPROPERTY(Config, EditAnywhere, Category = "IREE Runtime", meta = ( DisplayName = "Logical core index", ToolTip = "Specify with an index the logical core the thread should be scheduled on. Set to -1 to let the thread be scheduled on any core."))` — Logical core index

#### struct `FNNERuntimeIREETaskTopology`  
`struct FNNERuntimeIREETaskTopology`  
_L47-56_
- reflection: `USTRUCT()`
- desc: Specifies the task topology used for multi-threading
- L55 _public member_ `TArray<FNNERuntimeIREEThreadingAffinity> TaskTopologyGroups;` — `UPROPERTY(Config, EditAnywhere, Category = "IREE Runtime", meta = ( DisplayName = "Task topology groups", ToolTip = "Specify the task system topology with zero or more groups. If empty, the runtime will try to use all physical cores."))` — Task topology groups

#### struct `FNNERuntimeIREEThreadingOptions`  
`struct FNNERuntimeIREEThreadingOptions`  
_L60-75_
- reflection: `USTRUCT()`
- desc: Threading options to configure single/multi-threading, including task topology for multi-threading case
- L68 _public member_ `bool bIsSingleThreaded = true;` — `UPROPERTY(Config, EditAnywhere, Category = "IREE Runtime", meta = ( DisplayName = "Is single threaded", ToolTip = "Should the runtime run single threaded (might result in better performance with very small models)."))` — Run single threaded?
- L74 _public member_ `FNNERuntimeIREETaskTopology TaskTopology;` — `UPROPERTY(Config, EditAnywhere, Category = "IREE Runtime", meta = ( DisplayName = "Task topology", ToolTip = "For multi-threading you can specify the task system topology."))` — Task topology used for multi-threading

#### class `UNNERuntimeIREESettings`  
`class UNNERuntimeIREESettings : public UDeveloperSettings`  
_L79-102_
- reflection: `UCLASS(config = Engine, defaultconfig, meta = (DisplayName = "NNERuntimeIREE"))`
- inherits: `UDeveloperSettings`
- desc: Settings used to configure NNERuntimeIREE
- L83 _private prototype_ `UNNERuntimeIREESettings(const FObjectInitializer& ObjectInitlaizer);`
- L89 _public member_ `FNNERuntimeIREEThreadingOptions EditThreadingOptions{};` — `UPROPERTY(Config, EditAnywhere, Category = "IREE Runtime", meta = (DisplayName = "Editor threading options", ToolTip = "Threading options in Editor targets", ConfigRestartRequired = true))` — Threading options in Editor targets
- L93 _public member_ `FNNERuntimeIREEThreadingOptions GameThreadingOptions{};` — `UPROPERTY(Config, EditAnywhere, Category = "IREE Runtime", meta = (DisplayName = "Game threading options", ToolTip = "Threading options in Non-Editor (Game, Program, ...) targets", ConfigRestartRequired = true))` — Threading options in Non-Editor (Game, Program, ...) targets
- L96 _public prototype_ `virtual FName GetCategoryName() const override;`
- L98 _public prototype_ `virtual FText GetSectionText() const override;`

#### struct `FNNERuntimeIREECpuCompilerFlags`  
`struct FNNERuntimeIREECpuCompilerFlags`  
_L106-127_
- reflection: `USTRUCT()`
- desc: NNERuntimeIREECpu compiler flag settings
- L114 _public member_ `FString Platform;` — `UPROPERTY(EditAnywhere, Category = "IREE Runtime", meta = ( DisplayName = "Platform", ToolTip = "The Platform the flags should be applied to, or leave empty to apply to all."))` — The Platform the flags should be applied to, or leave empty to apply to all
- L120 _public member_ `FString Target;` — `UPROPERTY(EditAnywhere, Category = "IREE Runtime", meta = ( DisplayName = "Target", ToolTip = "The name of the target these flags should be applied to, or leave empty to apply to all."))` — The name of the target these flags should be applied to, or leave empty to apply to all
- L126 _public member_ `FString Flags;` — `UPROPERTY(EditAnywhere, Category = "IREE Runtime", meta = ( DisplayName = "Flags", ToolTip = "The flags that get appended to the iree compiler arguments on the specified platform and target."))` — The flags that get appended to the iree compiler arguments on the specified platform and target

#### struct `FNNERuntimeIREECpuCompilerSettings`  
`struct FNNERuntimeIREECpuCompilerSettings`  
_L131-141_
- reflection: `USTRUCT()`
- desc: NNERuntimeIREECpu compiler settings
- L140 _public member_ `TArray<FNNERuntimeIREECpuCompilerFlags> CompilerFlags;` — `UPROPERTY(EditAnywhere, Category = "IREE Runtime", meta = ( DisplayName = "Compiler Flags", ToolTip = "List of compiler flags. The flags of the first item that has the correct platform and target get appended to the existing iree compiler arguments.", TitleProperty="{Platform}, {Target}: {Flags}"))` — NNERuntimeIREECpu compiler flag settings

#### class `UNNERuntimeIREECpuSettings`  
`class UNNERuntimeIREECpuSettings : public UObject`  
_L145-157_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: RuntimeSettings for NNERuntimeIREECpu
- L156 _public member_ `FNNERuntimeIREECpuCompilerSettings CompilerSettings;` — `UPROPERTY(EditAnywhere, Category = "IREE Runtime", meta = ( DisplayName = "Compiler settings", ToolTip = "Settings to configure compilation.", NoResetToDefault))` — NNERuntimeIREECpu compiler settings

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREE/Private/NNERuntimeIREETensor.h` (Private)


#### class `UE::NNERuntimeIREE::Private::FTensor`  
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
- L7 _namespace_ `namespace NNERuntimeIREE` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeIREE`)
