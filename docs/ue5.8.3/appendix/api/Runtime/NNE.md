# Runtime / NNE

- module root: `Source/Runtime/NNE`
- headers: 10; symbols: 210
- symbol kinds: class=24, enum=6, enumerator=37, function=12, member=20, namespace=20, prototype=77, struct=2, typedef=12
- DynamicallyLoadedModuleNames: NNEEditor
- PrivateDependencyModuleNames: Core, CoreUObject, DerivedDataCache

### `Source/Runtime/NNE/Public/NNE.h` (Public)


#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNE, Log, All);`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace NNE` (scope `UE`)
- L16 _typedef_ `using ERegisterRuntimeStatus = EResultStatus;` (scope `UE::NNE`)
- L17 _typedef_ `using EUnregisterRuntimeStatus = EResultStatus;` (scope `UE::NNE`)
- L27 _prototype_ `ERegisterRuntimeStatus RegisterRuntime(TWeakInterfacePtr<INNERuntime> Runtime);` (scope `UE::NNE`) — Register a runtime to make it accessible to NNE clients. The caller needs to keep a strong pointer to the runtime object to prevent it from being garbage collected. @param Runtime A weak interface pointer to the runtime to be registered. @return Status indicating success or failure (e.g. if the runtime already has been registered).
- L35 _prototype_ `EUnregisterRuntimeStatus UnregisterRuntime(TWeakInterfacePtr<INNERuntime> Runtime);` (scope `UE::NNE`) — Unregister a registered runtime. @param Runtime A weak interface pointer to the runtime to be unregistered. @return Status indicating success or failure (e.g. if the runtime has not been registered).
- L42 _prototype_ `TArray<FString> GetAllRuntimeNames();` (scope `UE::NNE`) — List and return all registered runtime names. @return An array containing runtime names of all registered runtimes.
- L52 _prototype_ `TWeakInterfacePtr<INNERuntime> GetRuntime(const FString& Name);` (scope `UE::NNE`) — Find and return a runtime by name. This function tries to find a runtime by name. @param Name The name of the runtime. @return A weak pointer to the runtime if it has been found or an invalid pointer otherwise.
- L63 _function_ `template<class T> TWeakInterfacePtr<T> GetRuntime(const FString& Name)` (scope `UE::NNE`) — Find and return a runtime by name and interface. This function tries to find a runtime by name and casts it to the interface passed as template argument (e.g. INNERuntime, INNERuntimeCPU or INNERuntimeRDG). @param Name The name of the runtime. @return A weak pointer to the runtime if it has been found and implements the interface in the template argument or an invalid pointer otherwise.
- L78 _function_ `template<class T> TArray<FString> GetAllRuntimeNames()` (scope `UE::NNE`) — List and return all registered runtime names that implement the provided interface. @return An array containing runtime names of all registered runtimes that implement the interface in the template argument.
- L82 _function_ `` (scope `UE::NNE::GetAllRuntimeNames`)

### `Source/Runtime/NNE/Public/NNEModelData.h` (Public)


#### class `UE::NNE::FSharedModelData`  
`class FSharedModelData`  
_L20-62_
- desc: This class implements a reference counted view on an immutable memory buffer representing model data. It allows runtimes to reference results of GetModelData() even if they outlive UNNEModelData.
- L30 _public prototype_ `FSharedModelData(FSharedBuffer InData, uint32 InMemoryAlignment);` — Constructor to shared model data. @param InData The shared buffer containing the model data. InData must be owned and the memory aligned with InMemoryAlignment. @param InMemoryAlignment The memory alignment with which InData has been aligned. A value <= 1 indicates arbitrary memory alignment.
- L35 _public prototype_ `FSharedModelData();` — Constructor to create empty data.
- L42 _public prototype_ `TConstArrayView64<uint8> GetView() const;` — Get a const array view on the shared data which is guaranteed to remain valid as long as this objects exists. @return A const array view of the shared data.
- L49 _public prototype_ `uint32 GetMemoryAlignment() const;` — Get the memory alignment with which the data has been aligned. @return Memory alignment with which the data has been aligned. A value <= 1 indicates arbitrary memory alignment.
- L56 _private member_ `FSharedBuffer Data;` — The shared buffer containing the model data. Data must be aligned with MemoryAlignment.
- L61 _private member_ `uint32 MemoryAlignment;` — The memory alignment with which Data has been aligned. A value <= 1 indicates arbitrary memory alignment.

