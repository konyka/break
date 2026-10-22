# Editor / PixelInspectorModule

- module root: `Source/Editor/PixelInspector`
- headers: 6; symbols: 208
- symbol kinds: class=7, function=11, macro=16, member=90, namespace=4, prototype=80
- PrivateDependencyModuleNames: EditorFramework, Renderer, SlateCore
- PrivateIncludePathModuleNames: LevelEditor
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, PropertyEditor, RHI, RenderCore, Slate, UnrealEd

### `Source/Editor/PixelInspector/Private/PixelInspector.h` (Private)


#### class `PixelInspector::FPixelInspectorSceneViewExtension`  
`class FPixelInspectorSceneViewExtension : public FSceneViewExtensionBase`  
_L26-47_
- inherits: `FSceneViewExtensionBase`
- L29 _public prototype_ `FPixelInspectorSceneViewExtension(const FAutoRegister& AutoRegister);`
- L33 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L34 _public prototype_ `virtual void SubscribeToPostProcessingPass(EPostProcessingPass PassId, const FSceneView& View, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled) override;`
- L37 _public prototype_ `FScreenPassTexture PostProcessPassAfterFxaa_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& InOutInputs);`
- L38 _public prototype_ `FScreenPassTexture PostProcessPassAfterMotionBlur_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& InOutInputs);`
- L39 _public function_ `const EPixelFormat GetFinalColorPixelFormat() const`
- L40 _public function_ `const EPixelFormat GetHDRPixelFormat() const`
- L41 _public function_ `const float GetGamma() const`
- L44 _private member_ `EPixelFormat FinalColorPixelFormat;`
- L45 _private member_ `EPixelFormat HDRPixelFormat;`
- L46 _private member_ `float FinalColorGamma;`

