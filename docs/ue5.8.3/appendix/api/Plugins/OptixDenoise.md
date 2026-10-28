# Plugins / OptixDenoise

- module root: `Plugins/Experimental/OptiXDenoise/Source/OptiXDenoise`
- headers: 1; symbols: 131
- symbol kinds: class=4, delegate=1, enum=5, enumerator=18, function=16, macro=2, member=49, namespace=2, prototype=30, struct=2, typedef=2
- PrivateDependencyModuleNames: CUDA, Core, CoreUObject, D3D12RHI, Engine, MessageLog, OptiXDenoiseBase, Projects, RHI, RenderCore, Renderer

### `Plugins/Experimental/OptiXDenoise/Source/OptiXDenoise/Private/OptiXDenoiser.h` (Private)


#### enum `UE::OptiXDenoiser::ECUDASurfaceCopyType`  
`enum class ECUDASurfaceCopyType`  
_L59-63_
- L61 _public enumerator_ `SurfaceToBuffer`
- L62 _public enumerator_ `BufferToSurface`

#### class `UE::OptiXDenoiser::FOptiXImage2D`  
`class FOptiXImage2D`  
_L65-129_
- L76 _public typedef_ `using FReleaseCUDATextureCallback = TFunction<void(TSurfaceObject)>;`
- L77 _public typedef_ `using FCUDASurfaceTextureCopyCallback = TFunction<void(TSurfaceObject, FOptiXImage2D&, CUstream, ECUDASurfaceCopyType)>;`
- L102 _public function_ `bool IsValid()`
- L103 _public prototype_ `FOptiXImageData& GetRawImage();`
- L104 _public prototype_ `void SetTexture(TSurfaceObject InTexture, EUnderlyingRHI UnderlyingRHI, void* SharedHandle, FReleaseCUDATextureCallback InOnReleaseTexture, FCUDASurfaceTextureCopyCallback InCopyCallback );`
- L108 _public prototype_ `void Flush(ECUDASurfaceCopyType CopyType, CUstream CudaStream);`
- L109 _public function_ `void SetFormat(EOptiXImageFormat InFormat)`
- L110 _public function_ `const FCudaBuffer& GetCudaBuffer() const`
- L111 _public function_ `FCudaBuffer& GetCudaBuffer()`
- L112 _public function_ `void SetWidth(uint32 InWidth)`
- L113 _public function_ `uint32 GetWidth() const`
- L114 _public function_ `void SetHeight(uint32 InHeight)`
- L115 _public function_ `uint32 GetHeight() const`
- L117 _public prototype_ `~FOptiXImage2D();`
- L118 _public function_ `FOptiXImage2D()`
- L121 _protected prototype_ `void DestroyCUDAIntermediateMemory();`
- L122 _protected prototype_ `void ReleaseCUDABuffer();`
- L124 _protected member_ `FCudaBuffer CudaBuffer = {};`
- L125 _protected member_ `FOptiXImageData Image = {};`
- L126 _protected member_ `uint32 Width = 0;`
- L127 _protected member_ `uint32 Height = 0;`
- L128 _protected member_ `EOptiXImageFormat Format = EOptiXImageFormat::Undefined;`

#### enum `UE::OptiXDenoiser::FOptiXImage2D::EUnderlyingRHI`  
`enum class EUnderlyingRHI`  
_L69-74_
- L71 _public enumerator_ `Undefined`
- L72 _public enumerator_ `D3D12`
- L73 _public enumerator_ `Vulkan`

#### struct `UE::OptiXDenoiser::FOptiXImage2D::FCudaBuffer`  
`struct FCudaBuffer`  
_L80-99_
- desc: Struct to hold buffer for cuda inter-operation.
- L82 _public member_ `EUnderlyingRHI UnderlyingRHI;`
- L85 _public member_ `HANDLE Handle = NULL;` — @todo add support for vulkan, now support only windows
- L88 _public member_ `TSurfaceObject SurfaceObject = 0;` — Mapped to external texture object
- L91 _public member_ `void* CudaPtr = nullptr;` — cudaExternalMemory_t ExternalMemory;
- L94 _public member_ `unsigned int CudaMemorySize = 0;` — Device memory size of CudaPtr;
- L96 _public member_ `FReleaseCUDATextureCallback DestroyFunc;`
- L98 _public member_ `FCUDASurfaceTextureCopyCallback CopyCallback;`

