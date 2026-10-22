# Plugins / GoogleARCoreRendering

- module root: `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreRendering`
- headers: 5; symbols: 52
- symbol kinds: class=5, enum=2, enumerator=10, function=2, member=17, prototype=14, struct=1, variable=1
- PrivateDependencyModuleNames: ARUtilities, Core, CoreUObject, Engine, Json, RHI, RenderCore, Renderer

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreRendering/Private/GoogleARCorePassthroughCameraExternalTextureGuid.h` (Private)


#### Free symbols / members of external scopes

- L9 _variable_ `static FGuid GoogleARCorePassthroughCameraExternalTextureGuid(0x3c87151d, 0x929e4f87, 0xab5bb2dc, 0xc4f9042c);` — GUID used to indicate that this external texture is the tango camera.

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreRendering/Private/MaterialExpressionGoogleARCorePassthroughCamera.h` (Private)


#### class `UDEPRECATED_MaterialExpressionGoogleARCorePassthroughCamera`  
`class UDEPRECATED_MaterialExpressionGoogleARCorePassthroughCamera : public UMaterialExpression`  
_L15-33_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, Deprecated)`
- inherits: `UMaterialExpression`
- desc: Implements a node sampling from the ARCore Passthrough external texture.
- L20 _private member_ `FExpressionInput Coordinates;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstCoordinate' if not specified"))`
- L24 _private member_ `uint32 ConstCoordinate;` — `UPROPERTY(EditAnywhere, Category = UMaterialExpressionGoogleARCorePassthroughCamera)` — only used if Coordinates are not hooked up.
- L28 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L29 _private prototype_ `virtual int32 CompilePreview(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L30 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreRendering/Public/GoogleARCorePassthroughCameraRenderer.h` (Public)


#### class `UGoogleARCoreCameraOverlayMaterialLoader`  
`class UGoogleARCoreCameraOverlayMaterialLoader : public UObject`  
_L29-63_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A helper class that is used to load the GoogleARCorePassthroughCameraMaterial from its default object.
- L36 _public member_ `TObjectPtr<UMaterialInterface> RegularOverlayMaterial;` — `UPROPERTY()` — A pointer to the camera overlay material that will be used to render the passthrough camera texture as background.
- L40 _public member_ `TObjectPtr<UMaterialInterface> DebugOverlayMaterial;` — `UPROPERTY()` — A pointer to the camera overlay material that will be used to render the passthrough camera texture as background.
- L43 _public member_ `TObjectPtr<UMaterialInterface> DepthOcclusionMaterial;` — `UPROPERTY()`
- L47 _public member_ `TObjectPtr<UMaterialInterface> DepthColorationMaterial;` — `UPROPERTY()` — Material used for rendering the coloration of the depth map.
- L49 _public function_ `UGoogleARCoreCameraOverlayMaterialLoader()`

#### class `FGoogleARCorePassthroughCameraRenderer`  
`class FGoogleARCorePassthroughCameraRenderer : public FGCObject`  
_L65-99_
- inherits: `FGCObject`
- L68 _public prototype_ `FGoogleARCorePassthroughCameraRenderer();`
- L70 _public prototype_ `void InitializeRenderer_RenderThread(FSceneViewFamily& InViewFamily);`
- L72 _public prototype_ `void RenderVideoOverlay_RenderThread(FRHICommandList& RHICmdList, FSceneView& InView);`
- L74 _public prototype_ `void UpdateCameraTextures(UTexture* NewCameraTexture, UTexture* DepthTexture, bool bEnableOcclusion);`
- L76 _public prototype_ `void UpdateCameraYCbCrConversion(IYCbCrConversionQuery* NewYCbCrConversionQuery);`
- L78 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L79 _public function_ `virtual FString GetReferencerName() const override`
- L85 _private prototype_ `void RenderVideoOverlayWithMaterial(FRHICommandList& RHICmdList, FSceneView& InView, UMaterialInstanceDynamic* OverlayMaterialToUse, bool bRenderingOcclusion, bool bUsesCameraTexture);`
- L88 _private member_ `FBufferRHIRef OverlayIndexBufferRHI;`
- L89 _private member_ `FBufferRHIRef OverlayVertexBufferRHI;`
- L91 _private member_ `TObjectPtr<UMaterialInstanceDynamic> RegularOverlayMaterial = nullptr;`
- L92 _private member_ `TObjectPtr<UMaterialInstanceDynamic> DebugOverlayMaterial = nullptr;`
- L93 _private member_ `TObjectPtr<UMaterialInstanceDynamic> DepthColorationMaterial = nullptr;`
- L94 _private member_ `TObjectPtr<UMaterialInstanceDynamic> DepthOcclusionMaterial = nullptr;`
- L96 _private member_ `bool bEnableOcclusionRendering = false;`
- L98 _private member_ `FYCbCrConversion CameraYCbCrConversion;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreRendering/Public/GoogleARCoreRenderingModule.h` (Public)


#### class `FGoogleARCoreRenderingModule`  
`class FGoogleARCoreRenderingModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation.
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreRendering/Public/GoogleARCoreYCbCrConversion.h` (Public)


#### enum `EYCbCrModelConversion`  
`enum class EYCbCrModelConversion : uint8`  
_L7-15_
- L9 _public enumerator_ `None = 0`
- L10 _public enumerator_ `YCbCrIdentity`
- L11 _public enumerator_ `YCbCrRec709`
- L12 _public enumerator_ `YCbCrRec601`
- L13 _public enumerator_ `YCbCrRec2020`
- L14 _public enumerator_ `Max`

#### enum `EYCbCrRange`  
`enum class EYCbCrRange : uint8`  
_L17-23_
- L19 _public enumerator_ `Unknown = 0`
- L20 _public enumerator_ `Full`
- L21 _public enumerator_ `Narrow`
- L22 _public enumerator_ `Max`

#### struct `FYCbCrConversion`  
`struct FYCbCrConversion`  
_L25-31_
- L28 _public member_ `EYCbCrModelConversion YCbCrModelConversion = EYCbCrModelConversion::None;`
- L29 _public member_ `EYCbCrRange YCbCrRange = EYCbCrRange::Unknown;`
- L30 _public member_ `uint8 NumBits = 8;`

#### class `IYCbCrConversionQuery`  
`class IYCbCrConversionQuery`  
_L33-41_
- L36 _public prototype_ `virtual ~IYCbCrConversionQuery() = default;`
- L40 _public prototype_ `virtual FYCbCrConversion GetYCbCrConversion_RenderThread() const = 0;` — Returns the YCbCr conversion paramers of Vulkan's external Hardware Buffer. It should be called from the render thread only.