#### class `UNNEModelData`  
`class UNNEModelData : public UObject`  
_L73-278_
- reflection: `UCLASS(BlueprintType, Category = "NNE", MinimalAPI)`
- inherits: `UObject`
- desc: This class represents assets that store neural network model data. Neural network models typically consist of a graph of operations and corresponding parameters as e.g. weights. UNNEModelData assets store such model data as imported e.g. by the UNNEModelDataFactory class. An INNERuntime object retrieved by UE::NNE::GetRuntime<T>(const FString& Name) can be used to create an inferable neural network model.
- L107 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;` — UObject interface
- L108 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L128 _public prototype_ `TArrayView<const FString> GetTargetRuntimes() const;` — In editor: Get the target runtimes this model data will be cooked for. An empty list means all runtimes. In standalone: An empty list. @return The target runtimes names.
- L135 _public prototype_ `void SetTargetRuntimes(TArrayView<const FString> RuntimeNames);` — Set the target runtimes this model data will be cooked for. An empty list means all runtimes. @param RuntimeNames The target runtimes names.
- L145 _public prototype_ `FString GetFileType() const;` — Get the type of data inside FileData. In editor: The FileType identifies the type of data inside FileData and typically is the extension of the file used to create the asset. In standalone: An empty string. @return The FileType.
- L155 _public prototype_ `TConstArrayView64<uint8> GetFileData() const;` — Get read only access to FileData. In editor: The FileData contains the binary data of the file which has been used to create the asset. In standalone: An empty array. @return The FileData.
- L165 _public prototype_ `TConstArrayView64<uint8> GetAdditionalFileData(const FString& Key) const;` — Get read only access to AdditionalFileData. In editor: The AdditionalFileData contains the additional binary data of the neural network model. In standalone: An empty map. @return The AdditionalFileData with a given Key if it exists and an empty view in standalone or when the key does not exist.
- L172 _public prototype_ `void ClearFileDataAndFileType();` — Clears the FileData and the FileType. Caution, if the FileData is cleared, no more models can be created on runtimes that do not already have ModelData inside this asset.
- L184 _public prototype_ `static EDeserializeRuntimeSettings DeserializeRuntimeSettings(const TMap<FString, TConstArrayView64<uint8>>& InAdditionalFileData, UObject& InOutSettings);` — Uses AdditionalFileData that is passed into CanCreateModelData and CreateModelData to populate InOutSettings @param InAdditionalFileData The AdditionalFileData argument that was passed into INNERuntime::CanCreateModelData or INNERuntime::CreateModelData @param InOutSettings An instance of the RuntimeSettings that is returned from INNERuntime::CreateDefaultRuntimeSettings. If the user hasn't changed the runtime settings this will be unchanged. Else InOutSettings will be deserialized. On failure the value of InOutSettings is undefined. @return Status of deserializing the settings.
- L194 _public prototype_ `EGetRuntimeSettingsStatus GetRuntimeSettings(const FString& InRuntimeName, UObject*& OutSettings) const;` — Gets the setting of the given runtime. @param InRuntimeName The name of the runtime whose setting to get. @param OutSettings On success points to the created settings. On Failure OutSettings is left unchanged. @return Status of getting the setting.
- L204 _public prototype_ `ESetRuntimeSettingsStatus SetRuntimeSettings(const FString& InRuntimeName, UObject& InSettings);` — Sets the setting of the given runtime. @param InRuntimeName The name of the runtime whose setting to set. @param InSettings The setting to set. This needs to have the same type as gets returned by the runtime through INNERuntime::CreateDefaultRuntimeSettings(). @return Status of setting the setting.
- L214 _public prototype_ `FGuid GetFileId() const;` — Get the FGuid identifying the FileData. The FileId is created on import of an asset. It can be used to identify the FileData, e.g. when putting corresponding data into the DDC or caching data locally. In standalone: An empty FGuid. @return The FileId.
- L224 _public prototype_ `TSharedPtr<UE::NNE::FSharedModelData> GetModelData(const FString& RuntimeName);` — Get the cached (editor) or cooked (game) optimized model data for a given runtime. This function is used by runtimes when creating a model. In editor, the function will create the optimized model data with the passed runtime in case it has not been cached in the DCC yet. In game, the cooked data is accessed. The returned model data is aligned in memory as requested by the runtime. @param RuntimeName The name of the runtime for which the data should be returned. @return The optimized and runtime specific model data or an invalid TSharedPtr in case of failure.
- L231 _public prototype_ `void ClearModelData();` — Clears the ModelData. Caution, if the ModelData is cleared, only runtimes that support cooking on the current platform can create new models from this asset.
- L237 _private member_ `TArray<FString> TargetRuntimes;` — A list of string of the supported runtime, empty to support them all.
- L242 _private member_ `FString FileType;` — A string identifying the type of data inside this asset. Corresponds to the extension of the imported file.
- L247 _private member_ `TArray64<uint8> FileData;` — The raw binary file data of the imported model.
- L252 _private member_ `TMap<FString, TArray64<uint8>> AdditionalFileData;` — Additional raw binary data of the imported model.
- L257 _private member_ `TMap<FString, TArray64<uint8>> RuntimeSettings;` — Mapping between a runtime name and the serialized version of it's runtime settings.
- L262 _private member_ `FGuid FileId;` — A Guid that uniquely identifies this model. This is used to cache optimized models in the editor.
- L267 _private member_ `TMap<FString, TSharedPtr<UE::NNE::FSharedModelData>> ModelData;` — The processed / optimized model data for the different runtimes.
- L272 _private prototype_ `TSharedPtr<UE::NNE::FSharedModelData> CreateModelData(const FString& RuntimeName, const ITargetPlatform* TargetPlatform) const;` — Helper method for creating shared model data
- L277 _private member_ `static inline const FString RuntimeSettingsKeyPrefix = TEXT("Run` — Prefix of the key that stores serialized runtime settings in the version of AdditionalFileData that is passed into INNERuntime::CanCreateModelData and INNERuntime::CreateModelData

#### enum `UNNEModelData::EDeserializeRuntimeSettings`  
`enum class EDeserializeRuntimeSettings : uint8`  
_L79-85_
- L81 _public enumerator_ `Success = 0`
- L82 _public enumerator_ `InvalidCustomVersion = 1`
- L83 _public enumerator_ `NewerCustomVersion = 2`
- L84 _public enumerator_ `SerializationError = 3`

#### enum `UNNEModelData::EGetRuntimeSettingsStatus`  
`enum class EGetRuntimeSettingsStatus : uint8`  
_L87-95_
- L89 _public enumerator_ `Success = 0`
- L90 _public enumerator_ `RuntimeNotFound = 1`
- L91 _public enumerator_ `RuntimeUnsupported = 2`
- L92 _public enumerator_ `InvalidCustomVersion = 3`
- L93 _public enumerator_ `NewerCustomVersion = 4`
- L94 _public enumerator_ `SerializationError = 5`

#### enum `UNNEModelData::ESetRuntimeSettingsStatus`  
`enum class ESetRuntimeSettingsStatus : uint8`  
_L97-104_
- L99 _public enumerator_ `Success = 0`
- L100 _public enumerator_ `RuntimeNotFound = 1`
- L101 _public enumerator_ `RuntimeUnsupported = 2`
- L102 _public enumerator_ `WrongSettingType = 3`
- L103 _public enumerator_ `SerializationError = 4`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NNE` (scope `UE`)

### `Source/Runtime/NNE/Public/NNERuntime.h` (Public)


#### class `UNNERuntime`  
`class UNNERuntime : public UInterface`  
_L20-23_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `INNERuntime`  
`class INNERuntime`  
_L32-97_
- desc: The base interface of a neural network runtime. This interface is mainly used internally by UNNEModelData to cook a model given in a file format (e.g. .onnx) into runtime specific model data. The model data is then stored inside UNNEModelData which then can be used in game to create an inferable model. See INNERuntimeCPU, INNERuntimeGPU and INNERuntimeRDG on how to create a model given a UNNEModelData asset.
- L50 _public prototype_ `virtual FString GetRuntimeName() const = 0;` — Get the name of the runtime. @return The name of the runtime.
- L62 _public prototype_ `virtual ECanCreateModelDataStatus CanCreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const = 0;` — Check if the runtime is able to create model data given some file data representing a neural network. @param FileType The type of file inside FileData. Corresponds to the file extension (e.g. 'onnx'). @param FileData The raw binary file of a neural network model. @param AdditionalFileData Additional raw binary data of the neural network model. Can be passed to UNNEModelData::DeserializeRuntimeSettings. @param FileId The unique identifier representing FileData. @param TargetPlatform The Interface identifying the target platform for which the data needs to be created. A null pointer indicates the currently compiled/running platform. @return Ok if the runtime is able to create model data, FailFileIdNotSupported if this fileId is not supported and Fail otherwise.
- L74 _public prototype_ `virtual TSharedPtr<UE::NNE::FSharedModelData> CreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) = 0;` — Create model data given some raw file data. @param FileType The type of file inside FileData. Corresponds to the file extension (e.g. 'onnx'). @param FileData The raw binary file of a neural network model. @param AdditionalFileData Additional raw binary data of the neural network model. Can be passed to UNNEModelData::DeserializeRuntimeSettings. @param FileId The unique identifier representing FileData. @param TargetPlatform The Interface identifying the target platform for which the data needs to be created. A null pointer indicates the currently compiled/running platform. @return A pointer to data representing the runtime specific representation of the model to be stored by UNNEModelData on success or an invalid pointer otherwise.
- L86 _public prototype_ `virtual FString GetModelDataIdentifier(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const = 0;` — Get an id uniquely identifying the model data. This is used by UNNEModelData to create a FCacheKey to get and add the model data from and to a DDC. @param FileType The type of file inside FileData. Corresponds to the file extension (e.g. 'onnx'). @param FileData The raw binary file of a neural network model. @param AdditionalFileData Additional raw binary data of the neural network model. @param FileId The unique identifier representing FileData. @param TargetPlatform The Interface identifying the target platform for which the data is produced or by which it will be consumed. A null pointer indicates the currently compiled/running platform. @return A string that identifies the model data uniquely, e.g. by containing the FileId, model data version and target platform display name.
- L93 _public function_ `virtual UObject* CreateDefaultRuntimeSettings() const` — Create an instance of the default runtime settings. The Serialize(FArchive& Ar) and GetClass() methods are used to store and display these settings. @return A new instance of the runtime settings or nullptr if runtime settings are not supported by this runtime.

#### enum `INNERuntime::ECanCreateModelDataStatus`  
`enum class ECanCreateModelDataStatus : uint8`  
_L38-43_
- L40 _public enumerator_ `Ok = 0`
- L41 _public enumerator_ `Fail = 1`
- L42 _public enumerator_ `FailFileIdNotSupported = 2`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace NNE` (scope `UE`)

### `Source/Runtime/NNE/Public/NNERuntimeCPU.h` (Public)


#### class `UE::NNE::IModelInstanceCPU`  
`class IModelInstanceCPU : public IModelInstanceRunSync`  
_L22-24_
- inherits: `IModelInstanceRunSync`
- desc: The interface of a model instance that can run on CPU. Use UE::NNE::IModelCPU::CreateModelInstance() to get a model instance. Use UE::NNE::GetRuntime<INNERuntimeCPU>(RuntimeName) to get a runtime capable of creating CPU models.

#### class `UE::NNE::IModelCPU`  
`class IModelCPU`  
_L31-46_
- desc: The interface of a model capable of creating model instance that can run on CPU. Use UE::NNE::GetRuntime<INNERuntimeCPU>(RuntimeName) to get a runtime capable of creating CPU models.
- L35 _public prototype_ `virtual ~IModelCPU() = default;`
- L45 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelInstanceCPU> CreateModelInstanceCPU() = 0;` — Create a model instance for inference The runtime have the opportunity to share the model weights among multiple IModelInstanceCPU created from an IModelCPU instance, however this is not mandatory. The caller can decide to convert the result into a shared pointer if required (e.g. if the model needs to be shared with an async task for evaluation). @return A caller owned model representing the neural network instance created.

#### class `UNNERuntimeCPU`  
`class UNNERuntimeCPU : public UInterface`  
_L51-54_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `INNERuntimeCPU`  
`class INNERuntimeCPU`  
_L61-88_
- desc: The interface of a neural network runtime capable of creating CPU models. Call UE::NNE::GetRuntime<INNERuntimeCPU>(RuntimeName) to get a runtime implementing this interface.
- L67 _public typedef_ `using ECanCreateModelCPUStatus = UE::NNE::EResultStatus;`
- L75 _public prototype_ `virtual ECanCreateModelCPUStatus CanCreateModelCPU(const TObjectPtr<UNNEModelData> ModelData) const = 0;` — Check if the runtime is able to create a model given some ModelData. @param ModelData The model data for which to create a model. @return True if the runtime is able to create the model, false otherwise.
- L87 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelCPU> CreateModelCPU(const TObjectPtr<UNNEModelData> ModelData) = 0;` — Create a model given some ModelData. The caller must make sure ModelData remains valid throughout the call. ModelData is not required anymore after the model has been created. The caller can decide to convert the result into a shared pointer if required (e.g. if the model needs to be shared with an async task for evaluation). @param ModelData The model data for which to create a model. @return A caller owned model representing the neural network created from ModelData.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NNE` (scope `UE`)

### `Source/Runtime/NNE/Public/NNERuntimeGPU.h` (Public)


#### class `UE::NNE::IModelInstanceGPU`  
`class IModelInstanceGPU : public IModelInstanceRunSync`  
_L24-26_
- inherits: `IModelInstanceRunSync`
- desc: The interface of a model instance that can run on GPU. Use UE::NNE::IModelGPU::CreateModelInstance() to get a model instance. Use UE::NNE::GetRuntime<INNERuntimeGPU>(RuntimeName) to get a runtime capable of creating GPU models.

#### class `UE::NNE::IModelGPU`  
`class IModelGPU`  
_L33-48_
- desc: The interface of a model capable of creating model instance that can run on GPU. Use UE::NNE::GetRuntime<INNERuntimeGPU>(RuntimeName) to get a runtime capable of creating GPU models.
- L37 _public prototype_ `virtual ~IModelGPU() = default;`
- L47 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelInstanceGPU> CreateModelInstanceGPU() = 0;` — Create a model instance for inference The runtime have the opportunity to share the model weights among multiple IModelInstanceGPU created from an IModelGPU instance, however this is not mandatory. The caller can decide to convert the result into a shared pointer if required (e.g. if the model needs to be shared with an async task for evaluation). @return A caller owned model representing the neural network instance created.

#### class `UNNERuntimeGPU`  
`class UNNERuntimeGPU : public UInterface`  
_L53-56_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `INNERuntimeGPU`  
`class INNERuntimeGPU`  
_L63-90_
- desc: The interface of a neural network runtime capable of creating GPU models. Call UE::NNE::GetRuntime<INNERuntimeGPU>(RuntimeName) to get a runtime implementing this interface.
- L69 _public typedef_ `using ECanCreateModelGPUStatus = UE::NNE::EResultStatus;`
- L77 _public prototype_ `virtual ECanCreateModelGPUStatus CanCreateModelGPU(const TObjectPtr<UNNEModelData> ModelData) const = 0;` — Check if the runtime is able to create a model given some ModelData. @param ModelData The model data for which to create a model. @return True if the runtime is able to create the model, false otherwise.
- L89 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelGPU> CreateModelGPU(const TObjectPtr<UNNEModelData> ModelData) = 0;` — Create a model given some ModelData. The caller must make sure ModelData remains valid throughout the call. ModelData is not required anymore after the model has been created. The caller can decide to convert the result into a shared pointer if required (e.g. if the model needs to be shared with an async task for evaluation). @param ModelData The model data for which to create a model. @return A caller owned model representing the neural network created from ModelData.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NNE` (scope `UE`)
- L16 _typedef_ `typedef FTensorBindingCPU FTensorBindingGPU;` (scope `UE::NNE`) — `UE_DEPRECATED(5.5, "Use UE::NNE::FTensorBindingCPU instead.")`

### `Source/Runtime/NNE/Public/NNERuntimeNPU.h` (Public)


#### class `UE::NNE::IModelInstanceNPU`  
`class IModelInstanceNPU : public IModelInstanceRunSync`  
_L22-24_
- inherits: `IModelInstanceRunSync`
- desc: The interface of a model instance that can run on NPU. Use UE::NNE::IModelNPU::CreateModelInstance() to get a model instance. Use UE::NNE::GetRuntime<INNERuntimeNPU>(RuntimeName) to get a runtime capable of creating NPU models.

#### class `UE::NNE::IModelNPU`  
`class IModelNPU`  
_L31-46_
- desc: The interface of a model capable of creating model instance that can run on NPU. Use UE::NNE::GetRuntime<INNERuntimeNPU>(RuntimeName) to get a runtime capable of creating NPU models.
- L35 _public prototype_ `virtual ~IModelNPU() = default;`
- L45 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelInstanceNPU> CreateModelInstanceNPU() = 0;` — Create a model instance for inference The runtime have the opportunity to share the model weights among multiple IModelInstanceNPU created from an IModelNPU instance, however this is not mandatory. The caller can decide to convert the result into a shared pointer if required (e.g. if the model needs to be shared with an async task for evaluation). @return A caller owned model representing the neural network instance created.

#### class `UNNERuntimeNPU`  
`class UNNERuntimeNPU : public UInterface`  
_L51-54_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `INNERuntimeNPU`  
`class INNERuntimeNPU`  
_L61-88_
- desc: The interface of a neural network runtime capable of creating NPU models. Call UE::NNE::GetRuntime<INNERuntimeNPU>(RuntimeName) to get a runtime implementing this interface.
- L67 _public typedef_ `using ECanCreateModelNPUStatus = UE::NNE::EResultStatus;`
- L75 _public prototype_ `virtual ECanCreateModelNPUStatus CanCreateModelNPU(const TObjectPtr<UNNEModelData> ModelData) const = 0;` — Check if the runtime is able to create a model given some ModelData. @param ModelData The model data for which to create a model. @return True if the runtime is able to create the model, false otherwise.
- L87 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelNPU> CreateModelNPU(const TObjectPtr<UNNEModelData> ModelData) = 0;` — Create a model given some ModelData. The caller must make sure ModelData remains valid throughout the call. ModelData is not required anymore after the model has been created. The caller can decide to convert the result into a shared pointer if required (e.g. if the model needs to be shared with an async task for evaluation). @param ModelData The model data for which to create a model. @return A caller owned model representing the neural network created from ModelData.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NNE` (scope `UE`)

### `Source/Runtime/NNE/Public/NNERuntimeRDG.h` (Public)


#### struct `UE::NNE::FTensorBindingRDG`  
`struct FTensorBindingRDG`  
_L27-30_
- desc: The tensor binding for passing input and output to IModelRDG. Memory is owned by the caller. The caller must make sure the buffer is large enough.
- L29 _public member_ `FRDGBufferRef Buffer;`

#### class `UE::NNE::IModelInstanceRDG`  
`class IModelInstanceRDG`  
_L38-106_
- desc: The interface of a model instance that can run on RDG. Use UE::NNE::IModelRDG::CreateModelInstance() to get a model instance. Use UE::NNE::GetRuntime<INNERuntimeRDG>(RuntimeName) to get a runtime capable of creating RDG models.
- L42 _public typedef_ `using ESetInputTensorShapesStatus = EResultStatus;`
- L43 _public typedef_ `using EEnqueueRDGStatus = EResultStatus;`
- L45 _public prototype_ `virtual ~IModelInstanceRDG() = default;`
- L52 _public prototype_ `virtual TConstArrayView<FTensorDesc> GetInputTensorDescs() const = 0;` — Get the input tensor descriptions as defined by the model, potentially with variable dimensions. @return An array containing a tensor descriptor for each input tensor of the model.
- L59 _public prototype_ `virtual TConstArrayView<FTensorDesc> GetOutputTensorDescs() const = 0;` — Get the output tensor descriptions as defined by the model, potentially with variable dimensions. @return An array containing a tensor descriptor for each output tensor of the model.
- L68 _public prototype_ `virtual TConstArrayView<FTensorShape> GetInputTensorShapes() const = 0;` — Get the input shapes. SetInputTensorShapes must be called prior of running a model. @return An array of input shapes or an empty array if SetInputTensorShapes has not been called.
- L78 _public prototype_ `virtual TConstArrayView<FTensorShape> GetOutputTensorShapes() const = 0;` — Getters for outputs shapes if they were already resolved. Output shapes might be resolved after a call to SetInputTensorShapes if the model and runtime supports it. Otherwise they will be resolved while running the model @return An array of output shapes or an empty array if not resolved yet.
- L91 _public prototype_ `virtual ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<FTensorShape> InInputShapes) = 0;` — Prepare the model to be run with the given input shape. The call is mandatory before a model can be run. This function might be called from the render thread, if not it is up to the caller to ensure thread safety. The function will run shape inference and resolve, if possible, the output shapes which can then be accessed by calling GetOutputTensorShapes(). This is a potentially expensive call and should be called lazily if possible. @param InInputShapes The input shapes to prepare the model with. @return Status indicating success or failure.
- L105 _public prototype_ `virtual EEnqueueRDGStatus EnqueueRDG(FRDGBuilder& RDGBuilder, TConstArrayView<FTensorBindingRDG> Inputs, TConstArrayView<FTensorBindingRDG> Outputs) = 0;` — Enqueue the model graph to a FRDGBuilder. This function must be called from the render thread. SetInputTensorShapes must be called prior to this call. The caller owns the memory inside the bindings and must make sure that they are big enough. @param RDGBuilder The RDG builder to which the neural network operations are enqueued. @param InInputTensors An array containing tensor bindings for each input tensor with caller owned memory containing the input data. @param InOutputTensors An array containing tensor bindings for each output tensor with caller owned memory big enough to contain the results on success. @return Status indicating success or failure.

#### class `UE::NNE::IModelRDG`  
`class IModelRDG`  
_L113-128_
- desc: The interface of a model capable of creating model instance that can run on RDG. Use UE::NNE::GetRuntime<INNERuntimeRDG>(RuntimeName) to get a runtime capable of creating RDG models.
- L117 _public prototype_ `virtual ~IModelRDG() = default;`
- L127 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelInstanceRDG> CreateModelInstanceRDG() = 0;` — Create a model instance for inference The runtime have the opportunity to share the model weights among multiple IModelInstanceRDG created from an IModelRDG instance, however this is not mandatory. The caller can decide to convert the result into a shared pointer if required (e.g. if the model needs to be shared with an async task for evaluation). @return A caller owned model representing the neural network instance created.