#### class `PixelInspector::SPixelInspector`  
`class SPixelInspector : public SCompoundWidget, public FNotifyHook`  
_L54-207_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: Implements the PixelInspector window.
- L58 _public prototype_ `SPixelInspector();` — Default constructor.
- L61 _public prototype_ `virtual ~SPixelInspector();` — Virtual destructor.
- L64 _public prototype_ `void ReleaseRessource();` — Release all the ressource
- L66 _public function_ `SLATE_BEGIN_ARGS(SPixelInspector)`
- L67 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L75 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L78 _public prototype_ `void OnApplicationPreInputKeyDownListener(const FKeyEvent& InKeyEvent);`
- L79 _public prototype_ `void OnWindowClosed();`
- L82 _public prototype_ `FReply HandleTogglePixelInspectorEnableButton();` — Button handlers
- L83 _public prototype_ `FText GetPixelInspectorEnableButtonText() const;`
- L84 _public prototype_ `FText GetPixelInspectorEnableButtonTooltipText() const;`
- L85 _public prototype_ `const FSlateBrush* GetPixelInspectorEnableButtonBrush() const;`
- L88 _public function_ `TOptional<uint32> GetCurrentViewportId() const`
- L89 _public function_ `FIntPoint GetCurrentCoordinate() const`
- L90 _public function_ `TOptional<int32> GetCurrentCoordinateX() const`
- L91 _public prototype_ `void SetCurrentCoordinateX(int32 NewValue);`
- L92 _public prototype_ `void SetCurrentCoordinateXCommit(int32 NewValue, ETextCommit::Type);`
- L93 _public function_ `TOptional<int32> GetCurrentCoordinateY() const`
- L94 _public prototype_ `void SetCurrentCoordinateY(int32 NewValue);`
- L95 _public prototype_ `void SetCurrentCoordinateYCommit(int32 NewValue, ETextCommit::Type);`
- L96 _public prototype_ `TOptional<int32> GetMaxCoordinateX() const;`
- L97 _public prototype_ `TOptional<int32> GetMaxCoordinateY() const;`
- L101 _public function_ `bool IsPixelInspectorEnable() const`
- L103 _public prototype_ `void SetCurrentCoordinate(FIntPoint NewCoordinate, bool ReleaseAllRequest);`
- L105 _public function_ `void SetViewportInformation(int32 ViewportUniqueId, FIntPoint ViewportSize)`
- L116 _public prototype_ `void CreatePixelInspectorRequest(FVector2D InspectViewportUV, int32 viewportUniqueId, FSceneInterface *SceneInterface, bool bInGameViewMode, float InPreExposure);` — Create a request and the associate buffers ScreenPosition: This is the viewport coordinate in 2D of the pixel to analyze viewportUniqueId: The id of the view (FSceneView::State::GetViewKey) we want to capture the pixel, ScreenPosition has to come from this viewport SceneInterface: The interface to set the data for the next render frame. bInGameViewMode: Whether the next render frame is a game view. InPreExposure: The preexposure for the next render frame.
- L124 _public prototype_ `void ReadBackRequestData();` — Look if there is some request ready to be read and retrieve the value. If there is a request that are ready it will read the gpu buffer to get the value and store the result. The request will be configure to be available again and the buffers will be release.
- L137 _protected prototype_ `int32 CreateRequestBuffer(FSceneInterface *SceneInterface, const int32 GBufferFormat, bool bInGameViewMode);` — Create the necessary rendertarget buffers for a request and set the render scene data. First created buffer (1x1) is for the normal (GBufferA) which can be of the following format: PF_FloatRGBA PF_B8G8R8A8 or PF_A2B10G10R10, depending on the precision settings Second created buffer (1x4) is for the other data (GBuffer B, C, D and E) which can be of the following format: PF_FloatRGBA or PF_B8G8R8A8, depending on the precision settings GBufferFormat: 0(Low RGB8), 1 (default), 5(float) Return a unique Index to allow the request to know how to find them in the FPixelInspectorData at the post process time when sending the read buffer graphic commands.
- L142 _protected prototype_ `void ReleaseBuffers(int32 BufferIndex);` — Release all Ubuffer with the BufferIndex so the garbage collector will destroy them.
- L144 _protected prototype_ `void OnLevelActorDeleted(AActor* Actor);`
- L146 _protected prototype_ `void OnRedrawViewport(bool bInvalidateHitProxies);`
- L151 _protected prototype_ `void SetCurrentViewportInRealtime();` — Use by the Coordinate mode only, this change the realtime state of the viewport if the state is not true
- L153 _protected prototype_ `void SetPixelInspectorState(bool bInIsPixelInspectorEnabled);`
- L157 _private prototype_ `void ReleaseAllRequests();`
- L158 _private member_ `FDelegateHandle OnLevelActorDeletedDelegateHandle;`
- L159 _private member_ `FDelegateHandle OnEditorCloseHandle;`
- L160 _private member_ `FDelegateHandle OnRedrawViewportHandle;`
- L161 _private member_ `FDelegateHandle OnApplicationPreInputKeyDownListenerHandle;`
- L163 _private member_ `bool bIsPixelInspectorEnable;`
- L165 _private member_ `int32 TickSinceLastCreateRequest;`
- L166 _private member_ `FPixelInspectorRequest Requests[2];`
- L172 _private member_ `UTextureRenderTarget2D* Buffer_FinalColor_AnyFormat[2];` — Buffer management we can do only one pixel inspection per frame We have two buffer of each type to not halt the render thread when we do the read back from the GPU FinalColor Buffer
- L174 _private member_ `UTextureRenderTarget2D* Buffer_Depth_Float[2];` — Depth Buffer
- L176 _private member_ `UTextureRenderTarget2D* Buffer_SceneColorBeforePost_Float[2];` — SceneColor Buffers
- L177 _private member_ `UTextureRenderTarget2D* Buffer_SceneColorBeforeToneMap_Float[2];`
- L179 _private member_ `UTextureRenderTarget2D* Buffer_A_Float[2];` — GBufferA RenderTarget
- L180 _private member_ `UTextureRenderTarget2D* Buffer_A_RGB8[2];`
- L181 _private member_ `UTextureRenderTarget2D* Buffer_A_RGB10[2];`
- L183 _private member_ `UTextureRenderTarget2D* Buffer_BCDEF_Float[2];` — GBuffer BCDE RenderTarget
- L184 _private member_ `UTextureRenderTarget2D* Buffer_BCDEF_RGB8[2];`
- L186 _private member_ `int32 LastBufferIndex;` — Which index we are at for the current Request
- L190 _private member_ `TArray<PixelInspectorResult> AccumulationResult;` — ReadBack Data
- L195 _private member_ `UPixelInspectorView *DisplayResult;`
- L197 _private member_ `FIntPoint LastViewportInspectionSize;`
- L199 _private member_ `FIntPoint LastViewportInspectionPosition;`
- L201 _private member_ `uint32 LastViewportId;`
- L203 _private member_ `TSharedPtr<IDetailsView> DisplayDetailsView;`
- L205 _private member_ `TSharedPtr< class FPixelInspectorSceneViewExtension, ESPMode::ThreadSafe > PixelInspectorSceneViewExtension;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace PixelInspector`
- L50 _macro_ `#define WAIT_FRAMENUMBER_BEFOREREADING 5`

