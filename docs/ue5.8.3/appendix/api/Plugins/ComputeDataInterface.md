# Plugins / ComputeDataInterface

- module root: `Plugins/Runtime/ComputeFramework/Source/ComputeDataInterface`
- headers: 2; symbols: 64
- symbol kinds: class=6, enum=1, enumerator=12, function=3, member=15, prototype=25, typedef=2
- PrivateDependencyModuleNames: RHI, RenderCore
- PublicDependencyModuleNames: ComputeFramework, Core, CoreUObject, Engine

### `Plugins/Runtime/ComputeFramework/Source/ComputeDataInterface/Internal/ComputeFramework/ComputeDataInterfaceBuffer.h` (Internal)


#### enum `EComputeDataInterfaceBufferType`  
`enum class EComputeDataInterfaceBufferType : uint8`  
_L14-28_
- reflection: `UENUM()`
- L16 _public enumerator_ `Int`
- L17 _public enumerator_ `Uint`
- L18 _public enumerator_ `Float`
- L19 _public enumerator_ `Int2`
- L20 _public enumerator_ `Uint2`
- L21 _public enumerator_ `Float2`
- L22 _public enumerator_ `Int3`
- L23 _public enumerator_ `Uint3`
- L24 _public enumerator_ `Float3`
- L25 _public enumerator_ `Int4`
- L26 _public enumerator_ `Uint4`
- L27 _public enumerator_ `Float4`

#### class `UComputeDataInterfaceBuffer`  
`class UComputeDataInterfaceBuffer : public UComputeDataInterface`  
_L32-58_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UComputeDataInterface`
- desc: Compute data interface used to own and give access to a GPU buffer.
- L37 _private function_ `TCHAR const* GetClassName() const override`
- L38 _private prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L39 _private prototype_ `void GetSupportedOutputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L40 _private prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L41 _private prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L42 _private prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L43 _private prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L44 _private prototype_ `UComputeDataProvider* CreateDataProvider() const override;`
- L50 _public member_ `EComputeDataInterfaceBufferType ValueType;` — `UPROPERTY(EditAnywhere, Category = Settings)` — The value type for the buffer.
- L54 _public member_ `bool bAllowReadWrite = false;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Whether to allow read/write access.
- L57 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UBufferDataProvider`  
`class UBufferDataProvider : public UComputeDataProvider`  
_L62-83_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute data provider implementation for UComputeDataInterfaceBuffer.
- L67 _private prototype_ `void Initialize(int32 InDataInterfaceIndex, UComputeDataInterface const* InDataInterface, UObject* InBinding, uint64 InInputMask, uint64 InOutputMask) override;`
- L68 _private prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L74 _public member_ `EComputeDataInterfaceBufferType ValueType;` — `UPROPERTY()` — The value type for the buffer.
- L78 _public member_ `int32 ElementCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataInterface)` — The size of the buffer.
- L82 _public member_ `bool bClearBeforeUse = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataInterface)` — Whether to clear the buffer before use.

#### class `FBufferDataProviderProxy`  
`class FBufferDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L86-107_
- inherits: `FComputeDataProviderRenderProxy`
- desc: Compute data provider proxy implementation for UComputeDataInterfaceBuffer.
- L89 _private prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L90 _private prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L91 _private prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L95 _public prototype_ `FBufferDataProviderProxy(uint32 InElementStride, uint32 InElementCount, bool bInClearBeforeUse);`
- L98 _private typedef_ `using FParameters = FBufferDataInterfaceParameters;`
- L100 _private member_ `const uint32 ElementStride;`
- L101 _private member_ `const uint32 ElementCount;`
- L102 _private member_ `const bool bClearBeforeUse;`
- L104 _private member_ `FRDGBufferRef Buffer;`
- L105 _private member_ `FRDGBufferSRVRef BufferSRV;`
- L106 _private member_ `FRDGBufferUAVRef BufferUAV;`

### `Plugins/Runtime/ComputeFramework/Source/ComputeDataInterface/Internal/ComputeFramework/ComputeDataInterfaceDispatch.h` (Internal)


#### class `UComputeDataInterfaceDispatch`  
`class UComputeDataInterfaceDispatch : public UComputeDataInterface`  
_L14-31_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UComputeDataInterface`
- desc: Compute data interface used to control a static dispatch size, and expose thread count to the shader.
- L19 _private function_ `TCHAR const* GetClassName() const override`
- L20 _private function_ `bool IsExecutionInterface() const override`
- L21 _private prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L22 _private prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L23 _private prototype_ `const TCHAR* GetShaderVirtualPath() const override;`
- L24 _private prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L25 _private prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L26 _private prototype_ `UComputeDataProvider* CreateDataProvider() const override;`
- L30 _private member_ `static const TCHAR* TemplateFilePath;`

#### class `UDispatchDataProvider`  
`class UDispatchDataProvider : public UComputeDataProvider`  
_L35-47_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute data provider implementation for UComputeDataInterfaceDispatch.
- L40 _private prototype_ `void Initialize(int32 InDataInterfaceIndex, UComputeDataInterface const* InDataInterface, UObject* InBinding, uint64 InInputMask, uint64 InOutputMask) override;`
- L41 _private prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L46 _public member_ `FIntVector ThreadCount = FIntVector(1, 1, 1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataInterface)`

#### class `FDispatchDataProviderProxy`  
`class FDispatchDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L50-65_
- inherits: `FComputeDataProviderRenderProxy`
- desc: Compute data provider proxy implementation for UComputeDataInterfaceDispatch.
- L53 _private prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L54 _private prototype_ `int32 GetDispatchThreadCount(TArray<FIntVector>& InOutThreadCounts) const override;`
- L55 _private prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L59 _public prototype_ `FDispatchDataProviderProxy(FIntVector InThreadCount);`
- L62 _private typedef_ `using FParameters = FDataInterfaceDispatchParameters;`
- L64 _private member_ `FIntVector ThreadCount;`
