# Plugins / LandscapePatch

- module root: `Plugins/Editor/LandscapePatch/Source/LandscapePatch`
- headers: 11; symbols: 503
- symbol kinds: class=21, enum=10, enumerator=35, function=71, member=102, namespace=9, prototype=248, struct=5, typedef=2
- PrivateDependencyModuleNames: LevelEditor, Projects, RHI, RenderCore, Renderer, TypedElementRuntime, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Landscape

### `Plugins/Editor/LandscapePatch/Source/LandscapePatch/Private/LandscapeCircleHeightPatchPS.h` (Private)


#### class `FLandscapeCircleHeightPatchPS`  
`class FLandscapeCircleHeightPatchPS : public FGlobalShader`  
_L11-31_
- inherits: `FGlobalShader`
- desc: Shader that applies a circle height patch to a landscape heightmap.
- L13 _private prototype_ `DECLARE_GLOBAL_SHADER(FLandscapeCircleHeightPatchPS);`
- L14 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FLandscapeCircleHeightPatchPS, FGlobalShader);`
- L18 _public prototype_ `SHADER_PARAMETER(FVector3f, InCenter) SHADER_PARAMETER(float, InRadius) SHADER_PARAMETER(float, InFalloff)`
- L28 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L30 _public prototype_ `static void AddToRenderGraph(FRDGEventName&& InRDGEventName, FRDGBuilder& GraphBuilder, FParameters* InParameters, const FIntRect& DestinationBounds);`

#### class `FLandscapeCircleVisibilityPatchPS`  
`class FLandscapeCircleVisibilityPatchPS : public FLandscapeCircleHeightPatchPS`  
_L36-49_
- inherits: `FLandscapeCircleHeightPatchPS`
- desc: Shader that applies a circle patch to a landscape visibility layer.
- L38 _private prototype_ `DECLARE_GLOBAL_SHADER(FLandscapeCircleVisibilityPatchPS);`
- L41 _public prototype_ `FLandscapeCircleVisibilityPatchPS() = default;`
- L42 _public function_ `FLandscapeCircleVisibilityPatchPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FLandscapeCircleHeightPatchPS(Initializer)`
- L47 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L48 _public prototype_ `static void AddToRenderGraph(FRDGEventName&& InRDGEventName, FRDGBuilder& GraphBuilder, FParameters* InParameters, const FIntRect& DestinationBounds);`

### `Plugins/Editor/LandscapePatch/Source/LandscapePatch/Private/LandscapeTexturePatchPS.h` (Private)


#### class `UE::Landscape::FApplyLandscapeTextureHeightPatchPS`  
`class FApplyLandscapeTextureHeightPatchPS : public FGlobalShader`  
_L19-84_
- inherits: `FGlobalShader`
- desc: Shader that applies a texture-based height patch to a landscape heightmap.
- L21 _private prototype_ `DECLARE_GLOBAL_SHADER(FApplyLandscapeTextureHeightPatchPS);`
- L22 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FApplyLandscapeTextureHeightPatchPS, FGlobalShader);`
- L45 _public prototype_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, InHeightPatch) SHADER_PARAMETER_SAMPLER(SamplerState, InHeightPatchSampler) SHADER_PARAMETER(FMatrix44f, InHeightmapToPatchUV)`
- L81 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L83 _public prototype_ `static void AddToRenderGraph(FRDGEventName&& InRDGEventName, FRDGBuilder& GraphBuilder, FParameters* InParameters, const FIntRect& DestinationBounds);`

#### enum `UE::Landscape::FApplyLandscapeTextureHeightPatchPS::EFlags`  
`enum class EFlags : uint8`  
_L27-37_
- desc: Flags that get packed into a bitfield because we're not allowed to use bool shader parameters:
- L29 _public enumerator_ `None = 0`
- L32 _public enumerator_ `RectangularFalloff = 1 << 0` — When false, falloff is circular.
- L36 _public enumerator_ `InputIsPackedHeight = 1 << 1` — When false, the input is directly interpreted as being the height value to process. When true, the height is unpacked from the red and green channels to make a 16 bit int.

#### class `UE::Landscape::FApplyLandscapeTextureHeightPatchPSParameters`  
`class FApplyLandscapeTextureHeightPatchPSParameters : public FApplyLandscapeTextureHeightPatchPS::FParameters`  
_L87-87_
- inherits: `FApplyLandscapeTextureHeightPatchPS::FParameters`
- desc: We need an alias for FApplyLandscapeTextureHeightPatchPS::FParameters so that it can be forward-declared in another header file (cannot forward-declare internal classes)

#### class `UE::Landscape::FOffsetHeightmapPS`  
`class FOffsetHeightmapPS : public FGlobalShader`  
_L94-111_
- inherits: `FGlobalShader`
- desc: Simple shader that just offsets each height value in a height patch by a constant.
- L96 _private prototype_ `DECLARE_GLOBAL_SHADER(FOffsetHeightmapPS);`
- L97 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FOffsetHeightmapPS, FGlobalShader);`
- L102 _public prototype_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, InHeightmap) SHADER_PARAMETER(float, InHeightOffset) RENDER_TARGET_BINDING_SLOTS()`
- L108 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L110 _public prototype_ `static void AddToRenderGraph(FRDGBuilder& GraphBuilder, FParameters* InParameters);`

#### class `UE::Landscape::FConvertToNativeLandscapePatchPS`  
`class FConvertToNativeLandscapePatchPS : public FGlobalShader`  
_L119-139_
- inherits: `FGlobalShader`
- desc: Shader that converts a texture stored in some other encoding (where height is in the R channel) to the landscape "native" encoding, where height is stored as a 16 bit int split across the R and G channels. This is not perfectly reversible (in case of clamping and due to rounding), but it lets us store the texture in the way that it would be applied to the landscape (usually).
- L121 _private prototype_ `DECLARE_GLOBAL_SHADER(FConvertToNativeLandscapePatchPS);`
- L122 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FConvertToNativeLandscapePatchPS, FGlobalShader);`
- L127 _public prototype_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, InHeightmap) SHADER_PARAMETER(float, InZeroInEncoding) SHADER_PARAMETER(float, InHeightScale) SHADER_PARAMETER(float, InHeightOffset) RENDER_TARGET_BINDING_SLOTS()`
- L135 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L137 _public prototype_ `static void AddToRenderGraph(FRDGBuilder& GraphBuilder, FRDGTextureRef SourceTexture, FRDGTextureRef DestinationTexture, const FLandscapeHeightPatchConvertToNativeParams& Params);`

#### class `UE::Landscape::FConvertBackFromNativeLandscapePatchPS`  
`class FConvertBackFromNativeLandscapePatchPS : public FGlobalShader`  
_L145-165_
- inherits: `FGlobalShader`
- desc: Shader that undoes the conversion done by FConvertToNativeLandscapePatchPS (to the extent possible, since rounding/clamping makes it not perfectly recoverable).
- L147 _private prototype_ `DECLARE_GLOBAL_SHADER(FConvertBackFromNativeLandscapePatchPS);`
- L148 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FConvertBackFromNativeLandscapePatchPS, FGlobalShader);`
- L153 _public prototype_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, InHeightmap) SHADER_PARAMETER(float, InZeroInEncoding) SHADER_PARAMETER(float, InHeightScale) SHADER_PARAMETER(float, InHeightOffset) RENDER_TARGET_BINDING_SLOTS()`
- L161 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L163 _public prototype_ `static void AddToRenderGraph(FRDGBuilder& GraphBuilder, FRDGTextureRef SourceTexture, FRDGTextureRef DestinationTexture, const FLandscapeHeightPatchConvertToNativeParams& Params);`

#### class `UE::Landscape::FApplyLandscapeTextureWeightPatchPS`  
`class FApplyLandscapeTextureWeightPatchPS : public FGlobalShader`  
_L167-222_
- inherits: `FGlobalShader`
- L169 _private prototype_ `DECLARE_GLOBAL_SHADER(FApplyLandscapeTextureWeightPatchPS);`
- L170 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FApplyLandscapeTextureWeightPatchPS, FGlobalShader);`
- L189 _public prototype_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, InWeightPatch) SHADER_PARAMETER_SAMPLER(SamplerState, InWeightPatchSampler) SHADER_PARAMETER(FMatrix44f, InWeightmapToPatchUV)`
- L219 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L221 _public prototype_ `static void AddToRenderGraph(FRDGEventName&& InRDGEventName, FRDGBuilder& GraphBuilder, FParameters* InParameters, const FIntRect& DestinationBounds);`

#### enum `UE::Landscape::FApplyLandscapeTextureWeightPatchPS::EFlags`  
`enum class EFlags : uint8`  
_L175-181_
- desc: Flags that get packed into a bitfield because we're not allowed to use bool shader parameters:
- L177 _public enumerator_ `None = 0`
- L180 _public enumerator_ `RectangularFalloff = 1 << 0` — When false, falloff is circular.

#### class `UE::Landscape::FApplyLandscapeTextureWeightPatchPSParameters`  
`class FApplyLandscapeTextureWeightPatchPSParameters : public FApplyLandscapeTextureWeightPatchPS::FParameters`  
_L225-225_
- inherits: `FApplyLandscapeTextureWeightPatchPS::FParameters`
- desc: We need an alias for FApplyLandscapeTextureWeightPatchPSParameters::FParameters so that it can be forward-declared in another header file (cannot forward-declare internal classes)

#### class `UE::Landscape::FReinitializeLandscapePatchPS`  
`class FReinitializeLandscapePatchPS : public FGlobalShader`  
_L229-251_
- inherits: `FGlobalShader`
- L231 _private prototype_ `DECLARE_GLOBAL_SHADER(FReinitializeLandscapePatchPS);`
- L232 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FReinitializeLandscapePatchPS, FGlobalShader);`
- L237 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FHeightPatch>;`
- L240 _public prototype_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, InSource) SHADER_PARAMETER_SAMPLER(SamplerState, InSourceSampler) SHADER_PARAMETER(FMatrix44f, InPatchToSource) RENDER_TARGET_BINDING_SLOTS()`
- L248 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L250 _public prototype_ `static void AddToRenderGraph(FRDGBuilder& GraphBuilder, FParameters* InParameters, bool bHeightPatch);`

#### class `UE::Landscape::FSimpleTextureCopyPS`  
`class FSimpleTextureCopyPS : public FGlobalShader`  
_L258-276_
- inherits: `FGlobalShader`
- L260 _private prototype_ `DECLARE_GLOBAL_SHADER(FSimpleTextureCopyPS);`
- L261 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FSimpleTextureCopyPS, FGlobalShader);`
- L266 _public prototype_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, InSource) SHADER_PARAMETER_SAMPLER(SamplerState, InSourceSampler) SHADER_PARAMETER(FVector2f, InDestinationResolution) RENDER_TARGET_BINDING_SLOTS()`
- L273 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L275 _public prototype_ `static void AddToRenderGraph(FRDGBuilder& GraphBuilder, FRDGTextureRef SourceTexture, FRDGTextureRef DestinationTexture);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Landscape` (scope `UE`)
- L89 _prototype_ `ENUM_CLASS_FLAGS(FApplyLandscapeTextureHeightPatchPS::EFlags);` (scope `UE::Landscape`)
- L227 _prototype_ `ENUM_CLASS_FLAGS(FApplyLandscapeTextureWeightPatchPS::EFlags);` (scope `UE::Landscape`)

### `Plugins/Editor/LandscapePatch/Source/LandscapePatch/Public/LandscapeCircleHeightPatch.h` (Public)


