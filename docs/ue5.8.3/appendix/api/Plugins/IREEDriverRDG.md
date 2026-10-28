# Plugins / IREEDriverRDG

- module root: `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG`
- headers: 13; symbols: 119
- symbol kinds: class=2, delegate=1, enum=3, enumerator=7, function=3, member=28, namespace=41, prototype=26, struct=8
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, IREE, IREEUtils, Json, NNE, NNERuntimeIREEShader, Projects, RHI, RenderCore, ShaderCompilerCommon

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Internal/IREECompilerRDG.h` (Internal)


#### struct `FIREECompilerRDGExecutableData`  
`struct FIREECompilerRDGExecutableData`  
_L13-22_
- reflection: `USTRUCT()`
- L18 _public member_ `FString Name;` — `UPROPERTY()`
- L21 _public member_ `TArray<uint8> Data;` — `UPROPERTY()`

#### struct `FIREECompilerRDGBuildTargetResult`  
`struct FIREECompilerRDGBuildTargetResult`  
_L25-59_
- reflection: `USTRUCT()`
- L30 _public member_ `FString ShaderPlatform;` — `UPROPERTY()`
- L33 _public member_ `TArray<FIREECompilerRDGExecutableData> Executables;` — `UPROPERTY()`
- L35 _public member_ `int64 DataSize;`
- L36 _public member_ `TArray64<uint8> VmfbData;`
- L38 _public function_ `bool Serialize(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FIREECompilerRDGBuildTargetResult> : public TStructOpsTypeTraitsBase2<FIREECompilerRDGBuildTargetResult>`  
_L62-68_
- inherits: `TStructOpsTypeTraitsBase2<FIREECompilerRDGBuildTargetResult>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L65-67_

#### struct `FIREECompilerRDGResult`  
`struct FIREECompilerRDGResult`  
_L71-77_
- reflection: `USTRUCT()`
- L76 _public member_ `TArray<FIREECompilerRDGBuildTargetResult> BuildTargetResults;` — `UPROPERTY()`

#### struct `UE::IREE::Compiler::RDG::FBuildTarget`  
`struct FBuildTarget : public FJsonSerializable`  
_L84-94_
- inherits: `FJsonSerializable`
- L86 _public member_ `FString ShaderPlatform;`
- L87 _public member_ `FString CompilerArguments;`
- L88 _public member_ `FString LinkerArguments;`

#### struct `UE::IREE::Compiler::RDG::FBuildConfig`  
`struct FBuildConfig : public FJsonSerializable`  
_L96-109_
- inherits: `FJsonSerializable`
- L98 _public member_ `TArray<FString> ImporterCommand;`
- L99 _public member_ `FString ImporterArguments;`
- L100 _public member_ `TArray<FString> CompilerCommand;`
- L101 _public member_ `TArray<FBuildTarget> BuildTargets;`

#### class `UE::IREE::Compiler::RDG::FCompiler`  
`class FCompiler`  
_L111-132_
- L114 _private prototype_ `FCompiler(const ITargetPlatform* TargetPlatform, const FString& InImporterCommand, const FString& InImporterArguments, const FString& InCompilerCommand, const FString& InSharedLibExt, TConstArrayView<FBuildTarget> InBuildTargets, const FMD5Hash& InHash);`
- L117 _public function_ `~FCompiler()`
- L118 _public prototype_ `static TUniquePtr<FCompiler> Make(const ITargetPlatform* TargetPlatform);`
- L121 _public function_ `const FMD5Hash& GetHash() const`
- L122 _public prototype_ `bool ImportOnnx(TConstArrayView<uint8> InFileData, const FString& InModelName, const FString& InOutputDir, TArray64<uint8>& OutMlirData);`
- L123 _public prototype_ `bool CompileMlir(TConstArrayView<uint8> InFileData, const FString& InModelName, const FString& InOutputDir, TConstArrayView<EShaderPlatform> ShaderPlatforms, FIREECompilerRDGResult& OutCompilerResult);`
- L126 _private member_ `const ITargetPlatform* TargetPlatform;`
- L127 _private member_ `FString ImporterCommand;`
- L128 _private member_ `FString ImporterArguments;`
- L129 _private member_ `FString CompilerCommand;`
- L130 _private member_ `TArray<FBuildTarget> BuildTargets;`
- L131 _private member_ `const FMD5Hash Hash;`

#### Free symbols / members of external scopes

- L66 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonc7c2ee590103`)
- L82 _namespace_ `namespace UE`
- L82 _namespace_ `namespace IREE` (scope `UE`)
- L82 _namespace_ `namespace Compiler` (scope `UE::IREE`)
- L82 _namespace_ `namespace RDG` (scope `UE::IREE::Compiler`)

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Internal/IREEDriverRDG.h` (Internal)


#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace IREE` (scope `UE`)
- L24 _namespace_ `namespace HAL` (scope `UE::IREE`)
- L24 _namespace_ `namespace RDG` (scope `UE::IREE::HAL`)
- L27 _prototype_ `iree_status_t DeviceCreate(iree_string_view_t Identifier, iree_allocator_t HostAllocator, const TMap<FString, TConstArrayView<uint8>>& Executables, iree_hal_device_t** OutDevice);` (scope `UE::IREE::HAL::RDG`)
- L29 _prototype_ `iree_status_t BufferWrapRDG(iree_allocator_t HostAllocator, iree_hal_allocator_t* DeviceAllocator, iree_hal_memory_type_t MemoryType, iree_hal_memory_access_t AllowedAccess, iree_hal_buffer_usage_t AllowedUsage, iree_device_size_t AllocationSize, iree_device_size_t ByteOffset, iree_device_size_t ByteLength, FRDGBuilder* GraphBuilder, FRDGBufferRef RDGBuffer, iree_hal_buffer_release_callback_t UserReleaseCallback, iree_hal_buffer_t** OutBuffer);` (scope `UE::IREE::HAL::RDG`)
- L30 _prototype_ `FRDGBufferRef BufferRDGBuffer(iree_hal_buffer_t* Buffer, FRDGBuilder* GraphBuilder);` (scope `UE::IREE::HAL::RDG`)
- L32 _prototype_ `void DeviceAllocatorSetGraphBuilder(iree_hal_allocator_t* DeviceAllocator, FRDGBuilder& GraphBuilder);` (scope `UE::IREE::HAL::RDG`)
- L33 _prototype_ `FRDGBuilder& DeviceAllocatorGetGraphBuilder(iree_hal_allocator_t* DeviceAllocator);` (scope `UE::IREE::HAL::RDG`)
- L34 _prototype_ `void DeviceAllocatorResetGraphBuilder(iree_hal_allocator_t* DeviceAllocator);` (scope `UE::IREE::HAL::RDG`)

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Internal/IREEDriverRDGLog.h` (Internal)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogIREEDriverRDG, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIREEDriverRDG, Log, All);`

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Private/IREEDriverRDGBuffer.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace IREE` (scope `UE`)
- L12 _namespace_ `namespace HAL` (scope `UE::IREE`)
- L12 _namespace_ `namespace RDG` (scope `UE::IREE::HAL`)
- L15 _prototype_ `iree_status_t BufferWrap(iree_allocator_t HostAllocator, iree_hal_allocator_t* DeviceAllocator, iree_hal_memory_type_t MemoryType, iree_hal_memory_access_t AllowedAccess, iree_hal_buffer_usage_t AllowedUsage, iree_device_size_t AllocationSize, iree_device_size_t ByteOffset, iree_device_size_t ByteLength, const TRefCountPtr<FRDGPooledBuffer>& PooledBuffer, iree_hal_buffer_release_callback_t UserReleaseCallback, iree_hal_buffer_t** OutBuffer);` (scope `UE::IREE::HAL::RDG`)
- L16 _prototype_ `bool BufferIsTransient(iree_hal_buffer_t* Buffer);` (scope `UE::IREE::HAL::RDG`)
- L17 _prototype_ `FRDGPooledBuffer* BufferPooledBufferHandle(iree_hal_buffer_t* Buffer);` (scope `UE::IREE::HAL::RDG`)

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Private/IREEDriverRDGBuiltinExecutables.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace IREE` (scope `UE`)
- L11 _namespace_ `namespace HAL` (scope `UE::IREE`)
- L11 _namespace_ `namespace RDG` (scope `UE::IREE::HAL`)
- L14 _namespace_ `namespace BuiltinExecutables` (scope `UE::IREE::HAL::RDG`)
- L17 _prototype_ `iree_status_t FillBuffer(uint8* Buffer, uint32 BufferLength, uint32 Pattern, uint32 PatternLength, uint32 FillOffset, uint32 FillLength);` (scope `UE::IREE::HAL::RDG::BuiltinExecutables`)
- L19 _prototype_ `iree_status_t AddFillBufferPass(FRDGBuilder& GraphBuilder, FRDGBufferRef RDGBuffer, uint32 Pattern, uint32 PatternLength, uint32 FillOffset, uint32 FillLength);` (scope `UE::IREE::HAL::RDG::BuiltinExecutables`)

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Private/IREEDriverRDGDevice.h` (Private)
_(no declarations extracted)_

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Private/IREEDriverRDGDeviceAllocator.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace IREE` (scope `UE`)
- L9 _namespace_ `namespace HAL` (scope `UE::IREE`)
- L9 _namespace_ `namespace RDG` (scope `UE::IREE::HAL`)
- L12 _prototype_ `iree_status_t DeviceAllocatorCreate(iree_allocator_t HostAllocator, iree_hal_allocator_t** OutDeviceAllocator);` (scope `UE::IREE::HAL::RDG`)

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Private/IREEDriverRDGDirectCommandBuffer.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace IREE` (scope `UE`)
- L9 _namespace_ `namespace HAL` (scope `UE::IREE`)
- L9 _namespace_ `namespace RDG` (scope `UE::IREE::HAL`)
- L12 _prototype_ `iree_status_t DirectCommandBufferCreate(iree_allocator_t HostAllocator, iree_hal_allocator_t* DeviceAllocator, iree_hal_command_buffer_mode_t Mode, iree_hal_command_category_t CommandCategories, iree_hal_queue_affinity_t QueueAffinity, iree_host_size_t BindingCapacity, iree_hal_command_buffer_t** OutCommandBuffer);` (scope `UE::IREE::HAL::RDG`)

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Private/IREEDriverRDGExecutable.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace IREE` (scope `UE`)
- L12 _namespace_ `namespace HAL` (scope `UE::IREE`)
- L12 _namespace_ `namespace RDG` (scope `UE::IREE::HAL`)
- L15 _prototype_ `iree_status_t ExecutableCreate(iree_allocator_t HostAllocator, TArrayView<TSharedRef<FNNERuntimeIREEResource>> KernelResources, iree_hal_executable_t** OutExecutable);` (scope `UE::IREE::HAL::RDG`)
- L17 _prototype_ `iree_status_t ExecutableGetResource(iree_hal_executable_t* Executable, int32 EntryPoint, const FNNERuntimeIREEResource** OutResource);` (scope `UE::IREE::HAL::RDG`)

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Private/IREEDriverRDGModule.h` (Private)


#### class `FIREEDriverRDGModule`  
`class FIREEDriverRDGModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Private/IREEDriverRDGNoOpExecutableCache.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace IREE` (scope `UE`)
- L9 _namespace_ `namespace HAL` (scope `UE::IREE`)
- L9 _namespace_ `namespace RDG` (scope `UE::IREE::HAL`)
- L12 _prototype_ `iree_status_t NoOpExecutableCacheCreate(iree_allocator_t HostAllocator, const TMap<FString, TArray<uint8>>* Executables, iree_hal_executable_cache_t** OutExecutableCache);` (scope `UE::IREE::HAL::RDG`)

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Private/IREEDriverRDGSemaphore.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace IREE` (scope `UE`)
- L9 _namespace_ `namespace HAL` (scope `UE::IREE`)
- L9 _namespace_ `namespace RDG` (scope `UE::IREE::HAL`)
- L12 _prototype_ `iree_status_t SemaphoreCreate(iree_allocator_t HostAllocator, uint64 InitialValue, iree_hal_semaphore_t** OutSemaphore);` (scope `UE::IREE::HAL::RDG`)

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEDriverRDG/Private/IREEDriverRDGShaderParametersMetadata.h` (Private)


#### enum `FIREEDriverRDGUniformBufferBaseType`  
`enum class FIREEDriverRDGUniformBufferBaseType : uint8`  
_L8-14_
- reflection: `UENUM()`
- L10 _public enumerator_ `INVALID`
- L11 _public enumerator_ `PARAM`
- L12 _public enumerator_ `PARAM_ARRAY`
- L13 _public enumerator_ `BUFFER_UAV`

#### enum `FIREEDriverRDGUniformBufferElementType`  
`enum class FIREEDriverRDGUniformBufferElementType : uint8`  
_L17-21_
- reflection: `UENUM()`
- L19 _public enumerator_ `NONE`
- L20 _public enumerator_ `UINT32`

#### struct `FIREEDriverRDGShaderParametersMetadataEntry`  
`struct FIREEDriverRDGShaderParametersMetadataEntry`  
_L24-48_
- reflection: `USTRUCT()`
- L29 _public member_ `FIREEDriverRDGUniformBufferBaseType Type = FIREEDriverRDGUniformBufferBaseType::INVALID;` — `UPROPERTY()`
- L32 _public member_ `FString Name;` — `UPROPERTY()`
- L35 _public member_ `FString ShaderType;` — `UPROPERTY()`
- L38 _public member_ `uint32 Binding = 0;` — `UPROPERTY()`
- L41 _public member_ `uint32 DescriptorSet = 0;` — `UPROPERTY()`
- L44 _public member_ `FIREEDriverRDGUniformBufferElementType ElementType = FIREEDriverRDGUniformBufferElementType::NONE;` — `UPROPERTY()`
- L47 _public member_ `uint32 NumElements = 0;` — `UPROPERTY()`

#### struct `FIREEDriverRDGShaderParametersMetadata`  
`struct FIREEDriverRDGShaderParametersMetadata`  
_L51-57_
- reflection: `USTRUCT()`
- L56 _public member_ `TArray<FIREEDriverRDGShaderParametersMetadataEntry> Entries;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L66 _namespace_ `namespace UE`
- L66 _namespace_ `namespace IREE` (scope `UE`)
- L66 _namespace_ `namespace HAL` (scope `UE::IREE`)
- L66 _namespace_ `namespace RDG` (scope `UE::IREE::HAL`)
- L71 _prototype_ `bool BuildIREEShaderParametersMetadata(const FString& Filepath, FIREEDriverRDGShaderParametersMetadata& Metadata);` (scope `UE::IREE::HAL::RDG`)
- L75 _prototype_ `FShaderParametersMetadata* BuildShaderParametersMetadata(const FIREEDriverRDGShaderParametersMetadata& Metadata, FNNERuntimeIREEShaderParametersMetadataAllocations& Allocations);` (scope `UE::IREE::HAL::RDG`)
