# Plugins / DisplayClusterProjection

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection`
- headers: 49; symbols: 705
- symbol kinds: class=38, delegate=10, enum=3, enumerator=9, function=59, macro=5, member=170, namespace=25, prototype=256, struct=10, typedef=35, union=1, variable=84
- PrivateDependencyModuleNames: D3D11RHI, D3D12RHI, DisplayCluster, ProceduralMeshComponent, Projects, RHI, RenderCore, UnrealEd
- PublicDependencyModuleNames: CinematicCamera, Core, CoreUObject, DisplayCluster, Engine, Projects, Slate, SlateCore
- PublicIncludePathModuleNames: DisplayClusterConfiguration, DisplayClusterShaders, DisplayClusterWarp

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Blueprints/DisplayClusterProjectionBlueprintAPIImpl.h` (Private)


#### class `UDisplayClusterProjectionBlueprintAPIImpl`  
`class UDisplayClusterProjectionBlueprintAPIImpl : public UObject , public IDisplayClusterProjectionBlueprintAPI`  
_L16-30_
- reflection: `UCLASS()`
- inherits: `UObject,IDisplayClusterProjectionBlueprintAPI`
- desc: Blueprint API interface implementation
- L29 _public prototype_ `virtual void CameraPolicySetCamera(const FString& ViewportId, UCameraComponent* NewCamera, float FOVMultiplier = 1.f) override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterProjectionBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Sets active camera component for camera policy

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/DisplayClusterProjectionLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjection, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjection, Log, All);`
- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionCamera, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionCamera, Log, All);`
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionDomeprojection, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionDomeprojection, Log, All);`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionEasyBlend, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionEasyBlend, Log, All);`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionManual, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionManual, Log, All);`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionMesh, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionMesh, Log, All);`
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionMPCDI, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionMPCDI, Log, All);`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionSimple, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionSimple, Log, All);`
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionVIOSO, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionVIOSO, Log, All);`
- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionReference, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterProjectionReference, Log, All);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/DisplayClusterProjectionModule.h` (Private)


#### class `FDisplayClusterProjectionModule`  
`class FDisplayClusterProjectionModule : public IDisplayClusterProjection`  
_L13-41_
- inherits: `IDisplayClusterProjection`
- L17 _public prototype_ `FDisplayClusterProjectionModule();`
- L18 _public prototype_ `virtual ~FDisplayClusterProjectionModule();`
- L24 _public prototype_ `virtual void StartupModule() override;`
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _public prototype_ `virtual void GetSupportedProjectionTypes(TArray<FString>& OutProjectionTypes) override;`
- L32 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicyFactory> GetProjectionFactory(const FString& InProjectionType) override;`
- L34 _public prototype_ `virtual bool CameraPolicySetCamera(const TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& InPolicy, UCameraComponent* const NewCamera, const FDisplayClusterProjectionCameraPolicySettings& CameraSettings) override;`
- L36 _public prototype_ `virtual UCameraComponent* CameraPolicyGetCameraComponent(const TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& InPolicy) override;`
- L40 _private member_ `TMap<FString, TSharedPtr<IDisplayClusterProjectionPolicyFactory>> ProjectionPolicyFactories;` — Available factories

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/PDisplayClusterProjectionStrings.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace DisplayClusterProjectionStrings`
- L8 _namespace_ `namespace ThirdParty` (scope `DisplayClusterProjectionStrings`)
- L10 _namespace_ `namespace DLL` (scope `DisplayClusterProjectionStrings::ThirdParty`)
- L12 _variable_ `static constexpr const TCHAR* EasyBlendDX11 = TEXT("Eas` (scope `DisplayClusterProjectionStrings::ThirdParty::DLL`)
- L13 _variable_ `static constexpr const TCHAR* EasyBlendDX12 = TEXT("Eas` (scope `DisplayClusterProjectionStrings::ThirdParty::DLL`)
- L15 _variable_ `static constexpr const TCHAR* VIOSO = TEXT("VIO` (scope `DisplayClusterProjectionStrings::ThirdParty::DLL`)
- L17 _variable_ `static constexpr const TCHAR* DomeprojectionDX11 = TEXT("Dom` (scope `DisplayClusterProjectionStrings::ThirdParty::DLL`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Camera/DisplayClusterProjectionCameraPolicy.h` (Private)


#### class `FDisplayClusterProjectionCameraPolicy`  
`class FDisplayClusterProjectionCameraPolicy : public FDisplayClusterProjectionPolicyBase`  
_L12-71_
- inherits: `FDisplayClusterProjectionPolicyBase`
- desc: Camera projection policy implementation
- L16 _public prototype_ `FDisplayClusterProjectionCameraPolicy(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy);`
- L20 _public prototype_ `virtual const FString& GetType() const override;`
- L22 _public prototype_ `virtual bool HandleStartScene(IDisplayClusterViewport* InViewport) override;`
- L23 _public prototype_ `virtual void HandleEndScene(IDisplayClusterViewport* InViewport) override;`
- L25 _public prototype_ `virtual bool CalculateView(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& ViewOffset, const float WorldToMeters, const float NCP, const float FCP) override;`
- L26 _public prototype_ `virtual bool GetProjectionMatrix(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FMatrix& OutPrjMatrix) override;`
- L27 _public prototype_ `virtual void SetupProjectionViewPoint(IDisplayClusterViewport* InViewport, const float InDeltaTime, FMinimalViewInfo& InOutViewInfo, float* OutCustomNearClippingPlane = nullptr) override;`
- L29 _public prototype_ `virtual void UpdatePostProcessSettings(IDisplayClusterViewport* InViewport) override;`
- L31 _public function_ `virtual bool ShouldUseSourceTextureWithMips(const IDisplayClusterViewport* InViewport) const override`
- L36 _public function_ `virtual bool ShouldUseViewPointComponentPostProcesses(IDisplayClusterViewport* InViewport) const override`
- L43 _public prototype_ `virtual EDisplayClusterProjectionPolicyFlags GetProjectionPolicyFlags(const IDisplayClusterViewport* InViewport, const uint32 InContextNum) const override;`
- L44 _public prototype_ `virtual UCameraComponent* GetCameraComponent() const override;`
- L48 _public prototype_ `void SetCamera(UCameraComponent* const NewCamera, const FDisplayClusterProjectionCameraPolicySettings& InCameraSettings);`
- L51 _private prototype_ `bool ImplSetupProjectionViewPoint(IDisplayClusterViewport* InViewport, const float InDeltaTime, FMinimalViewInfo& InOutViewInfo, float* OutCustomNearClippingPlane = nullptr) const;`
- L57 _private member_ `FDisplayClusterSceneComponentRef CameraRef;` — Camera to use for rendering
- L60 _private member_ `FDisplayClusterProjectionCameraPolicySettings CameraSettings;` — Camera settings
- L63 _private member_ `float ZNear = 1.f;` — Values of the clipping planes (saved from CalculateView())
- L64 _private member_ `float ZFar = 1.f;`
- L67 _private member_ `float CameraFOVDegrees = 90;` — camera FOV value in degrees (saved from the SetupProjectionViewPoint() function)
- L70 _private member_ `float CameraAspectRatio = 1;` — camera aspect ratio value (saved from the SetupProjectionViewPoint() function)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Camera/DisplayClusterProjectionCameraPolicyFactory.h` (Private)


#### class `FDisplayClusterProjectionCameraPolicyFactory`  
`class FDisplayClusterProjectionCameraPolicyFactory : public IDisplayClusterProjectionPolicyFactory , protected FDisplayClusterProjectionPolicyFactoryBase`  
_L12-20_
- inherits: `IDisplayClusterProjectionPolicyFactory,FDisplayClusterProjectionPolicyFactoryBase`
- desc: Factory for the 'camera' projection policy. Creates policies that derive view and projection from a UCameraComponent assigned to the projection policy.
- L18 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> Create(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/DisplayClusterProjectionPolicyBase.h` (Private)


#### class `FDisplayClusterProjectionPolicyBase`  
`class FDisplayClusterProjectionPolicyBase : public IDisplayClusterProjectionPolicy`  
_L16-70_
- inherits: `IDisplayClusterProjectionPolicy`
- desc: Base projection policy
- L20 _public prototype_ `FDisplayClusterProjectionPolicyBase(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy);`
- L24 _public function_ `virtual const FString& GetId() const override`
- L29 _public function_ `virtual USceneComponent* const GetOriginComponent() const override`
- L34 _public function_ `virtual USceneComponent* const GetPreviewMeshOriginComponent(IDisplayClusterViewport* InViewport) const override`
- L39 _public function_ `virtual const TMap<FString, FString>& GetParameters() const override`
- L44 _public prototype_ `virtual bool IsConfigurationChanged(const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) const override;`
- L48 _public prototype_ `static bool IsEditorOperationMode(IDisplayClusterViewport* InViewport);`
- L49 _public prototype_ `static bool IsEditorOperationMode_RenderThread(const IDisplayClusterViewportProxy* InViewportProxy);`
- L52 _protected prototype_ `void InitializeOriginComponent(IDisplayClusterViewport* InViewport, const FString& OriginCopmId);`
- L53 _protected prototype_ `void ReleaseOriginComponent();`
- L57 _private member_ `const FString PolicyInstanceId;` — The unique name of this projection policy.
- L60 _private member_ `FString PolicyOriginCompId;` — Origin component name.
- L63 _private member_ `TMap<FString, FString> Parameters;` — Projection policy parameters. Used for initialization.
- L66 _private member_ `FDisplayClusterSceneComponentRef PolicySceneOriginComponentRef;` — Origin component in DCRA from the scene
- L69 _private member_ `FDisplayClusterSceneComponentRef PolicyPreviewMeshOriginComponentRef;` — Origin component in the parent DCRA that is used to render the preview.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/DisplayClusterProjectionPolicyFactoryBase.h` (Private)


#### class `FDisplayClusterProjectionPolicyFactoryBase`  
`class FDisplayClusterProjectionPolicyFactoryBase`  
_L12-37_
- desc: Base class for all projection policy factories. Provides CanShowMsgOnce() to suppress repeated log messages — call it before any warning or error that may fire every frame (e.g. unsupported RHI, missing library).
- L21 _protected function_ `bool CanShowMsgOnce(const FString& InMsgTag)` — Returns true the first time InMsgTag is seen; false on every subsequent call with the same tag. Use this to gate log messages that should only fire once per factory instance. @param InMsgTag - unique string identifying the message site @return true if the caller should emit the message, false if it has already been shown
- L29 _protected function_ `bool CanShowMsgOnce(const TCHAR* InMsgTag)` — Returns true the first time InMsgTag is seen.
- L36 _private member_ `TSet<FString> ShownMsgTags;` — Tags of messages already shown; prevents the same log line from firing every frame.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Domeprojection/DisplayClusterProjectionDomeprojectionPolicyBase.h` (Private)


#### class `FDisplayClusterProjectionDomeprojectionPolicyBase`  
`class FDisplayClusterProjectionDomeprojectionPolicyBase : public FDisplayClusterProjectionPolicyBase`  
_L12-73_
- inherits: `FDisplayClusterProjectionPolicyBase`
- desc: Domeprojection projection policy base class
- L16 _public prototype_ `FDisplayClusterProjectionDomeprojectionPolicyBase(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy);`
- L20 _public prototype_ `virtual const FString& GetType() const override;`
- L22 _public prototype_ `virtual bool HandleStartScene(IDisplayClusterViewport* InViewport) override;`
- L23 _public prototype_ `virtual void HandleEndScene(IDisplayClusterViewport* InViewport) override;`
- L25 _public prototype_ `virtual bool CalculateView(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& ViewOffset, const float WorldToMeters, const float NCP, const float FCP) override;`
- L26 _public prototype_ `virtual bool GetProjectionMatrix(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FMatrix& OutPrjMatrix) override;`
- L28 _public prototype_ `virtual bool IsWarpBlendSupported(const IDisplayClusterViewport* InViewport) const override;`
- L29 _public prototype_ `virtual bool IsWarpBlendSupported_RenderThread(const IDisplayClusterViewportProxy* InViewportProxy) const override;`
- L31 _public prototype_ `virtual void ApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* InViewportProxy) override;`
- L34 _public function_ `virtual bool ShouldUseAdditionalTargetableResource(const IDisplayClusterViewport* InViewport) const override` — Request additional targetable resources for domeprojection  external warpblend
- L39 _public function_ `virtual float GetGeometryToMeters(const IDisplayClusterViewport* InViewport, const float InWorldToMeters) const override`
- L44 _public prototype_ `virtual void ApplyClippingPlanesOverrides(const IDisplayClusterViewport* InViewport, float& InOutNCP, float& InOutFCP) const override;`
- L46 _public function_ `virtual EDisplayClusterProjectionPolicyFlags GetProjectionPolicyFlags(const IDisplayClusterViewport* InViewport, const uint32 InContextNum) const override`
- L57 _protected prototype_ `virtual TUniquePtr<FDisplayClusterProjectionDomeprojectionViewAdapterBase> CreateViewAdapter(const FDisplayClusterProjectionDomeprojectionViewAdapterBase::FInitParams& InitParams) = 0;` — Delegate view adapter instantiation to the RHI specific children
- L61 _private prototype_ `bool ReadConfigData(IDisplayClusterViewport* InViewport, FString& OutFile, FString& OutOrigin, uint32& OutChannel, float& OutGeometryScale);` — Parse Domeprojection related data from the nDisplay config file
- L64 _private member_ `FString OriginCompId;`
- L65 _private member_ `uint32 DomeprojectionChannel = 0;`
- L69 _private member_ `float GeometryScale = 1000.f;` — Dome geometry units. Default it is in mm. @TODO: add this parameter to the domeprojection configuration UI
- L72 _private member_ `TUniquePtr<FDisplayClusterProjectionDomeprojectionViewAdapterBase> ViewAdapter;` — RHI depended view adapter (different RHI require different DLL/API etc.)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Domeprojection/DisplayClusterProjectionDomeprojectionPolicyFactory.h` (Private)


#### class `FDisplayClusterProjectionDomeprojectionPolicyFactory`  
`class FDisplayClusterProjectionDomeprojectionPolicyFactory : public IDisplayClusterProjectionPolicyFactory , protected FDisplayClusterProjectionPolicyFactoryBase`  
_L13-21_
- inherits: `IDisplayClusterProjectionPolicyFactory,FDisplayClusterProjectionPolicyFactoryBase`
- desc: Factory for the 'domeprojection' projection policy (Windows/DX11 only). Creates policies backed by the Domeprojection warping and blending library, used for dome and planetarium projection setups.
- L19 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> Create(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Domeprojection/DisplayClusterProjectionDomeprojectionViewAdapterBase.h` (Private)


#### class `FDisplayClusterProjectionDomeprojectionViewAdapterBase`  
`class FDisplayClusterProjectionDomeprojectionViewAdapterBase`  
_L14-48_
- desc: Base Domeprojection view adapter
- L23 _public function_ `FDisplayClusterProjectionDomeprojectionViewAdapterBase(const FInitParams& InitializationParams) : InitParams(InitializationParams)`
- L27 _public prototype_ `virtual ~FDisplayClusterProjectionDomeprojectionViewAdapterBase() = default;`
- L30 _public prototype_ `virtual bool Initialize(IDisplayClusterViewport* InViewport, const FString& File) = 0;`
- L32 _public function_ `virtual void Release()`
- L36 _public function_ `uint32 GetNumViews() const`
- L42 _public prototype_ `virtual bool CalculateView(IDisplayClusterViewport* InViewport, const uint32 InContextNum, const uint32 Channel, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& ViewOffset, const float WorldToMeters, const float NCP, const float FCP) = 0;`
- L43 _public prototype_ `virtual bool GetProjectionMatrix(IDisplayClusterViewport* InViewport, const uint32 InContextNum, const uint32 Channel, FMatrix& OutPrjMatrix) = 0;`
- L44 _public prototype_ `virtual bool ApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* InViewportProxy, const uint32 Channel) = 0;`
- L47 _private member_ `const FInitParams InitParams;`

#### struct `FDisplayClusterProjectionDomeprojectionViewAdapterBase::FInitParams`  
`struct FInitParams`  
_L17-20_
- L19 _public member_ `uint32 NumViews;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Domeprojection/Windows/DX11/DisplayClusterProjectionDomeprojectionLibraryDX11.h` (Private)


#### struct `DisplayClusterProjectionDomeprojectionLibraryDX11`  
`struct DisplayClusterProjectionDomeprojectionLibraryDX11`  
_L14-59_
- L16 _public prototype_ `static bool Initialize();`
- L17 _public prototype_ `static void Release();`
- L19 _public typedef_ `typedef dpResult(__cdecl *dpCreateContextD3D11)(dpContext** ppContext, ID3D11Device* pDevice, unsigned int pluginId);`
- L20 _public member_ `static dpCreateContextD3D11 dpCreateContextFunc;`
- L22 _public typedef_ `typedef dpResult(__cdecl *dpDestroyContextD3D11)(dpContext* pContext);`
- L23 _public member_ `static dpDestroyContextD3D11 dpDestroyContextFunc;`
- L25 _public typedef_ `typedef dpResult(__cdecl *dpLoadConfigurationFromFileD3D11)(dpContext* pContext, const char* filename);`
- L26 _public member_ `static dpLoadConfigurationFromFileD3D11 dpLoadConfigurationFromFileFunc;`
- L28 _public typedef_ `typedef dpResult(__cdecl *dpSetClippingPlanesD3D11)(dpContext* pContext, float cNear, float cFar);`
- L29 _public member_ `static dpSetClippingPlanesD3D11 dpSetClippingPlanesFunc;`
- L31 _public typedef_ `typedef dpResult(__cdecl *dpSetActiveChannelD3D11)(dpContext* pContext, unsigned int channelId, ID3D11Device* pDevice, unsigned int width, unsigned int height);`
- L32 _public member_ `static dpSetActiveChannelD3D11 dpSetActiveChannelFunc;`
- L34 _public typedef_ `typedef dpResult(__cdecl *dpSetCorrectionPassD3D11)(dpContext* pContext, dpCorrectionPassType pass, bool enabled);`
- L35 _public member_ `static dpSetCorrectionPassD3D11 dpSetCorrectionPassFunc;`
- L37 _public typedef_ `typedef dpResult(__cdecl *dpSetCorrectionPassD3D11_1)(dpContext* pContext, dpCorrectionPassType pass, float value);`
- L38 _public member_ `static dpSetCorrectionPassD3D11_1 dpSetCorrectionPass1Func;`
- L40 _public typedef_ `typedef dpResult(__cdecl *dpSetFlipWarpmeshVerticesYD3D11)(dpContext* pContext, bool flip);`
- L41 _public member_ `static dpSetFlipWarpmeshVerticesYD3D11 dpSetFlipWarpmeshVerticesYFunc;`
- L43 _public typedef_ `typedef dpResult(__cdecl *dpSetFlipWarpmeshTexcoordsVD3D11)(dpContext* pContext, bool flip);`
- L44 _public member_ `static dpSetFlipWarpmeshTexcoordsVD3D11 dpSetFlipWarpmeshTexcoordsVFunc;`
- L46 _public typedef_ `typedef dpResult(__cdecl *dpPreDrawD3D11_1)(dpContext* pContext, const dpVec3f eyepoint, dpCamera* pCamera);`
- L47 _public member_ `static dpPreDrawD3D11_1 dpPreDrawFunc;`
- L49 _public typedef_ `typedef dpResult(__cdecl *dpPostDrawD3D11)(dpContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11DeviceContext* pDeviceContext);`
- L50 _public member_ `static dpPostDrawD3D11 dpPostDrawFunc;`
- L52 _public typedef_ `typedef dpResult(__cdecl *dpGetOrientation)(const dpVec3f dir, const dpVec3f up, dpVec3f* pOrientation);`
- L53 _public member_ `static dpGetOrientation dpGetOrientationFunc;`
- L56 _private member_ `static void* DllHandle;`
- L57 _private member_ `static FCriticalSection CritSec;`
- L58 _private member_ `static bool bInitializeOnce;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Domeprojection/Windows/DX11/DisplayClusterProjectionDomeprojectionPolicyDX11.h` (Private)


#### class `FDisplayClusterProjectionDomeprojectionPolicyDX11`  
`class FDisplayClusterProjectionDomeprojectionPolicyDX11 : public FDisplayClusterProjectionDomeprojectionPolicyBase`  
_L14-28_
- inherits: `FDisplayClusterProjectionDomeprojectionPolicyBase`
- desc: Domeprojection projection policy (DX11 implementation)
- L18 _public function_ `FDisplayClusterProjectionDomeprojectionPolicyDX11(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) : FDisplayClusterProjectionDomeprojectionPolicyBase(ProjectionPolicyId, InConfigurationProjectionPolicy)`
- L23 _protected function_ `virtual TUniquePtr<FDisplayClusterProjectionDomeprojectionViewAdapterBase> CreateViewAdapter(const FDisplayClusterProjectionDomeprojectionViewAdapterBase::FInitParams& InitParams) override`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Domeprojection/Windows/DX11/DisplayClusterProjectionDomeprojectionViewAdapterDX11.h` (Private)


#### class `FDisplayClusterProjectionDomeprojectionViewAdapterDX11`  
`class FDisplayClusterProjectionDomeprojectionViewAdapterDX11 : public FDisplayClusterProjectionDomeprojectionViewAdapterBase`  
_L15-55_
- inherits: `FDisplayClusterProjectionDomeprojectionViewAdapterBase`
- desc: Domeprojection projection policy (DX11 adapter)
- L19 _public prototype_ `FDisplayClusterProjectionDomeprojectionViewAdapterDX11(const FDisplayClusterProjectionDomeprojectionViewAdapterBase::FInitParams& InitParams);`
- L20 _public prototype_ `virtual ~FDisplayClusterProjectionDomeprojectionViewAdapterDX11();`
- L23 _public prototype_ `virtual bool Initialize(IDisplayClusterViewport* InViewport, const FString& File) override;`
- L29 _public prototype_ `virtual bool CalculateView(IDisplayClusterViewport* InViewport, const uint32 InContextNum, const uint32 Channel, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& ViewOffset, const float WorldToMeters, const float NCP, const float FCP) override;`
- L30 _public prototype_ `virtual bool GetProjectionMatrix(IDisplayClusterViewport* InViewport, const uint32 InContextNum, const uint32 Channel, FMatrix& OutPrjMatrix) override;`
- L31 _public prototype_ `virtual bool ApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* InViewportProxy, const uint32 Channel) override;`
- L34 _protected prototype_ `bool ImplApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, uint32 ContextNum, const uint32 Channel, FRHITexture* InputTextures, FRHITexture* OutputTextures);`
- L37 _private member_ `float ZNear;`
- L38 _private member_ `float ZFar;`
- L52 _private member_ `TArray<FViewData> Views;`
- L54 _private member_ `FCriticalSection DllAccessCS;`

#### class `FDisplayClusterProjectionDomeprojectionViewAdapterDX11::FViewData`  
`class FViewData`  
_L40-50_
- L43 _public prototype_ `bool Initialize(IDisplayClusterViewport* InViewport, const FString& InFile, FCriticalSection& DllAccessCS);`
- L44 _public prototype_ `void Release(FCriticalSection& DllAccessCS);`
- L47 _public member_ `dpCamera Camera;`
- L49 _public member_ `dpContext* Context = nullptr;` — unique context for each eye (hold warp settings, different for each eye)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/EasyBlend/DisplayClusterProjectionEasyBlendPolicy.h` (Private)


#### class `FDisplayClusterProjectionEasyBlendPolicy`  
`class FDisplayClusterProjectionEasyBlendPolicy : public FDisplayClusterProjectionPolicyBase , public TSharedFromThis<FDisplayClusterProjectionEasyBlendPolicy, ESPMode::ThreadSafe>`  
_L15-91_
- inherits: `FDisplayClusterProjectionPolicyBase,TSharedFromThis<FDisplayClusterProjectionEasyBlendPolicy,ESPMode::ThreadSafe>`
- desc: EasyBlend projection policy
- L20 _public prototype_ `FDisplayClusterProjectionEasyBlendPolicy(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy);`
- L21 _public prototype_ `virtual ~FDisplayClusterProjectionEasyBlendPolicy();`
- L25 _public prototype_ `virtual const FString& GetType() const override;`
- L27 _public prototype_ `virtual bool HandleStartScene(IDisplayClusterViewport* InViewport) override;`
- L28 _public prototype_ `virtual void HandleEndScene(IDisplayClusterViewport* InViewport) override;`
- L30 _public prototype_ `virtual bool CalculateView(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& ViewOffset, const float WorldToMeters, const float NCP, const float FCP) override;`
- L31 _public prototype_ `virtual bool GetProjectionMatrix(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FMatrix& OutPrjMatrix) override;`
- L33 _public prototype_ `virtual bool IsWarpBlendSupported(const IDisplayClusterViewport* InViewport) const override;`
- L34 _public prototype_ `virtual bool IsWarpBlendSupported_RenderThread(const IDisplayClusterViewportProxy* InViewportProxy) const override;`
- L36 _public prototype_ `virtual void ApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* InViewportProxy) override;`
- L38 _public function_ `virtual float GetGeometryToMeters(const IDisplayClusterViewport* InViewport, const float InWorldToMeters) const override`
- L44 _public function_ `virtual EDisplayClusterProjectionPolicyFlags GetProjectionPolicyFlags(const IDisplayClusterViewport* InViewport, const uint32 InContextNum) const override`
- L51 _public function_ `virtual FVector GetOriginLocationOffsetInGeometryUnits(const IDisplayClusterViewport* InViewport) const override`
- L57 _public function_ `virtual bool ShouldUseAdditionalTargetableResource(const IDisplayClusterViewport* InViewport) const override` — Request additional targetable resources for easyblend external warpblend
- L62 _public prototype_ `virtual void UpdateProxyData(IDisplayClusterViewport* InViewport) override;`
- L64 _public prototype_ `virtual bool HasPreviewMesh(IDisplayClusterViewport* InViewport) override;`
- L65 _public prototype_ `virtual class UMeshComponent* GetOrCreatePreviewMeshComponent(IDisplayClusterViewport* InViewport, bool& bOutIsRootActorComponent) override;`
- L70 _public prototype_ `static bool IsEasyBlendSupported();` — Returns true if the current OS and RHI has an EasyBlend implementation.
- L73 _protected prototype_ `void ReleasePreviewMeshComponent();`
- L74 _protected prototype_ `void ImplRelease();`
- L78 _private member_ `FDisplayClusterProjectionEasyBlendPolicyConfiguration EasyBlendConfiguration;` — Configuration of the EasyBlend
- L81 _private member_ `TSharedPtr<IDisplayClusterProjectionEasyBlendPolicyViewData, ESPMode::ThreadSafe> PolicyViewData;` — Views data for game and rendering thread
- L82 _private member_ `TArray<FDisplayClusterProjectionEasyBlendPolicyViewInfo> PolicyViewInfo;`
- L84 _private member_ `TSharedPtr<IDisplayClusterProjectionEasyBlendPolicyViewData, ESPMode::ThreadSafe> PolicyViewDataProxy;`
- L85 _private member_ `TArray<FDisplayClusterProjectionEasyBlendPolicyViewInfo> PolicyViewInfoProxy;`
- L87 _private member_ `FDisplayClusterSceneComponentRef PreviewMeshComponentRef;`
- L90 _private member_ `FRHIViewport* RHIViewportProxy = nullptr;` — Viewport RHI

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/EasyBlend/DisplayClusterProjectionEasyBlendPolicyConfiguration.h` (Private)


#### struct `FDisplayClusterProjectionEasyBlendPolicyConfiguration`  
`struct FDisplayClusterProjectionEasyBlendPolicyConfiguration`  
_L12-50_
- desc: EasyBlend projection policy configuration data
- L16 _public prototype_ `bool Initialize(const TMap<FString, FString>& InParameters, IDisplayClusterViewport* InViewport);` — Initialize exsyblend configuration from parameters.
- L18 _public function_ `void RaiseInvalidConfigurationFlag()`
- L26 _public prototype_ `FString ToString(const bool bOnlyGeometryParameters = false) const;` — convert all parameters to string
- L30 _public member_ `FString CalibrationFile;` — Path to EasyBlend calibration file
- L33 _public member_ `FString OriginCompId;` — Origin component name
- L36 _public member_ `float GeometryScale = 1.f;` — EasyBlend unit scale
- L39 _public member_ `FVector OriginOffset = FVector::ZeroVector;` — Origin's location in geometry units.
- L42 _public member_ `bool bIsPreviewMeshEnabled = false;` — Allow to use preview mesh
- L46 _private member_ `bool bInvalidConfiguration = false;` — Discard this configuration
- L49 _private member_ `bool bInitializeOnce = false;` — Since the projection policy has const-parameters, we must initialize the configuration only once

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/EasyBlend/DisplayClusterProjectionEasyBlendPolicyFactory.h` (Private)


#### class `FDisplayClusterProjectionEasyBlendPolicyFactory`  
`class FDisplayClusterProjectionEasyBlendPolicyFactory : public IDisplayClusterProjectionPolicyFactory , protected FDisplayClusterProjectionPolicyFactoryBase`  
_L14-27_
- inherits: `IDisplayClusterProjectionPolicyFactory,FDisplayClusterProjectionPolicyFactoryBase`
- desc: Factory for the 'easyblend' projection policy. Creates policies backed by the Scalable Display EasyBlend warping and blending library. The factory owns shared library instances for DX11 and DX12; the appropriate one is selected at policy creation time based on the active RHI.
- L20 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> Create(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) override;`
- L25 _private member_ `TSharedPtr<class FDisplayClusterProjectionEasyBlendLibraryDX11, ESPMode::ThreadSafe> EasyBlendLibraryDX11;` — EasyBlend runtime library instances, one per supported RHI. Shared across all policies created by this factory.
- L26 _private member_ `TSharedPtr<class FDisplayClusterProjectionEasyBlendLibraryDX12, ESPMode::ThreadSafe> EasyBlendLibraryDX12;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/EasyBlend/DisplayClusterProjectionEasyBlendPolicyGeometryExportData.h` (Private)


#### class `FDisplayClusterProjectionEasyBlendGeometryExportData`  
`class FDisplayClusterProjectionEasyBlendGeometryExportData`  
_L11-50_
- desc: Export warp geometry
- L14 _public function_ `FDisplayClusterProjectionEasyBlendGeometryExportData(const FString& InUniqueName) : UniqueName(InUniqueName)`
- L19 _public prototype_ `void GenerateGeometryNormals();` — Generate normals.
- L23 _public prototype_ `static int32 GetDataCacheTimeOutInFrames();` — Return DataCache timeout in frames.
- L26 _public prototype_ `static bool IsDataCacheEnabled();` — Return true if DataCache is enabled.
- L29 _public function_ `inline const FString& GetDataCacheName() const` — Returns the unique name of this MPCDI file resource for DataCache.
- L35 _public function_ `inline void ReleaseDataCacheItem()` — Method for releasing a cached data item, called before its destructor.
- L39 _public prototype_ `static TSharedPtr<FDisplayClusterProjectionEasyBlendGeometryExportData, ESPMode::ThreadSafe> Create(const TSharedRef<IDisplayClusterProjectionEasyBlendPolicyViewData, ESPMode::ThreadSafe>& InViewData, const FDisplayClusterProjectionEasyBlendPolicyConfiguration& InConfigData);`
- L42 _public member_ `const FString UniqueName;`
- L44 _public member_ `TArray<FVector> Vertices;`
- L45 _public member_ `TArray<FVector> Normal;`
- L46 _public member_ `TArray<FVector2D> UV;`
- L47 _public member_ `TArray<int32> Triangles;`
- L49 _public member_ `float GeometryScale = 1;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/EasyBlend/IDisplayClusterProjectionEasyBlendPolicyViewData.h` (Private)


#### struct `FDisplayClusterProjectionEasyBlendPolicyViewInfo`  
`struct FDisplayClusterProjectionEasyBlendPolicyViewInfo`  
_L15-20_
- desc: View information
- L17 _public member_ `FVector ViewLocation;`
- L18 _public member_ `FRotator ViewRotation;`
- L19 _public member_ `FVector4 FrustumAngles;` — L R T B

#### class `IDisplayClusterProjectionEasyBlendPolicyViewData`  
`class IDisplayClusterProjectionEasyBlendPolicyViewData`  
_L25-57_
- desc: EasyBlend view data interface
- L28 _public prototype_ `virtual ~IDisplayClusterProjectionEasyBlendPolicyViewData() = default;`
- L33 _public prototype_ `static TSharedPtr<IDisplayClusterProjectionEasyBlendPolicyViewData, ESPMode::ThreadSafe> Create(const FDisplayClusterProjectionEasyBlendPolicyConfiguration& InEasyBlendConfiguration);` — Creates and initializes the EasyBlend interface for the current RHI and OS. Returns nullptr if it is not implemented or cannot be initialized.
- L37 _public function_ `virtual bool Initialize(const FDisplayClusterProjectionEasyBlendPolicyConfiguration& InEasyBlendConfiguration)` — Initialize EasyBlend view data.
- L39 _public function_ `virtual bool CalculateWarpBlend(FDisplayClusterProjectionEasyBlendPolicyViewInfo& InOutViewInfo)`
- L40 _public function_ `virtual bool ApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const FDisplayClusterProjectionEasyBlendPolicyViewInfo& InViewInfo, FRHITexture* InputTexture, FRHITexture* OutputTexture, FRHIViewport* InRHIViewport)`
- L45 _public function_ `virtual bool HasPreviewMesh()` — Export warp mesh geometry from EasyBlend file
- L46 _public function_ `virtual bool GetPreviewMeshGeometry(const FDisplayClusterProjectionEasyBlendPolicyConfiguration& InEasyBlendConfiguration, FDisplayClusterProjectionEasyBlendGeometryExportData& OutMeshData)`
- L50 _protected member_ `FCriticalSection EasyBlendMeshDataAccessCS;` — Lock access to EasyBlendMeshData
- L53 _protected member_ `bool bIsEasyBlendMeshDataInitialized = false;` — Whether EasyBlendMeshData requires a call to the EasyBlend1Uninitialize() function.
- L56 _protected member_ `bool bIsRenderResourcesInitialized = false;` — The rendering resources must be initialized once or the rendering thread must be initialized

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/EasyBlend/Windows/DX11/DisplayClusterProjectionEasyBlendLibraryDX11.h` (Private)


#### class `FDisplayClusterProjectionEasyBlendLibraryDX11`  
`class FDisplayClusterProjectionEasyBlendLibraryDX11`  
_L16-56_
- desc: Implement access to EasyBlend DX11 DLL functions The basic idea is to load the DLL dynamically without using LIB files The DLL function is described in the file ./ThirdParty/EasyBlend/Include/EasyBlendSDKDXApi.h
- L19 _public prototype_ `FDisplayClusterProjectionEasyBlendLibraryDX11();`
- L20 _public prototype_ `~FDisplayClusterProjectionEasyBlendLibraryDX11();`
- L23 _public prototype_ `static TSharedRef<FDisplayClusterProjectionEasyBlendLibraryDX11, ESPMode::ThreadSafe>& Get();` — Return EaxyBlend DX11 library api.
- L26 _public function_ `inline bool IsInitialized() const` — If the DLL is loaded correctly, this function returns true.
- L32 _public prototype_ `DeclareEasyBlendFunc(Initialize);`
- L33 _public prototype_ `DeclareEasyBlendFunc(Uninitialize);`
- L35 _public prototype_ `DeclareEasyBlendFunc(InitDeviceObjects);`
- L37 _public prototype_ `DeclareEasyBlendFunc(SetEyepoint);`
- L38 _public prototype_ `DeclareEasyBlendFunc(SDK_GetHeadingPitchRoll);`
- L40 _public prototype_ `DeclareEasyBlendFunc(DXRender);`
- L41 _public prototype_ `DeclareEasyBlendFunc(SetInputTexture2D);`
- L42 _public prototype_ `DeclareEasyBlendFunc(SetOutputTexture2D);`
- L46 _private prototype_ `bool InitializeDLL();` — Imprort all functionf from EasyBlend DLL. Return true on success.
- L47 _private prototype_ `void ReleaseDLL();`
- L52 _private member_ `bool bInitialized = false;` — Initializetion state
- L55 _private member_ `void* EasyBlend_DLL_Handler = nullptr;` — Saved handle to EasyBlend DLL

#### Free symbols / members of external scopes

- L8 _macro_ `#define DeclareEasyBlendFunc(DLLFunc) EasyBlend1##DLLFunc##Proc EasyBlend1##DLLFunc = nullptr;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/EasyBlend/Windows/DX11/DisplayClusterProjectionEasyBlendLibraryDX11Types.h` (Private)


#### Free symbols / members of external scopes

- L22 _typedef_ `typedef EasyBlend1SDKDXError(__stdcall* EasyBlend1InitializeProc)(const char* szFileName, EasyBlend1SDKDX_Mesh* msm);` — Initializes a Mesh structure from an EasyBlend calibration file (*.ol file ). The given Mesh pointer should be allocated ( not NULL ) and will be overwritten. @param szFileName - the calibration file name @param msm      - a pointer to the mesh
- L30 _typedef_ `typedef EasyBlend1SDKDXError(__stdcall* EasyBlend1UninitializeProc)(EasyBlend1SDKDX_Mesh* msm);` — Given a correctly initialized SDK Mesh, releases the resources used by the Mesh structure.  The Mesh pointer memory must still be externally deallocated after this call. @param msm - a pointer to the mesh
- L40 _typedef_ `typedef EasyBlend1SDKDXError(__stdcall* EasyBlend1InitDeviceObjectsProc)(EasyBlend1SDKDX_Mesh* msm, ID3D1XDevice* pDevice, ID3D1XDeviceContext* pDeviceContext , IDXGISwapChain* pSwapChain);` — The Standard DirectX Commands to deal with losing/regaining a DirectX device. @param msm @param pDevice @param pDeviceContext @param pSwapChain
- L51 _typedef_ `typedef EasyBlend1SDKDXError(__stdcall* EasyBlend1DXRenderProc)(EasyBlend1SDKDX_Mesh* msm, ID3D1XDevice* id3d, ID3D1XDeviceContext* pDeviceContext , IDXGISwapChain* iswapChain, bool doPresent);` — Render warpblend @param msm @param id3d @param pDeviceContext @param iswapChain @param doPresent
- L66 _typedef_ `typedef EasyBlend1SDKDXError(__stdcall* EasyBlend1SetEyepointProc)(EasyBlend1SDKDX_Mesh* msm, const double& eyeX, const double& eyeY, const double& eyeZ);` — This comand is used only for Dynamic Eyepoint. The new location of the viewer is sent to the command, and a new frustum is calculated. To use this function, the Inititalize command must have been called with a .pol file. After this call, remember to get new frustum and use it to update the frustum. This command is currently CPU bound. @param msm @param eyeX @param eyeY @param eyeZ
- L78 _typedef_ `typedef EasyBlend1SDKDXError(__stdcall* EasyBlend1SDK_GetHeadingPitchRollProc)(double& rdDegreesHeading, double& rdDegreesPitch, double& rdDegreesRoll, EasyBlend1SDKDX_Mesh* msm);` — This command returns the view angles for the instance of the SDK. As Heading, then Pitch then Roll. The Angles are pre-computed in the SDK file, so that it only works with newer version of EasyBlend that write this information to disk. (Newer than Nov 2011 or newer) @param rdDegreesHeading @param rdDegreesPitch @param rdDegreesRoll @param msm
- L86 _typedef_ `typedef EasyBlend1SDKDXError(__stdcall* EasyBlend1SetInputTexture2DProc)(EasyBlend1SDKDX_Mesh* msm, ID3D1XTexture2D* texture);` — These function are for setting input/output textures, which allows chaining filters @param msm @param texture
- L94 _typedef_ `typedef EasyBlend1SDKDXError(__stdcall* EasyBlend1SetOutputTexture2DProc)(EasyBlend1SDKDX_Mesh* msm, ID3D1XTexture2D* texture);` — These function are for setting input/output textures, which allows chaining filters @param msm @param texture

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/EasyBlend/Windows/DX11/DisplayClusterProjectionEasyBlendPolicyViewDataDX11.h` (Private)


#### class `FDisplayClusterProjectionEasyBlendPolicyViewDataDX11`  
`class FDisplayClusterProjectionEasyBlendPolicyViewDataDX11 : public IDisplayClusterProjectionEasyBlendPolicyViewData , public TSharedFromThis<FDisplayClusterProjectionEasyBlendPolicyViewDataDX11, ESPMode::ThreadSafe>`  
_L11-32_
- inherits: `IDisplayClusterProjectionEasyBlendPolicyViewData,TSharedFromThis<FDisplayClusterProjectionEasyBlendPolicyViewDataDX11,ESPMode::ThreadSafe>`
- desc: The DX11 implementation for EasyBlend
- L16 _public prototype_ `~FDisplayClusterProjectionEasyBlendPolicyViewDataDX11();`
- L20 _public prototype_ `virtual bool Initialize(const FDisplayClusterProjectionEasyBlendPolicyConfiguration& InEasyBlendConfiguration) override;` — BEGIN ~IDisplayClusterProjectionEasyBlendPolicyViewData
- L22 _public prototype_ `virtual bool CalculateWarpBlend(FDisplayClusterProjectionEasyBlendPolicyViewInfo& InOutViewInfo) override;`
- L23 _public prototype_ `virtual bool ApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const FDisplayClusterProjectionEasyBlendPolicyViewInfo& InViewInfo, FRHITexture* InputTexture, FRHITexture* OutputTexture, FRHIViewport* InRHIViewport) override;`
- L27 _protected prototype_ `void ImplRelease();`
- L31 _private member_ `TUniquePtr<EasyBlend1SDKDX_Mesh> EasyBlendMeshData;` — The unique EasyBlend data that useed for warpblend

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/EasyBlend/Windows/DX12/DisplayClusterProjectionEasyBlendLibraryDX12.h` (Private)


