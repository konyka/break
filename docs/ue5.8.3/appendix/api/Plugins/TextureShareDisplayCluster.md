# Plugins / TextureShareDisplayCluster

- module root: `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster`
- headers: 14; symbols: 124
- symbol kinds: class=11, delegate=6, function=12, macro=2, member=16, namespace=7, prototype=60, struct=1, variable=9
- PrivateDependencyModuleNames: Engine, RHI, RenderCore, Renderer, TextureShare, TextureShareCore
- PublicDependencyModuleNames: Core, CoreUObject, DisplayCluster, DisplayClusterConfiguration, DisplayClusterShaders

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Private/ITextureShareDisplayClusterAPI.h` (Private)


#### class `ITextureShareDisplayClusterAPI`  
`class ITextureShareDisplayClusterAPI`  
_L9-24_
- desc: Private API for nDisplay integration with TextureShare
- L12 _public prototype_ `virtual ~ITextureShareDisplayClusterAPI() = default;`
- L23 _public prototype_ `virtual bool TextureSharePolicySetProjectionData(const TSharedPtr<class IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& InPolicy, const TArray<struct FTextureShareCoreManualProjection>& InProjectionData) = 0;` — Set manual projection data @param InPolicy   - projection policy @param InProjectionData - manual prj data @return true, if success

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Private/Misc/TextureShareDisplayClusterStrings.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TextureShare` (scope `UE`)
- L13 _namespace_ `namespace DisplayClusterStrings` (scope `UE::TextureShare`)
- L16 _variable_ `static constexpr auto DefaultShareName = TEXT("nDi` (scope `UE::TextureShare::DisplayClusterStrings`) — Default ShareName for nDisplay integration object
- L18 _namespace_ `namespace Viewport` (scope `UE::TextureShare::DisplayClusterStrings`)
- L21 _variable_ `static constexpr auto FinalColor = TEXT("Vie` (scope `UE::TextureShare::DisplayClusterStrings::Viewport`) — FinalColor, but can be overrided
- L24 _variable_ `static constexpr auto Input = TEXT("Vie` (scope `UE::TextureShare::DisplayClusterStrings::Viewport`) — internal resolved shader resources, used as warp&blend source
- L25 _variable_ `static constexpr auto Mips = TEXT("Vie` (scope `UE::TextureShare::DisplayClusterStrings::Viewport`)
- L28 _variable_ `static constexpr auto Warped = TEXT("Vie` (scope `UE::TextureShare::DisplayClusterStrings::Viewport`) — After warp viewport (before output remap)
- L31 _namespace_ `namespace Output` (scope `UE::TextureShare::DisplayClusterStrings`)
- L34 _variable_ `static constexpr auto Backbuffer = TEXT("Fra` (scope `UE::TextureShare::DisplayClusterStrings::Output`) — access to nDisplay frame backbuffer
- L35 _variable_ `static constexpr auto BackbufferTemp = TEXT("Fra` (scope `UE::TextureShare::DisplayClusterStrings::Output`)
- L38 _namespace_ `namespace Postprocess` (scope `UE::TextureShare::DisplayClusterStrings`)
- L40 _variable_ `static constexpr auto TextureShare = TEXT("Tex` (scope `UE::TextureShare::DisplayClusterStrings::Postprocess`)
- L43 _namespace_ `namespace Projection` (scope `UE::TextureShare::DisplayClusterStrings`)
- L45 _variable_ `static constexpr auto TextureShare = TEXT("tex` (scope `UE::TextureShare::DisplayClusterStrings::Projection`)

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Private/Module/TextureShareDisplayClusterAPI.h` (Private)


#### class `FTextureShareDisplayClusterAPI`  
`class FTextureShareDisplayClusterAPI : public ITextureShareDisplayClusterAPI`  
_L9-31_
- inherits: `ITextureShareDisplayClusterAPI`
- desc: Private API for nDisplay integration with TextureShare implementation
- L13 _public prototype_ `FTextureShareDisplayClusterAPI();`
- L14 _public prototype_ `virtual ~FTextureShareDisplayClusterAPI();`
- L17 _public prototype_ `virtual bool TextureSharePolicySetProjectionData(const TSharedPtr<class IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& InPolicy, const TArray<FTextureShareCoreManualProjection>& InProjectionData) override;`
- L20 _public prototype_ `bool StartupModule();`
- L21 _public prototype_ `void ShutdownModule();`
- L25 _private member_ `TMap<FString, TSharedPtr<class IDisplayClusterProjectionPolicyFactory>> ProjectionPolicyFactories;` — Available projection policies factories
- L28 _private member_ `TMap<FString, TSharedPtr<class IDisplayClusterPostProcessFactory>> PostprocessAssets;` — Available postprocess factories
- L30 _private member_ `bool bModuleActive = false;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Private/Module/TextureShareDisplayClusterLog.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_TS_LOG(CategoryName, Verbosity, Format, ...)\` — Enable extra log
- L15 _macro_ `#define UE_TS_LOG(CategoryName, Verbosity, Format, ...)` — Disable extra log
- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareDisplayCluster, Warning, Warning);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareDisplayCluster, Warning, Warning);`
- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareDisplayClusterProjection, Warning, Warning);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareDisplayClusterProjection, Warning, Warning);`
- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareDisplayClusterPostProcess, Warning, Warning);`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareDisplayClusterPostProcess, Warning, Warning);`
- L24 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareDisplayCluster, Log, All);`
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareDisplayCluster, Log, All);`
- L25 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareDisplayClusterProjection, Log, All);`
- L25 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareDisplayClusterProjection, Log, All);`
- L26 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareDisplayClusterPostProcess, Log, All);`
- L26 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareDisplayClusterPostProcess, Log, All);`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Private/Module/TextureShareDisplayClusterModule.h` (Private)


#### class `FTextureShareDisplayCluster`  
`class FTextureShareDisplayCluster : public ITextureShareDisplayCluster`  
_L10-27_
- inherits: `ITextureShareDisplayCluster`
- desc: Module Impl
- L14 _public prototype_ `FTextureShareDisplayCluster();`
- L15 _public prototype_ `virtual ~FTextureShareDisplayCluster();`
- L19 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _public prototype_ `virtual ITextureShareDisplayClusterAPI& GetTextureShareDisplayClusterAPI() override;`
- L26 _protected member_ `TUniquePtr<FTextureShareDisplayClusterAPI> TextureShareDisplayClusterAPI;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Private/PostProcess/TextureSharePostprocess.h` (Private)


#### class `FTextureSharePostprocess`  
`class FTextureSharePostprocess : public FTextureSharePostprocessBase , public TSharedFromThis<FTextureSharePostprocess, ESPMode::ThreadSafe>`  
_L21-68_
- inherits: `FTextureSharePostprocessBase,TSharedFromThis<FTextureSharePostprocess,ESPMode::ThreadSafe>`
- desc: TextureShare over nDisplay post-process interface
- L26 _public prototype_ `FTextureSharePostprocess(const FString& PostprocessId, const struct FDisplayClusterConfigurationPostprocess* InConfigurationPostprocess);`
- L27 _public prototype_ `virtual ~FTextureSharePostprocess();`
- L29 _public prototype_ `virtual const FString& GetType() const override;`
- L32 _public prototype_ `virtual bool HandleStartScene(IDisplayClusterViewportManager* InViewportManager) override;` — Handle scene loading, viewport re-new etc
- L33 _public prototype_ `virtual void HandleEndScene(IDisplayClusterViewportManager* InViewportManager) override;`
- L36 _public prototype_ `virtual void HandleSetupNewFrame(IDisplayClusterViewportManager* InViewportManager) override;` — Handle frame on game thread
- L37 _public prototype_ `virtual void HandleBeginNewFrame(IDisplayClusterViewportManager* InViewportManager, FDisplayClusterRenderFrame& InOutRenderFrame) override;`
- L40 _public prototype_ `virtual void BeginFrameSync_RenderThread(FRHICommandListImmediate& RHICmdList);` — Handle frame on rendering thread
- L41 _public prototype_ `virtual void HandleRenderFrameSetup_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* InViewportManagerProxy) override;`
- L42 _public prototype_ `virtual void HandleBeginUpdateFrameResources_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* InViewportManagerProxy) override;`
- L43 _public prototype_ `virtual void HandleUpdateFrameResourcesAfterWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* InViewportManagerProxy) override;`
- L44 _public prototype_ `virtual void HandleEndUpdateFrameResources_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* InViewportManagerProxy) override;`
- L47 _public function_ `virtual bool IsPostProcessFrameAfterWarpBlendRequired() const override` — Also share backbuffer
- L53 _private prototype_ `bool IsEnabled() const;`
- L55 _private prototype_ `void ReleaseDisplayClusterPostProcessTextureShare();`
- L57 _private prototype_ `void UpdateSupportedViews(IDisplayClusterViewportManager* InViewportManager);`
- L58 _private prototype_ `void UpdateManualProjectionPolicy(IDisplayClusterViewportManager* InViewportManager);`
- L59 _private prototype_ `void UpdateViews(IDisplayClusterViewportManager* InViewportManager);`
- L62 _private prototype_ `void ShareViewport_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* InViewportManagerProxy, const ETextureShareSyncStep InReceiveSyncStep, const EDisplayClusterViewportResourceType InResourceType, const FString& InTextureId, bool bAfterWarpBlend = false) const;`
- L63 _private prototype_ `void ShareFrame_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* InViewportManagerProxy, const ETextureShareSyncStep InReceiveSyncStep, const EDisplayClusterViewportResourceType InResourceType, const FString& TextureId) const;`
- L66 _private member_ `TSharedPtr<class ITextureShareObject, ESPMode::ThreadSafe> Object;`
- L67 _private member_ `TSharedPtr<class ITextureShareObjectProxy, ESPMode::ThreadSafe> ObjectProxy;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Private/PostProcess/TextureSharePostprocessBase.h` (Private)


#### class `FTextureSharePostprocessBase`  
`class FTextureSharePostprocessBase : public IDisplayClusterPostProcess`  
_L9-37_
- inherits: `IDisplayClusterPostProcess`
- desc: Base postprocess
- L13 _public prototype_ `FTextureSharePostprocessBase(const FString& PostprocessId, const struct FDisplayClusterConfigurationPostprocess* InConfigurationPostprocess);`
- L14 _public prototype_ `virtual ~FTextureSharePostprocessBase() = 0;`
- L16 _public function_ `virtual const FString& GetId() const override`
- L21 _public function_ `virtual int32 GetOrder() const override`
- L26 _public function_ `virtual const TMap<FString, FString>& GetParameters() const override`
- L31 _public prototype_ `virtual bool IsConfigurationChanged(const struct FDisplayClusterConfigurationPostprocess* InConfigurationPostprocess) const override;`
- L34 _private member_ `FString PostprocessId;`
- L35 _private member_ `TMap<FString, FString> Parameters;`
- L36 _private member_ `int32 Order = -1;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Private/PostProcess/TextureSharePostprocessContext.h` (Private)


#### struct `FTextureSharePostprocessContext`  
`struct FTextureSharePostprocessContext : public ITextureShareDisplayClusterContext`  
_L10-16_
- inherits: `ITextureShareDisplayClusterContext`
- desc: Custom implementation of TextureShare context for nDisplay
- L14 _public prototype_ `virtual ~FTextureSharePostprocessContext() = default;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Private/PostProcess/TextureSharePostprocessFactory.h` (Private)


#### class `FTextureSharePostprocessFactory`  
`class FTextureSharePostprocessFactory : public IDisplayClusterPostProcessFactory`  
_L10-22_
- inherits: `IDisplayClusterPostProcessFactory`
- desc: Postprocess factory for TextureShare over nDisplay
- L15 _public prototype_ `virtual TSharedPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe> Create(const FString& PostProcessId, const struct FDisplayClusterConfigurationPostprocess* InConfigurationPostProcess) override;` — Constructor for postprocess
- L17 _public prototype_ `virtual bool CanBeCreated(const FDisplayClusterConfigurationPostprocess* InConfigurationPostProcess) const;`
- L21 _private member_ `TWeakPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe> ExistsTextureSharePostprocess;` — There can only be one TextureShare postprocess per application

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Private/Projection/TextureShareProjectionPolicy.h` (Private)