#### class `UNNERuntimeRDG`  
`class UNNERuntimeRDG : public UInterface`  
_L133-136_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `INNERuntimeRDG`  
`class INNERuntimeRDG`  
_L143-170_
- desc: The interface of a neural network runtime capable of creating RDG models. Call UE::NNE::GetRuntime<INNERuntimeRDG>(RuntimeName) to get a runtime implementing this interface.
- L149 _public typedef_ `using ECanCreateModelRDGStatus = UE::NNE::EResultStatus;`
- L157 _public prototype_ `virtual ECanCreateModelRDGStatus CanCreateModelRDG(const TObjectPtr<UNNEModelData> ModelData) const = 0;` — Check if the runtime is able to create a model given some ModelData. @param ModelData The model data for which to create a model. @return True if the runtime is able to create the model, false otherwise.
- L169 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelRDG> CreateModelRDG(const TObjectPtr<UNNEModelData> ModelData) = 0;` — Create a model given some ModelData. The caller must make sure ModelData remains valid throughout the call. ModelData is not required anymore after the model has been created. The caller can decide to convert the result into a shared pointer if required (e.g. if the model needs to be shared with the render thread). @param ModelData The model data for which to create a model. @return A caller owned model representing the neural network created from ModelData.

#### Free symbols / members of external scopes

- L13 _typedef_ `using FRDGBufferRef = FRDGBuffer*;`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace NNE` (scope `UE`)

