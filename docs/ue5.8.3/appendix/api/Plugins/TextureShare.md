# Plugins / TextureShare

- module root: `Plugins/VirtualProduction/TextureShare/Source/TextureShare`
- headers: 30; symbols: 610
- symbol kinds: class=21, delegate=27, enum=3, enumerator=10, function=73, macro=2, member=133, namespace=3, prototype=306, struct=21, variable=11
- PrivateDependencyModuleNames: Core, D3D11RHI, D3D12RHI, Engine, RHI, RHICore, RenderCore, Renderer, Slate, SlateCore, TextureShareCore, UnrealEd, VulkanRHI
- PrivateIncludePathModuleNames: VulkanRHI
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Projects

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Containers/TextureShareContainers.h` (Private)


#### struct `FTextureShareData`  
`struct FTextureShareData`  
_L12-37_
- desc: Data from TextureShareObject sent to proxy
- L15 _public function_ `const FTextureShareCoreResourceRequest* FindResourceRequest(const FTextureShareCoreResourceDesc& InResourceDesc) const`
- L30 _public member_ `FTextureShareViewsData Views;` — Map from UE stereoscopic pass to FTextureShareViewportDesc
- L33 _public member_ `FTextureShareCoreData ObjectData;` — Saved local data from game thread
- L36 _public member_ `TArray<FTextureShareCoreObjectData> ReceivedObjectsData;` — Saved received data from game thread

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Containers/TextureShareContainers_Color.h` (Private)


#### struct `FTextureShareColorDesc`  
`struct FTextureShareColorDesc`  
_L11-62_
- desc: This is a container with information related to color: gamma, sRGB, OCIO, etc. Used to support color conversion to and from the TS SDK.
- L14 _public prototype_ `FTextureShareColorDesc() = default;` — Default constructor.
- L17 _public function_ `FTextureShareColorDesc(const float InCustomGamma) : GammaType(ETextureShareResourceGammaType::Custom) , CustomGamma(InCustomGamma)` — Constructor for custom gamma.
- L22 _public function_ `FTextureShareColorDesc(const ETextureShareResourceGammaType InGammaType) : GammaType(InGammaType)`
- L27 _public function_ `inline bool IsGammaDefined() const` — Return true if gamma is defined.
- L42 _public function_ `inline bool ShouldConvertGamma(const FTextureShareColorDesc& InDestColor) const` — Is the gamma should be converted.
- L48 _public function_ `inline bool operator==(const FTextureShareColorDesc& InDestColor) const` — Implements compare operator.
- L56 _public member_ `ETextureShareResourceGammaType GammaType = ETextureShareResourceGammaType::None;` — Gamma type
- L59 _public member_ `float CustomGamma = -1.f;` — User-defined gamma parameter. The default value of '-1' indicates undefined.

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Containers/TextureShareContainers_Views.h` (Private)


#### struct `FTextureShareSceneViewInfo`  
`struct FTextureShareSceneViewInfo`  
_L12-35_
- desc: Scene view info: ViewDesc -> UE ViewIndex&Pass
- L15 _public member_ `FTextureShareCoreViewDesc ViewDesc;` — View description
- L18 _public member_ `int32 StereoViewIndex = INDEX_NONE;` — View index
- L21 _public member_ `EStereoscopicPass StereoscopicPass = EStereoscopicPass::eSSP_PRIMARY;` — Stereoscopic pass
- L24 _public prototype_ `FTextureShareSceneViewInfo() = default;`
- L26 _public function_ `FTextureShareSceneViewInfo(const FTextureShareCoreViewDesc& InViewDesc, const int32 InStereoViewIndex, const EStereoscopicPass InStereoscopicPass) : ViewDesc(InViewDesc), StereoViewIndex(InStereoViewIndex), StereoscopicPass(InStereoscopicPass)`
- L31 _public function_ `bool Equals(const int32 InStereoViewIndex, const EStereoscopicPass InStereoscopicPass) const`

#### struct `FTextureShareViewsData`  
`struct FTextureShareViewsData`  
_L40-64_
- desc: Map from UE stereoscopic pass to FTextureShareViewDesc
- L42 _public member_ `TArray<FTextureShareSceneViewInfo> Views;`
- L45 _public function_ `const FTextureShareSceneViewInfo* Find(const int32 InStereoViewIndex, const EStereoscopicPass InStereoscopicPass) const`
- L53 _public function_ `bool Add(const FTextureShareCoreViewDesc& InViewDesc, const int32 InStereoViewIndex, const EStereoscopicPass InStereoscopicPass)`

#### Free symbols / members of external scopes

- L48 _function_ `` (scope `FTextureShareViewsData::Find`)

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Containers/TextureShareEnums.h` (Private)


#### enum `ETextureShareObjectProxyFlags`  
`enum class ETextureShareObjectProxyFlags : uint8`  
_L9-32_
- desc: TextureShare proxy object flags
- L11 _public enumerator_ `None = 0`
- L15 _public enumerator_ `WritableSceneTextures = 1 << 0` — The scene textures are writable. The other party can override UE scene textures. This flag is used by the FTextureShareSceneViewExtension
- L18 _public enumerator_ `SessionStarted = 1 << 5` — Session started (internal)
- L21 _public enumerator_ `FrameProxySyncActive = 1 << 6` — Frame proxy sync valid (internal)
- L25 _public enumerator_ `ViewExtensionUsed = 1 << 7` — The view extension is used by this TS proxy object (internal) this means that callbacks will be called from the FTextureShareSceneViewExtension
- L28 _public enumerator_ `InternalFlags = SessionStarted | FrameProxySyncActive | ViewExtensionUsed` — Internal flags, that can't be override by the function SetObjectProxyFlags()

#### enum `ETextureShareResourceGammaType`  
`enum class ETextureShareResourceGammaType : uint8`  
_L45-54_
- desc: This enumeration defines the gamma conversion method implemented in TextureShare. Texture resources in UE can use multiple gamma types. This can be a simple gamma based on the pow() function Or it can be a other gamma function that based on custom math (see /Engine/Private/GammaCorrectionCommon.ush) The other party can request to share a resource with a custom gamut, such as linear, in order to process it. It is also expected that the result sent back will be converted to the original gamut.
- L48 _public enumerator_ `None = 0` — Gamma is not used for this resource
- L51 _public enumerator_ `Custom` — The gamma is based on pow() function.

#### Free symbols / members of external scopes

- L33 _prototype_ `ENUM_CLASS_FLAGS(ETextureShareObjectProxyFlags);`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Game/Settings/TextureShareSettings.h` (Private)


#### struct `FTextureShareSettings`  
`struct FTextureShareSettings`  
_L15-26_
- desc: TextureShare plugin settings
- L18 _public prototype_ `static FTextureShareSettings GetSettings();`
- L22 _public member_ `bool bCreateDefaults = true;` — Enable base textureshare object creation by default
- L25 _public member_ `FString ProcessName;` — Process name for this app

#### class `UTextureShareSettings`  
`class UTextureShareSettings : public UObject`  
_L32-57_
- reflection: `UCLASS(config = Engine, defaultconfig)`
- inherits: `UObject`
- desc: TextureShare plugin settings
- L37 _public prototype_ `UTextureShareSettings(const FObjectInitializer& ObjectInitializer);`
- L40 _public member_ `static const FName Container;`
- L41 _public member_ `static const FName Category;`
- L42 _public member_ `static const FName Section;`
- L46 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L52 _protected member_ `bool bCreateDefaults = true;` — `UPROPERTY(config, EditAnywhere, Category = Main, meta = (ToolTip = "Enable base textureshare object creation by default", ConfigRestartRequired = false))`
- L55 _protected member_ `FString ProcessName = UE::TextureShareCoreStrings::DefaultProcessName::UE;` — `UPROPERTY(config, EditAnywhere, Category = Main, meta = (ToolTip = "Process name for this app", ConfigRestartRequired = false))`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Game/ViewExtension/TextureShareSceneViewExtension.h` (Private)


#### struct `FTextureShareSceneView`  
`struct FTextureShareSceneView`  
_L20-33_
- desc: A container with a saved scene view for TS.
- L22 _public prototype_ `FTextureShareSceneView(const FSceneViewFamily& InViewFamily, const FSceneView& InSceneView, const FTextureShareSceneViewInfo& InViewInfo);`
- L25 _public member_ `int32 GPUIndex = -1;`
- L27 _public member_ `FIntRect UnconstrainedViewRect;`
- L28 _public member_ `FIntRect UnscaledViewRect;`
- L30 _public member_ `FTextureShareSceneViewInfo ViewInfo;`
- L32 _public member_ `const FSceneView& SceneView;`