#### class `ULandscapeCircleHeightPatch`  
`class ULandscapeCircleHeightPatch : public ULandscapePatchComponent`  
_L24-74_
- reflection: `UCLASS(Blueprintable, BlueprintType, ClassGroup = Landscape, meta = (BlueprintSpawnableComponent))`
- inherits: `ULandscapePatchComponent`
- desc: The simplest height patch: a circle of flat ground with a falloff past the initial radius across which the alpha decreases linearly. When added to an actor, initializes itself to the bottom of the bounding box.
- L32 _public prototype_ `virtual void GetRendererStateInfo(const UE::Landscape::EditLayers::FMergeContext* InMergeContext, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutSupportedTargetTypeState, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutEnabledTargetTypeState, TArray<UE::Landscape::EditLayers::FTargetLayerGroup>& OutTargetLayerGroups) const override;` — ILandscapeEditLayerRenderer, via ULandscapePatchComponent
- L36 _public prototype_ `virtual FString GetEditLayerRendererDebugName() const override;`
- L37 _public prototype_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRenderItem> GetRenderItems(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override;`
- L38 _public prototype_ `virtual UE::Landscape::EditLayers::ERenderFlags GetRenderFlags(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override;`
- L39 _public prototype_ `virtual bool CanGroupRenderLayerWith(TScriptInterface<ILandscapeEditLayerRenderer> InOtherRenderer) const override;`
- L40 _public prototype_ `virtual bool RenderLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder) override;`
- L41 _public prototype_ `virtual void BlendLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder) override;`
- L44 _public function_ `virtual bool CanAffectHeightmap() const override`
- L45 _public function_ `virtual bool CanAffectVisibilityLayer() const override`
- L48 _public prototype_ `virtual void OnComponentCreated() override;` — UActorComponent
- L53 _protected member_ `float Radius = 500;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L57 _protected member_ `float Falloff = 500;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Distance across which the alpha will go from 1 down to 0 outside of circle.
- L61 _protected member_ `bool bEditVisibility = false;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Specifies if this patch edits the visibility layer instead of height.
- L66 _protected member_ `bool bExclusiveRadius = false;` — `UPROPERTY(EditAnywhere, Category = Settings, AdvancedDisplay)` — When true, only the vertices in the circle have alpha 1. If false, the radius is expanded slightly so that neighboring vertices are also included and the whole circle is able to lie flat.
- L70 _private prototype_ `bool ApplyCirclePatch(UE::Landscape::EditLayers::FRenderParams* RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder, bool bIsVisibilityLayer, FTextureResource* InMergedLandscapeTextureResource, int32 LandscapeTextureSliceIndex, const FIntPoint& DestinationResolution, const FTransform& HeightmapCoordsToWorld, ERHIAccess OutputAccess = ERHIAccess::None);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Landscape` (scope `UE`)

### `Plugins/Editor/LandscapePatch/Source/LandscapePatch/Public/LandscapePatchComponent.h` (Public)


#### enum `ELandscapePatchPriorityInitialization`  
`enum class ELandscapePatchPriorityInitialization : uint8`  
_L23-38_
- reflection: `UENUM()`
- L28 _public enumerator_ `AcquireHighest` — Initialize priority to highest currently known value, so that the new patch is on top of any existing patches. Note that the highest known priority could be out of date in between landscape updates if priorities change, so it is possible that adjustment will still be needed.
- L32 _public enumerator_ `KeepOriginal` — Do not change the default/archetype priority value. This is useful when using custom priority values as categories.
- L37 _public enumerator_ `SmallIncrement` — Increment the original priority by a small amount (0.01). This can be useful when copying a patch around multiple times, as it allows the new patches to be roughly in the same place in the priority hierarchy while still being higher priority than the copied patch.

