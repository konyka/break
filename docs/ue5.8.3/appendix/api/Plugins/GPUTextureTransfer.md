# Plugins / GPUTextureTransfer

- module root: `Plugins/Media/MediaIOFramework/Source/GPUTextureTransfer`
- headers: 6; symbols: 175
- symbol kinds: class=6, delegate=1, enum=3, enumerator=9, macro=1, member=48, namespace=16, prototype=83, struct=5, typedef=2, union=1
- PrivateDependencyModuleNames: EditorFramework, GPUDirect, RenderCore, UnrealEd, VulkanRHI
- PublicDependencyModuleNames: Core, RHI

### `Plugins/Media/MediaIOFramework/Source/GPUTextureTransfer/Private/D3D11TextureTransfer.h` (Private)


#### class `UE::GPUTextureTransfer::Private::FD3D11TextureTransfer`  
`class FD3D11TextureTransfer : public FTextureTransferBase`  
_L12-24_
- inherits: `FTextureTransferBase`
- L15 _protected prototype_ `virtual DVPStatus Init_Impl() override;`
- L16 _protected prototype_ `virtual DVPStatus GetConstants_Impl(uint32* OutBufferAddrAlignment, uint32* OutBufferGPUStrideAlignment, uint32* OutSemaphoreAddrAlignment, uint32* OutSemaphoreAllocSize, uint32* OutSemaphorePayloadOffset, uint32* OutSemaphorePayloadSize) const override;`
- L17 _protected prototype_ `virtual DVPStatus BindBuffer_Impl(DVPBufferHandle InBufferHandle) const override;`
- L18 _protected prototype_ `virtual DVPStatus CreateGPUResource_Impl(const FRegisterDMATextureArgs& InArgs, FTextureInfo* OutTextureInfo) const override;`
- L19 _protected prototype_ `virtual DVPStatus UnbindBuffer_Impl(DVPBufferHandle InBufferHandle) const override;`
- L20 _protected prototype_ `virtual DVPStatus CloseDevice_Impl() const override;`
- L23 _private member_ `ID3D11Device* D3DDevice = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace GPUTextureTransfer` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::GPUTextureTransfer`)

### `Plugins/Media/MediaIOFramework/Source/GPUTextureTransfer/Private/D3D12TextureTransfer.h` (Private)


#### class `UE::GPUTextureTransfer::Private::FD3D12TextureTransfer`  
`class FD3D12TextureTransfer : public FTextureTransferBase`  
_L14-30_
- inherits: `FTextureTransferBase`
- L17 _protected prototype_ `virtual DVPStatus Init_Impl() override;`
- L18 _protected prototype_ `virtual DVPStatus GetConstants_Impl(uint32* OutBufferAddrAlignment, uint32* OutBufferGPUStrideAlignment, uint32* OutSemaphoreAddrAlignment, uint32* OutSemaphoreAllocSize, uint32* OutSemaphorePayloadOffset, uint32* OutSemaphorePayloadSize) const override;`
- L19 _protected prototype_ `virtual DVPStatus BindBuffer_Impl(DVPBufferHandle InBufferHandle) const override;`
- L20 _protected prototype_ `virtual DVPStatus CreateGPUResource_Impl(const FRegisterDMATextureArgs& InArgs, FTextureInfo* OutTextureInfo) const override;`
- L21 _protected prototype_ `virtual DVPStatus UnbindBuffer_Impl(DVPBufferHandle InBufferHandle) const override;`
- L22 _protected prototype_ `virtual DVPStatus CloseDevice_Impl() const override;`
- L23 _protected prototype_ `virtual DVPStatus MapBufferWaitAPI_Impl(DVPBufferHandle InHandle) const;`
- L24 _protected prototype_ `virtual DVPStatus MapBufferEndAPI_Impl(DVPBufferHandle InHandle) const;`
- L28 _private member_ `ID3D12Device* D3DDevice = nullptr;`
- L29 _private member_ `ID3D12CommandQueue* D3DCommandQueue = nullptr;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace GPUTextureTransfer` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::GPUTextureTransfer`)