#### class `FTextureShareSceneViewExtension`  
`class FTextureShareSceneViewExtension : public FSceneViewExtensionBase`  
_L38-98_
- inherits: `FSceneViewExtensionBase`
- desc: A view extension to handle a multi-threaded renderer for a TextureShare object.
- L42 _private function_ `virtual FName GetRTTI() const` — A quick and dirty way to determine which TS ViewExtension (sub)class this is. Every subclass should implement it.
- L45 _public prototype_ `FTextureShareSceneViewExtension(const FAutoRegister&, FViewport* InLinkedViewport);`
- L46 _public prototype_ `virtual ~FTextureShareSceneViewExtension();`
- L50 _public function_ `virtual int32 GetPriority() const override`
- L52 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L54 _public prototype_ `virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L55 _public prototype_ `virtual void PostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L57 _public prototype_ `virtual void OnResolvedSceneColor_RenderThread(FRDGBuilder& GraphBuilder, const FSceneTextures& SceneTextures) const;`
- L59 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L63 _public prototype_ `virtual void GetSceneViewData_RenderThread(const FTextureShareSceneView& InView, ITextureShareObjectProxy& ObjectProxy);`
- L64 _public prototype_ `virtual void ShareSceneViewColors_RenderThread(FRDGBuilder& GraphBuilder, const FSceneTextures& SceneTextures, const FTextureShareSceneView& InView) const;`
- L68 _public function_ `bool IsA(const FTextureShareSceneViewExtension&& Other) const` — Returns true if the given object is of the same type.
- L73 _public prototype_ `bool IsStereoRenderingAllowed() const;`
- L76 _public function_ `void Release_RenderThread()` — Marks this VE as unused.
- L82 _private prototype_ `void PreRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily);`
- L83 _private prototype_ `void PostRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily);`
- L86 _private prototype_ `bool IsEnabled_RenderThread() const;` — true, if this VE can be used.
- L90 _public member_ `FViewport* const LinkedViewport;` — Viewport to which we are attached
- L94 _protected member_ `TArray<FTextureShareSceneView> Views;` — Internal collection of used views
- L97 _protected member_ `bool bUseThisViewExtension = true;` — Is this VE used.

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Game/WorldSubsystem/TextureShareWorldSubsystem.h` (Private)


#### class `UTextureShareWorldSubsystem`  
`class UTextureShareWorldSubsystem : public UTickableWorldSubsystem`  
_L19-68_
- reflection: `UCLASS(BlueprintType, Transient)`
- inherits: `UTickableWorldSubsystem`
- desc: Tickable TextureShare World Subsystem used to handle tick and react to level and world changes.
- L24 _public prototype_ `UTextureShareWorldSubsystem();`
- L25 _public prototype_ `virtual ~UTextureShareWorldSubsystem();`
- L28 _public prototype_ `virtual void OnWorldBeginPlay(UWorld& InWorld) override;`
- L29 _public prototype_ `virtual void OnWorldEndPlay(UWorld& InWorld);`
- L33 _public function_ `virtual bool IsTickable() const override`
- L34 _public function_ `virtual bool IsTickableInEditor() const override`
- L35 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L36 _public prototype_ `virtual TStatId GetStatId() const override;`
- L41 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L42 _public prototype_ `virtual void Deinitialize() override;`
- L48 _public function_ `UTextureShare* GetTextureShare() const` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "TextureShareAPI"), Category = "TextureShare")` — Get textureshare API UObject
- L56 _public member_ `TObjectPtr<UTextureShare> TextureShare;` — `UPROPERTY(Transient)` — This UObject implements configuration and API
- L60 _private prototype_ `void Release();` — Release objects and resources
- L64 _private member_ `TSet<FString> NamesOfExistingObjects;` — Names of the created TextureShare objects
- L67 _private member_ `bool bWorldPlay = false;` — Handle logic OnWorldBeginPlay/OnWorldEndPlay

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Game/WorldSubsystem/TextureShareWorldSubsystemContext.h` (Private)


#### struct `FTextureShareWorldSubsystemContext`  
`struct FTextureShareWorldSubsystemContext : public ITextureShareWorldSubsystemContext`  
_L19-103_
- inherits: `ITextureShareWorldSubsystemContext`
- desc: Custom implementation of TextureShare context All ITextureShareCallbacks must be implemented here.
- L23 _public prototype_ `virtual ~FTextureShareWorldSubsystemContext() = default;`
- L25 _public prototype_ `virtual void RegisterTextureShareContextCallbacks() override;`
- L26 _public prototype_ `virtual void UnregisterTextureShareContextCallbacks() override;`
- L28 _public prototype_ `virtual void RegisterTextureShareContextCallbacks_RenderThread() override;`
- L29 _public prototype_ `virtual void UnregisterTextureShareContextCallbacks_RenderThread() override;`
- L38 _public prototype_ `void Tick( ITextureShareObject& Object, UTextureShareObject& TextureShareUObject, FViewport* InViewport);` — Implement tick for the TextureShare object. @param TextureShareObject  - (in) TS object to process @param TextureShareUObject - (in,out) TS UObject. @param Viewport            - the viewport that shared by TS
- L44 _public prototype_ `void GameViewportEndDraw_RenderThread(FRHICommandListImmediate& RHICmdList, const ITextureShareObjectProxy& ObjectProxy);` — Called on rendering thread, after viewfamily is rendered.
- L50 _protected prototype_ `void OnTextureShareBeginRenderViewFamily(FSceneViewFamily& ViewFamily, ITextureShareObject& Object);` — Called for each view family that are rendered in the frame.
- L53 _protected prototype_ `void OnTextureSharePreRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, const ITextureShareObjectProxy& ObjectProxy);` — Called from the FTextureShareSceneViewExtension in the rendering thread just before rendering starts.
- L56 _protected prototype_ `void OnTextureSharePostRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, const ITextureShareObjectProxy& ObjectProxy);` — Called from the FTextureShareSceneViewExtension in the rendering thread immediately after rendering completes.
- L59 _protected prototype_ `void OnTextureShareBackBufferReadyToPresent_RenderThread(SWindow& SlateWindow, const FTextureRHIRef& RHITexture, const ITextureShareObjectProxy& ObjectProxy);` — Called from the FTextureShareSceneViewExtension in the rendering thread just before present.
- L62 _protected prototype_ `void OnTextureShareGameViewportBeginDraw(ITextureShareObject& Object);` — GameViewport event onBeginDraw.
- L65 _protected prototype_ `void OnTextureShareGameViewportEndDraw(ITextureShareObject& Object);` — GameViewport event onEndDraw.
- L70 _private prototype_ `void Tick_GameThread(ITextureShareObject& TextureShareObject);` — Update TS object on the game thread.
- L73 _private prototype_ `bool ShouldUseBackbufferTexture(const ITextureShareObjectProxy& ObjectProxy) const;` — Returns true is backbuffer texture is shared.
- L78 _private prototype_ `void ShareResources_RenderThread(FRHICommandListImmediate& RHICmdList, const ITextureShareObjectProxy& ObjectProxy) const;` — Share resources of this context
- L82 _public member_ `TMap<FString, FTextureShareWorldSubsystemTextureProxy> Send;` — Named resources to send
- L85 _public member_ `TMap<FString, FTextureShareWorldSubsystemRenderTargetResourceProxy> Receive;` — Named Resources to receive
- L87 _public member_ `TObjectPtr<UTextureShareObject> TextureShareUObject;`
- L90 _public member_ `bool bRTCallbacksRegistered = false;` — Is rendering thread callbacks are registered.
- L93 _public member_ `bool bGameThreadCallbacksRegistered = false;` — Is Game thread callbacks are registered.
- L96 _public member_ `bool bGameThreadUpdated = false;` — The game thread logic has already been updated. This flag is true even if synchronization in the game thread fails.
- L99 _public member_ `bool bGameThreadSynchronized = false;` — Is the game thread synchronization a success
- L102 _public member_ `bool bRenderThreadFrameStarted = false;` — Is frame started on rendering thread

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Game/WorldSubsystem/TextureShareWorldSubsystemProxy.h` (Private)


#### struct `FTextureShareWorldSubsystemProxyBase`  
`struct FTextureShareWorldSubsystemProxyBase`  
_L13-26_
- desc: Proxy data base class.
- L16 _public prototype_ `bool IsRectValid() const;` — Is rect valid and can be used.
- L19 _public prototype_ `const FIntRect* GetRectIfDefined() const;` — Returns a pointer to the region if defined, or nullptr.
- L22 _public member_ `FTextureShareColorDesc ColorDesc;` — Color desc (gamma, etc)
- L25 _public member_ `FIntRect Rect = FIntRect(FIntPoint::ZeroValue, FIntPoint::ZeroValue);` — Region on texture

#### struct `FTextureShareWorldSubsystemTextureProxy`  
`struct FTextureShareWorldSubsystemTextureProxy : public FTextureShareWorldSubsystemProxyBase`  
_L29-39_
- inherits: `FTextureShareWorldSubsystemProxyBase`
- desc: Proxy data for textures.
- L32 _public prototype_ `FTextureShareWorldSubsystemTextureProxy(const FTextureShareSendTextureDesc& InSendTextureDesc);`
- L35 _public prototype_ `bool IsEnabled() const;` — Is this proxy can be used.
- L38 _public member_ `FTextureResource* Texture = nullptr;` — Texture resource

#### struct `FTextureShareWorldSubsystemRenderTargetResourceProxy`  
`struct FTextureShareWorldSubsystemRenderTargetResourceProxy : public FTextureShareWorldSubsystemProxyBase`  
_L42-52_
- inherits: `FTextureShareWorldSubsystemProxyBase`
- desc: Proxy data for RTT.
- L45 _public prototype_ `FTextureShareWorldSubsystemRenderTargetResourceProxy(const FTextureShareReceiveTextureDesc& InReceiveTextureDesc);`
- L48 _public prototype_ `bool IsEnabled() const;` — Is this proxy can be used.
- L51 _public member_ `FTextureRenderTargetResource* RenderTarget = nullptr;` — RTT resource

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/ITextureShareAPI.h` (Private)


#### class `ITextureShareAPI`  
`class ITextureShareAPI`  
_L17-163_
- desc: TextureShare API
- L20 _public prototype_ `virtual ~ITextureShareAPI() = default;`
- L30 _public prototype_ `virtual void OnWorldBeginPlay(UWorld& InWorld) = 0;` — Handle BeginPlay event @param InWorld - world @return - none
- L39 _public prototype_ `virtual void OnWorldEndPlay(UWorld& InWorld) = 0;` — Handle EndPlay event @param InWorld - world @return - none
- L49 _public prototype_ `virtual TSharedPtr<ITextureShareObject, ESPMode::ThreadSafe> GetOrCreateObject(const FString& ShareName, const ETextureShareProcessType InProcessType = ETextureShareProcessType::Undefined) = 0;` — Get or create new TextureShare object @param ShareName - Unique share name (case insensitive) @return - Ptr to TextureShare object
- L58 _public prototype_ `virtual bool RemoveObject(const FString& ShareName) = 0;` — Remove TextureShare object @param ShareName - Unique share name (case insensitive) @return True if the success
- L67 _public prototype_ `virtual bool IsObjectExist(const FString& ShareName) const = 0;` — The test for the TextureShare object with the specified name still exists. @param ShareName - Unique share name (case insensitive) @return - true, if object with the specified name still exists.
- L77 _public prototype_ `virtual TSharedPtr<ITextureShareObject, ESPMode::ThreadSafe> GetObject(const FString& ShareName) const = 0;` — Get TextureShare object @param ShareName - Unique share name (case insensitive) @return - Ptr to TextureShare object
- L86 _public prototype_ `virtual TSharedPtr<ITextureShareObjectProxy, ESPMode::ThreadSafe> GetObjectProxy_RenderThread(const FString& ShareName) const = 0;` — Get TextureShare proxy object @param ShareName - Unique share name (case insensitive) @return - Ptr to TextureShare proxy object
- L95 _public prototype_ `virtual TSharedPtr<ITextureShareObject, ESPMode::ThreadSafe> GetObject(const TSharedRef<const FSceneViewExtensionBase, ESPMode::ThreadSafe>& InViewExtension) const = 0;` — Get TextureShare object @param InViewExtension - View extension that used by TextureShare object. @return - Ptr to TextureShare object
- L104 _public prototype_ `virtual TSharedPtr<ITextureShareObjectProxy, ESPMode::ThreadSafe> GetObjectProxy_RenderThread(const TSharedRef<const FSceneViewExtensionBase, ESPMode::ThreadSafe>& InViewExtension) const = 0;` — Get TextureShare proxy object @param InViewExtension - View extension that used by TextureShare proxy object. @return - Ptr to TextureShare proxy object
- L115 _public prototype_ `virtual bool GetInterprocessObjects(const FString& InShareName, TArray<struct FTextureShareCoreObjectDesc>& OutInterprocessObjects) const = 0;` — Returns a list of handles to interprocess TextureShare objects with the specified name. @param InShareName            - (optional) name of the TextureShare object @param OutInterprocessObjects - Output array with handles to TextureShare objects @return true, if success
- L120 _public prototype_ `virtual const struct FTextureShareCoreObjectProcessDesc& GetProcessDesc() const = 0;` — Returns detailed information about the local process
- L127 _public prototype_ `virtual void SetProcessName(const FString& InProcessId) = 0;` — Assign a unique name to the local process. The changes only affect newly created TextureShare objects. @param InProcessId - Custom local process name
- L135 _public prototype_ `virtual ITextureShareCallbacks& GetCallbacks() = 0;` — Access to the TextureShare callbacks API @return Callbacks API
- L146 _public function_ `virtual void DisableWorldSubsystem(const uint8* InObject)` — `UE_DEPRECATED(5.6, "This function has been deprecated. Use the ITextureShareContext class to separate different implementations.")` — Disable the multi-object world subsystem. This disabled state will persist until the EnableWorldSubsystem() pair function is called on all objects. @param InObject - external object @return none
- L156 _public function_ `virtual void EnableWorldSubsystem(const uint8* InObject)` — `UE_DEPRECATED(5.6, "This function has been deprecated. Use the ITextureShareContext class to separate different implementations.")` — Enable WorldSubsystem. @param InObject - external object @return none
- L162 _public function_ `virtual bool IsWorldSubsystemEnabled() const` — `UE_DEPRECATED(5.6, "This function has been deprecated. Use the ITextureShareContext class to separate different implementations.")` — Return true if WorldSubsystem.can by used

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/ITextureShareCallbacks.h` (Private)