#### class `FTextureShareProjectionPolicy`  
`class FTextureShareProjectionPolicy : public FTextureShareProjectionPolicyBase`  
_L12-46_
- inherits: `FTextureShareProjectionPolicyBase`
- desc: Manual projection policy for TextureShare
- L16 _public prototype_ `FTextureShareProjectionPolicy(const FString& ProjectionPolicyId, const struct FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy);`
- L17 _public prototype_ `virtual ~FTextureShareProjectionPolicy();`
- L20 _public prototype_ `virtual const FString& GetType() const;`
- L22 _public prototype_ `virtual bool HandleStartScene(class IDisplayClusterViewport* InViewport) override;`
- L23 _public prototype_ `virtual void HandleEndScene(class IDisplayClusterViewport* InViewport) override;`
- L25 _public prototype_ `virtual bool CalculateView(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& ViewOffset, const float WorldToMeters, const float NCP, const float FCP) override;`
- L26 _public prototype_ `virtual bool GetProjectionMatrix(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FMatrix& OutPrjMatrix) override;`
- L28 _public function_ `virtual bool IsWarpBlendSupported(const IDisplayClusterViewport* InViewport) const override`
- L31 _public function_ `virtual bool IsWarpBlendSupported_RenderThread(const IDisplayClusterViewportProxy* InViewportProxy) const override`
- L34 _public function_ `virtual bool ShouldUseSourceTextureWithMips(const IDisplayClusterViewport* InViewport) const override`
- L38 _public prototype_ `bool SetCustomProjection(const TArray<FTextureShareCoreManualProjection>& InProjectionData);`
- L41 _private member_ `TArray<FTextureShareCoreManualProjection> Projections;`
- L44 _private member_ `float NCP;` — Near/far clip planes
- L45 _private member_ `float FCP;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Private/Projection/TextureShareProjectionPolicyBase.h` (Private)