#### class `FDisplayClusterProjectionEasyBlendLibraryDX12`  
`class FDisplayClusterProjectionEasyBlendLibraryDX12`  
_L16-52_
- desc: Implement access to EasyBlend DX12 DLL functions The basic idea is to load the DLL dynamically without using LIB files The DLL function is described in the file ./ThirdParty/EasyBlendDX12/Include/EasyBlendSDKDXApi.h
- L19 _public prototype_ `FDisplayClusterProjectionEasyBlendLibraryDX12();`
- L20 _public prototype_ `~FDisplayClusterProjectionEasyBlendLibraryDX12();`
- L23 _public prototype_ `static TSharedRef<FDisplayClusterProjectionEasyBlendLibraryDX12, ESPMode::ThreadSafe>& Get();` — Return EaxyBlend DX12 library api.
- L26 _public function_ `inline bool IsInitialized() const` — If the DLL is loaded correctly, this function returns true.
- L32 _public prototype_ `DeclareEasyBlendFunc(EasyBlendSDK_Initialize);`
- L33 _public prototype_ `DeclareEasyBlendFunc(EasyBlendSDK_Uninitialize);`
- L35 _public prototype_ `DeclareEasyBlendFunc(EasyBlendSDK_SetEyepoint);`
- L36 _public prototype_ `DeclareEasyBlendFunc(EasyBlendSDK_GetHeadingPitchRoll);`
- L38 _public prototype_ `DeclareEasyBlendFunc(EasyBlendSDK_InitializeDX12_Device);`
- L39 _public prototype_ `DeclareEasyBlendFunc(EasyBlendSDK_TransformInputToOutputDX12_CommandList);`
- L43 _private prototype_ `bool InitializeDLL();` — Imprort all functionf from EasyBlend DLL. Return true on success.
- L44 _private prototype_ `void ReleaseDLL();`
- L48 _private member_ `bool bInitialized = false;` — Initializetion state
- L51 _private member_ `void* EasyBlend_DLL_Handler = nullptr;` — Saved handle to EasyBlend DLL