### `Source/Editor/PixelInspector/Private/PixelInspectorDetailsCustomization.h` (Private)


#### class `FPixelInspectorDetailsCustomization`  
`class FPixelInspectorDetailsCustomization : public IDetailCustomization`  
_L19-41_
- inherits: `IDetailCustomization`
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L29 _public member_ `TWeakObjectPtr<UPixelInspectorView> PixelInspectorView;` — The UI data object being customised
- L30 _public member_ `IDetailLayoutBuilder* CachedDetailBuilder;` — The detail builder for this cusomtomisation
- L34 _private prototype_ `FReply HandleColorCellMouseButtonDown(const FGeometry &, const FPointerEvent &, int32 RowIndex, int32 ColumnIndex);`
- L36 _private prototype_ `TSharedRef<SHorizontalBox> GetGridColorContext();`
- L37 _private prototype_ `TSharedRef<SColorBlock> CreateColorCell(int32 RowIndex, int32 ColumnIndex, const FLinearColor &CellColor);`
- L40 _private prototype_ `FPixelInspectorDetailsCustomization();` — Use MakeInstance to create an instance of this class

### `Source/Editor/PixelInspector/Private/PixelInspectorResult.h` (Private)


#### class `PixelInspector::PixelInspectorResult`  
`class PixelInspectorResult`  
_L32-167_
- L35 _public function_ `PixelInspectorResult()`
- L71 _public member_ `int32 ViewUniqueId;` — Data Identification
- L72 _public member_ `FVector2D ViewportUV;`
- L77 _public member_ `float PreExposure;` — PreExposure used to render this frame.
- L78 _public member_ `float OneOverPreExposure;`
- L82 _public member_ `TArray<FLinearColor> FinalColor;` — Final color 3x3 grid
- L86 _public member_ `FLinearColor SceneColorBeforePostProcessing;` — Scene color
- L87 _public member_ `FLinearColor SceneColorBeforeTonemap;`
- L88 _public member_ `float LuminanceBeforeTonemap;`
- L92 _public member_ `float Depth;` — Depth and world position
- L93 _public member_ `FVector WorldPosition;`
- L97 _public member_ `FVector Normal;` — Buffers value
- L98 _public member_ `float PerObjectGBufferData;` — GBufferA A
- L99 _public member_ `float Metallic;` — GBufferB R
- L100 _public member_ `float Specular;` — GBufferB G
- L101 _public member_ `float Roughness;` — GBufferB B
- L102 _public member_ `EMaterialShadingModel ShadingModel;` — GBufferB A encode
- L103 _public member_ `int32 SelectiveOutputMask;` — GBufferB A encode
- L104 _public member_ `FLinearColor BaseColor;` — GBufferC RGB
- L107 _public member_ `float IndirectIrradiance;` — Irradiance and Ambient occlusion decoding
- L108 _public member_ `float AmbientOcclusion;` — GBufferC A if static light is not allow 1 otherwise
- L116 _public member_ `FLinearColor SubSurfaceColor;` — MSM_Subsurface MSM_PreintegratedSkin MSM_TwoSidedFoliage
- L117 _public member_ `float Opacity;` — GBufferD A
- L120 _public member_ `FVector SubsurfaceProfile;` — MSM_SubsurfaceProfile
- L123 _public member_ `float ClearCoat;` — MSM_ClearCoat
- L124 _public member_ `float ClearCoatRoughness;` — GBufferD G
- L127 _public member_ `FVector WorldNormal;` — MSM_Hair
- L128 _public member_ `float BackLit;`
- L131 _public member_ `float Cloth;` — MSM_Cloth
- L134 _public member_ `FVector EyeTangent;` — MSM_Eye
- L135 _public member_ `float IrisMask;`
- L136 _public member_ `float IrisDistance;`
- L139 _public prototype_ `void DecodeFinalColor(TArray<FLinearColor> &BufferFinalColorValue, float InGamma, bool bHasAlphaChannel);` — Decodes final color from HDR input.
- L140 _public prototype_ `void DecodeSceneColorBeforePostProcessing(TArray<FLinearColor> &BufferSceneColorValue);`
- L141 _public prototype_ `void DecodeDepth(TArray<FLinearColor> &BufferDepthValue);`
- L142 _public prototype_ `void DecodeSceneColorBeforeToneMap(TArray<FLinearColor>& BufferSceneColorValue, bool bHasAlphaChannel);`
- L144 _public prototype_ `void DecodeBufferData(TArray<FColor> &BufferAValue, TArray<FColor> &BufferBCDEValue, bool AllowStaticLighting);`
- L145 _public prototype_ `void DecodeBufferData(TArray<FLinearColor> &BufferAValue, TArray<FColor> &BufferBCDEValue, bool AllowStaticLighting);`
- L146 _public prototype_ `void DecodeBufferData(TArray<FFloat16Color> &BufferAValue, TArray<FFloat16Color> &BufferBCDEValue, bool AllowStaticLighting);`
- L150 _private prototype_ `void DecodeBufferA(TArray<FColor> &BufferAValue);`
- L151 _private prototype_ `void DecodeBufferA(TArray<FLinearColor> &BufferAValue);`
- L152 _private prototype_ `void DecodeBufferA(TArray<FFloat16Color> &BufferAValue);`
- L154 _private prototype_ `void DecodeBufferBCDE(TArray<FColor> &BufferBCDEValue, bool AllowStaticLighting);`
- L155 _private prototype_ `void DecodeBufferBCDE(TArray<FFloat16Color> &BufferBCDEValue, bool AllowStaticLighting);`
- L157 _private prototype_ `FVector4 ConvertLinearRGBAToFloat(FColor LinearRGBColor);`
- L158 _private prototype_ `FVector ConvertLinearRGBToFloat(FColor LinearRGBColor);`
- L159 _private prototype_ `FVector ConvertLinearRGBToFloat(uint8 Red, uint8 Green, uint8 Blue);`
- L160 _private prototype_ `FLinearColor DecodeSubSurfaceColor(FVector EncodeColor);`
- L161 _private prototype_ `FVector DecodeNormalFromBuffer(FVector NormalEncoded);`
- L162 _private prototype_ `EMaterialShadingModel DecodeShadingModel(float InPackedChannel);`
- L163 _private prototype_ `uint32 DecodeSelectiveOutputMask(float InPackedChannel);`
- L164 _private prototype_ `float DecodeIndirectIrradiance(float IndirectIrradiance);`
- L165 _private prototype_ `FVector OctahedronToUnitVector(FVector2D Oct);`
- L166 _private prototype_ `void DecodeCustomData(FVector4 InCustomData);`

