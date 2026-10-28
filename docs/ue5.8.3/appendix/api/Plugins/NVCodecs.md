# Plugins / NVCodecs

- module root: `Plugins/Experimental/AVCodecs/NVCodecs/Source/NVCodecs`
- headers: 1; symbols: 29
- symbol kinds: class=2, function=5, macro=1, member=7, prototype=13, struct=1
- PrivateDependencyModuleNames: AVCodecsCore, CUDA, Engine, Vulkan
- PublicDependencyModuleNames: Core, RenderCore

### `Plugins/Experimental/AVCodecs/NVCodecs/Source/NVCodecs/Public/Video/Resources/VideoResourceCUDA.h` (Public)


#### struct `FCUDAContextScope`  
`struct FCUDAContextScope`  
_L13-24_
- L15 _public function_ `FCUDAContextScope(CUcontext Context)`
- L20 _public function_ `~FCUDAContextScope()`

#### class `FVideoContextCUDA`  
`class FVideoContextCUDA : public FAVContext`  
_L26-32_
- inherits: `FAVContext`
- L29 _public member_ `CUcontext Raw;`
- L31 _public prototype_ `FVideoContextCUDA(CUcontext const& Raw);`

#### class `FVideoResourceCUDA`  
`class FVideoResourceCUDA : public TVideoResource<FVideoContextCUDA>`  
_L34-91_
- inherits: `TVideoResource<FVideoContextCUDA>`
- L37 _private member_ `CUexternalSemaphore ExternalSemaphore = nullptr;`
- L38 _private member_ `uint64 SemaphoreValue = 0;`
- L39 _private member_ `CUexternalMemory ExternalArray = nullptr;`
- L40 _private member_ `CUmipmappedArray MipArray = nullptr;`
- L41 _private member_ `CUarray MaxMipArray = nullptr;`
- L43 _private member_ `CUarray Raw = nullptr;`
- L46 _public function_ `inline CUarray GetRaw() const`
- L48 _public prototype_ `FVideoResourceCUDA(TSharedRef<FAVDevice> const& Device, CUarray Raw, FAVLayout const& Layout, FVideoDescriptor const& Descriptor);`
- L49 _public prototype_ `FVideoResourceCUDA(TSharedRef<FAVDevice> const& Device, CUDA_EXTERNAL_MEMORY_HANDLE_DESC const& ExternalResourceDesc, CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC const& ExternalFenceDesc, FAVLayout const& Layout, FVideoDescriptor const& Descriptor, uint64 FenceValue = 0);`
- L50 _public prototype_ `FVideoResourceCUDA(TSharedRef<FAVDevice> const& Device, CUDA_EXTERNAL_MEMORY_HANDLE_DESC const& ExternalResourceDesc, CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC const& ExternalFenceDesc, TSharedRef<FVideoResource> const& ExternalResource, uint64 FenceValue = 0);`
- L53 _public prototype_ `virtual FAVResult Validate() const override;`
- L55 _public prototype_ `FAVResult ReadData(TArray64<uint8>& OutData) const;`
- L57 _public prototype_ `FAVResult CopyFrom(CUdeviceptr Target, uint32 MapPitch);`
- L58 _public prototype_ `FAVResult CopyFromAsync(CUdeviceptr Target, uint32 MapPitch);`
- L60 _public prototype_ `FAVResult CopyTo(CUdeviceptr Source, uint32 MapPitch);`
- L61 _public prototype_ `FAVResult CopyToAsync(CUdeviceptr Source, uint32 MapPitch);`
- L64 _private function_ `inline CUDA_MEMCPY2D CreateCopyFromParams(CUdeviceptr Source, uint32 SourcePitch)`
- L78 _private function_ `inline CUDA_MEMCPY2D CreateCopyToParams(CUdeviceptr Target, uint32 TargetPitch)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NVCODECS_API`
- L96 _prototype_ `template <> FAVResult FAVExtension::TransformResource(TSharedPtr<FVideoResourceCUDA>& OutResource, TSharedPtr<class FVideoResourceD3D11> const& InResource);` (scope `FAVExtension`)
- L99 _prototype_ `template <> FAVResult FAVExtension::TransformResource(TSharedPtr<FVideoResourceCUDA>& OutResource, TSharedPtr<class FVideoResourceD3D12> const& InResource);` (scope `FAVExtension`)
- L104 _prototype_ `template <> FAVResult FAVExtension::TransformResource(TSharedPtr<FVideoResourceCUDA>& OutResource, TSharedPtr<class FVideoResourceVulkan> const& InResource);` (scope `FAVExtension`)