#### class `ITextureShareCallbacks`  
`class ITextureShareCallbacks`  
_L44-134_
- desc: TextureShare callbacks API: The same callbacks can be used by multiple implementations, and all of them will be invoked by broadcast calls for each TS object. This will cause a single TS object to be consistently called by all callbacks of the same type from all existing implementations. To avoid this situation, we must filter the TS objects within each callback by implementation type. Each custom implementation must create a new user context class based on the ITextureShareContext class. Each implementation must then assign this new context to all TS objects it owns using the ITextureShareObject::SetTextureShareContext() function. Within each callback, the context of the TS object must be checked for the implementation type. The context of a TextureShare object can be retrieved using one of two functions: ITextureShareObject::GetTextureShareContext() and ITextureShareObject::GetTextureShareContext_RenderThread() The context class can be checked using the ITextureShareContext::IsA() function. Game thread callbacks must be registered and unregistered using these two overridden functions: ITextureShareContext::RegisterTextureShareContextCallbacks() and ITextureShareContext::UnregisterTextureShareContextCallbacks(). Rendering thread callbacks must be registered and unregistered using these two overridden functions: ITextureShareContext::RegisterTextureShareContextCallbacks_RenderThread() and ITextureShareContext::UnregisterTextureShareContextCallbacks_RenderThread().
- L47 _public prototype_ `static ITextureShareCallbacks& Get();`
- L49 _public prototype_ `virtual ~ITextureShareCallbacks() = default;`
- L56 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareGameViewportBeginDrawEvent, ITextureShareObject&);` — This is a subscription to the UGameViewportClient::OnBeginDraw() callback. Accessor for the delegate called when the engine starts drawing a game viewport
- L57 _public prototype_ `virtual FTextureShareGameViewportBeginDrawEvent& OnTextureShareGameViewportBeginDraw() = 0;`
- L63 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareGameViewportDrawEvent, ITextureShareObject&);` — This is a subscription to the UGameViewportClient::OnDraw() callback. Accessor for the delegate called when the game viewport is drawn, before drawing the console
- L64 _public prototype_ `virtual FTextureShareGameViewportDrawEvent& OnTextureShareGameViewportDraw() = 0;`
- L70 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareGameViewportEndDrawEvent, ITextureShareObject&);` — This is a subscription to the UGameViewportClient::OnEndDraw() callback. Accessor for the delegate called when the engine finishes drawing a game viewport
- L71 _public prototype_ `virtual FTextureShareGameViewportEndDrawEvent& OnTextureShareGameViewportEndDraw() = 0;`
- L75 _public prototype_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureShareBeginRenderViewFamilyEvent, FSceneViewFamily&, ITextureShareObject&);` — Called on begin frame sync
- L76 _public prototype_ `virtual FTextureShareBeginRenderViewFamilyEvent& OnTextureShareBeginRenderViewFamily() = 0;`
- L79 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareBeginSessionEvent, ITextureShareObject&);` — Called on session start
- L80 _public prototype_ `virtual FTextureShareBeginSessionEvent& OnTextureShareBeginSession() = 0;`
- L83 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareEndSessionEvent, ITextureShareObject&);` — Called on session end
- L84 _public prototype_ `virtual FTextureShareEndSessionEvent& OnTextureShareEndSession() = 0;`
- L87 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureSharePreBeginFrameSyncEvent, ITextureShareObject&);` — Called on begin frame sync
- L88 _public prototype_ `virtual FTextureSharePreBeginFrameSyncEvent& OnTextureSharePreBeginFrameSync() = 0;`
- L91 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareBeginFrameSyncEvent, ITextureShareObject&);` — Called on begin frame sync
- L92 _public prototype_ `virtual FTextureShareBeginFrameSyncEvent& OnTextureShareBeginFrameSync() = 0;`
- L95 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareEndFrameSyncEvent, ITextureShareObject&);` — Called on end frame sync
- L96 _public prototype_ `virtual FTextureShareEndFrameSyncEvent& OnTextureShareEndFrameSync() = 0;`
- L99 _public prototype_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureShareFrameSyncEvent, ITextureShareObject&, const ETextureShareSyncStep);` — Called on frame sync
- L100 _public prototype_ `virtual FTextureShareFrameSyncEvent& OnTextureShareFrameSync() = 0;`
- L108 _public prototype_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureSharePreBeginFrameSyncEvent_RenderThread, FRHICommandListImmediate&, const ITextureShareObjectProxy&);` — This is a redirected event from the game thread, just before frame synchronization. If game stream synchronization fails, the proxy context remains from the previous frame. This callback is useful for preparing context and other data for the new frame.
- L109 _public prototype_ `virtual FTextureSharePreBeginFrameSyncEvent_RenderThread& OnTextureSharePreBeginFrameSync_RenderThread() = 0;`
- L112 _public prototype_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureShareBeginFrameSyncEvent_RenderThread, FRHICommandListImmediate&, const ITextureShareObjectProxy&);` — Called on begin frame sync on render thread
- L113 _public prototype_ `virtual FTextureShareBeginFrameSyncEvent_RenderThread& OnTextureShareBeginFrameSync_RenderThread() = 0;`
- L116 _public prototype_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureShareEndFrameSyncEvent_RenderThread, FRHICommandListImmediate&, const ITextureShareObjectProxy&);` — Called on end frame sync on render thread
- L117 _public prototype_ `virtual FTextureShareEndFrameSyncEvent_RenderThread& OnTextureShareEndFrameSync_RenderThread() = 0;`
- L120 _public prototype_ `DECLARE_EVENT_ThreeParams(ITextureShareCallbacks, FTextureShareFrameSyncEvent_RenderThread, FRHICommandListImmediate&, const ITextureShareObjectProxy&, const ETextureShareSyncStep);` — Called on frame sync on render thread
- L121 _public prototype_ `virtual FTextureShareFrameSyncEvent_RenderThread& OnTextureShareFrameSync_RenderThread() = 0;`
- L124 _public prototype_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureSharePreRenderViewFamily_RenderThread, FRHICommandListImmediate&, const ITextureShareObjectProxy&);` — Called from the FTextureShareSceneViewExtension in the rendering thread just before rendering starts.
- L125 _public prototype_ `virtual FTextureSharePreRenderViewFamily_RenderThread& OnTextureSharePreRenderViewFamily_RenderThread() = 0;`
- L128 _public prototype_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureSharePostRenderViewFamily_RenderThread, FRHICommandListImmediate&, const ITextureShareObjectProxy&);` — Called from the FTextureShareSceneViewExtension in the rendering thread immediately after rendering completes.
- L129 _public prototype_ `virtual FTextureSharePostRenderViewFamily_RenderThread& OnTextureSharePostRenderViewFamily_RenderThread() = 0;`
- L132 _public prototype_ `DECLARE_EVENT_ThreeParams(ITextureShareCallbacks, FTextureShareBackBufferReadyToPresentEvent_RenderThread, SWindow&, const FTextureRHIRef&, const ITextureShareObjectProxy&);` — Called from the FTextureShareSceneViewExtension in the rendering thread just before present.
- L133 _public prototype_ `virtual FTextureShareBackBufferReadyToPresentEvent_RenderThread& OnTextureShareBackBufferReadyToPresent_RenderThread() = 0;`

#### Free symbols / members of external scopes

- L56 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareGameViewportBeginDrawEvent, ITextureShareObject&);` — This is a subscription to the UGameViewportClient::OnBeginDraw() callback. Accessor for the delegate called when the engine starts drawing a game viewport
- L63 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareGameViewportDrawEvent, ITextureShareObject&);` — This is a subscription to the UGameViewportClient::OnDraw() callback. Accessor for the delegate called when the game viewport is drawn, before drawing the console
- L70 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareGameViewportEndDrawEvent, ITextureShareObject&);` — This is a subscription to the UGameViewportClient::OnEndDraw() callback. Accessor for the delegate called when the engine finishes drawing a game viewport
- L75 _delegate_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureShareBeginRenderViewFamilyEvent, FSceneViewFamily&, ITextureShareObject&);` — Called on begin frame sync
- L79 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareBeginSessionEvent, ITextureShareObject&);` — Called on session start
- L83 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareEndSessionEvent, ITextureShareObject&);` — Called on session end
- L87 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureSharePreBeginFrameSyncEvent, ITextureShareObject&);` — Called on begin frame sync
- L91 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareBeginFrameSyncEvent, ITextureShareObject&);` — Called on begin frame sync
- L95 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCallbacks, FTextureShareEndFrameSyncEvent, ITextureShareObject&);` — Called on end frame sync
- L99 _delegate_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureShareFrameSyncEvent, ITextureShareObject&, const ETextureShareSyncStep);` — Called on frame sync
- L108 _delegate_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureSharePreBeginFrameSyncEvent_RenderThread, FRHICommandListImmediate&, const ITextureShareObjectProxy&);` — This is a redirected event from the game thread, just before frame synchronization. If game stream synchronization fails, the proxy context remains from the previous frame. This callback is useful for preparing context and other data for the new frame.
- L112 _delegate_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureShareBeginFrameSyncEvent_RenderThread, FRHICommandListImmediate&, const ITextureShareObjectProxy&);` — Called on begin frame sync on render thread
- L116 _delegate_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureShareEndFrameSyncEvent_RenderThread, FRHICommandListImmediate&, const ITextureShareObjectProxy&);` — Called on end frame sync on render thread
- L120 _delegate_ `DECLARE_EVENT_ThreeParams(ITextureShareCallbacks, FTextureShareFrameSyncEvent_RenderThread, FRHICommandListImmediate&, const ITextureShareObjectProxy&, const ETextureShareSyncStep);` — Called on frame sync on render thread
- L124 _delegate_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureSharePreRenderViewFamily_RenderThread, FRHICommandListImmediate&, const ITextureShareObjectProxy&);` — Called from the FTextureShareSceneViewExtension in the rendering thread just before rendering starts.
- L128 _delegate_ `DECLARE_EVENT_TwoParams(ITextureShareCallbacks, FTextureSharePostRenderViewFamily_RenderThread, FRHICommandListImmediate&, const ITextureShareObjectProxy&);` — Called from the FTextureShareSceneViewExtension in the rendering thread immediately after rendering completes.
- L132 _delegate_ `DECLARE_EVENT_ThreeParams(ITextureShareCallbacks, FTextureShareBackBufferReadyToPresentEvent_RenderThread, SWindow&, const FTextureRHIRef&, const ITextureShareObjectProxy&);` — Called from the FTextureShareSceneViewExtension in the rendering thread just before present.

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/ITextureShareObject.h` (Private)