### `Plugins/Media/MediaIOFramework/Source/GPUTextureTransfer/Private/TextureTransferBase.h` (Private)


#### class `UE::GPUTextureTransfer::Private::FTextureTransferBase`  
`class FTextureTransferBase : public ITextureTransfer`  
_L16-108_
- inherits: `ITextureTransfer`
- L19 _public prototype_ `virtual ~FTextureTransferBase() = default;`
- L22 _public prototype_ `virtual void WaitForGPU(FRHITexture* InRHITexture) override;`
- L23 _public prototype_ `virtual void ThreadPrep() override;`
- L24 _public prototype_ `virtual void ThreadCleanup() override;`
- L25 _public prototype_ `virtual bool BeginSync(void* InBuffer, ETransferDirection TransferDirection) override;`
- L26 _public prototype_ `virtual void EndSync(void* InBuffer) override;`
- L27 _public prototype_ `virtual bool TransferTexture(void* InBuffer, FRHITexture* InRHITexture, ETransferDirection TransferDirection) override;`
- L28 _public prototype_ `virtual void RegisterBuffer(const FRegisterDMABufferArgs& Args) override;`
- L29 _public prototype_ `virtual void UnregisterBuffer(void* InBuffer) override;`
- L30 _public prototype_ `virtual void RegisterTexture(const FRegisterDMATextureArgs& Args) override;`
- L31 _public prototype_ `virtual void UnregisterTexture(FRHITexture* InRHITexture) override;`
- L32 _public prototype_ `virtual uint32 GetBufferAlignment() const override;`
- L33 _public prototype_ `virtual uint32 GetTextureStride() const override;`
- L34 _public prototype_ `virtual void LockTexture(FRHITexture* InRHITexture) override;`
- L35 _public prototype_ `virtual void UnlockTexture(FRHITexture* InRHITexture) override;`
- L38 _public prototype_ `virtual bool Initialize() override;`
- L39 _public prototype_ `virtual bool Uninitialize() override;`
- L81 _protected prototype_ `virtual DVPStatus Init_Impl() = 0;`
- L82 _protected prototype_ `virtual DVPStatus GetConstants_Impl(uint32* OutBufferAddrAlignment, uint32* OutBufferGPUStrideAlignment, uint32* OutSemaphoreAddrAlignment, uint32* OutSemaphoreAllocSize, uint32* OutSemaphorePayloadOffset, uint32* OutSemaphorePayloadSize) const = 0;`
- L83 _protected prototype_ `virtual DVPStatus BindBuffer_Impl(DVPBufferHandle InBufferHandle) const = 0;`
- L84 _protected prototype_ `virtual DVPStatus CreateGPUResource_Impl(const FRegisterDMATextureArgs& InArgs, FTextureInfo* OutTextureInfo) const = 0;`
- L85 _protected prototype_ `virtual DVPStatus UnbindBuffer_Impl(DVPBufferHandle InBufferHandle) const = 0;`
- L86 _protected prototype_ `virtual DVPStatus CloseDevice_Impl() const = 0;`
- L87 _protected prototype_ `virtual DVPStatus MapBufferWaitAPI_Impl(DVPBufferHandle InHandle) const;`
- L88 _protected prototype_ `virtual DVPStatus MapBufferEndAPI_Impl(DVPBufferHandle InHandle) const;`
- L91 _private prototype_ `void ClearBufferInfo(FExternalBufferInfo& BufferInfo);`
- L92 _private prototype_ `void ClearRegisteredTextures();`
- L93 _private prototype_ `void ClearRegisteredBuffers();`
- L96 _private member_ `bool bInitialized = false;`
- L97 _private member_ `TMap<void*, FExternalBufferInfo> RegisteredBuffers;`
- L98 _private member_ `TMap<FRHITexture*, FTextureInfo> RegisteredTextures;`
- L100 _private member_ `uint32 BufferAddressAlignment = 0;`
- L101 _private member_ `uint32 BufferGpuStrideAlignment = 0;`
- L102 _private member_ `uint32 SemaphoreAddressAlignment = 0;`
- L103 _private member_ `uint32 SemaphoreAllocSize = 0;`
- L104 _private member_ `uint32 SemaphorePayloadOffset = 0;`
- L105 _private member_ `uint32 SemaphorePayloadSize = 0;`
- L107 _private member_ `FCriticalSection CriticalSection;`

