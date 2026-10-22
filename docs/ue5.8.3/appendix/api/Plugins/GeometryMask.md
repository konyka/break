# Plugins / GeometryMask

- module root: `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask`
- headers: 22; symbols: 415
- symbol kinds: class=22, delegate=3, enum=2, enumerator=10, function=28, macro=6, member=111, namespace=15, prototype=190, struct=12, typedef=10, variable=6
- PrivateDependencyModuleNames: DeveloperSettings, GeometryCore, GeometryFramework, LevelEditor, Projects, RHI, RenderCore, Renderer, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Private/GeometryMaskCanvasUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace GeometryMask` (scope `UE`)
- L12 _prototype_ `void UpdateRenderTarget(TNotNull<UTextureRenderTarget2DArray*> InRenderTarget);` (scope `UE::GeometryMask`) — Updates the resource for the render target

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Private/GeometryMaskModule.h` (Private)


#### class `FGeometryMaskModule`  
`class FGeometryMaskModule : public IGeometryMaskModule`  
_L14-35_
- inherits: `IGeometryMaskModule`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _private prototype_ `void RegisterConsoleCommands();` — Called from StartupModule and sets up console commands for the plugin via IConsoleManager
- L28 _private prototype_ `void UnregisterConsoleCommands();` — Called from ShutdownModule and clears out previously registered console commands
- L30 _private prototype_ `void ExecuteDebugDF(const TArray<FString>& InArgs);`
- L34 _private member_ `TArray<IConsoleObject*> ConsoleCommands;` — References of registered console commands via IConsoleManager

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryMask, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryMask, Log, All);`
- L12 _delegate_ `DECLARE_STATS_GROUP(TEXT("GeometryMask"), STATGROUP_GeometryMask, STATCA`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Private/GeometryMaskSVE.h` (Private)


#### class `FGeometryMaskSceneViewExtension`  
`class FGeometryMaskSceneViewExtension : public FWorldSceneViewExtension`  
_L10-23_
- inherits: `FWorldSceneViewExtension`
- L14 _public prototype_ `FGeometryMaskSceneViewExtension(const FAutoRegister& AutoRegister, UWorld* InWorld);`
- L17 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L18 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L22 _private member_ `TWeakObjectPtr<UGeometryMaskSubsystem> GeometryMaskSubsystemWeak;`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Private/GeometryMaskSettings.h` (Private)


#### class `UGeometryMaskSettings`  
`class UGeometryMaskSettings : public UDeveloperSettings`  
_L10-37_
- reflection: `UCLASS(Config = "Plugins", DefaultConfig, MinimalAPI)`
- inherits: `UDeveloperSettings`
- L17 _public member_ `uint8 DebugDF = 0;` — `UPROPERTY()`
- L21 _public function_ `virtual FName GetContainerName() const override`
- L22 _public function_ `virtual FName GetCategoryName() const override`
- L23 _public function_ `virtual FName GetSectionName() const override`
- L26 _public function_ `virtual FText GetSectionText() const override`
- L27 _public function_ `virtual FText GetSectionDescription() const override`
- L30 _public prototype_ `float GetDefaultResolutionMultiplier() const;`
- L31 _public prototype_ `void SetDefaultResolutionMultiplier(const float InValue);`
- L36 _private member_ `float DefaultResolutionMultiplier = 1.0;` — `UPROPERTY(Config, EditAnywhere, Category = "Canvas", Getter, Setter, meta = (ClampMin = 0.25, ClampMax = 16.0, AllowPrivateAccess = "true"))` — Set to enable super-sampling, ie. 2.0 will render at twice the resolution.

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Private/Shaders/GeometryMaskPostProcess.h` (Private)


#### class `IGeometryMaskPostProcess`  
`class IGeometryMaskPostProcess`  
_L9-18_
- L12 _public prototype_ `virtual ~IGeometryMaskPostProcess() = default;`
- L14 _public prototype_ `virtual void Execute(FRenderTarget* InTexture) = 0;`
- L17 _protected prototype_ `virtual void Execute_RenderThread(FRHICommandListImmediate& InRHICmdList, FRenderTarget* InTexture) = 0;`

#### class `TGeometryMaskPostProcess`  
`template <typename InParametersType> class TGeometryMaskPostProcess : public IGeometryMaskPostProcess`  
_L21-40_
- inherits: `IGeometryMaskPostProcess`
- L25 _public function_ `explicit TGeometryMaskPostProcess(const InParametersType& InParameters) : Parameters(InParameters)`
- L28 _public function_ `const InParametersType& GetParameters() const`
- L33 _public function_ `void SetParameters(const InParametersType& InParameters)`
- L39 _protected member_ `InParametersType Parameters;`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Private/Shaders/GeometryMaskPostProcess_Blur.h` (Private)


#### struct `FGeometryMaskPostProcessParameters_Blur`  
`struct FGeometryMaskPostProcessParameters_Blur`  
_L17-22_
- L19 _public member_ `bool bApplyBlur = false;`
- L20 _public member_ `uint16 SliceIndex = 0;`
- L21 _public member_ `double BlurStrength = 16.0;`

#### class `FGeometryMaskPostProcess_Blur`  
`class FGeometryMaskPostProcess_Blur : public TGeometryMaskPostProcess<FGeometryMaskPostProcessParameters_Blur> , public TSharedFromThis<FGeometryMaskPostProcess_Blur>`  
_L24-37_
- inherits: `TGeometryMaskPostProcess<FGeometryMaskPostProcessParameters_Blur>,TSharedFromThis<FGeometryMaskPostProcess_Blur>`
- L28 _private typedef_ `using Super = TGeometryMaskPostProcess<FGeometryMaskPostProcessParameters_Blur>;`
- L31 _public prototype_ `explicit FGeometryMaskPostProcess_Blur(const FGeometryMaskPostProcessParameters_Blur& InParameters);`
- L33 _public prototype_ `virtual void Execute(FRenderTarget* InTexture) override;`
- L36 _protected prototype_ `virtual void Execute_RenderThread(FRHICommandListImmediate& InRHICmdList, FRenderTarget* InTexture) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace GeometryMask` (scope `UE`)
- L12 _namespace_ `namespace Internal` (scope `UE::GeometryMask`)
- L14 _prototype_ `int32 ComputeEffectiveKernelSize(double InStrength);` (scope `UE::GeometryMask::Internal`)

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Private/Shaders/GeometryMaskPostProcess_DistanceField.h` (Private)


#### struct `FGeometryMaskPostProcessParameters_DistanceField`  
`struct FGeometryMaskPostProcessParameters_DistanceField`  
_L19-24_
- L21 _public member_ `bool bCalculateDF = false;`
- L22 _public member_ `uint16 SliceIndex = 0;`
- L23 _public member_ `double Radius = 16.f;`

#### class `FGeometryMaskPostProcess_DistanceField`  
`class FGeometryMaskPostProcess_DistanceField : public TGeometryMaskPostProcess<FGeometryMaskPostProcessParameters_DistanceField> , public TSharedFromThis<FGeometryMaskPostProcess_DistanceField>`  
_L27-46_
- inherits: `TGeometryMaskPostProcess<FGeometryMaskPostProcessParameters_DistanceField>,TSharedFromThis<FGeometryMaskPostProcess_DistanceField>`
- L31 _private typedef_ `using Super = TGeometryMaskPostProcess<FGeometryMaskPostProcessParameters_DistanceField>;`
- L34 _public prototype_ `explicit FGeometryMaskPostProcess_DistanceField(const FGeometryMaskPostProcessParameters_DistanceField& InParameters);`
- L36 _public prototype_ `virtual void Execute(FRenderTarget* InTexture) override;`
- L39 _protected prototype_ `virtual void Execute_RenderThread(FRHICommandListImmediate& InRHICmdList, FRenderTarget* InTexture) override;`
- L43 _private member_ `TOptional<FIntPoint> LastInputSize;` — Cached to selectively resize resources when needed.
- L44 _private member_ `TRefCountPtr<FRDGPooledBuffer> StoredInitOutputBuffer;`
- L45 _private member_ `TRefCountPtr<FRDGPooledBuffer> StoredStepIntermediateBufferB;`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/GeometryMaskCanvas.h` (Public)


#### class `UGeometryMaskCanvas`  
`class UGeometryMaskCanvas : public UObject`  
_L27-232_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Transient)`
- inherits: `UObject`
- desc: A uniquely identified Canvas.
- L33 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L36 _public prototype_ `ULevel* GetLevel() const;`
- L39 _public prototype_ `const TArray<TWeakInterfacePtr<IGeometryMaskWriteInterface>>& GetWriters() const;` — Returns all writers.
- L42 _public prototype_ `void AddWriter(const TScriptInterface<IGeometryMaskWriteInterface>& InWriter);` — Adds a Mask Writer to the canvas.
- L45 _public prototype_ `void AddWriters(const TArray<TScriptInterface<IGeometryMaskWriteInterface>>& InWriters);` — Appends multiple writers to the canvas.
- L48 _public prototype_ `void RemoveWriter(const TScriptInterface<IGeometryMaskWriteInterface>& InWriter);` — Remove a writer from this canvas.
- L51 _public prototype_ `int32 GetNumWriters() const;` — Gets the number of writers for the canvas.
- L54 _public prototype_ `bool IsDefaultCanvas() const;` — Returns true if this is the default/blank canvas.
- L57 _public prototype_ `void Free();` — Forcibly free the canvas - removed all writers and frees the resource.
- L61 _public prototype_ `UCanvasRenderTarget2D* GetTexture() const;` — `UE_DEPRECATED(5.8, "GetTexture (CanvasRenderTarget2D) has been deprecated. Use GetRenderTarget (TextureRenderTarget2DArray) and pass it into Mask_Textures parameter instead")` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Rendering", meta=(DeprecatedFunction, DeprecationMessage="GetTexture (CanvasRenderTarget2D) has been deprecated. Use GetRenderTarget (TextureRenderTarget2DArray) and pass it into Mask_Textures parameter instead"))`
- L65 _public prototype_ `UTextureRenderTarget2DArray* GetRenderTarget() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Rendering")` — Returns the render target 2D array that the canvas draws to
- L68 _public prototype_ `int16 GetRenderTargetSliceIndex() const;` — Get the index to the render target slice the canvas draws to
- L72 _public prototype_ `int32 BP_GetRenderTargetSliceIndex() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="Get Render Target Slice Index", Category = "Rendering")` — Get the index to the render target slice the canvas draws to
- L75 _public prototype_ `const FGeometryMaskCanvasId& GetCanvasId() const;` — Get the unique canvas id based on the world and canvas name.
- L78 _public prototype_ `FName GetCanvasName() const;` — Returns the canvas name
- L81 _public prototype_ `bool IsBlurApplied() const;` — Whether blur is applied or not.
- L84 _public prototype_ `void SetApplyBlur(const bool bInValue);` — Sets whether blur is applied or not.
- L87 _public prototype_ `double GetBlurStrength() const;` — Gets the current blur strength, if applicable.
- L90 _public prototype_ `void SetBlurStrength(const double InValue);` — Sets the blur strength. 0.0 will disable blur.
- L93 _public prototype_ `bool IsFeatherApplied() const;` — Whether feathering is applied or not.
- L96 _public prototype_ `void SetApplyFeather(const bool bInValue);` — Sets whether feathering is applied or not.
- L99 _public prototype_ `int32 GetOuterFeatherRadius() const;` — Gets the current outer feather radius, in pixels.
- L102 _public prototype_ `void SetOuterFeatherRadius(const int32 InValue);` — Sets the outer feather radius, in pixels.
- L105 _public prototype_ `int32 GetInnerFeatherRadius() const;` — Gets the current inner feather radius, in pixels.
- L108 _public prototype_ `void SetInnerFeatherRadius(const int32 InValue);` — Sets the inner feather radius, in pixels.
- L112 _public prototype_ `EGeometryMaskColorChannel GetColorChannel() const;` — `UE_DEPRECATED(5.8, "Color channel has been deprecated in 5.8. Use GetRenderTargetSliceIndex and pass it into the R value in the Mask_TextureIndexVector color parameter. Rest of the values (GBA) should be -1.")` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Rendering", meta=(DeprecatedFunction, DeprecationMessage="Color channel has been deprecated in 5.8. Use GetRenderTargetSliceIndex and pass it into the R value in the Mask_TextureIndexVector color parameter. Rest of the values (GBA) should be -1"))`
- L115 _public function_ `FOnGeometryMaskCanvasActivated& OnActivated()` — Called when Writers becomes non-empty.
- L121 _public function_ `FOnGeometryMaskCanvasDeactivated& OnDeactivated()` — Called when Writers becomes empty.
- L127 _public prototype_ `void Initialize(const ULevel* InLevel, FName InCanvasName);` — `UE_DEPRECATED(5.8, "Initialize with level and canvas name has been deprecated")`
- L142 _public prototype_ `void Initialize(const FInitParams& InInitParams);`
- L145 _public prototype_ `void Update(const ULevel* InLevel, FSceneView& InView);` — Updates the canvas, intended to be called every frame.
- L148 _public prototype_ `TSharedPtr<FGeometryMaskCanvasSharedData> GetSharedData() const;` — Get the data shared among canvases using the same render target
- L150 _public function_ `const UGeometryMaskCanvasResource* GetResource() const`
- L155 _public function_ `UGeometryMaskCanvasResource* GetResourceMutable()`
- L161 _public prototype_ `void AssignResource(UGeometryMaskCanvasResource* InResource, EGeometryMaskColorChannel InColorChannel);` — `UE_DEPRECATED(5.8, "AssignResource has been deprecated as resource management is done by the canvas itself")`
- L164 _public prototype_ `void FreeResource();` — `UE_DEPRECATED(5.8, "FreeResource has been deprecated as resource management is done by the canvas itself")`
- L167 _public prototype_ `static FName GetApplyBlurPropertyName();`
- L168 _public prototype_ `static FName GetBlurStrengthPropertyName();`
- L169 _public prototype_ `static FName GetApplyFeatherPropertyName();`
- L170 _public prototype_ `static FName GetOuterFeatherRadiusPropertyName();`
- L171 _public prototype_ `static FName GetInnerFeatherRadiusPropertyName();`
- L174 _private member_ `static const FName ApplyBlurPropertyName;`
- L175 _private member_ `static const FName BlurStrengthPropertyName;`
- L176 _private member_ `static const FName ApplyFeatherPropertyName;`
- L177 _private member_ `static const FName OuterFeatherRadiusPropertyName;`
- L178 _private member_ `static const FName InnerFeatherRadiusPropertyName;`
- L184 _private prototype_ `void SortWriters();` — Sorts writers by various criteria for proper rendering order.
- L187 _private prototype_ `void RemoveInvalidWriters();` — Remove all invalid/stale writers.
- L190 _private prototype_ `void OnDrawToCanvas(const FGeometryMaskDrawingContext& InDrawingContext, FSceneView& InView, FCanvas* InCanvas);` — Draws all writers to the canvas.
- L193 _private prototype_ `void UpdateRenderParameters();` — Updates relevant shader parameters for the given color channel.
- L196 _private member_ `FOnGeometryMaskCanvasActivated OnActivatedDelegate;`
- L197 _private member_ `FOnGeometryMaskCanvasDeactivated OnDeactivatedDelegate;`
- L200 _private member_ `FGeometryMaskCanvasId CanvasId;` — `UPROPERTY(Transient, DuplicateTransient)`
- L204 _private member_ `FName CanvasName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Getter, Category = "Canvas", meta = (AllowPrivateAccess = "true"))` — Uniquely identifies this canvas.
- L208 _private member_ `bool bApplyBlur = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsBlurApplied", Setter = "SetApplyBlur", Category = "Canvas", meta = (AllowPrivateAccess = "true"))` — Optional Blur Toggle.
- L212 _private member_ `double BlurStrength = 16;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Canvas", meta = (AllowPrivateAccess = "true", EditCondition = "bApplyBlur", EditConditionHides, ClampMin = 0.0))` — Optional Blur Strength.
- L216 _private member_ `bool bApplyFeather = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsFeatherApplied", Setter = "SetApplyFeather", Category = "Canvas", meta = (AllowPrivateAccess = "true"))` — Optional Feather Toggle.
- L220 _private member_ `int32 OuterFeatherRadius = 16;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Canvas", meta = (AllowPrivateAccess = "true", EditCondition = "bApplyFeather", EditConditionHides, ClampMin = 0))` — Optional Outer Feather Radius.
- L224 _private member_ `int32 InnerFeatherRadius = 16;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Canvas", meta = (AllowPrivateAccess = "true", EditCondition = "bApplyFeather", EditConditionHides, ClampMin = 0))` — Optional Inner Feather Radius.
- L228 _private member_ `TObjectPtr<UGeometryMaskCanvasResource> CanvasResource;` — `UPROPERTY(Transient)` — Canvas GPU resource to use.
- L231 _private member_ `TArray<TWeakInterfacePtr<IGeometryMaskWriteInterface>> Writers;` — List of objects that write to this canvas.

#### struct `UGeometryMaskCanvas::FInitParams`  
`struct FInitParams`  
_L129-141_
- L132 _public member_ `const ULevel* Level = nullptr;` — Level that this canvas is relevant for
- L134 _public member_ `FName CanvasName;` — Name identifying this canvas within the level
- L136 _public member_ `UTextureRenderTarget2DArray* RenderTarget = nullptr;` — Render target to draw to
- L138 _public member_ `int32 SliceIndex = -1;` — Index to the slice in the render target to draw to
- L140 _public member_ `TSharedPtr<FGeometryMaskCanvasSharedData> SharedData;` — Shared data between canvases

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYMASK_API`
- L20 _typedef_ `using FOnGeometryMaskCanvasActivated = TDelegate<void()>;` — Called when Writers becomes non-empty.
- L23 _typedef_ `using FOnGeometryMaskCanvasDeactivated = TDelegate<void()>;` — Called when Writers becomes empty.

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/GeometryMaskCanvasActor.h` (Public)


#### class `AGeometryMaskCanvasActor`  
`class AGeometryMaskCanvasActor : public AActor, public IGeometryMaskClient`  
_L16-61_
- reflection: `UCLASS(BlueprintType)`
- inherits: `AActor,IGeometryMaskClient`
- desc: Wraps a GeometryMaskCanvas, and discovers/registers writers.
- L21 _public prototype_ `AGeometryMaskCanvasActor(const FObjectInitializer& ObjectInitializer);`
- L25 _public member_ `FName CanvasName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Canvas")` — Identifies the referenced Canvas.
- L29 _public prototype_ `UCanvasRenderTarget2D* GetTexture() const;` — `UE_DEPRECATED(5.8, "GetTexture (UCanvasRenderTarget2D*) has been deprecated. Use GetRenderTarget (UTextureRenderTarget2DArray*) instead")` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Rendering", meta=(DeprecatedFunction, DeprecatedMessage="GetTexture (CanvasRenderTarget2D) has been deprecated in favor of GetRenderTarget (TextureRenderTarget2DArray)"))`
- L33 _public prototype_ `UTextureRenderTarget2DArray* GetRenderTarget() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Rendering")` — Returns the render target 2D array that the canvas draws to
- L35 _public prototype_ `virtual void BeginPlay() override;`
- L37 _public prototype_ `virtual void PostLoad() override;`
- L40 _public prototype_ `virtual void RerunConstructionScripts() override;`
- L45 _protected prototype_ `bool TryResolveCanvas();` — Resolve/locate the canvas identified by CanvasName.
- L48 _protected prototype_ `void FindWriters();` — Find writers on child actors and add them to the referenced canvas.
- L51 _protected prototype_ `virtual bool ForEachUsedCanvasName(TFunctionRef<bool(FName)> InFunc) const override;`
- L56 _protected member_ `TObjectPtr<UGeometryMaskCanvas> Canvas;` — `UPROPERTY(Transient, DuplicateTransient)` — Reference to the Canvas used, identified by CanvasName.
- L60 _protected member_ `TArray<TScriptInterface<IGeometryMaskWriteInterface>> Writers;` — `UPROPERTY()` — List of objects that write to this canvas.

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/GeometryMaskCanvasResource.h` (Public)


#### class `UGeometryMaskCanvasResource`  
`class UGeometryMaskCanvasResource : public UObject`  
_L26-175_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L31 _public member_ `static constexpr int32 MaxNumChannels = UE::GeometryMask::MaxNumChannels;`
- L32 _public member_ `static constexpr int32 MaxNumAvailableChannels = UE::GeometryMask::MaxNumChannels;`
- L33 _public member_ `static constexpr int32 MaxTextureSize = UE::GeometryMask::MaxTextureSize;`
- L35 _public prototype_ `UGeometryMaskCanvasResource();`
- L37 _public prototype_ `virtual void BeginDestroy() override;`
- L39 _public prototype_ `void Initialize(UTextureRenderTarget2DArray* InRenderTarget, int32 InSliceIndex, const TSharedPtr<FGeometryMaskCanvasSharedData>& InSharedData);`
- L43 _public prototype_ `const EGeometryMaskColorChannel GetNextAvailableColorChannel() const;` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — Will return the first available color channel without a canvas assigned. EGeometryMaskColorChannel::None if not available.
- L47 _public prototype_ `bool Checkout(const EGeometryMaskColorChannel InColorChannel, const FGeometryMaskCanvasId& InRequestingCanvasId);` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — Requests usage of the given color channel for this resource. Will return true if successful.
- L51 _public prototype_ `bool Checkin(const FGeometryMaskCanvasId& InRequestingCanvasId);` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — Returns/frees the color channel associated with the given canvas name. Returns true if canvas name found.
- L55 _public prototype_ `int32 Compact();` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — Re-arranges used channels such that they are used sequentially. Returns number of unused channels.
- L58 _public prototype_ `int32 GetNumChannelsUsed() const;` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")`
- L61 _public prototype_ `bool IsAnyChannelUsed() const;` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")`
- L65 _public prototype_ `TArray<FGeometryMaskCanvasId> GetDependentCanvasIds() const;` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — Get the list of dependent canvases, for debug purposes.
- L68 _public prototype_ `const TSharedPtr<FGeometryMaskCanvasSharedData>& GetSharedData() const;` — Gets the data shared between canvases using the same render target
- L74 _public prototype_ `bool UpdateViewportSize();` — Validates that the render target size is up-to-date with the viewport size and updating it if not @return true if the render target size was updated
- L77 _public prototype_ `void SetViewportSize(FGeometryMaskDrawingContext& InDrawingContext, const FIntPoint& InViewportSize);` — `UE_DEPRECATED(5.8, "SetViewportSize deprecated as it's no longer needed")`
- L80 _public prototype_ `const FIntPoint& GetMaxViewportSize() const;` — Returns the maximum size that would cover all requested viewports
- L83 _public prototype_ `int32 GetViewportPadding(const FGeometryMaskDrawingContext& InDrawingContext) const;` — `UE_DEPRECATED(5.8, "GetViewportPadding requiring a drawing context has been deprecated. Use GetRequiredViewportPadding() instead")`
- L86 _public prototype_ `int32 GetSharedViewportPadding() const;` — Returns the current viewport padding
- L89 _public prototype_ `int32 GetRequiredViewportPadding() const;` — Returns the minimum required viewport padding, in pixels - determined by certain effects.
- L92 _public prototype_ `UCanvasRenderTarget2D* GetRenderTargetTexture();` — `UE_DEPRECATED(5.8, "GetRenderTargetTexture (UCanvasRenderTarget2D) has been deprecated in favor of GetRenderTarget (UTextureRenderTarget2DArray)")`
- L95 _public prototype_ `UTextureRenderTarget2DArray* GetRenderTarget() const;` — Returns the render target the resource draws to
- L98 _public prototype_ `int16 GetRenderTargetSliceIndex() const;` — Get the index to the render target slice the resource draws to
- L101 _public prototype_ `FOnGeometryMaskCanvasDraw& OnDrawToCanvas();` — `UE_DEPRECATED(5.8, "OnDrawToCanvasDelegate has been deprecated as canvas resources are now directly owned by the canvas object")`
- L104 _public prototype_ `void UpdateRenderParameters(EGeometryMaskColorChannel InColorChannel, bool bInApplyBlur, double InBlurStrength, bool bInApplyFeather, int32 InOuterFeatherRadius, int32 InInnerFeatherRadius);` — `UE_DEPRECATED(5.8, "Color Channel is no longer used. Use the overload that does not take the color channel")`
- L106 _public prototype_ `void UpdateRenderParameters(bool bInApplyBlur, double InBlurStrength, bool bInApplyFeather, int32 InOuterFeatherRadius, int32 InInnerFeatherRadius);`
- L110 _public prototype_ `void ResetRenderParameters(EGeometryMaskColorChannel InColorChannel);` — `UE_DEPRECATED(5.8, "Color Channel is no longer used. Use the overload that does not take the color channel")` — Resets the render parameters for the given channel.
- L113 _public prototype_ `void ResetRenderParameters();` — Resets the render parameters for the resource
- L116 _public prototype_ `void Update(const ULevel* InLevel, FSceneView& InView, int32 InViewIndex = 0);` — Updates the canvas, intended to be called every frame.
- L119 _private prototype_ `ETextureRenderTargetSampleCount GetSampleCount() const;`
- L122 _private prototype_ `void Draw(const ULevel* InLevel, FSceneView& InView, int32 InViewIndex = 0);` — Draws all writers to the canvas.
- L124 _private prototype_ `FGeometryMaskDrawingContext* GetDrawingContextForLevel(const ULevel* InLevel, uint8 InSceneViewIndex);`
- L125 _private prototype_ `FGeometryMaskDrawingContext* GetDrawingContextForCanvas(const FGeometryMaskCanvasId& InCanvasId);`
- L128 _private prototype_ `FGeometryMaskDrawingContext* GetDrawingContextForChannel(EGeometryMaskColorChannel InColorChannel);` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")`
- L130 _private prototype_ `[[maybe_unused]] bool RemoveInvalidDrawingContexts();`
- L134 _private member_ `TMap<EGeometryMaskColorChannel, FGeometryMaskCanvasId> DependentCanvasIds_DEPRECATED;` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — `UPROPERTY()`
- L137 _private member_ `TBitArray<TInlineAllocator<UE::GeometryMask::MaxNumChannels>> UsedChannelMask;` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")`
- L141 _private member_ `int32 NumUsedChannels_DEPRECATED = 0;` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — `UPROPERTY()`
- L144 _private member_ `TSharedPtr<FCanvas> Canvas;` — Canvas used for drawing. Using FCanvas over UCanvas for perf
- L148 _private member_ `FIntPoint MaxViewportSize = FIntPoint(1920, 1080);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetMaxViewportSize", Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — The default viewport size to use when it can't be resolved from the actual viewport.
- L153 _private member_ `TObjectPtr<UCanvasRenderTarget2D> RenderTargetTexture_DEPRECATED;` — `UE_DEPRECATED(5.8, "RenderTargetTexture (UCanvasRenderTarget2D) has been deprecated in favor of RenderTarget (UTextureRenderTarget2DArray)")` — `UPROPERTY()` — The underlying Render Target texture.
- L157 _private member_ `TObjectPtr<UTextureRenderTarget2DArray> RenderTarget;` — `UPROPERTY(DuplicateTransient)` — The Render Target that this resource uses
- L161 _private member_ `int16 RenderTargetSliceIndex = -1;` — `UPROPERTY(DuplicateTransient)` — The render target slice assigned to this resource
- L164 _private member_ `TSharedPtr<FGeometryMaskCanvasSharedData> SharedData;` — Shared data between canvases using the same render target
- L166 _private member_ `TSet<FGeometryMaskDrawingContext> DrawingContextCache;`
- L168 _private member_ `FGeometryMaskDrawingContext DefaultDrawingContext;`
- L170 _private member_ `bool bApplyBlur = false;`
- L171 _private member_ `bool bApplyDF = false;`
- L173 _private member_ `TSharedPtr<FGeometryMaskPostProcess_Blur> PostProcess_Blur;`
- L174 _private member_ `TSharedPtr<FGeometryMaskPostProcess_DistanceField> PostProcess_DistanceField;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYMASK_API`
- L23 _typedef_ `using FOnGeometryMaskCanvasDraw = TMulticastDelegate<void(const FGeometryMaskDrawingContext&, FCanvas*)>;`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/GeometryMaskCanvasSharedData.h` (Public)


#### struct `FGeometryMaskCanvasSharedData`  
`struct FGeometryMaskCanvasSharedData`  
_L8-25_
- L10 _public function_ `void Reset()`
- L18 _public member_ `FIntPoint ViewportSize = FIntPoint(0, 0);` — Viewport size of the canvas
- L21 _public member_ `FIntPoint TextureSize = FIntPoint(0, 0);` — Actual size of the canvas render target
- L24 _public member_ `int32 ViewportPadding = 0;` — Viewport padding affecting the texture size

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/GeometryMaskConstants.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace GeometryMask` (scope `UE`)
- L9 _variable_ `constexpr int32 MaxNumChannels = 1;` (scope `UE::GeometryMask`)
- L10 _variable_ `constexpr int32 MaxTextureSize = 8192;` (scope `UE::GeometryMask`)

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/GeometryMaskReadComponent.h` (Public)


#### class `UGeometryMaskReadComponent`  
`class UGeometryMaskReadComponent : public UGeometryMaskCanvasReferenceComponentBase , public IGeometryMaskReadInterface`  
_L15-45_
- reflection: `UCLASS(Blueprintable, BlueprintType, HideCategories=(Activation, Cooking, AssetUserData, Navigation), meta=(BlueprintSpawnableComponent))`
- inherits: `UGeometryMaskCanvasReferenceComponentBase,IGeometryMaskReadInterface`
- L23 _public prototype_ `virtual void SetParameters(FGeometryMaskReadParameters& InParameters) override;`
- L24 _public function_ `virtual const FGeometryMaskReadParameters& GetParameters() const override`
- L28 _public function_ `virtual FOnGeometryMaskSetCanvasNativeDelegate& OnSetCanvas() override`
- L36 _protected prototype_ `virtual bool ForEachUsedCanvasName(TFunctionRef<bool(FName)> InFunc) const override;`
- L40 _protected prototype_ `virtual bool TryResolveCanvas() override;`
- L44 _protected member_ `FGeometryMaskReadParameters Parameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter="SetParameters", Getter="GetParameters", Category="Mask", meta=(ShowOnlyInnerProperties))`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/GeometryMaskSubsystem.h` (Public)


#### class `UGeometryMaskSubsystem`  
`class UGeometryMaskSubsystem : public UEngineSubsystem`  
_L23-89_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UEngineSubsystem`
- desc: Maintains the registered named canvases.
- L30 _public prototype_ `UGeometryMaskCanvas* GetDefaultCanvas();` — `UE_DEPRECATED(5.8, "GetDefaultCanvas is deprecated. Subsystem no longer manages holds a default canvas")` — `UFUNCTION(BlueprintCallable, Category = "Canvas", meta=(DeprecatedFunction, DeprecatedMessage="GetDefaultCanvas is deprecated. Subsystem no longer manages holds a default canvas"))`
- L33 _public prototype_ `int32 GetNumCanvasResources() const;` — `UE_DEPRECATED(5.8, "CanvasResources is deprecated. Subsystem no longer manages resources")`
- L36 _public prototype_ `const TSet<TObjectPtr<UGeometryMaskCanvasResource>>& GetCanvasResources() const;` — `UE_DEPRECATED(5.8, "CanvasResources is deprecated. Subsystem no longer manages resources")`
- L38 _public prototype_ `void Update(UWorld* InWorld, FSceneViewFamily& InViewFamily);`
- L41 _public prototype_ `void ToggleUpdate(const TOptional<bool>& bInShouldUpdate = {});` — Toggles if no arg given.
- L45 _public function_ `FOnGeometryMaskResourceCreated& OnGeometryMaskResourceCreated()` — `UE_DEPRECATED(5.8, "OnGeometryMaskResourceCreated is deprecated. Subsystem no longer manages resources")` — Called when a new canvas resource is created.
- L54 _public function_ `FOnGeometryMaskResourceDestroyed& OnGeometryMaskResourceDestroyed()` — `UE_DEPRECATED(5.8, "OnGeometryMaskResourceDestroyed is deprecated. Subsystem no longer manages resources")` — Called when a canvas resource is destroyed.
- L62 _private prototype_ `void UpdateLevel(const ULevel* InLevel, UGeometryMaskWorldSubsystem* InWorldSubsystem, FSceneViewFamily& InViewFamily);`
- L66 _private prototype_ `void AssignResourceToCanvas(UGeometryMaskCanvas* InCanvas);` — `UE_DEPRECATED(5.8, "AssignResourceToCanvas is deprecated. Subsystem no longer manages resources")` — Find and assign the next available resource to the given canvas.
- L69 _private prototype_ `void CompactResources();` — `UE_DEPRECATED(5.8, "CompactResources is deprecated. Subsystem no longer manages resources")`
- L72 _private prototype_ `void OnWorldDestroyed(UWorld* InWorld);` — `UE_DEPRECATED(5.8, "OnWorldDestroyed is deprecated. Subsystem no longer manages resources")`
- L78 _private member_ `FOnGeometryMaskResourceCreated OnGeometryMaskResourceCreatedDelegate;` — `UE_DEPRECATED(5.8, "OnGeometryMaskResourceCreatedDelegate is deprecated. Subsystem no longer manages resources")`
- L81 _private member_ `FOnGeometryMaskResourceDestroyed OnGeometryMaskResourceDestroyedDelegate;` — `UE_DEPRECATED(5.8, "OnGeometryMaskResourceDestroyedDelegate is deprecated. Subsystem no longer manages resources")`
- L83 _private member_ `std::atomic<bool> bDoUpdates = true;`
- L88 _private member_ `TSet<TObjectPtr<UGeometryMaskCanvasResource>> CanvasResources_DEPRECATED;` — `UE_DEPRECATED(5.8, "CanvasResources is deprecated. Subsystem no longer manages resources")` — `UPROPERTY()` — Pool of GPU/Texture resources used by the canvases.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GEOMETRYMASK_API`
- L18 _typedef_ `using FOnGeometryMaskResourceCreated = TMulticastDelegate<void(const UGeometryMaskCanvasResource*)>;`
- L19 _typedef_ `using FOnGeometryMaskResourceDestroyed = TMulticastDelegate<void(const UGeometryMaskCanvasResource*)>;`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/GeometryMaskTypes.h` (Public)


#### enum `EGeometryMaskColorChannel`  
`enum class EGeometryMaskColorChannel : uint8`  
_L17-26_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `Red = 0`
- L20 _public enumerator_ `Green = 1 << 0`
- L21 _public enumerator_ `Blue = 1 << 1`
- L22 _public enumerator_ `Alpha = 1 << 2`
- L23 _public enumerator_ `None = 1 << 3`
- L25 _public enumerator_ `Num`

#### struct `FGeometryMaskCanvasId`  
`struct FGeometryMaskCanvasId`  
_L85-125_
- reflection: `USTRUCT()`
- L90 _public member_ `TObjectKey<ULevel> Level;`
- L93 _public member_ `uint8 SceneViewIndex = 0;` — `UPROPERTY()`
- L96 _public member_ `FName Name;` — `UPROPERTY()`
- L99 _public member_ `static const FGeometryMaskCanvasId& None;`
- L100 _public member_ `static const FName DefaultCanvasName;`
- L103 _public prototype_ `FGeometryMaskCanvasId() = default;`
- L104 _public prototype_ `explicit FGeometryMaskCanvasId(const ULevel* InLevel, const FName InName);`
- L105 _public prototype_ `explicit FGeometryMaskCanvasId(EForceInit);`
- L107 _public prototype_ `bool IsDefault() const;`
- L108 _public prototype_ `bool IsNone() const;`
- L109 _public prototype_ `void ResetToNone();`
- L111 _public prototype_ `FString ToString() const;`
- L114 _public function_ `bool operator==(const FGeometryMaskCanvasId& InOther) const`
- L119 _public function_ `bool operator!=(const FGeometryMaskCanvasId& InOther) const`

#### struct `FGeometryMaskDrawingContext`  
`struct FGeometryMaskDrawingContext`  
_L129-166_
- reflection: `USTRUCT()`
- desc: Uniquely identified by world and scene view index.
- L134 _public member_ `TObjectKey<ULevel> Level;`
- L137 _public member_ `uint8 SceneViewIndex = 0;` — `UPROPERTY()`
- L140 _public member_ `FIntPoint ViewportSize = { 1920, 1080 };` — `UPROPERTY()`
- L144 _public member_ `FMatrix ViewProjectionMatrix = FMatrix::Identity;` — `UPROPERTY()` — The last resolved ViewProjectionMatrix.
- L147 _public prototype_ `FGeometryMaskDrawingContext() = default;`
- L148 _public prototype_ `explicit FGeometryMaskDrawingContext(TObjectKey<ULevel> InLevel, const uint8 InSceneViewIndex = 0);`
- L149 _public prototype_ `explicit FGeometryMaskDrawingContext(const ULevel* InLevel, const uint8 InSceneViewIndex = 0);`
- L150 _public prototype_ `explicit FGeometryMaskDrawingContext(EForceInit);`
- L152 _public prototype_ `bool IsValid() const;`
- L155 _public function_ `bool operator==(const FGeometryMaskDrawingContext& InOther) const`
- L160 _public function_ `bool operator!=(const FGeometryMaskDrawingContext& InOther) const`

#### enum `EGeometryMaskCompositeOperation`  
`enum class EGeometryMaskCompositeOperation : uint8`  
_L170-177_
- reflection: `UENUM(BlueprintType)`
- L172 _public enumerator_ `Add`
- L173 _public enumerator_ `Subtract`
- L174 _public enumerator_ `Intersect`
- L176 _public enumerator_ `Num`

#### struct `FGeometryMaskReadParameters`  
`struct FGeometryMaskReadParameters`  
_L183-197_
- reflection: `USTRUCT(BlueprintType)`
- L190 _public member_ `FName CanvasName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Canvas")` — Specifies the GeometryMaskCanvas to read from.
- L193 _public member_ `EGeometryMaskColorChannel ColorChannel = EGeometryMaskColorChannel::Red;` — `UPROPERTY(EditAnywhere, Category = "Read")`
- L196 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Read")`

#### struct `FGeometryMaskWriteParameters`  
`struct FGeometryMaskWriteParameters`  
_L200-237_
- reflection: `USTRUCT(BlueprintType)`
- L205 _public prototype_ `FGeometryMaskWriteParameters() = default;`
- L206 _public prototype_ `FGeometryMaskWriteParameters(const FGeometryMaskWriteParameters&) = default;`
- L207 _public prototype_ `FGeometryMaskWriteParameters(FGeometryMaskWriteParameters&&) = default;`
- L208 _public prototype_ `FGeometryMaskWriteParameters& operator=(const FGeometryMaskWriteParameters&) = default;`
- L209 _public prototype_ `FGeometryMaskWriteParameters& operator=(FGeometryMaskWriteParameters&&) = default;`
- L214 _public member_ `FName CanvasName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Canvas")` — Specifies the GeometryMaskCanvas to reference.
- L218 _public member_ `EGeometryMaskColorChannel ColorChannel_DEPRECATED = EGeometryMaskColorChannel::Red;` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — `UPROPERTY()`
- L221 _public member_ `EGeometryMaskCompositeOperation OperationType = EGeometryMaskCompositeOperation::Add;` — `UPROPERTY(EditAnywhere, Category = "Write")`
- L224 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Write")`
- L228 _public member_ `int32 Priority = 50;` — `UPROPERTY(EditAnywhere, Category = "Write")` — Higher values draw above lower.
- L232 _public member_ `double OuterRadius = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Shape", meta = (ClampMin = 0, UIMin = 0))` — The outer offset of the shapes extent in world units. Smoothly interpolates between the shape/inner radius and this.
- L236 _public member_ `double InnerRadius = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Shape", meta = (ClampMin = 0, UIMin = 0))` — The inner offset of the shapes extent in world units. Smoothly interpolates between the shape/outer radius and this.

#### class `UGeometryMaskCanvasReferenceComponentBase`  
`class UGeometryMaskCanvasReferenceComponentBase : public UActorComponent, public IGeometryMaskClient`  
_L240-280_
- reflection: `UCLASS(Abstract)`
- inherits: `UActorComponent,IGeometryMaskClient`
- L249 _public prototype_ `void ReceiveSetCanvas(const UGeometryMaskCanvas* InCanvas);` — `UFUNCTION(BlueprintImplementableEvent, CallInEditor, Category = "Canvas", meta = (DisplayName = "Canvas Changed"))` — Implement to perform an operation with the provided canvas.
- L253 _public prototype_ `UCanvasRenderTarget2D* GetTexture() const;` — `UE_DEPRECATED(5.8, "GetTexture (CanvasRenderTarget2D) has been deprecated. Use GetRenderTarget (TextureRenderTarget2DArray) and pass it into Mask_Textures parameter instead")` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Rendering", meta=(DeprecatedFunction, DeprecationMessage="GetTexture (CanvasRenderTarget2D) has been deprecated. Use GetRenderTarget (TextureRenderTarget2DArray) and pass it into Mask_Textures parameter instead"))`
- L257 _public prototype_ `UTextureRenderTarget2DArray* GetRenderTarget() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Rendering")` — Returns the render target 2D array that the canvas draws to
- L260 _protected prototype_ `virtual void BeginPlay() override;`
- L261 _protected prototype_ `virtual void PostLoad() override;`
- L262 _protected prototype_ `virtual void OnRegister() override;`
- L265 _protected prototype_ `virtual bool TryResolveCanvas() PURE_VIRTUAL(UGeometryMaskCanvasReferenceComponentBase::TryResolveCanvas, return false; ) bool TryResolveNamedCanvas(FName InCanvasName);` — Override to inject CanvasName into TryResolveCanvas(FName).
- L269 _protected prototype_ `[[maybe_unused]] virtual bool Cleanup();`
- L272 _protected prototype_ `virtual bool ForEachUsedCanvasName(TFunctionRef<bool(FName)> InFunc) const override;`
- L275 _protected member_ `FOnGeometryMaskSetCanvasNativeDelegate OnSetCanvasDelegate;`
- L279 _protected member_ `TWeakObjectPtr<UGeometryMaskCanvas> CanvasWeak;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Reference to the Canvas used, identified by CanvasName.

#### struct `FGeometryMaskBatchElementData`  
`struct FGeometryMaskBatchElementData`  
_L284-310_
- reflection: `USTRUCT()`
- desc: Mesh data for a single mesh, in local space.
- L289 _public member_ `TArray<FVector3f> Vertices;` — `UPROPERTY()`
- L292 _public member_ `TArray<uint32> Indices;` — `UPROPERTY()`
- L295 _public member_ `int32 NumTriangles = 0;` — `UPROPERTY()`
- L299 _public member_ `uint64 ChangeStamp = 0;` — `UPROPERTY()` — Used to check cached state.
- L301 _public function_ `void Reserve( const int32 InNumVertices, const int32 InNumIndices, const int32 InNumTriangles)`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace GeometryMask` (scope `UE`)
- L34 _variable_ `static TMap<FLinearColor, EGeometryMaskColorChannel> VectorToMaskChannelEnum = { { {1, 0, 0, 0}, EGeometryMaskColorChannel::Red }, { {0, 1, 0, 0}, EGeometryMaskColorChannel::Green }, { {0, 0, 1, 0}, EGeometryMaskColorChannel::Blue }, { {0, 0, 0, 1}, EGeometryMaskColorChannel::Alpha } };` (scope `UE::GeometryMask`) — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — Use to convert between a multiplied vector and an EGeometryMaskColorChannel enum value.
- L44 _variable_ `static TMap<EGeometryMaskColorChannel, FLinearColor> MaskChannelEnumToVector = { { EGeometryMaskColorChannel::Red, {1, 0, 0, 0} }, { EGeometryMaskColorChannel::Green, {0, 1, 0, 0} }, { EGeometryMaskColorChannel::Blue, {0, 0, 1, 0} }, { EGeometryMaskColorChannel::Alpha, {0, 0, 0, 1} } };` (scope `UE::GeometryMask`) — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — Use to convert between a EGeometryMaskColorChannel enum value and a multiplied vector.
- L54 _variable_ `static TMap<EGeometryMaskColorChannel, FColor> MaskChannelEnumToColor = { { EGeometryMaskColorChannel::Red, {255, 0, 0, 0} }, { EGeometryMaskColorChannel::Green, {0, 255, 0, 0} }, { EGeometryMaskColorChannel::Blue, {0, 0, 255, 0} }, { EGeometryMaskColorChannel::Alpha, {0, 0, 0, 255} } };` (scope `UE::GeometryMask`) — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — Use to convert between a EGeometryMaskColorChannel enum value and an FColor.
- L64 _variable_ `static TMap<EGeometryMaskColorChannel, FString> MaskChannelEnumToString = { { EGeometryMaskColorChannel::Red, TEXT("Red") }, { EGeometryMaskColorChannel::Green, TEXT("Green") }, { EGeometryMaskColorChannel::Blue, TEXT("Blue") }, { EGeometryMaskColorChannel::Alpha, TEXT("Alpha") }, { EGeometryMaskColorChannel::None, TEXT("None") }, { EGeometryMaskColorChannel::Num, TEXT("Num/Max") } };` (scope `UE::GeometryMask`) — Use to convert between a EGeometryMaskColorChannel and it's value name (as string).
- L75 _prototype_ `EGeometryMaskColorChannel VectorToMaskChannel(const FLinearColor& InVector);` (scope `UE::GeometryMask`) — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")`
- L79 _prototype_ `EGeometryMaskColorChannel GetValidMaskChannel(EGeometryMaskColorChannel InColorChannel, bool bInIncludeAlpha = false);` (scope `UE::GeometryMask`) — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — Returns a valid ColorChannel (R,G,B or A).
- L81 _prototype_ `FStringView ChannelToString(EGeometryMaskColorChannel InColorChannel);` (scope `UE::GeometryMask`)
- L179 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGeometryMaskSetCanvasDelegate, const UGeometryMaskCanvas*, InCanvas);`
- L179 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGeometryMaskSetCanvasDelegate, const UGeometryMaskCanvas*, InCanvas);`
- L180 _typedef_ `using FOnGeometryMaskSetCanvasNativeDelegate = TMulticastDelegate<void(const UGeometryMaskCanvas* InCanvas)>;`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/GeometryMaskWorldSubsystem.h` (Public)


#### struct `FGeometryMaskLevelState`  
`struct FGeometryMaskLevelState`  
_L22-42_
- reflection: `USTRUCT()`
- L28 _public member_ `TMap<FName, TObjectPtr<UGeometryMaskCanvas>> NamedCanvases;` — `UPROPERTY()` — All the canvases in the level
- L31 _public member_ `TArray<TWeakInterfacePtr<const IGeometryMaskClient>> MaskClients;` — All the clients using the mask canvases
- L35 _public member_ `TObjectPtr<UTextureRenderTarget2DArray> RenderTarget;` — `UPROPERTY()` — The render target where the canvases in the levels draw to
- L38 _public prototype_ `int32 AcquireAvailableSliceIndex();` — Returns the index to the first available slice in the render target
- L41 _public prototype_ `void CleanupUnusedCanvases();` — Cleans up all canvases that were registered but are no longer being used by any of the registered mask clients

#### class `UGeometryMaskWorldSubsystem`  
`class UGeometryMaskWorldSubsystem : public UWorldSubsystem`  
_L46-105_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- desc: Updates the canvases.
- L51 _public prototype_ `UGeometryMaskWorldSubsystem();`
- L54 _public prototype_ `UGeometryMaskCanvas* GetNamedCanvas(const ULevel* InLevel, FName InName);` — Retrieves a Canvas, uniquely identified by this world and the canvas name.
- L62 _public prototype_ `UGeometryMaskCanvas* GetNamedCanvas(const ULevel* InLevel, FName InName, const IGeometryMaskClient* InMaskClient);` — Retrieves a Canvas, uniquely identified by this world and the canvas name. @param InLevel the level that the canvas relates to @param InName the name of the canvas @param InMaskClient the user of the mask (if any)
- L65 _public prototype_ `TArray<FName> GetCanvasNames(const ULevel* InLevel);` — Returns all registered canvas names for this world.
- L68 _public prototype_ `int32 RemoveWithoutWriters();` — Remove all canvases without any Readers or Writers. Return the number of canvases removed.
- L71 _public function_ `FOnGeometryMaskCanvasCreated& OnGeometryMaskCanvasCreated()` — Called when a new canvas is created due to a unique name being requested.
- L77 _public function_ `FOnGeometryMaskCanvasDestroyed& OnGeometryMaskCanvasDestroyed()` — Called when a canvas is destroyed due to having no registered writers.
- L84 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L85 _protected prototype_ `virtual void Deinitialize() override;`
- L89 _private prototype_ `const FGeometryMaskLevelState* FindLevelState(const ULevel* InLevel) const;`
- L91 _private prototype_ `FGeometryMaskLevelState& FindOrAddLevelState(const ULevel* InLevel);`
- L95 _private member_ `TSharedPtr<FGeometryMaskSceneViewExtension> GeometryMaskSceneViewExtension;`
- L97 _private member_ `FOnGeometryMaskCanvasCreated OnGeometryMaskCanvasCreatedDelegate;`
- L98 _private member_ `FOnGeometryMaskCanvasDestroyed OnGeometryMaskCanvasDestroyedDelegate;`
- L101 _private member_ `TMap<TWeakObjectPtr<const ULevel>, FGeometryMaskLevelState> LevelStates;` — `UPROPERTY()`
- L104 _private member_ `TSharedPtr<FGeometryMaskCanvasSharedData> SharedData;` — Shared data for canvases of the world presented

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYMASK_API`
- L18 _typedef_ `using FOnGeometryMaskCanvasCreated = TMulticastDelegate<void(const UGeometryMaskCanvas*)>;`
- L19 _typedef_ `using FOnGeometryMaskCanvasDestroyed = TMulticastDelegate<void(const FGeometryMaskCanvasId&)>;`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/GeometryMaskWriteComponent.h` (Public)


#### class `UGeometryMaskWriteMeshComponent`  
`class UGeometryMaskWriteMeshComponent: public UGeometryMaskCanvasReferenceComponentBase, public IGeometryMaskWriteInterface`  
_L23-106_
- reflection: `UCLASS(MinimalAPI, BlueprintType, HideCategories=(Activation, Cooking, AssetUserData, Navigation), meta=(BlueprintSpawnableComponent))`
- inherits: `UGeometryMaskCanvasReferenceComponentBase,IGeometryMaskWriteInterface`
- L28 _public prototype_ `UGeometryMaskWriteMeshComponent();`
- L31 _public prototype_ `virtual bool IsMaskWriterEnabled() const override;`
- L32 _public prototype_ `virtual void SetParameters(FGeometryMaskWriteParameters& InParameters) override;`
- L33 _public function_ `virtual const FGeometryMaskWriteParameters& GetParameters() const override`
- L37 _public prototype_ `virtual void DrawToCanvas(FCanvas* InCanvas) override;`
- L38 _public function_ `virtual FOnGeometryMaskSetCanvasNativeDelegate& OnSetCanvas() override`
- L42 _public prototype_ `virtual UE::GeometryMask::FMaskWriter* GetMaskWriter() override;`
- L47 _protected prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L51 _protected prototype_ `virtual bool ForEachUsedCanvasName(TFunctionRef<bool(FName)> InFunc) const override;`
- L55 _protected prototype_ `virtual bool TryResolveCanvas() override;`
- L56 _protected prototype_ `virtual bool Cleanup() override;`
- L61 _protected prototype_ `void ResetCachedData();` — `UE_DEPRECATED(5.8, "Logic moved to UE::GeometryMask::FMaskWriter")` — Resets cached data, triggers rebuild
- L64 _protected prototype_ `void UpdateCachedData();` — `UE_DEPRECATED(5.8, "Logic moved to UE::GeometryMask::FMaskWriter")`
- L67 _protected prototype_ `void UpdateCachedStaticMeshData(TConstArrayView<UPrimitiveComponent*> InPrimitiveComponents);` — `UE_DEPRECATED(5.8, "Logic moved to UE::GeometryMask::FMaskWriter")`
- L70 _protected prototype_ `void UpdateCachedDynamicMeshData(TConstArrayView<UPrimitiveComponent*> InPrimitiveComponents);` — `UE_DEPRECATED(5.8, "Logic moved to UE::GeometryMask::FMaskWriter")`
- L74 _protected prototype_ `void OnStaticMeshChanged(UStaticMeshComponent* InStaticMeshComponent);` — `UE_DEPRECATED(5.8, "Logic moved to UE::GeometryMask::FMaskWriter")`
- L77 _protected prototype_ `void OnDynamicMeshChanged(UDynamicMeshComponent* InDynamicMeshComponent);` — `UE_DEPRECATED(5.8, "Logic moved to UE::GeometryMask::FMaskWriter")`
- L80 _protected member_ `FGeometryMaskWriteParameters Parameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mask", meta=(ShowOnlyInnerProperties))`
- L84 _protected member_ `bool bWriteWhenHidden = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mask")` — Write to the mask even when this or it's owner is hidden.
- L88 _protected member_ `int32 LastPrimitiveComponentCount;` — `UE_DEPRECATED(5.8, "Deprecated to use MaskWriter instead")` — `UPROPERTY(Transient, meta=(DeprecatedProperty, DeprecatedMessage="Deprecated to use MaskWriter instead"))`
- L92 _protected member_ `TMap<FName, TWeakObjectPtr<UPrimitiveComponent>> CachedComponentsWeak;` — `UE_DEPRECATED(5.7, "Deprecated to use MaskWriter instead")` — `UPROPERTY(Transient, meta=(DeprecatedProperty, DeprecatedMessage="Deprecated to use MaskWriter instead"))`
- L97 _protected member_ `TMap<TWeakObjectPtr<UPrimitiveComponent>, FName> CachedComponents;` — `UE_DEPRECATED(5.8, "Deprecated to use MaskWriter instead")` — `UPROPERTY(Transient, meta=(DeprecatedProperty, DeprecatedMessage="Deprecated to use MaskWriter instead"))` — Cached primitive component to mesh name, multiple components can use same mesh data
- L102 _protected member_ `TMap<FName, FGeometryMaskBatchElementData> CachedMeshData;` — `UE_DEPRECATED(5.8, "Deprecated to use MaskWriter instead")` — `UPROPERTY(Transient, meta=(DeprecatedProperty, DeprecatedMessage="Deprecated to use MaskWriter instead"))` — Cached mesh name to data (one entry per unique mesh)
- L105 _protected member_ `TSharedPtr<UE::GeometryMask::FMaskWriter> MaskWriter;` — Handles caching and drawing the mask

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYMASK_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace GeometryMask` (scope `UE`)

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/GeometryMaskWriter.h` (Public)