#### class `ITextureShareObject`  
`class ITextureShareObject`  
_L13-188_
- desc: TextureShare object interface (GameThread)
- L16 _public prototype_ `virtual ~ITextureShareObject() = default;`
- L28 _public prototype_ `virtual void SetTextureShareContext(const TSharedPtr<ITextureShareContext, ESPMode::ThreadSafe>& InTextureShareContext) = 0;` — Assign new context data for this TS object on game thread Every frame in the game thread we have to create a new context and populate it with new data. Then set it using the ITextureShareObject::SetTextureShareContext() function. This context is passed from the game thread to the rendering thread. (from the ITextureShareObject to the ITextureShareObjectProxy) With this approach, we get unique context data for both threads.
- L31 _public prototype_ `virtual const ITextureShareContext* GetTextureShareContext() const = 0;` — Returns a pointer to the assigned context.
- L39 _public prototype_ `virtual const FString& GetName() const = 0;` — Return the name of the TextureShare.
- L44 _public prototype_ `virtual FTextureShareCoreObjectDesc GetObjectDesc() const = 0;` — Returns detailed information about the TextureShare object.
- L49 _public prototype_ `virtual bool IsActive() const = 0;` — Returns true if the TextureShare object is ready to be used.
- L54 _public prototype_ `virtual bool IsFrameSyncActive() const = 0;` — Returns true if the TextureShareCore object has started a session and processes are connected for this frame.
- L67 _public prototype_ `virtual bool SetProcessId(const FString& InProcessId) = 0;` — Change the process name for this TextureShare object. If the object is synced now, then the changes are deferred and executed in the next frame. @param InProcessId - New process name @return true, if success
- L77 _public prototype_ `virtual bool SetSyncSetting(const FTextureShareCoreSyncSettings& InSyncSetting) = 0;` — Change the sync settings for this TextureShare object. If the object is synced now, then the changes are deferred and executed in the next frame. @param InSyncSetting - New sync settings @return true, if success
- L82 _public prototype_ `virtual FTextureShareCoreSyncSettings GetSyncSetting() const = 0;` — Return the sync settings of the TextureShare.
- L92 _public prototype_ `virtual FTextureShareCoreFrameSyncSettings GetFrameSyncSettings(const ETextureShareFrameSyncTemplate InType) const = 0;` — Get TextureShare default sync settings by template type The settings of this template are not related to the current settings of the object @param InType - Sync settings template type @return structure with sync logic settings
- L104 _public prototype_ `virtual bool BeginSession(class FViewport* InViewport = nullptr) = 0;` — Start a TextureShare session for the specified viewport @param InViewport - (opt) ptr on rendering viewport @return True if the success
- L111 _public prototype_ `virtual bool EndSession() = 0;` — End the TextureShare session and the resources in use are also removed. @return True if the success
- L116 _public prototype_ `virtual bool IsSessionActive() const = 0;` — Returns true if the session is currently valid
- L128 _public prototype_ `virtual bool BeginFrameSync() = 0;` — Begin sync logic in range FrameBegin..FrameEnd The list of connected processes for the current frame will also be updated. Returns true if the frame is connected to other processes that match the synchronization settings. Game and render thread are in sync
- L139 _public prototype_ `virtual bool FrameSync(const ETextureShareSyncStep InSyncStep) = 0;` — Synchronize connected processes that support this sync step Data from remote processes will be read at the time the barrier is synchronized. Missed sync steps from the sync settings will also be called. @param InSyncStep - Sync step value @return True if the success
- L147 _public prototype_ `virtual bool EndFrameSync() = 0;` — Finalize sync logic in range FrameBegin..FrameEnd Missed sync steps from the sync settings will also be called. Game and render thread are in sync
- L156 _public prototype_ `virtual TArray<FTextureShareCoreObjectDesc> GetConnectedInterprocessObjects() const = 0;` — Returns a list of handles to the interprocess TextureShare objects that are currently connected to this object. @param OutInterprocessObjects - Output array with handles to TextureShare objects @return true, if success
- L165 _public prototype_ `virtual FTextureShareCoreData& GetCoreData() = 0;` — Reference to Data. Object data for the current frame in the GameThread.
- L166 _public prototype_ `virtual const FTextureShareCoreData& GetCoreData() const = 0;`
- L171 _public prototype_ `virtual TArray<FTextureShareCoreObjectData> GetReceivedCoreObjectData() const = 0;` — Received Data from connected process objects
- L176 _public prototype_ `virtual FTextureShareData& GetData() = 0;` — Reference to views data
- L181 _public prototype_ `virtual TSharedPtr<class FTextureShareSceneViewExtension, ESPMode::ThreadSafe> GetViewExtension() const = 0;` — Reference to to view extension
- L187 _public prototype_ `virtual TSharedRef<class ITextureShareObjectProxy, ESPMode::ThreadSafe> GetProxy() const = 0;` — Return proxy interface

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/ITextureShareObjectProxy.h` (Private)


#### class `ITextureShareObjectProxy`  
`class ITextureShareObjectProxy`  
_L18-272_
- desc: TextureShare object proxy interface (RenderingThread)
- L21 _public prototype_ `virtual ~ITextureShareObjectProxy() = default;`
- L25 _public prototype_ `virtual const ITextureShareContext* GetTextureShareContext_RenderThread() const = 0;` — Returns a pointer to the assigned context on rendering thread.
- L33 _public prototype_ `virtual const FString& GetName_RenderThread() const = 0;` — Return the name of the TextureShare.
- L38 _public prototype_ `virtual FTextureShareCoreObjectDesc GetObjectDesc_RenderThread() const = 0;` — Returns detailed information about the TextureShare object.
- L43 _public prototype_ `virtual bool IsActive_RenderThread() const = 0;` — Returns true if the TextureShare object is ready to be used.
- L48 _public prototype_ `virtual bool IsFrameSyncActive_RenderThread() const = 0;` — Returns true if the TextureShare object has started a session and processes are connected for this frame.
- L57 _public prototype_ `virtual bool BeginFrameSync_RenderThread(FRHICommandListImmediate& RHICmdList) const = 0;` — Begin sync logic in range FrameProxyBegin..FrameProxyEnd Game and render thread are in sync
- L68 _public prototype_ `virtual bool FrameSync_RenderThread(FRHICommandListImmediate& RHICmdList, const ETextureShareSyncStep InSyncStep) const = 0;` — Synchronize connected processes that support this sync step ProxyData from remote processes will be read at the time the barrier is synchronized. Missed sync steps from the sync settings will also be called. @param InSyncStep - Sync step value @return True if the success
- L75 _public prototype_ `virtual bool EndFrameSync_RenderThread(FRHICommandListImmediate& RHICmdList) const = 0;` — Finalize sync logic in range FrameProxyBegin..FrameProxyEnd Missed sync steps from the sync settings will also be called. Game and render thread are in sync
- L92 _public prototype_ `virtual bool ShareResource_RenderThread( FRHICommandListImmediate& RHICmdList, const FTextureShareCoreResourceDesc& InResourceDesc, FRHITexture* InTexture, const FTextureShareColorDesc& InTextureColorDesc, const int32 InTextureGPUIndex, const FIntRect* InTextureRect = nullptr) const = 0;` — Share texture resource with ResourceRequest @param RHICmdList        - RHI cmd list @param InResourceDesc    - resource information @param InTexture         - Texture RHI resource @param InTextureColor    - InTexture color desc @param InTextureGPUIndex - Texture GPU index @param InTextureRect     - (optional) Share only region from InTexture @return True if the success
- L112 _public prototype_ `virtual bool ShareResource_RenderThread( FRDGBuilder& GraphBuilder, const FTextureShareCoreResourceDesc& InResourceDesc, const FRDGTextureRef& InTextureRef, const FTextureShareColorDesc& InTextureColorDesc, const int32 InTextureGPUIndex, const FIntRect* InTextureRect = nullptr) const = 0;` — Share texture resource with ResourceRequest @param GraphBuilder      - RDG builder @param InResourceDesc    - resource information @param InTextureRef      - RDG Texture ref @param InTextureColor    - InTextureRef color desc @param InTextureGPUIndex - Texture GPU index @param InTextureRect     - (optional) Share only region from InTexture @return True if the success
- L132 _public prototype_ `virtual bool ShareResource_RenderThread( FRHICommandListImmediate& RHICmdList, const FTextureShareCoreResourceRequest& InResourceRequest, FRHITexture* InTexture, const FTextureShareColorDesc& InTextureColorDesc, const int32 InTextureGPUIndex, const FIntRect* InTextureRect = nullptr) const = 0;` — Share texture resource with ResourceRequest @param RHICmdList        - RHI cmd list @param InResourceRequest - resource information @param InTexture         - Texture RHI resource @param InTextureColor    - InTexture color desc @param InTextureGPUIndex - Texture GPU index @param InTextureRect     - (optional) Share only region from InTexture @return True if the success
- L152 _public prototype_ `virtual bool ShareRenderTargetResource_RenderThread( FRHICommandListImmediate& RHICmdList, const FTextureShareCoreResourceRequest& InResourceRequest, FTextureRenderTargetResource* InRenderTargetResource, const FTextureShareColorDesc& InRenderTargetColorDesc, const int32 InRenderTargetGPUIndex, const FIntRect* InRenderTargetRect = nullptr) const = 0;` — Share texture RTT with ResourceRequest @param RHICmdList             - RHI cmd list @param InResourceRequest      - resource information @param InRenderTargetResource - Texture Render Target RHI resource @param InRenderTargetColor    - Texture RTT color desc @param InRenderTargetGPUIndex - Texture RTT GPU index @param InRenderTargetRect     - (optional) Share only region from Texture RTT @return True if the success
- L172 _public prototype_ `virtual bool ShareResource_RenderThread( FRDGBuilder& GraphBuilder, const FTextureShareCoreResourceRequest& InResourceRequest, const FRDGTextureRef& InTextureRef, const FTextureShareColorDesc& InTextureColorDesc, const int32 InTextureGPUIndex, const FIntRect* InTextureRect = nullptr) const = 0;` — Share texture resource with ResourceRequest @param GraphBuilder      - RDG builder @param InResourceRequest - resource information @param InTextureRef      - RDG Texture ref @param InTextureColor    - InTextureRef color desc @param InTextureGPUIndex - Texture GPU index @param InTextureRect     - (optional) Share only region from InTexture @return True if the success
- L187 _public prototype_ `virtual FTextureShareCoreProxyData& GetCoreProxyData_RenderThread() = 0;` — Reference to ProxyData. Object proxy data for the current frame in the RenderThread.
- L188 _public prototype_ `virtual const FTextureShareCoreProxyData& GetCoreProxyData_RenderThread() const = 0;`
- L193 _public prototype_ `virtual TArray<FTextureShareCoreObjectProxyData> GetReceivedCoreObjectProxyData_RenderThread() const = 0;` — Received ProxyData from connected process objects
- L198 _public prototype_ `virtual ETextureShareObjectProxyFlags GetObjectProxyFlags() const = 0;` — Return proxy flags
- L203 _public prototype_ `virtual void SetObjectProxyFlags(const ETextureShareObjectProxyFlags InFlags) = 0;` — Set new proxy flags
- L208 _public prototype_ `virtual const FTextureShareData& GetData_RenderThread() const = 0;` — Get data from game thread
- L213 _public prototype_ `virtual const TSharedPtr<FTextureShareSceneViewExtension, ESPMode::ThreadSafe>& GetViewExtension_RenderThread() const = 0;` — Get view extension ptr
- L228 _public function_ `virtual bool ShareResource_RenderThread(FRHICommandListImmediate& RHICmdList, const FTextureShareCoreResourceDesc& InResourceDesc, FRHITexture* InTexture, const int32 InTextureGPUIndex, const FIntRect* InTextureRect = nullptr) const` — `UE_DEPRECATED(5.6, "This function has been deprecated. Use the new function with other arguments. ")` — Share texture resource with ResourceRequest @param RHICmdList        - RHI cmd list @param InResourceDesc    - resource information @param InTexture         - Texture RHI resource @param InTextureGPUIndex - Texture GPU index @param InTextureRect     - (optional) Share only region from InTexture @return True if the success
- L242 _public function_ `virtual bool ShareResource_RenderThread(FRDGBuilder& GraphBuilder, const FTextureShareCoreResourceDesc& InResourceDesc, const FRDGTextureRef& InTextureRef, const int32 InTextureGPUIndex, const FIntRect* InTextureRect = nullptr) const` — `UE_DEPRECATED(5.6, "This function has been deprecated. Use the new function with other arguments. ")` — Share texture resource with ResourceRequest @param GraphBuilder      - RDG builder @param InResourceDesc    - resource information @param InTextureRef      - RDG Texture ref @param InTextureGPUIndex - Texture GPU index @param InTextureRect     - (optional) Share only region from InTexture @return True if the success
- L256 _public function_ `virtual bool ShareResource_RenderThread(FRHICommandListImmediate& RHICmdList, const FTextureShareCoreResourceRequest& InResourceRequest, FRHITexture* InTexture, const int32 InTextureGPUIndex, const FIntRect* InTextureRect = nullptr) const` — `UE_DEPRECATED(5.6, "This function has been deprecated. Use the new function with other arguments. ")` — Share texture resource with ResourceRequest @param RHICmdList        - RHI cmd list @param InResourceRequest - resource information @param InTexture         - Texture RHI resource @param InTextureGPUIndex - Texture GPU index @param InTextureRect     - (optional) Share only region from InTexture @return True if the success
- L270 _public function_ `virtual bool ShareResource_RenderThread(FRDGBuilder& GraphBuilder, const FTextureShareCoreResourceRequest& InResourceRequest, const FRDGTextureRef& InTextureRef, const int32 InTextureGPUIndex, const FIntRect* InTextureRect = nullptr) const` — `UE_DEPRECATED(5.6, "This function has been deprecated. Use the new function with other arguments. ")` — Share texture resource with ResourceRequest @param GraphBuilder      - RDG builder @param InResourceRequest - resource information @param InTextureRef      - RDG Texture ref @param InTextureGPUIndex - Texture GPU index @param InTextureRect     - (optional) Share only region from InTexture @return True if the success

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Misc/TextureShareStrings.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TextureShareStrings` (scope `UE`)
- L13 _namespace_ `namespace SceneTextures` (scope `UE::TextureShareStrings`)
- L16 _variable_ `static constexpr auto SceneColor = TEXT("Sce` (scope `UE::TextureShareStrings::SceneTextures`) — Read-only scene resources
- L17 _variable_ `static constexpr auto SceneDepth = TEXT("Sce` (scope `UE::TextureShareStrings::SceneTextures`)
- L18 _variable_ `static constexpr auto SmallDepthZ = TEXT("Sma` (scope `UE::TextureShareStrings::SceneTextures`)
- L19 _variable_ `static constexpr auto GBufferA = TEXT("GBu` (scope `UE::TextureShareStrings::SceneTextures`)
- L20 _variable_ `static constexpr auto GBufferB = TEXT("GBu` (scope `UE::TextureShareStrings::SceneTextures`)
- L21 _variable_ `static constexpr auto GBufferC = TEXT("GBu` (scope `UE::TextureShareStrings::SceneTextures`)
- L22 _variable_ `static constexpr auto GBufferD = TEXT("GBu` (scope `UE::TextureShareStrings::SceneTextures`)
- L23 _variable_ `static constexpr auto GBufferE = TEXT("GBu` (scope `UE::TextureShareStrings::SceneTextures`)
- L24 _variable_ `static constexpr auto GBufferF = TEXT("GBu` (scope `UE::TextureShareStrings::SceneTextures`)
- L27 _variable_ `static constexpr auto FinalColor = TEXT("Fin` (scope `UE::TextureShareStrings::SceneTextures`) — Read-write RTTs
- L28 _variable_ `static constexpr auto Backbuffer = TEXT("Bac` (scope `UE::TextureShareStrings::SceneTextures`)

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Module/TextureShareAPI.h` (Private)


#### class `FTextureShareAPI`  
`class FTextureShareAPI : public ITextureShareAPI`  
_L17-95_
- inherits: `ITextureShareAPI`
- desc: TextureShare API impl
- L21 _public prototype_ `FTextureShareAPI();`
- L22 _public prototype_ `virtual ~FTextureShareAPI();`
- L26 _public prototype_ `virtual TSharedPtr<ITextureShareObject, ESPMode::ThreadSafe> GetOrCreateObject(const FString& ShareName, const ETextureShareProcessType InProcessType = ETextureShareProcessType::Undefined) override;`
- L27 _public prototype_ `virtual bool RemoveObject(const FString& ShareName) override;`
- L28 _public prototype_ `virtual bool IsObjectExist(const FString& ShareName) const override;`
- L30 _public prototype_ `virtual TSharedPtr<ITextureShareObject, ESPMode::ThreadSafe> GetObject(const FString& ShareName) const override;`
- L31 _public prototype_ `virtual TSharedPtr<ITextureShareObjectProxy, ESPMode::ThreadSafe> GetObjectProxy_RenderThread(const FString& ShareName) const override;`
- L33 _public prototype_ `virtual TSharedPtr<ITextureShareObject, ESPMode::ThreadSafe> GetObject(const TSharedRef<const FSceneViewExtensionBase, ESPMode::ThreadSafe>& InViewExtension) const override;`
- L34 _public prototype_ `virtual TSharedPtr<ITextureShareObjectProxy, ESPMode::ThreadSafe> GetObjectProxy_RenderThread(const TSharedRef<const FSceneViewExtensionBase, ESPMode::ThreadSafe>& InViewExtension) const override;`
- L37 _public prototype_ `virtual bool GetInterprocessObjects(const FString& InShareName, TArray<struct FTextureShareCoreObjectDesc>& OutInterprocessObjects) const override;`
- L39 _public prototype_ `virtual const struct FTextureShareCoreObjectProcessDesc& GetProcessDesc() const override;`
- L40 _public prototype_ `virtual void SetProcessName(const FString& InProcessId) override;`
- L42 _public prototype_ `virtual void OnWorldBeginPlay(UWorld& InWorld) override;`
- L43 _public prototype_ `virtual void OnWorldEndPlay(UWorld& InWorld) override;`
- L45 _public function_ `virtual ITextureShareCallbacks& GetCallbacks() override`
- L55 _private prototype_ `void RemoveTextureShareObjectInstances();`
- L59 _private prototype_ `void OnResolvedSceneColor_RenderThread(FRDGBuilder& GraphBuilder, const FSceneTextures& SceneTextures);` — Rendered callback (get scene textures to share)
- L62 _private prototype_ `void OnBackBufferReadyToPresent_RenderThread(SWindow& Window, ISlateViewportProvider& ViewportProvider);` — Slate app callback before present to share app backbuffer
- L65 _private prototype_ `void OnGameViewportBeginDraw();` — GameViewport event onBeginDraw.
- L68 _private prototype_ `void OnGameViewportDraw();` — GameViewport event onDraw.
- L71 _private prototype_ `void OnGameViewportEndDraw();` — GameViewport event onEndDraw.
- L73 _private prototype_ `void RegisterRendererModuleCallbacks();`
- L74 _private prototype_ `void UnregisterRendererModuleCallbacks();`
- L77 _private prototype_ `void RegisterSettings_Editor();`
- L78 _private prototype_ `void UnregisterSettings_Editor();`
- L82 _private member_ `TMap<FString, TSharedPtr<FTextureShareObject, ESPMode::ThreadSafe>> Objects;`
- L83 _private member_ `TMap<FString, TSharedPtr<FTextureShareObjectProxy, ESPMode::ThreadSafe>> ObjectProxies;`
- L85 _private member_ `FDelegateHandle ResolvedSceneColorCallbackHandle;`
- L86 _private member_ `FDelegateHandle OnBackBufferReadyToPresentHandle;`
- L88 _private member_ `FDelegateHandle OnGameViewportBeginDrawHandle;`
- L89 _private member_ `FDelegateHandle OnGameViewportDrawHandle;`
- L90 _private member_ `FDelegateHandle OnGameViewportEndDrawHandle;`
- L92 _private member_ `mutable FCriticalSection ThreadDataCS;`
- L94 _private member_ `FTextureShareCallbacks Callbacks;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Module/TextureShareCallbacks.h` (Private)


#### class `FTextureShareCallbacks`  
`class FTextureShareCallbacks : public ITextureShareCallbacks`  
_L10-128_
- inherits: `ITextureShareCallbacks`
- desc: TextureShare callbacks API implementation
- L14 _public prototype_ `virtual ~FTextureShareCallbacks() = default;`
- L17 _public function_ `virtual FTextureShareGameViewportBeginDrawEvent& OnTextureShareGameViewportBeginDraw() override`
- L22 _public function_ `virtual FTextureShareGameViewportDrawEvent& OnTextureShareGameViewportDraw() override`
- L27 _public function_ `virtual FTextureShareGameViewportEndDrawEvent& OnTextureShareGameViewportEndDraw() override`
- L32 _public function_ `virtual FTextureShareBeginRenderViewFamilyEvent& OnTextureShareBeginRenderViewFamily() override`
- L37 _public function_ `virtual FTextureShareBeginSessionEvent& OnTextureShareBeginSession() override`
- L42 _public function_ `virtual FTextureShareEndSessionEvent& OnTextureShareEndSession() override`
- L48 _public function_ `virtual FTextureSharePreBeginFrameSyncEvent& OnTextureSharePreBeginFrameSync() override`
- L53 _public function_ `virtual FTextureShareBeginFrameSyncEvent& OnTextureShareBeginFrameSync() override`
- L58 _public function_ `virtual FTextureShareEndFrameSyncEvent& OnTextureShareEndFrameSync() override`
- L63 _public function_ `virtual FTextureShareFrameSyncEvent& OnTextureShareFrameSync() override`
- L68 _public function_ `virtual FTextureSharePreBeginFrameSyncEvent_RenderThread& OnTextureSharePreBeginFrameSync_RenderThread() override`
- L73 _public function_ `virtual FTextureShareBeginFrameSyncEvent_RenderThread& OnTextureShareBeginFrameSync_RenderThread() override`
- L78 _public function_ `virtual FTextureShareEndFrameSyncEvent_RenderThread& OnTextureShareEndFrameSync_RenderThread() override`
- L83 _public function_ `virtual FTextureShareFrameSyncEvent_RenderThread& OnTextureShareFrameSync_RenderThread() override`
- L88 _public function_ `virtual FTextureSharePreRenderViewFamily_RenderThread& OnTextureSharePreRenderViewFamily_RenderThread() override`
- L93 _public function_ `virtual FTextureSharePostRenderViewFamily_RenderThread& OnTextureSharePostRenderViewFamily_RenderThread() override`
- L98 _public function_ `virtual FTextureShareBackBufferReadyToPresentEvent_RenderThread& OnTextureShareBackBufferReadyToPresent_RenderThread() override`
- L104 _private member_ `FTextureShareGameViewportBeginDrawEvent TextureShareGameViewportBeginDrawEvent;`
- L105 _private member_ `FTextureShareGameViewportDrawEvent TextureShareGameViewportDrawEvent;`
- L106 _private member_ `FTextureShareGameViewportEndDrawEvent TextureShareGameViewportEndDrawEvent;`
- L108 _private member_ `FTextureShareBeginRenderViewFamilyEvent TextureShareBeginRenderViewFamilyEvent;`
- L110 _private member_ `FTextureShareBeginSessionEvent TextureShareBeginSessionEvent;`
- L111 _private member_ `FTextureShareEndSessionEvent TextureShareEndSessionEvent;`
- L113 _private member_ `FTextureSharePreBeginFrameSyncEvent TextureSharePreBeginFrameSyncEvent;`
- L114 _private member_ `FTextureShareBeginFrameSyncEvent TextureShareBeginFrameSyncEvent;`
- L116 _private member_ `FTextureShareEndFrameSyncEvent TextureShareEndFrameSyncEvent;`
- L117 _private member_ `FTextureShareFrameSyncEvent TextureShareFrameSyncEvent;`
- L119 _private member_ `FTextureSharePreBeginFrameSyncEvent_RenderThread TextureSharePreBeginFrameSyncEvent_RenderThread;`
- L120 _private member_ `FTextureShareBeginFrameSyncEvent_RenderThread TextureShareBeginFrameSyncEvent_RenderThread;`
- L122 _private member_ `FTextureShareEndFrameSyncEvent_RenderThread TextureShareEndFrameSyncEvent_RenderThread;`
- L123 _private member_ `FTextureShareFrameSyncEvent_RenderThread TextureShareFrameSyncEvent_RenderThread;`
- L125 _private member_ `FTextureSharePreRenderViewFamily_RenderThread TextureSharePreRenderViewFamily_RenderThread;`
- L126 _private member_ `FTextureSharePostRenderViewFamily_RenderThread TextureSharePostRenderViewFamily_RenderThread;`
- L127 _private member_ `FTextureShareBackBufferReadyToPresentEvent_RenderThread TextureShareBackBufferReadyToPresentEvent_RenderThread;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Module/TextureShareLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_TS_LOG(CategoryName, Verbosity, Format, ...)\` — Enable extra log
- L13 _macro_ `#define UE_TS_LOG(CategoryName, Verbosity, Format, ...)` — Disable extra log
- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShare, Warning, Warning);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShare, Warning, Warning);`
- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareObject, Warning, Warning);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareObject, Warning, Warning);`
- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareObjectProxy, Warning, Warning);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareObjectProxy, Warning, Warning);`
- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareWorldSubsystem, Warning, Warning);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareWorldSubsystem, Warning, Warning);`
- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareResource, Warning, Warning);`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareResource, Warning, Warning);`
- L25 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShare, Log, All);`
- L25 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShare, Log, All);`
- L26 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareObject, Log, All);`
- L26 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareObject, Log, All);`
- L27 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareObjectProxy, Log, All);`
- L27 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareObjectProxy, Log, All);`
- L28 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareWorldSubsystem, Log, All);`
- L28 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareWorldSubsystem, Log, All);`
- L29 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareResource, Log, All);`
- L29 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareResource, Log, All);`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Module/TextureShareModule.h` (Private)


#### class `FTextureShareModule`  
`class FTextureShareModule : public ITextureShare`  
_L9-35_
- inherits: `ITextureShare`
- desc: TextureShare module impl
- L13 _public prototype_ `FTextureShareModule();`
- L14 _public prototype_ `virtual ~FTextureShareModule();`
- L18 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _public prototype_ `virtual class ITextureShareAPI& GetTextureShareAPI() override;` — ITextureShare
- L28 _private member_ `TUniquePtr<class FTextureShareAPI> TextureShareAPI;`
- L32 _private prototype_ `void RegisterSettings_Editor();`
- L33 _private prototype_ `void UnregisterSettings_Editor();`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Object/TextureShareObject.h` (Private)