#### struct `UE::GPUTextureTransfer::Private::FTextureTransferBase::DVPSync`  
`struct DVPSync`  
_L43-54_
- L45 _public prototype_ `DVPSync(uint32 SemaphoreAllocSize, uint32 SemaphoreAlignment);`
- L46 _public prototype_ `~DVPSync();`
- L48 _public member_ `volatile uint32* Semaphore = nullptr;`
- L49 _public member_ `volatile uint32 ReleaseValue = 0;`
- L50 _public member_ `volatile uint32 AcquireValue = 0;`
- L51 _public member_ `DVPSyncObjectHandle DVPSyncObject = 0;`
- L53 _public prototype_ `void SetValue(uint32 Value);`

#### struct `UE::GPUTextureTransfer::Private::FTextureTransferBase::FExternalBufferInfo`  
`struct FExternalBufferInfo`  
_L56-67_
- L58 _public member_ `uint32 Width = 0;`
- L59 _public member_ `uint32 Height = 0;`
- L60 _public member_ `uint32 Stride = 0;`
- L61 _public member_ `TUniquePtr<DVPSync> SystemMemorySync;`
- L62 _public member_ `TUniquePtr<DVPSync> GPUMemorySync;`
- L63 _public member_ `DVPBufferHandle DVPHandle = 0;`
- L66 _public member_ `DVPBufferHandle PendingTextureHandle = 0;` — Handle to the texture currently being transferred to this buffer.

#### struct `UE::GPUTextureTransfer::Private::FTextureTransferBase::FTextureInfo`  
`struct FTextureInfo`  
_L69-78_
- L71 _public member_ `DVPBufferHandle DVPHandle = 0;`
- L77 _public member_ `} External;` — D3D12 and Vulkan only

#### union `UE::GPUTextureTransfer::Private::FTextureTransferBase::FTextureInfo::(anonymous)`  
``  
_L74-77_

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace GPUTextureTransfer` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::GPUTextureTransfer`)
- L75 _member_ `void* Handle = nullptr;` (scope `UE::GPUTextureTransfer::Private::FTextureTransferBase::FTextureInfo::__anon6754c7ad010a`)
- L76 _member_ `int Fd;` (scope `UE::GPUTextureTransfer::Private::FTextureTransferBase::FTextureInfo::__anon6754c7ad010a`)

### `Plugins/Media/MediaIOFramework/Source/GPUTextureTransfer/Private/VulkanTextureTransfer.h` (Private)