#### struct `UE::GeometryMask::FMaskWriter`  
`struct FMaskWriter : public TSharedFromThis<FMaskWriter>`  
_L21-61_
- inherits: `TSharedFromThis<FMaskWriter>`
- desc: Handles writing to the mask canvas and caching component draw data
- L23 _public prototype_ `static TSharedRef<FMaskWriter> Create();`
- L36 _public prototype_ `void DrawToCanvas(const FDrawParams& InParams);`
- L39 _public prototype_ `void ForEachMaskPrimitive(TFunctionRef<void(TNotNull<const UPrimitiveComponent*>)> InFunc) const;` — Iterates each primitive that is masked
- L43 _private prototype_ `void ResetCachedData();` — Resets cached data, triggers rebuild
- L44 _private prototype_ `void UpdateCachedData(AActor* InActor);`
- L45 _private prototype_ `void UpdateCachedStaticMeshData(TConstArrayView<UPrimitiveComponent*> InPrimitiveComponents);`
- L46 _private prototype_ `void UpdateCachedDynamicMeshData(TConstArrayView<UPrimitiveComponent*> InPrimitiveComponents);`
- L49 _private prototype_ `void OnStaticMeshChanged(UStaticMeshComponent* InStaticMeshComponent);`
- L51 _private prototype_ `void OnDynamicMeshChanged(UDynamicMeshComponent* InDynamicMeshComponent);`
- L54 _private member_ `TMap<TObjectKey<UPrimitiveComponent>, FObjectKey> CachedComponents;` — Cached primitive component to the mesh object used, multiple components can use same mesh data
- L57 _private member_ `TMap<FObjectKey, FGeometryMaskBatchElementData> CachedMeshData;` — Cached mesh object to its batch element data (one entry per unique mesh)
- L60 _private member_ `TMap<TObjectKey<AActor>, int32> LastPrimitiveComponentCountMap;` — Cached component count per actor