#### class `FTextureShareObject`  
`class FTextureShareObject : public ITextureShareObject , public TSharedFromThis<FTextureShareObject, ESPMode::ThreadSafe>`  
_L16-99_
- inherits: `ITextureShareObject,TSharedFromThis<FTextureShareObject,ESPMode::ThreadSafe>`
- desc: TextureShare object
- L21 _public prototype_ `FTextureShareObject(const TSharedRef<ITextureShareCoreObject, ESPMode::ThreadSafe>& InCoreObject);`
- L22 _public prototype_ `virtual ~FTextureShareObject();`
- L26 _public prototype_ `virtual void SetTextureShareContext(const TSharedPtr<ITextureShareContext, ESPMode::ThreadSafe>& InTextureShareContext) override;`
- L27 _public prototype_ `virtual const ITextureShareContext* GetTextureShareContext() const override;`
- L29 _public prototype_ `virtual const FString& GetName() const override;`
- L30 _public prototype_ `virtual FTextureShareCoreObjectDesc GetObjectDesc() const override;`
- L32 _public prototype_ `virtual bool IsActive() const override;`
- L33 _public prototype_ `virtual bool IsFrameSyncActive() const override;`
- L35 _public prototype_ `virtual bool SetProcessId(const FString& InProcessId) override;`
- L37 _public prototype_ `virtual bool SetSyncSetting(const FTextureShareCoreSyncSettings& InSyncSetting) override;`
- L38 _public prototype_ `virtual FTextureShareCoreSyncSettings GetSyncSetting() const override;`
- L40 _public prototype_ `virtual FTextureShareCoreFrameSyncSettings GetFrameSyncSettings(const ETextureShareFrameSyncTemplate InType) const override;`
- L42 _public prototype_ `virtual bool BeginSession(FViewport* InViewport) override;`
- L43 _public prototype_ `virtual bool EndSession() override;`
- L44 _public prototype_ `virtual bool IsSessionActive() const override;`
- L46 _public prototype_ `virtual bool BeginFrameSync() override;`
- L47 _public prototype_ `virtual bool FrameSync(const ETextureShareSyncStep InSyncStep) override;`
- L48 _public prototype_ `virtual bool EndFrameSync() override;`
- L50 _public prototype_ `virtual TArray<FTextureShareCoreObjectDesc> GetConnectedInterprocessObjects() const override;`
- L52 _public prototype_ `virtual FTextureShareCoreData& GetCoreData() override;`
- L53 _public prototype_ `virtual const FTextureShareCoreData& GetCoreData() const override;`
- L55 _public prototype_ `virtual TArray<FTextureShareCoreObjectData> GetReceivedCoreObjectData() const override;`
- L57 _public prototype_ `virtual FTextureShareData& GetData() override;`
- L59 _public prototype_ `virtual TSharedPtr<FTextureShareSceneViewExtension, ESPMode::ThreadSafe> GetViewExtension() const override;`
- L61 _public prototype_ `virtual TSharedRef<ITextureShareObjectProxy, ESPMode::ThreadSafe> GetProxy() const override;`
- L65 _public function_ `const TSharedRef<FTextureShareObjectProxy, ESPMode::ThreadSafe>& GetObjectProxyRef() const`
- L71 _private prototype_ `void UpdateViewExtension(FViewport* InViewport);`
- L77 _private prototype_ `bool DoFrameSync(const ETextureShareSyncStep InSyncStep);` — Implementing the synchronization step (calling a function from TextureShareCore) and handling callbacks This function can be called multiple times from FrameSync() to add missing synchronization steps.
- L84 _protected member_ `const TSharedRef<ITextureShareCoreObject, ESPMode::ThreadSafe> CoreObject;` — TS Core lib coreobject
- L87 _protected member_ `const TSharedRef<FTextureShareObjectProxy, ESPMode::ThreadSafe> ObjectProxy;` — Render thread object proxy
- L90 _protected member_ `TSharedRef<FTextureShareData, ESPMode::ThreadSafe> TextureShareData;` — Object data from game thread
- L93 _protected member_ `TSharedPtr<ITextureShareContext, ESPMode::ThreadSafe> TextureShareContext;` — Is an abstract container that can be used by the user to handle callback logic.
- L95 _protected member_ `bool bFrameSyncActive = false;`
- L96 _protected member_ `bool bSessionActive = false;`
- L98 _protected member_ `TSharedPtr<FTextureShareSceneViewExtension, ESPMode::ThreadSafe> ViewExtension;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Object/TextureShareObjectProxy.h` (Private)