#### class `ULandscapePatchComponent`  
`class ULandscapePatchComponent : public USceneComponent , public ILandscapeEditLayerRenderer`  
_L47-261_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Abstract, HideCategories = (Tags, Activation, Cooking, Physics, Rendering, Navigation, LOD))`
- inherits: `USceneComponent,ILandscapeEditLayerRenderer`
- L53 _public prototype_ `ULandscapePatchComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L62 _public function_ `virtual bool CanAffectHeightmap() const` — These determine whether the patch is configured correctly to affect height/weightmaps, ignoring whether it is currently enabled or not.
- L63 _public function_ `virtual bool CanAffectWeightmap() const`
- L64 _public function_ `virtual bool CanAffectWeightmapLayer(const FName& InLayerName) const`
- L65 _public function_ `virtual bool CanAffectVisibilityLayer() const`
- L67 _public function_ `bool CanAffectLandscape() const`
- L70 _public function_ `bool AffectsHeightmap() const` — These compose IsEnabled with the appropriate CanAffect functions
- L71 _public function_ `bool AffectsWeightmap() const`
- L72 _public function_ `bool AffectsWeightmapLayer(const FName& InLayerName) const`
- L73 _public function_ `bool AffectsVisibilityLayer() const`
- L76 _public function_ `virtual void GetRenderDependencies(TSet<UObject*>& OutDependencies) const` — Allows the patch to specify textures that need to be ready/compiled before applying the patch
- L79 _public prototype_ `void RequestLandscapeUpdate(bool bInUserTriggeredUpdate = false);` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch")`
- L86 _public prototype_ `void SetIsEnabled(bool bEnabledIn);` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch")` — Allows the patch to be disabled, so that it no longer affects the landscape. This can be useful when deleting the patch is undesirable, usually when the disabling is temporary.
- L92 _public function_ `virtual bool IsEnabled() const` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch")` — @return false if the patch is marked as disabled and therefore can't affect the landscape.
- L95 _public function_ `double GetPriority() const` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch")`
- L98 _public prototype_ `void SetPriority(double PriorityIn);` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch")`
- L101 _public function_ `FGuid GetEditLayerGuid() const` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch")`
- L104 _public prototype_ `void SetEditLayerGuid(const FGuid& GuidIn);` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch")`
- L114 _public prototype_ `bool AssignToLandscape(ALandscape* InLandscape, const FName& InEditLayerName);` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch")` — Tries to assign the patch to the landscape @param InLandscape Landscape actor on which the patch component should be applied. Passing an null actor will un-assign the patch component from any landscape @param InEditLayerName Name of the edit layer on which the patch component should be assigned. The layer name has to be present on the landscape and it has to be a Landscape Patch Edit Layer for this to succeed @return true if the patch was successfully assigned (or un-assigned) to (from) the landscape's edit layer
- L120 _public prototype_ `uint32 GetFullNameHash() const;` — Returns the result of GetTypeHash(GetFullName()) for this component. Useful for quick deterministic (though not lexical) ordering of same-priority patches.
- L123 _public prototype_ `FTransform GetLandscapeHeightmapCoordsToWorld() const;` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch")`
- L126 _public function_ `ALandscape* GetLandscape() const` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch")`
- L129 _public prototype_ `virtual void SetLandscape(ALandscape* NewLandscape);` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch")`
- L133 _public prototype_ `virtual void SetPatchManager(ADEPRECATED_LandscapePatchManager* NewPatchManager);` — `UE_DEPRECATED(all, "Patch manager use is deprecated. Patches should point to an edit layer using a Guid, and order themselves using priority.")` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch", meta = (DeprecatedFunction, DeprecationMessage = "Patch manager use is deprecated. Patches should point to an edit layer using a Guid, and order themselves using priority."))`
- L137 _public prototype_ `virtual ADEPRECATED_LandscapePatchManager* GetPatchManager() const;` — `UE_DEPRECATED(all, "Patch manager use is deprecated. Patches should point to an edit layer using a Guid, and order themselves using priority.")` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch", meta = (DeprecatedFunction, DeprecationMessage = "Patch manager use is deprecated. Patches should point to an edit layer using a Guid, and order themselves using priority."))`
- L140 _public prototype_ `bool IsPatchInWorld() const;` — Verifies that we're not an archetype or trash or in an invalid world
- L149 _public prototype_ `void FixBindings();` — Cleanup method that can be used to fix the patch's binding to a landscape. An arbitrary landscape will be bound to if no guid, or no landscape is set on the patch.
- L152 _public prototype_ `void NotifyOfBoundLayerDeletion(ULandscapePatchEditLayer* LayerIn);` — Allows the patch to update its UI and cached pointer
- L155 _public prototype_ `virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport) override;` — USceneComponent
- L158 _public prototype_ `virtual void CheckForErrors() override;` — UActorComponent
- L159 _public prototype_ `virtual void OnComponentCreated() override;`
- L160 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L161 _public prototype_ `virtual void OnRegister() override;`
- L162 _public prototype_ `virtual void GetActorDescProperties(FPropertyPairsMap& PropertyPairsMap) const override;`
- L163 _public prototype_ `virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;`
- L166 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject
- L167 _public function_ `virtual bool IsPostLoadThreadSafe() const override`
- L168 _public prototype_ `virtual void PostLoad() override;`
- L169 _public prototype_ `virtual void PostEditUndo() override;`
- L171 _public function_ `virtual bool IsEditorOnly() const override`
- L172 _public function_ `virtual bool NeedsLoadForClient() const override`
- L173 _public function_ `virtual bool NeedsLoadForServer() const override`
- L177 _protected function_ `ULandscapePatchEditLayer* GetBoundEditLayer() const`
- L182 _protected member_ `FGuid EditLayerGuid;` — `UPROPERTY()` — Guid of the edit layer to which the patch is bound
- L186 _protected member_ `ELandscapePatchPriorityInitialization PriorityInitialization = ELandscapePatchPriorityInitialization::AcquireHighest;` — `UPROPERTY(EditAnywhere, Category = Settings, AdvancedDisplay)` — How to initialize the patch priority when a patch is first created.
- L190 _protected member_ `double Priority = ULandscapePatchEditLayer::PATCH_PRIORITY_BASE;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Value that determines the patch ordering relative to other patches.
- L193 _protected member_ `TSoftObjectPtr<ALandscape> Landscape = nullptr;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L199 _protected member_ `bool bIsEnabled = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — When false, patch does not affect the landscape. Useful for temporarily disabling the patch.
- L202 _protected member_ `bool bWasCopy = false;` — Determines whether the height patch was made by copying a different height patch.
- L209 _private member_ `bool bPropertiesCopiedIndicator = false;` — `UPROPERTY()` — Starts as false and gets set to true in construction, so gets used to set bWasCopy by checking the indicator value at the start of construction.
- L218 _private member_ `TSoftObjectPtr<ADEPRECATED_LandscapePatchManager> PatchManager_DEPRECATED = nullptr;` — `UPROPERTY()` — Deprecated: Patch manager that can hold the patch as part of its legacy patch list. Instead, patches should now point to an edit layer via a guid and order themselves using their priority value.
- L225 _private member_ `FString DetailPanelLayerName = TEXT("-Nu` — `UPROPERTY(Transient, EditAnywhere, Category = Settings, Meta = (DisplayName="Edit Layer", GetOptions = "GetLayerOptions"))` — Name of the edit layer to which the patch is bound. Options are determined by the set Landscape pointer.
- L228 _private member_ `FString DetailPanelLayerGuid = EditLayerGuid.ToString();` — `UPROPERTY(Transient, VisibleAnywhere, Category = Settings, AdvancedDisplay, Meta = (DisplayName = "Layer Guid"))`
- L233 _private prototype_ `const TArray<FString> GetLayerOptions();` — `UFUNCTION()`
- L238 _private member_ `TWeakObjectPtr<ULandscapePatchEditLayer> EditLayer;` — Transient pointer to the edit layer that we are bound to using EditLayerGuid. Will be null if that layer is not of an appropriate type.
- L240 _private prototype_ `bool BindToEditLayer(const FGuid& Guid);`
- L241 _private prototype_ `void ResetEditLayer();`
- L242 _private prototype_ `bool BindToLandscape(ALandscape* LandscapeIn);`
- L243 _private prototype_ `bool BindToAnyLandscape();`
- L244 _private prototype_ `void UpdateEditLayerFromDetailPanelLayerName();`
- L247 _private prototype_ `bool IsPatchPreview();` — Tells us whether the patch is attached to an actor that is being dragged around as an editor preview
- L250 _private member_ `bool bGaveCouldNotBindToEditLayerWarning = false;` — Used to avoid spamming warning messages
- L251 _private member_ `bool bGaveMissingEditLayerGuidWarning = false;`
- L252 _private member_ `bool bGaveMismatchedLandscapeWarning = false;`
- L253 _private prototype_ `void ResetWarnings();`
- L254 _private member_ `bool bInstanceDataApplied = false;`
- L255 _private member_ `bool bDeferUpdateRequestUntilInstanceData = false;`
- L257 _private prototype_ `void ApplyComponentInstanceData(struct FLandscapePatchComponentInstanceData* ComponentInstanceData, ECacheApplyPhase CacheApplyPhase);`

#### struct `FLandscapePatchComponentInstanceData`  
`struct FLandscapePatchComponentInstanceData : public FSceneComponentInstanceData`  
_L265-324_
- reflection: `USTRUCT()`
- inherits: `FSceneComponentInstanceData`
- desc: Used to store some extra data during RerunConstructionScripts.
- L269 _public prototype_ `FLandscapePatchComponentInstanceData() = default;`
- L270 _public prototype_ `FLandscapePatchComponentInstanceData(const ULandscapePatchComponent* SourceComponent);`
- L274 _public prototype_ `FLandscapePatchComponentInstanceData(const FLandscapePatchComponentInstanceData&) = default;` — `UE_DEPRECATED(5.7, ...)`
- L275 _public prototype_ `FLandscapePatchComponentInstanceData(FLandscapePatchComponentInstanceData&&) = default;`
- L276 _public prototype_ `FLandscapePatchComponentInstanceData& operator=(const FLandscapePatchComponentInstanceData&) = default;`
- L277 _public prototype_ `FLandscapePatchComponentInstanceData& operator=(FLandscapePatchComponentInstanceData&&) = default;`
- L280 _public prototype_ `virtual ~FLandscapePatchComponentInstanceData() = default;`
- L282 _public function_ `virtual bool ContainsData() const override`
- L287 _public function_ `virtual void ApplyToComponent(UActorComponent* Component, const ECacheApplyPhase CacheApplyPhase) override`
- L300 _public member_ `TSoftObjectPtr<ADEPRECATED_LandscapePatchManager> PatchManager_DEPRECATED = nullptr;` — `UPROPERTY()`
- L302 _public member_ `FGuid EditLayerGuid;` — `UPROPERTY()`
- L306 _public member_ `double Priority = 0;` — `UPROPERTY()` — Priority needs to be carried over becuse our tweaks to it in OnComponentCreated cause it to not be captured automatically, as it is detected as "UCS altered".
- L311 _public member_ `bool bGaveCouldNotBindToEditLayerWarning = false;` — `UPROPERTY()` — Used so that we don't spam warning messages while rerunning construction scripts on a patch that triggers one of the warnings.
- L313 _public member_ `bool bGaveMismatchedLandscapeWarning = false;` — `UPROPERTY()`
- L315 _public member_ `bool bGaveMissingEditLayerGuidWarning = false;` — `UPROPERTY()`
- L319 _public member_ `bool bGaveNotInPatchManagerWarning = false;` — `UE_DEPRECATED(5.7, "Not needed since the deprecation of PatchManager")` — `UPROPERTY()`
- L322 _public member_ `bool bGaveMissingLandscapeWarning = false;` — `UE_DEPRECATED(5.7, "Not needed since the deprecation of PatchManager")` — `UPROPERTY()`

### `Plugins/Editor/LandscapePatch/Source/LandscapePatch/Public/LandscapePatchEditLayer.h` (Public)


#### class `ULandscapePatchEditLayer`  
`class ULandscapePatchEditLayer : public ULandscapeEditLayerProcedural`  
_L17-100_
- reflection: `UCLASS(MinimalAPI, meta = (ShortToolTip = "Special edit layer for landscape patches"))`
- inherits: `ULandscapeEditLayerProcedural`
- desc: Special edit layer used only for landscape patches. Patches point to the layer via a guid and determine their ordering by their Priority values.
- L28 _public prototype_ `virtual void RegisterPatchForEditLayer(ULandscapePatchComponent* Patch);` — Must be called by patches on this layer to let the layer know that the patch is pointing to it via its layer guid.
- L34 _public prototype_ `virtual void NotifyOfPatchRemoval(ULandscapePatchComponent* Patch);` — Should be called to notify the edit layer when a patch is destroyed or changes its edit layer guid away from this layer.
- L39 _public prototype_ `virtual void NotifyOfPriorityChange(ULandscapePatchComponent* Patch);` — Should be called to notify the edit layer when a patch priority changes.
- L44 _public prototype_ `virtual double GetHighestPatchPriority();` — Returns the highest known patch priority, or PATCH_PRIORITY_BASE if none are higher.
- L46 _public prototype_ `void RequestLandscapeUpdate(bool bInUserTriggered = false);`
- L49 _public member_ `inline static const double PATCH_PRIORITY_BASE = 1000;`
- L52 _public prototype_ `virtual bool SupportsTargetType(ELandscapeToolTargetType InType) const override;` — ULandscapeEditLayerBase
- L53 _public function_ `virtual bool NeedsPersistentTextures() const override`
- L54 _public function_ `virtual bool SupportsMultiple() const override`
- L55 _public function_ `virtual FString GetDefaultName() const override`
- L56 _public prototype_ `virtual void GetRenderDependencies(TSet<UObject*>& OutDependencies) const override;`
- L57 _public prototype_ `virtual void OnLayerRemoved() override;`
- L60 _public typedef_ `using FEditLayerRendererState = UE::Landscape::EditLayers::FEditLayerRendererState;`
- L63 _public prototype_ `virtual TArray<FEditLayerRendererState> GetEditLayerRendererStates(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) override;` — IEditLayerRendererProvider
- L66 _public prototype_ `virtual void PostEditUndo() override;` — UObject
- L75 _private member_ `TArray<TSoftObjectPtr<ULandscapePatchComponent>> RegisteredPatches;` — `UPROPERTY(Transient)` — This is the transient list of patches that are bound to this edit layer, usually sorted by priority. TSoftObjectPtr is used because it is robust across blueprint actor construction script reruns.
- L80 _private member_ `TMap<TSoftObjectPtr<ULandscapePatchComponent>, int32> PatchToIndex;` — `UPROPERTY(Transient)` — A helper structure for quick containment queries and updates. This should always be kept consistent with RegisteredPatches.
- L85 _private member_ `bool bPatchListDirty = false;` — When true, the entire patch list needs filtering and sorting. This is not meant to happen but it is used as a safety in case some lack of notifications puts us in a situation where our patches are not all valid and sorted.
- L89 _private prototype_ `void UpdatePatchList();`
- L90 _private prototype_ `void UpdatePatchListIfDirty();`
- L91 _private prototype_ `void UpdateHighestKnownPriority();`
- L93 _private prototype_ `bool ShouldPatchBeIncludedInList(const ULandscapePatchComponent* Patch) const;`
- L94 _private prototype_ `int32 GetInsertionIndex(ULandscapePatchComponent* Patch, bool& bFoundInvalidPatchOut) const;`
- L98 _private member_ `double HighestKnownPriority = PATCH_PRIORITY_BASE;` — A tracker of the highest priority we've seen. When the patch list is not dirty, it will be the priority of the last element, but this variable allows us to maintain the value past dirtying.

### `Plugins/Editor/LandscapePatch/Source/LandscapePatch/Public/LandscapePatchLogging.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLandscapePatch, Log, All);`

### `Plugins/Editor/LandscapePatch/Source/LandscapePatch/Public/LandscapePatchManager.h` (Public)


#### class `ADEPRECATED_LandscapePatchManager`  
`class ADEPRECATED_LandscapePatchManager : public ALandscapeBlueprintBrushBase`  
_L22-178_
- reflection: `UCLASS(Deprecated, meta = (DeprecationMessage = "Landscape patches are now fully handled by ULandscapePatchEditLayer and migration is automatic so effectively, this actor is only there for backwards-compatibility/serialization purposes"))`
- inherits: `ALandscapeBlueprintBrushBase`
- desc: Actor used in legacy landscape patch handling where a manager keeps a serialized list of patches that determines their priority. This approach is deprecated- patches now point to a special landscape patch edit layer via a guid, and determine their ordering relative to each other using a priority value.
- L27 _public prototype_ `ADEPRECATED_LandscapePatchManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L32 _public function_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRendererState> GetEditLayerRendererStates(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) override` — IEditLayerRendererProvider Deprecated
- L39 _public function_ `virtual void GetRendererStateInfo(const UE::Landscape::EditLayers::FMergeContext* InMergeContext, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutSupportedTargetTypeState, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutEnabledTargetTypeState, TArray<UE::Landscape::EditLayers::FTargetLayerGroup>& OutTargetLayerGroups) const override` — ILandscapeEditLayerRenderer Deprecated
- L46 _public function_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRenderItem> GetRenderItems(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override` — Deprecated
- L52 _public function_ `virtual bool RenderLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder) override` — Deprecated
- L58 _public function_ `virtual bool SupportsBlueprintBrushTool() const` — In 5.6 users should not be able to add new Patch Managers anywhere in the editor
- L65 _public prototype_ `virtual void SetTargetLandscape(ALandscape* InOwningLandscape);` — `UE_DEPRECATED(5.7, "Patch manager is deprecated and replaced by Landscape Patch Edit Layer.")` — `UFUNCTION(BlueprintCallable, Category = LandscapeManager, meta = (DeprecatedFunction, DeprecationMessage = "Patch manager is deprecated and replaced by Landscape Patch Edit Layer."))` — Adds the brush to the given landscape, removing it from any previous one. This differs from SetOwningLandscape in that SetOwningLandscape is called by the landscape itself from AddBrushToLayer to update the manager.
- L69 _public function_ `virtual FTransform GetHeightmapCoordsToWorld()` — `UE_DEPRECATED(5.7, "LandscapePatchManager is deprecated and replaced by Landscape Patch Edit Layer.")` — Deprecated
- L76 _public function_ `bool ContainsPatch(ULandscapePatchComponent* Patch) const` — `UE_DEPRECATED(5.7, "Patch manager is deprecated and replaced by Landscape Patch Edit Layer.")` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch, meta = (DeprecatedFunction, DeprecationMessage = "Patch manager is deprecated and replaced by Landscape Patch Edit Layer."))`
- L83 _public function_ `void AddPatch(ULandscapePatchComponent* Patch)` — `UE_DEPRECATED(5.7, "Patch manager is deprecated and replaces by Landscape Patch Edit Layer.")` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch, meta = (DeprecatedFunction, DeprecationMessage = "Patch manager is deprecated and replaced by Landscape Patch Edit Layer."))`
- L88 _public function_ `bool RemovePatch(ULandscapePatchComponent* Patch)` — `UE_DEPRECATED(5.7, "Patch manager is deprecated and replaces by Landscape Patch Edit Layer.")` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch, meta = (DeprecatedFunction, DeprecationMessage = "Patch manager is deprecated and replaced by Landscape Patch Edit Layer."))`
- L95 _public function_ `int32 GetIndexOfPatch(const ULandscapePatchComponent* Patch) const` — `UE_DEPRECATED(5.7, "Patch manager is deprecated and replaces by Landscape Patch Edit Layer.")` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch, meta = (DeprecatedFunction, DeprecationMessage = "Patch manager is deprecated and replaced by Landscape Patch Edit Layer."))`
- L102 _public function_ `void MovePatchToIndex(ULandscapePatchComponent* Patch, int32 Index)` — `UE_DEPRECATED(5.7, "Patch manager is deprecated and replaces by Landscape Patch Edit Layer.")` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch, meta = (DeprecatedFunction, DeprecationMessage = "Patch manager use is deprecated and replaces by Landscape Patch Edit Layer."))`
- L113 _public prototype_ `void MigrateToPrioritySystemAndDelete();` — `UFUNCTION(CallInEditor, Category = LandscapeManager, meta = (DisplayName = "MigrateToPrioritySystem"))` — Move any patches from legacy patch list to being bound directly to an edit layer, and delete the patch manager. This will cause a popup to the user if there is still a dangling reference to the manager (there shouldn't be).
- L116 _public function_ `virtual bool CanAffectWeightmapLayer(const FName& InLayerName) const override` — ALandscapeBlueprintBrushBase
- L121 _public function_ `virtual bool AffectsHeightmap() const override`
- L126 _public function_ `virtual bool AffectsWeightmap() const override`
- L131 _public function_ `virtual bool AffectsWeightmapLayer(const FName& InLayerName) const override`
- L136 _public function_ `virtual bool AffectsVisibilityLayer() const override`
- L141 _public function_ `virtual void GetRenderDependencies(TSet<UObject*>& OutDependencies) override`
- L145 _public prototype_ `virtual void PostRegisterAllComponents() override;` — AActor
- L148 _public function_ `virtual bool IsEditorOnly() const override`
- L153 _public function_ `virtual bool NeedsLoadForClient() const override`
- L158 _public function_ `virtual bool NeedsLoadForServer() const override`
- L165 _public member_ `inline static const double LEGACY_PATCH_PRIORITY_BASE = ULandscapePatchEditLayer::PATCH_PRIORITY_BASE - 10;` — This is intentionally lower than PATCH_PRIORITY_BASE so that patches converted from a patch manager list are applied before other edit layer patches.
- L169 _private prototype_ `void MigrateToPrioritySystemAndDeleteInternal(bool bAllowUI);`
- L172 _private member_ `TArray<TSoftObjectPtr<ULandscapePatchComponent>> PatchComponents;` — `UPROPERTY()`
- L176 _private member_ `bool bDead = false;` — This patch manager has been migrated out of and should no longer be accessible.

### `Plugins/Editor/LandscapePatch/Source/LandscapePatch/Public/LandscapePatchModule.h` (Public)


#### class `FLandscapePatchModule`  
`class FLandscapePatchModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Editor/LandscapePatch/Source/LandscapePatch/Public/LandscapePatchUtil.h` (Public)


#### struct `FLandscapeHeightPatchConvertToNativeParams`  
`struct FLandscapeHeightPatchConvertToNativeParams`  
_L17-29_
- reflection: `USTRUCT()`
- desc: Values needed to convert a patch stored in some source encoding into the native (two byte int) encoding and back
- L22 _public member_ `float ZeroInEncoding = 0.0f;` — `UPROPERTY()`
- L25 _public member_ `float HeightScale = 1.0f;` — `UPROPERTY()`
- L28 _public member_ `float HeightOffset = 0.0f;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace Landscape` (scope `UE`)
- L34 _namespace_ `namespace PatchUtil` (scope `UE::Landscape`)
- L36 _prototype_ `void CopyTextureOnRenderThread(FRHICommandListImmediate& RHICmdList, const FTextureResource& Source, FTextureResource& Destination);` (scope `UE::Landscape::PatchUtil`)
- L42 _prototype_ `FTransform GetHeightmapToWorld(const FTransform& InLandscapeTransform);` (scope `UE::Landscape::PatchUtil`) — Given a landscape transform, gives a transform from heightmap coordinates (where the Z value is the two byte integer value stored as the height) to world coordinates.

### `Plugins/Editor/LandscapePatch/Source/LandscapePatch/Public/LandscapeTextureBackedRenderTarget.h` (Public)


#### class `ULandscapeTextureBackedRenderTargetBase`  
`class ULandscapeTextureBackedRenderTargetBase : public UObject`  
_L22-91_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: A combination of a render target and UTexture2D that allows render target to be saved across save/load/etc by copying the data back and forth from the internal texture. After an Initialize() call, the internal texture will always be present, and the render target will be present depending on how SetUseInternalTextureOnly is called (by default, present).
- L28 _public function_ `virtual UTextureRenderTarget2D* GetRenderTarget()`
- L29 _public function_ `virtual UTexture2D* GetInternalTexture()`
- L34 _public prototype_ `virtual void SetUseInternalTextureOnly(bool bUseInternalTextureOnlyIn, bool bCopyExisting = true);`
- L36 _public prototype_ `virtual void SetResolution(int32 SizeXIn, int32 SizeYIn);`
- L38 _public prototype_ `virtual void Initialize();`
- L40 _public prototype_ `virtual void CopyToInternalTexture() PURE_VIRTUAL(ULandscapeTextureBackedRenderTargetBase::CopyToInternalTexture);`
- L41 _public prototype_ `virtual void CopyBackFromInternalTexture() PURE_VIRTUAL(ULandscapeTextureBackedRenderTargetBase::CopyBackFromInternalTexture);`
- L45 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;` — UObject
- L46 _public prototype_ `virtual void PostLoad() override;`
- L47 _public prototype_ `virtual void PreDuplicate(FObjectDuplicationParameters& DupParams) override;`
- L48 _public prototype_ `virtual void ExportCustomProperties(FOutputDevice& Out, uint32 Indent) override;`
- L49 _public prototype_ `virtual void PostEditImport() override;`
- L50 _public prototype_ `virtual void PostEditUndo() override;`
- L54 _public prototype_ `UE_INTERNAL void SetTemporarilyNonTransactional(bool bInIsTemporarilyNonTransactional);` — This is a very bespoke function to work around UE-225445, see comment in cpp file
- L59 _protected prototype_ `virtual bool IsCopyingBackAndForthAllowed();` — Allows us to disable copying back and forth between render target and texture when this is not possible (for instance, when rendering is turned off, so render target resources are not allocated).
- L61 _protected prototype_ `virtual ETextureSourceFormat GetInternalTextureFormat() PURE_VIRTUAL(ULandscapeTextureBackedRenderTargetBase::GetInternalTextureFormat, return ETextureSourceFormat::TSF_G8;);`
- L62 _protected prototype_ `virtual ETextureRenderTargetFormat GetRenderTargetFormat() PURE_VIRTUAL(ULandscapeTextureBackedRenderTargetBase::GetRenderTargetFormat, return ETextureRenderTargetFormat::RTF_R8;);`
- L64 _protected prototype_ `void ReinitializeRenderTarget(bool bClear);`
- L67 _protected prototype_ `UTexture2D* CreateInternalTexture();`
- L72 _public member_ `TObjectPtr<UTexture2D> InternalTexture = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = DebugData)`
- L75 _public member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = DebugData, Transient, DuplicateTransient)`
- L78 _public member_ `int32 SizeX = 32;` — `UPROPERTY(VisibleAnywhere, Category = DebugData)`
- L81 _public member_ `int32 SizeY = 32;` — `UPROPERTY(VisibleAnywhere, Category = DebugData)`
- L84 _public member_ `bool bUseInternalTextureOnly = false;` — `UPROPERTY()`
- L90 _protected member_ `bool bIsTemporarilyNonTransactional = false;` — Allows to indicate that the object has temporarily lost its RF_Transactional flag and should not add it back, neither to itself or to any of its sub-objects at this time (see SetTemporarilyNonTransactional)