#### struct `UE::GeometryMask::FMaskWriter::FDrawParams`  
`struct FDrawParams`  
_L25-35_
- L28 _public member_ `FCanvas* Canvas = nullptr;` — The canvas to write to
- L30 _public member_ `AActor* Actor = nullptr;` — The actor to gather components from
- L32 _public member_ `TNotNull<const FGeometryMaskWriteParameters*> Parameters;` — Write parameters
- L34 _public member_ `bool bWriteWhenHidden = true;` — Whether to write the actor if it's hidden

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYMASK_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace GeometryMask` (scope `UE`)

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/IGeometryMaskClient.h` (Public)


#### class `UGeometryMaskClient`  
`class UGeometryMaskClient : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IGeometryMaskClient`  
`class IGeometryMaskClient`  
_L17-24_
- desc: Interface for objects using canvases
- L23 _public prototype_ `virtual bool ForEachUsedCanvasName(TFunctionRef<bool(FName)> InFunc) const = 0;` — Iterates each canvas that the client uses

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/IGeometryMaskModule.h` (Public)


#### class `IGeometryMaskModule`  
`class IGeometryMaskModule : public IModuleInterface`  
_L7-17_
- inherits: `IModuleInterface`
- L16 _public prototype_ `static IGeometryMaskModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/IGeometryMaskReadInterface.h` (Public)


#### class `UGeometryMaskReadInterface`  
`class UGeometryMaskReadInterface : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IGeometryMaskReadInterface`  
`class IGeometryMaskReadInterface`  
_L19-27_
- desc: Implement to Read from a host GeometryMaskCanvas.
- L24 _public prototype_ `virtual const FGeometryMaskReadParameters& GetParameters() const = 0;`
- L25 _public prototype_ `virtual void SetParameters(FGeometryMaskReadParameters& InParameters) = 0;`
- L26 _public prototype_ `virtual FOnGeometryMaskSetCanvasNativeDelegate& OnSetCanvas() = 0;`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Public/IGeometryMaskWriteInterface.h` (Public)


#### class `UGeometryMaskWriteInterface`  
`class UGeometryMaskWriteInterface : public UInterface`  
_L18-21_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IGeometryMaskWriteInterface`  
`class IGeometryMaskWriteInterface`  
_L24-44_
- desc: Implement to write to a host canvas.
- L29 _public function_ `virtual bool IsMaskWriterEnabled() const`
- L33 _public prototype_ `virtual const FGeometryMaskWriteParameters& GetParameters() const = 0;`
- L34 _public prototype_ `virtual void SetParameters(FGeometryMaskWriteParameters& InParameters) = 0;`
- L35 _public prototype_ `virtual void DrawToCanvas(FCanvas* InCanvas) = 0;`
- L36 _public prototype_ `virtual FOnGeometryMaskSetCanvasNativeDelegate& OnSetCanvas() = 0;`
- L39 _public function_ `virtual UE::GeometryMask::FMaskWriter* GetMaskWriter()` — Gets the mask writer for this interface

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace GeometryMask` (scope `UE`)