#### Free symbols / members of external scopes

- L8 _macro_ `#define DeclareEasyBlendFunc(DLLFunc) DLLFunc##Proc DLLFunc = nullptr;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/EasyBlend/Windows/DX12/DisplayClusterProjectionEasyBlendLibraryDX12Types.h` (Private)


#### Free symbols / members of external scopes

- L27 _typedef_ `typedef EasyBlendSDKError(__stdcall* EasyBlendSDK_InitializeProc)(const char* Filename, EasyBlendSDK_Mesh* msm, int SDKMode, EasyBlendSDKCallback cb,void* cbData);` — Initializes a Mesh structure from an EasyBlend calibration file (typically a .ol file or .pol file for dynamic eyepoint). For OpenGL, this call MUST be made when a valid OpenGL context has been created. Otherwise the EasyBlend SDK will conclude that you only have OpenGL 1.0 support. The given Mesh pointer should be allocated ( not NULL ) and will be overwritten. @param Filename @param msm @param SDKMode @param cb @param cbData
- L39 _typedef_ `typedef EasyBlendSDKError(__stdcall* EasyBlendSDK_UninitializeProc)(EasyBlendSDK_Mesh* msm, EasyBlendSDKCallback cb, void* cbData);` — Given a correctly initialized SDK Mesh, releases the resources used by the Mesh structure.  The Mesh pointer memory must still be externally deallocated after this call. @param msm @param cb @param cbData
- L47 _typedef_ `typedef EasyBlendSDKError(__stdcall* EasyBlendSDK_InitializeDX12_DeviceProc)(EasyBlendSDK_Mesh* msm, ID3D12Device* pDevice);` — Initialize the DX12 renderer @param msm           - EasyBlend SDK mesh initialized using EasyBlendSDK_SDKMODE_DX12 @param pDevice       - D3D12 device object pointer
- L60 _typedef_ `typedef EasyBlendSDKError(__stdcall* EasyBlendSDK_TransformInputToOutputDX12_CommandListProc)(EasyBlendSDK_Mesh* msm, ID3D12Resource* InputTexture, ID3D12Resource* OutputTexture, D3D12_CPU_DESCRIPTOR_HANDLE OutputRTV, ID3D12GraphicsCommandList* pCommandList);` — Fill a given command list with commands that will warp the image on the back buffer and write the warped image back into the same buffer.  The swap chain provided to EasyBlendSDK_InitializeDX12 will be used to obtain the current backbuffer resource. This resource will be assumed to be in the state D3D12_RESOURCE_STATE_PRESENT and will be returned to that state after executing the command list.  Caller is responsible for executing the command list on the appropriate command queue and then calling present. @param msm       - EasyBlend SDK mesh initialized using EasyBlendSDK_SDKMODE_DX12 @param pCmdQueue - D3D12 command list that is ready to accept commands
- L72 _typedef_ `typedef EasyBlendSDKError(__stdcall* EasyBlendSDK_GetHeadingPitchRollProc)(double& rdDegreesHeading, double& rdDegreesPitch, double& rdDegreesRoll, EasyBlendSDK_Mesh* msm);` — This command returns the view angles for the instance of the SDK. As Heading, then Pitch then Roll. The Angles are pre-computed in the SDK file, so that it only works with newer version of EasyBlend that write this information to disk. (Newer than Nov 2011 or newer) @param rdDegreesHeading - (out) yaw @param rdDegreesPitch   - (out) pitch @param rdDegreesRoll    - (out) roll @param msm              - EasyBlend SDK mesh
- L87 _typedef_ `typedef EasyBlendSDKError(__stdcall* EasyBlendSDK_SetEyepointProc)(EasyBlendSDK_Mesh* msm, const double& eyeX, const double& eyeY, const double& eyeZ);` — This comand is used only for Dynamic Eyepoint. The new location of the viewer is sent to the command, and a new frustum is calculated. To use this function, the Inititalize command must have been called with a .pol file. After this call, remember to get new frustum and use it to update the frustum. This command is currently CPU bound. @param msm  - EasyBlend SDK mesh @param eyeX - eye X position @param eyeY - eye Y position @param eyeZ - eye Z position

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/EasyBlend/Windows/DX12/DisplayClusterProjectionEasyBlendPolicyViewDataDX12.h` (Private)


#### class `FDisplayClusterProjectionEasyBlendPolicyViewDataDX12`  
`class FDisplayClusterProjectionEasyBlendPolicyViewDataDX12 : public IDisplayClusterProjectionEasyBlendPolicyViewData , public TSharedFromThis<FDisplayClusterProjectionEasyBlendPolicyViewDataDX12, ESPMode::ThreadSafe>`  
_L11-34_
- inherits: `IDisplayClusterProjectionEasyBlendPolicyViewData,TSharedFromThis<FDisplayClusterProjectionEasyBlendPolicyViewDataDX12,ESPMode::ThreadSafe>`
- desc: The DX12 implementation for EasyBlend
- L16 _public prototype_ `~FDisplayClusterProjectionEasyBlendPolicyViewDataDX12();`
- L20 _public prototype_ `virtual bool Initialize(const FDisplayClusterProjectionEasyBlendPolicyConfiguration& InEasyBlendConfiguration) override;` — BEGIN ~IDisplayClusterProjectionEasyBlendPolicyViewData
- L21 _public prototype_ `virtual bool CalculateWarpBlend(FDisplayClusterProjectionEasyBlendPolicyViewInfo& InOutViewInfo) override;`
- L22 _public prototype_ `virtual bool ApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const FDisplayClusterProjectionEasyBlendPolicyViewInfo& InViewInfo, FRHITexture* InputTexture, FRHITexture* OutputTexture, FRHIViewport* InRHIViewport) override;`
- L24 _public function_ `virtual bool HasPreviewMesh() override`
- L25 _public prototype_ `virtual bool GetPreviewMeshGeometry(const FDisplayClusterProjectionEasyBlendPolicyConfiguration& InEasyBlendConfiguration, FDisplayClusterProjectionEasyBlendGeometryExportData& OutMeshData) override;`
- L29 _protected prototype_ `void ImplRelease();`
- L33 _private member_ `TUniquePtr<EasyBlendSDK_Mesh> EasyBlendMeshData;` — The unique EasyBlend data that useed for warpblend

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Link/DisplayClusterProjectionLinkPolicy.h` (Private)