#### Free symbols / members of external scopes

- L15 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_UNLIT 0`
- L16 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_DEFAULT_LIT 1`
- L17 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_SUBSURFACE 2`
- L18 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_PREINTEGRATED_SKIN 3`
- L19 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_CLEAR_COAT 4`
- L20 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_SUBSURFACE_PROFILE 5`
- L21 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_TWOSIDED_FOLIAGE 6`
- L22 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_HAIR 7`
- L23 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_CLOTH 8`
- L24 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_EYE 9`
- L25 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_SINGLELAYERWATER 10`
- L26 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_THIN_TRANSLUCENT 11`
- L27 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_SUBSTRATE 12`
- L28 _macro_ `#define PIXEL_INSPECTOR_SHADINGMODELID_MASK 0xF`
- L30 _namespace_ `namespace PixelInspector`

### `Source/Editor/PixelInspector/Private/PixelInspectorStyle.h` (Private)


#### class `FPixelInspectorStyle`  
`class FPixelInspectorStyle`  
_L8-22_
- L12 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L15 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L17 _public prototype_ `static FName GetStyleSetName();`
- L21 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

### `Source/Editor/PixelInspector/Private/PixelInspectorView.h` (Private)


#### class `UPixelInspectorView`  
`class UPixelInspectorView : public UObject`  
_L22-162_
- reflection: `UCLASS(HideCategories = Object, MinimalAPI)`
- inherits: `UObject`
- L26 _private member_ `FLinearColor FinalColorContext[FinalColorContextGridSize*FinalColorContextGridSize];`
- L30 _private member_ `FLinearColor FinalColor;` — `UPROPERTY(VisibleAnywhere, category = FinalColor)` — Final color in display space after tone mapping.
- L34 _private member_ `float PreExposure;` — `UPROPERTY(VisibleAnywhere, category = SceneColor)` — Amount of exposure applied to Scene Color due to auto-exposure and/or exposure compensation.
- L38 _private member_ `FLinearColor SceneColorBeforePostProcessing;` — `UPROPERTY(VisibleAnywhere, category = SceneColor, meta = (DisplayName = "Scene Color Before Post-Processing"))` — HDR scene-linear color in working color space, before post-processing. Previously called Scene Color.
- L42 _private member_ `FLinearColor SceneColorBeforeTonemap;` — `UPROPERTY(VisibleAnywhere, category = SceneColor)` — HDR scene-linear color in working color space, before tone mapping. Previously called Hdr Color.
- L46 _private member_ `float LuminanceBeforeTonemap;` — `UPROPERTY(VisibleAnywhere, category = SceneColor)` — Luminance of the Scene Color Before Tonemap.
- L50 _private member_ `FVector Normal;` — `UPROPERTY(VisibleAnywhere, category = GBufferA)` — From the GBufferA RGB Channels.
- L54 _private member_ `float PerObjectGBufferData;` — `UPROPERTY(VisibleAnywhere, category = GBufferA)` — From the GBufferA A Channel.
- L58 _private member_ `float Metallic;` — `UPROPERTY(VisibleAnywhere, category = GBufferB)` — From the GBufferB R Channel.
- L62 _private member_ `float Specular;` — `UPROPERTY(VisibleAnywhere, category = GBufferB)` — From the GBufferB G Channel.
- L66 _private member_ `float Roughness;` — `UPROPERTY(VisibleAnywhere, category = GBufferB)` — From the GBufferB B Channel.
- L74 _private member_ `int32 SelectiveOutputMask;` — `UPROPERTY(VisibleAnywhere, category = GBufferB)` — From the GBufferB A Channel encoded with ShadingModel.
- L78 _private member_ `FLinearColor BaseColor;` — `UPROPERTY(VisibleAnywhere, category = GBufferC)` — From the GBufferC RGB Channels.
- L82 _private member_ `float IndirectIrradiance;` — `UPROPERTY(VisibleAnywhere, category = GBufferC)` — From the GBufferC A Channel encoded with AmbientOcclusion.
- L86 _private member_ `float AmbientOcclusion;` — `UPROPERTY(VisibleAnywhere, category = GBufferC)` — From the GBufferC A Channel encoded with IndirectIrradiance.
- L92 _private member_ `FLinearColor SubSurfaceColor;` — `UPROPERTY(VisibleAnywhere, category = GBufferD)` — From the GBufferD RGB Channels.
- L96 _private member_ `FVector SubsurfaceProfile;` — `UPROPERTY(VisibleAnywhere, category = GBufferD)` — From the GBufferD RGB Channels.
- L100 _private member_ `float Opacity;` — `UPROPERTY(VisibleAnywhere, category = GBufferD)` — From the GBufferD A Channel.
- L104 _private member_ `float ClearCoat;` — `UPROPERTY(VisibleAnywhere, category = GBufferD)` — From the GBufferD R Channel.
- L108 _private member_ `float ClearCoatRoughness;` — `UPROPERTY(VisibleAnywhere, category = GBufferD)` — From the GBufferD G Channel.
- L112 _private member_ `FVector WorldNormal;` — `UPROPERTY(VisibleAnywhere, category = GBufferD)` — From the GBufferD RG Channels.
- L116 _private member_ `float BackLit;` — `UPROPERTY(VisibleAnywhere, category = GBufferD)` — From the GBufferD B Channel.
- L120 _private member_ `float Cloth;` — `UPROPERTY(VisibleAnywhere, category = GBufferD)` — From the GBufferD A Channel.
- L124 _private member_ `FVector EyeTangent;` — `UPROPERTY(VisibleAnywhere, category = GBufferD)` — From the GBufferD RG Channels.
- L128 _private member_ `float IrisMask;` — `UPROPERTY(VisibleAnywhere, category = GBufferD)` — From the GBufferD B Channel.
- L132 _private member_ `float IrisDistance;` — `UPROPERTY(VisibleAnywhere, category = GBufferD)` — From the GBufferD A Channel.
- L134 _private prototype_ `void SetFromResult(PixelInspector::PixelInspectorResult &Result);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace PixelInspector`
- L17 _macro_ `#define FinalColorContextGridSize 7`