#### class `UE::OptiXDenoiser::FOptiXImageFactory`  
`class FOptiXImageFactory`  
_L131-154_
- L134 _public prototype_ `FOptiXImageFactory();`
- L135 _public prototype_ `~FOptiXImageFactory();`
- L137 _public prototype_ `TSharedPtr<FOptiXImage2D> GetOptiXImage2DAndSetTexture(FTextureRHIRef InTexture);`
- L138 _public prototype_ `void FlushImages();`
- L140 _private prototype_ `TSharedPtr<FOptiXImage2D> GetOrCreateImage(const FTextureRHIRef InTexture);`
- L142 _private prototype_ `void SetTexture(TSharedPtr<FOptiXImage2D> FOptiXImageData, const FTextureRHIRef& Texture);`
- L144 _private prototype_ `void SetTextureCUDAVulkan(TSharedPtr<FOptiXImage2D> FOptiXImageData, const FTextureRHIRef& Texture);`
- L146 _private prototype_ `void SetTextureCUDAD3D12(TSharedPtr<FOptiXImage2D> FOptiXImageData, const FTextureRHIRef& Texture);`
- L149 _private prototype_ `void RemoveStaleTextures();`
- L152 _private member_ `uint64 FrameId = 0;`
- L153 _private member_ `TMap <TRefCountPtr<FRHITexture>, TSharedPtr<FOptiXImage2D>> TextureToOptiXImage2DMapping;`

#### enum `UE::OptiXDenoiser::EOpticalFlowImageType`  
`enum class EOpticalFlowImageType : uint32_t`  
_L157-163_
- L159 _public enumerator_ `INPUTFRAME = 0`
- L160 _public enumerator_ `REFERENCE`
- L161 _public enumerator_ `FLOWOUTPUT`
- L162 _public enumerator_ `MAX`

#### class `UE::OptiXDenoiser::FOptiXFlowEstimator`  
`class FOptiXFlowEstimator`  
_L169-213_
- desc: Estimate the flow based on the optiX OpticalFlow from source to target. viable to newer GPUs.
- L185 _public function_ `CUstream GetCudaStream()`
- L187 _public prototype_ `void Init( uint32_t InWidth, uint32_t InHeight, EOptiXImageFormat InPixelFormat = EOptiXImageFormat::CUDA_A32B32G32R32_F);`
- L191 _public function_ `void SetOptiXImage2D(EOpticalFlowImageType Type, TSharedPtr<FOptiXImage2D> Image)`
- L192 _public function_ `TSharedPtr<FOptiXImage2D> GetOptiXImage2D(EOpticalFlowImageType Type)`
- L194 _public prototype_ `void Commit();`
- L195 _public prototype_ `~FOptiXFlowEstimator();`
- L198 _private prototype_ `void Update();`
- L199 _private prototype_ `void Execute();`
- L200 _private prototype_ `void Destroy();`
- L202 _private member_ `TSharedPtr<FOptiXImage2D> Images[static_cast<uint32_t>(EOpticalFlowImageType::MAX)];`
- L204 _private member_ `CUstream CudaStream = nullptr;`
- L206 _private member_ `EOptiXImageFormat PixelFormat;`
- L207 _private member_ `uint32_t Width;`
- L208 _private member_ `uint32_t Height;`
- L209 _private member_ `uint32_t PixelSize;`
- L212 _private member_ `TUniquePtr<FOpticalFlowContext> OptixFlow = nullptr;`

#### struct `UE::OptiXDenoiser::FOptiXFlowEstimator::FData`  
`struct FData`  
_L172-183_
- L174 _public member_ `uint32_t Width = 0;`
- L175 _public member_ `uint32_t Height = 0;`
- L177 _public member_ `HANDLE SharedInputHandle = nullptr;`
- L178 _public member_ `HANDLE SharedReferenceHandle = nullptr;`
- L180 _public member_ `HANDLE SharedOutputHandle = nullptr;`
- L182 _public member_ `unsigned long long Size = 0;`