#### class `FDisplayClusterProjectionLinkPolicy`  
`class FDisplayClusterProjectionLinkPolicy : public FDisplayClusterProjectionPolicyBase`  
_L13-39_
- inherits: `FDisplayClusterProjectionPolicyBase`
- desc: Link projection policy (for internal usage)
- L17 _public prototype_ `FDisplayClusterProjectionLinkPolicy(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy);`
- L23 _public prototype_ `virtual const FString& GetType() const override;`
- L27 _public prototype_ `virtual bool CalculateView(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& ViewOffset, const float WorldToMeters, const float NCP, const float FCP) override;` — Return values from linked parent viewport Important note: before doing this, the parent viewports must be updated.
- L28 _public prototype_ `virtual bool GetProjectionMatrix(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FMatrix& OutPrjMatrix) override;`
- L29 _public prototype_ `virtual void SetupProjectionViewPoint(IDisplayClusterViewport* InViewport, const float InDeltaTime, FMinimalViewInfo& InOutViewInfo, float* OutCustomNearClippingPlane = nullptr) override;`
- L31 _public function_ `virtual bool ShouldUseSourceTextureWithMips(const IDisplayClusterViewport* InViewport) const override`
- L38 _private prototype_ `const FString& GetParentViewport(IDisplayClusterViewport* InViewport) const;` — Get parent viewport name.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Link/DisplayClusterProjectionLinkPolicyFactory.h` (Private)


#### class `FDisplayClusterProjectionLinkPolicyFactory`  
`class FDisplayClusterProjectionLinkPolicyFactory : public IDisplayClusterProjectionPolicyFactory , protected FDisplayClusterProjectionPolicyFactoryBase`  
_L13-21_
- inherits: `IDisplayClusterProjectionPolicyFactory,FDisplayClusterProjectionPolicyFactoryBase`
- desc: Factory for the 'link' projection policy (internal use only). A linked viewport inherits its view and projection matrix from a designated parent viewport instead of computing them independently.
- L19 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> Create(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/MPCDI/DisplayClusterProjectionMPCDIPolicy.h` (Private)


#### class `FDisplayClusterProjectionMPCDIPolicy`  
`class FDisplayClusterProjectionMPCDIPolicy : public FDisplayClusterProjectionPolicyBase , public TSharedFromThis<FDisplayClusterProjectionMPCDIPolicy, ESPMode::ThreadSafe>`  
_L16-112_
- inherits: `FDisplayClusterProjectionPolicyBase,TSharedFromThis<FDisplayClusterProjectionMPCDIPolicy,ESPMode::ThreadSafe>`
- desc: MPCDI projection policy Supported load from 'MPCDI' and 'PFM' files
- L21 _public prototype_ `FDisplayClusterProjectionMPCDIPolicy(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy);`
- L22 _public prototype_ `virtual ~FDisplayClusterProjectionMPCDIPolicy();`
- L26 _public prototype_ `virtual bool ShouldSupportICVFX(const IDisplayClusterViewport* InViewport) const override;` — This policy can support ICVFX rendering
- L30 _public prototype_ `virtual const FString& GetType() const override;`
- L32 _public prototype_ `virtual bool HandleStartScene(IDisplayClusterViewport* InViewport) override;`
- L33 _public prototype_ `virtual void HandleEndScene(IDisplayClusterViewport* InViewport) override;`
- L35 _public prototype_ `virtual bool CalculateView(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& ViewOffset, const float WorldToMeters, const float NCP, const float FCP) override;`
- L36 _public prototype_ `virtual bool GetProjectionMatrix(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FMatrix& OutPrjMatrix) override;`
- L38 _public prototype_ `virtual bool IsFrustumRotatedToFitContextSize(IDisplayClusterViewport* InViewport, const uint32 InContextNum) override;`
- L39 _public prototype_ `virtual bool IsFrustumRotatedToFitContextSize_RenderThread(const IDisplayClusterViewportProxy* InViewportProxy, const uint32 InContextNum) override;`
- L41 _public prototype_ `virtual bool IsWarpBlendSupported(const IDisplayClusterViewport* InViewport) const override;`
- L42 _public prototype_ `virtual bool IsWarpBlendSupported_RenderThread(const IDisplayClusterViewportProxy* InViewportProxy) const override;`
- L44 _public prototype_ `virtual void ApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* InViewportProxy) override;`
- L46 _public prototype_ `virtual bool GetWarpBlendInterface(TSharedPtr<class IDisplayClusterWarpBlend, ESPMode::ThreadSafe>& OutWarpBlendInterface) const override;`
- L47 _public prototype_ `virtual bool GetWarpBlendInterface_RenderThread(TSharedPtr<class IDisplayClusterWarpBlend, ESPMode::ThreadSafe>& OutWarpBlendInterfaceProxy) const override;`
- L49 _public function_ `virtual bool ShouldUseSourceTextureWithMips(const IDisplayClusterViewport* InViewport) const override`
- L55 _public function_ `virtual bool ShouldUseAdditionalTargetableResource(const IDisplayClusterViewport* InViewport) const override`
- L61 _public function_ `virtual EDisplayClusterProjectionPolicyFlags GetProjectionPolicyFlags(const IDisplayClusterViewport* InViewport, const uint32 InContextNum) const override`
- L68 _public prototype_ `virtual void UpdateProxyData(IDisplayClusterViewport* InViewport) override;`
- L70 _public prototype_ `virtual void SetWarpPolicy(IDisplayClusterWarpPolicy* InWarpPolicy) override;`
- L71 _public prototype_ `virtual IDisplayClusterWarpPolicy* GetWarpPolicy() const override;`
- L72 _public prototype_ `virtual IDisplayClusterWarpPolicy* GetWarpPolicy_RenderThread() const override;`
- L74 _public prototype_ `virtual bool HasPreviewMesh(IDisplayClusterViewport* InViewport) override;`
- L75 _public prototype_ `virtual UMeshComponent* GetOrCreatePreviewMeshComponent(IDisplayClusterViewport* InViewport, bool& bOutIsRootActorComponent) override;`
- L77 _public prototype_ `virtual bool HasPreviewEditableMesh(IDisplayClusterViewport* InViewport) override;`
- L78 _public prototype_ `virtual UMeshComponent* GetOrCreatePreviewEditableMeshComponent(IDisplayClusterViewport* InViewport) override;`
- L79 _public prototype_ `virtual USceneComponent* const GetPreviewEditableMeshOriginComponent(IDisplayClusterViewport* InViewport) const override;`
- L84 _protected prototype_ `bool CreateWarpBlendFromConfig(IDisplayClusterViewport* InViewport);`
- L85 _protected prototype_ `void ImplRelease();`
- L89 _protected member_ `TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> WarpBlendInterface;` — GameThread: WarpBlend and WarpPolicy interfaces
- L90 _protected member_ `TSharedPtr<IDisplayClusterWarpPolicy, ESPMode::ThreadSafe> WarpPolicyInterface;`
- L93 _protected member_ `TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> WarpBlendInterface_Proxy;` — RenderingThread: WarpBlend and WarpPolicy interfaces
- L94 _protected member_ `TSharedPtr<IDisplayClusterWarpPolicy, ESPMode::ThreadSafe> WarpPolicyInterface_Proxy;`
- L97 _protected member_ `TArray<FDisplayClusterWarpContext> WarpBlendContexts;` — Context for both game and rendering threads
- L98 _protected member_ `TArray<FDisplayClusterWarpContext> WarpBlendContexts_Proxy;`
- L100 _protected member_ `bool bInvalidConfiguration = false;`
- L101 _protected member_ `bool bIsPreviewMeshEnabled = false;`
- L105 _private member_ `FDisplayClusterSceneComponentRef PreviewMeshComponentRef;` — Stored value of the preview mesh
- L108 _private member_ `bool bIsRootActorHasPreviewMeshComponent = false;` — Stored value of the preview meshes belonging flag. True if this component exists in DCRA and cannot be deleted with preview.
- L111 _private member_ `FDisplayClusterSceneComponentRef PreviewEditableMeshComponentRef;` — Stored value of the editable preview mesh

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/MPCDI/DisplayClusterProjectionMPCDIPolicyFactory.h` (Private)


#### class `FDisplayClusterProjectionMPCDIPolicyFactory`  
`class FDisplayClusterProjectionMPCDIPolicyFactory : public IDisplayClusterProjectionPolicyFactory , protected FDisplayClusterProjectionPolicyFactoryBase`  
_L13-21_
- inherits: `IDisplayClusterProjectionPolicyFactory,FDisplayClusterProjectionPolicyFactoryBase`
- desc: Factory for the 'mpcdi' and 'mesh' projection policies. 'mpcdi' loads warp and blend data from an MPCDI calibration file; 'mesh' drives warp from a UE mesh component instead.
- L19 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> Create(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/MPCDI/DisplayClusterProjectionMPCDIPolicy_Config.h` (Private)