#### class `UE::GPUTextureTransfer::Private::FVulkanTextureTransfer`  
`class FVulkanTextureTransfer : public FTextureTransferBase`  
_L12-29_
- inherits: `FTextureTransferBase`
- L15 _protected prototype_ `virtual DVPStatus Init_Impl() override;`
- L16 _protected prototype_ `virtual DVPStatus GetConstants_Impl(uint32* OutBufferAddrAlignment, uint32* OutBufferGPUStrideAlignment, uint32* OutSemaphoreAddrAlignment, uint32* OutSemaphoreAllocSize, uint32* OutSemaphorePayloadOffset, uint32* OutSemaphorePayloadSize) const override;`
- L17 _protected prototype_ `virtual DVPStatus BindBuffer_Impl(DVPBufferHandle InBufferHandle) const override;`
- L18 _protected prototype_ `virtual DVPStatus CreateGPUResource_Impl(const FRegisterDMATextureArgs& InArgs, FTextureInfo* OutTextureInfo) const override;`
- L19 _protected prototype_ `virtual DVPStatus UnbindBuffer_Impl(DVPBufferHandle InBufferHandle) const override;`
- L20 _protected prototype_ `virtual DVPStatus CloseDevice_Impl() const override;`
- L21 _protected prototype_ `virtual DVPStatus MapBufferWaitAPI_Impl(DVPBufferHandle InHandle) const;`
- L22 _protected prototype_ `virtual DVPStatus MapBufferEndAPI_Impl(DVPBufferHandle InHandle) const;`
- L26 _private member_ `VkInstance VulkanInstance = nullptr;`
- L27 _private member_ `VkDevice VulkanDevice = nullptr;`
- L28 _private member_ `VkQueue VulkanQueue = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace GPUTextureTransfer` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::GPUTextureTransfer`)

### `Plugins/Media/MediaIOFramework/Source/GPUTextureTransfer/Public/GPUTextureTransfer.h` (Public)


#### enum `UE::GPUTextureTransfer::ERHI`  
`enum class ERHI : uint8`  
_L11-18_
- L13 _public enumerator_ `Invalid`
- L14 _public enumerator_ `D3D11`
- L15 _public enumerator_ `D3D12`
- L16 _public enumerator_ `Vulkan`
- L17 _public enumerator_ `RHI_MAX`

#### enum `UE::GPUTextureTransfer::EPixelFormat`  
`enum class EPixelFormat : uint8_t`  
_L22-26_
- L24 _public enumerator_ `PF_8Bit`
- L25 _public enumerator_ `PF_10Bit`

#### struct `UE::GPUTextureTransfer::FRegisterDMABufferArgs`  
`struct FRegisterDMABufferArgs`  
_L28-35_
- L30 _public member_ `void* Buffer = nullptr;`
- L31 _public member_ `uint32 Width = 0;`
- L32 _public member_ `uint32 Height = 0;`
- L33 _public member_ `uint32 Stride = 0;`
- L34 _public member_ `EPixelFormat PixelFormat = EPixelFormat::PF_8Bit;`

#### struct `UE::GPUTextureTransfer::FRegisterDMATextureArgs`  
`struct FRegisterDMATextureArgs`  
_L37-48_
- L39 _public member_ `FRHITexture* RHITexture = nullptr;`
- L40 _public member_ `void* RHIResourceMemory = nullptr;` — Vulkan only
- L41 _public member_ `uint32 Width = 0;`
- L42 _public member_ `uint32 Height = 0;`
- L43 _public member_ `EPixelFormat PixelFormat = EPixelFormat::PF_8Bit;`
- L45 _public member_ `uint32 Stride = 0;` — Stride in bytes
- L47 _public member_ `void* SharedHandle = nullptr;` — Only for VK

#### enum `UE::GPUTextureTransfer::ETransferDirection`  
`enum class ETransferDirection :uint8`  
_L50-54_
- L52 _public enumerator_ `GPU_TO_CPU`
- L53 _public enumerator_ `CPU_TO_GPU`

#### class `UE::GPUTextureTransfer::ITextureTransfer`  
`class ITextureTransfer`  
_L56-112_
- L59 _public prototype_ `virtual ~ITextureTransfer() = default;`
- L62 _public prototype_ `virtual void WaitForGPU(FRHITexture* InRHITexture) = 0;` — Wait for a signal that the texture is ready to use by DVP. (Experimental)
- L64 _public prototype_ `virtual void ThreadPrep() = 0;` — Must be called called before TransferTexture on the same thread.
- L66 _public prototype_ `virtual void ThreadCleanup() = 0;` — Must be called called after TransferTexture on the same thread.
- L68 _public prototype_ `virtual void RegisterBuffer(const FRegisterDMABufferArgs& Args) = 0;`
- L69 _public prototype_ `virtual void UnregisterBuffer(void* InBuffer) = 0;`
- L71 _public prototype_ `virtual void RegisterTexture(const FRegisterDMATextureArgs& Args) = 0;`
- L72 _public prototype_ `virtual void UnregisterTexture(FRHITexture* RHITexture) = 0;`
- L77 _public prototype_ `virtual void LockTexture(FRHITexture* RHITexture) = 0;` — Calling this will prevent the DVP library from using the RHI texture passed as argument until Unlock is called.
- L82 _public prototype_ `virtual void UnlockTexture(FRHITexture* RHITexture) = 0;` — Calling this will allow the DVP library to access the RHI texture passed as argument.
- L84 _public prototype_ `virtual bool BeginSync(void* InBuffer, ETransferDirection TransferDirection) = 0;`
- L85 _public prototype_ `virtual void EndSync(void* InBuffer) = 0;`
- L98 _public prototype_ `virtual bool TransferTexture(void* InBuffer, FRHITexture* RHITexture, ETransferDirection TransferDirection) = 0;` — RegisterBuffer(BufferArgs); TransferTexture(InArgs.Buffer, RHITexture, InTransferDirection); BeginSync(InArgs.Buffer, InTransferDirection); Schedule output frame EndSync(Buffer);
- L103 _public prototype_ `virtual uint32 GetBufferAlignment() const = 0;` — Get the recommended alignment for the cpu buffer.
- L108 _public prototype_ `virtual uint32 GetTextureStride() const = 0;` — Get the recommended stride for textures that will be  copied.
- L110 _public prototype_ `virtual bool Initialize() = 0;`
- L111 _public prototype_ `virtual bool Uninitialize() = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace GPUTextureTransfer` (scope `UE`)
- L20 _typedef_ `using FLoggingCallbackPtr = void(*)(const TCHAR* Format, ...);` (scope `UE::GPUTextureTransfer`)

### `Plugins/Media/MediaIOFramework/Source/GPUTextureTransfer/Public/GPUTextureTransferModule.h` (Public)


#### class `FGPUTextureTransferModule`  
`class FGPUTextureTransferModule : public IModuleInterface`  
_L22-75_
- inherits: `IModuleInterface`
- L25 _public prototype_ `static FGPUTextureTransferModule& Get();`
- L28 _public prototype_ `static bool IsAvailable();` — `UE_DEPRECATED(5.6, "Use IsInitialized() and IsEnabled() instead.")`
- L31 _public prototype_ `virtual void StartupModule() override;`
- L32 _public prototype_ `virtual void ShutdownModule() override;`
- L36 _public prototype_ `void Initialize();` — Load the DVP DLL and intialize the API.Note: This is a blocking call and could take upwards of 2s.
- L39 _public prototype_ `UE::GPUTextureTransfer::TextureTransferPtr GetTextureTransfer();` — Get a texture transfer object that acts as a layer above the DVP library.
- L42 _public prototype_ `bool IsInitialized() const;` — Returns whether the DVP library was loaded and initialized. If this returns false, GetTextureTransfer will trigger the library to initialize.
- L45 _public prototype_ `bool IsEnabled() const;` — Returns whether GPUDirect is enabled. This reflects the value of MediaIO.EnableGPUDirect. You should check IsAvailable to know if the library is initialized.
- L49 _private prototype_ `bool LoadGPUDirectBinary();` — Load the DVP dll.
- L52 _private prototype_ `void InitializeTextureTransfer();` — Initialize the DVP library and creates the ITextureTransfer objects.
- L55 _private prototype_ `void UninitializeTextureTransfer();` — Clean up and uninitializes the DVP library.
- L58 _private prototype_ `void OnEnableGPUDirectCVarChange(class IConsoleVariable* ConsoleVariable);` — Initializes the DVP library when MediaIO.EnableGPUDirect is set to 1.
- L62 _private member_ `static constexpr uint8 RHI_MAX = static_cast<uint8>(UE::GPUTextureTransfer::ERHI::RHI_MAX);` — Max number of RHIs that GPUTextureTransfer supports.
- L65 _private member_ `void* TextureTransferHandle = nullptr;` — DVP DLL Handle.
- L68 _private member_ `std::atomic<bool> bInitialized = false;` — Tracks whether the dvp library and texture transfer objects were successfully created.
- L71 _private member_ `TArray<UE::GPUTextureTransfer::TextureTransferPtr> TransferObjects;` — Texture transfer objects.
- L74 _private member_ `FGPUDriverInfo CachedDriverInfo;` — Cached information about the GPU Driver.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GPUTEXTURETRANSFER_API`
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGPUTextureTransfer, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGPUTextureTransfer, Log, All);`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace GPUTextureTransfer` (scope `UE`)
- L19 _typedef_ `using TextureTransferPtr = TSharedPtr<ITextureTransfer>;` (scope `UE::GPUTextureTransfer`)