### `Source/Runtime/NNE/Public/NNERuntimeRunSync.h` (Public)


#### struct `UE::NNE::FTensorBindingCPU`  
`struct FTensorBindingCPU`  
_L18-22_
- desc: The tensor binding for passing input and output to from CPU memory. Memory is owned by the caller. The caller must make sure the buffer is large enough and at least as large as SizeInBytes.
- L20 _public member_ `void* Data;`
- L21 _public member_ `uint64 SizeInBytes;`

#### class `UE::NNE::IModelInstanceRunSync`  
`class IModelInstanceRunSync`  
_L30-97_
- desc: The interface of a model instance that can run synchronously from CPU memory. Use UE::NNE::IModelXXX::CreateModelInstance() to get a model instance. Use UE::NNE::GetRuntime<INNERuntimeXXX>(RuntimeName) to get a runtime capable of creating models.
- L34 _public typedef_ `using ESetInputTensorShapesStatus = EResultStatus;`
- L35 _public typedef_ `using ERunSyncStatus = EResultStatus;`
- L37 _public prototype_ `virtual ~IModelInstanceRunSync() = default;`
- L44 _public prototype_ `virtual TConstArrayView<FTensorDesc> GetInputTensorDescs() const = 0;` — Get the input tensor descriptions as defined by the model, potentially with variable dimensions. @return An array containing a tensor descriptor for each input tensor of the model.
- L51 _public prototype_ `virtual TConstArrayView<FTensorDesc> GetOutputTensorDescs() const = 0;` — Get the output tensor descriptions as defined by the model, potentially with variable dimensions. @return An array containing a tensor descriptor for each output tensor of the model.
- L60 _public prototype_ `virtual TConstArrayView<FTensorShape> GetInputTensorShapes() const = 0;` — Get the input shapes. SetInputTensorShapes must be called prior of running a model. @return An array of input shapes or an empty array if SetInputTensorShapes has not been called.
- L70 _public prototype_ `virtual TConstArrayView<FTensorShape> GetOutputTensorShapes() const = 0;` — Getters for outputs shapes if they were already resolved. Output shapes might be resolved after a call to SetInputTensorShapes if the model and runtime supports it. Otherwise they will be resolved while running the model @return An array of output shapes or an empty array if not resolved yet.
- L82 _public prototype_ `virtual ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<FTensorShape> InInputShapes) = 0;` — Prepare the model to be run with the given input shape. The call is mandatory before a model can be run. The function will run shape inference and resolve, if possible, the output shapes which can then be accessed by calling GetOutputTensorShapes(). This is a potentially expensive call and should be called lazily if possible. @param InInputShapes The input shapes to prepare the model with. @return Status indicating success or failure.
- L96 _public prototype_ `virtual ERunSyncStatus RunSync(TConstArrayView<FTensorBindingCPU> InInputTensors, TConstArrayView<FTensorBindingCPU> InOutputTensors) = 0;` — Evaluate the model synchronously. SetInputTensorShapes must be called prior to this call. This function will block the calling thread until the inference is complete. The caller owns the memory inside the bindings and must make sure that they are big enough. Clients can call this function from an async task but must make sure the memory remains valid throughout the evaluation. @param InInputTensors An array containing tensor bindings for each input tensor with caller owned memory containing the input data. @param InOutputTensors An array containing tensor bindings for each output tensor with caller owned memory big enough to contain the results on success. @return Status indicating success or failure.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNE` (scope `UE`)

### `Source/Runtime/NNE/Public/NNEStatus.h` (Public)


#### enum `UE::NNE::EResultStatus`  
`enum class EResultStatus : uint8`  
_L10-14_
- L12 _public enumerator_ `Ok = 0`
- L13 _public enumerator_ `Fail = 1`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNE` (scope `UE`)