#### struct `FDisplayClusterProjectionMPCDIPolicy_ConfigParser`  
`struct FDisplayClusterProjectionMPCDIPolicy_ConfigParser`  
_L16-95_
- desc: MPCDI projection policy configuration parser
- L19 _public member_ `FString MPCDIFileName;` — Name of the MPCDI file that is used as the data source
- L22 _public member_ `FString BufferId;` — Name of the buffer inside the MPCDI file that will be used as the data source
- L25 _public member_ `FString RegionId;` — Name of the region inside the MPCDI file that will be used as the data source
- L28 _public member_ `FString OriginType;` — The origin point name
- L31 _public member_ `FDisplayClusterWarpMPCDIAttributes MPCDIAttributes;` — Todo: fill this data from InConfigParameters
- L34 _public member_ `UDisplayClusterScreenComponent* ScreenComponent = nullptr;` — Screen component with source geometry
- L37 _public member_ `UDisplayClusterScreenComponent* PreviewScreenComponent = nullptr;` — Screen component with source geometry used as a preview mesh
- L40 _public member_ `FString PFMFile;` — Name of the PFM file that is used as the data source
- L43 _public member_ `float PFMFileScale = 1;` — Scale unit of the PFM file geometry
- L46 _public member_ `bool bIsUnrealGameSpace = false;` — Are the axes of the PFM geometry the same as in UE
- L49 _public member_ `FString AlphaFile;` — Filename of the image to be used as an AlphaMap
- L51 _public member_ `float AlphaGamma = 1;` — Gamma used for the AlphaMap image
- L54 _public member_ `FString BetaFile;` — Filename of the image to be used as an BetaMap
- L57 _public member_ `bool bEnablePreview = false;` — The preview geometry must be imported from the PFM\MPCDI file and displayed.
- L65 _public prototype_ `FDisplayClusterProjectionMPCDIPolicy_ConfigParser(IDisplayClusterViewport* InViewport, const TMap<FString, FString>& InConfigParameters);` — Read MPCDI policy configuration from projection policy parameters @param InViewport         - the projection policy owner viewport @param InConfigParameters - the projection policy parameters
- L68 _public function_ `inline bool IsValid() const` — When this configuration is valid, it returns true.
- L75 _private prototype_ `bool ReadConfig();` — Implementation of reading the configuration from the parameters.
- L78 _private prototype_ `bool ImplGetBaseConfig();` — Implementation of reading basic parameters.
- L81 _private prototype_ `bool ImplGetMPCDIConfig();` — Implementation of parameter reading for the case when we initialize from an MPCDI file.
- L84 _private prototype_ `bool ImplGetPFMConfig();` — Implementation of parameter reading for the case when we initialize from an PFM file.
- L88 _private member_ `const TMap<FString, FString>& ConfigParameters;` — The projection policy parameters used to read this configuration
- L91 _private member_ `TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe> Viewport;` — The projection policy owner viewport
- L94 _private member_ `bool bValid = false;` — Is this configuration valid.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Manual/DisplayClusterProjectionManualPolicy.h` (Private)


#### class `FDisplayClusterProjectionManualPolicy`  
`class FDisplayClusterProjectionManualPolicy : public FDisplayClusterProjectionPolicyBase`  
_L11-65_
- inherits: `FDisplayClusterProjectionPolicyBase`
- desc: Manual projection policy
- L15 _public prototype_ `FDisplayClusterProjectionManualPolicy(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy);`
- L24 _public function_ `EManualDataType GetDataType() const`
- L33 _public prototype_ `virtual const FString& GetType() const override;`
- L34 _public prototype_ `virtual bool HandleStartScene(IDisplayClusterViewport* InViewport) override;`
- L35 _public prototype_ `virtual bool CalculateView(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& InViewOffset, const float InWorldToMeters, const float InNCP, const float InFCP) override;`
- L36 _public prototype_ `virtual bool GetProjectionMatrix(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FMatrix& OutPrjMatrix) override;`
- L37 _public prototype_ `virtual void SetupProjectionViewPoint(IDisplayClusterViewport* InViewport, const float InDeltaTime, FMinimalViewInfo& InOutViewInfo, float* OutCustomNearClippingPlane = nullptr) override;`
- L48 _protected prototype_ `virtual bool ExtractAngles(const FString& InAngles, FFrustumAngles& OutAngles);`
- L51 _private prototype_ `EManualDataType DataTypeFromString(IDisplayClusterViewport* InViewport, const FString& DataTypeInString) const;`
- L55 _private member_ `EManualDataType DataType = EManualDataType::Matrix;` — Current data type (matrix, frustum angle, ...)
- L57 _private member_ `FRotator ViewRotation = FRotator::ZeroRotator;` — View rotation
- L59 _private member_ `FMatrix ProjectionMatrix[2] = { FMatrix::Identity };` — Projection matrix
- L61 _private member_ `FFrustumAngles FrustumAngles[2];` — Frustum angles
- L63 _private member_ `float NCP;` — Near/far clip planes
- L64 _private member_ `float FCP;`

#### enum `FDisplayClusterProjectionManualPolicy::EManualDataType`  
`enum class EManualDataType`  
_L18-22_
- L20 _public enumerator_ `Matrix`
- L21 _public enumerator_ `FrustumAngles`

#### struct `FDisplayClusterProjectionManualPolicy::FFrustumAngles`  
`struct FFrustumAngles`  
_L40-46_
- L42 _public member_ `float Left = -30.f;`
- L43 _public member_ `float Right = 30.f;`
- L44 _public member_ `float Top = 30.f;`
- L45 _public member_ `float Bottom = -30.f;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Manual/DisplayClusterProjectionManualPolicyFactory.h` (Private)


#### class `FDisplayClusterProjectionManualPolicyFactory`  
`class FDisplayClusterProjectionManualPolicyFactory : public IDisplayClusterProjectionPolicyFactory , protected FDisplayClusterProjectionPolicyFactoryBase`  
_L11-20_
- inherits: `IDisplayClusterProjectionPolicyFactory,FDisplayClusterProjectionPolicyFactoryBase`
- desc: Implements projection policy factory for the 'manual' policy
- L19 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> Create(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Mesh/DisplayClusterProjectionMeshPolicy.h` (Private)


#### class `FDisplayClusterProjectionMeshPolicy`  
`class FDisplayClusterProjectionMeshPolicy : public FDisplayClusterProjectionMPCDIPolicy`  
_L15-41_
- inherits: `FDisplayClusterProjectionMPCDIPolicy`
- desc: Mesh projection policy Supported geometry sources - StaticMeshComponent, ProceduralMeshComponent
- L19 _public prototype_ `FDisplayClusterProjectionMeshPolicy(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy);`
- L25 _public prototype_ `virtual const FString& GetType() const override;`
- L26 _public prototype_ `virtual bool HandleStartScene(IDisplayClusterViewport* InViewport) override;`
- L30 _public prototype_ `bool CreateWarpMeshInterface(IDisplayClusterViewport* InViewport);` — Parse the config data for a mesh id and try to retrieve it from the root actor.
- L40 _private prototype_ `bool GetWarpMeshConfiguration(IDisplayClusterViewport* InViewport, struct FDisplayClusterProjectionMeshPolicyConfiguration& OutWarpCfg);` — Read mesh policy configuration from the projection policy parameters @param InViewport - projection policy owner viewport @param OutWarpCfg - (out) warpblend configuration @return - true when successful.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Reference/DisplayClusterProjectionReferencePolicy.h` (Private)


#### enum `EDisplayClusterProjectionReferencePolicyLogMsgState`  
`enum class EDisplayClusterProjectionReferencePolicyLogMsgState : uint8`  
_L10-22_
- desc: Enum flags used to mark log messages after they have been displayed.
- L12 _public enumerator_ `None = 0`
- L15 _public enumerator_ `LocalNode = 1 << 0` — The referenced viewport should be on the same cluster node.
- L18 _public enumerator_ `Recursion= 1 << 1` — The viewport we are referencing cannot reference another viewport or use this projection policy.
- L21 _public enumerator_ `InvalidName = 1 << 2` — The viewport referenced does not exist.

#### class `FDisplayClusterProjectionReferencePolicy`  
`class FDisplayClusterProjectionReferencePolicy : public FDisplayClusterProjectionPolicyBase , public TSharedFromThis<FDisplayClusterProjectionReferencePolicy, ESPMode::ThreadSafe>`  
_L28-97_
- inherits: `FDisplayClusterProjectionPolicyBase,TSharedFromThis<FDisplayClusterProjectionReferencePolicy,ESPMode::ThreadSafe>`
- desc: Link projection policy (for internal usage)
- L33 _public prototype_ `FDisplayClusterProjectionReferencePolicy( const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy);`
- L39 _public prototype_ `virtual const FString& GetType() const override;`
- L41 _public prototype_ `virtual bool ShouldSupportICVFX(const IDisplayClusterViewport* InViewport) const override;`
- L42 _public prototype_ `virtual void PostUpdateBaseConfiguration(IDisplayClusterViewport* InViewport) const override;`
- L44 _public prototype_ `virtual bool IsWarpBlendSupported(const IDisplayClusterViewport* InViewport) const override;`
- L45 _public prototype_ `virtual bool IsWarpBlendSupported_RenderThread(const IDisplayClusterViewportProxy* InViewportProxy) const override;`
- L47 _public prototype_ `virtual void ApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* InViewportProxy) override;`
- L49 _public prototype_ `virtual bool ShouldUseSourceTextureWithMips(const IDisplayClusterViewport* InViewport) const override;`
- L50 _public prototype_ `virtual bool ShouldUseAdditionalTargetableResource(const IDisplayClusterViewport* InViewport) const override;`
- L52 _public prototype_ `virtual EDisplayClusterProjectionPolicyFlags GetProjectionPolicyFlags(const IDisplayClusterViewport* InViewport, const uint32 InContextNum) const override;`
- L54 _public prototype_ `virtual void UpdateProxyData(IDisplayClusterViewport* InViewport) override;`
- L56 _public function_ `virtual bool CalculateView( IDisplayClusterViewport* InViewport, const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& ViewOffset, const float WorldToMeters, const float NCP, const float FCP) override`
- L70 _public function_ `virtual bool GetProjectionMatrix( IDisplayClusterViewport* InViewport, const uint32 InContextNum, FMatrix& OutPrjMatrix) override`
- L82 _protected prototype_ `IDisplayClusterViewport* GetSourceViewport(const IDisplayClusterViewport* InViewport) const;` — Return viewport referenced by this policy.
- L85 _protected prototype_ `IDisplayClusterViewportProxy* GetSourceViewport_RenderThread(const IDisplayClusterViewportProxy* InViewportProxy) const;` — Return viewport proxy referenced by this policy.
- L89 _private member_ `FString ReferencedViewportId;` — The name of the viewport referenced by this policy.
- L90 _private member_ `FString ReferencedViewportId_RenderThread;`
- L93 _private member_ `mutable EDisplayClusterProjectionReferencePolicyLogMsgState LogMsgState = EDisplayClusterProjectionReferencePolicyLogMsgState::None;` — Allow a message to be displayed in the log only once.
- L94 _private member_ `mutable EDisplayClusterProjectionReferencePolicyLogMsgState LogMsgState_RenderThread = EDisplayClusterProjectionReferencePolicyLogMsgState::None;`
- L96 _private member_ `bool bSupportICVFXProxy = false;`

#### Free symbols / members of external scopes

- L23 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterProjectionReferencePolicyLogMsgState);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/Reference/DisplayClusterProjectionReferencePolicyFactory.h` (Private)


