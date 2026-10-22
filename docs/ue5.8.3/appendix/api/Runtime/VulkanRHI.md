# Runtime / VulkanRHI

- module root: `Source/Runtime/VulkanRHI`
- headers: 50; symbols: 4314
- symbol kinds: class=122, delegate=62, enum=48, enumerator=247, externvar=18, function=1035, macro=166, member=1288, namespace=18, prototype=1097, struct=142, typedef=63, union=5, variable=3
- PrivateDependencyModuleNames: ApplicationCore, BuildSettings, Core, CoreUObject, Engine, GoogleGameSDK, HeadMountedDisplay, Launch, PreLoadScreen, RHI, RHICore, RenderCore, TraceLog
- PrivateIncludePathModuleNames: Launch
- PublicIncludePathModuleNames: Vulkan

### `Source/Runtime/VulkanRHI/Private/Android/AndroidVulkanPlatformDefines.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/VulkanRHI/Private/Android/VulkanAndroidPlatform.h` (Private)


#### class `FVulkanAndroidPlatformWindowContext`  
`class FVulkanAndroidPlatformWindowContext`  
_L55-113_
- L58 _public function_ `FVulkanAndroidPlatformWindowContext(void* InWindowHandle)`
- L74 _public function_ `FVulkanAndroidPlatformWindowContext(TOptional<FAndroidWindow::FNativeAccessor> WindowContainerIn)`
- L90 _public function_ `static bool CanCreateSwapchainOnDemand()` — we dont have a locked window to create swapchains during present, android will use the SetRHIOnReleaseWindowCallback / SetRHIOnReInitWindowCallback to create as required.
- L91 _public function_ `bool IsValid() const`
- L96 _public function_ `ANativeWindow* GetANativeWindow() const`
- L101 _public function_ `void* GetWindowHandle() const`
- L107 _public function_ `uint32 GetWindowId() const` — Android tracks window lifetime via the native accessor, not an SDL-style window id.
- L110 _private member_ `ANativeWindow* NativeWindow = nullptr;`
- L111 _private member_ `FAndroidWindow* AndroidWindow = nullptr;`
- L112 _private member_ `TOptional<FAndroidWindow::FNativeAccessor> WindowContainer;`

#### class `FVulkanAndroidPlatform`  
`class FVulkanAndroidPlatform : public FVulkanGenericPlatform`  
_L117-306_
- inherits: `FVulkanGenericPlatform`
- L120 _public prototype_ `static bool LoadVulkanLibrary();`
- L121 _public prototype_ `static bool LoadVulkanInstanceFunctions(VkInstance inInstance);`
- L122 _public prototype_ `static void FreeVulkanLibrary();`
- L124 _public prototype_ `static void InitDevice(FVulkanDevice* InDevice);`
- L125 _public prototype_ `static void PostInitGPU(const FVulkanDevice& InDevice);`
- L127 _public prototype_ `static void GetInstanceExtensions(FVulkanInstanceExtensionArray& OutExtensions);`
- L128 _public prototype_ `static void GetInstanceLayers(TArray<const ANSICHAR*>& OutLayers);`
- L129 _public prototype_ `static void GetDeviceExtensions(FVulkanDevice* Device, FVulkanDeviceExtensionArray& OutExtensions);`
- L130 _public prototype_ `static void GetDeviceLayers(TArray<const ANSICHAR*>& OutLayers);`
- L131 _public prototype_ `static void NotifyFoundDeviceLayersAndExtensions(VkPhysicalDevice PhysicalDevice, const TArray<const ANSICHAR*>& Layers, const TArray<const ANSICHAR*>& Extensions);`
- L133 _public prototype_ `static void CreateSurface(FVulkanPlatformWindowContext& WindowContext, VkInstance Instance, VkSurfaceKHR* OutSurface);`
- L135 _public prototype_ `static void* GetHardwareWindowHandle();`
- L137 _public prototype_ `static bool SupportsBCTextureFormats();`
- L138 _public function_ `static bool SupportsASTCTextureFormats()`
- L139 _public function_ `static bool SupportsETC2TextureFormats()`
- L141 _public function_ `static bool SupportsR16UnormTextureFormat()` — GLES does not support R16Unorm, so all Android has to fallback to R16F instead
- L143 _public function_ `static bool SupportsQuerySurfaceProperties()`
- L145 _public function_ `static void SetupFeatureLevels(TArrayView<EShaderPlatform> ShaderPlatformForFeatureLevel)`
- L165 _public prototype_ `static bool SupportsTimestampRenderQueries();`
- L167 _public prototype_ `static bool SupportsDynamicResolution();`
- L169 _public function_ `static bool RequiresMobileRenderer()`
- L178 _public function_ `static ERHIFeatureLevel::Type GetFeatureLevel(ERHIFeatureLevel::Type RequestedFeatureLevel)`
- L187 _public function_ `static bool SupportsVolumeTextureRendering()`
- L189 _public prototype_ `static void OverridePlatformHandlers(bool bInit);`
- L191 _public prototype_ `static bool IsWaitingForWindowCreated();`
- L195 _public function_ `static bool RequiresPresentLayoutFix()` — #todo-rco: Detect Mali?
- L198 _public prototype_ `static bool HasUnifiedMemory();`
- L200 _public function_ `static bool HasUnifiedMemory()`
- L204 _public function_ `static bool SupportParallelRenderingTasks()` — Assume most devices can't use the extra cores for running parallel tasks
- L207 _public function_ `static bool RequiresSwapchainGeneralInitialLayout()` — #todo-rco: Detect Mali? Doing a clear on ColorAtt layout on empty cmd buffer causes issues
- L209 _public function_ `static bool RequiresWaitingForFrameCompletionEvent()`
- L212 _public function_ `static bool SupportsNullPixelShader()` — Does the platform allow a nullptr Pixelshader on the pipeline
- L215 _public function_ `static bool RequiresDepthStencilFullWrite()` — Does the platform require depth to be written on stencil clear
- L216 _public prototype_ `static void SetupRequiresDepthStencilFullWriteWorkaround(const FVulkanDevice& Device);`
- L219 _public function_ `static bool RequiresMergedDepthStencilLayout()` — Does the platform require to avoid VkAttachmentDescriptionStencilLayout in favor of merged depth-stencil layouts
- L220 _public prototype_ `static void SetupRequiresMergedDepthStencilLayoutWorkaround(const FVulkanDevice& Device);`
- L222 _public prototype_ `static bool FramePace(FVulkanDevice& Device, void* WindowHandle, VkSwapchainKHR Swapchain, uint32 PresentID, VkPresentInfoKHR& Info);`
- L224 _public prototype_ `static VkResult Present(VkQueue Queue, VkPresentInfoKHR& PresentInfo);`
- L226 _public prototype_ `static VkResult CreateSwapchainKHR(FVulkanPlatformWindowContext& WindowContext, VkPhysicalDevice PhysicalDevice, VkDevice Device, const VkSwapchainCreateInfoKHR* CreateInfo, const VkAllocationCallbacks* Allocator, VkSwapchainKHR* Swapchain);`
- L228 _public prototype_ `static void DestroySwapchainKHR(VkDevice Device, VkSwapchainKHR Swapchain, const VkAllocationCallbacks* Allocator);`
- L231 _public prototype_ `static VkPipelineCache PrecompilePSO(FVulkanDevice* Device, const TArrayView<const uint8> ContextData, const TArrayView<const uint8> OptionalPSOCacheData, FGraphicsPipelineStateInitializer::EPSOPrecacheCompileType PSOCompileType, const VkGraphicsPipelineCreateInfo* PipelineInfo, const FGfxPipelineDesc* GfxEntry, const FVulkanRenderTargetLayout* RTLayout, TArrayView<const uint32_t> VS, TArrayView<const uint32_t> PS, size_t& AfterSize, FString* FailureMessageOUT = nullptr);` — handle precompile of PSOs, send to an android specific precompile external process.
- L233 _public prototype_ `static FString GetCompiledPSOCacheTopFolderPath();`
- L235 _public prototype_ `static bool AreRemoteCompileServicesActive();`
- L236 _public prototype_ `static bool StartRemoteCompileServices(int NumServices);`
- L237 _public prototype_ `static void StopRemoteCompileServices();`
- L240 _public function_ `static bool RecreateSwapchainOnFail()` — Do not attempt to immediately recreate swapchain
- L244 _public prototype_ `static void RecreateSwapChain(void* NewNativeWindow);` — original window behavior swapchain functions. ignored with the new window method.
- L245 _public prototype_ `static void DestroySwapChain();`
- L247 _public function_ `static VkFormat GetPlatform5551FormatWithFallback(VkFormat& OutFallbackFormat0, VkFormat& OutFallbackFormat1)`
- L255 _public prototype_ `static void SetupImageMemoryRequirementWorkaround(const FVulkanDevice& InDevice);` — Setup platform to use a workaround to reduce textures memory requirements
- L256 _public prototype_ `static void SetImageMemoryRequirementWorkaround(VkImageCreateInfo& ImageCreateInfo);`
- L259 _public prototype_ `static FString GetVulkanProfileNameForFeatureLevel(ERHIFeatureLevel::Type FeatureLevel, bool bRaytracing);` — Returns the profile name to look up for a given feature level on a platform
- L261 _public function_ `static VkShaderStageFlags RequiredWaveOpsShaderStageFlags(VkShaderStageFlags VulkanDeviceShaderStageFlags)`
- L267 _public prototype_ `static void OnGPUCrash(const TCHAR* Message);`
- L269 _public function_ `static VkTimeDomainKHR GetTimeDomain()`
- L272 _public prototype_ `static void OnCreatePipelineCrash(struct FCrashContextExtendedWriter& Writer, TConstArrayView<FVulkanShader*> Shaders, TStringView<TCHAR> ExtraInfo, bool bIsPrecache);`
- L276 _public member_ `static bool bSwappyEnabledAtRHIInit;`
- L280 _protected member_ `static void* VulkanLib;`
- L281 _protected member_ `static bool bAttemptedLoad;`
- L284 _protected member_ `static bool bHasGoogleDisplayTiming;`
- L285 _protected member_ `static TUniquePtr<class FGDTimingFramePacer> GDTimingFramePacer;`
- L288 _protected member_ `static TUniquePtr<struct FAndroidVulkanFramePacer> FramePacer;`
- L289 _protected member_ `static int32 CachedFramePace;`
- L290 _protected member_ `static int32 CachedRefreshRate;`
- L291 _protected member_ `static int32 CachedSyncInterval;`
- L292 _protected member_ `static int32 SuccessfulRefreshRateFrames;`
- L293 _protected member_ `static int32 UnsuccessfulRefreshRateFrames;`
- L294 _protected member_ `static TArray<TArray<ANSICHAR>> DebugVulkanDeviceLayers;`
- L295 _protected member_ `static TArray<TArray<ANSICHAR>> DebugVulkanInstanceLayers;`
- L296 _protected member_ `static TArray<TArray<ANSICHAR>> SwappyRequiredExtensions;`
- L298 _protected member_ `static int32 AFBCWorkaroundOption;`
- L299 _protected member_ `static int32 ASTCWorkaroundOption;`
- L301 _protected member_ `static bool bRequiresDepthStencilFullWrite;`
- L302 _protected member_ `static bool bRequiresMergedRenderPassDepthStencilLayout;`
- L303 _protected member_ `static bool bRequiresWaitingForFrameCompletionEvent;`
- L305 _protected member_ `static FAutoConsoleVariableRef CVarVulkanRequiresWaitingForFrameCompletionEvent;`

#### class `FGDTimingFramePacer`  
`class FGDTimingFramePacer : FNoncopyable`  
_L309-351_
- inherits: `FNoncopyable`
- L312 _public prototype_ `FGDTimingFramePacer(VkDevice InDevice, VkSwapchainKHR InSwapChain);`
- L314 _public function_ `const VkPresentTimesInfoGOOGLE* GetPresentTimesInfo() const`
- L319 _public prototype_ `void ScheduleNextFrame(uint32 InPresentID, int32 FramePace, int32 RefreshRate);` — Call right before present
- L322 _private prototype_ `void UpdateSyncDuration(int32 FramePace, int32 RefreshRate);`
- L324 _private prototype_ `uint64 PredictLastScheduledFramePresentTime(uint32 CurrentPresentID) const;`
- L325 _private prototype_ `uint64 CalculateMinPresentTime(uint64 CpuPresentTime) const;`
- L326 _private prototype_ `uint64 CalculateMaxPresentTime(uint64 CpuPresentTime) const;`
- L327 _private prototype_ `uint64 CalculateNearestVsTime(uint64 ActualPresentTime, uint64 TargetTime) const;`
- L328 _private prototype_ `void PollPastFrameInfo();`
- L339 _private member_ `VkDevice Device;`
- L340 _private member_ `VkSwapchainKHR SwapChain;`
- L342 _private member_ `VkPresentTimesInfoGOOGLE PresentTimesInfo;`
- L343 _private member_ `VkPresentTimeGOOGLE PresentTime;`
- L344 _private member_ `uint64 RefreshDuration = 0;`
- L345 _private member_ `uint64 HalfRefreshDuration = 0;`
- L347 _private member_ `FKnownFrameInfo LastKnownFrameInfo;`
- L348 _private member_ `uint64 LastScheduledPresentTime = 0;`
- L349 _private member_ `uint64 SyncDuration = 0;`
- L350 _private member_ `int32 FramePace = 0;`

#### struct `FGDTimingFramePacer::FKnownFrameInfo`  
`struct FKnownFrameInfo`  
_L331-336_
- L333 _public member_ `bool bValid = false;`
- L334 _public member_ `uint32 PresentID = 0;`
- L335 _public member_ `uint64 ActualPresentTime = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define VK_USE_PLATFORM_ANDROID_KHR 1`
- L10 _macro_ `#define VULKAN_ENABLE_DUMP_LAYER 0`
- L11 _macro_ `#define VULKAN_DYNAMICALLYLOADED 1`
- L12 _macro_ `#define VULKAN_SHOULD_ENABLE_DRAW_MARKERS (UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG)`
- L13 _macro_ `#define VULKAN_USE_IMAGE_ACQUIRE_FENCES 0`
- L14 _macro_ `#define VULKAN_USE_CREATE_ANDROID_SURFACE 1`
- L15 _macro_ `#define VULKAN_SHOULD_USE_LLM (UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT) // If enabled Vulkan will report detailed allocation statistics, overrides some tags with custom ones`
- L16 _macro_ `#define VULKAN_SHOULD_USE_COMMANDWRAPPERS VULKAN_SHOULD_USE_LLM //LLM on Vulkan needs command wrappers to account for vkallocs`
- L17 _macro_ `#define VULKAN_ENABLE_LRU_CACHE 1`
- L18 _macro_ `#define VULKAN_SUPPORTS_GOOGLE_DISPLAY_TIMING 1`
- L19 _macro_ `#define VULKAN_PURGE_SHADER_MODULES 0`
- L20 _macro_ `#define VULKAN_SUPPORTS_DEDICATED_ALLOCATION 0`
- L21 _macro_ `#define VULKAN_SUPPORTS_ASTC_DECODE_MODE 1`
- L22 _macro_ `#define VULKAN_SUPPORTS_SCALAR_BLOCK_LAYOUT 1`
- L23 _macro_ `#define VULKAN_SUPPORTS_TRANSIENT_RESOURCE_ALLOCATOR 0`
- L24 _macro_ `#define VULKAN_SUPPORTS_DRIVER_PROPERTIES 0`
- L25 _macro_ `#define VULKAN_SUPPORTS_DESCRIPTOR_INDEXING 1`
- L26 _macro_ `#define VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH 0`
- L30 _macro_ `#define VULKAN_HAS_DEBUGGING_ENABLED (UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT || UE_BUILD_TEST)` — Enabling debugging gives access to features that have little cost unless enabled (Validation Layer, Renderdoc detection, etc.) Because Development is slower on Android, more testing using validation layer occurs on Test builds.
- L32 _macro_ `#define UE_VK_API_VERSION VK_API_VERSION_1_1`
- L36 _macro_ `# define VK_TYPE_TO_STRING(Type, Value) ANSI_TO_TCHAR(string_##Type(Value))`
- L40 _macro_ `#define ENUM_VK_ENTRYPOINTS_PLATFORM_BASE(EnumMacro)`
- L42 _macro_ `#define ENUM_VK_ENTRYPOINTS_PLATFORM_INSTANCE(EnumMacro) \`
- L46 _macro_ `#define ENUM_VK_ENTRYPOINTS_OPTIONAL_PLATFORM_INSTANCE(EnumMacro) \`
- L53 _prototype_ `extern bool IsInAndroidEventThread();`
- L115 _typedef_ `using FVulkanPlatformWindowContext = FVulkanAndroidPlatformWindowContext;`
- L354 _typedef_ `typedef FVulkanAndroidPlatform FVulkanPlatform;`

### `Source/Runtime/VulkanRHI/Private/Linux/LinuxVulkanPlatformDefines.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/VulkanRHI/Private/Linux/VulkanLinuxPlatform.h` (Private)


#### class `FVulkanLinuxPlatformWindowContext`  
`class FVulkanLinuxPlatformWindowContext : public FVulkanGenericPlatformWindowContext`  
_L38-46_
- inherits: `FVulkanGenericPlatformWindowContext`
- desc: Carries the SDL_Window* plus the SDL window id captured at construction time (while the window is provably alive). The id rides with the context through swapchain creation so the surface can be released by that immutable, never-recycled id -- never by re-deriving it from a pointer that may be stale or reused by destroy time. Ctor/IsValid are defined out-of-line so SDL stays out of this header and IsValid can reach FVulkanLinuxPlatform::IsWindowValid.
- L41 _public prototype_ `explicit FVulkanLinuxPlatformWindowContext(void* InWindowHandle);`
- L42 _public function_ `uint32 GetWindowId() const`
- L43 _public prototype_ `bool IsValid() const;`
- L45 _private member_ `uint32 WindowId = 0;`

#### class `FVulkanLinuxPlatform`  
`class FVulkanLinuxPlatform : public FVulkanGenericPlatform`  
_L50-82_
- inherits: `FVulkanGenericPlatform`
- L53 _public prototype_ `static bool IsSupported();`
- L55 _public prototype_ `static bool LoadVulkanLibrary();`
- L56 _public prototype_ `static bool LoadVulkanInstanceFunctions(VkInstance inInstance);`
- L57 _public prototype_ `static void FreeVulkanLibrary();`
- L59 _public prototype_ `static void GetInstanceExtensions(FVulkanInstanceExtensionArray& OutExtensions);`
- L60 _public function_ `static void GetInstanceLayers(TArray<const ANSICHAR*>& OutLayers)`
- L61 _public prototype_ `static void GetDeviceExtensions(FVulkanDevice* Device, FVulkanDeviceExtensionArray& OutExtensions);`
- L62 _public function_ `static void GetDeviceLayers(TArray<const ANSICHAR*>& OutLayers)`
- L64 _public prototype_ `static void CreateSurface(FVulkanPlatformWindowContext& WindowContext, VkInstance Instance, VkSurfaceKHR* OutSurface);`
- L65 _public prototype_ `static void DestroySurface(uint32 WindowId, VkInstance Instance, VkSurfaceKHR Surface);`
- L68 _public prototype_ `static bool IsWindowValid(void* WindowHandle);` — Returns false if the native window handle has been destroyed (e.g. Wayland surface invalidated).
- L71 _public prototype_ `static bool TryConsumeSwapchainRecreateRequest(void* WindowHandle);` — Test-and-clear the swapchain-recreate request set by FLinuxWindow::Show() after a Hide/Show cycle.
- L73 _public function_ `static VkTimeDomainKHR GetTimeDomain()`
- L75 _public function_ `static bool SupportsASTCTextureFormats()`
- L76 _public function_ `static bool SupportsETC2TextureFormats()`
- L79 _protected member_ `static void* VulkanLib;`
- L80 _protected member_ `static bool bLoadedSDLVulkanLibrary;`
- L81 _protected member_ `static bool bAttemptedLoad;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define VULKAN_DYNAMICALLYLOADED 1`
- L9 _macro_ `#define VULKAN_ENABLE_DUMP_LAYER 0`
- L10 _macro_ `#define VULKAN_SHOULD_DEBUG_IN_DEVELOPMENT 1`
- L11 _macro_ `#define VULKAN_SHOULD_ENABLE_DRAW_MARKERS (UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT)`
- L12 _macro_ `#define VULKAN_SIGNAL_UNIMPLEMENTED() checkf(false, TEXT("Unimplemented vulkan functionality: %hs"), __PRETTY_FUNCTION__)`
- L13 _macro_ `#define VULKAN_SUPPORTS_SCALAR_BLOCK_LAYOUT 1`
- L14 _macro_ `#define VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH 1`
- L16 _macro_ `#define UE_VK_API_VERSION VK_API_VERSION_1_1`
- L20 _macro_ `# define VK_TYPE_TO_STRING(Type, Value) ANSI_TO_TCHAR(string_##Type(Value))`
- L21 _macro_ `# define VK_FLAGS_TO_STRING(Type, Value) ANSI_TO_TCHAR(string_##Type(Value).c_str())`
- L24 _macro_ `#define ENUM_VK_ENTRYPOINTS_PLATFORM_BASE(EnumMacro)`
- L26 _macro_ `#define ENUM_VK_ENTRYPOINTS_PLATFORM_INSTANCE(EnumMacro)`
- L28 _macro_ `#define ENUM_VK_ENTRYPOINTS_OPTIONAL_PLATFORM_INSTANCE(EnumMacro)`
- L48 _typedef_ `typedef FVulkanLinuxPlatformWindowContext FVulkanPlatformWindowContext;`
- L84 _typedef_ `typedef FVulkanLinuxPlatform FVulkanPlatform;`

### `Source/Runtime/VulkanRHI/Private/Mac/MacVulkanPlatformDefines.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/VulkanRHI/Private/VulkanBarriers.h` (Private)


#### struct `FVulkanPipelineBarrier`  
`struct FVulkanPipelineBarrier`  
_L13-37_
- L15 _public prototype_ `FVulkanPipelineBarrier() = default;`
- L17 _public typedef_ `using MemoryBarrierArrayType = TArray<VkMemoryBarrier2, TInlineAllocator<1>>;`
- L18 _public typedef_ `using ImageBarrierArrayType = TArray<VkImageMemoryBarrier2, TInlineAllocator<2>>;`
- L19 _public typedef_ `using BufferBarrierArrayType = TArray<VkBufferMemoryBarrier2>;`
- L21 _public member_ `MemoryBarrierArrayType MemoryBarriers;`
- L22 _public member_ `ImageBarrierArrayType ImageBarriers;`
- L23 _public member_ `BufferBarrierArrayType BufferBarriers;`
- L25 _public prototype_ `void AddMemoryBarrier(VkAccessFlags SrcAccessFlags, VkAccessFlags DstAccessFlags, VkPipelineStageFlags SrcStageMask, VkPipelineStageFlags DstStageMask);`
- L26 _public prototype_ `void AddFullImageLayoutTransition(const FVulkanTexture& Texture, VkImageLayout SrcLayout, VkImageLayout DstLayout);`
- L27 _public prototype_ `void AddImageLayoutTransition(VkImage Image, VkImageLayout SrcLayout, VkImageLayout DstLayout, const VkImageSubresourceRange& SubresourceRange);`
- L28 _public prototype_ `void AddImageAccessTransition(const FVulkanTexture& Surface, ERHIAccess SrcAccess, ERHIAccess DstAccess, const VkImageSubresourceRange& SubresourceRange, VkImageLayout& InOutLayout);`
- L29 _public prototype_ `void Execute(VkCommandBuffer CmdBuffer);`
- L30 _public prototype_ `void Execute(FVulkanCommandBuffer* CmdBuffer);`
- L32 _public prototype_ `static VkImageSubresourceRange MakeSubresourceRange(VkImageAspectFlags AspectMask, uint32 FirstMip = 0, uint32 NumMips = VK_REMAINING_MIP_LEVELS, uint32 FirstLayer = 0, uint32 NumLayers = VK_REMAINING_ARRAY_LAYERS);`
- L35 _public prototype_ `static VkImageLayout GetDefaultLayout(const FVulkanTexture& VulkanTexture, ERHIAccess DesiredAccess);` — Predetermined layouts for given RHIAccess
- L36 _public prototype_ `static VkImageLayout GetDepthOrStencilLayout(ERHIAccess Access);`

#### struct `FVulkanTransitionData`  
`struct FVulkanTransitionData`  
_L39-45_
- L41 _public member_ `ERHIPipeline SrcPipelines, DstPipelines;`
- L41 _public member_ `ERHIPipeline SrcPipelines, DstPipelines;`
- L42 _public member_ `TRefCountPtr<FVulkanSemaphore> Semaphore;` — used for cross queue
- L43 _public member_ `VkEvent EventHandle = VK_NULL_HANDLE;` — used for split barriers
- L44 _public member_ `TArray<FRHITransitionInfo> TransitionInfos;`

### `Source/Runtime/VulkanRHI/Private/VulkanBindlessDescriptorManager.h` (Private)


#### class `FVulkanBindlessDescriptorManager`  
`class FVulkanBindlessDescriptorManager`  
_L16-204_
- desc: Manager for resource descriptors used in bindless rendering.
- L33 _public member_ `static constexpr uint32 RequiredPushDataSize = 256u;`
- L34 _public prototype_ `static uint32 GetBindingPushDataOffset(EShaderFrequency Frequency, uint32 BindingIndex);`
- L36 _public prototype_ `FVulkanBindlessDescriptorManager(FVulkanDevice& InDevice);`
- L37 _public prototype_ `~FVulkanBindlessDescriptorManager();`
- L39 _public prototype_ `void Init();`
- L40 _public prototype_ `void Deinit();`
- L42 _public prototype_ `FRHIDescriptorHandle AllocateDescriptor(ERHIDescriptorType DescriptorType);`
- L43 _public prototype_ `TOptional<FRHIDescriptorAllocation> AllocateDescriptors(ERHIDescriptorType DescriptorType, uint32 DescriptorCount);`
- L44 _public prototype_ `void FreeDescriptor(FRHIDescriptorHandle DescriptorHandle);`
- L45 _public prototype_ `void FreeDescriptors(FRHIDescriptorAllocation Allocation, ERHIDescriptorType DescriptorType);`
- L48 _public prototype_ `void UpdateDescriptor(FRHIDescriptorHandle DescriptorHandle, const VkSamplerCreateInfo& SamplerCreateInfo);` — Descriptor Heap update functions
- L49 _public function_ `void UpdateDescriptor(const FVulkanContextArray& Contexts, FRHIDescriptorHandle DescriptorHandle, const VkImageDescriptorInfoEXT& ImageDescriptorInfo, bool bImmediateUpdate = true)`
- L54 _public function_ `void UpdateDescriptor(const FVulkanContextArray& Contexts, FRHIDescriptorHandle DescriptorHandle, const VkTexelBufferDescriptorInfoEXT& TexelBufferDescriptorInfo, bool bImmediateUpdate = true)`
- L59 _public function_ `void UpdateDescriptor(const FVulkanContextArray& Contexts, FRHIDescriptorHandle DescriptorHandle, const VkDeviceAddressRangeEXT& DeviceAddressRange, bool bImmediateUpdate = true)`
- L66 _public prototype_ `void BindDescriptorBuffers(VkCommandBuffer CommandBuffer, VkPipelineStageFlags SupportedStages);` — Descriptor Buffer functions
- L67 _public prototype_ `void UpdateDescriptor(FRHIDescriptorHandle DescriptorHandle, VkSampler VulkanSampler);`
- L68 _public prototype_ `void UpdateDescriptor(const FVulkanContextArray& Contexts, FRHIDescriptorHandle DescriptorHandle, VkImageView VulkanImage, bool bIsDepthStencil, bool bImmediateUpdate = true);`
- L69 _public prototype_ `void UpdateDescriptor(const FVulkanContextArray& Contexts, FRHIDescriptorHandle DescriptorHandle, VkBuffer VulkanBuffer, VkDeviceSize BufferOffset, VkDeviceSize BufferSize, bool bImmediateUpdate = true);`
- L70 _public prototype_ `void UpdateDescriptor(const FVulkanContextArray& Contexts, FRHIDescriptorHandle DescriptorHandle, VkDeviceAddress BufferAddress, VkDeviceSize BufferSize, bool bImmediateUpdate = true);`
- L71 _public prototype_ `void UpdateDescriptor(const FVulkanContextArray& Contexts, FRHIDescriptorHandle DescriptorHandle, const VkBufferViewCreateInfo& ViewInfo, bool bImmediateUpdate = true);`
- L72 _public prototype_ `void UpdateDescriptor(const FVulkanContextArray& Contexts, FRHIDescriptorHandle DescriptorHandle, VkAccelerationStructureKHR AccelerationStructure, bool bImmediateUpdate = true);`
- L73 _public prototype_ `void RegisterUniformBuffers(FVulkanCommandListContext& Context, VkShaderStageFlags StageFlags, TConstArrayView<VkWriteDescriptorSet> UBDescriptors);`
- L75 _public prototype_ `TConstArrayView<VkDescriptorSetAndBindingMappingEXT> GetBindingMappings(EShaderFrequency Frequency, bool bHasGlobals) const;`
- L77 _public function_ `ERHIBindlessConfiguration GetConfiguration() const`
- L82 _public function_ `bool IsSupported() const`
- L87 _public function_ `VkPipelineCreateFlagBits2 GetPipelineCreateFlag() const`
- L93 _public function_ `VkPipelineLayout GetPipelineLayout() const`
- L99 _public function_ `TConstArrayView<VkDescriptorSetLayout> GetDescriptorSetLayouts() const` — Returns descriptor set layouts for a single stage
- L104 _public function_ `TConstArrayView<VkPushConstantRange> GetPushConstantRanges() const`
- L109 _public function_ `bool UseDescriptorHeaps() const`
- L114 _public function_ `bool UseDescriptorBuffers() const`
- L119 _public function_ `const VkBindHeapInfoEXT& GetSamplerBindHeapInfo() const`
- L124 _public function_ `const VkBindHeapInfoEXT& GetResourceBindHeapInfo() const`
- L129 _public prototype_ `bool SupportsBindlessAccelerationStructures() const;`
- L132 _private member_ `FVulkanDevice& Device;`
- L134 _private member_ `ERHIBindlessConfiguration Configuration{};`
- L135 _private member_ `ERHIPipeline ConfiguredPipelines = ERHIPipeline::None;`
- L137 _private member_ `EBindlessType BindlessType = EBindlessType::Disabled;`
- L170 _private member_ `BindlessSetState SamplerState;`
- L171 _private member_ `BindlessSetState ResourceState;`
- L173 _private prototype_ `BindlessSetState& GetBindlessState(ERHIDescriptorType RHIDescriptorType);`
- L176 _private member_ `VkBindHeapInfoEXT SamplerBindHeapInfo;` — Descriptor Heap specific values
- L177 _private member_ `VkBindHeapInfoEXT ResourceBindHeapInfo;`
- L181 _private member_ `TArray<VkDescriptorSetAndBindingMappingEXT> HeapOnlyBindingMappings;` — Only provides binding mappings for the Sampler and Resource Heaps NOTE: Won't be necessary when our DXC supports SamplerHeapEXT / ResourceHeapEXT builtins
- L183 _private member_ `TArray<VkDescriptorSetAndBindingMappingEXT> GraphicsBindingMappings[SF_NumGraphicsFrequencies];` — Binding mappins where only bindless handles are used (no temporary allocation for globals)
- L184 _private member_ `TArray<VkDescriptorSetAndBindingMappingEXT> ComputeBindingMappings;`
- L186 _private member_ `TArray<VkDescriptorSetAndBindingMappingEXT> GraphicsBindingMappingsWithPushAddr[SF_NumGraphicsFrequencies];` — Bindings with a push address in Binding0 for the temporary allocation used for globals
- L187 _private member_ `TArray<VkDescriptorSetAndBindingMappingEXT> ComputeBindingMappingsWithPushAddr;`
- L190 _private prototype_ `void InitDescriptorHeaps();` — Descriptor Heap functions
- L191 _private prototype_ `void UpdateDescriptorInternal(const FVulkanContextArray& Contexts, FRHIDescriptorHandle DescriptorHandle, const VkResourceDescriptorDataEXT& DescriptorData, bool bImmediateUpdate);`
- L194 _private member_ `VkDescriptorSetLayout SingleUseUBDescriptorSetLayout = VK_NULL_HANDLE;` — Descriptor Buffer specific values
- L195 _private member_ `VkDescriptorBufferBindingInfoEXT BufferBindingInfo[VulkanBindless::NumBindlessSets];`
- L196 _private member_ `uint32_t BufferIndices[VulkanBindless::MaxNumSets];`
- L197 _private member_ `VkPipelineLayout BindlessPipelineLayout = VK_NULL_HANDLE;`
- L198 _private member_ `TStaticArray<VkDescriptorSetLayout, VulkanBindless::MaxNumSets> BindlessDescriptorSetLayouts;`
- L199 _private member_ `static const VkPushConstantRange PushConstantRanges[(uint8)EPushConstantRangeType::Count];`
- L202 _private prototype_ `void InitDescriptorBuffers();` — Descriptor Buffer functions
- L203 _private prototype_ `void UpdateDescriptorInternal(const FVulkanContextArray& Contexts, FRHIDescriptorHandle DescriptorHandle, VkDescriptorDataEXT DescriptorData, bool bImmediateUpdate);`

#### enum `FVulkanBindlessDescriptorManager::EBindlessType`  
`enum class EBindlessType : uint8`  
_L19-24_
- L21 _public enumerator_ `DescriptorHeap`
- L22 _public enumerator_ `DescriptorBuffer`
- L23 _public enumerator_ `Disabled`

#### enum `FVulkanBindlessDescriptorManager::EPushConstantRangeType`  
`enum class EPushConstantRangeType : uint8`  
_L26-31_
- L28 _public enumerator_ `StaticUniformBuffers`
- L30 _public enumerator_ `Count`

#### struct `FVulkanBindlessDescriptorManager::BindlessSetState`  
`struct BindlessSetState`  
_L139-169_
- L141 _public function_ `~BindlessSetState()`
- L156 _public member_ `FRHIHeapDescriptorAllocator* Allocator = nullptr;`
- L158 _public member_ `uint32 DescriptorSize = 0;`
- L160 _public member_ `VkBuffer BufferHandle = VK_NULL_HANDLE;`
- L161 _public member_ `VkDeviceMemory MemoryHandle = VK_NULL_HANDLE;`
- L162 _public member_ `uint8* MappedPointer = nullptr;`
- L165 _public member_ `TArray<VkDescriptorType, TInlineAllocator<2>> DescriptorTypes;` — Descriptor Buffer specific
- L166 _public member_ `VkDescriptorSetLayout DescriptorSetLayout = VK_NULL_HANDLE;`
- L167 _public member_ `uint32 DescriptorCapacity = 0;`
- L168 _public member_ `uint8* CPUDescriptorMemory = nullptr;`

### `Source/Runtime/VulkanRHI/Private/VulkanChunkedPipelineCache.h` (Private)


#### class `FVulkanChunkedPipelineCacheManager`  
`class FVulkanChunkedPipelineCacheManager`  
_L15-52_
- L17 _private member_ `TUniquePtr<class FVulkanChunkedPipelineCacheManagerImpl> VulkanPipelineCacheManagerImpl;`
- L20 _public prototype_ `static void Init();`
- L21 _public prototype_ `static void Shutdown();`
- L22 _public prototype_ `static bool IsEnabled();`
- L23 _public prototype_ `static FVulkanChunkedPipelineCacheManager& Get();`
- L46 _public typedef_ `template<class TPipelineState> using FPSOCreateCallbackFunc = TUniqueFunction<VkResult(FPSOCreateFuncParams<TPipelineState>& Params)>;`
- L49 _public prototype_ `template<class TPipelineState> VkResult CreatePSO(TPipelineState* GraphicsPipelineState, bool bIsPrecompileJob, FPSOCreateCallbackFunc<TPipelineState> PSOCreateFunc);`
- L51 _public prototype_ `void Tick();`

#### enum `FVulkanChunkedPipelineCacheManager::EPSOOperation`  
`enum class EPSOOperation`  
_L25-29_
- L27 _public enumerator_ `CreateIfPresent` — checks the PSO is already present in the cache, VK api requires it creates the PSO too.
- L28 _public enumerator_ `CreateAndStorePSO` — Create and store the PSO in the cache.

#### struct `FVulkanChunkedPipelineCacheManager::FPSOCreateFuncParams`  
`template<class TPipelineState> struct FPSOCreateFuncParams`  
_L33-43_
- L35 _public function_ `FPSOCreateFuncParams(TPipelineState* PSOIn, VkPipelineCache DestPipelineCacheIn, FVulkanChunkedPipelineCacheManager::EPSOOperation PSOOperationIn, FRWLock& DestPipelineCacheLockIn) : PSO(PSOIn), DestPipelineCache(DestPipelineCacheIn), PSOOperation(PSOOperationIn), DestPipelineCacheLock(DestPipelineCacheLockIn)`
- L39 _public member_ `TPipelineState* PSO;`
- L40 _public member_ `VkPipelineCache DestPipelineCache;`
- L41 _public member_ `FVulkanChunkedPipelineCacheManager::EPSOOperation PSOOperation;`
- L42 _public member_ `FRWLock& DestPipelineCacheLock;` — ensure lock is acquired before use of DestPipelineCache.

### `Source/Runtime/VulkanRHI/Private/VulkanCommandBuffer.h` (Private)


#### enum `EVulkanCommandBufferType`  
`enum class EVulkanCommandBufferType : uint8`  
_L28-41_
- L30 _public enumerator_ `Primary`
- L34 _public enumerator_ `Secondary` — Secondary command buffer with an inherited render pass that will get executed from a primary cmd buffer Used for parallel contexts without dynamic rendering
- L38 _public enumerator_ `Parallel` — Primary command buffer that suspend/resume the current renderpass Used for parallel contexts with dynamic rendering
- L40 _public enumerator_ `Count`

#### class `FVulkanCommandBuffer`  
`class FVulkanCommandBuffer`  
_L43-204_
- L49 _protected prototype_ `FVulkanCommandBuffer(FVulkanDevice& InDevice, FVulkanCommandBufferPool& InCommandBufferPool);`
- L50 _protected prototype_ `~FVulkanCommandBuffer();`
- L53 _public function_ `bool IsInsideRenderPass() const`
- L58 _public function_ `bool IsOutsideRenderPass() const`
- L63 _public function_ `bool HasBegun() const`
- L68 _public function_ `bool HasEnded() const`
- L73 _public function_ `bool IsSubmitted() const`
- L78 _public function_ `bool IsAllocated() const`
- L83 _public function_ `VkCommandBuffer GetHandle() const`
- L88 _public prototype_ `EVulkanCommandBufferType GetCommandBufferType() const;`
- L90 _public prototype_ `void SetSubmitted();`
- L92 _public prototype_ `void Begin(FVulkanQueryPool* OptionalQueryPool, VkRenderPass RenderPassHandle);`
- L93 _public prototype_ `void End(FVulkanQueryPool* OptionalQueryPool);`
- L106 _public member_ `TArray<VkViewport, TInlineAllocator<2>> CurrentViewports;`
- L107 _public member_ `TArray<VkRect2D, TInlineAllocator<2>> CurrentScissors;`
- L108 _public member_ `uint32 CurrentStencilRef = 0;`
- L109 _public member_ `EState State = EState::NotAllocated;`
- L111 _public member_ `FGfxPipelineDesc* LastDynamicStateUpdate = nullptr;`
- L113 _public member_ `uint8 bNeedsFullDynamicStateUpdate : 1 = 1;`
- L114 _public member_ `uint8 bHasPipeline : 1 = 0;`
- L115 _public member_ `uint8 bHasViewport : 1 = 0;`
- L116 _public member_ `uint8 bHasScissor : 1 = 0;`
- L117 _public member_ `uint8 bHasStencilRef : 1 = 0;`
- L118 _public member_ `uint8 bHasBoundDescriptorHeap : 1 = 0;`
- L120 _public member_ `uint8 CurrentMultiViewCount = 0;`
- L123 _public member_ `TArray<FVulkanCommandBuffer*> ExecutedSecondaryCommandBuffers;` — Every secondary command buffer executed from this one with tied lifetimes
- L126 _public prototype_ `void BeginRenderPass(const FVulkanBeginRenderPassInfo& BeginRenderPassInfo, const VkClearValue* AttachmentClearValues);` — You never want to call Begin/EndRenderPass directly as it will mess up the layout manager.
- L127 _public prototype_ `void EndRenderPass();`
- L130 _public prototype_ `void BeginDynamicRendering(const VkRenderingInfo& RenderingInfo, FVulkanQueryPool* OptionalQueryPool);`
- L131 _public prototype_ `void EndDynamicRendering(FVulkanQueryPool* OptionalQueryPool);`
- L134 _public member_ `VkRenderingFlags LastDynamicRenderingFlags = 0;` — Flags used with the last dynamic rendering pass
- L137 _public prototype_ `void BeginSplitBarrier(VkEvent BarrierEvent, const VkDependencyInfo& DependencyInfo);` — Split barriers
- L138 _public prototype_ `void EndSplitBarrier(VkEvent BarrierEvent, const VkDependencyInfo& DependencyInfo);`
- L141 _public function_ `template <typename TEventType, typename... TArgs> TEventType& EmplaceProfilerEvent(TArgs&&... Args)`
- L154 _public function_ `void FlushProfilerEvents(UE::RHI::GPUProfiler::FEventStream& Destination, uint64 CPUTimestamp)`
- L167 _public member_ `FVulkanDevice& Device;` — Public immutable reference to be accessed directly
- L169 _public prototype_ `void SetUnusedGraphicsDynamicStates();`
- L171 _public prototype_ `void BindPipeline(VkPipelineBindPoint BindPoint, VkPipeline PipelineHandle, bool bBindless);`
- L172 _public prototype_ `void BindGraphicsShaderObjects(TArrayView<FVulkanShader*> VulkanShaders);`
- L173 _public prototype_ `void BindComputeShaderObject(FVulkanShader* VulkanShader);`
- L175 _public prototype_ `void SetStaticUniformBufferPushConstants(TConstArrayView<uint32> StaticUniformBuffers);`
- L176 _public prototype_ `void SetBindingPushConstants(EShaderFrequency Frequency, uint64 GlobalsAddressOrFirstBinding, TConstArrayView<uint32> Bindings);`
- L179 _private member_ `VkCommandBuffer CommandBufferHandle = VK_NULL_HANDLE;`
- L180 _private member_ `double SubmittedTime = 0.0f;`
- L182 _private prototype_ `void Reset();`
- L184 _private member_ `FVulkanCommandBufferPool& CommandBufferPool;`
- L186 _private member_ `VkPipeline CurrentPipelineHandle = VK_NULL_HANDLE;`
- L187 _private member_ `VkShaderEXT CurrentComputeShaderObject = VK_NULL_HANDLE;`
- L188 _private member_ `VkShaderEXT CurrentGraphicsShaderObjects[ShaderStage::NumGraphicsStages] = { VK_NULL_HANDLE };`
- L189 _private member_ `TArray<uint32> CurrentPushConstants;`
- L191 _private prototype_ `void ResetCurrentState();`
- L192 _private prototype_ `void ResetBoundShaderObject();`
- L194 _private member_ `TArray<VkEvent> EndedBarrierEvents;`
- L196 _private prototype_ `void AllocMemory();`
- L197 _private prototype_ `void FreeMemory();`
- L199 _private member_ `UE::RHI::GPUProfiler::FEventStream EventStream;`
- L200 _private member_ `TArray<UE::RHI::GPUProfiler::FEvent::FBeginWork*, TInlineAllocator<8>> BeginEvents;`
- L253 _function_ `inline EVulkanCommandBufferType FVulkanCommandBuffer::GetCommandBufferType() const`

#### enum `FVulkanCommandBuffer::EState`  
`enum class EState : uint8`  
_L95-104_
- L97 _public enumerator_ `ReadyForBegin`
- L98 _public enumerator_ `IsInsideBegin`
- L99 _public enumerator_ `IsInsideRenderPass`
- L100 _public enumerator_ `HasEnded`
- L101 _public enumerator_ `Submitted`
- L102 _public enumerator_ `NotAllocated`
- L103 _public enumerator_ `NeedReset`

#### class `FVulkanCommandBufferPool`  
`class FVulkanCommandBufferPool`  
_L206-250_
- L209 _public prototype_ `FVulkanCommandBufferPool(FVulkanDevice& InDevice, FVulkanQueue& InQueue, EVulkanCommandBufferType InCommandBufferType);`
- L210 _public prototype_ `~FVulkanCommandBufferPool();`
- L212 _public function_ `VkCommandPool GetHandle() const`
- L217 _public function_ `FCriticalSection* GetCS()`
- L222 _public function_ `FVulkanQueue& GetQueue()`
- L227 _public function_ `EVulkanCommandBufferType GetCommandBufferType() const`
- L232 _public prototype_ `void FreeUnusedCmdBuffers(FVulkanQueue* Queue, bool bTrimMemory);`
- L235 _private member_ `FVulkanDevice& Device;`
- L236 _private member_ `FVulkanQueue& Queue;`
- L238 _private member_ `const EVulkanCommandBufferType CommandBufferType;`
- L240 _private member_ `VkCommandPool Handle = VK_NULL_HANDLE;`
- L242 _private member_ `TArray<FVulkanCommandBuffer*> CmdBuffers;`
- L243 _private member_ `TArray<FVulkanCommandBuffer*> FreeCmdBuffers;`
- L245 _private member_ `FCriticalSection CS;`
- L247 _private prototype_ `FVulkanCommandBuffer* Create();`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace VulkanRHI`

### `Source/Runtime/VulkanRHI/Private/VulkanCommandWrappers.h` (Private)


#### struct `FWrapLayer`  
`struct FWrapLayer`  
_L44-334_
- L48 _public prototype_ `static void CreateInstance(VkResult Result, const VkInstanceCreateInfo* CreateInfo, VkInstance* Instance) VULKAN_LAYER_BODY static void DestroyInstance(VkResult Result, VkInstance Instance) VULKAN_LAYER_BODY static void EnumeratePhysicalDevices(VkResult Result, VkInstance Instance, uint32* PhysicalDeviceCount, VkPhysicalDevice* PhysicalDevices) VULKAN_LAYER_BODY static void EnumerateInstanceVersion(VkResult Result, uint32_t* ApiVersion) VULKAN_LAYER_BODY static void GetPhysicalDeviceFeatures(VkResult Result, VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceFeatures* Features) VULKAN_LAYER_BODY static void GetPhysicalDeviceFormatProperties(VkResult Result, VkPhysicalDevice PhysicalDevice, VkFormat Format, VkFormatProperties* FormatProperties) VULKAN_LAYER_BODY static void GetPhysicalDeviceFormatProperties2(VkResult Result, VkPhysicalDevice PhysicalDevice, VkFormat Format, VkFormatProperties2* FormatProperties) VULKAN_LAYER_BODY static void GetPhysicalDeviceImageFormatProperties(VkResult Result, VkPhysicalDevice PhysicalDevice, VkFormat Format, VkImageType Type, VkImageTiling Tiling, VkImageUsageFlags Usage, VkImageCreateFlags Flags, VkImageFormatProperties* pImageFormatProperties) VULKAN_LAYER_BODY static void GetPhysicalDeviceImageFormatProperties2(VkResult Result, VkPhysicalDevice PhysicalDevice, const VkPhysicalDeviceImageFormatInfo2* FormatInfo, VkImageFormatProperties2* FormatProperties) VULKAN_LAYER_BODY static void GetPhysicalDeviceProperties(VkResult Result, VkPhysical ...`

#### Free symbols / members of external scopes

- L16 _macro_ `#define VK_DYNAMICAPI_TO_VULKANRHI(Type,Func) using VulkanDynamicAPI::Func;` — Bring functions from VulkanDynamicAPI to VulkanRHI
- L18 _namespace_ `namespace VulkanRHI`
- L20 _prototype_ `ENUM_VK_ENTRYPOINTS_ALL(VK_DYNAMICAPI_TO_VULKANRHI);` (scope `VulkanRHI`)
- L30 _macro_ `#define VULKANAPINAMESPACE VulkanDynamicAPI` — Vulkan API is defined in VulkanDynamicAPI namespace.
- L33 _macro_ `#define VULKANAPINAMESPACE` — Vulkan API is in the global namespace.
- L37 _macro_ `#define VULKAN_LAYER_BODY ;`
- L38 _macro_ `#define VULKAN_EXTERN_EXPORT VULKANRHI_API`
- L40 _macro_ `#define VULKAN_LAYER_BODY {}`
- L41 _macro_ `#define VULKAN_EXTERN_EXPORT`
- L339 _namespace_ `namespace VulkanRHI`
- L341 _prototype_ `void FlushDebugWrapperLog();` (scope `VulkanRHI`)
- L343 _function_ `FORCEINLINE_DEBUGGABLE VkResult vkCreateInstance(const VkInstanceCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkInstance* Instance)` (scope `VulkanRHI`)
- L351 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyInstance(VkInstance Instance, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L358 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkEnumeratePhysicalDevices(VkInstance Instance, uint32* PhysicalDeviceCount, VkPhysicalDevice* PhysicalDevices)` (scope `VulkanRHI`)
- L366 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkEnumerateInstanceVersion(uint32_t* ApiVersion)` (scope `VulkanRHI`)
- L374 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetPhysicalDeviceFeatures(VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceFeatures* Features)` (scope `VulkanRHI`)
- L381 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format, VkFormatProperties* FormatProperties)` (scope `VulkanRHI`)
- L388 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetPhysicalDeviceFormatProperties2(VkPhysicalDevice PhysicalDevice, VkFormat Format, VkFormatProperties2* FormatProperties)` (scope `VulkanRHI`)
- L395 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetPhysicalDeviceImageFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format, VkImageType Type, VkImageTiling Tiling, VkImageUsageFlags Usage, VkImageCreateFlags Flags, VkImageFormatProperties* pImageFormatProperties)` (scope `VulkanRHI`)
- L403 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice PhysicalDevice, const VkPhysicalDeviceImageFormatInfo2* FormatInfo, VkImageFormatProperties2* FormatProperties)` (scope `VulkanRHI`)
- L411 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetPhysicalDeviceProperties(VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceProperties* Properties)` (scope `VulkanRHI`)
- L418 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetPhysicalDeviceMemoryProperties2(VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties)` (scope `VulkanRHI`)
- L425 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetPhysicalDeviceProperties2(VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceProperties2* Properties)` (scope `VulkanRHI`)
- L432 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetPhysicalDeviceFeatures2(VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceFeatures2* Features)` (scope `VulkanRHI`)
- L439 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetPhysicalDeviceFragmentShadingRatesKHR(VkPhysicalDevice PhysicalDevice, uint32* FragmentShadingRateCount, VkPhysicalDeviceFragmentShadingRateKHR* FragmentShadingRates)` (scope `VulkanRHI`)
- L446 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice PhysicalDevice, uint32* QueueFamilyPropertyCount, VkQueueFamilyProperties* QueueFamilyProperties)` (scope `VulkanRHI`)
- L453 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice PhysicalDevice, uint32* QueueFamilyPropertyCount, VkQueueFamilyProperties2* QueueFamilyProperties)` (scope `VulkanRHI`)
- L460 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceMemoryProperties* MemoryProperties)` (scope `VulkanRHI`)
- L467 _function_ `static FORCEINLINE_DEBUGGABLE PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance Instance, const char* Name)` (scope `VulkanRHI`)
- L475 _function_ `static FORCEINLINE_DEBUGGABLE PFN_vkVoidFunction vkGetDeviceProcAddr(VkDevice Device, const char* Name)` (scope `VulkanRHI`)
- L483 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateDevice(VkPhysicalDevice PhysicalDevice, const VkDeviceCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkDevice* Device)` (scope `VulkanRHI`)
- L491 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyDevice(VkDevice Device, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L498 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkEnumerateInstanceExtensionProperties(const char* LayerName, uint32* PropertyCount, VkExtensionProperties* Properties)` (scope `VulkanRHI`)
- L506 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkEnumerateDeviceExtensionProperties(VkPhysicalDevice PhysicalDevice, const char* LayerName, uint32* PropertyCount, VkExtensionProperties* Properties)` (scope `VulkanRHI`)
- L514 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkEnumerateInstanceLayerProperties(uint32* PropertyCount, VkLayerProperties* Properties)` (scope `VulkanRHI`)
- L522 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkEnumerateDeviceLayerProperties(VkPhysicalDevice PhysicalDevice, uint32* PropertyCount, VkLayerProperties* Properties)` (scope `VulkanRHI`)
- L530 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetDeviceQueue(VkDevice Device, uint32 QueueFamilyIndex, uint32 QueueIndex, VkQueue* Queue)` (scope `VulkanRHI`)
- L537 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkQueueSubmit(VkQueue Queue, uint32 SubmitCount, const VkSubmitInfo* Submits, VkFence Fence)` (scope `VulkanRHI`)
- L544 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkQueueWaitIdle(VkQueue Queue)` (scope `VulkanRHI`)
- L552 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkDeviceWaitIdle(VkDevice Device)` (scope `VulkanRHI`)
- L560 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkAllocateMemory(VkDevice Device, const VkMemoryAllocateInfo* AllocateInfo, const VkAllocationCallbacks* Allocator, VkDeviceMemory* Memory)` (scope `VulkanRHI`)
- L568 _function_ `static FORCEINLINE_DEBUGGABLE void vkFreeMemory(VkDevice Device, VkDeviceMemory Memory, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L575 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkMapMemory(VkDevice Device, VkDeviceMemory Memory, VkDeviceSize Offset, VkDeviceSize Size, VkMemoryMapFlags Flags, void** Data)` (scope `VulkanRHI`)
- L583 _function_ `static FORCEINLINE_DEBUGGABLE void vkUnmapMemory(VkDevice Device, VkDeviceMemory Memory)` (scope `VulkanRHI`)
- L590 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkFlushMappedMemoryRanges(VkDevice Device, uint32 MemoryRangeCount, const VkMappedMemoryRange* MemoryRanges)` (scope `VulkanRHI`)
- L598 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkInvalidateMappedMemoryRanges(VkDevice Device, uint32 MemoryRangeCount, const VkMappedMemoryRange* MemoryRanges)` (scope `VulkanRHI`)
- L606 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetDeviceMemoryCommitment(VkDevice Device, VkDeviceMemory Memory, VkDeviceSize* pCommittedMemoryInBytes)` (scope `VulkanRHI`)
- L613 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkBindBufferMemory(VkDevice Device, VkBuffer Buffer, VkDeviceMemory Memory, VkDeviceSize MemoryOffset)` (scope `VulkanRHI`)
- L621 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkBindImageMemory(VkDevice Device, VkImage Image, VkDeviceMemory Memory, VkDeviceSize MemoryOffset)` (scope `VulkanRHI`)
- L629 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetBufferMemoryRequirements(VkDevice Device, VkBuffer Buffer, VkMemoryRequirements* MemoryRequirements)` (scope `VulkanRHI`)
- L636 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetImageMemoryRequirements(VkDevice Device, VkImage Image, VkMemoryRequirements* MemoryRequirements)` (scope `VulkanRHI`)
- L643 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetImageSparseMemoryRequirements(VkDevice Device, VkImage Image, uint32* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements)` (scope `VulkanRHI`)
- L650 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format, VkImageType Type, VkSampleCountFlagBits Samples, VkImageUsageFlags Usage, VkImageTiling Tiling, uint32* pPropertyCount, VkSparseImageFormatProperties* pProperties)` (scope `VulkanRHI`)
- L657 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkQueueBindSparse(VkQueue Queue, uint32 BindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence Fence)` (scope `VulkanRHI`)
- L665 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateFence(VkDevice Device, const VkFenceCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkFence* Fence)` (scope `VulkanRHI`)
- L673 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyFence(VkDevice Device, VkFence Fence, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L680 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkResetFences(VkDevice Device, uint32 FenceCount, const VkFence* Fences)` (scope `VulkanRHI`)
- L688 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetFenceStatus(VkDevice Device, VkFence Fence)` (scope `VulkanRHI`)
- L696 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkWaitForFences(VkDevice Device, uint32 FenceCount, const VkFence* Fences, VkBool32 bWaitAll, uint64_t Timeout)` (scope `VulkanRHI`)
- L704 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateSemaphore(VkDevice Device, const VkSemaphoreCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkSemaphore* Semaphore)` (scope `VulkanRHI`)
- L713 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroySemaphore(VkDevice Device, VkSemaphore Semaphore, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L720 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateEvent(VkDevice Device, const VkEventCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkEvent* Event)` (scope `VulkanRHI`)
- L728 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyEvent(VkDevice Device, VkEvent Event, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L735 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetEventStatus(VkDevice Device, VkEvent Event)` (scope `VulkanRHI`)
- L743 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkSetEvent(VkDevice Device, VkEvent Event)` (scope `VulkanRHI`)
- L751 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkResetEvent(VkDevice Device, VkEvent Event)` (scope `VulkanRHI`)
- L759 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateQueryPool(VkDevice Device, const VkQueryPoolCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkQueryPool* QueryPool)` (scope `VulkanRHI`)
- L767 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyQueryPool(VkDevice Device, VkQueryPool QueryPool, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L774 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetQueryPoolResults(VkDevice Device, VkQueryPool QueryPool, uint32 FirstQuery, uint32 QueryCount, size_t DataSize, void* Data, VkDeviceSize Stride, VkQueryResultFlags Flags)` (scope `VulkanRHI`)
- L783 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateBuffer(VkDevice Device, const VkBufferCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkBuffer* Buffer)` (scope `VulkanRHI`)
- L791 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyBuffer(VkDevice Device, VkBuffer Buffer, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L798 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateBufferView(VkDevice Device, const VkBufferViewCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkBufferView* View)` (scope `VulkanRHI`)
- L806 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyBufferView(VkDevice Device, VkBufferView BufferView, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L813 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateImage(VkDevice Device, const VkImageCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkImage* Image)` (scope `VulkanRHI`)
- L821 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyImage(VkDevice Device, VkImage Image, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L828 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetImageSubresourceLayout(VkDevice Device, VkImage Image, const VkImageSubresource* Subresource, VkSubresourceLayout* Layout)` (scope `VulkanRHI`)
- L835 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetImageSubresourceLayout2KHR(VkDevice Device, VkImage Image, const VkImageSubresource2KHR* Subresource, VkSubresourceLayout2KHR* Layout)` (scope `VulkanRHI`)
- L842 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateImageView(VkDevice Device, const VkImageViewCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkImageView* View)` (scope `VulkanRHI`)
- L850 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyImageView(VkDevice Device, VkImageView ImageView, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L857 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateShaderModule(VkDevice Device, const VkShaderModuleCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkShaderModule* ShaderModule)` (scope `VulkanRHI`)
- L865 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyShaderModule(VkDevice Device, VkShaderModule ShaderModule, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L872 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreatePipelineCache(VkDevice Device, const VkPipelineCacheCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkPipelineCache* PipelineCache)` (scope `VulkanRHI`)
- L880 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyPipelineCache(VkDevice Device, VkPipelineCache PipelineCache, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L887 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetPipelineCacheData(VkDevice Device, VkPipelineCache PipelineCache, size_t* DataSize, void* Data)` (scope `VulkanRHI`)
- L895 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkMergePipelineCaches(VkDevice Device, VkPipelineCache DestCache, uint32 SourceCacheCount, const VkPipelineCache* SrcCaches)` (scope `VulkanRHI`)
- L903 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateGraphicsPipelines(VkDevice Device, VkPipelineCache PipelineCache, uint32 CreateInfoCount, const VkGraphicsPipelineCreateInfo* CreateInfos, const VkAllocationCallbacks* Allocator, VkPipeline* Pipelines)` (scope `VulkanRHI`)
- L911 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateComputePipelines(VkDevice Device, VkPipelineCache PipelineCache, uint32 CreateInfoCount, const VkComputePipelineCreateInfo* CreateInfos, const VkAllocationCallbacks* Allocator, VkPipeline* Pipelines)` (scope `VulkanRHI`)
- L919 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyPipeline(VkDevice Device, VkPipeline Pipeline, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L926 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreatePipelineLayout(VkDevice Device, const VkPipelineLayoutCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkPipelineLayout* PipelineLayout)` (scope `VulkanRHI`)
- L934 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyPipelineLayout(VkDevice Device, VkPipelineLayout PipelineLayout, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L941 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateSampler(VkDevice Device, const VkSamplerCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkSampler* Sampler)` (scope `VulkanRHI`)
- L949 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroySampler(VkDevice Device, VkSampler Sampler, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L956 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateDescriptorSetLayout(VkDevice Device, const VkDescriptorSetLayoutCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkDescriptorSetLayout* SetLayout)` (scope `VulkanRHI`)
- L964 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyDescriptorSetLayout(VkDevice Device, VkDescriptorSetLayout DescriptorSetLayout, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L971 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateDescriptorPool(VkDevice Device, const VkDescriptorPoolCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkDescriptorPool* DescriptorPool)` (scope `VulkanRHI`)
- L979 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyDescriptorPool(VkDevice Device, VkDescriptorPool DescriptorPool, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L986 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkResetDescriptorPool(VkDevice Device, VkDescriptorPool DescriptorPool, VkDescriptorPoolResetFlags Flags)` (scope `VulkanRHI`)
- L994 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkAllocateDescriptorSets(VkDevice Device, const VkDescriptorSetAllocateInfo* AllocateInfo, VkDescriptorSet* DescriptorSets)` (scope `VulkanRHI`)
- L1002 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkFreeDescriptorSets(VkDevice Device, VkDescriptorPool DescriptorPool, uint32 DescriptorSetCount, const VkDescriptorSet* DescriptorSets)` (scope `VulkanRHI`)
- L1010 _function_ `static FORCEINLINE_DEBUGGABLE void vkUpdateDescriptorSets(VkDevice Device, uint32 DescriptorWriteCount, const VkWriteDescriptorSet* DescriptorWrites, uint32 DescriptorCopyCount, const VkCopyDescriptorSet* DescriptorCopies)` (scope `VulkanRHI`)
- L1017 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateFramebuffer(VkDevice Device, const VkFramebufferCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkFramebuffer* Framebuffer)` (scope `VulkanRHI`)
- L1025 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyFramebuffer(VkDevice Device, VkFramebuffer Framebuffer, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L1032 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateRenderPass(VkDevice Device, const VkRenderPassCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkRenderPass* RenderPass)` (scope `VulkanRHI`)
- L1040 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateRenderPass2KHR(VkDevice Device, const VkRenderPassCreateInfo2* CreateInfo, const VkAllocationCallbacks* Allocator, VkRenderPass* RenderPass)` (scope `VulkanRHI`)
- L1048 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyRenderPass(VkDevice Device, VkRenderPass RenderPass, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L1055 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetRenderAreaGranularity(VkDevice Device, VkRenderPass RenderPass, VkExtent2D* pGranularity)` (scope `VulkanRHI`)
- L1062 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateCommandPool(VkDevice Device, const VkCommandPoolCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkCommandPool* CommandPool)` (scope `VulkanRHI`)
- L1070 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyCommandPool(VkDevice Device, VkCommandPool CommandPool, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L1077 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkResetCommandPool(VkDevice Device, VkCommandPool CommandPool, VkCommandPoolResetFlags Flags)` (scope `VulkanRHI`)
- L1085 _function_ `static FORCEINLINE_DEBUGGABLE void vkTrimCommandPool(VkDevice Device, VkCommandPool CommandPool, VkCommandPoolTrimFlags Flags)` (scope `VulkanRHI`)
- L1092 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkAllocateCommandBuffers(VkDevice Device, const VkCommandBufferAllocateInfo* AllocateInfo, VkCommandBuffer* CommandBuffers)` (scope `VulkanRHI`)
- L1100 _function_ `static FORCEINLINE_DEBUGGABLE void vkFreeCommandBuffers(VkDevice Device, VkCommandPool CommandPool, uint32 CommandBufferCount, const VkCommandBuffer* CommandBuffers)` (scope `VulkanRHI`)
- L1107 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkBeginCommandBuffer(VkCommandBuffer CommandBuffer, const VkCommandBufferBeginInfo* BeginInfo)` (scope `VulkanRHI`)
- L1115 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkEndCommandBuffer(VkCommandBuffer CommandBuffer)` (scope `VulkanRHI`)
- L1123 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkResetCommandBuffer(VkCommandBuffer CommandBuffer, VkCommandBufferResetFlags Flags)` (scope `VulkanRHI`)
- L1131 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBindPipeline(VkCommandBuffer CommandBuffer, VkPipelineBindPoint PipelineBindPoint, VkPipeline Pipeline)` (scope `VulkanRHI`)
- L1138 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetViewport(VkCommandBuffer CommandBuffer, uint32 FirstViewport, uint32 ViewportCount, const VkViewport* Viewports)` (scope `VulkanRHI`)
- L1145 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetScissor(VkCommandBuffer CommandBuffer, uint32 FirstScissor, uint32 ScissorCount, const VkRect2D* Scissors)` (scope `VulkanRHI`)
- L1152 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetLineWidth(VkCommandBuffer CommandBuffer, float LineWidth)` (scope `VulkanRHI`)
- L1159 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetDepthBias(VkCommandBuffer CommandBuffer, float DepthBiasConstantFactor, float DepthBiasClamp, float DepthBiasSlopeFactor)` (scope `VulkanRHI`)
- L1166 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetBlendConstants(VkCommandBuffer CommandBuffer, const float BlendConstants[4])` (scope `VulkanRHI`)
- L1173 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetDepthBounds(VkCommandBuffer CommandBuffer, float MinDepthBounds, float MaxDepthBounds)` (scope `VulkanRHI`)
- L1180 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetStencilCompareMask(VkCommandBuffer CommandBuffer, VkStencilFaceFlags FaceMask, uint32 CompareMask)` (scope `VulkanRHI`)
- L1187 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetStencilWriteMask(VkCommandBuffer CommandBuffer, VkStencilFaceFlags FaceMask, uint32 WriteMask)` (scope `VulkanRHI`)
- L1194 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetStencilReference(VkCommandBuffer CommandBuffer, VkStencilFaceFlags FaceMask, uint32 Reference)` (scope `VulkanRHI`)
- L1201 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBindDescriptorSets(VkCommandBuffer CommandBuffer, VkPipelineBindPoint PipelineBindPoint, VkPipelineLayout Layout, uint32 FirstSet, uint32 DescriptorSetCount, const VkDescriptorSet* DescriptorSets, uint32 DynamicOffsetCount, const uint32* DynamicOffsets)` (scope `VulkanRHI`)
- L1208 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBindIndexBuffer(VkCommandBuffer CommandBuffer, VkBuffer Buffer, VkDeviceSize Offset, VkIndexType IndexType)` (scope `VulkanRHI`)
- L1215 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBindVertexBuffers(VkCommandBuffer CommandBuffer, uint32 FirstBinding, uint32 BindingCount, const VkBuffer* Buffers, const VkDeviceSize* Offsets)` (scope `VulkanRHI`)
- L1222 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdDraw(VkCommandBuffer CommandBuffer, uint32 VertexCount, uint32 InstanceCount, uint32 FirstVertex, uint32 FirstInstance)` (scope `VulkanRHI`)
- L1229 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdDrawIndexed(VkCommandBuffer CommandBuffer, uint32 IndexCount, uint32 InstanceCount, uint32 FirstIndex, int32_t VertexOffset, uint32 FirstInstance)` (scope `VulkanRHI`)
- L1236 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdDrawIndirect(VkCommandBuffer CommandBuffer, VkBuffer Buffer, VkDeviceSize Offset, uint32 DrawCount, uint32 Stride)` (scope `VulkanRHI`)
- L1243 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdDrawIndexedIndirect(VkCommandBuffer CommandBuffer, VkBuffer Buffer, VkDeviceSize Offset, uint32 DrawCount, uint32 Stride)` (scope `VulkanRHI`)
- L1250 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdDispatch(VkCommandBuffer CommandBuffer, uint32 X, uint32 Y, uint32 Z)` (scope `VulkanRHI`)
- L1257 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdDispatchIndirect(VkCommandBuffer CommandBuffer, VkBuffer Buffer, VkDeviceSize Offset)` (scope `VulkanRHI`)
- L1264 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdCopyBuffer(VkCommandBuffer CommandBuffer, VkBuffer SrcBuffer, VkBuffer DstBuffer, uint32 RegionCount, const VkBufferCopy* Regions)` (scope `VulkanRHI`)
- L1271 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdCopyImage(VkCommandBuffer CommandBuffer, VkImage SrcImage, VkImageLayout SrcImageLayout, VkImage DstImage, VkImageLayout DstImageLayout, uint32 RegionCount, const VkImageCopy* Regions)` (scope `VulkanRHI`)
- L1278 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBlitImage(VkCommandBuffer CommandBuffer, VkImage SrcImage, VkImageLayout SrcImageLayout, VkImage DstImage, VkImageLayout DstImageLayout, uint32 RegionCount, const VkImageBlit* Regions, VkFilter Filter)` (scope `VulkanRHI`)
- L1285 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdCopyBufferToImage(VkCommandBuffer CommandBuffer, VkBuffer SrcBuffer, VkImage DstImage, VkImageLayout DstImageLayout, uint32 RegionCount, const VkBufferImageCopy* Regions)` (scope `VulkanRHI`)
- L1292 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdCopyImageToBuffer(VkCommandBuffer CommandBuffer, VkImage SrcImage, VkImageLayout SrcImageLayout, VkBuffer DstBuffer, uint32 RegionCount, const VkBufferImageCopy* Regions)` (scope `VulkanRHI`)
- L1299 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdUpdateBuffer(VkCommandBuffer CommandBuffer, VkBuffer DstBuffer, VkDeviceSize DstOffset, VkDeviceSize DataSize, const void* pData)` (scope `VulkanRHI`)
- L1306 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdFillBuffer(VkCommandBuffer CommandBuffer, VkBuffer DstBuffer, VkDeviceSize DstOffset, VkDeviceSize Size, uint32 Data)` (scope `VulkanRHI`)
- L1313 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdClearColorImage(VkCommandBuffer CommandBuffer, VkImage Image, VkImageLayout ImageLayout, const VkClearColorValue* Color, uint32 RangeCount, const VkImageSubresourceRange* Ranges)` (scope `VulkanRHI`)
- L1320 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdClearDepthStencilImage(VkCommandBuffer CommandBuffer, VkImage Image, VkImageLayout ImageLayout, const VkClearDepthStencilValue* DepthStencil, uint32 RangeCount, const VkImageSubresourceRange* Ranges)` (scope `VulkanRHI`)
- L1327 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdClearAttachments(VkCommandBuffer CommandBuffer, uint32 AttachmentCount, const VkClearAttachment* Attachments, uint32 RectCount, const VkClearRect* Rects)` (scope `VulkanRHI`)
- L1334 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdResolveImage( VkCommandBuffer CommandBuffer, VkImage SrcImage, VkImageLayout SrcImageLayout, VkImage DstImage, VkImageLayout DstImageLayout, uint32 RegionCount, const VkImageResolve* Regions)` (scope `VulkanRHI`)
- L1345 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetEvent(VkCommandBuffer CommandBuffer, VkEvent Event, VkPipelineStageFlags StageMask)` (scope `VulkanRHI`)
- L1352 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdResetEvent(VkCommandBuffer CommandBuffer, VkEvent Event, VkPipelineStageFlags StageMask)` (scope `VulkanRHI`)
- L1359 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdWaitEvents(VkCommandBuffer CommandBuffer, uint32 EventCount, const VkEvent* Events, VkPipelineStageFlags SrcStageMask, VkPipelineStageFlags DstStageMask, uint32 MemoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32 BufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32 ImageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)` (scope `VulkanRHI`)
- L1373 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdPipelineBarrier( VkCommandBuffer CommandBuffer, VkPipelineStageFlags SrcStageMask, VkPipelineStageFlags DstStageMask, VkDependencyFlags DependencyFlags, uint32 MemoryBarrierCount, const VkMemoryBarrier* MemoryBarriers, uint32 BufferMemoryBarrierCount, const VkBufferMemoryBarrier* BufferMemoryBarriers, uint32 ImageMemoryBarrierCount, const VkImageMemoryBarrier* ImageMemoryBarriers)` (scope `VulkanRHI`)
- L1384 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBeginQuery(VkCommandBuffer CommandBuffer, VkQueryPool QueryPool, uint32 Query, VkQueryControlFlags Flags)` (scope `VulkanRHI`)
- L1391 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdEndQuery(VkCommandBuffer CommandBuffer, VkQueryPool QueryPool, uint32 Query)` (scope `VulkanRHI`)
- L1398 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdResetQueryPool(VkCommandBuffer CommandBuffer, VkQueryPool QueryPool, uint32 FirstQuery, uint32 QueryCount)` (scope `VulkanRHI`)
- L1405 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdWriteTimestamp(VkCommandBuffer CommandBuffer, VkPipelineStageFlagBits PipelineStage, VkQueryPool QueryPool, uint32 Query)` (scope `VulkanRHI`)
- L1412 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdCopyQueryPoolResults(VkCommandBuffer CommandBuffer, VkQueryPool QueryPool, uint32 FirstQuery, uint32 QueryCount, VkBuffer DstBuffer, VkDeviceSize DstOffset, VkDeviceSize Stride, VkQueryResultFlags Flags)` (scope `VulkanRHI`)
- L1420 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdPushConstants(VkCommandBuffer CommandBuffer, VkPipelineLayout Layout, VkShaderStageFlags StageFlags, uint32 Offset, uint32 Size, const void* pValues)` (scope `VulkanRHI`)
- L1427 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdPushDescriptorSetKHR(VkCommandBuffer CommandBuffer, VkPipelineBindPoint PipelineBindPoint, VkPipelineLayout Layout, uint32_t Set, uint32_t DescriptorWriteCount, const VkWriteDescriptorSet* DescriptorWrites)` (scope `VulkanRHI`)
- L1434 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdPushDescriptorSet2KHR(VkCommandBuffer CommandBuffer, const VkPushDescriptorSetInfo* PushDescriptorSetInfo)` (scope `VulkanRHI`)
- L1441 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBeginRenderPass(VkCommandBuffer CommandBuffer, const VkRenderPassBeginInfo* RenderPassBegin, VkSubpassContents Contents)` (scope `VulkanRHI`)
- L1448 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBeginRenderPass2KHR(VkCommandBuffer CommandBuffer, const VkRenderPassBeginInfo* RenderPassBegin, const VkSubpassBeginInfo* SubpassBeginInfo)` (scope `VulkanRHI`)
- L1455 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdNextSubpass(VkCommandBuffer CommandBuffer, VkSubpassContents Contents)` (scope `VulkanRHI`)
- L1462 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdEndRenderPass(VkCommandBuffer CommandBuffer)` (scope `VulkanRHI`)
- L1469 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdEndRenderPass2KHR(VkCommandBuffer CommandBuffer, const VkSubpassEndInfo* SubpassEndInfo)` (scope `VulkanRHI`) — The VK_EXT_fragment_density_map_offset extension requires EndRenderPass2KHR so that we can pack extra info into the struct chain to specify the offsets
- L1476 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBeginRenderingKHR(VkCommandBuffer CommandBuffer, const VkRenderingInfo* RenderingInfo)` (scope `VulkanRHI`)
- L1483 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdEndRenderingKHR(VkCommandBuffer CommandBuffer)` (scope `VulkanRHI`)
- L1490 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdEndRendering2KHR(VkCommandBuffer CommandBuffer, const VkRenderingEndInfoKHR* RenderingEndInfo)` (scope `VulkanRHI`)
- L1497 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdExecuteCommands(VkCommandBuffer CommandBuffer, uint32 CommandBufferCount, const VkCommandBuffer* pCommandBuffers)` (scope `VulkanRHI`)
- L1504 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateSwapchainKHR(VkDevice Device, const VkSwapchainCreateInfoKHR* CreateInfo, const VkAllocationCallbacks* Allocator, VkSwapchainKHR* Swapchain)` (scope `VulkanRHI`)
- L1512 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroySwapchainKHR(VkDevice Device, VkSwapchainKHR Swapchain, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L1519 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetSwapchainImagesKHR(VkDevice Device, VkSwapchainKHR Swapchain, uint32_t* SwapchainImageCount, VkImage* SwapchainImages)` (scope `VulkanRHI`)
- L1527 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkAcquireNextImageKHR(VkDevice Device, VkSwapchainKHR Swapchain, uint64_t Timeout, VkSemaphore Semaphore, VkFence Fence, uint32_t* ImageIndex)` (scope `VulkanRHI`)
- L1535 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkQueuePresentKHR(VkQueue Queue, const VkPresentInfoKHR* PresentInfo)` (scope `VulkanRHI`)
- L1543 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, VkSurfaceCapabilitiesKHR* SurfaceCapabilities)` (scope `VulkanRHI`)
- L1551 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, uint32_t* SurfaceFormatCountPtr, VkSurfaceFormatKHR* SurfaceFormats)` (scope `VulkanRHI`)
- L1559 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice PhysicalDevice, uint32_t QueueFamilyIndex, VkSurfaceKHR Surface, VkBool32* SupportedPtr)` (scope `VulkanRHI`)
- L1567 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, uint32_t* PresentModeCountPtr, VkPresentModeKHR* PresentModesPtr)` (scope `VulkanRHI`)
- L1576 _function_ `FORCEINLINE_DEBUGGABLE VkResult vkCreateWin32SurfaceKHR(VkInstance Instance, const VkWin32SurfaceCreateInfoKHR* CreateInfo, const VkAllocationCallbacks* Allocator, VkSurfaceKHR* Surface)` (scope `VulkanRHI`)
- L1586 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateAndroidSurfaceKHR(VkInstance Instance, const VkAndroidSurfaceCreateInfoKHR* CreateInfo, const VkAllocationCallbacks* Allocator, VkSurfaceKHR* Surface)` (scope `VulkanRHI`)
- L1595 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroySurfaceKHR(VkInstance Instance, VkSurfaceKHR Surface, const VkAllocationCallbacks* pAllocator)` (scope `VulkanRHI`)
- L1602 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetImageMemoryRequirements2(VkDevice Device, const VkImageMemoryRequirementsInfo2* Info, VkMemoryRequirements2* MemoryRequirements)` (scope `VulkanRHI`)
- L1609 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetBufferMemoryRequirements2(VkDevice Device, const VkBufferMemoryRequirementsInfo2* Info, VkMemoryRequirements2* MemoryRequirements)` (scope `VulkanRHI`)
- L1616 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateAccelerationStructureKHR(VkDevice Device, const VkAccelerationStructureCreateInfoKHR* CreateInfo, const VkAllocationCallbacks* Allocator, VkAccelerationStructureKHR* AccelerationStructure)` (scope `VulkanRHI`)
- L1624 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyAccelerationStructureKHR(VkDevice Device, VkAccelerationStructureKHR AccelerationStructure, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L1631 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBuildAccelerationStructuresKHR(VkCommandBuffer CommandBuffer, uint32 InfoCount, const VkAccelerationStructureBuildGeometryInfoKHR* Infos, const VkAccelerationStructureBuildRangeInfoKHR* const* BuildRangeInfos)` (scope `VulkanRHI`)
- L1638 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetAccelerationStructureBuildSizesKHR(VkDevice Device, VkAccelerationStructureBuildTypeKHR BuildType, const VkAccelerationStructureBuildGeometryInfoKHR* BuildInfo, const uint32* MaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR* SizeInfo)` (scope `VulkanRHI`)
- L1645 _function_ `static FORCEINLINE_DEBUGGABLE VkDeviceAddress vkGetAccelerationStructureDeviceAddressKHR(VkDevice Device, const VkAccelerationStructureDeviceAddressInfoKHR* Info)` (scope `VulkanRHI`)
- L1653 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdTraceRaysKHR(VkCommandBuffer CommandBuffer, const VkStridedDeviceAddressRegionKHR* RaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* MissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* HitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* CallableShaderBindingTable, uint32 width, uint32 height, uint32 depth)` (scope `VulkanRHI`)
- L1660 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdTraceRaysIndirectKHR(VkCommandBuffer CommandBuffer, const VkStridedDeviceAddressRegionKHR* RaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* MissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* HitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* CallableShaderBindingTable, VkDeviceAddress IndirectDeviceAddress)` (scope `VulkanRHI`)
- L1667 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdTraceRaysIndirect2KHR(VkCommandBuffer CommandBuffer, VkDeviceAddress IndirectDeviceAddress)` (scope `VulkanRHI`)
- L1674 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateRayTracingPipelinesKHR(VkDevice Device, VkDeferredOperationKHR DeferredOperation, VkPipelineCache PipelineCache, uint32_t CreateInfoCount, const VkRayTracingPipelineCreateInfoKHR* CreateInfos, const VkAllocationCallbacks* Allocator, VkPipeline* Pipelines)` (scope `VulkanRHI`)
- L1682 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetRayTracingShaderGroupHandlesKHR(VkDevice Device, VkPipeline Pipeline, uint32_t FirstGroup, uint32_t GroupCount, size_t DataSize, void* Data)` (scope `VulkanRHI`)
- L1690 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer CommandBuffer, uint32_t AccelerationStructureCount, const VkAccelerationStructureKHR* AccelerationStructures, VkQueryType QueryType, VkQueryPool QueryPool, uint32_t FirstQuery)` (scope `VulkanRHI`)
- L1697 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdCopyAccelerationStructureKHR(VkCommandBuffer CommandBuffer, const VkCopyAccelerationStructureInfoKHR* Info)` (scope `VulkanRHI`)
- L1704 _function_ `static FORCEINLINE_DEBUGGABLE VkDeviceAddress vkGetBufferDeviceAddressKHR(VkDevice Device, const VkBufferDeviceAddressInfo* Info)` (scope `VulkanRHI`)
- L1712 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetDeviceImageMemoryRequirementsKHR(VkDevice Device, const VkDeviceImageMemoryRequirements* Info, VkMemoryRequirements2* MemoryRequirements)` (scope `VulkanRHI`)
- L1719 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetDeviceBufferMemoryRequirementsKHR(VkDevice Device, const VkDeviceBufferMemoryRequirements* Info, VkMemoryRequirements2* MemoryRequirements)` (scope `VulkanRHI`)
- L1726 _function_ `static FORCEINLINE_DEBUGGABLE void vkResetQueryPoolEXT(VkDevice Device, VkQueryPool QueryPool, uint32_t FirstQuery, uint32_t QueryCount)` (scope `VulkanRHI`)
- L1733 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(VkPhysicalDevice PhysicalDevice, uint32_t* TimeDomainCount, VkTimeDomainEXT* TimeDomains)` (scope `VulkanRHI`)
- L1741 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetCalibratedTimestampsEXT(VkDevice Device, uint32_t TimestampCount, const VkCalibratedTimestampInfoEXT* TimestampInfos, uint64_t* Timestamps, uint64_t* MaxDeviation)` (scope `VulkanRHI`)
- L1749 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkBindBufferMemory2(VkDevice Device, uint32_t BindInfoCount, const VkBindBufferMemoryInfo* BindInfos)` (scope `VulkanRHI`)
- L1757 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkBindImageMemory2(VkDevice Device, uint32_t BindInfoCount, const VkBindImageMemoryInfo* BindInfos)` (scope `VulkanRHI`)
- L1765 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdPipelineBarrier2KHR(VkCommandBuffer CommandBuffer, const VkDependencyInfo* DependencyInfo)` (scope `VulkanRHI`)
- L1772 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdResetEvent2KHR(VkCommandBuffer CommandBuffer, VkEvent Event, VkPipelineStageFlags2 StageMask)` (scope `VulkanRHI`)
- L1779 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetEvent2KHR(VkCommandBuffer CommandBuffer, VkEvent Event, const VkDependencyInfo* DependencyInfo)` (scope `VulkanRHI`)
- L1786 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdWaitEvents2KHR(VkCommandBuffer CommandBuffer, uint32_t EventCount, const VkEvent* Events, const VkDependencyInfo* DependencyInfos)` (scope `VulkanRHI`)
- L1793 _function_ `static FORCEINLINE_DEBUGGABLE void vkQueueSubmit2KHR(VkQueue Queue, uint32_t SubmitCount, const VkSubmitInfo2* Submits, VkFence Fence)` (scope `VulkanRHI`)
- L1800 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetDescriptorSetLayoutSizeEXT(VkDevice Device, VkDescriptorSetLayout Layout, VkDeviceSize* OutLayoutSizeInBytes)` (scope `VulkanRHI`)
- L1807 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetDescriptorSetLayoutBindingOffsetEXT(VkDevice Device, VkDescriptorSetLayout Layout, uint32_t Binding, VkDeviceSize* Offset)` (scope `VulkanRHI`)
- L1814 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBindDescriptorBuffersEXT(VkCommandBuffer CommandBuffer, uint32_t BufferCount, const VkDescriptorBufferBindingInfoEXT* BindingInfos)` (scope `VulkanRHI`)
- L1821 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer CommandBuffer, VkPipelineBindPoint PipelineBindPoint, VkPipelineLayout Layout, uint32_t FirstSet, uint32_t SetCount, const uint32_t* BufferIndices, const VkDeviceSize* Offsets)` (scope `VulkanRHI`)
- L1828 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetDescriptorBufferOffsets2EXT(VkCommandBuffer CommandBuffer, const VkSetDescriptorBufferOffsetsInfoEXT* SetDescriptorBufferOffsetsInfo)` (scope `VulkanRHI`)
- L1835 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetDescriptorEXT(VkDevice Device, const VkDescriptorGetInfoEXT* DescriptorInfo, size_t DataSize, void* Descriptor)` (scope `VulkanRHI`)
- L1842 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateDeferredOperationKHR(VkDevice Device, const VkAllocationCallbacks* Allocator, VkDeferredOperationKHR* DeferredOperation)` (scope `VulkanRHI`)
- L1850 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyDeferredOperationKHR(VkDevice Device, VkDeferredOperationKHR DeferredOperation, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L1857 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkDeferredOperationJoinKHR(VkDevice Device, VkDeferredOperationKHR DeferredOperation)` (scope `VulkanRHI`)
- L1865 _function_ `static FORCEINLINE_DEBUGGABLE uint32_t vkGetDeferredOperationMaxConcurrencyKHR(VkDevice Device, VkDeferredOperationKHR DeferredOperation)` (scope `VulkanRHI`)
- L1873 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetDeferredOperationResultKHR(VkDevice Device, VkDeferredOperationKHR DeferredOperation)` (scope `VulkanRHI`)
- L1881 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetDeviceFaultInfoEXT(VkDevice Device, VkDeviceFaultCountsEXT* FaultCounts, VkDeviceFaultInfoEXT* FaultInfo)` (scope `VulkanRHI`)
- L1889 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetPhysicalDeviceToolPropertiesEXT(VkPhysicalDevice PhysicalDevice, uint32_t* ToolCount, VkPhysicalDeviceToolPropertiesEXT* ToolProperties)` (scope `VulkanRHI`)
- L1897 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateSamplerYcbcrConversion(VkDevice Device, const VkSamplerYcbcrConversionCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkSamplerYcbcrConversion* YcbcrConversion)` (scope `VulkanRHI`)
- L1905 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroySamplerYcbcrConversion(VkDevice Device, VkSamplerYcbcrConversion YcbcrConversion, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L1913 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetAndroidHardwareBufferPropertiesANDROID(VkDevice Device, const struct AHardwareBuffer* Buffer, VkAndroidHardwareBufferPropertiesANDROID* Properties)` (scope `VulkanRHI`)
- L1922 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetSemaphoreCounterValueKHR(VkDevice Device, VkSemaphore Semaphore, uint64_t* Value)` (scope `VulkanRHI`)
- L1930 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkWaitSemaphoresKHR(VkDevice Device, const VkSemaphoreWaitInfo* WaitInfo, uint64_t Timeout)` (scope `VulkanRHI`)
- L1938 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkSignalSemaphoreKHR(VkDevice Device, const VkSemaphoreSignalInfo* SignalInfo)` (scope `VulkanRHI`)
- L1946 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateShadersEXT(VkDevice Device, uint32_t CreateInfoCount, const VkShaderCreateInfoEXT* CreateInfos, const VkAllocationCallbacks* Allocator, VkShaderEXT* Shaders)` (scope `VulkanRHI`)
- L1954 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyShaderEXT(VkDevice Device, VkShaderEXT Shader, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L1961 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetShaderBinaryDataEXT(VkDevice Device, VkShaderEXT Shader, size_t* DataSize, void* Data)` (scope `VulkanRHI`)
- L1969 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBindShadersEXT(VkCommandBuffer CommandBuffer, uint32_t StageCount, const VkShaderStageFlagBits* Stages, const VkShaderEXT* Shaders)` (scope `VulkanRHI`)
- L1976 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBindVertexBuffers2EXT(VkCommandBuffer CommandBuffer, uint32_t FirstBinding, uint32_t BindingCount, const VkBuffer* Buffers, const VkDeviceSize* Offsets, const VkDeviceSize* Sizes, const VkDeviceSize* Strides)` (scope `VulkanRHI`)
- L1983 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetCullModeEXT(VkCommandBuffer CommandBuffer, VkCullModeFlags CullMode)` (scope `VulkanRHI`)
- L1990 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetColorBlendEnableEXT(VkCommandBuffer CommandBuffer, uint32_t FirstAttachment, uint32_t AttachmentCount, const VkBool32* ColorBlendEnables)` (scope `VulkanRHI`)
- L1997 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetColorBlendEquationEXT(VkCommandBuffer CommandBuffer, uint32_t FirstAttachment, uint32_t AttachmentCount, const VkColorBlendEquationEXT* ColorBlendEquations)` (scope `VulkanRHI`)
- L2004 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetColorWriteMaskEXT(VkCommandBuffer CommandBuffer, uint32_t FirstAttachment, uint32_t AttachmentCount, const VkColorComponentFlags* ColorWriteMasks)` (scope `VulkanRHI`)
- L2011 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetFrontFaceEXT(VkCommandBuffer CommandBuffer, VkFrontFace FrontFace)` (scope `VulkanRHI`)
- L2018 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetPolygonModeEXT(VkCommandBuffer CommandBuffer, VkPolygonMode PolygonMode)` (scope `VulkanRHI`)
- L2025 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetPrimitiveTopologyEXT(VkCommandBuffer CommandBuffer, VkPrimitiveTopology PrimitiveTopology)` (scope `VulkanRHI`)
- L2032 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetRasterizationSamplesEXT(VkCommandBuffer CommandBuffer, VkSampleCountFlagBits RasterizationSamples)` (scope `VulkanRHI`)
- L2039 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetScissorWithCountEXT(VkCommandBuffer CommandBuffer, uint32_t ScissorCount, const VkRect2D* Scissors)` (scope `VulkanRHI`)
- L2046 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetStencilOpEXT(VkCommandBuffer CommandBuffer, VkStencilFaceFlags FaceMask, VkStencilOp FailOp, VkStencilOp PassOp, VkStencilOp DepthFailOp, VkCompareOp CompareOp)` (scope `VulkanRHI`)
- L2053 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetStencilTestEnableEXT(VkCommandBuffer CommandBuffer, VkBool32 StencilTestEnable)` (scope `VulkanRHI`)
- L2060 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetVertexInputEXT(VkCommandBuffer CommandBuffer, uint32_t VertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* VertexBindingDescriptions, uint32_t VertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* VertexAttributeDescriptions)` (scope `VulkanRHI`)
- L2067 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetViewportWithCountEXT(VkCommandBuffer CommandBuffer, uint32_t ViewportCount, const VkViewport* Viewports)` (scope `VulkanRHI`)
- L2074 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetDepthBiasEnableEXT(VkCommandBuffer CommandBuffer, VkBool32 DepthBiasEnable)` (scope `VulkanRHI`)
- L2081 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetDepthBoundsTestEnableEXT(VkCommandBuffer CommandBuffer, VkBool32 DepthBoundsTestEnable)` (scope `VulkanRHI`)
- L2088 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetDepthClampEnableEXT(VkCommandBuffer CommandBuffer, VkBool32 DepthClampEnable)` (scope `VulkanRHI`)
- L2095 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetDepthCompareOpEXT(VkCommandBuffer CommandBuffer, VkCompareOp DepthCompareOp)` (scope `VulkanRHI`)
- L2102 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetDepthTestEnableEXT(VkCommandBuffer CommandBuffer, VkBool32 DepthTestEnable)` (scope `VulkanRHI`)
- L2109 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetDepthWriteEnableEXT(VkCommandBuffer CommandBuffer, VkBool32 DepthWriteEnable)` (scope `VulkanRHI`)
- L2116 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetRasterizerDiscardEnableEXT(VkCommandBuffer CommandBuffer, VkBool32 RasterizerDiscardEnable)` (scope `VulkanRHI`)
- L2123 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetPrimitiveRestartEnableEXT(VkCommandBuffer CommandBuffer, VkBool32 PrimitiveRestartEnable)` (scope `VulkanRHI`)
- L2130 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetLogicOpEnableEXT(VkCommandBuffer CommandBuffer, VkBool32 LogicOpEnable)` (scope `VulkanRHI`)
- L2137 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetAlphaToCoverageEnableEXT(VkCommandBuffer CommandBuffer, VkBool32 AlphaToCoverageEnable)` (scope `VulkanRHI`)
- L2144 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetAlphaToOneEnableEXT(VkCommandBuffer CommandBuffer, VkBool32 AlphaToOneEnable)` (scope `VulkanRHI`)
- L2151 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetSampleMaskEXT(VkCommandBuffer CommandBuffer, VkSampleCountFlagBits Samples, const VkSampleMask* SampleMask)` (scope `VulkanRHI`)
- L2158 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetFragmentShadingRateKHR(VkCommandBuffer CommandBuffer, const VkExtent2D* FragmentSize, const VkFragmentShadingRateCombinerOpKHR combinerOps[2])` (scope `VulkanRHI`)
- L2165 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdExecuteGeneratedCommandsEXT(VkCommandBuffer CommandBuffer, VkBool32 IsPreprocessed, const VkGeneratedCommandsInfoEXT* GeneratedCommandsInfo)` (scope `VulkanRHI`)
- L2172 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdPreprocessGeneratedCommandsEXT(VkCommandBuffer CommandBuffer, const VkGeneratedCommandsInfoEXT* GeneratedCommandsInfo, VkCommandBuffer StateCommandBuffer)` (scope `VulkanRHI`)
- L2179 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateIndirectCommandsLayoutEXT(VkDevice Device, const VkIndirectCommandsLayoutCreateInfoEXT* CreateInfo, const VkAllocationCallbacks* Allocator, VkIndirectCommandsLayoutEXT* IndirectCommandsLayout)` (scope `VulkanRHI`)
- L2187 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCreateIndirectExecutionSetEXT(VkDevice Device, const VkIndirectExecutionSetCreateInfoEXT* CreateInfo, const VkAllocationCallbacks* Allocator, VkIndirectExecutionSetEXT* IndirectExecutionSet)` (scope `VulkanRHI`)
- L2195 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyIndirectCommandsLayoutEXT(VkDevice Device, VkIndirectCommandsLayoutEXT IndirectCommandsLayout, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L2202 _function_ `static FORCEINLINE_DEBUGGABLE void vkDestroyIndirectExecutionSetEXT(VkDevice Device, VkIndirectExecutionSetEXT IndirectExecutionSet, const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L2209 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetGeneratedCommandsMemoryRequirementsEXT(VkDevice Device, const VkGeneratedCommandsMemoryRequirementsInfoEXT* Info, VkMemoryRequirements2* MemoryRequirements)` (scope `VulkanRHI`)
- L2216 _function_ `static FORCEINLINE_DEBUGGABLE void vkUpdateIndirectExecutionSetPipelineEXT(VkDevice Device, VkIndirectExecutionSetEXT IndirectExecutionSet, uint32_t ExecutionSetWriteCount, const VkWriteIndirectExecutionSetPipelineEXT* ExecutionSetWrites)` (scope `VulkanRHI`)
- L2223 _function_ `static FORCEINLINE_DEBUGGABLE void vkUpdateIndirectExecutionSetShaderEXT(VkDevice Device, VkIndirectExecutionSetEXT IndirectExecutionSet, uint32_t ExecutionSetWriteCount, const VkWriteIndirectExecutionSetShaderEXT* ExecutionSetWrites)` (scope `VulkanRHI`)
- L2231 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkCopyMemoryToImageEXT(VkDevice Device, const VkCopyMemoryToImageInfo* CopyMemoryToImageInfo)` (scope `VulkanRHI`)
- L2239 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkTransitionImageLayoutEXT(VkDevice Device, uint32_t TransitionCount, const VkHostImageLayoutTransitionInfo* Transitions)` (scope `VulkanRHI`)
- L2247 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetPastPresentationTimingEXT(VkDevice Device, const VkPastPresentationTimingInfoEXT* PastPresentationTimingInfo, VkPastPresentationTimingPropertiesEXT* PastPresentationTimingProperties)` (scope `VulkanRHI`)
- L2255 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetSwapchainTimeDomainPropertiesEXT(VkDevice Device, VkSwapchainKHR Swapchain, VkSwapchainTimeDomainPropertiesEXT* SwapchainTimeDomainProperties, uint64_t* TimeDomainsCounter)` (scope `VulkanRHI`)
- L2263 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkGetSwapchainTimingPropertiesEXT(VkDevice Device, VkSwapchainKHR Swapchain, VkSwapchainTimingPropertiesEXT* SwapchainTimingProperties, uint64_t* SwapchainTimingPropertiesCounter)` (scope `VulkanRHI`)
- L2271 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkSetSwapchainPresentTimingQueueSizeEXT(VkDevice Device, VkSwapchainKHR Swapchain, uint32_t Size)` (scope `VulkanRHI`)
- L2279 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBindResourceHeapEXT(VkCommandBuffer CommandBuffer, const VkBindHeapInfoEXT* BindInfo)` (scope `VulkanRHI`)
- L2286 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdBindSamplerHeapEXT(VkCommandBuffer CommandBuffer, const VkBindHeapInfoEXT* BindInfo)` (scope `VulkanRHI`)
- L2293 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdPushDataEXT(VkCommandBuffer CommandBuffer, const VkPushDataInfoEXT* PushDataInfo)` (scope `VulkanRHI`)
- L2300 _function_ `static FORCEINLINE_DEBUGGABLE VkDeviceSize vkGetPhysicalDeviceDescriptorSizeEXT(VkPhysicalDevice PhysicalDevice, VkDescriptorType DescriptorType)` (scope `VulkanRHI`)
- L2308 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkWriteResourceDescriptorsEXT(VkDevice Device, uint32_t ResourceCount, const VkResourceDescriptorInfoEXT* Resources, const VkHostAddressRangeEXT* Descriptors)` (scope `VulkanRHI`)
- L2316 _function_ `static FORCEINLINE_DEBUGGABLE VkResult vkWriteSamplerDescriptorsEXT(VkDevice Device, uint32_t SamplerCount, const VkSamplerCreateInfo* Samplers, const VkHostAddressRangeEXT* Descriptors)` (scope `VulkanRHI`)
- L2324 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetRenderingAttachmentLocationsKHR(VkCommandBuffer CommandBuffer, const VkRenderingAttachmentLocationInfo* LocationInfo)` (scope `VulkanRHI`)
- L2331 _function_ `static FORCEINLINE_DEBUGGABLE void vkCmdSetRenderingInputAttachmentIndicesKHR(VkCommandBuffer CommandBuffer, const VkRenderingInputAttachmentIndexInfo* InputAttachmentIndexInfo)` (scope `VulkanRHI`)
- L2338 _function_ `static FORCEINLINE_DEBUGGABLE void vkGetDescriptorSetLayoutSupport(VkDevice Device, const VkDescriptorSetLayoutCreateInfo* CreateInfo, VkDescriptorSetLayoutSupport* OutSupport)` (scope `VulkanRHI`)
- L2347 _prototype_ `void BindDebugLabelName(VkImage Image, const TCHAR* Name);` (scope `VulkanRHI`)
- L2351 _prototype_ `void DumpLayerPushMarker(const TCHAR* Name);` (scope `VulkanRHI`)
- L2352 _prototype_ `void DumpLayerPopMarker();` (scope `VulkanRHI`)
- L2353 _prototype_ `void PrintfBegin(const FString& String);` (scope `VulkanRHI`)

### `Source/Runtime/VulkanRHI/Private/VulkanCommandsDirect.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/VulkanRHI/Private/VulkanContext.h` (Private)


#### enum `EVulkanFlushFlags`  
`enum class EVulkanFlushFlags`  
_L22-31_
- L24 _public enumerator_ `None = 0`
- L27 _public enumerator_ `WaitForSubmission = 1` — Block the calling thread until the submission thread has dispatched all work.
- L30 _public enumerator_ `WaitForCompletion = 2` — Both the calling thread until the GPU has signaled completion of all dispatched work.

#### struct `FVulkanDynamicRenderingInfo`  
`struct FVulkanDynamicRenderingInfo`  
_L35-47_
- L38 _public member_ `TStaticArray<VkRenderingAttachmentInfo, MaxSimultaneousRenderTargets> ColorAttachmentInfos;` — Vulkan structures sent to API
- L39 _public member_ `VkRenderingAttachmentInfo DepthAttachmentInfo;`
- L40 _public member_ `VkRenderingAttachmentInfo StencilAttachmentInfo;`
- L41 _public member_ `VkRenderingFragmentShadingRateAttachmentInfoKHR FragmentShadingRateAttachmentInfo;`
- L42 _public member_ `VkRenderingInfo RenderingInfo;`
- L45 _public member_ `TStaticArray<FVulkanView*, MaxSimultaneousRenderTargets> ColorAttachmentViews;` — View tracking used for input attachments
- L46 _public member_ `FVulkanView* PartialDepthAttachmentView;`

#### struct `FVulkanParallelRenderPassInfo`  
`struct FVulkanParallelRenderPassInfo`  
_L49-55_
- L51 _public member_ `VkRenderPass RenderPassHandle = VK_NULL_HANDLE;`
- L52 _public member_ `TUniquePtr<FVulkanDynamicRenderingInfo> DynamicRenderingInfo;`
- L53 _public member_ `TArray<FVulkanPayload*> SecondaryPayloads;`
- L54 _public member_ `std::atomic<int32> NumParallelContexts = 0;`

#### class `FVulkanContextCommon`  
`class FVulkanContextCommon`  
_L58-241_
- L74 _public prototype_ `FVulkanContextCommon(FVulkanDevice& InDevice, FVulkanQueue& InQueue, EVulkanCommandBufferType InCommandBufferType);`
- L75 _public prototype_ `virtual ~FVulkanContextCommon();`
- L77 _public function_ `FVulkanPayload& GetPayload(EPhase Phase)`
- L89 _public function_ `FVulkanCommandBuffer* GetActiveCmdBuffer()` — NOTE: This call is getting phased out, use GetCommandBuffer()
- L94 _public function_ `FVulkanCommandBuffer& GetCommandBuffer()`
- L107 _public function_ `void AddWaitSemaphore(VkPipelineStageFlags InWaitFlags, FVulkanSemaphore* InWaitSemaphore)`
- L111 _public function_ `void AddWaitSemaphores(VkPipelineStageFlags InWaitFlags, TArrayView<FVulkanSemaphore*> InWaitSemaphores)`
- L127 _public function_ `void AddSignalSemaphore(FVulkanSemaphore* InSignalSemaphore)`
- L131 _public function_ `void AddSignalSemaphores(TArrayView<FVulkanSemaphore*> InSignalSemaphores)`
- L142 _public prototype_ `virtual void Finalize(TArray<FVulkanPayload*>& OutPayloads);` — Complete recording of the current command list set, and appends the resulting payloads to the given array. Resets the context so new commands can be recorded.
- L144 _public function_ `VkCommandPool GetHandle() const`
- L149 _public prototype_ `void FreeUnusedCmdBuffers(bool bTrimMemory);`
- L152 _public prototype_ `void FlushCommands(EVulkanFlushFlags FlushFlags = EVulkanFlushFlags::None);` — Should only ne used when we are certain there are no other pending contexts (like UploadContext)
- L155 _public member_ `FVulkanDevice& Device;` — Public immutable references, access them directly
- L156 _public member_ `FVulkanQueue& Queue;`
- L159 _public function_ `void SignalSyncPoint(const FVulkanSyncPointRef& InSync)` — Add a provided sync point that will be signaled at the end of the current payload's accumulated work
- L166 _public function_ `void AddPendingSyncPoint(const FVulkanSyncPointRef& InSyncs)` — Add provided sync points that will be appended next time a payload reaches the Signal phase
- L172 _public function_ `void AddSubmissionEvent(const FGraphEventRef& InEvent)` — Add an event to be signaled with the current payload is submitted (does not alter phase)
- L179 _public function_ `void FlushPendingSyncPoints()` — Force pending syncs to be sent to a payload
- L190 _public function_ `FVulkanSyncPointRef GetContextSyncPoint()` — Returns a single sync point for the context that will be inserted when it is finalized
- L199 _public function_ `TArray<FVulkanQueryPool*>& GetQueryPoolArray(EVulkanQueryPoolType Type)`
- L205 _public function_ `FVulkanQueryPool* GetCurrentTimestampQueryPool()`
- L210 _public function_ `virtual FVulkanParallelRenderPassInfo* GetParallelRenderPassInfo()`
- L215 _public prototype_ `void HandleReservedResourceCommits(TArrayView<const FRHITransition*> Transitions);`
- L220 _protected prototype_ `void AppendParallelRenderPayload(FVulkanPayload* ParallelRenderingPayload, VkRenderingInfo* NeedsResumeInfo);`
- L224 _private prototype_ `FVulkanQueryPool* GetCurrentTimestampQueryPool(FVulkanPayload& Payload);`
- L225 _private prototype_ `void PrepareNewCommandBuffer(FVulkanPayload& Payload, bool bAllowTimestamp=true);`
- L226 _private prototype_ `void NewPayload();`
- L227 _private prototype_ `void EndPayload();`
- L229 _private member_ `FVulkanCommandBufferPool& Pool;`
- L231 _private member_ `TArray<FVulkanPayload*> Payloads;`
- L232 _private member_ `EPhase CurrentPhase = EPhase::Wait;`
- L235 _private member_ `TArray<FVulkanSyncPointRef> PendingSyncPoints;` — Sync points signaled at the next Signal phase (will not force a phase change) or when context is finalized
- L238 _private member_ `FVulkanSyncPointRef ContextSyncPoint;` — Sync point signaled when the current context is finalized

#### enum `FVulkanContextCommon::EPhase`  
`enum class EPhase`  
_L65-71_
- desc: Phases are used to track where we are at in filling the current payload. Phases always move forward in the order declared here, never backwards. Always use GetPayload(EPhase) to fetch the payload for the phase you want, it will take care of creating a new payload when necessary.
- L67 _public enumerator_ `Wait`
- L68 _public enumerator_ `UpdateReservedResources`
- L69 _public enumerator_ `Execute`
- L70 _public enumerator_ `Signal`

#### class `FVulkanCommandListContext`  
`class FVulkanCommandListContext : public FVulkanContextCommon, public IRHICommandContext`  
_L245-452_
- inherits: `FVulkanContextCommon,IRHICommandContext`
- L248 _public prototype_ `FVulkanCommandListContext(FVulkanDevice& InDevice, ERHIPipeline InPipeline, bool bInImmediate);`
- L249 _public prototype_ `virtual ~FVulkanCommandListContext();`
- L252 _public prototype_ `FVulkanCommandListContext(FVulkanDevice& InDevice, FVulkanParallelRenderPassInfo* InParallelRenderPassInfo);` — Constructor for parallel render contexts that use secondary command buffers
- L254 _public function_ `static inline FVulkanCommandListContext& Get(FRHICommandListBase& RHICmdList)`
- L259 _public function_ `inline bool IsImmediate() const`
- L264 _public function_ `virtual ERHIPipeline GetPipeline() const override`
- L269 _public prototype_ `template <class ShaderType> void SetResourcesFromTables(const ShaderType* RESTRICT);`
- L270 _public prototype_ `template <class ShaderType> void SetResourcesFromTables(const ShaderType* RESTRICT);`
- L271 _public prototype_ `void CommitComputeResourceTables();`
- L273 _public prototype_ `virtual void RHISetStreamSource(uint32 StreamIndex, FRHIBuffer* VertexBuffer, uint32 Offset) final override;`
- L274 _public prototype_ `virtual void RHISetViewport(float MinX, float MinY, float MinZ, float MaxX, float MaxY, float MaxZ) final override;`
- L275 _public prototype_ `virtual void RHISetStereoViewport(float LeftMinX, float RightMinX, float LeftMinY, float RightMinY, float MinZ, float LeftMaxX, float RightMaxX, float LeftMaxY, float RightMaxY, float MaxZ) override;`
- L276 _public prototype_ `virtual void RHISetScissorRect(bool bEnable, uint32 MinX, uint32 MinY, uint32 MaxX, uint32 MaxY) final override;`
- L277 _public prototype_ `virtual void RHISetGraphicsPipelineState(FRHIGraphicsPipelineState* GraphicsState, uint32 StencilRef, bool bApplyAdditionalState) final override;`
- L278 _public prototype_ `virtual void RHISetStaticUniformBuffers(const FUniformBufferStaticBindings& InUniformBuffers) final override;`
- L279 _public prototype_ `virtual void RHISetStaticUniformBuffer(FUniformBufferStaticSlot Slot, FRHIUniformBuffer* Buffer) final override;`
- L280 _public prototype_ `virtual void RHISetUniformBufferDynamicOffset(FUniformBufferStaticSlot Slot, uint32 InOffset) final override;`
- L281 _public prototype_ `virtual void RHISetShaderParameters(FRHIGraphicsShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override;`
- L282 _public prototype_ `virtual void RHISetShaderParameters(FRHIComputeShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override;`
- L283 _public prototype_ `virtual void RHISetStencilRef(uint32 StencilRef) final override;`
- L284 _public prototype_ `virtual void RHIDrawPrimitive(uint32 BaseVertexIndex, uint32 NumPrimitives, uint32 NumInstances) final override;`
- L285 _public prototype_ `virtual void RHIDrawPrimitiveIndirect(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L286 _public prototype_ `virtual void RHIDrawIndexedPrimitive(FRHIBuffer* IndexBuffer, int32 BaseVertexIndex, uint32 FirstInstance, uint32 NumVertices, uint32 StartIndex, uint32 NumPrimitives, uint32 NumInstances) final override;`
- L287 _public prototype_ `virtual void RHIDrawIndexedPrimitiveIndirect(FRHIBuffer* IndexBuffer, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L289 _public prototype_ `virtual void RHIDispatchMeshShader(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ) final override;`
- L290 _public prototype_ `virtual void RHIDispatchIndirectMeshShader(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L292 _public prototype_ `virtual void RHISetDepthBounds(float MinDepth, float MaxDepth) final override;`
- L294 _public prototype_ `virtual void RHIBeginBreadcrumbGPU(FRHIBreadcrumbNode* Breadcrumb) final override;`
- L295 _public prototype_ `virtual void RHIEndBreadcrumbGPU (FRHIBreadcrumbNode* Breadcrumb) final override;`
- L297 _public prototype_ `virtual void RHISetComputePipelineState(FRHIComputePipelineState* ComputePipelineState) final override;`
- L298 _public prototype_ `virtual void RHIDispatchComputeShader(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ) final override;`
- L299 _public prototype_ `virtual void RHIDispatchIndirectComputeShader(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L301 _public prototype_ `virtual void RHISetMultipleViewports(uint32 Count, const FViewportBounds* Data) final override;`
- L302 _public prototype_ `virtual void RHIClearUAVFloat(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FVector4f& Values) final override;`
- L303 _public prototype_ `virtual void RHIClearUAVUint(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FUintVector4& Values) final override;`
- L304 _public prototype_ `virtual void RHICopyTexture(FRHITexture* SourceTexture, FRHITexture* DestTexture, const FRHICopyTextureInfo& CopyInfo) final override;`
- L305 _public prototype_ `virtual void RHICopyBufferRegion(FRHIBuffer* DstBuffer, uint64 DstOffset, FRHIBuffer* SrcBuffer, uint64 SrcOffset, uint64 NumBytes) final override;`
- L306 _public prototype_ `virtual void RHIBeginTransitions(TArrayView<const FRHITransition*> Transitions) override final;`
- L307 _public prototype_ `virtual void RHIEndTransitions(TArrayView<const FRHITransition*> Transitions) override final;`
- L308 _public prototype_ `virtual void RHICopyToStagingBuffer(FRHIBuffer* SourceBuffer, FRHIStagingBuffer* DestinationStagingBuffer, uint32 Offset, uint32 NumBytes) final override;`
- L309 _public prototype_ `virtual void RHIWriteGPUFence(FRHIGPUFence* Fence) final override;`
- L312 _public prototype_ `virtual void RHIBeginRenderQuery(FRHIRenderQuery* RenderQuery) final override;` — Render time measurement
- L313 _public prototype_ `virtual void RHIEndRenderQuery(FRHIRenderQuery* RenderQuery) final override;`
- L315 _public function_ `void FlushProfilerStats()`
- L325 _public prototype_ `virtual void Finalize(TArray<FVulkanPayload*>& OutPayloads) override;`
- L327 _public prototype_ `virtual void RHIBeginRenderPass(const FRHIRenderPassInfo& InInfo, const TCHAR* InName) final override;`
- L328 _public prototype_ `virtual void RHIEndRenderPass() final override;`
- L329 _public prototype_ `virtual void RHINextSubpass() final override;`
- L331 _public prototype_ `virtual void RHIBeginParallelRenderPass(TSharedPtr<FRHIParallelRenderPassInfo> InInfo, const TCHAR* InName) final override;`
- L332 _public prototype_ `virtual void RHIEndParallelRenderPass() final override;`
- L334 _public prototype_ `virtual void RHICommitShaderBindingTable(FRHIShaderBindingTable* SBT, FRHIBuffer* InlineBindingDataBuffer) final override;`
- L335 _public prototype_ `virtual void RHIBindAccelerationStructureMemory(FRHIRayTracingScene* Scene, FRHIBuffer* Buffer, uint32 BufferOffset) final override;`
- L336 _public prototype_ `virtual void RHIBuildAccelerationStructures(TConstArrayView<FRayTracingGeometryBuildParams> Params, const FRHIBufferRange& ScratchBufferRange) final override;`
- L337 _public prototype_ `virtual void RHIBuildAccelerationStructures(TConstArrayView<FRayTracingSceneBuildParams> Params) final override;`
- L339 _public prototype_ `virtual void RHIRayTraceDispatch(FRHIRayTracingPipelineState* RayTracingPipelineState, FRHIRayTracingShader* RayGenShader, FRHIShaderBindingTable* SBT, const FRayTracingShaderBindings& GlobalResourceBindings, uint32 Width, uint32 Height) final override;`
- L342 _public prototype_ `virtual void RHIRayTraceDispatchIndirect(FRHIRayTracingPipelineState* RayTracingPipelineState, FRHIRayTracingShader* RayGenShader, FRHIShaderBindingTable* SBT, const FRayTracingShaderBindings& GlobalResourceBindings, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L346 _public prototype_ `virtual void RHISetBindingsOnShaderBindingTable(FRHIShaderBindingTable* SBT, FRHIRayTracingPipelineState* Pipeline, uint32 NumBindings, const FRayTracingLocalShaderBindings* Bindings, ERayTracingBindingType BindingType) final override;`
- L351 _public prototype_ `void InsertEndFrameDebugLabel();`
- L353 _public function_ `inline FVulkanPendingGfxState* GetPendingGfxState()`
- L358 _public function_ `inline FVulkanPendingComputeState* GetPendingComputeState()`
- L363 _public prototype_ `void NotifyDeletedRenderTarget(VkImage Image);`
- L365 _public function_ `inline FVulkanRenderPass* GetCurrentRenderPass()`
- L370 _public function_ `inline FVulkanFramebuffer* GetCurrentFramebuffer()`
- L375 _public function_ `void BeginRecursiveCommand()`
- L380 _public prototype_ `void ReleasePendingState();`
- L382 _public prototype_ `FVulkanQueryPool* GetCurrentOcclusionQueryPool();`
- L384 _public function_ `virtual FVulkanParallelRenderPassInfo* GetParallelRenderPassInfo()`
- L389 _public function_ `void SetParallelRenderPassInfo(FVulkanParallelRenderPassInfo* ParallelRenderPassInfo)`
- L394 _public prototype_ `bool AcquirePoolSetAndDescriptorsIfNeeded(const class FVulkanDescriptorSetsLayout& Layout, bool bNeedDescriptors, VkDescriptorSet* OutDescriptors);`
- L396 _public prototype_ `bool IsSwapchainImage(FRHITexture* InTexture) const;`
- L397 _public prototype_ `FVulkanSwapChain* GetSwapChain() const;`
- L399 _public prototype_ `FVulkanRenderPass* PrepareRenderPassForPSOCreation(const FGraphicsPipelineStateInitializer& Initializer);`
- L400 _public prototype_ `FVulkanRenderPass* PrepareRenderPassForPSOCreation(const FVulkanRenderTargetLayout& Initializer);`
- L402 _public prototype_ `void ApplyShaderBindingLayout();`
- L404 _public prototype_ `void ExtractDepthStencilLayouts(const FRHIRenderPassInfo& InInfo, VkImageLayout& OutDepthLayout, VkImageLayout& OutStencilLayout);`
- L405 _public prototype_ `void FillDynamicRenderingInfo(const FRHIRenderPassInfo& RenderPassInfo, FVulkanDynamicRenderingInfo& OutRenderingInfo);`
- L407 _public member_ `const ERHIPipeline RHIPipeline;`
- L408 _public member_ `const bool bSupportsBreadcrumbs;`
- L409 _public member_ `const bool bImmediate;`
- L411 _public prototype_ `void BeginOcclusionQueryBatch(uint32 NumQueriesInBatch, uint32 MultiViewCount);`
- L413 _public member_ `TArray<FString> EventStack;`
- L415 _public member_ `FVulkanRenderPass* CurrentRenderPass = nullptr;`
- L416 _public member_ `FVulkanFramebuffer* CurrentFramebuffer = nullptr;`
- L418 _public member_ `FVulkanParallelRenderPassInfo* CurrentParallelRenderPassInfo = nullptr;`
- L419 _public member_ `FVulkanDynamicRenderingInfo* CurrentDynamicRenderingInfo = nullptr;`
- L421 _public member_ `FVulkanPendingGfxState* PendingGfxState = nullptr;`
- L422 _public member_ `FVulkanPendingComputeState* PendingComputeState = nullptr;`
- L428 _public member_ `FVulkanUniformBuffer* BoundUniformBuffers[SF_NumStandardFrequencies][MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE] = {};` — Track the currently bound uniform buffers.
- L431 _public member_ `uint16 DirtyUniformBuffers[SF_NumStandardFrequencies] = {};` — Bit array to track which uniform buffers have changed since the last draw call.
- L433 _public prototype_ `void InternalClearMRT(FVulkanCommandBuffer& CommandBuffer, bool bClearColor, int32 NumClearColors, const FLinearColor* ColorArray, bool bClearDepth, float Depth, bool bClearStencil, uint32 Stencil);`
- L435 _public member_ `FVulkanDescriptorPoolSetContainer* CurrentDescriptorPoolSetContainer = nullptr;`
- L436 _public member_ `TMap<uint32, class FVulkanTypedDescriptorPoolSet*> TypedDescriptorPoolSets;`
- L437 _public prototype_ `void AcquirePoolSetContainer();`
- L439 _public function_ `inline const TArray<FRHIUniformBuffer*>& GetStaticUniformBuffers() const`
- L445 _private prototype_ `void RHIClearMRT(bool bClearColor, int32 NumClearColors, const FLinearColor* ColorArray, bool bClearDepth, float Depth, bool bClearStencil, uint32 Stencil);`
- L450 _private member_ `TArray<FRHIUniformBuffer*> StaticUniformBuffers;`
- L451 _private member_ `const FRHIShaderBindingLayout* ShaderBindingLayout = nullptr;`

#### enum `FVulkanCommandListContext::(anonymous)`  
`enum`  
_L425-425_
- desc: Match the D3D12 maximum of 16 constant buffers per shader stage.

#### class `FVulkanUploadContext`  
`class FVulkanUploadContext : public FVulkanContextCommon, public IRHIUploadContext`  
_L454-468_
- inherits: `FVulkanContextCommon,IRHIUploadContext`
- L458 _public function_ `static inline FVulkanUploadContext& Get(FRHICommandListBase& RHICmdList)`
- L463 _public prototype_ `FVulkanUploadContext(FVulkanDevice& Device, FVulkanQueue& InQueue);`
- L464 _public prototype_ `virtual ~FVulkanUploadContext();`
- L466 _public member_ `static TLockFreePointerListUnordered<FVulkanUploadContext, PLATFORM_CACHE_LINE_SIZE> Pool;`
- L467 _public prototype_ `static void DestroyPool();`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<IRHIUploadContext>`  
_L471-474_
- L473 _public typedef_ `typedef FVulkanUploadContext TConcreteType;`

#### struct `FVulkanContextArray`  
`struct FVulkanContextArray : public TRHIPipelineArray<FVulkanCommandListContext*>`  
_L477-493_
- inherits: `TRHIPipelineArray<FVulkanCommandListContext*>`
- L479 _public function_ `FVulkanContextArray() : TRHIPipelineArray(InPlace, nullptr)`
- L484 _public function_ `FVulkanContextArray(FRHIContextArray const& Contexts) : TRHIPipelineArray(InPlace, nullptr)`

#### Free symbols / members of external scopes

- L425 _enumerator_ `enum { MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE = 16 }; FVulkanUniformBuffer* BoundUniformBuffers[SF_NumStandardFrequencies][MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE] = {}; uint16 DirtyUniformBuffers[SF_NumStandardFrequencies] = {};` (scope `FVulkanCommandListContext::__anon0e8c23a20103`) — Match the D3D12 maximum of 16 constant buffers per shader stage.

### `Source/Runtime/VulkanRHI/Private/VulkanDescriptorSets.h` (Private)


#### class `FVulkanDSetKey`  
`class FVulkanDSetKey : public TDataKey<FVulkanDSetKey, true>`  
_L22-22_
- inherits: `TDataKey<FVulkanDSetKey,true>`
- desc: (AlwaysCompareData == true) because of CRC-32 hash collisions

#### class `FVulkanDSetsKey`  
`class FVulkanDSetsKey : public TDataKey<FVulkanDSetsKey, true>`  
_L23-23_
- inherits: `TDataKey<FVulkanDSetsKey,true>`

#### struct `FUniformBufferGatherInfo`  
`struct FUniformBufferGatherInfo`  
_L25-28_
- L27 _public member_ `const FVulkanShaderHeader* CodeHeaders[ShaderStage::MaxNumStages]{};`

#### class `FVulkanDescriptorSetsLayoutInfo`  
`class FVulkanDescriptorSetsLayoutInfo`  
_L32-231_
- desc: Information for the layout of descriptor sets; does not hold runtime objects
- L35 _public function_ `FVulkanDescriptorSetsLayoutInfo()`
- L46 _public function_ `inline uint32 GetTypesUsed(VkDescriptorType Type) const`
- L68 _public function_ `friend uint32 GetTypeHash(const FSetLayout& In)`
- L100 _public function_ `const TArray<FSetLayout>& GetLayouts() const`
- L106 _public prototype_ `template<bool bIsCompute> void FinalizeBindings(const FVulkanDevice& Device, const FUniformBufferGatherInfo& UBGatherInfo, bool bUsesBindless);`
- L108 _public prototype_ `void GenerateHash(VkPipelineBindPoint InBindPoint);`
- L115 _public function_ `inline bool operator == (const FVulkanDescriptorSetsLayoutInfo& In) const`
- L153 _public function_ `void CopyFrom(const FVulkanDescriptorSetsLayoutInfo& Info)`
- L162 _public function_ `inline const TMap<VkDescriptorType, uint32>& GetLayoutTypes() const`
- L167 _public function_ `inline uint32 GetTypesUsageID() const`
- L172 _public function_ `inline bool HasInputAttachments() const`
- L212 _public member_ `TStaticArray<FStageInfo, ShaderStage::MaxNumStages> StageInfos;`
- L215 _protected member_ `TMap<VkDescriptorType, uint32> LayoutTypes;`
- L216 _protected member_ `TArray<FSetLayout> SetLayouts;`
- L218 _protected member_ `uint32 Hash = 0;`
- L220 _protected member_ `uint32 TypesUsageID = ~0;`
- L222 _protected member_ `VkPipelineBindPoint BindPoint = VK_PIPELINE_BIND_POINT_MAX_ENUM;`
- L224 _protected prototype_ `void CompileTypesUsageID();`
- L226 _protected prototype_ `void AddDescriptor(int32 DescriptorSetIndex, const VkDescriptorSetLayoutBinding& Descriptor);`

#### struct `FVulkanDescriptorSetsLayoutInfo::FSetLayout`  
`struct FSetLayout`  
_L58-98_
- L60 _public member_ `TArray<VkDescriptorSetLayoutBinding> LayoutBindings;`
- L61 _public member_ `uint32 Hash;`
- L63 _public function_ `inline void GenerateHash()`
- L73 _public function_ `inline bool operator == (const FSetLayout& In) const`
- L94 _public function_ `inline bool operator != (const FSetLayout& In) const`

#### struct `FVulkanDescriptorSetsLayoutInfo::FStageInfo`  
`struct FStageInfo`  
_L177-211_
- L179 _public member_ `TArray<VkDescriptorType> Types;`
- L180 _public member_ `uint32 PackedGlobalsSize = 0;`
- L181 _public member_ `uint32 NumBoundUniformBuffers = 0;`
- L182 _public member_ `uint16 NumImageInfos = 0;`
- L183 _public member_ `uint16 NumBufferInfos = 0;`
- L184 _public member_ `uint16 NumAccelerationStructures = 0;`
- L186 _public function_ `inline bool IsEmpty() const`
- L196 _public function_ `inline bool operator==(const FStageInfo& In) const`

#### struct `FVulkanDescriptorSetLayoutEntry`  
`struct FVulkanDescriptorSetLayoutEntry`  
_L233-237_
- L235 _public member_ `VkDescriptorSetLayout Handle = 0;`
- L236 _public member_ `uint32 HandleId = 0;`

#### class `FVulkanDescriptorSetsLayout`  
`class FVulkanDescriptorSetsLayout : public FVulkanDescriptorSetsLayoutInfo`  
_L242-277_
- inherits: `FVulkanDescriptorSetsLayoutInfo`
- desc: The actual run-time descriptor set layouts
- L245 _public prototype_ `FVulkanDescriptorSetsLayout(FVulkanDevice* InDevice);`
- L246 _public prototype_ `~FVulkanDescriptorSetsLayout();`
- L249 _public prototype_ `void Compile(FVulkanDescriptorSetLayoutMap& DSetLayoutMap);` — Can be called only once, the idea is that the Layout remains fixed.
- L251 _public function_ `inline const TArray<VkDescriptorSetLayout>& GetHandles() const`
- L256 _public function_ `inline const TArray<uint32>& GetHandleIds() const`
- L261 _public function_ `inline const VkDescriptorSetAllocateInfo& GetAllocateInfo() const`
- L266 _public function_ `inline uint32 GetHash() const`
- L272 _private member_ `FVulkanDevice* Device;`
- L274 _private member_ `TArray<VkDescriptorSetLayout> LayoutHandles;` — uint32 Hash = 0;
- L275 _private member_ `TArray<uint32> LayoutHandleIds;`
- L276 _private member_ `VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo;`

#### class `FVulkanDescriptorPool`  
`class FVulkanDescriptorPool`  
_L279-322_
- L282 _public prototype_ `FVulkanDescriptorPool(FVulkanDevice* InDevice, const FVulkanDescriptorSetsLayout& Layout, uint32 MaxSetsAllocations);`
- L283 _public prototype_ `~FVulkanDescriptorPool();`
- L285 _public function_ `inline VkDescriptorPool GetHandle() const`
- L290 _public function_ `inline bool CanAllocate(const FVulkanDescriptorSetsLayout& InLayout) const`
- L295 _public prototype_ `void TrackAddUsage(const FVulkanDescriptorSetsLayout& InLayout);`
- L296 _public prototype_ `void TrackRemoveUsage(const FVulkanDescriptorSetsLayout& InLayout);`
- L298 _public function_ `inline bool IsEmpty() const`
- L303 _public prototype_ `void Reset();`
- L304 _public prototype_ `bool AllocateDescriptorSets(const VkDescriptorSetAllocateInfo& InDescriptorSetAllocateInfo, VkDescriptorSet* OutSets);`
- L305 _public function_ `inline uint32 GetNumAllocatedDescriptorSets() const`
- L311 _private member_ `FVulkanDevice* Device;`
- L313 _private member_ `uint32 MaxDescriptorSets;`
- L314 _private member_ `uint32 NumAllocatedDescriptorSets;`
- L315 _private member_ `uint32 PeakAllocatedDescriptorSets;`
- L318 _private member_ `const FVulkanDescriptorSetsLayout& Layout;` — Tracks number of allocated types, to ensure that we are not exceeding our allocated limit
- L319 _private member_ `VkDescriptorPool DescriptorPool;`

#### class `FVulkanTypedDescriptorPoolSet`  
`class FVulkanTypedDescriptorPoolSet`  
_L325-358_
- L327 _private typedef_ `typedef TList<FVulkanDescriptorPool*> FPoolList;`
- L329 _private prototype_ `FVulkanDescriptorPool* GetFreePool(bool bForceNewPool = false);`
- L330 _private prototype_ `FVulkanDescriptorPool* PushNewPool();`
- L336 _protected function_ `FVulkanTypedDescriptorPoolSet(FVulkanDevice* InDevice, const FVulkanDescriptorSetsLayout& InLayout) : Device(InDevice) , Layout(InLayout) , PoolsCount(0)`
- L344 _protected prototype_ `~FVulkanTypedDescriptorPoolSet();`
- L346 _protected prototype_ `void Reset();`
- L349 _public prototype_ `bool AllocateDescriptorSets(const FVulkanDescriptorSetsLayout& Layout, VkDescriptorSet* OutSets);`
- L352 _private member_ `FVulkanDevice* Device;`
- L353 _private member_ `const FVulkanDescriptorSetsLayout& Layout;`
- L354 _private member_ `uint32 PoolsCount;`
- L356 _private member_ `FPoolList* PoolListHead = nullptr;`
- L357 _private member_ `FPoolList* PoolListCurrent = nullptr;`

#### class `FVulkanDescriptorPoolSetContainer`  
`class FVulkanDescriptorPoolSetContainer`  
_L360-399_
- L363 _public function_ `FVulkanDescriptorPoolSetContainer(FVulkanDevice* InDevice) : Device(InDevice) , LastFrameUsed(GFrameNumberRenderThread) , bUsed(true)`
- L370 _public prototype_ `~FVulkanDescriptorPoolSetContainer();`
- L372 _public prototype_ `FVulkanTypedDescriptorPoolSet* AcquireTypedPoolSet(const FVulkanDescriptorSetsLayout& Layout);`
- L374 _public prototype_ `void Reset();`
- L376 _public function_ `inline void SetUsed(bool bInUsed)`
- L382 _public function_ `inline bool IsUnused() const`
- L387 _public function_ `inline uint32 GetLastFrameUsed() const`
- L393 _private member_ `FVulkanDevice* Device;`
- L395 _private member_ `TMap<uint32, FVulkanTypedDescriptorPoolSet*> TypedDescriptorPools;`
- L397 _private member_ `uint32 LastFrameUsed;`
- L398 _private member_ `bool bUsed;`

#### class `FVulkanDescriptorPoolsManager`  
`class FVulkanDescriptorPoolsManager`  
_L401-451_
- L434 _public prototype_ `~FVulkanDescriptorPoolsManager();`
- L436 _public function_ `void Init(FVulkanDevice* InDevice)`
- L441 _public prototype_ `FVulkanDescriptorPoolSetContainer& AcquirePoolSetContainer();`
- L442 _public prototype_ `void ReleasePoolSet(FVulkanDescriptorPoolSetContainer& PoolSet);`
- L443 _public prototype_ `void GC();`
- L446 _private member_ `FVulkanDevice* Device = nullptr;`
- L447 _private member_ `FAsyncTask<FVulkanAsyncPoolSetDeletionWorker>* AsyncDeletionTask = nullptr;`
- L449 _private member_ `FCriticalSection CS;`
- L450 _private member_ `TArray<FVulkanDescriptorPoolSetContainer*> PoolSets;`

#### class `FVulkanDescriptorPoolsManager::FVulkanAsyncPoolSetDeletionWorker`  
`class FVulkanAsyncPoolSetDeletionWorker : public FNonAbandonableTask`  
_L403-431_
- inherits: `FNonAbandonableTask`
- L405 _private member_ `FVulkanDescriptorPoolSetContainer* PoolSet;`
- L408 _public function_ `FVulkanAsyncPoolSetDeletionWorker(FVulkanDescriptorPoolSetContainer* InPoolSet) : PoolSet(InPoolSet)`
- L412 _public function_ `void DoWork()`
- L421 _public function_ `void SetPoolSet(FVulkanDescriptorPoolSetContainer* InPoolSet)`
- L427 _public function_ `FORCEINLINE TStatId GetStatId() const`

#### union `FVulkanHashableDescriptorInfo`  
`union FVulkanHashableDescriptorInfo`  
_L453-479_
- L460 _public member_ `} Layout;`
- L466 _public member_ `} Buffer;`
- L472 _public member_ `} Image;`
- L478 _public member_ `} BufferView;`

#### struct `FVulkanHashableDescriptorInfo::(anonymous)`  
``  
_L456-460_

#### struct `FVulkanHashableDescriptorInfo::(anonymous)`  
``  
_L462-466_

#### struct `FVulkanHashableDescriptorInfo::(anonymous)`  
``  
_L468-472_

#### struct `FVulkanHashableDescriptorInfo::(anonymous)`  
``  
_L474-478_

#### struct `FVulkanDescriptorSetWriteContainer`  
`struct FVulkanDescriptorSetWriteContainer`  
_L483-493_
- desc: This container holds the actual VkWriteDescriptorSet structures; a Compute pipeline uses the arrays 'as-is', whereas a Gfx PSO will have one big array and chunk it depending on the stage (eg Vertex, Pixel).
- L485 _public member_ `TArray<FVulkanHashableDescriptorInfo> HashableDescriptorInfo;`
- L486 _public member_ `TArray<VkDescriptorImageInfo> DescriptorImageInfo;`
- L487 _public member_ `TArray<VkDescriptorBufferInfo> DescriptorBufferInfo;`
- L488 _public member_ `TArray<VkWriteDescriptorSet> DescriptorWrites;`
- L489 _public member_ `TArray<VkAccelerationStructureKHR> AccelerationStructures;`
- L490 _public member_ `TArray<VkWriteDescriptorSetAccelerationStructureKHR> AccelerationStructureWrites;`
- L492 _public member_ `TArray<uint8> BindingToDynamicOffsetMap;`

#### class `FVulkanDescriptorSetWriter`  
`class FVulkanDescriptorSetWriter`  
_L498-839_
- desc: This class encapsulates updating VkWriteDescriptorSet structures (but doesn't own them), and their flags for dirty ranges; it is intended to be used to access a sub-region of a long array of VkWriteDescriptorSet (ie FVulkanDescriptorSetWriteContainer)
- L501 _public function_ `FVulkanDescriptorSetWriter() : WriteDescriptors(nullptr) , BindingToDynamicOffsetMap(nullptr) , DynamicOffsets(nullptr) , NumWrites(0) , HashableDescriptorInfos(nullptr) , bIsKeyDirty(true)`
- L511 _public function_ `const FVulkanDSetKey& GetKey() const`
- L522 _public function_ `const VkWriteDescriptorSet* GetWriteDescriptors() const`
- L527 _public function_ `const uint32 GetNumWrites() const`
- L532 _public prototype_ `bool WriteBindlessUniformBuffer(FVulkanDevice& Device, uint32 DescriptorIndex, const FVulkanUniformBuffer* UniformBuffer);`
- L534 _public function_ `bool WriteUniformBuffer(uint32 DescriptorIndex, VkBuffer BufferHandle, uint32 HandleId, VkDeviceSize Offset, VkDeviceSize Range)`
- L539 _public function_ `bool WriteDynamicUniformBuffer(uint32 DescriptorIndex, VkBuffer BufferHandle, uint32 HandleId, VkDeviceSize Offset, VkDeviceSize Range, uint32 DynamicOffset)`
- L544 _public function_ `bool WriteSampler(uint32 DescriptorIndex, const FVulkanSamplerState& Sampler)`
- L572 _public function_ `bool WriteImage(uint32 DescriptorIndex, const FVulkanView::FTextureView& TextureView, VkImageLayout Layout)`
- L577 _public function_ `bool WriteInputAttachment(uint32 DescriptorIndex, const FVulkanView::FTextureView& TextureView, VkImageLayout Layout)`
- L582 _public function_ `bool WriteStorageImage(uint32 DescriptorIndex, const FVulkanView::FTextureView& TextureView, VkImageLayout Layout)`
- L587 _public function_ `bool WriteStorageTexelBuffer(uint32 DescriptorIndex, const FVulkanView::FTypedBufferView& View)`
- L592 _public function_ `bool WriteStorageBuffer(uint32 DescriptorIndex, const FVulkanView::FStructuredBufferView& View)`
- L597 _public function_ `bool WriteUniformTexelBuffer(uint32 DescriptorIndex, const FVulkanView::FTypedBufferView& View)`
- L602 _public function_ `bool WriteAccelerationStructure(uint32 DescriptorIndex, VkAccelerationStructureKHR InAccelerationStructure)`
- L637 _public function_ `void SetDescriptorSet(VkDescriptorSet DescriptorSet)`
- L647 _protected function_ `template <VkDescriptorType DescriptorType> bool WriteBuffer(uint32 DescriptorIndex, VkBuffer BufferHandle, uint32 HandleId, VkDeviceSize Offset, VkDeviceSize Range, uint32 DynamicOffset = 0)`
- L707 _protected function_ `template <VkDescriptorType DescriptorType> bool WriteTextureView(uint32 DescriptorIndex, const FVulkanView::FTextureView& TextureView, VkImageLayout Layout)`
- L763 _protected function_ `template <VkDescriptorType DescriptorType> bool WriteBufferView(uint32 DescriptorIndex, const FVulkanView::FTypedBufferView& View)`
- L797 _protected member_ `VkWriteDescriptorSet* WriteDescriptors;` — A view into someone else's descriptors
- L800 _protected member_ `uint8* BindingToDynamicOffsetMap;` — A view into the mapping from binding index to dynamic uniform buffer offsets
- L803 _protected member_ `uint32* DynamicOffsets;` — A view into someone else's dynamic uniform buffer offsets
- L805 _protected member_ `uint32 NumWrites;`
- L808 _protected member_ `TArray<uint32> BindlessUBIndices;` — UB handles when running with bindless descriptor heaps
- L810 _protected member_ `FVulkanHashableDescriptorInfo* HashableDescriptorInfos;`
- L811 _protected member_ `mutable FVulkanDSetKey Key;`
- L812 _protected member_ `mutable bool bIsKeyDirty;`
- L813 _protected member_ `bool bHasVolatileResources = false;`
- L815 _protected prototype_ `uint32 SetupDescriptorWrites(const TArray<VkDescriptorType>& Types, FVulkanHashableDescriptorInfo* InHashableDescriptorInfos, VkWriteDescriptorSet* InWriteDescriptors, VkDescriptorImageInfo* InImageInfo, VkDescriptorBufferInfo* InBufferInfo, uint8* InBindingToDynamicOffsetMap, VkWriteDescriptorSetAccelerationStructureKHR* InAccelerationStructuresWriteDescriptors, VkAccelerationStructureKHR* InAccelerationStructures, const FVulkanSamplerState& DefaultSampler, const FVulkanView::FTextureView& DefaultImageView);`
- L829 _protected member_ `TArray<uint32, TInlineAllocator<2> > WrittenMask;`
- L830 _protected member_ `TArray<uint32, TInlineAllocator<2> > BaseWrittenMask;`
- L831 _protected member_ `TArray<uint32, TInlineAllocator<2> > ExcludedMask;`
- L833 _protected prototype_ `void CheckAllWritten();`
- L834 _protected prototype_ `void Reset();`
- L835 _protected prototype_ `void SetWritten(uint32 DescriptorIndex);`
- L836 _protected prototype_ `void SetWrittenBase(uint32 DescriptorIndex);`
- L837 _protected prototype_ `void InitWrittenMasks(uint32 NumDescriptorWrites);`
- L838 _protected prototype_ `void SetExcludedResources(const TArrayView<uint32> ExcludedResourceCount);`

#### class `FVulkanGenericDescriptorPool`  
`class FVulkanGenericDescriptorPool : FNoncopyable`  
_L842-867_
- inherits: `FNoncopyable`
- L845 _public prototype_ `FVulkanGenericDescriptorPool(FVulkanDevice* InDevice, uint32 InMaxDescriptorSets, const float PoolSizes[VK_DESCRIPTOR_TYPE_RANGE_SIZE]);`
- L846 _public prototype_ `~FVulkanGenericDescriptorPool();`
- L848 _public function_ `FVulkanDevice* GetDevice() const`
- L853 _public function_ `uint32 GetMaxDescriptorSets() const`
- L858 _public prototype_ `void Reset();`
- L859 _public prototype_ `bool AllocateDescriptorSet(VkDescriptorSetLayout Layout, VkDescriptorSet& OutSet);`
- L862 _private member_ `FVulkanDevice* const Device;`
- L863 _private member_ `const uint32 MaxDescriptorSets;`
- L864 _private member_ `VkDescriptorPool DescriptorPool;`
- L866 _private member_ `uint32 PoolSizes[VK_DESCRIPTOR_TYPE_RANGE_SIZE];` — information for debugging

#### class `FVulkanDescriptorSetCache`  
`class FVulkanDescriptorSetCache : FNoncopyable`  
_L869-930_
- inherits: `FNoncopyable`
- L872 _public prototype_ `FVulkanDescriptorSetCache(FVulkanDevice* InDevice);`
- L873 _public prototype_ `~FVulkanDescriptorSetCache();`
- L875 _public prototype_ `void GetDescriptorSets(const FVulkanDSetsKey& DSetsKey, const FVulkanDescriptorSetsLayout& SetsLayout, TArray<FVulkanDescriptorSetWriter>& DSWriters, VkDescriptorSet* OutSets);`
- L877 _public prototype_ `void GC();`
- L880 _private prototype_ `void UpdateAllocRatio();`
- L881 _private prototype_ `void AddCachedPool();`
- L926 _private member_ `FVulkanDevice* const Device;`
- L927 _private member_ `TArray<TUniquePtr<FCachedPool>> CachedPools;`
- L928 _private member_ `TUniquePtr<FCachedPool> FreePool;`
- L929 _private member_ `float PoolAllocRatio;`

#### struct `FVulkanDescriptorSetCache::FSetsEntry`  
`struct FSetsEntry`  
_L884-888_
- L886 _public member_ `TStaticArray<VkDescriptorSet, ShaderStage::MaxNumStages> Sets;`
- L887 _public member_ `int32 NumSets;`

#### class `FVulkanDescriptorSetCache::FCachedPool`  
`class FCachedPool : FNoncopyable`  
_L890-923_
- inherits: `FNoncopyable`
- L893 _public prototype_ `FCachedPool(FVulkanDevice* InDevice, uint32 InMaxDescriptorSets, const float PoolSizesRatio[VK_DESCRIPTOR_TYPE_RANGE_SIZE]);`
- L895 _public function_ `inline uint32 GetMaxDescriptorSets() const`
- L900 _public prototype_ `void Reset();`
- L901 _public prototype_ `bool CanGC() const;`
- L902 _public prototype_ `float CalcAllocRatio() const;`
- L904 _public prototype_ `bool FindDescriptorSets(const FVulkanDSetsKey& DSetsKey, VkDescriptorSet* OutSets);`
- L905 _public prototype_ `bool CreateDescriptorSets(const FVulkanDSetsKey& DSetsKey, const FVulkanDescriptorSetsLayout& SetsLayout, TArray<FVulkanDescriptorSetWriter>& DSWriters, VkDescriptorSet* OutSets);`
- L908 _public prototype_ `void CalcPoolSizesRatio(float PoolSizesRatio[VK_DESCRIPTOR_TYPE_RANGE_SIZE]);`
- L911 _private member_ `static const float MinAllocRatio;`
- L912 _private member_ `static const float MaxAllocRatio;`
- L915 _private member_ `const uint32 SetCapacity;`
- L916 _private member_ `FVulkanGenericDescriptorPool Pool;`
- L917 _private member_ `TMap<FVulkanDSetsKey, FSetsEntry> SetsCache;`
- L918 _private member_ `TMap<FVulkanDSetKey, VkDescriptorSet> SetCache;`
- L919 _private member_ `uint32 RecentFrame;`
- L922 _public member_ `uint32 PoolSizesStatistic[VK_DESCRIPTOR_TYPE_RANGE_SIZE];`

#### Free symbols / members of external scopes

- L13 _macro_ `#define VULKAN_VALIDATE_DESCRIPTORS_WRITTEN 0`
- L15 _macro_ `#define VULKAN_VALIDATE_DESCRIPTORS_WRITTEN RHI_INCLUDE_SHADER_DEBUG_DATA`
- L110 _function_ `friend uint32 GetTypeHash(const FVulkanDescriptorSetsLayoutInfo& In)`
- L239 _typedef_ `using FVulkanDescriptorSetLayoutMap = TMap<FVulkanDescriptorSetsLayoutInfo::FSetLayout, FVulkanDescriptorSetLayoutEntry>;`
- L457 _member_ `uint32 Max0;` (scope `FVulkanHashableDescriptorInfo::__anonc532d7db0108`)
- L458 _member_ `uint32 Max1;` (scope `FVulkanHashableDescriptorInfo::__anonc532d7db0108`)
- L459 _member_ `uint32 LayoutId;` (scope `FVulkanHashableDescriptorInfo::__anonc532d7db0108`)
- L463 _member_ `uint32 Id;` (scope `FVulkanHashableDescriptorInfo::__anonc532d7db0208`)
- L464 _member_ `uint32 Offset;` (scope `FVulkanHashableDescriptorInfo::__anonc532d7db0208`)
- L465 _member_ `uint32 Range;` (scope `FVulkanHashableDescriptorInfo::__anonc532d7db0208`)
- L469 _member_ `uint32 SamplerId;` (scope `FVulkanHashableDescriptorInfo::__anonc532d7db0308`)
- L470 _member_ `uint32 ImageViewId;` (scope `FVulkanHashableDescriptorInfo::__anonc532d7db0308`)
- L471 _member_ `uint32 ImageLayout;` (scope `FVulkanHashableDescriptorInfo::__anonc532d7db0308`)
- L475 _member_ `uint32 Id;` (scope `FVulkanHashableDescriptorInfo::__anonc532d7db0408`)
- L476 _member_ `uint32 Zero1;` (scope `FVulkanHashableDescriptorInfo::__anonc532d7db0408`)
- L477 _member_ `uint32 Zero2;` (scope `FVulkanHashableDescriptorInfo::__anonc532d7db0408`)

### `Source/Runtime/VulkanRHI/Private/VulkanDevice.h` (Private)


#### struct `FOptionalVulkanDeviceExtensions`  
`struct FOptionalVulkanDeviceExtensions`  
_L37-155_
- L125 _public function_ `FOptionalVulkanDeviceExtensions()`
- L131 _public function_ `bool HasGPUCrashDumpExtensions() const`
- L136 _public function_ `bool HasRaytracingExtensions() const`
- L148 _public function_ `bool HasAnyExtendedDynamicState() const`

#### union `FOptionalVulkanDeviceExtensions::(anonymous)`  
``  
_L40-123_

#### struct `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::(anonymous)`  
``  
_L42-121_

#### struct `FOptionalVulkanDeviceExtensionProperties`  
`struct FOptionalVulkanDeviceExtensionProperties`  
_L158-186_
- desc: All the features and properties we need to keep around from extension initialization
- L160 _public function_ `FOptionalVulkanDeviceExtensionProperties()`
- L165 _public member_ `VkPhysicalDeviceDriverPropertiesKHR PhysicalDeviceDriverProperties;`
- L166 _public member_ `VkPhysicalDeviceMaintenance7PropertiesKHR PhysicalDeviceMaintenance7Properties;`
- L168 _public member_ `VkPhysicalDeviceDescriptorBufferPropertiesEXT DescriptorBufferProps;`
- L169 _public member_ `VkPhysicalDeviceDescriptorHeapPropertiesEXT DescriptorHeapProps;`
- L170 _public member_ `VkPhysicalDeviceSubgroupSizeControlPropertiesEXT SubgroupSizeControlProperties;`
- L172 _public member_ `VkPhysicalDeviceAccelerationStructurePropertiesKHR AccelerationStructureProps;`
- L173 _public member_ `VkPhysicalDeviceRayTracingPipelinePropertiesKHR RayTracingPipelineProps;`
- L175 _public member_ `VkPhysicalDeviceFragmentShadingRateFeaturesKHR FragmentShadingRateFeatures;`
- L176 _public member_ `VkPhysicalDeviceFragmentDensityMapFeaturesEXT FragmentDensityMapFeatures;`
- L177 _public member_ `VkPhysicalDeviceFragmentDensityMap2FeaturesEXT FragmentDensityMap2Features;`
- L179 _public member_ `VkPhysicalDeviceFragmentShaderBarycentricPropertiesKHR FragmentShaderBarycentricProps;`
- L180 _public member_ `VkPhysicalDeviceComputeShaderDerivativesFeaturesKHR ComputeShaderDerivativesFeatures;`
- L181 _public member_ `VkPhysicalDeviceGraphicsPipelineLibraryPropertiesEXT GraphicsPipelineLibraryProperties;`
- L183 _public member_ `VkPhysicalDeviceMeshShaderPropertiesEXT MeshShaderProperties;`
- L185 _public member_ `VkPhysicalDeviceDeviceGeneratedCommandsPropertiesEXT DeviceGeneratedCommandsProperties;`

#### class `FVulkanPhysicalDeviceFeatures`  
`class FVulkanPhysicalDeviceFeatures`  
_L188-208_
- L191 _public function_ `FVulkanPhysicalDeviceFeatures()`
- L196 _public prototype_ `void Query(VkPhysicalDevice PhysicalDevice, uint32 APIVersion);`
- L198 _public member_ `VkPhysicalDeviceFeatures Core_1_0;`
- L199 _public member_ `VkPhysicalDeviceVulkan11Features Core_1_1;`
- L202 _private member_ `VkPhysicalDeviceVulkan12Features Core_1_2;` — Anything above Core 1.1 cannot be assumed, they should only be used by the device at init time
- L203 _private member_ `VkPhysicalDeviceVulkan13Features Core_1_3;`
- L204 _private member_ `VkPhysicalDeviceVulkan14Features Core_1_4;`

#### class `VulkanRHI::FDeferredDeletionQueue2`  
`class FDeferredDeletionQueue2`  
_L213-288_
- L217 _public prototype_ `FDeferredDeletionQueue2(FVulkanDevice& InDevice);`
- L218 _public prototype_ `~FDeferredDeletionQueue2();`
- L244 _public function_ `template <typename T> inline void EnqueueResource(EType Type, T Handle)`
- L250 _public function_ `inline void EnqueueBindlessHandle(FRHIDescriptorHandle DescriptorHandle)`
- L259 _public prototype_ `void EnqueueFunc(TUniqueFunction<void(class FVulkanDevice&)>&& Func);`
- L260 _public prototype_ `void EnqueueResourceAllocation(FVulkanAllocation& Allocation);`
- L261 _public prototype_ `void EnqueueDeviceAllocation(FDeviceMemoryAllocation* DeviceMemoryAllocation);`
- L263 _public prototype_ `void ReleaseResources(bool bDeleteImmediately = false);`
- L265 _public function_ `inline void Clear()`
- L271 _private prototype_ `void EnqueueGenericResource(EType Type, uint64 Handle);`
- L283 _private prototype_ `void ReleaseResourcesImmediately(const TArray<FEntry>& InEntries);`
- L285 _private member_ `FVulkanDevice& Device;`
- L286 _private member_ `FCriticalSection CS;`
- L287 _private member_ `TArray<FEntry> Entries;`

#### enum `VulkanRHI::FDeferredDeletionQueue2::EType`  
`enum class EType`  
_L220-241_
- L222 _public enumerator_ `RenderPass`
- L223 _public enumerator_ `Buffer`
- L224 _public enumerator_ `BufferView`
- L225 _public enumerator_ `Image`
- L226 _public enumerator_ `ImageView`
- L227 _public enumerator_ `Pipeline`
- L228 _public enumerator_ `PipelineLayout`
- L229 _public enumerator_ `Framebuffer`
- L230 _public enumerator_ `DescriptorSetLayout`
- L231 _public enumerator_ `Sampler`
- L232 _public enumerator_ `Semaphore`
- L233 _public enumerator_ `ShaderModule`
- L234 _public enumerator_ `Event`
- L235 _public enumerator_ `ResourceAllocation`
- L236 _public enumerator_ `DeviceMemoryAllocation`
- L237 _public enumerator_ `BufferSuballocation`
- L238 _public enumerator_ `AccelerationStructure`
- L239 _public enumerator_ `BindlessHandle`
- L240 _public enumerator_ `Func`

#### struct `VulkanRHI::FDeferredDeletionQueue2::FEntry`  
`struct FEntry`  
_L273-281_
- L275 _public member_ `EType StructureType;`
- L276 _public member_ `uint32 FrameNumber;`
- L277 _public member_ `uint64 Handle = 0;`
- L278 _public member_ `FVulkanAllocation Allocation;`
- L279 _public member_ `FDeviceMemoryAllocation* DeviceMemoryAllocation = nullptr;`
- L280 _public member_ `TUniqueFunction<void(class FVulkanDevice&)>* Func = nullptr;`

#### class `FVulkanDevice`  
`class FVulkanDevice`  
_L292-760_
- L295 _public prototype_ `FVulkanDevice(FVulkanDynamicRHI* InRHI, VkPhysicalDevice Gpu);`
- L297 _public prototype_ `~FVulkanDevice();`
- L299 _public prototype_ `void InitGPU();`
- L301 _public prototype_ `void CreateDevice(TArray<const ANSICHAR*>& DeviceLayers, FVulkanDeviceExtensionArray& UEExtensions);`
- L302 _public prototype_ `void ChooseVariableRateShadingMethod();`
- L304 _public prototype_ `void PrepareForDestroy();`
- L305 _public prototype_ `void Destroy();`
- L307 _public prototype_ `void WaitUntilIdle();`
- L309 _public function_ `EGpuVendorId GetVendorId() const`
- L314 _public function_ `bool HasAsyncComputeQueue() const`
- L319 _public function_ `bool HasTransferQueue() const`
- L324 _public function_ `bool HasMultipleQueues() const`
- L329 _public function_ `bool CanPresentOnComputeQueue() const`
- L334 _public function_ `FVulkanQueue* GetQueue(ERHIPipeline Pipeline)`
- L348 _public function_ `FVulkanQueue* GetQueue(EVulkanQueueType QueueType)`
- L353 _public function_ `FVulkanQueue* GetGraphicsQueue()`
- L358 _public function_ `FVulkanQueue* GetComputeQueue()`
- L363 _public function_ `FVulkanQueue* GetTransferQueue()`
- L368 _public function_ `FVulkanQueue* GetPresentQueue()`
- L373 _public prototype_ `void ForEachQueue(TFunctionRef<void(FVulkanQueue&)> Callback);`
- L375 _public function_ `VkPhysicalDevice GetPhysicalHandle() const`
- L380 _public function_ `const VkPhysicalDeviceProperties& GetDeviceProperties() const`
- L385 _public function_ `VkExtent2D GetBestMatchedFragmentSize(EVRSShadingRate Rate) const`
- L390 _public function_ `const VkPhysicalDeviceLimits& GetLimits() const`
- L395 _public function_ `const VkPhysicalDeviceIDPropertiesKHR& GetDeviceIdProperties() const`
- L400 _public function_ `const VkPhysicalDeviceSubgroupProperties& GetDeviceSubgroupProperties() const`
- L405 _public function_ `FVulkanRayTracingCompactionRequestHandler* GetRayTracingCompactionRequestHandler()`
- L410 _public function_ `FVulkanRayTracingPipelineLibraryCache* GetRayTracingPipelineLibraryCache()`
- L415 _public prototype_ `void InitializeRayTracing();`
- L416 _public prototype_ `void CleanUpRayTracing();`
- L419 _public function_ `VkValidationCacheEXT GetValidationCache() const`
- L425 _public function_ `const FVulkanPhysicalDeviceFeatures& GetPhysicalDeviceFeatures() const`
- L430 _public function_ `bool HasUnifiedMemory() const`
- L435 _public prototype_ `bool SupportsBindless() const;`
- L437 _public prototype_ `const VkComponentMapping& GetFormatComponentMapping(EPixelFormat UEFormat) const;`
- L439 _public function_ `VkDevice GetHandle() const`
- L444 _public function_ `const FVulkanSamplerState& GetDefaultSampler() const`
- L449 _public prototype_ `const VkFormatProperties& GetFormatProperties(VkFormat InFormat) const;`
- L451 _public function_ `VulkanRHI::FDeviceMemoryManager& GetDeviceMemoryManager()`
- L456 _public function_ `const VkPhysicalDeviceMemoryProperties& GetDeviceMemoryProperties() const`
- L461 _public function_ `VulkanRHI::FMemoryManager& GetMemoryManager()`
- L466 _public function_ `VulkanRHI::FDeferredDeletionQueue2& GetDeferredDeletionQueue()`
- L471 _public function_ `VulkanRHI::FStagingManager& GetStagingManager()`
- L476 _public function_ `FVulkanFenceManager& GetFenceManager()`
- L481 _public function_ `VulkanRHI::FTempBlockAllocator& GetTempBlockAllocator()`
- L486 _public function_ `FVulkanRenderPassManager& GetRenderPassManager()`
- L491 _public function_ `FVulkanDescriptorSetCache& GetDescriptorSetCache()`
- L496 _public function_ `FVulkanDescriptorPoolsManager& GetDescriptorPoolsManager()`
- L501 _public function_ `FVulkanBindlessDescriptorManager* GetBindlessDescriptorManager()`
- L506 _public function_ `TMap<uint32, TRefCountPtr<FVulkanSamplerState>>& GetSamplerMap()`
- L511 _public function_ `FVulkanShaderFactory& GetShaderFactory()`
- L516 _public function_ `FVulkanCommandListContext& GetImmediateContext()`
- L521 _public prototype_ `void NotifyDeletedImage(VkImage Image, bool bRenderTarget);`
- L524 _public function_ `inline PFN_vkCmdInsertDebugUtilsLabelEXT GetCmdInsertDebugLabel() const`
- L529 _public function_ `PFN_vkCmdBeginDebugUtilsLabelEXT GetCmdBeginDebugLabel() const`
- L534 _public function_ `PFN_vkCmdEndDebugUtilsLabelEXT GetCmdEndDebugLabel() const`
- L539 _public function_ `PFN_vkSetDebugUtilsObjectNameEXT GetSetDebugName() const`
- L545 _public prototype_ `FVulkanQueryPool* AcquireOcclusionQueryPool(uint32 NumQueries);`
- L546 _public prototype_ `FVulkanQueryPool* AcquireTimingQueryPool();`
- L547 _public prototype_ `void ReleaseQueryPool(FVulkanQueryPool* Pool);`
- L548 _public prototype_ `void RemoveStaleQueryPools();`
- L550 _public function_ `class FVulkanPipelineStateCacheManager* GetPipelineStateCache()`
- L555 _public prototype_ `void NotifyDeletedGfxPipeline(class FVulkanGraphicsPipelineState* Pipeline);`
- L556 _public prototype_ `void NotifyDeletedComputePipeline(class FVulkanComputePipeline* Pipeline);`
- L558 _public prototype_ `void VulkanSetObjectName(VkObjectType Type, uint64_t Handle, const TCHAR* Name);`
- L559 _public function_ `const FOptionalVulkanDeviceExtensions& GetOptionalExtensions() const`
- L564 _public function_ `const FOptionalVulkanDeviceExtensionProperties& GetOptionalExtensionProperties() const`
- L569 _public function_ `bool NeedsAllPlanes() const`
- L574 _public function_ `bool SupportsParallelRendering() const`
- L579 _public function_ `bool SupportsGraphicPipelineLibraries() const`
- L595 _public function_ `FVulkanShaderObjectManager* GetShaderObjectManager()`
- L600 _public function_ `bool SupportsShaderObjects() const`
- L610 _public prototype_ `void SetupPresentQueue(VkSurfaceKHR Surface);`
- L612 _public function_ `const TArray<VkQueueFamilyProperties>& GetQueueFamilyProps()`
- L617 _public function_ `bool NeedsQueueFamilyOwnershipTransfers() const`
- L622 _public prototype_ `FVulkanTransientHeapCache& GetOrCreateTransientHeapCache();`
- L624 _public function_ `const TArray<const ANSICHAR*>& GetDeviceExtensions()`
- L626 _public prototype_ `void GetCalibrationTimestamp(FVulkanTiming& InOutTiming);`
- L628 _public function_ `const FVulkanSamplerState& GetGlobalSamplers(FVulkanShaderHeader::EGlobalSamplerType Type) const`
- L633 _public prototype_ `VkEvent GetBarrierEvent();`
- L634 _public prototype_ `void ReleaseBarrierEvent(VkEvent Handle);`
- L636 _public prototype_ `VkBuffer CreateBuffer(VkDeviceSize BufferSize, VkBufferUsageFlags BufferUsageFlags, VkBufferCreateFlags BufferCreateFlags=0) const;`
- L638 _public function_ `const TArray<uint32>& GetActiveQueueFamilies() const`
- L643 _public prototype_ `bool UseMinimalSubmits() const;`
- L645 _public prototype_ `bool SupportsDeviceLocalHostVisible() const;`
- L648 _private prototype_ `void MapBufferFormatSupport(FPixelFormatInfo& PixelFormatInfo, EPixelFormat UEFormat, VkFormat VulkanFormat);`
- L649 _private prototype_ `void MapImageFormatSupport(FPixelFormatInfo& PixelFormatInfo, const TArrayView<const VkFormat>& PrioritizedFormats, EPixelFormatCapabilities RequiredCapabilities);`
- L650 _private prototype_ `void MapFormatSupport(EPixelFormat UEFormat, std::initializer_list<VkFormat> PrioritizedFormats, const VkComponentMapping& ComponentMapping, EPixelFormatCapabilities RequiredCapabilities, int32 BlockBytes);`
- L651 _private prototype_ `void MapFormatSupport(EPixelFormat UEFormat, std::initializer_list<VkFormat> PrioritizedFormats, const VkComponentMapping& ComponentMapping);`
- L652 _private prototype_ `void MapFormatSupport(EPixelFormat UEFormat, std::initializer_list<VkFormat> PrioritizedFormats, const VkComponentMapping& ComponentMapping, int32 BlockBytes);`
- L653 _private prototype_ `void MapFormatSupport(EPixelFormat UEFormat, std::initializer_list<VkFormat> PrioritizedFormats, const VkComponentMapping& ComponentMapping, EPixelFormatCapabilities RequiredCapabilities);`
- L655 _private prototype_ `void InitGlobalSamplers();`
- L656 _private member_ `TStaticArray<FVulkanSamplerState*, (uint32)FVulkanShaderHeader::EGlobalSamplerType::Count> GlobalSamplers;`
- L658 _private member_ `VkDevice Device;`
- L660 _private member_ `VulkanRHI::FDeviceMemoryManager DeviceMemoryManager;`
- L662 _private member_ `VulkanRHI::FMemoryManager MemoryManager;`
- L664 _private member_ `VulkanRHI::FDeferredDeletionQueue2 DeferredDeletionQueue;`
- L666 _private member_ `VulkanRHI::FStagingManager StagingManager;`
- L668 _private member_ `FVulkanFenceManager FenceManager;`
- L670 _private member_ `VulkanRHI::FTempBlockAllocator* TempBlockAllocator = nullptr;`
- L672 _private member_ `FVulkanRenderPassManager* RenderPassManager;`
- L674 _private member_ `FVulkanTransientHeapCache* TransientHeapCache = nullptr;`
- L677 _private member_ `FVulkanDescriptorSetCache* DescriptorSetCache = nullptr;` — Active on ES3.1
- L679 _private member_ `FVulkanDescriptorPoolsManager* DescriptorPoolsManager = nullptr;` — Active on >= SM4
- L681 _private member_ `FVulkanBindlessDescriptorManager* BindlessDescriptorManager = nullptr;`
- L683 _private member_ `FVulkanShaderFactory ShaderFactory;`
- L684 _private member_ `FVulkanShaderObjectManager* ShaderObjectManager = nullptr;`
- L686 _private member_ `VkPhysicalDevice Gpu;`
- L687 _private member_ `VkPhysicalDeviceProperties GpuProps;`
- L689 _private member_ `TArray<VkPhysicalDeviceFragmentShadingRateKHR> FragmentShadingRates;`
- L690 _private member_ `TStaticArray<VkExtent2D, (EVRSShadingRate::VRSSR_Last+1)> FragmentSizeMap;`
- L693 _private member_ `VkPhysicalDeviceIDPropertiesKHR GpuIdProps;` — Extension specific properties
- L694 _private member_ `VkPhysicalDeviceSubgroupProperties GpuSubgroupProps;`
- L696 _private member_ `FVulkanRayTracingCompactionRequestHandler* RayTracingCompactionRequestHandler = nullptr;`
- L697 _private member_ `FVulkanRayTracingPipelineLibraryCache* RayTracingPipelineLibraryCache = nullptr;`
- L699 _private member_ `FVulkanPhysicalDeviceFeatures PhysicalDeviceFeatures;`
- L701 _private member_ `TArray<VkQueueFamilyProperties> QueueFamilyProps;`
- L702 _private member_ `bool bNeedsQueueFamilyOwnershipTransfers = true;`
- L704 _private member_ `VkFormatProperties FormatProperties[VK_FORMAT_RANGE_SIZE];`
- L706 _private member_ `mutable TMap<VkFormat, VkFormatProperties> ExtensionFormatProperties;` — Info for formats that are not in the core Vulkan spec (i.e. extensions)
- L709 _private member_ `FCriticalSection QueryPoolLock;` — Reusable query pools
- L710 _private member_ `uint32 OcclusionQueryPoolSize = 256;`
- L711 _private member_ `TStaticArray<TArray<FVulkanQueryPool*>, (int32)EVulkanQueryPoolType::Count> FreeQueryPools;`
- L714 _private member_ `FCriticalSection BarrierEventLock;` — Reusable gpu-only barrier events
- L715 _private member_ `TArray<VkEvent> BarrierEvents;`
- L717 _private member_ `TStaticArray<FVulkanQueue*, (int32)EVulkanQueueType::Count> Queues;`
- L718 _private member_ `FVulkanQueue* PresentQueue = nullptr;` — points to an existing queue
- L719 _private member_ `bool bPresentOnComputeQueue = false;`
- L720 _private member_ `TArray<uint32> ActiveQueueFamilies;`
- L722 _private member_ `EGpuVendorId VendorId = EGpuVendorId::NotQueried;`
- L724 _private member_ `VkComponentMapping PixelFormatComponentMapping[PF_MAX];`
- L726 _private member_ `TMap<uint32, TRefCountPtr<FVulkanSamplerState>> SamplerMap;`
- L728 _private member_ `FVulkanCommandListContext* ImmediateContext;`
- L730 _private member_ `FVulkanDynamicRHI* RHI = nullptr;`
- L732 _private prototype_ `TArray<const ANSICHAR*> SetupDeviceLayers(FVulkanDeviceExtensionArray& UEExtensions);`
- L734 _private member_ `FOptionalVulkanDeviceExtensions OptionalDeviceExtensions;`
- L735 _private member_ `FOptionalVulkanDeviceExtensionProperties OptionalDeviceExtensionProperties;`
- L736 _private member_ `TArray<const ANSICHAR*> DeviceExtensions;`
- L738 _private prototype_ `void SetupFormats();`
- L741 _private member_ `VkValidationCacheEXT ValidationCache = VK_NULL_HANDLE;`
- L745 _private member_ `bool bUseLegacyDebugMarkerExt = false;`
- L752 _private member_ `} DebugMarkers;`
- L755 _private prototype_ `void SetupDrawMarkers();`
- L757 _private member_ `class FVulkanPipelineStateCacheManager* PipelineStateCache;`

#### struct `FVulkanDevice::(anonymous)`  
``  
_L747-752_

#### Free symbols / members of external scopes

- L32 _macro_ `#define VULKAN_SET_DEBUG_NAME(Device, Type, Handle, Format, ...) (Device).VulkanSetObjectName(Type, (uint64)Handle, *FString::Printf(Format, __VA_ARGS__))`
- L34 _macro_ `#define VULKAN_SET_DEBUG_NAME(Device, Type, Handle, Format, ...) do{}while(0)`
- L44 _member_ `uint64 HasEXTValidationCache : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`) — Optional Extensions
- L45 _member_ `uint64 HasMemoryPriority : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L46 _member_ `uint64 HasMemoryBudget : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L47 _member_ `uint64 HasEXTASTCDecodeMode : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L48 _member_ `uint64 HasEXTFragmentDensityMap : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L49 _member_ `uint64 HasEXTFragmentDensityMap2 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L50 _member_ `uint64 HasEXTFragmentDensityMapOffset : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L51 _member_ `uint64 HasKHRFragmentShadingRate : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L52 _member_ `uint64 HasKHRFragmentShaderBarycentric : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L53 _member_ `uint64 HasEXTFullscreenExclusive : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L54 _member_ `uint64 HasImageAtomicInt64 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L55 _member_ `uint64 HasAccelerationStructure : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L56 _member_ `uint64 HasRayTracingPipeline : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L57 _member_ `uint64 HasRayQuery : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L58 _member_ `uint64 HasKHRPipelineLibrary : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L59 _member_ `uint64 HasDeferredHostOperations : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L60 _member_ `uint64 HasEXTCalibratedTimestamps : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L61 _member_ `uint64 HasEXTDescriptorBuffer : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L62 _member_ `uint64 HasEXTDescriptorHeap : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L63 _member_ `uint64 HasEXTDeviceFault : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L64 _member_ `uint64 HasEXTMeshShader : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L65 _member_ `uint64 HasEXTToolingInfo : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L66 _member_ `uint64 HasEXTImageCompressionControl : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L67 _member_ `uint64 HasEXTMutableDescriptorType : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L68 _member_ `uint64 HasKHRMaintenance7 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L69 _member_ `uint64 HasKHRMaintenance9 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L70 _member_ `uint64 HasEXTShaderObject : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L71 _member_ `uint64 HasEXTGraphicsPipelineLibrary : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L72 _member_ `uint64 HasEXTDeviceGeneratedCommands : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L73 _member_ `uint64 HasEXTDeviceAddressBindingReport : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L76 _member_ `uint64 HasAMDBufferMarker : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`) — Vendor specific
- L77 _member_ `uint64 HasNVDiagnosticCheckpoints : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L78 _member_ `uint64 HasNVDeviceDiagnosticConfig : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L79 _member_ `uint64 HasANDROIDExternalMemoryHardwareBuffer : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L82 _member_ `uint64 HasKHRMultiview : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`) — Promoted to 1.1
- L83 _member_ `uint64 HasKHR16bitStorage : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L84 _member_ `uint64 HasKHRSamplerYcbcrConversion : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L87 _member_ `uint64 HasKHRRenderPass2 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`) — Promoted to 1.2
- L88 _member_ `uint64 HasKHRImageFormatList : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L89 _member_ `uint64 HasKHRShaderAtomicInt64 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L90 _member_ `uint64 HasEXTScalarBlockLayout : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L91 _member_ `uint64 HasBufferDeviceAddress : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L92 _member_ `uint64 HasSPIRV_14 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L93 _member_ `uint64 HasShaderFloatControls : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L94 _member_ `uint64 HasKHRShaderFloat16 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L95 _member_ `uint64 HasEXTDescriptorIndexing : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L96 _member_ `uint64 HasSeparateDepthStencilLayouts : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L97 _member_ `uint64 HasEXTHostQueryReset : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L98 _member_ `uint64 HasQcomRenderPassShaderResolve : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L99 _member_ `uint64 HasKHRDepthStencilResolve : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L100 _member_ `uint64 HasKHRTimelineSemaphore : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L103 _member_ `uint64 HasEXTTextureCompressionASTCHDR : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`) — Promoted to 1.3
- L104 _member_ `uint64 HasKHRMaintenance4 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L105 _member_ `uint64 HasKHRSynchronization2 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L106 _member_ `uint64 HasKHRDynamicRendering : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L107 _member_ `uint64 HasEXTSubgroupSizeControl : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L108 _member_ `uint64 HasEXTPipelineCreationCacheControl : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L109 _member_ `uint64 HasEXTExtendedDynamicState1 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L110 _member_ `uint64 HasEXTExtendedDynamicState2 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L111 _member_ `uint64 HasEXTExtendedDynamicState3 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L112 _member_ `uint64 HasEXTVertexInputDynamicState : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L113 _member_ `uint64 HasEXTImageRobustness : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L116 _member_ `uint64 HasKHRMaintenance5 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`) — Promoted to 1.4
- L117 _member_ `uint64 HasKHRMaintenance6 : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L118 _member_ `uint64 HasKHRPushDescriptors : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L119 _member_ `uint64 HasEXTLoadStoreOpNone : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L120 _member_ `uint64 HasEXTHostImageCopy : 1;` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a::__anon97f3de6d0208`)
- L122 _member_ `uint64 Packed[2];` (scope `FOptionalVulkanDeviceExtensions::__anon97f3de6d010a`)
- L211 _namespace_ `namespace VulkanRHI`
- L748 _member_ `PFN_vkSetDebugUtilsObjectNameEXT SetDebugName = nullptr;` (scope `FVulkanDevice::__anon97f3de6d0308`)
- L749 _member_ `PFN_vkCmdInsertDebugUtilsLabelEXT CmdInsertLabel = nullptr;` (scope `FVulkanDevice::__anon97f3de6d0308`)
- L750 _member_ `PFN_vkCmdBeginDebugUtilsLabelEXT CmdBeginDebugLabel = nullptr;` (scope `FVulkanDevice::__anon97f3de6d0308`)
- L751 _member_ `PFN_vkCmdEndDebugUtilsLabelEXT CmdEndDebugLabel = nullptr;` (scope `FVulkanDevice::__anon97f3de6d0308`)

### `Source/Runtime/VulkanRHI/Private/VulkanDynamicRHI.h` (Private)


#### struct `FOptionalVulkanInstanceExtensions`  
`struct FOptionalVulkanInstanceExtensions`  
_L26-46_
- L41 _public function_ `FOptionalVulkanInstanceExtensions()`

#### union `FOptionalVulkanInstanceExtensions::(anonymous)`  
``  
_L29-39_

#### struct `FOptionalVulkanInstanceExtensions::__anona224af25010a::(anonymous)`  
``  
_L31-37_

#### class `FVulkanTiming`  
`class FVulkanTiming`  
_L49-61_
- desc: Encapsulates the state required for tracking GPU queue performance across a frame.
- L52 _public prototype_ `FVulkanTiming(FVulkanQueue& InQueue);`
- L54 _public member_ `FVulkanQueue& Queue;`
- L57 _public member_ `uint64 GPUFrequency = 0, GPUTimestamp = 0;` — Timer calibration data
- L57 _public member_ `uint64 GPUFrequency = 0, GPUTimestamp = 0;` — Timer calibration data
- L58 _public member_ `uint64 CPUFrequency = 0, CPUTimestamp = 0;`
- L58 _public member_ `uint64 CPUFrequency = 0, CPUTimestamp = 0;`
- L60 _public member_ `UE::RHI::GPUProfiler::FEventStream EventStream;`

#### class `FVulkanDynamicRHI`  
`class FVulkanDynamicRHI : public IVulkanDynamicRHI`  
_L66-464_
- inherits: `IVulkanDynamicRHI`
- desc: The interface which is implemented by the dynamically bound RHI.
- L70 _public function_ `static FVulkanDynamicRHI& Get()`
- L73 _public prototype_ `FVulkanDynamicRHI();` — Initialization constructor.
- L76 _public prototype_ `~FVulkanDynamicRHI();` — Destructor
- L79 _public prototype_ `virtual uint32 RHIGetVulkanVersion() const final override;` — IVulkanDynamicRHI interface
- L80 _public prototype_ `virtual VkInstance RHIGetVkInstance() const final override;`
- L81 _public prototype_ `virtual VkDevice RHIGetVkDevice() const final override;`
- L82 _public prototype_ `virtual const uint8* RHIGetVulkanDeviceUUID() const final override;`
- L83 _public prototype_ `virtual VkPhysicalDevice RHIGetVkPhysicalDevice() const final override;`
- L84 _public prototype_ `virtual const VkAllocationCallbacks* RHIGetVkAllocationCallbacks() final override;`
- L85 _public prototype_ `virtual IVulkanMemoryAllocator* RHIGetVulkanMemoryAllocator() final override;`
- L86 _public prototype_ `virtual VkQueue RHIGetGraphicsVkQueue() const final override;`
- L87 _public prototype_ `virtual uint32 RHIGetGraphicsQueueIndex() const final override;`
- L88 _public prototype_ `virtual uint32 RHIGetGraphicsQueueFamilyIndex() const final override;`
- L89 _public prototype_ `virtual VkCommandBuffer RHIGetVkCommandBuffer(FRHICommandListBase& ExecutingCmdList) const final override;`
- L90 _public prototype_ `virtual uint64 RHIGetGraphicsAdapterLUID(VkPhysicalDevice InPhysicalDevice) const final override;`
- L91 _public prototype_ `virtual bool RHIDoesAdapterMatchDevice(const void* InAdapterId) const final override;`
- L92 _public prototype_ `virtual void* RHIGetVkDeviceProcAddr(const char* InName) const final override;`
- L93 _public prototype_ `virtual void* RHIGetVkInstanceProcAddr(const char* InName) const final override;`
- L94 _public prototype_ `virtual void* RHIGetVkInstanceGlobalProcAddr(const char* InName) const final override;`
- L95 _public prototype_ `virtual VkFormat RHIGetSwapChainVkFormat(EPixelFormat InFormat) const final override;`
- L96 _public prototype_ `virtual bool RHISupportsEXTFragmentDensityMap2() const final override;`
- L97 _public prototype_ `virtual TArray<VkExtensionProperties> RHIGetAllInstanceExtensions() const final override;`
- L98 _public prototype_ `virtual TArray<VkExtensionProperties> RHIGetAllDeviceExtensions(VkPhysicalDevice InPhysicalDevice) const final override;`
- L99 _public prototype_ `virtual TArray<FAnsiString> RHIGetLoadedDeviceExtensions() const final override;`
- L100 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromResource(EPixelFormat Format, uint32 SizeX, uint32 SizeY, uint32 NumMips, uint32 NumSamples, VkImage Resource, ETextureCreateFlags Flags, const FClearValueBinding& ClearValueBinding = FClearValueBinding::Transparent, const FVulkanRHIExternalImageDeleteCallbackInfo& ExternalImageDeleteCallbackInfo = {}) final override;`
- L102 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromAndroidHardwareBuffer(AHardwareBuffer* HardwareBuffer) final override;`
- L104 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DArrayFromResource(EPixelFormat Format, uint32 SizeX, uint32 SizeY, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, VkImage Resource, ETextureCreateFlags Flags, const FClearValueBinding& ClearValueBinding = FClearValueBinding::Transparent) final override;`
- L105 _public prototype_ `virtual FTextureRHIRef RHICreateTextureCubeFromResource(EPixelFormat Format, uint32 Size, bool bArray, uint32 ArraySize, uint32 NumMips, VkImage Resource, ETextureCreateFlags Flags, const FClearValueBinding& ClearValueBinding = FClearValueBinding::Transparent) final override;`
- L106 _public prototype_ `virtual VkImage RHIGetVkImage(FRHITexture* InTexture) const final override;`
- L107 _public prototype_ `virtual VkFormat RHIGetViewVkFormat(FRHITexture* InTexture) const final override;`
- L108 _public prototype_ `virtual FVulkanRHIAllocationInfo RHIGetAllocationInfo(FRHITexture* InTexture) const final override;`
- L109 _public prototype_ `virtual FVulkanRHIImageViewInfo RHIGetImageViewInfo(FRHITexture* InTexture) const final override;`
- L110 _public prototype_ `virtual FVulkanRHIAllocationInfo RHIGetAllocationInfo(FRHIBuffer* InBuffer) const final override;`
- L111 _public prototype_ `virtual void RHIFinishExternalComputeWork(VkCommandBuffer InCommandBuffer) final override;`
- L112 _public prototype_ `virtual void RHIVerifyResult(VkResult Result, const ANSICHAR* VkFuntion, const ANSICHAR* Filename, uint32 Line) final override;`
- L115 _public prototype_ `virtual void Init() final override;` — FDynamicRHI interface.
- L116 _public prototype_ `virtual void PostInit() final override;`
- L117 _public prototype_ `virtual void Shutdown() final override;`
- L118 _public function_ `virtual const TCHAR* GetName() final override`
- L120 _public prototype_ `void InitInstance();`
- L122 _public prototype_ `virtual void RHIEndFrame_RenderThread(FRHICommandListImmediate& RHICmdList) final override;`
- L123 _public prototype_ `virtual void RHIEndFrame(const FRHIEndFrameArgs& Args) final override;`
- L125 _public prototype_ `virtual FSamplerStateRHIRef RHICreateSamplerState(const FSamplerStateInitializerRHI& Initializer) final override;`
- L126 _public prototype_ `virtual FRasterizerStateRHIRef RHICreateRasterizerState(const FRasterizerStateInitializerRHI& Initializer) final override;`
- L127 _public prototype_ `virtual FDepthStencilStateRHIRef RHICreateDepthStencilState(const FDepthStencilStateInitializerRHI& Initializer) final override;`
- L128 _public prototype_ `virtual FBlendStateRHIRef RHICreateBlendState(const FBlendStateInitializerRHI& Initializer) final override;`
- L129 _public prototype_ `virtual FVertexDeclarationRHIRef RHICreateVertexDeclaration(const FVertexDeclarationElementList& Elements) final override;`
- L130 _public prototype_ `virtual FPixelShaderRHIRef RHICreatePixelShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L131 _public prototype_ `virtual FVertexShaderRHIRef RHICreateVertexShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L132 _public prototype_ `virtual FMeshShaderRHIRef RHICreateMeshShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L133 _public prototype_ `virtual FAmplificationShaderRHIRef RHICreateAmplificationShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L134 _public prototype_ `virtual FGeometryShaderRHIRef RHICreateGeometryShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L135 _public prototype_ `virtual FComputeShaderRHIRef RHICreateComputeShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L136 _public prototype_ `virtual FGPUFenceRHIRef RHICreateGPUFence(const FName &Name) final override;`
- L137 _public prototype_ `virtual void RHIWriteGPUFence_TopOfPipe(FRHICommandListBase& RHICmdList, FRHIGPUFence* FenceRHI) final override;`
- L138 _public prototype_ `virtual void RHICreateTransition(FRHITransition* Transition, const FRHITransitionCreateInfo& CreateInfo) final override;`
- L139 _public prototype_ `virtual void RHIReleaseTransition(FRHITransition* Transition) final override;`
- L140 _public prototype_ `virtual FStagingBufferRHIRef RHICreateStagingBuffer() final override;`
- L141 _public prototype_ `virtual FBoundShaderStateRHIRef RHICreateBoundShaderState(FRHIVertexDeclaration* VertexDeclaration, FRHIVertexShader* VertexShader, FRHIPixelShader* PixelShader, FRHIGeometryShader* GeometryShader) final override;`
- L142 _public prototype_ `virtual FGraphicsPipelineStateRHIRef RHICreateGraphicsPipelineState(const FGraphicsPipelineStateInitializer& Initializer) final override;`
- L143 _public prototype_ `virtual FComputePipelineStateRHIRef RHICreateComputePipelineState(const FComputePipelineStateInitializer& Initializer) final override;`
- L144 _public prototype_ `virtual FUniformBufferRHIRef RHICreateUniformBuffer(const void* Contents, const FRHIUniformBufferLayout* Layout, EUniformBufferUsage Usage, EUniformBufferValidation Validation) final override;`
- L145 _public prototype_ `virtual void RHIUpdateUniformBuffer(FRHICommandListBase& RHICmdList, FRHIUniformBuffer* UniformBufferRHI, const void* Contents) final override;`
- L147 _public prototype_ `[[nodiscard]] virtual FRHIBufferInitializer RHICreateBufferInitializer(FRHICommandListBase& RHICmdList, const FRHIBufferCreateDesc& CreateDesc) final override;`
- L149 _public prototype_ `virtual void RHIReplaceResources(FRHICommandListBase& RHICmdList, TArray<FRHIResourceReplaceInfo>&& ReplaceInfos) final override;`
- L150 _public prototype_ `virtual void RHIWriteResourceGPUAddresses(FRHICommandListBase& RHICmdList, uint32 GPUIndex, TConstArrayView<FRHIResource*> Resources, uint64* AddressesPtr) final override;`
- L152 _public prototype_ `virtual void* LockBuffer_BottomOfPipe(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, uint32 Offset, uint32 Size, EResourceLockMode LockMode) final override;`
- L153 _public prototype_ `virtual void UnlockBuffer_BottomOfPipe(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override;`
- L154 _public prototype_ `virtual void* RHILockBuffer(FRHICommandListBase& RHICmdList, FRHIBuffer* BufferRHI, uint32 Offset, uint32 Size, EResourceLockMode LockMode) final override;`
- L155 _public prototype_ `virtual void RHIUnlockBuffer(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override;`
- L158 _public prototype_ `virtual void RHIUpdateAllocationTags(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override;`
- L161 _public prototype_ `virtual FTextureReferenceRHIRef RHICreateTextureReference(FRHICommandListBase& RHICmdList, FRHITexture* InReferencedTexture) final override;`
- L162 _public prototype_ `virtual void RHIUpdateTextureReference(FRHICommandListBase& RHICmdList, FRHITextureReference* TextureRef, FRHITexture* NewTexture) final override;`
- L163 _public prototype_ `virtual FRHICalcTextureSizeResult RHICalcTexturePlatformSize(FRHITextureDesc const& Desc, uint32 FirstMipIndex) final override;`
- L164 _public prototype_ `virtual void RHIGetTextureMemoryStats(FTextureMemoryStats& OutStats) final override;`
- L165 _public prototype_ `virtual bool RHIGetTextureMemoryVisualizeData(FColor* TextureData, int32 SizeX, int32 SizeY, int32 Pitch, int32 PixelSize) final override;`
- L175 _public prototype_ `FCreateTextureResult BeginCreateTextureInternal(const FRHITextureCreateDesc& CreateDesc, const FRHITransientHeapAllocation* InTransientHeapAllocation);`
- L176 _public prototype_ `FVulkanTexture* FinalizeCreateTextureInternal(FRHICommandListBase& RHICmdList, FCreateTextureResult CreateResult);`
- L178 _public prototype_ `FVulkanTexture* CreateTextureInternal(FRHICommandListBase& RHICmdList, const FRHITextureCreateDesc& CreateDesc);`
- L179 _public prototype_ `FVulkanTexture* CreateTextureInternal(const FRHITextureCreateDesc& CreateDesc, const FRHITransientHeapAllocation& InTransientHeapAllocation);`
- L181 _public prototype_ `[[nodiscard]] virtual FRHITextureInitializer RHICreateTextureInitializer(FRHICommandListBase& RHICmdList, const FRHITextureCreateDesc& CreateDesc);`
- L183 _public prototype_ `virtual FTextureRHIRef RHIAsyncCreateTexture2D(uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, ETextureCreateFlags Flags, ERHIAccess InResourceState, void** InitialMipData, uint32 NumInitialMips, const TCHAR* DebugName, FGraphEventRef& OutCompletionEvent) final override;`
- L184 _public prototype_ `virtual uint32 RHIComputeMemorySize(FRHITexture* TextureRHI) final override;`
- L186 _public prototype_ `virtual void RHIGetMemoryStats(FRHIMemoryStats& OutStats) final override;`
- L188 _public prototype_ `virtual FRHILockTextureResult RHILockTexture(FRHICommandListImmediate& RHICmdList, const FRHILockTextureArgs& Arguments) final override;`
- L189 _public prototype_ `virtual void RHIUnlockTexture(FRHICommandListImmediate& RHICmdList, const FRHILockTextureArgs& Arguments) final override;`
- L191 _public function_ `virtual void RHIUpdateTexture2D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion2D& UpdateRegion, uint32 SourcePitch, const uint8* SourceData) final override`
- L195 _public function_ `virtual void RHIUpdateTexture3D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion3D& UpdateRegion, uint32 SourceRowPitch, uint32 SourceDepthPitch, const uint8* SourceData) final override`
- L199 _public prototype_ `virtual void RHIBindDebugLabelName(FRHICommandListBase& RHICmdList, FRHITexture* Texture, const TCHAR* Name) final override;`
- L200 _public prototype_ `virtual void RHIReadSurfaceData(FRHITexture* Texture, FIntRect Rect, TArray<FColor>& OutData, FReadSurfaceDataFlags InFlags) final override;`
- L201 _public prototype_ `virtual void RHIReadSurfaceData(FRHITexture* Texture, FIntRect Rect, TArray<FLinearColor>& OutData, FReadSurfaceDataFlags InFlags) final override;`
- L202 _public prototype_ `virtual void RHIMapStagingSurface(FRHITexture* Texture, FRHIGPUFence* Fence, void*& OutData, int32& OutWidth, int32& OutHeight, uint32 GPUIndex = 0) final override;`
- L203 _public prototype_ `virtual void RHIUnmapStagingSurface(FRHITexture* Texture, uint32 GPUIndex = 0) final override;`
- L205 _public prototype_ `virtual void RHIReadSurfaceFloatData(FRHITexture* Texture, FIntRect Rect, TArray<FFloat16Color>& OutData, ECubeFace CubeFace, int32 ArrayIndex, int32 MipIndex) final override;`
- L206 _public prototype_ `virtual void RHIRead3DSurfaceFloatData(FRHITexture* Texture, FIntRect Rect, FIntPoint ZMinMax, TArray<FFloat16Color>& OutData) final override;`
- L207 _public prototype_ `virtual FRenderQueryRHIRef RHICreateRenderQuery(ERenderQueryType QueryType) final override;`
- L208 _public prototype_ `virtual void RHIEndRenderQuery_TopOfPipe(FRHICommandListBase& RHICmdList, FRHIRenderQuery* RenderQuery) final override;`
- L209 _public prototype_ `virtual void RHIBeginRenderQueryBatch_TopOfPipe(FRHICommandListBase& RHICmdList, ERenderQueryType QueryType) final override;`
- L210 _public prototype_ `virtual void RHIEndRenderQueryBatch_TopOfPipe(FRHICommandListBase& RHICmdList, ERenderQueryType QueryType) final override;`
- L211 _public prototype_ `virtual bool RHIGetRenderQueryResult(FRHIRenderQuery* RenderQuery, uint64& OutResult, bool bWait, uint32 GPUIndex = INDEX_NONE) final override;`
- L212 _public prototype_ `virtual FTextureRHIRef RHIGetViewportBackBuffer(FRHIViewport* Viewport) final override;`
- L213 _public prototype_ `virtual void RHIAliasTextureResources(FTextureRHIRef& DestTexture, FTextureRHIRef& SrcTexture) final override;`
- L214 _public prototype_ `virtual FTextureRHIRef RHICreateAliasedTexture(FTextureRHIRef& SourceTexture) final override;`
- L215 _public prototype_ `virtual FViewportRHIRef RHICreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PixelFormat) final override;`
- L216 _public prototype_ `virtual void RHIResizeViewport(FRHIViewport* Viewport, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PixelFormat) final override;`
- L217 _public prototype_ `virtual void RHIEndDrawingViewport(FRHICommandListImmediate& RHICmdList, FRHIViewport* Viewport, const FRHIPresentArgs& PresentArgs) final override;`
- L218 _public prototype_ `virtual void RHITick(float DeltaTime) final override;`
- L219 _public prototype_ `virtual void RHIBlockUntilGPUIdle() final override;`
- L220 _public prototype_ `virtual void RHISuspendRendering() final override;`
- L221 _public prototype_ `virtual void RHIResumeRendering() final override;`
- L222 _public prototype_ `virtual bool RHIIsRenderingSuspended() final override;`
- L223 _public prototype_ `virtual bool RHIGetAvailableResolutions(FScreenResolutionArray& Resolutions, bool bIgnoreRefreshRate) final override;`
- L224 _public prototype_ `virtual void RHIGetSupportedResolution(uint32& Width, uint32& Height) final override;`
- L225 _public prototype_ `virtual void* RHIGetNativeDevice() final override;`
- L226 _public prototype_ `virtual void* RHIGetNativePhysicalDevice() final override;`
- L227 _public prototype_ `virtual void* RHIGetNativeGraphicsQueue() final override;`
- L228 _public prototype_ `virtual void* RHIGetNativeComputeQueue() final override;`
- L229 _public prototype_ `virtual class IRHICommandContext* RHIGetDefaultContext() final override;`
- L230 _public prototype_ `virtual IRHIComputeContext* RHIGetCommandContext(ERHIPipeline Pipeline) final override;`
- L231 _public prototype_ `virtual IRHIUploadContext* RHIGetUploadContext() final override;`
- L232 _public prototype_ `virtual FRHIFinalizeContextsResult RHIFinalizeContexts(FRHIFinalizeContextsArgs&& Args) final override;`
- L233 _public prototype_ `virtual void RHISubmitCommandLists(FRHISubmitCommandListsArgs&& Args) final override;`
- L234 _public prototype_ `virtual uint64 RHIGetMinimumAlignmentForBufferBackedSRV(EPixelFormat Format) final override;`
- L236 _public prototype_ `virtual IRHICommandContext* RHIGetParallelCommandContext(FRHIParallelRenderPassInfo const& ParallelRenderPass) final override;`
- L239 _public prototype_ `virtual IRHITransientResourceAllocator* RHICreateTransientResourceAllocator() final override;` — Transient Resource Functions and Helpers
- L242 _public prototype_ `static uint32 GetPrecachePSOHashVersion();` — version of the RHIComputePrecachePSOHash
- L243 _public prototype_ `virtual uint64 RHIComputePrecachePSOHash(const FGraphicsPipelineStateInitializer& Initializer) final override;`
- L244 _public prototype_ `virtual uint64 RHIComputeStatePrecachePSOHash(const FGraphicsPipelineStateInitializer& Initializer) final override;`
- L245 _public prototype_ `virtual bool RHIMatchPrecachePSOInitializers(const FGraphicsPipelineStateInitializer& LHS, const FGraphicsPipelineStateInitializer& RHS) final override;`
- L247 _public prototype_ `virtual FUpdateTexture3DData RHIBeginUpdateTexture3D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion3D& UpdateRegion) override final;`
- L248 _public prototype_ `virtual void RHIEndUpdateTexture3D(FRHICommandListBase& RHICmdList, FUpdateTexture3DData& UpdateData) override final;`
- L251 _public prototype_ `virtual FShaderResourceViewRHIRef RHICreateShaderResourceView (class FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc) final override;` — SRV / UAV creation functions
- L252 _public prototype_ `virtual FUnorderedAccessViewRHIRef RHICreateUnorderedAccessView(class FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc) final override;`
- L255 _public prototype_ `virtual FRHIResourceCollectionRef RHICreateResourceCollection(FRHICommandListBase& RHICmdList, TConstArrayView<FRHIResourceCollectionMember> InMembers) final override;`
- L256 _public prototype_ `virtual void RHIUpdateResourceCollection(FRHICommandListBase& RHICmdList, FRHIResourceCollection* InResourceCollection, uint32 InStartIndex, TConstArrayView<FRHIResourceCollectionMember> InMemberUpdates) final override;`
- L259 _public prototype_ `virtual FRayTracingAccelerationStructureSize RHICalcRayTracingSceneSize(const FRayTracingSceneInitializer& Initializer) final override;`
- L260 _public prototype_ `virtual FRayTracingAccelerationStructureSize RHICalcRayTracingGeometrySize(const FRayTracingGeometryInitializer& Initializer) final override;`
- L261 _public prototype_ `virtual FRayTracingGeometryRHIRef RHICreateRayTracingGeometry(FRHICommandListBase& RHICmdList, const FRayTracingGeometryInitializer& Initializer) final override;`
- L262 _public prototype_ `virtual FRayTracingSceneRHIRef RHICreateRayTracingScene(FRayTracingSceneInitializer Initializer) final override;`
- L263 _public prototype_ `virtual FRayTracingShaderRHIRef RHICreateRayTracingShader(const FRHICreateShaderDesc& CreateShaderDesc, EShaderFrequency ShaderFrequency) final override;`
- L264 _public prototype_ `virtual FRayTracingPipelineStateRHIRef RHICreateRayTracingPipelineState(const FRayTracingPipelineStateInitializer& Initializer) final override;`
- L266 _public prototype_ `virtual FShaderBindingTableRHIRef RHICreateShaderBindingTable(FRHICommandListBase& RHICmdList, const FRayTracingShaderBindingTableInitializer& Initializer) final override;`
- L269 _public member_ `uint32 TotalPresentCount = 0;` — Historical number of times we've presented any and all viewports
- L271 _public function_ `const TArray<const ANSICHAR*>& GetInstanceExtensions() const`
- L276 _public function_ `const TArray<const ANSICHAR*>& GetInstanceLayers() const`
- L281 _public function_ `VkInstance GetInstance() const`
- L286 _public function_ `FVulkanDevice* GetDevice() const`
- L291 _public function_ `bool SupportsDebugUtilsExt() const`
- L296 _public function_ `const FOptionalVulkanInstanceExtensions& GetOptionalExtensions() const`
- L301 _public prototype_ `void VulkanSetImageLayout( VkCommandBuffer CmdBuffer, VkImage Image, VkImageLayout OldLayout, VkImageLayout NewLayout, const VkImageSubresourceRange& SubresourceRange );`
- L303 _public prototype_ `virtual void* RHILockStagingBuffer(FRHIStagingBuffer* StagingBuffer, FRHIGPUFence* Fence, uint32 Offset, uint32 SizeRHI) final override;`
- L304 _public prototype_ `virtual void RHIUnlockStagingBuffer(FRHIStagingBuffer* StagingBuffer) final override;`
- L306 _public function_ `TArray<FVulkanViewport*>& GetViewports()`
- L311 _public function_ `uint32 GetApiVersion() const`
- L317 _public prototype_ `virtual void RHIRunOnQueue(EVulkanRHIRunOnQueueType QueueType, TFunction<void(VkQueue)>&& CodeToRun, bool bWaitForSubmission) final override;` — Runs code on SubmissionThread with access to VkQueue.  Useful for plugins.
- L319 _public prototype_ `virtual void RHISetFDMOffsets(const FVector2f GazePoint[2], FIntPoint FramebufferSize);`
- L321 _public prototype_ `void DumpCrashMarkers();`
- L323 _public prototype_ `static void SavePipelineCache();`
- L325 _public prototype_ `void ProcessInterruptQueueUntil(FVulkanSyncPointRef SyncPoint);`
- L326 _public prototype_ `void ProcessInterruptQueueUntil(FGraphEvent* GraphEvent);`
- L327 _public prototype_ `void EnqueueEndOfPipeTask(TUniqueFunction<void()> TaskFunc, TUniqueFunction<void(FVulkanPayload&)> ModifyPayloadCallback = {});`
- L328 _public prototype_ `void CompletePayload(FVulkanPayload* Payload);`
- L330 _public member_ `TOptional<uint64> ExternalGPUTime;`
- L334 _public prototype_ `bool IsInInterruptThread() const;` — Returns true if the calling thread is the interrupt thread (or acting as the interrupt thread when USE_INTERRUPT_THREAD is zero).
- L337 _public prototype_ `void ProcessInterruptQueueOnGPUCrash();` — Called when the GPU has crashed. This function will not return.
- L338 _public prototype_ `void TerminateOnGPUCrash(const TCHAR* Message);`
- L340 _public function_ `bool HasInterruptThread() const`
- L345 _public function_ `bool HasSubmissionThread() const`
- L350 _public prototype_ `void KickSubmissionThread(bool bForce = false);`
- L353 _protected prototype_ `void InitializeSubmissionPipe();`
- L354 _protected prototype_ `void ShutdownSubmissionPipe();`
- L355 _protected prototype_ `bool ProcessSubmissionQueue();`
- L356 _protected prototype_ `bool ProcessInterruptQueue();`
- L357 _protected prototype_ `bool WaitAndProcessInterruptQueue();`
- L358 _protected prototype_ `void KickInterruptThread();`
- L367 _protected member_ `FVulkanTimingArray CurrentTimingPerQueue;`
- L369 _protected member_ `FCriticalSection SubmissionCS;`
- L370 _protected member_ `FVulkanThread* SubmissionThread = nullptr;`
- L371 _protected member_ `FCriticalSection InterruptCS;`
- L372 _protected member_ `FVulkanThread* InterruptThread = nullptr;`
- L373 _protected member_ `FVulkanSemaphore* CPUTimelineSemaphore = nullptr;` — used to wake up interrupt thread from CPU
- L374 _protected member_ `std::atomic<uint64> CPUTimelineSemaphoreValue = 1;`
- L375 _protected member_ `TQueue<FVulkanPlatformCommandList*, EQueueMode::Mpsc> PendingPayloadsForSubmission;`
- L376 _protected member_ `TMap<VkSemaphore, FBinarySemaphoreSignalInfo> SignaledSemaphores;`
- L377 _protected member_ `FGraphEventRef EopTask;`
- L381 _protected member_ `uint32 InterruptThreadID = 0;` — Used when a dedicated interrupt thread is disabled (D3D12_USE_INTERRUPT_THREAD) Tracks the thread ID of the thread currently acting as the interrupt thread.
- L383 _protected member_ `uint32 ApiVersion = 0;`
- L384 _protected member_ `VkInstance Instance;`
- L385 _protected member_ `TArray<const ANSICHAR*> InstanceExtensions;`
- L386 _protected member_ `TArray<const ANSICHAR*> InstanceLayers;`
- L388 _protected member_ `FVulkanDevice* Device;`
- L391 _protected member_ `TArray<FVulkanViewport*> Viewports;` — A list of all viewport RHIs that have been created.
- L393 _protected prototype_ `void CreateInstance();`
- L394 _protected prototype_ `void SelectDevice();`
- L404 _protected prototype_ `TArray<const ANSICHAR*> SetupInstanceLayers(FVulkanInstanceExtensionArray& UEExtensions);`
- L406 _protected member_ `IConsoleObject* SavePipelineCacheCmd = nullptr;`
- L407 _protected member_ `IConsoleObject* RebuildPipelineCacheCmd = nullptr;`
- L409 _protected member_ `IConsoleObject* SaveValidationCacheCmd = nullptr;`
- L412 _protected prototype_ `static void RebuildPipelineCache();`
- L414 _protected prototype_ `static void SaveValidationCache();`
- L418 _protected member_ `IConsoleObject* DumpMemoryCmd = nullptr;`
- L419 _protected member_ `IConsoleObject* DumpMemoryFullCmd = nullptr;`
- L420 _protected member_ `IConsoleObject* DumpStagingMemoryCmd = nullptr;`
- L421 _protected member_ `IConsoleObject* DumpLRUCmd = nullptr;`
- L422 _protected member_ `IConsoleObject* TrimLRUCmd = nullptr;`
- L424 _public prototype_ `static void DumpMemory();`
- L425 _public prototype_ `static void DumpMemoryFull();`
- L426 _public prototype_ `static void DumpStagingMemory();`
- L427 _public prototype_ `static void DumpLRU();`
- L428 _public prototype_ `static void TrimLRU();`
- L441 _protected member_ `bool bIsStandaloneStereoDevice = false;`
- L443 _protected member_ `EActiveDebugLayerExtension ActiveDebugLayerExtension = EActiveDebugLayerExtension::None;`
- L446 _protected member_ `VkDebugUtilsMessengerEXT Messenger = VK_NULL_HANDLE;`
- L447 _protected member_ `VkDebugUtilsMessengerEXT AddressBindingMessenger = VK_NULL_HANDLE;`
- L449 _protected prototype_ `void SetupDebugCallbacks();`
- L450 _protected prototype_ `void RemoveDebugCallbacks();`
- L453 _protected member_ `FCriticalSection LockBufferCS;`
- L455 _protected prototype_ `void InternalUpdateTexture2D(FRHICommandListBase& RHICmdList, FRHITexture* TextureRHI, uint32 MipIndex, const struct FUpdateTextureRegion2D& UpdateRegion, uint32 SourcePitch, const uint8* SourceData);`
- L456 _protected prototype_ `void InternalUpdateTexture3D(FRHICommandListBase& RHICmdList, FRHITexture* TextureRHI, uint32 MipIndex, const struct FUpdateTextureRegion3D& UpdateRegion, uint32 SourceRowPitch, uint32 SourceDepthPitch, const uint8* SourceData);`
- L458 _protected prototype_ `static void SetupValidationRequests();`
- L460 _protected member_ `FOptionalVulkanInstanceExtensions OptionalInstanceExtensions;`
- L463 _public member_ `static TSharedPtr< IHeadMountedDisplayVulkanExtensions, ESPMode::ThreadSafe > HMDVulkanExtensions;`

#### struct `FVulkanDynamicRHI::FCreateTextureResult`  
`struct FCreateTextureResult`  
_L167-173_
- L169 _public member_ `FVulkanTexture* Texture;`
- L170 _public member_ `VkImageLayout DefaultLayout;`
- L171 _public member_ `bool bTransientResource;`
- L172 _public member_ `bool bClear;`

#### struct `FVulkanDynamicRHI::FVulkanTimingArray`  
`struct FVulkanTimingArray : public TArray<TUniquePtr<FVulkanTiming>, TInlineAllocator<(int32)EVulkanQueueType::Count>>`  
_L360-366_
- inherits: `TArray<TUniquePtr<FVulkanTiming>,TInlineAllocator<(int32)EVulkanQueueType::Count>>`
- L362 _public function_ `FVulkanTiming* CreateNew(FVulkanQueue& Queue)`

#### enum `FVulkanDynamicRHI::EActiveDebugLayerExtension`  
`enum class EActiveDebugLayerExtension`  
_L432-438_
- L434 _public enumerator_ `None`
- L435 _public enumerator_ `GfxReconstructLayer`
- L436 _public enumerator_ `VkTraceLayer`
- L437 _public enumerator_ `DebugUtilsExtension`

#### class `FVulkanDynamicRHIModule`  
`class FVulkanDynamicRHIModule : public IDynamicRHIModule`  
_L469-480_
- inherits: `IDynamicRHIModule`
- desc: Implements the Vulkan module as a dynamic RHI providing module.
- L473 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L476 _public prototype_ `virtual bool IsSupported() override;` — IDynamicRHIModule
- L477 _public prototype_ `virtual bool IsSupported(ERHIFeatureLevel::Type RequestedFeatureLevel) override;`
- L479 _public prototype_ `virtual FDynamicRHI* CreateRHI(ERHIFeatureLevel::Type RequestedFeatureLevel = ERHIFeatureLevel::Num) override;`

#### Free symbols / members of external scopes

- L33 _member_ `uint32 HasKHRExternalMemoryCapabilities : 1;` (scope `FOptionalVulkanInstanceExtensions::__anona224af25010a::__anona224af250208`) — `UE_DEPRECATED(5.3, "Vulkan 1.1 is now a requirement so there is no need to check these capabilities.")`
- L36 _member_ `uint32 HasKHRGetPhysicalDeviceProperties2 : 1;` (scope `FOptionalVulkanInstanceExtensions::__anona224af25010a::__anona224af250208`) — `UE_DEPRECATED(5.3, "Vulkan 1.1 is now a requirement so there is no need to check these capabilities.")`
- L38 _member_ `uint32 Packed;` (scope `FOptionalVulkanInstanceExtensions::__anona224af25010a`)

### `Source/Runtime/VulkanRHI/Private/VulkanExtensions.h` (Private)


#### enum `EVulkanVariableRateShadingPreference`  
`enum class EVulkanVariableRateShadingPreference : uint8`  
_L20-28_
- L22 _public enumerator_ `PreferFSR = 0` — This can be used to prefer FSR over FDM when both are available.
- L23 _public enumerator_ `UseFSROnlyIfAvailable` — This will only print a message if FSR is not available.
- L24 _public enumerator_ `RequireFSR` — This will print an error if FSR is not available.
- L25 _public enumerator_ `PreferFDM` — This can be used to prefer FDM over FSR when both are available.
- L26 _public enumerator_ `UseFDMOnlyIfAvailable` — This will only print a message if FDM is not available.
- L27 _public enumerator_ `RequireFDM` — This will print an error if FDM is not available.

#### class `FVulkanExtensionBase`  
`class FVulkanExtensionBase`  
_L30-97_
- L44 _public function_ `FVulkanExtensionBase(const ANSICHAR* InExtensionName, int32 InEnabledInCode, uint32 InPromotedVersion, EExtensionActivation InActivation) : ExtensionName(InExtensionName) , PromotedVersion(InPromotedVersion) , bEnabledInCode(InEnabledInCode == VULKAN_EXTENSION_ENABLED) , bSupported(false) , bActivated(InActivation == EExtensionActivation::AutoActivate) , bCore(false)`
- L53 _public prototype_ `virtual ~FVulkanExtensionBase() = default;`
- L55 _public function_ `inline void SetSupported()`
- L56 _public function_ `inline void SetActivated()`
- L57 _public function_ `inline bool SetCore(uint32 ApiVersion)`
- L59 _public function_ `inline const ANSICHAR* GetExtensionName() const`
- L60 _public function_ `inline bool IsEnabled() const`
- L61 _public function_ `inline bool IsSupported() const`
- L62 _public function_ `inline bool IsCore()`
- L64 _public function_ `inline bool InUse() const`
- L70 _public function_ `template <typename ExtensionType> static int32 FindExtension(const TArray<TUniquePtr<ExtensionType>>& UEExtensions, const ANSICHAR* ExtensionName)`
- L83 _protected member_ `const ANSICHAR* ExtensionName;`
- L84 _protected member_ `const uint32 PromotedVersion;`
- L87 _protected member_ `bool bEnabledInCode;` — Extension is enabled in code if the VULKAN_SUPPORTS_* define is TRUE in VulkanConfiguration.h or Vulkan*Platform.h.
- L90 _protected member_ `bool bSupported;` — Signals if the extension is support by the driver of the device being used (evaluated at runtime).
- L93 _protected member_ `bool bActivated;` — Signals if the runtime currently wants this extension to be loaded.
- L96 _protected member_ `bool bCore;` — Signals if the extension has been promoted to core Vulkan for the current instance version

#### enum `FVulkanExtensionBase::EExtensionActivation`  
`enum EExtensionActivation : uint8`  
_L33-42_
- L36 _public enumerator_ `AutoActivate` — If the extension is enabled in code and supported by the driver, it will automatically get used.
- L41 _public enumerator_ `ManuallyActivate` — The extension will not be used unless SetActivated() is called in the extension. Can be used to add engine support for an extension, but not use it by default unless externally requested. Useful for extensions only activated by plugins, or only present when a certain layer is loaded.

#### class `FVulkanDeviceExtension`  
`class FVulkanDeviceExtension : public FVulkanExtensionBase`  
_L101-140_
- inherits: `FVulkanExtensionBase`
- L105 _public function_ `FVulkanDeviceExtension(FVulkanDevice* InDevice, const ANSICHAR* InExtensionName, int32 InEnabledInCode, uint32 InPromotedVersion = VULKAN_EXTENSION_NOT_PROMOTED, TUniqueFunction<void(FOptionalVulkanDeviceExtensions& ExtensionFlags)>&& InFlagSetter = nullptr, EExtensionActivation InActivation = FVulkanExtensionBase::AutoActivate) : FVulkanExtensionBase(InExtensionName, InEnabledInCode, InPromotedVersion, InActivation) , Device(InDevice) , FlagSetter(MoveTemp(InFlagSetter)) , bRequirementsPassed(true)`
- L112 _public prototype_ `static FVulkanDeviceExtensionArray GetUESupportedDeviceExtensions(FVulkanDevice* InDevice, uint32 ApiVersion);`
- L113 _public prototype_ `static TArray<VkExtensionProperties> GetDriverSupportedDeviceExtensions(VkPhysicalDevice Gpu, const ANSICHAR* LayerName = nullptr);`
- L115 _public function_ `virtual void PrePhysicalDeviceProperties(VkPhysicalDeviceProperties2KHR& PhysicalDeviceProperties2)`
- L116 _public function_ `virtual void PostPhysicalDeviceProperties(FOptionalVulkanDeviceExtensions& ExtensionFlags)`
- L118 _public function_ `virtual void PrePhysicalDeviceFeatures(VkPhysicalDeviceFeatures2KHR& PhysicalDeviceFeatures2)`
- L119 _public function_ `virtual void PostPhysicalDeviceFeatures(FOptionalVulkanDeviceExtensions& ExtensionFlags)`
- L127 _public function_ `virtual void PreCreateDevice(VkDeviceCreateInfo& DeviceInfo)`
- L130 _public member_ `static TArray<TSharedRef<class FVulkanRHIExternalDeviceExtensionBase>> ExternalExtensions;` — Holds extensions requested externally (eg plugins)
- L133 _protected prototype_ `struct FOptionalVulkanDeviceExtensionProperties& GetDeviceExtensionProperties();`
- L135 _protected member_ `FVulkanDevice* Device;`
- L136 _protected member_ `TUniqueFunction<void(FOptionalVulkanDeviceExtensions& ExtensionFlags)> FlagSetter;`
- L139 _protected member_ `bool bRequirementsPassed;` — Signals that this extension has passed any specific feature and/or property requirements

#### class `FVulkanInstanceExtension`  
`class FVulkanInstanceExtension : public FVulkanExtensionBase`  
_L144-168_
- inherits: `FVulkanExtensionBase`
- L148 _public function_ `FVulkanInstanceExtension(const ANSICHAR* InExtensionName, int32 InEnabledInCode, uint32 InPromotedVersion = VULKAN_EXTENSION_NOT_PROMOTED, TUniqueFunction<void(FOptionalVulkanInstanceExtensions& ExtensionFlags)>&& InFlagSetter = nullptr, EExtensionActivation InActivation = FVulkanExtensionBase::AutoActivate) : FVulkanExtensionBase(InExtensionName, InEnabledInCode, InPromotedVersion, InActivation) , FlagSetter(MoveTemp(InFlagSetter))`
- L153 _public prototype_ `static FVulkanInstanceExtensionArray GetUESupportedInstanceExtensions(uint32 ApiVersion);`
- L154 _public prototype_ `static TArray<VkExtensionProperties> GetDriverSupportedInstanceExtensions(const ANSICHAR* LayerName = nullptr);`
- L156 _public function_ `virtual void PreCreateInstance(VkInstanceCreateInfo& CreateInfo, FOptionalVulkanInstanceExtensions& ExtensionFlags)`
- L164 _public member_ `static TArray<const ANSICHAR*> ExternalExtensions;`
- L167 _protected member_ `TUniqueFunction<void(FOptionalVulkanInstanceExtensions& ExtensionFlags)> FlagSetter;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define VULKAN_EXTENSION_NOT_PROMOTED UINT32_MAX`
- L15 _macro_ `#define VULKAN_EXTENSION_ENABLED 1`
- L16 _macro_ `#define VULKAN_EXTENSION_DISABLED 0`
- L171 _macro_ `#define DEVICE_EXT_FLAG_SETTER(FLAG_NAME) [](FOptionalVulkanDeviceExtensions& ExtensionFlags) { ExtensionFlags.FLAG_NAME = 1; }` — Helpers to create simple extensions that set a flag
- L172 _macro_ `#define INSTANCE_EXT_FLAG_SETTER(FLAG_NAME) [](FOptionalVulkanInstanceExtensions& ExtensionFlags) { ExtensionFlags.FLAG_NAME = 1; }`

### `Source/Runtime/VulkanRHI/Private/VulkanFramebuffer.h` (Private)


#### class `FVulkanFramebuffer`  
`class FVulkanFramebuffer`  
_L7-93_
- L10 _public prototype_ `FVulkanFramebuffer(FVulkanDevice& Device, const FRHISetRenderTargetsInfo& InRTInfo, const FVulkanRenderTargetLayout& RTLayout, const FVulkanRenderPass& RenderPass);`
- L11 _public prototype_ `~FVulkanFramebuffer();`
- L13 _public prototype_ `bool Matches(const FRHISetRenderTargetsInfo& RTInfo) const;`
- L15 _public function_ `uint32 GetNumColorAttachments() const`
- L20 _public prototype_ `void Destroy(FVulkanDevice& Device);`
- L22 _public function_ `VkFramebuffer GetHandle()`
- L27 _public function_ `const FVulkanView::FTextureView& GetPartialDepthTextureView() const`
- L33 _public member_ `TArray<FVulkanView const*> AttachmentTextureViews;`
- L36 _public member_ `FVulkanView const* PartialDepthTextureView = nullptr;` — Copy from the Depth render target partial view
- L38 _public function_ `bool ContainsRenderTarget(FRHITexture* Texture) const`
- L45 _public function_ `bool ContainsRenderTarget(VkImage Image) const`
- L59 _public function_ `VkRect2D GetRenderArea() const`
- L65 _public prototype_ `static FVulkanView* GetColorRenderTargetViewDesc(FVulkanTexture* Texture, uint32 MipIndex, int32 ArraySliceIndex, uint32 MultiViewCount, uint32& InOutNumLayers);` — Expose the view creation logic so it can be reused for dynamic rendering
- L66 _public prototype_ `static FVulkanView* GetColorResolveTargetViewDesc(FVulkanTexture* ResolveTexture, uint32 MipIndex, int32 ArraySliceIndex);`
- L67 _public prototype_ `static FVulkanView* GetDepthStencilTargetViewDesc(FVulkanTexture* Texture, uint32 NumColorAttachments, uint32 MipIndex, uint32 MultiViewCount, uint32& InOutNumLayers);`
- L68 _public prototype_ `static FVulkanView* GetDepthStencilResolveTargetViewDesc(FVulkanTexture* ResolveTexture, uint32 MipIndex);`
- L69 _public prototype_ `static FVulkanView* GetFragmentDensityAttachmentViewDesc(FVulkanTexture* Texture, uint32 MipIndex);`
- L72 _private prototype_ `[[nodiscard]] static FVulkanTextureViewDesc GetDefaultRenderTargetViewDesc(const FVulkanTexture& Texture, const uint32 MipIndex, const int32 SliceIndex);`
- L75 _private member_ `VkFramebuffer Framebuffer;`
- L76 _private member_ `VkRect2D RenderArea;`
- L79 _private member_ `uint32 NumColorRenderTargets;` — Unadjusted number of color render targets as in FRHISetRenderTargetsInfo
- L82 _private member_ `uint32 NumColorAttachments;` — Save image off for comparison, in case it gets aliased.
- L83 _private member_ `VkImage ColorRenderTargetImages[MaxSimultaneousRenderTargets];`
- L84 _private member_ `VkImage ColorResolveTargetImages[MaxSimultaneousRenderTargets];`
- L85 _private member_ `VkImage DepthStencilRenderTargetImage;`
- L86 _private member_ `VkImage DepthStencilResolveRenderTargetImage;`
- L87 _private member_ `VkImage FragmentDensityImage;`
- L90 _private member_ `TArray<VkImageMemoryBarrier> WriteBarriers;` — Predefined set of barriers, when executes ensuring all writes are finished

### `Source/Runtime/VulkanRHI/Private/VulkanGenericPlatform.h` (Private)


#### class `FVulkanGenericPlatformWindowContext`  
`class FVulkanGenericPlatformWindowContext`  
_L29-43_
- L32 _public function_ `FVulkanGenericPlatformWindowContext(void* WindowHandleIn) : WindowHandle(WindowHandleIn)`
- L33 _public function_ `void* GetWindowHandle() const`
- L37 _public function_ `uint32 GetWindowId() const` — Platform-defined opaque window id captured at context construction (0 if the platform does not track one). Used to release per-window RHI resources by a stable id rather than by a pointer that may be stale/reused by destroy time.
- L39 _public function_ `static bool CanCreateSwapchainOnDemand()` — whether the platform can attempt to create a swapchains during present
- L40 _public function_ `bool IsValid() const`
- L42 _protected member_ `void* WindowHandle = nullptr;`

#### class `FVulkanGenericPlatform`  
`class FVulkanGenericPlatform`  
_L45-179_
- L48 _public function_ `static bool IsSupported()`
- L50 _public function_ `static bool LoadVulkanLibrary()`
- L51 _public prototype_ `static bool LoadVulkanInstanceFunctions(VkInstance inInstance);`
- L52 _public prototype_ `static void ClearVulkanInstanceFunctions();`
- L53 _public function_ `static void FreeVulkanLibrary()`
- L55 _public function_ `static void InitDevice(FVulkanDevice* InDevice)`
- L56 _public function_ `static void PostInitGPU(const FVulkanDevice& InDevice)`
- L59 _public function_ `static void NotifyFoundInstanceLayersAndExtensions(const TArray<const ANSICHAR*>& Layers, const TArray<const ANSICHAR*>& Extensions)` — Called after querying all the available extensions and layers
- L60 _public function_ `static void NotifyFoundDeviceLayersAndExtensions(VkPhysicalDevice PhysicalDevice, const TArray<const ANSICHAR*>& Layers, const TArray<const ANSICHAR*>& Extensions)`
- L63 _public prototype_ `static void GetInstanceExtensions(FVulkanInstanceExtensionArray& OutExtensions);` — Array of required extensions for the platform (Required!)
- L64 _public function_ `static void GetInstanceLayers(TArray<const ANSICHAR*>& OutLayers)`
- L65 _public prototype_ `static void GetDeviceExtensions(FVulkanDevice* Device, FVulkanDeviceExtensionArray& OutExtensions);`
- L66 _public function_ `static void GetDeviceLayers(TArray<const ANSICHAR*>& OutLayers)`
- L69 _public function_ `static void OnGPUCrash(const TCHAR* Message)` — Allows platform specific GPU crash handling
- L72 _public prototype_ `static void CreateSurface(VkSurfaceKHR* OutSurface);` — create/destroy the platform-specific surface object - required
- L73 _public prototype_ `static void DestroySurface(uint32 WindowId, VkInstance Instance, VkSurfaceKHR Surface);`
- L76 _public function_ `static bool SupportsBCTextureFormats()` — most platforms support BC* but not ASTC* or ETC2*
- L77 _public function_ `static bool SupportsASTCTextureFormats()`
- L78 _public function_ `static bool SupportsETC2TextureFormats()`
- L79 _public function_ `static bool SupportsR16UnormTextureFormat()`
- L82 _public function_ `static bool SupportsQuerySurfaceProperties()` — most platforms can query the surface for the present mode, and size, etc
- L84 _public prototype_ `static void SetupFeatureLevels(TArrayView<EShaderPlatform> ShaderPlatformForFeatureLevel);`
- L86 _public function_ `static bool SupportsTimestampRenderQueries()`
- L88 _public function_ `static bool RequiresMobileRenderer()`
- L90 _public prototype_ `static ERHIFeatureLevel::Type GetFeatureLevel(ERHIFeatureLevel::Type RequestedFeatureLevel);`
- L93 _public function_ `static void OverridePlatformHandlers(bool bInit)` — bInit=1 called at RHI init time, bInit=0 at RHI deinit time
- L96 _public function_ `static bool RequiresPresentLayoutFix()` — Some platforms have issues with the access flags for the Present layout
- L98 _public function_ `static bool HasUnifiedMemory()`
- L101 _public prototype_ `static void RestrictEnabledPhysicalDeviceFeatures(FVulkanPhysicalDeviceFeatures* InOutFeaturesToEnable);` — Allow the platform code to restrict the device features
- L103 _public function_ `static bool SupportParallelRenderingTasks()`
- L106 _public function_ `static bool SupportsDynamicResolution()` — The status quo is true, Platforms might opt out if GPU timing queries are not supported.
- L108 _public function_ `static bool SupportsVolumeTextureRendering()`
- L110 _public function_ `static bool RequiresSwapchainGeneralInitialLayout()`
- L113 _public function_ `static bool FramePace(FVulkanDevice& Device, void* WindowHandle, VkSwapchainKHR Swapchain, uint32 PresentID, VkPresentInfoKHR& Info)` — Allow platforms to perform their own frame pacing, called before Present. Returns true if the platform has done framepacing, false otherwise.
- L116 _public prototype_ `static VkResult Present(VkQueue Queue, VkPresentInfoKHR& PresentInfo);` — Allow platforms to do extra work on present
- L119 _public prototype_ `static VkResult CreateSwapchainKHR(FVulkanGenericPlatformWindowContext& WindowContext, VkPhysicalDevice PhysicalDevice, VkDevice Device, const VkSwapchainCreateInfoKHR* CreateInfo, const VkAllocationCallbacks* Allocator, VkSwapchainKHR* Swapchain);` — Allow platforms to track swapchain creation
- L122 _public prototype_ `static void DestroySwapchainKHR(VkDevice Device, VkSwapchainKHR Swapchain, const VkAllocationCallbacks* Allocator);` — Allow platforms to track swapchain destruction
- L125 _public function_ `static bool RecreateSwapchainOnFail()` — Whether to attempt recreate swapchain when present or acqurire operations fail
- L129 _public function_ `static bool IsWindowValid(void* WindowHandle)` — Check if a native window handle is still valid for presentation. Platforms where surfaces can be invalidated externally (e.g. Wayland) should override this.
- L132 _public function_ `static bool TryConsumeSwapchainRecreateRequest(void* WindowHandle)` — Test-and-clear a platform-side swapchain-recreate request.
- L135 _public function_ `static bool RequiresWaitingForFrameCompletionEvent()` — Ensure the last frame completed on the GPU
- L138 _public function_ `static bool SupportsNullPixelShader()` — Does the platform allow a nullptr Pixelshader on the pipeline
- L141 _public function_ `static bool RequiresDepthStencilFullWrite()` — Does the platform require depth to be written on stencil clear
- L144 _public function_ `static bool RequiresMergedDepthStencilLayout()` — Does the platform require to avoid VkAttachmentDescriptionStencilLayout in favor of merged depth-stencil layouts
- L147 _public prototype_ `static bool PSOBinaryCacheMatches(FVulkanDevice* Device, const TArray<uint8>& DeviceCache);` — Checks if the PSO cache matches the expected vulkan device properties
- L150 _public prototype_ `static FString CreatePSOBinaryCacheFilename(FVulkanDevice* Device, FString CacheFilename);` — Will create the correct format from a generic pso filename
- L153 _public prototype_ `static FString GetCompiledPSOCacheTopFolderPath();` — Get top-level path for pso cache files (defaults to ProjectSavedDir/VulkanProgramBinaryCache)
- L156 _public prototype_ `static TArray<FString> GetPSOCacheFilenames();` — Gathers a list of pso cache filenames to attempt to load
- L159 _public function_ `static VkPipelineCache PrecompilePSO(FVulkanDevice* Device, const TArrayView<const uint8> ContextData, const TArrayView<const uint8> OptionalPSOCacheData, FGraphicsPipelineStateInitializer::EPSOPrecacheCompileType PSOCompileType, const VkGraphicsPipelineCreateInfo* PipelineInfo, const FGfxPipelineDesc* GfxEntry, const FVulkanRenderTargetLayout* RTLayout, TArrayView<const uint32_t> VS, TArrayView<const uint32_t> PS, size_t& AfterSize, FString* FailureMessageOUT = nullptr)` — Gives platform a chance to handle precompile of PSOs, returns VK_NULL_HANDLE if unsupported
- L162 _public function_ `static VkBool32 DebugReportFunction(VkDebugReportFlagsEXT MsgFlags, VkDebugReportObjectTypeEXT ObjType, uint64_t SrcObject, size_t Location, int32 MsgCode, const ANSICHAR* LayerPrefix, const ANSICHAR* Msg, void* UserData)` — Return VK_FALSE if platform wants to suppress the given debug report from the validation layers, VK_TRUE to print it.
- L165 _public function_ `static void SetImageMemoryRequirementWorkaround(VkImageCreateInfo& ImageCreateInfo)` — Setup platform to use a workaround to reduce textures memory requirements
- L168 _public prototype_ `static bool SupportsProfileChecks();` — Returns the profile name to look up for a given feature level on a platform
- L169 _public prototype_ `static FString GetVulkanProfileNameForFeatureLevel(ERHIFeatureLevel::Type FeatureLevel, bool bRaytracing);`
- L172 _public function_ `static VkShaderStageFlags RequiredWaveOpsShaderStageFlags(VkShaderStageFlags VulkanDeviceShaderStageFlags)` — Returns the shader stages for which we need support for subgroup ops.
- L174 _public function_ `static VkTimeDomainKHR GetTimeDomain()`
- L177 _public prototype_ `static void OnCreatePipelineCrash(struct FCrashContextExtendedWriter& Writer, TConstArrayView<FVulkanShader*> Shaders, TStringView<TCHAR> ExtraInfo, bool bIsPrecache);`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace ERHIFeatureLevel`
- L24 _typedef_ `using FVulkanDeviceExtensionArray = TArray<TUniquePtr<class FVulkanDeviceExtension>>;`
- L25 _typedef_ `using FVulkanInstanceExtensionArray = TArray<TUniquePtr<class FVulkanInstanceExtension>>;`

### `Source/Runtime/VulkanRHI/Private/VulkanLLM.h` (Private)


#### enum `ELLMTagVulkan`  
`enum class ELLMTagVulkan : LLM_TAG_TYPE`  
_L17-31_
- desc: Add custom Tags
- L19 _public enumerator_ `VulkanMisc = (LLM_TAG_TYPE)ELLMTag::PlatformTagStart`
- L20 _public enumerator_ `VulkanUniformBuffers`
- L21 _public enumerator_ `VulkanBuffers`
- L22 _public enumerator_ `VulkanTextures`
- L23 _public enumerator_ `VulkanRenderTargets`
- L24 _public enumerator_ `VulkanSpareMemoryGPU`
- L25 _public enumerator_ `VulkanShaders`
- L26 _public enumerator_ `VulkanFrameTemp`
- L27 _public enumerator_ `VulkanStagingBuffers`
- L28 _public enumerator_ `VulkanDriverMemoryCPU`
- L29 _public enumerator_ `VulkanDriverMemoryGPU`
- L30 _public enumerator_ `Count`
- L52 _public enumerator_ `VulkanMisc = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L53 _public enumerator_ `VulkanUniformBuffers = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L54 _public enumerator_ `VulkanBuffers = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L55 _public enumerator_ `VulkanTextures = (LLM_TAG_TYPE)ELLMTag::Textures`
- L56 _public enumerator_ `VulkanRenderTargets = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L57 _public enumerator_ `VulkanSpareMemoryGPU = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L58 _public enumerator_ `VulkanShaders = (LLM_TAG_TYPE)ELLMTag::Shaders`
- L59 _public enumerator_ `VulkanFrameTemp = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L60 _public enumerator_ `VulkanStagingBuffers = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L61 _public enumerator_ `VulkanDriverMemoryCPU = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L62 _public enumerator_ `VulkanDriverMemoryGPU = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L63 _public enumerator_ `Count = (LLM_TAG_TYPE)ELLMTag::PlatformTagStart + 11`

#### enum `ELLMTagVulkan`  
`enum class ELLMTagVulkan : LLM_TAG_TYPE`  
_L50-64_
- desc: Translate VulkanTag to regular Tag
- L19 _public enumerator_ `VulkanMisc = (LLM_TAG_TYPE)ELLMTag::PlatformTagStart`
- L20 _public enumerator_ `VulkanUniformBuffers`
- L21 _public enumerator_ `VulkanBuffers`
- L22 _public enumerator_ `VulkanTextures`
- L23 _public enumerator_ `VulkanRenderTargets`
- L24 _public enumerator_ `VulkanSpareMemoryGPU`
- L25 _public enumerator_ `VulkanShaders`
- L26 _public enumerator_ `VulkanFrameTemp`
- L27 _public enumerator_ `VulkanStagingBuffers`
- L28 _public enumerator_ `VulkanDriverMemoryCPU`
- L29 _public enumerator_ `VulkanDriverMemoryGPU`
- L30 _public enumerator_ `Count`
- L52 _public enumerator_ `VulkanMisc = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L53 _public enumerator_ `VulkanUniformBuffers = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L54 _public enumerator_ `VulkanBuffers = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L55 _public enumerator_ `VulkanTextures = (LLM_TAG_TYPE)ELLMTag::Textures`
- L56 _public enumerator_ `VulkanRenderTargets = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L57 _public enumerator_ `VulkanSpareMemoryGPU = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L58 _public enumerator_ `VulkanShaders = (LLM_TAG_TYPE)ELLMTag::Shaders`
- L59 _public enumerator_ `VulkanFrameTemp = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L60 _public enumerator_ `VulkanStagingBuffers = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L61 _public enumerator_ `VulkanDriverMemoryCPU = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L62 _public enumerator_ `VulkanDriverMemoryGPU = (LLM_TAG_TYPE)ELLMTag::RHIMisc`
- L63 _public enumerator_ `Count = (LLM_TAG_TYPE)ELLMTag::PlatformTagStart + 11`

#### Free symbols / members of external scopes

- L33 _externvar_ `extern uint64 GVulkanLLMAllocationID;`
- L34 _macro_ `#define LLM_TRACK_VULKAN_HIGH_LEVEL_ALLOC(AllocObj, Size) { AllocObj.SetLLMTrackerID(0xDEAD | (++GVulkanLLMAllocationID << 16)); FLowLevelMemTracker::Get().OnLowLevelAlloc(ELLMTracker::Default, (void*)AllocObj.GetLLMTrackerID(), Size, (ELLM`
- L35 _macro_ `#define LLM_TRACK_VULKAN_HIGH_LEVEL_FREE(AllocObj) { FLowLevelMemTracker::Get().OnLowLevelFree(ELLMTracker::Default, (void*)AllocObj.GetLLMTrackerID()); }`
- L36 _macro_ `#define LLM_TRACK_VULKAN_SPARE_MEMORY_GPU(Size) { LLM_SCOPED_PAUSE_TRACKING_WITH_ENUM_AND_AMOUNT((ELLMTag)ELLMTagVulkan::VulkanSpareMemoryGPU, Size, ELLMTracker::Default, ELLMAllocType::None); }`
- L38 _macro_ `#define LLM_TRACK_VULKAN_HIGH_LEVEL_ALLOCATION`
- L42 _namespace_ `namespace VulkanLLM`
- L44 _prototype_ `void Initialize();` (scope `VulkanLLM`)
- L66 _macro_ `#define LLM_TRACK_VULKAN_HIGH_LEVEL_ALLOC(...)`
- L67 _macro_ `#define LLM_TRACK_VULKAN_HIGH_LEVEL_FREE(...)`
- L68 _macro_ `#define LLM_TRACK_VULKAN_SPARE_MEMORY_GPU(...)`
- L72 _macro_ `#define LLM_SCOPE_VULKAN(Tag) LLM_SCOPE((ELLMTag)Tag)`
- L73 _macro_ `#define LLM_PLATFORM_SCOPE_VULKAN(Tag) LLM_PLATFORM_SCOPE((ELLMTag)Tag)`
- L78 _macro_ `#define LLM_SCOPE_VULKAN(...)`
- L79 _macro_ `#define LLM_PLATFORM_SCOPE_VULKAN(...)`

### `Source/Runtime/VulkanRHI/Private/VulkanLayout.h` (Private)


#### class `FVulkanLayout`  
`class FVulkanLayout`  
_L9-54_
- desc: Layout for a Pipeline, also includes DescriptorSets layout
- L12 _public prototype_ `FVulkanLayout(FVulkanDevice& InDevice, bool InGfxLayout, bool InUsesBindless);`
- L13 _public prototype_ `virtual ~FVulkanLayout();`
- L15 _public function_ `const FVulkanDescriptorSetsLayout& GetDescriptorSetsLayout() const`
- L20 _public function_ `VkPipelineLayout GetPipelineLayout() const`
- L25 _public function_ `bool HasDescriptors() const`
- L30 _public function_ `uint32 GetDescriptorSetLayoutHash() const`
- L35 _public function_ `bool IsGfxLayout() const`
- L41 _protected member_ `FVulkanDevice& Device;`
- L42 _protected member_ `FVulkanDescriptorSetsLayout DescriptorSetLayout;`
- L43 _protected member_ `VkPipelineLayout PipelineLayout;`
- L45 _protected member_ `const bool bIsGfxLayout;`
- L46 _protected member_ `const bool bUsesBindless;`
- L48 _protected prototype_ `void Compile(FVulkanDescriptorSetLayoutMap& DSetLayoutMap);`

### `Source/Runtime/VulkanRHI/Private/VulkanLoader.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define ENUM_VK_ENTRYPOINTS_INSTANCE(EnumMacro) \` — List all instance Vulkan entry points used by Unreal that need to be loaded manually
- L163 _macro_ `#define ENUM_VK_ENTRYPOINTS_SURFACE_INSTANCE(EnumMacro) \` — List all surface Vulkan entry points used by Unreal that need to be loaded manually
- L171 _macro_ `#define ENUM_VK_ENTRYPOINTS_BASE(EnumMacro) \` — List all base Vulkan entry points used by Unreal that need to be loaded manually
- L179 _macro_ `#define ENUM_VK_ENTRYPOINTS_OPTIONAL_BASE(EnumMacro) \` — List all optional Vulkan entry points used by Unreal that need to be loaded manually
- L189 _macro_ `#define ENUM_VK_ENTRYPOINTS_RAYTRACING(EnumMacro) \` — List all optional Vulkan raytracing entrypoints used by Unreal
- L204 _macro_ `#define ENUM_VK_ENTRYPOINTS_OPTIONAL_INSTANCE(EnumMacro) \` — List all optional Vulkan entry points used by Unreal that need to be loaded manually
- L308 _macro_ `#define ENUM_VK_ENTRYPOINTS_ALL(EnumMacro) \` — List of all Vulkan entry points
- L319 _macro_ `#define DECLARE_VK_ENTRYPOINTS(Type,Func) extern VULKANRHI_API Type Func;` — Declare all Vulkan functions
- L320 _namespace_ `namespace VulkanDynamicAPI`
- L322 _prototype_ `ENUM_VK_ENTRYPOINTS_ALL(DECLARE_VK_ENTRYPOINTS);` (scope `VulkanDynamicAPI`)

### `Source/Runtime/VulkanRHI/Private/VulkanMemory.h` (Private)


#### class `TVulkanTrackBase`  
`template<typename Type> class TVulkanTrackBase`  
_L50-80_
- L54 _public member_ `static FCriticalSection Lock;`
- L55 _public member_ `static TSet<Type*> Objects;`
- L57 _public function_ `template<typename Callback> static uint32 CollectAll(Callback CB)`
- L69 _public function_ `static void Add(Type* Object)`
- L75 _public function_ `static void Remove(Type* Object)`

#### class `FVulkanEvictable`  
`class FVulkanEvictable`  
_L103-111_
- L106 _public function_ `virtual bool CanMove() const`
- L107 _public function_ `virtual bool CanEvict() const`
- L108 _public function_ `virtual void Evict(FVulkanDevice& Device, const FVulkanContextArray& Contexts)`
- L109 _public function_ `virtual void Move(FVulkanDevice& Device, const FVulkanContextArray& Contexts, VulkanRHI::FVulkanAllocation& Allocation)`
- L110 _public function_ `virtual FVulkanTexture* GetEvictableTexture()`

#### struct `FVulkanTrackInfo`  
`struct FVulkanTrackInfo`  
_L114-119_
- L116 _public prototype_ `FVulkanTrackInfo();`
- L117 _public member_ `void* Data;`
- L118 _public member_ `int32 SizeOrLine;` — negative indicates a stack trace, Positive line number

#### enum `EDelayAcquireImageType`  
`enum class EDelayAcquireImageType`  
_L121-125_
- L123 _public enumerator_ `None` — acquire next image on frame start
- L124 _public enumerator_ `DelayAcquire` — acquire next image just before presenting, rendering is done to intermediate image which is copied to real backbuffer

#### enum `VulkanRHI::EVulkanAllocationType`  
`enum EVulkanAllocationType : uint8`  
_L133-140_
- L134 _public enumerator_ `EVulkanAllocationEmpty`
- L135 _public enumerator_ `EVulkanAllocationPooledBuffer`
- L136 _public enumerator_ `EVulkanAllocationBuffer`
- L137 _public enumerator_ `EVulkanAllocationImage`
- L138 _public enumerator_ `EVulkanAllocationImageDedicated`
- L139 _public enumerator_ `EVulkanAllocationSize` — keep last

#### enum `VulkanRHI::EVulkanAllocationMetaType`  
`enum EVulkanAllocationMetaType : uint8`  
_L142-155_
- L144 _public enumerator_ `EVulkanAllocationMetaUnknown`
- L145 _public enumerator_ `EVulkanAllocationMetaUniformBuffer`
- L146 _public enumerator_ `EVulkanAllocationMetaMultiBuffer`
- L147 _public enumerator_ `EVulkanAllocationMetaRingBuffer`
- L148 _public enumerator_ `EVulkanAllocationMetaFrameTempBuffer`
- L149 _public enumerator_ `EVulkanAllocationMetaImageRenderTarget`
- L150 _public enumerator_ `EVulkanAllocationMetaImageOther`
- L151 _public enumerator_ `EVulkanAllocationMetaBufferUAV`
- L152 _public enumerator_ `EVulkanAllocationMetaBufferStaging`
- L153 _public enumerator_ `EVulkanAllocationMetaBufferOther`
- L154 _public enumerator_ `EVulkanAllocationMetaSize` — keep last

#### enum `VulkanRHI::ELegacyVulkanAllocationFlags`  
`enum ELegacyVulkanAllocationFlags`  
_L156-160_
- L158 _public enumerator_ `VulkanAllocationFlagsMapped = 0x1`
- L159 _public enumerator_ `VulkanAllocationFlagsCanEvict= 0x2`

#### enum `VulkanRHI::EType`  
`enum class EType`  
_L162-166_
- L164 _public enumerator_ `Image`
- L165 _public enumerator_ `Buffer`

#### class `VulkanRHI::FDeviceMemoryAllocation`  
`class FDeviceMemoryAllocation`  
_L170-249_
- desc: An Allocation off a Device Heap. Lowest level of allocations and bounded by VkPhysicalDeviceLimits::maxMemoryAllocationCount.
- L173 _public function_ `FDeviceMemoryAllocation() : Size(0) , DeviceHandle(VK_NULL_HANDLE) , Handle(VK_NULL_HANDLE) , MappedPointer(nullptr) , MemoryTypeIndex(0) , bCanBeMapped(0) , bIsCoherent(0) , bIsCached(0) , bFreedBySystem(false) , bDedicatedMemory(0)`
- L187 _public prototype_ `void* Map(VkDeviceSize Size, VkDeviceSize Offset);`
- L188 _public prototype_ `void Unmap();`
- L190 _public function_ `inline bool CanBeMapped() const`
- L195 _public function_ `inline bool IsMapped() const`
- L200 _public function_ `inline void* GetMappedPointer()`
- L206 _public function_ `inline bool IsCoherent() const`
- L211 _public prototype_ `void FlushMappedMemory(VkDeviceSize InOffset, VkDeviceSize InSize);`
- L212 _public prototype_ `void InvalidateMappedMemory(VkDeviceSize InOffset, VkDeviceSize InSize);`
- L214 _public function_ `inline VkDeviceMemory GetHandle() const`
- L219 _public function_ `inline VkDeviceSize GetSize() const`
- L224 _public function_ `inline uint32 GetMemoryTypeIndex() const`
- L230 _protected member_ `VkDeviceSize Size;`
- L231 _protected member_ `VkDevice DeviceHandle;`
- L232 _protected member_ `VkDeviceMemory Handle;`
- L233 _protected member_ `void* MappedPointer;`
- L234 _protected member_ `uint32 MemoryTypeIndex : 8;`
- L235 _protected member_ `uint32 bCanBeMapped : 1;`
- L236 _protected member_ `uint32 bIsCoherent : 1;`
- L237 _protected member_ `uint32 bIsCached : 1;`
- L238 _protected member_ `uint32 bFreedBySystem : 1;`
- L239 _protected member_ `uint32 bDedicatedMemory : 1;`
- L244 _protected member_ `FVulkanTrackInfo Track;`
- L246 _protected prototype_ `~FDeviceMemoryAllocation();`

#### struct `VulkanRHI::FDeviceMemoryBlockKey`  
`struct FDeviceMemoryBlockKey`  
_L251-260_
- L253 _public member_ `uint32 MemoryTypeIndex;`
- L254 _public member_ `VkDeviceSize BlockSize;`
- L256 _public function_ `bool operator==(const FDeviceMemoryBlockKey& Other) const`

#### struct `VulkanRHI::FDeviceMemoryBlock`  
`struct FDeviceMemoryBlock`  
_L267-277_
- L269 _public member_ `FDeviceMemoryBlockKey Key;`
- L275 _public member_ `TArray<FFreeBlock> Allocations;`

#### struct `VulkanRHI::FDeviceMemoryBlock::FFreeBlock`  
`struct FFreeBlock`  
_L270-274_
- L272 _public member_ `FDeviceMemoryAllocation* Allocation;`
- L273 _public member_ `uint32 FrameFreed;`

#### class `VulkanRHI::FDeviceMemoryManager`  
`class FDeviceMemoryManager`  
_L282-369_
- desc: Manager of Device Heap Allocations. Calling Alloc/Free is expensive!
- L284 _private member_ `TMap<FDeviceMemoryBlockKey, FDeviceMemoryBlock> Allocations;`
- L285 _private member_ `FRHIMemoryStats MemoryStats;`
- L287 _public prototype_ `FDeviceMemoryManager();`
- L288 _public prototype_ `~FDeviceMemoryManager();`
- L290 _public prototype_ `void Init(FVulkanDevice* InDevice);`
- L292 _public prototype_ `void Deinit();`
- L294 _public prototype_ `uint32 GetEvictedMemoryProperties();`
- L296 _public function_ `inline bool HasUnifiedMemory() const`
- L301 _public function_ `inline bool SupportsMemoryless() const`
- L306 _public function_ `inline uint32 GetNumMemoryTypes() const`
- L311 _public prototype_ `bool SupportsMemoryType(VkMemoryPropertyFlags Properties) const;`
- L312 _public prototype_ `void GetPrimaryHeapStatus(uint64& OutAllocated, uint64& OutLimit);`
- L314 _public prototype_ `VkResult GetMemoryTypeFromProperties(uint32 TypeBits, VkMemoryPropertyFlags Properties, uint32* OutTypeIndex);`
- L315 _public prototype_ `VkResult GetMemoryTypeFromPropertiesExcluding(uint32 TypeBits, VkMemoryPropertyFlags Properties, uint32 ExcludeTypeIndex, uint32* OutTypeIndex);`
- L316 _public prototype_ `const VkPhysicalDeviceMemoryProperties& GetMemoryProperties() const;`
- L320 _public prototype_ `FDeviceMemoryAllocation* Alloc(bool bCanFail, VkDeviceSize AllocationSize, uint32 MemoryTypeIndex, void* DedicatedAllocateInfo, float Priority, bool bExternal, const char* File, uint32 Line);` — bCanFail means an allocation failing is not a fatal error, just returns nullptr
- L321 _public prototype_ `FDeviceMemoryAllocation* Alloc(bool bCanFail, VkDeviceSize AllocationSize, uint32 MemoryTypeBits, VkMemoryPropertyFlags MemoryPropertyFlags, void* DedicatedAllocateInfo, float Priority, bool bExternal, const char* File, uint32 Line);`
- L324 _public prototype_ `void Free(FDeviceMemoryAllocation*& Allocation);` — Sets the Allocation to nullptr
- L326 _public prototype_ `uint64 GetTotalMemory(bool bGPU) const;`
- L327 _public prototype_ `VkDeviceSize GetBaseHeapSize(uint32 HeapIndex) const;`
- L328 _public prototype_ `uint32 GetHeapIndex(uint32 MemoryTypeIndex);`
- L330 _public prototype_ `void UpdateMemoryProperties();`
- L331 _public function_ `FRHIMemoryStats GetRHIMemoryStats() const`
- L334 _protected prototype_ `void FreeInternal(FDeviceMemoryAllocation* Allocation);`
- L335 _protected prototype_ `void TrimMemory(bool bFullTrim);`
- L337 _protected prototype_ `void GetMemoryDump(TArray<FResourceHeapStats>& OutDeviceHeapsStats);`
- L338 _protected prototype_ `void DumpMemory();`
- L339 _protected prototype_ `void PrintMemInfo() const;`
- L341 _protected member_ `double MemoryUpdateTime;`
- L342 _protected member_ `VkPhysicalDeviceMemoryBudgetPropertiesEXT MemoryBudget;`
- L343 _protected member_ `VkPhysicalDeviceMemoryProperties MemoryProperties;`
- L344 _protected member_ `VkDevice DeviceHandle;`
- L345 _protected member_ `FVulkanDevice* Device;`
- L346 _protected member_ `uint32 NumAllocations;`
- L347 _protected member_ `uint32 PeakNumAllocations;`
- L348 _protected member_ `bool bHasUnifiedMemory;`
- L349 _protected member_ `bool bSupportsMemoryless;`
- L364 _protected member_ `TArray<FHeapInfo> HeapInfos;`
- L366 _protected member_ `int32 PrimaryHeapIndex;` — memory usage of this heap will decide when to evict.
- L368 _protected member_ `FCriticalSection DeviceMemLock;`

#### struct `VulkanRHI::FDeviceMemoryManager::FHeapInfo`  
`struct FHeapInfo`  
_L351-362_
- L353 _public member_ `VkDeviceSize UsedSize;`
- L354 _public member_ `VkDeviceSize PeakSize;`
- L355 _public member_ `TArray<FDeviceMemoryAllocation*> Allocations;`
- L357 _public function_ `FHeapInfo() : UsedSize(0), PeakSize(0)`

#### struct `VulkanRHI::FRange`  
`struct FRange`  
_L371-397_
- L373 _public member_ `uint32 Offset;`
- L374 _public member_ `uint32 Size;`
- L376 _public function_ `inline bool operator<(const FRange& In) const`
- L381 _public prototype_ `static void JoinConsecutiveRanges(TArray<FRange>& Ranges);`
- L384 _public prototype_ `static int32 InsertAndTryToMerge(TArray<FRange>& Ranges, const FRange& Item, int32 ProposedIndex);` — Tries to insert the item so it has index ProposedIndex, but may end up merging it with neighbors
- L387 _public prototype_ `static int32 AppendAndTryToMerge(TArray<FRange>& Ranges, const FRange& Item);` — Tries to append the item to the end but may end up merging it with the neighbor
- L390 _public prototype_ `static void AllocateFromEntry(TArray<FRange>& Ranges, int32 Index, uint32 SizeToAllocate);` — Attempts to allocate from an entry - can remove it if it was used up
- L393 _public prototype_ `static void SanityCheck(TArray<FRange>& Ranges);` — Sanity checks an array of ranges
- L396 _public prototype_ `static int32 Add(TArray<FRange>& Ranges, const FRange& Item);` — Adds to the array while maintaing the sort.

#### struct `VulkanRHI::FVulkanPageSizeBucket`  
`struct FVulkanPageSizeBucket`  
_L399-409_
- L401 _public member_ `uint64 AllocationMax;`
- L402 _public member_ `uint32 PageSize;`
- L408 _public member_ `uint32 BucketMask;`

#### enum `VulkanRHI::FVulkanPageSizeBucket::(anonymous)`  
``  
_L404-407_

#### class `VulkanRHI::FVulkanAllocation`  
`class FVulkanAllocation`  
_L415-463_
- desc: Holds a reference to -any- vulkan gpu allocation !Intentionally not reference counted !User must call Free exactly once
- L418 _public prototype_ `FVulkanAllocation();`
- L419 _public prototype_ `~FVulkanAllocation();`
- L420 _public prototype_ `void Init(EVulkanAllocationType Type, EVulkanAllocationMetaType MetaType, uint64 Handle, uint32 InSize, uint32 AlignedOffset, uint32 AllocatorIndex, uint32 AllocationIndex, uint32 BufferId);`
- L421 _public prototype_ `void Free(FVulkanDevice& Device);`
- L422 _public prototype_ `void Swap(FVulkanAllocation& Other);`
- L423 _public prototype_ `void Reference(const FVulkanAllocation& Other);` — point to other, but don't take ownership
- L424 _public prototype_ `bool HasAllocation() const;`
- L426 _public prototype_ `void Disown();` — disown & own should be used if ownership is transferred.
- L427 _public prototype_ `void Own();`
- L428 _public prototype_ `bool IsValid() const;`
- L430 _public member_ `uint64 VulkanHandle = 0;`
- L431 _public member_ `uint32 HandleId = 0;`
- L432 _public member_ `uint32 Size = 0;`
- L433 _public member_ `uint32 Offset = 0;`
- L434 _public member_ `uint32 AllocationIndex = 0;`
- L435 _public member_ `uint16 AllocatorIndex = 0;`
- L436 _public member_ `EVulkanAllocationMetaType MetaType = EVulkanAllocationMetaUnknown;`
- L437 _public member_ `uint8 Type : 5;`
- L438 _public member_ `uint8 bHasOwnership : 1;`
- L439 _public member_ `uint8 bTransient : 1;`
- L440 _public member_ `uint8 bTempBlockAllocator : 1;`
- L443 _public function_ `inline EVulkanAllocationType GetType() const`
- L447 _public function_ `inline void SetType(EVulkanAllocationType InType)`
- L453 _public prototype_ `void* GetMappedPointer(FVulkanDevice* Device);` — helper functions
- L454 _public prototype_ `void FlushMappedMemory(FVulkanDevice* Device);`
- L455 _public prototype_ `void InvalidateMappedMemory(FVulkanDevice* Device);`
- L456 _public prototype_ `VkBuffer GetBufferHandle() const;`
- L457 _public prototype_ `uint32 GetBufferAlignment(FVulkanDevice* Device) const;`
- L458 _public prototype_ `VkDeviceMemory GetDeviceMemoryHandle(FVulkanDevice* Device) const;`
- L459 _public prototype_ `FVulkanSubresourceAllocator* GetSubresourceAllocator(FVulkanDevice* Device) const;`
- L460 _public prototype_ `VkMemoryPropertyFlags GetMemoryPropertyFlags(FVulkanDevice* Device) const;`
- L461 _public prototype_ `void BindBuffer(FVulkanDevice* Device, VkBuffer Buffer);`
- L462 _public prototype_ `void BindImage(FVulkanDevice* Device, VkImage Image);`

#### struct `VulkanRHI::FVulkanAllocationInternal`  
`struct FVulkanAllocationInternal`  
_L467-500_
- L478 _public member_ `int State = EUNUSED;`
- L479 _public prototype_ `void Init(const FVulkanAllocation& Alloc, FVulkanEvictable* InAllocationOwner, uint32 AllocationOffset, uint32 AllocationSize, uint32 Alignment);`
- L481 _public member_ `EVulkanAllocationType Type = EVulkanAllocationEmpty;`
- L482 _public member_ `EVulkanAllocationMetaType MetaType = EVulkanAllocationMetaUnknown;`
- L484 _public member_ `uint32 Size = 0;`
- L485 _public member_ `uint32 AllocationSize = 0;`
- L486 _public member_ `uint32 AllocationOffset = 0;`
- L487 _public member_ `FVulkanEvictable* AllocationOwner = 0;`
- L488 _public member_ `uint32 Alignment = 0;`
- L490 _public member_ `int32 NextFree = -1;`
- L493 _public member_ `FVulkanTrackInfo Track;`
- L496 _public member_ `uint64 LLMTrackerID;`
- L497 _public function_ `void SetLLMTrackerID(uint64 InTrackerID)`
- L498 _public function_ `uint64 GetLLMTrackerID()`

#### enum `VulkanRHI::FVulkanAllocationInternal::(anonymous)`  
``  
_L470-476_

#### class `VulkanRHI::FVulkanSubresourceAllocator`  
`class FVulkanSubresourceAllocator`  
_L504-621_
- L509 _public prototype_ `FVulkanSubresourceAllocator(EVulkanAllocationType InType, FMemoryManager* InOwner, uint8 InSubResourceAllocatorFlags, FDeviceMemoryAllocation* InDeviceMemoryAllocation, uint32 InMemoryTypeIndex, VkMemoryPropertyFlags InMemoryPropertyFlags, uint32 InAlignment, VkBuffer InBuffer, uint32 InBufferSize, uint32 InBufferId, VkBufferUsageFlags InBufferUsageFlags, int32 InPoolSizeIndex);`
- L514 _public prototype_ `FVulkanSubresourceAllocator(EVulkanAllocationType InType, FMemoryManager* InOwner, uint8 InSubResourceAllocatorFlags, FDeviceMemoryAllocation* InDeviceMemoryAllocation, uint32 InMemoryTypeIndex, uint32 BufferId = 0xffffffff);`
- L517 _public prototype_ `~FVulkanSubresourceAllocator();`
- L519 _public prototype_ `void Destroy(FVulkanDevice* Device);`
- L520 _public prototype_ `bool TryAllocate2(FVulkanAllocation& OutAllocation, FVulkanEvictable* Owner, uint32 InSize, uint32 InAlignment, EVulkanAllocationMetaType InMetaType, const char* File, uint32 Line);`
- L521 _public prototype_ `void Free(FVulkanAllocation& Allocation);`
- L523 _public function_ `uint32 GetAlignment() const`
- L528 _public function_ `void* GetMappedPointer()`
- L533 _public prototype_ `void Flush(VkDeviceSize Offset, VkDeviceSize AllocationSize);`
- L534 _public prototype_ `void Invalidate(VkDeviceSize Offset, VkDeviceSize AllocationSize);`
- L535 _public function_ `uint32 GetMaxSize() const`
- L536 _public function_ `uint32 GetUsedSize() const`
- L538 _public function_ `uint32 GetMemoryTypeIndex() const`
- L543 _public function_ `uint32 GetHandleId() const`
- L547 _public function_ `FDeviceMemoryAllocation* GetMemoryAllocation()`
- L551 _public function_ `EVulkanAllocationType GetType()`
- L553 _public prototype_ `TArrayView<uint32> GetMemoryUsed();`
- L554 _public prototype_ `uint32 GetNumSubAllocations();`
- L556 _public function_ `uint8 GetSubresourceAllocatorFlags() const`
- L560 _public function_ `uint32 GetId() const`
- L564 _public function_ `bool GetIsDefragging() const`
- L570 _protected function_ `void SetIsDefragging(bool bInIsDefragging)`
- L571 _protected prototype_ `void DumpFullHeap();`
- L572 _protected prototype_ `int32 DefragTick(FVulkanDevice& Device, const FVulkanContextArray& Contexts, FVulkanResourceHeap* Heap, uint32 Count);`
- L573 _protected prototype_ `bool CanDefrag();`
- L574 _protected prototype_ `uint64 EvictToHost(FVulkanDevice& Device, const FVulkanContextArray& Contexts);`
- L575 _protected prototype_ `void SetFreePending(FVulkanAllocation& Allocation);`
- L576 _protected prototype_ `void FreeInternalData(int32 Index);`
- L577 _protected prototype_ `int32 AllocateInternalData();`
- L579 _protected member_ `uint32 MemoryUsed[EVulkanAllocationMetaSize];`
- L581 _protected member_ `EVulkanAllocationType Type;`
- L582 _protected member_ `FMemoryManager* Owner;`
- L583 _protected member_ `const uint32 MemoryTypeIndex;`
- L584 _protected member_ `VkMemoryPropertyFlags MemoryPropertyFlags;`
- L585 _protected member_ `FDeviceMemoryAllocation* MemoryAllocation;`
- L586 _protected member_ `uint32 MaxSize;`
- L587 _protected member_ `uint32 Alignment;`
- L588 _protected member_ `uint32 FrameFreed;`
- L589 _protected member_ `uint32 LastDefragFrame = 0;`
- L590 _protected member_ `int64 UsedSize;`
- L591 _protected member_ `VkBufferUsageFlags BufferUsageFlags;`
- L592 _protected member_ `VkBuffer Buffer;`
- L593 _protected member_ `uint32 BufferId;`
- L594 _protected member_ `int32 PoolSizeIndex;`
- L595 _protected member_ `uint32 AllocatorIndex;`
- L596 _protected member_ `uint8 SubresourceAllocatorFlags;`
- L597 _protected member_ `uint8 BucketId;`
- L598 _protected member_ `bool bIsEvicting = false;`
- L599 _protected member_ `bool bLocked = false;`
- L600 _protected member_ `bool bIsDefragging = false;`
- L602 _protected member_ `uint32 NumSubAllocations = 0;`
- L603 _protected member_ `uint32 AllocCalls = 0;`
- L604 _protected member_ `uint32 FreeCalls = 0;`
- L607 _protected member_ `TArray<FRange> FreeList;` — List of free ranges
- L608 _protected prototype_ `bool JoinFreeBlocks();`
- L609 _protected function_ `uint32 GetAllocatorIndex()`
- L616 _protected member_ `FVulkanTrackInfo Track;`
- L618 _protected member_ `TArray<FVulkanAllocationInternal> InternalData;`
- L619 _protected member_ `int32 InternalFreeList= -1;`
- L620 _protected member_ `FCriticalSection SubresourceAllocatorCS;`

#### class `VulkanRHI::FVulkanResourceHeap`  
`class FVulkanResourceHeap`  
_L626-695_
- desc: A set of Device Allocations (Heap Pages) for a specific memory type. This handles pooling allocations inside memory pages to avoid doing allocations directly off the device's heaps
- L629 _public prototype_ `FVulkanResourceHeap(FMemoryManager* InOwner, uint32 InMemoryTypeIndex, uint32 InOverridePageSize = 0);`
- L630 _public prototype_ `~FVulkanResourceHeap();`
- L632 _public prototype_ `void FreePage(FVulkanSubresourceAllocator* InPage);`
- L633 _public prototype_ `void ReleasePage(FVulkanSubresourceAllocator* InPage);`
- L637 _public function_ `inline FMemoryManager* GetOwner()`
- L642 _public function_ `inline bool IsHostCachedSupported() const`
- L647 _public function_ `inline bool IsLazilyAllocatedSupported() const`
- L652 _public function_ `inline uint32 GetMemoryTypeIndex() const`
- L657 _public prototype_ `uint64 EvictOne(FVulkanDevice& Device, const FVulkanContextArray& Contexts);`
- L658 _public prototype_ `void DefragTick(FVulkanDevice& Device, const FVulkanContextArray& Contexts, uint32 Count);`
- L659 _public prototype_ `void DumpMemory(FResourceHeapStats& Stats);`
- L661 _public prototype_ `void SetDefragging(FVulkanSubresourceAllocator* Allocator);`
- L662 _public prototype_ `bool GetIsDefragging(FVulkanSubresourceAllocator* Allocator);`
- L663 _public prototype_ `uint32 GetPageSizeBucket(FVulkanPageSizeBucket& BucketOut, EType Type, uint32 AllocationSize, bool bForceSingleAllocation);`
- L669 _protected member_ `TArray<FVulkanPageSizeBucket, TFixedAllocator<MAX_BUCKETS> > PageSizeBuckets;`
- L670 _protected prototype_ `uint32 GetPageSize();`
- L671 _protected member_ `FMemoryManager* Owner;`
- L672 _protected member_ `const uint16 MemoryTypeIndex;`
- L673 _protected member_ `const uint16 HeapIndex;`
- L675 _protected member_ `bool bIsHostCachedSupported;`
- L676 _protected member_ `bool bIsLazilyAllocatedSupported;`
- L677 _protected member_ `uint8 DefragCountDown = 0;`
- L679 _protected member_ `uint32 OverridePageSize;`
- L681 _protected member_ `uint32 PeakPageSize;`
- L682 _protected member_ `uint64 UsedMemory;`
- L683 _protected member_ `uint32 PageIDCounter;`
- L685 _protected member_ `FCriticalSection PagesLock;`
- L686 _protected member_ `TArray<FVulkanSubresourceAllocator*> ActivePages[MAX_BUCKETS];`
- L687 _protected member_ `TArray<FVulkanSubresourceAllocator*> UsedDedicatedImagePages;`
- L689 _protected prototype_ `bool TryRealloc(FVulkanAllocation& OutAllocation, FVulkanEvictable* AllocationOwner, EType Type, uint32 Size, uint32 Alignment, EVulkanAllocationMetaType MetaType);`
- L690 _protected prototype_ `bool AllocateResource(FVulkanAllocation& OutAllocation, FVulkanEvictable* AllocationOwner, EType Type, uint32 Size, uint32 Alignment, bool bMapAllocation, bool bForceSeparateAllocation, EVulkanAllocationMetaType MetaType, bool bExternal, const char* File, uint32 Line);`
- L691 _protected prototype_ `bool AllocateDedicatedImage(FVulkanAllocation& OutAllocation, FVulkanEvictable* AllocationOwner, VkImage Image, uint32 Size, uint32 Alignment, EVulkanAllocationMetaType MetaType, bool bExternal, const char* File, uint32 Line);`

#### enum `VulkanRHI::FVulkanResourceHeap::(anonymous)`  
`enum`  
_L666-668_

#### enum `VulkanRHI::EVulkanFreeFlags`  
`enum EVulkanFreeFlags`  
_L697-701_
- L699 _public enumerator_ `EVulkanFreeFlag_None = 0x0`
- L700 _public enumerator_ `EVulkanFreeFlag_DontDefer = 0x1`

#### enum `VulkanRHI::EVulkanAllocationFlags`  
`enum class EVulkanAllocationFlags : uint16`  
_L705-720_
- desc: Allocation flags to account for conditions not covered by vkGet*MemoryRequirements or resource usage flags
- L707 _public enumerator_ `None = 0x0000`
- L709 _public enumerator_ `HostVisible = 0x0001` — Will be written from CPU, will likely contain the HOST_VISIBLE + HOST_COHERENT flags
- L710 _public enumerator_ `HostCached = 0x0002` — Will be used for readback, will likely contain the HOST_CACHED flag.  Implies HostVisible.
- L711 _public enumerator_ `PreferBAR = 0x0004` — Will be allocated from a HOST_VISIBLE + DEVICE_LOCAL heap if available and possible (HOST_VISIBLE if not)
- L713 _public enumerator_ `Dedicated = 0x0008` — Will not share a memory block with other resources
- L714 _public enumerator_ `External = 0x0010` — To be used with VK_KHR_external_memory
- L715 _public enumerator_ `Memoryless = 0x0020` — Will use LAZILY_ALLOCATED
- L716 _public enumerator_ `Protected = 0x0040` — Will use PROTECTED
- L718 _public enumerator_ `NoError = 0x0080` — OOM is not fatal, return an invalid allocation
- L719 _public enumerator_ `AutoBind = 0x0100` — Will automatically bind the allocation to the supplied VkBuffer/VkImage, avoids an extra lock to bind separately

#### class `VulkanRHI::FMemoryManager`  
`class FMemoryManager`  
_L724-882_
- desc: Manages heaps and their interactions
- L729 _public prototype_ `FMemoryManager(FVulkanDevice& InDevice);`
- L730 _public prototype_ `~FMemoryManager();`
- L732 _public prototype_ `void Init();`
- L733 _public prototype_ `void Deinit();`
- L735 _public function_ `FVulkanDevice& GetDevice()`
- L740 _public prototype_ `static uint32 CalculateBufferAlignment(FVulkanDevice& InDevice, EBufferUsageFlags InUEUsage, bool bZeroSize);`
- L741 _public prototype_ `static float CalculateBufferPriority(const VkBufferUsageFlags BufferUsageFlags);`
- L743 _public prototype_ `void FreeVulkanAllocation(FVulkanAllocation& Allocation, EVulkanFreeFlags FreeFlags = EVulkanFreeFlag_None);`
- L744 _public prototype_ `void FreeVulkanAllocationPooledBuffer(FVulkanAllocation& Allocation);`
- L745 _public prototype_ `void FreeVulkanAllocationBuffer(FVulkanAllocation& Allocation);`
- L746 _public prototype_ `void FreeVulkanAllocationImage(FVulkanAllocation& Allocation);`
- L747 _public prototype_ `void FreeVulkanAllocationImageDedicated(FVulkanAllocation& Allocation);`
- L750 _public prototype_ `bool AllocateBufferPooled(FVulkanAllocation& Allocation, FVulkanEvictable* AllocationOwner, uint32 Size, uint32 MinAlignment, VkBufferUsageFlags BufferUsageFlags, VkMemoryPropertyFlags MemoryPropertyFlags, EVulkanAllocationMetaType MetaType, const char* File, uint32 Line);` — Legacy calls
- L751 _public prototype_ `bool AllocateImageMemory(FVulkanAllocation& Allocation, FVulkanEvictable* AllocationOwner, const VkMemoryRequirements& MemoryReqs, VkMemoryPropertyFlags MemoryPropertyFlags, EVulkanAllocationMetaType MetaType, bool bExternal, const char* File, uint32 Line);`
- L752 _public prototype_ `bool AllocateDedicatedImageMemory(FVulkanAllocation& Allocation, FVulkanEvictable* AllocationOwner, VkImage Image, VkMemoryPropertyFlags MemoryPropertyFlags, EVulkanAllocationMetaType MetaType, bool bExternal, bool bForceDedicatedAllocation, const char* File, uint32 Line);`
- L754 _private prototype_ `bool AllocateBufferMemory(FVulkanAllocation& Allocation, FVulkanEvictable* AllocationOwner, const VkMemoryRequirements& MemoryReqs, VkMemoryPropertyFlags MemoryPropertyFlags, EVulkanAllocationMetaType MetaType, bool bExternal, bool bForceSeparateAllocation, const char* File, uint32 Line);`
- L758 _public prototype_ `bool AllocateBufferMemory(FVulkanAllocation& OutAllocation, VkBuffer InBuffer, EVulkanAllocationFlags InAllocFlags, const TCHAR* InDebugName, uint32 InForceMinAlignment = 1);`
- L760 _public prototype_ `void RegisterSubresourceAllocator(FVulkanSubresourceAllocator* SubresourceAllocator);`
- L761 _public prototype_ `void UnregisterSubresourceAllocator(FVulkanSubresourceAllocator* SubresourceAllocator);`
- L762 _public prototype_ `bool ReleaseSubresourceAllocator(FVulkanSubresourceAllocator* SubresourceAllocator);`
- L765 _public prototype_ `void ReleaseFreedPages(const FVulkanContextArray& Contexts);`
- L766 _public prototype_ `void DumpMemory(bool bFullDump = true);`
- L769 _public prototype_ `void AllocUniformBuffer(FVulkanAllocation& OutAllocation, uint32 Size);`
- L770 _public prototype_ `void FreeUniformBuffer(FVulkanAllocation& InAllocation);`
- L772 _public prototype_ `void HandleOOM(bool bCanResume = false, VkResult Result = VK_SUCCESS, uint64 AllocationSize = 0, uint32 MemoryTypeIndex = 0);`
- L773 _public prototype_ `bool UpdateEvictThreshold(bool bLog);`
- L776 _protected member_ `FVulkanDevice& Device;`
- L777 _protected member_ `FDeviceMemoryManager* DeviceMemoryManager;`
- L778 _protected member_ `TArray<FVulkanResourceHeap*> ResourceTypeHeaps;`
- L802 _protected member_ `constexpr static uint32 PoolSizes[(int32)EPoolSizes::SizesCount] = {`
- L815 _protected member_ `constexpr static uint32 BufferSizes[(int32)EPoolSizes::SizesCount + 1] = {`
- L829 _protected function_ `EPoolSizes GetPoolTypeForAlloc(uint32 Size, uint32 Alignment)`
- L846 _protected member_ `FCriticalSection UsedFreeBufferAllocationsLock;`
- L847 _protected member_ `TArray<FVulkanSubresourceAllocator*> UsedBufferAllocations[(int32)EPoolSizes::SizesCount + 1];`
- L848 _protected member_ `TArray<FVulkanSubresourceAllocator*> FreeBufferAllocations[(int32)EPoolSizes::SizesCount + 1];`
- L850 _protected member_ `FRWLock AllBufferAllocationsLock;` — protects against resizing of array (RenderThread<->RHIThread)
- L851 _protected member_ `TArray<FVulkanSubresourceAllocator*> AllBufferAllocations;`
- L852 _protected member_ `PTRINT AllBufferAllocationsFreeListHead = (PTRINT)-1;`
- L853 _protected function_ `inline FVulkanSubresourceAllocator* GetSubresourceAllocator(const uint32 AllocatorIndex)`
- L859 _protected member_ `uint64 PendingEvictBytes = 0;`
- L860 _protected member_ `bool bIsEvicting = false;`
- L861 _protected member_ `bool bWantEviction = false;`
- L865 _protected prototype_ `void ReleaseFreedResources(bool bImmediately);`
- L866 _protected prototype_ `void DestroyResourceAllocations();`
- L878 _protected member_ `} UBAllocations;`
- L880 _protected prototype_ `void ProcessPendingUBFreesNoLock(bool bForce);`
- L881 _protected prototype_ `void ProcessPendingUBFrees(bool bForce);`

#### enum `VulkanRHI::FMemoryManager::(anonymous)`  
``  
_L781-784_

#### enum `VulkanRHI::FMemoryManager::EPoolSizes`  
`enum class EPoolSizes : uint8`  
_L788-800_
- desc: pool sizes that we support
- L792 _public enumerator_ `E128` — E32, E64,
- L793 _public enumerator_ `E256`
- L794 _public enumerator_ `E512`
- L795 _public enumerator_ `E1k`
- L796 _public enumerator_ `E2k`
- L797 _public enumerator_ `E8k`
- L798 _public enumerator_ `E16k`
- L799 _public enumerator_ `SizesCount`

#### struct `VulkanRHI::FMemoryManager::FUBPendingFree`  
`struct FUBPendingFree`  
_L867-871_
- L869 _public member_ `FVulkanAllocation Allocation;`
- L870 _public member_ `int64 Frame = 0;`

#### struct `VulkanRHI::FMemoryManager::(anonymous)`  
``  
_L874-878_

#### class `VulkanRHI::FStagingBuffer`  
`class FStagingBuffer : public FRefCountedObject`  
_L884-914_
- inherits: `FRefCountedObject`
- L887 _public prototype_ `FStagingBuffer(FVulkanDevice* InDevice);`
- L889 _public prototype_ `VkBuffer GetHandle() const;`
- L890 _public prototype_ `void* GetMappedPointer();`
- L891 _public prototype_ `uint32 GetSize() const;`
- L892 _public prototype_ `VkDeviceMemory GetDeviceMemoryHandle() const;`
- L893 _public prototype_ `void FlushMappedMemory();`
- L894 _public prototype_ `void InvalidateMappedMemory();`
- L897 _public member_ `FVulkanTrackInfo Track;`
- L901 _protected member_ `FVulkanDevice* Device;`
- L902 _protected member_ `FVulkanAllocation Allocation;`
- L904 _protected member_ `VkBuffer Buffer;`
- L905 _protected member_ `VkMemoryPropertyFlagBits MemoryReadFlags;`
- L906 _protected member_ `uint32 BufferSize;`
- L909 _protected prototype_ `virtual ~FStagingBuffer();` — Owner maintains lifetime
- L911 _protected prototype_ `void Destroy();`

#### class `VulkanRHI::FStagingManager`  
`class FStagingManager`  
_L916-959_
- L919 _public prototype_ `FStagingManager();`
- L920 _public prototype_ `~FStagingManager();`
- L922 _public function_ `void Init(FVulkanDevice* InDevice)`
- L927 _public prototype_ `void Deinit();`
- L929 _public prototype_ `FStagingBuffer* AcquireBuffer(uint32 Size, VkBufferUsageFlags InUsageFlags = VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VkMemoryPropertyFlagBits InMemoryReadFlags = VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);`
- L932 _public prototype_ `void ReleaseBuffer(FVulkanContextCommon* Context, FStagingBuffer*& StagingBuffer);` — Sets pointer to nullptr
- L934 _public prototype_ `void ProcessPendingFree(bool bImmediately, bool bFreeToOS);`
- L936 _public prototype_ `void GetMemoryDump(FResourceHeapStats& Stats);`
- L937 _public prototype_ `void DumpMemory();`
- L942 _protected member_ `FCriticalSection StagingLock;`
- L944 _protected member_ `TArray<FStagingBuffer*> UsedStagingBuffers;`
- L945 _protected member_ `TMap<FVulkanSyncPointRef, TArray<FStagingBuffer*>> PendingFreeStagingBuffers;`
- L951 _protected member_ `TArray<FFreeEntry> FreeStagingBuffers;`
- L953 _protected member_ `uint64 PeakUsedMemory = 0;`
- L954 _protected member_ `uint64 UsedMemory = 0;`
- L956 _protected prototype_ `void ProcessPendingFreeNoLock(bool bImmediately, bool bFreeToOS);`
- L958 _protected member_ `FVulkanDevice* Device = nullptr;`

#### struct `VulkanRHI::FStagingManager::FFreeEntry`  
`struct FFreeEntry`  
_L946-950_
- L948 _public member_ `FStagingBuffer* StagingBuffer;`
- L949 _public member_ `uint32 FrameNumber;`

#### class `VulkanRHI::FTempBlockAllocator`  
`class FTempBlockAllocator`  
_L962-1014_
- desc: Simple temp allocation blocks used for volatile allocations
- L984 _public prototype_ `FTempBlockAllocator(FVulkanDevice& InDevice, uint32 InBlockSize, uint32 InBlockAlignment, VkBufferUsageFlags InBufferUsage);`
- L985 _public prototype_ `virtual ~FTempBlockAllocator();`
- L987 _public prototype_ `uint8* Alloc(uint32 InSize, FVulkanContextCommon& Context, VkDescriptorBufferBindingInfoEXT& OutBindingInfo, VkDeviceSize& OutOffset);`
- L988 _public prototype_ `uint8* Alloc(uint32 InSize, uint32 InAlignment, FVulkanContextCommon* Context, FVulkanAllocation& OutAllocation, VkDescriptorAddressInfoEXT* OutDescriptorAddressInfo = nullptr);`
- L989 _public prototype_ `uint8* Alloc(uint32 InSize, FVulkanContextCommon& Context, VkStridedDeviceAddressRegionKHR* OutStridedDeviceAddressRegion);`
- L991 _public function_ `uint8* Alloc(uint32 InSize, uint32 InAlignment, FVulkanContextCommon& Context, FVulkanAllocation& OutAllocation, VkDescriptorAddressInfoEXT* OutDescriptorAddressInfo = nullptr)`
- L996 _public prototype_ `void FreeReference(const FVulkanAllocation& InAllocation);`
- L998 _public prototype_ `void UpdateBlocks();`
- L1001 _protected prototype_ `FTempMemoryBlock* AllocBlock();`
- L1002 _protected prototype_ `FInternalAlloc InternalAlloc(uint32 InSize, FVulkanContextCommon* Context);`
- L1004 _protected member_ `FVulkanDevice& Device;`
- L1006 _protected member_ `const uint32 BlockSize;`
- L1007 _protected member_ `const uint32 BlockAlignment;`
- L1008 _protected member_ `const VkBufferUsageFlags BufferUsage;`
- L1010 _protected member_ `FTempMemoryBlock* CurrentBlock = nullptr;`
- L1011 _protected member_ `TArray<FTempMemoryBlock*> BusyBlocks;`
- L1012 _protected member_ `TArray<FTempMemoryBlock*> AvailableBlocks;`
- L1013 _protected member_ `FRWLock RWLock;`

#### struct `VulkanRHI::FTempBlockAllocator::FTempMemoryBlock`  
`struct FTempMemoryBlock`  
_L965-976_
- L967 _public member_ `FVulkanAllocation Allocation;`
- L968 _public member_ `VkBuffer Buffer = 0;`
- L969 _public member_ `uint8* MappedPointer = 0;`
- L970 _public member_ `VkDeviceAddress BufferAddress = 0;`
- L973 _public member_ `TArray<FVulkanSyncPointRef> SyncPoints;` — Used by owners to suballocate
- L974 _public member_ `std::atomic<uint32> References = 0;`
- L975 _public member_ `std::atomic<uint32> CurrentOffset = 0;`

#### struct `VulkanRHI::FTempBlockAllocator::FInternalAlloc`  
`struct FInternalAlloc`  
_L978-982_
- L980 _public member_ `FTempMemoryBlock* Block = nullptr;`
- L981 _public member_ `uint32 Offset = 0;`

#### struct `FVulkanCustomMemManager`  
`struct FVulkanCustomMemManager`  
_L1020-1044_
- L1022 _public prototype_ `static VKAPI_ATTR void* Alloc(void* UserData, size_t Size, size_t Alignment, VkSystemAllocationScope AllocScope);`
- L1023 _public prototype_ `static VKAPI_ATTR void Free(void* pUserData, void* pMem);`
- L1024 _public prototype_ `static VKAPI_ATTR void* Realloc(void* pUserData, void* pOriginal, size_t size, size_t alignment, VkSystemAllocationScope allocScope);`
- L1025 _public prototype_ `static VKAPI_ATTR void InternalAllocationNotification(void* pUserData, size_t size, VkInternalAllocationType allocationType, VkSystemAllocationScope allocationScope);`
- L1026 _public prototype_ `static VKAPI_ATTR void InternalFreeNotification(void* pUserData, size_t size, VkInternalAllocationType allocationType, VkSystemAllocationScope allocationScope);`
- L1028 _public prototype_ `FVulkanCustomMemManager();`
- L1041 _public member_ `TStaticArray<FType, VK_SYSTEM_ALLOCATION_SCOPE_RANGE_SIZE> Types;`
- L1043 _public prototype_ `static FType& GetType(void* pUserData, VkSystemAllocationScope AllocScope);`

#### enum `FVulkanCustomMemManager::(anonymous)`  
``  
_L1031-1033_

#### struct `FVulkanCustomMemManager::FType`  
`struct FType`  
_L1035-1040_
- L1037 _public member_ `size_t UsedMemory = 0;`
- L1038 _public member_ `size_t MaxAllocSize = 0;`
- L1039 _public member_ `TMap<void*, size_t> Allocs;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API VULKANRHI_API`
- L19 _macro_ `#define VULKAN_MEMORY_TRACK 1`
- L21 _macro_ `#define VULKAN_MEMORY_TRACK 0`
- L25 _macro_ `#define VULKAN_MEMORY_LOW_PRIORITY 0.f`
- L26 _macro_ `#define VULKAN_MEMORY_MEDIUM_PRIORITY 0.5f`
- L27 _macro_ `#define VULKAN_MEMORY_HIGHER_PRIORITY 0.75f`
- L28 _macro_ `#define VULKAN_MEMORY_HIGHEST_PRIORITY 1.f`
- L40 _typedef_ `using FVulkanSyncPointRef = TRefCountPtr<FVulkanSyncPoint>;`
- L43 _macro_ `#define VULKAN_TRACK_OBJECT_CREATE(Type, Ptr) do{}while(0)`
- L44 _macro_ `#define VULKAN_TRACK_OBJECT_DELETE(Type, Ptr) do{}while(0)`
- L46 _macro_ `#define VULKAN_TRACK_OBJECT_CREATE(Type, Ptr) do{TVulkanTrackBase<Type>::Add(Ptr);}while(0)`
- L47 _macro_ `#define VULKAN_TRACK_OBJECT_DELETE(Type, Ptr) do{TVulkanTrackBase<Type>::Remove(Ptr);}while(0)`
- L83 _member_ `template<typename Type> FCriticalSection TVulkanTrackBase<Type>::Lock;` (scope `TVulkanTrackBase<Type>`)
- L85 _member_ `template<typename Type> TSet<Type*> TVulkanTrackBase<Type>::Objects;` (scope `TVulkanTrackBase<Type>`)
- L88 _namespace_ `namespace VulkanRHI`
- L127 _externvar_ `extern EDelayAcquireImageType GVulkanDelayAcquireImage;`
- L129 _externvar_ `extern int32 GVulkanUseBufferBinning;`
- L131 _namespace_ `namespace VulkanRHI`
- L262 _function_ `FORCEINLINE uint32 GetTypeHash(const FDeviceMemoryBlockKey& BlockKey)` (scope `VulkanRHI`)
- L405 _enumerator_ `BUCKET_MASK_IMAGE=0x1` (scope `VulkanRHI::FVulkanPageSizeBucket::__anond1bb0e760103`)
- L406 _enumerator_ `BUCKET_MASK_BUFFER=0x2` (scope `VulkanRHI::FVulkanPageSizeBucket::__anond1bb0e760103`)
- L471 _enumerator_ `EUNUSED` (scope `VulkanRHI::FVulkanAllocationInternal::__anond1bb0e760203`)
- L472 _enumerator_ `EALLOCATED` (scope `VulkanRHI::FVulkanAllocationInternal::__anond1bb0e760203`)
- L473 _enumerator_ `EFREED` (scope `VulkanRHI::FVulkanAllocationInternal::__anond1bb0e760203`)
- L474 _enumerator_ `EFREEPENDING` (scope `VulkanRHI::FVulkanAllocationInternal::__anond1bb0e760203`)
- L475 _enumerator_ `EFREEDISCARDED` (scope `VulkanRHI::FVulkanAllocationInternal::__anond1bb0e760203`) — if a defrag happens with a pending free, its put into this state, so we can ignore the deferred delete once it happens.
- L667 _enumerator_ `MAX_BUCKETS = 5` (scope `VulkanRHI::FVulkanResourceHeap::__anond1bb0e760303`)
- L721 _prototype_ `ENUM_CLASS_FLAGS(EVulkanAllocationFlags);` (scope `VulkanRHI`)
- L782 _enumerator_ `BufferAllocationSize = 1 * 1024 * 1024` (scope `VulkanRHI::FMemoryManager::__anond1bb0e760403`)
- L783 _enumerator_ `UniformBufferAllocationSize = 2 * 1024 * 1024` (scope `VulkanRHI::FMemoryManager::__anond1bb0e760403`)
- L875 _member_ `FCriticalSection CS;` (scope `VulkanRHI::FMemoryManager::__anond1bb0e760508`)
- L876 _member_ `TArray<FUBPendingFree> PendingFree;` (scope `VulkanRHI::FMemoryManager::__anond1bb0e760508`)
- L877 _member_ `uint32 Peak = 0;` (scope `VulkanRHI::FMemoryManager::__anond1bb0e760508`)
- L1032 _enumerator_ `VK_SYSTEM_ALLOCATION_SCOPE_RANGE_SIZE = 5` (scope `FVulkanCustomMemManager::__anond1bb0e760603`)

### `Source/Runtime/VulkanRHI/Private/VulkanPendingState.h` (Private)


#### class `FVulkanPendingComputeState`  
`class FVulkanPendingComputeState`  
_L20-93_
- desc: All the current compute pipeline states in use
- L23 _public function_ `FVulkanPendingComputeState(FVulkanDevice& InDevice) : Device(InDevice)`
- L28 _public prototype_ `~FVulkanPendingComputeState();`
- L30 _public function_ `void Reset()`
- L36 _public function_ `void SetComputePipeline(FVulkanComputePipeline* InComputePipeline)`
- L57 _public prototype_ `void PrepareForDispatch(FVulkanCommandListContext& Context);`
- L59 _public function_ `inline const FVulkanComputeShader* GetCurrentShader() const`
- L64 _public function_ `FVulkanPackedUniformBufferState& GetUniformBuffers(uint8 Stage)`
- L69 _public function_ `inline void SetSamplerStateForUBResource(uint32 DescriptorSet, uint32 BindingIndex, FVulkanSamplerState* Sampler)`
- L74 _public function_ `void NotifyDeletedPipeline(FVulkanComputePipeline* Pipeline)`
- L79 _public function_ `FVulkanComputePipelineDescriptorState& GetCurrentState()`
- L85 _protected member_ `FVulkanComputePipeline* CurrentPipeline = nullptr;`
- L86 _protected member_ `FVulkanComputePipelineDescriptorState* CurrentState = nullptr;`
- L88 _protected member_ `TMap<FVulkanComputePipeline*, FVulkanComputePipelineDescriptorState*> PipelineStates;`
- L90 _protected member_ `FVulkanDevice& Device;`

#### class `FVulkanPendingGfxState`  
`class FVulkanPendingGfxState`  
_L96-280_
- desc: All the current gfx pipeline states in use
- L99 _public function_ `FVulkanPendingGfxState(FVulkanDevice& InDevice) : Device(InDevice)`
- L105 _public prototype_ `~FVulkanPendingGfxState();`
- L107 _public function_ `void Reset()`
- L125 _public function_ `const uint64 GetCurrentShaderKey(EShaderFrequency Frequency) const`
- L130 _public function_ `const uint64 GetCurrentShaderKey(ShaderStage::EStage Stage) const`
- L135 _public function_ `const FVulkanShader* GetCurrentShader(EShaderFrequency Frequency) const`
- L140 _public function_ `void SetViewport(float MinX, float MinY, float MinZ, float MaxX, float MaxY, float MaxZ)`
- L163 _public function_ `void SetMultiViewport(const TArrayView<VkViewport>& InViewports)`
- L179 _public function_ `void SetScissor(bool bInEnable, uint32 MinX, uint32 MinY, uint32 MaxX, uint32 MaxY)`
- L194 _public function_ `void SetScissorRect(uint32 MinX, uint32 MinY, uint32 Width, uint32 Height)`
- L204 _public function_ `void SetStreamSource(uint32 StreamIndex, VkBuffer VertexBuffer, uint32 Offset)`
- L211 _public function_ `void Bind(FVulkanCommandBuffer& CommandBuffer)`
- L216 _public function_ `FVulkanPackedUniformBufferState& GetUniformBuffers(uint8 Stage)`
- L221 _public prototype_ `void PrepareForDraw(FVulkanCommandListContext& Context);`
- L223 _public prototype_ `bool SetGfxPipeline(FVulkanGraphicsPipelineState* InGfxPipeline, bool bForceReset);`
- L225 _public prototype_ `void UpdateDynamicStates(FVulkanCommandBuffer& CommandBuffer);`
- L227 _public function_ `void SetStencilRef(uint32 InStencilRef)`
- L235 _public function_ `void NotifyDeletedPipeline(FVulkanGraphicsPipelineState* Pipeline)`
- L240 _public function_ `FVulkanGraphicsPipelineDescriptorState& GetCurrentState()`
- L246 _protected member_ `TArray<VkViewport, TInlineAllocator<2>> Viewports;`
- L247 _protected member_ `TArray<VkRect2D, TInlineAllocator<2>> Scissors;`
- L249 _protected member_ `EPrimitiveType PrimitiveType = PT_Num;`
- L250 _protected member_ `uint32 StencilRef;`
- L251 _protected member_ `bool bScissorEnable;`
- L253 _protected member_ `bool bNeedToClear;`
- L255 _protected member_ `FVulkanGraphicsPipelineState* CurrentPipeline;`
- L256 _protected member_ `FVulkanGraphicsPipelineDescriptorState* CurrentState;`
- L258 _protected member_ `TMap<FVulkanGraphicsPipelineState*, FVulkanGraphicsPipelineDescriptorState*> PipelineStates;`
- L271 _protected member_ `FVertexStream PendingStreams[MaxVertexElementCount];`
- L272 _protected member_ `bool bDirtyVertexStreams;`
- L273 _protected member_ `bool bDirtyDynamicVertexInput;`
- L275 _protected prototype_ `void UpdateInputAttachments(FVulkanCommandListContext& Context);`
- L277 _protected member_ `FVulkanDevice& Device;`

#### struct `FVulkanPendingGfxState::FVertexStream`  
`struct FVertexStream`  
_L260-270_
- L262 _public function_ `FVertexStream() : Stream(VK_NULL_HANDLE), BufferOffset(0)`
- L268 _public member_ `VkBuffer Stream;`
- L269 _public member_ `uint32 BufferOffset;`

### `Source/Runtime/VulkanRHI/Private/VulkanPipeline.h` (Private)


#### class `FVulkanPSOKey`  
`class FVulkanPSOKey : public TDataKey<FVulkanPSOKey, true>`  
_L25-25_
- inherits: `TDataKey<FVulkanPSOKey,true>`

#### struct `FVulkanShaderHashes`  
`struct FVulkanShaderHashes`  
_L62-92_
- L64 _public member_ `uint32 Hash;`
- L65 _public member_ `FShaderHash Stages[ShaderStage::MaxNumStages];`
- L67 _public prototype_ `FVulkanShaderHashes();`
- L68 _public prototype_ `FVulkanShaderHashes(const FGraphicsPipelineStateInitializer& PSOInitializer);`
- L75 _public function_ `inline void Finalize()`

#### struct `FVulkanPipelineSize`  
`struct FVulkanPipelineSize`  
_L94-104_
- L97 _public member_ `uint64 ShaderHash;` — TODO: increase hash to 12 bytes to reduce collisions
- L98 _public member_ `uint32 PipelineSize;`
- L100 _public function_ `FVulkanPipelineSize() :ShaderHash(0), PipelineSize(0)`

#### struct `FDescriptorSetLayoutBinding`  
`struct FDescriptorSetLayoutBinding`  
_L106-121_
- L108 _public member_ `uint32 Binding;`
- L109 _public member_ `uint8 DescriptorType;`
- L110 _public member_ `uint8 StageFlags;`
- L112 _public prototype_ `void ReadFrom(const VkDescriptorSetLayoutBinding& InState);`
- L113 _public prototype_ `void WriteInto(VkDescriptorSetLayoutBinding& OutState) const;`
- L115 _public function_ `bool operator==(const FDescriptorSetLayoutBinding& In) const`

#### struct `FGfxPipelineDesc`  
`struct FGfxPipelineDesc`  
_L126-492_
- L128 _public prototype_ `FVulkanPSOKey CreateKey2() const;`
- L130 _public member_ `uint32 VertexInputKey;`
- L131 _public member_ `uint16 RasterizationSamples;`
- L132 _public member_ `uint32 Topology;`
- L159 _public member_ `TArray<FBlendAttachment> ColorAttachmentStates;`
- L161 _public member_ `TArray<TArray<FDescriptorSetLayoutBinding>> DescriptorSetLayoutBindings;`
- L180 _public member_ `TArray<FVertexBinding> VertexBindings;`
- L200 _public member_ `TArray<FVertexAttribute> VertexAttributes;`
- L220 _public member_ `FRasterizer Rasterizer;`
- L270 _public member_ `FDepthStencil DepthStencil;`
- L273 _public member_ `uint64 ShaderKeys[ShaderStage::NumGraphicsStages];`
- L274 _public member_ `uint64 ShaderKeyShared;`
- L276 _public member_ `FVulkanShaderHashes ShaderHashes;`
- L278 _public member_ `uint64 SpecializationKey;`
- L393 _public member_ `FRenderTargets RenderTargets;`
- L395 _public member_ `uint8 SubpassIndex;`
- L397 _public member_ `uint8 UseAlphaToCoverage;`
- L399 _public member_ `EVRSShadingRate ShadingRate = EVRSShadingRate::VRSSR_1x1;`
- L400 _public member_ `EVRSRateCombiner Combiner = EVRSRateCombiner::VRSRB_Passthrough;`
- L402 _public function_ `bool operator==(const FGfxPipelineDesc& In) const`

#### struct `FGfxPipelineDesc::FBlendAttachment`  
`struct FBlendAttachment`  
_L133-158_
- L135 _public member_ `bool bBlend;`
- L136 _public member_ `uint8 ColorBlendOp;`
- L137 _public member_ `uint8 SrcColorBlendFactor;`
- L138 _public member_ `uint8 DstColorBlendFactor;`
- L139 _public member_ `uint8 AlphaBlendOp;`
- L140 _public member_ `uint8 SrcAlphaBlendFactor;`
- L141 _public member_ `uint8 DstAlphaBlendFactor;`
- L142 _public member_ `uint8 ColorWriteMask;`
- L144 _public prototype_ `void ReadFrom(const VkPipelineColorBlendAttachmentState& InState);`
- L145 _public prototype_ `void WriteInto(VkPipelineColorBlendAttachmentState& OutState) const;`
- L147 _public function_ `bool operator==(const FBlendAttachment& In) const`

#### struct `FGfxPipelineDesc::FVertexBinding`  
`struct FVertexBinding`  
_L163-179_
- L165 _public member_ `uint32 Stride;`
- L166 _public member_ `uint16 Binding;`
- L167 _public member_ `uint16 InputRate;`
- L169 _public prototype_ `void ReadFrom(const VkVertexInputBindingDescription& InState);`
- L170 _public prototype_ `void WriteInto(VkVertexInputBindingDescription& OutState) const;`
- L171 _public prototype_ `void WriteInto(VkVertexInputBindingDescription2EXT& OutState) const;`
- L173 _public function_ `bool operator==(const FVertexBinding& In) const`

#### struct `FGfxPipelineDesc::FVertexAttribute`  
`struct FVertexAttribute`  
_L181-199_
- L183 _public member_ `uint32 Location;`
- L184 _public member_ `uint32 Binding;`
- L185 _public member_ `uint32 Format;`
- L186 _public member_ `uint32 Offset;`
- L188 _public prototype_ `void ReadFrom(const VkVertexInputAttributeDescription& InState);`
- L189 _public prototype_ `void WriteInto(VkVertexInputAttributeDescription& OutState) const;`
- L190 _public prototype_ `void WriteInto(VkVertexInputAttributeDescription2EXT& OutState) const;`
- L192 _public function_ `bool operator==(const FVertexAttribute& In) const`

#### struct `FGfxPipelineDesc::FRasterizer`  
`struct FRasterizer`  
_L202-219_
- L204 _public member_ `uint8 PolygonMode;`
- L205 _public member_ `uint8 CullMode;`
- L206 _public member_ `float DepthBiasSlopeScale;`
- L207 _public member_ `float DepthBiasConstantFactor;`
- L209 _public prototype_ `void ReadFrom(const VkPipelineRasterizationStateCreateInfo& InState);`
- L210 _public prototype_ `void WriteInto(VkPipelineRasterizationStateCreateInfo& OutState) const;`
- L212 _public function_ `bool operator==(const FRasterizer& In) const`

#### struct `FGfxPipelineDesc::FDepthStencil`  
`struct FDepthStencil`  
_L222-269_
- L224 _public member_ `uint8 DepthCompareOp;`
- L225 _public member_ `bool bDepthTestEnable;`
- L226 _public member_ `bool bDepthWriteEnable;`
- L227 _public member_ `bool bStencilTestEnable;`
- L228 _public member_ `bool bDepthBoundsTestEnable;`
- L229 _public member_ `uint8 FrontFailOp;`
- L230 _public member_ `uint8 FrontPassOp;`
- L231 _public member_ `uint8 FrontDepthFailOp;`
- L232 _public member_ `uint8 FrontCompareOp;`
- L233 _public member_ `uint32 FrontCompareMask;`
- L234 _public member_ `uint32 FrontWriteMask;`
- L235 _public member_ `uint32 FrontReference;`
- L236 _public member_ `uint8 BackFailOp;`
- L237 _public member_ `uint8 BackPassOp;`
- L238 _public member_ `uint8 BackDepthFailOp;`
- L239 _public member_ `uint8 BackCompareOp;`
- L240 _public member_ `uint32 BackCompareMask;`
- L241 _public member_ `uint32 BackWriteMask;`
- L242 _public member_ `uint32 BackReference;`
- L244 _public prototype_ `void ReadFrom(const VkPipelineDepthStencilStateCreateInfo& InState);`
- L245 _public prototype_ `void WriteInto(VkPipelineDepthStencilStateCreateInfo& OutState) const;`
- L247 _public function_ `bool operator==(const FDepthStencil& In) const`

#### struct `FGfxPipelineDesc::FRenderTargets`  
`struct FRenderTargets`  
_L280-392_
- L307 _public member_ `TArray<FAttachmentRef> ColorAttachments;`
- L308 _public member_ `TArray<FAttachmentRef> ResolveAttachments;`
- L309 _public member_ `FAttachmentRef Depth;`
- L310 _public member_ `FStencilAttachmentRef Stencil;`
- L311 _public member_ `FAttachmentRef FragmentDensity;`
- L357 _public member_ `TArray<FAttachmentDesc> Descriptions;`
- L358 _public member_ `FStencilAttachmentDesc StencilDescription;`
- L360 _public member_ `uint8 NumAttachments;`
- L361 _public member_ `uint8 NumColorAttachments;`
- L362 _public member_ `uint8 bHasDepthStencil;`
- L363 _public member_ `uint8 bHasResolveAttachments;`
- L364 _public member_ `uint8 bHasDepthStencilResolve;`
- L365 _public member_ `uint8 bHasFragmentDensityAttachment;`
- L366 _public member_ `uint8 NumUsedClearValues;`
- L367 _public member_ `uint32 RenderPassCompatibleHash;`
- L368 _public member_ `FVector Extent3D;`
- L370 _public prototype_ `void ReadFrom(const FVulkanRenderTargetLayout &InState);`
- L371 _public prototype_ `void WriteInto(FVulkanRenderTargetLayout& OutState) const;`
- L373 _public function_ `bool operator==(const FRenderTargets& In) const`

#### struct `FGfxPipelineDesc::FRenderTargets::FAttachmentRef`  
`struct FAttachmentRef`  
_L282-293_
- L284 _public member_ `uint32 Attachment;`
- L285 _public member_ `uint64 Layout;`
- L287 _public prototype_ `void ReadFrom(const VkAttachmentReference& InState);`
- L288 _public prototype_ `void WriteInto(VkAttachmentReference& OutState) const;`
- L289 _public function_ `bool operator == (const FAttachmentRef& In) const`

#### struct `FGfxPipelineDesc::FRenderTargets::FStencilAttachmentRef`  
`struct FStencilAttachmentRef`  
_L295-305_
- L297 _public member_ `uint64 Layout;`
- L299 _public prototype_ `void ReadFrom(const VkAttachmentReferenceStencilLayout& InState);`
- L300 _public prototype_ `void WriteInto(VkAttachmentReferenceStencilLayout& OutState) const;`
- L301 _public function_ `bool operator == (const FStencilAttachmentRef& In) const`

#### struct `FGfxPipelineDesc::FRenderTargets::FAttachmentDesc`  
`struct FAttachmentDesc`  
_L313-340_
- L315 _public member_ `uint32 Format;`
- L316 _public member_ `uint8 Flags;`
- L317 _public member_ `uint8 Samples;`
- L318 _public member_ `uint8 LoadOp;`
- L319 _public member_ `uint8 StoreOp;`
- L320 _public member_ `uint8 StencilLoadOp;`
- L321 _public member_ `uint8 StencilStoreOp;`
- L322 _public member_ `uint64 InitialLayout;`
- L323 _public member_ `uint64 FinalLayout;`
- L325 _public function_ `bool operator==(const FAttachmentDesc& In) const`
- L338 _public prototype_ `void ReadFrom(const VkAttachmentDescription &InState);`
- L339 _public prototype_ `void WriteInto(VkAttachmentDescription& OutState) const;`

#### struct `FGfxPipelineDesc::FRenderTargets::FStencilAttachmentDesc`  
`struct FStencilAttachmentDesc`  
_L342-355_
- L344 _public member_ `uint64 InitialLayout;`
- L345 _public member_ `uint64 FinalLayout;`
- L347 _public function_ `bool operator==(const FStencilAttachmentDesc& In) const`
- L353 _public prototype_ `void ReadFrom(const VkAttachmentDescriptionStencilLayout& InState);`
- L354 _public prototype_ `void WriteInto(VkAttachmentDescriptionStencilLayout& OutState) const;`

#### class `FVulkanPipelineStateCacheManager`  
`class FVulkanPipelineStateCacheManager`  
_L497-649_
- L502 _public prototype_ `void InitAndLoad(const TArray<FString>& CacheFilenames);` — Array of potential cache locations; first entries have highest priority. Only one cache file is loaded. If unsuccessful, tries next entry in the array.
- L503 _public prototype_ `void Save(const FString& CacheFilename);`
- L505 _public prototype_ `FVulkanPipelineStateCacheManager(FVulkanDevice* InParent);`
- L506 _public prototype_ `~FVulkanPipelineStateCacheManager();`
- L508 _public prototype_ `void RebuildCache();`
- L510 _public prototype_ `FVulkanComputePipeline* GetOrCreateComputePipeline(const FComputePipelineStateInitializer& Initializer);`
- L511 _public prototype_ `void NotifyDeletedComputePipeline(FVulkanComputePipeline* Pipeline);`
- L513 _public prototype_ `VkResult CreateRayTracingPipeline(const VkRayTracingPipelineCreateInfoKHR& CreateInfo, bool bIsPartial, VkPipeline& OutPipeline);`
- L519 _private prototype_ `void OnShaderPipelineCacheOpened(FString const& Name, EShaderPlatform Platform, uint32 Count, const FGuid& VersionGuid, FShaderPipelineCache::FShaderCachePrecompileContext& ShaderCachePrecompileContext);` — Delegate handlers to track the ShaderPipelineCache precompile.
- L520 _private prototype_ `void OnShaderPipelineCachePrecompilationComplete(uint32 Count, double Seconds, const FShaderPipelineCache::FShaderCachePrecompileContext& ShaderCachePrecompileContext);`
- L522 _private prototype_ `void CreateGfxEntry(const FGraphicsPipelineStateInitializer& PSOInitializer, FVulkanDescriptorSetsLayoutInfo& DescriptorSetLayoutInfo, FGfxPipelineDesc* Desc);`
- L523 _private prototype_ `bool Load(const TArray<FString>& CacheFilenames, FPipelineCache& Cache);`
- L524 _private prototype_ `void SavePSOCache(const FString& CacheFilename, FPipelineCache& Cache);`
- L525 _private prototype_ `void DestroyCache();`
- L527 _private prototype_ `FGraphicsPipelineStateRHIRef RHICreateGraphicsPipelineState(const FGraphicsPipelineStateInitializer& Initializer);`
- L528 _private prototype_ `FVulkanComputePipeline* RHICreateComputePipelineState(const FComputePipelineStateInitializer& Initializer);`
- L529 _private prototype_ `void NotifyDeletedGraphicsPSO(FRHIGraphicsPipelineState* PSO);`
- L530 _private prototype_ `bool CreateGfxPipelineFromEntry(FVulkanGraphicsPipelineState* PSO, FVulkanShader* Shaders[ShaderStage::NumGraphicsStages], FGraphicsPipelineStateInitializer::EPSOPrecacheCompileType PSOCompileType);`
- L531 _private prototype_ `bool CreateGfxPipelineFromLibrary(FVulkanGraphicsPipelineState& GraphicsPipelineState, FVulkanShader* Shaders[ShaderStage::NumGraphicsStages], FGraphicsPipelineStateInitializer::EPSOPrecacheCompileType PSOCompileType);`
- L533 _private prototype_ `void CreateVertexInputLibraries();`
- L534 _private member_ `VkPipeline VertexInputPipelineLibraryVS = VK_NULL_HANDLE;`
- L535 _private member_ `VkPipeline VertexInputPipelineLibraryMS = VK_NULL_HANDLE;`
- L537 _private prototype_ `void CreateEmptyFragmentStageLibrary();`
- L538 _private member_ `VkPipeline EmptyFragmentStageLibrary = VK_NULL_HANDLE;`
- L540 _private prototype_ `VkPipeline FindOrCreateFragmentOutputStateLibrary(const FVulkanGraphicsPipelineState& GraphicsPipelineState);`
- L541 _private member_ `TMap<uint32, VkPipeline> FragmentOutputStatePipelineLibraries;`
- L542 _private member_ `FCriticalSection FragmentOutputStateCS;`
- L544 _private prototype_ `VkResult CreateVKPipeline(FVulkanGraphicsPipelineState* PSO, FVulkanShader* Shaders[ShaderStage::NumGraphicsStages], const VkGraphicsPipelineCreateInfo& PipelineInfo, FGraphicsPipelineStateInitializer::EPSOPrecacheCompileType PSOCompileType);`
- L546 _private prototype_ `FVulkanLayout* FindOrAddLayout(const FVulkanDescriptorSetsLayoutInfo& DescriptorSetLayoutInfo, bool bGfxLayout, bool bUsesBindless);`
- L547 _private prototype_ `FVulkanComputePipeline* CreateComputePipeline(const FComputePipelineStateInitializer& Initializer);`
- L550 _private prototype_ `void TickLRU();` — LRU Related functions
- L551 _private prototype_ `bool LRUEvictImmediately();`
- L552 _private prototype_ `void LRUTrim(uint32 nSpaceNeeded);`
- L553 _private prototype_ `void LRUAdd(FVulkanGraphicsPipelineState* PSO);`
- L554 _private prototype_ `void LRUTouch(FVulkanGraphicsPipelineState* PSO);`
- L555 _private prototype_ `bool LRUEvictOne(bool bOnlyOld = false);`
- L556 _private prototype_ `void LRURemoveAll();`
- L557 _private prototype_ `void LRUDump();`
- L558 _private prototype_ `void LRUDebugEvictAll();` — evict all that are safe to evict without stalling..
- L559 _private prototype_ `void LRURemove(FVulkanGraphicsPipelineState* PSO);`
- L560 _private prototype_ `void LRUCheckNotInside(FVulkanGraphicsPipelineState* PSO);`
- L563 _private member_ `FVulkanDevice* Device;`
- L564 _private member_ `bool bEvictImmediately;`
- L565 _private member_ `FString CompiledPSOCacheTopFolderPath;`
- L566 _private member_ `FString CompiledPSOCacheFolderName;`
- L567 _private member_ `FDelegateHandle OnShaderPipelineCacheOpenedDelegate;`
- L568 _private member_ `FDelegateHandle OnShaderPipelineCachePrecompilationCompleteDelegate;`
- L571 _private member_ `FRWLock ComputePipelineLock;`
- L572 _private member_ `TMap<uint64, FVulkanComputePipeline*> ComputePipelineEntries;`
- L586 _private typedef_ `using FScopedPipelineCache = FScopedRWAccessor<VkPipelineCache>;`
- L600 _private member_ `FPipelineCache GlobalPSOCache;` — contains all PSO caches opened during the program run as well as PSO objects created on the fly
- L602 _private member_ `FPipelineCache CurrentPrecompilingPSOCache;`
- L604 _private member_ `bool bPrecompilingCacheLoadedFromFile;` — if true, we will link to the PSOFC, loading later, when we have that guid and only if the guid matches, saving only if there is no match, and only saving after the PSOFC is done.
- L605 _private member_ `FGuid CurrentPrecompilingPSOCacheGuid;`
- L607 _private member_ `TSet<FGuid> CompiledPSOCaches;`
- L609 _private member_ `FCriticalSection LayoutMapCS;`
- L610 _private member_ `TMap<FVulkanDescriptorSetsLayoutInfo, FVulkanLayout*> LayoutMap;`
- L611 _private member_ `FVulkanDescriptorSetLayoutMap DSetLayoutMap;`
- L614 _private member_ `FCriticalSection GraphicsPSOLockedCS;`
- L615 _private member_ `TMap<FVulkanPSOKey, FVulkanGraphicsPipelineState*> GraphicsPSOLockedMap;`
- L618 _private member_ `FCriticalSection LRUCS;`
- L619 _private member_ `FVulkanGraphicsPipelineStateLRU LRU;`
- L620 _private member_ `uint32 LRUUsedPipelineSize = 0;`
- L621 _private member_ `uint32 LRUUsedPipelineCount = 0;`
- L622 _private member_ `uint32 LRUUsedPipelineMax = 0;`
- L623 _private member_ `TMap<uint64, FVulkanPipelineSize> LRU2SizeList;` — key: Shader hash (FShaderHash), value: pipeline size
- L624 _private member_ `bool bUseLRU = true;`
- L647 _private member_ `static constexpr uint32 MaxNumSpecializationConstants = 32;`
- L648 _private member_ `TStaticArray<VkSpecializationMapEntry, MaxNumSpecializationConstants> SpecializationMapEntries;`

#### class `FVulkanPipelineStateCacheManager::FScopedRWAccessor`  
`template<typename TType> class FScopedRWAccessor`  
_L575-584_
- L577 _private member_ `bool bWriteAccess;`
- L578 _private member_ `TType& ProtectedObj;`
- L579 _private member_ `FRWLock& RWLock;`
- L581 _public function_ `FScopedRWAccessor(bool bWriteAccessIn, TType& ProtectedObjIn, FRWLock& RWLockIn) : bWriteAccess(bWriteAccessIn), ProtectedObj(ProtectedObjIn), RWLock(RWLockIn)`
- L582 _public function_ `~FScopedRWAccessor()`
- L583 _public function_ `TType& Get()`

#### enum `FVulkanPipelineStateCacheManager::EPipelineCacheAccess`  
`enum class EPipelineCacheAccess : uint8`  
_L588-592_
- L590 _public enumerator_ `Shared` — 'read' access, or for use when the API does its own synchronization.
- L591 _public enumerator_ `Exclusive` — 'write' access, excludes all other usage for the duration.

#### class `FVulkanPipelineStateCacheManager::FPipelineCache`  
`class FPipelineCache`  
_L593-599_
- L595 _private member_ `VkPipelineCache PipelineCache = VK_NULL_HANDLE;`
- L596 _private member_ `FRWLock PipelineCacheLock;`
- L598 _public function_ `FScopedPipelineCache Get(EPipelineCacheAccess PipelineAccessType)`

#### struct `FVulkanPipelineStateCacheManager::FVulkanLRUCacheFile`  
`struct FVulkanLRUCacheFile`  
_L629-645_
- L639 _public member_ `} Header;`
- L641 _public member_ `TArray<FVulkanPipelineSize> PipelineSizes;`
- L643 _public prototype_ `void Save(FArchive& Ar);`
- L644 _public prototype_ `bool Load(FArchive& Ar);`

#### enum `FVulkanPipelineStateCacheManager::FVulkanLRUCacheFile::(anonymous)`  
``  
_L632-634_

#### struct `FVulkanPipelineStateCacheManager::FVulkanLRUCacheFile::FFileHeader`  
`struct FFileHeader`  
_L635-639_
- L637 _public member_ `int32 Version = -1;`
- L638 _public member_ `int32 SizeOfPipelineSizes = -1;`

#### struct `VulkanResourceFrameCounter`  
`struct VulkanResourceFrameCounter`  
_L651-665_
- L653 _public function_ `void Set(uint32_t Frame) const`
- L658 _public function_ `uint32 Get() const`
- L664 _public member_ `mutable std::atomic<uint32> LastUsedFrame{0};` — Note that the frame counter may be updated from any number of threads, and is not entirely synchronized

#### class `FVulkanPipeline`  
`class FVulkanPipeline`  
_L668-711_
- desc: Common pipeline class
- L671 _public prototype_ `FVulkanPipeline(FVulkanDevice* InDevice);`
- L672 _public prototype_ `virtual ~FVulkanPipeline();`
- L674 _public function_ `inline VkPipeline GetHandle() const`
- L679 _public function_ `inline const FVulkanLayout& GetLayout() const`
- L684 _public function_ `inline void DeleteVkPipeline(bool ImmediateDestroy)`
- L701 _public member_ `VulkanResourceFrameCounter FrameCounter;`
- L704 _protected member_ `FVulkanDevice* Device;`
- L705 _protected member_ `VkPipeline Pipeline;`
- L706 _protected member_ `FVulkanLayout* Layout;`

#### class `FVulkanComputePipeline`  
`class FVulkanComputePipeline : public FVulkanPipeline, public FRHIComputePipelineState`  
_L713-744_
- inherits: `FVulkanPipeline,FRHIComputePipelineState`
- L716 _public prototype_ `FVulkanComputePipeline(FVulkanDevice* InDevice, const FComputePipelineStateInitializer& Initializer);`
- L717 _public prototype_ `virtual ~FVulkanComputePipeline();`
- L719 _public function_ `const FVulkanShaderHeader& GetShaderCodeHeader() const`
- L724 _public function_ `const FVulkanLayout& GetLayout() const`
- L729 _public prototype_ `void Bind(FVulkanCommandBuffer& CommandBuffer);`
- L731 _public function_ `bool UsesBindless() const`
- L736 _public function_ `const FSpecializationContainerType& GetSpecializationConstants() const`
- L742 _protected member_ `const bool bUsesBindless;`
- L743 _protected member_ `const FSpecializationContainerType SpecializationConstants;`

#### class `FVulkanGraphicsPipelineState`  
`class FVulkanGraphicsPipelineState : public FRHIGraphicsPipelineState`  
_L746-847_
- inherits: `FRHIGraphicsPipelineState`
- L749 _public prototype_ `FVulkanGraphicsPipelineState(FVulkanDevice* Device, const FGraphicsPipelineStateInitializer& PSOInitializer, const FGfxPipelineDesc& Desc, FVulkanPSOKey* Key);`
- L750 _public prototype_ `~FVulkanGraphicsPipelineState();`
- L752 _public function_ `const FVulkanVertexInputStateInfo& GetVertexInputState() const`
- L757 _public function_ `const FVulkanLayout& GetLayout() const`
- L762 _public prototype_ `void Bind(FVulkanCommandBuffer& CommandBuffer);`
- L764 _public function_ `const uint64 GetShaderKey(EShaderFrequency Frequency) const`
- L770 _public function_ `const FVulkanShader* GetVulkanShader(EShaderFrequency Frequency) const`
- L776 _public function_ `VkPipeline GetVulkanPipeline() const`
- L781 _public function_ `FRHIGraphicsShader* GetShader(EShaderFrequency Frequency) const override`
- L798 _public prototype_ `void DeleteVkPipeline(bool bImmediate);`
- L799 _public prototype_ `void GetOrCreateShaderModules(TRefCountPtr<FVulkanShaderModule>(&ShaderModulesOUT)[ShaderStage::NumGraphicsStages], FVulkanShader* const* Shaders);`
- L800 _public prototype_ `FVulkanShader::FSpirvCode GetPatchedSpirvCode(FVulkanShader* Shader);`
- L801 _public prototype_ `void PurgeShaderModules(FVulkanShader*const* Shaders);`
- L803 _public function_ `bool UsesBindless() const`
- L809 _public member_ `bool bHasInputAttachments = false;`
- L810 _public member_ `bool bIsRegistered;`
- L811 _public member_ `bool bUsesBindless = false;`
- L813 _public member_ `uint64 ShaderKeys[ShaderStage::NumGraphicsStages];`
- L814 _public member_ `TEnumAsByte<EPrimitiveType> PrimitiveType;`
- L817 _public member_ `VkPipeline VulkanPipeline;`
- L818 _public member_ `FVulkanVertexInputStateInfo VertexInputState;`
- L819 _public member_ `FVulkanLayout* Layout;`
- L820 _public member_ `FVulkanDevice* Device;`
- L821 _public member_ `const FGfxPipelineDesc Desc;`
- L822 _public member_ `FVulkanShader* VulkanShaders[ShaderStage::NumGraphicsStages];`
- L823 _public member_ `FSpecializationContainerType SpecializationConstants[ShaderStage::NumGraphicsStages];`
- L824 _public member_ `const FVulkanRenderPass* RenderPass;`
- L827 _public member_ `FVulkanGraphicsPipelineStateLRUNode* LRUNode = nullptr;`
- L828 _public member_ `uint32 LRUFrame = UINT32_MAX;`
- L829 _public member_ `uint32 PipelineCacheSize = UINT32_MAX;`
- L830 _public member_ `uint64 PrecacheKey;` — hash of elements relevant to the PSO cache
- L831 _public member_ `FVulkanPSOKey VulkanKey;`
- L833 _public member_ `VulkanResourceFrameCounter FrameCounter;`
- L836 _public member_ `FPixelShaderRHIRef PixelShaderRHI;`
- L837 _public member_ `FVertexShaderRHIRef VertexShaderRHI;`
- L838 _public member_ `FVertexDeclarationRHIRef VertexDeclarationRHI;`
- L841 _public member_ `FGeometryShaderRHIRef GeometryShaderRHI;`
- L844 _public member_ `FGraphicsPipelineStateInitializer PSOInitializer;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<class FRHIComputePipelineState>`  
_L880-883_
- L882 _public typedef_ `typedef class FVulkanComputePipeline TConcreteType;`
- L888 _public typedef_ `typedef FVulkanGraphicsPipelineState TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIGraphicsPipelineState>`  
_L886-889_
- L882 _public typedef_ `typedef class FVulkanComputePipeline TConcreteType;`
- L888 _public typedef_ `typedef FVulkanGraphicsPipelineState TConcreteType;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define VULKAN_PSO_CACHE_DEBUG 0`
- L16 _macro_ `#define VULKAN_USE_SHADERKEYS 1`
- L21 _typedef_ `using FVulkanGraphicsPipelineStateLRU = TDoubleLinkedList<FVulkanGraphicsPipelineState*>;`
- L22 _typedef_ `using FVulkanGraphicsPipelineStateLRUNode = FVulkanGraphicsPipelineStateLRU::TDoubleLinkedListNode;`
- L28 _function_ `template <typename TVulkanShader> static inline uint64 GetShaderKey(FRHIGraphicsShader* ShaderType)`
- L35 _function_ `inline uint64 GetShaderKeyForGfxStage(const FBoundShaderStateInput& BSI, ShaderStage::EStage Stage)`
- L57 _prototype_ `void GetVulkanGfxShaders(const FBoundShaderStateInput& BSI, FVulkanShader* OutShaders[ShaderStage::NumGraphicsStages]);`
- L58 _prototype_ `void GetVulkanGfxShaders(FVulkanDevice* Device, const FVulkanGraphicsPipelineState& GfxPipelineState, FVulkanShader* OutShaders[ShaderStage::NumGraphicsStages]);`
- L70 _function_ `friend inline uint32 GetTypeHash(const FVulkanShaderHashes& Hashes)`
- L80 _function_ `friend inline bool operator == (const FVulkanShaderHashes& A, const FVulkanShaderHashes& B)`
- L633 _enumerator_ `LRU_CACHE_VERSION = 2` (scope `FVulkanPipelineStateCacheManager::FVulkanLRUCacheFile::__anonbecbb0730103`)
- L850 _function_ `inline VkRenderingInputAttachmentIndexInfo GetDefaultRenderingInputAttachmentIndexInfo(uint32 NumColorAttachments)` — Returns a structure with all input attachments pre-configured

### `Source/Runtime/VulkanRHI/Private/VulkanPipelineState.h` (Private)


#### class `FVulkanCommonPipelineDescriptorState`  
`class FVulkanCommonPipelineDescriptorState`  
_L23-184_
- desc: Common Pipeline state
- L26 _public function_ `FVulkanCommonPipelineDescriptorState(FVulkanDevice& InDevice, uint32 InMaxNumSets, bool InUsesBindless) : Device(InDevice) , MaxNumSets(InMaxNumSets) , bUseBindless(InUsesBindless)`
- L33 _public prototype_ `virtual ~FVulkanCommonPipelineDescriptorState() = default;`
- L35 _public function_ `const FVulkanDSetsKey& GetDSetsKey() const`
- L47 _public function_ `bool HasVolatileResources() const`
- L59 _public function_ `inline void MarkDirty(bool bDirty)`
- L65 _public prototype_ `void SetSRV(bool bCompute, uint8 DescriptorSet, uint32 BindingIndex, FVulkanShaderResourceView* SRV);`
- L66 _public prototype_ `void SetUAV(bool bCompute, uint8 DescriptorSet, uint32 BindingIndex, FVulkanUnorderedAccessView* UAV);`
- L68 _public function_ `inline void SetTexture(uint8 DescriptorSet, uint32 BindingIndex, const FVulkanTexture* Texture, VkImageLayout Layout)`
- L84 _public function_ `inline void SetSamplerState(uint8 DescriptorSet, uint32 BindingIndex, const FVulkanSamplerState* Sampler)`
- L91 _public function_ `inline void SetInputAttachment(uint8 DescriptorSet, uint32 BindingIndex, const FVulkanView::FTextureView& TextureView, VkImageLayout Layout)`
- L97 _public function_ `inline void SetUniformBuffer(uint8 DescriptorSet, uint32 BindingIndex, const FVulkanUniformBuffer* UniformBuffer, bool bDynamic)`
- L117 _public function_ `inline void SetUniformBufferDynamicOffset(uint8 DescriptorSet, uint32 BindingIndex, uint32 DynamicOffset)`
- L123 _public function_ `VkDescriptorType GetDescriptorType(uint8 DescriptorSet, uint32 BindingIndex) const`
- L129 _public prototype_ `virtual TArray<uint32> GetExcludedResources(uint32 SetIndex) const = 0;`
- L132 _protected function_ `void Reset()`
- L139 _protected function_ `inline void Bind(VkCommandBuffer CmdBuffer, VkPipelineLayout PipelineLayout, VkPipelineBindPoint BindPoint)`
- L156 _protected prototype_ `void CreateDescriptorWriteInfos();`
- L158 _protected member_ `FVulkanDevice& Device;`
- L160 _protected member_ `const uint32 MaxNumSets;`
- L163 _protected member_ `FVulkanDescriptorSetWriteContainer DSWriteContainer;` — #todo-rco: Won't work multithreaded!
- L164 _protected member_ `const FVulkanDescriptorSetsLayout* DescriptorSetsLayout = nullptr;`
- L167 _protected member_ `TArray<VkDescriptorSet> DescriptorSetHandles;` — #todo-rco: Won't work multithreaded!
- L171 _protected member_ `uint32 UsedSetsMask = 0;` — Bitmask of sets that exist in this pipeline #todo-rco: Won't work multithreaded!
- L174 _protected member_ `TArray<uint32> DynamicOffsets;` — #todo-rco: Won't work multithreaded!
- L176 _protected member_ `bool bIsResourcesDirty = true;`
- L178 _protected member_ `TArray<FVulkanDescriptorSetWriter> DSWriter;`
- L180 _protected member_ `mutable FVulkanDSetsKey DSetsKey;`
- L181 _protected member_ `mutable bool bIsDSetsKeyDirty = true;`
- L183 _protected member_ `const bool bUseBindless;`

#### struct `FVulkanPackedUniformBufferState`  
`struct FVulkanPackedUniformBufferState`  
_L186-206_
- L188 _public member_ `FPackedUniformBuffers UniformBuffers;`
- L189 _public member_ `uint32 Mask = 0;`
- L190 _public member_ `uint32 Dirty = 0;`
- L192 _public function_ `void Init(const FVulkanShaderHeader& CodeHeader)`
- L197 _public function_ `void Reset()`
- L202 _public function_ `void SetParameter(uint32 ByteOffset, uint32 NumBytes, const void* NewValue)`

#### class `FVulkanComputePipelineDescriptorState`  
`class FVulkanComputePipelineDescriptorState : public FVulkanCommonPipelineDescriptorState`  
_L208-263_
- inherits: `FVulkanCommonPipelineDescriptorState`
- L211 _public prototype_ `FVulkanComputePipelineDescriptorState(FVulkanDevice& InDevice, FVulkanComputePipeline* InComputePipeline);`
- L212 _public function_ `virtual ~FVulkanComputePipelineDescriptorState()`
- L217 _public function_ `void Reset()`
- L223 _public function_ `FVulkanPackedUniformBufferState& GetUniformBuffers(uint8 Stage)`
- L228 _public function_ `void SetParameter(uint32 ByteOffset, uint32 NumBytes, const void* NewValue)`
- L233 _public function_ `bool UpdateDescriptorSets(FVulkanCommandListContext& Context)`
- L244 _public prototype_ `void UpdateBindlessDescriptors(FVulkanCommandListContext& Context);`
- L246 _public function_ `void BindDescriptorSets(VkCommandBuffer CmdBuffer)`
- L251 _public prototype_ `TArray<uint32> GetExcludedResources(uint32 SetIndex) const override final;`
- L254 _protected member_ `FVulkanPackedUniformBufferState PackedUniformBufferState;`
- L256 _protected member_ `FVulkanComputePipeline* ComputePipeline;`
- L259 _protected prototype_ `template<bool bUseDynamicGlobalUBs> bool InternalUpdateDescriptorSets(FVulkanCommandListContext& Context);`

#### class `FVulkanGraphicsPipelineDescriptorState`  
`class FVulkanGraphicsPipelineDescriptorState : public FVulkanCommonPipelineDescriptorState`  
_L265-329_
- inherits: `FVulkanCommonPipelineDescriptorState`
- L268 _public prototype_ `FVulkanGraphicsPipelineDescriptorState(FVulkanDevice& InDevice, FVulkanGraphicsPipelineState* InGfxPipeline);`
- L269 _public function_ `virtual ~FVulkanGraphicsPipelineDescriptorState()`
- L274 _public function_ `FVulkanPackedUniformBufferState& GetUniformBuffers(uint8 Stage)`
- L279 _public function_ `void SetParameter(uint8 Stage, uint32 ByteOffset, uint32 NumBytes, const void* NewValue)`
- L284 _public function_ `bool UpdateDescriptorSets(FVulkanCommandListContext& Context)`
- L299 _public prototype_ `void UpdateBindlessDescriptors(FVulkanCommandListContext& Context);`
- L301 _public function_ `inline void BindDescriptorSets(VkCommandBuffer CmdBuffer)`
- L306 _public function_ `void Reset()`
- L317 _public prototype_ `TArray<uint32> GetExcludedResources(uint32 SetIndex) const override final;`
- L320 _protected member_ `TStaticArray<FVulkanPackedUniformBufferState, ShaderStage::NumGraphicsStages> PackedUniformBufferStates;`
- L322 _protected member_ `FVulkanGraphicsPipelineState* GfxPipeline;`
- L325 _protected prototype_ `template<bool bUseDynamicGlobalUBs> bool InternalUpdateDescriptorSets(FVulkanCommandListContext& Context);`

#### Free symbols / members of external scopes

- L19 _externvar_ `extern TAutoConsoleVariable<int32> GDynamicGlobalUBs;`
- L332 _function_ `template <bool bIsDynamic> static inline bool SubmitPackedUniformBuffers(FVulkanDescriptorSetWriter& DescriptorWriteSet, const VulkanRHI::FVulkanAllocation& TempAllocation)`

### `Source/Runtime/VulkanRHI/Private/VulkanPlatform.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/VulkanRHI/Private/VulkanQuery.h` (Private)


#### enum `EVulkanQueryPoolType`  
`enum class EVulkanQueryPoolType : uint8`  
_L22-30_
- L24 _public enumerator_ `Occlusion`
- L25 _public enumerator_ `PipelineStats`
- L26 _public enumerator_ `Timestamp`
- L27 _public enumerator_ `ASCompactedSize`
- L29 _public enumerator_ `Count`

#### class `FVulkanQueryPool`  
`class FVulkanQueryPool`  
_L48-122_
- L51 _public prototype_ `FVulkanQueryPool(FVulkanDevice& InDevice, uint32 InMaxQueries, EVulkanQueryPoolType InQueryType);`
- L52 _public prototype_ `virtual ~FVulkanQueryPool();`
- L54 _public function_ `uint32 GetMaxQueries() const`
- L59 _public function_ `VkQueryPool GetHandle() const`
- L64 _public function_ `EVulkanQueryPoolType GetPoolType() const`
- L69 _public function_ `FVulkanDevice& GetDevice()`
- L74 _public function_ `uint32 GetQueryStride() const`
- L79 _public function_ `bool IsFull() const`
- L84 _public prototype_ `void ReserveQuery(FVulkanRenderQuery* Query);`
- L85 _public prototype_ `uint32 ReserveQuery(uint64* ResultPtr);`
- L87 _public prototype_ `void Reset(FVulkanCommandBuffer* InCmdBuffer, uint32 InQueryStride = 1u);`
- L88 _public prototype_ `bool IsStale() const;`
- L90 _public function_ `void IncrementUnusedFrameCount()`
- L95 _public function_ `void SetDirty()`
- L100 _public function_ `bool IsDirty() const`
- L106 _protected member_ `FVulkanDevice& Device;`
- L107 _protected member_ `VkQueryPool QueryPool;`
- L108 _protected member_ `const uint32 MaxQueries;`
- L109 _protected member_ `const EVulkanQueryPoolType QueryType;`
- L110 _protected member_ `TArray<TRefCountPtr<FVulkanRenderQuery>> QueryRefs;`
- L111 _protected member_ `TArray<uint64*> QueryResults;`
- L112 _protected member_ `uint32 CurrentQueryCount = 0;`
- L117 _protected member_ `uint32 QueryStride = 1u;` — When queries are issued during a multiview render pass, vkCmdBeginQuery and vkCmdEndQuery each correspond to multiple subsequent queries in the pool, one for each view. The interpretation of these per-view values is implementation dependent, but they can be summed together to get the actual value.
- L118 _protected member_ `int32 UnusedFrameCount = 0;`
- L119 _protected member_ `bool bIsDirty = true;`

#### class `FVulkanRenderQuery`  
`class FVulkanRenderQuery : public FRHIRenderQuery`  
_L124-147_
- inherits: `FRHIRenderQuery`
- L127 _public prototype_ `FVulkanRenderQuery(ERenderQueryType InType);`
- L128 _public prototype_ `virtual ~FVulkanRenderQuery();`
- L130 _public function_ `EVulkanQueryPoolType GetQueryPoolType()`
- L143 _public member_ `const ERenderQueryType QueryType;`
- L144 _public member_ `uint64 Result = 0;`
- L145 _public member_ `uint32 IndexInPool = UINT32_MAX;`
- L146 _public member_ `FVulkanSyncPointRef SyncPoint;`

#### Free symbols / members of external scopes

- L19 _typedef_ `using FVulkanSyncPointRef = TRefCountPtr<FVulkanSyncPoint>;`
- L32 _function_ `constexpr VkQueryType GetVkQueryType(EVulkanQueryPoolType Type)`

### `Source/Runtime/VulkanRHI/Private/VulkanQueue.h` (Private)


#### enum `EVulkanQueueType`  
`enum class EVulkanQueueType : uint8`  
_L26-33_
- L28 _public enumerator_ `Graphics = 0`
- L29 _public enumerator_ `AsyncCompute`
- L30 _public enumerator_ `Transfer`
- L32 _public enumerator_ `Count`

#### struct `FBinarySemaphoreSignalInfo`  
`struct FBinarySemaphoreSignalInfo`  
_L46-50_
- L48 _public member_ `uint64 TimelineValue;`
- L49 _public member_ `EVulkanQueueType QueueType;`

#### class `FVulkanQueue`  
`class FVulkanQueue`  
_L52-182_
- L55 _public prototype_ `FVulkanQueue(FVulkanDevice& InDevice, uint32 InFamilyIndex, EVulkanQueueType InQueueType);`
- L56 _public prototype_ `~FVulkanQueue();`
- L58 _public function_ `EVulkanQueueType GetQueueType() const`
- L63 _public function_ `uint32 GetFamilyIndex() const`
- L68 _public function_ `uint32 GetQueueIndex() const`
- L73 _public function_ `VkQueue GetHandle() const`
- L78 _public prototype_ `FVulkanCommandBufferPool* AcquireCommandBufferPool(EVulkanCommandBufferType CommandBufferType);`
- L79 _public prototype_ `void ReleaseCommandBufferPool(FVulkanCommandBufferPool* CommandBufferPool);`
- L81 _public function_ `VkPipelineStageFlags GetSupportedStageBits() const`
- L86 _public function_ `VkAccessFlags GetSupportedAccessFlags() const`
- L91 _public function_ `const FVulkanSemaphore* GetTimelineSemaphore() const`
- L96 _public function_ `uint64 GetLastSubmittedTimelineSemaphoreValue() const`
- L101 _public function_ `uint64 GetCompletedTimelineSemaphoreValue() const`
- L106 _public prototype_ `int32 SubmitQueuedPayloads(TMap<VkSemaphore, FBinarySemaphoreSignalInfo>& SignaledSemas);`
- L107 _public prototype_ `int32 ProcessInterruptQueue(uint64 Timeout);`
- L109 _public prototype_ `UE::RHI::GPUProfiler::FQueue GetProfilerQueue() const;`
- L111 _public prototype_ `void InitDiagnosticBuffer();`
- L112 _public function_ `class FVulkanDiagnosticBuffer* GetDiagnosticBuffer()`
- L118 _private prototype_ `void SubmitPayloads(TArrayView<FVulkanPayload*> Payloads, TMap<VkSemaphore, FBinarySemaphoreSignalInfo>& InOutSignaledSemas);`
- L119 _private prototype_ `void Submit(TArrayView<VkSubmitInfo> InSubmitInfos, FVulkanFence* Fence);`
- L121 _private prototype_ `void BindSparseResources(FVulkanPayload& Payload);`
- L125 _private member_ `VkQueue Queue;`
- L126 _private member_ `uint32 FamilyIndex;`
- L127 _private member_ `uint32 QueueIndex;`
- L128 _private member_ `EVulkanQueueType QueueType;`
- L129 _private member_ `FVulkanDevice& Device;`
- L131 _private member_ `FCriticalSection CommandBufferPoolCS;`
- L132 _private member_ `TStaticArray<TArray<FVulkanCommandBufferPool*>, (int32)EVulkanCommandBufferType::Count> CommandBufferPools;`
- L134 _private member_ `const bool bUseTimelineSemaphores;`
- L135 _private member_ `FVulkanSemaphore* TimelineSempahore = nullptr;`
- L136 _private member_ `uint64 NextTimelineSemaphoreValue = 1;`
- L137 _private member_ `uint64 CompletedTimelineSemaphoreValue = 0;`
- L139 _private member_ `uint64 SubmitCounter;`
- L140 _private member_ `VkPipelineStageFlags SupportedStages = VK_PIPELINE_STAGE_NONE;`
- L141 _private member_ `VkAccessFlags SupportedAccess = VK_ACCESS_NONE;`
- L173 _private member_ `FVulkanPayloadQueue PendingSubmission;`
- L174 _private member_ `FVulkanPayloadQueue PendingInterrupt;`
- L177 _private member_ `FVulkanTiming* Timing = nullptr;` — The active timing struct on this queue. Updated / accessed by the interrupt thread.
- L179 _private member_ `TUniquePtr<class FVulkanDiagnosticBuffer> DiagnosticBuffer;`
- L181 _private prototype_ `void FillSupportedStageBits();`

#### class `FVulkanQueue::FVulkanPayloadQueue`  
`class FVulkanPayloadQueue`  
_L143-171_
- L145 _private member_ `TSpscQueue<FVulkanPayload*> Queue;`
- L148 _public function_ `void Enqueue(FVulkanPayload* Payload)`
- L154 _public function_ `FVulkanPayload* Peek()`
- L164 _public function_ `void Pop()`
- L169 _public function_ `auto begin()`
- L170 _public function_ `auto end ()`

#### class `FVulkanDiagnosticBuffer`  
`class FVulkanDiagnosticBuffer : public FRHIDiagnosticBuffer`  
_L189-229_
- inherits: `FRHIDiagnosticBuffer`
- desc: Per Queue diagnostic buffer. Stays accessible after a GPU crash to allow readback of diagnostic messages. Also used to track the progress of the GPU via breadcrumb markers.
- L192 _public prototype_ `FVulkanDiagnosticBuffer(FVulkanDevice& InDevice, FVulkanQueue& InQueue);`
- L193 _public prototype_ `~FVulkanDiagnosticBuffer();`
- L198 _public prototype_ `void WriteMarkerIn(FVulkanCommandBuffer& CommandBuffer, FRHIBreadcrumbNode* Breadcrumb) const;`
- L199 _public prototype_ `void WriteMarkerOut(FVulkanCommandBuffer& CommandBuffer, FRHIBreadcrumbNode* Breadcrumb) const;`
- L201 _public function_ `uint32 ReadMarkerIn()`
- L206 _public function_ `uint32 ReadMarkerOut()`
- L213 _public function_ `bool IsValid() const`
- L216 _private member_ `FVulkanDevice& Device;`
- L217 _private member_ `FVulkanQueue& Queue;`
- L218 _private member_ `VkBuffer Buffer = VK_NULL_HANDLE;`
- L219 _private member_ `VulkanRHI::FVulkanAllocation Allocation;`
- L224 _private member_ `TArray<FRHIBreadcrumbAllocatorArray> ExtendedBreadcrumbAllocators;` — Extend lifetime of breadcrumbs so we can use the pointers directly One array per frame, and cycle which array is used on EndFrame
- L225 _private member_ `int32 CurrentExtendedIndex = 0;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace VulkanRHI`
- L35 _function_ `inline const TCHAR* GetVulkanQueueTypeName(EVulkanQueueType QueueType)`

### `Source/Runtime/VulkanRHI/Private/VulkanRHIPrivate.h` (Private)


#### union `UNvidiaDriverVersion`  
`union UNvidiaDriverVersion`  
_L122-139_
- L138 _public member_ `uint32 Packed;`

#### struct `UNvidiaDriverVersion::(anonymous)`  
``  
_L125-137_

#### Free symbols / members of external scopes

- L43 _function_ `template<typename BitsType> constexpr bool VKHasAllFlags(VkFlags Flags, BitsType Contains)`
- L49 _function_ `template<typename BitsType> constexpr bool VKHasAnyFlags(VkFlags Flags, BitsType Contains)`
- L54 _function_ `inline VkShaderStageFlagBits UEFrequencyToVKStageBit(EShaderFrequency InStage)`
- L76 _function_ `inline EShaderFrequency VkStageBitToUEFrequency(VkShaderStageFlagBits FlagBits)`
- L105 _function_ `static constexpr int32 GetNumStagesForBindPoint(VkPipelineBindPoint BindPoint)`
- L127 _member_ `uint32 Tertiary : 6;` (scope `UNvidiaDriverVersion::__anon41add1db0108`)
- L128 _member_ `uint32 Secondary : 8;` (scope `UNvidiaDriverVersion::__anon41add1db0108`)
- L129 _member_ `uint32 Minor : 8;` (scope `UNvidiaDriverVersion::__anon41add1db0108`)
- L130 _member_ `uint32 Major : 10;` (scope `UNvidiaDriverVersion::__anon41add1db0108`)
- L142 _prototype_ `void VulkanSetImageLayout(FVulkanCommandBuffer* CmdBuffer, VkImage Image, VkImageLayout OldLayout, VkImageLayout NewLayout, const VkImageSubresourceRange& SubresourceRange);` — Transitions an image to the specified layout. This does not update the layout cached internally by the RHI; the calling code must do that explicitly via FVulkanCommandListContext::GetLayoutManager() if necessary.
- L146 _delegate_ `DECLARE_STATS_GROUP(TEXT("Vulkan PSO"), STATGROUP_VulkanPSO, STATCAT_` — Regular pipeline creation stats
- L147 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("PSO LRU Elements"), STAT_VulkanNumPSOLRU, STATGRO`
- L148 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("PSO LRU Size"), STAT_VulkanNumPSOLRUSize, STATGROUP_V`
- L149 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num PSOs"), STAT_VulkanNumPSOs, STATGROUP_Vulka`
- L150 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Graphics PSOs"), STAT_VulkanNumGraphicsPSOs, STATGR`
- L151 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Compute PSOs"), STAT_VulkanNumComputePSOs, STATGR`
- L152 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("VulkanPSOKey Memory"), STAT_VulkanPSOKeyMemory, STAT`
- L154 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("PSO HeaderInit time"), STAT_VulkanPSOHeaderInitTime, STAT`
- L155 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("PSO Lookup time"), STAT_VulkanPSOLookupTime, STATGROU`
- L156 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("PSO Creation time"), STAT_VulkanPSOCreationTime, STATGR`
- L157 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("PSO Vulkan Creation time"), STAT_VulkanPSOVulkanCreationTime,`
- L161 _delegate_ `DECLARE_STATS_GROUP(TEXT("Vulkan Graphic Pipeline Libraries"), STATGROUP_VulkanGraphi` — Graphic pipeline library stats
- L162 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Regular PSO Compile Count"), STAT_VulkanRegPSOCompileCount, STATGROUP_Vulk`
- L163 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Library PSO Compile Count"), STAT_VulkanLibPSOCompileCount, STATGROUP_Vulk`
- L164 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num VertexInput Libraries"), STAT_VulkanNumVertexInputLibs, STATGROUP_Vulk`
- L165 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num VS Libraries"), STAT_VulkanNumVSLibs, STATGROUP_VulkanGraphic`
- L166 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num MS Libraries"), STAT_VulkanNumMSLibs, STATGROUP_VulkanGraphic`
- L167 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num PS Libraries"), STAT_VulkanNumPSLibs, STATGROUP_VulkanGraphic`
- L168 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num FragmentOutputState Libraries"), STAT_VulkanNumFragOutputStateLibs, STATGR`
- L169 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Shader Modules"), STAT_VulkanNumShaderModule, STATGROUP_VulkanGraph`
- L173 _delegate_ `DECLARE_STATS_GROUP(TEXT("Vulkan RHI"), STATGROUP_VulkanRHI, STATCAT_` — General Stats
- L174 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Draw call time"), STAT_VulkanDrawCallTime, STATGROUP`
- L175 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Dispatch call time"), STAT_VulkanDispatchCallTime, STATG`
- L176 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Draw call prep time"), STAT_VulkanDrawCallPrepareTime, STAT`
- L177 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CustomPresent time"), STAT_VulkanCustomPresentTime, STATG`
- L178 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Dispatch call prep time"), STAT_VulkanDispatchCallPrepareTime,`
- L179 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Get Or Create Pipeline"), STAT_VulkanGetOrCreatePipeline, S`
- L180 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Get DescriptorSet"), STAT_VulkanGetDescriptorSet, STATGR`
- L181 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Pipeline Bind"), STAT_VulkanPipelineBind, STATGROUP_`
- L182 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Cmd Buffers"), STAT_VulkanNumCmdBuffers, STATGROU`
- L183 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Render Passes"), STAT_VulkanNumRenderPasses, STATGR`
- L184 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Frame Buffers"), STAT_VulkanNumFrameBuffers, STATGR`
- L185 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Buffer Views"), STAT_VulkanNumBufferViews, STATGRO`
- L186 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Image Views"), STAT_VulkanNumImageViews, STATGROU`
- L187 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Physical Mem Allocations"), STAT_VulkanNumPhysicalMemAllocati`
- L188 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Uniform Buffer Creation Time"), STAT_VulkanUniformBufferCreateT`
- L189 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Apply Packed Uniform Buffers"), STAT_VulkanApplyPackedUniformBuff`
- L190 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("SRV Update Time"), STAT_VulkanSRVUpdateTime, STATGROU`
- L191 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAV Update Time"), STAT_VulkanUAVUpdateTime, STATGROU`
- L192 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Deletion Queue"), STAT_VulkanDeletionQueue, STATGROUP`
- L193 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Queue Submit"), STAT_VulkanQueueSubmit, STATGROUP_V`
- L194 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Queue Present"), STAT_VulkanQueuePresent, STATGROUP_`
- L195 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Queries"), STAT_VulkanNumQueries, STATGROUP_Vu`
- L196 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Query Pools"), STAT_VulkanNumQueryPools, STATGROU`
- L197 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Wait For Fence"), STAT_VulkanWaitFence, STATGROUP`
- L198 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Wait For Swapchain"), STAT_VulkanWaitSwapchain, STATG`
- L199 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Acquire Backbuffer"), STAT_VulkanAcquireBackBuffer, STATG`
- L200 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Staging Buffer Mgmt"), STAT_VulkanStagingBuffer, STAT`
- L201 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("VkCreateDescriptorPool"), STAT_VulkanVkCreateDescriptorPool, S`
- L202 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Created DescSet Pools"), STAT_VulkanNumDescPools`
- L203 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UpdateUniformBuffers"), STAT_VulkanUpdateUniformBuffers, STA`
- L204 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UpdateUniformBuffersRename"), STAT_VulkanUpdateUniformBuffersRenam`
- L205 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Pooled Barrier Events"), STAT_VulkanNumPooledBarrierEvents`
- L207 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Barrier Time"), STAT_VulkanBarrierTime, STATGROUP_V`
- L208 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Update DescriptorSets"), STAT_VulkanUpdateDescriptorSets, ST`
- L209 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Num Desc Sets Updated"), STAT_VulkanNumDescSets, ST`
- L210 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Num WriteDescriptors Cmd"), STAT_VulkanNumUpdateDescriptors,`
- L211 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Set unif Buffer"), STAT_VulkanSetUniformBufferTime, STATGROU`
- L212 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("VkUpdate DS"), STAT_VulkanVkUpdateDS, STATGROUP_Vu`
- L213 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Bind Vertex Streams"), STAT_VulkanBindVertexStreamsTime, STAT`
- L215 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Max Potential Desc Sets"), STAT_VulkanNumDescSetsTotal,`
- L217 _namespace_ `namespace VulkanRHI`
- L219 _function_ `static uint32 GetNumBitsPerPixel(VkFormat Format)` (scope `VulkanRHI`)
- L313 _function_ `static VkImageAspectFlags GetAspectMaskFromUEFormat(EPixelFormat Format, bool bIncludeStencil, bool bIncludeDepth = true)` (scope `VulkanRHI`)
- L329 _function_ `static bool VulkanFormatHasStencil(VkFormat Format)` (scope `VulkanRHI`)
- L345 _externvar_ `extern TAutoConsoleVariable<int32> GValidationCvar;`
- L348 _function_ `static inline VkAttachmentLoadOp RenderTargetLoadActionToVulkan(ERenderTargetLoadAction InLoadAction)`
- L365 _function_ `static inline VkAttachmentStoreOp RenderTargetStoreActionToVulkan(ERenderTargetStoreAction InStoreAction)`
- L387 _externvar_ `extern VkFormat GVulkanSRGBFormat[PF_MAX];`
- L388 _function_ `inline VkFormat UEToVkTextureFormat(EPixelFormat UEFormat, const bool bIsSRGB)`
- L400 _function_ `static inline VkFormat UEToVkBufferFormat(EVertexElementType Type)`
- L452 _function_ `static inline bool IsAstcLdrFormat(VkFormat Format)`
- L457 _function_ `static inline bool IsAstcSrgbFormat(VkFormat Format)`
- L482 _externvar_ `extern TAutoConsoleVariable<int32> CVarVulkanDebugBarrier;`
- L485 _namespace_ `namespace VulkanRHI`
- L487 _function_ `static inline FString GetPipelineCacheFilename()` (scope `VulkanRHI`)
- L492 _function_ `static inline FString GetValidationCacheFilename()` (scope `VulkanRHI`)
- L498 _function_ `inline void SetDebugName(PFN_vkSetDebugUtilsObjectNameEXT SetDebugName, VkDevice Device, VkImage Image, const char* Name)` (scope `VulkanRHI`)
- L510 _function_ `inline VkImageLayout GetMergedDepthStencilLayout(VkImageLayout DepthLayout, VkImageLayout StencilLayout)` (scope `VulkanRHI`) — Merge a depth and a stencil layout for drivers that don't support VK_KHR_separate_depth_stencil_layouts
- L542 _function_ `` (scope `VulkanRHI::GetMergedDepthStencilLayout`)
- L587 _function_ `inline void HeavyWeightBarrier(VkCommandBuffer CmdBuffer)` (scope `VulkanRHI`)
- L632 _function_ `inline void DebugHeavyWeightBarrier(VkCommandBuffer CmdBuffer, int32 CVarConditionMask)` (scope `VulkanRHI`)
- L643 _function_ `inline bool UseVulkanDescriptorCache()`
- L649 _function_ `inline bool ValidateShadingRateDataType()`
- L671 _externvar_ `extern int32 GWaitForIdleOnSubmit;`
- L674 _externvar_ `extern bool GRenderDocFound;`
- L677 _variable_ `const int GMaxCrashBufferEntries = 2048;`
- L679 _externvar_ `extern class FVulkanDynamicRHI* GVulkanRHI;`
- L681 _externvar_ `extern TAtomic<uint64> GVulkanBufferHandleIdCounter;`
- L682 _externvar_ `extern TAtomic<uint64> GVulkanBufferViewHandleIdCounter;`
- L683 _externvar_ `extern TAtomic<uint64> GVulkanImageViewHandleIdCounter;`
- L684 _externvar_ `extern TAtomic<uint64> GVulkanSamplerHandleIdCounter;`
- L685 _externvar_ `extern TAtomic<uint64> GVulkanDSetLayoutHandleIdCounter;`

### `Source/Runtime/VulkanRHI/Private/VulkanRayTracing.h` (Private)


#### class `FVulkanRayTracingPlatform`  
`class FVulkanRayTracingPlatform`  
_L18-22_
- L21 _public prototype_ `static bool CheckVulkanInstanceFunctions(VkInstance inInstance);`

#### struct `FVulkanHitGroupSystemParameters`  
`struct FVulkanHitGroupSystemParameters`  
_L27-37_
- desc: Built-in local root parameters that are always bound to all hit shaders :todo-jn: NOTE: Keep in sync with VulkanCommon.ush decl until it's put in a common header
- L29 _public member_ `FHitGroupSystemRootConstants RootConstants;`
- L31 _public member_ `uint32 BindlessHitGroupSystemIndexBuffer;`
- L32 _public member_ `uint32 BindlessHitGroupSystemVertexBuffer;`
- L34 _public member_ `uint32 BindlessUniformBuffers[32];`

#### struct `FVkRtTLASBuildData`  
`struct FVkRtTLASBuildData`  
_L40-52_
- L42 _public function_ `FVkRtTLASBuildData()`
- L49 _public member_ `VkAccelerationStructureGeometryKHR Geometry;`
- L50 _public member_ `VkAccelerationStructureBuildGeometryInfoKHR GeometryInfo;`
- L51 _public member_ `VkAccelerationStructureBuildSizesInfoKHR SizesInfo;`

#### struct `FVkRtBLASBuildData`  
`struct FVkRtBLASBuildData`  
_L54-67_
- L56 _public function_ `FVkRtBLASBuildData()`
- L62 _public member_ `TArray<VkAccelerationStructureGeometryKHR, TInlineAllocator<1>> Segments;`
- L63 _public member_ `TArray<VkAccelerationStructureGeometryLinearSweptSpheresDataNV, TInlineAllocator<1>> LSSSegments;`
- L64 _public member_ `TArray<VkAccelerationStructureBuildRangeInfoKHR, TInlineAllocator<1>> Ranges;`
- L65 _public member_ `VkAccelerationStructureBuildGeometryInfoKHR GeometryInfo;`
- L66 _public member_ `VkAccelerationStructureBuildSizesInfoKHR SizesInfo;`

#### class `FVulkanRayTracingShaderTable`  
`class FVulkanRayTracingShaderTable : public FRHIShaderBindingTable`  
_L69-180_
- inherits: `FRHIShaderBindingTable`
- L72 _public prototype_ `FVulkanRayTracingShaderTable(FRHICommandListBase& RHICmdList, FVulkanDevice& InDevice, const FRayTracingShaderBindingTableInitializer& InInitializer);`
- L73 _public prototype_ `~FVulkanRayTracingShaderTable();`
- L75 _public prototype_ `void ReleaseLocalBuffers();`
- L77 _public prototype_ `const VkStridedDeviceAddressRegionKHR* GetRegion(EShaderFrequency Frequency);`
- L79 _public prototype_ `void SetSlot(EShaderFrequency Frequency, uint32 DstSlot, uint32 SrcHandleIndex, TConstArrayView<uint8> SrcHandleData);`
- L81 _public prototype_ `VkStridedDeviceAddressRegionKHR CommitRayGenShader(FVulkanCommandListContext& Context, uint32 SrcHandleIndex, TConstArrayView<uint8> SrcHandleData);`
- L84 _public function_ `template <typename T> void SetLocalShaderParameters(EShaderFrequency Frequency, uint32 RecordIndex, uint32 InOffsetWithinRootSignature, const T& Parameters)`
- L89 _public prototype_ `void SetLocalShaderParameters(EShaderFrequency Frequency, uint32 RecordIndex, uint32 OffsetWithinRecord, const void* InData, uint32 InDataSize);`
- L91 _public function_ `void SetLooseParameterData(EShaderFrequency Frequency, uint32 RecordIndex, const void* InData, uint32 InDataSize)`
- L101 _public prototype_ `void SetInlineGeometryParameters(uint32 SegmentIndex, const void* InData, uint32 InDataSize);`
- L103 _public prototype_ `void Commit(FVulkanCommandListContext& Context, FRHIBuffer* InlineBindingDataBuffer);`
- L105 _public prototype_ `virtual FRHISizeAndStride GetInlineBindingDataSizeAndStride() const override final;`
- L107 _public function_ `void AddUBRef(FRHIUniformBuffer* UB)`
- L112 _public function_ `TArrayView<TRefCountPtr<FRHIUniformBuffer>> GetUBRefs()`
- L117 _public function_ `ERayTracingHitGroupIndexingMode GetHitGroupIndexingMode() const`
- L122 _public function_ `ERayTracingShaderBindingMode GetShaderBindingMode() const`
- L127 _public function_ `FVulkanDevice& GetDevice()`
- L135 _public member_ `static constexpr uint32 MaxBindingWorkers = 1;` — Ray tracing shader bindings can be processed in parallel. Each concurrent worker gets its own dedicated descriptor cache instance to avoid contention or locking. Scaling beyond 5 total threads does not yield any speedup in practice (RHI thread + 4 parallel workers).
- L160 _private prototype_ `FVulkanShaderTableAllocation& GetAlloc(EShaderFrequency Frequency);`
- L161 _private prototype_ `static void ReleaseLocalBuffer(FVulkanDevice& Device, FVulkanShaderTableAllocation& Alloc);`
- L163 _private member_ `FVulkanDevice& Device;`
- L165 _private member_ `ERayTracingShaderBindingMode ShaderBindingMode = ERayTracingShaderBindingMode::Disabled;`
- L166 _private member_ `ERayTracingHitGroupIndexingMode HitGroupIndexingMode = ERayTracingHitGroupIndexingMode::Allow;`
- L168 _private member_ `FVulkanShaderTableAllocation Miss;`
- L169 _private member_ `FVulkanShaderTableAllocation HitGroup;`
- L170 _private member_ `FVulkanShaderTableAllocation Callable;`
- L173 _private member_ `TArray<uint8> InlineGeometryParameterData;` — Buffer that contains per-hitrecord index and vertex buffer binding data
- L175 _private member_ `TArray<TRefCountPtr<FRHIUniformBuffer>> ReferencedUniformBuffers;`
- L178 _private member_ `const uint32 HandleSize;` — Convenience
- L179 _private member_ `const uint32 HandleSizeAligned;`

#### struct `FVulkanRayTracingShaderTable::FVulkanShaderTableAllocation`  
`struct FVulkanShaderTableAllocation`  
_L139-158_
- L141 _public function_ `FVulkanShaderTableAllocation()`
- L146 _public member_ `uint32 HandleCount = 0;`
- L147 _public member_ `bool bUseLocalRecord = false;`
- L150 _public member_ `TArray<uint8> HostBuffer;` — Host memory copy
- L153 _public member_ `VkBuffer LocalBuffer = VK_NULL_HANDLE;` — GPU Local memory copy
- L154 _public member_ `VulkanRHI::FVulkanAllocation LocalAllocation;`
- L155 _public member_ `VkStridedDeviceAddressRegionKHR Region;`
- L157 _public member_ `bool bIsDirty = true;`

#### class `FVulkanRayTracingGeometry`  
`class FVulkanRayTracingGeometry : public FRHIRayTracingGeometry`  
_L182-224_
- inherits: `FRHIRayTracingGeometry`
- L185 _public member_ `static constexpr uint32 IndicesPerPrimitive = 3;` — Only triangle meshes are supported
- L187 _public prototype_ `FVulkanRayTracingGeometry(ENoInit);`
- L188 _public prototype_ `FVulkanRayTracingGeometry(FRHICommandListBase& RHICmdList, const FRayTracingGeometryInitializer& Initializer, FVulkanDevice* InDevice);`
- L189 _public prototype_ `~FVulkanRayTracingGeometry();`
- L191 _public function_ `virtual VkDeviceAddress GetDeviceAddress() const`
- L194 _public function_ `virtual FRayTracingAccelerationStructureAddress GetAccelerationStructureAddress(uint64 GPUIndex) const final override`
- L197 _public prototype_ `void Swap(FVulkanRayTracingGeometry& Other);`
- L202 _public prototype_ `void RemoveCompactionRequest();`
- L203 _public prototype_ `void CompactAccelerationStructure(FVulkanCommandBuffer& CmdBuffer, uint64 InSizeAfterCompaction);`
- L205 _public prototype_ `void SetupHitGroupSystemParameters();`
- L206 _public prototype_ `void ReleaseBindlessHandles();`
- L208 _public prototype_ `void SetupInlineGeometryParameters(uint32 GeometrySegmentIndex, FVulkanRayTracingGeometryParameters& Parameters) const;`
- L210 _public member_ `VkAccelerationStructureKHR Handle = VK_NULL_HANDLE;`
- L211 _public member_ `VkDeviceAddress Address = 0;`
- L212 _public member_ `TRefCountPtr<FVulkanBuffer> AccelerationStructureBuffer;`
- L213 _public member_ `bool bHasPendingCompactionRequests = false;`
- L214 _public member_ `uint64 AccelerationStructureCompactedSize = 0;`
- L216 _public member_ `FVulkanDevice* const Device = nullptr;`
- L218 _public member_ `TArray<FVulkanHitGroupSystemParameters> HitGroupSystemParameters;`
- L219 _public member_ `TArray<FRHIDescriptorHandle> HitGroupSystemVertexViews;` — :todo-jn: use views?
- L220 _public member_ `FRHIDescriptorHandle HitGroupSystemIndexView;`
- L222 _public member_ `FDebugName DebugName;`
- L223 _public member_ `FName OwnerName;` — Store the path name of the owner object for resource tracking

#### class `FVulkanRayTracingScene`  
`class FVulkanRayTracingScene : public FRHIRayTracingScene`  
_L226-270_
- inherits: `FRHIRayTracingScene`
- L231 _public prototype_ `FVulkanRayTracingScene(FRayTracingSceneInitializer Initializer, FVulkanDevice& InDevice);`
- L232 _public prototype_ `~FVulkanRayTracingScene();`
- L234 _public function_ `const FRayTracingSceneInitializer& GetInitializer() const override final`
- L236 _public prototype_ `void BindBuffer(FRHIBuffer* InBuffer, uint32 InBufferOffset);`
- L238 _public function_ `inline bool IsBuilt() const`
- L248 _public member_ `FVulkanDevice& Device;`
- L250 _public member_ `const FRayTracingSceneInitializer Initializer;`
- L260 _public member_ `TUniquePtr<FVulkanView> View;`
- L262 _public member_ `uint32 NumInstances = 0;`
- L264 _public member_ `TRefCountPtr<FVulkanBuffer> AccelerationStructureBuffer;`
- L266 _public member_ `bool bBuilt = false;`
- L269 _private member_ `UE::FMutex Mutex;`

#### class `FVulkanRayTracingPipelineState`  
`class FVulkanRayTracingPipelineState : public FRHIRayTracingPipelineState`  
_L273-321_
- inherits: `FRHIRayTracingPipelineState`
- L278 _public prototype_ `FVulkanRayTracingPipelineState(FVulkanDevice& InDevice, const FRayTracingPipelineStateInitializer& Initializer);`
- L279 _public prototype_ `~FVulkanRayTracingPipelineState();`
- L281 _public function_ `VkPipeline GetPipeline() const`
- L286 _public function_ `bool IsPartialPipeline() const`
- L291 _public prototype_ `int32 GetShaderIndex(const FVulkanRayTracingShader* Shader) const;`
- L292 _public prototype_ `const FVulkanRayTracingShader* GetVulkanShader(EShaderFrequency Frequency, int32 ShaderIndex) const;`
- L293 _public prototype_ `int32 GetVulkanShaderNum(EShaderFrequency Frequency) const;`
- L294 _public prototype_ `const TArray<uint8>& GetShaderHandles(EShaderFrequency Frequency) const;`
- L297 _private member_ `FVulkanDevice& Device;`
- L305 _private prototype_ `const ShaderData& GetShaderData(EShaderFrequency Frequency) const;`
- L307 _private member_ `ShaderData RayGen;`
- L308 _private member_ `ShaderData Miss;`
- L309 _private member_ `ShaderData HitGroup;`
- L310 _private member_ `ShaderData Callable;`
- L312 _private member_ `VkPipeline Pipeline = VK_NULL_HANDLE;`
- L314 _private member_ `const bool bIsPartialPipeline;`
- L317 _public member_ `VulkanResourceFrameCounter FrameCounter;`

#### struct `FVulkanRayTracingPipelineState::ShaderData`  
`struct ShaderData`  
_L299-303_
- L301 _public member_ `TArray<TRefCountPtr<FVulkanRayTracingShader>> Shaders;`
- L302 _public member_ `TArray<uint8> ShaderHandles;`

#### class `FVulkanRayTracingCompactedSizeQueryPool`  
`class FVulkanRayTracingCompactedSizeQueryPool : public FVulkanQueryPool`  
_L323-334_
- inherits: `FVulkanQueryPool`
- L326 _public prototype_ `FVulkanRayTracingCompactedSizeQueryPool(FVulkanDevice& InDevice, uint32 InMaxQueries);`
- L328 _public prototype_ `void EndBatch(FVulkanCommandListContext& CommandContext);`
- L329 _public prototype_ `bool TryGetResults(uint32 NumResults);`
- L330 _public prototype_ `void Reset();`
- L332 _public member_ `TArray<uint64> QueryOutput;`
- L333 _public member_ `FVulkanSyncPointRef SyncPoint;`

#### class `FVulkanRayTracingCompactionRequestHandler`  
`class FVulkanRayTracingCompactionRequestHandler`  
_L337-362_
- desc: Manages all the pending BLAS compaction requests
- L342 _public prototype_ `FVulkanRayTracingCompactionRequestHandler(FVulkanDevice& InDevice);`
- L343 _public prototype_ `~FVulkanRayTracingCompactionRequestHandler();`
- L345 _public prototype_ `void RequestCompact(FVulkanRayTracingGeometry* InRTGeometry);`
- L346 _public prototype_ `bool ReleaseRequest(FVulkanRayTracingGeometry* InRTGeometry);`
- L348 _public prototype_ `void Update(FVulkanCommandListContext& InCommandContext);`
- L351 _private member_ `FVulkanDevice& Device;`
- L353 _private member_ `FCriticalSection CS;`
- L354 _private member_ `TArray<FVulkanRayTracingGeometry*> PendingRequests;`
- L355 _private member_ `TArray<VkAccelerationStructureKHR> ActiveBLASes;`
- L358 _private member_ `TArray<TRefCountPtr<FVulkanRayTracingGeometry>> ActiveRequests;` — Keep references on FVulkanRayTracingGeometry until lifetime issue is found (this prevents cancellation)
- L359 _private member_ `FVulkanSyncPointRef ActiveRequestsSyncPoint;`
- L361 _private member_ `FVulkanRayTracingCompactedSizeQueryPool* QueryPool = nullptr;`

#### Free symbols / members of external scopes

- L16 _typedef_ `using FVulkanSyncPointRef = TRefCountPtr<FVulkanSyncPoint>;`

### `Source/Runtime/VulkanRHI/Private/VulkanRenderTargetLayout.h` (Private)


#### class `FVulkanRenderTargetLayout`  
`class FVulkanRenderTargetLayout`  
_L7-130_
- L10 _public prototype_ `FVulkanRenderTargetLayout(const FGraphicsPipelineStateInitializer& Initializer);`
- L11 _public prototype_ `FVulkanRenderTargetLayout(FVulkanDevice& InDevice, const FRHISetRenderTargetsInfo& RTInfo);`
- L12 _public prototype_ `FVulkanRenderTargetLayout(FVulkanDevice& InDevice, const FRHIRenderPassInfo& RPInfo, VkImageLayout CurrentDepthLayout, VkImageLayout CurrentStencilLayout);`
- L14 _public function_ `inline uint32 GetRenderPassCompatibleHash() const`
- L19 _public function_ `inline uint32 GetRenderPassFullHash() const`
- L24 _public function_ `inline const VkOffset2D& GetOffset2D() const`
- L25 _public function_ `inline const VkOffset3D& GetOffset3D() const`
- L26 _public function_ `inline const VkExtent2D& GetExtent2D() const`
- L27 _public function_ `inline const VkExtent3D& GetExtent3D() const`
- L28 _public function_ `inline const VkAttachmentDescription* GetAttachmentDescriptions() const`
- L29 _public function_ `inline uint32 GetNumColorAttachments() const`
- L30 _public function_ `inline bool GetHasDepthStencil() const`
- L31 _public function_ `inline bool GetHasResolveAttachments() const`
- L32 _public function_ `inline bool GetHasDepthStencilResolve() const`
- L33 _public function_ `inline bool GetHasFragmentDensityAttachment() const`
- L34 _public function_ `inline uint32 GetNumAttachmentDescriptions() const`
- L35 _public function_ `inline uint32 GetNumSamples() const`
- L36 _public function_ `inline uint32 GetNumUsedClearValues() const`
- L37 _public function_ `inline bool GetIsMultiView() const`
- L38 _public function_ `inline uint32 GetMultiViewCount() const`
- L41 _public function_ `inline const VkAttachmentReference* GetColorAttachmentReferences() const`
- L42 _public function_ `inline const VkAttachmentReference* GetResolveAttachmentReferences() const`
- L43 _public function_ `inline const VkAttachmentReference* GetDepthAttachmentReference() const`
- L44 _public function_ `inline const VkAttachmentReferenceStencilLayout* GetStencilAttachmentReference() const`
- L45 _public function_ `inline const VkAttachmentReference* GetDepthStencilResolveAttachmentReference() const`
- L46 _public function_ `inline const VkAttachmentReference* GetFragmentDensityAttachmentReference() const`
- L48 _public function_ `inline const VkAttachmentDescriptionStencilLayout* GetStencilDesc() const`
- L50 _public function_ `inline const ESubpassHint GetSubpassHint() const`
- L53 _protected prototype_ `VkImageLayout GetVRSImageLayout() const;`
- L56 _protected member_ `VkAttachmentReference ColorReferences[MaxSimultaneousRenderTargets];`
- L57 _protected member_ `VkAttachmentReference DepthReference;`
- L58 _protected member_ `VkAttachmentReferenceStencilLayout StencilReference;`
- L59 _protected member_ `VkAttachmentReference FragmentDensityReference;`
- L60 _protected member_ `VkAttachmentReference ResolveReferences[MaxSimultaneousRenderTargets];`
- L61 _protected member_ `VkAttachmentReference DepthStencilResolveReference;`
- L64 _protected member_ `VkAttachmentDescription Desc[MaxSimultaneousRenderTargets * 2 + 3];` — Depth goes in the "+1" slot, Depth resolve goes in the "+2 slot", and the Shading Rate texture goes in the "+3" slot.
- L65 _protected member_ `VkAttachmentDescriptionStencilLayout StencilDesc;`
- L67 _protected member_ `uint8 NumAttachmentDescriptions;`
- L68 _protected member_ `uint8 NumColorAttachments;`
- L69 _protected member_ `uint8 NumInputAttachments = 0;`
- L70 _protected member_ `uint8 bHasDepthStencil;`
- L71 _protected member_ `uint8 bHasResolveAttachments;`
- L72 _protected member_ `uint8 bHasDepthStencilResolve;`
- L73 _protected member_ `uint8 bHasFragmentDensityAttachment;`
- L74 _protected member_ `uint8 NumSamples;`
- L75 _protected member_ `uint8 NumUsedClearValues;`
- L76 _protected member_ `ESubpassHint SubpassHint = ESubpassHint::None;`
- L77 _protected member_ `uint8 MultiViewCount;`
- L80 _protected member_ `uint32 RenderPassCompatibleHash = 0;` — Hash for a compatible RenderPass
- L82 _protected member_ `uint32 RenderPassFullHash = 0;` — Hash for the render pass including the load/store operations
- L88 _protected member_ `} Offset;`
- L94 _protected member_ `} Extent;`
- L96 _protected function_ `inline void ResetAttachments()`
- L111 _protected function_ `FVulkanRenderTargetLayout()`
- L126 _protected member_ `bool bCalculatedHash = false;`

#### union `FVulkanRenderTargetLayout::(anonymous)`  
``  
_L85-88_

#### Free symbols / members of external scopes

- L86 _member_ `VkOffset3D Offset3D;` (scope `FVulkanRenderTargetLayout::__anon76464302010a`)
- L87 _member_ `VkOffset2D Offset2D;` (scope `FVulkanRenderTargetLayout::__anon76464302010a`)
- L92 _member_ `VkExtent3D Extent3D;` (scope `FVulkanRenderTargetLayout::__anon76464302020a`)
- L93 _member_ `VkExtent2D Extent2D;` (scope `FVulkanRenderTargetLayout::__anon76464302020a`)

### `Source/Runtime/VulkanRHI/Private/VulkanRenderpass.h` (Private)


#### struct `FVulkanAttachmentReference`  
`template <typename TAttachmentReferenceType> struct FVulkanAttachmentReference : public TAttachmentReferenceType`  
_L19-37_
- inherits: `TAttachmentReferenceType`
- L22 _public function_ `FVulkanAttachmentReference()`
- L27 _public function_ `FVulkanAttachmentReference(const VkAttachmentReference& AttachmentReferenceIn, VkImageAspectFlags AspectMask)`
- L32 _public function_ `inline void SetAttachment(const VkAttachmentReference& AttachmentReferenceIn, VkImageAspectFlags AspectMask)`
- L33 _public function_ `inline void SetAttachment(const FVulkanAttachmentReference<TAttachmentReferenceType>& AttachmentReferenceIn, VkImageAspectFlags AspectMask)`
- L34 _public function_ `inline void SetDepthStencilAttachment(const VkAttachmentReference& AttachmentReferenceIn, const VkAttachmentReferenceStencilLayout* StencilReference, VkImageAspectFlags AspectMask, bool bSupportsParallelRendering)`
- L35 _public function_ `inline void ZeroStruct()`
- L36 _public function_ `inline void SetAspect(uint32 Aspect)`
- L40 _function_ `template <> inline void FVulkanAttachmentReference<VkAttachmentReference>::SetAttachment(const VkAttachmentReference& AttachmentReferenceIn, VkImageAspectFlags AspectMask)`
- L47 _function_ `template <> inline void FVulkanAttachmentReference<VkAttachmentReference2>::SetAttachment(const VkAttachmentReference& AttachmentReferenceIn, VkImageAspectFlags AspectMask)`
- L57 _function_ `template<> inline void FVulkanAttachmentReference<VkAttachmentReference2>::SetAttachment(const FVulkanAttachmentReference<VkAttachmentReference2>& AttachmentReferenceIn, VkImageAspectFlags AspectMask)`
- L67 _function_ `template <> inline void FVulkanAttachmentReference<VkAttachmentReference>::SetDepthStencilAttachment(const VkAttachmentReference& AttachmentReferenceIn, const VkAttachmentReferenceStencilLayout* StencilReference, VkImageAspectFlags AspectMask, bool bSupportsParallelRendering)`
- L76 _function_ `template <> inline void FVulkanAttachmentReference<VkAttachmentReference2>::SetDepthStencilAttachment(const VkAttachmentReference& AttachmentReferenceIn, const VkAttachmentReferenceStencilLayout* StencilReference, VkImageAspectFlags AspectMask, bool bSupportsParallelRendering)`
- L104 _function_ `template<> inline void FVulkanAttachmentReference<VkAttachmentReference>::ZeroStruct()`
- L111 _function_ `template<> inline void FVulkanAttachmentReference<VkAttachmentReference2>::ZeroStruct()`
- L121 _function_ `template<> inline void FVulkanAttachmentReference<VkAttachmentReference2>::SetAspect(uint32 Aspect)`

#### class `FVulkanSubpassDescription`  
`template <typename TSubpassDescriptionType> class FVulkanSubpassDescription`  
_L127-129_
- L135 _public function_ `FVulkanSubpassDescription()`
- L141 _public function_ `void SetColorAttachments(const TArray<FVulkanAttachmentReference<VkAttachmentReference>>& ColorAttachmentReferences, int OverrideCount = -1)`
- L147 _public function_ `void SetResolveAttachments(const TArrayView<FVulkanAttachmentReference<VkAttachmentReference>>& ResolveAttachmentReferences)`
- L156 _public function_ `void SetDepthStencilAttachment(FVulkanAttachmentReference<VkAttachmentReference>* DepthStencilAttachmentReference)`
- L161 _public function_ `void SetInputAttachments(FVulkanAttachmentReference<VkAttachmentReference>* InputAttachmentReferences, uint32 NumInputAttachmentReferences)`
- L167 _public function_ `void SetDepthStencilResolveAttachment(VkSubpassDescriptionDepthStencilResolveKHR* DepthStencilResolveAttachmentDesc)`
- L172 _public function_ `void SetShadingRateAttachment(VkFragmentShadingRateAttachmentInfoKHR* )`
- L177 _public function_ `void SetMultiViewMask(uint32_t Mask)`
- L194 _public function_ `void SetColorAttachments(const TArray<FVulkanAttachmentReference<VkAttachmentReference2>>& ColorAttachmentReferences, int OverrideCount = -1)`
- L200 _public function_ `void SetResolveAttachments(const TArrayView<FVulkanAttachmentReference<VkAttachmentReference2>>& ResolveAttachmentReferences)`
- L209 _public function_ `void SetDepthStencilAttachment(FVulkanAttachmentReference<VkAttachmentReference2>* DepthStencilAttachmentReference)`
- L214 _public function_ `void SetInputAttachments(FVulkanAttachmentReference<VkAttachmentReference2>* InputAttachmentReferences, uint32 NumInputAttachmentReferences)`
- L227 _public function_ `void SetShadingRateAttachment(VkFragmentShadingRateAttachmentInfoKHR* ShadingRateAttachmentInfo)`

#### struct `FVulkanSubpassDescription`  
`template<> struct FVulkanSubpassDescription<VkSubpassDescription> : public VkSubpassDescription`  
_L132-181_
- inherits: `VkSubpassDescription`
- L135 _public function_ `FVulkanSubpassDescription()`
- L141 _public function_ `void SetColorAttachments(const TArray<FVulkanAttachmentReference<VkAttachmentReference>>& ColorAttachmentReferences, int OverrideCount = -1)`
- L147 _public function_ `void SetResolveAttachments(const TArrayView<FVulkanAttachmentReference<VkAttachmentReference>>& ResolveAttachmentReferences)`
- L156 _public function_ `void SetDepthStencilAttachment(FVulkanAttachmentReference<VkAttachmentReference>* DepthStencilAttachmentReference)`
- L161 _public function_ `void SetInputAttachments(FVulkanAttachmentReference<VkAttachmentReference>* InputAttachmentReferences, uint32 NumInputAttachmentReferences)`
- L167 _public function_ `void SetDepthStencilResolveAttachment(VkSubpassDescriptionDepthStencilResolveKHR* DepthStencilResolveAttachmentDesc)`
- L172 _public function_ `void SetShadingRateAttachment(VkFragmentShadingRateAttachmentInfoKHR* )`
- L177 _public function_ `void SetMultiViewMask(uint32_t Mask)`
- L194 _public function_ `void SetColorAttachments(const TArray<FVulkanAttachmentReference<VkAttachmentReference2>>& ColorAttachmentReferences, int OverrideCount = -1)`
- L200 _public function_ `void SetResolveAttachments(const TArrayView<FVulkanAttachmentReference<VkAttachmentReference2>>& ResolveAttachmentReferences)`
- L209 _public function_ `void SetDepthStencilAttachment(FVulkanAttachmentReference<VkAttachmentReference2>* DepthStencilAttachmentReference)`
- L214 _public function_ `void SetInputAttachments(FVulkanAttachmentReference<VkAttachmentReference2>* InputAttachmentReferences, uint32 NumInputAttachmentReferences)`
- L227 _public function_ `void SetShadingRateAttachment(VkFragmentShadingRateAttachmentInfoKHR* ShadingRateAttachmentInfo)`

#### struct `FVulkanSubpassDescription`  
`template<> struct FVulkanSubpassDescription<VkSubpassDescription2> : public VkSubpassDescription2`  
_L184-238_
- inherits: `VkSubpassDescription2`
- L135 _public function_ `FVulkanSubpassDescription()`
- L141 _public function_ `void SetColorAttachments(const TArray<FVulkanAttachmentReference<VkAttachmentReference>>& ColorAttachmentReferences, int OverrideCount = -1)`
- L147 _public function_ `void SetResolveAttachments(const TArrayView<FVulkanAttachmentReference<VkAttachmentReference>>& ResolveAttachmentReferences)`
- L156 _public function_ `void SetDepthStencilAttachment(FVulkanAttachmentReference<VkAttachmentReference>* DepthStencilAttachmentReference)`
- L161 _public function_ `void SetInputAttachments(FVulkanAttachmentReference<VkAttachmentReference>* InputAttachmentReferences, uint32 NumInputAttachmentReferences)`
- L167 _public function_ `void SetDepthStencilResolveAttachment(VkSubpassDescriptionDepthStencilResolveKHR* DepthStencilResolveAttachmentDesc)`
- L172 _public function_ `void SetShadingRateAttachment(VkFragmentShadingRateAttachmentInfoKHR* )`
- L177 _public function_ `void SetMultiViewMask(uint32_t Mask)`
- L194 _public function_ `void SetColorAttachments(const TArray<FVulkanAttachmentReference<VkAttachmentReference2>>& ColorAttachmentReferences, int OverrideCount = -1)`
- L200 _public function_ `void SetResolveAttachments(const TArrayView<FVulkanAttachmentReference<VkAttachmentReference2>>& ResolveAttachmentReferences)`
- L209 _public function_ `void SetDepthStencilAttachment(FVulkanAttachmentReference<VkAttachmentReference2>* DepthStencilAttachmentReference)`
- L214 _public function_ `void SetInputAttachments(FVulkanAttachmentReference<VkAttachmentReference2>* InputAttachmentReferences, uint32 NumInputAttachmentReferences)`
- L227 _public function_ `void SetShadingRateAttachment(VkFragmentShadingRateAttachmentInfoKHR* ShadingRateAttachmentInfo)`

#### struct `FVulkanSubpassDependency`  
`template <typename TSubpassDependencyType> struct FVulkanSubpassDependency : public TSubpassDependencyType`  
_L241-244_
- inherits: `TSubpassDependencyType`
- L250 _public function_ `FVulkanSubpassDependency()`

#### struct `FVulkanSubpassDependency`  
`template<> struct FVulkanSubpassDependency<VkSubpassDependency> : public VkSubpassDependency`  
_L247-254_
- inherits: `VkSubpassDependency`
- L250 _public function_ `FVulkanSubpassDependency()`

#### struct `FVulkanSubpassDependency`  
`template<> struct FVulkanSubpassDependency<VkSubpassDependency2> : public VkSubpassDependency2`  
_L257-265_
- inherits: `VkSubpassDependency2`
- L250 _public function_ `FVulkanSubpassDependency()`

#### struct `FVulkanAttachmentDescription`  
`template<typename TAttachmentDescriptionType> struct FVulkanAttachmentDescription`  
_L268-270_
- L276 _public function_ `FVulkanAttachmentDescription()`
- L281 _public function_ `FVulkanAttachmentDescription(const VkAttachmentDescription& InDesc)`
- L294 _public function_ `FVulkanAttachmentDescription(const VkAttachmentDescription& InDesc, const VkAttachmentDescriptionStencilLayout* InStencilDesc, bool bSupportsParallelRendering)`

#### struct `FVulkanAttachmentDescription`  
`template<> struct FVulkanAttachmentDescription<VkAttachmentDescription> : public VkAttachmentDescription`  
_L273-310_
- inherits: `VkAttachmentDescription`
- L276 _public function_ `FVulkanAttachmentDescription()`
- L281 _public function_ `FVulkanAttachmentDescription(const VkAttachmentDescription& InDesc)`
- L294 _public function_ `FVulkanAttachmentDescription(const VkAttachmentDescription& InDesc, const VkAttachmentDescriptionStencilLayout* InStencilDesc, bool bSupportsParallelRendering)`

#### struct `FVulkanAttachmentDescription`  
`template<> struct FVulkanAttachmentDescription<VkAttachmentDescription2> : public VkAttachmentDescription2`  
_L313-366_
- inherits: `VkAttachmentDescription2`
- L276 _public function_ `FVulkanAttachmentDescription()`
- L281 _public function_ `FVulkanAttachmentDescription(const VkAttachmentDescription& InDesc)`
- L294 _public function_ `FVulkanAttachmentDescription(const VkAttachmentDescription& InDesc, const VkAttachmentDescriptionStencilLayout* InStencilDesc, bool bSupportsParallelRendering)`

#### struct `FVulkanRenderPassCreateInfo`  
`template <typename T> struct FVulkanRenderPassCreateInfo`  
_L369-370_
- L376 _public function_ `FVulkanRenderPassCreateInfo()`
- L381 _public function_ `void SetCorrelationMask(const uint32_t* MaskPtr)`
- L386 _public function_ `VkRenderPass Create(FVulkanDevice& Device)`

#### struct `FVulkanRenderPassCreateInfo`  
`template<> struct FVulkanRenderPassCreateInfo<VkRenderPassCreateInfo> : public VkRenderPassCreateInfo`  
_L373-392_
- inherits: `VkRenderPassCreateInfo`
- L376 _public function_ `FVulkanRenderPassCreateInfo()`
- L381 _public function_ `void SetCorrelationMask(const uint32_t* MaskPtr)`
- L386 _public function_ `VkRenderPass Create(FVulkanDevice& Device)`

#### struct `FVulkanRenderPassFragmentDensityMapCreateInfoEXT`  
`struct FVulkanRenderPassFragmentDensityMapCreateInfoEXT : public VkRenderPassFragmentDensityMapCreateInfoEXT`  
_L394-401_
- inherits: `VkRenderPassFragmentDensityMapCreateInfoEXT`
- L397 _public function_ `FVulkanRenderPassFragmentDensityMapCreateInfoEXT()`

#### struct `FVulkanRenderPassMultiviewCreateInfo`  
`struct FVulkanRenderPassMultiviewCreateInfo : public VkRenderPassMultiviewCreateInfo`  
_L403-410_
- inherits: `VkRenderPassMultiviewCreateInfo`
- L406 _public function_ `FVulkanRenderPassMultiviewCreateInfo()`

#### struct `FVulkanRenderPassCreateInfo`  
`template<> struct FVulkanRenderPassCreateInfo<VkRenderPassCreateInfo2> : public VkRenderPassCreateInfo2`  
_L413-433_
- inherits: `VkRenderPassCreateInfo2`
- L376 _public function_ `FVulkanRenderPassCreateInfo()`
- L381 _public function_ `void SetCorrelationMask(const uint32_t* MaskPtr)`
- L386 _public function_ `VkRenderPass Create(FVulkanDevice& Device)`

#### struct `FVulkanFragmentShadingRateAttachmentInfo`  
`struct FVulkanFragmentShadingRateAttachmentInfo : public VkFragmentShadingRateAttachmentInfoKHR`  
_L435-450_
- inherits: `VkFragmentShadingRateAttachmentInfoKHR`
- L438 _public function_ `FVulkanFragmentShadingRateAttachmentInfo()`
- L446 _public function_ `void SetReference(FVulkanAttachmentReference<VkAttachmentReference2>* AttachmentReference)`

#### struct `FVulkanDepthStencilResolveSubpassDesc`  
`struct FVulkanDepthStencilResolveSubpassDesc : public VkSubpassDescriptionDepthStencilResolveKHR`  
_L452-470_
- inherits: `VkSubpassDescriptionDepthStencilResolveKHR`
- L455 _public function_ `FVulkanDepthStencilResolveSubpassDesc()`
- L460 _public function_ `void SetResolveModes(VkResolveModeFlagBits DepthMode, VkResolveModeFlagBits StencilMode)`
- L466 _public function_ `void SetReference(FVulkanAttachmentReference<VkAttachmentReference2>* AttachmentReference)`

#### class `FVulkanRenderPass`  
`class FVulkanRenderPass`  
_L472-502_
- L475 _public function_ `inline const FVulkanRenderTargetLayout& GetLayout() const`
- L480 _public function_ `inline VkRenderPass GetHandle() const`
- L485 _public function_ `inline uint32 GetNumUsedClearValues() const`
- L494 _private prototype_ `FVulkanRenderPass(FVulkanDevice& Device, const FVulkanRenderTargetLayout& RTLayout);`
- L495 _private prototype_ `~FVulkanRenderPass();`
- L498 _private member_ `FVulkanRenderTargetLayout Layout;`
- L499 _private member_ `VkRenderPass RenderPass;`
- L500 _private member_ `uint32 NumUsedClearValues;`
- L501 _private member_ `FVulkanDevice& Device;`

#### class `FVulkanRenderPassBuilder`  
`template <typename TSubpassDescriptionClass, typename TSubpassDependencyClass, typename TAttachmentReferenceClass, typename TAttachmentDescriptionClass, typename TRenderPassCreateInfoClass> class FVulkanRenderPassBuilder`  
_L507-914_
- L510 _public function_ `FVulkanRenderPassBuilder(FVulkanDevice& InDevice) : Device(InDevice) , CorrelationMask(0)`
- L515 _public function_ `void BuildCreateInfo(const FVulkanRenderTargetLayout& RTLayout)`
- L865 _public function_ `VkRenderPass Create(const FVulkanRenderTargetLayout& RTLayout)`
- L872 _public function_ `TRenderPassCreateInfoClass& GetCreateInfo()`
- L878 _private member_ `TSubpassDescriptionClass SubpassDescriptions[8];`
- L879 _private member_ `TSubpassDependencyClass SubpassDependencies[8];`
- L881 _private member_ `TArray<TAttachmentReferenceClass> ColorAttachmentReferences;`
- L882 _private member_ `TArray<TAttachmentReferenceClass> ResolveAttachmentReferences;`
- L885 _private member_ `static const uint32 InputAttachment1Count = 1;` — Color write and depth read sub-pass
- L886 _private member_ `TAttachmentReferenceClass InputAttachments1[InputAttachment1Count];`
- L889 _private member_ `TAttachmentReferenceClass InputAttachments2[MaxSimultaneousRenderTargets + 1];` — Two subpasses for deferred shading
- L890 _private member_ `TAttachmentReferenceClass DepthStencilAttachment;`
- L892 _private member_ `TAttachmentReferenceClass DepthStencilAttachmentReference;`
- L893 _private member_ `TArray<TAttachmentDescriptionClass> AttachmentDescriptions;`
- L896 _private member_ `TAttachmentReferenceClass InputAttachments3[MaxSimultaneousRenderTargets + 1];` — Tonemap subpass
- L897 _private member_ `TAttachmentReferenceClass ColorAttachments3[MaxSimultaneousRenderTargets + 1];`
- L899 _private member_ `FVulkanAttachmentReference<VkAttachmentReference2> ShadingRateAttachmentReference;`
- L900 _private member_ `FVulkanFragmentShadingRateAttachmentInfo FragmentShadingRateAttachmentInfo;`
- L903 _private member_ `FVulkanAttachmentReference<VkAttachmentReference2> DepthStencilResolveAttachmentReference;` — Depth stencil resolve
- L904 _private member_ `FVulkanDepthStencilResolveSubpassDesc DepthStencilResolveSubpassDesc;`
- L906 _private member_ `FVulkanRenderPassFragmentDensityMapCreateInfoEXT FragDensityCreateInfo;`
- L907 _private member_ `FVulkanRenderPassMultiviewCreateInfo MultiviewInfo;`
- L909 _private member_ `TRenderPassCreateInfoClass CreateInfo;`
- L910 _private member_ `FVulkanDevice& Device;`
- L912 _private member_ `uint32 ViewMask[2];`
- L913 _private member_ `uint32 CorrelationMask;`

#### struct `FVulkanBeginRenderPassInfo`  
`struct FVulkanBeginRenderPassInfo`  
_L918-923_
- L920 _public member_ `FVulkanRenderPass& RenderPass;`
- L921 _public member_ `FVulkanFramebuffer& Framebuffer;`
- L922 _public member_ `bool bIsParallelRenderPass;`

#### class `FVulkanRenderPassManager`  
`class FVulkanRenderPassManager`  
_L925-978_
- L928 _public function_ `FVulkanRenderPassManager(FVulkanDevice& InDevice) : Device(InDevice)`
- L929 _public prototype_ `~FVulkanRenderPassManager();`
- L931 _public prototype_ `FVulkanFramebuffer* GetOrCreateFramebuffer(const FRHISetRenderTargetsInfo& RenderTargetsInfo, const FVulkanRenderTargetLayout& RTLayout, FVulkanRenderPass& RenderPass);`
- L932 _public function_ `FVulkanRenderPass* GetOrCreateRenderPass(const FVulkanRenderTargetLayout& RTLayout)`
- L959 _public prototype_ `void BeginRenderPass(FVulkanCommandListContext& Context, const FRHIRenderPassInfo& RPInfo, const FVulkanRenderTargetLayout& RTLayout, const FVulkanBeginRenderPassInfo& BeginRenderPassInfo);`
- L960 _public prototype_ `void EndRenderPass(FVulkanCommandListContext& Context);`
- L962 _public member_ `FRWLock RenderPassesLock;`
- L963 _public member_ `FRWLock FramebuffersLock;`
- L965 _public prototype_ `void NotifyDeletedRenderTarget(VkImage Image);`
- L969 _private member_ `TMap<uint32, FVulkanRenderPass*> RenderPasses;`
- L975 _private member_ `TMap<uint32, FFramebufferList*> Framebuffers;`
- L977 _private member_ `FVulkanDevice& Device;`

#### struct `FVulkanRenderPassManager::FFramebufferList`  
`struct FFramebufferList`  
_L971-974_
- L973 _public member_ `TArray<FVulkanFramebuffer*> Framebuffer;`

#### Free symbols / members of external scopes

- L504 _externvar_ `extern int32 GVulkanInputAttachmentShaderRead;`
- L916 _prototype_ `VkRenderPass CreateVulkanRenderPass(FVulkanDevice& Device, const FVulkanRenderTargetLayout& RTLayout);`

### `Source/Runtime/VulkanRHI/Private/VulkanResourceCollection.h` (Private)


#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIResourceCollection>`  
_L12-15_
- L14 _public typedef_ `using TConcreteType = FVulkanResourceCollection;`

#### Free symbols / members of external scopes

- L9 _typedef_ `using FVulkanResourceCollection = UE::RHICore::FGenericResourceCollection;`

### `Source/Runtime/VulkanRHI/Private/VulkanResources.h` (Private)


#### enum `(anonymous)`  
``  
_L48-52_

#### class `FVulkanVertexDeclaration`  
`class FVulkanVertexDeclaration : public FRHIVertexDeclaration`  
_L72-90_
- inherits: `FRHIVertexDeclaration`
- desc: This represents a vertex declaration that hasn't been combined with a specific shader to create a bound shader.
- L75 _public member_ `FVertexDeclarationElementList Elements;`
- L76 _public member_ `uint32 Hash;`
- L77 _public member_ `uint32 HashNoStrides;`
- L79 _public prototype_ `FVulkanVertexDeclaration(const FVertexDeclarationElementList& InElements, uint32 InHash, uint32 InHashNoStrides);`
- L81 _public function_ `virtual bool GetInitializer(FVertexDeclarationElementList& Out) final override`
- L87 _public prototype_ `static void EmptyCache();`
- L89 _public function_ `virtual uint32 GetPrecachePSOHash() const final override`

#### class `FVulkanShaderModule`  
`class FVulkanShaderModule : public FRefCountedObject`  
_L94-106_
- inherits: `FRefCountedObject`
- L96 _private member_ `static FVulkanDevice* Device;`
- L97 _private member_ `VkShaderModule ActualShaderModule;`
- L99 _public function_ `FVulkanShaderModule(FVulkanDevice* DeviceIn, VkShaderModule ShaderModuleIn) : ActualShaderModule(ShaderModuleIn)`
- L104 _public prototype_ `virtual ~FVulkanShaderModule();`
- L105 _public function_ `VkShaderModule& GetVkShaderModule()`

#### class `FVulkanShader`  
`class FVulkanShader : public IRefCountedObject`  
_L108-271_
- inherits: `IRefCountedObject`
- L112 _protected member_ `static FCriticalSection VulkanShaderModulesMapCS;`
- L115 _public prototype_ `virtual ~FVulkanShader();`
- L117 _public prototype_ `void PurgeShaderModules();`
- L119 _public prototype_ `TRefCountPtr<FVulkanShaderModule> GetOrCreateHandle();`
- L121 _public function_ `TRefCountPtr<FVulkanShaderModule> GetOrCreateHandle(const FVulkanLayout* Layout, uint32 LayoutHash)`
- L133 _public function_ `TRefCountPtr<FVulkanShaderModule> GetOrCreateHandle(const FGfxPipelineDesc& Desc, const FVulkanLayout* Layout, uint32 LayoutHash)`
- L150 _public function_ `const FString& GetDebugName() const`
- L156 _public function_ `void GetEntryPoint(ANSICHAR* Name, int32 NameLength) const` — Name should be pointing to "main_"
- L161 _public function_ `FORCEINLINE const FVulkanShaderHeader& GetCodeHeader() const`
- L166 _public function_ `uint64 GetShaderKey() const`
- L188 _public function_ `inline FSpirvCode GetSpirvCode() const`
- L193 _public prototype_ `FSpirvCode GetPatchedSpirvCode(const FGfxPipelineDesc& Desc, const FVulkanLayout* Layout);`
- L195 _public member_ `TArray<FUniformBufferStaticSlot>& StaticSlots;`
- L197 _public function_ `void SetUsesBindless(bool bValue)`
- L202 _public function_ `bool UsesBindless() const`
- L207 _public function_ `void WaitForAsyncCompile()`
- L215 _public function_ `VkShaderEXT GetShaderObject() const`
- L223 _protected member_ `FString DebugEntryPoint;`
- L225 _protected member_ `uint64 ShaderKey;`
- L228 _protected member_ `FVulkanShaderHeader CodeHeader;` — External bindings for this shader.
- L229 _protected member_ `TMap<uint32, TRefCountPtr<FVulkanShaderModule>> ShaderModules;`
- L230 _protected member_ `const EShaderFrequency Frequency;`
- L231 _protected member_ `bool bUsesBindless = false;`
- L233 _protected member_ `VkPipeline PipelineLibrary = VK_NULL_HANDLE;`
- L234 _protected member_ `VkShaderEXT ShaderObject = VK_NULL_HANDLE;`
- L235 _protected member_ `FGraphEventRef AsyncCompileTask;`
- L247 _protected member_ `} SpirvContainer;`
- L250 _protected prototype_ `static FSpirvCode PatchSpirvInputAttachments(FSpirvCode& SpirvCode);`
- L252 _protected prototype_ `static FSpirvCode GetSpirvCode(const FSpirvContainer& Container);`
- L255 _protected member_ `FVulkanDevice* Device;`
- L257 _protected prototype_ `TRefCountPtr<FVulkanShaderModule> CreateHandle(const FVulkanLayout* Layout, uint32 LayoutHash);`
- L258 _protected prototype_ `TRefCountPtr<FVulkanShaderModule> CreateHandle(const FGfxPipelineDesc& Desc, const FVulkanLayout* Layout, uint32 LayoutHash);`
- L260 _protected prototype_ `bool NeedsSpirvInputAttachmentPatching(const FGfxPipelineDesc& Desc) const;`
- L262 _protected prototype_ `FVulkanShader(FVulkanDevice* InDevice, EShaderFrequency InFrequency, FVulkanShaderHeader&& InCodeHeader, FSpirvContainer&& InSpirvContainer, uint64 InShaderKey, TArray<FUniformBufferStaticSlot>& InStaticSlots);`

#### class `FVulkanShader::FSpirvCode`  
`class FSpirvCode`  
_L173-186_
- desc: This provides a view of the raw spirv bytecode. If it is stored compressed then the result of GetSpirvCode will contain the decompressed spirv.
- L176 _private function_ `explicit FSpirvCode(TArray<uint32>&& UncompressedCodeIn) : UncompressedCode(MoveTemp(UncompressedCodeIn))`
- L180 _private function_ `explicit FSpirvCode(TArrayView<uint32> UncompressedCodeView) : CodeView(UncompressedCodeView)`
- L181 _private member_ `TArrayView<uint32> CodeView;`
- L182 _private member_ `TArray<uint32> UncompressedCode;`
- L184 _public function_ `TArrayView<uint32> GetCodeView()`
- L185 _public function_ `int32 GetCodeSizeInBytes()`

#### class `FVulkanShader::FSpirvContainer`  
`class FSpirvContainer`  
_L238-247_
- L241 _private member_ `TArray<uint8> SpirvCode;`
- L242 _private member_ `int32 UncompressedSizeBytes = -1;`
- L244 _public function_ `bool IsCompressed() const`
- L245 _public function_ `int32 GetSizeBytes() const`

#### class `TVulkanBaseShader`  
`template<typename BaseResourceType, EShaderFrequency ShaderType> class TVulkanBaseShader : public BaseResourceType, public FVulkanShader`  
_L275-301_
- inherits: `BaseResourceType,FVulkanShader`
- desc: This represents a vertex shader that hasn't been combined with a specific declaration to create a bound shader.
- L278 _private function_ `TVulkanBaseShader(FVulkanDevice* InDevice, FShaderResourceTable&& InSRT, FVulkanShaderHeader&& InCodeHeader, FSpirvContainer&& InSpirvContainer, uint64 InShaderKey) : BaseResourceType() , FVulkanShader(InDevice, ShaderType, MoveTemp(InCodeHeader), MoveTemp(InSpirvContainer), InShaderKey, BaseResourceType::StaticSlots)`
- L289 _public function_ `virtual void AddRef() const override final` — IRefCountedObject interface.
- L293 _public function_ `virtual FReturnedRefCountValue Release() const override final`
- L297 _public function_ `virtual FReturnedRefCountValue GetRefCount() const override final`

#### enum `TVulkanBaseShader::(anonymous)`  
`enum`  
_L286-286_

#### class `FVulkanRayTracingShader`  
`class FVulkanRayTracingShader : public FRHIRayTracingShader, public FVulkanShader`  
_L310-346_
- inherits: `FRHIRayTracingShader,FVulkanShader`
- L313 _private function_ `FVulkanRayTracingShader(FVulkanDevice* InDevice, EShaderFrequency InFrequency, FShaderResourceTable&& InSRT, FVulkanShaderHeader&& InCodeHeader, FSpirvContainer&& InSpirvContainer, uint64 InShaderKey) : FRHIRayTracingShader(InFrequency) , FVulkanShader(InDevice, InFrequency, MoveTemp(InCodeHeader), MoveTemp(InSpirvContainer), InShaderKey, FRHIRayTracingShader::StaticSlots)`
- L320 _private member_ `FSpirvContainer AnyHitSpirvContainer;`
- L321 _private member_ `FSpirvContainer IntersectionSpirvContainer;`
- L326 _public member_ `static const uint32 MainModuleIdentifier = 0;`
- L327 _public member_ `static const uint32 ClosestHitModuleIdentifier = MainModuleIdentifier;`
- L328 _public member_ `static const uint32 AnyHitModuleIdentifier = 1;`
- L329 _public member_ `static const uint32 IntersectionModuleIdentifier = 2;`
- L331 _public prototype_ `TRefCountPtr<FVulkanShaderModule> GetOrCreateHandle(uint32 ModuleIdentifier);`
- L334 _public function_ `virtual void AddRef() const override final` — IRefCountedObject interface.
- L338 _public function_ `virtual FReturnedRefCountValue Release() const override final`
- L342 _public function_ `virtual FReturnedRefCountValue GetRefCount() const override final`

#### class `FVulkanShaderFactory`  
`class FVulkanShaderFactory`  
_L348-381_
- L351 _public prototype_ `~FVulkanShaderFactory();`
- L354 _public prototype_ `template <typename ShaderType> ShaderType* CreateShader(TArrayView<const uint8> Code, FVulkanDevice* Device);`
- L357 _public function_ `template <typename ShaderType> ShaderType* LookupShader(uint64 ShaderKey) const`
- L372 _public prototype_ `template <EShaderFrequency ShaderFrequency> FVulkanRayTracingShader* CreateRayTracingShader(TArrayView<const uint8> Code, FVulkanDevice* Device);`
- L374 _public prototype_ `void LookupGfxShaders(const uint64 InShaderKeys[ShaderStage::NumGraphicsStages], FVulkanShader* OutShaders[ShaderStage::NumGraphicsStages]) const;`
- L376 _public prototype_ `void OnDeleteShader(const FVulkanShader& Shader);`
- L379 _private member_ `mutable FRWLock RWLock[SF_NumFrequencies];`
- L380 _private member_ `TMap<uint64, FVulkanShader*> ShaderMap[SF_NumFrequencies];`

#### class `FVulkanBoundShaderState`  
`class FVulkanBoundShaderState : public FRHIBoundShaderState`  
_L383-422_
- inherits: `FRHIBoundShaderState`
- L386 _public prototype_ `FVulkanBoundShaderState( FRHIVertexDeclaration* InVertexDeclarationRHI, FRHIVertexShader* InVertexShaderRHI, FRHIPixelShader* InPixelShaderRHI, FRHIGeometryShader* InGeometryShaderRHI );`
- L393 _public prototype_ `virtual ~FVulkanBoundShaderState();`
- L395 _public function_ `FORCEINLINE FVulkanVertexShader* GetVertexShader() const`
- L396 _public function_ `FORCEINLINE FVulkanPixelShader* GetPixelShader() const`
- L397 _public function_ `FORCEINLINE FVulkanMeshShader* GetMeshShader() const`
- L398 _public function_ `FORCEINLINE FVulkanTaskShader* GetTaskShader() const`
- L399 _public function_ `FORCEINLINE FVulkanGeometryShader* GetGeometryShader() const`
- L401 _public function_ `const FVulkanShader* GetShader(ShaderStage::EStage Stage) const`
- L421 _private member_ `FCachedBoundShaderStateLink_Threadsafe CacheLink;`

#### struct `FVulkanCpuReadbackBuffer`  
`struct FVulkanCpuReadbackBuffer`  
_L424-428_
- L426 _public member_ `VkBuffer Buffer;`
- L427 _public member_ `uint32 MipOffsets[MAX_TEXTURE_MIP_COUNT];`

#### struct `FVulkanTextureViewDesc`  
`struct FVulkanTextureViewDesc`  
_L431-446_
- L433 _public member_ `VkImageViewType ViewType = VK_IMAGE_VIEW_TYPE_MAX_ENUM;`
- L434 _public member_ `VkImageAspectFlags AspectFlags = VK_IMAGE_ASPECT_NONE;`
- L435 _public member_ `EPixelFormat UEFormat = PF_Unknown;`
- L436 _public member_ `VkFormat Format = VK_FORMAT_UNDEFINED;`
- L437 _public member_ `uint32 FirstMip = 0;`
- L438 _public member_ `uint32 NumMips = VK_REMAINING_MIP_LEVELS;`
- L439 _public member_ `uint32 ArraySliceIndex = 0;`
- L440 _public member_ `uint32 NumArraySlices = VK_REMAINING_ARRAY_LAYERS;`
- L441 _public member_ `VkImageUsageFlags ImageUsageFlags = 0;`
- L442 _public member_ `VkSamplerYcbcrConversion SamplerYcbcrConversion = VK_NULL_HANDLE;`
- L443 _public member_ `bool bUseIdentitySwizzle = false;`
- L445 _public prototype_ `uint32 GetHash() const;`

#### class `FVulkanView`  
`class FVulkanView`  
_L448-551_
- L490 _public typedef_ `> TStorage;`
- L501 _public prototype_ `FVulkanView(FVulkanDevice& InDevice, ERHIDescriptorType InDescriptorType);`
- L503 _public prototype_ `~FVulkanView();`
- L505 _public prototype_ `void Invalidate();`
- L507 _public function_ `EType GetViewType() const`
- L512 _public function_ `bool IsInitialized() const`
- L517 _public function_ `FTypedBufferView const& GetTypedBufferView () const`
- L518 _public function_ `FTextureView const& GetTextureView () const`
- L519 _public function_ `FStructuredBufferView const& GetStructuredBufferView () const`
- L520 _public function_ `FAccelerationStructureView const& GetAccelerationStructureView() const`
- L522 _public prototype_ `void CreateTextureView(VkImage InImage, const FVulkanTextureViewDesc& ViewDesc);`
- L523 _public prototype_ `void UpdateTextureView(const FVulkanContextArray& Contexts, VkImage InImage, const FVulkanTextureViewDesc& ViewDesc);`
- L526 _public prototype_ `void InitAsTypedBufferView(const FVulkanContextArray& Contexts, FVulkanBuffer* Buffer, EPixelFormat Format, uint32 InOffset, uint32 InSize);` — NOTE: The InOffset applies to the FVulkanBuffer (it does not include any internal Allocation offsets that may exist)
- L529 _public prototype_ `void InitAsStructuredBufferView(const FVulkanContextArray& Contexts, FVulkanBuffer* Buffer, uint32 InOffset, uint32 InSize);` — NOTE: The InOffset applies to the FVulkanBuffer (it does not include any internal Allocation offsets that may exist)
- L530 _public prototype_ `void InitAsAccelerationStructureView(const FVulkanContextArray& Contexts, FVulkanBuffer* Buffer, uint32 Offset, uint32 Size);`
- L533 _public prototype_ `FVulkanView(FVulkanView &&) = delete;` — No moving or copying
- L534 _public prototype_ `FVulkanView(FVulkanView const&) = delete;`
- L535 _public prototype_ `FVulkanView& operator = (FVulkanView &&) = delete;`
- L536 _public prototype_ `FVulkanView& operator = (FVulkanView const&) = delete;`
- L538 _public function_ `FRHIDescriptorHandle GetBindlessHandle() const`
- L544 _protected prototype_ `void InitAsTextureView(const FVulkanContextArray& Contexts, VkImage InImage, const FVulkanTextureViewDesc& ViewDesc);`
- L547 _private member_ `FVulkanDevice& Device;`
- L548 _private member_ `FRHIDescriptorHandle BindlessHandle;`
- L549 _private member_ `const ERHIDescriptorType DescriptorType;`
- L550 _private member_ `TStorage Storage;`

#### struct `FVulkanView::FInvalidatedState`  
`struct FInvalidatedState`  
_L452-455_
- L454 _public member_ `bool bInitialized = false;`

#### struct `FVulkanView::FTypedBufferView`  
`struct FTypedBufferView`  
_L457-462_
- L459 _public member_ `VkBufferView View = VK_NULL_HANDLE;`
- L460 _public member_ `uint32 ViewId = 0;`
- L461 _public member_ `bool bVolatile = false;` — Whether source buffer is volatile

#### struct `FVulkanView::FStructuredBufferView`  
`struct FStructuredBufferView`  
_L464-470_
- L466 _public member_ `VkBuffer Buffer = VK_NULL_HANDLE;`
- L467 _public member_ `uint32 HandleId = 0;`
- L468 _public member_ `uint32 Offset = 0;`
- L469 _public member_ `uint32 Size = 0;`

#### struct `FVulkanView::FAccelerationStructureView`  
`struct FAccelerationStructureView`  
_L472-475_
- L474 _public member_ `VkAccelerationStructureKHR Handle = VK_NULL_HANDLE;`

#### struct `FVulkanView::FTextureView`  
`struct FTextureView`  
_L477-482_
- L479 _public member_ `VkImageView View = VK_NULL_HANDLE;`
- L480 _public member_ `VkImage Image = VK_NULL_HANDLE;`
- L481 _public member_ `uint32 ViewId = 0;`

#### enum `FVulkanView::EType`  
`enum EType`  
_L492-499_
- L494 _public enumerator_ `Null = TStorage::IndexOfType<FInvalidatedState >()`
- L495 _public enumerator_ `TypedBuffer = TStorage::IndexOfType<FTypedBufferView >()`
- L496 _public enumerator_ `Texture = TStorage::IndexOfType<FTextureView >()`
- L497 _public enumerator_ `StructuredBuffer = TStorage::IndexOfType<FStructuredBufferView >()`
- L498 _public enumerator_ `AccelerationStructure = TStorage::IndexOfType<FAccelerationStructureView>()`

#### class `FVulkanLinkedView`  
`class FVulkanLinkedView : public FVulkanView, public TIntrusiveLinkedList<FVulkanLinkedView>`  
_L553-567_
- inherits: `FVulkanView,TIntrusiveLinkedList<FVulkanLinkedView>`
- L556 _protected function_ `FVulkanLinkedView(FVulkanDevice& Device, ERHIDescriptorType DescriptorType) : FVulkanView(Device, DescriptorType)`
- L560 _protected function_ `~FVulkanLinkedView()`
- L566 _public prototype_ `virtual void UpdateView(const FVulkanContextArray& Contexts) = 0;`

#### class `FVulkanViewableResource`  
`class FVulkanViewableResource`  
_L569-590_
- L572 _public function_ `virtual ~FVulkanViewableResource()`
- L577 _public function_ `bool HasLinkedViews() const`
- L584 _public prototype_ `virtual void UpdateLinkedViews(const FVulkanContextArray& Contexts);` — @todo convert views owned by the texture into proper FVulkanView instances, then remove 'virtual' from this class
- L589 _private member_ `FVulkanLinkedView* LinkedViews = nullptr;`

#### struct `FVulkanReservedResourceData`  
`struct FVulkanReservedResourceData`  
_L592-604_
- L599 _public member_ `TArray<FSparseAllocation> Allocations;`
- L600 _public member_ `VkMemoryRequirements MemoryRequirements;`
- L601 _public member_ `uint64 LastBlockSize = 0;`
- L602 _public member_ `uint32 BlockCount = 0;`
- L603 _public member_ `uint32 NumCommittedTiles = 0;`

#### struct `FVulkanReservedResourceData::FSparseAllocation`  
`struct FSparseAllocation`  
_L594-598_
- L596 _public member_ `VulkanRHI::FVulkanAllocation Allocation;`
- L597 _public member_ `uint64 ResourceOffset = 0;`

#### enum `EImageOwnerType`  
`enum class EImageOwnerType : uint8`  
_L607-613_
- L609 _public enumerator_ `None`
- L610 _public enumerator_ `LocalOwner`
- L611 _public enumerator_ `ExternalOwner`
- L612 _public enumerator_ `Aliased`

#### class `FVulkanTexture`  
`class FVulkanTexture : public FRHITexture, public FVulkanEvictable, public FVulkanViewableResource`  
_L615-834_
- inherits: `FRHITexture,FVulkanEvictable,FVulkanViewableResource`
- L620 _public prototype_ `FVulkanTexture(FVulkanDevice& InDevice, const FRHITextureCreateDesc& InCreateDesc, const FRHITransientHeapAllocation* InTransientHeapAllocation);` — Constructor without command list: targets will not be cleared, cannot contain initial data, will be left in VK_IMAGE_LAYOUT_UNDEFINED. Layout changes and initial data upload should be handled by FinalizeCreateTextureInternal
- L623 _public prototype_ `FVulkanTexture(FVulkanDevice& InDevice, const FRHITextureCreateDesc& InCreateDesc, VkImage InImage, const FVulkanRHIExternalImageDeleteCallbackInfo& InExternalImageDeleteCallbackInfo);` — Construct from external resource.
- L627 _public prototype_ `FVulkanTexture(FVulkanDevice& InDevice, const FRHITextureCreateDesc& InCreateDesc, const AHardwareBuffer_Desc& HardwareBufferDesc, AHardwareBuffer* HardwareBuffer);` — Construct from Android Hardware buffer. HardwareBuffer_Desc could be extracted from HardwareBuffer, but adding it here makes the function signature unambigious
- L631 _public prototype_ `FVulkanTexture(FVulkanDevice& InDevice, const FRHITextureCreateDesc& InCreateDesc, FTextureRHIRef& SrcTextureRHI);` — Aliasing constructor.
- L633 _public prototype_ `virtual ~FVulkanTexture();`
- L635 _public prototype_ `void AliasTextureResources(FTextureRHIRef& SrcTextureRHI);`
- L637 _public prototype_ `void UploadInitialData(FRHICommandListBase& RHICmdList, VulkanRHI::FStagingBuffer* UploadBuffer);`
- L638 _public prototype_ `void HostUploadInitialData(FRHICommandListBase& RHICmdList, const uint8* BulkData, uint32 BulkDataSize);`
- L641 _public member_ `FVulkanView* DefaultView = nullptr;` — View with all mips/layers
- L644 _public member_ `FVulkanView* PartialView = nullptr;` — View with all mips/layers, but if it's a Depth/Stencil, only the Depth view
- L646 _public prototype_ `FVulkanView* FindOrAddInternalView(const FVulkanTextureViewDesc& ViewDesc);`
- L648 _public member_ `FTextureRHIRef AliasedTexture;`
- L651 _public function_ `template<typename T> void DumpMemory(T Callback)`
- L658 _public function_ `bool CanMove() const override` — FVulkanEvictable interface.
- L659 _public function_ `bool CanEvict() const override`
- L660 _public prototype_ `void Evict(FVulkanDevice& Device, const FVulkanContextArray& Contexts) override;` — evict to system memory
- L661 _public prototype_ `void Move(FVulkanDevice& Device, const FVulkanContextArray& Contexts, VulkanRHI::FVulkanAllocation& NewAllocation) override;` — move to a full new allocation
- L662 _public function_ `FVulkanTexture* GetEvictableTexture() override`
- L664 _public prototype_ `bool GetTextureResourceInfo(FRHIResourceInfo& OutResourceInfo) const;`
- L666 _public function_ `void* GetNativeResource() const override final`
- L667 _public function_ `void* GetTextureBaseRHI() override final`
- L669 _public function_ `virtual FRHIDescriptorHandle GetDefaultBindlessHandle() const override final`
- L689 _public prototype_ `static void GenerateImageCreateInfo( FImageCreateInfo& OutImageCreateInfo, FVulkanDevice& InDevice, const FRHITextureDesc& InDesc, VkFormat* OutStorageFormat = nullptr, VkFormat* OutViewFormat = nullptr, bool bForceLinearTexture = false);` — Separate method for creating VkImageCreateInfo
- L697 _public prototype_ `void DestroySurface();`
- L698 _public prototype_ `void InvalidateMappedMemory();`
- L699 _public prototype_ `void* GetMappedPointer();`
- L703 _public prototype_ `bool GetResourceInfo(FRHIResourceInfo& OutResourceInfo) const override;`
- L709 _public function_ `uint32 GetMemorySize() const` — Returns how much memory is used by the surface
- L717 _public prototype_ `void GetMipStride(uint32 MipIndex, uint32& Stride);` — Returns one of the texture's mip-maps stride.
- L722 _public prototype_ `void GetMipSize(uint32 MipIndex, uint64& MipBytes);` — Returns how much memory a single mip uses.
- L724 _public function_ `VkImageViewType GetViewType() const`
- L729 _public function_ `VkImageTiling GetTiling() const`
- L734 _public function_ `uint32 GetNumberOfArrayLevels() const`
- L753 _public prototype_ `void ErrorInvalidViewType() const;`
- L756 _public function_ `VkImageAspectFlags GetFullAspectMask() const` — Full includes Depth+Stencil
- L762 _public function_ `VkImageAspectFlags GetPartialAspectMask() const` — Only Depth or Stencil
- L767 _public function_ `bool IsDepthOrStencilAspect() const`
- L772 _public function_ `bool IsImageOwner() const`
- L777 _public function_ `bool SupportsSampling() const`
- L783 _public prototype_ `VkDeviceMemory GetAllocationHandle() const;`
- L784 _public prototype_ `uint64 GetAllocationOffset() const;`
- L786 _public prototype_ `static void InternalLockWrite(FVulkanContextCommon& Context, FVulkanTexture* Surface, const VkBufferImageCopy& Region, VulkanRHI::FStagingBuffer* StagingBuffer, bool bNeedsTransitions);`
- L788 _public function_ `const FVulkanCpuReadbackBuffer* GetCpuReadbackBuffer() const`
- L790 _public prototype_ `virtual void UpdateLinkedViews(const FVulkanContextArray& Contexts) override;`
- L792 _public member_ `FVulkanDevice* const Device;`
- L793 _public member_ `VkImage Image = VK_NULL_HANDLE;`
- L794 _public member_ `VkImageUsageFlags ImageUsageFlags = 0;`
- L797 _public member_ `VkFormat StorageFormat = VK_FORMAT_UNDEFINED;` — Removes SRGB if requested, used to upload data
- L800 _public member_ `VkFormat ViewFormat = VK_FORMAT_UNDEFINED;` — Format for SRVs, render targets
- L802 _public member_ `VkMemoryPropertyFlags MemProps = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;`
- L803 _public member_ `VkMemoryRequirements MemoryRequirements;`
- L805 _public member_ `FVulkanRHIExternalImageDeleteCallbackInfo ExternalImageDeleteCallbackInfo;`
- L808 _public member_ `TStaticArray<ERHIAccess, 2> AllPlanesTrackedAccess{ InPlace, ERHIAccess::Unknown };` — Only used when HasSeparateDepthStencilLayouts == false.
- L810 _public prototype_ `void SetInitialImageState(FRHICommandListBase& RHICmdList, VkImageLayout InitialLayout, bool bClear, const FClearValueBinding& ClearValueBinding, bool bIsTransientResource);`
- L812 _public prototype_ `TArray<VkSparseMemoryBind> CommitReservedResource(uint64 RequiredCommitSizeInBytes);`
- L815 _private prototype_ `void InternalMoveSurface(FVulkanDevice& InDevice, FVulkanCommandListContext& Context, VulkanRHI::FVulkanAllocation& DestAllocation);`
- L817 _private member_ `static const VkImageUsageFlags DefaultImageUsageFlags = 0;`
- L818 _private prototype_ `void InitViews(VkImageUsageFlags ViewUsageFlags, VkSamplerYcbcrConversion SamplerYcbcrConversion = VK_NULL_HANDLE);`
- L819 _private prototype_ `void UpdateViews(const FVulkanContextArray& Contexts, VkImageUsageFlags ViewUsageFlags, VkSamplerYcbcrConversion SamplerYcbcrConversion = VK_NULL_HANDLE);`
- L821 _private member_ `VkImageTiling Tiling = VK_IMAGE_TILING_MAX_ENUM;`
- L822 _private member_ `VulkanRHI::FVulkanAllocation Allocation;`
- L823 _private member_ `VkImageAspectFlags FullAspectMask = 0;`
- L824 _private member_ `VkImageAspectFlags PartialAspectMask = 0;`
- L825 _private member_ `FVulkanCpuReadbackBuffer* CpuReadbackBuffer = nullptr;`
- L828 _private member_ `TMap<uint32, FVulkanView*> InternalViews;` — Views with lifetime tied to this image
- L830 _private member_ `TUniquePtr<FVulkanReservedResourceData> ReservedResourceData;`
- L833 _protected member_ `EImageOwnerType ImageOwnerType;`

#### struct `FVulkanTexture::FImageCreateInfo`  
`struct FImageCreateInfo`  
_L675-686_
- L677 _public member_ `VkImageCreateInfo ImageCreateInfo;`
- L679 _public member_ `VkImageFormatListCreateInfoKHR ImageFormatListCreateInfo;` — only used when HasImageFormatListKHR is supported. Otherise VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT is used.
- L681 _public member_ `VkExternalMemoryImageCreateInfoKHR ExternalMemImageCreateInfo;` — used when TexCreate_External is given
- L683 _public member_ `TArray<VkFormat, TInlineAllocator<2>> FormatsUsed;` — Array of formats used for mutable formats
- L684 _public member_ `VkImageCompressionFixedRateFlagsEXT CompressionFixedRateFlags;`
- L685 _public member_ `VkImageCompressionControlEXT CompressionControl;`

#### class `FVulkanBuffer`  
`class FVulkanBuffer : public FRHIBuffer, public FVulkanViewableResource`  
_L837-955_
- inherits: `FRHIBuffer,FVulkanViewableResource`
- L840 _public prototype_ `FVulkanBuffer(FVulkanDevice& InDevice, const FRHIBufferCreateDesc& CreateDesc, const FRHITransientHeapAllocation* InTransientHeapAllocation = nullptr);`
- L841 _public prototype_ `virtual ~FVulkanBuffer();`
- L843 _public function_ `inline const VulkanRHI::FVulkanAllocation& GetCurrentAllocation() const`
- L848 _public function_ `inline VkBuffer GetHandle() const`
- L853 _public function_ `inline bool IsVolatile() const`
- L859 _public function_ `inline uint32 GetOffset() const` — Offset used for Binding a VkBuffer
- L865 _public function_ `inline uint64 GetCurrentSize() const` — Remaining size from the current offset
- L870 _public function_ `inline VkDeviceAddress GetDeviceAddress() const`
- L875 _public function_ `inline VkBufferUsageFlags GetBufferUsageFlags() const`
- L880 _public function_ `inline VkIndexType GetIndexType() const`
- L885 _public prototype_ `void* Lock(FRHICommandListBase& RHICmdList, EResourceLockMode LockMode, uint32 Size, uint32 Offset);`
- L886 _public prototype_ `void Unlock(FRHICommandListBase& RHICmdList);`
- L888 _public prototype_ `void TakeOwnership(FVulkanBuffer& Other);`
- L889 _public prototype_ `void ReleaseOwnership();`
- L892 _public function_ `template<typename T> void DumpMemory(T Callback)`
- L897 _public prototype_ `static VkBufferUsageFlags UEToVKBufferUsageFlags(FVulkanDevice& InDevice, EBufferUsageFlags InUEUsage, bool bZeroSize);`
- L906 _public function_ `void* GetCurrentHostPointer()`
- L911 _public function_ `void IncrementLockCounter()`
- L918 _public function_ `bool GetResourceInfo(FRHIResourceInfo& OutResourceInfo) const override`
- L930 _public prototype_ `TArray<VkSparseMemoryBind> CommitReservedResource(uint64 RequiredCommitSizeInBytes);`
- L935 _protected prototype_ `void AllocateMemory(FBufferAlloc& OutAlloc);` — Will return a new allocation that can be used for this buffer (proper memory type and size)
- L937 _protected member_ `FVulkanDevice& Device;`
- L939 _protected member_ `VkBufferUsageFlags BufferUsageFlags;`
- L946 _protected member_ `Unlocked, Locked, PersistentMapping, } LockStatus = ELockStatus::Unlocked;`
- L948 _protected member_ `FBufferAlloc CurrentBufferAlloc;`
- L949 _protected member_ `uint32 LockCounter = 0;`
- L951 _protected member_ `TUniquePtr<FVulkanReservedResourceData> ReservedResourceData;`

#### struct `FVulkanBuffer::FBufferAlloc`  
`struct FBufferAlloc`  
_L899-904_
- L901 _public member_ `VulkanRHI::FVulkanAllocation Alloc;`
- L902 _public member_ `void* HostPtr = nullptr;`
- L903 _public member_ `VkDeviceAddress DeviceAddress = 0;`

#### enum `FVulkanBuffer::ELockStatus`  
`enum class ELockStatus : uint8`  
_L941-946_
- L943 _public enumerator_ `Unlocked`
- L944 _public enumerator_ `Locked`
- L945 _public enumerator_ `PersistentMapping`

#### class `FVulkanUniformBuffer`  
`class FVulkanUniformBuffer : public FRHIUniformBuffer`  
_L957-1009_
- inherits: `FRHIUniformBuffer`
- L960 _public prototype_ `FVulkanUniformBuffer(FVulkanDevice& Device, const FRHIUniformBufferLayout* InLayout, const void* Contents, EUniformBufferUsage InUsage, EUniformBufferValidation Validation);`
- L961 _public prototype_ `virtual ~FVulkanUniformBuffer();`
- L963 _public function_ `const TArray<TRefCountPtr<FRHIResource>>& GetResourceTable() const`
- L965 _public prototype_ `void UpdateResourceTable(const FRHIUniformBufferLayout& InLayout, const void* Contents, int32 ResourceNum);`
- L966 _public prototype_ `void UpdateResourceTable(TArrayView<FRHIResource*> Resources);`
- L968 _public function_ `VkBuffer GetBufferHandle() const`
- L973 _public function_ `uint32 GetOffset() const`
- L978 _public function_ `const VulkanRHI::FVulkanAllocation& GetAllocation() const`
- L983 _public function_ `bool IsUniformView() const`
- L988 _public function_ `FRHIDescriptorHandle GetBindlessHandle() const override`
- L993 _public prototype_ `void UpdateBindlessHandle(const FVulkanContextArray& Contexts, bool bImmediate);`
- L994 _public prototype_ `VkDeviceAddress GetDeviceAddress() const;`
- L996 _public prototype_ `void SetupUniformBufferView();`
- L998 _public prototype_ `void AllocateMemory(const void* InitialData);`
- L1001 _public member_ `const EUniformBufferUsage Usage;`
- L1005 _protected member_ `FVulkanDevice& Device;`
- L1006 _protected member_ `VulkanRHI::FVulkanAllocation Allocation;`
- L1007 _protected member_ `FRHIDescriptorHandle BindlessHandle;`
- L1008 _protected member_ `FRHIShaderResourceView* UniformViewSRV = nullptr;`

#### class `FVulkanUnorderedAccessView`  
`class FVulkanUnorderedAccessView final : public FRHIUnorderedAccessView, public FVulkanLinkedView`  
_L1011-1025_
- inherits: `FRHIUnorderedAccessView,FVulkanLinkedView`
- L1014 _public prototype_ `FVulkanUnorderedAccessView(FRHICommandListBase& RHICmdList, FVulkanDevice& InDevice, FRHIViewableResource* InResource, FRHIViewDesc const& InViewDesc);`
- L1016 _public prototype_ `FVulkanViewableResource* GetBaseResource() const;`
- L1017 _public prototype_ `void UpdateView(const FVulkanContextArray& Contexts) override;`
- L1019 _public function_ `virtual FRHIDescriptorHandle GetBindlessHandle() const override`
- L1024 _public prototype_ `void Clear(TRHICommandList_RecursiveHazardous<FVulkanCommandListContext>& RHICmdList, const void* ClearValue, bool bFloat);`

#### class `FVulkanShaderResourceView`  
`class FVulkanShaderResourceView final : public FRHIShaderResourceView, public FVulkanLinkedView`  
_L1028-1040_
- inherits: `FRHIShaderResourceView,FVulkanLinkedView`
- L1031 _public prototype_ `FVulkanShaderResourceView(FRHICommandListBase& RHICmdList, FVulkanDevice& InDevice, FRHIViewableResource* InResource, FRHIViewDesc const& InViewDesc);`
- L1033 _public prototype_ `FVulkanViewableResource* GetBaseResource() const;`
- L1034 _public prototype_ `void UpdateView(const FVulkanContextArray& Contexts) override;`
- L1036 _public function_ `virtual FRHIDescriptorHandle GetBindlessHandle() const override`

#### class `FVulkanVertexInputStateInfo`  
`class FVulkanVertexInputStateInfo`  
_L1042-1080_
- L1045 _public prototype_ `FVulkanVertexInputStateInfo();`
- L1046 _public prototype_ `~FVulkanVertexInputStateInfo();`
- L1048 _public prototype_ `void Generate(FVulkanVertexDeclaration* VertexDeclaration, uint32 VertexHeaderInOutAttributeMask);`
- L1050 _public function_ `inline uint32 GetHash() const`
- L1056 _public function_ `inline const VkPipelineVertexInputStateCreateInfo& GetInfo() const`
- L1061 _public prototype_ `bool operator ==(const FVulkanVertexInputStateInfo& Other);`
- L1064 _protected member_ `VkPipelineVertexInputStateCreateInfo Info;`
- L1065 _protected member_ `uint32 Hash;`
- L1067 _protected member_ `uint32 BindingsNum;`
- L1068 _protected member_ `uint32 BindingsMask;`
- L1071 _protected member_ `TMap<uint32, uint32> BindingToStream;` — #todo-rco: Remove these TMaps
- L1072 _protected member_ `TMap<uint32, uint32> StreamToBinding;`
- L1073 _protected member_ `VkVertexInputBindingDescription Bindings[MaxVertexElementCount];`
- L1075 _protected member_ `uint32 AttributesNum;`
- L1076 _protected member_ `VkVertexInputAttributeDescription Attributes[MaxVertexElementCount];`

#### class `FPackedUniformBuffers`  
`class FPackedUniformBuffers`  
_L1083-1130_
- desc: This class holds the staging area for packed global uniform buffers for a given shader
- L1087 _public typedef_ `typedef TArray<uint8> FPackedBuffer;` — One buffer is a chunk of bytes
- L1089 _public function_ `void Init(const FVulkanShaderHeader& InCodeHeader, uint32& OutPackedUniformBufferStagingMask)`
- L1103 _public function_ `inline void SetPackedGlobalParameter(uint32 ByteOffset, uint32 NumBytes, const void* RESTRICT NewValue, uint32& InOutPackedUniformBufferStagingDirty)`
- L1123 _public function_ `inline const FPackedBuffer& GetBuffer() const`
- L1129 _protected member_ `FPackedBuffer PackedUniformBuffers;`

#### class `FVulkanStagingBuffer`  
`class FVulkanStagingBuffer : public FRHIStagingBuffer`  
_L1132-1154_
- inherits: `FRHIStagingBuffer`
- L1136 _public function_ `FVulkanStagingBuffer() : FRHIStagingBuffer()`
- L1142 _public prototype_ `virtual ~FVulkanStagingBuffer();`
- L1144 _public prototype_ `virtual void* Lock(uint32 Offset, uint32 NumBytes) final override;`
- L1145 _public prototype_ `virtual void Unlock() final override;`
- L1147 _public function_ `uint64 GetGPUSizeBytes() const override`
- L1150 _private member_ `VulkanRHI::FStagingBuffer* StagingBuffer = nullptr;`
- L1151 _private member_ `uint32 QueuedNumBytes = 0;`
- L1153 _private member_ `FVulkanDevice* Device;` — The staging buffer was allocated from this device.

#### class `FVulkanGPUFence`  
`class FVulkanGPUFence final : public FRHIGPUFence`  
_L1156-1173_
- inherits: `FRHIGPUFence`
- L1159 _public prototype_ `FVulkanGPUFence(FVulkanDevice& InDevice, FName InName);`
- L1160 _public prototype_ `virtual ~FVulkanGPUFence();`
- L1162 _public prototype_ `virtual void Clear() override;`
- L1163 _public prototype_ `virtual bool Poll() const override;`
- L1164 _public prototype_ `virtual void Wait(FRHICommandListImmediate& RHICmdList, FRHIGPUMask GPUMask) const override;`
- L1167 _protected member_ `FVulkanDevice& Device;`
- L1168 _protected member_ `VkEvent Event = VK_NULL_HANDLE;`
- L1169 _protected member_ `FGraphEventRef SubmittedSyncPoint;`
- L1170 _protected member_ `FVulkanSyncPointRef CompletedSyncPoint;`

#### struct `TVulkanResourceTraits`  
`template<class T> struct TVulkanResourceTraits`  
_L1176-1178_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIVertexDeclaration>`  
_L1180-1183_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIVertexShader>`  
_L1185-1188_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIMeshShader>`  
_L1190-1193_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIAmplificationShader>`  
_L1195-1198_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIGeometryShader>`  
_L1200-1203_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIPixelShader>`  
_L1205-1208_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIComputeShader>`  
_L1210-1213_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIRenderQuery>`  
_L1215-1218_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIUniformBuffer>`  
_L1220-1223_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIBuffer>`  
_L1225-1228_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIShaderResourceView>`  
_L1230-1233_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIUnorderedAccessView>`  
_L1235-1238_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHISamplerState>`  
_L1241-1244_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIRasterizerState>`  
_L1246-1249_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIDepthStencilState>`  
_L1251-1254_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIBlendState>`  
_L1256-1259_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIBoundShaderState>`  
_L1262-1265_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIStagingBuffer>`  
_L1268-1271_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIGPUFence>`  
_L1274-1277_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIRayTracingScene>`  
_L1301-1304_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIRayTracingGeometry>`  
_L1306-1309_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIShaderBindingTable>`  
_L1311-1314_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIRayTracingPipelineState>`  
_L1316-1319_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIRayTracingShader>`  
_L1321-1324_
- L1182 _public typedef_ `typedef FVulkanVertexDeclaration TConcreteType;`
- L1187 _public typedef_ `typedef FVulkanVertexShader TConcreteType;`
- L1192 _public typedef_ `typedef FVulkanMeshShader TConcreteType;`
- L1197 _public typedef_ `typedef FVulkanTaskShader TConcreteType;`
- L1202 _public typedef_ `typedef FVulkanGeometryShader TConcreteType;`
- L1207 _public typedef_ `typedef FVulkanPixelShader TConcreteType;`
- L1212 _public typedef_ `typedef FVulkanComputeShader TConcreteType;`
- L1217 _public typedef_ `typedef FVulkanRenderQuery TConcreteType;`
- L1222 _public typedef_ `typedef FVulkanUniformBuffer TConcreteType;`
- L1227 _public typedef_ `typedef FVulkanBuffer TConcreteType;`
- L1232 _public typedef_ `typedef FVulkanShaderResourceView TConcreteType;`
- L1237 _public typedef_ `typedef FVulkanUnorderedAccessView TConcreteType;`
- L1243 _public typedef_ `typedef FVulkanSamplerState TConcreteType;`
- L1248 _public typedef_ `typedef FVulkanRasterizerState TConcreteType;`
- L1253 _public typedef_ `typedef FVulkanDepthStencilState TConcreteType;`
- L1258 _public typedef_ `typedef FVulkanBlendState TConcreteType;`
- L1264 _public typedef_ `typedef FVulkanBoundShaderState TConcreteType;`
- L1270 _public typedef_ `typedef FVulkanStagingBuffer TConcreteType;`
- L1276 _public typedef_ `typedef FVulkanGPUFence TConcreteType;`
- L1303 _public typedef_ `typedef FVulkanRayTracingScene TConcreteType;`
- L1308 _public typedef_ `typedef FVulkanRayTracingGeometry TConcreteType;`
- L1313 _public typedef_ `typedef FVulkanRayTracingShaderTable TConcreteType;`
- L1318 _public typedef_ `typedef FVulkanRayTracingPipelineState TConcreteType;`
- L1323 _public typedef_ `typedef FVulkanRayTracingShader TConcreteType;`

#### Free symbols / members of external scopes

- L40 _typedef_ `using FVulkanSyncPointRef = TRefCountPtr<FVulkanSyncPoint>;`
- L42 _namespace_ `namespace VulkanRHI`
- L49 _enumerator_ `NUM_OCCLUSION_QUERIES_PER_POOL = 4096` (scope `__anonf3dd29f80103`)
- L51 _enumerator_ `NUM_TIMESTAMP_QUERIES_PER_POOL = 1024` (scope `__anonf3dd29f80103`)
- L55 _externvar_ `extern VkFormat GVulkanBufferFormat[PF_MAX];` — Mirror GPixelFormats with format information for buffers
- L58 _function_ `inline VkImageViewType UETextureDimensionToVkImageViewType(ETextureDimension Dimension)` — Converts the internal texture dimension to Vulkan view type
- L286 _enumerator_ `enum { StaticFrequency = ShaderType }; virtual void AddRef() const override final { FRHIResource::AddRef(); } virtual FReturnedRefCountValue Release() const override final` (scope `TVulkanBaseShader::__anonf3dd29f80203`)
- L303 _typedef_ `typedef TVulkanBaseShader<FRHIVertexShader, SF_Vertex> FVulkanVertexShader;`
- L304 _typedef_ `typedef TVulkanBaseShader<FRHIPixelShader, SF_Pixel> FVulkanPixelShader;`
- L305 _typedef_ `typedef TVulkanBaseShader<FRHIComputeShader, SF_Compute> FVulkanComputeShader;`
- L306 _typedef_ `typedef TVulkanBaseShader<FRHIGeometryShader, SF_Geometry> FVulkanGeometryShader;`
- L307 _typedef_ `typedef TVulkanBaseShader<FRHIMeshShader, SF_Mesh> FVulkanMeshShader;`
- L308 _typedef_ `typedef TVulkanBaseShader<FRHIAmplificationShader, SF_Amplification> FVulkanTaskShader;`
- L1280 _function_ `template<typename TRHIType> static FORCEINLINE typename TVulkanResourceTraits<TRHIType>::TConcreteType* ResourceCast(TRHIType* Resource)`
- L1286 _function_ `template<typename TRHIType> static FORCEINLINE const typename TVulkanResourceTraits<TRHIType>::TConcreteType* ResourceCast(const TRHIType* Resource)`
- L1291 _function_ `static FORCEINLINE FVulkanTexture* ResourceCast(FRHITexture* Texture)`

### `Source/Runtime/VulkanRHI/Private/VulkanShaderObjectManager.h` (Private)


#### class `FVulkanShaderObjectManager`  
`class FVulkanShaderObjectManager`  
_L14-31_
- L17 _public prototype_ `FVulkanShaderObjectManager(FVulkanDevice& InDevice);`
- L18 _public prototype_ `~FVulkanShaderObjectManager();`
- L20 _public prototype_ `void CreateShaderObject(FVulkanShader& VulkanShader);`
- L21 _public prototype_ `bool CreateLinkedShaderObjects(FVulkanGraphicsPipelineState* PSO, FVulkanShader* Shaders[ShaderStage::NumGraphicsStages], FGraphicsPipelineStateInitializer::EPSOPrecacheCompileType PSOCompileType);`
- L24 _private prototype_ `VkShaderStageFlags GetPossibleNextStages(VkShaderStageFlagBits Stage);`
- L25 _private prototype_ `void InternalCreateShaderObject(FVulkanShader& VulkanShader);`
- L27 _private member_ `FVulkanDevice& Device;`
- L29 _private member_ `FCriticalSection AsyncTaskLock;`
- L30 _private member_ `TSet<TRefCountPtr<FVulkanShader>> AsyncTasks;`

### `Source/Runtime/VulkanRHI/Private/VulkanState.h` (Private)


#### class `FVulkanSamplerState`  
`class FVulkanSamplerState : public FRHISamplerState`  
_L16-33_
- inherits: `FRHISamplerState`
- L19 _public prototype_ `FVulkanSamplerState(const VkSamplerCreateInfo& InInfo, FVulkanDevice& InDevice, const bool bInIsImmutable = false);`
- L21 _public function_ `virtual bool IsImmutable() const final override`
- L23 _public member_ `VkSampler Sampler;`
- L24 _public member_ `uint32 SamplerId;`
- L25 _public member_ `FRHIDescriptorHandle BindlessHandle;`
- L27 _public prototype_ `static void SetupSamplerCreateInfo(const FSamplerStateInitializerRHI& Initializer, FVulkanDevice& InDevice, VkSamplerCreateInfo& OutSamplerInfo);`
- L29 _public function_ `virtual FRHIDescriptorHandle GetBindlessHandle() const override final`
- L32 _private member_ `bool bIsImmutable;`

#### class `FVulkanRasterizerState`  
`class FVulkanRasterizerState : public FRHIRasterizerState`  
_L35-55_
- inherits: `FRHIRasterizerState`
- L38 _public prototype_ `FVulkanRasterizerState(const FRasterizerStateInitializerRHI& InInitializer);`
- L40 _public function_ `static void ResetCreateInfo(VkPipelineRasterizationStateCreateInfo& OutInfo)`
- L47 _public function_ `virtual bool GetInitializer(FRasterizerStateInitializerRHI& Out) override final`
- L53 _public member_ `VkPipelineRasterizationStateCreateInfo RasterizerState;`
- L54 _public member_ `FRasterizerStateInitializerRHI Initializer;`

#### class `FVulkanDepthStencilState`  
`class FVulkanDepthStencilState : public FRHIDepthStencilState`  
_L57-74_
- inherits: `FRHIDepthStencilState`
- L60 _public function_ `FVulkanDepthStencilState(const FDepthStencilStateInitializerRHI& InInitializer)`
- L65 _public function_ `virtual bool GetInitializer(FDepthStencilStateInitializerRHI& Out) override final`
- L71 _public prototype_ `void SetupCreateInfo(const FGraphicsPipelineStateInitializer& GfxPSOInit, VkPipelineDepthStencilStateCreateInfo& OutDepthStencilState);`
- L73 _public member_ `FDepthStencilStateInitializerRHI Initializer;`

#### class `FVulkanBlendState`  
`class FVulkanBlendState : public FRHIBlendState`  
_L76-91_
- inherits: `FRHIBlendState`
- L79 _public prototype_ `FVulkanBlendState(const FBlendStateInitializerRHI& InInitializer);`
- L81 _public function_ `virtual bool GetInitializer(FBlendStateInitializerRHI& Out) override final`
- L88 _public member_ `VkPipelineColorBlendAttachmentState BlendStates[MaxSimultaneousRenderTargets];` — array the pipeline state can point right to
- L90 _public member_ `FBlendStateInitializerRHI Initializer;`

### `Source/Runtime/VulkanRHI/Private/VulkanSubmission.h` (Private)


#### enum `EVulkanSyncPointType`  
`enum class EVulkanSyncPointType`  
_L24-39_
- L33 _public enumerator_ `GPUAndCPU` — Sync points of this type include an FGraphEvent. The IsComplete() and Wait() functions can be used to poll for completion from the CPU, or block the CPU, respectively.
- L38 _public enumerator_ `Context` — Same as GPUAndCPU but not time critical and can be pushed back up until the end of the frame. Generally meant to be used for work that can happen at any point after the command buffers are done executing on the GPU.

#### class `FVulkanSyncPoint`  
`class FVulkanSyncPoint final : public FRefCountedObject`  
_L53-135_
- inherits: `FRefCountedObject`
- desc: A sync point is a logical point on a GPU queue's timeline that can be awaited by other queues, or the CPU. These are used throughout the RHI as a way to abstract the underlying Vulkan semaphores and fences. The submission thread manages the underlying semaphores, fences and signaled values, and reports completion to the relevant sync points via an FGraphEvent. Sync points are one-shot, meaning they represent a single timeline point, and are released after use, via ref-counting. Use FVulkanSyncPoint::Create() to make a new sync point and hold a reference to it via a FVulkanSyncPointRef object.
- L58 _private member_ `static TLockFreePointerListUnordered<void, PLATFORM_CACHE_LINE_SIZE> MemoryPool;`
- L61 _private prototype_ `FVulkanSyncPoint(FVulkanSyncPoint const&) = delete;` — No copying or moving
- L62 _private prototype_ `FVulkanSyncPoint(FVulkanSyncPoint&&) = delete;`
- L64 _private function_ `FVulkanSyncPoint(EVulkanSyncPointType InType, const TCHAR* InDebugName) : Type(InType) #if RHI_USE_SYNC_POINT_DEBUG_NAME , DebugName(InDebugName) #endif`
- L77 _public function_ `static FVulkanSyncPointRef Create(EVulkanSyncPointType Type, const TCHAR* InDebugName)`
- L83 _public function_ `bool IsComplete() const`
- L89 _public prototype_ `void Wait() const;`
- L91 _public function_ `FGraphEvent* GetGraphEvent() const`
- L97 _public function_ `EVulkanSyncPointType GetType() const`
- L102 _public function_ `void* operator new(size_t Size)`
- L114 _public function_ `void operator delete(void* Pointer)`
- L119 _public function_ `inline const TCHAR* GetDebugName() const`
- L129 _private member_ `FGraphEventRef GraphEvent;`
- L130 _private member_ `EVulkanSyncPointType Type;`
- L133 _private member_ `const TCHAR* DebugName = nullptr;`

#### struct `FVulkanCommitReservedResourceDesc`  
`struct FVulkanCommitReservedResourceDesc`  
_L139-143_
- L141 _public member_ `TRefCountPtr<FRHIResource> Resource = nullptr;`
- L142 _public member_ `uint64 CommitSizeInBytes = 0;`

#### class `FVulkanPayload`  
`class FVulkanPayload`  
_L147-206_
- L155 _public function_ `FVulkanPayload(FVulkanQueue& InQueue) : Queue(InQueue) , EventStream(InQueue.GetProfilerQueue())`
- L160 _public prototype_ `~FVulkanPayload();`
- L165 _protected prototype_ `void Merge(FVulkanPayload& Other);` — Must only be used to merge Secondary or Parallel command buffers
- L167 _protected prototype_ `void PreExecute();`
- L169 _protected member_ `FVulkanQueue& Queue;`
- L170 _protected member_ `TArray<VkPipelineStageFlags> WaitFlags;` — flags that match 1:1 with WaitSemaphores
- L171 _protected member_ `TArray<TRefCountPtr<FVulkanSemaphore>> WaitSemaphores;` — wait before command buffers
- L172 _protected member_ `TArray<FVulkanCommandBuffer*> CommandBuffers;`
- L173 _protected member_ `TArray<TRefCountPtr<FVulkanSemaphore>> SignalSemaphores;` — signaled after command buffers
- L176 _protected member_ `TArray<FGraphEventRef> SubmissionEvents;` — Signaled when the payload has been submitted to the GPU queue
- L179 _protected member_ `uint64 TimelineSemaphoreValue = 0;` — For internal completion tracking of the payload
- L180 _protected member_ `FVulkanFence* Fence = nullptr;`
- L183 _protected member_ `TArray<FVulkanSyncPointRef> SyncPoints;` — Used to sync other CPU work to payload completion
- L186 _protected member_ `TStaticArray<TArray<FVulkanQueryPool*>, (int32)EVulkanQueryPoolType::Count> QueryPools;` — Queries used in the command lists of this payload
- L189 _protected member_ `TArray<FVulkanDescriptorPoolSetContainer*> DescriptorPoolSetContainers;` — Used DescriptorPoolSetContainers that can be cleaned up on completion
- L192 _protected member_ `TFunction<void(VkQueue)> PreExecuteCallback;` — Used by RHIRunOnQueue
- L195 _protected member_ `FRHIBreadcrumbRange BreadcrumbRange{};`
- L196 _protected member_ `TSharedPtr<FRHIBreadcrumbAllocatorArray> BreadcrumbAllocators{};`
- L199 _protected member_ `TOptional<FVulkanTiming*> Timing;`
- L200 _protected member_ `TOptional<uint64> ExternalGPUTime;`
- L201 _protected member_ `TOptional<UE::RHI::GPUProfiler::FEvent::FFrameBoundary> EndFrameEvent;`
- L202 _protected member_ `UE::RHI::GPUProfiler::FEventStream EventStream;`
- L205 _protected member_ `TArray<FVulkanCommitReservedResourceDesc> ReservedResourcesToCommit;` — UpdateReservedResources

#### struct `FVulkanPlatformCommandList`  
`struct FVulkanPlatformCommandList : public IRHIPlatformCommandList, public TArray<FVulkanPayload*>`  
_L208-210_
- inherits: `IRHIPlatformCommandList,TArray<FVulkanPayload*>`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<IRHIPlatformCommandList>`  
_L213-216_
- L215 _public typedef_ `typedef FVulkanPlatformCommandList TConcreteType;`

#### Free symbols / members of external scopes

- L42 _typedef_ `using FVulkanSyncPointRef = TRefCountPtr<FVulkanSyncPoint>;`

### `Source/Runtime/VulkanRHI/Private/VulkanSwapChain.h` (Private)


#### struct `FVulkanSwapChainRecreateInfo`  
`struct FVulkanSwapChainRecreateInfo`  
_L22-26_
- L24 _public member_ `VkSwapchainKHR SwapChain;`
- L25 _public member_ `VkSurfaceKHR Surface;`

#### class `FVulkanSwapChain`  
`class FVulkanSwapChain`  
_L29-102_
- L31 _private prototype_ `FVulkanSwapChain(VkInstance InInstance, FVulkanDevice& InDevice, VkSurfaceKHR InSurface, VkSwapchainKHR InSwapChain, VkSurfaceTransformFlagBitsKHR PreTransform, uint32 InWidth, uint32 InHeight, bool InIsFullscreen, uint32 NumSwapChainImages, int8 InLockToVsync, FVulkanPlatformWindowContext& WindowContext);`
- L36 _public prototype_ `static FVulkanSwapChain* Create( VkInstance InInstance, FVulkanDevice& Device, EPixelFormat& InOutPixelFormat, uint32 Width, uint32 Height, bool bIsFullScreen, uint32* InOutDesiredNumBackBuffers, TArray<VkImage>& OutImages, int8 LockToVsync, FVulkanPlatformWindowContext& WindowContext, FVulkanSwapChainRecreateInfo* RecreateInfo);`
- L42 _public prototype_ `void Destroy(FVulkanSwapChainRecreateInfo* RecreateInfo);`
- L52 _public prototype_ `EStatus Present(FVulkanQueue* PresentQueue, FVulkanSemaphore* BackBufferRenderingDoneSemaphore);`
- L54 _public function_ `inline int8 DoesLockToVsync()`
- L56 _public function_ `inline VkSurfaceTransformFlagBitsKHR GetCachedSurfaceTransform() const`
- L59 _public function_ `void ResetCurrentImageIndex()` — Reset the current image index when a present is skipped (e.g. window destroyed).
- L62 _protected member_ `const VkInstance Instance;`
- L63 _protected member_ `FVulkanDevice& Device;`
- L65 _protected member_ `VkSurfaceKHR Surface = VK_NULL_HANDLE;`
- L66 _protected member_ `VkSwapchainKHR SwapChain = VK_NULL_HANDLE;`
- L68 _protected member_ `const VkSurfaceTransformFlagBitsKHR PreTransform;`
- L70 _protected member_ `uint32 InternalWidth = 0;`
- L71 _protected member_ `uint32 InternalHeight = 0;`
- L72 _protected member_ `bool bInternalFullScreen = false;`
- L74 _protected member_ `void* WindowHandle = nullptr;`
- L77 _protected member_ `uint32 WindowId = 0;` — Platform window id captured at creation (0 if untracked). Used to release per-window RHI resources by a stable id at destroy time instead of by the WindowHandle pointer.
- L79 _protected member_ `int32 CurrentImageIndex = -1;`
- L80 _protected member_ `int32 SyncIndex = 0;`
- L81 _protected member_ `uint32 NumPresentCalls = 0;`
- L82 _protected member_ `uint32 NumAcquireCalls = 0;`
- L84 _protected member_ `uint32 RTPacingSampleCount = 0;`
- L85 _protected member_ `double RTPacingPreviousFrameCPUTime = 0;`
- L86 _protected member_ `double RTPacingSampledDeltaTimeMS = 0;`
- L88 _protected member_ `double NextPresentTargetTime = 0;`
- L90 _protected member_ `TArray<TRefCountPtr<FVulkanSemaphore>> ImageAcquiredSemaphore;`
- L91 _protected member_ `TArray<FVulkanFence*> ImageAcquiredFences;`
- L93 _protected member_ `int8 LockToVsync = 0;`
- L95 _protected member_ `uint32 PresentID = 0;`
- L97 _protected prototype_ `int32 AcquireImageIndex(TRefCountPtr<FVulkanSemaphore>* OutSemaphore);`

#### enum `FVulkanSwapChain::EStatus`  
`enum class EStatus`  
_L45-51_
- desc: Has to be negative as we use this also on other callbacks as the acquired image index
- L47 _public enumerator_ `Healthy = 0`
- L48 _public enumerator_ `OutOfDate = -1`
- L49 _public enumerator_ `SurfaceLost = -2`
- L50 _public enumerator_ `NotReady = -3`

### `Source/Runtime/VulkanRHI/Private/VulkanSynchronization.h` (Private)


#### class `FVulkanFence`  
`class FVulkanFence`  
_L16-55_
- desc: Internal Vulkan Fence class that wrap VkFence management (not to be confused with FVulkanGPUFence class that maps to RHI's FRHIFence)
- L19 _public prototype_ `FVulkanFence(FVulkanDevice& InDevice, FVulkanFenceManager& InOwner, bool bCreateSignaled);`
- L21 _public function_ `inline VkFence GetHandle() const`
- L26 _public function_ `inline bool IsSignaled() const`
- L31 _public function_ `FVulkanFenceManager& GetOwner()`
- L37 _protected member_ `VkFence Handle;`
- L48 _protected member_ `EState State;`
- L50 _protected member_ `FVulkanFenceManager& Owner;`
- L53 _protected prototype_ `~FVulkanFence();` — Only owner can delete!

#### enum `FVulkanFence::EState`  
`enum class EState`  
_L39-46_
- L42 _public enumerator_ `NotReady` — Initial state
- L45 _public enumerator_ `Signaled` — After GPU processed it

#### class `FVulkanFenceManager`  
`class FVulkanFenceManager`  
_L57-102_
- L60 _public function_ `FVulkanFenceManager(FVulkanDevice& InDevice) : Device(InDevice)`
- L64 _public prototype_ `~FVulkanFenceManager();`
- L66 _public prototype_ `void Deinit();`
- L68 _public prototype_ `FVulkanFence* AllocateFence(bool bCreateSignaled = false);`
- L70 _public function_ `inline bool IsFenceSignaled(FVulkanFence* Fence)`
- L81 _public prototype_ `bool WaitForAnyFence(TArrayView<FVulkanFence*> Fences, uint64 TimeInNanoseconds);` — Returns false if it timed out
- L82 _public prototype_ `bool WaitForFence(FVulkanFence* Fence, uint64 TimeInNanoseconds);`
- L84 _public prototype_ `void ResetFence(FVulkanFence* Fence);`
- L87 _public prototype_ `void ReleaseFence(FVulkanFence*& Fence);` — Sets it to nullptr
- L90 _public prototype_ `void WaitAndReleaseFence(FVulkanFence*& Fence, uint64 TimeInNanoseconds);` — Sets it to nullptr
- L93 _protected member_ `FVulkanDevice& Device;`
- L94 _protected member_ `FCriticalSection FenceLock;`
- L95 _protected member_ `TArray<FVulkanFence*> FreeFences;`
- L96 _protected member_ `TArray<FVulkanFence*> UsedFences;`
- L99 _protected prototype_ `bool CheckFenceState(FVulkanFence* Fence);` — Returns true if signaled
- L101 _protected prototype_ `void DestroyFence(FVulkanFence* Fence);`

#### enum `EVulkanSemaphoreFlags`  
`enum class EVulkanSemaphoreFlags : uint8`  
_L106-124_
- L108 _public enumerator_ `None = 0`
- L111 _public enumerator_ `ExternallyOwned = 1 << 1` — Will not delete handle on destruction
- L114 _public enumerator_ `ExternallySignaled = 1 << 2` — Inform submission pipeline that the signal will not come from a payload (acquired image semaphore for example)
- L117 _public enumerator_ `Timeline = 1 << 3` — Create a timeline semaphore (must be supported)
- L120 _public enumerator_ `ImmediateDeletion = 1 << 4` — Will not be queued for deferred deletion
- L123 _public enumerator_ `ExternallyWaited = 1 << 5` — Inform submission pipeline that the wait will not come from a payload (rendering done semaphore is consumed by vkQueuePresentKHR)

#### class `FVulkanSemaphore`  
`class FVulkanSemaphore : public FRefCountedObject`  
_L129-168_
- inherits: `FRefCountedObject`
- desc: Internal Vulkan Semaphore class that wrap VkSemaphore management (binary or timeline)
- L132 _public prototype_ `FVulkanSemaphore(FVulkanDevice& InDevice, EVulkanSemaphoreFlags InFlags=EVulkanSemaphoreFlags::None, uint64 InInitialTimelineValue=0);`
- L133 _public prototype_ `FVulkanSemaphore(FVulkanDevice& InDevice, const VkSemaphore& InExternalSemaphore);`
- L134 _public prototype_ `virtual ~FVulkanSemaphore();`
- L136 _public function_ `VkSemaphore GetHandle() const`
- L141 _public function_ `bool IsExternallyOwned() const`
- L146 _public function_ `bool IsExternallySignaled() const`
- L151 _public function_ `bool IsExternallyWaited() const`
- L156 _public function_ `bool IsTimeline() const`
- L161 _public prototype_ `void GetTimelineSemaphoreValue(uint64& OutValue);`
- L162 _public prototype_ `bool WaitForTimelineSemaphoreValue(uint64 Value, uint64 Timeout);`
- L165 _private member_ `FVulkanDevice& Device;`
- L166 _private member_ `VkSemaphore SemaphoreHandle;`
- L167 _private member_ `const EVulkanSemaphoreFlags Flags;`

#### Free symbols / members of external scopes

- L125 _prototype_ `ENUM_CLASS_FLAGS(EVulkanSemaphoreFlags);`

### `Source/Runtime/VulkanRHI/Private/VulkanTransientResourceAllocator.h` (Private)


#### class `FVulkanTransientHeap`  
`class FVulkanTransientHeap final : public FRHITransientHeap , public FRefCountedObject`  
_L9-26_
- inherits: `FRHITransientHeap,FRefCountedObject`
- L14 _public prototype_ `FVulkanTransientHeap(const FInitializer& Initializer, FVulkanDevice& InDevice);`
- L15 _public prototype_ `~FVulkanTransientHeap();`
- L17 _public prototype_ `VkDeviceMemory GetMemoryHandle();`
- L18 _public prototype_ `static VulkanRHI::FVulkanAllocation GetVulkanAllocation(const FRHITransientHeapAllocation& TransientInitializer);`
- L21 _private member_ `FVulkanDevice& Device;`
- L22 _private member_ `VkBuffer VulkanBuffer = VK_NULL_HANDLE;`
- L23 _private member_ `uint32 HandleID = 0;`
- L24 _private member_ `VkMemoryRequirements MemoryRequirements;`
- L25 _private member_ `VulkanRHI::FVulkanAllocation InternalAllocation;`

#### class `FVulkanTransientHeapCache`  
`class FVulkanTransientHeapCache final : public FRHITransientHeapCache`  
_L29-41_
- inherits: `FRHITransientHeapCache`
- L33 _public prototype_ `static FVulkanTransientHeapCache* Create(FVulkanDevice& InDevice);`
- L35 _public prototype_ `FRHITransientHeap* CreateHeap(const FRHITransientHeap::FInitializer& Initializer) override;`
- L37 _public member_ `FVulkanDevice& Device;`
- L40 _private prototype_ `FVulkanTransientHeapCache(const FInitializer& Initializer, FVulkanDevice& InDevice);`

#### class `FVulkanTransientResourceAllocator`  
`class FVulkanTransientResourceAllocator final : public FRHITransientResourceHeapAllocator`  
_L44-64_
- inherits: `FRHITransientResourceHeapAllocator`
- L48 _public prototype_ `FVulkanTransientResourceAllocator(FVulkanTransientHeapCache& InHeapCache);`
- L51 _public function_ `bool SupportsResourceType(ERHITransientResourceType InType) const override` — IRHITransientResourceAllocator Overrides
- L60 _public prototype_ `FRHITransientTexture* CreateTexture(const FRHITextureCreateInfo& InCreateInfo, const TCHAR* InDebugName, const FRHITransientAllocationFences& Fences) override;`
- L61 _public prototype_ `FRHITransientBuffer* CreateBuffer(const FRHIBufferCreateInfo& InCreateInfo, const TCHAR* InDebugName, const FRHITransientAllocationFences& Fences) override;`
- L63 _public member_ `FVulkanDevice& Device;`

### `Source/Runtime/VulkanRHI/Private/VulkanViewport.h` (Private)


#### class `FVulkanBackBuffer`  
`class FVulkanBackBuffer : public FVulkanTexture`  
_L23-40_
- inherits: `FVulkanTexture`
- L26 _public prototype_ `FVulkanBackBuffer(FVulkanDevice& Device, FVulkanViewport* InViewport, EPixelFormat Format, uint32 SizeX, uint32 SizeY, ETextureCreateFlags UEFlags);`
- L27 _public prototype_ `virtual ~FVulkanBackBuffer();`
- L29 _public prototype_ `void OnGetBackBufferImage(FRHICommandListImmediate& RHICmdList);`
- L30 _public prototype_ `void OnAdvanceBackBufferFrame(FRHICommandListImmediate& RHICmdList);`
- L32 _public prototype_ `void ReleaseViewport();`
- L33 _public prototype_ `void ReleaseAcquiredImage();`
- L36 _private prototype_ `void AcquireBackBufferImage(FVulkanCommandListContext& Context);`
- L39 _private member_ `FVulkanViewport* Viewport;`

#### class `FVulkanViewport`  
`class FVulkanViewport : public FRHIViewport`  
_L43-172_
- inherits: `FRHIViewport`
- L46 _public prototype_ `FVulkanViewport(FVulkanDevice& InDevice, void* InWindowHandle, uint32 InSizeX,uint32 InSizeY,bool bInIsFullscreen, EPixelFormat InPreferredPixelFormat);`
- L47 _public prototype_ `~FVulkanViewport();`
- L49 _public prototype_ `FTextureRHIRef GetBackBuffer(FRHICommandListImmediate& RHICmdList);`
- L50 _public prototype_ `void AdvanceBackBufferFrame(FRHICommandListImmediate& RHICmdList, bool bPresent);`
- L52 _public prototype_ `virtual void WaitForFrameEventCompletion() override;`
- L54 _public prototype_ `virtual void IssueFrameEvent() override;`
- L56 _public function_ `inline FIntPoint GetSizeXY() const`
- L61 _public function_ `virtual void SetCustomPresent(FRHICustomPresent* InCustomPresent) override final`
- L66 _public function_ `virtual FRHICustomPresent* GetCustomPresent() const override final`
- L71 _public prototype_ `void CheckSwapChain();`
- L73 _public prototype_ `bool Present(FVulkanCommandListContext& Context, const FRHIPresentArgs& InPresentArgs);`
- L75 _public function_ `inline uint32 GetPresentCount() const`
- L80 _public function_ `inline bool IsFullscreen() const`
- L85 _public function_ `inline uint32 GetBackBufferImageCount()`
- L90 _public function_ `inline VkImage GetBackBufferImage(uint32 Index)`
- L102 _public function_ `inline FVulkanSwapChain* GetSwapChain()`
- L107 _public function_ `inline void* GetWindowHandle()`
- L109 _public prototype_ `void DestroySwapchain(struct FVulkanSwapChainRecreateInfo* RecreateInfo);`
- L110 _public prototype_ `void RecreateSwapchain(FVulkanCommandListContext& Context, FVulkanPlatformWindowContext& WindowContext);`
- L113 _public member_ `constexpr static uint32 NumRequestedSwapchainImages = 3;` — This is the number of images we're aiming for, driver might return more
- L116 _protected member_ `FVulkanDevice& Device;`
- L125 _protected member_ `TArray<FBackbufferImageData, TInlineAllocator<NumRequestedSwapchainImages*2>> BackBufferData;`
- L126 _protected member_ `TRefCountPtr<FVulkanBackBuffer> RHIBackBuffer;`
- L129 _protected member_ `TRefCountPtr<FVulkanTexture> RenderingBackBuffer;` — 'Dummy' back buffer
- L132 _protected member_ `FCriticalSection RecreatingSwapchain;` — narrow-scoped section that locks access to back buffer during its recreation
- L134 _protected member_ `uint32 SizeX;`
- L135 _protected member_ `uint32 SizeY;`
- L136 _protected member_ `bool bIsFullscreen;`
- L137 _protected member_ `EPixelFormat PixelFormat;`
- L138 _protected member_ `int32 AcquiredImageIndex;`
- L139 _protected member_ `FVulkanSwapChain* SwapChain;`
- L140 _protected member_ `void* WindowHandle;`
- L141 _protected member_ `uint32 PresentCount;`
- L143 _protected member_ `int8 LockToVsync;`
- L145 _protected member_ `FCustomPresentRHIRef CustomPresent;`
- L147 _protected member_ `FVulkanSyncPointRef LastFrameSyncPoint;`
- L149 _protected member_ `EDeviceScreenOrientation CachedOrientation = EDeviceScreenOrientation::Unknown;`
- L150 _protected prototype_ `void OnSystemResolutionChanged(uint32 ResX, uint32 ResY);`
- L152 _protected prototype_ `void CreateSwapchain(FVulkanCommandListContext& Context, struct FVulkanSwapChainRecreateInfo* RecreateInfo, FVulkanPlatformWindowContext& WindowContext);`
- L153 _protected prototype_ `bool TryAcquireImageIndex(FVulkanCommandListContext& Context);`
- L154 _protected prototype_ `void InitImages(TConstArrayView<VkImage> Images);`
- L156 _protected prototype_ `void RecreateSwapchainFromRT(FRHICommandListImmediate& RHICmdList, EPixelFormat PreferredPixelFormat, FVulkanPlatformWindowContext& WindowContext);`
- L157 _protected function_ `void RecreateSwapchainFromRT(FRHICommandListImmediate& RHICmdList, FVulkanPlatformWindowContext& WindowContext)`
- L161 _protected prototype_ `void Resize(FRHICommandListImmediate& RHICmdList, uint32 InSizeX, uint32 InSizeY, bool bIsFullscreen, EPixelFormat PreferredPixelFormat, FVulkanPlatformWindowContext& WindowContext);`
- L163 _protected prototype_ `bool DoCheckedSwapChainJob(FVulkanCommandListContext& Context);`
- L164 _protected prototype_ `bool SupportsStandardSwapchain();`
- L165 _protected prototype_ `bool RequiresRenderingBackBuffer();`
- L166 _protected prototype_ `EPixelFormat GetPixelFormatForNonDefaultSwapchain();`

#### struct `FVulkanViewport::FBackbufferImageData`  
`struct FBackbufferImageData`  
_L118-124_
- L120 _public member_ `TRefCountPtr<FVulkanTexture> Texture;`
- L121 _public member_ `TRefCountPtr<FVulkanSemaphore> RenderingDoneSemaphores;`
- L122 _public member_ `TUniquePtr<FVulkanView> TextureView;`
- L123 _public member_ `bool bFirstUse = true;`

#### struct `TVulkanResourceTraits`  
`template<> struct TVulkanResourceTraits<FRHIViewport>`  
_L175-178_
- L177 _public typedef_ `typedef FVulkanViewport TConcreteType;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace VulkanRHI`

### `Source/Runtime/VulkanRHI/Private/Windows/VulkanWindowsPlatform.h` (Private)


#### class `FVulkanWindowsPlatform`  
`class FVulkanWindowsPlatform : public FVulkanGenericPlatform`  
_L44-62_
- inherits: `FVulkanGenericPlatform`
- L47 _public prototype_ `static bool LoadVulkanLibrary();`
- L48 _public prototype_ `static bool LoadVulkanInstanceFunctions(VkInstance inInstance);`
- L49 _public prototype_ `static void FreeVulkanLibrary();`
- L51 _public prototype_ `static void GetInstanceExtensions(FVulkanInstanceExtensionArray& OutExtensions);`
- L52 _public function_ `static void GetInstanceLayers(TArray<const ANSICHAR*>& OutLayers)`
- L53 _public prototype_ `static void GetDeviceExtensions(FVulkanDevice* Device, FVulkanDeviceExtensionArray& OutExtensions);`
- L54 _public function_ `static void GetDeviceLayers(TArray<const ANSICHAR*>& OutLayers)`
- L56 _public prototype_ `static void CreateSurface(FVulkanPlatformWindowContext& WindowContext, VkInstance Instance, VkSurfaceKHR* OutSurface);`
- L58 _public function_ `static VkTimeDomainKHR GetTimeDomain()`
- L61 _private member_ `static bool bAttemptedLoad;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define VK_USE_PLATFORM_WIN32_KHR 1`
- L10 _macro_ `#define VK_USE_PLATFORM_WIN32_KHX 1`
- L12 _macro_ `#define VULKAN_SHOULD_ENABLE_DRAW_MARKERS (UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT)`
- L13 _macro_ `#define VULKAN_USE_CREATE_WIN32_SURFACE 1`
- L14 _macro_ `#define VULKAN_DYNAMICALLYLOADED 1`
- L15 _macro_ `#define VULKAN_SHOULD_ENABLE_DESKTOP_HMD_SUPPORT 1`
- L16 _macro_ `#define VULKAN_SIGNAL_UNIMPLEMENTED() checkf(false, TEXT("Unimplemented vulkan functionality: %s"), StringCast<TCHAR>(__FUNCTION__).Get())`
- L17 _macro_ `#define VULKAN_SUPPORTS_SCALAR_BLOCK_LAYOUT 1`
- L18 _macro_ `#define VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH 1`
- L19 _macro_ `#define VULKAN_SUPPORTS_FULLSCREEN_EXCLUSIVE 1`
- L21 _macro_ `#define UE_VK_API_VERSION VK_API_VERSION_1_1`
- L26 _macro_ `# define VK_TYPE_TO_STRING(Type, Value) ANSI_TO_TCHAR(string_##Type(Value))`
- L27 _macro_ `# define VK_FLAGS_TO_STRING(Type, Value) ANSI_TO_TCHAR(string_##Type(Value).c_str())`
- L30 _macro_ `#define VULKAN_SHOULD_USE_LLM (UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT)`
- L32 _macro_ `#define ENUM_VK_ENTRYPOINTS_PLATFORM_BASE(EnumMacro)`
- L34 _macro_ `#define ENUM_VK_ENTRYPOINTS_PLATFORM_INSTANCE(EnumMacro) \`
- L37 _macro_ `#define ENUM_VK_ENTRYPOINTS_OPTIONAL_PLATFORM_INSTANCE(EnumMacro)`
- L42 _typedef_ `typedef FVulkanGenericPlatformWindowContext FVulkanPlatformWindowContext;`
- L64 _typedef_ `typedef FVulkanWindowsPlatform FVulkanPlatform;`

### `Source/Runtime/VulkanRHI/Private/Windows/WindowsVulkanPlatformDefines.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/VulkanRHI/Public/IVulkanDynamicRHI.h` (Public)


#### struct `FVulkanRHIAllocationInfo`  
`struct FVulkanRHIAllocationInfo`  
_L8-14_
- L10 _public member_ `VkDeviceMemory Handle{};`
- L11 _public member_ `uint64 Offset{};`
- L12 _public member_ `uint64 Size{};`
- L13 _public member_ `VkMemoryPropertyFlags Flags{};`

#### struct `FVulkanRHIImageViewInfo`  
`struct FVulkanRHIImageViewInfo`  
_L16-26_
- L18 _public member_ `VkImageView ImageView;`
- L19 _public member_ `VkImage Image;`
- L20 _public member_ `VkImageSubresourceRange SubresourceRange;`
- L21 _public member_ `VkFormat Format;`
- L22 _public member_ `uint32 Width;`
- L23 _public member_ `uint32 Height;`
- L24 _public member_ `uint32 Depth;`
- L25 _public member_ `ETextureCreateFlags UEFlags;`

#### struct `FVulkanRHIExternalImageDeleteCallbackInfo`  
`struct FVulkanRHIExternalImageDeleteCallbackInfo`  
_L28-32_
- L30 _public member_ `void* UserData = nullptr;`
- L31 _public member_ `void (*Function)(void* UserData) = nullptr;`

#### class `FVulkanRHIExternalDeviceExtensionBase`  
`class FVulkanRHIExternalDeviceExtensionBase : public TSharedFromThis<FVulkanRHIExternalDeviceExtensionBase>`  
_L57-80_
- inherits: `TSharedFromThis<FVulkanRHIExternalDeviceExtensionBase>`
- desc: Base class used for external code (such as plugins) to enable extensions in the Vulkan RHI. The lifetime is managed through the use of TSharedRef. Basic usage:  Using this as a base class, pass in the ExtensionName and overload GetFeaturesStruct() to return the extension specific features struct. IMPORTANT:    Make sure the feature struct has its sType correctly set and pNext to NULL. Example to enable VK_EXT_memory_decompression: class FDeviceExtensionMemoryDecompression : public FVulkanRHIExternalDeviceExtensionBase { FDeviceExtensionMemoryDecompression() : FVulkanRHIExternalDeviceExtensionBase(VK_EXT_MEMORY_DECOMPRESSION_EXTENSION_NAME) { ZeroVulkanStruct(Features, VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_DECOMPRESSION_FEATURES_EXT); } virtual VkBaseOutStructure* GetFeaturesStruct() final override { return reinterpret_cast<VkBaseOutStructure*>(&Features); } VkPhysicalDeviceMemoryDecompressionFeaturesEXT Features; } - If properties are needed, overload GetPropertiesStruct() to return the extension specific properties struct (with sType and pNext initialized). - FeaturesCallback() / PropertiesCallback() are called after those property structures are filled. - If inspection of the features and/or properties reveals the extension should not be loaded, the callbacks should return false. - If the extension is already handled by the engine or loaded by another plugin, DuplicateCallback() will be called.
- L60 _public function_ `FVulkanRHIExternalDeviceExtensionBase(const ANSICHAR* InExtensionName) : ExtensionName(InExtensionName)`
- L61 _public function_ `virtual ~FVulkanRHIExternalDeviceExtensionBase()`
- L64 _public function_ `virtual VkBaseOutStructure* GetFeaturesStruct()` — Returns a pointer to the extension's feature structure
- L67 _public function_ `virtual bool FeaturesCallback()` — Callback when the features structure has been filled.  Return true if the features meet your requirements.
- L70 _public function_ `virtual VkBaseOutStructure* GetPropertiesStruct()` — Pointer to the extension's properties structure
- L73 _public function_ `virtual bool PropertiesCallback()` — Callback when the properties structure has been filled.  Return true if the properties meet your requirements.
- L76 _public function_ `virtual void DuplicateCallback()` — Callback if the extension is found to be a duplicate (already loaded by the engine or other plugin).
- L79 _public member_ `const FAnsiString ExtensionName;` — Name of the extension to be loaded

#### enum `EVulkanRHIRunOnQueueType`  
`enum class EVulkanRHIRunOnQueueType`  
_L82-86_
- L84 _public enumerator_ `Graphics = 0`
- L85 _public enumerator_ `Transfer`

#### class `IVulkanMemoryAllocator`  
`class IVulkanMemoryAllocator`  
_L89-108_
- desc: Patch allocations into the engine's allocators
- L92 _public typedef_ `typedef void* AllocHandle;`
- L94 _public function_ `virtual ~IVulkanMemoryAllocator()`
- L96 _public prototype_ `virtual VkResult AllocateImageMemory(VkImage Image, VkMemoryPropertyFlags Flags, bool bForceDedicatedAllocation, AllocHandle* OutAllocHandle) = 0;`
- L97 _public prototype_ `virtual VkResult AllocateBufferMemory(VkBuffer Buffer, VkMemoryPropertyFlags Flags, bool bForceDedicatedAllocation, AllocHandle* OutAllocHandle) = 0;`
- L98 _public prototype_ `virtual void FreeMemory(const AllocHandle&) = 0;`
- L99 _public prototype_ `virtual FVulkanRHIAllocationInfo GetAllocInfo(const AllocHandle&) = 0;`
- L101 _public prototype_ `virtual void* MapMemory(const AllocHandle&) = 0;`
- L102 _public prototype_ `virtual void UnmapMemory(const AllocHandle&) = 0;`
- L104 _public prototype_ `virtual void FlushMemory(const AllocHandle&, VkDeviceSize Offset, VkDeviceSize Size) = 0;`
- L105 _public prototype_ `virtual void InvalidateMemory(const AllocHandle&, VkDeviceSize Offset, VkDeviceSize Size) = 0;`
- L107 _public prototype_ `virtual FRHIMemoryStats GetMemoryStats() = 0;`

#### struct `IVulkanDynamicRHI`  
`struct IVulkanDynamicRHI : public FDynamicRHI`  
_L110-195_
- inherits: `FDynamicRHI`
- L112 _public function_ `virtual ERHIInterfaceType GetInterfaceType() const override`
- L114 _public prototype_ `virtual uint32 RHIGetVulkanVersion() const = 0;`
- L115 _public prototype_ `virtual VkInstance RHIGetVkInstance() const = 0;`
- L116 _public prototype_ `virtual VkDevice RHIGetVkDevice() const = 0;`
- L117 _public prototype_ `virtual const uint8* RHIGetVulkanDeviceUUID() const = 0;`
- L118 _public prototype_ `virtual VkPhysicalDevice RHIGetVkPhysicalDevice() const = 0;`
- L119 _public prototype_ `virtual const VkAllocationCallbacks* RHIGetVkAllocationCallbacks() = 0;`
- L121 _public prototype_ `virtual IVulkanMemoryAllocator* RHIGetVulkanMemoryAllocator() = 0;`
- L123 _public prototype_ `virtual VkQueue RHIGetGraphicsVkQueue() const = 0;`
- L124 _public prototype_ `virtual uint32 RHIGetGraphicsQueueIndex() const = 0;`
- L125 _public prototype_ `virtual uint32 RHIGetGraphicsQueueFamilyIndex() const = 0;`
- L128 _public function_ `VkCommandBuffer RHIGetActiveVkCommandBuffer()` — `UE_DEPRECATED(5.8, "RHIGetActiveVkCommandBuffer is deprecated, and dangerous because it is incompatible with parallel translation. Use RHIGetVkCommandBuffer(FRHICommandListBase&).")`
- L138 _public prototype_ `virtual VkCommandBuffer RHIGetVkCommandBuffer(FRHICommandListBase& ExecutingCmdList) const = 0;` — Returns the command buffer for the currently active pipeline on the given RHI command list. Can only be called on executing command lists (i.e. ExecutingCmdList.IsBottomOfPipe() must be true),
- L140 _public prototype_ `virtual uint64 RHIGetGraphicsAdapterLUID(VkPhysicalDevice InPhysicalDevice) const = 0;`
- L141 _public prototype_ `virtual bool RHIDoesAdapterMatchDevice(const void* InAdapterId) const = 0;`
- L142 _public prototype_ `virtual void* RHIGetVkDeviceProcAddr(const char* InName) const = 0;`
- L143 _public prototype_ `virtual void* RHIGetVkInstanceProcAddr(const char* InName) const = 0;`
- L148 _public prototype_ `virtual void* RHIGetVkInstanceGlobalProcAddr(const char* InName) const = 0;` — Version of RHIGetVkInstanceProcAddr that uses nullptr as the instance argument. See vkGetInstanceProcAddr manpage for distinction between "global" and non-global commands.
- L149 _public prototype_ `virtual VkFormat RHIGetSwapChainVkFormat(EPixelFormat InFormat) const = 0;`
- L150 _public prototype_ `virtual bool RHISupportsEXTFragmentDensityMap2() const = 0;`
- L152 _public prototype_ `virtual void RHISetFDMOffsets(const FVector2f GazePoint[2], FIntPoint FramebufferSize) = 0;`
- L154 _public prototype_ `virtual TArray<VkExtensionProperties> RHIGetAllInstanceExtensions() const = 0;`
- L155 _public prototype_ `virtual TArray<VkExtensionProperties> RHIGetAllDeviceExtensions(VkPhysicalDevice InPhysicalDevice) const = 0;`
- L156 _public prototype_ `virtual TArray<FAnsiString> RHIGetLoadedDeviceExtensions() const = 0;`
- L158 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromResource(EPixelFormat Format, uint32 SizeX, uint32 SizeY, uint32 NumMips, uint32 NumSamples, VkImage Resource, ETextureCreateFlags Flags, const FClearValueBinding& ClearValueBinding = FClearValueBinding::Transparent, const FVulkanRHIExternalImageDeleteCallbackInfo& ExternalImageDeleteCallbackInfo = {}) = 0;`
- L160 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromAndroidHardwareBuffer(AHardwareBuffer* HardwareBuffer) = 0;`
- L162 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DArrayFromResource(EPixelFormat Format, uint32 SizeX, uint32 SizeY, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, VkImage Resource, ETextureCreateFlags Flags, const FClearValueBinding& ClearValueBinding = FClearValueBinding::Transparent) = 0;`
- L163 _public prototype_ `virtual FTextureRHIRef RHICreateTextureCubeFromResource(EPixelFormat Format, uint32 Size, bool bArray, uint32 ArraySize, uint32 NumMips, VkImage Resource, ETextureCreateFlags Flags, const FClearValueBinding& ClearValueBinding = FClearValueBinding::Transparent) = 0;`
- L165 _public prototype_ `virtual VkImage RHIGetVkImage(FRHITexture* InTexture) const = 0;`
- L166 _public prototype_ `virtual VkFormat RHIGetViewVkFormat(FRHITexture* InTexture) const = 0;`
- L167 _public prototype_ `virtual FVulkanRHIAllocationInfo RHIGetAllocationInfo(FRHITexture* InTexture) const = 0;`
- L168 _public prototype_ `virtual FVulkanRHIImageViewInfo RHIGetImageViewInfo(FRHITexture* InTexture) const = 0;`
- L169 _public prototype_ `virtual FVulkanRHIAllocationInfo RHIGetAllocationInfo(FRHIBuffer* InBuffer) const = 0;`
- L171 _public prototype_ `virtual void RHIFinishExternalComputeWork(VkCommandBuffer InCommandBuffer) = 0;`
- L172 _public prototype_ `virtual void RHIVerifyResult(VkResult Result, const ANSICHAR* VkFuntion, const ANSICHAR* Filename, uint32 Line) = 0;`
- L174 _public prototype_ `static void AddEnabledInstanceExtensionsAndLayers(TArrayView<const ANSICHAR* const> InInstanceExtensions, TArrayView<const ANSICHAR* const> InInstanceLayers);`
- L175 _public function_ `static void AddEnabledDeviceExtensionsAndLayers(TArrayView<const ANSICHAR* const> InDeviceExtensions, TArrayView<const ANSICHAR* const> InDeviceLayers)`
- L185 _public prototype_ `static void AddEnabledDeviceExtensionsAndLayers(TArrayView<TSharedRef<FVulkanRHIExternalDeviceExtensionBase>> InDeviceExtensions, TArrayView<const ANSICHAR* const> InDeviceLayers);`
- L189 _public prototype_ `virtual void RHIRunOnQueue(EVulkanRHIRunOnQueueType QueueType, TFunction<void(VkQueue)>&& CodeToRun, bool bWaitForSubmission) = 0;` — Runs code on SubmissionThread with access to VkQueue.  Useful for plugins.
- L192 _public function_ `void RHIRegisterWork(uint32 NumPrimitives)` — `UE_DEPRECATED(5.8, "RHIRegisterWork is deprecated, and there is no replacement. Remove calls to this function.")`

#### Free symbols / members of external scopes

- L197 _function_ `inline IVulkanDynamicRHI* GetIVulkanDynamicRHI()`
- L204 _macro_ `#define VERIFYVULKANRESULT_EXTERNAL(VkFunction) { const VkResult ScopedResult = VkFunction; if (ScopedResult != VK_SUCCESS) { GetIVulkanDynamicRHI()->RHIVerifyResult(ScopedResult, #VkFunction, __FILE__, __LINE__); }}`

### `Source/Runtime/VulkanRHI/Public/VulkanCommon.h` (Public)


#### enum `ShaderStage::EStage`  
`enum EStage`  
_L27-51_
- desc: There should be one value for each value in EShaderFrequency. These values are meant to be used as indices in contexts where values for different bind points can overlap (Graphics/Compute/RayTracing) like shader arrays in pipeline states or UB binding indices for Graphics (Vertex==0, Pixel==1) that can overlap with Compute (Compute==0). IMPORTANT: Adjusting these requires a full shader rebuild (ie modify the GUID in VulkanCommon.usf)
- L29 _public enumerator_ `Vertex = 0`
- L30 _public enumerator_ `Pixel = 1`
- L31 _public enumerator_ `Geometry = 2`
- L32 _public enumerator_ `Mesh = 3`
- L33 _public enumerator_ `Task = 4`
- L35 _public enumerator_ `NumGraphicsStages = 5`
- L37 _public enumerator_ `RayGen = 0`
- L38 _public enumerator_ `RayMiss = 1`
- L39 _public enumerator_ `RayHitGroup = 2`
- L40 _public enumerator_ `RayCallable = 3`
- L42 _public enumerator_ `NumRayTracingStages = 4`
- L44 _public enumerator_ `Compute = 0`
- L46 _public enumerator_ `NumComputeStages = 1`
- L48 _public enumerator_ `MaxNumStages = 6` — work with even count to simplify bindless alignment requirements
- L50 _public enumerator_ `Invalid = -1`

#### enum `VulkanBindless::EDescriptorSets`  
`enum EDescriptorSets`  
_L100-124_
- L102 _public enumerator_ `BindlessSamplerSet = 0`
- L103 _public enumerator_ `BindlessResourceSet = 1`
- L105 _public enumerator_ `BindlessStorageBufferSet = BindlessResourceSet`
- L106 _public enumerator_ `BindlessUniformBufferSet = BindlessResourceSet`
- L108 _public enumerator_ `BindlessStorageImageSet = BindlessResourceSet`
- L109 _public enumerator_ `BindlessSampledImageSet = BindlessResourceSet`
- L111 _public enumerator_ `BindlessStorageTexelBufferSet = BindlessResourceSet`
- L112 _public enumerator_ `BindlessUniformTexelBufferSet = BindlessResourceSet`
- L114 _public enumerator_ `BindlessAccelerationStructureSet = BindlessResourceSet`
- L117 _public enumerator_ `NumBindlessSets` — Number of sets reserved for samplers/resources
- L120 _public enumerator_ `BindlessSingleUseUniformBufferSet = NumBindlessSets` — Index of the descriptor set used for single use ub (like globals)
- L123 _public enumerator_ `MaxNumSets = NumBindlessSets + 1` — Total number of descriptor sets used in a bindless pipeline

#### Free symbols / members of external scopes

- L13 _macro_ `#define VULKAN_SUPPORTS_GEOMETRY_SHADERS PLATFORM_SUPPORTS_GEOMETRY_SHADERS`
- L19 _macro_ `#define VULKAN_ENABLE_BINDING_DEBUG_NAMES 0` — This defines controls shader generation (so will cause a format rebuild) be careful wrt cooker/target platform not matching define-wise!!! ONLY used for debugging binding table/descriptor set bugs/mismatches.
- L21 _namespace_ `namespace ShaderStage`
- L55 _function_ `inline EStage GetStageForFrequency(EShaderFrequency Stage)` (scope `ShaderStage`)
- L77 _function_ `inline EShaderFrequency GetFrequencyForGfxStage(EStage Stage)` (scope `ShaderStage`)
- L95 _namespace_ `namespace VulkanBindless`
- L97 _variable_ `static constexpr uint32 MaxUniformBuffersPerStage = 16;` (scope `VulkanBindless`)
- L98 _variable_ `static constexpr uint32 MaxUniformBuffersTotal = 32;` (scope `VulkanBindless`) — Guaranteed to be min 32 by Vulkan 1.4
- L126 _function_ `inline int32 GetOffsetForFrequency(EShaderFrequency Frequency)` (scope `VulkanBindless`)
- L159 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVulkan, Display, All);`
- L159 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVulkan, Display, All);`
- L162 _function_ `template< class T > static inline void ZeroVulkanStruct(T& Struct, int32 VkStructureType)`
- L173 _function_ `template <typename ExistingChainType, typename NewStructType> static inline void AddToPNext(ExistingChainType& Existing, NewStructType& Added)`

### `Source/Runtime/VulkanRHI/Public/VulkanConfiguration.h` (Public)


#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_VK_API_VERSION VK_API_VERSION_1_1`
- L24 _macro_ `#define VULKAN_SHOULD_DEBUG_IN_DEVELOPMENT 1`
- L28 _macro_ `#define VULKAN_HAS_DEBUGGING_ENABLED (!IS_PROGRAM && (UE_BUILD_DEBUG || (UE_BUILD_DEVELOPMENT && VULKAN_SHOULD_DEBUG_IN_DEVELOPMENT)))`
- L39 _macro_ `#define VULKAN_VALIDATION_DEFAULT_VALUE (UE_BUILD_DEBUG ? 2 : 0)`
- L43 _macro_ `#define VULKAN_SHOULD_ENABLE_DRAW_MARKERS 0`
- L48 _macro_ `#define VULKAN_ENABLE_DUMP_LAYER 0`
- L51 _macro_ `#define VULKAN_ENABLE_DRAW_MARKERS VULKAN_SHOULD_ENABLE_DRAW_MARKERS`
- L54 _macro_ `#define VULKAN_ENABLE_IMAGE_TRACKING_LAYER 0`
- L58 _macro_ `#define VULKAN_ENABLE_BUFFER_TRACKING_LAYER 0`
- L61 _macro_ `#define VULKAN_ENABLE_TRACKING_LAYER (VULKAN_ENABLE_BUFFER_TRACKING_LAYER || VULKAN_ENABLE_IMAGE_TRACKING_LAYER)`
- L62 _macro_ `#define VULKAN_ENABLE_WRAP_LAYER (VULKAN_ENABLE_DUMP_LAYER || VULKAN_ENABLE_TRACKING_LAYER)`
- L64 _macro_ `#define VULKAN_HASH_POOLS_WITH_TYPES_USAGE_ID 1`
- L66 _macro_ `#define VULKAN_SINGLE_ALLOCATION_PER_RESOURCE 0`
- L69 _macro_ `#define VULKAN_SHOULD_USE_LLM 0`
- L73 _macro_ `#define VULKAN_USE_LLM ((ENABLE_LOW_LEVEL_MEM_TRACKER) && VULKAN_SHOULD_USE_LLM)`
- L77 _macro_ `#define VULKAN_CUSTOM_MEMORY_MANAGER_ENABLED VULKAN_USE_LLM`
- L81 _macro_ `#define VULKAN_SHOULD_USE_COMMANDWRAPPERS VULKAN_ENABLE_WRAP_LAYER`
- L85 _macro_ `#define VULKAN_COMMANDWRAPPERS_ENABLE VULKAN_SHOULD_USE_COMMANDWRAPPERS`
- L89 _macro_ `#define VULKAN_USE_IMAGE_ACQUIRE_FENCES 1`
- L92 _macro_ `#define VULKAN_ENABLE_AGGRESSIVE_STATS 0`
- L94 _macro_ `#define VULKAN_REUSE_FENCES 1`
- L97 _macro_ `#define VULKAN_QUERY_CALLSTACK 0`
- L101 _macro_ `#define VULKAN_ENABLE_DESKTOP_HMD_SUPPORT 0`
- L105 _macro_ `#define VULKAN_SIGNAL_UNIMPLEMENTED()`
- L109 _macro_ `#define VULKAN_ENABLE_LRU_CACHE 0`
- L113 _macro_ `#define VULKAN_SUPPORTS_VALIDATION_CACHE 1`
- L117 _macro_ `#define VULKAN_HAS_VALIDATION_FEATURES 1`
- L121 _macro_ `#define VULKAN_SUPPORTS_DEDICATED_ALLOCATION 1`
- L125 _macro_ `#define VULKAN_SUPPORTS_GOOGLE_DISPLAY_TIMING 0`
- L129 _macro_ `#define VULKAN_USE_CREATE_ANDROID_SURFACE 0`
- L133 _macro_ `#define VULKAN_USE_CREATE_WIN32_SURFACE 0`
- L137 _macro_ `#define VULKAN_USE_DIFFERENT_POOL_CMDBUFFERS 1`
- L141 _macro_ `#define VULKAN_DELETE_STALE_CMDBUFFERS 1`
- L145 _macro_ `#define VULKAN_SUPPORTS_SCALAR_BLOCK_LAYOUT 1`
- L150 _macro_ `#define VULKAN_SUPPORTS_MEMORY_BUDGET 1`
- L154 _macro_ `#define VULKAN_SUPPORTS_MEMORY_PRIORITY 1`
- L158 _macro_ `#define VULKAN_SUPPORTS_DRIVER_PROPERTIES 1`
- L162 _macro_ `#define VULKAN_SUPPORTS_QCOM_RENDERPASS_SHADER_RESOLVE 1`
- L166 _macro_ `#define VULKAN_SUPPORTS_FULLSCREEN_EXCLUSIVE 0`
- L170 _macro_ `#define VULKAN_SUPPORTS_TEXTURE_COMPRESSION_ASTC_HDR 1`
- L174 _macro_ `#define VULKAN_SUPPORTS_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER 1`
- L178 _macro_ `#define VULKAN_SUPPORTS_RENDERPASS2 1`
- L182 _macro_ `#define VULKAN_SUPPORTS_ASTC_DECODE_MODE 1`
- L186 _macro_ `#define VULKAN_SUPPORTS_SHADER_VIEWPORT_INDEX_LAYER 1`
- L190 _macro_ `#define VULKAN_SUPPORTS_DESCRIPTOR_INDEXING 1`
- L194 _macro_ `#define VULKAN_OBJECT_TRACKING 0 //Track objects created and memory used. use r.vulkan.dumpmemory to dump to console`
- L197 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVulkanRHI, Log, All);`
- L200 _macro_ `#define VULKAN_CPU_ALLOCATOR VulkanRHI::GetMemoryAllocator(nullptr)`
- L202 _macro_ `#define VULKAN_CPU_ALLOCATOR nullptr`
- L206 _macro_ `#define VULKAN_PURGE_SHADER_MODULES 0`
- L210 _macro_ `#define VULKAN_SUPPORTS_TRANSIENT_RESOURCE_ALLOCATOR 1`
- L214 _macro_ `# define VK_TYPE_TO_STRING(Type, Value) *FString::Printf(TEXT("%u"), (uint32)Value)`
- L217 _macro_ `# define VK_FLAGS_TO_STRING(Type, Value) *FString::Printf(TEXT("%u"), (uint32)Value)`
- L221 _macro_ `# define VULKAN_USE_DEBUG_NAMES 1`
- L224 _namespace_ `namespace VulkanRHI`
- L226 _function_ `static inline const VkAllocationCallbacks* GetMemoryAllocator(const VkAllocationCallbacks* Allocator)` (scope `VulkanRHI`)
- L229 _externvar_ `extern VkAllocationCallbacks GAllocationCallbacks;` (scope `VulkanRHI::GetMemoryAllocator`)

### `Source/Runtime/VulkanRHI/Public/VulkanDynamicRHI.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/VulkanRHI/Public/VulkanShaderResources.h` (Public)


#### struct `FVulkanShaderHeader`  
`struct FVulkanShaderHeader`  
_L20-141_
- desc: Vulkan ParameterMap: Buffer Index = EBufferIndex Base Offset = Index into the subtype Size = Ignored for non-globals
- L31 _public member_ `TArray<FBindingInfo> Bindings;`
- L40 _public member_ `TArray<FUniformBufferInfo> UniformBufferInfos;`
- L64 _public member_ `TArray<FInputAttachmentInfo> InputAttachmentInfos;`
- L86 _public member_ `TArray<FGlobalSamplerInfo> GlobalSamplerInfos;`
- L90 _public member_ `uint32 NumBoundUniformBuffers = 0;` — The number of uniform buffers containing constants and requiring bindings Uniform buffers beyond this index do not have bindings (resource only UB)
- L94 _public member_ `uint32 PackedGlobalsSize = 0;` — Size of the uniform buffer containing packed globals If present (not zero), it will always be at binding 0 of the stage
- L97 _public member_ `uint32 InputAttachmentsMask = 0;` — Mask of input attachments being used (the index of the bit corresponds to EAttachmentType value)
- L100 _public member_ `uint32 InOutMask;` — Mostly relevant for Vertex Shaders
- L103 _public member_ `uint32 RayTracingPayloadType = 0;` — Relevant for Ray Tracing Shaders
- L104 _public member_ `uint32 RayTracingPayloadSize = 0;`
- L107 _public member_ `FSpecializationConstantData SpecializationConstantData;` — Specialization constant info
- L109 _public member_ `FShaderHash CodeHash;`
- L110 _public member_ `uint32 SpirvCRC = 0;`
- L111 _public member_ `uint8 WaveSize = 0;`
- L127 _public member_ `ERayHitGroupEntrypoint RayGroupAnyHit = ERayHitGroupEntrypoint::NotPresent;`
- L128 _public member_ `ERayHitGroupEntrypoint RayGroupIntersection = ERayHitGroupEntrypoint::NotPresent;`
- L130 _public member_ `FString DebugName;`
- L132 _public prototype_ `FVulkanShaderHeader() = default;`
- L137 _public function_ `FVulkanShaderHeader(EInit) : InOutMask(0)`

#### struct `FVulkanShaderHeader::FBindingInfo`  
`struct FBindingInfo`  
_L23-30_
- desc: Includes all bindings, the index in this array is the binding slot
- L26 _public member_ `uint32 DescriptorType;` — VkDescriptorType
- L28 _public member_ `FString DebugName;`

#### struct `FVulkanShaderHeader::FUniformBufferInfo`  
`struct FUniformBufferInfo`  
_L34-39_
- desc: FBindingInfo with type VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER have a corresponding entry in this table (at the same index)
- L36 _public member_ `uint32 LayoutHash;`
- L37 _public member_ `uint8 bHasResources;`
- L38 _public member_ `uint8 BindlessCBIndex;`

#### enum `FVulkanShaderHeader::EAttachmentType`  
`enum class EAttachmentType : uint8`  
_L43-56_
- desc: The order of this enum should always match the strings in VulkanBackend.cpp (VULKAN_SUBPASS_FETCH)
- L45 _public enumerator_ `Depth`
- L46 _public enumerator_ `Color0`
- L47 _public enumerator_ `Color1`
- L48 _public enumerator_ `Color2`
- L49 _public enumerator_ `Color3`
- L50 _public enumerator_ `Color4`
- L51 _public enumerator_ `Color5`
- L52 _public enumerator_ `Color6`
- L53 _public enumerator_ `Color7`
- L55 _public enumerator_ `Count`

#### struct `FVulkanShaderHeader::FInputAttachmentInfo`  
`struct FInputAttachmentInfo`  
_L59-63_
- desc: Used to determine the EAttachmentType of a FBindingInfo with type VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT
- L61 _public member_ `uint8 BindingIndex;`
- L62 _public member_ `EAttachmentType Type;`

#### enum `FVulkanShaderHeader::EGlobalSamplerType`  
`enum class EGlobalSamplerType : uint8`  
_L69-80_
- desc: Types of Global Samplers (see Common.ush for types) Must match GetGlobalSamplerType() in SpirVShaderCompiler.inl and and declarations in VulkanCommon.ush
- L71 _public enumerator_ `PointClampedSampler`
- L72 _public enumerator_ `PointWrappedSampler`
- L73 _public enumerator_ `BilinearClampedSampler`
- L74 _public enumerator_ `BilinearWrappedSampler`
- L75 _public enumerator_ `TrilinearClampedSampler`
- L76 _public enumerator_ `TrilinearWrappedSampler`
- L78 _public enumerator_ `Count`
- L79 _public enumerator_ `Invalid`

#### struct `FVulkanShaderHeader::FGlobalSamplerInfo`  
`struct FGlobalSamplerInfo`  
_L81-85_
- L83 _public member_ `uint8 BindingIndex;`
- L84 _public member_ `EGlobalSamplerType Type;`

#### enum `FVulkanShaderHeader::ERayHitGroupEntrypoint`  
`enum class ERayHitGroupEntrypoint : uint8`  
_L114-126_
- desc: For RayHitGroup shaders
- L116 _public enumerator_ `NotPresent = 0`
- L121 _public enumerator_ `CommonBlob` — Hit group types are all stored in a single spirv blob and each have different entry point names NOTE: Not used yet because of compiler issues
- L125 _public enumerator_ `SeparateBlob` — Hit group types are each stored in a different spirv blob to circumvent DXC compilation issues

#### enum `FVulkanShaderHeader::EInit`  
`enum EInit`  
_L133-136_
- L135 _public enumerator_ `EZero`

#### Free symbols / members of external scopes

- L143 _function_ `inline FArchive& operator<<(FArchive& Ar, FVulkanShaderHeader::FBindingInfo& BindingInfo)`
- L152 _function_ `inline FArchive& operator<<(FArchive& Ar, FVulkanShaderHeader::FUniformBufferInfo& Info)`
- L160 _function_ `inline FArchive& operator<<(FArchive& Ar, FVulkanShaderHeader::FInputAttachmentInfo& Info)`
- L167 _function_ `inline FArchive& operator<<(FArchive& Ar, FVulkanShaderHeader::FGlobalSamplerInfo& Info)`
- L174 _function_ `inline FArchive& operator<<(FArchive& Ar, FVulkanShaderHeader& Header)`

### `Source/Runtime/VulkanRHI/Public/VulkanThirdParty.h` (Public)


#### enum `VkDescriptorType`  
`typedef enum VkDescriptorType`  
_L15-36_
- desc: Horrible hack as we need the enum available but the Vulkan headers do not compile on Mac
- L16 _public enumerator_ `VK_DESCRIPTOR_TYPE_SAMPLER = 0`
- L17 _public enumerator_ `VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER = 1`
- L18 _public enumerator_ `VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE = 2`
- L19 _public enumerator_ `VK_DESCRIPTOR_TYPE_STORAGE_IMAGE = 3`
- L20 _public enumerator_ `VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER = 4`
- L21 _public enumerator_ `VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER = 5`
- L22 _public enumerator_ `VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER = 6`
- L23 _public enumerator_ `VK_DESCRIPTOR_TYPE_STORAGE_BUFFER = 7`
- L24 _public enumerator_ `VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC = 8`
- L25 _public enumerator_ `VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC = 9`
- L26 _public enumerator_ `VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT = 10`
- L27 _public enumerator_ `VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK = 1000138000`
- L28 _public enumerator_ `VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR = 1000150000`
- L29 _public enumerator_ `VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV = 1000165000`
- L30 _public enumerator_ `VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM = 1000440000`
- L31 _public enumerator_ `VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM = 1000440001`
- L32 _public enumerator_ `VK_DESCRIPTOR_TYPE_MUTABLE_EXT = 1000351000`
- L33 _public enumerator_ `VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT = VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK`
- L34 _public enumerator_ `VK_DESCRIPTOR_TYPE_MUTABLE_VALVE = VK_DESCRIPTOR_TYPE_MUTABLE_EXT`
- L35 _public enumerator_ `VK_DESCRIPTOR_TYPE_MAX_ENUM = 0x7FFFFFFF`

#### Free symbols / members of external scopes

- L36 _typedef_ `} VkDescriptorType;`
- L40 _macro_ `#define VK_NO_PROTOTYPES`
- L46 _macro_ `#define VK_DESCRIPTOR_TYPE_BEGIN_RANGE (VK_DESCRIPTOR_TYPE_SAMPLER)` — workaround for removed defines in sdk 141
- L47 _macro_ `#define VK_DESCRIPTOR_TYPE_END_RANGE (VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT)`
- L48 _macro_ `#define VK_DESCRIPTOR_TYPE_RANGE_SIZE (VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT - VK_DESCRIPTOR_TYPE_SAMPLER + 1)`
- L49 _macro_ `#define VK_IMAGE_VIEW_TYPE_RANGE_SIZE (VK_IMAGE_VIEW_TYPE_CUBE_ARRAY - VK_IMAGE_VIEW_TYPE_1D + 1)`
- L50 _macro_ `#define VK_FORMAT_RANGE_SIZE (VK_FORMAT_ASTC_12x12_SRGB_BLOCK - VK_FORMAT_UNDEFINED + 1)`

### `Source/Runtime/VulkanRHI/Public/VulkanUtil.h` (Public)


#### class `TDataKeyBase`  
`template <> class TDataKeyBase<0>`  
_L49-67_
- L53 _protected function_ `template <class DataReceiver> void GetData(DataReceiver&& ReceiveData)`
- L59 _protected function_ `void SetData(const void* InData, uint32 InSize)`
- L61 _protected function_ `void CopyDataDeep(TDataKeyBase& Result) const`
- L62 _protected function_ `void CopyDataShallow(TDataKeyBase& Result) const`
- L63 _protected function_ `bool IsDataEquals(const TDataKeyBase& Other) const`
- L66 _protected member_ `uint32 Hash = 0;`
- L108 _public function_ `TArray<uint8>& GetDataRef()`
- L114 _private function_ `void EnsureDataStorage()`
- L125 _protected member_ `TArray<uint8> *Data = nullptr;`
- L127 _private member_ `TUniquePtr<TArray<uint8>> DataStorage;`

#### class `TDataKeyBase`  
`template <> class TDataKeyBase<1>`  
_L70-128_
- L53 _protected function_ `template <class DataReceiver> void GetData(DataReceiver&& ReceiveData)`
- L59 _protected function_ `void SetData(const void* InData, uint32 InSize)`
- L61 _protected function_ `void CopyDataDeep(TDataKeyBase& Result) const`
- L62 _protected function_ `void CopyDataShallow(TDataKeyBase& Result) const`
- L63 _protected function_ `bool IsDataEquals(const TDataKeyBase& Other) const`
- L66 _protected member_ `uint32 Hash = 0;`
- L108 _public function_ `TArray<uint8>& GetDataRef()`
- L114 _private function_ `void EnsureDataStorage()`
- L125 _protected member_ `TArray<uint8> *Data = nullptr;`
- L127 _private member_ `TUniquePtr<TArray<uint8>> DataStorage;`

#### class `TDataKeyBase`  
`template <> class TDataKeyBase<2> : public TDataKeyBase<1>`  
_L131-140_
- inherits: `TDataKeyBase<1>`
- L53 _protected function_ `template <class DataReceiver> void GetData(DataReceiver&& ReceiveData)`
- L59 _protected function_ `void SetData(const void* InData, uint32 InSize)`
- L61 _protected function_ `void CopyDataDeep(TDataKeyBase& Result) const`
- L62 _protected function_ `void CopyDataShallow(TDataKeyBase& Result) const`
- L63 _protected function_ `bool IsDataEquals(const TDataKeyBase& Other) const`
- L66 _protected member_ `uint32 Hash = 0;`
- L108 _public function_ `TArray<uint8>& GetDataRef()`
- L114 _private function_ `void EnsureDataStorage()`
- L125 _protected member_ `TArray<uint8> *Data = nullptr;`
- L127 _private member_ `TUniquePtr<TArray<uint8>> DataStorage;`

#### class `TDataKey`  
`template <class Derived, bool AlwaysCompareData = false> class TDataKey : public TDataKeyBase<AlwaysCompareData ? 2 : (DO_CHECK != 0)>`  
_L143-202_
- inherits: `TDataKeyBase<AlwaysCompareData?2:(DO_CHECK != 0)>`
- L147 _public function_ `template <class ArchiveWriter> void GenerateFromArchive(ArchiveWriter&& WriteToArchive, int32 DataReserve = 0)`
- L161 _public function_ `template <class ObjectType> void GenerateFromObject(const ObjectType& Object)`
- L166 _public function_ `void GenerateFromData(const void* InData, uint32 InSize)`
- L172 _public function_ `uint32 GetHash() const`
- L177 _public function_ `Derived CopyDeep() const`
- L185 _public function_ `Derived CopyShallow() const`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace VulkanRHI`
- L27 _prototype_ `extern void VerifyVulkanResult(VkResult Result, const ANSICHAR* VkFuntion, const ANSICHAR* Filename, uint32 Line);` (scope `VulkanRHI`) — Checks that the given result isn't a failure.  If it is, the application exits with an appropriate error message. @param	Result - The result code to check @param	Code - The code which yielded the result. @param	VkFunction - Tested function name. @param	Filename - The filename of the source file containing Code. @param	Line - The line number of Code within Filename.
- L29 _prototype_ `VkBuffer CreateBuffer(FVulkanDevice* InDevice, VkDeviceSize Size, VkBufferUsageFlags BufferUsageFlags, VkMemoryRequirements& OutMemoryRequirements);` (scope `VulkanRHI`)
- L32 _macro_ `#define VERIFYVULKANRESULT(VkFunction) { const VkResult ScopedResult = VkFunction; if (ScopedResult != VK_SUCCESS) { VulkanRHI::VerifyVulkanResult(ScopedResult, #VkFunction, __FILE__, __LINE__); }}`
- L33 _macro_ `#define VERIFYVULKANRESULT_EXPANDED(VkFunction) { const VkResult ScopedResult = VkFunction; if (ScopedResult < VK_SUCCESS) { VulkanRHI::VerifyVulkanResult(ScopedResult, #VkFunction, __FILE__, __LINE__); }}`
- L35 _prototype_ `void SetVulkanResourceName(FVulkanDevice* Device, FVulkanTexture* Texture, const TCHAR* Name);`
- L38 _function_ `template<typename T> inline bool CopyAndReturnNotEqual(T& A, T B)`
- L150 _function_ `` (scope `TDataKey::GenerateFromArchive`)
- L193 _function_ `friend uint32 GetTypeHash(const Derived& Key)`
- L198 _function_ `friend bool operator==(const Derived& A, const Derived& B)`