#### class `FTextureShareProjectionPolicyBase`  
`class FTextureShareProjectionPolicyBase : public IDisplayClusterProjectionPolicy`  
_L10-36_
- inherits: `IDisplayClusterProjectionPolicy`
- desc: Base projection policy
- L14 _public prototype_ `FTextureShareProjectionPolicyBase(const FString& ProjectionPolicyId, const struct FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy);`
- L15 _public prototype_ `virtual ~FTextureShareProjectionPolicyBase() = 0;`
- L17 _public function_ `virtual const FString& GetId() const override`
- L22 _public function_ `virtual const TMap<FString, FString>& GetParameters() const override`
- L27 _public prototype_ `virtual bool IsConfigurationChanged(const struct FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) const override;`
- L29 _public prototype_ `static bool IsEditorOperationMode(class IDisplayClusterViewport* InViewport);`
- L30 _public prototype_ `static bool IsEditorOperationMode_RenderThread(const IDisplayClusterViewportProxy* InViewportProxy);`
- L34 _private member_ `FString ProjectionPolicyId;` — Added 'Policy' prefix to avoid "... hides class name ..." warnings in child classes
- L35 _private member_ `TMap<FString, FString> Parameters;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Private/Projection/TextureShareProjectionPolicyFactory.h` (Private)