#### class `FDisplayClusterProjectionReferencePolicyFactory`  
`class FDisplayClusterProjectionReferencePolicyFactory : public IDisplayClusterProjectionPolicyFactory , protected FDisplayClusterProjectionPolicyFactoryBase`  
_L11-21_
- inherits: `IDisplayClusterProjectionPolicyFactory,FDisplayClusterProjectionPolicyFactoryBase`
- desc: Implements projection policy factory for the 'Reference' policy
- L17 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> Create( const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/VIOSO/DisplayClusterProjectionVIOSOGeometryExportData.h` (Private)


#### class `FDisplayClusterProjectionVIOSOGeometryExportData`  
`class FDisplayClusterProjectionVIOSOGeometryExportData`  
_L10-48_
- L13 _public function_ `FDisplayClusterProjectionVIOSOGeometryExportData(const FString& InUniqueName) : UniqueName(InUniqueName)`
- L18 _public prototype_ `void GenerateVIOSOGeometryNormals();` — Generate normals.
- L23 _public prototype_ `static int32 GetDataCacheTimeOutInFrames();` — Return DataCache timeout in frames.
- L26 _public prototype_ `static bool IsDataCacheEnabled();` — Return true if DataCache is enabled.
- L29 _public function_ `inline const FString& GetDataCacheName() const` — Returns the unique name of this MPCDI file resource for DataCache.
- L35 _public function_ `inline void ReleaseDataCacheItem()` — Method for releasing a cached data item, called before its destructor.
- L39 _public prototype_ `static TSharedPtr<FDisplayClusterProjectionVIOSOGeometryExportData, ESPMode::ThreadSafe> Create(const TSharedRef<FDisplayClusterProjectionVIOSOLibrary, ESPMode::ThreadSafe>& InVIOSOLibrary, const FViosoPolicyConfiguration& InConfigData);`
- L42 _public member_ `const FString UniqueName;`
- L44 _public member_ `TArray<FVector> Vertices;`
- L45 _public member_ `TArray<FVector> Normal;`
- L46 _public member_ `TArray<FVector2D> UV;`
- L47 _public member_ `TArray<int32> Triangles;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/VIOSO/DisplayClusterProjectionVIOSOLibrary.h` (Private)


#### class `FDisplayClusterProjectionVIOSOLibrary`  
`class FDisplayClusterProjectionVIOSOLibrary`  
_L15-58_
- desc: Implement access to VIOSO DLL functions The basic idea is to load the DLL dynamically without using LIB files The DLL function is described in the file //nDisplay/Source/ThirdParty/VIOSO/Include/VIOSOWarpBlend.h Supported: IDirect3DDevice9,IDirect3DDevice9Ex,ID3D10Device,ID3D10Device1,ID3D11Device,ID3D12CommandQueue (for ID3D12Device initialization)
- L18 _public prototype_ `FDisplayClusterProjectionVIOSOLibrary();`
- L19 _public prototype_ `~FDisplayClusterProjectionVIOSOLibrary();`
- L22 _public function_ `inline bool IsInitialized() const` — If the DLL is loaded correctly, this function returns true.
- L30 _public prototype_ `DeclareVIOSOFunc(VWB_getVersion);`
- L32 _public prototype_ `DeclareVIOSOFunc(VWB_CreateA);`
- L33 _public prototype_ `DeclareVIOSOFunc(VWB_Destroy);`
- L34 _public prototype_ `DeclareVIOSOFunc(VWB_Init);`
- L35 _public prototype_ `DeclareVIOSOFunc(VWB_getViewClip);`
- L36 _public prototype_ `DeclareVIOSOFunc(VWB_getPosDirClip);`
- L37 _public prototype_ `DeclareVIOSOFunc(VWB_render);`
- L39 _public prototype_ `DeclareVIOSOFunc(VWB_getWarpBlendMesh);`
- L40 _public prototype_ `DeclareVIOSOFunc(VWB_destroyWarpBlendMesh);`
- L43 _public member_ `FCriticalSection DllAccessCS;` — Protect VIOSO SDK calls: the DLL is not thread-safe.
- L47 _private prototype_ `bool InitializeDLL();` — Imprort all functionf from VIOSO DLL. Return true on success.
- L48 _private prototype_ `void ReleaseDLL();`
- L54 _private member_ `bool bInitialized = false;` — Initializetion state
- L57 _private member_ `void* VIOSO_DLL_Handler = nullptr;` — Saved handle to VIOSO DLL

#### Free symbols / members of external scopes

- L6 _macro_ `#define DeclareVIOSOFunc(DLLFunc) DLLFunc##Proc DLLFunc = nullptr;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/VIOSO/DisplayClusterProjectionVIOSOPolicyFactory.h` (Private)


#### class `FDisplayClusterProjectionVIOSOPolicyFactory`  
`class FDisplayClusterProjectionVIOSOPolicyFactory : public IDisplayClusterProjectionPolicyFactory , protected FDisplayClusterProjectionPolicyFactoryBase`  
_L14-29_
- inherits: `IDisplayClusterProjectionPolicyFactory,FDisplayClusterProjectionPolicyFactoryBase`
- desc: Factory for the 'VIOSO' projection policy (Windows only). Creates policies backed by the VIOSO warping and blending library. The factory owns the shared VIOSO library instance; policy creation fails if the library is unavailable or not yet initialized.
- L19 _public prototype_ `FDisplayClusterProjectionVIOSOPolicyFactory();`
- L20 _public prototype_ `virtual ~FDisplayClusterProjectionVIOSOPolicyFactory() = default;`
- L24 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> Create(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) override;`
- L28 _private member_ `TSharedPtr<class FDisplayClusterProjectionVIOSOLibrary, ESPMode::ThreadSafe> VIOSOLibrary;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/VIOSO/DisplayClusterProjectionVIOSOTypes.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define WITH_VIOSO_LIBRARY 1`
- L26 _typedef_ `typedef VWB_ERROR(__stdcall* VWB_getVersionProc)(VWB_int* major, VWB_int* minor, VWB_int* maintenance, VWB_int* build);` — Get the version of the API @param major       - (out) major version @param minor       - (out) minor version @param maintenance - (out) maintenance revision @param build       - (out) build number @return VWB_ERROR_NONE on success, VWB_ERROR_PARAMETER, if parameters are out of range
- L47 _typedef_ `typedef VWB_ERROR(__stdcall * VWB_CreateAProc)(void* pDxDevice, char const* szConfigFile, char const* szChannelName, VWB_Warper** ppWarper, VWB_int logLevel, char const* szLogFile);` — Creates a new VIOSO Warp & Blend API instance @param pDxDevice     - a pointer to a DirectX device for Direct3D 9 to 11; for Direct3D 12, you need to specify a pointer to a ID3D12CommandQueue, set to NULL for OpenGL, set to VWB_DUMMYDEVICE, to just hold the data to create a textured mesh. @param szConfigFile  - path to a .ini file containing settings, if NULL the default values are used @param szChannelName -  a section name to look for in .ini-file. @param ppWarper      - (out) this receives the warper @param logLevel      - set a log level. @param logFile       - set a log file. @return VWB_ERROR_NONE on success, otherwise @see VWB_ERROR @remarks Default settings are loaded, then, if a .ini file is given, the settings are updated. If there is a [default] section, values are loaded from there, before individual settings are loaded. After creating, you are able to edit all settings. You may specify a logLevel in .ini, it overwrites given loglevel. You have to destroy a created warper using VWB_Destroy. After successful creation, call VWB_Init, to load .vwf file and initialize the warper.
- L52 _typedef_ `typedef void(__stdcall * VWB_DestroyProc)(VWB_Warper* pWarper);` — Destroys a warper @param pWarper - (in) a warper to be destroyed
- L60 _typedef_ `typedef VWB_ERROR(__stdcall* VWB_InitProc)(VWB_Warper* pWarper);` — Initializes a warper @param pWarper - a warper @remarks In case of an OpenGL warper, the later used context needs to be active. There is no multi-threading on side of VIOSO API.\
- L72 _typedef_ `typedef VWB_ERROR(__stdcall* VWB_getViewClipProc)(VWB_Warper* pWarper, VWB_float* pEye, VWB_float* pRot, VWB_float* pView, VWB_float* pClip);` — Set the new dynamic eye position and direction @param pWarper - (in)          a valid warper @param pEye    - (in,out, opt) sets the new eye position, if a eye point provider is present, the value is getted from there, pEye is updated @param pRot    - (in,out, opt) the new rotation in radian, if a eye point provider is present, the value is getted from there, pRot is updated @param pView   - (out)         it gets the updated view matrix to translate and rotate into the viewer's perspective @param pClip   - (out)         it gets the updated clip planes: left, top, right, bottom, near, far, where all components are usually positive @return VWB_ERROR_NONE on success, VWB_ERROR_GENERIC otherwise
- L87 _typedef_ `typedef VWB_ERROR(__stdcall* VWB_getPosDirClipProc)(VWB_Warper* pWarper, VWB_float* pEye, VWB_float* pRot, VWB_float* pPos, VWB_float* pDir, VWB_float* pClip, bool symmetric, VWB_float aspect);` — Set the new dynamic eye position and direction @param pWarper - (in)          a valid warper @param pEye    - (in,out, opt) sets the new eye position, if a eye point provider is present, the value is getted from there, pEye is updated @param pRot    - (in,out, opt) the new rotation in radian, if a eye point provider is present, the value is getted from there, pRot is updated @param pPos      (out)         it gets the updated relative position: x,y,z @param pDir      (out)         it gets the updated relative direction: euler angles around x,y,z rotation order is y,x,z @param pClip   - (out)         it gets the updated clip planes: left, top, right, bottom, near, far, where all components are usually positive @param symmetric (in opt)      set to true, to force symmetric frustum, NOTE: symmetric frusta are worse in quality, as the image plane is no longer parallel to the screen plane @param aspect    (in, opt)     set to some ratio, to force clip planes to form a rect with this ratio, if set to 0, optimal aspect ratio is used. NOTE: Non-optimal aspect ratia are worse in quality, as part of the input image is rendered but not used. @return VWB_ERROR_NONE on success, VWB_ERROR_GENERIC otherwise
- L101 _typedef_ `typedef VWB_ERROR(__stdcall* VWB_renderProc)(VWB_Warper* pWarper, VWB_param src, VWB_uint stateMask);` — Eender a warped and blended source texture into the current back buffer @param pWarper   - a valid warper @param pSrc      - the source texture, a IDirect3DTexture9*, ID3D10Texture2D*, ID3D11Texture2D*, VWB_D3D12_RENDERINPUT* or a GLint texture index; if current backbuffer must be read, set to NULL in any DX mode except 12 or to -1 in OpenGL mode in case of directX 12 you need to provide a @see VWB_D3D12_RENDERINPUT as parameter. @param stateMask - @see VWB_STATEMASK enumeration, default is 0 to restore usual stuff In D3D12 all flags except VWB_STATEMASK_CLEARBACKBUFFER are ignored. The application is required to set inputs and shader in each term anyway. @return VWB_ERROR_NONE on success, VWB_ERROR_GENERIC otherwise
- L112 _typedef_ `typedef VWB_ERROR(__stdcall* VWB_getWarpBlendMeshProc)(VWB_Warper* pWarper, VWB_int cols, VWB_int rows, VWB_WarpBlendMesh& mesh);` — Fills a VWB_WarpBlendMesh from currently loaded data. It uses cols * rows vertices or less depending on how .vwf is filled. Warper needs to be initialized as VWB_DUMMYDEVICE. @param pWarper - a valid warper @param cols    - sets the number of columns @param rows    - sets the number of rows @param mesh    - (out) the resulting mesh, the mesh will be emptied before filled @return VWB_ERROR_NONE on success, VWB_ERROR_PARAMETER, if parameters are out of range, VWB_ERROR_GENERIC otherwise\
- L121 _typedef_ `typedef VWB_ERROR(__stdcall* VWB_destroyWarpBlendMeshProc)(VWB_Warper* pWarper, VWB_WarpBlendMesh& mesh);` — Destroys a VWB_WarpBlendMesh @param pWarper - a valid warper @param mesh    - the mesh to be destroyed @return VWB_ERROR_NONE on success, VWB_ERROR_PARAMETER, if parameters are out of range, VWB_ERROR_GENERIC otherwise.
- L126 _macro_ `#define WITH_VIOSO_LIBRARY 0` — VIOSO library is not supported by the current platform

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/VIOSO/ViosoPolicyConfiguration.h` (Private)


#### struct `FViosoPolicyConfiguration`  
`struct FViosoPolicyConfiguration`  
_L12-42_
- desc: VIOSO projection policy configuration data
- L14 _public member_ `FString OriginCompId;`
- L16 _public member_ `FString INIFile;`
- L17 _public member_ `FString ChannelName;`
- L20 _public member_ `FString CalibrationFile;` — Calibration file and display segment with geometry
- L21 _public member_ `int32 CalibrationIndex = -1;`
- L24 _public member_ `float Gamma = 1.f;` — @todo add more vioso options, if required
- L27 _public member_ `float UnitsInMeter = 1000.f;` — How many VIOSO units in meter
- L30 _public member_ `bool bIsPreviewMeshEnabled = false;` — Allow to use preview mesh
- L33 _public member_ `int32 PreviewMeshWidth = 100;` — Preview mesh dimensions
- L34 _public member_ `int32 PreviewMeshHeight = 100;`
- L36 _public prototype_ `bool Initialize(const TMap<FString, FString>& InParameters, IDisplayClusterViewport* InViewport);`
- L41 _public prototype_ `FString ToString(const bool bOnlyGeometryParameters = false) const;` — convert all parameters to string

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/VIOSO/Windows/DisplayClusterProjectionVIOSOPolicy.h` (Private)


#### class `FDisplayClusterProjectionVIOSOPolicy`  
`class FDisplayClusterProjectionVIOSOPolicy : public FDisplayClusterProjectionPolicyBase , public TSharedFromThis<FDisplayClusterProjectionVIOSOPolicy, ESPMode::ThreadSafe>`  
_L12-82_
- inherits: `FDisplayClusterProjectionPolicyBase,TSharedFromThis<FDisplayClusterProjectionVIOSOPolicy,ESPMode::ThreadSafe>`
- desc: VIOSO projection policy
- L17 _public prototype_ `FDisplayClusterProjectionVIOSOPolicy(const FString& ProjectionPolicyId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy, const TSharedRef<FDisplayClusterProjectionVIOSOLibrary, ESPMode::ThreadSafe>& InVIOSOLibrary);`
- L18 _public prototype_ `virtual ~FDisplayClusterProjectionVIOSOPolicy();`
- L22 _public prototype_ `virtual const FString& GetType() const override;`
- L24 _public prototype_ `virtual bool HandleStartScene(IDisplayClusterViewport* InViewport) override;`
- L25 _public prototype_ `virtual void HandleEndScene(IDisplayClusterViewport* InViewport) override;`
- L27 _public prototype_ `virtual bool CalculateView(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& ViewOffset, const float WorldToMeters, const float NCP, const float FCP) override;`
- L28 _public prototype_ `virtual bool GetProjectionMatrix(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FMatrix& OutPrjMatrix) override;`
- L30 _public prototype_ `virtual bool IsWarpBlendSupported(const IDisplayClusterViewport* InViewport) const override;`
- L31 _public prototype_ `virtual bool IsWarpBlendSupported_RenderThread(const IDisplayClusterViewportProxy* InViewportProxy) const override;`
- L33 _public prototype_ `virtual void ApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* InViewportProxy) override;`
- L36 _public function_ `virtual bool ShouldUseAdditionalTargetableResource(const IDisplayClusterViewport* InViewport) const override` — Request additional targetable resources for domeprojection  external warpblend
- L41 _public function_ `virtual bool ShouldUseSourceTextureWithMips(const IDisplayClusterViewport* InViewport) const override`
- L46 _public prototype_ `virtual bool HasPreviewMesh(IDisplayClusterViewport* InViewport) override;`
- L47 _public prototype_ `virtual class UMeshComponent* GetOrCreatePreviewMeshComponent(IDisplayClusterViewport* InViewport, bool& bOutIsRootActorComponent) override;`
- L49 _public function_ `virtual float GetGeometryToMeters(const IDisplayClusterViewport* InViewport, const float InWorldToMeters) const override`
- L54 _public function_ `virtual EDisplayClusterProjectionPolicyFlags GetProjectionPolicyFlags(const IDisplayClusterViewport* InViewport, const uint32 InContextNum) const override`
- L61 _public prototype_ `virtual void UpdateProxyData(IDisplayClusterViewport* InViewport) override;`
- L66 _protected prototype_ `bool ImplApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* InViewportProxy);`
- L67 _protected prototype_ `void ImplRelease();`
- L71 _protected member_ `const TSharedRef<FDisplayClusterProjectionVIOSOLibrary, ESPMode::ThreadSafe> VIOSOLibrary;` — VIOSO DLL api
- L73 _protected member_ `FViosoPolicyConfiguration ViosoConfigData;`
- L76 _protected member_ `TArray<TSharedRef<FDisplayClusterProjectionVIOSOPolicyViewData, ESPMode::ThreadSafe>> PolicyViewData;` — View data owned and updated on the game thread
- L79 _protected member_ `TArray<TSharedRef<FDisplayClusterProjectionVIOSOPolicyViewData, ESPMode::ThreadSafe>> PolicyViewDataProxy;` — Snapshot of PolicyViewData pushed to the render thread each frame via UpdateProxyData()
- L81 _protected member_ `FDisplayClusterSceneComponentRef PreviewMeshComponentRef;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/VIOSO/Windows/DisplayClusterProjectionVIOSOPolicyViewData.h` (Private)


#### struct `FDisplayClusterProjectionVIOSOPolicyViewData`  
`struct FDisplayClusterProjectionVIOSOPolicyViewData : public TSharedFromThis<FDisplayClusterProjectionVIOSOPolicyViewData, ESPMode::ThreadSafe>`  
_L18-78_
- inherits: `TSharedFromThis<FDisplayClusterProjectionVIOSOPolicyViewData,ESPMode::ThreadSafe>`
- desc: VIOSO projection policy data
- L29 _public prototype_ `FDisplayClusterProjectionVIOSOPolicyViewData(const TSharedRef<FDisplayClusterProjectionVIOSOLibrary, ESPMode::ThreadSafe>& InVIOSOLibrary, const FViosoPolicyConfiguration& InConfigData, IDisplayClusterViewport* InViewport, const int32 InContextNum);`
- L30 _public prototype_ `virtual ~FDisplayClusterProjectionVIOSOPolicyViewData() = default;`
- L32 _public function_ `FDisplayClusterProjectionVIOSOPolicyViewData(const FDisplayClusterProjectionVIOSOPolicyViewData& In) : ViewLocation(In.ViewLocation) , ViewRotation(In.ViewRotation) , ProjectionMatrix(In.ProjectionMatrix) #if WITH_VIOSO_LIBRARY , WarperInterface(In.WarperInterface) #endif , RenderDevice(In.RenderDevice) , bInitialized(In.bInitialized) , UsedRenderTargetTexture(In.UsedRenderTargetTexture) , ClippingPlanes(In.ClippingPlanes)`
- L46 _public prototype_ `bool IsWarperInterfaceValid();`
- L48 _public function_ `bool IsViewDataValid()`
- L53 _public prototype_ `bool UpdateVIOSO(IDisplayClusterViewport* InViewport, const uint32 InContextNum, const FVector& LocalLocation, const FRotator& LocalRotator, const float WorldToMeters, const float NCP, const float FCP);`
- L54 _public prototype_ `bool RenderVIOSO_RenderThread(FRHICommandListImmediate& RHICmdList, FRHITexture* ShaderResourceTexture, FRHITexture* RenderTargetTexture);`
- L57 _protected prototype_ `bool InitializeVIOSO_RenderThread(FRHICommandListImmediate& RHICmdList, FRHITexture* RenderTargetTexture);`
- L60 _public member_ `FVector ViewLocation;`
- L61 _public member_ `FRotator ViewRotation;`
- L62 _public member_ `FMatrix ProjectionMatrix;`
- L67 _private member_ `const TSharedRef<FDisplayClusterProjectionVIOSOWarper, ESPMode::ThreadSafe> WarperInterface;` — VIOSO warper interface
- L70 _private member_ `ERenderDevice RenderDevice = ERenderDevice::Unsupported;`
- L72 _private member_ `bool bInitialized = false;`
- L75 _private member_ `FRHITexture* UsedRenderTargetTexture = nullptr;` — This RTT is used for VIOSO. If we change this resource, we need to re-initialize VIOSO
- L77 _private member_ `FVector2D ClippingPlanes;`

#### enum `FDisplayClusterProjectionVIOSOPolicyViewData::ERenderDevice`  
`enum class ERenderDevice : uint8`  
_L21-26_
- L23 _public enumerator_ `Unsupported = 0`
- L24 _public enumerator_ `D3D11`
- L25 _public enumerator_ `D3D12`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Private/Policy/VIOSO/Windows/DisplayClusterProjectionVIOSOWarper.h` (Private)


#### class `FDisplayClusterProjectionVIOSOWarper`  
`class FDisplayClusterProjectionVIOSOWarper`  
_L18-119_
- desc: Warper api for VIOSO
- L21 _public function_ `FDisplayClusterProjectionVIOSOWarper(const TSharedRef<FDisplayClusterProjectionVIOSOLibrary, ESPMode::ThreadSafe>& InVIOSOLibrary, const FViosoPolicyConfiguration& InVIOSOConfigData, const FString& InUniqueName) : VIOSOLibrary(InVIOSOLibrary) , VIOSOConfigData(InVIOSOConfigData) , UniqueName(InUniqueName)`
- L27 _public function_ `virtual ~FDisplayClusterProjectionVIOSOWarper()`
- L41 _public prototype_ `static TSharedRef<FDisplayClusterProjectionVIOSOWarper, ESPMode::ThreadSafe> Create(const TSharedRef<FDisplayClusterProjectionVIOSOLibrary, ESPMode::ThreadSafe>& InVIOSOLibrary, const FViosoPolicyConfiguration& InConfigData, const FString& InUniqueName);` — Constructor for VIOSO warper instances. (The cache is implemented inside) @param InVIOSOLibrary @param InConfigData @param InUniqueName is a unique viewname for the viewport (for ex.: "vp_1:0", "vp_1:1", "vp_2:0",...) @return an instance of the Warper class (the same object if InConfigData are equal).
- L44 _public function_ `inline bool IsInitialized() const`
- L49 _public prototype_ `bool Initialize(void* pDxDevice, const FVector2D& InClippingPLanes);`
- L50 _public prototype_ `void Release();`
- L52 _public prototype_ `void UpdateClippingPlanes(const FVector2D& InClippingPlanes);`
- L54 _public prototype_ `bool CalculateViewProjection(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, FMatrix& OutProjMatrix, const float WorldToMeters, const float NCP, const float FCP);`
- L56 _public prototype_ `bool Render(VWB_param RenderParam, VWB_uint StateMask);`
- L60 _public prototype_ `static int32 GetDataCacheTimeOutInFrames();` — Return DataCache timeout in frames.
- L63 _public prototype_ `static bool IsDataCacheEnabled();` — Return true if DataCache is enabled.
- L66 _public function_ `inline const FString& GetDataCacheName() const` — Returns the unique name of this MPCDI file resource for DataCache.
- L72 _public function_ `inline void ReleaseDataCacheItem()` — Method for releasing a cached data item, called before its destructor.
- L82 _protected prototype_ `bool ExportGeometry(FDisplayClusterProjectionVIOSOGeometryExportData& OutMeshData);` — Export warp mesh geometry from VIOSO file
- L86 _private prototype_ `FMatrix GetProjMatrix(IDisplayClusterViewport* InViewport, const uint32 InContextNum) const;`
- L90 _private member_ `const TSharedRef<FDisplayClusterProjectionVIOSOLibrary, ESPMode::ThreadSafe> VIOSOLibrary;` — VIOSO API
- L93 _private member_ `const FViosoPolicyConfiguration VIOSOConfigData;` — vioso confguration data
- L95 _private member_ `const FString UniqueName;`
- L98 _private member_ `struct VWB_Warper* pWarper = nullptr;` — Internal VIOSO data
- L115 _private member_ `bool bInitialized = false;` — Warped can be used
- L118 _private member_ `FVector2D DefaultClippingPlanes;` — Custom clipping planes

#### struct `FDisplayClusterProjectionVIOSOWarper::FViewClip`  
`struct FViewClip`  
_L101-106_
- desc: Convert arry to local vars.
- L105 _public member_ `VWB_float Left, Top, Right, Bottom, NCP, FCP;` — The correct order of ViewClips was obtained from the VIOSO sources void VWB_Warper_base::getClip( VWB_VEC3f const& e, VWB_float * pClip )
- L105 _public member_ `VWB_float Left, Top, Right, Bottom, NCP, FCP;` — The correct order of ViewClips was obtained from the VIOSO sources void VWB_Warper_base::getClip( VWB_VEC3f const& e, VWB_float * pClip )
- L105 _public member_ `VWB_float Left, Top, Right, Bottom, NCP, FCP;` — The correct order of ViewClips was obtained from the VIOSO sources void VWB_Warper_base::getClip( VWB_VEC3f const& e, VWB_float * pClip )
- L105 _public member_ `VWB_float Left, Top, Right, Bottom, NCP, FCP;` — The correct order of ViewClips was obtained from the VIOSO sources void VWB_Warper_base::getClip( VWB_VEC3f const& e, VWB_float * pClip )
- L105 _public member_ `VWB_float Left, Top, Right, Bottom, NCP, FCP;` — The correct order of ViewClips was obtained from the VIOSO sources void VWB_Warper_base::getClip( VWB_VEC3f const& e, VWB_float * pClip )
- L105 _public member_ `VWB_float Left, Top, Right, Bottom, NCP, FCP;` — The correct order of ViewClips was obtained from the VIOSO sources void VWB_Warper_base::getClip( VWB_VEC3f const& e, VWB_float * pClip )

#### union `FDisplayClusterProjectionVIOSOWarper::(anonymous)`  
``  
_L109-112_

#### Free symbols / members of external scopes

- L110 _member_ `VWB_float VWB_ViewClip[6];` (scope `FDisplayClusterProjectionVIOSOWarper::__anon136d1b9f010a`)
- L111 _member_ `FViewClip ViewClip;` (scope `FDisplayClusterProjectionVIOSOWarper::__anon136d1b9f010a`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Public/Blueprints/DisplayClusterProjectionBlueprintLib.h` (Public)


#### class `UDisplayClusterProjectionBlueprintLib`  
`class UDisplayClusterProjectionBlueprintLib : public UBlueprintFunctionLibrary`  
_L15-32_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint API function library
- L25 _public prototype_ `static void GetAPI(TScriptInterface<IDisplayClusterProjectionBlueprintAPI>& OutAPI);` — `UE_DEPRECATED(5.4, "GetAPI function has been deprecated. All functions are now available in UDisplayClusterProjectionBlueprintLib.")` — `UFUNCTION(BlueprintPure, meta = (DeprecatedFunction, DeprecationMessage = "GetAPI has been deprecated. All functions are now available in the main blueprint functions list under 'nDisplay' category."))` — [DEPRECATED] Returns Display Cluster Projection API interface.
- L31 _public prototype_ `static void CameraPolicySetCamera(const FString& ViewportId, UCameraComponent* NewCamera, float FOVMultiplier = 1.f);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set camera"), Category = "NDisplay|Projection")` — Sets camera up for 'camera' projection policy.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Public/Blueprints/IDisplayClusterProjectionBlueprintAPI.h` (Public)


#### class `UDisplayClusterProjectionBlueprintAPI`  
`class UDisplayClusterProjectionBlueprintAPI : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IDisplayClusterProjectionBlueprintAPI`  
`class IDisplayClusterProjectionBlueprintAPI`  
_L23-35_
- desc: Blueprint API interface
- L34 _public prototype_ `virtual void CameraPolicySetCamera(const FString& ViewportId, UCameraComponent* NewCamera, float FOVMultiplier = 1.f) = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterProjectionBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Sets active camera component for camera policy

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Public/Containers/DisplayClusterProjectionCameraPolicySettings.h` (Public)


#### struct `FDisplayClusterProjectionCameraPolicySettings`  
`struct FDisplayClusterProjectionCameraPolicySettings`  
_L7-25_
- L9 _public member_ `float FOVMultiplier = 1;`
- L12 _public member_ `FRotator FrustumRotation = FRotator::ZeroRotator;` — Rotate incamera frustum on this value to fix broken lens on physic camera
- L15 _public member_ `FVector FrustumOffset = FVector::ZeroVector;` — Move incamera frustum on this value to fix broken lens on physic camera
- L18 _public member_ `FVector2D OffCenterProjectionOffset = FVector2D::ZeroVector;` — Off-axis / off-center projection offset as proportion of screen dimensions
- L21 _public member_ `bool bCameraOverrideDefaults = false;` — When enabled, ignore all next updates, until null cam ref not assigned (UE-137222)
- L24 _public member_ `bool bUseCameraPostprocess = true;` — Allow to use camera postprocess

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Public/DisplayClusterProjectionStrings.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace DisplayClusterProjectionStrings`
- L12 _namespace_ `namespace cfg` (scope `DisplayClusterProjectionStrings`)
- L14 _namespace_ `namespace easyblend` (scope `DisplayClusterProjectionStrings::cfg`)
- L16 _variable_ `static constexpr const TCHAR* File = TEXT("fil` (scope `DisplayClusterProjectionStrings::cfg::easyblend`)
- L17 _variable_ `static constexpr const TCHAR* Origin = TEXT("ori` (scope `DisplayClusterProjectionStrings::cfg::easyblend`)
- L18 _variable_ `static constexpr const TCHAR* Scale = TEXT("sca` (scope `DisplayClusterProjectionStrings::cfg::easyblend`)
- L20 _variable_ `static constexpr const TCHAR* OriginOffset = TEXT("ori` (scope `DisplayClusterProjectionStrings::cfg::easyblend`)
- L23 _namespace_ `namespace VIOSO` (scope `DisplayClusterProjectionStrings::cfg`)
- L25 _variable_ `static constexpr const TCHAR* Origin = TEXT("ori` (scope `DisplayClusterProjectionStrings::cfg::VIOSO`)
- L27 _variable_ `static constexpr const TCHAR* INIFile = TEXT("ini` (scope `DisplayClusterProjectionStrings::cfg::VIOSO`)
- L28 _variable_ `static constexpr const TCHAR* ChannelName = TEXT("cha` (scope `DisplayClusterProjectionStrings::cfg::VIOSO`)
- L30 _variable_ `static constexpr const TCHAR* File = TEXT("fil` (scope `DisplayClusterProjectionStrings::cfg::VIOSO`)
- L33 _variable_ `static constexpr const TCHAR* CalibIndex = TEXT("ind` (scope `DisplayClusterProjectionStrings::cfg::VIOSO`) — The VIOSO calibration file contains several instances of geometry (for several screens in one file), so we must use this parameter to be able to select the right one.
- L34 _variable_ `static constexpr const TCHAR* CalibAdapter = TEXT("ada` (scope `DisplayClusterProjectionStrings::cfg::VIOSO`)
- L36 _variable_ `static constexpr const TCHAR* Gamma = TEXT("gam` (scope `DisplayClusterProjectionStrings::cfg::VIOSO`)
- L39 _variable_ `static constexpr const TCHAR* UnitsInMeter = TEXT("Uni` (scope `DisplayClusterProjectionStrings::cfg::VIOSO`) — How many VIOSO units in meter
- L41 _variable_ `static constexpr const TCHAR* EnablePreview = TEXT("Ena` (scope `DisplayClusterProjectionStrings::cfg::VIOSO`)
- L44 _namespace_ `namespace manual` (scope `DisplayClusterProjectionStrings::cfg`)
- L46 _variable_ `static constexpr const TCHAR* Rendering = TEXT("Man` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L47 _variable_ `static constexpr const TCHAR* Type = TEXT("Man` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L48 _variable_ `static constexpr const TCHAR* Rotation = TEXT("rot` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L50 _variable_ `static constexpr const TCHAR* Matrix = TEXT("mat` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L51 _variable_ `static constexpr const TCHAR* MatrixLeft = TEXT("mat` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L52 _variable_ `static constexpr const TCHAR* MatrixRight = TEXT("mat` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L54 _variable_ `static constexpr const TCHAR* Frustum = TEXT("fru` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L55 _variable_ `static constexpr const TCHAR* FrustumLeft = TEXT("fru` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L56 _variable_ `static constexpr const TCHAR* FrustumRight = TEXT("fru` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L58 _variable_ `static constexpr const TCHAR* AngleL = TEXT("l")` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L59 _variable_ `static constexpr const TCHAR* AngleR = TEXT("r")` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L60 _variable_ `static constexpr const TCHAR* AngleT = TEXT("t")` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L61 _variable_ `static constexpr const TCHAR* AngleB = TEXT("b")` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L63 _namespace_ `namespace FrustumType` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L65 _variable_ `static constexpr const TCHAR* Matrix = TEXT("Mat` (scope `DisplayClusterProjectionStrings::cfg::manual::FrustumType`)
- L66 _variable_ `static constexpr const TCHAR* Angles = TEXT("Ang` (scope `DisplayClusterProjectionStrings::cfg::manual::FrustumType`)
- L68 _namespace_ `namespace RenderingType` (scope `DisplayClusterProjectionStrings::cfg::manual`)
- L70 _variable_ `static constexpr const TCHAR* Mono = TEXT("Mon` (scope `DisplayClusterProjectionStrings::cfg::manual::RenderingType`)
- L71 _variable_ `static constexpr const TCHAR* Stereo = TEXT("Ste` (scope `DisplayClusterProjectionStrings::cfg::manual::RenderingType`)
- L72 _variable_ `static constexpr const TCHAR* MonoStereo = TEXT("Mon` (scope `DisplayClusterProjectionStrings::cfg::manual::RenderingType`)
- L76 _namespace_ `namespace camera` (scope `DisplayClusterProjectionStrings::cfg`)
- L78 _variable_ `static constexpr const TCHAR* Component = TEXT("cam` (scope `DisplayClusterProjectionStrings::cfg::camera`)
- L79 _variable_ `static constexpr const TCHAR* Native = TEXT("nat` (scope `DisplayClusterProjectionStrings::cfg::camera`)
- L82 _namespace_ `namespace reference` (scope `DisplayClusterProjectionStrings::cfg`)
- L84 _variable_ `static constexpr const TCHAR* ViewportId = TEXT("vie` (scope `DisplayClusterProjectionStrings::cfg::reference`)
- L87 _namespace_ `namespace mesh` (scope `DisplayClusterProjectionStrings::cfg`)
- L89 _variable_ `static constexpr const TCHAR* Component = TEXT("mes` (scope `DisplayClusterProjectionStrings::cfg::mesh`)
- L91 _variable_ `static constexpr const TCHAR* LODIndex = TEXT("lod` (scope `DisplayClusterProjectionStrings::cfg::mesh`)
- L92 _variable_ `static constexpr const TCHAR* SectionIndex = TEXT("sec` (scope `DisplayClusterProjectionStrings::cfg::mesh`)
- L94 _variable_ `static constexpr const TCHAR* BaseUVIndex = TEXT("bas` (scope `DisplayClusterProjectionStrings::cfg::mesh`)
- L95 _variable_ `static constexpr const TCHAR* ChromakeyUVIndex = TEXT("chr` (scope `DisplayClusterProjectionStrings::cfg::mesh`)
- L98 _namespace_ `namespace mpcdi` (scope `DisplayClusterProjectionStrings::cfg`)
- L100 _variable_ `static constexpr const TCHAR* File = TEXT("fil` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L101 _variable_ `static constexpr const TCHAR* Buffer = TEXT("buf` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L102 _variable_ `static constexpr const TCHAR* Region = TEXT("reg` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L103 _variable_ `static constexpr const TCHAR* Origin = TEXT("ori` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L105 _variable_ `static constexpr const TCHAR* MPCDIType = TEXT("mpc` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L107 _variable_ `static constexpr const TCHAR* FilePFM = TEXT("pfm` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L108 _variable_ `static constexpr const TCHAR* WorldScale = TEXT("sca` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L109 _variable_ `static constexpr const TCHAR* UseUnrealAxis = TEXT("ue_` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L111 _variable_ `static constexpr const TCHAR* FileAlpha = TEXT("alp` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L112 _variable_ `static constexpr const TCHAR* AlphaGamma = TEXT("alp` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L113 _variable_ `static constexpr const TCHAR* FileBeta = TEXT("bet` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L115 _variable_ `static constexpr const TCHAR* MPCDITypeKey = TEXT("MPC` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L116 _variable_ `static constexpr const TCHAR* TypeMPCDI = TEXT("MPC` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L117 _variable_ `static constexpr const TCHAR* TypePFM = TEXT("Exp` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L119 _variable_ `static constexpr const TCHAR* EnablePreview = TEXT("Ena` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L121 _variable_ `static constexpr const TCHAR* Component = TEXT("scr` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L123 _namespace_ `namespace Profiles` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L125 _variable_ `static constexpr const TCHAR* mpcdi_2d = TEXT("2d"` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Profiles`)
- L126 _variable_ `static constexpr const TCHAR* mpcdi_3d = TEXT("3d"` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Profiles`)
- L127 _variable_ `static constexpr const TCHAR* mpcdi_a3d = TEXT("a3d` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Profiles`)
- L128 _variable_ `static constexpr const TCHAR* mpcdi_sl = TEXT("sl"` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Profiles`)
- L131 _namespace_ `namespace Attributes` (scope `DisplayClusterProjectionStrings::cfg::mpcdi`)
- L133 _namespace_ `namespace Buffer` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Attributes`)
- L135 _variable_ `static constexpr const TCHAR* Resolution = TEXT("Buf` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Attributes::Buffer`)
- L138 _namespace_ `namespace Region` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Attributes`)
- L140 _variable_ `static constexpr const TCHAR* Resolution = TEXT("Reg` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Attributes::Region`)
- L141 _variable_ `static constexpr const TCHAR* Pos = TEXT("Reg` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Attributes::Region`)
- L142 _variable_ `static constexpr const TCHAR* Size = TEXT("Reg` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Attributes::Region`)
- L145 _namespace_ `namespace Frustum` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Attributes`)
- L147 _variable_ `static constexpr const TCHAR* Rotation = TEXT("Fru` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Attributes::Frustum`)
- L148 _variable_ `static constexpr const TCHAR* Angles = TEXT("Fru` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Attributes::Frustum`)
- L151 _namespace_ `namespace CoordinateFrame` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Attributes`)
- L153 _variable_ `static constexpr const TCHAR* Position = TEXT("Coo` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Attributes::CoordinateFrame`)
- L154 _variable_ `static constexpr const TCHAR* Rotation = TEXT("Coo` (scope `DisplayClusterProjectionStrings::cfg::mpcdi::Attributes::CoordinateFrame`)
- L159 _namespace_ `namespace domeprojection` (scope `DisplayClusterProjectionStrings::cfg`)
- L161 _variable_ `static constexpr const TCHAR* File = TEXT("fil` (scope `DisplayClusterProjectionStrings::cfg::domeprojection`)
- L162 _variable_ `static constexpr const TCHAR* Channel = TEXT("cha` (scope `DisplayClusterProjectionStrings::cfg::domeprojection`)
- L163 _variable_ `static constexpr const TCHAR* Origin = TEXT("ori` (scope `DisplayClusterProjectionStrings::cfg::domeprojection`)
- L164 _variable_ `static constexpr const TCHAR* UnitsToMeter = TEXT("sca` (scope `DisplayClusterProjectionStrings::cfg::domeprojection`)
- L168 _namespace_ `namespace projection` (scope `DisplayClusterProjectionStrings`)
- L170 _variable_ `static constexpr const TCHAR* Camera = TEXT("cam` (scope `DisplayClusterProjectionStrings::projection`)
- L171 _variable_ `static constexpr const TCHAR* Domeprojection = TEXT("dom` (scope `DisplayClusterProjectionStrings::projection`)
- L172 _variable_ `static constexpr const TCHAR* EasyBlend = TEXT("eas` (scope `DisplayClusterProjectionStrings::projection`)
- L173 _variable_ `static constexpr const TCHAR* Link = TEXT("lin` (scope `DisplayClusterProjectionStrings::projection`)
- L174 _variable_ `static constexpr const TCHAR* Manual = TEXT("man` (scope `DisplayClusterProjectionStrings::projection`)
- L175 _variable_ `static constexpr const TCHAR* Mesh = TEXT("mes` (scope `DisplayClusterProjectionStrings::projection`)
- L176 _variable_ `static constexpr const TCHAR* MPCDI = TEXT("mpc` (scope `DisplayClusterProjectionStrings::projection`)
- L177 _variable_ `static constexpr const TCHAR* Reference = TEXT("ref` (scope `DisplayClusterProjectionStrings::projection`)
- L178 _variable_ `static constexpr const TCHAR* VIOSO = TEXT("vio` (scope `DisplayClusterProjectionStrings::projection`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Public/IDisplayClusterProjection.h` (Public)


#### class `IDisplayClusterProjection`  
`class IDisplayClusterProjection : public IModuleInterface`  
_L14-70_
- inherits: `IModuleInterface`
- L17 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L20 _public prototype_ `virtual ~IDisplayClusterProjection() = default;`
- L29 _public function_ `static inline IDisplayClusterProjection& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L39 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L49 _public prototype_ `virtual void GetSupportedProjectionTypes(TArray<FString>& OutProjectionTypes) = 0;` — Returns supported projection types @param OutProjectionTypes - (out) Array of supported projection types
- L58 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicyFactory> GetProjectionFactory(const FString& InProjectionType) = 0;` — Returns specified projection factory @param InProjectionType - Projection type @return - Projection policy factory of requested type, null if not available
- L64 _public prototype_ `virtual bool CameraPolicySetCamera(const TSharedPtr<class IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& InPolicy, class UCameraComponent* const NewCamera, const struct FDisplayClusterProjectionCameraPolicySettings& CameraSettings) = 0;` — Set camera policy camera
- L69 _public prototype_ `virtual class UCameraComponent* CameraPolicyGetCameraComponent(const TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& InPolicy) = 0;` — Get camera policy camera

### `Plugins/Runtime/nDisplay/Source/DisplayClusterProjection/Public/Misc/DisplayClusterProjectionHelpers.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DisplayClusterProjectionHelpers` (scope `UE`)
- L11 _namespace_ `namespace MPCDI` (scope `UE::DisplayClusterProjectionHelpers`)
- L14 _function_ `static EDisplayClusterWarpProfileType ProfileTypeFromString(const FString& InProfileTypeName)` (scope `UE::DisplayClusterProjectionHelpers::MPCDI`) — Convert the mpcdi profile type from a string to an enum value.
- L37 _function_ `static FString ProfileTypeToString(const EDisplayClusterWarpProfileType InProfileType)` (scope `UE::DisplayClusterProjectionHelpers::MPCDI`) — Convert the mpcdi profile type from an enum value to a string.