#### class `FTextureShareObjectProxy`  
`class FTextureShareObjectProxy : public ITextureShareObjectProxy , public TSharedFromThis<FTextureShareObjectProxy, ESPMode::ThreadSafe>`  
_L16-144_
- inherits: `ITextureShareObjectProxy,TSharedFromThis<FTextureShareObjectProxy,ESPMode::ThreadSafe>`
- desc: TextureShare proxy object
- L23 _public prototype_ `FTextureShareObjectProxy(const TSharedRef<ITextureShareCoreObject, ESPMode::ThreadSafe>& InCoreObject);`
- L24 _public prototype_ `virtual ~FTextureShareObjectProxy();`
- L28 _public prototype_ `virtual const ITextureShareContext* GetTextureShareContext_RenderThread() const override;` — ITextureShareObjectProxy
- L30 _public prototype_ `virtual const FString& GetName_RenderThread() const override;`
- L31 _public prototype_ `virtual FTextureShareCoreObjectDesc GetObjectDesc_RenderThread() const override;`
- L33 _public prototype_ `virtual bool IsActive_RenderThread() const override;`
- L34 _public prototype_ `virtual bool IsFrameSyncActive_RenderThread() const override;`
- L36 _public prototype_ `virtual bool BeginFrameSync_RenderThread(FRHICommandListImmediate& RHICmdList) const override;`
- L37 _public prototype_ `virtual bool FrameSync_RenderThread(FRHICommandListImmediate& RHICmdList, const ETextureShareSyncStep InSyncStep) const override;`
- L38 _public prototype_ `virtual bool EndFrameSync_RenderThread(FRHICommandListImmediate& RHICmdList) const override;`
- L40 _public prototype_ `virtual FTextureShareCoreProxyData& GetCoreProxyData_RenderThread() override;`
- L41 _public prototype_ `virtual const FTextureShareCoreProxyData& GetCoreProxyData_RenderThread() const override;`
- L43 _public prototype_ `virtual TArray<FTextureShareCoreObjectProxyData> GetReceivedCoreObjectProxyData_RenderThread() const override;`
- L45 _public prototype_ `virtual const FTextureShareData& GetData_RenderThread() const override;`
- L47 _public function_ `virtual const TSharedPtr<FTextureShareSceneViewExtension, ESPMode::ThreadSafe>& GetViewExtension_RenderThread() const override`
- L52 _public prototype_ `virtual ETextureShareObjectProxyFlags GetObjectProxyFlags() const override;`
- L53 _public prototype_ `virtual void SetObjectProxyFlags(const ETextureShareObjectProxyFlags InFlags) override;`
- L55 _public prototype_ `virtual bool ShareResource_RenderThread( FRHICommandListImmediate& RHICmdList, const FTextureShareCoreResourceDesc& InResourceDesc, FRHITexture* InTexture, const FTextureShareColorDesc& InTextureColorDesc, const int32 InTextureGPUIndex, const FIntRect* InTextureRect = nullptr) const override;`
- L63 _public prototype_ `virtual bool ShareResource_RenderThread( FRDGBuilder& GraphBuilder, const FTextureShareCoreResourceDesc& InResourceDesc, const FRDGTextureRef& InTextureRef, const FTextureShareColorDesc& InTextureColorDesc, const int32 InTextureGPUIndex, const FIntRect* InTextureRect = nullptr) const override;`
- L71 _public prototype_ `virtual bool ShareResource_RenderThread( FRHICommandListImmediate& RHICmdList, const FTextureShareCoreResourceRequest& InResourceRequest, FRHITexture* InTexture, const FTextureShareColorDesc& InTextureColorDesc, const int32 InTextureGPUIndex, const FIntRect* InTextureRect = nullptr) const override;`
- L79 _public prototype_ `virtual bool ShareResource_RenderThread( FRDGBuilder& GraphBuilder, const FTextureShareCoreResourceRequest& InResourceRequest, const FRDGTextureRef& InTextureRef, const FTextureShareColorDesc& InTextureColorDesc, const int32 InTextureGPUIndex, const FIntRect* InTextureRect = nullptr) const override;`
- L87 _public prototype_ `virtual bool ShareRenderTargetResource_RenderThread( FRHICommandListImmediate& RHICmdList, const FTextureShareCoreResourceRequest& InResourceRequest, FTextureRenderTargetResource* InRenderTargetResource, const FTextureShareColorDesc& InRenderTargetColorDesc, const int32 InRenderTargetGPUIndex, const FIntRect* InRenderTargetRect = nullptr) const override;`
- L98 _protected prototype_ `bool BeginSession_RenderThread();`
- L99 _protected prototype_ `bool EndSession_RenderThread();`
- L102 _protected prototype_ `void HandleNewFrame_RenderThread( const TSharedRef<FTextureShareData, ESPMode::ThreadSafe>& InTextureShareData, const TSharedPtr<ITextureShareContext, ESPMode::ThreadSafe>& InTextureShareContext, const TSharedPtr<FTextureShareSceneViewExtension, ESPMode::ThreadSafe>& InViewExtension);` — Set the data from the game thread to the proxy object.
- L107 _protected prototype_ `bool DoFrameSync_RenderThread(FRHICommandListImmediate& RHICmdList, const ETextureShareSyncStep InSyncStep) const;`
- L110 _protected prototype_ `void AssignNewContext_RenderThread(const TSharedPtr<ITextureShareContext, ESPMode::ThreadSafe>& InTextureShareContext);` — This function assigns a new context to the proxy object and handles multithreading issues.
- L113 _protected prototype_ `void AssignNewViewExtension_RenderThread(const TSharedPtr<FTextureShareSceneViewExtension, ESPMode::ThreadSafe>& InViewExtension);` — This function assigns a new ViewExtension to the proxy object and handles multithreading issues.
- L116 _protected prototype_ `void ReleaseCoreObject_RenderThread();` — The CoreObject should be destroyed in the game thread.
- L118 _protected prototype_ `static void BeginSession_GameThread(const FTextureShareObject& In);`
- L119 _protected prototype_ `static void EndSession_GameThread(const FTextureShareObject& In);`
- L120 _protected prototype_ `static void UpdateProxy_GameThread(const FTextureShareObject& In);`
- L124 _protected prototype_ `static void OnTextureSharePreBeginFrameSync_GameThread(const FTextureShareObject& In);` — Called from the FTextureShareObject::BeginFrameSync().
- L128 _private member_ `const TSharedRef<ITextureShareCoreObject, ESPMode::ThreadSafe> CoreObject;` — TS Core lib object
- L131 _private member_ `TSharedRef<FTextureShareData, ESPMode::ThreadSafe> TextureShareData;` — Object data from game thread
- L134 _private member_ `TSharedPtr<ITextureShareContext, ESPMode::ThreadSafe> TextureShareContext;` — Is an abstract container that can be used by the user to handle callback logic.
- L137 _private member_ `mutable ETextureShareObjectProxyFlags ObjectProxyFlags = ETextureShareObjectProxyFlags::None;` — Extra flags
- L140 _private member_ `TUniquePtr<FTextureShareResourcesProxy> ResourcesProxy;` — All RHI resources and interfaces
- L143 _private member_ `TSharedPtr<FTextureShareSceneViewExtension, ESPMode::ThreadSafe> ViewExtension;` — Scene view extension

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Resources/TextureShareResource.h` (Private)


#### struct `FTextureShareExternalTextureRHI`  
`struct FTextureShareExternalTextureRHI`  
_L19-28_
- desc: TextureShare external RHI resource
- L21 _public function_ `FTextureShareExternalTextureRHI(const FTextureRHIRef InTextureRHI, const FTextureShareCoreResourceHandle* InResourceHandle, const uint32 InGPUIndex = 0) : TextureRHI(InTextureRHI), ResourceHandle(InResourceHandle), GPUIndex(InGPUIndex)`
- L25 _public member_ `const FTextureRHIRef TextureRHI;`
- L26 _public member_ `const FTextureShareCoreResourceHandle* ResourceHandle;`
- L27 _public member_ `const uint32 GPUIndex;`

#### class `FTextureShareResource`  
`class FTextureShareResource : public FTexture`  
_L33-121_
- inherits: `FTexture`
- desc: TextureShare RHI resource
- L37 _public prototype_ `FTextureShareResource(const TSharedRef<ITextureShareCoreObject, ESPMode::ThreadSafe>& InCoreObject, const FTextureShareCoreResourceDesc& InResourceDesc, const FTextureShareResourceSettings& InResourceSettings);`
- L38 _public prototype_ `virtual ~FTextureShareResource();`
- L41 _public function_ `const FTextureShareCoreResourceDesc& GetResourceDesc() const`
- L46 _public function_ `const FTextureShareResourceSettings& GetResourceSettings() const`
- L51 _public function_ `const FTextureRHIRef& GetResourceTextureRHI() const`
- L56 _public prototype_ `const FString& GetCoreObjectName() const;`
- L58 _public prototype_ `bool RegisterResourceHandle_RenderThread(FRHICommandListImmediate& RHICmdList, const FTextureShareCoreResourceRequest& InResourceRequest);`
- L59 _public prototype_ `bool ReleaseTextureShareHandle_RenderThread();`
- L64 _public prototype_ `virtual void HandleFrameBegin_RenderThread();` — [experimental] Mark all resources in cache as unused. Later, when the resources are used within the frame, this flag is cleared.
- L69 _public prototype_ `virtual void HandleFrameEnd_RenderThread();` — [experimental] Release all unused resources from cache.
- L72 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L75 _public function_ `virtual uint32 GetSizeX() const override` — Returns the width of the texture in pixels.
- L81 _public function_ `virtual uint32 GetSizeY() const override` — Returns the height of the texture in pixels.
- L86 _public function_ `virtual FString GetFriendlyName() const override`
- L92 _protected prototype_ `void InitDynamicRHI_Default(FRHICommandListBase& RHICmdList, FTextureRHIRef& OutTextureRHI);`
- L93 _protected prototype_ `void InitDynamicRHI_D3D12(FRHICommandListBase& RHICmdList, FTextureRHIRef& OutTextureRHI);`
- L95 _protected prototype_ `bool D3D11RegisterResourceHandle_RenderThread(FRHICommandListImmediate& RHICmdList, const FTextureShareCoreResourceRequest& InResourceRequest);`
- L96 _protected prototype_ `bool D3D11ReleaseTextureShareHandle_RenderThread();`
- L98 _protected prototype_ `bool D3D12RegisterResourceHandle_RenderThread(FRHICommandListImmediate& RHICmdList, const FTextureShareCoreResourceRequest& InResourceRequest);`
- L99 _protected prototype_ `bool D3D12ReleaseTextureShareHandle_RenderThread();`
- L103 _protected prototype_ `bool VulkanRegisterResourceHandle_RenderThread(FRHICommandListImmediate& RHICmdList, const FTextureShareCoreResourceRequest& InResourceRequest);`
- L104 _protected prototype_ `bool VulkanReleaseTextureShareHandle_RenderThread();`
- L115 _private member_ `const TSharedRef<ITextureShareCoreObject, ESPMode::ThreadSafe> CoreObject;`
- L118 _private member_ `const FTextureShareCoreResourceDesc ResourceDesc;` — Resource description
- L119 _private member_ `const FTextureShareResourceSettings ResourceSettings;`
- L120 _private member_ `TArray<struct FCachedSharedResource> CachedSharedResources;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Resources/TextureShareResourceSettings.h` (Private)


#### struct `FTextureShareResourceSettings`  
`struct FTextureShareResourceSettings`  
_L15-35_
- desc: TextureShare resource settings
- L17 _public prototype_ `FTextureShareResourceSettings() = default;`
- L18 _public prototype_ `FTextureShareResourceSettings(const FTextureShareCoreResourceRequest& InResourceRequest, FRHITexture* InTexture);`
- L21 _public prototype_ `bool Initialize(const FTextureShareCoreResourceRequest& InResourceRequest);` — Initialize the resource based on the request information.
- L24 _public prototype_ `bool Equals(const FTextureShareResourceSettings& In) const;` — Return true if the settings are equal and this resource can be reused.
- L27 _public member_ `FIntPoint Size;`
- L28 _public member_ `EPixelFormat Format = PF_Unknown;`
- L31 _public member_ `FTextureShareColorDesc ColorDesc;` — A description of the colors of this resource (Gamma, sRGB, OCIO, etc)
- L33 _public member_ `uint32 NumMips = 1;`
- L34 _public member_ `bool bShouldUseSRGB = false;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Resources/TextureShareResourceUtils.h` (Private)


#### class `FTextureShareResourceUtils`  
`class FTextureShareResourceUtils`  
_L18-95_
- desc: TextureShare resources helpers Implements resample shaders that can modify a texture in many ways: size, format, color gamma, etc.
- L31 _public prototype_ `static bool WriteToShareTexture_RenderThread( FRHICommandListImmediate& RHICmdList, TArray<TRefCountPtr<IPooledRenderTarget>>& InOutPoolResources, FRHITexture* SrcTexture, FRHITexture* DestSharedTexture, const FTextureShareColorDesc& SrcColorDesc, const FTextureShareColorDesc& DestColorDesc, const FIntRect* SrcTextureRectPtr = nullptr);` — Read the shared resoure to the texture. @param InOutPoolResources - All temporarily created resources will be added to this array. @param SrcTexture         - Src texture @param DestSharedTexture  - Dest texture (shared resource) @param SrcColorDesc       - Source texture color information (gamma, etc) @param DestColorDesc      - Dest texture color information (gamma, etc) @param SrcTextureRectPtr  - Src texture region (nullptr if the whole texture is used) @return - true if any RHI command has been used.
- L50 _public prototype_ `static bool ReadFromShareTexture_RenderThread( FRHICommandListImmediate& RHICmdList, TArray<TRefCountPtr<IPooledRenderTarget>>& InOutPoolResources, FRHITexture* SrcSharedTexture, FRHITexture* DestTexture, const FTextureShareColorDesc& SrcColorDesc, const FTextureShareColorDesc& DestColorDesc, const FIntRect* DestTextureRectPtr = nullptr);` — Write the shared resource to the texture @param InOutPoolResources - All temporarily created resources will be added to this array. @param SrcSharedTexture   - Src texture @param DestTexture  - Dest texture (shared resource) @param SrcColorDesc       - Source texture color information (gamma, etc) @param DestColorDesc      - Dest texture color information (gamma, etc) @param DestTextureRectPtr - Src texture region (nullptr if the whole texture is used) @return - true if any RHI command has been used.
- L68 _private prototype_ `static bool DirectCopyTexture_RenderThread( FRHICommandListImmediate& RHICmdList, FRHITexture* SrcTexture, FRHITexture* DestTexture, const FIntRect* SrcTextureRect, const FIntRect* DestTextureRect);` — Copying a texture region. @param SrcTexture      - Src texture @param DestTexture     - Dest texture @param SrcTextureRect  - Src texture region @param DestTextureRect - Dest texture region @return - true if RHI commands were used to copy the texture.
- L87 _private prototype_ `static bool ResampleCopyTexture_RenderThread( FRHICommandListImmediate& RHICmdList, FRHITexture* SrcTexture, FRHITexture* DestTexture, const FTextureShareColorDesc& SrcTextureColorDesc, const FTextureShareColorDesc& DestTextureColorDesc, const FIntRect* SrcTextureRect, const FIntRect* DestTextureRect);` — Copies src-texture to dest-texture with changes in size, texture format and color. @param SrcTexture           - Src texture @param DestTexture          - Dest texture @param SrcTextureColorDesc  - Source texture color information (gamme, etc) @param DestTextureColorDesc - Dest texture color information (gamme, etc) @param SrcTextureRect       - Src texture region @param DestTextureRect      - Dest texture region @return - true if RHI commands were used to copy the texture.

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Resources/TextureShareResourcesPool.h` (Private)