#### class `ULandscapeWeightTextureBackedRenderTarget`  
`class ULandscapeWeightTextureBackedRenderTarget : public ULandscapeTextureBackedRenderTargetBase`  
_L94-111_
- reflection: `UCLASS()`
- inherits: `ULandscapeTextureBackedRenderTargetBase`
- L100 _public prototype_ `virtual void SetUseAlphaChannel(bool bUseAlphaChannelIn);`
- L102 _public prototype_ `virtual void Initialize() override;`
- L103 _public prototype_ `virtual void CopyToInternalTexture() override;`
- L104 _public prototype_ `virtual void CopyBackFromInternalTexture() override;`
- L106 _protected prototype_ `virtual ETextureSourceFormat GetInternalTextureFormat() override;`
- L107 _protected prototype_ `virtual ETextureRenderTargetFormat GetRenderTargetFormat() override;`
- L110 _protected member_ `bool bUseAlphaChannel = true;` — `UPROPERTY()`

#### class `ULandscapeHeightTextureBackedRenderTarget`  
`class ULandscapeHeightTextureBackedRenderTarget : public ULandscapeTextureBackedRenderTargetBase`  
_L114-135_
- reflection: `UCLASS()`
- inherits: `ULandscapeTextureBackedRenderTargetBase`
- L120 _public prototype_ `virtual void SetFormat(ETextureRenderTargetFormat FormatToUse);`
- L122 _public prototype_ `virtual void Initialize() override;`
- L123 _public prototype_ `virtual void CopyToInternalTexture() override;`
- L124 _public prototype_ `virtual void CopyBackFromInternalTexture() override;`
- L127 _public member_ `FLandscapeHeightPatchConvertToNativeParams ConversionParams;` — `UPROPERTY()`
- L130 _protected function_ `virtual ETextureSourceFormat GetInternalTextureFormat() override`
- L131 _protected function_ `virtual ETextureRenderTargetFormat GetRenderTargetFormat() override`
- L134 _protected member_ `TEnumAsByte<ETextureRenderTargetFormat> RenderTargetFormat = ETextureRenderTargetFormat::RTF_R32f;` — `UPROPERTY()`

### `Plugins/Editor/LandscapePatch/Source/LandscapePatch/Public/LandscapeTexturePatch.h` (Public)


#### enum `ELandscapeTexturePatchSourceMode`  
`enum class ELandscapeTexturePatchSourceMode : uint8`  
_L30-55_
- reflection: `UENUM(BlueprintType)`
- desc: Determines where the patch gets its information, which affects its memory usage in editor (not in runtime, since patches are baked directly into landscape and removed for runtime).
- L36 _public enumerator_ `None` — The patch is considered not to have any data stored for this element. Setting source mode to this is a way to discard any internally stored data.
- L42 _public enumerator_ `InternalTexture` — The data will be read from an internally-stored UTexture2D. In this mode, the patch can't be written-to via blueprints, but it avoids storing the extra render target needed for TextureBackedRenderTarget.
- L48 _public enumerator_ `TextureBackedRenderTarget` — The patch data will be read from an internally-stored render target, which can be written to via Blueprints and which gets serialized to an internally stored UTexture2D when needed. Uses double the memory of InternalTexture.
- L54 _public enumerator_ `TextureAsset` — The data will be read from a UTexture asset (which can be a render target). Allows multiple patches to share the same texture.

#### enum `ELandscapeTexturePatchAlphaSourceMode`  
`enum class ELandscapeTexturePatchAlphaSourceMode : uint8`  
_L61-91_
- reflection: `UENUM(BlueprintType)`
- desc: Determines the alpha mask applied to a patch texture. Alpha is applied in addition to the patch falloff settings
- L66 _public enumerator_ `None` — The patch texture is not masked by any alpha value
- L72 _public enumerator_ `InternalTexture` — The alpha data will be read from an internally-stored UTexture2D. In this mode, the patch can't be written-to via blueprints, but it avoids storing the extra render target needed for TextureBackedRenderTarget.
- L78 _public enumerator_ `TextureBackedRenderTarget` — The patch alpha data will be read from an internally-stored render target, which can be written to via Blueprints and which gets serialized to an internally stored UTexture2D when needed. Uses double the memory of InternalTexture.
- L84 _public enumerator_ `TextureAsset` — The alpha data will be read from a UTexture asset (which can be a render target). Allows multiple patches to share the same alpha texture.
- L90 _public enumerator_ `SourceTextureChannel` — A color channel of the original source texture will be used as the alpha mask. By default, the alpha channel of the texture is used. The source texture must have data in the defined channel to affect the patch

#### enum `ELandscapeTexturePatchTextureChannel`  
`enum class ELandscapeTexturePatchTextureChannel : uint8`  
_L97-110_
- reflection: `UENUM(BlueprintType)`
- desc: Color channel of the source texture
- L99 _public enumerator_ `None UMETA(Hidden)`
- L101 _public enumerator_ `Red` — Texture's red channel
- L103 _public enumerator_ `Green` — Texture's green channel
- L105 _public enumerator_ `Blue` — Texture's blue channel
- L107 _public enumerator_ `Alpha` — Texture's alpha channel
- L109 _public enumerator_ `Luminance` — Texture's luminance

#### enum `ELandscapeTexturePatchBlendMode`  
`enum class ELandscapeTexturePatchBlendMode : uint8`  
_L114-132_
- reflection: `UENUM(BlueprintType)`
- desc: Determines how the patch is combined with the previous state of the landscape.
- L120 _public enumerator_ `AlphaBlend` — Let the patch specify the actual target height, and blend that with the existing height using falloff/alpha. E.g. with no falloff and alpha 1, the landscape will be set directly to the height sampled from patch. With alpha 0.5, landscape height will be averaged evenly with patch height.
- L125 _public enumerator_ `Additive` — Interpreting the landscape mid value as 0, use the texture patch as an offset to apply to the landscape. Falloff/alpha will just affect the degree to which the offset is applied (e.g. alpha of 0.5 will apply just half the offset).
- L128 _public enumerator_ `Min` — Like Alpha Blend mode, but limited to only lowering the existing landscape values
- L131 _public enumerator_ `Max` — Like Alpha Blend mode, but limited to only raising the existing landscape values

#### enum `ELandscapeTexturePatchFalloffMode`  
`enum class ELandscapeTexturePatchFalloffMode : uint8`  
_L136-145_
- reflection: `UENUM(BlueprintType)`
- desc: Determines falloff method for the patch's influence.
- L140 _public enumerator_ `Circle` — Affect landscape in a circle inscribed in the patch, and fall off across a margin extending into that circle.
- L144 _public enumerator_ `RoundedRectangle` — Affect entire rectangle of patch (except for circular corners), and fall off across a margin extending inward from the boundary.