### `Source/Runtime/NNE/Public/NNETypes.h` (Public)


#### enum `ENNETensorDataType`  
`enum class ENNETensorDataType : uint8`  
_L15-34_
- reflection: `UENUM()`
- desc: The enum lists all tensor data types used in NNE. See UE::NNE::GetTensorDataTypeSizeInBytes(ENNETensorDataType InType) to get the size of each data type in bytes.
- L17 _public enumerator_ `None` — For empty tensors
- L18 _public enumerator_ `Char` — Character type
- L19 _public enumerator_ `Boolean` — Boolean type
- L20 _public enumerator_ `Half` — 16-bit floating number
- L21 _public enumerator_ `Float` — 32-bit floating number
- L22 _public enumerator_ `Double` — 64-bit floating number
- L23 _public enumerator_ `Int8` — 8-bit signed integer
- L24 _public enumerator_ `Int16` — 16-bit signed integer
- L25 _public enumerator_ `Int32` — 32-bit signed integer
- L26 _public enumerator_ `Int64` — 64-bit signed integer
- L27 _public enumerator_ `UInt8` — 8-bit unsigned integer
- L28 _public enumerator_ `UInt16` — 16-bit unsigned integer
- L29 _public enumerator_ `UInt32` — 32-bit unsigned integer
- L30 _public enumerator_ `UInt64` — 64-bit unsigned integer
- L31 _public enumerator_ `Complex64` — 64-bit Complex Number
- L32 _public enumerator_ `Complex128` — 128-bit Complex Number
- L33 _public enumerator_ `BFloat16` — 16-bit floating number