#### class `FTextureShareResourcesPool`  
`class FTextureShareResourcesPool`  
_L14-48_
- desc: TextureShare RHI resources pool
- L17 _public prototype_ `FTextureShareResourcesPool();`
- L18 _public prototype_ `~FTextureShareResourcesPool();`
- L20 _public prototype_ `void Release();`
- L23 _public prototype_ `FTextureShareResource* GetSharedResource_RenderThread(FRHICommandListImmediate& RHICmdList, const TSharedRef<ITextureShareCoreObject, ESPMode::ThreadSafe>& InCoreObject, FRHITexture* InSrcTexture, const FTextureShareCoreResourceRequest& InResourceRequest);`
- L25 _public function_ `bool IsRHICommandsListChanged_RenderThread() const`
- L31 _public function_ `void ClearFlagRHICommandsListChanged_RenderThread()`
- L38 _private prototype_ `FTextureShareResource* FindExistTextureShareResource_RenderThread(const FTextureShareCoreResourceDesc& InResourceDesc) const;`
- L39 _private prototype_ `FTextureShareResource* CreateTextureShareResource_RenderThread(const TSharedRef<ITextureShareCoreObject, ESPMode::ThreadSafe>& InCoreObject, const FTextureShareCoreResourceDesc& InResourceDesc, const FTextureShareResourceSettings& InResourceSettings);`
- L40 _private prototype_ `void ReleaseTextureShareResource_RenderThread(FTextureShareResource* &InOutResource);`
- L43 _private member_ `TArray<FTextureShareResource*> TextureResources;`
- L46 _private member_ `bool bIsRHICommandsListChanged = false;` — when RHI changed inside proxy function then value will be true

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Resources/TextureShareResourcesProxy.h` (Private)


#### enum `ECrossGPUTransferType`  
`enum class ECrossGPUTransferType : uint8`  
_L12-16_
- L14 _public enumerator_ `BeforeSync = 0`
- L15 _public enumerator_ `AfterSync`

#### class `FTextureShareResourcesProxy`  
`class FTextureShareResourcesProxy`  
_L27-207_
- desc: Support RHI resources on rendering thread
- L30 _public prototype_ `FTextureShareResourcesProxy();`
- L31 _public prototype_ `~FTextureShareResourcesProxy();`
- L37 _private prototype_ `bool ReadFromShareTexture_RenderThread( FRHICommandListImmediate& RHICmdList, FTextureShareResource* InSrcSharedResource, FRHITexture* InDestTexture, const FTextureShareColorDesc& InDestTextureColorDesc, const FIntRect* InDestTextureRect);` — Reads the shared texture into the DestTexture resource. The gamma will be
- L47 _public prototype_ `bool WriteToShareTexture_RenderThread( FRHICommandListImmediate& RHICmdList, FRHITexture* InSrcTexture, const FTextureShareColorDesc& InSrcTextureColorDesc, const FIntRect* InSrcTextureRect, FTextureShareResource* InDestSharedResource);`
- L54 _public prototype_ `FTextureShareResource* GetSharedTexture_RenderThread( FRHICommandListImmediate& RHICmdList, const TSharedRef<class ITextureShareCoreObject, ESPMode::ThreadSafe>& InCoreObject, FRHITexture* InSrcTexture, const FTextureShareCoreResourceRequest& InResourceRequest);`
- L61 _public prototype_ `void PushCrossGPUTransfer_RenderThread(const ECrossGPUTransferType InType, FTextureShareResource* InSharedResource, const int32 InSrcGPUIndex, const int32 InDestGPUIndex);` — save mgpu transfer and apply all at once before RHI flush
- L62 _public prototype_ `void RunCrossGPUTransfer_RenderThread(const ECrossGPUTransferType InType, FRHICommandListImmediate& RHICmdList, const ETextureShareSyncStep InSyncStep);`
- L65 _public prototype_ `void PushReceiveResource_RenderThread( const FTextureShareCoreResourceRequest& InResourceRequest, FTextureShareResource* InSrcSharedResource, FRHITexture* InDestTexture, const FTextureShareColorDesc& InDestTextureColorDesc, const FIntRect* InDestTextureSubRect);` — Support deferred receive (RHI stuff)
- L72 _public prototype_ `void PushReceiveResource_RenderThread( const FTextureShareCoreResourceRequest& InResourceRequest, FTextureShareResource* InSrcSharedResource, FTextureRenderTargetResource* InDestRTT, const FTextureShareColorDesc& InDestRTTColorDesc, const FIntRect* InDestTextureSubRect);`
- L79 _public prototype_ `void RunReceiveResources_RenderThread(FRHICommandListImmediate& RHICmdList, const ETextureShareSyncStep InSyncStep);`
- L82 _public prototype_ `void PushRegisterResource_RenderThread(const FTextureShareCoreResourceRequest& InResourceRequest, FTextureShareResource* InSharedResource);` — Collect shared resources
- L83 _public prototype_ `void RunRegisterResourceHandles_RenderThread(FRHICommandListImmediate& RHICmdList);`
- L86 _public prototype_ `void RHIThreadFlush_RenderThread(FRHICommandListImmediate& RHICmdList);` — flush RHI thread if needed
- L88 _public function_ `void ForceRHIFlushFlush_RenderThread()`
- L96 _public prototype_ `void Empty();` — Reset all deferred ops (in case when frame sync lost)
- L101 _private member_ `TArray<TRefCountPtr<IPooledRenderTarget>> PooledTempRTTs;` — Store all used temporary RTTs until RHI flush
- L103 _private member_ `TUniquePtr<FTextureShareResourcesPool> SendResourcesPool;`
- L104 _private member_ `TUniquePtr<FTextureShareResourcesPool> ReceiveResourcesPool;`
- L108 _private member_ `bool bForceRHIFlush = false;` — before IPC sync() call we need to flush RHI cmds, be sure resources created+updated
- L110 _private member_ `bool bRHIThreadChanged = false;`
- L198 _private member_ `TArray<FResourceCrossGPUTransferData> ResourceCrossGPUTransferPreSyncData;`
- L199 _private member_ `TArray<FResourceCrossGPUTransferData> ResourceCrossGPUTransferPostSyncData;`
- L201 _private member_ `TArray<FRegisteredResourceData> RegisteredResources;`
- L203 _private member_ `TArray<FReceiveResourceData> ReceiveResourceData;`
- L206 _protected prototype_ `void DoCrossGPUTransfers_RenderThread(FRHICommandListImmediate& RHICmdList, const ETextureShareSyncStep InSyncStep, TArray<FResourceCrossGPUTransferData>& InOutData);`

#### struct `FTextureShareResourcesProxy::FRegisteredResourceData`  
`struct FRegisteredResourceData`  
_L112-127_
- L114 _public function_ `FRegisteredResourceData(const FTextureShareCoreResourceRequest& InResourceRequest, FTextureShareResource* InSharedResource) : ResourceRequest(InResourceRequest), SharedResource(InSharedResource)`
- L118 _public function_ `bool operator==(const FRegisteredResourceData& In) const`
- L124 _public member_ `const FTextureShareCoreResourceRequest ResourceRequest;`
- L126 _public member_ `FTextureShareResource* const SharedResource = nullptr;`

#### struct `FTextureShareResourcesProxy::FReceiveResourceData`  
`struct FReceiveResourceData`  
_L130-178_
- desc: Contains data about receiver resource.
- L132 _public function_ `FReceiveResourceData( const FTextureShareCoreResourceRequest& InResourceRequest, FTextureShareResource* InSrcSharedResource, FRHITexture* InDestTexture, const FTextureShareColorDesc& InDestTextureColorDesc, const FIntRect* InDestTextureSubRect) : ResourceRequest(InResourceRequest) , SrcSharedResource(InSrcSharedResource) , DestTexture(InDestTexture) , DestColorDesc(InDestTextureColorDesc) , InDestTextureSubRect(InDestTextureSubRect ? *InDestTextureSubRect : FIntRect())`
- L145 _public function_ `FReceiveResourceData( const FTextureShareCoreResourceRequest& InResourceRequest, FTextureShareResource* InSrcSharedResource, FTextureRenderTargetResource* InDestRTT, const FTextureShareColorDesc& InDestRTTColorDesc, const FIntRect* InDestTextureSubRect) : ResourceRequest(InResourceRequest) , SrcSharedResource(InSrcSharedResource) , DestRTT(InDestRTT) , DestColorDesc(InDestRTTColorDesc) , InDestTextureSubRect(InDestTextureSubRect ? *InDestTextureSubRect : FIntRect())`
- L158 _public function_ `bool operator==(const FReceiveResourceData& In) const`
- L167 _public member_ `const FTextureShareCoreResourceRequest ResourceRequest;`
- L169 _public member_ `FTextureShareResource* const SrcSharedResource = nullptr;`
- L171 _public member_ `FRHITexture* const DestTexture = nullptr;`
- L172 _public member_ `FTextureRenderTargetResource* const DestRTT = nullptr;`
- L175 _public member_ `const FTextureShareColorDesc DestColorDesc;` — DestTexture/DestRTT gamma
- L177 _public member_ `FIntRect const InDestTextureSubRect;`

#### struct `FTextureShareResourcesProxy::FResourceCrossGPUTransferData`  
`struct FResourceCrossGPUTransferData`  
_L180-196_
- L182 _public function_ `FResourceCrossGPUTransferData(FTextureShareResource* InSharedResource, const int32 InSrcGPUIndex, const int32 InDestGPUIndex) : SharedResource(InSharedResource), SrcGPUIndex(InSrcGPUIndex), DestGPUIndex(InDestGPUIndex)`
- L186 _public function_ `bool operator==(const FResourceCrossGPUTransferData& In) const`
- L192 _public member_ `FTextureShareResource* const SharedResource = nullptr;`
- L194 _public member_ `const int32 SrcGPUIndex = -1;`
- L195 _public member_ `const int32 DestGPUIndex = -1;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Public/Blueprints/TextureShareBlueprintContainers.h` (Public)


#### class `UTextureShareObject`  
`class UTextureShareObject : public UObject`  
_L12-42_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject`
- desc: TextureShare UObject container
- L18 _public prototype_ `UTextureShareObject();`
- L19 _public prototype_ `virtual ~UTextureShareObject();`
- L24 _public prototype_ `void SendCustomData(const TMap<FString, FString>& InSendParameters);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Send Custom Data"), Category = "TextureShare")` — Override CustomData SendParameters
- L29 _public member_ `bool bEnable = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Enable this texture share object
- L33 _public member_ `FTextureShareObjectDesc Desc;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Object description
- L37 _public member_ `FTextureShareTexturesDesc Textures;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Shared resources
- L41 _public member_ `FTextureShareCustomData CustomData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Shared custom data