### `Source/Editor/PixelInspector/Public/PixelInspectorModule.h` (Public)


#### class `FPixelInspectorModule`  
`class FPixelInspectorModule : public IModuleInterface`  
_L19-67_
- inherits: `IModuleInterface`
- desc: The module holding all of the UI related pieces for pixel inspector
- L26 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L31 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L34 _public prototype_ `virtual TSharedRef<SWidget> CreatePixelInspectorWidget();` — Creates the HLOD Outliner widget
- L36 _public prototype_ `virtual void ActivateCoordinateMode();`
- L38 _public prototype_ `virtual bool IsPixelInspectorEnable();`
- L40 _public prototype_ `virtual void GetCoordinatePosition(FIntPoint &InspectViewportCoordinate, uint32 &InspectViewportId);`
- L42 _public prototype_ `virtual void SetCoordinatePosition(FIntPoint &InspectViewportCoordinate, bool ReleaseAllRequest);`
- L44 _public prototype_ `virtual bool GetViewportRealtime(int32 ViewportUid, bool IsCurrentlyRealtime, bool IsMouseInsideViewport);`
- L46 _public prototype_ `virtual void CreatePixelInspectorRequest(FVector2D InspectViewportUV, int32 ViewportUniqueId, FSceneInterface *SceneInterface, bool bInGameViewMode, float InPreExposure);`
- L48 _public prototype_ `virtual void SetViewportInformation(int32 ViewportUniqueId, FIntPoint ViewportSize);`
- L50 _public prototype_ `virtual void ReadBackSync();`
- L52 _public prototype_ `virtual void RegisterTabSpawner(const TSharedPtr<FWorkspaceItem>& WorkspaceGroup);`
- L54 _public prototype_ `virtual void UnregisterTabSpawner();`
- L58 _private prototype_ `void OnTabClosed(TSharedRef<SDockTab> TabBeingClosed);`
- L61 _private prototype_ `TSharedRef<SDockTab> MakePixelInspectorTab(const FSpawnTabArgs&);`
- L63 _private member_ `bool bHasRegisteredTabSpawners;`
- L64 _private member_ `TSharedPtr<PixelInspector::SPixelInspector> HPixelInspectorWindow;`
- L66 _private member_ `TMap<uint32, bool> OriginalViewportStates;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace PixelInspector`