#### class `UE::NNE::FSymbolicTensorShape`  
`class FSymbolicTensorShape`  
_L51-126_
- desc: A symbolic tensor shape represents the shape of a tensor with potentially variable dimension. The variable dimensions are represented by -1 values.
- L57 _public member_ `constexpr static int32 MaxRank = 8;` — The maximum number of dimensions supported by the symbolic tensor shape, aka the rank.
- L60 _private member_ `TArray<int32, TInlineAllocator<MaxRank>> Data;`
- L66 _public prototype_ `FSymbolicTensorShape() = default;` — Default construct a symbolic tensor shape.
- L73 _public prototype_ `FSymbolicTensorShape(const FSymbolicTensorShape& OtherShape) = default;` — Construct this symbolic tensor shape from another one. @param OtherShape the other symbolic tensor shape to copy from.
- L81 _public prototype_ `static FSymbolicTensorShape Make(TConstArrayView<int32> Data);` — Construct a symbolic tensor shape with the given dimensions. @param Data an array of dimensions. @return a symbolic tensor shape with the given dimensions.
- L88 _public function_ `inline TConstArrayView<int32> GetData() const` — Get the dimensions of the symbolic tensor shape. @return a view on the dimensions of the symbolic tensor shape.
- L95 _public function_ `inline int32 Rank() const` — Get the number of dimensions of the symbolic tensor shape, aka the rank. @return the number of dimensions of the symbolic tensor shape.
- L102 _public prototype_ `bool IsConcrete() const;` — Check if the symbolic tensor shape has no variable dimensions, aka is concrete. @return true if the symbolic tensor shape is concrete, false otherwise.
- L110 _public prototype_ `bool operator==(const FSymbolicTensorShape& OtherShape) const;` — Check if the symbolic tensor shape is equal to another one. @param OtherShape the other symbolic tensor shape. @return true if the symbolic tensor shape is equal to the other one, false otherwise.
- L118 _public prototype_ `bool operator!=(const FSymbolicTensorShape& OtherShape) const;` — Check if the symbolic tensor shape is different from another one. @param OtherShape the other symbolic tensor shape. @return true if the symbolic tensor shape is different from the other one, false otherwise.
- L125 _public prototype_ `void operator=(const FSymbolicTensorShape& OtherShape);` — Assign this symbolic tensor shape from another one. @param OtherShape the other symbolic tensor shape to copy from.