#### enum `UE::OptiXDenoiser::EDenoiseDimension`  
`enum class EDenoiseDimension`  
_L215-219_
- L217 _public enumerator_ `SPATIAL = 0`
- L218 _public enumerator_ `SPATIAL_TEMPORAL = 1`

#### enum `UE::OptiXDenoiser::EDenoisingImageType`  
`enum class EDenoisingImageType : uint32_t`  
_L221-230_
- L223 _public enumerator_ `COLOR = 0`
- L224 _public enumerator_ `ALBEDO`
- L225 _public enumerator_ `NORMAL`
- L226 _public enumerator_ `FLOW`
- L227 _public enumerator_ `OUTPUT`
- L228 _public enumerator_ `PREVOUTPUT`
- L229 _public enumerator_ `MAX`

#### class `UE::OptiXDenoiser::FOptiXGPUDenoiser`  
`class FOptiXGPUDenoiser`  
_L233-297_
- desc: Denoise the rendering with/without flow
- L236 _public function_ `FOptiXGPUDenoiser()`
- L237 _public prototype_ `FOptiXGPUDenoiser(const FOptiXGPUDenoiser&) = delete;`
- L238 _public prototype_ `~FOptiXGPUDenoiser();`
- L240 _public prototype_ `void Init( uint32_t Width, uint32_t Height, EOptiXImageFormat InPixelFormat = EOptiXImageFormat::CUDA_A32B32G32R32_F, uint32_t TileWidth = 0u, uint32_t TileHeight = 0u, bool GuildAlbedo = true, bool GuildNormal = true, bool KPMode = false, bool InTemporalMode = true);`
- L250 _public prototype_ `void Finish();`
- L251 _public prototype_ `void Commit();`
- L252 _public prototype_ `void SetOptiXImage2D(EDenoisingImageType Type, TSharedPtr<FOptiXImage2D> Image);`
- L253 _public function_ `TSharedPtr<FOptiXImage2D> GetOptiXImage2D(EDenoisingImageType Type)`
- L254 _public function_ `CUstream GetCudaStream() const`
- L255 _public function_ `bool IsImageSizeChanged(uint32_t InWidth, uint32_t InHeight)`
- L259 _private prototype_ `void Update();`
- L260 _private prototype_ `void Execute();`
- L262 _private member_ `EDenoiseDimension DenoiseDimension;`
- L263 _private member_ `bool GuideAlbedo;`
- L264 _private member_ `bool GuideNormal;`
- L266 _private member_ `uint32_t TileWidth;`
- L267 _private member_ `uint32_t TileHeight;`
- L268 _private member_ `uint32_t Width;`
- L269 _private member_ `uint32_t Height;`
- L270 _private member_ `uint32_t PixelSize;`
- L272 _private member_ `EOptiXImageFormat PixelFormat;`
- L275 _private member_ `CUstream CudaStream;` — Cuda stream for nonblocking
- L277 _private member_ `CUdeviceptr CudaState = 0;`
- L278 _private member_ `uint32_t CudaStateSize = 0;`
- L280 _private member_ `CUdeviceptr CudaScratch = 0;`
- L281 _private member_ `uint32_t CudaScratchSize = 0;`
- L282 _private member_ `uint32_t CudaOverlap = 0;`
- L284 _private member_ `CUdeviceptr Intensity = 0;`
- L285 _private member_ `CUdeviceptr AverageColor = 0;`
- L286 _private member_ `CUdeviceptr InternalMemIn = 0;`
- L287 _private member_ `CUdeviceptr InternalMemOut = 0;`
- L289 _private member_ `TSharedPtr<FOptiXImage2D> Images[static_cast<uint32_t>(EDenoisingImageType::MAX)] = {};`
- L291 _private member_ `uint32_t InternalDenoisedFrameId = 0;`
- L296 _private member_ `TUniquePtr<FOptiXDenoiseContext> OptiXDenoiseContext;` — The wrapper entry for NVIDIA's OptiX Denoiser

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOptiXDenoise, Log, All);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOptiXDenoise, Log, All);`
- L21 _macro_ `#define OPTIX_CHECK(Call) \`
- L31 _macro_ `#define CUDA_CHECK(Call) \`
- L57 _namespace_ `namespace UE`
- L57 _namespace_ `namespace OptiXDenoiser` (scope `UE`)