#### class `UTextureShare`  
`class UTextureShare : public UObject`  
_L48-92_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject`
- desc: TextureShare UObject interface
- L54 _public prototype_ `UTextureShare();`
- L55 _public prototype_ `virtual ~UTextureShare();`
- L58 _public function_ `bool IsEnabled() const`
- L64 _public prototype_ `TSet<FString> GetTextureShareObjectNames() const;` — return existing textureshare object names (duplicates are ignored)
- L67 _public prototype_ `UTextureShareObject* GetTextureShareObject(const FString& InShareName) const;` — Return enabled UObject by name
- L72 _public prototype_ `UTextureShareObject* GetOrCreateTextureShareObject(const FString& InShareName);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get or Create TextureShare Object"), Category = "TextureShare")` — Create new or get exist UTextureShare object
- L75 _public prototype_ `bool RemoveTextureShareObject(const FString& InShareName);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Remove TextureShare Object"), Category = "TextureShare")`
- L78 _public prototype_ `const TArray<UTextureShareObject*> GetTextureShareObjects() const;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get All TextureShare Objects"), Category = "TextureShare")`
- L83 _public member_ `bool bEnable = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Enable sharing for all objects
- L87 _public member_ `FString ProcessName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Unique process name (optional). When empty, used default name
- L91 _public member_ `TArray<TObjectPtr<UTextureShareObject>> TextureShareObjects;` — `UPROPERTY(Transient)` — Objects for sharing

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Public/Blueprints/TextureShareBlueprintContainersBase.h` (Public)


#### struct `FTextureShareSendTextureDesc`  
`struct FTextureShareSendTextureDesc`  
_L13-25_
- reflection: `USTRUCT(Blueprintable)`
- desc: Texture with name for sending
- L20 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Resource name (used for IPC)
- L24 _public member_ `TObjectPtr<UTexture> Texture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Resource to send

#### struct `FTextureShareReceiveTextureDesc`  
`struct FTextureShareReceiveTextureDesc`  
_L31-43_
- reflection: `USTRUCT(Blueprintable)`
- desc: Texture with name for receive
- L38 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Resource name (used for IPC)
- L42 _public member_ `TObjectPtr<UTextureRenderTarget> Texture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Resource to receive

#### struct `FTextureShareTexturesDesc`  
`struct FTextureShareTexturesDesc`  
_L49-61_
- reflection: `USTRUCT(Blueprintable)`
- desc: Custom textures for sharing
- L56 _public member_ `TArray<FTextureShareSendTextureDesc> SendTextures;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Send all this textures
- L60 _public member_ `TArray<FTextureShareReceiveTextureDesc> ReceiveTextures;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Receive all this textures

#### struct `FTextureShareCustomData`  
`struct FTextureShareCustomData`  
_L67-79_
- reflection: `USTRUCT(Blueprintable)`
- desc: Custom data for sharing
- L74 _public member_ `TMap<FString, FString> SendParameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — These custom data will be sent to remote processes.
- L78 _public member_ `TMap<FString, FString> ReceivedParameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — This user data is received from remote processes. Updated every frame tick

#### struct `FTextureShareObjectSyncSettings`  
`struct FTextureShareObjectSyncSettings`  
_L85-97_
- reflection: `USTRUCT(Blueprintable)`
- desc: Sync settings
- L92 _public member_ `int FrameSyncTimeOut = 1000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — MaxMillisecondsToWait for sync. 0 -infinite
- L96 _public member_ `int FrameConnectTimeOut = 5000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — MaxMillisecondsToWait for first connection. 0 -infinite

#### struct `FTextureShareObjectDesc`  
`struct FTextureShareObjectDesc`  
_L103-118_
- reflection: `USTRUCT(Blueprintable)`
- desc: Object descriptor
- L108 _public prototype_ `FString GetTextureShareObjectName() const;`
- L113 _public member_ `FString ShareName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Unique share name (case insensitive). When empty, used default name
- L117 _public member_ `FTextureShareObjectSyncSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureShare")` — Settings

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Public/ITextureShare.h` (Public)


#### class `ITextureShare`  
`class ITextureShare : public IModuleInterface`  
_L15-50_
- inherits: `IModuleInterface`
- desc: TextureShare module public API
- L19 _public member_ `static constexpr auto ModuleName = TEXT("Tex`
- L28 _public function_ `static inline ITextureShare& Get()`
- L38 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L49 _public prototype_ `virtual class ITextureShareAPI& GetTextureShareAPI() = 0;` — Returns API Interface Put headers in an Internal folder. This limits visibility to other engine modules, and allows implementations to be changed in hotfixes.

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Public/ITextureShareContext.h` (Public)


#### class `ITextureShareContext`  
`class ITextureShareContext : public TSharedFromThis<ITextureShareContext, ESPMode::ThreadSafe>`  
_L34-62_
- inherits: `TSharedFromThis<ITextureShareContext,ESPMode::ThreadSafe>`
- desc: TextureShare context Is an abstract container that should be used by the user to handle callback logic. Multithreading: The implementation of TS on the UE side is multithreaded. Every frame in the game thread we have to create a new context and populate it with new data. Then set it using the ITextureShareObject::SetTextureShareContext() function. This context is passed from the game thread to the rendering thread. (from the ITextureShareObject to the ITextureShareObjectProxy) With this approach, we get unique context data for both threads. Callbacks: Global TS callbacks are implemented in ITextureShareCallbacks. All of them can be used by different implementations at the same time. Therefore, we must separate the logic of these callbacks from each other. This can easily be done by implementing them in unique classes that are children of ITextureShareContext. For example, by checking the context of a TS object using one of these two functions: if(ITextureShareObject::GetTextureShareContext() == this) ... if(ITextureShareObjectProxy::GetTextureShareContext_RenderThread() == this) ... Custom implementation: Each custom implementation can create and use a new context class based on the ITextureShareContext class. It may also contain additional custom data for callbacks logic.
- L38 _public function_ `virtual ~ITextureShareContext()`
- L46 _public function_ `virtual void RegisterTextureShareContextCallbacks()` — Register callbacks for the game thread.
- L49 _public function_ `virtual void UnregisterTextureShareContextCallbacks()` — Unregister callbacks for the game thread.
- L52 _public function_ `virtual void RegisterTextureShareContextCallbacks_RenderThread()` — Register callbacks for the rendering thread.
- L55 _public function_ `virtual void UnregisterTextureShareContextCallbacks_RenderThread()` — Unregister callbacks for the rendering thread.
- L58 _public function_ `virtual FName GetRTTI() const` — A quick and dirty way to determine which TS data (sub)class this is.
- L61 _public function_ `bool IsA(const ITextureShareContext&& Other) const` — Returns true if the given object is of the same type.

### `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Public/ITextureShareWorldSubsystemContext.h` (Public)


#### class `ITextureShareWorldSubsystemContext`  
`class ITextureShareWorldSubsystemContext : public ITextureShareContext`  
_L9-17_
- inherits: `ITextureShareContext`
- desc: TextureShare context for WorldSubsystem based implementation
- L13 _public prototype_ `virtual ~ITextureShareWorldSubsystemContext() = default;`
- L16 _public function_ `virtual FName GetRTTI() const` — A quick and dirty way to determine which TS data (sub)class this is.