#### class `UE::NNE::FTensorShape`  
`class FTensorShape`  
_L133-225_
- desc: The concrete shape of a tensor. Concrete tensor shapes are well defined through strictly positive values and thus have a defined volume.
- L139 _public member_ `constexpr static int32 MaxRank = FSymbolicTensorShape::MaxRank;` — The maximum number of dimensions supported by the tensor shape, aka the rank.
- L142 _private member_ `TArray<uint32, TInlineAllocator<MaxRank>> Data;`
- L148 _public prototype_ `FTensorShape() = default;` — Default construct a tensor shape.
- L154 _public prototype_ `FTensorShape(const FTensorShape& OtherShape) = default;` — Construct this tensor shape from another one. @param OtherShape the other tensor shape to copy from.
- L162 _public prototype_ `static FTensorShape Make(TConstArrayView<uint32> Data);` — Construct a tensor shape with the given dimensions. @param Data an array of dimensions. @return a tensor shape with the given dimensions.
- L172 _public prototype_ `static FTensorShape MakeFromSymbolic(const FSymbolicTensorShape& SymbolicShape);` — Construct a tensor shape from a symbolic tensor shape. Negative dimension values are replaced by 1. @param SymbolicShape a symbolic tensor shape. @return a tensor shape with the given dimensions.
- L179 _public function_ `inline TConstArrayView<uint32> GetData() const` — Get the dimensions of the tensor shape. @return a view on the dimensions of the tensor shape.
- L186 _public function_ `inline int32 Rank() const` — Get the number of dimensions of the tensor shape, aka the rank. @return the number of dimensions of the tensor shape.
- L193 _public prototype_ `uint64 Volume() const;` — Get the number of elements in this tensor shape. @return the number of element in this tensor shape.
- L202 _public prototype_ `bool IsCompatibleWith(const FSymbolicTensorShape& SymbolicShape) const;` — Check if this tensor shape is part of the ensemble of shapes defined by the symbolic shape. For example [1,2] is compatible with [-1,2] and [1,2] but not with [2,2] or [1,2,3]. @return true if this tensor shape is compatible with the symbolic shape, false otherwise.
- L210 _public prototype_ `bool operator==(const FTensorShape& OtherShape) const;` — Check if the tensor shape is equal to another one. @param OtherShape the other tensor shape. @return true if the tensor shape is equal to the other one, false otherwise.
- L218 _public prototype_ `bool operator!=(const FTensorShape& OtherShape) const;` — Check if the tensor shape is different from another one. @param OtherShape the other tensor shape. @return true if the tensor shape is different from the other one, false otherwise.
- L224 _public prototype_ `void operator=(const FTensorShape& OtherShape);` — Assign this tensor shape from another one. @param OtherShape the other tensor shape to copy from.