#### enum `ELandscapeTextureHeightPatchEncoding`  
`enum class ELandscapeTextureHeightPatchEncoding : uint8`  
_L148-165_
- reflection: `UENUM(BlueprintType)`
- L153 _public enumerator_ `ZeroToOne` — Values in texture should be interpreted as being floats in the range [0,1]. User specifies what value corresponds to height 0 (i.e. height when landscape is "cleared"), and the size of the range in world units.
- L156 _public enumerator_ `WorldUnits` — Values in texture are direct world-space heights.
- L160 _public enumerator_ `NativePackedHeight` — Values in texture are stored the same way they are in landscape actors: as 16 bit integers packed into two bytes, mapping to [-256, 256 - 1/128] before applying landscape scale.

#### enum `ELandscapeTextureHeightPatchZeroHeightMeaning`  
`enum class ELandscapeTextureHeightPatchZeroHeightMeaning : uint8`  
_L168-183_
- reflection: `UENUM(BlueprintType)`
- L172 _public enumerator_ `PatchZ` — Zero height corresponds to the patch vertical position relative to the landscape. This moves the results up and down as the patch moves up and down.
- L177 _public enumerator_ `LandscapeZ` — Zero height corresponds to Z = 0 in the local space of the landscape, regardless of the patch vertical position. For instance, if landscape transform has z=-100 in world, then writing height 0 will correspond to z=-100 in world coordinates, regardless of patch Z.
- L182 _public enumerator_ `WorldZero` — Zero height corresponds to the height of the world origin relative to landscape. In other words, writing height 0 will correspond to world z = 0 regardless of patch Z or landscape transform (as long as landscape transform still has Z up in world coordinates).

#### struct `FLandscapeTexturePatchTextureTransform`  
`struct FLandscapeTexturePatchTextureTransform`  
_L186-224_
- reflection: `USTRUCT(BlueprintType)`
- L192 _public member_ `bool bUseWorldSpaceScale = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture Transform", meta = (DisplayName = "Use World Unit Tiling"))` — When enabled, texture UVs are scaled using world-space units (1000 = tile texture every 10 meters). If disabled, scaling is applied in local UV space.
- L198 _public member_ `bool bUseWorldPositionSampling = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture Transform")` — By default, texture UVs are centered at the patch's min bounds. Moving the patch does not change texture sampling. When enabled, UVs are anchored in world space at the world origin. Moving the patch's world position changes where the texture is sampled.
- L204 _public member_ `FVector2D Scale = FVector2D(1, 1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture Transform")` — Scale applied to the texture's UV. By default, scaling is applied in local UV space. Relative scale 2.0 = texture is twice as large as original size. When World Space Scale is enabled, scale 1000 = tile texture every 10 meters.
- L208 _public member_ `float Rotation = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture Transform", meta = (UIMin = "0", UIMax = "360", ClampMin = "0", ClampMax = "360"))` — Rotation in degrees applied to the texture's UV.
- L212 _public member_ `FVector2D Offset = FVector2D(0, 0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture Transform")` — Offset applied to the sampled texture. By default, offset is in UV space [0, 1]. When bUseWorldPositionSampling is enabled, offset is in world units.
- L214 _public prototype_ `FMatrix44d GetTransformAsMatrix(const FTransform& PatchToWorldIn, const FVector2f& PatchWorldDimensionsIn) const;`
- L216 _public function_ `FORCEINLINE bool operator==(const FLandscapeTexturePatchTextureTransform InTransform) const`

#### struct `FLandscapeTexturePatchAlphaSettings`  
`struct FLandscapeTexturePatchAlphaSettings`  
_L227-276_
- reflection: `USTRUCT(BlueprintType)`
- L232 _public prototype_ `UTextureRenderTarget2D* GetAlphaRenderTarget(UObject* InOuter, bool bAlwaysMarkDirty = true);` — When alpha source mode is TextureBackedRenderTarget returns the alpha render target. Will allocate new render target if not yet initialized
- L234 _public prototype_ `UTexture2D* GetAlphaInternalTexture(UObject* InOuter, bool bAlwaysMarkDirty = true);` — When alpha source mode is  InternalTexture/TextureBackedRenderTarget returns the alpha internal texture. Will allocate new internal data if not yet initialized
- L241 _public prototype_ `void SetAlphaSourceMode(ELandscapeTexturePatchAlphaSourceMode InNewSourceMode, UObject* InOuter, bool bAlwaysMarkDirty = true);` — Transitions from the previous alpha source mode to the new mode. Marks the Outer owner dirty and clears internal data if needed @param InNewSourceMode the new alpha source mode @param InOuter The alpha settings owner (must be direct texture patch or weight patch info) @param bAlwaysMarkDirty When true, marks the outer package dirty when the source mode changes
- L242 _public function_ `ELandscapeTexturePatchAlphaSourceMode GetAlphaSourceMode() const`
- L249 _public member_ `ELandscapeTexturePatchAlphaSourceMode DetailPanelAlphaSourceMode = ELandscapeTexturePatchAlphaSourceMode::None;` — `UPROPERTY(EditAnywhere, Category = "Texture Alpha Settings", meta = (DisplayName = "Source Mode"))` — How the alpha texture is stored.
- L255 _public member_ `TObjectPtr<UTexture> AlphaTextureAsset;` — `UPROPERTY(EditAnywhere, Category = "Texture Alpha Settings", meta = (EditConditionHides, EditCondition = "AlphaSourceMode == ELandscapeTexturePatchAlphaSourceMode::TextureAsset", DisallowedAssetDataTags = "VirtualTextureStreaming=True"))` — Alpha Texture to use when the source mode is set to texture asset.
- L259 _public member_ `ELandscapeTexturePatchTextureChannel AlphaTextureChannel = ELandscapeTexturePatchTextureChannel::Alpha;` — `UPROPERTY(EditAnywhere, Category = "Texture Alpha Settings", meta = (EditConditionHides, EditCondition = "AlphaSourceMode != ELandscapeTexturePatchAlphaSourceMode::None"))` — Texture channel utilized for the alpha mask. The texture alpha channel is used by default.
- L263 _public member_ `TObjectPtr<ULandscapeWeightTextureBackedRenderTarget> InternalAlphaData;` — `UPROPERTY(VisibleAnywhere, Category = "Texture Alpha Settings", Instanced, AdvancedDisplay, meta = (DisplayName = "Debug Data", EditConditionHides, EditCondition = "AlphaSourceMode != ELandscapeTexturePatchAlphaSourceMode::None"))` — Not directly settable via detail panel- for alpha display/debugging purposes only.
- L267 _public member_ `FLandscapeTexturePatchTextureTransform AlphaTextureUVTransform;` — `UPROPERTY(EditAnywhere, Category = "Texture Alpha Settings", meta = (DisplayName = "Alpha Texture Transform"), meta = (EditConditionHides, EditCondition = "AlphaSourceMode != ELandscapeTexturePatchAlphaSourceMode::None"))` — Alpha texture's UV transform (Scale, Offset, Rotation)
- L275 _private member_ `ELandscapeTexturePatchAlphaSourceMode AlphaSourceMode = ELandscapeTexturePatchAlphaSourceMode::None;` — `UPROPERTY(VisibleAnywhere, Category = "Texture Alpha Settings", meta = (EditConditionHides, EditCondition = "false"))` — When the source mode changes, there are transition steps that need run to clean up render targets / internal data. In PostEditChangeProperty, the previous source mode is already lost and it becomes harder to track the necessary transition. DetailPanelAlphaSourceMode exposes the property and allows us to process the source mode transition before updating AlphaSourceMode

#### struct `FLandscapeTexturePatchEncodingSettings`  
`struct FLandscapeTexturePatchEncodingSettings`  
_L280-299_
- reflection: `USTRUCT(BlueprintType)`
- L289 _public member_ `double ZeroInEncoding = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — The value in the patch data that corresponds to 0 height relative to the starting point specified by Zero Height Meaning.
- L298 _public member_ `double WorldSpaceEncodingScale = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — The scale that should be applied to the data stored in the patch relative to the zero in the encoding, in world coordinates. For instance if the encoding is [0,1], and 0.5 corresponds to 0, a WorldSpaceEncoding Scale of 100 means that the resulting values will lie in the range [-50, 50] in world space, which would be [-0.5, 0.5] in the landscape local heights if the Z scale is 100.