#### class `FTextureShareProjectionPolicyFactory`  
`class FTextureShareProjectionPolicyFactory : public IDisplayClusterProjectionPolicyFactory`  
_L10-16_
- inherits: `IDisplayClusterProjectionPolicyFactory`
- desc: Projection policy factory for the 'TextureShare' policy
- L15 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> Create(const FString& ProjectionPolicyId, const struct FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) override;` — Constructor for policy

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Public/ITextureShareDisplayCluster.h` (Public)


#### class `ITextureShareDisplayCluster`  
`class ITextureShareDisplayCluster : public IModuleInterface`  
_L11-47_
- inherits: `IModuleInterface`
- desc: Public API for nDisplay integration with TextureShare
- L14 _public member_ `static constexpr auto ModuleName = TEXT("Tex`
- L17 _public prototype_ `virtual ~ITextureShareDisplayCluster() = default;`
- L26 _public function_ `static inline ITextureShareDisplayCluster& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton object, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L46 _public prototype_ `virtual class ITextureShareDisplayClusterAPI& GetTextureShareDisplayClusterAPI() = 0;` — Returns TextureShare nDisplay API Interface Put headers in an Internal folder. This limits visibility to other engine modules, and allows implementations to be changed in hotfixes.

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareDisplayCluster/Public/ITextureShareDisplayClusterContext.h` (Public)


#### class `ITextureShareDisplayClusterContext`  
`class ITextureShareDisplayClusterContext : public ITextureShareContext`  
_L9-17_
- inherits: `ITextureShareContext`
- desc: TextureShare context for implementing nDisplay integration
- L13 _public prototype_ `virtual ~ITextureShareDisplayClusterContext() = default;`
- L16 _public function_ `virtual FName GetRTTI() const` — A quick and dirty way to determine which TS data (sub)class this is.