#### class `UE::NNE::FTensorDesc`  
`class FTensorDesc`  
_L233-280_
- desc: The descriptor for a tensor as model inputs and output. A tensor is described by its name, the type of data it contains and it's shape. Since input and output tensors of a neural network can have dynamic shapes, Shape is symbolic.
- L236 _private member_ `FString Name;`
- L237 _private member_ `ENNETensorDataType DataType;`
- L238 _private member_ `FSymbolicTensorShape Shape;`
- L240 _private prototype_ `FTensorDesc() = default;`
- L251 _public prototype_ `static FTensorDesc Make(const FString& Name, const FSymbolicTensorShape& Shape, ENNETensorDataType DataType);` — Construct a tensor description for model input/output @param Name the name of the tensor. @param Shape the symbolic shape of the tensor. @param DataType the type of data the tensor contains. @return a tensor shape with the given dimensions.
- L258 _public function_ `inline const FString& GetName() const` — Get the name of the tensor @return the name of the tensor.
- L265 _public function_ `inline ENNETensorDataType GetDataType() const` — Get the data type of the tensor @return the data type of the tensor.
- L272 _public function_ `inline uint32 GetElementByteSize() const` — Get the size in bytes of one element of the tensor. @return the size in bytes of one element of the tensor.
- L279 _public function_ `inline const FSymbolicTensorShape& GetShape() const` — Get the symbolic shape of the tensor. @return the symbolic shape of the tensor.

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace NNE` (scope `UE`)
- L44 _prototype_ `int32 GetTensorDataTypeSizeInBytes(ENNETensorDataType InType);` (scope `UE::NNE`) — Return the data size in bytes for a tensor data type. @param InType the type of the element to consider. @return the data size in bytes of an element.