#### class `ULandscapeWeightPatchTextureInfo`  
`class ULandscapeWeightPatchTextureInfo : public UObject`  
_L307-387_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, CollapseCategories)`
- inherits: `UObject`
- desc: Helper class for ULandscapeTexturePatch that stores information for a given weight layer. Should not be used outside this class.
- L314 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject
- L315 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L316 _public prototype_ `virtual void PreDuplicate(FObjectDuplicationParameters& DupParams) override;`
- L322 _protected member_ `FName WeightmapLayerName;` — `UPROPERTY(EditAnywhere, Category = WeightPatch, meta = (DisplayName = "Target Layer Name"))` — Name of the target layer to affect.
- L326 _protected member_ `bool bEditVisibilityLayer = false;` — `UPROPERTY(EditAnywhere, Category = WeightPatch, meta = (DisplayName = "Affects Visibility Layer"))` — Specifies if this patch affects the visibility layer.
- L329 _protected member_ `ELandscapeTexturePatchSourceMode SourceMode = ELandscapeTexturePatchSourceMode::None;` — `UPROPERTY(EditAnywhere, Category = WeightPatch, meta = (EditConditionHides, EditCondition = "false"))`
- L333 _protected member_ `ELandscapeTexturePatchSourceMode DetailPanelSourceMode = ELandscapeTexturePatchSourceMode::None;` — `UPROPERTY(EditAnywhere, Category = WeightPatch, meta = (DisplayName = "Source Mode"))` — How the weightmap of the patch is stored.
- L339 _protected member_ `TObjectPtr<UTexture> TextureAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = WeightPatch, meta = (EditConditionHides, EditCondition = "SourceMode == ELandscapeTexturePatchSourceMode::TextureAsset", DisallowedAssetDataTags = "VirtualTextureStreaming=True"))` — Texture to use when source mode is set to texture asset.
- L342 _protected member_ `FLandscapeTexturePatchTextureTransform WeightTextureUVTransform;` — `UPROPERTY(EditAnywhere, Category = WeightPatch, meta = (DisplayName = "Texture Transform"), meta = (EditConditionHides, EditCondition = "SourceMode != ELandscapeTexturePatchSourceMode::None"))`
- L346 _protected member_ `ELandscapeTexturePatchTextureChannel WeightPatchTextureChannel = ELandscapeTexturePatchTextureChannel::Red;` — `UPROPERTY(EditAnywhere, Category = HeightPatch, meta = (EditConditionHides, EditCondition = "SourceMode != ELandscapeTexturePatchSourceMode::None"))` — Color channel of the texture used for weight data. By default the weight texture's red channel is used.
- L350 _protected member_ `TObjectPtr<ULandscapeWeightTextureBackedRenderTarget> InternalData = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = WeightPatch, Instanced, AdvancedDisplay, meta = (DisplayName = "Debug Data"))` — Not directly settable via detail panel- for display/debugging purposes only.
- L354 _protected member_ `bool bUseAlphaChannel_DEPRECATED = false;` — `UE_DEPRECATED(5.8, "bUseAlphaChannel is deprecated, use the WeightPatchAlphaSettings.SetAlphaSourceMode() with ELandscapeTexturePatchAlphaSourceMode (use alpha mode None or SourceTextureChannel for legacy behavior).")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use WeightPatchAlphaSettings.SetAlphaSourceMode() with ELandscapeTexturePatchAlphaSourceMode (use alpha mode None or SourceTextureChannel for legacy behavior)."))`
- L357 _protected member_ `bool bOverrideWeightAlphaSettings = false;` — `UPROPERTY(EditAnywhere, Category = WeightPatch, meta = (InlineEditConditionToggle))`
- L360 _protected member_ `FLandscapeTexturePatchAlphaSettings WeightPatchAlphaSettings;` — `UPROPERTY(EditAnywhere, Category = WeightPatch, meta = (DisplayName = "Override Alpha Settings", EditCondition = "bOverrideWeightAlphaSettings"))`
- L364 _protected member_ `bool bOverrideBlendMode = false;` — `UPROPERTY(EditAnywhere, Category = WeightPatch, meta = (InlineEditConditionToggle))` — Allows to override the patch component's weightmap blend node
- L368 _protected member_ `ELandscapeTexturePatchBlendMode OverrideBlendMode = ELandscapeTexturePatchBlendMode::AlphaBlend;` — `UPROPERTY(EditAnywhere, Category = WeightPatch, meta = (EditCondition = "bOverrideBlendMode"))` — Determines how the patch is combined with the previous state of the landscape (overrides the patch component's own blend node).
- L373 _protected member_ `bool bReinitializeOnNextRender = false;`
- L375 _protected prototype_ `void SetSourceMode(ELandscapeTexturePatchSourceMode NewMode);`
- L376 _protected prototype_ `void SetWeightPatchAlphaSourceMode(ELandscapeTexturePatchAlphaSourceMode InSourceMode, bool bInOverrideAlpha, bool bAlwaysMarkDirty = true);`
- L377 _protected prototype_ `void SetWeightPatchTextureChannel(ELandscapeTexturePatchTextureChannel InTextureChannel, bool bAlwaysMarkDirty = true);`
- L378 _protected prototype_ `void SetWeightPatchAlphaTextureChannel(ELandscapeTexturePatchTextureChannel InTextureChannel, bool bAlwaysMarkDirty = true);`
- L379 _protected prototype_ `void SetWeightPatchTextureTransform(const FLandscapeTexturePatchTextureTransform& InTextureTransform, bool bAlwaysMarkDirty = true);`
- L380 _protected prototype_ `void SetWeightPatchAlphaTextureTransform(const FLandscapeTexturePatchTextureTransform& InTextureTransform, bool bAlwaysMarkDirty = true);`
- L383 _protected prototype_ `void TransitionSourceModeInternal(ELandscapeTexturePatchSourceMode OldMode, ELandscapeTexturePatchSourceMode NewMode);`

#### class `ULandscapeTexturePatch`  
`class ULandscapeTexturePatch : public ULandscapePatchComponent`  
_L391-1072_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, ClassGroup = Landscape, meta = (BlueprintSpawnableComponent))`
- inherits: `ULandscapePatchComponent`
- L399 _public prototype_ `virtual void GetRendererStateInfo(const UE::Landscape::EditLayers::FMergeContext* InMergeContext, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutSupportedTargetTypeState, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutEnabledTargetTypeState, TArray<UE::Landscape::EditLayers::FTargetLayerGroup>& OutTargetLayerGroups) const override;` — ILandscapeEditLayerRenderer, via ULandscapePatchComponent
- L403 _public prototype_ `virtual FString GetEditLayerRendererDebugName() const override;`
- L404 _public prototype_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRenderItem> GetRenderItems(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override;`
- L405 _public prototype_ `virtual UE::Landscape::EditLayers::ERenderFlags GetRenderFlags(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override;`
- L406 _public prototype_ `virtual bool CanGroupRenderLayerWith(TScriptInterface<ILandscapeEditLayerRenderer> InOtherRenderer) const override;`
- L407 _public prototype_ `virtual bool RenderLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder) override;`
- L408 _public prototype_ `virtual void BlendLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder) override;`
- L411 _public prototype_ `virtual bool CanAffectHeightmap() const override;` — ULandscapePatchComponent
- L412 _public prototype_ `virtual bool CanAffectWeightmap() const override;`
- L413 _public prototype_ `virtual bool CanAffectWeightmapLayer(const FName& InLayerName) const override;`
- L414 _public prototype_ `virtual bool CanAffectVisibilityLayer() const override;`
- L415 _public prototype_ `virtual void GetRenderDependencies(TSet<UObject*>& OutDependencies) const override;`
- L418 _public prototype_ `virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;` — UActorComponent
- L419 _public prototype_ `virtual void CheckForErrors() override;`
- L422 _public prototype_ `virtual void PostLoad() override;` — UObject
- L423 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L425 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L433 _public prototype_ `virtual FTransform GetPatchToWorldTransform() const;` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Gets the transform from patch to world. The transform is based off of the component transform, but with rotation changed to align to the landscape, only using the yaw to rotate it relative to the landscape.
- L442 _public function_ `virtual FVector2D GetUnscaledCoverage() const` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Gives size in unscaled world coordinates (ie before applying patch transform) of the patch as measured between the centers of the outermost pixels. This is the range across which bilinear interpolation always has correct values, so the area outside this center portion in the texture does not affect the landscape.
- L448 _public function_ `virtual void SetUnscaledCoverage(FVector2D Coverage)` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Set the patch coverage (see GetUnscaledCoverage for description).
- L457 _public prototype_ `virtual FVector2D GetFullUnscaledWorldSize() const;` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — When using an internal texture, gives size in unscaled world coordinates of the patch in the world, based off of UnscaledCoverage and texture resolution (i.e., adds a half-pixel around UnscaledCoverage). Does not reflect the resolution of any used texture assets (if the source mode is texture asset for the height/weight patches).
- L464 _public function_ `virtual FVector2D GetResolution() const` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Gets the size (in pixels) of the internal textures used by the patch. Does not reflect the resolution of any used texture assets (if the source mode is texture asset).
- L473 _public prototype_ `virtual void SetResolution(FVector2D ResolutionIn);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the resolution of the currently used internal texture or render target. Has no effect if the source mode is set to an external texture asset. @return true if successful.
- L483 _public prototype_ `virtual UPARAM(DisplayName = "Success") bool GetInitResolutionFromLandscape(float ResolutionMultiplier, FVector2D& ResolutionOut)` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch, meta = (ResolutionMultiplier = "1.0"))` — Given the landscape resolution, current patch coverage, and a landscape resolution multiplier, gives the needed resolution of the landscape patch. I.e., figures out the number of pixels in the landcape that would be in a region of such size, and then uses the resolution multiplier to give a result. @return true if successful (may fail if landscape is not set, for instance)
- L486 _public function_ `float GetFalloff() const` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L489 _public function_ `void SetFalloff(float FalloffIn)` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L499 _public function_ `ELandscapeTexturePatchFalloffMode GetFalloffMode() const` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L502 _public function_ `void SetFalloffMode(ELandscapeTexturePatchFalloffMode FalloffModeIn)` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L512 _public function_ `ELandscapeTexturePatchBlendMode GetBlendMode() const` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L518 _public function_ `void SetBlendMode(ELandscapeTexturePatchBlendMode BlendModeIn)` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Determines how the height patch is blended into the existing terrain.
- L530 _public function_ `virtual ELandscapeTexturePatchSourceMode GetHeightSourceMode() const` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L538 _public prototype_ `virtual void SetHeightSourceMode(ELandscapeTexturePatchSourceMode NewMode);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Changes source mode. There are currently no API guarantees regarding the initialization of the new source data. E.g. when first switching to use an internal render target, the data in that render target may not be initialized.
- L541 _public function_ `virtual const FLandscapeTexturePatchTextureTransform& GetHeightTextureTransform() const` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L549 _public prototype_ `virtual void SetHeightTextureTransform(const FLandscapeTexturePatchTextureTransform& InTextureTransform, bool bAlwaysMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the height texture's UV transform. Transform is applied relative UVSpace unless struct property bInWorldSpaceScale is true @param InTextureTransform the height texture's transform @param bAlwaysMarkDirty mark the package dirty when transform changes
- L557 _public prototype_ `virtual void SetHeightTextureChannel(ELandscapeTexturePatchTextureChannel InTextureChannel, bool bAlwaysMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the height texture's color channel. Texture channel is restricted when HeightSource is InternalData or HeightEncoding is NativePackedHeight (Assumes RG channels) @param InTextureChannel the color channel of the texture to use @param bAlwaysMarkDirty mark the package dirty when channel property changes
- L560 _public function_ `virtual ELandscapeTexturePatchTextureChannel GetHeightTextureChannel() const` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L563 _public function_ `virtual ELandscapeTexturePatchAlphaSourceMode GetHeightAlphaSourceMode() const` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L571 _public prototype_ `virtual void SetHeightAlphaSourceMode(ELandscapeTexturePatchAlphaSourceMode InNewMode, bool bAlwaysMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Changes the source mode of the height patch alpha data. There are currently no API guarantees regarding the initialization of the new alpha source data. E.g. when first switching to use an internal render target, the data in that render target may not be initialized.
- L574 _public function_ `virtual const FLandscapeTexturePatchTextureTransform& GetHeightAlphaTextureTransform() const` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L582 _public prototype_ `virtual void SetHeightAlphaTextureTransform(const FLandscapeTexturePatchTextureTransform& InTextureTransform, bool bAlwaysMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the height alpha texture's UV transform. Transform is applied relative UVSpace unless struct property bInWorldSpaceScale is true @param InTextureTransform the height alpha texture's transform @param bAlwaysMarkDirty mark the package dirty when alpha transform changes
- L585 _public function_ `virtual ELandscapeTexturePatchTextureChannel GetHeightAlphaSourceTextureChannel() const` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L593 _public prototype_ `virtual void SetHeightAlphaTextureChannel(ELandscapeTexturePatchTextureChannel InTextureChannel, bool bAlwaysMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the height alpha texture patch color channel @param InTextureChannel the color channel of the texture to use for the height alpha @param bAlwaysMarkDirty mark the package dirty when channel property changes
- L609 _public prototype_ `virtual UTextureRenderTarget2D* GetHeightAlphaRenderTarget(bool bMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Gets the internal height alpha render target, if the height alpha source mode is set to Texture Backed Render Target Things that should be set up if using the internal render target: - An appropriate texture size should have been set with SetResolution. If the patch extent has already been set, you can base your resolution on the extent and the resolution of the landscape by using GetInitResolutionFromLandscape() - The alpha uses RenderTargetFormat RTF_R8 by default. The AlphaTextureChannel property defines the single color channel storing the Alpha data @param bMarkDirty If true, marks the containing package as dirty, since the render target is presumably being written to. Can be set to false if the render target is not being written to.
- L616 _public prototype_ `void SetHeightTextureAsset(UTexture* TextureIn);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the texture used for height when the height source mode is set to texture asset. Note that virtual textures are not supported.
- L638 _public prototype_ `virtual UTextureRenderTarget2D* GetHeightRenderTarget(bool bMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Gets the internal height render target, if source mode is set to Texture Backed Render Target. Things that should be set up if using the internal render target: - SetHeightSourceMode should have been called with TextureBackedRenderTarget. - An appropriate texture size should have been set with SetResolution. If the patch extent has already been set, you can base your resolution on the extent and the resolution of the landscape by using GetInitResolutionFromLandscape(). - SetHeightRenderTargetFormat should have been called with a desired format. In particular, if using an alpha channel, the format should have an alpha channel (and SetUseAlphaChannelForHeight should have been called with "true"). In addition, you may need to call SetHeightEncodingMode, SetHeightEncodingSettings, and SetZeroHeightMeaning based on how you want the data you write to be interpreted. This part is not specific to using an internal render target, since you are likely to need to do that with a TextureAsset source mode as well. @param bMarkDirty If true, marks the containing package as dirty, since the render target is presumably being written to. Can be set to false if the render target is not being written to.
- L641 _public prototype_ `void SetHeightRenderTargetFormat(ETextureRenderTargetFormat Format);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch, meta = (ETextureRenderTargetFormat = "ETextureRenderTargetFormat::RTF_R32f"))`
- L645 _public function_ `void SetUseAlphaChannelForHeight(bool bUse)` — `UE_DEPRECATED(all, "SetUseAlphaChannelForHeight is deprecated. Use SetHeightAlphaSourceMode with ELandscapeTexturePatchAlphaSourceMode instead (use alpha mode None or SourceTextureChannel for legacy behavior)")` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "SetUseAlphaChannelForHeight has been deprecated, use SetHeightAlphaSourceMode instead (use alpha mode None or SourceTextureChannel for legacy behavior)."))`
- L656 _public function_ `void SetHeightEncodingMode(ELandscapeTextureHeightPatchEncoding EncodingMode)` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Set the height encoding mode for the patch, which determines how stored values in the patch are translated into heights when applying to landscape.
- L676 _public prototype_ `void ResetHeightEncodingMode(ELandscapeTextureHeightPatchEncoding EncodingMode);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Just like SetSourceEncodingMode, but resets ZeroInEncoding, WorldSpaceEncodingScale, and height render target format to mode-specific defaults.
- L684 _public prototype_ `void SetHeightEncodingSettings(const FLandscapeTexturePatchEncodingSettings& Settings);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Set settings that determine how values in the patch are translated into heights. This is only used if the encoding mode is not NativePackedHeight, where values are expected to be already in the same space as the landscape heightmap.
- L690 _public function_ `void SetZeroHeightMeaning(ELandscapeTextureHeightPatchZeroHeightMeaning ZeroHeightMeaningIn)` — `UFUNCTION(BlueprintCallable, Category = "LandscapePatch")` — Set how zero height is interpreted, see comments in ELandscapeTextureHeightPatchZeroHeightMeaning.
- L703 _public prototype_ `virtual void AddWeightPatch(const FName& InWeightmapLayerName, ELandscapeTexturePatchSourceMode SourceMode, bool bUseAlphaChannel);` — `UE_DEPRECATED(all, "Use CreateWeightPatch with ELandscapeTexturePatchAlphaSourceMode instead (use alpha mode None or SourceTextureChannel for legacy behavior)")` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "AddWeightPatch has been deprecated, use CreateWeightPatch with ELandscapeTexturePatchAlphaSourceMode instead (use None or SourceTextureChannel for legacy behavior)."))` — Weight related functions:
- L709 _public prototype_ `virtual void CreateWeightPatch(const FName& InWeightmapLayerName, ELandscapeTexturePatchSourceMode InSourceMode, ELandscapeTexturePatchAlphaSourceMode InAlphaSourceMode);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — By default, the layer is added with source mode set to be a texture-backed render target.
- L712 _public prototype_ `virtual void RemoveWeightPatch(const FName& InWeightmapLayerName);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L715 _public prototype_ `virtual void RemoveAllWeightPatches();` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L719 _public prototype_ `virtual void DisableAllWeightPatches();` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the source mode of all weight patches to "None".
- L722 _public prototype_ `TArray<FName> GetAllWeightPatchLayerNames();` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L725 _public prototype_ `virtual ELandscapeTexturePatchSourceMode GetWeightPatchSourceMode(const FName& InWeightmapLayerName);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L728 _public prototype_ `virtual const FLandscapeTexturePatchTextureTransform& GetWeightPatchTextureTransform(const FName& InWeightmapLayerName) const;` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L737 _public prototype_ `virtual void SetWeightPatchTextureTransform(const FName& InWeightmapLayerName, const FLandscapeTexturePatchTextureTransform& InTextureTransform, bool bAlwaysMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the weight texture's UV transform. Transform is applied relative UVSpace unless struct property bInWorldSpaceScale is true @param InWeightmapLayerName weightmap layer name to set the texture transform @param InTextureTransform the weight texture's transform @param bAlwaysMarkDirty mark the package dirty when transform changes
- L740 _public prototype_ `virtual UTexture* GetWeightPatchTextureAsset(const FName& InWeightmapLayerName);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L743 _public prototype_ `virtual void SetWeightPatchSourceMode(const FName& InWeightmapLayerName, ELandscapeTexturePatchSourceMode NewMode);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L746 _public prototype_ `virtual ELandscapeTexturePatchTextureChannel GetWeightPatchTextureChannel(const FName& InWeightmapLayerName) const;` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L755 _public prototype_ `virtual void SetWeightPatchTextureChannel(const FName& InWeightmapLayerName, ELandscapeTexturePatchTextureChannel InTextureChannel, bool bAlwaysMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the texture patch color channel specific weight patch @param InWeightmapLayerName weightmap layer name to set the texture channel @param InTextureChannel the channel of the texture the weight patch will use @param bAlwaysMarkDirty mark the package dirty when property changes
- L758 _public prototype_ `void SetWeightPatchTextureAsset(const FName& InWeightmapLayerName, UTexture* TextureIn);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L765 _public prototype_ `virtual UTextureRenderTarget2D* GetWeightPatchRenderTarget(const FName& InWeightmapLayerName, bool bMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — @param bMarkDirty If true, marks the containing package as dirty, since the render target is presumably being written to. Can be set to false if the render target is not being written to.
- L769 _public prototype_ `virtual void SetUseAlphaChannelForWeightPatch(const FName& InWeightmapLayerName, bool bUseAlphaChannel);` — `UE_DEPRECATED(all, "SetUseAlphaChannelForWeightPatch is deprecated. Use SetWeightPatchAlphaSourceMode with ELandscapeTexturePatchAlphaSourceMode instead (use None or SourceTextureChannel for legacy behavior)")` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "SetUseAlphaChannelForWeightPatch has been deprecated, use SetWeightPatchAlphaSourceMode instead (use None or SourceTextureChannel for legacy behavior)."))`
- L772 _public prototype_ `virtual ELandscapeTexturePatchAlphaSourceMode GetWeightPatchAlphaSourceMode(const FName& InWeightmapLayerName) const;` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L782 _public prototype_ `virtual void SetWeightPatchAlphaSourceMode(const FName& InWeightmapLayerName, ELandscapeTexturePatchAlphaSourceMode InSourceMode, bool bInOverrideAlpha = true, bool bAlwaysMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the default weight patch alpha source mode for all weight patches or overrides the source for a specific weight patch @param InWeightmapLayerName weightmap layer name to set the alpha mode. Overrides a specific layer or sets default source mode when name is None @param InSourceMode the alpha source mode @param bInOverrideAlpha sets the weightmap layer's override flag. When false, the weightmap layer will fallback to the default source mode @param bAlwaysMarkDirty mark the package dirty when property changes
- L785 _public prototype_ `virtual const UTexture* GetWeightPatchAlphaTextureAsset(const FName& InWeightmapLayerName) const;` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L798 _public prototype_ `virtual UTextureRenderTarget2D* GetWeightPatchAlphaRenderTarget(const FName& InWeightmapLayerName, bool bMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Gets the internal weight patch alpha render target, if the weight patch alpha source mode is set to Texture Backed Render Target Returns a reference to the default (shared) weightmap alpha render target unless the given weightmap patch overrides the default alpha settings - The alpha uses RenderTargetFormat RTF_R8 by default. The AlphaTextureChannel property defines the single color channel storing the Alpha data @param bMarkDirty If true, marks the containing package as dirty, since the render target is presumably being written to. Can be set to false if the render target is not being written to.
- L808 _public prototype_ `void SetWeightPatchAlphaTextureAsset(const FName& InWeightmapLayerName, UTexture* InTexture, bool bInOverrideAlpha = true, bool bAlwaysMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the default weight patch alpha texture asset for all weight patches or overrides the texture for a specific weight patch @param InWeightmapLayerName weightmap layer name to set the alpha texture. Overrides a specific layer or sets the default texture when name is None @param InTexture the alpha texture the weightmap will use @param bInOverrideAlpha sets the weightmap layer's override flag. When false, the weightmap layer will fallback to the default alpha texture @param bAlwaysMarkDirty mark the package dirty when property changes
- L811 _public prototype_ `virtual const FLandscapeTexturePatchTextureTransform& GetWeightPatchAlphaTextureTransform(const FName& InWeightmapLayerName) const;` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L820 _public prototype_ `virtual void SetWeightPatchAlphaTextureTransform(const FName& InWeightmapLayerName, const FLandscapeTexturePatchTextureTransform& InTextureTransform, bool bAlwaysMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the weight texture's alpha UV transform. Transform is applied relative UVSpace unless struct property bInWorldSpaceScale is true @param InWeightmapLayerName weightmap layer name to set the texture transform @param InTextureTransform the weight alpha texture's transform @param bAlwaysMarkDirty mark the package dirty when alpha transform changes
- L823 _public prototype_ `virtual ELandscapeTexturePatchTextureChannel GetWeightPatchAlphaTextureChannel(const FName& InWeightmapLayerName) const;` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L833 _public prototype_ `virtual void SetWeightPatchAlphaTextureChannel(const FName& InWeightmapLayerName, ELandscapeTexturePatchTextureChannel InTextureChannel, bool bInOverrideAlpha = true, bool bAlwaysMarkDirty = true);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Sets the texture patch color channel for all weight patches or set the texture channel for a specific weight patch alpha override @param InWeightmapLayerName weightmap layer name to set the alpha texture channel. Overrides a specific layer or sets to the default texture channel when name is None @param InTextureChannel the channel of the texture the alpha mask will use @param bInOverrideAlpha sets the weightmap layer's override flag. When false, the weightmap layer will fallback to the default alpha channel @param bAlwaysMarkDirty mark the package dirty when property changes
- L836 _public prototype_ `virtual void SetWeightPatchBlendModeOverride(const FName& InWeightmapLayerName, ELandscapeTexturePatchBlendMode BlendMode);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L839 _public prototype_ `virtual void ClearWeightPatchBlendModeOverride(const FName& InWeightmapLayerName);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L842 _public prototype_ `virtual void SetEditVisibilityLayer(const FName& InWeightmapLayerName, const bool bEditVisibilityLayer);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)`
- L849 _protected member_ `int32 ResolutionX = 32;` — `UPROPERTY(EditDefaultsOnly, Category = Settings)`
- L851 _protected member_ `int32 ResolutionY = 32;` — `UPROPERTY(EditDefaultsOnly, Category = Settings)`
- L856 _protected member_ `FVector2D UnscaledPatchCoverage = FVector2D(2000, 2000);` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (UIMin = "0", ClampMin = "0"))` — At scale 1.0, the X and Y of the region affected by the height patch. This corresponds to the distance from the center of the first pixel to the center of the last pixel in the patch texture in the X and Y directions.
- L860 _protected member_ `ELandscapeTexturePatchBlendMode BlendMode = ELandscapeTexturePatchBlendMode::AlphaBlend;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Determines how the patch's heightmap is combined with the previous state of the landscape.
- L863 _protected member_ `ELandscapeTexturePatchFalloffMode FalloffMode = ELandscapeTexturePatchFalloffMode::RoundedRectangle;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L869 _protected member_ `float Falloff = 0;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0", UIMax = "2000"))` — Distance (in unscaled world coordinates) across which to smoothly fall off the patch effects.
- L880 _protected member_ `ELandscapeTexturePatchSourceMode HeightSourceMode = ELandscapeTexturePatchSourceMode::None;` — `UPROPERTY(EditAnywhere, Category = HeightPatch, meta = (EditConditionHides, EditCondition = "false"))`
- L886 _protected member_ `ELandscapeTexturePatchSourceMode DetailPanelHeightSourceMode = ELandscapeTexturePatchSourceMode::None;` — `UPROPERTY(EditAnywhere, Category = HeightPatch, meta = (DisplayName = "Source Mode"))` — How the heightmap of the patch is stored.
- L894 _protected member_ `ELandscapeTexturePatchTextureChannel HeightTextureChannel = ELandscapeTexturePatchTextureChannel::Red;` — `UPROPERTY(EditAnywhere, Category = HeightPatch, meta = (DisplayName = "Texture Channels", EditConditionHides, EditCondition = "HeightSourceMode != ELandscapeTexturePatchSourceMode::None && HeightSourceMode != ELandscapeTexturePatchSourceMode::InternalTexture && HeightEncoding != ELandscapeTextureHeightPatchEncoding::NativePackedHeight"))` — Texture's color channel used for the height. The texture's Red channel is selected by default. The patch will not affect the landscape when no channel is selected. When the height source mode is InternalTexture or HeightEncoding is NativePackedHeight the texture channel cannot be customized (assumes RG channel)
- L898 _protected member_ `TObjectPtr<ULandscapeHeightTextureBackedRenderTarget> HeightInternalData = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = HeightPatch, Instanced, AdvancedDisplay, meta = (DisplayName = "Debug Data"))` — Not directly settable via detail panel- for display/debugging purposes only.
- L906 _protected member_ `TObjectPtr<UTexture> HeightTextureAsset = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HeightPatch, meta = (EditConditionHides, EditCondition = "HeightSourceMode == ELandscapeTexturePatchSourceMode::TextureAsset", DisallowedAssetDataTags = "VirtualTextureStreaming=True"))` — Texture used when source mode is set to a texture asset.
- L909 _protected member_ `FLandscapeTexturePatchTextureTransform HeightTextureUVTransform;` — `UPROPERTY(EditAnywhere, Category = HeightPatch, meta = (DisplayName = "Texture Transform"), meta = (EditConditionHides, EditCondition = "HeightSourceMode != ELandscapeTexturePatchSourceMode::None"))`
- L913 _protected member_ `bool bUseTextureAlphaForHeight_DEPRECATED = false;` — `UE_DEPRECATED(5.8, "bUseAlphaChannel is deprecated, HeightAlphaSettings.SetAlphaSourceMode() with ELandscapeTexturePatchAlphaSourceMode (use None or SourceTextureChannel for legacy behavior).")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use HeightAlphaSettings.SetAlphaSourceMode() with ELandscapeTexturePatchAlphaSourceMode instead (use None or SourceTextureChannel for legacy behavior)"))`
- L916 _protected member_ `FLandscapeTexturePatchAlphaSettings HeightAlphaSettings;` — `UPROPERTY(EditAnywhere, Category = HeightPatch, meta = (EditConditionHides, EditCondition = "HeightSourceMode != ELandscapeTexturePatchSourceMode::None"))`
- L921 _protected member_ `ELandscapeTextureHeightPatchEncoding HeightEncoding = ELandscapeTextureHeightPatchEncoding::WorldUnits;` — `UPROPERTY(EditAnywhere, Category = HeightPatch, meta = ( EditCondition = "HeightSourceMode != ELandscapeTexturePatchSourceMode::InternalTexture"))` — How the values stored in the patch represent the height. Not customizable for Internal Texture source mode, which always uses native packed height.
- L926 _protected member_ `FLandscapeTexturePatchEncodingSettings HeightEncodingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HeightPatch, meta = (UIMin = "0", UIMax = "1", EditCondition = "HeightSourceMode != ELandscapeTexturePatchSourceMode::InternalTexture && HeightEncoding != ELandscapeTextureHeightPatchEncoding::NativePackedHeight"))` — Encoding settings. Not relevant when using native packed height as the encoding.
- L932 _protected member_ `ELandscapeTextureHeightPatchZeroHeightMeaning ZeroHeightMeaning = ELandscapeTextureHeightPatchZeroHeightMeaning::PatchZ;` — `UPROPERTY(EditAnywhere, Category = HeightPatch)` — How 0 height is interpreted.
- L938 _protected member_ `bool bApplyComponentZScale = true;` — `UPROPERTY(EditAnywhere, Category = HeightPatch, AdvancedDisplay, meta = (DisplayName = "Apply Component Z Scale"))` — Whether to apply the patch Z scale to the height stored in the patch.
- L952 _protected member_ `TArray<TObjectPtr<ULandscapeWeightPatchTextureInfo>> WeightPatches;` — `UPROPERTY(EditAnywhere, Category = WeightPatches, Instanced, NoClear, meta=(NoResetToDefault))` — Weight patches. Note that manipulating these in the blueprint editor will not reliably update instances that are already placed into the world, due to current limitations in how change detection is done for such arrays. Specifically, existing instances that are actually not customized are very likely to be erroneously be treated as having customized their version of the array, causing the blueprint changes to not be pushed to those instances when they otherwise would be for most other properties.
- L959 _protected member_ `FLandscapeTexturePatchAlphaSettings WeightPatchesAlphaSettings;` — `UPROPERTY(EditAnywhere, Category = WeightPatches)` — Default weight patches alpha settings. Defines the alpha mask settings for all weight patches within this texture patch. Alpha is only applied to weight patches with a valid source mode. Alpha settings can be overridden by individual weight patches.
- L964 _protected member_ `ELandscapeTexturePatchBlendMode WeightPatchesBlendMode = ELandscapeTexturePatchBlendMode::AlphaBlend;` — `UPROPERTY(EditAnywhere, Category = WeightPatches)` — Determines how the patch's weightmap layers are combined with the previous state of the landscape. Blend mode can be overriden by individual weight patches
- L972 _protected prototype_ `void RequestReinitializeHeight();` — `UFUNCTION(CallInEditor, Category = HeightPatch, meta = (DisplayName= "Reinitialize Height"))` — Given the current initialization settings, reinitialize the height patch.
- L975 _protected prototype_ `void RequestReinitializeWeights();` — `UFUNCTION(CallInEditor, Category = WeightPatches, meta = (DisplayName = "Reinitialize Weights"))`
- L977 _protected member_ `bool bReinitializeHeightOnNextRender = false;`
- L989 _protected prototype_ `void SnapToLandscape();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = Initialization)` — Adjusts patch rotation to be aligned to a 90 degree increment relative to the landscape, adjusts UnscaledPatchCoverage such that it becomes a multiple of landscape quad size, and adjusts patch location so that the boundaries of the covered area lie on the nearest landscape vertices. Note that this doesn't adjust the resolution of the texture that the patch uses, so landscape vertices within the inside of the patch may still not always align with texture patch pixel centers (if the resolutions aren't multiples of each other).
- L993 _protected member_ `bool bBaseResolutionOffLandscape = true;` — `UPROPERTY(EditAnywhere, Category = Initialization)` — When initializing from landscape, set resolution based off of the landscape (and a multiplier).
- L1001 _protected member_ `float ResolutionMultiplier = 1;` — `UPROPERTY(EditAnywhere, Category = Initialization, meta = (EditCondition = "bBaseResolutionOffLandscape"))` — Multiplier to apply to landscape resolution when initializing patch resolution. A value greater than 1.0 will use higher resolution than the landscape (perhaps useful for slightly more accurate results while not aligned to landscape), and a value less that 1.0 will use lower.
- L1005 _protected member_ `int32 InitTextureSizeX = 33;` — `UPROPERTY(EditAnywhere, Category = Initialization, meta = (EditCondition = "!bBaseResolutionOffLandscape", ClampMin = "1"))` — Texture width to use when reinitializing using Reinitialize Weights or ReinitializeHeight, if not basing resolution off landscape.
- L1009 _protected member_ `int32 InitTextureSizeY = 33;` — `UPROPERTY(EditAnywhere, Category = Initialization, meta = (EditCondition = "!bBaseResolutionOffLandscape", ClampMin = "1"))` — Texture height to use when reinitializing using Reinitialize Weights or ReinitializeHeight, if not basing resolution off landscape.
- L1011 _protected prototype_ `UTexture2D* GetHeightInternalTexture();`
- L1012 _protected prototype_ `UTextureRenderTarget2D* GetHeightAlphaRenderTarget();`
- L1013 _protected prototype_ `UTexture2D* GetHeightAlphaInternalTexture();`
- L1015 _protected prototype_ `UTextureRenderTarget2D* GetWeightPatchRenderTarget(ULandscapeWeightPatchTextureInfo* WeightPatch);`
- L1016 _protected prototype_ `UTexture2D* GetWeightPatchInternalTexture(ULandscapeWeightPatchTextureInfo* WeightPatch);`
- L1018 _protected prototype_ `UTextureRenderTarget2D* GetWeightPatchAlphaRenderTarget(ULandscapeWeightPatchTextureInfo* WeightPatch, bool bMarkDirty = true);` — Returns the default weight patch alpha render target or the specific weight patch override render target
- L1020 _protected prototype_ `UTexture2D* GetWeightPatchAlphaInternalTexture(ULandscapeWeightPatchTextureInfo* WeightPatch, bool bMarkDirty = true);` — Returns the default weight patch alpha internal texture or the specific weight patch override internal texture
- L1023 _private prototype_ `void UpdateHeightConvertToNativeParamsIfNeeded();`
- L1028 _private prototype_ `FLandscapeTexturePatchAlphaSettings& GetWeightPatchAlphaSettings(ULandscapeWeightPatchTextureInfo* WeightPatch);` — If the weight patch overrides the alpha, returns the specific weight patch override settings. Otherwise, returns the default weight patch alpha settings
- L1029 _private prototype_ `const FLandscapeTexturePatchAlphaSettings& GetWeightPatchAlphaSettingsConst(ULandscapeWeightPatchTextureInfo* WeightPatch) const;`
- L1031 _private prototype_ `TObjectPtr<ULandscapeWeightPatchTextureInfo> GetWeightPatch(const FName& InWeightmapLayerName, const TCHAR* InDebugLogName = TEXT("ULandscape`
- L1034 _private prototype_ `void TransitionHeightSourceModeInternal(ELandscapeTexturePatchSourceMode OldMode, ELandscapeTexturePatchSourceMode NewMode);`
- L1035 _private prototype_ `FLandscapeHeightPatchConvertToNativeParams GetHeightConvertToNativeParams() const;`
- L1037 _private prototype_ `UTextureRenderTarget2D* ApplyToHeightmap(UE::Landscape::EditLayers::FRenderParams* RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder, UTextureRenderTarget2D* InCombinedResult, const FTransform& LandscapeHeightmapToWorld, bool& bHasRenderedSomething, ERHIAccess OutputAccess = ERHIAccess::None);`
- L1040 _private prototype_ `void ApplyToWeightmap(UE::Landscape::EditLayers::FRenderParams* RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder, ULandscapeWeightPatchTextureInfo* PatchInfo, FTextureResource* InMergedLandscapeTextureResource, int32 LandscapeTextureSliceIndex, const FIntPoint& LandscapeTextureResolution, const FTransform& LandscapeHeightmapToWorld, bool& bHasRenderedSomething, ERHIAccess OutputAccess = ERHIAccess::None);`
- L1044 _private prototype_ `void GetCommonShaderParams(const FTransform& LandscapeHeightmapToWorldIn, const FIntPoint& SourceResolutionIn, const FIntPoint& DestinationResolutionIn, const FLandscapeTexturePatchTextureTransform& SourceTextureTransformIn, const FLandscapeTexturePatchTextureTransform& AlphaTextureTransformIn, FTransform& PatchToWorldOut, FVector2f& PatchWorldDimensionsOut, FMatrix44f& HeightmapToPatchUVOut, FMatrix44f& HeightmapToPatchUVTransformOut, FMatrix44f& HeightmapAlphaToPatchUVTransformOut, FIntRect& DestinationBoundsOut, FVector2f& EdgeUVDeadBorderOut, float& FalloffWorldMarginOut) const;`
- L1050 _private prototype_ `void GetHeightShaderParams(const FTransform& LandscapeHeightmapToWorldIn, const FIntPoint& SourceResolutionIn, const FIntPoint& DestinationResolutionIn, UE::Landscape::FApplyLandscapeTextureHeightPatchPSParameters& ParamsOut, FIntRect& DestinationBoundsOut) const;`
- L1053 _private prototype_ `void GetWeightShaderParams(const FTransform& LandscapeHeightmapToWorldIn, const FIntPoint& SourceResolutionIn, const FIntPoint& DestinationResolutionIn, const ULandscapeWeightPatchTextureInfo* WeightPatchInfo, UE::Landscape::FApplyLandscapeTextureWeightPatchPSParameters& ParamsOut, FIntRect& DestinationBoundsOut) const;`
- L1056 _private prototype_ `FMatrix44f GetPatchToHeightmapUVs(const FTransform& LandscapeHeightmapToWorld, int32 PatchSizeX, int32 PatchSizeY, int32 HeightmapSizeX, int32 HeightmapSizeY) const;`
- L1057 _private prototype_ `void ReinitializeHeight(UTextureRenderTarget2D* InCombinedResult, const FTransform& LandscapeHeightmapToWorld);`
- L1061 _private prototype_ `void ReinitializeWeightPatch(ULandscapeWeightPatchTextureInfo* PatchInfo, FTextureResource* InputResource, FIntPoint ResourceSize, int32 SliceIndex, const FTransform& LandscapeHeightmapToWorld);` — @param SliceIndex set to a negative value when not using a Texture2DArray
- L1065 _private prototype_ `bool WeightPatchCanRender(const ULandscapeWeightPatchTextureInfo& InWeightPatch) const;`
- L1067 _private prototype_ `void ResetHeightRenderTargetFormat();`
- L1071 _private member_ `TEnumAsByte<ETextureRenderTargetFormat> HeightRenderTargetFormat = ETextureRenderTargetFormat::RTF_R32f;` — `UPROPERTY(EditDefaultsOnly, Category = Settings)`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Landscape` (scope `UE`)
